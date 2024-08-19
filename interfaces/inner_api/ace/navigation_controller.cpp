/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "navigation_controller.h"


#include "ace_forward_compatibility.h"
#include "utils.h"

namespace OHOS {
namespace Ace {
using GetNavigationControllerFunc = NavigationController* (*)(UIContent*, const char*);
constexpr char GET_NAVIGATION_CONTROL_FUNC[] = "OHOS_ACE_GetNavigationController";

NavigationController* NavigationController::GetNavigationController(
    UIContent* uiContent, const std::string& navigationId)
{
    LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<GetNavigationControllerFunc>(LOADSYM(handle, GET_NAVIGATION_CONTROL_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return nullptr;
    }

    auto contain = entry(uiContent, navigationId.c_str());
    FREELIB(handle);
    return contain;
}
} // namespace Ace
} // namespace OHOS
