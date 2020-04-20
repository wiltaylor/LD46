#include "ui_system.h"
#include "platform/asset.h"
#include "ecs/entity.h"
#include "coords.h"
#include <iostream>
#include "components.h"

void UISystem::init(){
    m_render_event = std::bind(&UISystem::on_render, this);

    m_mousedown_event = std::bind(&UISystem::on_mousedown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_mouseup_event = std::bind(&UISystem::on_mouseup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    m_unit_select_event = std::bind(&UISystem::on_unit_select, this, std::placeholders::_1);

    auto assetman =get_asset_manager();
    m_ui_sprite = assetman->get_texture_asset("assets/mainscreen.png", Global);
    m_ui_bar_empty = assetman->get_texture_asset("assets/empty_bar.png", Global);
    m_ui_bar_red = assetman->get_texture_asset("assets/full_bar_red.png", Global);
    m_ui_bar_green = assetman->get_texture_asset("assets/full_bar_green.png", Global);
    m_ui_bar_power = assetman->get_texture_asset("assets/full_bar_power.png", Global);
    m_font = assetman->get_font_asset("assets/ThatNogoFontCasual.ttf", 25, Global);

    m_selected_entity = 0;
}

void UISystem::on_enable() {

    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();
    auto unit_selected_event = em->get_event<UnitSelected>();

    event->register_handler(&m_render_event);
    mouseup_event->register_handler_priority(&m_mouseup_event);
    mousedown_event->register_handler_priority(&m_mousedown_event);
    unit_selected_event->register_handler(&m_unit_select_event);
}

void UISystem::on_disable(){

    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    auto mouseup_event = em->get_event<MouseUpEvent>();
    auto mousedown_event = em->get_event<MouseDownEvent>();
    auto unit_selected_event = em->get_event<UnitSelected>();

    event->unregister_handler(&m_render_event);
    mouseup_event->unregister_handler(&m_mouseup_event);
    mousedown_event->unregister_handler(&m_mousedown_event);
    unit_selected_event->unregister_handler(&m_unit_select_event);
}

bool UISystem::on_mousedown(int x, int y, int button){
    if(x < 16 || x > 880 || y < 60 || y > 500)
        return true;
    return false;
}

bool UISystem::on_mouseup(int x, int y, int button){
    if(x < 16 || x > 880 || y < 60 || y > 500)
        return true;
    return false;
}

void UISystem::render_bar(float x, float y, const char* text, float percent, BarColor color){
    auto rend = get_renderer();

    float full_width = 200 * percent;
    float empty_width = 200 * (1.0f - percent);

    Rectangle src_fullRect;
    Rectangle src_emptyRect;
    Rectangle dest_fullRect;
    Rectangle dest_emptyRect;

    src_fullRect.x = 0;
    src_fullRect.y = 0;
    src_fullRect.width = full_width;
    src_fullRect.height = 40;

    dest_fullRect.x = x;
    dest_fullRect.y = y;
    dest_fullRect.width = full_width;
    dest_fullRect.height = 40;

    src_emptyRect.x = 200 - empty_width;
    src_emptyRect.y = 0;
    src_emptyRect.width = empty_width;
    src_emptyRect.height = 40;

    dest_emptyRect.x = x + full_width;
    dest_emptyRect.y = y;
    dest_emptyRect.width = empty_width;
    dest_emptyRect.height = 40;

    switch(color){
        case BAR_Red:
            rend->draw(m_ui_bar_red, src_fullRect, dest_fullRect);
            break;
        case BAR_Green:
            rend->draw(m_ui_bar_green, src_fullRect, dest_fullRect);
            break;
        case BAR_Power:
            rend->draw(m_ui_bar_power, src_fullRect, dest_fullRect);
            break;
    }

    rend->draw(m_ui_bar_empty, src_emptyRect, dest_emptyRect);
    rend->draw_text(m_font, text, glm::vec2(x + 10.0f, y + 10.0f));
}

void UISystem::on_render() {
    auto rend = get_renderer();

    rend->draw(m_ui_sprite, glm::vec2(0.0f, 0.0f));

    render_bar(10.0f, 10.0f, "Hunger", 0.25f, BAR_Red);
    render_bar(250.0f, 10.0f, "HP", 1.0f, BAR_Green);
    render_bar(500.0f, 10.0f, "Power", 0.9f, BAR_Power);

    auto em = ecs::get_entity_manager();

    auto unit = em->get_component<Unit>(m_selected_entity);

    if(unit == nullptr){
        auto building = em->get_component<Building>(m_selected_entity);

        if(building == nullptr)
            return;

        rend->draw(building->animation_frames[building->current_frame], glm::vec2(10.0f, screen_height() - building->height));

        switch(building->type){
            case BUILDING_Monster:
                rend->draw_text(m_font, "Grrr...bring me more burgers!", glm::vec2(250.0f, screen_height() - 75.0f));
                break;
            case BUILDING_Burger:
                render_bar(175.0f, screen_height() - 75.0f, "Burgers Left", 0.75f, BAR_Green);
                break;
        }
    }else{
        rend->draw(unit->down_texture, glm::vec2(10.0f, screen_height() - unit->height));

        switch(unit->type){
            case UNIT_Cultist:
                break;
            case UNIT_Wizard:
                break;
            case UNIT_Enemy:
                rend->draw_text(m_font, "Apply fire to face. If problem persists apply more fire!", glm::vec2(250.0f, screen_height() - 75.0f));
                break;
        }
    }


}

void UISystem::on_unit_select(unsigned int entity){
    m_selected_entity = entity;
}