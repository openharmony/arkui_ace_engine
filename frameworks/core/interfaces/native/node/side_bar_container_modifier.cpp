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
#include "core/interfaces/native/node/side_bar_container_modifier.h"

#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"
namespace OHOS::Ace::NG {

namespace NodeModifier {
const ArkUISideBarContainerModifier* GetSideBarContainerModifier()
{
    static const ArkUISideBarContainerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Sidebar");
        if (module == nullptr) {
            LOGF("Can't find sidebar dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const ArkUISideBarContainerModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUISideBarContainerModifier* GetCJUISideBarContainerModifier()
{
    static const CJUISideBarContainerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Sidebar");
        if (module == nullptr) {
            LOGF("Can't find sidebar dynamic module");
            abort();
        }
        cachedModifier = reinterpret_cast<const CJUISideBarContainerModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
