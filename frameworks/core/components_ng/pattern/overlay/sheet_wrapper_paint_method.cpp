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

#include "core/components_ng/pattern/overlay/sheet_wrapper_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paint_wrapper.h"
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

void SheetWrapperPaintMethod::PaintOuterBorder(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    CHECK_EQUAL_VOID(IsDrawBorder(paintWrapper), false);
    auto sheetNode = GetSheetNode(paintWrapper);
    CHECK_NULL_VOID(sheetNode);
    auto pipeline = sheetNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    RSPath path;
    auto outerBorderWidth = sheetTheme->GetSheetOuterBorderWidth().ConvertToPx();
    GetBorderDrawPath(path, sheetNode, sheetTheme, outerBorderWidth);
    RSPen pen;
    SetBorderPenStyle(pen, sheetTheme->GetSheetOuterBorderWidth(), sheetTheme->GetSheetOuterBorderColor());
    canvas.Save();
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();
    path.Close();
}

RefPtr<FrameNode> SheetWrapperPaintMethod::GetSheetNode(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(paintWrapper, nullptr);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto host = renderContext->GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto sheetNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(sheetNode, nullptr);
    return sheetNode;
}

Dimension SheetWrapperPaintMethod::GetSheetRadius(const SizeF& sheetSize, const Dimension& radius)
{
    float half = 0.5f;
    auto sheetRadius = radius;
    if (GreatNotEqual(radius.ConvertToPx(), sheetSize.Width() * half)) {
        sheetRadius = Dimension(sheetSize.Width() * half);
    }
    return sheetRadius;
}

void SheetWrapperPaintMethod::GetBorderDrawPath(
    RSPath& path, const RefPtr<FrameNode> sheetNode, const RefPtr<SheetTheme>& sheetTheme, float borderWidth)
{
    auto sheetPattern = DynamicCast<SheetPresentationPattern>(sheetNode->GetPattern());
    CHECK_NULL_VOID(sheetPattern);
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetSize = geometryNode->GetFrameSize();
    auto targetOffset = sheetNode->GetPositionToParentWithTransform();
    auto sheetRadius = GetSheetRadius(sheetSize, sheetTheme->GetSheetRadius()).ConvertToPx();
    auto borderRadius = sheetRadius + borderWidth * 0.5f;
    auto borderOffset = borderWidth * 0.5f;
    auto arrowOffset = sheetPattern->GetSheetArrowOffset().GetX();
    path.Reset();
    path.MoveTo(
        targetOffset.GetX() - borderOffset, SHEET_ARROW_HEIGHT.ConvertToPx() + sheetRadius + targetOffset.GetY());
    path.ArcTo(borderRadius, borderRadius, 0.0f, RSPathDirection::CW_DIRECTION, sheetRadius + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY() - borderOffset);
    path.LineTo(arrowOffset - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY() - borderOffset); // P1
    path.LineTo(arrowOffset - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx() + targetOffset.GetX() - borderOffset,
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx() + targetOffset.GetY()); // P2
    path.ArcTo(ARROW_RADIUS.ConvertToPx() + borderOffset, ARROW_RADIUS.ConvertToPx() + borderOffset, 0.0f,
        RSPathDirection::CW_DIRECTION,
        arrowOffset + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx() + targetOffset.GetX() + borderOffset,
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx() + targetOffset.GetY()); // P4
    path.LineTo(arrowOffset + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY() - borderOffset); // P5
    path.LineTo(sheetSize.Width() - sheetRadius + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY() - borderOffset);
    path.ArcTo(borderRadius, borderRadius, 0.0f, RSPathDirection::CW_DIRECTION,
        sheetSize.Width() + targetOffset.GetX() + borderOffset,
        SHEET_ARROW_HEIGHT.ConvertToPx() + sheetRadius + targetOffset.GetY());
    path.LineTo(
        sheetSize.Width() + targetOffset.GetX() + borderOffset, sheetSize.Height() - sheetRadius + targetOffset.GetY());
    path.ArcTo(borderRadius, borderRadius, 0.0f, RSPathDirection::CW_DIRECTION,
        sheetSize.Width() - sheetRadius + targetOffset.GetX(), sheetSize.Height() + targetOffset.GetY() + borderOffset);
    path.LineTo(sheetRadius + targetOffset.GetX(), sheetSize.Height() + targetOffset.GetY() + borderOffset);
    path.ArcTo(borderRadius, borderRadius, 0.0f, RSPathDirection::CW_DIRECTION, targetOffset.GetX() - borderOffset,
        sheetSize.Height() - sheetRadius + targetOffset.GetY());
    path.LineTo(
        targetOffset.GetX() - borderOffset, SHEET_ARROW_HEIGHT.ConvertToPx() + sheetRadius + targetOffset.GetY());
}

void SheetWrapperPaintMethod::PaintInnerBorder(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    CHECK_EQUAL_VOID(IsDrawBorder(paintWrapper), false);
    auto sheetNode = GetSheetNode(paintWrapper);
    CHECK_NULL_VOID(sheetNode);
    auto pipeline = sheetNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    RSPath path;
    auto innerBorderWidth = -(sheetTheme->GetSheetInnerBorderWidth().ConvertToPx());
    GetBorderDrawPath(path, sheetNode, sheetTheme, innerBorderWidth);
    RSPen pen;
    SetBorderPenStyle(pen, sheetTheme->GetSheetInnerBorderWidth(), sheetTheme->GetSheetInnerBorderColor());
    canvas.Save();
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();
    path.Close();
}

void SheetWrapperPaintMethod::SetBorderPenStyle(RSPen& pen, const Dimension& borderWidth, const Color& borderColor)
{
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::SOLID, BLUR_MASK_FILTER));
    pen.SetFilter(filter);
    pen.SetAntiAlias(true);
    pen.SetWidth(borderWidth.ConvertToPx());
    pen.SetColor(borderColor.GetValue());
}

bool SheetWrapperPaintMethod::IsDrawBorder(PaintWrapper* paintWrapper)
{
    auto sheetNode = GetSheetNode(paintWrapper);
    CHECK_NULL_RETURN(sheetNode, false);
    auto sheetPattern = DynamicCast<SheetPresentationPattern>(sheetNode->GetPattern());
    CHECK_NULL_RETURN(sheetPattern, false);
    auto sheetType = sheetPattern->GetSheetType();
    auto pipeline = sheetNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, false);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (sheetTheme->IsOuterBorderEnable() && sheetType == SheetType::SHEET_POPUP &&
        !sheetStyle.borderWidth.has_value()) {
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
