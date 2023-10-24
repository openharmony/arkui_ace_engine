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

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/manager/select_overlay/select_overlay_scroll_notifier.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Color SELECT_FILL_COLOR = Color(0x1A000000);
constexpr Color SELECT_STROKE_COLOR = Color(0x33FFFFFF);
} // namespace

void ScrollablePattern::SetAxis(Axis axis)
{
    if (axis_ == axis) {
        return;
    }
    axis_ = axis;
    if (scrollBar_) {
        scrollBar_->SetPositionMode(axis_ == Axis::HORIZONTAL ? PositionMode::BOTTOM : PositionMode::RIGHT);
    }
    if (scrollBarOverlayModifier_) {
        scrollBarOverlayModifier_->SetPositionMode(
            axis_ == Axis::HORIZONTAL ? PositionMode::BOTTOM : PositionMode::RIGHT);
    }
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
        scrollableEvent_->SetAxis(axis);
        gestureHub->AddScrollableEvent(scrollableEvent_);
    }
    if (scrollEffect_) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
    }
}

RefPtr<GestureEventHub> ScrollablePattern::GetGestureHub()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    return hub->GetOrCreateGestureEventHub();
}

RefPtr<InputEventHub> ScrollablePattern::GetInputHub()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(host, nullptr);
    return hub->GetOrCreateInputEventHub();
}

bool ScrollablePattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        return true;
    }
    return UpdateCurrentOffset(offset, source);
}

void ScrollablePattern::DraggedDownScrollEndProcess()
{
    CHECK_NULL_VOID(navBarPattern_);
    if (!navBarPattern_->GetDraggedDown() && isReactInParentMovement_) {
        isReactInParentMovement_ = false;
        navBarPattern_->OnCoordScrollEnd();
    }
}

void ScrollablePattern::ProcessNavBarReactOnStart()
{
    CHECK_NULL_VOID(navBarPattern_);
    navBarPattern_->OnCoordScrollStart();
}

bool ScrollablePattern::ProcessNavBarReactOnUpdate(float offset)
{
    CHECK_NULL_RETURN(navBarPattern_, true);
    auto minTitle = navBarPattern_ ? navBarPattern_->GetIsMinTitle() : false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    std::list<RefPtr<FrameNode>> childrens;
    host->GenerateOneDepthVisibleFrame(childrens);
    auto firstGeometryNode = (*childrens.begin())->GetGeometryNode();
    CHECK_NULL_RETURN(firstGeometryNode, true);
    auto dragOffsetY = firstGeometryNode->GetFrameOffset().GetY();
    navBarPattern_->OnCoordScrollUpdate(offset, dragOffsetY);
    DraggedDownScrollEndProcess();
    if (minTitle) {
        return scrollEffect_ && scrollEffect_->IsNoneEffect();
    }
    return scrollEffect_ && scrollEffect_->IsSpringEffect();
}

void ScrollablePattern::ProcessNavBarReactOnEnd()
{
    CHECK_NULL_VOID(navBarPattern_);
    navBarPattern_->OnCoordScrollEnd();
}

bool ScrollablePattern::OnScrollPosition(double offset, int32_t source)
{
    auto isAtTop = (IsAtTop() && Positive(offset));
    auto refreshCoordinateMode = CoordinateWithRefresh(offset, source, isAtTop);
    auto isDraggedDown = navBarPattern_ ? navBarPattern_->GetDraggedDown() : false;
    auto navigationInCoordination = CoordinateWithNavigation(isAtTop, isDraggedDown, offset, source);
    if ((refreshCoordinateMode == RefreshCoordinationMode::REFRESH_SCROLL) || navigationInCoordination) {
        return false;
    }

    if (source == SCROLL_FROM_START) {
        SetParentScrollable();
        GetParentNavigation();
        StopScrollBarAnimatorByProxy();
        AbortScrollAnimator();
    } else if (!AnimateStoped()) {
        return false;
    }
    return true;
}

bool ScrollablePattern::NeedSplitScroll(OverScrollOffset& overOffsets, int32_t source)
{
    return GreatNotEqual(overOffsets.start, 0.0) && refreshCoordination_ && refreshCoordination_->InCoordination() &&
           !isRefreshInReactive_ &&
           (source == SCROLL_FROM_UPDATE || source == SCROLL_FROM_ANIMATION_SPRING ||
               source == SCROLL_FROM_ANIMATION) &&
           (axis_ == Axis::VERTICAL);
}

RefreshCoordinationMode ScrollablePattern::CoordinateWithRefresh(double& offset, int32_t source, bool isAtTop)
{
    auto coordinationMode = RefreshCoordinationMode::UNKNOWN;
    if (!refreshCoordination_) {
        CreateRefreshCoordination();
    }
    auto overOffsets = GetOverScrollOffset(offset);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && !IsAtTop() && Positive(offset) &&
        NeedSplitScroll(overOffsets, source)) {
        offset = offset - overOffsets.start;
        OnScrollCallback(offset, source);
        isRefreshInReactive_ = true;
        if (refreshCoordination_) {
            refreshCoordination_->OnScrollStart(source == SCROLL_FROM_UPDATE);
        }
    }
    if (IsAtTop() &&
        (Positive(offset) || (Negative(offset) && refreshCoordination_ && refreshCoordination_->IsRefreshInScroll())) &&
        (source == SCROLL_FROM_UPDATE || source == SCROLL_FROM_ANIMATION) && !isRefreshInReactive_ &&
        (axis_ == Axis::VERTICAL)) {
        isRefreshInReactive_ = true;
        if (refreshCoordination_) {
            refreshCoordination_->OnScrollStart(source == SCROLL_FROM_UPDATE);
        }
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
        (refreshCoordination_ && refreshCoordination_->InCoordination()) && source != SCROLL_FROM_UPDATE &&
        isRefreshInReactive_) {
        isRefreshInReactive_ = false;
        refreshCoordination_->OnScrollEnd(0.0f);
    }
    if (refreshCoordination_ && refreshCoordination_->InCoordination() && isRefreshInReactive_) {
        if (!refreshCoordination_->OnScroll(GreatNotEqual(overOffsets.start, 0.0) ? overOffsets.start : offset)) {
            isRefreshInReactive_ = false;
            coordinationMode = RefreshCoordinationMode::SCROLLABLE_SCROLL;
        }
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            coordinationMode = RefreshCoordinationMode::REFRESH_SCROLL;
        } else {
            if (scrollEffect_ && scrollEffect_->IsSpringEffect()) {
                coordinationMode = RefreshCoordinationMode::SCROLLABLE_SCROLL;
            } else {
                coordinationMode = RefreshCoordinationMode::REFRESH_SCROLL;
            }
        }
    }
    return coordinationMode;
}

bool ScrollablePattern::CoordinateWithNavigation(bool isAtTop, bool isDraggedDown, double& offset, int32_t source)
{
    bool reactiveIn = false;
    if (!ProcessAssociatedScroll(offset, source)) {
        return true;
    }

    if ((isAtTop || isDraggedDown) && (source == SCROLL_FROM_UPDATE) && !isReactInParentMovement_ &&
        (axis_ == Axis::VERTICAL)) {
        isReactInParentMovement_ = true;
        ProcessNavBarReactOnStart();
    }

    if (navBarPattern_ && source != SCROLL_FROM_UPDATE && isReactInParentMovement_) {
        isReactInParentMovement_ = false;
        ProcessNavBarReactOnEnd();
    }
    if (isReactInParentMovement_) {
        auto needMove = ProcessNavBarReactOnUpdate(offset);
        if (navBarPattern_ && navBarPattern_->IsTitleModeFree()) {
            reactiveIn = !needMove;
        }
    }
    return reactiveIn;
}

void ScrollablePattern::OnScrollEnd()
{
    // Previous: Sets ScrollablePattern::OnScrollEnd to Scrollable->scrollEndCallback_
    // Scrollable calls scrollEndCallback_ in HandleOverScroll

    // Now: HandleOverScroll moved to ScrollablePattern and renamed HandleScrollVelocity, directly
    // calls OnScrollEnd in ScrollablePattern
    if (isRefreshInReactive_) {
        if (refreshCoordination_) {
            isRefreshInReactive_ = false;
            refreshCoordination_->OnScrollEnd(GetVelocity());
        }
    }
    if (isReactInParentMovement_) {
        ProcessNavBarReactOnEnd();
    }

    OnScrollEndCallback();
    SelectOverlayScrollNotifier::NotifyOnScrollEnd(WeakClaim(this));
}

void ScrollablePattern::AddScrollEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleScrollImpl(static_cast<float>(offset), source);
    };
    auto scrollable = MakeRefPtr<Scrollable>(std::move(scrollCallback), GetAxis());
    scrollable->SetNodeId(host->GetAccessibilityId());
    scrollable->Initialize(host->GetContext());

    // move HandleScroll and HandleOverScroll to ScrollablePattern by setting callbacks to scrollable
    auto handleScroll = [weak = AceType::WeakClaim(this)](
                            float offset, int32_t source, NestedState state) -> ScrollResult {
        auto pattern = weak.Upgrade();
        if (pattern) {
            return pattern->HandleScroll(offset, source, state);
        }
        return {};
    };
    scrollable->SetHandleScrollCallback(std::move(handleScroll));

    auto handleVelocityCallback = [weak = WeakClaim(this)](float velocity) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleScrollVelocity(velocity);
    };
    scrollable->SetHandleVelocityCallback(std::move(handleVelocityCallback));

    auto scrollStart = [weak = WeakClaim(this)](float position) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollStartRecursive(position);
    };
    scrollable->SetOnScrollStartRec(std::move(scrollStart));

    auto scrollEndRec = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEndRecursive();
    };
    scrollable->SetOnScrollEndRec(std::move(scrollEndRec));

    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEnd();
    };
    scrollable->SetScrollEndCallback(std::move(scrollEnd));
    scrollable->SetUnstaticFriction(friction_);

    auto scrollSnap = [weak = WeakClaim(this)](double targetOffset, double velocity) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnScrollSnapCallback(targetOffset, velocity);
    };
    scrollable->SetOnScrollSnapCallback(scrollSnap);

    auto calePredictSnapOffsetCallback = [weak = WeakClaim(this)](float delta) -> std::optional<float> {
        auto pattern = weak.Upgrade();
        std::optional<float> predictSnapOffset;
        CHECK_NULL_RETURN(pattern, predictSnapOffset);
        return pattern->CalePredictSnapOffset(delta);
    };
    scrollable->SetCalePredictSnapOffsetCallback(std::move(calePredictSnapOffsetCallback));

    auto needScrollSnapToSideCallback = [weak = WeakClaim(this)](float delta) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->NeedScrollSnapToSide(delta);
    };
    scrollable->SetNeedScrollSnapToSideCallback(std::move(needScrollSnapToSideCallback));

    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(GetAxis());
    scrollableEvent_->SetScrollable(scrollable);
    gestureHub->AddScrollableEvent(scrollableEvent_);
}

void ScrollablePattern::SetEdgeEffect(EdgeEffect edgeEffect)
{
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollEffect_ && (edgeEffect != scrollEffect_->GetEdgeEffect())) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        scrollEffect_.Reset();
    }
    if (edgeEffect == EdgeEffect::SPRING && !scrollEffect_) {
        auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
        CHECK_NULL_VOID(springEffect);
        springEffect->SetOutBoundaryCallback([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, false);
            return pattern->OutBoundaryCallback();
        });
        // add callback to springEdgeEffect
        SetEdgeEffectCallback(springEffect);
        scrollEffect_ = springEffect;
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
    }
    if (edgeEffect == EdgeEffect::FADE && !scrollEffect_) {
        auto fadeEdgeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::GRAY);
        CHECK_NULL_VOID(fadeEdgeEffect);
        fadeEdgeEffect->SetHandleOverScrollCallback([weakScroll = AceType::WeakClaim(this)]() -> void {
            auto list = weakScroll.Upgrade();
            CHECK_NULL_VOID(list);
            auto host = list->GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        });
        SetEdgeEffectCallback(fadeEdgeEffect);
        fadeEdgeEffect->InitialEdgeEffect();
        scrollEffect_ = fadeEdgeEffect;
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
    }
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID(scrollable);
    scrollable->SetEdgeEffect(edgeEffect);
}

bool ScrollablePattern::HandleEdgeEffect(float offset, int32_t source, const SizeF& size)
{
    bool isAtTop = IsAtTop();
    bool isAtBottom = IsAtBottom();
    // check edgeEffect is not springEffect
    if (scrollEffect_ && scrollEffect_->IsFadeEffect() && (source == SCROLL_FROM_UPDATE ||
        source == SCROLL_FROM_ANIMATION)) {    // handle edge effect
        if ((isAtTop && Positive(offset)) || (isAtBottom && Negative(offset))) {
            scrollEffect_->HandleOverScroll(GetAxis(), -offset, size);
        }
    }
    if (!(scrollEffect_ && scrollEffect_->IsSpringEffect() && (source == SCROLL_FROM_UPDATE ||
        source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING))) {
        if (isAtTop && Positive(offset)) {
            animateOverScroll_ = false;
            return false;
        }
        if (isAtBottom && Negative(offset)) {
            animateOverScroll_ = false;
            return false;
        }
    }
    animateOverScroll_ = (source == SCROLL_FROM_ANIMATION_CONTROLLER) && (isAtTop || isAtBottom);
    return true;
}

void ScrollablePattern::RegisterScrollBarEventTask()
{
    CHECK_NULL_VOID(scrollBar_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = GetGestureHub();
    auto inputHub = GetInputHub();
    CHECK_NULL_VOID(gestureHub);
    CHECK_NULL_VOID(inputHub);
    scrollBar_->SetGestureEvent();
    scrollBar_->SetMouseEvent();
    scrollBar_->SetHoverEvent();
    scrollBar_->SetMarkNeedRenderFunc([weak = AceType::WeakClaim(AceType::RawPtr(host))]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    });
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnScrollCallback(static_cast<float>(offset), source);
    };
    scrollBar_->SetScrollPositionCallback(std::move(scrollCallback));
    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEnd();
    };
    scrollBar_->SetScrollEndCallback(std::move(scrollEnd));
    auto calePredictSnapOffsetCallback = [weak = WeakClaim(this)](float delta) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, std::optional<float>());
        return pattern->CalePredictSnapOffset(delta);
    };
    scrollBar_->SetCalePredictSnapOffsetCallback(std::move(calePredictSnapOffsetCallback));
    auto startScrollSnapMotionCallback = [weak = WeakClaim(this)](float scrollSnapDelta, float scrollSnapVelocity) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StartScrollSnapMotion(scrollSnapDelta, scrollSnapVelocity);
    };
    scrollBar_->SetStartScrollSnapMotionCallback(std::move(startScrollSnapMotionCallback));

    gestureHub->AddTouchEvent(scrollBar_->GetTouchEvent());
    inputHub->AddOnMouseEvent(scrollBar_->GetMouseEvent());
    inputHub->AddOnHoverEvent(scrollBar_->GetHoverEvent());
    CHECK_NULL_VOID(scrollableEvent_);
    scrollableEvent_->SetInBarRegionCallback(
        [weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_))](const PointF& point, SourceType source) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_RETURN(scrollBar, false);
            if (source == SourceType::MOUSE) {
                return scrollBar->InBarHoverRegion(Point(point.GetX(), point.GetY()));
            }
            return scrollBar->InBarTouchRegion(Point(point.GetX(), point.GetY()));
        }
    );
    scrollableEvent_->SetBarCollectTouchTargetCallback([weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_))]
        (const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->OnCollectTouchTarget(coordinateOffset, getEventTargetImpl, result);
        }
    );
}

void ScrollablePattern::SetScrollBar(DisplayMode displayMode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            auto gestureHub = GetGestureHub();
            if (gestureHub) {
                gestureHub->RemoveTouchEvent(scrollBar_->GetTouchEvent());
            }
            scrollBar_.Reset();
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetOpacity(0);
            }
        }
        return;
    }
    DisplayMode oldDisplayMode = DisplayMode::OFF;
    if (!scrollBar_) {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>();
        // set the scroll bar style
        if (GetAxis() == Axis::HORIZONTAL) {
            scrollBar_->SetPositionMode(PositionMode::BOTTOM);
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetPositionMode(PositionMode::BOTTOM);
            }
        }
        RegisterScrollBarEventTask();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        oldDisplayMode = scrollBar_->GetDisplayMode();
    }

    if (oldDisplayMode != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
        if (scrollBarOverlayModifier_ && scrollBar_->IsScrollable()) {
            scrollBarOverlayModifier_->SetOpacity(UINT8_MAX);
        }
        scrollBar_->ScheduleDisappearDelayTask();
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasBorderRadius()) {
        auto borderRadius = renderContext->GetBorderRadius().value();
        if (!(borderRadius == scrollBar_->GetHostBorderRadius())) {
            scrollBar_->SetHostBorderRadius(borderRadius);
            scrollBar_->CalcReservedHeight();
        }
    }
}

void ScrollablePattern::SetScrollBar(const std::unique_ptr<ScrollBarProperty>& property)
{
    if (!property) {
        SetScrollBar(DisplayMode::AUTO);
        return;
    }
    auto displayMode = property->GetScrollBarMode().value_or(DisplayMode::AUTO);
    SetScrollBar(displayMode);
    if (scrollBar_) {
        auto barColor = property->GetScrollBarColor();
        if (barColor) {
            scrollBar_->SetForegroundColor(barColor.value());
        }
        auto barWidth = property->GetScrollBarWidth();
        if (barWidth) {
            scrollBar_->SetInactiveWidth(barWidth.value());
            scrollBar_->SetNormalWidth(barWidth.value());
            scrollBar_->SetActiveWidth(barWidth.value());
            scrollBar_->SetTouchWidth(barWidth.value());
            scrollBar_->SetIsUserNormalWidth(true);
        } else {
            scrollBar_->SetIsUserNormalWidth(false);
        }
    }
}

void ScrollablePattern::UpdateScrollBarRegion(float offset, float estimatedHeight, Size viewPort, Offset viewOffset)
{
    // inner scrollbar, viewOffset is padding offset
    if (scrollBar_) {
        auto mainSize = axis_ == Axis::VERTICAL ? viewPort.Height() : viewPort.Width();
        bool scrollable = GreatNotEqual(estimatedHeight, mainSize) && IsScrollable();
        if (scrollBar_->IsScrollable() != scrollable) {
            scrollBar_->SetScrollable(scrollable);
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetOpacity(scrollable ? UINT8_MAX : 0);
            }
            if (scrollable) {
                scrollBar_->ScheduleDisappearDelayTask();
            }
        }
        Offset scrollOffset = { offset, offset }; // fit for w/h switched.
        scrollBar_->SetIsOutOfBoundary(IsOutOfBoundary());
        scrollBar_->UpdateScrollBarRegion(viewOffset, viewPort, scrollOffset, estimatedHeight);
        scrollBar_->MarkNeedRender();
    }

    // outer scrollbar
    if (scrollBarProxy_) {
        estimatedHeight_ = estimatedHeight - (GetAxis() == Axis::VERTICAL ? viewPort.Height() : viewPort.Width());
        barOffset_ = -offset;
        scrollBarProxy_->NotifyScrollBar(AceType::WeakClaim(this));
    }
}

void ScrollablePattern::SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy)
{
    CHECK_NULL_VOID(scrollBarProxy);
    auto scrollFunction = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (!pattern || pattern->GetAxis() == Axis::NONE) {
                return false;
            }
            return pattern->UpdateCurrentOffset(offset, SCROLL_FROM_BAR);
        }
        return true;
    };
    auto scrollStartCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->OnScrollStartCallback();
        return pattern->OnScrollCallback(static_cast<float>(offset), source);
    };
    auto scrollEndCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEnd();
    };
    auto calePredictSnapOffsetCallback = [weak = WeakClaim(this)](float delta) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, std::optional<float>());
        return pattern->CalePredictSnapOffset(delta);
    };
    auto startScrollSnapMotionCallback = [weak = WeakClaim(this)](float scrollSnapDelta, float scrollSnapVelocity) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StartScrollSnapMotion(scrollSnapDelta, scrollSnapVelocity);
    };
    ScrollableNodeInfo nodeInfo = { AceType::WeakClaim(this), std::move(scrollFunction), std::move(scrollStartCallback),
        std::move(scrollEndCallback), std::move(calePredictSnapOffsetCallback),
        std::move(startScrollSnapMotionCallback) };
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    scrollBarProxy_ = scrollBarProxy;
}

void ScrollablePattern::CreateScrollBarOverlayModifier()
{
    CHECK_NULL_VOID(scrollBar_ && scrollBar_->NeedPaint());
    CHECK_NULL_VOID(!scrollBarOverlayModifier_);
    scrollBarOverlayModifier_ = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
    scrollBarOverlayModifier_->SetRect(scrollBar_->GetActiveRect());
    scrollBarOverlayModifier_->SetPositionMode(scrollBar_->GetPositionMode());
}

void ScrollablePattern::HandleScrollBarOutBoundary(float scrollBarOutBoundaryExtent)
{
    scrollBarOutBoundaryExtent_ = scrollBarOutBoundaryExtent;
    CHECK_NULL_VOID(scrollBar_ && scrollBar_->NeedScrollBar());
    scrollBar_->SetOutBoundary(std::abs(scrollBarOutBoundaryExtent_));
}

void ScrollablePattern::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    nestedScroll_ = nestedOpt;
}

void ScrollablePattern::SetFriction(double friction)
{
    if (LessOrEqual(friction, 0.0)) {
        friction = FRICTION;
    }
    friction_ = friction;
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    scrollable->SetUnstaticFriction(friction_);
}

void ScrollablePattern::GetParentNavigation()
{
    if (navBarPattern_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if ((host->GetTag() != V2::LIST_ETS_TAG) && (host->GetTag() != V2::GRID_ETS_TAG) &&
        (host->GetTag() != V2::SCROLL_ETS_TAG)) {
        return;
    }
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        if ((frameNode->GetTag() == V2::LIST_ETS_TAG) || (frameNode->GetTag() == V2::GRID_ETS_TAG) ||
            (frameNode->GetTag() == V2::SCROLL_ETS_TAG)) {
            break;
        }
        navBarPattern_ = frameNode->GetPattern<NavBarPattern>();
        if (!navBarPattern_) {
            continue;
        }
        return;
    }
    navBarPattern_ = nullptr;
    return;
}

void ScrollablePattern::SetParentScrollable()
{
    if (nestedScroll_.NeedParent()) {
        parent_ = SearchParent();
    } else {
        parent_ = nullptr;
    }
}

void ScrollablePattern::StopAnimate()
{
    if (!IsScrollableStopped()) {
        StopScrollable();
    }
    if (animator_ && !animator_->IsStopped()) {
        animator_->Stop();
    }
}

void ScrollablePattern::ScrollTo(float position)
{
    StopAnimate();
    UpdateCurrentOffset(GetTotalOffset() - position, SCROLL_FROM_JUMP);
}

void ScrollablePattern::AnimateTo(float position, float duration, const RefPtr<Curve>& curve, bool smooth)
{
    TAG_LOGD(AceLogTag::ACE_SCROLLABLE, "The position of the animation is %{public}f, duration is %{public}f",
        position, duration);
    float currVelocity = 0.0f;
    if (!IsScrollableStopped()) {
        CHECK_NULL_VOID(scrollableEvent_);
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_VOID(scrollable);
        currVelocity = -scrollable->GetCurrentVelocity();
        scrollAbort_ = true;
        StopScrollable();
    }
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
        animator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnAnimateStop();
        });
    } else if (!animator_->IsStopped()) {
        if (springMotion_) {
            currVelocity = springMotion_->GetCurrentVelocity();
        }
        scrollAbort_ = true;
        animator_->Stop();
    }
    animator_->ClearInterpolators();

    if (smooth) {
        PlaySpringAnimation(position, DEFAULT_SCROLL_TO_VELOCITY, DEFAULT_SCROLL_TO_MASS,
            DEFAULT_SCROLL_TO_STIFFNESS, DEFAULT_SCROLL_TO_DAMPING);
    } else if (AceType::InstanceOf<InterpolatingSpring>(curve)) {
        auto springCurve = AceType::DynamicCast<InterpolatingSpring>(curve);
        float velocity = springCurve->GetVelocity();
        float mass = springCurve->GetMass();
        float stiffness = springCurve->GetStiffness();
        float damping = springCurve->GetDamping();
        PlaySpringAnimation(position, velocity, mass, stiffness, damping);
    } else if (AceType::InstanceOf<ResponsiveSpringMotion>(curve)) {
        auto springCurve = AceType::DynamicCast<ResponsiveSpringMotion>(curve);
        constexpr float PI = 3.1415926f;
        float tmpStiffness = (2 * PI / springCurve->GetResponse());
        float stiffness = tmpStiffness * tmpStiffness;
        float damping = 4 * PI * springCurve->GetDampingRatio() / springCurve->GetResponse();
        PlaySpringAnimation(position, currVelocity, 1.0f, stiffness, damping);
    } else {
        auto animation = AceType::MakeRefPtr<CurveAnimation<float>>(GetTotalOffset(), position, curve);
        animation->AddListener([weakScroll = AceType::WeakClaim(this), position](float value) {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (!pattern->UpdateCurrentOffset(pattern->GetTotalOffset() - value, SCROLL_FROM_ANIMATION_CONTROLLER)) {
                if ((pattern->IsAtTop() && LessOrEqual(position, pattern->GetTotalOffset())) ||
                    (pattern->IsAtBottom() && GreatOrEqual(position, pattern->GetTotalOffset()))) {
                    pattern->animator_->Stop();
                }
            }
        });
        animator_->AddInterpolator(animation);
        animator_->SetDuration(static_cast<int32_t>(duration));
        animator_->Play();
    }
}

void ScrollablePattern::PlaySpringAnimation(
    float position, float velocity, float mass, float stiffness, float damping)
{
    auto start = GetTotalOffset();
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
    AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping);
    if (!springMotion_) {
        const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
            AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping);
        springMotion_ = AceType::MakeRefPtr<SpringMotion>(start, position, velocity, DEFAULT_OVER_SPRING_PROPERTY);
        CHECK_NULL_VOID(scrollableEvent_);
        scrollableEvent_->SetAnimateVelocityCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_RETURN(pattern, 0.0f);
            CHECK_NULL_RETURN(pattern->springMotion_, 0.0f);
            CHECK_NULL_RETURN(pattern->animator_, 0.0f);
            auto velocity = pattern->animator_->IsStopped() ? 0.0f : pattern->springMotion_->GetCurrentVelocity();
            return velocity;
        });
    } else {
        springMotion_->Reset(start, position, velocity, DEFAULT_OVER_SPRING_PROPERTY);
        springMotion_->ClearListeners();
    }
    springMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double position) {
        auto pattern = weakScroll.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->UpdateCurrentOffset(pattern->GetTotalOffset() - position, SCROLL_FROM_ANIMATION_CONTROLLER)) {
            pattern->animator_->Stop();
        }
    });
    animator_->PlayMotion(springMotion_);
}

void ScrollablePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
    host->GetRenderContext()->UpdateClipEdge(true);
}

void ScrollablePattern::UninitMouseEvent()
{
    if (!mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    mouseEventHub->RemoveOnMouseEvent(mouseEvent_);
    ClearMultiSelect();
    ClearInvisibleItemsSelectedStatus();
    isMouseEventInit_ = false;
}

void ScrollablePattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto mouseEventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(mouseEventHub);
    if (!mouseEvent_) {
        auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->HandleMouseEventWithoutKeyboard(info);
            }
        };
        mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    }
    mouseEventHub->AddOnMouseEvent(mouseEvent_);
    isMouseEventInit_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetNotifyInDraggedCallback([wp = WeakClaim(this)]() {
        auto pattern = wp.Upgrade();
        if (pattern && pattern->mousePressed_) {
            pattern->OnMouseRelease();
        }
    });
}

void ScrollablePattern::ClearInvisibleItemsSelectedStatus()
{
    for (auto& item : itemToBeSelected_) {
        item.second.FireSelectChangeEvent(false);
    }
    itemToBeSelected_.clear();
}

void ScrollablePattern::HandleInvisibleItemsSelectedStatus(const RectF& selectedZone)
{
    auto newRect = selectedZone;
    auto startMainOffset = mouseStartOffset_.GetMainOffset(axis_);
    auto endMainOffset = mouseEndOffset_.GetMainOffset(axis_);
    SelectDirection oldDirection = selectDirection_;
    if (LessNotEqual(startMainOffset, endMainOffset)) {
        selectDirection_ = SELECT_DOWN;
        if (axis_ == Axis::VERTICAL) {
            newRect.SetOffset(OffsetF(selectedZone.Left(), totalOffsetOfMousePressed_));
        } else {
            newRect.SetOffset(OffsetF(totalOffsetOfMousePressed_, selectedZone.Top()));
        }
    } else {
        selectDirection_ = SELECT_UP;
        if (axis_ == Axis::VERTICAL) {
            newRect.SetOffset(
                OffsetF(selectedZone.Left(), totalOffsetOfMousePressed_ - (startMainOffset - endMainOffset)));
        } else {
            newRect.SetOffset(
                OffsetF(totalOffsetOfMousePressed_ - (startMainOffset - endMainOffset), selectedZone.Top()));
        }
    }
    oldDirection = oldDirection == SELECT_NONE ? selectDirection_ : oldDirection;

    for (auto& item : itemToBeSelected_) {
        item.second.FireSelectChangeEvent(newRect.IsIntersectWith(item.second.rect));
    }

    if (oldDirection != selectDirection_) {
        itemToBeSelected_.clear();
    }
}

void ScrollablePattern::HandleMouseEventWithoutKeyboard(const MouseInfo& info)
{
    if (info.GetButton() != MouseButton::LEFT_BUTTON) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsDragged()) {
        if (mousePressed_) {
            OnMouseRelease();
        }
        return;
    }

    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    if (info.GetAction() == MouseAction::PRESS) {
        if (!IsItemSelected(info)) {
            ClearMultiSelect();
            ClearInvisibleItemsSelectedStatus();
        }
        mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        lastMouseStart_ = mouseStartOffset_;
        mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        mousePressOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        totalOffsetOfMousePressed_ = mousePressOffset_.GetMainOffset(axis_) + GetTotalOffset();
        mousePressed_ = true;
        // do not select when click
    } else if (info.GetAction() == MouseAction::MOVE) {
        if (!mousePressed_) {
            return;
        }
        lastMouseMove_ = info;
        auto delta = OffsetF(mouseOffsetX, mouseOffsetY) - mousePressOffset_;
        if (Offset(delta.GetX(), delta.GetY()).GetDistance() > DEFAULT_PAN_DISTANCE.ConvertToPx()) {
            mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
            // avoid large select zone
            LimitMouseEndOffset();
            auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
            MultiSelectWithoutKeyboard(selectedZone);
            HandleInvisibleItemsSelectedStatus(selectedZone);
        }
        SelectWithScroll();
    } else if (info.GetAction() == MouseAction::RELEASE) {
        OnMouseRelease();
    }
}

void ScrollablePattern::SelectWithScroll()
{
    if (!IsScrollable()) {
        return;
    }
    auto offset = GetOutOfScrollableOffset();
    if (NearZero(offset)) {
        return;
    }

    if (AnimateRunning()) {
        return;
    }
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(PipelineBase::GetCurrentContext());
        animator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnAnimateStop();
        });
    } else if (!animator_->IsStopped()) {
        scrollAbort_ = true;
        animator_->Stop();
    }

    if (!selectMotion_) {
        selectMotion_ = AceType::MakeRefPtr<SelectMotion>(offset, [weak = WeakClaim(this)]() -> bool {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, true);
            return pattern->ShouldSelectScrollBeStopped();
        });
        selectMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double offset) {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateCurrentOffset(offset, SCROLL_FROM_AXIS);
            pattern->UpdateMouseStart(offset);
        });
    } else {
        offset = GetOffsetWithLimit(mouseStartOffset_.GetMainOffset(axis_), offset);
        selectMotion_->Reset(offset);
    }

    animator_->PlayMotion(selectMotion_);
}

void ScrollablePattern::OnMouseRelease()
{
    mouseStartOffset_.Reset();
    lastMouseStart_.Reset();
    mouseEndOffset_.Reset();
    mousePressed_ = false;
    ClearSelectedZone();
    itemToBeSelected_.clear();
    lastMouseMove_.SetLocalLocation(Offset::Zero());
}

void ScrollablePattern::ClearSelectedZone()
{
    DrawSelectedZone(RectF());
}

RectF ScrollablePattern::ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset)
{
    RectF selectedZone;
    if (startOffset.GetX() <= endOffset.GetX()) {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom right
            selectedZone = RectF(startOffset.GetX(), startOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top right
            selectedZone = RectF(startOffset.GetX(), endOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    } else {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom left
            selectedZone = RectF(endOffset.GetX(), startOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top left
            selectedZone = RectF(endOffset.GetX(), endOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    }

    return selectedZone;
}

void ScrollablePattern::DrawSelectedZone(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(selectedZone, SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

void ScrollablePattern::MarkSelectedItems()
{
    if (multiSelectable_ && mousePressed_) {
        auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
        if (!selectedZone.IsEmpty()) {
            MultiSelectWithoutKeyboard(selectedZone);
            HandleInvisibleItemsSelectedStatus(selectedZone);
        }
    }
}

bool ScrollablePattern::ShouldSelectScrollBeStopped()
{
    if (!mousePressed_) {
        return true;
    }
    auto offset = GetOutOfScrollableOffset();
    if (NearZero(offset)) {
        return true;
    }

    offset = GetOffsetWithLimit(lastMouseStart_.GetMainOffset(axis_), offset);
    if (axis_ == Axis::VERTICAL) {
        lastMouseStart_.AddY(offset);
    } else {
        lastMouseStart_.AddX(offset);
    }
    if (selectMotion_) {
        selectMotion_->Reset(offset);
    }
    return false;
};

void ScrollablePattern::UpdateMouseStart(float offset)
{
    if (axis_ == Axis::VERTICAL) {
        mouseStartOffset_.AddY(offset);
    } else {
        mouseStartOffset_.AddX(offset);
    }
}

float ScrollablePattern::GetOutOfScrollableOffset() const
{
    auto offset = 0.0f;
    auto mouseMainOffset = static_cast<float>(
        axis_ == Axis::VERTICAL ? lastMouseMove_.GetLocalLocation().GetY() : lastMouseMove_.GetLocalLocation().GetX());
    auto hostSize = GetHostFrameSize();
    CHECK_NULL_RETURN(hostSize.has_value(), offset);
    auto mainTop = 0.0f;
    auto mainBottom = hostSize->MainSize(axis_);
    if (GreatOrEqual(mouseMainOffset, mainTop) && LessOrEqual(mouseMainOffset, mainBottom)) {
        return offset;
    }
    if (GreatNotEqual(mouseMainOffset, mainBottom)) {
        if (IsAtBottom()) {
            return offset;
        }
        offset = mainBottom - mouseMainOffset;
    }
    if (LessNotEqual(mouseMainOffset, mainTop)) {
        if (IsAtTop()) {
            return offset;
        }
        offset = mainTop - mouseMainOffset;
    }
    return offset;
}

// avoid start position move when offset is bigger then item height
float ScrollablePattern::GetOffsetWithLimit(float position, float offset) const
{
    auto limitedOffset = offset;
    if (Positive(offset)) {
        if (LessNotEqual(totalOffsetOfMousePressed_, position + offset)) {
            limitedOffset = totalOffsetOfMousePressed_ - position;
        }
    } else {
        auto hostSize = GetHostFrameSize();
        CHECK_NULL_RETURN(hostSize.has_value(), true);
        auto minStartOffset = -(GetTotalHeight() - totalOffsetOfMousePressed_ - hostSize->MainSize(axis_));
        if (GreatNotEqual(minStartOffset, position + offset)) {
            limitedOffset = minStartOffset - position;
        }
    }
    return limitedOffset;
}

void ScrollablePattern::LimitMouseEndOffset()
{
    float limitedMainOffset = -1.0f;
    float limitedCrossOffset = -1.0f;
    auto hostSize = GetHostFrameSize();
    auto mainSize = hostSize->MainSize(axis_);
    auto crossSize = hostSize->CrossSize(axis_);
    auto mainOffset = mouseEndOffset_.GetMainOffset(axis_);
    auto crossOffset = mouseEndOffset_.GetCrossOffset(axis_);
    if (LessNotEqual(mainOffset, 0.0f)) {
        limitedMainOffset = 0.0f;
    }
    if (GreatNotEqual(mainOffset, mainSize)) {
        limitedMainOffset = mainSize;
    }
    if (LessNotEqual(crossOffset, 0.0f)) {
        limitedCrossOffset = 0.0f;
    }
    if (GreatNotEqual(crossOffset, crossSize)) {
        limitedCrossOffset = crossSize;
    }

    if (axis_ == Axis::VERTICAL) {
        mouseEndOffset_.SetX(LessNotEqual(limitedCrossOffset, 0.0f) ? mouseEndOffset_.GetX() : limitedCrossOffset);
        mouseEndOffset_.SetY(LessNotEqual(limitedMainOffset, 0.0f) ? mouseEndOffset_.GetY() : limitedMainOffset);
    } else {
        mouseEndOffset_.SetX(LessNotEqual(limitedMainOffset, 0.0f) ? mouseEndOffset_.GetX() : limitedMainOffset);
        mouseEndOffset_.SetY(LessNotEqual(limitedCrossOffset, 0.0f) ? mouseEndOffset_.GetY() : limitedCrossOffset);
    }
}

bool ScrollablePattern::ProcessAssociatedScroll(double offset, int32_t source)
{
    if (navBarPattern_) {
        if (source == SCROLL_FROM_START) {
            navBarPattern_->ResetAssociatedScroll();
        } else if ((source == SCROLL_FROM_UPDATE) || (source == SCROLL_FROM_ANIMATION) ||
                   (source == SCROLL_FROM_ANIMATION_SPRING)) {
            if (IsAtTop()) {
                auto host = GetHost();
                return navBarPattern_->UpdateAssociatedScrollOffset(offset, host);
            }
        }
    }
    return true;
}

bool ScrollablePattern::HandleScrollImpl(float offset, int32_t source)
{
    // Previous: Set HandleScrollImpl to Scrollable->callback_
    // Scrollable::HandleScroll calls callback_ through UpdateScrollPosition

    // Now: HandleScroll moved to ScrollablePattern, directly call HandleScrollImpl in
    // ScrollablePattern::HandleScroll
    if (!OnScrollPosition(offset, source)) {
        return false;
    }
    auto result = OnScrollCallback(offset, source);
    SelectOverlayScrollNotifier::NotifyOnScrollCallback(WeakClaim(this), offset, source);
    return result;
}

void ScrollablePattern::NotifyMoved(bool value)
{
    CHECK_NULL_VOID(scrollableEvent_);
    auto&& scroll = scrollableEvent_->GetScrollable();
    if (scroll) {
        scroll->SetMoved(value);
    }
}

void ScrollablePattern::ProcessSpringEffect(float velocity)
{
    CHECK_NULL_VOID(InstanceOf<ScrollSpringEffect>(scrollEffect_));
    if (!OutBoundaryCallback() && !GetCanOverScroll()) {
        return;
    }
    scrollEffect_->ProcessScrollOver(velocity);
}

void ScrollablePattern::SetCanOverScroll(bool val)
{
    CHECK_NULL_VOID(scrollableEvent_);
    auto&& scrollable = scrollableEvent_->GetScrollable();
    if (scrollable) {
        scrollable->SetCanOverScroll(val);
    }
}

bool ScrollablePattern::GetCanOverScroll() const
{
    CHECK_NULL_RETURN(scrollableEvent_, true);
    auto&& scrollable = scrollableEvent_->GetScrollable();
    if (scrollable) {
        return scrollable->CanOverScroll();
    }
    return true;
}

EdgeEffect ScrollablePattern::GetEdgeEffect() const
{
    CHECK_NULL_RETURN(scrollEffect_, EdgeEffect::NONE);
    return scrollEffect_->GetEdgeEffect();
}

ScrollResult ScrollablePattern::HandleScrollParentFirst(float& offset, int32_t source, NestedState state)
{
    auto parent = parent_.Upgrade();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        if (GetEdgeEffect() == EdgeEffect::NONE) {
            return parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL);
        }
        ExecuteScrollFrameBegin(offset, scrollState);
        return { 0, true };
    }
    auto result = parent->HandleScroll(offset, source, NestedState::CHILD_SCROLL);
    offset = result.remain;
    if (NearZero(offset)) {
        SetCanOverScroll(!InstanceOf<ScrollablePattern>(parent));
        return { 0, false };
    }
    float allOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = std::abs(offset) < std::abs(allOffset) ? allOffset - offset : 0;
    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    remainOffset += overOffset;
    if (NearZero(remainOffset)) {
        SetCanOverScroll(false);
        return { 0, false };
    }
    if (state == NestedState::CHILD_SCROLL) {
        offset -= overOffset;
        SetCanOverScroll(false);
        return { remainOffset, !NearZero(overOffset) };
    }
    if (GetEdgeEffect() == EdgeEffect::NONE) {
        result = parent->HandleScroll(remainOffset, source, NestedState::CHILD_OVER_SCROLL);
    }
    SetCanOverScroll(!NearZero(overOffset) || (NearZero(offset) && result.reachEdge));
    return { 0, GetCanOverScroll() };
}

ScrollResult ScrollablePattern::HandleScrollSelfFirst(float& offset, int32_t source, NestedState state)
{
    auto parent = parent_.Upgrade();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        auto result = parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL);
        if (NearZero(result.remain)) {
            offset = 0;
            return result;
        }
        ExecuteScrollFrameBegin(offset, scrollState);
        if (GetEdgeEffect() == EdgeEffect::NONE) {
            return result;
        }
        return { 0, true };
    }
    float allOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = std::abs(offset) < std::abs(allOffset) ? allOffset - offset : 0;
    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    if (NearZero(overOffset) && NearZero(remainOffset)) {
        SetCanOverScroll(false);
        return { 0, false };
    }
    offset -= overOffset;
    auto result = parent->HandleScroll(overOffset + remainOffset, source, NestedState::CHILD_SCROLL);
    if (NearZero(result.remain)) {
        SetCanOverScroll(!InstanceOf<ScrollablePattern>(parent));
        return { 0, false };
    }
    if (state == NestedState::CHILD_SCROLL) {
        SetCanOverScroll(false);
        return result;
    }
    // triggering overScroll, parent always handle it first
    auto overRes = parent->HandleScroll(result.remain, source, NestedState::CHILD_OVER_SCROLL);
    offset += std::abs(overOffset) < std::abs(result.remain) ? overOffset : overRes.remain;
    SetCanOverScroll((!NearZero(overOffset) || NearZero(offset)) && overRes.reachEdge);
    return { 0, GetCanOverScroll() };
}

ScrollResult ScrollablePattern::HandleScrollSelfOnly(float& offset, int32_t source, NestedState state)
{
    float allOffset = offset;
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = allOffset - offset;
    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    remainOffset += overOffset;
    if (NearZero(remainOffset)) {
        SetCanOverScroll(false);
        return { 0, false };
    }
    bool canOverScroll = false;
    if (state == NestedState::CHILD_SCROLL) {
        offset -= overOffset;
    } else if (state == NestedState::GESTURE) {
        canOverScroll = !NearZero(overOffset) && GetEdgeEffect() != EdgeEffect::NONE;
    } else if (GetEdgeEffect() != EdgeEffect::NONE) {
        remainOffset = 0;
    }
    SetCanOverScroll(canOverScroll);
    return { remainOffset, !NearZero(overOffset) };
}

ScrollResult ScrollablePattern::HandleScrollParallel(float& offset, int32_t source, NestedState state)
{
    auto remainOffset = 0.0;
    auto parent = parent_.Upgrade();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        if (GetEdgeEffect() == EdgeEffect::NONE) {
            auto result = parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL);
            remainOffset = result.remain;
            offset = 0;
        } else {
            ExecuteScrollFrameBegin(offset, scrollState);
        }
        return { remainOffset, true };
    }

    bool canOverScroll = false;
    float parentOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto result = parent->HandleScroll(parentOffset, source, NestedState::CHILD_SCROLL);

    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    if (!NearZero(overOffset) && result.reachEdge) {
        if (state == NestedState::CHILD_SCROLL) {
            remainOffset = overOffset;
            offset = offset - overOffset;
        } else if (GetEdgeEffect() == EdgeEffect::NONE) {
            parent->HandleScroll(result.remain, source, NestedState::CHILD_OVER_SCROLL);
            canOverScroll = true;
            offset = offset - overOffset;
        } else {
            canOverScroll = true;
        }
    } else if (!NearZero(overOffset)) {
        offset = offset - overOffset;
    }
    SetCanOverScroll(canOverScroll);
    return { remainOffset, !NearZero(overOffset) && result.reachEdge };
}

ScrollResult ScrollablePattern::HandleScroll(float offset, int32_t source, NestedState state)
{
    ScrollResult result = { 0, false };
    auto parent = parent_.Upgrade();
    auto overOffsets = GetOverScrollOffset(offset);
    float backOverOffset = offset > 0 ? overOffsets.end : overOffsets.start;
    if (NearZero(offset) || !NearZero(backOverOffset)) {
        ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
        ExecuteScrollFrameBegin(offset, scrollState);
    } else if (parent && ((offset < 0 && nestedScroll_.forward == NestedScrollMode::PARENT_FIRST) ||
                             (offset > 0 && nestedScroll_.backward == NestedScrollMode::PARENT_FIRST))) {
        result = HandleScrollParentFirst(offset, source, state);
    } else if (parent && ((offset < 0 && nestedScroll_.forward == NestedScrollMode::SELF_FIRST) ||
                             (offset > 0 && nestedScroll_.backward == NestedScrollMode::SELF_FIRST))) {
        result = HandleScrollSelfFirst(offset, source, state);
    } else if (parent && ((offset < 0 && nestedScroll_.forward == NestedScrollMode::PARALLEL) ||
                             (offset > 0 && nestedScroll_.backward == NestedScrollMode::PARALLEL))) {
        result = HandleScrollParallel(offset, source, state);
    } else {
        result = HandleScrollSelfOnly(offset, source, state);
    }
    bool moved = HandleScrollImpl(offset, source);
    NotifyMoved(moved);
    return result;
}

bool ScrollablePattern::HandleScrollVelocity(float velocity)
{
    auto parent = parent_.Upgrade();
    if (!parent || !nestedScroll_.NeedParent()) {
        if (GetEdgeEffect() == EdgeEffect::SPRING) {
            // trigger onScrollEnd later, when spring animation finishes
            ProcessSpringEffect(velocity);
            return true;
        }
        OnScrollEnd();
        return false;
    }
    // parent handle over scroll first
    if ((velocity < 0 && (nestedScroll_.forward == NestedScrollMode::SELF_FIRST)) ||
        (velocity > 0 && (nestedScroll_.backward == NestedScrollMode::SELF_FIRST)) ||
        !InstanceOf<ScrollablePattern>(parent)) {
        if (parent->HandleScrollVelocity(velocity)) {
            OnScrollEnd();
            return true;
        }
        if (GetEdgeEffect() == EdgeEffect::SPRING) {
            ProcessSpringEffect(velocity);
            return true;
        }
    }

    // self handle over scroll first
    if (GetEdgeEffect() == EdgeEffect::SPRING) {
        ProcessSpringEffect(velocity);
        return true;
    }
    OnScrollEnd();
    return parent->HandleScrollVelocity(velocity);
}

void ScrollablePattern::ExecuteScrollFrameBegin(float& mainDelta, ScrollState state)
{
    auto context = PipelineContext::GetCurrentContext();
    if (!context || !scrollFrameBeginCallback_) {
        return;
    }

    auto offset = Dimension(mainDelta / context->GetDipScale(), DimensionUnit::VP);
    auto scrollRes = scrollFrameBeginCallback_(-offset, state);
    mainDelta = -context->NormalizeToPx(scrollRes.offset);
}

void ScrollablePattern::OnScrollStartRecursive(float position)
{
    HandleScrollImpl(position, SCROLL_FROM_START);
    auto parent = parent_.Upgrade();
    if (parent && nestedScroll_.NeedParent()) {
        parent->OnScrollStartRecursive(position);
    }
}

void ScrollablePattern::OnScrollEndRecursive()
{
    OnScrollEnd();
    auto parent = parent_.Upgrade();
    if (parent && nestedScroll_.NeedParent()) {
        parent->OnScrollEndRecursive();
    }
}

float ScrollablePattern::GetVelocity() const
{
    float velocity = 0.0f;
    CHECK_NULL_RETURN(scrollableEvent_, velocity);
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_RETURN(scrollable, velocity);
    velocity = scrollable->GetCurrentVelocity();
    return velocity;
}
} // namespace OHOS::Ace::NG
