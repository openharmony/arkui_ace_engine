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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_METHOD_H

#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"
namespace OHOS::Ace::NG {

struct RenderRingInfo {
    float radius = 0.0f;
    float startDegree = 0.0f;
    float sweepDegree = 0.0f;
    float thickness = 0.0f;
    Offset center;
    SizeF contentSize;
    Color color;
};

class ACE_EXPORT GaugePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(GaugePaintMethod, NodePaintMethod)
public:
    GaugePaintMethod() = default;
    ~GaugePaintMethod() override = default;

    CanvasDrawFunction GetForegroundDrawFunction(PaintWrapper* paintWrapper) override;

private:
    void Paint(RSCanvas& canvas, PaintWrapper* paintWrapper) const;
    void DrawGauge(RSCanvas& canvas, RenderRingInfo data) const;
    void DrawIndicator(RSCanvas& canvas, RenderRingInfo data) const;
    bool ShouldHighLight(float start, float interval, float percent) const;
    // API11
    void NewPaint(RSCanvas& canvas, PaintWrapper* paintWrapper) const;
    void NewDrawIndicator(RSCanvas& canvas, const RenderRingInfo& data) const;
    void PaintMonochromeCircular(
        RSCanvas& canvas, RenderRingInfo data, const RefPtr<GaugePaintProperty>& paintProperty) const;
    void PaintSingleSegmentGradientCircular(
        RSCanvas& canvas, RenderRingInfo data, const RefPtr<GaugePaintProperty>& paintProperty) const;
    void PaintMultiSegmentGradientCircular(
        RSCanvas& canvas, RenderRingInfo data, const RefPtr<GaugePaintProperty>& paintProperty) const;
    void DrawHighLight(RSCanvas& canvas, const RenderRingInfo& data, const float drawStartDegree) const;
    void CalculateStartAndSweepDegree(const RefPtr<GaugePaintProperty>& paintProperty, RenderRingInfo& data) const;
    float GetOffsetDegree(const RenderRingInfo& data, const float oppositeSide) const;
    float GetValueRatio(const RefPtr<GaugePaintProperty>& paintProperty) const;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_PAINT_METHOD_H
