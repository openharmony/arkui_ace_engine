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
    namespace ClientAuthenticationHandlerModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void Confirm_string_stringImpl(ClientAuthenticationHandlerPeer* peer, const Ark_String* priKeyFile, const Ark_String* certChainFile) {
        }
        void Confirm_stringImpl(ClientAuthenticationHandlerPeer* peer, const Ark_String* authUri) {
        }
        void CancelImpl(ClientAuthenticationHandlerPeer* peer) {
        }
        void IgnoreImpl(ClientAuthenticationHandlerPeer* peer) {
        }
    } // ClientAuthenticationHandlerModifier
    const GENERATED_ArkUIClientAuthenticationHandlerAccessor* GetClientAuthenticationHandlerAccessor() {
        static const GENERATED_ArkUIClientAuthenticationHandlerAccessor ClientAuthenticationHandlerAccessorImpl {
            ClientAuthenticationHandlerModifier::CtorImpl,
            ClientAuthenticationHandlerModifier::GetFinalizerImpl,
            ClientAuthenticationHandlerModifier::Confirm_string_stringImpl,
            ClientAuthenticationHandlerModifier::Confirm_stringImpl,
            ClientAuthenticationHandlerModifier::CancelImpl,
            ClientAuthenticationHandlerModifier::IgnoreImpl,
        };
        return &ClientAuthenticationHandlerAccessorImpl;
    }

}
