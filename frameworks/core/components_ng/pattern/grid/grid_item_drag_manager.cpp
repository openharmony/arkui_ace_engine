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

#include "core/components_ng/pattern/grid/grid_item_drag_manager.h"

#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "base/memory/ace_type.h"
#include "base/utils/multi_thread.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/gestures/gesture_event.h"
#include <numeric>
#include <vector>
#include <cmath>

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_SCALE = 1.05f;
constexpr int32_t DEFAULT_Z_INDEX = 100;
constexpr float HOT_ZONE_SIZE_VP = 59.0f;
constexpr float MOVE_THRESHOLD = 0.5f;
constexpr float DEFAULT_ITEM_SIZE = 100.0f;
constexpr int32_t LONG_PRESS_ANIMATION_DURATION = 300;
constexpr int32_t SWAP_ANIMATION_DURATION = 30;
}

RefPtr<FrameNode> GridItemDragManager::GetGridFrameNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParentFrameNode();
    CHECK_NULL_RETURN(parent, nullptr);
    if (parent->GetTag() == V2::GRID_ETS_TAG) {
        return parent;
    }
    return nullptr;
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

    HandleDragEndAnimation();
    dragState_ = GridItemDragState::IDLE;
    fromIndex_ = -1;
    scrolling_ = false;
    dragOffset_ = OffsetF();
    realOffset_ = OffsetF();
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
        forEach->FireOnLongPress(GetIndex());
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
    fromIndex_ = currentIndex_;
    forEach->FireOnDragStart(fromIndex_);
}

void GridItemDragManager::HandleOnItemDragUpdate(const GestureEvent& info)
{
    if (dragState_ != GridItemDragState::DRAGGING) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto frameRect = geometry->GetMarginFrameRect();
    OffsetF gestureOffset(info.GetOffsetX(), info.GetOffsetY());
    realOffset_ = gestureOffset + dragOffset_;
    SetPosition(realOffset_);

    int32_t from = GetIndex();
    PointF point(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    HandleAutoScroll(from, point, frameRect);

    auto paddingOffset = GetParentPaddingOffset();
    int32_t to = FindSwapTarget(from, realOffset_ - frameRect.GetOffset() + paddingOffset);
    if (to == from) {
        return;
    }
    HandleSwapAnimation(from, to);
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    forEach->FireOnMoveThrough(fromIndex_, to);
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
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    forEach->FireOnMove(fromIndex_, to);
    forEach->FireOnDrop(to);
    pattern->GetMutableLayoutInfo().ClearOnMoveDragState();
    dragState_ = GridItemDragState::IDLE;
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
    HandleDragEndAnimation();
    if (dragState_ == GridItemDragState::DRAGGING) {
        int32_t to = GetIndex();
        auto forEach = forEachNode_.Upgrade();
        CHECK_NULL_VOID(forEach);
        forEach->FireOnMove(fromIndex_, to);
        forEach->FireOnDrop(to);
    }
    dragState_ = GridItemDragState::IDLE;
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

bool GridItemDragManager::HasIrregularItemInRange(int32_t from, int32_t to) const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, false);
    int32_t checkStart = std::min(from, to);
    int32_t checkEnd = std::max(from, to);
    for (int32_t i = checkStart; i <= checkEnd; ++i) {
        auto node = forEach->GetFrameNode(i);
        if (node) {
            auto itemPattern = node->GetPattern<GridItemPattern>();
            if (itemPattern && itemPattern->GetIrregularItemInfo().has_value()) {
                return true;
            }
        }
    }
    return false;
}

void GridItemDragManager::PrepareIrregularDragState(int32_t from, int32_t to, GridLayoutInfo& info)
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);
    if (!info.isOnMoveDragUpdate_) {
        for (int32_t i = 0; i < forEach->FrameCount(); ++i) {
            info.dragOriginalIndexMap_[i] = i;
        }
        info.isOnMoveDragUpdate_ = true;
    }
    info.UpdateDragOriginalIndex(from, to);
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

    if (HasIrregularItemInRange(from, to)) {
        auto pattern = grid->GetPattern<GridPattern>();
        CHECK_NULL_VOID(pattern);
        auto& info = pattern->GetMutableLayoutInfo();
        PrepareIrregularDragState(from, to, info);
    }

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

int32_t GridItemDragManager::FindSwapTarget(int32_t currentIndex, const OffsetF& delta)
{
    currentIndex_ = currentIndex;
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_RETURN(grid, currentIndex);

    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, currentIndex);

    auto& info = pattern->GetMutableLayoutInfo();

    auto [currentCol, currentRow] = info.GetItemPos(currentIndex);
    if (currentCol < 0 || currentRow < 0) {
        return currentIndex;
    }

    TargetPosition targetPos = CalculateTargetPosition(currentRow, currentCol, delta, info);
    if (!targetPos.isValid) {
        return currentIndex;
    }

    return GetTargetItemAtPosition(currentIndex, targetPos, info, delta);
}

int32_t GridItemDragManager::GetTargetItemAtPosition(int32_t currentIndex,
    const TargetPosition& targetPos, const GridLayoutInfo& info, const OffsetF& delta) const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, currentIndex);
    // Irregular item (spanning multiple cells), use area swap logic
    std::set<int32_t> targetIndices;

    for (int32_t r = targetPos.row; r < targetPos.row + targetPos.rowSpan; ++r) {
        auto rowIt = info.gridMatrix_.find(r);
        if (rowIt == info.gridMatrix_.end()) {
            continue;
        }

        for (int32_t c = targetPos.col; c < targetPos.col + targetPos.colSpan; ++c) {
            auto colIt = rowIt->second.find(c);
            if (colIt == rowIt->second.end()) {
                continue;
            }
            int32_t idx = std::abs(colIt->second);
            if (idx >= info.startIndex_ && idx <= info.endIndex_) {
                targetIndices.insert(idx);
            }
        }
    }

    if (targetIndices.empty()) {
        return currentIndex;
    }

    float mainDelta = delta.GetMainOffset(axis_);
    int32_t targetIndex = Positive(mainDelta) ? *targetIndices.rbegin() : *targetIndices.begin();
    if (ValidateMoveBySimulation(currentIndex, targetIndex, info)) {
        return targetIndex;
    }
    return currentIndex;
}

void GridItemDragManager::ComputeTargetRowCol(TargetPosition& targetPos, int32_t currentRow,
    int32_t currentCol, float mainDelta, float crossDelta, float singleRowHeight,
    float singleColWidth, int32_t crossCount) const
{
    targetPos.row = currentRow;
    if (GreatNotEqual(std::abs(mainDelta), singleRowHeight * MOVE_THRESHOLD) &&
        !NearZero(singleRowHeight)) {
        if (Positive(mainDelta)) {
            targetPos.row = currentRow + 1;
        } else {
            targetPos.row = currentRow - 1;
        }
    }

    targetPos.col = currentCol;
    if (GreatNotEqual(std::abs(crossDelta), singleColWidth * MOVE_THRESHOLD) &&
        !NearZero(singleColWidth)) {
        if (Positive(crossDelta)) {
            targetPos.col = currentCol + 1;
        } else {
            targetPos.col = currentCol - 1;
        }
    }
}

void GridItemDragManager::ClampTargetPosition(
    TargetPosition& targetPos, int32_t crossCount, int32_t rowCount) const
{
    if (targetPos.row < 0) {
        targetPos.row = 0;
    }
    if (targetPos.col < 0) {
        targetPos.col = 0;
    }
    if (targetPos.colSpan > 0 && targetPos.col + targetPos.colSpan > crossCount) {
        targetPos.col = std::max(0, crossCount - targetPos.colSpan);
    }
}

bool GridItemDragManager::CheckTargetCellsExist(const TargetPosition& targetPos,
    int32_t rowCount, const GridLayoutInfo& info) const
{
    int32_t maxRowToCheck = std::min(targetPos.row + targetPos.rowSpan, rowCount);
    for (int32_t r = targetPos.row; r < maxRowToCheck; ++r) {
        auto rowIt = info.gridMatrix_.find(r);
        if (rowIt == info.gridMatrix_.end()) {
            continue;
        }
        for (int32_t c = targetPos.col; c < targetPos.col + targetPos.colSpan; ++c) {
            if (rowIt->second.find(c) != rowIt->second.end()) {
                return true;
            }
        }
    }
    return false;
}

GridItemDragManager::TargetPosition GridItemDragManager::CalculateTargetPosition(
    int32_t currentRow, int32_t currentCol, const OffsetF& delta, const GridLayoutInfo& info) const
{
    TargetPosition targetPos;

    float mainDelta = delta.GetMainOffset(axis_);
    float crossDelta = delta.GetCrossOffset(axis_);
    int32_t crossCount = info.crossCount_;
    int32_t rowCount = info.gridMatrix_.empty() ? 0 : info.gridMatrix_.rbegin()->first + 1;

    float mainItemSize = GetItemMainSize(currentIndex_, info);
    float crossItemSize = GetItemCrossSize(currentIndex_, info);

    ItemSpanInfo currentSpanInfo = GetIrregularItemInfoAndSpan(currentIndex_);
    float singleRowHeight = currentSpanInfo.rowSpan > 0 ? mainItemSize / currentSpanInfo.rowSpan : mainItemSize;
    float singleColWidth = currentSpanInfo.colSpan > 0 ? crossItemSize / currentSpanInfo.colSpan : crossItemSize;

    ComputeTargetRowCol(targetPos, currentRow, currentCol, mainDelta, crossDelta,
        singleRowHeight, singleColWidth, crossCount);
    targetPos.rowSpan = currentSpanInfo.rowSpan;
    targetPos.colSpan = currentSpanInfo.colSpan;
    ClampTargetPosition(targetPos, crossCount, rowCount);

    bool hasCells = CheckTargetCellsExist(targetPos, rowCount, info);
    if (!hasCells && targetPos.row < rowCount) {
        targetPos.isValid = false;
        return targetPos;
    }
    targetPos.isValid = true;
    return targetPos;
}

float GridItemDragManager::GetItemMainSize(int32_t currentIndex, const GridLayoutInfo& info) const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, DEFAULT_ITEM_SIZE);
    
    auto node = forEach->GetFrameNode(currentIndex);
    if (!node) {
        // Item not rendered, try to get the row height of the current item's row
        auto [col, row] = info.GetItemPos(currentIndex);
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
    if (currentInfo.has_value()) {
        spanInfo.rowSpan = currentInfo->mainSpan;
        spanInfo.colSpan = currentInfo->crossSpan;
        spanInfo.isIrregular = true;
    }

    return spanInfo;
}

std::vector<GridItemDragManager::SimSpanInfo> GridItemDragManager::CollectSpanInfo(int32_t totalItems) const
{
    std::vector<SimSpanInfo> spans(totalItems);
    auto forEach = forEachNode_.Upgrade();
    if (!forEach) {
        return spans;
    }
    for (int32_t i = 0; i < totalItems; ++i) {
        auto node = forEach->GetFrameNode(i);
        if (!node) {
            continue;
        }
        auto pattern = node->GetPattern<GridItemPattern>();
        if (!pattern) {
            continue;
        }
        auto irregularInfo = pattern->GetIrregularItemInfo();
        if (!irregularInfo.has_value()) {
            continue;
        }
        spans[i].rowSpan = irregularInfo->mainSpan;
        spans[i].colSpan = irregularInfo->crossSpan;
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

std::pair<int32_t, int32_t> GridItemDragManager::PlaceItemInMatrix(
    SimMatrix& matrix, int32_t itemIdx, const SimSpanInfo& span,
    int32_t crossCount, int32_t totalItems) const
{
    if (span.colSpan > crossCount) {
        return { -1, -1 };
    }
    for (int32_t row = 0; row <= totalItems; ++row) {
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

bool GridItemDragManager::CopyLayoutToMatrix(SimMatrix& matrix,
    const std::vector<SimSpanInfo>& spans, const GridLayoutInfo& info, int32_t count) const
{
    int32_t minItemId = count;
    for (const auto& [rowIdx, cols] : info.gridMatrix_) {
        for (const auto& [colIdx, idx] : cols) {
            if (idx >= 0 && idx < minItemId) {
                minItemId = idx;
            }
        }
    }
    for (int32_t i = minItemId; i < count; ++i) {
        auto [col, row] = info.GetItemPos(i);
        if (row < 0 || col < 0) {
            continue;
        }
        auto origIt = info.gridMatrix_.find(row);
        if (origIt == info.gridMatrix_.end()) {
            continue;
        }
        if (origIt->second.find(col) == origIt->second.end()) {
            continue;
        }
        for (int32_t r = 0; r < spans[i].rowSpan; ++r) {
            for (int32_t c = 0; c < spans[i].colSpan; ++c) {
                matrix[row + r][col + c] = -i;
            }
        }
        matrix[row][col] = i;
    }
    return true;
}

bool GridItemDragManager::SimulateLayout(SimMatrix& matrix, const std::vector<int32_t>& order,
    const std::vector<SimSpanInfo>& spans, const GridLayoutInfo& info,
    int32_t startRebuild, int32_t totalItems, int32_t from, int32_t to) const
{
    for (int32_t i = startRebuild; i < totalItems; ++i) {
        auto [newRow, newCol] = PlaceItemInMatrix(matrix, order[i], spans[order[i]],
            info.crossCount_, totalItems);
        if (newRow < 0) {
            return false;
        }
        auto [origCol, origRow] = info.GetItemPos(order[i]);
        if (origRow == newRow && origCol == newCol && i > std::max(from, to)) {
            break;
        }
    }
    return true;
}

bool GridItemDragManager::ValidateMoveBySimulation(
    int32_t from, int32_t to, const GridLayoutInfo& info) const
{
    if (from == to) {
        return true;
    }

    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, false);

    int32_t totalItems = totalCount_;
    if (from < 0 || from >= totalItems || to < 0 || to >= totalItems) {
        return false;
    }

    int32_t crossCount = info.crossCount_;
    if (crossCount <= 0) {
        return false;
    }

    auto spans = CollectSpanInfo(totalItems);

    std::vector<int32_t> order(totalItems);
    std::iota(order.begin(), order.end(), 0);
    ApplyMoveToArray(order, from, to);
    if (order[from] < info.startIndex_ || order[from] > info.endIndex_) {
        return false;
    }

    SimMatrix simMatrix;
    int32_t startRebuild = std::min(from, to);
    if (!CopyLayoutToMatrix(simMatrix, spans, info, startRebuild)) {
        return false;
    }
    return SimulateLayout(simMatrix, order, spans, info, startRebuild, totalItems, from, to);
}

bool GridItemDragManager::IsInHotZone(int32_t index, const RectF& frameRect) const
{
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_RETURN(grid, false);

    auto gridGeometry = grid->GetGeometryNode();
    CHECK_NULL_RETURN(gridGeometry, false);

    auto gridSize = gridGeometry->GetFrameSize();

    float hotZone = Dimension(HOT_ZONE_SIZE_VP, DimensionUnit::VP).ConvertToPx();

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
        pattern->HandleMoveEventInComp(point, true);

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

void GridItemDragManager::HandleScrollCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    auto frameRect = geometry->GetMarginFrameRect();
    int32_t from = GetIndex();
    if (scrolling_ && !IsInHotZone(from, frameRect)) {
        auto grid = gridNode_.Upgrade();
        CHECK_NULL_VOID(grid);
        auto pattern = grid->GetPattern<GridPattern>();
        CHECK_NULL_VOID(pattern);

        pattern->HandleLeaveHotzoneEvent();
        pattern->SetHotZoneScrollCallback(nullptr);
        scrolling_ = false;
    }

    auto paddingOffset = GetParentPaddingOffset();
    int32_t to = FindSwapTarget(from, realOffset_ - frameRect.GetOffset() + paddingOffset);
    if (to == from) {
        return;
    }

    HandleSwapAnimation(from, to);

    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_VOID(forEach);

    forEach->FireOnMoveThrough(fromIndex_, to);
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

bool GridItemDragManager::GetDummyItemRect(int32_t index, RectF& rect) const
{
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_RETURN(grid, false);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto& info = pattern->GetMutableLayoutInfo();

    auto [col, row] = info.GetItemPos(index);
    if (col < 0 || row < 0) {
        return false;
    }

    auto rowIt = info.lineHeightMap_.find(row);
    if (rowIt == info.lineHeightMap_.end()) {
        return false;
    }

    float height = rowIt->second;
    float width = 0.0f;
    for (auto& [r, cMap] : info.gridMatrix_) {
        if (r != row) {
            continue;
        }
        for (auto& [c, idx] : cMap) {
            if (c != col) {
                continue;
            }
            auto forEach = forEachNode_.Upgrade();
            CHECK_NULL_RETURN(forEach, false);
            auto node = forEach->GetFrameNode(idx);
            if (!node) {
                continue;
            }
            auto geometry = node->GetGeometryNode();
            if (geometry) {
                width = geometry->GetFrameSize().Width();
                break;
            }
        }
    }

    rect = RectF(OffsetF(0.0f, 0.0f), SizeF(width, height));
    return true;
}

} // namespace OHOS::Ace::NG
