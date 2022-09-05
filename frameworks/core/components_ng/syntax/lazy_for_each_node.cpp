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

#include "core/components_ng/syntax/lazy_for_each_node.h"

#include <cstdint>
#include <type_traits>
#include <utility>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
void MakeNodeMapById(const std::list<RefPtr<UINode>>& nodes, const std::list<int32_t>& indexes,
    std::map<int32_t, RefPtr<UINode>>& result)
{
    ACE_DCHECK(ids.size() == nodes.size());
    auto idsIter = indexes.begin();
    auto nodeIter = nodes.begin();
    while (idsIter != indexes.end()) {
        result.emplace(*idsIter, *nodeIter);
        ++idsIter;
        ++nodeIter;
    }
}
} // namespace

RefPtr<LazyForEachNode> LazyForEachNode::GetOrCreateLazyForEachNode(
    int32_t nodeId, const RefPtr<LazyForEachBuilder>& forEachBuilder)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<LazyForEachNode>(nodeId);
    if (node) {
        if (node->builder_ != forEachBuilder) {
            LOGW("replace old lazy for each builder");
            node->builder_ = forEachBuilder;
        }
        return node;
    }
    node = MakeRefPtr<LazyForEachNode>(nodeId, forEachBuilder);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

void LazyForEachNode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapper>& parent, bool forceMeasure, bool forceLayout)
{
    CHECK_NULL_VOID(builder_);
    auto lazyLayoutWrapperBuilder = MakeRefPtr<LazyLayoutWrapperBuilder>(builder_, WeakClaim(this));
    const auto& cachedItems = builder_->GetCacheItems();
    for (const auto& iter : cachedItems) {
        auto frameNode = DynamicCast<FrameNode>(iter.second.second);
        if (frameNode) {
            lazyLayoutWrapperBuilder->AddCachedItem(
                iter.first, frameNode->CreateLayoutWrapper(forceMeasure, forceLayout));
        }
        // TODO: add ifelse syntax node.
    }

    parent->SetLayoutWrapperBuilder(lazyLayoutWrapperBuilder);
}

void LazyForEachNode::UpdateCachedItems(std::list<int32_t>& newIndexes)
{
    ACE_FUNCTION_TRACE();
    std::list<RefPtr<UINode>> oldChildren;
    std::swap(oldChildren, children_);
    auto& cachedItems = builder_->ModifyCacheItems();

    // create map id -> Node
    // old children
    std::map<int32_t, RefPtr<UINode>> oldNodeByIdMap;
    MakeNodeMapById(oldChildren, indexes_, oldNodeByIdMap);

    // result of id gen function of most re-recent render
    // create a map for quicker find/search
    std::unordered_set<int32_t> newIndexSet(newIndexes.begin(), newIndexes.end());

    // result of id gen function of previous render/re-render
    // create a map for quicker find/search
    std::unordered_set<int32_t> oldIndexSet(indexes_.begin(), indexes_.end());

    for (const auto& newIndex : newIndexes) {
        if (oldIndexSet.find(newIndex) == oldIndexSet.end()) {
            // found a newly added ID
            // insert new child item.
            // Call AddChild to execute AttachToMainTree of new child.
            AddChild(cachedItems[newIndex].second);
        } else {
            // the ID was used before, only need to update the child position.
            children_.emplace_back(oldNodeByIdMap[newIndex]);
            oldIndexSet.erase(newIndex);
        }
    }

    // the remain oldIndexSet is not used and need to remove.
    for (const auto& index : oldIndexSet) {
        cachedItems.erase(index);
    }

    // final swap old and new index.
    std::swap(indexes_, newIndexes);

    LOGD("cachedItems size is %{public}d", static_cast<int32_t>(cachedItems.size()));
}

} // namespace OHOS::Ace::NG