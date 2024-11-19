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

#include "core/components_ng/pattern/list/list_item_pattern.h"
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
    node->RegisterBuilderListener();
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
    tempChildren_.clear();
    tempChildren_.swap(children_);
    auto items = builder_->GetAllChildren();
    for (auto& [index, item] : items) {
        if (item.second) {
            RemoveDisappearingChild(item.second);
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
    ACE_SCOPED_TRACE("LazyForEach OnDataReloaded");
    tempChildren_.clear();
    tempChildren_.swap(children_);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataReloaded();
        if (FrameCount() == 0) {
            PostIdleTask();
        }
    }
    NotifyChangeWithCount(0, 0, NotificationType::START_CHANGE_POSITION);
    NotifyChangeWithCount(static_cast<int32_t>(FrameCount()), 0, NotificationType::END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataAdded(size_t index)
{
    ACE_SCOPED_TRACE("LazyForEach OnDataAdded");
    auto insertIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataAdded(index);
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(insertIndex, 1, NotificationType::START_AND_END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataBulkAdded(size_t index, size_t count)
{
    ACE_SCOPED_TRACE("LazyForEach OnDataBulkAdded");
    auto insertIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataBulkAdded(index, count);
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(insertIndex, static_cast<int32_t>(count), NotificationType::START_AND_END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataDeleted(size_t index)
{
    ACE_SCOPED_TRACE("LazyForEach OnDataDeleted");
    auto deletedIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        auto node = builder_->OnDataDeleted(index);

        if (node) {
            if (!node->OnRemoveFromParent(true)) {
                AddDisappearingChild(node);
            } else {
                node->DetachFromMainTree();
            }
            builder_->ProcessOffscreenNode(node, true);
        }
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(deletedIndex, -1, NotificationType::START_AND_END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataBulkDeleted(size_t index, size_t count)
{
    ACE_SCOPED_TRACE("LazyForEach OnDataBulkDeleted");
    auto deletedIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        const auto& nodeList = builder_->OnDataBulkDeleted(index, count);
        for (const auto& node : nodeList) {
            if (node.second == nullptr) {
                continue;
            }
            if (!node.second->OnRemoveFromParent(true)) {
                AddDisappearingChild(node.second);
            } else {
                node.second->DetachFromMainTree();
            }
            builder_->ProcessOffscreenNode(node.second, true);
            builder_->NotifyItemDeleted(RawPtr(node.second), node.first);
        }
        builder_->clearDeletedNodes();
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(deletedIndex, -static_cast<int32_t>(count), NotificationType::START_AND_END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataChanged(size_t index)
{
    auto changedIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataChanged(index);
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(changedIndex, 0, NotificationType::START_AND_END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataBulkChanged(size_t index, size_t count)
{
    ACE_SCOPED_TRACE("LazyForEach OnDataBulkChanged");
    auto changedIndex = static_cast<int32_t>(index);
    if (builder_) {
        builder_->SetUseNewInterface(false);
        const auto& nodeList = builder_->OnDataBulkChanged(index, count);
        for (const auto& node : nodeList) {
            if (node.second == nullptr) {
                continue;
            }
            if (!node.second->OnRemoveFromParent(true)) {
                AddDisappearingChild(node.second);
            } else {
                node.second->DetachFromMainTree();
            }
            builder_->ProcessOffscreenNode(node.second, true);
            builder_->NotifyItemDeleted(RawPtr(node.second), node.first);
        }
        builder_->clearDeletedNodes();
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(changedIndex, 0, NotificationType::START_CHANGE_POSITION);
    NotifyChangeWithCount(changedIndex + static_cast<int32_t>(count) - 1, 0, NotificationType::END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataMoveToNewPlace(size_t from, size_t to)
{
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataMoveToNewPlace(from, to);
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(static_cast<int32_t>(std::min(from, to)), 0, NotificationType::START_CHANGE_POSITION);
    NotifyChangeWithCount(static_cast<int32_t>(std::max(from, to)), 0, NotificationType::END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDataMoved(size_t from, size_t to)
{
    if (builder_) {
        builder_->SetUseNewInterface(false);
        builder_->OnDataMoved(from, to);
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(static_cast<int32_t>(std::min(from, to)), 0, NotificationType::START_CHANGE_POSITION);
    NotifyChangeWithCount(static_cast<int32_t>(std::max(from, to)), 0, NotificationType::END_CHANGE_POSITION);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::OnDatasetChange(const std::list<V2::Operation>& DataOperations)
{
    ACE_SCOPED_TRACE("LazyForEach OnDatasetChange");
    int32_t initialChangedIndex = 0;
    if (builder_) {
        builder_->SetUseNewInterface(true);
        std::pair<int32_t, std::list<std::pair<std::string, RefPtr<UINode>>>> pair =
            builder_->OnDatasetChange(DataOperations);
        initialChangedIndex = pair.first;
        std::list<std::pair<std::string, RefPtr<UINode>>> nodeList = pair.second;
        for (const auto& node : nodeList) {
            if (node.second == nullptr) {
                continue;
            }
            if (!node.second->OnRemoveFromParent(true)) {
                AddDisappearingChild(node.second);
            } else {
                node.second->DetachFromMainTree();
            }
            builder_->ProcessOffscreenNode(node.second, true);
        }
        builder_->clearDeletedNodes();
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    NotifyChangeWithCount(initialChangedIndex, 0, NotificationType::START_CHANGE_POSITION);
    ParseOperations(DataOperations);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::MarkNeedSyncRenderTree(bool needRebuild)
{
    if (needMarkParent_) {
        UINode::MarkNeedSyncRenderTree(needRebuild);
    }
}

RefPtr<UINode> LazyForEachNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    ACE_SYNTAX_SCOPED_TRACE("LazyForEach.GetFrameChildByIndex index[%d] needBuild[%d] isCache[%d] addToRenderTree[%d]",
        static_cast<int32_t>(index), static_cast<int32_t>(needBuild),
        static_cast<int32_t>(isCache), static_cast<int32_t>(addToRenderTree));
    if (index >= static_cast<uint32_t>(FrameCount())) {
        return nullptr;
    }
    auto child = builder_->GetChildByIndex(index, needBuild, isCache);
    if (!child.second) {
        return nullptr;
    }
    if (isCache) {
        child.second->SetParent(WeakClaim(this));
        child.second->SetJSViewActive(false, true);
        return child.second->GetFrameChildByIndex(0, needBuild);
    }
    if (isActive_) {
        child.second->SetJSViewActive(true, true);
    }
    if (addToRenderTree) {
        child.second->SetActive(true);
    }
    if (child.second->GetDepth() != GetDepth() + 1) {
        child.second->SetDepth(GetDepth() + 1);
    }
    MarkNeedSyncRenderTree();
    tempChildren_.clear();
    tempChildren_.swap(children_);
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
    tempChildren_.clear();
    tempChildren_.swap(children_);
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
    tempChildren_.clear();
    tempChildren_.swap(children_);
    if (isAll) {
        builder_->RemoveAllChild();
        MarkNeedSyncRenderTree();
        PostIdleTask();
    }
}

void LazyForEachNode::DoSetActiveChildRange(
    int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    if (!builder_) {
        return;
    }
    if (showCache) {
        start -= cacheStart;
        end += cacheEnd;
        builder_->SetShowCached(cacheStart, cacheEnd);
    }
    if (builder_->SetActiveChildRange(start, end)) {
        tempChildren_.clear();
        tempChildren_.swap(children_);
        MarkNeedSyncRenderTree();
        PostIdleTask();
    }
}

const std::list<RefPtr<UINode>>& LazyForEachNode::GetChildren(bool notDetach) const
{
    if (children_.empty()) {
        LoadChildren(notDetach);

        // if measure not done, return previous children
        if (notDetach && children_.empty()) {
            return tempChildren_;
        }

        tempChildren_.clear();
    }
    return children_;
}

void LazyForEachNode::UpdateChildrenFreezeState(bool isFreeze, bool isForceUpdateFreezeVaule)
{
    if (!builder_) {
        return;
    }
    std::vector<UINode*> children;
    builder_->GetAllItems(children);
    for (const auto& child : children) {
        if (child) {
            child->SetFreeze(isFreeze);
        }
    }
}

void LazyForEachNode::LoadChildren(bool notDetach) const
{
    ACE_SYNTAX_SCOPED_TRACE("LazyForEach.LoadChildren notDetach[%d]", static_cast<int32_t>(notDetach));
    std::list<std::pair<std::string, RefPtr<UINode>>> childList;
    const auto& items = builder_->GetItems(childList);

    if (!notDetach) {
        for (auto& node : childList) {
            if (!node.second->OnRemoveFromParent(true)) {
                const_cast<LazyForEachNode*>(this)->AddDisappearingChild(node.second);
            } else {
                node.second->DetachFromMainTree();
            }
        }
    }

    for (const auto& [index, item] : items) {
        if (item.second) {
            const_cast<LazyForEachNode*>(this)->RemoveDisappearingChild(item.second);
            children_.push_back(item.second);
        }
    }
}

void LazyForEachNode::OnConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    if (configurationChange.IsNeedUpdate() && builder_) {
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
        builder_->UpdateMoveFromTo(from, to);
    }
    tempChildren_.clear();
    tempChildren_.swap(children_);
    MarkNeedSyncRenderTree(true);
    MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void LazyForEachNode::FireOnMove(int32_t from, int32_t to)
{
    if (builder_) {
        builder_->ResetMoveFromTo();
    }
    ForEachBaseNode::FireOnMove(from, to);
}

RefPtr<FrameNode> LazyForEachNode::GetFrameNode(int32_t index)
{
    CHECK_NULL_RETURN(builder_, nullptr);
    auto child = builder_->GetChildByIndex(index, false, false);
    CHECK_NULL_RETURN(child.second, nullptr);
    return AceType::DynamicCast<FrameNode>(child.second->GetFrameChildByIndex(0, true));
}

int32_t LazyForEachNode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded)
{
    if (!isExpanded) {
        return UINode::GetFrameNodeIndex(node, false);
    }
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

void LazyForEachNode::NotifyChangeWithCount(int32_t index, int32_t count, NotificationType notificationType) const
{
    auto parent = GetParent();
    int64_t accessibilityId = GetAccessibilityId();
    if (parent) {
        parent->NotifyChange(index, count, accessibilityId, notificationType);
    }
}

void LazyForEachNode::ParseOperations(const std::list<V2::Operation>& dataOperations)
{
    std::map<std::string, int32_t> operationTypeMap = { { "add", 1 }, { "delete", 2 }, { "change", 3 }, { "move", 4 },
        { "exchange", 5 }, { "reload", 6 } };
    constexpr int ADDOP = 1;
    constexpr int DELETEOP = 2;
    constexpr int CHANGEOP = 3;
    constexpr int MOVEOP = 4;
    constexpr int EXCHANGEOP = 5;
    constexpr int RELOADOP = 6;
    for (const auto& operation : dataOperations) {
        switch (operationTypeMap[operation.type]) {
            case ADDOP:
                NotifyChangeWithCount(operation.index, operation.count, NotificationType::END_CHANGE_POSITION);
                break;
            case DELETEOP:
                NotifyChangeWithCount(operation.index, -operation.count, NotificationType::END_CHANGE_POSITION);
                break;
            case CHANGEOP:
                NotifyChangeWithCount(operation.index + operation.count - 1, 0, NotificationType::END_CHANGE_POSITION);
                break;
            case MOVEOP:
                NotifyChangeWithCount(std::max(operation.coupleIndex.first, operation.coupleIndex.second), 0,
                    NotificationType::END_CHANGE_POSITION);
                break;
            case EXCHANGEOP:
                NotifyChangeWithCount(operation.coupleIndex.second, 0, NotificationType::END_CHANGE_POSITION);
                break;
            case RELOADOP:
                NotifyChangeWithCount(static_cast<int32_t>(FrameCount()), 0, NotificationType::END_CHANGE_POSITION);
                break;
        }
    }
}
} // namespace OHOS::Ace::NG
