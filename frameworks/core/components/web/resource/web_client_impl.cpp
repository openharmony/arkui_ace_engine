/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components/web/resource/web_client_impl.h"

namespace OHOS::Ace {
void WebClientImpl::OnPageFinished(int httpStatusCode, const std::string& url)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnPageFinished(url);
}

void WebClientImpl::OnRequestFocus()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnRequestFocus();
}

void WebClientImpl::OnPageStarted(const std::string& url)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnPageStarted(url);
}

void WebClientImpl::SetWebView(std::shared_ptr<WebView> webview)
{
    webviewWeak_ = webview;
}

void WebClientImpl::OnProxyDied()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
}

void WebClientImpl::OnPageLoadError(int errorCode, const std::string& description, const std::string& failingUrl)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
}

void WebClientImpl::OnMessage(const std::string& param)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnMessage(param);
}

void WebClientImpl::OnRouterPush(const std::string& param)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnRouterPush(param);
}
} // namespace OHOS::Ace
