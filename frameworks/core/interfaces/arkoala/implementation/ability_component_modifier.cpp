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
    namespace AbilityComponentInterfaceModifier {
        void _setAbilityComponentOptionsImpl(Ark_NativePointer node, const Type_AbilityComponentInterface__setAbilityComponentOptions_Arg0* value) {
        }
    } // AbilityComponentInterfaceModifier
    namespace AbilityComponentAttributeModifier {
        void OnConnectImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnDisconnectImpl(Ark_NativePointer node, Ark_Function callback) {
        }
    } // AbilityComponentAttributeModifier
    const GENERATED_ArkUIAbilityComponentModifier* GetAbilityComponentModifier() {
        static const GENERATED_ArkUIAbilityComponentModifier ArkUIAbilityComponentModifierImpl {
            AbilityComponentInterfaceModifier::_setAbilityComponentOptionsImpl,
            AbilityComponentAttributeModifier::OnConnectImpl,
            AbilityComponentAttributeModifier::OnDisconnectImpl,
        };
        return &ArkUIAbilityComponentModifierImpl;
    }

}
