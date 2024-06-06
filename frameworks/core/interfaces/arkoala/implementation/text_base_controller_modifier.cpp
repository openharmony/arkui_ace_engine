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
    namespace TextBaseControllerModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void SetSelectionImpl(TextBaseControllerPeer* peer, const Ark_Number* selectionStart, const Ark_Number* selectionEnd, const Opt_SelectionOptions* options) {
        }
        void CloseSelectionMenuImpl(TextBaseControllerPeer* peer) {
        }
        Ark_NativePointer GetLayoutManagerImpl(TextBaseControllerPeer* peer) {
            return 0;
        }
    } // TextBaseControllerModifier
    const GENERATED_ArkUITextBaseControllerAccessor* GetTextBaseControllerAccessor() {
        static const GENERATED_ArkUITextBaseControllerAccessor TextBaseControllerAccessorImpl {
            TextBaseControllerModifier::CtorImpl,
            TextBaseControllerModifier::GetFinalizerImpl,
            TextBaseControllerModifier::SetSelectionImpl,
            TextBaseControllerModifier::CloseSelectionMenuImpl,
            TextBaseControllerModifier::GetLayoutManagerImpl,
        };
        return &TextBaseControllerAccessorImpl;
    }

}
