/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_RESOURCE_PLUGIN_REQUEST_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_RESOURCE_PLUGIN_REQUEST_DATA_H

#include <sstream>
#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
struct RequestPluginInfo {
    int32_t id = 0;
    std::string pluginName;
    std::string bundleName;
    std::string abilityName;
    std::string moduleName;
    std::string source;
    std::string moduleResPath;
    int32_t dimension = -1;
    bool allowUpdate = true;
    Dimension width;
    Dimension height;
    uint64_t index = GetNanoseconds();

    std::string ToString() const
    {
        std::stringstream paramStream;
        paramStream << bundleName << abilityName << moduleName << pluginName << source << dimension << index;
        return paramStream.str();
    }

    bool operator==(const RequestPluginInfo& pluginInfo) const
    {
        return id == pluginInfo.id && pluginName == pluginInfo.pluginName && bundleName == pluginInfo.bundleName &&
               abilityName == pluginInfo.abilityName && moduleName == pluginInfo.moduleName &&
               source == pluginInfo.source && moduleResPath == pluginInfo.moduleResPath &&
               dimension == pluginInfo.dimension && allowUpdate == pluginInfo.allowUpdate &&
               width == pluginInfo.width && height == pluginInfo.height && index == pluginInfo.index;
    }
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_RESOURCE_PLUGIN_REQUEST_DATA_H
