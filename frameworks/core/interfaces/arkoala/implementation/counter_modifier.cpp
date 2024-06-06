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
    namespace CounterInterfaceModifier {
        void _setCounterOptionsImpl(Ark_NativePointer node) {
        }
    } // CounterInterfaceModifier
    namespace CounterAttributeModifier {
        void OnIncImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnDecImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void EnableDecImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void EnableIncImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
    } // CounterAttributeModifier
    const GENERATED_ArkUICounterModifier* GetCounterModifier() {
        static const GENERATED_ArkUICounterModifier ArkUICounterModifierImpl {
            CounterInterfaceModifier::_setCounterOptionsImpl,
            CounterAttributeModifier::OnIncImpl,
            CounterAttributeModifier::OnDecImpl,
            CounterAttributeModifier::EnableDecImpl,
            CounterAttributeModifier::EnableIncImpl,
        };
        return &ArkUICounterModifierImpl;
    }

}
