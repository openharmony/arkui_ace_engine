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
namespace FormComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // FormComponentModifier
namespace FormComponentInterfaceModifier {
void SetFormComponentOptionsImpl(Ark_NativePointer node,
                                 const Ark_FormInfo* value)
{
}
} // FormComponentInterfaceModifier
namespace FormComponentAttributeModifier {
void SizeImpl(Ark_NativePointer node,
              const Opt_SizeOptions* value)
{
}
void ModuleNameImpl(Ark_NativePointer node,
                    const Opt_String* value)
{
}
void DimensionImpl(Ark_NativePointer node,
                   const Opt_FormDimension* value)
{
}
void AllowUpdateImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
}
void VisibilityImpl(Ark_NativePointer node,
                    const Opt_Visibility* value)
{
}
void OnAcquiredImpl(Ark_NativePointer node,
                    const Opt_Callback_FormCallbackInfo_Void* value)
{
}
void OnErrorImpl(Ark_NativePointer node,
                 const Opt_Callback_Literal_Number_errcode_String_msg_Void* value)
{
}
void OnRouterImpl(Ark_NativePointer node,
                  const Opt_Callback_Any_Void* value)
{
}
void OnUninstallImpl(Ark_NativePointer node,
                     const Opt_Callback_FormCallbackInfo_Void* value)
{
}
void OnLoadImpl(Ark_NativePointer node,
                const Opt_Callback_Void* value)
{
}
} // FormComponentAttributeModifier
const GENERATED_ArkUIFormComponentModifier* GetFormComponentModifier()
{
    static const GENERATED_ArkUIFormComponentModifier ArkUIFormComponentModifierImpl {
        FormComponentModifier::ConstructImpl,
        FormComponentInterfaceModifier::SetFormComponentOptionsImpl,
        FormComponentAttributeModifier::SizeImpl,
        FormComponentAttributeModifier::ModuleNameImpl,
        FormComponentAttributeModifier::DimensionImpl,
        FormComponentAttributeModifier::AllowUpdateImpl,
        FormComponentAttributeModifier::VisibilityImpl,
        FormComponentAttributeModifier::OnAcquiredImpl,
        FormComponentAttributeModifier::OnErrorImpl,
        FormComponentAttributeModifier::OnRouterImpl,
        FormComponentAttributeModifier::OnUninstallImpl,
        FormComponentAttributeModifier::OnLoadImpl,
    };
    return &ArkUIFormComponentModifierImpl;
}

}
