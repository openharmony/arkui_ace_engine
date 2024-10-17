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

#include "core/components/common/properties/scroll_bar.h"

namespace OHOS::Ace {

bool ScrollBar::InBarRegion(const Point& point) const
{
    if (NeedScrollBar() && shapeMode_ == ShapeMode::RECT) {
        return touchRegion_.IsInRegion(point);
    }
    return false;
}

void ScrollBar::UpdateScrollBarRegion(
    const Offset& offset, const Size& size, const Offset& lastOffset, double estimatedHeight)
{
    if (!NearZero(estimatedHeight)) {
        SetBarRegion(offset, size);
        if (shapeMode_ == ShapeMode::RECT) {
            SetRectTrickRegion(offset, size, lastOffset, estimatedHeight);
        } else {
            SetRoundTrickRegion(offset, size, lastOffset, estimatedHeight);
        }
    }
}

void ScrollBar::SetBarRegion(const Offset& offset, const Size& size)
{
    double normalWidth = NormalizeToPx(normalWidth_);
    if (shapeMode_ == ShapeMode::RECT) {
        double height = std::max(size.Height() - NormalizeToPx(reservedHeight_), 0.0);
        if (positionMode_ == PositionMode::LEFT) {
            barRect_ = Rect(0.0, 0.0, normalWidth, height) + offset;
        } else if (positionMode_ == PositionMode::RIGHT) {
            barRect_ = Rect(size.Width() - normalWidth - NormalizeToPx(padding_.Right()), 0.0,
                normalWidth, height) + offset;
        } else if (positionMode_ == PositionMode::BOTTOM) {
            auto scrollBarWidth = std::max(size.Width() - NormalizeToPx(reservedHeight_), 0.0);
            barRect_ = Rect(0.0, size.Height() - normalWidth - NormalizeToPx(padding_.Bottom()),
                scrollBarWidth, normalWidth) + offset;
        }
    }
}

void ScrollBar::SetRectTrickRegion(const Offset& offset, const Size& size,
    const Offset& lastOffset, double estimatedHeight)
{
    double mainSize = (positionMode_ == PositionMode::BOTTOM ? size.Width() : size.Height());
    double barRegionSize = std::max(mainSize - NormalizeToPx(reservedHeight_), 0.0);
    double activeSize = barRegionSize * mainSize / estimatedHeight - outBoundary_;
    if (!NearEqual(mainSize, estimatedHeight)) {
        if (!NearZero(outBoundary_)) {
            activeSize = std::max(
                std::max(activeSize, NormalizeToPx(minHeight_) - outBoundary_), NormalizeToPx(minDynamicHeight_));
        } else {
            activeSize = std::max(activeSize, NormalizeToPx(minHeight_));
        }
        double lastMainOffset =
            std::max(positionMode_ == PositionMode::BOTTOM ? lastOffset.GetX() : lastOffset.GetY(), 0.0);
        double activeMainOffset = (mainSize - activeSize) * lastMainOffset / (estimatedHeight - mainSize);
        activeMainOffset = std::min(activeMainOffset, barRegionSize - activeSize);
        double normalWidth = NormalizeToPx(normalWidth_);
        if (positionMode_ == PositionMode::LEFT) {
            activeRect_ = Rect(-NormalizeToPx(position_), activeMainOffset, normalWidth, activeSize) + offset;
            touchRegion_ = activeRect_ + Size(NormalizeToPx(touchWidth_), 0);
        } else if (positionMode_ == PositionMode::RIGHT) {
            double x = size.Width() - normalWidth - NormalizeToPx(padding_.Right()) + NormalizeToPx(position_);
            activeRect_ = Rect(x, activeMainOffset, normalWidth, activeSize) + offset;
            // Update the hot region
            touchRegion_ =
                activeRect_ -
                Offset(NormalizeToPx(touchWidth_) - NormalizeToPx(normalWidth_) - NormalizeToPx(padding_.Right()),
                    0.0) +
                Size(NormalizeToPx(touchWidth_) - NormalizeToPx(normalWidth_), 0);
        } else if (positionMode_ == PositionMode::BOTTOM) {
            auto positionY =
                size.Height() - normalWidth - NormalizeToPx(padding_.Bottom()) + NormalizeToPx(position_);
            activeRect_ = Rect(activeMainOffset, positionY, activeSize, normalWidth) + offset;
            auto hotRegionOffset =
                Offset(0.0, NormalizeToPx(touchWidth_) - NormalizeToPx(normalWidth_)
                    - NormalizeToPx(padding_.Bottom()));
            auto hotRegionSize = Size(0, NormalizeToPx(touchWidth_) - NormalizeToPx(normalWidth_));
            touchRegion_ = activeRect_ - hotRegionOffset + hotRegionSize;
        }
    }
}

void ScrollBar::SetRoundTrickRegion(const Offset& offset, const Size& size,
    const Offset& lastOffset, double estimatedHeight)
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

void ScrollBar::InitScrollBar(const WeakPtr<RenderNode>& scroll, const WeakPtr<PipelineContext>& context)
{
    pipelineContext_ = context;
    if (NeedScrollBar()) {
        if (!barController_) {
            barController_ = AceType::MakeRefPtr<ScrollBarController>();
        }
        bool isVertical = (positionMode_ == PositionMode::LEFT || positionMode_ == PositionMode::RIGHT);
        barController_->Initialize(context, isVertical);
        barController_->SetScrollNode(scroll);
        barController_->SetActiveWidth(activeWidth_);
        barController_->SetInactiveWidth(inactiveWidth_);
    }
}

double ScrollBar::NormalizeToPx(const Dimension& dimension) const
{
    auto pipelineContext = pipelineContext_.Upgrade();
    if (!pipelineContext) {
        LOGE("NormalizeToPx failed");
        return 0.0;
    }
    return pipelineContext->NormalizeToPx(dimension);
}

void ScrollBar::SetCallBack(const ScrollBarPositionCallback& callback, const ScrollBarEndCallback& barEndCallback,
    const ScrollBarEventCallback& scrollEndCallback)
{
    if (barController_) {
        barController_->SetCallback(callback);
        barController_->SetBarEndCallback(barEndCallback);
        barController_->SetScrollEndCallback(scrollEndCallback);
        barController_->SetTouchDownCallback([weakScrollBar = AceType::WeakClaim(this)](double value) {
            auto scrollBar = weakScrollBar.Upgrade();
            if (!scrollBar) {
                LOGE("scrollBar is released");
                return;
            }
            // value is normalized before animation
            scrollBar->normalWidth_ = Dimension(value, DimensionUnit::PX);
        });
        barController_->SetTouchUpCallback([weakScrollBar = AceType::WeakClaim(this)](double value) {
            auto scrollBar = weakScrollBar.Upgrade();
            if (!scrollBar) {
                LOGE("scrollBar is released");
                return;
            }
            // value is normalized before animation
            scrollBar->normalWidth_ = Dimension(value, DimensionUnit::PX);
        });
    }
}

void ScrollBar::HandleScrollBarEnd()
{
    if (displayMode_ == DisplayMode::AUTO) {
        barController_->HandleScrollBarEnd();
    }
}

void ScrollBar::AddScrollBarController(const Offset& coordinateOffset, TouchTestResult& result)
{
    if (barController_) {
        barController_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(barController_);
    }
}

void ScrollBar::SetActive(bool isActive)
{
    if (barController_) {
        barController_->SetActive(isActive);
    }
}

bool ScrollBar::IsActive() const
{
    if (barController_) {
        return barController_->IsActive();
    }
    return false;
}

Size ScrollBar::GetRootSize() const
{
    auto context = pipelineContext_.Upgrade();
    if (context) {
        auto rootHeight = context->GetRootHeight();
        auto rootWidth = context->GetRootWidth();
        return Size(rootWidth, rootHeight);
    } else {
        return Size();
    }
}

void ScrollBar::Reset(const RefPtr<ScrollBar>& scrollBar)
{
    if (scrollBar) {
        displayMode_ = scrollBar->GetDisplayMode();
        backgroundColor_ = scrollBar->GetBackgroundColor();
        foregroundColor_ = scrollBar->GetForegroundColor();
        inactiveWidth_ = scrollBar->GetInactiveWidth();
        normalWidth_ = scrollBar->GetNormalWidth();
        activeWidth_ = scrollBar->GetActiveWidth();
        touchWidth_ = scrollBar->GetTouchWidth();
    }
    if (!barController_) {
        return;
    }
    if (displayMode_ == DisplayMode::AUTO) {
        barController_->HandleScrollBarEnd();
        return;
    }
    barController_->Reset();
}

} // namespace OHOS::Ace