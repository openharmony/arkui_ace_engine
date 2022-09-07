/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/toggle/toggle_view.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void ToggleView::Create(Ace::NG::ToggleType toggleType, bool isOn)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TOGGLE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SwitchPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, ToggleType, toggleType);
    ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
}

void ToggleView::SetSelectedColor(const Color& selectedColor)
{
    ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, selectedColor);
}

void ToggleView::SetSwitchPointColor(const Color& switchPointColor)
{
    ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, SwitchPointColor, switchPointColor);
}
void ToggleView::OnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

} // namespace OHOS::Ace::NG