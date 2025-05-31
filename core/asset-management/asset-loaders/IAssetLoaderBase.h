//
// Created by probn on 30/05/2025.
//

#ifndef CMLENGINE_IASSETLOADERBASE_H
#define CMLENGINE_IASSETLOADERBASE_H

#include "asset-management/IAsset.h"
#include <string>

class IAssetLoaderBase
{
public:
    virtual ~IAssetLoaderBase() = default;
    virtual IAsset* load(const std::string& path) = 0;
    [[nodiscard]] virtual const type_info& getAssetType() const = 0;
};


#endif //CMLENGINE_IASSETLOADERBASE_H
