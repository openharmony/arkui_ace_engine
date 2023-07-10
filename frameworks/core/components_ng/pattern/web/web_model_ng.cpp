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

#include "core/components_ng/pattern/web/web_model_ng.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void WebModelNG::Create(const std::string& src, const RefPtr<WebController>& webController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
    pipeline->AddWindowSizeChangeCallback(nodeId);
    AddDragFrameNodeToManager();
}

void WebModelNG::Create(const std::string& src, std::function<void(int32_t)>&& setWebIdCallback,
    std::function<void(const std::string&)>&& setHapPathCallback, int32_t parentWebId, bool popup)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, setWebIdCallback]() { return AceType::MakeRefPtr<WebPattern>(src, std::move(setWebIdCallback)); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetPopup(popup);
    webPattern->SetSetWebIdCallback(std::move(setWebIdCallback));
    webPattern->SetSetHapPathCallback(std::move(setHapPathCallback));
    webPattern->SetParentNWebId(parentWebId);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
    pipeline->AddWindowSizeChangeCallback(nodeId);
    AddDragFrameNodeToManager();
}

void WebModelNG::SetCustomScheme(const std::string& cmdLine)
{
    if (!cmdLine.empty()) {
        auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
        CHECK_NULL_VOID(webPattern);
        webPattern->SetCustomScheme(cmdLine);
    }
}

void WebModelNG::SetOnCommonDialog(std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool { return func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnCommonDialogEvent(std::move(uiCallback), static_cast<DialogEventType>(dialogEventType));
}

void WebModelNG::SetOnConsoleLog(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto onConsole = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(context, false);
        bool result = false;
        context->PostSyncEvent([func, info, &result]() { result = func(info.get()); });
        return result;
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnConsoleEvent(std::move(onConsole));
}

void WebModelNG::SetOnPageStart(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageStartedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnPageFinish(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageFinishedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnProgressChange(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnProgressChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetOnTitleReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTitleReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFullScreenExit(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenExitEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFullScreenEnter(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenEnterEvent(std::move(uiCallback));
}

void WebModelNG::SetOnGeolocationHide(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationHideEvent(std::move(uiCallback));
}

void WebModelNG::SetOnGeolocationShow(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationShowEvent(std::move(uiCallback));
}

void WebModelNG::SetOnRequestFocus(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto instanceId = Container::CurrentId();

    auto uiCallback = [func, instanceId](const std::shared_ptr<BaseEventInfo>& info) {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent([info, func]() { func(info.get()); });
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRequestFocusEvent(std::move(uiCallback));
}

void WebModelNG::SetOnDownloadStart(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDownloadStartEvent(std::move(uiCallback));
}

void WebModelNG::SetOnHttpAuthRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool { return func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpAuthRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool { return func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslErrorRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnSslSelectCertRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool { return func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslSelectCertRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetMediaPlayGestureAccess(bool isNeedGestureAccess)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMediaPlayGestureAccess(isNeedGestureAccess);
}

void WebModelNG::SetOnKeyEvent(std::function<void(KeyEventInfo& keyEventInfo)>&& jsCallback)
{
    auto func = jsCallback;
    auto instanceId = Container::CurrentId();
    auto uiCallback = [func, instanceId](KeyEventInfo& keyEventInfo) {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostSyncEvent([&keyEventInfo, func]() { func(keyEventInfo); });
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnKeyEvent(std::move(uiCallback));
}

void WebModelNG::SetOnErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnErrorReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnHttpErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpErrorReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnUrlLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool { return func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnUrlLoadInterceptEvent(std::move(uiCallback));
}

void WebModelNG::SetOnLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool { return func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnLoadInterceptEvent(std::move(uiCallback));
}

void WebModelNG::SetOnInterceptRequest(std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> RefPtr<WebResponse> {
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnInterceptRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFileSelectorShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool { return func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFileSelectorShowEvent(std::move(uiCallback));
}

void WebModelNG::SetOnContextMenuShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool { return func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuShowEvent(std::move(uiCallback));
}

void WebModelNG::SetOnContextMenuHide(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuHideEvent(std::move(uiCallback));
}

void WebModelNG::SetJsEnabled(bool isJsEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateJsEnabled(isJsEnabled);
}

void WebModelNG::SetTextZoomRatio(int32_t textZoomRatioNum)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateTextZoomRatio(textZoomRatioNum);
}

void WebModelNG::SetFileAccessEnabled(bool isFileAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateFileAccessEnabled(isFileAccessEnabled);
}

void WebModelNG::SetOnLineImageAccessEnabled(bool isOnLineImageAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOnLineImageAccessEnabled(isOnLineImageAccessEnabled);
}

void WebModelNG::SetDomStorageAccessEnabled(bool isDomStorageAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void WebModelNG::SetImageAccessEnabled(bool isImageAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateImageAccessEnabled(isImageAccessEnabled);
}

void WebModelNG::SetMixedMode(MixedModeContent mixedContentMode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMixedMode(mixedContentMode);
}

void WebModelNG::SetZoomAccessEnabled(bool isZoomAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateZoomAccessEnabled(isZoomAccessEnabled);
}

void WebModelNG::SetGeolocationAccessEnabled(bool isGeolocationAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void WebModelNG::SetJsProxyCallback(std::function<void()>&& jsProxyCallback)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetJsProxyCallback(std::move(jsProxyCallback));
}

void WebModelNG::SetUserAgent(const std::string& userAgent)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateUserAgent(userAgent);
}

void WebModelNG::SetRenderExitedId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderExitedEvent(std::move(uiCallback));
}

void WebModelNG::SetRefreshAccessedHistoryId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRefreshAccessedHistoryEvent(std::move(uiCallback));
}

void WebModelNG::SetCacheMode(WebCacheMode cacheMode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateCacheMode(cacheMode);
}

void WebModelNG::SetOverviewModeAccessEnabled(bool isOverviewModeAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOverviewModeAccessEnabled(isOverviewModeAccessEnabled);
}

void WebModelNG::SetFileFromUrlAccessEnabled(bool isFileFromUrlAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateFileFromUrlAccessEnabled(isFileFromUrlAccessEnabled);
}

void WebModelNG::SetDatabaseAccessEnabled(bool isDatabaseAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDatabaseAccessEnabled(isDatabaseAccessEnabled);
}

void WebModelNG::SetWebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebDebuggingAccessEnabled(isWebDebuggingAccessEnabled);
}

void WebModelNG::SetOnMouseEvent(std::function<void(MouseInfo& info)>&& jsCallback)
{
    auto func = jsCallback;
    auto instanceId = Container::CurrentId();
    auto uiCallback = [func, instanceId](MouseInfo& info) {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostSyncEvent([&info, func]() { func(info); });
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnMouseEvent(std::move(uiCallback));
}

void WebModelNG::SetResourceLoadId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnResourceLoadEvent(std::move(uiCallback));
}

void WebModelNG::SetScaleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScaleChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScrollEvent(std::move(uiCallback));
}

void WebModelNG::SetPermissionRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPermissionRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetScreenCaptureRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScreenCaptureRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetBackgroundColor(Color backgroundColor)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateBackgroundColor(backgroundColor.GetValue());
}

void WebModelNG::InitialScale(float scale)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateInitialScale(scale);
}

void WebModelNG::SetSearchResultReceiveEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSearchResultReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnDragStart(
    std::function<NG::DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)>&&
        onDragStart)
{
    auto dragStart = [dragStartFunc = std::move(onDragStart)](
                         const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> DragDropInfo {
        auto dragInfo = dragStartFunc(event, extraParams);
        DragDropInfo info;
        info.extraInfo = dragInfo.extraInfo;
        info.pixelMap = dragInfo.pixelMap;
        info.customNode = AceType::DynamicCast<UINode>(dragInfo.node);
        return info;
    };
    ViewAbstract::SetOnDragStart(std::move(dragStart));
}

void WebModelNG::SetOnDragEnter(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragEnter)
{
    ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
}

void WebModelNG::SetOnDragMove(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)>&& onDragMoveId)
{
    ViewAbstract::SetOnDragMove(std::move(onDragMoveId));
}

void WebModelNG::SetOnDragLeave(
    std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragLeave)
{
    ViewAbstract::SetOnDrop(std::move(onDragLeave));
}

void WebModelNG::SetOnDrop(std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDropId)
{
    ViewAbstract::SetOnDrop(std::move(onDropId));
}

void WebModelNG::SetPinchSmoothModeEnabled(bool isPinchSmoothModeEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdatePinchSmoothModeEnabled(isPinchSmoothModeEnabled);
}

void WebModelNG::SetWindowNewEvent(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& jsCallback)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowNewEvent(std::move(jsCallback));
}

void WebModelNG::SetWindowExitEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowExitEvent(std::move(uiCallback));
}

void WebModelNG::SetMultiWindowAccessEnabled(bool isMultiWindowAccessEnable)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMultiWindowAccessEnabled(isMultiWindowAccessEnable);
}

void WebModelNG::SetAllowWindowOpenMethod(bool isAllowWindowOpenMethod)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateAllowWindowOpenMethod(isAllowWindowOpenMethod);
}

void WebModelNG::SetWebCursiveFont(const std::string& cursiveFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebCursiveFont(cursiveFontFamily);
}

void WebModelNG::SetWebFantasyFont(const std::string& fantasyFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebFantasyFont(fantasyFontFamily);
}

void WebModelNG::SetWebFixedFont(const std::string& fixedFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebFixedFont(fixedFontFamily);
}

void WebModelNG::SetWebSansSerifFont(const std::string& sansSerifFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebSansSerifFont(sansSerifFontFamily);
}

void WebModelNG::SetWebSerifFont(const std::string& serifFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebSerifFont(serifFontFamily);
}

void WebModelNG::SetWebStandardFont(const std::string& standardFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebStandardFont(standardFontFamily);
}

void WebModelNG::SetDefaultFixedFontSize(int32_t defaultFixedFontSize)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultFixedFontSize(defaultFixedFontSize);
}

void WebModelNG::SetDefaultFontSize(int32_t defaultFontSize)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultFontSize(defaultFontSize);
}

void WebModelNG::SetMinFontSize(int32_t minFontSize)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMinFontSize(minFontSize);
}

void WebModelNG::SetMinLogicalFontSize(int32_t minLogicalFontSize)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMinLogicalFontSize(minLogicalFontSize);
}

void WebModelNG::SetBlockNetwork(bool isNetworkBlocked)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateBlockNetwork(isNetworkBlocked);
}

void WebModelNG::SetPageVisibleId(OnWebAsyncFunc&& pageVisibleId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageVisibleEvent(std::move(pageVisibleId));
}

void WebModelNG::SetOnInterceptKeyEventCallback(std::function<bool(KeyEventInfo& keyEventInfo)>&& keyEventInfo)
{
    auto func = keyEventInfo;
    auto instanceId = Container::CurrentId();
    auto onConsole = [func, instanceId](KeyEventInfo& keyEventInfo) -> bool {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        bool result = false;
        CHECK_NULL_RETURN(context, result);
        context->PostSyncEvent([func, &keyEventInfo, &result]() { result = func(keyEventInfo); });
        return result;
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPreKeyEvent(std::move(onConsole));
}

void WebModelNG::SetOnDataResubmitted(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& dataResubmittedId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDataResubmittedEvent(std::move(dataResubmittedId));
}

void WebModelNG::SetDataResubmittedId(OnWebAsyncFunc&& dataResubmittedId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDataResubmittedEvent(std::move(dataResubmittedId));
}

void WebModelNG::SetFaviconReceivedId(OnWebAsyncFunc&& faviconReceivedId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFaviconReceivedEvent(std::move(faviconReceivedId));
}

void WebModelNG::SetAudioStateChangedId(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& audioStateChanged)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAudioStateChangedEvent(std::move(audioStateChanged));
}

void WebModelNG::SetFirstContentfulPaintId(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstContentfulPaintId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFirstContentfulPaintEvent(std::move(firstContentfulPaintId));
}

void WebModelNG::SetTouchIconUrlId(OnWebAsyncFunc&& touchIconUrlId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTouchIconUrlEvent(std::move(touchIconUrlId));
}

void WebModelNG::SetDarkMode(WebDarkMode mode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDarkMode(mode);
}

void WebModelNG::SetForceDarkAccess(bool access)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateForceDarkAccess(access);
}

void WebModelNG::SetHorizontalScrollBarAccessEnabled(bool isHorizontalScrollBarAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateHorizontalScrollBarAccessEnabled(isHorizontalScrollBarAccessEnabled);
}

void WebModelNG::SetVerticalScrollBarAccessEnabled(bool isVerticalScrollBarAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateVerticalScrollBarAccessEnabled(isVerticalScrollBarAccessEnabled);
}

void WebModelNG::SetOnControllerAttached(std::function<void()>&& callback)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetOnControllerAttachedCallback(std::move(callback));
}

void WebModelNG::NotifyPopupWindowResult(int32_t webId, bool result)
{
    if (webId != -1) {
        std::weak_ptr<OHOS::NWeb::NWeb> nwebWeak = OHOS::NWeb::NWebHelper::Instance().GetNWeb(webId);
        auto nwebSptr = nwebWeak.lock();
        if (nwebSptr) {
            nwebSptr->NotifyPopupWindowResult(result);
        }
    }
}

void WebModelNG::AddDragFrameNodeToManager()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    dragDropManager->AddDragFrameNode(frameNode);
}

void WebModelNG::SetAudioResumeInterval(int32_t resumeInterval)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateAudioResumeInterval(resumeInterval);
}
void WebModelNG::SetAudioExclusive(bool audioExclusive)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateAudioExclusive(audioExclusive);
}

void WebModelNG::SetOverScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnOverScrollEvent(std::move(uiCallback));
}
} // namespace OHOS::Ace::NG
