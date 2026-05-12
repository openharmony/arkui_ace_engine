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

enum class GridItemDragState {
    IDLE,
    LONG_PRESS,
    DRAGGING,
    SWAPPING,
};

class ACE_EXPORT GridItemDragManager : public AceType {
    DECLARE_ACE_TYPE(GridItemDragManager, AceType);

public:
    GridItemDragManager(RefPtr<FrameNode> host, RefPtr<ForEachBaseNode> forEach)
        : frameNode_(host), forEachNode_(forEach)
    {
        gridNode_ = GetGridFrameNode();
    }
    ~GridItemDragManager() override;

    RefPtr<FrameNode> GetHost() const
    {
        return frameNode_.Upgrade();
    }

    void InitDragDropEvent();
    void DeInitDragDropEvent();
    void Reset();

private:
    void HandleOnItemLongPress(const GestureEvent& info);
    void HandleOnItemDragStart(const GestureEvent& info);
    void HandleOnItemDragUpdate(const GestureEvent& info);
    void HandleOnItemDragEnd(const GestureEvent& info);
    void HandleOnItemDragCancel();
    void HandleZIndexAndPosition();
    void HandleBackShadow();
    void HandleTransformScale();
    void HandleDragEndAnimation();
    void HandleSwapAnimation(int32_t from, int32_t to);
    void PrepareIrregularDragState(int32_t from, int32_t to, GridLayoutInfo& info);

    struct SimSpanInfo {
        int32_t rowSpan = 1;
        int32_t colSpan = 1;
    };
    using SimMatrix = std::map<int32_t, std::map<int32_t, int32_t>>;
    void CalculateGaps(float& mainGap, float& crossGap, const GridLayoutInfo& info) const;
    bool IsRowInViewport(int32_t row, float mainGap, float mainSize, const GridLayoutInfo& info) const;
    float CalculateMainPosition(int32_t targetRow, float mainGap, const GridLayoutInfo& info) const;
    std::optional<OffsetF> CreatePositionFromCoords(float mainPos, float crossPos) const;
    std::optional<OffsetF> SearchRowForTarget(const std::map<int32_t, int32_t>& cols, int32_t targetIdx,
        int32_t row, const RefPtr<FrameNode>& node, int32_t colSpan, float mainGap,
        float crossGap, const GridLayoutInfo& info) const;
    std::optional<OffsetF> FindItemPositionInMatrix(const SimMatrix& simMatrix, int32_t targetIdx,
        const RefPtr<FrameNode>& node, int32_t colSpan, float mainGap, float crossGap,
        const GridLayoutInfo& info) const;
    std::optional<OffsetF> CalculateFromNewPosition(int32_t from, int32_t to, const GridLayoutInfo& info) const;

    float CalculateDistance(const OffsetF& pos1, const OffsetF& pos2) const;
    int32_t SelectBestCandidate(int32_t currentIndex, bool movingDown,
        int32_t currentBest, int32_t candidate, float candidateDistance, float bestDistance) const;

    int32_t FindSwapTarget(int32_t currentIndex, const OffsetF& delta);
    float GetItemMainSize(int32_t currentIndex, const GridLayoutInfo& info) const;
    float GetItemCrossSize(int32_t currentIndex, const GridLayoutInfo& info) const;
    std::vector<SimSpanInfo> CollectSpanInfo(const GridLayoutInfo& info) const;
    static void ApplyMoveToArray(std::vector<int32_t>& order, int32_t from, int32_t to);
    int32_t FindAvailableColumn(const SimMatrix& matrix, int32_t row,
        int32_t colSpan, int32_t crossCount) const;
    std::pair<int32_t, int32_t> PlaceItemInMatrix(const GridLayoutInfo& info, SimMatrix& matrix,
        int32_t itemIdx, const SimSpanInfo& span, int32_t crossCount, int32_t viewportEndRow) const;
    bool CopyLayoutToMatrix(SimMatrix& matrix, std::vector<SimSpanInfo>& spans,
        const GridLayoutInfo& info, int32_t count, float mainGap, float mainSize) const;
    int32_t CalculateColSpan(const std::map<int32_t, int32_t>& rowCols,
        int32_t col, int32_t itemIdx, int32_t crossCount) const;
    int32_t CalculateRowSpan(const GridLayoutInfo& info, int32_t row, int32_t col, int32_t itemIdx) const;
    void CalculateSpanInfo(const GridLayoutInfo& info, int32_t itemIdx,
        int32_t row, int32_t col, std::vector<SimSpanInfo>& spans) const;
    void FillMatrixWithItem(SimMatrix& matrix, int32_t itemIdx,
        int32_t row, int32_t col, const std::vector<SimSpanInfo>& spans) const;
    std::vector<int32_t> CollectSwapCandidates(int32_t currentIndex, const OffsetF& delta,
        const GridLayoutInfo& info) const;
    bool SimulateLayoutInRange(SimMatrix& matrix, const std::vector<int32_t>& order,
        const std::vector<SimSpanInfo>& spans, const GridLayoutInfo& info,
        int32_t startRebuild, int32_t endRebuild, int32_t from, int32_t to,
        float mainGap, float mainSize) const;

    struct ItemSpanInfo {
        int32_t rowSpan = 1;
        int32_t colSpan = 1;
        bool isIrregular = false;
    };
    int32_t GetColSpanForIrregularItem(int32_t crossSpan) const;
    ItemSpanInfo GetIrregularItemInfoAndSpan(int32_t index) const;
    void HandleAutoScroll(int32_t index, const PointF& point, const RectF& frameRect);
    void HandleScrollCallback();
    bool IsInHotZone(int32_t index, const RectF& frameRect) const;
    void SetPosition(const OffsetF& offset);
    int32_t GetIndex() const;
    RefPtr<FrameNode> GetGridFrameNode() const;
    OffsetF GetParentPaddingOffset() const;

    bool CancelDragOnGridChange();
    void ProcessSwap(int32_t from);
    void StopAutoScroll();

    std::pair<std::vector<double>, float> ResolveCrossLens(
        const RefPtr<GeometryNode>& gridGeometry,
        const RefPtr<GridLayoutProperty>& layoutProperty,
        float crossGap, const GridLayoutInfo& info) const;
    float CalculateCrossPosition(int32_t col, float adjustedCrossGap,
        const std::vector<double>& crossLens,
        const RefPtr<GeometryNode>& gridGeometry) const;
    std::optional<OffsetF> ApplyAlignmentAndRTL(const RefPtr<FrameNode>& node,
        int32_t row, int32_t col, OffsetF offset,
        const std::vector<double>& crossLens,
        const RefPtr<GeometryNode>& gridGeometry,
        const RefPtr<GridLayoutProperty>& layoutProperty,
        const GridLayoutInfo& info) const;

    bool IsItemInViewport(int32_t currentIndex, const GridLayoutInfo& info) const;
    std::pair<int32_t, int32_t> GetRowRangeForItem(int32_t currentIndex,
        const GridLayoutInfo& info) const;
    int32_t FindBestCandidate(int32_t currentIndex,
        const std::vector<int32_t>& candidates, const OffsetF& delta,
        int32_t currentRow, int32_t endRow, const GridLayoutInfo& info) const;
    bool IsCandidateValidForAutoScroll(int32_t candidate, int32_t currentRow,
        int32_t endRow, const GridLayoutInfo& info) const;

    struct MovementBounds {
        int32_t startRow = 0;
        int32_t endRow = 0;
        int32_t startCol = 0;
        int32_t endCol = 0;
        bool zeroMove = false;
    };
    MovementBounds ComputeMovementBounds(int32_t currentIndex,
        int32_t currentCol, int32_t currentRow,
        const OffsetF& delta, const GridLayoutInfo& info) const;

    SimSpanInfo ResolveItemSpan(int32_t forEachIdx, int32_t crossCount) const;
    static int32_t FindMaxIndexRow(const SimMatrix& matrix);
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
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_DRAG_MANAGER_H
