/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/data_panel/data_panel_modifier.h"

#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float FIXED_WIDTH = 1.0f;
constexpr float HALF_CIRCLE = 180.0f;
constexpr float WHOLE_CIRCLE = 360.0f;
constexpr float QUARTER_CIRCLE = 90.0f;
constexpr float MIN_CIRCLE = 0.03f;
constexpr float PERCENT_HALF = 0.5f;
constexpr float DIAMETER_TO_THICKNESS_RATIO = 0.12f;
constexpr uint32_t SHADOW_ALPHA = 0.4 * 255;
constexpr float ZERO_CORNER_RADIUS = 0.0f;
} // namespace

DataPanelModifier::DataPanelModifier()
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<DataPanelTheme>();
    auto colors = theme->GetColorsArray();

    date_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
    for (size_t i = 0; i < MAX_COUNT; ++i) {
        auto value = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
        AttachProperty(value);
        values_.emplace_back(value);
    }
    max_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(DEFAULT_MAX_VALUE);
    trackBackgroundColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(theme->GetBackgroundColor()));
    strokeWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(theme->GetThickness().ConvertToPx());
    isEffect_ = AceType::MakeRefPtr<PropertyBool>(true);
    useContentModifier_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(date_);
    AttachProperty(max_);
    AttachProperty(trackBackgroundColor_);
    AttachProperty(strokeWidth_);
    AttachProperty(isEffect_);

    shadowRadiusFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(theme->GetTrackShadowRadius().ConvertToPx());
    shadowOffsetXFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(theme->GetTrackShadowOffsetX().ConvertToPx());
    shadowOffsetYFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(theme->GetTrackShadowOffsetY().ConvertToPx());
    AttachProperty(shadowRadiusFloat_);
    AttachProperty(shadowOffsetXFloat_);
    AttachProperty(shadowOffsetYFloat_);

    for (const auto& item : colors) {
        Gradient gradient;
        GradientColor gradientColorStart;
        gradientColorStart.SetLinearColor(LinearColor(item.first));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        GradientColor gradientColorEnd;
        gradientColorEnd.SetLinearColor(LinearColor(item.second));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);

        auto gradientColor = AceType::MakeRefPtr<AnimatablePropertyVectorColor>(GradientArithmetic(gradient));
        AttachProperty(gradientColor);
        valueColors_.emplace_back(gradientColor);

        auto gradientShadowColor = AceType::MakeRefPtr<AnimatablePropertyVectorColor>(GradientArithmetic(gradient));
        AttachProperty(gradientShadowColor);
        shadowColors_.emplace_back(gradientShadowColor);
    }
}

void DataPanelModifier::onDraw(DrawingContext& context)
{
    if (useContentModifier_->Get()) {
        return;
    }
    if (dataPanelType_ == 0) {
        PaintCircle(context, offset_);
    } else {
        PaintLinearProgress(context, offset_);
    }
}

void DataPanelModifier::UpdateDate()
{
    if (isEffect_->Get()) {
        // When the date update, the animation will repeat once.
        date_->Set(ANIMATION_START);
        AnimationOption option = AnimationOption();
        RefPtr<Curve> curve = AceType::MakeRefPtr<SpringCurve>(
            ANIMATION_CURVE_VELOCITY, ANIMATION_CURVE_MASS, ANIMATION_CURVE_STIFFNESS, ANIMATION_CURVE_DAMPING);
        option.SetDuration(ANIMATION_DURATION);
        option.SetDelay(ANIMATION_DELAY);
        option.SetCurve(curve);
        option.SetIteration(ANIMATION_TIMES);
        AnimationUtils::Animate(option, [&]() { date_->Set(ANIMATION_END); });
    } else {
        date_->Set(ANIMATION_END);
    }
}

void DataPanelModifier::PaintCircle(DrawingContext& context, OffsetF offset) const
{
    RSCanvas& canvas = context.canvas;
    canvas.Save();
    canvas.Translate(offset.GetX(), offset.GetY());

    auto defaultThickness = strokeWidth_->Get();
    ArcData arcData;
    Offset center = Offset(context.width * PERCENT_HALF, context.height * PERCENT_HALF);
    arcData.center = center;
    // Here radius will minus defaultThickness, when there will be new api to set padding, use the new padding.
    arcData.radius = std::min(context.width, context.height) * PERCENT_HALF - defaultThickness;
    if (defaultThickness >= arcData.radius) {
        arcData.thickness = arcData.radius * DIAMETER_TO_THICKNESS_RATIO;
    } else {
        arcData.thickness = defaultThickness;
    }
    PaintTrackBackground(canvas, arcData, trackBackgroundColor_->Get().ToColor());
    arcData.maxValue = max_->Get();
    for (size_t i = 0; i < valuesLastLength_; ++i) {
        arcData.totalAllValue += values_[i]->Get();
    }
    if (NonPositive(arcData.totalAllValue)) {
        // all values are invalid
        return;
    }

    arcData.totalDrawAngle = (arcData.totalAllValue * date_->Get()) / arcData.maxValue * WHOLE_CIRCLE;
    arcData.totalDrawAngle = std::min(arcData.totalDrawAngle, WHOLE_CIRCLE);
    Offset shadowCenter = Offset(context.width * PERCENT_HALF + shadowOffsetXFloat_->Get(),
        context.height * PERCENT_HALF + shadowOffsetYFloat_->Get());

    // paint shadows
    if ((isShadowVisible_ && (isHasShadowValue_ || isEffect_->Get()))) {
        for (size_t i = 0; i < shadowColorsLastLength_; ++i) {
            if (NearZero(values_[i]->Get())) {
                continue;
            }
            arcData.shadowColor = SortGradientColorsOffset(shadowColors_[i]->Get().GetGradient());
            auto totalValuePre = arcData.totalValue;
            arcData.totalValue += values_[i]->Get();
            if (GreatNotEqual(arcData.totalValue, arcData.maxValue)) {
                continue;
            }
            arcData.progressValue = arcData.totalValue * date_->Get();
            arcData.drawAngle = arcData.progressValue / arcData.maxValue * WHOLE_CIRCLE;
            arcData.drawAngle = arcData.lastAngle + std::max(arcData.drawAngle - arcData.lastAngle, MIN_CIRCLE);
            arcData.drawAngle = std::min(arcData.drawAngle, WHOLE_CIRCLE);

            arcData.gradientPointBase = totalValuePre / arcData.totalValue;

#ifndef USE_ROSEN_DRAWING
            RSPath path;
            RSPath endPath;
#else
            RSRecordingPath path;
            RSRecordingPath endPath;
#endif
            arcData.center = shadowCenter;
            GetPaintPath(arcData, path, endPath);
            PaintProgress(canvas, arcData, path, endPath, true);
            arcData.lastAngle = arcData.drawAngle;
        }
    }
    arcData.lastAngle = 0.0f;
    arcData.totalValue = 0.0f;
    canvas.Restore();

    for (size_t i = 0; i < valuesLastLength_; ++i) {
        if (NearZero(values_[i]->Get())) {
            continue;
        }
        arcData.progressColors = SortGradientColorsOffset(valueColors_[i]->Get().GetGradient());
        auto totalValuePre = arcData.totalValue;
        arcData.totalValue += values_[i]->Get();
        if (GreatNotEqual(arcData.totalValue, arcData.maxValue)) {
            return;
        }
        arcData.progressValue = arcData.totalValue * date_->Get();
        arcData.drawAngle = arcData.progressValue / arcData.maxValue * WHOLE_CIRCLE;
        arcData.drawAngle = arcData.lastAngle + std::max(arcData.drawAngle - arcData.lastAngle, MIN_CIRCLE);
        arcData.drawAngle = std::min(arcData.drawAngle, WHOLE_CIRCLE);

        arcData.gradientPointBase = totalValuePre / arcData.totalValue;

#ifndef USE_ROSEN_DRAWING
        RSPath path;
        RSPath endPath;
#else
        RSRecordingPath path;
        RSRecordingPath endPath;
#endif
        arcData.center = center;
        GetPaintPath(arcData, path, endPath);
        PaintProgress(canvas, arcData, path, endPath, false);
        arcData.lastAngle = arcData.drawAngle;
    }
    canvas.Restore();
}

void DataPanelModifier::GetPaintPath(ArcData& arcData, RSPath& path, RSPath& endPath) const
{
    float thickness = arcData.thickness;
    float radius = arcData.radius;
    float lastAngle = arcData.lastAngle;
    float drawAngle = arcData.drawAngle;
    float totalDrawAngle = arcData.totalDrawAngle;

    Offset center = arcData.center;

    float sine = thickness * PERCENT_HALF / (radius - (thickness * PERCENT_HALF));
    float radian = asin(sine);
    // the angle of center of start half circle to center and tangent of start half circle to center
    arcData.circleAngle = radian * HALF_CIRCLE / M_PI;
    float circleAngle = arcData.circleAngle;

    float startAngle = 0.0f;
    // first line and start half circle not cover end half circle
    if (NearZero(lastAngle) && LessOrEqual(drawAngle, WHOLE_CIRCLE - circleAngle * 2.0f)) {
        lastAngle += circleAngle;
        drawAngle += circleAngle;
        startAngle += circleAngle;
        totalDrawAngle += circleAngle;
    }
    /*
     * lastRadian: radian of last angle
     * drawRadian: radian of this draw angle
     * totalDrawRadian: radian of total draw angle
     * startRadian: radian of draw start angle
     * originDrawRadian: radian of total draw angle before rotate
     * d: the distance between center of start half circle and end half circle
     * midAngel: the angle of 0 angle and line of center of start half circle and center of end half circle
     * tagAngle: the angle of line of center of start half circle and center of end half circle and
                 line of intersection of start half circle and intersection of end half circle
    */
    float lastRadian = M_PI * lastAngle / HALF_CIRCLE;
    float drawRadian = M_PI * drawAngle / HALF_CIRCLE;
    float totalDrawRadian = M_PI * totalDrawAngle / HALF_CIRCLE;
    float startRadian = M_PI * startAngle / HALF_CIRCLE;
    float originDrawRadian = M_PI * arcData.totalDrawAngle / HALF_CIRCLE;
    float d = std::sqrt(
        std::pow(
            (radius - thickness * PERCENT_HALF) - (radius - thickness * PERCENT_HALF) * std::cos(originDrawRadian), 2) +
        std::pow((radius - thickness * PERCENT_HALF) * std::sin(originDrawRadian), 2));
    float midAngle = QUARTER_CIRCLE;
    float tagAngle = QUARTER_CIRCLE;
    if (d > 0) {
        midAngle = std::acos(std::abs((radius - thickness * PERCENT_HALF) -
                                      (radius - thickness * PERCENT_HALF) * std::cos(originDrawRadian)) /
                             d) *
                   HALF_CIRCLE / M_PI;
        tagAngle = std::acos((d / thickness)) * HALF_CIRCLE / M_PI;
    }
    /*
     * path of start half circle:
     * when it's not first line or total draw angle is a whole circle, path is a half circle inward
     * when it's first line and end half circle not cover start cover circle, path is a half circle outword
     * when it's first line and end half circle cover start cover circle, path is cut by end half circle
     */
    if (GreatNotEqual(arcData.lastAngle, START_ANGLE) || arcData.totalDrawAngle == WHOLE_CIRCLE) {
        Path2DArc(path, center.GetX() + (radius - thickness * PERCENT_HALF) * std::cos(lastRadian),
            center.GetY() + (radius - thickness * PERCENT_HALF) * std::sin(lastRadian), thickness * PERCENT_HALF,
            lastAngle + HALF_CIRCLE, lastAngle, true);
    } else if (LessOrEqual(arcData.totalDrawAngle, WHOLE_CIRCLE - circleAngle * 2.0f)) {
        Path2DArc(path, center.GetX() + (radius - thickness * PERCENT_HALF) * std::cos(lastRadian),
            center.GetY() + (radius - thickness * PERCENT_HALF) * std::sin(lastRadian), thickness * PERCENT_HALF,
            lastAngle + HALF_CIRCLE, lastAngle, false);
    } else {
        Path2DArc(path, center.GetX() + (radius - thickness * PERCENT_HALF) * std::cos(startRadian),
            center.GetY() + (radius - thickness * PERCENT_HALF) * std::sin(startRadian), thickness * PERCENT_HALF,
            HALF_CIRCLE + startAngle, HALF_CIRCLE + midAngle - tagAngle + startAngle, false);
        Path2DArc(path, center.GetX() + (radius - thickness * PERCENT_HALF) * std::cos(totalDrawRadian),
            center.GetY() + (radius - thickness * PERCENT_HALF) * std::sin(totalDrawRadian), thickness * PERCENT_HALF,
            arcData.totalDrawAngle - HALF_CIRCLE - midAngle + tagAngle + startAngle,
            arcData.totalDrawAngle + HALF_CIRCLE - midAngle - tagAngle + startAngle, true);
        Path2DArc(path, center.GetX() + (radius - thickness * PERCENT_HALF) * std::cos(startRadian),
            center.GetY() + (radius - thickness * PERCENT_HALF) * std::sin(startRadian), thickness * PERCENT_HALF,
            -HALF_CIRCLE + midAngle + tagAngle + startAngle, startAngle, false);
    }

    /* when it's end half circle not cover it's start angle draw whole outer circle and inner circle and draw path
     * of end half circle else draw outer circle and inner circle to 180 angle */
    if (LessOrEqual(drawAngle - lastAngle, WHOLE_CIRCLE - circleAngle * 2.0f)) {
        // path of outer circle
        Path2DArc(path, center.GetX(), center.GetY(), radius, lastAngle, drawAngle, false);
        Path2DArc(path, center.GetX() + (radius - thickness * PERCENT_HALF) * std::cos(drawRadian),
            center.GetY() + (radius - thickness * PERCENT_HALF) * std::sin(drawRadian), thickness * PERCENT_HALF,
            drawAngle, drawAngle + HALF_CIRCLE, false);
        // path of inner circle
        Path2DArc(path, center.GetX(), center.GetY(), radius - thickness, drawAngle, lastAngle, true);
    } else {
        Path2DArc(path, center.GetX(), center.GetY(), radius, lastAngle, HALF_CIRCLE, false);
        Path2DArc(path, center.GetX(), center.GetY(), radius - thickness, HALF_CIRCLE, lastAngle, true);
    }
    path.Close();

    if (GreatNotEqual(drawAngle - lastAngle, WHOLE_CIRCLE - circleAngle * 2.0f)) {
        Path2DArc(endPath, center.GetX(), center.GetY(), radius - thickness, HALF_CIRCLE, drawAngle, false);
        Path2DArc(endPath, center.GetX() + (radius - thickness * PERCENT_HALF) * std::cos(drawRadian),
            center.GetY() + (radius - thickness * PERCENT_HALF) * std::sin(drawRadian), thickness * PERCENT_HALF,
            drawAngle + HALF_CIRCLE, drawAngle, true);
        Path2DArc(endPath, center.GetX(), center.GetY(), radius, drawAngle, HALF_CIRCLE, true);
        endPath.Close();
    }
}

void DataPanelModifier::PaintLinearProgress(DrawingContext& context, OffsetF offset) const
{
    auto& canvas = context.canvas;
    auto totalWidth = context.width;
    auto spaceWidth = PipelineBase::Vp2PxWithCurrentDensity(FIXED_WIDTH);
    auto segmentWidthSum = 0.0f;
    auto segmentSize = 0.0;
    for (size_t i = 0; i < valuesLastLength_; ++i) {
        if (NearZero(values_[i]->Get())) {
            continue;
        }
        segmentWidthSum += values_[i]->Get();
        if (GreatOrEqual(segmentWidthSum, max_->Get())) {
            break;
        }
        ++segmentSize;
    }

    float scaleMaxValue = 0.0f;
    scaleMaxValue = (totalWidth - segmentSize * spaceWidth) / max_->Get();

    auto widthSegment = offset.GetX();
    auto firstSegmentWidth = values_[0]->Get() * scaleMaxValue;
    PaintBackground(canvas, offset, totalWidth, context.height, firstSegmentWidth);
    float totalPaintWidth = 0.0f;
    float preWidthSegment = 0.0f;
    std::vector<LinearData> linearDataMap;
    bool isFirstValidDate = true;
    for (size_t i = 0; i < valuesLastLength_; ++i) {
        auto segmentWidth = values_[i]->Get();
        if (NonPositive(segmentWidth)) {
            continue;
        }
        LinearData segmentLinearData;
        segmentLinearData.offset = offset;
        segmentLinearData.height = context.height;
        segmentLinearData.totalWidth = totalWidth;

        if (isFirstValidDate) {
            segmentLinearData.isFirstData = true;
            isFirstValidDate = false;
        }

        segmentLinearData.segmentColor = SortGradientColorsOffset(valueColors_[i]->Get().GetGradient());
        segmentLinearData.segmentWidth = segmentWidth * scaleMaxValue;
        segmentLinearData.xSegment = widthSegment;
        preWidthSegment = widthSegment;
        if (GreatOrEqual(segmentLinearData.segmentWidth + segmentLinearData.xSegment, totalWidth)) {
            segmentLinearData.segmentWidth = totalWidth - preWidthSegment;
        }
        // mark last data or add space width
        widthSegment += values_[i]->Get() * scaleMaxValue;
        totalPaintWidth += segmentWidth;
        if (GreatOrEqual(totalPaintWidth, max_->Get())) {
            segmentLinearData.isEndData = true;
        } else {
            widthSegment += spaceWidth;
        }
        // draw the shadow at the bottom
        if ((isShadowVisible_ && (isHasShadowValue_ || isEffect_->Get())) && (i < shadowColorsLastLength_)) {
            segmentLinearData.segmentShadowColor = SortGradientColorsOffset(shadowColors_[i]->Get().GetGradient());
            PaintColorSegmentFilterMask(canvas, segmentLinearData);
        }

        linearDataMap.emplace_back(segmentLinearData);
    }
    // draw the data and the space after drawing the shadow
    for (size_t i = 0; i < linearDataMap.size(); ++i) {
        PaintColorSegment(canvas, linearDataMap[i]);
        if (!linearDataMap[i].isEndData) {
            PaintSpace(canvas, linearDataMap[i], spaceWidth);
        }
    }
}

void DataPanelModifier::PaintBackground(
    RSCanvas& canvas, OffsetF offset, float totalWidth, float height, float segmentWidth) const
{
    RSBrush brush;
    brush.SetColor(ToRSColor(trackBackgroundColor_->Get()));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    RSRect rRect(offset.GetX(), offset.GetY(), totalWidth + offset.GetX(), height + offset.GetY());
    RSRoundRect rrRect;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (height <= segmentWidth) {
            rrRect = RSRoundRect(rRect, height, height);
        } else {
            rrRect = RSRoundRect(rRect, segmentWidth, segmentWidth);
        }
    } else {
        rrRect = RSRoundRect(rRect, ZERO_CORNER_RADIUS, ZERO_CORNER_RADIUS);
    }
    canvas.DrawRoundRect(rrRect);
    canvas.DetachBrush();
}

void DataPanelModifier::SetCornerRadius(
    RSRoundRect& paintRect, const LinearData& segmentLinearData, const float height) const
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (segmentLinearData.isFirstData) {
            paintRect.SetCornerRadius(RSRoundRect::TOP_LEFT_POS, height, height);
            paintRect.SetCornerRadius(RSRoundRect::BOTTOM_LEFT_POS, height, height);
        }

        if (segmentLinearData.isEndData) {
            paintRect.SetCornerRadius(RSRoundRect::TOP_RIGHT_POS, height, height);
            paintRect.SetCornerRadius(RSRoundRect::BOTTOM_RIGHT_POS, height, height);
        }
    }
}

void DataPanelModifier::PaintColorSegment(RSCanvas& canvas, const LinearData& segmentLinearData) const
{
    auto offset = segmentLinearData.offset;
    auto xSegment = segmentLinearData.xSegment;
    auto segmentWidth = segmentLinearData.segmentWidth;
    auto height = segmentLinearData.height;

    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    size_t length = segmentLinearData.segmentColor.GetColors().size();
    for (size_t i = 0; i < length; ++i) {
        colors.emplace_back(segmentLinearData.segmentColor.GetColors().at(i).GetLinearColor().GetValue());
        pos.emplace_back(segmentLinearData.segmentColor.GetColors().at(i).GetDimension().Value());
    }

    RSRect rect(xSegment, offset.GetY(), xSegment + segmentWidth, offset.GetY() + height);
    RSRoundRect paintRect = RSRoundRect(rect, 0, 0);
    SetCornerRadius(paintRect, segmentLinearData, height);

    RSPoint segmentStartPoint;
    segmentStartPoint.SetX(rect.GetLeft());
    segmentStartPoint.SetY(rect.GetTop());
    RSPoint segmentEndPoint;
    segmentEndPoint.SetX(rect.GetRight());
    segmentEndPoint.SetY(rect.GetBottom());
    canvas.Save();
    RSBrush brush;
#ifndef USE_ROSEN_DRAWING
    brush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(segmentStartPoint, segmentEndPoint, colors, pos, RSTileMode::CLAMP));
#else
    brush.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
        segmentStartPoint, segmentEndPoint, colors, pos, RSTileMode::CLAMP));
#endif
    canvas.AttachBrush(brush);
    if (isRtl_) {
        canvas.Translate(segmentLinearData.totalWidth, 0);
        canvas.Scale(-1, 1);
    }
    canvas.DrawRoundRect(paintRect);
    canvas.DetachBrush();
    canvas.Restore();
}

void DataPanelModifier::PaintColorSegmentFilterMask(RSCanvas& canvas, const LinearData& segmentLinearData) const
{
    auto offset = segmentLinearData.offset;
    auto xSegment = segmentLinearData.xSegment;
    auto segmentWidth = segmentLinearData.segmentWidth;
    auto height = segmentLinearData.height;

    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    size_t length = segmentLinearData.segmentShadowColor.GetColors().size();
    for (size_t i = 0; i < length; ++i) {
        colors.emplace_back(segmentLinearData.segmentShadowColor.GetColors().at(i).GetLinearColor().GetValue());
        pos.emplace_back(segmentLinearData.segmentShadowColor.GetColors().at(i).GetDimension().Value());
    }

    RSRect rect(xSegment + shadowOffsetXFloat_->Get(), offset.GetY() + shadowOffsetYFloat_->Get(),
        xSegment + segmentWidth + shadowOffsetXFloat_->Get(), offset.GetY() + height + shadowOffsetYFloat_->Get());
    RSRoundRect paintRect = RSRoundRect(rect, 0, 0);
    SetCornerRadius(paintRect, segmentLinearData, height);

    RSPoint segmentStartPoint;
    segmentStartPoint.SetX(rect.GetLeft());
    segmentStartPoint.SetY(rect.GetTop());
    RSPoint segmentEndPoint;
    segmentEndPoint.SetX(rect.GetRight());
    segmentEndPoint.SetY(rect.GetBottom());
    canvas.Save();
    RSBrush brush;
    RSFilter filter;
#ifndef USE_ROSEN_DRAWING
    filter.SetImageFilter(RSImageFilter::CreateBlurImageFilter(
        shadowRadiusFloat_->Get(), shadowRadiusFloat_->Get(), RSTileMode::DECAL, nullptr));
    brush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(segmentStartPoint, segmentEndPoint, colors, pos, RSTileMode::CLAMP));
#else
    filter.SetImageFilter(RSRecordingImageFilter::CreateBlurImageFilter(
        shadowRadiusFloat_->Get(), shadowRadiusFloat_->Get(), RSTileMode::DECAL, nullptr));
    brush.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
        segmentStartPoint, segmentEndPoint, colors, pos, RSTileMode::CLAMP));
#endif
    brush.SetFilter(filter);
    brush.SetAlpha(SHADOW_ALPHA);
    canvas.AttachBrush(brush);
    if (isRtl_) {
        canvas.Translate(segmentLinearData.totalWidth, 0);
        canvas.Scale(-1, 1);
    }
    canvas.DrawRoundRect(paintRect);
    canvas.DetachBrush();
    canvas.Restore();
}

void DataPanelModifier::PaintSpace(RSCanvas& canvas, const LinearData& segmentLinearData, float spaceWidth) const
{
    float xSpace = segmentLinearData.xSegment + segmentLinearData.segmentWidth;
    auto offset = segmentLinearData.offset;
    canvas.Save();
    RSBrush brush;
    RSRect rect(xSpace, offset.GetY(), xSpace + spaceWidth, offset.GetY() + segmentLinearData.height);
    brush.SetColor(ToRSColor(Color::WHITE));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    if (isRtl_) {
        canvas.Translate(segmentLinearData.totalWidth, 0);
        canvas.Scale(-1, 1);
    }
    canvas.DrawRect(rect);
    canvas.DetachBrush();
    canvas.Restore();
}

void DataPanelModifier::PaintTrackBackground(RSCanvas& canvas, ArcData arcData, const Color color) const
{
    RSPen backgroundTrackData;
#ifndef USE_ROSEN_DRAWING
    RSPath backgroundTrackPath;
#else
    RSRecordingPath backgroundTrackPath;
#endif
    auto center = arcData.center;
    float thickness = arcData.thickness;
    float radius = arcData.radius;

    RSRect rect(center.GetX() - radius + thickness * PERCENT_HALF, center.GetY() - radius + thickness * PERCENT_HALF,
        center.GetX() + radius - thickness * PERCENT_HALF, center.GetY() + radius - thickness * PERCENT_HALF);

    backgroundTrackPath.AddArc(rect, 0.0, WHOLE_CIRCLE);
    backgroundTrackData.SetColor(ToRSColor(color));
    backgroundTrackData.SetAntiAlias(true);
    backgroundTrackData.SetWidth(thickness);

    canvas.AttachPen(backgroundTrackData);
    canvas.DrawPath(backgroundTrackPath);
    canvas.DetachPen();
}

void DataPanelModifier::PaintProgress(
    RSCanvas& canvas, ArcData arcData, RSPath& path, RSPath& endPath, bool isShadow) const
{
    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    Gradient sourceColors;
    if (isShadow) {
        sourceColors = arcData.shadowColor;
    } else {
        sourceColors = arcData.progressColors;
    }
    float circleAngle = arcData.circleAngle;
    // add end half circle color
    if (GreatNotEqual(arcData.gradientPointBase, 0.0f)) {
        pos.emplace_back(circleAngle / WHOLE_CIRCLE);
        colors.emplace_back(sourceColors.GetColors().rbegin()->GetLinearColor().GetValue());
    }
    size_t length = sourceColors.GetColors().size();
    for (size_t i = 0; i < length; ++i) {
        colors.emplace_back(sourceColors.GetColors().at(i).GetLinearColor().GetValue());
        if (NearZero(arcData.gradientPointBase)) {
            pos.emplace_back(sourceColors.GetColors().at(i).GetDimension().Value());
        } else {
            auto itemPos = (1.0f - arcData.gradientPointBase) * sourceColors.GetColors().at(i).GetDimension().Value() +
                           arcData.gradientPointBase;
            pos.emplace_back(itemPos);
        }
    }

    float lastAngle = arcData.lastAngle;
    float drawAngle = arcData.drawAngle;
    Offset center = arcData.center;

    // first line and start half circle not cover end half circle
    if (NearZero(lastAngle) && LessOrEqual(drawAngle, WHOLE_CIRCLE - circleAngle * 2.0f)) {
        lastAngle += circleAngle;
        drawAngle += circleAngle;
    }
    RSBrush gradientPaint;
    gradientPaint.SetAntiAlias(true);

    /*
     * when it's first line and end circle not cover start circle, use wide gradient
     * when it's first line and end circle cover start circle, use default gradient and set start half circle color
     * extra else paint line and use default gradient
     */
    if (NearZero(arcData.lastAngle) && LessOrEqual(arcData.drawAngle, WHOLE_CIRCLE - circleAngle * 2.0f)) {
        drawAngle += circleAngle;
        canvas.Save();
        canvas.Rotate(-QUARTER_CIRCLE - circleAngle, center.GetX(), center.GetY());
    } else if (NearZero(arcData.lastAngle) && GreatNotEqual(arcData.drawAngle, WHOLE_CIRCLE - circleAngle * 2.0f)) {
        float startPos = (WHOLE_CIRCLE - circleAngle) / WHOLE_CIRCLE;
        pos.emplace_back(startPos);
        colors.emplace_back(sourceColors.GetColors().begin()->GetLinearColor().GetValue());
        canvas.Save();
        canvas.Rotate(-QUARTER_CIRCLE, center.GetX(), center.GetY());
    } else {
        canvas.Save();
        canvas.Rotate(-QUARTER_CIRCLE, center.GetX(), center.GetY());
    }
#ifndef USE_ROSEN_DRAWING
    gradientPaint.SetShaderEffect(RSShaderEffect::CreateSweepGradient(ToRSPoint(PointF(center.GetX(), center.GetY())),
        colors, pos, RSTileMode::CLAMP, START_ANGLE, drawAngle, nullptr));
#else
    gradientPaint.SetShaderEffect(
        RSRecordingShaderEffect::CreateSweepGradient(ToRSPoint(PointF(center.GetX(), center.GetY())), colors, pos,
            RSTileMode::CLAMP, START_ANGLE, drawAngle, nullptr));
#endif
    RSFilter filter;
    if (isShadow) {
        gradientPaint.SetAlpha(SHADOW_ALPHA);
#ifndef USE_ROSEN_DRAWING
        filter.SetImageFilter(RSImageFilter::CreateBlurImageFilter(
            shadowRadiusFloat_->Get(), shadowRadiusFloat_->Get(), RSTileMode::DECAL, nullptr));
        gradientPaint.SetFilter(filter);
#else
        filter.SetImageFilter(RSRecordingImageFilter::CreateBlurImageFilter(
            shadowRadiusFloat_->Get(), shadowRadiusFloat_->Get(), RSTileMode::DECAL, nullptr));
        gradientPaint.SetFilter(filter);
#endif
    }

    canvas.AttachBrush(gradientPaint);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    path.Reset();
    canvas.Restore();

    /* if path havn't end half circle, draw end circle extra. when draw is not whole circle, add fix angle to cover
       gap between line and end half circle */
    if (GreatNotEqual(drawAngle - lastAngle, WHOLE_CIRCLE - circleAngle * 2.0f)) {
        RSBrush endCirclePaint;
        endCirclePaint.SetAntiAlias(true);
        if (NearZero(arcData.lastAngle)) {
            pos.pop_back();
            colors.pop_back();
        }
        pos.emplace(pos.begin(), circleAngle / WHOLE_CIRCLE);
        colors.emplace(colors.begin(), sourceColors.GetColors().rbegin()->GetLinearColor().GetValue());
#ifndef USE_ROSEN_DRAWING
        endCirclePaint.SetShaderEffect(
            RSShaderEffect::CreateSweepGradient(ToRSPoint(PointF(center.GetX(), center.GetY())), colors, pos,
                RSTileMode::CLAMP, START_ANGLE, drawAngle, nullptr));
#else
        endCirclePaint.SetShaderEffect(
            RSRecordingShaderEffect::CreateSweepGradient(ToRSPoint(PointF(center.GetX(), center.GetY())), colors, pos,
                RSTileMode::CLAMP, START_ANGLE, drawAngle, nullptr));
#endif
        if (isShadow) {
            endCirclePaint.SetAlpha(SHADOW_ALPHA);
            endCirclePaint.SetFilter(filter);
        }
        canvas.Save();
        canvas.Rotate(-QUARTER_CIRCLE, center.GetX(), center.GetY());
        canvas.AttachBrush(endCirclePaint);
        canvas.DrawPath(endPath);
        canvas.DetachBrush();
        endPath.Reset();
        canvas.Restore();
    }
}

void DataPanelModifier::Path2DArc(
    RSPath& path, double x, double y, double r, double startAngle, double endAngle, bool counterclockwise) const
{
    RSPoint point1(x - r, y - r);
    RSPoint point2(x + r, y + r);

    double sweepAngle = endAngle - startAngle;
    if (!NearZero(counterclockwise)) {
        sweepAngle = endAngle > startAngle ? (std::fmod(sweepAngle, WHOLE_CIRCLE) - WHOLE_CIRCLE) : sweepAngle;
    } else {
        sweepAngle = endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, WHOLE_CIRCLE) + WHOLE_CIRCLE);
    }

    if (NearEqual(std::fmod(sweepAngle, WHOLE_CIRCLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        path.ArcTo(point1, point2, startAngle, HALF_CIRCLE);
        path.ArcTo(point1, point2, startAngle + HALF_CIRCLE, HALF_CIRCLE);
    } else if (!NearEqual(std::fmod(sweepAngle, WHOLE_CIRCLE), 0.0) && std::abs(sweepAngle) > WHOLE_CIRCLE) {
        path.ArcTo(point1, point2, startAngle, HALF_CIRCLE);
        path.ArcTo(point1, point2, startAngle + HALF_CIRCLE, HALF_CIRCLE);
        path.ArcTo(point1, point2, startAngle + HALF_CIRCLE + HALF_CIRCLE, sweepAngle);
    } else {
        path.ArcTo(point1, point2, startAngle, sweepAngle);
    }
}

Gradient DataPanelModifier::SortGradientColorsOffset(const Gradient& srcGradient) const
{
    auto srcGradientColors = srcGradient.GetColors();
    std::sort(
        srcGradientColors.begin(), srcGradientColors.end(), [](const GradientColor& left, const GradientColor& right) {
            return left.GetDimension().Value() < right.GetDimension().Value();
        });

    Gradient gradient;
    for (const auto& item : srcGradientColors) {
        gradient.AddColor(item);
    }

    return gradient;
}
} // namespace OHOS::Ace::NG
