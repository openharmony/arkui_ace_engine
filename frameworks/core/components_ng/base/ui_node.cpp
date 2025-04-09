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

#include "base/log/ace_checker.h"
#include "base/log/dump_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/token_theme/token_theme_storage.h"

namespace OHOS::Ace::NG {

thread_local int64_t currentAccessibilityId_ = 0;
const std::set<std::string> UINode::layoutTags_ = { "Flex", "Stack", "Row", "Column", "WindowScene", "root",
    "__Common__", "Swiper", "Grid", "GridItem", "page", "stage", "FormComponent", "Tabs", "TabContent" };

UINode::UINode(const std::string& tag, int32_t nodeId, bool isRoot)
    : tag_(tag), nodeId_(nodeId), accessibilityId_(currentAccessibilityId_++), isRoot_(isRoot)
{
    if (AceChecker::IsPerformanceCheckEnabled()) {
        auto pos = EngineHelper::GetPositionOnJsCode();
        nodeInfo_ = std::make_unique<PerformanceCheckNode>();
        nodeInfo_->codeRow = pos.first;
        nodeInfo_->codeCol = pos.second;
    }
    apiVersion_ = Container::GetCurrentApiTargetVersion();
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
        ElementRegister::GetInstance()->RemoveItem(nodeId_);
    } else {
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId_);
    }
    if (propInspectorId_.has_value()) {
        ElementRegister::GetInstance()->RemoveFrameNodeByInspectorId(propInspectorId_.value_or(""), nodeId_);
    }
    if (!onMainTree_) {
        return;
    }
    if (context_) {
        context_->RemoveAttachedNode(this);
    }
    onMainTree_ = false;
    if (nodeStatus_ == NodeStatus::BUILDER_NODE_ON_MAINTREE) {
        nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;
    }
}

void UINode::AttachContext(PipelineContext* context, bool recursive)
{
    CHECK_NULL_VOID(context);
    context_ = context;
    context_->RegisterAttachedNode(this);
    instanceId_ = context->GetInstanceId();
    if (updateJSInstanceCallback_) {
        updateJSInstanceCallback_(instanceId_);
    }
    if (recursive) {
        for (auto& child : children_) {
            child->AttachContext(context, recursive);
        }
    }
}

void UINode::DetachContext(bool recursive)
{
    CHECK_NULL_VOID(context_);
    context_->DetachNode(Claim(this));
    context_ = nullptr;
    instanceId_ = INSTANCE_ID_UNDEFINED;
    if (recursive) {
        for (auto& child : children_) {
            child->DetachContext(recursive);
        }
    }
}

void UINode::AddChild(const RefPtr<UINode>& child, int32_t slot,
    bool silently, bool addDefaultTransition, bool addModalUiextension)
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
    if (!addModalUiextension && modalUiextensionCount_ > 0) {
        bool canAddChild = CanAddChildWhenTopNodeIsModalUec(it);
        if (!canAddChild) {
            LOGW("Current Node(id: %{public}d) is prohibited add child(tag %{public}s, id: %{public}d), "
                "Current modalUiextension count is : %{public}d",
                GetId(), child->GetTag().c_str(), child->GetId(), modalUiextensionCount_);
            return;
        } else {
            LOGI("Child(tag %{public}s, id: %{public}d) must under modalUec, which count is: %{public}d",
                child->GetTag().c_str(), child->GetId(), modalUiextensionCount_);
        }
    }
    DoAddChild(it, child, silently, addDefaultTransition);
}

bool UINode::CanAddChildWhenTopNodeIsModalUec(std::list<RefPtr<UINode>>::iterator& curIter)
{
    if (children_.empty()) {
        return true;
    }

    auto preIter = curIter;
    preIter--;
    // Gernerally, uiContent instance is allowwd to have multiple modalUecs.
    // Therefore, need to check all modalUec's isAllowAddChildBelowModalUec.
    while (preIter != children_.begin()) {
        if (preIter == children_.end()) {
            break;
        }

        if ((*preIter)->GetTag() != V2::MODAL_PAGE_TAG) {
            break;
        }

        if (!(*preIter)->IsAllowAddChildBelowModalUec()) {
            return false;
        }

        curIter--;
        preIter--;
    }

    return true;
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

void UINode::TraversingCheck(RefPtr<UINode> node, bool withAbort)
{
    if (!isTraversing_) {
        return;
    }

    if (withAbort) {
        if (node) {
            LOGF_ABORT("Try to remove the child([%{public}s][%{public}d]) of "
                "node [%{public}s][%{public}d] when its children is traversing",
                node->GetTag().c_str(), node->GetId(), GetTag().c_str(), GetId());
        } else {
            LOGF_ABORT("Try to remove all the children of "
                "node [%{public}s][%{public}d] when its children is traversing",
                GetTag().c_str(), GetId());
        }
    }

    if (node) {
        LOGE("Try to remove the child([%{public}s][%{public}d]) of "
            "node [%{public}s][%{public}d] when its children is traversing",
            node->GetTag().c_str(), node->GetId(), GetTag().c_str(), GetId());
    } else {
        LOGE("Try to remove all the children of "
            "node [%{public}s][%{public}d] when its children is traversing",
            GetTag().c_str(), GetId());
    }
    LogBacktrace();
}

std::list<RefPtr<UINode>>::iterator UINode::RemoveChild(const RefPtr<UINode>& child, bool allowTransition)
{
    CHECK_NULL_RETURN(child, children_.end());

    auto iter = std::find(children_.begin(), children_.end(), child);
    if (iter == children_.end()) {
        return children_.end();
    }

    // the node set isInDestroying state when destroying in pop animation
    // when in isInDestroying state node should not DetachFromMainTree preventing pop page from being white
    if (IsDestroyingState()) {
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
    // Iter maybe lost in OnRemoveFromParent, needs reacquire.
    iter = std::find(children_.begin(), children_.end(), child);
    if (iter == children_.end()) {
        LOGW("Iter is qeual to children end");
        return children_.end();
    }
    TraversingCheck(*iter);
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
    auto& children = GetChildren();
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

void UINode::Clean(bool cleanDirectly, bool allowTransition, int32_t branchId)
{
    bool needSyncRenderTree = false;
    int32_t index = 0;

    auto children = GetChildren();
    for (const auto& child : children) {
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
            AddDisappearingChild(child, index, branchId);
        }
        ++index;
    }

    if (tag_ != V2::JS_IF_ELSE_ETS_TAG) {
        children_.clear();
    }
    MarkNeedSyncRenderTree(true);
}

void UINode::MountToParent(const RefPtr<UINode>& parent,
    int32_t slot, bool silently, bool addDefaultTransition, bool addModalUiextension)
{
    CHECK_NULL_VOID(parent);
    parent->AddChild(AceType::Claim(this), slot, silently, addDefaultTransition, addModalUiextension);
    if (parent->IsInDestroying()) {
        parent->SetChildrenInDestroying();
    }
    if (parent->GetPageId() != 0) {
        SetHostPageId(parent->GetPageId());
    }
    AfterMountToParent();
}

void UINode::MountToParentAfter(const RefPtr<UINode>& parent, const RefPtr<UINode>& siblingNode)
{
    CHECK_NULL_VOID(parent);
    parent->AddChildAfter(AceType::Claim(this), siblingNode);
    if (parent->IsInDestroying()) {
        parent->SetChildrenInDestroying();
    }
    if (parent->GetPageId() != 0) {
        SetHostPageId(parent->GetPageId());
    }
    AfterMountToParent();
}

void UINode::MountToParentBefore(const RefPtr<UINode>& parent, const RefPtr<UINode>& siblingNode)
{
    CHECK_NULL_VOID(parent);
    parent->AddChildBefore(AceType::Claim(this), siblingNode);
    if (parent->IsInDestroying()) {
        parent->SetChildrenInDestroying();
    }
    if (parent->GetPageId() != 0) {
        SetHostPageId(parent->GetPageId());
    }
    AfterMountToParent();
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
    if (IsDestroyingState()) {
        return false;
    }
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
    UpdateThemeScopeId(0);
}

namespace {
std::ostream& operator<<(std::ostream& ss, const RefPtr<UINode>& node)
{
    return ss << node->GetId() << "(" << node->GetTag() << "," << node->GetDepth()
        << "," << node->GetChildren().size() << ")";
}

std::string ToString(const RefPtr<UINode>& node)
{
    std::stringstream ss;
    ss << node;
    for (auto parent = node->GetParent(); parent; parent = parent->GetParent()) {
        ss << "->" << parent;
    }
    return ss.str();
}

void LoopDetected(const RefPtr<UINode>& child, const RefPtr<UINode>& current)
{
    auto childNode = ToString(child);
    auto currentNode = ToString(current);

    constexpr size_t totalLengthLimit = 900; // hilog oneline length limit is 1024
    constexpr size_t childLengthLimit = 100;
    static_assert(totalLengthLimit > childLengthLimit, "totalLengthLimit too small");
    constexpr size_t currentLengthLimit = totalLengthLimit - childLengthLimit;

    // log full childNode info in case of hilog length limit reached
    if (childNode.length() > childLengthLimit) {
        auto s = childNode.c_str();
        for (size_t i = 0; i < childNode.length(); i += totalLengthLimit) {
            LOGI("child.%{public}zu:[%{public}.*s]", i, (int)totalLengthLimit, s + i);
        }
    }

    // log full currentNode info in case of hilog length limit reached
    if (currentNode.length() > currentLengthLimit) {
        auto s = currentNode.c_str();
        for (size_t i = 0; i < currentNode.length(); i += totalLengthLimit) {
            LOGI("current.%{public}zu:[%{public}.*s]", i, (int)totalLengthLimit, s + i);
        }
    }

    if (SystemProperties::GetLayoutDetectEnabled()) {
        LOGF_ABORT("LoopDetected: child[%{public}.*s] vs current[%{public}.*s]",
            (int)childLengthLimit, childNode.c_str(), (int)currentLengthLimit, currentNode.c_str());
    } else {
        LOGE("LoopDetected: child[%{public}.*s] vs current[%{public}.*s]",
            (int)childLengthLimit, childNode.c_str(), (int)currentLengthLimit, currentNode.c_str());
        LogBacktrace();
    }
}

bool DetectLoop(const RefPtr<UINode>& child, const RefPtr<UINode>& current)
{
    if ((child->GetDepth() > 0 && child->GetDepth() < INT32_MAX) || child == current) {
        for (auto parent = current; parent; parent = parent->GetParent()) {
            if (parent == child) {
                LoopDetected(child, current);
                return true;
            }
        }
    }
    return false;
}
}

void UINode::DoAddChild(
    std::list<RefPtr<UINode>>::iterator& it, const RefPtr<UINode>& child, bool silently, bool addDefaultTransition)
{
    if (DetectLoop(child, Claim(this))) {
        return;
    }
    children_.insert(it, child);

    if (IsAccessibilityVirtualNode()) {
        auto parentVirtualNode = GetVirtualNodeParent().Upgrade();
        if (parentVirtualNode) {
            child->SetAccessibilityNodeVirtual();
            child->SetAccessibilityVirtualNodeParent(parentVirtualNode);
        }
    }

    child->SetParent(Claim(this), false);
    auto themeScopeId = GetThemeScopeId();
    if (child->IsAllowUseParentTheme() && child->GetThemeScopeId() != themeScopeId) {
        child->UpdateThemeScopeId(themeScopeId);
    }
    child->SetDepth(GetDepth() + 1);
    if (nodeStatus_ != NodeStatus::NORMAL_NODE) {
        child->UpdateNodeStatus(nodeStatus_);
    }

    if (!silently && onMainTree_) {
        child->AttachToMainTree(!addDefaultTransition, context_);
    }
    MarkNeedSyncRenderTree(true);
    ProcessIsInDestroyingForReuseableNode(child);
}

void UINode::GetBestBreakPoint(RefPtr<UINode>& breakPointChild, RefPtr<UINode>& breakPointParent)
{
    while (breakPointParent && !breakPointChild->IsDisappearing()) {
        // recursively looking up the node tree, until we reach the breaking point (IsDisappearing() == true).
        // Because when trigger transition, only the breakPoint will be marked as disappearing and
        // moved to disappearingChildren.
        breakPointChild = breakPointParent;
        breakPointParent = breakPointParent->GetParent();
    }
    RefPtr<UINode> betterChild = breakPointChild;
    RefPtr<UINode> betterParent = breakPointParent;
    // when current breakPointParent is UINode, looking up the node tree to see whether there is a better breakPoint.
    while (betterParent && !InstanceOf<FrameNode>(betterParent)) {
        if (betterChild->IsDisappearing()) {
            if (!betterChild->RemoveImmediately()) {
                break;
            }
            breakPointChild = betterChild;
            breakPointParent = betterParent;
        }
        betterChild = betterParent;
        betterParent = betterParent->GetParent();
    }
}

void UINode::RemoveFromParentCleanly(const RefPtr<UINode>& child, const RefPtr<UINode>& parent)
{
    if (!parent->RemoveDisappearingChild(child)) {
        auto& children = parent->ModifyChildren();
        auto iter = std::find(children.begin(), children.end(), child);
        if (iter != children.end()) {
            parent->TraversingCheck(*iter);
            children.erase(iter);
        }
    }
    auto frameChild = DynamicCast<FrameNode>(child);
    if (frameChild->GetRenderContext()->HasTransitionOutAnimation()) {
        // delete the real breakPoint.
        RefPtr<UINode> breakPointChild = child;
        RefPtr<UINode> breakPointParent = parent;
        GetBestBreakPoint(breakPointChild, breakPointParent);
        if (breakPointParent && breakPointChild->RemoveImmediately()) {
            // Result of RemoveImmediately of the breakPointChild is true and
            // result of RemoveImmediately of the child is false,
            // so breakPointChild must be different from child in this branch.
            breakPointParent->RemoveDisappearingChild(breakPointChild);
            breakPointParent->MarkNeedSyncRenderTree();
        }
    }
}

RefPtr<FrameNode> UINode::GetParentFrameNode() const
{
    auto parent = GetParent();
    while (parent) {
        auto parentFrame = AceType::DynamicCast<FrameNode>(parent);
        if (parentFrame) {
            return parentFrame;
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

RefPtr<CustomNode> UINode::GetParentCustomNode() const
{
    auto parent = GetParent();
    while (parent) {
        auto customNode = AceType::DynamicCast<CustomNode>(parent);
        if (customNode) {
            return customNode;
        }
        parent = parent->GetParent();
    }
    return nullptr;
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

RefPtr<FrameNode> UINode::GetFocusParentWithBoundary() const
{
    auto parentUi = GetParent();
    while (parentUi) {
        if (parentUi->GetTag() == V2::SCREEN_ETS_TAG) {
            return nullptr;
        }
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

void UINode::GetCurrentChildrenFocusHub(std::list<RefPtr<FocusHub>>& focusNodes)
{
    for (const auto& uiChild : children_) {
        auto frameChild = AceType::DynamicCast<FrameNode>(Referenced::RawPtr(uiChild));
        if (frameChild && frameChild->GetFocusType() != FocusType::DISABLE) {
            const auto focusHub = frameChild->GetFocusHub();
            if (focusHub) {
                focusNodes.emplace_back(focusHub);
            }
        } else {
            uiChild->GetCurrentChildrenFocusHub(focusNodes);
        }
    }
}

void UINode::AttachToMainTree(bool recursive, PipelineContext* context)
{
    if (onMainTree_) {
        return;
    }
    // the context should not be nullptr.
    AttachContext(context, false);
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
    if (context && context->IsOpenInvisibleFreeze()) {
        auto parent = GetParent();
        // if it does not has parent, reset the flag.
        SetFreeze(parent ? parent->isFreeze_ : false);
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
    if (IsDestroyingState()) {
        return;
    }
    onMainTree_ = false;
    if (nodeStatus_ == NodeStatus::BUILDER_NODE_ON_MAINTREE) {
        nodeStatus_ = NodeStatus::BUILDER_NODE_OFF_MAINTREE;
    }
    isRemoving_ = true;
    auto context = context_;
    DetachContext(false);
    OnDetachFromMainTree(recursive, context);
    // if recursive = false, recursively call DetachFromMainTree(false), until we reach the first FrameNode.
    bool isRecursive = recursive || AceType::InstanceOf<FrameNode>(this);
    isTraversing_ = true;
    std::list<RefPtr<UINode>> children = GetChildren();
    for (const auto& child : children) {
        child->DetachFromMainTree(isRecursive);
    }
    isTraversing_ = false;
}

void UINode::SetUserFreeze(bool isUserFreeze)
{
    userFreeze_ = isUserFreeze;
}

bool UINode::IsUserFreeze()
{
    return userFreeze_.has_value() && userFreeze_.value();
}

void UINode::SetFreeze(bool isFreeze, bool isForceUpdateFreezeVaule, bool isUserFreeze)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    if (isUserFreeze) {
        SetUserFreeze(isUserFreeze);
    } else if (IsUserFreeze()) {
        return;
    }

    auto isNeedUpdateFreezeVaule = context->IsOpenInvisibleFreeze() || isForceUpdateFreezeVaule;
    if (isNeedUpdateFreezeVaule && isFreeze_ != isFreeze) {
        isFreeze_ = isFreeze;
        OnFreezeStateChange();
        UpdateChildrenFreezeState(isFreeze_, isForceUpdateFreezeVaule);
    }
}

void UINode::UpdateChildrenFreezeState(bool isFreeze, bool isForceUpdateFreezeVaule)
{
    const auto& children = GetChildren(true);
    for (const auto& child : children) {
        if (child) {
            child->SetFreeze(isFreeze, isForceUpdateFreezeVaule);
        }
    }
}

void UINode::FireCustomDisappear()
{
    std::list<RefPtr<UINode>> children = GetChildren();
    for (const auto& child : children) {
        child->FireCustomDisappear();
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
            parentNode->TraversingCheck(*itSelf);
            children.erase(itSelf);
        } else {
            parentNode->TraversingCheck(self);
            children.remove(self);
            ++it;
        }
    } else {
        parentNode->TraversingCheck(self);
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

void UINode::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    for (const auto& child : GetChildren()) {
        child->MarkDirtyNode(extraFlag);
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
void UINode::OnDetachFromMainTree(bool, PipelineContext*) {}

void UINode::OnAttachToMainTree(bool)
{
    useOffscreenProcess_ = false;
}

void UINode::UpdateGeometryTransition()
{
    auto children = GetChildren();
    for (const auto& child: children) {
        child->UpdateGeometryTransition();
    }
}

bool UINode::IsAutoFillContainerNode()
{
    return tag_ == V2::PAGE_ETS_TAG || tag_ == V2::NAVDESTINATION_VIEW_ETS_TAG || tag_ == V2::DIALOG_ETS_TAG
        || tag_ == V2::SHEET_PAGE_TAG || tag_ == V2::MODAL_PAGE_TAG || tag_ == V2::POPUP_ETS_TAG;
}

void UINode::DumpViewDataPageNodes(
    RefPtr<ViewDataWrap> viewDataWrap, bool skipSubAutoFillContainer, bool needsRecordData)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(this);
    if (frameNode && !frameNode->IsVisible()) {
        auto pattern = frameNode->GetPattern();
        if (pattern && !pattern->TriggerAutoSaveWhenInvisible()) {
            return;
        }
    }
    DumpViewDataPageNode(viewDataWrap, needsRecordData);
    for (const auto& item : GetChildren()) {
        if (!item) {
            continue;
        }
        if (skipSubAutoFillContainer && item->IsAutoFillContainerNode()) {
            continue;
        }
        item->DumpViewDataPageNodes(viewDataWrap, skipSubAutoFillContainer, needsRecordData);
    }
}

bool UINode::NeedRequestAutoSave()
{
    auto frameNode = AceType::DynamicCast<FrameNode>(this);
    if (frameNode && !frameNode->IsVisible()) {
        auto pattern = frameNode->GetPattern();
        if (pattern && !pattern->TriggerAutoSaveWhenInvisible()) {
            return false;
        }
    }
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

void UINode::DumpTree(int32_t depth, bool hasJson)
{
    if (hasJson) {
        std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
        std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
        children->Put("childSize", static_cast<int32_t>(GetChildren().size()));
        children->Put("ID", nodeId_);
        children->Put("Depth", GetDepth());
        children->Put("InstanceId", instanceId_);
        children->Put("AccessibilityId", accessibilityId_);
        if (IsDisappearing()) {
            children->Put("IsDisappearing", IsDisappearing());
        }
        DumpInfo(children);
        std::string key = isRoot_ ? tag_ : tag_ + "_" + std::to_string(nodeId_);
        json->Put(key.c_str(), children);
        std::string jsonstr = DumpLog::GetInstance().FormatDumpInfo(json->ToString(), depth);
        auto prefix = DumpLog::GetInstance().GetPrefix(depth);
        DumpLog::GetInstance().Append(prefix + jsonstr);
    } else {
        if (DumpLog::GetInstance().GetDumpFile()) {
            DumpLog::GetInstance().AddDesc("ID: " + std::to_string(nodeId_));
            DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(GetDepth())));
            DumpLog::GetInstance().AddDesc("InstanceId: " + std::to_string(instanceId_));
            DumpLog::GetInstance().AddDesc("AccessibilityId: " + std::to_string(accessibilityId_));
            if (IsDisappearing()) {
                DumpLog::GetInstance().AddDesc(
                    std::string("IsDisappearing: ").append(std::to_string(IsDisappearing())));
            }
            DumpInfo();
            DumpLog::GetInstance().Append(depth, tag_, static_cast<int32_t>(GetChildren().size()));
        }
    }
    if (!CheckVisibleOrActive()) {
        return;
    }
    for (const auto& item : GetChildren()) {
        item->DumpTree(depth + 1, hasJson);
    }
    for (const auto& [item, index, branch] : disappearingChildren_) {
        item->DumpTree(depth + 1, hasJson);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(this);
    if (frameNode && frameNode->GetOverlayNode()) {
        frameNode->GetOverlayNode()->DumpTree(depth + 1, hasJson);
    }
}

void UINode::DumpTreeJsonForDiff(std::unique_ptr<JsonValue>& json)
{
    auto currentNode = JsonUtil::Create(true);
    auto childrenNodeArray = JsonUtil::CreateArray(true);
    auto children = GetChildren();
    currentNode->Put("childSize", static_cast<int32_t>(children.size()));
    currentNode->Put("ID", nodeId_);
    currentNode->Put("Depth", GetDepth());
    currentNode->Put("InstanceId", instanceId_);
    currentNode->Put("AccessibilityId", accessibilityId_);
    if (IsDisappearing()) {
        currentNode->Put("IsDisappearing", IsDisappearing());
    }
    DumpInfo(currentNode);
    for (auto& child : children) {
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(child);
        if (frameNode && layoutTags_.find(frameNode->GetTag()) != layoutTags_.end() && !frameNode->IsActive()) {
            continue;
        }
        auto childNode = JsonUtil::Create(true);
        child->DumpTreeJsonForDiff(childNode);
        childrenNodeArray->PutRef(std::move(childNode));
    }
    currentNode->PutRef("children", std::move(childrenNodeArray));
    std::string key = isRoot_ ? tag_ : tag_ + "_" + std::to_string(nodeId_);
    json->PutRef(key.c_str(), std::move(currentNode));
}

void UINode::DumpSimplifyTree(int32_t depth, std::unique_ptr<JsonValue>& current)
{
    current->Put("$type", tag_.c_str());
    current->Put("$ID", nodeId_);
    if (InstanceOf<CustomNode>(this)) {
        current->Put("type", "custom");
    } else {
        current->Put("type", "build-in");
    }
    auto nodeChildren = GetChildren();
    DumpSimplifyInfo(current);
    if (!CheckVisibleOrActive()) {
        return;
    }
    bool hasChildren = !nodeChildren.empty() || !disappearingChildren_.empty();
    if (hasChildren) {
        auto array = JsonUtil::CreateArray();
        if (!nodeChildren.empty()) {
            for (const auto& item : nodeChildren) {
                auto child = JsonUtil::Create();
                item->DumpSimplifyTree(depth + 1, child);
                array->PutRef(std::move(child));
            }
        }
        if (!disappearingChildren_.empty()) {
            for (const auto& [item, index, branch] : disappearingChildren_) {
                auto child = JsonUtil::Create();
                item->DumpSimplifyTree(depth + 1, child);
                array->PutRef(std::move(child));
            }
        }
        current->PutRef("$children", std::move(array));
    }
}

bool UINode::DumpTreeById(int32_t depth, const std::string& id, bool hasJson)
{
    if (hasJson) {
        if ((id == propInspectorId_.value_or("") || id == std::to_string(nodeId_))) {
            std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
            std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
            children->Put("childSize", static_cast<int32_t>(GetChildren().size()));
            children->Put("ID", nodeId_);
            children->Put("Depth", GetDepth());
            children->Put("IsDisappearing", IsDisappearing());
            DumpAdvanceInfo(children);
            json->Put(tag_.c_str(), children);
            DumpLog::GetInstance().PrintJson(json->ToString());
            return true;
        }
    } else {
        if (DumpLog::GetInstance().GetDumpFile() &&
            (id == propInspectorId_.value_or("") || id == std::to_string(nodeId_))) {
            DumpLog::GetInstance().AddDesc("ID: " + std::to_string(nodeId_));
            DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(GetDepth())));
            DumpLog::GetInstance().AddDesc(std::string("IsDisappearing: ").append(std::to_string(IsDisappearing())));
            DumpAdvanceInfo();
            DumpLog::GetInstance().Print(depth, tag_, static_cast<int32_t>(GetChildren().size()));
            return true;
        }
    }
    for (const auto& item : GetChildren()) {
        if (item->DumpTreeById(depth + 1, id, hasJson)) {
            return true;
        }
    }
    for (const auto& [item, index, branch] : disappearingChildren_) {
        if (item->DumpTreeById(depth + 1, id, hasJson)) {
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
        auto& [disappearingChild, index, _] = *iter;
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

void UINode::GenerateOneDepthVisibleFrameWithOffset(
    std::list<RefPtr<FrameNode>>& visibleList, OffsetF& offset)
{
    if (disappearingChildren_.empty()) {
        // normal child
        for (const auto& child : GetChildren()) {
            child->OnGenerateOneDepthVisibleFrameWithOffset(visibleList, offset);
        }
        return;
    }
    // generate the merged list of children_ and disappearingChildren_
    auto allChildren = GetChildren();
    for (auto iter = disappearingChildren_.rbegin(); iter != disappearingChildren_.rend(); ++iter) {
        auto& [disappearingChild, index, _] = *iter;
        if (index >= allChildren.size()) {
            allChildren.emplace_back(disappearingChild);
        } else {
            auto insertIter = allChildren.begin();
            std::advance(insertIter, index);
            allChildren.insert(insertIter, disappearingChild);
        }
    }
    for (const auto& child : allChildren) {
        child->OnGenerateOneDepthVisibleFrameWithOffset(visibleList, offset);
    }
}

void UINode::GenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& visibleList)
{
    for (const auto& child : GetChildren()) {
        child->OnGenerateOneDepthAllFrame(visibleList);
    }
}

PipelineContext* UINode::GetContext() const
{
    PipelineContext* context = nullptr;
    if (context_) {
        context = context_;
    } else {
        if (externalData_) {
            context = PipelineContext::GetCurrentContextPtrSafelyWithCheck();
        } else {
            context = PipelineContext::GetCurrentContextPtrSafely();
        }
    }
    return context;
}

PipelineContext* UINode::GetAttachedContext() const
{
    return context_;
}

PipelineContext* UINode::GetContextWithCheck()
{
    if (context_) {
        return context_;
    }
    return PipelineContext::GetCurrentContextPtrSafelyWithCheck();
}

RefPtr<PipelineContext> UINode::GetContextRefPtr() const
{
    auto* context = GetContext();
    return Claim(context);
}

HitTestResult UINode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
    ResponseLinkResult& responseLinkResult, bool isDispatch)
{
    auto children = GetChildren();
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto hitResult = child->TouchTest(
            globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result, touchId, responseLinkResult);
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

HitTestResult UINode::AxisTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, AxisTestResult& onAxisResult)
{
    auto children = GetChildren();
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto hitResult = child->AxisTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, onAxisResult);
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

int32_t UINode::CurrentFrameCount() const
{
    int32_t count = 0;
    for (const auto& child : GetChildren()) {
        count += child->CurrentFrameCount();
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
    ACE_LAYOUT_TRACE_BEGIN("Build[%s][self:%d][parent:%d][key:%s]", GetTag().c_str(), GetId(),
        GetParent() ? GetParent()->GetId() : 0, GetInspectorIdValue("").c_str());
    std::vector<RefPtr<UINode>> children;
    children.reserve(GetChildren().size());
    for (const auto& child : GetChildren()) {
        children.push_back(child);
    }
    for (const auto& child : children) {
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
    ACE_LAYOUT_TRACE_END()
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

void UINode::SetActive(bool active, bool needRebuildRenderContext)
{
    for (const auto& child : GetChildren()) {
        child->SetActive(active, needRebuildRenderContext);
    }
}

void UINode::SetJSViewActive(bool active, bool isLazyForEachNode, bool isReuse)
{
    for (const auto& child : GetChildren()) {
        auto customNode = AceType::DynamicCast<CustomNode>(child);
        // do not need to recursive here, stateMgmt will recursive all children when set active
        if (customNode && customNode->GetIsV2() && isLazyForEachNode) {
            return;
        }
        if (customNode) {
            customNode->SetJSViewActive(active, isLazyForEachNode, isReuse);
            continue;
        }
        child->SetJSViewActive(active, isLazyForEachNode, isReuse);
    }
}

void UINode::TryVisibleChangeOnDescendant(VisibleType preVisibility, VisibleType currentVisibility)
{
    UpdateChildrenVisible(preVisibility, currentVisibility);
}

void UINode::UpdateChildrenVisible(VisibleType preVisibility, VisibleType currentVisibility) const
{
    for (const auto& child : GetChildren()) {
        child->TryVisibleChangeOnDescendant(preVisibility, currentVisibility);
    }
}

void UINode::OnRecycle()
{
    for (const auto& child : GetChildren(true)) {
        child->OnRecycle();
    }
}

void UINode::OnReuse()
{
    for (const auto& child : GetChildren(true)) {
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

bool UINode::MarkRemoving()
{
    bool pendingRemove = false;
    isRemoving_ = true;
    const auto children = GetChildren();
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

void UINode::AddDisappearingChild(const RefPtr<UINode>& child, uint32_t index, int32_t branchId)
{
    if (child->isDisappearing_) {
        // if child is already disappearing, remove it from disappearingChildren_ first
        auto it = std::find_if(disappearingChildren_.begin(), disappearingChildren_.end(),
            [child](const auto& tup) { return std::get<0>(tup) == child; });
        if (it != disappearingChildren_.end()) {
            disappearingChildren_.erase(it);
        }
    } else {
        // mark child as disappearing before adding to disappearingChildren_
        child->isDisappearing_ = true;
    }
    if (DetectLoop(child, Claim(this))) {
        return;
    }
    disappearingChildren_.emplace_back(child, index, branchId);
}

bool UINode::RemoveDisappearingChild(const RefPtr<UINode>& child)
{
    // quick reject
    if (!child->isDisappearing_) {
        return false;
    }
    auto it = std::find_if(disappearingChildren_.begin(), disappearingChildren_.end(),
        [child](const auto& tup) { return std::get<0>(tup) == child; });
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

void UINode::OnGenerateOneDepthVisibleFrameWithOffset(
    std::list<RefPtr<FrameNode>>& visibleList, OffsetF& offset)
{
    GenerateOneDepthVisibleFrameWithOffset(visibleList, offset);
}

bool UINode::RemoveImmediately() const
{
    auto children = GetChildren();
    return std::all_of(
               children.begin(), children.end(), [](const auto& child) { return child->RemoveImmediately(); }) &&
           std::all_of(disappearingChildren_.begin(), disappearingChildren_.end(),
               [](const auto& tup) { return std::get<0>(tup)->RemoveImmediately(); });
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

RefPtr<UINode> UINode::GetDisappearingChildById(const std::string& id, int32_t branchId) const
{
    if (id.empty()) {
        return nullptr;
    }
    for (auto& [node, index, branch] : disappearingChildren_) {
        if (node->GetInspectorIdValue("") == id && branch == branchId) {
            return node;
        }
    }
    return nullptr;
}

RefPtr<UINode> UINode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    for (const auto& child : GetChildren()) {
        uint32_t count = static_cast<uint32_t>(child->FrameCount());
        if (count > index) {
            return child->GetFrameChildByIndex(index, needBuild, isCache, addToRenderTree);
        }
        index -= count;
    }
    return nullptr;
}

RefPtr<UINode> UINode::GetFrameChildByIndexWithoutExpanded(uint32_t index)
{
    for (const auto& child : GetChildren()) {
        uint32_t count = static_cast<uint32_t>(child->CurrentFrameCount());
        if (count > index) {
            return child->GetFrameChildByIndexWithoutExpanded(index);
        }
        index -= count;
    }
    return nullptr;
}

int32_t UINode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded)
{
    int32_t index = 0;
    for (const auto& child : GetChildren()) {
        if (InstanceOf<FrameNode>(child)) {
            if (child == node) {
                return index;
            } else {
                index++;
                continue;
            }
        }
        int32_t childIndex = child->GetFrameNodeIndex(node, isExpanded);
        if (childIndex >= 0) {
            return index + childIndex;
        }
        index += isExpanded ? child->FrameCount() : child->CurrentFrameCount();
    }
    return -1;
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

void UINode::DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    for (const auto& child : children_) {
        uint32_t count = static_cast<uint32_t>(child->FrameCount());
        child->DoSetActiveChildRange(start, end, cacheStart, cacheEnd, showCache);
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
                extraInfo.append("    ")
                    .append("at (")
                    .append(child.page)
                    .append(":")
                    .append(std::to_string(child.line))
                    .append(":")
                    .append(std::to_string(child.col))
                    .append(")\n");
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
    if (nodeStatus_ == nodeStatus) {
        return;
    }
    nodeStatus_ = nodeStatus;
    OnAttachToBuilderNode(nodeStatus_);
    for (const auto& child : children_) {
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
// Fills the "removedElmtId" list and the "reservedElmtId" list with the collected child elements
void UINode::CollectCleanedChildren(const std::list<RefPtr<UINode>>& children, std::list<int32_t>& removedElmtId,
    std::list<int32_t>& reservedElmtId, bool isEntry)
{
    auto greatOrEqualApi13 = GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN);
    for (auto const& child : children) {
        bool needByTransition = child->IsDisappearing();
        if (greatOrEqualApi13) {
            needByTransition = isEntry && child->IsDisappearing() && child->GetInspectorIdValue("") != "";
        }

        if (!needByTransition && child->GetTag() != V2::RECYCLE_VIEW_ETS_TAG && !child->GetIsRootBuilderNode()) {
            removedElmtId.emplace_back(child->GetId());
            if (child->GetTag() != V2::JS_VIEW_ETS_TAG) {
                CollectCleanedChildren(child->GetChildren(), removedElmtId, reservedElmtId, false);
            }
        } else if (needByTransition && greatOrEqualApi13) {
            child->CollectReservedChildren(reservedElmtId);
        }
    }
    if (isEntry) {
        children_.clear();
    }
}

void UINode::CollectReservedChildren(std::list<int32_t>& reservedElmtId)
{
    reservedElmtId.emplace_back(GetId());
    if (GetTag() == V2::JS_VIEW_ETS_TAG) {
        SetJSViewActive(false);
    } else {
        for (auto const& child : GetChildren()) {
            child->CollectReservedChildren(reservedElmtId);
        }
    }
}

// Collects  all the child elements of "children" in a recursive manner
// Fills the "removedElmtId" list with the collected child elements
void UINode::CollectRemovedChildren(const std::list<RefPtr<UINode>>& children,
    std::list<int32_t>& removedElmtId, bool isEntry)
{
    auto greatOrEqualApi13 = GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN);
    for (auto const& child : children) {
        bool needByTransition = child->IsDisappearing();
        if (greatOrEqualApi13) {
            needByTransition = isEntry && child->IsDisappearing() && child->GetInspectorIdValue("") != "";
        }
        if (!needByTransition && child->GetTag() != V2::RECYCLE_VIEW_ETS_TAG && !child->GetIsRootBuilderNode()) {
            CollectRemovedChild(child, removedElmtId);
        }
    }
    if (isEntry) {
        children_.clear();
    }
}

void UINode::CollectRemovedChild(const RefPtr<UINode>& child, std::list<int32_t>& removedElmtId)
{
    removedElmtId.emplace_back(child->GetId());
    child->OnCollectRemoved();
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

void UINode::GetInspectorValue()
{
    for (const auto& item : GetChildren()) {
        item->GetInspectorValue();
    }
}

void UINode::ClearSubtreeLayoutAlgorithm(bool includeSelf, bool clearEntireTree)
{
    for (const auto& child : GetChildren()) {
        child->ClearSubtreeLayoutAlgorithm(includeSelf, clearEntireTree);
    }
}

void UINode::NotifyWebPattern(bool isRegister)
{
    for (const auto& item : GetChildren()) {
        item->NotifyWebPattern(isRegister);
    }
}

void UINode::GetContainerComponentText(std::u16string& text)
{
    for (const auto& child : GetChildren()) {
        if (InstanceOf<FrameNode>(child) && child->GetTag() == V2::TEXT_ETS_TAG) {
            auto frameChild = DynamicCast<FrameNode>(child);
            auto pattern = frameChild->GetPattern();
            CHECK_NULL_VOID(pattern);
            auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            text = layoutProperty->GetContent().value_or(u"");
            break;
        }
        child->GetContainerComponentText(text);
    }
}

int32_t UINode::CalcAbsPosition(int32_t changeIdx, int64_t id) const
{
    int32_t updateFrom = 0;
    for (const auto& child : GetChildren()) {
        if (child->GetAccessibilityId() == id) {
            updateFrom += changeIdx;
            break;
        }
        int32_t count = child->FrameCount();
        updateFrom += count;
    }
    return updateFrom;
}

void UINode::NotifyChange(int32_t changeIdx, int32_t count, int64_t id, NotificationType notificationType)
{
    int32_t updateFrom = CalcAbsPosition(changeIdx, id);
    auto accessibilityId = GetAccessibilityId();
    auto parent = GetParent();
    if (parent) {
        parent->NotifyChange(updateFrom, count, accessibilityId, notificationType);
    }
}

void UINode::SetParent(const WeakPtr<UINode>& parent, bool needDetect)
{
    auto current = parent.Upgrade();
    CHECK_NULL_VOID(current);
    if (needDetect && DetectLoop(Claim(this), current)) {
        return;
    }
    parent_ = parent;
}

int32_t UINode::GetThemeScopeId() const
{
    return themeScopeId_;
}

void UINode::SetThemeScopeId(int32_t themeScopeId)
{
    LOGD("WithTheme SetThemeScopeId %{public}d", themeScopeId);
    themeScopeId_ = themeScopeId;
    auto children = GetChildren();
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
        child->SetThemeScopeId(themeScopeId);
    }
}

void UINode::UpdateThemeScopeId(int32_t themeScopeId)
{
    if (GetThemeScopeId() == themeScopeId) {
        return;
    }
    LOGD("WithTheme UpdateThemeScopeId old:%{public}d new:%{public}d", GetThemeScopeId(), themeScopeId);
    themeScopeId_ = themeScopeId;
    OnThemeScopeUpdate(themeScopeId);
    auto children = GetChildren();
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
        child->UpdateThemeScopeId(themeScopeId);
    }
}

void UINode::UpdateThemeScopeUpdate(int32_t themeScopeId)
{
    if (GetThemeScopeId() != themeScopeId) {
        return;
    }
    OnThemeScopeUpdate(themeScopeId);
    if (needCallChildrenUpdate_) {
        auto children = GetChildren();
        for (const auto& child : children) {
            if (!child) {
                continue;
            }
            child->UpdateThemeScopeUpdate(themeScopeId);
        }
    }
}

void UINode::AllowUseParentTheme(bool isAllow)
{
    isAllowUseParentTheme_ = isAllow;
}

bool UINode::IsAllowUseParentTheme() const
{
    return isAllowUseParentTheme_;
}

ColorMode UINode::GetLocalColorMode() const
{
    auto theme = TokenThemeStorage::GetInstance()->GetTheme(GetThemeScopeId());
    return theme ? theme->GetColorMode() : ColorMode::COLOR_MODE_UNDEFINED;
}

void UINode::SetAllowReusableV2Descendant(bool allow)
{
    allowReusableV2Descendant_ = allow;
}

bool UINode::IsAllowReusableV2Descendant() const
{
    return allowReusableV2Descendant_;
}

void UINode::SetDestroying(bool isDestroying, bool cleanStatus)
{
    if (isInDestroying_ == isDestroying) {
        return;
    }

    isInDestroying_ = isDestroying;
    for (const auto& child : GetChildren()) {
        if (child->IsReusableNode()) {
            child->SetDestroying(isDestroying, false);
        } else {
            child->SetDestroying(isDestroying, cleanStatus);
        }
    }
    // add customnode to pipiline when state change, destroy them next vsync
    OnDestroyingStateChange(isDestroying, cleanStatus);
}

bool UINode::HasSkipNode()
{
    for (const auto& child : children_) {
        if (child->GetTag() == V2::WEB_ETS_TAG) {
            return true;
        }

        if (child->HasSkipNode()) {
            return true;
        }
    }
    return false;
}

void UINode::ProcessIsInDestroyingForReuseableNode(const RefPtr<UINode>& child)
{
    if (!child || !child->IsReusableNode()) {
        return;
    }
    if (!IsInDestroying() && child->IsInDestroying()) {
        child->SetDestroying(false, false);
    }
}

bool UINode::GreatOrEqualAPITargetVersion(PlatformVersion version) const
{
    if (!context_ || context_->GetApiTargetVersion() == 0) {
        return apiVersion_ >= static_cast<int32_t>(version);
    }
    return context_->GreatOrEqualAPITargetVersion(version);
}

bool UINode::LessThanAPITargetVersion(PlatformVersion version) const
{
    if (!context_ || context_->GetApiTargetVersion() == 0) {
        return apiVersion_ < static_cast<int32_t>(version);
    }
    return context_->LessThanAPITargetVersion(version);
}
} // namespace OHOS::Ace::NG
