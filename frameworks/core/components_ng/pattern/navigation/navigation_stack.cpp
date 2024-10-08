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

#include "core/components_ng/pattern/navigation/navigation_stack.h"

#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NOT_EXIST = -1;
}
void NavigationStack::Remove()
{
    if (navPathList_.empty()) {
        return;
    }
    navPathList_.pop_back();
    Pop();
}

void NavigationStack::Remove(const std::string& name)
{
    if (navPathList_.empty()) {
        return;
    }
    for (auto it = navPathList_.begin(); it != navPathList_.end();) {
        if (((*it).first) == name) {
            it = navPathList_.erase(it);
        } else {
            ++it;
        }
    }
    RemoveName(name);
}

void NavigationStack::Remove(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    int32_t index = RemoveInNavPathList(name, navDestinationNode);
    if (index != NOT_EXIST) {
        RemoveIndex(index);
    }
}

int32_t NavigationStack::RemoveInNavPathList(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    int32_t index = NOT_EXIST;
    if (!navPathList_.empty()) {
        index = FindIndex(name, navDestinationNode, true);
    }
    if (index != NOT_EXIST) {
        auto it = navPathList_.begin() + index;
        navPathList_.erase(it);
    }
    return index;
}

int32_t NavigationStack::RemoveInPreNavPathList(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    int32_t index = NOT_EXIST;
    if (!preNavPathList_.empty()) {
        index = FindIndex(name, navDestinationNode, false);
    }
    if (index != NOT_EXIST) {
        auto it = preNavPathList_.begin() + index;
        preNavPathList_.erase(it);
    }
    return index;
}

void NavigationStack::RemoveIndex(int32_t index) {}

void NavigationStack::Add(const std::string& name, const RefPtr<UINode>& navDestinationNode, NavRouteMode mode,
    const RefPtr<RouteInfo>& routeInfo)
{
    if (mode == NavRouteMode::PUSH) {
        Add(name, navDestinationNode, routeInfo);
    } else if (mode == NavRouteMode::PUSH_WITH_RECREATE) {
        AddForDefault(name, navDestinationNode, routeInfo);
    } else if (mode == NavRouteMode::REPLACE) {
        AddForReplace(name, navDestinationNode, routeInfo);
    }
}

#if defined(ENABLE_NAV_SPLIT_MODE)
bool NavigationStack::isLastListContains(
    const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    if (lastNavPathList_.empty()) {
        return false;
    }
    // find from top to bottom
    for (auto it = lastNavPathList_.rbegin(); it != lastNavPathList_.rend(); ++it) {
        if ((*it).first == name && (*it).second == navDestinationNode) {
            return true;
        }
    }
    return false;
}
#endif

void NavigationStack::Add(
    const std::string& name, const RefPtr<UINode>& navDestinationNode, const RefPtr<RouteInfo>& routeInfo)
{
    // for the old page: keep the UINode, and keep in the stack
    auto index = FindIndex(name, navDestinationNode, true);
    if (index != NOT_EXIST) {
        RemoveIndex(index);
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "This navigation destination node already exists");
    }
    navPathList_.emplace_back(std::make_pair(name, navDestinationNode));
    if (index != NOT_EXIST) {
        Push(name, index);
    } else {
        Push(name, routeInfo);
    }
}

void NavigationStack::AddForDefault(
    const std::string& name, const RefPtr<UINode>& navDestinationNode, const RefPtr<RouteInfo>& routeInfo)
{
    // for the old page: destroy the UINode, but keep in the stack
    auto index = FindIndex(name, navDestinationNode, true);
    if (index != NOT_EXIST) {
        RemoveIndex(index);
    }
    navPathList_.emplace_back(std::make_pair(name, navDestinationNode));
    // push param into JSNavigationStack
    if (index != NOT_EXIST) {
        Push(name, index);
    } else {
        Push(name, routeInfo);
    }
}

void NavigationStack::AddForReplace(
    const std::string& name, const RefPtr<UINode>& navDestinationNode, const RefPtr<RouteInfo>& routeInfo)
{
    // for the old page: destroy the UINode, and move out of the stack
    if (navPathList_.empty()) {
        Add(name, navDestinationNode);
        return;
    }
    auto index = FindIndex(name, navDestinationNode, true);
    if (index != NOT_EXIST) {
        navPathList_.pop_back(); // move the old page
        RemoveIndex(index);
    } else {
        navPathList_.pop_back();
    }
    navPathList_.emplace_back(std::make_pair(name, navDestinationNode));

    Pop();
    if (index != NOT_EXIST) {
        Push(name, index);
    } else {
        Push(name, routeInfo);
    }
}

void NavigationStack::RemoveAll()
{
    navPathList_.clear();
    Clear();
}

int32_t NavigationStack::FindIndex(
    const std::string& name, const RefPtr<UINode>& navDestinationNode, bool isNavPathList)
{
    NavPathList navPathList = isNavPathList ? navPathList_ : preNavPathList_;
    if (navPathList.empty()) {
        return NOT_EXIST;
    }
    int32_t index = static_cast<int32_t>(navPathList.size()) - 1;
    // find from top to bottom
    for (auto it = navPathList.rbegin(); it != navPathList.rend(); ++it) {
        if ((*it).first == name && (*it).second == navDestinationNode) {
            return index;
        }
        --index;
    }
    return NOT_EXIST;
}

RefPtr<UINode> NavigationStack::Get()
{
    if (navPathList_.empty()) {
        return nullptr;
    }
    int32_t top = static_cast<int32_t>(navPathList_.size()) - 1;
    return navPathList_[top].second;
}

bool NavigationStack::Get(const std::string& name, RefPtr<UINode>& navDestinationNode, int32_t& index)
{
    // from bottom to top
    if (navPathList_.empty()) {
        navDestinationNode = nullptr;
        index = NOT_EXIST;
        return false;
    }
    int32_t curIndex = 0;
    for (auto it = navPathList_.begin(); it != navPathList_.end(); ++it) {
        if ((*it).first == name) {
            navDestinationNode = (*it).second;
            index = curIndex;
            return true;
        }
        curIndex++;
    }
    navDestinationNode = nullptr;
    index = NOT_EXIST;
    return false;
}

RefPtr<UINode> NavigationStack::Get(int32_t index)
{
    if (index < 0 || index >= Size()) {
        return nullptr;
    }
    return navPathList_[index].second;
}

std::string NavigationStack::GetNavDesNameByIndex(int32_t index)
{
    if (index < 0 || index >= Size()) {
        return "";
    }
    return navPathList_[index].first;
}

bool NavigationStack::GetFromPreBackup(const std::string& name, RefPtr<UINode>& navDestinationNode, int32_t& index)
{
    // from bottom to top
    if (preNavPathList_.empty()) {
        navDestinationNode = nullptr;
        index = NOT_EXIST;
        return false;
    }
    int32_t curIndex = 0;
    for (auto it = preNavPathList_.begin(); it != preNavPathList_.end(); ++it) {
        if ((*it).first == name) {
            navDestinationNode =  (*it).second;
            index = curIndex;
            return true;
        }
        curIndex++;
    }
    navDestinationNode = nullptr;
    index = NOT_EXIST;
    return false;
}

RefPtr<UINode> NavigationStack::GetPre(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    if (navPathList_.empty() || navPathList_.size() == 1) {
        return nullptr;
    }
    auto index = FindIndex(name, navDestinationNode, true);
    if (index == 0 || index == NOT_EXIST) {
        // no more navDestinationNode in front or no this navDestinationNode
        return nullptr;
    } else {
        --index;
        return navPathList_[index].second;
    }
}

bool NavigationStack::IsEmpty()
{
    return false;
}

void NavigationStack::Pop() {}

std::vector<std::string> NavigationStack::GetAllPathName()
{
    if (navPathList_.empty()) {
        return {};
    }
    std::vector<std::string> pathNames;
    for (const auto& path : navPathList_) {
        pathNames.emplace_back(path.first);
    }
    return pathNames;
}

std::vector<int32_t> NavigationStack::GetAllPathIndex()
{
    if (navPathList_.empty()) {
        return {};
    }
    std::vector<int32_t> pathIndex;
    for (int32_t i = 0; i < static_cast<int32_t>(navPathList_.size()); i++) {
        pathIndex.emplace_back(i);
    }
    return pathIndex;
}
void NavigationStack::Push(const std::string& name, const RefPtr<RouteInfo>& routeInfo) {}

void NavigationStack::Push(const std::string& name, int32_t index) {}

void NavigationStack::RemoveName(const std::string& name) {}

void NavigationStack::Clear()
{
    navPathList_.clear();
    cacheNodes_.clear();
}

bool NavigationStack::CreateNodeByIndex(int32_t index, const WeakPtr<UINode>& customNode, RefPtr<UINode>& node)
{
    return false;
}

RefPtr<UINode> NavigationStack::CreateNodeByRouteInfo(const RefPtr<RouteInfo>& routeInfo, const WeakPtr<UINode>& node)
{
    return nullptr;
}

void NavigationStack::UpdateReplaceValue(int32_t value) const {}

int32_t NavigationStack::GetReplaceValue() const
{
    return 0;
}

NavPathList NavigationStack::GetAllCacheNodes()
{
    return cacheNodes_;
}

void NavigationStack::AddCacheNode(
    const std::string& name, const RefPtr<UINode>& uiNode)
{
    if (name.empty() || uiNode == nullptr) {
        return;
    }

    auto navDestination = AceType::DynamicCast<NG::NavDestinationGroupNode>(
        NG::NavigationGroupNode::GetNavDestinationNode(uiNode));
    if (navDestination) {
        navDestination->SetIsCacheNode(true);
    }

    cacheNodes_.emplace_back(std::make_pair(name, uiNode));
}

void NavigationStack::RemoveCacheNode(int32_t handle)
{
    if (handle <= 0) {
        return;
    }

    for (auto it = cacheNodes_.begin(); it != cacheNodes_.end(); ++it) {
        if ((*it).second->GetId() == handle) {
            auto navDestination = AceType::DynamicCast<NG::NavDestinationGroupNode>(
                NG::NavigationGroupNode::GetNavDestinationNode(it->second));
            if (navDestination) {
                navDestination->SetIsCacheNode(false);
            }
            cacheNodes_.erase(it);
            return;
        }
    }
}

void NavigationStack::RemoveCacheNode(
    NavPathList& cacheNodes, const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    if (cacheNodes.empty() || name.empty() || navDestinationNode == nullptr) {
        return;
    }

    for (auto it = cacheNodes.begin(); it != cacheNodes.end(); ++it) {
        if ((*it).first == name || (*it).second == navDestinationNode) {
            cacheNodes.erase(it);
            return;
        }
    }
}

void NavigationStack::ReOrderCache(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    if (name.empty() || navDestinationNode == nullptr) {
        return;
    }

    auto cacheNodes = cacheNodes_;
    cacheNodes_.clear();
    cacheNodes_.emplace_back(std::make_pair(name, navDestinationNode));
    for (auto it = cacheNodes.begin(); it != cacheNodes.end(); ++it) {
        if ((*it).first == name && (*it).second == navDestinationNode) {
            continue;
        }

        cacheNodes_.emplace_back(std::make_pair((*it).first, (*it).second));
    }
}

RefPtr<UINode> NavigationStack::GetFromCacheNode(
    NavPathList& cacheNodes, const std::string& name)
{
    if (cacheNodes.empty() || name.empty()) {
        return nullptr;
    }
    for (auto it = cacheNodes.begin(); it != cacheNodes.end(); ++it) {
        if ((*it).first == name) {
            return (*it).second;
        }
    }
    return nullptr;
}

RefPtr<UINode> NavigationStack::GetFromCacheNode(const std::string& name)
{
    if (name.empty()) {
        return nullptr;
    }
    for (auto it = cacheNodes_.begin(); it != cacheNodes_.end(); ++it) {
        if ((*it).first == name) {
            return (*it).second;
        }
    }
    return nullptr;
}

std::optional<std::pair<std::string, RefPtr<UINode>>> NavigationStack::GetFromCacheNode(int32_t handle)
{
    for (auto it = cacheNodes_.begin(); it != cacheNodes_.end(); ++it) {
        if ((*it).second || (*it).second->GetId() == handle) {
            return std::make_pair((*it).first, (*it).second);
        }
    }
    return std::nullopt;
}

std::vector<std::string> NavigationStack::DumpStackInfo() const
{
    std::vector<std::string> dumpInfos;
    for (size_t i = 0; i < navPathList_.size(); ++i) {
        const auto& name = navPathList_[i].first;
        std::string info = "[" + std::to_string(i) + "]{ name: \"" + name + "\" }";
        dumpInfos.push_back(std::move(info));
    }
    return dumpInfos;
}
} // namespace OHOS::Ace::NG
