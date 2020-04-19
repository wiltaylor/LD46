#include "ui_system.h"
#include "platform/asset.h"

void UISystem::init(){
    m_render_event = std::bind(&UISystem::on_render, this);

    auto assetman =get_asset_manager();
    m_ui_sprite = assetman->get_texture_asset("assets/mainscreen.png", Global);
    m_font = assetman->get_font_asset("assets/ThatNogoFontCasual.ttf", 25, Global);
}

void UISystem::on_enable() {

    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->register_handler(&m_render_event);
}

void UISystem::on_disable(){

    auto em = ecs::get_event_manager();
    auto event = em->get_event<RenderEvent>();
    event->unregister_handler(&m_render_event);
}

void UISystem::on_render() {
    auto rend = get_renderer();

    rend->draw(m_ui_sprite, glm::vec2(0.0f, 0.0f));

    rend->draw_text(m_font, "Hey", glm::vec2(0.0f, 0.0f));
}