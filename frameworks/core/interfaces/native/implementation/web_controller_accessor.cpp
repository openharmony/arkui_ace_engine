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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebControllerAccessor {
void DestroyPeerImpl(WebControllerPeer* peer)
{
}
WebControllerPeer* CtorImpl()
{
    return new WebControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void OnInactiveImpl(WebControllerPeer* peer)
{
}
void OnActiveImpl(WebControllerPeer* peer)
{
}
void ZoomImpl(WebControllerPeer* peer,
              const Ark_Number* factor)
{
}
void ClearHistoryImpl(WebControllerPeer* peer)
{
}
void RunJavaScriptImpl(WebControllerPeer* peer,
                       const Ark_Literal_String_script_Callback_String_Void_callback* options)
{
}
void LoadDataImpl(WebControllerPeer* peer,
                  const Ark_Literal_String_baseUrl_data_encoding_historyUrl_mimeType* options)
{
}
void LoadUrlImpl(WebControllerPeer* peer,
                 const Ark_Literal_Union_String_Resource_url_Array_Header_headers* options)
{
}
void RefreshImpl(WebControllerPeer* peer)
{
}
void StopImpl(WebControllerPeer* peer)
{
}
void RegisterJavaScriptProxyImpl(WebControllerPeer* peer,
                                 const Ark_Literal_Object_object_String_name_Array_String_methodList* options)
{
}
void DeleteJavaScriptRegisterImpl(WebControllerPeer* peer,
                                  const Ark_String* name)
{
}
Ark_NativePointer GetHitTestImpl(WebControllerPeer* peer)
{
    return 0;
}
void RequestFocusImpl(WebControllerPeer* peer)
{
}
Ark_Boolean AccessBackwardImpl(WebControllerPeer* peer)
{
    return 0;
}
Ark_Boolean AccessForwardImpl(WebControllerPeer* peer)
{
    return 0;
}
Ark_Boolean AccessStepImpl(WebControllerPeer* peer,
                           const Ark_Number* step)
{
    return 0;
}
void BackwardImpl(WebControllerPeer* peer)
{
}
void ForwardImpl(WebControllerPeer* peer)
{
}
Ark_NativePointer GetCookieManagerImpl(WebControllerPeer* peer)
{
    return 0;
}
} // WebControllerAccessor
const GENERATED_ArkUIWebControllerAccessor* GetWebControllerAccessor()
{
    static const GENERATED_ArkUIWebControllerAccessor WebControllerAccessorImpl {
        WebControllerAccessor::DestroyPeerImpl,
        WebControllerAccessor::CtorImpl,
        WebControllerAccessor::GetFinalizerImpl,
        WebControllerAccessor::OnInactiveImpl,
        WebControllerAccessor::OnActiveImpl,
        WebControllerAccessor::ZoomImpl,
        WebControllerAccessor::ClearHistoryImpl,
        WebControllerAccessor::RunJavaScriptImpl,
        WebControllerAccessor::LoadDataImpl,
        WebControllerAccessor::LoadUrlImpl,
        WebControllerAccessor::RefreshImpl,
        WebControllerAccessor::StopImpl,
        WebControllerAccessor::RegisterJavaScriptProxyImpl,
        WebControllerAccessor::DeleteJavaScriptRegisterImpl,
        WebControllerAccessor::GetHitTestImpl,
        WebControllerAccessor::RequestFocusImpl,
        WebControllerAccessor::AccessBackwardImpl,
        WebControllerAccessor::AccessForwardImpl,
        WebControllerAccessor::AccessStepImpl,
        WebControllerAccessor::BackwardImpl,
        WebControllerAccessor::ForwardImpl,
        WebControllerAccessor::GetCookieManagerImpl,
    };
    return &WebControllerAccessorImpl;
}

}
