/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components/web/resource/web_delegate.h"

namespace OHOS::Ace {
class NWebResponseAsyncHandle : public WebResponseAsyncHandle {
    DECLARE_ACE_TYPE(NWebResponseAsyncHandle, WebResponseAsyncHandle);
public:
    explicit NWebResponseAsyncHandle(std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> nwebResponse)
        :nwebResponse_(nwebResponse) {}
    ~NWebResponseAsyncHandle() = default;
    void HandleFileFd(int32_t fd) override
    {
        if (nwebResponse_ == nullptr) {
            return;
        }
        nwebResponse_->PutResponseFileHandle(fd);
    }

    void HandleData(std::string& data) override
    {
        if (nwebResponse_ == nullptr) {
            return;
        }
        nwebResponse_->PutResponseData(data);
    }

    void HandleResourceUrl(std::string& url) override
    {
        CHECK_NULL_VOID(nwebResponse_);
        nwebResponse_->PutResponseResourceUrl(url);
    }

    void HandleHeadersVal(const std::map<std::string, std::string>& response_headers) override
    {
        if (nwebResponse_ == nullptr) {
            return;
        }
        nwebResponse_->PutResponseHeaders(response_headers);
    }

    void HandleEncoding(std::string& encoding) override
    {
        if (nwebResponse_ == nullptr) {
            return;
        }
        nwebResponse_->PutResponseEncoding(encoding);
    }

    void HandleMimeType(std::string& mimeType) override
    {
        if (nwebResponse_ == nullptr) {
            return;
        }
        nwebResponse_->PutResponseMimeType(mimeType);
    }

    void HandleStatusCodeAndReason(int32_t statusCode, std::string& reason) override
    {
        if (nwebResponse_ == nullptr) {
            return;
        }
        nwebResponse_->PutResponseStateAndStatuscode(statusCode, reason);
    }

    void HandleResponseStatus(bool isReady) override
    {
        if (nwebResponse_ == nullptr) {
            return;
        }
        nwebResponse_->PutResponseDataStatus(isReady);
    }

private:
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> nwebResponse_;
};

bool OnJsCommonDialog(
    const WebClientImpl* webClientImpl,
    DialogEventType dialogEventType,
    std::shared_ptr<NWeb::NWebJSDialogResult> result,
    const std::string &url,
    const std::string &message,
    const std::string &value = "",
    RefPtr<TaskExecutor> task = nullptr,
    bool isReload = false)
{
    CHECK_NULL_RETURN(task, false);
    bool jsResult = false;
    auto param = std::make_shared<WebDialogEvent>(url, message, value, dialogEventType,
        AceType::MakeRefPtr<ResultOhos>(result), isReload);
    task->PostSyncTask(
        [&webClientImpl, dialogEventType, &param, &jsResult] {
            if (webClientImpl == nullptr) {
                return;
            }
            auto delegate = webClientImpl->GetWebDelegate();
            if (delegate) {
                jsResult = delegate->OnCommonDialog(param, dialogEventType);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientCommonDialogEvent");
    return jsResult;
}

void DownloadListenerImpl::OnDownloadStart(const std::string& url, const std::string& userAgent,
    const std::string& contentDisposition, const std::string& mimetype, long contentLength)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnDownloadStart(url, userAgent, contentDisposition, mimetype, contentLength);
}

void FindListenerImpl::OnFindResultReceived(
    const int activeMatchOrdinal, const int numberOfMatches, const bool isDoneCounting)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnSearchResultReceive(activeMatchOrdinal, numberOfMatches, isDoneCounting);
}

std::string SpanstringConvertHtmlImpl::SpanstringConvertHtml(const std::vector<uint8_t> &content)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return "";
    }
    return delegate->SpanstringConvertHtml(content);
}

void WebClientImpl::OnPageLoadEnd(int httpStatusCode, const std::string& url)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnPageFinished(url);
}

bool WebClientImpl::OnFocus()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    bool isFocused = delegate->RequestFocus();
    delegate->OnRequestFocus();

    delegate->SetToken();
    return isFocused;
}

bool WebClientImpl::OnFocus(OHOS::NWeb::NWebFocusSource source)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    bool isFocused = delegate->RequestFocus(source);
    delegate->OnRequestFocus();

    delegate->SetToken();
    return isFocused;
}

bool WebClientImpl::OnConsoleLog(const std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    bool jsMessage = false;
    auto task = delegate->GetTaskExecutor();
    if (!task) {
        return false;
    }
    task->PostSyncTask(
        [webClient = this, message, &jsMessage] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsMessage = delegate->OnConsoleLog(message);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientConsoleLog");

    return jsMessage;
}

void WebClientImpl::OnPageLoadBegin(const std::string& url)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnPageStarted(url);
}

void WebClientImpl::OnLoadingProgress(int newProgress)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnProgressChanged(newProgress);
}

void WebClientImpl::OnPageTitle(const std::string &title)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnReceivedTitle(title);
}

void WebClientImpl::OnFullScreenExit()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnFullScreenExit();
}

void WebClientImpl::OnFullScreenEnter(std::shared_ptr<NWeb::NWebFullScreenExitHandler> handler)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(handler);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnFullScreenEnter(handler, 0, 0);
}

void WebClientImpl::OnFullScreenEnterWithVideoSize(
    std::shared_ptr<NWeb::NWebFullScreenExitHandler> handler, int videoNaturalWidth, int videoNaturalHeight)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(handler);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnFullScreenEnter(handler, videoNaturalWidth, videoNaturalHeight);
}

void WebClientImpl::OnGeolocationHide()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnGeolocationPermissionsHidePrompt();
}

void WebClientImpl::OnGeolocationShow(const std::string& origin,
    std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface> callback)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
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
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnErrorReceive(request, error);
}

void WebClientImpl::OnHttpError(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    auto task = delegate->GetTaskExecutor();
    if (task == nullptr) {
        return;
    }
    std::weak_ptr<WebClientImpl> webClientWeak = shared_from_this();
    task->PostTask(
        [webClient = webClientWeak, request, response] {
            auto webClientUpgrade = webClient.lock();
            if (webClientUpgrade == nullptr) {
                return;
            }
            auto delegate = webClientUpgrade->GetWebDelegate();
            if (delegate) {
                delegate->OnHttpErrorReceive(request, response);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientHttpError");
}

void WebClientImpl::OnMessage(const std::string& param)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnMessage(param);
}

void WebClientImpl::OnRouterPush(const std::string& param)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnRouterPush(param);
}

bool WebClientImpl::OnHandleInterceptUrlLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    ContainerScope scope(delegate->GetInstanceId());

    bool result = delegate->OnHandleInterceptUrlLoading(request->Url());
    if (!result) {
        result = delegate->OnHandleInterceptLoading(request);
    }
    return result;
}

std::string WebClientImpl::OnHandleOverrideErrorPage(
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return "";
    }
    ContainerScope scope(delegate->GetInstanceId());

    return delegate->OnOverrideErrorPage(request, error);
}

bool WebClientImpl::OnHandleInterceptRequest(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
                                             std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate || (delegate->IsEmptyOnInterceptRequest())) {
        return false;
    }
    ContainerScope scope(delegate->GetInstanceId());

    auto webRequest = AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
        request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect());
    auto param = std::make_shared<OnInterceptRequestEvent>(webRequest);
    RefPtr<WebResponse> webResponse = nullptr;
    auto task = delegate->GetTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask(
        [&delegate, &webResponse, &param] {
            webResponse = delegate->OnInterceptRequest(param);
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientInterceptRequest");
    if (webResponse == nullptr) {
        return false;
    }
    std::string data = webResponse->GetData();
    response->PutResponseData(data);
    response->PutResponseHeaders(webResponse->GetHeaders());
    response->PutResponseMimeType(webResponse->GetMimeType());
    response->PutResponseEncoding(webResponse->GetEncoding());
    response->PutResponseStateAndStatuscode(webResponse->GetStatusCode(), webResponse->GetReason());
    switch (webResponse->GetDataType()) {
        case WebResponseDataType::FILE_TYPE:
            response->PutResponseFileHandle(webResponse->GetFileHandle());
            break;
        case WebResponseDataType::RESOURCE_URL_TYPE:
            response->PutResponseResourceUrl(webResponse->GetResourceUrl());
            break;
        case WebResponseDataType::BUFFER_TYPE:
            response->PutResponseDataBuffer(webResponse->GetBuffer(), webResponse->GetBufferSize());
            break;
        default:
            response->PutResponseData(data);
            break;
    }
    if (webResponse->GetResponseStatus() == false) {
        std::shared_ptr<NWebResponseAsyncHandle> asyncHandle = std::make_shared<NWebResponseAsyncHandle>(response);
        webResponse->SetAsyncHandle(asyncHandle);
        response->PutResponseDataStatus(false);
    }
    return true;
}

bool WebClientImpl::OnAlertDialogByJS(
    const std::string &url, const std::string &message, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_ALERT, result, url, message, "",
        delegate->GetTaskExecutor());
}

bool WebClientImpl::OnBeforeUnloadByJS(
    const std::string &url, const std::string &message, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD, result, url, message, "",
        delegate->GetTaskExecutor());
}

bool WebClientImpl::OnConfirmDialogByJS(
    const std::string &url, const std::string &message, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_CONFIRM, result, url, message, "",
        delegate->GetTaskExecutor());
}

bool WebClientImpl::OnPromptDialogByJS(const std::string &url, const std::string &message,
    const std::string &defaultValue, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_PROMPT, result, url, message, defaultValue,
        delegate->GetTaskExecutor());
}

void WebClientImpl::OnRenderExited(OHOS::NWeb::RenderExitReason reason)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnRenderExited(reason);
}

void WebClientImpl::OnRefreshAccessedHistory(const std::string& url, bool isReload)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnRefreshAccessedHistory(url, isReload);
}

bool WebClientImpl::OnFileSelectorShow(
    std::shared_ptr<NWeb::NWebStringVectorValueCallback> callback,
    std::shared_ptr<NWeb::NWebFileSelectorParams> params)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    bool jsResult = false;
    auto param = std::make_shared<FileSelectorEvent>(AceType::MakeRefPtr<FileSelectorParamOhos>(params),
        AceType::MakeRefPtr<FileSelectorResultOhos>(callback, delegate));
    auto task = delegate->GetTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask(
        [webClient = this, &param, &jsResult] {
            if (webClient == nullptr) {
                return;
            }
            auto delegate = webClient->GetWebDelegate();
            if (delegate) {
                jsResult = delegate->OnFileSelectorShow(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientFileSelectorShow");
    return jsResult;
}

void WebClientImpl::OnResource(const std::string& url)
{
    // Don't use RefPtr<WebDelegate> object here!
    // OnResource will be called in a background thread. When the RefPtr object is
    // the last reference, the destructor will be called here, which may cause
    // js-object-releasing of WebDelegate in non-main thread.
    auto task = Container::CurrentTaskExecutorSafely();
    CHECK_NULL_VOID(task);
    std::weak_ptr<WebClientImpl> webClientWeak = shared_from_this();
    task->PostTask(
        [webClient = webClientWeak, url] {
            auto webClientUpgrade = webClient.lock();
            if (webClientUpgrade == nullptr) {
                return;
            }
            auto delegate = webClientUpgrade->GetWebDelegate();
            if (delegate) {
                delegate->OnResourceLoad(url);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientResourceLoad");
}

void WebClientImpl::OnScaleChanged(float oldScaleFactor, float newScaleFactor)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnScaleChange(oldScaleFactor, newScaleFactor);
}

void WebClientImpl::OnScroll(double xOffset, double yOffset)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnScroll(xOffset, yOffset);
}

bool WebClientImpl::OnHttpAuthRequestByJS(std::shared_ptr<NWeb::NWebJSHttpAuthResult> result, const std::string &host,
    const std::string &realm)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());

    bool jsResult = false;
    auto param = std::make_shared<WebHttpAuthEvent>(AceType::MakeRefPtr<AuthResultOhos>(result), host, realm);
    auto task = delegate->GetTaskExecutor();
    CHECK_NULL_RETURN(task, false);
    task->PostSyncTask(
        [webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnHttpAuthRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientHttpAuthRequest");
    return jsResult;
}

bool WebClientImpl::OnSslErrorRequestByJS(std::shared_ptr<NWeb::NWebJSSslErrorResult> result,
    OHOS::NWeb::SslError error)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());

    bool jsResult = false;
    auto param = std::make_shared<WebSslErrorEvent>(AceType::MakeRefPtr<SslErrorResultOhos>(result),
        static_cast<int32_t>(error));
    auto task = delegate->GetTaskExecutor();
    CHECK_NULL_RETURN(task, false);
    task->PostSyncTask(
        [webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnSslErrorRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientSslErrorRequest");
    return jsResult;
}

bool WebClientImpl::OnAllSslErrorRequestByJS(std::shared_ptr<NWeb::NWebJSAllSslErrorResult> result,
    OHOS::NWeb::SslError error,
    const std::string& url,
    const std::string& originalUrl,
    const std::string& referrer,
    bool isFatalError,
    bool isMainFrame)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());

    bool jsResult = false;
    auto param = std::make_shared<WebAllSslErrorEvent>(AceType::MakeRefPtr<AllSslErrorResultOhos>(result),
        static_cast<int32_t>(error), url, originalUrl, referrer, isFatalError, isMainFrame);
    auto task = delegate->GetTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask(
        [webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnAllSslErrorRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientAllSslErrorRequest");
    return jsResult;
}

bool WebClientImpl::OnSslSelectCertRequestByJS(
    std::shared_ptr<NWeb::NWebJSSslSelectCertResult> result,
    const std::string& host,
    int port,
    const std::vector<std::string>& keyTypes,
    const std::vector<std::string>& issuers)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());

    bool jsResult = false;
    auto param = std::make_shared<WebSslSelectCertEvent>(AceType::MakeRefPtr<SslSelectCertResultOhos>(result),
        host, port, keyTypes, issuers);
    auto task = delegate->GetTaskExecutor();
    if (task == nullptr) {
        return false;
    }

    task->PostSyncTask(
        [webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnSslSelectCertRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientSslSelectCertRequest");

    return jsResult;
}

void WebClientImpl::OnPermissionRequest(std::shared_ptr<NWeb::NWebAccessRequest> request)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnPermissionRequestPrompt(request);
}

void WebClientImpl::OnScreenCaptureRequest(std::shared_ptr<NWeb::NWebScreenCaptureAccessRequest> request)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnScreenCaptureRequest(request);
}

bool WebClientImpl::RunContextMenu(
    std::shared_ptr<NWeb::NWebContextMenuParams> params,
    std::shared_ptr<NWeb::NWebContextMenuCallback> callback)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    bool jsResult = false;
    auto param = std::make_shared<ContextMenuEvent>(AceType::MakeRefPtr<ContextMenuParamOhos>(params),
        AceType::MakeRefPtr<ContextMenuResultOhos>(callback));
    auto task = delegate->GetTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask(
        [webClient = this, &param, &jsResult] {
            if (webClient == nullptr) {
                return;
            }
            auto delegate = webClient->GetWebDelegate();
            if (delegate) {
                jsResult = delegate->OnContextMenuShow(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebRunContextMenu");
    return jsResult;
}

void WebClientImpl::UpdateClippedSelectionBounds(int x, int y, int w, int h)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->UpdateClippedSelectionBounds(x, y, w, h);
}

bool WebClientImpl::RunQuickMenu(std::shared_ptr<NWeb::NWebQuickMenuParams> params,
                                 std::shared_ptr<NWeb::NWebQuickMenuCallback> callback)
{
    if (!params || !callback) {
        return false;
    }
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->RunQuickMenu(params, callback);
}

void WebClientImpl::HideHandleAndQuickMenuIfNecessary(bool hide)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->HideHandleAndQuickMenuIfNecessary(hide);
}

void WebClientImpl::ChangeVisibilityOfQuickMenu()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->ChangeVisibilityOfQuickMenu();
}

bool WebClientImpl::ChangeVisibilityOfQuickMenuV2()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->ChangeVisibilityOfQuickMenuV2();
}

void WebClientImpl::OnQuickMenuDismissed()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnQuickMenuDismissed();
}

void WebClientImpl::OnTouchSelectionChanged(
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnTouchSelectionChanged(
        insertHandle, startSelectionHandle, endSelectionHandle);
}

bool WebClientImpl::OnDragAndDropData(const void* data, size_t len, std::shared_ptr<NWeb::NWebImageOptions> opt)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    ContainerScope scope(delegate->GetInstanceId());
    if (opt) {
        return delegate->OnDragAndDropData(data, len, opt->GetWidth(), opt->GetHeight());
    }
    return delegate->OnDragAndDropData(data, len, 0, 0);
}

bool WebClientImpl::OnDragAndDropDataUdmf(std::shared_ptr<NWeb::NWebDragData> dragData)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->OnDragAndDropDataUdmf(dragData);
}

void WebClientImpl::UpdateDragCursor(NWeb::NWebDragData::DragOperation op)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->UpdateDragCursor(op);
}

void WebClientImpl::OnWindowNewByJS(
    const std::string& targetUrl,
    bool isAlert,
    bool isUserTrigger,
    std::shared_ptr<NWeb::NWebControllerHandler> handler)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnWindowNew(targetUrl, isAlert, isUserTrigger, handler);
}

void WebClientImpl::OnActivateContentByJS()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnActivateContent();
}

void WebClientImpl::OnWindowExitByJS()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnWindowExit();
}

void WebClientImpl::OnPageVisible(const std::string& url)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebClientImpl::OnPageVisible override enter");
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnPageVisible(url);
}

void WebClientImpl::OnDataResubmission(std::shared_ptr<NWeb::NWebDataResubmissionCallback> handler)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(handler);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnDataResubmitted(handler);
}

void WebClientImpl::OnNavigationEntryCommitted(
    std::shared_ptr<NWeb::NWebLoadCommittedDetails> details)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(details);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnNavigationEntryCommitted(details);
}

void WebClientImpl::OnPageIcon(const void* data,
                               size_t width,
                               size_t height,
                               NWeb::ImageColorType colorType,
                               NWeb::ImageAlphaType alphaType)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnFaviconReceived(data, width, height, colorType, alphaType);
}

void WebClientImpl::OnDesktopIconUrl(const std::string& icon_url, bool precomposed)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnTouchIconUrl(icon_url, precomposed);
}

bool WebClientImpl::OnCursorChange(const NWeb::CursorType& type, std::shared_ptr<NWeb::NWebCursorInfo> info)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->OnCursorChange(type, info);
}

void WebClientImpl::OnSelectPopupMenu(
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnSelectPopupMenu(params, callback);
}

void ReleaseSurfaceImpl::ReleaseSurface()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    if (!surfaceDelegate_) {
        return;
    }
    surfaceDelegate_->ReleaseSurface();
}

void WebClientImpl::OnAudioStateChanged(bool playing)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnAudioStateChanged(playing);
}

void WebClientImpl::OnFirstContentfulPaint(int64_t navigationStartTick, int64_t firstContentfulPaintMs)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnFirstContentfulPaint(navigationStartTick, firstContentfulPaintMs);
}

void WebClientImpl::OnFirstMeaningfulPaint(
    std::shared_ptr<NWeb::NWebFirstMeaningfulPaintDetails> details)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(details);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnFirstMeaningfulPaint(details);
}

void WebClientImpl::OnLargestContentfulPaint(
    std::shared_ptr<NWeb::NWebLargestContentfulPaintDetails> details)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(details);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnLargestContentfulPaint(details);
}


void WebClientImpl::OnSafeBrowsingCheckResult(int threat_type)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnSafeBrowsingCheckResult(threat_type);
}

void WebClientImpl::OnCompleteSwapWithNewSize()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnCompleteSwapWithNewSize();
}

void WebClientImpl::OnResizeNotWork()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnResizeNotWork();
}

void WebClientImpl::OnGetTouchHandleHotZone(std::shared_ptr<NWeb::NWebTouchHandleHotZone> hotZone)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnGetTouchHandleHotZone(hotZone);
}

void WebClientImpl::OnDateTimeChooserPopup(
    std::shared_ptr<NWeb::NWebDateTimeChooser> chooser,
    const std::vector<std::shared_ptr<NWeb::NWebDateTimeSuggestion>>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnDateTimeChooserPopup(chooser, suggestions, callback);
}

void WebClientImpl::OnDateTimeChooserClose()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnDateTimeChooserClose();
}

void WebClientImpl::OnOverScroll(float xOffset, float yOffset)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnOverScroll(xOffset, yOffset);
}

void WebClientImpl::OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnOverScrollFlingVelocity(xVelocity, yVelocity, isFling);
}

void WebClientImpl::OnOverScrollFlingEnd() {}

void WebClientImpl::OnScrollState(bool scrollState)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnScrollState(scrollState);
}

void WebClientImpl::EnableSecurityLayer(bool isNeedSecurityLayer)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->EnableSecurityLayer(isNeedSecurityLayer);
}

void WebClientImpl::OnNativeEmbedLifecycleChange(std::shared_ptr<NWeb::NWebNativeEmbedDataInfo> dataInfo)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnNativeEmbedLifecycleChange(dataInfo);
}
void WebClientImpl::OnNativeEmbedGestureEvent(std::shared_ptr<NWeb::NWebNativeEmbedTouchEvent> event)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnNativeEmbedGestureEvent(event);
}

void WebClientImpl::OnNativeEmbedMouseEvent(std::shared_ptr<NWeb::NWebNativeEmbedMouseEvent> event)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnNativeEmbedMouseEvent(event);
}

void WebClientImpl::OnRootLayerChanged(int width, int height)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnRootLayerChanged(width, height);
}

void WebClientImpl::ReleaseResizeHold()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->ReleaseResizeHold();
}

bool WebClientImpl::FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->FilterScrollEvent(x, y, xVelocity, yVelocity);
}

void WebClientImpl::OnIntelligentTrackingPreventionResult(
    const std::string& websiteHost, const std::string& trackerHost)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnIntelligentTrackingPreventionResult(websiteHost, trackerHost);
}

void WebClientImpl::OnTooltip(const std::string& tooltip)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnTooltip(tooltip);
}

void WebClientImpl::OnPopupSize(int x, int y, int width, int height)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnPopupSize(x, y, width, height);
}

void WebClientImpl::GetVisibleRectToWeb(int& visibleX, int& visibleY, int& visibleWidth, int& visibleHeight)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->GetVisibleRectToWeb(visibleX, visibleY, visibleWidth, visibleHeight);
}

void WebClientImpl::RestoreRenderFit()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->RestoreRenderFit();
}

void WebClientImpl::OnPopupShow(bool show)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnPopupShow(show);
}
bool WebClientImpl::OnHandleOverrideUrlLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    ContainerScope scope(delegate->GetInstanceId());

    bool result = delegate->OnHandleOverrideLoading(request);

    return result;
}

std::vector<int8_t> WebClientImpl::GetWordSelection(const std::string& text, int8_t offset)
{
    auto delegate = webDelegate_.Upgrade();
    std::vector<int8_t> vec = { -1, -1 };
    CHECK_NULL_RETURN(delegate, vec);
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->GetWordSelection(text, offset);
}

bool WebClientImpl::OnOpenAppLink(
    const std::string& url, std::shared_ptr<OHOS::NWeb::NWebAppLinkCallback> callback)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    ContainerScope scope(delegate->GetInstanceId());

    return delegate->OnOpenAppLink(url, callback);
}

void WebClientImpl::OnRenderProcessNotResponding(
    const std::string& jsStack, int pid, OHOS::NWeb::RenderProcessNotRespondingReason reason)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnRenderProcessNotResponding(jsStack, pid, reason);
}

void WebClientImpl::OnRenderProcessResponding()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnRenderProcessResponding();
}

void WebClientImpl::OnInterceptKeyboardAttach(
    const std::shared_ptr<OHOS::NWeb::NWebCustomKeyboardHandler> keyboardHandler,
    const std::map<std::string, std::string> &attributes, bool &useSystemKeyboard, int32_t &enterKeyType)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard OnInterceptKeyboardAttach override enter");
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnInterceptKeyboardAttach(keyboardHandler, attributes, useSystemKeyboard, enterKeyType);
}

void WebClientImpl::OnCustomKeyboardAttach()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard OnCustomKeyboardAttach override enter");
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnCustomKeyboardAttach();
}

void WebClientImpl::OnCustomKeyboardClose()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard OnCustomKeyboardClose override enter");
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnCustomKeyboardClose();
}

void WebClientImpl::OnShowAutofillPopup(
    const float offsetX, const float offsetY, const std::vector<std::string>& menu_items)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnShowAutofillPopup(offsetX, offsetY, menu_items);
}

void WebClientImpl::OnShowAutofillPopupV2(
    const float offsetX, const float offsetY, const float height, const float width,
    const std::vector<std::string>& menu_items)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnShowAutofillPopupV2(offsetX, offsetY, height, width, menu_items);
}

void WebClientImpl::OnHideAutofillPopup()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnHideAutofillPopup();
}

void WebClientImpl::OnViewportFitChange(OHOS::NWeb::ViewportFit viewportFit)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnViewportFitChange(viewportFit);
}

void WebClientImpl::CreateOverlay(void* data, size_t len, int width, int height, int offsetX, int offsetY,
    int rectWidth, int rectHeight, int pointX, int pointY)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->CreateOverlay(data, len, width, height, offsetX, offsetY, rectWidth, rectHeight, pointX, pointY);
}

void WebClientImpl::OnOverlayStateChanged(int offsetX, int offsetY, int rectWidth, int rectHeight)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnOverlayStateChanged(offsetX, offsetY, rectWidth, rectHeight);
}

void WebClientImpl::OnAdsBlocked(const std::string& url, const std::vector<std::string>& adsBlocked)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnAdsBlocked(url, adsBlocked);
}

void WebClientImpl::KeyboardReDispatch(
    std::shared_ptr<OHOS::NWeb::NWebKeyEvent> event, bool isUsed)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->KeyboardReDispatch(event, isUsed);
}

void WebClientImpl::OnCursorUpdate(double x, double y, double width, double height)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnCursorUpdate(x, y, width, height);
}

void WebClientImpl::ReportDynamicFrameLossEvent(const std::string& sceneId, bool isStart)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->ReportDynamicFrameLossEvent(sceneId, isStart);
}

void WebClientImpl::StartVibraFeedback(const std::string& vibratorType)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->StartVibraFeedback(vibratorType);
}

void WebClientImpl::OnNativeEmbedVisibilityChange(const std::string& embedId, bool visibility)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnNativeEmbedVisibilityChange(embedId, visibility);
}

bool WebClientImpl::CloseImageOverlaySelection()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->CloseImageOverlaySelection();
}

bool WebClientImpl::OnSslErrorRequestByJSV2(std::shared_ptr<NWeb::NWebJSSslErrorResult> result,
    OHOS::NWeb::SslError error, const std::vector<std::string>& certChainData)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());

    bool jsResult = false;
    auto param = std::make_shared<WebSslErrorEvent>(AceType::MakeRefPtr<SslErrorResultOhos>(result),
        static_cast<int32_t>(error), certChainData);
    auto task = delegate->GetTaskExecutor();
    CHECK_NULL_RETURN(task, false);
    task->PostSyncTask(
        [webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnSslErrorRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientSslErrorRequest");
    return jsResult;
}

void WebClientImpl::OnAccessibilityEventV2(int64_t accessibilityId, int32_t eventType, const std::string& argument)
{
    TAG_LOGI(AceLogTag::ACE_WEB,
        "OnAccessibilityEvent accessibilityId: %{public}" PRId64 ", eventType: %{public}d, argument: %{public}s",
        accessibilityId, eventType, argument.c_str());
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnAccessibilityEvent(accessibilityId, static_cast<AccessibilityEventType>(eventType), argument);
}

bool WebClientImpl::IsCurrentFocus()
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->IsCurrentFocus();
}

void WebClientImpl::OnScrollStart(const float x, const float y)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnScrollStart(x, y);
}

bool WebClientImpl::OnNestedScroll(float& x, float& y, float& xVelocity, float& yVelocity, bool& isAvailable)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return delegate->OnNestedScroll(x, y, xVelocity, yVelocity, isAvailable);
}

void WebClientImpl::OnPip(int status, int delegate_id, int child_id,
    int frame_routing_id, int width, int height)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebClientImpl::OnPip");
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnPip(status, delegate_id, child_id, frame_routing_id, width, height);
}

bool WebClientImpl::OnAllSslErrorRequestByJSV2(std::shared_ptr<NWeb::NWebJSAllSslErrorResult> result,
    OHOS::NWeb::SslError error,
    const std::string& url,
    const std::string& originalUrl,
    const std::string& referrer,
    bool isFatalError,
    bool isMainFrame,
    const std::vector<std::string>& certChainData)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());

    bool jsResult = false;
    auto param = std::make_shared<WebAllSslErrorEvent>(AceType::MakeRefPtr<AllSslErrorResultOhos>(result),
        static_cast<int32_t>(error), url, originalUrl, referrer, isFatalError, isMainFrame, certChainData);
    auto task = delegate->GetTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask(
        [webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnAllSslErrorRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebClientAllSslErrorRequest");
    return jsResult;
}

void WebClientImpl::ShowMagnifier()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->ShowMagnifier();
}

void WebClientImpl::HideMagnifier()
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->HideMagnifier();
}

void WebClientImpl::OnPageTitleV2(const std::string &title, bool isRealTitle)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    ContainerScope scope(delegate->GetInstanceId());
    delegate->OnReceivedTitle(title, isRealTitle);
}

void WebClientImpl::OnInsertBlanklessFrame(const std::string& pathToFrame)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    // pass directly without any judgment, CreateSnapshotFrameNode will check the parameter
    delegate->CreateSnapshotFrameNode(pathToFrame);
}

void WebClientImpl::OnRemoveBlanklessFrame(int delayTime)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->RemoveSnapshotFrameNode(delayTime);
}

bool WebClientImpl::OnBeforeUnloadByJSV2(
    const std::string& url, const std::string& message, bool isReload, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    ContainerScope scope(delegate->GetInstanceId());
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD, result, url, message, "",
        delegate->GetTaskExecutor(), isReload);
}
} // namespace OHOS::Ace
