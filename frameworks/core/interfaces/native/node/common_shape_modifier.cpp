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

void SetStrokeMiterLimit(ArkUINodeHandle node, ArkUI_Float32 miterLimit, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeMiterLimit(frameNode, miterLimit);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeMiterLimit");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<double>("ShapeMiterLimit", resObj, miterLimit);
    }
}

void ResetStrokeMiterLimit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeMiterLimit(frameNode, DEFAULT_MITER_LIMIT);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeMiterLimit");
    }
}

void SetFillOpacity(ArkUINodeHandle node, ArkUI_Float32 fillOpacity, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFillOpacity(frameNode, fillOpacity);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractFillOpacity");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<double>("ShapeAbstractFillOpacity", resObj, fillOpacity);
    }
}

void ResetFillOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFillOpacity(frameNode, DEFAULT_FILL_OPACITY);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeAbstractFillOpacity");
    }
}

void SetStrokeOpacity(ArkUINodeHandle node, ArkUI_Float32 strokeOpacity, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeOpacity(frameNode, strokeOpacity);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractStrokeOpacity");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<double>("ShapeAbstractStrokeOpacity", resObj, strokeOpacity);
    }
}

void ResetStrokeOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeOpacity(frameNode, DEFAULT_STROKE_OPACITY);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeAbstractStrokeOpacity");
    }
}

void SetStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int unit, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    auto lineWidth = Dimension(value, unitEnum);
    ShapeModelNG::SetStrokeWidth(frameNode, lineWidth);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractStrokeWidth");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<CalcDimension>("ShapeAbstractStrokeWidth", resObj, lineWidth);
    }
}

void ResetStrokeWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeWidth(frameNode, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeAbstractStrokeWidth");
    }
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

void SetStroke(ArkUINodeHandle node, uint32_t stroke, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeColor = Color(stroke);
    ShapeModelNG::SetStroke(frameNode, strokeColor);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractStroke");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<Color>("ShapeAbstractStroke", resObj, strokeColor);
    }
}

void ResetStroke(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStroke(frameNode, Color::TRANSPARENT);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeAbstractStroke");
    }
}

void SetFill(ArkUINodeHandle node, uint32_t fill, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto fillColor = Color(fill);
    ShapeModelNG::SetFill(frameNode, fillColor);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractFill");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<Color>("ShapeAbstractFill", resObj, fillColor);
    }
}

void ResetFill(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetFill(frameNode, Color::BLACK);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeAbstractFill");
    }
}

void SetStrokeDashOffset(ArkUINodeHandle node, ArkUI_Float32 value, int unit, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    ShapeModelNG::SetStrokeDashOffset(frameNode, Dimension(value, unitEnum));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeDashOffset");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<CalcDimension>("ShapeDashOffset", resObj, Dimension(value, unitEnum));
    }
}

void ResetStrokeDashOffset(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeDashOffset(frameNode, Dimension(DEFAULT_STROKE_DASH_OFFSET));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeDashOffset");
    }
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

void SetStrokeDashArray(
    ArkUINodeHandle node, const ArkUI_Float32* dashArrayArray, int32_t* dimUnits, int32_t size, void* resObjArray)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractStrokeDashArray");
    std::vector<Dimension> dashArray;
    std::vector<RefPtr<ResourceObject>> resObjArrayResult;
    RefPtr<ResourceObject>* resObjPtr = static_cast<RefPtr<ResourceObject>*>(resObjArray);
    bool hasResObj = false;
    for (int32_t i = 0; i < size; i++) {
        dashArray.emplace_back(CalcDimension(dashArrayArray[i], (DimensionUnit)dimUnits[i]));
        if (resObjPtr[i]) {
            hasResObj = true;
        }
        resObjArrayResult.emplace_back(resObjPtr[i]);
    }
    if (SystemProperties::ConfigChangePerform() && hasResObj) {
        ShapeAbstractModelNG::SetStrokeDashArray(frameNode, dashArray, resObjArrayResult);
    }
    ShapeModelNG::SetStrokeDashArray(frameNode, dashArray);
}

void ResetStrokeDashArray(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Dimension> dashArray;
    ShapeModelNG::SetStrokeDashArray(frameNode, dashArray);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractStrokeDashArray");
}

void SetShapeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    Dimension width = Dimension(value, unitEnum);
    ShapeAbstractModelNG::SetWidth(frameNode, width);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractWidth");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<CalcDimension>("ShapeAbstractWidth", resObj, width);
    }
}

void ResetShapeWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeAbstractModelNG::ResetWidth(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeAbstractWidth");
    }
}

void SetShapeHeight(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    Dimension height = Dimension(value, unitEnum);
    ShapeAbstractModelNG::SetHeight(frameNode, height);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("ShapeAbstractHeight");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->RegisterResource<CalcDimension>("ShapeAbstractHeight", resObj, height);
    }
}

void ResetShapeHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeAbstractModelNG::ResetHeight(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeAbstractHeight");
    }
}

void SetShapeForegroundColor(ArkUINodeHandle node, ArkUI_Bool isColor, uint32_t color, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (isColor) {
        auto foregroundColor = Color(color);
        ShapeModelNG::SetFill(frameNode, foregroundColor);
        ViewAbstract::SetForegroundColor(frameNode, foregroundColor);
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("ShapeAbstractForegroundColor");
        if (SystemProperties::ConfigChangePerform() && resObjPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
            pattern->RegisterResource<Color>("ShapeAbstractForegroundColor", resObj, foregroundColor);
        }
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
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->UnRegisterResource("ShapeAbstractForegroundColor");
    }
}

namespace NodeModifier {
const ArkUICommonShapeModifier* GetCommonShapeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
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
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUICommonShapeModifier* GetCJUICommonShapeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
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
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
