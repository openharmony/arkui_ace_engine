/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "core/components/scroll/render_scroll.h"

#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t SCROLL_NONE = 0;
constexpr int32_t SCROLL_TOUCH_DOWN = 1;
constexpr int32_t SCROLL_TOUCH_UP = 2;
constexpr double SCROLL_RATIO = 0.52;
constexpr float SCROLL_BY_SPEED = 250.0f; // move 250 pixels per second
constexpr double UNIT_CONVERT = 1000.0;   // 1s convert to 1000ms
constexpr double ROTATE_FACTOR = -1.0;    // pixels factor per angle

} // namespace

RenderScroll::RenderScroll() : RenderNode(true)
{
    Initialize();
}

RenderScroll::~RenderScroll()
{
    if (scrollBarProxy_) {
        scrollBarProxy_->UnRegisterScrollableNode(AceType::WeakClaim(this));
    }
}

void RenderScroll::Initialize()
{
    touchRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
    touchRecognizer_->SetOnTouchCancel([weakItem = AceType::WeakClaim(this)](const TouchEventInfo&) {
        auto item = weakItem.Upgrade();
        if (!item) {
            return;
        }
        // check out of boundary
        if (!item->IsOutOfBoundary()) {
            return;
        }
        auto scrollEffect = item->scrollEffect_;
        if (scrollEffect) {
            scrollEffect->ProcessScrollOver(0.0);
        }
    });
}

bool RenderScroll::ValidateOffset(int32_t source)
{
    if (mainScrollExtent_ <= GetMainSize(viewPort_)) {
        return true;
    }

    outBoundaryExtent_ = 0.0;
    scrollBarOutBoundaryExtent_ = 0.0;

    // restrict position between top and bottom
    if (!scrollEffect_ || scrollEffect_->IsRestrictBoundary() || source == SCROLL_FROM_JUMP ||
        source == SCROLL_FROM_BAR || source == SCROLL_FROM_ROTATE || refreshParent_.Upgrade()) {
        if (axis_ == Axis::HORIZONTAL) {
            currentOffset_.SetX(std::clamp(currentOffset_.GetX(), 0.0, mainScrollExtent_ - viewPort_.Width()));
        } else {
            // Refresh support spring when pulling up.
#ifdef WEARABLE_PRODUCT
            if (refreshParent_.Upgrade() &&
                GetMainOffset(currentOffset_) >= (mainScrollExtent_ - GetMainSize(viewPort_)) && ReachMaxCount()) {
                scrollBarOutBoundaryExtent_ = GetMainOffset(currentOffset_) -
                    (mainScrollExtent_ - GetMainSize(viewPort_));
            } else {
                currentOffset_.SetY(std::clamp(currentOffset_.GetY(), 0.0, mainScrollExtent_ - viewPort_.Height()));
            }
#else
            currentOffset_.SetY(std::clamp(currentOffset_.GetY(), 0.0, mainScrollExtent_ - viewPort_.Height()));
#endif
        }
    } else {
        if (GetMainOffset(currentOffset_) < 0) {
            outBoundaryExtent_ = -GetMainOffset(currentOffset_);
            scrollBarOutBoundaryExtent_ = -GetMainOffset(currentOffset_);
        } else if (GetMainOffset(currentOffset_) >= (mainScrollExtent_ - GetMainSize(viewPort_)) &&
            ReachMaxCount()) {
            scrollBarOutBoundaryExtent_ =
            GetMainOffset(currentOffset_) - (mainScrollExtent_ - GetMainSize(viewPort_));
        }
        HandleScrollBarOutBoundary();
    }

    axis_ == Axis::HORIZONTAL ? currentOffset_.SetY(0.0) : currentOffset_.SetX(0.0);
    return true;
}

void RenderScroll::HandleScrollBarOutBoundary()
{
    if (scrollBar_ && scrollBar_->NeedScrollBar()) {
        scrollBar_->SetOutBoundary(std::abs(scrollBarOutBoundaryExtent_));
    }
}

void RenderScroll::HandleScrollPosition(double scrollX, double scrollY, int32_t scrollState) const
{
    if (!positionController_) {
        LOGW("positionController is null");
        return;
    }

    if (GetMainOffset(currentOffset_) > 0.0 &&
        GetMainOffset(currentOffset_) < mainScrollExtent_ - GetMainSize(viewPort_)) {
        positionController_->SetMiddle();
    }

    positionController_->HandleScrollEvent(
        std::make_shared<ScrollEventInfo>(ScrollEvent::SCROLL_POSITION, scrollX, scrollY, scrollState));
}

bool RenderScroll::HandleCrashBottom()
{
    if (positionController_) {
        positionController_->SetBottom();
        positionController_->HandleScrollEvent(
            std::make_shared<ScrollEventInfo>(ScrollEvent::SCROLL_BOTTOM, 0.0, 0.0, -1));
    }
    if (axis_ == Axis::HORIZONTAL) {
        OnReachEnd();
    } else {
        OnReachBottom();
    }
    return false;
}

bool RenderScroll::HandleCrashTop()
{
    if (positionController_) {
        positionController_->SetTop();
        positionController_->HandleScrollEvent(
            std::make_shared<ScrollEventInfo>(ScrollEvent::SCROLL_TOP, 0.0, 0.0, -1));
    }
    if (axis_ == Axis::HORIZONTAL) {
        OnReachStart();
    } else {
        OnReachTop();
    }
    return false;
}

bool RenderScroll::UpdateOffset(Offset& delta, int32_t source)
{
    if (source == SCROLL_FROM_ROTATE) {
        isFromRotate_ = true;
    } else {
        isFromRotate_ = false;
    }
    if (!scrollable_->Available()) {
        return false;
    }
    if (delta.IsZero()) {
        return false;
    }
    if (IsAtTop() && HandleRefreshEffect(-delta.GetY(), source, currentOffset_.GetY())) {
        return true;
    }
    if ((IsAtBottom() && GetMainOffset(delta) > 0.0) || (IsAtTop() && GetMainOffset(delta) < 0.0)) {
        if (!scrollEffect_) {
            return false;
        }
        if (scrollEffect_->IsNoneEffect()) {
            return false;
        }
    }
    if (!ScrollPageCheck(delta, source)) {
        return false;
    }
    if (GetMainOffset(currentOffset_) <= 0.0) {
        if (scrollable_->RelatedScrollEventDoing(delta)) {
            return false;
        }
    }
    if (scrollBar_ && scrollBar_->NeedScrollBar()) {
        scrollBar_->SetOutBoundary(std::abs(scrollBarOutBoundaryExtent_));
        scrollBar_->SetActive(SCROLL_FROM_CHILD != source);
    }
    currentOffset_ += delta;
    currentDeltaInMain_ += GetMainOffset(delta);
    // handle edge effect
    HandleScrollEffect();

    if (!ValidateOffset(source)) {
        currentOffset_ = currentOffset_ - delta;
        return false;
    }

    bool next = true;
    Offset correctedDelta = currentOffset_ - lastOffset_;
    if (!correctedDelta.IsZero()) {
        int32_t touchState = SCROLL_NONE;
        if (source == SCROLL_FROM_UPDATE) {
            touchState = SCROLL_TOUCH_DOWN;
        } else if (source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
            touchState = SCROLL_TOUCH_UP;
        }
        HandleScrollPosition(correctedDelta.GetX(), correctedDelta.GetY(), touchState);

        if (IsCrashTop()) {
            // scroll to top
            next = HandleCrashTop();
        } else if (IsCrashBottom()) {
            // scroll to bottom
            next = HandleCrashBottom();
        }
        if (scrollEffect_ && !scrollEffect_->IsRestrictBoundary()) {
            next = true;
            MarkNeedPredictLayout();
        }
    } else {
        next = false;
    }

    lastOffset_ = currentOffset_;
    currentBottomOffset_ = axis_ == Axis::VERTICAL ? currentOffset_ + Offset(0.0, viewPort_.Height())
                                                   : currentOffset_ + Offset(viewPort_.Width(), 0.0);
    correctedDelta_ = correctedDelta;
    MarkNeedLayout(true);
    return next;
}

void RenderScroll::HandleScrollEffect()
{
    // handle edge effect
    if (scrollEffect_) {
        overScroll_ = scrollEffect_->CalculateOverScroll(GetMainOffset(lastOffset_), ReachMaxCount());
        if (!NearZero(overScroll_)) {
            scrollEffect_->HandleOverScroll(axis_, overScroll_, viewPort_);
        }
    }
}

bool RenderScroll::IsCrashTop()
{
    double current = GetMainOffset(currentOffset_);
    double last = GetMainOffset(lastOffset_);
    bool scrollUpToReachTop = GreatNotEqual(last, 0.0) && LessOrEqual(current, 0.0);
    bool scrollDownToReachTop = LessNotEqual(last, 0.0) && GreatOrEqual(current, 0.0);
    return scrollUpToReachTop || scrollDownToReachTop;
}

bool RenderScroll::IsCrashBottom()
{
    double maxExtent = mainScrollExtent_ - GetMainSize(viewPort_);
    double current = GetMainOffset(currentOffset_);
    double last = GetMainOffset(lastOffset_);
    bool scrollDownToReachEnd = LessNotEqual(last, maxExtent) && GreatOrEqual(current, maxExtent);
    bool scrollUpToReachEnd = GreatNotEqual(last, maxExtent) && LessOrEqual(current, maxExtent);
    return (scrollUpToReachEnd || scrollDownToReachEnd) && ReachMaxCount();
}

bool RenderScroll::CanScrollVertically(const Offset& delta)
{
    if (axis_ != Axis::VERTICAL) {
        return false;
    }

    if (delta.IsZero()) {
        return false;
    }
    Offset currentOffset = currentOffset_ + delta;

    if (currentOffset.GetY() < 0.0) {
        currentOffset.SetY(0.0);
    } else if (currentOffset.GetY() > mainScrollExtent_ - viewPort_.Height()) {
        currentOffset.SetY(mainScrollExtent_ - viewPort_.Height());
    }

    if (mainScrollExtent_ <= GetMainSize(viewPort_)) {
        return false;
    }

    bool next = true;
    Offset correctedDelta = currentOffset - lastOffset_;
    if (!correctedDelta.IsZero()) {
        double mainOffset = GetMainOffset(currentOffset);
        if (NearZero(mainOffset)) {
            // scroll to top
            next = false;
        } else if (NearEqual(mainOffset, mainScrollExtent_ - GetMainSize(viewPort_)) && ReachMaxCount()) {
            // scroll to bottom
            next = false;
        }
    } else {
        next = false;
    }
    return next;
}

bool RenderScroll::ScrollPageCheck(Offset& delta, int32_t source)
{
    if (source == SCROLL_FROM_ANIMATION_SPRING || source == SCROLL_FROM_BAR) {
        return true;
    }
    if (axis_ != Axis::VERTICAL) {
        return true;
    }
    if (scrollPage_) {
        if (delta.GetY() > 0.0) {
            // scroll up
            bool selfCanScroll = RenderNode::ScrollPageByChild(delta, SCROLL_FROM_CHILD);
            if (!selfCanScroll) {
                return false;
            }
        } else {
            // scroll down
            if (!CanScrollVertically(delta)) {
                bool selfCanScroll = RenderNode::ScrollPageByChild(delta, SCROLL_FROM_CHILD);
                if (!selfCanScroll) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool RenderScroll::ScrollPageByChild(Offset& delta, int32_t source)
{
    // scroll up
    if (delta.GetY() > 0.0) {
        bool selfCanScroll = RenderNode::ScrollPageByChild(delta, source);
        if (selfCanScroll) {
            AdjustOffset(delta, source);
            return !UpdateOffset(delta, source);
        }
        return false;
    } else {
        // scroll down
        AdjustOffset(delta, source);
        if (UpdateOffset(delta, source)) {
            return false;
        } else {
            return RenderNode::ScrollPageByChild(delta, source);
        }
    }
}

bool RenderScroll::IsOutOfBottomBoundary()
{
    return GreatOrEqual(GetMainOffset(currentOffset_), (mainScrollExtent_ - GetMainSize(viewPort_))) &&
                       ReachMaxCount();
}

bool RenderScroll::IsOutOfTopBoundary()
{
    return LessOrEqual(GetMainOffset(currentOffset_), 0.0);
}

bool RenderScroll::IsOutOfBoundary()
{
    return (IsOutOfTopBoundary() || IsOutOfBottomBoundary());
}

void RenderScroll::AdjustOffset(Offset& delta, int32_t source)
{
    if (delta.IsZero() || source == SCROLL_FROM_ANIMATION || source == SCROLL_FROM_ANIMATION_SPRING) {
        return;
    }

    double viewPortSize = GetMainSize(viewPort_);
    double offset = GetMainOffset(delta);
    if (NearZero(viewPortSize) || NearZero(offset)) {
        return;
    }

    double maxScrollExtent = mainScrollExtent_ - viewPortSize;
    double overscrollPastStart = 0.0;
    double overscrollPastEnd = 0.0;
    double overscrollPast = 0.0;
    bool easing = false;
    overscrollPastStart = std::max(-GetCurrentPosition(), 0.0);
    overscrollPastEnd = std::max(GetCurrentPosition() - maxScrollExtent, 0.0);
    // do not adjust offset if direction oppsite from the overScroll direction when out of boundary
    if ((overscrollPastStart > 0.0 && offset > 0.0) || (overscrollPastEnd > 0.0 && offset < 0.0)) {
        return;
    }
    easing = (overscrollPastStart > 0.0 && offset < 0.0) || (overscrollPastEnd > 0.0 && offset > 0.0);
    overscrollPast = std::max(overscrollPastStart, overscrollPastEnd);
    double friction = easing ? CalculateFriction((overscrollPast - std::abs(offset)) / viewPortSize)
                             : CalculateFriction(overscrollPast / viewPortSize);
    double direction = offset / std::abs(offset);
    offset = direction * CalculateOffsetByFriction(overscrollPast, std::abs(offset), friction);
    axis_ == Axis::VERTICAL ? delta.SetY(offset) : delta.SetX(offset);
}

double RenderScroll::CalculateFriction(double gamma)
{
    return SCROLL_RATIO * std::pow(1.0 - gamma, SQUARE);
}

double RenderScroll::CalculateOffsetByFriction(double extentOffset, double delta, double friction)
{
    double offset = 0.0;
    if (extentOffset > 0.0 && !NearZero(friction)) {
        double deltaToLimit = extentOffset / friction;
        if (delta < deltaToLimit) {
            return delta * friction;
        }
        offset += extentOffset;
        delta -= deltaToLimit;
    }
    return offset + delta;
}

void RenderScroll::ResetEdgeEffect()
{
    if (scrollEffect_) {
        scrollEffect_->SetCurrentPositionCallback([weakScroll = AceType::WeakClaim(this)]() {
            auto scroll = weakScroll.Upgrade();
            if (scroll) {
                return -scroll->GetCurrentPosition();
            }
            return 0.0;
        });
        scrollEffect_->SetLeadingCallback([weakScroll = AceType::WeakClaim(this)]() {
            auto scroll = weakScroll.Upgrade();
            if (scroll) {
                if (!scroll->IsRowReverse() && !scroll->IsColReverse()) {
                    return scroll->GetMainSize(scroll->viewPort_) - scroll->mainScrollExtent_;
                }
            }
            return 0.0;
        });
        scrollEffect_->SetTrailingCallback([weakScroll = AceType::WeakClaim(this)]() {
            auto scroll = weakScroll.Upgrade();
            if (scroll) {
                if (scroll->IsRowReverse() || scroll->IsColReverse()) {
                    return scroll->mainScrollExtent_ - scroll->GetMainSize(scroll->viewPort_);
                }
            }
            return 0.0;
        });
        scrollEffect_->SetInitLeadingCallback([weakScroll = AceType::WeakClaim(this)]() {
            auto scroll = weakScroll.Upgrade();
            if (scroll) {
                if (!scroll->IsRowReverse() && !scroll->IsColReverse()) {
                    return scroll->GetMainSize(scroll->viewPort_) - scroll->GetMainScrollExtent();
                }
            }
            return 0.0;
        });
        scrollEffect_->SetInitTrailingCallback([weakScroll = AceType::WeakClaim(this)]() {
            auto scroll = weakScroll.Upgrade();
            if (scroll) {
                if (scroll->IsRowReverse() || scroll->IsColReverse()) {
                    return scroll->GetMainScrollExtent() - scroll->GetMainSize(scroll->viewPort_);
                }
            }
            return 0.0;
        });
        scrollEffect_->SetScrollNode(AceType::WeakClaim(this));

        SetEdgeEffectAttribute();
        scrollEffect_->InitialEdgeEffect();
    }
}

void RenderScroll::ResetScrollEventCallBack()
{
    scrollable_->SetScrollEndCallback([weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            if (scroll->positionController_) {
                scroll->positionController_->HandleScrollEvent(
                    std::make_shared<ScrollEventInfo>(ScrollEvent::SCROLL_END, 0.0, 0.0, -1));
            }
            // Send scroll none when scroll is end.
            auto context = scroll->GetContext().Upgrade();
            if (!(context && context->GetIsDeclarative())) {
                scroll->HandleScrollPosition(0.0, 0.0, SCROLL_NONE);
            }
            scroll->HandleScrollBarEnd();

            auto proxy = scroll->scrollBarProxy_;
            if (proxy) {
                proxy->StartScrollBarAnimator();
            }
        }
    });
    scrollable_->SetScrollTouchUpCallback([weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (scroll && scroll->positionController_) {
            scroll->positionController_->HandleScrollEvent(
                std::make_shared<ScrollEventInfo>(ScrollEvent::SCROLL_TOUCHUP, 0.0, 0.0, -1));
        }
    });
    if (positionController_) {
        positionController_->SetMiddle();
        double mainOffset = GetMainOffset(currentOffset_);
        // No need to set bottom, because if scrollable, it must not be at the bottom.
        if (NearZero(mainOffset)) {
            positionController_->SetTop();
        }
    }
}

void RenderScroll::InitScrollBar(const RefPtr<ScrollBar>& scrollBar)
{
    if (scrollBar_ == scrollBar) {
        return;
    }

    scrollBar_ = scrollBar;
    if (!scrollBar_) {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF);
    }
    if (axis_ == Axis::HORIZONTAL) {
        scrollBar_->SetPositionMode(PositionMode::BOTTOM);
    }
    if (axis_ == Axis::VERTICAL) {
        if (rightToLeft_) {
            scrollBar_->SetPositionMode(PositionMode::LEFT);
        }
    }
    scrollBar_->InitScrollBar(AceType::WeakClaim(this), GetContext());
    SetBarCallBack(axis_ == Axis::VERTICAL);
}

void RenderScroll::ResetScrollable()
{
    const auto isVertical = (axis_ == Axis::VERTICAL);
    auto&& callback = [weakScroll = AceType::WeakClaim(this), isVertical](double value, int32_t source) {
        auto scroll = weakScroll.Upgrade();
        if (!scroll) {
            LOGE("render scroll is released");
            return false;
        }
        if (source == SCROLL_FROM_START) {
            scroll->NotifyDragStart(value);
            scroll->currentDeltaInMain_ = 0.0;
            return true;
        }
        Offset delta;
        if (isVertical) {
            delta.SetX(0.0);
            delta.SetY(-value);
        } else {
            delta.SetX(-value);
            delta.SetY(0.0);
        }
        scroll->AdjustOffset(delta, source);
        scroll->NotifyDragUpdate(scroll->GetMainOffset(delta), source);

        // Stop animator of scroll bar.
        auto scrollBarProxy = scroll->scrollBarProxy_;
        if (scrollBarProxy) {
            scrollBarProxy->StopScrollBarAnimator();
        }
        return scroll->UpdateOffset(delta, source);
    };
    // Initializes scrollable with different direction.
    if (scrollable_) {
        scrollable_->SetAxis(axis_ == Axis::VERTICAL ? Axis::VERTICAL : Axis::HORIZONTAL);
        scrollable_->SetCallback(callback);
    } else {
        if (isVertical) {
            scrollable_ = AceType::MakeRefPtr<Scrollable>(callback, Axis::VERTICAL);
            scrollable_->InitRelatedParent(GetParent());
        } else {
            scrollable_ = AceType::MakeRefPtr<Scrollable>(callback, Axis::HORIZONTAL);
        }
        scrollable_->SetScrollableNode(AceType::WeakClaim(this));
    }
    scrollable_->SetOnScrollBegin(onScrollBegin_);
    scrollable_->SetNotifyScrollOverCallBack([weak = AceType::WeakClaim(this)](double velocity) {
        auto scroll = weak.Upgrade();
        if (!scroll) {
            return;
        }
        scroll->ProcessScrollOverCallback(velocity);
    });
    scrollable_->SetWatchFixCallback([weak = AceType::WeakClaim(this)](double final, double current) {
        auto scroll = weak.Upgrade();
        if (scroll) {
            return scroll->GetFixPositionOnWatch(final, current);
        }
        return final;
    });
    scrollable_->Initialize(GetContext());
    scrollable_->SetNodeId(GetAccessibilityNodeId());
    scrollable_->SetScrollEnd([weakScroll = AceType::WeakClaim(this)]() {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->MarkNeedLayout(true);
        }
    });
    InitializeScrollable(scrollable_);

    currentBottomOffset_ = Offset::Zero();
    currentOffset_ = Offset::Zero();
    lastOffset_ = Offset::Zero();
    ResetScrollEventCallBack();
    SetEdgeEffectAttribute();
}

void RenderScroll::SetEdgeEffectAttribute()
{
    if (scrollEffect_ && scrollable_) {
        scrollEffect_->SetScrollable(scrollable_);
        scrollEffect_->RegisterSpringCallback();
        if (scrollEffect_->IsSpringEffect()) {
            scrollable_->SetOutBoundaryCallback([weakScroll = AceType::WeakClaim(this)]() {
                auto scroll = weakScroll.Upgrade();
                if (scroll) {
                    return scroll->IsOutOfBoundary();
                }
                return false;
            });
        }
    }
}

void RenderScroll::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (!GetVisible() || axis_ == Axis::NONE) {
        return;
    }
    if (!scrollable_) {
        return;
    }
    if (scrollable_->Available() && scrollBar_ && scrollBar_->InBarRegion(globalPoint_ - coordinateOffset)) {
        scrollBar_->AddScrollBarController(coordinateOffset, result);
    } else {
        scrollable_->SetCoordinateOffset(coordinateOffset);
        auto newTouchRestrict = touchRestrict;
        AdjustTouchRestrict(newTouchRestrict);
        scrollable_->SetDragTouchRestrict(newTouchRestrict);
        result.emplace_back(scrollable_);
    }
    touchRecognizer_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(touchRecognizer_);
}

void RenderScroll::HandleMouseHoverEvent(const MouseState mouseState)
{
    LOGI("scroll hover state: %{public}d", mouseState);
    if (scrollBar_ && mouseState == MouseState::NONE) {
        scrollBar_->SetIsHover(false);
    }
}

bool RenderScroll::HandleMouseEvent(const MouseEvent& event)
{
    if (!scrollBar_) {
        return RenderNode::HandleMouseEvent(event);
    }
    auto globalOffset = GetGlobalOffset();
    auto localPoint = Point(event.x - globalOffset.GetX(), event.y - globalOffset.GetY());
    bool isInBarRegion = scrollBar_->InBarRegion(localPoint);
    scrollBar_->SetIsHover(isInBarRegion);
    return isInBarRegion;
}

void RenderScroll::JumpToIndex(int32_t index)
{
    LOGE("Do not support in base RenderScroll");
}

void RenderScroll::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    if ((IsRowReverse() && scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) ||
        (!IsRowReverse() && scrollEdgeType == ScrollEdgeType::SCROLL_TOP)) {
        double distance = -GetMainOffset(currentOffset_);
        ScrollBy(distance, distance, smooth);
    } else {
        double distance = mainScrollExtent_ - GetMainOffset(currentOffset_);
        ScrollBy(distance, distance, smooth);
    }
}

bool RenderScroll::ScrollPage(bool reverse, bool smooth, const std::function<void()>& onFinish)
{
    if ((IsRowReverse() && !reverse) || (!IsRowReverse() && reverse)) {
        double distance = -GetMainSize(viewPort_);
        ScrollBy(distance, distance, smooth, onFinish);
    } else {
        double distance = GetMainSize(viewPort_);
        ScrollBy(distance, distance, smooth, onFinish);
    }
    return true;
}

void RenderScroll::JumpToPosition(double position, int32_t source)
{
    // If an animation is playing, stop it.
    if (animator_) {
        if (!animator_->IsStopped()) {
            animator_->Stop();
        }
        animator_->ClearInterpolators();
    }
    DoJump(position, source);
    HandleScrollBarEnd();
}

void RenderScroll::DoJump(double position, int32_t source)
{
    if (!NearEqual(GetCurrentPosition(), position)) {
        Offset delta;
        if (axis_ == Axis::VERTICAL) {
            delta.SetY(position - GetMainOffset(currentOffset_));
        } else {
            delta.SetX(position - GetMainOffset(currentOffset_));
        }

        UpdateOffset(delta, source);
    }
}

void RenderScroll::AnimateTo(double position, float duration, const RefPtr<Curve>& curve, bool limitDuration,
    const std::function<void()>& onFinish)
{
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(GetContext());
        CHECK_NULL_VOID(animator_);
    }
    if (!animator_->IsStopped()) {
        animator_->Stop();
    }
    animator_->ClearInterpolators();

    // Send event to accessibility when scroll start.
    auto context = GetContext().Upgrade();
    if (context) {
        AccessibilityEvent scrollEvent;
        scrollEvent.nodeId = GetAccessibilityNodeId();
        scrollEvent.eventType = "scrollstart";
        context->SendEventToAccessibility(scrollEvent);
    }
    auto animation = AceType::MakeRefPtr<CurveAnimation<double>>(GetCurrentPosition(), position, curve);
    animation->AddListener([weakScroll = AceType::WeakClaim(this)](double value) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->DoJump(value);
        }
    });
    animator_->AddInterpolator(animation);
    animator_->SetDuration(duration);
    animator_->ClearStopListeners();
    animator_->Play();
    auto weakScroll = AceType::WeakClaim(this);
    auto weakScrollBar = AceType::WeakClaim(AceType::RawPtr(scrollBar_));
    animator_->AddStopListener([weakScroll, weakScrollBar, onFinish, context = context_]() {
        auto scrollBar = weakScrollBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleScrollBarEnd();
        }
        // Send event to accessibility when scroll end.
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            auto context = scroll->GetContext().Upgrade();
            if (context) {
                AccessibilityEvent scrollEvent;
                scrollEvent.nodeId = scroll->GetAccessibilityNodeId();
                scrollEvent.eventType = "scrollend";
                context->SendEventToAccessibility(scrollEvent);
                if (context->GetIsDeclarative() && scroll->scrollable_) {
                    scroll->scrollable_->ChangeMoveStatus(true);
                    scroll->scrollable_->ProcessScrollMotionStop();
                }
            }
        }

        if (onFinish) {
            onFinish();
        }
    });
}

bool RenderScroll::AnimateToTarget(const ComposeId& targetId, float duration, const RefPtr<Curve>& curve,
    bool limitDuration, const std::function<void()>& onFinish)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return false;
    }
    auto targetElement = context->GetComposedElementById(targetId);
    if (!targetElement) {
        return false;
    }
    auto targetRender = targetElement->GetRenderNode();
    if (!targetRender) {
        return false;
    }

    auto globalOffset = targetRender->GetGlobalOffset() - GetPosition();
    double distance = ((axis_ == Axis::VERTICAL) ? globalOffset.GetY() : globalOffset.GetX()) + GetCurrentPosition();
    AnimateTo(distance, duration, curve, limitDuration, onFinish);
    return true;
}

void RenderScroll::ScrollBy(double pixelX, double pixelY, bool smooth, const std::function<void()>& onFinish)
{
    double distance = (axis_ == Axis::VERTICAL) ? pixelY : pixelX;
    if (NearZero(distance)) {
        return;
    }
    double position = GetMainOffset(currentOffset_) + distance;
    if (smooth) {
        AnimateTo(position, fabs(distance) * UNIT_CONVERT / SCROLL_BY_SPEED, Curves::EASE_OUT, true, onFinish);
    } else {
        JumpToPosition(position);
    }
}

double RenderScroll::GetCurrentPosition() const
{
    double position = 0.0;
    if (axis_ == Axis::VERTICAL) {
        position = currentOffset_.GetY();
    } else {
        position = currentOffset_.GetX();
    }
    return position;
}

void RenderScroll::Update(const RefPtr<Component>& component)
{
    auto scroll = AceType::DynamicCast<ScrollComponent>(component);
    if (scroll == nullptr) {
        LOGI("scroll component is null, which it is multi scroll, not single scroll");
        return;
    }
    hasHeight_ = scroll->GetHasHeight();
    hasWidth_ = scroll->GetHasWidth();
    if (!animator_) {
        animator_ = CREATE_ANIMATOR(GetContext());
    }
    // ApplyRestoreInfo maybe change currentOffset_
    ApplyRestoreInfo();
    lastOffset_ = currentOffset_;
    // Send scroll none when first build.
    HandleScrollPosition(0.0, 0.0, SCROLL_NONE);
    MarkNeedLayout();
    onReachStart_ = AceAsyncEvent<void(const std::string&)>::Create(scroll->GetOnReachStart(), context_);
    onReachEnd_ = AceAsyncEvent<void(const std::string&)>::Create(scroll->GetOnReachEnd(), context_);
    onReachTop_ = AceAsyncEvent<void(const std::string&)>::Create(scroll->GetOnReachTop(), context_);
    onReachBottom_ = AceAsyncEvent<void(const std::string&)>::Create(scroll->GetOnReachBottom(), context_);
    scrollBarProxy_ = scroll->GetScrollBarProxy();
    InitScrollBarProxy();
}

void RenderScroll::InitScrollBarProxy()
{
    if (!scrollBarProxy_) {
        return;
    }
    auto isVertical = (axis_ == Axis::VERTICAL);
    auto&& scrollCallback = [weakScroll = AceType::WeakClaim(this), isVertical](double value, int32_t source) {
        auto scroll = weakScroll.Upgrade();
        if (!scroll) {
            LOGE("render scroll is released");
            return false;
        }
        Offset delta;
        if (isVertical) {
            delta.SetX(0.0);
            delta.SetY(-value);
        } else {
            delta.SetX(-value);
            delta.SetY(0.0);
        }
        scroll->AdjustOffset(delta, source);
        return scroll->UpdateOffset(delta, source);
    };
    scrollBarProxy_->UnRegisterScrollableNode(AceType::WeakClaim(this));
    scrollBarProxy_->RegisterScrollableNode({ AceType::WeakClaim(this), scrollCallback });
}

void RenderScroll::SetBarCallBack(bool isVertical)
{
    if (scrollBar_ && scrollBar_->NeedScrollBar()) {
        auto&& barEndCallback = [weakScroll = AceType::WeakClaim(this), isVertical](int32_t value) {
            auto scroll = weakScroll.Upgrade();
            if (!scroll) {
                LOGE("render scroll is released");
                return;
            }
            scroll->scrollBarOpacity_ = value;
            scroll->MarkNeedRender();
        };
        auto&& scrollEndCallback = [weakScroll = AceType::WeakClaim(this), isVertical]() {
            auto scroll = weakScroll.Upgrade();
            if (!scroll) {
                LOGE("render scroll is released");
                return;
            }
            if (scroll->positionController_) {
                scroll->positionController_->HandleScrollEvent(
                    std::make_shared<ScrollEventInfo>(ScrollEvent::SCROLL_END, 0.0, 0.0, -1));
            }
            // Send scroll none when scroll is end.
            scroll->HandleScrollPosition(0.0, 0.0, SCROLL_NONE);
        };
        auto&& scrollCallback = [weakScroll = AceType::WeakClaim(this), isVertical](double value, int32_t source) {
            auto scroll = weakScroll.Upgrade();
            if (!scroll) {
                LOGE("render scroll is released");
                return false;
            }
            Offset delta;
            if (isVertical) {
                delta.SetX(0.0);
                delta.SetY(-value);
            } else {
                delta.SetX(-value);
                delta.SetY(0.0);
            }
            scroll->AdjustOffset(delta, source);

            return scroll->UpdateOffset(delta, source);
        };
        scrollBar_->SetCallBack(scrollCallback, barEndCallback, scrollEndCallback);
    }
}

double RenderScroll::GetEstimatedHeight()
{
    if (ReachMaxCount()) {
        estimatedHeight_ = scrollBarExtent_;
    } else {
        estimatedHeight_ = std::max(estimatedHeight_, scrollBarExtent_);
    }
    return estimatedHeight_;
}

void RenderScroll::HandleScrollOverByBar(double velocity)
{
    // the direction of bar and scroll is opposite, so it need be negative
    if (scrollEffect_) {
        scrollEffect_->ProcessScrollOver(-velocity);
    }
}

void RenderScroll::HandleScrollBarEnd()
{
    if (scrollBar_) {
        scrollBar_->HandleScrollBarEnd();
    }
}

void RenderScroll::HandleRotate(double rotateValue, bool isVertical)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        LOGE("context is null");
        return;
    }
    double value = context->NormalizeToPx(Dimension(rotateValue, DimensionUnit::VP)) * ROTATE_FACTOR;

    // Vertical or horizontal, different axis
    Offset delta;
    if (isVertical) {
        delta.SetX(0.0);
        delta.SetY(value);
    } else {
        delta.SetX(value);
        delta.SetY(0.0);
    }
    UpdateOffset(delta, SCROLL_FROM_ROTATE);
}

void RenderScroll::OnChildAdded(const RefPtr<RenderNode>& child)
{
    child->SetSlipFactorSetting([weakScroll = AceType::WeakClaim(this)](double slipFactor) {
        auto scroll = weakScroll.Upgrade();
        if (scroll) {
            scroll->scrollable_->SetSlipFactor(slipFactor);
        }
    });
}

void RenderScroll::OnReachStart() const
{
    if (onReachStart_) {
        onReachStart_(std::string("\"reachstart\",null"));
    }
}

void RenderScroll::OnReachEnd() const
{
    if (onReachEnd_) {
        onReachEnd_(std::string("\"reachend\",null"));
    }
}

void RenderScroll::OnReachTop() const
{
    if (onReachTop_) {
        onReachTop_(std::string("\"reachtop\",null"));
    }
}

void RenderScroll::OnReachBottom() const
{
    if (onReachBottom_) {
        onReachBottom_(std::string("\"reachbottom\",null"));
    }
}

void RenderScroll::UpdateTouchRect()
{
    RenderNode::UpdateTouchRect();
    if (!scrollBar_) {
        return;
    }
    double scrollBarPosition = NormalizeToPx(scrollBar_->GetPosition());
    if (!NearZero(scrollBarPosition)) {
        touchRect_.SetWidth(touchRect_.Width() + scrollBarPosition);
        if (scrollBar_->GetPositionMode() == PositionMode::LEFT) {
            touchRect_.SetLeft(touchRect_.Left() - scrollBarPosition);
        }
    }
}

bool RenderScroll::IsAxisScrollable(AxisDirection direction)
{
    return (((AxisEvent::IsDirectionUp(direction) || AxisEvent::IsDirectionLeft(direction)) && !IsAtTop()) ||
            ((AxisEvent::IsDirectionDown(direction) || AxisEvent::IsDirectionRight(direction)) && !IsAtBottom()));
}

void RenderScroll::HandleAxisEvent(const AxisEvent& event)
{
}

std::string RenderScroll::ProvideRestoreInfo()
{
    if (!NearZero(currentOffset_.GetY()) && axis_ == Axis::VERTICAL) {
        return std::to_string(currentOffset_.GetY());
    } else if (!NearZero(currentOffset_.GetX()) && axis_ == Axis::HORIZONTAL) {
        return std::to_string(currentOffset_.GetX());
    }
    return "";
}

void RenderScroll::ApplyRestoreInfo()
{
    if (GetRestoreInfo().empty()) {
        return;
    }
    if (axis_ == Axis::VERTICAL) {
        currentOffset_.SetY(StringUtils::StringToDouble(GetRestoreInfo()));
    } else {
        currentOffset_.SetX(StringUtils::StringToDouble(GetRestoreInfo()));
    }
    SetRestoreInfo("");
}

} // namespace OHOS::Ace
