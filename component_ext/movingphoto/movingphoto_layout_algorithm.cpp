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
namespace {
constexpr int32_t ROUND_XMAGE_MODE_VALUE = 0;
constexpr int32_t ROUND_XMAGE_PIXEL_GAP = 2;
}

void MovingPhotoLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::PerformLayout(layoutWrapper);
    auto contentOffset = layoutWrapper->GetGeometryNode()->GetContentOffset();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<MovingPhotoPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    SizeF xmageOffset = GetXmageLayoutOffset(layoutWrapper);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        CHECK_NULL_VOID(child);
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            child->GetGeometryNode()->SetMarginFrameOffset({ contentOffset.GetX(), contentOffset.GetY() });
        } else if (child->GetHostTag() == V2::COLUMN_ETS_TAG) {
            child->GetGeometryNode()->SetMarginFrameOffset(
                { contentOffset.GetX() + xmageOffset.Width(), contentOffset.GetY() + xmageOffset.Height() });
        }
        child->Layout();
        if (child->GetHostTag() != V2::COLUMN_ETS_TAG) {
            continue;
        }
        int32_t childCount = host->GetTotalChildCount();
        CHECK_NULL_VOID(childCount >= 1);
        auto childLayoutWrapper = host->GetChildByIndex(childCount - 1);
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
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<MovingPhotoPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->SetXmagePosition();
    if (pattern->GetXmageModeStatus() && pattern->GetXmageModeValue() != ROUND_XMAGE_MODE_VALUE) {
        MeasureInXmageMode(layoutWrapper);
        return;
    }
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        CHECK_NULL_VOID(child);
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            auto layoutConstraintForImage = layoutConstraint;
            layoutConstraintForImage.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForImage.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForImage.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForImage);
        } else if (child->GetHostTag() == V2::COLUMN_ETS_TAG) {
            auto layoutConstraintForColumn = layoutConstraint;
            layoutConstraintForColumn.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForColumn.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForColumn.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForColumn);
            int32_t childCount = host->GetTotalChildCount();
            CHECK_NULL_VOID(childCount >= 1);
            auto childLayoutWrapper = host->GetChildByIndex(childCount - 1);
            ChildMeasure(childLayoutWrapper, contentSize, layoutConstraint);
            if (childLayoutWrapper) {
                PerformMeasureSelf(&*childLayoutWrapper);
            }
        }
    }
    PerformMeasureSelf(layoutWrapper);
}

void MovingPhotoLayoutAlgorithm::ChildMeasure(RefPtr<LayoutWrapper> childLayoutWrapper,
                                              SizeF contentSize, LayoutConstraintF layoutConstraint)
{
    for (auto&& columnChild : childLayoutWrapper->GetAllChildrenWithBuild()) {
        if (columnChild->GetHostTag() == V2::COLUMN_ETS_TAG) {
            auto layoutConstraintForVideo = layoutConstraint;
            layoutConstraintForVideo.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForVideo.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForVideo.UpdateMinSizeWithCheck(contentSize);
            columnChild->Measure(layoutConstraintForVideo);
        }
    }
}


void MovingPhotoLayoutAlgorithm::MeasureInXmageMode(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto contentSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    auto layoutProperty = DynamicCast<MovingPhotoLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = DynamicCast<MovingPhotoPattern>(host->GetPattern());
    CHECK_NULL_VOID(pattern);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        CHECK_NULL_VOID(child);
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            auto layoutConstraintForImage = layoutConstraint;
            layoutConstraintForImage.UpdateSelfMarginSizeWithCheck(OptionalSizeF(contentSize));
            layoutConstraintForImage.UpdateMaxSizeWithCheck(contentSize);
            layoutConstraintForImage.UpdateMinSizeWithCheck(contentSize);
            child->Measure(layoutConstraintForImage);
        } else if (child->GetHostTag() == V2::COLUMN_ETS_TAG) {
            auto layoutConstraintForColumn = layoutConstraint;
            auto columnSize = contentSize;
            SizeF xmageOffsetRatio = pattern->CalculateXmageOffsetRatio(contentSize);
            SizeF imageSize = layoutProperty->GetImageSize().value();
            columnSize.SetHeight(imageSize.Height() * xmageOffsetRatio.Height() + ROUND_XMAGE_PIXEL_GAP);
            columnSize.SetWidth(imageSize.Width() * xmageOffsetRatio.Width() + ROUND_XMAGE_PIXEL_GAP);
            layoutConstraintForColumn.UpdateSelfMarginSizeWithCheck(OptionalSizeF(columnSize));
            layoutConstraintForColumn.UpdateMaxSizeWithCheck(columnSize);
            layoutConstraintForColumn.UpdateMinSizeWithCheck(columnSize);
            child->Measure(layoutConstraintForColumn);
            int32_t childCount = host->GetTotalChildCount();
            CHECK_NULL_VOID(childCount >= 1);
            auto childLayoutWrapper = host->GetChildByIndex(childCount - 1);
            ChildMeasureInXmage(childLayoutWrapper, contentSize, imageSize, xmageOffsetRatio, layoutConstraint);
            if (childLayoutWrapper) {
                PerformMeasureSelf(&*childLayoutWrapper);
            }
        }
    }
    PerformMeasureSelf(layoutWrapper);
}

void MovingPhotoLayoutAlgorithm::ChildMeasureInXmage(RefPtr<LayoutWrapper> childLayoutWrapper, SizeF contentSize,
    SizeF imageSize, SizeF xmageRatio, LayoutConstraintF layoutConstraint)
{
    for (auto&& columnChild : childLayoutWrapper->GetAllChildrenWithBuild()) {
        CHECK_NULL_VOID(columnChild);
        if (columnChild->GetHostTag() == V2::COLUMN_ETS_TAG) {
            auto layoutConstraintForVideo = layoutConstraint;
            auto videoSize = contentSize;
            videoSize.SetHeight(imageSize.Height() * xmageRatio.Height() + ROUND_XMAGE_PIXEL_GAP);
            videoSize.SetWidth(imageSize.Width() * xmageRatio.Width() + ROUND_XMAGE_PIXEL_GAP);
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

SizeF MovingPhotoLayoutAlgorithm::GetXmageLayoutOffset(LayoutWrapper* layoutWrapper)
{
    SizeF ret = SizeF(0, 0);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, ret);
    auto pattern = DynamicCast<MovingPhotoPattern>(host->GetPattern());
    CHECK_NULL_RETURN(pattern, ret);
    if (pattern->GetXmageModeStatus() && (pattern->GetXmageModeValue() == ROUND_XMAGE_MODE_VALUE)) {
        auto contentSize = layoutWrapper->GetGeometryNode()->GetContentSize();
        auto layoutProperty = DynamicCast<MovingPhotoLayoutProperty>(layoutWrapper->GetLayoutProperty());
        CHECK_NULL_RETURN(layoutProperty, ret);
        if (!layoutProperty->HasXmageOffset()) {
            return ret;
        }
        SizeF xmageOffset = layoutProperty->GetXmageOffset().value();
        SizeF xmageOffsetRatio = pattern->CalculateXmageOffsetRatio(contentSize);
        ret = SizeF(xmageOffset.Width() * xmageOffsetRatio.Width() - 1,
                    xmageOffset.Height() * xmageOffsetRatio.Height() - 1);
    }
    return ret;
}
} // namespace OHOS::Ace::NG