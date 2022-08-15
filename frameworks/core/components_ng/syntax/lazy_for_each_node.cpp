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

#include "base/utils/utils.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

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

void LazyForEachNode::UpdateCachedItems(const std::unordered_set<int32_t>& activeIndexes)
{
    children_.clear();
    auto& cachedItems = builder_->ModifyCacheItems();
    for (auto iter = cachedItems.begin(); iter != cachedItems.end();) {
        if (activeIndexes.count(iter->first) > 0) {
            AddChild(iter->second.second);
            ++iter;
        } else {
            iter = cachedItems.erase(iter);
        }
    }
    LOGD("cachedItems size is %{public}d", static_cast<int32_t>(cachedItems.size()));
}

} // namespace OHOS::Ace::NG