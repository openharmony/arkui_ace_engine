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

#include "core/components_ng/pattern/grid/grid_custom/grid_custom_layout_algorithm.h"

#include "grid_custom_layout_algorithm.h"

#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
namespace {
GridIrregularFiller::FillParameters GetFillParameters(const RefPtr<FrameNode>& host, const GridLayoutInfo& info,
    double originalWidth)
{
    const auto& contentSize = host->GetGeometryNode()->GetContentSize();
    auto props = AceType::DynamicCast<GridLayoutProperty>(host->GetLayoutProperty());
    auto crossGap = GridUtils::GetCrossGap(props, contentSize, info.axis_);
    auto mainGap = GridUtils::GetMainGap(props, contentSize, info.axis_);
    std::string args = info.axis_ == Axis::VERTICAL
                           ? props->GetFinalColumnsTemplate(originalWidth).value_or("")
                           : props->GetRowsTemplate().value_or("");
    const float crossSize = contentSize.CrossSize(info.axis_);
    auto res = ParseTemplateArgs(GridUtils::ParseArgs(args), crossSize, crossGap, info.GetChildrenCount());
    auto crossLens = std::vector<float>(res.first.begin(), res.first.end());
    if (crossLens.empty()) {
        crossLens.push_back(crossSize);
    }
    crossGap = res.second;
    return { crossLens, crossGap, mainGap };
}

inline void PrepareJumpOnReset(GridLayoutInfo& info)
{
    info.jumpIndex_ = std::min(info.startIndex_, info.childrenCount_ - 1);
    info.scrollAlign_ = ScrollAlign::START;
}
} // namespace

void GridCustomLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    if (info_.GetChildrenCount() <= 0) {
        return;
    }
    wrapper_ = layoutWrapper;
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());

    float mainSize = MeasureSelf(props);
    CalcContentOffset(wrapper_, mainSize);
    auto layoutPolicy = props->GetLayoutPolicyProperty();
    auto isMainWrap = false;
    if (layoutPolicy.has_value()) {
        auto isVertical = info_.axis_ == Axis::VERTICAL;
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto isMainFix = (isVertical ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
        isMainWrap = (isVertical ? heightLayoutPolicy : widthLayoutPolicy) == LayoutCalPolicy::WRAP_CONTENT;
        if (isMainFix) {
            frameSize_.SetMainSize(LayoutInfinity<float>(), info_.axis_);
        }
    }
    bool matchChildren = GreaterOrEqualToInfinity(mainSize) || isMainWrap;
    Init(props);

    if (info_.targetIndex_) {
        MeasureToTarget(mainSize);
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
    if (matchChildren) {
        AdaptToChildMainSize(props, mainSize, frameSize_);
    }
    const int32_t cacheCnt = props->GetCachedCountValue(info_.defCachedCount_) * info_.crossCount_;
    PreloadItems(cacheCnt);
}

void GridCustomLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    const auto& info = info_;
    if (info.childrenCount_ <= 0) {
        return;
    }
    wrapper_ = layoutWrapper;
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    CHECK_NULL_VOID(props);

    const int32_t cacheLines = props->GetCachedCountValue(info.defCachedCount_);
    if (!props->HasCachedCount()) {
        info_.UpdateDefaultCachedCount();
    }
    auto cachedItemCnt = LayoutChildren(info.currentOffset_, cacheLines);

    if (!props->GetShowCachedItemsValue(false)) {
        // only use accurate counting method when cached items need to be shown
        cachedItemCnt.first = cachedItemCnt.second = cacheLines * info.crossCount_;
    }
    LostChildFocusToSelf(layoutWrapper, std::min(info.startIndex_, info.endIndex_) - cachedItemCnt.first,
        info.endIndex_ + cachedItemCnt.second);
    wrapper_->SetActiveChildRange(std::min(info.startIndex_, info.endIndex_), info.endIndex_, cachedItemCnt.first,
        cachedItemCnt.second, props->GetShowCachedItemsValue(false));
    wrapper_->SetCacheCount(cachedItemCnt.first);
    UpdateOverlay(wrapper_);
}

float GridCustomLayoutAlgorithm::MeasureSelf(const RefPtr<GridLayoutProperty>& props)
{
    // set self size
    frameSize_ = CreateIdealSize(props->GetLayoutConstraint().value(), info_.axis_, props->GetMeasureType(), true);
    originalWidth_ = frameSize_.Width();
    wrapper_->GetGeometryNode()->SetFrameSize(frameSize_);

    // set content size
    const auto& padding = props->CreatePaddingAndBorder();
    wrapper_->GetGeometryNode()->UpdatePaddingWithBorder(padding);
    MinusPaddingToSize(padding, frameSize_);
    info_.contentEndPadding_ = ScrollableUtils::CheckHeightExpansion(props, info_.axis_);
    frameSize_.AddHeight(info_.contentEndPadding_);
    wrapper_->GetGeometryNode()->SetContentSize(frameSize_);

    return frameSize_.MainSize(info_.axis_);
}

void GridCustomLayoutAlgorithm::Init(const RefPtr<GridLayoutProperty>& props)
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
        args = props->GetFinalColumnsTemplate(originalWidth_).value_or("");
    }

    const float crossSize = contentSize.CrossSize(info_.axis_);
    auto res = ParseTemplateArgs(GridUtils::ParseArgs(args), crossSize, crossGap_, info_.GetChildrenCount());

    crossLens_ = std::vector<float>(res.first.begin(), res.first.end());
    if (crossLens_.empty()) {
        crossLens_.push_back(crossSize);
    }

    crossGap_ = res.second;

    info_.crossCount_ = static_cast<int32_t>(crossLens_.size());
    if (!info_.lastCrossCount_) {
        info_.lastCrossCount_ = info_.crossCount_;
    }
    CheckForReset();

    auto host = wrapper_->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->IsInitialized()) {
        info_.currentOffset_ += info_.contentStartOffset_;
    }
}

void GridCustomLayoutAlgorithm::ClearCache()
{
    info_.lineHeightMap_.clear();
    info_.gridMatrix_.clear();
    info_.endIndex_ = -1;
    info_.endMainLineIndex_ = 0;
    info_.prevOffset_ = info_.currentOffset_;
    info_.ResetPositionFlags();
}

void GridCustomLayoutAlgorithm::ClearCacheForReload()
{
    info_.lastCrossCount_ = info_.crossCount_;
    info_.lineHeightMap_.clear();
    info_.gridMatrix_.clear();
    info_.irregularItemsPosition_.clear();
    info_.endIndex_ = -1;
    info_.endMainLineIndex_ = 0;
    info_.prevOffset_ = info_.currentOffset_;
    info_.ResetPositionFlags();
    info_.clearStretch_ = true;
    ResetFocusedIndex(wrapper_);
}

void GridCustomLayoutAlgorithm::CheckForReset()
{
    int32_t updateIdx = wrapper_->GetHostNode()->GetChildrenUpdated();
    if (info_.IsResetted() || updateIdx == 0 || (updateIdx != -1 && updateIdx <= info_.endIndex_)) {
        if (info_.lastCrossCount_ != info_.crossCount_ && info_.jumpIndex_ == EMPTY_JUMP_INDEX) {
            PrepareJumpOnReset(info_);
            adjustOffset_ = info_.currentOffset_;
        }
        ClearCacheForReload();
        reloadFlag_ = true;
        wrapper_->GetHostNode()->ChildrenUpdatedFrom(-1);
        return;
    }

    auto property = wrapper_->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    if (property->GetPropertyChangeFlag() & PROPERTY_UPDATE_BY_CHILD_REQUEST) {
        reloadFlag_ = true;
        return;
    }

    if (wrapper_->ConstraintChanged()) {
        reloadFlag_ = true;
    }
}

void GridCustomLayoutAlgorithm::MeasureOnOffset(float mainSize)
{
    if (LessOrEqual(info_.currentOffset_, info_.prevOffset_)) {
        MeasureBackward(mainSize);
    } else {
        MeasureForward(mainSize);
    }

    if (info_.startIndex_ == 0 && GreatOrEqual(info_.currentOffset_, info_.contentStartOffset_)) {
        if (!canOverScrollStart_) {
            info_.currentOffset_ = info_.contentStartOffset_;
        }
        return;
    }
    // adjust offset
    if (!canOverScrollEnd_ && info_.endIndex_ == info_.GetChildrenCount() - 1) {
        float overDis =
            -info_.GetDistanceToBottom(mainSize, info_.GetTotalHeightOfItemsInView(mainGap_, true), mainGap_);
        if (Negative(overDis)) {
            return;
        }
        info_.currentOffset_ += overDis;
        if (Positive(info_.currentOffset_)) {
            info_.currentDelta_ = overDis;
            MeasureForward(mainSize);
        } else {
            info_.totalOffset_ -= overDis;
        }
    }
}

void GridCustomLayoutAlgorithm::MeasureForward(float mainSize)
{
    JumpToTargetOffset(mainSize);
}

void GridCustomLayoutAlgorithm::MeasureBackward(float mainSize)
{
    if (NeedJump(mainSize) || reloadFlag_) {
        JumpToTargetOffset(mainSize);
        return;
    }

    FillBackward(mainSize);
}
namespace {
inline void UpdateStartInfo(GridLayoutInfo& info, const GridLayoutRangeSolver::StartingRowInfo& res)
{
    info.startMainLineIndex_ = res.row;
    info.currentOffset_ = res.pos;
    info.startIndex_ = res.idx;
}
} // namespace

void GridCustomLayoutAlgorithm::JumpToTargetOffset(float mainSize)
{
    ClearCache();
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    const auto& opts = *props->GetLayoutOptions();
    float targetOffset = info_.totalOffset_ - info_.currentDelta_;
    if (!canOverScrollStart_) {
        targetOffset = std::max(targetOffset, -info_.contentStartOffset_);
    }
    auto host = wrapper_->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    auto totalHeight = pattern->GetTotalHeight();
    if (LessNotEqual(info_.totalOffset_, totalHeight - mainSize) &&
        GreatNotEqual(targetOffset, totalHeight - mainSize)) {
        targetOffset = totalHeight - mainSize;
    }
    auto startLineInfo = GetStartIndexByOffset(targetOffset, opts);
    info_.startIndex_ = std::clamp(startLineInfo.startIndex, 0, info_.GetChildrenCount() - 1);
    info_.startMainLineIndex_ = std::max(0, startLineInfo.startLine);
    info_.currentOffset_ = startLineInfo.startOffset;
    info_.totalOffset_ = startLineInfo.totalOffset;

    GridIrregularFiller filler(&info_, wrapper_);
    filler.FillFromStartIndex({ crossLens_, crossGap_, mainGap_ }, mainSize - info_.currentOffset_);

    GridLayoutRangeSolver solver(&info_, wrapper_);
    auto res = solver.FindStartingRow(mainGap_);
    UpdateStartInfo(info_, res);
    auto [endMainLineIdx, endIdx] =
        solver.SolveForwardForEndIdx(mainGap_, mainSize - info_.currentOffset_, info_.startMainLineIndex_);
    info_.endMainLineIndex_ = endMainLineIdx;
    info_.endIndex_ = endIdx;
}

void GridCustomLayoutAlgorithm::FillBackward(float mainSize)
{
    auto [it, offset] = info_.SkipLinesAboveView(mainGap_);
    int32_t line = 0;
    if (info_.lineHeightMap_.empty() || (it == info_.lineHeightMap_.end() && (--it) == info_.lineHeightMap_.end())) {
        line = info_.startMainLineIndex_;
    } else {
        line = it->first;
    }
    GridIrregularFiller filler(&info_, wrapper_);
    filler.FillBackward({ crossLens_, crossGap_, mainGap_ }, mainSize - offset + it->second + mainGap_, line);

    GridLayoutRangeSolver solver(&info_, wrapper_);
    auto res = solver.FindStartingRow(mainGap_);

    UpdateStartInfo(info_, res);

    auto [endLine, endIdx] = solver.SolveForwardForEndIdx(mainGap_, mainSize - res.pos, res.row);
    info_.endMainLineIndex_ = endLine;
    info_.endIndex_ = endIdx;
    info_.totalOffset_ -= info_.currentDelta_;
}
namespace {
constexpr float SKIP_THRESHOLD = 2.0f;
}

bool GridCustomLayoutAlgorithm::NeedJump(float mainSize)
{
    return std::abs(info_.currentDelta_) >= mainSize * SKIP_THRESHOLD && !TargetOffsetInCache();
}

bool GridCustomLayoutAlgorithm::TargetOffsetInCache()
{
    // If startMainLineIndex_ is not within valid range, return false directly
    if (info_.startMainLineIndex_ < 0) {
        return false;
    }
    float accumulatedHeight = info_.currentOffset_;
    int32_t currentLine = info_.startMainLineIndex_;
    // Traverse forward from startMainLineIndex_ until currentLine >= 0
    while (currentLine >= 0) {
        // Check if the row exists in both gridMatrix_ and lineHeightMap_
        auto matrixIter = info_.gridMatrix_.find(currentLine);
        auto heightIter = info_.lineHeightMap_.find(currentLine);
        if (matrixIter != info_.gridMatrix_.end() && heightIter != info_.lineHeightMap_.end()) {
            // Accumulate row height and gap
            accumulatedHeight += mainGap_;
            accumulatedHeight += heightIter->second;
            // If accumulatedHeight >= 0 after accumulation, it means the target offset is within the page
            if (accumulatedHeight >= 0) {
                return true;
            }
        }
        currentLine--;
    }
    // After traversing all available rows, accumulatedHeight is still less than 0,
    // indicating the target offset is not within the page
    return false;
}

namespace {
inline void UpdateTotalOffset(GridLayoutInfo& info, int32_t startLine, float mainGap)
{
    int32_t currentLine = info.startMainLineIndex_;
    float heightInRange = 0.f;
    if (startLine <= currentLine) {
        heightInRange = info.GetHeightInRange(startLine, currentLine, mainGap);
        info.totalOffset_ = info.totalOffset_ - heightInRange;
    } else {
        heightInRange = info.GetHeightInRange(currentLine, startLine, mainGap);
        info.totalOffset_ = info.totalOffset_ + heightInRange;
    }
}
} // namespace

void GridCustomLayoutAlgorithm::MeasureOnJump(float mainSize)
{
    if (info_.jumpIndex_ == JUMP_TO_BOTTOM_EDGE || info_.jumpIndex_ == LAST_ITEM) {
        info_.jumpIndex_ = info_.GetChildrenCount() - 1;
    }
    // 1. Validate the legality of jumpIndex
    if (info_.jumpIndex_ < 0 || info_.jumpIndex_ >= info_.GetChildrenCount()) {
        info_.jumpIndex_ = EMPTY_JUMP_INDEX;
        adjustOffset_.reset(); // Clear adjustment offset
        return;
    }
    if (info_.scrollAlign_ == ScrollAlign::AUTO) {
        int32_t height = GridLayoutUtils::GetItemSize(&info_, wrapper_, info_.jumpIndex_).rows;
        info_.scrollAlign_ = info_.TransformAutoScrollAlign(info_.jumpIndex_, height, mainSize, mainGap_);
        if (info_.scrollAlign_ == ScrollAlign::NONE) {
            info_.jumpIndex_ = EMPTY_JUMP_INDEX;
            adjustOffset_.reset(); // Clear adjustment offset
            return;
        }
    }

    // Not in cache, perform jump
    float itemHeight = JumpToTargetIndex(mainSize, info_.jumpIndex_);

    // 4. Adjust currentOffset_ based on scrollAlign, extraOffset and contentStartOffset or contentEndOffset
    info_.prevOffset_ = info_.currentOffset_;

    // Handle scrollAlign
    switch (info_.scrollAlign_) {
        case ScrollAlign::START:
            // Adjust to content start position
            info_.currentOffset_ += info_.contentStartOffset_;
            break;
        case ScrollAlign::CENTER: {
            // Center the target node
            info_.currentOffset_ += ((mainSize - itemHeight) / 2.0f);
            break;
        }
        case ScrollAlign::END:
            // Adjust to content end position
            info_.currentOffset_ += mainSize - itemHeight - info_.contentEndOffset_;
            break;
        default:
            // Auto adjust, handle based on actual situation
            break;
    }

    // Handle extraOffset
    if (info_.extraOffset_ && !NearZero(*info_.extraOffset_)) {
        info_.currentOffset_ += *info_.extraOffset_;
    }

    // Handle adjustOffset_ (adjustment offset for crossCount change)
    if (adjustOffset_ && !NearZero(*adjustOffset_)) {
        info_.currentOffset_ += *adjustOffset_;
        adjustOffset_.reset(); // Clear immediately after use
    }

    info_.currentDelta_ = info_.currentOffset_ - info_.prevOffset_;
    // 5. Call MeasureOnOffset for layout
    MeasureOnOffset(mainSize);
    // Reset jumpIndex_
    info_.jumpIndex_ = EMPTY_JUMP_INDEX;
}

bool GridCustomLayoutAlgorithm::IsTargetRowInCache(int32_t jumpIndex)
{
    auto targetRow = info_.GetItemPos(jumpIndex);
    if (targetRow.second != -1) {
        if (info_.lineHeightMap_.find(targetRow.second) != info_.lineHeightMap_.end() &&
            info_.gridMatrix_.find(targetRow.second) != info_.gridMatrix_.end()) {
            return true;
        }
    }
    return false;
}

float GridCustomLayoutAlgorithm::JumpToTargetIndex(float mainSize, int32_t targetIndex)
{
    ClearCache();
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    const auto& opts = *props->GetLayoutOptions();
    auto startLineInfo = GetStartIndexByIndex(targetIndex, opts);
    info_.startIndex_ = startLineInfo.startIndex;
    info_.startMainLineIndex_ = startLineInfo.startLine;
    info_.currentOffset_ = startLineInfo.startOffset;
    info_.totalOffset_ = startLineInfo.totalOffset;

    GridIrregularFiller filler(&info_, wrapper_);
    auto heightInRange = filler.FillMatrixFromStartIndexWithMeasure(
        { crossLens_, crossGap_, mainGap_ }, info_.startMainLineIndex_, info_.startIndex_, targetIndex);
    return heightInRange;
}

GridStartLineInfo GridCustomLayoutAlgorithm::GetStartIndexByIndex(int32_t index, const GridLayoutOptions& options)
{
    auto startLineInfo = options.getStartIndexByIndex(index);
    return startLineInfo;
}
GridStartLineInfo GridCustomLayoutAlgorithm::GetStartIndexByOffset(float offset, const GridLayoutOptions& options)
{
    auto startLineInfo = options.getStartIndexByOffset(offset);
    return startLineInfo;
}

void GridCustomLayoutAlgorithm::UpdateLayoutInfo()
{
    info_.reachStart_ = info_.startIndex_ == 0 && GreatOrEqual(info_.currentOffset_, info_.contentStartOffset_);
    info_.reachEnd_ = info_.endIndex_ == info_.GetChildrenCount() - 1;

    float mainSize = wrapper_->GetGeometryNode()->GetContentSize().MainSize(info_.axis_);

    info_.lastMainSize_ = mainSize;
    info_.totalHeightOfItemsInView_ = info_.GetTotalHeightOfItemsInView(mainGap_, true);
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

std::pair<int32_t, int32_t> GridCustomLayoutAlgorithm::LayoutChildren(float mainOffset, int32_t cacheLine)
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

    std::pair<int32_t, int32_t> cacheCnt = { 0, 0 };
    auto endIt = info.gridMatrix_.upper_bound(std::max(info.endMainLineIndex_ + cacheLine, info.startMainLineIndex_));
    for (auto it = info.gridMatrix_.lower_bound(cacheStartLine); it != endIt; ++it) {
        auto lineHeightIt = info.lineHeightMap_.find(it->first);
        if (lineHeightIt == info.lineHeightMap_.end()) {
            continue;
        }
        const bool isCache = !props->GetShowCachedItemsValue(false) &&
                             (it->first < info.startMainLineIndex_ || it->first > info.endMainLineIndex_);
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

            if (it->first < info.startMainLineIndex_) {
                ++cacheCnt.first;
            } else if (it->first > info.endMainLineIndex_) {
                ++cacheCnt.second;
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
            if (!isCache && child->CheckNeedForceMeasureAndLayout()) {
                child->Layout();
            } else {
                child->GetHostNode()->ForceSyncGeometryNode();
            }
            auto frameNode = DynamicCast<FrameNode>(child);
            if (frameNode) {
                frameNode->MarkAndCheckNewOpIncNode(info.axis_);
            }
        }
        // add mainGap below the item
        mainOffset += lineHeightIt->second + mainGap_;
    }
    return cacheCnt;
}

std::vector<float> GridCustomLayoutAlgorithm::CalculateCrossPositions(const PaddingPropertyF& padding)
{
    std::vector<float> res(info_.crossCount_, 0.0f);
    res[0] = info_.axis_ == Axis::HORIZONTAL ? padding.top.value_or(0.0f) : 0.0f;
    for (int32_t i = 1; i < info_.crossCount_; ++i) {
        res[i] = res[i - 1] + crossLens_[i - 1] + crossGap_;
    }
    return res;
}

void GridCustomLayoutAlgorithm::MeasureToTarget(float mainSize)
{
    if (!info_.targetIndex_.has_value()) {
        return;
    }
    int32_t height = GridLayoutUtils::GetItemSize(&info_, wrapper_, info_.jumpIndex_).rows;
    if (info_.scrollAlign_ == ScrollAlign::AUTO) {
        info_.scrollAlign_ = info_.TransformAutoScrollAlign(info_.targetIndex_.value(), height, mainSize, mainGap_);
        if (info_.scrollAlign_ == ScrollAlign::NONE) {
            info_.targetIndex_.reset();
            return;
        }
    }
    auto targetRow = info_.GetItemPos(info_.targetIndex_.value());
    bool isInCache = IsTargetRowInCache(info_.targetIndex_.value());
    float itemHeight = 0.f;
    float targetOffset = 0.f;
    if (isInCache) {
        float totalOffset = info_.totalOffset_;
        UpdateTotalOffset(info_, targetRow.second, mainGap_);
        info_.totalOffset_ += info_.currentOffset_;
        itemHeight = info_.GetHeightInRange(targetRow.second, targetRow.second + height, mainGap_) - mainGap_;
        targetOffset = info_.totalOffset_;
        info_.totalOffset_ = totalOffset;
    } else {
        auto tempInfo = info_;
        itemHeight = JumpToTargetIndex(mainSize, info_.targetIndex_.value());
        targetOffset = info_.totalOffset_;
        info_ = tempInfo;
    }
    switch (info_.scrollAlign_) {
        case ScrollAlign::START:
            targetOffset -= info_.contentStartOffset_;
            break;
        case ScrollAlign::CENTER: {
            float centerOffset = (mainSize - itemHeight) / 2.0f;
            targetOffset -= centerOffset;
            break;
        }
        case ScrollAlign::END: {
            float endHeight = mainSize - itemHeight - info_.contentEndOffset_;
            targetOffset -= endHeight;
            break;
        }
        default:
            break;
    }
    info_.targetPos_ = targetOffset;
    info_.targetIndex_.reset();
}

bool GridCustomLayoutAlgorithm::IsIrregularLine(int32_t lineIndex) const
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

void GridCustomLayoutAlgorithm::PreloadItems(int32_t cacheCnt)
{
    std::list<GridPreloadItem> itemsToPreload;
    int32_t startIndex = info_.startIndex_;
    int32_t endIndex = info_.endIndex_;
    for (int32_t i = 1; i <= cacheCnt; ++i) {
        const int32_t l = info_.startIndex_ - i;
        auto itemWrapper = wrapper_->GetChildByIndex(l, true);
        if (l >= 0 && GridUtils::CheckNeedCacheLayout(itemWrapper)) {
            itemsToPreload.emplace_back(l);
            startIndex = l;
        }
        const int32_t r = info_.endIndex_ + i;
        itemWrapper = wrapper_->GetChildByIndex(r, true);
        if (r < info_.GetChildrenCount() && GridUtils::CheckNeedCacheLayout(itemWrapper)) {
            itemsToPreload.emplace_back(r);
            endIndex = r;
        }
    }
    if (itemsToPreload.empty()) {
        return;
    }
    GridIrregularFiller filler(&info_, wrapper_);
    const auto pos = info_.GetItemPos(startIndex);
    if (pos.second == -1) {
        auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
        const auto& options = *props->GetLayoutOptions();
        auto startLineInfo = GetStartIndexByIndex(startIndex, options);
        filler.FillMatrixFromStartIndex(startLineInfo.startLine, startLineInfo.startIndex, endIndex);
    } else {
        filler.FillMatrixFromStartIndex(pos.second, startIndex, endIndex);
    }

    auto wrapper = wrapper_->GetHostNode();
    CHECK_NULL_VOID(wrapper);
    double originalWidth = originalWidth_;
    GridLayoutUtils::PreloadGridItems(wrapper->GetPattern<GridPattern>(), std::move(itemsToPreload),
        [originalWidth](const RefPtr<FrameNode>& host, int32_t itemIdx) {
            CHECK_NULL_RETURN(host, false);
            auto pattern = host->GetPattern<GridPattern>();
            CHECK_NULL_RETURN(pattern, false);

            ScopedLayout scope(host->GetContext());
            auto& info = pattern->GetMutableLayoutInfo();
            GridIrregularFiller filler(&info, RawPtr(host));
            const auto pos = info.GetItemPos(itemIdx);
            auto constraint =
                filler.MeasureItem(GetFillParameters(host, info, originalWidth), itemIdx, pos.first, pos.second, true)
                    .second;

            auto item = GetGridItem(&(*host), itemIdx, false, true);
            CHECK_NULL_RETURN(item, false);
            item->SetActive(false);
            auto itemFrameNode = item->GetHostNode();
            CHECK_NULL_RETURN(itemFrameNode, false);
            itemFrameNode->GetGeometryNode()->SetParentLayoutConstraint(constraint);
            FrameNode::ProcessOffscreenNode(itemFrameNode);
            return true;
        });
}

void GridCustomLayoutAlgorithm::AdaptToChildMainSize(
    RefPtr<GridLayoutProperty>& gridLayoutProperty, float mainSize, SizeF idealSize)
{
    float lengthOfItemsInViewport = info_.GetTotalHeightOfItemsInView(mainGap_);
    float totalHeight = lengthOfItemsInViewport + info_.contentStartOffset_ + info_.contentEndOffset_;
    float gridMainSize = std::min(totalHeight, mainSize);
    gridMainSize =
        std::max(gridMainSize, GetMainAxisSize(gridLayoutProperty->GetLayoutConstraint()->minSize, info_.axis_));
    idealSize.SetMainSize(gridMainSize, info_.axis_);
    AddPaddingToSize(gridLayoutProperty->CreatePaddingAndBorder(), idealSize);
    wrapper_->GetGeometryNode()->SetFrameSize(idealSize);
    if (!NearEqual(gridMainSize, info_.lastMainSize_)) {
        info_.lastMainSize_ = gridMainSize;
        TAG_LOGI(AceLogTag::ACE_GRID, "gridMainSize:%{public}f", gridMainSize);
    }
}
} // namespace OHOS::Ace::NG
