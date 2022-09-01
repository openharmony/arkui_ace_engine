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

#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"

namespace OHOS::Ace::NG {
ProgressLayoutAlgorithm::ProgressLayoutAlgorithm() = default;

std::optional<SizeF> ProgressLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    LOGI("progress: ProgressLayoutAlgorithm::MeasureContent");
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto progressLayoutProperty = DynamicCast<ProgressLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(progressLayoutProperty, std::nullopt);
    const auto& progressDate = progressLayoutProperty->GetProgressDate();
    value_ = progressDate->GetValue().value_or(0);
    maxValue_ = progressDate->GetMaxValue().value_or(100);
    CHECK_NULL_RETURN(progressDate, std::nullopt);
    // auto width_ = progressDate->GetValue();
    float width_ = contentConstraint.maxSize.Width();
    if (contentConstraint.selfIdealSize.Width()){
        width_=contentConstraint.selfIdealSize.Width().value();
    }
    float height_ =  10;
    if (contentConstraint.selfIdealSize.Height()){
        width_=contentConstraint.selfIdealSize.Height().value();
    }
    constrainSize_ = SizeF(width_, height_);
    LOGI("progress: progressDate Width:%f , Height:%f ", constrainSize_->Width(), constrainSize_->Height());
    return constrainSize_;
}


double ProgressLayoutAlgorithm::GetValue() const
{
    return value_;
}
double ProgressLayoutAlgorithm::GetMaxValue() const
{
    return maxValue_;
}

std::optional<SizeF> ProgressLayoutAlgorithm::GetConstrainSize() const
{
    return constrainSize_;
}
} // namespace OHOS::Ace::NG
