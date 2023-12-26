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

#include "core/components_ng/pattern/grid/irregular/grid_irregular_layout_algorithm.h"

#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"
#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void GridIrregularLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    wrapper_ = layoutWrapper;
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());

    float mainSize = MeasureSelf(props);
    Init(props);

    if (gridLayoutInfo_.jumpIndex_ > -1) {
        MeasureOnJump(mainSize);
    } else {
        MeasureOnOffset(mainSize);
    }

    wrapper_->SetCacheCount(static_cast<int32_t>(props->GetCachedCountValue(1) * gridLayoutInfo_.crossCount_));
}

void GridIrregularLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    wrapper_ = layoutWrapper;

    wrapper_->RemoveAllChildInRenderTree();

    LayoutChildren(gridLayoutInfo_.currentOffset_);

    UpdateLayoutInfo();
}

float GridIrregularLayoutAlgorithm::MeasureSelf(const RefPtr<GridLayoutProperty>& props)
{
    // set self size
    auto size =
        CreateIdealSize(props->GetLayoutConstraint().value(), gridLayoutInfo_.axis_, props->GetMeasureType(), true);
    wrapper_->GetGeometryNode()->SetFrameSize(size);

    // set content size
    const auto& padding = props->CreatePaddingAndBorder();
    wrapper_->GetGeometryNode()->UpdatePaddingWithBorder(padding);
    MinusPaddingToSize(padding, size);
    gridLayoutInfo_.contentEndPadding_ = ScrollableUtils::CheckHeightExpansion(props, gridLayoutInfo_.axis_);
    size.AddHeight(gridLayoutInfo_.contentEndPadding_);
    wrapper_->GetGeometryNode()->SetContentSize(size);

    return size.MainSize(gridLayoutInfo_.axis_);
}

void GridIrregularLayoutAlgorithm::Init(const RefPtr<GridLayoutProperty>& props)
{
    const auto& contentSize = wrapper_->GetGeometryNode()->GetContentSize();
    crossGap_ = GridUtils::GetCrossGap(props, contentSize, gridLayoutInfo_.axis_);
    mainGap_ = GridUtils::GetMainGap(props, contentSize, gridLayoutInfo_.axis_);

    std::string args;
    if (props->GetRowsTemplate()) {
        gridLayoutInfo_.axis_ = Axis::HORIZONTAL;
        args = props->GetRowsTemplate().value_or("");
    } else {
        gridLayoutInfo_.axis_ = Axis::VERTICAL;
        args = props->GetColumnsTemplate().value_or("");
    }

    const float crossSize = contentSize.CrossSize(gridLayoutInfo_.axis_);
    auto res = ParseTemplateArgs(GridUtils::ParseArgs(args), crossSize, crossGap_, wrapper_->GetTotalChildCount());

    crossLens_ = std::vector<float>(res.first.begin(), res.first.end());
    if (crossLens_.empty()) {
        crossLens_.push_back(crossSize);
    }

    if (res.second) {
        // compress, no more gaps
        crossGap_ = 0.0f;
    }

    gridLayoutInfo_.crossCount_ = crossLens_.size();
}

void GridIrregularLayoutAlgorithm::MeasureOnOffset(float mainSize)
{
    auto& info = gridLayoutInfo_;

    GridLayoutRangeSolver solver(&info, wrapper_);
    auto res = solver.FindStartingRow(mainGap_);

    info.startMainLineIndex_ = res.row;
    info.currentOffset_ = res.pos;
    // on init, gridMatrix_ is empty
    if (info.gridMatrix_.find(res.row) != info.gridMatrix_.end()) {
        info.startIndex_ = info.gridMatrix_[res.row][0];
    }

    GridIrregularFiller filler(&gridLayoutInfo_, wrapper_);
    filler.Fill({ crossLens_, mainSize - res.pos, crossGap_, mainGap_ });
}

void GridIrregularLayoutAlgorithm::MeasureOnJump(float mainSize)
{
    auto& info = gridLayoutInfo_;

    if (info.jumpIndex_ == LAST_ITEM) {
        info.jumpIndex_ = wrapper_->GetTotalChildCount() - 1;
    }

    if (info.scrollAlign_ == ScrollAlign::AUTO) {
        TransformAutoScrollAlign();
    }
    if (info.scrollAlign_ == ScrollAlign::NONE) {
        info.jumpIndex_ = EMPTY_JUMP_INDEX;
        return;
    }

    int32_t jumpLineIdx = FindJumpLineIdx(info.jumpIndex_);

    info.startMainLineIndex_ = jumpLineIdx;
    info.startIndex_ = info.jumpIndex_;
    info.jumpIndex_ = EMPTY_JUMP_INDEX;

    PrepareLineHeight(mainSize, jumpLineIdx);

    GridLayoutRangeSolver solver(&info, wrapper_);
    auto res = solver.FindRangeOnJump(jumpLineIdx, mainGap_);

    info.currentOffset_ = res.pos;
    info.startMainLineIndex_ = res.startRow;
    info.startIndex_ = info.gridMatrix_[res.startRow][0];
    info.endMainLineIndex_ = res.endRow;
    info.endIndex_ = res.endIdx;
}

void GridIrregularLayoutAlgorithm::FillWithItems(float targetLen)
{
    GridIrregularFiller filler(&gridLayoutInfo_, wrapper_);
    filler.Fill({ crossLens_, targetLen, crossGap_, mainGap_ });
}

bool GridIrregularLayoutAlgorithm::ReachedEnd() const
{
    const auto& info = gridLayoutInfo_;
    if (info.endIndex_ < wrapper_->GetTotalChildCount() - 1) {
        return false;
    }
    auto child = wrapper_->GetChildByIndex(info.endIndex_);
    CHECK_NULL_RETURN(child, false);

    float bottom = wrapper_->GetGeometryNode()->GetFrameSize().MainSize(info.axis_) - info.contentEndPadding_;
    float itemBot = info.axis_ == Axis::HORIZONTAL ? child->GetGeometryNode()->GetFrameRect().Right()
                                                   : child->GetGeometryNode()->GetFrameRect().Bottom();
    return itemBot <= bottom;
}

void GridIrregularLayoutAlgorithm::UpdateLayoutInfo()
{
    auto& info = gridLayoutInfo_;

    info.reachStart_ = info.startIndex_ == 0 && info.currentOffset_ >= 0;
    // GridLayoutInfo::reachEnd_ has a different meaning
    info.reachEnd_ = info.endIndex_ == wrapper_->GetTotalChildCount() - 1;

    info.offsetEnd_ = ReachedEnd();

    info.lastMainSize_ = wrapper_->GetGeometryNode()->GetContentSize().MainSize(info.axis_);
    info.totalHeightOfItemsInView_ = info.GetTotalHeightOfItemsInView(mainGap_);
}

void GridIrregularLayoutAlgorithm::LayoutChildren(float mainOffset)
{
    Alignment align = gridLayoutInfo_.axis_ == Axis::VERTICAL ? Alignment::TOP_CENTER : Alignment::CENTER_LEFT;
    const auto& positionProp = wrapper_->GetLayoutProperty()->GetPositionProperty();
    if (positionProp) {
        align = positionProp->GetAlignment().value_or(align);
    }

    const auto& padding = *wrapper_->GetGeometryNode()->GetPadding();
    mainOffset += gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? padding.left.value_or(0.0f) : padding.top.value_or(0.0f);
    auto crossPos = CalculateCrossPositions(padding);
    const auto& info = gridLayoutInfo_;

    for (int32_t r = info.startMainLineIndex_; r <= info.endMainLineIndex_; ++r) {
        const auto& row = info.gridMatrix_.at(r);
        for (int32_t c = 0; c < info.crossCount_; ++c) {
            if (row.find(c) == row.end() || row.at(c) == -1) {
                continue;
            }
            auto child = wrapper_->GetOrCreateChildByIndex(row.at(c));

            SizeF blockSize = info.axis_ == Axis::HORIZONTAL ? SizeF { crossLens_.at(c), info.lineHeightMap_.at(r) }
                                                             : SizeF { info.lineHeightMap_.at(r), crossLens_.at(c) };
            auto alignPos =
                Alignment::GetAlignPosition(blockSize, child->GetGeometryNode()->GetMarginFrameSize(), align);

            OffsetF offset = info.axis_ == Axis::HORIZONTAL ? OffsetF { mainOffset, crossPos[c] }
                                                            : OffsetF { crossPos[c], mainOffset };
            child->GetGeometryNode()->SetMarginFrameOffset(offset + alignPos);
            child->Layout();
        }
        // add mainGap below the item
        if (info.lineHeightMap_.find(r) == info.lineHeightMap_.end()) {
            continue;
        }
        mainOffset += info.lineHeightMap_.at(r) + mainGap_;
    }
}

std::vector<float> GridIrregularLayoutAlgorithm::CalculateCrossPositions(const PaddingPropertyF& padding)
{
    std::vector<float> res(gridLayoutInfo_.crossCount_, 0.0f);
    res[0] = gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? padding.top.value_or(0.0f) : padding.left.value_or(0.0f);
    for (int32_t i = 1; i < gridLayoutInfo_.crossCount_; ++i) {
        res[i] = res[i - 1] + crossLens_[i - 1] + crossGap_;
    }
    return res;
}

void GridIrregularLayoutAlgorithm::TransformAutoScrollAlign()
{
    auto& info = gridLayoutInfo_;
    if (info.jumpIndex_ > info.startIndex_ && info.jumpIndex_ < info.endIndex_) {
        info.scrollAlign_ = ScrollAlign::NONE;
    } else if (info.jumpIndex_ > info.endIndex_) {
        info.scrollAlign_ = ScrollAlign::START;
    } else {
        info.scrollAlign_ = ScrollAlign::END;
    }
}

int32_t GridIrregularLayoutAlgorithm::FindJumpLineIdx(int32_t jumpIdx)
{
    auto& info = gridLayoutInfo_;
    if (jumpIdx > info.startIndex_ && jumpIdx < info.endIndex_) {
        return info.FindItemInRange(jumpIdx);
    }
    if (jumpIdx > info.endIndex_) {
        // fill matrix up to jumpIndex_
        GridIrregularFiller filler(&info, wrapper_);
        info.UpdateStartIdxToLastItem();
        filler.FillMatrixOnly(jumpIdx);
        return info.endMainLineIndex_;
    }
    // find jumpIdx above startMainLine
    for (int r = info.startMainLineIndex_; r >= 0; --r) {
        auto row = info.gridMatrix_.at(r);
        for (auto it = row.rbegin(); it != row.rend(); ++it) {
            if (it->second == jumpIdx) {
                return r;
            }
        }
    }
    return -1;
}

void GridIrregularLayoutAlgorithm::PrepareLineHeight(float mainSize, int32_t jumpLineIdx)
{
    auto& info = gridLayoutInfo_;
    GridIrregularFiller filler(&info, wrapper_);
    switch (info.scrollAlign_) {
        case ScrollAlign::START:
            filler.Fill({ crossLens_, mainSize, crossGap_, mainGap_ });
            break;
        case ScrollAlign::CENTER: {
            GridIrregularFiller::FillParameters params { crossLens_, mainSize / 2.0f, crossGap_, mainGap_ };
            filler.Fill(params);
            filler.MeasureBackward(params, jumpLineIdx);
            break;
        }
        case ScrollAlign::END:
            filler.MeasureBackward({ crossLens_, mainSize, crossGap_, mainGap_ }, jumpLineIdx);
            break;
        default:
            break;
    }
}
} // namespace OHOS::Ace::NG
