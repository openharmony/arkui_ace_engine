/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "base/utils/feature_manager.h"

namespace OHOS::Ace {
FeatureManager& FeatureManager::GetInstance()
{
    static FeatureManager instance;
    return instance;
}

FeatureManager::FeatureManager()
{
    Init();
}

void FeatureManager::Init()
{
    initialized_ = true;
}

int32_t FeatureManager::GetFeatureParam(const std::string& key, std::string& value)
{
    value.clear();
    if (key.empty()) {
        return KEY_NOT_FOUND;
    }
    value = "mock_feature_param";
    return SUCCESS;
}

#ifdef ACE_UNITTEST
void FeatureManager::ResetForTest()
{
    Init();
}
#endif
} // namespace OHOS::Ace
