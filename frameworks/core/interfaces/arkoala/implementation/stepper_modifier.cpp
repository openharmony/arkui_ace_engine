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
    namespace StepperInterfaceModifier {
        void _setStepperOptionsImpl(Ark_NativePointer node, const Opt_Type_StepperInterface__setStepperOptions_Arg0* value) {
        }
    } // StepperInterfaceModifier
    namespace StepperAttributeModifier {
        void OnFinishImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnSkipImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnChangeImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnNextImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnPreviousImpl(Ark_NativePointer node, Ark_Function callback) {
        }
    } // StepperAttributeModifier
    const GENERATED_ArkUIStepperModifier* GetStepperModifier() {
        static const GENERATED_ArkUIStepperModifier ArkUIStepperModifierImpl {
            StepperInterfaceModifier::_setStepperOptionsImpl,
            StepperAttributeModifier::OnFinishImpl,
            StepperAttributeModifier::OnSkipImpl,
            StepperAttributeModifier::OnChangeImpl,
            StepperAttributeModifier::OnNextImpl,
            StepperAttributeModifier::OnPreviousImpl,
        };
        return &ArkUIStepperModifierImpl;
    }

}
