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
#include "core/interfaces/native/node/node_arc_list_modifier.h"

#include "core/common/dynamic_module_helper.h"
#if !defined(CROSS_PLATFORM)
#include "core/components_ng/pattern/arc_list/bridge/arc_list_dynamic_modifier.h"
#endif

namespace OHOS::Ace::NG {
namespace NodeModifier {

// Cross builds: ArcList lives in a split SO, so fetch the table via dlopen.
// Non-cross builds: the bridge (arc_list_dynamic_modifier.cpp) is compiled into
// the main SO, so call it directly — no dlopen. GetArcListCustomModifier has the
// same name as the bridge's, so it is only defined here for cross; in non-cross
// the bridge's definition satisfies the declaration in node_arc_list_modifier.h.
#if defined(CROSS_PLATFORM)
const ArkUIArcListCustomModifier* GetArcListCustomModifier()
{
    static const ArkUIArcListCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ARKUI_CAPI_UNITTEST
        return nullptr;
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ArcList");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            static_cast<const ArkUIArcListCustomModifier*>(module->GetCustomModifier());
#endif
    }
    return cachedModifier;
}
#endif

const ArkUIArcListModifier* GetArcListModifier()
{
#if defined(CROSS_PLATFORM)
    static const ArkUIArcListModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ARKUI_CAPI_UNITTEST
        return nullptr;
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ArcList");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            static_cast<const ArkUIArcListModifier*>(module->GetDynamicModifier());
#endif
    }
    return cachedModifier;
#else
    return GetArcListDynamicModifier();
#endif
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
