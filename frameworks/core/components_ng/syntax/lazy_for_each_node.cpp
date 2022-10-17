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

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <optional>
#include <utility>

#include "base/memory/referenced.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/syntax/for_each_node.h"
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
    lazyLayoutWrapperBuilder->UpdateIndexRange(startIndex_, endIndex_, ids_);
    lazyLayoutWrapperBuilder->UpdateForceFlag(forceMeasure, forceLayout);
    parent->SetLayoutWrapperBuilder(lazyLayoutWrapperBuilder);
}

void LazyForEachNode::UpdateLazyForEachItems(int32_t newStartIndex, int32_t newEndIndex,
    std::list<std::optional<std::string>>&& nodeIds,
    std::unordered_map<int32_t, std::optional<std::string>>&& cachedItems)
{
    ACE_SCOPED_TRACE("lazyforeach update cache [%d -%d]", newStartIndex, newEndIndex);
    CHECK_NULL_VOID(builder_);
    std::list<std::optional<std::string>> newIds(std::move(nodeIds));
    // clean current children.
    Clean();

    // delete all.
    if (newIds.empty()) {
        builder_->Clean();
        startIndex_ = -1;
        endIndex_ = -1;
        ids_.clear();
        return;
    }

    auto newSize = static_cast<int32_t>(newIds.size());
    if ((newEndIndex - newStartIndex + 1) != newSize) {
        LOGE("the index is illegal, %{public}d, %{public}d, %{public}d", newStartIndex, newEndIndex, newSize);
        return;
    }

    // use new ids to create new child tree.
    for (const auto& id : newIds) {
        CHECK_NULL_VOID(id);
        auto uiNode = builder_->GetChildByKey(*id);
        CHECK_NULL_VOID(uiNode);
        AddChild(uiNode);
    }

    // delete useless items.
    builder_->UpdateCachedItems(newIds, std::move(cachedItems));

    startIndex_ = newStartIndex;
    endIndex_ = newEndIndex;
    std::swap(ids_, newIds);
    LOGD("cachedItems size is %{public}d", static_cast<int32_t>(newIds.size()));
}

void LazyForEachNode::PostIdleTask(std::list<int32_t>&& items)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    predictItems_ = std::move(items);
    if (needPredict) {
        return;
    }
    needPredict = true;
    context->AddPredictTask([weak = AceType::WeakClaim(this)](int64_t deadline) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->needPredict = false;
        ACE_SCOPED_TRACE("LazyForEach predict size[%zu]", node->predictItems_.size());
        decltype(node->predictItems_) items(std::move(node->predictItems_));
        auto item = items.begin();
        while (item != items.end()) {
            if (GetSysTimestamp() > deadline) {
                std::list<int32_t> predictItems;
                predictItems.insert(predictItems.begin(), item, items.end());
                node->PostIdleTask(std::move(predictItems));
                return;
            }

            auto itemInfo = node->builder_->CreateChildByIndex(*item);
            node->builder_->SetCacheItemInfo(*item, itemInfo.first);
            auto uiNode = itemInfo.second;
            if (uiNode) {
                uiNode->Build();
            }
            item++;
        }
    });
}

void LazyForEachNode::OnDataReloaded()
{
    startIndex_ = -1;
    endIndex_ = -1;
    ids_.clear();
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataAdded(size_t index)
{
    auto insertIndex = static_cast<int32_t>(index);
    // check if insertIndex is in the range [startIndex_, endIndex_ + 1]
    if ((insertIndex < startIndex_)) {
        LOGI("insertIndex is out of begin range, ignored, %{public}d, %{public}d", insertIndex, startIndex_);
        startIndex_++;
        endIndex_++;
        return;
    }
    if (insertIndex > (endIndex_ + 1)) {
        LOGI("insertIndex is out of end range, ignored, %{public}d, %{public}d", insertIndex, endIndex_);
        return;
    }
    if (insertIndex == startIndex_) {
        // insert at begin.
        ids_.emplace_front(std::nullopt);
    } else if (insertIndex == (endIndex_ + 1)) {
        // insert at end.
        ids_.emplace_back(std::nullopt);
    } else {
        // insert at middle.
        auto iter = ids_.begin();
        std::advance(iter, index - startIndex_);
        ids_.insert(iter, std::nullopt);
    }
    endIndex_++;
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataDeleted(size_t index)
{
    auto deletedIndex = static_cast<int32_t>(index);
    if (deletedIndex > endIndex_) {
        LOGI("deletedIndex is out of end range, ignored, %{public}d, %{public}d", deletedIndex, endIndex_);
        return;
    }
    if (deletedIndex < startIndex_) {
        LOGI("deletedIndex is out of begin range, ignored, %{public}d, %{public}d", deletedIndex, startIndex_);
        startIndex_--;
        endIndex_--;
        return;
    }
    if (deletedIndex == startIndex_) {
        // delete at begin.
        ids_.pop_front();
    } else if (deletedIndex == endIndex_) {
        // delete at end.
        ids_.pop_back();
    } else {
        // delete at middle.
        auto iter = ids_.begin();
        std::advance(iter, index - startIndex_);
        ids_.erase(iter);
    }
    endIndex_--;
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataChanged(size_t index)
{
    auto changeIndex = static_cast<int32_t>(index);
    if ((changeIndex < startIndex_) || (changeIndex > endIndex_)) {
        LOGI("changeIndex is out of range, ignored, %{public}d, %{public}d, %{public}d", changeIndex, startIndex_,
            endIndex_);
        return;
    }
    auto iter = ids_.begin();
    std::advance(iter, index - startIndex_);
    *iter = std::nullopt;
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataMoved(size_t from, size_t to)
{
    auto fromIndex = static_cast<int32_t>(from);
    auto toIndex = static_cast<int32_t>(to);
    auto fromOutOfRange = (fromIndex < startIndex_) || (fromIndex > endIndex_);
    auto toOutOfRange = (toIndex < startIndex_) || (toIndex > endIndex_);
    if (fromOutOfRange && toOutOfRange) {
        LOGI("both out of range, ignored");
        return;
    }
    if (fromOutOfRange && !toOutOfRange) {
        auto iter = ids_.begin();
        std::advance(iter, toIndex - startIndex_);
        *iter = std::nullopt;
        MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return;
    }
    if (!fromOutOfRange && toOutOfRange) {
        auto iter = ids_.begin();
        std::advance(iter, fromIndex - startIndex_);
        *iter = std::nullopt;
        MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        return;
    }
    auto formIter = ids_.begin();
    std::advance(formIter, fromIndex - startIndex_);
    auto toIter = ids_.begin();
    std::advance(toIter, toIndex - startIndex_);
    auto temp = *formIter;
    *formIter = *toIter;
    *toIter = temp;
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

} // namespace OHOS::Ace::NG