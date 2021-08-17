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

struct ListElement::ComponentNode {
    explicit ComponentNode(const RefPtr<ListItemComponent>& component) : component(component) {}
    ~ComponentNode() = default;

    RefPtr<ListItemComponent> component;
    RefPtr<Element> element;
};

ListElement::ListElement() = default;
ListElement::~ListElement() = default;

RefPtr<RenderNode> ListElement::CreateRenderNode()
{
    renderList_ = AceType::DynamicCast<RenderList>(RenderElement::CreateRenderNode());
    if (!renderList_) {
        LOGE("Failed to create render node for list element");
        return nullptr;
    }
    renderList_->RegisterItemGenerator(AceType::WeakClaim(this));
    return renderList_;
}

void ListElement::PerformBuild()
{
    auto listComponent = AceType::DynamicCast<ListComponent>(component_);
    ACE_DCHECK(listComponent); // MUST be ListComponent

    const auto& children = listComponent->GetChildren();
    auto itComponent = children.begin();
    auto itChild = components_.begin();
    while (itChild != components_.end() && itComponent != children.end()) {
        auto component = *(itComponent++);
        auto composed = AceType::DynamicCast<ComposedComponent>(component);
        auto listItem = AceType::DynamicCast<ListItemComponent>(composed ? composed->GetChild() : component);
        if (!listItem) {
            continue;
        }

        auto child = *(itChild++);
        if (child.element) {
            child.element = UpdateChild(child.element, listItem);
        }
        child.component = listItem;
    }

    if (itChild != components_.end()) {
        while (itChild != components_.end()) {
            auto child = *(itChild++);
            if (child.element) {
                child.element = UpdateChild(child.element, nullptr);
            }
        }
        components_.erase(itChild, components_.end());
    }

    while (itComponent != children.end()) {
        auto component = *(itComponent++);
        auto composed = AceType::DynamicCast<ComposedComponent>(component);
        auto listItem = AceType::DynamicCast<ListItemComponent>(composed ? composed->GetChild() : component);
        if (listItem) {
            components_.emplace_back(listItem);
        }
    }
}

void ListElement::Apply(const RefPtr<Element>& child)
{
    // Nothing to do
}

RefPtr<RenderListItem> ListElement::RequestListItem(size_t index)
{
    if (index >= components_.size()) {
        return nullptr;
    }

    auto& node = components_[index];
    if (!node.element) {
        node.element = UpdateChild(nullptr, node.component);
    }

    return AceType::DynamicCast<RenderListItem>(node.element->GetRenderNode());
}

void ListElement::RecycleListItem(size_t index, bool forceDelete)
{
    if (index >= components_.size()) {
        return;
    }

    auto& node = components_[index];
    if (node.element) {
        node.element = UpdateChild(node.element, nullptr);
    }

    if (forceDelete) {
        auto it = components_.begin();
        std::advance(it, index);
        components_.erase(it);
    }
}

size_t ListElement::TotalCount()
{
    return components_.size();
}

size_t ListElement::FindPreviousStickyListItem(size_t index)
{
    for (size_t idx = std::min(index + 1, TotalCount()); idx > 0; --idx) {
        auto& node = components_[idx - 1];
        if (node.component->GetSticky() != StickyMode::NONE) {
            return idx - 1;
        }
    }
    return INVALID_INDEX;
}

bool ListElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    // TODO:
    return false;
}

} // namespace
