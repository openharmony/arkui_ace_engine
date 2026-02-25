/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_item_group_inner_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/menu/menu_tag_constants.h"

namespace OHOS::Ace::NG {
namespace {
void AddHeader(const RefPtr<FrameNode>& node, const RefPtr<NG::UINode>& header)
{
    auto menuItemGroupPattern = node->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(menuItemGroupPattern);
    menuItemGroupPattern->AddHeader(header);
}

void AddHeaderContent(const RefPtr<FrameNode>& node, const RefPtr<NG::FrameNode>& headerContent)
{
    auto menuItemGroupPattern = node->GetPattern<MenuItemGroupPattern>();
    CHECK_NULL_VOID(menuItemGroupPattern);
    menuItemGroupPattern->AddHeaderContent(headerContent);
}

void UpdateStrokeWidth(const RefPtr<FrameNode>& node, const Dimension& value)
{
    CHECK_NULL_VOID(node);
    auto menuItemGroupPaintPros = node->GetPaintProperty<MenuItemGroupPaintProperty>();
    CHECK_NULL_VOID(node);
    menuItemGroupPaintPros->UpdateStrokeWidth(value);
}

RefPtr<FrameNode> GetOrCreateFrameNode()
{
    return FrameNode::GetOrCreateFrameNode(MENU_ITEM_GROUP_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemGroupPattern>(); });
}
} // namespace

namespace InnerModifier {
const ArkUIMenuItemGroupInnerModifier* GetMenuItemGroupInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIMenuItemGroupInnerModifier modifier = {
        .menuItemGroupAddHeader = AddHeader,
        .menuItemGroupAddHeaderContent = AddHeaderContent,
        .menuItemGroupUpdateStrokeWidth = UpdateStrokeWidth,
        .menuItemGroupAddHeaderGetOrCreateFrameNode = GetOrCreateFrameNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace InnerModifier
} // namespace OHOS::Ace::NG