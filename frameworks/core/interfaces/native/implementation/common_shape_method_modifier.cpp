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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

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
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetStroke(frameNode, convValue);
}
void SetFillImpl(Ark_NativePointer node,
                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetFill(frameNode, convValue);
}
void SetStrokeDashOffsetImpl(Ark_NativePointer node,
                             const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetStrokeDashOffset(frameNode, convValue);
}
void SetStrokeLineCapImpl(Ark_NativePointer node,
                          const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetStrokeLineCap(frameNode, convValue);
}
void SetStrokeLineJoinImpl(Ark_NativePointer node,
                           const Opt_LineJoinStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetStrokeLineJoin(frameNode, convValue);
}
void SetStrokeMiterLimitImpl(Ark_NativePointer node,
                             const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetStrokeMiterLimit(frameNode, convValue);
}
void SetStrokeOpacityImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetStrokeOpacity(frameNode, convValue);
}
void SetFillOpacityImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetFillOpacity(frameNode, convValue);
}
void SetStrokeWidthImpl(Ark_NativePointer node,
                        const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetStrokeWidth(frameNode, convValue);
}
void SetAntiAliasImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetAntiAlias(frameNode, convValue);
}
void SetStrokeDashArrayImpl(Ark_NativePointer node,
                            const Opt_Array_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonShapeMethodModelNG::SetSetStrokeDashArray(frameNode, convValue);
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
