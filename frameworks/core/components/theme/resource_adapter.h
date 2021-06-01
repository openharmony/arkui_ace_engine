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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_H

#include "base/utils/device_config.h"
#include "core/components/theme/theme_style.h"

namespace OHOS::Ace {

class ResourceAdapter : public virtual AceType {
    DECLARE_ACE_TYPE(ResourceAdapter, AceType);

public:
    ResourceAdapter() = default;
    ~ResourceAdapter() override = default;

    static RefPtr<ResourceAdapter> Create();

    virtual void Init(const DeviceResourceInfo& resourceInfo) {};
    virtual void UpdateConfig(const DeviceConfig& config) {};

    virtual RefPtr<ThemeStyle> GetTheme(int32_t themeId) = 0;

    virtual Color GetColor(uint32_t resId) = 0;
    virtual Dimension GetDimension(uint32_t resId) = 0;
    virtual std::string GetString(uint32_t resId) = 0;
    virtual double GetDouble(uint32_t resId) = 0;
    virtual int32_t GetInt(uint32_t resId) = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_RESOURCE_ADAPTER_H
