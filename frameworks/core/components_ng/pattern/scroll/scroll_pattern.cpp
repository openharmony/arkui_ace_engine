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

#include "core/components_ng/pattern/scroll/scroll_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_paint_property.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t SCROLL_NONE = 0;
constexpr int32_t SCROLL_TOUCH_DOWN = 1;
constexpr int32_t SCROLL_TOUCH_UP = 2;
constexpr float SCROLL_RATIO = 0.52f;
constexpr float SCROLL_BY_SPEED = 250.0f; // move 250 pixels per second
constexpr float UNIT_CONVERT = 1000.0f;   // 1s convert to 1000ms

float CalculateFriction(float gamma)
{
    return static_cast<float>(SCROLL_RATIO * std::pow(1.0 - gamma, SQUARE));
}

float CalculateOffsetByFriction(float extentOffset, float delta, float friction)
{
    if (NearZero(friction)) {
        return delta;
    }
    float deltaToLimit = extentOffset / friction;
    if (delta < deltaToLimit) {
        return delta * friction;
    }
    return extentOffset + delta - deltaToLimit;
}

} // namespace

void ScrollPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
    host->GetRenderContext()->UpdateClipEdge(true);
}

void ScrollPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = host->GetPaintProperty<ScrollPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    if (axis != GetAxis()) {
        SetAxis(axis);
        ResetPosition();
    }
    if (!GetScrollableEvent()) {
        AddScrollEvent();
        RegisterScrollEventTask();
    }
    SetEdgeEffect(layoutProperty->GetEdgeEffect().value_or(EdgeEffect::NONE));
    SetScrollBar(paintProperty->GetScrollBarProperty());
    SetAccessibilityAction();
    if (scrollSnapUpdate_) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void ScrollPattern::RegisterScrollEventTask()
{
    auto scrollableEvent = GetScrollableEvent();
    CHECK_NULL_VOID(scrollableEvent);
    auto eventHub = GetHost()->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onScrollEvent = eventHub->GetOnScrollEvent();
    if (onScrollEvent) {
        scrollableEvent->SetOnScrollCallback(std::move(onScrollEvent));
    }
    auto scrollBeginEvent = eventHub->GetScrollBeginEvent();
    if (scrollBeginEvent) {
        scrollableEvent->SetScrollBeginCallback(std::move(scrollBeginEvent));
    }
    auto scrollFrameBeginEvent = eventHub->GetScrollFrameBeginEvent();
    if (scrollFrameBeginEvent) {
        scrollableEvent->SetScrollFrameBeginCallback(std::move(scrollFrameBeginEvent));
    }
}

bool ScrollPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<ScrollLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    currentOffset_ = layoutAlgorithm->GetCurrentOffset();
    scrollableDistance_ = layoutAlgorithm->GetScrollableDistance();
    auto axis = GetAxis();
    auto oldMainSize = GetMainAxisSize(viewPort_, axis);
    auto newMainSize = GetMainAxisSize(layoutAlgorithm->GetViewPortSize(), axis);
    auto oldExtentMainSize = GetMainAxisSize(viewPortExtent_, axis);
    auto newExtentMainSize = GetMainAxisSize(layoutAlgorithm->GetViewPortExtent(), axis);
    viewPortLength_ = layoutAlgorithm->GetViewPort();
    viewPort_ = layoutAlgorithm->GetViewPortSize();
    viewPortExtent_ = layoutAlgorithm->GetViewPortExtent();
    if (scrollSnapUpdate_ || !NearEqual(oldMainSize, newMainSize) || !NearEqual(oldExtentMainSize, newExtentMainSize)) {
        CaleSnapOffsets();
        scrollSnapUpdate_ = false;
    }
    UpdateScrollBarOffset();
    if (config.frameSizeChange) {
        if (GetScrollBar() != nullptr) {
            GetScrollBar()->OnScrollEnd();
        }
    }
    if (ScrollableIdle() && !AnimateRunning()) {
        auto predictSnapOffset = CalePredictSnapOffset(0.0);
        if (predictSnapOffset.has_value() && !NearZero(predictSnapOffset.value())) {
            StartScrollSnapMotion(predictSnapOffset.value(), 0.0f);
            FireOnScrollStart();
            scrollStop_ = false;
        }
    }
    if (scrollStop_) {
        FireOnScrollStop();
        scrollStop_ = false;
    }
    CheckScrollable();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    host->SetViewPort(geometryNode->GetFrameRect());
    return false;
}

void ScrollPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    SetScrollEnable(layoutProperty->GetScrollEnabled().value_or(true));
}

void ScrollPattern::FireOnScrollStart()
{
    if (GetScrollAbort()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID_NOLOG(hub);
    auto onScrollStart = hub->GetScrollStartEvent();
    CHECK_NULL_VOID_NOLOG(onScrollStart);
    onScrollStart();
}

void ScrollPattern::FireOnScrollStop()
{
    if (GetScrollAbort()) {
        SetScrollAbort(false);
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID_NOLOG(hub);
    auto onScrollStop = hub->GetScrollStopEvent();
    CHECK_NULL_VOID_NOLOG(onScrollStop);
    onScrollStop();
}

bool ScrollPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source != SCROLL_FROM_START) {
        if (GetAxis() == Axis::NONE) {
            return false;
        }
        if (!AnimateStoped()) {
            return false;
        }
        auto adjustOffset = static_cast<float>(offset);
        auto scrollBar = GetScrollBar();
        if (scrollBar && scrollBar->IsDriving()) {
            adjustOffset = scrollBar->CalcPatternOffset(adjustOffset);
            source = SCROLL_FROM_BAR;
        }
        AdjustOffset(adjustOffset, source);
        return UpdateCurrentOffset(adjustOffset, source);
    } else {
        FireOnScrollStart();
    }
    return true;
}

void ScrollPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("friction", GetFriction());
}

void ScrollPattern::OnScrollEndCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto scrollEndEvent = eventHub->GetScrollEndEvent();
    if (scrollEndEvent) {
        scrollEndEvent();
    }
    scrollStop_ = true;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ScrollPattern::ResetPosition()
{
    currentOffset_ = 0.0f;
    lastOffset_ = 0.0f;
}

bool ScrollPattern::IsAtTop() const
{
    return GreatOrEqual(currentOffset_, 0.0);
}

bool ScrollPattern::IsAtBottom() const
{
    bool atBottom = LessOrEqual(currentOffset_, -scrollableDistance_);
    // TODO: ignore ReachMaxCount
    return atBottom;
}

OverScrollOffset ScrollPattern::GetOverScrollOffset(double delta) const
{
    OverScrollOffset offset = { 0, 0 };
    auto startPos = currentOffset_;
    auto newStartPos = startPos + delta;
    if (startPos > 0 && newStartPos > 0) {
        offset.start = delta;
    }
    if (startPos > 0 && newStartPos <= 0) {
        offset.start = -startPos;
    }
    if (startPos <= 0 && newStartPos > 0) {
        offset.start = newStartPos;
    }

    auto endPos = currentOffset_;
    auto newEndPos = endPos + delta;
    auto endRefences = -scrollableDistance_;
    if (endPos < endRefences && newEndPos < endRefences) {
        offset.end = delta;
    }
    if (endPos < endRefences && newEndPos >= endRefences) {
        offset.end = endRefences - endPos;
    }
    if (endPos >= endRefences && newEndPos < endRefences) {
        offset.end = newEndPos - endRefences;
    }
    return offset;
}

bool ScrollPattern::IsOutOfBoundary() const
{
    return Positive(currentOffset_) || LessNotEqual(currentOffset_, -scrollableDistance_);
}

bool ScrollPattern::ScrollPageCheck(float delta, int32_t source)
{
    return true;
}

void ScrollPattern::HandleScrollBarOutBoundary()
{
    auto scrollBar = GetScrollBar();
    if (scrollBar && scrollBar->NeedScrollBar()) {
        scrollBar->SetOutBoundary(std::abs(GetScrollBarOutBoundaryExtent()));
    }
}

void ScrollPattern::AdjustOffset(float& delta, int32_t source)
{
    if (NearZero(delta) || NearZero(viewPortLength_) || source == SCROLL_FROM_ANIMATION ||
        source == SCROLL_FROM_ANIMATION_SPRING) {
        return;
    }
    // the distance above the top, if lower than top, it is zero
    float overScrollPastStart = 0.0f;
    // the distance below the bottom, if higher than bottom, it is zero
    float overScrollPastEnd = 0.0f;
    float overScrollPast = 0.0f;
    // TODO: not consider rowReverse or colReverse
    overScrollPastStart = std::max(currentOffset_, 0.0f);
    overScrollPastEnd = std::max(-scrollableDistance_ - currentOffset_, 0.0f);
    // do not adjust offset if direction opposite from the overScroll direction when out of boundary
    if ((overScrollPastStart > 0.0f && delta < 0.0f) || (overScrollPastEnd > 0.0f && delta > 0.0f)) {
        return;
    }
    overScrollPast = std::max(overScrollPastStart, overScrollPastEnd);
    if (overScrollPast == 0.0f) {
        return;
    }
    float friction = CalculateFriction((overScrollPast - std::abs(delta)) / viewPortLength_);
    float direction = delta > 0.0f ? 1.0f : -1.0f;
    delta = direction * CalculateOffsetByFriction(overScrollPast, std::abs(delta), friction);
}

void ScrollPattern::ValidateOffset(int32_t source)
{
    if (scrollableDistance_ <= 0.0f || source == SCROLL_FROM_JUMP) {
        return;
    }

    // restrict position between top and bottom
    if (IsRestrictBoundary() || source == SCROLL_FROM_BAR || source == SCROLL_FROM_ROTATE) {
        if (GetAxis() == Axis::HORIZONTAL) {
            if (IsRowReverse()) {
                currentOffset_ = std::clamp(currentOffset_, 0.0f, scrollableDistance_);
            } else {
                currentOffset_ = std::clamp(currentOffset_, -scrollableDistance_, 0.0f);
            }
        } else {
            currentOffset_ = std::clamp(currentOffset_, -scrollableDistance_, 0.0f);
        }
    } else {
        if (currentOffset_ > 0) {
            SetScrollBarOutBoundaryExtent(currentOffset_);
        } else if ((-currentOffset_) >= (GetMainSize(viewPortExtent_) - GetMainSize(viewPort_)) && ReachMaxCount()) {
            SetScrollBarOutBoundaryExtent((-currentOffset_) - (GetMainSize(viewPortExtent_) - GetMainSize(viewPort_)));
        }
        HandleScrollBarOutBoundary();
    }
}

void ScrollPattern::HandleScrollPosition(float scroll, int32_t scrollState)
{
    auto scrollableEvent = GetScrollableEvent();
    CHECK_NULL_VOID_NOLOG(scrollableEvent);
    const auto& onScroll = scrollableEvent->GetOnScrollCallback();
    CHECK_NULL_VOID_NOLOG(onScroll);
    // not consider async call
    Dimension scrollX(0, DimensionUnit::VP);
    Dimension scrollY(0, DimensionUnit::VP);
    Dimension scrollPx(scroll, DimensionUnit::PX);
    auto scrollVpValue = scrollPx.ConvertToVp();
    if (GetAxis() == Axis::HORIZONTAL) {
        scrollX.SetValue(scrollVpValue);
    } else {
        scrollY.SetValue(scrollVpValue);
    }
    onScroll(scrollX, scrollY);
}

bool ScrollPattern::IsCrashTop() const
{
    bool scrollUpToReachTop = LessNotEqual(lastOffset_, 0.0) && GreatOrEqual(currentOffset_, 0.0);
    bool scrollDownToReachTop = GreatNotEqual(lastOffset_, 0.0) && LessOrEqual(currentOffset_, 0.0);
    return scrollUpToReachTop || scrollDownToReachTop;
}

bool ScrollPattern::IsCrashBottom() const
{
    float minExtent = -scrollableDistance_;
    bool scrollDownToReachEnd = GreatNotEqual(lastOffset_, minExtent) && LessOrEqual(currentOffset_, minExtent);
    bool scrollUpToReachEnd = LessNotEqual(lastOffset_, minExtent) && GreatOrEqual(currentOffset_, minExtent);
    return (scrollUpToReachEnd || scrollDownToReachEnd) && ReachMaxCount();
}

void ScrollPattern::HandleCrashTop() const
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    const auto& onScrollEdge = eventHub->GetScrollEdgeEvent();
    CHECK_NULL_VOID_NOLOG(onScrollEdge);
    // not consider async call
    if (GetAxis() == Axis::HORIZONTAL) {
        onScrollEdge(ScrollEdge::LEFT);
        return;
    }
    onScrollEdge(ScrollEdge::TOP);
}

void ScrollPattern::HandleCrashBottom() const
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollEventHub>();
    CHECK_NULL_VOID(eventHub);
    const auto& onScrollEdge = eventHub->GetScrollEdgeEvent();
    CHECK_NULL_VOID_NOLOG(onScrollEdge);
    if (GetAxis() == Axis::HORIZONTAL) {
        onScrollEdge(ScrollEdge::RIGHT);
        return;
    }
    onScrollEdge(ScrollEdge::BOTTOM);
}

bool ScrollPattern::UpdateCurrentOffset(float delta, int32_t source)
{
    SetScrollState(source);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (NearZero(delta)) {
        return true;
    }
    // TODO: ignore handle refresh
    if (source != SCROLL_FROM_JUMP && !HandleEdgeEffect(delta, source, viewPort_)) {
        if (IsOutOfBoundary()) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        return false;
    }
    // TODO: scrollBar effect!!
    lastOffset_ = currentOffset_;
    currentOffset_ += delta;
    ValidateOffset(source);
    int32_t touchState = SCROLL_NONE;
    if (source == SCROLL_FROM_UPDATE) {
        touchState = SCROLL_TOUCH_DOWN;
    } else if (source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
        touchState = SCROLL_TOUCH_UP;
    }
    HandleScrollPosition(-delta, touchState);
    if (IsCrashTop()) {
        HandleCrashTop();
    } else if (IsCrashBottom()) {
        HandleCrashBottom();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return true;
}

void ScrollPattern::OnAnimateStop()
{
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    StartScrollBarAnimatorByProxy();
    scrollStop_ = true;
}

void ScrollPattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
    ScrollablePattern::AnimateTo(position, duration, curve, smooth);
    FireOnScrollStart();
}

void ScrollPattern::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    if (scrollEdgeType == ScrollEdgeType::SCROLL_NONE) {
        return;
    }
    float distance = scrollEdgeType == ScrollEdgeType::SCROLL_TOP ? -currentOffset_ :
        (-scrollableDistance_ - currentOffset_);
    ScrollBy(distance, distance, smooth);
}

void ScrollPattern::ScrollBy(float pixelX, float pixelY, bool smooth, const std::function<void()>& onFinish)
{
    float distance = (GetAxis() == Axis::VERTICAL) ? pixelY : pixelX;
    if (NearZero(distance)) {
        return;
    }
    float position = currentOffset_ + distance;
    if (smooth) {
        AnimateTo(-position, fabs(distance) * UNIT_CONVERT / SCROLL_BY_SPEED, Curves::EASE_OUT, true);
        return;
    }
    JumpToPosition(position);
}

bool ScrollPattern::ScrollPage(bool reverse, bool smooth, const std::function<void()>& onFinish)
{
    float distance = reverse ? viewPortLength_ : -viewPortLength_;
    ScrollBy(distance, distance, smooth, onFinish);
    return true;
}

void ScrollPattern::JumpToPosition(float position, int32_t source)
{
    // If an animation is playing, stop it.
    StopAnimate();
    float cachePosition = currentOffset_;
    DoJump(position, source);
    StartScrollBarAnimatorByProxy();
    if (cachePosition != currentOffset_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    }
}

void ScrollPattern::ScrollTo(float position)
{
    JumpToPosition(-position, SCROLL_FROM_JUMP);
}

void ScrollPattern::DoJump(float position, int32_t source)
{
    float setPosition = (GetAxis() == Axis::HORIZONTAL && IsRowReverse()) ? -position : position;
    if (!NearEqual(currentOffset_, setPosition)) {
        UpdateCurrentOffset(setPosition - currentOffset_, source);
    }
}

void ScrollPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        CHECK_NULL_RETURN_NOLOG(scroll, 0.0);
        return scroll->GetCurrentPosition();
    });
    scrollEffect->SetLeadingCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll && !scroll->IsRowReverse() && !scroll->IsColReverse() && scroll->GetScrollableDistance() > 0) {
            return -scroll->GetScrollableDistance();
        }
        return 0.0;
    });
    scrollEffect->SetTrailingCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll && (scroll->IsRowReverse() || scroll->IsColReverse())) {
            return scroll->GetScrollableDistance();
        }
        return 0.0;
    });
    scrollEffect->SetInitLeadingCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll && !scroll->IsRowReverse() && !scroll->IsColReverse() && scroll->GetScrollableDistance() > 0) {
            return -scroll->GetScrollableDistance();
        }
        return 0.0;
    });
    scrollEffect->SetInitTrailingCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto scroll = weakScroll.Upgrade();
        if (scroll && (scroll->IsRowReverse() || scroll->IsColReverse())) {
            return scroll->GetScrollableDistance();
        }
        return 0.0;
    });
}

void ScrollPattern::UpdateScrollBarOffset()
{
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    Size size(viewPort_.Width(), viewPort_.Height());
    auto estimatedHeight = (GetAxis() == Axis::HORIZONTAL) ? viewPortExtent_.Width() : viewPortExtent_.Height();
    UpdateScrollBarRegion(-currentOffset_, estimatedHeight, size, Offset(0.0, 0.0));
}

void ScrollPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsScrollable() && pattern->GetScrollableDistance() > 0.0f) {
            pattern->ScrollPage(false, true);
        }
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsScrollable() && pattern->GetScrollableDistance() > 0.0f) {
            pattern->ScrollPage(true, true);
        }
    });
}

OffsetF ScrollPattern::GetOffsetToScroll(const RefPtr<FrameNode>& childFrame) const
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, OffsetF());
    CHECK_NULL_RETURN(childFrame, OffsetF());
    auto childGeometryNode = childFrame->GetGeometryNode();
    CHECK_NULL_RETURN(childGeometryNode, OffsetF());
    OffsetF result = childGeometryNode->GetFrameOffset();
    auto parent = childFrame->GetParent();
    while (parent) {
        auto parentFrame = AceType::DynamicCast<FrameNode>(parent);
        if (!parentFrame) {
            parent = parent->GetParent();
            continue;
        }
        if (parentFrame == frameNode) {
            return result;
        }
        auto parentGeometryNode = parentFrame->GetGeometryNode();
        if (!parentGeometryNode) {
            parent = parent->GetParent();
            continue;
        }
        result += parentGeometryNode->GetFrameOffset();
        parent = parent->GetParent();
    }
    return OffsetF(0.0, 0.0);
}

bool ScrollPattern::ScrollToNode(const RefPtr<FrameNode>& focusFrameNode)
{
    CHECK_NULL_RETURN(focusFrameNode, false);
    auto focusGeometryNode = focusFrameNode->GetGeometryNode();
    CHECK_NULL_RETURN(focusGeometryNode, false);
    auto focusNodeSize = focusGeometryNode->GetFrameSize();
    auto focusNodeOffsetToScrolll = GetOffsetToScroll(focusFrameNode);
    auto scrollFrame = GetHost();
    CHECK_NULL_RETURN(scrollFrame, false);
    auto scrollGeometry = scrollFrame->GetGeometryNode();
    CHECK_NULL_RETURN(scrollGeometry, false);
    auto scrollFrameSize = scrollGeometry->GetFrameSize();
    LOGD("Child: %{public}s/%{public}d on focus. Size is (%{public}f,%{public}f). Offset to Scroll is "
         "(%{public}f,%{public}f). Scroll size is (%{public}f,%{public}f)",
        focusFrameNode->GetTag().c_str(), focusFrameNode->GetId(), focusNodeSize.Width(), focusNodeSize.Height(),
        focusNodeOffsetToScrolll.GetX(), focusNodeOffsetToScrolll.GetY(), scrollFrameSize.Width(),
        scrollFrameSize.Height());

    float focusNodeDiffToScroll =
        GetAxis() == Axis::VERTICAL ? focusNodeOffsetToScrolll.GetY() : focusNodeOffsetToScrolll.GetX();
    if (NearZero(focusNodeDiffToScroll)) {
        return false;
    }
    float focusNodeLength = GetAxis() == Axis::VERTICAL ? focusNodeSize.Height() : focusNodeSize.Width();
    float scrollFrameLength = GetAxis() == Axis::VERTICAL ? scrollFrameSize.Height() : scrollFrameSize.Width();
    float moveOffset = 0.0;
    if (LessNotEqual(focusNodeDiffToScroll, 0)) {
        moveOffset = -focusNodeDiffToScroll;
    } else if (GreatNotEqual(focusNodeDiffToScroll + focusNodeLength, scrollFrameLength)) {
        moveOffset = scrollFrameLength - focusNodeDiffToScroll - focusNodeLength;
    }
    if (!NearZero(moveOffset)) {
        LOGD("Scroll offset: %{public}f on axis: %{public}d", moveOffset, GetAxis());
        return OnScrollCallback(moveOffset, SCROLL_FROM_FOCUS_JUMP);
    }
    return false;
}

std::optional<float> ScrollPattern::CalePredictSnapOffset(float delta)
{
    std::optional<float> predictSnapOffset;
    CHECK_NULL_RETURN_NOLOG(!snapOffsets_.empty(), predictSnapOffset);
    CHECK_NULL_RETURN_NOLOG(GetScrollSnapAlign() != ScrollSnapAlign::NONE, predictSnapOffset);
    float finalPosition = currentOffset_ + delta;
    if (!IsSnapToInterval()) {
        if (!enableSnapToSide_.first) {
            if (GreatNotEqual(finalPosition, *(snapOffsets_.begin() + 1)) ||
                GreatNotEqual(currentOffset_, *(snapOffsets_.begin() + 1))) {
                return predictSnapOffset;
            }
        }
        if (!enableSnapToSide_.second) {
            if (LessNotEqual(finalPosition, *(snapOffsets_.rbegin() + 1)) ||
                LessNotEqual(currentOffset_, *(snapOffsets_.rbegin() + 1))) {
                return predictSnapOffset;
            }
        }
    }
    float head = 0.0f;
    float tail = -scrollableDistance_;
    if (GreatOrEqual(finalPosition, head) || LessOrEqual(finalPosition, tail)) {
        return predictSnapOffset;
    } else if (LessNotEqual(finalPosition, head) && GreatOrEqual(finalPosition, *(snapOffsets_.begin()))) {
        predictSnapOffset = *(snapOffsets_.begin());
    } else if (GreatNotEqual(finalPosition, tail) && LessOrEqual(finalPosition, *(snapOffsets_.rbegin()))) {
        predictSnapOffset = *(snapOffsets_.rbegin());
    } else {
        auto iter = snapOffsets_.begin() + 1;
        float start = *(iter - 1);
        float end = *(iter);
        for (; iter != snapOffsets_.end(); ++iter) {
            if (GreatOrEqual(finalPosition, *iter)) {
                start = *(iter - 1);
                end = *(iter);
                predictSnapOffset = (LessNotEqual(start - finalPosition, finalPosition - end) ? start : end);
                break;
            }
        }
    }
    if (predictSnapOffset.has_value()) {
        predictSnapOffset = predictSnapOffset.value() - currentOffset_;
        LOGD("CalePredictSnapOffset predictSnapOffset:%{public}f", predictSnapOffset.value());
    }
    return predictSnapOffset;
}

void ScrollPattern::CaleSnapOffsets()
{
    auto scrollSnapAlign = GetScrollSnapAlign();
    std::vector<float>().swap(snapOffsets_);
    CHECK_NULL_VOID_NOLOG(scrollSnapAlign != ScrollSnapAlign::NONE);
    if (IsSnapToInterval()) {
        CaleSnapOffsetsByInterval(scrollSnapAlign);
    } else {
        CaleSnapOffsetsByPaginations();
    }
}

void ScrollPattern::CaleSnapOffsetsByInterval(ScrollSnapAlign scrollSnapAlign)
{
    auto mainSize = GetMainAxisSize(viewPort_, GetAxis());
    auto extentMainSize = GetMainAxisSize(viewPortExtent_, GetAxis());
    auto start = 0.0f;
    auto end = -scrollableDistance_;
    auto snapOffset = 0.0f;
    auto intervalSize = 0.0f;
    auto sizeDelta = 0.0f;
    if (intervalSize_.Unit() == DimensionUnit::PERCENT) {
        intervalSize = intervalSize_.Value() * mainSize;
    } else {
        intervalSize = intervalSize_.ConvertToPx();
    }
    float temp = static_cast<int32_t>(extentMainSize / intervalSize) * intervalSize;
    switch (scrollSnapAlign) {
        case ScrollSnapAlign::START:
            start = 0.0f;
            end = -temp;
            break;
        case ScrollSnapAlign::CENTER:
            sizeDelta = (mainSize - intervalSize) / 2;
            start = Positive(sizeDelta) ? sizeDelta - static_cast<int32_t>(sizeDelta / intervalSize) * intervalSize
                                        : sizeDelta;
            end = -temp + (mainSize - extentMainSize + temp) / 2;
            break;
        case ScrollSnapAlign::END:
            sizeDelta = mainSize - intervalSize;
            start = Positive(sizeDelta) ? mainSize - static_cast<int32_t>(mainSize / intervalSize) * intervalSize
                                        : sizeDelta;
            end = -scrollableDistance_;
            break;
        default:
            break;
    }
    if (!Positive(start)) {
        snapOffsets_.emplace_back(start);
    }
    snapOffset = start - intervalSize;
    while (GreatOrEqual(snapOffset, -scrollableDistance_) && GreatOrEqual(snapOffset, end)) {
        snapOffsets_.emplace_back(snapOffset);
        snapOffset -= intervalSize;
    }
    if (GreatNotEqual(end, -scrollableDistance_)) {
        snapOffsets_.emplace_back(end);
    }
}

void ScrollPattern::CaleSnapOffsetsByPaginations()
{
    auto mainSize = GetMainAxisSize(viewPort_, GetAxis());
    auto start = 0.0f;
    auto end = -scrollableDistance_;
    auto snapOffset = 0.0f;
    snapOffsets_.emplace_back(start);
    int32_t length = 0;
    if (static_cast<int32_t>(snapPaginations_.size()) > 0 && NearZero(snapPaginations_[length].Value())) {
        length++;
    }
    for (; length < static_cast<int32_t>(snapPaginations_.size()); length++) {
        if (snapPaginations_[length].Unit() == DimensionUnit::PERCENT) {
            snapOffset = -(snapPaginations_[length].Value() * mainSize);
        } else {
            snapOffset = -snapPaginations_[length].ConvertToPx();
        }
        if (GreatNotEqual(snapOffset, -scrollableDistance_)) {
            snapOffsets_.emplace_back(snapOffset);
        } else {
            break;
        }
    }
    snapOffsets_.emplace_back(end);
}

bool ScrollPattern::NeedScrollSnapToSide(float delta)
{
    CHECK_NULL_RETURN_NOLOG(GetScrollSnapAlign() != ScrollSnapAlign::NONE, false);
    CHECK_NULL_RETURN_NOLOG(!IsSnapToInterval(), false);
    auto finalPosition = currentOffset_ + delta;
    CHECK_NULL_RETURN_NOLOG(static_cast<int32_t>(snapOffsets_.size()) > 2, false);
    if (!enableSnapToSide_.first) {
        if (GreatOrEqual(currentOffset_, *(snapOffsets_.begin() + 1)) &&
            LessOrEqual(finalPosition, *(snapOffsets_.begin() + 1))) {
            return true;
        }
    }
    if (!enableSnapToSide_.second) {
        if (LessOrEqual(currentOffset_, *(snapOffsets_.rbegin() + 1)) &&
            GreatOrEqual(finalPosition, *(snapOffsets_.rbegin() + 1))) {
            return true;
        }
    }
    return false;
}
} // namespace OHOS::Ace::NG
