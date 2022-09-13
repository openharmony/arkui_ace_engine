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

#include "core/common/container.h"
#include "core/components/web/resource/web_delegate.h"

namespace OHOS::Ace {

bool OnJsCommonDialog(
    const WebClientImpl* webClientImpl,
    DialogEventType dialogEventType,
    std::shared_ptr<NWeb::NWebJSDialogResult> result,
    const std::string &url,
    const std::string &message,
    const std::string &value = "")
{
    bool jsResult = false;
    auto param = std::make_shared<WebDialogEvent>(url, message, value, dialogEventType,
        AceType::MakeRefPtr<ResultOhos>(result));
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return false;
    }
    task->PostSyncTask([&webClientImpl, dialogEventType, &param, &jsResult] {
        if (webClientImpl == nullptr) {
            return;
        }
        auto delegate = webClientImpl->GetWebDelegate();
        if (delegate) {
            jsResult = delegate->OnCommonDialog(param.get(), dialogEventType);
        }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS);
    LOGI("OnJsCommonDialog result:%{public}d", jsResult);
    return jsResult;
}

void DownloadListenerImpl::OnDownloadStart(const std::string& url, const std::string& userAgent,
    const std::string& contentDisposition, const std::string& mimetype, long contentLength)
{
    ContainerScope scope(instanceId_);
    LOGI("OnDownloadStart.");
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnDownloadStart(url, userAgent, contentDisposition, mimetype, contentLength);
}

void FindListenerImpl::OnFindResultReceived(
    const int activeMatchOrdinal, const int numberOfMatches, const bool isDoneCounting)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnSearchResultReceive(activeMatchOrdinal, numberOfMatches, isDoneCounting);
}

void WebClientImpl::OnPageLoadEnd(int httpStatusCode, const std::string& url)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnPageFinished(url);
}

void WebClientImpl::OnFocus()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnRequestFocus();
}

bool WebClientImpl::OnConsoleLog(const OHOS::NWeb::NWebConsoleLog& message)
{
    ContainerScope scope(instanceId_);
    bool jsMessage = false;
    auto task = Container::CurrentTaskExecutor();
    if (!task) {
        return false;
    }
    task->PostSyncTask([webClient = this, &message, &jsMessage] {
        if (!webClient) {
            return;
        }
        auto delegate = webClient->webDelegate_.Upgrade();
        if (delegate) {
            jsMessage = delegate->OnConsoleLog(std::make_shared<OHOS::NWeb::NWebConsoleLog>(message));
        }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS);

    return jsMessage;
}

void WebClientImpl::OnPageLoadBegin(const std::string& url)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnPageStarted(url);
}

void WebClientImpl::OnLoadingProgress(int newProgress)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnProgressChanged(newProgress);
}

void WebClientImpl::OnPageTitle(const std::string &title)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnReceivedTitle(title);
}

void WebClientImpl::OnGeolocationHide()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnGeolocationPermissionsHidePrompt();
}

void WebClientImpl::OnGeolocationShow(const std::string& origin,
    OHOS::NWeb::NWebGeolocationCallbackInterface* callback)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnGeolocationPermissionsShowPrompt(origin, callback);
}

void WebClientImpl::SetNWeb(std::shared_ptr<OHOS::NWeb::NWeb> nweb)
{
    webviewWeak_ = nweb;
}

void WebClientImpl::OnProxyDied()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
}

void WebClientImpl::OnResourceLoadError(
    std::shared_ptr<NWeb::NWebUrlResourceRequest> request, std::shared_ptr<NWeb::NWebUrlResourceError> error)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnErrorReceive(request, error);
}

void WebClientImpl::OnHttpError(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnHttpErrorReceive(request, response);
}

void WebClientImpl::OnMessage(const std::string& param)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnMessage(param);
}

void WebClientImpl::OnRouterPush(const std::string& param)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnRouterPush(param);
}

bool WebClientImpl::OnHandleInterceptUrlLoading(const std::string& url)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    return delegate->OnHandleInterceptUrlLoading(url);
}

std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> WebClientImpl::OnHandleInterceptRequest(
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    ContainerScope scope(instanceId_);

    LOGI("OnHandleInterceptRequest url %{private}s", request->Url().c_str());
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return nullptr;
    }
    if (delegate->IsEmptyOnInterceptRequest() == true) {
        LOGI("OnHandleInterceptRequest is empty");
        return nullptr;
    }

    auto webRequest = AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(),
        request->Method(), request->Url(), request->FromGesture(),
        request->IsAboutMainFrame(), request->IsRequestRedirect());
    auto param = std::make_shared<OnInterceptRequestEvent>(webRequest);

    RefPtr<WebResponse> webResponse = nullptr;
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGE("can't get task executor");
        return nullptr;
    }
    task->PostSyncTask([&delegate, &webResponse, &param] {
            webResponse = delegate->OnInterceptRequest(param.get());
        }, OHOS::Ace::TaskExecutor::TaskType::JS);

    if (webResponse == nullptr) {
        LOGI("webResponse is null");
        return nullptr;
    }
    std::string data = webResponse->GetData();
    LOGI("intercept Encoding %{public}s",  webResponse->GetEncoding().c_str());
    LOGI("intercept GetMimeType %{public}s",  webResponse->GetMimeType().c_str());
    LOGI("intercept GetStatusCode %{public}d",  webResponse->GetStatusCode());
    LOGI("intercept GetReason %{public}s",  webResponse->GetReason().c_str());
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> nwebResponse =
        std::make_shared<OHOS::NWeb::NWebUrlResourceResponse>(webResponse->GetMimeType(), webResponse->GetEncoding(),
        webResponse->GetStatusCode(), webResponse->GetReason(), webResponse->GetHeaders(), data);
    return nwebResponse;
}

bool WebClientImpl::OnAlertDialogByJS(
    const std::string &url, const std::string &message, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    LOGI("OnAlertDialogByJS");
    ContainerScope scope(instanceId_);
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_ALERT, result, url, message);
}

bool WebClientImpl::OnBeforeUnloadByJS(
    const std::string &url, const std::string &message, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    LOGI("OnBeforeUnloadByJS");
    ContainerScope scope(instanceId_);
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD, result, url, message);
}

bool WebClientImpl::OnConfirmDialogByJS(
    const std::string &url, const std::string &message, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    LOGI("OnConfirmDialogByJS");
    ContainerScope scope(instanceId_);
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_CONFIRM, result, url, message);
}

bool WebClientImpl::OnPromptDialogByJS(const std::string &url, const std::string &message,
    const std::string &defaultValue, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    LOGI("OnPromptDialogByJS: %{public}s", defaultValue.c_str());
    ContainerScope scope(instanceId_);
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_PROMPT, result, url, message, defaultValue);
}

void WebClientImpl::OnRenderExited(OHOS::NWeb::RenderExitReason reason)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnRenderExited(reason);
}

void WebClientImpl::OnRefreshAccessedHistory(const std::string& url, bool isReload)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnRefreshAccessedHistory(url, isReload);
}

bool WebClientImpl::OnFileSelectorShow(
    std::shared_ptr<NWeb::FileSelectorCallback> callback,
    std::shared_ptr<NWeb::NWebFileSelectorParams> params)
{
    ContainerScope scope(instanceId_);
    bool jsResult = false;
    auto param = std::make_shared<FileSelectorEvent>(AceType::MakeRefPtr<FileSelectorParamOhos>(params),
        AceType::MakeRefPtr<FileSelectorResultOhos>(callback));
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
        if (webClient == nullptr) {
            return;
        }
        auto delegate = webClient->GetWebDelegate();
        if (delegate) {
            jsResult = delegate->OnFileSelectorShow(param.get());
        }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS);
    LOGI("OnFileSelectorShow result:%{public}d", jsResult);
    return jsResult;
}

void WebClientImpl::OnResource(const std::string& url)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnResourceLoad(url);
}

void WebClientImpl::OnScaleChanged(float oldScaleFactor, float newScaleFactor)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnScaleChange(oldScaleFactor, newScaleFactor);
}

void WebClientImpl::OnScroll(double xOffset, double yOffset)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnScroll(xOffset, yOffset);
}

bool WebClientImpl::OnHttpAuthRequestByJS(std::shared_ptr<NWeb::NWebJSHttpAuthResult> result, const std::string &host,
    const std::string &realm)
{
    LOGI("OnHttpAuthRequestByJS");
    ContainerScope scope(instanceId_);

    bool jsResult = false;
    auto param = std::make_shared<WebHttpAuthEvent>(AceType::MakeRefPtr<AuthResultOhos>(result), host, realm);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnHttpAuthRequest(param.get());
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS);

    LOGI("OnHttpAuthRequestByJS result:%{public}d", jsResult);
    return jsResult;
}

bool WebClientImpl::OnSslErrorRequestByJS(std::shared_ptr<NWeb::NWebJSSslErrorResult> result,
    OHOS::NWeb::SslError error)
{
    LOGI("OnSslErrorRequestByJS");
    ContainerScope scope(instanceId_);

    bool jsResult = false;
    auto param = std::make_shared<WebSslErrorEvent>(AceType::MakeRefPtr<SslErrorResultOhos>(result), static_cast<int32_t>(error));
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnSslErrorRequest(param.get());
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS);

    LOGI("OnSslErrorRequestByJS result:%{public}d", jsResult);
    return jsResult;
}

bool WebClientImpl::OnSslSelectCertRequestByJS(
    std::shared_ptr<NWeb::NWebJSSslSelectCertResult> result,
    const std::string& host,
    int port,
    const std::vector<std::string>& keyTypes,
    const std::vector<std::string>& issuers)
{
    LOGI("OnSslSelectCertRequestByJS");
    ContainerScope scope(instanceId_);

    bool jsResult = false;
    auto param = std::make_shared<WebSslSelectCertEvent>(AceType::MakeRefPtr<SslSelectCertResultOhos>(result),
        host, port, keyTypes, issuers);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return false;
    }
    LOGI("OnSslSelectCertRequestByJS PostSyncTask");

    task->PostSyncTask([webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            LOGI("OnSslSelectCertRequestByJS PostSyncTask delegate->OnSslSelectCertRequest");
            if (delegate) {
                jsResult = delegate->OnSslSelectCertRequest(param.get());
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS);

    LOGI("OnSslSelectCertRequestByJS result:%{public}d", jsResult);
    return jsResult;
}

void WebClientImpl::OnPermissionRequest(std::shared_ptr<NWeb::NWebAccessRequest> request)
{
    LOGI("OnPermissionRequest");
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnPermissionRequestPrompt(request);
}

bool WebClientImpl::RunContextMenu(
    std::shared_ptr<NWeb::NWebContextMenuParams> params,
    std::shared_ptr<NWeb::NWebContextMenuCallback> callback)
{
    ContainerScope scope(instanceId_);
    bool jsResult = false;
    auto param = std::make_shared<ContextMenuEvent>(AceType::MakeRefPtr<ContextMenuParamOhos>(params),
        AceType::MakeRefPtr<ContextMenuResultOhos>(callback));
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
        if (webClient == nullptr) {
            return;
        }
        auto delegate = webClient->GetWebDelegate();
        if (delegate) {
            jsResult = delegate->OnContextMenuShow(param.get());
        }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS);
    LOGI("OnContextMenuEventShow result:%{public}d", jsResult);
    return jsResult;
}

bool WebClientImpl::RunQuickMenu(std::shared_ptr<NWeb::NWebQuickMenuParams> params,
                                 std::shared_ptr<NWeb::NWebQuickMenuCallback> callback)
{
    if (!params || !callback) {
        return false;
    }
    ContainerScope scope(instanceId_);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return false;
    }
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    return delegate->RunQuickMenu(params, callback);
}

void WebClientImpl::OnQuickMenuDismissed()
{
    ContainerScope scope(instanceId_);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return;
    }
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnQuickMenuDismissed();
}

void WebClientImpl::OnTouchSelectionChanged(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    ContainerScope scope(instanceId_);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return;
    }
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnTouchSelectionChanged(
        insertHandle, startSelectionHandle, endSelectionHandle);
}

bool WebClientImpl::OnDragAndDropData(const void* data, size_t len, const NWeb::ImageOptions& opt)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    return delegate->OnDragAndDropData(data, len, opt.width, opt.height);
}
} // namespace OHOS::Ace
