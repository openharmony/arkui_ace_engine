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
#include "core/components_ng/base/view_stack_processor.h"
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
GeometryTransition::GeometryTransition(const std::string& id, const WeakPtr<FrameNode>& frameNode,
    bool followWithoutTransition) : id_(id), inNode_(frameNode), followWithoutTransition_(followWithoutTransition) {}

bool GeometryTransition::IsInAndOutEmpty() const
{
    return !inNode_.Upgrade() && !outNode_.Upgrade();
}

bool GeometryTransition::IsInAndOutValid() const
{
    return inNode_.Upgrade() && outNode_.Upgrade();
}

bool GeometryTransition::IsRunning(const WeakPtr<FrameNode>& frameNode) const
{
    CHECK_NULL_RETURN(IsInAndOutValid(), false);
    return (hasInAnim_ && frameNode.Upgrade() == inNode_) || (hasOutAnim_ && frameNode.Upgrade() == outNode_);
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

RectF GeometryTransition::GetNodeAbsFrameRect(const RefPtr<FrameNode>& node, std::optional<OffsetF> parentPos) const
{
    CHECK_NULL_RETURN(node, RectF());
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, RectF());
    auto parentGlobalOffset = parentPos.value_or(node->GetPaintRectGlobalOffsetWithTranslate(true));
    auto paintRect = renderContext->GetPaintRectWithTransform();
    return RectF(parentGlobalOffset + paintRect.GetOffset(), paintRect.GetSize());
}

void GeometryTransition::RecordOutNodeFrame()
{
    auto outNode = outNode_.Upgrade();
    CHECK_NULL_VOID(outNode);
    outNodeParentPos_ = outNode->GetPaintRectGlobalOffsetWithTranslate(true);
    auto outNodeAbsRect = GetNodeAbsFrameRect(outNode_.Upgrade(), outNodeParentPos_);
    outNodePos_ = outNodeAbsRect.GetOffset();
    outNodeSize_ = outNodeAbsRect.GetSize();
}

void GeometryTransition::MarkLayoutDirty(const RefPtr<FrameNode>& node, int32_t layoutPriority)
{
    CHECK_NULL_VOID(node && node->GetLayoutProperty());
    if (layoutPriority) {
        node->SetLayoutPriority(layoutPriority);
    }
    node->GetLayoutProperty()->CleanDirty();
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

// Build should be called during node tree build phase dealing with node add/remove or appearing/disappearing
void GeometryTransition::Build(const WeakPtr<FrameNode>& frameNode, bool isNodeIn)
{
    state_ = State::IDLE;
    outNodeTargetAbsRect_ = std::nullopt;
    if (IsInAndOutEmpty()) {
        hasInAnim_ = false;
        hasOutAnim_ = false;
    }
    auto node = frameNode.Upgrade();
    CHECK_NULL_VOID(node && node->GetRenderContext() && !id_.empty());
    LOGD("GeometryTransition: build node: %{public}d %{public}s", node->GetId(), isNodeIn ? "in" : "out");
    if (!isNodeIn && (frameNode == inNode_ || frameNode == outNode_)) {
        SwapInAndOut(frameNode == inNode_);
        RecordOutNodeFrame();
        hasOutAnim_ = true;
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
    CHECK_NULL_VOID(IsInAndOutValid() && (inNode != outNode));

    bool follow = false;
    if (hasOutAnim_) {
        MarkLayoutDirty(outNode, -1);
        if (!hasInAnim_) {
            follow = OnFollowWithoutTransition(false);
        }
    }
    if (hasInAnim_ && !follow) {
        state_ = State::ACTIVE;
        MarkLayoutDirty(inNode, 1);
        if (!hasOutAnim_) {
            follow = OnFollowWithoutTransition(true);
        }
    }

    LOGD("GeometryTransition: inAnim: %{public}d, outAnim: %{public}d, follow: %{public}d, "
        "inNode: %{public}d, %{public}s, outNode: %{public}d, %{public}s", hasInAnim_, hasOutAnim_, follow,
        inNode->GetId(), inNode->GetTag().c_str(), outNode->GetId(), outNode->GetTag().c_str());
}

// Update should be called during node update phase when node exists
bool GeometryTransition::Update(const WeakPtr<FrameNode>& which, const WeakPtr<FrameNode>& value)
{
    bool ret = false;
    std::string str = id_ + ",";
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
        layoutPropertyIn_ = hostNode->GetLayoutProperty()->Clone();
        ModifyLayoutConstraint(layoutWrapper, true);
    } else if (IsNodeOutAndActive(hostNode)) {
        layoutPropertyOut_ = hostNode->GetLayoutProperty()->Clone();
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
        LOGD("GeometryTransition: node: %{public}d in and active", node->GetId());
        state_ = State::IDENTITY;
        auto geometryNode = node->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        inNodeActiveFrameSize_ = geometryNode->GetFrameSize();
        layoutPropertyIn_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        node->SetLayoutProperty(layoutPropertyIn_);
        layoutPropertyIn_.Reset();
    } else if (IsNodeInAndIdentity(node)) {
        LOGD("GeometryTransition: node: %{public}d in and identity", node->GetId());
        state_ = State::IDLE;
        node->SetLayoutPriority(0);
        direction = true;
        hasInAnim_ = false;
    } else if (isRoot && IsNodeOutAndActive(node)) {
        LOGD("GeometryTransition: node: %{public}d out and active", node->GetId());
        hasOutAnim_ = false;
        CHECK_NULL_VOID(!hasInAnim_);
        direction = false;
    }

    if (direction.has_value()) {
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(PipelineBase::GetCurrentContext());
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterLayoutTask([weak = WeakClaim(this), isNodeIn = direction.value()]() {
            auto geometryTransition = weak.Upgrade();
            CHECK_NULL_VOID(geometryTransition);
            geometryTransition->SyncGeometry(isNodeIn);
            if (!isNodeIn) {
                auto outNode = geometryTransition->outNode_.Upgrade();
                if (outNode && geometryTransition->layoutPropertyOut_) {
                    outNode->SetLayoutProperty(geometryTransition->layoutPropertyOut_);
                    geometryTransition->layoutPropertyOut_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
                    geometryTransition->layoutPropertyOut_.Reset();
                }
            }
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
    SizeF size;
    if (isNodeIn) {
        staticNodeAbsRect_ =
            target->IsRemoving() ? std::nullopt : std::optional<RectF>(target->GetTransformRectRelativeToWindow());
        size = target->IsRemoving() ? outNodeSize_ : staticNodeAbsRect_->GetSize();
    } else {
        staticNodeAbsRect_ =
            !staticNodeAbsRect_ ? std::nullopt : std::optional<RectF>(target->GetTransformRectRelativeToWindow());
        size = !staticNodeAbsRect_ ? targetGeometryNode->GetFrameSize() : staticNodeAbsRect_->GetSize();
    }
    auto targetSize = CalcSize(NG::CalcLength(size.Width()), NG::CalcLength(size.Height()));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUserDefinedIdealSize(targetSize);
    LOGD("GeometryTransition: node: %{public}d modify size to: %{public}s",
        self->GetId(), targetSize.ToString().c_str());
    // if node has aspect ratio we'll ignore it in active state, instead target's aspect ratio is respected
    const auto& magicItemProperty = layoutProperty->GetMagicItemProperty();
    auto hasAspectRatio = magicItemProperty ? magicItemProperty->HasAspectRatio() : false;
    if (hasAspectRatio && size.IsPositive()) {
        auto targetAspectRatio = size.Width() / size.Height();
        magicItemProperty->UpdateAspectRatio(targetAspectRatio);
        LOGD("GeometryTransition: node: %{public}d modify aspect ratio to: %{public}f",
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
    auto targetRect = target->IsRemoving() ? RectF(outNodePos_, outNodeSize_) :
                                             staticNodeAbsRect_.value_or(GetNodeAbsFrameRect(target));
    auto targetPos = targetRect.GetOffset();
    // adjust self's position to match with target's position, here we only need to adjust node self,
    // its children's positions are still determined by layout process.
    auto activeFrameRect = isNodeIn ? RectF(targetPos - parentPos, inNodeActiveFrameSize_) :
                                      RectF(targetPos - parentPos, geometryNode->GetFrameSize());
    auto activeCornerRadius = targetRenderContext->GetBorderRadius().value_or(BorderRadiusProperty());
    auto cornerRadius = renderContext->GetBorderRadius().value_or(BorderRadiusProperty());

    if (!isNodeIn) {
        // save outNode's target global frame rect for future compare to sync outNode with inNode's frame change
        outNodeTargetAbsRect_ = targetRect;
    } else if (target->IsRemoving()) {
        // notify backend for hierarchy processing to avoid outNode being shaded
        renderContext->RegisterSharedTransition(targetRenderContext);
    }

    AnimationUtils::AnimateWithCurrentOptions(
        [&]() {
            // sync geometry in active state
            renderContext->SetBorderRadius(activeCornerRadius);
            renderContext->SyncGeometryProperties(activeFrameRect);
            // sync geometry in identity state for inNode
            if (isNodeIn) {
                renderContext->SetBorderRadius(cornerRadius);
                renderContext->SyncGeometryProperties(RawPtr(geometryNode));
            }
            // draw self and children in sandbox which will not be affected by parent's transition
            renderContext->SetSandBox(parentPos);
        },
        [id = Container::CurrentId(), nodeWeak = WeakClaim(RawPtr(self))]() {
            ContainerScope scope(id);
            auto node = nodeWeak.Upgrade();
            CHECK_NULL_VOID(node);
            auto renderContext = node->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->SetSandBox(std::nullopt);
            LOGD("GeometryTransition: node %{public}d animation completed", node->GetId());
        },
        false);

    LOGD("GeometryTransition: node: %{public}d, parent: %{public}s, target: %{public}s, "
        "active frame: %{public}s, identity frame: %{public}s",
        self->GetId(), parentPos.ToString().c_str(), targetPos.ToString().c_str(),
        activeFrameRect.ToString().c_str(), isNodeIn ? geometryNode->GetFrameRect().ToString().c_str() : "no log");
}

RefPtr<FrameNode> CreateHolderNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto newNode = FrameNode::CreateFrameNode(
        node->GetTag(), ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    newNode->SetGeometryNode(node->GetGeometryNode()->Clone());
    auto frameSize = node->GetGeometryNode()->GetFrameSize();
    newNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(frameSize.Width()), CalcLength(frameSize.Height())));
    return newNode;
}

// For nodes without transition (still on the tree), but still need to follow the matched node which has
// transition (parameter is its transition direction).
bool GeometryTransition::OnFollowWithoutTransition(std::optional<bool> direction)
{
    CHECK_NULL_RETURN(followWithoutTransition_, false);
    if (!direction.has_value()) {
        auto inNode = inNode_.Upgrade();
        auto outNode = outNode_.Upgrade();
        CHECK_NULL_RETURN(holder_ && inNode && outNode, false);
        auto parent = holder_->GetParent();
        auto inRenderContext = inNode->GetRenderContext();
        auto outRenderContext = outNode->GetRenderContext();
        CHECK_NULL_RETURN(parent && inRenderContext && outRenderContext, false);
        parent->ReplaceChild(holder_, outNode);
        parent->RemoveDisappearingChild(outNode);
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        inRenderContext->UnregisterSharedTransition(outRenderContext);
        hasOutAnim_ = false;
        LOGD("GeometryTransition: follow cancelled, node %{public}d to %{public}d", holder_->GetId(), outNode->GetId());
        holder_ = nullptr;
        return false;
    }
    if (direction.value()) {
        auto outNode = outNode_.Upgrade();
        CHECK_NULL_RETURN(outNode, false);
        auto parent = outNode->GetParent();
        CHECK_NULL_RETURN(parent, false);
        holder_ = CreateHolderNode(outNode);
        CHECK_NULL_RETURN(holder_, false);
        RecordOutNodeFrame();
        parent->ReplaceChild(outNode, holder_);
        parent->AddDisappearingChild(outNode);
        MarkLayoutDirty(outNode, -1);
        hasOutAnim_ = true;
        LOGD("GeometryTransition: follow started, node %{public}d to %{public}d", outNode->GetId(), holder_->GetId());
    } else {
        auto inNode = inNode_.Upgrade();
        CHECK_NULL_RETURN(inNode && holder_, false);
        auto parent = holder_->GetParent();
        CHECK_NULL_RETURN(parent, false);
        parent->ReplaceChild(holder_, inNode);
        parent->RemoveDisappearingChild(inNode);
        state_ = State::ACTIVE;
        MarkLayoutDirty(inNode, 1);
        if (auto inNodeParent = inNode->GetAncestorNodeOfFrame()) {
            MarkLayoutDirty(inNodeParent);
        }
        hasInAnim_ = true;
        LOGD("GeometryTransition: follow ended, node %{public}d to %{public}d", holder_->GetId(), inNode->GetId());
        holder_ = nullptr;
    }
    return true;
}

bool GeometryTransition::IsParent(const WeakPtr<FrameNode>& parent, const WeakPtr<FrameNode>& child) const
{
    CHECK_NULL_RETURN(parent.Upgrade() && child.Upgrade(), false);
    RefPtr<UINode> node = child.Upgrade();
    while (node != nullptr) {
        if (AceType::DynamicCast<FrameNode>(node) == parent) {
            return true;
        }
        node = node->GetParent();
    }
    return false;
}

void GeometryTransition::RecordAnimationOption(const WeakPtr<FrameNode>& trigger, const AnimationOption& option)
{
    if (option.IsValid()) {
        if (IsParent(trigger, inNode_)) {
            animationOption_ = option;
        }
    } else if (NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption().IsValid()) {
        if (IsParent(trigger, inNode_)) {
            animationOption_ = NG::ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
        }
    } else {
        auto pipeline = PipelineBase::GetCurrentContext();
        if (pipeline && pipeline->GetSyncAnimationOption().IsValid() && IsParent(trigger, inNode_)) {
            animationOption_ = pipeline->GetSyncAnimationOption();
        }
    }
}

// during outNode animation is running target inNode's frame is changed, outNode needs to change as well to
// match tightly.
void GeometryTransition::OnReSync(const WeakPtr<FrameNode>& trigger, const AnimationOption& option)
{
    auto inNode = inNode_.Upgrade();
    auto outNode = outNode_.Upgrade();
    CHECK_NULL_VOID(!staticNodeAbsRect_ &&
        inNode && outNode && outNode->IsRemoving() && outNodeTargetAbsRect_ && outNodeTargetAbsRect_->IsValid());
    if (trigger.Upgrade()) {
        RecordAnimationOption(trigger, option);
        return;
    }
    auto inRenderContext = inNode->GetRenderContext();
    auto outRenderContext = outNode->GetRenderContext();
    CHECK_NULL_VOID(inRenderContext && outRenderContext && inRenderContext->IsSynced());
    auto inNodeParentPos = inNode->GetPaintRectGlobalOffsetWithTranslate(true);
    auto inNodeAbsRect = GetNodeAbsFrameRect(inNode, inNodeParentPos);
    auto inNodeAbsRectOld = outNodeTargetAbsRect_.value();
    CHECK_NULL_VOID(inNodeAbsRect != inNodeAbsRectOld);
    static constexpr int32_t defaultDuration = 100;
    auto animOption = animationOption_.IsValid() ? animationOption_ : AnimationOption(Curves::LINEAR, defaultDuration);
    AnimationUtils::Animate(animOption,
        [&]() {
            inRenderContext->SetSandBox(inNodeParentPos);
            if (inNodeAbsRect.GetSize() == inNodeAbsRectOld.GetSize()) {
                auto activeFrameRect = RectF(inNodeAbsRect.GetOffset() - outNodeParentPos_, inNodeAbsRect.GetSize());
                outRenderContext->SyncGeometryProperties(activeFrameRect);
                outNodeTargetAbsRect_ = inNodeAbsRect;
            } else {
                hasOutAnim_ = true;
                outNodeTargetAbsRect_.reset();
                MarkLayoutDirty(outNode);
            }
        },
        [id = Container::CurrentId(), inNodeWeak = WeakClaim(RawPtr(inNode)), outNodeWeak = WeakClaim(RawPtr(outNode)),
            geometryTransitionWeak = WeakClaim(this)]() {
            ContainerScope scope(id);
            auto geometryTransition = geometryTransitionWeak.Upgrade();
            auto inNode = inNodeWeak.Upgrade();
            CHECK_NULL_VOID(geometryTransition && inNode);
            auto inContext = inNode->GetRenderContext();
            CHECK_NULL_VOID(inContext);
            inContext->SetSandBox(std::nullopt, geometryTransition->inNode_ == inNode && !outNodeWeak.Upgrade());
        });
    LOGD("GeometryTransition: outNode: %{public}d %{public}s resyncs to inNode: %{public}d %{public}s, "
        "outAnim: %{public}d, option: %{public}d", outNode->GetId(), inNodeAbsRectOld.ToString().c_str(),
        inNode->GetId(), inNodeAbsRect.ToString().c_str(), hasOutAnim_, animationOption_.IsValid());
    animationOption_ = AnimationOption();
}

// if nodes with geometry transitions are added during layout, we need to execute additional layout in current frame
bool GeometryTransition::OnAdditionalLayout(const WeakPtr<FrameNode>& frameNode)
{
    bool ret = false;
    auto node = frameNode.Upgrade();
    CHECK_NULL_RETURN(node, false);
    if (IsNodeInAndActive(frameNode)) {
        auto parentNode = node->GetAncestorNodeOfFrame();
        if (parentNode) {
            MarkLayoutDirty(node);
            MarkLayoutDirty(parentNode);
            ret = true;
            LOGD("GeometryTransition: node: %{public}d, parent node: %{public}d is marked dirty",
                node->GetId(), parentNode->GetId());
        }
    } else if (IsNodeOutAndActive(frameNode)) {
        MarkLayoutDirty(node);
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
