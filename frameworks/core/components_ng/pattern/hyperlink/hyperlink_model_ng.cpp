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

#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"

#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_pattern.h"

namespace OHOS::Ace::NG {
void HyperlinkModelNG::Create(const std::string& address, const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::HYPERLINK_ETS_TAG, nodeId);
    auto hyperlinkNode = FrameNode::GetOrCreateFrameNode(
        V2::HYPERLINK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<HyperlinkPattern>(); });

    stack->Push(hyperlinkNode);
    SetTextStyle(hyperlinkNode, content, address);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto draggable = pipeline->GetDraggable<HyperlinkTheme>();
    SetDraggable(draggable);
}

void HyperlinkModelNG::SetColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(HyperlinkLayoutProperty, TextColor, value);
    ACE_UPDATE_LAYOUT_PROPERTY(HyperlinkLayoutProperty, Color, value);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
}

void HyperlinkModelNG::SetTextStyle(
    const RefPtr<FrameNode>& hyperlinkNode, const std::string& content, const std::string& address)
{
    CHECK_NULL_VOID(hyperlinkNode);
    auto textLayoutProperty = hyperlinkNode->GetLayoutProperty<HyperlinkLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto textStyle = PipelineBase::GetCurrentContext()->GetTheme<TextTheme>()->GetTextStyle();
    textLayoutProperty->UpdateContent(content.empty() ? address : content);
    textLayoutProperty->UpdateAddress(address);
    auto theme = PipelineContext::GetCurrentContext()->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(theme);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateTextColor(theme->GetTextColor());
    textLayoutProperty->UpdateFontWeight(textStyle.GetFontWeight());
    textLayoutProperty->UpdateTextDecoration({theme->GetTextUnSelectedDecoration()});
    textLayoutProperty->UpdateAdaptMinFontSize(10.0_vp);
    textLayoutProperty->UpdateAdaptMaxFontSize(textStyle.GetFontSize());
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    hyperlinkNode->MarkModifyDone();
    hyperlinkNode->MarkDirtyNode();
}

void HyperlinkModelNG::SetDraggable(bool draggable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (draggable && !frameNode->IsDraggable()) {
        auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->InitDragDropEvent();
    }
    frameNode->SetDraggable(draggable);
}

void HyperlinkModelNG::SetColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(HyperlinkLayoutProperty, TextColor, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(HyperlinkLayoutProperty, Color, value, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
}

void HyperlinkModelNG::SetDraggable(FrameNode* frameNode, bool draggable)
{
    CHECK_NULL_VOID(frameNode);
    if (draggable && !frameNode->IsDraggable()) {
        auto gestureHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->InitDragDropEvent();
    }
    frameNode->SetDraggable(draggable);
}

void HyperlinkModelNG::SetResponseRegion(bool isUserSetResponseRegion)
{
    auto textPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->SetIsUserSetResponseRegion(isUserSetResponseRegion);
}

void HyperlinkModelNG::SetResponseRegion(
    FrameNode* frameNode, const std::vector<DimensionRect>& regions, bool isUserSetResponseRegion)
{
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    gesture->SetResponseRegion(regions);
    textPattern->SetIsUserSetResponseRegion(isUserSetResponseRegion);
}
} // namespace OHOS::Ace::NG
