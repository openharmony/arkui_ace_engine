/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_fill_algorithm.h"

#include "irregular/grid_layout_range_solver.h"

#include "base/geometry/axis.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void GridFillAlgorithm::PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt)
{
    Init(viewport, axis, totalCnt);
}
void GridFillAlgorithm::Init(const SizeF& viewport, Axis axis, int32_t totalCnt)
{
    params_.mainGap = GridUtils::GetMainGap(props_, viewport, axis);

    std::string args = (axis == Axis::VERTICAL ? props_.GetColumnsTemplate() : props_.GetRowsTemplate()).value_or("");
    auto res = ParseTemplateArgs(
        GridUtils::ParseArgs(args), viewport.CrossSize(axis), GridUtils::GetCrossGap(props_, viewport, axis), totalCnt);

    params_.crossLens = std::vector<float>(res.first.begin(), res.first.end());
    params_.crossGap = static_cast<float>(res.second);
    if (params_.crossLens.empty()) {
        params_.crossLens.push_back(viewport.CrossSize(axis));
    }

    info_.axis_ = axis;
    info_.childrenCount_ = totalCnt;

    range_.startLine = info_.startMainLineIndex_;
    range_.offset = info_.currentOffset_;
    range_.endLine = info_.endMainLineIndex_;
    if (range_.startLine == 0) {
        range_.offset = std::min(range_.offset, 0.0f); // no overScroll in range estimation
    }
}

void GridFillAlgorithm::FillMarkItem(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index)
{
    FillNext(viewport, axis, node, index);
    if (resetRangeOnJump_) {
        range_.startLine = range_.endLine = info_.GetItemPos(index).second;
        resetRangeOnJump_ = false;
    }
}

namespace {
void MeasureItem(GridIrregularFiller& filler, const GridIrregularFiller::FillParameters& params, FrameNode* node,
    int32_t index, int32_t col, int32_t row)
{
    filler.MeasureItem(params, node, index, col, row);
    // clean flag to prevent remeasure in LayoutTask
    node->GetLayoutProperty()->CleanDirty();
    node->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
}
} // namespace

void GridFillAlgorithm::FillNext(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index)
{
    GridIrregularFiller filler(&info_, props_.GetHost().GetRawPtr());
    filler.FillMatrixOnly(index);
    const auto pos = info_.GetItemPos(index);
    if (!node->CheckNeedForceMeasureAndLayout() && info_.lineHeightMap_.count(pos.second)) {
        return;
    }
    MeasureItem(filler, params_, node, index, pos.first, pos.second);
}

void GridFillAlgorithm::FillPrev(const SizeF& viewport, Axis axis, FrameNode* node, int32_t index)
{
    if (!node->CheckNeedForceMeasureAndLayout()) {
        return;
    }
    // matrix is ready
    GridIrregularFiller filler(&info_, props_.GetHost().GetRawPtr());
    const auto pos = info_.GetItemPos(index);
    MeasureItem(filler, params_, node, index, pos.first, pos.second);
}

bool GridFillAlgorithm::CanFillMore(Axis axis, const SizeF& scrollWindowSize, int32_t idx, FillDirection direction)
{
    auto [col, row] = info_.GetItemPos(idx);
    if (idx < 0) {
        row = direction == FillDirection::START ? range_.startLine : range_.endLine + 1;
        col = 0;
    }
    if (row == -1 || col == -1) {
        LOGW("grid matrix is corrupted");
        return false;
    }
    if (col > 0) {
        // always fill by full lines
        return true;
    }
    if (direction == FillDirection::START) {
        if (row > range_.startLine) {
            return true;
        }
        range_.AdjustBackward(info_.lineHeightMap_, params_.mainGap, row);
        return GreatNotEqual(range_.offset, params_.mainGap);
    }

    range_.endLine = row - 1;
    range_.AdjustForward(info_.lineHeightMap_, params_.mainGap);
    float contentHeight = info_.GetHeightInRange(range_.startLine, range_.endLine + 1, params_.mainGap) + range_.offset;
    return LessNotEqual(contentHeight, scrollWindowSize.MainSize(axis));
}

void GridFillAlgorithm::LayoutRange::AdjustBackward(
    const decltype(info_.lineHeightMap_)& lineHeights, float gap, int32_t firstRow)
{
    while (startLine > firstRow && GreatNotEqual(offset, gap)) {
        auto height = lineHeights.find(--startLine);
        if (height == lineHeights.end()) {
            LOGW("line heights data is corrupted");
            break;
        }
        offset -= height->second + gap;
    }
}

void GridFillAlgorithm::LayoutRange::AdjustForward(const decltype(info_.lineHeightMap_)& lineHeights, float gap)
{
    while (startLine <= endLine) {
        auto height = lineHeights.find(startLine);
        if (height == lineHeights.end()) {
            LOGW("line heights data is corrupted");
            break;
        }
        if (LessOrEqual(-offset, height->second + gap)) {
            break;
        }
        offset += height->second + gap;
        ++startLine;
    }
}
void GridFillAlgorithm::OnSlidingOffsetUpdate(float delta)
{
    range_.offset += delta;
    if (range_.startLine == 0) {
        range_.offset = std::min(range_.offset, 0.0f);
    }
}

bool GridFillAlgorithm::OnSlidingOffsetUpdate(const SizeF& viewport, Axis axis, float delta)
{
    // update range
    auto prevRange = std::pair { range_.startIdx, range_.endIdx };
    range_.startLine = info_.startMainLineIndex_;
    range_.endLine = info_.endMainLineIndex_;
    range_.offset = info_.currentOffset_;
    GridLayoutRangeSolver solver(&info_, props_.GetHost().GetRawPtr());
    if (Positive(range_.offset)) {
        auto res = solver.FindStartingRow(params_.mainGap);
        range_.startIdx = res.idx;
        range_.startLine = res.row;
        range_.offset = res.pos;

        auto [endLine, endIdx] =
            solver.SolveForwardForEndIdx(params_.mainGap, viewport.MainSize(axis) - res.pos, res.row);
        range_.endLine = endLine;
        range_.endIdx = endIdx;
        return prevRange != std::pair(range_.startIdx, range_.endIdx);
    }

    float heightToFill = viewport.MainSize(axis) - info_.currentOffset_ -
                         info_.GetHeightInRange(range_.startLine, range_.endLine, params_.mainGap);
    GridIrregularFiller filler(&info_, props_.GetHost().GetRawPtr());
    constexpr float LINE_HEIGHT = 450.0f;
    while (Positive(heightToFill)) {
        filler.FillMatrixByLine(range_.endLine, ++range_.endLine);
        heightToFill -= LINE_HEIGHT;
        info_.lineHeightMap_[range_.endLine - 1] = LINE_HEIGHT;
    }

    auto solveRes = solver.FindStartingRow(params_.mainGap);
    range_.startLine = solveRes.row;
    range_.offset = solveRes.pos;
    range_.startIdx = solveRes.idx;
    auto [endMainLineIdx, endIdx] =
        solver.SolveForwardForEndIdx(params_.mainGap, viewport.MainSize(axis) - solveRes.pos, solveRes.row);
    range_.endLine = endMainLineIdx;
    range_.endIdx = endIdx;
    return prevRange != std::pair(range_.startIdx, range_.endIdx);
}
} // namespace OHOS::Ace::NG