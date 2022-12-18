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

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/panel/drag_bar_layout_property.h"
#include "core/components_ng/pattern/panel/drag_bar_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/event/mouse_event.h"

namespace OHOS::Ace::NG {
namespace {

// For DragBar Initial State Point.
const OffsetT<Dimension> POINT_L_INITIAL = OffsetT<Dimension>(18.0_vp, 12.0_vp);
const OffsetT<Dimension> POINT_C_INITIAL = OffsetT<Dimension>(32.0_vp, 12.0_vp);
const OffsetT<Dimension> POINT_R_INITIAL = OffsetT<Dimension>(46.0_vp, 12.0_vp);
const float OPACITY = 1.0f;
const Color BAR_COLOR = Color(0xffb3b3b3);
const Dimension BAR_WIDTH = 4.0_vp;

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
    auto paintProperty = DynamicCast<DragBarPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto barLeftPoint = paintProperty->GetBarLeftPoint().value_or(POINT_L_INITIAL);
    auto barCenterPoint = paintProperty->GetBarCenterPoint().value_or(POINT_C_INITIAL);
    auto barRightPoint = paintProperty->GetBarRightPoint().value_or(POINT_R_INITIAL);
    auto dragOffset = paintProperty->GetDragOffset().value_or(OffsetF());
    auto opacity = paintProperty->GetOpacity().value_or(OPACITY);
    // paint size
    auto contentSize = paintWrapper->GetContentSize();
    auto width = contentSize.Width();
    auto height = contentSize.Height();
    // paint offset
    auto paintOffset = paintWrapper->GetContentOffset();
    RSPen pen;
    pen.SetAntiAlias(true);
    const float defaultOpacity = 0.2f;
    auto alpha_ = std::floor(UINT8_MAX * defaultOpacity);
    pen.SetAlpha(alpha_ * opacity);
    pen.SetColor(ToRSColor(BAR_COLOR));
    pen.SetWidth(BAR_WIDTH.ConvertToPx() * scaleWidth_);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(pen);

    OffsetF totalOffset = paintOffset + iconOffset_ + dragOffset;
    RSPath path;
    path.MoveTo(
        barLeftPoint.GetX().ConvertToPx() + totalOffset.GetX(), barLeftPoint.GetY().ConvertToPx() + totalOffset.GetY());
    path.LineTo(barCenterPoint.GetX().ConvertToPx() + totalOffset.GetX(),
        barCenterPoint.GetY().ConvertToPx() + totalOffset.GetY());
    path.LineTo(barRightPoint.GetX().ConvertToPx() + totalOffset.GetX(),
        barRightPoint.GetY().ConvertToPx() + totalOffset.GetY());
    if (!NearEqual(scaleIcon_, 1.0)) {
        LOGD("NearEqual scaleIcon_, 1.0 ");
        canvas.Scale(scaleIcon_, scaleIcon_);
        Size translate = Size(width, height) * ((scaleIcon_ - 1.0) / 2.0);
        canvas.Translate(-translate.Width(), -translate.Height());
    }
    canvas.DrawPath(path);
}

} // namespace OHOS::Ace::NG
