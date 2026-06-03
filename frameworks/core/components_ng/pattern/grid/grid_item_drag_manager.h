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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_DRAG_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_DRAG_MANAGER_H

#include "base/memory/ace_type.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/vector.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/syntax/for_each_base_node.h"

namespace OHOS::Ace {
class GestureEvent;
}

namespace OHOS::Ace::NG {

class GeometryNode;
class GridLayoutProperty;
class RenderContext;
class GridPattern;

/**
 * @brief Represents the current state of a grid item drag operation.
 */
enum class GridItemDragState {
    IDLE,
    LONG_PRESS,
    DRAGGING,
};

/**
 * @brief Manages drag-and-drop reordering of GridItem within a Grid component.
 *
 * GridItemDragManager is created per draggable GridItem and handles the complete
 * drag lifecycle:
 *
 * 1. **Long-press initiation**: Detects long-press on a GridItem, plays a scale-up
 *    animation and fires the onLongPress callback.
 *
 * 2. **Position tracking**: Follows the drag gesture to update the item's position
 *    in real time via RenderContext.
 *
 * 3. **Swap target finding**: During drag, simulates layout to determine where the
 *    dragged item would land if swapped with each candidate, then selects the best
 *    match using center-point distance comparison.
 *
 * 4. **Swap animation**: When a better swap target is found, animates the data swap
 *    between the dragged item and the target, repositioning surrounding items.
 *
 * 5. **Nearby item scaling**: Applies a subtle scale-down effect to items adjacent
 *    to the dragged item (main axis, cross axis, and diagonal neighbors).
 *
 * 6. **Auto-scroll**: When the drag point approaches grid edges, triggers auto-scroll
 *    to allow dragging items beyond the visible viewport.
 *
 * 7. **Drag end/cancel**: Plays recovery animations (scale, shadow, z-index) and
 *    fires onMove/onDrop callbacks to finalize or cancel the reordering.
 *
 * The manager supports both regular and irregular (multi-row/column span) items,
 * and works with vertical and horizontal grid layouts.
 */
class ACE_EXPORT GridItemDragManager : public AceType {
    DECLARE_ACE_TYPE(GridItemDragManager, AceType);

public:
    /**
     * @brief Constructs a GridItemDragManager for the given host item.
     * @param host The FrameNode of the GridItem being dragged.
     * @param forEach The ForEachBaseNode that contains the draggable items.
     */
    GridItemDragManager(RefPtr<FrameNode> host, RefPtr<ForEachBaseNode> forEach)
        : frameNode_(host), forEachNode_(forEach)
    {
        gridNode_ = GetGridFrameNode();
    }
    ~GridItemDragManager() override;

    /**
     * @brief Gets the host FrameNode (the dragged GridItem).
     * @return The host FrameNode, or nullptr if it has been released.
     */
    RefPtr<FrameNode> GetHost() const
    {
        return frameNode_.Upgrade();
    }

    /**
     * @brief Initializes drag gesture events on the host GridItem.
     * Registers long-press, drag start, update, end, and cancel handlers.
     */
    void InitDragDropEvent();

    /**
     * @brief Removes drag gesture events from the host GridItem.
     */
    void DeInitDragDropEvent();

    /**
     * @brief Resets drag state and fires onMove/onDrop callbacks.
     * Called when the drag operation is interrupted or the manager is destroyed.
     */
    void Reset();

private:
    /**
     * @brief Handles the long-press gesture on the GridItem.
     * Plays a scale-up animation and fires the onLongPress callback.
     * @param info The gesture event information.
     */
    void HandleOnItemLongPress(const GestureEvent& info);

    /**
     * @brief Handles the start of a drag gesture.
     * Records the initial drag offset, axis direction, and item index.
     * @param info The gesture event information.
     */
    void HandleOnItemDragStart(const GestureEvent& info);

    /**
     * @brief Handles drag position updates during the drag gesture.
     * Updates the item position, triggers auto-scroll, nearby scaling, and swap logic.
     * @param info The gesture event information.
     */
    void HandleOnItemDragUpdate(const GestureEvent& info);

    /**
     * @brief Handles the end of a drag gesture.
     * Plays the drag-end animation and fires onMove/onDrop callbacks.
     * @param info The gesture event information.
     */
    void HandleOnItemDragEnd(const GestureEvent& info);

    /**
     * @brief Handles drag cancellation.
     * Resets animations and fires onMove/onDrop at the current position.
     */
    void HandleOnItemDragCancel();

    /**
     * @brief Animates z-index and position back to the original state on drag end.
     */
    void HandleZIndexAndPosition();

    /**
     * @brief Animates the back shadow back to its original value on drag end.
     */
    void HandleBackShadow();

    /**
     * @brief Animates the transform scale back to its original value on drag end.
     */
    void HandleTransformScale();

    /**
     * @brief Runs all drag-end animations in sequence (z-index, shadow, scale).
     */
    void HandleDragEndAnimation();

    /**
     * @brief Animates the data swap between two items and triggers layout.
     * @param from The source item index.
     * @param to The target item index.
     */
    void HandleSwapAnimation(int32_t from, int32_t to);

    /**
     * @brief Prepares drag state for irregular (multi-span) items.
     * Initializes the dragOriginalIndexMap if this is the first drag update.
     * @param from The source item index.
     * @param to The target item index.
     * @param info The mutable GridLayoutInfo reference.
     */
    void PrepareIrregularDragState(int32_t from, int32_t to, GridLayoutInfo& info);

    /**
     * @brief Simulated span info used for layout simulation during drag.
     */
    struct SimSpanInfo {
        int32_t rowSpan = 1;
        int32_t colSpan = 1;
    };
    /**
     * @brief Simulated grid matrix type: [row, [col, itemIndex]].
     */
    using SimMatrix = std::map<int32_t, std::map<int32_t, int32_t>>;

    /**
     * @brief Calculates main and cross axis gaps for the grid.
     * @param[out] mainGap The computed main axis gap.
     * @param[out] crossGap The computed cross axis gap.
     * @param info The current GridLayoutInfo.
     */
    void CalculateGaps(float& mainGap, float& crossGap, const GridLayoutInfo& info) const;

    /**
     * @brief Checks whether a given row is visible within the grid viewport.
     * @param row The row index to check.
     * @param mainGap The main axis gap between rows.
     * @param mainSize The main axis size of the grid viewport.
     * @param info The current GridLayoutInfo.
     * @return True if the row is within the visible viewport.
     */
    bool IsRowInViewport(int32_t row, float mainGap, float mainSize, const GridLayoutInfo& info) const;

    /**
     * @brief Calculates the main axis position for a given target row.
     * @param targetRow The target row index.
     * @param mainGap The main axis gap.
     * @param info The current GridLayoutInfo.
     * @return The main axis position in pixels.
     */
    float CalculateMainPosition(int32_t targetRow, float mainGap, const GridLayoutInfo& info) const;

    /**
     * @brief Searches a single row's column map for a target item and computes its position.
     * @param cols The column map for the row.
     * @param targetIdx The target item index to find.
     * @param row The row index.
     * @param node The FrameNode of the item (for size and alignment).
     * @param colSpan The column span of the item.
     * @param mainGap The main axis gap.
     * @param crossLens The cross axis column widths.
     * @param adjustedCrossGap The adjusted cross axis gap.
     * @param info The current GridLayoutInfo.
     * @return The computed position offset, or std::nullopt if not found or out of viewport.
     */
    std::optional<OffsetF> SearchRowForTarget(const std::map<int32_t, int32_t>& cols, int32_t targetIdx,
        int32_t row, const RefPtr<FrameNode>& node, int32_t colSpan, float mainGap,
        const std::vector<double>& crossLens, float adjustedCrossGap, const GridLayoutInfo& info) const;

    /**
     * @brief Finds the position of an item in a simulated grid matrix.
     * @param simMatrix The simulated grid matrix.
     * @param targetIdx The target item index.
     * @param node The FrameNode of the item.
     * @param colSpan The column span of the item.
     * @param mainGap The main axis gap.
     * @param crossLens The cross axis column widths.
     * @param adjustedCrossGap The adjusted cross axis gap.
     * @param info The current GridLayoutInfo.
     * @return The computed position offset, or std::nullopt if not found.
     */
    std::optional<OffsetF> FindItemPositionInMatrix(const SimMatrix& simMatrix, int32_t targetIdx,
        const RefPtr<FrameNode>& node, int32_t colSpan, float mainGap,
        const std::vector<double>& crossLens, float adjustedCrossGap, const GridLayoutInfo& info) const;

    /**
     * @brief Calculates where the dragged item would be placed after swapping from->to.
     * Simulates the layout with the swap applied and returns the item's new position.
     * @param from The source item index (dragged item).
     * @param to The target item index (swap candidate).
     * @param info The current GridLayoutInfo.
     * @param[in,out] spans The span info for all items (may be extended).
     * @param mainGap The main axis gap.
     * @param crossLens The cross axis column widths.
     * @param adjustedCrossGap The adjusted cross axis gap.
     * @return The computed position of the dragged item after swap, or std::nullopt on failure.
     */
    std::optional<OffsetF> CalculateFromNewPosition(int32_t from, int32_t to, const GridLayoutInfo& info,
        std::vector<SimSpanInfo>& spans, float mainGap,
        const std::vector<double>& crossLens, float adjustedCrossGap) const;

    /**
     * @brief Calculates the Euclidean distance between two offset points.
     * @param pos1 The first point.
     * @param pos2 The second point.
     * @return The distance value.
     */
    float CalculateDistance(const OffsetF& pos1, const OffsetF& pos2) const;

    /**
     * @brief Gets the margin  swap candidate when distances are equal.
     * Uses drag direction to break ties in favor of items in the direction of movement.
     * @param currentIndex The index of the currently dragged item.
     * @param movingDown Whether the drag direction is forward (positive main axis delta).
     * @param currentBest The current best candidate index.
     * @param candidate The new candidate to compare.
     * @param candidateDistance The distance of the new candidate.
     * @param bestDistance The current best distance.
     * @return The selected best candidate index.
     */
    int32_t SelectBestCandidate(int32_t currentIndex, bool movingDown,
        int32_t currentBest, int32_t candidate, float candidateDistance, float bestDistance) const;

    /**
     * @brief Finds the best swap target for the currently dragged item.
     * Collects candidates, finds the best one, and returns its index.
     * @param currentIndex The ForEach-local index of the dragged item.
     * @param delta The offset delta from the item's original position.
     * @return The ForEach-local index of the best swap target.
     */
    int32_t FindSwapTarget(int32_t currentIndex, const OffsetF& delta);

    /**
     * @brief Gets the main axis size of the item at the given index.
     * Falls back to row height if the item node is not rendered, or DEFAULT_ITEM_SIZE.
     * @param currentIndex The ForEach-local index of the item.
     * @param info The current GridLayoutInfo.
     * @return The main axis size in pixels.
     */
    float GetItemMainSize(int32_t currentIndex, const GridLayoutInfo& info) const;

    /**
     * @brief Gets the cross axis size of the item at the given index.
     * Falls back to DEFAULT_ITEM_SIZE if the item node is not rendered.
     * @param currentIndex The ForEach-local index of the item.
     * @param info The current GridLayoutInfo.
     * @return The cross axis size in pixels.
     */
    float GetItemCrossSize(int32_t currentIndex, const GridLayoutInfo& info) const;

    /**
     * @brief Collects span info (rowSpan, colSpan) for all ForEach items in viewport.
     * @param info The current GridLayoutInfo.
     * @return A vector of SimSpanInfo indexed by global item index.
     */
    std::vector<SimSpanInfo> CollectSpanInfo(const GridLayoutInfo& info) const;

    /**
     * @brief Moves an element in an array from one position to another.
     * @param[in,out] order The array to modify.
     * @param from The source position.
     * @param to The destination position.
     */
    static void ApplyMoveToArray(std::vector<int32_t>& order, int32_t from, int32_t to);

    /**
     * @brief Finds the first available column in a row that can fit the given column span.
     * @param matrix The simulated grid matrix.
     * @param row The row to search.
     * @param colSpan The required column span.
     * @param crossCount The total number of columns.
     * @return The starting column index, or -1 if no space is available.
     */
    int32_t FindAvailableColumn(const SimMatrix& matrix, int32_t row,
        int32_t colSpan, int32_t crossCount) const;

    /**
     * @brief Inserts an item into the grid matrix.
     * @param[in,out] matrix The simulated grid matrix to place into.
     * @param itemIdx The global item index to place.
     * @param span The span info for the item.
     * @param crossCount The total number of columns.
     * @param viewportEndRow The last row allowed for placement.
     * @return A pair of (row, col) on success, or (-1, -1) on failure.
     */
    std::pair<int32_t, int32_t> PlaceItemInMatrix(const GridLayoutInfo& info, SimMatrix& matrix,
        int32_t itemIdx, const SimSpanInfo& span, int32_t crossCount, int32_t viewportEndRow) const;

    /**
     * @brief Copies the current grid layout into a simulated matrix.
     * Also fills in span info for items not covered by CollectSpanInfo.
     * @param[out] matrix The simulated matrix to fill.
     * @param[in,out] spans The span info vector (may be extended for off-screen items).
     * @param info The current GridLayoutInfo.
     * @param count The upper bound global item index to copy.
     * @param mainGap The main axis gap.
     * @param mainSize The main axis viewport size.
     * @return True on success.
     */
    bool CopyLayoutToMatrix(SimMatrix& matrix, std::vector<SimSpanInfo>& spans,
        const GridLayoutInfo& info, int32_t count, float mainGap, float mainSize) const;

    /**
     * @brief Calculates the column span of an item by scanning rightward from a starting column.
     * @param rowCols The column map for the row.
     * @param col The starting column.
     * @param itemIdx The item index to match.
     * @param crossCount The total number of columns.
     * @return The column span count.
     */
    int32_t CalculateColSpan(const std::map<int32_t, int32_t>& rowCols,
        int32_t col, int32_t itemIdx, int32_t crossCount) const;

    /**
     * @brief Calculates the row span of an item by scanning downward from a starting row.
     * @param info The current GridLayoutInfo.
     * @param row The starting row.
     * @param col The column to check.
     * @param itemIdx The item index to match.
     * @return The row span count.
     */
    int32_t CalculateRowSpan(const GridLayoutInfo& info,
        int32_t row, int32_t col, int32_t itemIdx) const;

    /**
     * @brief Computes and fills span info for a single item from the real grid matrix.
     * @param info The current GridLayoutInfo.
     * @param itemIdx The global item index.
     * @param row The row position.
     * @param col The column position.
     * @param[out] spans The span info vector to fill.
     */
    void CalculateSpanInfo(const GridLayoutInfo& info, int32_t itemIdx,
        int32_t row, int32_t col, std::vector<SimSpanInfo>& spans) const;

    /**
     * @brief Fills the simulated matrix cells for an item based on its span info.
     * @param[out] matrix The simulated matrix.
     * @param itemIdx The global item index.
     * @param row The starting row.
     * @param col The starting column.
     * @param spans The span info vector.
     */
    void FillMatrixWithItem(SimMatrix& matrix, int32_t itemIdx,
        int32_t row, int32_t col, const std::vector<SimSpanInfo>& spans) const;

    /**
     * @brief Collects candidate item indices for swapping based on drag movement.
     * Computes a movement bounding box and collects items within that range.
     * @param currentIndex The ForEach-local index of the dragged item.
     * @param delta The offset delta from the item's original position.
     * @param info The current GridLayoutInfo.
     * @return A vector of ForEach-local candidate indices.
     */
    std::vector<int32_t> CollectSwapCandidates(int32_t currentIndex, const OffsetF& delta,
        const GridLayoutInfo& info) const;

    /**
     * @brief Simulates layout for items in a range after applying a swap.
     * @param[in,out] matrix The simulated matrix to update.
     * @param order The reordered item index array.
     * @param spans The span info vector.
     * @param info The current GridLayoutInfo.
     * @param startRebuild The starting global index to rebuild.
     * @param endRebuild The ending global index to rebuild.
     * @param from The source global index of the swap.
     * @param to The target global index of the swap.
     * @param mainGap The main axis gap.
     * @param mainSize The main axis viewport size.
     * @return True if simulation succeeded, false if an item could not be placed.
     */
    bool SimulateLayoutInRange(SimMatrix& matrix, const std::vector<int32_t>& order,
        const std::vector<SimSpanInfo>& spans, const GridLayoutInfo& info,
        int32_t startRebuild, int32_t endRebuild, int32_t from, int32_t to,
        float mainGap, float mainSize) const;

    /**
     * @brief Span info for an item, including whether it is irregular.
     */
    struct ItemSpanInfo {
        int32_t rowSpan = 1;
        int32_t colSpan = 1;
        bool isIrregular = false;
    };

    /**
     * @brief Adjusts column span for irregular items when crossCount is 1.
     * @param crossSpan The original cross span.
     * @return The adjusted column span (1 if crossCount <= 1, otherwise the original value).
     */
    int32_t GetColSpanForIrregularItem(int32_t crossSpan) const;

    /**
     * @brief Gets the row and column span info for the item at the given index.
     * @param index The ForEach-local index of the item.
     * @return The ItemSpanInfo for the item.
     */
    ItemSpanInfo GetIrregularItemInfoAndSpan(int32_t index) const;

    /**
     * @brief Handles auto-scroll when the drag position is near grid edges.
     * @param index The ForEach-local index of the dragged item.
     * @param point The global touch point.
     * @param frameRect The margin frame rect of the dragged item.
     */
    void HandleAutoScroll(int32_t index, const PointF& point, const RectF& frameRect);

    /**
     * @brief Callback invoked during auto-scroll to update drag state.
     * Re-evaluates nearby scaling and swap targets as the grid scrolls.
     */
    void HandleScrollCallback();

    /**
     * @brief Checks whether the dragged item is within the auto-scroll hot zone.
     * @param index The ForEach-local index of the dragged item.
     * @param frameRect The margin frame rect of the dragged item.
     * @return True if the item is in the hot zone.
     */
    bool IsInHotZone(int32_t index, const RectF& frameRect) const;

    /**
     * @brief Sets the position of the dragged item via render context.
     * @param offset The new position offset in pixels.
     */
    void SetPosition(const OffsetF& offset);

    /**
     * @brief Gets the ForEach-local index of the host GridItem.
     * @return The index, or -1 if not found.
     */
    int32_t GetIndex() const;

    /**
     * @brief Gets the parent Grid FrameNode.
     * @return The Grid FrameNode, or nullptr if the parent is not a Grid.
     */
    RefPtr<FrameNode> GetGridFrameNode() const;

    /**
     * @brief Gets the padding offset of the parent Grid.
     * @return The (left, top) padding offset.
     */
    OffsetF GetParentPaddingOffset() const;

    /**
     * @brief Applies a multiplicative scale to a node's transform, saving the previous scale.
     * @param node The FrameNode to scale.
     * @param scale The scale factor to apply.
     */
    void SetNearbyNodeScale(RefPtr<FrameNode> node, float scale);

    /**
     * @brief Resets all previously scaled nodes back to their original scales.
     * Swaps the prev/curr tracking maps for the next frame.
     */
    void ResetPrevScaleNode();

    /**
     * @brief Scales a neighbor item along the main axis based on drag delta proximity.
     * @param currentIndex The ForEach-local index of the dragged item.
     * @param currentRow The current row of the dragged item.
     * @param currentCol The current column of the dragged item.
     * @param mainRowStep The row step direction (+rowSpan or -1).
     * @param colSpan The column span of the dragged item, iterates columns in range.
     * @param rect The margin frame rect of the dragged item.
     * @param mainDelta The main axis component of the drag delta.
     * @param startIdx The first valid item index in viewport.
     * @param endIdx The last valid item index in viewport.
     * @param info The current GridLayoutInfo.
     * @param forEach The ForEachBaseNode containing items.
     * @return True if a neighbor was found and scaled.
     */
    bool ScaleMainAxisNeighbor(int32_t currentIndex, int32_t currentRow, int32_t currentCol,
        int32_t mainRowStep, int32_t colSpan, const RectF& rect, float mainDelta,
        int32_t startIdx, int32_t endIdx, const GridLayoutInfo& info,
        const RefPtr<ForEachBaseNode>& forEach);

    /**
     * @brief Scales a neighbor item along the cross axis based on drag delta proximity.
     * @param currentIndex The ForEach-local index of the dragged item.
     * @param currentRow The current row of the dragged item.
     * @param currentCol The current column of the dragged item.
     * @param crossColStep The column step direction (+colSpan or -1).
     * @param rowSpan The row span of the dragged item, iterates rows in range.
     * @param rect The margin frame rect of the dragged item.
     * @param crossDelta The cross axis component of the drag delta.
     * @param startIdx The first valid item index in viewport.
     * @param endIdx The last valid item index in viewport.
     * @param info The current GridLayoutInfo.
     * @param forEach The ForEachBaseNode containing items.
     * @return True if a neighbor was found and scaled.
     */
    bool ScaleCrossAxisNeighbor(int32_t currentIndex, int32_t currentRow, int32_t currentCol,
        int32_t crossColStep, int32_t rowSpan, const RectF& rect, float crossDelta,
        int32_t startIdx, int32_t endIdx, const GridLayoutInfo& info,
        const RefPtr<ForEachBaseNode>& forEach);

    /**
     * @brief Scales a diagonal neighbor item based on distance change during drag.
     * Only called when both main and cross axis neighbors were scaled.
     * @param currentIndex The ForEach-local index of the dragged item.
     * @param currentRow The current row of the dragged item.
     * @param currentCol The current column of the dragged item.
     * @param mainRowStep The row step direction.
     * @param crossColStep The column step direction.
     * @param rect The margin frame rect of the dragged item.
     * @param delta The full drag delta offset.
     * @param startIdx The first valid item index in viewport.
     * @param endIdx The last valid item index in viewport.
     * @param info The current GridLayoutInfo.
     * @param forEach The ForEachBaseNode containing items.
     */
    void ScaleDiagonalNeighbor(int32_t currentIndex, int32_t currentRow, int32_t currentCol,
        int32_t mainRowStep, int32_t crossColStep, const RectF& rect, const OffsetF& delta,
        int32_t startIdx, int32_t endIdx, const GridLayoutInfo& info,
        const RefPtr<ForEachBaseNode>& forEach);

    /**
     * @brief Scales nearby items (main, cross, and diagonal neighbors) during drag.
     * @param currentIndex The ForEach-local index of the dragged item.
     * @param rect The margin frame rect of the dragged item.
     * @param delta The drag delta offset.
     */
    void ScaleNearbyItems(int32_t currentIndex, const RectF& rect, const OffsetF& delta);

    /**
     * @brief Finds the ForEach-local index of the item at the given grid position.
     * @param row The row in the grid matrix.
     * @param col The column in the grid matrix.
     * @param info The current GridLayoutInfo.
     * @return The ForEach-local index, or -1 if not found.
     */
    int32_t FindNeighborIndex(int32_t row, int32_t col, const GridLayoutInfo& info) const;

    /**
     * @brief Cancels the drag if the grid layout changes during dragging.
     * @return True if the drag was cancelled.
     */
    bool CancelDragOnGridChange();

    /**
     * @brief Processes a swap for the given item index.
     * Finds the swap target and triggers the swap animation if the target differs.
     * @param from The ForEach-local index of the dragged item.
     */
    void ProcessSwap(int32_t from);

    /**
     * @brief Stops auto-scrolling and resets scroll-related state.
     */
    void StopAutoScroll();

    /**
     * @brief Resolves cross axis column widths and adjusted gap from layout properties.
     * @param gridGeometry The Grid's geometry node.
     * @param layoutProperty The Grid's layout property.
     * @param crossGap The cross axis gap.
     * @param info The current GridLayoutInfo.
     * @return A pair of (crossLens vector, adjustedCrossGap).
     */
    std::pair<std::vector<double>, float> ResolveCrossLens(
        const RefPtr<GeometryNode>& gridGeometry,
        const RefPtr<GridLayoutProperty>& layoutProperty,
        float crossGap, const GridLayoutInfo& info) const;

    /**
     * @brief Calculates the cross axis position for a given column index.
     * @param col The column index.
     * @param adjustedCrossGap The adjusted cross axis gap.
     * @param crossLens The cross axis column widths.
     * @param gridGeometry The Grid's geometry node (for padding).
     * @return The cross axis position in pixels.
     */
    float CalculateCrossPosition(int32_t col, float adjustedCrossGap,
        const std::vector<double>& crossLens,
        const RefPtr<GeometryNode>& gridGeometry) const;

    /**
     * @brief Applies alignment and RTL adjustments to an item's offset.
     * Also checks if the position is within the visible viewport.
     * @param node The item's FrameNode.
     * @param row The row position.
     * @param col The column position.
     * @param offset The base offset to adjust.
     * @param crossLens The cross axis column widths.
     * @param gridGeometry The Grid's geometry node.
     * @param layoutProperty The Grid's layout property.
     * @param info The current GridLayoutInfo.
     * @return The adjusted offset, or std::nullopt if out of viewport.
     */
    std::optional<OffsetF> ApplyAlignmentAndRTL(const RefPtr<FrameNode>& node,
        int32_t row, int32_t col, OffsetF offset,
        const std::vector<double>& crossLens,
        const RefPtr<GeometryNode>& gridGeometry,
        const RefPtr<GridLayoutProperty>& layoutProperty,
        const GridLayoutInfo& info) const;

    /**
     * @brief Checks whether the item at the given index is visible in the viewport.
     * @param currentIndex The ForEach-local index.
     * @param info The current GridLayoutInfo.
     * @return True if the item (including its row span) is at least partially visible.
     */
    bool IsItemInViewport(int32_t currentIndex, const GridLayoutInfo& info) const;

    /**
     * @brief Gets the start and end row for an item (accounting for row span).
     * @param currentIndex The ForEach-local index.
     * @param info The current GridLayoutInfo.
     * @return A pair of (startRow, endRow).
     */
    std::pair<int32_t, int32_t> GetRowRangeForItem(int32_t currentIndex,
        const GridLayoutInfo& info) const;

    /**
     * @brief Finds the best swap candidate among a list of candidates.
     * Uses center-point distance comparison between the dragged item and each candidate.
     * @param currentIndex The ForEach-local index of the dragged item.
     * @param candidates The vector of candidate indices.
     * @param delta The drag delta offset.
     * @param currentRow The start row of the dragged item.
     * @param endRow The end row of the dragged item.
     * @param info The current GridLayoutInfo.
     * @return The ForEach-local index of the best candidate.
     */
    int32_t FindBestCandidate(int32_t currentIndex,
        const std::vector<int32_t>& candidates, const OffsetF& delta,
        int32_t currentRow, int32_t endRow, const GridLayoutInfo& info) const;

    /**
     * @brief Validates whether a candidate is in the correct direction for auto-scroll.
     * @param candidate The ForEach-local candidate index.
     * @param currentRow The start row of the dragged item.
     * @param endRow The end row of the dragged item.
     * @param info The current GridLayoutInfo.
     * @return True if the candidate is valid for the current auto-scroll direction.
     */
    bool IsCandidateValidForAutoScroll(int32_t candidate, int32_t currentRow,
        int32_t endRow, const GridLayoutInfo& info) const;

    /**
     * @brief Describes the bounding row/column range for candidate collection.
     */
    struct MovementBounds {
        int32_t startRow = 0;
        int32_t endRow = 0;
        int32_t startCol = 0;
        int32_t endCol = 0;
        bool zeroMove = false;
    };

    /**
     * @brief Computes the movement bounding box based on drag delta and item span.
     * @param currentIndex The ForEach-local index of the dragged item.
     * @param currentCol The current column.
     * @param currentRow The current row.
     * @param delta The drag delta offset.
     * @param info The current GridLayoutInfo.
     * @return The MovementBounds for candidate collection.
     */
    MovementBounds ComputeMovementBounds(int32_t currentIndex,
        int32_t currentCol, int32_t currentRow,
        const OffsetF& delta, const GridLayoutInfo& info) const;

    /**
     * @brief Resolves the span info for a single ForEach item.
     * @param forEachIdx The ForEach-local index.
     * @param crossCount The total number of cross axis columns.
     * @return The SimSpanInfo for the item.
     */
    SimSpanInfo ResolveItemSpan(int32_t forEachIdx, int32_t crossCount) const;

    /**
     * @brief Finds the row containing the item with the highest global index in the matrix.
     * @param matrix The simulated grid matrix.
     * @return The row index.
     */
    static int32_t FindMaxIndexRow(const SimMatrix& matrix);

    /**
     * @brief Prints the simulated matrix for debugging purposes.
     * @param matrix The simulated grid matrix to print.
     */
    static void PrintSimMatrix(const SimMatrix& matrix);

    /**
     * @brief Finds the row from which to start placing items in the simulated matrix.
     * @param matrix The simulated matrix (may be empty).
     * @param info The current GridLayoutInfo.
     * @return The starting row index.
     */
    int32_t FindPlacementStartRow(const SimMatrix& matrix, const GridLayoutInfo& info) const;

    WeakPtr<FrameNode> frameNode_;
    WeakPtr<ForEachBaseNode> forEachNode_;
    WeakPtr<FrameNode> gridNode_;
    Axis axis_ = Axis::VERTICAL;
    int32_t totalCount_ = -1;
    bool scrolling_ = false;
    bool autoScrollForward_ = false; // true = scroll toward end (bottom/right)
    bool inAutoScrollHotZone_ = false; // true when finger is in top/bottom hot zone during drag
    OffsetF dragOffset_;
    OffsetF realOffset_;

    int32_t currentIndex_ = -1;
    int32_t fromIndex_ = -1;
    int32_t moveThroughIndex_ = -1;
    int32_t forEachStartIndex_ = 0;  // Cached ForEach start index in parent Grid
    VectorF prevScale_{1.0f, 1.0f};
    Shadow prevShadow_;
    int32_t prevZIndex_ = 0;
    GridItemDragState dragState_ = GridItemDragState::IDLE;
    bool isDragAnimationStopped_ = false;
    std::map<WeakPtr<RenderContext>, VectorF> scaleNode_;
    std::map<WeakPtr<RenderContext>, VectorF> prevScaleNode_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_DRAG_MANAGER_H
