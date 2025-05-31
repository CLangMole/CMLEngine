//
// Created by probn on 29/05/2025.
//

#include "AssetManager.h"

template<typename TAsset>
requires(std::is_base_of_v<IAsset, TAsset>)
TAsset *AssetManager::load(const std::string &path) {
    return m_loaders[typeid(TAsset)]->load(path);
}

void AssetManager::registerLoader(IAssetLoaderBase *loader) {
    m_loaders.emplace(loader->getAssetType(), loader);
}

void AssetManager::unregisterLoader(std::type_index index) {
    IAssetLoaderBase* loader = m_loaders[index];
    m_loaders.erase(index);

    delete loader;
}

AssetManager::~AssetManager() {
    for (auto& [key, val] : m_loaders){
        delete val;
        val = nullptr;
    }

    m_loaders.clear();
}
