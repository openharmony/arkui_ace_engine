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

#include "core/components_ng/animation/geometry_transition.h"

#include "core/components_ng/property/property.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
GeometryTransition::GeometryTransition(const WeakPtr<FrameNode>& frameNode, bool forceOutAnim)
    : inNode_(frameNode), forceOutAnim_(forceOutAnim)
{
    state_ = State::IDLE;
    hasInAnim_ = false;
    hasOutAnim_ = false;
}

// Transition has two states: active and identity, for inNode appearing transition active state defines
// the start of transition while for outNode disappearing transition active state defines the end of transition,
// identity state means the state it should to be as ui descriptions.
// Geometry transition is used for hero animation dealing with matched pair of inNode and outNode holding the
// same key. During geometry transition inNode starts with the size and position of outNode(inNode active),
// animates to the place where it should to be(inNode identity), meanwhile outNode starts with its own size
// and position(outNode identity), animates to the final size and position of inNode(outNode active). Although
// we have two transitions but these two transitions fit together perfectly, so the appearance looks like a
// single view move from its old position to its new position, thus visual foucus guidance is completed.
// We design the pipeline to have two layouts with different layout constraints, during implicit animation
// layout related render node properties changes by two layouts are animated. The relationship between node and
// layout state is as follows.
// ---------------------------------------------------------
// inNode   | outNode  | layout state
// ---------------------------------------------------------
// (active inNode uses outNode's size as layout constraint)
// active   | identity | initial layout
// (active inNode syncs position to outNode's position)
// ---------------------------------------------------------
// (active outNode uses inNode's size as layout constraint)
// identity |  acitve  | final layout
// (active outNode syncs position to inNode's position)
// ---------------------------------------------------------
bool GeometryTransition::IsNodeActive(const WeakPtr<FrameNode>& frameNode) const
{
    return IsNodeInAndActive(frameNode) || IsNodeOutAndActive(frameNode);
}

bool GeometryTransition::IsNodeIdentity(const WeakPtr<FrameNode>& frameNode) const
{
    return IsNodeInAndIdentity(frameNode) || IsNodeOutAndIdentity(frameNode);
}

bool GeometryTransition::IsNodeInAndIdentity(const WeakPtr<FrameNode>& frameNode) const
{
    // inNode is identity in final layout
    return hasInAnim_ && frameNode.Upgrade() == inNode_ && state_ == State::FINAL_LAYOUT;
}

bool GeometryTransition::IsNodeInAndActive(const WeakPtr<FrameNode>& frameNode) const
{
    // inNode is active in initial layout
    return hasInAnim_ && frameNode.Upgrade() == inNode_ && state_ == State::INITIAL_LAYOUT;
}

bool GeometryTransition::IsNodeOutAndIdentity(const WeakPtr<FrameNode>& frameNode) const
{
    // outNode is identity in initial layout
    return hasOutAnim_ && frameNode.Upgrade() == outNode_ && state_ == State::INITIAL_LAYOUT;
}

bool GeometryTransition::IsNodeOutAndActive(const WeakPtr<FrameNode>& frameNode) const
{
    // outNode is active in final layout
    return hasOutAnim_ && frameNode.Upgrade() == outNode_ && state_ == State::FINAL_LAYOUT;
}

// Build should be called during node tree bulid phase dealing with node add/remove or appearing/disappearing
void GeometryTransition::Build(const WeakPtr<FrameNode>& frameNode, bool isNodeIn)
{
    CHECK_NULL_VOID(frameNode.Upgrade());

    if (isNodeIn) {
        if (frameNode == inNode_) {
            return;
        }
        if (inNode_.Upgrade() != nullptr) {
            std::swap(inNode_, outNode_);
        }
        inNode_ = frameNode;
        hasInAnim_ = true;
        // if forceOutAnim_ is true we'll animate outNode regardless of whether it's really removed,
        // otherwise we'll animate outNode only when it's really removed.
        hasOutAnim_ = hasOutAnim_ || forceOutAnim_;
    } else {
        if (frameNode != inNode_ && frameNode != outNode_) {
            return;
        }
        if (frameNode == inNode_) {
            std::swap(inNode_, outNode_);
        }
        hasOutAnim_ = true;
        outNode_.Upgrade()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }

    auto inNode = inNode_.Upgrade();
    auto outNode = outNode_.Upgrade();
    CHECK_NULL_VOID(inNode);
    CHECK_NULL_VOID(outNode);
    CHECK_NULL_VOID(inNode->GetLayoutProperty());
    CHECK_NULL_VOID(outNode->GetLayoutProperty());
    CHECK_NULL_VOID(inNode->GetGeometryNode());
    CHECK_NULL_VOID(outNode->GetGeometryNode());

    // once there is inNode animation we need two layout phases and start from initial layout,
    // outNode animation only without inNode animation just needs one layout phase and starts from final layout.
    state_ = isNodeIn ? State::INITIAL_LAYOUT : State::FINAL_LAYOUT;
    forceState_ = false;

    // outNode in identity state means no layout change and keeping its original size and position
    if (IsNodeOutAndIdentity(outNode_)) {
        outNode->MarkDirtyNode(PROPERTY_UPDATE_NORMAL);
    }

    LOGD("GeometryTransition: matched info, "
        "inNodeId: %{public}d, inAnim: %{public}d, outNodeId: %{public}d, outAnim: %{public}d, state: %{public}d",
        inNode->GetId(), hasInAnim_, outNode->GetId(), hasOutAnim_, state_);
}

// Update should be called during node update phase when node exisits
bool GeometryTransition::Update(const WeakPtr<FrameNode>& which, const WeakPtr<FrameNode>& value)
{
    if (which.Upgrade() == inNode_) {
        inNode_ = value;
        return true;
    } else if (which.Upgrade() == outNode_) {
        outNode_ = value;
        return true;
    }
    return false;
}

// Called before layout, perform layout constraints match modifications in active state to
// impact self and children's measure and layout.
void GeometryTransition::WillLayout(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    if (state_ == State::IDLE) {
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);
    // in geometry transition active state node uses matched target's geometry size as layout constraints instead of
    // using own or parent's constraints, its layout behavior is not limited by parent.
    auto hostNode = layoutWrapper->GetHostNode();
    if (IsNodeInAndActive(hostNode)) {
        ModifyLayoutConstraint(layoutWrapper, true);
    } else if (IsNodeOutAndActive(hostNode)) {
        ModifyLayoutConstraint(layoutWrapper, false);
    }
}

// Called after layout, perform final adjustments of geometry position
void GeometryTransition::DidLayout(const WeakPtr<FrameNode>& frameNode)
{
    if (state_ == State::IDLE) {
        return;
    }
    auto node = frameNode.Upgrade();
    CHECK_NULL_VOID(node);
    if (state_ == State::INITIAL_LAYOUT) {
        if (IsNodeInAndActive(frameNode)) {
            SyncGeometry(true);
            // dirty node is added to initiate the second layout
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            TryToSetState(!hasOutAnim_, State::FINAL_LAYOUT);
            LOGD("GeometryTransition: node%{public}d: in and active", node->GetId());
            return;
        }
        if (IsNodeOutAndIdentity(frameNode)) {
            // dirty node is added to initiate the second layout
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            TryToSetState(!hasInAnim_, State::FINAL_LAYOUT);
            LOGD("GeometryTransition: node%{public}d: out and identity", node->GetId());
            return;
        }
    } else if (state_ == State::FINAL_LAYOUT) {
        if (IsNodeInAndIdentity(frameNode)) {
            hasInAnim_ = false;
            TryToSetState(!hasOutAnim_, State::IDLE);
            LOGD("GeometryTransition: node%{public}d: in and identity", node->GetId());
            return;
        }
        if (IsNodeOutAndActive(frameNode)) {
            SyncGeometry(false);
            hasOutAnim_ = false;
            TryToSetState(!hasInAnim_, State::IDLE);
            LOGD("GeometryTransition: node%{public}d: out and active", node->GetId());
            return;
        }
    }
}

void GeometryTransition::TryToSetState(bool condition, State state)
{
    if (condition || forceState_) {
        state_ = state;
        forceState_ = false;
    } else {
        forceState_ = true;
    }
}

void GeometryTransition::ModifyLayoutConstraint(const RefPtr<LayoutWrapper>& layoutWrapper, bool isNodeIn)
{
    // outNode's frame is the target frame for active inNode to match,
    // inNode's frame is the target frame for active outNode to match.
    auto inNode = inNode_.Upgrade();
    auto outNode = outNode_.Upgrade();
    auto self = isNodeIn ? inNode : outNode;
    auto target = isNodeIn ? outNode : inNode;
    CHECK_NULL_VOID(self);
    CHECK_NULL_VOID(target);
    // as outNodes are sequentially processed after inNodes's layout is completed,
    // inNode's geometry is ready for outNode to use as its layout constraints now.
    auto size = target->GetGeometryNode()->GetFrameSize();
    auto targetSize = CalcSize(NG::CalcLength(size.Width()), NG::CalcLength(size.Height()));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    // as layoutWrapper copy layout property from node, node's original layout property is not modified,
    // otherwise we need to recovery layout constraints modifications.
    layoutProperty->UpdateUserDefinedIdealSize(targetSize);
    LOGD("GeometryTransition: node%{public}d: modify size to: %{public}s",
        self->GetId(), targetSize.ToString().c_str());
    // if node has aspect ratio we'll ignore it in active state, instead target's aspect ratio is respected
    const auto& magicItemProperty = layoutProperty->GetMagicItemProperty();
    auto hasAspectRatio = magicItemProperty ? magicItemProperty->HasAspectRatio() : false;
    if (hasAspectRatio && size.Width() > 0) {
        auto targetAspectRatio = size.Width() / size.Height();
        magicItemProperty->UpdateAspectRatio(targetAspectRatio);
        LOGD("GeometryTransition: node%{public}d: modify aspect ratio to: %{public}f",
            self->GetId(), targetAspectRatio);
    }
}

void GeometryTransition::SyncGeometry(bool isNodeIn)
{
    // outNode's position is the target position for active inNode to match,
    // inNode's position is the target position for active outNode to match.
    auto inNode = inNode_.Upgrade();
    auto outNode = outNode_.Upgrade();
    auto self = isNodeIn ? inNode : outNode;
    auto target = isNodeIn ? outNode : inNode;
    CHECK_NULL_VOID(self);
    CHECK_NULL_VOID(target);
    // get own parent's global position
    auto parentPos = self->GetPaintRectOffset(true);
    // get target's global position
    auto targetPos = target->GetPaintRectOffset();
    // adjust self's position to match with target's position, here we only need to adust node self,
    // its children's positions are still determined by layout process.
    auto paintRect = self->GetGeometryNode()->GetFrameRect();
    paintRect.SetOffset(targetPos - parentPos);
    self->GetRenderContext()->SyncGeometryProperties(paintRect);

    LOGD("GeometryTransition: node%{public}d: %{public}s, target: %{public}s, "
        "synced frame: %{public}f %{public}f %{public}f %{public}f",
        self->GetId(), parentPos.ToString().c_str(), targetPos.ToString().c_str(),
        paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
}
} // namespace OHOS::Ace::NG