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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H

#include <utility>

#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SliderPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SliderPaintMethod, NodePaintMethod)

public:
    static constexpr float HALF = 0.5f;
    struct Parameters {
        float trackThickness = 0.0f;
        float blockDiameter = 0.0f;
        float sliderLength = 0.0f;
        float borderBlank = 0.0f;
        float stepRatio = 0.0f;
        float valueRatio = 0.0f;
    };
    explicit SliderPaintMethod(const Parameters& parameters)
        : parameters_(parameters) {};
    ~SliderPaintMethod() override = default;
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

private:
    struct LinePenAndSize {
        RSPen pen;
        PointF start;
        PointF end;
    };

    struct MarkerPenAndPath {
        RSPen pen;
        RSPath path;
    };

    struct CirclePenAndSize {
        RSPen pen;
        PointF center;
        float radius;
    };

    LinePenAndSize GetBackgroundPen(
        const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset) const;
    MarkerPenAndPath GetMarkerPen(const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset) const;
    LinePenAndSize GetSelectPen(const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset) const;
    CirclePenAndSize GetCirclePen(const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset) const;

    Parameters parameters_;

    float centerWidth_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(SliderPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H