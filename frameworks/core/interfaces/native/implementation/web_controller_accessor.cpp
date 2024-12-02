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
#include "core/interfaces/native/implementation/web_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebControllerAccessor {
static void DestroyPeer(WebControllerPeerImpl *peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
WebControllerPeer* CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<WebControllerPeerImpl>();
    peerImpl->IncRefCount();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    peerImpl->SetController(controller);
    return reinterpret_cast<WebControllerPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void OnInactiveImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    peerImpl->GetController()->OnInactive();
}
void OnActiveImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    peerImpl->GetController()->OnActive();
}
void ZoomImpl(WebControllerPeer* peer,
              const Ark_Number* factor)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    CHECK_NULL_VOID(factor);
    peerImpl->GetController()->Zoom(Converter::Convert<float>(*factor));
}
void ClearHistoryImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    peerImpl->GetController()->ClearHistory();
}
void RunJavaScriptImpl(WebControllerPeer* peer,
                       const Ark_Literal_String_script_Callback_String_Void_callback* options)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    CHECK_NULL_VOID(options);
    std::string script = Converter::Convert<std::string>(options->script);
    std::function<void(std::string)> callback = nullptr;
    auto arkFun = Converter::OptConvert<Callback_String_Void>(options->callback);
    if (arkFun) {
        LOGE("WebControllerAccessor::RunJavaScriptImpl callback supporting is not implemented yet");
    }
    peerImpl->GetController()->ExecuteTypeScript(script, std::move(callback));
}
void LoadDataImpl(WebControllerPeer* peer,
                  const Ark_Literal_String_baseUrl_data_encoding_historyUrl_mimeType* options)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    CHECK_NULL_VOID(options);
    std::string data = Converter::Convert<std::string>(options->data);
    std::string mimeType = Converter::Convert<std::string>(options->mimeType);
    std::string encoding = Converter::Convert<std::string>(options->encoding);
    std::string baseUrl = Converter::OptConvert<std::string>(options->baseUrl).value_or("");
    std::string historyUrl = Converter::OptConvert<std::string>(options->historyUrl).value_or("");
    peerImpl->GetController()->LoadDataWithBaseUrl(baseUrl, data, mimeType, encoding, historyUrl);
}
void LoadUrlImpl(WebControllerPeer* peer,
                 const Ark_Literal_Union_String_Resource_url_Array_Header_headers* options)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    CHECK_NULL_VOID(options);
    std::string url = Converter::OptConvert<std::string>(options->url).value_or("");
    std::map<std::string, std::string> httpHeaders;
    auto headersOpt = Converter::OptConvert<std::vector<Converter::Header>>(options->headers);
    if (headersOpt) {
        for (auto header : headersOpt.value()) {
            httpHeaders[header.headerKey] = header.headerValue;
        }
    }
    peerImpl->GetController()->LoadUrl(url, httpHeaders);
}
void RefreshImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    peerImpl->GetController()->Refresh();
}
void StopImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    peerImpl->GetController()->StopLoading();
}
void RegisterJavaScriptProxyImpl(WebControllerPeer* peer,
                                 const Ark_Literal_Object_object_String_name_Array_String_methodList* options)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    CHECK_NULL_VOID(options);
    LOGE("WebControllerAccessor::RegisterJavaScriptProxyImpl options->object argument is not supported");
    std::string objName = Converter::Convert<std::string>(options->name);
    std::vector<std::string> methods = Converter::Convert<std::vector<std::string>>(options->methodList);
    peerImpl->GetController()->AddJavascriptInterface(objName, methods);
}
void DeleteJavaScriptRegisterImpl(WebControllerPeer* peer,
                                  const Ark_String* name)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    CHECK_NULL_VOID(name);
    peerImpl->GetController()->RemoveJavascriptInterface(Converter::Convert<std::string>(*name), {});
}
Ark_NativePointer GetHitTestImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl && peerImpl->GetController(), 0);
    ContainerScope scope(peerImpl->GetInstanceId());
    LOGE("WebControllerAccessor::GetHitTestImpl is not fully implemented");
    peerImpl->GetController()->GetHitTestResult();
    return 0;
}
void RequestFocusImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    peerImpl->GetController()->RequestFocus();
}
Ark_Boolean AccessBackwardImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl && peerImpl->GetController(), Converter::ArkValue<Ark_Boolean>(false));
    ContainerScope scope(peerImpl->GetInstanceId());
    return Converter::ArkValue<Ark_Boolean>(peerImpl->GetController()->AccessBackward());
}
Ark_Boolean AccessForwardImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl && peerImpl->GetController(), Converter::ArkValue<Ark_Boolean>(false));
    ContainerScope scope(peerImpl->GetInstanceId());
    return Converter::ArkValue<Ark_Boolean>(peerImpl->GetController()->AccessForward());
}
Ark_Boolean AccessStepImpl(WebControllerPeer* peer,
                           const Ark_Number* step)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl && peerImpl->GetController(), Converter::ArkValue<Ark_Boolean>(false));
    ContainerScope scope(peerImpl->GetInstanceId());
    CHECK_NULL_RETURN(step, Converter::ArkValue<Ark_Boolean>(false));
    return Converter::ArkValue<Ark_Boolean>(
        peerImpl->GetController()->AccessStep(Converter::Convert<int32_t>(*step)));
}
void BackwardImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    peerImpl->GetController()->Backward();
}
void ForwardImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    ContainerScope scope(peerImpl->GetInstanceId());
    peerImpl->GetController()->Forward();
}
Ark_NativePointer GetCookieManagerImpl(WebControllerPeer* peer)
{
    auto peerImpl = reinterpret_cast<WebControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    auto cookiePeerImpl = peerImpl->GetCookieManager();
    return cookiePeerImpl ? Referenced::RawPtr(cookiePeerImpl) : nullptr;
}
} // WebControllerAccessor
const GENERATED_ArkUIWebControllerAccessor* GetWebControllerAccessor()
{
    static const GENERATED_ArkUIWebControllerAccessor WebControllerAccessorImpl {
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
