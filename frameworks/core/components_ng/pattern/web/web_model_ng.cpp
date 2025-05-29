/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "base/utils/utils.h"
#include "core/components_ng/base/node_flag.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "nweb_helper.h"
#endif

namespace OHOS::Ace::NG {
void WebModelNG::Create(const std::string& src, const RefPtr<WebController>& webController, RenderMode renderMode,
    bool incognitoMode, const std::string& sharedRenderProcessToken)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::WEB_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, webController, renderMode, incognitoMode, sharedRenderProcessToken]() {
            return AceType::MakeRefPtr<WebPattern>(
                src, webController, renderMode, incognitoMode, sharedRenderProcessToken);
        });
    frameNode->AddFlag(NodeFlag::WEB_TAG);
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetNestedScrollExt(NestedScrollOptionsExt({
            .scrollUp = NestedScrollMode::SELF_FIRST,
            .scrollDown = NestedScrollMode::SELF_FIRST,
            .scrollLeft = NestedScrollMode::SELF_FIRST,
            .scrollRight = NestedScrollMode::SELF_FIRST,
        }));
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
    webPattern->SetRenderMode(renderMode);
    webPattern->SetIncognitoMode(incognitoMode);
    webPattern->SetSharedRenderProcessToken(sharedRenderProcessToken);
}

void WebModelNG::Create(const std::string& src, std::function<void(int32_t)>&& setWebIdCallback,
    std::function<void(const std::string&)>&& setHapPathCallback, int32_t parentWebId, bool popup,
    RenderMode renderMode, bool incognitoMode, const std::string& sharedRenderProcessToken)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, setWebIdCallback, renderMode, incognitoMode, sharedRenderProcessToken]() {
            return AceType::MakeRefPtr<WebPattern>(
                src, std::move(setWebIdCallback), renderMode, incognitoMode, sharedRenderProcessToken);
        });
    frameNode->AddFlag(NodeFlag::WEB_TAG);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetNestedScrollExt(NestedScrollOptionsExt({
            .scrollUp = NestedScrollMode::SELF_FIRST,
            .scrollDown = NestedScrollMode::SELF_FIRST,
            .scrollLeft = NestedScrollMode::SELF_FIRST,
            .scrollRight = NestedScrollMode::SELF_FIRST,
        }));
    webPattern->SetWebSrc(src);
    webPattern->SetPopup(popup);
    webPattern->SetSetWebIdCallback(std::move(setWebIdCallback));
    webPattern->SetSetHapPathCallback(std::move(setHapPathCallback));
    webPattern->SetParentNWebId(parentWebId);
    webPattern->SetRenderMode(renderMode);
    webPattern->SetIncognitoMode(incognitoMode);
    webPattern->SetSharedRenderProcessToken(sharedRenderProcessToken);
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
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnCommonDialogEvent(std::move(uiCallback), static_cast<DialogEventType>(dialogEventType));
}

void WebModelNG::SetOnConsoleLog(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto onConsole = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_RETURN(context, false);
        bool result = false;
        context->PostSyncEvent([func, info, &result]() { result = func(info.get()); }, "ArkUIWebConsoleLogCallback");
        return result;
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnConsoleEvent(std::move(onConsole));
}

void WebModelNG::SetOnPageStart(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageStartedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnPageFinish(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageFinishedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnProgressChange(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnProgressChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetOnTitleReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTitleReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFullScreenExit(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenExitEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFullScreenEnter(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenEnterEvent(std::move(uiCallback));
}

void WebModelNG::SetOnGeolocationHide(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationHideEvent(std::move(uiCallback));
}

void WebModelNG::SetOnGeolocationShow(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationShowEvent(std::move(uiCallback));
}

void WebModelNG::SetOnRequestFocus(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    WeakPtr<NG::FrameNode> weak = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

    auto uiCallback = [func, weak](const std::shared_ptr<BaseEventInfo>& info) {
        auto frameNode = weak.Upgrade();
        int32_t instanceId = INSTANCE_ID_UNDEFINED;
        if (frameNode) {
            instanceId = frameNode->GetInstanceId();
        } else {
            instanceId = Container::CurrentIdSafely();
        }
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostAsyncEvent([info, func]() { func(info.get()); }, "ArkUIWebRequestFocusCallback");
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRequestFocusEvent(std::move(uiCallback));
}

void WebModelNG::SetOnDownloadStart(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDownloadStartEvent(std::move(uiCallback));
}

void WebModelNG::SetOnHttpAuthRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpAuthRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslErrorRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnAllSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAllSslErrorRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnSslSelectCertRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
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
    WeakPtr<NG::FrameNode> weak = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto uiCallback = [func, weak](KeyEventInfo& keyEventInfo) {
        auto frameNode = weak.Upgrade();
        int32_t instanceId = INSTANCE_ID_UNDEFINED;
        if (frameNode) {
            instanceId = frameNode->GetInstanceId();
        } else {
            instanceId = Container::CurrentIdSafely();
        }
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostSyncEvent([&keyEventInfo, func]() { func(keyEventInfo); }, "ArkUIWebKeyEventCallback");
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnKeyEvent(std::move(uiCallback));
}

void WebModelNG::SetOnErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnErrorReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnHttpErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpErrorReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnUrlLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnUrlLoadInterceptEvent(std::move(uiCallback));
}

void WebModelNG::SetOnLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnLoadInterceptEvent(std::move(uiCallback));
}

void WebModelNG::SetOnOverrideUrlLoading(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnOverrideUrlLoadingEvent(std::move(uiCallback));
}

void WebModelNG::SetOnInterceptRequest(std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> RefPtr<WebResponse> {
        CHECK_NULL_RETURN(info, nullptr);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnInterceptRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetOnFileSelectorShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFileSelectorShowEvent(std::move(uiCallback));
}

void WebModelNG::SetOnContextMenuShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuShowEvent(std::move(uiCallback));
}

void WebModelNG::SetNewDragStyle(bool isNewDragStyle)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetNewDragStyle(isNewDragStyle);
}

void WebModelNG::SetPreviewSelectionMenu(const std::shared_ptr<WebPreviewSelectionMenuParam>& param)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetPreviewSelectionMenu(param);
}

void WebModelNG::SetOnContextMenuHide(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
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
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderExitedEvent(std::move(uiCallback));
}

void WebModelNG::SetRefreshAccessedHistoryId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
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

void WebModelNG::SetOverScrollMode(OverScrollMode mode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOverScrollMode(mode);
}

void WebModelNG::SetBlurOnKeyboardHideMode(BlurOnKeyboardHideMode mode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateBlurOnKeyboardHideMode(mode);
}

void WebModelNG::SetCopyOptionMode(CopyOptions mode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateCopyOptionMode(static_cast<int32_t>(mode));
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
    webPattern->UpdateWebDebuggingAccessEnabledAndPort(
        std::make_tuple(isWebDebuggingAccessEnabled, 0));
}

void WebModelNG::SetWebDebuggingAccessEnabledAndPort(
    bool isWebDebuggingAccessEnabled, int32_t webDebuggingPort)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebDebuggingAccessEnabledAndPort(
        std::make_tuple(isWebDebuggingAccessEnabled, webDebuggingPort));
}

void WebModelNG::SetOnMouseEvent(std::function<void(MouseInfo& info)>&& jsCallback)
{
    auto func = jsCallback;
    WeakPtr<NG::FrameNode> weak = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto uiCallback = [func, weak](MouseInfo& info) {
        auto frameNode = weak.Upgrade();
        int32_t instanceId = INSTANCE_ID_UNDEFINED;
        if (frameNode) {
            instanceId = frameNode->GetInstanceId();
        } else {
            instanceId = Container::CurrentIdSafely();
        }
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->PostSyncEvent([&info, func]() { func(info); }, "ArkUIWebMouseEventCallback");
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnMouseEvent(std::move(uiCallback));
}

void WebModelNG::SetResourceLoadId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnResourceLoadEvent(std::move(uiCallback));
}

void WebModelNG::SetScaleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScaleChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScrollEvent(std::move(uiCallback));
}

void WebModelNG::SetPermissionRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
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

Color WebModelNG::GetDefaultBackgroundColor()
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_RETURN(webPattern, Color::WHITE);
    return webPattern->GetDefaultBackgroundColor();
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
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
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
    ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
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
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
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

void WebModelNG::SetDefaultTextEncodingFormat(const std::string& textEncodingFormat)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultTextEncodingFormat(textEncodingFormat);
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
    WeakPtr<NG::FrameNode> weak = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onConsole = [func, weak](KeyEventInfo& keyEventInfo) -> bool {
        auto frameNode = weak.Upgrade();
        int32_t instanceId = INSTANCE_ID_UNDEFINED;
        if (frameNode) {
            instanceId = frameNode->GetInstanceId();
        } else {
            instanceId = Container::CurrentIdSafely();
        }
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        bool result = false;
        CHECK_NULL_RETURN(context, result);
        context->PostSyncEvent(
            [func, &keyEventInfo, &result]() { result = func(keyEventInfo); }, "ArkUIWebInterceptKeyEventCallback");
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

void WebModelNG::SetFirstMeaningfulPaintId(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstMeaningfulPaintId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFirstMeaningfulPaintEvent(std::move(firstMeaningfulPaintId));
}

void WebModelNG::SetLargestContentfulPaintId(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& largestContentfulPaintId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnLargestContentfulPaintEvent(std::move(largestContentfulPaintId));
}

void WebModelNG::SetNavigationEntryCommittedId(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& navigationEntryCommittedId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNavigationEntryCommittedEvent(std::move(navigationEntryCommittedId));
}

void WebModelNG::SetTouchIconUrlId(OnWebAsyncFunc&& touchIconUrlId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTouchIconUrlEvent(std::move(touchIconUrlId));
}

void WebModelNG::SetSafeBrowsingCheckResultId(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& safeBrowsingCheckResultId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSafeBrowsingCheckResultEvent(std::move(safeBrowsingCheckResultId));
}

void WebModelNG::SetIntelligentTrackingPreventionResultId(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&&
        intelligentTrackingPreventionResultId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->
        GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnIntelligentTrackingPreventionResultEvent(
        std::move(intelligentTrackingPreventionResultId));
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

void WebModelNG::SetNativeEmbedModeEnabled(bool isEmbedModeEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateNativeEmbedModeEnabled(isEmbedModeEnabled);
}

void WebModelNG::SetIntrinsicSizeEnabled(bool isIntrinsicSizeEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateIntrinsicSizeEnabled(isIntrinsicSizeEnabled);
}

void WebModelNG::RegisterNativeEmbedRule(const std::string& tag, const std::string& type)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateNativeEmbedRuleTag(tag);
    webPattern->UpdateNativeEmbedRuleType(type);
}

void WebModelNG::SetOnControllerAttached(std::function<void()>&& callback)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetOnControllerAttachedCallback(std::move(callback));
}

void WebModelNG::NotifyPopupWindowResult(int32_t webId, bool result)
{
#if !defined(IOS_PLATFORM) && !defined(ANDROID_PLATFORM)
    if (webId != -1) {
        std::shared_ptr<OHOS::NWeb::NWeb> nweb = OHOS::NWeb::NWebHelper::Instance().GetNWeb(webId);
        if (nweb) {
            nweb->NotifyPopupWindowResult(result);
        } else {
            TAG_LOGE(AceLogTag::ACE_WEB, "NotifyPopupWindowResult not found nweb %{public}d", webId);
        }
    }
#endif
}

void WebModelNG::AddDragFrameNodeToManager()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    dragDropManager->AddDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
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

void WebModelNG::SetNativeEmbedLifecycleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedLifecycleChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetNativeEmbedVisibilityChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedVisibilityChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetNativeEmbedGestureEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedGestureEvent(std::move(uiCallback));
}

void WebModelNG::SetLayoutMode(WebLayoutMode mode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetLayoutMode(mode);
}

void WebModelNG::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetNestedScroll(nestedOpt);
}

void WebModelNG::SetNestedScrollExt(const NestedScrollOptionsExt& nestedOpt)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetNestedScrollExt(nestedOpt);
}

void WebModelNG::SetMetaViewport(bool enabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMetaViewport(enabled);
}

void WebModelNG::JavaScriptOnDocumentStart(const ScriptItems& scriptItems)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnDocumentStart(scriptItems);
}

void WebModelNG::JavaScriptOnDocumentStartByOrder(const ScriptItems& scriptItems,
    const ScriptItemsByOrder& scriptItemsByOrder)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnDocumentStartByOrder(scriptItems, scriptItemsByOrder);
}

void WebModelNG::JavaScriptOnDocumentEndByOrder(const ScriptItems& scriptItems,
    const ScriptItemsByOrder& scriptItemsByOrder)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnDocumentEndByOrder(scriptItems, scriptItemsByOrder);
}

void WebModelNG::JavaScriptOnHeadReadyByOrder(const ScriptItems& scriptItems,
    const ScriptItemsByOrder& scriptItemsByOrder)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnHeadReadyByOrder(scriptItems, scriptItemsByOrder);
}

void WebModelNG::JavaScriptOnDocumentEnd(const ScriptItems& scriptItems)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnDocumentEnd(scriptItems);
}

void WebModelNG::SetPermissionClipboard(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);

    webPattern->SetPermissionClipboardCallback(std::move(jsCallback));
}

void WebModelNG::SetOpenAppLinkFunction(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);

    webPattern->SetOnOpenAppLinkCallback(std::move(jsCallback));
}

void WebModelNG::SetDefaultFileSelectorShow(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetDefaultFileSelectorShowCallback(std::move(jsCallback));
}

void WebModelNG::SetTextAutosizing(bool isTextAutosizing)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateTextAutosizing(isTextAutosizing);
}

void WebModelNG::SetNativeVideoPlayerConfig(bool enable, bool shouldOverlay)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);

    webPattern->UpdateNativeVideoPlayerConfig(std::make_tuple(enable, shouldOverlay));
}

void WebModelNG::SetRenderProcessNotRespondingId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderProcessNotRespondingEvent(std::move(uiCallback));
}

void WebModelNG::SetRenderProcessRespondingId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderProcessRespondingEvent(std::move(uiCallback));
}

void WebModelNG::SetSelectionMenuOptions(const WebMenuOptionsParam& webMenuOption)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateSelectionMenuOptions(std::move(webMenuOption));
}

void WebModelNG::SetEditMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
                                    const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateEditMenuOptions(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void WebModelNG::SetViewportFitChangedId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnViewportFitChangedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnInterceptKeyboardAttach(std::function<WebKeyboardOption(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> WebKeyboardOption {
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnInterceptKeyboardAttachEvent(std::move(uiCallback));
}

void WebModelNG::SetAdsBlockedEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAdsBlockedEvent(std::move(uiCallback));
}

void WebModelNG::SetUpdateInstanceIdCallback(std::function<void(int32_t)>&& callback)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);

    webPattern->SetUpdateInstanceIdCallback(std::move(callback));
}

void WebModelNG::SetOverlayScrollbarEnabled(bool isEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOverlayScrollbarEnabled(isEnabled);
}

void WebModelNG::SetKeyboardAvoidMode(const WebKeyboardAvoidMode& mode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateKeyboardAvoidMode(mode);
}

void WebModelNG::SetEnabledHapticFeedback(bool isEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateEnabledHapticFeedback(isEnabled);
}

void WebModelNG::SetOptimizeParserBudgetEnabled(bool enable)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOptimizeParserBudgetEnabled(enable);
}

void WebModelNG::SetWebMediaAVSessionEnabled(bool isEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebMediaAVSessionEnabled(isEnabled);
}

void WebModelNG::SetEnableDataDetector(bool isEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateEnableDataDetector(isEnabled);
}

void WebModelNG::SetDataDetectorConfig(const TextDetectConfig& config)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDataDetectorConfig(config);
}

void WebModelNG::SetEnableFollowSystemFontWeight(bool enableFollowSystemFontWeight)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateEnableFollowSystemFontWeight(enableFollowSystemFontWeight);
}

void WebModelNG::SetJsEnabled(FrameNode* frameNode, bool isJsEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateJsEnabled(isJsEnabled);
}

void WebModelNG::SetFileAccessEnabled(FrameNode* frameNode, bool isFileAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateFileAccessEnabled(isFileAccessEnabled);
}

void WebModelNG::SetDomStorageAccessEnabled(FrameNode* frameNode, bool isDomStorageAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void WebModelNG::SetMixedMode(FrameNode* frameNode, MixedModeContent mixedContentMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMixedMode(mixedContentMode);
}

void WebModelNG::SetZoomAccessEnabled(FrameNode* frameNode, bool isZoomAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateZoomAccessEnabled(isZoomAccessEnabled);
}

void WebModelNG::SetCacheMode(FrameNode* frameNode, WebCacheMode cacheMode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateCacheMode(cacheMode);
}

void WebModelNG::SetDarkMode(FrameNode* frameNode, WebDarkMode mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDarkMode(mode);
}

void WebModelNG::SetMultiWindowAccessEnabled(FrameNode* frameNode, bool isMultiWindowAccessEnable)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMultiWindowAccessEnabled(isMultiWindowAccessEnable);
}

void WebModelNG::SetAllowWindowOpenMethod(FrameNode* frameNode, bool isAllowWindowOpenMethod)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateAllowWindowOpenMethod(isAllowWindowOpenMethod);
}

void WebModelNG::SetOnScroll(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScrollEvent(std::move(uiCallback));
}

void WebModelNG::SetOnOverScroll(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnOverScrollEvent(std::move(uiCallback));
}

void WebModelNG::SetOnScaleChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScaleChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetOnRequestFocus(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRequestFocusEvent(std::move(uiCallback));
}

void WebModelNG::SetOnContextMenuHide(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuHideEvent(std::move(uiCallback));
}

void WebModelNG::SetKeyboardAvoidMode(FrameNode* frameNode, const WebKeyboardAvoidMode& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateKeyboardAvoidMode(mode);
}

void WebModelNG::SetOnControllerAttached(FrameNode* frameNode, std::function<void()>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetOnControllerAttachedCallback(std::move(callback));
}

void WebModelNG::SetVerticalScrollBarAccessEnabled(FrameNode* frameNode, bool isVerticalScrollBarAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateVerticalScrollBarAccessEnabled(isVerticalScrollBarAccessEnabled);
}

void WebModelNG::SetHorizontalScrollBarAccessEnabled(FrameNode* frameNode, bool isHorizontalScrollBarAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateHorizontalScrollBarAccessEnabled(isHorizontalScrollBarAccessEnabled);
}

void WebModelNG::SetTextZoomRatio(FrameNode* frameNode, int32_t textZoomRatioNum)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateTextZoomRatio(textZoomRatioNum);
}

void WebModelNG::InitialScale(FrameNode* frameNode, float scale)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateInitialScale(scale);
}
void WebModelNG::SetGeolocationAccessEnabled(FrameNode* frameNode, bool isGeolocationAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void WebModelNG::SetDatabaseAccessEnabled(FrameNode* frameNode, bool isDatabaseAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDatabaseAccessEnabled(isDatabaseAccessEnabled);
}

void WebModelNG::SetOnGeolocationShow(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationShowEvent(std::move(uiCallback));
}

void WebModelNG::SetOverviewModeAccessEnabled(FrameNode* frameNode, bool isOverviewModeAccessEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOverviewModeAccessEnabled(isOverviewModeAccessEnabled);
}

void WebModelNG::SetForceDarkAccess(FrameNode* frameNode, bool isForceDarkAccess)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateForceDarkAccess(isForceDarkAccess);
}

void WebModelNG::SetPinchSmoothModeEnabled(FrameNode* frameNode, bool isPinchSmoothModeEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdatePinchSmoothModeEnabled(isPinchSmoothModeEnabled);
}

void WebModelNG::SetMetaViewport(FrameNode* frameNode, bool isMetaViewport)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMetaViewport(isMetaViewport);
}

void WebModelNG::SetEnableFollowSystemFontWeight(FrameNode* frameNode, bool isEnableFollowSystemFontWeight)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateEnableFollowSystemFontWeight(isEnableFollowSystemFontWeight);
}

void WebModelNG::SetNativeEmbedModeEnabled(FrameNode* frameNode, bool isNativeEmbedModeEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateNativeEmbedModeEnabled(isNativeEmbedModeEnabled);
}

void WebModelNG::SetMinFontSize(FrameNode* frameNode, int32_t minFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMinFontSize(minFontSize); 
}

void WebModelNG::SetDefaultFontSize(FrameNode* frameNode, int32_t defaultFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultFontSize(defaultFontSize);
}

void WebModelNG::SetDefaultFixedFontSize(FrameNode* frameNode, int32_t defaultFixedFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultFixedFontSize(defaultFixedFontSize);
}

void WebModelNG::SetMinLogicalFontSize(FrameNode* frameNode, int32_t minLogicalFontSize)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMinLogicalFontSize(minLogicalFontSize);
}

void WebModelNG::SetWebStandardFont(FrameNode* frameNode, const std::string& standardFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebStandardFont(standardFontFamily);
}

void WebModelNG::SetWebSerifFont(FrameNode* frameNode, const std::string& serifFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebSerifFont(serifFontFamily);
}

void WebModelNG::SetWebSansSerifFont(FrameNode* frameNode, const std::string& sansSerifFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebSansSerifFont(sansSerifFontFamily);
}


void WebModelNG::SetWebFixedFont(FrameNode* frameNode, const std::string& fixedFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebFixedFont(fixedFontFamily);
}

void WebModelNG::SetWebFantasyFont(FrameNode* frameNode, const std::string& fixedFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebFantasyFont(fixedFontFamily);
}

void WebModelNG::SetWebCursiveFont(FrameNode* frameNode, const std::string& cursiveFontFamily)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebCursiveFont(cursiveFontFamily);
}

void WebModelNG::SetLayoutMode(FrameNode* frameNode, WebLayoutMode mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetLayoutMode(mode);
}

void WebModelNG::SetNativeEmbedLifecycleChangeId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedLifecycleChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetNativeEmbedGestureEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNativeEmbedGestureEvent(std::move(uiCallback));
}

void WebModelNG::RegisterNativeEmbedRule(FrameNode* frameNode, const std::string& tag, const std::string& type)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateNativeEmbedRuleTag(tag);
    webPattern->UpdateNativeEmbedRuleType(type);
}

void WebModelNG::SetNativeEmbedOptions(FrameNode* frameNode, bool isIntrinsicSizeEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateIntrinsicSizeEnabled(isIntrinsicSizeEnabled);
}

void WebModelNG::SetFirstContentfulPaintId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstContentfulPaintId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFirstContentfulPaintEvent(std::move(firstContentfulPaintId));
}

void WebModelNG::SetAudioStateChangedId(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& audioStateChanged)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnAudioStateChangedEvent(std::move(audioStateChanged));
}

void WebModelNG::SetOnFullScreenExit(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenExitEvent(std::move(uiCallback));
}

void WebModelNG::SetImageAccessEnabled(FrameNode* frameNode, bool isImageAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateImageAccessEnabled(isImageAccessEnabled);
}

void WebModelNG::SetOnLineImageAccessEnabled(FrameNode* frameNode, bool isOnLineImageAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOnLineImageAccessEnabled(isOnLineImageAccessEnabled);
}

void WebModelNG::SetMediaPlayGestureAccess(FrameNode* frameNode, bool isNeedGestureAccess)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMediaPlayGestureAccess(isNeedGestureAccess);
}

void WebModelNG::SetAudioResumeInterval(FrameNode* frameNode, int32_t resumeInterval)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateAudioResumeInterval(resumeInterval);
}

void WebModelNG::SetAudioExclusive(FrameNode* frameNode, bool audioExclusive)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateAudioExclusive(audioExclusive);
}

void WebModelNG::SetOnPageFinish(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageFinishedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnPageStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageStartedEvent(std::move(uiCallback));
}

void WebModelNG::SetOnProgressChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnProgressChangeEvent(std::move(uiCallback));
}

void WebModelNG::SetOnTitleReceive(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTitleReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOnDownloadStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDownloadStartEvent(std::move(uiCallback));
}

void WebModelNG::JavaScriptOnDocumentStart(FrameNode* frameNode, const ScriptItems& scriptItems)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnDocumentStart(scriptItems);
}

void WebModelNG::JavaScriptOnDocumentEnd(FrameNode* frameNode, const ScriptItems& scriptItems)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->JavaScriptOnDocumentEnd(scriptItems);
}

void WebModelNG::SetCopyOptionMode(FrameNode* frameNode, CopyOptions mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateCopyOptionMode(static_cast<int32_t>(mode));
}

void WebModelNG::SetRenderProcessNotRespondingId(FrameNode* frameNode,  std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderProcessNotRespondingEvent(std::move(uiCallback));
}

void WebModelNG::SetOnPageVisible(FrameNode* frameNode, OnWebAsyncFunc&& pageVisibleId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageVisibleEvent(std::move(pageVisibleId));
}

void WebModelNG::SetOnRenderExited(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderExitedEvent(std::move(uiCallback));
}

void WebModelNG::SetBlockNetwork(FrameNode* frameNode, bool isNetworkBlocked)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateBlockNetwork(isNetworkBlocked);
}

void WebModelNG::SetOnResourceLoad(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnResourceLoadEvent(std::move(uiCallback));
}

void WebModelNG::SetOnRefreshAccessedHistory(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRefreshAccessedHistoryEvent(std::move(uiCallback));
}

void WebModelNG::SetOnNavigationEntryCommitted(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& navigationEntryCommitted)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnNavigationEntryCommittedEvent(std::move(navigationEntryCommitted));
}

void WebModelNG::SetOnSearchResultReceive(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSearchResultReceiveEvent(std::move(uiCallback));
}

void WebModelNG::SetOverScrollMode(FrameNode* frameNode, OverScrollMode mode)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOverScrollMode(mode);
}
void WebModelNG::SetOnTouchIconUrlReceived(FrameNode* frameNode, OnWebAsyncFunc&& touchIconUrlId)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTouchIconUrlEvent(std::move(touchIconUrlId));
}

void WebModelNG::SetOnRenderProcessResponding(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderProcessRespondingEvent(std::move(uiCallback));
}

void WebModelNG::SetPermissionRequestEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPermissionRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetScreenCaptureRequestEventId(
    FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScreenCaptureRequestEvent(std::move(uiCallback));
}

void WebModelNG::SetWindowNewEvent(
    FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowNewEvent(std::move(jsCallback));
}

void WebModelNG::SetOnFullScreenEnter(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenEnterEvent(std::move(uiCallback));
}

void WebModelNG::SetWindowExitEventId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) {
        CHECK_NULL_VOID(info);
        func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowExitEvent(std::move(uiCallback));
}

void WebModelNG::SetOnAlert(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnCommonDialogEvent(std::move(uiCallback), static_cast<DialogEventType>(dialogEventType));
}

void WebModelNG::SetOnConfirm(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnCommonDialogEvent(std::move(uiCallback), static_cast<DialogEventType>(dialogEventType));
}

void WebModelNG::SetOnPrompt(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType)
{
    CHECK_NULL_VOID(frameNode);
    auto func = jsCallback;
    auto uiCallback = [func](const std::shared_ptr<BaseEventInfo>& info) -> bool {
        CHECK_NULL_RETURN(info, false);
        return func(info.get());
    };
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnCommonDialogEvent(std::move(uiCallback), static_cast<DialogEventType>(dialogEventType));
}
} // namespace OHOS::Ace::NG
