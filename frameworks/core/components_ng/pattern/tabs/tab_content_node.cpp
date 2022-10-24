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

#include "core/components_ng/pattern/tabs/tab_content_node.h"

#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"

namespace OHOS::Ace::NG {

void TabContentNode::OnAttachToMainTree()
{
    auto tabs = TabContentModelNG::FindTabsNode(Referenced::Claim(this));
    if (!tabs) {
        return;
    }

    auto swiper = tabs? tabs->GetTabs() : nullptr;
    auto myIndex = swiper ? swiper->GetChildFlatIndex(GetId()).second : 0;

    TabContentModelNG::AddTabBarItem(Referenced::Claim(this), myIndex);
}

void TabContentNode::OnDetachFromMainTree()
{
    // That is never called, because object in in the middle of distruction
    // virtual function is not working anymore

    auto tabs = TabContentModelNG::FindTabsNode(Referenced::Claim(this));

    if (!tabs) {
        LOGE("Tabs  not found");
        return;
    }

    // Change focus to the other tab if current is being deleted
    auto swiper = tabs? tabs->GetTabs() : nullptr;
    auto pattern = swiper ? AceType::DynamicCast<FrameNode>(swiper)->GetPattern():nullptr;
    auto swiperPattern = pattern? AceType::DynamicCast<SwiperPattern>(pattern) : nullptr;

    auto deletedIdx = swiper->GetChildFlatIndex(GetId()).second;
    auto currentIdx = swiperPattern->GetCurrentShownIndex();
    LOGD( "Deleting tab: %{public}d, currentTab: %{public}d", deletedIdx,
        swiperPattern->GetCurrentShownIndex());
    if (swiperPattern) {
        // Removing currently shown tab, focus on first after that
        if (currentIdx == deletedIdx) {
            swiperPattern->GetSwiperController()->SwipeTo(0);
        }
        TabContentModelNG::RemoveTabBarItem(Referenced::Claim(this));

        // Removing tab before current, re-focus on the same tab with new index
        if (currentIdx > deletedIdx) {
            LOGD( "RE-activate TAB with new IDX %{public}d from idx %{public}d",
                currentIdx-1, deletedIdx);
            swiperPattern->GetSwiperController()->SwipeTo(currentIdx-1);
        }
    }
}

RefPtr<TabContentNode> TabContentNode::GetOrCreateTabContentNode(
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

} // namespace OHOS::Ace::NG
