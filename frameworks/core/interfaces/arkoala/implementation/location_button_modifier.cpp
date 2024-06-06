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
    namespace LocationButtonInterfaceModifier {
        void _setLocationButtonOptions_Impl(Ark_NativePointer node) {
        }
        void _setLocationButtonOptions_LocationButtonOptionsImpl(Ark_NativePointer node, const LocationButtonOptions* options) {
        }
    } // LocationButtonInterfaceModifier
    namespace LocationButtonAttributeModifier {
        void OnClickImpl(Ark_NativePointer node, Ark_Function event) {
        }
    } // LocationButtonAttributeModifier
    const GENERATED_ArkUILocationButtonModifier* GetLocationButtonModifier() {
        static const GENERATED_ArkUILocationButtonModifier ArkUILocationButtonModifierImpl {
            LocationButtonInterfaceModifier::_setLocationButtonOptions_Impl,
            LocationButtonInterfaceModifier::_setLocationButtonOptions_LocationButtonOptionsImpl,
            LocationButtonAttributeModifier::OnClickImpl,
        };
        return &ArkUILocationButtonModifierImpl;
    }

}
