/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <unordered_map>

#include "base/utils/feature_manager.h"

namespace OHOS::Ace {
namespace {
struct MockFeatureParamEntry {
    int32_t code = FeatureManager::SUCCESS;
    std::string value;
};

std::unordered_map<std::string, MockFeatureParamEntry>& GetMockFeatureParamMap()
{
    static std::unordered_map<std::string, MockFeatureParamEntry> map;
    return map;
}
} // namespace

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
    auto& mockMap = GetMockFeatureParamMap();
    auto it = mockMap.find(key);
    if (it != mockMap.end()) {
        value = it->second.value;
        return it->second.code;
    }
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

void FeatureManager::SetFeatureParamForTest(const std::string& key, const std::string& value, int32_t code)
{
    GetMockFeatureParamMap()[key] = { code, value };
}

void FeatureManager::ClearFeatureParamForTest()
{
    GetMockFeatureParamMap().clear();
}
#endif
} // namespace OHOS::Ace
