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

#include "core/components_ng/pattern/data_panel/data_panel_layout_algorithm.h"

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
DataPanelLayoutAlgorithm::DataPanelLayoutAlgorithm() = default;

void DataPanelLayoutAlgorithm::OnReset() {}

std::optional<SizeF> DataPanelLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);

    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    if (contentConstraint.selfIdealSize.Width().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Width().value())) {
        auto width = contentConstraint.selfIdealSize.Width().value();
        auto height = contentConstraint.maxSize.Height();
        return SizeF(width, height);
    }
    if (contentConstraint.selfIdealSize.Height().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Height().value())) {
        auto width = contentConstraint.maxSize.Width();
        auto height = contentConstraint.selfIdealSize.Height().value();
        return SizeF(width, height);
    }
    return contentConstraint.maxSize;
}

} // namespace OHOS::Ace::NG
