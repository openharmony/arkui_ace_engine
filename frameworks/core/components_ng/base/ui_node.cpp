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

#include <algorithm>
#include <cstdint>
#include <iterator>

#include "base/geometry/ng/point_t.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

UINode::~UINode()
{
    ElementRegister::GetInstance()->RemoveItem(nodeId_);
    if (!onMainTree_) {
        return;
    }
    DetachFromMainTree();
    onMainTree_ = false;
}

void UINode::AddChild(const RefPtr<UINode>& child, int32_t slot)
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
    children_.insert(it, child);

    child->SetParent(Claim(this));
    child->SetDepth(GetDepth() + 1);
    if (onMainTree_) {
        child->AttachToMainTree();
    }
    MarkNeedSyncRenderTree();
}

std::list<RefPtr<UINode>>::iterator UINode::RemoveChild(const RefPtr<UINode>& child)
{
    CHECK_NULL_RETURN(child, children_.end());

    auto iter = std::find(children_.begin(), children_.end(), child);
    if (iter == children_.end()) {
        LOGE("child is not exist.");
        return children_.end();
    }
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
    children_.erase(iter);
    MarkNeedSyncRenderTree();
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
    children_.insert(iter, newNode);
    newNode->SetParent(Claim(this));
    newNode->SetDepth(GetDepth() + 1);
    if (onMainTree_) {
        newNode->AttachToMainTree();
    }
    MarkNeedSyncRenderTree();
}

void UINode::Clean()
{
    children_.clear();
    MarkNeedSyncRenderTree();
}

void UINode::MountToParent(const RefPtr<UINode>& parent, int32_t slot)
{
    CHECK_NULL_VOID(parent);
    parent->AddChild(AceType::Claim(this), slot);
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
        DumpLog::GetInstance().AddDesc("tag: " + tag_);
        DumpLog::GetInstance().AddDesc("id: " + std::to_string(nodeId_));
        DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(GetDepth())));
        DumpInfo();
        DumpLog::GetInstance().Print(depth, AceType::TypeName(this), static_cast<int32_t>(children_.size()));
    }

    for (const auto& item : children_) {
        item->DumpTree(depth + 1);
    }
}

void UINode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapper>& parent, bool forceMeasure, bool forceLayout)
{
    for (const auto& child : children_) {
        child->AdjustLayoutWrapperTree(parent, forceMeasure, forceLayout);
    }
}

void UINode::GenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
{
    for (const auto& child : children_) {
        child->OnGenerateOneDepthVisibleFrame(visibleList);
    }
}

RefPtr<PipelineContext> UINode::GetContext()
{
    return PipelineContext::GetCurrentContext();
}

HitTestResult UINode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    HitTestResult hitTestResult = HitTestResult::OUT_OF_REGION;
    for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
        auto& child = *iter;
        auto hitResult = child->TouchTest(globalPoint, parentLocalPoint, touchRestrict, result);
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

} // namespace OHOS::Ace::NG
