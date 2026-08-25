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
        // With startFixOffset_ > 0 (contentClip extension), items above the start line that
        // fit in the clip extension area should be included. Use SolveBackward to find the
        // new start line, matching the currentOffset_ > 0 branch below. When startFixOffset_
        // == 0 (CONTENT_ONLY) or no items above exist, fall back to the original behavior.
        // The lineHeightMap_ check guards against layouts that don't pre-measure lines above
        // (e.g., custom layout after ClearCache in JumpToTargetIndex): without it, SolveBackward
        // returns {0, 0, 0} on missing entries and corrupts the visible range.
        if (GreatNotEqual(info_->startFixOffset_, 0.0f) && info_->startMainLineIndex_ > 0 &&
            info_->lineHeightMap_.find(info_->startMainLineIndex_ - 1) != info_->lineHeightMap_.end()) {
            auto res = SolveBackward(mainGap, info_->startFixOffset_, info_->startMainLineIndex_);
            res.pos -= info_->startFixOffset_;
            return res;
        }
        return { info_->startMainLineIndex_, info_->startIndex_, 0.0f };
    }
    if (Negative(info_->currentOffset_)) {
        // With startFixOffset_ > 0 (contentClip extension), use SkipLinesAboveView which
        // accounts for the clip start bound. When startFixOffset_ == 0 (CONTENT_ONLY),
        // fall back to SolveForward to preserve the exact original boundary behavior.
        if (GreatNotEqual(info_->startFixOffset_, 0.0f)) {
            auto res = SolveForwardWithExtension(mainGap);
            if (res.has_value()) {
                return res.value();
            }
        }
        return SolveForward(mainGap, -info_->currentOffset_, info_->startMainLineIndex_);
    }
    // currentOffset_ > 0: blank at start. With startFixOffset_ > 0, the blank can extend into the
    // clip extension area (down to -startFixOffset_), so increase targetLen by startFixOffset_ and
    // correct the returned offset. When startFixOffset_ == 0, both adjustments are no-ops.
    // The lineHeightMap_ check guards against layouts that don't pre-measure lines above
    // (same rationale as the NearZero branch above).
    if (GreatNotEqual(info_->startFixOffset_, 0.0f) && info_->startMainLineIndex_ > 0 &&
        info_->lineHeightMap_.find(info_->startMainLineIndex_ - 1) != info_->lineHeightMap_.end()) {
        auto res = SolveBackward(mainGap, info_->currentOffset_ + info_->startFixOffset_, info_->startMainLineIndex_);
        res.pos -= info_->startFixOffset_;
        return res;
    }
    return SolveBackward(mainGap, info_->currentOffset_, info_->startMainLineIndex_);
}

std::optional<GridLayoutRangeSolver::StartingRowInfo> GridLayoutRangeSolver::SolveForwardWithExtension(float mainGap)
{
    auto [it, offset] = info_->SkipLinesAboveView(mainGap);
    if (it == info_->lineHeightMap_.end()) {
        return std::nullopt;
    }
    // Extend backward to include lines visible in the start contentClip extension area.
    // SkipLinesAboveView only goes forward from startMainLineIndex_; when scrolling upward,
    // lines above startMainLineIndex_ become visible in the extension area (top padding region
    // when contentClip = BOUNDARY). Without this backward walk, those lines are never included
    // in the visible range, so their items are not laid out every frame.
    // A previous line is visible if its bottom (currOffset - mainGap) is at or below the clip
    // start bound (-startFixOffset_), mirroring the SkipLinesAboveView visibility test.
    // When startFixOffset_ == 0 (CONTENT_ONLY), the condition is never satisfied (the clip
    // start is 0, and offset - mainGap < 0 always holds for a line above), so the backward walk
    // is a no-op, preserving the original behavior.
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
            // Use GetViewEndBound so the end extension (endFixOffset_) is filled on jump.
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
    float len = 0.0f;
    auto it = info_->lineHeightMap_.find(line);
    if (it == info_->lineHeightMap_.end()) {
        return { -1, -1 };
    }

    for (; LessNotEqual(len, targetLen) && it != info_->lineHeightMap_.end(); ++it) {
        len += it->second + mainGap;
    }
    --it;
    return { it->first, info_->FindEndIdx(it->first).itemIdx };
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
