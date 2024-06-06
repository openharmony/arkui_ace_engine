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
    namespace SaveButtonInterfaceModifier {
        void _setSaveButtonOptions_Impl(Ark_NativePointer node) {
        }
        void _setSaveButtonOptions_SaveButtonOptionsImpl(Ark_NativePointer node, const SaveButtonOptions* options) {
        }
    } // SaveButtonInterfaceModifier
    namespace SaveButtonAttributeModifier {
        void OnClickImpl(Ark_NativePointer node, Ark_Function event) {
        }
    } // SaveButtonAttributeModifier
    const GENERATED_ArkUISaveButtonModifier* GetSaveButtonModifier() {
        static const GENERATED_ArkUISaveButtonModifier ArkUISaveButtonModifierImpl {
            SaveButtonInterfaceModifier::_setSaveButtonOptions_Impl,
            SaveButtonInterfaceModifier::_setSaveButtonOptions_SaveButtonOptionsImpl,
            SaveButtonAttributeModifier::OnClickImpl,
        };
        return &ArkUISaveButtonModifierImpl;
    }

}
