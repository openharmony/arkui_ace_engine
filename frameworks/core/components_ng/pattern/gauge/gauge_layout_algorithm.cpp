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

#include "core/components_ng/pattern/gauge/gauge_layout_algorithm.h"

#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
GaugeLayoutAlgorithm::GaugeLayoutAlgorithm() = default;

void GaugeLayoutAlgorithm::OnReset() {}

std::optional<SizeF> GaugeLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto themeManager = pipeline->GetThemeManager();
    auto gaugeTheme = themeManager->GetTheme<ProgressTheme>();
    float defaultThickness = gaugeTheme->GetTrackWidth().ConvertToPx();
    if ((NearEqual(contentConstraint.maxSize.Width(), Size::INFINITE_SIZE))) {
        float defaultWidth = gaugeTheme->GetTrackWidth().ConvertToPx();
        defaultWidth = std::min(defaultWidth, contentConstraint.maxSize.Width());
        return SizeF(defaultWidth, defaultThickness);
    }
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    if (contentConstraint.selfIdealSize.Width().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Width().value())) {
        auto width = contentConstraint.selfIdealSize.Width().value();
        return SizeF(width, width);
    }
    if (contentConstraint.selfIdealSize.Height().has_value() &&
        NonNegative(contentConstraint.selfIdealSize.Height().value())) {
        auto height = contentConstraint.selfIdealSize.Height().value();
        return SizeF(height, height);
    }
    auto len = std::min(contentConstraint.maxSize.Height(), contentConstraint.maxSize.Width());
    return SizeF(len, len);
}

} // namespace OHOS::Ace::NG