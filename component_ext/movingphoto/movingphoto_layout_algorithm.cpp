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
        if (child->GetHostTag() != V2::COLUMN_ETS_TAG) {
            continue;
        }
        auto childLayoutWrapper = host->GetChildByIndex(1);
        for (auto&& videoChild : childLayoutWrapper->GetAllChildrenWithBuild()) {
            if (videoChild->GetHostTag() == V2::COLUMN_ETS_TAG) {
                videoChild->GetGeometryNode()->SetMarginFrameOffset({ contentOffset.GetX(), contentOffset.GetY() });
            }
            videoChild->Layout();
        }
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
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            auto layoutConstraintForImage = layoutConstraint;
            layoutConstraintForImage.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForImage.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForImage.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForImage);
        } else if (child->GetHostTag() == V2::COLUMN_ETS_TAG) {
            auto layoutConstraintForColumn = layoutConstraint;
            auto columnSize = contentSize;
            float xmageHeight = 0;
            float ratio = 0;
            if (pattern->GetXmageModeStatus()) {
                pattern->GetXmageHeight();
                ratio = pattern->CalculateRatio(contentSize);
                xmageHeight = layoutProperty->GetXmageHeight().value();
                TAG_LOGI(AceLogTag::ACE_MOVING_PHOTO, "Measure xmageHeight.%{public}f, GetRatio.%{public}f",
                    xmageHeight, ratio);
                columnSize.SetHeight(contentSize.Height() - xmageHeight * ratio + 1);
            }
            layoutConstraintForColumn.UpdateSelfMarginSizeWithCheck(OptionalSizeF(columnSize));
            layoutConstraintForColumn.UpdateMaxSizeWithCheck(columnSize);
            layoutConstraintForColumn.UpdateMinSizeWithCheck(columnSize);
            child->Measure(layoutConstraintForColumn);
            auto childLayoutWrapper = host->GetChildByIndex(1);
            ChildMeasure(childLayoutWrapper, contentSize, xmageHeight * ratio, layoutConstraint);
            if (childLayoutWrapper) {
                PerformMeasureSelf(&*childLayoutWrapper);
            }
        }
    }
    PerformMeasureSelf(layoutWrapper);
}

void MovingPhotoLayoutAlgorithm::ChildMeasure(RefPtr<LayoutWrapper> childLayoutWrapper,
                                              SizeF contentSize, float xHeight, LayoutConstraintF layoutConstraint)
{
    for (auto&& columnChild : childLayoutWrapper->GetAllChildrenWithBuild()) {
        if (columnChild->GetHostTag() == V2::COLUMN_ETS_TAG) {
            auto layoutConstraintForVideo = layoutConstraint;
            auto videoSize = contentSize;
            videoSize.SetHeight(contentSize.Height() - xHeight);
            layoutConstraintForVideo.UpdateSelfMarginSizeWithCheck(OptionalSizeF(videoSize));
            layoutConstraintForVideo.UpdateMaxSizeWithCheck(videoSize);
            layoutConstraintForVideo.UpdateMinSizeWithCheck(videoSize);
            columnChild->Measure(layoutConstraintForVideo);
        }
    }
}

std::optional<SizeF> MovingPhotoLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto layoutSize = contentConstraint.selfIdealSize.IsValid() ? contentConstraint.selfIdealSize.ConvertToSizeT()
                                                                : contentConstraint.maxSize;
    return layoutSize;
}

} // namespace OHOS::Ace::NG