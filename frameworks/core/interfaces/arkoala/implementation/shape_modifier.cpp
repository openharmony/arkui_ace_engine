/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ShapeInterfaceModifier {
void SetShapeOptions0Impl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
}
void SetShapeOptions1Impl(Ark_NativePointer node)
{
}
} // ShapeInterfaceModifier
namespace ShapeAttributeModifier {
void ViewPortImpl(Ark_NativePointer node,
                  const Type_ShapeAttribute_viewPort_Arg0* value)
{
}
void StrokeImpl(Ark_NativePointer node,
                const ResourceColor* value)
{
}
void FillImpl(Ark_NativePointer node,
              const ResourceColor* value)
{
}
void StrokeDashOffsetImpl(Ark_NativePointer node,
                          const Type_ShapeAttribute_strokeDashOffset_Arg0* value)
{
}
void StrokeDashArrayImpl(Ark_NativePointer node,
                         const Array_CustomObject* value)
{
}
void StrokeLineCapImpl(Ark_NativePointer node,
                       enum Ark_LineCapStyle value)
{
}
void StrokeLineJoinImpl(Ark_NativePointer node,
                        enum Ark_LineJoinStyle value)
{
}
void StrokeMiterLimitImpl(Ark_NativePointer node,
                          const Type_ShapeAttribute_strokeMiterLimit_Arg0* value)
{
}
void StrokeOpacityImpl(Ark_NativePointer node,
                       const Type_ShapeAttribute_strokeOpacity_Arg0* value)
{
}
void FillOpacityImpl(Ark_NativePointer node,
                     const Type_ShapeAttribute_fillOpacity_Arg0* value)
{
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Type_ShapeAttribute_strokeWidth_Arg0* value)
{
}
void AntiAliasImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void MeshImpl(Ark_NativePointer node,
              const Array_CustomObject* value,
              const Ark_Number* column,
              const Ark_Number* row)
{
}
} // ShapeAttributeModifier
const GENERATED_ArkUIShapeModifier* GetShapeModifier()
{
    static const GENERATED_ArkUIShapeModifier ArkUIShapeModifierImpl {
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
