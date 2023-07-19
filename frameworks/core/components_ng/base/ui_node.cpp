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

#include "core/components_ng/base/ui_node.h"

#include "base/geometry/ng/point_t.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

thread_local int32_t UINode::currentAccessibilityId_ = 0;

UINode::~UINode()
{
    if (!removeSilently_) {
        ElementRegister::GetInstance()->RemoveItem(nodeId_);
    } else {
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId_);
    }
    if (!onMainTree_) {
        return;
    }
    onMainTree_ = false;
}

void UINode::AddChild(const RefPtr<UINode>& child, int32_t slot, bool silently)
{
    CHECK_NULL_VOID(child);
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        LOGW("Child node already exists. Existing child nodeId %{public}d, add. child nodeId nodeId %{public}d",
            (*it)->GetId(), child->GetId());
        return;
    }

    it = children_.begin();
    std::advance(it, slot);
    DoAddChild(it, child, silently);
}

std::list<RefPtr<UINode>>::iterator UINode::RemoveChild(const RefPtr<UINode>& child)
{
    CHECK_NULL_RETURN(child, children_.end());

    auto iter = std::find(children_.begin(), children_.end(), child);
    if (iter == children_.end()) {
        LOGE("child is not exist.");
        return children_.end();
    }
    (*iter)->OnRemoveFromParent();
    auto result = children_.erase(iter);
    MarkNeedSyncRenderTree();
    return result;
}

int32_t UINode::RemoveChildAndReturnIndex(const RefPtr<UINode>& child)
{
    auto result = RemoveChild(child);
    return std::distance(children_.begin(), result);
}

void UINode::RemoveChildAtIndex(int32_t index)
{
    if ((index < 0) || (index >= static_cast<int32_t>(children_.size()))) {
        return;
    }
    auto iter = children_.begin();
    std::advance(iter, index);
    (*iter)->OnRemoveFromParent();
    children_.erase(iter);
    MarkNeedSyncRenderTree();
}

RefPtr<UINode> UINode::GetChildAtIndex(int32_t index) const
{
    if ((index < 0) || (index >= static_cast<int32_t>(children_.size()))) {
        return nullptr;
    }
    auto iter = children_.begin();
    std::advance(iter, index);
    if (iter != children_.end()) {
        return *iter;
    }
    return nullptr;
}

int32_t UINode::GetChildIndex(const RefPtr<UINode>& child) const
{
    int32_t index = 0;
    for (const auto& iter : children_) {
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
    DoAddChild(iter, newNode);
}

void UINode::Clean()
{
    for (const auto& child : children_) {
        child->OnRemoveFromParent();
    }
    children_.clear();
    MarkNeedSyncRenderTree();
}

void UINode::MountToParent(const RefPtr<UINode>& parent, int32_t slot, bool silently)
{
    CHECK_NULL_VOID(parent);
    parent->AddChild(AceType::Claim(this), slot, silently);
    if (parent->IsInDestroying()) {
        parent->SetChildrenInDestroying();
    }
    if (parent->GetPageId() != 0) {
        SetHostPageId(parent->GetPageId());
    }
}

void UINode::OnRemoveFromParent()
{
    DetachFromMainTree();
    auto* frame = AceType::DynamicCast<FrameNode>(this);
    if (frame) {
        auto focusHub = frame->GetFocusHub();
        if (focusHub) {
            focusHub->RemoveSelf();
        }
    }
    parent_.Reset();
    depth_ = -1;
}

void UINode::DoAddChild(std::list<RefPtr<UINode>>::iterator& it, const RefPtr<UINode>& child, bool silently)
{
    children_.insert(it, child);

    child->SetParent(Claim(this));
    child->SetDepth(GetDepth() + 1);
    if (!silently && onMainTree_) {
        child->AttachToMainTree();
    }
    MarkNeedSyncRenderTree();
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

void UINode::AttachToMainTree()
{
    if (onMainTree_) {
        return;
    }
    onMainTree_ = true;
    OnAttachToMainTree();
    for (const auto& child : children_) {
        child->AttachToMainTree();
    }
}

void UINode::DetachFromMainTree()
{
    if (!onMainTree_) {
        return;
    }
    onMainTree_ = false;
    OnDetachFromMainTree();
    for (const auto& child : children_) {
        child->DetachFromMainTree();
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
            LOGD("Already at the right place");
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
    parentNode->MarkNeedSyncRenderTree();
}

void UINode::UpdateLayoutPropertyFlag()
{
    for (const auto& child : children_) {
        child->UpdateLayoutPropertyFlag();
    }
}

void UINode::AdjustParentLayoutFlag(PropertyChangeFlag& flag)
{
    for (const auto& child : children_) {
        child->AdjustParentLayoutFlag(flag);
    }
}

void UINode::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    for (const auto& child : children_) {
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

void UINode::MarkNeedSyncRenderTree()
{
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->MarkNeedSyncRenderTree();
    }
}

void UINode::RebuildRenderContextTree()
{
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->RebuildRenderContextTree();
    }
}
void UINode::OnDetachFromMainTree() {}

void UINode::OnAttachToMainTree() {}

void UINode::DumpTree(int32_t depth)
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc("ID: " + std::to_string(nodeId_));
        DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(GetDepth())));
        DumpInfo();
        DumpLog::GetInstance().Print(depth, tag_, static_cast<int32_t>(children_.size()));
    }

    for (const auto& item : children_) {
        item->DumpTree(depth + 1);
    }
}

void UINode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapper>& parent, bool forceMeasure, bool forceLayout)
{
    for (const auto& child : children_) {
        if (!child->IsInDestroying()) {
            child->AdjustLayoutWrapperTree(parent, forceMeasure, forceLayout);
        }
    }
}

void UINode::GenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
{
    for (const auto& child : children_) {
        child->OnGenerateOneDepthVisibleFrame(visibleList);
    }
}

void UINode::GenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& allList)
{
    for (const auto& child : children_) {
        child->OnGenerateOneDepthAllFrame(allList);
    }
}

RefPtr<PipelineContext> UINode::GetContext()
{
    return PipelineContext::GetCurrentContext();
}

HitTestResult UINode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId)
{
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
        auto& child = *iter;
        auto hitResult = child->TouchTest(globalPoint, parentLocalPoint, touchRestrict, result, touchId);
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
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
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
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
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
    auto iter = children_.begin();
    while (iter != GetChildren().end()) {
        if (id == (*iter)->GetId()) {
            return pos;
        }
        pos++;
        iter++;
    }
    return -1;
}

RefPtr<LayoutWrapper> UINode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
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

void UINode::Build()
{
    for (const auto& child : children_) {
        child->Build();
    }
}

void UINode::SetActive(bool active)
{
    for (const auto& child : children_) {
        child->SetActive(active);
    }
}

void UINode::OnVisibleChange(bool isVisible)
{
    for (const auto& child : GetChildren()) {
        child->OnVisibleChange(isVisible);
    }
}

std::pair<bool, int32_t> UINode::GetChildFlatIndex(int32_t id)
{
    if (GetId() == id) {
        return std::pair<bool, int32_t>(true, 0);
    }

    const auto& node = ElementRegister::GetInstance()->GetUINodeById(id);
    if (!node) {
        return std::pair<bool, int32_t>(false, 0);
    }

    if (node && (node->GetTag() == GetTag())) {
        return std::pair<bool, int32_t>(false, 1);
    }

    int32_t count = 0;
    for (const auto& child : GetChildren()) {
        auto res = child->GetChildFlatIndex(id);
        if (res.first) {
            return std::pair<bool, int32_t>(true, count + res.second);
        }
        count += res.second;
    }
    return std::pair<bool, int32_t>(false, count);
}

// for Grid refresh GridItems
void UINode::ChildrenUpdatedFrom(int32_t index)
{
    childrenUpdatedFrom_ = index;
}

void UINode::SetChildrenInDestroying()
{
    if (children_.empty()) {
        return;
    }

    for (const auto& child : children_) {
        if (!child) {
            continue;
        }
        child->SetChildrenInDestroying();
        child->SetInDestroying();
    }
}
} // namespace OHOS::Ace::NG
