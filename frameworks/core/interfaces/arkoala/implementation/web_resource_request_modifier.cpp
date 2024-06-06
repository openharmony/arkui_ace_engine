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
    namespace WebResourceRequestModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        Ark_NativePointer GetRequestHeaderImpl(WebResourceRequestPeer* peer) {
            return 0;
        }
        void GetRequestUrlImpl(WebResourceRequestPeer* peer) {
        }
        Ark_Boolean IsRequestGestureImpl(WebResourceRequestPeer* peer) {
            return 0;
        }
        Ark_Boolean IsMainFrameImpl(WebResourceRequestPeer* peer) {
            return 0;
        }
        Ark_Boolean IsRedirectImpl(WebResourceRequestPeer* peer) {
            return 0;
        }
        void GetRequestMethodImpl(WebResourceRequestPeer* peer) {
        }
    } // WebResourceRequestModifier
    const GENERATED_ArkUIWebResourceRequestAccessor* GetWebResourceRequestAccessor() {
        static const GENERATED_ArkUIWebResourceRequestAccessor WebResourceRequestAccessorImpl {
            WebResourceRequestModifier::CtorImpl,
            WebResourceRequestModifier::GetFinalizerImpl,
            WebResourceRequestModifier::GetRequestHeaderImpl,
            WebResourceRequestModifier::GetRequestUrlImpl,
            WebResourceRequestModifier::IsRequestGestureImpl,
            WebResourceRequestModifier::IsMainFrameImpl,
            WebResourceRequestModifier::IsRedirectImpl,
            WebResourceRequestModifier::GetRequestMethodImpl,
        };
        return &WebResourceRequestAccessorImpl;
    }

}
