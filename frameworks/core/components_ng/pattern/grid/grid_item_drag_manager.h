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
    ~GridItemDragManager() override = default;

    RefPtr<FrameNode> GetHost() const
    {
        return frameNode_.Upgrade();
    }

    void InitDragDropEvent();
    void DeInitDragDropEvent();

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
    bool HasIrregularItemInRange(int32_t from, int32_t to) const;
    void PrepareIrregularDragState(int32_t from, int32_t to, GridLayoutInfo& info);

    int32_t FindSwapTarget(int32_t currentIndex, const OffsetF& delta);


    struct TargetPosition {
        int32_t row = 0;
        int32_t col = 0;
        bool isValid = false;
        int32_t rowSpan = 1;
        int32_t colSpan = 1;
    };
    TargetPosition CalculateTargetPosition(int32_t currentRow, int32_t currentCol,
        const OffsetF& delta, const GridLayoutInfo& info) const;
    void ComputeTargetRowCol(TargetPosition& targetPos, int32_t currentRow, int32_t currentCol,
        float mainDelta, float crossDelta, float singleRowHeight, float singleColWidth,
        int32_t crossCount) const;
    void ClampTargetPosition(TargetPosition& targetPos, int32_t crossCount, int32_t rowCount) const;
    bool CheckTargetCellsExist(const TargetPosition& targetPos, int32_t rowCount,
        const GridLayoutInfo& info) const;
    int32_t GetTargetItemAtPosition(int32_t currentIndex, const TargetPosition& targetPos,
        const GridLayoutInfo& info, const OffsetF& delta) const;
    float GetItemMainSize(int32_t currentIndex, const GridLayoutInfo& info) const;
    float GetItemCrossSize(int32_t currentIndex, const GridLayoutInfo& info) const;
    bool ValidateMoveBySimulation(int32_t from, int32_t to, const GridLayoutInfo& info) const;

    struct SimSpanInfo {
        int32_t rowSpan = 1;
        int32_t colSpan = 1;
    };
    using SimMatrix = std::map<int32_t, std::map<int32_t, int32_t>>;
    std::vector<SimSpanInfo> CollectSpanInfo(int32_t totalItems) const;
    static void ApplyMoveToArray(std::vector<int32_t>& order, int32_t from, int32_t to);
    int32_t FindAvailableColumn(const SimMatrix& matrix, int32_t row,
        int32_t colSpan, int32_t crossCount) const;
    std::pair<int32_t, int32_t> PlaceItemInMatrix(SimMatrix& matrix, int32_t itemIdx,
        const SimSpanInfo& span, int32_t crossCount, int32_t totalItems) const;
    bool CopyLayoutToMatrix(SimMatrix& matrix, const std::vector<SimSpanInfo>& spans,
        const GridLayoutInfo& info, int32_t count) const;
    bool SimulateLayout(SimMatrix& matrix, const std::vector<int32_t>& order,
        const std::vector<SimSpanInfo>& spans, const GridLayoutInfo& info,
        int32_t startRebuild, int32_t totalItems, int32_t from, int32_t to) const;

    struct ItemSpanInfo {
        int32_t rowSpan = 1;
        int32_t colSpan = 1;
        bool isIrregular = false;
    };
    ItemSpanInfo GetIrregularItemInfoAndSpan(int32_t index) const;
    void HandleAutoScroll(int32_t index, const PointF& point, const RectF& frameRect);
    void HandleScrollCallback();
    bool IsInHotZone(int32_t index, const RectF& frameRect) const;
    void SetPosition(const OffsetF& offset);
    int32_t GetIndex() const;
    RefPtr<FrameNode> GetGridFrameNode() const;
    OffsetF GetParentPaddingOffset() const;
    bool GetDummyItemRect(int32_t index, RectF& rect) const;

    WeakPtr<FrameNode> frameNode_;
    WeakPtr<ForEachBaseNode> forEachNode_;
    WeakPtr<FrameNode> gridNode_;
    GridLayoutInfo info_;
    Axis axis_ = Axis::VERTICAL;
    int32_t totalCount_ = -1;
    bool scrolling_ = false;
    OffsetF dragOffset_;
    OffsetF realOffset_;

    int32_t currentIndex_ = -1;
    int32_t fromIndex_ = -1;
    VectorF prevScale_{1.0f, 1.0f};
    Shadow prevShadow_;
    int32_t prevZIndex_ = 0;
    GridItemDragState dragState_ = GridItemDragState::IDLE;
    bool isDragAnimationStopped_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_GRID_ITEM_DRAG_MANAGER_H
