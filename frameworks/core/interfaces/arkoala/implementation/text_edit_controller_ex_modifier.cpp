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
    namespace TextEditControllerExModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        Ark_Boolean IsEditingImpl(TextEditControllerExPeer* peer) {
            return 0;
        }
        void StopEditingImpl(TextEditControllerExPeer* peer) {
        }
        Ark_Boolean SetCaretOffsetImpl(TextEditControllerExPeer* peer, const Ark_Number* offset) {
            return 0;
        }
        Ark_Int32 GetCaretOffsetImpl(TextEditControllerExPeer* peer) {
            return 0;
        }
    } // TextEditControllerExModifier
    const GENERATED_ArkUITextEditControllerExAccessor* GetTextEditControllerExAccessor() {
        static const GENERATED_ArkUITextEditControllerExAccessor TextEditControllerExAccessorImpl {
            TextEditControllerExModifier::CtorImpl,
            TextEditControllerExModifier::GetFinalizerImpl,
            TextEditControllerExModifier::IsEditingImpl,
            TextEditControllerExModifier::StopEditingImpl,
            TextEditControllerExModifier::SetCaretOffsetImpl,
            TextEditControllerExModifier::GetCaretOffsetImpl,
        };
        return &TextEditControllerExAccessorImpl;
    }

}
