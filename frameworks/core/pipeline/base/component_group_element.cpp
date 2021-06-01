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

#include "core/pipeline/base/component_group_element.h"

#include "base/log/log.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/common/frontend.h"
#include "core/pipeline/base/component_group.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace {

RefPtr<Element> ComponentGroupElement::Create()
{
    LOGD("ComponentGroupElement::Create");
    return AceType::MakeRefPtr<ComponentGroupElement>();
}

bool ComponentGroupElement::IsComposed(const std::list<RefPtr<Component>>& newComponents)
{
    for (const auto& child : children_) {
        if (!AceType::InstanceOf<ComposedElement>(child)) {
            return false;
        }
    }

    for (const auto& newComponent : newComponents) {
        if (!AceType::InstanceOf<ComposedComponent>(newComponent)) {
            return false;
        }
    }
    return true;
}

void ComponentGroupElement::PerformBuild()
{
    LOGD("start build  %{public}s", GetTag());

    RefPtr<ComponentGroup> group = AceType::DynamicCast<ComponentGroup>(component_);
    if (!group) {
        return;
    }

    const auto& newComponents = group->GetChildren();

    if (IsComposed(newComponents)) {
        LOGD("Reconcilliation via composeted path for %{public}s", GetTag());
        UpdateComposedChildren(newComponents);
    } else {
        auto context = context_.Upgrade();
        if (context && context->GetIsDeclarative()) {
            LOGD("Reconcilliation via optimized common path %{public}s", GetTag());
            UpdateCommonChildrenOptimized(newComponents);
        } else {
            LOGD("Reconcilliation via NON optimized common path %{public}s", GetTag());
            UpdateCommonChildren(newComponents);
        }
    }
    LOGD("end build %{public}s", GetTag());
}

std::list<RefPtr<Element>> ComponentGroupElement::UpdateCommonChildren(
    const std::list<RefPtr<Component>>& newComponents)
{
    LOGD("ComponentGroupElement::UpdateCommonChildren start");
    const auto& oldChildren = children_;
    auto componentIter = newComponents.begin();
    auto childIter = oldChildren.begin();
    while (childIter != oldChildren.end() && componentIter != newComponents.end()) {
        if ((*childIter)->NeedUpdateWithComponent(*componentIter)) {
            if ((*childIter)->CanUpdate(*componentIter)) {
                UpdateChild(*childIter, *componentIter);
            } else {
                break;
            }
        }
        ++childIter;
        ++componentIter;
    }

    // children_ will be modified during UpdateChild.(some items will be removed from children_)
    while (childIter != oldChildren.end()) {
        auto child = *childIter;
        ++childIter;
        UpdateChild(child, nullptr);
    }

    while (componentIter != newComponents.end()) {
        UpdateChild(nullptr, *componentIter);
        ++componentIter;
    }

    LOGD("ComponentGroupElement::UpdateCommonChildren end");
    return oldChildren;
}

void ComponentGroupElement::UpdateCommonChildrenOptimized(const std::list<RefPtr<Component>>& newComponents)
{
    LOGD("%{public}s parent: %{public}s child count %{public}lu", GetTag(),
        (GetElementParent().Upgrade() ? GetElementParent().Upgrade()->GetTag() : "No parent"), children_.size());

    auto oldChildrenTopIter = children_.begin();
    auto oldChildrenBottomIter = children_.end();

    auto newComponentsTopIter = newComponents.begin();
    auto newComponentsBottomIter = newComponents.end();

    int32_t slot = 0;
    std::size_t topLength = 0;
    std::size_t bottomLength = 0;

    // Scan through the beggining of the list and update matching components

    while (oldChildrenTopIter != children_.end() && newComponentsTopIter != newComponents.end()) {
        // For ComposedElement
        //   Condition is true if IDs are the same for Element and Component OR
        //   marked as update needed
        //   true if component not a ComposedComponent
        // Not a ComposedComponent:
        //   always true

        if ((*oldChildrenTopIter)->NeedUpdateWithComponent(*newComponentsTopIter)) {
            // For ComposedElement
            //   true,
            //       if ComposedComponent and element have the same ID OR
            //       ID is different, but childlen is empty or null
            //       if child exists call child's CanUpdate
            //   false
            //       if want to update with non composed component
            //
            //   Summary checks for ID to be the same for all levels
            // Not a ComposedComponent:
            //   Returns true if types components are the same
            //   Redefined by progress, picker, list...
            if ((*oldChildrenTopIter)->CanUpdate(*newComponentsTopIter)) {
                LOGD("%{public}s parent: %{public}s childer count %{public}lu updating child %{public}s", GetTag(),
                    (GetElementParent().Upgrade() ? GetElementParent().Upgrade()->GetTag() : "No parent"),
                    children_.size(), (*oldChildrenTopIter)->GetTag());
                UpdateChild(*oldChildrenTopIter, *newComponentsTopIter, slot);
            } else {
                LOGD("%{public}s parent: %{public}s childer count %{public}lu CAN NOT update child %{public}s",
                    GetTag(), (GetElementParent().Upgrade() ? GetElementParent().Upgrade()->GetTag() : "No parent"),
                    children_.size(), (*oldChildrenTopIter)->GetTag());

                break;
            }
        } else {
            break;
        }
        ++slot;
        ++topLength;
        ++oldChildrenTopIter;
        ++newComponentsTopIter;
    }
    LOGD("%{public}s, checked TOP elements, count %{public}lu, slot %{public}d", GetTag(), topLength, slot);

    // Scan the bottom of the list.
    if (topLength < children_.size() && topLength < newComponents.size()) {
        do {
            --oldChildrenBottomIter;
            --newComponentsBottomIter;
            auto oldChild = *oldChildrenBottomIter;
            auto newComponent = *newComponentsBottomIter;
            if (!oldChild || !newComponent) {
                LOGE("Element or component is null during update proces");
            }
            // Break out of the loop if IDs are not the same
            if (!(oldChild && newComponent && oldChild->NeedUpdateWithComponent(newComponent) &&
                    oldChild->CanUpdate(newComponent))) {
                ++oldChildrenBottomIter;
                ++newComponentsBottomIter;
                break;
            }
            ++bottomLength;
        } while ((oldChildrenTopIter != oldChildrenBottomIter) && (newComponentsTopIter != newComponentsBottomIter));
    }
    LOGD("%{public}s, checked BOTTOM elements, count %{public}lu, slot %{public}d", GetTag(), bottomLength, slot);

    // Scan the old children in the middle of the list.
    // Collect all childeren with ID into the map

    LOGD("%{public}s, processing MIDDLE section, slot %{public}d", GetTag(), slot);
    std::map<ComposeId, RefPtr<ComposedElement>> oldKeyedChildren;
    bool haveOldChildren = (topLength + bottomLength < children_.size());
    if (haveOldChildren) {
        while (oldChildrenTopIter != oldChildrenBottomIter) {
            auto oldChild = AceType::DynamicCast<ComposedElement>(*oldChildrenTopIter);
            if (oldChild) {
                // ComposedComponent
                ++oldChildrenTopIter;
                if (oldKeyedChildren.count(oldChild->GetId()) == 0) {
                    LOGD("%{public}s Adding old child in the middle of the list ID: \"%{public}s\"" +
                        "to update %{public}s", GetTag(), oldChild->GetId().c_str(), oldChild->GetTag());
                    oldKeyedChildren[oldChild->GetId()] = oldChild;
                } else {
                    LOGD("%{public}s Deleting old child in the middle of the list ID: \"%{public}s\" %{public}s",
                        GetTag(), oldChild->GetId().c_str(), oldChild->GetTag());
                    RemoveChild(oldChild);
                }
            } else {
                // Not a ComposedComponent
                auto oldChild = *oldChildrenTopIter;
                ++oldChildrenTopIter;
                LOGD("%{public}s old child in the middle of the list: Delete it %{public}s",
                    GetTag(), oldChild->GetTag());
                RemoveChild(oldChild);
            }
        }
    }
    LOGD("%{public}s, checked MIDDLE old elements, count in the map %{public}lu", GetTag(),
        oldKeyedChildren.size());

    // Update the middle of the list.

    while (newComponentsTopIter != newComponentsBottomIter) {
        RefPtr<Element> oldChild;
        auto newComponent = AceType::DynamicCast<ComposedComponent>(*newComponentsTopIter);
        if (haveOldChildren && newComponent) {
            auto key = newComponent->GetId();
            if (oldKeyedChildren.count(key) != 0) {
                oldChild = oldKeyedChildren[key];
                LOGD("%{public}s, updating MIDDLE element: \"%{public}s\" ", GetTag(),
                    oldKeyedChildren[key]->GetId().c_str());
                oldKeyedChildren.erase(key);
            }
        }

        // newComponent can be null here, so use *newComponentsTopIter
        // Will update exiting element or add a new one

        LOGD("%{public}s, updating MIDDLE element: for slot %{public}d with %{public}s old child",
            GetTag(), slot, oldChild == nullptr ? "NO" : "existing");

        UpdateChild(oldChild, *newComponentsTopIter, slot);

        ++slot;
        ++newComponentsTopIter;
    }

    LOGD("%{public}s, updated MIDDLE elements, slot %{public}d", GetTag(), slot);

    // Update the end of the list

    while ((oldChildrenBottomIter != children_.end()) && (newComponentsBottomIter != newComponents.end())) {
        auto oldChild = *oldChildrenBottomIter;
        auto newComponent = *newComponentsBottomIter;

        if (oldChild && oldChild->NeedUpdateWithComponent(newComponent)) {
            UpdateChild(oldChild, newComponent, slot);
            LOGD("%{public}s, updatin BOTTOM child %{public}s, slot %{public}d", GetTag(), oldChild->GetTag(), slot);
        }
        ++slot;
        ++oldChildrenBottomIter;
        ++newComponentsBottomIter;
    }

    LOGD("%{public}s, updated BOTTOM elements, slot %{public}d", GetTag(), slot);
    LOGD("%{public}s, clean up %{public}zu oldChildren", GetTag(), oldKeyedChildren.size());
    if (!oldKeyedChildren.empty()) {
        for (const auto& oldChild : oldKeyedChildren) {
            RemoveChild(oldChild.second);
        }
    }
    LOGD("%{public}s end", GetTag());
}

void ComponentGroupElement::UpdateComposedChildrenPreprocess(const std::vector<RefPtr<Element>>& oldChildren,
    const std::list<RefPtr<Component>>& newComponents, size_t& topLength, size_t& bottomLength, int32_t& slot)
{
    auto oldChildrenTopIter = oldChildren.begin();
    auto oldChildrenBottomIter = oldChildren.end();
    auto newComponentsTopIter = newComponents.begin();
    auto newComponentsBottomIter = newComponents.end();
    topLength = 0;
    bottomLength = 0;
    slot = 0;

    // Update the top of the list.
    while ((oldChildrenTopIter != oldChildrenBottomIter) && (newComponentsTopIter != newComponentsBottomIter)) {
        auto oldChild = AceType::DynamicCast<ComposedElement>(*oldChildrenTopIter);
        auto newComponent = AceType::DynamicCast<ComposedComponent>(*newComponentsTopIter);
        if (oldChild && oldChild->NeedUpdateWithComponent(newComponent)) {
            UpdateChild(oldChild, newComponent, slot);
        } else {
            auto context = context_.Upgrade();
            if (context && context->GetIsDeclarative()) {
                break;
            }
        }
        ++slot;
        ++topLength;
        ++newComponentsTopIter;
        ++oldChildrenTopIter;
    }

    // Scan the bottom of the list.
    if (topLength < oldChildren.size() && topLength < newComponents.size()) {
        do {
            --oldChildrenBottomIter;
            --newComponentsBottomIter;
            auto oldChild = AceType::DynamicCast<ComposedElement>(*oldChildrenBottomIter);
            auto newComponent = AceType::DynamicCast<ComposedComponent>(*newComponentsBottomIter);
            if (oldChild && newComponent && oldChild->GetId() != newComponent->GetId()) {
                ++oldChildrenBottomIter;
                ++newComponentsBottomIter;
                break;
            }
            ++bottomLength;
        } while ((oldChildrenTopIter != oldChildrenBottomIter) && (newComponentsTopIter != newComponentsBottomIter));
    }

    // here, oldChildren and newComponents are divided into three parts!
    // first  part: [oldChildren.begin(), oldChildrenTopIter) and [newComponents.begin(), newComponentsTopIter)
    //              the corresponding id is the same and all children in this range have been updated.
    // second part: [oldChildrenTopIter, oldChildrenBottomIter) and [newComponentsTopIter, newComponentsBottomIter)
    //              the corresponding id is different.
    // third  part: [oldChildrenBottomIter, oldChildren.end()) and [newComponentsBottomIter, newComponents.end())
    //              the corresponding id is the same and all children in this range have not been updated.
    LOGD("oldChildren %{public}zu = %{public}zu + %{public}zd + %{public}zu", oldChildren.size(), topLength,
        std::distance(oldChildrenTopIter, oldChildrenBottomIter), bottomLength);
    LOGD("newComponents %{public}zu = %{public}zu+ %{public}zd + %{public}zu", newComponents.size(), topLength,
        std::distance(newComponentsTopIter, newComponentsBottomIter), bottomLength);
}

void ComponentGroupElement::UpdateComposedChildrenProcess(const std::vector<RefPtr<Element>>& oldChildren,
    const std::list<RefPtr<Component>>& newComponents, size_t topLength, size_t bottomLength, int32_t& slot,
    std::map<ComposeId, RefPtr<Element>>& oldKeyedChildren)
{
    auto oldChildrenTopIter = oldChildren.begin();
    auto oldChildrenBottomIter = oldChildren.end();
    auto newComponentsTopIter = newComponents.begin();
    auto newComponentsBottomIter = newComponents.end();
    std::advance(oldChildrenTopIter, topLength);
    std::advance(newComponentsTopIter, topLength);
    std::advance(oldChildrenBottomIter, -bottomLength);
    std::advance(newComponentsBottomIter, -bottomLength);
    oldKeyedChildren.clear();

    // Scan the old children in the middle of the list.
    bool haveOldChildren = (topLength + bottomLength < oldChildren.size());
    if (haveOldChildren) {
        while (oldChildrenTopIter != oldChildrenBottomIter) {
            auto oldChild = AceType::DynamicCast<ComposedElement>(*oldChildrenTopIter);
            if (oldChild) {
                oldKeyedChildren[oldChild->GetId()] = *oldChildrenTopIter;
            }
            ++oldChildrenTopIter;
        }
    }

    // Update the middle of the list.
    while (newComponentsTopIter != newComponentsBottomIter) {
        RefPtr<Element> oldChild;
        auto newComponent = AceType::DynamicCast<ComposedComponent>(*newComponentsTopIter);
        if (haveOldChildren && newComponent) {
            auto key = newComponent->GetId();
            if (oldKeyedChildren.count(key) != 0) {
                oldChild = oldKeyedChildren[key];
                oldKeyedChildren.erase(key);
            }
        }

        if (!oldChild || oldChild->NeedUpdateWithComponent(newComponent)) {
            UpdateChild(oldChild, newComponent, slot);
        }

        ++slot;
        ++newComponentsTopIter;
    }

    // We've scanned the whole list.
    ACE_DCHECK(oldChildrenTopIter == oldChildrenBottomIter);
    ACE_DCHECK(newComponentsTopIter == newComponentsBottomIter);
}

void ComponentGroupElement::UpdateComposedChildrenPostprocess(const std::vector<RefPtr<Element>>& oldChildren,
    const std::list<RefPtr<Component>>& newComponents, size_t topLength, size_t bottomLength, int32_t& slot,
    std::map<ComposeId, RefPtr<Element>>& oldKeyedChildren)
{
    auto oldChildrenBottomIter = oldChildren.end();
    auto newComponentsBottomIter = newComponents.end();
    std::advance(oldChildrenBottomIter, -bottomLength);
    std::advance(newComponentsBottomIter, -bottomLength);

    // Update the bottom of the list.
    while ((oldChildrenBottomIter != oldChildren.end()) && (newComponentsBottomIter != newComponents.end())) {
        auto oldChild = *oldChildrenBottomIter;
        auto newComponent = *newComponentsBottomIter;
        if (oldChild && oldChild->NeedUpdateWithComponent(newComponent)) {
            UpdateChild(oldChild, newComponent, slot);
        }
        ++slot;
        ++oldChildrenBottomIter;
        ++newComponentsBottomIter;
    }

    // Clean up any of the remaining middle nodes from the old list.
    bool haveOldChildren = (topLength + bottomLength < oldChildren.size());
    LOGD("clean up %{public}zu oldChildren", oldKeyedChildren.size());
    if (haveOldChildren && !oldKeyedChildren.empty()) {
        for (const auto& oldChild : oldKeyedChildren) {
            RemoveChild(oldChild.second);
        }
    }
}

std::list<RefPtr<Element>> ComponentGroupElement::UpdateComposedChildren(
    const std::list<RefPtr<Component>>& newComponents)
{
    // For javascript front-end, children of one node will keep their relative order during the update process.
    // In other word, if child A is in front of B, child A will surely be in front of B after update.
    // For a particular old child, after all the children before it have been processed, it must be in the right slot.
    LOGD("ComponentGroupElement::UpdateComposedChildren start for %{public}s child count: %{public}lu",
        GetTag(), children_.size());

    // For security, we use a copy of children_ as it will change during processing.
    std::vector<RefPtr<Element>> oldChildren(children_.begin(), children_.end());
    size_t topLength = 0;
    size_t bottomLength = 0;
    int32_t slot = 0;
    std::map<ComposeId, RefPtr<Element>> oldKeyedChildren;

    UpdateComposedChildrenPreprocess(oldChildren, newComponents, topLength, bottomLength, slot);
    UpdateComposedChildrenProcess(oldChildren, newComponents, topLength, bottomLength, slot, oldKeyedChildren);
    UpdateComposedChildrenPostprocess(oldChildren, newComponents, topLength, bottomLength, slot, oldKeyedChildren);

    LOGD("ComponentGroupElement::UpdateComposedChildren end");
    return children_;
}

std::list<RefPtr<Element>> ComponentGroupElement::UpdateComposedChildrenForEach(std::string oldFirstChildKey,
    int32_t oldChildCount, std::vector<std::string> newComponentsKeys, ComponentFunction&& componentFunc)
{
    LOGD("ComponentGroupElement::UpdateComposedChildrenForEach start");
    int32_t slot = 0;
    auto oldChildrenTopIter = children_.begin();
    auto oldChildrenBottomIter = children_.end();

    // Travese to get the start/end iter of foreach's item components.
    while ((oldChildrenTopIter != oldChildrenBottomIter)) {
        auto child = AceType::DynamicCast<ComposedElement>(*oldChildrenTopIter);
        if (child && child->GetId() == oldFirstChildKey) {
            break;
        }
        ++oldChildrenTopIter;
        ++slot;
    }

    oldChildrenBottomIter = oldChildrenTopIter;

    // Advance the bottomiter to the end of foreach items
    std::advance(oldChildrenBottomIter, oldChildCount);

    std::map<ComposeId, RefPtr<Element>> oldKeyedChildren;

    // Scan the old foreach component in the middle of the list.
    while (oldChildrenTopIter != oldChildrenBottomIter) {
        auto oldChild = AceType::DynamicCast<ComposedElement>(*oldChildrenTopIter);
        if (oldChild) {
            oldKeyedChildren[oldChild->GetId()] = *oldChildrenTopIter;
        }
        ++oldChildrenTopIter;
    }

    int32_t index = 0;
    for (auto key : newComponentsKeys) {
        RefPtr<Element> oldChild;
        if (oldKeyedChildren.count(key) != 0) {
            oldChild = oldKeyedChildren[key];
            oldKeyedChildren.erase(key);
        }

        if (oldChild) {
            // update the slot of the element
            oldChild->SetSlot(slot);
            children_.remove(oldChild);
            auto pos = children_.begin();
            std::advance(pos, slot);
            children_.insert(pos, oldChild);

            while (AceType::TypeName<ComposedElement>() == AceType::TypeName(oldChild)) {
                // this child is a composedelement
                // update its only child slot
                // if the child is again composed component
                // do the same until we hit a renderelement
                oldChild = oldChild->GetFirstChild();
                oldChild->SetSlot(slot);
            }
        } else {
            // New item in foreach added
            UpdateChild(oldChild, componentFunc(index), slot);
        }

        ++slot;
        ++index;
    }

    if (!oldKeyedChildren.empty()) {
        // remove the foreach items view which are removed
        for (const auto& oldChild : oldKeyedChildren) {
            RemoveChild(oldChild.second);
        }
    }

    LOGD("ComponentGroupElement::UpdateComposedChildrenForEach end");
    return children_;
}

} // namespace OHOS::Ace
