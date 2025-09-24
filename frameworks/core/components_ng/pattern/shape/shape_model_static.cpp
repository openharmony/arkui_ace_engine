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

#include "core/components_ng/pattern/shape/shape_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_container_pattern.h"

namespace OHOS::Ace::NG {
constexpr double FILL_OPACITY_MIN = 0.0f;
constexpr double FILL_OPACITY_MAX = 1.0f;

void ShapeModelStatic::InitBox(FrameNode* frameNode, const RefPtr<PixelMap>& pixMap)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        ImageSourceInfo pixelMapInfo(pixMap);
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapeContainerPaintProperty, PixelMapInfo, pixelMapInfo, frameNode);
    }
}

void ShapeModelStatic::SetStroke(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Stroke, *color, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, Stroke, frameNode);
    }
}

void ShapeModelStatic::SetFill(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, *color, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, *color, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
    } else {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, Fill, Color::BLACK, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, false, frameNode);
    }
}

void ShapeModelStatic::SetStrokeDashOffset(FrameNode* frameNode, const std::optional<Ace::Dimension>& dashOffset)
{
    if (dashOffset) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashOffset, dashOffset.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeDashOffset, frameNode);
    }
}

void ShapeModelStatic::SetStrokeLineCap(FrameNode* frameNode, const std::optional<int>& lineCapStyle)
{
    if (lineCapStyle) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineCap, lineCapStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineCap, frameNode);
    }
}

void ShapeModelStatic::SetStrokeLineJoin(FrameNode* frameNode, const std::optional<int>& lineJoinStyle)
{
    if (lineJoinStyle) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineJoin, lineJoinStyle.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeLineJoin, frameNode);
    }
}

void ShapeModelStatic::SetStrokeMiterLimit(FrameNode* frameNode, const std::optional<double>& miterLimit)
{
    if (miterLimit) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeMiterLimit, miterLimit.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeMiterLimit, frameNode);
    }
}

void ShapeModelStatic::SetFillOpacity(FrameNode* frameNode, const std::optional<double>& fillOpacity)
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

void ShapeModelStatic::SetStrokeOpacity(FrameNode* frameNode, const std::optional<double>& strokeOpacity)
{
    if (strokeOpacity) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, strokeOpacity.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeOpacity, frameNode);
    }
}

void ShapeModelStatic::SetStrokeWidth(FrameNode* frameNode, const std::optional<Ace::Dimension>& strokeWidth)
{
    if (strokeWidth) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, strokeWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ShapePaintProperty, StrokeWidth, frameNode);
    }
}

void ShapeModelStatic::SetViewPort(FrameNode* frameNode,
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

RefPtr<NG::FrameNode> ShapeModelStatic::CreateFrameNode(int32_t nodeId)
{
    return FrameNode::CreateFrameNode(
        V2::SHAPE_ETS_TAG, nodeId, AceType::MakeRefPtr<ShapeContainerPattern>());
}

} // namespace OHOS::Ace::NG

