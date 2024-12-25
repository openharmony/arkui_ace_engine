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

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"

namespace OHOS::Ace::NG {
constexpr double DEFAULT_MITER_LIMIT = 4.0f;
constexpr double DEFAULT_FILL_OPACITY = 1.0f;
constexpr double DEFAULT_STROKE_OPACITY = 1.0f;
constexpr double DEFAULT_STROKE_WIDTH = 1.0f;

constexpr int DEFAULT_STROKE_DASH_OFFSET = 0;
constexpr int DEFAULT_STROKE_LINE_CAPS = 0;
constexpr int DEFAULT_STROKE_LINE_JOIN = 0;

void SetStrokeMiterLimit(ArkUINodeHandle node, ArkUI_Float32 miterLimit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeMiterLimit(frameNode, miterLimit);
}

void ResetStrokeMiterLimit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeMiterLimit(frameNode, DEFAULT_MITER_LIMIT);
}

void SetFillOpacity(ArkUINodeHandle node, ArkUI_Float32 fillOpacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFillOpacity(frameNode, fillOpacity);
}

void ResetFillOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFillOpacity(frameNode, DEFAULT_FILL_OPACITY);
}

void SetStrokeOpacity(ArkUINodeHandle node, ArkUI_Float32 strokeOpacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeOpacity(frameNode, strokeOpacity);
}

void ResetStrokeOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeOpacity(frameNode, DEFAULT_STROKE_OPACITY);
}

void SetStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    ShapeModelNG::SetStrokeWidth(frameNode, Dimension(value, unitEnum));
}

void ResetStrokeWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeWidth(frameNode, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
}

void SetAntiAlias(ArkUINodeHandle node, ArkUI_Bool antiAlias)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetAntiAlias(frameNode, antiAlias);
}

void ResetAntiAlias(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetAntiAlias(frameNode, true);
}

void SetStroke(ArkUINodeHandle node, uint32_t stroke)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStroke(frameNode, Color(stroke));
}

void ResetStroke(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStroke(frameNode, Color::TRANSPARENT);
}

void SetFill(ArkUINodeHandle node, uint32_t fill)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFill(frameNode, Color(fill));
}

void ResetFill(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFill(frameNode, Color::BLACK);
}

void SetStrokeDashOffset(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    ShapeModelNG::SetStrokeDashOffset(frameNode, Dimension(value, unitEnum));
}

void ResetStrokeDashOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeDashOffset(frameNode, Dimension(DEFAULT_STROKE_DASH_OFFSET));
}

void SetStrokeLineCap(ArkUINodeHandle node, int strokeLineCap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeLineCap(frameNode, strokeLineCap);
}

void ResetStrokeLineCap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeLineCap(frameNode, DEFAULT_STROKE_LINE_CAPS);
}

void SetStrokeLineJoin(ArkUINodeHandle node, int lineJoinStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeLineJoin(frameNode, lineJoinStyle);
}

void ResetStrokeLineJoin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeLineJoin(frameNode, DEFAULT_STROKE_LINE_JOIN);
}

void SetStrokeDashArray(ArkUINodeHandle node, const ArkUI_Float32* dashArrayArray, int32_t* dimUnits, int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Dimension> dashArray;
    for (int32_t i = 0; i < size; i++) {
        dashArray.emplace_back(CalcDimension(dashArrayArray[i], (DimensionUnit)dimUnits[i]));
    }
    ShapeModelNG::SetStrokeDashArray(frameNode, dashArray);
}

void ResetStrokeDashArray(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Dimension> dashArray;
    ShapeModelNG::SetStrokeDashArray(frameNode, dashArray);
}

void SetShapeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    Dimension width = Dimension(value, unitEnum);
    ShapeAbstractModelNG::SetWidth(frameNode, width);
}

void ResetShapeWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeAbstractModelNG::ResetWidth(frameNode);
}

void SetShapeHeight(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    Dimension height = Dimension(value, unitEnum);
    ShapeAbstractModelNG::SetHeight(frameNode, height);
}

void ResetShapeHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeAbstractModelNG::ResetHeight(frameNode);
}

void SetShapeForegroundColor(ArkUINodeHandle node, ArkUI_Bool isColor, uint32_t color)
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

void ResetShapeForegroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
}

namespace NodeModifier {
const ArkUICommonShapeModifier* GetCommonShapeModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUICommonShapeModifier modifier = {
        .setStrokeDashArray = SetStrokeDashArray,
        .resetStrokeDashArray = ResetStrokeDashArray,
        .setStrokeMiterLimit = SetStrokeMiterLimit,
        .resetStrokeMiterLimit = ResetStrokeMiterLimit,
        .setFillOpacity = SetFillOpacity,
        .resetFillOpacity = ResetFillOpacity,
        .setStrokeOpacity = SetStrokeOpacity,
        .resetStrokeOpacity = ResetStrokeOpacity,
        .setStrokeWidth = SetStrokeWidth,
        .resetStrokeWidth = ResetStrokeWidth,
        .setAntiAlias = SetAntiAlias,
        .resetAntiAlias = ResetAntiAlias,
        .setStroke = SetStroke,
        .resetStroke = ResetStroke,
        .setFill = SetFill,
        .resetFill = ResetFill,
        .setStrokeDashOffset = SetStrokeDashOffset,
        .resetStrokeDashOffset = ResetStrokeDashOffset,
        .setStrokeLineCap = SetStrokeLineCap,
        .resetStrokeLineCap = ResetStrokeLineCap,
        .setStrokeLineJoin = SetStrokeLineJoin,
        .resetStrokeLineJoin = ResetStrokeLineJoin,
        .setShapeWidth = SetShapeWidth,
        .resetShapeWidth = ResetShapeWidth,
        .setShapeHeight = SetShapeHeight,
        .resetShapeHeight = ResetShapeHeight,
        .setShapeForegroundColor = SetShapeForegroundColor,
        .resetShapeForegroundColor = ResetShapeForegroundColor,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}

const CJUICommonShapeModifier* GetCJUICommonShapeModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUICommonShapeModifier modifier = {
        .setStrokeDashArray = SetStrokeDashArray,
        .resetStrokeDashArray = ResetStrokeDashArray,
        .setStrokeMiterLimit = SetStrokeMiterLimit,
        .resetStrokeMiterLimit = ResetStrokeMiterLimit,
        .setFillOpacity = SetFillOpacity,
        .resetFillOpacity = ResetFillOpacity,
        .setStrokeOpacity = SetStrokeOpacity,
        .resetStrokeOpacity = ResetStrokeOpacity,
        .setStrokeWidth = SetStrokeWidth,
        .resetStrokeWidth = ResetStrokeWidth,
        .setAntiAlias = SetAntiAlias,
        .resetAntiAlias = ResetAntiAlias,
        .setStroke = SetStroke,
        .resetStroke = ResetStroke,
        .setFill = SetFill,
        .resetFill = ResetFill,
        .setStrokeDashOffset = SetStrokeDashOffset,
        .resetStrokeDashOffset = ResetStrokeDashOffset,
        .setStrokeLineCap = SetStrokeLineCap,
        .resetStrokeLineCap = ResetStrokeLineCap,
        .setStrokeLineJoin = SetStrokeLineJoin,
        .resetStrokeLineJoin = ResetStrokeLineJoin,
        .setShapeWidth = SetShapeWidth,
        .resetShapeWidth = ResetShapeWidth,
        .setShapeHeight = SetShapeHeight,
        .resetShapeHeight = ResetShapeHeight,
        .setShapeForegroundColor = SetShapeForegroundColor,
        .resetShapeForegroundColor = ResetShapeForegroundColor,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
