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
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
void MenuItemGroupPattern::OnMountToParentDone()
{
    ModifyFontSize();
}

void MenuItemGroupPattern::ModifyFontSize()
{
    auto menu = GetMenu();
    CHECK_NULL_VOID(menu);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuFontSize = menuPattern->FontSize();

    if (headerContent_) {
        auto headerProperty = headerContent_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(headerProperty);
        headerProperty->UpdateFontSize(menuFontSize);
        headerContent_->MarkModifyDone();
    }

    if (footerContent_) {
        auto footerProperty = footerContent_->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(footerProperty);
        footerProperty->UpdateFontSize(menuFontSize);
        footerContent_->MarkModifyDone();
    }

    auto host = GetHost();
    for (const auto& child : host->GetChildren()) {
        auto menuItemPattern = DynamicCast<FrameNode>(child)->GetPattern<MenuItemPattern>();
        if (menuItemPattern) {
            menuItemPattern->ModifyFontSize(menuFontSize);
        }
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
    auto menu = AceType::DynamicCast<FrameNode>(host->GetParent());
    return menu ? menu : nullptr;
}
} // namespace OHOS::Ace::NG