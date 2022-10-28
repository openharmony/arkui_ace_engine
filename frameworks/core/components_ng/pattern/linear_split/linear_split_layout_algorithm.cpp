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

#include "core/components_ng/pattern/linear_split/linear_split_layout_algorithm.h"

#include <algorithm>
#include <cstdint>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void LinearSplitLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& parentIdeaSize = layoutConstraint->parentIdealSize;
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();
    OptionalSizeF realSize;
    do {
        // Use idea size first if it is valid.
        realSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (realSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            realSize.UpdateIllegalSizeWithCheck(parentIdeaSize);
        }
    } while (false);

    // Get Max Size for children.
    OptionalSizeF optionalMaxSize;
    optionalMaxSize.UpdateIllegalSizeWithCheck(maxSize);
    auto maxSizeT = optionalMaxSize.ConvertToSizeT();
    MinusPaddingToSize(padding, maxSizeT);

    const auto& childrenWrappers = layoutWrapper->GetAllChildrenWithBuild();

    auto childConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childConstraint.maxSize = layoutConstraint->selfIdealSize.ConvertToSizeT();

    float allocatedSize = 0.0f;
    float crossSize = 0.0f;
    // measure normal node.
    for (const auto& child : childrenWrappers) {
        child->Measure(childConstraint);
        allocatedSize += child->GetGeometryNode()->GetMarginFrameSize().Width();
        crossSize += child->GetGeometryNode()->GetMarginFrameSize().Height();
    }

    // measure self size.
    SizeF childTotalSize = { allocatedSize, crossSize };
    AddPaddingToSize(padding, childTotalSize);
    if (splitType_ == SplitType::ROW_SPLIT) {
        if (!layoutConstraint->selfIdealSize.Width()) {
            float width = std::max(minSize.Width(), childTotalSize.Width());
            if (maxSize.Width() > 0) {
                width = std::min(maxSize.Width(), width);
            }
            realSize.SetWidth(width);
        }
        if (!layoutConstraint->selfIdealSize.Height()) {
            realSize.SetHeight(maxSize.Height());
        }
        if (realSize.Height().has_value()) {
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize((realSize.ConvertToSizeT()));
    } else if (splitType_ == SplitType::COLUMN_SPLIT) {
        if (!layoutConstraint->selfIdealSize.Height()) {
            float height = std::min(maxSize.Height(), childTotalSize.Height());
            realSize.SetHeight(height);
        }
        if (!layoutConstraint->selfIdealSize.Width()) {
            realSize.SetWidth(maxSize.Width());
        }
        if (realSize.Height().has_value()) {
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize((realSize.ConvertToSizeT()));
    }
}

void LinearSplitLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    int32_t index = 0;
    float childOffsetMain = 0.0f;
    float childOffsetCross = 0.0f;
    float childTotalWidth = 0.0f;
    float childTotalHeight = 0.0f;
    for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
        childTotalWidth += item->GetGeometryNode()->GetFrameSize().Width();
        childTotalHeight += item->GetGeometryNode()->GetFrameSize().Height();
    }
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width() - padding.Width();
    auto parentHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - padding.Height();
    auto startPointX = (parentWidth - childTotalWidth) / 2;
    startPointX = startPointX < 0 ? 0.0f : startPointX;
    startPointX += padding.left.value_or(0.0f);
    auto startPointY = (parentHeight - childTotalHeight) / 2;
    startPointY = startPointY < 0 ? 0.0f : startPointY;
    startPointY += padding.top.value_or(0.0f);
    childOffsetMain += startPointX;
    childOffsetCross += startPointY;
    if (splitType_ == SplitType::ROW_SPLIT) {
        splitLength_ = parentHeight;
        for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
            if (padding.top.has_value()) {
                childOffsetCross = padding.top.value();
            }
            OffsetF offset = OffsetF(childOffsetMain, childOffsetCross);
            item->GetGeometryNode()->SetMarginFrameOffset(offset);
            childOffsetMain += item->GetGeometryNode()->GetFrameSize().Width();
            if (index < layoutWrapper->GetTotalChildCount() - 1) {
                childrenOffset_.emplace_back(OffsetF(childOffsetMain, childOffsetCross));
            }
            childOffsetMain += static_cast<float>(DEFAULT_SPLIT_HEIGHT);
            index++;
            item->Layout();
        }
    } else if (splitType_ == SplitType::COLUMN_SPLIT) {
        splitLength_ = parentWidth;
        for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
            if (padding.left.has_value()) {
                childOffsetMain = padding.left.value();
            }
            OffsetF offset = OffsetF(childOffsetMain, childOffsetCross);
            item->GetGeometryNode()->SetMarginFrameOffset(offset);
            childOffsetCross += item->GetGeometryNode()->GetFrameSize().Height();
            if (index < layoutWrapper->GetTotalChildCount() - 1) {
                childrenOffset_.emplace_back(OffsetF(childOffsetMain, childOffsetCross));
            }
            childOffsetCross += static_cast<float>(DEFAULT_SPLIT_HEIGHT);
            index++;
            item->Layout();
        }
    }
}

} // namespace OHOS::Ace::NG