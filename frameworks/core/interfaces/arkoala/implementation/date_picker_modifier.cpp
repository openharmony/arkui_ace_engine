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
    namespace DatePickerInterfaceModifier {
        void _setDatePickerOptionsImpl(Ark_NativePointer node, const Opt_DatePickerOptions* options) {
        }
    } // DatePickerInterfaceModifier
    namespace DatePickerAttributeModifier {
        void LunarImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void DisappearTextStyleImpl(Ark_NativePointer node, const PickerTextStyle* value) {
        }
        void TextStyleImpl(Ark_NativePointer node, const PickerTextStyle* value) {
        }
        void SelectedTextStyleImpl(Ark_NativePointer node, const PickerTextStyle* value) {
        }
        void OnChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnDateChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
    } // DatePickerAttributeModifier
    const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier() {
        static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
            DatePickerInterfaceModifier::_setDatePickerOptionsImpl,
            DatePickerAttributeModifier::LunarImpl,
            DatePickerAttributeModifier::DisappearTextStyleImpl,
            DatePickerAttributeModifier::TextStyleImpl,
            DatePickerAttributeModifier::SelectedTextStyleImpl,
            DatePickerAttributeModifier::OnChangeImpl,
            DatePickerAttributeModifier::OnDateChangeImpl,
        };
        return &ArkUIDatePickerModifierImpl;
    }

}
