/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components/common/properties/paint_state.h"

namespace {
    static const double STROKE_MITER_LIMIT_MIN_VALUE = 1.0;
    void validateStrokeMiterLimit(std::optional<float>& limit)
    {
        if (limit && limit.value() < STROKE_MITER_LIMIT_MIN_VALUE) {
            limit = 1.0;
        }
    }
} // namespace

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonShapeMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void StrokeImpl(Ark_NativePointer node,
                const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelStatic::SetStroke(frameNode, Converter::OptConvert<Color>(*value));
}
void FillImpl(Ark_NativePointer node,
              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelStatic::SetFill(frameNode, Converter::OptConvert<Color>(*value));
}
void StrokeDashOffsetImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeDashOffset = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeDashOffset);
    Validator::ValidateNonPercent(strokeDashOffset);
    ShapeModelStatic::SetStrokeDashOffset(frameNode, strokeDashOffset);
}
void StrokeLineCapImpl(Ark_NativePointer node,
                       const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineCapStyle = Converter::OptConvert<LineCapStyle>(*value);
    auto intLineCapStyle = EnumToInt(enumLineCapStyle);
    ShapeModelStatic::SetStrokeLineCap(frameNode, intLineCapStyle);
}
void StrokeLineJoinImpl(Ark_NativePointer node,
                        const Opt_LineJoinStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineJoinStyle = Converter::OptConvert<LineJoinStyle>(*value);
    auto intLineJoinStyle = EnumToInt(enumLineJoinStyle);
    ShapeModelStatic::SetStrokeLineJoin(frameNode, intLineJoinStyle);
}
void StrokeMiterLimitImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeMiterLimit = Converter::OptConvert<float>(*value);
    validateStrokeMiterLimit(strokeMiterLimit);
    ShapeModelStatic::SetStrokeMiterLimit(frameNode, strokeMiterLimit);
}
void StrokeOpacityImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelStatic::SetStrokeOpacity(frameNode, strokeOpacity);
}
void FillOpacityImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelStatic::SetFillOpacity(frameNode, strokeOpacity);
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ShapeModelStatic::SetStrokeWidth(frameNode, std::nullopt);
        return;
    }
    auto strokeWidth = Converter::OptConvertFromArkLength(value->value, DimensionUnit::VP);
    Validator::ValidatePositive(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ShapeModelStatic::SetStrokeWidth(frameNode, strokeWidth);
}
void AntiAliasImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        ShapeModelNG::SetAntiAlias(frameNode, false);
        return;
    }
    ShapeModelNG::SetAntiAlias(frameNode, *convValue);
}
void StrokeDashArrayImpl(Ark_NativePointer node,
                         const Opt_Array_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::vector<Dimension> dashArray;
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ShapeModelNG::SetStrokeDashArray(frameNode, dashArray);
        return;
    }
    Array_Length arrayValue = value->value;
    int32_t length = arrayValue.length;
    for (int32_t i = 0; i < length; ++i) {
        auto optLength = Converter::OptConvertFromArkLength(arrayValue.array[i], DimensionUnit::VP);
        if (optLength.has_value()) {
            dashArray.emplace_back(optLength.value());
        }
    }
    // if odd,add twice
    auto dashArraySize = dashArray.size();
    if (dashArraySize & 1) {
        for (size_t i = 0; i < dashArraySize; ++i) {
            dashArray.emplace_back(dashArray[i]);
        }
    }
    ShapeModelNG::SetStrokeDashArray(frameNode, dashArray);
}
} // CommonShapeMethodModifier
const GENERATED_ArkUICommonShapeMethodModifier* GetCommonShapeMethodModifier()
{
    static const GENERATED_ArkUICommonShapeMethodModifier ArkUICommonShapeMethodModifierImpl {
        CommonShapeMethodModifier::ConstructImpl,
        CommonShapeMethodModifier::StrokeImpl,
        CommonShapeMethodModifier::FillImpl,
        CommonShapeMethodModifier::StrokeDashOffsetImpl,
        CommonShapeMethodModifier::StrokeLineCapImpl,
        CommonShapeMethodModifier::StrokeLineJoinImpl,
        CommonShapeMethodModifier::StrokeMiterLimitImpl,
        CommonShapeMethodModifier::StrokeOpacityImpl,
        CommonShapeMethodModifier::FillOpacityImpl,
        CommonShapeMethodModifier::StrokeWidthImpl,
        CommonShapeMethodModifier::AntiAliasImpl,
        CommonShapeMethodModifier::StrokeDashArrayImpl,
    };
    return &ArkUICommonShapeMethodModifierImpl;
}

}
