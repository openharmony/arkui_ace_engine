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
    namespace WebContextMenuResultModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void CloseContextMenuImpl(WebContextMenuResultPeer* peer) {
        }
        void CopyImageImpl(WebContextMenuResultPeer* peer) {
        }
        void CopyImpl(WebContextMenuResultPeer* peer) {
        }
        void PasteImpl(WebContextMenuResultPeer* peer) {
        }
        void CutImpl(WebContextMenuResultPeer* peer) {
        }
        void SelectAllImpl(WebContextMenuResultPeer* peer) {
        }
    } // WebContextMenuResultModifier
    const GENERATED_ArkUIWebContextMenuResultAccessor* GetWebContextMenuResultAccessor() {
        static const GENERATED_ArkUIWebContextMenuResultAccessor WebContextMenuResultAccessorImpl {
            WebContextMenuResultModifier::CtorImpl,
            WebContextMenuResultModifier::GetFinalizerImpl,
            WebContextMenuResultModifier::CloseContextMenuImpl,
            WebContextMenuResultModifier::CopyImageImpl,
            WebContextMenuResultModifier::CopyImpl,
            WebContextMenuResultModifier::PasteImpl,
            WebContextMenuResultModifier::CutImpl,
            WebContextMenuResultModifier::SelectAllImpl,
        };
        return &WebContextMenuResultAccessorImpl;
    }

}
