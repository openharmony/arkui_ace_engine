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
#include "core/components_ng/pattern/button/toggle_button_view.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"

namespace OHOS::Ace::NG {
void ToggleButtonView::Create(const std::string& tagName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(tagName, nodeId, []() { return AceType::MakeRefPtr<ToggleButtonPattern>(); });
    stack->Push(frameNode);
}

void ToggleButtonView::SetSelectedColor(const Color& selectedColor)
{
    ACE_UPDATE_PAINT_PROPERTY(ToggleButtonPaintProperty, SelectedColor, selectedColor);
}

void ToggleButtonView::SetIsOn(bool isOn)
{
    ACE_UPDATE_PAINT_PROPERTY(ToggleButtonPaintProperty, IsOn, isOn);
}

void ToggleButtonView::SetBackgroundColor(const Color& backgroundColor)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto buttonPattern = stack->GetMainFrameNodePattern<ToggleButtonPattern>();
    if (buttonPattern) {
        ACE_UPDATE_PAINT_PROPERTY(ToggleButtonPaintProperty, BackgroundColor, backgroundColor);
        return;
    }
    NG::ViewAbstract::SetBackgroundColor(backgroundColor);
}

} // namespace OHOS::Ace::NG