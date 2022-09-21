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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H

#include <list>
#include <map>

#include "base/memory/referenced.h"
#include "core/components_ng/render/render_surface.h"
#include "core/pipeline/pipeline_base.h"
#ifdef OHOS_STANDARD_SYSTEM
#include <ui/rs_surface_node.h>
#endif

#include "base/image/pixel_map.h"
#include "core/components/common/layout/constants.h"
#include "core/components/web/resource/web_client_impl.h"
#include "core/components/web/resource/web_resource.h"
#include "core/components/web/web_component.h"
#include "core/components/web/web_event.h"
#ifdef OHOS_STANDARD_SYSTEM
#include "nweb_handler.h"
#include "nweb_helper.h"
#include "nweb_hit_testresult.h"
#include "window.h"
#endif

namespace OHOS::Ace {

class WebMessagePortOhos : public WebMessagePort {
    DECLARE_ACE_TYPE(WebMessagePortOhos, WebMessagePort)

public:
    WebMessagePortOhos(WeakPtr<WebDelegate> webDelegate) : webDelegate_(webDelegate) {}
    WebMessagePortOhos() = default;
    ~WebMessagePortOhos() = default;

    void Close() override;
    void PostMessage(std::string& data) override;
    void SetWebMessageCallback(std::function<void(const std::string&)>&& callback) override;
    void SetPortHandle(std::string& handle) override;
    std::string GetPortHandle() override;

private:
    WeakPtr<WebDelegate> webDelegate_;
    std::string handle_;
};

class ConsoleLogOhos : public WebConsoleLog {
    DECLARE_ACE_TYPE(ConsoleLogOhos, WebConsoleLog)

public:
    ConsoleLogOhos(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message) : message_(message) {}

    int GetLineNumber() override;

    std::string GetLog() override;

    int GetLogLevel() override;

    std::string GetSourceId() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message_;
};

class ResultOhos : public Result {
    DECLARE_ACE_TYPE(ResultOhos, Result)

public:
    ResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSDialogResult> result) : result_(result) {}

    void Confirm() override;
    void Confirm(const std::string& message) override;
    void Cancel() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebJSDialogResult> result_;
};

class AuthResultOhos : public AuthResult {
    DECLARE_ACE_TYPE(AuthResultOhos, AuthResult)

public:
    AuthResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSHttpAuthResult> result) : result_(result) {}

    bool Confirm(std::string& userName, std::string& pwd) override;
    bool IsHttpAuthInfoSaved() override;
    void Cancel() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebJSHttpAuthResult> result_;
};

class SslErrorResultOhos : public SslErrorResult {
    DECLARE_ACE_TYPE(SslErrorResultOhos, SslErrorResult)

public:
    SslErrorResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSSslErrorResult> result) : result_(result) {}

    void HandleConfirm() override;
    void HandleCancel() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebJSSslErrorResult> result_;
};

class SslSelectCertResultOhos : public SslSelectCertResult {
    DECLARE_ACE_TYPE(SslSelectCertResultOhos, SslSelectCertResult)

public:
    SslSelectCertResultOhos(std::shared_ptr<OHOS::NWeb::NWebJSSslSelectCertResult> result)
        : result_(result) {}

    void HandleConfirm(const std::string& privateKeyFile, const std::string& certChainFile) override;

    void HandleCancel() override;

    void HandleIgnore() override;
private:
    std::shared_ptr<OHOS::NWeb::NWebJSSslSelectCertResult> result_;
};

class FileSelectorParamOhos : public WebFileSelectorParam {
    DECLARE_ACE_TYPE(FileSelectorParamOhos, WebFileSelectorParam)

public:
    FileSelectorParamOhos(std::shared_ptr<OHOS::NWeb::NWebFileSelectorParams> param) : param_(param) {}

    std::string GetTitle() override;
    int GetMode() override;
    std::string GetDefaultFileName() override;
    std::vector<std::string> GetAcceptType() override;
    bool IsCapture() override;

private:
    std::shared_ptr<OHOS::NWeb::NWebFileSelectorParams> param_;
};

class FileSelectorResultOhos : public FileSelectorResult {
    DECLARE_ACE_TYPE(FileSelectorResultOhos, FileSelectorResult)

public:
    FileSelectorResultOhos(std::shared_ptr<OHOS::NWeb::FileSelectorCallback> callback) : callback_(callback) {}

    void HandleFileList(std::vector<std::string>& result) override;

private:
    std::shared_ptr<OHOS::NWeb::FileSelectorCallback> callback_;
};

class ContextMenuParamOhos : public WebContextMenuParam {
    DECLARE_ACE_TYPE(ContextMenuParamOhos, WebContextMenuParam)

public:
    ContextMenuParamOhos(std::shared_ptr<OHOS::NWeb::NWebContextMenuParams> param) : param_(param) {}

    int32_t GetXCoord() const override;
    int32_t GetYCoord() const override;
    std::string GetLinkUrl() const override;
    std::string GetUnfilteredLinkUrl() const override;
    std::string GetSourceUrl() const override;
    bool HasImageContents() const override;

private:
    std::shared_ptr<OHOS::NWeb::NWebContextMenuParams> param_;
};

class ContextMenuResultOhos : public ContextMenuResult {
    DECLARE_ACE_TYPE(ContextMenuResultOhos, ContextMenuResult)

public:
    ContextMenuResultOhos(std::shared_ptr<OHOS::NWeb::NWebContextMenuCallback> callback) : callback_(callback) {}

    void Cancel() const override;
    void CopyImage() const override;

private:
    std::shared_ptr<OHOS::NWeb::NWebContextMenuCallback> callback_;
};

class WebGeolocationOhos : public WebGeolocation {
    DECLARE_ACE_TYPE(WebGeolocationOhos, WebGeolocation)

public:
    WebGeolocationOhos(OHOS::NWeb::NWebGeolocationCallbackInterface* callback) : geolocationCallback_(callback) {}

    void Invoke(const std::string& origin, const bool& allow, const bool& retain) override;

private:
    std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface> geolocationCallback_;
};

class WebPermissionRequestOhos : public WebPermissionRequest {
    DECLARE_ACE_TYPE(WebPermissionRequestOhos, WebPermissionRequest)

public:
    WebPermissionRequestOhos(const std::shared_ptr<OHOS::NWeb::NWebAccessRequest>& request) : request_(request) {}

    void Deny() const override;

    std::string GetOrigin() const override;

    std::vector<std::string> GetResources() const override;

    void Grant(std::vector<std::string>& resources) const override;

private:
    std::shared_ptr<OHOS::NWeb::NWebAccessRequest> request_;
};

enum class DragAction {
    DRAG_START = 0,
    DRAG_ENTER,
    DRAG_LEAVE,
    DRAG_OVER,
    DRAG_DROP,
    DRAG_END,
    DRAG_CANCEL,
};

namespace NG {
class WebPattern;
}; // namespace NG

class RenderWeb;
class WebDelegate : public WebResource {
    DECLARE_ACE_TYPE(WebDelegate, WebResource);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using EventCallback = std::function<void(const std::string&)>;
    using EventCallbackV2 = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    enum class State : char {
        WAITINGFORSIZE,
        CREATING,
        CREATED,
        CREATEFAILED,
        RELEASED,
    };

    WebDelegate() = delete;
    ~WebDelegate() override;
    WebDelegate(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type)
        : WebResource(type, context, std::move(onError))
    {}

    void SetRenderWeb(const WeakPtr<RenderWeb>& renderWeb);

    void CreatePlatformResource(const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context);
    void CreatePluginResource(const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context);
    void AddCreatedCallback(const CreatedCallback& createdCallback);
    void RemoveCreatedCallback();
    void AddReleasedCallback(const ReleasedCallback& releasedCallback);
    void SetComponent(const RefPtr<WebComponent>& component);
    void RemoveReleasedCallback();
    void Reload();
    void UpdateUrl(const std::string& url);
#ifdef OHOS_STANDARD_SYSTEM
    // TODO: add to separate this file into three file, base file, component impl and ng impl.
    void InitOHOSWeb(const RefPtr<PipelineBase>& context, const RefPtr<NG::RenderSurface>& surface);
    void InitOHOSWeb(const WeakPtr<PipelineBase>& context, sptr<Surface> surface = nullptr);
    void InitWebViewWithWindow();
    void ShowWebView();
    void HideWebView();
    void Resize(const double& width, const double& height);
    void UpdateUserAgent(const std::string& userAgent);
    void UpdateBackgroundColor(const int backgroundColor);
    void UpdateInitialScale(float scale);
    void UpdateJavaScriptEnabled(const bool& isJsEnabled);
    void UpdateAllowFileAccess(const bool& isFileAccessEnabled);
    void UpdateBlockNetworkImage(const bool& onLineImageAccessEnabled);
    void UpdateLoadsImagesAutomatically(const bool& isImageAccessEnabled);
    void UpdateMixedContentMode(const MixedModeContent& mixedMode);
    void UpdateSupportZoom(const bool& isZoomAccessEnabled);
    void UpdateDomStorageEnabled(const bool& isDomStorageAccessEnabled);
    void UpdateGeolocationEnabled(const bool& isGeolocationAccessEnabled);
    void UpdateCacheMode(const WebCacheMode& mode);
    void UpdateOverviewModeEnabled(const bool& isOverviewModeAccessEnabled);
    void UpdateFileFromUrlEnabled(const bool& isFileFromUrlAccessEnabled);
    void UpdateDatabaseEnabled(const bool& isDatabaseAccessEnabled);
    void UpdateTextZoomRatio(const int32_t& textZoomRatioNum);
    void UpdateWebDebuggingAccess(bool isWebDebuggingAccessEnabled);
    void UpdatePinchSmoothModeEnabled(bool isPinchSmoothModeEnabled);
    void UpdateMediaPlayGestureAccess(bool isNeedGestureAccess);
    void LoadUrl();
    void CreateWebMessagePorts(std::vector<RefPtr<WebMessagePort>>& ports);
    void PostWebMessage(std::string& message, std::vector<RefPtr<WebMessagePort>>& ports, std::string& uri);
    void ClosePort(std::string& handle);
    void PostPortMessage(std::string& handle, std::string& data);
    void SetPortMessageCallback(std::string& handle, std::function<void(const std::string&)>&& callback);
    void HandleTouchDown(const int32_t& id, const double& x, const double& y);
    void HandleTouchUp(const int32_t& id, const double& x, const double& y);
    void HandleTouchMove(const int32_t& id, const double& x, const double& y);
    void HandleTouchCancel();
    void HandleAxisEvent(const double& x, const double& y, const double& deltaX, const double& deltaY);
    bool OnKeyEvent(int32_t keyCode, int32_t keyAction);
    void OnMouseEvent(int32_t x, int32_t y, const MouseButton button, const MouseAction action, int count);
    void OnFocus();
    void OnBlur();
    void OnPermissionRequestPrompt(const std::shared_ptr<OHOS::NWeb::NWebAccessRequest>& request);
    bool RunQuickMenu(
        std::shared_ptr<NWeb::NWebQuickMenuParams> params, std::shared_ptr<NWeb::NWebQuickMenuCallback> callback);
    void OnQuickMenuDismissed();
    void OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle);
    void HandleDragEvent(int32_t x, int32_t y, const DragAction& dragAction);
    RefPtr<PixelMap> GetDragPixelMap();
    std::string GetUrl();
#endif
    void OnErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
        std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error);
    void OnHttpErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
        std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response);
    RefPtr<WebResponse> OnInterceptRequest(const BaseEventInfo* info);
    bool IsEmptyOnInterceptRequest();
    void OnPageStarted(const std::string& param);
    void OnPageFinished(const std::string& param);
    void OnProgressChanged(int param);
    void OnReceivedTitle(const std::string& param);
    void OnGeolocationPermissionsHidePrompt();
    void OnGeolocationPermissionsShowPrompt(
        const std::string& origin, OHOS::NWeb::NWebGeolocationCallbackInterface* callback);
    void OnRequestFocus();
    bool OnCommonDialog(const BaseEventInfo* info, DialogEventType dialogEventType);
    bool OnHttpAuthRequest(const BaseEventInfo* info);
    bool OnSslErrorRequest(const BaseEventInfo* info);
    bool OnSslSelectCertRequest(const BaseEventInfo* info);
    void OnDownloadStart(const std::string& url, const std::string& userAgent, const std::string& contentDisposition,
        const std::string& mimetype, long contentLength);
    void OnPageError(const std::string& param);
    void OnMessage(const std::string& param);
    bool OnConsoleLog(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message);
    void OnRouterPush(const std::string& param);
    void OnRenderExited(OHOS::NWeb::RenderExitReason reason);
    void OnRefreshAccessedHistory(const std::string& url, bool isRefreshed);
    bool OnFileSelectorShow(const BaseEventInfo* info);
    bool OnContextMenuShow(const BaseEventInfo* info);
    bool OnHandleInterceptUrlLoading(const std::string& url);
    void OnResourceLoad(const std::string& url);
    void OnScaleChange(float oldScaleFactor, float newScaleFactor);
    void OnScroll(double xOffset, double yOffset);
    bool LoadDataWithRichText();
    void OnSearchResultReceive(int activeMatchOrdinal, int numberOfMatches, bool isDoneCounting);
    bool OnDragAndDropData(const void* data, size_t len, int width, int height);

    void SetNGWebPattern(const RefPtr<NG::WebPattern>& webPattern);

private:
    void InitWebEvent();
    void RegisterWebEvent();
    void ReleasePlatformResource();
    void Stop();
    void UnregisterEvent();
    std::string GetUrlStringParam(const std::string& param, const std::string& name) const;
    void CallWebRouterBack();
    void CallPopPageSuccessPageUrl(const std::string& url);
    void CallIsPagePathInvalid(const bool& isPageInvalid);

    void BindRouterBackMethod();
    void BindPopPageSuccessMethod();
    void BindIsPagePathInvalidMethod();

#ifdef OHOS_STANDARD_SYSTEM
    sptr<OHOS::Rosen::Window> CreateWindow();
    void LoadUrl(const std::string& url, const std::map<std::string, std::string>& httpHeaders);
    void ExecuteTypeScript(const std::string& jscode, const std::function<void(std::string)>&& callback);
    void LoadDataWithBaseUrl(const std::string& baseUrl, const std::string& data, const std::string& mimeType,
        const std::string& encoding, const std::string& historyUrl);
    void Refresh();
    void StopLoading();
    void AddJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList);
    void RemoveJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList);
    void SetWebViewJavaScriptResultCallBack(const WebController::JavaScriptCallBackImpl&& javaScriptCallBackImpl);
    void RequestFocus();
    void OnInactive();
    void OnActive();
    void Zoom(float factor);
    bool ZoomIn();
    bool ZoomOut();
    int ConverToWebHitTestType(int hitType);
    int GetHitTestResult();
    void GetHitTestValue(HitTestResult& result);
    int GetPageHeight();
    int GetWebId();
    std::string GetTitle();
    std::string GetDefaultUserAgent();
    bool SaveCookieSync();
    bool SetCookie(const std::string& url, const std::string& value);
    std::string GetCookie(const std::string& url) const;
    void DeleteEntirelyCookie();
    void RegisterOHOSWebEventAndMethord();
    void SetWebCallBack();

    // Backward and forward
    void Backward();
    void Forward();
    void ClearHistory();
    void ClearSslCache();
    void ClearClientAuthenticationCache();
    bool AccessStep(int32_t step);
    void BackOrForward(int32_t step);
    bool AccessBackward();
    bool AccessForward();

    void SearchAllAsync(const std::string& searchStr);
    void ClearMatches();
    void SearchNext(bool forward);

    void UpdateSettting(bool useNewPipe = false);

#if defined(ENABLE_ROSEN_BACKEND)
    void InitWebViewWithSurface(sptr<Surface> surface);
#endif
#endif

    WeakPtr<WebComponent> webComponent_;
    WeakPtr<RenderWeb> renderWeb_;

    WeakPtr<NG::WebPattern> webPattern_;

    std::list<CreatedCallback> createdCallbacks_;
    std::list<ReleasedCallback> releasedCallbacks_;
    EventCallback onPageStarted_;
    EventCallback onPageFinished_;
    EventCallback onPageError_;
    EventCallback onMessage_;
    Method reloadMethod_;
    Method updateUrlMethod_;
    Method routerBackMethod_;
    Method changePageUrlMethod_;
    Method isPagePathInvalidMethod_;
    State state_ { State::WAITINGFORSIZE };
#ifdef OHOS_STANDARD_SYSTEM
    std::shared_ptr<OHOS::NWeb::NWeb> nweb_;
    OHOS::NWeb::NWebCookieManager* cookieManager_ = nullptr;
    sptr<Rosen::Window> window_;
    bool isCreateWebView_ = false;

    EventCallbackV2 onPageFinishedV2_;
    EventCallbackV2 onPageStartedV2_;
    EventCallbackV2 onProgressChangeV2_;
    EventCallbackV2 onTitleReceiveV2_;
    EventCallbackV2 onGeolocationHideV2_;
    EventCallbackV2 onGeolocationShowV2_;
    EventCallbackV2 onRequestFocusV2_;
    EventCallbackV2 onErrorReceiveV2_;
    EventCallbackV2 onHttpErrorReceiveV2_;
    EventCallbackV2 onDownloadStartV2_;
    EventCallbackV2 onRefreshAccessedHistoryV2_;
    EventCallbackV2 onRenderExitedV2_;
    EventCallbackV2 onResourceLoadV2_;
    EventCallbackV2 onScaleChangeV2_;
    EventCallbackV2 onScrollV2_;
    EventCallbackV2 onPermissionRequestV2_;
    EventCallbackV2 onSearchResultReceiveV2_;

    std::string bundlePath_;
    std::string bundleDataPath_;
    RefPtr<PixelMap> pixelMap_ = nullptr;
    bool isRefreshPixelMap_ = false;
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H
