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
#include "core/components_ng/pattern/rating/rating_layout_algorithm.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/rating/rating_layout_property.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> RatingLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // case 1: rating component is set with valid size, return contentConstraint.selfIdealSize as component size
    if (contentConstraint.selfIdealSize.IsValid() && contentConstraint.selfIdealSize.IsNonNegative()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_RETURN(ratingTheme, std::nullopt);
    auto ratingLayoutProperty = DynamicCast<RatingLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto stars =
        ratingLayoutProperty->GetStarsValue(RatingPattern::GetStarNumFromTheme().value_or(DEFAULT_RATING_STAR_NUM));
    // case 2: rating component is only set with valid width or height
    // return height = width / stars, or width = height * stars.
    if (contentConstraint.selfIdealSize.Width() && !contentConstraint.selfIdealSize.Height()) {
        auto width = contentConstraint.selfIdealSize.Width().value();
        return SizeF(width, width / static_cast<float>(stars));
    }
    if (!contentConstraint.selfIdealSize.Width() && contentConstraint.selfIdealSize.Height()) {
        auto height = contentConstraint.selfIdealSize.Height().value();
        return SizeF(height * static_cast<float>(stars), height);
    }

    // case 3: Using the theme's height and width by default if rating component is not set size.
    SizeF componentSize;
    bool indicator = ratingLayoutProperty->GetIndicator().value_or(false);
    // Rating use the mini size specified in the theme, when it is used as indicator.
    auto height =
        indicator ? ratingTheme->GetRatingMiniHeight().ConvertToPx() : ratingTheme->GetRatingHeight().ConvertToPx();
    componentSize.SetHeight(static_cast<float>(height));
    componentSize.SetWidth(static_cast<float>(height * stars));
    return contentConstraint.Constrain(componentSize);
}

void RatingLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Layout(layoutWrapper);
    // if layout size has not decided yet, resize target can not be calculated
    CHECK_NULL_VOID(layoutWrapper->GetGeometryNode()->GetContent());
    const auto& ratingSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    auto ratingLayoutProperty = DynamicCast<RatingLayoutProperty>(layoutWrapper->GetLayoutProperty());

    // step1: calculate single star size.
    float singleWidth =
        ratingSize.Width() / static_cast<float>(ratingLayoutProperty->GetStars().value_or(
                                 RatingPattern::GetStarNumFromTheme().value_or(DEFAULT_RATING_STAR_NUM)));
    SizeF singleStarSize(singleWidth, ratingSize.Height());

    // step2: make 3 images canvas and set its dst size as single star size.
    foregroundLoadingCtx_->MakeCanvasImage(singleStarSize, true, ImageFit::FILL);
    secondaryLoadingCtx_->MakeCanvasImage(singleStarSize, true, ImageFit::FILL);
    backgroundLoadingCtx_->MakeCanvasImage(singleStarSize, true, ImageFit::FILL);
}

} // namespace OHOS::Ace::NG
