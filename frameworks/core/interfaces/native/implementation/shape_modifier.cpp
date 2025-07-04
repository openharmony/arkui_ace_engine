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
namespace ShapeModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ShapeModifier
namespace ShapeInterfaceModifier {
void SetShapeOptionsImpl(Ark_NativePointer node,
                         const Opt_image_PixelMap* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetShapeOptions(frameNode, convValue);
}
} // ShapeInterfaceModifier
namespace ShapeAttributeModifier {
void SetViewPortImpl(Ark_NativePointer node,
                     const Opt_ViewportRect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetViewPort(frameNode, convValue);
}
void SetStrokeImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetStroke(frameNode, convValue);
}
void SetFillImpl(Ark_NativePointer node,
                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetFill(frameNode, convValue);
}
void SetStrokeDashOffsetImpl(Ark_NativePointer node,
                             const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetStrokeDashOffset(frameNode, convValue);
}
void SetStrokeDashArrayImpl(Ark_NativePointer node,
                            const Opt_Array_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetStrokeDashArray(frameNode, convValue);
}
void SetStrokeLineCapImpl(Ark_NativePointer node,
                          const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetStrokeLineCap(frameNode, convValue);
}
void SetStrokeLineJoinImpl(Ark_NativePointer node,
                           const Opt_LineJoinStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetStrokeLineJoin(frameNode, convValue);
}
void SetStrokeMiterLimitImpl(Ark_NativePointer node,
                             const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetStrokeMiterLimit(frameNode, convValue);
}
void SetStrokeOpacityImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetStrokeOpacity(frameNode, convValue);
}
void SetFillOpacityImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetFillOpacity(frameNode, convValue);
}
void SetStrokeWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetStrokeWidth(frameNode, convValue);
}
void SetAntiAliasImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ShapeModelNG::SetSetAntiAlias(frameNode, convValue);
}
void SetMeshImpl(Ark_NativePointer node,
                 const Opt_Array_Number* value,
                 const Opt_Number* column,
                 const Opt_Number* row)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //ShapeModelNG::SetSetMesh(frameNode, convValue);
}
} // ShapeAttributeModifier
const GENERATED_ArkUIShapeModifier* GetShapeModifier()
{
    static const GENERATED_ArkUIShapeModifier ArkUIShapeModifierImpl {
        ShapeModifier::ConstructImpl,
        ShapeInterfaceModifier::SetShapeOptionsImpl,
        ShapeAttributeModifier::SetViewPortImpl,
        ShapeAttributeModifier::SetStrokeImpl,
        ShapeAttributeModifier::SetFillImpl,
        ShapeAttributeModifier::SetStrokeDashOffsetImpl,
        ShapeAttributeModifier::SetStrokeDashArrayImpl,
        ShapeAttributeModifier::SetStrokeLineCapImpl,
        ShapeAttributeModifier::SetStrokeLineJoinImpl,
        ShapeAttributeModifier::SetStrokeMiterLimitImpl,
        ShapeAttributeModifier::SetStrokeOpacityImpl,
        ShapeAttributeModifier::SetFillOpacityImpl,
        ShapeAttributeModifier::SetStrokeWidthImpl,
        ShapeAttributeModifier::SetAntiAliasImpl,
        ShapeAttributeModifier::SetMeshImpl,
    };
    return &ArkUIShapeModifierImpl;
}

}
