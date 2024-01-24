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
#include "core/interfaces/native/node/common_shape_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {
constexpr double DEFAULT_MITER_LIMIT = 4.0f;
constexpr double DEFAULT_FILL_OPACITY = 1.0f;
constexpr double DEFAULT_STROKE_OPACITY = 1.0f;
constexpr double DEFAULT_STROKE_WIDTH = 1.0f;

constexpr int DEFAULT_STROKE_DASH_OFFSET = 0;
constexpr int DEFAULT_STROKE_LINE_CAPS = 0;
constexpr int DEFAULT_STROKE_LINE_JOIN = 0;
void SetStrokeMiterLimit(NodeHandle node, const double miterLimit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeMiterLimit(frameNode, miterLimit);
}

void ResetStrokeMiterLimit(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeMiterLimit(frameNode, DEFAULT_MITER_LIMIT);
}

void SetFillOpacity(NodeHandle node, const double fillOpacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFillOpacity(frameNode, fillOpacity);
}

void ResetFillOpacity(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFillOpacity(frameNode, DEFAULT_FILL_OPACITY);
}

void SetStrokeOpacity(NodeHandle node, const double strokeOpacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeOpacity(frameNode, strokeOpacity);
}

void ResetStrokeOpacity(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeOpacity(frameNode, DEFAULT_STROKE_OPACITY);
}

void SetStrokeWidth(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    ShapeModelNG::SetStrokeWidth(frameNode, Dimension(value, unitEnum));
}

void ResetStrokeWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeWidth(frameNode, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
}

void SetAntiAlias(NodeHandle node, const bool antiAlias)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetAntiAlias(frameNode, antiAlias);
}

void ResetAntiAlias(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetAntiAlias(frameNode, true);
}

void SetStroke(NodeHandle node, const uint32_t stroke)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStroke(frameNode, Color(stroke));
}

void ResetStroke(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStroke(frameNode, Color::TRANSPARENT);
}

void SetFill(NodeHandle node, const uint32_t fill)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFill(frameNode, Color(fill));
}

void ResetFill(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFill(frameNode, Color::BLACK);
}

void SetStrokeDashOffset(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    ShapeModelNG::SetStrokeDashOffset(frameNode, Dimension(value, unitEnum));
}

void ResetStrokeDashOffset(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeDashOffset(frameNode, Dimension(DEFAULT_STROKE_DASH_OFFSET));
}

void SetStrokeLineCap(NodeHandle node, const int strokeLineCap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeLineCap(frameNode, strokeLineCap);
}

void ResetStrokeLineCap(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeLineCap(frameNode, DEFAULT_STROKE_LINE_CAPS);
}

void SetStrokeLineJoin(NodeHandle node, const int lineJoinStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeLineJoin(frameNode, lineJoinStyle);
}

void ResetStrokeLineJoin(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeLineJoin(frameNode, DEFAULT_STROKE_LINE_JOIN);
}

void SetStrokeDashArray(NodeHandle node,  double* dashArrayArray, int32_t* dimUnits, int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Dimension> dashArray;
    for (int32_t i = 0; i < size; i++) {
        dashArray.emplace_back(CalcDimension(dashArrayArray[i], (DimensionUnit)dimUnits[i]));
    }
    ShapeModelNG::SetStrokeDashArray(frameNode, dashArray);
}

void ResetStrokeDashArray(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Dimension> dashArray;
    ShapeModelNG::SetStrokeDashArray(frameNode, dashArray);
}

void SetShapeWidth(NodeHandle node, const double value, const int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    Dimension width = Dimension(value, unitEnum);
    ShapeAbstractModelNG::SetWidth(frameNode, width);
}

void ResetShapeWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeAbstractModelNG::ResetWidth(frameNode);
}

void SetShapeHeight(NodeHandle node, const double value, const int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    Dimension height = Dimension(value, unitEnum);
    ShapeAbstractModelNG::SetHeight(frameNode, height);
}

void ResetShapeHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeAbstractModelNG::ResetHeight(frameNode);
}

void SetShapeForegroundColor(NodeHandle node, bool isColor, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (isColor) {
        ShapeModelNG::SetFill(frameNode, Color(color));
        ViewAbstract::SetForegroundColor(frameNode, Color(color));
    } else {
        ShapeModelNG::SetFill(frameNode, Color::FOREGROUND);
        auto strategy = static_cast<ForegroundColorStrategy>(color);
        ViewAbstract::SetForegroundColorStrategy(frameNode, strategy);
    }
}

void ResetShapeForegroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}

ArkUICommonShapeModifierAPI GetCommonShapeModifier()
{
    static const ArkUICommonShapeModifierAPI modifier = { SetStrokeDashArray, ResetStrokeDashArray, SetStrokeMiterLimit,
        ResetStrokeMiterLimit, SetFillOpacity, ResetFillOpacity, SetStrokeOpacity, ResetStrokeOpacity, SetStrokeWidth,
        ResetStrokeWidth, SetAntiAlias, ResetAntiAlias, SetStroke, ResetStroke, SetFill, ResetFill, SetStrokeDashOffset,
        ResetStrokeDashOffset, SetStrokeLineCap, ResetStrokeLineCap, SetStrokeLineJoin, ResetStrokeLineJoin,
        SetShapeWidth, ResetShapeWidth, SetShapeHeight, ResetShapeHeight, SetShapeForegroundColor,
        ResetShapeForegroundColor };
    return modifier;
}
} // namespace OHOS::Ace::NG