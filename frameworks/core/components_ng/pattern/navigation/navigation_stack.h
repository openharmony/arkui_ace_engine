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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_STACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_STACK_H

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace::NG {
using NavPathList = std::vector<std::pair<std::string, RefPtr<UINode>>>;

class RouteInfo : public virtual AceType {
    DECLARE_ACE_TYPE(NG::RouteInfo, AceType)
public:
    RouteInfo() = default;
    virtual ~RouteInfo() = default;

    virtual std::string GetName()
    {
        return "";
    }
};

class NavigationStack : public virtual AceType {
    DECLARE_ACE_TYPE(NG::NavigationStack, AceType)
public:
    NavigationStack() = default;
    virtual ~NavigationStack() = default;

    NavPathList& GetAllNavDestinationNodes()
    {
        return navPathList_;
    }

    void SetNavPathList(const NavPathList& navPathList)
    {
        navPathList_ = navPathList;
    }

    bool Empty() const
    {
        return navPathList_.empty();
    }

    void Remove();
    void Remove(const std::string& name);
    void Remove(const std::string& name, const RefPtr<UINode>& navDestinationNode);
    int32_t RemoveInNavPathList(const std::string& name, const RefPtr<UINode>& navDestinationNode);
    void RemoveAll();
    void Add(const std::string& name, const RefPtr<UINode>& navDestinationNode,
        const RefPtr<RouteInfo>& routeInfo = nullptr);
    void Add(const std::string& name, const RefPtr<UINode>& navDestinationNode, NavRouteMode mode,
        const RefPtr<RouteInfo>& routeInfo = nullptr);
    const RefPtr<UINode>& Get();
    const RefPtr<UINode>& Get(const std::string& name);
    const RefPtr<UINode>& GetPre(const std::string& name, const RefPtr<UINode>& navDestinationNode);
    virtual bool IsEmpty();
    virtual std::vector<std::string> GetAllPathName();
    virtual void Pop();
    virtual void Push(const std::string& name, const RefPtr<RouteInfo>& routeInfo = nullptr);
    virtual void Push(const std::string& name, int32_t index);
    virtual void RemoveName(const std::string& name);
    virtual void RemoveIndex(int32_t index);
    virtual void Clear();
    virtual RefPtr<UINode> CreateNodeByIndex(int32_t index);
    virtual RefPtr<UINode> CreateNodeByRouteInfo(const RefPtr<RouteInfo>& routeInfo);
    int32_t FindIndex(const std::string& name, const RefPtr<UINode>& navDestinationNode);

private:
    void MoveToTop(const std::string& name, const RefPtr<UINode>& navDestinationNode);
    void AddForDefault(const std::string& name, const RefPtr<UINode>& navDestinationNode,
        const RefPtr<RouteInfo>& routeInfo = nullptr);
    void AddForReplace(const std::string& name, const RefPtr<UINode>& navDestinationNode,
        const RefPtr<RouteInfo>& routeInfo = nullptr);

    NavPathList navPathList_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_STACK_H
