/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_scroll_bar.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
GridScrollBar::~GridScrollBar()
{
    CHECK_NULL_VOID_NOLOG(touchEvent_);
    auto gridPattern = pattern_.Upgrade();
    CHECK_NULL_VOID_NOLOG(gridPattern);
    auto hub = gridPattern->GetEventHub<EventHub>();
    CHECK_NULL_VOID_NOLOG(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID_NOLOG(gestureHub);
    gestureHub->RemoveTouchEvent(touchEvent_);
}

void GridScrollBar::OnInnerBarTouch(const TouchEventInfo& info)
{
    CHECK_NULL_VOID_NOLOG(innerBar_);
    if (info.GetTouches().empty()) {
        return;
    }
    auto host = pattern_.Upgrade()->GetHost();
    auto touch = info.GetTouches().front();
    if (touch.GetTouchType() == TouchType::DOWN) {
        Point point(touch.GetLocalLocation().GetX(), touch.GetLocalLocation().GetY());
        innerBar_->SetDriving(innerBar_->InBarRegion(point));
        innerBar_->SetPressed(innerBar_->InBarRegion(point));
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    if (touch.GetTouchType() == TouchType::UP) {
        innerBar_->SetDriving(false);
        innerBar_->SetPressed(false);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

bool GridScrollBar::OnInnerBarScroll(float offset)
{
    CHECK_NULL_RETURN_NOLOG(innerBar_, false);
    if (!innerBar_->IsPressed()) {
        return false;
    }
    offset = innerBar_->CalcPatternOffset(-offset);
    return pattern_.Upgrade()->UpdateScrollPosition(offset);
}

void GridScrollBar::CreateInnerBar()
{
    auto gridPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(gridPattern);

    if (!SetInnerBarProperties(gridPattern)) {
        return;
    }

    auto hub = gridPattern->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>([weak = pattern_](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->scrollBar_);
        pattern->scrollBar_->OnInnerBarTouch(info);
    });
    gestureHub->AddTouchEvent(touchEvent_);
}

bool GridScrollBar::SetInnerBarProperties(const RefPtr<GridPattern>& gridPattern)
{
    auto gridPaintProperty = gridPattern->GetPaintProperty<GridPaintProperty>();
    const auto& property = gridPaintProperty->GetScrollBarProperty();

    DisplayMode displayMode = DisplayMode::OFF;
    if (gridPattern->isConfigScrollable_ && property) {
        displayMode = property->GetScrollBarMode().value_or(DisplayMode::OFF);
    }
    if (displayMode == DisplayMode::OFF) {
        innerBar_.Reset();
        return false;
    }

    innerBar_ = AceType::MakeRefPtr<ScrollBar>();
    auto barPositionMode =
        (gridPattern->gridLayoutInfo_.axis_ == Axis::HORIZONTAL) ? PositionMode::BOTTOM : PositionMode::RIGHT;

    innerBar_->SetDisplayMode(displayMode);
    innerBar_->SetPositionMode(barPositionMode);
    auto barColor = property->GetScrollBarColor();
    if (barColor) {
        innerBar_->SetForegroundColor(barColor.value());
    }
    auto barWidth = property->GetScrollBarWidth();
    if (barWidth) {
        innerBar_->SetInactiveWidth(barWidth.value());
        innerBar_->SetNormalWidth(barWidth.value());
        innerBar_->SetActiveWidth(barWidth.value());
        innerBar_->SetTouchWidth(barWidth.value());
    }
    return true;
}

void GridScrollBar::CreateBarProxy(const RefPtr<NG::ScrollBarProxy>& scrollBarProxy)
{
    CHECK_NULL_VOID(scrollBarProxy);

    auto onScroll = [weak = pattern_](double offset, int32_t source) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            if (!pattern || !pattern->isConfigScrollable_) {
                return false;
            }
            // TODO: jump and UpdateScrollPosition while offset is large
            pattern->UpdateScrollPosition(offset);
            return true;
        }
        return true;
    };
    scrollBarProxy->RegisterScrollableNode({ pattern_, std::move(onScroll) });
    scrollBarProxy_ = scrollBarProxy;
}

void GridScrollBar::UpdateBarOffset(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    if (!innerBar_ && !scrollBarProxy_) {
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);

    auto gridPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(gridPattern);
    const auto& info = gridPattern->gridLayoutInfo_;
    auto viewScopeSize = layoutWrapper->GetGeometryNode()->GetPaddingSize();
    auto layoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());

    float heightSum = 0;
    for (const auto& item : info.lineHeightMap_) {
        heightSum += item.second;
    }

    auto averageHeight_ = heightSum / (info.endIndex_ - info.startIndex_ + 1);
    int32_t estimateLineCount = (info.childrenCount_ + info.crossCount_ - 1) / info.crossCount_;
    estimatedHeight_ = info.childrenCount_ * averageHeight_;
    auto gap = (info.axis_ == Axis::HORIZONTAL) ? layoutProperty->GetRowsGap() : layoutProperty->GetColumnsGap();
    if (gap) {
        estimatedHeight_ += gap.value().ConvertToPx() * (estimateLineCount - 1);
    }
    offset_ = info.startIndex_ * averageHeight_ - info.currentOffset_;
    Offset scrollOffset { offset_, offset_ };
    Size mainSize = { viewScopeSize.Width(), viewScopeSize.Height() };

    if (innerBar_) {
        innerBar_->UpdateScrollBarRegion(Offset(), mainSize, scrollOffset, estimatedHeight_);
        gridPattern->GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    if (scrollBarProxy_) {
        float mainHeight = (info.axis_ == Axis::HORIZONTAL) ? mainSize.Width() : mainSize.Height();
        estimatedHeight_ -= mainHeight;
        scrollBarProxy_->NotifyScrollBar(pattern_);
    }
}
} // namespace OHOS::Ace::NG
