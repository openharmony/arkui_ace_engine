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

#include <utility>

#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

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
        index = FindIndex(name, navDestinationNode);
    }
    if (index != NOT_EXIST) {
        auto it = navPathList_.begin() + index;
        navPathList_.erase(it);
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
    } else {
        LOGW("unsupported navRouteMode");
    }
}

void NavigationStack::Add(
    const std::string& name, const RefPtr<UINode>& navDestinationNode, const RefPtr<RouteInfo>& routeInfo)
{
    // for the old page: keep the UINode, and keep in the stack
    auto index = FindIndex(name, navDestinationNode);
    if (index != NOT_EXIST) {
        LOGW("This navDestination node already exists");
        Remove(name, navDestinationNode);
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
    auto index = FindIndex(name, navDestinationNode);
    auto top = static_cast<int32_t>(navPathList_.size()) - 1;
    if (top != NOT_EXIST) {
        auto oldName = navPathList_[top].first;
        navPathList_.pop_back();
        navPathList_.emplace_back(std::make_pair(oldName, nullptr));
    }

    if (index != NOT_EXIST) {
        Remove(name, navDestinationNode);
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
    auto index = FindIndex(name, navDestinationNode);
    if (index != NOT_EXIST) {
        navPathList_.pop_back(); // move the old page
        Remove(name, navDestinationNode);
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

int32_t NavigationStack::FindIndex(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    if (navPathList_.empty()) {
        return NOT_EXIST;
    }
    int32_t index = navPathList_.size() - 1;
    // find from top to bottom
    for (auto it = navPathList_.rbegin(); it != navPathList_.rend(); ++it) {
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
    int32_t top = navPathList_.size() - 1;
    return navPathList_[top].second;
}

RefPtr<UINode> NavigationStack::Get(const std::string& name)
{
    // from bottom to top
    if (navPathList_.empty()) {
        return nullptr;
    }
    for (auto it = navPathList_.begin(); it != navPathList_.end(); ++it) {
        if ((*it).first == name) {
            return (*it).second;
        }
    }
    return nullptr;
}

RefPtr<UINode> NavigationStack::GetPre(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    if (navPathList_.empty() || navPathList_.size() == 1) {
        return nullptr;
    }
    auto index = FindIndex(name, navDestinationNode);
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

void NavigationStack::Push(const std::string& name, const RefPtr<RouteInfo>& routeInfo) {}

void NavigationStack::Push(const std::string& name, int32_t index) {}

void NavigationStack::RemoveName(const std::string& name) {}

void NavigationStack::Clear()
{
    navPathList_.clear();
}

RefPtr<UINode> NavigationStack::CreateNodeByIndex(int32_t index)
{
    return nullptr;
}

RefPtr<UINode> NavigationStack::CreateNodeByRouteInfo(const RefPtr<RouteInfo>& routeInfo)
{
    return nullptr;
}
} // namespace OHOS::Ace::NG
