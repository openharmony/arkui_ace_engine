/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include <functional>
#include <inttypes.h>
#include <list>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

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

    ACE_FORCE_EXPORT RefPtr<NG::UINode> GetUINodeById(ElementIdType elementId);
    ACE_FORCE_EXPORT std::vector<RefPtr<NG::UINode>> GetUINodesFromItemMap(const std::vector<std::int32_t>& keys);
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

    ACE_FORCE_EXPORT ElementIdType MakeUniqueId();
    /**
     * For ArkTS 1.2
     *
     * Based on the incoming capacity, generate the starting value for arkoala node IDs
     * and adjust the nextUniqueElementId_ value.
     */
    ACE_FORCE_EXPORT ElementIdType RequireArkoalaNodeId(int32_t capacity);

    RefPtr<NG::GeometryTransition> GetOrCreateGeometryTransition(
        const std::string& id, bool followWithoutTransition = false, bool doRegisterSharedTransition = true);
    void DumpGeometryTransition();

    void ReSyncGeometryTransition(const WeakPtr<NG::FrameNode>& trigger = nullptr,
                                  const AnimationOption& option = AnimationOption());

    void AddPendingRemoveNode(const RefPtr<NG::UINode>& node);
    void ClearPendingRemoveNodes();

    uint32_t GetNodeNum() const;

    ElementIdType GetLatestElementId() const;

    RefPtr<NG::FrameNode> GetAttachedFrameNodeById(
        const std::string& key, bool willGetAll = false, int32_t instanceId = -1);

    void AddFrameNodeByInspectorId(const std::string& key, const WeakPtr<NG::FrameNode>& node, int32_t nodeId);

    void RemoveFrameNodeByInspectorId(const std::string& key, int32_t nodeId);

    void RegisterEmbedNode(const uint64_t surfaceId, const WeakPtr<NG::FrameNode>& node);

    void UnregisterEmbedNode(const uint64_t surfaceId, const WeakPtr<NG::FrameNode>& node);

    WeakPtr<NG::FrameNode> GetEmbedNodeBySurfaceId(const uint64_t surfaceId);

    bool IsEmbedNode(NG::FrameNode* node);

    uint64_t GetSurfaceIdByEmbedNode(NG::FrameNode* node);

private:
    // private constructor
    ElementRegister() = default;

    bool AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced);
    ACE_DISALLOW_COPY_AND_MOVE(ElementRegister);
};
} // namespace OHOS::Ace
#endif
