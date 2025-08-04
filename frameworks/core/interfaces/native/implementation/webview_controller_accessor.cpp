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

#ifdef WEB_SUPPORTED
#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_application_context.h"
#include "test/unittest/capi/stubs/mock_nweb_helper.h"
#else
#include "application_context.h"
#include "nweb_helper.h"
#endif // ARKUI_CAPI_UNITTEST
#endif // WEB_SUPPORTED
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/webview_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace webview_WebviewControllerAccessor {
void DestroyPeerImpl(Ark_webview_WebviewController peer)
{
    if (peer) {
        peer->DecRefCount();
    }
}
Ark_webview_WebviewController ConstructImpl()
{
    auto peer = Referenced::MakeRefPtr<webview_WebviewControllerPeer>();
    peer->IncRefCount();
    return Referenced::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void InitializeWebEngineImpl()
{
#ifdef WEB_SUPPORTED
    auto applicationContext = AbilityRuntime::ApplicationContext::GetApplicationContext();
    const std::string& bundlePath = applicationContext->GetBundleCodeDir();
    NWeb::NWebHelper::Instance().SetBundlePath(bundlePath);
    if (!NWeb::NWebHelper::Instance().InitAndRun(true)) {
        LOGE("ARKOALA InitializeWebEngine Failed.");
    }
#endif
}
void LoadUrlImpl(Ark_webview_WebviewController peer,
                 const Ark_Union_String_Resource* url,
                 const Opt_Array_webview_WebHeader* headers)
{
#ifdef WEB_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(url);
    CHECK_NULL_VOID(headers);
    auto nweb = NWeb::NWebHelper::Instance().GetNWeb(peer->nwebId);
    CHECK_NULL_VOID(nweb);
    std::string urlStr = Converter::OptConvert<std::string>(*url).value_or("");
    std::map<std::string, std::string> httpHeaders;
    auto headersOpt = Converter::OptConvert<std::vector<Converter::Header>>(*headers);
    if (headersOpt) {
        for (auto header : headersOpt.value()) {
            httpHeaders[header.headerKey] = header.headerValue;
        }
    }
    nweb->Load(urlStr, httpHeaders);
#endif
}
} // webview_WebviewControllerAccessor
const GENERATED_ArkUIWebview_WebviewControllerAccessor* GetWebview_WebviewControllerAccessor()
{
    static const GENERATED_ArkUIWebview_WebviewControllerAccessor Webview_WebviewControllerAccessorImpl {
        webview_WebviewControllerAccessor::DestroyPeerImpl,
        webview_WebviewControllerAccessor::ConstructImpl,
        webview_WebviewControllerAccessor::GetFinalizerImpl,
        webview_WebviewControllerAccessor::InitializeWebEngineImpl,
        webview_WebviewControllerAccessor::LoadUrlImpl,
    };
    return &Webview_WebviewControllerAccessorImpl;
}

}
