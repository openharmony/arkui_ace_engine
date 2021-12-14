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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_RENDER_GRID_LAYOUT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_RENDER_GRID_LAYOUT_H

#include <functional>
#include <map>
#include <vector>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/grid_layout/grid_layout_component.h"
#include "core/components/positioned/positioned_component.h"
#include "core/components/stack/stack_element.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t DEFAULT_FINGERS = 1;
constexpr int32_t DEFAULT_DURATION = 150;
constexpr int32_t DEFAULT_DISTANCE = 0;

}; // namespace

using OnItemDragFunc = std::function<void(const RefPtr<ItemDragInfo>& info)>;
class RenderGridLayout : public RenderNode {
    DECLARE_ACE_TYPE(RenderGridLayout, RenderNode);

public:
    static RefPtr<RenderNode> Create();

    void OnChildAdded(const RefPtr<RenderNode>& renderNode) override;

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;

    // Adjust focus index when grid_item request focus itself.
    void UpdateFocusInfo(int32_t focusIndex);

    // Support to grid element response focus event.
    int32_t RequestNextFocus(bool vertical, bool reverse);

    const std::string& GetColumnsTemplate() const
    {
        return colsArgs_;
    }

    const std::string& GetRowTemplate() const
    {
        return rowsArgs_;
    }

    double GetColumnsGap() const
    {
        return colGap_;
    }

    double GetRowGaps() const
    {
        return rowGap_;
    }

    Dimension GetColumns() const
    {
        return userColGap_;
    }

    Dimension GetRows() const
    {
        return userRowGap_;
    }

    const std::string& GetScrollBarWidth() const
    {
        return scrollBarWidth_;
    }

    const std::string& GetScrollBarColor() const
    {
        return scrollBarColor_;
    }

    DisplayMode GetScrollBar() const
    {
        return displayMode_;
    }

    const OnItemDragFunc& GetUpdatePositionId() const
    {
        return updatePosition_;
    }

    void SetUpdatePositionId(const OnItemDragFunc& updatePosition)
    {
        updatePosition_ = updatePosition;
    }

protected:
    virtual LayoutParam MakeInnerLayoutParam(int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan) const;

    void SetItemIndex(const RefPtr<RenderNode>& child, int32_t index);

    int32_t GetItemRowIndex(const RefPtr<RenderNode>& child) const;

    int32_t GetItemColumnIndex(const RefPtr<RenderNode>& child) const;

    int32_t GetItemSpan(const RefPtr<RenderNode>& child, bool isRow) const;

    virtual void GetNextGrid(int32_t& curRow, int32_t& curCol) const;

    virtual void GetPreviousGird(int32_t& curRow, int32_t& curCol) const;

    virtual bool CheckGridPlaced(int32_t index, int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan);

    int32_t GetIndexByGrid(int32_t row, int32_t column) const;

    // Sets child position, the mainAxis does not contain the offset.
    virtual void SetChildPosition(
        const RefPtr<RenderNode>& child, int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan);

    void DisableChild(const RefPtr<RenderNode>& child, int32_t index);

    void ConvertRepeatArgs(std::string& args);

    // Handle direction key move
    int32_t focusMove(KeyDirection direction);

    Size GetTargetLayoutSize(int32_t row, int32_t col);

    std::string PreParseRows();

    std::string PreParseCols();

    virtual void InitialGridProp();

    void UpdateAccessibilityAttr();

    std::vector<double> ParseArgs(const std::string& agrs, double size, double gap);

    std::vector<double> ParseAutoFill(const std::vector<std::string>& strs, double size, double gap);

    template<typename T>
    RefPtr<T> FindTargetRenderNode(const RefPtr<PipelineContext> context, const GestureEvent& info);

    void SetPreTargetRenderGrid(const RefPtr<RenderGridLayout>& preTargetRenderGrid)
    {
        preTargetRenderGrid_ = preTargetRenderGrid;
    }

    const RefPtr<RenderGridLayout> GetPreTargetRenderGrid() const
    {
        return preTargetRenderGrid_;
    }

    void SetMainTargetRenderGrid(const RefPtr<RenderGridLayout>& mainTargetRenderGrid)
    {
        mainTargetRenderGrid_ = mainTargetRenderGrid;
    }

    const RefPtr<RenderGridLayout> GetMainTargetRenderGrid() const
    {
        return mainTargetRenderGrid_;
    }

    void SetLongPressPoint(const Point& lastLongPressPoint)
    {
        lastLongPressPoint_ = lastLongPressPoint;
    }

    const Point GetLongPressPoint() const
    {
        return lastLongPressPoint_;
    }

    void ClearDragInfo();
    void CalIsVertical();
    void RegisterLongPressedForItems();
    void CreateDragDropRecognizer();
    void ActionStart(const RefPtr<ItemDragInfo>& info, RefPtr<Component> customComponent);
    void PanOnActionUpdate(const GestureEvent& info);
    void PanOnActionEnd(const GestureEvent& info);
    void OnDragEnter(const RefPtr<ItemDragInfo>& info);
    void OnDragLeave(const RefPtr<ItemDragInfo>& info);
    void OnDragMove(const RefPtr<ItemDragInfo>& info);
    bool OnDrop(const RefPtr<ItemDragInfo>& info);
    void ImpDragStart(const RefPtr<ItemDragInfo>& info);
    bool ImpDropInGrid(const RefPtr<ItemDragInfo>& info);

    void OnCallSubDragEnter(const RefPtr<ItemDragInfo>& info);
    void OnCallSubDragLeave(const RefPtr<ItemDragInfo>& info);

    // Check whether the item is currently allowed to be inserted
    bool CouldBeInserted();
    bool NeedBeLarger();
    bool NeedBeSmaller();
    void BackGridMatrix();
    void RestoreScene();

    int32_t CountItemInGrid();
    // dragLeave -1;dragEnter 1; none 0;
    void InitialDynamicGridProp(int32_t dragLeaveOrEnter = 0);
    void PerformLayoutForEditGrid();
    bool CalDragCell(const RefPtr<ItemDragInfo>& info);
    bool CalDragRowIndex(double dragRelativelyY, int32_t& dragRowIndex);
    bool CalDragColumIndex(double dragRelativelyX, int32_t& dragColIndex);
    void MoveItems();

    // These functions cannot be called independently, they must be called by MoveItems()
    void MoveWhenNoInsertCell();
    void MoveWhenNoInsertCellAndNoItemInDragCell();
    void MoveWhenNoInsertCellButWithItemInDragCell();
    void MoveWhenNoInsertCellButWithItemInDragCellAndDragEnter();
    void MoveWhenNoInsertCellButWithItemInDragCellAndDragStart();
    void MoveWhenWithInsertCell();

    void MoveWhenWithInsertCellAndNoItemInDragCell();
    void MoveWhenWithInsertCellButWithItemInDragCell();
    void MoveWhenWithInsertCellButWithItemInDragCellDragBeforeInsert();
    void MoveWhenWithInsertCellButWithItemInDragCellDragAfterInsert();

    void FakeRemoveDragItem();

    // it should be cells which has item in
    bool MoveItemsForward(int32_t fromRow, int32_t fromColum, int32_t toRow, int32_t toColum);

    // it should be cells which has item in
    bool MoveItemsBackward(int32_t fromRow, int32_t fromColum, int32_t toRow, int32_t toColum);
    void UpdateMatrixByIndexStrong(int32_t index, int32_t row, int32_t colum);
    void UpdateCurInsertPos(int32_t curInsertRow, int32_t curInsertColum);
    int32_t CalIndexForItemByRowAndColum(int32_t row, int32_t colum);

    // If the first is equal the second, return true, else return false.
    bool SortCellIndex(int32_t rowFirst, int32_t columFirst, int32_t rowSecond, int32_t columSecond, bool& firstIsPre);

    // if there is no empty in the cell return false, else return true.
    bool CalTheFirstEmptyCell(int32_t& rowIndex, int32_t& columIndex, bool ignoreInsert);

    void SetGridLayoutParam();
    void CalculateVerticalSize(std::vector<double>& cols, std::vector<double>& rows, int32_t dragLeaveOrEnter);
    void CalculateHorizontalSize(std::vector<double>& cols, std::vector<double>& rows, int32_t dragLeaveOrEnter);
    void UpdateCollectionInfo(std::vector<double> cols, std::vector<double> rows);

    bool isVertical_ = false;
    bool updateFlag_ = false;
    FlexDirection direction_ = FlexDirection::ROW;
    FlexAlign crossAxisAlign_ = FlexAlign::CENTER;

    int32_t focusRow_ = -1;
    int32_t focusCol_ = -1;
    int32_t focusIndex_ = 0;

    double colSize_ = 0.0;
    double rowSize_ = 0.0;
    double gridWidth_ = -1.0;
    double gridHeight_ = -1.0;
    int32_t colCount_ = 0;
    int32_t rowCount_ = 0;
    Dimension userColGap_ = 0.0_px;
    Dimension userRowGap_ = 0.0_px;
    double colGap_ = 0.0;
    double rowGap_ = 0.0;
    std::string colsArgs_;
    std::string rowsArgs_;
    std::string scrollBarWidth_;
    std::string scrollBarColor_;
    DisplayMode displayMode_ = DisplayMode::OFF;
    bool rightToLeft_ = false;
    // Map structure: [rowIndex - (columnIndex, index)]
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix_;
    // Map structure: [rowIndex - columnIndex - (width, height)]
    std::map<int32_t, std::map<int32_t, Size>> gridCells_;

    RefPtr<GestureRecognizer> dragDropGesture_;
    RefPtr<RenderGridLayout> preTargetRenderGrid_ = nullptr;
    RefPtr<RenderGridLayout> mainTargetRenderGrid_ = nullptr;

    // The list of renderNodes of items in the grid
    std::vector<RefPtr<RenderNode>> itemsInGrid_;

    // back for gridMatrix_
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrixBack_;

    // The maximum number of items that the grid can hold
    int32_t itemCountMax_ = -1;

    // The grid length in the main axis direction
    int32_t cellLength_ = 0;

    // The maximum number of rows (columns) that can be accommodated in a variable direction.
    // (only for dynamic limited grid)
    int32_t mainCountMax_ = -1;

    // The minimum number of rows (columns) that must be accommodated in the variable direction.
    // (only for dynamic limited grid)
    int32_t mainCountMin_ = -1;

    // The maximum number of items that the grid can hold.
    // (Only the dynamic grid needs to be used to determine whether the main sequence needs to be increased.)
    int32_t curItemCountMax_ = -1;

    // The rowIndex of the grid currently to be inserted
    int32_t curInsertRowIndex_ = -1;

    // The columnIndex of the grid currently to be inserted
    int32_t curInsertColumnIndex_ = -1;

    // The rowIndex of the grid where the Drag coordinates are located
    int32_t dragPosRowIndex_ = -1;

    // The columnIndex of the grid where the Drag coordinates are located
    int32_t dragPosColumnIndex_ = -1;

    // The index of the item currently being dragged.
    int32_t dragingItemIndex_ = -1;

    // Whether to send changes to the grid where the drag coordinate is located
    bool dragPosChanged_ = false;

    bool isDynamicGrid_ = false;

    bool editMode_ = false;

    bool itemLongPressed_ = false;

    bool itemDragEntered_ = false;

    bool itemDragStarted_ = false;

    bool isDragChangeLayout_ = false;

    bool needRestoreScene_ = false;

    bool isInMainGrid_ = false;

    bool isMainGrid_ = false;

    bool reEnter_ = false;

    WeakPtr<RenderNode> dragingItemRenderNode_;
    WeakPtr<RenderGridLayout> subGrid_;
    RefPtr<GridLayoutComponent> component_;

    OnGridDragEnterFunc OnGridDragEnterFunc_;
    OnGridDragMoveFunc onGridDragMoveFunc_;
    OnGridDragLeaveFunc onGridDragLeaveFunc_;
    OnGridDragStartFunc onGridDragStartFunc_;
    OnGridDropFunc onGridDropFunc_;

    OnItemDragFunc updatePosition_;
    Point lastGlobalPoint_;
    Point lastLongPressPoint_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_RENDER_GRID_LAYOUT_H
