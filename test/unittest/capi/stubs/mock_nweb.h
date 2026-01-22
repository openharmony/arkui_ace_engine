/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef CAPI_STUBS_MOCK_NWEB_H
#define CAPI_STUBS_MOCK_NWEB_H

#include <string>
#include <map>
#include <memory>
#include <vector>

namespace OHOS::NWeb {

enum class BlurReason : int32_t {
    FOCUS_SWITCH = 0,
    WINDOW_BLUR = 1,
    FRAME_DESTROY = 2, // frame node detached from main tree
    VIEW_SWITCH = 3,
    CLEAR_FOCUS = 4, // User api clearFocus triggered
};

enum class FocusReason : int32_t {
    FOCUS_DEFAULT = 0,
    EVENT_REQUEST = 1,
};

class NWebTouchPointInfo {
public:
    virtual ~NWebTouchPointInfo() = default;

    virtual int GetId() = 0;
    virtual double GetX() = 0;
    virtual double GetY() = 0;
};

class NWeb {
public:
    NWeb() = default;
    virtual ~NWeb() = default;

    virtual void Resize(uint32_t width, uint32_t height, bool isKeyboard = false) {}

    /* lifecycle interface */
    virtual void OnPause() {}
    virtual void OnContinue() {}
    virtual void OnDestroy() {}

    /* focus event */
    virtual void OnFocus(const FocusReason& focusReason = FocusReason::FOCUS_DEFAULT) {}
    virtual void OnBlur(const BlurReason& blurReason) {}

    /* event interface */
    virtual void OnTouchPress(int32_t id, double x, double y, bool fromOverlay = false) {}
    virtual void OnTouchRelease(int32_t id, double x = 0, double y = 0, bool fromOverlay = false) {}
    virtual void OnTouchMove(int32_t id, double x, double y, bool fromOverlay = false) {}
    virtual void OnTouchMove(
        const std::vector<std::shared_ptr<NWebTouchPointInfo>>& touch_point_infos, bool fromOverlay = false) {}
    virtual void OnTouchCancel() {}
    virtual void OnNavigateBack() {}
    virtual bool SendKeyEvent(int32_t keyCode, int32_t keyAction)
    {
        return true;
    }
    virtual void SendMouseWheelEvent(double x, double y, double deltaX, double deltaY) {}
    virtual void SendMouseEvent(int x, int y, int button, int action, int count) {}

    virtual int Load(const std::string& url)
    {
        return 0;
    }

    virtual bool IsNavigatebackwardAllowed()
    {
        return true;
    }

    virtual bool IsNavigateForwardAllowed()
    {
        return true;
    }

    virtual bool CanNavigateBackOrForward(int numSteps)
    {
        return true;
    }
    virtual void NavigateBack() {}
    virtual void NavigateForward() {}
    virtual void NavigateBackOrForward(int step) {}

    virtual void DeleteNavigateHistory() {}

    virtual void Reload() {}

    virtual int Zoom(float zoomFactor)
    {
        return 0;
    }

    virtual int ZoomIn()
    {
        return 0;
    }

    virtual int ZoomOut()
    {
        return 0;
    }

    virtual void Stop() {}

    virtual void ExecuteJavaScript(const std::string& code) {}

    virtual unsigned int GetWebId()
    {
        return 0;
    }

    virtual void PutBackgroundColor(int color) {}

    virtual void InitialScale(float scale) {}

    virtual std::string Title()
    {
        return "";
    }

    virtual int PageLoadProgress()
    {
        return 0;
    }

    virtual int ContentHeight()
    {
        return 0;
    }

    virtual float Scale()
    {
        return .0f;
    }

    virtual int Load(const std::string& url, const std::map<std::string, std::string>& additionalHttpHeaders)
    {
        return 0;
    }

    virtual int LoadWithDataAndBaseUrl(const std::string& baseUrl, const std::string& data, const std::string& mimeType,
        const std::string& encoding, const std::string& historyUrl)
    {
        return 0;
    }

    virtual int LoadWithData(const std::string& data, const std::string& mimeType, const std::string& encoding)
    {
        return 0;
    }

    virtual void RegisterArkJSfunction(
        const std::string& object_name, const std::vector<std::string>& method_list, const int32_t object_id) {}

    virtual void UnregisterArkJSfunction(
        const std::string& object_name, const std::vector<std::string>& method_list) {}

    virtual void FindAllAsync(const std::string& searchStr) {}

    virtual void ClearMatches() {}

    virtual void FindNext(const bool forward) {}

    virtual std::vector<std::string> CreateWebMessagePorts()
    {
        return {};
    }

    virtual void PostWebMessage(
        const std::string& message, const std::vector<std::string>& ports, const std::string& targetUri) {}

    virtual void ClosePort(const std::string& portHandle) {}

    virtual void ClearSslCache() {}

    virtual std::string GetUrl()
    {
        return "";
    }

    virtual void ClearClientAuthenticationCache() {}

    virtual void UpdateLocale(const std::string& language, const std::string& region) {}

    virtual const std::string GetOriginalUrl()
    {
        return "";
    }

    virtual void PutNetworkAvailable(bool available) {}

    virtual void RemoveCache(bool include_disk_files) {}

    virtual std::vector<uint8_t> SerializeWebState()
    {
        return {};
    }

    virtual bool RestoreWebState(const std::vector<uint8_t>& state)
    {
        return true;
    }

    virtual void PageUp(bool top) {}

    virtual void PageDown(bool bottom) {}

    virtual void ScrollTo(float x, float y) {}

    virtual void ScrollBy(float delta_x, float delta_y) {}

    virtual void SlideScroll(float vx, float vy) {}

    virtual bool GetCertChainDerData(std::vector<std::string>& certChainData, bool isSingleCert)
    {
        return true;
    }

    virtual void SetScreenOffSet(double x, double y) {}

    virtual void SetAudioMuted(bool muted) {}

    virtual void SetShouldFrameSubmissionBeforeDraw(bool should) {}

    virtual void NotifyPopupWindowResult(bool result) {}

    virtual void SetAudioResumeInterval(int32_t resumeInterval) {}

    virtual void SetAudioExclusive(bool audioExclusive) {}

    virtual void UnRegisterScreenLockFunction(int32_t windowId) {}

    virtual void NotifyMemoryLevel(int32_t level) {}

    virtual void OnWebviewHide() {}
    virtual void OnWebviewShow() {}

    virtual void PrefetchPage(
        const std::string& url, const std::map<std::string, std::string>& additionalHttpHeaders) {}

    virtual void SetWindowId(uint32_t window_id) {}

    virtual void OnOccluded() {}

    virtual void OnUnoccluded() {}

    virtual void SetToken(void* token) {}

    virtual void SetEnableLowerFrameRate(bool enabled) {}

    virtual void SetVirtualKeyBoardArg(int32_t width, int32_t height, double keyboard) {}

    virtual bool ShouldVirtualKeyboardOverlay()
    {
        return true;
    }

    virtual void SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height) {}

    virtual void SetDrawMode(int32_t mode) {}

    virtual void* CreateWebPrintDocumentAdapter(const std::string& jobName)
    {
        return nullptr;
    }

    virtual int PostUrl(const std::string& url, const std::vector<char>& postData)
    {
        return 0;
    }

    virtual void ExecuteAction(int64_t accessibilityId, uint32_t action) {}

    virtual void SetAccessibilityState(bool state) {}

    virtual bool NeedSoftKeyboard()
    {
        return true;
    }

    virtual bool Discard()
    {
        return true;
    }

    virtual bool Restore()
    {
        return true;
    }

    virtual int GetSecurityLevel()
    {
        return 0;
    }

    virtual bool IsIncognitoMode()
    {
        return true;
    }

    virtual void UnRegisterNativeArkJSFunction(const char* objName) {}

    virtual void EnableSafeBrowsing(bool enable) {}

    virtual bool IsSafeBrowsingEnabled()
    {
        return true;
    }

    virtual void SetPrintBackground(bool enable) {}

    virtual bool GetPrintBackground()
    {
        return true;
    }

    virtual void CloseAllMediaPresentations() {}

    virtual void StopAllMedia() {}

    virtual void ResumeAllMedia() {}

    virtual void PauseAllMedia() {}

    virtual int GetMediaPlaybackState()
    {
        return 0;
    }

    virtual void EnableIntelligentTrackingPrevention(bool enable) {}

    virtual bool IsIntelligentTrackingPreventionEnabled() const
    {
        return true;
    }

    virtual void StartCamera() {}

    virtual void StopCamera() {}

    virtual void CloseCamera() {}

    virtual std::string GetLastJavascriptProxyCallingFrameUrl()
    {
        return "";
    }

    virtual bool GetPendingSizeStatus()
    {
        return true;
    }

    virtual void ScrollByRefScreen(float delta_x, float delta_y, float vx, float vy) {}

    virtual void OnRenderToBackground() {}

    virtual void OnRenderToForeground() {}

    virtual void DragResize(uint32_t width, uint32_t height, uint32_t pre_height, uint32_t pre_width) {}

    virtual void OnTouchCancelById(int32_t id, double x, double y, bool from_overlay) {}

    virtual int ScaleGestureChange(double scale, double centerX, double centerY)
    {
        return 0;
    }

    virtual void InjectOfflineResource(const std::string& url, const std::string& origin,
        const std::vector<uint8_t>& resource, const std::map<std::string, std::string>& responseHeaders,
        const int type) {}

    virtual bool TerminateRenderProcess()
    {
        return true;
    }

    virtual void SuggestionSelected(int32_t index) {}

    virtual void RegisterArkJSfunction(const std::string& object_name, const std::vector<std::string>& method_list,
        const std::vector<std::string>& async_method_list, const int32_t object_id) {}

    virtual void SendTouchpadFlingEvent(double x, double y, double vx, double vy) {}

    virtual void SetFitContentMode(int32_t mode) {}

    virtual std::string GetSelectInfo()
    {
        return "";
    }

    virtual void OnOnlineRenderToForeground() {}

    virtual void OnSafeInsetsChange(int left, int top, int right, int bottom) {}

    virtual void OnTextSelected() {}

    virtual bool WebSendKeyEvent(int32_t keyCode, int32_t keyAction,
                                 const std::vector<int32_t>& pressedCodes)
    {
        return false;
    }

    virtual void EnableAdsBlock(bool enable) {}

    virtual bool IsAdsBlockEnabled()
    {
        return false;
    }

    virtual bool IsAdsBlockEnabledForCurPage()
    {
        return false;
    }

    virtual void NotifyForNextTouchEvent() {}

    virtual int SetUrlTrustList(const std::string& urlTrustList)
    {
        return 0;
    }

    virtual void SetPathAllowingUniversalAccess(const std::vector<std::string>& dirList,
                                                const std::vector<std::string>& moduleName,
                                                std::string& errorPath) {}

    virtual void PerformAction(int64_t accessibilityId, uint32_t action,
        const std::map<std::string, std::string>& actionArguments) {}

    virtual void ScrollToWithAnime(float x, float y, int32_t duration) {}

    virtual void ScrollByWithAnime(float delta_x, float delta_y, int32_t duration) {}

    virtual void WebSendMouseWheelEvent(double x,
                                        double y,
                                        double delta_x,
                                        double delta_y,
                                        const std::vector<int32_t>& pressedCodes) {}

    virtual void WebSendTouchpadFlingEvent(double x,
                                           double y,
                                           double vx,
                                           double vy,
                                           const std::vector<int32_t>& pressedCodes) {}

    virtual int SetUrlTrustListWithErrMsg(const std::string& urlTrustList, std::string& detailErrMsg)
    {
        return 0;
    }

    virtual void SendAccessibilityHoverEvent(int32_t x, int32_t y) {}

    virtual void RegisterArkJSfunction(const std::string& object_name, const std::vector<std::string>& method_list,
        const std::vector<std::string>& async_method_list, const int32_t object_id, const std::string& permission) {}

    virtual void ResizeVisibleViewport(uint32_t width, uint32_t height, bool isKeyboard) {}

    virtual void SetBackForwardCacheOptions(int32_t size, int32_t timeToLive) { return; }

    virtual void OnAutofillCancel(const std::string& fillContent) {}

    virtual void GetScrollOffset(float* offset_x, float* offset_y) {}

    virtual bool ScrollByWithResult(float delta_x, float delta_y)
    {
        return false;
    }

    virtual void SetPopupSurface(void* popupSurface) {}

    virtual void OnDestroyImageAnalyzerOverlay() {}

    virtual void SetTransformHint(uint32_t rotation) {}
};
} // namespace OHOS::NWeb

#endif