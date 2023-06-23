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

#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"

#include <queue>

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void MenuItemGroupPattern::OnMountToParentDone()
{
    ModifyFontSize();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            auto itemNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(itemNode);
            auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(itemPattern);
            itemPattern->UpdateTextNodes();
        }
    }
}

void MenuItemGroupPattern::ModifyFontSize()
{
    auto menu = GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuProperty = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    auto menuFontSize = menuProperty->GetFontSize();
    if (!menuFontSize.has_value()) {
        return;
    }

    if (headerContent_) {
        auto headerProperty = headerContent_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(headerProperty);
        headerProperty->UpdateFontSize(menuFontSize.value());
        headerContent_->MarkModifyDone();
    }

    if (footerContent_) {
        auto footerProperty = footerContent_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(footerProperty);
        footerProperty->UpdateFontSize(menuFontSize.value());
        footerContent_->MarkModifyDone();
    }
}

void MenuItemGroupPattern::AddHeader(const RefPtr<NG::UINode>& header)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (headerIndex_ < 0) {
        headerIndex_ = itemStartIndex_;
        host->AddChild(header);
        itemStartIndex_++;
    } else {
        host->ReplaceChild(host->GetChildAtIndex(headerIndex_), header);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(header);
    CHECK_NULL_VOID(frameNode);
}

void MenuItemGroupPattern::AddFooter(const RefPtr<NG::UINode>& footer)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (footerIndex_ < 0) {
        footerIndex_ = itemStartIndex_;
        host->AddChild(footer);
        itemStartIndex_++;
    } else {
        host->ReplaceChild(host->GetChildAtIndex(footerIndex_), footer);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(footer);
    CHECK_NULL_VOID(frameNode);
}

RefPtr<FrameNode> MenuItemGroupPattern::GetMenu()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_ETS_TAG) {
            return DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

std::string MenuItemGroupPattern::GetHeaderContent()
{
    CHECK_NULL_RETURN(headerContent_, "");
    auto content = headerContent_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(content, "");
    return content->GetContentValue("");
}

void MenuItemGroupPattern::UpdateMenuItemIconInfo()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::queue<RefPtr<UINode>> nodes;
    nodes.emplace(host);
    while (!nodes.empty()) {
        auto currentNode = nodes.front();
        nodes.pop();
        if (DynamicCast<FrameNode>(currentNode) && DynamicCast<FrameNode>(currentNode)->GetPattern<MenuItemPattern>()) {
            auto itemPattern = DynamicCast<FrameNode>(currentNode)->GetPattern<MenuItemPattern>();
            hasSelectIcon_ |= itemPattern->HasSelectIcon();
            hasStartIcon_ |= itemPattern->HasStartIcon();
        }
        for (const auto& child : currentNode->GetChildren()) {
            nodes.emplace(child);
        }
    }
}
} // namespace OHOS::Ace::NG
