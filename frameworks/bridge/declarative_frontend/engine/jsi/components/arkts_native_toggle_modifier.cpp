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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_toggle_modifier.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
void SetToggleSelectedColor(NodeHandle node, uint32_t selectedColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSelectedColor(frameNode, Color(selectedColor));
}

void ResetToggleSelectedColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> selectedColor;
    ToggleModelNG::SetSelectedColor(frameNode, selectedColor);
}

void SetToggleSwitchPointColor(NodeHandle node, uint32_t switchPointColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSwitchPointColor(frameNode, Color(switchPointColor));
}

void ResetToggleSwitchPointColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwitchTheme>();
    Color color;
    if (theme) {
        color = theme->GetPointColor();
    }
    ToggleModelNG::SetSwitchPointColor(frameNode, Color(color));
}

ArkUIToggleModifierAPI GetToggleModifier()
{
    static const ArkUIToggleModifierAPI modifier = {
        SetToggleSelectedColor,
        ResetToggleSelectedColor,
        SetToggleSwitchPointColor,
        ResetToggleSwitchPointColor,
    };

    return modifier;
}
} // namespace OHOS::Ace::NG