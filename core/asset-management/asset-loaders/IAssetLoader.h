//
// Created by probn on 30/05/2025.
//

#ifndef CMLENGINE_IASSETLOADER_H
#define CMLENGINE_IASSETLOADER_H

#include "IAssetLoaderBase.h"

template<typename TAsset>
requires std::is_base_of_v<IAsset, TAsset>
class IAssetLoader : public IAssetLoaderBase
{
    virtual TAsset* loadTyped(const std::string& path) = 0;
public:
    IAsset * load(const std::string &path) override;

    [[nodiscard]] const type_info & getAssetType() const override;
};


#endif //CMLENGINE_IASSETLOADER_H
