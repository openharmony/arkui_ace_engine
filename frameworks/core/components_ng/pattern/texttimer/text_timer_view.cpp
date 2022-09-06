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

#include "core/components_ng/pattern/texttimer/text_timer_view.h"

#include <cstddef>

#include "base/geometry/dimension.h"
#include "core/common/frontend.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
RefPtr<TextTimerController> TextTimerView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = (stack ? stack->ClaimNodeId() : 0);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTTIMER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextTimerPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetChildren().empty()) {
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(textNode, nullptr);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textLayoutProperty, nullptr);
        textLayoutProperty->UpdateContent(std::string(""));
        frameNode->AddChild(textNode);
    } else {
        auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
        ACE_DCHECK(textChild);
        auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
        ACE_DCHECK(textLayoutProperty);
        textLayoutProperty->UpdateContent(std::string(""));
    }
    stack->Push(frameNode);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    return pattern ? pattern->GetTextTimerController() : nullptr;
}

void TextTimerView::SetFormat(const std::string& format)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, Format, format);
}

void TextTimerView::SetTextColor(const Color& textColor)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(textColor);
}

void TextTimerView::SetFontSize(const Dimension& fontSize)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateFontSize(fontSize);
}

void TextTimerView::SetFontWeight(const FontWeight& fontWeight)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateFontWeight(fontWeight);
}

void TextTimerView::SetFontFamily(const std::vector<std::string>& fontFamilies)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateFontFamily(fontFamilies);
}

void TextTimerView::SetItalicFontStyle(const Ace::FontStyle& fontStyle)
{
    auto frameNode = ViewStackProcessor ::GetInstance()->GetMainFrameNode();
    if (frameNode->GetChildren().empty()) {
        return;
    }
    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    ACE_DCHECK(textChild);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    ACE_DCHECK(textLayoutProperty);
    textLayoutProperty->UpdateItalicFontStyle(fontStyle);
}

void TextTimerView::SetIsCountDown(bool isCountDown)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, IsCountDown, isCountDown);
}

void TextTimerView::SetInputCount(const double& count)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, InputCount, count);
}

void TextTimerView::SetOnTimer(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextTimerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTimer(std::move(onChange));
}
} // namespace OHOS::Ace::NG
