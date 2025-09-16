/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/shape_abstract_model_static.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"

namespace OHOS::Ace::NG {
void ShapeAbstractModelStatic::SetWidth(FrameNode* frameNode, const std::optional<Dimension>& width)
{
    if (width) {
        Dimension val = width.value();
        if (LessNotEqual(val.Value(), 0.0)) {
            val.SetValue(0.0);
        }
        ViewAbstract::SetWidth(frameNode, CalcLength(val));
    } else {
        ViewAbstract::ClearWidthOrHeight(frameNode, false);
    }
}

void ShapeAbstractModelStatic::SetHeight(FrameNode* frameNode, const std::optional<Dimension>& height)
{
    if (height) {
        Dimension val = height.value();
        if (LessNotEqual(val.Value(), 0.0)) {
            val.SetValue(0.0);
        }
        ViewAbstract::SetHeight(frameNode, CalcLength(val));
    } else {
        ViewAbstract::ClearWidthOrHeight(frameNode, true);
    }
}

void ShapeAbstractModelStatic::SetStrokeDashOffset(FrameNode* frameNode, const Ace::Dimension& dashOffset)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashOffset, dashOffset, frameNode);
}

void ShapeAbstractModelStatic::SetStrokeLineCap(FrameNode* frameNode, int lineCapStyle)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineCap, lineCapStyle, frameNode);
}
void ShapeAbstractModelStatic::SetStrokeLineJoin(FrameNode* frameNode, int lineJoinStyle)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineJoin, lineJoinStyle, frameNode);
}

void ShapeAbstractModelStatic::SetStrokeMiterLimit(FrameNode* frameNode, double miterLimit)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeMiterLimit, miterLimit, frameNode);
}

void ShapeAbstractModelStatic::SetStrokeOpacity(FrameNode* frameNode, double opacity)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, opacity, frameNode);
}

void ShapeAbstractModelStatic::SetFillOpacity(FrameNode* frameNode, double opacity)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, FillOpacity, opacity, frameNode);
}

void ShapeAbstractModelStatic::SetAntiAlias(FrameNode* frameNode, bool antiAlias)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, AntiAlias, antiAlias, frameNode);
}

} // namespace OHOS::Ace::NG
