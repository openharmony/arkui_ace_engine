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

#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_v2/inspector/inspector_constants.h"
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

void LazyForEachNode::AdjustLayoutWrapperTree(
    const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
{
    CHECK_NULL_VOID(builder_);
    auto lazyLayoutWrapperBuilder = MakeRefPtr<LazyLayoutWrapperBuilder>(builder_, WeakClaim(this));
    if (parent->GetHostTag() == V2::SWIPER_ETS_TAG) {
        lazyLayoutWrapperBuilder->SetLazySwiper();
    }
    lazyLayoutWrapperBuilder->UpdateIndexRange(startIndex_, endIndex_, ids_);
    lazyLayoutWrapperBuilder->UpdateForceFlag(forceMeasure, forceLayout);
    parent->SetLayoutWrapperBuilder(lazyLayoutWrapperBuilder);
}

void LazyForEachNode::BuildAllChildren()
{
    for (int i = 0; i < FrameCount(); i++) {
        GetFrameChildByIndex(i);
    }
}

void LazyForEachNode::UpdateLazyForEachItems(int32_t newStartIndex, int32_t newEndIndex,
    std::list<std::optional<std::string>>&& nodeIds,
    std::unordered_map<int32_t, std::optional<std::string>>&& cachedItems)
{
    ACE_SCOPED_TRACE("lazyforeach update cache [%d -%d]", newStartIndex, newEndIndex);
    CHECK_NULL_VOID(builder_);
    std::list<std::optional<std::string>> newIds(std::move(nodeIds));

    // delete all.
    if (newIds.empty()) {
        // clean current children.
        Clean(true, true);
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

    int32_t slot = 0;
    // use new ids to update child tree.
    for (const auto& id : newIds) {
        CHECK_NULL_VOID(id);
        auto uiNode = builder_->GetChildByKey(*id);
        CHECK_NULL_VOID(uiNode);
        int32_t childIndex = GetChildIndex(uiNode);
        if (childIndex < 0) {
            AddChild(uiNode, slot);
        } else if (childIndex != slot) {
            uiNode->MovePosition(slot);
        }
        slot++;
    }
    while (static_cast<size_t>(slot) < GetChildren().size()) {
        RemoveChild(GetLastChild(), true);
    }

    // delete useless items.
    builder_->UpdateCachedItems(newIds, std::move(cachedItems));

    startIndex_ = newStartIndex;
    endIndex_ = newEndIndex;
    std::swap(ids_, newIds);
    LOGD("cachedItems size is %{public}d", static_cast<int32_t>(newIds.size()));
}

void LazyForEachNode::PostIdleTask()
{
    if (needPredict_) {
        return;
    }
    needPredict_ = true;
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = AceType::WeakClaim(this)](int64_t deadline, bool canUseLongPredictTask) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->needPredict_ = false;
        ACE_SCOPED_TRACE(
            "LazyForEach predict [%d-%d] cache size [%d]", node->startIndex_, node->endIndex_, node->cacheCount_);
        auto canRunLongPredictTask = node->requestLongPredict_ && canUseLongPredictTask;
        if (node->builder_) {
            ViewStackProcessor::GetInstance()->SetPredict(true);
            auto preBuildResult = node->builder_->PreBuild(node->startIndex_, node->endIndex_, node->cacheCount_,
                deadline, node->itemConstraint_, canRunLongPredictTask);
            ViewStackProcessor::GetInstance()->SetPredict(false);
            if (!preBuildResult) {
                node->PostIdleTask();
            }
        }
        node->requestLongPredict_ = false;
        node->itemConstraint_.reset();
    });
}

void LazyForEachNode::PostIdleTask(
    std::list<int32_t>&& items, const std::optional<LayoutConstraintF>& itemConstraint, bool longPredictTask)
{}

void LazyForEachNode::OnDataReloaded()
{
    ACE_SCOPED_TRACE("OnDataReloaded");
    children_.clear();
    if (builder_) {
        builder_->OnDataReloaded();
    }

    NotifyDataCountChanged(0);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataAdded(size_t index)
{
    ACE_SCOPED_TRACE("OnDataAdded");
    auto insertIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->OnDataAdded(index);
    }
    children_.clear();
    NotifyDataCountChanged(insertIndex);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataDeleted(size_t index)
{
    ACE_SCOPED_TRACE("OnDataDeleted");
    auto deletedIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->OnDataDeleted(index);
    }
    children_.clear();
    NotifyDataCountChanged(deletedIndex);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataChanged(size_t index)
{
    if (builder_) {
        builder_->OnDataChanged(index);
    }
    children_.clear();
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataMoved(size_t from, size_t to)
{
    // TODO: data move
}

void LazyForEachNode::NotifyDataCountChanged(int32_t index)
{
    auto parent = GetParent();
    if (parent) {
        parent->ChildrenUpdatedFrom(index);
    }
}

void LazyForEachNode::MarkNeedSyncRenderTree(bool needRebuild)
{
    if (needMarkParent_) {
        UINode::MarkNeedSyncRenderTree(needRebuild);
    }
}

RefPtr<UINode> LazyForEachNode::GetFrameChildByIndex(uint32_t index)
{
    if (index < FrameCount()) {
        auto child = builder_->CreateChildByIndex(index);
        if (child.second) {
            child.second->SetJSViewActive(true);
            if (child.second->GetDepth() != GetDepth() + 1) {
                child.second->SetDepth(GetDepth() + 1);
            }
            MarkNeedSyncRenderTree();
            children_.clear();
            child.second->SetParent(WeakClaim(this));
            if (IsOnMainTree()) {
                child.second->AttachToMainTree();
            }
            PostIdleTask();
            return child.second->GetFrameChildByIndex(0);
        }
    }
    return nullptr;
}

void LazyForEachNode::DoRemoveChildInRenderTree(uint32_t index, bool isAll)
{
    if (!builder_) {
        return;
    }
    ACE_SCOPED_TRACE("DoRemoveChildInRenderTree %u, %d", index, isAll);
    children_.clear();
    if (isAll) {
        builder_->RemoveAllChild();
        MarkNeedSyncRenderTree();
        PostIdleTask();
        return;
    }
    builder_->RemoveChildByIndex(index);
    MarkNeedSyncRenderTree();
    PostIdleTask();
}

const std::list<RefPtr<UINode>>& LazyForEachNode::GetChildren() const
{
    if (children_.empty()) {
        auto items = builder_->GetItems();
        int32_t startIndex = -1;
        int32_t endIndex = -1;
        if (!items.empty()) {
            for (const auto& item : items) {
                children_.push_back(item.second);
            }
            startIndex = items.begin()->first;
            endIndex = items.rbegin()->first;
        }
        if (startIndex != startIndex_ || endIndex != endIndex_) {
            startIndex_ = startIndex;
            endIndex_ = endIndex;
        }
    }
    return children_;
}

} // namespace OHOS::Ace::NG
