/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebControllerAccessor {
void DestroyPeerImpl(Ark_WebController peer)
{
}
Ark_WebController CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void OnInactiveImpl(Ark_WebController peer)
{
}
void OnActiveImpl(Ark_WebController peer)
{
}
void ZoomImpl(Ark_WebController peer,
              const Ark_Number* factor)
{
}
void ClearHistoryImpl(Ark_WebController peer)
{
}
void RunJavaScriptImpl(Ark_WebController peer,
                       const Ark_Literal_String_script_Callback_String_Void_callback_* options)
{
}
void LoadDataImpl(Ark_WebController peer,
                  const Ark_Literal_String_baseUrl_data_encoding_historyUrl_mimeType* options)
{
}
void LoadUrlImpl(Ark_WebController peer,
                 const Ark_Literal_Union_String_Resource_url_Array_Header_headers* options)
{
}
void RefreshImpl(Ark_WebController peer)
{
}
void StopImpl(Ark_WebController peer)
{
}
void RegisterJavaScriptProxyImpl(Ark_WebController peer,
                                 const Ark_Literal_Object_object__String_name_Array_String_methodList* options)
{
}
void DeleteJavaScriptRegisterImpl(Ark_WebController peer,
                                  const Ark_String* name)
{
}
Ark_HitTestType GetHitTestImpl(Ark_WebController peer)
{
    return {};
}
void RequestFocusImpl(Ark_WebController peer)
{
}
Ark_Boolean AccessBackwardImpl(Ark_WebController peer)
{
    return {};
}
Ark_Boolean AccessForwardImpl(Ark_WebController peer)
{
    return {};
}
Ark_Boolean AccessStepImpl(Ark_WebController peer,
                           const Ark_Number* step)
{
    return {};
}
void BackwardImpl(Ark_WebController peer)
{
}
void ForwardImpl(Ark_WebController peer)
{
}
Ark_WebCookie GetCookieManagerImpl(Ark_WebController peer)
{
    return {};
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
