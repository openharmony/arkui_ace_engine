/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/ui_node.h"

#include <memory>

#include "base/geometry/ng/point_t.h"
#include "base/log/ace_checker.h"
#include "base/log/ace_performance_check.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

thread_local int64_t UINode::currentAccessibilityId_ = 0;

UINode::UINode(const std::string& tag, int32_t nodeId, bool isRoot)
    : tag_(tag), nodeId_(nodeId), accessibilityId_(currentAccessibilityId_++), isRoot_(isRoot)
{
    if (AceChecker::IsPerformanceCheckEnabled()) {
        auto pos = EngineHelper::GetPositionOnJsCode();
        nodeInfo_ = std::make_unique<PerformanceCheckNode>();
        nodeInfo_->codeRow = pos.first;
        nodeInfo_->codeCol = pos.second;
    }
#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        distributedUI->AddNewNode(nodeId_);
    } while (false);
#endif
    instanceId_ = Container::CurrentId();
    nodeStatus_ = ViewStackProcessor::GetInstance()->IsBuilderNode() ? NodeStatus::BUILDER_NODE_OFF_MAINTREE
                                                                     : NodeStatus::NORMAL_NODE;
}

UINode::~UINode()
{
#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        if (hostPageId_ == distributedUI->GetCurrentPageId()) {
            distributedUI->AddDeletedNode(nodeId_);
        }
    } while (false);
#endif

    if (!removeSilently_) {
        ElementRegister::GetInstance()->RemoveItem(nodeId_, tag_);
    } else {
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId_);
    }
    if (!onMainTree_) {
        return;
    }
    onMainTree_ = false;
    if (nodeStatus_ == NodeStatus::BUILDER_NODE_ON_MAINTREE) {
        nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;
    }
}

void UINode::AttachContext(PipelineContext* context, bool recursive)
{
    context_ = context;
    if (recursive) {
        for (auto& child : children_) {
            child->AttachContext(context, recursive);
        }
    }
}

void UINode::DetachContext(bool recursive)
{
    context_ = nullptr;
    if (recursive) {
        for (auto& child : children_) {
            child->DetachContext(recursive);
        }
    }
}

void UINode::AddChild(const RefPtr<UINode>& child, int32_t slot, bool silently, bool addDefaultTransition)
{
    CHECK_NULL_VOID(child);
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        return;
    }

    // remove from disappearing children
    RemoveDisappearingChild(child);
    it = children_.begin();
    std::advance(it, slot);
    DoAddChild(it, child, silently, addDefaultTransition);
}

void UINode::AddChildAfter(const RefPtr<UINode>& child, const RefPtr<UINode>& siblingNode)
{
    CHECK_NULL_VOID(child);
    CHECK_NULL_VOID(siblingNode);
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        LOGW("Child node already exists. Existing child nodeId %{public}d, add %{public}s child nodeId nodeId "
             "%{public}d",
            (*it)->GetId(), child->GetTag().c_str(), child->GetId());
        return;
    }
    // remove from disappearing children
    RemoveDisappearingChild(child);
    auto siblingNodeIter = std::find(children_.begin(), children_.end(), siblingNode);
    if (siblingNodeIter != children_.end()) {
        DoAddChild(++siblingNodeIter, child, false);
        return;
    }
    it = children_.begin();
    std::advance(it, -1);
    DoAddChild(it, child, false);
}

void UINode::AddChildBefore(const RefPtr<UINode>& child, const RefPtr<UINode>& siblingNode)
{
    CHECK_NULL_VOID(child);
    CHECK_NULL_VOID(siblingNode);
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        LOGW("Child node already exists. Existing child nodeId %{public}d, add %{public}s child nodeId nodeId "
             "%{public}d",
            (*it)->GetId(), child->GetTag().c_str(), child->GetId());
        return;
    }
    // remove from disappearing children
    RemoveDisappearingChild(child);
    auto siblingNodeIter = std::find(children_.begin(), children_.end(), siblingNode);
    if (siblingNodeIter != children_.end()) {
        DoAddChild(siblingNodeIter, child, false);
        return;
    }
    it = children_.begin();
    std::advance(it, -1);
    DoAddChild(it, child, false);
}

std::list<RefPtr<UINode>>::iterator UINode::RemoveChild(const RefPtr<UINode>& child, bool allowTransition)
{
    CHECK_NULL_RETURN(child, children_.end());

    auto iter = std::find(children_.begin(), children_.end(), child);
    if (iter == children_.end()) {
        return children_.end();
    }
    // If the child is undergoing a disappearing transition, rather than simply removing it, we should move it to the
    // disappearing children. This ensures that the child remains alive and the tree hierarchy is preserved until the
    // transition has finished. We can then perform the necessary cleanup after the transition is complete.
    if ((*iter)->OnRemoveFromParent(allowTransition)) {
        // OnRemoveFromParent returns true means the child can be removed from tree immediately.
        RemoveDisappearingChild(child);
    } else {
        // else move child into disappearing children, skip syncing render tree
        AddDisappearingChild(child, std::distance(children_.begin(), iter));
    }
    MarkNeedSyncRenderTree(true);
    auto result = children_.erase(iter);
    return result;
}

int32_t UINode::RemoveChildAndReturnIndex(const RefPtr<UINode>& child)
{
    auto result = RemoveChild(child);
    return std::distance(children_.begin(), result);
}

void UINode::RemoveChildAtIndex(int32_t index)
{
    auto children = GetChildren();
    if ((index < 0) || (index >= static_cast<int32_t>(children.size()))) {
        return;
    }
    auto iter = children.begin();
    std::advance(iter, index);
    RemoveChild(*iter);
}

RefPtr<UINode> UINode::GetChildAtIndex(int32_t index) const
{
    auto children = GetChildren();
    if ((index < 0) || (index >= static_cast<int32_t>(children.size()))) {
        return nullptr;
    }
    auto iter = children.begin();
    std::advance(iter, index);
    if (iter != children.end()) {
        return *iter;
    }
    return nullptr;
}

int32_t UINode::GetChildIndex(const RefPtr<UINode>& child) const
{
    int32_t index = 0;
    for (const auto& iter : GetChildren()) {
        if (iter == child) {
            return index;
        }
        index++;
    }
    return -1;
}

void UINode::ReplaceChild(const RefPtr<UINode>& oldNode, const RefPtr<UINode>& newNode)
{
    if (!oldNode) {
        if (newNode) {
            AddChild(newNode);
        }
        return;
    }

    auto iter = RemoveChild(oldNode);
    DoAddChild(iter, newNode, false, false);
}

void UINode::Clean(bool cleanDirectly, bool allowTransition)
{
    bool needSyncRenderTree = false;
    int32_t index = 0;
    for (const auto& child : children_) {
        // traverse down the child subtree to mark removing and find needs to hold subtree, if found add it to pending
        if (!cleanDirectly && child->MarkRemoving()) {
            ElementRegister::GetInstance()->AddPendingRemoveNode(child);
        }
        // If the child is undergoing a disappearing transition, rather than simply removing it, we should move it to
        // the disappearing children. This ensures that the child remains alive and the tree hierarchy is preserved
        // until the transition has finished. We can then perform the necessary cleanup after the transition is
        // complete.
        if (child->OnRemoveFromParent(allowTransition)) {
            // OnRemoveFromParent returns true means the child can be removed from tree immediately.
            RemoveDisappearingChild(child);
            needSyncRenderTree = true;
        } else {
            // else move child into disappearing children, skip syncing render tree
            AddDisappearingChild(child, index);
        }
        ++index;
    }
    if (tag_ != V2::JS_IF_ELSE_ETS_TAG) {
        children_.clear();
    }
    MarkNeedSyncRenderTree(true);
}

void UINode::MountToParent(const RefPtr<UINode>& parent, int32_t slot, bool silently, bool addDefaultTransition)
{
    CHECK_NULL_VOID(parent);
    parent->AddChild(AceType::Claim(this), slot, silently, addDefaultTransition);
    if (parent->IsInDestroying()) {
        parent->SetChildrenInDestroying();
    }
    if (parent->GetPageId() != 0) {
        SetHostPageId(parent->GetPageId());
    }
}

void UINode::UpdateConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    OnConfigurationUpdate(configurationChange);
    if (needCallChildrenUpdate_) {
        auto children = GetChildren();
        for (const auto& child : children) {
            if (!child) {
                continue;
            }
            child->UpdateConfigurationUpdate(configurationChange);
        }
    }
}

bool UINode::OnRemoveFromParent(bool allowTransition)
{
    // The recursive flag will used by RenderContext, if recursive flag is false,
    // it may trigger transition
    DetachFromMainTree(!allowTransition);
    if (allowTransition && !RemoveImmediately()) {
        return false;
    }
    ResetParent();
    return true;
}

void UINode::ResetParent()
{
    parent_.Reset();
    depth_ = -1;
}

void UINode::DoAddChild(
    std::list<RefPtr<UINode>>::iterator& it, const RefPtr<UINode>& child, bool silently, bool addDefaultTransition)
{
    children_.insert(it, child);

    child->SetParent(Claim(this));
    child->SetDepth(GetDepth() + 1);
    if (nodeStatus_ != NodeStatus::NORMAL_NODE) {
        child->UpdateNodeStatus(nodeStatus_);
    }

    if (!silently && onMainTree_) {
        child->AttachToMainTree(!addDefaultTransition, context_);
    }
    MarkNeedSyncRenderTree(true);
}

RefPtr<FrameNode> UINode::GetFocusParent() const
{
    auto parentUi = GetParent();
    while (parentUi) {
        auto parentFrame = AceType::DynamicCast<FrameNode>(parentUi);
        if (!parentFrame) {
            parentUi = parentUi->GetParent();
            continue;
        }
        auto type = parentFrame->GetFocusType();
        if (type == FocusType::SCOPE) {
            return parentFrame;
        }
        if (type == FocusType::NODE) {
            return nullptr;
        }
        parentUi = parentUi->GetParent();
    }
    return nullptr;
}

RefPtr<FocusHub> UINode::GetFirstFocusHubChild() const
{
    const auto* frameNode = AceType::DynamicCast<FrameNode>(this);
    if (frameNode) {
        auto focusHub = frameNode->GetFocusHub();
        if (focusHub && focusHub->GetFocusType() != FocusType::DISABLE) {
            return focusHub;
        }
    }
    for (const auto& child : GetChildren()) {
        auto focusHub = child->GetFirstFocusHubChild();
        if (focusHub) {
            return focusHub;
        }
    }
    return nullptr;
}

void UINode::GetFocusChildren(std::list<RefPtr<FrameNode>>& children) const
{
    auto uiChildren = GetChildren();
    for (const auto& uiChild : uiChildren) {
        auto frameChild = AceType::DynamicCast<FrameNode>(uiChild);
        if (frameChild && frameChild->GetFocusType() != FocusType::DISABLE) {
            children.emplace_back(frameChild);
        } else {
            uiChild->GetFocusChildren(children);
        }
    }
}

void UINode::GetChildrenFocusHub(std::list<RefPtr<FocusHub>>& focusNodes)
{
    for (const auto& uiChild : GetChildren()) {
        auto frameChild = AceType::DynamicCast<FrameNode>(uiChild.GetRawPtr());
        if (frameChild && frameChild->GetFocusType() != FocusType::DISABLE) {
            const auto focusHub = frameChild->GetFocusHub();
            if (focusHub) {
                focusNodes.emplace_back(focusHub);
            }
        } else {
            uiChild->GetChildrenFocusHub(focusNodes);
        }
    }
}

void UINode::AttachToMainTree(bool recursive, PipelineContext* context)
{
    if (onMainTree_) {
        return;
    }
    context_ = context;
    onMainTree_ = true;
    if (nodeStatus_ == NodeStatus::BUILDER_NODE_OFF_MAINTREE) {
        nodeStatus_ = NodeStatus::BUILDER_NODE_ON_MAINTREE;
    }
    isRemoving_ = false;
    OnAttachToMainTree(recursive);
    // if recursive = false, recursively call AttachToMainTree(false), until we reach the first FrameNode.
    bool isRecursive = recursive || AceType::InstanceOf<FrameNode>(this);
    for (const auto& child : GetChildren()) {
        child->AttachToMainTree(isRecursive, context);
    }
}

[[deprecated]] void UINode::AttachToMainTree(bool recursive)
{
    if (onMainTree_) {
        return;
    }
    onMainTree_ = true;
    if (nodeStatus_ == NodeStatus::BUILDER_NODE_OFF_MAINTREE) {
        nodeStatus_ = NodeStatus::BUILDER_NODE_ON_MAINTREE;
    }
    isRemoving_ = false;
    OnAttachToMainTree(recursive);
    // if recursive = false, recursively call AttachToMainTree(false), until we reach the first FrameNode.
    bool isRecursive = recursive || AceType::InstanceOf<FrameNode>(this);
    for (const auto& child : GetChildren()) {
        child->AttachToMainTree(isRecursive);
    }
}

void UINode::DetachFromMainTree(bool recursive)
{
    if (!onMainTree_) {
        return;
    }
    onMainTree_ = false;
    if (nodeStatus_ == NodeStatus::BUILDER_NODE_ON_MAINTREE) {
        nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;
    }
    isRemoving_ = true;
    context_ = nullptr;
    OnDetachFromMainTree(recursive);
    // if recursive = false, recursively call DetachFromMainTree(false), until we reach the first FrameNode.
    bool isRecursive = recursive || AceType::InstanceOf<FrameNode>(this);
    for (const auto& child : GetChildren()) {
        child->DetachFromMainTree(isRecursive);
    }
}

void UINode::ProcessOffscreenTask(bool recursive)
{
    if (useOffscreenProcess_) {
        return;
    }
    useOffscreenProcess_ = true;
    OnOffscreenProcess(recursive);
    // if recursive = false, recursively call AttachToMainTree(false), until we reach the first FrameNode.
    bool isRecursive = recursive || AceType::InstanceOf<FrameNode>(this);
    for (const auto& child : GetChildren()) {
        child->ProcessOffscreenTask(isRecursive);
    }
}

void UINode::MovePosition(int32_t slot)
{
    auto parentNode = parent_.Upgrade();
    CHECK_NULL_VOID(parentNode);

    auto self = AceType::Claim(this);
    auto& children = parentNode->children_;
    auto it = children.end();
    if (slot >= 0 && static_cast<size_t>(slot) < children.size()) {
        it = children.begin();
        std::advance(it, slot);
        if ((it != children.end()) && (*it == this)) {
            // Already at the right place
            return;
        }

        auto itSelf = std::find(it, children.end(), self);
        if (itSelf != children.end()) {
            children.erase(itSelf);
        } else {
            children.remove(self);
            ++it;
        }
    } else {
        children.remove(self);
    }
    children.insert(it, self);
    parentNode->MarkNeedSyncRenderTree(true);
}

void UINode::UpdateLayoutPropertyFlag()
{
    for (const auto& child : GetChildren()) {
        child->UpdateLayoutPropertyFlag();
    }
}

void UINode::AdjustParentLayoutFlag(PropertyChangeFlag& flag)
{
    for (const auto& child : GetChildren()) {
        child->AdjustParentLayoutFlag(flag);
    }
}

void UINode::MarkDirtyNode(PropertyChangeFlag extraFlag, bool childExpansiveAndMark)
{
    for (const auto& child : GetChildren()) {
        child->MarkDirtyNode(extraFlag, childExpansiveAndMark);
    }
}

void UINode::MarkNeedFrameFlushDirty(PropertyChangeFlag extraFlag)
{
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->MarkNeedFrameFlushDirty(extraFlag);
    }
}

void UINode::MarkNeedSyncRenderTree(bool needRebuild)
{
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->MarkNeedSyncRenderTree(needRebuild);
    }
}

void UINode::RebuildRenderContextTree()
{
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->RebuildRenderContextTree();
    }
}
void UINode::OnDetachFromMainTree(bool) {}

void UINode::OnAttachToMainTree(bool)
{
    useOffscreenProcess_ = false;
    decltype(attachToMainTreeTasks_) tasks(std::move(attachToMainTreeTasks_));
    for (const auto& task : tasks) {
        if (task) {
            task();
        }
    }
}

void UINode::DumpViewDataPageNodes(RefPtr<ViewDataWrap> viewDataWrap)
{
    DumpViewDataPageNode(viewDataWrap);
    for (const auto& item : GetChildren()) {
        item->DumpViewDataPageNodes(viewDataWrap);
    }
}

bool UINode::NeedRequestAutoSave()
{
    if (CheckAutoSave()) {
        return true;
    }
    for (const auto& item : GetChildren()) {
        if (item->NeedRequestAutoSave()) {
            return true;
        }
    }
    return false;
}

void UINode::DumpTree(int32_t depth)
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc("ID: " + std::to_string(nodeId_));
        DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(GetDepth())));
        DumpLog::GetInstance().AddDesc("InstanceId: " + std::to_string(instanceId_));
        DumpLog::GetInstance().AddDesc("AccessibilityId: " + std::to_string(accessibilityId_));
        if (IsDisappearing()) {
            DumpLog::GetInstance().AddDesc(std::string("IsDisappearing: ").append(std::to_string(IsDisappearing())));
        }
        DumpInfo();
        DumpLog::GetInstance().Append(depth, tag_, static_cast<int32_t>(GetChildren().size()));
    }
    for (const auto& item : GetChildren()) {
        item->DumpTree(depth + 1);
    }
    for (const auto& [item, index] : disappearingChildren_) {
        item->DumpTree(depth + 1);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(this);
    if (frameNode && frameNode->GetOverlayNode()) {
        frameNode->GetOverlayNode()->DumpTree(depth + 1);
    }
}

bool UINode::DumpTreeById(int32_t depth, const std::string& id)
{
    if (DumpLog::GetInstance().GetDumpFile() &&
        (id == propInspectorId_.value_or("") || id == std::to_string(nodeId_))) {
        DumpLog::GetInstance().AddDesc("ID: " + std::to_string(nodeId_));
        DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(GetDepth())));
        DumpLog::GetInstance().AddDesc(std::string("IsDisappearing: ").append(std::to_string(IsDisappearing())));
        DumpAdvanceInfo();
        DumpLog::GetInstance().Print(depth, tag_, static_cast<int32_t>(GetChildren().size()));
        return true;
    }
    for (const auto& item : GetChildren()) {
        if (item->DumpTreeById(depth + 1, id)) {
            return true;
        }
    }
    for (const auto& [item, index] : disappearingChildren_) {
        if (item->DumpTreeById(depth + 1, id)) {
            return true;
        }
    }
    return false;
}

void UINode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
{
    for (const auto& child : children_) {
        if (!child->IsInDestroying()) {
            child->AdjustLayoutWrapperTree(parent, forceMeasure, forceLayout);
        }
    }
}

void UINode::GenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
{
    for (const auto& child : GetChildren()) {
        child->OnGenerateOneDepthVisibleFrame(visibleList);
    }
}

void UINode::GenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList)
{
    if (disappearingChildren_.empty()) {
        // normal child
        for (const auto& child : GetChildren()) {
            child->OnGenerateOneDepthVisibleFrameWithTransition(visibleList);
        }
        return;
    }
    // generate the merged list of children_ and disappearingChildren_
    auto allChildren = GetChildren();
    for (auto iter = disappearingChildren_.rbegin(); iter != disappearingChildren_.rend(); ++iter) {
        auto& [disappearingChild, index] = *iter;
        if (index >= allChildren.size()) {
            allChildren.emplace_back(disappearingChild);
        } else {
            auto insertIter = allChildren.begin();
            std::advance(insertIter, index);
            allChildren.insert(insertIter, disappearingChild);
        }
    }
    for (const auto& child : allChildren) {
        child->OnGenerateOneDepthVisibleFrameWithTransition(visibleList);
    }
}

void UINode::GenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& visibleList)
{
    for (const auto& child : GetChildren()) {
        child->OnGenerateOneDepthAllFrame(visibleList);
    }
}

PipelineContext* UINode::GetContext()
{
    if (context_) {
        return context_;
    }
    return PipelineContext::GetCurrentContextPtrSafely();
}

RefPtr<PipelineContext> UINode::GetContextRefPtr()
{
    auto* context = GetContext();
    return Claim(context);
}

HitTestResult UINode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
    bool isDispatch)
{
    auto children = GetChildren();
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto hitResult =
            child->TouchTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result, touchId);
        if (hitResult == HitTestResult::STOP_BUBBLING) {
            return HitTestResult::STOP_BUBBLING;
        }
        if (hitResult == HitTestResult::BUBBLING) {
            hitTestResult = HitTestResult::BUBBLING;
        }
    }
    return hitTestResult;
}

HitTestResult UINode::MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    MouseTestResult& onMouseResult, MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode)
{
    auto children = GetChildren();
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto hitResult = child->MouseTest(globalPoint, parentLocalPoint, onMouseResult, onHoverResult, hoverNode);
        if (hitResult == HitTestResult::STOP_BUBBLING) {
            return HitTestResult::STOP_BUBBLING;
        }
        if (hitResult == HitTestResult::BUBBLING) {
            hitTestResult = HitTestResult::BUBBLING;
        }
    }
    return hitTestResult;
}

HitTestResult UINode::AxisTest(const PointF& globalPoint, const PointF& parentLocalPoint, AxisTestResult& onAxisResult)
{
    auto children = GetChildren();
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto hitResult = child->AxisTest(globalPoint, parentLocalPoint, onAxisResult);
        if (hitResult == HitTestResult::STOP_BUBBLING) {
            return HitTestResult::STOP_BUBBLING;
        }
        if (hitResult == HitTestResult::BUBBLING) {
            hitTestResult = HitTestResult::BUBBLING;
        }
    }
    return hitTestResult;
}

int32_t UINode::FrameCount() const
{
    return TotalChildCount();
}

int32_t UINode::TotalChildCount() const
{
    int32_t count = 0;
    for (const auto& child : GetChildren()) {
        count += child->FrameCount();
    }
    return count;
}

int32_t UINode::GetChildIndexById(int32_t id)
{
    int32_t pos = 0;
    auto children = GetChildren();
    auto iter = children.begin();
    while (iter != children.end()) {
        if (id == (*iter)->GetId()) {
            return pos;
        }
        pos++;
        iter++;
    }
    return -1;
}

RefPtr<LayoutWrapperNode> UINode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    if (GetChildren().empty()) {
        return nullptr;
    }

    auto child = GetChildren().front();
    while (!InstanceOf<FrameNode>(child)) {
        auto children = child->GetChildren();
        if (children.empty()) {
            return nullptr;
        }

        child = children.front();
    }

    auto frameChild = DynamicCast<FrameNode>(child);
    return frameChild ? frameChild->CreateLayoutWrapper(forceMeasure, forceLayout) : nullptr;
}

bool UINode::RenderCustomChild(int64_t deadline)
{
    for (const auto& child : GetChildren()) {
        if (child && !child->RenderCustomChild(deadline)) {
            return false;
        }
    }
    return true;
}

void UINode::Build(std::shared_ptr<std::list<ExtraInfo>> extraInfos)
{
    ACE_LAYOUT_SCOPED_TRACE("Build[%s][self:%d][parent:%d][key:%s]", GetTag().c_str(), GetId(),
        GetParent() ? GetParent()->GetId() : 0, GetInspectorIdValue("").c_str());
    for (const auto& child : GetChildren()) {
        if (InstanceOf<CustomNode>(child)) {
            auto custom = DynamicCast<CustomNode>(child);
            if (custom->HasExtraInfo()) {
                if (!extraInfos) {
                    extraInfos = std::make_shared<std::list<ExtraInfo>>();
                }
                extraInfos->emplace_front(custom->GetExtraInfo());
                custom->Build(extraInfos);
                extraInfos->pop_front();
            } else {
                custom->Build(extraInfos);
            }
        } else {
            child->Build(extraInfos);
        }
    }
}

void UINode::CreateExportTextureInfoIfNeeded()
{
    if (!exportTextureInfo_) {
        exportTextureInfo_ = MakeRefPtr<ExportTextureInfo>();
    }
}

bool UINode::IsNeedExportTexture() const
{
    return exportTextureInfo_ && exportTextureInfo_->GetCurrentRenderType() == NodeRenderType::RENDER_TYPE_TEXTURE;
}

void UINode::SetActive(bool active)
{
    for (const auto& child : GetChildren()) {
        child->SetActive(active);
    }
}

void UINode::SetJSViewActive(bool active)
{
    for (const auto& child : GetChildren()) {
        auto customNode = AceType::DynamicCast<CustomNode>(child);
        // do not need to recursive here, stateMgmt will recursive all children when set active
        if (customNode) {
            customNode->SetJSViewActive(active);
            return;
        }
        child->SetJSViewActive(active);
    }
}

void UINode::TryVisibleChangeOnDescendant(bool isVisible)
{
    UpdateChildrenVisible(isVisible);
}

void UINode::UpdateChildrenVisible(bool isVisible) const
{
    for (const auto& child : GetChildren()) {
        child->TryVisibleChangeOnDescendant(isVisible);
    }
}

void UINode::OnRecycle()
{
    for (const auto& child: GetChildren()) {
        child->OnRecycle();
    }
}

void UINode::OnReuse()
{
    for (const auto& child: GetChildren()) {
        child->OnReuse();
    }
}

std::pair<bool, int32_t> UINode::GetChildFlatIndex(int32_t id)
{
    if (GetId() == id) {
        return { true, 0 };
    }

    const auto& node = ElementRegister::GetInstance()->GetUINodeById(id);
    if (!node) {
        return { false, 0 };
    }

    if (node && (node->GetTag() == GetTag())) {
        return { false, 1 };
    }

    int32_t count = 0;
    for (const auto& child : GetChildren()) {
        auto res = child->GetChildFlatIndex(id);
        if (res.first) {
            return { true, count + res.second };
        }
        count += res.second;
    }
    return { false, count };
}

// for Grid refresh GridItems
void UINode::ChildrenUpdatedFrom(int32_t index)
{
    childrenUpdatedFrom_ = childrenUpdatedFrom_ >= 0 ? std::min(index, childrenUpdatedFrom_) : index;
}

bool UINode::MarkRemoving()
{
    bool pendingRemove = false;
    isRemoving_ = true;
    const auto& children = GetChildren();
    for (const auto& child : children) {
        pendingRemove = child->MarkRemoving() || pendingRemove;
    }
    return pendingRemove;
}

void UINode::SetChildrenInDestroying()
{
    auto children = GetChildren();
    if (children.empty()) {
        return;
    }

    for (const auto& child : children) {
        if (!child) {
            continue;
        }
        child->SetChildrenInDestroying();
        child->SetInDestroying();
    }
}

void UINode::AddDisappearingChild(const RefPtr<UINode>& child, uint32_t index)
{
    if (child->isDisappearing_) {
        // if child is already disappearing, remove it from disappearingChildren_ first
        auto it = std::find_if(disappearingChildren_.begin(), disappearingChildren_.end(),
            [child](const auto& pair) { return pair.first == child; });
        if (it != disappearingChildren_.end()) {
            disappearingChildren_.erase(it);
        }
    } else {
        // mark child as disappearing before adding to disappearingChildren_
        child->isDisappearing_ = true;
    }
    disappearingChildren_.emplace_back(child, index);
}

bool UINode::RemoveDisappearingChild(const RefPtr<UINode>& child)
{
    // quick reject
    if (!child->isDisappearing_) {
        return false;
    }
    auto it = std::find_if(disappearingChildren_.begin(), disappearingChildren_.end(),
        [child](const auto& pair) { return pair.first == child; });
    if (it == disappearingChildren_.end()) {
        return false;
    }
    disappearingChildren_.erase(it);
    child->isDisappearing_ = false;
    return true;
}

void UINode::OnGenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList)
{
    GenerateOneDepthVisibleFrameWithTransition(visibleList);
}

bool UINode::RemoveImmediately() const
{
    auto children = GetChildren();
    return std::all_of(
               children.begin(), children.end(), [](const auto& child) { return child->RemoveImmediately(); }) &&
           std::all_of(disappearingChildren_.begin(), disappearingChildren_.end(),
               [](const auto& pair) { return pair.first->RemoveImmediately(); });
}

void UINode::GetPerformanceCheckData(PerformanceCheckNodeMap& nodeMap)
{
    auto parent = GetParent();
    auto children = GetChildren();
    if (parent && parent->GetTag() == V2::JS_FOR_EACH_ETS_TAG) {
        // At this point, all of the children_
        // belong to the child nodes of syntaxItem
        for (const auto& child : children) {
            if (child->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
                auto grandChildren = child->GetChildren();
                if (!grandChildren.empty()) {
                    auto begin = grandChildren.begin();
                    (*begin)->SetForeachItem();
                }
            } else {
                child->SetForeachItem();
            }
        }
    }

    if (tag_ == V2::COMMON_VIEW_ETS_TAG) {
        if (!children.empty()) {
            auto begin = children.begin();
            nodeInfo_->nodeTag = (*begin)->GetCustomTag();
        }
    } else {
        nodeInfo_->nodeTag = GetCustomTag();
    }

    nodeInfo_->pageDepth = depth_;
    nodeInfo_->childrenSize = children.size();
    if (isBuildByJS_) {
        nodeMap.insert({ GetId(), *(nodeInfo_) });
    }
    for (const auto& child : children) {
        // Recursively traverse the child nodes of each node
        child->GetPerformanceCheckData(nodeMap);
    }
}

RefPtr<UINode> UINode::GetDisappearingChildById(const std::string& id) const
{
    if (id.empty()) {
        return nullptr;
    }
    for (auto& [node, index] : disappearingChildren_) {
        if (node->GetInspectorIdValue("") == id) {
            return node;
        }
    }
    return nullptr;
}

RefPtr<UINode> UINode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache)
{
    for (const auto& child : GetChildren()) {
        uint32_t count = static_cast<uint32_t>(child->FrameCount());
        if (count > index) {
            return child->GetFrameChildByIndex(index, needBuild, isCache);
        }
        index -= count;
    }
    return nullptr;
}

void UINode::DoRemoveChildInRenderTree(uint32_t index, bool isAll)
{
    if (isAll) {
        for (const auto& child : children_) {
            child->DoRemoveChildInRenderTree(index, isAll);
        }
        return;
    }
    for (const auto& child : children_) {
        uint32_t count = static_cast<uint32_t>(child->FrameCount());
        if (count > index) {
            return child->DoRemoveChildInRenderTree(index);
        }
        index -= count;
    }
}

void UINode::DoSetActiveChildRange(int32_t start, int32_t end)
{
    for (const auto& child : children_) {
        uint32_t count = static_cast<uint32_t>(child->FrameCount());
        child->DoSetActiveChildRange(start, end);
        start -= static_cast<int32_t>(count);
        end -= static_cast<int32_t>(count);
    }
}

void UINode::OnSetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint)
{
    for (const auto& child : GetChildren()) {
        child->OnSetCacheCount(cacheCount, itemConstraint);
    }
}

std::string UINode::GetCurrentCustomNodeInfo()
{
    auto parent = AceType::Claim(this);
    std::string extraInfo;
    while (parent) {
        if (InstanceOf<CustomNode>(parent)) {
            auto custom = DynamicCast<CustomNode>(parent);
            auto list = custom->GetExtraInfos();
            for (const auto& child : list) {
                extraInfo.append("    ").append("at (").append(child.page).append(":")
                    .append(std::to_string(child.line)).append(")\n");
            }
            break;
        }
        parent = parent->GetParent();
       
    }
    return extraInfo;
}

int64_t UINode::GenerateAccessibilityId()
{
    return currentAccessibilityId_++;
}

NodeStatus UINode::GetNodeStatus() const
{
    return nodeStatus_;
}

bool UINode::SetParentLayoutConstraint(const SizeF& size) const
{
    auto children = GetChildren();
    return std::any_of(children.begin(), children.end(),
        [size](const RefPtr<UINode>& child) { return child->SetParentLayoutConstraint(size); });
}

void UINode::UpdateNodeStatus(NodeStatus nodeStatus)
{
    nodeStatus_ = nodeStatus;
    for (const auto& child : children_) {
        if (child->GetNodeStatus() == nodeStatus_) {
            continue;
        }
        child->OnAttachToBuilderNode(nodeStatus_);
        child->UpdateNodeStatus(nodeStatus_);
    }
}

void UINode::SetIsRootBuilderNode(bool isRootBuilderNode)
{
    isRootBuilderNode_ = isRootBuilderNode;
}

bool UINode::GetIsRootBuilderNode() const
{
    return isRootBuilderNode_;
}

// Collects  all the child elements of "children" in a recursive manner
// Fills the "removedElmtId" list with the collected child elements
void UINode::CollectRemovedChildren(const std::list<RefPtr<UINode>>& children,
    std::list<int32_t>& removedElmtId, bool isEntry)
{
    for (auto const& child : children) {
        if (!child->IsDisappearing()) {
            CollectRemovedChild(child, removedElmtId);
        }
    }
    if (isEntry) {
        children_.clear();
    }
}

void UINode::CollectRemovedChild(const RefPtr<UINode>& child, std::list<int32_t>& removedElmtId)
{
    if (child->GetNodeStatus() != NodeStatus::NORMAL_NODE) {
        return;
    }
    removedElmtId.emplace_back(child->GetId());
    // Fetch all the child elementIDs recursively
    if (child->GetTag() != V2::JS_VIEW_ETS_TAG) {
        // add CustomNode but do not recurse into its children
        // add node create by BuilderNode do not recurse into its children
        CollectRemovedChildren(child->GetChildren(), removedElmtId, false);
    }
}

void UINode::PaintDebugBoundaryTreeAll(bool flag)
{
    PaintDebugBoundary(flag);
    for (const auto& child : GetChildren()) {
        child->PaintDebugBoundaryTreeAll(flag);
    }
}

void UINode::GetPageNodeCountAndDepth(int32_t* count, int32_t* depth)
{
    ACE_SCOPED_TRACE("GetPageNodeCountAndDepth");
    auto children = GetChildren();
    if (*depth < depth_) {
        *depth = depth_;
    }
    if (InstanceOf<FrameNode>(this)) {
        (*count)++;
    }

    for (const auto& child : children) {
        child->GetPageNodeCountAndDepth(count, depth);
    }
}

void UINode::DFSAllChild(const RefPtr<UINode>& root, std::vector<RefPtr<UINode>>& res)
{
    if (root->GetChildren().empty()) {
        res.emplace_back(root);
    }
    for (const auto& child : root->GetChildren()) {
        DFSAllChild(child, res);
    }
}

bool UINode::IsContextTransparent()
{
    for (const auto& item : GetChildren()) {
        if (!item->IsContextTransparent()) {
            return false;
        }
    }
    return true;
}

} // namespace OHOS::Ace::NG
