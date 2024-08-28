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

#include "core/components_ng/pattern/overlay/sheet_presentation_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension ARROW_VERTICAL_P1_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_VERTICAL_P2_OFFSET_X = 1.5_vp;
constexpr Dimension ARROW_VERTICAL_P2_OFFSET_Y = 7.32_vp;
constexpr Dimension ARROW_VERTICAL_P4_OFFSET_X = 1.5_vp;
constexpr Dimension ARROW_VERTICAL_P4_OFFSET_Y = 7.32_vp;
constexpr Dimension ARROW_VERTICAL_P5_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_RADIUS = 2.0_vp;
constexpr float BLUR_MASK_FILTER = 0.55f;
} // namespace

void SheetPresentationPaintMethod::PaintInnerBorder(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    auto sheetPattern = DynamicCast<SheetPresentationPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto sheetType = sheetPattern->GetSheetType();
    auto pipeline = sheetNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (!sheetTheme->IsOuterBorderEnable() || sheetType != SheetType::SHEET_POPUP ||
        sheetStyle.borderWidth.has_value()) {
        return;
    }

    RSPath path;
    CHECK_EQUAL_VOID(GetInnerDrawPath(path, sheetNode), false);
    RSPen pen;
    SetInnerPenStyle(pen, sheetTheme);
    canvas.AttachPen(pen);
    canvas.Save();
    canvas.DrawPath(path);
    canvas.Restore();
    canvas.DetachPen();
    path.Close();
}

Dimension SheetPresentationPaintMethod::GetSheetInnerRadius(const SizeF& sheetSize, const Dimension& sheetRadius)
{
    float half = 0.5f;
    Dimension sheetInnerRadius;
    if (sheetSize.Width() * half < sheetRadius.ConvertToPx()) {
        sheetInnerRadius = Dimension(sheetSize.Width() * half);
    }
    sheetInnerRadius = Dimension(sheetRadius.ConvertToPx());
    return sheetInnerRadius;
}

bool SheetPresentationPaintMethod::SetInnerPenStyle(RSPen& pen, const RefPtr<SheetTheme>& sheetTheme)
{
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::SOLID, BLUR_MASK_FILTER));
    pen.SetAntiAlias(true);
    pen.SetWidth(sheetTheme->GetSheetInnerBorderWidth().ConvertToPx());
    pen.SetColor(sheetTheme->GetSheetInnerBorderColor().GetValue());
    return true;
}

bool SheetPresentationPaintMethod::GetInnerDrawPath(RSPath& path, const RefPtr<FrameNode> sheetNode)
{
    auto sheetPattern = DynamicCast<SheetPresentationPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(sheetPattern, false);
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto sheetSize = geometryNode->GetFrameSize();
    auto targetOffset = Offset();
    auto pipeline = sheetNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, false);
    auto sheetInnerRadius = GetSheetInnerRadius(sheetSize, sheetTheme->GetSheetRadius());

    path.Reset();
    path.MoveTo(
        targetOffset.GetX(), SHEET_ARROW_HEIGHT.ConvertToPx() + sheetInnerRadius.ConvertToPx() + targetOffset.GetY());
    path.ArcTo(sheetInnerRadius.ConvertToPx(), sheetInnerRadius.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        sheetInnerRadius.ConvertToPx() + targetOffset.GetX(), SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY());
    path.LineTo(
        sheetPattern->GetSheetArrowOffset().GetX() - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY()); // P1
    path.LineTo(
        sheetPattern->GetSheetArrowOffset().GetX() - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx() + targetOffset.GetY()); // P2
    path.ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        sheetPattern->GetSheetArrowOffset().GetX() + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx() + targetOffset.GetY()); // P4
    path.LineTo(
        sheetPattern->GetSheetArrowOffset().GetX() + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY()); // P5
    path.LineTo(sheetSize.Width() - sheetInnerRadius.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY());
    path.ArcTo(sheetInnerRadius.ConvertToPx(), sheetInnerRadius.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        sheetSize.Width() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + sheetInnerRadius.ConvertToPx() + targetOffset.GetY());
    path.LineTo(sheetSize.Width() + targetOffset.GetX(),
        sheetSize.Height() - sheetInnerRadius.ConvertToPx() + targetOffset.GetY());
    path.ArcTo(sheetInnerRadius.ConvertToPx(), sheetInnerRadius.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        sheetSize.Width() - sheetInnerRadius.ConvertToPx() + targetOffset.GetX(),
        sheetSize.Height() + targetOffset.GetY());
    path.LineTo(sheetInnerRadius.ConvertToPx() + targetOffset.GetX(), sheetSize.Height() + targetOffset.GetY());
    path.ArcTo(sheetInnerRadius.ConvertToPx(), sheetInnerRadius.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        targetOffset.GetX(), sheetSize.Height() - sheetInnerRadius.ConvertToPx() + targetOffset.GetY());
    path.LineTo(
        targetOffset.GetX(), SHEET_ARROW_HEIGHT.ConvertToPx() + sheetInnerRadius.ConvertToPx() + targetOffset.GetY());
    return true;
}

} // namespace OHOS::Ace::NG
