/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "js_third_provider_interaction_operation.h"

#include <algorithm>

#include "accessibility_constants.h"
#include "accessibility_event_info.h"
#include "accessibility_system_ability_client.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "js_third_provider_interaction_operation_utils.h"

namespace OHOS::Ace::Framework {
namespace {
void FillNodeConfig(
    const NodeConfig& config, Accessibility::AccessibilityElementInfo& info)
{
    OHOS::Accessibility::Rect oldRect = info.GetRectInScreen();
    OHOS::Accessibility::Rect newRect = OHOS::Accessibility::Rect(
        oldRect.GetLeftTopXScreenPostion() + static_cast<int32_t>(config.offset.GetX()),
        oldRect.GetLeftTopYScreenPostion() + static_cast<int32_t>(config.offset.GetY()),
        oldRect.GetRightBottomXScreenPostion() + static_cast<int32_t>(config.offset.GetX()),
        oldRect.GetRightBottomYScreenPostion() + static_cast<int32_t>(config.offset.GetY()));
    info.SetRectInScreen(newRect);
    info.SetPageId(config.pageId);
    info.SetWindowId(config.windowId);
    info.SetBelongTreeId(config.belongTreeId);
    info.SetChildTreeIdAndWinId(config.childTreeId, config.childWindowId);
    info.SetParentWindowId(config.parentWindowId);
    info.SetBundleName(config.bundleName);
    info.SetInspectorKey(config.inspectorKey);
}

void CopyNativeInfoToAccessibilityElementInfo(
    const ArkUI_AccessibilityElementInfo& elementInfo,
    const NodeConfig& config,
    Accessibility::AccessibilityElementInfo& info)
{
    TransformAccessbilityElementInfo(elementInfo, info);
    FillNodeConfig(config, info);
}

void CopyNativeInfosToAccessibilityElementInfos(
    const std::vector<ArkUI_AccessibilityElementInfo>& nativeInfos,
    const NodeConfig& config,
    std::list<Accessibility::AccessibilityElementInfo>& infos)
{
    for (const auto& nativeInfo : nativeInfos) {
        Accessibility::AccessibilityElementInfo info;
        TransformAccessbilityElementInfo(nativeInfo, info);
        FillNodeConfig(config, info);
        infos.push_back(info);
    }
}
}

JsThirdProviderInteractionOperation::JsThirdProviderInteractionOperation(
    const WeakPtr<AccessibilityProvider>& accessibilityProvider,
    const WeakPtr<JsAccessibilityManager>& jsAccessibilityManager,
    WeakPtr<NG::FrameNode> host)
    : accessibilityProvider_(accessibilityProvider),
    jsAccessibilityManager_(jsAccessibilityManager),
    host_(host)
{
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "JsThirdProviderInteractionOperation Create");
}

JsThirdProviderInteractionOperation::~JsThirdProviderInteractionOperation()
{
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "JsThirdProviderInteractionOperation Destory");
}

void JsThirdProviderInteractionOperation::Initialize()
{
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_VOID(provider);
}

void JsThirdProviderInteractionOperation::SearchElementInfoByAccessibilityId(
    const int64_t elementId, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback, const int32_t mode)
{
    // 1. Get real elementId
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        elementId, splitElementId, splitTreeId);

    // 2. FindAccessibilityNodeInfosById by provider
    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = FindAccessibilityNodeInfosByIdFromProvider(
        splitElementId, mode, requestId, infos);
    if (!ret) {
    }
    // 3. Return result
    SetSearchElementInfoByAccessibilityIdResult(callback, std::move(infos), requestId);
}

bool JsThirdProviderInteractionOperation::FindAccessibilityNodeInfosByIdFromProvider(
    const int64_t splitElementId, const int32_t mode, const int32_t requestId,
    std::list<Accessibility::AccessibilityElementInfo>& infos)
{
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_RETURN(provider, false);
    std::vector<ArkUI_AccessibilityElementInfo> nativeInfos;
    int32_t code = provider->FindAccessibilityNodeInfosById(
        splitElementId, mode, requestId, nativeInfos);
    if (code != 0) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "FindAccessibilityNodeInfosByIdFromProvider failed: %{public}d", code);
        return false;
    }

    NodeConfig config;
    GetNodeConfig(config);
    CopyNativeInfosToAccessibilityElementInfos(nativeInfos, config, infos);
    return !infos.empty();
}

void JsThirdProviderInteractionOperation::SetSearchElementInfoByAccessibilityIdResult(
    AccessibilityElementOperatorCallback& callback,
    std::list<AccessibilityElementInfo>&& infos,
    const int32_t requestId)
{
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(context->GetTaskExecutor());
    context->GetTaskExecutor()->PostTask(
        [jsMgr = jsAccessibilityManager_,
            infos = std::move(infos), &callback, requestId] () mutable {
            auto jsAccessibilityManager = jsMgr.Upgrade();
            CHECK_NULL_VOID(jsAccessibilityManager);
            if (!jsAccessibilityManager->IsRegister()) {
                return;
            }
            jsAccessibilityManager->UpdateElementInfosTreeId(infos);
            callback.SetSearchElementInfoByAccessibilityIdResult(infos, requestId);
        }, TaskExecutor::TaskType::BACKGROUND, "SearchElementInfoByAccessibilityId");
}

void JsThirdProviderInteractionOperation::SearchElementInfosByText(
    const int64_t elementId, const std::string& text, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback)
{
    // 1. Get real elementId
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        elementId, splitElementId, splitTreeId);

    // 2. FindAccessibilityNodeInfosByText from provider
    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = FindAccessibilityNodeInfosByTextFromProvider(
        splitElementId, text, requestId, infos);
    if (!ret) {
    }

    // 3. Return result
    SetSearchElementInfoByTextResult(callback, std::move(infos), requestId);
}

bool JsThirdProviderInteractionOperation::FindAccessibilityNodeInfosByTextFromProvider(
    const int64_t splitElementId, const std::string& text, const int32_t requestId,
    std::list<Accessibility::AccessibilityElementInfo>& infos)
{
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_RETURN(provider, false);
    std::vector<ArkUI_AccessibilityElementInfo> nativeInfos;
    int32_t code = provider->FindAccessibilityNodeInfosByText(
        splitElementId, text, requestId, nativeInfos);
    if (code != 0) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "FindAccessibilityNodeInfosByTextFromProvider failed: %{public}d", code);
        return false;
    }

    NodeConfig config;
    GetNodeConfig(config);
    CopyNativeInfosToAccessibilityElementInfos(nativeInfos, config, infos);
    return true;
}

void JsThirdProviderInteractionOperation::SetSearchElementInfoByTextResult(
    AccessibilityElementOperatorCallback& callback,
    std::list<AccessibilityElementInfo>&& infos,
    const int32_t requestId)
{
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(context->GetTaskExecutor());
    context->GetTaskExecutor()->PostTask(
        [jsMgr = jsAccessibilityManager_,
            infos = std::move(infos), &callback, requestId] () mutable {
            auto jsAccessibilityManager = jsMgr.Upgrade();
            CHECK_NULL_VOID(jsAccessibilityManager);
            if (!jsAccessibilityManager->IsRegister()) {
                return;
            }
            jsAccessibilityManager->UpdateElementInfosTreeId(infos);
            callback.SetSearchElementInfoByTextResult(infos, requestId);
        }, TaskExecutor::TaskType::BACKGROUND, "SetSearchElementInfoByTextResult");
}

void JsThirdProviderInteractionOperation::FindFocusedElementInfo(
    const int64_t elementId, const int32_t focusType, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback)
{
    // 1. Get real elementId
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        elementId, splitElementId, splitTreeId);

    // 2. FindFocusedAccessibilityNode from provider
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_VOID(provider);
    ArkUI_AccessibilityElementInfo nativeInfo;
    int32_t code = provider->FindFocusedAccessibilityNode(
        splitElementId, focusType, requestId, nativeInfo);
    if (code != 0) {
        return;
    }

    NodeConfig config;
    GetNodeConfig(config);
    Accessibility::AccessibilityElementInfo info;
    CopyNativeInfoToAccessibilityElementInfo(nativeInfo, config, info);

    // 3. Return result
    SetFindFocusedElementInfoResult(callback, info, requestId);
}

void JsThirdProviderInteractionOperation::SetFindFocusedElementInfoResult(
    AccessibilityElementOperatorCallback& callback,
    AccessibilityElementInfo& info,
    const int32_t requestId)
{
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);
    callback.SetFindFocusedElementInfoResult(info, requestId);
}

void JsThirdProviderInteractionOperation::FocusMoveSearch(
    const int64_t elementId, const int32_t direction, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback)
{
    // 1. Get real elementId
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        elementId, splitElementId, splitTreeId);

    // 2. FindNextFocusAccessibilityNode from provider
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_VOID(provider);
    ArkUI_AccessibilityElementInfo nativeInfo;
    int32_t code = provider->FindNextFocusAccessibilityNode(
        splitElementId, direction, requestId, nativeInfo);
    if (code != 0) {
        return;
    }

    NodeConfig config;
    GetNodeConfig(config);
    Accessibility::AccessibilityElementInfo info;
    CopyNativeInfoToAccessibilityElementInfo(nativeInfo, config, info);

    // 3. Return result
    SetFocusMoveSearchResult(callback, info, requestId);
}

void JsThirdProviderInteractionOperation::SetFocusMoveSearchResult(
    AccessibilityElementOperatorCallback& callback,
    AccessibilityElementInfo& info,
    const int32_t requestId)
{
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);
    jsAccessibilityManager->UpdateElementInfoTreeId(info);
    callback.SetFocusMoveSearchResult(info, requestId);
}

void JsThirdProviderInteractionOperation::ExecuteAction(
    const int64_t elementId, const int32_t action,
    const std::map<std::string, std::string>& actionArguments, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback)
{
    // 1. Get real elementId
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        elementId, splitElementId, splitTreeId);

    // 2. FindNextFocusAccessibilityNode from provider
    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = FindAccessibilityNodeInfosByIdFromProvider(
        splitElementId, 0, requestId, infos);
    if (!ret || infos.size() == 0) {
        return;
    }

    // 3. DrawBound
    ExecuteActionForThird(splitElementId, infos.front(), action);

    //4. ExecuteAccessibilityAction To provider
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_VOID(provider);
    int32_t code = provider->ExecuteAccessibilityAction(
        splitElementId, action, requestId, actionArguments);
    if (code != 0) {
        return;
    }

    // 5. Return result
    SetExecuteActionResult(callback, code == 0, requestId);
}

bool JsThirdProviderInteractionOperation::ExecuteActionForThird(
    int64_t elementId, const AccessibilityElementInfo& nodeInfo, const int32_t action)
{
    auto hostNode = GetHost();
    CHECK_NULL_RETURN(hostNode, false);
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_RETURN(context, false);
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(context);
    CHECK_NULL_RETURN(ngPipeline, false);
    if (action == static_cast<int32_t>(
        Accessibility::ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS)) {
        jsAccessibilityManager->ActThirdAccessibilityFocus(
            elementId, nodeInfo, hostNode, ngPipeline, false);
    } else if (action == static_cast<int32_t>(
        Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS)) {
        jsAccessibilityManager->ActThirdAccessibilityFocus(
            elementId, nodeInfo, hostNode, ngPipeline, true);
    }
    return true;
}

void JsThirdProviderInteractionOperation::SetExecuteActionResult(
    AccessibilityElementOperatorCallback& callback,
    const bool succeeded, const int32_t requestId)
{
    callback.SetExecuteActionResult(succeeded, requestId);
}

void JsThirdProviderInteractionOperation::ClearFocus()
{
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_VOID(provider);
    int32_t code = provider->ClearFocusedAccessibilityNode();
    if (code != 0) {
        return;
    }
}

void JsThirdProviderInteractionOperation::OutsideTouch()
{}

void JsThirdProviderInteractionOperation::GetCursorPosition(
    const int64_t elementId, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback &callback)
{
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_VOID(provider);
    int32_t cursorPosition = -1;
    int32_t code = provider->GetAccessibilityNodeCursorPosition(
        elementId, requestId, cursorPosition);
    if (code != 0) {
        callback.SetCursorPositionResult(-1, requestId);
        return;
    }

    callback.SetCursorPositionResult(cursorPosition, requestId);
}

void JsThirdProviderInteractionOperation::GetNodeConfig(NodeConfig& config)
{
    auto host = host_.Upgrade();
    CHECK_NULL_VOID(host);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID(context);
    auto [displayOffset, err] = host->GetPaintRectGlobalOffsetWithTranslate();
    config.offset = displayOffset;
    config.pageId = host->GetPageId();
    config.windowId = context->GetRealHostWindowId();
    config.belongTreeId = belongTreeId_;
    config.parentWindowId = context->GetRealHostWindowId();
    config.bundleName = AceApplicationInfo::GetInstance().GetPackageName();
}

void JsThirdProviderInteractionOperation::SetChildTreeIdAndWinId(
    const int64_t nodeId, const int32_t treeId, const int32_t childWindowId)
{
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "SetChildTreeIdAndWinId, node: %{public}" PRId64 ","
        "treeId: %{public}d, childWindowId: %{public}d", nodeId, treeId, childWindowId);
}

void JsThirdProviderInteractionOperation::SetBelongTreeId(const int32_t treeId)
{
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "SetBelongTreeId treeId: %{public}d", treeId);
    belongTreeId_ = treeId;
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);
    jsAccessibilityManager->SetTreeIdForTest(treeId);
}

int32_t JsThirdProviderInteractionOperation::SendAccessibilityAsyncEvent(
    const ArkUI_AccessibilityEventInfo& nativeAccessibilityEvent,
    void (*callback)(int32_t errorCode))
{
    // 1. Get OHOS::Accessibility::AccessibilityEventInfo
    OHOS::Accessibility::AccessibilityEventInfo accessibilityEventInfo;
    GetAccessibilityEventInfoFromNativeEvent(
        nativeAccessibilityEvent, accessibilityEventInfo);

    // 2. SendEvent
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, -1);
    auto host = host_.Upgrade();
    CHECK_NULL_RETURN(host, -1);
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "Inner SendAccessibilityAsyncEvent");
    SendAccessibilitySyncEventToService(accessibilityEventInfo, callback);
    callback(880);
    return 0;
}

void JsThirdProviderInteractionOperation::GetAccessibilityEventInfoFromNativeEvent(
    const ArkUI_AccessibilityEventInfo& nativeEventInfo,
    OHOS::Accessibility::AccessibilityEventInfo& accessibilityEventInfo)
{
    // 1. Transform native event to OHOS::Accessibility::AccessibilityEventInfo
    TransformAccessbilityEventInfo(
        nativeEventInfo, accessibilityEventInfo);

    // 2. Fill node config
    NodeConfig config;
    GetNodeConfig(config);

    // 2.1. Fill elementInfo config
    auto elementInfo = accessibilityEventInfo.GetElementInfo();
    FillNodeConfig(config, elementInfo);
    int64_t elementId = elementInfo.GetAccessibilityId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(belongTreeId_, elementId);
    elementInfo.SetAccessibilityId(elementId);

    // 2.2. Fill eventInfo config
    accessibilityEventInfo.SetPageId(config.pageId);
    accessibilityEventInfo.SetComponentType(elementInfo.GetComponentType());
    accessibilityEventInfo.AddContent(elementInfo.GetContent());
    accessibilityEventInfo.SetElementInfo(elementInfo);
}

bool JsThirdProviderInteractionOperation::SendAccessibilitySyncEventToService(
    const OHOS::Accessibility::AccessibilityEventInfo& eventInfo,
    void (*callback)(int32_t errorCode))
{
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_RETURN(context, false);
    CHECK_NULL_RETURN(context->GetTaskExecutor(), false);
    context->GetTaskExecutor()->PostTask(
        [jsMgr = jsAccessibilityManager_, eventInfo, callback] () mutable {
            auto jsAccessibilityManager = jsMgr.Upgrade();
            if (jsAccessibilityManager == nullptr) {
                return;
            }

            if (!jsAccessibilityManager->IsRegister()) {
                return;
            }

            auto client = AccessibilitySystemAbilityClient::GetInstance();
            CHECK_NULL_VOID(client);
            bool isEnabled = false;
            client->IsEnabled(isEnabled);
            if (!isEnabled) {
                return;
            }

            TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
                "send accessibility componentType:%{public}s event:%{public}d accessibilityId:%{public}" PRId64,
                eventInfo.GetComponentType().c_str(), eventInfo.GetEventType(), eventInfo.GetAccessibilityId());
            client->SendEvent(eventInfo);
        }, TaskExecutor::TaskType::BACKGROUND, "SetSearchElementInfoByTextResult");
    return true;
}
} // namespace OHOS::Ace::Framework