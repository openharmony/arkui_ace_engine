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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_EVENT_H

#include <map>

#include "base/memory/ace_type.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace {

enum DialogEventType {
    DIALOG_EVENT_ALERT = 0,
    DIALOG_EVENT_BEFORE_UNLOAD = 1,
    DIALOG_EVENT_CONFIRM = 2,
    DIALOG_EVENT_PROMPT = 3
};

class WebConsoleLog : public AceType {
    DECLARE_ACE_TYPE(WebConsoleLog, AceType)
public:
    WebConsoleLog() = default;
    ~WebConsoleLog() = default;

    virtual int GetLineNumber() = 0;
    virtual std::string GetLog() = 0;
    virtual int GetLogLevel() = 0;
    virtual std::string GetSourceId() = 0;
};

class WebFileSelectorParam : public AceType {
    DECLARE_ACE_TYPE(WebFileSelectorParam, AceType)
public:
    WebFileSelectorParam() = default;
    ~WebFileSelectorParam() = default;

    virtual std::string GetTitle() = 0;
    virtual int GetMode() = 0;
    virtual std::string GetDefaultFileName() = 0;
    virtual std::vector<std::string> GetAcceptType() = 0;
    virtual bool IsCapture() = 0;
};

class ACE_EXPORT WebError : public AceType {
    DECLARE_ACE_TYPE(WebError, AceType)

public:
    WebError(const std::string& info, int32_t code) : info_(info), code_(code) {}
    ~WebError() = default;

    const std::string& GetInfo() const
    {
        return info_;
    }

    int32_t GetCode() const
    {
        return code_;
    }

private:
    std::string info_;
    int32_t code_;
};

enum class WebResponseDataType : int32_t {
    STRING_TYPE,
    FILE_TYPE,
    RESOURCE_URL_TYPE,
};

class WebResponseAsyncHandle : public AceType {
    DECLARE_ACE_TYPE(WebResponseAsyncHandle, AceType)
public:
    WebResponseAsyncHandle() = default;
    virtual ~WebResponseAsyncHandle() = default;

    virtual void HandleData(std::string& data) = 0;
    virtual void HandleFileFd(int32_t fd) = 0;
    virtual void HandleResourceUrl(std::string& url) = 0;
    virtual void HandleHeadersVal(const std::map<std::string, std::string>& response_headers) = 0;
    virtual void HandleEncoding(std::string& encoding) = 0;
    virtual void HandleMimeType(std::string& mimeType) = 0;
    virtual void HandleStatusCodeAndReason(int32_t statusCode, std::string& reason) = 0;
    virtual void HandleResponseStatus(bool isReady) = 0;
};

class ACE_EXPORT WebResponse : public AceType {
    DECLARE_ACE_TYPE(WebResponse, AceType)

public:
    WebResponse(const std::map<std::string, std::string>& headers, const std::string& data, const std::string& encoding,
        const std::string& mimeType, const std::string& reason, int32_t statusCode)
        : headers_(headers), data_(data), encoding_(encoding), mimeType_(mimeType), reason_(reason),
          statusCode_(statusCode)
    {}
    WebResponse() = default;
    ~WebResponse() = default;

    const std::map<std::string, std::string>& GetHeaders() const
    {
        return headers_;
    }

    const std::string& GetData() const
    {
        return data_;
    }

    const std::string& GetEncoding() const
    {
        return encoding_;
    }

    const std::string& GetMimeType() const
    {
        return mimeType_;
    }

    const std::string& GetReason() const
    {
        return reason_;
    }

    int32_t GetStatusCode() const
    {
        return statusCode_;
    }

    bool GetResponseStatus() const
    {
        return isReady_;
    }

    int32_t GetFileHandle() const
    {
        return fd_;
    }

    const std::string& GetResourceUrl() const
    {
        return resourceUrl_;
    }

    WebResponseDataType GetDataType() const
    {
        return dataType_;
    }

    void SetHeadersVal(std::string& key, std::string& val)
    {
        headers_[key] = val;
    }

    void SetData(std::string& data)
    {
        data_ = data;
        dataType_ = WebResponseDataType::STRING_TYPE;
        fd_ = 0;
    }

    void SetFileHandle(int32_t fd)
    {
        fd_ = fd;
        data_.clear();
        dataType_ = WebResponseDataType::FILE_TYPE;
    }

    void SetResourceUrl(const std::string& url)
    {
        resourceUrl_ = url;
        dataType_ = WebResponseDataType::RESOURCE_URL_TYPE;
    }

    void SetEncoding(std::string& encoding)
    {
        encoding_ = encoding;
    }

    void SetMimeType(std::string& mimeType)
    {
        mimeType_ = mimeType;
    }

    void SetReason(std::string& reason)
    {
        reason_ = reason;
    }

    void SetStatusCode(int32_t statusCode)
    {
        statusCode_ = statusCode;
    }

    void SetResponseStatus(bool isReady)
    {
        isReady_ = isReady;
        if (handle_ == nullptr) {
            return;
        }
        if (isReady_ == true) {
            if (dataType_ == WebResponseDataType::FILE_TYPE) {
                handle_->HandleFileFd(fd_);
            } else if (dataType_ == WebResponseDataType::RESOURCE_URL_TYPE) {
                handle_->HandleResourceUrl(resourceUrl_);
            } else {
                handle_->HandleData(data_);
            }
            handle_->HandleHeadersVal(headers_);
            handle_->HandleEncoding(encoding_);
            handle_->HandleMimeType(mimeType_);
            handle_->HandleStatusCodeAndReason(statusCode_, reason_);
        }
        handle_->HandleResponseStatus(isReady_);
    }

    void SetAsyncHandle(std::shared_ptr<WebResponseAsyncHandle> handle)
    {
        handle_ = handle;
    }

    bool IsFileHandle()
    {
        if (dataType_ == WebResponseDataType::FILE_TYPE) {
            return true;
        }
        return false;
    }

private:
    std::map<std::string, std::string> headers_;
    std::string data_;
    int32_t fd_;
    std::string resourceUrl_;
    WebResponseDataType dataType_ = WebResponseDataType::STRING_TYPE;
    std::string encoding_;
    std::string mimeType_;
    std::string reason_;
    int32_t statusCode_;
    bool isReady_ = true;
    std::shared_ptr<WebResponseAsyncHandle> handle_;
};

class ACE_EXPORT WebRequest : public AceType {
    DECLARE_ACE_TYPE(WebRequest, AceType)

public:
    WebRequest(const std::map<std::string, std::string>& headers, const std::string& method, const std::string& url,
        bool hasGesture, bool isMainFrame, bool isRedirect)
        : headers_(headers), method_(method), url_(url), hasGesture_(hasGesture), isMainFrame_(isMainFrame),
          isRedirect_(isRedirect)
    {}
    ~WebRequest() = default;

    const std::map<std::string, std::string>& GetHeaders() const
    {
        return headers_;
    }

    const std::string& GetMethod() const
    {
        return method_;
    }

    const std::string& GetUrl() const
    {
        return url_;
    }

    bool HasGesture() const
    {
        return hasGesture_;
    }

    bool IsMainFrame() const
    {
        return isMainFrame_;
    }

    bool IsRedirect() const
    {
        return isRedirect_;
    }

private:
    std::map<std::string, std::string> headers_;
    std::string method_;
    std::string url_;
    bool hasGesture_;
    bool isMainFrame_;
    bool isRedirect_;
};

class ACE_EXPORT Result : public AceType {
    DECLARE_ACE_TYPE(Result, AceType)

public:
    Result() = default;
    ~Result() = default;

    virtual void Confirm() = 0;
    virtual void Confirm(const std::string& message) = 0;
    virtual void Cancel() = 0;
};

class ACE_EXPORT FileSelectorResult : public AceType {
    DECLARE_ACE_TYPE(FileSelectorResult, AceType)

public:
    FileSelectorResult() = default;
    ~FileSelectorResult() = default;

    virtual void HandleFileList(std::vector<std::string>& fileList) = 0;
};

class ACE_EXPORT WebDialogEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebDialogEvent, BaseEventInfo);

public:
    WebDialogEvent(const std::string& url, const std::string& message, const std::string& value,
        const DialogEventType& type, const RefPtr<Result>& result)
        : BaseEventInfo("WebDialogEvent"), url_(url), message_(message), value_(value), type_(type), result_(result)
    {}
    ~WebDialogEvent() = default;

    const std::string& GetUrl() const
    {
        return url_;
    }

    const std::string& GetMessage() const
    {
        return message_;
    }

    const std::string& GetValue() const
    {
        return value_;
    }

    const RefPtr<Result>& GetResult() const
    {
        return result_;
    }

    const DialogEventType& GetType() const
    {
        return type_;
    }

private:
    std::string url_;
    std::string message_;
    std::string value_;
    DialogEventType type_;
    RefPtr<Result> result_;
};

class ACE_EXPORT AuthResult : public AceType {
    DECLARE_ACE_TYPE(AuthResult, AceType)

public:
    AuthResult() = default;
    ~AuthResult() = default;

    virtual bool Confirm(std::string& userName, std::string& pwd) = 0;
    virtual bool IsHttpAuthInfoSaved() = 0;
    virtual void Cancel() = 0;
};

class ACE_EXPORT WebHttpAuthEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebHttpAuthEvent, BaseEventInfo);

public:
    WebHttpAuthEvent(const RefPtr<AuthResult>& result, const std::string& host, const std::string& realm)
        : BaseEventInfo("WebHttpAuthEvent"), result_(result), host_(host), realm_(realm)
    {}
    ~WebHttpAuthEvent() = default;

    const RefPtr<AuthResult>& GetResult() const
    {
        return result_;
    }

    const std::string& GetHost() const
    {
        return host_;
    }

    const std::string& GetRealm() const
    {
        return realm_;
    }

private:
    RefPtr<AuthResult> result_;
    std::string host_;
    std::string realm_;
};

class ACE_EXPORT SslErrorResult : public AceType {
    DECLARE_ACE_TYPE(SslErrorResult, AceType)

public:
    SslErrorResult() = default;
    ~SslErrorResult() = default;
    virtual void HandleConfirm() = 0;
    virtual void HandleCancel() = 0;
};

class ACE_EXPORT WebSslErrorEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebSslErrorEvent, BaseEventInfo);

public:
    WebSslErrorEvent(const RefPtr<SslErrorResult>& result, int32_t error)
        : BaseEventInfo("WebSslErrorEvent"), result_(result), error_(error) {}
    ~WebSslErrorEvent() = default;

    const RefPtr<SslErrorResult>& GetResult() const
    {
        return result_;
    }

    int32_t GetError() const
    {
        return error_;
    }

private:
    RefPtr<SslErrorResult> result_;
    int32_t error_;
};

class ACE_EXPORT SslSelectCertResult : public AceType {
    DECLARE_ACE_TYPE(SslSelectCertResult, AceType)
public:
    SslSelectCertResult() = default;
    ~SslSelectCertResult() = default;

    virtual void HandleConfirm(const std::string& privateKeyFile, const std::string& certChainFile) = 0;
    virtual void HandleCancel() = 0;
    virtual void HandleIgnore() = 0;
};

class ACE_EXPORT WebSslSelectCertEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebSslSelectCertEvent, BaseEventInfo);

public:
    WebSslSelectCertEvent(const RefPtr<SslSelectCertResult>& result,
        const std::string& host, int port,
        const std::vector<std::string>& keyTypes,
        const std::vector<std::string>& issuers)
        : BaseEventInfo("WebSslSelectCertEvent"),
        result_(result), host_(host), port_(port), keyTypes_(keyTypes), issuers_(issuers) {}

    ~WebSslSelectCertEvent() = default;

    const RefPtr<SslSelectCertResult>& GetResult() const
    {
        return result_;
    }

    const std::string& GetHost() const
    {
        return host_;
    }

    int32_t GetPort() const
    {
        return port_;
    }

    const std::vector<std::string>& GetKeyTypes() const
    {
        return keyTypes_;
    }

    const std::vector<std::string>& GetIssuers_() const
    {
        return issuers_;
    }

private:
    RefPtr<SslSelectCertResult> result_;
    std::string host_;
    int32_t port_ = -1;
    std::vector<std::string> keyTypes_;
    std::vector<std::string> issuers_;
};

class ACE_EXPORT WebGeolocation : public AceType {
    DECLARE_ACE_TYPE(WebGeolocation, AceType)

public:
    WebGeolocation() = default;
    ~WebGeolocation() = default;

    virtual void Invoke(const std::string& origin, const bool& allow, const bool& retain) = 0;
};

class ACE_EXPORT WebPermissionRequest : public AceType {
    DECLARE_ACE_TYPE(WebPermissionRequest, AceType)

public:
    WebPermissionRequest() = default;
    ~WebPermissionRequest() = default;

    virtual void Deny() const = 0;

    virtual std::string GetOrigin() const = 0;

    virtual std::vector<std::string> GetResources() const = 0;

    virtual void Grant(std::vector<std::string>& resources) const = 0;
};

class ACE_EXPORT WebScreenCaptureRequest : public AceType {
    DECLARE_ACE_TYPE(WebScreenCaptureRequest, AceType)

public:
    WebScreenCaptureRequest() = default;
    ~WebScreenCaptureRequest() = default;

    virtual void Deny() const = 0;

    virtual std::string GetOrigin() const = 0;

    virtual void SetCaptureMode(int32_t mode) = 0;

    virtual void SetSourceId(int32_t sourceId) = 0;

    virtual void Grant() const = 0;
};

class ACE_EXPORT WebWindowNewHandler : public AceType {
    DECLARE_ACE_TYPE(WebWindowNewHandler, AceType)

public:
    WebWindowNewHandler() = default;
    ~WebWindowNewHandler() = default;

    virtual void SetWebController(int32_t id) = 0;

    virtual bool IsFrist() const = 0;

    virtual int32_t GetId() const = 0;

    virtual int32_t GetParentNWebId() const = 0;
};

class ACE_EXPORT LoadWebPageStartEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebPageStartEvent, BaseEventInfo);

public:
    explicit LoadWebPageStartEvent(const std::string& url) : BaseEventInfo("LoadWebPageStartEvent"), loadedUrl_(url) {}
    ~LoadWebPageStartEvent() = default;

    const std::string& GetLoadedUrl() const
    {
        return loadedUrl_;
    }

private:
    std::string loadedUrl_;
};

class ACE_EXPORT LoadWebPageFinishEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebPageFinishEvent, BaseEventInfo);

public:
    explicit LoadWebPageFinishEvent(const std::string& url) : BaseEventInfo("LoadWebPageFinishEvent"), loadedUrl_(url)
    {}
    ~LoadWebPageFinishEvent() = default;

    const std::string& GetLoadedUrl() const
    {
        return loadedUrl_;
    }

private:
    std::string loadedUrl_;
};

class ACE_EXPORT ContextMenuHideEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ContextMenuHideEvent, BaseEventInfo);

public:
    explicit ContextMenuHideEvent(const std::string& info) : BaseEventInfo("ContextMenuHideEvent"), info_(info)
    {}
    ~ContextMenuHideEvent() = default;

    const std::string& GetInfo() const
    {
        return info_;
    }

private:
    std::string info_;
};

class ACE_EXPORT LoadWebProgressChangeEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebProgressChangeEvent, BaseEventInfo);

public:
    explicit LoadWebProgressChangeEvent(const int& newProgress)
        : BaseEventInfo("LoadWebProgressChangeEvent"), newProgress_(newProgress)
    {}
    ~LoadWebProgressChangeEvent() = default;

    const int& GetNewProgress() const
    {
        return newProgress_;
    }

private:
    int newProgress_;
};

class ACE_EXPORT LoadWebTitleReceiveEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebTitleReceiveEvent, BaseEventInfo);

public:
    explicit LoadWebTitleReceiveEvent(const std::string& title)
        : BaseEventInfo("LoadWebTitleReceiveEvent"), title_(title)
    {}
    ~LoadWebTitleReceiveEvent() = default;

    const std::string& GetTitle() const
    {
        return title_;
    }

private:
    std::string title_;
};

class ACE_EXPORT FullScreenExitHandler : public AceType {
    DECLARE_ACE_TYPE(FullScreenExitHandler, AceType)

public:
    FullScreenExitHandler() = default;
    ~FullScreenExitHandler() = default;

    virtual void ExitFullScreen() = 0;
};

class ACE_EXPORT FullScreenEnterEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(FullScreenEnterEvent, BaseEventInfo);

public:
    FullScreenEnterEvent(const RefPtr<FullScreenExitHandler>& handler)
        : BaseEventInfo("FullScreenEnterEvent"), handler_(handler) {}
    ~FullScreenEnterEvent() = default;

    const RefPtr<FullScreenExitHandler>& GetHandler() const
    {
        return handler_;
    }

private:
    RefPtr<FullScreenExitHandler> handler_;
};

class ACE_EXPORT FullScreenExitEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(FullScreenExitEvent, BaseEventInfo);

public:
    explicit FullScreenExitEvent(bool fullscreen = false)
        : BaseEventInfo("FullScreenExitEvent"), fullscreen_(fullscreen) {}
    ~FullScreenExitEvent() = default;

    bool IsFullScreen() const
    {
        return fullscreen_;
    }

private:
    bool fullscreen_ = false;
};

class ACE_EXPORT UrlLoadInterceptEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(UrlLoadInterceptEvent, BaseEventInfo);

public:
    explicit UrlLoadInterceptEvent(const std::string& data) : BaseEventInfo("UrlLoadInterceptEvent"), data_(data) {}
    ~UrlLoadInterceptEvent() = default;

    const std::string& GetData() const
    {
        return data_;
    }

private:
    std::string data_;
};

class ACE_EXPORT LoadInterceptEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadInterceptEvent, BaseEventInfo);

public:
    explicit LoadInterceptEvent(const RefPtr<WebRequest>& request) :
        BaseEventInfo("LoadInterceptEvent"), request_(request) {}
    ~LoadInterceptEvent() = default;

    const RefPtr<WebRequest>& GetRequest() const
    {
        return request_;
    }

private:
    RefPtr<WebRequest> request_;
};

class ACE_EXPORT LoadWebGeolocationHideEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebGeolocationHideEvent, BaseEventInfo);

public:
    explicit LoadWebGeolocationHideEvent(const std::string& origin)
        : BaseEventInfo("LoadWebGeolocationHideEvent"), origin_(origin)
    {}
    ~LoadWebGeolocationHideEvent() = default;

    const std::string& GetOrigin() const
    {
        return origin_;
    }

private:
    std::string origin_;
};

class ACE_EXPORT LoadWebGeolocationShowEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebGeolocationShowEvent, BaseEventInfo);

public:
    LoadWebGeolocationShowEvent(const std::string& origin, const RefPtr<WebGeolocation>& webGeolocation)
        : BaseEventInfo("LoadWebGeolocationShowEvent"), origin_(origin), webGeolocation_(webGeolocation)
    {}
    ~LoadWebGeolocationShowEvent() = default;

    const std::string& GetOrigin() const
    {
        return origin_;
    }

    const RefPtr<WebGeolocation>& GetWebGeolocation() const
    {
        return webGeolocation_;
    }

private:
    std::string origin_;
    RefPtr<WebGeolocation> webGeolocation_;
};

class ACE_EXPORT WebPermissionRequestEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebPermissionRequestEvent, BaseEventInfo);

public:
    WebPermissionRequestEvent(const RefPtr<WebPermissionRequest>& webPermissionRequest)
        : BaseEventInfo("WebPermissionRequestEvent"), webPermissionRequest_(webPermissionRequest)
    {}
    ~WebPermissionRequestEvent() = default;

    const RefPtr<WebPermissionRequest>& GetWebPermissionRequest() const
    {
        return webPermissionRequest_;
    }

private:
    RefPtr<WebPermissionRequest> webPermissionRequest_;
};

class ACE_EXPORT WebScreenCaptureRequestEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebScreenCaptureRequestEvent, BaseEventInfo);

public:
    WebScreenCaptureRequestEvent(const RefPtr<WebScreenCaptureRequest>& request)
        : BaseEventInfo("WebScreenCaptureRequestEvent"), request_(request)
    {}
    ~WebScreenCaptureRequestEvent() = default;

    const RefPtr<WebScreenCaptureRequest>& GetWebScreenCaptureRequest() const
    {
        return request_;
    }

private:
    RefPtr<WebScreenCaptureRequest> request_;
};

class ACE_EXPORT DownloadStartEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(DownloadStartEvent, BaseEventInfo);

public:
    DownloadStartEvent(const std::string& url, const std::string& userAgent, const std::string& contentDisposition,
        const std::string& mimetype, long contentLength)
        : BaseEventInfo("DownloadStartEvent"), url_(url), userAgent_(userAgent),
          contentDisposition_(contentDisposition), mimetype_(mimetype), contentLength_(contentLength)
    {}
    ~DownloadStartEvent() = default;

    const std::string& GetUrl() const
    {
        return url_;
    }

    const std::string& GetUserAgent() const
    {
        return userAgent_;
    }

    const std::string& GetContentDisposition() const
    {
        return contentDisposition_;
    }

    const std::string& GetMimetype() const
    {
        return mimetype_;
    }

    long GetContentLength() const
    {
        return contentLength_;
    }

private:
    std::string url_;
    std::string userAgent_;
    std::string contentDisposition_;
    std::string mimetype_;
    long contentLength_;
};

class ACE_EXPORT ReceivedErrorEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ReceivedErrorEvent, BaseEventInfo);

public:
    ReceivedErrorEvent(const RefPtr<WebRequest>& request, const RefPtr<WebError>& error)
        : BaseEventInfo("ReceivedErrorEvent"), request_(request), error_(error)
    {
        LOGI("ReceivedErrorEvent constructor");
    }
    ~ReceivedErrorEvent() = default;

    const RefPtr<WebRequest>& GetRequest() const
    {
        return request_;
    }

    const RefPtr<WebError>& GetError() const
    {
        return error_;
    }

private:
    RefPtr<WebRequest> request_;
    RefPtr<WebError> error_;
};

class ACE_EXPORT ReceivedHttpErrorEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ReceivedHttpErrorEvent, BaseEventInfo);

public:
    ReceivedHttpErrorEvent(const RefPtr<WebRequest>& request, const RefPtr<WebResponse>& response)
        : BaseEventInfo("ReceivedHttpErrorEvent"), request_(request), response_(response)
    {
        LOGI("ReceivedHttpErrorEvent constructor");
    }
    ~ReceivedHttpErrorEvent() = default;

    const RefPtr<WebRequest>& GetRequest() const
    {
        return request_;
    }

    const RefPtr<WebResponse>& GetResponse() const
    {
        return response_;
    }

private:
    RefPtr<WebRequest> request_;
    RefPtr<WebResponse> response_;
};

class ACE_EXPORT OnInterceptRequestEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(OnInterceptRequestEvent, BaseEventInfo);

public:
    OnInterceptRequestEvent(const RefPtr<WebRequest>& request)
        : BaseEventInfo("OnInterceptRequestEvent"), request_(request)
    {
        LOGI("OnInterceptRequestEvent constructor");
    }
    ~OnInterceptRequestEvent() = default;

    const RefPtr<WebRequest>& GetRequest() const
    {
        return request_;
    }

private:
    RefPtr<WebRequest> request_;
};

class ACE_EXPORT LoadWebRequestFocusEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebRequestFocusEvent, BaseEventInfo);

public:
    explicit LoadWebRequestFocusEvent(const std::string& url)
        : BaseEventInfo("LoadWebRequestFocusEvent"), focusUrl_(url)
    {}
    ~LoadWebRequestFocusEvent() = default;

    const std::string& GetRequestFocus() const
    {
        return focusUrl_;
    }

private:
    std::string focusUrl_;
};

class ACE_EXPORT LoadWebOnFocusEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebOnFocusEvent, BaseEventInfo);

public:
    explicit LoadWebOnFocusEvent(const std::string& url) : BaseEventInfo("LoadWebOnFocusEvent"), focusUrl_(url) {}
    ~LoadWebOnFocusEvent() = default;

    const std::string& GetOnFocus() const
    {
        return focusUrl_;
    }

private:
    std::string focusUrl_;
};

class ACE_EXPORT LoadWebConsoleLogEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebConsoleLogEvent, BaseEventInfo);

public:
    LoadWebConsoleLogEvent(RefPtr<WebConsoleLog> message) : BaseEventInfo("LoadWebConsoleLogEvent"), message_(message)
    {}
    ~LoadWebConsoleLogEvent() = default;

    const RefPtr<WebConsoleLog> GetMessage() const
    {
        return message_;
    }

private:
    RefPtr<WebConsoleLog> message_;
};

class ACE_EXPORT RenderExitedEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(RenderExitedEvent, BaseEventInfo);

public:
    RenderExitedEvent(int32_t exitedReason) : BaseEventInfo("RenderExitedEvent"), exitedReason_(exitedReason) {}
    ~RenderExitedEvent() = default;

    int32_t GetExitedReason() const
    {
        return exitedReason_;
    }

private:
    int32_t exitedReason_;
};

class ACE_EXPORT RefreshAccessedHistoryEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(RefreshAccessedHistoryEvent, BaseEventInfo);

public:
    RefreshAccessedHistoryEvent(const std::string& url, bool isRefreshed)
        : BaseEventInfo("RefreshAccessedHistoryEvent"), url_(url), isRefreshed_(isRefreshed)
    {}

    ~RefreshAccessedHistoryEvent() = default;

    const std::string& GetVisitedUrl() const
    {
        return url_;
    }

    bool IsRefreshed() const
    {
        return isRefreshed_;
    }

private:
    std::string url_;
    bool isRefreshed_;
};

class ACE_EXPORT FileSelectorEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(FileSelectorEvent, BaseEventInfo);

public:
    FileSelectorEvent(const RefPtr<WebFileSelectorParam>& param, const RefPtr<FileSelectorResult>& result)
        : BaseEventInfo("FileSelectorEvent"), param_(param), result_(result)
    {
        LOGI("FileSelectorEvent constructor");
    }
    ~FileSelectorEvent() = default;

    const RefPtr<WebFileSelectorParam>& GetParam() const
    {
        return param_;
    }

    const RefPtr<FileSelectorResult>& GetFileSelectorResult() const
    {
        return result_;
    }

private:
    RefPtr<WebFileSelectorParam> param_;
    RefPtr<FileSelectorResult> result_;
};

class ACE_EXPORT ResourceLoadEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ResourceLoadEvent, BaseEventInfo);

public:
    explicit ResourceLoadEvent(const std::string& url) : BaseEventInfo("ResourceLoadEvent"), loadUrl_(url) {}
    ~ResourceLoadEvent() = default;

    const std::string& GetOnResourceLoadUrl() const
    {
        return loadUrl_;
    }

private:
    std::string loadUrl_;
};

class ACE_EXPORT ScaleChangeEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ScaleChangeEvent, BaseEventInfo);

public:
    ScaleChangeEvent(float oldScale, float newScale)
        : BaseEventInfo("ScaleChangeEvent"), oldScale_(oldScale), newScale_(newScale)
    {}
    ~ScaleChangeEvent() = default;

    float GetOnScaleChangeOldScale() const
    {
        return oldScale_;
    }

    float GetOnScaleChangeNewScale() const
    {
        return newScale_;
    }

private:
    float oldScale_ = 0.0f;
    float newScale_ = 0.0f;
};

class ACE_EXPORT WebOnScrollEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebOnScrollEvent, BaseEventInfo);

public:
    WebOnScrollEvent(double xOffset, double yOffset)
        : BaseEventInfo("OnScrollEvent"), xOffset_(xOffset), yOffset_(yOffset)
    {}
    ~WebOnScrollEvent() = default;

    float GetX() const
    {
        return xOffset_;
    }

    float GetY() const
    {
        return yOffset_;
    }

private:
    double xOffset_ = 0.0f;
    double yOffset_ = 0.0f;
};

class WebContextMenuParam : public AceType {
    DECLARE_ACE_TYPE(WebContextMenuParam, AceType)

public:
    WebContextMenuParam() = default;
    ~WebContextMenuParam() = default;

    virtual int32_t GetXCoord() const = 0;
    virtual int32_t GetYCoord() const = 0;
    virtual std::string GetLinkUrl() const = 0;
    virtual std::string GetUnfilteredLinkUrl() const = 0;
    virtual std::string GetSourceUrl() const = 0;
    virtual bool HasImageContents() const = 0;
    virtual bool IsEditable() const = 0;
    virtual int GetEditStateFlags() const = 0;
    virtual int GetSourceType() const = 0;
    virtual int GetMediaType() const = 0;
    virtual int GetInputFieldType() const = 0;
    virtual std::string GetSelectionText() const = 0;
};

class ACE_EXPORT ContextMenuResult : public AceType {
    DECLARE_ACE_TYPE(ContextMenuResult, AceType)

public:
    ContextMenuResult() = default;
    ~ContextMenuResult() = default;

    virtual void Cancel() const = 0;
    virtual void CopyImage() const = 0;
    virtual void Copy() const = 0;
    virtual void Paste() const = 0;
    virtual void Cut() const = 0;
    virtual void SelectAll() const = 0;
};

class ACE_EXPORT ContextMenuEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(ContextMenuEvent, BaseEventInfo);

public:
    ContextMenuEvent(const RefPtr<WebContextMenuParam>& param, const RefPtr<ContextMenuResult>& result)
        : BaseEventInfo("ContextShowEvent"), param_(param), result_(result)
    {
        LOGI("ContextShowEvent constructor");
    }
    ~ContextMenuEvent() = default;

    const RefPtr<WebContextMenuParam>& GetParam() const
    {
        return param_;
    }

    const RefPtr<ContextMenuResult>& GetContextMenuResult() const
    {
        return result_;
    }

private:
    RefPtr<WebContextMenuParam> param_;
    RefPtr<ContextMenuResult> result_;
};

class ACE_EXPORT SearchResultReceiveEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(SearchResultReceiveEvent, BaseEventInfo);

public:
    SearchResultReceiveEvent(int activeMatchOrdinal, int numberOfMatches, bool isDoneCounting)
        : BaseEventInfo("SearchResultReceiveEvent"), activeMatchOrdinal_(activeMatchOrdinal),
          numberOfMatches_(numberOfMatches), isDoneCounting_(isDoneCounting)
    {}
    ~SearchResultReceiveEvent() = default;

    int GetActiveMatchOrdinal() const
    {
        return activeMatchOrdinal_;
    }

    int GetNumberOfMatches() const
    {
        return numberOfMatches_;
    }

    bool GetIsDoneCounting() const
    {
        return isDoneCounting_;
    }

private:
    int activeMatchOrdinal_;
    int numberOfMatches_;
    bool isDoneCounting_;
};

class ACE_EXPORT WebWindowNewEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebWindowNewEvent, BaseEventInfo);

public:
    WebWindowNewEvent(const std::string& targetUrl, bool isAlert, bool isUserTrigger,
        const RefPtr<WebWindowNewHandler>& handler)
        : BaseEventInfo("WebWindowNewEvent"), targetUrl_(targetUrl), isAlert_(isAlert),
          isUserTrigger_(isUserTrigger), handler_(handler) {}
    ~WebWindowNewEvent() = default;

    const std::string& GetTargetUrl() const
    {
        return targetUrl_;
    }

    bool IsAlert() const
    {
        return isAlert_;
    }

    bool IsUserTrigger() const
    {
        return isUserTrigger_;
    }

    const RefPtr<WebWindowNewHandler>& GetWebWindowNewHandler() const
    {
        return handler_;
    }
private:
    std::string targetUrl_;
    bool isAlert_;
    bool isUserTrigger_;
    RefPtr<WebWindowNewHandler> handler_;
};

class ACE_EXPORT WebWindowExitEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebWindowExitEvent, BaseEventInfo);

public:
    WebWindowExitEvent() : BaseEventInfo("WebWindowExitEvent") {}
    ~WebWindowExitEvent() = default;
};

class ACE_EXPORT PageVisibleEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(PageVisibleEvent, BaseEventInfo);

public:
    PageVisibleEvent(const std::string& url)
        : BaseEventInfo("PageVisibleEvent"), url_(url)
    {}

    ~PageVisibleEvent() = default;

    const std::string& GetUrl() const
    {
        return url_;
    }

private:
    std::string url_;
};

class ACE_EXPORT DataResubmitted : public AceType {
    DECLARE_ACE_TYPE(DataResubmitted, AceType)

public:
    DataResubmitted() = default;
    ~DataResubmitted() = default;

    virtual void Resend() = 0;
    virtual void Cancel() = 0;
};

class ACE_EXPORT DataResubmittedEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(DataResubmittedEvent, BaseEventInfo);

public:
    DataResubmittedEvent(const RefPtr<DataResubmitted>& handler)
        : BaseEventInfo("DataResubmittedEvent"), handler_(handler) {}
    ~DataResubmittedEvent() = default;

    const RefPtr<DataResubmitted>& GetHandler() const
    {
        return handler_;
    }

private:
    RefPtr<DataResubmitted> handler_;
};

class ACE_EXPORT WebFaviconReceived : public AceType {
    DECLARE_ACE_TYPE(WebFaviconReceived, AceType)

public:
    WebFaviconReceived() = default;
    ~WebFaviconReceived() = default;

    virtual const void* GetData() = 0;
    virtual size_t GetWidth() = 0;
    virtual size_t GetHeight() = 0;
    virtual int GetColorType() = 0;
    virtual int GetAlphaType() = 0;
};

class ACE_EXPORT FaviconReceivedEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(FaviconReceivedEvent, BaseEventInfo);

public:
    FaviconReceivedEvent(const RefPtr<WebFaviconReceived>& handler)
        : BaseEventInfo("FaviconReceivedEvent"), handler_(handler) {}
    ~FaviconReceivedEvent() = default;

    const RefPtr<WebFaviconReceived>& GetHandler() const
    {
        return handler_;
    }

private:
    RefPtr<WebFaviconReceived> handler_;
};

class ACE_EXPORT TouchIconUrlEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TouchIconUrlEvent, BaseEventInfo);

public:
    TouchIconUrlEvent(const std::string& iconUrl, bool precomposed)
        : BaseEventInfo("TouchIconUrlEvent"), url_(iconUrl), precomposed_(precomposed)
    {}

    ~TouchIconUrlEvent() = default;

    const std::string& GetUrl() const
    {
        return url_;
    }

    bool GetPreComposed() const
    {
        return precomposed_;
    }

private:
    std::string url_;
    bool precomposed_;
};

class ACE_EXPORT AudioStateChangedEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(AudioStateChangedEvent, BaseEventInfo);

public:
    AudioStateChangedEvent(bool playing) : BaseEventInfo("AudioStateChangedEvent"), playing_(playing) {}
    ~AudioStateChangedEvent() = default;

    bool IsPlaying() const
    {
        return playing_;
    }

private:
    bool playing_;
};

class ACE_EXPORT FirstContentfulPaintEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(FirstContentfulPaintEvent, BaseEventInfo);

public:
    FirstContentfulPaintEvent(int64_t navigationStartTick, int64_t firstContentfulPaintMs)
        : BaseEventInfo("FirstContentfulPaintEvent"), navigationStartTick_(navigationStartTick),
          firstContentfulPaintMs_(firstContentfulPaintMs)
    {}

    ~FirstContentfulPaintEvent() = default;

    int64_t GetNavigationStartTick() const
    {
        return navigationStartTick_;
    }

    int64_t GetFirstContentfulPaintMs() const
    {
        return firstContentfulPaintMs_;
    }

private:
    int64_t navigationStartTick_;
    int64_t firstContentfulPaintMs_;
};

class ACE_EXPORT WebOnOverScrollEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(WebOnOverScrollEvent, BaseEventInfo);

public:
    WebOnOverScrollEvent(double xOffset, double yOffset)
        : BaseEventInfo("OnOverScrollEvent"), xOffset_(xOffset), yOffset_(yOffset)
    {}
    ~WebOnOverScrollEvent() = default;

    float GetX() const
    {
        return xOffset_;
    }

    float GetY() const
    {
        return yOffset_;
    }

private:
    float xOffset_ = 0.0f;
    float yOffset_ = 0.0f;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_EVENT_H
