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

#include "core/common/container.h"
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
    const std::string &value = "")
{
    bool jsResult = false;
    auto param = std::make_shared<WebDialogEvent>(url, message, value, dialogEventType,
        AceType::MakeRefPtr<ResultOhos>(result));
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask([&webClientImpl, dialogEventType, &param, &jsResult] {
        if (webClientImpl == nullptr) {
            return;
        }
        auto delegate = webClientImpl->GetWebDelegate();
        if (delegate) {
            jsResult = delegate->OnCommonDialog(param, dialogEventType);
        }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS);
    return jsResult;
}

void DownloadListenerImpl::OnDownloadStart(const std::string& url, const std::string& userAgent,
    const std::string& contentDisposition, const std::string& mimetype, long contentLength)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnDownloadStart(url, userAgent, contentDisposition, mimetype, contentLength);
}

void AccessibilityEventListenerImpl::OnAccessibilityEvent(int64_t accessibilityId, uint32_t eventType)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnAccessibilityEvent(accessibilityId, static_cast<AccessibilityEventType>(eventType));
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

bool WebClientImpl::OnFocus()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    bool isFocused = delegate->RequestFocus();
    delegate->OnRequestFocus();
    return isFocused;
}

bool WebClientImpl::OnConsoleLog(const std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message)
{
    ContainerScope scope(instanceId_);
    bool jsMessage = false;
    auto task = Container::CurrentTaskExecutor();
    if (!task) {
        return false;
    }
    task->PostSyncTask([webClient = this, message, &jsMessage] {
        if (!webClient) {
            return;
        }
        auto delegate = webClient->webDelegate_.Upgrade();
        if (delegate) {
            jsMessage = delegate->OnConsoleLog(message);
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

void WebClientImpl::OnFullScreenExit()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnFullScreenExit();
}

void WebClientImpl::OnFullScreenEnter(std::shared_ptr<NWeb::NWebFullScreenExitHandler> handler)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(handler);
    delegate->OnFullScreenEnter(handler, 0, 0);
}

void WebClientImpl::OnFullScreenEnterWithVideoSize(
    std::shared_ptr<NWeb::NWebFullScreenExitHandler> handler, int videoNaturalWidth, int videoNaturalHeight)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(handler);
    delegate->OnFullScreenEnter(handler, videoNaturalWidth, videoNaturalHeight);
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
    std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface> callback)
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

bool WebClientImpl::OnHandleInterceptUrlLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }

    bool result = delegate->OnHandleInterceptUrlLoading(request->Url());
    if (!result) {
        result = delegate->OnHandleInterceptLoading(request);
    }
    return result;
}

bool WebClientImpl::OnHandleInterceptRequest(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
                                             std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate || (delegate->IsEmptyOnInterceptRequest())) {
        return false;
    }

    auto webRequest = AceType::MakeRefPtr<WebRequest>(request->RequestHeaders(), request->Method(), request->Url(),
        request->FromGesture(), request->IsAboutMainFrame(), request->IsRequestRedirect());
    auto param = std::make_shared<OnInterceptRequestEvent>(webRequest);
    RefPtr<WebResponse> webResponse = nullptr;
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask([&delegate, &webResponse, &param] {
            webResponse = delegate->OnInterceptRequest(param);
        }, OHOS::Ace::TaskExecutor::TaskType::JS);
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
    ContainerScope scope(instanceId_);
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_ALERT, result, url, message);
}

bool WebClientImpl::OnBeforeUnloadByJS(
    const std::string &url, const std::string &message, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    ContainerScope scope(instanceId_);
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD, result, url, message);
}

bool WebClientImpl::OnConfirmDialogByJS(
    const std::string &url, const std::string &message, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
    ContainerScope scope(instanceId_);
    return OnJsCommonDialog(this, DialogEventType::DIALOG_EVENT_CONFIRM, result, url, message);
}

bool WebClientImpl::OnPromptDialogByJS(const std::string &url, const std::string &message,
    const std::string &defaultValue, std::shared_ptr<NWeb::NWebJSDialogResult> result)
{
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
    std::shared_ptr<NWeb::NWebStringVectorValueCallback> callback,
    std::shared_ptr<NWeb::NWebFileSelectorParams> params)
{
    ContainerScope scope(instanceId_);
    bool jsResult = false;
    auto param = std::make_shared<FileSelectorEvent>(AceType::MakeRefPtr<FileSelectorParamOhos>(params),
        AceType::MakeRefPtr<FileSelectorResultOhos>(callback));
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
        if (webClient == nullptr) {
            return;
        }
        auto delegate = webClient->GetWebDelegate();
        if (delegate) {
            jsResult = delegate->OnFileSelectorShow(param);
        }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS);
    return jsResult;
}

void WebClientImpl::OnResource(const std::string& url)
{
    ContainerScope scope(instanceId_);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        return;
    }
    std::weak_ptr<WebClientImpl> webClientWeak = shared_from_this();
    task->PostTask([webClient = webClientWeak, url] {
        auto webClientUpgrade = webClient.lock();
        if (webClientUpgrade == nullptr) {
            return;
        }
        auto delegate = webClientUpgrade->GetWebDelegate();
        if (delegate) {
            delegate->OnResourceLoad(url);
        }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS);
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
    ContainerScope scope(instanceId_);

    bool jsResult = false;
    auto param = std::make_shared<WebHttpAuthEvent>(AceType::MakeRefPtr<AuthResultOhos>(result), host, realm);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnHttpAuthRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS);
    return jsResult;
}

bool WebClientImpl::OnSslErrorRequestByJS(std::shared_ptr<NWeb::NWebJSSslErrorResult> result,
    OHOS::NWeb::SslError error)
{
    ContainerScope scope(instanceId_);

    bool jsResult = false;
    auto param = std::make_shared<WebSslErrorEvent>(AceType::MakeRefPtr<SslErrorResultOhos>(result), static_cast<int32_t>(error));
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnSslErrorRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS);
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
    ContainerScope scope(instanceId_);

    bool jsResult = false;
    auto param = std::make_shared<WebAllSslErrorEvent>(AceType::MakeRefPtr<AllSslErrorResultOhos>(result),
        static_cast<int32_t>(error), url, originalUrl, referrer, isFatalError, isMainFrame);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnAllSslErrorRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS);
    return jsResult;
}

bool WebClientImpl::OnSslSelectCertRequestByJS(
    std::shared_ptr<NWeb::NWebJSSslSelectCertResult> result,
    const std::string& host,
    int port,
    const std::vector<std::string>& keyTypes,
    const std::vector<std::string>& issuers)
{
    ContainerScope scope(instanceId_);

    bool jsResult = false;
    auto param = std::make_shared<WebSslSelectCertEvent>(AceType::MakeRefPtr<SslSelectCertResultOhos>(result),
        host, port, keyTypes, issuers);
    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        return false;
    }

    task->PostSyncTask([webClient = this, &param, &jsResult] {
            if (!webClient) {
                return;
            }
            auto delegate = webClient->webDelegate_.Upgrade();
            if (delegate) {
                jsResult = delegate->OnSslSelectCertRequest(param);
            }
        }, OHOS::Ace::TaskExecutor::TaskType::JS);

    return jsResult;
}

void WebClientImpl::OnPermissionRequest(std::shared_ptr<NWeb::NWebAccessRequest> request)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnPermissionRequestPrompt(request);
}

void WebClientImpl::OnScreenCaptureRequest(std::shared_ptr<NWeb::NWebScreenCaptureAccessRequest> request)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnScreenCaptureRequest(request);
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
        return false;
    }
    task->PostSyncTask([webClient = this, &param, &jsResult] {
        if (webClient == nullptr) {
            return;
        }
        auto delegate = webClient->GetWebDelegate();
        if (delegate) {
            jsResult = delegate->OnContextMenuShow(param);
        }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS);
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
        return;
    }
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return;
    }
    delegate->OnTouchSelectionChanged(
        insertHandle, startSelectionHandle, endSelectionHandle);
}

bool WebClientImpl::OnDragAndDropData(const void* data, size_t len, std::shared_ptr<NWeb::NWebImageOptions> opt)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    if (opt) {
        return delegate->OnDragAndDropData(data, len, opt->GetWidth(), opt->GetHeight());
    }
    return delegate->OnDragAndDropData(data, len, 0, 0);
}

bool WebClientImpl::OnDragAndDropDataUdmf(std::shared_ptr<NWeb::NWebDragData> dragData)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }
    return delegate->OnDragAndDropDataUdmf(dragData);
}

void WebClientImpl::UpdateDragCursor(NWeb::NWebDragData::DragOperation op)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->UpdateDragCursor(op);
}

void WebClientImpl::OnWindowNewByJS(
    const std::string& targetUrl,
    bool isAlert,
    bool isUserTrigger,
    std::shared_ptr<NWeb::NWebControllerHandler> handler)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnWindowNew(targetUrl, isAlert, isUserTrigger, handler);
}

void WebClientImpl::OnWindowExitByJS()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnWindowExit();
}

void WebClientImpl::OnPageVisible(const std::string& url)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnPageVisible(url);
}

void WebClientImpl::OnDataResubmission(std::shared_ptr<NWeb::NWebDataResubmissionCallback> handler)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(handler);
    delegate->OnDataResubmitted(handler);
}

void WebClientImpl::OnNavigationEntryCommitted(
    std::shared_ptr<NWeb::NWebLoadCommittedDetails> details)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(details);
    delegate->OnNavigationEntryCommitted(details);
}

void WebClientImpl::OnPageIcon(const void* data,
                               size_t width,
                               size_t height,
                               NWeb::ImageColorType colorType,
                               NWeb::ImageAlphaType alphaType)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnFaviconReceived(data, width, height, colorType, alphaType);
}

void WebClientImpl::OnDesktopIconUrl(const std::string& icon_url, bool precomposed)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnTouchIconUrl(icon_url, precomposed);
}

bool WebClientImpl::OnCursorChange(const NWeb::CursorType& type, const NWeb::NWebCursorInfo& info)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    return delegate->OnCursorChange(type, info);
}

void WebClientImpl::OnSelectPopupMenu(
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnSelectPopupMenu(params, callback);
}

void ReleaseSurfaceImpl::ReleaseSurface()
{
    ContainerScope scope(instanceId_);
    if (!surfaceDelegate_) {
        return;
    }
    surfaceDelegate_->ReleaseSurface();
}

void WebClientImpl::OnAudioStateChanged(bool playing)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnAudioStateChanged(playing);
}

void WebClientImpl::OnFirstContentfulPaint(int64_t navigationStartTick, int64_t firstContentfulPaintMs)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnFirstContentfulPaint(navigationStartTick, firstContentfulPaintMs);
}

void WebClientImpl::OnFirstMeaningfulPaint(
    std::shared_ptr<NWeb::NWebFirstMeaningfulPaintDetails> details)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(details);
    delegate->OnFirstMeaningfulPaint(details);
}

void WebClientImpl::OnLargestContentfulPaint(
    std::shared_ptr<NWeb::NWebLargestContentfulPaintDetails> details)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    CHECK_NULL_VOID(details);
    delegate->OnLargestContentfulPaint(details);
}


void WebClientImpl::OnSafeBrowsingCheckResult(int threat_type)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnSafeBrowsingCheckResult(threat_type);
}

void WebClientImpl::OnCompleteSwapWithNewSize()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnCompleteSwapWithNewSize();
}

void WebClientImpl::OnResizeNotWork()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnResizeNotWork();
}

void WebClientImpl::OnGetTouchHandleHotZone(std::shared_ptr<NWeb::NWebTouchHandleHotZone> hotZone)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnGetTouchHandleHotZone(hotZone);
}

void WebClientImpl::OnDateTimeChooserPopup(
    std::shared_ptr<NWeb::NWebDateTimeChooser> chooser,
    const std::vector<std::shared_ptr<NWeb::NWebDateTimeSuggestion>>& suggestions,
    std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnDateTimeChooserPopup(chooser, suggestions, callback);
}

void WebClientImpl::OnDateTimeChooserClose()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnDateTimeChooserClose();
}

void WebClientImpl::OnOverScroll(float xOffset, float yOffset)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnOverScroll(xOffset, yOffset);
}

void WebClientImpl::OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnOverScrollFlingVelocity(xVelocity, yVelocity, isFling);
}

void WebClientImpl::OnOverScrollFlingEnd() {}

void WebClientImpl::OnScrollState(bool scrollState)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnScrollState(scrollState);
}
void WebClientImpl::OnNativeEmbedLifecycleChange(std::shared_ptr<NWeb::NWebNativeEmbedDataInfo> dataInfo)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnNativeEmbedLifecycleChange(dataInfo);
}
void WebClientImpl::OnNativeEmbedGestureEvent(std::shared_ptr<NWeb::NWebNativeEmbedTouchEvent> event)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnNativeEmbedGestureEvent(event);
}

void WebClientImpl::OnRootLayerChanged(int width, int height)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnRootLayerChanged(width, height);
}

void WebClientImpl::ReleaseResizeHold()
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->ReleaseResizeHold();
}

bool WebClientImpl::FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_RETURN(delegate, false);
    return delegate->FilterScrollEvent(x, y, xVelocity, yVelocity);
}

void WebClientImpl::OnIntelligentTrackingPreventionResult(
    const std::string& websiteHost, const std::string& trackerHost)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnIntelligentTrackingPreventionResult(websiteHost, trackerHost);
}

void WebClientImpl::OnTooltip(const std::string& tooltip)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    CHECK_NULL_VOID(delegate);
    delegate->OnTooltip(tooltip);
}

bool WebClientImpl::OnHandleOverrideUrlLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return false;
    }

    bool result = delegate->OnHandleOverrideLoading(request);
    
    return result;
}

std::vector<int8_t> WebClientImpl::GetWordSelection(const std::string& text, int8_t offset)
{
    ContainerScope scope(instanceId_);
    auto delegate = webDelegate_.Upgrade();
    std::vector<int8_t> vec = { -1, -1 };
    CHECK_NULL_RETURN(delegate, vec);
    return delegate->GetWordSelection(text, offset);
}
} // namespace OHOS::Ace
