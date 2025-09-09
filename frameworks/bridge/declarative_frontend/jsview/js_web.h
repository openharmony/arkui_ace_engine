/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WEB_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WEB_H

#include <string>

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components/web/web_component.h"
#include "frameworks/base/image/pixel_map.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "core/event/mouse_event.h"

namespace OHOS::Ace::Framework {
using JSwebEventCallback = std::function<void()>;
class JSWeb : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void OnAlert(const JSCallbackInfo& args);
    static void OnBeforeUnload(const JSCallbackInfo& args);
    static void OnConfirm(const JSCallbackInfo& args);
    static void OnFullScreenEnter(const JSCallbackInfo& args);
    static void OnFullScreenExit(const JSCallbackInfo& args);
    static void OnPrompt(const JSCallbackInfo& args);
    static void OnConsoleLog(const JSCallbackInfo& args);
    static void OnPageStart(const JSCallbackInfo& args);
    static void OnPageFinish(const JSCallbackInfo& args);
    static void OnProgressChange(const JSCallbackInfo& args);
    static void OnTitleReceive(const JSCallbackInfo& args);
    static void OnGeolocationHide(const JSCallbackInfo& args);
    static void OnGeolocationShow(const JSCallbackInfo& args);
    static void OnRequestFocus(const JSCallbackInfo& args);
    static void OnError(const JSCallbackInfo& args);
    static void OnMessage(const JSCallbackInfo& args);
    static void OnDownloadStart(const JSCallbackInfo& args);
    static void OnErrorReceive(const JSCallbackInfo& args);
    static void OnHttpErrorReceive(const JSCallbackInfo& args);
    static void OnFileSelectorShow(const JSCallbackInfo& args);
    static void OnInterceptRequest(const JSCallbackInfo& args);
    static void OnOverrideErrorPage(const JSCallbackInfo& args);
    static void OnUrlLoadIntercept(const JSCallbackInfo& args);
    static void OnLoadIntercept(const JSCallbackInfo& args);
    static void JsEnabled(bool isJsEnabled);
    static void ContentAccessEnabled(bool isContentAccessEnabled);
    static void FileAccessEnabled(bool isFileAccessEnabled);
    static void OnFocus(const JSCallbackInfo& args);
    static void OnLineImageAccessEnabled(bool isOnLineImageAccessEnabled);
    static void DomStorageAccessEnabled(bool isDomStorageAccessEnabled);
    static void ImageAccessEnabled(bool isImageAccessEnabled);
    static void MixedMode(int32_t MixedModeNum);
    static void ZoomAccessEnabled(bool isZoomAccessEnabled);
    static void GeolocationAccessEnabled(bool isGeolocationAccessEnabled);
    static void JavaScriptProxy(const JSCallbackInfo& args);
    static void UserAgent(const std::string& userAgent);
    static void OnRenderExited(const JSCallbackInfo& args);
    static void OnRefreshAccessedHistory(const JSCallbackInfo& args);
    static void CacheMode(int32_t cacheMode);
    static void OverviewModeAccess(bool isOverviewModeAccessEnabled);
    static void WebDebuggingAccess(const JSCallbackInfo& args);
    static void WideViewModeAccess(const JSCallbackInfo& args);
    static void FileFromUrlAccess(bool isFileFromUrlAccessEnabled);
    static void DatabaseAccess(bool isDatabaseAccessEnabled);
    static void TextZoomRatio(int32_t textZoomRatioNum);
    static void WebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled);
    static void OnMouse(const JSCallbackInfo& args);
    static void OnResourceLoad(const JSCallbackInfo& args);
    static void OnScaleChange(const JSCallbackInfo& args);
    static void OnScroll(const JSCallbackInfo& args);
    static void WebRotate(const JSCallbackInfo& args);
    static void BackgroundColor(const JSCallbackInfo& info);
    static void InitialScale(float scale);
    static void Password(bool password);
    static void TableData(bool tableData);
    static void OnFileSelectorShowAbandoned(const JSCallbackInfo& args);
    static void OnHttpAuthRequest(const JSCallbackInfo& args);
    static void OnSslErrRequest(const JSCallbackInfo& args);
    static void OnSslErrorRequest(const JSCallbackInfo& args);
    static void OnAllSslErrorRequest(const JSCallbackInfo& args);
    static void OnSslSelectCertRequest(const JSCallbackInfo& args);
    static void OnPermissionRequest(const JSCallbackInfo& args);
    static void OnScreenCaptureRequest(const JSCallbackInfo& args);
    static void BindSelectionMenu(const JSCallbackInfo& info);
    static void OnContextMenuHide(const JSCallbackInfo& args);
    static void OnContextMenuShow(const JSCallbackInfo& args);
    static void OnSearchResultReceive(const JSCallbackInfo& args);
    static void MediaPlayGestureAccess(bool isNeedGestureAccess);
    static void OnKeyEvent(const JSCallbackInfo& args);
    static void JsOnDragStart(const JSCallbackInfo& info);
    static void JsOnDragEnter(const JSCallbackInfo& info);
    static void JsOnDragMove(const JSCallbackInfo& info);
    static void JsOnDragLeave(const JSCallbackInfo& info);
    static void JsOnDrop(const JSCallbackInfo& info);
    static void PinchSmoothModeEnabled(bool isPinchSmoothModeEnabled);
    static void OnWindowNew(const JSCallbackInfo& args);
    static void OnActivateContent(const JSCallbackInfo& args);
    static void OnWindowExit(const JSCallbackInfo& args);
    static void MultiWindowAccessEnabled(bool isMultiWindowAccessEnable);
    static void AllowWindowOpenMethod(bool isAllowWindowOpenMethod);
    static void WebCursiveFont(const std::string& cursiveFontFamily);
    static void WebFantasyFont(const std::string& fantasyFontFamily);
    static void WebFixedFont(const std::string& fixedFontFamily);
    static void WebSansSerifFont(const std::string& sansSerifFontFamily);
    static void WebSerifFont(const std::string& serifFontFamily);
    static void WebStandardFont(const std::string& standardFontFamily);
    static void DefaultFixedFontSize(int32_t defaultFixedFontSize);
    static void DefaultFontSize(int32_t defaultFontSize);
    static void DefaultTextEncodingFormat(const JSCallbackInfo& args);
    static void MinFontSize(int32_t minFontSize);
    static void MinLogicalFontSize(int32_t minLogicalFontSize);
    static void BlockNetwork(bool isNetworkBlocked);
    static void OnPageVisible(const JSCallbackInfo& args);
    static void OnInterceptKeyEvent(const JSCallbackInfo& args);
    static void OnDataResubmitted(const JSCallbackInfo& args);
    static void OnFaviconReceived(const JSCallbackInfo& args);
    static void OnTouchIconUrlReceived(const JSCallbackInfo& args);
    static void DarkMode(int32_t darkMode);
    static void ForceDarkAccess(bool access);
    static void HorizontalScrollBarAccess(bool isHorizontalScrollBarAccessEnabled);
    static void VerticalScrollBarAccess(bool isVerticalScrollBarAccessEnabled);
    static void OnAudioStateChanged(const JSCallbackInfo& args);
    static void MediaOptions(const JSCallbackInfo& args);
    static void OnFirstContentfulPaint(const JSCallbackInfo& args);
    static void OnFirstMeaningfulPaint(const JSCallbackInfo& args);
    static void OnLargestContentfulPaint(const JSCallbackInfo& args);
    static void OnSafeBrowsingCheckResult(const JSCallbackInfo& args);
    static void OnNavigationEntryCommitted(const JSCallbackInfo& args);
    static void OnIntelligentTrackingPreventionResult(const JSCallbackInfo& args);
    static void OnControllerAttached(const JSCallbackInfo& args);
    static void OnOverScroll(const JSCallbackInfo& args);
    static void SetLayoutMode(int32_t layoutMode);
    static void SetNestedScroll(const JSCallbackInfo& info);
    static void SetMetaViewport(const JSCallbackInfo& args);
    static void OverScrollMode(int overScrollMode);
    static void BlurOnKeyboardHideMode(int blurOnKeyboardHideMode);
    static void EnableNativeEmbedMode(bool isEmbedModeEnabled);
    static void NativeEmbedOptions(const JSCallbackInfo& args);
    static void RegisterNativeEmbedRule(const std::string& tag, const std::string& type);
    static void OnNativeEmbedLifecycleChange(const JSCallbackInfo& args);
    static void OnNativeEmbedVisibilityChange(const JSCallbackInfo& args);
    static void OnNativeEmbedGestureEvent(const JSCallbackInfo& args);
    static void OnNativeEmbedMouseEvent(const JSCallbackInfo& args);
    static void OnNativeEmbedObjectParamChange(const JSCallbackInfo& args);
    static void JavaScriptOnDocumentStart(const JSCallbackInfo& args);
    static void JavaScriptOnDocumentEnd(const JSCallbackInfo& args);
    static void OptimizeParserBudgetEnabled(bool enable);
    static void BypassVsyncCondition(int32_t webBypassVsyncCondition);
    static void RunJavaScriptOnDocumentStart(const JSCallbackInfo& args);
    static void RunJavaScriptOnDocumentEnd(const JSCallbackInfo& args);
    static void RunJavaScriptOnHeadEnd(const JSCallbackInfo& args);
    static void SetCallbackFromController(const JSRef<JSObject> controller);
    static void SetForceEnableZoom(const JSCallbackInfo& args);
    static JSRef<JSVal> CreateJSWindowNewHandler(const WebWindowNewEvent& eventInfo);
    static bool HandleWindowNewEvent(const WebWindowNewEvent* eventInfo);
    static JSRef<JSVal> CreateScreenCaptureHandler(const WebScreenCaptureRequestEvent& eventInfo);
    static JSRef<JSVal> CreatePermissionRequestHandler(const WebPermissionRequestEvent& eventInfo);
    static JSRef<JSVal> CreateGeolocationShowHandler(const LoadWebGeolocationShowEvent& eventInfo);
    static JSRef<JSVal> CreateNativeEmbedGestureHandler(const NativeEmbeadTouchInfo& eventInfo);
    static JSRef<JSVal> CreateFullScreenEnterHandler(const FullScreenEnterEvent& eventInfo);
    static JSRef<JSVal> CreateCommonDialogResultHandler(const WebDialogEvent& eventInfo);
    static JSRef<JSVal> CreateFileSelectorResultHandler(const FileSelectorEvent& eventInfo);
    static JSRef<JSVal> CreateFileSelectorParamHandler(const FileSelectorEvent& eventInfo);
    static JSRef<JSVal> CreateContextMenuParamHandler(const ContextMenuEvent& eventInfo);
    static JSRef<JSVal> CreateContextMenuResultHandler(const ContextMenuEvent& eventInfo);
    static JSRef<JSVal> CreateRequestErrorHandler(const ReceivedErrorEvent& eventInfo);
    static JSRef<JSVal> CreateResponseErrorHandler(const ReceivedErrorEvent& eventInfo);
    static JSRef<JSVal> CreateLoadInterceptHandler(const LoadInterceptEvent& eventInfo);
    static JSRef<JSVal> CreateHttpErrorReceiveRequestHandler(const ReceivedHttpErrorEvent& eventInfo);
    static JSRef<JSVal> CreateHttpErrorReceiveResponseHandler(const ReceivedHttpErrorEvent& eventInfo);
    static JSRef<JSVal> CreateOverrideUrlLoadingHandler(const LoadOverrideEvent& eventInfo);
    static JSRef<JSVal> CreateHttpAuthRequestHandler(const WebHttpAuthEvent& eventInfo);
    static JSRef<JSVal> CreateConsoleHandler(const LoadWebConsoleLogEvent& eventInfo);
    static JSRef<JSVal> CreateSslErrorEventHandler(const WebAllSslErrorEvent& eventInfo);
    static JSRef<JSVal> CreateDataResubmittedHandler(const DataResubmittedEvent& eventInfo);
    static JSRef<JSVal> CreateClientAuthenticationRequestHandler(const WebSslSelectCertEvent& eventInfo);
    static JSRef<JSVal> CreateSslErrorEventReceiveHandler(const WebSslErrorEvent& eventInfo);
    static JSRef<JSVal> CreateInterceptRequestHandler(const OnInterceptRequestEvent& eventInfo);
    static JSRef<JSVal> CreateFaviconReceivedHandler(const FaviconReceivedEvent& eventInfo);
    static uint32_t GetBytesPerPixel(OHOS::Ace::PixelFormat format);

    // Enable or disable debugging of web content
    static bool webDebuggingAccess_;
    static int32_t webDebuggingPort_;
    static JSwebEventCallback OnControllerAttachedCallback_;
    static void CopyOption(int32_t copyOption);
    static void OnOverrideUrlLoading(const JSCallbackInfo& args);
    static void TextAutosizing(const JSCallbackInfo& args);
    static void EnableNativeVideoPlayer(const JSCallbackInfo& args);
    static void OnRenderProcessNotResponding(const JSCallbackInfo& args);
    static void OnRenderProcessResponding(const JSCallbackInfo& args);
    static void SelectionMenuOptions(const JSCallbackInfo& args);
    static void OnViewportFitChanged(const JSCallbackInfo& args);
    static void OnInterceptKeyboardAttach(const JSCallbackInfo& args);
    static void OnAdsBlocked(const JSCallbackInfo& args);
    static void ForceDisplayScrollBar(const JSCallbackInfo& args);
    static void KeyboardAvoidMode(int32_t mode);
    static void EditMenuOptions(const JSCallbackInfo& info);
    static void EnableHapticFeedback(const JSCallbackInfo& args);
    static void EnableWebAVSession(const JSCallbackInfo& args);
    static void EnableDataDetector(const JSCallbackInfo& args);
    static void DataDetectorConfig(const JSCallbackInfo& args);
    static void EnableFollowSystemFontWeight(bool enableFollowSystemFontWeight);
    static void OnLoadStarted(const JSCallbackInfo& args);
    static void OnLoadFinished(const JSCallbackInfo& args);
    static void GestureFocusMode(int32_t gestureFocusMode);
    static void OnPdfScrollAtBottom(const JSCallbackInfo& args);
    static void OnPdfLoadEvent(const JSCallbackInfo& args);
    static void OnSafeBrowsingCheckFinish(const JSCallbackInfo& args);

protected:
    static void OnCommonDialog(const JSCallbackInfo& args, int dialogEventType);
    static void ParseRawfileWebSrc(const JSRef<JSVal>& srcValue, std::string& webSrc);
    static void ParseJsCustomKeyboardOption(const JsiExecutionContext& context,
        const JSRef<JSVal>& keyboardOpt, WebKeyboardOption& keyboardOption);

private:
    static void ParseScriptItems(const JSCallbackInfo& args, ScriptItems& scriptItems,
        ScriptItemsByOrder& scriptItemsByOrder);
    static bool CheckNestedScrollMode(const int32_t& modeValue);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WEB_H
