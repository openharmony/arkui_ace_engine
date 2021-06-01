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
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RenderGridLayout : public RenderNode {
    DECLARE_ACE_TYPE(RenderGridLayout, RenderNode);

public:
    static RefPtr<RenderNode> Create();

    void OnChildAdded(const RefPtr<RenderNode>& renderNode) override;

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    // Adjust focus index when grid_item request focus itself.
    void UpdateFocusInfo(int32_t focusIndex);

    // Support to grid element response focus event.
    int32_t RequestNextFocus(bool vertical, bool reverse);

protected:
    LayoutParam MakeInnerLayoutParam(int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan) const;

    void SetItemIndex(const RefPtr<RenderNode>& child, int32_t index);

    int32_t GetItemRowIndex(const RefPtr<RenderNode>& child) const;

    int32_t GetItemColumnIndex(const RefPtr<RenderNode>& child) const;

    int32_t GetItemSpan(const RefPtr<RenderNode>& child, bool isRow) const;

    void GetNextGird(int32_t& curRow, int32_t& curCol) const;

    bool CheckGridPlaced(int32_t index, int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan);

    int32_t GetIndexByGrid(int32_t row, int32_t column) const;

    // Sets child position, the mainAxis does not contain the offset.
    void SetChildPosition(const RefPtr<RenderNode>& child, int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan);

    void DisableChild(const RefPtr<RenderNode>& child, int32_t index);

    void ConvertRepeatArgs(std::string& args);

    // Handle direction key move
    int32_t focusMove(KeyDirection direction);

    Size GetTargetLayoutSize(int32_t row, int32_t col);

    std::string PreParseRows();

    std::string PreParseCols();

    void InitialGridProp();

    void UpdateAccessibilityAttr();

    std::vector<double> ParseArgs(const std::string& agrs, double size, double gap);

    std::vector<double> ParseAutoFill(const std::vector<std::string>& strs, double size, double gap);

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
    double colGap_ = 0.0;
    double rowGap_ = 0.0;
    std::string colsArgs_;
    std::string rowsArgs_;
    bool rightToLeft_ = false;
    // Map structure: [rowIndex - (columnIndex, index)]
    std::map<int32_t, std::map<int32_t, int32_t>> gridMatrix_;
    // Map structure: [rowIndex - columnIndex - (width, height)]
    std::map<int32_t, std::map<int32_t, Size>> gridCells_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_GRID_LAYOUT_RENDER_GRID_LAYOUT_H
