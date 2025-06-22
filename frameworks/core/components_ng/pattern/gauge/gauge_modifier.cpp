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
#include "core/components_ng/pattern/gauge/gauge_modifier.h"

#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_VALUE = 0.0f;
constexpr float ZERO_CIRCLE = 0.0f;
constexpr float MIN_CIRCLE = 2.0f;
constexpr float HALF_CIRCLE = 180.0f;
constexpr float WHOLE_CIRCLE = 360.0f;
constexpr float QUARTER_CIRCLE = 90.0f;
constexpr float PERCENT_HALF = 0.5f;
}
void GaugeModifier::onDraw(DrawingContext& context)
{
    if (useContentModifier_ && useContentModifier_->Get()) {
        return;
    }
    RSCanvas& canvas = context.canvas;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        PaintCircularAndIndicator(canvas);
    } else {
        NewPaintCircularAndIndicator(canvas);
    }
}

void GaugeModifier::UpdateValue()
{
    auto pattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto paintProperty = pattern->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    UpdateProperty(paintProperty);
    float value = paintProperty->GetValueValue();
    if (paintProperty->GetIsSensitiveValue(false)) {
        value = 0.0f;
    }
    float max = paintProperty->GetMaxValue();
    float min = paintProperty->GetMinValue();
    value = std::clamp(value, min, max);
    float ratio = 0.0f;
    if (Positive(max - min)) {
        ratio = (value - min) / (max - min);
    }
    if (NearEqual(ratio, value_->Get())) {
        return;
    }
    start_ = end_;
    end_ = ratio;
    value_->Set(start_);
    AnimationOption option = AnimationOption();
    auto curve =
        AceType::MakeRefPtr<ResponsiveSpringMotion>(RESPONSE, DAMPING_FRACTION);
    option.SetDuration(ANIMATION_DURATION);
    option.SetDelay(ANIMATION_DELAY);
    option.SetCurve(curve);
    option.SetIteration(ANIMATION_TIMES);
    AnimationUtils::Animate(option, [&]() { value_->Set(end_); });
}

void GaugeModifier::InitProperty()
{
    auto pattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto paintProperty = pattern->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    float startAngle = paintProperty->GetStartAngleValue(DEFAULT_START_DEGREE);
    float endAngle = paintProperty->GetEndAngleValue(DEFAULT_END_DEGREE);
    startAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(startAngle);
    endAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(endAngle);
    max_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(paintProperty->GetMaxValue());
    min_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(paintProperty->GetMinValue());

    float strokeWidth = DEFAULT_VALUE;
    if (paintProperty->GetStrokeWidth().has_value()) {
        strokeWidth = paintProperty->GetStrokeWidth()->ConvertToPx();
    }
    strokeWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(strokeWidth);
    float indicatorSpace = paintProperty->GetIndicatorSpaceValue(INDICATOR_DISTANCE_TO_TOP).ConvertToPx();
    indicatorSpace_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(indicatorSpace);
    GaugeType gaugeType = paintProperty->GetGaugeTypeValue(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
    gaugeTypeValue_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(static_cast<int>(gaugeType));
    isShowIndicator_ = AceType::MakeRefPtr<PropertyBool>(paintProperty->GetIsShowIndicatorValue(true));
    indicatorChange_ = AceType::MakeRefPtr<PropertyBool>(paintProperty->GetIndicatorChangeValue(false));

    if (paintProperty->HasShadowOptions()) {
        GaugeShadowOptions shadowOptions = paintProperty->GetShadowOptionsValue();
        shadowRadiusFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(shadowOptions.radius);
        shadowOffsetXFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(shadowOptions.offsetX);
        shadowOffsetYFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(shadowOptions.offsetY);
    } else {
        shadowRadiusFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(DEFAULT_VALUE);
        shadowOffsetXFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(DEFAULT_VALUE);
        shadowOffsetYFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(DEFAULT_VALUE);
    }
    InitPropertyColors(paintProperty);
}

void GaugeModifier::InitPropertyColors(RefPtr<GaugePaintProperty>& paintProperty)
{
    if (paintProperty->GetColors().has_value()) {
        auto colors = paintProperty->GetColorsValue();
        for (size_t i = 0; i < colors.size(); i++) {
            auto color =  AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(colors[i]));
            AttachProperty(color);
            colors_.emplace_back(color);
        }
    }
    if (paintProperty->HasGradientColors()) {
        auto gradientColors = paintProperty->GetGradientColorsValue();
        if (gradientColors.empty()) {
            return;
        }
        auto colors = gradientColors.at(0);
        for (size_t i = 0; i < colors.size(); i++) {
            auto color =  AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(colors[i].first));
            AttachProperty(color);
            gradientColors_.emplace_back(color);
        }
    }
}

void GaugeModifier::UpdateProperty(RefPtr<GaugePaintProperty>& paintProperty)
{
    startAngle_->Set(paintProperty->GetStartAngleValue(DEFAULT_START_DEGREE));
    endAngle_->Set(paintProperty->GetEndAngleValue(DEFAULT_END_DEGREE));
    max_->Set(paintProperty->GetMaxValue());
    min_->Set(paintProperty->GetMinValue());

    if (paintProperty->GetStrokeWidth().has_value()) {
        float strokeWidth = paintProperty->GetStrokeWidth()->ConvertToPx();
        strokeWidth_->Set(strokeWidth);
    } else {
        strokeWidth_->Set(DEFAULT_VALUE);
    }
    indicatorSpace_->Set(paintProperty->GetIndicatorSpaceValue(INDICATOR_DISTANCE_TO_TOP).ConvertToPx());
    GaugeType gaugeType = paintProperty->GetGaugeTypeValue(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
    gaugeTypeValue_->Set(static_cast<int>(gaugeType));
    isShowIndicator_ = AceType::MakeRefPtr<PropertyBool>(paintProperty->GetIsShowIndicatorValue(true));

    if (paintProperty->HasShadowOptions()) {
        GaugeShadowOptions shadowOptions = paintProperty->GetShadowOptionsValue();
        shadowRadiusFloat_->Set(shadowOptions.radius);
        shadowOffsetXFloat_->Set(shadowOptions.offsetX);
        shadowOffsetYFloat_->Set(shadowOptions.offsetY);
    }
    
    if (paintProperty->GetColors().has_value()) {
        auto colors = paintProperty->GetColorsValue();
        for (size_t i = 0; i < colors.size() && i < colors_.size(); i++) {
            colors_[i]->Set(LinearColor(colors[i]));
        }
    }

    if (paintProperty->HasGradientColors()) {
        auto gradientColors = paintProperty->GetGradientColorsValue();
        if (!gradientColors.empty()) {
            auto colors = gradientColors.at(0);
            for (size_t i = 0; i < colors.size() && i < gradientColors_.size(); i++) {
                gradientColors_[i]->Set(LinearColor(colors[i].first));
            }
        }
    }

    if (paintProperty->GetIsShowIndicatorValue(false) ||
        (SystemProperties::ConfigChangePerform() && paintProperty->GetUseSpecialDefaultIndicatorValue(false))) {
        auto indicatorChange = indicatorChange_->Get();
        indicatorChange_->Set(!indicatorChange);
    }
}


void GaugeModifier::PaintCircularAndIndicator(RSCanvas& canvas)
{
    auto pattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto paintProperty = pattern->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto host = pattern->GetHost();
    auto geometryNode = host->GetGeometryNode();
    auto offset = geometryNode->GetContentOffset();
    auto contentSize = geometryNode->GetContentSize();
    RenderRingInfo data;
    data.radius = std::min(contentSize.Width(), contentSize.Height()) * PERCENT_HALF;
    data.center = Offset(contentSize.Width() * PERCENT_HALF + offset.GetX(),
        contentSize.Height() * PERCENT_HALF + offset.GetY());
    float startAngle = DEFAULT_START_DEGREE;
    float endAngle = DEFAULT_END_DEGREE;
    if (paintProperty->GetStartAngle().has_value()
        && !std::isnan(paintProperty->GetStartAngle().value())) {
        startAngle = paintProperty->GetStartAngle().value();
    }
    if (paintProperty->GetEndAngle().has_value()
        && !std::isnan(paintProperty->GetEndAngle().value())) {
        endAngle = paintProperty->GetEndAngle().value();
    }
    float startDegree = startAngle;
    float sweepDegree = endAngle - startAngle;
    if (GreatNotEqual(sweepDegree, WHOLE_CIRCLE)  || LessNotEqual(sweepDegree, ZERO_CIRCLE)) {
        sweepDegree = sweepDegree - floor(sweepDegree / WHOLE_CIRCLE) * WHOLE_CIRCLE;
    }
    if (NearZero(sweepDegree)) {
        sweepDegree = WHOLE_CIRCLE;
    }
    auto theme = pipelineContext->GetTheme<ProgressTheme>();
    data.thickness = theme->GetTrackThickness().ConvertToPx();
    if (paintProperty->GetStrokeWidth().has_value()
        && paintProperty->GetStrokeWidth()->Value() > 0) {
        data.thickness =
            std::min(static_cast<float>(paintProperty->GetStrokeWidth()->ConvertToPx()),
            contentSize.Width() * PERCENT_HALF);
    }
    PaintDraw(canvas, paintProperty, startDegree, endAngle, data);
}

void GaugeModifier::PaintDraw(RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty,
    float startDegree, float sweepDegree, RenderRingInfo data)
{
    std::vector<float> weights;
    if (paintProperty->GetValues().has_value()) {
        weights = paintProperty->GetValuesValue();
    } else {
        weights.push_back(1);
    }
    std::vector<Color> colors;
    if (paintProperty->GetColors().has_value()) {
        colors = paintProperty->GetColorsValue();
    } else {
        colors.push_back(Color::BLACK);
    }
    if (colors.size() == 0 || colors.size() != weights.size()) {
        TAG_LOGW(AceLogTag::ACE_GAUGE, "Gauge get the color size is 0 or is not equal to weight size");
        return;
    }
    float totalWeight = ZERO_CIRCLE;
    for (auto& weight : weights) {
        totalWeight += weight;
    }
    if (NearEqual(totalWeight, 0.0)) {
        return;
    }
    float currentStart = ZERO_CIRCLE;
    float highLightStart = ZERO_CIRCLE;
    size_t highLightIndex = 0;
    auto ratio = value_->Get();
    for (int32_t index = static_cast<int32_t>(colors.size()) - 1; index >= 0; --index) {
        data.color = colors[index];
        data.color.ChangeAlpha(UNSELECT_ALPHA);
        currentStart += weights[index];
        if (ShouldHighLight(totalWeight - currentStart, weights[index], ratio * totalWeight)) {
            highLightIndex = static_cast<size_t>(index);
            highLightStart = totalWeight - currentStart;
        }
        data.startDegree = startDegree + (1 - currentStart / totalWeight) * sweepDegree;
        data.sweepDegree = (weights[index] / totalWeight) * sweepDegree;
        DrawGauge(canvas, data);
    }
    // draw highlight part
    data.color = colors[highLightIndex];
    data.startDegree = startDegree + (highLightStart / totalWeight) * sweepDegree;
    data.sweepDegree = (weights[highLightIndex] / totalWeight) * sweepDegree;
    DrawGauge(canvas, data);
    data.startDegree = startDegree;
    data.sweepDegree = sweepDegree * ratio;
    DrawIndicator(canvas, data);
}

void GaugeModifier::DrawGauge(RSCanvas& canvas, RenderRingInfo data)
{
    float thickness = data.thickness;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(data.color.GetValue());
    pen.SetWidth(thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

    canvas.AttachPen(pen);
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
    RSRect rRect(data.center.GetX() - data.radius + thickness * PERCENT_HALF,
        data.center.GetY() - data.radius + thickness * PERCENT_HALF,
        data.center.GetX() + data.radius - thickness * PERCENT_HALF,
        data.center.GetY() + data.radius - thickness * PERCENT_HALF);
    path.AddArc(rRect, data.startDegree - QUARTER_CIRCLE, data.sweepDegree);
    canvas.DrawPath(path);
    canvas.DetachPen();
}

void GaugeModifier::DrawIndicator(RSCanvas& canvas, RenderRingInfo data)
{
#ifndef USE_ROSEN_DRAWING
    RSPath path;
#else
    RSRecordingPath path;
#endif
    float pathStartVertexX = data.center.GetX();
    float pathStartVertexY = data.center.GetY() - data.radius + (data.thickness / 2);
    path.MoveTo(pathStartVertexX, pathStartVertexY);
    path.LineTo(pathStartVertexX - EDGE, pathStartVertexY + EDGE);
    path.LineTo(pathStartVertexX - EDGE, pathStartVertexY + EDGE + HEIGHT_OFFSET);
    path.LineTo(pathStartVertexX + EDGE, pathStartVertexY + EDGE + HEIGHT_OFFSET);
    path.LineTo(pathStartVertexX + EDGE, pathStartVertexY + EDGE);
    path.LineTo(pathStartVertexX, pathStartVertexY);

    canvas.Save();
    canvas.Rotate(data.startDegree + data.sweepDegree, data.center.GetX(), data.center.GetY());
    RSBrush paint;
    paint.SetColor(Color::WHITE.GetValue());
    canvas.AttachBrush(paint);
    canvas.DrawPath(path);
    canvas.DetachBrush();

    RSPen pen;
    pen.SetColor(Color::BLACK.GetValue());
    pen.SetWidth(INDICATOR_STROKE_WIDTH);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();
}

bool GaugeModifier::ShouldHighLight(float start, float interval, float percent)
{
    if (LessOrEqual(percent, start + interval) && GreatOrEqual(percent, start)) {
        return true;
    }
    return false;
}

void GaugeModifier::NewPaintCircularAndIndicator(RSCanvas& canvas)
{
    auto pattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto paintProperty = pattern->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto host = pattern->GetHost();
    auto geometryNode = host->GetGeometryNode();
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto offset = geometryNode->GetContentOffset();

    canvas.Save();
    auto paddingSize = geometryNode->GetPaddingSize();
    CHECK_NULL_VOID(geometryNode->GetPadding());
    auto left = geometryNode->GetPadding()->left.value_or(0.0f);
    auto top = geometryNode->GetPadding()->top.value_or(0.0f);
    auto radius = std::min(paddingSize.Width(), paddingSize.Height()) * PERCENT_HALF;
    RenderRingInfo data;
    data.contentSize = paddingSize;
    data.radius = radius;
    data.center = Offset(offset.GetX() + left + radius, offset.GetY() + top + radius);
    auto theme = pipelineContext->GetTheme<GaugeTheme>();
    data.thickness = theme->GetTrackThickness().ConvertToPx();
    CalculateStartAndSweepDegree(paintProperty, data);
    if (paintProperty->GetIsSensitiveValue(false)) {
        PaintMonochromeCircular(canvas, data, paintProperty);
    } else {
        switch (paintProperty->GetGaugeTypeValue(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT)) {
            case GaugeType::TYPE_CIRCULAR_MULTI_SEGMENT_GRADIENT: {
                PaintMultiSegmentGradientCircular(canvas, data, paintProperty);
                break;
            }
            case GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT: {
                PaintSingleSegmentGradientCircular(canvas, data, paintProperty);
                break;
            }
            case GaugeType::TYPE_CIRCULAR_MONOCHROME: {
                PaintMonochromeCircular(canvas, data, paintProperty);
                break;
            }
            default:
                // do nothing.
                break;
        }
    }
    canvas.Restore();
}

void GaugeModifier::PaintMonochromeCircular(
    RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty)
{
    CHECK_NULL_VOID(paintProperty);
    Color color(Color::BLACK);
    if (paintProperty->HasGradientColors()) {
        color = paintProperty->GetGradientColorsValue().at(0).at(0).first;
    }
    auto gaugeType = paintProperty->GetGaugeTypeValue(GaugeType::TYPE_CIRCULAR_SINGLE_SEGMENT_GRADIENT);
    auto isSensitive = paintProperty->GetIsSensitive().value_or(false);
    if (isSensitive && gaugeType != GaugeType::TYPE_CIRCULAR_MONOCHROME) {
        color = Color::GRAY;
    }
    Color backgroundColor = color.ChangeOpacity(MONOCHROME_CIRCULAR_BACKGROUND_COLOR_OPACITY);
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    auto ratio = value_->Get();
    RSBrush brush;
    brush.SetAntiAlias(true);
    
    RSPath path;
    auto startAngle = data.startDegree - QUARTER_CIRCLE + offsetDegree;
    auto sweepAngle = GreatNotEqual(data.sweepDegree, MIN_CIRCLE * offsetDegree)
                               ? data.sweepDegree - MIN_CIRCLE * offsetDegree
                               : ZERO_CIRCLE;
    GetDrawPath(path, data, startAngle, sweepAngle, true);
    auto tempSweepDegree = GreatNotEqual(data.sweepDegree * ratio, MIN_CIRCLE * offsetDegree)
                               ? data.sweepDegree * ratio - MIN_CIRCLE * offsetDegree
                               : ZERO_CIRCLE;

    PaintMonochromeCircularShadow(canvas, data, color, paintProperty, tempSweepDegree);
    brush.SetColor(backgroundColor.GetValue());
    canvas.Save();
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    canvas.Restore();

    path.Reset();
    GetDrawPath(path, data, startAngle, tempSweepDegree, true);
    brush.SetColor(color.GetValue());
    canvas.Save();
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    canvas.Restore();
    data.sweepDegree = data.sweepDegree * ratio;
    NewDrawIndicator(canvas, paintProperty, data);
}

void GaugeModifier::PaintMonochromeCircularShadow(RSCanvas& canvas, RenderRingInfo& data, Color& color,
    RefPtr<GaugePaintProperty>& paintProperty, float sweepDegree)
{
    CHECK_NULL_VOID(paintProperty);
    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }
    if (!shadowOptions.isShadowVisible) {
        return;
    }
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, shadowOptions.radius));
    RSBrush shadowPen;
    shadowPen.SetAntiAlias(true);
    shadowPen.SetColor(color.GetValue());
    shadowPen.SetFilter(filter);
    shadowPen.SetAlphaF(SHADOW_ALPHA);

    RSPath shadowPath;
    GetDrawPath(shadowPath, data, data.startDegree - QUARTER_CIRCLE + offsetDegree, sweepDegree, true);

    canvas.Save();
    canvas.Translate(shadowOptions.offsetX, shadowOptions.offsetY);
    canvas.AttachBrush(shadowPen);
    canvas.DrawPath(shadowPath);
    canvas.DetachBrush();
    canvas.Restore();
}

void GaugeModifier::PaintSingleSegmentGradientCircular(
    RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty)
{
    CHECK_NULL_VOID(paintProperty);
    std::vector<RSColorQuad> colors;
    std::vector<float> pos;
    if (paintProperty->HasGradientColors()) {
        auto colorsArray = paintProperty->GetGradientColorsValue().at(0);
        for (auto& colorStop : colorsArray) {
            colors.emplace_back(colorStop.first.GetValue());
            pos.emplace_back(colorStop.second.Value());
        }
    } else {
        CreateDefaultColor(colors, pos);
    }

    PaintSingleSegmentGradientCircularShadow(canvas, data, paintProperty, colors, pos);
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(data.thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(ToRSPoint(PointF(data.center.GetX(), data.center.GetY())),
        colors, pos, RSTileMode::CLAMP, offsetDegree, data.sweepDegree - offsetDegree, nullptr));

    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);

    RSPath path;
    path.AddArc(rRect, offsetDegree, data.sweepDegree - MIN_CIRCLE * offsetDegree);
    canvas.Rotate(data.startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();

    auto ratio = value_->Get();
    data.startDegree = QUARTER_CIRCLE;
    data.sweepDegree = data.sweepDegree * ratio;
    NewDrawIndicator(canvas, paintProperty, data);
}

void GaugeModifier::PaintSingleSegmentGradientCircularShadow(RSCanvas& canvas, RenderRingInfo& data,
    RefPtr<GaugePaintProperty>& paintProperty, std::vector<RSColorQuad>& colors,
    std::vector<float>& pos)
{
    CHECK_NULL_VOID(paintProperty);
    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }
    if (!shadowOptions.isShadowVisible) {
        return;
    }

    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    RSFilter filter;
    filter.SetImageFilter(
        RSImageFilter::CreateBlurImageFilter(shadowOptions.radius, shadowOptions.radius, RSTileMode::CLAMP, nullptr));
    RSPen shadowPen;
    shadowPen.SetAntiAlias(true);
    shadowPen.SetWidth(data.thickness);
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetAlphaF(SHADOW_ALPHA);
    shadowPen.SetFilter(filter);
    shadowPen.SetShaderEffect(
        RSShaderEffect::CreateSweepGradient(ToRSPoint(PointF(data.center.GetX(), data.center.GetY())), colors, pos,
            RSTileMode::CLAMP, offsetDegree, data.sweepDegree - offsetDegree, nullptr));

    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);

    RSPath path;
    path.AddArc(rRect, offsetDegree, data.sweepDegree - MIN_CIRCLE * offsetDegree);

    canvas.Save();
    canvas.Translate(shadowOptions.offsetX, shadowOptions.offsetY);
    canvas.Rotate(data.startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();
}

void GaugeModifier::PaintMultiSegmentGradientCircular(
    RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty)
{
    CHECK_NULL_VOID(paintProperty);
    float startDegree = data.startDegree;
    float sweepDegree = data.sweepDegree;
    std::vector<float> weights;
    if (paintProperty->HasValues()) {
        weights = paintProperty->GetValuesValue();
    } else {
        weights.push_back(1);
    }
    std::vector<ColorStopArray> colors;
    if (paintProperty->HasGradientColors()) {
        colors = paintProperty->GetGradientColorsValue();
    } else {
        ColorStopArray colorStopArray;
        colorStopArray.emplace_back(std::make_pair(Color::BLACK, Dimension(0.0)));
        colors.push_back(colorStopArray);
    }

    if (colors.size() == 0 || colors.size() != weights.size()) {
        TAG_LOGW(AceLogTag::ACE_GAUGE, "Gauge get the color size is 0 or is not equal to weight size");
        return;
    }
    float totalWeight = ZERO_CIRCLE;
    for (auto& weight : weights) {
        totalWeight += weight;
    }
    if (NearEqual(totalWeight, 0.0)) {
        return;
    }

    PaintMultiSegmentGradientCircularShadow(canvas, data, paintProperty, colors, weights);

    auto ratio = value_->Get();
    data.startDegree = QUARTER_CIRCLE;
    data.sweepDegree = sweepDegree * ratio;
    SingleSegmentGradientInfo info;
    info.isDrawShadow = false;
    canvas.Rotate(startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());
    for (size_t index = 0; index < colors.size(); index++) {
        info.drawStartDegree = info.drawStartDegree + info.drawSweepDegree;
        info.drawSweepDegree = (weights[index] / totalWeight) * sweepDegree;
        info.offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
        info.colorStopArray = colors.at(index);
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            DrawSingleSegmentGradient(canvas, data, paintProperty, info, index);
        } else {
            DrawSingleSegmentGradientExtend(canvas, data, paintProperty, info, index);
        }
    }
    NewDrawIndicator(canvas, paintProperty, data);
}

void GaugeModifier::PaintMultiSegmentGradientCircularShadow(RSCanvas& canvas, RenderRingInfo& data,
    RefPtr<GaugePaintProperty>& paintProperty, std::vector<ColorStopArray>& colors,
    std::vector<float>& weights)
{
    CHECK_NULL_VOID(paintProperty);
    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }

    if (!shadowOptions.isShadowVisible) {
        return;
    }
    float totalWeight = ZERO_CIRCLE;
    for (auto& weight : weights) {
        totalWeight += weight;
    }
    canvas.Save();
    canvas.Translate(shadowOptions.offsetX, shadowOptions.offsetY);
    canvas.Rotate(data.startDegree - QUARTER_CIRCLE, data.center.GetX(), data.center.GetY());

    SingleSegmentGradientInfo info;
    info.isDrawShadow = true;
    info.shadowRadius = shadowOptions.radius;
    for (size_t index = 0; index < colors.size(); index++) {
        info.drawStartDegree = info.drawStartDegree + info.drawSweepDegree;
        info.drawSweepDegree = (weights[index] / totalWeight) * data.sweepDegree;
        info.offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
        info.colorStopArray = colors.at(index);
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            DrawSingleSegmentGradient(canvas, data, paintProperty, info, index);
        } else {
            DrawSingleSegmentGradientExtend(canvas, data, paintProperty, info, index);
        }
    }
    canvas.Restore();
}

void GaugeModifier::DrawSingleSegmentGradient(RSCanvas& canvas, RenderRingInfo& data,
    RefPtr<GaugePaintProperty>& paintProperty, SingleSegmentGradientInfo& info, size_t index)
{
    auto drawStartDegree = info.drawStartDegree;
    auto drawSweepDegree = info.drawSweepDegree;
    auto offsetDegree = info.offsetDegree;
    std::vector<RSColorQuad> colorValues;
    std::vector<float> pos;
    for (auto& colorStop : info.colorStopArray) {
        colorValues.emplace_back(colorStop.first.GetValue());
        pos.emplace_back(colorStop.second.Value());
    }

    RSPen pen;
    RSPath path;
    pen.SetAntiAlias(true);
    pen.SetWidth(data.thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    RSRect rRect(data.center.GetX() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetY() - data.radius + data.thickness * PERCENT_HALF,
                 data.center.GetX() + data.radius - data.thickness * PERCENT_HALF,
                 data.center.GetY() + data.radius - data.thickness * PERCENT_HALF);

    if (info.isDrawShadow) {
        RSFilter filter;
        filter.SetImageFilter(
            RSImageFilter::CreateBlurImageFilter(info.shadowRadius, info.shadowRadius, RSTileMode::CLAMP, nullptr));
        pen.SetFilter(filter);
        pen.SetAlphaF(SHADOW_ALPHA);
    } else {
        NewDrawIndicator(canvas, paintProperty, data);
    }

    if (index != 0) {
        if (!info.isDrawShadow) {
            DrawHighLight(canvas, data, drawStartDegree);
        }
        pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
            ToRSPoint(PointF(data.center.GetX(), data.center.GetY())), colorValues, pos, RSTileMode::CLAMP,
            drawStartDegree - offsetDegree, drawStartDegree + drawSweepDegree - offsetDegree, nullptr));
        path.AddArc(rRect, drawStartDegree - offsetDegree, drawSweepDegree);
    } else {
        pen.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
            ToRSPoint(PointF(data.center.GetX(), data.center.GetY())), colorValues, pos, RSTileMode::CLAMP,
            drawStartDegree + offsetDegree, drawStartDegree + drawSweepDegree + offsetDegree, nullptr));
        path.AddArc(rRect, drawStartDegree + offsetDegree, drawSweepDegree - MIN_CIRCLE * offsetDegree);
    }

    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();
}

void GaugeModifier::DrawSingleSegmentGradientExtend(RSCanvas& canvas, RenderRingInfo& data,
    RefPtr<GaugePaintProperty>& paintProperty, SingleSegmentGradientInfo& info, size_t index)
{
    auto drawStartDegree = info.drawStartDegree;
    auto drawSweepDegree = info.drawSweepDegree;
    auto offsetDegree = info.offsetDegree;
    std::vector<RSColorQuad> colorValues;
    std::vector<float> pos;
    for (auto& colorStop : info.colorStopArray) {
        colorValues.emplace_back(colorStop.first.GetValue());
        pos.emplace_back(colorStop.second.Value());
    }
    RSBrush brush;
    if (info.isDrawShadow) {
        RSFilter filter;
        filter.SetImageFilter(
            RSImageFilter::CreateBlurImageFilter(info.shadowRadius, info.shadowRadius, RSTileMode::CLAMP, nullptr));
        brush.SetFilter(filter);
        brush.SetAlphaF(SHADOW_ALPHA);
    }
    canvas.Save();
    if (index == 0) {
        brush.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
            ToRSPoint(PointF(data.center.GetX(), data.center.GetY())), colorValues, pos, RSTileMode::CLAMP,
            drawStartDegree + offsetDegree, drawStartDegree + drawSweepDegree + offsetDegree, nullptr));
        float startDegree = drawStartDegree + offsetDegree;
        float sweepDegree = drawSweepDegree - offsetDegree * MIN_CIRCLE;
        if (info.isDrawShadow) {
            sweepDegree = std::max(sweepDegree, 0.0f);
        }
        DrawSegmentGradient(canvas, brush, data, paintProperty, info, true, startDegree, sweepDegree);
    } else {
        brush.SetShaderEffect(RSShaderEffect::CreateSweepGradient(
            ToRSPoint(PointF(data.center.GetX(), data.center.GetY())), colorValues, pos, RSTileMode::CLAMP,
            drawStartDegree - offsetDegree, drawStartDegree + drawSweepDegree - offsetDegree, nullptr));
        float startDegree = drawStartDegree - offsetDegree;
        float sweepDegree = 0.0f;
        if (Positive(startDegree - offsetDegree)) {
            sweepDegree = drawSweepDegree;
        } else {
            sweepDegree = drawSweepDegree + startDegree - offsetDegree;
            startDegree = offsetDegree;
        }
        DrawSegmentGradient(canvas, brush, data, paintProperty, info, false, startDegree, sweepDegree);
    }
}

void GaugeModifier::DrawSegmentGradient(RSCanvas& canvas, RSBrush& brush, RenderRingInfo& data,
    RefPtr<GaugePaintProperty>& paintProperty, SingleSegmentGradientInfo& info, bool isFirst, float startDegree,
    float sweepDegree)
{
    auto drawStartDegree = info.drawStartDegree;
    auto drawSweepDegree = info.drawSweepDegree;
    auto offsetDegree = info.offsetDegree;
    RSPath path;
    RSPath clipPath;
    RSPath clipPath2;

    if (isFirst) {
        if (!info.isDrawShadow) {
            GetDrawPath(clipPath, data, startDegree, drawSweepDegree, true);
            GetDrawPath(clipPath2, data, drawStartDegree, drawSweepDegree - offsetDegree, true);
            canvas.ClipPath(clipPath, RSClipOp::INTERSECT, true);
            canvas.ClipPath(clipPath2, RSClipOp::INTERSECT, true);
        }
        GetDrawPath(path, data, startDegree, sweepDegree, true);
    } else {
        if (info.isDrawShadow) {
            sweepDegree = std::max(sweepDegree, 0.0f);
            GetDrawPath(path, data, startDegree, sweepDegree, false);
        } else {
            GetDrawPath(path, data, startDegree, sweepDegree, true);
            GetDrawPath(clipPath, data, startDegree, drawSweepDegree, true);
            auto radius = data.radius - data.thickness * PERCENT_HALF;
            auto pattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
            CHECK_NULL_VOID(pattern);
            auto context = pattern->GetContext();
            CHECK_NULL_VOID(context);
            auto theme = context->GetTheme<GaugeTheme>();
            CHECK_NULL_VOID(theme);
            float space = data.radius * MIN_CIRCLE * theme->GetIntervalRatio();
            auto degree = info.lastStartDegree + info.lastSweepDegree;
            clipPath2.AddCircle(data.center.GetX() + radius * std::cos((degree)*M_PI / HALF_CIRCLE),
                data.center.GetY() + radius * std::sin((degree)*M_PI / HALF_CIRCLE),
                (data.thickness * PERCENT_HALF + space));
            canvas.ClipPath(clipPath, RSClipOp::INTERSECT, true);
            canvas.ClipPath(clipPath2, RSClipOp::DIFFERENCE, true);
        }
    }

    info.lastStartDegree = startDegree;
    info.lastSweepDegree = sweepDegree;
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    canvas.Restore();
}

void GaugeModifier::CalculateStartAndSweepDegree(
    RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data)
{
    CHECK_NULL_VOID(paintProperty);
    float startAngle = DEFAULT_START_DEGREE;
    float endAngle = DEFAULT_END_DEGREE;

    if (paintProperty->HasStartAngle() && !std::isnan(paintProperty->GetStartAngleValue())) {
        startAngle = paintProperty->GetStartAngleValue();
    }

    if (paintProperty->HasEndAngle() && !std::isnan(paintProperty->GetEndAngleValue())) {
        endAngle = paintProperty->GetEndAngleValue();
    }

    if (paintProperty->HasStrokeWidth() && (paintProperty->GetStrokeWidth()->Value() > 0)) {
        data.thickness = std::min(static_cast<float>(paintProperty->GetStrokeWidth()->ConvertToPx()),
            data.contentSize.Width() * PERCENT_HALF);
    }

    float sweepDegree = endAngle - startAngle;
    if (GreatNotEqual(sweepDegree, DEFAULT_END_DEGREE) || LessNotEqual(sweepDegree, DEFAULT_START_DEGREE)) {
        sweepDegree = sweepDegree - floor(sweepDegree / WHOLE_CIRCLE) * WHOLE_CIRCLE;
    }

    if (NearZero(sweepDegree)) {
        sweepDegree = WHOLE_CIRCLE;
    }
    data.startDegree = startAngle;
    data.sweepDegree = sweepDegree;
}

void GaugeModifier::DrawHighLight(RSCanvas& canvas, RenderRingInfo& data, float drawStartDegree)
{
    float offsetDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF);
    auto radius = data.radius - data.thickness * PERCENT_HALF;
    auto pattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto context = pattern->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<GaugeTheme>();
    CHECK_NULL_VOID(theme);
    float space = data.radius * MIN_CIRCLE * theme->GetIntervalRatio();
    RSPath path1;
    path1.AddCircle(data.center.GetX() + radius * std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    data.center.GetY() + radius * std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    data.thickness * PERCENT_HALF);

    RSPath path2;
    path2.AddCircle(data.center.GetX() + radius * std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    data.center.GetY() + radius * std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                    (data.thickness * PERCENT_HALF + space));

    canvas.ClipPath(path2, RSClipOp::DIFFERENCE, true);

    RSPath path3;
    path3.Op(path2, path1, RSPathOp::DIFFERENCE);

    float tempDegree = GetOffsetDegree(data, data.thickness * PERCENT_HALF + space);
    RSPath path4;
    path4.MoveTo(data.center.GetX() + (data.radius) * std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
                 data.center.GetY() + (data.radius) * std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE));
    path4.LineTo(
        data.center.GetX() + (data.radius - data.thickness) *
            std::cos((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE),
        data.center.GetY() + (data.radius - data.thickness) *
            std::sin((drawStartDegree - offsetDegree) * M_PI / HALF_CIRCLE));
    path4.LineTo(
        data.center.GetX() + (data.radius - data.thickness) *
            std::cos((drawStartDegree - offsetDegree - tempDegree) * M_PI / HALF_CIRCLE),
        data.center.GetY() + (data.radius - data.thickness) *
            std::sin((drawStartDegree - offsetDegree - tempDegree) * M_PI / HALF_CIRCLE));
    path4.LineTo(
        data.center.GetX() + (data.radius) *
            std::cos((drawStartDegree - offsetDegree - tempDegree) * M_PI / HALF_CIRCLE),
        data.center.GetY() + (data.radius) *
            std::sin((drawStartDegree - offsetDegree - tempDegree) * M_PI / HALF_CIRCLE));

    RSPath path5;
    path5.Op(path3, path4, RSPathOp::DIFFERENCE);

    canvas.ClipPath(path5, RSClipOp::DIFFERENCE, true);
}

float GaugeModifier::GetOffsetDegree(RenderRingInfo& data, float oppositeSide)
{
    return NearEqual(data.radius, data.thickness * PERCENT_HALF)
               ? ZERO_CIRCLE
               : std::tan((oppositeSide) / (data.radius - data.thickness * PERCENT_HALF)) * HALF_CIRCLE / M_PI;
}

void GaugeModifier::NewDrawIndicator(
    RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data)
{
    CHECK_NULL_VOID(paintProperty);
    if (!(paintProperty->GetIsShowIndicatorValue(true))) {
        return;
    }
    if (paintProperty->HasIndicatorIconSourceInfo()) {
        NewDrawImageIndicator(canvas, paintProperty, data);
        return;
    }

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<GaugeTheme>();

    Dimension indicatorToTop = paintProperty->GetIndicatorSpaceValue(INDICATOR_DISTANCE_TO_TOP);
    if (GreatNotEqual(indicatorToTop.ConvertToPx(), data.radius)) {
        indicatorToTop = INDICATOR_DISTANCE_TO_TOP;
    }

    float pathStartVertexX = data.center.GetX();
    float pathStartVertexY = data.center.GetY() - data.radius + indicatorToTop.ConvertToPx() -
                             INDICATOR_BORDER_WIDTH_RATIO * data.radius * PERCENT_HALF;
    RSPath path;
    CreateDefaultTrianglePath(pathStartVertexX, pathStartVertexY, data.radius, path);
    canvas.Save();
    canvas.Rotate(data.startDegree + data.sweepDegree, data.center.GetX(), data.center.GetY());
    RSPen pen;
    pen.SetBlendMode(RSBlendMode::SRC_OVER);
    pen.SetColor(theme->GetIndicatorBorderColor().GetValue());
    pen.SetAntiAlias(true);
    pen.SetWidth(theme->GetIndicatorBorderRatio() * data.radius);
    pen.SetJoinStyle(RSPen::JoinStyle::ROUND_JOIN);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();

    RSBrush paint;
    paint.SetAntiAlias(true);
    paint.SetColor(theme->GetIndicatorColor().GetValue());
    paint.SetBlendMode(RSBlendMode::SRC_OVER);
    canvas.AttachBrush(paint);
    canvas.DrawPath(path);
    canvas.DetachBrush();
    canvas.Restore();
}

void GaugeModifier::NewDrawImageIndicator(
    RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data)
{
    CHECK_NULL_VOID(paintProperty);
    canvas.Save();
    canvas.Rotate(data.startDegree + data.sweepDegree, data.center.GetX(), data.center.GetY());
    auto gaugePattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(gaugePattern);
    RefPtr<CanvasImage> indicatorIconCanvasImage = gaugePattern->GetIndicatorIconCanvasImage();
    Dimension indicatorToTop = paintProperty->GetIndicatorSpaceValue(INDICATOR_DISTANCE_TO_TOP);
    if (GreatNotEqual(indicatorToTop.ConvertToPx(), data.radius)) {
        indicatorToTop = INDICATOR_DISTANCE_TO_TOP;
    }

    CHECK_NULL_VOID(indicatorIconCanvasImage);
    auto&& config = indicatorIconCanvasImage->GetPaintConfig();
    config.renderMode_ = ImageRenderMode::ORIGINAL;
    config.imageInterpolation_ = ImageInterpolation::NONE;
    config.imageRepeat_ = ImageRepeat::NO_REPEAT;
    config.imageFit_ = ImageFit::FILL;
    config.isSvg_ = true;
    auto diameter = data.radius * RADIUS_TO_DIAMETER;
    float pathStartVertexX = data.center.GetX();
    float pathStartVertexY = data.center.GetY() - data.radius + indicatorToTop.ConvertToPx();

    ImagePainter indicatorIconImagePainter(indicatorIconCanvasImage);
    indicatorIconImagePainter.DrawImage(canvas,
        OffsetF(pathStartVertexX - INDICATOR_WIDTH_RADIO * data.radius, pathStartVertexY),
        SizeF(INDICATOR_WIDTH_RADIO * diameter, INDICATOR_HEIGHT_RADIO * diameter));
    canvas.Restore();
}

void GaugeModifier::CreateDefaultColor(std::vector<RSColorQuad>& colors, std::vector<float>& pos)
{
    float space = ZERO_CIRCLE;
    for (auto& color : GAUGE_DEFAULT_COLOR) {
        colors.emplace_back(color.GetValue());
        pos.emplace_back(space);
        space += PERCENT_HALF;
    }
}

void GaugeModifier::CreateDefaultTrianglePath(
    float pathStartVertexX, float pathStartVertexY, float radius, RSPath& path)
{
    auto pattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto context = pattern->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<GaugeTheme>();
    CHECK_NULL_VOID(theme);
    float width = radius * RADIUS_TO_DIAMETER * theme->GetIndicatorWidthRatio();
    float height = radius * RADIUS_TO_DIAMETER * theme->GetIndicatorHeightRatio();
    auto hypotenuse = std::sqrt(((width * PERCENT_HALF) * (width * PERCENT_HALF)) + (height * height));
    
    float cornerRadius = radius * RADIUS_TO_DIAMETER * theme->GetIndicatorRadiusRatio();
    auto bottomAngle = std::atan(height / (width * PERCENT_HALF));

    if (!NearZero(hypotenuse) && hypotenuse != 0) {
        auto tempTopHypotenuse = cornerRadius / (width * PERCENT_HALF) * height;
        auto tempTopWidth = tempTopHypotenuse / hypotenuse * (width * PERCENT_HALF);
        auto tempTopHeight = tempTopHypotenuse / hypotenuse * height;
        auto tempBottomHypotenuse = cornerRadius / std::tan(bottomAngle * PERCENT_HALF);
        auto tempBottomWidth = tempBottomHypotenuse / hypotenuse * (width * PERCENT_HALF);
        auto tempBottomHeight = tempBottomHypotenuse / hypotenuse * height;

        PointF topControlPoint = PointF(pathStartVertexX, pathStartVertexY);
        PointF leftControlPoint = PointF(pathStartVertexX - width * PERCENT_HALF, pathStartVertexY + height);
        PointF rightControlPoint = PointF(pathStartVertexX + width * PERCENT_HALF, pathStartVertexY + height);

        PointF trianglePoint1 = topControlPoint + OffsetF(-tempTopWidth, tempTopHeight);
        PointF trianglePoint2 = leftControlPoint + OffsetF(tempBottomWidth, -tempBottomHeight);
        PointF trianglePoint3 = leftControlPoint + OffsetF(tempBottomHypotenuse, ZERO_CIRCLE);
        PointF trianglePoint4 = rightControlPoint + OffsetF(-tempBottomHypotenuse, ZERO_CIRCLE);
        PointF trianglePoint5 = rightControlPoint + OffsetF(-tempBottomWidth, -tempBottomHeight);
        PointF trianglePoint6 = topControlPoint + OffsetF(tempTopWidth, tempTopHeight);

        path.MoveTo(trianglePoint1.GetX(), trianglePoint1.GetY());
        path.LineTo(trianglePoint2.GetX(), trianglePoint2.GetY());
        path.QuadTo(leftControlPoint.GetX(), leftControlPoint.GetY(), trianglePoint3.GetX(), trianglePoint3.GetY());
        path.LineTo(trianglePoint4.GetX(), trianglePoint4.GetY());
        path.QuadTo(rightControlPoint.GetX(), rightControlPoint.GetY(), trianglePoint5.GetX(), trianglePoint5.GetY());
        path.LineTo(trianglePoint6.GetX(), trianglePoint6.GetY());
        path.QuadTo(topControlPoint.GetX(), topControlPoint.GetY(), trianglePoint1.GetX(), trianglePoint1.GetY());
    }
}

void GaugeModifier::GetDrawPath(RSPath& path, RenderRingInfo& data, float startAngle, float sweepAngle, bool isFirst)
{
    auto startRadian = M_PI * startAngle / HALF_CIRCLE;
    RSPoint startPoint1(data.center.GetX() + (data.radius - data.thickness * PERCENT_HALF) * std::cos(startRadian) -
                            data.thickness * PERCENT_HALF,
        data.center.GetY() + (data.radius - data.thickness * PERCENT_HALF) * std::sin(startRadian) -
            data.thickness * PERCENT_HALF);
    RSPoint startPoint2(data.center.GetX() + (data.radius - data.thickness * PERCENT_HALF) * std::cos(startRadian) +
                            data.thickness * PERCENT_HALF,
        data.center.GetY() + (data.radius - data.thickness * PERCENT_HALF) * std::sin(startRadian) +
            data.thickness * PERCENT_HALF);
    if (isFirst) {
        path.ArcTo(startPoint1, startPoint2, startAngle + HALF_CIRCLE, HALF_CIRCLE);
    } else {
        path.ArcTo(startPoint1, startPoint2, startAngle + HALF_CIRCLE, -HALF_CIRCLE);
    }

    if (Positive(sweepAngle)) {
        RSPoint outPoint1(data.center.GetX() - data.radius, data.center.GetY() - data.radius);
        RSPoint outPoint2(data.center.GetX() + data.radius, data.center.GetY() + data.radius);
        path.ArcTo(outPoint1, outPoint2, startAngle, sweepAngle);
    }

    auto endAngle = startAngle + sweepAngle;
    auto endRadian = M_PI * endAngle / HALF_CIRCLE;
    RSPoint endPoint1(data.center.GetX() + (data.radius - data.thickness * PERCENT_HALF) * std::cos(endRadian) -
                          data.thickness * PERCENT_HALF,
        data.center.GetY() + (data.radius - data.thickness * PERCENT_HALF) * std::sin(endRadian) -
            data.thickness * PERCENT_HALF);
    RSPoint endPoint2(data.center.GetX() + (data.radius - data.thickness * PERCENT_HALF) * std::cos(endRadian) +
                          data.thickness * PERCENT_HALF,
        data.center.GetY() + (data.radius - data.thickness * PERCENT_HALF) * std::sin(endRadian) +
            data.thickness * PERCENT_HALF);
    path.ArcTo(endPoint1, endPoint2, endAngle, HALF_CIRCLE);

    if (Positive(sweepAngle)) {
        RSPoint inPoint1(
            data.center.GetX() - data.radius + data.thickness, data.center.GetY() - data.radius + data.thickness);
        RSPoint inPoint2(
            data.center.GetX() + data.radius - data.thickness, data.center.GetY() + data.radius - data.thickness);
        path.ArcTo(inPoint1, inPoint2, startAngle + sweepAngle, -sweepAngle);
    }
    path.Close();
}
}
