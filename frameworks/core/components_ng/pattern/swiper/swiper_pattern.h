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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_PATTERN_H

#include <functional>
#include <optional>
#include <vector>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/nestable_scroll_container.h"
#include "core/components_ng/pattern/swiper/swiper_accessibility_property.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_layout_algorithm.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/components_ng/pattern/tabs/tab_content_transition_proxy.h"
#include "core/components_v2/inspector/utils.h"

#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif
namespace OHOS::Ace::NG {
enum class GestureStatus {
    INIT = 0,
    START,
    END,
};

enum class PageFlipMode {
    CONTINUOUS = 0,
    SINGLE,
};

enum class MoveStep {
    NEXT = 0,
    PREV,
    NONE
};

using SwiperHoverFlag = uint32_t;
constexpr SwiperHoverFlag HOVER_NONE = 0;
constexpr SwiperHoverFlag HOVER_SWIPER = 1;
constexpr SwiperHoverFlag HOVER_INDICATOR = 1 << 1;
constexpr SwiperHoverFlag HOVER_ARROW = 1 << 2;
constexpr int32_t NEW_STYLE_MIN_TURN_PAGE_VELOCITY = 780;
constexpr float SWIPER_CURVE_MASS = 1.0f;
constexpr float SWIPER_CURVE_STIFFNESS = 328.0f;
constexpr float SWIPER_CURVE_DAMPING = 34.0f;

class SwiperPattern : public NestableScrollContainer {
    DECLARE_ACE_TYPE(SwiperPattern, NestableScrollContainer);

public:
    using CustomContentTransitionPtr = std::shared_ptr<std::function<TabContentAnimatedTransition(int32_t, int32_t)>>;
    using PanEventFunction = std::function<void(const GestureEvent& info)>;

    SwiperPattern();
    ~SwiperPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsNeedPercent() const override
    {
        return true;
    }

    bool ShouldDelayChildPressedState() const override
    {
        return true;
    }

    void RegisterScrollingListener(const RefPtr<ScrollingListener> listener) override;
    void FireAndCleanScrollingListener() override;
    void CleanScrollingListener() override;

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

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SwiperEventHub>();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    virtual std::string GetArcDotIndicatorStyle() const { return ""; }
    // ArcSwiper will implement this interface in order to set transitionAnimation disable
    virtual void SetDisableTransitionAnimation(bool isDisable) {};
    int32_t GetCurrentShownIndex() const
    {
        return IsLoop() ? currentIndex_ : GetLoopIndex(currentIndex_);
    }

    RefPtr<SwiperController> GetSwiperController() const
    {
        return swiperController_;
    }

    void SetSwiperController(const RefPtr<SwiperController>& controller);

    void SetPropertyAnimationIsRunning(bool propertyAnimationIsRunning);

    bool GetPropertyAnimationIsRunning();

    int32_t GetCurrentFirstIndex() const
    {
        return currentFirstIndex_;
    }

    int32_t GetCurrentIndex(bool original = false);

    float GetTurnPageRate() const
    {
        return turnPageRate_;
    }

    float GetGroupTurnPageRate() const
    {
        return groupTurnPageRate_;
    }

    GestureState GetGestureState();

    TouchBottomTypeLoop GetTouchBottomTypeLoop() const
    {
        return touchBottomType_;
    }

    bool IsIndicatorAnimatorRunning() const
    {
        return indicatorAnimationIsRunning_;
    }

    void SetTurnPageRate(float turnPageRate)
    {
        turnPageRate_ = turnPageRate;
    }

    void SetGroupTurnPageRate(float groupTurnPageRate)
    {
        groupTurnPageRate_ = groupTurnPageRate;
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
    /**
     * @brief Checks if the given offset exceeds the bounds of the swiper container and triggers overScroll.
     *
     * @param offset The offset to check.
     * @return True if overScroll is triggered, false otherwise.
     */
    bool CheckOverScroll(float offset);

    /**
     * @brief Applies spring effect to the over-scrolling of the swiper.
     *
     * @param offset The offset of the swiper.
     * @return true if the spring effect is applied successfully, false otherwise.
     */
    bool SpringOverScroll(float offset);

    void CheckMarkDirtyNodeForRenderIndicator(
        float additionalOffset = 0.0f, std::optional<int32_t> nextIndex = std::nullopt);

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
                FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) -> bool {
                auto swiper = wp.Upgrade();
                if (swiper) {
                    nextFocusNode = swiper->GetNextFocusNode(step, currFocusNode);
                }
                return nextFocusNode.Upgrade() != currFocusNode.Upgrade();
            });
    }

    void UpdateChangeEvent(ChangeEvent&& event)
    {
        if (!changeEvent_) {
            changeEvent_ = std::make_shared<ChangeEvent>(event);
            auto eventHub = GetOrCreateEventHub<SwiperEventHub>();
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
            auto eventHub = GetOrCreateEventHub<SwiperEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->AddOnChangeEvent(onIndexChangeEvent_);
        } else {
            (*onIndexChangeEvent_).swap(event);
        }
    }

    void UpdateAnimationStartEvent(AnimationStartEvent&& event)
    {
        if (!animationStartEvent_) {
            animationStartEvent_ = std::make_shared<AnimationStartEvent>(event);
            auto eventHub = GetOrCreateEventHub<SwiperEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->AddAnimationStartEvent(animationStartEvent_);
        } else {
            (*animationStartEvent_).swap(event);
        }
    }

    void UpdateAnimationEndEvent(AnimationEndEvent&& event)
    {
        if (!animationEndEvent_) {
            animationEndEvent_ = std::make_shared<AnimationEndEvent>(event);
            auto eventHub = GetOrCreateEventHub<SwiperEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->AddAnimationEndEvent(animationEndEvent_);
        } else {
            (*animationEndEvent_).swap(event);
        }
    }

    void UpdateOnSelectedEvent(ChangeEvent&& event)
    {
        if (!selectedEvent_) {
            selectedEvent_ = std::make_shared<ChangeEvent>(event);
            auto eventHub = GetOrCreateEventHub<SwiperEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->AddOnSlectedEvent(selectedEvent_);
        } else {
            (*selectedEvent_).swap(event);
        }
    }

    void UpdateOnUnselectedEvent(ChangeEvent&& event)
    {
        if (!unselectedEvent_) {
            unselectedEvent_ = std::make_shared<ChangeEvent>(event);
            auto eventHub = GetOrCreateEventHub<SwiperEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->AddOnUnselectedEvent(unselectedEvent_);
        } else {
            (*unselectedEvent_).swap(event);
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

    void ResetIndicatorParameters()
    {
        if (GetIndicatorType() == SwiperIndicatorType::DOT) {
            swiperParameters_ = nullptr;
        } else {
            swiperDigitalParameters_ = nullptr;
        }
    }

    virtual void SetSwiperArcDotParameters(const SwiperArcDotParameters& swiperArcDotParameters) {}

    void ShowNext(bool needCheckWillScroll = false);
    void ShowPrevious(bool needCheckWillScroll = false);
    void SwipeTo(int32_t index);
    void ChangeIndex(int32_t index, bool useAnimation);
    void ChangeIndex(int32_t index, SwiperAnimationMode mode);

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
        return indicatorId_.has_value() || GetIndicatorNode() != nullptr;
    }

    bool HasLeftButtonNode() const
    {
        return leftButtonId_.has_value();
    }

    bool HasRightButtonNode() const
    {
        return rightButtonId_.has_value();
    }

    int32_t CreateIndicatorId()
    {
        indicatorId_ = ElementRegister::GetInstance()->MakeUniqueId();
        return indicatorId_.value();
    }

    int32_t GetIndicatorId() const
    {
        return indicatorId_.has_value() ? indicatorId_.value() : -1;
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

    int32_t GetId() const
    {
        return swiperId_;
    }

    void RemoveIndicatorNode()
    {
        CHECK_NULL_VOID(HasIndicatorNode());
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        swiperNode->RemoveChildAtIndex(swiperNode->GetChildIndexById(GetIndicatorId()));
        indicatorId_ = std::nullopt;
    }

    void RemoveLeftButtonNode()
    {
        CHECK_NULL_VOID(HasLeftButtonNode());
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        swiperNode->RemoveChildAtIndex(swiperNode->GetChildIndexById(GetLeftButtonId()));
        leftButtonId_ = std::nullopt;
    }

    void RemoveRightButtonNode()
    {
        CHECK_NULL_VOID(HasRightButtonNode());
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        swiperNode->RemoveChildAtIndex(swiperNode->GetChildIndexById(GetRightButtonId()));
        rightButtonId_ = std::nullopt;
    }

    SwiperIndicatorType GetIndicatorType() const;

    bool IsIndicatorCustomSize() const
    {
        return isCustomSize_;
    }

    void SetIsIndicatorCustomSize(bool isCustomSize)
    {
        isCustomSize_ = isCustomSize;
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

    void SetIndicatorLongPress(bool isIndicatorLongPress)
    {
        isIndicatorLongPress_ = isIndicatorLongPress;
    }
    void SetCachedCount(int32_t cachedCount)
    {
        if (cachedCount_.has_value() && cachedCount_.value() != cachedCount) {
            SetLazyLoadFeature(true);
        }
        cachedCount_ = cachedCount;
    }

    void SetFinishCallbackType(FinishCallbackType finishCallbackType)
    {
        finishCallbackType_ = finishCallbackType;
    }

    FinishCallbackType GetFinishCallbackType() const
    {
        return finishCallbackType_;
    }

    void SetStopIndicatorAnimationCb(const std::function<void(bool)>& stopCallback)
    {
        stopIndicatorAnimationFunc_ = std::move(stopCallback);
    }

    void SetUpdateOverlongForceStopPageRateCb(const std::function<void(float)>& updateCallback)
    {
        updateOverlongForceStopPageRateFunc_ = std::move(updateCallback);
    }

    std::shared_ptr<SwiperParameters> GetSwiperParameters() const;
    virtual std::shared_ptr<SwiperArcDotParameters> GetSwiperArcDotParameters() const { return nullptr; }
    std::shared_ptr<SwiperDigitalParameters> GetSwiperDigitalParameters() const;

    void ArrowHover(bool isHover, SwiperHoverFlag flag);
    bool IsHoverNone()
    {
        return hoverFlag_ == HOVER_NONE;
    }
    virtual bool IsLoop() const;
    bool IsEnabled() const;
    void OnWindowShow() override;
    void OnWindowHide() override;
    std::string ProvideRestoreInfo() override;
    void OnRestoreInfo(const std::string& restoreInfo) override;
    bool IsAutoFill() const;
    void SwipeToWithoutAnimation(int32_t index);
    void StopAutoPlay();
    void StartAutoPlay();
    void StopTranslateAnimation();
    void StopSpringAnimationImmediately();
    void StopSpringAnimation();
    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    void BuildOffsetInfo(std::unique_ptr<JsonValue>& json);
    void BuildAxisInfo(std::unique_ptr<JsonValue>& json);
    void BuildItemPositionInfo(std::unique_ptr<JsonValue>& json);
    void BuildIndicatorTypeInfo(std::unique_ptr<JsonValue>& json);
    void BuildPanDirectionInfo(std::unique_ptr<JsonValue>& json);
    int32_t GetLoopIndex(int32_t originalIndex) const;
    virtual int32_t GetDuration() const;
    void UpdateDragFRCSceneInfo(float speed, SceneStatus sceneStatus);
    void AdjustCurrentIndexOnSwipePage(int32_t index);
    void OnCustomContentTransition(int32_t toIndex);
    void OnCustomAnimationFinish(int32_t fromIndex, int32_t toIndex, bool hasOnChanged);
    void OnSwiperCustomAnimationFinish(CancelableCallback<void()>& task, int32_t index, bool isFinishAnimation);

    void SetCustomAnimationToIndex(int32_t toIndex)
    {
        customAnimationToIndex_ = toIndex;
    }

    std::optional<int32_t> GetCustomAnimationToIndex() const
    {
        return customAnimationToIndex_;
    }

    void SetTabsCustomContentTransition(std::function<TabContentAnimatedTransition(int32_t, int32_t)>&& event)
    {
        onTabsCustomContentTransition_ =
            std::make_shared<std::function<TabContentAnimatedTransition(int32_t, int32_t)>>(event);
    }

    CustomContentTransitionPtr GetTabsCustomContentTransition() const
    {
        return onTabsCustomContentTransition_;
    }

    void SetSwiperCustomContentTransition(SwiperContentAnimatedTransition& transition)
    {
        onSwiperCustomContentTransition_ = std::make_shared<SwiperContentAnimatedTransition>(transition);
    }

    std::shared_ptr<SwiperContentAnimatedTransition> GetSwiperCustomContentTransition() const
    {
        return onSwiperCustomContentTransition_;
    }

    void SetOnContentDidScroll(ContentDidScrollEvent&& onContentDidScroll)
    {
        onContentDidScroll_ = std::make_shared<ContentDidScrollEvent>(onContentDidScroll);
    }

    void SetOnContentWillScroll(ContentWillScrollEvent&& onContentWillScroll)
    {
        onContentWillScroll_ = std::make_shared<ContentWillScrollEvent>(onContentWillScroll);
    }

    bool HasOnContentWillScroll() const
    {
        return onContentWillScroll_ && *onContentWillScroll_;
    }

    std::shared_ptr<ContentDidScrollEvent> GetOnContentDidScroll() const
    {
        return onContentDidScroll_;
    }

    void SetSwiperEventCallback(bool disableSwipe);
    void UpdateSwiperPanEvent(bool disableSwipe);
    bool IsUseCustomAnimation() const;

    void SetTabsPaddingAndBorder(const PaddingPropertyF& tabsPaddingAndBorder)
    {
        tabsPaddingAndBorder_ = tabsPaddingAndBorder;
    }

    void InitAnimationCurve();
    RefPtr<Curve> GetCurveIncludeMotion();
    RefPtr<Curve> GetIndicatorHeadCurve();
    float GetMotionVelocity()
    {
        return motionVelocity_;
    }

    int32_t RealTotalCount() const;
    bool IsSwipeByGroup() const;
    int32_t DisplayIndicatorTotalCount() const;
    bool IsAutoLinear() const;
    std::pair<int32_t, int32_t> CalculateStepAndItemCount() const;
    int32_t GetDisplayCount() const;
    int32_t GetCachedCount() const;
    bool ContentWillChange(int32_t comingIndex);
    bool ContentWillChange(int32_t currentIndex, int32_t comingIndex);
    bool CheckSwiperPanEvent(float mainDeltaOrVelocity);
    void InitIndexCanChangeMap()
    {
        indexCanChangeMap_.clear();
    }

    int32_t GetNextValidIndex() const
    {
        return nextValidIndex_;
    }
    void UpdateNextValidIndex();
    void CheckMarkForIndicatorBoundary();
    bool IsHorizontalAndRightToLeft() const;
    TextDirection GetNonAutoLayoutDirection() const;
    void FireSelectedEvent(int32_t currentIndex, int32_t targetIndex);
    void FireWillHideEvent(int32_t willHideIndex) const;
    void FireWillShowEvent(int32_t willShowIndex) const;
    void SetOnHiddenChangeForParent();
    void RemoveOnHiddenChange();

    void SetHasTabsAncestor(bool hasTabsAncestor)
    {
        hasTabsAncestor_ = hasTabsAncestor;
    }

    void SetIndicatorInteractive(bool isInteractive)
    {
        isIndicatorInteractive_ = isInteractive;
    }

    bool IsAtStart() const;
    bool IsAtEnd() const;

    bool IsIndicatorInteractive() const
    {
        return isIndicatorInteractive_;
    }

    void SetNextMarginIgnoreBlank(bool nextMarginIgnoreBlank)
    {
        nextMarginIgnoreBlank_ = nextMarginIgnoreBlank;
    }

    void SetPrevMarginIgnoreBlank(bool prevMarginIgnoreBlank)
    {
        prevMarginIgnoreBlank_ = prevMarginIgnoreBlank;
    }

    void SetFrameRateRange(const RefPtr<FrameRateRange>& rateRange, SwiperDynamicSyncSceneType type) override
    {
        if (rateRange) {
            frameRateRange_[type] = rateRange;
        }
    }
    void UpdateNodeRate();
#ifdef SUPPORT_DIGITAL_CROWN
    virtual void SetDigitalCrownSensitivity(CrownSensitivity sensitivity) {}
    virtual void InitOnCrownEventInternal(const RefPtr<FocusHub>& focusHub) {}
    virtual bool IsCrownSpring() const { return false; }
    virtual void SetIsCrownSpring(bool isCrownSpring) {}
#endif
    int32_t GetMaxDisplayCount() const;
    virtual bool GetDisableFlushFocus() { return false; }
    virtual void SaveCircleDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode) {}
    bool GetPrevMarginIgnoreBlank()
    {
        return prevMarginIgnoreBlank_;
    }

    bool GetNextMarginIgnoreBlank()
    {
        return nextMarginIgnoreBlank_;
    }

    const std::set<int32_t>& GetCachedItems() const
    {
        return cachedItems_;
    }

    void SetCachedItems(const std::set<int32_t>& cachedItems)
    {
        cachedItems_ = cachedItems;
    }

    LayoutConstraintF GetLayoutConstraint() const
    {
        return layoutConstraint_;
    }

    void SetContentMainSize(float contentMainSize)
    {
        contentMainSize_ = contentMainSize;
    }

    bool GetRequestLongPredict() const
    {
        return requestLongPredict_;
    }

    bool IsPropertyAnimationRunning() const
    {
        return propertyAnimationIsRunning_;
    }

    bool IsTranslateAnimationRunning() const
    {
        return translateAnimationIsRunning_;
    }

    bool IsTouchDown() const
    {
        return isTouchDown_;
    }

    bool IsTouchDownOnOverlong() const
    {
        return isTouchDownOnOverlong_ || isDragging_;
    }

    bool IsAutoPlay() const;

    void SetPageFlipMode(int32_t pageFlipMode);

    int32_t GetPageFlipMode() const
    {
        return static_cast<int32_t>(pageFlipMode_);
    }

    bool IsStopWhenTouched() const
    {
        return stopWhenTouched_;
    }

    void SetStopWhenTouched(bool stopWhenTouched)
    {
        stopWhenTouched_ = stopWhenTouched;
    }

    void SetJumpAnimationMode(TabAnimateMode tabAnimationMode)
    {
        tabAnimationMode_ = tabAnimationMode;
    }

    bool NeedFastAnimation() const;
    bool IsInFastAnimation() const;

    float CalcCurrentTurnPageRate(bool isTouchBottom = false) const;
    int32_t GetFirstIndexInVisibleArea() const;
    float CalculateGroupTurnPageRate(float additionalOffset);

    bool IsBindIndicator() const
    {
        return isBindIndicator_;
    }

    void SetBindIndicator(bool bind)
    {
        isBindIndicator_ = bind;
        // Need to reset the last independent indicator first,
        // whether it will rebind to a new independent navigation point.
        ResetIndicatorNode();
    }

    void SetJSIndicatorController(std::function<void()> resetFunc)
    {
        if (resetFunc_) {
            resetFunc_();
        }
        resetFunc_ = resetFunc;
    }

    void SetIndicatorNode(const RefPtr<FrameNode>& indicatorNode);

    void ResetIndicatorNode();

    RefPtr<FrameNode> GetIndicatorNode() const
    {
        auto refUINode = indicatorNode_.Upgrade();
        CHECK_NULL_RETURN(refUINode, nullptr);
        auto frameNode = DynamicCast<FrameNode>(refUINode);
        CHECK_NULL_RETURN(frameNode, nullptr);
        return frameNode;
    }

    void SetIndicatorController(Framework::JSIndicatorController* controller);

    Framework::JSIndicatorController* GetIndicatorController();

    bool IsFocusNodeInItemPosition(const RefPtr<FrameNode>& focusNode);
    virtual RefPtr<Curve> GetCurve() const;

    void SetGestureStatus(GestureStatus gestureStatus)
    {
        gestureStatus_ = gestureStatus;
    }
    bool HasRepeatTotalCountDifference(RefPtr<UINode> node) const;
    int32_t OnInjectionEvent(const std::string& command) override;

    bool GetMaintainVisibleContentPosition()
    {
        auto props = GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_RETURN(props, false);
        return props->GetMaintainVisibleContentPosition().value_or(false);
    }

    void NotifyDataChange(int32_t index, int32_t count) override;

protected:
    void MarkDirtyNodeSelf();
    void OnPropertyTranslateAnimationFinish(const OffsetF& offset);
    void OnAnimationTranslateZero(int32_t nextIndex, bool stopAutoPlay);
    bool NeedStartNewAnimation(const OffsetF& offset) const;
    void StopPropertyTranslateAnimation(bool isFinishAnimation,
        bool isBeforeCreateLayoutWrapper = false, bool isInterrupt = false);
    void StopIndicatorAnimation(bool ifImmediately = false);
    void FireAnimationStartEvent(int32_t currentIndex, int32_t nextIndex, const AnimationCallbackInfo& info) const;
    void SetLazyLoadFeature(bool useLazyLoad);
    void UpdateItemRenderGroup(bool itemRenderGroup);

    float GetCustomPropertyOffset() const;
    float GetCustomPropertyTargetOffset() const;
    float CalculateVisibleSize() const
    {
        return contentMainSize_ - GetPrevMarginWithItemSpace() - GetNextMarginWithItemSpace();
    }
    bool SupportSwiperCustomAnimation() const
    {
        auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
        return (onSwiperCustomContentTransition_ || onContentDidScroll_) &&
            !hasCachedCapture_ && SwiperUtils::IsStretch(swiperLayoutProperty);
    }

    GestureState gestureState_ = GestureState::GESTURE_STATE_INIT;
    int32_t currentIndex_ = 0;
    std::optional<int32_t> fastCurrentIndex_;
    SwiperLayoutAlgorithm::PositionMap itemPosition_;
    SwiperLayoutAlgorithm::PositionMap itemPositionInAnimation_;
    SwiperLayoutAlgorithm::PositionMap itemPositionWillInvisible_;
    std::optional<int32_t> targetIndex_;
    float swiperProportion_ = 2.0f;
    int32_t newMinTurnPageVelocity_ = NEW_STYLE_MIN_TURN_PAGE_VELOCITY;
    int32_t propertyAnimationIndex_ = -1;

    bool hasTabsAncestor_ = false;
    bool usePropertyAnimation_ = false;
    bool stopIndicatorAnimation_ = true;
    bool isFinishAnimation_ = false;
    bool isDragging_ = false;
    float motionVelocity_ = 0.0f;
    float currentIndexOffset_ = 0.0f;

    std::unordered_map<SwiperDynamicSyncSceneType, RefPtr<FrameRateRange>> frameRateRange_;
    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd(double dragVelocity, float mainDelta = 0.0f);

    void HandleTouchDown(const TouchLocationInfo& locationInfo);
    void HandleTouchUp();

    /**
     * @brief Notifies the parent component that the scroll has started at the specified position.
     *
     * @param position The position where the scroll has started.
     */
    void NotifyParentScrollStart(WeakPtr<NestableScrollContainer> child, float position);
    /**
     * @brief Notifies the parent NestableScrollContainer that the scroll has ended.
     */
    void NotifyParentScrollEnd();

    Axis direction_ = Axis::HORIZONTAL;

private:
    Framework::JSIndicatorController* indicatorController_ = nullptr;
    void OnModifyDone() override;
    void OnAfterModifyDone() override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* node) override;
    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;
    void InitSurfaceChangedCallback();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void HandleTargetIndex(const RefPtr<LayoutWrapper>& dirty, const RefPtr<SwiperLayoutAlgorithm>& algo);
    void HandleRunningTranslateAnimation();
    void HandleTargetItemNotFound(
        const RefPtr<SwiperLayoutProperty>& props, int32_t targetIndexValue, const RefPtr<SwiperLayoutAlgorithm>& algo);
    bool IsNeedForwardTranslate(const RefPtr<SwiperLayoutProperty>& props, int32_t targetIndexValue);
    bool IsNeedBackwardTranslate(const RefPtr<SwiperLayoutProperty>& props, int32_t targetIndexValue);
    void HandleTabsAncestor();
    void UpdateLayoutProperties(const RefPtr<SwiperLayoutAlgorithm>& algo);
    // Init pan recognizer to move items when drag update, play translate animation when drag end.
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void AddPanEvent(const RefPtr<GestureEventHub>& gestureHub, GestureEventFunc&& actionStart,
        GestureEventFunc&& actionUpdate, GestureEventFunc&& actionEnd, GestureEventNoParameter&& actionCancel);
    PanEventFunction ActionStartTask();
    PanEventFunction ActionUpdateTask();
    PanEventFunction ActionEndTask();

    // Init touch event, stop animation when touch down.
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitHoverMouseEvent();
    // Init on key event
    void InitOnFocusInternal(const RefPtr<FocusHub>& focusHub);
    void HandleFocusInternal();
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);
    bool IsFocusNodeInItemPosition(const RefPtr<FocusHub>& targetFocusHub);
    void FlushFocus(const RefPtr<FrameNode>& curShowFrame);
    WeakPtr<FocusHub> GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    bool FindFocusableContentIndex(MoveStep moveStep);
    bool IsContentChildFocusable(int32_t childIndex) const;

    // Init indicator
    void InitIndicator();
    void InitArrow();
    void SaveIndicatorProperty(const RefPtr<FrameNode>& indicatorNode, SwiperIndicatorType swiperIndicatorType);

    bool InsideIndicatorRegion(const TouchLocationInfo& locationInfo);
    void HandleTouchEvent(const TouchEventInfo& info);

    void HandleMouseEvent(const MouseInfo& info);
    void PlayTranslateAnimation(
        float startPos, float endPos, int32_t nextIndex, bool restartAutoPlay = false, float velocity = 0.0f);
    void OnTranslateAnimationFinish();
    void PlaySpringAnimation(double dragVelocity);
    void PlayFadeAnimation();

    // use property animation feature
    // ArcSwiper will implement this interface in order to reset the animation effect parameters.
    virtual void ResetAnimationParam() {};
    // ArcSwiper will implement this interface in order to reset the animation effect of the current node.
    virtual void ResetCurrentFrameNodeAnimation() {};
    // ArcSwiper will implement this interface in order to reset the background color of parent node.
    virtual void ResetParentNodeColor() {};
    // ArcSwiper will implement this interface in order to achieve the function of the manual effect.
    virtual void PlayScrollAnimation(float currentDelta, float currentIndexOffset) {};
    virtual void PlayPropertyTranslateAnimation(float translate, int32_t nextIndex, float velocity = 0.0f,
        bool stopAutoPlay = false, std::optional<float> pixelRoundTargetPos = std::nullopt);
    void UpdateOffsetAfterPropertyAnimation(float offset);
    void PlayIndicatorTranslateAnimation(float translate, std::optional<int32_t> nextIndex = std::nullopt);
    void PropertyCancelAnimationFinish(bool isFinishAnimation, bool isBeforeCreateLayoutWrapper, bool isInterrupt);

    // Implement of swiper controller

    void FinishAnimation();
    void StopFadeAnimation();

    bool IsOutOfBoundary(float mainOffset = 0.0f) const;
    bool IsOutOfStart(float mainOffset = 0.0f) const;
    bool IsOutOfEnd(float mainOffset = 0.0f) const;
    bool AutoLinearIsOutOfBoundary(float mainOffset) const;
    float GetDistanceToEdge() const;
    float MainSize() const;
    float GetMainContentSize() const;
    void FireChangeEvent(int32_t preIndex, int32_t currentIndex, bool isInLayout = false) const;
    void FireAnimationEndEvent(int32_t currentIndex, const AnimationCallbackInfo& info, bool isInterrupt = false) const;
    void FireGestureSwipeEvent(int32_t currentIndex, const AnimationCallbackInfo& info) const;
    void FireUnselectedEvent(int32_t currentIndex, int32_t targetIndex);
    void FireSwiperCustomAnimationEvent();
    void FireContentDidScrollEvent();
    void HandleSwiperCustomAnimation(float offset);
    void CalculateAndUpdateItemInfo(float offset = 0.0f);
    void UpdateItemInfoInCustomAnimation(int32_t index, float startPos, float endPos);
    void UpdateTabBarAnimationDuration(int32_t index);

    float GetItemSpace() const;
    float GetPrevMargin() const;
    float GetNextMargin() const;
    float GetPrevMarginWithItemSpace() const
    {
        return Positive(GetPrevMargin()) ? GetPrevMargin() + GetItemSpace() : 0.0f;
    }
    float GetNextMarginWithItemSpace() const
    {
        return Positive(GetNextMargin()) ? GetNextMargin() + GetItemSpace() : 0.0f;
    }
    int32_t CurrentIndex() const;
    int32_t CalculateDisplayCount() const;
    int32_t CalculateCount(
        float contentWidth, float minSize, float margin, float gutter, float swiperPadding = 0.0f) const;
    int32_t GetInterval() const;
    EdgeEffect GetEdgeEffect() const;
    bool IsDisableSwipe() const;
    bool IsShowIndicator() const;
    std::pair<int32_t, SwiperItemInfo> GetFirstItemInfoInVisibleArea() const;
    std::pair<int32_t, SwiperItemInfo> GetLastItemInfoInVisibleArea() const;
    std::pair<int32_t, SwiperItemInfo> GetSecondItemInfoInVisibleArea() const;
    void OnIndexChange(bool isInLayout = false);
    bool IsOutOfHotRegion(const PointF& dragPoint) const;
    void SetDigitStartAndEndProperty(const RefPtr<FrameNode>& indicatorNode);
    void UpdatePaintProperty(const RefPtr<FrameNode>& indicatorNode);
    void PostTranslateTask(uint32_t delayTime);
    void HandleVisibleChange(bool visible);
    void RegisterVisibleAreaChange();
    bool NeedAutoPlay() const;
    void OnTranslateFinish(int32_t nextIndex, bool restartAutoPlay, bool isFinishAnimation, bool forceStop = false,
        bool isInterrupt = false);
    bool IsShowArrow() const;
    void SaveArrowProperty(const RefPtr<FrameNode>& arrowNode);
    RefPtr<FocusHub> GetFocusHubChild(std::string childFrameName);
    WeakPtr<FocusHub> PreviousFocus(const RefPtr<FocusHub>& curFocusNode);
    WeakPtr<FocusHub> NextFocus(const RefPtr<FocusHub>& curFocusNode);
    void SetAccessibilityAction();
    bool NeedStartAutoPlay() const;
    void CheckAndSetArrowHoverState(const PointF& mousePoint);
    RectF GetArrowFrameRect(const int32_t index) const;
    void UpdateAnimationProperty(float velocity);
    void TriggerAnimationEndOnForceStop(bool isInterrupt = false);
    void TriggerAnimationEndOnSwipeToLeft();
    void TriggerAnimationEndOnSwipeToRight();
    void TriggerEventOnFinish(int32_t nextIndex);
    bool IsVisibleChildrenSizeLessThanSwiper() const;
    void BeforeCreateLayoutWrapper() override;
    int32_t CheckUserSetIndex(int32_t index);

    void SetLazyForEachLongPredict(bool useLazyLoad) const;
    void SetLazyLoadIsLoop() const;
    void SetLazyForEachFlag() const;
    float GetVelocityCoefficient();
    int32_t ComputeNextIndexByVelocity(float velocity, bool onlyDistance = false) const;
    void UpdateCurrentIndex(int32_t index);
    void OnSpringAnimationStart(float velocity);
    void OnSpringAnimationFinish();
    float EstimateSpringOffset(float realOffset);
    void OnSpringAndFadeAnimationFinish();
    void OnFadeAnimationStart();
    int32_t TotalDisPlayCount() const;
    void StopAndResetSpringAnimation();
    void CheckLoopChange();
    void StopSpringAnimationAndFlushImmediately();
    void ResetAndUpdateIndexOnAnimationEnd(int32_t nextIndex);
    int32_t GetLoopIndex(int32_t index, int32_t childrenSize) const;
    bool AutoLinearAnimationNeedReset(float translate) const;
    void TriggerCustomContentTransitionEvent(int32_t fromIndex, int32_t toIndex);
    /**
     * @brief Preprocess drag delta when received from DragUpdate event.
     *
     * Drag offset in Swiper can't go beyond a full page. Apply the restriction through this function.
     *
     * @param delta
     * @param mainSize content length along the main axis.
     * @param deltaSum accumulated delta in the current drag event.
     */
    static void ProcessDelta(float& delta, float mainSize, float deltaSum);

    /**
     * @brief Stops animations when the scroll starts.
     *
     * @param flushImmediately Whether to flush layout immediately.
     * @param stopLongPointAnimation Whether to stop indicator long point animation immediately.
     */
    void StopAnimationOnScrollStart(bool flushImmediately, bool stopLongPointAnimation = false);
    /**
     * @return true if any translate animation (switching page / spring) is running, false otherwise.
     */
    inline bool DuringTranslateAnimation() const;
    /**
     * @return true if any translate animation (switching page / spring) is running, ignore animation pause etc.
     */
    inline bool RunningTranslateAnimation() const;
    /**
     * @return true if fade animation is running, false otherwise.
     */
    inline bool DuringFadeAnimation() const;

    /**
     *  NestableScrollContainer implementations
     *  ============================================================
     */
    Axis GetAxis() const override
    {
        return GetDirection();
    }

    /**
     * @brief Closes gap to the edge, called before Swiper transfers extra offset to parent/child to ensure that Swiper
     * actually reaches the edge.
     *
     * @param offset The scroll offset from DragUpdate.
     */
    void CloseTheGap(float& offset);

    void HandleOutBoundarySelf(float offset, float& selfOffset, float& remainOffset);

    ScrollResult HandleOutBoundary(float offset, int32_t source, float velocity);

    ScrollResult HandleScroll(
        float offset, int32_t source, NestedState state = NestedState::GESTURE, float velocity = 0.f) override;

    ScrollResult HandleScrollSelfFirst(float offset, int32_t source, NestedState state, float velocity = 0.f);

    ScrollResult HandleScrollParentFirst(float offset, int32_t source, NestedState state, float velocity = 0.f);

    bool NestedScrollOutOfBoundary() override
    {
        return IsOutOfBoundary();
    }

    bool HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child = nullptr) override;

    void OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float velocity) override;
    void OnScrollEndRecursive(const std::optional<float>& velocity) override;
    void OnScrollDragEndRecursive() override;

    inline bool ChildFirst(NestedState state);
    RefPtr<FrameNode> GetCurrentFrameNode(int32_t currentIndex) const;
    bool FadeOverScroll(float offset);
    int32_t ComputeSwipePageNextIndex(float velocity, bool onlyDistance = false) const;
    int32_t ComputeNextIndexInSinglePage(float velocity, bool onlyDistance) const;
    int32_t ComputePageIndex(int32_t index) const;
    void UpdateIndexOnAnimationStop();
    void UpdateIndexOnSwipePageStop(int32_t pauseTargetIndex);
    void AdjustCurrentFocusIndex();
    bool IsContentFocused();

    int32_t CheckTargetIndex(int32_t targetIndex, bool isForceBackward = false);

    void HandleTouchBottomLoop();
    void HandleTouchBottomLoopOnRTL();
    void CalculateGestureStateOnRTL(float additionalOffset, float currentTurnPageRate, int32_t preFirstIndex);
    void CalculateGestureState(float additionalOffset, float currentTurnPageRate, int32_t preFirstIndex);
    std::pair<float, float> CalcCurrentPageStatus(float additionalOffset) const;
    std::pair<float, float> CalcCurrentPageStatusOnRTL(float additionalOffset, bool isTouchBottom = false) const;

    void PreloadItems(const std::set<int32_t>& indexSet);
    void DoTabsPreloadItems(const std::set<int32_t>& indexSet);
    void DoSwiperPreloadItems(const std::set<int32_t>& indexSet);
    void BuildForEachChild(const std::set<int32_t>& indexSet, const RefPtr<UINode>& child);
    void FirePreloadFinishEvent(int32_t errorCode, std::string message = "");
    // capture node start
    void InitCapture();
    int32_t GetLeftCaptureId()
    {
        if (!leftCaptureId_.has_value()) {
            leftCaptureId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return leftCaptureId_.value();
    }
    int32_t GetRightCaptureId()
    {
        if (!rightCaptureId_.has_value()) {
            rightCaptureId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return rightCaptureId_.value();
    }
    void RemoveAllCaptureNode()
    {
        auto swiperNode = GetHost();
        CHECK_NULL_VOID(swiperNode);
        swiperNode->RemoveChildAtIndex(swiperNode->GetChildIndexById(GetLeftCaptureId()));
        leftCaptureId_ = std::nullopt;
        swiperNode->RemoveChildAtIndex(swiperNode->GetChildIndexById(GetRightCaptureId()));
        rightCaptureId_ = std::nullopt;
    }
    RefPtr<FrameNode> GetLeftCaptureNode()
    {
        auto swiperNode = GetHost();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        return DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetLeftCaptureId())));
    }
    RefPtr<FrameNode> GetRightCaptureNode()
    {
        auto swiperNode = GetHost();
        CHECK_NULL_RETURN(swiperNode, nullptr);
        return DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(swiperNode->GetChildIndexById(GetRightCaptureId())));
    }
    bool IsCaptureNodeValid()
    {
        return hasCachedCapture_ && GetLeftCaptureNode() && GetRightCaptureNode();
    }
    void UpdateTranslateForCaptureNode(const OffsetF& offset, bool cancel = false);
    void UpdateFinalTranslateForSwiperItem(const SwiperLayoutAlgorithm::PositionMap& itemPosition);
    void UpdateTranslateForSwiperItem(SwiperLayoutAlgorithm::PositionMap& itemPosition,
        const OffsetF& offset, bool cancel = false);
    void UpdateTargetCapture(bool forceUpdate);
    void CreateCaptureCallback(int32_t targetIndex, int32_t captureId, bool forceUpdate);
    void UpdateCaptureSource(std::shared_ptr<Media::PixelMap> pixelMap, int32_t captureId, int32_t targetIndex);

    bool SupportSwiperCustomAnimation()
    {
        auto swiperLayoutProperty = GetLayoutProperty<SwiperLayoutProperty>();
        return (onSwiperCustomContentTransition_ || onContentDidScroll_) && !hasCachedCapture_ &&
               SwiperUtils::IsStretch(swiperLayoutProperty);
    }

    void ResetOnForceMeasure();
    void ResetTabBar();
    void UpdateTabBarIndicatorCurve();
    const RefPtr<Curve> GetTabBarAnimationCurve(const RefPtr<Curve>& curve);
    bool CheckDragOutOfBoundary(double dragVelocity);
    void UpdateCurrentFocus();

    void CreateSpringProperty();

    std::optional<RefPtr<UINode>> FindLazyForEachNode(RefPtr<UINode> baseNode, bool isSelfNode = true) const;
    std::optional<RefPtr<UINode>> FindForEachNode(const RefPtr<UINode>& baseNode, bool isSelfNode = true) const;
    bool NeedForceMeasure() const;
    void SetIndicatorChangeIndexStatus(bool withAnimation, std::optional<int32_t> startIndex = std::nullopt);
    void SetIndicatorJumpIndex(std::optional<int32_t> jumpIndex);
    void SetIndicatorIsInFast(std::optional<bool> isInFast);

    void PostIdleTask(const RefPtr<FrameNode>& frameNode);

    float AdjustIgnoreBlankOverScrollOffSet(bool isStartOverScroll) const;
    void UpdateIgnoreBlankOffsetWithIndex();
    // overSrollDirection is true means over start boundary, false means over end boundary.
    void UpdateIgnoreBlankOffsetWithDrag(bool overSrollDirection);
    void UpdateIgnoreBlankOffsetInMap(float lastIgnoreBlankOffset);
    bool NeedEnableIgnoreBlankOffset() const
    {
        return !IsLoop() && (prevMarginIgnoreBlank_ || nextMarginIgnoreBlank_) && TotalCount() > GetDisplayCount();
    }

    bool IsItemOverlay() const;
    void UpdateIndicatorOnChildChange();
    void UpdateDigitalIndicator();

    void CheckSpecialItemCount() const;
    int32_t CheckIndexRange(int32_t index) const;
    void CheckAndFireCustomAnimation();
    void UpdateOverlongForceStopPageRate(float forceStopPageRate);
    bool IsCachedShow() const;
    bool ContentWillScroll(int32_t currentIndex, int32_t comingIndex, float offset);
    bool CheckContentWillScroll(float checkValue, float mainDelta);
    float CalcWillScrollOffset(int32_t comingIndex);
    std::optional<bool> OnContentWillScroll(int32_t currentIndex, int32_t comingIndex, float offset) const;
    std::pair<int32_t, SwiperItemInfo> CalcFirstItemWithoutItemSpace() const;
    int32_t CalcComingIndex(float mainDelta) const;
    void TriggerAddTabBarEvent() const;

    bool ComputeTargetIndex(int32_t index, int32_t& targetIndex) const;
    void FastAnimation(int32_t targetIndex);
    void MarkDirtyBindIndicatorNode() const;

    RefPtr<FrameNode> GetCommonIndicatorNode();
    bool IsIndicator(const std::string& tag) const
    {
        return tag == V2::SWIPER_INDICATOR_ETS_TAG || tag == V2::INDICATOR_ETS_TAG;
    }

    void CheckAndReportEvent();

    void UpdateItemsLatestSwitched();
    void HandleTabsCachedMaxCount(int32_t startIndex, int32_t endIndex);
    void PostIdleTaskToCleanTabContent();
    std::shared_ptr<SwiperParameters> GetBindIndicatorParameters() const;
    int32_t GetNodeId() const;
    bool GetTargetIndex(const std::string& command, int32_t& targetIndex);
    void ReportComponentChangeEvent(
        const std::string& eventType, int32_t currentIndex, bool includeOffset, float offset = 0.0) const;
    void ReportTraceOnDragEnd() const;
    void UpdateBottomTypeOnMultiple(int32_t currentFirstIndex);
    void UpdateBottomTypeOnMultipleRTL(int32_t currentFirstIndex);
    void CheckTargetPositon(float& correctOffset);
    friend class SwiperHelper;

    RefPtr<PanEvent> panEvent_;
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> hoverEvent_;

    // Control translate animation when drag end.
    RefPtr<Animator> controller_;

    // Control spring animation when drag beyond boundary and drag end.
    std::shared_ptr<AnimationUtils::Animation> springAnimation_;

    // Control fade animation when drag beyond boundary and drag end.
    std::shared_ptr<AnimationUtils::Animation> fadeAnimation_;

    // Control translate animation for indicator.
    std::shared_ptr<AnimationUtils::Animation> indicatorAnimation_;

    std::shared_ptr<AnimationUtils::Animation> translateAnimation_;

    bool indicatorAnimationIsRunning_ = false;
    bool translateAnimationIsRunning_ = false;

    // stop indicator animation callback
    std::function<void(bool)> stopIndicatorAnimationFunc_;
    std::function<void(float)> updateOverlongForceStopPageRateFunc_;

    RefPtr<SwiperController> swiperController_;
    RefPtr<InputEvent> mouseEvent_;

    bool isLastIndicatorFocused_ = false;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = 0;
    int32_t oldIndex_ = 0;
    int32_t nextIndex_ = 0;
    int32_t prevStartIndex_ = 0;
    int32_t prevEndIndex_ = 0;

    PanDirection panDirection_;

    float currentOffset_ = 0.0f;
    float fadeOffset_ = 0.0f;
    float springOffset_ = 0.0f;
    float turnPageRate_ = 0.0f;
    float groupTurnPageRate_ = 0.0f;
    float translateAnimationEndPos_ = 0.0f;
    TouchBottomTypeLoop touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    float touchBottomRate_ = 1.0f;
    int32_t gestureSwipeIndex_ = 0;
    int32_t currentFirstIndex_ = 0;
    int32_t nextValidIndex_ = 0;
    int32_t currentFocusIndex_ = 0;
    int32_t selectedIndex_ = -1;
    int32_t unselectedIndex_ = -1;

    bool moveDirection_ = false;
    bool indicatorDoingAnimation_ = false;
    bool isInit_ = true;
    bool hasVisibleChangeRegistered_ = false;
    bool isVisible_ = true;
    bool isVisibleArea_ = false;
    bool isWindowShow_ = true;
    bool isCustomSize_ = false;
    bool indicatorIsBoolean_ = true;
    bool isAtHotRegion_ = false;
    bool needTurn_ = false;
    bool isParentHiddenChange_ = false;
    /**
     * @brief Indicates whether the child NestableScrollContainer is currently scrolling and affecting Swiper.
     */
    bool childScrolling_ = false;
    bool isTouchDown_ = false;
    bool isTouchDownOnOverlong_ = false;
    std::optional<bool> preLoop_;

    ChangeEventPtr changeEvent_;
    ChangeEventPtr onIndexChangeEvent_;
    ChangeEventPtr selectedEvent_;
    ChangeEventPtr unselectedEvent_;
    AnimationStartEventPtr animationStartEvent_;
    AnimationEndEventPtr animationEndEvent_;

    mutable std::shared_ptr<SwiperParameters> swiperParameters_;
    mutable std::shared_ptr<SwiperDigitalParameters> swiperDigitalParameters_;

    WeakPtr<FrameNode> lastWeakShowNode_;

    CancelableCallback<void()> translateTask_;
    CancelableCallback<void()> resetLayoutTask_;

    std::optional<int32_t> indicatorId_;
    std::optional<int32_t> leftButtonId_;
    std::optional<int32_t> rightButtonId_;
    std::optional<int32_t> leftCaptureId_;
    std::optional<int32_t> rightCaptureId_;
    std::optional<SwiperIndicatorType> lastSwiperIndicatorType_;

    float startMainPos_ = 0.0f;
    float endMainPos_ = 0.0f;
    float contentMainSize_ = 0.0f;
    float oldContentMainSize_ = 0.0f;
    float contentMainSizeBeforeAni_ = 0.0f;
    float contentCrossSize_ = 0.0f;
    bool crossMatchChild_ = false;

    std::optional<int32_t> uiCastJumpIndex_;
    std::optional<int32_t> jumpIndex_;
    std::optional<int32_t> runningTargetIndex_;
    std::optional<int32_t> pauseTargetIndex_;
    std::optional<int32_t> oldChildrenSize_;
    std::optional<int32_t> oldRealTotalCount_;
    std::optional<float> placeItemWidth_;
    float currentDelta_ = 0.0f;
    // cumulated delta in a single drag event
    float mainDeltaSum_ = 0.0f;
    std::optional<float> velocity_;
    bool mainSizeIsMeasured_ = false;
    bool propertyAnimationIsRunning_ = false;
    bool syncCancelAniIsFailed_ = false;
    bool springAnimationIsRunning_ = false;
    bool isTouchDownSpringAnimation_ = false;
    bool isTouchDownFadeAnimation_ = false;
    bool isUserFinish_ = true;
    bool isVoluntarilyClear_ = false;
    bool isIndicatorLongPress_ = false;
    bool isTouchPad_ = false;
    bool fadeAnimationIsRunning_ = false;
    bool autoLinearReachBoundary_ = false;
    bool needAdjustIndex_ = false;
    bool isIndicatorInteractive_ = true;
    bool nextMarginIgnoreBlank_ = false;
    bool prevMarginIgnoreBlank_ = false;
    float ignoreBlankOffset_ = 0.0f;
    int32_t swiperId_ = -1;
    float animationCurveStiffness_ = SWIPER_CURVE_STIFFNESS;
    float animationCurveDamping_ = SWIPER_CURVE_DAMPING;

    std::optional<int32_t> cachedCount_;

    std::optional<int32_t> surfaceChangedCallbackId_;

    WindowSizeChangeReason windowSizeChangeReason_ = WindowSizeChangeReason::UNDEFINED;
    std::vector<RefPtr<ScrollingListener>> scrollingListener_;
    FinishCallbackType finishCallbackType_ = FinishCallbackType::REMOVED;

    CustomContentTransitionPtr onTabsCustomContentTransition_;
    std::shared_ptr<SwiperContentAnimatedTransition> onSwiperCustomContentTransition_;
    std::shared_ptr<ContentDidScrollEvent> onContentDidScroll_;
    std::shared_ptr<ContentWillScrollEvent> onContentWillScroll_;
    std::set<int32_t> indexsInAnimation_;
    std::set<int32_t> needUnmountIndexs_;
    std::optional<int32_t> customAnimationToIndex_;
    RefPtr<TabContentTransitionProxy> currentProxyInAnimation_;
    PaddingPropertyF tabsPaddingAndBorder_;
    std::map<int32_t, bool> indexCanChangeMap_;
    // capture
    std::optional<int32_t> leftCaptureIndex_;
    std::optional<int32_t> rightCaptureIndex_;
    bool hasCachedCapture_ = false;
    bool isCaptureReverse_ = false;
    OffsetF captureFinalOffset_;
    bool isInAutoPlay_ = false;

    bool needFireCustomAnimationEvent_ = true;
    // Indicates whether previous frame animation is running, only used on swiper custom animation.
    bool prevFrameAnimationRunning_ = false;
    std::optional<bool> isSwipeByGroup_;
    std::set<WeakPtr<FrameNode>> groupedItems_;

    std::set<int32_t> cachedItems_;
    LayoutConstraintF layoutConstraint_;
    bool requestLongPredict_ = false;

    PageFlipMode pageFlipMode_ = PageFlipMode::CONTINUOUS;
    bool jumpOnChange_ = false;
    TabAnimateMode tabAnimationMode_ = TabAnimateMode::NO_ANIMATION;
    bool isFirstAxisAction_ = true;
    bool stopWhenTouched_ = true;
    WeakPtr<FrameNode> indicatorNode_;
    bool isBindIndicator_ = false;
    std::function<void()> resetFunc_;

    SwiperHoverFlag hoverFlag_ = HOVER_NONE;
    GestureStatus gestureStatus_ = GestureStatus::INIT;

    std::list<int32_t> itemsLatestSwitched_;
    std::set<int32_t> itemsNeedClean_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_PATTERN_H
