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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H

#include <string>

#include "base/geometry/size.h"
#include "base/utils/utils.h"
#include "core/components/declaration/common/declaration.h"
#include "core/components/declaration/web/web_client.h"
#include "core/components/declaration/web/web_declaration.h"
#include "core/components/web/resource/web_javascript_value.h"
#include "core/components/web/web_event.h"
#include "core/components_v2/common/common_def.h"
#include "core/event/key_event.h"
#include "core/focus/focus_node.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {

class WebDelegate;
using OnMouseCallback = std::function<void(MouseInfo& info)>;
using OnKeyEventCallback = std::function<void(KeyEventInfo& keyEventInfo)>;

enum MixedModeContent {
    MIXED_CONTENT_ALWAYS_ALLOW = 0,
    MIXED_CONTENT_NEVER_ALLOW = 1,
    MIXED_CONTENT_COMPATIBILITY_MODE = 2
};

enum WebCacheMode {
    DEFAULT = 0,
    USE_CACHE_ELSE_NETWORK,
    USE_NO_CACHE,
    USE_CACHE_ONLY
};

constexpr int32_t DEFAULT_TEXT_ZOOM_RATIO = 100;

class HitTestResult : public virtual AceType {
    DECLARE_ACE_TYPE(HitTestResult, AceType);

public:
    HitTestResult(const std::string& extraData, int hitType) : extraData_(extraData), hitType_(hitType) {}
    HitTestResult() = default;
    ~HitTestResult() = default;

    const std::string& GetExtraData() const
    {
        return extraData_;
    }

    void SetExtraData(const std::string& extraData)
    {
        extraData_ = extraData;
    }

    int GetHitType() const
    {
        return hitType_;
    }

    void SetHitTpye(int hitType)
    {
        hitType_ = hitType;
    }

private:
    std::string extraData_;
    int hitType_ = static_cast<int>(WebHitTestType::UNKNOWN);
};

class WebMessagePort : public virtual AceType {
    DECLARE_ACE_TYPE(WebMessagePort, AceType);

public:
    WebMessagePort() = default;
    virtual ~WebMessagePort() = default;
    virtual void SetPortHandle(std::string& handle) = 0;
    virtual std::string GetPortHandle() = 0;
    virtual void Close() = 0;
    virtual void PostMessage(std::string& data) = 0;
    virtual void SetWebMessageCallback(std::function<void(const std::string&)>&& callback) = 0;
};

class WebCookie : public virtual AceType {
    DECLARE_ACE_TYPE(WebCookie, AceType);

public:
    using SetCookieImpl = std::function<bool(const std::string&, const std::string&)>;
    using GetCookieImpl = std::function<std::string(const std::string&)>;
    using DeleteEntirelyCookieImpl = std::function<void()>;
    using SaveCookieSyncImpl = std::function<bool()>;
    bool SetCookie(const std::string& url, const std::string& value)
    {
        if (setCookieImpl_) {
            return setCookieImpl_(url, value);
        }
        return false;
    }

    std::string GetCookie(const std::string& url)
    {
        if (getCookieImpl_) {
            return getCookieImpl_(url);
        }
        return "";
    }

    void DeleteEntirelyCookie()
    {
        if (deleteEntirelyCookieImpl_) {
            deleteEntirelyCookieImpl_();
        }
    }

    bool SaveCookieSync()
    {
        if (saveCookieSyncImpl_) {
            return saveCookieSyncImpl_();
        }
        return false;
    }

    void SetSetCookieImpl(SetCookieImpl&& setCookieImpl)
    {
        setCookieImpl_ = setCookieImpl;
    }

    void SetGetCookieImpl(GetCookieImpl&& getCookieImpl)
    {
        getCookieImpl_ = getCookieImpl;
    }

    void SetDeleteEntirelyCookieImpl(DeleteEntirelyCookieImpl&& deleteEntirelyCookieImpl)
    {
        deleteEntirelyCookieImpl_ = deleteEntirelyCookieImpl;
    }

    void SetSaveCookieSyncImpl(SaveCookieSyncImpl&& saveCookieSyncImpl)
    {
        saveCookieSyncImpl_ = saveCookieSyncImpl;
    }

private:
    SetCookieImpl setCookieImpl_;
    GetCookieImpl getCookieImpl_;
    DeleteEntirelyCookieImpl deleteEntirelyCookieImpl_;
    SaveCookieSyncImpl saveCookieSyncImpl_;
};

class WebController : public virtual AceType {
    DECLARE_ACE_TYPE(WebController, AceType);

public:
    using LoadUrlImpl = std::function<void(std::string, const std::map<std::string, std::string>&)>;
    using AccessBackwardImpl = std::function<bool()>;
    using AccessForwardImpl = std::function<bool()>;
    using AccessStepImpl = std::function<bool(int32_t)>;
    using BackOrForwardImpl = std::function<void(int32_t)>;
    using BackwardImpl = std::function<void()>;
    using ForwardImpl = std::function<void()>;
    using ClearHistoryImpl = std::function<void()>;
    using ClearSslCacheImpl = std::function<void()>;

    void LoadUrl(std::string url, std::map<std::string, std::string>& httpHeaders) const
    {
        if (loadUrlImpl_) {
            loadUrlImpl_(url, httpHeaders);
        }
    }

    bool AccessStep(int32_t step)
    {
        if (accessStepImpl_) {
            return accessStepImpl_(step);
        }
        return false;
    }

    void BackOrForward(int32_t step)
    {
        if (backOrForwardImpl_) {
            return backOrForwardImpl_(step);
        }
    }

    bool AccessBackward()
    {
        if (accessBackwardImpl_) {
            return accessBackwardImpl_();
        }
        return false;
    }

    bool AccessForward()
    {
        if (accessForwardImpl_) {
            return accessForwardImpl_();
        }
        return false;
    }

    void Backward()
    {
        LOGI("Start backward.");
        if (backwardImpl_) {
            backwardImpl_();
        }
    }

    void Forward()
    {
        LOGI("Start forward.");
        if (forwardimpl_) {
            forwardimpl_();
        }
    }

    void ClearHistory()
    {
        LOGI("Start clear navigation history");
        if (clearHistoryImpl_) {
            clearHistoryImpl_();
        }
    }

    void ClearSslCache()
    {
        LOGI("Start clear ssl cache");
        if (clearSslCacheImpl_) {
            clearSslCacheImpl_();
        }
    }

    void SetLoadUrlImpl(LoadUrlImpl && loadUrlImpl)
    {
        loadUrlImpl_ = std::move(loadUrlImpl);
    }

    void SetAccessBackwardImpl(AccessBackwardImpl && accessBackwardImpl)
    {
        accessBackwardImpl_ = std::move(accessBackwardImpl);
    }

    void SetAccessForwardImpl(AccessForwardImpl && accessForwardImpl)
    {
        accessForwardImpl_ = std::move(accessForwardImpl);
    }

    void SetAccessStepImpl(AccessStepImpl && accessStepImpl)
    {
        accessStepImpl_ = std::move(accessStepImpl);
    }

    void SetBackOrForwardImpl(BackOrForwardImpl && backOrForwardImpl)
    {
        backOrForwardImpl_ = std::move(backOrForwardImpl);
    }

    void SetBackwardImpl(BackwardImpl && backwardImpl)
    {
        backwardImpl_ = std::move(backwardImpl);
    }

    void SetForwardImpl(ForwardImpl && forwardImpl)
    {
        forwardimpl_ = std::move(forwardImpl);
    }

    void SetClearHistoryImpl(ClearHistoryImpl && clearHistoryImpl)
    {
        clearHistoryImpl_ = std::move(clearHistoryImpl);
    }

    void SetClearSslCacheImpl(ClearSslCacheImpl && clearSslCaheImpl)
    {
        clearSslCacheImpl_ = std::move(clearSslCaheImpl);
    }

    using ExecuteTypeScriptImpl = std::function<void(std::string, std::function<void(std::string)>&&)>;
    void ExecuteTypeScript(std::string jscode, std::function<void(std::string)>&& callback) const
    {
        if (executeTypeScriptImpl_) {
            executeTypeScriptImpl_(jscode, std::move(callback));
        }
    }
    void SetExecuteTypeScriptImpl(ExecuteTypeScriptImpl && executeTypeScriptImpl)
    {
        executeTypeScriptImpl_ = std::move(executeTypeScriptImpl);
    }

    using LoadDataWithBaseUrlImpl = std::function<void(
        std::string, std::string, std::string, std::string, std::string)>;
    void LoadDataWithBaseUrl(std::string baseUrl, std::string data, std::string mimeType, std::string encoding,
        std::string historyUrl) const
    {
        if (loadDataWithBaseUrlImpl_) {
            loadDataWithBaseUrlImpl_(baseUrl, data, mimeType, encoding, historyUrl);
        }
    }

    void SetLoadDataWithBaseUrlImpl(LoadDataWithBaseUrlImpl && loadDataWithBaseUrlImpl)
    {
        loadDataWithBaseUrlImpl_ = std::move(loadDataWithBaseUrlImpl);
    }

    using InitJavascriptInterface = std::function<void()>;
    void LoadInitJavascriptInterface() const
    {
        if (initJavascriptInterface_) {
            initJavascriptInterface_();
        }
    }
    void SetInitJavascriptInterface(InitJavascriptInterface&& initJavascriptInterface)
    {
        initJavascriptInterface_ = std::move(initJavascriptInterface);
    }

    using OnInactiveImpl = std::function<void()>;
    void OnInactive() const
    {
        if (onInactiveImpl_) {
            onInactiveImpl_();
        }
    }

    void SetOnInactiveImpl(OnInactiveImpl && onInactiveImpl)
    {
        onInactiveImpl_ = std::move(onInactiveImpl);
    }

    using OnActiveImpl = std::function<void()>;
    void OnActive() const
    {
        if (onActiveImpl_) {
            onActiveImpl_();
        }
    }

    void SetOnActiveImpl(OnActiveImpl && onActiveImpl)
    {
        onActiveImpl_ = std::move(onActiveImpl);
    }

    using ZoomImpl = std::function<void(float)>;
    void Zoom(float factor) const
    {
        if (zoomImpl_) {
            zoomImpl_(factor);
        }
    }

    void SetZoomImpl(ZoomImpl&& zoomImpl)
    {
        zoomImpl_ = std::move(zoomImpl);
    }

    using ZoomInImpl = std::function<bool()>;
    bool ZoomIn() const
    {
        if (zoomInImpl_) {
            return zoomInImpl_();
        }
        return false;
    }

    void SetZoomInImpl(ZoomInImpl&& zoomInImpl)
    {
        zoomInImpl_ = std::move(zoomInImpl);
    }

    using ZoomOutImpl = std::function<bool()>;
    bool ZoomOut() const
    {
        if (zoomOutImpl_) {
            return zoomOutImpl_();
        }
        return false;
    }

    void SetZoomOutImpl(ZoomOutImpl&& zoomOutImpl)
    {
        zoomOutImpl_ = std::move(zoomOutImpl);
    }

    using RefreshImpl = std::function<void()>;
    void Refresh() const
    {
        if (refreshImpl_) {
            refreshImpl_();
        }
    }
    void SetRefreshImpl(RefreshImpl && refreshImpl)
    {
        refreshImpl_ = std::move(refreshImpl);
    }

    using StopLoadingImpl = std::function<void()>;
    void StopLoading() const
    {
        if (stopLoadingImpl_) {
            stopLoadingImpl_();
        }
    }
    void SetStopLoadingImpl(StopLoadingImpl && stopLoadingImpl)
    {
        stopLoadingImpl_ = std::move(stopLoadingImpl);
    }

    using GetHitTestResultImpl = std::function<int()>;
    int GetHitTestResult()
    {
        if (getHitTestResultImpl_) {
            return getHitTestResultImpl_();
        }
        return 0;
    }
    void SetGetHitTestResultImpl(GetHitTestResultImpl&& getHitTestResultImpl)
    {
        getHitTestResultImpl_ = std::move(getHitTestResultImpl);
    }

    using GetHitTestValueImpl = std::function<void(HitTestResult&)>;
    void GetHitTestValue(HitTestResult& result)
    {
        if (getHitTestValueImpl_) {
            getHitTestValueImpl_(result);
        }
    }
    void SetGetHitTestValueImpl(GetHitTestValueImpl&& getHitTestValueImpl)
    {
        getHitTestValueImpl_ = getHitTestValueImpl;
    }

    WebCookie* GetCookieManager()
    {
        if (!saveCookieSyncImpl_ || !setCookieImpl_) {
            return nullptr;
        }
        if (cookieManager_ != nullptr) {
            return cookieManager_;
        }
        cookieManager_ = new WebCookie();
        cookieManager_->SetSaveCookieSyncImpl(std::move(saveCookieSyncImpl_));
        cookieManager_->SetSetCookieImpl(std::move(setCookieImpl_));
        cookieManager_->SetGetCookieImpl(std::move(getCookieImpl_));
        cookieManager_->SetDeleteEntirelyCookieImpl(std::move(deleteEntirelyCookieImpl_));
        return cookieManager_;
    }

    using GetPageHeightImpl = std::function<int()>;
    int GetPageHeight()
    {
        if (getPageHeightImpl_) {
            return getPageHeightImpl_();
        }
        return 0;
    }
    void SetGetPageHeightImpl(GetPageHeightImpl&& getPageHeightImpl)
    {
        getPageHeightImpl_ = getPageHeightImpl;
    }

    using GetWebIdImpl = std::function<int()>;
    int GetWebId()
    {
        if (getWebIdImpl_) {
            return getWebIdImpl_();
        }
        return -1;
    }
    void SetGetWebIdImpl(GetWebIdImpl&& getWebIdImpl)
    {
        getWebIdImpl_ = getWebIdImpl;
    }

    using GetTitleImpl = std::function<std::string()>;
    std::string GetTitle()
    {
        if (getTitleImpl_) {
            return getTitleImpl_();
        }
        return "";
    }
    void SetGetTitleImpl(GetTitleImpl&& getTitleImpl)
    {
        getTitleImpl_ = getTitleImpl;
    }

    using CreateMsgPortsImpl = std::function<void(std::vector<RefPtr<WebMessagePort>>&)>;
    void CreateMsgPorts(std::vector<RefPtr<WebMessagePort>>& ports)
    {
        if (createMsgPortsImpl_) {
            createMsgPortsImpl_(ports);
        }
    }
    void SetCreateMsgPortsImpl(CreateMsgPortsImpl&& createMsgPortsImpl)
    {
        createMsgPortsImpl_ = createMsgPortsImpl;
    }

    using PostWebMessageImpl = std::function<void(std::string&, std::vector<RefPtr<WebMessagePort>>&, std::string&)>;
    void PostWebMessage(std::string& message, std::vector<RefPtr<WebMessagePort>>& ports, std::string& uri)
    {
        if (postWebMessageImpl_) {
            postWebMessageImpl_(message, ports, uri);
        }
    }
    void SetPostWebMessageImpl(PostWebMessageImpl&& postWebMessageImpl)
    {
        postWebMessageImpl_ = postWebMessageImpl;
    }



    using GetDefaultUserAgentImpl = std::function<std::string()>;
    std::string GetDefaultUserAgent()
    {
        if (getDefaultUserAgentImpl_) {
            return getDefaultUserAgentImpl_();
        }
        return "";
    }
    void SetGetDefaultUserAgentImpl(GetDefaultUserAgentImpl&& getDefaultUserAgentImpl)
    {
        getDefaultUserAgentImpl_ = getDefaultUserAgentImpl;
    }

    using SetCookieImpl = std::function<bool(const std::string&, const std::string&)>;
    bool SetCookie(const std::string& url, const std::string& value)
    {
        if (setCookieImpl_) {
            return setCookieImpl_(url, value);
        }
        return false;
    }
    void SetSetCookieImpl(SetCookieImpl&& setCookieImpl)
    {
        setCookieImpl_ = setCookieImpl;
    }

    using GetCookieImpl = std::function<std::string(const std::string&)>;
    std::string GetCookie(const std::string& url)
    {
        if (getCookieImpl_) {
            return getCookieImpl_(url);
        }
        return "";
    }
    void SetGetCookieImpl(GetCookieImpl&& getCookieImpl)
    {
        getCookieImpl_ = getCookieImpl;
    }

    using DeleteEntirelyCookieImpl = std::function<void()>;
    void DeleteEntirelyCookie()
    {
        if (deleteEntirelyCookieImpl_) {
            deleteEntirelyCookieImpl_();
        }
    }
    void SetDeleteEntirelyCookieImpl(DeleteEntirelyCookieImpl&& deleteEntirelyCookieImpl)
    {
        deleteEntirelyCookieImpl_ = deleteEntirelyCookieImpl;
    }

    using SaveCookieSyncImpl = std::function<bool()>;
    bool SaveCookieSync()
    {
        if (saveCookieSyncImpl_) {
            return saveCookieSyncImpl_();
        }
        return false;
    }
    void SetSaveCookieSyncImpl(SaveCookieSyncImpl&& saveCookieSyncImpl)
    {
        saveCookieSyncImpl_ = saveCookieSyncImpl;
    }

    using AddJavascriptInterfaceImpl = std::function<void(
        const std::string&,
        const std::vector<std::string>&)>;
    void AddJavascriptInterface(
        const std::string& objectName,
        const std::vector<std::string>& methodList)
    {
        if (addJavascriptInterfaceImpl_) {
            addJavascriptInterfaceImpl_(objectName, methodList);
        }
    }
    void SetAddJavascriptInterfaceImpl(AddJavascriptInterfaceImpl && addJavascriptInterfaceImpl)
    {
        addJavascriptInterfaceImpl_ = std::move(addJavascriptInterfaceImpl);
    }

    using RemoveJavascriptInterfaceImpl = std::function<void(std::string, const std::vector<std::string>&)>;
    void RemoveJavascriptInterface(std::string objectName, const std::vector<std::string>& methodList)
    {
        if (removeJavascriptInterfaceImpl_) {
            removeJavascriptInterfaceImpl_(objectName, methodList);
        }
    }
    void SetRemoveJavascriptInterfaceImpl(RemoveJavascriptInterfaceImpl && removeJavascriptInterfaceImpl)
    {
        removeJavascriptInterfaceImpl_ = std::move(removeJavascriptInterfaceImpl);
    }

    using JavaScriptCallBackImpl = std::function<std::shared_ptr<WebJSValue>(
        const std::string& objectName,
        const std::string& objectMethod,
        const std::vector<std::shared_ptr<WebJSValue>>& args)>;
    using WebViewJavaScriptResultCallBackImpl = std::function<void(JavaScriptCallBackImpl&& javaScriptCallBackImpl)>;
    void SetWebViewJavaScriptResultCallBackImpl(
        WebViewJavaScriptResultCallBackImpl && webViewJavaScriptResultCallBackImpl)
    {
        webViewJavaScriptResultCallBackImpl_ = webViewJavaScriptResultCallBackImpl;
    }
    void SetJavaScriptCallBackImpl(JavaScriptCallBackImpl&& javaScriptCallBackImpl)
    {
        if (webViewJavaScriptResultCallBackImpl_) {
            webViewJavaScriptResultCallBackImpl_(std::move(javaScriptCallBackImpl));
        }
    }

    using RequestFocusImpl = std::function<void()>;
    void RequestFocus()
    {
        if (requestFocusImpl_) {
            return requestFocusImpl_();
        }
    }
    void SetRequestFocusImpl(RequestFocusImpl  && requestFocusImpl)
    {
        requestFocusImpl_ = std::move(requestFocusImpl);
    }

    using SearchAllAsyncImpl = std::function<void(const std::string&)>;
    void SearchAllAsync(const std::string& searchStr)
    {
        if (searchAllAsyncImpl_) {
            searchAllAsyncImpl_(searchStr);
        }
    }

    void SetSearchAllAsyncImpl(SearchAllAsyncImpl&& searchAllAsyncImpl)
    {
        searchAllAsyncImpl_ = std::move(searchAllAsyncImpl);
    }

    using ClearMatchesImpl = std::function<void()>;
    void ClearMatches()
    {
        if (clearMatchesImpl_) {
            clearMatchesImpl_();
        }
    }
    void SetClearMatchesImpl(ClearMatchesImpl&& clearMatchesImpl)
    {
        clearMatchesImpl_ = std::move(clearMatchesImpl);
    }

    using SearchNextImpl = std::function<void(bool)>;
    void SearchNext(bool forward)
    {
        if (searchNextImpl_) {
            searchNextImpl_(forward);
        }
    }

    void SetSearchNextImpl(SearchNextImpl&& searchNextImpl)
    {
        searchNextImpl_ = std::move(searchNextImpl);
    }

    void Reload() const
    {
        declaration_->webMethod.Reload();
    }

private:
    RefPtr<WebDeclaration> declaration_;
    WebCookie* cookieManager_ = nullptr;
    LoadUrlImpl loadUrlImpl_;

    // Forward and Backward
    AccessBackwardImpl accessBackwardImpl_;
    AccessForwardImpl accessForwardImpl_;
    AccessStepImpl accessStepImpl_;
    BackOrForwardImpl backOrForwardImpl_;
    BackwardImpl backwardImpl_;
    ForwardImpl forwardimpl_;
    ClearHistoryImpl clearHistoryImpl_;
    ClearSslCacheImpl clearSslCacheImpl_;

    ExecuteTypeScriptImpl executeTypeScriptImpl_;
    OnInactiveImpl onInactiveImpl_;
    OnActiveImpl onActiveImpl_;
    ZoomImpl zoomImpl_;
    ZoomInImpl zoomInImpl_;
    ZoomOutImpl zoomOutImpl_;
    LoadDataWithBaseUrlImpl loadDataWithBaseUrlImpl_;
    InitJavascriptInterface initJavascriptInterface_;
    RefreshImpl refreshImpl_;
    StopLoadingImpl stopLoadingImpl_;
    GetHitTestResultImpl getHitTestResultImpl_;
    GetHitTestValueImpl getHitTestValueImpl_;
    GetPageHeightImpl getPageHeightImpl_;
    GetWebIdImpl getWebIdImpl_;
    GetTitleImpl getTitleImpl_;
    CreateMsgPortsImpl createMsgPortsImpl_;
    PostWebMessageImpl postWebMessageImpl_;
    GetDefaultUserAgentImpl getDefaultUserAgentImpl_;
    SaveCookieSyncImpl saveCookieSyncImpl_;
    SetCookieImpl setCookieImpl_;
    GetCookieImpl getCookieImpl_;
    DeleteEntirelyCookieImpl deleteEntirelyCookieImpl_;
    AddJavascriptInterfaceImpl addJavascriptInterfaceImpl_;
    RemoveJavascriptInterfaceImpl removeJavascriptInterfaceImpl_;
    WebViewJavaScriptResultCallBackImpl webViewJavaScriptResultCallBackImpl_;
    RequestFocusImpl requestFocusImpl_;
    SearchAllAsyncImpl searchAllAsyncImpl_;
    ClearMatchesImpl clearMatchesImpl_;
    SearchNextImpl searchNextImpl_;
};

// A component can show HTML5 webpages.
class ACE_EXPORT WebComponent : public RenderComponent {
    DECLARE_ACE_TYPE(WebComponent, RenderComponent);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using ErrorCallback = std::function<void(const std::string&, const std::string&)>;
    using MethodCall = std::function<void(const std::string&)>;
    using Method = std::string;

    WebComponent() = default;
    explicit WebComponent(const std::string& type);
    ~WebComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void SetType(const std::string& type)
    {
        type_ = type;
    }

    const std::string& GetType() const
    {
        return type_;
    }

    void SetSrc(const std::string& src)
    {
        declaration_->SetWebSrc(src);
    }

    const std::string& GetSrc() const
    {
        return declaration_->GetWebSrc();
    }

    void SetData(const std::string& data)
    {
        declaration_->SetWebData(data);
    }

    const std::string& GetData() const
    {
        return declaration_->GetWebData();
    }

    void SetPageStartedEventId(const EventMarker& pageStartedEventId)
    {
        declaration_->SetPageStartedEventId(pageStartedEventId);
    }

    const EventMarker& GetPageStartedEventId() const
    {
        return declaration_->GetPageStartedEventId();
    }

    void SetPageFinishedEventId(const EventMarker& pageFinishedEventId)
    {
        declaration_->SetPageFinishedEventId(pageFinishedEventId);
    }

    const EventMarker& GetPageFinishedEventId() const
    {
        return declaration_->GetPageFinishedEventId();
    }

    using OnProgressChangeImpl = std::function<void(const BaseEventInfo* info)>;
    void OnProgressChange(const BaseEventInfo* info) const
    {
        if (onProgressChangeImpl_) {
            onProgressChangeImpl_(info);
        }
    }
    void SetProgressChangeImpl(OnProgressChangeImpl && onProgressChangeImpl)
    {
        if (onProgressChangeImpl == nullptr) {
            return;
        }
        onProgressChangeImpl_ = std::move(onProgressChangeImpl);
    }

    void SetTitleReceiveEventId(const EventMarker& titleReceiveEventId)
    {
        declaration_->SetTitleReceiveEventId(titleReceiveEventId);
    }

    const EventMarker& GetTitleReceiveEventId() const
    {
        return declaration_->GetTitleReceiveEventId();
    }

    void SetGeolocationHideEventId(const EventMarker& geolocationHideEventId)
    {
        declaration_->SetGeolocationHideEventId(geolocationHideEventId);
    }

    const EventMarker& GetGeolocationHideEventId() const
    {
        return declaration_->GetGeolocationHideEventId();
    }

    void SetGeolocationShowEventId(const EventMarker& geolocationShowEventId)
    {
        declaration_->SetGeolocationShowEventId(geolocationShowEventId);
    }

    const EventMarker& GetGeolocationShowEventId() const
    {
        return declaration_->GetGeolocationShowEventId();
    }

    void SetRequestFocusEventId(const EventMarker& requestFocusEventId)
    {
        declaration_->SetRequestFocusEventId(requestFocusEventId);
    }

    const EventMarker& GetRequestFocusEventId() const
    {
        return declaration_->GetRequestFocusEventId();
    }

    void SetDownloadStartEventId(const EventMarker& downloadStartEventId)
    {
        declaration_->SetDownloadStartEventId(downloadStartEventId);
    }

    const EventMarker& GetDownloadStartEventId() const
    {
        return declaration_->GetDownloadStartEventId();
    }

    void SetPageErrorEventId(const EventMarker& pageErrorEventId)
    {
        declaration_->SetPageErrorEventId(pageErrorEventId);
    }

    const EventMarker& GetPageErrorEventId() const
    {
        return declaration_->GetPageErrorEventId();
    }

    void SetHttpErrorEventId(const EventMarker& httpErrorEventId)
    {
        declaration_->SetHttpErrorEventId(httpErrorEventId);
    }

    const EventMarker& GetHttpErrorEventId() const
    {
        return declaration_->GetHttpErrorEventId();
    }

    void SetMessageEventId(const EventMarker& messageEventId)
    {
        declaration_->SetMessageEventId(messageEventId);
    }

    const EventMarker& GetMessageEventId() const
    {
        return declaration_->GetMessageEventId();
    }

    void SetRenderExitedId(const EventMarker& renderExitedId)
    {
        declaration_->SetRenderExitedId(renderExitedId);
    }

    const EventMarker& GetRenderExitedId() const
    {
        return declaration_->GetRenderExitedId();
    }

    void SetRefreshAccessedHistoryId(const EventMarker& refreshAccessedHistoryId)
    {
        declaration_->SetRefreshAccessedHistoryId(refreshAccessedHistoryId);
    }

    const EventMarker& GetRefreshAccessedHistoryId() const
    {
        return declaration_->GetRefreshAccessedHistoryId();
    }

    void SetResourceLoadId(const EventMarker& resourceLoadId)
    {
        declaration_->SetResourceLoadId(resourceLoadId);
    }

    const EventMarker& GetResourceLoadId() const
    {
        return declaration_->GetResourceLoadId();
    }

    void SetScaleChangeId(const EventMarker& scaleChangeId)
    {
        declaration_->SetScaleChangeId(scaleChangeId);
    }

    const EventMarker& GetScaleChangeId() const
    {
        return declaration_->GetScaleChangeId();
    }

    void SetScrollId(const EventMarker& scrollId)
    {
        declaration_->SetScrollId(scrollId);
    }

    const EventMarker& GetScrollId() const
    {
        return declaration_->GetScrollId();
    }

    void SetPermissionRequestEventId(const EventMarker& permissionRequestEventId)
    {
        declaration_->SetPermissionRequestEventId(permissionRequestEventId);
    }

    const EventMarker& GetPermissionRequestEventId() const
    {
        return declaration_->GetPermissionRequestEventId();
    }

    void SetDeclaration(const RefPtr<WebDeclaration>& declaration)
    {
        if (declaration) {
            declaration_ = declaration;
        }
    }

    RefPtr<WebController> GetController() const
    {
        return webController_;
    }

    void SetWebController(const RefPtr<WebController>& webController)
    {
        webController_ = webController;
    }

    bool GetJsEnabled() const
    {
        return isJsEnabled_;
    }

    void SetJsEnabled(bool isEnabled)
    {
        isJsEnabled_ = isEnabled;
    }

    std::string GetUserAgent() const
    {
        return userAgent_;
    }

    void SetUserAgent(std::string userAgent)
    {
        userAgent_ = userAgent;
    }

    bool GetContentAccessEnabled() const
    {
        return isContentAccessEnabled_;
    }

    void SetContentAccessEnabled(bool isEnabled)
    {
        isContentAccessEnabled_ = isEnabled;
    }

    bool GetFileAccessEnabled() const
    {
        return isFileAccessEnabled_;
    }

    void SetFileAccessEnabled(bool isEnabled)
    {
        isFileAccessEnabled_ = isEnabled;
    }
    bool GetOnLineImageAccessEnabled() const
    {
        return isOnLineImageAccessEnabled_;
    }

    void SetOnLineImageAccessEnabled(bool isEnabled)
    {
        isOnLineImageAccessEnabled_ = isEnabled;
    }

    bool GetDomStorageAccessEnabled() const
    {
        return isDomStorageAccessEnabled_;
    }

    void SetDomStorageAccessEnabled(bool isEnabled)
    {
        isDomStorageAccessEnabled_ = isEnabled;
    }

    bool GetImageAccessEnabled() const
    {
        return isImageAccessEnabled_;
    }

    void SetImageAccessEnabled(bool isEnabled)
    {
        isImageAccessEnabled_ = isEnabled;
    }

    MixedModeContent GetMixedMode() const
    {
        return mixedContentMode_;
    }

    void SetMixedMode(MixedModeContent mixedModeNum)
    {
        mixedContentMode_ = mixedModeNum;
    }

    bool GetZoomAccessEnabled() const
    {
        return isZoomAccessEnabled_;
    }

    void SetZoomAccessEnabled(bool isEnabled)
    {
        isZoomAccessEnabled_ = isEnabled;
    }

    bool GetGeolocationAccessEnabled() const
    {
        return isGeolocationAccessEnabled_;
    }

    void SetGeolocationAccessEnabled(bool isEnabled)
    {
        isGeolocationAccessEnabled_ = isEnabled;
    }

    WebCacheMode GetCacheMode() {
        return cacheMode_;
    }

    void SetCacheMode(WebCacheMode mode) {
        cacheMode_ = mode;
    }

    bool GetOverviewModeAccessEnabled() const
    {
        return isOverviewModeAccessEnabled_;
    }

    void SetOverviewModeAccessEnabled(bool isEnabled)
    {
        isOverviewModeAccessEnabled_ = isEnabled;
    }

    bool GetFileFromUrlAccessEnabled() const
    {
        return isFileFromUrlAccessEnabled_;
    }

    void SetFileFromUrlAccessEnabled(bool isEnabled)
    {
        isFileFromUrlAccessEnabled_ = isEnabled;
    }

    bool GetDatabaseAccessEnabled() const
    {
        return isDatabaseAccessEnabled_;
    }

    void SetDatabaseAccessEnabled(bool isEnabled)
    {
        isDatabaseAccessEnabled_ = isEnabled;
    }

    bool GetWebDebuggingAccessEnabled() const
    {
        return isWebDebuggingAccessEnabled_;
    }

    void SetWebDebuggingAccessEnabled(bool isEnabled)
    {
        isWebDebuggingAccessEnabled_ = isEnabled;
    }

    bool GetIsInitialScaleSet() const
    {
        return isInitialScaleSet_;
    }

    float GetInitialScale() const
    {
        return initialScale_;
    }

    void SetInitialScale(float scale)
    {
        initialScale_ = scale;
        isInitialScaleSet_ = true;
    }

    bool GetBackgroundColorEnabled() const
    {
        return isBackgroundColor_;
    }

    int32_t GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    void SetBackgroundColor(int32_t backgroundColor)
    {
        backgroundColor_ = backgroundColor;
        isBackgroundColor_ = true;
    }

    int32_t GetTextZoomRatio() const
    {
        return textZoomRatioNum_;
    }

    void SetTextZoomRatio(int32_t ratio)
    {
        textZoomRatioNum_ = ratio;
    }

    using OnCommonDialogImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnCommonDialog(const BaseEventInfo* info, DialogEventType dialogEventType) const
    {
        if (dialogEventType == DialogEventType::DIALOG_EVENT_ALERT && onAlertImpl_) {
            return onAlertImpl_(info);
        } else if (dialogEventType == DialogEventType::DIALOG_EVENT_CONFIRM && onConfirmImpl_) {
            return onConfirmImpl_(info);
        } else if (dialogEventType == DialogEventType::DIALOG_EVENT_PROMPT && onPromptImpl_) {
            return onPromptImpl_(info);
        } else if (dialogEventType == DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD && onBeforeUnloadImpl_) {
            return onBeforeUnloadImpl_(info);
        } else {
            return false;
        }
    }
    void SetOnCommonDialogImpl(OnCommonDialogImpl && onCommonDialogImpl, DialogEventType dialogEventType)
    {
        if (onCommonDialogImpl == nullptr) {
            return;
        }

        switch (dialogEventType) {
            case DialogEventType::DIALOG_EVENT_ALERT:
                onAlertImpl_ = std::move(onCommonDialogImpl);
                break;
            case DialogEventType::DIALOG_EVENT_CONFIRM:
                onConfirmImpl_ = std::move(onCommonDialogImpl);
                break;
            case DialogEventType::DIALOG_EVENT_PROMPT:
                onPromptImpl_ = std::move(onCommonDialogImpl);
                break;
            case DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD:
                onBeforeUnloadImpl_ = std::move(onCommonDialogImpl);
                break;
            default:
                break;
        }
    }

    using OnHttpAuthRequestImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnHttpAuthRequest(const BaseEventInfo* info) const
    {
        if (onHttpAuthRequestImpl_) {
            return onHttpAuthRequestImpl_(info);
        }
        return false;
    }
    void SetOnHttpAuthRequestImpl(OnHttpAuthRequestImpl && onHttpAuthRequestImpl)
    {
        if (onHttpAuthRequestImpl == nullptr) {
            return;
        }
        onHttpAuthRequestImpl_ = std::move(onHttpAuthRequestImpl);
    }

    using OnSslErrorRequestImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnSslErrorRequest(const BaseEventInfo* info) const
    {
        if (onSslErrorRequestImpl_) {
            return onSslErrorRequestImpl_(info);
        }
        return false;
    }
    void SetOnSslErrorRequestImpl(OnSslErrorRequestImpl && onSslErrorRequestImpl)
    {
        if (onSslErrorRequestImpl == nullptr) {
            return;
        }
        onSslErrorRequestImpl_ = std::move(onSslErrorRequestImpl);
    }

    void RequestFocus();

    using OnConsoleImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnConsole(const BaseEventInfo* info) const
    {
        if (consoleImpl_) {
            return consoleImpl_(info);
        }
        return false;
    }

    void SetOnConsoleImpl(OnConsoleImpl && consoleImpl)
    {
        consoleImpl_ = std::move(consoleImpl);
    }

    void SetFocusElement(const WeakPtr<FocusNode>& focusElement)
    {
        focusElement_ = focusElement;
    }

    using OnFileSelectorShowImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnFileSelectorShow(const BaseEventInfo* info) const
    {
        if (onFileSelectorShowImpl_) {
            return onFileSelectorShowImpl_(info);
        }
        return false;
    }
    void SetOnFileSelectorShow(OnFileSelectorShowImpl && onFileSelectorShowImpl)
    {
        if (onFileSelectorShowImpl == nullptr) {
            return;
        }

        onFileSelectorShowImpl_ = onFileSelectorShowImpl;
    }

    using OnContextMenuImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnContextMenuShow(const BaseEventInfo* info) const
    {
        if (onContextMenuImpl_) {
            return onContextMenuImpl_(info);
        }
        return false;
    }
    void SetOnContextMenuShow(OnContextMenuImpl && onContextMenuImpl)
    {
        if (onContextMenuImpl == nullptr) {
            return;
        }
        onContextMenuImpl_ = std::move(onContextMenuImpl);
    }

    using OnUrlLoadInterceptImpl = std::function<bool(const BaseEventInfo* info)>;
    bool OnUrlLoadIntercept(const BaseEventInfo* info) const
    {
        if (onUrlLoadInterceptImpl_) {
            return onUrlLoadInterceptImpl_(info);
        }
        return false;
    }
    void SetOnUrlLoadIntercept(OnUrlLoadInterceptImpl && onUrlLoadInterceptImpl)
    {
        if (onUrlLoadInterceptImpl == nullptr) {
            return;
        }

        onUrlLoadInterceptImpl_ = onUrlLoadInterceptImpl;
    }

    using OnInterceptRequestImpl = std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>;
    RefPtr<WebResponse> OnInterceptRequest(const BaseEventInfo* info) const
    {
        if (onInterceptRequestImpl_) {
            return onInterceptRequestImpl_(info);
        }
        return nullptr;
    }

    bool IsEmptyOnInterceptRequest() const
    {
        if (onInterceptRequestImpl_ == nullptr) {
            return true;
        }
        return false;
    }

    void SetOnInterceptRequest(OnInterceptRequestImpl&& onInterceptRequestImpl)
    {
        if (onInterceptRequestImpl == nullptr) {
            return;
        }
        onInterceptRequestImpl_ = std::move(onInterceptRequestImpl);
    }

    void SetOnMouseEventCallback(const OnMouseCallback& onMouseId)
    {
        onMouseEvent_ = onMouseId;
    }

    OnMouseCallback GetOnMouseEventCallback() const
    {
        return onMouseEvent_;
    }

    void SetOnKeyEventCallback(const OnKeyEventCallback& onKeyEventId)
    {
        onKeyEvent_ = onKeyEventId;
    }

    OnKeyEventCallback GetOnKeyEventCallback() const
    {
        return onKeyEvent_;
    }

    void SetSearchResultReceiveEventId(const EventMarker& searchResultReceiveEventId)
    {
        declaration_->SetSearchResultReceiveEventId(searchResultReceiveEventId);
    }

    const EventMarker& GetSearchResultReceiveEventId() const
    {
        return declaration_->GetSearchResultReceiveEventId();
    }

    void SetMediaPlayGestureAccess(bool isNeedGestureAccess)
    {
        isNeedGestureAccess_ = isNeedGestureAccess;
    }

    bool IsMediaPlayGestureAccess() const
    {
        return isNeedGestureAccess_;
    }

private:
    RefPtr<WebDeclaration> declaration_;
    CreatedCallback createdCallback_ = nullptr;
    ReleasedCallback releasedCallback_ = nullptr;
    ErrorCallback errorCallback_ = nullptr;
    RefPtr<WebDelegate> delegate_;
    RefPtr<WebController> webController_;
    OnCommonDialogImpl onAlertImpl_;
    OnCommonDialogImpl onConfirmImpl_;
    OnCommonDialogImpl onPromptImpl_;
    OnCommonDialogImpl onBeforeUnloadImpl_;
    OnConsoleImpl consoleImpl_;
    OnFileSelectorShowImpl onFileSelectorShowImpl_;
    OnUrlLoadInterceptImpl onUrlLoadInterceptImpl_;
    OnHttpAuthRequestImpl onHttpAuthRequestImpl_;
    OnSslErrorRequestImpl onSslErrorRequestImpl_;
    OnContextMenuImpl onContextMenuImpl_;
    OnInterceptRequestImpl onInterceptRequestImpl_ = nullptr;
    OnProgressChangeImpl onProgressChangeImpl_ = nullptr;

    std::string type_;
    bool isJsEnabled_ = true;
    bool isContentAccessEnabled_ = true;
    bool isFileAccessEnabled_ = true;
    std::string userAgent_;
    WeakPtr<FocusNode> focusElement_;
    bool isOnLineImageAccessEnabled_ = false;
    bool isDomStorageAccessEnabled_ = false;
    bool isImageAccessEnabled_ = true;
    MixedModeContent mixedContentMode_ = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
    bool isZoomAccessEnabled_ = true;
    bool isGeolocationAccessEnabled_ = true;
    bool isOverviewModeAccessEnabled_ = true;
    bool isFileFromUrlAccessEnabled_ = false;
    bool isDatabaseAccessEnabled_ = false;
    int32_t textZoomRatioNum_ = DEFAULT_TEXT_ZOOM_RATIO;
    WebCacheMode cacheMode_ = WebCacheMode::DEFAULT;
    bool isWebDebuggingAccessEnabled_ = false;
    OnMouseCallback onMouseEvent_;
    OnKeyEventCallback onKeyEvent_;
    float initialScale_;
    bool isInitialScaleSet_ = false;
    int32_t backgroundColor_;
    bool isBackgroundColor_ = false;
    bool isNeedGestureAccess_ = true;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_COMPONENT_H
