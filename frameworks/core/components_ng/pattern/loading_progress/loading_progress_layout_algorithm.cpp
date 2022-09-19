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

#include "core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h"

#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {
LoadingProgressLayoutAlgorithm::LoadingProgressLayoutAlgorithm() = default;

std::optional<SizeF> LoadingProgressLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    float height_ = (contentConstraint.selfIdealSize.Height()) ? contentConstraint.selfIdealSize.Height().value()
                                                               : contentConstraint.maxSize.Height();
    float width_ = (contentConstraint.selfIdealSize.Width()) ? contentConstraint.selfIdealSize.Width().value()
                                                             : contentConstraint.maxSize.Width();
    height_ = std::min(height_, contentConstraint.maxSize.Height());
    width_ = std::min(width_, contentConstraint.maxSize.Width());
    LOGD("LoadingProgressLayoutAlgorithm::MeasureContent: width_: %{public}fl ,height_: %{public}fl", width_, height_);
    return SizeF(width_, height_);
}

} // namespace OHOS::Ace::NG