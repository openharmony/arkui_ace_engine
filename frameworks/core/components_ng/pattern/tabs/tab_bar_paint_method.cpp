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

namespace OHOS::Ace::NG {

CanvasDrawFunction TabBarPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintProperty = AceType::DynamicCast<TabBarPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, nullptr);
    if (!paintProperty->GetFadingEdge().value_or(true)) {
        return nullptr;
    }
    
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    auto frameRect = geometryNode->GetFrameRect();

    auto paintFunc = [gradientRegions = gradientRegions_, barRect = frameRect,
        backgroundColor = backgroundColor_](
                         RSCanvas& canvas) { PaintGradient(canvas, barRect, backgroundColor, gradientRegions); };
    return paintFunc;
}

void TabBarPaintMethod::PaintGradient(RSCanvas& canvas, RectF barRect,
    Color backgroundColor, std::vector<bool> gradientRegions)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    float shadowMargin = static_cast<float>(tabTheme->GetTabBarShadowMargin().ConvertToPx());
    float gradientWidth = static_cast<float>(tabTheme->GetTabBarGradientWidth().ConvertToPx());

    for (int8_t position = 0; position < POS_NUM; position++) {
        if (gradientRegions[position]) {
            switch (position) {
                case LEFT_GRADIENT:
                    PaintLeftGradient(canvas, barRect, backgroundColor, shadowMargin, gradientWidth);
                    break;
                case RIGHT_GRADIENT:
                    PaintRightGradient(canvas, barRect, backgroundColor, shadowMargin, gradientWidth);
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

void TabBarPaintMethod::PaintLeftGradient(RSCanvas& canvas, RectF barRect, Color backgroundColor, float shadowMargin,
    float gradientWidth)
{
    RSBrush leftBrush;
    RSRect rect(0.0f, 0.0f, shadowMargin + gradientWidth, barRect.Height());
    RSPoint leftStartPoint;
    leftStartPoint.SetX(shadowMargin + gradientWidth);
    leftStartPoint.SetY(0.0f);
    RSPoint leftEndPoint;
    leftEndPoint.SetX(0.0f);
    leftEndPoint.SetY(0.0f);
    Color endColor = backgroundColor;
    Color startColor = endColor.ChangeAlpha(0);
    std::vector<float> leftPos { 0.0f, gradientWidth / (shadowMargin + gradientWidth), 1.0f };
    std::vector<RSColorQuad> leftColors { startColor.GetValue(), endColor.GetValue(), endColor.GetValue() };
    leftBrush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(leftStartPoint, leftEndPoint, leftColors, leftPos, RSTileMode::CLAMP));
    canvas.DetachPen().AttachBrush(leftBrush);
    canvas.DrawRect(rect);
}

void TabBarPaintMethod::PaintRightGradient(RSCanvas& canvas, RectF barRect, Color backgroundColor, float shadowMargin,
    float gradientWidth)
{
    RSBrush rightBrush;
    RSRect rect(barRect.Width() - shadowMargin - gradientWidth,
                    0.0f, barRect.Width(), barRect.Height());
    RSPoint rightStartPoint;
    rightStartPoint.SetX(barRect.Width() - shadowMargin - gradientWidth);
    rightStartPoint.SetY(0.0f);
    RSPoint rightEndPoint;
    rightEndPoint.SetX(barRect.Width());
    rightEndPoint.SetY(0.0f);
    Color endColor = backgroundColor;
    Color startColor = endColor.ChangeAlpha(0);
    std::vector<float> rightPos { 0.0f, gradientWidth / (shadowMargin + gradientWidth), 1.0f };
    std::vector<RSColorQuad> rightColors { startColor.GetValue(), endColor.GetValue(), endColor.GetValue() };
    rightBrush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(rightStartPoint, rightEndPoint, rightColors, rightPos, RSTileMode::CLAMP));
    canvas.DetachPen().AttachBrush(rightBrush);
    canvas.DrawRect(rect);
}

void TabBarPaintMethod::PaintTopGradient(RSCanvas& canvas, RectF barRect, Color backgroundColor, float shadowMargin,
    float gradientWidth)
{
    RSBrush topBrush;
    RSRect rect(0.0f, 0.0f, barRect.Width(), shadowMargin + gradientWidth);
    RSPoint topStartPoint;
    topStartPoint.SetX(0.0f);
    topStartPoint.SetY(shadowMargin + gradientWidth);
    RSPoint topEndPoint;
    topEndPoint.SetX(0.0f);
    topEndPoint.SetY(0.0f);
    Color endColor = backgroundColor;
    Color startColor = endColor.ChangeAlpha(0);
    std::vector<float> topPos { 0.0f, gradientWidth / (shadowMargin + gradientWidth), 1.0f };
    std::vector<RSColorQuad> topColors { startColor.GetValue(), endColor.GetValue(), endColor.GetValue() };
    topBrush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(topStartPoint, topEndPoint, topColors, topPos, RSTileMode::CLAMP));
    canvas.DetachPen().AttachBrush(topBrush);
    canvas.DrawRect(rect);
}

void TabBarPaintMethod::PaintBottomGradient(RSCanvas& canvas, RectF barRect, Color backgroundColor, float shadowMargin,
    float gradientWidth)
{
    RSBrush bottomBrush;
    RSRect rect(0.0f, barRect.Height() - shadowMargin - gradientWidth,
        barRect.Width(), barRect.Height());
    RSPoint bottomStartPoint;
    bottomStartPoint.SetX(0.0f);
    bottomStartPoint.SetY(barRect.Height() - shadowMargin - gradientWidth);
    RSPoint bottomEndPoint;
    bottomEndPoint.SetX(0.0f);
    bottomEndPoint.SetY(barRect.Height());
    Color endColor = backgroundColor;
    Color startColor = endColor.ChangeAlpha(0);
    std::vector<float> bottomPos { 0.0f, gradientWidth / (shadowMargin + gradientWidth), 1.0f };
    std::vector<RSColorQuad> bottomColors { startColor.GetValue(), endColor.GetValue(), endColor.GetValue() };
    bottomBrush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(
            bottomStartPoint, bottomEndPoint, bottomColors, bottomPos, RSTileMode::CLAMP));
    canvas.DetachPen().AttachBrush(bottomBrush);
    canvas.DrawRect(rect);
}

RefPtr<Modifier> TabBarPaintMethod::GetContentModifier(PaintWrapper* paintWrapper)
{
    return tabBarModifier_;
}

void TabBarPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(tabBarModifier_);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto paintProperty = DynamicCast<TabBarPaintProperty>(paintWrapper->GetPaintProperty());
    if (paintProperty) {
        RectF rect;
        auto indicator = paintProperty->GetIndicator().value_or(rect);
        indicator.SetLeft(currentIndicatorOffset_);
        tabBarModifier_->SetIndicator(indicator);
    }
    tabBarModifier_->SetIndicatorColor(LinearColor(indicatorStyle_.color));
    tabBarModifier_->SetIndicatorHeight(indicatorStyle_.height.ConvertToPx());
    tabBarModifier_->SetIndicatorWidth(indicatorStyle_.width.ConvertToPx());
    tabBarModifier_->SetIndicatorBorderRadius(indicatorStyle_.borderRadius.ConvertToPx());
    tabBarModifier_->SetIndicatorMarginTop(indicatorStyle_.marginTop.ConvertToPx());
    tabBarModifier_->SetSelectedMode(selectedMode_);
}
} // namespace OHOS::Ace::NG
