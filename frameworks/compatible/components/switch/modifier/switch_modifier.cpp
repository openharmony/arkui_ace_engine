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

#include "compatible/components/switch/modifier/switch_modifier.h"
#include "compatible/components/switch/rosen_render_switch.h"

namespace OHOS::Ace::SwitchModifier {

RefPtr<RenderNode> CreateSwitchRenderNode()
{
    return RenderSwitch::Create();
}

const ArkUISwitchModifierCompatible* GetSwitchModifierCompatible()
{
    static const ArkUISwitchModifierCompatible impl = {
        .createRenderNode = CreateSwitchRenderNode,
    };
    return &impl;
}

} // namespace OHOS::Ace::SwitchModifier