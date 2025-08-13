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

#include "accessibility_system_ability_client.h"

#include "core/pipeline_ng/pipeline_context.h"
#include "js_third_provider_interaction_operation_utils.h"

namespace OHOS::Ace::Framework {
namespace {
void LogAccessibilityElementInfo(
    const std::string& tag, const Accessibility::AccessibilityElementInfo& info)
{
    std::string printStr;
    printStr.append(tag).append(", info: [");
    printStr.append("accessibilityId: ").append(std::to_string(info.GetAccessibilityId()));
    printStr.append(", accessibilityText: ").append(info.GetAccessibilityText());
    printStr.append(", childCount: ").append(std::to_string(info.GetChildCount()));
    printStr.append(", windowId: ").append(std::to_string(info.GetWindowId()));
    printStr.append(", parentNodeId: ").append(std::to_string(info.GetParentNodeId()));
    printStr.append(", checkable: ").append(info.IsCheckable() ? "true" : "false");
    printStr.append(", checked: ").append(info.IsChecked() ? "true" : "false");
    printStr.append(", focusable: ").append(info.IsFocusable() ? "true" : "false");
    printStr.append(", focused: ").append(info.IsFocused() ? "true" : "false");
    printStr.append(", visible: ").append(info.IsVisible() ? "true" : "false");
    printStr.append(", hasAccessibilityFocus: ")
        .append(info.HasAccessibilityFocus() ? "true" : "false");
    printStr.append(", selected: ").append(info.IsSelected() ? "true" : "false");
    printStr.append(", clickable: ").append(info.IsClickable() ? "true" : "false");
    printStr.append(", longClickable: ").append(info.IsLongClickable() ? "true" : "false");
    printStr.append(", enabled: ").append(info.IsEnabled() ? "true" : "false");
    printStr.append(", componentType: ").append(info.GetComponentType());
    printStr.append(", content: ").append(info.GetContent());
    printStr.append(", pageId: ").append(std::to_string(info.GetPageId()));
    printStr.append(", triggerAction: ")
        .append(std::to_string(static_cast<int32_t>(info.GetTriggerAction())));
    printStr.append(", accessibilityText: ").append(info.GetAccessibilityText());
    printStr.append(", childTreeId: ").append(std::to_string(info.GetChildTreeId()));
    printStr.append(", belongTreeId: ").append(std::to_string(info.GetBelongTreeId()));
    printStr.append(", parentWindowId: ").append(std::to_string(info.GetParentWindowId()));
    printStr.append(", accessibilityGroup: ").append(info.GetAccessibilityGroup() ? "true" : "false");
    std::string actionStr;
    actionStr.append("{");
    for (const auto& action : info.GetActionList()) {
        actionStr.append(std::to_string(
            static_cast<int32_t>(action.GetActionType()))).append(" ");
    }
    actionStr.append("}");
    printStr.append(", action: ").append(actionStr);
    printStr.append("]");
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "%{public}s", printStr.c_str());
}

void LogAccessibilityEventInfo(
    const std::string& tag, const Accessibility::AccessibilityEventInfo& info)
{
    std::string printStr;
    printStr.append(tag).append(", info: [");
    printStr.append("accessibilityId: ").append(std::to_string(info.GetAccessibilityId()));
    printStr.append(", windowId: ").append(std::to_string(info.GetWindowId()));
    printStr.append(", viewId: ").append(std::to_string(info.GetViewId()));
    printStr.append(", componentType: ").append(info.GetComponentType());
    printStr.append(", pageId: ").append(std::to_string(info.GetPageId()));
    printStr.append(", eventType: ").append(
        std::to_string(static_cast<int32_t>(info.GetEventType())));
    printStr.append(", triggerAction: ").append(
        std::to_string(static_cast<int32_t>(info.GetTriggerAction())));
    printStr.append(", requestFocusElementId: ").append(
        std::to_string(info.GetRequestFocusElementId()));
    printStr.append("]");
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "%{public}s", printStr.c_str());
}

void CopyNativeInfoToAccessibilityElementInfo(
    const ArkUI_AccessibilityElementInfo& elementInfo,
    const NodeConfig& config,
    Accessibility::AccessibilityElementInfo& info)
{
    TransformAccessbilityElementInfo(elementInfo, info);
    JsThirdProviderInteractionOperation::FillNodeConfig(config, info);
}

void CopyNativeInfosToAccessibilityElementInfos(
    const std::vector<ArkUI_AccessibilityElementInfo>& nativeInfos,
    const NodeConfig& config,
    std::list<Accessibility::AccessibilityElementInfo>& infos)
{
    for (const auto& nativeInfo : nativeInfos) {
        Accessibility::AccessibilityElementInfo info;
        TransformAccessbilityElementInfo(nativeInfo, info);
        JsThirdProviderInteractionOperation::FillNodeConfig(config, info);
        infos.push_back(info);
    }
}

bool CheckEventIgnoreHostOffset(
    const ArkUI_AccessibilityEventInfo& nativeAccessibilityEvent)
{
    auto eventType = nativeAccessibilityEvent.GetEventType();
    bool ignoreHostOffset = false;
    switch (eventType) {
        case ArkUI_AccessibilityEventType::
            ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_FOCUS_NODE_UPDATE:
            TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY, "ignoreHostOffset keep false by focus update");
            ignoreHostOffset = true;
            break;
        default:
            TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY, "ignoreHostOffset keep false by other eventType");
    }
    return ignoreHostOffset;
}

void RemoveKeysForClickAction(
    int32_t action,
    std::map<std::string, std::string>& args)
{
    auto aceAction = static_cast<ActionType>(action);
    if (aceAction != ActionType::ACCESSIBILITY_ACTION_CLICK) {
        return;
    }

    args.erase(ACTION_ARGU_CLICK_ENHANCE_DATA);
    args.erase(ACTION_ARGU_CLICK_TIMESTAMP);
}
} // namespace

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

void JsThirdProviderInteractionOperation::FillNodeConfig(
    const NodeConfig& config, Accessibility::AccessibilityElementInfo& info)
{
    OHOS::Accessibility::Rect oldRect = info.GetRectInScreen();
    OHOS::Accessibility::Rect newRect = OHOS::Accessibility::Rect(
        oldRect.GetLeftTopXScreenPostion() * config.scaleX + static_cast<int32_t>(config.offset.GetX()),
        oldRect.GetLeftTopYScreenPostion() * config.scaleY + static_cast<int32_t>(config.offset.GetY()),
        oldRect.GetRightBottomXScreenPostion() * config.scaleX + static_cast<int32_t>(config.offset.GetX()),
        oldRect.GetRightBottomYScreenPostion() * config.scaleY + static_cast<int32_t>(config.offset.GetY()));
    info.SetRectInScreen(newRect);
    info.SetPageId(config.pageId);
    info.SetWindowId(config.windowId);
    info.SetBelongTreeId(config.belongTreeId);
    info.SetChildTreeIdAndWinId(config.childTreeId, config.childWindowId);
    info.SetParentWindowId(config.parentWindowId);
    info.SetBundleName(config.bundleName);
    info.SetInspectorKey(config.inspectorKey);
    int64_t splitElementId = info.GetAccessibilityId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(config.belongTreeId, splitElementId);
    info.SetAccessibilityId(splitElementId);
}

RetError JsThirdProviderInteractionOperation::SearchElementInfoByAccessibilityId(
    const int64_t elementId, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback, const int32_t mode)
{
    uint32_t realMode = mode;
    if (realMode & static_cast<uint32_t>(PREFETCH_RECURSIVE_CHILDREN_REDUCED)) {
        realMode &= ~static_cast<uint32_t>(PREFETCH_RECURSIVE_CHILDREN_REDUCED);
        realMode |= static_cast<uint32_t>(PREFETCH_RECURSIVE_CHILDREN);
    }
    // 1. Get real elementId
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        elementId, splitElementId, splitTreeId);

    // 2. FindAccessibilityNodeInfosById by provider
    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = FindAccessibilityNodeInfosByIdFromProvider(
        splitElementId, realMode, requestId, infos);
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "SearchElementInfoByAccessibilityId failed.");
        infos.clear();
    }

    // 3. Return result
    SetSearchElementInfoByAccessibilityIdResult(callback, std::move(infos), requestId);
    return RET_OK;
}

bool JsThirdProviderInteractionOperation::FindNativeInfoById(
    const WeakPtr<AccessibilityProvider>& accessibilityProvider,
    int64_t splitElementId,
    std::shared_ptr<ArkUI_AccessibilityElementInfo>& nativeInfo)
{
    CHECK_NULL_RETURN(nativeInfo, false);
    auto provider = accessibilityProvider.Upgrade();
    CHECK_NULL_RETURN(provider, false);
    std::vector<ArkUI_AccessibilityElementInfo> nativeInfos;
    int32_t code = provider->FindAccessibilityNodeInfosById(
        splitElementId, 0, 0, nativeInfos);
    if (code != 0) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "FindNativeInfoById failed: %{public}d", code);
        return false;
    }
    if (nativeInfos.empty()) {
        return false;
    }
    *nativeInfo = nativeInfos.front();
    return true;
}

bool JsThirdProviderInteractionOperation::FindAccessibilityNodeInfosByIdFromProvider(
    const int64_t splitElementId, const int32_t mode, const int32_t requestId,
    std::list<Accessibility::AccessibilityElementInfo>& infos, bool ignoreHostOffset)
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
    config.ignoreHostOffset = ignoreHostOffset;
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

void JsThirdProviderInteractionOperation::SearchElementInfoBySpecificProperty(const int64_t elementId,
    const SpecificPropertyParam &param, const int32_t requestId,
    AccessibilityElementOperatorCallback &callback)
{
    std::list<AccessibilityElementInfo> infos;
    std::list<AccessibilityElementInfo> treeInfos;
    callback.SetSearchElementInfoBySpecificPropertyResult(infos, treeInfos, requestId);
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
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "SearchElementInfosByText failed.");
        infos.clear();
    }

    // 3. Return result
    SetSearchElementInfoByTextResult(callback, std::move(infos), requestId);
}

void JsThirdProviderInteractionOperation::SearchDefaultFocusByWindowId(
    const int32_t windowId, const int32_t requestId,
    Accessibility::AccessibilityElementOperatorCallback& callback, const int32_t pageId)
{
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
    Accessibility::AccessibilityElementInfo info;
    bool ret = FindFocusedElementInfoFromProvider(
        splitElementId, focusType, requestId, info);
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "SearchElementInfosByText failed.");
        info.SetValidElement(false);
    }

    // 3. Return result
    SetFindFocusedElementInfoResult(callback, info, requestId);
}

bool JsThirdProviderInteractionOperation::FindFocusedElementInfoFromProvider(
    int64_t elementId, const int32_t focusType, const int32_t requestId,
    Accessibility::AccessibilityElementInfo& info)
{
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_RETURN(provider, false);
    ArkUI_AccessibilityElementInfo nativeInfo;
    int32_t code = provider->FindFocusedAccessibilityNode(
        elementId, focusType, requestId, nativeInfo);
    if (code != 0) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "FindFocusedElementInfoFromProvider failed: %{public}d", code);
        return false;
    }

    NodeConfig config;
    GetNodeConfig(config);
    CopyNativeInfoToAccessibilityElementInfo(nativeInfo, config, info);
    return true;
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
    Accessibility::AccessibilityElementInfo info;
    bool ret = FocusMoveSearchProvider(
        splitElementId, direction, requestId, info);
    // 3. Return result
    if (!ret) {
        auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
        CHECK_NULL_VOID(jsAccessibilityManager);
        auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
        CHECK_NULL_VOID(context);
        CHECK_NULL_VOID(context->GetTaskExecutor());
        context->GetTaskExecutor()->PostTask(
            [jsMgr = jsAccessibilityManager_, weakHost = host_, &callback, requestId] () {
                auto jsAccessibilityManager = jsMgr.Upgrade();
                if ((!jsAccessibilityManager) || (!jsAccessibilityManager->IsRegister())) {
                    AccessibilityElementInfo nodeInfo;
                    nodeInfo.SetValidElement(false);
                    callback.SetFocusMoveSearchResult(nodeInfo, requestId);
                    return;
                }
                jsAccessibilityManager->SetFocusMoveResultWithNode(weakHost, callback, requestId);
            }, TaskExecutor::TaskType::UI, "AccessibilityThirdPartyFocusMoveSearchFail");
    } else {
        SetFocusMoveSearchResult(callback, info, requestId);
    }
}

bool JsThirdProviderInteractionOperation::FocusMoveSearchProvider(
    int64_t elementId, const int32_t direction, const int32_t requestId,
    Accessibility::AccessibilityElementInfo& info)
{
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_RETURN(provider, false);
    ArkUI_AccessibilityElementInfo nativeInfo;
    int32_t code = provider->FindNextFocusAccessibilityNode(
        elementId, direction, requestId, nativeInfo);
    if (code != 0) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "FocusMoveSearchProvider failed: %{public}d", code);
        return false;
    }

    NodeConfig config;
    GetNodeConfig(config);
    CopyNativeInfoToAccessibilityElementInfo(nativeInfo, config, info);
    return true;
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

void JsThirdProviderInteractionOperation::HandleActionWhenFindNodeFail(const int32_t action)
{
    if (action == static_cast<int32_t>(
        Accessibility::ActionType::ACCESSIBILITY_ACTION_CLEAR_ACCESSIBILITY_FOCUS)) {
        ClearDrawBound();
    }
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

    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "ExecuteAction elementId: %{public}" PRId64 ","
        " action: %{public}d, requestId: %{public}d, splitElementId: %{public}" PRId64 ","
        " splitTreeId: %{public}d",
        elementId, action, requestId, splitElementId, splitTreeId);
    // 2. FindNextFocusAccessibilityNode from provider
    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = FindAccessibilityNodeInfosByIdFromProvider(
        splitElementId, 0, requestId, infos, true); // for drawbound, no need fix host offset
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "Find info failed when ExecuteAction.");
        SetExecuteActionResult(callback, false, requestId);
        HandleActionWhenFindNodeFail(action);
        return;
    }

    // 3. DrawBound
    ExecuteActionForThird(splitElementId, infos.front(), action);

    //4. ExecuteAccessibilityAction To provider
    ret = ExecuteActionFromProvider(splitElementId, action, actionArguments, requestId);
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY, "ExecuteAccessibilityAction failed.");
    }

    // 5. Return result
    SetExecuteActionResult(callback, ret, requestId);
}

bool JsThirdProviderInteractionOperation::ExecuteActionFromProvider(
    int64_t elementId, const int32_t action,
    const std::map<std::string, std::string>& actionArguments, const int32_t requestId)
{
    auto actionFilteredArguments = actionArguments;
    RemoveKeysForClickAction(action, actionFilteredArguments);

    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_RETURN(provider, false);
    int32_t code = provider->ExecuteAccessibilityAction(
        elementId, action, requestId, actionFilteredArguments);
    if (code != 0) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "ExecuteActionFromProvider failed: %{public}d", code);
        return false;
    }

    return true;
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
    // 1. Clear focus from provider
    ClearFocusFromProvider();
    // 2. Clear DrawBound
    ClearDrawBound();
}

bool JsThirdProviderInteractionOperation::ClearFocusFromProvider()
{
    auto provider = accessibilityProvider_.Upgrade();
    CHECK_NULL_RETURN(provider, false);
    int32_t code = provider->ClearFocusedAccessibilityNode();
    if (code != 0) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "ExecuteActionFromProvider failed: %{public}d", code);
        return false;
    }
    return true;
}

bool JsThirdProviderInteractionOperation::ClearDrawBound()
{
    auto jsAccessibilityManager = jsAccessibilityManager_.Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    auto hostNode = GetHost();
    CHECK_NULL_RETURN(hostNode, false);
    return jsAccessibilityManager->ClearThirdAccessibilityFocus(hostNode);
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

void JsThirdProviderInteractionOperation::GetHostRectTranslateInfo(NodeConfig& config)
{
    auto host = host_.Upgrade();
    if ((!host) || config.ignoreHostOffset) {
        config.offset = NG::OffsetF(0, 0);
        config.scaleX = 1.0f;
        config.scaleY = 1.0f;
        return;
    }
    auto rect = host->GetTransformRectRelativeToWindow();
    NG::VectorF finalScale = host->GetTransformScaleRelativeToWindow();
    auto pipeline = host->GetContextRefPtr();
    if (pipeline) {
        auto accessibilityManager = pipeline->GetAccessibilityManager();
        if (accessibilityManager) {
            auto windowInfo = accessibilityManager->GenerateWindowInfo(host, pipeline);
            auto top = rect.Top() * windowInfo.scaleY + static_cast<int32_t>(windowInfo.top);
            auto left = rect.Left() * windowInfo.scaleX + static_cast<int32_t>(windowInfo.left);
            finalScale.x *= windowInfo.scaleX;
            finalScale.y *= windowInfo.scaleY;
            config.offset = NG::OffsetT(left, top);
        } else {
            auto windowRect = pipeline->GetDisplayWindowRectInfo();
            auto top = rect.Top() + static_cast<int32_t>(windowRect.Top());
            auto left = rect.Left() + static_cast<int32_t>(windowRect.Left());
            config.offset = NG::OffsetT(left, top);
        }
    }
    
    config.scaleX = finalScale.x;
    config.scaleY = finalScale.y;
}

void JsThirdProviderInteractionOperation::GetNodeConfig(NodeConfig& config)
{
    auto host = host_.Upgrade();
    CHECK_NULL_VOID(host);
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_VOID(jsAccessibilityManager);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_VOID(context);
    config.pageId = host->GetPageId();
    config.windowId = static_cast<int32_t>(context->GetRealHostWindowId());
    config.belongTreeId = belongTreeId_;
    config.parentWindowId = static_cast<int32_t>(context->GetRealHostWindowId());
    config.bundleName = AceApplicationInfo::GetInstance().GetPackageName();

    GetHostRectTranslateInfo(config);
}

void JsThirdProviderInteractionOperation::SetChildTreeIdAndWinId(
    const int64_t nodeId, const int32_t treeId, const int32_t childWindowId)
{
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "SetChildTreeIdAndWinId, node: %{public}" PRId64 ","
        "treeId: %{public}d, childWindowId: %{public}d", nodeId, treeId, childWindowId);
}

void JsThirdProviderInteractionOperation::SetBelongTreeId(const int32_t treeId)
{
    TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY, "SetBelongTreeId treeId: %{public}d", treeId);
    belongTreeId_ = treeId;
}

int32_t JsThirdProviderInteractionOperation::SendAccessibilityAsyncEventForThird(
    int64_t thirdElementId,
    Accessibility::EventType eventType)
{
    // 1. generate event
    Accessibility::AccessibilityEventInfo event;
    event.SetTimeStamp(GetMicroTickCount());
    event.SetWindowChangeTypes(
        Accessibility::WindowUpdateType::WINDOW_UPDATE_INVALID);
    event.SetWindowContentChangeTypes(
        Accessibility::WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
    event.SetSource(thirdElementId);
    event.SetEventType(eventType);
    event.SetBundleName(AceApplicationInfo::GetInstance().GetPackageName());

    // 2. get element from third
    // cut tree id
    int64_t splitElementId = AccessibilityElementInfo::UNDEFINED_ACCESSIBILITY_ID;
    int32_t splitTreeId = AccessibilityElementInfo::UNDEFINED_TREE_ID;
    AccessibilitySystemAbilityClient::GetTreeIdAndElementIdBySplitElementId(
        thirdElementId, splitElementId, splitTreeId);
    std::list<Accessibility::AccessibilityElementInfo> infos;
    bool ret = FindAccessibilityNodeInfosByIdFromProvider(
        splitElementId, 0, 0, infos);
    if ((!ret) || (infos.size() == 0)) {
        return -1;
    }

    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, -1);
    jsAccessibilityManager->UpdateElementInfosTreeId(infos);
    event.SetElementInfo(infos.front());

    // 3. change event info by host info
    GetAccessibilityEventInfoFromNativeEvent(event, false);

    // 4. SendEvent
    auto host = host_.Upgrade();
    CHECK_NULL_RETURN(host, -1);
    SendAccessibilitySyncEventToService(event, nullptr);
    return 0;
}

bool JsThirdProviderInteractionOperation::HandleNativeFocusUpdate(
    int64_t elementId,
    Accessibility::AccessibilityEventInfo& accessibilityEventInfo)
{
    ExecuteActionForThird(
        elementId,
        accessibilityEventInfo.GetElementInfo(),
        static_cast<int32_t>(
            Accessibility::ActionType::ACCESSIBILITY_ACTION_ACCESSIBILITY_FOCUS));
    return false;
}

bool JsThirdProviderInteractionOperation::HandleEventByFramework(
    const ArkUI_AccessibilityEventInfo& nativeAccessibilityEvent,
    Accessibility::AccessibilityEventInfo& accessibilityEventInfo)
{
    auto eventType = nativeAccessibilityEvent.GetEventType();
    bool needSendEvent = true;
    switch (eventType) {
        case ArkUI_AccessibilityEventType::
            ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_FOCUS_NODE_UPDATE:
            if (nativeAccessibilityEvent.GetElementInfo()) {
                needSendEvent = HandleNativeFocusUpdate(
                    nativeAccessibilityEvent.GetElementInfo()->GetElementId(),
                    accessibilityEventInfo);
            }
            break;
        default:
            TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "Unsupported eventType");
    }
    return needSendEvent;
}

int32_t JsThirdProviderInteractionOperation::SendAccessibilityAsyncEvent(
    const ArkUI_AccessibilityEventInfo& nativeAccessibilityEvent,
    void (*callback)(int32_t errorCode))
{
    bool ignoreHostOffset = CheckEventIgnoreHostOffset(nativeAccessibilityEvent);
    // 1. Get OHOS::Accessibility::AccessibilityEventInfo
    OHOS::Accessibility::AccessibilityEventInfo accessibilityEventInfo;
    GetAccessibilityEventInfoFromNativeEvent(
        nativeAccessibilityEvent, accessibilityEventInfo, ignoreHostOffset);

    // 2. handleEvent by frame work
    bool needSendEvent =  HandleEventByFramework(
        nativeAccessibilityEvent,
        accessibilityEventInfo);
    // 3. SendEvent
    if (needSendEvent) {
        auto jsAccessibilityManager = GetHandler().Upgrade();
        CHECK_NULL_RETURN(jsAccessibilityManager, -1);
        auto host = host_.Upgrade();
        CHECK_NULL_RETURN(host, -1);
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "Inner SendAccessibilityAsyncEvent");
        SendAccessibilitySyncEventToService(accessibilityEventInfo, callback);
    }
    callback(0);
    return 0;
}

void JsThirdProviderInteractionOperation::GetAccessibilityEventInfoFromNativeEvent(
    OHOS::Accessibility::AccessibilityEventInfo& accessibilityEventInfo,
    bool ignoreHostOffset)
{
    // 1. Fill node config
    NodeConfig config;
    config.ignoreHostOffset = ignoreHostOffset;
    GetNodeConfig(config);

    // 1.1. Fill elementInfo config
    auto elementInfo = accessibilityEventInfo.GetElementInfo();
    JsThirdProviderInteractionOperation::FillNodeConfig(config, elementInfo);
    int64_t elementId = elementInfo.GetAccessibilityId();
    AccessibilitySystemAbilityClient::SetSplicElementIdTreeId(belongTreeId_, elementId);
    elementInfo.SetAccessibilityId(elementId);

    // 1.2. Fill eventInfo config
    accessibilityEventInfo.SetPageId(config.pageId);
    accessibilityEventInfo.SetWindowId(config.windowId);
    accessibilityEventInfo.SetSource(elementId);
    accessibilityEventInfo.SetComponentType(elementInfo.GetComponentType());
    accessibilityEventInfo.AddContent(elementInfo.GetContent());
    accessibilityEventInfo.SetElementInfo(elementInfo);
    LogAccessibilityElementInfo("sendEvent", elementInfo);
    LogAccessibilityEventInfo("sendEvent", accessibilityEventInfo);
}

void JsThirdProviderInteractionOperation::GetAccessibilityEventInfoFromNativeEvent(
    const ArkUI_AccessibilityEventInfo& nativeEventInfo,
    OHOS::Accessibility::AccessibilityEventInfo& accessibilityEventInfo,
    bool ignoreHostOffset)
{
    // 1. Transform native event to OHOS::Accessibility::AccessibilityEventInfo
    TransformAccessbilityEventInfo(
        nativeEventInfo, accessibilityEventInfo);

    // 2. Transform Accessibility::AccessibilityEventInfo with host info
    GetAccessibilityEventInfoFromNativeEvent(accessibilityEventInfo, ignoreHostOffset);
}

bool JsThirdProviderInteractionOperation::SendAccessibilitySyncEventToService(
    const OHOS::Accessibility::AccessibilityEventInfo& eventInfo,
    [[maybe_unused]] void (*callback)(int32_t errorCode))
{
    auto jsAccessibilityManager = GetHandler().Upgrade();
    CHECK_NULL_RETURN(jsAccessibilityManager, false);
    auto context = jsAccessibilityManager->GetPipelineContext().Upgrade();
    CHECK_NULL_RETURN(context, false);
    CHECK_NULL_RETURN(context->GetTaskExecutor(), false);
    context->GetTaskExecutor()->PostTask(
        [jsMgr = jsAccessibilityManager_, eventInfo] () mutable {
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
