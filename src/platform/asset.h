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

    virtual unsigned int get_texture_asset(char* name, AssetPersistance persist) = 0;
};

AssetManager* getAssetManager();

#endif // __ASSET_H_