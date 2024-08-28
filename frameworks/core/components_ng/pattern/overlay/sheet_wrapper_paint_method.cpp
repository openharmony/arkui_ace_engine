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
constexpr Dimension OUTER_MARGIN = Dimension(1.0f);
constexpr float BLUR_MASK_FILTER = 0.55f;
} // namespace

void SheetWrapperPaintMethod::PaintOuterBorder(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    auto sheetNode = GetSheetNode();
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = DynamicCast<SheetPresentationPattern>(sheetNode->GetPattern());
    CHECK_NULL_VOID(sheetPattern);
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
    CHECK_EQUAL_VOID(GetOuterDrawPath(path, sheetNode), false);
    RSPen pen;
    SetOuterPenStyle(pen, sheetTheme);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.Save();
    canvas.Restore();
    canvas.DetachPen();
    path.Close();
}

RefPtr<FrameNode> SheetWrapperPaintMethod::GetSheetNode()
{
    auto pattern = DynamicCast<SheetWrapperPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, nullptr);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto sheetNode = DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_RETURN(sheetNode, nullptr);
    return sheetNode;
}

Dimension SheetWrapperPaintMethod::GetSheetOuterRadius(const SizeF& sheetSize, const Dimension& sheetRadius)
{
    float half = 0.5f;
    Dimension sheetOuterRadius;
    if (sheetSize.Width() * half < sheetRadius.ConvertToPx()) {
        sheetOuterRadius = Dimension(sheetSize.Width() * half);
    }
    sheetOuterRadius = Dimension(sheetRadius.ConvertToPx() + 1.0f);
    return sheetOuterRadius;
}

bool SheetWrapperPaintMethod::SetOuterPenStyle(RSPen& pen, const RefPtr<SheetTheme>& sheetTheme)
{
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::SOLID, BLUR_MASK_FILTER));
    pen.SetFilter(filter);
    pen.SetAntiAlias(true);
    pen.SetWidth(sheetTheme->GetSheetOuterBorderWidth().ConvertToPx());
    pen.SetColor(sheetTheme->GetSheetOuterBorderColor().GetValue());
    return true;
}

bool SheetWrapperPaintMethod::GetOuterDrawPath(RSPath& path, const RefPtr<FrameNode> sheetNode)
{
    auto sheetPattern = DynamicCast<SheetPresentationPattern>(sheetNode->GetPattern());
    CHECK_NULL_RETURN(sheetPattern, false);
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto sheetSize = geometryNode->GetFrameSize();
    auto targetOffset = sheetNode->GetPositionToParentWithTransform();
    auto pipeline = sheetNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, false);
    auto outerRadius = GetSheetOuterRadius(sheetSize, sheetTheme->GetSheetRadius());
    auto arrowOffset = sheetPattern->GetSheetArrowOffset().GetX();
    path.Reset();
    path.MoveTo(targetOffset.GetX() - OUTER_MARGIN.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + outerRadius.ConvertToPx() + targetOffset.GetY());
    path.ArcTo(outerRadius.ConvertToPx(), outerRadius.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        outerRadius.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY() - OUTER_MARGIN.ConvertToPx());
    path.LineTo(arrowOffset - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY() - OUTER_MARGIN.ConvertToPx()); // P1
    path.LineTo(
        arrowOffset - ARROW_VERTICAL_P2_OFFSET_X.ConvertToPx() + targetOffset.GetX() - OUTER_MARGIN.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P2_OFFSET_Y.ConvertToPx() + targetOffset.GetY()); // P2
    path.ArcTo(ARROW_RADIUS.ConvertToPx() + OUTER_MARGIN.ConvertToPx(),
        ARROW_RADIUS.ConvertToPx() + OUTER_MARGIN.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        arrowOffset + ARROW_VERTICAL_P4_OFFSET_X.ConvertToPx() + targetOffset.GetX() + OUTER_MARGIN.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() - ARROW_VERTICAL_P4_OFFSET_Y.ConvertToPx() + targetOffset.GetY()); // P4
    path.LineTo(arrowOffset + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY() - OUTER_MARGIN.ConvertToPx()); // P5
    path.LineTo(sheetSize.Width() - outerRadius.ConvertToPx() + targetOffset.GetX(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + targetOffset.GetY() - OUTER_MARGIN.ConvertToPx());
    path.ArcTo(outerRadius.ConvertToPx(), outerRadius.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        sheetSize.Width() + targetOffset.GetX() + OUTER_MARGIN.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + outerRadius.ConvertToPx() + targetOffset.GetY());
    path.LineTo(sheetSize.Width() + targetOffset.GetX() + OUTER_MARGIN.ConvertToPx(),
        sheetSize.Height() - outerRadius.ConvertToPx() + targetOffset.GetY());
    path.ArcTo(outerRadius.ConvertToPx(), outerRadius.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        sheetSize.Width() - outerRadius.ConvertToPx() + targetOffset.GetX(),
        sheetSize.Height() + targetOffset.GetY() + OUTER_MARGIN.ConvertToPx());
    path.LineTo(outerRadius.ConvertToPx() + targetOffset.GetX(),
        sheetSize.Height() + targetOffset.GetY() + OUTER_MARGIN.ConvertToPx());
    path.ArcTo(outerRadius.ConvertToPx(), outerRadius.ConvertToPx(), 0.0f, RSPathDirection::CW_DIRECTION,
        targetOffset.GetX() - OUTER_MARGIN.ConvertToPx(),
        sheetSize.Height() - outerRadius.ConvertToPx() + targetOffset.GetY());
    path.LineTo(targetOffset.GetX() - OUTER_MARGIN.ConvertToPx(),
        SHEET_ARROW_HEIGHT.ConvertToPx() + outerRadius.ConvertToPx() + targetOffset.GetY());
    return true;
}
} // namespace OHOS::Ace::NG
