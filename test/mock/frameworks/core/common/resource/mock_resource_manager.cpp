/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/common/resource/resource_manager.h"

namespace OHOS::Ace {
ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

RefPtr<ResourceAdapter> ResourceManager::GetOrCreateResourceAdapter(const RefPtr<ResourceObject>& resourceObject)
{
    (void)resourceObject;
    return nullptr;
}

void ResourceManager::UpdateResourceConfig(const std::string& bundleName, const std::string& moduleName,
    int32_t instanceId, const ResourceConfiguration& config, bool themeFlag)
{
    (void)bundleName;
    (void)moduleName;
    (void)instanceId;
    (void)config;
    (void)themeFlag;
}

void ResourceManager::UpdateColorMode(
    const std::string& bundleName, const std::string& moduleName, int32_t instanceId, ColorMode colorMode)
{
    (void)bundleName;
    (void)moduleName;
    (void)instanceId;
    (void)colorMode;
}

void ResourceManager::RegisterMainResourceAdapter(const std::string& bundleName, const std::string& moduleName,
    int32_t instanceId, const RefPtr<ResourceAdapter>& resAdapter)
{
    (void)bundleName;
    (void)moduleName;
    (void)instanceId;
    (void)resAdapter;
}

void ResourceManager::DumpResLoadError() {}
} // namespace OHOS::Ace
