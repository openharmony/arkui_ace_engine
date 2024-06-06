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
    namespace WebControllerModifier {
        Ark_NativePointer CtorImpl() {
            return 0;
        }
        Ark_NativePointer GetFinalizerImpl() {
            return 0;
        }
        void OnInactiveImpl(WebControllerPeer* peer) {
        }
        void OnActiveImpl(WebControllerPeer* peer) {
        }
        void ZoomImpl(WebControllerPeer* peer, const Ark_Number* factor) {
        }
        void ClearHistoryImpl(WebControllerPeer* peer) {
        }
        void RunJavaScriptImpl(WebControllerPeer* peer, const Literal_script_Ark_String_callback_Opt_Ark_Function* options) {
        }
        void LoadDataImpl(WebControllerPeer* peer, const Literal_data_Ark_String_mimeType_Ark_String_encoding_Ark_String_baseUrl_Opt_Ark_String_historyUrl_Opt_Ark_String* options) {
        }
        void LoadUrlImpl(WebControllerPeer* peer, const Literal_url_Union_Ark_String_Ark_Resource_headers_Opt_Array_Header* options) {
        }
        void RefreshImpl(WebControllerPeer* peer) {
        }
        void StopImpl(WebControllerPeer* peer) {
        }
        void RegisterJavaScriptProxyImpl(WebControllerPeer* peer, const Literal_object_Ark_CustomObject_name_Ark_String_methodList_Array_Ark_String* options) {
        }
        void DeleteJavaScriptRegisterImpl(WebControllerPeer* peer, const Ark_String* name) {
        }
        Ark_NativePointer GetHitTestImpl(WebControllerPeer* peer) {
            return 0;
        }
        void RequestFocusImpl(WebControllerPeer* peer) {
        }
        Ark_Boolean AccessBackwardImpl(WebControllerPeer* peer) {
            return 0;
        }
        Ark_Boolean AccessForwardImpl(WebControllerPeer* peer) {
            return 0;
        }
        Ark_Boolean AccessStepImpl(WebControllerPeer* peer, const Ark_Number* step) {
            return 0;
        }
        void BackwardImpl(WebControllerPeer* peer) {
        }
        void ForwardImpl(WebControllerPeer* peer) {
        }
        Ark_NativePointer GetCookieManagerImpl(WebControllerPeer* peer) {
            return 0;
        }
    } // WebControllerModifier
    const GENERATED_ArkUIWebControllerAccessor* GetWebControllerAccessor() {
        static const GENERATED_ArkUIWebControllerAccessor WebControllerAccessorImpl {
            WebControllerModifier::CtorImpl,
            WebControllerModifier::GetFinalizerImpl,
            WebControllerModifier::OnInactiveImpl,
            WebControllerModifier::OnActiveImpl,
            WebControllerModifier::ZoomImpl,
            WebControllerModifier::ClearHistoryImpl,
            WebControllerModifier::RunJavaScriptImpl,
            WebControllerModifier::LoadDataImpl,
            WebControllerModifier::LoadUrlImpl,
            WebControllerModifier::RefreshImpl,
            WebControllerModifier::StopImpl,
            WebControllerModifier::RegisterJavaScriptProxyImpl,
            WebControllerModifier::DeleteJavaScriptRegisterImpl,
            WebControllerModifier::GetHitTestImpl,
            WebControllerModifier::RequestFocusImpl,
            WebControllerModifier::AccessBackwardImpl,
            WebControllerModifier::AccessForwardImpl,
            WebControllerModifier::AccessStepImpl,
            WebControllerModifier::BackwardImpl,
            WebControllerModifier::ForwardImpl,
            WebControllerModifier::GetCookieManagerImpl,
        };
        return &WebControllerAccessorImpl;
    }

}
