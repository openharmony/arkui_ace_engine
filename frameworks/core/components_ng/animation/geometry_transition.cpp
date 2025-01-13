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
GeometryTransition::GeometryTransition(
    const std::string& id, bool followWithoutTransition, bool doRegisterSharedTransition) : id_(id),
    followWithoutTransition_(followWithoutTransition), doRegisterSharedTransition_(doRegisterSharedTransition) {}

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
    auto node = frameNode.Upgrade();
    CHECK_NULL_RETURN(node && IsInAndOutValid(), false);
    return node->GetLayoutPriority() != 0 && (node == inNode_ || node == outNode_);
}

bool GeometryTransition::IsNodeInAndActive(const WeakPtr<FrameNode>& frameNode) const
{
    return state_ == State::ACTIVE && hasInAnim_ && frameNode.Upgrade() == inNode_ && IsInAndOutValid();
}

bool GeometryTransition::IsNodeInAndIdentity(const WeakPtr<FrameNode>& frameNode) const
{
    return state_ == State::IDENTITY && hasInAnim_ && frameNode.Upgrade() == inNode_ && IsInAndOutValid();
}

bool GeometryTransition::IsNodeOutAndActive(const WeakPtr<FrameNode>& frameNode) const
{
    return hasOutAnim_ && frameNode.Upgrade() == outNode_ && IsInAndOutValid();
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
    auto parentGlobalOffset = parentPos.value_or(node->GetPaintRectGlobalOffsetWithTranslate(true).first);
    auto paintRect = renderContext->GetPaintRectWithTransform();
    return RectF(parentGlobalOffset + paintRect.GetOffset(), paintRect.GetSize());
}

void GeometryTransition::RecordOutNodeFrame()
{
    auto outNode = outNode_.Upgrade();
    CHECK_NULL_VOID(outNode);
    auto [val, err] = outNode->GetPaintRectGlobalOffsetWithTranslate(true);
    outNodeParentPos_ = val;
    outNodeParentHasScales_ = err;
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
    outNodeTargetAbsRect_.reset();
    isSynced_ = false;
    if (IsInAndOutEmpty()) {
        hasInAnim_ = false;
        hasOutAnim_ = false;
    }
    auto node = frameNode.Upgrade();
    CHECK_NULL_VOID(node && node->GetRenderContext() && !id_.empty());
    TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "build node: %{public}d, direction: %{public}d, onTree: %{public}d, "
        "removing: %{public}d, compid: %{public}s .", node->GetId(), isNodeIn, node->IsOnMainTree(),
        node->IsRemoving(), node->GetInspectorId().value_or("").c_str());
    if (!isNodeIn && (frameNode == inNode_ || frameNode == outNode_)) {
        SwapInAndOut(frameNode == inNode_);
        RecordOutNodeFrame();
        hasOutAnim_ = true;
    }
    if (isNodeIn && (frameNode != inNode_)) {
        auto inNode = inNode_.Upgrade();
        bool replace = true;
        if (inNode && !inNode->IsRemoving() && inNode->IsOnMainTree()) {
            std::string id = node->GetInspectorId().value_or("");
            replace = !id.empty() && id == inNode->GetInspectorId().value_or("");
        }
        SwapInAndOut(!replace);
        inNode_ = frameNode;
        bool isInAnimating = inNode && inNode->GetRenderContext() && inNode->GetRenderContext()->HasSandBox();
        CHECK_NULL_VOID(!(replace && isInAnimating));
        hasInAnim_ = true;
    }
    auto inNode = inNode_.Upgrade();
    auto outNode = outNode_.Upgrade();
    CHECK_NULL_VOID(inNode && outNode && (inNode != outNode));

    bool isImplicitAnimationOpen = AnimationUtils::IsImplicitAnimationOpen();
    bool follow = false;
    if (hasOutAnim_) {
        if (!hasInAnim_) {
            follow = OnFollowWithoutTransition(false);
        }
        hasOutAnim_ = isImplicitAnimationOpen || follow;
        if (hasOutAnim_) {
            MarkLayoutDirty(outNode, -1);
        }
    }
    if (hasInAnim_ && !follow) {
        if (!hasOutAnim_) {
            follow = OnFollowWithoutTransition(true);
        }
        if (isImplicitAnimationOpen || follow) {
            state_ = State::ACTIVE;
            MarkLayoutDirty(inNode, 1);
        } else {
            hasInAnim_ = false;
            inNode->SetLayoutPriority(0);
            inNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            inNode->GetGeometryNode()->SetFrameSize(SizeF());
        }
    }

    TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "inAnim: %{public}d, outAnim: %{public}d, follow: %{public}d, "
        "inNode: %{public}d, %{public}s, outNode: %{public}d, %{public}s", hasInAnim_, hasOutAnim_, follow,
        inNode->GetId(), inNode->GetTag().c_str(), outNode->GetId(), outNode->GetTag().c_str());
}

// Update should be called during node update phase when node exists
bool GeometryTransition::Update(const WeakPtr<FrameNode>& which, const WeakPtr<FrameNode>& value)
{
    bool ret = true;
    if (which.Upgrade() == inNode_.Upgrade()) {
        inNode_ = value;
    } else if (which.Upgrade() == outNode_.Upgrade()) {
        outNode_ = value;
    } else {
        ret = false;
    }
    auto whichNode = which.Upgrade();
    if (ret && whichNode && whichNode != value.Upgrade()) {
        whichNode->SetLayoutPriority(0);
    }
    return ret;
}

// Called before layout, perform layout constraints match modifications in active state to
// impact self and children's measure and layout.
void GeometryTransition::WillLayout(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper && layoutWrapper->IsRootMeasureNode());
    auto hostNode = layoutWrapper->GetHostNode();
    if (IsNodeInAndActive(hostNode)) {
        layoutPropertyIn_ = hostNode->GetLayoutProperty()->Clone();
        ModifyLayoutConstraint(layoutWrapper, true);
    } else if (IsNodeOutAndActive(hostNode) && !hasInAnim_) {
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
    std::optional<bool> direction;
    if (isRoot && IsNodeInAndActive(node)) {
        TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "node: %{public}d in and active", node->GetId());
        state_ = State::IDENTITY;
        auto geometryNode = node->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        inNodeActiveFrameSize_ = geometryNode->GetFrameSize();
        CHECK_NULL_VOID(layoutPropertyIn_);
        layoutPropertyIn_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        node->SetLayoutProperty(layoutPropertyIn_);
        layoutPropertyIn_.Reset();
    } else if (IsNodeInAndIdentity(node)) {
        TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "node: %{public}d in and identity", node->GetId());
        state_ = State::IDLE;
        direction = true;
        hasInAnim_ = false;
    } else if (isRoot && IsNodeOutAndActive(node)) {
        TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "node: %{public}d out and active, dependency check: %{public}d",
            node->GetId(), !hasInAnim_);
        if (hasInAnim_) {
            MarkLayoutDirty(node);
            return;
        }
        hasOutAnim_ = false;
        direction = false;
    }
    if (direction.has_value()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterLayoutTask([weak = WeakClaim(this), isNodeIn = direction.value()]() {
            auto geometryTransition = weak.Upgrade();
            CHECK_NULL_VOID(geometryTransition);
            geometryTransition->SyncGeometry(isNodeIn);
            if (!isNodeIn) {
                auto outNode = geometryTransition->outNode_.Upgrade();
                if (outNode && geometryTransition->layoutPropertyOut_) {
                    outNode->SetLayoutProperty(geometryTransition->layoutPropertyOut_);
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
    CHECK_NULL_VOID(self && target && layoutWrapper);
    // target's geometry is ensured ready to use because layout nodes are sorted to respect dependency,
    // the order is active inNode, normal layout, active outNode.
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    auto targetGeometryNode = target->GetGeometryNode();
    auto targetRenderContext = target->GetRenderContext();
    CHECK_NULL_VOID(targetRenderContext && targetGeometryNode && layoutProperty);
    SizeF size;
    if (isNodeIn) {
        staticNodeAbsRect_ =
            target->IsRemoving() ? std::nullopt : std::optional<RectF>(target->GetTransformRectRelativeToWindow());
        size = target->IsRemoving() ? outNodeSize_ : staticNodeAbsRect_->GetSize();
    } else {
        staticNodeAbsRect_ =
            !staticNodeAbsRect_ ? std::nullopt : std::optional<RectF>(target->GetTransformRectRelativeToWindow());
        size = staticNodeAbsRect_ ? staticNodeAbsRect_->GetSize() :
            (inNodeAbsRect_ ? inNodeAbsRect_->GetSize() : targetGeometryNode->GetFrameSize());
    }
    auto targetSize = CalcSize(NG::CalcLength(size.Width()), NG::CalcLength(size.Height()));
    layoutProperty->UpdateUserDefinedIdealSize(targetSize);
    TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "node: %{public}d modify size to: %{public}s",
        self->GetId(), targetSize.ToString().c_str());
    // if node has aspect ratio we'll ignore it in active state
    auto& magicItemProperty = layoutProperty->GetMagicItemProperty();
    if (magicItemProperty.HasAspectRatio()) {
        magicItemProperty.ResetAspectRatio();
    }
}

void GeometryTransition::SyncGeometry(bool isNodeIn)
{
    auto [self, target] = GetMatchedPair(isNodeIn);
    CHECK_NULL_VOID(self && target);
    auto renderContext = self->GetRenderContext();
    auto targetRenderContext = target->GetRenderContext();
    auto geometryNode = self->GetGeometryNode();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(renderContext && targetRenderContext && geometryNode && pipeline);
    // get own parent's global position, parent's transform is not taken into account other than translate
    auto parentPos = self->IsRemoving() ? outNodeParentPos_ : self->GetPaintRectGlobalOffsetWithTranslate(true).first;
    // get target's global position, target own transform is taken into account
    auto targetRect = target->IsRemoving() ? RectF(outNodePos_, outNodeSize_) :
        staticNodeAbsRect_.value_or(inNodeAbsRect_.value_or(GetNodeAbsFrameRect(target)));
    auto targetPos = targetRect.GetOffset();
    // adjust self's position to match with target's position, here we only need to adjust node self,
    // its children's positions are still determined by layout process.
    auto activeFrameRect = isNodeIn ? RectF(targetPos - parentPos, inNodeActiveFrameSize_) :
                                      RectF(targetPos - parentPos, geometryNode->GetFrameSize());
    auto activeCornerRadius = targetRenderContext->GetBorderRadius().value_or(BorderRadiusProperty());
    auto cornerRadius = renderContext->GetBorderRadius().value_or(BorderRadiusProperty());
    if (isNodeIn) {
        self->SetLayoutPriority(0);
        renderContext->SetFrameWithoutAnimation(activeFrameRect);
        if (target->IsRemoving()) {
            if (doRegisterSharedTransition_) {
                // notify backend for hierarchy processing
                renderContext->RegisterSharedTransition(targetRenderContext);
            }
        }
    } else {
        isSynced_ = true;
        outNodeTargetAbsRect_ = targetRect;
        if (staticNodeAbsRect_ && targetRenderContext->HasSandBox()) {
            staticNodeAbsRect_.reset();
            if (doRegisterSharedTransition_) {
                targetRenderContext->RegisterSharedTransition(renderContext);
            }
        }
    }
    auto propertyCallback = [&]() {
        // sync geometry in active state
        renderContext->SetBorderRadius(activeCornerRadius);
        renderContext->SyncGeometryProperties(activeFrameRect);
        // sync geometry in identity state for inNode
        if (isNodeIn) {
            renderContext->SetBorderRadius(cornerRadius);
            renderContext->SyncGeometryProperties(RawPtr(geometryNode));
        }
        // draw self and children in sandbox which will not be affected by parent's transition
        if (!isNodeIn && outNodeParentHasScales_) {
            renderContext->SetSandBox(std::nullopt, true);
        } else {
            renderContext->SetSandBox(parentPos);
        }
    };
    auto follow = followWithoutTransition_;
    auto finishCallback = [follow, nodeWeak = WeakClaim(RawPtr(self))]() {
        auto node = nodeWeak.Upgrade();
        CHECK_NULL_VOID(node);
        auto renderContext = node->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetSandBox(std::nullopt);
        TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "node %{public}d animation completed", node->GetId());
    };
    if (!isNodeIn && inNodeAbsRect_) {
        AnimationUtils::Animate(animationOption_, propertyCallback, finishCallback);
        inNodeAbsRect_.reset();
        animationOption_ = AnimationOption();
    } else {
        AnimationUtils::AnimateWithCurrentOptions(propertyCallback, finishCallback, false);
    }

    TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "node: %{public}d, parent: %{public}s, target: %{public}s, "
        "active frame: %{public}s, identity frame: %{public}s, option: %{public}d",
        self->GetId(), parentPos.ToString().c_str(), targetPos.ToString().c_str(), activeFrameRect.ToString().c_str(),
        isNodeIn ? geometryNode->GetFrameRect().ToString().c_str() : "no log",
        AnimationUtils::IsImplicitAnimationOpen());
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

void GeometryTransition::SyncGeometryPropertiesAfterLayout(const RefPtr<FrameNode>& syncNode)
{
    CHECK_NULL_VOID(syncNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask(
        [nodeWeak = WeakClaim(RawPtr(syncNode))]() {
            auto node = nodeWeak.Upgrade();
            CHECK_NULL_VOID(node);
            auto renderContext = node->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            auto geometryNode = node->GetGeometryNode();
            CHECK_NULL_VOID(geometryNode);
            renderContext->SyncGeometryProperties(RawPtr(geometryNode));
            renderContext->SetBorderRadius(renderContext->GetBorderRadius().value_or(BorderRadiusProperty()));
        }, true);
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
        TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "follow cancelled");
        holder_ = nullptr;
        SyncGeometryPropertiesAfterLayout(outNode);
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
        auto idx = parent->GetChildIndex(outNode);
        parent->ReplaceChild(outNode, holder_);
        parent->AddDisappearingChild(outNode, idx);
        MarkLayoutDirty(outNode, -1);
        hasOutAnim_ = true;
        TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "follow started");
    } else {
        auto inNode = inNode_.Upgrade();
        CHECK_NULL_RETURN(inNode && inNode->GetGeometryNode() && holder_, false);
        auto parent = holder_->GetParent();
        CHECK_NULL_RETURN(parent, false);
        parent->ReplaceChild(holder_, inNode);
        parent->RemoveDisappearingChild(inNode);
        state_ = State::ACTIVE;
        MarkLayoutDirty(inNode, 1);
        if (auto inNodeParent = inNode->GetAncestorNodeOfFrame(false)) {
            MarkLayoutDirty(inNodeParent);
        }
        hasInAnim_ = true;
        TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "follow ended");
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

void GeometryTransition::AnimateWithSandBox(const OffsetF& inNodeParentPos, bool inNodeParentHasScales,
    const std::function<void()>& propertyCallback, const AnimationOption& option)
{
    auto inNode = inNode_.Upgrade();
    CHECK_NULL_VOID(inNode);
    auto inRenderContext = inNode->GetRenderContext();
    CHECK_NULL_VOID(inRenderContext);
    AnimationUtils::Animate(option, [&]() {
        if (inRenderContext->HasSandBox()) {
            auto parent = inNode->GetAncestorNodeOfFrame(false);
            if (inNodeParentHasScales && parent) {
                inRenderContext->SetSandBox(parent->GetTransformRectRelativeToWindow().GetOffset());
            } else {
                inRenderContext->SetSandBox(inNodeParentPos);
            }
        }
        propertyCallback();
    }, [nodeWeak = WeakClaim(RawPtr(inNode))]() {
        auto node = nodeWeak.Upgrade();
        CHECK_NULL_VOID(node);
        auto renderContext = node->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (renderContext->HasSandBox()) {
            renderContext->SetSandBox(std::nullopt);
        }
        TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "node %{public}d resync animation completed", node->GetId());
    });
}

// during outNode animation is running target inNode's frame is changed, outNode needs to change as well to
// match tightly.
void GeometryTransition::OnReSync(const WeakPtr<FrameNode>& trigger, const AnimationOption& option)
{
    auto inNode = inNode_.Upgrade();
    auto outNode = outNode_.Upgrade();
    CHECK_NULL_VOID(isSynced_ && outNode && outNode->IsRemoving() && outNodeTargetAbsRect_ &&
        outNodeTargetAbsRect_->IsValid() && inNode && inNode->IsOnMainTree());
    auto inRenderContext = inNode->GetRenderContext();
    auto outRenderContext = outNode->GetRenderContext();
    CHECK_NULL_VOID(inRenderContext && outRenderContext);
    if (trigger.Upgrade()) {
        RecordAnimationOption(trigger, option);
        return;
    }
    OffsetF inNodeParentPos;
    bool inNodeParentHasScales = false;
    if (!staticNodeAbsRect_) {
        auto [val, err] = inNode->GetPaintRectGlobalOffsetWithTranslate(true);
        inNodeParentPos = val;
        inNodeParentHasScales = err;
    }
    auto inNodeAbsRect = staticNodeAbsRect_ || inNodeParentHasScales ?
        inNode->GetTransformRectRelativeToWindow() : GetNodeAbsFrameRect(inNode, inNodeParentPos);
    auto inNodeAbsRectOld = outNodeTargetAbsRect_.value();
    bool sizeChanged = GreatNotEqual(std::fabs(inNodeAbsRect.Width() - inNodeAbsRectOld.Width()), 1.0f) ||
        GreatNotEqual(std::fabs(inNodeAbsRect.Height() - inNodeAbsRectOld.Height()), 1.0f);
    bool posChanged = GreatNotEqual(std::fabs(inNodeAbsRect.GetX() - inNodeAbsRectOld.GetX()), 1.0f) ||
        GreatNotEqual(std::fabs(inNodeAbsRect.GetY() - inNodeAbsRectOld.GetY()), 1.0f);
    CHECK_NULL_VOID(sizeChanged || posChanged);
    auto animOption = animationOption_.IsValid() ? animationOption_ : AnimationOption(Curves::LINEAR, RESYNC_DURATION);
    auto propertyCallback = [&]() {
        if (!sizeChanged) {
            auto activeFrameRect = RectF(inNodeAbsRect.GetOffset() - outNodeParentPos_, inNodeAbsRect.GetSize());
            outRenderContext->SyncGeometryProperties(activeFrameRect);
            outNodeTargetAbsRect_ = inNodeAbsRect;
            animationOption_ = AnimationOption();
        } else {
            hasOutAnim_ = true;
            inNodeAbsRect_ = inNodeAbsRect;
            outNodeTargetAbsRect_.reset();
            MarkLayoutDirty(outNode);
            animationOption_ = animOption;
        }
    };
    AnimateWithSandBox(inNodeParentPos, inNodeParentHasScales, propertyCallback, animOption);
    TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "outNode: %{public}d %{public}s resyncs to inNode: %{public}d "
        "%{public}s, option: %{public}d, hasScales: %{public}d", outNode->GetId(), inNodeAbsRectOld.ToString().c_str(),
        inNode->GetId(), inNodeAbsRect.ToString().c_str(), animOption.GetDuration(), inNodeParentHasScales);
}

// if nodes with geometry transitions are added during layout, we need to execute additional layout in current frame
bool GeometryTransition::OnAdditionalLayout(const WeakPtr<FrameNode>& frameNode)
{
    bool ret = false;
    auto node = frameNode.Upgrade();
    CHECK_NULL_RETURN(node, false);
    if (IsNodeInAndActive(frameNode)) {
        auto parentNode = node->GetAncestorNodeOfFrame(false);
        if (parentNode) {
            MarkLayoutDirty(node);
            MarkLayoutDirty(parentNode);
            ret = true;
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
