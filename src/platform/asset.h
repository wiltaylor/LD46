#ifndef __ASSET_H_
#define __ASSET_H_

enum AssetPersistance {
    LevelOnly,
    Global
};

class AssetManager {
public:
    AssetManager() {};
    virtual ~AssetManager() {};

    virtual unsigned int get_texture_asset(const char* name, AssetPersistance persist) = 0;
    virtual unsigned int get_font_asset(const char* name, int size, AssetPersistance persist) = 0;
};

AssetManager* get_asset_manager();

#endif // __ASSET_H_
