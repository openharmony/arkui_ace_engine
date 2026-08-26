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

#include "core/components_ng/pattern/tabs/tab_content_pattern.h"

#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"

namespace OHOS::Ace::NG {

void TabContentPattern::OnAttachToMainTree()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto tabs = TabContentModelNG::FindTabsNode(hostNode);
    CHECK_NULL_VOID(tabs);
    auto swiper = tabs->GetTabs();
    CHECK_NULL_VOID(swiper);
    auto indexPair = swiper->GetChildFlatIndex(hostNode->GetId());
    if (!indexPair.first) {
        return;
    }
    GenerateGlobalComponentId(std::to_string(indexPair.second));
}

void TabContentPattern::OnModifyDone()
{
    Pattern::OnModifyDone();

    const auto& defaultVisibility = GetDefaultVisibility();
    if (defaultVisibility == lastAppliedVisibility_) {
        return;
    }
    lastAppliedVisibility_ = defaultVisibility;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(host);
    CHECK_NULL_VOID(tabContentNode);
    auto tabsNode = AceType::DynamicCast<TabsNode>(TabContentModelNG::FindTabsNode(host));
    CHECK_NULL_VOID(tabsNode);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);
    auto tabsProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsProperty);

    auto barLayoutStyle = tabsProperty->GetBarLayoutStyleValue(TabBarLayoutStyle::BOTTOM);
    auto currentDisplayMode = tabsPattern->GetCurrentBarDisplayMode();
    TabBarDisplayMode activeDisplayMode = currentDisplayMode.value_or(TabBarDisplayMode::BOTTOMTABBAR);

    bool shouldHide = false;
    if (barLayoutStyle != TabBarLayoutStyle::BOTTOM && !defaultVisibility.isNull &&
        defaultVisibility.visibility == TabVisibility::HIDDEN) {
        shouldHide = !defaultVisibility.displayMode.has_value() ||
            (defaultVisibility.displayMode.value() == activeDisplayMode);
    }

    if (barLayoutStyle == TabBarLayoutStyle::BOTTOM ||
        (barLayoutStyle == TabBarLayoutStyle::SIDEBAR_ADAPTABLE &&
        activeDisplayMode == TabBarDisplayMode::BOTTOMTABBAR)) {
        // Bottom tab bar is currently visible — update this tab's columnNode directly
        if (!tabContentNode->HasTabBarItemId()) {
            return;
        }
        auto columnNode = AceType::DynamicCast<FrameNode>(
            ElementRegister::GetInstance()->GetUINodeById(tabContentNode->GetTabBarItemId()));
        CHECK_NULL_VOID(columnNode);
        auto columnProperty = columnNode->GetLayoutProperty();
        CHECK_NULL_VOID(columnProperty);
        columnProperty->UpdateVisibility(shouldHide ? VisibleType::GONE : VisibleType::VISIBLE);
        columnNode->MarkNeedSyncRenderTree();
        columnNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    // Sidebar is currently visible — update this tab's sidebar tabItemNode directly
    if (!tabContentNode->HasSideBarTabBarItemId()) {
        return;
    }
    auto tabItemNode = AceType::DynamicCast<FrameNode>(
        ElementRegister::GetInstance()->GetUINodeById(tabContentNode->GetSideBarTabBarItemId()));
    CHECK_NULL_VOID(tabItemNode);
    auto property = tabItemNode->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    property->UpdateVisibility(shouldHide ? VisibleType::GONE : VisibleType::VISIBLE);
    tabItemNode->MarkNeedSyncRenderTree();
    tabItemNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

} // namespace OHOS::Ace::NG
