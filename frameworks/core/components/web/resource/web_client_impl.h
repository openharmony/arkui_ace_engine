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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEBVIEW_CLIENT_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEBVIEW_CLIENT_IMPL_H

#include "foundation/ace/ace_engine/frameworks/base/memory/referenced.h"
#include "webview_client.h"

#include "base/log/log.h"

namespace OHOS::Ace {
class WebDelegate;

class DownloadListenerImpl : public OHOS::WebView::DownloadListener {
public:
    DownloadListenerImpl() = default;
    ~DownloadListenerImpl() = default;

    void OnDownloadStart(const std::string& url, const std::string& userAgent, const std::string& contentDisposition,
        const std::string& mimetype, long contentLength) override;

    void SetWebDelegate(const WeakPtr<WebDelegate>& delegate)
    {
        webDelegate_ = delegate;
    }

private:
    WeakPtr<WebDelegate> webDelegate_;
};

class WebClientImpl : public OHOS::WebView::WebViewClient {
public:
    WebClientImpl() = default;
    ~WebClientImpl() = default;

    void SetWebView(std::shared_ptr<OHOS::WebView::WebView> webview) override;
    void OnProxyDied() override;
    void OnRouterPush(const std::string& param) override;
    void OnMessage(const std::string& param) override;
    void OnPageStarted(const std::string& url) override;
    void OnPageFinished(int httpStatusCode, const std::string& url) override;
    void OnProgressChanged(int newProgress) override;
    void OnReceivedTitle(const std::string &title) override;
    void OnGeolocationPermissionsHidePrompt() override;
    void OnGeolocationPermissionsShowPrompt(const std::string& origin,
        OHOS::WebView::GeolocationCallback* callback) override;

    void OnRequestFocus() override;
    void onReceivedError(std::shared_ptr<WebView::WebResourceRequest> request,
        std::shared_ptr<WebView::WebResourceError> error) override;
    bool ShouldOverrideUrlLoading(const std::string& url) override
    {
        return false;
    }
    void SetWebDelegate(const WeakPtr<WebDelegate>& delegate)
    {
        webDelegate_ = delegate;
    }

private:
    std::weak_ptr<OHOS::WebView::WebView> webviewWeak_;
    WeakPtr<WebDelegate> webDelegate_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEBVIEW_CLIENT_IMPL_H