/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scroll/scroll_model_static.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
 
namespace OHOS::Ace::NG {
 
RefPtr<FrameNode> ScrollModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, nodeId, AceType::MakeRefPtr<ScrollPattern>());
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    pattern->SetAlwaysEnabled(true);
    auto positionController = AceType::MakeRefPtr<NG::ScrollableController>();
    pattern->SetPositionController(positionController);
    pattern->TriggerModifyDone();
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
    positionController->SetScrollPattern(pattern);
    return frameNode;
}

RefPtr<ScrollControllerBase> ScrollModelStatic::GetOrCreateController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    if (!pattern->GetScrollPositionController()) {
        auto controller = AceType::MakeRefPtr<NG::ScrollableController>();
        pattern->SetPositionController(controller);
    }
    return pattern->GetScrollPositionController();
}

RefPtr<ScrollProxy> ScrollModelStatic::GetOrCreateScrollBarProxy(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto scrollBarProxy = pattern->GetScrollBarProxy();
    if (scrollBarProxy == nullptr) {
        scrollBarProxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
        pattern->SetScrollBarProxy(scrollBarProxy);
    }
    return scrollBarProxy;
}

void ScrollModelStatic::SetAxis(FrameNode* frameNode, const std::optional<Axis>& axisI)
{
    auto axis = axisI.value_or(Axis::VERTICAL);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, Axis, axis, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetAxis(axis);
}

void ScrollModelStatic::SetOnScroll(FrameNode* frameNode, NG::ScrollEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(event));
}

void ScrollModelStatic::SetOnWillScroll(FrameNode* frameNode, ScrollEventWithReturn&& event)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillScrollEvent(std::move(event));
}

void ScrollModelStatic::SetOnDidScroll(FrameNode* frameNode, ScrollEventWithState&& event)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidScrollEvent(std::move(event));
}

void ScrollModelStatic::SetOnScrollEdge(FrameNode* frameNode, NG::ScrollEdgeEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollEdge(std::move(event));
}

void ScrollModelStatic::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(event));
}

void ScrollModelStatic::SetOnScrollEnd(FrameNode* frameNode, ScrollEndEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollEnd(std::move(event));
}

void ScrollModelStatic::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(event));
}

void ScrollModelStatic::SetScrollBar(FrameNode* frameNode, std::optional<DisplayMode> barState)
{
    if (barState.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, barState.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, frameNode);
    }
}

void ScrollModelStatic::SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, frameNode);
    }
}

void ScrollModelStatic::SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& dimension)
{
    if (dimension) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth,  dimension.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, frameNode);
    }
}

void ScrollModelStatic::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(event));
}

void ScrollModelStatic::SetNestedScroll(FrameNode* frameNode,
    const std::optional<NestedScrollMode>& forward, const std::optional<NestedScrollMode>& backward)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    NestedScrollOptions nestedOpt = {
        .forward = forward.value_or(NestedScrollMode::SELF_ONLY),
        .backward = backward.value_or(NestedScrollMode::SELF_ONLY)};
    pattern->SetNestedScroll(nestedOpt);
}

void ScrollModelStatic::SetScrollEnabled(FrameNode* frameNode, const std::optional<bool> scrollEnabled)
{
    if (scrollEnabled) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollEnabled,  scrollEnabled.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollEnabled, frameNode);
    }
}

void ScrollModelStatic::SetFriction(FrameNode* frameNode, const std::optional<float> friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction.value_or(-1.0f));
}

void ScrollModelStatic::SetScrollSnap(
    FrameNode* frameNode,
    std::optional<ScrollSnapAlign> scrollSnapAlignI,
    const std::optional<Dimension>& intervalSize,
    const std::vector<Dimension>& snapPaginations,
    const std::optional<bool>& enableSnapToStart,
    const std::optional<bool>& enableSnapToEnd)
{
    auto scrollSnapAlign = scrollSnapAlignI.value_or(ScrollSnapAlign::NONE);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetScrollSnapAlign() != scrollSnapAlign) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, scrollSnapAlign, frameNode);
        pattern->SetScrollSnapUpdate(true);
    }
    if (scrollSnapAlign != ScrollSnapAlign::NONE) {
        pattern->SetIntervalSize(intervalSize.value_or(Dimension()));
    }
    pattern->SetSnapPaginations(snapPaginations);
    pattern->SetEnableSnapToSide(std::make_pair(enableSnapToStart.value_or(true), enableSnapToEnd.value_or(true)));
}

void ScrollModelStatic::SetEnablePaging(FrameNode* frameNode, const std::optional<bool> enablePaging)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    if (!enablePaging.value_or(false)) {
        pattern->SetEnablePaging(ScrollPagingStatus::INVALID);
        return;
    }
    pattern->SetEnablePaging(ScrollPagingStatus::VALID);
    pattern->SetScrollSnapUpdate(true);
}

void ScrollModelStatic::SetInitialOffset(FrameNode* frameNode, const std::optional<OffsetT<CalcDimension>>& offset)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetInitialOffset(offset.value_or(OffsetT(CalcDimension(), CalcDimension())));
}

void ScrollModelStatic::SetEdgeEffect(FrameNode* frameNode, const std::optional<EdgeEffect>& edgeEffect,
    const std::optional<bool>& alwaysEnabled, EffectEdge edge)
{
    ScrollableModelStatic::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled, edge);
}
} // namespace OHOS::Ace::NG
 