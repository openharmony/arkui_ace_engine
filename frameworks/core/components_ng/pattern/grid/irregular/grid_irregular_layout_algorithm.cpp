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
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);

    // set content size
    MinusPaddingToSize(props->CreatePaddingAndBorder(), size);
    gridLayoutInfo_.contentEndPadding_ = ScrollableUtils::CheckHeightExpansion(props, gridLayoutInfo_.axis_);
    size.AddHeight(gridLayoutInfo_.contentEndPadding_);
    layoutWrapper->GetGeometryNode()->SetContentSize(size);

    Init(props);

    float targetLen = size.MainSize(gridLayoutInfo_.axis_) - gridLayoutInfo_.currentOffset_;
    targetLen -= gridLayoutInfo_.totalHeight_.value_or(0.0f);
    // fill content with new children and measure them
    GridIrregularFiller filler(&gridLayoutInfo_, wrapper_);
    float additionalLen = filler.Fill(targetLen, crossLens_);
    if (!gridLayoutInfo_.totalHeight_) {
        gridLayoutInfo_.totalHeight_ = 0.0f;
    }
    *gridLayoutInfo_.totalHeight_ += additionalLen;

    wrapper_->SetCacheCount(static_cast<int32_t>(props->GetCachedCountValue(1) * gridLayoutInfo_.crossCount_));
}

void GridIrregularLayout::Init(const RefPtr<GridLayoutProperty>& props)
{
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    auto crossSize = wrapper_->GetGeometryNode()->GetContentSize().CrossSize(gridLayoutInfo_.axis_);

    std::string args;
    if (gridLayoutInfo_.axis_ == Axis::HORIZONTAL) {
        crossGap_ = ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, crossSize).value_or(0.0f);
        mainGap_ = ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, crossSize).value_or(0.0f);
        args = props->GetRowsTemplate().value_or("");
    } else {
        mainGap_ = ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, crossSize).value_or(0.0f);
        crossGap_ = ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, crossSize).value_or(0.0f);
        args = props->GetColumnsTemplate().value_or("");
    }

    auto res = ParseTemplateArgs(GridUtils::ParseArgs(args), crossSize, crossGap_, wrapper_->GetTotalChildCount());

    crossLens_ = std::vector<float>(res.first.begin(), res.first.end());
    if (crossLens_.empty()) {
        crossLens_.push_back(crossSize);
    }

    if (res.second) {
        crossGap_ = 0.0f;
    }

    gridLayoutInfo_.crossCount_ = crossLens_.size();
}

void GridIrregularLayout::Layout(LayoutWrapper* layoutWrapper)
{
    wrapper_ = layoutWrapper;
}
} // namespace OHOS::Ace::NG