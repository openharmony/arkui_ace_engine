/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "node_toggle_modifier.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
void SetToggleSelectedColor(ArkUINodeHandle node, uint32_t selectedColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSelectedColor(frameNode, Color(selectedColor));
}

void ResetToggleSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> selectedColor;
    ToggleModelNG::SetSelectedColor(frameNode, selectedColor);
}

void SetToggleSwitchPointColor(ArkUINodeHandle node, uint32_t switchPointColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSwitchPointColor(frameNode, Color(switchPointColor));
}

void ResetToggleSwitchPointColor(ArkUINodeHandle node)
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
} // namespace

namespace NodeModifier {
const ArkUIToggleModifier* GetToggleModifier()
{
    static const ArkUIToggleModifier modifier = {
        SetToggleSelectedColor,
        ResetToggleSelectedColor,
        SetToggleSwitchPointColor,
        ResetToggleSwitchPointColor,
    };

    return &modifier;
}

void SetOnToggleChange(ArkUINodeHandle node, ArkUI_Int32 eventId, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [node, eventId, extraParam](const bool isOn) {
        ArkUINodeEvent event;
        event.kind = ON_TOGGLE_CHANGE;
        event.eventId = eventId;
        event.extraParam= extraParam;
        event.componentAsyncEvent.data[0].u32 = isOn;
        SendArkUIAsyncEvent(&event);
    };
    ToggleModelNG::OnChange(frameNode, std::move(onChange));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
