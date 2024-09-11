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
namespace WaterFlowInterfaceModifier {
void SetWaterFlowOptionsImpl(Ark_NativePointer node,
                             const Opt_WaterFlowOptions* options)
{
}
} // WaterFlowInterfaceModifier
namespace WaterFlowAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node,
                         const Ark_String* value)
{
}
void ItemConstraintSizeImpl(Ark_NativePointer node,
                            const Ark_ConstraintSizeOptions* value)
{
}
void RowsTemplateImpl(Ark_NativePointer node,
                      const Ark_String* value)
{
}
void ColumnsGapImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
}
void RowsGapImpl(Ark_NativePointer node,
                 const Ark_Length* value)
{
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         enum Ark_FlexDirection value)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Ark_NestedScrollOptions* value)
{
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
{
}
void FrictionImpl(Ark_NativePointer node,
                  const Type_WaterFlowAttribute_friction_Arg0* value)
{
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
}
void OnReachStartImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void OnReachEndImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            Ark_Function event)
{
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       Ark_Function event)
{
}
} // WaterFlowAttributeModifier
const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowModifier()
{
    static const GENERATED_ArkUIWaterFlowModifier ArkUIWaterFlowModifierImpl {
        WaterFlowInterfaceModifier::SetWaterFlowOptionsImpl,
        WaterFlowAttributeModifier::ColumnsTemplateImpl,
        WaterFlowAttributeModifier::ItemConstraintSizeImpl,
        WaterFlowAttributeModifier::RowsTemplateImpl,
        WaterFlowAttributeModifier::ColumnsGapImpl,
        WaterFlowAttributeModifier::RowsGapImpl,
        WaterFlowAttributeModifier::LayoutDirectionImpl,
        WaterFlowAttributeModifier::NestedScrollImpl,
        WaterFlowAttributeModifier::EnableScrollInteractionImpl,
        WaterFlowAttributeModifier::FrictionImpl,
        WaterFlowAttributeModifier::CachedCountImpl,
        WaterFlowAttributeModifier::OnReachStartImpl,
        WaterFlowAttributeModifier::OnReachEndImpl,
        WaterFlowAttributeModifier::OnScrollFrameBeginImpl,
        WaterFlowAttributeModifier::OnScrollIndexImpl,
    };
    return &ArkUIWaterFlowModifierImpl;
}

}
