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

#include "core/components_v2/list/list_item_group_component.h"

#include "core/components_v2/list/list_item_group_element.h"

namespace OHOS::Ace::V2 {

RefPtr<RenderNode> ListItemGroupComponent::CreateRenderNode()
{
    return RenderListItemGroup::Create();
}

RefPtr<Element> ListItemGroupComponent::CreateElement()
{
    return AceType::MakeRefPtr<ListItemGroupElement>();
}

uint32_t ListItemGroupComponent::Compare(const RefPtr<Component> &component) const
{
    auto listItemGroup = AceType::DynamicCast<ListItemGroupComponent>(component);
    if (!listItemGroup) {
        return static_cast<uint32_t>(UpdateRenderType::LAYOUT);
    }
    uint32_t updateType = static_cast<uint32_t>(UpdateRenderType::NONE);
    updateType |= static_cast<uint32_t>(listItemGroup->GetItemDivider()->strokeWidth == itemDivider_->strokeWidth ?
        UpdateRenderType::NONE : UpdateRenderType::LAYOUT);
    updateType |= static_cast<uint32_t>(listItemGroup->GetItemDivider()->startMargin == itemDivider_->startMargin ?
        UpdateRenderType::NONE : UpdateRenderType::LAYOUT);
    updateType |= static_cast<uint32_t>(listItemGroup->GetItemDivider()->endMargin == itemDivider_->endMargin ?
        UpdateRenderType::NONE : UpdateRenderType::LAYOUT);
    if (updateType == static_cast<uint32_t>(UpdateRenderType::LAYOUT)) {
        return updateType;
    }
    updateType |= static_cast<uint32_t>(listItemGroup->GetItemDivider()->color == itemDivider_->color ?
        UpdateRenderType::NONE : UpdateRenderType::PAINT);
    return updateType;
}

} // namespace OHOS::Ace::V2
