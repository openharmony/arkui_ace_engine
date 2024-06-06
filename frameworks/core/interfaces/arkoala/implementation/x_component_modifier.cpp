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
    namespace XComponentInterfaceModifier {
        void _setXComponentOptions_idstringtypestringlibrarynamestringcontrollerXComponentControllerImpl(Ark_NativePointer node, const Type_XComponentInterface__setXComponentOptions_Arg0* value) {
        }
        void _setXComponentOptions_idstringtypeXComponentTypelibrarynamestringcontrollerXComponentControllerImpl(Ark_NativePointer node, const Type_XComponentInterface__setXComponentOptions1_Arg0* value) {
        }
        void _setXComponentOptions_XComponentOptionsImpl(Ark_NativePointer node, const XComponentOptions* options) {
        }
    } // XComponentInterfaceModifier
    namespace XComponentAttributeModifier {
        void OnLoadImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnDestroyImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void EnableAnalyzerImpl(Ark_NativePointer node, Ark_Boolean enable) {
        }
    } // XComponentAttributeModifier
    const GENERATED_ArkUIXComponentModifier* GetXComponentModifier() {
        static const GENERATED_ArkUIXComponentModifier ArkUIXComponentModifierImpl {
            XComponentInterfaceModifier::_setXComponentOptions_idstringtypestringlibrarynamestringcontrollerXComponentControllerImpl,
            XComponentInterfaceModifier::_setXComponentOptions_idstringtypeXComponentTypelibrarynamestringcontrollerXComponentControllerImpl,
            XComponentInterfaceModifier::_setXComponentOptions_XComponentOptionsImpl,
            XComponentAttributeModifier::OnLoadImpl,
            XComponentAttributeModifier::OnDestroyImpl,
            XComponentAttributeModifier::EnableAnalyzerImpl,
        };
        return &ArkUIXComponentModifierImpl;
    }

}
