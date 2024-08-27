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

#include "movingphoto_layout_algorithm.h"
#include "movingphoto_pattern.h"

namespace OHOS::Ace::NG {

void MovingPhotoLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::PerformLayout(layoutWrapper);
    auto contentOffset = layoutWrapper->GetGeometryNode()->GetContentOffset();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<MovingPhotoPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG || child->GetHostTag() == V2::COLUMN_ETS_TAG) {
            child->GetGeometryNode()->SetMarginFrameOffset({ contentOffset.GetX(), contentOffset.GetY() });
        }
        child->Layout();
    }
}

void MovingPhotoLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto contentSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    auto layoutProperty = DynamicCast<MovingPhotoLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<MovingPhotoPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG || child->GetHostTag() == V2::COLUMN_ETS_TAG) {
            auto layoutConstraintForImage = layoutConstraint;
            layoutConstraintForImage.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForImage.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForImage.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForImage);
        }
    }
    PerformMeasureSelf(layoutWrapper);
}

std::optional<SizeF> MovingPhotoLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto layoutSize = contentConstraint.selfIdealSize.IsValid() ? contentConstraint.selfIdealSize.ConvertToSizeT()
                                                                : contentConstraint.maxSize;
    return layoutSize;
}

} // namespace OHOS::Ace::NG