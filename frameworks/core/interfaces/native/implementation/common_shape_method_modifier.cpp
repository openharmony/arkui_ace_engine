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

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonShapeMethodModifier {
namespace {
    const Color STROKE_DEFAULT = Color::TRANSPARENT;
    const Color FILL_DEFAULT = Color::BLACK;
    const double STROKE_MITERLIMIT_DEFAULT = 4.0f;
    const double STROKE_MITER_LIMIT_MIN_VALUE = 1.0;
    void validateStrokeMiterLimit(std::optional<float>& limit)
    {
        if (limit && limit.value() < STROKE_MITER_LIMIT_MIN_VALUE) {
            limit = 1.0;
        }
    }
} // namespace
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
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    ShapeAbstractModelNG::SetStroke(frameNode, color.value_or(STROKE_DEFAULT));
}
void FillImpl(Ark_NativePointer node,
              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    ShapeAbstractModelNG::SetFill(frameNode, color.value_or(FILL_DEFAULT));
}
void StrokeDashOffsetImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeDashOffset = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeDashOffset);
    Validator::ValidateNonPercent(strokeDashOffset);
    ShapeAbstractModelNG::SetStrokeDashOffset(frameNode, strokeDashOffset.value_or(Dimension(0.0)));
}
void StrokeLineCapImpl(Ark_NativePointer node,
                       const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto enumLineCapStyle = Converter::OptConvert<LineCapStyle>(*value);
    auto intLineCapStyle = EnumToInt(enumLineCapStyle);
    ShapeAbstractModelNG::SetStrokeLineCap(frameNode, intLineCapStyle.value_or(0));
}
void StrokeLineJoinImpl(Ark_NativePointer node,
                        const Opt_LineJoinStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto enumLineJoinStyle = Converter::OptConvert<LineJoinStyle>(*value);
    auto intLineJoinStyle = EnumToInt(enumLineJoinStyle);
    ShapeAbstractModelNG::SetStrokeLineJoin(frameNode, intLineJoinStyle.value_or(0));
}
void StrokeMiterLimitImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeMiterLimit = Converter::OptConvert<float>(*value);
    validateStrokeMiterLimit(strokeMiterLimit);
    ShapeAbstractModelNG::SetStrokeMiterLimit(frameNode, strokeMiterLimit.value_or(STROKE_MITERLIMIT_DEFAULT));
}
void StrokeOpacityImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeAbstractModelNG::SetStrokeOpacity(frameNode, strokeOpacity.value_or(1.0f));
}
void FillOpacityImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeOpacity = Converter::OptConvert<float>(*value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeAbstractModelNG::SetFillOpacity(frameNode, strokeOpacity.value_or(1.0f));
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto strokeWidth = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ShapeAbstractModelNG::SetStrokeWidth(frameNode, strokeWidth.value_or(1.0_vp));
}
void AntiAliasImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto antiAlias = Converter::OptConvert<bool>(*value);
    ShapeAbstractModelNG::SetAntiAlias(frameNode, antiAlias.value_or(false));
}
void StrokeDashArrayImpl(Ark_NativePointer node,
                         const Opt_Array_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ShapeAbstractModelNG::SetStrokeDashArray(frameNode, {});
        return;
    }
    auto strokeDashArray = Converter::Convert<std::vector<Dimension>>(value->value);
    // if odd,add twice
    int32_t length = value->value.length;
    if (length == static_cast<int32_t>(strokeDashArray.size()) && (length & 1)) {
        for (int32_t i = 0; i < length; ++i) {
            strokeDashArray.emplace_back(strokeDashArray[i]);
        }
    }
    ShapeAbstractModelNG::SetStrokeDashArray(frameNode, strokeDashArray);
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
