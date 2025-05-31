//
// Created by probn on 29/05/2025.
//

#ifndef CMLENGINE_ASSETMANAGER_H
#define CMLENGINE_ASSETMANAGER_H

#include <unordered_map>
#include <typeindex>
#include "asset-management/asset-loaders/IAssetLoader.h"

class AssetManager
{
    std::unordered_map<std::type_index, IAssetLoaderBase*> m_loaders;

public:
    AssetManager() = default;

    ~AssetManager();
    AssetManager(const AssetManager&) = delete;

    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) noexcept = default;

    AssetManager& operator=(AssetManager&&) = default;

    void registerLoader(IAssetLoaderBase* loader);
    void unregisterLoader(std::type_index index);

    template<typename TAsset>
    requires(std::is_base_of_v<IAsset, TAsset>)
    TAsset* load(const std::string& path);
};


#endif //CMLENGINE_ASSETMANAGER_H
