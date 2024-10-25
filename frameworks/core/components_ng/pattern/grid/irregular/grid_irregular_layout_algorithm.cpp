/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"

#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void GridIrregularLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    if (info_.childrenCount_ <= 0) {
        return;
    }
    wrapper_ = layoutWrapper;
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());

    float mainSize = MeasureSelf(props);
    Init(props);

    if (info_.targetIndex_) {
        MeasureToTarget();
        info_.targetIndex_.reset();
    }

    if (info_.jumpIndex_ != EMPTY_JUMP_INDEX) {
        MeasureOnJump(mainSize);
    } else {
        MeasureOnOffset(mainSize);
    }

    if (props->GetAlignItems().value_or(GridItemAlignment::DEFAULT) == GridItemAlignment::STRETCH) {
        GridLayoutBaseAlgorithm::AdjustChildrenHeight(layoutWrapper);
    }

    UpdateLayoutInfo();
    const int32_t cacheCnt = props->GetCachedCountValue(1) * info_.crossCount_;
    if (props->GetShowCachedItemsValue(false)) {
        SyncPreloadItems(cacheCnt);
    } else {
        PreloadItems(cacheCnt);
    }
}

void GridIrregularLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    const auto& info = info_;
    if (info.childrenCount_ <= 0) {
        return;
    }
    wrapper_ = layoutWrapper;
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    CHECK_NULL_VOID(props);

    LayoutChildren(info.currentOffset_, props->GetCachedCountValue(1));

    const int32_t cacheCnt = props->GetCachedCountValue(1) * info.crossCount_;
    wrapper_->SetActiveChildRange(std::min(info.startIndex_, info.endIndex_), info.endIndex_, cacheCnt, cacheCnt,
        props->GetShowCachedItemsValue(false));
    wrapper_->SetCacheCount(cacheCnt);
}

float GridIrregularLayoutAlgorithm::MeasureSelf(const RefPtr<GridLayoutProperty>& props)
{
    // set self size
    auto size = CreateIdealSize(props->GetLayoutConstraint().value(), info_.axis_, props->GetMeasureType(), true);
    wrapper_->GetGeometryNode()->SetFrameSize(size);

    // set content size
    const auto& padding = props->CreatePaddingAndBorder();
    wrapper_->GetGeometryNode()->UpdatePaddingWithBorder(padding);
    MinusPaddingToSize(padding, size);
    info_.contentEndPadding_ = ScrollableUtils::CheckHeightExpansion(props, info_.axis_);
    size.AddHeight(info_.contentEndPadding_);
    wrapper_->GetGeometryNode()->SetContentSize(size);

    return size.MainSize(info_.axis_);
}

void GridIrregularLayoutAlgorithm::Init(const RefPtr<GridLayoutProperty>& props)
{
    const auto& contentSize = wrapper_->GetGeometryNode()->GetContentSize();
    crossGap_ = GridUtils::GetCrossGap(props, contentSize, info_.axis_);
    mainGap_ = GridUtils::GetMainGap(props, contentSize, info_.axis_);

    std::string args;
    if (props->GetRowsTemplate()) {
        info_.axis_ = Axis::HORIZONTAL;
        args = props->GetRowsTemplate().value_or("");
    } else {
        info_.axis_ = Axis::VERTICAL;
        args = props->GetColumnsTemplate().value_or("");
    }

    const float crossSize = contentSize.CrossSize(info_.axis_);
    auto res = ParseTemplateArgs(GridUtils::ParseArgs(args), crossSize, crossGap_, info_.childrenCount_);

    crossLens_ = std::vector<float>(res.first.begin(), res.first.end());
    if (crossLens_.empty()) {
        crossLens_.push_back(crossSize);
    }

    crossGap_ = res.second;

    info_.crossCount_ = static_cast<int32_t>(crossLens_.size());
    CheckForReset();
}

namespace {
inline void PrepareJumpOnReset(GridLayoutInfo& info)
{
    info.jumpIndex_ = std::min(info.startIndex_, info.childrenCount_ - 1);
    info.scrollAlign_ = ScrollAlign::START;
}
inline void ResetMaps(GridLayoutInfo& info)
{
    info.gridMatrix_.clear();
    info.lineHeightMap_.clear();
}
inline void ResetLayoutRange(GridLayoutInfo& info)
{
    info.startIndex_ = 0;
    info.endIndex_ = -1;
    info.startMainLineIndex_ = 0;
    info.endMainLineIndex_ = -1;
    info.currentOffset_ = 0.0f;
    info.prevOffset_ = 0.0f;
}
} // namespace

void GridIrregularLayoutAlgorithm::CheckForReset()
{
    if (info_.IsResetted()) {
        // reset layout info_ and perform jump to current startIndex
        postJumpOffset_ = info_.currentOffset_;
        PrepareJumpOnReset(info_);
        ResetMaps(info_);
        ResetLayoutRange(info_);
        return;
    }

    int32_t updateIdx = wrapper_->GetHostNode()->GetChildrenUpdated();
    if (updateIdx != -1) {
        auto it = info_.FindInMatrix(updateIdx);
        if (it != info_.gridMatrix_.end()) {
            info_.ClearHeightsToEnd(it->first);
            info_.ClearMatrixToEnd(updateIdx, it->first);
        }
        if (updateIdx <= info_.endIndex_) {
            postJumpOffset_ = info_.currentOffset_;
            PrepareJumpOnReset(info_);
            ResetLayoutRange(info_);
        }
        wrapper_->GetHostNode()->ChildrenUpdatedFrom(-1);
        return;
    }

    if (wrapper_->GetLayoutProperty()->GetPropertyChangeFlag() & PROPERTY_UPDATE_BY_CHILD_REQUEST) {
        postJumpOffset_ = info_.currentOffset_;
        info_.lineHeightMap_.clear();
        PrepareJumpOnReset(info_);
        ResetLayoutRange(info_);
        return;
    }

    if (wrapper_->ConstraintChanged()) {
        // need to remeasure all items in current view
        postJumpOffset_ = info_.currentOffset_;
        PrepareJumpOnReset(info_);
    }
}

void GridIrregularLayoutAlgorithm::MeasureOnOffset(float mainSize)
{
    if (TrySkipping(mainSize)) {
        return;
    }

    if (GreatNotEqual(info_.currentOffset_, info_.prevOffset_)) {
        MeasureBackward(mainSize);
    } else {
        MeasureForward(mainSize);
    }
}

namespace {
inline void UpdateStartInfo(GridLayoutInfo& info, const GridLayoutRangeSolver::StartingRowInfo& res)
{
    info.startMainLineIndex_ = res.row;
    info.currentOffset_ = res.pos;
    info.startIndex_ = res.idx;
}

inline float GetPrevHeight(const GridLayoutInfo& info, float mainGap)
{
    return info.GetHeightInRange(info.startMainLineIndex_, info.endMainLineIndex_, mainGap);
}
} // namespace

void GridIrregularLayoutAlgorithm::MeasureForward(float mainSize)
{
    float heightToFill = mainSize - info_.currentOffset_ - GetPrevHeight(info_, mainGap_);
    if (Positive(heightToFill)) {
        GridIrregularFiller filler(&info_, wrapper_);
        filler.Fill({ crossLens_, crossGap_, mainGap_ }, heightToFill, info_.endMainLineIndex_);
    }

    GridLayoutRangeSolver solver(&info_, wrapper_);
    auto res = solver.FindStartingRow(mainGap_);
    UpdateStartInfo(info_, res);
    auto [endMainLineIdx, endIdx] = solver.SolveForwardForEndIdx(mainGap_, mainSize - res.pos, res.row);
    info_.endMainLineIndex_ = endMainLineIdx;
    info_.endIndex_ = endIdx;

    // adjust offset
    if (!overScroll_ && info_.endIndex_ == info_.childrenCount_ - 1) {
        float overDis =
            -info_.GetDistanceToBottom(mainSize, info_.GetTotalHeightOfItemsInView(mainGap_, false), mainGap_);
        if (Negative(overDis)) {
            return;
        }
        info_.currentOffset_ += overDis;
        if (Positive(info_.currentOffset_)) {
            MeasureBackward(mainSize);
        }
    }
}

void GridIrregularLayoutAlgorithm::MeasureBackward(float mainSize)
{
    // skip adding starting lines that are outside viewport in LayoutIrregular
    auto [it, offset] = info_.SkipLinesAboveView(mainGap_);
    GridIrregularFiller filler(&info_, wrapper_);
    filler.MeasureBackward({ crossLens_, crossGap_, mainGap_ }, offset + it->second + mainGap_, it->first);

    GridLayoutRangeSolver solver(&info_, wrapper_);
    auto res = solver.FindStartingRow(mainGap_);
    if (!overScroll_ && res.row == 0) {
        res.pos = std::min(res.pos, 0.0f);
    }
    UpdateStartInfo(info_, res);

    auto [endLine, endIdx] = solver.SolveForwardForEndIdx(mainGap_, mainSize - res.pos, res.row);
    info_.endMainLineIndex_ = endLine;
    info_.endIndex_ = endIdx;
}

namespace {
constexpr float SKIP_THRESHOLD = 2.0f;
}

bool GridIrregularLayoutAlgorithm::TrySkipping(float mainSize)
{
    float delta = std::abs(info_.currentOffset_ - info_.prevOffset_);
    if (enableSkip_ && GreatNotEqual(delta, mainSize)) {
        // a more costly check, therefore perform after comparing to [mainSize]
        if (LessOrEqual(delta, SKIP_THRESHOLD * info_.GetTotalHeightOfItemsInView(mainGap_))) {
            return false;
        }
        info_.jumpIndex_ = Negative(info_.currentOffset_) ? SkipLinesForward() : SkipLinesBackward();
        info_.scrollAlign_ = ScrollAlign::START;
        info_.currentOffset_ = 0.0f;
        Jump(mainSize);
        return true;
    }
    return false;
}

void GridIrregularLayoutAlgorithm::MeasureOnJump(float mainSize)
{
    Jump(mainSize);

    if (info_.extraOffset_ && !NearZero(*info_.extraOffset_)) {
        info_.prevOffset_ = info_.currentOffset_;
        info_.currentOffset_ += *info_.extraOffset_;
        MeasureOnOffset(mainSize);
    }
    if (!NearZero(postJumpOffset_)) {
        info_.currentOffset_ = postJumpOffset_;
        enableSkip_ = false;
        MeasureOnOffset(mainSize);
    }
}

void GridIrregularLayoutAlgorithm::Jump(float mainSize)
{
    if (info_.jumpIndex_ == JUMP_TO_BOTTOM_EDGE) {
        GridIrregularFiller filler(&info_, wrapper_);
        filler.FillMatrixOnly(info_.childrenCount_ - 1);
        info_.PrepareJumpToBottom();
    }

    if (info_.jumpIndex_ == LAST_ITEM) {
        info_.jumpIndex_ = info_.childrenCount_ - 1;
    }

    if (info_.scrollAlign_ == ScrollAlign::AUTO) {
        int32_t height = GridLayoutUtils::GetItemSize(&info_, wrapper_, info_.jumpIndex_).rows;
        info_.scrollAlign_ = info_.TransformAutoScrollAlign(info_.jumpIndex_, height, mainSize, mainGap_);
    }
    if (info_.scrollAlign_ == ScrollAlign::NONE) {
        info_.jumpIndex_ = EMPTY_JUMP_INDEX;
        return;
    }

    int32_t jumpLineIdx = FindJumpLineIdx(info_.jumpIndex_);

    PrepareLineHeight(mainSize, jumpLineIdx);

    GridLayoutRangeSolver solver(&info_, wrapper_);
    const auto res = solver.FindRangeOnJump(info_.jumpIndex_, jumpLineIdx, mainGap_);

    info_.currentOffset_ = res.pos;
    info_.startMainLineIndex_ = res.startRow;
    info_.startIndex_ = res.startIdx;
    info_.endMainLineIndex_ = res.endRow;
    info_.endIndex_ = res.endIdx;
    info_.jumpIndex_ = EMPTY_JUMP_INDEX;
}

void GridIrregularLayoutAlgorithm::UpdateLayoutInfo()
{
    info_.reachStart_ = info_.startIndex_ == 0 && NonNegative(info_.currentOffset_);
    // GridLayoutInfo::reachEnd_ has a different meaning
    info_.reachEnd_ = info_.endIndex_ == info_.childrenCount_ - 1;

    float mainSize = wrapper_->GetGeometryNode()->GetContentSize().MainSize(info_.axis_);

    info_.lastMainSize_ = mainSize;
    info_.totalHeightOfItemsInView_ = info_.GetTotalHeightOfItemsInView(mainGap_, false);
    info_.avgLineHeight_ = info_.GetTotalLineHeight(0.0f) / static_cast<float>(info_.lineHeightMap_.size());

    if (info_.reachEnd_) {
        info_.offsetEnd_ = NonPositive(info_.GetDistanceToBottom(mainSize, info_.totalHeightOfItemsInView_, mainGap_));
    } else {
        info_.offsetEnd_ = false;
    }
    info_.prevOffset_ = info_.currentOffset_;

    // validity check
    for (int i = info_.startMainLineIndex_; i <= info_.endMainLineIndex_; ++i) {
        if (info_.lineHeightMap_.find(i) == info_.lineHeightMap_.end()) {
            TAG_LOGW(AceLogTag::ACE_GRID,
                "lineHeight at line %d not ready. Data is corrupted. StartLine = %d, EndLine = %d", i,
                info_.startMainLineIndex_, info_.endMainLineIndex_);
            info_.endMainLineIndex_ = i - 1;
            info_.endIndex_ = info_.startIndex_ - 1;
            return;
        }
    }
}

namespace {
Alignment GetAlignment(Axis axis, const RefPtr<GridLayoutProperty>& props)
{
    Alignment align = axis == Axis::VERTICAL ? Alignment::TOP_CENTER : Alignment::CENTER_LEFT;
    const auto& positionProp = props->GetPositionProperty();
    if (positionProp) {
        align = positionProp->GetAlignment().value_or(align);
    }
    return align;
}
/* adjust mainOffset to the first cache line */
void AdjustStartOffset(const std::map<int32_t, float>& lineHeights, int32_t startLine, int32_t cacheStartLine,
    float mainGap, float& mainOffset)
{
    auto startLineIt = lineHeights.lower_bound(startLine);
    for (auto it = lineHeights.lower_bound(cacheStartLine); it != startLineIt; ++it) {
        mainOffset -= mainGap + it->second;
    }
}
} // namespace

void GridIrregularLayoutAlgorithm::LayoutChildren(float mainOffset, int32_t cacheLine)
{
    const auto& info = info_;
    const auto& props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    const Alignment align = GetAlignment(info.axis_, props);

    const auto& padding = *wrapper_->GetGeometryNode()->GetPadding();
    mainOffset += info.axis_ == Axis::HORIZONTAL ? 0.0f : padding.top.value_or(0.0f);
    auto crossPos = CalculateCrossPositions(padding);

    auto frameSize = wrapper_->GetGeometryNode()->GetFrameSize();
    MinusPaddingToSize(padding, frameSize);
    const bool isRtl = props->GetNonAutoLayoutDirection() == TextDirection::RTL;
    const int32_t cacheStartLine = info.startMainLineIndex_ - cacheLine;
    AdjustStartOffset(info.lineHeightMap_, info.startMainLineIndex_, cacheStartLine, mainGap_, mainOffset);

    auto endIt = info.gridMatrix_.upper_bound(std::max(info.endMainLineIndex_ + cacheLine, info.startMainLineIndex_));
    for (auto it = info.gridMatrix_.lower_bound(cacheStartLine); it != endIt; ++it) {
        auto lineHeightIt = info.lineHeightMap_.find(it->first);
        if (lineHeightIt == info.lineHeightMap_.end()) {
            continue;
        }
        const bool isCache = it->first < info.startMainLineIndex_ || it->first > info.endMainLineIndex_;
        const auto& row = it->second;
        for (const auto& [c, itemIdx] : row) {
            if (itemIdx < 0 || (itemIdx == 0 && (it->first > 0 || c > 0))) {
                // not top-left tile
                continue;
            }
            auto child = wrapper_->GetChildByIndex(itemIdx, isCache);
            if (!child) {
                continue;
            }

            SizeF blockSize = SizeF(crossLens_.at(c), lineHeightIt->second, info.axis_);
            auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
            auto alignPos = Alignment::GetAlignPosition(blockSize, childSize, align);

            OffsetF offset = OffsetF(crossPos[c], mainOffset, info.axis_);

            if (isRtl) {
                offset.SetX(frameSize.Width() - offset.GetX() - childSize.Width());
            }
            offset += OffsetF { padding.left.value_or(0.0f), 0.0f };
            child->GetGeometryNode()->SetMarginFrameOffset(offset + alignPos);
            if (child->CheckNeedForceMeasureAndLayout()) {
                child->Layout();
            } else {
                child->GetHostNode()->ForceSyncGeometryNode();
            }
        }
        // add mainGap below the item
        mainOffset += lineHeightIt->second + mainGap_;
    }
}

std::vector<float> GridIrregularLayoutAlgorithm::CalculateCrossPositions(const PaddingPropertyF& padding)
{
    std::vector<float> res(info_.crossCount_, 0.0f);
    res[0] = info_.axis_ == Axis::HORIZONTAL ? padding.top.value_or(0.0f) : 0.0f;
    for (int32_t i = 1; i < info_.crossCount_; ++i) {
        res[i] = res[i - 1] + crossLens_[i - 1] + crossGap_;
    }
    return res;
}

int32_t GridIrregularLayoutAlgorithm::FindJumpLineIdx(int32_t jumpIdx)
{
    GridIrregularFiller filler(&info_, wrapper_);
    int32_t jumpLine = -1;
    auto it = info_.FindInMatrix(jumpIdx);
    if (it == info_.gridMatrix_.end()) {
        // fill matrix up to jumpIndex_
        jumpLine = filler.FillMatrixOnly(jumpIdx);
    } else {
        jumpLine = it->first;
    }

    if (info_.scrollAlign_ == ScrollAlign::END) {
        // jump to the last line the item occupies
        auto lastLine = jumpLine + GridLayoutUtils::GetItemSize(&info_, wrapper_, jumpIdx).rows - 1;
        filler.FillMatrixByLine(jumpLine, lastLine + 1);
        jumpLine = lastLine;
    }
    return jumpLine;
}

using FillParams = GridIrregularFiller::FillParameters;
void GridIrregularLayoutAlgorithm::PrepareLineHeight(float mainSize, int32_t& jumpLineIdx)
{
    /* When mainSize can't be filled, adjust parameters and call function again. The maximum length of
     * the recursion is 3 iterations ([Start && len not filled] -> [End && len not filled] -> [Start with jumpIdx 0]).
     */
    GridIrregularFiller filler(&info_, wrapper_);
    const FillParams params { crossLens_, crossGap_, mainGap_ };
    switch (info_.scrollAlign_) {
        case ScrollAlign::START: {
            // call this to ensure irregular items on the first line are measured, not skipped
            filler.MeasureLineWithIrregulars(params, jumpLineIdx);

            float len = filler.Fill(params, mainSize, jumpLineIdx).length;
            // condition [jumpLineIdx > 0] guarantees a finite call stack
            if (LessNotEqual(len, mainSize) && jumpLineIdx > 0) {
                jumpLineIdx = info_.lineHeightMap_.rbegin()->first;
                info_.scrollAlign_ = ScrollAlign::END;
                PrepareLineHeight(mainSize, jumpLineIdx);
            }
            break;
        }
        case ScrollAlign::CENTER: {
            // because the current line's height is unknown, we can't determine the exact target length to fill.
            // Using the full [mainSize]
            const auto pos = info_.GetItemPos(info_.jumpIndex_);
            const float itemLen = filler.MeasureItem(params, info_.jumpIndex_, pos.first, pos.second, false).first;
            const float targetLen = mainSize / 2.0f;
            float backwardLen = filler.MeasureBackward(params, mainSize, jumpLineIdx);
            backwardLen -= info_.lineHeightMap_.at(jumpLineIdx) / 2.0f;
            if (LessNotEqual(backwardLen, targetLen)) {
                jumpLineIdx = 0;
                info_.scrollAlign_ = ScrollAlign::START;
                PrepareLineHeight(mainSize, jumpLineIdx);
                return;
            }
            float forwardLen = filler.Fill(params, std::max(mainSize, itemLen), jumpLineIdx).length;
            forwardLen -= info_.lineHeightMap_.at(jumpLineIdx) / 2.0f;
            if (LessNotEqual(forwardLen, targetLen)) {
                jumpLineIdx = info_.lineHeightMap_.rbegin()->first;
                info_.scrollAlign_ = ScrollAlign::END;
                PrepareLineHeight(mainSize, jumpLineIdx);
            }
            break;
        }
        case ScrollAlign::END: {
            float len = filler.MeasureBackward(params, mainSize, jumpLineIdx);
            if (LessNotEqual(len, mainSize)) {
                jumpLineIdx = 0;
                info_.scrollAlign_ = ScrollAlign::START;
                PrepareLineHeight(mainSize, jumpLineIdx);
            }
            break;
        }
        default:
            break;
    }
}

namespace {
void AddLineHeight(float& height, int32_t curLine, int32_t startLine, const std::map<int32_t, float>& lineHeights)
{
    auto iter = lineHeights.find(curLine);
    if (iter != lineHeights.end()) {
        height += iter->second;
    } else {
        // estimation
        height += height / std::abs(curLine - startLine);
    }
}
} // namespace

int32_t GridIrregularLayoutAlgorithm::SkipLinesForward()
{
    int32_t line = info_.startMainLineIndex_;
    float height = 0.0f;
    while (LessNotEqual(height, -info_.currentOffset_)) {
        AddLineHeight(height, line++, info_.startMainLineIndex_, info_.lineHeightMap_);
    }
    GridIrregularFiller filler(&info_, wrapper_);
    return filler.FillMatrixByLine(info_.startMainLineIndex_, line);
}

int32_t GridIrregularLayoutAlgorithm::SkipLinesBackward() const
{
    const auto& info = info_;
    float height = info.GetHeightInRange(info.startMainLineIndex_, info.endMainLineIndex_ + 1, 0.0f);

    float target = info.currentOffset_ + height;
    int32_t line = info.startMainLineIndex_;
    while (LessNotEqual(height, target) && line > 0) {
        AddLineHeight(height, --line, info.endMainLineIndex_, info.lineHeightMap_);
    }
    return std::max(0, info.FindEndIdx(line).itemIdx);
}

void GridIrregularLayoutAlgorithm::MeasureToTarget()
{
    GridIrregularFiller filler(&info_, wrapper_);
    FillParams param { crossLens_, crossGap_, mainGap_ };
    if (info_.targetIndex_ < info_.startIndex_) {
        auto it = info_.FindInMatrix(*info_.targetIndex_);
        filler.MeasureBackwardToTarget(param, it->first, info_.startMainLineIndex_);
    } else {
        filler.FillToTarget(param, *info_.targetIndex_, info_.startMainLineIndex_);
    }
}

bool GridIrregularLayoutAlgorithm::IsIrregularLine(int32_t lineIndex) const
{
    const auto& line = info_.gridMatrix_.find(lineIndex);
    if (line == info_.gridMatrix_.end()) {
        return true;
    }
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    const auto& opts = *props->GetLayoutOptions();
    return std::any_of(line->second.begin(), line->second.end(),
        [opts](const auto& item) { return opts.irregularIndexes.count(std::abs(item.second)); });
}

void GridIrregularLayoutAlgorithm::SyncPreloadItems(int32_t cacheCnt)
{
    const int32_t start = std::max(info_.startIndex_ - cacheCnt, 0);
    const int32_t end = std::min(info_.endIndex_ + cacheCnt, info_.childrenCount_ - 1);
    GridIrregularFiller filler(&info_, wrapper_);
    FillParams param { crossLens_, crossGap_, mainGap_ };
    auto it = info_.FindInMatrix(start);
    filler.MeasureBackwardToTarget(param, it->first, info_.startMainLineIndex_ - 1);
    filler.FillToTarget(param, end, info_.endMainLineIndex_);
}

void GridIrregularLayoutAlgorithm::PreloadItems(int32_t cacheCnt)
{
    std::list<GridPreloadItem> itemsToPreload;
    for (int32_t i = 1; i <= cacheCnt; ++i) {
        const int32_t l = info_.startIndex_ - i;
        if (l >= 0 && !wrapper_->GetChildByIndex(l)) {
            itemsToPreload.emplace_back(l);
        }
        const int32_t r = info_.endIndex_ + i;
        if (r < info_.childrenCount_ && !wrapper_->GetChildByIndex(r)) {
            itemsToPreload.emplace_back(r);
        }
    }

    GridIrregularFiller filler(&info_, wrapper_);
    filler.FillMatrixOnly(std::min(info_.childrenCount_, info_.endIndex_ + cacheCnt));

    GridLayoutUtils::PreloadGridItems(wrapper_->GetHostNode()->GetPattern<GridPattern>(), std::move(itemsToPreload),
        [crossLens = crossLens_, crossGap = crossGap_, mainGap = mainGap_](
            const RefPtr<FrameNode>& host, int32_t itemIdx) {
            CHECK_NULL_RETURN(host, false);
            auto pattern = host->GetPattern<GridPattern>();
            CHECK_NULL_RETURN(pattern, false);
            auto& info = pattern->GetMutableLayoutInfo();
            GridIrregularFiller filler(&info, RawPtr(host));
            const auto pos = info.GetItemPos(itemIdx);
            auto constraint = filler
                                  .MeasureItem(GridIrregularFiller::FillParameters { crossLens, crossGap, mainGap },
                                      itemIdx, pos.first, pos.second, true)
                                  .second;

            auto item = DynamicCast<FrameNode>(host->GetChildByIndex(itemIdx, true));
            CHECK_NULL_RETURN(item, false);
            item->GetGeometryNode()->SetParentLayoutConstraint(constraint);
            item->Layout();
            item->SetActive(false);
            return true;
        });
}
} // namespace OHOS::Ace::NG
