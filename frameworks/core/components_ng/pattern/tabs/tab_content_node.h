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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TAB_TAB_CONTENT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TAB_TAB_CONTENT_NODE_H

#include <optional>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TabContentNode : public FrameNode {
    DECLARE_ACE_TYPE(TabsContentNode, FrameNode);

public:
    // avoid use creator function, use CreateFrameNode
    TabContentNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot) {}

    ~TabContentNode()
    {
        // Find Tabs
        // Creatign RefPtr will recursivelly call DTOR again!!
        // Same code is in 
        // RefPtr<TabsNode> TabContentView::FindTabsNode(const RefPtr<UINode>& tabContent)

        RefPtr<UINode> parent = GetParent();
        RefPtr<TabsNode> tabs;
        while (parent) {
            if (AceType::InstanceOf<TabsNode>(parent)) {
                tabs = AceType::DynamicCast<TabsNode>(parent);
                break;
            }
            parent = parent->GetParent();
        }
        if (tabs) {
            TabContentView::RemoveTabBarItem(tabs, GetId());
        }
    }

    void OnAttachToMainTree() override
    {
        auto tabs = TabContentView::FindTabsNode(Referenced::Claim(this));
        if (!tabs) {
            return;
        }

        auto swiper = tabs? tabs->GetTabs() : nullptr;
        auto myIndex = swiper ? swiper->GetShallowIndex<TabContentNode>(GetId()).second : 0;

        TabContentView::AddTabBarItem(Referenced::Claim(this), myIndex);
    }

    void OnDetachFromMainTree() override
    {
        // That is never called, because object in in the middle of distruction
        // virtual function is not working anymore

        auto tabs = TabContentView::FindTabsNode(Referenced::Claim(this));

        if (!tabs) {
            LOGE("Tabs  not found");
            return;
        }

        // Change focus to the other tab if current is being deleted
        auto swiper = tabs? tabs->GetTabs() : nullptr;
        auto pattern = swiper ? AceType::DynamicCast<FrameNode>(swiper)->GetPattern():nullptr;
        auto swiperPattern = pattern? AceType::DynamicCast<SwiperPattern>(pattern) : nullptr;

        auto deletedIdx = swiper->GetShallowIndex<TabContentNode>(GetId()).second;
        auto currentIdx = swiperPattern->GetCurrentShownIndex();
        LOGD( "Deleting tab: %{public}d, currentTab: %{public}d", deletedIdx,
            swiperPattern->GetCurrentShownIndex());
        if (swiperPattern) {
            // Removing currently shown tab, focus on first after that
            if (currentIdx == deletedIdx) {
                swiperPattern->GetSwiperController()->SwipeTo(0);
            }
            TabContentView::RemoveTabBarItem(tabs, GetId());

            // Removing tab before current, re-focus on the same tab with new index
            if (currentIdx > deletedIdx) {
                LOGD( "RE-activate TAB with new IDX %{public}d from idx %{public}d",
                    currentIdx-1, deletedIdx);
                swiperPattern->GetSwiperController()->SwipeTo(currentIdx-1);
            }
        }
    }

    static RefPtr<TabContentNode> GetOrCreateTabContentNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
    {
        auto node = GetFrameNode(tag, nodeId);
        auto tabContentNode = AceType::DynamicCast<TabContentNode>(node);

        if (tabContentNode) {
            LOGD("found existing");
            return tabContentNode;
        }

        auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
        tabContentNode = AceType::MakeRefPtr<TabContentNode>(tag, nodeId, pattern, false);
        ElementRegister::GetInstance()->AddUINode(tabContentNode);
        return tabContentNode;
    }
    ACE_DISALLOW_COPY_AND_MOVE(TabContentNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TAB_TAB_CONTENT_NODE_H