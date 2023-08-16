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
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_accessibility_property.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_paint_method.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_v2/inspector/utils.h"

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

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<SwiperAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto layoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, nullptr);
        const auto& paddingProperty = layoutProperty->GetPaddingProperty();
        bool needClipPadding = paddingProperty != nullptr;
        bool needPaintFade = !IsLoop() && GetEdgeEffect() == EdgeEffect::FADE && !NearZero(fadeOffset_);
        auto paintMethod = MakeRefPtr<SwiperPaintMethod>(GetDirection(), fadeOffset_);
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
        json->Put("currentIndex", currentIndex_);
        json->Put("currentOffset", currentOffset_);

        if (indicatorIsBoolean_) {
            return;
        }

        auto indicatorType = GetIndicatorType();
        if (indicatorType == SwiperIndicatorType::DOT) {
            json->Put("indicator", GetDotIndicatorStyle().c_str());
        } else {
            json->Put("indicator", GetDigitIndicatorStyle().c_str());
        }
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        currentIndex_ = json->GetInt("currentIndex");
        auto currentOffset = json->GetDouble("currentOffset");
        if (currentOffset != currentOffset_) {
            auto delta = currentOffset - currentOffset_;
            LOGD("UITree delta=%{public}f", delta);
            UpdateCurrentOffset(delta);
        }
        Pattern::FromJson(json);
    }

    std::string GetDotIndicatorStyle() const
    {
        auto swiperParameters = GetSwiperParameters();
        CHECK_NULL_RETURN(swiperParameters, "");
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("left", swiperParameters_->dimLeft.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("top", swiperParameters_->dimTop.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("right", swiperParameters_->dimRight.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("bottom", swiperParameters_->dimBottom.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("itemWidth", swiperParameters_->itemWidth.value_or(6.0_vp).ToString().c_str());
        jsonValue->Put("itemHeight", swiperParameters_->itemHeight.value_or(6.0_vp).ToString().c_str());
        jsonValue->Put("selectedItemWidth", swiperParameters_->selectedItemWidth.value_or(6.0_vp).ToString().c_str());
        jsonValue->Put("selectedItemHeight", swiperParameters_->selectedItemHeight.value_or(6.0_vp).ToString().c_str());
        jsonValue->Put("selectedColor",
            swiperParameters_->selectedColorVal.value_or(Color::FromString("#ff007dff")).ColorToString().c_str());
        jsonValue->Put(
            "color", swiperParameters_->colorVal.value_or(Color::FromString("#19182431")).ColorToString().c_str());
        jsonValue->Put("mask", swiperParameters_->maskValue ? "true" : "false");
        return jsonValue->ToString();
    }

    std::string GetDigitIndicatorStyle() const
    {
        auto swiperParameters = GetSwiperDigitalParameters();
        CHECK_NULL_RETURN(swiperParameters, "");
        auto jsonValue = JsonUtil::Create(true);
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, "");
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperIndicatorTheme, "");
        jsonValue->Put("left", swiperDigitalParameters_->dimLeft.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("top", swiperDigitalParameters_->dimTop.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("right", swiperDigitalParameters_->dimRight.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("bottom", swiperDigitalParameters_->dimBottom.value_or(0.0_vp).ToString().c_str());
        jsonValue->Put("fontSize", swiperDigitalParameters_->fontSize
                                       .value_or(swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize())
                                       .ToString()
                                       .c_str());
        jsonValue->Put("fontColor", swiperDigitalParameters_->fontColor
                                        .value_or(swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor())
                                        .ColorToString()
                                        .c_str());
        jsonValue->Put("fontWeight",
            V2::ConvertWrapFontWeightToStirng(swiperDigitalParameters_->fontWeight.value_or(FontWeight::NORMAL))
                .c_str());
        jsonValue->Put(
            "selectedFontSize", swiperDigitalParameters_->selectedFontSize
                                    .value_or(swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize())
                                    .ToString()
                                    .c_str());
        jsonValue->Put(
            "selectedFontColor", swiperDigitalParameters_->selectedFontColor
                                     .value_or(swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor())
                                     .ColorToString()
                                     .c_str());
        jsonValue->Put("selectedFontWeight",
            V2::ConvertWrapFontWeightToStirng(swiperDigitalParameters_->selectedFontWeight.value_or(FontWeight::NORMAL))
                .c_str());
        return jsonValue->ToString();
    }

    int32_t GetCurrentShownIndex() const
    {
        return GetLoopIndex(currentIndex_);
    }

    RefPtr<SwiperController> GetSwiperController() const
    {
        return swiperController_;
    }

    void SetSwiperController(const RefPtr<SwiperController>& swiperController)
    {
        swiperController_ = swiperController;
    }

    int32_t GetCurrentFirstIndex() const
    {
        return currentFirstIndex_;
    }

    int32_t GetCurrentIndex()
    {
        return GetLoopIndex(currentIndex_);
    }

    float GetTurnPageRate() const
    {
        return turnPageRate_;
    }

    void SetTurnPageRate(float turnPageRate)
    {
        turnPageRate_ = turnPageRate;
    }

    float GetTouchBottomRate() const
    {
        return touchBottomRate_;
    }

    void SetTouchBottomRate(float touchBottomRate)
    {
        touchBottomRate_ = touchBottomRate;
    }

    RefPtr<Animator> GetController()
    {
        return controller_;
    }

    void SetIndicatorDoingAnimation(bool indicatorDoingAnimation)
    {
        indicatorDoingAnimation_ = indicatorDoingAnimation;
    }

    void UpdateCurrentOffset(float offset);

    void CheckMarkDirtyNodeForRenderIndicator(float additionalOffset = 0.0f);

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

    void UpdateOnChangeEvent(ChangeEvent&& event)
    {
        if (!onIndexChangeEvent_) {
            onIndexChangeEvent_ = std::make_shared<ChangeEvent>(event);
            auto eventHub = GetEventHub<SwiperEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->AddOnChangeEvent(onIndexChangeEvent_);
        } else {
            (*onIndexChangeEvent_).swap(event);
        }
    }

    void SetSwiperParameters(const SwiperParameters& swiperParameters)
    {
        swiperParameters_ = std::make_shared<SwiperParameters>(swiperParameters);
    }

    void SetSwiperDigitalParameters(const SwiperDigitalParameters& swiperDigitalParameters)
    {
        swiperDigitalParameters_ = std::make_shared<SwiperDigitalParameters>(swiperDigitalParameters);
    }

    void ShowNext();
    void ShowPrevious();
    void SwipeTo(int32_t index);

    void OnVisibleChange(bool isVisible) override;

    int32_t GetStartIndex() const
    {
        return startIndex_;
    }

    int32_t GetEndIndex() const
    {
        return endIndex_;
    }

    bool HasIndicatorNode() const
    {
        return indicatorId_.has_value();
    }

    bool HasLeftButtonNode() const
    {
        return leftButtonId_.has_value();
    }

    bool HasRightButtonNode() const
    {
        return rightButtonId_.has_value();
    }

    int32_t GetIndicatorId()
    {
        if (!indicatorId_.has_value()) {
            indicatorId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return indicatorId_.value();
    }

    int32_t GetLeftButtonId()
    {
        if (!leftButtonId_.has_value()) {
            leftButtonId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return leftButtonId_.value();
    }

    int32_t GetRightButtonId()
    {
        if (!rightButtonId_.has_value()) {
            rightButtonId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return rightButtonId_.value();
    }

    void RemoveIndicatorNode()
    {
        CHECK_NULL_VOID_NOLOG(HasIndicatorNode());
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        swiperNode->RemoveChildAtIndex(swiperNode->GetChildIndexById(GetIndicatorId()));
        indicatorId_ = std::nullopt;
    }

    void RemoveLeftButtonNode()
    {
        CHECK_NULL_VOID_NOLOG(HasLeftButtonNode());
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        swiperNode->RemoveChildAtIndex(swiperNode->GetChildIndexById(GetLeftButtonId()));
        leftButtonId_ = std::nullopt;
    }

    void RemoveRightButtonNode()
    {
        CHECK_NULL_VOID_NOLOG(HasRightButtonNode());
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        swiperNode->RemoveChildAtIndex(swiperNode->GetChildIndexById(GetRightButtonId()));
        rightButtonId_ = std::nullopt;
    }

    SwiperIndicatorType GetIndicatorType() const;

    bool IsIndicatorCustomSize() const
    {
        return IsCustomSize_;
    }

    void SetIsIndicatorCustomSize(bool IsCustomSize)
    {
        IsCustomSize_ = IsCustomSize;
    }

    void SetIndicatorIsBoolean(bool isBoolean)
    {
        indicatorIsBoolean_ = isBoolean;
    }

    bool GetIsAtHotRegion() const
    {
        return isAtHotRegion_;
    }

    bool HasSurfaceChangedCallback()
    {
        return surfaceChangedCallbackId_.has_value();
    }

    void UpdateSurfaceChangedCallbackId(int32_t id)
    {
        surfaceChangedCallbackId_ = id;
    }

    std::shared_ptr<SwiperParameters> GetSwiperParameters() const;
    std::shared_ptr<SwiperDigitalParameters> GetSwiperDigitalParameters() const;

    void ArrowHover(bool hoverFlag);
    bool IsLoop() const;
    bool IsEnabled() const;
    void OnWindowShow() override;
    void OnWindowHide() override;
    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;

    void OnTouchTestHit(SourceType hitTestType) override;
    void SwipeToWithoutAnimation(int32_t index);
    void SwipeToWithoutAnimationAutoPlay();
private:
    void OnModifyDone() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* node) override;
    void InitSurfaceChangedCallback();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    // Init pan recognizer to move items when drag update, play translate animation when drag end.
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);

    // Init touch event, stop animation when touch down.
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitHoverMouseEvent();
    // Init on key event
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    void FlushFocus(const RefPtr<FrameNode>& curShowFrame);
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);

    // Init controller of swiper, controller support showNext, showPrevious and finishAnimation interface.
    void InitSwiperController();

    // Init indicator
    void InitIndicator();
    void InitArrow();

    void HandleDragStart();
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(double dragVelocity);

    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDown();
    void HandleTouchUp();

    void HandleMouseEvent(const MouseInfo& info);
    void PlayTranslateAnimation(
        float startPos, float endPos, int32_t nextIndex, bool restartAutoPlay = false, float velocity = 0.0f);
    void PlaySpringAnimation(double dragVelocity);
    void PlayFadeAnimation();

    // use property animation feature
    void PlayPropertyTranslateAnimation(float translate, int32_t nextIndex, float velocity = 0.0f);
    void StopPropertyTranslateAnimation();
    void UpdateOffsetAfterPropertyAnimation(float offset);
    void OnPropertyTranslateAnimationFinish(const OffsetF& offset);
    RefPtr<Curve> GetCurveIncludeMotion(float velocity = 0.0f) const;
    void PlayIndicatorTranslateAnimation(float translate);

    // Implement of swiper controller

    void FinishAnimation();
    void StopTranslateAnimation();
    void StopSpringAnimation();
    void StopFadeAnimation();

    void StopAutoPlay();
    void StartAutoPlay();
    bool IsOutOfBoundary(float mainOffset = 0.0f) const;
    float GetRemainingOffset() const;
    float MainSize() const;
    float GetMainContentSize() const;
    void FireChangeEvent() const;
    void FireAnimationStartEvent(int32_t currentIndex, int32_t nextIndex, const AnimationCallbackInfo& info) const;
    void FireAnimationEndEvent(int32_t currentIndex, const AnimationCallbackInfo& info) const;
    void FireGestureSwipeEvent(int32_t currentIndex, const AnimationCallbackInfo& info) const;

    float GetItemSpace() const;
    float GetPrevMargin() const;
    float GetNextMargin() const;
    float CalculateVisibleSize() const;
    int32_t GetLoopIndex(int32_t originalIndex) const;
    int32_t CurrentIndex() const;
    int32_t GetDisplayCount() const;
    int32_t CalculateDisplayCount() const;
    int32_t CalculateCount(
        float contentWidth, float minSize, float margin, float gutter, float swiperPadding = 0.0f) const;
    bool IsAutoFill() const;
    int32_t GetDuration() const;
    int32_t GetInterval() const;
    RefPtr<Curve> GetCurve() const;
    EdgeEffect GetEdgeEffect() const;
    bool IsAutoPlay() const;
    bool IsDisableSwipe() const;
    bool IsShowIndicator() const;
    float GetTranslateLength() const;
    std::pair<int32_t, SwiperItemInfo> GetFirstItemInfoInVisibleArea() const;
    std::pair<int32_t, SwiperItemInfo> GetLastItemInfoInVisibleArea() const;
    std::pair<int32_t, SwiperItemInfo> GetSecondItemInfoInVisibleArea() const;
    void OnIndexChange() const;
    bool IsOutOfHotRegion(const PointF& dragPoint) const;
    bool IsOutOfIndicatorZone(const PointF& dragPoint);
    void SaveDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode);
    void SaveDigitIndicatorProperty(const RefPtr<FrameNode>& indicatorNode);
    void PostTranslateTask(uint32_t delayTime);
    void RegisterVisibleAreaChange();
    bool NeedAutoPlay() const;
    void OnTranslateFinish(int32_t nextIndex, bool restartAutoPlay, bool forceStop = false);
    bool IsShowArrow() const;
    void SaveArrowProperty(const RefPtr<FrameNode>& arrowNode);
    RefPtr<FocusHub> GetFocusHubChild(std::string childFrameName);
    WeakPtr<FocusHub> PreviousFocus(const RefPtr<FocusHub>& curFocusNode);
    WeakPtr<FocusHub> NextFocus(const RefPtr<FocusHub>& curFocusNode);
    void SetAccessibilityAction();
    bool NeedStartAutoPlay() const;
    void CheckAndSetArrowHoverState(const PointF& mousePoint);
    RectF GetArrowFrameRect(const int32_t index) const;
    float GetCustomPropertyOffset() const;
    float GetCurrentFirstIndexStartPos() const;
    void UpdateAnimationProperty(float velocity);
    void TriggerAnimationEndOnForceStop();
    void TriggerAnimationEndOnSwipeToLeft();
    void TriggerAnimationEndOnSwipeToRight();
    void TriggerEventOnFinish(int32_t nextIndex);
    bool IsVisibleChildrenSizeLessThanSwiper();
    void BeforeCreateLayoutWrapper() override;

    void SetLazyLoadFeature(bool useLazyLoad) const;
    void SetLazyLoadIsLoop() const;
    int32_t ComputeNextIndexByVelocity(float velocity) const;
    void UpdateCurrentIndex(int32_t index);
    void OnSpringAnimationStart(float velocity);
    void OnSpringAndFadeAnimationFinish();
    void OnFadeAnimationStart();
    int32_t TotalDisPlayCount() const;
    void StopAndResetSpringAnimation();
    void OnLoopChange();
    void StopSpringAnimationAndFlushImmediately();
    void UpdateItemRenderGroup(bool itemRenderGroup);

    RefPtr<PanEvent> panEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> hoverEvent_;

    // Control translate animation when drag end.
    RefPtr<Animator> controller_;

    // Control spring animation when drag beyond boundary and drag end.
    RefPtr<Animator> springController_;

    // Control fade animation when drag beyond boundary and drag end.
    RefPtr<Animator> fadeController_;

    // Control translate animation for indicator.
    RefPtr<Animator> indicatorController_;

    RefPtr<SwiperController> swiperController_;
    RefPtr<InputEvent> mouseEvent_;

    bool isLastIndicatorFocused_ = false;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = 0;
    int32_t currentIndex_ = 0;
    int32_t oldIndex_ = 0;

    PanDirection panDirection_;

    float currentOffset_ = 0.0f;
    float fadeOffset_ = 0.0f;
    float turnPageRate_ = 0.0f;
    float touchBottomRate_ = 1.0f;
    float currentIndexOffset_ = 0.0f;
    int32_t gestureSwipeIndex_ = 0;
    int32_t currentFirstIndex_ = 0;
    int32_t autoPlayCurrentIndex_ = 0;

    bool moveDirection_ = false;
    bool indicatorDoingAnimation_ = false;
    bool isInit_ = true;
    bool hasVisibleChangeRegistered_ = false;
    bool isVisible_ = true;
    bool isVisibleArea_ = true;
    bool isWindowShow_ = true;
    bool IsCustomSize_ = false;
    bool indicatorIsBoolean_ = true;
    bool isAtHotRegion_ = false;
    bool isDragging_ = false;
    bool isTouchDown_ = false;
    std::optional<bool> preLoop_;

    Axis direction_ = Axis::HORIZONTAL;

    ChangeEventPtr changeEvent_;
    ChangeEventPtr onIndexChangeEvent_;

    mutable std::shared_ptr<SwiperParameters> swiperParameters_;
    mutable std::shared_ptr<SwiperDigitalParameters> swiperDigitalParameters_;

    WeakPtr<FrameNode> lastWeakShowNode_;

    CancelableCallback<void()> translateTask_;

    std::optional<int32_t> indicatorId_;
    std::optional<int32_t> leftButtonId_;
    std::optional<int32_t> rightButtonId_;
    std::optional<SwiperIndicatorType> lastSwiperIndicatorType_;

    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;
    float contentMainSize_ = 0.0f;
    float contentCrossSize_ = 0.0f;

    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> targetIndex_;
    std::optional<int32_t> preTargetIndex_;
    std::optional<int32_t> pauseTargetIndex_;
    float currentDelta_ = 0.0f;
    SwiperLayoutAlgorithm::PositionMap itemPosition_;
    std::optional<float> velocity_;
    bool isFinishAnimation_ = false;
    bool mainSizeIsMeasured_ = false;
    bool isNeedResetPrevMarginAndNextMargin_ = false;
    bool usePropertyAnimation_ = false;
    int32_t propertyAnimationIndex_ = -1;
    bool isUserFinish_ = true;
    bool isVoluntarilyClear_ = false;

    std::optional<int32_t> surfaceChangedCallbackId_;
    SwiperLayoutAlgorithm::PositionMap itemPositionInAnimation_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_PATTERN_H
