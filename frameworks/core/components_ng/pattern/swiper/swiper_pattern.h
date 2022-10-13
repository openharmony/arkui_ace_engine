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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_PATTERN_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_method.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"

namespace OHOS::Ace::NG {

class SwiperPattern : public Pattern {
    DECLARE_ACE_TYPE(SwiperPattern, Pattern);

public:
    SwiperPattern();
    ~SwiperPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SwiperLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<SwiperPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto layoutAlgorithm = MakeRefPtr<SwiperLayoutAlgorithm>(currentIndex_, startIndex_, endIndex_);
        layoutAlgorithm->SetCurrentOffset(currentOffset_);
        layoutAlgorithm->SetTargetIndex(targetIndex_);
        layoutAlgorithm->SetTotalCount(TotalCount());
        layoutAlgorithm->SetPreItemRange(preItemRange_);
        layoutAlgorithm->SetIsLoop(IsLoop());
        return layoutAlgorithm;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!IsLoop() && GetEdgeEffect() == EdgeEffect::FADE && IsOutOfBoundary(currentOffset_)) {
            return MakeRefPtr<SwiperPaintMethod>(GetDirection(), currentOffset_);
        }
        return nullptr;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SwiperEventHub>();
    }

    RefPtr<SwiperController> GetSwiperController() const
    {
        return swiperController_;
    }

    void SetSwiperController(const RefPtr<SwiperController>& swiperController)
    {
        swiperController_ = swiperController;
    }

    int GetCurrentIndex() const
    {
        return currentIndex_;
    }

    void UpdateCurrentOffset(float offset);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    // Init pan recognizer to move items when drag update, play translate animation when drag end.
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);

    // Init touch event, stop animation when touch down.
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);

    // Init on key event
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);

    // Init auto play, show next item in duration time when auto play.
    void InitAutoPlay();

    // Init controller of swiper, controller support showNext, showPrevious and finishAnimation interface.
    void InitSwiperController();

    void HandleDragStart();
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(double dragVelocity);

    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown();
    void HandleTouchUp();

    void PlayTranslateAnimation(float startPos, float endPos, int32_t nextIndex, bool restartAutoPlay = false);
    void PlaySpringAnimation(double dragVelocity);
    void PlayFadeAnimation();

    // Implement of swiper controller
    void SwipeToWithoutAnimation(int32_t index);
    void SwipeTo(int32_t index);
    void ShowNext();
    void ShowPrevious();
    void FinishAnimation();
    void StopTranslateAnimation();

    // Timer tick callback, duration is in millisecond.
    void Tick(uint64_t duration);
    void StopAutoPlay();
    void StartAutoPlay();
    bool IsOutOfBoundary(double mainOffset) const;
    float MainSize() const;
    void FireChangeEvent() const;
    void CalculateCacheRange();

    float GetItemSpace() const;
    Axis GetDirection() const;
    int32_t CurrentIndex() const;
    int32_t GetDisplayCount() const;
    int32_t GetDuration() const;
    int32_t GetInterval() const;
    RefPtr<Curve> GetCurve() const;
    EdgeEffect GetEdgeEffect() const;
    bool IsAutoPlay() const;
    bool IsLoop() const;
    bool IsDisableSwipe() const;
    int32_t TotalCount() const;

    RefPtr<PanEvent> panEvent_;
    RefPtr<TouchEventImpl> touchEvent_;

    // Control translate animation when drag end.
    RefPtr<Animator> controller_;

    // Control spring animation when drag beyond boundary and drag end.
    RefPtr<Animator> springController_;

    // Control fade animation when drag beyond boundary and drag end.
    RefPtr<Animator> fadeController_;

    RefPtr<Scheduler> scheduler_;

    RefPtr<SwiperController> swiperController_;

    int32_t startIndex_ = 0;
    int32_t endIndex_ = 0;
    int32_t currentIndex_ = 0;
    std::optional<int32_t> targetIndex_;
    std::set<int32_t> preItemRange_;

    float currentOffset_ = 0.0f;

    bool moveDirection_ = false;

    Axis direction_ = Axis::HORIZONTAL;

    uint64_t elapsedTime_ = 0; // millisecond.
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_PATTERN_H
