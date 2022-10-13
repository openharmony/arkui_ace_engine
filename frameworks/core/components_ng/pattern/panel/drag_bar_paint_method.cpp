/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/panel/drag_bar_paint_method.h"

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/panel/drag_bar_layout_property.h"
#include "core/components_ng/pattern/panel/drag_bar_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {

// For DragBar Shrink State Point.
const Offset POINT_L_SHRINK = Offset(17.0, 15.0);
const Offset POINT_C_SHRINK = Offset(32.0, 9.0);
const Offset POINT_R_SHRINK = Offset(47.0, 15.0);

// For DragBar Initial State Point.
const Offset POINT_L_INITIAL = Offset(18.0, 12.0);
const Offset POINT_C_INITIAL = Offset(32.0, 12.0);
const Offset POINT_R_INITIAL = Offset(46.0, 12.0);

// For DragBar Expand State Point.
const Offset POINT_L_EXPAND = Offset(17.0, 9.0);
const Offset POINT_C_EXPAND = Offset(32.0, 15.0);
const Offset POINT_R_EXPAND = Offset(47.0, 9.0);

const Color BAR_COLOR = Color(0xffb3b3b3);

} // namespace

CanvasDrawFunction DragBarPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(paintWrapper, nullptr);
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto dragBar = weak.Upgrade();
        if (dragBar) {
            dragBar->Paint(canvas, paintWrapper);
        }
    };
    return paintFunc;
}

void DragBarPaintMethod::Paint(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    CHECK_NULL_VOID(paintWrapper);
    if (NearZero(opacity_)) {
        return;
    }

    auto contentSize = paintWrapper->GetContentSize();
    auto width = contentSize.Width();
    auto height = contentSize.Height();
    auto paintOffset = paintWrapper->GetContentOffset();
    auto xOffset = paintOffset.GetX();
    auto yOffset = paintOffset.GetY();
    RSPen pen;
    pen.SetWidth(barWidth_);
    pen.SetAntiAlias(true);
    pen.SetColor(ToRSColor(BAR_COLOR));
    canvas.AttachPen(pen);
    OffsetF totalOffset = OffsetF(xOffset, yOffset) + iconOffset_ + dragOffset_;

    RSPath path;
    path.MoveTo(
        POINT_L_INITIAL.GetX() * scaleX_ + totalOffset.GetX(), POINT_L_INITIAL.GetY() * scaleY_ + totalOffset.GetY());
    path.LineTo(
        POINT_C_INITIAL.GetX() * scaleX_ + totalOffset.GetX(), POINT_C_INITIAL.GetY() * scaleY_ + totalOffset.GetY());
    path.LineTo(
        POINT_R_INITIAL.GetX() * scaleX_ + totalOffset.GetX(), POINT_R_INITIAL.GetY() * scaleY_ + totalOffset.GetY());
    if (!NearEqual(scaleIcon_, 1.0)) {
        canvas.Scale(scaleIcon_, scaleIcon_);
        Size translate = Size(width, height) * ((scaleIcon_ - 1.0) / 2.0);
        canvas.Translate(-translate.Width(), -translate.Height());
    }
    canvas.DrawPath(path);
}

} // namespace OHOS::Ace::NG
