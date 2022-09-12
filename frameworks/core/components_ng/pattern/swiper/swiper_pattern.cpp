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

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

// TODO use theme.
constexpr Dimension MIN_TURN_PAGE_VELOCITY = 10.0_vp;
constexpr Dimension MIN_DRAG_DISTANCE = 25.0_vp;

// TODO define as common method
float CalculateFriction(float gamma)
{
    constexpr float SCROLL_RATIO = 0.72f;
    if (GreatOrEqual(gamma, 1.0)) {
        gamma = 1.0;
    }
    return SCROLL_RATIO * static_cast<float>(std::pow(1.0 - gamma, SQUARE));
}

} // namespace

SwiperPattern::SwiperPattern()
{
    swiperController_ = MakeRefPtr<SwiperController>();
}

void SwiperPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
}

void SwiperPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto childrenSize = TotalCount();
    if (CurrentIndex() >= 0 && CurrentIndex() < childrenSize) {
        currentIndex_ = CurrentIndex();
    } else {
        LOGE("index is not valid: %{public}d, items size: %{public}d", CurrentIndex(), childrenSize);
    }

    CalculateCacheRange();
    InitAutoPlay();
    InitSwiperController();
    InitTouchEvent(gestureHub);
    if (IsDisableSwipe()) {
        if (panEvent_) {
            gestureHub->RemovePanEvent(panEvent_);
            panEvent_.Reset();
        }
        return;
    }
    InitPanEvent(gestureHub);
}

bool SwiperPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto swiperLayoutAlgorithm = DynamicCast<SwiperLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(swiperLayoutAlgorithm, false);
    preItemRange_ = swiperLayoutAlgorithm->GetItemRange();
    return false;
}

void SwiperPattern::CalculateCacheRange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = host->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto displayCount = GetDisplayCount();
    auto cacheCount = layoutProperty->GetCachedCount().value_or(1);
    auto loadCount = cacheCount * 2 + displayCount;
    auto totalCount = TotalCount();
    if (loadCount >= totalCount) { // Load all items.
        startIndex_ = 0;
        endIndex_ = totalCount - 1;
        LOGI("Load all items, range [%{public}d - %{public}d]", startIndex_, endIndex_);
        return;
    }

    if (!IsLoop()) {
        startIndex_ = std::max(currentIndex_ - cacheCount, 0);
        endIndex_ = std::min(currentIndex_ + displayCount + cacheCount - 1, totalCount - 1);
    } else {
        startIndex_ = (totalCount + currentIndex_ - cacheCount) % totalCount;
        endIndex_ = (currentIndex_ + cacheCount) % totalCount;
    }

    LOGI("Cache range [%{public}d - %{public}d], totalCount: %{public}d", startIndex_, endIndex_, totalCount);
}

void SwiperPattern::FireChangeEvent() const
{
    auto swiperEventHub = GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    swiperEventHub->FireChangeEvent(currentIndex_);
}

void SwiperPattern::SwipeTo(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto targetIndex = std::clamp(index, 0, TotalCount() - 1);
    if (currentIndex_ == targetIndex) {
        LOGD("Target index is same with current index.");
        return;
    }

    StopAutoPlay();
    StopTranslateAnimation();
    targetIndex_ = targetIndex;
    // TODO Adapt displayCount.
    auto translateOffset = targetIndex_.value() > currentIndex_ ? -MainSize() : MainSize();
    PlayTranslateAnimation(0, translateOffset, targetIndex_.value(), true);
}

void SwiperPattern::ShowNext()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenSize = TotalCount();
    if (currentIndex_ >= childrenSize - 1 && !IsLoop()) {
        LOGW("already last one, can't show next");
        return;
    }
    StopAutoPlay();
    StopTranslateAnimation();
    PlayTranslateAnimation(0, -MainSize(), (currentIndex_ + 1) % childrenSize, true);
}

void SwiperPattern::ShowPrevious()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenSize = TotalCount();
    if (currentIndex_ <= 0 && !IsLoop()) {
        LOGW("already first one, can't show previous");
        return;
    }
    StopAutoPlay();
    StopTranslateAnimation();
    PlayTranslateAnimation(0, MainSize(), (currentIndex_ + childrenSize - 1) % childrenSize, true);
}

void SwiperPattern::FinishAnimation()
{
    StopTranslateAnimation();
    if (swiperController_ && swiperController_->GetFinishCallback()) {
        swiperController_->GetFinishCallback()();
    }
}

void SwiperPattern::StopTranslateAnimation()
{
    if (controller_ && !controller_->IsStopped()) {
        controller_->Stop();
    }
}

void SwiperPattern::InitSwiperController()
{
    if (swiperController_->HasInitialized()) {
        return;
    }

    swiperController_->SetSwipeToImpl([weak = WeakClaim(this)](int32_t index, bool reverse) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->SwipeTo(index);
        }
    });

    swiperController_->SetShowNextImpl([weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->ShowNext();
        }
    });

    swiperController_->SetShowPrevImpl([weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->ShowPrevious();
        }
    });

    swiperController_->SetFinishImpl([weak = WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->FinishAnimation();
        }
    });
}

void SwiperPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (direction_ == GetDirection() && panEvent_) {
        return;
    }
    direction_ = GetDirection();

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGI("Pan event start");
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart();
        }
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragUpdate(info);
        }
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGI("Pan event end mainVelocity: %{public}lf", info.GetMainVelocity());
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd(info.GetMainVelocity());
        }
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        LOGI("Pan event cancel");
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd(0.0);
        }
    };

    PanDirection panDirection;
    if (GetDirection() == Axis::VERTICAL) {
        panDirection.type = PanDirection::VERTICAL;
    } else {
        panDirection.type = PanDirection::HORIZONTAL;
    }
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }

    float distance = DEFAULT_PAN_DISTANCE;
    auto host = GetHost();
    if (host) {
        auto context = host->GetContext();
        if (context) {
            distance = static_cast<float>(context->NormalizeToPx(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP)));
        }
    }
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);
}

void SwiperPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };

    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void SwiperPattern::InitAutoPlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto weak = AceType::WeakClaim(this);
    if (!scheduler_) {
        auto&& callback = [weak](uint64_t duration) {
            auto swiper = weak.Upgrade();
            if (swiper) {
                swiper->Tick(duration);
            }
        };
        scheduler_ = SchedulerBuilder::Build(callback, host->GetContext());
    } else if (scheduler_->IsActive()) {
        scheduler_->Stop();
    }

    if (IsAutoPlay() && !scheduler_->IsActive()) {
        scheduler_->Start();
    }
}

void SwiperPattern::Tick(uint64_t duration)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto childrenSize = TotalCount();
    elapsedTime_ += duration;
    if (elapsedTime_ >= static_cast<uint64_t>(GetInterval())) {
        if (currentIndex_ >= childrenSize - 1 && !IsLoop()) {
            LOGD("already last one, stop auto play because not loop");
            if (scheduler_) {
                scheduler_->Stop();
            }
        } else {
            PlayTranslateAnimation(0, -MainSize(), (currentIndex_ + 1) % childrenSize);
        }
        elapsedTime_ = 0;
    }
}

void SwiperPattern::StopAutoPlay()
{
    if (IsAutoPlay() && scheduler_) {
        scheduler_->Stop();
        elapsedTime_ = 0;
    }
}

void SwiperPattern::StartAutoPlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (!scheduler_ || !IsAutoPlay()) {
        return;
    }
    bool reachEnd = currentIndex_ >= TotalCount() - 1 && !IsLoop();
    if (reachEnd && scheduler_->IsActive()) {
        scheduler_->Stop();
    } else {
        scheduler_->Start();
    }
}

void SwiperPattern::UpdateCurrentOffset(float offset)
{
    currentOffset_ = currentOffset_ + offset;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SwiperPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown();
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    }
}

void SwiperPattern::HandleTouchDown()
{
    // Stop translate animation when touch down.
    if (controller_ && !controller_->IsStopped()) {
        // Clear stop listener before stop, otherwise the previous swipe will be considered complete.
        controller_->ClearStopListeners();
        controller_->Stop();
    }

    // Stop auto play when touch down.
    StopAutoPlay();
}

void SwiperPattern::HandleTouchUp()
{
    StartAutoPlay();
}

void SwiperPattern::HandleDragStart()
{
    currentOffset_ = std::fmod(currentOffset_, MainSize());
}

void SwiperPattern::HandleDragUpdate(const GestureEvent& info)
{
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto isOutOfBoundary = IsOutOfBoundary(mainDelta + currentOffset_);
    if (!IsLoop() && isOutOfBoundary) {
        auto edgeEffect = GetEdgeEffect();
        if (edgeEffect == EdgeEffect::SPRING) {
            LOGI("Swiper has reached boundary, can't drag any more, effect spring.");
            auto mainOffset = std::fmod(currentOffset_, MainSize());
            auto friction = CalculateFriction(std::abs(mainOffset) / MainSize());
            UpdateCurrentOffset(friction * mainDelta);
            return;
        }

        if (edgeEffect == EdgeEffect::FADE) {
            LOGI("Swiper has reached boundary, can't drag any more, effect fade");
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            currentOffset_ += mainDelta;
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            return;
        }

        if (edgeEffect == EdgeEffect::NONE) {
            LOGI("Swiper has reached boundary, can't drag any more.");
            return;
        }
    }

    UpdateCurrentOffset(static_cast<float>(mainDelta));
}

void SwiperPattern::HandleDragEnd(double dragVelocity)
{
    LOGI("Drag end velocity: %{public}lf, currentOffset: %{public}lf", dragVelocity, currentOffset_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    // Play edge effect animation.
    if (!IsLoop() && IsOutOfBoundary(currentOffset_)) {
        auto edgeEffect = GetEdgeEffect();
        if (edgeEffect == EdgeEffect::SPRING) {
            PlaySpringAnimation(dragVelocity);
            return;
        }

        if (edgeEffect == EdgeEffect::FADE) {
            PlayFadeAnimation();
            return;
        }

        if (edgeEffect == EdgeEffect::NONE) {
            return;
        }
    }

    // Play translate animation.
    auto mainSize = MainSize();
    int32_t nextIndex = currentIndex_;
    float start = currentOffset_;
    float end = 0.0f;
    if (std::abs(dragVelocity) > context->NormalizeToPx(MIN_TURN_PAGE_VELOCITY) &&
        std::abs(currentOffset_) > context->NormalizeToPx(MIN_DRAG_DISTANCE)) {
        if (GreatNotEqual(dragVelocity * currentOffset_, 0.0)) {
            auto intervalSize = static_cast<int32_t>(std::floor(std::abs(currentOffset_) / mainSize)) + 1;
            end = GreatNotEqual(dragVelocity, 0.0) ? mainSize * intervalSize : -mainSize * intervalSize;
            nextIndex = GreatNotEqual(dragVelocity, 0.0) ? (nextIndex - intervalSize) : (nextIndex + intervalSize);
        }
    }

    // Adjust next item index when loop and index is out of range.
    auto childrenSize = TotalCount();
    if (IsLoop()) {
        if (nextIndex < 0) {
            nextIndex = childrenSize + nextIndex;
        } else if (nextIndex >= childrenSize) {
            nextIndex = nextIndex % childrenSize;
        }
    }

    PlayTranslateAnimation(start, end, nextIndex);
}

void SwiperPattern::PlayTranslateAnimation(float startPos, float endPos, int32_t nextIndex, bool restartAutoPlay)
{
    LOGI("Play translate animation startPos: %{public}lf, endPos: %{public}lf, nextIndex: %{public}d", startPos, endPos,
        nextIndex);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto curve = GetCurve();
    if (!curve) {
        curve = Curves::LINEAR;
    }

    // If animation is still running, stop it before play new animation.
    StopTranslateAnimation();

    auto translate = AceType::MakeRefPtr<CurveAnimation<double>>(startPos, endPos, curve);
    auto weak = AceType::WeakClaim(this);
    translate->AddListener(Animation<double>::ValueCallback([weak, startPos, endPos](double value) {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        if (!NearEqual(value, startPos) && !NearEqual(value, endPos) && !NearEqual(startPos, endPos)) {
            float moveRate =
                Curves::EASE_OUT->MoveInternal(static_cast<float>((value - startPos) / (endPos - startPos)));
            value = startPos + (endPos - startPos) * moveRate;
        }
        swiper->UpdateCurrentOffset(static_cast<float>(value - swiper->currentOffset_));
    }));

    if (!controller_) {
        controller_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    controller_->ClearStopListeners();
    controller_->ClearInterpolators();
    controller_->AddStopListener([weak, nextIndex, restartAutoPlay]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->currentOffset_ = 0.0;
        swiper->targetIndex_.reset();
        if (swiper->currentIndex_ != nextIndex) {
            swiper->currentIndex_ = nextIndex;
            swiper->FireChangeEvent();
            swiper->CalculateCacheRange();
        }
        if (restartAutoPlay) {
            swiper->StartAutoPlay();
        }
    });
    controller_->SetDuration(GetDuration());
    controller_->AddInterpolator(translate);
    controller_->Play();
}

void SwiperPattern::PlaySpringAnimation(double dragVelocity)
{
    LOGI("Play spring animation start");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!springController_) {
        springController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    springController_->ClearStopListeners();
    springController_->ClearInterpolators();

    // TODO use theme.
    constexpr float SPRING_SCROLL_MASS = 0.5f;
    constexpr float SPRING_SCROLL_STIFFNESS = 100.0f;
    constexpr float SPRING_SCROLL_DAMPING = 15.55635f;
    const RefPtr<SpringProperty> DEFAULT_OVER_SPRING_PROPERTY =
        AceType::MakeRefPtr<SpringProperty>(SPRING_SCROLL_MASS, SPRING_SCROLL_STIFFNESS, SPRING_SCROLL_DAMPING);
    ExtentPair extentPair = ExtentPair(0.0, 0.0);
    float friction = CalculateFriction(std::abs(currentOffset_) / MainSize());
    auto scrollMotion = AceType::MakeRefPtr<ScrollMotion>(
        currentOffset_, dragVelocity * friction, extentPair, extentPair, DEFAULT_OVER_SPRING_PROPERTY);
    scrollMotion->AddListener([weak = AceType::WeakClaim(this)](double position) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateCurrentOffset(static_cast<float>(position) - swiper->currentOffset_);
        }
    });
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {});
    springController_->PlayMotion(scrollMotion);
}

void SwiperPattern::PlayFadeAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (NearZero(currentOffset_)) {
        return;
    }

    LOGI("Play fade animation start");
    if (!fadeController_) {
        fadeController_ = AceType::MakeRefPtr<Animator>(host->GetContext());
    }
    fadeController_->ClearAllListeners();

    auto translate = AceType::MakeRefPtr<CurveAnimation<double>>(currentOffset_, 0, Curves::LINEAR);
    auto weak = AceType::WeakClaim(this);
    translate->AddListener(Animation<double>::ValueCallback([weak](double value) {
        auto swiper = weak.Upgrade();
        if (swiper && swiper->GetHost()) {
            swiper->currentOffset_ = static_cast<float>(value);
            swiper->GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }));

    fadeController_->AddStopListener([weak]() {});
    constexpr float FADE_DURATION = 500.0f;
    fadeController_->SetDuration(FADE_DURATION);
    fadeController_->AddInterpolator(translate);
    fadeController_->Play();
}

bool SwiperPattern::IsOutOfBoundary(double mainOffset) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    if (IsLoop()) {
        return false;
    }

    mainOffset = std::fmod(currentOffset_, MainSize());
    auto isOutOfStart = currentIndex_ == 0 && GreatOrEqual(mainOffset, 0.0);
    auto isOutOfEnd = currentIndex_ == TotalCount() - 1 && LessOrEqual(mainOffset, 0.0);
    return isOutOfStart || isOutOfEnd;
}

float SwiperPattern::MainSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetFrameSize().MainSize(GetDirection());
}

Axis SwiperPattern::GetDirection() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, Axis::HORIZONTAL);
    return swiperLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
}

int32_t SwiperPattern::CurrentIndex() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    return swiperLayoutProperty->GetIndex().value_or(0);
}

int32_t SwiperPattern::GetDisplayCount() const
{
    auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 1);
    return swiperLayoutProperty->GetDisplayCount().value_or(1);
}

bool SwiperPattern::IsAutoPlay() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, false);
    return swiperPaintProperty->GetAutoPlay().value_or(false);
}

int32_t SwiperPattern::GetDuration() const
{
    const int32_t DEFAULT_DURATION = 400;
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, DEFAULT_DURATION);
    return swiperPaintProperty->GetDuration().value_or(DEFAULT_DURATION);
}

int32_t SwiperPattern::GetInterval() const
{
    const int32_t DEFAULT_INTERVAL = 3000;
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, DEFAULT_INTERVAL);
    return swiperPaintProperty->GetAutoPlayInterval().value_or(DEFAULT_INTERVAL);
}

RefPtr<Curve> SwiperPattern::GetCurve() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    return swiperPaintProperty->GetCurve().value_or(nullptr);
}

bool SwiperPattern::IsLoop() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, true);
    return swiperPaintProperty->GetLoop().value_or(true);
}

EdgeEffect SwiperPattern::GetEdgeEffect() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, EdgeEffect::SPRING);
    return swiperPaintProperty->GetEdgeEffect().value_or(EdgeEffect::SPRING);
}

bool SwiperPattern::IsDisableSwipe() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, false);
    return swiperPaintProperty->GetDisableSwipe().value_or(false);
}

int32_t SwiperPattern::TotalCount() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    return host->TotalChildCount();
}

} // namespace OHOS::Ace::NG
