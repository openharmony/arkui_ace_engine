/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

#include "mock_web_delegate.h"

#include <gmock/gmock.h>
#include <vector>

#include "core/components/web/resource/web_delegate.h"

namespace OHOS::Ace {
#define EGLCONFIG_VERSION 3
static std::string g_setReturnStatus = "";
const std::string STATUS_TRUE = "true";
static std::string g_setComponentType = "";
const std::string STATUS_FALSE = "false";
std::map<std::string, std::string> htmlElementToSurfaceMap = { { "existhtmlElementId", "existSurfaceId" },
    { "existhtmlElementIdOther", "existSurfaceIdOther" } };
std::map<std::string, std::string> surfaceToHtmlElementMap = { { "existSurfaceId", "existhtmlElementId" },
    { "existSurfaceIdOther", "existhtmlElementIdOther" } };
std::map<std::string, int64_t> surfaceToWebAccessibilityMap = { { "existSurfaceId", 123 },
    { "existSurfaceIdOther", 456 } };
class MockNWebAccessibilityNodeInfoOnlyForReturn : public NWeb::NWebAccessibilityNodeInfo {
public:
    std::string GetHint() override
    {
        return "";
    }
    std::string GetError() override
    {
        return "";
    }
    int32_t GetRectX()
    {
        return 0;
    }
    int32_t GetRectY()
    {
        return 0;
    }
    void SetPageId(int32_t pageId) override {}
    int32_t GetPageId() override
    {
        return 0;
    }
    std::vector<uint32_t> GetActions() override
    {
        return {};
    }
    std::string GetContent() override
    {
        return "";
    }
    std::vector<int64_t> GetChildIds() override
    {
        if (g_setReturnStatus == STATUS_TRUE) {
            return { 1 };
        }
        return {};
    }
    void SetParentId(int64_t parentId) override {}
    int64_t GetParentId() override
    {
        return 0;
    }
    bool GetIsHeading() override
    {
        return false;
    }
    bool GetIsChecked() override
    {
        return false;
    }
    bool GetIsEnabled() override
    {
        return false;
    }
    bool GetIsFocused() override
    {
        return false;
    }
    int32_t GetRectWidth()
    {
        return 0;
    }
    int32_t GetRectHeight()
    {
        return 0;
    }
    bool GetIsVisible() override
    {
        return false;
    }
    bool GetIsHinting() override
    {
        return false;
    }
    bool GetIsEditable() override
    {
        return false;
    }
    bool GetIsSelected() override
    {
        return false;
    }
    size_t GetItemCounts() override
    {
        return 0;
    }
    int32_t GetLiveRegion() override
    {
        return 0;
    }
    bool GetIsPassword() override
    {
        return false;
    }
    bool GetIsCheckable() override
    {
        return false;
    }
    bool GetIsClickable() override
    {
        return false;
    }
    bool GetIsFocusable() override
    {
        return false;
    }
    bool GetIsScrollable() override
    {
        return false;
    }
    bool GetIsDeletable() override
    {
        return false;
    }
    int64_t GetAccessibilityId() override
    {
        return 0;
    }
    bool GetIsPopupSupported() override
    {
        return false;
    }
    bool GetIsContentInvalid() override
    {
        return false;
    }
    int32_t GetSelectionEnd() override
    {
        return 0;
    }
    int32_t GetSelectionStart() override
    {
        return 0;
    }
    float GetRangeInfoMin() override
    {
        return 0.0f;
    }
    float GetRangeInfoMax() override
    {
        return 0.0f;
    }
    float GetRangeInfoCurrent() override
    {
        return 0.0f;
    }
    int32_t GetInputType() override
    {
        return 0;
    }
    std::string GetComponentType() override
    {
        g_setReturnStatus = STATUS_FALSE;
        return g_setComponentType;
    }
    std::string GetDescriptionInfo() override
    {
        return "";
    }
    int32_t GetGridRows() override
    {
        return 0;
    }
    int32_t GetGridItemRow() override
    {
        return 0;
    }
    int32_t GetGridColumns() override
    {
        return 0;
    }
    int32_t GetGridItemColumn() override
    {
        return 0;
    }
    int32_t GetGridItemRowSpan() override
    {
        return 0;
    }
    int32_t GetGridSelectedMode() override
    {
        return 0;
    }
    int32_t GetGridItemColumnSpan() override
    {
        return 0;
    }
    bool GetIsAccessibilityFocus() override
    {
        return false;
    }
    bool GetIsPluralLineSupported() override
    {
        return false;
    }
};
void WebMessagePortOhos::SetPortHandle(std::string& handle) {}
std::string WebMessagePortOhos::GetPortHandle()
{
    return "";
}
void WebMessagePortOhos::Close() {}
void WebMessagePortOhos::PostMessage(std::string& data) {}
void WebMessagePortOhos::SetWebMessageCallback(std::function<void(const std::string&)>&& callback) {}
int ConsoleLogOhos::GetLineNumber()
{
    return false;
}
std::string ConsoleLogOhos::GetLog()
{
    return "";
}
int ConsoleLogOhos::GetLogLevel()
{
    return false;
}
std::string ConsoleLogOhos::GetSourceId()
{
    return "";
}
void ResultOhos::Confirm() {}
void ResultOhos::Confirm(const std::string& message) {}
void ResultOhos::Cancel() {}
void FullScreenExitHandlerOhos::ExitFullScreen() {}
bool AuthResultOhos::Confirm(std::string& userName, std::string& pwd)
{
    return false;
}
bool AuthResultOhos::IsHttpAuthInfoSaved()
{
    return false;
}
void AuthResultOhos::Cancel() {}
void SslErrorResultOhos::HandleConfirm() {}
void SslErrorResultOhos::HandleCancel() {}
void AllSslErrorResultOhos::HandleConfirm() {}
void AllSslErrorResultOhos::HandleCancel(bool abortLoading) {}
void SslSelectCertResultOhos::HandleConfirm(const std::string& privateKeyFile, const std::string& certChainFile) {}
void SslSelectCertResultOhos::HandleCancel() {}
void SslSelectCertResultOhos::HandleIgnore() {}
std::string FileSelectorParamOhos::GetTitle()
{
    return "";
}
int FileSelectorParamOhos::GetMode()
{
    return false;
}
std::string FileSelectorParamOhos::GetDefaultFileName()
{
    return "";
}
std::vector<std::string> FileSelectorParamOhos::GetAcceptType()
{
    return {};
}
bool FileSelectorParamOhos::IsCapture()
{
    return false;
}
void FileSelectorResultOhos::HandleFileList(std::vector<std::string>& result) {}
void WebPermissionRequestOhos::Deny() const {}
std::string WebPermissionRequestOhos::GetOrigin() const
{
    return "";
}
std::vector<std::string> WebPermissionRequestOhos::GetResources() const
{
    return {};
}
void WebPermissionRequestOhos::Grant(std::vector<std::string>& resources) const {}
void WebScreenCaptureRequestOhos::Deny() const {}
std::string WebScreenCaptureRequestOhos::GetOrigin() const
{
    return "";
}
void WebScreenCaptureRequestOhos::SetCaptureMode(int32_t mode) {}
void WebScreenCaptureRequestOhos::SetSourceId(int32_t sourceId) {}
void WebScreenCaptureRequestOhos::Grant() const {}
int32_t ContextMenuParamOhos::GetXCoord() const
{
    return false;
}
int32_t ContextMenuParamOhos::GetYCoord() const
{
    return false;
}
std::string ContextMenuParamOhos::GetLinkUrl() const
{
    return "";
}
std::string ContextMenuParamOhos::GetUnfilteredLinkUrl() const
{
    return "";
}
std::string ContextMenuParamOhos::GetSourceUrl() const
{
    return "";
}
bool ContextMenuParamOhos::HasImageContents() const
{
    return false;
}
bool ContextMenuParamOhos::IsEditable() const
{
    return false;
}
int ContextMenuParamOhos::GetEditStateFlags() const
{
    return false;
}
int ContextMenuParamOhos::GetSourceType() const
{
    return false;
}
int ContextMenuParamOhos::GetMediaType() const
{
    return false;
}
int ContextMenuParamOhos::GetInputFieldType() const
{
    return false;
}
std::string ContextMenuParamOhos::GetSelectionText() const
{
    return "";
}
void ContextMenuResultOhos::Cancel() const {}
void ContextMenuResultOhos::CopyImage() const {}
void ContextMenuResultOhos::Copy() const {}
void ContextMenuResultOhos::Paste() const {}
void ContextMenuResultOhos::Cut() const {}
void ContextMenuResultOhos::SelectAll() const {}
void WebWindowNewHandlerOhos::SetWebController(int32_t id) {}
bool WebWindowNewHandlerOhos::IsFrist() const
{
    return false;
}
int32_t WebWindowNewHandlerOhos::GetId() const
{
    return false;
}
int32_t WebWindowNewHandlerOhos::GetParentNWebId() const
{
    return false;
}
void DataResubmittedOhos::Resend() {}
void DataResubmittedOhos::Cancel() {}
const void* FaviconReceivedOhos::GetData()
{
    return nullptr;
}
size_t FaviconReceivedOhos::GetWidth()
{
    return 0;
}
size_t FaviconReceivedOhos::GetHeight()
{
    return 0;
}
int FaviconReceivedOhos::GetColorType()
{
    return false;
}
int FaviconReceivedOhos::GetAlphaType()
{
    return false;
}
NWebScreenLockCallbackImpl::NWebScreenLockCallbackImpl(const WeakPtr<PipelineBase>& context) : context_(context) {}
void NWebScreenLockCallbackImpl::Handle(bool key) {}
WebDelegateObserver::~WebDelegateObserver() {}
void WebDelegateObserver::NotifyDestory() {}
void WebDelegate::UnRegisterScreenLockFunction() {}
void WebDelegateObserver::OnAttachContext(const RefPtr<NG::PipelineContext>& context) {}
void WebDelegateObserver::OnDetachContext() {}
void GestureEventResultOhos::SetGestureEventResult(bool result) {}
void GestureEventResultOhos::SetGestureEventResult(bool result, bool stopPropagation) {}
void WebAvoidAreaChangedListener::OnAvoidAreaChanged(
    const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type,
    const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info) {}
WebDelegate::~WebDelegate() {}
void WebDelegate::ReleasePlatformResource() {}
void WebGeolocationOhos::Invoke(const std::string& origin, const bool& allow, const bool& retain) {}
void WebDelegate::Stop() {}
void WebDelegate::UnregisterEvent() {}
void WebDelegate::SetRenderWeb(const WeakPtr<RenderWeb>& renderWeb) {}
void WebDelegate::CreatePlatformResource(
    const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context)
{}
void WebDelegate::LoadUrl(const std::string& url, const std::map<std::string, std::string>& httpHeaders)
{
}
#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::Backward() {}
void WebDelegate::Forward() {}
void WebDelegate::ClearHistory() {}
void WebDelegate::ClearSslCache() {}
void WebDelegate::ClearClientAuthenticationCache() {}
bool WebDelegate::AccessStep(int32_t step)
{
    return false;
}
void WebDelegate::BackOrForward(int32_t step) {}
bool WebDelegate::AccessBackward()
{
    static bool temp = true;
    if (temp) {
        temp = false;
        return temp;
    }
    temp = true;
    return temp;
}
bool WebDelegate::AccessForward()
{
    return false;
}
#endif
void WebDelegate::ExecuteTypeScript(const std::string& jscode, const std::function<void(const std::string)>&& callback)
{}
void WebDelegate::LoadDataWithBaseUrl(const std::string& baseUrl, const std::string& data, const std::string& mimeType,
    const std::string& encoding, const std::string& historyUrl)
{}
bool WebDelegate::LoadDataWithRichText()
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::Refresh() {}
void WebDelegate::StopLoading() {}
void WebDelegate::AddJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList) {}
void WebDelegate::RemoveJavascriptInterface(const std::string& objectName, const std::vector<std::string>& methodList)
{}
void WebDelegate::SetWebViewJavaScriptResultCallBack(
    const WebController::JavaScriptCallBackImpl&& javaScriptCallBackImpl)
{}
void WebDelegate::CreateWebMessagePorts(std::vector<RefPtr<WebMessagePort>>& ports) {}
void WebDelegate::PostWebMessage(std::string& message, std::vector<RefPtr<WebMessagePort>>& ports, std::string& uri) {}
void WebDelegate::ClosePort(std::string& port) {}
void WebDelegate::PostPortMessage(std::string& port, std::string& data) {}
void WebDelegate::SetPortMessageCallback(std::string& port, std::function<void(const std::string&)>&& callback) {}
bool WebDelegate::RequestFocus(OHOS::NWeb::NWebFocusSource source)
{
    return false;
}
void WebDelegate::SearchAllAsync(const std::string& searchStr) {}
void WebDelegate::ClearMatches() {}
void WebDelegate::SearchNext(bool forward) {}
int WebDelegate::ConverToWebHitTestType(int hitType)
{
    return false;
}
int WebDelegate::GetLastHitTestResult()
{
    return 0;
}
int WebDelegate::GetHitTestResult()
{
    return false;
}
void WebDelegate::GetHitTestValue(HitTestResult& result) {}
int WebDelegate::GetProgress()
{
    return false;
}
int WebDelegate::GetPageHeight()
{
    return false;
}
int WebDelegate::GetWebId()
{
    return false;
}
std::string WebDelegate::GetTitle()
{
    return "";
}
std::string WebDelegate::GetDefaultUserAgent()
{
    return "";
}
bool WebDelegate::SaveCookieSync()
{
    return false;
}
bool WebDelegate::SetCookie(const std::string& url, const std::string& value, bool incognitoMode)
{
    return false;
}
std::string WebDelegate::GetCookie(const std::string& url, bool incognitoMode) const
{
    return "";
}
void WebDelegate::DeleteEntirelyCookie(bool incognitoMode) {}
void WebDelegate::CreatePluginResource(
    const Size& size, const Offset& position, const WeakPtr<PipelineContext>& context)
{}
void WebDelegate::InitWebEvent() {}
#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::ShowWebView() {}
void WebDelegate::HideWebView() {}
void WebDelegate::InitOHOSWeb(const RefPtr<PipelineBase>& context, const RefPtr<NG::RenderSurface>& surface)
{
#ifdef ENABLE_ROSEN_BACKEND
#ifndef ENABLE_ROSEN_BACKEND
#endif
#endif
}
bool WebDelegate::PrepareInitOHOSWeb(const WeakPtr<PipelineBase>& context)
{
    return false;
}
void WebSurfaceCallback::OnSurfaceCreated(const sptr<OHOS::Surface>& surface) {}
void WebSurfaceCallback::OnSurfaceChanged(const sptr<OHOS::Surface>& surface, int32_t width, int32_t height) {}
void WebSurfaceCallback::OnSurfaceDestroyed() {}
EGLConfig WebDelegate::GLGetConfig(int version, EGLDisplay eglDisplay)
{
    EGLConfig configs = NULL;
    return configs;
}
void WebDelegate::GLContextInit(void* window) {}
bool WebDelegate::InitWebSurfaceDelegate(const WeakPtr<PipelineBase>& context)
{
    return false;
}
void WebDelegate::InitOHOSWeb(const WeakPtr<PipelineBase>& context)
{
#ifdef ENABLE_ROSEN_BACKEND
#else
#endif
}
void WebDelegate::RegisterOHOSWebEventAndMethord() {}
void WebDelegate::NotifyPopupWindowResult(bool result) {}
void WebDelegate::RunSetWebIdAndHapPathCallback()
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::RunJsProxyCallback()
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::RegisterConfigObserver() {}
void WebDelegate::UnRegisterConfigObserver() {}
void WebDelegate::SetWebCallBack() {}
void WebDelegate::InitWebViewWithWindow() {}
void WebDelegate::UpdateSettting(bool useNewPipe)
{
#ifdef NG_BUILD
#else
#endif
}
std::string WebDelegate::GetCustomScheme()
{
    return "";
}
void WebDelegate::SurfaceOcclusionCallback(float visibleRatio) {}
void WebDelegate::ratioStrToFloat(const std::string& str) {}
void WebDelegate::ratioStrToFloatV2(const std::string& str) {}
void WebDelegate::RegisterSurfaceOcclusionChangeFun() {}
void WebDelegate::SetPartitionPoints(std::vector<float>& partition) {}
void WebDelegate::RegisterAvoidAreaChangeListener(int32_t) {}
class NWebAutoFillCallbackImpl : public OHOS::NWeb::NWebMessageValueCallback {
public:
    NWebAutoFillCallbackImpl(const WeakPtr<WebDelegate>& delegate) : delegate_(delegate) {}
    ~NWebAutoFillCallbackImpl() = default;

    void OnReceiveValue(std::shared_ptr<NWeb::NWebMessage> result) override
    {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "called");
        auto delegate = delegate_.Upgrade();
        CHECK_NULL_VOID(delegate);
        delegate->HandleAutoFillEvent(result);
    }

private:
    WeakPtr<WebDelegate> delegate_;
};
void WebDelegate::UnregisterAvoidAreaChangeListener(int32_t) {}
void WebDelegate::InitWebViewWithSurface()
{
#ifdef ENABLE_ROSEN_BACKEND
#endif
#ifdef OHOS_STANDARD_SYSTEM
#endif
}
void WebDelegate::SetKeepScreenOn(bool key) {}
void WebDelegate::UpdateUserAgent(const std::string& userAgent) {}
void WebDelegate::UpdateBackgroundColor(const int backgroundColor) {}
void WebDelegate::UpdateInitialScale(float scale) {}
void WebDelegate::Resize(const double& width, const double& height, bool isKeyboard) {}
void WebDelegate::UpdateJavaScriptEnabled(const bool& isJsEnabled) {}
void WebDelegate::UpdateAllowFileAccess(const bool& isFileAccessEnabled) {}
void WebDelegate::UpdateBlockNetworkImage(const bool& onLineImageAccessEnabled) {}
void WebDelegate::UpdateLoadsImagesAutomatically(const bool& isImageAccessEnabled) {}
void WebDelegate::UpdateMixedContentMode(const MixedModeContent& mixedMode) {}
void WebDelegate::UpdateSupportZoom(const bool& isZoomAccessEnabled) {}
void WebDelegate::UpdateDomStorageEnabled(const bool& isDomStorageAccessEnabled) {}
void WebDelegate::UpdateGeolocationEnabled(const bool& isGeolocationAccessEnabled) {}
void WebDelegate::UpdateCacheMode(const WebCacheMode& mode) {}
void WebDelegate::UpdateOptimizeParserBudgetEnabled(const bool enable) {}
std::shared_ptr<OHOS::NWeb::NWeb> WebDelegate::GetNweb()
{
    return nullptr;
}
bool WebDelegate::GetForceDarkMode()
{
    return false;
}
void WebDelegate::UpdateDarkMode(const WebDarkMode& mode) {}
void WebDelegate::UpdateDarkModeAuto(RefPtr<WebDelegate> delegate, std::shared_ptr<OHOS::NWeb::NWebPreference> setting)
{}
void WebDelegate::UpdateForceDarkAccess(const bool& access) {}
void WebDelegate::UpdateAudioResumeInterval(const int32_t& resumeInterval) {}
void WebDelegate::UpdateAudioSessionType(const WebAudioSessionType& audioSessionType) {}
void WebDelegate::UpdateAudioExclusive(const bool& audioExclusive) {}
void WebDelegate::UpdateOverviewModeEnabled(const bool& isOverviewModeAccessEnabled) {}
void WebDelegate::UpdateFileFromUrlEnabled(const bool& isFileFromUrlAccessEnabled) {}
void WebDelegate::UpdateDatabaseEnabled(const bool& isDatabaseAccessEnabled) {}
void WebDelegate::UpdateTextZoomRatio(const int32_t& textZoomRatioNum) {}
void WebDelegate::UpdateWebDebuggingAccess(bool isWebDebuggingAccessEnabled) {}
void WebDelegate::UpdateWebDebuggingAccessAndPort(bool enabled, int32_t port) {}
void WebDelegate::UpdatePinchSmoothModeEnabled(bool isPinchSmoothModeEnabled) {}
void WebDelegate::UpdateMediaPlayGestureAccess(bool isNeedGestureAccess) {}
void WebDelegate::UpdateMultiWindowAccess(bool isMultiWindowAccessEnabled) {}
void WebDelegate::UpdateAllowWindowOpenMethod(bool isAllowWindowOpenMethod) {}
void WebDelegate::UpdateWebCursiveFont(const std::string& cursiveFontFamily) {}
void WebDelegate::UpdateWebFantasyFont(const std::string& fantasyFontFamily) {}
void WebDelegate::UpdateWebFixedFont(const std::string& fixedFontFamily) {}
void WebDelegate::UpdateWebSansSerifFont(const std::string& sansSerifFontFamily) {}
void WebDelegate::UpdateWebSerifFont(const std::string& serifFontFamily) {}
void WebDelegate::UpdateWebStandardFont(const std::string& standardFontFamily) {}
void WebDelegate::UpdateDefaultFixedFontSize(int32_t defaultFixedFontSize) {}
void WebDelegate::OnConfigurationUpdated(const OHOS::AppExecFwk::Configuration& configuration) {}
void WebDelegate::UpdateDefaultFontSize(int32_t defaultFontSize) {}
void WebDelegate::UpdateMinFontSize(int32_t minFontSize) {}
void WebDelegate::UpdateMinLogicalFontSize(int32_t minLogicalFontSize) {}
void WebDelegate::UpdateBlockNetwork(bool isNetworkBlocked) {}
void WebDelegate::UpdateHorizontalScrollBarAccess(bool isHorizontalScrollBarAccessEnabled) {}
void WebDelegate::UpdateVerticalScrollBarAccess(bool isVerticalScrollBarAccessEnabled) {}
void WebDelegate::UpdateOverlayScrollbarEnabled(bool isEnabled) {}
void WebDelegate::UpdateNativeEmbedModeEnabled(bool isEmbedModeEnabled) {}
void WebDelegate::UpdateIntrinsicSizeEnabled(bool isIntrinsicSizeEnabled) {}
void WebDelegate::UpdateCssDisplayChangeEnabled(bool isCssDisplayChangeEnabled) {}
void WebDelegate::UpdateBypassVsyncCondition(const WebBypassVsyncCondition& condition) {}
void WebDelegate::UpdateGestureFocusMode(const GestureFocusMode& mode) {}
void WebDelegate::UpdateNativeEmbedRuleTag(const std::string& tag) {}
void WebDelegate::UpdateNativeEmbedRuleType(const std::string& type) {}
void WebDelegate::UpdateScrollBarColor(const std::string& colorValue) {}
void WebDelegate::LoadUrl() {}
void WebDelegate::OnInactive() {}
void WebDelegate::OnActive() {}
void WebDelegate::OnWebviewHide() {}
void WebDelegate::OnWebviewShow() {}
void WebDelegate::OnRenderToForeground() {}
void WebDelegate::OnRenderToBackground() {}
void WebDelegate::SetSurfaceDensity(const double& density) {}
void WebDelegate::OnOnlineRenderToForeground() {}
void WebDelegate::SetShouldFrameSubmissionBeforeDraw(bool should) {}
void WebDelegate::NotifyMemoryLevel(int32_t level) {}
void WebDelegate::SetAudioMuted(bool muted) {}
void WebDelegate::Zoom(float factor) {}
bool WebDelegate::ZoomIn()
{
    return false;
}
bool WebDelegate::ZoomOut()
{
    return false;
}
sptr<OHOS::Rosen::Window> WebDelegate::CreateWindow()
{
    return nullptr;
}
#endif
void WebDelegate::RegisterWebEvent() {}
// upper ui component which inherited from WebComponent
// could implement some curtain createdCallback to customized controller interface
// eg: web.loadurl.
void WebDelegate::AddCreatedCallback(const CreatedCallback& createdCallback) {}
void WebDelegate::RemoveCreatedCallback() {}
void WebDelegate::AddReleasedCallback(const ReleasedCallback& releasedCallback) {}
void WebDelegate::RemoveReleasedCallback() {}
void WebDelegate::Reload()
{
#ifdef OHOS_STANDARD_SYSTEM
#else
#endif
}
void WebDelegate::UpdateUrl(const std::string& url) {}
void WebDelegate::CallWebRouterBack() {}
void WebDelegate::CallPopPageSuccessPageUrl(const std::string& url) {}
void WebDelegate::CallIsPagePathInvalid(const bool& isPageInvalid) {}
void WebDelegate::RecordWebEvent(Recorder::EventType eventType, const std::string& param) const {}
void WebDelegate::OnPageStarted(const std::string& param) {}
void WebDelegate::OnPageFinished(const std::string& param) {}
void WebDelegate::SetPageFinishedState(const bool& state)
{
    isPageFinished_ = state;
}

bool WebDelegate::GetPageFinishedState()
{
    return isPageFinished_;
}
void WebDelegate::OnProgressChanged(int param) {}
void WebDelegate::OnReceivedTitle(const std::string& title, bool isRealTitle) {}
void WebDelegate::ExitFullScreen() {}
void WebDelegate::OnFullScreenExit()
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::OnGeolocationPermissionsHidePrompt() {}
void WebDelegate::OnGeolocationPermissionsShowPrompt(
    const std::string& origin, const std::shared_ptr<OHOS::NWeb::NWebGeolocationCallbackInterface>& callback)
{}
void WebDelegate::OnPermissionRequestPrompt(const std::shared_ptr<OHOS::NWeb::NWebAccessRequest>& request) {}
void WebDelegate::OnScreenCaptureRequest(const std::shared_ptr<OHOS::NWeb::NWebScreenCaptureAccessRequest>& request) {}
bool WebDelegate::OnConsoleLog(std::shared_ptr<OHOS::NWeb::NWebConsoleLog> message)
{
    return false;
}
bool WebDelegate::OnCommonDialog(const std::shared_ptr<BaseEventInfo>& info, DialogEventType dialogEventType)
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::OnFullScreenEnter(
    std::shared_ptr<OHOS::NWeb::NWebFullScreenExitHandler> handler, int videoNaturalWidth, int videoNaturalHeight)
{
#ifdef NG_BUILD
#else
#endif
}
bool WebDelegate::OnHttpAuthRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
bool WebDelegate::OnSslErrorRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
bool WebDelegate::OnAllSslErrorRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    return false;
}
bool WebDelegate::OnSslSelectCertRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::OnDownloadStart(const std::string& url, const std::string& userAgent,
    const std::string& contentDisposition, const std::string& mimetype, long contentLength)
{}
void WebDelegate::OnAccessibilityEvent(
    int64_t accessibilityId, AccessibilityEventType eventType, const std::string& argument)
{}
void WebDelegate::TextBlurReportByFocusEvent(int64_t accessibilityId) {}
void WebDelegate::WebComponentClickReport(int64_t accessibilityId) {}
void WebDelegate::TextBlurReportByBlurEvent(int64_t accessibilityId) {}
void WebDelegate::OnErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error)
{}
void WebDelegate::ReportDynamicFrameLossEvent(const std::string& sceneId, bool isStart) {}
void WebDelegate::OnHttpErrorReceive(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceResponse> response)
{}
bool WebDelegate::IsEmptyOnInterceptRequest()
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
RefPtr<WebResponse> WebDelegate::OnInterceptRequest(const std::shared_ptr<BaseEventInfo>& info)
{
    return nullptr;
}
std::string WebDelegate::OnOverrideErrorPage(
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request,
    std::shared_ptr<OHOS::NWeb::NWebUrlResourceError> error)
{
    return "";
}
void WebDelegate::OnTooltip(const std::string& tooltip) {}
void WebDelegate::OnRequestFocus() {}
void WebDelegate::OnRenderExited(OHOS::NWeb::RenderExitReason reason) {}
void WebDelegate::OnRefreshAccessedHistory(const std::string& url, bool isRefreshed) {}
void WebDelegate::OnPageError(const std::string& param) {}
void WebDelegate::OnMessage(const std::string& param) {}
void WebDelegate::OnRouterPush(const std::string& param) {}
bool WebDelegate::OnFileSelectorShow(const std::shared_ptr<BaseEventInfo>& info)
{
    return false;
}
bool WebDelegate::OnContextMenuShow(const std::shared_ptr<BaseEventInfo>& info)
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::OnContextMenuHide(const std::string& info) {}
bool WebDelegate::OnHandleInterceptUrlLoading(const std::string& data)
{
    return false;
}
bool WebDelegate::OnHandleInterceptLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    return false;
}
void WebDelegate::OnResourceLoad(const std::string& url) {}
void WebDelegate::OnScaleChange(float oldScaleFactor, float newScaleFactor) {}
void WebDelegate::OnScroll(double xOffset, double yOffset) {}
void WebDelegate::OnSearchResultReceive(int activeMatchOrdinal, int numberOfMatches, bool isDoneCounting) {}
bool WebDelegate::OnDragAndDropData(const void* data, size_t len, int width, int height)
{
    return false;
}
bool WebDelegate::OnDragAndDropDataUdmf(std::shared_ptr<OHOS::NWeb::NWebDragData> dragData)
{
    return false;
}
bool WebDelegate::IsImageDrag()
{
    return false;
}
std::shared_ptr<OHOS::NWeb::NWebDragData> WebDelegate::GetOrCreateDragData()
{
    return nullptr;
}
void WebDelegate::OnWindowNew(const std::string& targetUrl, bool isAlert, bool isUserTrigger,
    const std::shared_ptr<OHOS::NWeb::NWebControllerHandler>& handler)
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::OnActivateContent() {}
void WebDelegate::OnWindowExit() {}
void WebDelegate::OnPageVisible(const std::string& url) {}
void WebDelegate::OnFirstContentfulPaint(int64_t navigationStartTick, int64_t firstContentfulPaintMs) {}
void WebDelegate::OnFirstMeaningfulPaint(std::shared_ptr<OHOS::NWeb::NWebFirstMeaningfulPaintDetails> details) {}
void WebDelegate::OnLargestContentfulPaint(std::shared_ptr<OHOS::NWeb::NWebLargestContentfulPaintDetails> details) {}
void WebDelegate::OnSafeBrowsingCheckResult(int threat_type) {}
void WebDelegate::OnDataResubmitted(std::shared_ptr<OHOS::NWeb::NWebDataResubmissionCallback> handler) {}
void WebDelegate::OnNavigationEntryCommitted(std::shared_ptr<OHOS::NWeb::NWebLoadCommittedDetails> details) {}
void WebDelegate::OnFaviconReceived(const void* data, size_t width, size_t height, OHOS::NWeb::ImageColorType colorType,
    OHOS::NWeb::ImageAlphaType alphaType)
{}
void WebDelegate::OnTouchIconUrl(const std::string& iconUrl, bool precomposed) {}
void WebDelegate::OnAudioStateChanged(bool audible) {}
void WebDelegate::OnGetTouchHandleHotZone(std::shared_ptr<OHOS::NWeb::NWebTouchHandleHotZone> hotZone) {}
RefPtr<PixelMap> WebDelegate::GetDragPixelMap()
{
    return pixelMap_;
}
#ifdef OHOS_STANDARD_SYSTEM
void WebDelegate::HandleTouchDown(const int32_t& id, const double& x, const double& y, bool from_overlay) {}
void WebDelegate::HandleTouchUp(const int32_t& id, const double& x, const double& y, bool from_overlay) {}
void WebDelegate::HandleTouchMove(const int32_t& id, const double& x, const double& y, bool from_overlay) {}
void WebDelegate::HandleTouchMove(
    const std::vector<std::shared_ptr<OHOS::NWeb::NWebTouchPointInfo>>& touch_point_infos, bool from_overlay)
{}
void WebDelegate::HandleTouchCancel() {}
void WebDelegate::HandleTouchpadFlingEvent(const double& x, const double& y, const double& vx, const double& vy) {}
void WebDelegate::WebHandleTouchpadFlingEvent(
    const double& x, const double& y, const double& vx, const double& vy, const std::vector<int32_t>& pressedCodes)
{}
void WebDelegate::HandleAxisEvent(const double& x, const double& y, const double& deltaX, const double& deltaY) {}
void WebDelegate::WebHandleAxisEvent(const double& x, const double& y, const double& deltaX, const double& deltaY,
    const std::vector<int32_t>& pressedCodes, const int32_t source)
{}
bool WebDelegate::OnKeyEvent(int32_t keyCode, int32_t keyAction)
{
    return false;
}
bool WebDelegate::WebOnKeyEvent(int32_t keyCode, int32_t keyAction, const std::vector<int32_t>& pressedCodes)
{
    return false;
}
bool WebDelegate::SendKeyboardEvent(const std::shared_ptr<OHOS::NWeb::NWebKeyboardEvent>& keyboardEvent)
{
    return false;
}
void WebDelegate::OnMouseEvent(int32_t x, int32_t y, const MouseButton button, const MouseAction action, int count) {}
void WebDelegate::WebOnMouseEvent(const std::shared_ptr<OHOS::NWeb::NWebMouseEvent>& mouseEvent) {}
void WebDelegate::OnFocus(const OHOS::NWeb::FocusReason& reason) {}
bool WebDelegate::NeedSoftKeyboard()
{
    return true;
}
void WebDelegate::OnBlur() {}
void WebDelegate::UpdateClippedSelectionBounds(int32_t x, int32_t y, int32_t w, int32_t h) {}
bool WebDelegate::RunQuickMenu(std::shared_ptr<OHOS::NWeb::NWebQuickMenuParams> params,
    std::shared_ptr<OHOS::NWeb::NWebQuickMenuCallback> callback)
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::HideHandleAndQuickMenuIfNecessary(bool hide) {}
void WebDelegate::OnQuickMenuDismissed()
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::OnTouchSelectionChanged(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> insertHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> startSelectionHandle,
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> endSelectionHandle)
{
#ifdef NG_BUILD
#else
#endif
}
bool WebDelegate::OnCursorChange(const OHOS::NWeb::CursorType& type, std::shared_ptr<OHOS::NWeb::NWebCursorInfo> info)
{
    return false;
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::OnSelectPopupMenu(std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParam> params,
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallback> callback)
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::HandleDragEvent(int32_t x, int32_t y, const DragAction& dragAction)
{
}
std::string WebDelegate::GetUrl()
{
    return "";
}
void WebDelegate::UpdateLocale() {}
void WebDelegate::SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height) {}
bool WebDelegate::GetPendingSizeStatus()
{
    return false;
}
void WebDelegate::HandleAccessibilityHoverEvent(
    const NG::PointF& point, SourceType source, NG::AccessibilityHoverEventType eventType, TimeStamp time) {}

std::string WebDelegate::GetSurfaceIdByHtmlElementId(const std::string& htmlElementId)
{
    auto it = htmlElementToSurfaceMap.find(htmlElementId);
    if (it != htmlElementToSurfaceMap.end()) {
        return it->second;
    }
    return "";
}
std::string WebDelegate::GetHtmlElementIdBySurfaceId(const std::string& surfaceId)
{
    auto it = surfaceToHtmlElementMap.find(surfaceId);
    if (it != surfaceToHtmlElementMap.end()) {
        return it->second;
    }
    return "";
}

int64_t WebDelegate::GetWebAccessibilityIdBySurfaceId(const std::string& surfaceId)
{
    auto it = surfaceToWebAccessibilityMap.find(surfaceId);
    if (it != surfaceToWebAccessibilityMap.end()) {
        return it->second;
    }
    return -1;
}
void WebDelegate::NotifyAutoFillViewData(const std::string& jsonStr) {}
void WebDelegate::AutofillCancel(const std::string& fillContent) {}
bool WebDelegate::HandleAutoFillEvent(const std::shared_ptr<OHOS::NWeb::NWebMessage>& viewDataJson)
{
    return false;
}
#endif
std::string WebDelegate::GetUrlStringParam(const std::string& param, const std::string& name) const
{
    return "";
}
void WebDelegate::SetRenderMode(RenderMode renderMode) {}
void WebDelegate::SetFitContentMode(WebLayoutMode layoutMode) {}
void WebDelegate::BindRouterBackMethod() {}
void WebDelegate::BindPopPageSuccessMethod() {}
void WebDelegate::BindIsPagePathInvalidMethod() {}
void WebDelegate::SetComponent(const RefPtr<WebComponent>& component) {}
void WebDelegate::SetNGWebPattern(const RefPtr<NG::WebPattern>& webPattern) {}
void WebDelegate::SetDrawSize(const Size& drawSize) {}
void WebDelegate::SetEnhanceSurfaceFlag(const bool& isEnhanceSurface) {}
sptr<OHOS::SurfaceDelegate> WebDelegate::GetSurfaceDelegateClient()
{
    return nullptr;
}
void WebDelegate::SetBoundsOrResize(const Size& drawSize, const Offset& offset, bool isKeyboard) {}
void WebDelegate::ResizeVisibleViewport(const Size& visibleSize, bool isKeyboard) {}
Offset WebDelegate::GetWebRenderGlobalPos()
{
    return Offset();
}
Size WebDelegate::GetEnhanceSurfaceSize(const Size& drawSize)
{
    return Size();
}
WebDelegate::EventCallbackV2 WebDelegate::GetAudioStateChangedCallback(
    bool useNewPipe, const RefPtr<NG::WebEventHub>& eventHub)
{
    return nullptr;
}
#ifdef ENABLE_ROSEN_BACKEND
void WebDelegate::SetSurface(const sptr<Surface>& surface) {}
#endif
void WebDelegate::UpdateScreenOffSet(double& offsetX, double& offsetY)
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::UpdateOverScrollMode(const int overscrollModeValue) {}
void WebDelegate::UpdateBlurOnKeyboardHideMode(const int isBlurOnKeyboardHideEnable) {}
void WebDelegate::GestureBackBlur() {}
void WebDelegate::UpdateCopyOptionMode(const int copyOptionModeValue) {}
void WebDelegate::UpdateNativeVideoPlayerConfig(bool enable, bool shouldOverlay) {}
void WebDelegate::UpdateTextAutosizing(bool isTextAutosizing) {}
void WebDelegate::RegisterSurfacePositionChangedCallback()
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::UnregisterSurfacePositionChangedCallback()
{
#ifdef NG_BUILD
#else
#endif
}
void WebDelegate::OnCompleteSwapWithNewSize() {}
void WebDelegate::OnResizeNotWork() {}
void WebDelegate::OnDateTimeChooserPopup(std::shared_ptr<OHOS::NWeb::NWebDateTimeChooser> chooser,
    const std::vector<std::shared_ptr<OHOS::NWeb::NWebDateTimeSuggestion>>& suggestions,
    std::shared_ptr<OHOS::NWeb::NWebDateTimeChooserCallback> callback)
{}
void WebDelegate::OnDateTimeChooserClose() {}
void WebDelegate::OnOverScroll(float xOffset, float yOffset) {}
void WebDelegate::SetTouchEventInfo(
    std::shared_ptr<OHOS::NWeb::NWebNativeEmbedTouchEvent> touchEvent, TouchEventInfo& touchEventInfo)
{}

bool WebDelegate::GetIsSmoothDragResizeEnabled()
{
    return false;
}
void WebDelegate::MaximizeResize() {}
void WebDelegate::DragResize(
    const double& width, const double& height, const double& pre_height, const double& pre_width)
{}
void WebDelegate::OnNativeEmbedAllDestory() {}
void WebDelegate::OnNativeEmbedLifecycleChange(std::shared_ptr<OHOS::NWeb::NWebNativeEmbedDataInfo> dataInfo) {}
void WebDelegate::OnNativeEmbedGestureEvent(std::shared_ptr<OHOS::NWeb::NWebNativeEmbedTouchEvent> event) {}
void WebDelegate::SetToken() {}
#if defined(ENABLE_ROSEN_BACKEND)
void WebDelegate::SetPopupSurface(const RefPtr<NG::RenderSurface>& popupSurface) {}
#endif
void WebDelegate::OnOverScrollFlingVelocity(float xVelocity, float yVelocity, bool isFling) {}
void WebDelegate::OnScrollState(bool scrollState) {}
void WebDelegate::OnScrollStart(const float x, const float y) {}
bool WebDelegate::OnNestedScroll(float& x, float& y, float& xVelocity, float& yVelocity, bool& isAvailable)
{
    return false;
}
void WebDelegate::OnRootLayerChanged(int width, int height) {}
bool WebDelegate::FilterScrollEvent(const float x, const float y, const float xVelocity, const float yVelocity)
{
    return false;
}
void WebDelegate::ScrollBy(float deltaX, float deltaY) {}
void WebDelegate::ReleaseResizeHold() {}
void WebDelegate::ScrollByRefScreen(float deltaX, float deltaY, float vx, float vy) {}
void WebDelegate::SetVirtualKeyBoardArg(int32_t width, int32_t height, double keyboard) {}
bool WebDelegate::ShouldVirtualKeyboardOverlay()
{
    return true;
}
void WebDelegate::SetJavaScriptItems(const ScriptItems& scriptItems, const ScriptItemType& type) {}
void WebDelegate::JavaScriptOnDocumentStart() {}
void WebDelegate::JavaScriptOnDocumentEnd() {}

void WebDelegate::SetJavaScriptItemsByOrder(
    const ScriptItems& scriptItems,
    const ScriptItemType& type,
    const ScriptItemsByOrder& scriptItemsByOrder) {}
void WebDelegate::JavaScriptOnDocumentStartByOrder() {}
void WebDelegate::JavaScriptOnDocumentEndByOrder() {}
void WebDelegate::JavaScriptOnHeadReadyByOrder() {}
bool WebDelegate::ExecuteAction(
    int64_t accessibilityId, AceAction action, const std::map<std::string, std::string>& actionArguments)
{
    return false;
}
bool WebDelegate::GetAccessibilityNodeRectById(
    int64_t accessibilityId, int32_t* width, int32_t* height, int32_t* offsetX, int32_t* offsetY)
{
    return g_setReturnStatus == STATUS_TRUE;
}
void WebDelegate::SetAccessibilityState(bool state, bool isDelayed) {}
std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> WebDelegate::GetFocusedAccessibilityNodeInfo(
    int64_t accessibilityId, bool isAccessibilityFocus)
{
    if (g_setReturnStatus == STATUS_TRUE) {
        return std::make_shared<MockNWebAccessibilityNodeInfoOnlyForReturn>();
    }
    return nullptr;
}
std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> WebDelegate::GetAccessibilityNodeInfoById(
    int64_t accessibilityId)
{
    if (g_setReturnStatus == STATUS_TRUE) {
        return std::make_shared<MockNWebAccessibilityNodeInfoOnlyForReturn>();
    }
    return nullptr;
}
std::shared_ptr<OHOS::NWeb::NWebAccessibilityNodeInfo> WebDelegate::GetAccessibilityNodeInfoByFocusMove(
    int64_t accessibilityId, int32_t direction)
{
    if (g_setReturnStatus == STATUS_TRUE) {
        return std::make_shared<MockNWebAccessibilityNodeInfoOnlyForReturn>();
    }
    return nullptr;
}
OHOS::NWeb::NWebPreference::CopyOptionMode WebDelegate::GetCopyOptionMode() const
{
    return OHOS::NWeb::NWebPreference::CopyOptionMode::NONE;
}
bool WebDelegate::OnOpenAppLink(const std::string& url, std::shared_ptr<OHOS::NWeb::NWebAppLinkCallback> callback)
{
    return false;
}
std::string WebDelegate::GetCanonicalEncodingName(const std::string& alias_name) const
{
    return "";
}
void WebDelegate::UpdateDefaultTextEncodingFormat(const std::string& textEncodingFormat) {}
void WebDelegate::OnIntelligentTrackingPreventionResult(const std::string& websiteHost, const std::string& trackerHost)
{}
bool WebDelegate::OnHandleOverrideLoading(std::shared_ptr<OHOS::NWeb::NWebUrlResourceRequest> request)
{
    return false;
}
void WebDelegate::OnDetachContext() {}
void WebDelegate::OnAttachContext(const RefPtr<NG::PipelineContext>& context) {}
void WebDelegate::UpdateMetaViewport(bool isMetaViewportEnabled) {}
std::vector<int8_t> WebDelegate::GetWordSelection(const std::string& text, int8_t offset)
{
    return {};
}
void WebDelegate::NotifyForNextTouchEvent() {}
void WebDelegate::OnRenderProcessNotResponding(
    const std::string& jsStack, int pid, OHOS::NWeb::RenderProcessNotRespondingReason reason)
{}
void WebDelegate::OnRenderProcessResponding() {}
void WebDelegate::ScaleGestureChange(double scale, double centerX, double centerY)
{}
void WebDelegate::ScaleGestureChangeV2(int type, double scale, double originScale, double centerX, double centerY)
{}
std::string WebDelegate::GetSelectInfo() const
{
    return "";
}
Offset WebDelegate::GetPosition(const std::string& embedId)
{
    return Offset();
}
void WebDelegate::OnShowAutofillPopup(
    const float offsetX, const float offsetY, const std::vector<std::string>& menu_items)
{}
void WebDelegate::OnShowAutofillPopupV2(
    const float offsetX, const float offsetY, const float height, const float width,
    const std::vector<std::string>& menu_items)
{}
void WebDelegate::SuggestionSelected(int32_t index) {}
void WebDelegate::OnHideAutofillPopup() {}
void WebDelegate::OnAreaChange(const OHOS::Ace::Rect& area) {}
void WebDelegate::OnViewportFitChange(OHOS::NWeb::ViewportFit viewportFit) {}
void WebDelegate::OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type) {}
void WebDelegate::OnInterceptKeyboardAttach(
    const std::shared_ptr<OHOS::NWeb::NWebCustomKeyboardHandler> keyboardHandler,
    const std::map<std::string, std::string>& attributes, bool& useSystemKeyboard, int32_t& enterKeyType)
{}
void WebDelegate::OnCustomKeyboardAttach() {}
void WebDelegate::OnCustomKeyboardClose() {}
void WebDelegate::KeyboardReDispatch(const std::shared_ptr<OHOS::NWeb::NWebKeyEvent>& event, bool isUsed) {}
void WebDelegate::OnCursorUpdate(double x, double y, double width, double height) {}
void WebDelegate::OnSafeInsetsChange() {}
void WebDelegate::CreateOverlay(void* data, size_t len, int width, int height, int offsetX, int offsetY, int rectWidth,
    int rectHeight, int pointX, int pointY)
{}
void WebDelegate::OnOverlayStateChanged(int offsetX, int offsetY, int rectWidth, int rectHeight) {}
void WebDelegate::OnTextSelected() {}
void WebDelegate::OnDestroyImageAnalyzerOverlay() {}
std::string WebDelegate::GetWebInfoType()
{
    return g_setReturnStatus;
}
void WebDelegate::SetSurfaceId(const std::string& surfaceId) {}
void WebDelegate::OnAdsBlocked(const std::string& url, const std::vector<std::string>& adsBlocked) {}
std::string WebDelegate::SpanstringConvertHtml(const std::vector<uint8_t>& content)
{
    return "";
}
bool WebDelegate::CloseImageOverlaySelection()
{
    return false;
}
void SetReturnStatus(const std::string& status)
{
    g_setReturnStatus = status;
}
void SetComponentType(const std::string& type)
{
    g_setComponentType = type;
}
void WebDelegate::UpdateLayoutMode(OHOS::Ace::WebLayoutMode mode) {}
void WebDelegate::SetTransformHint(uint32_t rotation) {}
void WebDelegate::RegisterNativeArkJSFunction(const std::string& objName,
    const std::vector<std::pair<std::string, NativeMethodCallback>>& methodList, bool isNeedRefresh)
{}
void WebDelegate::UnRegisterNativeArkJSFunction(const std::string& objName) {}
void WebDelegate::RegisterNativeJavaScriptProxy(const std::string& obj, const std::vector<std::string>& method,
    std::vector<std::function<void(const std::vector<std::string>&)>> callbackImpl,
    bool isAync, const std::string& permission, bool isNeedRefresh)
{}
void WebDelegate::UpdateEnableFollowSystemFontWeight(bool enableFollowSystemFontWeight) {}
bool WebDelegate::IsActivePolicyDisable()
{
    return false;
}
void WebDelegate::SetDragResizeStartFlag(bool isDragResizeStart) {}
void WebDelegate::SetDragResizePreSize(const double& pre_height, const double& pre_width) {}
void WebDelegate::UpdateWebMediaAVSessionEnabled(bool isEnabled) {}
bool WebDelegate::SetFocusByPosition(float x, float y)
{
    return false;
}
std::string WebDelegate::GetCurrentLanguage()
{
    return "";
}
void WebDelegate::RegisterWebWindowFocusChangedListener() {}
void WebDelegate::UnRegisterWebWindowFocusChangedListener() {}
void WebDelegate::OnDragAttach() {}
bool WebDelegate::IsNWebEx() { return false; }
void WebDelegate::SetNativeInnerWeb(bool isInnerWeb) {}

void WebDelegate::ResetStateOfDataDetectorJS() {}
void WebDelegate::RunDataDetectorJS() {}
void WebDelegate::SetDataDetectorEnable(bool enable) {}
void WebDelegate::OnDataDetectorSelectText() {}
void WebDelegate::OnDataDetectorCopy(const std::vector<std::string>& recordMix) {}

bool WebDelegate::GetAccessibilityVisible(int64_t accessibilityId)
{
    return false;
}

void WebDelegate::RemoveSnapshotFrameNode(int removeDelayTime) {}
void WebDelegate::CreateSnapshotFrameNode(const std::string& snapshotPath) {}
void WebDelegate::SetVisibility(bool isVisible) {}

void WebDelegate::OnPip(int status, int delegate_id,
    int child_id, int frame_routing_id,  int width, int height) {}
void WebDelegate::SetPipNativeWindow(int delegate_id,
    int child_id, int frame_routing_id, void* window) {}
void WebDelegate::SendPipEvent(int delegate_id,
    int child_id, int frame_routing_id, int event) {}

void WebDelegate::UpdateSingleHandleVisible(bool isVisible) {}
bool WebDelegate::ShowMagnifier() { return false; }
bool WebDelegate::HideMagnifier() { return false; }
void WebDelegate::SetTouchHandleExistState(bool touchHandleExist) {}
void WebDelegate::SetBorderRadiusFromWeb(double borderRadiusTopLeft, double borderRadiusTopRight,
    double borderRadiusBottomLeft, double borderRadiusBottomRight) {}
} // namespace OHOS::Ace
