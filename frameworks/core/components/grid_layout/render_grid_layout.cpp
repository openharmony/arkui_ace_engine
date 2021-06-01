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

#include "core/components/grid_layout/render_grid_layout.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <regex>

#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/animation/curve_animation.h"
#include "core/components/grid_layout/grid_layout_component.h"
#include "core/components/grid_layout/render_grid_layout_item.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t DEFAULT_DEPTH = 10;
constexpr bool HORIZONTAL = false;
constexpr bool VERTICAL = true;
constexpr bool FORWARD = false;
constexpr bool REVERSE = true;
constexpr double FULL_PERCENT = 100.0;
constexpr uint32_t REPEAT_MIN_SIZE = 6;
const char UNIT_PIXEL[] = "px";
const char UNIT_PERCENT[] = "%";
const char UNIT_RATIO[] = "fr";
const char UNIT_AUTO[] = "auto";
const char UNIT_AUTO_FILL[] = "auto-fill";
const char REPEAT_PREFIX[] = "repeat";
const std::regex REPEAT_NUM_REGEX(R"(^repeat\((\d+),(.+)\))", std::regex::icase); // regex for "repeat(2, 100px)"
const std::regex AUTO_REGEX(R"(^repeat\((.+),(.+)\))", std::regex::icase);        // regex for "repeat(auto-fill, 10px)"

// first bool mean if vertical, second bool mean if reverse
// false, false --> RIGHT
// false, true --> LEFT
// true, false --> DOWN
// true, true ---> UP
// This map will adapter the Grid FlexDirection with Key Direction.
const std::map<bool, std::map<bool, std::map<bool, KeyDirection>>> DIRECTION_MAP = {
    { false, // RTL is false
        {
            { HORIZONTAL, { { FORWARD, KeyDirection::RIGHT }, { REVERSE, KeyDirection::LEFT } } },
            { VERTICAL, { { FORWARD, KeyDirection::DOWN }, { REVERSE, KeyDirection::UP } } }
        }
    },
    { true, // RTL is true
        {
            { HORIZONTAL, { { FORWARD, KeyDirection::LEFT }, { REVERSE, KeyDirection::RIGHT } } },
            { VERTICAL, { { FORWARD, KeyDirection::DOWN }, { REVERSE, KeyDirection::UP } } }
        }
    }
};

} // namespace

void RenderGridLayout::OnChildAdded(const RefPtr<RenderNode>& renderNode)
{
    RenderNode::OnChildAdded(renderNode);
}

void RenderGridLayout::Update(const RefPtr<Component>& component)
{
    const RefPtr<GridLayoutComponent> grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (!grid) {
        LOGE("RenderGridLayout update failed.");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }

    updateFlag_ = true;
    direction_ = grid->GetDirection();
    crossAxisAlign_ = grid->GetFlexAlign();
    gridWidth_ = grid->GetWidth();
    gridHeight_ = grid->GetHeight();
    colsArgs_ = grid->GetColumnsArgs();
    rowsArgs_ = grid->GetRowsArgs();
    colGap_ = grid->GetColumnGap();
    rowGap_ = grid->GetRowGap();
    rightToLeft_ = grid->GetRightToLeft();

    if (direction_ == FlexDirection::COLUMN) {
        isVertical_ = true;
    } else {
        isVertical_ = false;
    }

    MarkNeedLayout();
}

void RenderGridLayout::UpdateFocusInfo(int32_t focusIndex)
{
    if (focusIndex < 0) {
        LOGW("Invalid focus index, update focus info failed.");
        return;
    }
    if (focusIndex != focusIndex_) {
        LOGD("Update focus index from %{public}d to %{public}d", focusIndex_, focusIndex);
        focusIndex_ = focusIndex;
        for (const auto& gridMap : gridMatrix_) {
            for (const auto& grid : gridMap.second) {
                if (grid.second == focusIndex) {
                    focusRow_ = gridMap.first;
                    focusCol_ = grid.first;
                }
            }
        }
    }
}

int32_t RenderGridLayout::RequestNextFocus(bool vertical, bool reverse)
{
    KeyDirection key = DIRECTION_MAP.at(rightToLeft_).at(vertical).at(reverse);
    int32_t index = focusMove(key);
    if (index < 0) {
        return index;
    }
    return focusIndex_;
}

// Handle direction key move
int32_t RenderGridLayout::focusMove(KeyDirection direction)
{
    int32_t nextRow = focusRow_;
    int32_t nextCol = focusCol_;
    int32_t next = focusIndex_;
    while (focusIndex_ == next || next < 0) {
        switch (direction) {
            case KeyDirection::UP:
                --nextRow;
                break;
            case KeyDirection::DOWN:
                ++nextRow;
                break;
            case KeyDirection::LEFT:
                --nextCol;
                break;
            case KeyDirection::RIGHT:
                ++nextCol;
                break;
            default:
                return -1;
        }
        if (nextRow < 0 || nextCol < 0 || nextRow >= rowCount_ || nextCol >= colCount_) {
            return -1;
        }
        next = GetIndexByGrid(nextRow, nextCol);
    }
    LOGI("PreFocus:%{public}d CurrentFocus:%{public}d", focusIndex_, next);
    focusRow_ = nextRow;
    focusCol_ = nextCol;
    focusIndex_ = next;
    return next;
}

int32_t RenderGridLayout::GetIndexByGrid(int32_t row, int32_t column) const
{
    auto rowIter = gridMatrix_.find(row);
    if (rowIter != gridMatrix_.end()) {
        auto colIter = rowIter->second.find(column);
        if (colIter != rowIter->second.end()) {
            return colIter->second;
        }
    }
    return -1;
}

LayoutParam RenderGridLayout::MakeInnerLayoutParam(int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan) const
{
    LOGD("%{public}d %{public}d %{public}d %{public}d", row, col, rowSpan, colSpan);
    LayoutParam innerLayout;
    double rowLen = 0.0;
    double colLen = 0.0;
    for (int32_t i = 0; i < rowSpan; ++i) {
        rowLen += gridCells_.at(row + i).at(col).Height();
    }
    rowLen += (rowSpan - 1) * rowGap_;
    for (int32_t i = 0; i < colSpan; ++i) {
        colLen += gridCells_.at(row).at(col + i).Width();
    }
    colLen += (colSpan - 1) * colGap_;
    if (crossAxisAlign_ == FlexAlign::STRETCH) {
        innerLayout.SetMinSize(Size(colLen, rowLen));
        innerLayout.SetMaxSize(Size(colLen, rowLen));
    } else {
        innerLayout.SetMaxSize(Size(colLen, rowLen));
    }
    return innerLayout;
}

void RenderGridLayout::SetChildPosition(
    const RefPtr<RenderNode>& child, int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan)
{
    if (focusRow_ < 0 && focusCol_ < 0) {
        // Make the first item obtain focus.
        focusRow_ = row;
        focusCol_ = col;
    }

    // Calculate the position for current child.
    double positionX = 0.0;
    double positionY = 0.0;
    for (int32_t i = 0; i < row; ++i) {
        positionY += gridCells_.at(i).at(0).Height();
    }
    positionY += row * rowGap_;
    for (int32_t i = 0; i < col; ++i) {
        positionX += gridCells_.at(0).at(i).Width();
    }
    positionX += col * colGap_;

    // Calculate the size for current child.
    double rowLen = 0.0;
    double colLen = 0.0;
    for (int32_t i = 0; i < rowSpan; ++i) {
        rowLen += gridCells_.at(row + i).at(col).Height();
    }
    rowLen += (rowSpan - 1) * rowGap_;
    for (int32_t i = 0; i < colSpan; ++i) {
        colLen += gridCells_.at(row).at(col + i).Width();
    }
    colLen += (colSpan - 1) * colGap_;

    // If RTL, place the item from right.
    if (rightToLeft_) {
        positionX = colSize_ - positionX - colLen;
    }

    double widthOffset = (colLen - child->GetLayoutSize().Width()) / 2.0;
    double heightOffset = (rowLen - child->GetLayoutSize().Height()) / 2.0;
    child->SetPosition(Offset(positionX + widthOffset, positionY + heightOffset));
}

void RenderGridLayout::DisableChild(const RefPtr<RenderNode>& child, int32_t index)
{
    LOGW("No grid space for this item[%{public}d]", index);
    LayoutParam zeroLayout;
    zeroLayout.SetMinSize(Size(0.0, 0.0));
    zeroLayout.SetMaxSize(Size(0.0, 0.0));
    child->Layout(zeroLayout);
    child->SetPosition(Offset(0.0, 0.0));
}

Size RenderGridLayout::GetTargetLayoutSize(int32_t row, int32_t col)
{
    Size size;
    if (GetChildren().empty()) {
        return size;
    }
    LayoutParam innerLayout; // Init layout param for auto item.
    innerLayout.SetMaxSize(Size(colSize_, rowSize_));
    std::vector<std::string> rows, cols;
    StringUtils::StringSpliter(rowsArgs_, ' ', rows);
    rowCount_ = rows.size() == 0 ? 1 : rows.size();
    StringUtils::StringSpliter(colsArgs_, ' ', cols);
    colCount_ = cols.size() == 0 ? 1 : cols.size();
    int32_t rowIndex = 0;
    int32_t colIndex = 0;
    int32_t itemIndex = 0;
    for (const auto& item : GetChildren()) {
        int32_t itemRow = GetItemRowIndex(item);
        int32_t itemCol = GetItemColumnIndex(item);
        int32_t itemRowSpan = GetItemSpan(item, true);
        int32_t itemColSpan = GetItemSpan(item, false);
        if (itemRow >= 0 && itemRow < rowCount_ && itemCol >= 0 && itemCol < colCount_ &&
            CheckGridPlaced(itemIndex, itemRow, itemCol, itemRowSpan, itemColSpan)) {
            if (itemRow == row && itemCol == col) {
                item->Layout(innerLayout);
                return item->GetLayoutSize();
            }
        } else {
            while (!CheckGridPlaced(itemIndex, rowIndex, colIndex, itemRowSpan, itemColSpan)) {
                GetNextGird(rowIndex, colIndex);
                if (rowIndex >= rowCount_ || colIndex >= colCount_) {
                    break;
                }
            }
            if (rowIndex == row && colIndex == col) {
                item->Layout(innerLayout);
                return item->GetLayoutSize();
            }
        }
        ++itemIndex;
    }
    return size;
}

std::string RenderGridLayout::PreParseRows()
{
    if (rowsArgs_.empty() || rowsArgs_.find(UNIT_AUTO) == std::string::npos) {
        return rowsArgs_;
    }
    std::string rowsArgs;
    std::vector<std::string> strs;
    StringUtils::StringSpliter(rowsArgs_, ' ', strs);
    std::string current;
    int32_t rowArgSize = strs.size();
    for (int32_t i = 0; i < rowArgSize; ++i) {
        current = strs[i];
        if (strs[i] == std::string(UNIT_AUTO)) {
            Size layoutSize = GetTargetLayoutSize(i, 0);
            current = StringUtils::DoubleToString(layoutSize.Height()) + std::string(UNIT_PIXEL);
            gridMatrix_.clear();
        }
        rowsArgs += ' ' + current;
    }
    return rowsArgs;
}

std::string RenderGridLayout::PreParseCols()
{
    if (colsArgs_.empty() || colsArgs_.find(UNIT_AUTO) == std::string::npos) {
        return colsArgs_;
    }
    std::string colsArgs;
    std::vector<std::string> strs;
    StringUtils::StringSpliter(colsArgs_, ' ', strs);
    std::string current;
    int32_t colArgSize = strs.size();
    for (int32_t i = 0; i < colArgSize; ++i) {
        current = strs[i];
        if (strs[i] == std::string(UNIT_AUTO)) {
            Size layoutSize = GetTargetLayoutSize(0, i);
            current = StringUtils::DoubleToString(layoutSize.Width()) + std::string(UNIT_PIXEL);
            gridMatrix_.clear();
        }
        colsArgs += ' ' + current;
    }
    return colsArgs;
}

void RenderGridLayout::InitialGridProp()
{
    // Not first time layout after update, no need to initial.
    if (!updateFlag_) {
        return;
    }

    rowSize_ = ((gridHeight_ > 0.0) && (gridHeight_ < GetLayoutParam().GetMaxSize().Height())) ?
        gridHeight_ : GetLayoutParam().GetMaxSize().Height();
    colSize_ = ((gridWidth_ > 0.0) && (gridWidth_ < GetLayoutParam().GetMaxSize().Width())) ?
        gridWidth_ : GetLayoutParam().GetMaxSize().Width();
    if (NearEqual(rowSize_, Size::INFINITE_SIZE) && (rowsArgs_.find(UNIT_PERCENT) != std::string::npos ||
        rowsArgs_.find(UNIT_RATIO) != std::string::npos)) {
        rowSize_ = viewPort_.Height();
    }
    if (NearEqual(colSize_, Size::INFINITE_SIZE) && (colsArgs_.find(UNIT_PERCENT) != std::string::npos ||
        colsArgs_.find(UNIT_RATIO) != std::string::npos)) {
        colSize_ = viewPort_.Width();
    }
    LOGD("Row[%{public}s]: %{public}lf %{public}lf", rowsArgs_.c_str(), rowSize_, rowGap_);
    LOGD("Col[%{public}s]: %{public}lf %{public}lf", colsArgs_.c_str(), colSize_, colGap_);
    std::vector<double> rows = ParseArgs(PreParseRows(), rowSize_, rowGap_);
    std::vector<double> cols = ParseArgs(PreParseCols(), colSize_, colGap_);
    if (rows.empty()) {
        rows.push_back(rowSize_);
    }
    if (cols.empty()) {
        cols.push_back(colSize_);
    }
    if (NearEqual(rowSize_, Size::INFINITE_SIZE)) {
        rowSize_ = std::accumulate(rows.begin(), rows.end(), (rows.size() - 1) * rowGap_);
    }
    if (NearEqual(colSize_, Size::INFINITE_SIZE)) {
        colSize_ = std::accumulate(cols.begin(), cols.end(), (cols.size() - 1) * colGap_);
    }
    // Initialize the columnCount and rowCount, default is 1
    colCount_ = cols.size();
    rowCount_ = rows.size();
    gridCells_.clear();
    int32_t row = 0;
    for (auto height : rows) {
        int32_t col = 0;
        for (auto width : cols) {
            gridCells_[row][col] = Size(width, height);
            ++col;
        }
        ++row;
    }
    UpdateAccessibilityAttr();
    LOGD("GridLayout: %{public}lf %{public}lf %{public}d %{public}d", colSize_, rowSize_, colCount_, rowCount_);
}

void RenderGridLayout::UpdateAccessibilityAttr()
{
    auto refPtr = accessibilityNode_.Upgrade();
    if (!refPtr) {
        LOGE("GetAccessibilityNode failed.");
        return;
    }
    auto collectionInfo = refPtr->GetCollectionInfo();
    collectionInfo.rows = rowCount_;
    collectionInfo.columns = colCount_;
    refPtr->SetCollectionInfo(collectionInfo);
}

// Support five ways below:
// (1) 50px 100px 60px
// (2) 1fr 1fr 2fr
// (3) 30% 20% 50%
// (4) repeat(2,100px 20%) -- will be prebuild by JS Engine to --- 100px 20% 100px 20%
// (5) repeat(auto-fill, 100px 300px)  -- will be prebuild by JS Engine to --- auto-fill 100px 300px
std::vector<double> RenderGridLayout::ParseArgs(const std::string& agrs, double size, double gap)
{
    std::vector<double> lens;
    if (agrs.empty()) {
        return lens;
    }
    double pxSum = 0.0; // First priority: such as 50px
    double peSum = 0.0; // Second priority: such as 20%
    double frSum = 0.0; // Third priority: such as 2fr
    std::vector<std::string> strs;
    std::string handledArg = agrs;
    ConvertRepeatArgs(handledArg);
    StringUtils::StringSpliter(handledArg, ' ', strs);
    if (!strs.empty() && strs[0] == UNIT_AUTO_FILL) {
        return ParseAutoFill(strs, size, gap);
    }
    // first loop calculate all type sums.
    for (auto str : strs) {
        if (str.find(UNIT_PIXEL) != std::string::npos) {
            pxSum += StringUtils::StringToDouble(str);
        } else if (str.find(UNIT_PERCENT) != std::string::npos) {
            peSum += StringUtils::StringToDouble(str);
        } else if (str.find(UNIT_RATIO) != std::string::npos) {
            frSum += StringUtils::StringToDouble(str);
        } else {
            LOGE("Unsupported type: %{public}s, and use 0.0", str.c_str());
        }
    }
    if (GreatOrEqual(peSum, FULL_PERCENT)) {
        peSum = FULL_PERCENT;
    }
    // Second loop calculate actual width or height.
    double sizeLeft = size - (strs.size() - 1) * gap;
    double prSumLeft = FULL_PERCENT;
    double frSizeSum = size * (FULL_PERCENT - peSum) / FULL_PERCENT - (strs.size() - 1) * gap - pxSum;
    for (const auto& str : strs) {
        double num = StringUtils::StringToDouble(str);
        if (str.find(UNIT_PIXEL) != std::string::npos) {
            lens.push_back(sizeLeft < 0.0 ? 0.0 : std::clamp(num, 0.0, sizeLeft));
            sizeLeft -= num;
        } else if (str.find(UNIT_PERCENT) != std::string::npos) {
            num = prSumLeft < num ? prSumLeft : num;
            auto prSize = size * num / FULL_PERCENT;
            lens.push_back(prSize);
            prSumLeft -= num;
            sizeLeft -= prSize;
        } else if (str.find(UNIT_RATIO) != std::string::npos) {
            lens.push_back(NearZero(frSum) ? 0.0 : frSizeSum / frSum * num);
        } else {
            lens.push_back(0.0);
        }
    }
    return lens;
}

void RenderGridLayout::ConvertRepeatArgs(std::string& handledArg)
{
    if (handledArg.find(REPEAT_PREFIX) == std::string::npos) {
        return;
    }
    handledArg.erase(0, handledArg.find_first_not_of(" ")); // trim the input str
    std::smatch matches;
    if (handledArg.find(UNIT_AUTO_FILL) != std::string::npos) {
        if (handledArg.size() > REPEAT_MIN_SIZE && std::regex_match(handledArg, matches, AUTO_REGEX)) {
            handledArg = matches[1].str() + matches[2].str();
        }
    } else {
        if (handledArg.size() > REPEAT_MIN_SIZE && std::regex_match(handledArg, matches, REPEAT_NUM_REGEX)) {
            auto count = StringUtils::StringToInt(matches[1].str());
            handledArg = matches[2].str();
            while (count > 1) {
                handledArg.append(matches[2].str());
                --count;
            }
        }
    }
}

std::vector<double> RenderGridLayout::ParseAutoFill(const std::vector<std::string>& strs, double size, double gap)
{
    std::vector<double> lens;
    if (strs.size() <= 1) {
        return lens;
    }
    auto allocatedSize = size - (strs.size() - 2) * gap; // size() - 2 means 'auto-fill' should be erased.
    double pxSum = 0.0;
    double peSum = 0.0;
    for (const auto& str : strs) {
        auto num = StringUtils::StringToDouble(str);
        if (str.find(UNIT_PIXEL) != std::string::npos) {
            num = pxSum > allocatedSize ? 0.0 : num;
            pxSum += num;
            lens.emplace_back(num);
        } else if (str.find(UNIT_PERCENT) != std::string::npos) {
            // adjust invalid percent
            num = peSum >= FULL_PERCENT ? 0.0 : num;
            peSum += num;
            pxSum += num / FULL_PERCENT * size;
            lens.emplace_back(num / FULL_PERCENT * size);
        } else {
            LOGD("Unsupported type: %{public}s, and use 0.0", str.c_str());
        }
    }
    allocatedSize -= pxSum;
    if (LessOrEqual(allocatedSize, 0.0)) {
        return lens;
    }
    pxSum += lens.size() * gap;
    int32_t repeatCount = allocatedSize / pxSum;
    std::vector<double> newLens;
    for (int32_t i = 0; i < repeatCount + 1; i++) {
        newLens.insert(newLens.end(), lens.begin(), lens.end());
    }
    allocatedSize -= pxSum * repeatCount;
    for (auto lenIter = lens.begin(); lenIter != lens.end(); lenIter++) {
        allocatedSize -= *lenIter + gap;
        if (LessNotEqual(allocatedSize, 0.0)) {
            break;
        }
        newLens.emplace_back(*lenIter);
    }
    return newLens;
}

void RenderGridLayout::SetItemIndex(const RefPtr<RenderNode>& child, int32_t index)
{
    int32_t depth = DEFAULT_DEPTH;
    auto item = child;
    auto gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
    while (!gridLayoutItem && depth > 0) {
        if (!item || item->GetChildren().empty()) {
            return;
        }
        item = item->GetChildren().front();
        gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
        --depth;
    }
    if (gridLayoutItem) {
        gridLayoutItem->SetIndex(index);
    }
}

int32_t RenderGridLayout::GetItemRowIndex(const RefPtr<RenderNode>& child) const
{
    int32_t depth = DEFAULT_DEPTH;
    int32_t rowIndex = -1;
    auto item = child;
    auto gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
    while (!gridLayoutItem && depth > 0) {
        if (!item || item->GetChildren().empty()) {
            return rowIndex;
        }
        item = item->GetChildren().front();
        gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
        --depth;
    }
    if (gridLayoutItem) {
        rowIndex = gridLayoutItem->GetRowIndex();
    }
    return rowIndex;
}

int32_t RenderGridLayout::GetItemColumnIndex(const RefPtr<RenderNode>& child) const
{
    int32_t depth = DEFAULT_DEPTH;
    int32_t columnIndex = -1;
    auto item = child;
    auto gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
    while (!gridLayoutItem && depth > 0) {
        if (!item || item->GetChildren().empty()) {
            return columnIndex;
        }
        item = item->GetChildren().front();
        gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
        --depth;
    }
    if (gridLayoutItem) {
        columnIndex = gridLayoutItem->GetColumnIndex();
    }
    return columnIndex;
}

int32_t RenderGridLayout::GetItemSpan(const RefPtr<RenderNode>& child, bool isRow) const
{
    int32_t depth = DEFAULT_DEPTH;
    int32_t span = -1;
    auto item = child;
    auto gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
    while (!gridLayoutItem && depth > 0) {
        if (!item || item->GetChildren().empty()) {
            return span;
        }
        item = item->GetChildren().front();
        gridLayoutItem = AceType::DynamicCast<RenderGridLayoutItem>(item);
        --depth;
    }
    if (gridLayoutItem) {
        span = isRow ? gridLayoutItem->GetRowSpan() : gridLayoutItem->GetColumnSpan();
    }
    return span < 1 ? 1 : span;
}

void RenderGridLayout::GetNextGird(int32_t& curRow, int32_t& curCol) const
{
    if (isVertical_) {
        ++curCol;
        if (curCol >= colCount_) {
            curCol = 0;
            ++curRow;
        }
    } else {
        ++curRow;
        if (curRow >= rowCount_) {
            curRow = 0;
            ++curCol;
        }
    }
}

bool RenderGridLayout::CheckGridPlaced(int32_t index, int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan)
{
    auto rowIter = gridMatrix_.find(row);
    if (rowIter != gridMatrix_.end()) {
        auto colIter = rowIter->second.find(col);
        if (colIter != rowIter->second.end()) {
            return false;
        }
    }
    rowSpan = std::min(rowCount_ - row, rowSpan);
    colSpan = std::min(colCount_ - col, colSpan);
    int32_t rSpan = 0;
    int32_t cSpan = 0;
    int32_t retColSpan = 1;
    while (rSpan < rowSpan) {
        rowIter = gridMatrix_.find(rSpan + row);
        if (rowIter != gridMatrix_.end()) {
            cSpan = 0;
            while (cSpan < colSpan) {
                if (rowIter->second.find(cSpan + col) != rowIter->second.end()) {
                    colSpan = cSpan;
                    break;
                }
                ++cSpan;
            }
        } else {
            cSpan = colSpan;
        }
        if (retColSpan > cSpan) {
            break;
        }
        retColSpan = cSpan;
        ++rSpan;
    }
    rowSpan = rSpan;
    colSpan = retColSpan;
    for (int32_t i = row; i < row + rowSpan; ++i) {
        std::map<int32_t, int32_t> rowMap;
        auto iter = gridMatrix_.find(i);
        if (iter != gridMatrix_.end()) {
            rowMap = iter->second;
        }
        for (int32_t j = col; j < col + colSpan; ++j) {
            rowMap.emplace(std::make_pair(j, index));
        }
        gridMatrix_[i] = rowMap;
    }
    LOGD("%{public}d %{public}d %{public}d %{public}d %{public}d", index, row, col, rowSpan, colSpan);
    return true;
}

void RenderGridLayout::PerformLayout()
{
    if (GetChildren().empty()) {
        return;
    }
    // Initialize the the grid layout prop
    gridMatrix_.clear();
    InitialGridProp();
    int32_t rowIndex = 0;
    int32_t colIndex = 0;
    int32_t itemIndex = 0;
    for (const auto& item : GetChildren()) {
        int32_t itemRow = GetItemRowIndex(item);
        int32_t itemCol = GetItemColumnIndex(item);
        int32_t itemRowSpan = GetItemSpan(item, true);
        int32_t itemColSpan = GetItemSpan(item, false);
        if (itemRow >= 0 && itemRow < rowCount_ && itemCol >= 0 && itemCol < colCount_ &&
            CheckGridPlaced(itemIndex, itemRow, itemCol, itemRowSpan, itemColSpan)) {
            item->Layout(MakeInnerLayoutParam(itemRow, itemCol, itemRowSpan, itemColSpan));
            SetChildPosition(item, itemRow, itemCol, itemRowSpan, itemColSpan);
        } else {
            while (!CheckGridPlaced(itemIndex, rowIndex, colIndex, itemRowSpan, itemColSpan)) {
                GetNextGird(rowIndex, colIndex);
                if (rowIndex >= rowCount_ || colIndex >= colCount_) {
                    break;
                }
            }
            if (rowIndex >= rowCount_ || colIndex >= colCount_) {
                DisableChild(item, itemIndex);
                continue;
            }
            item->Layout(MakeInnerLayoutParam(rowIndex, colIndex, itemRowSpan, itemColSpan));
            SetChildPosition(item, rowIndex, colIndex, itemRowSpan, itemColSpan);
        }
        SetItemIndex(item, itemIndex); // Set index for focus adjust.
        ++itemIndex;
        LOGD("%{public}d %{public}d %{public}d %{public}d", rowIndex, colIndex, itemRowSpan, itemColSpan);
    }
    SetLayoutSize(GetLayoutParam().Constrain(Size(colSize_, rowSize_)));
}

} // namespace OHOS::Ace
