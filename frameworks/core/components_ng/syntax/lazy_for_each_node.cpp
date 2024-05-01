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

#include <utility>

#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
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
            TAG_LOGI(AceLogTag::ACE_LAZY_FOREACH, "replace old lazy for each builder");
            node->builder_ = forEachBuilder;
        }
        return node;
    }
    node = MakeRefPtr<LazyForEachNode>(nodeId, forEachBuilder);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

RefPtr<LazyForEachNode> LazyForEachNode::CreateLazyForEachNode(
    int32_t nodeId, const RefPtr<LazyForEachBuilder>& forEachBuilder)
{
    auto node = MakeRefPtr<LazyForEachNode>(nodeId, forEachBuilder);
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
    lazyLayoutWrapperBuilder->UpdateForceFlag(forceMeasure, forceLayout);
    parent->SetLayoutWrapperBuilder(lazyLayoutWrapperBuilder);
}

void LazyForEachNode::BuildAllChildren()
{
    for (int i = 0; i < FrameCount(); i++) {
        GetFrameChildByIndex(i, true);
    }
    children_.clear();
    auto items = builder_->GetAllChildren();
    for (auto& [index, item] : items) {
        if (item.second) {
            children_.push_back(item.second);
        }
    }
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
        ACE_SCOPED_TRACE("LazyForEach predict");
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->needPredict_ = false;
        auto canRunLongPredictTask = node->requestLongPredict_ && canUseLongPredictTask;
        if (node->builder_) {
            node->GetChildren();
            auto preBuildResult = node->builder_->PreBuild(deadline, node->itemConstraint_, canRunLongPredictTask);
            if (!preBuildResult) {
                node->PostIdleTask();
            } else {
                node->requestLongPredict_ = false;
                node->itemConstraint_.reset();
            }
        }
    });
}

void LazyForEachNode::OnDataReloaded()
{
    ACE_SCOPED_TRACE("OnDataReloaded");
    children_.clear();
    if (builder_) {
        builder_->SetUseNewInterface(false);
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
        builder_->SetUseNewInterface(false);
        builder_->OnDataAdded(index);
    }
    children_.clear();
    NotifyDataCountChanged(insertIndex);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataBulkAdded(size_t index, size_t count)
{
    ACE_SCOPED_TRACE("OnDataBulkAdded");
    auto insertIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataBulkAdded(index, count);
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
        builder_->SetUseNewInterface(false);
        auto node = builder_->OnDataDeleted(index);

        if (node) {
            if (!node->OnRemoveFromParent(true)) {
                const_cast<LazyForEachNode*>(this)->AddDisappearingChild(node);
            } else {
                node->DetachFromMainTree();
            }
            builder_->ProcessOffscreenNode(node, true);
        }
    }
    children_.clear();
    NotifyDataCountChanged(deletedIndex);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataBulkDeleted(size_t index, size_t count)
{
    ACE_SCOPED_TRACE("OnDataBulkDeleted");
    auto deletedIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        const auto& nodeList = builder_->OnDataBulkDeleted(index, count);
        for (const auto& node : nodeList) {
            if (node.second == nullptr) {
                continue;
            }
            if (!node.second->OnRemoveFromParent(true)) {
                const_cast<LazyForEachNode*>(this)->AddDisappearingChild(node.second);
            } else {
                node.second->DetachFromMainTree();
            }
            builder_->ProcessOffscreenNode(node.second, true);
            builder_->NotifyItemDeleted(RawPtr(node.second), node.first);
        }
        builder_->clearDeletedNodes();
    }
    children_.clear();
    NotifyDataCountChanged(deletedIndex);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataChanged(size_t index)
{
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataChanged(index);
    }
    children_.clear();
    NotifyDataCountChanged(static_cast<int32_t>(index));
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataBulkChanged(size_t index, size_t count)
{
    ACE_SCOPED_TRACE("OnDataBulkChanged");
    auto deletedIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        const auto& nodeList = builder_->OnDataBulkChanged(index, count);
        for (const auto& node : nodeList) {
            if (node.second == nullptr) {
                continue;
            }
            if (!node.second->OnRemoveFromParent(true)) {
                const_cast<LazyForEachNode*>(this)->AddDisappearingChild(node.second);
            } else {
                node.second->DetachFromMainTree();
            }
            builder_->ProcessOffscreenNode(node.second, true);
            builder_->NotifyItemDeleted(RawPtr(node.second), node.first);
        }
        builder_->clearDeletedNodes();
    }
    children_.clear();
    NotifyDataCountChanged(deletedIndex);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataMoveToNewPlace(size_t from, size_t to)
{
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataMoveToNewPlace(from, to);
    }
    children_.clear();
    NotifyDataCountChanged(static_cast<int32_t>(std::min(from, to)));
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataMoved(size_t from, size_t to)
{
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataMoved(from, to);
    }
    children_.clear();
    NotifyDataCountChanged(static_cast<int32_t>(std::min(from, to)));
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDatasetChange(const std::list<V2::Operation>& DataOperations)
{
    ACE_SCOPED_TRACE("OnDatasetChange");
    int32_t initialChangedIndex = 0;
    if (builder_) {
        builder_->SetUseNewInterface(true);
        std::pair<int32_t, std::list<RefPtr<UINode>>> pair = builder_->OnDatasetChange(DataOperations);
        initialChangedIndex = pair.first;
        std::list<RefPtr<UINode>> nodeList_ = pair.second;
        for (auto& node : nodeList_) {
            if (node == nullptr) {
                continue;
            }
            if (!node->OnRemoveFromParent(true)) {
                const_cast<LazyForEachNode*>(this)->AddDisappearingChild(node);
            } else {
                node->DetachFromMainTree();
            }
            builder_->ProcessOffscreenNode(node, true);
        }
        builder_->clearDeletedNodes();
    }
    children_.clear();
    NotifyDataCountChanged(initialChangedIndex);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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

RefPtr<UINode> LazyForEachNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    if (index >= static_cast<uint32_t>(FrameCount())) {
        return nullptr;
    }
    auto child = builder_->GetChildByIndex(index, needBuild, isCache);
    if (!child.second) {
        return nullptr;
    }
    if (isCache) {
        child.second->SetParent(WeakClaim(this));
        child.second->SetJSViewActive(false);
        return child.second->GetFrameChildByIndex(0, needBuild);
    }
    if (isActive_) {
        child.second->SetJSViewActive(true);
    }
    if (addToRenderTree) {
        child.second->SetActive(true);
    }
    if (child.second->GetDepth() != GetDepth() + 1) {
        child.second->SetDepth(GetDepth() + 1);
    }
    MarkNeedSyncRenderTree();
    children_.clear();
    child.second->SetParent(WeakClaim(this));
    if (IsOnMainTree()) {
        child.second->AttachToMainTree(false, GetContext());
    }
    PostIdleTask();
    auto childNode = child.second->GetFrameChildByIndex(0, needBuild);
    if (onMoveEvent_) {
        InitDragManager(AceType::DynamicCast<FrameNode>(childNode));
    }
    return childNode;
}

int32_t LazyForEachNode::GetIndexByUINode(const RefPtr<UINode>& uiNode) const
{
    if (!builder_) {
        return -1;
    }
    auto items = builder_->GetAllChildren();
    for (auto& [index, item] : items) {
        if (item.second == uiNode) {
            return index;
        }
    }
    return -1;
}

void LazyForEachNode::RecycleItems(int32_t from, int32_t to)
{
    if (!builder_) {
        return;
    }
    children_.clear();
    for (auto index = from; index < to; index++) {
        if (index >= startIndex_ && index < startIndex_ + count_) {
            builder_->RecordOutOfBoundaryNodes(index - startIndex_);
        }
    }
    PostIdleTask();
}

void LazyForEachNode::DoRemoveChildInRenderTree(uint32_t index, bool isAll)
{
    if (!builder_) {
        return;
    }
    children_.clear();
    if (isAll) {
        builder_->RemoveAllChild();
        MarkNeedSyncRenderTree();
        PostIdleTask();
    }
}

void LazyForEachNode::DoSetActiveChildRange(int32_t start, int32_t end)
{
    if (!builder_) {
        return;
    }
    if (builder_->SetActiveChildRange(start, end)) {
        children_.clear();
        MarkNeedSyncRenderTree();
        PostIdleTask();
    }
}

const std::list<RefPtr<UINode>>& LazyForEachNode::GetChildren() const
{
    if (children_.empty()) {
        std::list<std::pair<std::string, RefPtr<UINode>>> childList;
        const auto& items = builder_->GetItems(childList);

        for (auto& node : childList) {
            if (!node.second->OnRemoveFromParent(true)) {
                const_cast<LazyForEachNode*>(this)->AddDisappearingChild(node.second);
            } else {
                node.second->DetachFromMainTree();
            }
            builder_->NotifyItemDeleted(RawPtr(node.second), node.first);
        }
        for (const auto& [index, item] : items) {
            if (item.second) {
                const_cast<LazyForEachNode*>(this)->RemoveDisappearingChild(item.second);
                children_.push_back(item.second);
            }
        }
    }
    return children_;
}

void LazyForEachNode::OnConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    if ((configurationChange.colorModeUpdate || configurationChange.fontUpdate) && builder_) {
        auto map = builder_->GetCachedUINodeMap();
        for (auto& it : map) {
            auto node = DynamicCast<UINode>(it.second.second);
            if (node) {
                node->UpdateConfigurationUpdate(configurationChange);
            }
        }
    }
}

void LazyForEachNode::SetOnMove(std::function<void(int32_t, int32_t)>&& onMove)
{
    if (onMove && !onMoveEvent_) {
        InitAllChilrenDragManager(true);
    } else if (!onMove && onMoveEvent_) {
        InitAllChilrenDragManager(false);
    }
    onMoveEvent_ = onMove;
}

void LazyForEachNode::MoveData(int32_t from, int32_t to)
{
    if (builder_) {
        builder_->OnDataMoveToNewPlace(from, to);
    }
    children_.clear();
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

RefPtr<FrameNode> LazyForEachNode::GetFrameNode(int32_t index)
{
    CHECK_NULL_RETURN(builder_, nullptr);
    auto child = builder_->GetChildByIndex(index, false, false);
    CHECK_NULL_RETURN(child.second, nullptr);
    return AceType::DynamicCast<FrameNode>(child.second->GetFrameChildByIndex(0, true));
}
int32_t LazyForEachNode::GetFrameNodeIndex(RefPtr<FrameNode> node)
{
    CHECK_NULL_RETURN(builder_, -1);
    return builder_->GetChildIndex(node);
}
void LazyForEachNode::InitDragManager(const RefPtr<FrameNode>& childNode)
{
    CHECK_NULL_VOID(childNode);
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    auto pattern = childNode->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->InitDragManager(AceType::Claim(this));
}

void LazyForEachNode::InitAllChilrenDragManager(bool init)
{
    auto parentNode = GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    if (parentNode->GetTag() != V2::LIST_ETS_TAG) {
        return;
    }
    const auto& children = GetChildren();
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
        auto childNode = child->GetFrameChildByIndex(0, false);
        auto listItem = AceType::DynamicCast<FrameNode>(childNode);
        if (!listItem) {
            continue;
        }

        auto pattern = listItem->GetPattern<ListItemPattern>();
        if (!pattern) {
            continue;
        }
        if (init) {
            pattern->InitDragManager(AceType::Claim(this));
        } else {
            pattern->DeInitDragManager();
        }
    }
}
} // namespace OHOS::Ace::NG
