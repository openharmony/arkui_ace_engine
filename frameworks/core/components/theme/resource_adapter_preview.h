/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_PREVIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_PREVIEW_H

#include "core/components/theme/resource_adapter.h"

namespace OHOS::Ace {

class ResourceAdapterPreview : public ResourceAdapter {
    DECLARE_ACE_TYPE(ResourceAdapterPreview, ResourceAdapter);

public:
    ResourceAdapterPreview() = default;
    ~ResourceAdapterPreview() override = default;

    void Init(const DeviceResourceInfo& resourceInfo) override;
    void UpdateConfig(const DeviceConfig& config) override;

    RefPtr<ThemeStyle> GetTheme(int32_t themeId) override;

    Color GetColor(uint32_t resId) override;
    Dimension GetDimension(uint32_t resId) override;
    std::string GetString(uint32_t resId) override;
    double GetDouble(uint32_t resId) override;
    int32_t GetInt(uint32_t resId) override;

private:
    bool ReadFileToString(const std::string& filePath, std::string& fileContent);
    bool ConvertColorValToResValueWrapper(const std::string& colorVal, ResValueWrapper& resValWrapper);
    bool ConvertFloatValToResValueWrapper(const std::string& floatVal, ResValueWrapper& resValWrapper);
    bool ConvertThemeValToResValueWrapper(const std::string& themeVal, ResValueWrapper& resValWrapper);
    bool ConvertStringValToResValueWrapper(const std::string& StringVal, ResValueWrapper& resValWrapper);
    bool ParseFloatJsonFile(const std::string& jsonFile);
    bool ParseStringJsonFile(const std::string& jsonFile);
    bool ParseColorJsonFile(const std::string& jsonFile);
    bool ParsePatternJsonFile(const std::string& jsonFile);
    bool ParseThemeJsonFile(const std::string& jsonFile);
    bool ParseRecordJsonFile(const std::string& jsonFile);
    bool LoadSystemResources(const std::string& sysResDir, const int32_t& themeId, const ColorMode& colorMode);
    bool PostprocessSystemResources();

private:
    std::unordered_map<std::string, ResValueWrapper> sysResFloat_;
    std::unordered_map<std::string, ResValueWrapper> sysResString_;
    std::unordered_map<std::string, ResValueWrapper> sysResColor_;
    std::unordered_map<std::string, ResValueWrapper> sysResPattern_;
    std::unordered_map<std::string, ResValueWrapper> sysResTheme_;
    // record for mapping relationship between system resources id and name.(<resId, <resName, resType>>)
    std::unordered_map<uint32_t, std::pair<std::string, std::string>> sysResRecord_;

    ACE_DISALLOW_COPY_AND_MOVE(ResourceAdapterPreview);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_PREVIEW_H
