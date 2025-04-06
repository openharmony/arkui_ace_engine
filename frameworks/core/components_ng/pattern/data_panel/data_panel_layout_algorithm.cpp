/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/data_panel/data_panel_layout_algorithm.h"

#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"

namespace OHOS::Ace::NG {
DataPanelLayoutAlgorithm::DataPanelLayoutAlgorithm() = default;

void DataPanelLayoutAlgorithm::OnReset() {}

std::optional<SizeF> DataPanelLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = host->GetPattern<DataPanelPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->UseContentModifier()) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            host->GetGeometryNode()->ResetContent();
        } else {
            host->GetGeometryNode()->Reset();
        }
        return std::nullopt;
    }
    // 1.If user set the width and height, use the selfIdealSize.
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }

    auto width = contentConstraint.percentReference.Width();
    auto height = contentConstraint.percentReference.Height();
    bool infWidth = GreaterOrEqualToInfinity(width);
    bool infHeight = GreaterOrEqualToInfinity(height);

    // 2.If user set width only, use selfWidth and height of maxSize.
    // If the height is infinite, set the min of selfWidth and infinite.
    if (contentConstraint.selfIdealSize.Width().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Width().value())) {
        auto selfWidth = contentConstraint.selfIdealSize.Width().value();
        if (infHeight) {
            height = std::min(selfWidth, height);
        }
        return SizeF(selfWidth, height);
    }

    // 3.If user set height only, use selfHeight and width of maxSize.
    // If the width is infinite, set the min of selfHeight and infinite.
    if (contentConstraint.selfIdealSize.Height().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Height().value())) {
        auto selfHeight = contentConstraint.selfIdealSize.Height().value();
        if (infWidth) {
            width = std::min(width, selfHeight);
        }
        return SizeF(width, selfHeight);
    }

    // 4.If width and height are both infinite, use the root size as constraint.
    if (infWidth && infHeight) {
        auto minSize = std::min(PipelineContext::GetCurrentRootWidth(), PipelineContext::GetCurrentRootHeight());
        return SizeF(minSize, minSize);
    }

    // 5.If the width or height is infinite, use the min of them as the constraint.
    if (infWidth || infHeight) {
        auto minSize = std::min(width, height);
        return SizeF(minSize, minSize);
    }

    // 6.Otherwise use the maxSize
    return contentConstraint.percentReference;
}

} // namespace OHOS::Ace::NG
