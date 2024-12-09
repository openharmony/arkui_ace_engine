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

#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"

namespace OHOS::Ace::NG {

void ShapeAbstractModelNG::SetStroke(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, Stroke, color);
}

void ShapeAbstractModelNG::SetStroke(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Stroke, color, frameNode);
}

void ShapeAbstractModelNG::SetFill(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, Fill, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}
void ShapeAbstractModelNG::SetForegroundColor(const Color& color)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, Fill, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void ShapeAbstractModelNG::SetFill(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, color, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void ShapeAbstractModelNG::SetStrokeDashOffset(const Ace::Dimension& dashOffset)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashOffset, dashOffset);
}

void ShapeAbstractModelNG::SetStrokeLineCap(int lineCapStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineCap, lineCapStyle);
}

void ShapeAbstractModelNG::SetStrokeLineJoin(int lineJoinStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineJoin, lineJoinStyle);
}

void ShapeAbstractModelNG::SetStrokeMiterLimit(double miterLimit)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeMiterLimit, miterLimit);
}

void ShapeAbstractModelNG::SetStrokeOpacity(double opacity)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, opacity);
}

void ShapeAbstractModelNG::SetFillOpacity(double opacity)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, FillOpacity, std::clamp(opacity, 0.0, 1.0));
}

void ShapeAbstractModelNG::SetStrokeWidth(const Dimension& lineWidth)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, lineWidth);
}

void ShapeAbstractModelNG::SetStrokeWidth(FrameNode* frameNode, const Dimension& lineWidth)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, lineWidth, frameNode);
}

void ShapeAbstractModelNG::SetStrokeDashArray(const std::vector<Dimension>& segments)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashArray, segments);
}

void ShapeAbstractModelNG::SetAntiAlias(bool antiAlias)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, AntiAlias, antiAlias);
}

void ShapeAbstractModelNG::SetWidth(Dimension& width)
{
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    ViewAbstract::SetWidth(CalcLength(width));
}

void ShapeAbstractModelNG::SetHeight(Dimension& height)
{
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    ViewAbstract::SetHeight(CalcLength(height));
}

void ShapeAbstractModelNG::SetWidth(FrameNode* frameNode, Dimension& width)
{
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    ViewAbstract::SetWidth(frameNode, CalcLength(width));
}

void ShapeAbstractModelNG::SetHeight(FrameNode* frameNode, Dimension& height)
{
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    ViewAbstract::SetHeight(frameNode, CalcLength(height));
}

void ShapeAbstractModelNG::ResetWidth(FrameNode* frameNode)
{
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
}

void ShapeAbstractModelNG::ResetHeight(FrameNode* frameNode)
{
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}
} // namespace OHOS::Ace::NG