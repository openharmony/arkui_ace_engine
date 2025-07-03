/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/scroll/inner/scroll_bar_2d.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
namespace OHOS::Ace::NG {
namespace {

void ConfigureScrollBar(const std::unique_ptr<ScrollBarProperty>& property, ScrollBar& scrollBar)
{
    const auto& barWidth = property->GetScrollBarWidth();
    if (barWidth) {
        scrollBar.SetActiveWidth(*barWidth);
        scrollBar.SetTouchWidth(*barWidth);
        scrollBar.SetInactiveWidth(*barWidth);
        scrollBar.SetNormalWidth(*barWidth);
        scrollBar.SetIsUserNormalWidth(true);
    } else {
        scrollBar.SetIsUserNormalWidth(false);
    }
    const auto& barColor = property->GetScrollBarColor();
    if (barColor) {
        scrollBar.SetForegroundColor(*barColor, false);
    }
    const auto& margin = property->GetScrollBarMargin();
    if (margin && scrollBar.GetScrollBarMargin() != margin) {
        scrollBar.SetScrollBarMargin(*margin);
        scrollBar.FlushBarWidth();
    }
}
} // namespace

void ScrollBar2D::SetDisplayMode(ScrollBar& scrollBar, DisplayMode mode)
{
    if (mode == DisplayMode::OFF) {
        auto gestureHub = pattern_.GetGestureHub();
        if (gestureHub) {
            gestureHub->RemoveTouchEvent(scrollBar.GetTouchEvent());
        }
        if (painter_) {
            painter_->SetOpacity(0);
        }
        return;
    }

    const auto oldDisplayMode = scrollBar.GetDisplayMode();
    if (oldDisplayMode != mode) {
        scrollBar.SetDisplayMode(mode);
        if (painter_ && scrollBar.IsScrollable()) {
            painter_->SetOpacity(UINT8_MAX);
        }
        scrollBar.ScheduleDisappearDelayTask();
    }
}

void ScrollBar2D::Update(const std::unique_ptr<ScrollBarProperty>& props)
{
    ConfigureScrollBar(props, vertical_);
    ConfigureScrollBar(props, horizontal_);
    const auto displayMode = props->GetScrollBarMode().value_or(DisplayMode::AUTO);
    SetDisplayMode(vertical_, displayMode);
    SetDisplayMode(horizontal_, displayMode);

    vertical_.SetPositionMode(pattern_.GetPositionMode()); // considers RTL
}

ScrollBar2D::ScrollBar2D(ScrollPattern& pattern) : pattern_(pattern)
{
    vertical_.SetAxis(Axis::VERTICAL);
    horizontal_.SetAxis(Axis::HORIZONTAL);
    horizontal_.SetPositionMode(PositionMode::BOTTOM);
    vertical_.SetPositionMode(PositionMode::RIGHT);

    // init gesture events
}
} // namespace OHOS::Ace::NG