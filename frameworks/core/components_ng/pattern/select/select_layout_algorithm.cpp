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

#include "core/components_ng/pattern/select/select_layout_algorithm.h"

#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
void SelectLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);

    auto layoutProps = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateAlignment(Alignment::CENTER);
    auto childConstraint = layoutProps->CreateChildConstraint();

    // Measure child row to get row height and width.
    auto rowWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(rowWrapper);
    rowWrapper->Measure(childConstraint);
    auto rowGeometry = rowWrapper->GetGeometryNode();
    CHECK_NULL_VOID(rowGeometry);
    auto rowWidth = rowGeometry->GetMarginFrameSize().Width();
    auto rowHeight = rowGeometry->GetMarginFrameSize().Height();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto selectWidth = rowWidth;
    auto defaultHeight = static_cast<float>(theme->GetSelectMinHeight().ConvertToPx());
    auto selectHeight = std::max(defaultHeight, rowHeight);

    auto geometryNode = layoutWrapper->GetGeometryNode();
    const auto& calcLayoutConstraint = layoutProps->GetCalcLayoutConstraint();
    if (calcLayoutConstraint && calcLayoutConstraint->selfIdealSize.has_value()) {
        auto selfIdealSize = calcLayoutConstraint->selfIdealSize;
        auto selfIdealWidth = (selfIdealSize->Width().value_or(CalcLength(selectWidth))).GetDimension();
        auto selfIdealHeight = (selfIdealSize->Height().value_or(CalcLength(selectHeight))).GetDimension();
        geometryNode->SetFrameSize(
            SizeF(static_cast<float>(selfIdealWidth.ConvertToPx()), static_cast<float>(selfIdealHeight.ConvertToPx())));
    } else {
        geometryNode->SetFrameSize(SizeF(selectWidth, selectHeight));
    }
}
} // namespace OHOS::Ace::NG
