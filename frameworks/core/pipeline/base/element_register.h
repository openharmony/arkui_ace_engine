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

#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <functional>
#include "base/memory/referenced.h"
#include "frameworks/base/memory/ace_type.h"
#include "frameworks/core/components_ng/animation/geometry_transition.h"

namespace OHOS::Ace::V2 {
class ElementProxy;
} // namespace OHOS::Ace::V2

namespace OHOS::Ace::NG {
class UINode;
class FrameNode;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {
using ElementIdType = int32_t;
class Element;

using RemovedElementsType = std::unordered_set<ElementIdType>;

class ACE_EXPORT ElementRegister {
public:
    static constexpr ElementIdType UndefinedElementId = static_cast<ElementIdType>(-1);

    ACE_FORCE_EXPORT static ElementRegister* GetInstance();
    RefPtr<Element> GetElementById(ElementIdType elementId);
    RefPtr<V2::ElementProxy> GetElementProxyById(ElementIdType elementId);

    ACE_FORCE_EXPORT RefPtr<AceType> GetNodeById(ElementIdType elementId);
    /**
     * version of GetNodeById(elmtId) function to return an Element of
     * given class. returns nullptr if Element with this elmtId baddest found
     * or class mismatch
     */
    template<class E>
    RefPtr<E> GetSpecificItemById(ElementIdType elmtId)
    {
        return AceType::DynamicCast<E>(GetNodeById(elmtId));
    }

    bool AddElementProxy(const WeakPtr<V2::ElementProxy>& element);
    bool AddElement(const RefPtr<Element>& element);

    RefPtr<NG::UINode> GetUINodeById(ElementIdType elementId);
    NG::FrameNode* GetFrameNodePtrById(ElementIdType elementId);

    ACE_FORCE_EXPORT bool AddUINode(const RefPtr<NG::UINode>& node);

    bool Exists(ElementIdType elementId);

    /**
     * When a custom node is created from recycle, update its element id.
     */
    void UpdateRecycleElmtId(int32_t oldElmtId, int32_t newElmtId);

    /**
     * remove Element with given elmtId from the Map
     * means GetElementById on this elmtId no longer returns an Element
     * method adds the elmtId to the removed Element Set
     */
    bool RemoveItem(ElementIdType elementId);

    /**
     * remove Element with given elmtId from the Map
     * means GetElementById on this elmtId no longer returns an Element
     * method does NOT add the elmtId to the removed Element Set
     * Use with caution: e.g. only use when knowing the Element will
     * be added with new ElementId shortly
     */
    ACE_FORCE_EXPORT bool RemoveItemSilently(ElementIdType elementId);

    void MoveRemovedItems(RemovedElementsType& removedItems);

    /**
     * does a complete reset
     * clears the Map of Elements and Set of removed Elements
     */
    void Clear();

    ACE_FORCE_EXPORT ElementIdType MakeUniqueId()
    {
        return nextUniqueElementId_++;
    }

    RefPtr<NG::GeometryTransition> GetOrCreateGeometryTransition(
        const std::string& id, bool followWithoutTransition = false, bool doRegisterSharedTransition = true);
    void DumpGeometryTransition();

    void ReSyncGeometryTransition(const WeakPtr<NG::FrameNode>& trigger = nullptr,
                                  const AnimationOption& option = AnimationOption());

    void AddPendingRemoveNode(const RefPtr<NG::UINode>& node);
    void ClearPendingRemoveNodes();

    void RegisterJSCleanUpIdleTaskFunc(const std::function<void(void)>& jsCallback) {
        jsCleanUpIdleTaskCallback_ = std::move(jsCallback);
    }

    void CallJSCleanUpIdleTaskFunc() {
        if (jsCleanUpIdleTaskCallback_) {
            jsCleanUpIdleTaskCallback_();
        }
    }

    uint32_t GetNodeNum() const
    {
        return itemMap_.size();
    }

    ElementIdType GetLastestElementId() const
    {
        return lastestElementId_;
    }

    RefPtr<NG::FrameNode> GetAttachedFrameNodeById(const std::string& key, bool willGetAll = false);

    void AddFrameNodeByInspectorId(const std::string& key, const WeakPtr<NG::FrameNode>& node);

    void RemoveFrameNodeByInspectorId(const std::string& key, int32_t nodeId);

private:
    // private constructor
    ElementRegister() = default;

    bool AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced);

    //  Singleton instance
    static thread_local ElementRegister* instance_;
    static std::mutex mutex_;

    // ElementID assigned during initial render
    // first to Component, then synced to Element
    ElementIdType nextUniqueElementId_ = 0;

    ElementIdType lastestElementId_ = 0;

    // Map for created elements
    std::unordered_map<ElementIdType, WeakPtr<AceType>> itemMap_;

    // Map for inspectorId
    std::unordered_map<std::string, std::list<WeakPtr<NG::FrameNode>>> inspectorIdMap_;

    RemovedElementsType removedItems_;

    std::unordered_map<std::string, RefPtr<NG::GeometryTransition>> geometryTransitionMap_;

    std::list<RefPtr<NG::UINode>> pendingRemoveNodes_;

    std::function<void(void)> jsCleanUpIdleTaskCallback_;

    ACE_DISALLOW_COPY_AND_MOVE(ElementRegister);
};
} // namespace OHOS::Ace
#endif
