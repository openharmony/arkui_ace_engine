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
#include "core/interfaces/native/node/node_arc_list_item_modifier.h"

#include "core/common/dynamic_module_helper.h"
#if !defined(CROSS_PLATFORM)
#include "core/components_ng/pattern/arc_list/bridge/arc_list_dynamic_modifier.h"
#endif

namespace OHOS::Ace::NG {
namespace NodeModifier {

// See node_arc_list_modifier.cpp: cross = dlopen from split SO; non-cross = call
// the in-process bridge directly. GetArcListItemCustomModifier is cross-only
// (same name as the bridge's); non-cross resolves to the bridge's definition.
#if defined(CROSS_PLATFORM)
const ArkUIArcListItemCustomModifier* GetArcListItemCustomModifier()
{
    static const ArkUIArcListItemCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ARKUI_CAPI_UNITTEST
        return nullptr;
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ArcList");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            static_cast<const ArkUIArcListItemCustomModifier*>(module->GetCustomModifier("item"));
#endif
    }
    return cachedModifier;
}
#endif

const ArkUIArcListItemModifier* GetArcListItemModifier()
{
#if defined(CROSS_PLATFORM)
    static const ArkUIArcListItemModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ARKUI_CAPI_UNITTEST
        return nullptr;
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ArcList");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            static_cast<const ArkUIArcListItemModifier*>(module->GetCustomModifier("item_dynamic"));
#endif
    }
    return cachedModifier;
#else
    return GetArcListItemDynamicModifier();
#endif
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
