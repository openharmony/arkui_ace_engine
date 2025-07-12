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

#include "core/components_ng/manager/navigation/navigation_manager.h"

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t INDENT_SIZE = 2;
constexpr char INTENT_PARAM_KEY[] = "ohos.insightIntent.executeParam.param";
constexpr char INTENT_NAVIGATION_ID_KEY[] = "ohos.insightIntent.pageParam.navigationId";
constexpr char INTENT_NAVDESTINATION_NAME_KEY[] = "ohos.insightIntent.pageParam.navDestinationName";

bool NavigationManager::IsOuterMostNavigation(int32_t nodeId, int32_t depth)
{
    if (dumpMap_.empty()) {
        return false;
    }
    auto outerMostKey = dumpMap_.begin()->first;
    return outerMostKey == DumpMapKey(nodeId, depth);
}

void NavigationManager::AddNavigationDumpCallback(int32_t nodeId, int32_t depth, const DumpCallback& callback)
{
    CHECK_RUN_ON(UI);
    dumpMap_.emplace(DumpMapKey(nodeId, depth), callback);
}

void NavigationManager::RemoveNavigationDumpCallback(int32_t nodeId, int32_t depth)
{
    CHECK_RUN_ON(UI);
    auto it = dumpMap_.find(DumpMapKey(nodeId, depth));
    if (it != dumpMap_.end()) {
        dumpMap_.erase(it);
    }
}

void NavigationManager::OnDumpInfo()
{
    CHECK_RUN_ON(UI);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto rootNode = pipeline->GetRootElement();
    if (!rootNode) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "navigation dump failed, invalid root node");
        return;
    }
    DumpLog::GetInstance().Print("Navigation number: " + std::to_string(dumpMap_.size()));
    std::stack<std::pair<RefPtr<UINode>, int32_t>> stack;
    stack.push({ rootNode, 0 });
    while (!stack.empty()) {
        auto [curNode, curDepth] = stack.top();
        stack.pop();
        std::string space(INDENT_SIZE * curDepth, ' ');
        int32_t depth = 0;
        if (curNode->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
            auto navigation = AceType::DynamicCast<NavigationGroupNode>(curNode);
            CHECK_NULL_VOID(navigation);
            DumpLog::GetInstance().Print(space + navigation->ToDumpString());
            depth++;
        } else if (curNode->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(curNode);
            CHECK_NULL_VOID(navDestination);
            DumpLog::GetInstance().Print(space + navDestination->ToDumpString());
            depth++;
            auto parent = curNode->GetParent();
            if (!stack.empty() && parent && parent->GetTag() == V2::PRIMARY_CONTENT_NODE_ETS_TAG &&
                stack.top().first->GetTag() != V2::NAVDESTINATION_VIEW_ETS_TAG) {
                DumpLog::GetInstance().Print("----------------------------------------------------------");
            }
        } else if (curNode->GetTag() == V2::NAVBAR_ETS_TAG) {
            DumpLog::GetInstance().Print(space + "| [/]{ NavBar }");
            DumpLog::GetInstance().Print("----------------------------------------------------------");
        }
        const auto& children = curNode->GetChildren();
        for (auto it = children.rbegin(); it != children.rend(); it++) {
            if (!(*it)) {
                continue;
            }
            stack.push({ *it, curDepth + depth });
        }
    }
}

void NavigationManager::FireNavigationUpdateCallback()
{
    for (const auto& func : updateCallbacks_) {
        func();
    }
    updateCallbacks_.clear();
}

std::shared_ptr<NavigationInfo> NavigationManager::GetNavigationInfo(const RefPtr<AceType>& node)
{
    RefPtr<UINode> current = nullptr;
    auto customNode = AceType::DynamicCast<CustomNode>(node);
    if (customNode) {
        current = customNode->GetNavigationNode().Upgrade();
    }

    if (!current) {
        current = AceType::DynamicCast<UINode>(node);
        while (current) {
            if (current->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
                break;
            }
            current = current->GetParent();
        }
    }

    if (!current) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "find parent navigation node failed");
        return nullptr;
    }

    auto navigation = AceType::DynamicCast<NavigationGroupNode>(current);
    CHECK_NULL_RETURN(navigation, nullptr);
    auto pattern = navigation->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto stack = pattern->GetNavigationStack();
    CHECK_NULL_RETURN(stack, nullptr);
    return std::make_shared<NavigationInfo>(navigation->GetInspectorId().value_or(""), stack, navigation->GetId());
}

bool NavigationManager::AddInteractiveAnimation(const std::function<void()>& addCallback)
{
    if (!isInteractive_) {
        return false;
    }
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(
        FrameNode::GetFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, interactiveAnimationId_));
    CHECK_NULL_RETURN(navigationGroupNode, false);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto proxy = pattern->GetTopNavigationProxy();
    CHECK_NULL_RETURN(proxy, false);
    proxy->AddInteractiveAnimation(addCallback);
    return true;
}

bool NavigationManager::CheckNodeNeedCache(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);

    auto context = node->GetRenderContext();
    if ((context && context->GetAnimationsCount() != 0) || node->GetTag() == V2::UI_EXTENSION_COMPONENT_ETS_TAG) {
        return false;
    }
    std::stack<RefPtr<FrameNode>> nodeStack;
    nodeStack.push(node);
    while (!nodeStack.empty()) {
        auto curNode = nodeStack.top();
        nodeStack.pop();
        std::list<RefPtr<FrameNode>> children;
        curNode->GenerateOneDepthVisibleFrameWithTransition(children);
        for (auto& child : children) {
            if (!child) {
                continue;
            }
            auto childContext = child->GetRenderContext();
            if ((childContext && childContext->GetAnimationsCount() != 0) ||
                child->GetTag() == V2::UI_EXTENSION_COMPONENT_ETS_TAG) {
                return false;
            }
            nodeStack.push(child);
        }
        auto overlayNode = curNode->GetOverlayNode();
        if (overlayNode) {
            auto overlayNodeContext = overlayNode->GetRenderContext();
            if ((overlayNodeContext && overlayNodeContext->GetAnimationsCount() != 0) ||
                overlayNode->GetTag() == V2::UI_EXTENSION_COMPONENT_ETS_TAG) {
                return false;
            }
            nodeStack.push(overlayNode);
        }
    }
    return true;
}

RefPtr<FrameNode> NavigationManager::GetNavDestContentFrameNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto navDestinationNodeBase = AceType::DynamicCast<NavDestinationNodeBase>(node);
    CHECK_NULL_RETURN(navDestinationNodeBase, nullptr);
    auto navDestContentFrameNode = AceType::DynamicCast<FrameNode>(navDestinationNodeBase->GetContentNode());
    CHECK_NULL_RETURN(navDestContentFrameNode, nullptr);
    return navDestContentFrameNode;
}

void NavigationManager::UpdatePreNavNodeRenderGroupProperty()
{
    auto preNavNode = preNavNode_.Upgrade();
    CHECK_NULL_VOID(preNavNode);
    auto preNavDestContentNode = GetNavDestContentFrameNode(preNavNode);
    CHECK_NULL_VOID(preNavDestContentNode);
    auto state = CheckNodeNeedCache(preNavDestContentNode);
    UpdateAnimationCachedRenderGroup(preNavDestContentNode, state);
    preNodeAnimationCached_ = state;
    preNodeNeverSet_ = false;
    auto preNavPattern = preNavNode->GetPattern<NavDestinationPattern>();
    auto name = preNavPattern == nullptr ? "NavBar" : preNavPattern->GetName();
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "Cache PreNavNode, name=%{public}s, will cache? %{public}s", name.c_str(),
        state ? "yes" : "no");
}

void NavigationManager::UpdateCurNavNodeRenderGroupProperty()
{
    auto curNavNode = curNavNode_.Upgrade();
    CHECK_NULL_VOID(curNavNode);
    auto curNavDestContentNode = GetNavDestContentFrameNode(curNavNode);
    CHECK_NULL_VOID(curNavDestContentNode);
    auto state = CheckNodeNeedCache(curNavDestContentNode);
    UpdateAnimationCachedRenderGroup(curNavDestContentNode, state);
    curNodeAnimationCached_ = state;
    currentNodeNeverSet_ = false;
    auto curNavPattern = curNavNode->GetPattern<NavDestinationPattern>();
    auto name = curNavPattern == nullptr ? "NavBar" : curNavPattern->GetName();
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "Cache CurNavNode, name=%{public}s, will cache? %{public}s", name.c_str(),
        state ? "yes" : "no");
}

void NavigationManager::SetForceSplitEnable(bool isForceSplit, const std::string& homePage, bool ignoreOrientation)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "set navigation force split %{public}s, homePage:%{public}s, "
        "ignoreOrientation:%{public}d", (isForceSplit ? "enable" : "disable"), homePage.c_str(), ignoreOrientation);
    /**
     * As long as the application supports force split, regardless of whether it is enabled or not,
     * the SetForceSplitleEnable interface will be called.
     */
    isForceSplitSupported_ = true;
    if (isForceSplitEnable_ == isForceSplit && homePageName_ == homePage && ignoreOrientation_ == ignoreOrientation) {
        return;
    }
    isForceSplitEnable_ = isForceSplit;
    homePageName_ = homePage;
    ignoreOrientation_ = ignoreOrientation;

    auto listeners = forceSplitListeners_;
    for (auto& listener : listeners) {
        if (listener.second) {
            listener.second();
        }
    }
}

void NavigationManager::AddForceSplitListener(int32_t nodeId, std::function<void()>&& listener)
{
    forceSplitListeners_[nodeId] = std::move(listener);
}

void NavigationManager::RemoveForceSplitListener(int32_t nodeId)
{
    auto it = forceSplitListeners_.find(nodeId);
    if (it != forceSplitListeners_.end()) {
        forceSplitListeners_.erase(it);
    }
}

void NavigationManager::ResetCurNavNodeRenderGroupProperty()
{
    auto curNavNode = curNavNode_.Upgrade();
    CHECK_NULL_VOID(curNavNode);
    auto curNavDestContentNode = GetNavDestContentFrameNode(curNavNode);
    CHECK_NULL_VOID(curNavDestContentNode);
    UpdateAnimationCachedRenderGroup(curNavDestContentNode, false);
    curNodeAnimationCached_ = false;
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "Cancel Cache CurNavNode node(id=%{public}d name=%{public}s)",
        curNavDestContentNode->GetId(), curNavDestContentNode->GetTag().c_str());
}

void NavigationManager::CacheNavigationNodeAnimation()
{
    if (!hasCacheNavigationNodeEnable_) {
        return;
    }
    if (!IsNavigationInAnimation()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    /**
     * If the exit page has not been cached before, or if the already cached exit page changes again,
     * cache the exit page for future use.
     */
    if (preNodeNeverSet_ || (isNodeAddAnimation_ && preNodeAnimationCached_)) {
        UpdatePreNavNodeRenderGroupProperty();
        isNodeAddAnimation_ = false;
    }
    //  Cache the entry page for future use
    if (currentNodeNeverSet_ && !curNodeAnimationCached_ && !pipeline->GetIsRequestVsync()) {
        UpdateCurNavNodeRenderGroupProperty();
    }
    // If the cached entry page changes again, cancel the previously marked entry page.
    if (!currentNodeNeverSet_) {
        ResetCurNavNodeRenderGroupProperty();
    }
}

void NavigationManager::UpdateAnimationCachedRenderGroup(const RefPtr<FrameNode>& node, bool isSet)
{
    auto context = node->GetRenderContext();
    CHECK_NULL_VOID(context);
    TAG_LOGD(AceLogTag::ACE_NAVIGATION,
        "UpdateAnimationCachedRenderGroup node(id=%{public}d name=%{public}s), isSet=%{public}d", node->GetId(),
        node->GetTag().c_str(), isSet);
    context->UpdateRenderGroup(isSet, false, false);
}

bool NavigationManager::AddRecoverableNavigation(std::string id, RefPtr<AceType> navigationNode)
{
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(navigationNode);
    CHECK_NULL_RETURN(navigation, false);
    if (!navigation->CanRecovery() || id != navigation->GetCurId()) {
        return false;
    }
    recoverableNavigationMap_[id] = navigationNode;
    return true;
}

std::unique_ptr<JsonValue> NavigationManager::GetNavigationJsonInfo()
{
    auto allNavigationInfo = JsonUtil::CreateArray(true);
    for (auto iter : recoverableNavigationMap_) {
        auto node = iter.second.Upgrade();
        if (!node) {
            continue;
        }
        auto navigation = AceType::DynamicCast<NavigationGroupNode>(node);
        if (!navigation->CanRecovery()) {
            continue;
        }
        auto navigationPattern = navigation->GetPattern<NavigationPattern>();
        if (!navigationPattern) {
            continue;
        }
        auto navigationInfo = JsonUtil::Create(true);
        navigationInfo->Put("id", iter.first.c_str());
        navigationInfo->Put("stack", navigationPattern->GetNavdestinationJsonArray());
        allNavigationInfo->Put(navigationInfo);
    }
    return allNavigationInfo;
}

void NavigationManager::StorageNavigationRecoveryInfo(std::unique_ptr<JsonValue> navigationRecoveryInfo)
{
    auto allNavigationInfo = std::move(navigationRecoveryInfo);
    if (!allNavigationInfo || !allNavigationInfo->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Navigation recovery info invalid, can not restore!");
        return;
    }
    auto arraySize = allNavigationInfo->GetArraySize();
    for (int32_t i = 0; i < arraySize; ++ i) {
        auto navigationInfo = allNavigationInfo->GetArrayItem(i);
        auto navigationId = navigationInfo->GetString("id");
        auto stackInfo = navigationInfo->GetValue("stack");
        if (!stackInfo->IsArray()) {
            continue;
        }
        std::vector<NavdestinationRecoveryInfo> navdestinationsInfo;
        auto stackSize = stackInfo->GetArraySize();
        for (int32_t j = 0; j < stackSize; ++ j) {
            auto navdestinationInfo = stackInfo->GetArrayItem(j);
            auto name = navdestinationInfo->GetString("name");
            auto param = navdestinationInfo->GetString("param");
            auto mode = navdestinationInfo->GetInt("mode");
            navdestinationsInfo.emplace_back(NavdestinationRecoveryInfo(name, param, mode));
        }
        navigationRecoveryInfo_[navigationId] = navdestinationsInfo;
    }
}

const std::vector<NavdestinationRecoveryInfo> NavigationManager::GetNavigationRecoveryInfo(std::string navigationId)
{
    if (navigationRecoveryInfo_.find(navigationId) == navigationRecoveryInfo_.end()) {
        return {};
    }
    auto ret = navigationRecoveryInfo_[navigationId];
    navigationRecoveryInfo_.erase(navigationId);
    return ret;
}

void NavigationManager::AddNavigation(int32_t parentNodeId, const RefPtr<FrameNode>& navigationNode)
{
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(navigationNode);
    CHECK_NULL_VOID(navigation);
    auto navigationInfo = NavigationInfo(navigation->GetId(), navigation->GetCurId(), navigation);
    if (navigationMap_.find(parentNodeId) != navigationMap_.end()) {
        navigationMap_[parentNodeId].push_back(navigationInfo);
        return;
    }
    navigationMap_[parentNodeId] = { navigationInfo };
}

void NavigationManager::RemoveNavigation(int32_t navigationNodeId)
{
    for (auto navigationIter = navigationMap_.begin(); navigationIter != navigationMap_.end();) {
        auto& navigationInfos = navigationIter->second;
        auto it = std::find_if(navigationInfos.begin(), navigationInfos.end(), [navigationNodeId](auto info) {
            return navigationNodeId == info.nodeId;
        });
        if (it == navigationInfos.end()) {
            navigationIter++;
            continue;
        }
        navigationInfos.erase(it);
        if (navigationInfos.empty()) {
            navigationIter = navigationMap_.erase(navigationIter);
        } else {
            navigationIter++;
        }
    }
}

std::vector<int32_t> NavigationManager::FindNavigationInTargetParent(int32_t targetId)
{
    auto it = navigationMap_.find(targetId);
    if (it == navigationMap_.end()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "can't find inner navigation");
        return {};
    }
    std::vector<int32_t> navigationIds = {};
    auto navigationInfos = it->second;
    for (auto navigationInfo : navigationInfos) {
        navigationIds.push_back(navigationInfo.nodeId);
    }
    return navigationIds;
}

void NavigationManager::FireNavigationLifecycle(const RefPtr<UINode>& node, int32_t lifecycle, int32_t reason)
{
    NavDestinationActiveReason activeReason = static_cast<NavDestinationActiveReason>(reason);
    if (activeReason == NavDestinationActiveReason::TRANSITION) {
        NavigationPattern::FireNavigationLifecycle(node, static_cast<NavDestinationLifecycle>(lifecycle),
            activeReason);
        return;
    }
    // fire navdestination lifecycle in outer layer
    FireLowerLayerLifecycle(nullptr, lifecycle, reason);
}

void NavigationManager::FireOverlayLifecycle(const RefPtr<UINode>& node, int32_t lifecycle, int32_t reason)
{
    CHECK_NULL_VOID(node);
    NavDestinationActiveReason activeReason = static_cast<NavDestinationActiveReason>(reason);
    auto currentLifecycle = static_cast<NavDestinationLifecycle>(lifecycle);
    NavigationPattern::FireNavigationLifecycle(node, currentLifecycle, activeReason);
    NavDestinationLifecycle lowerLifecycle = NavDestinationLifecycle::ON_ACTIVE;
    if (lifecycle == NavDestinationLifecycle::ON_ACTIVE) {
        lowerLifecycle = NavDestinationLifecycle::ON_INACTIVE;
    }
    if (lifecycle == NavDestinationLifecycle::ON_INACTIVE) {
        lowerLifecycle = NavDestinationLifecycle::ON_ACTIVE;
    }
    FireLowerLayerLifecycle(node, static_cast<int32_t>(lowerLifecycle), reason);
}

void NavigationManager::FireLowerLayerLifecycle(const RefPtr<UINode>& node, int32_t lifecycle, int32_t reason)
{
    NavDestinationLifecycle lowerLifecycle = static_cast<NavDestinationLifecycle>(lifecycle);
    NavDestinationActiveReason activeReason = static_cast<NavDestinationActiveReason>(reason);
    auto pipelineContext = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipelineContext);
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    RefPtr<UINode> curNode = node;
    // sheet page node is not attach on root, get parent node sheetWrapper
    if (node && node->GetTag() == V2::SHEET_PAGE_TAG) {
        curNode = node->GetParent();
    }
    int32_t curNodeIndex = curNode ? rootNode->GetChildIndex(curNode)
        : static_cast<int32_t>(rootNode->GetChildren().size());
    // find lower layer node below node
    for (auto index = curNodeIndex - 1; index >= 0; index--) {
        auto child = AceType::DynamicCast<FrameNode>(rootNode->GetChildAtIndex(index));
        if (!child) {
            continue;
        }
        auto tag = child->GetTag();
        if (tag == V2::SHEET_WRAPPER_TAG) {
            NavigationPattern::FireNavigationLifecycle(child->GetChildAtIndex(0), lowerLifecycle, activeReason);
            return;
        }
        if (tag == V2::MODAL_PAGE_TAG) {
            NavigationPattern::FireNavigationLifecycle(child, lowerLifecycle, activeReason);
            return;
        }
        if (IsOverlayValid(child)) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "overlay has onShow");
            return;
        }
        if (IsCustomDialogValid(child)) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "custom dialog onShow");
            return;
        }
    }
    // fire last page lifecycle
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto lastPage = stageManager->GetLastPage();
    CHECK_NULL_VOID(lastPage);
    NavigationPattern::FireNavigationLifecycle(lastPage, lowerLifecycle, activeReason);
}

void NavigationManager::FireSubWindowLifecycle(const RefPtr<UINode>& node, int32_t lifecycle, int32_t reason)
{
    auto context = AceType::DynamicCast<NG::PipelineContext>(PipelineContext::GetMainPipelineContext());
    CHECK_NULL_VOID(context);
    auto navigationManager = context->GetNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    navigationManager->FireLowerLayerLifecycle(node, lifecycle, reason);
}

bool NavigationManager::IsOverlayValid(const RefPtr<UINode>& node)
{
    if (node->GetTag() != V2::OVERLAY_ETS_TAG) {
        return false;
    }
    auto overlays = node->GetChildren();
    // check overlay is visible, if overlay is visible, don't need fire active lifecycle
    for (auto index = 0; index < static_cast<int32_t>(overlays.size()); index++) {
        auto overlay = AceType::DynamicCast<FrameNode>(node->GetChildAtIndex(index));
        if (!overlay) {
            continue;
        }
        auto layoutProperty = overlay->GetLayoutProperty();
        if (layoutProperty && layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE) {
            return true;
        }
    }
    return false;
}

bool NavigationManager::IsCustomDialogValid(const RefPtr<UINode>& node)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_RETURN(frameNode, false);
    // if lower layer is dialog, don't need to trigger lifecycle
    auto pattern = frameNode->GetPattern();
    if (!InstanceOf<DialogPattern>(pattern)) {
        return false;
    }
    auto dialogPattern = AceType::DynamicCast<DialogPattern>(pattern);
    if (!dialogPattern) {
        return false;
    }
    auto dialogProperty = dialogPattern->GetDialogProperties();
    // if dialog is custom dialog, don't need to trigger active lifecycle, it triggers when dialog closed
    return dialogProperty.isUserCreatedDialog;
}

void NavigationManager::AddBeforeOrientationChangeTask(const std::function<void()>&& task)
{
    beforeOrientationChangeTasks_.emplace_back(std::move(task));
}

void NavigationManager::ClearBeforeOrientationChangeTask()
{
    beforeOrientationChangeTasks_.clear();
}

void NavigationManager::OnOrientationChanged()
{
    auto tasks = std::move(beforeOrientationChangeTasks_);
    for (auto& task : tasks) {
        if (task) {
            task();
        }
    }
}

void NavigationManager::SetNavigationIntentInfo(const std::string& intentInfoSerialized, bool isColdStart)
{
    if (intentInfoSerialized.empty()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "error, serialized intent info is empty!");
        return;
    }
    navigationIntentInfo_ = ParseNavigationIntentInfo(intentInfoSerialized);
    navigationIntentInfo_.value().isColdStart = isColdStart;
}

NavigationIntentInfo NavigationManager::ParseNavigationIntentInfo(const std::string& intentInfoSerialized)
{
    NavigationIntentInfo intentInfo;
    auto intentJson = JsonUtil::ParseJsonString(intentInfoSerialized);
    if (!intentJson || !intentJson->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "error, intent info is an invalid json object!");
        return intentInfo;
    }
    intentInfo.param = intentJson->GetObject(INTENT_PARAM_KEY)->ToString();
    intentInfo.navigationInspectorId = intentJson->GetString(INTENT_NAVIGATION_ID_KEY, "");
    intentInfo.navDestinationName = intentJson->GetString(INTENT_NAVDESTINATION_NAME_KEY, "");
    return intentInfo;
}

bool NavigationManager::FireNavigationIntentActively(int32_t pageId, bool needTransition)
{
    if (navigationMap_.find(pageId) == navigationMap_.end()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "error, no navigation in current page(id: %{public}d)", pageId);
        return false;
    }
    if (!navigationIntentInfo_.has_value()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "error, navigation intent info is empty!");
        return false;
    }
    auto navigationInfos = navigationMap_[pageId];
    // find target navigation
    for (auto navigationInfo : navigationInfos) {
        if (navigationInfo.navigationId == navigationIntentInfo_.value().navigationInspectorId) {
            auto navigationNode = navigationInfo.navigationNode.Upgrade();
            if (!navigationNode) {
                return false;
            }
            auto pattern = navigationNode->GetPattern<NavigationPattern>();
            if (!pattern) {
                return false;
            }
            return pattern->HandleIntent(needTransition);
        }
    }
    TAG_LOGE(AceLogTag::ACE_NAVIGATION,
        "error, specified navigation(id: %{public}s) doesn't exist in current page(id: %{public}d)",
        navigationIntentInfo_.value().navigationInspectorId.c_str(), pageId);
    return false;
}

std::string NavigationManager::GetTopNavDestinationInfo(int32_t pageId, bool onlyFullScreen, bool needParam)
{
    if (navigationMap_.find(pageId) == navigationMap_.end()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "no navigation in current page(id: %{public}d)", pageId);
        return "{}";
    }
    auto navigationInfos = navigationMap_[pageId];
    for (int32_t index = static_cast<int32_t>(navigationInfos.size()) -1; index >= 0; index--) {
        auto navigationInfo = navigationInfos[index];
        auto navigationNode = navigationInfo.navigationNode.Upgrade();
        if (!navigationNode) {
            continue;
        }
        auto pattern = navigationNode->GetPattern<NavigationPattern>();
        if (!pattern) {
            continue;
        }
        if (onlyFullScreen && !pattern->IsFullPageNavigation()) {
            continue;
        }
        return pattern->GetTopNavdestinationJson(needParam)->ToString();
    }
    TAG_LOGW(AceLogTag::ACE_NAVIGATION, "no valid navigation in current page(id: %{public}d)", pageId);
    return "{}";
}

void NavigationManager::RestoreNavDestinationInfo(const std::string& navDestinationInfo, bool isColdStart)
{
    auto navDestinationJson = JsonUtil::ParseJsonString(navDestinationInfo);
    if (!navDestinationJson || !navDestinationJson->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "restore navdestination info is an invalid json object!");
        return;
    }
    auto name = navDestinationJson->GetString("name");
    auto param = navDestinationJson->GetString("param");
    auto mode = navDestinationJson->GetInt("mode");
    if (isColdStart) {
        // for cold start case
        auto navigationId = navDestinationJson->GetString("navigationId", "");
        if (navigationId.empty()) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "will restore %{public}s without navigationId, "
                "it may lead to error in multi-navigation case!", name.c_str());
        }
        navigationRecoveryInfo_[navigationId] = { NavdestinationRecoveryInfo(name, param, mode) };
        return;
    }
    // for hot start case
    if (navigationMap_.empty()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "restore navdestination failed cause  is an invagitlid json object!");
        return;
    }
    auto navigationNode = GetNavigationByInspectorId(navDestinationJson->GetString("navigationId", ""));
    CHECK_NULL_VOID(navigationNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    auto navigationStack = pattern->GetNavigationStack();
    CHECK_NULL_VOID(navigationStack);
    navigationStack->CallPushDestinationInner(NavdestinationRecoveryInfo(name, param, mode));
}

RefPtr<FrameNode> NavigationManager::GetNavigationByInspectorId(const std::string& id) const
{
    for (auto iter : navigationMap_) {
        auto allNavigations = iter.second;
        for (int32_t index = static_cast<int32_t>(allNavigations.size()) - 1; index >= 0; index--) {
            auto navigationInfo = allNavigations[index];
            if (navigationInfo.navigationId == id && navigationInfo.navigationNode.Upgrade()) {
                return navigationInfo.navigationNode.Upgrade();
            }
        }
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG
