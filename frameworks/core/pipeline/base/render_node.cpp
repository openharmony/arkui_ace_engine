/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/pipeline/base/render_node.h"

#include <algorithm>
#include <set>

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "core/components/box/render_box.h"
#include "core/components/common/properties/motion_path_evaluator.h"
#include "core/components/common/properties/motion_path_option.h"
#include "core/components/common/rotation/rotation_node.h"
#include "core/components/focus_animation/render_focus_animation.h"
#include "core/components/root/render_root.h"
#include "core/components/scroll/render_single_child_scroll.h"
#include "core/components/transform/render_transform.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline/base/component.h"
#include "render_service_client/core/transition/rs_transition.h"

namespace OHOS::Ace {
namespace {

constexpr float PRESS_KEYFRAME_START = 0.0f;
constexpr float PRESS_KEYFRAME_END = 1.0f;

struct ZIndexCompartor {
    bool operator()(const RefPtr<RenderNode>& left, const RefPtr<RenderNode>& right) const
    {
        return (left->GetZIndex() < right->GetZIndex());
    }
};

inline std::multiset<RefPtr<RenderNode>, ZIndexCompartor> SortChildrenByZIndex(
    const std::list<RefPtr<RenderNode>>& children)
{
    return std::multiset<RefPtr<RenderNode>, ZIndexCompartor>(children.begin(), children.end());
}

} // namespace

constexpr Dimension FOCUS_BOUNDARY = 4.0_vp; // focus padding + effect boundary, VP

RenderNode::RenderNode(bool takeBoundary) : takeBoundary_(takeBoundary) {}

void RenderNode::AddChild(const RefPtr<RenderNode>& child, int32_t slot)
{
    if (!child) {
        LOGW("Child MUST NOT be nullptr");
        return;
    }

    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        LOGW("RenderNode exist AddChild failed");
        return;
    }

    auto pos = children_.begin();
    std::advance(pos, slot);
    children_.insert(pos, child);
    child->SetParent(AceType::WeakClaim(this));
    child->SetDepth(GetDepth() + 1);
    OnChildAdded(child);
    disappearingNodes_.remove(child);
    child->NotifyTransition(TransitionType::APPEARING, child->GetNodeId());
    if (SystemProperties::GetRosenBackendEnabled()) {
        RSNodeAddChild(child);
    }
}

void RenderNode::RemoveChild(const RefPtr<RenderNode>& child)
{
    if (!child) {
        LOGW("Child MUST NOT be nullptr");
        return;
    }

    // ClearChildren() before RemoveChild() also need to NotifyTransition().
    if (!children_.empty()) {
        auto it = std::find(children_.begin(), children_.end(), child);
        if (it == children_.end()) {
            LOGW("Child is not in this render node");
            return;
        } else {
            children_.erase(it);
        }
    }
    OnChildRemoved(child);
    disappearingNodes_.remove(child);
    // check whether child has config transition or will cause child memory leak.
    auto context = context_.Upgrade();
    if (context && context->GetExplicitAnimationOption().IsValid() &&
        child->HasDisappearingTransition(child->GetNodeId())) {
        LOGD("RemoveChild with transition. [child]: tag: %s, nodeId: %d", child->GetTypeName(), child->GetNodeId());
        disappearingNodes_.emplace_back(child);
        child->SetParent(AceType::WeakClaim(this));
        child->NotifyTransition(TransitionType::DISAPPEARING, child->GetNodeId());
    }
    if (child->RSNode_) {
        child->RSNode_->NotifyTransition(Rosen::RSTransitionEffect::FADE_OUT);
    }
    LOGD("RenderNode RemoveChild %{public}zu", children_.size());
}

void RenderNode::MovePosition(int32_t slot)
{
    auto parentNode = GetParent().Upgrade();
    if (!parentNode) {
        LOGW("Invalid parent");
        return;
    }

    auto self = AceType::Claim(this);
    auto& children = parentNode->children_;
    auto it = children.end();
    if (slot >= 0 && static_cast<size_t>(slot) < children.size()) {
        it = children.begin();
        std::advance(it, slot);
        if (*it == this) {
            // Already at the right place
            return;
        }

        auto itSelf = std::find(it, children.end(), self);
        if (itSelf != children.end()) {
            children.erase(itSelf);
        } else {
            LOGW("Should NOT be here");
            children.remove(self);
            ++it;
        }
    } else {
        children.remove(self);
    }
    children.insert(it, self);
}

void RenderNode::ClearChildren()
{
    children_.clear();
}

void RenderNode::UpdateTouchRect()
{
    touchRect_ = GetPaintRect();
    auto box = AceType::DynamicCast<RenderBox>(this);
    // For exclude the margin area from touch area and the margin must not be less than zero.
    if (box && box->GetTouchArea().GetOffset().IsPositiveOffset()) {
        touchRect_.SetOffset(box->GetTouchArea().GetOffset() + touchRect_.GetOffset());
        touchRect_.SetSize(box->GetTouchArea().GetSize());
    }
    ownTouchRect_ = touchRect_;
    const auto& children = GetChildren();
    if (!children.empty()) {
        double minX = touchRect_.Left();
        double minY = touchRect_.Top();
        double maxX = touchRect_.Right();
        double maxY = touchRect_.Bottom();
        for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
            auto& child = *iter;
            if (child->GetTouchRect().GetSize().IsEmpty()) {
                continue;
            }
            minX = std::min(minX, child->GetTouchRect().Left() + GetPaintRect().Left());
            minY = std::min(minY, child->GetTouchRect().Top() + GetPaintRect().Top());
            maxX = std::max(maxX, child->GetTouchRect().Right() + GetPaintRect().Left());
            maxY = std::max(maxY, child->GetTouchRect().Bottom() + GetPaintRect().Top());
        }
        touchRect_.SetOffset({ minX, minY });
        touchRect_.SetSize({ maxX - minX, maxY - minY });
    }
    touchRect_ = GetTransformRect(touchRect_);
}

void RenderNode::MoveWhenOutOfViewPort(bool hasEffect)
{
    if (SystemProperties::GetDeviceType() != DeviceType::TV) {
        return;
    }

    Offset effectOffset;
    if (hasEffect) {
        effectOffset = Offset(NormalizeToPx(FOCUS_BOUNDARY), NormalizeToPx(FOCUS_BOUNDARY));
    }
    auto parentNode = GetParent().Upgrade();
    while (parentNode) {
        auto scroll = AceType::DynamicCast<RenderSingleChildScroll>(parentNode);
        if (scroll) {
            // do move then break
            scroll->MoveChildToViewPort(GetLayoutSize(), GetGlobalOffset(), effectOffset);
            break;
        } else {
            parentNode = parentNode->GetParent().Upgrade();
        }
    }
}

void RenderNode::DumpTree(int32_t depth)
{
    auto accessibilityNode = GetAccessibilityNode().Upgrade();
    int32_t nodeId = 0;
    if (accessibilityNode) {
        nodeId = accessibilityNode->GetNodeId();
    }
    const auto& children = GetChildren();
    if (DumpLog::GetInstance().GetDumpFile()) {
        auto dirtyRect = context_.Upgrade()->GetDirtyRect();
        DumpLog::GetInstance().AddDesc(std::string("AccessibilityNodeID: ").append(std::to_string(nodeId)));
        DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(depth)));
        DumpLog::GetInstance().AddDesc(
            std::string("DisappearingNodes: ").append(std::to_string(disappearingNodes_.size())));
        DumpLog::GetInstance().AddDesc(std::string("GlobalOffset: ").append(GetGlobalOffset().ToString()));
        DumpLog::GetInstance().AddDesc(std::string("PaintRect: ").append(paintRect_.ToString()));
        DumpLog::GetInstance().AddDesc(std::string("TouchRect: ").append(touchRect_.ToString()));
        DumpLog::GetInstance().AddDesc(std::string("DirtyRect: ").append(dirtyRect.ToString()));
        DumpLog::GetInstance().AddDesc(std::string("LayoutParam: ").append(layoutParam_.ToString()));
        DumpLog::GetInstance().AddDesc(
            std::string("MouseState: ").append(mouseState_ == MouseState::HOVER ? "HOVER" : "NONE"));
        Dump();
        DumpLog::GetInstance().Print(depth, AceType::TypeName(this), children.size());
    }

    for (const auto& item : children) {
        item->DumpTree(depth + 1);
    }
}

void RenderNode::Dump() {}

void RenderNode::RenderWithContext(RenderContext& context, const Offset& offset)
{
    MarkNeedWindowBlur(false);
    if (onLayoutReady_ && pendingDispatchLayoutReady_) {
        onLayoutReady_(std::string("\"layoutReady\",null,null"));
    }
    pendingDispatchLayoutReady_ = false;
    ClipHole(context, offset);
    Paint(context, offset);
    for (const auto& item : SortChildrenByZIndex(disappearingNodes_)) {
        PaintChild(item, context, offset);
    }

    if (needUpdateAccessibility_) {
        auto pipelineContext = context_.Upgrade();
        if (pipelineContext != nullptr) {
            pipelineContext->AddNeedRenderFinishNode(AceType::Claim(this));
        }
    }
    CheckIfNeedUpdateTouchRect();
    SetNeedRender(false);
}

void RenderNode::NotifyPaintFinish()
{
    bool hasObserver = false;
    auto accessNode = accessibilityNode_.Upgrade();
    if (accessNode) {
        auto index = accessNode->GetNodeId();
        auto pipeline = context_.Upgrade();
        hasObserver = pipeline ? pipeline->IsVisibleChangeNodeExists(index) : false;
    }
    if (needUpdateAccessibility_ || hasObserver) {
        for (auto& child : children_) {
            child->NotifyPaintFinish();
        }
        auto pipelineContext = context_.Upgrade();
        if (pipelineContext != nullptr) {
            pipelineContext->AddNeedRenderFinishNode(AceType::Claim(this));
        }
    }
}

void RenderNode::Paint(RenderContext& context, const Offset& offset)
{
    const auto& children = GetChildren();
    for (const auto& item : SortChildrenByZIndex(children)) {
        PaintChild(item, context, offset);
    }
}

void RenderNode::PaintChild(const RefPtr<RenderNode>& child, RenderContext& context, const Offset& offset)
{
    if (child && child->GetVisible()) {
        context.PaintChild(child, offset);
    }
}

void RenderNode::ClipHole(RenderContext& context, const Offset& offset)
{
    LOGD("Hole: PrePaint RenderNode");
    auto pipelineContext = GetContext().Upgrade();

    if (pipelineContext && pipelineContext->GetIsHoleValid()) {
        if (!(pipelineContext->GetHasClipHole())) {
            if (!(pipelineContext->GetHasMeetSubWindowNode())) {
                context.ClipHoleBegin(pipelineContext->GetTransparentHole());
                pipelineContext->SetHasClipHole(true);
            } else {
                LOGI("Hole: hole status is wrong.");
            }
        } else {
            if (!(pipelineContext->GetHasMeetSubWindowNode())) {
                if (GetHasSubWindow()) {
                    context.ClipHoleEnd();
                    pipelineContext->SetHasMeetSubWindowNode(true);
                } else {
                    LOGI("Hole: RenderNode has not SubWindow.");
                }
            } else {
                LOGI("Hole: now clip has done.");
            }
        }
    } else {
        LOGD("Hole: hole is not valid.");
    }
}

void RenderNode::MarkNeedLayout(bool selfOnly, bool forceParent)
{
    bool addSelf = false;
    auto context = context_.Upgrade();
    if (context != nullptr) {
        context->ForceLayoutForImplicitAnimation();
    }

    bool forceSelf = forceParent && AceType::InstanceOf<RenderRoot>(this);
    if (forceSelf) {
        // This is root and child need force parent layout.
        SetNeedLayout(true);
        addSelf = true;
    } else if (forceParent) {
        // Force mark self and all ancestors need layout.
        SetNeedLayout(true);
        auto parent = parent_.Upgrade();
        if (parent && parent->CheckIfNeedLayoutAgain()) {
            parent->MarkNeedLayout(false, forceParent);
        } else {
            addSelf = true;
        }
    } else if (!needLayout_) {
        SetNeedLayout(true);
        if ((IsTakenBoundary() || selfOnly) && !MarkNeedRenderSpecial()) {
            addSelf = true;
        } else {
            auto parent = parent_.Upgrade();
            if (parent && parent->CheckIfNeedLayoutAgain()) {
                parent->MarkNeedLayout();
            } else {
                addSelf = true;
            }
        }
    }
    if (addSelf) {
        auto pipelineContext = context_.Upgrade();
        if (pipelineContext != nullptr) {
            pipelineContext->AddDirtyLayoutNode(AceType::Claim(this));
        }
    }
}

void RenderNode::MarkNeedPredictLayout()
{
    auto pipelineContext = context_.Upgrade();
    if (pipelineContext) {
        pipelineContext->AddPredictLayoutNode(AceType::Claim(this));
    }
}

void RenderNode::OnLayout()
{
    auto parent = parent_.Upgrade();
    if (parent) {
        Size parentViewPort = parent->GetChildViewPort();
        if (viewPort_ != parentViewPort) {
            viewPort_ = parentViewPort;
            needLayout_ = true;
        }
    }
    if (NeedLayout()) {
        PrepareLayout();
        PerformLayout();
        layoutParamChanged_ = false;
        SetNeedLayout(false);
        pendingDispatchLayoutReady_ = true;
        MarkNeedRender();
    }
}

void RenderNode::PrepareLayout() {}

void RenderNode::SetPosition(const Offset& offset)
{
    Offset selfOffset;
    if (positionParam_.left.second) {
        selfOffset.SetX(NormalizePercentToPx(positionParam_.left.first, false));
    } else if (positionParam_.right.second) {
        selfOffset.SetX(-NormalizePercentToPx(positionParam_.right.first, false));
    } else {
        selfOffset.SetX(0);
    }
    selfOffset.SetX(selfOffset.GetX() - NormalizePercentToPx(positionParam_.anchor.first, false, true));
    if (positionParam_.top.second) {
        selfOffset.SetY(NormalizePercentToPx(positionParam_.top.first, true));
    } else if (positionParam_.bottom.second) {
        selfOffset.SetY(-NormalizePercentToPx(positionParam_.bottom.first, true));
    } else {
        selfOffset.SetY(0);
    }
    selfOffset.SetY(selfOffset.GetY() - NormalizePercentToPx(positionParam_.anchor.second, true, true));
    selfOffset_ = selfOffset;
    SetPositionInternal(selfOffset + offset);
}

void RenderNode::Attach(const WeakPtr<PipelineContext>& context)
{
    context_ = context;
    OnAttachContext();
    paintX_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        auto render = weak.Upgrade();
        if (!render) {
            return;
        }
        auto parent = render->GetParent().Upgrade();
        if (!parent) {
            return;
        }
        parent->MarkNeedRender();
        render->needUpdateTouchRect_ = true;
        render->nonStrictPaintRect_.SetLeft(render->paintX_.Value());
        render->OnGlobalPositionChanged();
    });

    paintY_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        auto render = weak.Upgrade();
        if (!render) {
            return;
        }
        auto parent = render->GetParent().Upgrade();
        if (!parent) {
            return;
        }
        parent->MarkNeedRender();
        render->needUpdateTouchRect_ = true;
        render->nonStrictPaintRect_.SetTop(render->paintY_.Value());
        render->OnGlobalPositionChanged();
    });

    paintW_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        auto render = weak.Upgrade();
        if (!render) {
            return;
        }
        render->MarkNeedRender();
        render->needUpdateTouchRect_ = true;
        render->nonStrictPaintRect_.SetWidth(render->paintW_.Value());
        render->transitionPaintRectSize_.SetWidth(render->paintW_.Value());
        render->MarkNeedSyncGeometryProperties();
    });

    paintH_.SetContextAndCallback(context_, [weak = WeakClaim(this)] {
        auto render = weak.Upgrade();
        if (!render) {
            return;
        }
        render->MarkNeedRender();
        render->needUpdateTouchRect_ = true;
        render->nonStrictPaintRect_.SetHeight(render->paintH_.Value());
        render->transitionPaintRectSize_.SetHeight(render->paintH_.Value());
        render->MarkNeedSyncGeometryProperties();
    });
}

void RenderNode::SetPositionInternal(const Offset& offset)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Set position internal failed. context is null.");
        return;
    }
    if (paintRect_.GetOffset() != offset) {
        isFirstPositionAssign_ = false;
        nonStrictOption_ = context->GetExplicitAnimationOption();
        context->AddLayoutTransitionNode(AceType::Claim(this));
        paintRect_.SetOffset(offset);
        needUpdateTouchRect_ = true;
        OnPositionChanged();
        OnGlobalPositionChanged();
        MarkNeedSyncGeometryProperties();
    }
    if (isFirstPositionAssign_) {
        isFirstPositionAssign_ = false;
        nonStrictOption_ = context->GetExplicitAnimationOption();
        context->AddLayoutTransitionNode(AceType::Claim(this));
    }
}

void RenderNode::CheckIfNeedUpdateTouchRect()
{
    auto parent = parent_.Upgrade();
    if (!parent) {
        return;
    }
    parent->MarkNeedUpdateTouchRect(true);
    parent->CheckIfNeedUpdateTouchRect();
}

void RenderNode::CreateMouseAnimation(RefPtr<KeyframeAnimation<Color>>& animation, const Color& from, const Color& to)
{
    if (!animation) {
        return;
    }
    auto colorFrameStart = AceType::MakeRefPtr<Keyframe<Color>>(PRESS_KEYFRAME_START, from);
    auto colorFrameEnd = AceType::MakeRefPtr<Keyframe<Color>>(PRESS_KEYFRAME_END, to);
    colorFrameEnd->SetCurve(Curves::SHARP);
    animation->AddKeyframe(colorFrameStart);
    animation->AddKeyframe(colorFrameEnd);
    animation->AddListener([weakNode = AceType::WeakClaim(this)](const Color& value) {
        auto node = weakNode.Upgrade();
        if (node) {
            node->eventEffectColor_ = value;
            if (node->hoveAndPressCallback_) {
                node->hoveAndPressCallback_(value);
            }
            node->MarkNeedRender();
        }
    });
}

bool RenderNode::MarkNeedRenderSpecial()
{
    return false;
}

void RenderNode::MarkNeedRender(bool overlay)
{
    if (!needRender_) {
        SetNeedRender(true);
        if (IsRepaintBoundary()) {
            auto pipelineContext = context_.Upgrade();
            if (pipelineContext) {
                pipelineContext->AddDirtyRenderNode(AceType::Claim(this), overlay);
            }
        } else {
            auto parent = parent_.Upgrade();
            if (parent) {
                parent->MarkNeedRender();
            }
        }
    }
}

bool RenderNode::TouchTest(const Point& globalPoint, const Point& parentLocalPoint, const TouchRestrict& touchRestrict,
    TouchTestResult& result)
{
    LOGD("OnTouchTest: type is %{public}s, the region is %{public}lf, %{public}lf, %{public}lf, %{public}lf",
        GetTypeName(), GetTouchRect().Left(), GetTouchRect().Top(), GetTouchRect().Width(), GetTouchRect().Height());
    LOGD("OnTouchTest: the local point refer to parent is %{public}lf, %{public}lf, ", parentLocalPoint.GetX(),
        parentLocalPoint.GetY());
    if (disableTouchEvent_ || disabled_) {
        return false;
    }

    Point transformPoint = GetTransformPoint(parentLocalPoint);
    // Since the paintRect is relative to parent, use parent local point to perform touch test.
    if (!GetTouchRect().IsInRegion(transformPoint)) {
        return false;
    }

    // Calculates the local point location in this node.
    const auto localPoint = transformPoint - GetPaintRect().GetOffset();
    bool dispatchSuccess = false;
    const auto& sortedChildern = SortChildrenByZIndex(GetChildren());
    if (IsChildrenTouchEnable()) {
        for (auto iter = sortedChildern.rbegin(); iter != sortedChildern.rend(); ++iter) {
            auto& child = *iter;
            if (!child->GetVisible() || child->disabled_ || child->disableTouchEvent_) {
                continue;
            }
            if (child->TouchTest(globalPoint, localPoint, touchRestrict, result)) {
                dispatchSuccess = true;
                break;
            }
            if (child->InterceptTouchEvent() || IsExclusiveEventForChild()) {
                auto localTransformPoint = child->GetTransformPoint(localPoint);
                if (child->GetTouchRect().IsInRegion(localTransformPoint)) {
                    dispatchSuccess = true;
                    break;
                }
            }
        }
    }
    auto beforeSize = result.size();
    if (touchable_ && GetOwnTouchRect().IsInRegion(transformPoint)) {
        // Calculates the coordinate offset in this node.
        const auto coordinateOffset = globalPoint - localPoint;
        globalPoint_ = globalPoint;
        OnTouchTestHit(coordinateOffset, touchRestrict, result);
    }
    auto endSize = result.size();
    return dispatchSuccess || beforeSize != endSize;
}

RefPtr<RenderNode> RenderNode::FindDropChild(const Point& globalPoint, const Point& parentLocalPoint)
{
    Point transformPoint = GetTransformPoint(parentLocalPoint);
    if (!GetTouchRect().IsInRegion(transformPoint)) {
        return nullptr;
    }

    // Calculates the local point location in this node.
    const auto localPoint = transformPoint - GetPaintRect().GetOffset();
    const auto& children = GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        if (!child->GetVisible()) {
            continue;
        }

        if (child->InterceptTouchEvent()) {
            continue;
        }

        auto target = child->FindDropChild(globalPoint, localPoint);
        if (target) {
            return target;
        }
    }

    if (GetOwnTouchRect().IsInRegion(transformPoint)) {
        RefPtr<RenderNode> renderNode = AceType::Claim<RenderNode>(this);
        auto renderBox = AceType::DynamicCast<RenderBox>(renderNode);
        if (renderBox && renderBox->GetOnDrop()) {
            return renderNode;
        }
    }

    return nullptr;
}

void RenderNode::MouseTest(const Point& globalPoint, const Point& parentLocalPoint, MouseTestResult& result)
{
    LOGD("MouseTest: type is %{public}s, the region is %{public}lf, %{public}lf, %{public}lf, %{public}lf",
        GetTypeName(), GetTouchRect().Left(), GetTouchRect().Top(), GetTouchRect().Width(), GetTouchRect().Height());
    LOGD("MouseTest: the local point refer to parent is %{public}lf, %{public}lf, ", parentLocalPoint.GetX(),
        parentLocalPoint.GetY());

    // Since the paintRect is relative to parent, use parent local point to perform touch test.
    if (GetTouchRect().IsInRegion(parentLocalPoint)) {
        // Calculates the local point location in this node.
        const auto localPoint = parentLocalPoint - paintRect_.GetOffset();
        const auto& children = GetChildren();
        for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
            auto& child = *iter;
            child->MouseTest(globalPoint, localPoint, result);
        }
        // Calculates the coordinate offset in this node.
        const auto coordinateOffset = globalPoint - localPoint;
        globalPoint_ = globalPoint;
        OnMouseTestHit(coordinateOffset, result);
    }
}

bool RenderNode::HandleMouseHoverEvent(MouseState mouseState)
{
    return true;
}

bool RenderNode::MouseHoverTest(const Point& parentLocalPoint)
{
    LOGD("OnMouseHoverTest: type is %{public}s, the region is %{public}lf, %{public}lf, %{public}lf, %{public}lf",
        GetTypeName(), GetTouchRect().Left(), GetTouchRect().Top(), GetTouchRect().Width(), GetTouchRect().Height());
    LOGD("OnMouseHoverTest: the local point refer to parent is %{public}lf, %{public}lf, ", parentLocalPoint.GetX(),
        parentLocalPoint.GetY());
    if (disabled_) {
        return false;
    }

    Point transformPoint = GetTransformPoint(parentLocalPoint);
    const auto localPoint = transformPoint - paintRect_.GetOffset();
    // Since the paintRect is relative to parent, use parent local point to perform touch test.
    if (GetTouchRect().IsInRegion(transformPoint)) {
        auto context = context_.Upgrade();
        if (!context) {
            return false;
        }
        hoverChildren_.clear();
        context->AddToHoverList(AceType::WeakClaim(this).Upgrade());
        const auto& children = GetChildren();
        for (auto iter = children.begin(); iter != children.end(); ++iter) {
            auto& child = *iter;
            if (child->MouseHoverTest(localPoint)) {
                hoverChildren_.emplace_back(child);
            }
        }
        // mouse state of the node is from NONE to HOVER, the callback of hover enter is triggered.
        if (mouseState_ == MouseState::NONE) {
            if (hoverAnimationType_ == HoverAnimationType::AUTO) {
                OnMouseHoverEnterTest();
            } else {
                MouseHoverEnterTest();
            }
            mouseState_ = MouseState::HOVER;
            HandleMouseHoverEvent(MouseState::HOVER);
        }
        return true;
    } else {
        for (const auto& child : hoverChildren_) {
            child->MouseHoverTest(localPoint);
        }
        // mouse state of the node is from HOVER to NONE, the callback of hover exit is triggered.
        if (mouseState_ == MouseState::HOVER) {
            if (hoverAnimationType_ == HoverAnimationType::AUTO) {
                OnMouseHoverExitTest();
            } else {
                MouseHoverExitTest();
            }
            mouseState_ = MouseState::NONE;
            HandleMouseHoverEvent(MouseState::NONE);
        }
        return false;
    }
}

#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
void RenderNode::SetAccessibilityRect(const Rect& rect)
{
    Rect parentRect = rect;
    if (!selfOffset_.IsZero()) {
        parentRect.SetOffset(parentRect.GetOffset() + selfOffset_);
    }
    auto node = accessibilityNode_.Upgrade();
    auto content = context_.Upgrade();
    Rect currentRect = Rect(GetGlobalOffset(), GetLayoutSize());
    Rect clampRect = currentRect.Constrain(parentRect);
    if (node && content) {
        if (clampRect.IsValid()) {
            auto size = Size(clampRect.Width(), clampRect.Height()) * content->GetViewScale();
            node->SetGlobalRect(currentRect * content->GetViewScale());
            if (size.Width() > node->GetWidth() || size.Height() > node->GetHeight()) {
                // Same AccessibilityNode update the largest size.
                node->SetWidth(size.Width());
                node->SetHeight(size.Height());
                node->SetLeft(clampRect.Left() * content->GetViewScale());
                node->SetTop(clampRect.Top() * content->GetViewScale());
            } else if (NearEqual(size.Width(), node->GetWidth()) && NearEqual(size.Height(), node->GetHeight())) {
                // Update the offset when same size.
                node->SetLeft(clampRect.Left() * content->GetViewScale());
                node->SetTop(clampRect.Top() * content->GetViewScale());
            }
            if (node->GetTag() == "tab-bar") {
                return;
            }
        } else {
            SetAccessibilityVisible(false);
        }
    }
}
#else
void RenderNode::SetAccessibilityRect(const Rect& rect)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }
    if (!pipelineContext->IsAccessibilityEnabled()) {
        return;
    }
    Rect parentRect = rect;
    if (!selfOffset_.IsZero()) {
        parentRect.SetOffset(parentRect.GetOffset() + selfOffset_);
    }
    auto node = accessibilityNode_.Upgrade();
    auto content = context_.Upgrade();
    Rect currentRect = Rect(GetGlobalOffset(), GetLayoutSize());
    Rect clampRect = currentRect.Constrain(parentRect);
    if (node && content) {
        node->SetGlobalRect(currentRect * content->GetViewScale());
        if (clampRect.IsValid()) {
            node->SetRect(clampRect * content->GetViewScale());
        } else {
            SetAccessibilityVisible(false);
        }
    }
    if (clampRect.IsValid()) {
        for (auto& child : children_) {
            // Fix case: child size is empty but access node is not empty.
            auto childAccessNode = child->GetAccessibilityNode().Upgrade();
            if (childAccessNode) {
                auto childAccessGlobalRect = childAccessNode->GetGlobalRect();
                if (childAccessGlobalRect.IsValid() && !child->GetPaintRect().IsValid()) {
                    continue;
                }
            }
            child->SetAccessibilityRect(clampRect);
        }
    }
}
#endif

bool RenderNode::RotationMatchTest(const RefPtr<RenderNode>& requestRenderNode)
{
    RotationNode* rotationNode = AceType::DynamicCast<RotationNode>(this);
    if ((rotationNode != nullptr) && requestRenderNode == this) {
        LOGD("RotationMatchTest: match rotation focus node %{public}s.", GetTypeName());
        return true;
    }
    const auto& children = GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        const auto& child = *iter;
        if (child && child->RotationMatchTest(requestRenderNode)) {
            return true;
        }
    }

    return false;
}

bool RenderNode::RotationTest(const RotationEvent& event)
{
    if (disabled_) {
        return false;
    }

    const auto& children = GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        const auto& child = *iter;
        if (child && child->RotationTest(event)) {
            return true;
        }
    }

    RotationNode* rotationNode = AceType::DynamicCast<RotationNode>(this);
    if ((rotationNode != nullptr) && rotationNode->OnRotation(event)) {
        LOGD("RotationTest: type is %{public}s accept", GetTypeName());
        return true;
    }

    return false;
}

bool RenderNode::RotationTestForward(const RotationEvent& event)
{
    RotationNode* rotationNode = AceType::DynamicCast<RotationNode>(this);
    if ((rotationNode != nullptr) && rotationNode->OnRotation(event)) {
        LOGD("RotationTestForward: type is %{public}s accept", GetTypeName());
        return true;
    }
    const auto& children = GetChildren();
    for (auto iter = children.begin(); iter != children.end(); ++iter) {
        const auto& child = *iter;
        if (child && child->RotationTestForward(event)) {
            return true;
        }
    }

    return false;
}

double RenderNode::GetBaselineDistance(TextBaseline textBaseline)
{
    if (GetChildren().empty()) {
        return GetLayoutSize().Height();
    }
    return GetHighestChildBaseline(textBaseline);
}

Size RenderNode::GetContentSize()
{
    if (GetChildren().empty()) {
        return Size();
    }
    return GetLargestChildContentSize();
}

bool RenderNode::ScrollPageByChild(Offset& delta, int32_t source)
{
    RefPtr<RenderNode> parent = GetParent().Upgrade();
    if (parent) {
        return parent->ScrollPageByChild(delta, source);
    }
    return true;
}

double RenderNode::GetHighestChildBaseline(TextBaseline baseline)
{
    double distance = 0.0;
    for (const auto& child : children_) {
        double childBaseline = child->GetBaselineDistance(baseline);
        childBaseline += child->GetPosition().GetY();
        distance = NearZero(distance) ? childBaseline : std::min(distance, childBaseline);
    }
    return distance;
}

Size RenderNode::GetLargestChildContentSize()
{
    Size maxSize;
    for (const auto& child : children_) {
        Size childSize = child->GetContentSize();
        if (!childSize.IsValid()) {
            continue;
        }
        maxSize.SetWidth(maxSize.Width() > childSize.Width() ? maxSize.Width() : childSize.Width());
        maxSize.SetHeight(maxSize.Height() > childSize.Height() ? maxSize.Height() : childSize.Height());
    }
    return maxSize;
}

double RenderNode::GetFirstChildBaseline(TextBaseline baseline)
{
    double distance = GetLayoutSize().Height();
    if (!GetChildren().empty()) {
        auto firstChild = GetChildren().front();
        distance = firstChild->GetBaselineDistance(baseline);
        distance += firstChild->GetPosition().GetY();
    }
    return distance;
}

double RenderNode::NormalizeToPx(Dimension dimension) const
{
    if (dimension.Unit() == DimensionUnit::PX) {
        return dimension.Value();
    }
    auto context = context_.Upgrade();
    ACE_DCHECK(context);
    if (!context) {
        return dimension.Value();
    }
    return context->NormalizeToPx(dimension);
}

double RenderNode::NormalizePercentToPx(const Dimension& dimension, bool isVertical, bool referSelf) const
{
    if (dimension.Unit() != DimensionUnit::PERCENT) {
        return NormalizeToPx(dimension);
    }
    Size referSize;
    if (referSelf) {
        referSize = GetLayoutSize();
    } else {
        auto parent = parent_.Upgrade();
        if (!parent) {
            referSize = GetLayoutParam().GetMaxSize();
        } else {
            if (positionParam_.type == PositionType::OFFSET) {
                referSize = parent->GetLayoutSize();
            } else {
                referSize = parent->GetLayoutParam().GetMaxSize();
            }
            if (referSize > viewPort_) {
                referSize = viewPort_;
            }
        }
    }
    auto limit = isVertical ? referSize.Height() : referSize.Width();
    return limit * dimension.Value();
}

Offset RenderNode::GetOffsetFromOrigin(const Offset& offset) const
{
    auto parent = parent_.Upgrade();
    if (!parent) {
        return offset;
    }
    Offset nowOffset = GetPosition();
    return parent->GetOffsetFromOrigin(offset + nowOffset);
}

Offset RenderNode::GetGlobalOffset() const
{
    auto renderNode = parent_.Upgrade();
    return renderNode ? GetPosition() + renderNode->GetGlobalOffset() : GetPosition();
}

Offset RenderNode::GetPaintOffset() const
{
    auto renderNode = parent_.Upgrade();
    return (renderNode && !IsHeadRenderNode()) ? GetPosition() + renderNode->GetPaintOffset() : GetPosition();
}

Offset RenderNode::GetGlobalOffsetExternal() const
{
    auto renderNode = parent_.Upgrade();
    return renderNode ? GetPosition() + renderNode->GetGlobalOffsetExternal() : GetPosition();
}

bool RenderNode::IsVisible(const Rect& rect, bool totally) const
{
    Rect intersectRect = Rect(Offset(), GetLayoutSize());
    bool visible = totally ? rect.IsWrappedBy(intersectRect) : rect.IsIntersectWith(intersectRect);
    if (!visible) {
        return false;
    }
    auto parent = parent_.Upgrade();
    if (!parent) {
        return true;
    }
    return parent->IsVisible(rect + GetPosition());
}

RefPtr<RenderNode> RenderNode::GetLastChild() const
{
    if (children_.empty()) {
        return nullptr;
    }
    return children_.back();
}

RefPtr<RenderNode> RenderNode::GetFirstChild() const
{
    if (children_.empty()) {
        return nullptr;
    }
    return children_.front();
}

void RenderNode::UpdateAccessibilityPosition()
{
    const auto& context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto viewScale = context->GetViewScale();
    if (NearZero(viewScale)) {
        return;
    }

    auto accessibilityNode = GetAccessibilityNode().Upgrade();
    if (!accessibilityNode) {
        return;
    }

    Size size = GetLayoutSize();
    Offset globalOffset = GetGlobalOffset();
    PositionInfo positionInfo = { (size.Width()) * viewScale, (size.Height()) * viewScale,
        (globalOffset.GetX()) * viewScale, (globalOffset.GetY()) * viewScale };
    accessibilityNode->SetPositionInfo(positionInfo);
}

void RenderNode::UpdateAll(const RefPtr<Component>& component)
{
    if (!component) {
        LOGE("fail to update all due to component is null");
        return;
    }
    touchable_ = component->IsTouchable();
    disabled_ = component->IsDisabledStatus();
    auto renderComponent = AceType::DynamicCast<RenderComponent>(component);
    if (renderComponent) {
        motionPathOption_ = renderComponent->GetMotionPathOption();
        if (SystemProperties::GetRosenBackendEnabled() && motionPathOption_.IsValid()) {
            if (auto rsNode = GetRSNode()) {
                rsNode->SetMotionPathOption(motionPathOption_.ToNativeMotionPathOption());
            }
        }

        positionParam_ = renderComponent->GetPositionParam();
        flexWeight_ = renderComponent->GetFlexWeight();
        displayIndex_ = renderComponent->GetDisplayIndex();
        isIgnored_ = renderComponent->IsIgnored();
        interceptTouchEvent_ = renderComponent->InterceptEvent();
        if (renderComponent->IsCustomComponent()) {
            onLayoutReady_ =
                AceAsyncEvent<void(const std::string&)>::Create(renderComponent->GetOnLayoutReadyMarker(), context_);
        }
    }
    auto context = context_.Upgrade();
    if (context != nullptr) {
        minPlatformVersion_ = context->GetMinPlatformVersion();
    }
    SetZIndex(renderComponent->GetZIndex());
    isPercentSize_ = renderComponent->GetIsPercentSize();
    UpdatePropAnimation(component->GetAnimatables());
    Update(component);
    MarkNeedLayout();
}

void RenderNode::UpdateOpacity(uint8_t opacity)
{
    if (!SupportOpacity()) {
        return;
    }
    if (opacity_ != opacity) {
        opacity_ = opacity;
        if (auto rsNode = GetRSNode()) {
            rsNode->SetAlpha(opacity_ / 255.0);
        } else {
            MarkNeedRender();
        }
    }
}

RenderNode::OpacityCallback RenderNode::GetOpacityCallback(int32_t domId)
{
    if (domId != GetNodeId()) {
        return nullptr;
    }
    if (!SupportOpacity()) {
        return nullptr;
    }
    return [weak = AceType::WeakClaim(this)](uint8_t opacity) {
        auto render = weak.Upgrade();
        if (render) {
            render->UpdateOpacity(opacity);
        }
    };
}

void RenderNode::GetDomOpacityCallbacks(int32_t domId, std::list<OpacityCallback>& result)
{
    if (domId != GetNodeId()) {
        return;
    }
    auto callback = GetOpacityCallback(domId);
    if (callback) {
        result.emplace_back(callback);
    }
    for (auto& child : children_) {
        child->GetDomOpacityCallbacks(domId, result);
    }
}

int32_t RenderNode::GetNodeId() const
{
    return GetAccessibilityNodeId();
}

uint8_t RenderNode::GetOpacity() const
{
    return opacity_;
}

bool RenderNode::SupportOpacity()
{
    return false;
}

Offset RenderNode::GetOffsetToPage() const
{
    auto offset = GetGlobalOffset();
    auto context = GetContext().Upgrade();
    if (context) {
        offset = offset - context->GetPageRect().GetOffset();
    }
    return offset;
}

void RenderNode::ClearRenderObject()
{
    context_ = nullptr;
    viewPort_ = Size();
    globalPoint_ = Point();
    touchRect_ = Rect();
    accessibilityNode_ = nullptr;
    needUpdateAccessibility_ = true;
    disabled_ = false;
    positionParam_ = PositionParam();
    opacity_ = 255;
    interceptTouchEvent_ = false;
    mouseState_ = MouseState::NONE;

    ClearChildren();
    RSNode_ = nullptr;
    isHeadRenderNode_ = false;
    isTailRenderNode_ = false;
    accessibilityText_ = "";
    layoutParam_ = LayoutParam();
    paintRect_ = Rect();
    paintX_ = Dimension();
    paintY_ = Dimension();
    paintW_ = Dimension();
    paintH_ = Dimension();
    nonStrictPaintRect_ = Rect();
    transitionPaintRectSize_ = Size();
    isFirstSizeAssign_ = true;
    isFirstPositionAssign_ = true;
    disappearingNodes_.clear();
    parent_ = nullptr;
    depth_ = 0;
    needRender_ = false;
    needLayout_ = false;
    visible_ = true;
    hidden_ = false;
    takeBoundary_ = false;
    layoutParamChanged_ = false;
    disableTouchEvent_ = false;
    needUpdateTouchRect_ = false;
    flexWeight_ = 0.0;
    displayIndex_ = 1;
    textDirection_ = TextDirection::LTR;
    onChangeCallback_ = nullptr;
    isPaintGeometryTransition_ = false;
}

RRect RenderNode::GetGlobalWindowBlurRRect(std::vector<RRect>& coords) const
{
    RRect windowBlurRRect = GetWindowBlurRRect();
    Rect innerRect = windowBlurRRect.GetRect();
    if (!innerRect.IsValid()) {
        return RRect {};
    } else {
        innerRect += GetPosition();
        windowBlurRRect += GetPosition();
        coords.push_back(windowBlurRRect);
        auto parent = GetParent().Upgrade();
        while (parent) {
            auto parentBlurRRect = parent->GetWindowBlurRRect();
            const Corner& corner = parentBlurRRect.GetCorner();
            // intersect with parent or set border radius should clip by java
            if (!innerRect.IsWrappedBy(parentBlurRRect.GetRect()) ||
                (corner.topLeftRadius.GetX().IsValid() && corner.topLeftRadius.GetY().IsValid())) {
                coords.push_back(parentBlurRRect);
            }
            innerRect = innerRect.Constrain(parentBlurRRect.GetRect());
            auto offset = parent->GetPosition();
            innerRect += offset;
            // out of view port
            if (!innerRect.IsValid()) {
                coords.clear();
                return RRect {};
            }
            for (auto& coord : coords) {
                coord += offset;
            }
            parent = parent->GetParent().Upgrade();
        }
        return RRect::MakeRRect(innerRect, windowBlurRRect.GetCorner().topLeftRadius);
    }
}

Rect RenderNode::GetRectWithShadow() const
{
    Rect paintRect(paintRect_);
    if (InLayoutTransition()) {
        paintRect = nonStrictPaintRect_;
    }
    if (!hasShadow_ || !shadow_.IsValid()) {
        return Rect(Offset::Zero(), paintRect.GetSize());
    }
    auto blurRadius = shadow_.GetBlurRadius();
    auto elevation = shadow_.GetElevation();
    if (elevation > 0.0f && elevation < shadow_.GetLightHeight()) {
        // Conversion between blurRadius and elevation.
        blurRadius = elevation / (shadow_.GetLightHeight() - elevation) * shadow_.GetLightRadius();
    }
    auto radius = 2.0 * blurRadius + shadow_.GetSpreadRadius();

    Rect shadowRect = paintRect + (shadow_.GetOffset() - Offset(radius, radius));
    shadowRect += Size(2.0 * radius, 2.0 * radius);
    shadowRect = shadowRect.CombineRect(paintRect);

    Offset paintOffset = paintRect.GetOffset();
    Offset shadowOffset = shadowRect.GetOffset();
    Offset offset = Offset(std::min(0.0, shadowOffset.GetX() - paintOffset.GetX()),
        std::min(0.0, shadowOffset.GetY() - paintOffset.GetY()));
    return Rect(offset, shadowRect.GetSize());
}

void RenderNode::UpdateWindowBlurRRect(bool clear)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("pipelineContext is null");
        return;
    }
    if (clear) {
        pipelineContext->ClearWindowBlurRegion(GetNodeId());
    } else {
        std::vector<RRect> coords;
        auto blurRect = GetGlobalWindowBlurRRect(coords);
        pipelineContext->UpdateWindowBlurRegion(
            GetNodeId(), blurRect, GetWindowBlurProgress(), GetWindowBlurStyle(), coords);
    }
}

void RenderNode::WindowBlurTest()
{
    if (GetHidden() || !GetVisible()) {
        return;
    }

    if (NeedWindowBlur()) {
        UpdateWindowBlurRRect();
    }
    const auto& children = GetChildren();
    for (const auto& child : children) {
        child->WindowBlurTest();
    }
}

bool RenderNode::HasEffectiveTransform() const
{
    return false;
}

bool RenderNode::IsDisappearing()
{
    auto parentNode = parent_.Upgrade();
    if (!parentNode) {
        return false;
    }
    const auto& disappearingList = parentNode->disappearingNodes_;
    auto iter = std::find(disappearingList.begin(), disappearingList.end(), AceType::Claim(this));
    if (iter != disappearingList.end()) {
        return true;
    } else {
        return false;
    }
}
bool RenderNode::HasDisappearingTransition(int32_t nodeId)
{
    for (auto& child : children_) {
        if (child->GetNodeId() == nodeId) {
            if (child->HasDisappearingTransition(nodeId)) {
                return true;
            }
        }
    }
    return false;
}

void RenderNode::NotifyTransition(TransitionType type, int32_t nodeId)
{
    OnTransition(type, nodeId);
    for (auto& child : children_) {
        if (child->GetNodeId() == nodeId) {
            child->NotifyTransition(type, nodeId);
        }
    }
}

void RenderNode::NotifySizeTransition(const AnimationOption& option, Size fromSize, Size toSize, int32_t nodeId)
{
    paintW_.MoveTo(fromSize.Width());
    paintH_.MoveTo(fromSize.Height());
    paintW_ = AnimatableDimension(toSize.Width());
    paintH_ = AnimatableDimension(toSize.Height());
    for (auto& child : children_) {
        if (child->GetNodeId() == nodeId) {
            child->NotifySizeTransition(option, fromSize, toSize, nodeId);
        }
    }
}

Rect RenderNode::GetDirtyRect() const
{
    Rect dirty = Rect(GetGlobalOffset(), GetLayoutSize());
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Get dirty rect failed. context is null.");
        return dirty;
    }
    // check self has transform effect.
    if (HasEffectiveTransform()) {
        return context->GetRootRect();
    }
    // check parent has transform effect.
    auto pageRoot = context->GetLastPageRender();
    auto parent = GetParent().Upgrade();
    while (parent && parent != pageRoot) {
        if (parent->HasEffectiveTransform()) {
            return context->GetRootRect();
        }
        parent = parent->GetParent().Upgrade();
    }
    // No transform takes effect, return layoutSize.
    return dirty;
}

bool RenderNode::IsPointInBox(const TouchPoint& point)
{
    double offsetX = GetGlobalOffset().GetX();
    double offsetY = GetGlobalOffset().GetY();
    double maxX = GetPaintRect().Width() + offsetX;
    double maxY = GetPaintRect().Height() + offsetY;
    if (InRegion(offsetX, maxX, point.x) && InRegion(offsetY, maxY, point.y)) {
        return true;
    }
    return false;
}

bool RenderNode::GetAlignDeclarationOffset(AlignDeclarationPtr alignDeclarationPtr, Offset& offset) const
{
    offset = offset - GetPosition();
    auto renderNode = parent_.Upgrade();
    return renderNode ? renderNode->GetAlignDeclarationOffset(alignDeclarationPtr, offset) : false;
}

void RenderNode::SaveExplicitAnimationOption(const AnimationOption& option)
{
    nonStrictOption_ = option;
}

const AnimationOption& RenderNode::GetExplicitAnimationOption() const
{
    return nonStrictOption_;
}

void RenderNode::ClearExplicitAnimationOption()
{
    nonStrictOption_ = AnimationOption();
}

void RenderNode::ClearDisappearingNode(RefPtr<RenderNode> child)
{
    disappearingNodes_.remove(child);
}

void RenderNode::CreateLayoutTransition()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    if (nonStrictOption_.IsValid()) {
        auto option = context->GetExplicitAnimationOption();
        context->SaveExplicitAnimationOption(nonStrictOption_);
        CreatePathAnimation();
        paintX_ = AnimatableDimension(paintRect_.GetOffset().GetX());
        paintY_ = AnimatableDimension(paintRect_.GetOffset().GetY());
        paintW_ = AnimatableDimension(paintRect_.GetSize().Width());
        paintH_ = AnimatableDimension(paintRect_.GetSize().Height());
        context->SaveExplicitAnimationOption(option);
        nonStrictOption_ = AnimationOption();
    } else {
        if (paintX_.GetAnimationStatus() != Animator::Status::RUNNING) {
            paintX_.MoveTo(paintRect_.GetOffset().GetX());
        }
        if (paintY_.GetAnimationStatus() != Animator::Status::RUNNING) {
            paintY_.MoveTo(paintRect_.GetOffset().GetY());
        }
        if (paintW_.GetAnimationStatus() != Animator::Status::RUNNING) {
            paintW_.MoveTo(paintRect_.GetSize().Width());
        }
        if (paintH_.GetAnimationStatus() != Animator::Status::RUNNING) {
            paintH_.MoveTo(paintRect_.GetSize().Height());
        }
    }

    nonStrictPaintRect_.SetOffset(Offset(paintX_.Value(), paintY_.Value()));
    nonStrictPaintRect_.SetSize(Size(paintW_.Value(), paintH_.Value()));
}

void RenderNode::CreatePathAnimation()
{
    if (!motionPathOption_.IsValid()) {
        paintX_.SetEvaluator(nullptr);
        paintY_.SetEvaluator(nullptr);
        return;
    }
    if (paintX_.Value() == paintRect_.GetOffset().GetX() && paintY_.Value() == paintRect_.GetOffset().GetY()) {
        LOGE("CreatePathAnimation failed, target equal source");
        return;
    }

    auto evaluator = AceType::MakeRefPtr<MotionPathEvaluator>(
        motionPathOption_, Offset(paintX_.Value(), paintY_.Value()), paintRect_.GetOffset(), positionParam_.type);
    paintX_.SetEvaluator(evaluator->CreateXEvaluator());
    paintY_.SetEvaluator(evaluator->CreateYEvaluator());
    // find transform to create rotate Animation
    if (motionPathOption_.GetRotate()) {
        auto child = GetFirstChild();
        while (child) {
            auto transform = AceType::DynamicCast<RenderTransform>(child);
            if (transform) {
                transform->SetMotionPathEvaluator(evaluator);
                break;
            }
            child = child->GetFirstChild();
        }
    }
}

void RenderNode::CreateGeometryTransitionFrom(const RefPtr<RenderNode>& targetNode, AnimationOption& sharedOption)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto weak = AceType::WeakClaim(this);
    auto render = weak.Upgrade();
    if (!render) {
        return;
    }
    const Rect targetPaintRect_ = targetNode->GetPaintRect();
    const Offset targetOffset = targetNode->GetTransitionGlobalOffset();
    const Offset currentOffset = render->GetGlobalOffset();
    if (sharedOption.IsValid()) {
        auto option = context->GetExplicitAnimationOption();
        context->SaveExplicitAnimationOption(sharedOption);
        Size toSize = paintRect_.GetSize();
        Size fromSize = targetPaintRect_.GetSize();
        isPaintGeometryTransition_ = true;
        for (auto& child : children_) {
            child->SetIsPaintGeometryTransition(isPaintGeometryTransition_);
        }
        paintX_.MoveTo(targetOffset.GetX());
        paintY_.MoveTo(targetOffset.GetY());
        paintX_.SetAnimationStopCallback([weak = AceType::WeakClaim(this)] {
            auto render = weak.Upgrade();
            if (!render) {
                return;
            }
            auto children = render->GetChildren();
            render->isPaintGeometryTransition_ = false;
            for (auto& child : children) {
                child->SetIsPaintGeometryTransition(render->isPaintGeometryTransition_);
            }
            auto parent = render->GetParent().Upgrade();
            if (!parent) {
                return;
            }
            render->paintX_.MoveTo(render->GetGlobalOffset().GetX() - parent->GetGlobalOffset().GetX());
            render->paintY_.MoveTo(render->GetGlobalOffset().GetY() - parent->GetGlobalOffset().GetY());
        });
        paintY_.SetAnimationStopCallback([weak = AceType::WeakClaim(this)] {
            auto render = weak.Upgrade();
            if (!render) {
                return;
            }
            auto children = render->GetChildren();
            render->isPaintGeometryTransition_ = false;
            for (auto& child : children) {
                child->SetIsPaintGeometryTransition(render->isPaintGeometryTransition_);
            }
            auto parent = render->GetParent().Upgrade();
            if (!parent) {
                return;
            }
            render->paintX_.MoveTo(render->GetGlobalOffset().GetX() - parent->GetGlobalOffset().GetX());
            render->paintY_.MoveTo(render->GetGlobalOffset().GetY() - parent->GetGlobalOffset().GetY());
        });
        paintX_ = AnimatableDimension(currentOffset.GetX());
        paintY_ = AnimatableDimension(currentOffset.GetY());
        render->NotifySizeTransition(sharedOption, fromSize, toSize, render->GetNodeId());
        context->SaveExplicitAnimationOption(option);
    }
}

void RenderNode::CreateGeometryTransitionTo(const RefPtr<RenderNode>& targetNode, AnimationOption& sharedOption)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto weak = AceType::WeakClaim(this);
    auto render = weak.Upgrade();
    if (!render) {
        return;
    }
    const Rect targetPaintRect_ = targetNode->GetPaintRect();
    const Offset targetOffset = targetNode->GetGlobalOffset();
    const Offset currentOffset = render->GetTransitionGlobalOffset();
    if (sharedOption.IsValid()) {
        auto option = context->GetExplicitAnimationOption();
        context->SaveExplicitAnimationOption(sharedOption);
        Size fromSize = paintRect_.GetSize();
        Size toSize = targetPaintRect_.GetSize();
        isPaintGeometryTransition_ = true;
        for (auto& child : children_) {
            child->SetIsPaintGeometryTransition(isPaintGeometryTransition_);
        }
        paintX_.MoveTo(currentOffset.GetX());
        paintY_.MoveTo(currentOffset.GetY());
        paintX_.SetAnimationStopCallback([weak = AceType::WeakClaim(this)] {
            auto render = weak.Upgrade();
            if (!render) {
                return;
            }
            auto children = render->GetChildren();
            render->isPaintGeometryTransition_ = false;
            for (auto& child : children) {
                child->SetIsPaintGeometryTransition(render->isPaintGeometryTransition_);
            }
            auto parent = render->GetParent().Upgrade();
            if (!parent) {
                return;
            }
            render->paintX_.MoveTo(render->GetGlobalOffset().GetX() - parent->GetGlobalOffset().GetX());
            render->paintY_.MoveTo(render->GetGlobalOffset().GetY() - parent->GetGlobalOffset().GetY());
        });
        paintY_.SetAnimationStopCallback([weak = AceType::WeakClaim(this)] {
            auto render = weak.Upgrade();
            if (!render) {
                return;
            }
            auto children = render->GetChildren();
            render->isPaintGeometryTransition_ = false;
            for (auto& child : children) {
                child->SetIsPaintGeometryTransition(render->isPaintGeometryTransition_);
            }
            auto parent = render->GetParent().Upgrade();
            if (!parent) {
                return;
            }
            render->paintX_.MoveTo(render->GetGlobalOffset().GetX() - parent->GetGlobalOffset().GetX());
            render->paintY_.MoveTo(render->GetGlobalOffset().GetY() - parent->GetGlobalOffset().GetY());
        });
        paintX_ = AnimatableDimension(targetOffset.GetX());
        paintY_ = AnimatableDimension(targetOffset.GetY());
        render->NotifySizeTransition(sharedOption, fromSize, toSize, render->GetNodeId());
        context->SaveExplicitAnimationOption(option);
    }
}

const Rect& RenderNode::GetPaintRect() const
{
    if (InLayoutTransition()) {
        return nonStrictPaintRect_;
    } else {
        return paintRect_;
    }
}

Offset RenderNode::GetTransitionGlobalOffset() const
{
    auto renderNode = parent_.Upgrade();
    return renderNode ? GetTransitionPaintRect().GetOffset() + renderNode->GetTransitionGlobalOffset()
                      : GetTransitionPaintRect().GetOffset();
}

Rect RenderNode::GetTransitionPaintRect() const
{
    if (InLayoutTransition()) {
        return Rect(nonStrictPaintRect_.GetOffset(), transitionPaintRectSize_);
    } else {
        return paintRect_;
    }
}

void RenderNode::SetLayoutSize(const Size& size)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("Set layout size failed. context is null.");
        return;
    }
    if (paintRect_.GetSize() != size) {
        isFirstSizeAssign_ = false;
        nonStrictOption_ = context->GetExplicitAnimationOption();
        context->AddLayoutTransitionNode(AceType::Claim(this));
        // get bigger canvas size duration transition.
        transitionPaintRectSize_ = Rect(Offset(), paintRect_.GetSize()).CombineRect(Rect(Offset(), size)).GetSize();
        paintRect_.SetSize(size);
        needUpdateTouchRect_ = true;
        OnSizeChanged();
        MarkNeedSyncGeometryProperties();
    }
    if (isFirstSizeAssign_) {
        isFirstSizeAssign_ = false;
        nonStrictOption_ = context->GetExplicitAnimationOption();
        context->AddLayoutTransitionNode(AceType::Claim(this));
    }
}

bool RenderNode::InLayoutTransition() const
{
    return paintX_.GetAnimationStatus() == Animator::Status::RUNNING ||
           paintY_.GetAnimationStatus() == Animator::Status::RUNNING ||
           paintW_.GetAnimationStatus() == Animator::Status::RUNNING ||
           paintH_.GetAnimationStatus() == Animator::Status::RUNNING;
}

void RenderNode::MarkUpdateType(const RefPtr<Component>& component)
{
    updateType_ = component->Compare(GetComponent());
    if (updateType_ & static_cast<uint32_t>(UpdateRenderType::LAYOUT)) {
        MarkNeedLayout();
        return;
    }
    if (updateType_ & static_cast<uint32_t>(UpdateRenderType::PAINT)) {
        MarkNeedRender();
        return;
    }
}

void RenderNode::SetIsPaintGeometryTransition(bool isPaintGeometryTransition)
{
    isPaintGeometryTransition_ = isPaintGeometryTransition;
}

bool RenderNode::IsPaintOutOfParent()
{
    return isPaintGeometryTransition_;
}

void RenderNode::UpdatePosition()
{
    if (isPaintGeometryTransition_) {
        nonStrictPaintRect_.SetLeft(paintX_.Value() - GetParent().Upgrade()->GetTransitionGlobalOffset().GetX());
        nonStrictPaintRect_.SetTop(paintY_.Value() - GetParent().Upgrade()->GetTransitionGlobalOffset().GetY());
    }
}

void RenderNode::SetDepth(int32_t depth)
{
    if (depth_ != depth) {
        depth_ = depth;
        const auto& children = GetChildren();
        for (const auto& item : children) {
            item->SetDepth(depth_ + 1);
        }
    }
}

void RenderNode::SyncRSNodeBoundary(bool isHead, bool isTail)
{
    isHeadRenderNode_ = isHead;
    isTailRenderNode_ = isTail;
    if (isHead && !RSNode_) {
        // create RSNode in first node of JSview
        RSNode_ = CreateRSNode();
    } else if (!isHead && RSNode_) {
        // destroy unneeded RSNode
        RSNode_ = nullptr;
    }
}

void RenderNode::MarkNeedSyncGeometryProperties()
{
    if (!HasGeometryProperties()) {
        return;
    }
    if (auto pipelineContext = context_.Upgrade()) {
        pipelineContext->AddGeometryChangedNode(AceType::Claim(this));
    }
}

void RenderNode::SyncGeometryProperties()
{
    if (!IsTailRenderNode()) {
        return;
    }
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }
    Offset paintOffset = GetPaintOffset();
    Size paintSize = GetLayoutSize();
    rsNode->SetFrame(paintOffset.GetX(), paintOffset.GetY(), paintSize.Width(), paintSize.Height());
}

void RenderNode::SetPaintRect(const Rect& rect)
{
    if (paintRect_ == rect) {
        return;
    }
    paintRect_ = rect;
    needUpdateTouchRect_ = true;

    MarkNeedSyncGeometryProperties();
}

void RenderNode::RSNodeAddChild(const RefPtr<RenderNode>& child)
{
    if (!RSNode_) {
        LOGW("Parent render_node has no RSNode, creating now.");
        SyncRSNodeBoundary(true, true);
    }
    if (IsTailRenderNode()) {
        if (!child->GetRSNode()) {
            LOGW("Child render_node has no RSNode, creating now.");
            child->SyncRSNodeBoundary(true, true);
        }
    } else {
        child->RSNode_ = RSNode_;
    }
    if (child->RSNode_) {
        child->RSNode_->NotifyTransition(Rosen::RSTransitionEffect::FADE_IN);
    }
}

void RenderNode::MarkParentNeedRender() const
{
    auto renderNode = parent_.Upgrade();
    if (!renderNode) {
        return;
    }
    if (IsHeadRenderNode()) {
        renderNode->MarkNeedRender();
    } else {
        renderNode->MarkParentNeedRender();
    }
}

} // namespace OHOS::Ace
