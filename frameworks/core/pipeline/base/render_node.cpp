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

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "core/components/box/render_box.h"
#include "core/components/common/rotation/rotation_node.h"
#include "core/components/focus_animation/render_focus_animation.h"
#include "core/components/root/render_root.h"
#include "core/components/scroll/render_single_child_scroll.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline/base/component.h"

namespace OHOS::Ace {

namespace {

constexpr float PRESS_KEYFRAME_START = 0.0f;
constexpr float PRESS_KEYFRAME_END = 1.0f;

} // namespace

constexpr Dimension FOCUS_BOUNDARY = 4.0_vp; // focus padding + effect boundary, VP

RenderNode::RenderNode(bool takeBoundary) : takeBoundary_(takeBoundary) {}

void RenderNode::AddChild(const RefPtr<RenderNode>& child, int32_t slot)
{
    if (child) {
        const auto& it = std::find(children_.begin(), children_.end(), child);
        auto pos = children_.begin();
        std::advance(pos, slot);
        if (it == children_.end()) {
            children_.insert(pos, child);
            child->SetParent(AceType::WeakClaim(this));
            child->SetDepth(GetDepth() + 1);
            OnChildAdded(child);
        } else {
            LOGW("RenderNode exist AddChild failed");
        }
    }
}

void RenderNode::RemoveChild(const RefPtr<RenderNode>& child)
{
    if (child) {
        children_.remove(child);
        OnChildRemoved(child);
        LOGD("RenderNode RemoveChild %{public}zu", children_.size());
    }
}

void RenderNode::UpdateTouchRect()
{
    touchRect_ = paintRect_;
    auto box = AceType::DynamicCast<RenderBox>(this);
    // For exclude the margin area from touch area and the margin must not be less than zero.
    if (box && box->GetTouchArea().GetOffset().IsPositiveOffset()) {
        touchRect_.SetOffset(box->GetTouchArea().GetOffset() + touchRect_.GetOffset());
        touchRect_.SetSize(box->GetTouchArea().GetSize());
    }
    if (!children_.empty()) {
        double minX = touchRect_.Left();
        double minY = touchRect_.Top();
        double maxX = touchRect_.Right();
        double maxY = touchRect_.Bottom();
        for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
            auto& child = *iter;
            if (child->GetTouchRect().GetSize().IsEmpty()) {
                continue;
            }
            minX = std::min(minX, child->GetTouchRect().Left() + touchRect_.Left());
            minY = std::min(minY, child->GetTouchRect().Top() + touchRect_.Top());
            maxX = std::max(maxX, child->GetTouchRect().Right() + touchRect_.Left());
            maxY = std::max(maxY, child->GetTouchRect().Bottom() + touchRect_.Top());
        }
        touchRect_.SetOffset({ minX, minY });
        touchRect_.SetSize({ maxX - minX, maxY - minY });
    }
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
    if (DumpLog::GetInstance().GetDumpFile()) {
        auto dirtyRect = context_.Upgrade()->GetDirtyRect();
        DumpLog::GetInstance().AddDesc(std::string("AccessibilityNodeID: ").append(std::to_string(nodeId)));
        DumpLog::GetInstance().AddDesc(std::string("Position: ").append(GetGlobalOffset().ToString()));
        DumpLog::GetInstance().AddDesc(std::string("PaintRect: ").append(paintRect_.ToString()));
        DumpLog::GetInstance().AddDesc(std::string("TouchRect: ").append(touchRect_.ToString()));
        DumpLog::GetInstance().AddDesc(std::string("DirtyRect: ").append(dirtyRect.ToString()));
        DumpLog::GetInstance().AddDesc(std::string("LayoutParam: ").append(layoutParam_.ToString()));
        DumpLog::GetInstance().AddDesc(
            std::string("MouseState: ").append(mouseState_ == MouseState::HOVER ? "HOVER" : "NONE"));
        Dump();
        DumpLog::GetInstance().Print(depth, AceType::TypeName(this), children_.size());
    }

    for (const auto& item : children_) {
        item->DumpTree(depth + 1);
    }
}

void RenderNode::Dump() {}

void RenderNode::RenderWithContext(RenderContext& context, const Offset& offset)
{
    MarkNeedWindowBlur(false);
    if (onLayoutReady_) {
        onLayoutReady_(std::string("\"layoutReady\",null,null"));
    }
    Paint(context, offset);
    if (needUpdateAccessibility_) {
        OnPaintFinish();
    }
    SetNeedRender(false);
}

void RenderNode::Paint(RenderContext& context, const Offset& offset)
{
    for (const auto& item : paintChildren_) {
        PaintChild(item.Upgrade(), context, offset);
    }
}

void RenderNode::PaintChild(const RefPtr<RenderNode>& child, RenderContext& context, const Offset& offset)
{
    if (child && child->GetVisible()) {
        context.PaintChild(child, offset);
    }
}

void RenderNode::MarkNeedLayout(bool selfOnly, bool forceParent)
{
    bool forceSelf = forceParent && AceType::InstanceOf<RenderRoot>(this);
    if (forceSelf) {
        // This is root and child need force parent layout.
        SetNeedLayout(true);
        auto pipelineContext = context_.Upgrade();
        if (pipelineContext != nullptr) {
            pipelineContext->AddDirtyLayoutNode(AceType::Claim(this));
        }
    } else if (forceParent) {
        // Force mark self and all ancestors need layout.
        SetNeedLayout(true);
        auto parent = parent_.Upgrade();
        if (parent) {
            parent->MarkNeedLayout(false, forceParent);
        }
    } else if (!needLayout_) {
        SetNeedLayout(true);

        if (IsTakenBoundary() || selfOnly) {
            if (MarkNeedRenderSpecial()) {
                auto parent = parent_.Upgrade();
                if (parent) {
                    parent->MarkNeedLayout();
                }
            } else {
                auto pipelineContext = context_.Upgrade();
                if (pipelineContext != nullptr) {
                    pipelineContext->AddDirtyLayoutNode(AceType::Claim(this));
                }
            }
        } else {
            auto parent = parent_.Upgrade();
            if (parent) {
                parent->MarkNeedLayout();
            }
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
        MarkNeedRender();
    }
    SortPaintChildrenBasedOnZIndex();
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
    if (positionParam_.top.second) {
        selfOffset.SetY(NormalizePercentToPx(positionParam_.top.first, true));
    } else if (positionParam_.bottom.second) {
        selfOffset.SetY(-NormalizePercentToPx(positionParam_.bottom.first, true));
    } else {
        selfOffset.SetY(0);
    }
    selfOffset_ = selfOffset;
    SetPositionInternal(selfOffset + offset);
}

void RenderNode::SetPositionInternal(const Offset& offset)
{
    if (paintRect_.GetOffset() != offset) {
        paintRect_.SetOffset(offset);
        needUpdateTouchRect_ = true;
        OnPositionChanged();
        OnGlobalPositionChanged();
    }
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
    animation->SetEvaluator(AceType::MakeRefPtr<ColorEvaluator>());
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
    // Since the paintRect is relative to parent, use parent local point to perform touch test.
    if (!GetTouchRect().IsInRegion(parentLocalPoint)) {
        return false;
    }

    // Calculates the local point location in this node.
    const auto localPoint = parentLocalPoint - paintRect_.GetOffset();
    bool dispatchSuccess = false;
    for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
        auto& child = *iter;
        if (!child->GetVisible()) {
            continue;
        }
        if (child->TouchTest(globalPoint, localPoint, touchRestrict, result)) {
            dispatchSuccess = true;
            break;
        }
        if (child->InterceptTouchEvent() && GetTouchRect().IsInRegion(parentLocalPoint)) {
            dispatchSuccess = true;
            break;
        }
    }
    auto beforeSize = result.size();
    if (touchable_) {
        // Calculates the coordinate offset in this node.
        const auto coordinateOffset = globalPoint - localPoint;
        globalPoint_ = globalPoint;
        OnTouchTestHit(coordinateOffset, touchRestrict, result);
    }
    auto endSize = result.size();
    return dispatchSuccess || beforeSize != endSize;
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
        for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
            auto& child = *iter;
            child->MouseTest(globalPoint, localPoint, result);
        }
        // Calculates the coordinate offset in this node.
        const auto coordinateOffset = globalPoint - localPoint;
        globalPoint_ = globalPoint;
        OnMouseTestHit(coordinateOffset, result);
    }
}

bool RenderNode::MouseHoverTest(const Point& parentLocalPoint)
{
    const auto localPoint = parentLocalPoint - paintRect_.GetOffset();
    // Since the paintRect is relative to parent, use parent local point to perform touch test.
    if (GetTouchRect().IsInRegion(parentLocalPoint)) {
        auto context = context_.Upgrade();
        if (!context) {
            return false;
        }
        hoverChildren_.clear();
        context->AddToHoverList(AceType::WeakClaim(this).Upgrade());
        for (auto iter = children_.begin(); iter != children_.end(); ++iter) {
            auto& child = *iter;
            if (child->MouseHoverTest(localPoint)) {
                hoverChildren_.emplace_back(child);
            }
        }
        // mouse state of the node is from NONE to HOVER, the callback of hover enter is triggered.
        if (mouseState_ == MouseState::NONE) {
            OnMouseHoverEnterTest();
            mouseState_ = MouseState::HOVER;
        }
        return true;
    } else {
        for (const auto& child : hoverChildren_) {
            child->MouseHoverTest(localPoint);
        }
        // mouse state of the node is from HOVER to NONE, the callback of hover exit is triggered.
        if (mouseState_ == MouseState::HOVER) {
            OnMouseHoverExitTest();
            mouseState_ = MouseState::NONE;
        }
        return false;
    }
}

bool RenderNode::RotationMatchTest(const RefPtr<RenderNode>& requestRenderNode)
{
    RotationNode* rotationNode = AceType::DynamicCast<RotationNode>(this);
    if ((rotationNode != nullptr) && requestRenderNode == this) {
        LOGD("RotationMatchTest: match rotation focus node %{public}s.", GetTypeName());
        return true;
    }

    for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
        const auto& child = *iter;
        if (child && child->RotationMatchTest(requestRenderNode)) {
            return true;
        }
    }

    return false;
}

bool RenderNode::RotationTest(const RotationEvent& event)
{
    for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
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

    for (auto iter = children_.begin(); iter != children_.end(); ++iter) {
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
    return context->NormalizeToPx(dimension);
}

double RenderNode::NormalizePercentToPx(const Dimension& dimension, bool isVertical) const
{
    if (dimension.Unit() != DimensionUnit::PERCENT) {
        return NormalizeToPx(dimension);
    }
    double parentLimit = 0.0;
    auto parent = parent_.Upgrade();
    if (!parent) {
        parentLimit = isVertical ? GetLayoutParam().GetMaxSize().Height() : GetLayoutParam().GetMaxSize().Width();
        return parentLimit * dimension.Value();
    }
    auto parentSize = parent->GetLayoutParam().GetMaxSize();
    if (parentSize > viewPort_) {
        parentSize = viewPort_;
    }
    parentLimit = isVertical ? parentSize.Height() : parentSize.Width();
    return parentLimit * dimension.Value();
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
        positionParam_ = renderComponent->GetPositionParam();
        flexWeight_ = renderComponent->GetFlexWeight();
        displayIndex_ = renderComponent->GetDisplayIndex();
        isIgnored_ = renderComponent->IsIgnored();
        if (renderComponent->IsCustomComponent()) {
            onLayoutReady_ =
                AceAsyncEvent<void(const std::string&)>::Create(renderComponent->GetOnLayoutReadyMarker(), context_);
        }
    }
    zIndex_ = renderComponent->GetZIndex();
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
        MarkNeedRender();
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

    children_.clear();
    accessibilityText_ = "";
    layoutParam_ = LayoutParam();
    paintRect_ = Rect();
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
    if (!hasShadow_ || !shadow_.IsValid()) {
        return Rect(Offset::Zero(), paintRect_.GetSize());
    }
    auto blurRadius = shadow_.GetBlurRadius();
    auto elevation = shadow_.GetElevation();
    if (elevation > 0.0f && elevation < shadow_.GetLightHeight()) {
        // Conversion between blurRadius and elevation.
        blurRadius = elevation / (shadow_.GetLightHeight() - elevation) * shadow_.GetLightRadius();
    }
    auto radius = 2.0 * blurRadius + shadow_.GetSpreadRadius();

    Rect shadowRect = paintRect_ + (shadow_.GetOffset() - Offset(radius, radius));
    shadowRect += Size(2.0 * radius, 2.0 * radius);
    shadowRect = shadowRect.CombineRect(paintRect_);

    Offset paintOffset = paintRect_.GetOffset();
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
    for (const auto& child : children_) {
        child->WindowBlurTest();
    }
}

bool RenderNode::HasEffectiveTransform() const
{
    return false;
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

} // namespace OHOS::Ace
