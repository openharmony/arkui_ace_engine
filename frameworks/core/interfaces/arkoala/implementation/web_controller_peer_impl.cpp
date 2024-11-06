/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/arkoala/implementation/web_controller_peer_impl.h"

#include "core/common/container.h"

namespace OHOS::Ace::NG::GeneratedModifier {
WebControllerPeerImpl::WebControllerPeerImpl()
{
    instanceId_ = Container::CurrentId();
}

WebControllerPeerImpl::~WebControllerPeerImpl()
{
    if (webCookie_) {
        webCookie_->DecRefCount();
    }
}

const RefPtr<WebController>& WebControllerPeerImpl::GetController() const
{
    return webController_;
}

void WebControllerPeerImpl::SetController(const RefPtr<WebController>& webController)
{
    webController_ = webController;
}

void WebControllerPeerImpl::TriggerOnInactive()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->OnInactive();
    }
}

void WebControllerPeerImpl::TriggerOnActive()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->OnActive();
    }
}

void WebControllerPeerImpl::TriggerZoom(float factor)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->Zoom(factor);
    }
}

void WebControllerPeerImpl::TriggerClearHistory()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->ClearHistory();
    }
}

void WebControllerPeerImpl::TriggerLoadData(
    std::string baseUrl, std::string data, std::string mimeType, std::string encoding, std::string historyUrl)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->LoadDataWithBaseUrl(baseUrl, data, mimeType, encoding, historyUrl);
    }
}

void WebControllerPeerImpl::TriggerLoadUrl(std::string url, std::map<std::string, std::string>& httpHeaders)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->LoadUrl(url, httpHeaders);
    }
}

void WebControllerPeerImpl::TriggerRefresh()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->Refresh();
    }
}

void WebControllerPeerImpl::TriggerStop()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->StopLoading();
    }
}

void WebControllerPeerImpl::TriggerRequestFocus()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->RequestFocus();
    }
}

bool WebControllerPeerImpl::TriggerAccessBackward()
{
    ContainerScope scope(instanceId_);
    return webController_ ? webController_->AccessBackward() : false;
}

bool WebControllerPeerImpl::TriggerAccessForward()
{
    ContainerScope scope(instanceId_);
    return webController_ ? webController_->AccessForward() : false;
}

bool WebControllerPeerImpl::TriggerAccessStep(int32_t step)
{
    ContainerScope scope(instanceId_);
    return webController_ ? webController_->AccessStep(step) : false;
}

void WebControllerPeerImpl::TriggerBackward()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->Backward();
    }
}

void WebControllerPeerImpl::TriggerForward()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->Forward();
    }
}

RefPtr<WebCookiePeerImpl> WebControllerPeerImpl::TriggerGetCookieManager()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        if (!webController_->GetCookieManager()) {
            return nullptr;
        }
        if (webCookie_ == nullptr) {
            webCookie_ = Referenced::MakeRefPtr<WebCookiePeerImpl>();
            webCookie_->IncRefCount();
        }
    }
    return webCookie_;
}

void WebControllerPeerImpl::TriggerRegisterJavaScriptProxy(
    const std::string& objectName, const std::vector<std::string>& methodList)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->AddJavascriptInterface(objectName, methodList);
    }
}

void WebControllerPeerImpl::TriggerDeleteJavaScriptRegister(std::string objectName)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->RemoveJavascriptInterface(objectName, {});
    }
}

int WebControllerPeerImpl::TriggerGetHitTest()
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        return webController_->GetHitTestResult();
    }
    return 0;
}

void WebControllerPeerImpl::TriggerRunJavaScript(std::string jscode, std::function<void(std::string)>&& callback)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->ExecuteTypeScript(jscode, std::move(callback));
    }
}
} // namespace OHOS::Ace::NG::GeneratedModifier