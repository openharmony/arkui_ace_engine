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

#include "bridge/declarative_frontend/jsview/models/web_model_impl.h"

namespace OHOS::Ace::Framework {
void WebModelImpl::Create(const std::string& src, const RefPtr<WebController>& webController,
    RenderMode /* renderMode */, bool incognitoMode, const std::string& sharedRenderProcessToken)
{
    RefPtr<WebComponent> webComponent;
    webComponent = AceType::MakeRefPtr<WebComponent>(src);
    CHECK_NULL_VOID(webComponent);

    webComponent->SetSrc(src);
    webComponent->SetWebController(webController);
    webComponent->SetIncognitoMode(incognitoMode);
    webComponent->SetSharedRenderProcessToken(sharedRenderProcessToken);

    ViewStackProcessor::GetInstance()->Push(webComponent);
}

void WebModelImpl::Create(const std::string& src, std::function<void(int32_t)>&& setWebIdCallback,
    std::function<void(const std::string&)>&& setHapPathCallback, int32_t parentWebId, bool popup,
    RenderMode /* renderMode */, bool incognitoMode, const std::string& sharedRenderProcessToken)
{
    RefPtr<WebComponent> webComponent;
    webComponent = AceType::MakeRefPtr<WebComponent>(src);
    CHECK_NULL_VOID(webComponent);

    webComponent->SetSrc(src);
    webComponent->SetPopup(popup);
    webComponent->SetParentNWebId(parentWebId);
    webComponent->SetSetWebIdCallback(std::move(setWebIdCallback));
    webComponent->SetSetHapPathCallback(std::move(setHapPathCallback));
    webComponent->SetIncognitoMode(incognitoMode);
    webComponent->SetSharedRenderProcessToken(sharedRenderProcessToken);

    ViewStackProcessor::GetInstance()->Push(webComponent);
}

void WebModelImpl::SetCustomScheme(const std::string& cmdLine)
{
    if (!cmdLine.empty()) {
        auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        CHECK_NULL_VOID(webComponent);
        webComponent->SetCustomScheme(cmdLine);
    }
}

void WebModelImpl::SetFocusable(bool focusable)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    ViewStackProcessor::GetInstance()->Push(webComponent);

    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    CHECK_NULL_VOID(focusableComponent);
    focusableComponent->SetFocusable(focusable);
}

void WebModelImpl::SetFocusNode(bool isFocusNode)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    CHECK_NULL_VOID(focusableComponent);
    focusableComponent->SetFocusNode(isFocusNode);
}

void WebModelImpl::SetOnCommonDialog(std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnCommonDialogImpl(std::move(jsCallback), static_cast<DialogEventType>(dialogEventType));
}

void WebModelImpl::SetOnConsoleLog(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnConsoleImpl(std::move(jsCallback));
}

void WebModelImpl::SetOnPageStart(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetPageStartedEventId(eventMarker);
}

void WebModelImpl::SetOnPageFinish(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetPageFinishedEventId(eventMarker);
}

void WebModelImpl::SetOnProgressChange(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetProgressChangeImpl(std::move(jsCallback));
}

void WebModelImpl::SetOnTitleReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetTitleReceiveEventId(eventMarker);
}

void WebModelImpl::SetOnFullScreenExit(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetOnFullScreenExitEventId(eventMarker);
}

void WebModelImpl::SetOnFullScreenEnter(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnFullScreenEnterImpl(std::move(jsCallback));
}

void WebModelImpl::SetOnGeolocationHide(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetGeolocationHideEventId(eventMarker);
}

void WebModelImpl::SetOnGeolocationShow(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetGeolocationShowEventId(eventMarker);
}

void WebModelImpl::SetOnRequestFocus(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetRequestFocusEventId(eventMarker);
}

void WebModelImpl::SetOnDownloadStart(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetDownloadStartEventId(eventMarker);
}

void WebModelImpl::SetOnHttpAuthRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnHttpAuthRequestImpl(std::move(jsCallback));
}

void WebModelImpl::SetOnSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnSslErrorRequestImpl(std::move(jsCallback));
}

void WebModelImpl::SetOnAllSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnAllSslErrorRequestImpl(std::move(jsCallback));
}

void WebModelImpl::SetOnSslSelectCertRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnSslSelectCertRequestImpl(std::move(jsCallback));
}

void WebModelImpl::SetMediaPlayGestureAccess(bool isNeedGestureAccess)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetMediaPlayGestureAccess(isNeedGestureAccess);
}

void WebModelImpl::SetOnKeyEvent(std::function<void(KeyEventInfo& keyEventInfo)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnKeyEventCallback(std::move(jsCallback));
}

void WebModelImpl::SetOnErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetPageErrorEventId(eventMarker);
}

void WebModelImpl::SetOnHttpErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetHttpErrorEventId(eventMarker);
}

void WebModelImpl::SetOnInterceptRequest(std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnInterceptRequest(std::move(jsCallback));
}

void WebModelImpl::SetOnUrlLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnUrlLoadIntercept(std::move(jsCallback));
}

void WebModelImpl::SetOnLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnLoadIntercept(std::move(jsCallback));
}

void WebModelImpl::SetOnFileSelectorShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnFileSelectorShow(std::move(jsCallback));
}

void WebModelImpl::SetOnContextMenuShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnContextMenuShow(std::move(jsCallback));
}

void WebModelImpl::SetOnContextMenuHide(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnContextMenuHide(std::move(jsCallback));
}

void WebModelImpl::SetJsEnabled(bool isJsEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetJsEnabled(isJsEnabled);
}

void WebModelImpl::SetFileAccessEnabled(bool isJsEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetFileAccessEnabled(isJsEnabled);
}

void WebModelImpl::SetOnLineImageAccessEnabled(bool isOnLineImageAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnLineImageAccessEnabled(!isOnLineImageAccessEnabled);
}

void WebModelImpl::SetDomStorageAccessEnabled(bool isDomStorageAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void WebModelImpl::SetImageAccessEnabled(bool isImageAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetImageAccessEnabled(isImageAccessEnabled);
}

void WebModelImpl::SetMixedMode(MixedModeContent mixedMode)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetMixedMode(mixedMode);
}

void WebModelImpl::SetZoomAccessEnabled(bool isZoomAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetZoomAccessEnabled(isZoomAccessEnabled);
}

void WebModelImpl::SetGeolocationAccessEnabled(bool isGeolocationAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void WebModelImpl::SetJsProxyCallback(std::function<void()>&& jsProxyCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetJsProxyCallback(std::move(jsProxyCallback));
}

void WebModelImpl::SetUserAgent(const std::string& userAgent)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetUserAgent(userAgent);
}

void WebModelImpl::SetRenderExitedId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetRenderExitedId(eventMarker);
}

void WebModelImpl::SetRefreshAccessedHistoryId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetRefreshAccessedHistoryId(eventMarker);
}

void WebModelImpl::SetCacheMode(WebCacheMode cacheMode)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetCacheMode(cacheMode);
}

void WebModelImpl::SetOverScrollMode(OverScrollMode mode)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOverScrollMode(mode);
}

void WebModelImpl::SetCopyOptionMode(CopyOptions mode)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetCopyOptionMode(mode);
}

void WebModelImpl::SetOverviewModeAccessEnabled(bool isOverviewModeAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOverviewModeAccessEnabled(isOverviewModeAccessEnabled);
}

void WebModelImpl::SetFileFromUrlAccessEnabled(bool isFileFromUrlAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetFileFromUrlAccessEnabled(isFileFromUrlAccessEnabled);
}

void WebModelImpl::SetDatabaseAccessEnabled(bool isDatabaseAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetDatabaseAccessEnabled(isDatabaseAccessEnabled);
}

void WebModelImpl::SetTextZoomRatio(int32_t textZoomRatioNum)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetTextZoomRatio(textZoomRatioNum);
}

void WebModelImpl::SetWebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetWebDebuggingAccessEnabled(isWebDebuggingAccessEnabled);
}

void WebModelImpl::SetOnMouseEvent(std::function<void(MouseInfo& info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnMouseEventCallback(std::move(jsCallback));
}

void WebModelImpl::SetResourceLoadId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetResourceLoadId(eventMarker);
}

void WebModelImpl::SetScaleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetScaleChangeId(eventMarker);
}

void WebModelImpl::SetScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetScrollId(eventMarker);
}

void WebModelImpl::SetPermissionRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetPermissionRequestEventId(eventMarker);
}

void WebModelImpl::SetBackgroundColor(Color backgroundColor)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetBackgroundColor(backgroundColor.GetValue());
}

void WebModelImpl::InitialScale(float scale)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetInitialScale(scale);
}

void WebModelImpl::SetSearchResultReceiveEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetSearchResultReceiveEventId(eventMarker);
}

void WebModelImpl::SetOnDragStart(
    std::function<NG::DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams)>&&
        onDragStart)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto onDragStartId = [dragStartFunc = std::move(onDragStart)](
                             const RefPtr<DragEvent>& event, const std::string& extraParams) -> DragItemInfo {
        auto dragInfo = dragStartFunc(event, extraParams);
        DragItemInfo info;
        info.extraInfo = dragInfo.extraInfo;
        info.pixelMap = dragInfo.pixelMap;
        info.customComponent = AceType::DynamicCast<Component>(dragInfo.node);
        return info;
    };
    webComponent->SetOnDragStartId(onDragStartId);
}

void WebModelImpl::SetOnDragEnter(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragStart)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnDragEnterId(onDragStart);
}

void WebModelImpl::SetOnDragMove(std::function<void(const RefPtr<DragEvent>&, const std::string&)>&& onDragMoveId)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnDragMoveId(onDragMoveId);
}

void WebModelImpl::SetOnDragLeave(std::function<void(const RefPtr<DragEvent>&, const std::string&)>&& onDragLeave)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnDragLeaveId(onDragLeave);
}

void WebModelImpl::SetOnDrop(std::function<void(const RefPtr<DragEvent>&, const std::string&)>&& onDropId)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnDropId(onDropId);
}

void WebModelImpl::SetPinchSmoothModeEnabled(bool isPinchSmoothModeEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetPinchSmoothModeEnabled(isPinchSmoothModeEnabled);
}

void WebModelImpl::SetWindowNewEvent(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetWindowNewEvent(std::move(jsCallback));
}

void WebModelImpl::SetWindowExitEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));
    webComponent->SetWindowExitEventId(eventMarker);
}

void WebModelImpl::SetMultiWindowAccessEnabled(bool isMultiWindowAccessEnable)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetMultiWindowAccessEnabled(isMultiWindowAccessEnable);
}

void WebModelImpl::SetAllowWindowOpenMethod(bool isAllowWindowOpenMethod)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetAllowWindowOpenMethod(isAllowWindowOpenMethod);
}

void WebModelImpl::SetOnInterceptKeyEventCallback(std::function<bool(KeyEventInfo& keyEventInfo)>&& keyEventInfo)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnInterceptKeyEventCallback(keyEventInfo);
}

void WebModelImpl::SetOverScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetOverScrollId(eventMarker);
}

void WebModelImpl::SetNativeEmbedModeEnabled(bool isEmbedModeEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetNativeEmbedModeEnabled(isEmbedModeEnabled);
}

void WebModelImpl::RegisterNativeEmbedRule(const std::string& tag, const std::string& type)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->RegisterNativeEmbedRule(tag, type);
}

void WebModelImpl::SetNativeEmbedLifecycleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetNativeEmbedLifecycleChangeId(eventMarker);
}

void WebModelImpl::SetNativeEmbedVisibilityChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetNativeEmbedVisibilityChangeId(eventMarker);
}

void WebModelImpl::SetNativeEmbedGestureEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetNativeEmbedGestureEventId(eventMarker);
}

void WebModelImpl::SetOnOverrideUrlLoading(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetOnOverrideUrlLoading(std::move(jsCallback));
}

void WebModelImpl::SetNativeVideoPlayerConfig(bool enable, bool shouldOverlay)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetNativeVideoPlayerConfig(enable, shouldOverlay);
}

void WebModelImpl::SetSmoothDragResizeEnabled(bool isSmoothDragResizeEnabled)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    webComponent->SetSmoothDragResizeEnabled(isSmoothDragResizeEnabled);
}

void WebModelImpl::SetRenderProcessNotRespondingId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetRenderProcessNotRespondingId(eventMarker);
}

void WebModelImpl::SetRenderProcessRespondingId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetRenderProcessRespondingId(eventMarker);
}

void WebModelImpl::SetViewportFitChangedId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetViewportFitChangedId(eventMarker);
}

void WebModelImpl::SetAdsBlockedEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(webComponent);
    auto eventMarker = EventMarker(std::move(jsCallback));

    webComponent->SetAdsBlockedEventId(eventMarker);
}

void WebModelImpl::SetUpdateInstanceIdCallback(std::function<void(int32_t)>&& callback)
{
}
} // namespace OHOS::Ace::Framework
