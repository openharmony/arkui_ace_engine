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
#include "core/interfaces/native/node/node_arc_scroll_bar_modifier.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {

// Cross builds: dlopen ArcScrollBar from its split SO. Non-cross builds: the
// bridge (arc_scroll_bar_dynamic_modifier.cpp) is compiled into the main SO, so
// this function is cross-only here; in non-cross the bridge's same-name
// definition satisfies the declaration in node_arc_scroll_bar_modifier.h.
#if defined(CROSS_PLATFORM)
const ArkUIArcScrollBarCustomModifier* GetArcScrollBarCustomModifier()
{
    static const ArkUIArcScrollBarCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ARKUI_CAPI_UNITTEST
        return nullptr;
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("ArcScrollBar");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier =
            static_cast<const ArkUIArcScrollBarCustomModifier*>(module->GetCustomModifier());
#endif
    }
    return cachedModifier;
}
#endif

const ArkUIArcScrollBarModifier* GetArcScrollBarModifier()
{
    static const ArkUIArcScrollBarModifier modifier = {};
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
