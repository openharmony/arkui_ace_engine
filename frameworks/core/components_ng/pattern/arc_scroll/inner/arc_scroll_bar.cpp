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
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
inline constexpr double HALF = 0.5;
Dimension MIN_HOTREGION = 36.0_vp;
} // namespace

bool ArcScrollBar::InBarTouchRegion(const Point& point) const
{
    if (!NeedScrollBar()) {
        return false;
    }
    return arcHotZoneRect_.IsInRegion(point, static_cast<float>(MIN_HOTREGION.ConvertToPx()));
}

bool ArcScrollBar::InBarHoverRegion(const Point& point) const
{
    if (!NeedScrollBar()) {
        return false;
    }
    return arcHoverRegion_.IsInRegion(point, static_cast<float>(MIN_HOTREGION.ConvertToPx()));
}

bool ArcScrollBar::InBarRectRegion(const Point& point) const
{
    if (!NeedScrollBar()) {
        return false;
    }
    return arcAarRect_.IsInRegion(point, static_cast<float>(MIN_HOTREGION.ConvertToPx()));
}

void ArcScrollBar::SetBarRegion(const Offset& offset, const Size& size)
{
    double normalWidth = GetNormalWidthToPx();
    Point centerPoint(size.Width() * HALF, size.Height() * HALF);
    double startAngle = GetNormalStartAngle();
    double sweepAngle = GetPositionMode() == PositionMode::LEFT ? -GetNormaMaxOffsetAngle() : GetNormaMaxOffsetAngle();
    double width = NormalizeToPx(GetNormalBackgroundWidth());
    centerDeviation_ = width * FACTOR_HALF;
    if (normalWidth == NormalizeToPx(GetActiveWidth())) {
        startAngle = GetActiveStartAngle();
        sweepAngle = GetPositionMode() == PositionMode::LEFT ? -GetActiveMaxOffsetAngle() : GetActiveMaxOffsetAngle();
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
        if (normalWidth == NormalizeToPx(GetActiveWidth())) {
            width_ = NormalizeToPx(GetActiveScrollBarWidth());
            centerDeviation_ = NormalizeToPx(GetActiveBackgroundWidth()) * FACTOR_HALF;
            maxAngle = GetActiveMaxOffsetAngle();
        }

        double trickStartAngle = 0;
        if (NearZero(barRegionSize - activeSize) || NearZero(barRegionSize)) {
            LOGE("(barRegionSize - activeSize) or barRegionSize  is zero");
            return;
        } else {
            trickSweepAngle_ = activeSize * maxAngle / barRegionSize;
            trickStartAngle = (maxAngle - trickSweepAngle_) * activeMainOffset / (barRegionSize - activeSize);
        }
        trickStartAngle = std::clamp(0.0, trickStartAngle, maxAngle) - maxAngle * FACTOR_HALF;
        if (GetPositionMode() == PositionMode::LEFT) {
            if (trickStartAngle > 0.0) {
                trickStartAngle_ = STRAIGHT_ANGLE - trickStartAngle;
            } else {
                trickStartAngle_ = -(trickStartAngle + STRAIGHT_ANGLE);
            }
            trickSweepAngle_ = -trickSweepAngle_;
        } else {
            trickStartAngle_ = trickStartAngle;
        }
        double radius = size.Width() * FACTOR_HALF - centerDeviation_;

        Point centerPoint(size.Width() * HALF, size.Height() * HALF);
        arcHotZoneRect_ = ArcRound(centerPoint, radius, trickStartAngle_, trickSweepAngle_,
            NormalizeToPx(GetActiveBackgroundWidth()));
        arcHotZoneRect_.SetPositionMode(GetPositionMode());
        arcActiveRect_ = ArcRound(centerPoint, radius, trickStartAngle_, trickSweepAngle_, width_);
        arcHoverRegion_ = arcActiveRect_;
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
        activeSize = barRegionSize * (mainSize / estimatedHeight) - GetOutBoundary() * HALF;
    }
    auto minHeight = GetMinAngle() * barRegionSize / GetNormaMaxOffsetAngle();
    if (!NearZero(GetOutBoundary())) {
        activeSize = std::max(std::max(activeSize, minHeight - GetOutBoundary() * HALF),
            NormalizeToPx(GetMinDynamicHeight()));
    } else {
        activeSize = std::max(activeSize, minHeight);
    }

    if (LessOrEqual(activeSize, normalWidth)) {
        if (GreatNotEqual(normalWidth, mainSize)) {
            normalWidth = NormalizeToPx(GetThemeNormalWidth());
        } else {
            activeSize = normalWidth * HALF;
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

float ArcScrollBar::CalcPatternOffset(float scrollBarOffset) const
{
    auto activeRectLength = GetBarRegionSize() * (arcActiveRect_.GetSweepAngle() / arcAarRect_.GetSweepAngle());
    if (!IsDriving_() || NearZero(GetBarRegionSize() - activeRectLength)) {
        return scrollBarOffset;
    }
    auto mainSize = GetViewPortSize().Height();
    auto offset = -scrollBarOffset * (GetEstimatedHeigh() - mainSize) / (GetBarRegionSize() - activeRectLength);
    return offset;
}

void ArcScrollBar::CalcReservedHeight()
{
    SetStartReservedHeight(Dimension(0.0, DimensionUnit::PX));
    SetEndReservedHeight(Dimension(0.0, DimensionUnit::PX));
    FlushBarWidth();
}
} // namespace OHOS::Ace::NG