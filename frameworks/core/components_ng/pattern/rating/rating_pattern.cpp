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
#include <iomanip>
#include <sstream>

#include "core/components/common/properties/color.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/rating/rating_paint_method.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
constexpr int32_t RATING_IMAGE_SUCCESS_CODE = 0b111;
constexpr int32_t DEFAULT_RATING_STAR_NUM = 5;
constexpr double DEFAULT_RATING_STEP_SIZE = 0.5;

void RatingPattern::CheckImageInfoHasChangedOrNot(
    int32_t imageFlag, const ImageSourceInfo& sourceInfo, const std::string& lifeCycleTag)
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(ratingLayoutProperty);
    auto currentSourceInfo = ImageSourceInfo("");
    switch (imageFlag) {
        case 0b001:
            currentSourceInfo = ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(ImageSourceInfo(""));
            if (currentSourceInfo != sourceInfo) {
                LOGW("Foreground image sourceInfo does not match, ignore current %{private}s callback. "
                     "current: %{private}s vs callback's: %{private}s",
                    lifeCycleTag.c_str(), currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
                return;
            }
            if (lifeCycleTag == "ImageDataFailed") {
                LOGE("Rating load foreground image failed");
            }
            break;
        case 0b010:
            currentSourceInfo = ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo(""));
            if (currentSourceInfo != sourceInfo) {
                LOGW("Secondary image sourceInfo does not match, ignore current %{private}s callback. "
                     "current: %{private}s vs callback's: %{private}s",
                    lifeCycleTag.c_str(), currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
                return;
            }
            if (lifeCycleTag == "ImageDataFailed") {
                LOGE("Rating load secondary image failed");
            }
            break;
        case 0b100:
            currentSourceInfo = ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo(""));
            if (currentSourceInfo != sourceInfo) {
                LOGW("Background image sourceInfo does not match, ignore current %{private}s callback. "
                     "current: %{private}s vs callback's: %{private}s",
                    lifeCycleTag.c_str(), currentSourceInfo.ToString().c_str(), sourceInfo.ToString().c_str());
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
    singleStarImagePaintConfig_.srcRect_ = singleStarRect_;
    singleStarImagePaintConfig_.dstRect_ = singleStarDstRect_;
    return MakeRefPtr<RatingPaintMethod>(
        foregroundImageCanvas_, secondaryImageCanvas_, backgroundImageCanvas_, singleStarImagePaintConfig_, starNum);
}

bool RatingPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
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
    auto ratingTheme = pipelineContext->GetTheme<RatingTheme>();
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

    // if ratingScore < 0, assign the value defined in theme.
    if (ratingRenderProperty->HasRatingScore()) {
        if (LessOrEqual(ratingRenderProperty->GetRatingScore().value(), 0.0)) {
            ratingRenderProperty->UpdateRatingScore(GetRatingScoreFromTheme().value_or(0.0));
        }
    }

    // Calculate drewScore based on the stepSize, and it is cannot be greater than starNum.
    double ratingScore = ratingRenderProperty->GetRatingScore().value_or(GetRatingScoreFromTheme().value_or(0.0));
    double stepSize =
        ratingRenderProperty->GetStepSize().value_or(GetStepSizeFromTheme().value_or(DEFAULT_RATING_STEP_SIZE));
    int32_t starNum =
        ratingLayoutProperty->GetStars().value_or(GetStarNumFromTheme().value_or(DEFAULT_RATING_STAR_NUM));
    double drawScore = fmin(Round(ratingScore / stepSize) * stepSize, static_cast<double>(starNum));

    // do not fire onChange callback when rating is initialized for the first time.
    if (hasInit_ && lastRatingScore_ != drawScore) {
        FireChangeEvent();
    }
    if (!hasInit_) {
        hasInit_ = true;
    }
    ratingRenderProperty->UpdateRatingScore(drawScore);
    lastRatingScore_ = drawScore;
}

void RatingPattern::RecalculatedRatingScoreBasedOnEventPoint(const double eventPointX)
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(ratingLayoutProperty);
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);

    // step1: calculate the number of star which the touch point falls on.
    double wholeStarNum = 0.0;
    float singleWidth = singleStarDstRect_.Width();
    wholeStarNum = floor(eventPointX / singleWidth);

    // step2: calculate relative position where the touch point falls on the wholeStarNum star.
    double posInSingle = 0.0;
    posInSingle = (eventPointX - wholeStarNum * singleWidth) / singleWidth;
    // step3: calculate the new ratingScore according to the touch point.
    double ratingScore = wholeStarNum + posInSingle;
    int32_t starNum =
        ratingLayoutProperty->GetStars().value_or(GetStarNumFromTheme().value_or(DEFAULT_RATING_STAR_NUM));
    double stepSize = ratingRenderProperty->GetStepSize().value_or(GetStepSizeFromTheme().value_or(0.5));
    // step3.1: constrain ratingScore which cannot be greater than starNum and be less than stepSize.
    ratingScore = ratingScore > starNum ? starNum : ratingScore;
    ratingScore = (ratingScore > stepSize) ? ratingScore : stepSize;
    double newDrawScore = fmin(ceil(ratingScore / stepSize) * stepSize, starNum);
    // step3.2: Determine whether the old and new ratingScores are same or not.
    double oldRatingScore = ratingRenderProperty->GetRatingScoreValue();
    double oldDrawScore = fmin(Round(oldRatingScore / stepSize) * stepSize, static_cast<double>(starNum));
    if (NearEqual(newDrawScore, oldDrawScore)) {
        return;
    }
    // step4: Update the ratingScore saved in renderProperty and update render.
    ratingRenderProperty->UpdateRatingScore(newDrawScore);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool RatingPattern::IsIndicator()
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_RETURN(ratingLayoutProperty, true);
    // Do not handle event when rating is set as indicator or single star size is invalid.
    return ratingLayoutProperty->GetIndicator().value_or(false) || !singleStarDstRect_.IsValid();
}

void RatingPattern::HandleDragUpdate(const GestureEvent& info)
{
    RecalculatedRatingScoreBasedOnEventPoint(info.GetLocalLocation().GetX());
}

void RatingPattern::FireChangeEvent() const
{
    auto ratingEventHub = GetEventHub<RatingEventHub>();
    CHECK_NULL_VOID(ratingEventHub);
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    std::stringstream ss;
    ss << std::setprecision(2) << ratingRenderProperty->GetRatingScoreValue();
    ratingEventHub->FireChangeEvent(ss.str());
}

void RatingPattern::HandleDragEnd()
{
    FireChangeEvent();
}

void RatingPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (IsIndicator() || panEvent_) {
        return;
    }

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& /*info*/) { LOGD("Pan event start"); };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragUpdate(info);
        }
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& /*info*/) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            // invoke onChange callback
            pattern->HandleDragEnd();
        }
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() { LOGD("Pan event cancel"); };

    float distance = DEFAULT_PAN_DISTANCE;
    auto host = GetHost();
    if (host) {
        auto context = host->GetContext();
        if (context) {
            distance = static_cast<float>(context->NormalizeToPx(Dimension(DEFAULT_PAN_DISTANCE, DimensionUnit::VP)));
        }
    }
    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL;

    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distance);
}

void RatingPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (IsIndicator() || touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            auto localPosition = info.GetTouches().front().GetLocalLocation();
            // handle touch down event and draw touch down effect.
            pattern->HandleTouchDown(localPosition);
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            // handle touch up event and remove touch down effect.
            pattern->HandleTouchUp();
        }
    };

    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void RatingPattern::HandleTouchUp()
{
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    // Update touch star to 0 to indicate there is no star to be touched.
    ratingRenderProperty->UpdateTouchStar(0);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RatingPattern::HandleTouchDown(const Offset& localPosition)
{
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    // calculate the number of star the touch point falls on adn trigger render update.
    int32_t touchStar = floor(localPosition.GetX() / singleStarDstRect_.Width());
    ratingRenderProperty->UpdateTouchStar(touchStar);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RatingPattern::HandleClick(const GestureEvent& info)
{
    RecalculatedRatingScoreBasedOnEventPoint(info.GetLocalLocation().GetX());
    FireChangeEvent();
}

void RatingPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (IsIndicator() || clickEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        pattern->HandleClick(info);
    };

    clickEvent_ = MakeRefPtr<ClickEvent>(std::move(touchTask));
    gestureHub->AddClickEvent(clickEvent_);
}

void RatingPattern::UpdateInternalResource(ImageSourceInfo& sourceInfo, int32_t imageFlag)
{
    if (!sourceInfo.IsInternalResource()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (!iconPath.empty()) {
        sourceInfo.SetSrc(iconPath);
        auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
        CHECK_NULL_VOID(ratingLayoutProperty);
        switch (imageFlag) {
            case 0b001:
                ratingLayoutProperty->UpdateForegroundImageSourceInfo(sourceInfo);
                break;
            case 0b010:
                ratingLayoutProperty->UpdateSecondaryImageSourceInfo(sourceInfo);
                break;
            case 0b100:
                ratingLayoutProperty->UpdateBackgroundImageSourceInfo(sourceInfo);
                break;
            default:
                break;
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

    if (!ratingLayoutProperty->HasForegroundImageSourceInfo()) {
        isForegroundImageInfoFromTheme_ = true;
        ratingLayoutProperty->UpdateForegroundImageSourceInfo(GetImageSourceInfoFromTheme(0b001));
        singleStarImagePaintConfig_.isSvg_ = true;
    }
    ImageSourceInfo foregroundImageSourceInfo =
        ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(GetImageSourceInfoFromTheme(0b001));
    UpdateInternalResource(foregroundImageSourceInfo, 0b001);
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
    if (!ratingLayoutProperty->HasSecondaryImageSourceInfo()) {
        isSecondaryImageInfoFromTheme_ = true;
        ratingLayoutProperty->UpdateSecondaryImageSourceInfo(GetImageSourceInfoFromTheme(0b010));
    }
    ImageSourceInfo secondaryImageSourceInfo =
        ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(GetImageSourceInfoFromTheme(0b010));
    UpdateInternalResource(secondaryImageSourceInfo, 0b010);
    if (!secondaryImageLoadingCtx_ ||
        (secondaryImageLoadingCtx_ && secondaryImageLoadingCtx_->GetSourceInfo() != secondaryImageSourceInfo)) {
        LoadNotifier loadNotifierSecondaryImage(
            CreateDataReadyCallback(0b010), CreateLoadSuccessCallback(0b010), CreateLoadFailCallback(0b010));
        secondaryImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(secondaryImageSourceInfo, std::move(loadNotifierSecondaryImage));
        secondaryImageLoadingCtx_->LoadImageData();
    }

    if (!ratingLayoutProperty->HasBackgroundImageSourceInfo()) {
        isBackgroundImageInfoFromTheme_ = true;
        ratingLayoutProperty->UpdateBackgroundImageSourceInfo(GetImageSourceInfoFromTheme(0b100));
    }
    ImageSourceInfo backgroundImageSourceInfo =
        ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(GetImageSourceInfoFromTheme(0b100));
    UpdateInternalResource(backgroundImageSourceInfo, 0b100);
    if (!backgroundImageLoadingCtx_ || backgroundImageLoadingCtx_->GetSourceInfo() != backgroundImageSourceInfo) {
        LoadNotifier loadNotifierBackgroundImage(
            CreateDataReadyCallback(0b100), CreateLoadSuccessCallback(0b100), CreateLoadFailCallback(0b100));
        backgroundImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(backgroundImageSourceInfo, std::move(loadNotifierBackgroundImage));
        backgroundImageLoadingCtx_->LoadImageData();
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    // Init touch, pan and click event and register callback.
    InitTouchEvent(gestureHub);
    InitPanEvent(gestureHub);
    InitClickEvent(gestureHub);
}
// XTS inspector code
void RatingPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    if (isForegroundImageInfoFromTheme_) {
        json->Put("foregroundImageSourceInfo", ImageSourceInfo("").ToString().c_str());
    } else {
        auto foregroundImageSourceInfo = ratingLayoutProperty->GetForegroundImageSourceInfo();
        json->Put("foregroundImageSourceInfo", foregroundImageSourceInfo->ToString().c_str());
    }
    if (isSecondaryImageInfoFromTheme_) {
        json->Put("foregroundImageSourceInfo", ImageSourceInfo("").ToString().c_str());
    } else {
        auto secondaryImageSourceInfo = ratingLayoutProperty->GetSecondaryImageSourceInfo();
        json->Put("foregroundImageSourceInfo", secondaryImageSourceInfo->ToString().c_str());
    }
    if (isBackgroundImageInfoFromTheme_) {
        json->Put("foregroundImageSourceInfo", ImageSourceInfo("").ToString().c_str());
    } else {
        auto backgroundImageSourceInfo = ratingLayoutProperty->GetBackgroundImageSourceInfo();
        json->Put("foregroundImageSourceInfo", backgroundImageSourceInfo->ToString().c_str());
    }
}
} // namespace OHOS::Ace::NG