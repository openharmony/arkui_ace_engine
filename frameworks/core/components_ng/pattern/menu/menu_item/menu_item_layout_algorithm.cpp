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

#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
void MenuItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    horInterval_ = static_cast<float>(theme->GetMenuIconPadding().ConvertToPx()) -
        static_cast<float>(theme->GetOutPadding().ConvertToPx());
    auto props = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(props);
    auto layoutConstraint = props->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    float maxRowWidth = layoutConstraint->maxSize.Width() - horInterval_ * 2.0;
    float minRowWidth = layoutConstraint->minSize.Width();

    auto childConstraint = props->CreateChildConstraint();
    // set item min height
    auto minItemHeight = static_cast<float>(theme->GetOptionMinHeight().ConvertToPx());
    childConstraint.minSize.SetHeight(minItemHeight);
    // measure right row
    childConstraint.maxSize.SetWidth(maxRowWidth);
    childConstraint.percentReference.SetWidth(maxRowWidth);
    float rightRowWidth = 0.0f;
    auto rightRow = layoutWrapper->GetOrCreateChildByIndex(1);
    if (rightRow) {
        rightRow->Measure(childConstraint);
        rightRowWidth = rightRow->GetGeometryNode()->GetMarginFrameSize().Width();
    }
    // measure left row
    // left row constraint width = total constraint width - right row width - space
    auto middleSpace = static_cast<float>(theme->GetIconContentPadding().ConvertToPx());
    maxRowWidth -= rightRowWidth + middleSpace;
    childConstraint.maxSize.SetWidth(maxRowWidth);
    childConstraint.percentReference.SetWidth(maxRowWidth);
    auto leftRow = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(leftRow);
    leftRow->Measure(childConstraint);
    float leftRowWidth = leftRow->GetGeometryNode()->GetMarginFrameSize().Width();

    if (!layoutConstraint->selfIdealSize.Width().has_value()) {
        float contentWidth = leftRowWidth + rightRowWidth + horInterval_ * 2.0 + middleSpace;
        layoutConstraint->selfIdealSize.SetWidth(std::max(minRowWidth, contentWidth));
        props->UpdateLayoutConstraint(layoutConstraint.value());
    }
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
}

void MenuItemLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto itemSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto itemHeight = itemSize.Height();

    auto leftRow = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(leftRow);
    auto leftRowSize = leftRow->GetGeometryNode()->GetFrameSize();
    leftRow->GetGeometryNode()->SetMarginFrameOffset(OffsetF(horInterval_, (itemHeight - leftRowSize.Height()) / 2.0));
    leftRow->Layout();

    auto rightRow = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(rightRow);
    auto rightRowSize = rightRow->GetGeometryNode()->GetFrameSize();
    rightRow->GetGeometryNode()->SetMarginFrameOffset(
        OffsetF(layoutWrapper->GetGeometryNode()->GetFrameSize().Width() - horInterval_ -
                    rightRow->GetGeometryNode()->GetFrameSize().Width(),
            (itemHeight - rightRowSize.Height()) / 2.0));
    rightRow->Layout();
}
} // namespace OHOS::Ace::NG
