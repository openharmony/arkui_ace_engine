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

#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"
#include "core/components_ng/pattern/grid/irregular/layout_range_solver.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void GridIrregularLayout::Measure(LayoutWrapper* layoutWrapper)
{
    wrapper_ = layoutWrapper;
    auto props = DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());

    float mainSize = MeasureSelf(props);
    Init(props);

    /* alias */
    auto& info = gridLayoutInfo_;

    GridLayoutRangeSolver solver(&info, wrapper_);
    auto res = solver.FindStartingRow(mainGap_);

    firstRowPos_ = res.pos;
    info.startMainLineIndex_ = res.row;
    // on init, gridMatrix_ is empty
    if (info.gridMatrix_.find(res.row) != info.gridMatrix_.end()) {
        info.startIndex_ = info.gridMatrix_[res.row][0];
    }

    FillWithItems(mainSize + res.height);

    wrapper_->SetCacheCount(static_cast<int32_t>(props->GetCachedCountValue(1) * info.crossCount_));
}

void GridIrregularLayout::Layout(LayoutWrapper* layoutWrapper)
{
    wrapper_ = layoutWrapper;

    RemoveOutOfBoundChildren();

    float mainOffset = firstRowPos_ + gridLayoutInfo_.currentOffset_;
    LayoutChildren(mainOffset);

    UpdateLayoutInfo();
}

float GridIrregularLayout::MeasureSelf(const RefPtr<GridLayoutProperty>& props)
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

void GridIrregularLayout::Init(const RefPtr<GridLayoutProperty>& props)
{
    const auto& contentSize = wrapper_->GetGeometryNode()->GetContentSize();
    crossGap_ = GridUtils::GetCrossGap(props, contentSize, gridLayoutInfo_.axis_);
    mainGap_ = GridUtils::GetMainGap(props, contentSize, gridLayoutInfo_.axis_);

    std::string args;
    if (gridLayoutInfo_.axis_ == Axis::HORIZONTAL) {
        args = props->GetRowsTemplate().value_or("");
    } else {
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

void GridIrregularLayout::FillWithItems(float targetLen)
{
    // reset endIndex
    gridLayoutInfo_.endIndex_ = gridLayoutInfo_.startIndex_ - 1;
    gridLayoutInfo_.endMainLineIndex_ = gridLayoutInfo_.startMainLineIndex_;

    GridIrregularFiller filler(&gridLayoutInfo_, wrapper_);
    filler.Fill({ crossLens_, targetLen, crossGap_, mainGap_ });
}

bool GridIrregularLayout::ReachedEnd() const
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

void GridIrregularLayout::UpdateLayoutInfo()
{
    auto& info = gridLayoutInfo_;

    info.reachStart_ = info.currentOffset_ >= 0.0f;
    // GridLayoutInfo::reachEnd_ has a different meaning
    info.reachEnd_ = info.endIndex_ == wrapper_->GetTotalChildCount() - 1;

    info.offsetEnd_ = ReachedEnd();

    info.lastMainSize_ = wrapper_->GetGeometryNode()->GetContentSize().MainSize(info.axis_);
    info.totalHeightOfItemsInView_ = info.GetTotalHeightOfItemsInView(mainGap_);
}

void GridIrregularLayout::RemoveOutOfBoundChildren()
{
    wrapper_->RemoveAllChildInRenderTree();
    return;
    // try to optimize and remove only the children that are going out of bound
    int32_t idx = gridLayoutInfo_.startIndex_;
    // remove above
    while (idx > 0) {
        auto child = wrapper_->GetChildByIndex(--idx);
        if (!child || !child->IsActive()) {
            // no more children to remove
            break;
        }
        wrapper_->RemoveChildInRenderTree(idx);
    }

    // remove below
    idx = gridLayoutInfo_.endIndex_;
    while (idx < wrapper_->GetTotalChildCount() - 1) {
        auto child = wrapper_->GetChildByIndex(++idx);
        if (!child || !child->IsActive()) {
            // no more children to remove
            break;
        }
        wrapper_->RemoveChildInRenderTree(idx);
    }
}

void GridIrregularLayout::LayoutChildren(float mainOffset)
{
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

            if (!child) {
                TAG_LOGW(
                    AceLogTag::ACE_GRID, "Child not present at a valid index! r = %{public}d, c = %{public}d", r, c);
            }

            auto offset = info.axis_ == Axis::HORIZONTAL ? OffsetF { mainOffset, crossPos[c] }
                                                         : OffsetF { crossPos[c], mainOffset };
            child->GetGeometryNode()->SetMarginFrameOffset(offset);
            child->Layout();
        }
        // add mainGap below the item
        if (info.lineHeightMap_.find(r) == info.lineHeightMap_.end()) {
            continue;
        }
        mainOffset += info.lineHeightMap_.at(r) + mainGap_;
    }
}

std::vector<float> GridIrregularLayout::CalculateCrossPositions(const PaddingPropertyF& padding)
{
    std::vector<float> res(gridLayoutInfo_.crossCount_, 0.0f);
    res[0] = gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? padding.top.value_or(0.0f) : padding.left.value_or(0.0f);
    for (int32_t i = 1; i < gridLayoutInfo_.crossCount_; ++i) {
        res[i] = res[i - 1] + crossLens_[i - 1] + crossGap_;
    }
    return res;
}
} // namespace OHOS::Ace::NG
