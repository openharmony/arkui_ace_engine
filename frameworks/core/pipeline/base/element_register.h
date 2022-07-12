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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_ELEMENT_REGISTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_ELEMENT_REGISTER_H

#include <unordered_map>
#include <unordered_set>

#include "frameworks/base/memory/ace_type.h"

namespace OHOS::Ace::V2 {
    class ElementProxy;
}

namespace OHOS::Ace {
using ElementIdType = int32_t;
class Element;

class ACE_EXPORT ElementRegister {
public:
    static constexpr ElementIdType UndefinedElementId = static_cast<ElementIdType>(-1);

    static ElementRegister* GetInstance();
    RefPtr<Element> GetElementById(ElementIdType elementId);
    RefPtr<V2::ElementProxy> GetElementProxyById(ElementIdType elementId);

    /**
     * version of GetElementById(elmtId) function to return an Element of
     * given class. returns nullptr if Element with this elmtId naddeot found
     * or class mismatch
     */
    template<class E>
    RefPtr<E> GetSpecificElementById(ElementIdType elmtId)
    {
        return AceType::DynamicCast<E>(GetElementById(elmtId));
    }

    bool Exists(ElementIdType elementId);
    bool AddElementProxy(const WeakPtr<V2::ElementProxy>& element);
    bool AddElement(const RefPtr<Element>& element);

    /**
     * remove Element with given elmtId from the Map
     * means GetElementById on this elmtId no longer returns an Element
     * method adds the elmtId to the removed Element Set
     */
    bool RemoveElement(ElementIdType elementId);

    /**
     * remove Element with given elmtId from the Map
     * means GetElementById on this elmtId no longer returns an Element
     * method does NOT add the elmtId to the removed Element Set
     * Use with cautiuon: e.g. only use when knowing the Element will
     * be added with new ElementId shortly
     */
    bool RemoveElementSilently(ElementIdType elementId);

    /**
     * return  removed elements set to the caller
     * should be followed by ClearRemovedElements() call
     */
    std::unordered_set<ElementIdType>& GetRemovedElements();
    void ClearRemovedElement(ElementIdType elmtId)
    {
        removedElements_.erase(elmtId);
    }

    /**
     * does a complete reset
     * clears the Map of Elements and Set of removed Elemnts
     */
    void Clear();

    ElementIdType MakeUniqueId()
    {
        return nextUniqueElementId_++;
    }

private:
    // private constructor
    ElementRegister() = default;

    bool AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced);

    //  Singleton instance
    static thread_local ElementRegister* instance_;

    // ElementID assiugned during intial render
    // first to Component, then syned to Element
    ElementIdType nextUniqueElementId_ = 0;

    // Map for created elements
    std::unordered_map<ElementIdType, WeakPtr<AceType>> elementMap_;

    // Set of removed Elements (not in elementMap_ anymore)
    std::unordered_set<ElementIdType> removedElements_;

    ACE_DISALLOW_COPY_AND_MOVE(ElementRegister);
};
} // namespace OHOS::Ace
#endif