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

#include "frameworks/core/components_part_upd/foreach/foreach_element.h"

#include "frameworks/core/components_part_upd/foreach/foreach_component.h"

namespace OHOS::Ace::PartUpd {

bool ForEachElement::CanUpdate(const RefPtr<Component>& newComponent)
{
    return AceType::InstanceOf<PartUpd::ForEachComponent>(newComponent);
}

bool ForEachElement::CompareSlots(const RefPtr<Element>& first, const RefPtr<Element>& second)
{
    // sort lift of child Elements by their slot
    return first->GetSlot() < second->GetSlot();
}

// adds elements from given list into a Map with key Element.GetSlot
void ForEachElement::MakeElementByIdMap(const std::list<RefPtr<Element>>& elmts, const std::list<std::string>& ids,
    std::map<std::string, Ace::RefPtr<Element>>& result)
{
    ACE_SCOPED_TRACE("ForEachElement::UpdateWithComponent makeElmtByIdMap");

    ACE_DCHECK(ids.size() == elmts.size());

    // 1. step map Elements by their slot, because elmts is not sorted by slot
    std::map<int, Ace::RefPtr<Element>> elmtsBySlotMap;
    for (const auto& elmt : elmts) {
        ACE_DCHECK(elmt->GetSlot() >= 0);
        elmtsBySlotMap.emplace(elmt->GetSlot(), elmt);
    }
    ACE_DCHECK(elmtsBySlotMap.size() == elmts.size());

    // 2. map elmts by their id. Note ids list is in slot order
    auto idsIter = ids.begin();
    int slot = 0;
    while (idsIter != ids.end()) {
        auto elmtIter = elmtsBySlotMap.find(slot);
        ACE_DCHECK(elmtIter != elmtsBySlotMap.end());
        result.emplace(*idsIter, (*elmtIter).second);
        idsIter++;
        slot++;
    }
}

void ForEachElement::RemoveUnusedChildElementsFromRegistery(const std::list<std::string>& newIds) const
{
    ACE_SCOPED_TRACE("ForEachElement::RemoveUnusedChildElementsFromRegistery");

    // ID array before update
    std::list<std::string> oldIds = GetIdArray();

    if (oldIds.empty()) {
        return;
    }

    // construct a set from newIds list for faster find/search
    std::unordered_set<std::string> newIdsSet(newIds.begin(), newIds.end());

    // Element children before update
    const auto& oldChildElementsRef = GetChildren();
    std::list<RefPtr<Element>> oldChildElements(oldChildElementsRef); // make a copy of the list
    oldChildElements.sort(CompareSlots); // needs sorting by their slot to match the order of oldIds array

    ACE_DCHECK((oldIds.size() == oldChildElements.size()) &&
               "Number of IDs generated during previous render and number of ForEach child Elements must match");

    auto oldElementIter = oldChildElements.begin();
    for (const auto& oldId : oldIds) {
        // check if oldId still in newIds array
        if (newIdsSet.find(oldId) == newIdsSet.end()) {
            (*oldElementIter)->UnregisterForPartialUpdates();
        }
        oldElementIter++;
    }
}

void ForEachElement::Update()
{
    RefPtr<PartUpd::ForEachComponent> newFEComp = AceType::DynamicCast<PartUpd::ForEachComponent>(component_);
    if (!newFEComp) {
        LOGE("ForEachElement elmtId : %{public}d, no ForEachComponent set to update from, internal error",
            GetElementId());
        return;
    }
    MultiComposedElement::Update();

    SetIdArray(newFEComp->GetIdArray());
}

void ForEachElement::LocalizedUpdate()
{
    ACE_SCOPED_TRACE("ForEachElement::LocalizedUpdate");

    RefPtr<PartUpd::ForEachComponent> newFEComp = AceType::DynamicCast<PartUpd::ForEachComponent>(component_);
    if (!newFEComp) {
        LOGE("ForEachElement elmtId : %{public}d, no ForEachComponent set to update from, internal error",
            GetElementId());
        return;
    }
    // result of id gen function of most re-recent render
    // create a map for quicker find/search
    std::list<std::string> newIds = newFEComp->GetIdArray();
    std::unordered_set<std::string> newIdsSet(newIds.begin(), newIds.end());

    // result of id gen function of previous render/re-render
    // create a map for quicker find/search
    const auto& oldIds = GetIdArray();
    std::unordered_set<std::string> oldIdsSet(oldIds.begin(), oldIds.end());

    // ForEachComponent only includes children for _newly created_ array items
    // it does _not_ include children of array items that were rendered on a previous
    // render
    const auto& additionalChildComps = newFEComp->GetChildren();

    // create map id gen result -> Element
    // old children
    std::map<std::string, Ace::RefPtr<Element>> oldElmtsByIdMap;
    MakeElementByIdMap(GetChildren(), oldIds, oldElmtsByIdMap);

    ACE_DCHECK((oldIds.size() == GetChildren().size()) &&
               "Number of IDs generated during previous render and number of ForEach child Elements must match");
    ACE_DCHECK(oldIdsSet.size() == oldIds.size());
    ACE_DCHECK(GetChildren().size() == oldElmtsByIdMap.size());

    auto firstChildElement = GetChildren().begin();
    int renderSlot = GetRenderSlot();

    bool needRequestLayout = false;
    int32_t slot = ((*firstChildElement) != nullptr) ? (*firstChildElement)->GetSlot() : 0;
    int additionalChildIndex = 0;
    for (const auto& newId : newIds) {
        if (oldIdsSet.find(newId) == oldIdsSet.end()) {
            // found a newly added ID
            // insert component into 'slot'
            auto newCompsIter = additionalChildComps.begin();
            std::advance(newCompsIter, additionalChildIndex++);
            InflateComponent(*newCompsIter, slot, renderSlot);
            needRequestLayout = false;
        } else {
            // the ID was used before, only need to update the child Element's slot
            auto iter = oldElmtsByIdMap.find(newId);
            auto oldElmt = (*iter).second;
            ChangeChildSlot(oldElmt, slot);
            ChangeChildRenderSlot(oldElmt, renderSlot, true);
            needRequestLayout = true;
        }
        slot++;
        renderSlot++;
    }

    for (const auto& oldId : oldIds) {
        // check if oldId still in newIds array
        if (newIdsSet.find(oldId) == newIdsSet.end()) {
            // the ID is no longer used, delete the child Element
            auto iter = oldElmtsByIdMap.find(oldId);
            auto oldElmt = iter->second;
            // no new child component
            UpdateChild(oldElmt, nullptr);
            needRequestLayout = false;
        }
    }
    SetIdArray(newFEComp->GetIdArray());
    Update();
    if (needRequestLayout) {
        auto renderNode = GetRenderNode();
        if (renderNode != nullptr) {
            renderNode->MarkNeedLayout();
        }
    }
    SetNewComponent(nullptr);
}
} // namespace OHOS::Ace::PartUpd
