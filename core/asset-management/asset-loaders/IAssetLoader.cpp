//
// Created by probn on 30/05/2025.
//
#include "IAssetLoader.h"

template<typename TAsset>
requires std::is_base_of_v<IAsset, TAsset>IAsset *IAssetLoader<TAsset>::load(const std::string &path) {
    return loadTyped(path);
}

template<typename TAsset>
requires std::is_base_of_v<IAsset, TAsset>const type_info &IAssetLoader<TAsset>::getAssetType() const {
    return typeid(TAsset);
}