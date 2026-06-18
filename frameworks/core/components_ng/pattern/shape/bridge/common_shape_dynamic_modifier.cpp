/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/pattern/shape/shape_pattern.h"
#include "core/components_ng/pattern/shape/bridge/shape_abstract_model_impl.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::ShapeAbstractModelImpl* GetShapeAbstractModelImpl()
{
    static Framework::ShapeAbstractModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_MITER_LIMIT = 4.0f;
constexpr double DEFAULT_FILL_OPACITY = 1.0f;
constexpr double DEFAULT_STROKE_OPACITY = 1.0f;
constexpr double DEFAULT_STROKE_WIDTH = 1.0f;

constexpr int DEFAULT_STROKE_DASH_OFFSET = 0;
constexpr int DEFAULT_STROKE_LINE_CAPS = 0;
constexpr int DEFAULT_STROKE_LINE_JOIN = 0;

using NodeModifier::ShapeColorModifierPayload;

RefPtr<ShapeColorModifierPayload> GetShapeColorPayload(uint32_t colorValue, void* payloadPtr)
{
    if (!payloadPtr) {
        return nullptr;
    }
    auto payload = AceType::DynamicCast<ShapeColorModifierPayload>(
        AceType::Claim(reinterpret_cast<AceType*>(payloadPtr)));
    if (!payload) {
        return nullptr;
    }
    const auto& payloadColor = payload->GetColor();
    if (!payloadColor.GetHeadRoomColor().has_value() && payloadColor.GetColorSpace() != ColorSpace::BT2020 &&
        payloadColor.GetValue() != colorValue) {
        return nullptr;
    }
    return payload;
}

#ifndef CROSS_PLATFORM
void SetStrokeMiterLimitImpl(ArkUINodeHandle node, ArkUI_Float32 miterLimit, void* resObjPtr)
{
    GetShapeAbstractModelImpl()->SetStrokeMiterLimit(miterLimit);
}

void SetStrokeDashArrayImpl(
    ArkUINodeHandle node, const ArkUI_Float32* dashArrayArray, int32_t* dimUnits, int32_t size, void* resObjArray)
{
    std::vector<Dimension> dashArray;
    for (int32_t i = 0; i < size; i++) {
        dashArray.emplace_back(CalcDimension(dashArrayArray[i], static_cast<DimensionUnit>(dimUnits[i])));
    }
    GetShapeAbstractModelImpl()->SetStrokeDashArray(dashArray);
}

void SetFillOpacityImpl(ArkUINodeHandle node, ArkUI_Float32 fillOpacity, void* resObjPtr)
{
    GetShapeAbstractModelImpl()->SetFillOpacity(fillOpacity);
}

void SetStrokeOpacityImpl(ArkUINodeHandle node, ArkUI_Float32 strokeOpacity, void* resObjPtr)
{
    GetShapeAbstractModelImpl()->SetStrokeOpacity(strokeOpacity);
}

void SetStrokeWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit, void* resObjPtr)
{
    Dimension lineWidth = Dimension(value, static_cast<DimensionUnit>(unit));
    GetShapeAbstractModelImpl()->SetStrokeWidth(lineWidth);
}

void SetAntiAliasImpl(ArkUINodeHandle node, ArkUI_Bool antiAlias)
{
    GetShapeAbstractModelImpl()->SetAntiAlias(antiAlias);
}

void SetStrokeImpl(ArkUINodeHandle node, uint32_t stroke, void* resObjPtr)
{
    GetShapeAbstractModelImpl()->SetStroke(Color(stroke));
}

void SetFillImpl(ArkUINodeHandle node, uint32_t fill, void* resObjPtr)
{
    GetShapeAbstractModelImpl()->SetFill(Color(fill));
}

void SetStrokeDashOffsetImpl(ArkUINodeHandle node, ArkUI_Float32 value, int unit, void* resObjPtr)
{
    GetShapeAbstractModelImpl()->SetStrokeDashOffset(Dimension(value, static_cast<DimensionUnit>(unit)));
}

void SetStrokeLineCapImpl(ArkUINodeHandle node, int strokeLineCap)
{
    GetShapeAbstractModelImpl()->SetStrokeLineCap(strokeLineCap);
}

void SetStrokeLineJoinImpl(ArkUINodeHandle node, int lineJoinStyle)
{
    GetShapeAbstractModelImpl()->SetStrokeLineJoin(lineJoinStyle);
}

void SetShapeWidthImpl(ArkUINodeHandle node, ArkUI_Float64 value, int32_t unit, void* resObjPtr)
{
    Dimension width = Dimension(value, static_cast<DimensionUnit>(unit));
    GetShapeAbstractModelImpl()->SetWidth(width);
}

void SetShapeHeightImpl(ArkUINodeHandle node, ArkUI_Float64 value, int32_t unit, void* resObjPtr)
{
    Dimension height = Dimension(value, static_cast<DimensionUnit>(unit));
    GetShapeAbstractModelImpl()->SetHeight(height);
}

void SetShapeForegroundColorImpl(ArkUINodeHandle node, ArkUI_Bool isColor, uint32_t color, void* resObjPtr)
{
    if (isColor) {
        GetShapeAbstractModelImpl()->SetForegroundColor(Color(color));
    }
}

void ResetStrokeDashArrayImpl(ArkUINodeHandle node)
{
    std::vector<Dimension> dashArray;
    GetShapeAbstractModelImpl()->SetStrokeDashArray(dashArray);
}

void ResetStrokeMiterLimitImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetStrokeMiterLimit(DEFAULT_MITER_LIMIT);
}

void ResetFillOpacityImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetFillOpacity(DEFAULT_FILL_OPACITY);
}

void ResetStrokeOpacityImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetStrokeOpacity(DEFAULT_STROKE_OPACITY);
}

void ResetStrokeWidthImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetStrokeWidth(Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
}

void ResetAntiAliasImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetAntiAlias(true);
}

void ResetStrokeImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetStroke(Color::TRANSPARENT);
}

void ResetFillImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetFill(Color::BLACK);
}

void ResetStrokeDashOffsetImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetStrokeDashOffset(Dimension(DEFAULT_STROKE_DASH_OFFSET));
}

void ResetStrokeLineCapImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetStrokeLineCap(DEFAULT_STROKE_LINE_CAPS);
}

void ResetStrokeLineJoinImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetStrokeLineJoin(DEFAULT_STROKE_LINE_JOIN);
}

void ResetShapeWidthImpl(ArkUINodeHandle node)
{
    Dimension width;
    GetShapeAbstractModelImpl()->SetWidth(width);
}

void ResetShapeHeightImpl(ArkUINodeHandle node)
{
    Dimension height;
    GetShapeAbstractModelImpl()->SetHeight(height);
}

void ResetShapeForegroundColorImpl(ArkUINodeHandle node)
{
    GetShapeAbstractModelImpl()->SetForegroundColor(Color::BLACK);
}
#endif

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
        ShapeModelNG::SetStrokeMiterLimit(frameNode, resObj);
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
    pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeFillOpacity")
                                           : pattern->UnRegisterResource("ShapeAbstractFillOpacity");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->IsEnableChildrenMatchParent() ? ShapeModelNG::SetFillOpacity(frameNode, resObj)
                                               : ShapeAbstractModelNG::SetFillOpacity(frameNode, resObj);
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
        pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeFillOpacity")
                                               : pattern->UnRegisterResource("ShapeAbstractFillOpacity");
    }
}

void SetStrokeOpacity(ArkUINodeHandle node, ArkUI_Float32 strokeOpacity, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelNG::SetStrokeOpacity(frameNode, strokeOpacity);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeStrokeOpacity")
                                           : pattern->UnRegisterResource("ShapeAbstractStrokeOpacity");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->IsEnableChildrenMatchParent() ? ShapeModelNG::SetStrokeOpacity(frameNode, resObj)
                                               : ShapeAbstractModelNG::SetStrokeOpacity(frameNode, resObj);
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
        pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeStrokeOpacity")
                                               : pattern->UnRegisterResource("ShapeAbstractStrokeOpacity");
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
    pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeStrokeWidth")
                                           : pattern->UnRegisterResource("ShapeAbstractStrokeWidth");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        pattern->IsEnableChildrenMatchParent() ? ShapeModelNG::SetStrokeWidth(frameNode, resObj)
                                               : ShapeAbstractModelNG::SetStrokeWidth(frameNode, resObj);
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
        pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeStrokeWidth")
                                               : pattern->UnRegisterResource("ShapeAbstractStrokeWidth");
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
    auto payload = GetShapeColorPayload(stroke, resObjPtr);
    auto strokeColor = payload ? payload->GetColor() : Color(stroke);
    ShapeModelNG::SetStroke(frameNode, strokeColor);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeStroke")
                                           : pattern->UnRegisterResource("ShapeAbstractStroke");
    if (SystemProperties::ConfigChangePerform()) {
        auto resObj = payload ?
            payload->GetResourceObject() : AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        if (!resObj) {
            return;
        }
        pattern->IsEnableChildrenMatchParent() ? ShapeModelNG::SetStroke(frameNode, resObj)
                                               : ShapeAbstractModelNG::SetStroke(frameNode, resObj);
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
        pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeStroke")
                                               : pattern->UnRegisterResource("ShapeAbstractStroke");
    }
}

void SetFill(ArkUINodeHandle node, uint32_t fill, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto payload = GetShapeColorPayload(fill, resObjPtr);
    auto fillColor = payload ? payload->GetColor() : Color(fill);
    ShapeModelNG::SetFill(frameNode, fillColor);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeFill")
                                           : pattern->UnRegisterResource("ShapeAbstractFill");
    if (SystemProperties::ConfigChangePerform()) {
        auto resObj = payload ?
            payload->GetResourceObject() : AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        if (!resObj) {
            return;
        }
        pattern->IsEnableChildrenMatchParent() ? ShapeModelNG::SetFill(frameNode, resObj)
                                               : ShapeAbstractModelNG::SetFill(frameNode, resObj);
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
        pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeFill")
                                               : pattern->UnRegisterResource("ShapeAbstractFill");
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
        ShapeModelNG::SetStrokeDashOffset(frameNode, resObj);
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
    pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeStrokeDashArray")
                                           : pattern->UnRegisterResource("ShapeAbstractStrokeDashArray");
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
        pattern->IsEnableChildrenMatchParent()
            ? ShapeModelNG::SetStrokeDashArray(frameNode, dashArray, resObjArrayResult)
            : ShapeAbstractModelNG::SetStrokeDashArray(frameNode, dashArray, resObjArrayResult);
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
    pattern->IsEnableChildrenMatchParent() ? pattern->UnRegisterResource("ShapeStrokeDashArray")
                                           : pattern->UnRegisterResource("ShapeAbstractStrokeDashArray");
}

void SetShapeWidth(ArkUINodeHandle node, ArkUI_Float64 value, int32_t unit, void* resObjPtr)
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
        ShapeAbstractModelNG::SetWidth(frameNode, resObj);
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

void SetShapeHeight(ArkUINodeHandle node, ArkUI_Float64 value, int32_t unit, void* resObjPtr)
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
        ShapeAbstractModelNG::SetHeight(frameNode, resObj);
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
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("ShapeAbstractForegroundColor");
        if (SystemProperties::ConfigChangePerform() && resObjPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
            ShapeModelNG::SetFill(frameNode, resObj);
            ViewAbstract::SetForegroundColor(frameNode, foregroundColor, resObj);
        } else {
            ViewAbstract::SetForegroundColor(frameNode, foregroundColor);
        }
        ShapeModelNG::SetFill(frameNode, foregroundColor);
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
} // namespace

namespace NodeModifier {
const ArkUICommonShapeModifier* GetCommonShapeDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN();
        static const ArkUICommonShapeModifier modifier = {
            .setStrokeDashArray = SetStrokeDashArrayImpl,
            .resetStrokeDashArray = ResetStrokeDashArrayImpl,
            .setStrokeMiterLimit = SetStrokeMiterLimitImpl,
            .resetStrokeMiterLimit = ResetStrokeMiterLimitImpl,
            .setFillOpacity = SetFillOpacityImpl,
            .resetFillOpacity = ResetFillOpacityImpl,
            .setStrokeOpacity = SetStrokeOpacityImpl,
            .resetStrokeOpacity = ResetStrokeOpacityImpl,
            .setStrokeWidth = SetStrokeWidthImpl,
            .resetStrokeWidth = ResetStrokeWidthImpl,
            .setAntiAlias = SetAntiAliasImpl,
            .resetAntiAlias = ResetAntiAliasImpl,
            .setStroke = SetStrokeImpl,
            .resetStroke = ResetStrokeImpl,
            .setFill = SetFillImpl,
            .resetFill = ResetFillImpl,
            .setStrokeDashOffset = SetStrokeDashOffsetImpl,
            .resetStrokeDashOffset = ResetStrokeDashOffsetImpl,
            .setStrokeLineCap = SetStrokeLineCapImpl,
            .resetStrokeLineCap = ResetStrokeLineCapImpl,
            .setStrokeLineJoin = SetStrokeLineJoinImpl,
            .resetStrokeLineJoin = ResetStrokeLineJoinImpl,
            .setShapeWidth = SetShapeWidthImpl,
            .resetShapeWidth = ResetShapeWidthImpl,
            .setShapeHeight = SetShapeHeightImpl,
            .resetShapeHeight = ResetShapeHeightImpl,
            .setShapeForegroundColor = SetShapeForegroundColorImpl,
            .resetShapeForegroundColor = ResetShapeForegroundColorImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN();
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
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}

const CJUICommonShapeModifier* GetCJUICommonShapeDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
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
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
