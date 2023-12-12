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

#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"
#include "core/components_ng/pattern/grid/irregular/layout_range_solver.h"
#include "core/components_ng/pattern/scrollable/scrollable_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void GridIrregularLayout::Measure(LayoutWrapper* layoutWrapper)
{
    wrapper_ = layoutWrapper;
    auto props = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());

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

    Init(props);

    float targetLen = size.MainSize(gridLayoutInfo_.axis_) - gridLayoutInfo_.currentOffset_;
    targetLen -= gridLayoutInfo_.totalHeight_.value_or(0.0f);

    // fill content with new children and measure them
    GridIrregularFiller filler(&gridLayoutInfo_, wrapper_);
    float additionalLen = filler.Fill(targetLen, crossLens_, crossGap_);
    if (!gridLayoutInfo_.totalHeight_) {
        gridLayoutInfo_.totalHeight_ = 0.0f;
    }
    *gridLayoutInfo_.totalHeight_ += additionalLen;

    wrapper_->SetCacheCount(static_cast<int32_t>(props->GetCachedCountValue(1) * gridLayoutInfo_.crossCount_));
}

void GridIrregularLayout::Init(const RefPtr<GridLayoutProperty>& props)
{
    auto crossSize = wrapper_->GetGeometryNode()->GetContentSize().CrossSize(gridLayoutInfo_.axis_);
    crossGap_ = GridUtils::GetCrossGap(props, wrapper_->GetGeometryNode()->GetContentSize(), gridLayoutInfo_.axis_);
    mainGap_ = GridUtils::GetMainGap(props, wrapper_->GetGeometryNode()->GetContentSize(), gridLayoutInfo_.axis_);

    std::string args;
    if (gridLayoutInfo_.axis_ == Axis::HORIZONTAL) {
        args = props->GetRowsTemplate().value_or("");
    } else {
        args = props->GetColumnsTemplate().value_or("");
    }

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

void GridIrregularLayout::Layout(LayoutWrapper* layoutWrapper)
{
    wrapper_ = layoutWrapper;
    // handle layout backward separately??

    GridLayoutRangeSolver solver(&gridLayoutInfo_, wrapper_);
    float firstRowPos = solver.FindLayoutRange(mainGap_);

    RemoveOutOfBoundChildren();

    // layout children
    float mainOffset = firstRowPos + gridLayoutInfo_.currentOffset_;
    auto crossPos = CalculateCrossPositions();
    for (int32_t r = gridLayoutInfo_.startMainLineIndex_; r <= gridLayoutInfo_.endMainLineIndex_; ++r) {
        const auto& row = gridLayoutInfo_.gridMatrix_.at(r);
        for (int32_t c = 0; c < gridLayoutInfo_.crossCount_; ++c) {
            if (row.at(c) == -1) {
                // block of an irregular item
                continue;
            }
            auto child = wrapper_->GetChildByIndex(row.at(c));

            if (!child) {
                TAG_LOGW(
                    AceLogTag::ACE_GRID, "Child not present at a valid index! r = %{public}d, c = %{public}d", r, c);
            }

            auto offset = gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? OffsetF { mainOffset, crossPos[c] }
                                                                    : OffsetF { crossPos[c], mainOffset };
            child->GetGeometryNode()->SetMarginFrameOffset(offset);
            // re-layout previously hidden nodes
            if (!child->IsActive()) {
                child->Layout();
            }
        }
        mainOffset += gridLayoutInfo_.lineHeightMap_[r] + mainGap_;
    }
}

void GridIrregularLayout::RemoveOutOfBoundChildren()
{
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

std::vector<float> GridIrregularLayout::CalculateCrossPositions()
{
    std::vector<float> res(gridLayoutInfo_.crossCount_, 0.0f);
    const auto& padding = *wrapper_->GetGeometryNode()->GetPadding();
    res[0] = gridLayoutInfo_.axis_ == Axis::HORIZONTAL ? padding.top.value_or(0) : padding.left.value_or(0);
    for (int32_t i = 1; i < gridLayoutInfo_.crossCount_; ++i) {
        res[i] = res[i - 1] + crossLens_[i - 1] + crossGap_;
    }
    return res;
}
} // namespace OHOS::Ace::NG