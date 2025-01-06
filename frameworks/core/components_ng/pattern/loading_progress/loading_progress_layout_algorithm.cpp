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

#include "core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components/progress/progress_theme.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
    
LoadingProgressLayoutAlgorithm::LoadingProgressLayoutAlgorithm() = default;

std::optional<SizeF> LoadingProgressLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = host->GetPattern<LoadingProgressPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->UseContentModifier()) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
            host->GetGeometryNode()->ResetContent();
        } else {
            host->GetGeometryNode()->Reset();
        }
        return std::nullopt;
    }
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_RETURN(progressTheme, std::nullopt);

    float defaultHeight = contentConstraint.percentReference.Height();
    float defaultWidth = contentConstraint.percentReference.Width();
    float defaultLoadingSize = progressTheme->GetLoadingDefaultSize().ConvertToPx();
    if (LessNotEqual(0.0f, defaultLoadingSize)) {
        defaultHeight = defaultLoadingSize;
        defaultWidth = defaultLoadingSize;
    }
    float height_ = (contentConstraint.selfIdealSize.Height()) ? contentConstraint.selfIdealSize.Height().value()
                                                               : defaultHeight;
    float width_ = (contentConstraint.selfIdealSize.Width()) ? contentConstraint.selfIdealSize.Width().value()
                                                             : defaultWidth;
    auto diameter = std::min(width_, height_);
    return SizeF(diameter, diameter);
}

} // namespace OHOS::Ace::NG
