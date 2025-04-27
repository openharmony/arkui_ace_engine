/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_WEB_DELEGATE_INTERFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_WEB_DELEGATE_INTERFACE_H

#include "base/geometry/size.h"
#include "base/geometry/offset.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/event/ace_events.h"
#include "core/components/web/web_property.h"

namespace OHOS::Ace {
namespace NG {
class WebPattern;
}; // namespace NG
class WebDelegateInterface : public virtual AceType {
    DECLARE_ACE_TYPE(WebDelegateInterface, AceType);
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

    WebDelegateInterface() = default;
    virtual ~WebDelegateInterface() = default;

    virtual void CreatePlatformResource(const Size& size,
        const Offset& position, const WeakPtr<NG::PipelineContext>& context) = 0;
    virtual void ShowWebView() = 0;
    virtual void HideWebView() = 0;
    virtual void UpdateUserAgent(const std::string& userAgent) = 0;
    virtual void UpdateBackgroundColor(const int backgroundColor) = 0;
    virtual void UpdateInitialScale(float scale) = 0;
    virtual void UpdateJavaScriptEnabled(const bool& isJsEnabled) = 0;
    virtual void UpdateAllowFileAccess(const bool& isFileAccessEnabled) = 0;
    virtual void UpdateBlockNetworkImage(const bool& onLineImageAccessEnabled) = 0;
    virtual void UpdateLoadsImagesAutomatically(const bool& isImageAccessEnabled) = 0;
    virtual void UpdateMixedContentMode(const MixedModeContent& mixedMode) = 0;
    virtual void UpdateSupportZoom(const bool& isZoomAccessEnabled) = 0;
    virtual void UpdateDomStorageEnabled(const bool& isDomStorageAccessEnabled) = 0;
    virtual void UpdateGeolocationEnabled(const bool& isGeolocationAccessEnabled) = 0;
    virtual void UpdateCacheMode(const WebCacheMode& mode) = 0;
    virtual void UpdateDarkMode(const WebDarkMode& mode) = 0;
    virtual void UpdateForceDarkAccess(const bool& access) = 0;
    virtual void UpdateAudioResumeInterval(const int32_t& resumeInterval) = 0;
    virtual void UpdateAudioExclusive(const bool& audioExclusive) = 0;
    virtual void UpdateOverviewModeEnabled(const bool& isOverviewModeAccessEnabled) = 0;
    virtual void UpdateFileFromUrlEnabled(const bool& isFileFromUrlAccessEnabled) = 0;
    virtual void UpdateDatabaseEnabled(const bool& isDatabaseAccessEnabled) = 0;
    virtual void UpdateTextZoomRatio(const int32_t& textZoomRatioNum) = 0;
    virtual void UpdateWebDebuggingAccess(bool isWebDebuggingAccessEnabled) = 0;
    virtual void UpdatePinchSmoothModeEnabled(bool isPinchSmoothModeEnabled) = 0;
    virtual void UpdateMediaPlayGestureAccess(bool isNeedGestureAccess) = 0;
    virtual void UpdateMultiWindowAccess(bool isMultiWindowAccessEnabled) = 0;
    virtual void UpdateAllowWindowOpenMethod(bool isAllowWindowOpenMethod) = 0;
    virtual void UpdateWebCursiveFont(const std::string& cursiveFontFamily) = 0;
    virtual void UpdateWebFantasyFont(const std::string& fantasyFontFamily) = 0;
    virtual void UpdateWebFixedFont(const std::string& fixedFontFamily) = 0;
    virtual void UpdateWebSansSerifFont(const std::string& sansSerifFontFamily) = 0;
    virtual void UpdateWebSerifFont(const std::string& serifFontFamily) = 0;
    virtual void UpdateWebStandardFont(const std::string& standardFontFamily) = 0;
    virtual void UpdateDefaultFixedFontSize(int32_t size) = 0;
    virtual void UpdateDefaultFontSize(int32_t defaultFontSize) = 0;
    virtual void UpdateMinFontSize(int32_t minFontSize) = 0;
    virtual void UpdateMinLogicalFontSize(int32_t minLogicalFontSize) = 0;
    virtual void UpdateBlockNetwork(bool isNetworkBlocked) = 0;
    virtual void UpdateHorizontalScrollBarAccess(bool isHorizontalScrollBarAccessEnabled) = 0;
    virtual void UpdateVerticalScrollBarAccess(bool isVerticalScrollBarAccessEnabled) = 0;
    virtual void UpdateScrollBarColor(const std::string& colorValue) = 0;
    virtual void LoadUrl() = 0;
    virtual void HandleTouchDown(const int32_t& id, const double& x, const double& y, bool from_overlay = false) = 0;
    virtual void HandleTouchUp(const int32_t& id, const double& x, const double& y, bool from_overlay = false) = 0;
    virtual void HandleTouchMove(const int32_t& id, const double& x, const double& y, bool from_overlay = false) = 0;
    virtual void HandleTouchCancel() = 0;
    virtual bool OnKeyEvent(int32_t keyCode, int32_t keyAction) = 0;
    virtual void OnMouseEvent(int32_t x, int32_t y, const MouseButton button, const MouseAction action, int count) = 0;
    virtual void OnFocus() = 0;
    virtual void OnBlur() = 0;
    virtual void UpdateLocale() = 0;
    virtual void SetDrawRect(int32_t x, int32_t y, int32_t width, int32_t height) = 0;
    virtual void OnInactive() = 0;
    virtual void OnActive() = 0;
    virtual void SetBackgroundColor(int32_t backgroundColor) = 0;
    virtual void OnPageStarted(const std::string& param) = 0;
    virtual void OnPageFinished(const std::string& param) = 0;
    virtual void OnPageError(const std::string& param) = 0;
    virtual void OnProgressChanged(const std::string& param) = 0;
    virtual void OnReceivedTitle(const std::string& param) = 0;
    virtual void OnPageVisible(const std::string& param) = 0;
    virtual void OnGeolocationPermissionsHidePrompt() = 0;
    virtual bool LoadDataWithRichText() = 0;
    virtual void SetNGWebPattern(const RefPtr<NG::WebPattern>& webPattern) = 0;
    virtual void SetBoundsOrResize(const Size& drawSize, const Offset& offset) = 0;
    virtual int GetWebId() = 0;
    virtual void MaximizeResize() = 0;
    virtual void UpdateOptimizeParserBudgetEnabled(const bool enable) = 0;
};
}
#endif