/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"

namespace OHOS::Ace::NG {
namespace {
inline constexpr int TWOFOLD = 2;
inline constexpr double HALF = 0.5;
inline constexpr double NORMAL_WIDEN_WIDTH = 12.0;
constexpr int32_t BAR_SHRINK_DELAY_DURATION = 2000; // 2000ms
} // namespace

bool ArcScrollBar::InBarTouchRegion(const Point& point) const
{
    if (!NeedScrollBar()) {
        return false;
    }
    return arcTouchRegion_.IsInRegion(point);
}

bool ArcScrollBar::InBarHoverRegion(const Point& point) const
{
    if (!NeedScrollBar()) {
        return false;
    }
    return arcHoverRegion_.IsInRegion(point);
}

bool ArcScrollBar::InBarRectRegion(const Point& point) const
{
    if (!NeedScrollBar()) {
        return false;
    }
    return arcAarRect_.IsInRegion(point);
}

void ArcScrollBar::SetBarRegion(const Offset& offset, const Size& size)
{
    double normalWidth = GetNormalWidthToPx();
    Point centerPoint(size.Width() * HALF, size.Height() * HALF);
    double startAngle = GetNormalStartAngle();
    double sweepAngle = GetNormaMaxOffsetAngle();
    double width = NormalizeToPx(GetNormalBackgroundWidth());
    centerDeviation_ = width * FACTOR_HALF;
    if (normalWidth == NORMAL_WIDEN_WIDTH) {
        startAngle = GetActiveStartAngle();
        sweepAngle = GetActiveMaxOffsetAngle();
        width = NormalizeToPx(GetActiveBackgroundWidth());
        centerDeviation_ = width * FACTOR_HALF;
    }
    double radius = size.Width() * FACTOR_HALF - centerDeviation_;
    arcAarRect_ = ArcRound(centerPoint, radius, startAngle, sweepAngle, width);
}

void ArcScrollBar::SetRoundTrickRegion(double estimatedHeight, double barRegionSize, double activeSize,
    double activeMainOffset, double normalWidth, const Size& size)
{
    if (!NearEqual(estimatedHeight, size.Height())) {
        width_ = NormalizeToPx(GetNormalScrollBarWidth());
        centerDeviation_ = NormalizeToPx(GetNormalBackgroundWidth()) * FACTOR_HALF;
        double maxAngle = GetNormaMaxOffsetAngle();
        if (normalWidth == NORMAL_WIDEN_WIDTH) {
            width_ = NormalizeToPx(GetActiveScrollBarWidth());
            centerDeviation_ = NormalizeToPx(GetActiveBackgroundWidth()) * FACTOR_HALF;
            maxAngle = GetActiveMaxOffsetAngle();
        }

        double trickStartAngle = 0;
        if (NearZero(barRegionSize - activeSize) || NearZero(estimatedHeight)) {
            LOGE("(barRegionSize - activeSize) or estimatedHeight is zero");
            return;
        } else {
            trickSweepAngle_ = activeSize * maxAngle / estimatedHeight;
            trickStartAngle = (maxAngle - trickSweepAngle_) * activeMainOffset / (barRegionSize - activeSize);
        }
        trickStartAngle_ = std::clamp(0.0, trickStartAngle, maxAngle) - maxAngle * FACTOR_HALF;
        double radius = size.Width() * FACTOR_HALF - centerDeviation_;

        Point centerPoint(size.Width() * HALF, size.Height() * HALF);
        arcActiveRect_ = ArcRound(centerPoint, radius, trickStartAngle_, trickSweepAngle_, width_);
        arcTouchRegion_ = ArcRound(centerPoint, radius, trickStartAngle_, trickSweepAngle_, width_);
        arcHoverRegion_ = arcTouchRegion_;
    }
    MarkNeedRender();
}

void ArcScrollBar::SetRoundTrickRegion(
    const Offset& offset, const Size& size, const Offset& lastOffset, double estimatedHeight)
{
    double normalWidth = GetNormalWidthToPx();
    Point centerPoint(size.Width() * HALF, size.Height() * HALF);

    double mainSize = size.Height();
    double barRegionSize =
        std::max(mainSize - NormalizeToPx(GetEndReservedHeight()) - NormalizeToPx(GetStartReservedHeight()), 0.0);
    SetBarRegionSize(barRegionSize);

    double activeSize = 0.0;
    if (LessOrEqual(estimatedHeight, 0.0)) {
        TAG_LOGE(AceLogTag::ACE_SCROLL_BAR, "estimatedHeight:%{public}1f", estimatedHeight);
        return;
    } else {
        activeSize = barRegionSize * (mainSize / estimatedHeight) - GetOutBoundary();
    }
    if (!NearZero(GetOutBoundary())) {
        activeSize = std::max(std::max(activeSize, NormalizeToPx(GetMinHeight()) - GetOutBoundary()),
            NormalizeToPx(GetMinDynamicHeight()));
    } else {
        activeSize = std::max(activeSize, NormalizeToPx(GetMinHeight()));
    }

    if (LessOrEqual(activeSize, normalWidth)) {
        if (GreatNotEqual(normalWidth, mainSize)) {
            normalWidth = NormalizeToPx(GetThemeNormalWidth());
        } else {
            activeSize = normalWidth;
        }
    }

    SetOffsetScale(
        NearEqual(mainSize, estimatedHeight) ? 0.0 : (barRegionSize - activeSize) / (estimatedHeight - mainSize));

    // Avoid crossing the top or bottom boundary.
    double activeMainOffset =
        std::min(GetOffsetScale() * std::max(lastOffset.GetY(), 0.0), barRegionSize - activeSize) +
        NormalizeToPx(GetStartReservedHeight());
    activeMainOffset = !IsReverse() ? activeMainOffset : barRegionSize - activeSize - activeMainOffset;
    SetRoundTrickRegion(estimatedHeight, barRegionSize, activeSize, activeMainOffset, normalWidth, size);
}

void ArcScrollBar::HandlingTouch(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(IsScrollable());
    if (info.GetTouches().empty()) {
        return;
    }
    auto touch = info.GetTouches().front();
    if (touch.GetTouchType() == TouchType::DOWN) {
        TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "inner scrollBar touch down, panDirection: %{public}u", GetPanDirection());
        Point point(touch.GetLocalLocation().GetX(), touch.GetLocalLocation().GetY());
        bool inRegion = false;
        if (info.GetSourceDevice() == SourceType::TOUCH) {
            inRegion = InBarTouchRegion(point);
        } else if (info.GetSourceDevice() == SourceType::MOUSE) {
            inRegion = InBarHoverRegion(point);
            MarkNeedRender();
        }
        SetPressed(inRegion);
        if (!IsHover()) {
            PlayScrollBarGrowAnimation();
        }
    }

    if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
        info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
        SetPressed(false);
        if (!IsPressed()) {
            ScheduleShrinkDelayTask();
            ScheduleDisappearDelayTask();
        }
        MarkNeedRender();
    }
}

void ArcScrollBar::SetGestureEvent()
{
    if (!GetTouchEvent()) {
        auto touchEvent = MakeRefPtr<TouchEventImpl>(
            std::bind(&ArcScrollBar::HandlingTouch, this, std::placeholders::_1));
        SetTouchEvent(touchEvent);
    }
    if (!GetPanRecognizer()) {
        CallInitPanRecognizer();
    }
}

float ArcScrollBar::CalcPatternOffset(float scrollBarOffset) const
{
    auto activeRectLength = arcActiveRect_.GetRadius() * TWOFOLD;
    if (!IsDriving_() || NearZero(GetBarRegionSize() - activeRectLength)) {
        return scrollBarOffset;
    }
    auto mainSize = GetViewPortSize().Height();
    auto offset = -scrollBarOffset * (GetEstimatedHeigh() - mainSize) / (GetBarRegionSize() - activeRectLength);
    return offset;
}

void ArcScrollBar::SetMouseEvent()
{
    if (GetMouseEvent()) {
        return;
    }

    auto mouseEvent = MakeRefPtr<InputEvent>([weak = WeakClaim(this)](MouseInfo& info) {
        auto scrollBar = weak.Upgrade();
        CHECK_NULL_VOID(scrollBar && scrollBar->IsScrollable());
        Point point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
        bool inBarRegion = scrollBar->InBarRectRegion(point);
        if (inBarRegion) {
            scrollBar->PlayScrollBarAppearAnimation();
            if (info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::PRESS) {
                scrollBar->SetIsMousePressed(true);
            } else {
                scrollBar->SetIsMousePressed(false);
            }
        } else if (!scrollBar->IsPressed()) {
            scrollBar->ScheduleDisappearDelayTask();
        }

        if (scrollBar->IsPressed()) {
            scrollBar->PlayScrollBarGrowAnimation();
            scrollBar->SetHover(true);
        }

        if (scrollBar->IsHover()) {
            scrollBar->SetHover(false);
            if (!scrollBar->IsPressed()) {
                scrollBar->ScheduleShrinkDelayTask();
            }
        }
        scrollBar->SetLocationInfo(info.GetLocalLocation());
    });

    SetMouseEventMember(mouseEvent);
    if (!GetLongPressRecognizer()) {
        InitLongPressEvent();
    }
}

void ArcScrollBar::ScheduleShrinkDelayTask()
{
    if (GetDisplayMode() != DisplayMode::AUTO) {
        shrinkDelayTask_.Cancel();
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        shrinkDelayTask_.Reset([weak = WeakClaim(this)] {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->PlayScrollBarShrinkAnimation();
        });
        taskExecutor->PostDelayedTask(shrinkDelayTask_, TaskExecutor::TaskType::UI, BAR_SHRINK_DELAY_DURATION,
            "ArkUIScrollBarInnerShrinkAnimation");
    }
}

void ArcScrollBar::PlayScrollBarAppearAnimation()
{
    ScrollBar::PlayScrollBarAppearAnimation();

    if (GetDisplayMode() != DisplayMode::AUTO) {
        shrinkDelayTask_.Cancel();
        MarkNeedRender();
    }
}
} // namespace OHOS::Ace::NG