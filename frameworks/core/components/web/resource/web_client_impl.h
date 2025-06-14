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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEBVIEW_CLIENT_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEBVIEW_CLIENT_IMPL_H

#include "foundation/arkui/ace_engine/frameworks/base/memory/referenced.h"
#include "nweb_drag_data.h"
#include "nweb_handler.h"

#include "base/log/log.h"
#include "core/common/container_scope.h"
#include "surface_delegate.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "surface.h"
#endif

namespace OHOS::Ace {
class WebDelegate;

class DownloadListenerImpl : public OHOS::NWeb::NWebDownloadCallback {
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

class ReleaseSurfaceImpl : public OHOS::NWeb::NWebReleaseSurfaceCallback {
public:
    ReleaseSurfaceImpl() = default;
    ~ReleaseSurfaceImpl() = default;

    void ReleaseSurface() override;

    void SetSurfaceDelegate(const sptr<OHOS::SurfaceDelegate> &surfaceDelegate)
    {
        surfaceDelegate_ = surfaceDelegate;
    }

    void SetWebDelegate(const WeakPtr<WebDelegate>& delegate)
    {
        webDelegate_ = delegate;
    }

private:
    sptr<OHOS::SurfaceDelegate> surfaceDelegate_ = nullptr;
    WeakPtr<WebDelegate> webDelegate_;
};
class FindListenerImpl : public OHOS::NWeb::NWebFindCallback {
public:
    FindListenerImpl() = default;
    ~FindListenerImpl() = default;

    void OnFindResultReceived(
        const int activeMatchOrdinal, const int numberOfMatches, const bool isDoneCounting) override;

    void SetWebDelegate(const WeakPtr<WebDelegate>& delegate)
    {
        webDelegate_ = delegate;
    }

private:
    WeakPtr<WebDelegate> webDelegate_;
};

class SpanstringConvertHtmlImpl : public OHOS::NWeb::NWebSpanstringConvertHtmlCallback {
public:
    SpanstringConvertHtmlImpl() = default;
    explicit SpanstringConvertHtmlImpl(int32_t instanceId) : instanceId_(instanceId) {}
    ~SpanstringConvertHtmlImpl() = default;

    virtual std::string SpanstringConvertHtml(const std::vector<uint8_t> &content) override;

    void SetWebDelegate(const WeakPtr<WebDelegate>& delegate)
    {
        webDelegate_ = delegate;
    }

private:
    WeakPtr<WebDelegate> webDelegate_;
    int32_t instanceId_ = -1;
};

class WebClientImpl :
    public std::enable_shared_from_this<WebClientImpl>,
    public OHOS::NWeb::NWebHandler {
public:
    WebClientImpl() = default;
    ~WebClientImpl() = default;

    void SetNWeb(std::shared_ptr<OHOS::NWeb::NWeb> nweb) override;
    void OnProxyDied() override;
    void OnRouterPush(const std::string& param) override;
    bool OnConsoleLog(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message) override;
    void OnMessage(const std::string& param) override;
    void OnPageLoadBegin(const std::string& url) override;
    void OnPageLoadEnd(int httpStatusCode, const std::string& url) override;
    void OnLoadingProgress(int newProgress) override;
    void OnPageTitle(const std::string &title) override;
    void OnGeolocationHide() override;
    void OnFullScreenExit() override;
    void OnFullScreenEnter(std::shared_ptr<NWeb::NWebFullScreenExitHandler> handler) override;
    void OnFullScreenEnterWithVideoSize(std::shared_ptr<NWeb::NWebFullScreenExitHandler> handler,
        int videoNaturalWidth, int videoNaturalHeight) override;
    void OnGeolocationShow(const std::string& origin,
        std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface> callback) override;

    bool OnAlertDialogByJS(const std::string &url,
                           const std::string &message,
                           std::shared_ptr<NWeb::NWebJSDialogResult> result) override;
    bool OnBeforeUnloadByJS(const std::string &url,
                            const std::string &message,
                            std::shared_ptr<NWeb::NWebJSDialogResult> result) override;
    bool OnConfirmDialogByJS(const std::string &url,
                             const std::string &message,
                             std::shared_ptr<NWeb::NWebJSDialogResult> result) override;
    bool OnPromptDialogByJS(const std::string &url,
                             const std::string &message,
                             const std::string &defaultValue,
                             std::shared_ptr<NWeb::NWebJSDialogResult> result) override;
    bool OnFileSelectorShow(std::shared_ptr<NWeb::NWebStringVectorValueCallback> callback,
                            std::shared_ptr<NWeb::NWebFileSelectorParams> params) override;

    bool OnFocus() override;
    bool OnFocus(OHOS::NWeb::NWebFocusSource source) override;
    void OnResourceLoadError(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
        std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error) override;
    void ReportDynamicFrameLossEvent(const std::string& sceneId, bool isStart) override;
    void OnHttpError(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
        std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response) override;
    void OnRenderExited(OHOS::NWeb::RenderExitReason reason) override;
    void OnRefreshAccessedHistory(const std::string& url, bool isReload) override;
    bool OnHandleInterceptRequest(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
                                  std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response) override;
    bool OnHandleInterceptUrlLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request) override;
    void OnResource(const std::string& url) override;
    void OnScaleChanged(float oldScaleFactor, float newScaleFactor) override;
    void OnScroll(double xOffset, double yOffset) override;
    bool OnHttpAuthRequestByJS(std::shared_ptr<NWeb::NWebJSHttpAuthResult> result, const std::string &host,
        const std::string &realm) override;
    bool OnSslErrorRequestByJS(std::shared_ptr<NWeb::NWebJSSslErrorResult> result,
        OHOS::NWeb::SslError error) override;
    bool OnAllSslErrorRequestByJS(std::shared_ptr<NWeb::NWebJSAllSslErrorResult> result,
        OHOS::NWeb::SslError error,
        const std::string& url,
        const std::string& originalUrl,
        const std::string& referrer,
        bool isFatalError,
        bool isMainFrame) override;
    bool OnSslSelectCertRequestByJS(
        std::shared_ptr<NWeb::NWebJSSslSelectCertResult> result,
        const std::string& host,
        int32_t port,
        const std::vector<std::string>& keyTypes,
        const std::vector<std::string>& issuers) override;
    void OnPermissionRequest(std::shared_ptr<NWeb::NWebAccessRequest> request) override;
    bool RunContextMenu(std::shared_ptr<NWeb::NWebContextMenuParams> params,
        std::shared_ptr<NWeb::NWebContextMenuCallback> callback) override;
    void UpdateClippedSelectionBounds(int x, int y, int w, int h) override;
    bool RunQuickMenu(std::shared_ptr<NWeb::NWebQuickMenuParams> params,
                      std::shared_ptr<NWeb::NWebQuickMenuCallback> callback) override;
    void OnQuickMenuDismissed() override;
    void HideHandleAndQuickMenuIfNecessary(bool hide) override;
    void ChangeVisibilityOfQuickMenu() override;
    bool ChangeVisibilityOfQuickMenuV2() override;
    void OnTouchSelectionChanged(
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
        std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle) override;
    bool OnDragAndDropData(const void* data, size_t len, std::shared_ptr<NWeb::NWebImageOptions> opt) override;
    bool OnDragAndDropDataUdmf(std::shared_ptr<NWeb::NWebDragData> dragData) override;
    void UpdateDragCursor(NWeb::NWebDragData::DragOperation op) override;
    void OnWindowNewByJS(
        const std::string& targetUrl,
        bool isAlert,
        bool isUserTrigger,
        std::shared_ptr<NWeb::NWebControllerHandler> handler) override;
    void OnActivateContentByJS() override;
    void OnWindowExitByJS() override;
    void OnPageVisible(const std::string& url) override;
    void OnDataResubmission(std::shared_ptr<NWeb::NWebDataResubmissionCallback> handler) override;
    void OnNavigationEntryCommitted(std::shared_ptr<NWeb::NWebLoadCommittedDetails> details) override;
    void OnPageIcon(
        const void* data,
        size_t width,
        size_t height,
        NWeb::ImageColorType colorType,
        NWeb::ImageAlphaType alphaType) override;
    void OnDesktopIconUrl(const std::string& icon_url, bool precomposed) override;
    bool OnCursorChange(const NWeb::CursorType& type, std::shared_ptr<NWeb::NWebCursorInfo> info) override;
    void OnSelectPopupMenu(std::shared_ptr<NWeb::NWebSelectPopupMenuParam> params,
                           std::shared_ptr<NWeb::NWebSelectPopupMenuCallback> callback) override;
    void OnAudioStateChanged(bool playing) override;
    void OnFirstContentfulPaint(int64_t navigationStartTick, int64_t firstContentfulPaintMs) override;
    void OnFirstMeaningfulPaint(std::shared_ptr<NWeb::NWebFirstMeaningfulPaintDetails> details) override;
    void OnLargestContentfulPaint(std::shared_ptr<NWeb::NWebLargestContentfulPaintDetails> details) override;
    void OnSafeBrowsingCheckResult(int threat_type) override;
    void OnCompleteSwapWithNewSize() override;
    void OnResizeNotWork() override;
    void OnGetTouchHandleHotZone(std::shared_ptr<NWeb::NWebTouchHandleHotZone> hotZone) override;
    void OnDateTimeChooserPopup(
        std::shared_ptr<NWeb::NWebDateTimeChooser> chooser,
        const std::vector<std::shared_ptr<NWeb::NWebDateTimeSuggestion>>& suggestions,
        std::shared_ptr<NWeb::NWebDateTimeChooserCallback> callback) override;
    void OnDateTimeChooserClose() override;
    void OnOverScroll(float xOffset, float yOffset) override;
    void OnScreenCaptureRequest(std::shared_ptr<NWeb::NWebScreenCaptureAccessRequest> request) override;
    void OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling) override;
    void OnOverScrollFlingEnd() override;
    void OnScrollState(bool scrollState) override;
    void EnableSecurityLayer(bool isNeedSecurityLayer) override;
    void OnRootLayerChanged(int width, int height) override;
    void ReleaseResizeHold() override;
    bool FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity) override;
    void OnNativeEmbedLifecycleChange(std::shared_ptr<NWeb::NWebNativeEmbedDataInfo> dataInfo) override;
    void OnNativeEmbedGestureEvent(std::shared_ptr<NWeb::NWebNativeEmbedTouchEvent> event) override;
    void OnIntelligentTrackingPreventionResult(
        const std::string& websiteHost, const std::string& trackerHost) override;
    void OnTooltip(const std::string& tooltip) override;
    void OnPopupSize(int x, int y, int width, int height) override;
    void OnPopupShow(bool show) override;
    bool OnHandleOverrideUrlLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request) override;
    bool OnOpenAppLink(const std::string& url,
                       std::shared_ptr<OHOS::NWeb::NWebAppLinkCallback> callback) override;
    void OnShowAutofillPopup(
        const float offsetX, const float offsetY, const std::vector<std::string>& menu_items) override;
    void OnShowAutofillPopupV2(
        const float offsetX, const float offsetY, const float height, const float width,
        const std::vector<std::string>& menu_items) override;
    void OnHideAutofillPopup() override;
    void OnAdsBlocked(const std::string& url, const std::vector<std::string>& adsBlocked) override;

    void SetWebDelegate(const WeakPtr<WebDelegate>& delegate)
    {
        webDelegate_ = delegate;
    }

    const RefPtr<WebDelegate> GetWebDelegate() const
    {
        return webDelegate_.Upgrade();
    }

    std::vector<int8_t> GetWordSelection(const std::string& text, int8_t offset) override;
    void OnRenderProcessNotResponding(
        const std::string& jsStack, int pid, OHOS::NWeb::RenderProcessNotRespondingReason reason) override;
    void OnRenderProcessResponding() override;

    void OnViewportFitChange(NWeb::ViewportFit viewportFit) override;

    void CreateOverlay(void* data, size_t len, int width, int height, int offsetX, int offsetY, int rectWidth,
        int rectHeight, int pointX, int pointY) override;

    void OnOverlayStateChanged(int offsetX, int offsetY, int rectWidth, int rectHeight) override;

    void OnInterceptKeyboardAttach(
        const std::shared_ptr<OHOS::NWeb::NWebCustomKeyboardHandler> keyboardHandler,
        const std::map<std::string, std::string> &attributes, bool &useSystemKeyboard, int32_t &enterKeyType) override;

    void OnCustomKeyboardAttach() override;

    void OnCustomKeyboardClose() override;

    void KeyboardReDispatch(std::shared_ptr<OHOS::NWeb::NWebKeyEvent> event, bool isUsed) override;

    void OnCursorUpdate(double x, double y, double width, double height) override;

    void StartVibraFeedback(const std::string& vibratorType) override;

    void OnNativeEmbedVisibilityChange(const std::string& embedId, bool visibility) override;

    bool CloseImageOverlaySelection() override;
    
    bool OnSslErrorRequestByJSV2(std::shared_ptr<NWeb::NWebJSSslErrorResult> result,
        OHOS::NWeb::SslError error, const std::vector<std::string>& certChainData) override;

    void OnAccessibilityEventV2(int64_t accessibilityId, int32_t eventType, const std::string& argument) override;

    bool IsCurrentFocus() override;

    void GetVisibleRectToWeb(int& visibleX, int& visibleY, int& visibleWidth, int& visibleHeight) override;

    void OnScrollStart(const float x, const float y) override;

    void RestoreRenderFit() override;

    bool OnNestedScroll(float& x, float& y, float& xVelocity, float& yVelocity, bool& isAvailable) override;

    void OnPip(int status, int delegate_id, int child_id, int frame_routing_id, int width, int height) override;

    bool OnAllSslErrorRequestByJSV2(std::shared_ptr<NWeb::NWebJSAllSslErrorResult> result, OHOS::NWeb::SslError error,
        const std::string& url, const std::string& originalUrl, const std::string& referrer, bool isFatalError,
        bool isMainFrame, const std::vector<std::string>& certChainData) override;
private:
    std::weak_ptr<OHOS::NWeb::NWeb> webviewWeak_;
    WeakPtr<WebDelegate> webDelegate_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEBVIEW_CLIENT_IMPL_H
