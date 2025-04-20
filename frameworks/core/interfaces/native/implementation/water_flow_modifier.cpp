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
namespace WaterFlowModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // WaterFlowModifier
namespace WaterFlowInterfaceModifier {
void SetWaterFlowOptionsImpl(Ark_NativePointer node,
                             const Opt_WaterFlowOptions* options)
{
}
} // WaterFlowInterfaceModifier
namespace WaterFlowAttributeModifier {
void ColumnsTemplateImpl(Ark_NativePointer node,
                         const Opt_String* value)
{
}
void ItemConstraintSizeImpl(Ark_NativePointer node,
                            const Opt_ConstraintSizeOptions* value)
{
}
void RowsTemplateImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
}
void ColumnsGapImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
}
void RowsGapImpl(Ark_NativePointer node,
                 const Opt_Length* value)
{
}
void LayoutDirectionImpl(Ark_NativePointer node,
                         const Opt_FlexDirection* value)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_NestedScrollOptions* value)
{
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
}
void FrictionImpl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
}
void CachedCount0Impl(Ark_NativePointer node,
                      const Opt_Number* value)
{
}
void CachedCount1Impl(Ark_NativePointer node,
                      const Opt_Number* count,
                      const Opt_Boolean* show)
{
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void OnScrollFrameBeginImpl(Ark_NativePointer node,
                            const Opt_Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
{
}
void OnScrollIndexImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Number_Void* value)
{
}
} // WaterFlowAttributeModifier
const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowModifier()
{
    static const GENERATED_ArkUIWaterFlowModifier ArkUIWaterFlowModifierImpl {
        WaterFlowModifier::ConstructImpl,
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
        WaterFlowAttributeModifier::CachedCount0Impl,
        WaterFlowAttributeModifier::CachedCount1Impl,
        WaterFlowAttributeModifier::OnReachStartImpl,
        WaterFlowAttributeModifier::OnReachEndImpl,
        WaterFlowAttributeModifier::OnScrollFrameBeginImpl,
        WaterFlowAttributeModifier::OnScrollIndexImpl,
    };
    return &ArkUIWaterFlowModifierImpl;
}

}
