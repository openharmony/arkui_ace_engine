/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"

#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"

namespace OHOS::Ace::NG {
GridLayoutRangeSolver::GridLayoutRangeSolver(GridLayoutInfo* info, LayoutWrapper* wrapper)
    : info_(info), wrapper_(wrapper)
{
    auto props = AceType::DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    opts_ = &props->GetLayoutOptions().value();
};

using Result = GridLayoutRangeSolver::StartingRowInfo;
Result GridLayoutRangeSolver::FindStartingRow(float mainGap)
{
    if (info_->gridMatrix_.empty() || info_->lineHeightMap_.empty()) {
        return { 0, 0, 0.0f };
    }
    if (NearZero(info_->currentOffset_)) {
        // With the start extension active, rows visible in the start extension
        // must join the starting row too (fix #1/#3: the original code returned
        // only the current start, leaving extension rows out of layout). The
        // guard must cover SolveBackward's whole backward span (M-1): checking
        // only startMainLineIndex_-1 lets an upward walk of more than one row hit
        // a missing lineHeightMap_ entry, making SolveBackward silently return
        // {0,0,0} and the visible range jump back to item 0. With
        // startFixOffset_ == 0 the condition fails and the original behavior
        // is returned.
        if (GreatNotEqual(info_->startFixOffset_, 0.0f) && info_->startMainLineIndex_ > 0 &&
            CanSolveBackwardSpan(mainGap, info_->startFixOffset_, info_->startMainLineIndex_)) {
            auto res = SolveBackward(mainGap, info_->startFixOffset_, info_->startMainLineIndex_);
            res.pos -= info_->startFixOffset_;
            return res;
        }
        return { info_->startMainLineIndex_, info_->startIndex_, 0.0f };
    }
    if (Negative(info_->currentOffset_)) {
        // With the start extension active, first use SkipLinesAboveView to skip
        // rows above the content-area top (0) — its reference is the content-area
        // top, not the clip start — then the upward walk inside
        // SolveForwardWithExtension includes newly visible rows in the start
        // extension area (between the clip start -startFixOffset_ and the
        // content-area top). With startFixOffset_ == 0 fall back to
        // SolveForward.
        if (GreatNotEqual(info_->startFixOffset_, 0.0f)) {
            auto res = SolveForwardWithExtension(mainGap);
            if (res.has_value()) {
                return res.value();
            }
        }
        return SolveForward(mainGap, -info_->currentOffset_, info_->startMainLineIndex_);
    }
    // currentOffset_ > 0: blank at the top. When the extension is active the
    // blank can extend to the clip start, at minus startFixOffset_. TargetLen
    // gains startFixOffset_ and the returned offset is corrected. Both corrections are
    // no-ops when startFixOffset_ == 0. Backward-span guard as in the NearZero
    // branch (M-1): on guard failure fall back to the baseline SolveBackward
    // (no extension correction).
    if (GreatNotEqual(info_->startFixOffset_, 0.0f) && info_->startMainLineIndex_ > 0 &&
        CanSolveBackwardSpan(mainGap, info_->currentOffset_ + info_->startFixOffset_,
            info_->startMainLineIndex_)) {
        auto res = SolveBackward(mainGap, info_->currentOffset_ + info_->startFixOffset_, info_->startMainLineIndex_);
        res.pos -= info_->startFixOffset_;
        return res;
    }
    return SolveBackward(mainGap, info_->currentOffset_, info_->startMainLineIndex_);
}

bool GridLayoutRangeSolver::CanSolveBackwardSpan(float mainGap, float targetLen, int32_t idx) const
{
    // Mirror SolveBackward's accumulation exactly (len starts at mainGap) and
    // verify lineHeightMap_ has every entry in the backward span down to row
    // zero, returning false on the first missing entry so the caller falls back
    // to the baseline path without the extension correction.
    float len = mainGap;
    while (idx > 0 && LessNotEqual(len, targetLen)) {
        auto it = info_->lineHeightMap_.find(--idx);
        if (it == info_->lineHeightMap_.end()) {
            return false;
        }
        len += it->second + mainGap;
    }
    return true;
}

std::optional<GridLayoutRangeSolver::StartingRowInfo> GridLayoutRangeSolver::SolveForwardWithExtension(float mainGap)
{
    auto [it, offset] = info_->SkipLinesAboveView(mainGap);
    if (it == info_->lineHeightMap_.end()) {
        return std::nullopt;
    }
    // Walk backward from the found row to include rows that became visible in
    // the start extension while scrolling up: the previous row's bottom edge
    // (offset - mainGap) is visible once it is below the clip start
    // (-startFixOffset_). With startFixOffset_ == 0 the condition never holds
    // (the row above has offset - mainGap < 0), so the walk is a no-op.
    auto currIt = it;
    auto currOffset = offset;
    while (currIt != info_->lineHeightMap_.begin()) {
        auto prevIt = std::prev(currIt);
        if (Negative(currOffset - mainGap + info_->startFixOffset_)) {
            break;
        }
        currOffset -= prevIt->second + mainGap;
        currIt = prevIt;
    }
    auto [startRow, startIdx] = CheckMultiRow(currIt->first);
    if (startRow < 0 || startIdx < 0) {
        // gridMatrix_ lacks the current row (M-2): CheckMultiRow returns
        // {-1,-1}. Feeding that into the backtrack loop would treat startRow=-1
        // as a multi-row item start, subtract every height above (extreme
        // negative pos) and leak -1 indices into the visible range. Degrade to
        // the current row itself without the multi-row backtrack.
        return StartingRowInfo { currIt->first, info_->startIndex_, currOffset };
    }
    for (int32_t i = currIt->first; i > startRow; --i) {
        auto prevIt = info_->lineHeightMap_.find(i - 1);
        if (prevIt != info_->lineHeightMap_.end()) {
            currOffset -= prevIt->second + mainGap;
        }
    }
    return StartingRowInfo { startRow, startIdx, currOffset };
}

using RangeInfo = GridLayoutRangeSolver::RangeInfo;
RangeInfo GridLayoutRangeSolver::FindRangeOnJump(int32_t jumpIdx, int32_t jumpLineIdx, float mainGap)
{
    auto mainSize = wrapper_->GetGeometryNode()->GetContentSize().MainSize(info_->axis_);
    /*
    Notice that  finding the first line in ScrollAlign::END is the same as having the jumpLine matching the top of the
    viewport and applying a positive whole-page offset, so we can directly use SolveBackward. But for
    ScrollAlign::START, we have to change SolveForward a bit to find the ending row.
    */
    switch (info_->scrollAlign_) {
        case ScrollAlign::START: {
            auto [startRow, startIdx] = CheckMultiRow(jumpLineIdx);
            float offset = -info_->GetHeightInRange(startRow, jumpLineIdx, mainGap);
            // Use GetViewEndBound so the end extension area (endFixOffset_) is
            // also filled on jumps. Degenerates to mainSize when
            // endFixOffset_ == 0, matching the original behavior.
            auto [endLineIdx, endIdx] = SolveForwardForEndIdx(
                mainGap, info_->GetViewEndBound(mainSize) - info_->contentStartOffset_, jumpLineIdx);
            return { startRow, startIdx, offset, endLineIdx, endIdx };
        }
        case ScrollAlign::CENTER: {
            // align by item center
            auto size = GridLayoutUtils::GetItemSize(info_, wrapper_, jumpIdx);
            const auto [centerLine, offset] = info_->FindItemCenter(jumpLineIdx, size.rows, mainGap);
            const float halfMainSize = mainSize / 2.0f;
            auto [endLineIdx, endIdx] = SolveForwardForEndIdx(mainGap, halfMainSize + offset, centerLine);
            auto res = SolveBackward(mainGap, halfMainSize - offset, centerLine);
            return { res.row, res.idx, res.pos, endLineIdx, endIdx };
        }
        case ScrollAlign::END: {
            auto it = info_->lineHeightMap_.find(jumpLineIdx);
            if (it == info_->lineHeightMap_.end()) {
                TAG_LOGW(AceLogTag::ACE_GRID, "line height at %{public}d not prepared during jump", jumpLineIdx);
                return {};
            }
            Result res;
            if (jumpLineIdx == info_->lineHeightMap_.rbegin()->first) {
                res = SolveBackward(mainGap, mainSize - it->second - info_->contentEndOffset_, jumpLineIdx);
            } else {
                res = SolveBackward(mainGap, mainSize - it->second, jumpLineIdx);
            }
            return { res.row, res.idx, res.pos, jumpLineIdx, info_->FindEndIdx(jumpLineIdx).itemIdx };
        }
        default:
            return {};
    }
}

Result GridLayoutRangeSolver::SolveForward(float mainGap, float targetLen, const int32_t idx)
{
    float len = -mainGap;
    auto it = info_->lineHeightMap_.find(idx);
    for (; it != info_->lineHeightMap_.end(); ++it) {
        if (GreatNotEqual(len + it->second + mainGap, targetLen)) {
            break;
        }
        len += it->second + mainGap;
    }
    if (it == info_->lineHeightMap_.end()) {
        len -= (--it)->second + mainGap;
    }
    auto [startRow, startIdx] = CheckMultiRow(it->first);
    for (int32_t i = it->first; i > startRow; --i) {
        if (it == info_->lineHeightMap_.begin()) {
            TAG_LOGW(AceLogTag::ACE_GRID,
                "lineHeightMap_ front rows cleared before row %{public}d, startRow %{public}d, stop backtracking",
                it->first, startRow);
            break;
        }
        --it;
        len -= it->second + mainGap;
    }
    return { startRow, startIdx, len - targetLen + mainGap };
}

std::pair<int32_t, int32_t> GridLayoutRangeSolver::SolveForwardForEndIdx(float mainGap, float targetLen, int32_t line)
{
    if (Negative(targetLen)) {
        return { -1, -1 };
    }
    auto it = info_->lineHeightMap_.find(line);
    if (it == info_->lineHeightMap_.end()) {
        return { -1, -1 };
    }

    // lineHeightMap_ can be discontinuous: a bottom-edge jump fills the whole
    // matrix but measures only the view heights, and a later top-edge jump
    // re-measures from the top, leaving a hole between the measured ranges.
    // Map-order iteration would silently skip the hole and treat stale
    // far-away lines as adjacent, returning an end line inside the unmeasured
    // hole (the range then fails UpdateLayoutInfo's height validity check).
    // This is a bugfix over the original map-order walk, which was only
    // correct under a fully consecutive map. Walk consecutive line numbers
    // and stop at the first missing entry; the following fill passes extend
    // the measured range from there.
    float len = it->second + mainGap;
    int32_t endLine = line;
    for (int32_t next = line + 1; LessNotEqual(len, targetLen); ++next) {
        auto nextIt = info_->lineHeightMap_.find(next);
        if (nextIt == info_->lineHeightMap_.end()) {
            break;
        }
        len += nextIt->second + mainGap;
        endLine = next;
    }
    return { endLine, info_->FindEndIdx(endLine).itemIdx };
}

Result GridLayoutRangeSolver::SolveBackward(float mainGap, float targetLen, int32_t idx)
{
    float len = mainGap;
    while (idx > 0 && LessNotEqual(len, targetLen)) {
        auto it = info_->lineHeightMap_.find(--idx);
        if (it == info_->lineHeightMap_.end()) {
            return { 0, 0, 0.0f };
        }
        len += it->second + mainGap;
    }

    auto [startLine, startItem] = CheckMultiRow(idx);
    float newOffset = targetLen - len + mainGap;
    newOffset -= info_->GetHeightInRange(startLine, idx, mainGap);
    return { startLine, startItem, newOffset };
}

namespace {
int32_t FindItemStartRow(const GridLayoutInfo& info, int32_t startRow, int32_t colIdx)
{
    int32_t r = startRow;
    while (r > 0) {
        auto rowIt = info.gridMatrix_.find(r);
        if (rowIt == info.gridMatrix_.end() || rowIt->second.empty()) {
            break;
        }
        auto colIt = rowIt->second.find(colIdx);
        if (colIt == rowIt->second.end() || colIt->second >= 0) {
            break;
        }
        --r;
    }
    return r;
}
}

void GridLayoutRangeSolver::UpdateStartItemForMultiRow(const std::map<int32_t, int32_t>& row,
    int32_t colIdx, const std::map<int32_t, int32_t>::const_iterator& colIt, int32_t currentRowIdx,
    int32_t& startLine, int32_t& startItem) const
{
    auto currentColIt = row.find(std::max(colIdx - 1, 0));
    bool isCurrentRow = (currentColIt != row.end() && currentColIt->second == -colIt->second);
    if (isCurrentRow) {
        // current row contain startItem
        startItem = -colIt->second;
        return;
    }

    int32_t firstRow = FindItemStartRow(*info_, currentRowIdx, colIdx);
    if (firstRow < startLine) {
        startLine = firstRow;
        startItem = -colIt->second;
    }
}

std::pair<int32_t, int32_t> GridLayoutRangeSolver::CheckMultiRow(const int32_t idx)
{
    auto rowIt = info_->gridMatrix_.find(idx);
    if (rowIt == info_->gridMatrix_.end() || rowIt->second.empty()) {
        return { -1, -1 };
    }

    const auto& row = rowIt->second;
    int32_t startLine = idx;
    int32_t startItem = row.begin()->second;

    for (int32_t c = 0; c < info_->crossCount_; ++c) {
        auto colIt = row.find(c);
        if (colIt == row.end()) {
            continue;
        }

        if (colIt->second == 0) {
            return { 0, 0 };
        }

        if (colIt->second < 0) {
            UpdateStartItemForMultiRow(row, c, colIt, idx, startLine, startItem);
        }

        const int32_t itemIdx = info_->GetOriginalIndex(std::abs(colIt->second));
        if (opts_->irregularIndexes.find(itemIdx) != opts_->irregularIndexes.end()) {
            if (opts_->getSizeByIndex) {
                auto size = opts_->getSizeByIndex(itemIdx);
                size.columns = std::max(1, size.columns);
                size.rows = std::max(1, size.rows);
                c += (info_->axis_ == Axis::VERTICAL ? size.columns : size.rows) - 1;
            } else {
                break;
            }
        }
    }
    return { startLine, startItem };
}
} // namespace OHOS::Ace::NG
