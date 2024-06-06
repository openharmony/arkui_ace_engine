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
    namespace LinearIndicatorInterfaceModifier {
        void _setLinearIndicatorOptionsImpl(Ark_NativePointer node, const Opt_Ark_Number* count, const Opt_LinearIndicatorController* controller) {
        }
    } // LinearIndicatorInterfaceModifier
    namespace LinearIndicatorAttributeModifier {
        void IndicatorStyleImpl(Ark_NativePointer node, const Opt_LinearIndicatorStyle* style) {
        }
        void IndicatorLoopImpl(Ark_NativePointer node, const Opt_Ark_Boolean* loop) {
        }
        void OnChangeImpl(Ark_NativePointer node, const Opt_Ark_Function* callback) {
        }
    } // LinearIndicatorAttributeModifier
    const GENERATED_ArkUILinearIndicatorModifier* GetLinearIndicatorModifier() {
        static const GENERATED_ArkUILinearIndicatorModifier ArkUILinearIndicatorModifierImpl {
            LinearIndicatorInterfaceModifier::_setLinearIndicatorOptionsImpl,
            LinearIndicatorAttributeModifier::IndicatorStyleImpl,
            LinearIndicatorAttributeModifier::IndicatorLoopImpl,
            LinearIndicatorAttributeModifier::OnChangeImpl,
        };
        return &ArkUILinearIndicatorModifierImpl;
    }

}
