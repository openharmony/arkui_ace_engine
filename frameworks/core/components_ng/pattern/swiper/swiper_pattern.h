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
#include "core/components_ng/pattern/swiper/swiper_model.h"
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

    bool UsResRegion() override
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
        CalculateCacheRange();
        auto layoutAlgorithm = MakeRefPtr<SwiperLayoutAlgorithm>(currentIndex_, startIndex_, endIndex_);
        layoutAlgorithm->SetCurrentOffset(currentOffset_);
        layoutAlgorithm->SetTargetIndex(targetIndex_);
        layoutAlgorithm->SetTotalCount(TotalCount());
        layoutAlgorithm->SetPreItemRange(preItemRange_);
        layoutAlgorithm->SetIsLoop(IsLoop());
        layoutAlgorithm->SetMaxChildSize(maxChildSize_);
        layoutAlgorithm->SetDisplayCount(GetDisplayCount());
        return layoutAlgorithm;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, nullptr);
        const auto& paddingProperty = layoutProperty->GetPaddingProperty();
        bool needClipPadding = paddingProperty != nullptr;
        bool needPaintFade = !IsLoop() && GetEdgeEffect() == EdgeEffect::FADE && IsOutOfBoundary(currentOffset_);
        auto paintMethod = MakeRefPtr<SwiperPaintMethod>(GetDirection(), currentOffset_);
        paintMethod->SetNeedPaintFade(needPaintFade);
        paintMethod->SetNeedClipPadding(needClipPadding);
        return paintMethod;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SwiperEventHub>();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        Pattern::ToJsonValue(json);
        json->Put("indicatorStyle", GetIndicatorStyle().c_str());
    }

    std::string GetIndicatorStyle() const
    {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("left", swiperParameters_.dimLeft.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("top", swiperParameters_.dimTop.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("right", swiperParameters_.dimRight.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("bottom", swiperParameters_.dimBottom.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("size", swiperParameters_.dimSize.value_or(6.0_vp).ToString().c_str());
        jsonValue->Put("selectedColor",
            swiperParameters_.selectedColorVal.value_or(Color::FromString("#ff007dff")).ColorToString().c_str());
        jsonValue->Put(
            "color", swiperParameters_.colorVal.value_or(Color::FromString("#19182431")).ColorToString().c_str());
        return jsonValue->ToString();
    }

    int32_t GetCurrentShownIndex() const
    {
        return currentIndex_;
    }

    RefPtr<SwiperController> GetSwiperController() const
    {
        return swiperController_;
    }

    void SetSwiperController(const RefPtr<SwiperController>& swiperController)
    {
        swiperController_ = swiperController;
    }

    int32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

    float GetTurnPageRate() const
    {
        return turnPageRate_;
    }

    float GetBorderAndPaddingWidth();

    RefPtr<Animator> GetController()
    {
        return controller_;
    }

    void SetIndicatorDoingAnimation(bool indicatorDoingAnimation)
    {
        indicatorDoingAnimation_ = indicatorDoingAnimation;
    }

    void UpdateCurrentOffset(float offset);

    int32_t TotalCount() const;

    Axis GetDirection() const;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return ScopeFocusAlgorithm(direction_ != Axis::HORIZONTAL, true, ScopeType::OTHERS,
            [wp = WeakClaim(this)](
                FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) {
                auto swiper = wp.Upgrade();
                if (swiper) {
                    nextFocusNode = swiper->GetNextFocusNode(step, currFocusNode);
                }
            });
    }

    void UpdateChangeEvent(ChangeEvent&& event)
    {
        if (!changeEvent_) {
            changeEvent_ = std::make_shared<ChangeEvent>(event);
            auto eventHub = GetEventHub<SwiperEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->AddOnChangeEvent(changeEvent_);
        } else {
            (*changeEvent_).swap(event);
        }
    }

    void SetSwiperParameters(const SwiperParameters& swiperParameters)
    {
        swiperParameters_ = swiperParameters;
    }

    void ShowNext();
    void ShowPrevious();
    void SwipeTo(int32_t index);

    void OnVisibleChange(bool isVisible) override;

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
    void FlushFocus(const RefPtr<FrameNode>& curShowFrame);
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);

    // Init controller of swiper, controller support showNext, showPrevious and finishAnimation interface.
    void InitSwiperController();

    // Init swiper indicator
    void InitSwiperIndicator();

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
    void FinishAnimation();
    void StopTranslateAnimation();
    void StopSpringAnimation();

    void StopAutoPlay();
    void StartAutoPlay();
    bool IsOutOfBoundary(float mainOffset) const;
    float MainSize() const;
    void FireChangeEvent() const;
    void FireAnimationStartEvent() const;
    void FireAnimationEndEvent() const;
    void CalculateCacheRange();

    float GetItemSpace() const;
    int32_t CurrentIndex() const;
    int32_t GetDisplayCount() const;
    int32_t GetDuration() const;
    int32_t GetInterval() const;
    RefPtr<Curve> GetCurve() const;
    EdgeEffect GetEdgeEffect() const;
    bool IsAutoPlay() const;
    bool IsLoop() const;
    bool IsDisableSwipe() const;
    bool IsShowIndicator() const;
    float GetTranslateLength() const;
    void OnIndexChange() const;
    bool IsOutOfHotRegion(const PointF& dragPoint) const;
    void PostTranslateTask(uint32_t delayTime);
    void RegisterVisibleAreaChange();
    bool NeedAutoPlay() const;
    void OnTranslateFinish(int32_t nextIndex, bool restartAutoPlay);

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

    bool isLastIndicatorFocused_ = false;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = 0;
    int32_t currentIndex_ = 0;
    int32_t oldIndex_ = 0;
    std::optional<int32_t> targetIndex_;
    std::set<int32_t> preItemRange_;

    PanDirection panDirection_;
    float distance_ = 0.0f;

    float currentOffset_ = 0.0f;
    float turnPageRate_ = 0.0f;

    bool moveDirection_ = false;
    bool indicatorDoingAnimation_ = false;
    bool isInit_ = true;
    bool hasVisibleChangeRegistered_ = false;
    bool isVisible_ = true;

    Axis direction_ = Axis::HORIZONTAL;

    ChangeEventPtr changeEvent_;

    SwiperParameters swiperParameters_;
    SizeF maxChildSize_;

    WeakPtr<FrameNode> lastWeakShowNode_;
    
    CancelableCallback<void()> translateTask_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_PATTERN_H
