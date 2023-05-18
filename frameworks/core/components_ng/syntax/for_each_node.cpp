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

#include "core/components_ng/syntax/for_each_node.h"

#include <list>
#include <type_traits>

#include "base/log/ace_performance_check.h"
#include "base/log/ace_trace.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
void MakeNodeMapById(const std::list<RefPtr<UINode>>& nodes, const std::list<std::string>& ids,
    std::map<std::string, RefPtr<UINode>>& result)
{
    ACE_DCHECK(ids.size() == nodes.size());
    auto idsIter = ids.begin();
    auto nodeIter = nodes.begin();
    while (idsIter != ids.end() && nodeIter != nodes.end()) {
        result.emplace(*idsIter, *nodeIter);
        ++idsIter;
        ++nodeIter;
    }
}
} // namespace

RefPtr<ForEachNode> ForEachNode::GetOrCreateForEachNode(int32_t nodeId)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<ForEachNode>(nodeId);
    if (node) {
        return node;
    }
    node = MakeRefPtr<ForEachNode>(nodeId);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

void ForEachNode::CreateTempItems()
{
    std::swap(ids_, tempIds_);
    std::swap(ModifyChildren(), tempChildren_);
}

// same as foundation/arkui/ace_engine/frameworks/core/components_part_upd/foreach/foreach_element.cpp.
void ForEachNode::CompareAndUpdateChildren()
{
    ACE_SCOPED_TRACE("ForEachNode::CompareAndUpdateChildren");
    LOGD("Local update for ForEachNode nodeId: %{public}d ....", GetId());

    // result of id gen function of most re-recent render
    // create a map for quicker find/search
    std::unordered_set<std::string> newIdsSet(ids_.begin(), ids_.end());

    // result of id gen function of previous render/re-render
    // create a map for quicker find/search
    std::unordered_set<std::string> oldIdsSet(tempIds_.begin(), tempIds_.end());

    // ForEachNode only includes children for newly created_ array items
    // it does not include children of array items that were rendered on a previous
    // render
    std::list<RefPtr<UINode>> additionalChildComps;
    auto& children = ModifyChildren();
    std::swap(additionalChildComps, children);

    // create map id -> Node
    // old children
    std::map<std::string, RefPtr<UINode>> oldNodeByIdMap;
    MakeNodeMapById(tempChildren_, tempIds_, oldNodeByIdMap);

    int32_t additionalChildIndex = 0;
    for (const auto& newId : ids_) {
        auto oldIdIt = oldIdsSet.find(newId);
        if (oldIdIt == oldIdsSet.end()) {
            // found a newly added ID
            // insert new child item.
            auto newCompsIter = additionalChildComps.begin();
            std::advance(newCompsIter, additionalChildIndex++);
            if (newCompsIter != additionalChildComps.end()) {
                // Call AddChild to execute AttachToMainTree of new child.
                AddChild(*newCompsIter);
            }
        } else {
            auto iter = oldNodeByIdMap.find(newId);
            // the ID was used before, only need to update the child position.
            if (iter != oldNodeByIdMap.end() && iter->second) {
                AddChild(iter->second, DEFAULT_NODE_SLOT, true);
            }
            oldIdsSet.erase(oldIdIt);
        }
    }

    for (const auto& oldId : oldIdsSet) {
        auto iter = oldNodeByIdMap.find(oldId);
        if (iter != oldNodeByIdMap.end()) {
            // Adding silently, so that upon removal
            // node is a part the tree.
            // OnDetachFromMainTree to be called while node
            // still part of the tree, we need to find
            // position in the tab tab for the tab.
            AddChild(iter->second, DEFAULT_NODE_SLOT, true);
            // Remove and trigger all Detach callback.
            RemoveChild(iter->second, true);
        }
    }

    if (IsOnMainTree()) {
        for (const auto& newChild : additionalChildComps) {
            newChild->AttachToMainTree();
        }
    }

    tempChildren_.clear();
    tempIds_.clear();

    auto parent = GetParent();
    if (parent) {
        parent->ChildrenUpdatedFrom(0);
    }
}

void ForEachNode::FlushUpdateAndMarkDirty()
{
    // mark parent dirty to flush measure.
    MarkNeedSyncRenderTree();
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_BY_CHILD_REQUEST);
}

} // namespace OHOS::Ace::NG
