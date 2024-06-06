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
    namespace StepperItemInterfaceModifier {
        void _setStepperItemOptionsImpl(Ark_NativePointer node) {
        }
    } // StepperItemInterfaceModifier
    namespace StepperItemAttributeModifier {
        void PrevLabelImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void NextLabelImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void StatusImpl(Ark_NativePointer node, const Opt_Ark_ItemState* value) {
        }
    } // StepperItemAttributeModifier
    const GENERATED_ArkUIStepperItemModifier* GetStepperItemModifier() {
        static const GENERATED_ArkUIStepperItemModifier ArkUIStepperItemModifierImpl {
            StepperItemInterfaceModifier::_setStepperItemOptionsImpl,
            StepperItemAttributeModifier::PrevLabelImpl,
            StepperItemAttributeModifier::NextLabelImpl,
            StepperItemAttributeModifier::StatusImpl,
        };
        return &ArkUIStepperItemModifierImpl;
    }

}
