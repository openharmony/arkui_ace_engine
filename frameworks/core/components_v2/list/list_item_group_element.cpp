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

#include "core/components_v2/list/list_item_group_element.h"
namespace OHOS::Ace::V2 {

RefPtr<RenderNode> ListItemGroupElement::CreateRenderNode()
{
    renderListItemGroup_ = AceType::DynamicCast<RenderListItemGroup>(RenderElement::CreateRenderNode());
    if (!renderListItemGroup_) {
        LOGE("Failed to create render node for list element");
        return nullptr;
    }
    renderListItemGroup_->RegisterItemGenerator(AceType::WeakClaim(static_cast<ListItemGenerator*>(this)));
    return renderListItemGroup_;
}

void ListItemGroupElement::PerformBuild()
{
    auto listItemGroupComponent = AceType::DynamicCast<ListItemGroupComponent>(component_);
    ACE_DCHECK(listItemGroupComponent); // MUST be ListComponent
    if (!listItemGroupComponent) {
        return;
    }
    UpdateChildren(listItemGroupComponent->GetChildren());
    headerElement_ = UpdateChild(headerElement_, listItemGroupComponent->GetHeaderComponent());
    footerElement_ = UpdateChild(footerElement_, listItemGroupComponent->GetFooterComponent());
}

RefPtr<RenderListItem> ListItemGroupElement::RequestListItem(size_t index)
{
    auto element = GetElementByIndex(index);
    return element ? AceType::DynamicCast<RenderListItem>(element->GetRenderNode()) : nullptr;
}

RefPtr<RenderNode> ListItemGroupElement::RequestListItemHeader(void)
{
    return headerElement_ ? AceType::DynamicCast<RenderNode>(headerElement_->GetRenderNode()) : nullptr;
}

RefPtr<RenderNode> ListItemGroupElement::RequestListItemFooter(void)
{
    return footerElement_ ? AceType::DynamicCast<RenderNode>(footerElement_->GetRenderNode()) : nullptr;
}

RefPtr<Element> ListItemGroupElement::GetListItemBySlot(size_t index)
{
    auto listItemElement = GetElementByIndex(index);
    return listItemElement ? listItemElement : nullptr;
}

void ListItemGroupElement::RecycleListItem(size_t index)
{
    ReleaseElementByIndex(index);
}

size_t ListItemGroupElement::TotalCount()
{
    return ElementProxyHost::TotalCount();
}

void ListItemGroupElement::OnPostFlush()
{
    ReleaseRedundantComposeIds();
}

RefPtr<Element> ListItemGroupElement::OnUpdateElement(const RefPtr<Element>& element,
    const RefPtr<Component>& component)
{
    return UpdateChild(element, component);
}

RefPtr<Component> ListItemGroupElement::OnMakeEmptyComponent()
{
    return AceType::MakeRefPtr<ListItemComponent>();
}

void ListItemGroupElement::OnDataSourceUpdated(size_t startIndex)
{
    auto context = context_.Upgrade();
    if (context) {
        context->AddPostFlushListener(AceType::Claim(this));
    }
    if (renderListItemGroup_) {
        renderListItemGroup_->RemoveAllItems();
        renderListItemGroup_->MarkNeedLayout();
    }
    ElementProxyHost::OnDataSourceUpdated(startIndex);
}

} // namespace OHOS::Ace::V2
