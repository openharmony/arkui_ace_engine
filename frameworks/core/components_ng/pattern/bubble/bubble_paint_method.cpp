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
#include "core/components_ng/pattern/bubble/bubble_paint_method.h"

#include "base/geometry/ng/rect_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension BEZIER_WIDTH_HALF = 16.0_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FIRST = 1.3_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_SECOND = 3.2_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_THIRD = 6.6_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FOURTH = 16.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_FIRST = 0.1_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_SECOND = 3.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_THIRD = 8.0_vp;
constexpr Dimension ARROW_WIDTH = 32.0_vp;
constexpr Dimension ARROW_ZERO_PERCENT_VALUE = Dimension(0.0, DimensionUnit::PERCENT);
constexpr Dimension ARROW_HALF_PERCENT_VALUE = Dimension(0.5, DimensionUnit::PERCENT);
constexpr Dimension ARROW_ONE_HUNDRED_PERCENT_VALUE = Dimension(1.0, DimensionUnit::PERCENT);
constexpr float BLUR_MASK_FILTER = 0.55f;

constexpr double HALF = 2.0;
constexpr Dimension ARROW_RADIUS = 2.0_vp;
Dimension BUBBLE_ARROW_WIDTH = 16.0_vp;
Dimension BUBBLE_ARROW_HEIGHT = 10.0_vp;
constexpr int16_t P1INDEX = 0;
constexpr int16_t P2INDEX = 1;
constexpr int16_t P3INDEX = 2;
constexpr int16_t P4INDEX = 3;
} // namespace

float ModifyBorderRadius(float borderRadius, float halfChildHeight)
{
    return GreatOrEqual(borderRadius, halfChildHeight) ? halfChildHeight : borderRadius;
}

RefPtr<PipelineContext> BubbleGetPiplineContext(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(paintWrapper, nullptr);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto host = renderContext->GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    return pipelineContext;
}
void BubblePaintMethod::PaintMask(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintProperty = DynamicCast<BubbleRenderProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto host = renderContext->GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    auto maskColor = paintProperty->GetMaskColor().value_or(popupTheme->GetMaskColor());
    auto layoutSize = paintWrapper->GetContentSize();
    canvas.Save();
    RSBrush brush;
    brush.SetColor(maskColor.GetValue());
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawRect(RSRect(0.0, 0.0, layoutSize.Width(), layoutSize.Height()));
    canvas.DetachBrush();
    canvas.Restore();
}

void BubblePaintMethod::PaintBorder(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    BorderEdge edge = border_.Left();
    if (!border_.IsAllEqual()) {
        edge = border_.GetValidEdge();
        border_ = Border(edge);
    }
    if (!border_.HasValue()) {
        return;
    }
    float borderWidth = edge.GetWidth().ConvertToPx();
    RSPen paint;
    paint.SetWidth(borderWidth);
    paint.SetColor(edge.GetColor().GetValue());
    paint.SetAntiAlias(true);
    if (edge.GetBorderStyle() == BorderStyle::DOTTED) {
#ifndef USE_ROSEN_DRAWING
        RSPath dotPath;
        dotPath.AddCircle(0.0f, 0.0f, borderWidth / 2.0);
        paint.SetPathEffect(
            RSPathEffect::CreatePathDashEffect(dotPath, borderWidth * 2.0, 0.0, RSPathDashStyle::ROTATE));
#else
        RSRecordingPath dotPath;
        dotPath.AddCircle(0.0f, 0.0f, borderWidth / 2.0);
        paint.SetPathEffect(
            RSRecordingPathEffect::CreatePathDashEffect(dotPath, borderWidth * 2.0, 0.0, RSPathDashStyle::ROTATE));
#endif
    } else if (edge.GetBorderStyle() == BorderStyle::DASHED) {
#ifndef USE_ROSEN_DRAWING
        const float intervals[] = { borderWidth, borderWidth };
        paint.SetPathEffect(RSPathEffect::CreateDashPathEffect(intervals, 2, 0.0));
#else
        const RSScalar intervals[] = { borderWidth, borderWidth };
        paint.SetPathEffect(RSRecordingPathEffect::CreateDashPathEffect(intervals, 2, 0.0));
#endif
        DrawDashedBorder(canvas, paint);
    } else {
        paint.SetPathEffect(nullptr);
    }
    canvas.Save();
    canvas.Translate(childOffset_.GetX() + childSize_.Width() / 2.0, childOffset_.GetY() + childSize_.Height() / 2.0);
    canvas.Scale(1.0 - (borderWidth / childSize_.Width()), 1.0 - (borderWidth / childSize_.Height()));
    canvas.Translate(
        -(childOffset_.GetX() + childSize_.Width() / 2.0), -(childOffset_.GetY() + childSize_.Height() / 2.0));
    canvas.AttachPen(paint);
    auto rect = MakeRRect();
    canvas.DrawRoundRect(rect);
    canvas.DetachPen();
    canvas.Restore();
}

void BubblePaintMethod::DrawDashedBorder(RSCanvas& canvas, RSPen& paint)
{
    canvas.AttachPen(paint);
    canvas.DrawPath(path_);
    canvas.DetachPen();
}

void BubblePaintMethod::PaintBubble(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    isPaintBubble_ = true;
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<BubbleRenderProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    useCustom_ = paintProperty->GetUseCustom().value_or(false);
    enableArrow_ = paintProperty->GetEnableArrow().value_or(true);
    arrowPlacement_ = paintProperty->GetPlacement().value_or(Placement::BOTTOM);
    UpdateArrowOffset(paintProperty->GetArrowOffset(), arrowPlacement_);
    auto pipelineContext = BubbleGetPiplineContext(paintWrapper);
    CHECK_NULL_VOID(pipelineContext);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    backgroundColor_ = paintProperty->GetBackgroundColor().value_or(popupTheme->GetBackgroundColor());
    border_.SetBorderRadius(popupTheme->GetRadius());
    padding_ = popupTheme->GetPadding();
    RSPen paint;
    paint.SetColor(backgroundColor_.GetValue());
    paint.SetAntiAlias(true);
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::SOLID, BLUR_MASK_FILTER));
    paint.SetFilter(filter);
    // TODO: color is not correct
    RSBrush brush;
    brush.SetColor(static_cast<int>(backgroundColor_.GetValue()));
    brush.SetAntiAlias(true);
    brush.SetFilter(filter);
    canvas.AttachPen(paint);
    canvas.AttachBrush(brush);
    if (enableArrow_ && showArrow_) {
        if (popupTheme->GetPopupDoubleBorderEnable()) {
            canvas.DetachPen();
            paint.SetWidth(outerBorderWidth_);
            paint.SetColor(popupTheme->GetPopupOuterBorderColor().GetValue());
            canvas.AttachPen(paint);
        }
        PaintBubbleWithArrow(canvas, paintWrapper);
    } else {
        PaintDefaultBubble(canvas);
    }
    canvas.DetachBrush();
    canvas.DetachPen();
    if (enableArrow_ && showArrow_ && popupTheme->GetPopupDoubleBorderEnable()) {
        paint.SetWidth(innerBorderWidth_);
        paint.SetColor(popupTheme->GetPopupInnerBorderColor().GetValue());
        canvas.AttachPen(paint);
        needPaintOuterBorder_ = true;
        PaintBubbleWithArrow(canvas, paintWrapper);
        needPaintOuterBorder_ = false;
        canvas.DetachPen();
    }
}

bool BubblePaintMethod::IsPaintDoubleBorder(PaintWrapper* paintWrapper)
{
    BUBBLE_ARROW_WIDTH = Dimension(arrowWidth_);
    BUBBLE_ARROW_HEIGHT = Dimension(arrowHeight_);
    if (!OHOS::Ace::Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) || isPaintBubble_) {
        return false;
    }
    CHECK_NULL_RETURN(paintWrapper, false);
    auto paintProperty = DynamicCast<BubbleRenderProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, false);
    isTips_ = paintProperty->GetIsTips().value_or(false);
    enableArrow_ = paintProperty->GetEnableArrow().value_or(true);
    arrowPlacement_ = paintProperty->GetPlacement().value_or(Placement::BOTTOM);
    if (!enableArrow_ || !showArrow_) {
        arrowBuildPlacement_ = Placement::NONE;
        arrowPlacement_ = Placement::NONE;
    }
    UpdateArrowOffset(paintProperty->GetArrowOffset(), arrowPlacement_);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto host = renderContext->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, false);
    padding_ = isTips_ ? popupTheme->GetTipsPadding() : popupTheme->GetPadding();
    if (isTips_) {
        return enableArrow_ && showArrow_ && popupTheme->GetTipsDoubleBorderEnable();
    }
    return popupTheme->GetPopupDoubleBorderEnable() && childSize_.IsPositive();
}

void BubblePaintMethod::PaintSingleBorder(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    float borderWidth = popupTheme->GetBorderWidth().ConvertToPx();
    if (GreatNotEqual(static_cast<double>(borderWidth), 0.0)) {
        IsPaintDoubleBorder(paintWrapper);
        RSPen pen;
        pen.SetAntiAlias(true);
        pen.SetWidth(borderWidth);
        pen.SetColor(popupTheme->GetBorderColor().GetValue());
        canvas.AttachPen(pen);
        PaintDoubleBorderWithArrow(canvas, paintWrapper);
        canvas.DetachPen();
    }
}

void BubblePaintMethod::PaintOuterBorderGradient(RSPen& paint)
{
    auto halfWidth = childSize_.Width() / 2;
    RSPoint startPoint(childOffset_.GetX() + halfWidth, childOffset_.GetY());
    RSPoint endPoint(childOffset_.GetX() + halfWidth, childOffset_.GetY() + childSize_.Height());
    int popupOuterBorderDirectionInt = static_cast<int>(outlineLinearGradient_.popupDirection);
    std::vector<RSPoint> points = BorderLinearGradientPoint(popupOuterBorderDirectionInt);
    startPoint = points[0];
    endPoint = points[1];
    std::vector<uint32_t> colorQuads;
    std::vector<float> positions;
    std::pair<std::vector<uint32_t>, std::vector<float>> colors =
        BorderLinearGradientColors(outlineLinearGradient_.gradientColors);
    colorQuads = colors.first;
    positions = colors.second;
    std::shared_ptr<RSShaderEffect> shader = RSShaderEffect::CreateLinearGradient(startPoint,
        endPoint, colorQuads, positions, RSTileMode::CLAMP);
    paint.SetShaderEffect(shader);
}

void BubblePaintMethod::PaintOuterBorder(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    if (!IsPaintDoubleBorder(paintWrapper) && outlineLinearGradient_.gradientColors.empty()) {
        return;
    }
    auto paintProperty = DynamicCast<BubbleRenderProperty>(paintWrapper->GetPaintProperty());
    isTips_ = paintProperty->GetIsTips().value_or(false);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto host = renderContext->GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    RSPen paint;
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::SOLID, BLUR_MASK_FILTER));
    paint.SetFilter(filter);
    paint.SetAntiAlias(true);
    if (!outlineLinearGradient_.gradientColors.empty()) {
        if (outerBorderWidthByUser_ == 0) {
            return;
        }
        paint.SetWidth(outerBorderWidthByUser_);
        PaintOuterBorderGradient(paint);
    } else if (isTips_) {
        paint.SetWidth(popupTheme->GetTipsOuterBorderWidth().ConvertToPx());
        paint.SetColor(popupTheme->GetTipsOuterBorderColor().GetValue());
    } else {
        paint.SetWidth(outerBorderWidth_);
        paint.SetColor(popupTheme->GetPopupOuterBorderColor().GetValue());
    }
    canvas.AttachPen(paint);
    needPaintOuterBorder_ = true;
    PaintDoubleBorderWithArrow(canvas, paintWrapper);
    canvas.DetachPen();
    needPaintOuterBorder_ = false;
}

void BubblePaintMethod::PaintInnerBorderGradient(RSPen& paint)
{
    auto halfWidth = childSize_.Width() / 2;
    RSPoint startPoint(childOffset_.GetX() + halfWidth, childOffset_.GetY());
    RSPoint endPoint(childOffset_.GetX() + halfWidth, childOffset_.GetY() + childSize_.Height());
    int popupInnerBorderDirectionInt = static_cast<int>(innerBorderLinearGradient_.popupDirection);
    std::vector<RSPoint> points = BorderLinearGradientPoint(popupInnerBorderDirectionInt);
    startPoint = points[0];
    endPoint = points[1];
    std::vector<uint32_t> colorQuads;
    std::vector<float> positions;
    std::pair<std::vector<uint32_t>, std::vector<float>> colors =
        BorderLinearGradientColors(innerBorderLinearGradient_.gradientColors);
    colorQuads = colors.first;
    positions = colors.second;
    std::shared_ptr<RSShaderEffect> shader = RSShaderEffect::CreateLinearGradient(startPoint,
        endPoint, colorQuads, positions, RSTileMode::CLAMP);
    paint.SetShaderEffect(shader);
}

void BubblePaintMethod::PaintInnerBorder(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    if (!IsPaintDoubleBorder(paintWrapper) && innerBorderLinearGradient_.gradientColors.empty()) {
        return;
    }
    auto paintProperty = DynamicCast<BubbleRenderProperty>(paintWrapper->GetPaintProperty());
    isTips_ = paintProperty->GetIsTips().value_or(false);
    CHECK_NULL_VOID(paintWrapper);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto host = renderContext->GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    RSPen paint;
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::SOLID, BLUR_MASK_FILTER));
    paint.SetFilter(filter);
    paint.SetAntiAlias(true);
    if (!innerBorderLinearGradient_.gradientColors.empty()) {
        if (innerBorderWidthByUser_ == 0) {
            return;
        }
        paint.SetWidth(innerBorderWidthByUser_);
        PaintInnerBorderGradient(paint);
    } else if (isTips_) {
        paint.SetWidth(popupTheme->GetTipsInnerBorderWidth().ConvertToPx());
        paint.SetColor(popupTheme->GetTipsInnerBorderColor().GetValue());
    } else {
        paint.SetWidth(innerBorderWidth_);
        paint.SetColor(popupTheme->GetPopupInnerBorderColor().GetValue());
    }
    canvas.AttachPen(paint);
    PaintDoubleBorderWithArrow(canvas, paintWrapper);
    canvas.DetachPen();
}

std::pair<std::vector<uint32_t>, std::vector<float>> BubblePaintMethod::BorderLinearGradientColors(
    std::vector<PopupGradientColor> popupBorderGradientColor)
{
    std::vector<uint32_t> colorQuads;
    std::vector<float> positions;
    if (!popupBorderGradientColor.empty()) {
        for (auto it = popupBorderGradientColor.begin(); it != popupBorderGradientColor.end(); ++it) {
            auto colorItem = it->gradientColor;
            auto numberItem = it->gradientNumber;
            colorQuads.push_back(colorItem.GetValue());
            positions.push_back(static_cast<float>(numberItem));
        }
    }
    return std::make_pair(colorQuads, positions);
}

std::vector<RSPoint> CalculateGradientPoints(GradientDirection direction,
    float topLeftX, float topLeftY, float width, float height)
{
    auto halfWidth = width / 2;
    auto halfHeight = height / 2;
    RSPoint startPoint(topLeftX + halfWidth, topLeftY);
    RSPoint endPoint(topLeftX + halfWidth, topLeftY + height);
    switch (direction) {
        case GradientDirection::LEFT:
            startPoint = RSPoint(topLeftX + width, topLeftY + halfHeight);
            endPoint = RSPoint(topLeftX, topLeftY + halfHeight);
            break;
        case GradientDirection::TOP:
            startPoint = RSPoint(topLeftX + halfWidth, topLeftY + height);
            endPoint = RSPoint(topLeftX + halfWidth, topLeftY);
            break;
        case GradientDirection::RIGHT:
            startPoint = RSPoint(topLeftX, topLeftY + halfHeight);
            endPoint = RSPoint(topLeftX + width, topLeftY + halfHeight);
            break;
        case GradientDirection::BOTTOM:
        case GradientDirection::NONE:
            startPoint = RSPoint(topLeftX + halfWidth, topLeftY);
            endPoint = RSPoint(topLeftX + halfWidth, topLeftY + height);
            break;
        case GradientDirection::LEFT_TOP:
            startPoint = RSPoint(topLeftX + width, topLeftY + height);
            endPoint = RSPoint(0, 0);
            break;
        case GradientDirection::LEFT_BOTTOM:
            startPoint = RSPoint(topLeftX + width, topLeftY);
            endPoint = RSPoint(topLeftX, topLeftY + height);
            break;
        case GradientDirection::RIGHT_TOP:
            startPoint = RSPoint(topLeftX, topLeftY + height);
            endPoint = RSPoint(topLeftX + width, topLeftY);
            break;
        case GradientDirection::RIGHT_BOTTOM:
            startPoint = RSPoint(topLeftX, topLeftY);
            endPoint = RSPoint(topLeftX + width, topLeftY + height);
            break;
        default:
            break;
    }
    return std::vector<RSPoint>{startPoint, endPoint};
}

std::vector<RSPoint> BubblePaintMethod::BorderLinearGradientPoint(int popupInnerBorderDirectionInt)
{
    GradientDirection direction = static_cast<GradientDirection>(popupInnerBorderDirectionInt);
    auto topLeftX = childOffset_.GetX();
    auto topLeftY = childOffset_.GetY();
    auto width = childSize_.Width();
    auto height = childSize_.Height();
    std::vector<RSPoint> points = CalculateGradientPoints(direction, topLeftX,
        topLeftY, width, height);
    return points;
}

void BubblePaintMethod::ClipBubble(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto host = renderContext->GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = DynamicCast<BubbleRenderProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    enableArrow_ = paintProperty->GetEnableArrow().value_or(true);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    if (clipFrameNode_) {
        ClipBubbleWithPath(clipFrameNode_);
    }
}

void BubblePaintMethod::UpdateArrowOffset(const std::optional<Dimension>& offset, const Placement& placement)
{
    if (offset.has_value()) {
        arrowOffset_ = offset.value();
        if (arrowOffset_.Unit() == DimensionUnit::PERCENT) {
            arrowOffset_.SetValue(std::clamp(arrowOffset_.Value(), 0.0, 1.0));
        }
        return;
    }
    switch (placement) {
        case Placement::LEFT:
        case Placement::RIGHT:
        case Placement::TOP:
        case Placement::BOTTOM:
            arrowOffset_ = ARROW_HALF_PERCENT_VALUE;
            break;
        case Placement::TOP_LEFT:
        case Placement::BOTTOM_LEFT:
        case Placement::LEFT_TOP:
        case Placement::RIGHT_TOP:
            arrowOffset_ = ARROW_ZERO_PERCENT_VALUE;
            break;
        case Placement::TOP_RIGHT:
        case Placement::BOTTOM_RIGHT:
        case Placement::LEFT_BOTTOM:
        case Placement::RIGHT_BOTTOM:
            arrowOffset_ = ARROW_ONE_HUNDRED_PERCENT_VALUE;
            break;
        default:
            break;
    }
}

void BubblePaintMethod::PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas)
{
    canvas.Save();
#ifndef USE_ROSEN_DRAWING
    RSPath rsPath = path;
#else
    RSRecordingPath rsPath;
    rsPath.AddPath(path);
#endif
    rsPath.Offset(shadow.GetOffset().GetX(), shadow.GetOffset().GetY());
    RSColor spotColor = ToRSColor(shadow.GetColor());
    RSPoint3 planeParams = { 0.0f, 0.0f, shadow.GetElevation() };
#ifndef USE_ROSEN_DRAWING
    RSPoint3 lightPos = { rsPath.GetBounds().GetLeft() / 2.0 + rsPath.GetBounds().GetRight() / 2.0,
        rsPath.GetBounds().GetTop() / 2.0 + rsPath.GetBounds().GetBottom() / 2.0, shadow.GetLightHeight() };
#else
    auto bounds = rsPath.GetBounds();
    RSPoint3 lightPos = { bounds.GetLeft() / 2.0 + bounds.GetRight() / 2.0,
        bounds.GetTop() / 2.0 + bounds.GetBottom() / 2.0, shadow.GetLightHeight() };
#endif
    RSColor ambientColor = RSColor(0, 0, 0, 0);
    canvas.DrawShadow(rsPath, planeParams, lightPos, shadow.GetLightRadius(), ambientColor, spotColor,
        RSShadowFlags::TRANSPARENT_OCCLUDER);
    canvas.Restore();
}

void BubblePaintMethod::PaintDefaultBubble(RSCanvas& canvas)
{
    auto rect = MakeRRect();
    path_.AddRoundRect(
        rect.GetRect(), border_.TopLeftRadius().GetX().ConvertToPx(), border_.TopRightRadius().GetX().ConvertToPx());
    canvas.Save();
    canvas.ClipPath(path_, RSClipOp::DIFFERENCE, true);
    PaintShadow(path_, ShadowConfig::DefaultShadowM, canvas);
    canvas.Restore();
    canvas.DrawRoundRect(rect);
}

RSRoundRect BubblePaintMethod::MakeRRect()
{
    auto rect = RSRect(childOffset_.GetX(), childOffset_.GetY(), childOffset_.GetX() + childSize_.Width(),
        childOffset_.GetY() + childSize_.Height());
    std::vector<RSPoint> rectRadii;
    rectRadii.resize(4);
    rectRadii[RSRoundRect::TOP_LEFT_POS] =
        RSPoint(border_.TopLeftRadius().GetX().ConvertToPx(), border_.TopLeftRadius().GetY().ConvertToPx());
    rectRadii[RSRoundRect::TOP_RIGHT_POS] =
        RSPoint(border_.TopRightRadius().GetX().ConvertToPx(), border_.TopRightRadius().GetY().ConvertToPx());
    rectRadii[RSRoundRect::BOTTOM_RIGHT_POS] =
        RSPoint(border_.BottomRightRadius().GetX().ConvertToPx(), border_.BottomRightRadius().GetY().ConvertToPx());
    rectRadii[RSRoundRect::BOTTOM_LEFT_POS] =
        RSPoint(border_.BottomLeftRadius().GetX().ConvertToPx(), border_.BottomLeftRadius().GetY().ConvertToPx());
    return RSRoundRect(rect, rectRadii);
}

void BubblePaintMethod::PaintBubbleWithArrow(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    BuildCompletePath(path_);
    canvas.Save();
    canvas.ClipPath(path_, RSClipOp::DIFFERENCE, true);
    if (!needPaintOuterBorder_) {
        PaintShadow(path_, ShadowConfig::DefaultShadowM, canvas);
    }
    canvas.Restore();
    canvas.DrawPath(path_);
}

void BubblePaintMethod::PaintDoubleBorderWithArrow(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    BuildDoubleBorderPath(path_);
    canvas.Save();
    canvas.Restore();
    canvas.DrawPath(path_);
}

float BubblePaintMethod::GetInnerBorderOffset()
{
    float borderOffset = 0;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0);
    auto popupTheme = pipeline->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, 0);
    auto linearGradientFlag = false;
    if (!outlineLinearGradient_.gradientColors.empty() || !innerBorderLinearGradient_.gradientColors.empty()) {
        linearGradientFlag = true;
    }
    if ((popupTheme->GetPopupDoubleBorderEnable() || linearGradientFlag) && needPaintOuterBorder_) {
        borderOffset = outerBorderWidth_;
    }
    return borderOffset;
}

float BubblePaintMethod::GetBorderOffset()
{
    float borderOffset = 0.0f;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0);
    auto popupTheme = pipeline->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, 0);
    auto linearGradientFlag = false;
    if (!outlineLinearGradient_.gradientColors.empty() || !innerBorderLinearGradient_.gradientColors.empty()) {
        linearGradientFlag = true;
    }
    if (popupTheme->GetPopupDoubleBorderEnable() || linearGradientFlag) {
        if (needPaintOuterBorder_) {
            borderOffset = -outerBorderWidth_;
        } else {
            borderOffset = innerBorderWidth_;
        }
    }
    return borderOffset;
}

void BubblePaintMethod::BuildCompletePath(RSPath& path)
{
    float borderOffset = GetBorderOffset();
    float arrowOffset = GetArrowOffset(arrowPlacement_);
    auto borderRadius = ModifyBorderRadius(border_.BottomLeftRadius().GetY().ConvertToPx(), childSize_.Height() / 2);
    float radiusPx = borderRadius - borderOffset;
    path.Reset();
    path.MoveTo(childOffset_.GetX() + radiusPx, childOffset_.GetY() + borderOffset);
    BuildTopLinePath(path, arrowOffset, radiusPx);
    BuildCornerPath(path, Placement::TOP_RIGHT, radiusPx);
    BuildRightLinePath(path, arrowOffset, radiusPx);
    BuildCornerPath(path, Placement::BOTTOM_RIGHT, radiusPx);
    BuildBottomLinePath(path, arrowOffset, radiusPx);
    BuildCornerPath(path, Placement::BOTTOM_LEFT, radiusPx);
    BuildLeftLinePath(path, arrowOffset, radiusPx);
    BuildCornerPath(path, Placement::TOP_LEFT, radiusPx);
    path.Close();
}

void BubblePaintMethod::BuildDoubleBorderPath(RSPath& path)
{
    float borderOffset = GetBorderOffset();
    auto borderRadius = ModifyBorderRadius(border_.BottomLeftRadius().GetY().ConvertToPx(), childSize_.Height() / 2);
    float radiusPx = borderRadius - borderOffset;
    path.Reset();
    if ((arrowBuildPlacement_ == Placement::TOP_LEFT) || (arrowBuildPlacement_ == Placement::LEFT_TOP)) {
        path.MoveTo(childOffset_.GetX(), childOffset_.GetY() + borderOffset);
    } else {
        path.MoveTo(childOffset_.GetX() + radiusPx, childOffset_.GetY() + borderOffset);
    }
    BuildTopDoubleBorderPath(path, radiusPx);
    BuildRightDoubleBorderPath(path, radiusPx);
    BuildBottomDoubleBorderPath(path, radiusPx);
    BuildLeftDoubleBorderPath(path, radiusPx);
    path.Close();
}

void BubblePaintMethod::BuildTopLinePath(RSPath& path, float arrowOffset, float radius)
{
    float borderOffset = GetBorderOffset();
    float childOffsetY = childOffset_.GetY();
    float arrowPositionY = arrowPosition_.GetY();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto popupTheme = pipeline->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    auto leftOffset =
        childOffset_.GetX() + popupTheme->GetRadius().GetX().ConvertToPx() + ARROW_WIDTH.ConvertToPx() / 2;
    auto rightOffset = childOffset_.GetX() + childSize_.Width() - popupTheme->GetRadius().GetX().ConvertToPx() -
                       ARROW_WIDTH.ConvertToPx() / 2;
    auto arrowTopOffset = std::clamp(
        arrowPosition_.GetX() + arrowOffset, static_cast<float>(leftOffset), static_cast<float>(rightOffset));
    switch (arrowPlacement_) {
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            path.LineTo(arrowTopOffset - BEZIER_WIDTH_HALF.ConvertToPx() + borderOffset,
                childOffsetY + borderOffset);
            path.QuadTo(arrowTopOffset - BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx(),
                arrowPositionY + BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() + borderOffset,
                arrowTopOffset - BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx(),
                arrowPositionY + BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx() + borderOffset);
            path.QuadTo(arrowTopOffset - BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx() + borderOffset,
                arrowTopOffset, arrowPositionY + borderOffset);
            path.QuadTo(arrowTopOffset + BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx() + borderOffset,
                arrowTopOffset + BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx(),
                arrowPositionY + BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx() + borderOffset);
            path.QuadTo(arrowTopOffset + BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx(),
                arrowPositionY + BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() + borderOffset,
                arrowTopOffset + BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx(),
                arrowPositionY + BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() + borderOffset);
            break;
        default:
            break;
    }
    path.LineTo(childOffset_.GetX() + childSize_.Width() - radius, childOffsetY + borderOffset);
}

void BubblePaintMethod::BuildTopDoubleBorderPath(RSPath& path, float radius)
{
    float borderOffset = 0.0f;
    if (needPaintOuterBorder_) {
        borderOffset = -outerBorderWidth_;
    } else {
        borderOffset = innerBorderWidth_ / HALF;
    }
    float childOffsetY = childOffset_.GetY();
    float arrowTopOffset = childOffset_.GetX() - BUBBLE_ARROW_HEIGHT.ConvertToPx();
    switch (arrowPlacement_) {
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            borderOffset = GetBorderOffset();
            path.LineTo(arrowTopOffset + arrowOffsetsFromClip_[P1INDEX][0] + borderOffset / HALF,
                childOffsetY + borderOffset);
            path.LineTo(arrowTopOffset + arrowOffsetsFromClip_[P2INDEX][0] + borderOffset,
                childOffsetY + arrowOffsetsFromClip_[P2INDEX][1] - BUBBLE_ARROW_HEIGHT.ConvertToPx());
            path.ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f,
                RSPathDirection::CW_DIRECTION, arrowTopOffset + arrowOffsetsFromClip_[P3INDEX][0],
                childOffsetY + arrowOffsetsFromClip_[P3INDEX][1] - BUBBLE_ARROW_HEIGHT.ConvertToPx() + borderOffset);
            path.LineTo(arrowTopOffset + arrowOffsetsFromClip_[P4INDEX][0],
                childOffsetY + borderOffset);
            break;
        default:
            break;
    }
    if ((arrowBuildPlacement_ != Placement::TOP_RIGHT) && (arrowBuildPlacement_ != Placement::RIGHT_TOP)) {
        path.LineTo(childOffset_.GetX() + childSize_.Width() - radius, childOffsetY + borderOffset);
        BuildCornerPath(path, Placement::TOP_RIGHT, radius);
    }
}

void BubblePaintMethod::BuildCornerPath(RSPath& path, const Placement& placement, float radius)
{
    float borderOffset = GetBorderOffset();
    float childOffsetY = childOffset_.GetY();
    switch (placement) {
        case Placement::TOP_LEFT:
            path.ArcTo(radius, radius, 0.0f, RSPathDirection::CW_DIRECTION,
                childOffset_.GetX() + radius, childOffsetY + borderOffset);
            break;
        case Placement::TOP_RIGHT:
            path.ArcTo(radius, radius, 0.0f, RSPathDirection::CW_DIRECTION,
                childOffset_.GetX() + childSize_.Width() - borderOffset, childOffsetY + radius);
            break;
        case Placement::BOTTOM_RIGHT:
            path.ArcTo(radius, radius, 0.0f, RSPathDirection::CW_DIRECTION,
                childOffset_.GetX() + childSize_.Width() - radius,
                childOffsetY + childSize_.Height() - borderOffset);
            break;
        case Placement::BOTTOM_LEFT:
            path.ArcTo(radius, radius, 0.0f, RSPathDirection::CW_DIRECTION,
                childOffset_.GetX() + borderOffset,
                childOffsetY + childSize_.Height() - radius - borderOffset);
            break;
        default:
            break;
    }
}

void BubblePaintMethod::BuildRightLinePath(RSPath& path, float arrowOffset, float radius)
{
    float borderOffset = GetBorderOffset();
    float childOffsetY = childOffset_.GetY();
    float arrowPositionY = arrowPosition_.GetY();
    switch (arrowPlacement_) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            path.LineTo(childOffset_.GetX() + childSize_.Width() - borderOffset,
                arrowPositionY + arrowOffset - BEZIER_WIDTH_HALF.ConvertToPx() + borderOffset);
            path.QuadTo(arrowPosition_.GetX() - BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() - borderOffset,
                arrowPositionY + arrowOffset - BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx(),
                arrowPosition_.GetX() - BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx() - borderOffset,
                arrowPositionY + arrowOffset - BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx());
            path.QuadTo(arrowPosition_.GetX() + BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx() - borderOffset,
                arrowPositionY + arrowOffset - BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx(),
                arrowPosition_.GetX() - borderOffset, arrowPositionY + arrowOffset);
            path.QuadTo(arrowPosition_.GetX() + BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx() - borderOffset,
                arrowPositionY + arrowOffset + BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx(),
                arrowPosition_.GetX() - BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx() - borderOffset,
                arrowPositionY + arrowOffset + BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx());
            path.QuadTo(arrowPosition_.GetX() - BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() - borderOffset,
                arrowPositionY + arrowOffset + BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx(),
                arrowPosition_.GetX() - BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() - borderOffset,
                arrowPositionY + arrowOffset + BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx());
            break;
        default:
            break;
    }
    path.LineTo(childOffset_.GetX() + childSize_.Width() - borderOffset,
        childOffsetY + childSize_.Height() - radius - borderOffset);
}

void BubblePaintMethod::BuildRightDoubleBorderPath(RSPath& path, float radius)
{
    float borderOffset = GetBorderOffset();
    float childOffsetY = childOffset_.GetY();
    float arrowRightOffset = childOffset_.GetY() - BUBBLE_ARROW_HEIGHT.ConvertToPx();
    switch (arrowPlacement_) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            path.LineTo(childOffset_.GetX() + childSize_.Width() - borderOffset,
                arrowRightOffset + arrowOffsetsFromClip_[P1INDEX][1] + borderOffset / HALF);
            path.LineTo(childOffset_.GetX() + arrowOffsetsFromClip_[P2INDEX][0] - BUBBLE_ARROW_HEIGHT.ConvertToPx()
                - borderOffset, arrowRightOffset + arrowOffsetsFromClip_[P2INDEX][1]);
            path.ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f,
                RSPathDirection::CW_DIRECTION, childOffset_.GetX() + arrowOffsetsFromClip_[P3INDEX][0]
                - BUBBLE_ARROW_HEIGHT.ConvertToPx() - borderOffset,
                arrowRightOffset + arrowOffsetsFromClip_[P3INDEX][1]);
            path.LineTo(childOffset_.GetX()+ childSize_.Width() - borderOffset,
                arrowRightOffset + arrowOffsetsFromClip_[P4INDEX][1] - borderOffset / HALF);
            break;
        default:
            break;
    }
    if ((arrowBuildPlacement_ != Placement::RIGHT_BOTTOM) && (arrowBuildPlacement_ != Placement::BOTTOM_RIGHT)) {
        if (childOffsetY + childSize_.Height() - radius < childOffset_.GetY() + radius) {
            path.LineTo(childOffset_.GetX() + childSize_.Width() - borderOffset,
                childOffset_.GetY() + radius);
        } else {
            path.LineTo(childOffset_.GetX() + childSize_.Width() - borderOffset,
                childOffsetY + childSize_.Height() - radius);
        }
        BuildCornerPath(path, Placement::BOTTOM_RIGHT, radius);
    }
}

void BubblePaintMethod::BuildBottomLinePath(RSPath& path, float arrowOffset, float radius)
{
    float borderOffset = GetBorderOffset();
    float childOffsetY = childOffset_.GetY();
    float arrowPositionY = arrowPosition_.GetY();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto popupTheme = pipeline->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    auto leftOffset =
        childOffset_.GetX() + popupTheme->GetRadius().GetX().ConvertToPx() + ARROW_WIDTH.ConvertToPx() / HALF;
    auto rightOffset = childOffset_.GetX() + childSize_.Width() - popupTheme->GetRadius().GetX().ConvertToPx() -
                       ARROW_WIDTH.ConvertToPx() / HALF;
    auto arrowBottomOffset = std::clamp(
        arrowPosition_.GetX() + arrowOffset, static_cast<float>(leftOffset), static_cast<float>(rightOffset));
    switch (arrowPlacement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            path.LineTo(arrowBottomOffset + BEZIER_WIDTH_HALF.ConvertToPx() - borderOffset,
                childOffsetY + childSize_.Height() - borderOffset);
            path.QuadTo(arrowBottomOffset + BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() - borderOffset,
                arrowBottomOffset + BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx() - borderOffset);
            path.QuadTo(arrowBottomOffset + BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx() - borderOffset,
                arrowBottomOffset, arrowPositionY - borderOffset);
            path.QuadTo(arrowBottomOffset - BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx() - borderOffset,
                arrowBottomOffset - BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx() - borderOffset);
            path.QuadTo(arrowBottomOffset - BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() - borderOffset,
                arrowBottomOffset - BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx(),
                arrowPositionY - BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() - borderOffset);
            break;
        default:
            break;
    }
    path.LineTo(childOffset_.GetX() + radius, childOffsetY + childSize_.Height() - borderOffset);
}

void BubblePaintMethod::BuildBottomDoubleBorderPath(RSPath& path, float radius)
{
    float borderOffset = GetBorderOffset();
    float childOffsetY = childOffset_.GetY();
    float arrowBottomOffset = childOffset_.GetX() - BUBBLE_ARROW_HEIGHT.ConvertToPx();
    switch (arrowPlacement_) {
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            path.LineTo(arrowBottomOffset + arrowOffsetsFromClip_[P1INDEX][0],
                childOffsetY + childSize_.Height() - borderOffset);
            path.LineTo(arrowBottomOffset + arrowOffsetsFromClip_[P2INDEX][0],
                childOffsetY + arrowOffsetsFromClip_[P2INDEX][1] - BUBBLE_ARROW_HEIGHT.ConvertToPx() - borderOffset);
            path.ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f,
                RSPathDirection::CW_DIRECTION, arrowBottomOffset + arrowOffsetsFromClip_[P3INDEX][0],
                childOffsetY + arrowOffsetsFromClip_[P3INDEX][1] - BUBBLE_ARROW_HEIGHT.ConvertToPx() - borderOffset);
            path.LineTo(arrowBottomOffset + arrowOffsetsFromClip_[P4INDEX][0],
                childOffsetY + childSize_.Height() - borderOffset);
            break;
        default:
            break;
    }
    if ((arrowBuildPlacement_ != Placement::BOTTOM_LEFT) && (arrowBuildPlacement_ != Placement::LEFT_BOTTOM)) {
        path.LineTo(childOffset_.GetX() + radius, childOffsetY + childSize_.Height() - borderOffset);
        BuildCornerPath(path, Placement::BOTTOM_LEFT, radius);
    }
}

void BubblePaintMethod::BuildLeftDoubleBorderPath(RSPath& path, float radius)
{
    float borderOffset = GetBorderOffset();
    float childOffsetY = childOffset_.GetY();
    float arrowLeftOffset = childOffset_.GetY() - BUBBLE_ARROW_HEIGHT.ConvertToPx();
    switch (arrowPlacement_) {
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            path.LineTo(childOffset_.GetX() + borderOffset,
                arrowLeftOffset + arrowOffsetsFromClip_[P1INDEX][1]);
            path.LineTo(childOffset_.GetX() + arrowOffsetsFromClip_[P2INDEX][0] - BUBBLE_ARROW_HEIGHT.ConvertToPx()
                + borderOffset, arrowLeftOffset + arrowOffsetsFromClip_[P2INDEX][1]);
            path.ArcTo(ARROW_RADIUS.ConvertToPx(), ARROW_RADIUS.ConvertToPx(), 0.0f,
                RSPathDirection::CW_DIRECTION, childOffset_.GetX() + arrowOffsetsFromClip_[P3INDEX][0]
                - BUBBLE_ARROW_HEIGHT.ConvertToPx() + borderOffset,
                arrowLeftOffset + arrowOffsetsFromClip_[P3INDEX][1]);
            path.LineTo(childOffset_.GetX() + borderOffset, arrowLeftOffset + arrowOffsetsFromClip_[P4INDEX][1]);
            break;
        default:
            break;
    }
    if ((arrowBuildPlacement_ != Placement::LEFT_TOP) && (arrowBuildPlacement_ != Placement::TOP_LEFT)) {
        path.LineTo(childOffset_.GetX() + borderOffset, childOffsetY + radius + borderOffset);
        BuildCornerPath(path, Placement::TOP_LEFT, radius);
    }
}

void BubblePaintMethod::BuildLeftLinePath(RSPath& path, float arrowOffset, float radius)
{
    float borderOffset = GetBorderOffset();
    float childOffsetY = childOffset_.GetY();
    float arrowPositionY = arrowPosition_.GetY();
    switch (arrowPlacement_) {
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            path.LineTo(childOffset_.GetX() + borderOffset,
                arrowPositionY + arrowOffset + BEZIER_WIDTH_HALF.ConvertToPx() - borderOffset);
            path.QuadTo(arrowPosition_.GetX() + BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() + borderOffset,
                arrowPositionY + arrowOffset + BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx(),
                arrowPosition_.GetX() + BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx() + borderOffset,
                arrowPositionY + arrowOffset + BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx());
            path.QuadTo(arrowPosition_.GetX() - BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx() + borderOffset,
                arrowPositionY + arrowOffset + BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx() + borderOffset,
                arrowPosition_.GetX(), arrowPositionY + arrowOffset);
            path.QuadTo(arrowPosition_.GetX() - BEZIER_VERTICAL_OFFSET_FIRST.ConvertToPx() + borderOffset,
                arrowPositionY + arrowOffset - BEZIER_HORIZON_OFFSET_FIRST.ConvertToPx(),
                arrowPosition_.GetX() + BEZIER_VERTICAL_OFFSET_SECOND.ConvertToPx() + borderOffset,
                arrowPositionY + arrowOffset - BEZIER_HORIZON_OFFSET_SECOND.ConvertToPx());
            path.QuadTo(arrowPosition_.GetX() + BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() + borderOffset,
                arrowPositionY + arrowOffset - BEZIER_HORIZON_OFFSET_THIRD.ConvertToPx(),
                arrowPosition_.GetX() + BEZIER_VERTICAL_OFFSET_THIRD.ConvertToPx() + borderOffset,
                arrowPositionY + arrowOffset - BEZIER_HORIZON_OFFSET_FOURTH.ConvertToPx());
            break;
        default:
            break;
    }
    path.LineTo(childOffset_.GetX() + borderOffset, childOffsetY + radius + borderOffset);
}

float BubblePaintMethod::GetArrowOffset(const Placement& placement)
{
    double motionRange = 0.0;
    Edge edge;
    InitEdgeSize(edge);
    switch (placement) {
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            motionRange = childSize_.Width() - edge.Top().Value() - ARROW_WIDTH.ConvertToPx();
            break;
        case Placement::TOP:
            motionRange = childSize_.Width() - edge.Top().Value() - ARROW_WIDTH.ConvertToPx();
            break;
        case Placement::BOTTOM:
            motionRange = childSize_.Width() - edge.Bottom().Value() - ARROW_WIDTH.ConvertToPx();
            break;
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            motionRange = childSize_.Height() - edge.Left().Value() - ARROW_WIDTH.ConvertToPx();
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            motionRange = childSize_.Height() - edge.Right().Value() - ARROW_WIDTH.ConvertToPx();
            break;
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            motionRange = childSize_.Width() - edge.Bottom().Value() - ARROW_WIDTH.ConvertToPx();
            break;
        default:
            break;
    }
    return std::clamp(
        arrowOffset_.Unit() == DimensionUnit::PERCENT ? arrowOffset_.Value() * motionRange : arrowOffset_.ConvertToPx(),
        0.0, motionRange);
}

void BubblePaintMethod::InitEdgeSize(Edge& edge)
{
    edge.SetTop(Dimension(std::max(padding_.Left().ConvertToPx(), border_.TopLeftRadius().GetX().ConvertToPx()) +
                          std::max(padding_.Right().ConvertToPx(), border_.TopRightRadius().GetX().ConvertToPx())));
    edge.SetBottom(
        Dimension(std::max(padding_.Left().ConvertToPx(), border_.BottomLeftRadius().GetX().ConvertToPx()) +
                  std::max(padding_.Right().ConvertToPx(), border_.BottomRightRadius().GetX().ConvertToPx())));
    edge.SetLeft(
        Dimension(std::max(padding_.Top().ConvertToPx(), border_.TopRightRadius().GetY().ConvertToPx()) +
                  std::max(padding_.Bottom().ConvertToPx(), border_.BottomRightRadius().GetY().ConvertToPx())));
    edge.SetRight(
        Dimension(std::max(padding_.Top().ConvertToPx(), border_.TopLeftRadius().GetY().ConvertToPx()) +
                  std::max(padding_.Bottom().ConvertToPx(), border_.BottomLeftRadius().GetY().ConvertToPx())));
}

void BubblePaintMethod::ClipBubbleWithPath(const RefPtr<FrameNode>& frameNode)
{
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameNodeSize = geometryNode->GetFrameSize();
    CHECK_NULL_VOID(frameNodeSize.IsPositive());
    auto path = AceType::MakeRefPtr<Path>();
    path->SetValue(clipPath_);
    path->SetBasicShapeType(BasicShapeType::PATH);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateClipShape(path);
}

} // namespace OHOS::Ace::NG
