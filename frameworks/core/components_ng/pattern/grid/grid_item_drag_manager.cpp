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
#include "core/components_ng/pattern/grid/grid_item_drag_manager.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
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
#include <limits>
#include <set>
#include <algorithm>
#include <optional>

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_SCALE = 1.05f;
constexpr int32_t DEFAULT_Z_INDEX = 100;
constexpr float HOT_ZONE_SIZE_VP = 59.0f;
constexpr float DEFAULT_ITEM_SIZE = 100.0f;
constexpr int32_t LONG_PRESS_ANIMATION_DURATION = 300;
constexpr int32_t SWAP_ANIMATION_DURATION = 30;
constexpr int32_t POWER_FOR_DISTANCE = 2;

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
    forEachStartIndex_ = GetForEachIndexInGrid(forEach);
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
        pattern->GetMutableLayoutInfo().ClearOnMoveDragState();
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

    float mainDelta = delta.GetMainOffset(axis_);
    float crossDelta = delta.GetCrossOffset(axis_);

    ItemSpanInfo currentSpanInfo = GetIrregularItemInfoAndSpan(currentIndex);
    float mainItemSize = GetItemMainSize(currentIndex, info);
    float crossItemSize = GetItemCrossSize(currentIndex, info);
    float singleRowHeight = currentSpanInfo.rowSpan > 0 ? mainItemSize / currentSpanInfo.rowSpan : mainItemSize;
    float singleColWidth = currentSpanInfo.colSpan > 0 ? crossItemSize / currentSpanInfo.colSpan : crossItemSize;
    int32_t rowMove = static_cast<int32_t>(std::round(mainDelta / singleRowHeight));
    int32_t colMove = static_cast<int32_t>(std::round(crossDelta / singleColWidth));
    if (rowMove == 0 && colMove == 0) {
        candidates.push_back(currentIndex);
        return candidates;
    }

    int32_t startRow = std::min(currentRow, currentRow + rowMove);
    int32_t endRow = std::max(currentRow, currentRow + rowMove);
    int32_t startCol = std::min(std::max(0, currentCol - currentSpanInfo.colSpan), currentCol + colMove);
    int32_t maxCol = std::min(info.crossCount_ - 1, currentCol + currentSpanInfo.colSpan);
    int32_t endCol = std::max(maxCol, currentCol + colMove);
    std::set<int32_t> candidateSet;
    for (int32_t r = startRow; r <= endRow; ++r) {
        auto rowIt = info.gridMatrix_.find(r);
        if (rowIt == info.gridMatrix_.end()) {
            continue;
        }

        for (int32_t c = startCol; c <= endCol; ++c) {
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
    int32_t startRebuild, int32_t endRebuild, int32_t from, int32_t to) const
{
    for (int32_t i = startRebuild; i <= endRebuild; ++i) {
        int32_t orderIdx = i - info.startIndex_;
        if (orderIdx < 0 || orderIdx >= static_cast<int32_t>(order.size())) {
            break;
        }
        auto [newRow, newCol] = PlaceItemInMatrix(info, matrix, order[orderIdx],
            spans[order[orderIdx]], info.crossCount_);
        if (newRow < 0) {
            return false;
        }
        auto [origCol, origRow] = info.GetItemPos(order[orderIdx]);
        if (origRow == newRow && origCol == newCol && i > std::max(from, to)) {
            break;
        }
    }
    return true;
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

float GridItemDragManager::CalculateCrossPosition(int32_t col, int32_t colSpan,
    const RefPtr<FrameNode>& node, float crossGap, const GridLayoutInfo& info) const
{
    float colWidth = 0.0f;
    if (colSpan > 0 && info.crossCount_ > 0) {
        auto geometry = node->GetGeometryNode();
        if (geometry) {
            colWidth = geometry->GetFrameSize().CrossSize(axis_) / colSpan;
        }
    }
    return col * (colWidth + crossGap);
}

std::optional<OffsetF> GridItemDragManager::CreatePositionFromCoords(float mainPos, float crossPos) const
{
    if (axis_ == Axis::VERTICAL) {
        return OffsetF(crossPos, mainPos);
    } else {
        return OffsetF(mainPos, crossPos);
    }
}

std::optional<OffsetF> GridItemDragManager::SearchRowForTarget(const std::map<int32_t, int32_t>& cols,
    int32_t targetIdx, int32_t row, const RefPtr<FrameNode>& node, int32_t colSpan,
    float mainGap, float crossGap, const GridLayoutInfo& info) const
{
    for (const auto& [col, idx] : cols) {
        if (idx == targetIdx) {
            float mainPos = CalculateMainPosition(row, mainGap, info);
            float crossPos = CalculateCrossPosition(col, colSpan, node, crossGap, info);
            return CreatePositionFromCoords(mainPos, crossPos);
        }
    }
    return std::nullopt;
}

std::optional<OffsetF> GridItemDragManager::FindItemPositionInMatrix(const SimMatrix& simMatrix,
    int32_t targetIdx, const RefPtr<FrameNode>& node, int32_t colSpan, float mainGap,
    float crossGap, const GridLayoutInfo& info) const
{
    for (const auto& [row, cols] : simMatrix) {
        auto result = SearchRowForTarget(cols, targetIdx, row, node, colSpan, mainGap, crossGap, info);
        if (result.has_value()) {
            return result;
        }
    }
    return std::nullopt;
}

std::optional<OffsetF> GridItemDragManager::CalculateFromNewPosition(int32_t from, int32_t to,
    const GridLayoutInfo& info) const
{
    auto forEach = forEachNode_.Upgrade();
    CHECK_NULL_RETURN(forEach, std::nullopt);
    // drag item not in screen
    if (forEachStartIndex_ + from < info.startIndex_ || forEachStartIndex_ + from > info.endIndex_
        || forEachStartIndex_ + to < info.startIndex_ || forEachStartIndex_ + to > info.endIndex_) {
        return std::nullopt;
    }

    auto spans = CollectSpanInfo(info);

    int32_t startRebuild = std::max(forEachStartIndex_ + std::min(from, to), info.startIndex_);
    int32_t endRebuild = std::min(forEachStartIndex_ + std::max(from, to), info.endIndex_);

    SimMatrix simMatrix;
    if (!CopyLayoutToMatrix(simMatrix, spans, info, startRebuild)) {
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
    if (!SimulateLayoutInRange(simMatrix, order, spans, info, startRebuild, endRebuild, simFrom, simTo)) {
        return std::nullopt;
    }

    auto fromNode = forEach->GetFrameNode(from);
    CHECK_NULL_RETURN(fromNode, std::nullopt);

    auto fromPattern = fromNode->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(fromPattern, std::nullopt);

    auto irregularInfo = fromPattern->GetIrregularItemInfo();
    int32_t fromColSpan = irregularInfo.has_value() ? irregularInfo->crossSpan : 1;

    float mainGap = 0.0f;
    float crossGap = 0.0f;
    CalculateGaps(mainGap, crossGap, info);

    int32_t targetIdx = forEachStartIndex_ + from;
    return FindItemPositionInMatrix(simMatrix, targetIdx, fromNode, fromColSpan, mainGap, crossGap, info);
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

int32_t GridItemDragManager::FindSwapTarget(int32_t currentIndex, const OffsetF& delta)
{
    currentIndex_ = currentIndex;
    auto grid = gridNode_.Upgrade();
    CHECK_NULL_RETURN(grid, currentIndex);

    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, currentIndex);

    auto& info = pattern->GetMutableLayoutInfo();

    auto [currentCol, currentRow] = info.GetItemPos(forEachStartIndex_ + currentIndex);
    if (currentCol < 0 || currentRow < 0) {
        return currentIndex;
    }

    auto candidates = CollectSwapCandidates(currentIndex, delta, info);
    if (candidates.empty()) {
        return currentIndex;
    }

    OffsetF dragPosition = realOffset_;
    int32_t bestCandidate = currentIndex;
    float minDistance = std::numeric_limits<float>::max();
    float mainDelta = delta.GetMainOffset(axis_);
    bool movingDown = Positive(mainDelta);

    for (int32_t candidate : candidates) {
        auto newPositionOpt = CalculateFromNewPosition(currentIndex, candidate, info);
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
    // collect ForEach items
    for (int32_t forEachIdx = 0; forEachIdx < totalCount_; ++forEachIdx) {
        int32_t gridIndex = forEachStartIndex_ + forEachIdx;
        if (gridIndex < info.startIndex_) {
            continue;
        }
        if (gridIndex > info.endIndex_) {
            break;
        }
        auto node = forEach->GetFrameNode(forEachIdx);
        if (!node) {
            continue;
        }
        auto pattern = node->GetPattern<GridItemPattern>();
        if (!pattern) {
            spans[gridIndex].rowSpan = 1;
            spans[gridIndex].colSpan = 1;
            continue;
        }
        auto irregularInfo = pattern->GetIrregularItemInfo();
        if (!irregularInfo.has_value()) {
            spans[gridIndex].rowSpan = 1;
            spans[gridIndex].colSpan = 1;
            continue;
        }
        spans[gridIndex].rowSpan = irregularInfo->mainSpan;
        if (crossCount > 1) {
            spans[gridIndex].colSpan = irregularInfo->crossSpan;
        } else {
            spans[gridIndex].colSpan = 1;
        }
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
    const GridLayoutInfo& info, SimMatrix& matrix, int32_t itemIdx,
    const SimSpanInfo& span, int32_t crossCount) const
{
    if (span.colSpan > crossCount) {
        return { -1, -1 };
    }
    int32_t startRow = 0;
    if (!matrix.empty()) {
        startRow = matrix.rbegin()->first;
    } else if (!info.gridMatrix_.empty()) {
        startRow = info.gridMatrix_.begin()->first;
    }
    int32_t endRow = info.gridMatrix_.empty() ? startRow + 1 : info.gridMatrix_.rbegin()->first + 1;
    for (int32_t row = startRow; row <= endRow; ++row) {
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
    std::vector<SimSpanInfo>& spans, const GridLayoutInfo& info, int32_t count) const
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

        if (i < forEachNotIncludeIndex) {
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
} // namespace OHOS::Ace::NG
