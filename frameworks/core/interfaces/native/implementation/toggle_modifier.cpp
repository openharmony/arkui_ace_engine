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
namespace ToggleModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ToggleModifier
namespace ToggleInterfaceModifier {
void SetToggleOptionsImpl(Ark_NativePointer node,
                          const Ark_ToggleOptions* options)
{
}
} // ToggleInterfaceModifier
namespace ToggleAttributeModifier {
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Boolean_Void* value)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Opt_ContentModifier* value)
{
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
}
void SwitchPointColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
}
void SwitchStyleImpl(Ark_NativePointer node,
                     const Opt_SwitchStyle* value)
{
}
void _onChangeEvent_isOnImpl(Ark_NativePointer node,
                             const Callback_Boolean_Void* callback)
{
}
} // ToggleAttributeModifier
const GENERATED_ArkUIToggleModifier* GetToggleModifier()
{
    static const GENERATED_ArkUIToggleModifier ArkUIToggleModifierImpl {
        ToggleModifier::ConstructImpl,
        ToggleInterfaceModifier::SetToggleOptionsImpl,
        ToggleAttributeModifier::OnChangeImpl,
        ToggleAttributeModifier::ContentModifierImpl,
        ToggleAttributeModifier::SelectedColorImpl,
        ToggleAttributeModifier::SwitchPointColorImpl,
        ToggleAttributeModifier::SwitchStyleImpl,
        ToggleAttributeModifier::_onChangeEvent_isOnImpl,
    };
    return &ArkUIToggleModifierImpl;
}

}
