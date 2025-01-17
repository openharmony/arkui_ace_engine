/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"

#include "base/log/dump_log.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BAR_DISAPPRAE_DELAY_DURATION = 2000; // 2000ms
constexpr double BAR_ADAPT_EPSLION = 1.0;
constexpr int32_t LONG_PRESS_PAGE_INTERVAL_MS = 100;
constexpr int32_t LONG_PRESS_TIME_THRESHOLD_MS = 500;
constexpr int32_t SCROLL_BAR_LAYOUT_INFO_COUNT = 30;
#ifdef ARKUI_WEARABLE
constexpr char SCROLL_BAR_VIBRATOR_WEAK[] = "watchhaptic.feedback.crown.strength3";
#endif
} // namespace

ScrollBar::ScrollBar()
{
    InitTheme();
}

ScrollBar::ScrollBar(DisplayMode displayMode, ShapeMode shapeMode, PositionMode positionMode) : ScrollBar()
{
    displayMode_ = displayMode;
    shapeMode_ = shapeMode;
    positionMode_ = positionMode;
}

void ScrollBar::InitTheme()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(theme);
    themeNormalWidth_ = theme->GetNormalWidth();
    SetInactiveWidth(themeNormalWidth_);
    SetNormalWidth(themeNormalWidth_);
    SetActiveWidth(theme->GetActiveWidth());
    SetTouchWidth(theme->GetTouchWidth());
    SetMinHeight(theme->GetMinHeight());
    SetMinDynamicHeight(theme->GetMinDynamicHeight());
    SetBackgroundColor(theme->GetBackgroundColor());
    SetForegroundColor(theme->GetForegroundColor());
    SetPadding(theme->GetPadding());
    SetHoverWidth(theme);
#ifdef ARKUI_CIRCLE_FEATURE
    SetNormalBackgroundWidth(theme->GetNormalBackgroundWidth());
    SetActiveBackgroundWidth(theme->GetActiveBackgroundWidth());
    SetNormalStartAngle(theme->GetNormalStartAngle());
    SetActiveStartAngle(theme->GetActiveStartAngle());
    SetNormaMaxOffsetAngle(theme->GetNormaMaxOffsetAngle());
    SetActiveMaxOffsetAngle(theme->GetActiveMaxOffsetAngle());
    SetNormalScrollBarWidth(theme->GetNormalScrollBarWidth());
    SetActiveScrollBarWidth(theme->GetActiveScrollBarWidth());
#endif // ARKUI_CIRCLE_FEATURE
}

bool ScrollBar::InBarTouchRegion(const Point& point) const
{
    if (NeedPaint() && shapeMode_ == ShapeMode::RECT) {
        return touchRegion_.IsInRegion(point);
    }
    return false;
}

bool ScrollBar::InBarHoverRegion(const Point& point) const
{
    if (NeedPaint() && shapeMode_ == ShapeMode::RECT) {
        return hoverRegion_.IsInRegion(point);
    }
    return false;
}

bool ScrollBar::InBarRectRegion(const Point& point) const
{
    if (NeedPaint() && shapeMode_ == ShapeMode::RECT) {
        return barRect_.IsInRegion(point);
    }
    return false;
}

BarDirection ScrollBar::CheckBarDirection(const Point& point)
{
    if (!InBarRectRegion(point)) {
        return BarDirection::BAR_NONE;
    }
    auto touchRegion = GetTouchRegion();
    auto pointOffset = OffsetF(point.GetX(), point.GetY());
    auto scrollBarTopOffset = OffsetF(touchRegion.Left(), touchRegion.Top());
    auto scrollBarBottomOffset = OffsetF(touchRegion.Right(), touchRegion.Bottom());
    auto axis = positionMode_ == PositionMode::BOTTOM ? Axis::HORIZONTAL : Axis::VERTICAL;
    if (pointOffset.GetMainOffset(axis) < scrollBarTopOffset.GetMainOffset(axis)) {
        return BarDirection::PAGE_UP;
    } else if (pointOffset.GetMainOffset(axis) > scrollBarBottomOffset.GetMainOffset(axis)) {
        return BarDirection::PAGE_DOWN;
    } else {
        return BarDirection::BAR_NONE;
    }
}

void ScrollBar::FlushBarWidth()
{
    if (shapeMode_ == ShapeMode::RECT) {
        SetRectTrickRegion(paintOffset_, viewPortSize_, lastOffset_, estimatedHeight_, SCROLL_FROM_NONE);
    } else {
        SetRoundTrickRegion(paintOffset_, viewPortSize_, lastOffset_, estimatedHeight_);
    }
    SetBarRegion(paintOffset_, viewPortSize_);
}

void ScrollBar::UpdateScrollBarRegion(
    const Offset& offset, const Size& size, const Offset& lastOffset, double estimatedHeight, int32_t scrollSource)
{
    // return if nothing changes to avoid changing opacity
    if (!positionModeUpdate_ && !normalWidthUpdate_ && paintOffset_ == offset && viewPortSize_ == size &&
        lastOffset_ == lastOffset && NearEqual(estimatedHeight_, estimatedHeight, 0.000001f) && !isReverseUpdate_) {
        return;
    }
    if (!NearEqual(estimatedHeight_, estimatedHeight, 0.000001f) || viewPortSize_ != size) {
        needAddLayoutInfo = true;
    }
    if (!NearZero(estimatedHeight)) {
        paintOffset_ = offset;
        viewPortSize_ = size;
        lastOffset_ = lastOffset;
        estimatedHeight_ = estimatedHeight;
        if (shapeMode_ == ShapeMode::RECT) {
            SetRectTrickRegion(offset, size, lastOffset, estimatedHeight, scrollSource);
        } else {
            SetRoundTrickRegion(offset, size, lastOffset, estimatedHeight);
        }
        SetBarRegion(offset, size);
        positionModeUpdate_ = false;
        normalWidthUpdate_ = false;
        isReverseUpdate_ = false;
    }
    needAddLayoutInfo =false;
}

void ScrollBar::UpdateActiveRectSize(double activeSize)
{
    if (positionMode_ == PositionMode::LEFT || positionMode_ == PositionMode::RIGHT) {
        activeRect_.SetHeight(activeSize);
        touchRegion_.SetHeight(activeSize);
        hoverRegion_.SetHeight(activeSize);
    } else if (positionMode_ == PositionMode::BOTTOM) {
        activeRect_.SetWidth(activeSize);
        touchRegion_.SetWidth(activeSize);
        hoverRegion_.SetWidth(activeSize);
    }
}

void ScrollBar::UpdateActiveRectOffset(double activeMainOffset)
{
    if (positionMode_ == PositionMode::LEFT || positionMode_ == PositionMode::RIGHT) {
        activeMainOffset = std::min(activeMainOffset, barRegionSize_ - activeRect_.Height());
        activeRect_.SetTop(activeMainOffset);
        touchRegion_.SetTop(activeMainOffset);
        hoverRegion_.SetTop(activeMainOffset);
    } else if (positionMode_ == PositionMode::BOTTOM) {
        activeMainOffset = std::min(activeMainOffset, barRegionSize_ - activeRect_.Width());
        activeRect_.SetLeft(activeMainOffset);
        touchRegion_.SetLeft(activeMainOffset);
        hoverRegion_.SetLeft(activeMainOffset);
    }
}

void ScrollBar::SetBarRegion(const Offset& offset, const Size& size)
{
    if (shapeMode_ == ShapeMode::RECT) {
        double height =
            std::max(size.Height() - NormalizeToPx(startReservedHeight_) - NormalizeToPx(endReservedHeight_), 0.0);
        if (positionMode_ == PositionMode::LEFT) {
            barRect_ = Rect(NormalizeToPx(padding_.Left()), 0.0, barWidth_, height) + offset;
        } else if (positionMode_ == PositionMode::RIGHT) {
            barRect_ =
                Rect(size.Width() - barWidth_ - NormalizeToPx(padding_.Right()), 0.0, barWidth_, height) + offset;
        } else if (positionMode_ == PositionMode::BOTTOM) {
            auto trackWidth =
                std::max(size.Width() - NormalizeToPx(startReservedHeight_) - NormalizeToPx(endReservedHeight_), 0.0);
            barRect_ =
                Rect(0.0, size.Height() - barWidth_ - NormalizeToPx(padding_.Bottom()), trackWidth, barWidth_) +
                offset;
        }
    }
}

void ScrollBar::SetRectTrickRegion(
    const Offset& offset, const Size& size, const Offset& lastOffset, double estimatedHeight, int32_t scrollSource)
{
    double mainSize = (positionMode_ == PositionMode::BOTTOM ? size.Width() : size.Height());
    barRegionSize_ = std::max(mainSize - NormalizeToPx(endReservedHeight_) - NormalizeToPx(startReservedHeight_), 0.0);
    if (LessOrEqual(estimatedHeight, 0.0)) {
        return;
    }
    double activeSize = barRegionSize_ * mainSize / estimatedHeight - outBoundary_;

    if (!NearZero(outBoundary_)) {
        activeSize =
            std::max(std::max(activeSize, NormalizeToPx(minHeight_) - outBoundary_), NormalizeToPx(minDynamicHeight_));
    } else {
        activeSize = std::max(activeSize, NormalizeToPx(minHeight_));
    }
    barWidth_ = NormalizeToPx(normalWidth_);
    if (LessOrEqual(activeSize, barWidth_)) {
        if (GreatNotEqual(barWidth_, mainSize)) {
            barWidth_ = NormalizeToPx(themeNormalWidth_);
        } else {
            activeSize = barWidth_;
        }
    }
    double lastMainOffset =
        std::max(positionMode_ == PositionMode::BOTTOM ? lastOffset.GetX() : lastOffset.GetY(), 0.0);
    if (NearEqual(mainSize, estimatedHeight)) {
        offsetScale_ = 0.0;
    } else {
        offsetScale_ = (barRegionSize_ - activeSize) / (estimatedHeight - mainSize);
    }
    // Avoid crossing the top or bottom boundary.
    double activeMainOffset =
        std::min(offsetScale_ * lastMainOffset, barRegionSize_ - activeSize) + NormalizeToPx(startReservedHeight_);
    activeMainOffset = !isReverse_ ? activeMainOffset : barRegionSize_ - activeSize - activeMainOffset;
    bool canUseAnimation = !isOutOfBoundary_ && !positionModeUpdate_ && scrollSource != SCROLL_FROM_JUMP;
    double inactiveSize = 0.0;
    double inactiveMainOffset = 0.0;
    scrollableOffset_ = activeMainOffset;
    CalcScrollBarRegion(activeMainOffset, activeSize, offset, size, inactiveMainOffset, inactiveSize);
    AddScrollBarLayoutInfo();
    // If the scrollBar length changes, start the adaptation animation
    if (!NearZero(inactiveSize) && !NearEqual(activeSize, inactiveSize, BAR_ADAPT_EPSLION) && canUseAnimation &&
        !Negative(inactiveMainOffset) && !normalWidthUpdate_) {
        PlayScrollBarAdaptAnimation();
    } else {
        needAdaptAnimation_ = false;
    }
}

void ScrollBar::CalcScrollBarRegion(double activeMainOffset, double activeSize, const Offset& offset, const Size& size,
    double& inactiveMainOffset, double& inactiveSize)
{
    if (positionMode_ == PositionMode::LEFT) {
        inactiveSize = activeRect_.Height();
        inactiveMainOffset = activeRect_.Top();
        activeRect_ =
            Rect(-NormalizeToPx(position_) + NormalizeToPx(padding_.Left()), activeMainOffset, barWidth_, activeSize) +
            offset;
        if (isUserNormalWidth_) {
            touchRegion_ = activeRect_;
            hoverRegion_ = activeRect_;
        } else {
            touchRegion_ = activeRect_ + Size(NormalizeToPx(touchWidth_), 0);
            hoverRegion_ = activeRect_ + Size(NormalizeToPx(hoverWidth_), 0);
        }
    } else if (positionMode_ == PositionMode::RIGHT) {
        inactiveSize = activeRect_.Height();
        inactiveMainOffset = activeRect_.Top();
        double x = size.Width() - barWidth_ - NormalizeToPx(padding_.Right()) + NormalizeToPx(position_);
        activeRect_ = Rect(x, activeMainOffset, barWidth_, activeSize) + offset;
        // Update the hot region
        if (isUserNormalWidth_) {
            touchRegion_ = activeRect_;
            hoverRegion_ = activeRect_;
        } else {
            touchRegion_ = activeRect_ -
                           Offset(NormalizeToPx(touchWidth_) - barWidth_ - NormalizeToPx(padding_.Right()), 0.0) +
                           Size(NormalizeToPx(touchWidth_) - barWidth_, 0);
            hoverRegion_ = activeRect_ -
                           Offset(NormalizeToPx(hoverWidth_) - barWidth_ - NormalizeToPx(padding_.Right()), 0.0) +
                           Size(NormalizeToPx(hoverWidth_) - barWidth_, 0);
        }
    } else if (positionMode_ == PositionMode::BOTTOM) {
        inactiveSize = activeRect_.Width();
        inactiveMainOffset = activeRect_.Left();
        auto positionY = size.Height() - barWidth_ - NormalizeToPx(padding_.Bottom()) + NormalizeToPx(position_);
        activeRect_ = Rect(activeMainOffset, positionY, activeSize, barWidth_) + offset;
        if (isUserNormalWidth_) {
            touchRegion_ = activeRect_;
            hoverRegion_ = activeRect_;
        } else {
            auto hotRegionOffset =
                Offset(0.0, NormalizeToPx(touchWidth_) - barWidth_ - NormalizeToPx(padding_.Bottom()));
            auto hotRegionSize = Size(0, NormalizeToPx(touchWidth_) - barWidth_);
            touchRegion_ = activeRect_ - hotRegionOffset + hotRegionSize;

            auto hoverRegionOffset =
                Offset(0.0, NormalizeToPx(hoverWidth_) - barWidth_ - NormalizeToPx(padding_.Bottom()));
            auto hoverRegionSize = Size(0, NormalizeToPx(hoverWidth_) - barWidth_);
            hoverRegion_ = activeRect_ - hoverRegionOffset + hoverRegionSize;
        }
    }
}

void ScrollBar::SetRoundTrickRegion(
    const Offset& offset, const Size& size, const Offset& lastOffset, double estimatedHeight)
{
    double diameter = std::min(size.Width(), size.Height());
    if (!NearEqual(estimatedHeight, diameter)) {
        double maxAngle = bottomAngle_ - topAngle_;
        trickSweepAngle_ = std::max(diameter * maxAngle / estimatedHeight, minAngle_);
        double lastOffsetY = std::max(lastOffset.GetY(), 0.0);
        double trickStartAngle = (maxAngle - trickSweepAngle_) * lastOffsetY / (estimatedHeight - diameter);
        trickStartAngle = std::clamp(0.0, trickStartAngle, maxAngle) - maxAngle * FACTOR_HALF;
        if (positionMode_ == PositionMode::LEFT) {
            if (trickStartAngle > 0.0) {
                trickStartAngle_ = STRAIGHT_ANGLE - trickStartAngle;
            } else {
                trickStartAngle_ = -(trickStartAngle + STRAIGHT_ANGLE);
            }
            trickSweepAngle_ = -trickSweepAngle_;
        } else {
            trickStartAngle_ = trickStartAngle;
        }
    }
}

bool ScrollBar::NeedScrollBar() const
{
    return displayMode_ == DisplayMode::AUTO || displayMode_ == DisplayMode::ON;
}

bool ScrollBar::NeedPaint() const
{
    return NeedScrollBar() && isScrollable_;
}

double ScrollBar::GetNormalWidthToPx() const
{
    return NormalizeToPx(normalWidth_);
}

float ScrollBar::CalcPatternOffset(float scrollBarOffset) const
{
    auto activeRectLength = positionMode_ == PositionMode::BOTTOM ? activeRect_.Width() : activeRect_.Height();
    if (!isDriving_ || NearZero(barRegionSize_ - activeRectLength)) {
        return scrollBarOffset;
    }
    auto mainSize = (positionMode_ == PositionMode::BOTTOM ? viewPortSize_.Width() : viewPortSize_.Height());
    return -scrollBarOffset * (estimatedHeight_ - mainSize) / (barRegionSize_ - activeRectLength);
}

double ScrollBar::NormalizeToPx(const Dimension& dimension) const
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, 0.0);
    return pipelineContext->NormalizeToPx(dimension);
}

void ScrollBar::SetGestureEvent()
{
    if (!touchEvent_) {
        touchEvent_ = MakeRefPtr<TouchEventImpl>([weak = WeakClaim(this)](const TouchEventInfo& info) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar && scrollBar->IsScrollable());
            if (info.GetTouches().empty()) {
                return;
            }
            auto touch = info.GetTouches().front();
            if (touch.GetTouchType() == TouchType::DOWN) {
                TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "inner scrollBar touch down, panDirection: %{public}u",
                    scrollBar->GetPanDirection());
                Point point(touch.GetLocalLocation().GetX(), touch.GetLocalLocation().GetY());
                bool inRegion = false;
                if (info.GetSourceDevice() == SourceType::TOUCH) {
                    inRegion = scrollBar->InBarTouchRegion(point);
                } else if (info.GetSourceDevice() == SourceType::MOUSE) {
                    inRegion = scrollBar->InBarHoverRegion(point);
                    scrollBar->MarkNeedRender();
                }
                if (!scrollBar->IsPressed()) {
                    scrollBar->SetPressed(inRegion);
                }
                if (inRegion && !scrollBar->IsHover()) {
                    scrollBar->PlayScrollBarGrowAnimation();
                }
            }
            if ((info.GetTouches().front().GetTouchType() == TouchType::UP ||
                    info.GetTouches().front().GetTouchType() == TouchType::CANCEL) &&
                    (info.GetTouches().size() <= 1)) {
                if (scrollBar->IsPressed() && !scrollBar->IsHover()) {
                    scrollBar->PlayScrollBarShrinkAnimation();
                    scrollBar->ScheduleDisappearDelayTask();
                }
                scrollBar->SetPressed(false);
                scrollBar->MarkNeedRender();
            }
        });
    }
    if (!panRecognizer_) {
        InitPanRecognizer();
    }
}

void ScrollBar::SetMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    mouseEvent_ = MakeRefPtr<InputEvent>([weak = WeakClaim(this)](MouseInfo& info) {
        auto scrollBar = weak.Upgrade();
        CHECK_NULL_VOID(scrollBar && scrollBar->IsScrollable());
        Point point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
        bool inBarRegion = scrollBar->InBarRectRegion(point);
        bool inHoverRegion = scrollBar->InBarHoverRegion(point);
        if (inBarRegion) {
            scrollBar->PlayScrollBarAppearAnimation();
            if (info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::PRESS) {
                scrollBar->isMousePressed_ = true;
            } else {
                scrollBar->isMousePressed_ = false;
            }
            scrollBar->isShowScrollBar_ = true;
        }
        if (inHoverRegion && !scrollBar->IsHover()) {
            if (!scrollBar->IsPressed()) {
                scrollBar->PlayScrollBarGrowAnimation();
            }
            scrollBar->SetHover(true);
        }
        if (scrollBar->IsHover() && !inHoverRegion) {
            scrollBar->SetHover(false);
            if (!scrollBar->IsPressed()) {
                scrollBar->PlayScrollBarShrinkAnimation();
            }
        }
        if (!inBarRegion && !inHoverRegion && !scrollBar->IsPressed() && scrollBar->isShowScrollBar_) {
            scrollBar->ScheduleDisappearDelayTask();
            scrollBar->isShowScrollBar_ = false;
        }
        scrollBar->locationInfo_ = info.GetLocalLocation();
    });
    if (!longPressRecognizer_) {
        InitLongPressEvent();
    }
}

void ScrollBar::SetHoverEvent()
{
    CHECK_NULL_VOID(!hoverEvent_);
    hoverEvent_ = MakeRefPtr<InputEvent>([weak = WeakClaim(this)](bool isHover) {
        auto scrollBar = weak.Upgrade();
        CHECK_NULL_VOID(scrollBar && scrollBar->IsScrollable());
        if (scrollBar->IsHover() && !isHover) {
            scrollBar->SetHover(false);
            if (!scrollBar->IsPressed()) {
                scrollBar->PlayScrollBarShrinkAnimation();
                scrollBar->ScheduleDisappearDelayTask();
            }
        }
    });
}

void ScrollBar::CalcReservedHeight()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
        CHECK_NULL_VOID(theme);
        startReservedHeight_ = Dimension(0.0, DimensionUnit::PX);
        endReservedHeight_ = theme->GetReservedHeight();
        FlushBarWidth();
        return;
    }
    float startRadius = 0.f;
    float endRadius = 0.f;
    float barMargin = 0.f;
    float padding = 0.f;
    float startRadiusHeight = 0.f;
    float endRadiusHeight = 0.f;
    GetRadiusAndPadding(startRadius, endRadius, padding);
    if (std::isnan(startRadius)) {
        startRadius = 0.f;
    }
    if (std::isnan(endRadius)) {
        endRadius = 0.f;
    }
    barMargin = padding + NormalizeToPx(normalWidth_) / 2;
    if (LessOrEqual(startRadius, barMargin)) {
        startReservedHeight_ = Dimension(0.0, DimensionUnit::PX);
    } else {
        startRadiusHeight = startRadius - std::sqrt(2 * padding * startRadius - padding * padding);
        startReservedHeight_ = Dimension(startRadiusHeight + (startRadius / barMargin), DimensionUnit::PX);
    }

    if (LessOrEqual(endRadius, barMargin)) {
        endReservedHeight_ = Dimension(0.0, DimensionUnit::PX);
    } else {
        endRadiusHeight = endRadius - std::sqrt(2 * padding * endRadius - padding * padding);
        endReservedHeight_ = Dimension(endRadiusHeight + (endRadius / barMargin), DimensionUnit::PX);
    }
    FlushBarWidth();
}

void ScrollBar::GetRadiusAndPadding(float& startRadius, float& endRadius, float& padding)
{
    switch (positionMode_) {
        case PositionMode::LEFT:
            startRadius = hostBorderRadius_.radiusTopLeft.value_or(Dimension()).ConvertToPx();
            endRadius = hostBorderRadius_.radiusBottomLeft.value_or(Dimension()).ConvertToPx();
            padding = NormalizeToPx(padding_.Left());
            break;
        case PositionMode::RIGHT:
            startRadius = hostBorderRadius_.radiusTopRight.value_or(Dimension()).ConvertToPx();
            endRadius = hostBorderRadius_.radiusBottomRight.value_or(Dimension()).ConvertToPx();
            padding = NormalizeToPx(padding_.Right());
            break;
        case PositionMode::BOTTOM:
            startRadius = hostBorderRadius_.radiusBottomLeft.value_or(Dimension()).ConvertToPx();
            endRadius = hostBorderRadius_.radiusBottomRight.value_or(Dimension()).ConvertToPx();
            padding = NormalizeToPx(padding_.Bottom());
            break;
        default:
            break;
    }
}

void ScrollBar::InitPanRecognizer()
{
    PanDirection panDirection;
    panDirection.type = positionMode_ == PositionMode::BOTTOM ? PanDirection::HORIZONTAL : PanDirection::VERTICAL;
    panRecognizer_ = MakeRefPtr<PanRecognizer>(1, panDirection, DEFAULT_PAN_DISTANCE.ConvertToPx());
    panRecognizer_->SetMouseDistance(DRAG_PAN_DISTANCE_MOUSE.ConvertToPx());
    panRecognizer_->SetOnActionUpdate([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleDragUpdate(info);
        }
    });
    panRecognizer_->SetOnActionEnd([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleDragEnd(info);
        }
    });
    panRecognizer_->SetOnActionStart([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleDragStart(info);
        }
    });
    panRecognizer_->SetOnActionCancel([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            GestureEvent info;
            scrollBar->HandleDragEnd(info);
        }
    });
}

void ScrollBar::StopFlingAnimation()
{
    if (frictionController_ && frictionController_->IsRunning()) {
        frictionController_->Stop();
    }
}

void ScrollBar::HandleDragStart(const GestureEvent& info)
{
    StopFlingAnimation();
    TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "inner scrollBar drag start");
    ACE_SCOPED_TRACE("inner scrollBar HandleDragStart");
    if (scrollPositionCallback_) {
        scrollPositionCallback_(0, SCROLL_FROM_START);
        if (dragFRCSceneCallback_) {
            dragFRCSceneCallback_(0, NG::SceneStatus::START);
        }
    }
    SetDragStartPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    isDriving_ = true;
}

void ScrollBar::HandleDragUpdate(const GestureEvent& info)
{
    // if historical touch point slope is zero but delta is not zero, no need to update.
    auto mainDelta = info.GetMainDelta();
    if (info.IsInterpolated()) {
        if (GetPanDirection() == Axis::VERTICAL && NearZero(info.GetInputYDeltaSlope()) && !NearZero(mainDelta)) {
            return;
        } else if (GetPanDirection() == Axis::HORIZONTAL && NearZero(info.GetInputXDeltaSlope()) &&
                   !NearZero(mainDelta)) {
            return;
        }
    }
    if (scrollPositionCallback_) {
        // The offset of the mouse wheel and gesture is opposite.
        auto offset = info.GetInputEventType() == InputEventType::AXIS ?
                      info.GetMainDelta() : CalcPatternOffset(info.GetMainDelta());
        if (IsReverse()) {
            offset = -offset;
        }
        ACE_SCOPED_TRACE("inner scrollBar HandleDragUpdate offset:%f", offset);
        scrollPositionCallback_(offset, SCROLL_FROM_BAR);
        if (dragFRCSceneCallback_) {
            dragFRCSceneCallback_(NearZero(info.GetMainDelta()) ? info.GetMainVelocity()
                                                                : info.GetMainVelocity() / info.GetMainDelta() * offset,
                NG::SceneStatus::RUNNING);
        }
    }
}

void ScrollBar::HandleDragEnd(const GestureEvent& info)
{
    if (dragFRCSceneCallback_) {
        dragFRCSceneCallback_(0, NG::SceneStatus::END);
    }
    auto velocity = IsReverse() ? -info.GetMainVelocity() : info.GetMainVelocity();
    TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "inner scrollBar drag end, velocity is %{public}f", velocity);
    ACE_SCOPED_TRACE("inner scrollBar HandleDragEnd velocity:%f", velocity);
    if (NearZero(velocity) || info.GetInputEventType() == InputEventType::AXIS) {
        if (scrollEndCallback_) {
            scrollEndCallback_();
        }
        isDriving_ = false;
        return;
    }
    SetDragEndPosition(GetMainOffset(Offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY())));
    frictionPosition_ = 0.0;
    if (frictionMotion_) {
        frictionMotion_->Reset(friction_, 0, velocity);
    } else {
        frictionMotion_ = AceType::MakeRefPtr<FrictionMotion>(friction_, 0, velocity);
        frictionMotion_->AddListener([weakBar = AceType::WeakClaim(this)](double value) {
            auto scrollBar = weakBar.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->ProcessFrictionMotion(value);
        });
    }
    SnapAnimationOptions snapAnimationOptions = {
        .snapDelta = CalcPatternOffset(frictionMotion_->GetFinalPosition()),
        .animationVelocity = -velocity,
        .dragDistance = CalcPatternOffset(GetDragOffset()),
        .fromScrollBar = true,
    };
    if (startSnapAnimationCallback_ && startSnapAnimationCallback_(snapAnimationOptions)) {
        isDriving_ = false;
        return;
    }

    if (!frictionController_) {
        auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(context);
        frictionController_ = CREATE_ANIMATOR(context);
        frictionController_->AddStopListener([weakBar = AceType::WeakClaim(this)]() {
            auto scrollBar = weakBar.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->ProcessFrictionMotionStop();
        });
    }
    frictionController_->PlayMotion(frictionMotion_);
}

void ScrollBar::ProcessFrictionMotion(double value)
{
    if (scrollPositionCallback_) {
        auto offset = CalcPatternOffset(value - frictionPosition_);
        if (!scrollPositionCallback_(offset, SCROLL_FROM_BAR_FLING)) {
            if (frictionController_ && frictionController_->IsRunning()) {
                frictionController_->Stop();
            }
        }
    }
    frictionPosition_ = value;
}

void ScrollBar::ProcessFrictionMotionStop()
{
    if (scrollEndCallback_) {
        scrollEndCallback_();
    }
    isDriving_ = false;
}

void ScrollBar::OnCollectTouchTarget(const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
    TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
    ResponseLinkResult& responseLinkResult)
{
    if (panRecognizer_ && isScrollable_) {
        panRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        panRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        panRecognizer_->SetNodeId(frameNode->GetId());
        panRecognizer_->AttachFrameNode(frameNode);
        panRecognizer_->SetTargetComponent(targetComponent);
        panRecognizer_->SetIsSystemGesture(true);
        panRecognizer_->SetRecognizerType(GestureTypeName::PAN_GESTURE);
        result.emplace_front(panRecognizer_);
        responseLinkResult.emplace_back(panRecognizer_);
    }
}

void ScrollBar::ScheduleDisappearDelayTask()
{
    if (displayMode_ == DisplayMode::AUTO && isScrollable_ && !isHover_) {
        disappearDelayTask_.Cancel();
        auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        disappearDelayTask_.Reset([weak = WeakClaim(this)] {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->PlayScrollBarDisappearAnimation();
        });
        taskExecutor->PostDelayedTask(disappearDelayTask_, TaskExecutor::TaskType::UI, BAR_DISAPPRAE_DELAY_DURATION,
            "ArkUIScrollBarInnerDisappearAnimation");
    }
}

void ScrollBar::OnCollectLongPressTarget(const OffsetF& coordinateOffset, const GetEventTargetImpl& getEventTargetImpl,
    TouchTestResult& result, const RefPtr<FrameNode>& frameNode, const RefPtr<TargetComponent>& targetComponent,
    ResponseLinkResult& responseLinkResult)
{
    if (longPressRecognizer_ && isScrollable_) {
        longPressRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        longPressRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        longPressRecognizer_->SetNodeId(frameNode->GetId());
        longPressRecognizer_->AttachFrameNode(frameNode);
        longPressRecognizer_->SetTargetComponent(targetComponent);
        longPressRecognizer_->SetIsSystemGesture(true);
        longPressRecognizer_->SetRecognizerType(GestureTypeName::LONG_PRESS_GESTURE);
        longPressRecognizer_->SetSysGestureJudge([](const RefPtr<GestureInfo>& gestureInfo,
                                                 const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
            const auto &inputEventType = gestureInfo->GetInputEventType();
            TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "input event type:%{public}d", inputEventType);
            if (inputEventType == InputEventType::MOUSE_BUTTON) {
                return GestureJudgeResult::CONTINUE;
            }
            return GestureJudgeResult::REJECT;
        });
        result.emplace_front(longPressRecognizer_);
        responseLinkResult.emplace_back(longPressRecognizer_);
    }
}

void ScrollBar::InitLongPressEvent()
{
    longPressRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_TIME_THRESHOLD_MS, 1, false, false);
    longPressRecognizer_->SetOnAction([weakBar = AceType::WeakClaim(this)](const GestureEvent& info) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleLongPress(true);
        }
    });
}

void ScrollBar::HandleLongPress(bool smooth)
{
    Point point(locationInfo_.GetX(), locationInfo_.GetY());
    bool reverse = false;
    if (AnalysisUpOrDown(point, reverse) && isMousePressed_) {
        scrollPageCallback_(reverse, smooth);
        ScheduleCaretLongPress();
    }
}

bool ScrollBar::AnalysisUpOrDown(Point point, bool& reverse)
{
    switch (CheckBarDirection(point)) {
        case BarDirection::BAR_NONE:
            return false;
        case BarDirection::PAGE_UP:
            reverse = true;
            return true;
        case BarDirection::PAGE_DOWN:
            reverse = false;
            return true;
    }
}

void ScrollBar::ScheduleCaretLongPress()
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    if (!context->GetTaskExecutor()) {
        return;
    }
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleLongPress(true);
        },
        TaskExecutor::TaskType::UI, LONG_PRESS_PAGE_INTERVAL_MS, "ArkUIScrollBarInnerHandleLongPress");
}

void ScrollBar::AddScrollBarLayoutInfo()
{
    CHECK_NULL_VOID(needAddLayoutInfo);
    if (innerScrollBarLayoutInfos_.size() >= SCROLL_BAR_LAYOUT_INFO_COUNT) {
        innerScrollBarLayoutInfos_.pop_front();
    }
    innerScrollBarLayoutInfos_.push_back(InnerScrollBarLayoutInfo({
        .layoutTime_ = GetSysTimestamp(),
        .viewPortSize_ = viewPortSize_,
        .lastOffset_ = lastOffset_,
        .estimatedHeight_ = estimatedHeight_,
        .outBoundary_ = outBoundary_,
        .activeRect_ = activeRect_,
    }));
}

void ScrollBar::GetShapeModeDumpInfo()
{
    switch (shapeMode_) {
        case ShapeMode::RECT: {
            DumpLog::GetInstance().AddDesc("shapeMode: RECT");
            break;
        }
        case ShapeMode::ROUND: {
            DumpLog::GetInstance().AddDesc("shapeMode: ROUND");
            break;
        }
        case ShapeMode::DEFAULT: {
            DumpLog::GetInstance().AddDesc("shapeMode: DEFAULT");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBar::GetPositionModeDumpInfo()
{
    switch (positionMode_) {
        case PositionMode::RIGHT: {
            DumpLog::GetInstance().AddDesc("positionMode: RIGHT");
            DumpLog::GetInstance().AddDesc(std::string("padding.right: ").append(padding_.Right().ToString()));
            break;
        }
        case PositionMode::LEFT: {
            DumpLog::GetInstance().AddDesc("positionMode: LEFT");
            DumpLog::GetInstance().AddDesc(std::string("padding.left: ").append(padding_.Left().ToString()));
            break;
        }
        case PositionMode::BOTTOM: {
            DumpLog::GetInstance().AddDesc("positionMode: BOTTOM");
            DumpLog::GetInstance().AddDesc(std::string("padding.bottom: ").append(padding_.Bottom().ToString()));
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBar::GetAxisDumpInfo()
{
    switch (axis_) {
        case Axis::NONE: {
            DumpLog::GetInstance().AddDesc("axis: NONE");
            break;
        }
        case Axis::VERTICAL: {
            DumpLog::GetInstance().AddDesc("axis: VERTICAL");
            break;
        }
        case Axis::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("axis: HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            DumpLog::GetInstance().AddDesc("axis: FREE");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBar::GetPanDirectionDumpInfo()
{
    if (panRecognizer_) {
        switch (panRecognizer_->GetAxisDirection()) {
            case Axis::NONE: {
                DumpLog::GetInstance().AddDesc("panDirection: NONE");
                break;
            }
            case Axis::VERTICAL: {
                DumpLog::GetInstance().AddDesc("panDirection: VERTICAL");
                break;
            }
            case Axis::HORIZONTAL: {
                DumpLog::GetInstance().AddDesc("panDirection: HORIZONTAL");
                break;
            }
            case Axis::FREE: {
                DumpLog::GetInstance().AddDesc("panDirection: FREE");
                break;
            }
            default: {
                break;
            }
        }
    } else {
        DumpLog::GetInstance().AddDesc("panDirection is null");
    }
}

void ScrollBar::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("activeRect: ").append(activeRect_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("touchRegion: ").append(touchRegion_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("hoverRegion: ").append(hoverRegion_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("normalWidth: ").append(normalWidth_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("activeWidth: ").append(activeWidth_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("touchWidth: ").append(touchWidth_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("hoverWidth: ").append(hoverWidth_.ToString()));
    GetShapeModeDumpInfo();
    GetPositionModeDumpInfo();
    GetAxisDumpInfo();
    GetPanDirectionDumpInfo();
    DumpLog::GetInstance().AddDesc(std::string("hostBorderRadius: ").append(hostBorderRadius_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("startReservedHeight: ").append(startReservedHeight_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("endReservedHeight: ").append(endReservedHeight_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("isScrollable: ").append(std::to_string(isScrollable_)));
    DumpLog::GetInstance().AddDesc(std::string("isReverse: ").append(std::to_string(isReverse_)));
    DumpLog::GetInstance().AddDesc("==========================innerScrollBarLayoutInfos==========================");
    for (const auto& info : innerScrollBarLayoutInfos_) {
        DumpLog::GetInstance().AddDesc(info.ToString());
    }
    DumpLog::GetInstance().AddDesc("==========================innerScrollBarLayoutInfos==========================");
}

Color ScrollBar::GetForegroundColor() const
{
    return IsPressed() ? foregroundColor_.BlendColor(PRESSED_BLEND_COLOR) : foregroundColor_;
}

void ScrollBar::SetHoverWidth(const RefPtr<ScrollBarTheme>& theme)
{
    hoverWidth_ = theme->GetActiveWidth() + theme->GetScrollBarMargin() * 2;
}

void ScrollBar::SetNormalWidth(const Dimension& normalWidth)
{
    if (normalWidth_ != normalWidth) {
        normalWidthUpdate_ = true;
        normalWidth_ = normalWidth;
        CalcReservedHeight();
        MarkNeedRender();
    }
}

void ScrollBar::SetScrollable(bool isScrollable)
{
    CHECK_NULL_VOID(isScrollable_ != isScrollable);
    isScrollable_ = isScrollable;
}

void ScrollBar::SetPositionMode(PositionMode positionMode)
{
    if (positionMode_ != positionMode) {
        positionModeUpdate_ = true;
        positionMode_ = positionMode;
        if (panRecognizer_) {
            PanDirection panDirection;
            panDirection.type =
                positionMode_ == PositionMode::BOTTOM ? PanDirection::HORIZONTAL : PanDirection::VERTICAL;
            panRecognizer_->SetDirection(panDirection);
        }
    }
}

void ScrollBar::SetDisplayMode(DisplayMode displayMode)
{
    CHECK_NULL_VOID(displayMode_ != displayMode);
    displayMode_ = displayMode;
}

void ScrollBar::PlayScrollBarDisappearAnimation()
{
    if (displayMode_ == DisplayMode::AUTO && isScrollable_ && !isHover_ && !isPressed_) {
        opacityAnimationType_ = OpacityAnimationType::DISAPPEAR;
        MarkNeedRender();
    }
}

void ScrollBar::PlayScrollBarAppearAnimation()
{
    if (displayMode_ == DisplayMode::AUTO && isScrollable_) {
        disappearDelayTask_.Cancel();
        opacityAnimationType_ = OpacityAnimationType::APPEAR;
        MarkNeedRender();
    }
}

void ScrollBar::PlayScrollBarGrowAnimation()
{
#ifdef ARKUI_WEARABLE
    VibratorUtils::StartVibraFeedback(SCROLL_BAR_VIBRATOR_WEAK);
#endif
    PlayScrollBarAppearAnimation();
    normalWidth_ = activeWidth_;
    FlushBarWidth();
    hoverAnimationType_ = HoverAnimationType::GROW;
    MarkNeedRender();
}

void ScrollBar::PlayScrollBarShrinkAnimation()
{
#ifdef ARKUI_WEARABLE
    VibratorUtils::StartVibraFeedback(SCROLL_BAR_VIBRATOR_WEAK);
#endif
    normalWidth_ = inactiveWidth_;
    FlushBarWidth();
    hoverAnimationType_ = HoverAnimationType::SHRINK;
    MarkNeedRender();
}

void ScrollBar::PlayScrollBarAdaptAnimation()
{
    needAdaptAnimation_ = true;
    MarkNeedRender();
}

void ScrollBar::MarkNeedRender()
{
    if (markNeedRenderFunc_) {
        markNeedRenderFunc_();
    }
}

float ScrollBar::GetMainOffset(const Offset& offset) const
{
    return positionMode_ == PositionMode::BOTTOM ? offset.GetX() : offset.GetY();
}

void ScrollBar::SetReverse(bool reverse)
{
    if (isReverse_ != reverse) {
        isReverse_ = reverse;
        isReverseUpdate_ = true;
    }
}

Axis ScrollBar::GetPanDirection() const
{
    CHECK_NULL_RETURN(panRecognizer_, Axis::NONE);
    return panRecognizer_->GetAxisDirection();
}

void ScrollBar::GetShapeModeDumpInfo(std::unique_ptr<JsonValue>& json)
{
    switch (shapeMode_) {
        case ShapeMode::RECT: {
            json->Put("shapeMode", "RECT");
            break;
        }
        case ShapeMode::ROUND: {
            json->Put("shapeMode", "ROUND");
            break;
        }
        case ShapeMode::DEFAULT: {
            json->Put("shapeMode", "DEFAULT");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBar::GetPositionModeDumpInfo(std::unique_ptr<JsonValue>& json)
{
    switch (positionMode_) {
        case PositionMode::RIGHT: {
            json->Put("padding.right", padding_.Right().ToString().c_str());
            break;
        }
        case PositionMode::LEFT: {
            json->Put("padding.left", padding_.Left().ToString().c_str());
            break;
        }
        case PositionMode::BOTTOM: {
            json->Put("padding.bottom", padding_.Bottom().ToString().c_str());
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBar::GetAxisDumpInfo(std::unique_ptr<JsonValue>& json)
{
    switch (axis_) {
        case Axis::NONE: {
            json->Put("axis", "NONE");
            break;
        }
        case Axis::VERTICAL: {
            json->Put("axis", "VERTICAL");
            break;
        }
        case Axis::HORIZONTAL: {
            json->Put("axis", "HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            json->Put("axis", "FREE");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollBar::GetPanDirectionDumpInfo(std::unique_ptr<JsonValue>& json)
{
    if (panRecognizer_) {
        switch (panRecognizer_->GetAxisDirection()) {
            case Axis::NONE: {
                json->Put("panDirection", "NONE");
                break;
            }
            case Axis::VERTICAL: {
                json->Put("panDirection", "VERTICAL");
                break;
            }
            case Axis::HORIZONTAL: {
                json->Put("panDirection", "HORIZONTAL");
                break;
            }
            case Axis::FREE: {
                json->Put("panDirection", "FREE");
                break;
            }
            default: {
                break;
            }
        }
    }
}

void ScrollBar::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("activeRect", activeRect_.ToString().c_str());
    json->Put("touchRegion", touchRegion_.ToString().c_str());
    json->Put("hoverRegion", hoverRegion_.ToString().c_str());
    json->Put("normalWidth", normalWidth_.ToString().c_str());
    json->Put("activeWidth", activeWidth_.ToString().c_str());
    json->Put("touchWidth", touchWidth_.ToString().c_str());
    json->Put("hoverWidth", hoverWidth_.ToString().c_str());
    GetShapeModeDumpInfo(json);
    GetPositionModeDumpInfo(json);
    GetAxisDumpInfo(json);
    GetPanDirectionDumpInfo(json);
    json->Put("hostBorderRadius", hostBorderRadius_.ToString().c_str());
    json->Put("startReservedHeight", startReservedHeight_.ToString().c_str());
    json->Put("endReservedHeight", endReservedHeight_.ToString().c_str());
    json->Put("isScrollable", std::to_string(isScrollable_).c_str());
    json->Put("isReverse", std::to_string(isReverse_).c_str());

    std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
    for (const auto& info : innerScrollBarLayoutInfos_) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        info.ToJson(child);
        children->Put(child);
    }
    json->Put("innerScrollBarLayoutInfos", children);
}
} // namespace OHOS::Ace::NG
