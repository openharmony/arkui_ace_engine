/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_v2/list/list_element.h"

#include "core/components_v2/list/render_list_item_group.h"

namespace OHOS::Ace::V2 {

ListElement::ListElement() = default;
ListElement::~ListElement() = default;

RefPtr<RenderNode> ListElement::CreateRenderNode()
{
    renderList_ = AceType::DynamicCast<RenderList>(RenderElement::CreateRenderNode());
    if (!renderList_) {
        LOGE("Failed to create render node for list element");
        return nullptr;
    }
    renderList_->RegisterItemGenerator(AceType::WeakClaim(static_cast<ListItemGenerator*>(this)));
    return renderList_;
}

void ListElement::PerformBuild()
{
    auto listComponent = AceType::DynamicCast<ListComponent>(component_);
    ACE_DCHECK(listComponent); // MUST be ListComponent
    if (!listComponent) {
        return;
    }
    UpdateChildren(listComponent->GetChildren());
    listItemRange_.clear();
}

void ListElement::Apply(const RefPtr<Element>& child)
{
    // Nothing to do
}

size_t ListElement::FindItemStartIndex(size_t startIndex, size_t index)
{
    auto component = GetComponentByIndex(index);
    auto listItem = AceType::DynamicCast<ListItemComponent>(component);
    if (!listItem) {
        return index;
    }
    for (size_t idx = index; idx > startIndex; idx--) {
        component = GetComponentByIndex(idx - 1);
        listItem = AceType::DynamicCast<ListItemComponent>(component);
        if (!listItem) {
            return idx;
        }
    }
    if (startIndex == 0) {
        return 0;
    }
    return INVALID_INDEX;
}

size_t ListElement::FindItemStartIndex(size_t index)
{
    auto it = listItemRange_.upper_bound(index);
    if (it == listItemRange_.begin()) {
        size_t startIdx = FindItemStartIndex(0, index);
        listItemRange_[startIdx] = index;
        return startIdx;
    }
    it--;
    if (it->second >= index) {
        return it->first;
    }
    size_t startIdx = FindItemStartIndex(it->second, index);
    if (startIdx != INVALID_INDEX) {
        listItemRange_[startIdx] = index;
        return startIdx;
    }
    it->second = index;
    return it->first;
}

RefPtr<RenderListItem> ListElement::RequestListItem(size_t index)
{
    auto element = GetElementByIndex(index);
    if (!element) {
        return nullptr;
    }
    auto renderNode = element->GetRenderNode();
    // for list item
    auto renderListItem = AceType::DynamicCast<RenderListItem>(renderNode);
    if (renderListItem) {
        return renderListItem;
    }
    // get target list item group
    auto renderListItemGroup = AceType::DynamicCast<RenderListItemGroup>(renderNode);
    auto currentNode = renderNode;
    while (!renderListItemGroup) {
        currentNode = currentNode->GetFirstChild();
        if (!currentNode) {
            break;
        }
        renderListItemGroup = AceType::DynamicCast<RenderListItemGroup>(currentNode);
    }
    if (renderListItemGroup) {
        renderListItemGroup->SetRenderNode(renderNode);
    }
    return renderListItemGroup;
}

RefPtr<Element> ListElement::GetListItemBySlot(size_t index)
{
    auto listItemElement = GetElementByIndex(index);
    return listItemElement ? listItemElement : nullptr;
}

void ListElement::RecycleListItem(size_t index)
{
    ReleaseElementByIndex(index);
}

size_t ListElement::TotalCount()
{
    return ElementProxyHost::TotalCount();
}

size_t ListElement::FindPreviousStickyListItem(size_t index)
{
    size_t begin = std::min(index + 1, TotalCount());
    size_t end = stickyRange_ > begin ? 0 : begin - stickyRange_;
    for (size_t idx = begin; idx > end; --idx) {
        auto component = GetComponentByIndex(idx - 1);
        auto listItem = AceType::DynamicCast<ListItemComponent>(component);
        if (!listItem) {
            LOGW("MUST be ListItemComponent, %{public}s", AceType::TypeName(component));
            continue;
        }
        if (listItem->GetSticky() != StickyMode::NONE) {
            return idx - 1;
        }
    }
    return INVALID_INDEX;
}

bool ListElement::IsAncestor(const RefPtr<Element>& parent, const RefPtr<Element>& node)
{
    CHECK_NULL_RETURN(parent, false);
    CHECK_NULL_RETURN(node, false);
    if (node == parent) {
        return true;
    }
    auto nodeParent = (node->GetElementParent()).Upgrade();
    if (!nodeParent) {
        return false;
    }
    return IsAncestor(parent, nodeParent);
}

int32_t ListElement::GetRealElementIndex(const RefPtr<FocusNode>& node)
{
    auto nodeElement = AceType::DynamicCast<Element>(node);
    CHECK_NULL_RETURN(nodeElement, -1);
    for (int32_t i = 0; i < static_cast<int32_t>(children_.size()); i++) {
        auto element = GetElementByIndex(i);
        CHECK_NULL_RETURN(element, -1);
        if (IsAncestor(element, nodeElement)) {
            return i;
        }
    }
    return -1;
}

bool ListElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    RefPtr<RenderList> list = AceType::DynamicCast<RenderList>(renderNode_);
    if (!list) {
        LOGE("Render grid is null.");
        return false;
    }
    LOGI("RequestNextFocus vertical:%{public}d reverse:%{public}d.", vertical, reverse);
    if (!UpdateFocusIndex()) {
        LOGE("Update focus index failed");
        return false;
    }
    bool ret = false;
    while (!ret) {
        int32_t focusIndex = list->RequestNextFocus(vertical, reverse);
        LOGI("Request next focus index = %{public}d", focusIndex);
        auto size = static_cast<int32_t>(sortedFocusNodesList_.size());
        if (focusIndex < 0 || focusIndex >= size) {
            LOGW("Invalid next focus index");
            return false;
        }
        auto iter = sortedFocusNodesList_.begin();
        std::advance(iter, focusIndex);
        auto focusNode = *iter;
        if (!focusNode) {
            LOGE("Target focus node is null.");
            return false;
        }
        // If current Node can not obtain focus, move to next.
        ret = focusNode->RequestFocusImmediately();
    }
    return ret;
}

bool ListElement::UpdateFocusIndex()
{
    RefPtr<RenderList> list = AceType::DynamicCast<RenderList>(renderNode_);
    if (!list) {
        LOGE("Render grid is null.");
        return false;
    }
    sortedFocusNodesList_.clear();
    sortedFocusNodesList_ = GetChildrenList();
    sortedFocusNodesList_.sort([wp = WeakClaim(this)](RefPtr<FocusNode>& node1, RefPtr<FocusNode>& node2) {
        auto list = wp.Upgrade();
        if (list) {
            return list->GetRealElementIndex(node1) < list->GetRealElementIndex(node2);
        }
        return true;
    });
    int32_t index = 0;
    for (const auto& iter : sortedFocusNodesList_) {
        if (iter->IsCurrentFocus()) {
            list->SetFocusIndex(index);
            return true;
        }
        ++index;
    }
    return false;
}

RefPtr<Element> ListElement::OnUpdateElement(const RefPtr<Element>& element, const RefPtr<Component>& component)
{
    return UpdateChild(element, component);
}

RefPtr<Component> ListElement::OnMakeEmptyComponent()
{
    return AceType::MakeRefPtr<ListItemComponent>();
}

void ListElement::OnDataSourceUpdated(size_t startIndex)
{
    auto context = context_.Upgrade();
    if (context) {
        context->AddPostFlushListener(AceType::Claim(this));
    }
    if (renderList_) {
        renderList_->RemoveAllItems();
        renderList_->MarkNeedLayout();
    }
    ElementProxyHost::OnDataSourceUpdated(startIndex);
}

void ListElement::OnPostFlush()
{
    ReleaseRedundantComposeIds();
}

} // namespace
