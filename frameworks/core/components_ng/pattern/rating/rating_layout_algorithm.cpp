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

#include "core/common/container.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> RatingLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = host->GetPattern<RatingPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    if (pattern->UseContentModifier()) {
        if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            host->GetGeometryNode()->ResetContent();
        } else {
            host->GetGeometryNode()->Reset();
        }
        return std::nullopt;
    }
    // case 1: rating component is set with valid size, return contentConstraint.selfIdealSize as component size
    if (contentConstraint.selfIdealSize.IsValid() && contentConstraint.selfIdealSize.IsNonNegative()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_RETURN(ratingTheme, std::nullopt);
    auto ratingLayoutProperty = DynamicCast<RatingLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(ratingLayoutProperty, std::nullopt);
    auto stars = ratingLayoutProperty->GetStarsValue(ratingTheme->GetStarNum());
    CHECK_EQUAL_RETURN(stars, 0, std::nullopt);

    auto layoutPolicy = ratingLayoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value() && layoutPolicy->IsMatch()) {
        return LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy, stars);
    }
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
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<RatingPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->UseContentModifier()) {
        if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
            host->GetGeometryNode()->ResetContent();
        } else {
            host->GetGeometryNode()->Reset();
        }
        return;
    }
    // if layout size has not decided yet, resize target can not be calculated
    CHECK_NULL_VOID(layoutWrapper->GetGeometryNode()->GetContent());
    const auto& ratingSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    auto ratingLayoutProperty = DynamicCast<RatingLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(ratingLayoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    auto stars = ratingLayoutProperty->GetStarsValue(ratingTheme->GetStarNum());
    // step1: calculate single star size.
    CHECK_EQUAL_VOID(stars, 0);
    float singleWidth = ratingSize.Width() / static_cast<float>(stars);
    SizeF singleStarSize(singleWidth, ratingSize.Height());
    // step2: make 3 images canvas and set its dst size as single star size.
    CHECK_NULL_VOID(foregroundLoadingCtx_);
    foregroundLoadingCtx_->MakeCanvasImage(singleStarSize, true, ImageFit::FILL);
    CHECK_NULL_VOID(secondaryLoadingCtx_);
    secondaryLoadingCtx_->MakeCanvasImage(singleStarSize, true, ImageFit::FILL);
    CHECK_NULL_VOID(backgroundLoadingCtx_);
    backgroundLoadingCtx_->MakeCanvasImage(singleStarSize, true, ImageFit::FILL);
    if (pattern->IsNeedFocusStyle()) {
        backgroundFocusLoadingCtx_->MakeCanvasImage(singleStarSize, true, ImageFit::FILL);
    }
}

std::optional<SizeF> RatingLayoutAlgorithm::LayoutPolicyIsMatchParent(const LayoutConstraintF& contentConstraint,
    std::optional<NG::LayoutPolicyProperty> layoutPolicy, int32_t stars)
{
    float width = 0.0f;
    float height = 0.0f;
    if (layoutPolicy->IsWidthMatch()) {
        width = contentConstraint.parentIdealSize.Width().value_or(0.0f);
        if (!layoutPolicy->IsHeightMatch() && contentConstraint.selfIdealSize.Height()) {
            height = contentConstraint.selfIdealSize.Height().value();
        }
        if (!layoutPolicy->IsHeightMatch() && !contentConstraint.selfIdealSize.Height()) {
            height = width / static_cast<float>(stars);
        }
    }

    if (layoutPolicy->IsHeightMatch()) {
        height = contentConstraint.parentIdealSize.Height().value_or(0.0f);
        if (!layoutPolicy->IsWidthMatch() && contentConstraint.selfIdealSize.Width()) {
            width = contentConstraint.selfIdealSize.Width().value();
        }
        if (!layoutPolicy->IsWidthMatch() && !contentConstraint.selfIdealSize.Width()) {
            width = height * static_cast<float>(stars);
        }
    }
    return SizeF(width, height);
}

} // namespace OHOS::Ace::NG
