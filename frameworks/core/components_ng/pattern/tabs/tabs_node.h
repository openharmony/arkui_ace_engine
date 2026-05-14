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
// Dynamically load nodes.
struct ItemIndex {
    int32_t swiperIndex = 0;
    int32_t bgMaskIndex = -1;
    int32_t dividerIndex = 1;
    int32_t tabBarIndex = 2;
    int32_t effectIndex = 3;
};
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

    bool HasBackgroundMaskNode() const
    {
        return backgroundMaskId_.has_value();
    }

    bool HasSelectedMaskNode() const
    {
        return selectedMaskId_.has_value();
    }

    bool HasUnselectedMaskNode() const
    {
        return unselectedMaskId_.has_value();
    }

    bool HasIndicatorNode() const
    {
        return indicatorId_.has_value();
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

    int32_t GetBackgroundMaskId()
    {
        if (!backgroundMaskId_.has_value()) {
            backgroundMaskId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return backgroundMaskId_.value();
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

    int32_t GetIndicatorId()
    {
        if (!indicatorId_.has_value()) {
            indicatorId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return indicatorId_.value();
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
        return GetChildAtIndex(itemIndex_.tabBarIndex);
    }

    RefPtr<UINode> GetTabs()
    {
        return GetChildAtIndex(itemIndex_.swiperIndex);
    }

    RefPtr<UINode> GetDivider()
    {
        return GetChildAtIndex(itemIndex_.dividerIndex);
    }

    RefPtr<UINode> GetBackgroundMask() const
    {
        return GetChildAtIndex(itemIndex_.bgMaskIndex);
    }

    RefPtr<UINode> GetEffectNode()
    {
        return GetChildAtIndex(itemIndex_.effectIndex);
    }

    ItemIndex GetItemIndex() const
    {
        return itemIndex_;
    }

    void SetItemIndex(const ItemIndex& itemIndex)
    {
        itemIndex_ = itemIndex;
    }

private:
    bool Scrollable() const;
    const RefPtr<Curve> GetAnimationCurve(const RefPtr<Curve>& defaultCurve) const;
    std::string GetAnimationCurveStr(const RefPtr<Curve>& defaultCurve) const;
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
    std::optional<int32_t> backgroundMaskId_;
    std::optional<int32_t> effectId_;
    std::optional<int32_t> selectedMaskId_;
    std::optional<int32_t> unselectedMaskId_;
    std::optional<int32_t> indicatorId_;
    std::set<int32_t> swiperChildren_;
    std::map<int32_t, RefPtr<UINode>> builderNode_; // Key is id of TabContent, value is id of builder of TabBar.

    ItemIndex itemIndex_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_NODE_H
