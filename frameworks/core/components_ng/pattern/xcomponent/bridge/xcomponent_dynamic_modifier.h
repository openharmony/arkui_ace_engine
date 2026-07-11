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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_BRIDGE_XCOMPONENT_DYNAMIC_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_BRIDGE_XCOMPONENT_DYNAMIC_MODIFIER_H

#include "core/components_ng/base/view_abstract_model.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/node_xcomponent_modifier.h"

namespace OHOS::Ace::NG {
struct XComponentOnClickEvent {
    GestureEventFunc onTap;
    ClickEventFunc onClick;
    Dimension distanceThreshold;
};

struct XComponentOnTouchEvent {
    TouchEventFunc onTouch;
};
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::NodeModifier {
    const ArkUIXComponentModifier* GetXComponentDynamicModifier();
    const CJUIXComponentModifier* GetCJUIXComponentDynamicModifier();
    const ArkUIXComponentCustomModifier* GetXComponentDynamicCustomModifier();
} // namespace OHOS::Ace::NG::NodeModifier
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_BRIDGE_XCOMPONENT_DYNAMIC_MODIFIER_H
