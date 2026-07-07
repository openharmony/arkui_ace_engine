/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_BRIDGE_TABS_CONTROLLER_MODIFIER_API_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_BRIDGE_TABS_CONTROLLER_MODIFIER_API_H

#include <cstdint>
#include <functional>
#include <string>
#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG::NodeModifier {
struct ArkUITabsControllerModifier {
    RefPtr<AceType> (*createController)();
    void (*destroyController)(const RefPtr<AceType>& controller);
    void (*changeIndex)(const RefPtr<AceType>& controller, int32_t index);
    void (*preloadItems)(const RefPtr<AceType>& controller, const int32_t* indices, int32_t count);
    void (*setPreloadFinishCallback)(const RefPtr<AceType>& controller,
                                     const std::function<void(const int32_t, const std::string)>& callback);
    void (*setTabBarTranslate)(const RefPtr<AceType>& controller, double x, double y, double z,
                               int32_t unitX, int32_t unitY, int32_t unitZ);
    void (*setTabBarOpacity)(const RefPtr<AceType>& controller, double opacity);
    void (*startShowTabBar)(const RefPtr<AceType>& controller, int32_t delay);
    void (*cancelShowTabBar)(const RefPtr<AceType>& controller);
    void (*updateTabBarHiddenOffset)(const RefPtr<AceType>& controller, double offset);
    void (*setOnChangeImpl)(const RefPtr<AceType>& controller,
                            const std::function<void(int32_t)>& callback);
};
extern const ArkUITabsControllerModifier* GetTabsControllerModifier();
}

#endif
