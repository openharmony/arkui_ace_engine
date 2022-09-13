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

#include "core/components_ng/pattern/text_clock/text_clock_view.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
RefPtr<TextClockController> TextClockView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTCLOCK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextClockPattern>(); });
    stack->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    return pattern ? pattern->GetTextClockController() : nullptr;
}

void TextClockView::SetFormat(const std::string& format)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, Format, format);
}

void TextClockView::SetHoursWest(const int32_t& hoursWest)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, HoursWest, hoursWest);
}

void TextClockView::SetOnDateChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDateChange(std::move(onChange));
}
} // namespace OHOS::Ace::NG
