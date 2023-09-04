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

namespace OHOS::Ace::NG {
UINode::~UINode() {}
void UINode::ReplaceChild(const RefPtr<UINode>& oldNode, const RefPtr<UINode>& newNode) {}
void UINode::Clean(bool cleanDirectly, bool allowTransition) {}
void UINode::GetFocusChildren(std::list<RefPtr<FrameNode>>& children) const {}
void UINode::AttachToMainTree(bool) {}
void UINode::DetachFromMainTree(bool) {}
void UINode::MovePosition(int32_t slot) {}
void UINode::UpdateLayoutPropertyFlag() {}
void UINode::AdjustParentLayoutFlag(PropertyChangeFlag& flag) {}
void UINode::MarkDirtyNode(PropertyChangeFlag extraFlag) {}
void UINode::MarkNeedFrameFlushDirty(PropertyChangeFlag extraFlag) {}
void UINode::MarkNeedSyncRenderTree(bool needRebuild) {}
void UINode::RebuildRenderContextTree() {}
void UINode::OnDetachFromMainTree(bool) {}
void UINode::OnAttachToMainTree(bool) {}
void UINode::OnGenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList) {}
bool UINode::OnRemoveFromParent(bool)
{
    return true;
}
bool UINode::RemoveImmediately() const
{
    return true;
}
void UINode::DumpTree(int32_t depth) {}
void UINode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout) {}
void UINode::GenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList) {}
void UINode::GenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& allList) {}
void UINode::Build() {}
void UINode::SetActive(bool active) {}
void UINode::SetJSViewActive(bool active) {}
void UINode::OnVisibleChange(bool isVisible) {}

void UINode::AddChild(const RefPtr<UINode>& child, int32_t /* slot */, bool /*silently*/)
{
    CHECK_NULL_VOID(child);
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        return;
    }
    it = children_.begin();
    std::advance(it, -1);
    children_.insert(it, child);
    child->SetParent(Claim(this));
}

void UINode::MountToParent(const RefPtr<UINode>& parent, int32_t slot, bool silently)
{
    CHECK_NULL_VOID(parent);
    parent->AddChild(AceType::Claim(this), slot, silently);
}

std::list<RefPtr<UINode>>::iterator UINode::RemoveChild(const RefPtr<UINode>& child, bool allowTransition)
{
    CHECK_NULL_RETURN(child, children_.end());
    auto iter = std::find(children_.begin(), children_.end(), child);
    if (iter == children_.end()) {
        return children_.end();
    }
    auto result = children_.erase(iter);
    return result;
}

int32_t UINode::RemoveChildAndReturnIndex(const RefPtr<UINode>& child)
{
    return 1;
}

UINode::UINode(const std::string& tag, int32_t nodeId, bool isRoot) : tag_(tag), nodeId_(nodeId), isRoot_(isRoot) {}

void UINode::RemoveChildAtIndex(int32_t index) {}

RefPtr<UINode> UINode::GetChildAtIndex(int32_t index) const
{
    return nullptr;
}

RefPtr<FrameNode> UINode::GetFocusParent() const
{
    return nullptr;
}

RefPtr<PipelineContext> UINode::GetContext()
{
    return nullptr;
}

HitTestResult UINode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, const TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId)
{
    return HitTestResult::OUT_OF_REGION;
}

HitTestResult UINode::MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    MouseTestResult& onMouseResult, MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode)
{
    return HitTestResult::OUT_OF_REGION;
}

HitTestResult UINode::AxisTest(const PointF& globalPoint, const PointF& parentLocalPoint, AxisTestResult& onAxisResult)
{
    return HitTestResult::OUT_OF_REGION;
}

int32_t UINode::FrameCount() const
{
    return TotalChildCount();
}

int32_t UINode::TotalChildCount() const
{
    return 0;
}

int32_t UINode::GetChildIndexById(int32_t id)
{
    return -1;
}

RefPtr<LayoutWrapperNode> UINode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    return nullptr;
}

bool UINode::MarkRemoving()
{
    return false;
}

bool UINode::RemoveDisappearingChild(const RefPtr<UINode>& child)
{
    return false;
}

void UINode::UpdateConfigurationUpdate(const OnConfigurationChange& configurationChange) {}

void UINode::AddDisappearingChild(const RefPtr<UINode>& child, uint32_t) {}

RefPtr<UINode> UINode::GetDisappearingChildById(const std::string& id) const
{
    return nullptr;
}

RefPtr<UINode> UINode::GetFrameChildByIndex(uint32_t index, bool needBuild)
{
    return nullptr;
}

void UINode::DoRemoveChildInRenderTree(uint32_t index, bool isAll) {}

void UINode::OnSetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint) {}
} // namespace OHOS::Ace::NG
