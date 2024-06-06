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
    namespace UIExtensionComponentInterfaceModifier {
        void _setUIExtensionComponentOptionsImpl(Ark_NativePointer node, const Ark_CustomObject* want, const Opt_UIExtensionOptions* options) {
        }
    } // UIExtensionComponentInterfaceModifier
    namespace UIExtensionComponentAttributeModifier {
        void OnRemoteReadyImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnReceiveImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnResultImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnReleaseImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnErrorImpl(Ark_NativePointer node, const Ark_CustomObject* callback) {
        }
        void OnTerminatedImpl(Ark_NativePointer node, Ark_Function callback) {
        }
    } // UIExtensionComponentAttributeModifier
    const GENERATED_ArkUIUIExtensionComponentModifier* GetUIExtensionComponentModifier() {
        static const GENERATED_ArkUIUIExtensionComponentModifier ArkUIUIExtensionComponentModifierImpl {
            UIExtensionComponentInterfaceModifier::_setUIExtensionComponentOptionsImpl,
            UIExtensionComponentAttributeModifier::OnRemoteReadyImpl,
            UIExtensionComponentAttributeModifier::OnReceiveImpl,
            UIExtensionComponentAttributeModifier::OnResultImpl,
            UIExtensionComponentAttributeModifier::OnReleaseImpl,
            UIExtensionComponentAttributeModifier::OnErrorImpl,
            UIExtensionComponentAttributeModifier::OnTerminatedImpl,
        };
        return &ArkUIUIExtensionComponentModifierImpl;
    }

}
