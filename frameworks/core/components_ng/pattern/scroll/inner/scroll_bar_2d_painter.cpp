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
    // Enables use of WeakPtr captures in lambdas.
    // No need for DecRefCount in destructor since data is not dynamically allocated.
    horizontal_.IncRefCount();
    vertical_.IncRefCount();

    horizontal_.SetPositionMode(PositionMode::BOTTOM);
    vertical_.SetPositionMode(PositionMode::RIGHT);
    for (auto&& prop : horizontal_.GetAttachedProperties()) {
        AttachProperty(prop);
    }
    for (auto&& prop : vertical_.GetAttachedProperties()) {
        AttachProperty(prop);
    }
}

namespace {
void Update(ScrollBarOverlayModifier& painter, const ScrollBar& bar)
{
    painter.SetBarColor(bar.GetForegroundColor());
    painter.StartBarAnimation(
        bar.GetHoverAnimationType(), bar.GetOpacityAnimationType(), bar.GetNeedAdaptAnimation(), bar.GetActiveRect());
    painter.SetRect(bar.GetActiveRect());
    painter.SetOpacity(bar.GetDisplayMode() == DisplayMode::OFF ? 0 : UINT8_MAX);
    painter.SetScrollable(bar.IsScrollable());
}
} // namespace

void ScrollBar2DPainter::UpdateFrom(const ScrollBar2D& bar)
{
    Update(vertical_, bar.GetVerticalBar());
    vertical_.SetPositionMode(bar.GetVerticalBar().GetPositionMode());
    Update(horizontal_, bar.GetHorizontalBar());
}

void ScrollBar2DPainter::onDraw(DrawingContext& drawingContext)
{
    vertical_.onDraw(drawingContext);
    horizontal_.onDraw(drawingContext);
}
} // namespace OHOS::Ace::NG
