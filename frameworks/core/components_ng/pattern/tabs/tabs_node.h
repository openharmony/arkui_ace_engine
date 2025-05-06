/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/tabs/tabs_model.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SWIPER_INDEX = 0;
constexpr int32_t DIVIDER_INDEX = 1;
constexpr int32_t TAB_BAR_INDEX = 2;
constexpr int32_t EFFECT_INDEX = 3;
} // namespace
class InspectorFilter;

class ACE_EXPORT TabsNode : public GroupNode {
    DECLARE_ACE_TYPE(TabsNode, GroupNode);

public:
    TabsNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : GroupNode(tag, nodeId, pattern, isRoot)
    {}
    ~TabsNode() override = default;
    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override;

    bool HasSwiperNode() const
    {
        return swiperId_.has_value();
    }

    bool HasTabBarNode() const
    {
        return tabBarId_.has_value();
    }

    bool HasDividerNode() const
    {
        return dividerId_.has_value();
    }

    bool HasSelectedMaskNode() const
    {
        return selectedMaskId_.has_value();
    }

    bool HasUnselectedMaskNode() const
    {
        return unselectedMaskId_.has_value();
    }

    int32_t GetSwiperId()
    {
        if (!swiperId_.has_value()) {
            swiperId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return swiperId_.value();
    }

    int32_t GetDividerId()
    {
        if (!dividerId_.has_value()) {
            dividerId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return dividerId_.value();
    }

    int32_t GetEffectId()
    {
        if (!effectId_.has_value()) {
            effectId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return effectId_.value();
    }

    int32_t GetTabBarId()
    {
        if (!tabBarId_.has_value()) {
            tabBarId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return tabBarId_.value();
    }
	
    int32_t GetSelectedMaskId()
    {
        if (!selectedMaskId_.has_value()) {
            selectedMaskId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return selectedMaskId_.value();
    }

    int32_t GetUnselectedMaskId()
    {
        if (!unselectedMaskId_.has_value()) {
            unselectedMaskId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return unselectedMaskId_.value();
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

    void RemoveBuilderByContentId(int32_t tabContentId)
    {
        builderNode_.erase(tabContentId);
    }

    RefPtr<UINode> GetTabBar()
    {
        return GetChildAtIndex(TAB_BAR_INDEX);
    }

    RefPtr<UINode> GetTabs()
    {
        return GetChildAtIndex(SWIPER_INDEX);
    }

    RefPtr<UINode> GetDivider()
    {
        return GetChildAtIndex(DIVIDER_INDEX);
    }

    RefPtr<UINode> GetEffectNode()
    {
        return GetChildAtIndex(EFFECT_INDEX);
    }

private:
    bool Scrollable() const;
    int32_t GetAnimationDuration() const;
    TabBarMode GetTabBarMode() const;
    Dimension GetBarWidth() const;
    Dimension GetBarHeight() const;
    bool GetBarAdaptiveHeight() const;
    Color GetBarBackgroundColor() const;
    BlurStyle GetBarBackgroundBlurStyle() const;
    std::unique_ptr<JsonValue> GetBarBackgroundBlurStyleOptions() const;
    int32_t GetIndex() const;
    bool GetFadingEdge() const;
    BarGridColumnOptions GetBarGridAlign() const;
    ScrollableBarModeOptions GetScrollableBarModeOptions() const;
    std::string GetAnimationMode() const;
    std::string GetEdgeEffect() const;
    std::unique_ptr<JsonValue> GetBarBackgroundEffect() const;

    std::optional<int32_t> swiperId_;
    std::optional<int32_t> tabBarId_;
    std::optional<int32_t> dividerId_;
    std::optional<int32_t> effectId_;
    std::optional<int32_t> selectedMaskId_;
    std::optional<int32_t> unselectedMaskId_;
    std::set<int32_t> swiperChildren_;
    std::map<int32_t, RefPtr<UINode>> builderNode_; // Key is id of TabContent, value is id of builder of TabBar.
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_NODE_H
