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
#include "core/components_ng/pattern/navigation/navigation_pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t INDENT_SIZE = 2;
NavigationManager::NavigationManager()
{
#ifdef PREVIEW
    hasCacheNavigationNodeEnable_ = false;
#else
    hasCacheNavigationNodeEnable_ = SystemProperties::GetCacheNavigationNodeEnable();
#endif
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
    return std::make_shared<NavigationInfo>(navigation->GetInspectorId().value_or(""), stack);
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

bool NavigationManager::CheckChildrenAnimationAndTagState(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto context = node->GetRenderContext();
    if ((context && context->GetAnimationsCount() != 0) || node->GetTag() == V2::UI_EXTENSION_COMPONENT_ETS_TAG) {
        return true;
    }
    std::list<RefPtr<FrameNode>> children;
    node->GenerateOneDepthVisibleFrameWithTransition(children);
    for (auto& child : children) {
        if (!child) {
            continue;
        }
        if (CheckChildrenAnimationAndTagState(child)) {
            return true;
        }
    }
    return false;
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
    CHECK_NULL_VOID(preNavNode_);
    auto preNavDestContentNode = GetNavDestContentFrameNode(preNavNode_);
    CHECK_NULL_VOID(preNavDestContentNode);
    auto state = CheckChildrenAnimationAndTagState(preNavDestContentNode);
    SetPreNodeHasAnimation(state);
    UpdateRenderGroup(preNavDestContentNode, !state);
    TAG_LOGD(AceLogTag::ACE_NAVIGATION,
        "Cache PreNavNode node(id=%{public}d name=%{public}s) childrenAnimationAndTagState=%{public}d",
        preNavDestContentNode->GetId(), preNavDestContentNode->GetTag().c_str(), state);
}

void NavigationManager::UpdateCurNavNodeRenderGroupProperty()
{
    CHECK_NULL_VOID(curNavNode_);
    auto curNavDestContentNode = GetNavDestContentFrameNode(curNavNode_);
    CHECK_NULL_VOID(curNavDestContentNode);
    auto state = CheckChildrenAnimationAndTagState(curNavDestContentNode);
    UpdateRenderGroup(curNavDestContentNode, !state);
    SetCurNodeAnimationCached(!state);
    SetCurrentNodeNeverSet(false);
    TAG_LOGD(AceLogTag::ACE_NAVIGATION,
        "Cache CurNavNode node(id=%{public}d name=%{public}s) childrenAnimationAndTagState=%{public}d",
        curNavDestContentNode->GetId(), curNavDestContentNode->GetTag().c_str(), state);
}

void NavigationManager::ResetCurNavNodeRenderGroupProperty()
{
    CHECK_NULL_VOID(curNavNode_);
    auto curNavDestContentNode = GetNavDestContentFrameNode(curNavNode_);
    CHECK_NULL_VOID(curNavDestContentNode);
    UpdateRenderGroup(curNavDestContentNode, false);
    SetCurNodeAnimationCached(false);
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
    //  Cache exit pages for future use
    if (!preNodeHasAnimation_) {
        UpdatePreNavNodeRenderGroupProperty();
    }
    //  Cache the entry page for future use
    if (currentNodeNeverSet_ && !curNodeAnimationCached_ && !pipeline->GetIsRequestVsync()) {
        UpdateCurNavNodeRenderGroupProperty();
    }
    // If the cached entry page changes again, cancel the previously marked entry page.
    if (!currentNodeNeverSet_ && pipeline->GetIsRequestVsync()) {
        ResetCurNavNodeRenderGroupProperty();
    }
}

void NavigationManager::UpdateRenderGroup(const RefPtr<FrameNode>& node, bool isSet)
{
    auto context = node->GetRenderContext();
    CHECK_NULL_VOID(context);
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "UpdateRenderGroup node(id=%d name=%s)=%d", node->GetId(),
        node->GetTag().c_str(), isSet);
    context->OnRenderGroupUpdate(isSet);
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
} // namespace OHOS::Ace::NG
