/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "base/memory/ace_type.h"
#include "base/utils/multi_thread.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_drag_manager.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/property/templates_parser.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/gestures/gesture_event.h"
#include <numeric>
#include <vector>
#include <cmath>
#include <limits>
#include <set>
#include <algorithm>
#include <optional>

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_SCALE = 1.05f;
constexpr int32_t DEFAULT_Z_INDEX = 100;
constexpr Dimension HOT_ZONE_HEIGHT = 59.0_vp;
constexpr Dimension HOT_ZONE_WIDTH = 26.0_vp;
constexpr float DEFAULT_ITEM_SIZE = 100.0f;
constexpr int32_t LONG_PRESS_ANIMATION_DURATION = 300;
constexpr int32_t SWAP_ANIMATION_DURATION = 30;
constexpr int32_t POWER_FOR_DISTANCE = 2;
constexpr float NEARBY_SCALE_RATIO = 0.05f;
const char GRID_ETS_TAG[] = "Grid";

int32_t GetForEachIndexInGrid(const RefPtr<ForEachBaseNode>& forEach)
{
    RefPtr<UINode> node = forEach;
    auto parent = node->GetParent();
    // assume parent is grid
    if (parent) {
        int32_t childIndex = parent->GetChildIndex(node);
        int32_t startIndex = 0;
        for (int32_t i = 0; i < childIndex; i++) {
            auto childNode = parent->GetChildAtIndex(i);
            startIndex += childNode->FrameCount();
        }
        return startIndex;
    }
    return 0;
}
}

RefPtr<FrameNode> GridItemDragManager::GetGridFrameNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParentFrameNode();
    CHECK_NULL_RETURN(parent, nullptr);
    if (parent->GetTag() == GRID_ETS_TAG) {
        return parent;
    }
    return nullptr;
}

GridItemDragManager::~GridItemDragManager()
{
    Reset();
}

void GridItemDragManager::Reset()
{
    if (dragState_ != GridItemDragState::DRAGGING) {
        return;
    }
    ResetPrevScaleNode();
    auto grid = gridNode_.Upgrade();
    if (!grid) {
        return;
    }
    auto pattern = grid->GetPattern<GridPattern>();
    if (!pattern) {
        return;
    }
    if (scrolling_) {
        pattern->HandleLeaveHotzoneEvent();
        scrolling_ = false;
    }
    autoScrollForward_ = false;
    inAutoScrollHotZone_ = false;
    pattern->SetHotZoneScrollCallback(nullptr);
    pattern->GetMutableLayoutInfo().ClearOnMoveDragState();

    auto forEach = forEachNode_.Upgrade();
    if (!forEach) {
        return;
    }
    int32_t dropIndex = moveThroughIndex_ >= 0 ? moveThroughIndex_ : fromIndex_;
    if (fromIndex_ >= 0 && dropIndex >= 0) {
        forEach->FireOnMove(fromIndex_, dropIndex);
        forEach->FireOnDrop(dropIndex);
    }
    dragState_ = GridItemDragState::IDLE;
    moveThroughIndex_ = -1;
}

OffsetF GridItemDragManager::GetParentPaddingOffset() const
{
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_RETURN(grid, OffsetF(0.0f, 0.0f));
    auto gridGeometry = grid->GetGeometryNode();
    CHECK_NULL_RETURN(gridGeometry, OffsetF(0.0f, 0.0f));
    CHECK_NULL_RETURN(gridGeometry->GetPadding(), OffsetF(0.0f, 0.0f));
    float left = gridGeometry->GetPadding()->left.value_or(0.0f);
    float top = gridGeometry->GetPadding()->top.value_or(0.0f);
    return OffsetF(left, top);
}

void GridItemDragManager::InitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gridItemEventHub = host->GetEventHub<GridItemEventHub>();
    CHECK_NULL_VOID(gridItemEventHub);
    auto gestureHub = gridItemEventHub->GetOrCreateGestureEventHub();
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
        std::move(actionStartTask), std::move(actionUpdateTask),
        std::move(actionEndTask), std::move(actionCancelTask));
    dragEvent->SetLongPressEventFunc(std::move(actionLongPress));
    gestureHub->SetDragEvent(dragEvent, { PanDirection::ALL }, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
    auto dragEventActuator = gestureHub->GetDragEventActuator();
    CHECK_NULL_VOID(dragEventActuator);
    dragEventActuator->SetIsForDragDrop(true);
}

void GridItemDragManager::DeInitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gridItemEventHub = host->GetEventHub<GridItemEventHub>();
    CHECK_NULL_VOID(gridItemEventHub);
    auto gestureHub = gridItemEventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->RemoveDragEvent();
}

void GridItemDragManager::HandleOnItemLongPress(const GestureEvent& info)
{
    dragState_ = GridItemDragState::LONG_PRESS;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto forEach = forEachNode_.Upgrade();
    if (forEach && info.GetSourceTool() != SourceTool::MOUSE) {
        auto idx = GetIndex();
        if (idx < 0) {
            return;
        }
        forEach->FireOnLongPress(idx);
    }

    if (renderContext->HasTransformScale()) {
        prevScale_ = renderContext->GetTransformScaleValue({1.0f, 1.0f});
    } else {
        renderContext->UpdateTransformScale({1.0f, 1.0f});
    }
    if (renderContext->HasBackShadow()) {
        prevShadow_ = renderContext->GetBackShadowValue(ShadowConfig::NoneShadow);
    } else {
        renderContext->UpdateBackShadow(ShadowConfig::NoneShadow);
    }
    prevZIndex_ = renderContext->GetZIndexValue(0);

    AnimationOption option;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(LONG_PRESS_ANIMATION_DURATION);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
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
        option.GetOnFinishEvent(), nullptr, context);
}

void GridItemDragManager::HandleOnItemDragStart(const GestureEvent& info)
{
    if (dragState_ == GridItemDragState::IDLE) {
        HandleOnItemLongPress(info);
    }
    dragState_ = GridItemDragState::DRAGGING;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    dragOffset_ = geometry->GetMarginFrameOffset();

    auto grid = gridNode_.Upgrade();
    CHECK_NULL_VOID(grid);
    auto paddingOffset = GetParentPaddingOffset();
    dragOffset_ = dragOffset_ - paddingOffset;
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    axis_ = pattern->GetAxis();

    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    totalCount_ = forEach->FrameCount();
    currentIndex_ = GetIndex();
    if (currentIndex_ < 0) {
        dragState_ = GridItemDragState::IDLE;
        return;
    }
    fromIndex_ = currentIndex_;
    forEach->FireOnDragStart(fromIndex_);
    forEachStartIndex_ = GetForEachIndexInGrid(forEach);
}

bool GridItemDragManager::CancelDragOnGridChange()
{
    auto grid = gridNode_.Upgrade();
    if (!grid) {
        return false;
    }
    auto pattern = grid->GetPattern<GridPattern>();
    if (!pattern) {
        return false;
    }
    auto& layoutInfo = pattern->GetMutableLayoutInfo();
    if (!layoutInfo.isOnMoveGridChange_) {
        return false;
    }
    layoutInfo.isOnMoveGridChange_ = false;
    if (scrolling_) {
        pattern->HandleLeaveHotzoneEvent();
        scrolling_ = false;
    }
    autoScrollForward_ = false;
    inAutoScrollHotZone_ = false;
    pattern->SetHotZoneScrollCallback(nullptr);
    return true;
}

void GridItemDragManager::ProcessSwap(int32_t from)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto frameRect = geometry->GetMarginFrameRect();
    auto paddingOffset = GetParentPaddingOffset();
    int32_t to = FindSwapTarget(from, realOffset_ - frameRect.GetOffset() + paddingOffset);
    moveThroughIndex_ = to;
    auto grid = gridNode_.Upgrade();
    if (grid) {
        auto pattern = grid->GetPattern<GridPattern>();
        if (pattern) {
            auto& layoutInfo = pattern->GetMutableLayoutInfo();
            layoutInfo.fromDragIndex_ = forEachStartIndex_ + from;
            layoutInfo.toDragIndex_ = forEachStartIndex_ + to;
        }
    }
    if (to == from) {
        return;
    }
    HandleSwapAnimation(from, to);
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    forEach->FireOnMoveThrough(fromIndex_, to);
}

void GridItemDragManager::HandleOnItemDragUpdate(const GestureEvent& info)
{
    if (dragState_ != GridItemDragState::DRAGGING) {
        return;
    }
    if (CancelDragOnGridChange()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    OffsetF gestureOffset(info.GetOffsetX(), info.GetOffsetY());
    realOffset_ = gestureOffset + dragOffset_;
    SetPosition(realOffset_);
    int32_t from = GetIndex();
    if (from < 0) {
        return;
    }
    PointF point(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    auto frameRect = geometry->GetMarginFrameRect();
    HandleAutoScroll(from, point, frameRect);
    auto paddingOffset = GetParentPaddingOffset();
    ScaleNearbyItems(from, frameRect, realOffset_ - frameRect.GetOffset() + paddingOffset);
    ProcessSwap(from);
}

void GridItemDragManager::HandleOnItemDragEnd(const GestureEvent& info)
{
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_VOID(grid);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetHotZoneScrollCallback(nullptr);
    if (scrolling_) {
        pattern->HandleLeaveHotzoneEvent();
        scrolling_ = false;
    }
    HandleDragEndAnimation();
    int32_t to = GetIndex();
    pattern->GetMutableLayoutInfo().ClearOnMoveDragState();
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    if (fromIndex_ >= 0 && to >= 0) {
        forEach->FireOnMove(fromIndex_, to);
        forEach->FireOnDrop(to);
    }
    dragState_ = GridItemDragState::IDLE;
    moveThroughIndex_ = -1;
}

void GridItemDragManager::HandleOnItemDragCancel()
{
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_VOID(grid);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetHotZoneScrollCallback(nullptr);
    if (scrolling_) {
        pattern->HandleLeaveHotzoneEvent();
        scrolling_ = false;
    }
    autoScrollForward_ = false;
    inAutoScrollHotZone_ = false;
    HandleDragEndAnimation();
    pattern->GetMutableLayoutInfo().ClearOnMoveDragState();
    if (dragState_ == GridItemDragState::DRAGGING) {
        int32_t to = GetIndex();
        auto forEach = forEachNode_.Upgrade();
        CHECK_NULL_VOID(forEach);
        if (fromIndex_ >= 0 && to >= 0) {
            forEach->FireOnMove(fromIndex_, to);
            forEach->FireOnDrop(to);
        }
    }
    dragState_ = GridItemDragState::IDLE;
    moveThroughIndex_ = -1;
}

void GridItemDragManager::HandleDragEndAnimation()
{
    HandleZIndexAndPosition();
    HandleBackShadow();
    HandleTransformScale();
}

void GridItemDragManager::HandleZIndexAndPosition()
{
    AnimationOption option;
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(0, 1, 400, 38); /* 400:stiffness, 38:damping */
    option.SetCurve(curve);
    option.SetDuration(30); /* 30:duration */
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
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
        option.GetOnFinishEvent(), nullptr, context
    );
}

void GridItemDragManager::HandleBackShadow()
{
    AnimationOption option;
    isDragAnimationStopped_ = false;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(300); /* animate duration:300ms */
    option.SetOnFinishEvent([weak = WeakClaim(this)]() {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->isDragAnimationStopped_ = true;
    });
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            auto host = manager->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateBackShadow(manager->prevShadow_);
        },
        option.GetOnFinishEvent(), nullptr, context
    );
}

void GridItemDragManager::HandleTransformScale()
{
    AnimationOption option;
    /* 14:init velocity, 170:stiffness, 17:damping */
    option.SetCurve(AceType::MakeRefPtr<InterpolatingSpring>(14, 1, 170, 17));
    option.SetDuration(30);  /* 30:duration */
    option.SetDelay(150); /* 150:animate delay */
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto manager = weak.Upgrade();
            CHECK_NULL_VOID(manager);
            auto host = manager->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformScale(manager->prevScale_);
        },
        option.GetOnFinishEvent(), nullptr, context
    );
}

void GridItemDragManager::PrepareIrregularDragState(int32_t from, int32_t to, GridLayoutInfo& info)
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    if (!info.isOnMoveDragUpdate_) {
        for (int32_t i = 0; i < forEach->FrameCount(); ++i) {
            info.dragOriginalIndexMap_[forEachStartIndex_ + i] = forEachStartIndex_ + i;  // Use Grid-relative index
        }
        info.isOnMoveDragUpdate_ = true;
    }
    info.UpdateDragOriginalIndex(forEachStartIndex_ + from, forEachStartIndex_ + to);
}

void GridItemDragManager::HandleSwapAnimation(int32_t from, int32_t to)
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_VOID(grid);
    if (grid->CheckNeedForceMeasureAndLayout()) {
        auto pipeline = grid->GetContext();
        if (pipeline) {
            pipeline->FlushUITasks();
        }
    }

    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    auto& info = pattern->GetMutableLayoutInfo();
    PrepareIrregularDragState(from, to, info);

    AnimationOption option;
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(0, 1, 400, 38); /* 400:stiffness, 38:damping */
    option.SetCurve(curve);
    option.SetDuration(SWAP_ANIMATION_DURATION); /* 30:duration */
    AnimationUtils::Animate(option, [weak = forEachNode_, from, to]() {
            auto forEach = weak.Upgrade();
            CHECK_NULL_VOID(forEach);
            forEach->MoveData(from, to, true);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
            }
        },
        option.GetOnFinishEvent()
    );
}

GridItemDragManager::MovementBounds GridItemDragManager::ComputeMovementBounds(
    int32_t currentIndex, int32_t currentCol, int32_t currentRow,
    const OffsetF& delta, const GridLayoutInfo& info) const
{
    MovementBounds bounds;
    float mainDelta = delta.GetMainOffset(axis_);
    float crossDelta = delta.GetCrossOffset(axis_);
    ItemSpanInfo currentSpanInfo = GetIrregularItemInfoAndSpan(currentIndex);
    float mainItemSize = GetItemMainSize(currentIndex, info);
    float crossItemSize = GetItemCrossSize(currentIndex, info);
    float singleRowHeight = currentSpanInfo.rowSpan > 0 ? mainItemSize / currentSpanInfo.rowSpan : mainItemSize;
    float singleColWidth = currentSpanInfo.colSpan > 0 ? crossItemSize / currentSpanInfo.colSpan : crossItemSize;
    int32_t rowMove = static_cast<int32_t>(std::round(mainDelta / singleRowHeight));
    int32_t colMove = static_cast<int32_t>(std::round(crossDelta / singleColWidth));
    auto grid = gridNode_.Upgrade();
    if (grid) {
        auto layoutProperty = grid->GetLayoutProperty<GridLayoutProperty>();
        if (axis_ == Axis::HORIZONTAL && layoutProperty &&
            layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL) {
            rowMove = -rowMove;
        }
    }
    if (rowMove == 0 && colMove == 0) {
        bounds.zeroMove = true;
        return bounds;
    }
    bounds.startRow = std::min(currentRow, currentRow + rowMove);
    bounds.endRow = std::max(currentRow, currentRow + rowMove);
    bounds.startCol = 0;
    bounds.endCol = info.crossCount_ - 1;
    return bounds;
}

std::vector<int32_t> GridItemDragManager::CollectSwapCandidates(int32_t currentIndex,
    const OffsetF& delta, const GridLayoutInfo& info) const
{
    std::vector<int32_t> candidates;
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, candidates);
    auto [currentCol, currentRow] = info.GetItemPos(forEachStartIndex_ + currentIndex);
    if (currentCol < 0 || currentRow < 0) {
        return candidates;
    }
    auto bounds = ComputeMovementBounds(currentIndex, currentCol, currentRow, delta, info);
    if (bounds.zeroMove) {
        candidates.push_back(currentIndex);
        return candidates;
    }
    float mainGap = 0.0f;
    float crossGap = 0.0f;
    CalculateGaps(mainGap, crossGap, info);
    float mainSize = 0.0f;
    auto grid = gridNode_.Upgrade();
    if (grid) {
        auto gridGeometry = grid->GetGeometryNode();
        if (gridGeometry) {
            mainSize = gridGeometry->GetFrameSize().MainSize(axis_);
        }
    }
    std::set<int32_t> candidateSet;
    for (int32_t r = bounds.startRow; r <= bounds.endRow; ++r) {
        if (!IsRowInViewport(r, mainGap, mainSize, info)) {
            continue;
        }
        auto rowIt = info.gridMatrix_.find(r);
        if (rowIt == info.gridMatrix_.end()) {
            continue;
        }
        for (int32_t c = bounds.startCol; c <= bounds.endCol; ++c) {
            auto colIt = rowIt->second.find(c);
            if (colIt == rowIt->second.end()) {
                continue;
            }
            int32_t idx = std::abs(colIt->second);
            int32_t minIdx = std::max(forEachStartIndex_, info.startIndex_);
            int32_t maxIdx = std::min(info.endIndex_, totalCount_ + forEachStartIndex_ - 1);
            if (idx >= minIdx && idx <= maxIdx) {
                candidateSet.insert(idx - forEachStartIndex_);
            }
        }
    }
    candidates.insert(candidates.end(), candidateSet.begin(), candidateSet.end());
    return candidates;
}

bool GridItemDragManager::SimulateLayoutInRange(SimMatrix& matrix, const std::vector<int32_t>& order,
    const std::vector<SimSpanInfo>& spans, const GridLayoutInfo& info,
    int32_t startRebuild, int32_t endRebuild, int32_t from, int32_t to,
    float mainGap, float mainSize) const
{
    // Compute the last visible row as the base for PlaceItemInMatrix
    int32_t viewportEndRow = info.endMainLineIndex_;
    float pos = static_cast<float>(info.currentOffset_);
    for (auto it = info.lineHeightMap_.find(info.startMainLineIndex_);
         it != info.lineHeightMap_.end(); ++it) {
        float rowTop = pos;
        if (rowTop >= mainSize) {
            viewportEndRow = it->first - 1;
            break;
        }
        viewportEndRow = it->first;
        pos += it->second + mainGap;
    }

    // Extend by cacheCount to allow swapping items that are pushed off-screen
    // by large irregular items during auto-scroll drag scenarios.
    auto grid = gridNode_.Upgrade();
    if (grid) {
        auto layoutProperty = grid->GetLayoutProperty<GridLayoutProperty>();
        int32_t cacheCount = layoutProperty ? layoutProperty->GetCachedCountValue(info.defCachedCount_) : 0;
        // Walk cacheCount rows past the visible viewport
        auto it = info.lineHeightMap_.upper_bound(viewportEndRow);
        for (int32_t c = 0; c < cacheCount && it != info.lineHeightMap_.end(); ++c, ++it) {
            viewportEndRow = it->first;
        }
    }

    for (int32_t i = startRebuild; i <= endRebuild; ++i) {
        int32_t orderIdx = i - info.startIndex_;
        if (orderIdx < 0 || orderIdx >= static_cast<int32_t>(order.size())) {
            break;
        }
        int32_t itemIdx = order[orderIdx];
        auto [origCol, origRow] = info.GetItemPos(itemIdx);
        auto [newRow, newCol] = PlaceItemInMatrix(info, matrix, itemIdx,
            spans[itemIdx], info.crossCount_, viewportEndRow);
        if (newRow < 0) {
            return false;
        }
        if (origRow == newRow && origCol == newCol && i > std::max(from, to)) {
            break;
        }
    }
    return true;
}

bool GridItemDragManager::IsRowInViewport(int32_t row, float mainGap,
    float mainSize, const GridLayoutInfo& info) const
{
    auto heightIt = info.lineHeightMap_.find(row);
    if (heightIt == info.lineHeightMap_.end()) {
        return false;
    }
    float rowTop = static_cast<float>(info.currentOffset_) +
        info.GetHeightInRange(info.startMainLineIndex_, row, mainGap);
    float rowBottom = rowTop + heightIt->second;
    return (rowBottom > 0.0f && rowTop < mainSize);
}

void GridItemDragManager::CalculateGaps(float& mainGap, float& crossGap, const GridLayoutInfo& info) const
{
    mainGap = 0.0f;
    crossGap = 0.0f;
    auto grid = gridNode_.Upgrade();
    if (!grid) {
        return;
    }

    auto gridGeometry = grid->GetGeometryNode();
    if (!gridGeometry) {
        return;
    }

    auto viewScopeSize = gridGeometry->GetPaddingSize();
    auto layoutProperty = grid->GetLayoutProperty<GridLayoutProperty>();
    if (!layoutProperty) {
        return;
    }

    mainGap = GridUtils::GetMainGap(layoutProperty, viewScopeSize, axis_);
    crossGap = GridUtils::GetCrossGap(layoutProperty, viewScopeSize, axis_);
}

float GridItemDragManager::CalculateMainPosition(int32_t targetRow, float mainGap, const GridLayoutInfo& info) const
{
    float mainPos = info.currentOffset_;
    int32_t prevRow = info.startMainLineIndex_;

    for (auto iter = info.lineHeightMap_.find(info.startMainLineIndex_);
        iter != info.lineHeightMap_.end() && iter->first < targetRow; ++iter) {
        mainPos += iter->second;
        if (iter->first > prevRow && !NearZero(mainGap)) {
            mainPos += mainGap;
        }
        prevRow = iter->first;
    }

    return mainPos;
}


std::pair<std::vector<double>, float> GridItemDragManager::ResolveCrossLens(
    const RefPtr<GeometryNode>& gridGeometry,
    const RefPtr<GridLayoutProperty>& layoutProperty,
    float crossGap, const GridLayoutInfo& info) const
{
    std::vector<double> crossLens;
    float adjustedCrossGap = crossGap;
    float crossSize = gridGeometry ? gridGeometry->GetFrameSize().CrossSize(axis_) : 0.0f;
    if (layoutProperty) {
        auto rowsTemplate = layoutProperty->GetRowsTemplate().value_or("");
        auto columnsTemplate = layoutProperty->GetColumnsTemplate().value_or("");
        if (!rowsTemplate.empty()) {
            auto res = ParseTemplateArgs(
                GridUtils::ParseArgs(rowsTemplate), crossSize, crossGap, info.GetChildrenCount());
            crossLens = res.first;
            adjustedCrossGap = static_cast<float>(res.second);
        } else {
            auto res = ParseTemplateArgs(
                GridUtils::ParseArgs(columnsTemplate), crossSize, crossGap, info.GetChildrenCount());
            crossLens = res.first;
            adjustedCrossGap = static_cast<float>(res.second);
        }
    }
    if (crossLens.empty()) {
        crossLens.push_back(crossSize);
    }
    return { crossLens, adjustedCrossGap };
}

float GridItemDragManager::CalculateCrossPosition(int32_t col, float adjustedCrossGap,
    const std::vector<double>& crossLens, const RefPtr<GeometryNode>& gridGeometry) const
{
    bool hasPadding = gridGeometry && gridGeometry->GetPadding();
    float crossPos = 0.0f;
    if (axis_ == Axis::HORIZONTAL && hasPadding) {
        crossPos = gridGeometry->GetPadding()->top.value_or(0.0f);
    }
    for (int32_t i = 0; i < col && i < static_cast<int32_t>(crossLens.size()); ++i) {
        crossPos += static_cast<float>(crossLens[i]);
    }
    if (col > 0) {
        crossPos += col * adjustedCrossGap;
    }
    return crossPos;
}

std::optional<OffsetF> GridItemDragManager::ApplyAlignmentAndRTL(const RefPtr<FrameNode>& node,
    int32_t row, int32_t col, OffsetF offset, const std::vector<double>& crossLens,
    const RefPtr<GeometryNode>& gridGeometry,
    const RefPtr<GridLayoutProperty>& layoutProperty,
    const GridLayoutInfo& info) const
{
    auto childGeometry = node->GetGeometryNode();
    auto childSize = childGeometry->GetMarginFrameSize();
    auto lineHeightIt = info.lineHeightMap_.find(row);
    float lineHeight = lineHeightIt != info.lineHeightMap_.end() ? lineHeightIt->second : 0.0f;
    float colWidth = col < static_cast<int32_t>(crossLens.size()) ? static_cast<float>(crossLens[col]) : 0.0f;
    SizeF blockSize(colWidth, lineHeight, axis_);
    Alignment align = axis_ == Axis::VERTICAL ? Alignment::TOP_CENTER : Alignment::CENTER_LEFT;
    if (layoutProperty->GetPositionProperty()) {
        align = layoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }
    auto alignPos = Alignment::GetAlignPosition(blockSize, childSize, align);
    bool isRtl = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRtl) {
        SizeF paddedFrameSize = gridGeometry->GetFrameSize();
        if (gridGeometry->GetPadding()) {
            MinusPaddingToSize(*gridGeometry->GetPadding(), paddedFrameSize);
        }
        offset.SetX(paddedFrameSize.Width() - offset.GetX() - childSize.Width());
    }
    float padLeft = (gridGeometry && gridGeometry->GetPadding()) ?
        gridGeometry->GetPadding()->left.value_or(0.0f) : 0.0f;
    offset += OffsetF(padLeft, 0.0f);
    offset += alignPos;
    
    // Check if position is within the visible viewport
    float mainOffset = offset.GetMainOffset(axis_);
    float childMainSize = childSize.MainSize(axis_);
    float mainSize = gridGeometry ? gridGeometry->GetFrameSize().MainSize(axis_) : 0.0f;
    if (mainOffset + childMainSize <= 0.0f || mainOffset >= mainSize) {
        return std::nullopt;
    }
    return offset;
}

std::optional<OffsetF> GridItemDragManager::SearchRowForTarget(const std::map<int32_t, int32_t>& cols,
    int32_t targetIdx, int32_t row, const RefPtr<FrameNode>& node, int32_t colSpan,
    float mainGap, const std::vector<double>& crossLens, float adjustedCrossGap,
    const GridLayoutInfo& info) const
{
    for (const auto& [col, idx] : cols) {
        if (idx != targetIdx) {
            continue;
        }
        auto grid = gridNode_.Upgrade();
        auto gridGeometry = grid ? grid->GetGeometryNode() : nullptr;
        auto layoutProperty = grid ? grid->GetLayoutProperty<GridLayoutProperty>() : nullptr;
        float crossPos = CalculateCrossPosition(col, adjustedCrossGap, crossLens, gridGeometry);
        float mainPos = CalculateMainPosition(row, mainGap, info);
        bool hasPadding = gridGeometry && gridGeometry->GetPadding();
        if (axis_ == Axis::VERTICAL && hasPadding) {
            mainPos += gridGeometry->GetPadding()->top.value_or(0.0f);
        }
        OffsetF offset(crossPos, mainPos, axis_);
        if (!gridGeometry || !layoutProperty || !node || !node->GetGeometryNode()) {
            return offset;
        }
        return ApplyAlignmentAndRTL(node, row, col, offset, crossLens, gridGeometry, layoutProperty, info);
    }
    return std::nullopt;
}

std::optional<OffsetF> GridItemDragManager::FindItemPositionInMatrix(const SimMatrix& simMatrix,
    int32_t targetIdx, const RefPtr<FrameNode>& node, int32_t colSpan, float mainGap,
    const std::vector<double>& crossLens, float adjustedCrossGap, const GridLayoutInfo& info) const
{
    for (const auto& [row, cols] : simMatrix) {
        auto result = SearchRowForTarget(cols, targetIdx, row, node, colSpan, mainGap,
            crossLens, adjustedCrossGap, info);
        if (result.has_value()) {
            return result;
        }
    }
    return std::nullopt;
}

std::optional<OffsetF> GridItemDragManager::CalculateFromNewPosition(int32_t from, int32_t to,
    const GridLayoutInfo& info, std::vector<SimSpanInfo>& spans, float mainGap,
    const std::vector<double>& crossLens, float adjustedCrossGap) const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, std::nullopt);
    // drag item not in screen
    if (forEachStartIndex_ + from < info.startIndex_ || forEachStartIndex_ + from > info.endIndex_
        || forEachStartIndex_ + to < info.startIndex_ || forEachStartIndex_ + to > info.endIndex_) {
        return std::nullopt;
    }

    int32_t startRebuild = std::max(forEachStartIndex_ + std::min(from, to), info.startIndex_);
    int32_t endRebuild = std::min(forEachStartIndex_ + std::max(from, to), info.endIndex_);

    SimMatrix simMatrix;
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_RETURN(grid, std::nullopt);
    float mainSize = 0.0f;
    auto gridGeometry = grid->GetGeometryNode();
    if (gridGeometry) {
        mainSize = gridGeometry->GetFrameSize().MainSize(axis_);
    }
    if (!CopyLayoutToMatrix(simMatrix, spans, info, startRebuild, mainGap, mainSize)) {
        return std::nullopt;
    }

    std::vector<int32_t> order;
    for (int32_t i = info.startIndex_; i <= info.endIndex_; ++i) {
        order.push_back(i);
    }

    int32_t localFrom = forEachStartIndex_ + from - info.startIndex_;
    int32_t localTo = forEachStartIndex_ + to - info.startIndex_;
    ApplyMoveToArray(order, localFrom, localTo);

    int32_t simFrom = forEachStartIndex_ + from;
    int32_t simTo = forEachStartIndex_ + to;
    if (!SimulateLayoutInRange(simMatrix, order, spans, info, startRebuild, endRebuild, simFrom, simTo,
        mainGap, mainSize)) {
        return std::nullopt;
    }

    auto fromNode = forEach->GetFrameNode(from);
    CHECK_NULL_RETURN(fromNode, std::nullopt);

    auto fromPattern = fromNode->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(fromPattern, std::nullopt);

    auto irregularInfo = fromPattern->GetIrregularItemInfo();
    int32_t fromColSpan = irregularInfo.has_value() ? irregularInfo->crossSpan : 1;
    int32_t targetIdx = forEachStartIndex_ + from;

    return FindItemPositionInMatrix(simMatrix, targetIdx, fromNode, fromColSpan, mainGap,
        crossLens, adjustedCrossGap, info);
}

float GridItemDragManager::CalculateDistance(const OffsetF& pos1, const OffsetF& pos2) const
{
    return std::sqrt(
        std::pow(pos1.GetX() - pos2.GetX(), POWER_FOR_DISTANCE) +
        std::pow(pos1.GetY() - pos2.GetY(), POWER_FOR_DISTANCE)
    );
}

int32_t GridItemDragManager::SelectBestCandidate(int32_t currentIndex, bool movingDown,
    int32_t currentBest, int32_t candidate, float candidateDistance, float bestDistance) const
{
    if (candidateDistance < bestDistance) {
        return candidate;
    }

    if (!NearEqual(candidateDistance, bestDistance)) {
        return currentBest;
    }

    if (candidate == currentIndex) {
        return candidate;
    }

    if (currentBest == currentIndex) {
        return currentBest;
    }

    if (movingDown) {
        return (candidate > currentBest) ? candidate : currentBest;
    } else {
        return (candidate < currentBest) ? candidate : currentBest;
    }
}

bool GridItemDragManager::IsItemInViewport(int32_t currentIndex, const GridLayoutInfo& info) const
{
    int32_t globalIndex = forEachStartIndex_ + currentIndex;
    if (globalIndex < info.startIndex_ || globalIndex > info.endIndex_) {
        return false;
    }
    auto [currentCol, currentRow] = info.GetItemPos(globalIndex);
    if (currentCol < 0 || currentRow < 0) {
        return false;
    }
    // Check if the dragged item (including multi-row span) is visible in viewport
    float mainGap = 0.0f;
    float crossGap = 0.0f;
    CalculateGaps(mainGap, crossGap, info);
    float mainSize = 0.0f;
    auto grid = gridNode_.Upgrade();
    if (grid) {
        auto gridGeometry = grid->GetGeometryNode();
        if (gridGeometry) {
            mainSize = gridGeometry->GetFrameSize().MainSize(axis_);
        }
    }
    ItemSpanInfo spanInfo = GetIrregularItemInfoAndSpan(currentIndex);
    int32_t rowSpan = spanInfo.isIrregular ? spanInfo.rowSpan : 1;
    int32_t endRow = currentRow + rowSpan - 1;
    for (int32_t row = currentRow; row <= endRow; ++row) {
        if (IsRowInViewport(row, mainGap, mainSize, info)) {
            return true;
        }
    }
    return false;
}

std::pair<int32_t, int32_t> GridItemDragManager::GetRowRangeForItem(
    int32_t currentIndex, const GridLayoutInfo& info) const
{
    int32_t globalIndex = forEachStartIndex_ + currentIndex;
    auto [currentCol, currentRow] = info.GetItemPos(globalIndex);
    ItemSpanInfo spanInfo = GetIrregularItemInfoAndSpan(currentIndex);
    int32_t rowSpan = spanInfo.isIrregular ? spanInfo.rowSpan : 1;
    return { currentRow, currentRow + rowSpan - 1 };
}

bool GridItemDragManager::IsCandidateValidForAutoScroll(int32_t candidate,
    int32_t currentRow, int32_t endRow, const GridLayoutInfo& info) const
{
    auto [candidateCol, candidateRow] = info.GetItemPos(forEachStartIndex_ + candidate);
    if (candidateCol < 0 || candidateRow < 0) {
        return false;
    }
    bool isForwardScroll = autoScrollForward_;
    auto grid = gridNode_.Upgrade();
    if (grid && axis_ == Axis::HORIZONTAL) {
        auto layoutProperty = grid->GetLayoutProperty<GridLayoutProperty>();
        if (layoutProperty && layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL) {
            isForwardScroll = !isForwardScroll;
        }
    }
    if (isForwardScroll && candidateRow < currentRow) {
        return false;
    }
    if (!isForwardScroll && candidateRow > endRow) {
        return false;
    }
    return true;
}

int32_t GridItemDragManager::FindBestCandidate(int32_t currentIndex,
    const std::vector<int32_t>& candidates, const OffsetF& delta,
    int32_t currentRow, int32_t endRow, const GridLayoutInfo& info) const
{
    auto spans = CollectSpanInfo(info);
    float mainGap = 0.0f;
    float crossGap = 0.0f;
    CalculateGaps(mainGap, crossGap, info);
    auto grid = gridNode_.Upgrade();
    auto gridGeometry = grid ? grid->GetGeometryNode() : nullptr;
    auto layoutProperty = grid ? grid->GetLayoutProperty<GridLayoutProperty>() : nullptr;
    auto [crossLens, adjustedCrossGap] = ResolveCrossLens(gridGeometry, layoutProperty, crossGap, info);

    OffsetF dragPosition = realOffset_ + GetParentPaddingOffset();
    int32_t bestCandidate = currentIndex;
    float minDistance = std::numeric_limits<float>::max();
    float mainDelta = delta.GetMainOffset(axis_);
    bool movingDown = Positive(mainDelta);
    for (int32_t candidate : candidates) {
        if (inAutoScrollHotZone_ && candidate != currentIndex) {
            if (!IsCandidateValidForAutoScroll(candidate, currentRow, endRow, info)) {
                continue;
            }
        }
        auto newPositionOpt = CalculateFromNewPosition(currentIndex, candidate, info,
            spans, mainGap, crossLens, adjustedCrossGap);
        if (!newPositionOpt.has_value()) {
            continue;
        }
        OffsetF newPosition = newPositionOpt.value();
        float distance = CalculateDistance(dragPosition, newPosition);
        bestCandidate = SelectBestCandidate(currentIndex, movingDown, bestCandidate, candidate, distance, minDistance);
        if (distance < minDistance) {
            minDistance = distance;
        }
    }
    return bestCandidate;
}

int32_t GridItemDragManager::FindSwapTarget(int32_t currentIndex, const OffsetF& delta)
{
    currentIndex_ = currentIndex;
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_RETURN(grid, currentIndex);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, currentIndex);
    auto& info = pattern->GetMutableLayoutInfo();
    if (!IsItemInViewport(currentIndex, info)) {
        return currentIndex;
    }
    auto candidates = CollectSwapCandidates(currentIndex, delta, info);
    if (candidates.empty()) {
        return currentIndex;
    }
    auto [currentRow, endRow] = GetRowRangeForItem(currentIndex, info);
    return FindBestCandidate(currentIndex, candidates, delta, currentRow, endRow, info);
}

float GridItemDragManager::GetItemMainSize(int32_t currentIndex, const GridLayoutInfo& info) const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, DEFAULT_ITEM_SIZE);
    
    auto node = forEach->GetFrameNode(currentIndex);
    if (!node) {
        // Item not rendered, try to get the row height of the current item's row
        auto [col, row] = info.GetItemPos(forEachStartIndex_ + currentIndex);
        auto rowIt = info.lineHeightMap_.find(row);
        if (rowIt != info.lineHeightMap_.end()) {
            return rowIt->second;
        }
        return DEFAULT_ITEM_SIZE;
    }
    
    // Item rendered, get actual geometry size
    auto geometry = node->GetGeometryNode();
    CHECK_NULL_RETURN(geometry, DEFAULT_ITEM_SIZE);
    
    return geometry->GetFrameSize().MainSize(axis_);
}

float GridItemDragManager::GetItemCrossSize(int32_t currentIndex, const GridLayoutInfo& info) const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, DEFAULT_ITEM_SIZE);

    auto node = forEach->GetFrameNode(currentIndex);
    if (!node) {
        return DEFAULT_ITEM_SIZE;
    }

    auto geometry = node->GetGeometryNode();
    CHECK_NULL_RETURN(geometry, DEFAULT_ITEM_SIZE);
    
    return geometry->GetFrameSize().CrossSize(axis_);
}

int32_t GridItemDragManager::GetColSpanForIrregularItem(int32_t crossSpan) const
{
    auto grid = gridNode_.Upgrade();
    if (!grid) {
        return crossSpan;
    }

    auto gridPattern = grid->GetPattern<GridPattern>();
    if (!gridPattern) {
        return crossSpan;
    }

    int32_t crossCount = gridPattern->GetCrossCount();
    return (crossCount > 1) ? crossSpan : 1;
}

GridItemDragManager::ItemSpanInfo GridItemDragManager::GetIrregularItemInfoAndSpan(int32_t index) const
{
    ItemSpanInfo spanInfo;

    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, spanInfo);

    auto currentNode = forEach->GetFrameNode(index);
    CHECK_NULL_RETURN(currentNode, spanInfo);

    auto currentPattern = currentNode->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(currentPattern, spanInfo);

    auto currentInfo = currentPattern->GetIrregularItemInfo();
    if (!currentInfo.has_value()) {
        return spanInfo;
    }

    spanInfo.rowSpan = currentInfo->mainSpan;
    spanInfo.colSpan = GetColSpanForIrregularItem(currentInfo->crossSpan);
    spanInfo.isIrregular = true;

    return spanInfo;
}

GridItemDragManager::SimSpanInfo GridItemDragManager::ResolveItemSpan(
    int32_t forEachIdx, int32_t crossCount) const
{
    SimSpanInfo span;
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, span);
    auto node = forEach->GetFrameNode(forEachIdx);
    CHECK_NULL_RETURN(node, span);
    auto pattern = node->GetPattern<GridItemPattern>();
    if (!pattern) {
        return span;
    }
    auto irregularInfo = pattern->GetIrregularItemInfo();
    if (!irregularInfo.has_value()) {
        return span;
    }
    span.rowSpan = irregularInfo->mainSpan;
    span.colSpan = (crossCount > 1) ? irregularInfo->crossSpan : 1;
    return span;
}

std::vector<GridItemDragManager::SimSpanInfo> GridItemDragManager::CollectSpanInfo(const GridLayoutInfo& info) const
{
    std::vector<SimSpanInfo> spans(forEachStartIndex_ + totalCount_);
    auto forEach = forEachNode_.Upgrade();
    if (!forEach) {
        return spans;
    }
    auto grid = gridNode_.Upgrade();
    if (!grid) {
        return spans;
    }
    int32_t crossCount = 1;
    auto gridPattern = grid->GetPattern<GridPattern>();
    if (gridPattern) {
        crossCount = gridPattern->GetCrossCount();
    }
    float mainGap = 0.0f;
    float crossGap = 0.0f;
    CalculateGaps(mainGap, crossGap, info);
    float mainSize = 0.0f;
    auto gridGeometry = grid->GetGeometryNode();
    if (gridGeometry) {
        mainSize = gridGeometry->GetFrameSize().MainSize(axis_);
    }
    // collect ForEach items
    for (int32_t forEachIdx = 0; forEachIdx < totalCount_; ++forEachIdx) {
        int32_t gridIndex = forEachStartIndex_ + forEachIdx;
        if (gridIndex < info.startIndex_ || gridIndex > info.endIndex_) {
            continue;
        }
        auto [col, row] = info.GetItemPos(gridIndex);
        if (col < 0 || !IsRowInViewport(row, mainGap, mainSize, info)) {
            continue;
        }
        spans[gridIndex] = ResolveItemSpan(forEachIdx, crossCount);
    }
    return spans;
}

void GridItemDragManager::ApplyMoveToArray(std::vector<int32_t>& order, int32_t from, int32_t to)
{
    int32_t movedItem = order[from];
    if (from < to) {
        for (int32_t i = from; i < to; ++i) {
            order[i] = order[i + 1];
        }
    } else {
        for (int32_t i = from; i > to; --i) {
            order[i] = order[i - 1];
        }
    }
    order[to] = movedItem;
}

int32_t GridItemDragManager::FindAvailableColumn(
    const SimMatrix& matrix, int32_t row, int32_t colSpan, int32_t crossCount) const
{
    auto it = matrix.find(row);
    if (it == matrix.end()) {
        return 0;
    }
    if (static_cast<int32_t>(it->second.size()) + colSpan > crossCount) {
        return -1;
    }
    for (int32_t c = 0; c <= crossCount - colSpan; ++c) {
        bool ok = true;
        for (int32_t j = 0; j < colSpan; ++j) {
            if (it->second.find(c + j) != it->second.end()) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return c;
        }
    }
    return -1;
}

int32_t GridItemDragManager::FindMaxIndexRow(const SimMatrix& matrix)
{
    int32_t maxIdx = -1;
    int32_t startRow = 0;
    for (const auto& [row, cols] : matrix) {
        for (const auto& [col, val] : cols) {
            if (val > 0 && val > maxIdx) {
                maxIdx = val;
                startRow = row;
            }
        }
    }
    return startRow;
}

void GridItemDragManager::PrintSimMatrix(const SimMatrix& matrix)
{
    TAG_LOGI(AceLogTag::ACE_GRID, "-----------start print simMatrix------------");
    for (const auto& item : matrix) {
        std::string res;
        res.append(std::to_string(item.first));
        res.append(": ");
        for (const auto& index : item.second) {
            res.append("[")
                .append(std::to_string(index.first))
                .append(",")
                .append(std::to_string(index.second))
                .append("] ");
        }
        TAG_LOGI(AceLogTag::ACE_GRID, "%{public}s", res.c_str());
    }
    TAG_LOGI(AceLogTag::ACE_GRID, "-----------end print simMatrix------------");
}

int32_t GridItemDragManager::FindPlacementStartRow(const SimMatrix& matrix,
    const GridLayoutInfo& info) const
{
    if (!matrix.empty()) {
        return FindMaxIndexRow(matrix);
    }
    if (!info.gridMatrix_.empty()) {
        return info.gridMatrix_.begin()->first;
    }
    return 0;
}

std::pair<int32_t, int32_t> GridItemDragManager::PlaceItemInMatrix(
    const GridLayoutInfo& info, SimMatrix& matrix, int32_t itemIdx,
    const SimSpanInfo& span, int32_t crossCount, int32_t viewportEndRow) const
{
    if (span.colSpan > crossCount) {
        return { -1, -1 };
    }
    int32_t startRow = FindPlacementStartRow(matrix, info);
    for (int32_t row = startRow; row <= viewportEndRow; ++row) {
        int32_t col = FindAvailableColumn(matrix, row, span.colSpan, crossCount);
        if (col == -1) {
            continue;
        }
        for (int32_t r = 0; r < span.rowSpan; ++r) {
            for (int32_t c = 0; c < span.colSpan; ++c) {
                matrix[row + r][col + c] = -itemIdx;
            }
        }
        matrix[row][col] = itemIdx;
        return { row, col };
    }
    return { -1, -1 };
}

int32_t GridItemDragManager::CalculateColSpan(const std::map<int32_t, int32_t>& rowCols,
    int32_t col, int32_t itemIdx, int32_t crossCount) const
{
    int32_t colSpan = 1;
    for (int32_t j = col + 1; j < crossCount; ++j) {
        auto colIt = rowCols.find(j);
        if (colIt == rowCols.end()) {
            break;
        }
        if (std::abs(colIt->second) == itemIdx) {
            colSpan++;
        } else {
            break;
        }
    }
    return colSpan;
}

int32_t GridItemDragManager::CalculateRowSpan(const GridLayoutInfo& info,
    int32_t row, int32_t col, int32_t itemIdx) const
{
    int32_t rowSpan = 1;
    int32_t nextRow = row + 1;
    auto rowIt = info.gridMatrix_.find(nextRow);
    while (rowIt != info.gridMatrix_.end()) {
        auto colIt = rowIt->second.find(col);
        if (colIt == rowIt->second.end()) {
            break;
        }
        if (std::abs(colIt->second) == itemIdx) {
            rowSpan++;
            nextRow++;
            rowIt = info.gridMatrix_.find(nextRow);
        } else {
            break;
        }
    }
    return rowSpan;
}

void GridItemDragManager::CalculateSpanInfo(const GridLayoutInfo& info,
    int32_t itemIdx, int32_t row, int32_t col, std::vector<SimSpanInfo>& spans) const
{
    auto origIt = info.gridMatrix_.find(row);
    if (origIt == info.gridMatrix_.end()) {
        return;
    }

    if (origIt->second.find(col) == origIt->second.end()) {
        return;
    }

    spans[itemIdx].colSpan = CalculateColSpan(origIt->second, col, itemIdx, info.crossCount_);
    spans[itemIdx].rowSpan = CalculateRowSpan(info, row, col, itemIdx);
}

void GridItemDragManager::FillMatrixWithItem(SimMatrix& matrix, int32_t itemIdx,
    int32_t row, int32_t col, const std::vector<SimSpanInfo>& spans) const
{
    for (int32_t r = 0; r < spans[itemIdx].rowSpan; ++r) {
        for (int32_t c = 0; c < spans[itemIdx].colSpan; ++c) {
            matrix[row + r][col + c] = -itemIdx;
        }
    }
    matrix[row][col] = itemIdx;
}

bool GridItemDragManager::CopyLayoutToMatrix(SimMatrix& matrix,
    std::vector<SimSpanInfo>& spans, const GridLayoutInfo& info, int32_t count,
    float mainGap, float mainSize) const
{
    int32_t minItemId = count;
    for (const auto& [rowIdx, cols] : info.gridMatrix_) {
        for (const auto& [colIdx, idx] : cols) {
            if (idx >= 0 && idx < minItemId) {
                minItemId = idx;
            }
        }
    }

    int32_t forEachNotIncludeIndex = std::max(info.startIndex_, forEachStartIndex_);
    for (int32_t i = minItemId; i < count; ++i) {
        auto [col, row] = info.GetItemPos(i);
        if (row < 0 || col < 0) {
            continue;
        }

        // Calculate span info for items not covered by CollectSpanInfo:
        // 1. Items from other ForEach nodes (i < forEachNotIncludeIndex)
        // 2. Items off-screen (CollectSpanInfo now skips off-screen items)
        if (i < forEachNotIncludeIndex || !IsRowInViewport(row, mainGap, mainSize, info)) {
            CalculateSpanInfo(info, i, row, col, spans);
        }

        FillMatrixWithItem(matrix, i, row, col, spans);
    }
    return true;
}

bool GridItemDragManager::IsInHotZone(int32_t index, const RectF& frameRect) const
{
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_RETURN(grid, false);

    auto gridGeometry = grid->GetGeometryNode();
    CHECK_NULL_RETURN(gridGeometry, false);

    auto gridSize = gridGeometry->GetFrameSize();

    float hotZone = axis_ == Axis::VERTICAL ? HOT_ZONE_HEIGHT.ConvertToPx() : HOT_ZONE_WIDTH.ConvertToPx();

    float startOffset = frameRect.GetOffset().GetMainOffset(axis_);
    float endOffset = startOffset + frameRect.GetSize().MainSize(axis_);

    bool reachStart = (index == 0 && startOffset > hotZone);
    bool reachEnd = (index == totalCount_ - 1) &&
                    endOffset < (gridSize.MainSize(axis_) - hotZone);

    return (!reachStart && !reachEnd);
}

void GridItemDragManager::HandleAutoScroll(int32_t index, const PointF& point, const RectF& frameRect)
{
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_VOID(grid);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);

    if (IsInHotZone(index, frameRect) && pattern->GetScrollable()) {
        auto gridGeometry = grid->GetGeometryNode();
        inAutoScrollHotZone_ = false;
        if (gridGeometry) {
            auto gridGlobalOffset = grid->GetTransformRelativeOffset();
            float gridMainOffset =
                (axis_ == Axis::VERTICAL) ? gridGlobalOffset.GetY() : gridGlobalOffset.GetX();
            float gridMainSize = gridGeometry->GetFrameSize().MainSize(axis_);
            auto pointMain = (axis_ == Axis::VERTICAL) ? point.GetY() : point.GetX();
            float hotZone = axis_ == Axis::VERTICAL ? HOT_ZONE_HEIGHT.ConvertToPx() : HOT_ZONE_WIDTH.ConvertToPx();
            float relativeMain = pointMain - gridMainOffset;
            if (relativeMain < hotZone && !pattern->IsAtTop()) {
                inAutoScrollHotZone_ = true;
                autoScrollForward_ = false;
            } else if (relativeMain > gridMainSize - hotZone && !pattern->IsAtBottom()) {
                inAutoScrollHotZone_ = true;
                autoScrollForward_ = true;
            }
        }
        pattern->HandleMoveEventInComp(point, true);

        if (!scrolling_) {
            pattern->SetHotZoneScrollCallback([weak = WeakClaim(this)]() {
                auto manager = weak.Upgrade();
                CHECK_NULL_VOID(manager);
                manager->HandleScrollCallback();
            });
            scrolling_ = true;
        }
    } else {
        inAutoScrollHotZone_ = false;
        if (scrolling_) {
            pattern->HandleLeaveHotzoneEvent();
            pattern->SetHotZoneScrollCallback(nullptr);
            scrolling_ = false;
        }
    }
}

void GridItemDragManager::StopAutoScroll()
{
    auto grid = gridNode_.Upgrade();
    if (!grid) {
        return;
    }
    auto pattern = grid->GetPattern<GridPattern>();
    if (!pattern) {
        return;
    }
    if (scrolling_) {
        pattern->HandleLeaveHotzoneEvent();
        scrolling_ = false;
        autoScrollForward_ = false;
        inAutoScrollHotZone_ = false;
    }
    pattern->SetHotZoneScrollCallback(nullptr);
}

void GridItemDragManager::HandleScrollCallback()
{
    if (dragState_ != GridItemDragState::DRAGGING) {
        StopAutoScroll();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto frameRect = geometry->GetMarginFrameRect();
    int32_t from = GetIndex();
    if (from < 0) {
        return;
    }
    if (scrolling_ && !IsInHotZone(from, frameRect)) {
        auto grid = gridNode_.Upgrade();
        CHECK_NULL_VOID(grid);
        auto pattern = grid->GetPattern<GridPattern>();
        CHECK_NULL_VOID(pattern);

        pattern->HandleLeaveHotzoneEvent();
        pattern->SetHotZoneScrollCallback(nullptr);
        scrolling_ = false;
        autoScrollForward_ = false;
        inAutoScrollHotZone_ = false;
    }
    auto paddingOffset = GetParentPaddingOffset();
    ScaleNearbyItems(from, frameRect, realOffset_ - frameRect.GetOffset() + paddingOffset);
    ProcessSwap(from);
}

void GridItemDragManager::SetNearbyNodeScale(RefPtr<FrameNode> node, float scale)
{
    CHECK_NULL_VOID(node);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto it = prevScaleNode_.find(renderContext);
    VectorF prevScale = it != prevScaleNode_.end() ? it->second :
        renderContext->GetTransformScaleValue({1.0f, 1.0f});
    renderContext->UpdateTransformScale(prevScale * scale);
    scaleNode_.emplace(renderContext, prevScale);
}

void GridItemDragManager::ResetPrevScaleNode()
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

int32_t GridItemDragManager::FindNeighborIndex(int32_t row, int32_t col, const GridLayoutInfo& info) const
{
    auto rowIt = info.gridMatrix_.find(row);
    if (rowIt == info.gridMatrix_.end()) {
        return -1;
    }
    auto colIt = rowIt->second.find(col);
    if (colIt == rowIt->second.end()) {
        return -1;
    }
    return std::abs(colIt->second) - forEachStartIndex_;
}

bool GridItemDragManager::ScaleMainAxisNeighbor(int32_t currentIndex, int32_t currentRow, int32_t currentCol,
    int32_t mainRowStep, int32_t colSpan, const RectF& rect, float mainDelta,
    int32_t startIdx, int32_t endIdx, const GridLayoutInfo& info,
    const RefPtr<ForEachBaseNode>& forEach)
{
    int32_t targetRow = currentRow + mainRowStep;
    std::set<int32_t> scaledIndices;
    bool anyScaled = false;
    for (int32_t col = currentCol; col < currentCol + colSpan; ++col) {
        int32_t mainIdx = FindNeighborIndex(targetRow, col, info);
        if (mainIdx < 0 || mainIdx == currentIndex || mainIdx < startIdx || mainIdx > endIdx) {
            continue;
        }
        if (scaledIndices.count(mainIdx)) {
            continue;
        }
        scaledIndices.insert(mainIdx);
        auto node = forEach->GetFrameNode(mainIdx);
        if (!node) {
            continue;
        }
        auto geometry = node->GetGeometryNode();
        if (!geometry) {
            continue;
        }
        auto nearRect = geometry->GetMarginFrameRect();
        float c0 = rect.GetOffset().GetMainOffset(axis_) + rect.GetSize().MainSize(axis_) / 2;
        float c1 = nearRect.GetOffset().GetMainOffset(axis_) + nearRect.GetSize().MainSize(axis_) / 2;
        if (NearEqual(c0, c1)) {
            continue;
        }
        float sharped = Curves::SHARP->MoveInternal(std::abs(mainDelta / (c1 - c0)));
        float scale = 1 - sharped * NEARBY_SCALE_RATIO;
        SetNearbyNodeScale(node, scale);
        anyScaled = anyScaled || !NearEqual(scale, 1.0f);
    }
    return anyScaled;
}

bool GridItemDragManager::ScaleCrossAxisNeighbor(int32_t currentIndex, int32_t currentRow, int32_t currentCol,
    int32_t crossColStep, int32_t rowSpan, const RectF& rect, float crossDelta,
    int32_t startIdx, int32_t endIdx, const GridLayoutInfo& info,
    const RefPtr<ForEachBaseNode>& forEach)
{
    int32_t targetCol = currentCol + crossColStep;
    std::set<int32_t> scaledIndices;
    bool anyScaled = false;
    for (int32_t row = currentRow; row < currentRow + rowSpan; ++row) {
        int32_t crossIdx = FindNeighborIndex(row, targetCol, info);
        if (crossIdx < 0 || crossIdx == currentIndex || crossIdx < startIdx || crossIdx > endIdx) {
            continue;
        }
        if (scaledIndices.count(crossIdx)) {
            continue;
        }
        scaledIndices.insert(crossIdx);
        auto node = forEach->GetFrameNode(crossIdx);
        if (!node) {
            continue;
        }
        auto geometry = node->GetGeometryNode();
        if (!geometry) {
            continue;
        }
        auto nearRect = geometry->GetMarginFrameRect();
        float dragMainStart = rect.GetOffset().GetMainOffset(axis_);
        float dragMainEnd = dragMainStart + rect.GetSize().MainSize(axis_);
        float nearMainStart = nearRect.GetOffset().GetMainOffset(axis_);
        float nearMainEnd = nearMainStart + nearRect.GetSize().MainSize(axis_);
        if (nearMainEnd <= dragMainStart || nearMainStart >= dragMainEnd) {
            continue;
        }
        Axis crossAxis = (axis_ == Axis::VERTICAL) ? Axis::HORIZONTAL : Axis::VERTICAL;
        float c0 = rect.GetOffset().GetMainOffset(crossAxis) + rect.GetSize().MainSize(crossAxis) / 2;
        float c1 = nearRect.GetOffset().GetMainOffset(crossAxis) + nearRect.GetSize().MainSize(crossAxis) / 2;
        if (NearEqual(c0, c1)) {
            continue;
        }
        float sharped = Curves::SHARP->MoveInternal(std::abs(crossDelta / (c1 - c0)));
        float scale = 1 - sharped * NEARBY_SCALE_RATIO;
        SetNearbyNodeScale(node, scale);
        anyScaled = anyScaled || !NearEqual(scale, 1.0f);
    }
    return anyScaled;
}

void GridItemDragManager::ScaleDiagonalNeighbor(int32_t currentIndex, int32_t currentRow, int32_t currentCol,
    int32_t mainRowStep, int32_t crossColStep, const RectF& rect, const OffsetF& delta,
    int32_t startIdx, int32_t endIdx, const GridLayoutInfo& info,
    const RefPtr<ForEachBaseNode>& forEach)
{
    int32_t diagIdx = FindNeighborIndex(currentRow + mainRowStep, currentCol + crossColStep, info);
    if (diagIdx < 0 || diagIdx == currentIndex || diagIdx < startIdx || diagIdx > endIdx) {
        return;
    }
    auto node = forEach->GetFrameNode(diagIdx);
    CHECK_NULL_VOID(node);
    auto geometry = node->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto nearRect = geometry->GetMarginFrameRect();
    OffsetF c0 = rect.GetOffset() + OffsetF(rect.Width() / 2, rect.Height() / 2);
    OffsetF c1 = nearRect.GetOffset() + OffsetF(nearRect.Width() / 2, nearRect.Height() / 2);
    OffsetF c2 = c0 + delta;
    float d0 = c0.GetDistance(c1);
    if (NearZero(d0)) {
        return;
    }
    float d1 = c2.GetDistance(c1);
    float sharped = Curves::SHARP->MoveInternal(std::abs(1 - d1 / d0));
    float scale = 1 - sharped * NEARBY_SCALE_RATIO;
    SetNearbyNodeScale(node, scale);
}

void GridItemDragManager::ScaleNearbyItems(int32_t currentIndex, const RectF& rect, const OffsetF& delta)
{
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_VOID(grid);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    auto& info = pattern->GetMutableLayoutInfo();

    int32_t globalIndex = forEachStartIndex_ + currentIndex;
    auto [currentCol, currentRow] = info.GetItemPos(globalIndex);
    if (currentCol < 0 || currentRow < 0) {
        ResetPrevScaleNode();
        return;
    }

    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);

    float mainDelta = delta.GetMainOffset(axis_);
    float crossDelta = delta.GetCrossOffset(axis_);
    auto spanInfo = GetIrregularItemInfoAndSpan(currentIndex);
    int32_t mainRowStep = Positive(mainDelta) ? spanInfo.rowSpan : (Negative(mainDelta) ? -1 : 0);
    int32_t crossColStep = Positive(crossDelta) ? spanInfo.colSpan : (Negative(crossDelta) ? -1 : 0);
    auto layoutProperty = grid->GetLayoutProperty<GridLayoutProperty>();
    if (layoutProperty && layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL) {
        if (axis_ == Axis::VERTICAL) {
            crossColStep = -crossColStep;
        } else {
            mainRowStep = -mainRowStep;
        }
    }

    int32_t startIdx = info.startIndex_ - forEachStartIndex_;
    int32_t endIdx = info.endIndex_ - forEachStartIndex_;

    bool mainScaled = false;
    if (mainRowStep != 0) {
        mainScaled = ScaleMainAxisNeighbor(currentIndex, currentRow, currentCol,
            mainRowStep, spanInfo.colSpan, rect, mainDelta, startIdx, endIdx, info, forEach);
    }

    bool crossScaled = false;
    if (crossColStep != 0) {
        crossScaled = ScaleCrossAxisNeighbor(currentIndex, currentRow, currentCol,
            crossColStep, spanInfo.rowSpan, rect, crossDelta, startIdx, endIdx, info, forEach);
    }

    if (mainScaled && crossScaled && mainRowStep != 0 && crossColStep != 0) {
        ScaleDiagonalNeighbor(currentIndex, currentRow, currentCol,
            mainRowStep, crossColStep, rect, delta, startIdx, endIdx, info, forEach);
    }

    ResetPrevScaleNode();
}

void GridItemDragManager::SetPosition(const OffsetF& offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdatePosition({ Dimension(offset.GetX(), DimensionUnit::PX),
        Dimension(offset.GetY(), DimensionUnit::PX) });
}

int32_t GridItemDragManager::GetIndex() const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, -1);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    return forEach->GetFrameNodeIndex(host);
}
} // namespace OHOS::Ace::NG
