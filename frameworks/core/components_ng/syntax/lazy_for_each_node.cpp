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
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->needPredict_ = false;
        auto canRunLongPredictTask = node->requestLongPredict_ && canUseLongPredictTask;
        if (node->builder_) {
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
        auto node = builder_->OnDataDeleted(index);

        if (node) {
            if (!node->OnRemoveFromParent(true)) {
                const_cast<LazyForEachNode*>(this)->AddDisappearingChild(node);
            } else {
                node->DetachFromMainTree();
            }
        }
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
    if (builder_) {
        builder_->OnDataMoved(from, to);
    }
    children_.clear();
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

RefPtr<UINode> LazyForEachNode::GetFrameChildByIndex(uint32_t index, bool needBuild)
{
    if (index < static_cast<uint32_t>(FrameCount())) {
        auto child = builder_->GetChildByIndex(index, needBuild);
        if (child.second) {
            child.second->SetJSViewActive(true);
            if (child.second->GetDepth() != GetDepth() + 1) {
                child.second->SetDepth(GetDepth() + 1);
            }
            MarkNeedSyncRenderTree();
            children_.clear();
            child.second->SetParent(WeakClaim(this));
            child.second->SetHostPageId(GetPageId());
            if (IsOnMainTree()) {
                child.second->AttachToMainTree();
            }
            PostIdleTask();
            return child.second->GetFrameChildByIndex(0, needBuild);
        }
    }
    return nullptr;
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
    return;
}

const std::list<RefPtr<UINode>>& LazyForEachNode::GetChildren() const
{
    if (children_.empty()) {
        std::list<RefPtr<UINode>> childList;
        auto items = builder_->GetItems(childList);

        for (auto& node : childList) {
            if (!node->OnRemoveFromParent(true)) {
                const_cast<LazyForEachNode*>(this)->AddDisappearingChild(node);
            } else {
                node->DetachFromMainTree();
            }
        }
        for (auto& [index, item] : items) {
            if (item.second) {
                const_cast<LazyForEachNode*>(this)->RemoveDisappearingChild(item.second);
                children_.push_back(item.second);
            }
        }
    }
    return children_;
}

} // namespace OHOS::Ace::NG