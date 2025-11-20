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
void SetStrokeImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelStatic::SetStroke(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetFillImpl(Ark_NativePointer node,
                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ShapeModelStatic::SetFill(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetStrokeDashOffsetImpl(Ark_NativePointer node,
                             const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeDashOffset = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidatePositive(strokeDashOffset);
    Validator::ValidateNonPercent(strokeDashOffset);
    ShapeModelStatic::SetStrokeDashOffset(frameNode, strokeDashOffset);
}
void SetStrokeLineCapImpl(Ark_NativePointer node,
                          const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineCapStyle = Converter::OptConvertPtr<LineCapStyle>(value);
    auto intLineCapStyle = EnumToInt(enumLineCapStyle);
    ShapeModelStatic::SetStrokeLineCap(frameNode, intLineCapStyle);
}
void SetStrokeLineJoinImpl(Ark_NativePointer node,
                           const Opt_LineJoinStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto enumLineJoinStyle = Converter::OptConvertPtr<LineJoinStyle>(value);
    auto intLineJoinStyle = EnumToInt(enumLineJoinStyle);
    ShapeModelStatic::SetStrokeLineJoin(frameNode, intLineJoinStyle);
}
void SetStrokeMiterLimitImpl(Ark_NativePointer node,
                             const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeMiterLimit = Converter::OptConvertPtr<float>(value);
    validateStrokeMiterLimit(strokeMiterLimit);
    ShapeModelStatic::SetStrokeMiterLimit(frameNode, strokeMiterLimit);
}
void SetStrokeOpacityImpl(Ark_NativePointer node,
                          const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeOpacity = Converter::OptConvertPtr<float>(value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelStatic::SetStrokeOpacity(frameNode, strokeOpacity);
}
void SetFillOpacityImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeOpacity = Converter::OptConvertPtr<float>(value);
    Validator::ValidateOpacity(strokeOpacity);
    ShapeModelStatic::SetFillOpacity(frameNode, strokeOpacity);
}
void SetStrokeWidthImpl(Ark_NativePointer node,
                        const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto strokeWidth = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(strokeWidth);
    Validator::ValidateNonPercent(strokeWidth);
    ShapeModelStatic::SetStrokeWidth(frameNode, strokeWidth);
}
void SetAntiAliasImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        ShapeModelNG::SetAntiAlias(frameNode, false);
        return;
    }
    ShapeModelNG::SetAntiAlias(frameNode, *convValue);
}
void SetStrokeDashArrayImpl(Ark_NativePointer node,
                            const Opt_Array_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto dashArray = Converter::OptConvertPtr<std::vector<Dimension>>(value);
    if (!dashArray) {
        std::vector<Dimension> defaultDashArray;
        ShapeModelNG::SetStrokeDashArray(frameNode, defaultDashArray);
        return;
    }
    // if odd,add twice
    auto length = dashArray->size();
    if (length & 1) {
        for (size_t i = 0; i < length; i++) {
            dashArray->emplace_back((*dashArray)[i]);
        }
    }
    ShapeModelNG::SetStrokeDashArray(frameNode, std::move(*dashArray));
}
} // CommonShapeMethodModifier
const GENERATED_ArkUICommonShapeMethodModifier* GetCommonShapeMethodModifier()
{
    static const GENERATED_ArkUICommonShapeMethodModifier ArkUICommonShapeMethodModifierImpl {
        CommonShapeMethodModifier::ConstructImpl,
        CommonShapeMethodModifier::SetStrokeImpl,
        CommonShapeMethodModifier::SetFillImpl,
        CommonShapeMethodModifier::SetStrokeDashOffsetImpl,
        CommonShapeMethodModifier::SetStrokeLineCapImpl,
        CommonShapeMethodModifier::SetStrokeLineJoinImpl,
        CommonShapeMethodModifier::SetStrokeMiterLimitImpl,
        CommonShapeMethodModifier::SetStrokeOpacityImpl,
        CommonShapeMethodModifier::SetFillOpacityImpl,
        CommonShapeMethodModifier::SetStrokeWidthImpl,
        CommonShapeMethodModifier::SetAntiAliasImpl,
        CommonShapeMethodModifier::SetStrokeDashArrayImpl,
    };
    return &ArkUICommonShapeMethodModifierImpl;
}

}
