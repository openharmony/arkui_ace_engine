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

#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_clock/text_clock_layout_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<TextClockController> TextClockModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto textClockNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTCLOCK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextClockPattern>(); });

    auto pattern = textClockNode->GetPattern<TextClockPattern>();
    if (textClockNode->GetChildren().empty()) {
        auto textId = pattern->GetTextId();
        auto textNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, textId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(textNode, nullptr);
        textNode->MarkModifyDone();
        textNode->MountToParent(textClockNode);
    }
    stack->Push(textClockNode);
    return pattern ? pattern->GetTextClockController() : nullptr;
}

void TextClockModelNG::SetFormat(const std::string& format)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, Format, format);
}

void TextClockModelNG::SetHoursWest(const int32_t& hoursWest)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, HoursWest, hoursWest);
}

void TextClockModelNG::SetOnDateChange(std::function<void(const std::string)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextClockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDateChange(std::move(onChange));
}

void TextClockModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontSize, value);
}

void TextClockModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, TextColor, value);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void TextClockModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, ItalicFontStyle, value);
}

void TextClockModelNG::SetFontWeight(FontWeight value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontWeight, value);
}

void TextClockModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextClockLayoutProperty, FontFamily, value);
}
} // namespace OHOS::Ace::NG
