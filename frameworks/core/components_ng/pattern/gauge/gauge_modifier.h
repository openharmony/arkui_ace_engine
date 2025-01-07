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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_MODIFIER_H
                       
#include "base/geometry/ng/offset_t.h"
#include "core/animation/spring_curve.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"


namespace OHOS::Ace::NG {
constexpr int32_t ANIMATION_DURATION = 1200;        // The circle animation duration is 1200ms
constexpr int32_t ANIMATION_DELAY = 0;              // The circle animation delay is 0ms
constexpr int32_t ANIMATION_TIMES = 1;              // The circle animation repeat times is 1
constexpr float ANIMATION_START = 0.0f;             // The circle animation start from 0.0
constexpr float ANIMATION_END = 1.0f;               // The circle animation end with 1.0
constexpr float RESPONSE = 0.416f;                  //SPRING_MOTION_RESPONSE
constexpr float DAMPING_FRACTION = 0.99f;           //SPRING_MOTION_DAMPING_FRACTION
struct RenderRingInfo {
    float radius = 0.0f;
    float startDegree = 0.0f;
    float sweepDegree = 0.0f;
    float thickness = 0.0f;
    Offset center;
    SizeF contentSize;
    Color color;
};

struct SingleSegmentGradientInfo {
    bool isDrawShadow = false;
    float drawStartDegree = 0.0f;
    float drawSweepDegree = 0.0f;
    float lastStartDegree = 0.0f;
    float lastSweepDegree = 0.0f;
    float offsetDegree = 0.0f;
    float shadowRadius = 0.0f;
    ColorStopArray colorStopArray;
};
class GaugeModifier : public ForegroundModifier {
    DECLARE_ACE_TYPE(GaugeModifier, ForegroundModifier);
public:
    GaugeModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern): pattern_(pattern)
    {
        InitProperty();
        useContentModifier_ = AceType::MakeRefPtr<PropertyBool>(false);
        AttachProperty(min_);
        AttachProperty(max_);
        AttachProperty(startAngle_);
        AttachProperty(endAngle_);
        AttachProperty(strokeWidth_);
        AttachProperty(indicatorSpace_);
        AttachProperty(indicatorChange_);
        AttachProperty(gaugeTypeValue_);
        AttachProperty(isShowIndicator_);

        AttachProperty(shadowRadiusFloat_);
        AttachProperty(shadowOffsetXFloat_);
        AttachProperty(shadowOffsetYFloat_);

        value_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
        AttachProperty(value_);
    }
    ~GaugeModifier() override = default;

    void onDraw(DrawingContext& context) override;
    void UpdateValue();
    void SetUseContentModifier(bool useContentModifier)
    {
        if (useContentModifier_) {
            useContentModifier_->Set(useContentModifier);
        }
    }

    float start_ = 0.0f;
    float end_ = 0.0f;

private:
    void InitProperty();
    void InitPropertyColors(RefPtr<GaugePaintProperty>& paintProperty);
    void UpdateProperty(RefPtr<GaugePaintProperty>& paintProperty);
    
    void PaintCircularAndIndicator(RSCanvas& canvas);
    void PaintDraw(RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty,
        float startDegree, float sweepDegree, RenderRingInfo data);
    void DrawGauge(RSCanvas& canvas, RenderRingInfo data);
    void DrawIndicator(RSCanvas& canvas, RenderRingInfo data);
    bool ShouldHighLight(float start, float interval, float percent);
    void NewPaintCircularAndIndicator(RSCanvas& canvas);
    void NewDrawIndicator(
        RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data);
    void NewDrawImageIndicator(
        RSCanvas& canvas, RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data);
    void PaintMonochromeCircular(
        RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty);
    void PaintMonochromeCircularShadow(RSCanvas& canvas, RenderRingInfo& data, Color& color,
        RefPtr<GaugePaintProperty>& paintProperty, float sweepDegree);
    void PaintSingleSegmentGradientCircular(
        RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty);
    void PaintSingleSegmentGradientCircularShadow(RSCanvas& canvas, RenderRingInfo& data,
        RefPtr<GaugePaintProperty>& paintProperty, std::vector<RSColorQuad>& colors,
        std::vector<float>& pos);
    void PaintMultiSegmentGradientCircular(
        RSCanvas& canvas, RenderRingInfo data, RefPtr<GaugePaintProperty>& paintProperty);
    void PaintMultiSegmentGradientCircularShadow(RSCanvas& canvas, RenderRingInfo& data,
        RefPtr<GaugePaintProperty>& paintProperty, std::vector<ColorStopArray>& colors,
        std::vector<float>& weights);
    void DrawSingleSegmentGradient(RSCanvas& canvas, RenderRingInfo& data,
        RefPtr<GaugePaintProperty>& paintProperty, SingleSegmentGradientInfo& info,
        size_t index);
    void DrawSingleSegmentGradientExtend(RSCanvas& canvas, RenderRingInfo& data,
        RefPtr<GaugePaintProperty>& paintProperty, SingleSegmentGradientInfo& info, size_t index);
    void DrawSegmentGradient(RSCanvas& canvas, RSBrush& brush, RenderRingInfo& data,
        RefPtr<GaugePaintProperty>& paintProperty, SingleSegmentGradientInfo& info, bool isFirst, float startDegree,
        float sweepDegree);
    void DrawHighLight(RSCanvas& canvas, RenderRingInfo& data, float drawStartDegree);
    void CalculateStartAndSweepDegree(RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data);
    float GetOffsetDegree(RenderRingInfo& data, float oppositeSide);
    void CreateDefaultColor(std::vector<RSColorQuad>& colors, std::vector<float>& pos);
    void CreateDefaultTrianglePath(float pathStartVertexX, float pathStartVertexY, float radius, RSPath& path);
    WeakPtr<Pattern> pattern_;
    void GetDrawPath(RSPath& path, RenderRingInfo& data, float startAngle, float sweepAngle, bool isFirst);

    RefPtr<AnimatablePropertyFloat> value_;
    RefPtr<AnimatablePropertyFloat> min_;
    RefPtr<AnimatablePropertyFloat> max_;
    RefPtr<AnimatablePropertyFloat> startAngle_;
    RefPtr<AnimatablePropertyFloat> endAngle_;
    RefPtr<AnimatablePropertyFloat> strokeWidth_;
    RefPtr<AnimatablePropertyFloat> indicatorSpace_;
    RefPtr<AnimatablePropertyFloat> gaugeTypeValue_;

    RefPtr<AnimatablePropertyFloat> shadowRadiusFloat_;
    RefPtr<AnimatablePropertyFloat> shadowOffsetXFloat_;
    RefPtr<AnimatablePropertyFloat> shadowOffsetYFloat_;

    std::vector<RefPtr<AnimatablePropertyColor>> colors_;
    std::vector<RefPtr<AnimatablePropertyColor>> gradientColors_;

    RefPtr<PropertyBool> isShowIndicator_;
    RefPtr<PropertyBool> useContentModifier_;
    RefPtr<PropertyBool> indicatorChange_;
    ACE_DISALLOW_COPY_AND_MOVE(GaugeModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_MODIFIER_H

