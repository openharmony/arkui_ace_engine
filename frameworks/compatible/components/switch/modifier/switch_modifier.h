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

#ifndef FRAMEWORKS_COMPATIBLE_COMPONENTS_SWITCH_MODIFIER_SWITCH_MODIFIER_H
#define FRAMEWORKS_COMPATIBLE_COMPONENTS_SWITCH_MODIFIER_SWITCH_MODIFIER_H

#include "compatible/components/switch/dom_switch.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace OHOS::Ace {

namespace Framework {
class DOMNode;
} // namespace Framework

struct ArkUISwitchModifierCompatible {
    RefPtr<RenderNode> (*createRenderNode)();
};
namespace SwitchModifier {

const ArkUISwitchModifierCompatible* GetSwitchModifierCompatible();
} // namespace SwitchModifier

} // namespace OHOS::Ace

#ifdef __cplusplus
};
#endif

#endif // FRAMEWORKS_COMPATIBLE_COMPONENTS_SWITCH_MODIFIER_SWITCH_MODIFIER_H