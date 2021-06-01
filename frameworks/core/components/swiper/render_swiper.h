/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_RENDER_SWIPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_RENDER_SWIPER_H

#include <functional>
#include <map>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/animation/animation.h"
#include "core/animation/animator.h"
#include "core/animation/keyframe_animation.h"
#include "core/animation/spring_motion.h"
#include "core/common/vibrator/vibrator_proxy.h"
#include "core/components/box/render_box.h"
#include "core/components/common/properties/swiper_indicator.h"
#include "core/components/common/rotation/rotation_controller.h"
#include "core/components/common/rotation/rotation_node.h"
#include "core/components/flex/flex_component.h"
#include "core/components/flex/render_flex.h"
#include "core/components/text/render_text.h"
#include "core/components/text/text_component.h"
#include "core/gestures/click_recognizer.h"
#include "core/gestures/drag_recognizer.h"
#include "core/gestures/raw_recognizer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

struct IndicatorPaintData {
    double width = 0.0;
    double height = 0.0;
    double radius = 0.0;
    Color color;
    Offset position;
    Offset center;
};

struct SwiperIndicatorData {
    bool isDigital = false;
    bool isPressed = false;
    bool isHovered = false;
    IndicatorPaintData indicatorPaintData;
    std::unordered_map<int32_t, IndicatorPaintData> indicatorItemData;
    double pointPadding = 0.0;
    double startEndPadding = 0.0;
    RefPtr<RenderBox> textBoxRender;
    RefPtr<FlexComponent> flexComponent;
    RefPtr<RenderFlex> flexRender;
    RefPtr<TextComponent> textComponentPrev;
    RefPtr<RenderText> textRenderPrev;
    RefPtr<TextComponent> textComponentNext;
    RefPtr<RenderText> textRenderNext;
};

enum class SpringStatus {
    SPRING_STOP = 0,
    SPRING_START,
    FOCUS_SWITCH,
};

// swiper contains content and indicator, their operations are mutually exclusive.
enum class TouchContentType {
    TOUCH_NONE = 0,
    TOUCH_CONTENT,
    TOUCH_INDICATOR
};

using SwiperChangeEndListener = std::function<void(const int32_t)>;
using MoveCallback = std::function<void(int32_t)>;

class ACE_EXPORT SwiperChangeEvent : public BaseEventInfo, public EventToJSONStringAdapter {
    DECLARE_RELATIONSHIP_OF_CLASSES(SwiperChangeEvent, BaseEventInfo, EventToJSONStringAdapter);

public:
    SwiperChangeEvent(int32_t index) : BaseEventInfo("SwiperChangeEvent"), index_(index) {}
    ~SwiperChangeEvent() = default;

    int32_t GetIndex() const
    {
        return index_;
    }

    std::string ToJSONString() const override
    {
        return std::string(R"("change",{"index":)").append(std::to_string(index_).append("},null"));
    }

private:
    int32_t index_ = 0;
};

class ACE_EXPORT RenderSwiper : public RenderNode, public RotationNode {
    DECLARE_ACE_TYPE(RenderSwiper, RenderNode, RotationNode)

public:
    ~RenderSwiper() override;
    static RefPtr<RenderNode> Create();
    void Update(const RefPtr<Component>& component) override;
    void UpdateTouchRect() override;
    void PerformLayout() override;
    int32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }
    void OnFocus();
    void OnBlur();
    void RegisterChangeEndListener(int32_t listenerId, const SwiperChangeEndListener& listener);
    void UnRegisterChangeEndListener(int32_t listenerId);
    bool OnRotation(const RotationEvent& event) override;
    void OnStatusChanged(RenderStatus renderStatus) override;
    void IndicatorShowFocus(bool isFocus);
    void UpdateIndicatorFocus(bool isFocus, bool reverse);

    bool GetMoveStatus() const
    {
        return moveStatus_;
    }

    void ExecuteMoveCallback(int32_t index)
    {
        if (moveCallback_) {
            moveCallback_(index);
        }
    }

    void DisableSwipe(bool disableSwipe)
    {
        disableSwipe_ = disableSwipe;
    }

    /* indicator animimation begin */
    // indicator status init
    void InitIndicatorAnimation(const WeakPtr<PipelineContext>& context);
    void CalMaxStretch();

    // indicator with move or drag
    void MoveIndicator(int32_t toIndex, double offset, bool isAuto = false);
    void DragIndicator(double offset);
    void DragIndicatorEnd();
    void DragEdgeStretch(double offset);
    void VibrateIndicator();

    // indicator animation function
    void StartIndicatorAnimation(int32_t fromIndex, int32_t toIndex, bool isLoop = false);
    void StopIndicatorAnimation();
    void StartIndicatorSpringAnimation(double start, double end);
    void StopIndicatorSpringAnimation();
    void StartZoomInAnimation(bool isMouseHover = false);
    void StartZoomOutAnimation(bool isMouseHover = false);
    void StartZoomInDotAnimation(int32_t index);
    void StartZoomOutDotAnimation();
    void StopZoomAnimation();
    void StopZoomDotAnimation();
    void StartDragRetractionAnimation(); // on handle drag end
    void StopDragRetractionAnimation();
    void FinishAllSwipeAnimation();
    bool IsZoomAnimationStopped();
    bool IsZoomOutAnimationStopped();
    bool IsZoomOutDotAnimationStopped();

    // indicator info update with animimation
    void UpdateIndicatorLayout();
    void UpdateIndicatorOffset(int32_t fromIndex, int32_t toIndex, double value);
    void UpdateIndicatorHeadPosistion(double offset);
    void UpdateIndicatorTailPosistion(double offset, double switchOffset = 0.0);
    void UpdateIndicatorPointPosistion(double offset);
    void UpdateMaskOpacity(double value);
    void UpdateZoomValue(double value);
    void UpdateZoomDotValue(double value);
    void UpdateEdgeStretchRate(double value); // input 0.0 ~ 1.0 to real rate of high and witdh
    void UpdatePressStatus(bool isPress);
    void UpdateHoverStatus(bool isHover);
    void UpdatePositionOnStretch(Offset& position, const SwiperIndicatorData& indicatorData);
    void UpdateIndicatorSpringStatus(SpringStatus status);
    SpringStatus GetIndicatorSpringStatus() const;
    void ResetIndicatorSpringStatus();
    void ResetIndicatorPosition();
    void ResetHoverZoomDot();
    void MarkIndicatorPosition(bool isZoomMax = true);
    /* indicator animimation end */

protected:
    struct IndicatorProperties final {
        IndicatorProperties(const Offset& normalPaddingStart, const Offset& normalPaddingEnd,
            const Offset& selectedPaddingStart, const Offset& selectedPaddingEnd, const Offset& centerPadding,
            uint32_t normalColor, uint32_t selectedColor, double normalPointRadius, double selectedPointRadius,
            double indicatorPointPadding)
            : normalPaddingStart(normalPaddingStart), normalPaddingEnd(normalPaddingEnd),
              selectedPaddingStart(selectedPaddingStart), selectedPaddingEnd(selectedPaddingEnd),
              centerPadding(centerPadding), normalColor(normalColor), selectedColor(selectedColor),
              normalPointRadius(normalPointRadius), selectedPointRadius(selectedPointRadius),
              indicatorPointPadding(indicatorPointPadding)
        {}
        IndicatorProperties(IndicatorProperties&& indicatorProperties) = default;
        ~IndicatorProperties() = default;

        Offset normalPaddingStart;
        Offset normalPaddingEnd;
        Offset selectedPaddingStart;
        Offset selectedPaddingEnd;
        Offset centerPadding;
        uint32_t normalColor;
        uint32_t selectedColor;
        double normalPointRadius;
        double selectedPointRadius;
        double indicatorPointPadding;
    };
    virtual void UpdateIndicator() = 0;
    void OnHiddenChanged(bool hidden) override;
    double GetValidEdgeLength(double swiperLength, double indicatorLength, const Dimension& edge) const;
    void GetIndicatorCurrentRect(SwiperIndicatorData& indicatorData);
    double GetIndicatorWidth(SwiperIndicatorData& indicatorData);
    void LayoutIndicator(SwiperIndicatorData& indicatorData);
    void InitDigitalIndicator(SwiperIndicatorData& indicatorData);
    void LayoutDigitalIndicator(SwiperIndicatorData& indicatorData);
    void UpdateIndicatorPosition(SwiperIndicatorData& indicatorData);
    void UpdateIndicatorItem(SwiperIndicatorData& indicatorData);
    void IndicatorSwipePrev();
    void IndicatorSwipeNext();
    bool MouseHoverTest(const Point& parentLocalPoint) override;

    // swiper item
    std::vector<RefPtr<RenderNode>> childrenArray_;
    double scale_ = 0.0;
    int32_t itemCount_ = 0;
    float animationDuration_ = 0.0f;
    double swiperWidth_ = 0.0;
    double swiperHeight_ = 0.0;
    int32_t currentIndex_ = 0;
    int32_t targetIndex_ = 0;
    int32_t outItemIndex_ = 0;
    Axis axis_ = Axis::HORIZONTAL;
    AnimationCurve animationCurve_ = AnimationCurve::FRICTION;
    bool animationOpacity_ = true;
    bool needReverse_ = false;
    bool moveStatus_ = false;
    bool show_ = true;
    bool digitalIndicator_ = false;
    bool onFocus_ = false;

    // swiper indicator
    RefPtr<SwiperIndicator> indicator_;
    SwiperIndicatorData swiperIndicatorData_;
    Offset indicatorPosition_;
    Offset indicatorZoomMaxPositionLT_; // left and top position when zoom max
    Offset indicatorZoomMaxPositionRB_; // right and bottom position when zoom max
    Offset indicatorZoomMinPositionLT_; // left and top position when zoom min
    Offset indicatorZoomMinPositionRB_; // right and bottom position when zoom min
    Rect indicatorRect_;
    int32_t currentHoverIndex_ = -1;
    int64_t startTimeStamp_ = 0;
    int32_t fingerId_ = -1;
    bool indicatorIsFocus_ = false;

    // indicator dynamic offset info used by canvas
    double animationDirect_ = 1.0; // 1.0 or -1.0
    double indicatorHeadOffset_ = 0.0; // [0.0, 1.0)
    double indicatorTailOffset_ = 0.0; // [0.0, 1.0)
    double indicatorPointOffset_ = 0.0; // [0.0, 1.0)
    double indicatorSwitchTailOffset_ = 0.0; // [0.0, 1.0)
    double opacityValue_ = 0.0;
    double focusStretchMaxTime_ = 0.0; // the time of focus indicator stretch longest in range [0.0, 1.0]

    // indicator animation flag
    bool isIndicatorAnimationStart_ = false;
    bool isDragStart_ = false;

private:
    // for handle drag event
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    void HandleTouchDown(const TouchEventInfo& info);
    void HandleTouchUp(const TouchEventInfo& info);
    void HandleTouchMove(const TouchEventInfo& info);
    void HandleClick(const ClickInfo& clickInfo);
    void HandleDragStart(const DragStartInfo& info);
    void HandleDragUpdate(const DragUpdateInfo& info);
    void HandleDragEnd(const DragEndInfo& info);

    void Initialize(const WeakPtr<PipelineContext>& context);
    void InitRecognizer();
    void InitDragRecognizer();
    void InitRawDragRecognizer();
    void InitAccessibilityEventListener();
    void MoveItems(double dragOffset, int32_t fromIndex, int32_t toIndex);
    void RestoreAutoPlay()
    {
        if (autoPlay_) {
            bool playEnding = currentIndex_ >= itemCount_ - 1 && !loop_;
            if (playEnding && scheduler_->IsActive()) {
                scheduler_->Stop();
            } else {
                scheduler_->Start();
            }
        }
    }
    void StopSwipeAnimation()
    {
        if (controller_ && !controller_->IsStopped()) {
            // clear stop listener before stop, otherwise the previous swipe will be considered complete
            controller_->ClearStopListeners();
            controller_->Stop();
            isIndicatorAnimationStart_ = false;
        }
    }

    void FireItemChangedEvent() const;
    void SwipeTo(int32_t index, bool reverse);
    int32_t GetPrevIndex() const;
    int32_t GetNextIndex() const;
    int32_t GetPrevIndexOnAnimation() const;
    int32_t GetNextIndexOnAnimation() const;
    void ShowPrevious();
    void ShowNext();
    void InitSwipeToAnimation(double start, double end);
    void AddSwipeToTranslateListener(int32_t fromIndex, int32_t toIndex);
    void AddSwipeToOpacityListener(int32_t fromIndex, int32_t toIndex);
    void AddSwipeToIndicatorListener(int32_t fromIndex, int32_t toIndex);
    double CalculateEndOffset(int32_t fromIndex, int32_t toIndex, bool reverse);
    void DoSwipeToAnimation(int32_t fromIndex, int32_t toIndex, bool reverse);
    void RedoSwipeToAnimation(int32_t toIndex, bool reverse);
    void StopSwipeToAnimation();
    void UpdateItemOpacity(uint8_t opacity, int32_t index);
    void UpdateItemPosition(double offset, int32_t index);

    void UpdateScrollPosition(double dragDelta);
    void UpdateChildPosition(double offset, int32_t fromIndex, int32_t toIndex);
    Offset GetMainAxisOffset(double offset) const
    {
        return axis_ == Axis::HORIZONTAL ? Offset(offset, 0) : Offset(0, offset);
    }
    // timer tick callback, duration is in millisecond.
    void Tick(uint64_t duration);

    RefPtr<RawRecognizer> rawRecognizer_;
    RefPtr<ClickRecognizer> clickRecognizer_;
    RefPtr<DragRecognizer> dragDetector_;
    RefPtr<Animation<double>> translate_;
    RefPtr<Animator> controller_;
    RefPtr<Animator> swipeToController_;

    RefPtr<KeyframeAnimation<double>> curTranslateAnimation_;
    RefPtr<KeyframeAnimation<double>> targetTranslateAnimation_;
    RefPtr<KeyframeAnimation<uint8_t>> curOpacityAnimation_;
    RefPtr<KeyframeAnimation<uint8_t>> targetOpacityAnimation_;

    bool isAnimationAlreadyAdded_ = false;
    bool hasDragAction_ = false;
    bool isSwipeToAnimationAdded_ = false;
    std::function<void(const std::shared_ptr<BaseEventInfo>&)> changeEvent_;
    std::function<void(const std::string&)> rotationEvent_;
    std::function<void()> clickEvent_;

    double prevItemOffset_ = 0.0;
    double nextItemOffset_ = 0.0;
    double scrollOffset_ = 0.0;
    double rotationStepValue_ = 0.0;
    bool autoPlay_ = false;
    bool loop_ = true;
    bool slideContinued_  = false;
    bool disableSwipe_ = false;
    bool indexInitialized = false;

    // need timer for auto play
    RefPtr<Scheduler> scheduler_;
    uint64_t elapsedTime_ = 0; // millisecond.
    uint64_t autoPlayInterval_ = 0;
    std::map<int32_t, std::function<void(const int32_t&)>> changeEndListeners_;
    MoveCallback moveCallback_;

    // indicator animimation controller and indicator dyanamic info.
    RefPtr<SpringMotion> indicatorSpringMotion_;
    RefPtr<Animation<double>> indicatorAnimation_;
    RefPtr<Animation<double>> zoomInDotAnimation_;
    RefPtr<Animation<double>> zoomOutDotAnimation_;
    RefPtr<Animation<double>> zoomInAnimation_;
    RefPtr<Animation<double>> zoomOutAnimation_;
    RefPtr<Animation<double>> opacityInAnimation_;
    RefPtr<Animation<double>> opacityOutAnimation_;
    RefPtr<Animation<double>> dragRetractionAnimation_;
    RefPtr<Animator> zoomInController_;
    RefPtr<Animator> zoomOutController_;
    RefPtr<Animator> zoomInDotController_;
    RefPtr<Animator> zoomOutDotController_;
    RefPtr<Animator> springController_;
    RefPtr<Animator> indicatorController_;
    RefPtr<Animator> dragRetractionController_;
    RefPtr<Vibrator> vibrator_ = nullptr;
    SpringStatus indicatorSpringStatus_ = SpringStatus::SPRING_STOP;
    TouchContentType touchContentType_ = TouchContentType::TOUCH_NONE;
    double hotZoneMaxSize_ = 0.0;
    double hotZoneMinSize_ = 0.0;
    double hotZoneRealSize_ = 0.0;
    double zoomValue_ = 0.0;
    double zoomDotValue_ = 0.0;
    double stretchRate_ = 0.0;
    double widthStretchRate_ = 1.0;
    double heightStretchRate_ = 1.0;
    double dragBaseOffset_ = 0.0;
    double dragMoveOffset_ = 0.0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SWIPER_RENDER_SWIPER_H
