/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scroll/scroll_model_ng.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
}

void ScrollModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SCROLL_ETS_TAG, nodeId);
    auto frameNode = CreateScroll(nodeId);
    stack->Push(frameNode);
}

RefPtr<FrameNode> ScrollModelNG::CreateScroll(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    pattern->SetAlwaysEnabled(true);
    auto positionController = AceType::MakeRefPtr<NG::ScrollableController>();
    pattern->SetPositionController(positionController);
    positionController->SetScrollPattern(pattern);
    return frameNode;
}

RefPtr<ScrollControllerBase> ScrollModelNG::GetOrCreateController()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    if (!pattern->GetScrollPositionController()) {
        auto controller = AceType::MakeRefPtr<NG::ScrollableController>();
        pattern->SetPositionController(controller);
    }
    return pattern->GetScrollPositionController();
}

void ScrollModelNG::SetScrollController(
    FrameNode* frameNode, const RefPtr<ScrollControllerBase>& scroller, const RefPtr<ScrollProxy>& proxy)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    auto scrollController = AceType::DynamicCast<NG::ScrollableController>(scroller);
    CHECK_NULL_VOID(scrollController);
    pattern->SetPositionController(scrollController);
    scrollController->SetScrollPattern(pattern);
    auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(proxy);
    CHECK_NULL_VOID(scrollBarProxy);
    pattern->SetScrollBarProxy(scrollBarProxy);
}

void ScrollModelNG::SetOnScroll(FrameNode* frameNode, NG::ScrollEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(event));
}

RefPtr<ScrollProxy> ScrollModelNG::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<ScrollBarProxy>();
}

void ScrollModelNG::SetAxis(Axis axis)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollLayoutProperty, Axis, axis);
}

void ScrollModelNG::SetOnScrollBegin(OnScrollBeginEvent&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollBegin(std::move(event));
}

void ScrollModelNG::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(event));
}

void ScrollModelNG::SetOnScroll(NG::ScrollEvent&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnScroll(AceType::RawPtr(frameNode), std::move(event));
}

void ScrollModelNG::SetOnScrollEdge(NG::ScrollEdgeEvent&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollEdge(std::move(event));
}

void ScrollModelNG::SetOnScrollEnd(NG::ScrollEndEvent&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollEnd(std::move(event));
}

void ScrollModelNG::SetOnScrollStart(OnScrollStartEvent&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(event));
}

void ScrollModelNG::SetOnScrollStop(OnScrollStopEvent&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(event));
}

void ScrollModelNG::SetOnReachStart(OnReachEvent&& onReachStart)
{
    ScrollableModelNG::SetOnReachStart(std::move(onReachStart));
}

void ScrollModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    ScrollableModelNG::SetOnReachEnd(std::move(onReachEnd));
}

void ScrollModelNG::SetScrollBarProxy(const RefPtr<ScrollProxy>& proxy)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(proxy);
    CHECK_NULL_VOID(scrollBarProxy);
    pattern->SetScrollBarProxy(scrollBarProxy);
}

void ScrollModelNG::InitScrollBar(const RefPtr<ScrollBarTheme>& theme, const std::pair<bool, Color>& color,
    const std::pair<bool, Dimension>& width, EdgeEffect effect)
{}

void ScrollModelNG::SetDisplayMode(int value)
{
    auto displayMode = static_cast<DisplayMode>(value);
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, displayMode);
}

void ScrollModelNG::SetScrollBar(FrameNode* frameNode, DisplayMode barState)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, barState, frameNode);
}

void ScrollModelNG::SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void ScrollModelNG::SetFriction(FrameNode* frameNode, double friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction);
}

void ScrollModelNG::SetScrollSnap(FrameNode* frameNode, ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
    const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetScrollSnapAlign() != scrollSnapAlign) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, scrollSnapAlign, frameNode);
        pattern->SetScrollSnapUpdate(true);
    }
    pattern->SetIntervalSize(intervalSize);
    pattern->SetSnapPaginations(snapPaginations);
    pattern->SetEnableSnapToSide(enableSnapToSide);
    pattern->SetEnablePaging(ScrollPagingStatus::INVALID);
}

void ScrollModelNG::SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollEnabled, scrollEnabled, frameNode);
}

void ScrollModelNG::SetScrollBarWidth(const Dimension& dimension)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, dimension);
}

void ScrollModelNG::SetScrollBarColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, color);
}

void ScrollModelNG::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled)
{
    ScrollableModelNG::SetEdgeEffect(edgeEffect, alwaysEnabled);
}

void ScrollModelNG::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void ScrollModelNG::SetScrollEnabled(bool scrollEnabled)
{
    ACE_UPDATE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollEnabled, scrollEnabled);
}

void ScrollModelNG::SetFriction(double friction)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction);
}

void ScrollModelNG::SetScrollSnap(ScrollSnapAlign scrollSnapAlign, const Dimension& intervalSize,
    const std::vector<Dimension>& snapPaginations, const std::pair<bool, bool>& enableSnapToSide)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetScrollSnapAlign() != scrollSnapAlign) {
        ACE_UPDATE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, scrollSnapAlign);
        pattern->SetScrollSnapUpdate(true);
    }
    pattern->SetIntervalSize(intervalSize);
    pattern->SetSnapPaginations(snapPaginations);
    pattern->SetEnableSnapToSide(enableSnapToSide);
    pattern->SetEnablePaging(ScrollPagingStatus::INVALID);
}

void ScrollModelNG::SetAxis(FrameNode* frameNode, Axis axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, Axis, axis, frameNode);
}

void ScrollModelNG::SetScrollBarColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, color, frameNode);
}

void ScrollModelNG::SetScrollBarWidth(FrameNode* frameNode, const Dimension& dimension)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, dimension, frameNode);
}

void ScrollModelNG::SetEdgeEffect(FrameNode* frameNode, const EdgeEffect& edgeEffect, bool alwaysEnabled)
{
    ScrollableModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled);
}

void ScrollModelNG::SetEnablePaging(bool enablePaging)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->GetEnablePaging() != ScrollPagingStatus::INVALID);
    if (!enablePaging) {
        pattern->SetEnablePaging(ScrollPagingStatus::NONE);
        if (pattern->GetScrollSnapAlign() != ScrollSnapAlign::NONE) {
            ACE_UPDATE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, ScrollSnapAlign::NONE);
        }
        return;
    }
    pattern->SetEnablePaging(ScrollPagingStatus::VALID);
    // Reuse scrollSnap, and set intervalSize after layout.
    if (pattern->GetScrollSnapAlign() != ScrollSnapAlign::START) {
        ACE_UPDATE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollSnapAlign, ScrollSnapAlign::START);
    }
    pattern->SetScrollSnapUpdate(true);
}
} // namespace OHOS::Ace::NG
