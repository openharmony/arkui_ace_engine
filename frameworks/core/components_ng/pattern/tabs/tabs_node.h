/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_NODE_H

#include <optional>

#include "base/geometry/dimension.h"
#include "core/components_ng/base/group_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TabsNode : public GroupNode {
    DECLARE_ACE_TYPE(TabsNode, GroupNode);

public:
    TabsNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : GroupNode(tag, nodeId, pattern, isRoot)
    {}
    ~TabsNode() override = default;
    void AddChildToGroup(const RefPtr<UINode>& child) override;
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    bool HasSwiperNode() const
    {
        return swiperId_.has_value();
    }

    bool HasTabBarNode() const
    {
        return tabBarId_.has_value();
    }

    int32_t GetSwiperId()
    {
        if (!swiperId_.has_value()) {
            swiperId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return swiperId_.value();
    }

    int32_t GetTabBarId()
    {
        if (!tabBarId_.has_value()) {
            tabBarId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return tabBarId_.value();
    }

    int32_t GetTabBarByContentId(int32_t tabContentId)
    {
        auto iter = tabBarNode_.find(tabContentId);
        if (iter == tabBarNode_.end()) {
            auto tabBarId = ElementRegister::GetInstance()->MakeUniqueId();
            tabBarNode_.try_emplace(tabContentId, tabBarId);
            return tabBarId;
        }
        return iter->second;
    }

    RefPtr<UINode> GetBuilderByContentId(int32_t tabContentId, const RefPtr<UINode>& builderNode)
    {
        auto iter = builderNode_.find(tabContentId);
        if (iter == builderNode_.end()) {
            builderNode_.try_emplace(tabContentId, builderNode);
            return nullptr;
        }
        auto result = iter->second;
        iter->second = builderNode;
        return result;
    }

private:
    bool Scrollable() const;
    int32_t GetAnimationDuration() const;
    TabBarMode GetTabBarMode() const;
    Dimension GetBarWidth() const;
    Dimension GetBarHeight() const;
    int32_t GetIndex() const;

    std::optional<int32_t> swiperId_;
    std::optional<int32_t> tabBarId_;
    std::set<int32_t> swiperChildren_;
    std::map<int32_t, int32_t> tabBarNode_;         // Key is id of TabContent, value is id of Column of TabBar.
    std::map<int32_t, RefPtr<UINode>> builderNode_; // Key is id of TabContent, value is id of builder of TabBar.
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_NODE_H