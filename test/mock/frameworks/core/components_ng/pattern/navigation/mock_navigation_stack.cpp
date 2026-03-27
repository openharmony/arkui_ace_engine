/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/pattern/navigation/navigation_stack.h"

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
}

void NavigationStack::Remove(const std::string& name)
{
    if (name.empty()) {
        return;
    }
    for (auto it = navPathList_.begin(); it != navPathList_.end();) {
        if (it->first == name) {
            it = navPathList_.erase(it);
        } else {
            ++it;
        }
    }
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
    int32_t index = FindIndex(name, navDestinationNode, true);
    if (index != NOT_EXIST) {
        navPathList_.erase(navPathList_.begin() + index);
    }
    return index;
}

int32_t NavigationStack::RemoveInPreNavPathList(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    int32_t index = FindIndex(name, navDestinationNode, false);
    if (index != NOT_EXIST) {
        preNavPathList_.erase(preNavPathList_.begin() + index);
    }
    return index;
}

void NavigationStack::RemoveAll()
{
    navPathList_.clear();
    preNavPathList_.clear();
}

void NavigationStack::Add(
    const std::string& name, const RefPtr<UINode>& navDestinationNode, const RefPtr<RouteInfo>& routeInfo)
{
    (void)routeInfo;
    navPathList_.emplace_back(name, navDestinationNode);
}

void NavigationStack::Add(const std::string& name, const RefPtr<UINode>& navDestinationNode, NavRouteMode mode,
    const RefPtr<RouteInfo>& routeInfo)
{
    (void)mode;
    Add(name, navDestinationNode, routeInfo);
}

RefPtr<UINode> NavigationStack::Get()
{
    if (navPathList_.empty()) {
        return nullptr;
    }
    return navPathList_.back().second;
}

bool NavigationStack::Get(const std::string& name, RefPtr<UINode>& navDestinationNode, int32_t& index)
{
    int32_t cur = 0;
    for (const auto& item : navPathList_) {
        if (item.first == name) {
            navDestinationNode = item.second;
            index = cur;
            return true;
        }
        ++cur;
    }
    navDestinationNode = nullptr;
    index = NOT_EXIST;
    return false;
}

bool NavigationStack::GetFromPreBackup(const std::string& name, RefPtr<UINode>& navDestinationNode, int32_t& index)
{
    int32_t cur = 0;
    for (const auto& item : preNavPathList_) {
        if (item.first == name) {
            navDestinationNode = item.second;
            index = cur;
            return true;
        }
        ++cur;
    }
    navDestinationNode = nullptr;
    index = NOT_EXIST;
    return false;
}

std::string NavigationStack::GetNavDesNameByIndex(int32_t index)
{
    if (index < 0 || index >= Size()) {
        return "";
    }
    return navPathList_[index].first;
}

RefPtr<UINode> NavigationStack::Get(int32_t index)
{
    if (index < 0 || index >= Size()) {
        return nullptr;
    }
    return navPathList_[index].second;
}

RefPtr<UINode> NavigationStack::GetPre(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    int32_t index = FindIndex(name, navDestinationNode, true);
    if (index <= 0) {
        return nullptr;
    }
    return navPathList_[index - 1].second;
}

bool NavigationStack::IsEmpty()
{
    return navPathList_.empty();
}

std::vector<std::string> NavigationStack::GetAllPathName()
{
    std::vector<std::string> names;
    names.reserve(navPathList_.size());
    for (const auto& item : navPathList_) {
        names.emplace_back(item.first);
    }
    return names;
}

std::vector<int32_t> NavigationStack::GetAllPathIndex()
{
    std::vector<int32_t> indexes;
    indexes.reserve(navPathList_.size());
    for (int32_t i = 0; i < static_cast<int32_t>(navPathList_.size()); ++i) {
        indexes.emplace_back(i);
    }
    return indexes;
}

void NavigationStack::Pop() {}

void NavigationStack::Push(const std::string& name, const RefPtr<RouteInfo>& routeInfo)
{
    (void)name;
    (void)routeInfo;
}

void NavigationStack::Push(const std::string& name, int32_t index)
{
    (void)name;
    (void)index;
}

void NavigationStack::RemoveName(const std::string& name)
{
    (void)name;
}

void NavigationStack::RemoveIndex(int32_t index)
{
    (void)index;
}

void NavigationStack::Clear()
{
    navPathList_.clear();
    preNavPathList_.clear();
    cacheNodes_.clear();
}

void NavigationStack::UpdateReplaceValue(int32_t value) const
{
    (void)value;
}

int32_t NavigationStack::GetReplaceValue() const
{
    return 0;
}

bool NavigationStack::CreateNodeByIndex(int32_t index, const WeakPtr<UINode>& customNode, RefPtr<UINode>& node)
{
    (void)index;
    (void)customNode;
    node = nullptr;
    return false;
}

RefPtr<UINode> NavigationStack::CreateNodeByRouteInfo(const RefPtr<RouteInfo>& routeInfo, const WeakPtr<UINode>& node)
{
    (void)routeInfo;
    (void)node;
    return nullptr;
}

int32_t NavigationStack::FindIndex(const std::string& name, const RefPtr<UINode>& navDestinationNode, bool isNavPathList)
{
    const auto& list = isNavPathList ? navPathList_ : preNavPathList_;
    if (list.empty()) {
        return NOT_EXIST;
    }
    int32_t index = static_cast<int32_t>(list.size()) - 1;
    for (auto it = list.rbegin(); it != list.rend(); ++it) {
        if (it->first == name && it->second == navDestinationNode) {
            return index;
        }
        --index;
    }
    return NOT_EXIST;
}

NavPathList NavigationStack::GetAllCacheNodes()
{
    return cacheNodes_;
}

void NavigationStack::AddCacheNode(const std::string& name, const RefPtr<UINode>& uiNode)
{
    if (name.empty() || !uiNode) {
        return;
    }
    cacheNodes_.emplace_back(name, uiNode);
}

RefPtr<UINode> NavigationStack::GetFromCacheNode(NavPathList& cacheNodes, const std::string& name)
{
    for (const auto& item : cacheNodes) {
        if (item.first == name) {
            return item.second;
        }
    }
    return nullptr;
}

RefPtr<UINode> NavigationStack::GetFromCacheNode(const std::string& name)
{
    for (const auto& item : cacheNodes_) {
        if (item.first == name) {
            return item.second;
        }
    }
    return nullptr;
}

std::optional<std::pair<std::string, RefPtr<UINode>>> NavigationStack::GetFromCacheNode(int32_t handle)
{
    for (const auto& item : cacheNodes_) {
        if (item.second && item.second->GetId() == handle) {
            return std::make_pair(item.first, item.second);
        }
    }
    return std::nullopt;
}

void NavigationStack::RemoveCacheNode(NavPathList& cacheNodes, const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    for (auto it = cacheNodes.begin(); it != cacheNodes.end(); ++it) {
        if (it->first == name || it->second == navDestinationNode) {
            cacheNodes.erase(it);
            return;
        }
    }
}

void NavigationStack::RemoveCacheNode(int32_t handle)
{
    for (auto it = cacheNodes_.begin(); it != cacheNodes_.end(); ++it) {
        if (it->second && it->second->GetId() == handle) {
            cacheNodes_.erase(it);
            return;
        }
    }
}

void NavigationStack::ReOrderCache(const std::string& name, const RefPtr<UINode>& navDestinationNode)
{
    if (name.empty() || !navDestinationNode) {
        return;
    }
    NavPathList old = cacheNodes_;
    cacheNodes_.clear();
    cacheNodes_.emplace_back(name, navDestinationNode);
    for (const auto& item : old) {
        if (item.first == name && item.second == navDestinationNode) {
            continue;
        }
        cacheNodes_.emplace_back(item.first, item.second);
    }
}

std::vector<std::string> NavigationStack::DumpStackInfo() const
{
    std::vector<std::string> infos;
    infos.reserve(navPathList_.size());
    for (size_t i = 0; i < navPathList_.size(); ++i) {
        infos.emplace_back("[" + std::to_string(i) + "]{ name: \"" + navPathList_[i].first + "\" }");
    }
    return infos;
}
} // namespace OHOS::Ace::NG
