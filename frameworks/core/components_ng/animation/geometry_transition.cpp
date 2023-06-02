/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
// Geometry transition is used for hero animation dealing with matched pair of inNode and outNode holding the
// same key. During geometry transition inNode starts with the size and position of outNode(inNode active),
// animates to the place where it should to be(inNode identity), meanwhile outNode starts with its own size
// and position(outNode identity), animates to the final size and position of inNode(outNode active). Although
// we have two transitions but these two transitions fit together perfectly, so the appearance looks like a
// single view move from its old position to its new position, thus visual focus guidance is completed.
GeometryTransition::GeometryTransition(const WeakPtr<FrameNode>& frameNode) : inNode_(frameNode) {}

bool GeometryTransition::IsInAndOutEmpty() const
{
    return !inNode_.Upgrade() && !outNode_.Upgrade();
}

bool GeometryTransition::IsInAndOutValid() const
{
    return inNode_.Upgrade() && outNode_.Upgrade();
}

bool GeometryTransition::IsRunning() const
{
    return IsInAndOutValid() && (hasInAnim_ || hasOutAnim_);
}

bool GeometryTransition::IsNodeInAndActive(const WeakPtr<FrameNode>& frameNode) const
{
    return IsInAndOutValid() && hasInAnim_ && frameNode.Upgrade() == inNode_ && state_ == State::ACTIVE;
}

bool GeometryTransition::IsNodeInAndIdentity(const WeakPtr<FrameNode>& frameNode) const
{
    return IsInAndOutValid() && hasInAnim_ && frameNode.Upgrade() == inNode_ && state_ == State::IDENTITY;
}

bool GeometryTransition::IsNodeOutAndActive(const WeakPtr<FrameNode>& frameNode) const
{
    return IsInAndOutValid() && hasOutAnim_ && frameNode.Upgrade() == outNode_;
}

void GeometryTransition::SwapInAndOut(bool condition)
{
    if (condition) {
        std::swap(inNode_, outNode_);
    }
}

std::pair<RefPtr<FrameNode>, RefPtr<FrameNode>> GeometryTransition::GetMatchedPair(bool isNodeIn) const
{
    auto self = isNodeIn ? inNode_ : outNode_;
    auto target = isNodeIn ? outNode_ : inNode_;
    return { self.Upgrade(), target.Upgrade() };
}

// Build should be called during node tree build phase dealing with node add/remove or appearing/disappearing
void GeometryTransition::Build(const WeakPtr<FrameNode>& frameNode, bool isNodeIn)
{
    state_ = State::IDLE;
    auto node = frameNode.Upgrade();
    CHECK_NULL_VOID(node);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    LOGD("GeometryTransition: build node%{public}d %{public}s", node->GetId(), isNodeIn ? "in" : "out");

    if (!isNodeIn && (frameNode == inNode_ || frameNode == outNode_)) {
        SwapInAndOut(frameNode == inNode_);
        hasOutAnim_ = true;
        outNodeParentPos_ = node->GetPaintRectGlobalOffsetWithTranslate(true);
        outNodePos_ = outNodeParentPos_ + renderContext->GetPaintRectWithTransform().GetOffset();
    }
    if (isNodeIn && (frameNode != inNode_)) {
        auto inNode = inNode_.Upgrade();
        if (inNode != nullptr && !inNode->IsRemoving() && !inNode->IsOnMainTree()) {
            inNode_ = frameNode;
            return;
        }
        SwapInAndOut(inNode != nullptr);
        inNode_ = frameNode;
        hasInAnim_ = true;
    }

    auto inNode = inNode_.Upgrade();
    auto outNode = outNode_.Upgrade();
    if (!IsInAndOutValid() || (inNode == outNode)) {
        return;
    }

    if (hasOutAnim_) {
        // set relative low priority for outNode
        outNode->SetLayoutPriority(-1);
        outNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        LOGD("GeometryTransition: node%{public}d has out anim, tag: %{public}s, matched target node: %{public}d",
            outNode->GetId(), outNode->GetTag().c_str(), inNode->GetId());
    }
    if (hasInAnim_) {
        state_ = State::ACTIVE;
        // set relative high priority for inNode
        inNode->SetLayoutPriority(1);
        inNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        LOGD("GeometryTransition: node%{public}d has in anim, tag: %{public}s, matched target node: %{public}d",
            inNode->GetId(), inNode->GetTag().c_str(), outNode->GetId());
    }
}

// Update should be called during node update phase when node exists
bool GeometryTransition::Update(const WeakPtr<FrameNode>& which, const WeakPtr<FrameNode>& value)
{
    bool ret = false;
    std::string str;
    if (which.Upgrade() == inNode_.Upgrade()) {
        str += "inNode updated: ";
        inNode_ = value;
        ret = true;
    } else if (which.Upgrade() == outNode_.Upgrade()) {
        str += "outNode updated: ";
        outNode_ = value;
        ret = true;
    } else {
        str += "noneNode updated: ";
    }
    str += "old value: ";
    str += which.Upgrade() ? std::to_string(which.Upgrade()->GetId()) : "null";
    str += ", new value: ";
    str += value.Upgrade() ? std::to_string(value.Upgrade()->GetId()) : "null";
    LOGD("GeometryTransition: %{public}s", str.c_str());
    return ret;
}

// Called before layout, perform layout constraints match modifications in active state to
// impact self and children's measure and layout.
void GeometryTransition::WillLayout(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    if (!layoutWrapper->IsRootMeasureNode()) {
        return;
    }
    auto hostNode = layoutWrapper->GetHostNode();
    if (IsNodeInAndActive(hostNode)) {
        ModifyLayoutConstraint(layoutWrapper, true);
    } else if (IsNodeOutAndActive(hostNode)) {
        ModifyLayoutConstraint(layoutWrapper, false);
    }
}

// Called after layout, perform final adjustments of geometry position
void GeometryTransition::DidLayout(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto node = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(node);
    bool isRoot = layoutWrapper->IsRootMeasureNode();
    std::optional<bool> direction = std::nullopt;

    if (isRoot && IsNodeInAndActive(node)) {
        LOGD("GeometryTransition: node%{public}d: in and active", node->GetId());
        state_ = State::IDENTITY;
        auto geometryNode = node->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        inNodeActiveFrameSize_ = geometryNode->GetFrameSize();
    } else if (IsNodeInAndIdentity(node)) {
        LOGD("GeometryTransition: node%{public}d: in and identity", node->GetId());
        state_ = State::IDLE;
        node->SetLayoutPriority(0);
        direction = true;
        hasInAnim_ = false;
    } else if (isRoot && IsNodeOutAndActive(node)) {
        LOGD("GeometryTransition: node%{public}d: out and active", node->GetId());
        direction = false;
        hasOutAnim_ = false;
    }

    if (direction.has_value()) {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(PipelineBase::GetCurrentContext());
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterLayoutTask([weak = WeakClaim(this), isNodeIn = direction.value()]() {
            auto geometryTransition = weak.Upgrade();
            CHECK_NULL_VOID(geometryTransition);
            geometryTransition->SyncGeometry(isNodeIn);
        });
    }
}

void GeometryTransition::ModifyLayoutConstraint(const RefPtr<LayoutWrapper>& layoutWrapper, bool isNodeIn)
{
    // outNode's frame is the target frame for active inNode to match,
    // inNode's frame is the target frame for active outNode to match.
    auto [self, target] = GetMatchedPair(isNodeIn);
    CHECK_NULL_VOID(self);
    CHECK_NULL_VOID(target);
    // target's geometry is ensured ready to use because layout nodes are sorted to respect dependency,
    // the order is active inNode, normal layout, active outNode.
    auto targetGeometryNode = target->GetGeometryNode();
    CHECK_NULL_VOID(targetGeometryNode);
    auto targetRenderContext = target->GetRenderContext();
    CHECK_NULL_VOID(targetRenderContext);
    auto size = isNodeIn ? targetRenderContext->GetPaintRectWithTransform().GetSize() :
                           targetGeometryNode->GetFrameSize();
    auto targetSize = CalcSize(NG::CalcLength(size.Width()), NG::CalcLength(size.Height()));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(targetSize);
    LOGD("GeometryTransition: node%{public}d: modify size to: %{public}s",
        self->GetId(), targetSize.ToString().c_str());
    // if node has aspect ratio we'll ignore it in active state, instead target's aspect ratio is respected
    const auto& magicItemProperty = layoutProperty->GetMagicItemProperty();
    auto hasAspectRatio = magicItemProperty ? magicItemProperty->HasAspectRatio() : false;
    if (hasAspectRatio && size.IsPositive()) {
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
    auto [self, target] = GetMatchedPair(isNodeIn);
    CHECK_NULL_VOID(self);
    CHECK_NULL_VOID(target);
    auto renderContext = self->GetRenderContext();
    auto targetRenderContext = target->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    CHECK_NULL_VOID(targetRenderContext);
    auto geometryNode = self->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    // get own parent's global position, parent's transform is not taken into account other than translate
    auto parentPos = self->IsRemoving() ? outNodeParentPos_ : self->GetPaintRectGlobalOffsetWithTranslate(true);
    // get target's global position, target own transform is taken into account
    auto targetPos = target->IsRemoving() ? outNodePos_ : target->GetPaintRectGlobalOffsetWithTranslate(true) +
        targetRenderContext->GetPaintRectWithTransform().GetOffset();
    // adjust self's position to match with target's position, here we only need to adjust node self,
    // its children's positions are still determined by layout process.
    auto activeFrameRect = isNodeIn ? RectF(targetPos - parentPos, inNodeActiveFrameSize_) :
                                      RectF(targetPos - parentPos, geometryNode->GetFrameSize());
    auto activeCornerRadius = targetRenderContext->GetBorderRadius().value_or(BorderRadiusProperty());
    auto cornerRadius = renderContext->GetBorderRadius().value_or(BorderRadiusProperty());

    if (!isNodeIn) {
        // save outNode's target global frame rect for future compare to sync outNode with inNode's frame change
        outNodeTargetAbsRect_ = RectF(targetPos, activeFrameRect.GetSize());
    } else if (target->IsRemoving()) {
        // notify backend for hierarchy processing to avoid outNode being shaded
        renderContext->RegisterSharedTransition(targetRenderContext);
    }

    // draw self and children in sandbox which will not be affected by parent's transition
    renderContext->SetSandBox(parentPos);

    AnimationUtils::AnimateWithCurrentOptions(
        [&]() {
            // sync geometry in active state
            renderContext->UpdateBorderRadius(activeCornerRadius);
            renderContext->SyncGeometryProperties(activeFrameRect);
            // sync geometry in identity state for inNode
            if (isNodeIn) {
                renderContext->UpdateBorderRadius(cornerRadius);
                renderContext->SyncGeometryProperties(RawPtr(geometryNode));
            }
        },
        [id = Container::CurrentId(), nodeWeak = WeakClaim(RawPtr(self))]() {
            ContainerScope scope(id);
            auto node = nodeWeak.Upgrade();
            CHECK_NULL_VOID_NOLOG(node);
            auto renderContext = node->GetRenderContext();
            CHECK_NULL_VOID_NOLOG(renderContext);
            renderContext->SetSandBox(std::nullopt);
            LOGD("GeometryTransition: node%{public}d animation completed", node->GetId());
        },
        false);

    LOGD("GeometryTransition: node%{public}d: %{public}s, target: %{public}s, "
        "active frame: %{public}s, identity frame: %{public}s",
        self->GetId(), parentPos.ToString().c_str(), targetPos.ToString().c_str(),
        activeFrameRect.ToString().c_str(), isNodeIn ? geometryNode->GetFrameRect().ToString().c_str() : "no log");
}

// during outNode animation is running target inNode's frame is changed, outNode needs to change as well to
// match tightly.
void GeometryTransition::OnReSync()
{
    auto inNode = inNode_.Upgrade();
    auto outNode = outNode_.Upgrade();
    CHECK_NULL_VOID(inNode && outNode);
    auto renderContext = inNode->GetRenderContext();
    if (!renderContext || !renderContext->IsSynced() || !outNode->IsRemoving()) {
        return;
    }
    auto paintRect = renderContext->GetPaintRectWithTransform();
    auto inNodeAbsRect = RectF(inNode->GetPaintRectGlobalOffsetWithTranslate(true) + paintRect.GetOffset(),
                               paintRect.GetSize());
    if (inNodeAbsRect != outNodeTargetAbsRect_) {
        hasOutAnim_ = true;
        outNode->GetLayoutProperty()->CleanDirty();
        outNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        LOGD("GeometryTransition: outNode%{public}d %{public}s is marked dirty to respond to frame change of "
            "inNode%{public}d %{public}s", outNode->GetId(), outNodeTargetAbsRect_.ToString().c_str(),
            inNode->GetId(), inNodeAbsRect.ToString().c_str());
    }
}

// if nodes with geometry transitions are added during layout, we need to execute additional layout in current frame
bool GeometryTransition::OnAdditionalLayout(const WeakPtr<FrameNode>& frameNode)
{
    bool ret = false;
    auto node = frameNode.Upgrade();
    CHECK_NULL_RETURN(node, false);
    if (IsNodeInAndActive(frameNode)) {
        auto parent = node->GetParent();
        while (parent) {
            auto parentNode = AceType::DynamicCast<FrameNode>(parent);
            if (parentNode) {
                node->GetLayoutProperty()->CleanDirty();
                node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
                parentNode->GetLayoutProperty()->CleanDirty();
                parentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
                ret = true;
                LOGD("GeometryTransition: node%{public}d, parent node%{public}d is marked dirty",
                    node->GetId(), parentNode->GetId());
                break;
            }
            parent = parent->GetParent();
        }
    } else if (IsNodeOutAndActive(frameNode)) {
        ret = true;
    }
    return ret;
}

std::string GeometryTransition::ToString() const
{
    return std::string("in: ") + (inNode_.Upgrade() ? std::to_string(inNode_.Upgrade()->GetId()) : "null") +
        std::string(", out: ") + (outNode_.Upgrade() ? std::to_string(outNode_.Upgrade()->GetId()) : "null");
}
} // namespace OHOS::Ace::NG