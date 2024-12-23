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

#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"

namespace OHOS::Ace::NG {
void MenuItemGroupPattern::OnMountToParentDone()
{
    ModifyFontSize();
    ModifyDivider();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    bool needDivider = false;
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        if (child && child->GetTag() == V2::MENU_ITEM_ETS_TAG) {
            auto itemNode = AceType::DynamicCast<FrameNode>(child);
            CHECK_NULL_VOID(itemNode);
            auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
            CHECK_NULL_VOID(itemPattern);
            itemPattern->UpdateTextNodes();
            itemPattern->UpdateNeedDivider(needDivider);
            needDivider = true;
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
    if (headerContent_) {
        headerContent_->MarkModifyDone();
        headerContent_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
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
    if (footerContent_) {
        footerContent_->MarkModifyDone();
        footerContent_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
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

std::u16string MenuItemGroupPattern::GetHeaderContent()
{
    CHECK_NULL_RETURN(headerContent_, u"");
    auto content = headerContent_->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(content, u"");
    return content->GetContentValue(u"");
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

void MenuItemGroupPattern::ModifyDivider()
{
    auto menu = GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuProperty = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);

    auto divider = menuProperty->GetItemGroupDivider();
    if (divider.has_value()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto paintProperty = host->GetPaintProperty<MenuItemGroupPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        paintProperty->UpdateStrokeWidth(divider->strokeWidth);
        paintProperty->UpdateStartMargin(divider->startMargin);
        paintProperty->UpdateEndMargin(divider->endMargin);
        paintProperty->UpdateDividerColor(divider->color);
        paintProperty->UpdateNeedHeaderDivider(true);
        paintProperty->UpdateNeedFooterDivider(true);
    }
}

void MenuItemGroupPattern::OnExtItemPressed(bool press, bool beforeGroup)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<MenuItemGroupPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (beforeGroup) {
        paintProperty->UpdateNeedHeaderDivider(!press);
    } else {
        paintProperty->UpdateNeedFooterDivider(!press);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void MenuItemGroupPattern::OnIntItemPressed(int32_t index, bool press)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const size_t size = host->GetChildren().size();
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    auto currentIndex = parent->GetChildIndex(host);
    if (index == itemStartIndex_ && headerContent_ == nullptr) {
        OnExtItemPressed(press, true); // beforeGroup=true just to hide header divider
        auto prevNode = parent->GetChildAtIndex(currentIndex - 1);
        if (prevNode != nullptr && prevNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
            auto prevFrameNode = DynamicCast<FrameNode>(prevNode);
            CHECK_NULL_VOID(prevFrameNode);
            auto pattern = prevFrameNode->GetPattern<MenuItemGroupPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->OnExtItemPressed(press, false); // hide common divider for 2 group if another group before
        }
    }
    if (size > 0 && index == static_cast<int32_t>(size - 1) && footerContent_ == nullptr) {
        OnExtItemPressed(press, false); // beforeGroup=false just to hide footer divider
        auto nextNode = parent->GetChildAtIndex(currentIndex + 1);
        if (nextNode != nullptr && nextNode->GetTag() == V2::MENU_ITEM_GROUP_ETS_TAG) {
            auto nextFrameNode = DynamicCast<FrameNode>(nextNode);
            CHECK_NULL_VOID(nextFrameNode);
            auto pattern = nextFrameNode->GetPattern<MenuItemGroupPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->OnExtItemPressed(press, true); // hide common divider for 2 group if another group after
        }
    }
}
} // namespace OHOS::Ace::NG
