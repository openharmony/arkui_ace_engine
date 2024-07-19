/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_RESOURCE_CONFIGURATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_RESOURCE_RESOURCE_CONFIGURATION_H

namespace OHOS::Ace {
struct ConfigurationChange {
    bool colorModeUpdate = false;
    bool languageUpdate = false;
    bool directionUpdate = false;
    bool dpiUpdate = false;
    bool fontUpdate = false;
    bool iconUpdate = false;
    bool skinUpdate = false;
    bool fontScaleUpdate = false;
    bool fontWeightScaleUpdate = false;

    bool IsNeedUpdate() const
    {
        return colorModeUpdate || languageUpdate || directionUpdate || dpiUpdate || fontUpdate || iconUpdate ||
               skinUpdate || fontScaleUpdate || fontWeightScaleUpdate;
    }

    void MergeConfig(const ConfigurationChange& config)
    {
        colorModeUpdate |= config.colorModeUpdate;
        languageUpdate |= config.languageUpdate;
        directionUpdate |= config.directionUpdate;
        dpiUpdate |= config.dpiUpdate;
        fontUpdate |= config.fontUpdate;
        iconUpdate |= config.iconUpdate;
        skinUpdate |= config.skinUpdate;
        fontScaleUpdate |= config.fontScaleUpdate;
        fontWeightScaleUpdate |= config.fontWeightScaleUpdate;
    }
};
} // namespace OHOS::Ace

#endif
