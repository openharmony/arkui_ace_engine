/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/shape_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"

namespace OHOS::Ace::NG {
constexpr double FILL_OPACITY_MIN = 0.0f;
constexpr double FILL_OPACITY_MAX = 1.0f;

void ShapeModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SHAPE_CONTAINER_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SHAPE_CONTAINER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ShapeContainerPattern>(); });
    stack->Push(frameNode);
}

void ShapeModelNG::InitBox(const RefPtr<PixelMap>& pixMap)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        ImageSourceInfo pixelMapInfo(pixMap);
        ACE_UPDATE_PAINT_PROPERTY(ShapeContainerPaintProperty, PixelMapInfo, pixelMapInfo);
    }
}

void ShapeModelNG::SetBitmapMesh(const std::vector<float>& mesh, int32_t column, int32_t row)
{
    ACE_UPDATE_PAINT_PROPERTY(ShapeContainerPaintProperty, ImageMesh, ImageMesh(mesh, (int32_t)column, (int32_t)row));
}

void ShapeModelNG::SetViewPort(
    const Dimension& dimLeft, const Dimension& dimTop, const Dimension& dimWidth, const Dimension& dimHeight)
{
    ShapeViewBox shapeViewBox;
    shapeViewBox.SetLeft(dimLeft);
    shapeViewBox.SetTop(dimTop);
    shapeViewBox.SetWidth(dimWidth);
    shapeViewBox.SetHeight(dimHeight);
    ACE_UPDATE_PAINT_PROPERTY(ShapeContainerPaintProperty, ShapeViewBox, shapeViewBox);
}

void ShapeModelNG::SetStroke(const Color& color)
{
    ShapeAbstractModelNG().SetStroke(color);
}

void ShapeModelNG::SetFill(const Color& color)
{
    ShapeAbstractModelNG().SetFill(color);
}

void ShapeModelNG::SetStrokeDashOffset(const Ace::Dimension& dashOffset)
{
    ShapeAbstractModelNG().SetStrokeDashOffset(dashOffset);
}

void ShapeModelNG::SetStrokeLineCap(int lineCapStyle)
{
    ShapeAbstractModelNG().SetStrokeLineCap(lineCapStyle);
}

void ShapeModelNG::SetStrokeLineJoin(int lineJoinStyle)
{
    ShapeAbstractModelNG().SetStrokeLineJoin(lineJoinStyle);
}

void ShapeModelNG::SetStrokeMiterLimit(double miterLimit)
{
    ShapeAbstractModelNG().SetStrokeMiterLimit(miterLimit);
}

void ShapeModelNG::SetStrokeOpacity(double opacity)
{
    ShapeAbstractModelNG().SetStrokeOpacity(opacity);
}

void ShapeModelNG::SetFillOpacity(double opacity)
{
    ShapeAbstractModelNG().SetFillOpacity(opacity);
}

void ShapeModelNG::SetStrokeWidth(const Ace::Dimension& lineWidth)
{
    ShapeAbstractModelNG().SetStrokeWidth(lineWidth);
}

void ShapeModelNG::SetStrokeDashArray(const std::vector<Ace::Dimension>& segments)
{
    ShapeAbstractModelNG().SetStrokeDashArray(segments);
}

void ShapeModelNG::SetAntiAlias(bool antiAlias)
{
    ShapeAbstractModelNG().SetAntiAlias(antiAlias);
}

void ShapeModelNG::SetStrokeDashArray(FrameNode* frameNode, const std::vector<Ace::Dimension>& segments)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashArray, segments, frameNode);
}

void ShapeModelNG::SetStroke(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Stroke, *color, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, Stroke, frameNode);
    }
}

void ShapeModelNG::SetFill(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, *color, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, *color, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, false, frameNode);
    }
}

void ShapeModelNG::SetStrokeDashOffset(FrameNode* frameNode, const std::optional<Ace::Dimension>& dashOffset)
{
    if (dashOffset) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashOffset, dashOffset.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashOffset, frameNode);
    }
}

void ShapeModelNG::SetStrokeLineCap(FrameNode* frameNode, const std::optional<int>& lineCapStyle)
{
    if (lineCapStyle) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineCap, lineCapStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineCap, frameNode);
    }
}

void ShapeModelNG::SetStrokeLineJoin(FrameNode* frameNode, const std::optional<int>& lineJoinStyle)
{
    if (lineJoinStyle) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineJoin, lineJoinStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineJoin, frameNode);
    }
}

void ShapeModelNG::SetStrokeMiterLimit(FrameNode* frameNode, const std::optional<double>& miterLimit)
{
    if (miterLimit) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeMiterLimit, miterLimit.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeMiterLimit, frameNode);
    }
}

void ShapeModelNG::SetFillOpacity(FrameNode* frameNode, const std::optional<double>& fillOpacity)
{
    if (fillOpacity) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(
            ShapePaintProperty, FillOpacity,
            std::clamp(fillOpacity.value(), FILL_OPACITY_MIN, FILL_OPACITY_MAX),
            frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, FillOpacity, frameNode);
    }
}

void ShapeModelNG::SetStrokeOpacity(FrameNode* frameNode, const std::optional<double>& strokeOpacity)
{
    if (strokeOpacity) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, strokeOpacity.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, frameNode);
    }
}

void ShapeModelNG::SetStrokeWidth(FrameNode* frameNode, const std::optional<Ace::Dimension>& strokeWidth)
{
    if (strokeWidth) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, strokeWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, frameNode);
    }
}

void ShapeModelNG::SetAntiAlias(FrameNode* frameNode, bool antiAlias)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, AntiAlias, antiAlias, frameNode);
}

void ShapeModelNG::SetViewPort(FrameNode* frameNode,
    const std::optional<Dimension>& dimLeft, const std::optional<Dimension>& dimTop,
    const std::optional<Dimension>& dimWidth, const std::optional<Dimension>& dimHeight)
{
    if (!dimLeft && !dimTop && !dimWidth && !dimHeight) {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapeContainerPaintProperty, ShapeViewBox, frameNode);
        return;
    }
    Dimension defaultVal(0.0);
    ShapeViewBox shapeViewBox;
    shapeViewBox.SetLeft(dimLeft.value_or(defaultVal));
    shapeViewBox.SetTop(dimTop.value_or(defaultVal));
    shapeViewBox.SetWidth(dimWidth.value_or(defaultVal));
    shapeViewBox.SetHeight(dimHeight.value_or(defaultVal));
    ACE_UPDATE_NODE_PAINT_PROPERTY(ShapeContainerPaintProperty, ShapeViewBox, shapeViewBox, frameNode);
}

void ShapeModelNG::SetBitmapMesh(FrameNode* frameNode, const std::vector<float>& mesh, int32_t column, int32_t row)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(
        ShapeContainerPaintProperty, ImageMesh, ImageMesh(mesh, (int32_t)column, (int32_t)row), frameNode);
}

RefPtr<NG::FrameNode> ShapeModelNG::CreateFrameNode(int32_t nodeId)
{
    return FrameNode::CreateFrameNode(
        V2::SHAPE_ETS_TAG, nodeId, AceType::MakeRefPtr<ShapeContainerPattern>());
}
} // namespace OHOS::Ace::NG
