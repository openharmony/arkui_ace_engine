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

#ifndef FOUNDATION_ACE_FRAMEWORKS_WEB_PATTERN_WEB_DELEGATE_CROSS_H
#define FOUNDATION_ACE_FRAMEWORKS_WEB_PATTERN_WEB_DELEGATE_CROSS_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/web/web_delegate_interface.h"
#include "core/components_ng/pattern/web/cross_platform/web_resource.h"
#include "core/pipeline/pipeline_base.h"
#include "core/common/container.h"

#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"

namespace OHOS::Ace {
class WebResourceRequsetImpl : public AceType {
    DECLARE_ACE_TYPE(WebResourceRequsetImpl, AceType);
public:
    explicit WebResourceRequsetImpl(void* object) : object_(object) {}
    std::map<std::string, std::string> GetRequestHeader() const;
    std::string GetRequestUrl() const;
    std::string GetMethod() const;
    bool IsRequestGesture() const;
    bool IsMainFrame() const;
    bool IsRedirect() const;
private:
    void* object_ = nullptr;
};

class WebResourceErrorImpl : public AceType {
    DECLARE_ACE_TYPE(WebResourceErrorImpl, AceType);
public:
    explicit WebResourceErrorImpl(void* object) : object_(object) {}
    std::string GetErrorInfo() const;
    int GetErrorCode() const;
private:
    void* object_ = nullptr;
};

class WebDelegateCross : public WebDelegateInterface,
                         public WebResource {
    DECLARE_ACE_TYPE(WebDelegateCross, WebResource);
public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using EventCallback = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;
    enum class State : char {
        WAITINGFORSIZE,
        CREATING,
        CREATED,
        CREATEFAILED,
        RELEASED,
    };

    WebDelegateCross() = delete;
    ~WebDelegateCross() override;
    WebDelegateCross(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError, const std::string& type)
        : WebResource(type, context, std::move(onError)), context_(context), instanceId_(Container::CurrentId())
    {}

    void CreatePlatformResource(const Size& size, const Offset& position,
        const WeakPtr<NG::PipelineContext>& context) override;
    void SetNGWebPattern(const RefPtr<NG::WebPattern>& webPattern) override
    {
        webPattern_ = webPattern;
    }
    int GetWebId() override;
    void HandleTouchDown(const int32_t& id, const double& x, const double& y, bool from_overlay) override;
    void HandleTouchUp(const int32_t& id, const double& x, const double& y, bool from_overlay) override;
    void HandleTouchMove(const int32_t& id, const double& x, const double& y, bool from_overlay) override;
    void HandleTouchCancel() override;
    bool OnKeyEvent(int32_t keyCode, int32_t keyAction) override;
    void OnMouseEvent(int32_t x, int32_t y, const MouseButton button, const MouseAction action, int count) override;
    void OnFocus() override;
    void OnBlur() override;
    void UpdateLocale() override;
    void OnInactive() override;
    void OnActive() override;
    void ShowWebView() override;
    void HideWebView() override;
    void OnPageStarted(const std::string& param) override;
    void OnPageFinished(const std::string& param) override;
    void OnPageError(const std::string& param) override;

    void UpdateUserAgent(const std::string& userAgent) override;
    void UpdateBackgroundColor(const int backgroundColor) override;
    void UpdateInitialScale(float scale) override;
    void UpdateJavaScriptEnabled(const bool& isJsEnabled) override;
    void UpdateAllowFileAccess(const bool& isFileAccessEnabled) override;
    void UpdateBlockNetworkImage(const bool& onLineImageAccessEnabled) override;
    void UpdateLoadsImagesAutomatically(const bool& isImageAccessEnabled) override;
    void UpdateMixedContentMode(const MixedModeContent& mixedMode) override;
    void UpdateSupportZoom(const bool& isZoomAccessEnabled) override;
    void UpdateDomStorageEnabled(const bool& isDomStorageAccessEnabled) override;
    void UpdateGeolocationEnabled(const bool& isGeolocationAccessEnabled) override;
    void UpdateCacheMode(const WebCacheMode& mode) override;
    void UpdateDarkMode(const WebDarkMode& mode) override;
    void UpdateForceDarkAccess(const bool& access) override;
    void UpdateAudioResumeInterval(const int32_t& resumeInterval) override;
    void UpdateAudioExclusive(const bool& audioExclusive) override;
    void UpdateOverviewModeEnabled(const bool& isOverviewModeAccessEnabled) override;
    void UpdateFileFromUrlEnabled(const bool& isFileFromUrlAccessEnabled) override;
    void UpdateDatabaseEnabled(const bool& isDatabaseAccessEnabled) override;
    void UpdateTextZoomRatio(const int32_t& textZoomRatioNum) override;
    void UpdateWebDebuggingAccess(bool isWebDebuggingAccessEnabled) override;
    void UpdatePinchSmoothModeEnabled(bool isPinchSmoothModeEnabled) override;
    void UpdateMediaPlayGestureAccess(bool isNeedGestureAccess) override;
    void UpdateMultiWindowAccess(bool isMultiWindowAccessEnabled) override;
    void UpdateAllowWindowOpenMethod(bool isAllowWindowOpenMethod) override;
    void UpdateWebCursiveFont(const std::string& cursiveFontFamily) override;
    void UpdateWebFantasyFont(const std::string& fantasyFontFamily) override;
    void UpdateWebFixedFont(const std::string& fixedFontFamily) override;
    void UpdateWebSansSerifFont(const std::string& sansSerifFontFamily) override;
    void UpdateWebSerifFont(const std::string& serifFontFamily) override;
    void UpdateWebStandardFont(const std::string& standardFontFamily) override;
    void UpdateDefaultFixedFontSize(int32_t size) override;
    void UpdateDefaultFontSize(int32_t defaultFontSize) override;
    void UpdateMinFontSize(int32_t minFontSize) override;
    void UpdateMinLogicalFontSize(int32_t minLogicalFontSize) override;
    void UpdateBlockNetwork(bool isNetworkBlocked) override;
    void UpdateHorizontalScrollBarAccess(bool isHorizontalScrollBarAccessEnabled) override;
    void UpdateVerticalScrollBarAccess(bool isVerticalScrollBarAccessEnabled) override;
    void UpdateScrollBarColor(const std::string& colorValue) override;
    void LoadUrl() override;
    void SetBackgroundColor(int32_t backgroundColor) override;

    bool LoadDataWithRichText() override;

    void SetBoundsOrResize(const Size& drawSize, const Offset& offset) override;
private:
    void ReleasePlatformResource();
    void CreatePluginResource(const Size& size, const Offset& position, const WeakPtr<NG::PipelineContext>& context);
    void InitWebEvent();
    void RegisterWebEvent();
    void RegisterWebObjectEvent();
    void OnErrorReceive(void* object);

    WeakPtr<NG::WebPattern> webPattern_;
    WeakPtr<PipelineBase> context_;

    State state_ { State::WAITINGFORSIZE };

    Method reloadMethod_;
    Method updateUrlMethod_;
    Method routerBackMethod_;
    Method changePageUrlMethod_;
    Method isPagePathInvalidMethod_;
    Method backwardMethod_;
    Method forwardMethod_;
    Method clearHistoryMethod_;
    Method getHitTestMethod_;
    Method onActiveMethod_;
    Method onInactiveMethod_;
    Method refreshMethod_;
    Method stopLoadingMethod_;
    Method requestFocusMethod_;
    Method accessBackwardMethod_;
    Method accessForwardMethod_;
    Method accessStepMethod_;
    Method setWebViewJavaScriptResultCallBackMethod_;
    Method registerJavaScriptProxyMethod_;
    Method runTypeScriptMethod_;
    Method deleteJavaScriptInterfaceMethod_;
    Method loadUrlMethod_;
    Method loadDataMethod_;
    Method updateAttributeMethod_;
    Method saveCookieSyncMethod_;
    Method setCookieMethod_;
    Method touchDownMethod_;
    Method touchUpMethod_;
    Method touchMoveMethod_;
    Method touchCancelMethod_;
    Method updateLayoutMethod_;
    Method zoomMethod_;

    Method updateZoomAccess_;
    Method updateJavaScriptEnabled_;

    EventCallbackV2 onPageFinishedV2_;
    EventCallbackV2 onPageStartedV2_;
    EventCallbackV2 onProgressChangeV2_;

    int instanceId_ = -1;
};
}

#endif