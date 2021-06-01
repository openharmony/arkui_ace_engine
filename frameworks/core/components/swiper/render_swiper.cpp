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

#include "core/components/swiper/render_swiper.h"

#include "core/animation/curve_animation.h"
#include "core/animation/friction_motion.h"
#include "core/animation/keyframe.h"
#include "core/common/frontend.h"
#include "core/components/align/render_align.h"
#include "core/components/display/render_display.h"
#include "core/components/swiper/swiper_component.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {

constexpr double MAX_VIEW_PORT_WIDTH = 1080.0;
constexpr int32_t LEAST_SLIDE_ITEM_COUNT = 2;
constexpr uint8_t MAX_OPACITY = 255;
constexpr double CUR_START_TRANSLATE_TIME = 0.0;
constexpr double CUR_END_TRANSLATE_TIME = 1.0;
constexpr double CUR_START_OPACITY_TIME = 0.0;
constexpr uint8_t CUR_START_OPACITY_VALUE = 255;
constexpr uint8_t CUR_END_OPACITY_VALUE = 0;
constexpr double CUR_END_OPACITY_TIME = 0.5;
constexpr double TARGET_START_TRANSLATE_TIME = 0.0;
constexpr double TARGET_END_TRANSLATE_TIME = 1.0;
constexpr double TARGET_START_OPACITY_TIME = 0.3;
constexpr double TARGET_END_OPACITY_TIME = 1.0;
constexpr uint8_t TARGET_START_OPACITY_VALUE = 0;
constexpr uint8_t TARGET_END_OPACITY_VALUE = 255;
constexpr float SWIPE_TO_ANIMATION_TIME = 500.0f;
constexpr uint8_t TRANSLATE_RATIO = 10;
constexpr int32_t COMPONENT_CHANGE_END_LISTENER_KEY = 1001;
constexpr double THRESHOLD = 90.0;
constexpr double SWIPER_ROTATION_SENSITIVITY_NORMAL = 1.4;
constexpr double MIN_SCROLL_OFFSET = 0.20;

// for indicator animation const param
constexpr double SPRING_MASS = 1.0;
constexpr double SPRING_STIFF = 700.0;
constexpr double SPRING_DAMP = 22.0;
constexpr double SPRING_DAMP_INC = 5.0;
constexpr double DRAG_CALC_STRETCH_STEP = 0.01;
constexpr double DRAG_OFFSET_START_DP = 4.0;
constexpr double DRAG_OFFSET_SWITCH_DP = 14.0;
constexpr double DRAG_STRETCH_LONGEST_DP = 80.0;
constexpr double DRAG_STRETCH_BASE_WIDTH = 1.0;
constexpr double DRAG_STRETCH_BASE_HIGH = 1.0;
constexpr double DRAG_STRETCH_MAX_WIDTH = 1.2;
constexpr double DRAG_STRETCH_MAX_HIGH = 0.8;
constexpr double DRAG_OFFSET_MIN = 0.0;
constexpr double DRAG_OFFSET_MAX = 1.0;
constexpr double ZOOM_MIN = 0.0;
constexpr double ZOOM_MAX = 1.0;
constexpr double OPACITY_MIN = 0.0;
constexpr double OPACITY_MAX = 0.1;
constexpr double ZOOM_DOT_MIN = 0.0;
constexpr double ZOOM_DOT_MAX = 1.0;
constexpr double ZOOM_HOTZONE_MAX_RATE = 1.33;
constexpr double INDICATOR_DIRECT_RTL = 1.0;
constexpr double INDICATOR_DIRECT_LTR = -1.0;
constexpr int32_t VIBRATE_DURATION = 30;
constexpr int32_t ZOOM_IN_DURATION = 250;
constexpr int32_t ZOOM_OUT_DURATION = 250;
constexpr int32_t ZOOM_OUT_HOVER_DURATION = 250;
constexpr int32_t ZOOM_IN_DOT_DURATION = 100;
constexpr int32_t ZOOM_OUT_DOT_DURATION = 150;
constexpr int32_t DRAG_RETRETION_DURATION = 250;
constexpr int32_t INDICATOR_START_ANIMATION = 400;

// indicator animation curve
const RefPtr<CubicCurve> INDICATOR_FOCUS_HEAD = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 1.0f, 1.0f);
const RefPtr<CubicCurve> INDICATOR_FOCUS_TAIL = AceType::MakeRefPtr<CubicCurve>(1.0f, 0.0f, 1.0f, 1.0f);
const RefPtr<CubicCurve> INDICATOR_NORMAL_POINT = AceType::MakeRefPtr<CubicCurve>(0.4f, 0.0f, 1.0f, 1.0f);
const RefPtr<CubicCurve> INDICATOR_ZONE_STRETCH = AceType::MakeRefPtr<CubicCurve>(0.1f, 0.2f, 0.48f, 1.0f);

// for indicator
constexpr double DELAY_TIME_DEFAULT = 50;
constexpr int32_t TIME_RATIO = 1000;
constexpr int32_t INDICATOR_INVALID_HOVER_INDEX = -1;
constexpr Dimension INDICATOR_PADDING_TOP_DEFAULT = 9.0_vp;
constexpr Dimension INDICATOR_DIGITAL_PADDING = 8.0_vp;
constexpr Dimension INDICATOR_FOCUS_DEL_OFFSET = 4.0_vp;
constexpr Dimension INDICATOR_FOCUS_DEL_SIZE = 8.0_vp;
constexpr Dimension INDICATOR_FOCUS_RADIUS_DEL_SIZE = 3.0_vp;
constexpr int32_t INDICATOR_FOCUS_COLOR = 0x0a59f7;

} // namespace

RenderSwiper::~RenderSwiper()
{
    if (autoPlay_ && scheduler_ && scheduler_->IsActive()) {
        scheduler_->Stop();
    }
}

void RenderSwiper::Update(const RefPtr<Component>& component)
{
    const RefPtr<SwiperComponent> swiper = AceType::DynamicCast<SwiperComponent>(component);
    if (!swiper) {
        LOGW("swiper component is null");
        return;
    }
    auto context = context_.Upgrade();
    ACE_DCHECK(context);
    if (swiper->GetUpdateType() == UpdateType::STYLE) {
        // only update indicator when update style
        indicator_ = swiper->GetIndicator();
        MarkNeedRender();
        return;
    }
    disableSwipe_ = swiper->GetDisableSwipe();
    scale_ = context->GetDipScale();
    slideContinued_ = swiper->GetSlideContinue();
    moveCallback_ = swiper->GetMoveCallback();
    itemCount_ = swiper->GetChildren().size();
    animationDuration_ = swiper->GetDuration();
    indicator_ = swiper->GetIndicator();
    digitalIndicator_ = swiper->GetDigitalIndicator();
    changeEvent_ =
        AceAsyncEvent<void(const std::shared_ptr<BaseEventInfo>&)>::Create(swiper->GetChangeEventId(), context_);
    rotationEvent_ = AceAsyncEvent<void(const std::string&)>::Create(swiper->GetRotationEventId(), context_);
    clickEvent_ = AceAsyncEvent<void()>::Create(swiper->GetClickEventId(), context_);
    RegisterChangeEndListener(COMPONENT_CHANGE_END_LISTENER_KEY, swiper->GetChangeEndListener());
    autoPlay_ = swiper->IsAutoPlay();
    if (context && context->IsJsCard()) {
        autoPlay_ = false;
    }
    loop_ = swiper->IsLoop();
    show_ = swiper->IsShow();
    autoPlayInterval_ = swiper->GetAutoPlayInterval();
    axis_ = swiper->GetAxis();
    needReverse_ = (swiper->GetTextDirection() == TextDirection::RTL) && (axis_ == Axis::HORIZONTAL);
    animationCurve_ = swiper->GetAnimationCurve();
    animationOpacity_ = swiper->IsAnimationOpacity();
    const auto& swiperController = swiper->GetSwiperController();
    if (swiperController) {
        auto weak = AceType::WeakClaim(this);
        swiperController->SetSwipeToImpl([weak](int32_t index, bool reverse) {
            auto swiper = weak.Upgrade();
            if (swiper) {
                swiper->SwipeTo(index, reverse);
            }
        });
        swiperController->SetShowPrevImpl([weak]() {
            auto swiper = weak.Upgrade();
            if (swiper) {
                swiper->ShowPrevious();
            }
        });
        swiperController->SetShowNextImpl([weak]() {
            auto swiper = weak.Upgrade();
            if (swiper) {
                swiper->ShowNext();
            }
        });
    }

    const auto& rotationController = swiper->GetRotationController();
    if (rotationController) {
        auto weak = AceType::WeakClaim(this);
        rotationController->SetRequestRotationImpl(weak, context_);
    }

    int32_t index = swiper->GetIndex();
    // can't change index when stretch indicator, as stretch direct is single.
    if (index >= 0 && stretchRate_ == 0.0) {
        if (index >= itemCount_) {
            index = itemCount_ - 1;
        }
        if (indexInitialized) {
            SwipeTo(index, false);
        } else {
            currentIndex_ = index;
            indexInitialized = true;
        }
    }

    childrenArray_.clear();
    MarkNeedLayout();

    if (itemCount_ < LEAST_SLIDE_ITEM_COUNT) {
        LOGD("swiper item is less than least slide count");
        return;
    }
    Initialize(GetContext());
}

void RenderSwiper::UpdateTouchRect()
{
    touchRect_.SetSize(GetLayoutSize());
    touchRect_.SetOffset(GetPosition());
}

void RenderSwiper::PerformLayout()
{
    // layout all children
    const auto& children = GetChildren();
    if (childrenArray_.empty()) {
        childrenArray_ = std::vector<RefPtr<RenderNode>>(children.begin(), children.end());
    }

    LayoutParam innerLayout = GetLayoutParam();
    int32_t childrenSize = static_cast<int32_t>(childrenArray_.size());
    Size minSize = GetLayoutParam().GetMinSize();
    Size maxSize = GetLayoutParam().GetMaxSize();
    double maxWidth = minSize.Width();
    double maxHeight = minSize.Height();
    for (int32_t i = 0; i < childrenSize; i++) {
        const auto& childItem = childrenArray_[i];
        childItem->Layout(innerLayout);
        maxWidth = std::max(maxWidth, childItem->GetLayoutSize().Width());
        maxHeight = std::max(maxHeight, childItem->GetLayoutSize().Height());
    }
    if (maxSize.IsInfinite()) {
        SetLayoutSize(Size(maxWidth, maxHeight));
    } else {
        SetLayoutSize(maxSize);
    }
    Size layoutSize = GetLayoutSize();
    swiperWidth_ = layoutSize.Width();
    swiperHeight_ = layoutSize.Height();

    prevItemOffset_ = axis_ == Axis::HORIZONTAL ? (needReverse_ ? swiperWidth_ : -swiperWidth_) : -swiperHeight_;
    nextItemOffset_ = axis_ == Axis::HORIZONTAL ? (needReverse_ ? -swiperWidth_ : swiperWidth_) : swiperHeight_;
    Offset prevItemPosition = GetMainAxisOffset(prevItemOffset_);
    Offset nextItemPosition = GetMainAxisOffset(nextItemOffset_);
    for (int32_t i = 0; i < childrenSize; i++) {
        const auto& childItem = childrenArray_[i];
        if (i < currentIndex_) {
            childItem->SetPosition(prevItemPosition);
        } else if (i == currentIndex_) {
            childItem->SetPosition(Offset::Zero());
        } else {
            childItem->SetPosition(nextItemPosition);
        }
    }
    // layout indicator
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        LayoutIndicator(swiperIndicatorData_);
    } else {
        UpdateIndicator();
    }
}

void RenderSwiper::Initialize(const WeakPtr<PipelineContext>& context)
{
    if (!disableSwipe_) {
        if (axis_ == Axis::VERTICAL) {
            dragDetector_ = AceType::MakeRefPtr<VerticalDragRecognizer>();
        } else {
            dragDetector_ = AceType::MakeRefPtr<HorizontalDragRecognizer>();
        }
    }
    if (!controller_) {
        controller_ = AceType::MakeRefPtr<Animator>(context);
    } else {
        StopSwipeAnimation();
    }
    if (!swipeToController_) {
        swipeToController_ = AceType::MakeRefPtr<Animator>(context);
    }

    InitIndicatorAnimation(context);
    InitRecognizer();
    InitAccessibilityEventListener();

    // for auto play
    auto weak = AceType::WeakClaim(this);
    if (!scheduler_) {
        auto&& callback = [weak](uint64_t duration) {
            auto swiper = weak.Upgrade();
            if (swiper) {
                swiper->Tick(duration);
            } else {
                LOGW("empty swiper, skip tick callback.");
            }
        };
        scheduler_ = SchedulerBuilder::Build(callback, context);
    } else if (scheduler_->IsActive()) {
        LOGD("stop autoplay");
        scheduler_->Stop();
    }

    if (autoPlay_ && !scheduler_->IsActive() && show_) {
        LOGD("start autoplay");
        scheduler_->Start();
    }
}

void RenderSwiper::InitRecognizer()
{
    if (!clickRecognizer_) {
        auto weak = AceType::WeakClaim(this);
        clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
        clickRecognizer_->SetOnClick([weak](const ClickInfo& info) {
            auto client = weak.Upgrade();
            if (client) {
                client->HandleClick(info);
            }
        });
    }
    auto context = context_.Upgrade();
    if (context && context->IsJsCard()) {
        return;
    }
    InitDragRecognizer();
    InitRawDragRecognizer();
}

void RenderSwiper::InitRawDragRecognizer()
{
    if (!rawRecognizer_) {
        rawRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
        auto weak = AceType::WeakClaim(this);
        rawRecognizer_->SetOnTouchDown([weak](const TouchEventInfo& info) {
            auto client = weak.Upgrade();
            if (client) {
                client->HandleTouchDown(info);
            }
        });
        rawRecognizer_->SetOnTouchUp([weak](const TouchEventInfo& info) {
            auto client = weak.Upgrade();
            if (client) {
                client->HandleTouchUp(info);
            }
        });
        rawRecognizer_->SetOnTouchMove([weak](const TouchEventInfo& info) {
            auto client = weak.Upgrade();
            if (client) {
                client->HandleTouchMove(info);
            }
        });
    }
}

void RenderSwiper::InitDragRecognizer()
{
    auto weak = AceType::WeakClaim(this);
    if (!dragDetector_) {
        return;
    }
    dragDetector_->SetOnDragStart([weak](const DragStartInfo& info) {
        auto client = weak.Upgrade();
        if (client) {
            client->HandleDragStart(info);
        }
    });
    dragDetector_->SetOnDragUpdate([weak](const DragUpdateInfo& info) {
        auto client = weak.Upgrade();
        if (client) {
            client->HandleDragUpdate(info);
        }
    });
    dragDetector_->SetOnDragEnd([weak](const DragEndInfo& info) {
        auto client = weak.Upgrade();
        if (client) {
            client->HandleDragEnd(info);
        }
    });
}

void RenderSwiper::InitAccessibilityEventListener()
{
    auto refNode = accessibilityNode_.Upgrade();
    if (!refNode) {
        return;
    }
    refNode->AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
    refNode->AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);

    auto weakPtr = AceType::WeakClaim(this);
    refNode->SetActionScrollForward([weakPtr]() {
        auto swiper = weakPtr.Upgrade();
        if (swiper) {
            swiper->ShowPrevious();
            return true;
        }
        return false;
    });
    refNode->SetActionScrollBackward([weakPtr]() {
        auto swiper = weakPtr.Upgrade();
        if (swiper) {
            swiper->ShowNext();
            return true;
        }
        return false;
    });
}

void RenderSwiper::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (dragDetector_) {
        dragDetector_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(dragDetector_);
    }
    if (rawRecognizer_) {
        rawRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(rawRecognizer_);
    }
    if (clickRecognizer_) {
        clickRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(clickRecognizer_);
    }
}

void RenderSwiper::HandleTouchDown(const TouchEventInfo& info)
{
    if (info.GetTouches().empty()) {
        return;
    }
    const auto& locationInfo = info.GetTouches().front();
    Point touchPoint = Point(locationInfo.GetGlobalLocation().GetX(), locationInfo.GetGlobalLocation().GetY());
    if (fingerId_ >= 0 && locationInfo.GetFingerId() != fingerId_) {
        return;
    }

    GetIndicatorCurrentRect(swiperIndicatorData_);
    if (indicatorRect_.IsInRegion(touchPoint)) {
        fingerId_ = locationInfo.GetFingerId();
        startTimeStamp_ = clock();
        if (isIndicatorAnimationStart_) {
            touchContentType_ = TouchContentType::TOUCH_NONE;
            return;
        }
        touchContentType_ = TouchContentType::TOUCH_INDICATOR;
    } else {
        touchContentType_ = TouchContentType::TOUCH_CONTENT;
        if (hasDragAction_ && slideContinued_) {
            controller_->Finish();
            return;
        }
        // when is in item moving animation, touch event will break animation and stop in current position
        StopSwipeAnimation();
        StopIndicatorAnimation();
        if (autoPlay_) {
            scheduler_->Stop();
        }
    }
    StopIndicatorSpringAnimation();
}

// touch up event before than click event
void RenderSwiper::HandleTouchUp(const TouchEventInfo& info)
{
    // for indicator
    startTimeStamp_ = 0;
    int32_t fingerId = -1;
    if (!info.GetTouches().empty()) {
        fingerId = info.GetTouches().front().GetFingerId();
    } else if (!info.GetChangedTouches().empty()) {
        fingerId = info.GetChangedTouches().front().GetFingerId();
    }
    if (fingerId_ >= 0 && fingerId != fingerId_) {
        return;
    }

    // indicator zone
    if (touchContentType_ == TouchContentType::TOUCH_NONE) {
        LOGD(" touch content type is none");
        return;
    } else if (touchContentType_ == TouchContentType::TOUCH_INDICATOR) {
        if (swiperIndicatorData_.isPressed) {
            fingerId_ = -1;
            if (isDragStart_) {
                // reset flag of isPressed by function of HandleDragEnd.
                isDragStart_ = false;
                return;
            }
            if (IsZoomOutAnimationStopped()) {
                // reset flag of isPressed after zoom out animation
                StartZoomOutAnimation();
            }
        }
        return;
    }

    // content zone
    if (slideContinued_) {
        return;
    }
    if (hasDragAction_) {
        hasDragAction_ = false;
        return;
    }
    if (isIndicatorAnimationStart_) {
        return;
    }
    // restore the item position that slides to half stopped by a touch event during autoplay
    scrollOffset_ = fmod(scrollOffset_, nextItemOffset_);
    if (scrollOffset_ > 0.0) {
        MoveItems(scrollOffset_, currentIndex_, needReverse_ ? GetNextIndex() : GetPrevIndex());
    } else if (scrollOffset_ < 0.0) {
        MoveItems(scrollOffset_, currentIndex_, needReverse_ ? GetPrevIndex() : GetNextIndex());
    } else {
        // restore autoplay which break by a touch event
        RestoreAutoPlay();
    }
}

void RenderSwiper::HandleTouchMove(const TouchEventInfo& info)
{
    // for indicator
    if (!indicator_ || indicator_->GetIndicatorDisabled() || swiperIndicatorData_.isDigital) {
        return;
    }

    if (info.GetTouches().empty()) {
        return;
    }

    if (touchContentType_ != TouchContentType::TOUCH_INDICATOR) {
        return;
    }

    const auto& locationInfo = info.GetTouches().front();
    Point touchPoint = Point(locationInfo.GetGlobalLocation().GetX(), locationInfo.GetGlobalLocation().GetY());
    GetIndicatorCurrentRect(swiperIndicatorData_);
    if (indicatorRect_.IsInRegion(touchPoint)) {
        if (autoPlay_ && scheduler_->IsActive()) {
            // forbid indicator operation on auto play period.
            return;
        }
        if (!swiperIndicatorData_.isHovered) {
            int64_t endStartTime = clock();
            if (startTimeStamp_ == 0) {
                // move into indicator rage
                startTimeStamp_ = endStartTime;
                return;
            }
            double delayTime = static_cast<double>(endStartTime - startTimeStamp_) / TIME_RATIO;
            if (!swiperIndicatorData_.isPressed && delayTime >= DELAY_TIME_DEFAULT) {
                swiperIndicatorData_.isPressed = true;
                StartZoomInAnimation();
            }
        }
    }
}

void RenderSwiper::HandleClick(const ClickInfo& clickInfo)
{
    if (clickEvent_) {
        clickEvent_();
    }
    // for indicator
    if (!indicator_ || swiperIndicatorData_.isDigital) {
        return;
    }

    if (swiperIndicatorData_.isHovered || swiperIndicatorData_.isPressed) {
        if (currentHoverIndex_ != INDICATOR_INVALID_HOVER_INDEX) {
            StartIndicatorAnimation(currentIndex_, currentHoverIndex_);
            return;
        }
        // refuse click event
        LOGD("drop click event on press and hover status, otherwise exist hover index.");
        return;
    }

    // handle operation not support when indicator disabled.
    if (indicator_->GetIndicatorDisabled()) {
        return;
    }
    Point clickPoint = Point(clickInfo.GetGlobalLocation().GetX(), clickInfo.GetGlobalLocation().GetY());
    GetIndicatorCurrentRect(swiperIndicatorData_);
    if (!indicatorRect_.IsInRegion(clickPoint)) {
        return;
    }
    if (autoPlay_ && scheduler_->IsActive()) {
        // forbid indicator operation on auto play period.
        return;
    }
    if (fingerId_ >= 0 && clickInfo.GetFingerId() != fingerId_) {
        return;
    }

    Offset offset;
    Size size;
    Rect itemRect;
    if (axis_ == Axis::HORIZONTAL) {
        offset = indicatorRect_.GetOffset() + Offset(
            swiperIndicatorData_.indicatorItemData[currentIndex_].position.GetX(), 0);
        size = Size(swiperIndicatorData_.indicatorItemData[currentIndex_].width,
            swiperIndicatorData_.indicatorPaintData.height);
        itemRect = Rect(offset, size);
        if (clickPoint.GetX() < itemRect.GetOffset().GetX()) {
            IndicatorSwipePrev();
        } else if (clickPoint.GetX() > itemRect.Right()) {
            IndicatorSwipeNext();
        }
    } else {
        offset = indicatorRect_.GetOffset() + Offset(0,
            swiperIndicatorData_.indicatorItemData[currentIndex_].position.GetY());
        size = Size(swiperIndicatorData_.indicatorPaintData.width,
            swiperIndicatorData_.indicatorItemData[currentIndex_].height);
        itemRect = Rect(offset, size);
        if (clickPoint.GetY() < itemRect.GetOffset().GetY()) {
            IndicatorSwipePrev();
        } else if (clickPoint.GetY() > itemRect.Bottom()) {
            IndicatorSwipeNext();
        }
    }
}

void RenderSwiper::HandleDragStart(const DragStartInfo& info)
{
    Point dragStartPoint = Point(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    GetIndicatorCurrentRect(swiperIndicatorData_);
    if (indicatorRect_.IsInRegion(dragStartPoint)) {
        return;
    }
    if (fingerId_ >= 0 && info.GetFingerId() != fingerId_) {
        return;
    }
    // for swiper item
    hasDragAction_ = true;
    scrollOffset_ = fmod(scrollOffset_, nextItemOffset_);
    if (onFocus_) {
        auto context = GetContext().Upgrade();
        if (context) {
            context->CancelFocusAnimation();
        }
    }
}

void RenderSwiper::HandleDragUpdate(const DragUpdateInfo& info)
{
    Point touchPoint = Point(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    GetIndicatorCurrentRect(swiperIndicatorData_);
    if (swiperIndicatorData_.isPressed) {
        if (swiperIndicatorData_.isDigital) {
            return;
        }
        if (autoPlay_ && scheduler_->IsActive()) {
            // forbid indicator operation on auto play period.
            return;
        }
        DragIndicator(std::clamp(info.GetMainDelta(), -MAX_VIEW_PORT_WIDTH, MAX_VIEW_PORT_WIDTH));
    } else if (touchContentType_ == TouchContentType::TOUCH_CONTENT) {
        UpdateScrollPosition(info.GetMainDelta());
    }
}

void RenderSwiper::HandleDragEnd(const DragEndInfo& info)
{
    if (swiperIndicatorData_.isPressed) {
        DragIndicatorEnd();
        return;
    }

    if (touchContentType_ != TouchContentType::TOUCH_CONTENT) {
        return;
    }

    if (fingerId_ >= 0 && info.GetFingerId() != fingerId_) {
        return;
    }

    // for swiper item
    scrollOffset_ = fmod(scrollOffset_, nextItemOffset_);
    if (NearZero(scrollOffset_)) {
        // restore autoplay which break by a touch event
        RestoreAutoPlay();
        return;
    }
    if (scrollOffset_ > 0.0) {
        MoveItems(scrollOffset_, currentIndex_, needReverse_ ? GetNextIndex() : GetPrevIndex());
    } else {
        MoveItems(scrollOffset_, currentIndex_, needReverse_ ? GetPrevIndex() : GetNextIndex());
    }
}

void RenderSwiper::MoveItems(double dragOffset, int32_t fromIndex, int32_t toIndex)
{
    if (isIndicatorAnimationStart_) {
        LOGE("item and indicator animation is processing.");
        return;
    }

    if (isAnimationAlreadyAdded_) {
        controller_->RemoveInterpolator(translate_);
        isAnimationAlreadyAdded_ = false;
    }
    isIndicatorAnimationStart_ = true;
    double start = dragOffset;
    double end;

    // Adjust offset more than MIN_SCROLL_OFFSET at least
    double minOffset = 0.0;
    if (axis_ == Axis::VERTICAL) {
        minOffset = MIN_SCROLL_OFFSET * swiperHeight_;
    } else {
        minOffset = MIN_SCROLL_OFFSET * swiperWidth_;
    }
    bool needRestore = false;
    if (!NearZero(dragOffset) && std::abs(dragOffset) < minOffset) {
        LOGI("ScrollOffset less than min scroll offset.");
        targetIndex_ = fromIndex;
        end = 0.0;
        needRestore = true;
    } else {
        targetIndex_ = toIndex;
        // auto play drag offset is zero, move to previous
        end = needReverse_ ? (dragOffset >= 0.0 ? prevItemOffset_ : nextItemOffset_)
                           : (dragOffset > 0.0 ? nextItemOffset_ : prevItemOffset_);
    }
    LOGD("translate animation, start=%{public}f, end=%{public}f", start, end);
    translate_ = AceType::MakeRefPtr<CurveAnimation<double>>(start, end, Curves::LINEAR);
    auto weak = AceType::WeakClaim(this);
    translate_->AddListener(Animation<double>::ValueCallback([weak, fromIndex, toIndex, start, end](double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            if (value != start && value != end && start != end) {
                double moveRate = Curves::EASE_OUT->MoveInternal((value - start) / (end - start));
                value = start + (end - start) * moveRate;
            }
            swiper->UpdateChildPosition(value, fromIndex, toIndex);
            swiper->MoveIndicator(toIndex, value, true);
        }
    }));

    controller_->ClearStopListeners();
    // trigger the event after the animation ends.
    controller_->AddStopListener([weak, fromIndex, toIndex, needRestore]() {
        LOGI("slide animation stop");
        // moving animation end, one drag and item move is complete
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->isIndicatorAnimationStart_ = false;
            if (!needRestore) {
                swiper->outItemIndex_ = fromIndex;
                swiper->currentIndex_ = toIndex;
            }
            swiper->RestoreAutoPlay();
            swiper->FireItemChangedEvent();
            swiper->UpdateItemOpacity(MAX_OPACITY, fromIndex);
            swiper->UpdateItemOpacity(MAX_OPACITY, toIndex);
            swiper->ExecuteMoveCallback(swiper->currentIndex_);
            swiper->MarkNeedLayout();
        }
    });
    controller_->SetDuration(animationDuration_);
    controller_->AddInterpolator(translate_);
    controller_->Play();
    isAnimationAlreadyAdded_ = true;
    MarkNeedRender();
}

void RenderSwiper::FireItemChangedEvent() const
{
    if (changeEvent_) {
        changeEvent_(std::make_shared<SwiperChangeEvent>(currentIndex_));
    }

    for (const auto& [first, second] : changeEndListeners_) {
        if (second) {
            second(currentIndex_);
        }
    }
}

void RenderSwiper::SwipeTo(int32_t index, bool reverse)
{
    if (index >= itemCount_) {
        index = itemCount_ - 1;
    } else if (index < 0) {
        index = 0;
    }
    if (isIndicatorAnimationStart_) {
        RedoSwipeToAnimation(index, reverse);
    } else {
        StopIndicatorSpringAnimation();
        DoSwipeToAnimation(currentIndex_, index, reverse);
    }
}

void RenderSwiper::InitSwipeToAnimation(double start, double end)
{
    auto curStartTranslateKeyframe = AceType::MakeRefPtr<Keyframe<double>>(CUR_START_TRANSLATE_TIME, start);
    auto curEndTranslateKeyframe = AceType::MakeRefPtr<Keyframe<double>>(CUR_END_TRANSLATE_TIME, end);
    curEndTranslateKeyframe->SetCurve(
        animationCurve_ == AnimationCurve::FRICTION ? Curves::FRICTION : Curves::FAST_OUT_SLOW_IN);
    curTranslateAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<double>>();
    curTranslateAnimation_->AddKeyframe(curStartTranslateKeyframe);
    curTranslateAnimation_->AddKeyframe(curEndTranslateKeyframe);

    auto targetStartTranslateKeyframe = AceType::MakeRefPtr<Keyframe<double>>(TARGET_START_TRANSLATE_TIME, -end);
    auto targetEndTranslateKeyframe = AceType::MakeRefPtr<Keyframe<double>>(TARGET_END_TRANSLATE_TIME, start);
    targetEndTranslateKeyframe->SetCurve(
        animationCurve_ == AnimationCurve::FRICTION ? Curves::FRICTION : Curves::FAST_OUT_SLOW_IN);
    targetTranslateAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<double>>();
    targetTranslateAnimation_->AddKeyframe(targetStartTranslateKeyframe);
    targetTranslateAnimation_->AddKeyframe(targetEndTranslateKeyframe);

    if (animationOpacity_) {
        auto curStartOpacityKeyframe =
            AceType::MakeRefPtr<Keyframe<uint8_t>>(CUR_START_OPACITY_TIME, CUR_START_OPACITY_VALUE);
        auto curEndOpacityKeyframe =
            AceType::MakeRefPtr<Keyframe<uint8_t>>(CUR_END_OPACITY_TIME, CUR_END_OPACITY_VALUE);
        curEndOpacityKeyframe->SetCurve(
            animationCurve_ == AnimationCurve::FRICTION ? Curves::FRICTION : Curves::FAST_OUT_SLOW_IN);
        curOpacityAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<uint8_t>>();
        curOpacityAnimation_->AddKeyframe(curStartOpacityKeyframe);
        curOpacityAnimation_->AddKeyframe(curEndOpacityKeyframe);

        auto targetStartOpacityKeyframe =
            AceType::MakeRefPtr<Keyframe<uint8_t>>(TARGET_START_OPACITY_TIME, TARGET_START_OPACITY_VALUE);
        auto targetEndOpacityKeyframe =
            AceType::MakeRefPtr<Keyframe<uint8_t>>(TARGET_END_OPACITY_TIME, TARGET_END_OPACITY_VALUE);
        targetEndOpacityKeyframe->SetCurve(
            animationCurve_ == AnimationCurve::FRICTION ? Curves::FRICTION : Curves::FAST_OUT_SLOW_IN);
        targetOpacityAnimation_ = AceType::MakeRefPtr<KeyframeAnimation<uint8_t>>();
        targetOpacityAnimation_->AddKeyframe(targetStartOpacityKeyframe);
        targetOpacityAnimation_->AddKeyframe(targetEndOpacityKeyframe);
    }
}

void RenderSwiper::AddSwipeToTranslateListener(int32_t fromIndex, int32_t toIndex)
{
    auto weak = AceType::WeakClaim(this);
    curTranslateAnimation_->AddListener([weak, fromIndex](const double& value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateItemPosition(value, fromIndex);
        }
    });

    targetTranslateAnimation_->AddListener([weak, toIndex](const double& value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateItemPosition(value, toIndex);
        }
    });
}

void RenderSwiper::AddSwipeToOpacityListener(int32_t fromIndex, int32_t toIndex)
{
    if (!animationOpacity_) {
        return;
    }
    auto weak = AceType::WeakClaim(this);
    curOpacityAnimation_->AddListener([weak, fromIndex](const uint8_t& opacity) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateItemOpacity(opacity, fromIndex);
        }
    });

    targetOpacityAnimation_->AddListener([weak, toIndex](const uint8_t& opacity) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateItemOpacity(opacity, toIndex);
        }
    });
}

void RenderSwiper::AddSwipeToIndicatorListener(int32_t fromIndex, int32_t toIndex)
{
    indicatorAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(
        CUR_START_TRANSLATE_TIME, CUR_END_TRANSLATE_TIME, Curves::LINEAR);
    indicatorAnimation_->AddListener(
        [weak = AceType::WeakClaim(this), fromIndex, toIndex](const double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateIndicatorOffset(fromIndex, toIndex, value);
        }
    });
    animationDirect_ = (fromIndex - toIndex <= 0) ? INDICATOR_DIRECT_RTL : INDICATOR_DIRECT_LTR;
    targetIndex_ = toIndex;
}

double RenderSwiper::CalculateEndOffset(int32_t fromIndex, int32_t toIndex, bool reverse)
{
    double end = 0.0;
    auto context = GetContext().Upgrade();
    if (fromIndex > toIndex) {
        // default move to back position, if need reverse direction move to front position.
        end = reverse ? prevItemOffset_ / TRANSLATE_RATIO : nextItemOffset_ / TRANSLATE_RATIO;
    } else {
        // default move to front position, if need reverse direction move to back position.
        end = reverse ? nextItemOffset_ / TRANSLATE_RATIO : prevItemOffset_ / TRANSLATE_RATIO;
    }
    if (context && context->IsJsCard()) {
        if (loop_) {
            end = reverse ? nextItemOffset_ : prevItemOffset_;
        } else {
            if (fromIndex > toIndex) {
                end = reverse ? prevItemOffset_ : nextItemOffset_;
            } else {
                end = reverse ? nextItemOffset_ : prevItemOffset_;
            }
        }
    }
    return end;
}

void RenderSwiper::DoSwipeToAnimation(int32_t fromIndex, int32_t toIndex, bool reverse)
{
    if (!swipeToController_ || isIndicatorAnimationStart_ || fromIndex == toIndex) {
        return;
    }
    isIndicatorAnimationStart_ = true;
    double start = 0.0;
    moveStatus_ = true;
    if (onFocus_) {
        auto context = GetContext().Upgrade();
        if (context) {
            context->CancelFocusAnimation();
        }
    }
    double end = CalculateEndOffset(fromIndex, toIndex, reverse);
    swipeToController_->ClearStopListeners();
    if (isSwipeToAnimationAdded_) {
        swipeToController_->ClearInterpolators();
        isSwipeToAnimationAdded_ = false;
    }
    if (!swipeToController_->IsStopped()) {
        swipeToController_->Stop();
    }

    InitSwipeToAnimation(start, end);
    AddSwipeToTranslateListener(fromIndex, toIndex);
    AddSwipeToOpacityListener(fromIndex, toIndex);
    AddSwipeToIndicatorListener(fromIndex, toIndex);

    // trigger the event after the animation ends.
    auto weak = AceType::WeakClaim(this);
    swipeToController_->AddStopListener([weak, fromIndex, toIndex]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->isIndicatorAnimationStart_ = false;
            swiper->outItemIndex_ = fromIndex;
            swiper->currentIndex_ = toIndex;
            swiper->moveStatus_ = false;
            swiper->UpdateIndicatorSpringStatus(SpringStatus::FOCUS_SWITCH);
            swiper->UpdateItemOpacity(MAX_OPACITY, fromIndex);
            swiper->UpdateItemOpacity(MAX_OPACITY, toIndex);
            swiper->RestoreAutoPlay();
            swiper->FireItemChangedEvent();
            swiper->MarkNeedLayout();
        }
    });
    swipeToController_->SetDuration(SWIPE_TO_ANIMATION_TIME);
    swipeToController_->AddInterpolator(curTranslateAnimation_);
    swipeToController_->AddInterpolator(targetTranslateAnimation_);
    swipeToController_->AddInterpolator(curOpacityAnimation_);
    swipeToController_->AddInterpolator(targetOpacityAnimation_);
    swipeToController_->AddInterpolator(indicatorAnimation_);
    swipeToController_->SetFillMode(FillMode::FORWARDS);
    swipeToController_->Play();
    isSwipeToAnimationAdded_ = true;

    MarkNeedLayout();
}

void RenderSwiper::RedoSwipeToAnimation(int32_t toIndex, bool reverse)
{
    if (toIndex == targetIndex_) {
        // continue move animation
        return;
    }
    // stop animation before update item position, otherwise the
    // animation callback will change the item position
    FinishAllSwipeAnimation();
    DoSwipeToAnimation(currentIndex_, toIndex, false);
}

void RenderSwiper::StopSwipeToAnimation()
{
    if (swipeToController_ && !swipeToController_->IsStopped()) {
        swipeToController_->ClearStopListeners();
        swipeToController_->Stop();
        UpdateItemOpacity(MAX_OPACITY, currentIndex_);
        UpdateItemOpacity(MAX_OPACITY, targetIndex_);
        isIndicatorAnimationStart_ = false;
    }
}

void RenderSwiper::UpdateItemOpacity(uint8_t opacity, int32_t index)
{
    if (!animationOpacity_) {
        return;
    }
    int32_t childrenCount = static_cast<int32_t>(childrenArray_.size());
    if (index < 0 || index >= childrenCount) {
        LOGE("index is error, index = %{public}d", index);
        return;
    }
    auto child = childrenArray_[index];
    auto display = AceType::DynamicCast<RenderDisplay>(child);
    if (!display) {
        return;
    }
    display->UpdateOpacity(opacity);
}

void RenderSwiper::UpdateItemPosition(double offset, int32_t index)
{
    int32_t childrenCount = static_cast<int32_t>(childrenArray_.size());
    if (index < 0 || index >= childrenCount) {
        LOGE("index is error, index = %{public}d", index);
        return;
    }
    const auto& childItem = childrenArray_[index];
    childItem->SetPosition(GetMainAxisOffset(offset));
    MarkNeedRender();
}

int32_t RenderSwiper::GetPrevIndex() const
{
    int32_t index = currentIndex_ - 1;
    if (index < 0) {
        index = loop_ ? itemCount_ - 1 : 0;
    }
    return index;
}

int32_t RenderSwiper::GetPrevIndexOnAnimation() const
{
    int32_t index = targetIndex_ - 1;
    if (index < 0) {
        index = loop_ ? itemCount_ - 1 : 0;
    }
    return index;
}

int32_t RenderSwiper::GetNextIndex() const
{
    int32_t index = currentIndex_ + 1;
    if (index >= itemCount_) {
        index = loop_ ? 0 : itemCount_ - 1;
    }
    return index;
}

int32_t RenderSwiper::GetNextIndexOnAnimation() const
{
    int32_t index = targetIndex_ + 1;
    if (index >= itemCount_) {
        index = loop_ ? 0 : itemCount_ - 1;
    }
    return index;
}

void RenderSwiper::ShowPrevious()
{
    if (isIndicatorAnimationStart_) {
        int32_t index = GetPrevIndexOnAnimation();
        RedoSwipeToAnimation(index, false);
    } else {
        int32_t index = GetPrevIndex();
        StopIndicatorSpringAnimation();
        DoSwipeToAnimation(currentIndex_, index, false);
    }
}

void RenderSwiper::ShowNext()
{
    if (isIndicatorAnimationStart_) {
        int32_t index = GetNextIndexOnAnimation();
        RedoSwipeToAnimation(index, false);
    } else {
        int32_t index = GetNextIndex();
        StopIndicatorSpringAnimation();
        DoSwipeToAnimation(currentIndex_, index, false);
    }
}

void RenderSwiper::OnFocus()
{
    if (autoPlay_) {
        LOGD("stop autoplay cause by on focus");
        scheduler_->Stop();
        StopSwipeAnimation();
        StopSwipeToAnimation();
        StopIndicatorAnimation();
        StopIndicatorSpringAnimation();
        ResetIndicatorPosition();
    }
}

void RenderSwiper::OnBlur()
{
    RestoreAutoPlay();
}

void RenderSwiper::RegisterChangeEndListener(int32_t listenerId, const SwiperChangeEndListener& listener)
{
    if (listener) {
        changeEndListeners_[listenerId] = listener;
    }
}

void RenderSwiper::UnRegisterChangeEndListener(int32_t listenerId)
{
    changeEndListeners_.erase(listenerId);
}

void RenderSwiper::UpdateScrollPosition(double dragDelta)
{
    auto limitDelta = std::clamp(dragDelta, -MAX_VIEW_PORT_WIDTH, MAX_VIEW_PORT_WIDTH);
    double newDragOffset = scrollOffset_ + limitDelta;
    int32_t toIndex = 0;
    if (newDragOffset > 0) {
        toIndex = needReverse_ ? GetNextIndex() : GetPrevIndex();
    } else {
        toIndex = needReverse_ ? GetPrevIndex() : GetNextIndex();
    }
    if (toIndex < 0 || toIndex >= itemCount_) {
        LOGD("toIndex is out %{public}d", toIndex);
        return;
    }

    if (std::fabs(newDragOffset) >= std::fabs(nextItemOffset_)) {
        scrollOffset_ = (newDragOffset >= nextItemOffset_) ? newDragOffset - nextItemOffset_
                                                           : newDragOffset - prevItemOffset_;
        outItemIndex_ = currentIndex_;
        currentIndex_ = toIndex;
        FireItemChangedEvent();
        UpdateItemOpacity(MAX_OPACITY, outItemIndex_);
        UpdateItemOpacity(MAX_OPACITY, currentIndex_);
        ExecuteMoveCallback(currentIndex_);
        ResetIndicatorPosition();
        MarkNeedLayout();
        // drag length is greater than swiper's width, don't need to move position
        LOGD("scroll to next page index[%{public}d] from index[%{public}d], scroll offset:%{public}lf",
            currentIndex_, outItemIndex_, scrollOffset_);
        return;
    }

    bool dragReverse = (newDragOffset * scrollOffset_) < 0.0;
    if (dragReverse) {
        int32_t lastToIndex = 0;
        double toItemPosValue = 0.0;
        if (needReverse_) {
            lastToIndex = scrollOffset_ > 0 ? GetNextIndex() : GetPrevIndex();
            toItemPosValue = scrollOffset_ > 0 ? nextItemOffset_ : prevItemOffset_;
        } else {
            lastToIndex = scrollOffset_ > 0 ? GetPrevIndex() : GetNextIndex();
            toItemPosValue = scrollOffset_ > 0 ? prevItemOffset_ : nextItemOffset_;
        }
        childrenArray_[lastToIndex]->SetPosition(GetMainAxisOffset(toItemPosValue));
    }

    UpdateChildPosition(newDragOffset, currentIndex_, toIndex);
    MoveIndicator(toIndex, newDragOffset);
}

void RenderSwiper::UpdateChildPosition(double offset, int32_t fromIndex, int32_t toIndex)
{
    scrollOffset_ = offset;
    int32_t childrenCount = static_cast<int32_t>(childrenArray_.size());
    if (fromIndex < 0 || fromIndex >= childrenCount || toIndex < 0 || toIndex >= childrenCount ||
        fromIndex == toIndex) {
        LOGE("index is error, toIndex = %{public}d, fromIndex = %{public}d, childrenCount = %{public}d", toIndex,
            fromIndex, childrenCount);
        return;
    }
    const auto& fromItem = childrenArray_[fromIndex];
    fromItem->SetPosition(GetMainAxisOffset(offset));
    const auto& toItem = childrenArray_[toIndex];
    double toItemPosValue = 0.0;
    if (needReverse_) {
        toItemPosValue = offset + (offset > 0 ? nextItemOffset_ : prevItemOffset_);
    } else {
        toItemPosValue = offset + (offset > 0 ? prevItemOffset_ : nextItemOffset_);
    }
    Offset toItemPos = GetMainAxisOffset(toItemPosValue);
    toItem->SetPosition(toItemPos);
    MarkNeedRender();
}

void RenderSwiper::Tick(uint64_t duration)
{
    elapsedTime_ += duration;
    if (elapsedTime_ >= autoPlayInterval_) {
        LOGD("Tick %{public}" PRIu64 " %{public}" PRIu64 " timeout", duration, elapsedTime_);
        if (currentIndex_ >= itemCount_ - 1 && !loop_) {
            LOGD("already last one, stop auto play because not loop");
            scheduler_->Stop();
        } else {
            if (swiperIndicatorData_.isPressed) {
                // end drag operations on auto play.
                DragIndicatorEnd();
            }
            if (swiperIndicatorData_.isHovered) {
                ResetHoverZoomDot();
                StartZoomOutAnimation(true);
            }
            int nextIndex = GetNextIndex();
            StartIndicatorAnimation(currentIndex_, nextIndex, currentIndex_ > nextIndex);
        }
        elapsedTime_ = 0;
    }
}

void RenderSwiper::OnHiddenChanged(bool hidden)
{
    if (hidden) {
        if (autoPlay_) {
            LOGD("stop autoplay cause by hidden");
            scheduler_->Stop();
            StopSwipeAnimation();
        }
    } else {
        RestoreAutoPlay();
    }
}

bool RenderSwiper::OnRotation(const RotationEvent& event)
{
    // Clockwise rotation switches to the next one, counterclockwise rotation switches to the previous one.
    rotationStepValue_ += event.value * SWIPER_ROTATION_SENSITIVITY_NORMAL * (-1.0);
    if (GreatOrEqual(rotationStepValue_, THRESHOLD)) {
        if (rotationEvent_) {
            std::string param =
                std::string(R"("rotation",{"value":)").append(std::to_string(rotationStepValue_).append("},null"));
            rotationEvent_(param);
        }
        ShowNext();
        rotationStepValue_ = 0.0;
    } else if (LessOrEqual(rotationStepValue_, -THRESHOLD)) {
        if (rotationEvent_) {
            std::string param =
                std::string(R"("rotation",{"value":)").append(std::to_string(rotationStepValue_).append("},null"));
            rotationEvent_(param);
        }
        ShowPrevious();
        rotationStepValue_ = 0.0;
    }
    return true;
}

void RenderSwiper::OnStatusChanged(RenderStatus renderStatus)
{
    if (renderStatus == RenderStatus::FOCUS) {
        onFocus_ = true;
    } else if (renderStatus == RenderStatus::BLUR) {
        onFocus_ = false;
    }
}

double RenderSwiper::GetValidEdgeLength(double swiperLength, double indicatorLength, const Dimension& edge) const
{
    double edgeLength = edge.Unit() == DimensionUnit::PERCENT ? swiperLength * edge.Value() : NormalizeToPx(edge);
    if (!NearZero(edgeLength) && edgeLength > swiperLength - indicatorLength) {
        edgeLength = swiperLength - indicatorLength;
    }
    if (edgeLength < 0.0) {
        edgeLength = 0.0;
    }
    return edgeLength;
}

void RenderSwiper::GetIndicatorCurrentRect(SwiperIndicatorData& indicatorData)
{
    if (!indicator_) {
        indicatorRect_ = Rect();
        return;
    }
    Offset offset = indicatorPosition_ + GetGlobalOffset();
    Size size = Size(swiperIndicatorData_.indicatorPaintData.width, swiperIndicatorData_.indicatorPaintData.height);
    indicatorRect_ = Rect(offset, size);
}

double RenderSwiper::GetIndicatorWidth(SwiperIndicatorData& indicatorData)
{
    double indicatorWidth = 0.0;
    double lastItemEdge = 0.0;

    if (currentHoverIndex_ == itemCount_ - 1) {
        double deltaPadding = 0.0;
        if (axis_ == Axis::HORIZONTAL) {
            lastItemEdge = indicatorData.indicatorItemData[itemCount_ - 1].center.GetX() +
                           NormalizeToPx(indicator_->GetPressSize()) / 2;
        } else {
            lastItemEdge = indicatorData.indicatorItemData[itemCount_ - 1].center.GetY() +
                           NormalizeToPx(indicator_->GetPressSize()) / 2;
        }
        if (currentIndex_ == itemCount_ - 1) {
            deltaPadding = NormalizeToPx(indicator_->GetPressSize()) / 2;
        }
        indicatorWidth = lastItemEdge + indicatorData.startEndPadding + deltaPadding;
    } else {
        if (axis_ == Axis::HORIZONTAL) {
            lastItemEdge = indicatorData.indicatorItemData[itemCount_ - 1].center.GetX() +
                           indicatorData.indicatorItemData[itemCount_ - 1].width / 2;
        } else {
            lastItemEdge = indicatorData.indicatorItemData[itemCount_ - 1].center.GetY() +
                           indicatorData.indicatorItemData[itemCount_ - 1].height / 2;
        }
        indicatorWidth = lastItemEdge + indicatorData.startEndPadding;
    }
    return indicatorWidth;
}

void RenderSwiper::LayoutIndicator(SwiperIndicatorData& indicatorData)
{
    if (!indicator_) {
        LOGW("swiper has not default indicator");
        return;
    }

    // calc real hot zone size by zoom and stretch
    if (NearZero(hotZoneMaxSize_) || NearZero(hotZoneMinSize_)) {
        hotZoneMaxSize_ = NormalizeToPx((indicator_->GetHotZoneSize()));
        hotZoneMinSize_ = hotZoneMaxSize_ / ZOOM_HOTZONE_MAX_RATE;
    }
    hotZoneRealSize_ = hotZoneMinSize_ + (hotZoneMaxSize_ - hotZoneMinSize_) * zoomValue_;
    hotZoneRealSize_ *= heightStretchRate_;

    // update indicator item paint data;
    indicatorData.isDigital = digitalIndicator_;
    if (!digitalIndicator_) {
        UpdateIndicatorItem(indicatorData);
    }

    // update Indicator paint data
    if (digitalIndicator_) {
        LayoutDigitalIndicator(indicatorData);
        Size digitalIndicatorSize = indicatorData.textBoxRender->GetLayoutSize();
        indicatorData.indicatorPaintData.width = digitalIndicatorSize.Width();
        indicatorData.indicatorPaintData.height = digitalIndicatorSize.Height();
    } else {
        if (axis_ == Axis::HORIZONTAL) {
            indicatorData.indicatorPaintData.width = GetIndicatorWidth(indicatorData);
            indicatorData.indicatorPaintData.height = hotZoneRealSize_; // influenced on zoom and stretch
        } else {
            indicatorData.indicatorPaintData.width = hotZoneRealSize_; // influenced on zoom and stretch
            indicatorData.indicatorPaintData.height = GetIndicatorWidth(indicatorData);
        }
    }
    indicatorData.indicatorPaintData.radius = hotZoneRealSize_ / 2; // influenced on zoom and stretch
    if (!digitalIndicator_ && (indicatorData.isHovered || indicatorData.isPressed)) {
        indicatorData.indicatorPaintData.color = indicator_->GetHotZoneColor();
    } else {
        indicatorData.indicatorPaintData.color = Color::WHITE;
    }

    // update position
    UpdateIndicatorPosition(indicatorData);
}

void RenderSwiper::InitDigitalIndicator(SwiperIndicatorData& indicatorData)
{
    auto textBoxComponent = AceType::MakeRefPtr<BoxComponent>();
    double padding = NormalizeToPx(INDICATOR_DIGITAL_PADDING);
    Edge margin = (axis_ == Axis::HORIZONTAL) ?
                  Edge(padding, 0, padding, 0, DimensionUnit::PX) :
                  Edge(0, padding, 0, padding, DimensionUnit::PX);
    textBoxComponent->SetPadding(margin);
    indicatorData.textBoxRender = AceType::DynamicCast<RenderBox>(textBoxComponent->CreateRenderNode());
    indicatorData.textBoxRender->Attach(GetContext());

    // add flex
    FlexDirection direction = axis_ == Axis::HORIZONTAL ? FlexDirection::ROW : FlexDirection::COLUMN;
    indicatorData.flexComponent = AceType::MakeRefPtr<FlexComponent>(direction,
        FlexAlign::FLEX_END, FlexAlign::CENTER, std::list<RefPtr<Component>>());
    indicatorData.flexComponent->SetMainAxisSize(MainAxisSize::MIN);
    indicatorData.flexRender = AceType::DynamicCast<RenderFlex>(indicatorData.flexComponent->CreateRenderNode());
    indicatorData.textBoxRender->AddChild(indicatorData.flexRender);
    indicatorData.flexRender->Attach(GetContext());
    indicatorData.flexRender->Update(indicatorData.flexComponent);

    // add text
    indicatorData.textComponentPrev = AceType::MakeRefPtr<TextComponent>("");
    indicatorData.textRenderPrev = AceType::DynamicCast<RenderText>(
        indicatorData.textComponentPrev->CreateRenderNode());
    indicatorData.flexRender->AddChild(indicatorData.textRenderPrev);
    indicatorData.textRenderPrev->Attach(GetContext());
    indicatorData.textRenderPrev->Update(indicatorData.textComponentPrev);

    indicatorData.textComponentNext = AceType::MakeRefPtr<TextComponent>("");
    indicatorData.textRenderNext = AceType::DynamicCast<RenderText>(
        indicatorData.textComponentNext->CreateRenderNode());
    indicatorData.flexRender->AddChild(indicatorData.textRenderNext);
    indicatorData.textRenderNext->Attach(GetContext());
    indicatorData.textRenderNext->Update(indicatorData.textComponentNext);

    indicatorData.textBoxRender->Update(textBoxComponent);
}

void RenderSwiper::LayoutDigitalIndicator(SwiperIndicatorData& indicatorData)
{
    InitDigitalIndicator(indicatorData);

    auto textStyle = indicator_->GetDigitalIndicatorTextStyle();
    Color normalTextColor = textStyle.GetTextColor();
    // update text prev
    std::string indicatorTextPrev = std::to_string(currentIndex_ + 1);
    if (indicatorIsFocus_) {
        textStyle.SetTextColor(indicator_->GetIndicatorTextFocusColor());
    } else {
        textStyle.SetTextColor(normalTextColor);
    }
    indicatorData.textComponentPrev->SetTextStyle(textStyle);
    indicatorData.textComponentPrev->SetData(indicatorTextPrev);
    indicatorData.textRenderPrev->Update(indicatorData.textComponentPrev);

    // update text next
    std::string indicatorTextNext = (axis_ == Axis::HORIZONTAL) ? std::string("/").append(std::to_string(itemCount_))
        : std::string("/\n").append(std::to_string(itemCount_));
    textStyle.SetTextColor(normalTextColor);
    indicatorData.textComponentNext->SetTextStyle(textStyle);
    indicatorData.textComponentNext->SetData(indicatorTextNext);
    indicatorData.textRenderNext->Update(indicatorData.textComponentNext);

    // upadate text box
    auto decoration = AceType::MakeRefPtr<Decoration>();
    decoration->SetBackgroundColor(Color::TRANSPARENT);
    Border border;
    border.SetBorderRadius(Radius(indicator_->GetHotZoneSize() / 2.0));
    decoration->SetBorder(border);
    indicatorData.textBoxRender->SetBackDecoration(decoration);
    if (axis_ == Axis::HORIZONTAL) {
        indicatorData.textBoxRender->SetHeight(NormalizeToPx(indicator_->GetHotZoneSize()));
    } else {
        indicatorData.textBoxRender->SetWidth(NormalizeToPx(indicator_->GetHotZoneSize()));
    }

    LayoutParam innerLayout;
    innerLayout.SetMaxSize(Size(swiperWidth_, swiperHeight_));
    indicatorData.textBoxRender->Layout(innerLayout);
}

void RenderSwiper::UpdateIndicatorPosition(SwiperIndicatorData& indicatorData)
{
    Offset position;
    double indicatorWidth = indicatorData.indicatorPaintData.width;
    double indicatorHeight = indicatorData.indicatorPaintData.height;
    double stableOffset = NormalizeToPx(INDICATOR_PADDING_TOP_DEFAULT) + (hotZoneMaxSize_ + hotZoneRealSize_) * 0.5;

    if (indicator_->GetLeft().Value() != SwiperIndicator::DEFAULT_POSITION) {
        int32_t left = GetValidEdgeLength(swiperWidth_, indicatorWidth, indicator_->GetLeft());
        position.SetX(left);
    } else if (indicator_->GetRight().Value() != SwiperIndicator::DEFAULT_POSITION) {
        int32_t right = GetValidEdgeLength(swiperWidth_, indicatorWidth, indicator_->GetRight());
        position.SetX(swiperWidth_ - indicatorWidth - right);
    } else {
        if (axis_ == Axis::HORIZONTAL) {
            position.SetX((swiperWidth_ - indicatorWidth) / 2.0);
        } else {
            // horizontal line of indicator zone is stable.
            double currentX = swiperWidth_ - stableOffset;
            position.SetX(currentX);
        }
    }

    if (indicator_->GetTop().Value() != SwiperIndicator::DEFAULT_POSITION) {
        int32_t top = GetValidEdgeLength(swiperHeight_, indicatorHeight, indicator_->GetTop());
        position.SetY(top);
    } else if (indicator_->GetBottom().Value() != SwiperIndicator::DEFAULT_POSITION) {
        int32_t bottom = GetValidEdgeLength(swiperHeight_, indicatorHeight, indicator_->GetBottom());
        position.SetY(swiperHeight_ - indicatorHeight - bottom);
    } else {
        if (axis_ == Axis::HORIZONTAL) {
            // horizontal line of indicator zone is stable.
            double currentY = swiperHeight_ - stableOffset;
            position.SetY(currentY);
        } else {
            position.SetY((swiperHeight_ - indicatorHeight) / 2.0);
        }
    }

    // update position on stretch or restract indicator zone
    UpdatePositionOnStretch(position, indicatorData);

    // update  position
    indicatorPosition_ = position;
    indicatorData.indicatorPaintData.position = position;
    indicatorData.indicatorPaintData.center = position + Offset(indicatorData.indicatorPaintData.width / 2,
        indicatorData.indicatorPaintData.height / 2);
}

void RenderSwiper::UpdateIndicatorItem(SwiperIndicatorData& indicatorData)
{
    // horizontal line of indicator zone is stable
    double hotZoneCenterPadding = hotZoneRealSize_ / 2.0;
    if (indicatorData.isHovered || indicatorData.isPressed) {
        indicatorData.startEndPadding = NormalizeToPx(indicator_->GetStartEndPadding() +
            (indicator_->GetPressPadding() - indicator_->GetStartEndPadding()) * zoomValue_);
    } else {
        indicatorData.startEndPadding = NormalizeToPx(indicator_->GetStartEndPadding());
    }
    Offset startCenterOffset = axis_ == Axis::HORIZONTAL ? Offset(indicatorData.startEndPadding, hotZoneCenterPadding) :
        Offset(hotZoneCenterPadding, indicatorData.startEndPadding);
    Offset centerOffset = startCenterOffset;

    double targetIndex = currentIndex_;
    double hoverIndex = currentHoverIndex_;
    if (needReverse_) {
        targetIndex = itemCount_ - currentIndex_ - 1;
        hoverIndex = itemCount_ - currentHoverIndex_ - 1;
    }

    double itemRadius = 0.0;
    for (int32_t i = 0; i < itemCount_; i++) {
        bool isZoomInBackground = indicatorData.isHovered || indicatorData.isPressed;
        if (isZoomInBackground) {
            // indicator radius and point padding is dynamic changed on zoom and stretch
            itemRadius = NormalizeToPx(
                indicator_->GetSize() + (indicator_->GetPressSize() - indicator_->GetSize()) * zoomValue_) / 2.0;
            indicatorData.pointPadding = NormalizeToPx(indicator_->GetIndicatorPointPadding() +
                (indicator_->GetPressPointPadding() - indicator_->GetIndicatorPointPadding()) *
                zoomValue_) * widthStretchRate_;
        } else {
            itemRadius = NormalizeToPx(indicator_->GetSize()) / 2.0;
            indicatorData.pointPadding = NormalizeToPx(indicator_->GetIndicatorPointPadding());
        }

        double itemStartEndPadding = 0.0;
        if (i == targetIndex) {
            itemStartEndPadding = itemRadius * 2;
            indicatorData.indicatorItemData[i].color = indicator_->GetSelectedColor();
        } else {
            itemStartEndPadding = itemRadius;
            indicatorData.indicatorItemData[i].color = indicator_->GetColor();
        }
        Offset paddingStartOffset;
        Offset paddingEndOffset;
        if (axis_ == Axis::HORIZONTAL) {
            paddingStartOffset = Offset(itemStartEndPadding, 0);
            paddingEndOffset = Offset(itemStartEndPadding + indicatorData.pointPadding, 0);
        } else {
            paddingStartOffset = Offset(0, itemStartEndPadding);
            paddingEndOffset = Offset(0, itemStartEndPadding + indicatorData.pointPadding);
        }

        // update mouse hover radius
        if (isZoomInBackground && i == hoverIndex) {
            // point radius is dynamic changed on mouse hover
            itemRadius = NormalizeToPx(indicator_->GetPressSize() +
                                       (indicator_->GetHoverSize() - indicator_->GetPressSize()) * zoomDotValue_) / 2.0;
        }
        if (axis_ == Axis::HORIZONTAL) {
            indicatorData.indicatorItemData[i].height = itemRadius * 2;
            indicatorData.indicatorItemData[i].width = (i == targetIndex ? itemRadius * 4 : itemRadius * 2);
        } else {
            indicatorData.indicatorItemData[i].width = itemRadius * 2;
            indicatorData.indicatorItemData[i].height = (i == targetIndex ? itemRadius * 4 : itemRadius * 2);
        }
        indicatorData.indicatorItemData[i].radius = itemRadius;

        centerOffset += paddingStartOffset;
        indicatorData.indicatorItemData[i].center = centerOffset;
        indicatorData.indicatorItemData[i].position = centerOffset -
            Offset(indicatorData.indicatorItemData[i].width / 2, indicatorData.indicatorItemData[i].height / 2);
        centerOffset += paddingEndOffset;
    }
}

void RenderSwiper::UpdatePositionOnStretch(Offset& position, const SwiperIndicatorData& indicatorData)
{
    double indicatorWidth = indicatorData.indicatorPaintData.width;
    double indicatorHeight = indicatorData.indicatorPaintData.height;
    if (widthStretchRate_ > DRAG_STRETCH_BASE_WIDTH) {
        if (zoomValue_ == ZOOM_MAX) {
            // stretch indicator and update start position
            if (axis_ == Axis::HORIZONTAL) {
                if (currentIndex_ == itemCount_ - 1) {
                    position.SetX(indicatorZoomMaxPositionLT_.GetX());
                } else if (currentIndex_ == 0) {
                    position.SetX(indicatorZoomMaxPositionRB_.GetX() - indicatorData.indicatorPaintData.width);
                }
            } else {
                if (currentIndex_ == itemCount_ - 1) {
                    position.SetY(indicatorZoomMaxPositionLT_.GetY());
                } else if (currentIndex_ == 0) {
                    position.SetY(indicatorZoomMaxPositionRB_.GetY() - indicatorData.indicatorPaintData.height);
                }
            }
        } else if (zoomValue_ > ZOOM_MIN) {
            // restract indicator and update start position
            if (axis_ == Axis::HORIZONTAL) {
                if (currentIndex_ == itemCount_ - 1) {
                    position.SetX(indicatorZoomMinPositionLT_.GetX() -
                        (indicatorZoomMinPositionLT_.GetX() - indicatorZoomMaxPositionLT_.GetX()) * zoomValue_);
                } else if (currentIndex_ == 0) {
                    position.SetX(indicatorZoomMinPositionRB_.GetX() - indicatorWidth +
                        (indicatorZoomMaxPositionRB_.GetX() - indicatorZoomMinPositionRB_.GetX()) * zoomValue_);
                }
            } else {
                if (currentIndex_ == itemCount_ - 1) {
                    position.SetY(indicatorZoomMinPositionLT_.GetY() -
                        (indicatorZoomMinPositionLT_.GetY() - indicatorZoomMaxPositionLT_.GetY()) * zoomValue_);
                } else if (currentIndex_ == 0) {
                    position.SetY(indicatorZoomMinPositionRB_.GetY() - indicatorHeight +
                        (indicatorZoomMaxPositionRB_.GetY() - indicatorZoomMinPositionRB_.GetY()) * zoomValue_);
                }
            }
        }
    }
}

void RenderSwiper::IndicatorSwipePrev()
{
    auto toIndex = GetPrevIndex();
    StartIndicatorAnimation(currentIndex_, toIndex, currentIndex_ == 0);
}

void RenderSwiper::IndicatorSwipeNext()
{
    auto toIndex = GetNextIndex();
    StartIndicatorAnimation(currentIndex_, toIndex, currentIndex_ == itemCount_ - 1);
}

bool RenderSwiper::MouseHoverTest(const Point& parentLocalPoint)
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }
    const auto localPoint = parentLocalPoint - GetPosition();
    const auto& children = GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        child->MouseHoverTest(localPoint);
    }

    bool isInRegion = GetTouchRect().IsInRegion(parentLocalPoint);
    if (isInRegion) {
        context->AddToHoverList(AceType::WeakClaim(this).Upgrade());
    }

    // swiper indicator mouse hover
    if (!indicator_) {
        return isInRegion;
    }
    // indicator zone zoom animation should wait for indicator moving animation finished
    if (isIndicatorAnimationStart_) {
        return isInRegion;
    }

    // get absolute position
    Point hoverPoint = parentLocalPoint + GetGlobalOffset();
    GetIndicatorCurrentRect(swiperIndicatorData_);
    if (indicatorRect_.IsInRegion(hoverPoint)) {
        if (autoPlay_ && scheduler_->IsActive()) {
            // forbid indicator operation on auto play period.
            return isInRegion;
        }
        if ((!swiperIndicatorData_.isHovered && !swiperIndicatorData_.isPressed) || !IsZoomOutAnimationStopped()) {
            // hover animation
            swiperIndicatorData_.isHovered = true;
            StartZoomInAnimation(true);
            return isInRegion;
        }
        // point zoom after indicator zone zoom.
        if (!IsZoomAnimationStopped()) {
            return isInRegion;
        }
        for (int32_t i = 0; i < itemCount_; i++) {
            Offset offset = swiperIndicatorData_.indicatorItemData[i].position + indicatorRect_.GetOffset();
            Size size = Size(swiperIndicatorData_.indicatorItemData[i].width,
                swiperIndicatorData_.indicatorItemData[i].height);
            Rect itemRect = Rect(offset, size);
            if (itemRect.IsInRegion(hoverPoint)) {
                if (currentHoverIndex_ != i) {
                    StartZoomInDotAnimation(i);
                }
                return isInRegion;
            }
        }
        if (currentHoverIndex_ != INDICATOR_INVALID_HOVER_INDEX && IsZoomOutDotAnimationStopped()) {
            StartZoomOutDotAnimation();
        }
    } else {
        if (swiperIndicatorData_.isHovered) {
            ResetHoverZoomDot();
            StartZoomOutAnimation(true);
        }
    }
    return isInRegion;
}

void RenderSwiper::IndicatorShowFocus(bool isFocus)
{
    if (!indicator_) {
        return;
    }
    indicatorIsFocus_ = isFocus;
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    Offset offset = swiperIndicatorData_.indicatorPaintData.position;
    Size size = Size(swiperIndicatorData_.indicatorPaintData.width, swiperIndicatorData_.indicatorPaintData.height);
    Offset globalOffset = swiperIndicatorData_.indicatorPaintData.position + GetGlobalOffset();
    double radius = swiperIndicatorData_.indicatorPaintData.radius;
    if (isFocus) {
        offset += Offset(NormalizeToPx(INDICATOR_FOCUS_DEL_OFFSET), NormalizeToPx(INDICATOR_FOCUS_DEL_OFFSET));
        size -= Size(NormalizeToPx(INDICATOR_FOCUS_DEL_SIZE), NormalizeToPx(INDICATOR_FOCUS_DEL_SIZE));
        globalOffset += Offset(NormalizeToPx(INDICATOR_FOCUS_DEL_OFFSET), NormalizeToPx(INDICATOR_FOCUS_DEL_OFFSET));
        Radius focusRadius = Radius(radius) - Radius(NormalizeToPx(INDICATOR_FOCUS_RADIUS_DEL_SIZE));
        context->ShowFocusAnimation(RRect::MakeRRect(Rect(offset, size), focusRadius), Color(INDICATOR_FOCUS_COLOR),
            globalOffset);
    } else {
        context->CancelFocusAnimation();
    }
    MarkNeedLayout();
}

void RenderSwiper::UpdateIndicatorFocus(bool isFocus, bool reverse)
{
    if (reverse) {
        IndicatorSwipePrev();
    } else {
        IndicatorSwipeNext();
    }
    IndicatorShowFocus(isFocus);
}

void RenderSwiper::VibrateIndicator()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGW("GetVibrator fail, context is null");
        return;
    }

    if (!vibrator_) {
        vibrator_ = VibratorProxy::GetInstance().GetVibrator(context->GetTaskExecutor());
    }
    if (vibrator_) {
        vibrator_->Vibrate(VIBRATE_DURATION);
    } else {
        LOGW("GetVibrator fail");
    }
}

void RenderSwiper::UpdateIndicatorSpringStatus(SpringStatus status)
{
    if (indicatorSpringStatus_ == SpringStatus::SPRING_STOP &&
        status == SpringStatus::FOCUS_SWITCH) {
        return;
    }
    LOGD("UpdateIndicatorSpringStatus from[%{public}d] to[%{public}d]", indicatorSpringStatus_, status);
    indicatorSpringStatus_ = status;
}

SpringStatus RenderSwiper::GetIndicatorSpringStatus() const
{
    return indicatorSpringStatus_;
}

void RenderSwiper::ResetIndicatorSpringStatus()
{
    if (GetIndicatorSpringStatus() == SpringStatus::FOCUS_SWITCH) {
        UpdateIndicatorTailPosistion(DRAG_OFFSET_MIN, DRAG_OFFSET_MIN);
    }
    UpdateIndicatorSpringStatus(SpringStatus::SPRING_STOP);
}

void RenderSwiper::ResetIndicatorPosition()
{
    UpdateIndicatorHeadPosistion(DRAG_OFFSET_MIN);
    UpdateIndicatorTailPosistion(DRAG_OFFSET_MIN);
    UpdateIndicatorPointPosistion(DRAG_OFFSET_MIN);
}

void RenderSwiper::ResetHoverZoomDot()
{
    StopZoomDotAnimation();
    UpdateZoomDotValue(ZOOM_DOT_MIN);
    currentHoverIndex_ = INDICATOR_INVALID_HOVER_INDEX;
}

void RenderSwiper::MarkIndicatorPosition(bool isZoomMax)
{
    if (isZoomMax) {
        indicatorZoomMaxPositionLT_ = indicatorPosition_;
        indicatorZoomMaxPositionRB_ = indicatorZoomMaxPositionLT_ +
            Offset(swiperIndicatorData_.indicatorPaintData.width, swiperIndicatorData_.indicatorPaintData.height);
    } else {
        indicatorZoomMinPositionLT_ = indicatorPosition_;
        indicatorZoomMinPositionRB_ = indicatorZoomMinPositionLT_ +
            Offset(swiperIndicatorData_.indicatorPaintData.width, swiperIndicatorData_.indicatorPaintData.height);
    }
}

void RenderSwiper::StartIndicatorSpringAnimation(double start, double end)
{
    LOGD("StartIndicatorSpringAnimation(%{public}lf, %{public}lf)", start, end);
    UpdateIndicatorSpringStatus(SpringStatus::SPRING_START);
    double dampInc = std::fabs(currentIndex_ - targetIndex_) * SPRING_DAMP_INC;
    auto springDescription = AceType::MakeRefPtr<SpringProperty>(SPRING_MASS, SPRING_STIFF, SPRING_DAMP + dampInc);
    if (!indicatorSpringMotion_) {
        indicatorSpringMotion_ = AceType::MakeRefPtr<SpringMotion>(start, end, 0.0, springDescription);
    } else {
        indicatorSpringMotion_->Reset(start, end, 0.0, springDescription);
    }

    indicatorSpringMotion_->ClearListeners();
    indicatorSpringMotion_->AddListener([weak = AceType::WeakClaim(this), end](double position) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            double offset = position;
            double switchOffset = position - end;
            swiper->UpdateIndicatorTailPosistion(offset, switchOffset);
        }
    });

    springController_->PlayMotion(indicatorSpringMotion_);
    springController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->ResetIndicatorSpringStatus();
        }
    });
}

// spring animimation
void RenderSwiper::StopIndicatorSpringAnimation()
{
    if (springController_ && !springController_->IsStopped()) {
        // clear stop listener before stop
        springController_->ClearStopListeners();
        springController_->Stop();
    }
    ResetIndicatorSpringStatus();
    LOGD("StopIndicatorSpringAnimation");
}

void RenderSwiper::CalMaxStretch()
{
    if (focusStretchMaxTime_  == DRAG_OFFSET_MIN) {
        double stretch = DRAG_OFFSET_MIN;
        double maxStretch = DRAG_OFFSET_MIN;
        const double step = DRAG_CALC_STRETCH_STEP;
        for (double i = step; i <= 1.0; i += step) {
            stretch = INDICATOR_FOCUS_HEAD->Move(i) - INDICATOR_FOCUS_TAIL->Move(i);
            if (stretch > maxStretch) {
                maxStretch = stretch;
                focusStretchMaxTime_ = i;
            }
        }
        LOGD("CalMaxStretch(%{public}lf), time(%{public}lf)", maxStretch, focusStretchMaxTime_);
    }
}

void RenderSwiper::MoveIndicator(int32_t toIndex, double offset, bool isAuto)
{
    if (toIndex == currentIndex_) {
        LOGW("MoveIndicator drop it for edge moving.");
        return;
    }

    double dragRange = (axis_ == Axis::HORIZONTAL) ? swiperWidth_ : swiperHeight_;
    if (NearZero(dragRange)) {
        return;
    }
    double dragRate = offset / dragRange;
    animationDirect_ = (currentIndex_ <= toIndex) ? INDICATOR_DIRECT_RTL : INDICATOR_DIRECT_LTR;
    dragRate = std::fabs(dragRate);
    if (dragRate >= DRAG_OFFSET_MAX) {
        // move to end, and index change
        UpdateIndicatorPointPosistion(DRAG_OFFSET_MIN);
        UpdateIndicatorHeadPosistion(DRAG_OFFSET_MIN);
        UpdateIndicatorSpringStatus(SpringStatus::FOCUS_SWITCH);
        return;
    }

    targetIndex_ = toIndex;
    int32_t indicatorMoveNums = std::abs(currentIndex_ - toIndex);
    UpdateIndicatorPointPosistion(INDICATOR_NORMAL_POINT->MoveInternal(dragRate));
    UpdateIndicatorHeadPosistion(INDICATOR_FOCUS_HEAD->MoveInternal(dragRate) * indicatorMoveNums);
    if (!isAuto) {
        // move tails with hand
        UpdateIndicatorTailPosistion(INDICATOR_FOCUS_TAIL->MoveInternal(dragRate) * indicatorMoveNums);
        return;
    }

    // animation
    if (dragRate < focusStretchMaxTime_) {
        UpdateIndicatorTailPosistion(INDICATOR_FOCUS_TAIL->MoveInternal(dragRate) * indicatorMoveNums);
        return;
    }

    // curve sport into spring sport
    if (GetIndicatorSpringStatus() == SpringStatus::SPRING_STOP) {
        LOGD("indicator tail move end, start spring motion.");
        double springStart = INDICATOR_FOCUS_TAIL->MoveInternal(dragRate);
        UpdateIndicatorTailPosistion(springStart * indicatorMoveNums);
        StartIndicatorSpringAnimation(springStart * indicatorMoveNums, DRAG_OFFSET_MAX * indicatorMoveNums);
    }
}

void RenderSwiper::DragIndicator(double offset)
{
    // start drag after zoom in completed.
    if (!IsZoomAnimationStopped()) {
        LOGD("zoom in is not completed");
        return;
    }

    const double longPressDragStart = DRAG_OFFSET_START_DP * scale_;
    const double longPressDragSwitchFocus = DRAG_OFFSET_SWITCH_DP * scale_;
    const double longPressDragMaxDiff = longPressDragSwitchFocus - longPressDragStart;
    if (!isDragStart_) {
        isDragStart_ = true;
        dragBaseOffset_ = offset;
        dragMoveOffset_ = offset;
        return;
    }

    dragMoveOffset_ += offset;
    double diffOffset = dragMoveOffset_ - dragBaseOffset_;
    double fabsOffset = std::fabs(diffOffset);
    if (fabsOffset <= longPressDragStart) {
        // indicator move when drag offset large than 4 vp
        return;
    }

    animationDirect_ = diffOffset >= 0 && !needReverse_ ? INDICATOR_DIRECT_RTL : INDICATOR_DIRECT_LTR;
    if (currentIndex_ + animationDirect_ >= itemCount_ || currentIndex_ + animationDirect_ < 0) {
        // drag end and stretch background
        return DragEdgeStretch(fabsOffset);
    }

    if (fabsOffset >= longPressDragSwitchFocus) {
        // focus switch and vibrate
        VibrateIndicator();
        outItemIndex_ = currentIndex_;
        currentIndex_ += animationDirect_;
        dragBaseOffset_ += longPressDragSwitchFocus * animationDirect_;
        ResetIndicatorPosition();
        MarkNeedLayout();
    } else {
        double dragRate = (fabsOffset - longPressDragStart) / longPressDragMaxDiff;
        UpdateIndicatorHeadPosistion(INDICATOR_FOCUS_HEAD->MoveInternal(dragRate));
        UpdateIndicatorTailPosistion(INDICATOR_FOCUS_TAIL->MoveInternal(dragRate));
        UpdateIndicatorPointPosistion(INDICATOR_NORMAL_POINT->MoveInternal(dragRate));
    }
}

void RenderSwiper::DragIndicatorEnd()
{
    if ((currentIndex_ + animationDirect_ >= itemCount_ || currentIndex_ + animationDirect_ < 0) &&
        std::fabs(dragMoveOffset_ - dragBaseOffset_) > 0) {
        // drag than 80dp, play reset and zoom out animation
        LOGD("drag end and start restrection animation");
        StartDragRetractionAnimation();
        StartZoomOutAnimation();
    } else {
        ResetIndicatorPosition();
        UpdateEdgeStretchRate(DRAG_OFFSET_MIN);
        // only play zoom out animation
        LOGD("drag end and start mask zoom out animation");
        StartZoomOutAnimation();
    }
    dragBaseOffset_ = DRAG_OFFSET_MIN;
    dragMoveOffset_ = DRAG_OFFSET_MIN;
}

void RenderSwiper::DragEdgeStretch(double offset)
{
    const double longPressDragStrechLongest = DRAG_STRETCH_LONGEST_DP * scale_;
    if (offset >= longPressDragStrechLongest) {
        UpdateEdgeStretchRate(DRAG_OFFSET_MAX);
    } else {
        UpdateEdgeStretchRate(offset / longPressDragStrechLongest);
    }
}

void RenderSwiper::StartZoomInAnimation(bool isMouseHover)
{
    StopZoomAnimation();
    if (zoomValue_ == ZOOM_MIN) {
        MarkIndicatorPosition(false);
    }
    LOGD("startZoomInAnimation zoom[%{public}lf,%{public}lf], opacity[%{public}lf,%{public}lf], duration[%{public}d]",
        zoomValue_, ZOOM_MAX, opacityValue_, OPACITY_MAX, ZOOM_IN_DURATION);
    zoomInAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(zoomValue_, ZOOM_MAX, Curves::SHARP);
    zoomInAnimation_->AddListener([weak = AceType::WeakClaim(this)](const double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateZoomValue(value);
            if (value == ZOOM_MAX) {
                // record position zone of indicator zone for strecth when zoom in reach maximum value.
                swiper->MarkIndicatorPosition();
            }
        }
    });

    opacityInAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(opacityValue_, OPACITY_MAX, Curves::SHARP);
    opacityInAnimation_->AddListener([weak = AceType::WeakClaim(this)](const double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateMaskOpacity(value);
        }
    });

    zoomInController_->ClearInterpolators();
    zoomInController_->AddInterpolator(zoomInAnimation_);
    zoomInController_->AddInterpolator(opacityInAnimation_);
    zoomInController_->SetDuration(ZOOM_IN_DURATION);
    zoomInController_->Play();
}

void RenderSwiper::StartZoomOutAnimation(bool isMouseHover)
{
    StopZoomAnimation();
    int duartion = isMouseHover ? ZOOM_OUT_HOVER_DURATION : ZOOM_OUT_DURATION;
    LOGD("StartZoomOutAnimation zoom[%{public}lf,%{public}lf], opacity[%{public}lf,%{public}lf], duration[%{public}d]",
        zoomValue_, ZOOM_MIN, opacityValue_, OPACITY_MIN, duartion);
    zoomOutAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(zoomValue_, ZOOM_MIN, Curves::SHARP);
    zoomOutAnimation_->AddListener([weak = AceType::WeakClaim(this)](const double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateZoomValue(value);
        }
    });
    opacityOutAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(opacityValue_, OPACITY_MIN, Curves::SHARP);
    opacityOutAnimation_->AddListener([weak = AceType::WeakClaim(this)](const double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateMaskOpacity(value);
        }
    });
    zoomOutController_->ClearInterpolators();
    zoomOutController_->AddInterpolator(zoomOutAnimation_);
    zoomOutController_->AddInterpolator(opacityOutAnimation_);
    zoomOutController_->SetDuration(duartion);
    zoomOutController_->AddStopListener([weak = AceType::WeakClaim(this), isMouseHover]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            isMouseHover ? swiper->UpdateHoverStatus(false) : swiper->UpdatePressStatus(false);
        }
    });
    zoomOutController_->Play();
}

void RenderSwiper::StartZoomInDotAnimation(int32_t index)
{
    StopZoomDotAnimation(); // function will reset currentHoverIndex_. set it after stop zoom out dot.
    currentHoverIndex_ = index;
    LOGD("StartZoomInDotAnimation zoom[%{public}lf, %{public}lf], duration[%{public}d]",
        ZOOM_DOT_MIN, ZOOM_DOT_MAX, ZOOM_IN_DOT_DURATION);
    if (!zoomInDotAnimation_) {
        zoomInDotAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(ZOOM_DOT_MIN, ZOOM_DOT_MAX, Curves::SHARP);
        zoomInDotAnimation_->AddListener([weak = AceType::WeakClaim(this)](const double value) {
            auto swiper = weak.Upgrade();
            if (swiper) {
                swiper->UpdateZoomDotValue(value);
            }
        });
    }

    zoomInDotController_->ClearInterpolators();
    zoomInDotController_->AddInterpolator(zoomInDotAnimation_);
    zoomInDotController_->SetDuration(ZOOM_IN_DOT_DURATION);
    zoomInDotController_->Play();
}

void RenderSwiper::StartZoomOutDotAnimation()
{
    StopZoomDotAnimation();
    LOGD("StartZoomOutDotAnimation zoom[%{public}lf, %{public}lf], duration[%{public}d]",
        ZOOM_DOT_MAX, ZOOM_DOT_MIN, ZOOM_OUT_DOT_DURATION);
    if (!zoomOutDotAnimation_) {
        zoomOutDotAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(ZOOM_DOT_MAX, ZOOM_DOT_MIN, Curves::SHARP);
        zoomOutDotAnimation_->AddListener([weak = AceType::WeakClaim(this)](const double value) {
            auto swiper = weak.Upgrade();
            if (swiper) {
                swiper->UpdateZoomDotValue(value);
            }
        });
    }
    zoomOutDotController_->ClearInterpolators();
    zoomOutDotController_->AddInterpolator(zoomOutDotAnimation_);
    zoomOutDotController_->SetDuration(ZOOM_OUT_DOT_DURATION);
    zoomOutDotController_->AddStopListener([weak = AceType::WeakClaim(this)]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->currentHoverIndex_ = INDICATOR_INVALID_HOVER_INDEX;
        }
    });
    zoomOutDotController_->Play();
}

void RenderSwiper::StopZoomAnimation()
{
    LOGD("stopZoomAnimation");
    if (!zoomInController_->IsStopped()) {
        zoomInController_->ClearStopListeners();
        zoomInController_->Stop();
    }
    if (!zoomOutController_->IsStopped()) {
        zoomOutController_->ClearStopListeners();
        zoomOutController_->Stop();
    }
}

void RenderSwiper::StopZoomDotAnimation()
{
    LOGD("StopZoomDotAnimation");
    if (!zoomInDotController_->IsStopped()) {
        zoomInDotController_->ClearStopListeners();
        zoomInDotController_->Stop();
    }
    if (!zoomOutDotController_->IsStopped()) {
        zoomOutDotController_->ClearStopListeners();
        zoomOutDotController_->Stop();
    }
}

void RenderSwiper::StartDragRetractionAnimation()
{
    StopDragRetractionAnimation();
    dragRetractionAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(
        stretchRate_, TARGET_START_TRANSLATE_TIME, INDICATOR_ZONE_STRETCH);
    dragRetractionAnimation_->AddListener([weak = AceType::WeakClaim(this)](const double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateEdgeStretchRate(value);
        }
    });

    dragRetractionController_->ClearInterpolators();
    dragRetractionController_->AddInterpolator(dragRetractionAnimation_);
    dragRetractionController_->SetDuration(DRAG_RETRETION_DURATION);
    dragRetractionController_->Play();
}

void RenderSwiper::StopDragRetractionAnimation()
{
    if (!dragRetractionController_->IsStopped()) {
        dragRetractionController_->ClearStopListeners();
        dragRetractionController_->Stop();
    }
}

void RenderSwiper::FinishAllSwipeAnimation()
{
    StopSwipeAnimation();
    StopSwipeToAnimation();
    StopIndicatorAnimation();
    StopIndicatorSpringAnimation();
    ResetIndicatorPosition();
    UpdateItemOpacity(MAX_OPACITY, currentIndex_);
    UpdateItemOpacity(MAX_OPACITY, targetIndex_);
    currentIndex_ = targetIndex_;
}

bool RenderSwiper::IsZoomAnimationStopped()
{
    return zoomInController_->IsStopped() && zoomOutController_->IsStopped();
}

bool RenderSwiper::IsZoomOutAnimationStopped()
{
    return zoomOutController_->IsStopped();
}

bool RenderSwiper::IsZoomOutDotAnimationStopped()
{
    return zoomOutDotController_->IsStopped();
}

void RenderSwiper::UpdateIndicatorLayout()
{
    LayoutIndicator(swiperIndicatorData_);
    MarkNeedRender();
}

void RenderSwiper::UpdateIndicatorOffset(int32_t fromIndex, int32_t toIndex, double value)
{
    int32_t indicatorMoveNums = std::abs(fromIndex - toIndex);
    if (value >= 1.0) {
        // move to end, and index change
        UpdateIndicatorSpringStatus(SpringStatus::FOCUS_SWITCH);
        UpdateIndicatorPointPosistion(DRAG_OFFSET_MIN);
        UpdateIndicatorHeadPosistion(DRAG_OFFSET_MIN);
        return;
    }

    UpdateIndicatorPointPosistion(INDICATOR_NORMAL_POINT->MoveInternal(value));
    UpdateIndicatorHeadPosistion(INDICATOR_FOCUS_HEAD->MoveInternal(value) * indicatorMoveNums);
    if (value < focusStretchMaxTime_) {
        UpdateIndicatorTailPosistion(INDICATOR_FOCUS_TAIL->MoveInternal(value) * indicatorMoveNums);
        return;
    }

    // curive sport into spring sport
    if (GetIndicatorSpringStatus() == SpringStatus::SPRING_STOP) {
        LOGD("indicator tail move end, start spring sport.");
        double springStart = INDICATOR_FOCUS_TAIL->MoveInternal(value) * indicatorMoveNums;
        UpdateIndicatorTailPosistion(springStart);
        StartIndicatorSpringAnimation(springStart, indicatorMoveNums * DRAG_OFFSET_MAX);
    }
}

void RenderSwiper::UpdateIndicatorHeadPosistion(double offset)
{
    indicatorHeadOffset_ = offset * animationDirect_;
}

void RenderSwiper::UpdateIndicatorTailPosistion(double offset, double switchOffset)
{
    indicatorTailOffset_ = offset * animationDirect_;
    // if indicator switch to the next or last, tail offset will be different.
    indicatorSwitchTailOffset_ = switchOffset * animationDirect_;
    MarkNeedRender();
}

void RenderSwiper::UpdateIndicatorPointPosistion(double offset)
{
    indicatorPointOffset_ = offset * animationDirect_;
    MarkNeedRender();
}

void RenderSwiper::UpdateMaskOpacity(double value)
{
    opacityValue_ = value;
    MarkNeedRender();
}

void RenderSwiper::UpdateZoomValue(double value)
{
    zoomValue_ = value;
    LayoutIndicator(swiperIndicatorData_);
    MarkNeedRender();
}

void RenderSwiper::UpdateZoomDotValue(double value)
{
    zoomDotValue_ = value;
    LayoutIndicator(swiperIndicatorData_);
    MarkNeedRender();
}

void RenderSwiper::UpdateEdgeStretchRate(double value)
{
    stretchRate_ = value;
    widthStretchRate_ = DRAG_STRETCH_BASE_WIDTH + (DRAG_STRETCH_MAX_WIDTH - DRAG_STRETCH_BASE_WIDTH) * value;
    heightStretchRate_ = DRAG_STRETCH_BASE_HIGH + (DRAG_STRETCH_MAX_HIGH - DRAG_STRETCH_BASE_HIGH) * value;
    LayoutIndicator(swiperIndicatorData_);
    MarkNeedRender();
}

void RenderSwiper::UpdatePressStatus(bool isPress)
{
    swiperIndicatorData_.isPressed = isPress;
}

void RenderSwiper::UpdateHoverStatus(bool isHover)
{
    swiperIndicatorData_.isHovered = isHover;
}

void RenderSwiper::StartIndicatorAnimation(int32_t fromIndex, int32_t toIndex, bool isLoop)
{
    LOGD("StartIndicatorAnimation");
    if (fromIndex == toIndex) {
        LOGD("from index is same to next index.");
        return;
    }
    if (isIndicatorAnimationStart_) {
        LOGE("indicator animation is processing.");
        return;
    }

    CalMaxStretch();
    StopIndicatorSpringAnimation();
    StopIndicatorAnimation();
    ResetHoverZoomDot();
    targetIndex_ = toIndex;
    isIndicatorAnimationStart_ = true;
    animationDirect_ = (fromIndex - toIndex <= 0) ? INDICATOR_DIRECT_RTL : INDICATOR_DIRECT_LTR;
    // the start offset of swiper content zone.
    double contentOffset = (animationDirect_ == INDICATOR_DIRECT_RTL) ? (isLoop ? nextItemOffset_ : prevItemOffset_)
                                                                      : (isLoop ? prevItemOffset_ : nextItemOffset_);
    indicatorAnimation_ = AceType::MakeRefPtr<CurveAnimation<double>>(
        CUR_START_TRANSLATE_TIME, CUR_END_TRANSLATE_TIME, Curves::LINEAR);
    indicatorAnimation_->AddListener(
        [weak = AceType::WeakClaim(this), fromIndex, toIndex, contentOffset](const double value) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->UpdateIndicatorOffset(fromIndex, toIndex, value);
            double itemOffset = (value == CUR_END_TRANSLATE_TIME) ? value : Curves::EASE_OUT->MoveInternal(value);
            swiper->UpdateChildPosition(itemOffset * contentOffset, fromIndex, toIndex);
        }
    });

    indicatorController_->ClearInterpolators();
    indicatorController_->AddInterpolator(indicatorAnimation_);
    indicatorController_->SetDuration(INDICATOR_START_ANIMATION);
    indicatorController_->ClearStopListeners();
    indicatorController_->AddStopListener([weak = AceType::WeakClaim(this), fromIndex, toIndex]() {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->isIndicatorAnimationStart_ = false;
            swiper->outItemIndex_ = fromIndex;
            swiper->currentIndex_ = toIndex;
            swiper->UpdateIndicatorSpringStatus(SpringStatus::FOCUS_SWITCH);
            swiper->MarkNeedLayout();
        }
    });
    indicatorController_->Play();
}

void RenderSwiper::StopIndicatorAnimation()
{
    LOGD("stopZoomAnimation");
    if (indicatorController_ && !indicatorController_->IsStopped()) {
        indicatorController_->ClearStopListeners();
        indicatorController_->Stop();
        isIndicatorAnimationStart_ = false;
    }
}

void RenderSwiper::InitIndicatorAnimation(const WeakPtr<PipelineContext>& context)
{
    if (!springController_) {
        springController_ = AceType::MakeRefPtr<Animator>(context);
    } else {
        StopIndicatorSpringAnimation();
    }
    if (!zoomInController_) {
        zoomInController_ = AceType::MakeRefPtr<Animator>(context);
    }
    if (!zoomOutController_) {
        zoomOutController_ = AceType::MakeRefPtr<Animator>(context);
    }
    if (!zoomInDotController_) {
        zoomInDotController_ = AceType::MakeRefPtr<Animator>(context);
    }
    if (!zoomOutDotController_) {
        zoomOutDotController_ = AceType::MakeRefPtr<Animator>(context);
    }
    if (!dragRetractionController_) {
        dragRetractionController_ = AceType::MakeRefPtr<Animator>(context);
    }
    if (!indicatorController_) {
        indicatorController_ = AceType::MakeRefPtr<Animator>(context);
    } else {
        StopIndicatorAnimation();
        ResetIndicatorPosition();
    }
    CalMaxStretch();
}
} // namespace OHOS::Ace
