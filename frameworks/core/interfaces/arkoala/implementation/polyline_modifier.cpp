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
    namespace PolylineInterfaceModifier {
        void _setPolylineOptionsImpl(Ark_NativePointer node, const Opt_Type_PolylineInterface__setPolylineOptions_Arg0* value) {
        }
    } // PolylineInterfaceModifier
    namespace PolylineAttributeModifier {
        void PointsImpl(Ark_NativePointer node, const Array_Ark_CustomObject* value) {
        }
    } // PolylineAttributeModifier
    const GENERATED_ArkUIPolylineModifier* GetPolylineModifier() {
        static const GENERATED_ArkUIPolylineModifier ArkUIPolylineModifierImpl {
            PolylineInterfaceModifier::_setPolylineOptionsImpl,
            PolylineAttributeModifier::PointsImpl,
        };
        return &ArkUIPolylineModifierImpl;
    }

}
