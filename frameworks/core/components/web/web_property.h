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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_PROPERTY_H

#include <functional>
#include <utility>

#include "base/geometry/size.h"
#include "base/utils/utils.h"
#include "core/components/declaration/web/web_client.h"
#include "core/components/web/resource/web_javascript_value.h"
#include "core/components/web/web_event.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_v2/common/common_def.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"

namespace OHOS::Ace {

class WebDelegate;
using ScriptItems = std::map<std::string, std::vector<std::string>>;
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

enum OverScrollMode {
    NEVER = 0,
    ALWAYS,
};

enum class WebDarkMode {
    Off,
    On,
    Auto,
};

enum class WebLayoutMode {
    NONE,
    FIT_CONTENT,
};

enum class WebKeyboardAvoidMode : int32_t {
    RESIZE_VISUAL = 0,
    RESIZE_CONTENT,
    OVERLAYS_CONTENT,
    DEFAULT
};

struct WebMenuOptionsParam {
    std::vector<NG::MenuOptionsParam> menuOption;
    bool operator==(const WebMenuOptionsParam& webMenuOption) const
    {
        return menuOption.data() == webMenuOption.menuOption.data();
    }
};

constexpr int32_t DEFAULT_TEXT_ZOOM_RATIO = 100;
constexpr int32_t DEFAULT_FIXED_FONT_SIZE = 13;
constexpr int32_t DEFAULT_FONT_SIZE = 16;
constexpr int32_t DEFAULT_MINIMUM_FONT_SIZE = 8;
constexpr int32_t DEFAULT_MINIMUM_LOGICAL_FONT_SIZE = 8;
const std::string DEFAULT_CURSIVE_FONT_FAMILY = "cursive";
const std::string DEFAULT_FANTASY_FONT_FAMILY = "fantasy";
const std::string DEFAULT_FIXED_fONT_FAMILY = "monospace";
const std::string DEFAULT_SANS_SERIF_FONT_FAMILY = "sans-serif";
const std::string DEFAULT_SERIF_FONT_FAMILY = "serif";
const std::string DEFAULT_STANDARD_FONT_FAMILY = "sans-serif";
const std::string DEFAULT_SCROLLBAR_COLOR = "sys.color.ohos_id_color_foreground";

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

    void SetHitType(int hitType)
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
    using ClearClientAuthenticationCacheImpl = std::function<void()>;

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
        if (backwardImpl_) {
            backwardImpl_();
        }
    }

    void Forward()
    {
        if (forwardimpl_) {
            forwardimpl_();
        }
    }

    void ClearHistory()
    {
        if (clearHistoryImpl_) {
            clearHistoryImpl_();
        }
    }

    void ClearSslCache()
    {
        if (clearSslCacheImpl_) {
            clearSslCacheImpl_();
        }
    }

    void ClearClientAuthenticationCache()
    {
        if (clearClientAuthenticationCacheImpl_) {
            clearClientAuthenticationCacheImpl_();
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

    void SetClearSslCacheImpl(ClearSslCacheImpl && clearSslCacheImpl)
    {
        clearSslCacheImpl_ = std::move(clearSslCacheImpl);
    }

    void SetClearClientAuthenticationCacheImpl(ClearClientAuthenticationCacheImpl && clearClientAuthenticationCacheImpl)
    {
        clearClientAuthenticationCacheImpl_ = std::move(clearClientAuthenticationCacheImpl);
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
        WebClient::GetInstance().ReloadWebview();
    }

    using GetUrlImpl = std::function<std::string()>;
    std::string GetUrl()
    {
        if (getUrlImpl_) {
            return getUrlImpl_();
        }
        return "";
    }

    void SetGetUrlImpl(GetUrlImpl && getUrlImpl)
    {
        getUrlImpl_ = std::move(getUrlImpl);
    }

private:
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
    ClearClientAuthenticationCacheImpl clearClientAuthenticationCacheImpl_;

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
    GetUrlImpl getUrlImpl_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_PROPERTY_H
