/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/utils/multi_thread.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
namespace {
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
}

void ScrollModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SCROLL_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    stack->Push(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetAlwaysEnabled(true);
    auto positionController = AceType::MakeRefPtr<NG::ScrollableController>();
    pattern->SetPositionController(positionController);
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
    positionController->SetScrollPattern(pattern);
}

RefPtr<FrameNode> ScrollModelNG::CreateFrameNode(int32_t nodeId)
{
    // call CreateFrameNodeMultiThread by multi thread
    THREAD_SAFE_NODE_SCOPE_CHECK(CreateFrameNode, nodeId);
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

void ScrollModelNG::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(event));
}

void ScrollModelNG::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(event));
}

void ScrollModelNG::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(event));
}

RefPtr<ScrollProxy> ScrollModelNG::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<ScrollBarProxy>();
}

int32_t ScrollModelNG::GetAxis(FrameNode *frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    if (layoutProperty->GetAxis() == Axis::FREE) {
        return ArkUI_ScrollDirection::ARKUI_SCROLL_DIRECTION_FREE;
    }
    int32_t value = 0;
    if (layoutProperty->GetAxis()) {
        value = static_cast<int32_t>(layoutProperty->GetAxisValue());
    }
    return value;
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
    SetOnScroll(frameNode, std::move(event));
}

void ScrollModelNG::SetOnWillScroll(NG::ScrollEventWithReturn&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillScrollEvent(std::move(event));
}

void ScrollModelNG::SetOnWillScroll(FrameNode* frameNode, ScrollEventWithReturn&& event)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillScrollEvent(std::move(event));
}

void ScrollModelNG::SetOnDidScroll(NG::ScrollEventWithState&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidScrollEvent(std::move(event));
}

void ScrollModelNG::SetOnDidScroll(FrameNode* frameNode, ScrollEventWithState&& event)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidScrollEvent(std::move(event));
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

void ScrollModelNG::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    ScrollableModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}

void ScrollModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    ScrollableModelNG::SetOnReachEnd(std::move(onReachEnd));
}

void ScrollModelNG::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    ScrollableModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
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

int32_t ScrollModelNG::GetEnablePaging(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, 0.0f);
    return static_cast<int32_t>(pattern->GetEnablePaging());
}

void ScrollModelNG::SetEnablePaging(bool enablePaging)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    if (!enablePaging) {
        pattern->SetEnablePaging(ScrollPagingStatus::INVALID);
        return;
    }
    pattern->SetEnablePaging(ScrollPagingStatus::VALID);
    pattern->SetScrollSnapUpdate(true);
}

int32_t ScrollModelNG::GetScrollBar(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(
        frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetScrollBarMode().value_or(DisplayMode::AUTO));
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

float ScrollModelNG::GetFriction(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, 0.0f);
    return pattern->GetFriction();
}

void ScrollModelNG::SetFriction(FrameNode* frameNode, double friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction);
}

void ScrollModelNG::CreateWithResourceObjFriction(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ScrollFriction");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        double friction = -1.0;
        ResourceParseUtils::ParseResDouble(resObj, friction);
        pattern->SetFriction(friction);
    };
    pattern->AddResObj("ScrollFriction", resObj, std::move(updateFunc));
}

ScrollSnapOptions ScrollModelNG::GetScrollSnap(FrameNode* frameNode)
{
    ScrollSnapOptions snapOptions;
    CHECK_NULL_RETURN(frameNode, snapOptions);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, snapOptions);
    snapOptions.enableSnapToStart = pattern->GetEnableSnapToSide().first;
    snapOptions.enableSnapToEnd = pattern->GetEnableSnapToSide().second;
    snapOptions.snapAlign = static_cast<int32_t>(pattern->GetScrollSnapAlign());
    snapOptions.paginationParams = pattern->GetSnapPaginations();
    return snapOptions;
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
    if (scrollSnapAlign != ScrollSnapAlign::NONE) {
        pattern->SetIntervalSize(intervalSize);
    }
    pattern->SetSnapPaginations(snapPaginations);
    pattern->SetEnableSnapToSide(enableSnapToSide);
}

int32_t ScrollModelNG::GetScrollEnabled(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    int32_t value = true;
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    if (layoutProperty->GetScrollEnabled()) {
        value = layoutProperty->GetScrollEnabledValue();
    }
    return value;
}

void ScrollModelNG::SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, ScrollEnabled, scrollEnabled, frameNode);
}

float ScrollModelNG::GetScrollBarWidth(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto value = frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetBarWidth();
    return value.ConvertToVp();
}

void ScrollModelNG::SetScrollBarWidth(const Dimension& dimension)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, dimension);
}

uint32_t ScrollModelNG::GetScrollBarColor(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto value = frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetBarColor();
    return value.GetValue();
}

void ScrollModelNG::SetScrollBarColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetScrollBarColor(frameNode, color);
}

void ScrollModelNG::ResetScrollBarColor()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ResetScrollBarColor(frameNode);
}

int32_t ScrollModelNG::GetEdgeEffect(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return ScrollableModelNG::GetEdgeEffect(frameNode);
}

int32_t ScrollModelNG::GetEdgeEffectAlways(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return ScrollableModelNG::GetAlwaysEnabled(frameNode);
}

EffectEdge ScrollModelNG::GetEffectEdge(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, EffectEdge::ALL);
    return ScrollableModelNG::GetEffectEdge(frameNode);
}

void ScrollModelNG::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(edgeEffect, alwaysEnabled, edge);
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
    if (scrollSnapAlign != ScrollSnapAlign::NONE) {
        pattern->SetIntervalSize(intervalSize);
    }
    pattern->SetSnapPaginations(snapPaginations);
    pattern->SetEnableSnapToSide(enableSnapToSide);
}

void ScrollModelNG::SetAxis(FrameNode* frameNode, Axis axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(ScrollLayoutProperty, Axis, axis, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    if (axis == Axis::FREE || pattern->GetAxis() == Axis::FREE) {
        return; // calling SetAxis would disrupt the axisChanged signal in ::OnModifyDone and initialization of FreeScroll
    }
    pattern->SetAxis(axis);
}

void ScrollModelNG::SetScrollBarColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, color, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    auto scrollBar = pattern->GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    scrollBar->SetForegroundColor(color);
}

void ScrollModelNG::ResetScrollBarColor(FrameNode* frameNode)
{
    ScrollableModelNG::SetScrollBarColor(frameNode, std::nullopt);
}

void ScrollModelNG::SetScrollBarWidth(FrameNode* frameNode, const Dimension& dimension)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, dimension, frameNode);
}

void ScrollModelNG::SetEdgeEffect(
    FrameNode* frameNode, const EdgeEffect& edgeEffect, bool alwaysEnabled, EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled, edge);
}

void ScrollModelNG::SetEnablePaging(FrameNode* frameNode, bool enablePaging)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    if (!enablePaging) {
        pattern->SetEnablePaging(ScrollPagingStatus::INVALID);
        return;
    }
    pattern->SetEnablePaging(ScrollPagingStatus::VALID);
    pattern->SetScrollSnapUpdate(true);
}

RefPtr<ScrollControllerBase> ScrollModelNG::GetOrCreateController(FrameNode* frameNode)
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

void ScrollModelNG::SetOnScrollEdge(FrameNode* frameNode, NG::ScrollEdgeEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollEdge(std::move(event));
}

NestedScrollOptions ScrollModelNG::GetNestedScroll(FrameNode* frameNode)
{
    NestedScrollOptions defaultOptions;
    CHECK_NULL_RETURN(frameNode, defaultOptions);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, defaultOptions);
    return pattern->GetNestedScroll();
}

ScrollEdgeType ScrollModelNG::GetOnScrollEdge(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, ScrollEdgeType::SCROLL_TOP);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    Axis axis = pattern->GetAxis();

    switch (axis) {
        case Axis::VERTICAL:
            if (pattern->IsAtTop()) {
                return ScrollEdgeType::SCROLL_TOP;
            }
            if (pattern->IsAtBottom()) {
                return ScrollEdgeType::SCROLL_BOTTOM;
            }
            break;
        case Axis::HORIZONTAL:
            if (pattern->IsAtTop()) {
                return ScrollEdgeType::SCROLL_LEFT;
            }
            if (pattern->IsAtBottom()) {
                return ScrollEdgeType::SCROLL_RIGHT;
            }
            break;
        default:
            break;
    }
    return ScrollEdgeType::SCROLL_NONE;
}

void ScrollModelNG::SetInitialOffset(const OffsetT<CalcDimension>& offset)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetInitialOffset(offset);
}

void ScrollModelNG::SetInitialOffset(FrameNode* frameNode, const OffsetT<CalcDimension>& offset)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetInitialOffset(offset);
}

void ScrollModelNG::SetScrollBarProxy(FrameNode* frameNode, const RefPtr<ScrollProxy>& proxy)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(proxy);
    CHECK_NULL_VOID(scrollBarProxy);
    pattern->SetScrollBarProxy(scrollBarProxy);
}

void ScrollModelNG::CreateWithResourceObjFriction(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ScrollFriction");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        double friction = -1.0;
        ResourceParseUtils::ParseResDouble(resObj, friction);
        pattern->SetFriction(friction);
    };
    pattern->AddResObj("ScrollFriction", resObj, std::move(updateFunc));
}

void ScrollModelNG::CreateWithResourceObjIntervalSize(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ScrollIntervalSize");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto layoutProperty = pattern->GetLayoutProperty<ScrollLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto scrollSnapAlign = layoutProperty->GetScrollSnapAlignValue(ScrollSnapAlign::NONE);
        CalcDimension intervalSize;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, intervalSize)) {
            intervalSize = CalcDimension(0.0);
        }
        if (scrollSnapAlign != ScrollSnapAlign::NONE) {
            pattern->SetIntervalSize(intervalSize);
        }
    };
    pattern->AddResObj("ScrollIntervalSize", resObj, std::move(updateFunc));
}

void ScrollModelNG::CreateWithResourceObjIntervalSize(
    FrameNode* frameNode, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ScrollIntervalSize");
    CHECK_NULL_VOID(HasResObj(resObjs));
    RefPtr<ResourceObject> resObj;
    if (resObjs.size() == 1) {
        resObj = resObjs[0];
    }
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto layoutProperty = pattern->GetLayoutProperty<ScrollLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto scrollSnapAlign = layoutProperty->GetScrollSnapAlignValue(ScrollSnapAlign::NONE);
        CalcDimension intervalSize;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, intervalSize)) {
            intervalSize = CalcDimension(0.0);
        }
        if (scrollSnapAlign != ScrollSnapAlign::NONE) {
            pattern->SetIntervalSize(intervalSize);
        }
    };
    pattern->AddResObj("ScrollIntervalSize", resObj, std::move(updateFunc));
}

bool ScrollModelNG::CheckSnapPaginations(const std::vector<Dimension>& snapPaginations)
{
    CHECK_NULL_RETURN(!snapPaginations.empty(), false);
    float preValue = (*snapPaginations.begin()).Value();
    CHECK_NULL_RETURN(!Negative(preValue), false);
    auto unit = (*snapPaginations.begin()).Unit();
    for (auto iter = snapPaginations.begin() + 1; iter < snapPaginations.end(); ++iter) {
        if (Negative((*iter).Value()) || (*iter).Unit() != unit || LessOrEqual((*iter).Value(), preValue)) {
            return false;
        }
        preValue = (*iter).Value();
    }
    return true;
}

bool ScrollModelNG::HasResObj(const std::vector<RefPtr<ResourceObject>>& resObjs)
{
    for (size_t i = 0; i < resObjs.size(); ++i) {
        CHECK_NULL_CONTINUE(resObjs[i]);
        return true;
    }
    return false;
}

void ScrollModelNG::CreateWithResourceObjSnapPaginations(
    const std::vector<Dimension>& snapPaginations, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ScrollSnapPaginations");
    CHECK_NULL_VOID(HasResObj(resObjs));
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), resObjs, snapPaginations](
                            const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::vector<Dimension> snapPaginationsTmp(snapPaginations);
        CHECK_NULL_VOID(snapPaginationsTmp.size() == resObjs.size());
        for (size_t i = 0; i < resObjs.size(); ++i) {
            CHECK_NULL_CONTINUE(resObjs[i]);
            CalcDimension snapPagination;
            if (ResourceParseUtils::ParseResDimensionVp(resObjs[i], snapPagination)) {
                snapPaginationsTmp[i] = snapPagination;
            } else {
                std::vector<Dimension>().swap(snapPaginationsTmp);
                break;
            }
        }
        if (!CheckSnapPaginations(snapPaginationsTmp)) {
            std::vector<Dimension>().swap(snapPaginationsTmp);
        }
        pattern->SetSnapPaginations(snapPaginationsTmp);
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    pattern->AddResObj("ScrollSnapPaginations", resObj, std::move(updateFunc));
}

void ScrollModelNG::CreateWithResourceObjSnapPaginations(
    FrameNode* frameNode, const std::vector<Dimension>& snapPaginations, std::vector<RefPtr<ResourceObject>>& resObjs)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("ScrollSnapPaginations");
    CHECK_NULL_VOID(HasResObj(resObjs));
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), resObjs, snapPaginations](
                            const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::vector<Dimension> snapPaginationsTmp(snapPaginations);
        CHECK_NULL_VOID(snapPaginationsTmp.size() == resObjs.size());
        for (size_t i = 0; i < resObjs.size(); ++i) {
            CHECK_NULL_CONTINUE(resObjs[i]);
            CalcDimension snapPagination;
            if (ResourceParseUtils::ParseResDimensionVp(resObjs[i], snapPagination)) {
                snapPaginationsTmp[i] = snapPagination;
            } else {
                std::vector<Dimension>().swap(snapPaginationsTmp);
                break;
            }
        }
        if (!CheckSnapPaginations(snapPaginationsTmp)) {
            std::vector<Dimension>().swap(snapPaginationsTmp);
        }
        pattern->SetSnapPaginations(snapPaginationsTmp);
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    pattern->AddResObj("ScrollSnapPaginations", resObj, std::move(updateFunc));
}

void ScrollModelNG::SetMaxZoomScale(float scale)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetMaxZoomScale(frameNode, scale);
}

void ScrollModelNG::SetMaxZoomScale(FrameNode* frameNode, float scale)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaxZoomScale(scale);
}

float ScrollModelNG::GetMaxZoomScale(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 1.0f);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, 1.0f);
    return pattern->GetMaxZoomScale();
}

void ScrollModelNG::SetMinZoomScale(float scale)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetMinZoomScale(frameNode, scale);
}

void ScrollModelNG::SetMinZoomScale(FrameNode* frameNode, float scale)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMinZoomScale(scale);
}

float ScrollModelNG::GetMinZoomScale(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 1.0f);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, 1.0f);
    return pattern->GetMinZoomScale();
}

void ScrollModelNG::SetZoomScale(float scale)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetZoomScale(frameNode, scale);
}

void ScrollModelNG::SetZoomScale(FrameNode* frameNode, float scale)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetZoomScale(scale);
}

float ScrollModelNG::GetZoomScale(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 1.0f);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, 1.0f);
    return pattern->GetZoomScale();
}

void ScrollModelNG::ResetZoomScale()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ResetZoomScale(frameNode);
}

void ScrollModelNG::ResetZoomScale(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetZoomScale(std::nullopt);
}

void ScrollModelNG::SetZoomScaleChangeEvent(std::function<void(float)>&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnZoomScaleChange(std::move(event));
}

void ScrollModelNG::SetEnableBouncesZoom(bool enable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetEnableBouncesZoom(frameNode, enable);
}

void ScrollModelNG::SetEnableBouncesZoom(FrameNode* frameNode, bool enable)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableBouncesZoom(enable);
}

bool ScrollModelNG::GetEnableBouncesZoom(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, true);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    CHECK_NULL_RETURN(pattern, true);
    return pattern->GetEnableBouncesZoom();
}

void ScrollModelNG::SetOnDidZoom(std::function<void(float)>&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnDidZoom(frameNode, std::move(event));
}

void ScrollModelNG::SetOnZoomStart(std::function<void()>&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnZoomStart(frameNode, std::move(event));
}

void ScrollModelNG::SetOnZoomStop(std::function<void()>&& event)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnZoomStop(frameNode, std::move(event));
}

void ScrollModelNG::SetOnDidZoom(FrameNode* frameNode, std::function<void(float)>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidZoom(std::move(event));
}

void ScrollModelNG::SetOnZoomStart(FrameNode* frameNode, std::function<void()>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnZoomStart(std::move(event));
}

void ScrollModelNG::SetOnZoomStop(FrameNode* frameNode, std::function<void()>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnZoomStop(std::move(event));
}

void ScrollModelNG::CreateWithResourceObjScrollBarColor(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObjScrollBarColor(frameNode, resObj);
}

void ScrollModelNG::CreateWithResourceObjScrollBarColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    ScrollableModelNG::CreateWithResourceObjScrollBarColor(frameNode, resObj);
}
} // namespace OHOS::Ace::NG
