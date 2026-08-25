/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_SIDE_BAR_TAB_LIST_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_SIDE_BAR_TAB_LIST_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_side_bar_tab_list_layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"

namespace OHOS::Ace::NG {

class TabContentPattern;
class SwiperPattern;

class TabsSideBarTabListPattern : public Pattern {
    DECLARE_ACE_TYPE(TabsSideBarTabListPattern, Pattern);

public:
    TabsSideBarTabListPattern() = default;
    ~TabsSideBarTabListPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TabsSideBarTabListLayoutAlgorithm>();
    }

    void SetSwiperController(const RefPtr<SwiperController>& controller)
    {
        swiperController_ = controller;
    }

    void SetCurrentIndex(int32_t index);
    void InitCurrentIndex(int32_t index);
    int32_t GetCurrentIndex() const
    {
        return currentIndex_;
    }

    void SetTabsNode(const RefPtr<FrameNode>& tabsNode)
    {
        tabsNode_ = tabsNode;
    }
    void SetColumnNode(const RefPtr<FrameNode>& columnNode)
    {
        columnNode_ = columnNode;
    }
    const RefPtr<FrameNode>& GetTabItemContainerNode() const
    {
        return columnNode_;
    }
    void ApplySearchFilter(
        std::function<bool(int32_t, const std::string& text)> searchFilter, const std::u16string& searchText);
    void AddOrUpdateTabListItem(const RefPtr<FrameNode>& tabContentNode, int32_t position, bool update);

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

private:
    void OnModifyDone() override;
    void UpdateTabItemStyle(int32_t index, bool selected);
    RefPtr<FrameNode> GetOrCreateTabItemNode(int32_t id);
    void AddOrUpdateTabItemWithContent(
        const TabBarParam& tabBarParam, const RefPtr<FrameNode>& tabItemNode, int32_t tabContentId, int32_t myIndex);
    void AddOrUpdateTabItemWithBuilder(
        const TabBarParam& tabBarParam, const RefPtr<FrameNode>& tabItemNode, int32_t tabContentId, int32_t myIndex);
    void CreateOrUpdateTabItemTextAndIcon(
        const TabBarParam& tabBarParam, const RefPtr<FrameNode>& tabItemNode,
        const RefPtr<TabContentPattern>& tabContentPattern, int32_t position,
        RefPtr<FrameNode>& iconNode, RefPtr<FrameNode>& textNode);
    void UpdateTabBarItemTextProperties(
        const TabBarParam& tabBarParam, const RefPtr<FrameNode>& textNode, const RefPtr<SwiperPattern>& swiperPattern,
        const RefPtr<TabContentPattern>& tabContentPattern, int32_t myIndex, int32_t indicator);
    void UpdateTabBarItemIconProperties(
        const TabBarParam& tabBarParam, const RefPtr<FrameNode>& iconNode,
        const RefPtr<TabContentPattern>& tabContentPattern, int32_t myIndex, int32_t indicator);
    void AddOrUpdateTabItemWithIconAndText(
        const TabBarParam& tabBarParam, const RefPtr<FrameNode>& tabItemNode, const RefPtr<FrameNode>& swiperNode,
        const RefPtr<TabContentPattern>& tabContentPattern, int32_t position, int32_t myIndex);

    WeakPtr<FrameNode> tabsNode_ = nullptr;
    RefPtr<FrameNode> columnNode_ = nullptr;
    RefPtr<SwiperController> swiperController_ = nullptr;
    int32_t currentIndex_ = -1;
    std::map<int32_t, RefPtr<UINode>> builderNode_; // Key is id of TabContent, value is id of builder of TabBar.
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TABS_TABS_SIDE_BAR_TAB_LIST_PATTERN_H
