/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/log/log.h"
#include "base/utils/macros.h"
#include "core/components_v2/list/list_component.h"
#include "core/pipeline/base/composed_component.h"

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

    UpdateChildren(listComponent->GetChildren());
}

void ListElement::Apply(const RefPtr<Element>& child)
{
    // Nothing to do
}

RefPtr<RenderListItem> ListElement::RequestListItem(size_t index)
{
    auto element = GetElementByIndex(index);
    return element ? AceType::DynamicCast<RenderListItem>(element->GetRenderNode()) : nullptr;
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
    for (size_t idx = std::min(index + 1, TotalCount()); idx > 0; --idx) {
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

bool ListElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
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
    if (renderList_) {
        renderList_->RemoveAllItems();
        renderList_->MarkNeedLayout();
    }
}

} // namespace
