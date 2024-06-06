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
    namespace TextPickerInterfaceModifier {
        void _setTextPickerOptionsImpl(Ark_NativePointer node, const Opt_TextPickerOptions* options) {
        }
    } // TextPickerInterfaceModifier
    namespace TextPickerAttributeModifier {
        void DefaultPickerItemHeightImpl(Ark_NativePointer node, const Type_TextPickerAttribute_defaultPickerItemHeight_Arg0* value) {
        }
        void CanLoopImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void DisappearTextStyleImpl(Ark_NativePointer node, const PickerTextStyle* value) {
        }
        void TextStyleImpl(Ark_NativePointer node, const PickerTextStyle* value) {
        }
        void SelectedTextStyleImpl(Ark_NativePointer node, const PickerTextStyle* value) {
        }
        void OnAcceptImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnCancelImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void SelectedIndexImpl(Ark_NativePointer node, const Type_TextPickerAttribute_selectedIndex_Arg0* value) {
        }
        void DividerImpl(Ark_NativePointer node, const Type_TextPickerAttribute_divider_Arg0* value) {
        }
        void GradientHeightImpl(Ark_NativePointer node, const Ark_Length* value) {
        }
    } // TextPickerAttributeModifier
    const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier() {
        static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
            TextPickerInterfaceModifier::_setTextPickerOptionsImpl,
            TextPickerAttributeModifier::DefaultPickerItemHeightImpl,
            TextPickerAttributeModifier::CanLoopImpl,
            TextPickerAttributeModifier::DisappearTextStyleImpl,
            TextPickerAttributeModifier::TextStyleImpl,
            TextPickerAttributeModifier::SelectedTextStyleImpl,
            TextPickerAttributeModifier::OnAcceptImpl,
            TextPickerAttributeModifier::OnCancelImpl,
            TextPickerAttributeModifier::OnChangeImpl,
            TextPickerAttributeModifier::SelectedIndexImpl,
            TextPickerAttributeModifier::DividerImpl,
            TextPickerAttributeModifier::GradientHeightImpl,
        };
        return &ArkUITextPickerModifierImpl;
    }

}
