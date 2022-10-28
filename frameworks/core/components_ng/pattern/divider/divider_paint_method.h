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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_PAINT_METHOD_H

#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT DividerPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(DividerPaintMethod, NodePaintMethod)
public:
    DividerPaintMethod(float constrainStrokeWidth, float dividerLength, bool vertical)
        : constrainStrokeWidth_(constrainStrokeWidth), dividerLength_(dividerLength), vertical_(vertical)
    {}
    ~DividerPaintMethod() override = default;
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto theme = pipeline->GetTheme<DividerTheme>();
        CHECK_NULL_RETURN(theme, nullptr);
        auto dividerRenderProperty = DynamicCast<DividerRenderProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_RETURN(dividerRenderProperty, nullptr);
        dividerColor_ = dividerRenderProperty->GetDividerColor().value_or(theme->GetColor());
        lineCap_ = dividerRenderProperty->GetLineCap();
        auto offset = paintWrapper->GetContentOffset();
        lineCap_ = lineCap_ == LineCap::BUTT ? LineCap::SQUARE : lineCap_;
        DividerPainter dividerPainter(constrainStrokeWidth_, dividerLength_, vertical_, dividerColor_, lineCap_);
        return [dividerPainter, offset](RSCanvas& canvas) { dividerPainter.DrawLine(canvas, offset); };
    }

private:
    float constrainStrokeWidth_;
    float dividerLength_;
    bool vertical_ = false;

    std::optional<Color> dividerColor_;
    std::optional<LineCap> lineCap_;
    ACE_DISALLOW_COPY_AND_MOVE(DividerPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIVIDER_DIVIDER_PAINT_METHOD_H