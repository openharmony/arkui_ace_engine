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
    namespace NavigatorInterfaceModifier {
        void _setNavigatorOptions_targetstringtypeNavigationTypeImpl(Ark_NativePointer node, const Opt_Type_NavigatorInterface__setNavigatorOptions_Arg0* value) {
        }
        void _setNavigatorOptions_Impl(Ark_NativePointer node) {
        }
    } // NavigatorInterfaceModifier
    namespace NavigatorAttributeModifier {
        void ActiveImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void TypeImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void TargetImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void ParamsImpl(Ark_NativePointer node, const Ark_CustomObject* value) {
        }
    } // NavigatorAttributeModifier
    const GENERATED_ArkUINavigatorModifier* GetNavigatorModifier() {
        static const GENERATED_ArkUINavigatorModifier ArkUINavigatorModifierImpl {
            NavigatorInterfaceModifier::_setNavigatorOptions_targetstringtypeNavigationTypeImpl,
            NavigatorInterfaceModifier::_setNavigatorOptions_Impl,
            NavigatorAttributeModifier::ActiveImpl,
            NavigatorAttributeModifier::TypeImpl,
            NavigatorAttributeModifier::TargetImpl,
            NavigatorAttributeModifier::ParamsImpl,
        };
        return &ArkUINavigatorModifierImpl;
    }

}
