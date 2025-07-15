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

#include "scroll_bar_2d_painter.h"

#include "core/components_ng/pattern/scroll/inner/scroll_bar_2d.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"
namespace OHOS::Ace::NG {
ScrollBar2DPainter::ScrollBar2DPainter()
{
    CHECK_NULL_VOID(horizontal_ && vertical_);
    horizontal_->SetPositionMode(PositionMode::BOTTOM);
    vertical_->SetPositionMode(PositionMode::RIGHT);
    for (auto&& prop : horizontal_->GetAttachedProperties()) {
        AttachProperty(prop);
    }
    for (auto&& prop : vertical_->GetAttachedProperties()) {
        AttachProperty(prop);
    }
}

namespace {
void Update(ScrollBarOverlayModifier& painter, const ScrollBar& bar)
{
    if (!bar.NeedPaint()) {
        painter.SetOpacity(0);
        return;
    }
    painter.SetBarColor(bar.GetForegroundColor());
    painter.StartBarAnimation(
        bar.GetHoverAnimationType(), bar.GetOpacityAnimationType(), bar.GetNeedAdaptAnimation(), bar.GetActiveRect());
    painter.SetScrollable(bar.IsScrollable());

    switch (bar.GetDisplayMode()) {
        case DisplayMode::OFF:
            painter.SetOpacity(0);
            break;
        case DisplayMode::AUTO: // controlled by animations
            break;
        case DisplayMode::ON:
            painter.SetOpacity(UINT8_MAX);
            break;
        default:
            break;
    }
}
} // namespace

void ScrollBar2DPainter::UpdateFrom(const ScrollBar2D& bar)
{
    CHECK_NULL_VOID(vertical_ && horizontal_);
    Update(*vertical_, bar.GetVerticalBar());
    vertical_->SetPositionMode(bar.GetVerticalBar().GetPositionMode());
    Update(*horizontal_, bar.GetHorizontalBar());
}

void ScrollBar2DPainter::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(vertical_ && horizontal_);
    vertical_->onDraw(drawingContext);
    horizontal_->onDraw(drawingContext);
}
} // namespace OHOS::Ace::NG
