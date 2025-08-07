/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/list/list_item_drag_manager.h"

#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
namespace {
static constexpr Dimension HOT_ZONE_HEIGHT_VP_DIM = 59.0_vp;
static constexpr Dimension HOT_ZONE_WIDTH_VP_DIM = 26.0_vp;
static constexpr int32_t DEFAULT_Z_INDEX = 100;
static constexpr float DEFAULT_SCALE = 1.05f;
}

RefPtr<FrameNode> ListItemDragManager::GetListFrameNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParentFrameNode();
    CHECK_NULL_RETURN(parent, nullptr);
    if (parent->GetTag() == V2::LIST_ITEM_GROUP_ETS_TAG) {
        parent = parent->GetParentFrameNode();
        CHECK_NULL_RETURN(parent, nullptr);
    }
    if (parent->GetTag() == V2::LIST_ETS_TAG) {
        return parent;
    }
    return nullptr;
}

OffsetF ListItemDragManager::GetParentPaddingOffset()
{
    auto parent = listNode_.Upgrade();
    CHECK_NULL_RETURN(parent, OffsetF(0.0f, 0.0f));
    auto listGeometry = parent->GetGeometryNode();
    CHECK_NULL_RETURN(listGeometry, OffsetF(0.0f, 0.0f));
    CHECK_NULL_RETURN(listGeometry->GetPadding(), OffsetF(0.0f, 0.0f));
    float left = listGeometry->GetPadding()->left.value_or(0.0f);
    float top = listGeometry->GetPadding()->top.value_or(0.0f);
    return OffsetF(left, top);
}

void ListItemDragManager::InitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    auto gestureHub = listItemEventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (gestureHub->HasDragEvent()) {
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->HandleOnItemDragStart(info);
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->HandleOnItemDragUpdate(info);
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->HandleOnItemDragEnd(info);
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->HandleOnItemDragCancel();
    };

    auto actionLongPress = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->HandleOnItemLongPress(info);
    };

    auto dragEvent = MakeRefPtr<DragEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    dragEvent->SetLongPressEventFunc(std::move(actionLongPress));
    gestureHub->SetDragEvent(dragEvent, { PanDirection::ALL }, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
    auto dragEventActuator = gestureHub->GetDragEventActuator();
    CHECK_NULL_VOID(dragEventActuator);
    dragEventActuator->SetIsForDragDrop(true);
}

void ListItemDragManager::DeInitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listItemEventHub = host->GetOrCreateEventHub<ListItemEventHub>();
    CHECK_NULL_VOID(listItemEventHub);
    auto gestureHub = listItemEventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->RemoveDragEvent();
}

void ListItemDragManager::HandleOnItemDragStart(const GestureEvent& info)
{
    if (dragState_ == ListItemDragState::IDLE) {
        HandleOnItemLongPress(info);
    }
    dragState_ = ListItemDragState::DRAGGING;
    SetIsNeedDividerAnimation(false);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    dragOffset_ = geometry->GetMarginFrameOffset();

    auto parent = listNode_.Upgrade();
    CHECK_NULL_VOID(parent);
    auto paddingOffset = GetParentPaddingOffset();
    dragOffset_ = dragOffset_ - paddingOffset;
    auto pattern = parent->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    isRtl_ = pattern->IsRTL();
    axis_ = pattern->GetAxis();
    lanes_ = pattern->GetLanes();
    isStackFromEnd_ = pattern->IsStackFromEnd();

    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    totalCount_ = forEach->FrameCount();
    fromIndex_ = GetIndex();
    forEach->FireOnDragStart(fromIndex_);
}

void ListItemDragManager::HandleOnItemLongPress(const GestureEvent& info)
{
    dragState_ = ListItemDragState::LONG_PRESS;
    SetIsNeedDividerAnimation(false);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto forEach = forEachNode_.Upgrade();
    if (forEach && info.GetSourceTool() != SourceTool::MOUSE) {
        forEach->FireOnLongPress(GetIndex());
    }
    if (renderContext->HasTransformScale()) {
        prevScale_ = renderContext->GetTransformScaleValue({ 1.0f, 1.0f });
    } else {
        renderContext->UpdateTransformScale({ 1.0f, 1.0f });
    }
    if (renderContext->HasBackShadow()) {
        prevShadow_ = renderContext->GetBackShadowValue(ShadowConfig::NoneShadow);
    } else {
        renderContext->UpdateBackShadow(ShadowConfig::NoneShadow);
    }
    prevZIndex_ = renderContext->GetZIndexValue(0);

    AnimationOption option;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(300); /* 300:animate duration */
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            auto host = manager->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            auto newScale = manager->prevScale_ * DEFAULT_SCALE;
            renderContext->UpdateTransformScale(newScale);
            renderContext->UpdateZIndex(DEFAULT_Z_INDEX);
            renderContext->UpdateBackShadow(ShadowConfig::DefaultShadowS);
        },
        option.GetOnFinishEvent()
    );
}

void ListItemDragManager::SetNearbyNodeScale(RefPtr<FrameNode> node, float scale)
{
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto it = prevScaleNode_.find(renderContext);
    VectorF prevScale = it != prevScaleNode_.end() ? it->second :
        renderContext->GetTransformScaleValue({ 1.0f, 1.0f });
    renderContext->UpdateTransformScale(prevScale * scale);
    scaleNode_.emplace(renderContext, prevScale);
}

void ListItemDragManager::ResetPrevScaleNode()
{
    for (auto& [weakNode, scale] : prevScaleNode_) {
        if (scaleNode_.find(weakNode) == scaleNode_.end()) {
            auto node = weakNode.Upgrade();
            if (node) {
                node->UpdateTransformScale(scale);
            }
        }
    }
    prevScaleNode_.swap(scaleNode_);
    scaleNode_.clear();
}

ListItemDragManager::ScaleResult ListItemDragManager::ScaleAxisNearItem(
    int32_t index, const RectF& rect, const OffsetF& delta, Axis axis)
{
    ScaleResult res = { false, 1.0f };
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, res);

    auto node = forEach->GetFrameNode(index);
    CHECK_NULL_RETURN(node, res);
    if (!node->IsActive()) {
        return res;
    }
    auto geometry = node->GetGeometryNode();
    CHECK_NULL_RETURN(geometry, res);
    auto nearRect = geometry->GetMarginFrameRect();
    if (axis != axis_) {
        float offset1 = nearRect.GetOffset().GetMainOffset(axis_);
        if (!NearEqual(offset1, rect.GetOffset().GetMainOffset(axis_))) {
            return res;
        }
    }
    float axisDelta = delta.GetMainOffset(axis);
    float c0 = rect.GetOffset().GetMainOffset(axis) + rect.GetSize().MainSize(axis) / 2;
    float c1 = nearRect.GetOffset().GetMainOffset(axis) + nearRect.GetSize().MainSize(axis) / 2;
    if (NearEqual(c0, c1)) {
        return res;
    }
    float sharped = Curves::SHARP->MoveInternal(std::abs(axisDelta / (c1 - c0)));
    float scale = 1 - sharped * 0.05f;
    SetNearbyNodeScale(node, scale);
    res.scale = scale;
    res.needMove = IsNeedMove(nearRect, rect, axis, axisDelta);
    
    return res;
}

bool ListItemDragManager::IsNeedMove(const RectF& nearRect, const RectF& rect, Axis axis, float axisDelta)
{
    bool needMove = false;
    if (Positive(axisDelta)) {
        float th = (nearRect.GetOffset().GetMainOffset(axis) + nearRect.GetSize().MainSize(axis) -
            rect.GetOffset().GetMainOffset(axis) - rect.GetSize().MainSize(axis)) / 2;
        if (GreatNotEqual(axisDelta, th)) {
            needMove = true;
        }
    }
    if (Negative(axisDelta)) {
        float th = (nearRect.GetOffset().GetMainOffset(axis) - rect.GetOffset().GetMainOffset(axis)) / 2;
        if (LessNotEqual(axisDelta, th)) {
            needMove = true;
        }
    }
    return needMove;
}

void ListItemDragManager::ScaleDiagonalItem(int32_t index, const RectF& rect, const OffsetF& delta)
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);

    auto node = forEach->GetFrameNode(index);
    CHECK_NULL_VOID(node);
    auto geometry = node->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto diagonalRect = geometry->GetMarginFrameRect();

    OffsetF c0 = rect.GetOffset() + OffsetF(rect.Width() / 2, rect.Height() / 2);
    OffsetF c1 = diagonalRect.GetOffset() + OffsetF(diagonalRect.Width() / 2, diagonalRect.Height() / 2);
    OffsetF c2 = c0 + delta;

    float d0 = c0.GetDistance(c1);
    if (NearZero(d0)) {
        return;
    }
    float d1 = c2.GetDistance(c1);

    float sharped = Curves::SHARP->MoveInternal(std::abs(1 - d1 / d0));
    float scale = 1 - sharped * 0.05f;
    SetNearbyNodeScale(node, scale);
}

int32_t ListItemDragManager::CalcMainNearIndex(const int32_t index, const OffsetF& delta)
{
    int32_t nearIndex = index;
    float mainDelta = delta.GetMainOffset(axis_);
    if (isRtl_ && axis_ == Axis::HORIZONTAL) {
        if (Positive(mainDelta)) {
            nearIndex = index - lanes_;
        } else if (Negative(mainDelta)) {
            nearIndex = index + lanes_;
        }
    } else {
        if (Positive(mainDelta)) {
            nearIndex = index + lanes_;
        } else if (Negative(mainDelta)) {
            nearIndex = index - lanes_;
        }
    }
    
    return nearIndex;
}

int32_t ListItemDragManager::CalcCrossNearIndex(const int32_t index, const OffsetF& delta)
{
    int32_t nearIndex = index;
    float crossDelta = delta.GetCrossOffset(axis_);
    int32_t step = isStackFromEnd_ ? -1 : 1;
    if (isRtl_ && axis_ == Axis::VERTICAL) {
        if (Positive(crossDelta)) {
            nearIndex = index - step;
        } else if (Negative(crossDelta)) {
            nearIndex = index + step;
        }
    } else {
        if (Positive(crossDelta)) {
            nearIndex = index + step;
        } else if (Negative(crossDelta)) {
            nearIndex = index - step;
        }
    }
    return nearIndex;
}

int32_t ListItemDragManager::CalcDiagonalIndex(const int32_t mainNearIndex, const OffsetF& delta)
{
    int32_t diagonalIndex = Positive(delta.GetCrossOffset(axis_)) ? mainNearIndex + 1 : mainNearIndex - 1;
    if (isRtl_ && axis_ == Axis::VERTICAL) {
        diagonalIndex = Negative(delta.GetCrossOffset(axis_)) ? mainNearIndex + 1 : mainNearIndex - 1;
    }
    return diagonalIndex;
}

int32_t ListItemDragManager::ScaleNearItem(int32_t index, const RectF& rect, const OffsetF& delta)
{
    ScaleResult mainRes = { false, 1.0f };
    ScaleResult crossRes = { false, 1.0f };
    int32_t mainNearIndex = CalcMainNearIndex(index, delta);
    int32_t crossNearIndex = CalcCrossNearIndex(index, delta);
    if (mainNearIndex != index) {
        mainRes = ScaleAxisNearItem(mainNearIndex, rect, delta, axis_);
    }
    if (crossNearIndex != index) {
        Axis crossAxis = axis_ == Axis::VERTICAL ? Axis::HORIZONTAL : Axis::VERTICAL;
        crossRes = ScaleAxisNearItem(crossNearIndex, rect, delta, crossAxis);
    }

    bool isNeedScaleDiagonal = !NearEqual(mainRes.scale, 1.0f) && !NearEqual(crossRes.scale, 1.0f);
    if ((mainNearIndex < 0 && crossNearIndex == totalCount_) ||
        (mainNearIndex > totalCount_ - 1 && crossNearIndex == -1)) {
        isNeedScaleDiagonal = true;
        int32_t crossIndexGap = mainNearIndex < 0 ? -mainNearIndex : mainNearIndex - totalCount_ + 1;
        float mainDis = rect.GetSize().MainSize(axis_) / 2;
        float crossDis = rect.GetSize().CrossSize(axis_) / 2 * (crossIndexGap * 2 - 1);
        mainRes.needMove = GreatNotEqual(std::abs(delta.GetMainOffset(axis_)), mainDis);
        crossRes.needMove = GreatNotEqual(std::abs(delta.GetCrossOffset(axis_)), crossDis);
    }
    int32_t diagonalIndex = index;
    if (isNeedScaleDiagonal) {
        diagonalIndex = CalcDiagonalIndex(mainNearIndex, delta);
        if (diagonalIndex < 0) {
            diagonalIndex = 0;
        } else if (diagonalIndex > totalCount_ - 1) {
            diagonalIndex = totalCount_ - 1;
        }
        ScaleDiagonalItem(diagonalIndex, rect, delta);
    }

    ResetPrevScaleNode();
    if (mainRes.needMove && crossRes.needMove) {
        return diagonalIndex;
    } else if (mainRes.needMove) {
        return mainNearIndex;
    } else if (crossRes.needMove) {
        return crossNearIndex;
    }
    return index;
}

bool ListItemDragManager::IsInHotZone(int32_t index, const RectF& frameRect) const
{
    auto parent = listNode_.Upgrade();
    CHECK_NULL_RETURN(parent, false);
    auto listGeometry = parent->GetGeometryNode();
    CHECK_NULL_RETURN(listGeometry, false);
    auto listSize = listGeometry->GetFrameSize();
    float hotZone = axis_ == Axis::VERTICAL ?
        HOT_ZONE_HEIGHT_VP_DIM.ConvertToPx() : HOT_ZONE_WIDTH_VP_DIM.ConvertToPx();
    float startOffset = frameRect.GetOffset().GetMainOffset(axis_);
    float endOffset = startOffset + frameRect.GetSize().MainSize(axis_);
    bool reachStart = (index == 0 && startOffset > hotZone);
    bool reachEnd = (index == totalCount_ - 1) && endOffset < (listSize.MainSize(axis_) - hotZone);
    if (isRtl_ && axis_ == Axis::HORIZONTAL) {
        reachStart = index == 0 && endOffset < (listSize.MainSize(axis_) - hotZone);
        reachEnd = (index == totalCount_ - 1) && startOffset > hotZone;
    }
    return (!reachStart && !reachEnd);
}

void ListItemDragManager::HandleAutoScroll(int32_t index, const PointF& point, const RectF& frameRect)
{
    auto parent = listNode_.Upgrade();
    CHECK_NULL_VOID(parent);
    auto pattern = parent->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    if (IsInHotZone(index, frameRect) && parent->GetDragPreviewOption().enableEdgeAutoScroll) {
        pattern->HandleMoveEventInComp(point);
        if (!scrolling_) {
            pattern->SetHotZoneScrollCallback([weak = WeakClaim(this)]() {
                auto manager = weak.Upgrade();
                CHECK_NULL_VOID(manager);
                manager->HandleScrollCallback();
            });
            scrolling_ = true;
        }
    } else if (scrolling_) {
        pattern->HandleLeaveHotzoneEvent();
        pattern->SetHotZoneScrollCallback(nullptr);
        scrolling_ = false;
    }
}

void ListItemDragManager::HandleScrollCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto frameRect = geometry->GetMarginFrameRect();
    int32_t from = GetIndex();
    if (scrolling_ && !IsInHotZone(from, frameRect)) {
        auto parent = listNode_.Upgrade();
        CHECK_NULL_VOID(parent);
        auto pattern = parent->GetPattern<ListPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLeaveHotzoneEvent();
        pattern->SetHotZoneScrollCallback(nullptr);
        scrolling_ = false;
    }
    auto paddingOffset = GetParentPaddingOffset();
    int32_t to = ScaleNearItem(from, frameRect, realOffset_ - frameRect.GetOffset() + paddingOffset);
    if (to == from) {
        return;
    }
    HandleSwapAnimation(from, to);
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    forEach->FireOnMoveThrough(fromIndex_, to);
}

void ListItemDragManager::SetPosition(const OffsetF& offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdatePosition({ Dimension(offset.GetX(), DimensionUnit::PX),
        Dimension(offset.GetY(), DimensionUnit::PX) });
}

void ListItemDragManager::HandleOnItemDragUpdate(const GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto frameRect = geometry->GetMarginFrameRect();
    OffsetF gestureOffset(info.GetOffsetX(), info.GetOffsetY());
    realOffset_ = gestureOffset + dragOffset_;
    lanes_ = GetLanes();
    if (lanes_ == 1) {
        if (axis_ == Axis::VERTICAL) {
            realOffset_.SetX(dragOffset_.GetX());
        } else {
            realOffset_.SetY(dragOffset_.GetY());
        }
    }
    SetPosition(realOffset_);

    int32_t from = GetIndex();
    PointF point(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    HandleAutoScroll(from, point, frameRect);

    auto paddingOffset = GetParentPaddingOffset();
    int32_t to = ScaleNearItem(from, frameRect, realOffset_ - frameRect.GetOffset() + paddingOffset);
    if (to == from) {
        return;
    }
    HandleSwapAnimation(from, to);
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    forEach->FireOnMoveThrough(fromIndex_, to);
}

void ListItemDragManager::HandleSwapAnimation(int32_t from, int32_t to)
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    CHECK_NULL_VOID(forEach->GetFrameNode(to));
    auto list = listNode_.Upgrade();
    CHECK_NULL_VOID(list);
    if (list->CheckNeedForceMeasureAndLayout()) {
        auto pipeline = list->GetContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }
    auto pattern = list->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDraggingIndex(to);
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(0, 1, 400, 38); /* 400:stiffness, 38:damping */
    option.SetCurve(curve);
    option.SetDuration(30); /* 30:duration */
    AnimationUtils::Animate(option, [weak = forEachNode_, from, to]() {
            auto forEach = weak.Upgrade();
            CHECK_NULL_VOID(forEach);
            forEach->MoveData(from, to);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
            }
        },
        option.GetOnFinishEvent()
    );
}

void ListItemDragManager::HandleZIndexAndPosition()
{
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(0, 1, 400, 38); /* 400:stiffness, 38:damping */
    option.SetCurve(curve);
    option.SetDuration(30); /* 30:duration */
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            manager->ResetPrevScaleNode();
            auto host = manager->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateZIndex(manager->prevZIndex_);
            renderContext->ResetPosition();
            renderContext->OnPositionUpdate(OffsetT<Dimension>());
        },
        option.GetOnFinishEvent()
    );
}

void ListItemDragManager::HandleBackShadow()
{
    AnimationOption option;
    isDragAnimationStopped_ = false;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(300); /* animate duration:300ms */
    // choose the animation with max duration to re-open divider animation.
    option.SetOnFinishEvent([weak = WeakClaim(this)]() {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->isDragAnimationStopped_ = true;
        if (manager->dragState_ == ListItemDragState::IDLE) {
            manager->SetIsNeedDividerAnimation(true);
        }
    });
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            auto host = manager->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateBackShadow(manager->prevShadow_);
        },
        option.GetOnFinishEvent()
    );
}

void ListItemDragManager::HandleTransformScale()
{
    AnimationOption option;
    /* 14:init velocity, 170:stiffness, 17:damping */
    option.SetCurve(AceType::MakeRefPtr<InterpolatingSpring>(14, 1, 170, 17));
    option.SetDuration(30);  /* 30:duration */
    option.SetDelay(150); /* 150:animate delay */
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            auto host = manager->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformScale(manager->prevScale_);
        },
        option.GetOnFinishEvent()
    );
}

void ListItemDragManager::HandleDragEndAnimation()
{
    // start animation to reset z-index and position.
    HandleZIndexAndPosition();
    // start animation to reset backshadow.
    HandleBackShadow();
    // start animation to reset transformscale.
    HandleTransformScale();
}

void ListItemDragManager::HandleOnItemDragEnd(const GestureEvent& info)
{
    auto parent = listNode_.Upgrade();
    CHECK_NULL_VOID(parent);
    auto pattern = parent->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDraggingIndex(-1);
    pattern->SetHotZoneScrollCallback(nullptr);
    if (scrolling_) {
        pattern->HandleLeaveHotzoneEvent();
        scrolling_ = false;
    }
    HandleDragEndAnimation();
    int32_t to = GetIndex();
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    forEach->FireOnMove(fromIndex_, to);
    forEach->FireOnDrop(to);
    dragState_ = ListItemDragState::IDLE;
    if (isDragAnimationStopped_) {
        SetIsNeedDividerAnimation(true);
    }
}

void ListItemDragManager::HandleOnItemDragCancel()
{
    auto parent = listNode_.Upgrade();
    CHECK_NULL_VOID(parent);
    auto pattern = parent->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDraggingIndex(-1);
    HandleDragEndAnimation();
    dragState_ = ListItemDragState::IDLE;
    if (isDragAnimationStopped_) {
        SetIsNeedDividerAnimation(true);
    }
    pattern->HandleLeaveHotzoneEvent();
    pattern->SetHotZoneScrollCallback(nullptr);
}

int32_t ListItemDragManager::GetIndex() const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, -1);
    return forEach->GetFrameNodeIndex(GetHost());
}

int32_t ListItemDragManager::GetLanes() const
{
    auto parent = listNode_.Upgrade();
    CHECK_NULL_RETURN(parent, 1);
    auto pattern = parent->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(pattern, 1);
    return pattern->GetLanes();
}

void ListItemDragManager::SetIsNeedDividerAnimation(bool isNeedDividerAnimation)
{
    auto parent = listNode_.Upgrade();
    CHECK_NULL_VOID(parent);
    auto pattern = parent->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsNeedDividerAnimation(isNeedDividerAnimation);
}
} // namespace OHOS::Ace::NG
