/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_layout_base_algorithm.h"

namespace OHOS::Ace::NG {

void GridLayoutBaseAlgorithm::AdjustChildrenHeight(LayoutWrapper* layoutWrapper)
{
    gridLayoutInfo_.clearStretch_ = false;
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);
    const int32_t cacheCount = gridLayoutProperty->GetCachedCountValue(1);
    const int32_t startLine = std::max(gridLayoutInfo_.startMainLineIndex_ - cacheCount, 0);
    const int32_t endLine = gridLayoutInfo_.endMainLineIndex_ + cacheCount;
    for (int i = startLine; i <= endLine; i++) {
        if (IsIrregularLine(i)) {
            continue;
        }
        const auto& line = gridLayoutInfo_.gridMatrix_.find(i);
        if (line == gridLayoutInfo_.gridMatrix_.end() || line->second.empty()) {
            continue;
        }

        auto lineHeightIter = gridLayoutInfo_.lineHeightMap_.find(i);
        if (lineHeightIter == gridLayoutInfo_.lineHeightMap_.end()) {
            continue;
        }
        const float lineHeight = lineHeightIter->second;

        for (auto iter = line->second.begin(); iter != line->second.end(); iter++) {
            const int32_t itemIndex = iter->second;
            auto child = layoutWrapper->GetChildByIndex(itemIndex);
            if (!child) {
                break;
            }
            auto childLayoutProperty = AceType::DynamicCast<GridItemLayoutProperty>(child->GetLayoutProperty());
            if (!childLayoutProperty) {
                break;
            }
            auto childConstraint = childLayoutProperty->GetLayoutConstraint();
            if (!childLayoutProperty->GetNeedStretch() &&
                childConstraint->selfIdealSize.MainSize(gridLayoutInfo_.axis_).has_value()) {
                continue;
            }

            auto childFrameSize = child->GetGeometryNode()->GetFrameSize();
            if (GreatOrEqual(childFrameSize.MainSize(gridLayoutInfo_.axis_), lineHeight)) {
                continue;
            }
            childConstraint->selfIdealSize.SetMainSize(lineHeight, gridLayoutInfo_.axis_);
            childLayoutProperty->SetNeedStretch(true);
            childLayoutProperty->SetAxis(gridLayoutInfo_.axis_);
            child->Measure(childConstraint);
        }
    }
}
} // namespace OHOS::Ace::NG
