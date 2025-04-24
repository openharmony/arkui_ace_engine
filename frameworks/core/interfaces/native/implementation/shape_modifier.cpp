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
void SetShapeOptions0Impl(Ark_NativePointer node,
                          Ark_PixelMap value)
{
}
void SetShapeOptions1Impl(Ark_NativePointer node)
{
}
} // ShapeInterfaceModifier
namespace ShapeAttributeModifier {
void ViewPortImpl(Ark_NativePointer node,
                  const Opt_ViewportRect* value)
{
}
void StrokeImpl(Ark_NativePointer node,
                const Opt_ResourceColor* value)
{
}
void FillImpl(Ark_NativePointer node,
              const Opt_ResourceColor* value)
{
}
void StrokeDashOffsetImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
}
void StrokeDashArrayImpl(Ark_NativePointer node,
                         const Opt_Array_Length* value)
{
}
void StrokeLineCapImpl(Ark_NativePointer node,
                       const Opt_LineCapStyle* value)
{
}
void StrokeLineJoinImpl(Ark_NativePointer node,
                        const Opt_LineJoinStyle* value)
{
}
void StrokeMiterLimitImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
{
}
void StrokeOpacityImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
}
void FillOpacityImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String* value)
{
}
void AntiAliasImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void MeshImpl(Ark_NativePointer node,
              const Array_Number* value,
              const Ark_Number* column,
              const Ark_Number* row)
{
}
} // ShapeAttributeModifier
const GENERATED_ArkUIShapeModifier* GetShapeModifier()
{
    static const GENERATED_ArkUIShapeModifier ArkUIShapeModifierImpl {
        ShapeModifier::ConstructImpl,
        ShapeInterfaceModifier::SetShapeOptions0Impl,
        ShapeInterfaceModifier::SetShapeOptions1Impl,
        ShapeAttributeModifier::ViewPortImpl,
        ShapeAttributeModifier::StrokeImpl,
        ShapeAttributeModifier::FillImpl,
        ShapeAttributeModifier::StrokeDashOffsetImpl,
        ShapeAttributeModifier::StrokeDashArrayImpl,
        ShapeAttributeModifier::StrokeLineCapImpl,
        ShapeAttributeModifier::StrokeLineJoinImpl,
        ShapeAttributeModifier::StrokeMiterLimitImpl,
        ShapeAttributeModifier::StrokeOpacityImpl,
        ShapeAttributeModifier::FillOpacityImpl,
        ShapeAttributeModifier::StrokeWidthImpl,
        ShapeAttributeModifier::AntiAliasImpl,
        ShapeAttributeModifier::MeshImpl,
    };
    return &ArkUIShapeModifierImpl;
}

}
