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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_WEB_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_WEB_MODEL_IMPL_H

#include "base/memory/referenced.h"
#include "core/components/web/web_component.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/web/web_model.h"

namespace OHOS::Ace::Framework {
class WebModelImpl : public OHOS::Ace::WebModel {
public:
    void Create(const std::string& src, const RefPtr<WebController>& webController,
        RenderMode renderMode = RenderMode::ASYNC_RENDER, bool incognitoMode = false,
        const std::string& sharedRenderProcessToken = "") override;
    void Create(const std::string& src, std::function<void(int32_t)>&& setWebIdCallback,
        std::function<void(const std::string&)>&& setHapPathCallback,
        int32_t parentWebId, bool popup, RenderMode renderMode = RenderMode::ASYNC_RENDER,
        bool incognitoMode = false, const std::string& sharedRenderProcessToken = "") override;
    void SetCustomScheme(const std::string& cmdLine) override;
    void SetFocusable(bool focusable) override;
    void SetFocusNode(bool isFocusNode) override;

    void SetOnCommonDialog(std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType) override;
    void SetOnConsoleLog(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnPageStart(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnPageFinish(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnProgressChange(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnTitleReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnFullScreenExit(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnFullScreenEnter(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnGeolocationHide(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnGeolocationShow(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnRequestFocus(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnDownloadStart(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnHttpAuthRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnAllSslErrorRequest(std::function<bool(const BaseEventInfo *info)> &&jsCallback) override;
    void SetOnSslSelectCertRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetMediaPlayGestureAccess(bool isNeedGestureAccess) override;
    void SetOnKeyEvent(std::function<void(KeyEventInfo& keyEventInfo)>&& jsCallback) override;
    void SetOnErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnHttpErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnInterceptRequest(std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnUrlLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnFileSelectorShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnContextMenuShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnContextMenuHide(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetJsEnabled(bool isJsEnabled) override;
    void SetFileAccessEnabled(bool isFileAccessEnabled) override;
    void SetOnLineImageAccessEnabled(bool isOnLineImageAccessEnabled) override;
    void SetDomStorageAccessEnabled(bool isDomStorageAccessEnabled) override;
    void SetImageAccessEnabled(bool isImageAccessEnabled) override;
    void SetMixedMode(MixedModeContent mixedMode) override;
    void SetZoomAccessEnabled(bool isZoomAccessEnabled) override;
    void SetGeolocationAccessEnabled(bool isGeolocationAccessEnabled) override;
    void SetJsProxyCallback(std::function<void()>&& jsProxyCallback) override;
    void SetUserAgent(const std::string& userAgent) override;
    void SetRenderExitedId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetRefreshAccessedHistoryId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetCacheMode(WebCacheMode cacheMode) override;
    void SetOverviewModeAccessEnabled(bool isOverviewModeAccessEnabled) override;
    void SetFileFromUrlAccessEnabled(bool isFileFromUrlAccessEnabled) override;
    void SetDatabaseAccessEnabled(bool isDatabaseAccessEnabled) override;
    void SetTextZoomRatio(int32_t textZoomRatioNum) override;
    void SetWebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled) override;
    void SetOnMouseEvent(std::function<void(MouseInfo& info)>&& jsCallback) override;
    void SetResourceLoadId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetScaleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetPermissionRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetBackgroundColor(Color backgroundColor) override;
    void InitialScale(float scale) override;
    void SetSearchResultReceiveEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;

    void SetOnDragStart(
        std::function<NG::DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)>&&
            onDragStart) override;
    void SetOnDragEnter(
        std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragEnter) override;
    void SetOnDragMove(std::function<void(const RefPtr<DragEvent>&, const std::string&)>&& onDragMoveId) override;
    void SetOnDragLeave(std::function<void(const RefPtr<DragEvent>&, const std::string&)>&& onDragLeave) override;
    void SetOnDrop(std::function<void(const RefPtr<DragEvent>&, const std::string&)>&& onDropId) override;

    void SetPinchSmoothModeEnabled(bool isPinchSmoothModeEnabled) override;
    void SetWindowNewEvent(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& jsCallback) override;
    void SetWindowExitEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetMultiWindowAccessEnabled(bool isMultiWindowAccessEnable) override;
    void SetAllowWindowOpenMethod(bool isAllowWindowOpenMethod) override;
    void SetOnInterceptKeyEventCallback(std::function<bool(KeyEventInfo& keyEventInfo)>&& keyEventInfo) override;
    void SetOverScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOverScrollMode(OverScrollMode mode) override;
    void SetCopyOptionMode(CopyOptions mode) override;
    void SetNativeEmbedModeEnabled(bool isEmbedModeEnabled) override;
    void RegisterNativeEmbedRule(const std::string& tag, const std::string& type) override;
    void SetNativeEmbedLifecycleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeEmbedVisibilityChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeEmbedGestureEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnOverrideUrlLoading(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeVideoPlayerConfig(bool enable, bool shouldOverlay) override;
    void SetSmoothDragResizeEnabled(bool isSmoothDragResizeEnabled) override;
    void SetRenderProcessNotRespondingId(std::function<void(const BaseEventInfo* info)> && jsCallback) override;
    void SetRenderProcessRespondingId(std::function<void(const BaseEventInfo* info)> && jsCallback) override;
    void SetViewportFitChangedId(std::function<void(const BaseEventInfo* info)> && jsCallback) override;
    void SetAdsBlockedEventId(std::function<void(const BaseEventInfo* info)> && jsCallback) override;
    void SetUpdateInstanceIdCallback(std::function<void(int32_t)> &&callback) override;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_WEB_MODEL_IMPL_H
