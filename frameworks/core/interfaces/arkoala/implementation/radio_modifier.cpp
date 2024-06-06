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
    namespace RadioInterfaceModifier {
        void _setRadioOptionsImpl(Ark_NativePointer node, const RadioOptions* options) {
        }
    } // RadioInterfaceModifier
    namespace RadioAttributeModifier {
        void CheckedImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void OnChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void RadioStyleImpl(Ark_NativePointer node, const Opt_RadioStyle* value) {
        }
        void ContentModifierImpl(Ark_NativePointer node, const Ark_CustomObject* modifier) {
        }
    } // RadioAttributeModifier
    const GENERATED_ArkUIRadioModifier* GetRadioModifier() {
        static const GENERATED_ArkUIRadioModifier ArkUIRadioModifierImpl {
            RadioInterfaceModifier::_setRadioOptionsImpl,
            RadioAttributeModifier::CheckedImpl,
            RadioAttributeModifier::OnChangeImpl,
            RadioAttributeModifier::RadioStyleImpl,
            RadioAttributeModifier::ContentModifierImpl,
        };
        return &ArkUIRadioModifierImpl;
    }

}
