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

#include "core/components_ng/pattern/shape/shape_view.h"

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void ShapeView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SHAPE_CONTAINER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ShapeContainerPattern>(); });
    stack->Push(frameNode);
}

void ShapeView::SetStroke(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, Stroke, color);
}

void ShapeView::SetFill(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, Fill, color);
}

void ShapeView::SetStrokeDashOffset(const Ace::Dimension& dashOffset)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashOffset, dashOffset);
}

void ShapeView::SetStrokeLineCap(int lineCapStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineCap, lineCapStyle);
}

void ShapeView::SetStrokeLineJoin(int lineJoinStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineJoin, lineJoinStyle);
}

void ShapeView::SetStrokeMiterLimit(double miterLimit)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeMiterLimit, miterLimit);
}

void ShapeView::SetStrokeOpacity(double opacity)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, opacity);
}

void ShapeView::SetFillOpacity(double opacity)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, FillOpacity, opacity);
}

void ShapeView::SetStrokeWidth(const Dimension& lineWidth)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, lineWidth);
}

void ShapeView::SetStrokeDashArray(const std::vector<Dimension>& segments)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashArray, segments);
}

void ShapeView::SetAntiAlias(bool antiAlias)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapePaintProperty, AntiAlias, antiAlias);
}

void ShapeView::SetBitmapMesh(const ImageMesh& imageMesh)
{
    ACE_UPDATE_PAINT_PROPERTY(ContainerPaintProperty, ImageMesh, imageMesh);
}

void ShapeView::SetViewPort(const ShapeViewBox& viewBox)
{
    ACE_UPDATE_PAINT_PROPERTY(ContainerPaintProperty, ShapeViewBox, viewBox);
}

} // namespace OHOS::Ace::NG