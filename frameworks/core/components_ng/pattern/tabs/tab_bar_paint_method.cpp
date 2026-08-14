/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tab_bar_paint_method.h"

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int8_t LEFT_GRADIENT = 0;
constexpr int8_t RIGHT_GRADIENT = 1;
constexpr int8_t TOP_GRADIENT = 2;
constexpr int8_t BOTTOM_GRADIENT = 3;
constexpr int8_t POS_NUM = 4;
}

CanvasDrawFunction TabBarPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintProperty = AceType::DynamicCast<TabBarPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, nullptr);
    if (!paintProperty->GetFadingEdge().value_or(true)) {
        return nullptr;
    }
    
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    MarginPropertyF padding;
    if (geometryNode->GetPadding()) {
        padding.left = geometryNode->GetPadding()->left;
        padding.right = geometryNode->GetPadding()->right;
    }

    auto paintFunc = [gradientRegions = gradientRegions_, barRect = frameRect_, backgroundColor = backgroundColor_,
                         padding](RSCanvas& canvas) {
        PaintGradient(canvas, barRect, backgroundColor, gradientRegions, padding);
    };
    return paintFunc;
}

void TabBarPaintMethod::PaintGradient(RSCanvas& canvas, const RectF& barRect, const Color& backgroundColor,
    const std::vector<bool>& gradientRegions, const MarginPropertyF& padding)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    float shadowMargin = static_cast<float>(tabTheme->GetTabBarShadowMargin().ConvertToPx());
    float gradientWidth = static_cast<float>(tabTheme->GetTabBarGradientWidth().ConvertToPx());

    auto leftPadding = padding.left.value_or(0.0f);
    auto rightPadding = padding.right.value_or(0.0f);

    for (int8_t position = 0; position < POS_NUM; position++) {
        if (gradientRegions[position]) {
            switch (position) {
                case LEFT_GRADIENT:
                    PaintLeftGradient(canvas, barRect, backgroundColor, shadowMargin, gradientWidth, leftPadding);
                    break;
                case RIGHT_GRADIENT:
                    PaintRightGradient(canvas, barRect, backgroundColor, shadowMargin, gradientWidth, rightPadding);
                    break;
                case TOP_GRADIENT:
                    PaintTopGradient(canvas, barRect, backgroundColor, shadowMargin, gradientWidth);
                    break;
                case BOTTOM_GRADIENT:
                    PaintBottomGradient(canvas, barRect, backgroundColor, shadowMargin, gradientWidth);
                    break;
                default:
                    break;
            }
        }
    }
}

void TabBarPaintMethod::PaintLeftGradient(RSCanvas& canvas, const RectF& barRect, const Color& backgroundColor,
    float shadowMargin, float gradientWidth, float padding)
{
    RSRect gradientRect(0.0f, 0.0f, padding + shadowMargin + gradientWidth, barRect.Height());
    RSPoint leftStartPoint;
    leftStartPoint.SetX(shadowMargin + gradientWidth + padding);
    leftStartPoint.SetY(0.0f);
    RSPoint leftEndPoint;
    leftEndPoint.SetX(0.0f);
    leftEndPoint.SetY(0.0f);
    PaintGradientRect(
        canvas, gradientRect, backgroundColor, leftStartPoint, leftEndPoint, padding + shadowMargin, gradientWidth);
}

void TabBarPaintMethod::PaintRightGradient(RSCanvas& canvas, const RectF& barRect, const Color& backgroundColor,
    float shadowMargin, float gradientWidth, float padding)
{
    RSRect gradientRect(
        barRect.Width() - shadowMargin - gradientWidth - padding, 0.0f, barRect.Width(), barRect.Height());
    RSPoint rightStartPoint;
    rightStartPoint.SetX(barRect.Width() - shadowMargin - gradientWidth - padding);
    rightStartPoint.SetY(0.0f);
    RSPoint rightEndPoint;
    rightEndPoint.SetX(barRect.Width());
    rightEndPoint.SetY(0.0f);
    PaintGradientRect(
        canvas, gradientRect, backgroundColor, rightStartPoint, rightEndPoint, shadowMargin + padding, gradientWidth);
}

void TabBarPaintMethod::PaintTopGradient(RSCanvas& canvas, const RectF& barRect, const Color& backgroundColor,
    float shadowMargin, float gradientWidth)
{
    RSRect gradientRect(0.0f, 0.0f, barRect.Width(), shadowMargin + gradientWidth);
    RSPoint topStartPoint;
    topStartPoint.SetX(0.0f);
    topStartPoint.SetY(shadowMargin + gradientWidth);
    RSPoint topEndPoint;
    topEndPoint.SetX(0.0f);
    topEndPoint.SetY(0.0f);
    PaintGradientRect(canvas, gradientRect, backgroundColor, topStartPoint, topEndPoint, shadowMargin,
        gradientWidth);
}

void TabBarPaintMethod::PaintBottomGradient(RSCanvas& canvas, const RectF& barRect, const Color& backgroundColor,
    float shadowMargin, float gradientWidth)
{
    RSRect gradientRect(0.0f, barRect.Height() - shadowMargin - gradientWidth,
        barRect.Width(), barRect.Height());
    RSPoint bottomStartPoint;
    bottomStartPoint.SetX(0.0f);
    bottomStartPoint.SetY(barRect.Height() - shadowMargin - gradientWidth);
    RSPoint bottomEndPoint;
    bottomEndPoint.SetX(0.0f);
    bottomEndPoint.SetY(barRect.Height());
    PaintGradientRect(canvas, gradientRect, backgroundColor, bottomStartPoint, bottomEndPoint, shadowMargin,
        gradientWidth);
}

void TabBarPaintMethod::PaintGradientRect(RSCanvas& canvas, const RSRect& gradientRect, const Color& backgroundColor,
    const RSPoint& startPoint, const RSPoint& endPoint, float shadowMargin, float gradientWidth)
{
    RSBrush brush;
    Color endColor = backgroundColor;
    Color startColor = endColor.ChangeAlpha(0);
    std::vector<float> gradientPos { 0.0f, gradientWidth / (shadowMargin + gradientWidth), 1.0f };
    std::vector<RSColorQuad> gradientColors { startColor.GetValue(), endColor.GetValue(), endColor.GetValue() };
    brush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(
            startPoint, endPoint, gradientColors, gradientPos, RSTileMode::CLAMP));
    canvas.DetachPen().AttachBrush(brush);
    canvas.DrawRect(gradientRect);
    canvas.DetachBrush();
}

RefPtr<Modifier> TabBarPaintMethod::GetContentModifier(PaintWrapper* paintWrapper)
{
    return tabBarModifier_;
}

void TabBarPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(tabBarModifier_);
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);

    tabBarModifier_->SetIndicatorOffset(indicatorOffset_);
    tabBarModifier_->SetIndicatorColor(LinearColor(indicatorStyle_.color));
    tabBarModifier_->SetIndicatorHeight(indicatorStyle_.height.ConvertToPx());
    tabBarModifier_->SetIndicatorWidth(indicatorStyle_.width.ConvertToPx());
    tabBarModifier_->SetIndicatorBorderRadius(indicatorStyle_.borderRadius.ConvertToPx());
    tabBarModifier_->SetIndicatorMarginTop(indicatorStyle_.marginTop.ConvertToPx());
    tabBarModifier_->SetHasIndicator(hasIndicator_);
}
} // namespace OHOS::Ace::NG
