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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_CONTEXT_H

#include <string>

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"

namespace OHOS::Ace::NG {
class NavigationStack;
class NavDestinationPattern;
class NavPathInfo : public virtual AceType {
    DECLARE_ACE_TYPE(NavPathInfo, AceType)
public:
    NavPathInfo() = default;
    explicit NavPathInfo(const std::string& name) : name_(name) {}
    NavPathInfo(const std::string& name, bool isEntry) : name_(name), isEntry_(isEntry) {}
    virtual ~NavPathInfo() = default;

    void SetName(const std::string& name)
    {
        name_ = name;
    }

    std::string GetName() const
    {
        return name_;
    }

    virtual napi_value GetParamObj() const
    {
        return nullptr;
    }

    bool GetIsEntry() const
    {
        return isEntry_;
    }

    void SetIsEntry(bool isEntry)
    {
        isEntry_ = isEntry;
    }

    virtual void UpdateNavPathInfo(const RefPtr<NG::NavPathInfo>& info)
    {
        if (!info) {
            return;
        }
        name_ = info->GetName();
        isEntry_ = info->GetIsEntry();
    }

    virtual void OpenScope() {}
    virtual void CloseScope() {}

protected:
    std::string name_;
    bool isEntry_ = false;
};

class NavDestinationContext : public virtual AceType {
    DECLARE_ACE_TYPE(NavDestinationContext, AceType)
public:
    NavDestinationContext() = default;
    virtual ~NavDestinationContext() = default;

    void SetNavPathInfo(RefPtr<NavPathInfo> info)
    {
        pathInfo_ = info;
    }

    RefPtr<NavPathInfo> GetNavPathInfo() const
    {
        return pathInfo_;
    }

    void SetNavigationStack(WeakPtr<NavigationStack> stack)
    {
        navigationStack_ = stack;
    }

    WeakPtr<NavigationStack> GetNavigationStack() const
    {
        return navigationStack_;
    }

    int32_t GetIndex() const
    {
        return index_;
    }

    void SetIndex(int32_t index)
    {
        index_ = index;
    }

    int32_t GetPreIndex() const
    {
        return preIndex_;
    }

    void SetPreIndex(int32_t index)
    {
        preIndex_ = index;
    }

    uint64_t GetNavDestinationId() const
    {
        return navDestinationId_;
    }

    void SetNavDestinationId(uint64_t id)
    {
        navDestinationId_ = id;
    }

    void SetIsEmpty(bool isEmpty)
    {
        isEmpty_ = isEmpty;
    }

    bool GetIsEmpty() const
    {
        return isEmpty_;
    }

    void SetMode(NavDestinationMode mode)
    {
        mode_ = mode;
    }

    NavDestinationMode GetMode() const
    {
        return mode_;
    }

    void SetUniqueId(int32_t uniqueId)
    {
        uniqueId_ = uniqueId;
    }

    int32_t GetUniqueId() const
    {
        return uniqueId_;
    }

    void SetNavDestinationPattern(const WeakPtr<NavDestinationPattern>& pattern);
    RefPtr<NavDestinationPattern> GetNavDestinationPattern() const;

protected:
    int32_t index_ = -1;
    int32_t preIndex_ = -1;
    uint64_t navDestinationId_ = 0;
    NavDestinationMode mode_;
    RefPtr<NavPathInfo> pathInfo_;
    bool isEmpty_ = false;
    WeakPtr<NavigationStack> navigationStack_;
    WeakPtr<NavDestinationPattern> navDestinationPattern_;
    int32_t uniqueId_ = -1;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVROUTER_NAVDESTINATION_CONTEXT_H
