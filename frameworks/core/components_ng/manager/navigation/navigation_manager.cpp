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
    constexpr int NAVIGATION_DUMP_DEPTH = 2;
    CHECK_RUN_ON(UI);
    DumpLog::GetInstance().Print("Navigation number: " + std::to_string(dumpMap_.size()));
    int navIdx = 0;
    for (auto it = dumpMap_.begin(); it != dumpMap_.end(); ++it) {
        DumpLog::GetInstance().Print(1, "Navigation[" + std::to_string(navIdx) + "] ID: " +
            std::to_string(it->first.nodeId) + ", Depth: " + std::to_string(it->first.depth) + ", NavPathStack:");
        if (it->second) {
            it->second(NAVIGATION_DUMP_DEPTH);
        }
        navIdx++;
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
