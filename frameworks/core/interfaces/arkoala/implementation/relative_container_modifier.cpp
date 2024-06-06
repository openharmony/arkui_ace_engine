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
    namespace RelativeContainerInterfaceModifier {
        void _setRelativeContainerOptionsImpl(Ark_NativePointer node) {
        }
    } // RelativeContainerInterfaceModifier
    namespace RelativeContainerAttributeModifier {
        void GuideLineImpl(Ark_NativePointer node, const Array_GuideLineStyle* value) {
        }
        void Barrier_ArrayBarrierStyleImpl(Ark_NativePointer node, const Array_BarrierStyle* value) {
        }
        void Barrier_ArrayLocalizedBarrierStyleImpl(Ark_NativePointer node, const Array_LocalizedBarrierStyle* barrierStyle) {
        }
    } // RelativeContainerAttributeModifier
    const GENERATED_ArkUIRelativeContainerModifier* GetRelativeContainerModifier() {
        static const GENERATED_ArkUIRelativeContainerModifier ArkUIRelativeContainerModifierImpl {
            RelativeContainerInterfaceModifier::_setRelativeContainerOptionsImpl,
            RelativeContainerAttributeModifier::GuideLineImpl,
            RelativeContainerAttributeModifier::Barrier_ArrayBarrierStyleImpl,
            RelativeContainerAttributeModifier::Barrier_ArrayLocalizedBarrierStyleImpl,
        };
        return &ArkUIRelativeContainerModifierImpl;
    }

}
