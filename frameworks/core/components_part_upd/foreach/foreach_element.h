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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_COMPONENTS_FOR_EACH_ELEMENT_PART_UPD_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_COMPONENTS_FOR_EACH_ELEMENT_PART_UPD_H

#include <list>
#include <string>

#include "base/utils/macros.h"
#include "frameworks/core/pipeline/base/multi_composed_element.h"

namespace OHOS::Ace::PartUpd {

// ComposedElement just maintain a child element may have render node.
class ACE_EXPORT ForEachElement : public MultiComposedElement {
    DECLARE_ACE_TYPE(PartUpd::ForEachElement, MultiComposedElement);

using ComponentFunction = std::function<RefPtr<Component>(int32_t index)>;

public:
    explicit ForEachElement(const ComposeId& id) : MultiComposedElement(id) {};
    ~ForEachElement() override = default;
    bool CanUpdate(const RefPtr<Component>& newComponent) override;

    // array of id created during render
    // update from ForEachComponent on sync
    // purpose: memorize what array items (their IDs) have been
    // used for creating child components during previous render
    // and in which order (slots)
    // use to determin chich child Elements to keep and possibly
    // move, which ones to delete
    // e.g. old [ 1, 2, 3], new [ 0, 1, 2]
    //   new child from Component place to index 0
    //   old child moves from index 0 to 1
    //   old child moves from index 1 to 2
    //   old child at index 2 delete
    void SetIdArray(const std::list<std::string>& newIdArray)
    {
        idArray_ = newIdArray;
    }

    const std::list<std::string>& GetIdArray() const
    {
        return idArray_;
    }

    /**
     * Compare current ID array with given new ID array
     * find no longer used IDs, the corresponding earlier created child Element for each such ID
     * remove these children from the ElementRegister.
     * This function is called from
     * TS View.forEachUpdateFunction -> ForEach.setIdArray ->
     * C++ JSForEach::SetIdArray
     * This function reads from the ForEachElement but it does not modify it.
     */
    void RemoveUnusedChildElementsFromRegistery(const std::list<std::string>& newIds) const;

   // caution added for partial update
    virtual void Update() override;

    /**
     * Update Element with given ForEachComponent
     */
    virtual void LocalizedUpdate() override;

    /**
     * helper function that updates the slot of given Element
     * if the Element is a ComposedElement it
     * recursively sets the slot of of the single child until
     * it get to the first RenderElement
     */
    void UpdateSlot(const RefPtr<Element>& element, int32_t slot, int32_t renderSlot);

protected:
    static bool CompareSlots(const RefPtr<Element>& first, const RefPtr<Element>& second);
    // adds elements from given list into a Map with key Element.GetSlot
    static void MakeElementByIdMap(const std::list<RefPtr<Element>>& elmts,
        const std::list<std::string>& ids, std::map<std::string, Ace::RefPtr<Element>>& result);

private:
    std::list<std::string> idArray_;
};

} // namespace OHOS::Ace::PartUpd
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_COMPONENTS_FOR_EACH_ELEMENT_H
