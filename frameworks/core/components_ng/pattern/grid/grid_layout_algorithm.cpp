/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"

#ifdef NG_BUILD
#include "ace_shell/shell/common/window_manager.h"
#endif

namespace OHOS::Ace::NG {

void GridLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);

    // Step1: Decide size of Grid
    Axis axis = layoutController_->isVertical_ ? Axis::VERTICAL : Axis::HORIZONTAL;
    auto idealSize = CreateIdealSize(gridLayoutProperty->GetLayoutConstraint().value(), axis,
        gridLayoutProperty->GetMeasureType());
    if (GreatOrEqual(GetMainAxisSize(idealSize, axis), Infinity<float>())) {
        LOGE("size of main axis value is infinity, please check");
        return;
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    MinusPaddingToSize(gridLayoutProperty->CreatePaddingPropertyF(), idealSize);

    // Step2: Measure children that can be displayed in viewport of Grid
    float mainSize = GetMainAxisSize(idealSize, axis);
    float crossSize = GetCrossAxisSize(idealSize, axis);
    layoutController_->FillGridViewportAndMeasureChildren(mainSize, crossSize, gridLayoutProperty, layoutWrapper);
    layoutController_->StripItemsOutOfViewport();
}

void GridLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingPropertyF();
    MinusPaddingToSize(padding, size);
    auto childFrameOffset =
        OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f) + layoutController_->currentOffset_);
    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    float crossFrWidth =
        GetCrossAxisSize(size, layoutController_->GetAxis()) / static_cast<float>(layoutController_->crossCount_);

    // For e.g, when a vertical grid has two [GridItem] in first row, [gridMatrix_] is like {[0: {[0: 1fr], [1: 2fr]}]}
    // TODO: Support horizontal Grid
    float prevLineHeight = 0.0f;
    for (const auto& line : layoutController_->gridMatrix_) {
        auto offset = childFrameOffset + OffsetF(0.0, prevLineHeight);
        if (line.second.empty()) {
            LOGE("line %{public}d should not be empty, please check.", line.first);
            break;
        }

        // Step1. Layout the first [GridItem]
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(line.second.begin()->first);
        wrapper->GetGeometryNode()->SetFrameOffset(offset);
        wrapper->Layout(parentOffset);
        float prevItemCrossSize = static_cast<float>(line.second.begin()->second) * crossFrWidth;

        // Step2. Layout other [GridItem]
        for (auto iter = ++line.second.begin(); iter != line.second.end(); iter++) {
            offset += OffsetF(prevItemCrossSize, 0.0);
            wrapper = layoutWrapper->GetOrCreateChildByIndex(iter->first);
            wrapper->GetGeometryNode()->SetFrameOffset(offset);
            wrapper->Layout(parentOffset);
            prevItemCrossSize = static_cast<float>(iter->second) * crossFrWidth;
        }
        prevLineHeight += layoutController_->lineHeightMap_[line.first];
    }
    layoutController_->markNeedRenderTask_();
}

} // namespace OHOS::Ace::NG