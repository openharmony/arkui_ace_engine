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
#include "core/components_ng/pattern/rating/rating_pattern.h"

#include <cstdint>

#include "core/components_ng/pattern/rating/rating_paint_method.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
constexpr int32_t RATING_IMAGE_SUCCESS_CODE = 0b111;
constexpr int32_t DEFAULT_RATING_STAR_NUM = 5;

void RatingPattern::CheckImageInfoHasChangedOrNot(
    int32_t imageFlag, const ImageSourceInfo& sourceInfo, const std::string& lifeCycleTag)
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(ratingLayoutProperty);
    switch (imageFlag) {
        case 0b001:
            if (ratingLayoutProperty->GetForegroundImageSourceInfo() != sourceInfo) {
                LOGW("Foreground image sourceInfo does not match, ignore current %{private}s callback. "
                     "current: %{private}s vs callback's: %{private}s",
                    lifeCycleTag.c_str(), ratingLayoutProperty->GetForegroundImageSourceInfo()->ToString().c_str(),
                    sourceInfo.ToString().c_str());
                return;
            }
            if (lifeCycleTag == "ImageDataFailed") {
                LOGE("Rating load foreground image failed");
            }
            break;
        case 0b010:
            if (ratingLayoutProperty->GetSecondaryImageSourceInfo() != sourceInfo) {
                LOGW("Secondary image sourceInfo does not match, ignore current %{private}s callback. "
                     "current: %{private}s vs callback's: %{private}s",
                    lifeCycleTag.c_str(), ratingLayoutProperty->GetSecondaryImageSourceInfo()->ToString().c_str(),
                    sourceInfo.ToString().c_str());
                return;
            }
            if (lifeCycleTag == "ImageDataFailed") {
                LOGE("Rating load secondary image failed");
            }
            break;
        case 0b100:
            if (ratingLayoutProperty->GetBackgroundImageSourceInfo() != sourceInfo) {
                LOGW("Background image sourceInfo does not match, ignore current %{private}s callback. "
                     "current: %{private}s vs callback's: %{private}s",
                    lifeCycleTag.c_str(), ratingLayoutProperty->GetBackgroundImageSourceInfo()->ToString().c_str(),
                    sourceInfo.ToString().c_str());
                return;
            }
            if (lifeCycleTag == "ImageDataFailed") {
                LOGE("Rating load background image failed");
            }
            break;
        default:
            break;
    }
}

LoadSuccessNotifyTask RatingPattern::CreateLoadSuccessCallback(int32_t imageFlag)
{
    auto task = [weak = WeakClaim(this), imageFlag](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // check image info has changed or not
        pattern->CheckImageInfoHasChangedOrNot(imageFlag, sourceInfo, "ImageDataSuccess");
        pattern->OnImageLoadSuccess(imageFlag);
    };
    return task;
}

DataReadyNotifyTask RatingPattern::CreateDataReadyCallback(int32_t imageFlag)
{
    auto task = [weak = WeakClaim(this), imageFlag](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // check image info has changed or not
        pattern->CheckImageInfoHasChangedOrNot(imageFlag, sourceInfo, "ImageDataReady");
        pattern->OnImageDataReady(imageFlag);
    };
    return task;
}

LoadFailNotifyTask RatingPattern::CreateLoadFailCallback(int32_t imageFlag)
{
    auto task = [weak = WeakClaim(this), imageFlag](const ImageSourceInfo& sourceInfo) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // check image info has changed or not
        pattern->CheckImageInfoHasChangedOrNot(imageFlag, sourceInfo, "ImageDataFailed");
    };
    return task;
}

void RatingPattern::OnImageLoadSuccess(int32_t imageFlag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (imageFlag == 0b001) {
        foregroundImageCanvas_ = foregroundImageLoadingCtx_->GetCanvasImage();
        singleStarRect_ = foregroundImageLoadingCtx_->GetSrcRect();
        singleStarDstRect_ = foregroundImageLoadingCtx_->GetDstRect();
        imageSuccessStateCode_ = imageFlag | imageSuccessStateCode_;
    }
    if (imageFlag == 0b010) {
        secondaryImageCanvas_ = secondaryImageLoadingCtx_->GetCanvasImage();
        imageSuccessStateCode_ = imageFlag | imageSuccessStateCode_;
    }

    if (imageFlag == 0b100) {
        backgroundImageCanvas_ = backgroundImageLoadingCtx_->GetCanvasImage();
        imageSuccessStateCode_ = imageFlag | imageSuccessStateCode_;
    }
    // only when foreground, secondary and background image are all loaded successfully, mark dirty to update rendering.
    if (imageSuccessStateCode_ == RATING_IMAGE_SUCCESS_CODE) {
        LOGD("Rating foreground, secondary and background image are loaded successfully.");
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void RatingPattern::OnImageDataReady(int32_t imageFlag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    imageReadyStateCode_ = imageReadyStateCode_ | imageFlag;

    // 3 images are ready, invoke to update layout to calculate single star size.
    if (imageReadyStateCode_ == RATING_IMAGE_SUCCESS_CODE) {
        LOGD("Rating foreground, secondary and background image are ready.");
        host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
}

RefPtr<NodePaintMethod> RatingPattern::CreateNodePaintMethod()
{
    CHECK_NULL_RETURN(foregroundImageCanvas_, nullptr);
    CHECK_NULL_RETURN(secondaryImageCanvas_, nullptr);
    CHECK_NULL_RETURN(backgroundImageCanvas_, nullptr);
    auto starNum = GetLayoutProperty<RatingLayoutProperty>()->GetStars().value_or(
        GetStarNumFromTheme().value_or(DEFAULT_RATING_STAR_NUM));
    ImagePaintConfig singleStarImagePaintConfig(singleStarRect_, singleStarDstRect_);
    return MakeRefPtr<RatingPaintMethod>(
        foregroundImageCanvas_, secondaryImageCanvas_, backgroundImageCanvas_, singleStarImagePaintConfig, starNum);
}

bool RatingPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    if (!foregroundImageCanvas_ || !secondaryImageCanvas_ || !backgroundImageCanvas_) {
        return false;
    }
    return true;
}

ImageSourceInfo RatingPattern::GetImageSourceInfoFromTheme(int32_t imageFlag)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ImageSourceInfo imageSourceInfo;
    CHECK_NULL_RETURN(pipelineContext, imageSourceInfo);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, imageSourceInfo);
    auto ratingTheme = themeManager->GetTheme<RatingTheme>();
    CHECK_NULL_RETURN(ratingTheme, imageSourceInfo);
    switch (imageFlag) {
        case 0b001:
            imageSourceInfo.SetResourceId(ratingTheme->GetForegroundResourceId());
            break;
        case 0b010:
            imageSourceInfo.SetResourceId(ratingTheme->GetSecondaryResourceId());
            break;
        case 0b100:
            imageSourceInfo.SetResourceId(ratingTheme->GetBackgroundResourceId());
            break;
        default:
            break;
    }
    imageSourceInfo.UpdateSrcType();
    return imageSourceInfo;
}

void RatingPattern::ConstrainsRatingScore()
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();

    // constrains ratingScore and StarNum.
    // check if starNum is not positive, assign the value defined in theme.
    if (ratingLayoutProperty->HasStars() && ratingLayoutProperty->GetStars().value() <= 0) {
        ratingLayoutProperty->UpdateStars(GetStarNumFromTheme().value_or(DEFAULT_RATING_STAR_NUM));
    }

    // if ratingScore > StarsNum, constrain ratingScore value with StarNums.
    if (ratingRenderProperty->HasRatingScore() && ratingLayoutProperty->HasStars()) {
        if (GreatOrEqual(ratingRenderProperty->GetRatingScore().value(), ratingLayoutProperty->GetStars().value())) {
            ratingRenderProperty->UpdateRatingScore(ratingLayoutProperty->GetStars().value());
        }
    }

    // if ratingScore < 0, assign the value defined in theme.
    if (ratingRenderProperty->HasRatingScore()) {
        if (LessOrEqual(ratingRenderProperty->GetRatingScore().value(), 0.0)) {
            ratingRenderProperty->UpdateRatingScore(GetRatingScoreFromTheme().value_or(0.0));
        }
    }
}

void RatingPattern::OnModifyDone()
{
    // Reset image state code.
    imageReadyStateCode_ = 0;
    imageSuccessStateCode_ = 0;
    // Constrains ratingScore and starNum in case of the illegal input.
    ConstrainsRatingScore();

    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(ratingLayoutProperty);

    ImageSourceInfo foregroundImageSourceInfo =
        ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(GetImageSourceInfoFromTheme(0b001));
    // Recreate ImageLoadingContext only when image source info has changed.
    if (!foregroundImageLoadingCtx_ ||
        (foregroundImageLoadingCtx_ && (foregroundImageLoadingCtx_->GetSourceInfo() != foregroundImageSourceInfo))) {
        // Construct the ImageLoadingContext and register the image life cycle callback.
        LoadNotifier loadNotifierForegroundImage(
            CreateDataReadyCallback(0b001), CreateLoadSuccessCallback(0b001), CreateLoadFailCallback(0b001));
        foregroundImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(foregroundImageSourceInfo, std::move(loadNotifierForegroundImage));
        foregroundImageLoadingCtx_->LoadImageData();
    }

    ImageSourceInfo secondaryImageSourceInfo =
        ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(GetImageSourceInfoFromTheme(0b010));
    if (!secondaryImageLoadingCtx_ ||
        (secondaryImageLoadingCtx_ && secondaryImageLoadingCtx_->GetSourceInfo() != secondaryImageSourceInfo)) {
        LoadNotifier loadNotifierSecondaryImage(
            CreateDataReadyCallback(0b010), CreateLoadSuccessCallback(0b010), CreateLoadFailCallback(0b010));
        secondaryImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(secondaryImageSourceInfo, std::move(loadNotifierSecondaryImage));
        secondaryImageLoadingCtx_->LoadImageData();
    }

    ImageSourceInfo backgroundImageSourceInfo =
        ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(GetImageSourceInfoFromTheme(0b100));
    if (!backgroundImageLoadingCtx_ ||
        (backgroundImageLoadingCtx_ && backgroundImageLoadingCtx_->GetSourceInfo() != backgroundImageSourceInfo)) {
        LoadNotifier loadNotifierBackgroundImage(
            CreateDataReadyCallback(0b100), CreateLoadSuccessCallback(0b100), CreateLoadFailCallback(0b100));
        backgroundImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(backgroundImageSourceInfo, std::move(loadNotifierBackgroundImage));
        backgroundImageLoadingCtx_->LoadImageData();
    }
}
} // namespace OHOS::Ace::NG