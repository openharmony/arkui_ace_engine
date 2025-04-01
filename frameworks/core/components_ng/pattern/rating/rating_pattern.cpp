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
#include "core/components_ng/pattern/rating/rating_pattern.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/properties/color.h"
#include "core/components/rating/rating_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_paint_method.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr int32_t RATING_IMAGE_SUCCESS_CODE = 0b111;
constexpr int32_t RATING_IMAGE_SUCCESS_FOCUS_CODE = 0b1111;
constexpr int32_t DEFAULT_RATING_TOUCH_STAR_NUMBER = 0;
constexpr int32_t HALF_DIVIDE = 2;

void RatingPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetAlphaOffscreen(true);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    themeStarNum_ = ratingTheme->GetStarNum();
    themeStepSize_ = ratingTheme->GetStepSize();
    themeRatingScore_ = ratingTheme->GetRatingScore();
    themeBorderWidth_ = ratingTheme->GetFocusBorderWidth();
    pipelineContext_ = host->GetContextRefPtr();
    isNeedFocusStyle_ = !NearZero(ratingTheme->GetFocusSpace().Value());
}

void RatingPattern::CheckImageInfoHasChangedOrNot(
    int32_t imageFlag, const ImageSourceInfo& sourceInfo, const std::string& lifeCycleTag)
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(ratingLayoutProperty);
    auto currentSourceInfo = ImageSourceInfo("");
    switch (imageFlag) {
        case 0b001:
            if (isForegroundImageInfoFromTheme_) {
                currentSourceInfo = foregroundImageSourceInfo_.value_or(ImageSourceInfo(""));
            } else {
                currentSourceInfo = ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(ImageSourceInfo(""));
            }
            CHECK_NULL_VOID(currentSourceInfo == sourceInfo);
            if (lifeCycleTag == "ImageDataFailed") {
                TAG_LOGW(AceLogTag::ACE_SELECT_COMPONENT,
                    "Rating load foreground image failed, the sourceInfo is %{public}s", sourceInfo.ToString().c_str());
            }
            break;
        case 0b010:
            if (isSecondaryImageInfoFromTheme_) {
                currentSourceInfo = secondaryImageSourceInfo_.value_or(ImageSourceInfo(""));
            } else {
                currentSourceInfo = ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo(""));
            }
            CHECK_NULL_VOID(currentSourceInfo == sourceInfo);
            if (lifeCycleTag == "ImageDataFailed") {
                TAG_LOGW(AceLogTag::ACE_SELECT_COMPONENT,
                    "Rating load secondary image failed, the sourceInfo is %{public}s", sourceInfo.ToString().c_str());
            }
            break;
        case 0b100:
            if (isBackgroundImageInfoFromTheme_) {
                currentSourceInfo = backgroundImageSourceInfo_.value_or(ImageSourceInfo(""));
            } else {
                currentSourceInfo = ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo(""));
            }
            CHECK_NULL_VOID(currentSourceInfo == sourceInfo);
            if (lifeCycleTag == "ImageDataFailed") {
                TAG_LOGW(AceLogTag::ACE_SELECT_COMPONENT,
                    "Rating load background image failed, the sourceInfo is %{public}s", sourceInfo.ToString().c_str());
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
    auto task = [weak = WeakClaim(this), imageFlag](const ImageSourceInfo& sourceInfo, const std::string& msg) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // check image info has changed or not
        pattern->CheckImageInfoHasChangedOrNot(imageFlag, sourceInfo, "ImageDataFailed");
    };
    return task;
}

void RatingPattern::OnImageLoadSuccess(int32_t imageFlag)
{
    if (imageFlag == 0b001) {
        foregroundImageCanvas_ = foregroundImageLoadingCtx_->MoveCanvasImage();
        foregroundConfig_.srcRect_ = foregroundImageLoadingCtx_->GetSrcRect();
        foregroundConfig_.dstRect_ = foregroundImageLoadingCtx_->GetDstRect();
        imageSuccessStateCode_ |= static_cast<uint32_t>(imageFlag);
    }
    if (imageFlag == 0b010) {
        secondaryImageCanvas_ = secondaryImageLoadingCtx_->MoveCanvasImage();
        secondaryConfig_.srcRect_ = secondaryImageLoadingCtx_->GetSrcRect();
        secondaryConfig_.dstRect_ = secondaryImageLoadingCtx_->GetDstRect();
        imageSuccessStateCode_ |= static_cast<uint32_t>(imageFlag);
    }
    if (imageFlag == 0b100) {
        backgroundImageCanvas_ = backgroundImageLoadingCtx_->MoveCanvasImage();
        backgroundConfig_.srcRect_ = backgroundImageLoadingCtx_->GetSrcRect();
        backgroundConfig_.dstRect_ = backgroundImageLoadingCtx_->GetDstRect();
        imageSuccessStateCode_ |= static_cast<uint32_t>(imageFlag);
    }
    if (imageFlag == 0b1000 && backgroundImageFocusLoadingCtx_ != nullptr) {
        backgroundImageFocusCanvas_ = backgroundImageFocusLoadingCtx_->MoveCanvasImage();
        backgroundFocusConfig_.srcRect_ = backgroundImageFocusLoadingCtx_->GetSrcRect();
        backgroundFocusConfig_.dstRect_ = backgroundImageFocusLoadingCtx_->GetDstRect();
        imageSuccessStateCode_ |= static_cast<uint32_t>(imageFlag);
    }
    // only when foreground, secondary and background image are all loaded successfully, mark dirty to update rendering.
    if (IsRatingImageReady(imageSuccessStateCode_)) {
        MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void RatingPattern::OnImageDataReady(int32_t imageFlag)
{
    imageReadyStateCode_ |= static_cast<uint32_t>(imageFlag);
    MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void RatingPattern::UpdatePaintConfig()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto starsNum = layoutProperty->GetStarsValue(themeStarNum_);
    CHECK_EQUAL_VOID(starsNum, 0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto contentSize = geometryNode->GetContentSize();
    foregroundConfig_.imageFit_ = ImageFit::FILL;
    secondaryConfig_.imageFit_ = ImageFit::FILL;
    backgroundConfig_.imageFit_ = ImageFit::FILL;
    backgroundFocusConfig_.imageFit_ = ImageFit::FILL;
    if (NearZero(frameSize.Width(), 0.0) || NearZero(frameSize.Height(), 0.0)) {
        return;
    }
    foregroundConfig_.scaleX_ = contentSize.Width() / frameSize.Width() / static_cast<float>(starsNum);
    foregroundConfig_.scaleY_ = contentSize.Height() / frameSize.Height();
    secondaryConfig_.scaleX_ = contentSize.Width() / frameSize.Width() / static_cast<float>(starsNum);
    secondaryConfig_.scaleY_ = contentSize.Height() / frameSize.Height();
    backgroundConfig_.scaleX_ = contentSize.Width() / frameSize.Width() / static_cast<float>(starsNum);
    backgroundConfig_.scaleY_ = contentSize.Height() / frameSize.Height();
    backgroundFocusConfig_.scaleX_ = contentSize.Width() / frameSize.Width() / static_cast<float>(starsNum);
    backgroundFocusConfig_.scaleY_ = contentSize.Height() / frameSize.Height();
}

RefPtr<NodePaintMethod> RatingPattern::CreateNodePaintMethod()
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_RETURN(ratingLayoutProperty, nullptr);
    if (!ratingModifier_) {
        ratingModifier_ = AceType::MakeRefPtr<RatingModifier>();
    }
    auto starNum = ratingLayoutProperty->GetStarsValue(themeStarNum_);
    auto defaultPaintMethod = MakeRefPtr<RatingPaintMethod>(WeakClaim(this), ratingModifier_, starNum, state_, false);
    CHECK_NULL_RETURN(ratingLayoutProperty, defaultPaintMethod);
    CHECK_NULL_RETURN(foregroundImageCanvas_, defaultPaintMethod);
    CHECK_NULL_RETURN(secondaryImageCanvas_, defaultPaintMethod);
    CHECK_NULL_RETURN(backgroundImageCanvas_, defaultPaintMethod);
    CHECK_NULL_RETURN(foregroundImageLoadingCtx_, defaultPaintMethod);
    CHECK_NULL_RETURN(secondaryImageLoadingCtx_, defaultPaintMethod);
    CHECK_NULL_RETURN(backgroundImageLoadingCtx_, defaultPaintMethod);
    UpdatePaintConfig();
    PrepareAnimation(foregroundImageCanvas_);
    PrepareAnimation(secondaryImageCanvas_);
    PrepareAnimation(backgroundImageCanvas_);
    if (backgroundImageFocusCanvas_ != nullptr) {
        PrepareAnimation(backgroundImageFocusCanvas_);
    }
    // when frameNode mark dirty to update rendering, only when 3 images are all loaded successfully and
    // JudgeImageSourceInfo is true, pattern will update ratingModifier's CanvasImage.
    if (ratingModifier_->JudgeImageSourceInfo(foregroundImageLoadingCtx_->GetSourceInfo(),
            secondaryImageLoadingCtx_->GetSourceInfo(), backgroundImageLoadingCtx_->GetSourceInfo(),
            foregroundConfig_) &&
        IsRatingImageReady(imageSuccessStateCode_)) {
        ratingModifier_->UpdateImageSourceInfo(foregroundImageLoadingCtx_->GetSourceInfo(),
            secondaryImageLoadingCtx_->GetSourceInfo(), backgroundImageLoadingCtx_->GetSourceInfo());
        ratingModifier_->UpdateCanvasImage(foregroundImageCanvas_, secondaryImageCanvas_, backgroundImageCanvas_,
            backgroundImageFocusCanvas_, foregroundConfig_, secondaryConfig_,
            backgroundConfig_, backgroundFocusConfig_);
    }
    if (!(foregroundImageCanvas_->IsStatic() && secondaryImageCanvas_->IsStatic() &&
            backgroundImageCanvas_->IsStatic())) {
        ratingModifier_->SetNeedDraw(true);
    }
    auto&& ratingGroup = ratingLayoutProperty->GetOrCreateRatingPropertyGroup();
    CHECK_NULL_RETURN(ratingGroup, nullptr);
    ratingModifier_->SetIndicator(ratingGroup->GetIndicatorValue());
    ratingModifier_->SetImageInfoFromTheme(isForegroundImageInfoFromTheme_ &&
        isSecondaryImageInfoFromTheme_ && isBackgroundImageInfoFromTheme_);
    ratingModifier_->SetUseContentModifier(UseContentModifier());
    auto direction = ratingLayoutProperty->GetLayoutDirection();
    auto reverse = direction == TextDirection::AUTO ? AceApplicationInfo::GetInstance().IsRightToLeft() :
        direction == TextDirection::RTL;
    auto paintMethod = MakeRefPtr<RatingPaintMethod>(WeakClaim(this), ratingModifier_, starNum, state_, reverse);
    paintMethod->UpdateFocusState(isfocus_, focusRatingScore_);
    return paintMethod;
}

bool RatingPattern::IsRatingImageReady(uint32_t imageStateCode)
{
    return imageStateCode == (IsNeedFocusStyle() ? RATING_IMAGE_SUCCESS_FOCUS_CODE : RATING_IMAGE_SUCCESS_CODE);
}

bool RatingPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    std::optional<SizeF> contentSize = GetHostContentSize();
    CHECK_NULL_RETURN(contentSize, false);
    auto layoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto starsNum = layoutProperty->GetStarsValue(themeStarNum_);
    singleStarWidth_ = contentSize->Width() / static_cast<float>(starsNum);
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    if (!foregroundImageCanvas_ || !secondaryImageCanvas_ || !backgroundImageCanvas_) {
        return false;
    }
    return true;
}

void RatingPattern::ConstrainsRatingScore(const RefPtr<RatingLayoutProperty>& layoutProperty)
{
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();

    // constrains ratingScore and StarNum.
    // check if starNum is not positive, assign the value defined in theme.
    if (layoutProperty->HasStars() && layoutProperty->GetStars().value() <= 0) {
        layoutProperty->UpdateStars(themeStarNum_);
    }

    // if ratingScore < 0, assign the value defined in theme.
    if (ratingRenderProperty->HasRatingScore()) {
        if (LessOrEqual(ratingRenderProperty->GetRatingScore().value(), 0.0)) {
            UpdateRatingScore(themeRatingScore_);
        }
    }

    auto starNum = layoutProperty->GetStarsValue(themeStarNum_);
    // steps max is stars, if steps > stars, assign the value defined in theme.
    if (ratingRenderProperty->HasStepSize()) {
        if (GreatNotEqual(ratingRenderProperty->GetStepSizeValue(themeStepSize_), starNum)) {
            ratingRenderProperty->UpdateStepSize(themeStepSize_);
        }
    }

    // Calculate drewScore based on the stepSize, and it is cannot be greater than starNum.
    const double ratingScore = ratingRenderProperty->GetRatingScore().value_or(themeRatingScore_);
    const double stepSize = ratingRenderProperty->GetStepSize().value_or(themeStepSize_);
    const double drawScore = fmin(Round(ratingScore / stepSize) * stepSize, static_cast<double>(starNum));
    // do not fire onChange callback when rating is initialized for the first time.
    if (hasInit_ && lastRatingScore_ != drawScore) {
        FireChangeEvent();
    }
    if (!hasInit_) {
        hasInit_ = true;
    }
    UpdateRatingScore(drawScore);
    lastRatingScore_ = drawScore;
}

void RatingPattern::RecalculatedRatingScoreBasedOnEventPoint(double eventPointX, bool isDrag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(ratingLayoutProperty);
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    const auto& content = host->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto direction = ratingLayoutProperty->GetLayoutDirection();
    auto reverse = direction == TextDirection::AUTO ? AceApplicationInfo::GetInstance().IsRightToLeft() :
        direction == TextDirection::RTL;
    auto touchLocationX =
        reverse ? (content->GetRect().Right() - eventPointX) : (eventPointX - content->GetRect().Left());

    const int32_t starNum = ratingLayoutProperty->GetStarsValue(themeStarNum_);
    // step1: calculate the number of star which the touch point falls on.
    double wholeStarNum = 0.0;
    wholeStarNum = floor(touchLocationX / singleStarWidth_);

    // step2: calculate relative position where the touch point falls on the wholeStarNum star.
    double posInSingle = 0.0;
    posInSingle = (touchLocationX - wholeStarNum * singleStarWidth_) / singleStarWidth_;
    // step3: calculate the new ratingScore according to the touch point.
    double ratingScore = wholeStarNum + posInSingle;
    const double stepSize = ratingRenderProperty->GetStepSizeValue(themeStepSize_);
    // step3.1: constrain ratingScore which cannot be greater than starNum and be less than 0.0.
    ratingScore = ratingScore > starNum ? starNum : ratingScore;
    ratingScore = (ratingScore < 0.0) ? 0.0 : ratingScore;
    const double newDrawScore = fmin(ceil(ratingScore / stepSize) * stepSize, starNum);
    // step3.2: Determine whether the old and new ratingScores are same or not.
    const double oldRatingScore = ratingRenderProperty->GetRatingScoreValue();
    const double oldDrawScore = fmin(Round(oldRatingScore / stepSize) * stepSize, static_cast<double>(starNum));

    CHECK_NULL_VOID(!NearEqual(newDrawScore, oldDrawScore));

    // step4: Update the ratingScore saved in renderProperty and update render.
    UpdateRatingScore(newDrawScore);
    std::ostringstream oldScore;
    std::ostringstream newScore;
    oldScore << std::fixed << std::setprecision(1) << oldDrawScore;
    newScore << std::fixed << std::setprecision(1) << newDrawScore;
    if (isDrag) {
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, oldScore.str(), newScore.str());
        ratingRenderProperty->UpdateTouchStar(
            static_cast<int32_t>(reverse ? starNum - wholeStarNum - 1 : wholeStarNum));
    }
    MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool RatingPattern::IsIndicator()
{
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_RETURN(ratingLayoutProperty, true);
    // Do not handle event when rating is set as indicator or single star size is invalid.
    return ratingLayoutProperty->GetIndicator().value_or(false) || !foregroundConfig_.dstRect_.IsValid();
}

void RatingPattern::HandleDragUpdate(const GestureEvent& info)
{
    CHECK_NULL_VOID(!IsIndicator());
    RecalculatedRatingScoreBasedOnEventPoint(info.GetLocalLocation().GetX(), true);
}

void RatingPattern::FireChangeEvent()
{
    auto ratingEventHub = GetEventHub<RatingEventHub>();
    CHECK_NULL_VOID(ratingEventHub);
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    std::stringstream ss;
    ss << std::setprecision(2) << ratingRenderProperty->GetRatingScoreValue();
    ratingEventHub->FireChangeEvent(ss.str());
    lastRatingScore_ = ratingRenderProperty->GetRatingScoreValue();

    if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    Recorder::EventParamsBuilder builder;
    auto score = ss.str();
    builder.SetId(inspectorId)
        .SetType(host->GetTag())
        .SetText(score)
        .SetHost(host)
        .SetDescription(host->GetAutoEventParamValue(""));
    Recorder::EventRecorder::Get().OnChange(std::move(builder));
    if (inspectorId.empty()) {
        return;
    }
    Recorder::NodeDataCache::Get().PutString(host, inspectorId, score);
}

void RatingPattern::HandleDragEnd()
{
    CHECK_NULL_VOID(!IsIndicator());
    FireChangeEvent();
}

void RatingPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!panEvent_);
    PanDirection panDirection;
    panDirection.type = PanDirection::HORIZONTAL;

    panEvent_ = MakeRefPtr<PanEvent>([weak = WeakClaim(this)](const GestureEvent& info) {},
        [weak = WeakClaim(this)](const GestureEvent& info) {
            TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "rating handle drag update");
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragUpdate(info);
        },
        [weak = WeakClaim(this)](const GestureEvent& /*info*/) {
            TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "rating handle drag end");
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            // invoke onChange callback
            pattern->HandleDragEnd();
        },
        [weak = WeakClaim(this)]() {});
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void RatingPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!touchEvent_);
    touchEvent_ = MakeRefPtr<TouchEventImpl>([weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            auto localPosition = info.GetTouches().front().GetLocalLocation();
            // handle touch down event and draw touch down effect.
            pattern->HandleTouchDown(localPosition);
            TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "rating handle touch down");
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            // handle touch up event and remove touch down effect.
            pattern->HandleTouchUp();
            TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "rating handle touch up");
        }
    });
    gestureHub->AddTouchEvent(touchEvent_);
}

void RatingPattern::HandleTouchUp()
{
    CHECK_NULL_VOID(!IsIndicator());
    state_ = isHover_ ? RatingModifier::RatingAnimationType::PRESSTOHOVER : RatingModifier::RatingAnimationType::NONE;
    MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RatingPattern::HandleTouchDown(const Offset& localPosition)
{
    CHECK_NULL_VOID(!IsIndicator());

    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& content = host->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentOffset = content->GetRect().GetOffset();
    // calculate the number of star the touch point falls on and trigger render update.
    const int32_t touchStar = floor((localPosition.GetX() - contentOffset.GetX()) / singleStarWidth_);
    ratingRenderProperty->UpdateTouchStar(touchStar);
    state_ = isHover_ ? RatingModifier::RatingAnimationType::HOVERTOPRESS : RatingModifier::RatingAnimationType::PRESS;
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RatingPattern::HandleClick(const GestureEvent& info)
{
    CHECK_NULL_VOID(!IsIndicator());
    auto eventPointX = info.GetLocalLocation().GetX();
    if (Negative(eventPointX)) {
        return;
    }
    RecalculatedRatingScoreBasedOnEventPoint(eventPointX, false);
    FireChangeEvent();
}

void RatingPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!clickEvent_);
    clickEvent_ = MakeRefPtr<ClickEvent>([weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClick(info);
    });
    gestureHub->AddClickEvent(clickEvent_);
}

void RatingPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& content = host->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto singleStarHeight = content->GetRect().Height();
    auto property = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto offsetLeft = 0.0f;
    auto offsetTop = 0.0f;
    const auto& padding = property->GetPaddingProperty();
    if (padding) {
        offsetLeft += padding->left.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
        offsetTop += padding->top.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
    }
    const auto& border = property->GetBorderWidthProperty();
    if (border) {
        offsetLeft += border->leftDimen.value_or(Dimension(0.0)).ConvertToPx();
        offsetTop += border->topDimen.value_or(Dimension(0.0)).ConvertToPx();
    }
    auto ratingScore = focusRatingScore_;
    auto wholeStarNum =
        fmax((NearEqual(ratingScore, std::round(ratingScore)) ? ratingScore : ceil(ratingScore)) - 1, 0.0);
    auto direction = property->GetLayoutDirection();
    auto reverse = direction == TextDirection::AUTO ? AceApplicationInfo::GetInstance().IsRightToLeft() :
        direction == TextDirection::RTL;
    if (reverse) {
        double starNum = property->GetStarsValue(themeStarNum_);
        wholeStarNum = starNum - wholeStarNum - 1;
    }
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    ratingRenderProperty->UpdateTouchStar(wholeStarNum);
    float focusSpace = 0.0f;
    float radius = GetFocusRectRadius(property, focusSpace);
    auto focusButtonRect = RectF(static_cast<float>(wholeStarNum) * singleStarWidth_ + offsetLeft, offsetTop,
        singleStarWidth_, singleStarHeight);
    focusButtonRect -= OffsetF(focusSpace, focusSpace);
    focusButtonRect += SizeF(focusSpace + focusSpace, focusSpace + focusSpace);
    paintRect.SetRect(focusButtonRect);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, static_cast<RSScalar>(radius),
        static_cast<RSScalar>(radius));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, static_cast<RSScalar>(radius),
        static_cast<RSScalar>(radius));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, static_cast<RSScalar>(radius),
        static_cast<RSScalar>(radius));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, static_cast<RSScalar>(radius),
        static_cast<RSScalar>(radius));
}

float RatingPattern::GetFocusRectRadius(const RefPtr<RatingLayoutProperty>& property, float& focusSpace)
{
    CHECK_NULL_RETURN(ratingModifier_, 0.0);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0.0);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_RETURN(ratingTheme, 0.0);
    focusSpace = ratingTheme->GetFocusSpace().ConvertToPx();
    float radius = 0.0f;
    auto isImageInfoFromTheme = isForegroundImageInfoFromTheme_ &&
        isSecondaryImageInfoFromTheme_ && isBackgroundImageInfoFromTheme_;
    if (!ratingTheme->GetIsCircleRadius() || !isImageInfoFromTheme) {
        radius = ratingTheme->GetFocusBorderRadius().ConvertToPx() + ratingTheme->GetFocusSpace().ConvertToPx();
    } else {
        double starNum = property->GetStarsValue(themeStarNum_);
        if (!NearEqual(starNum, 0.0)) {
            auto contentSize = ratingModifier_->GetContentSize();
            CHECK_NULL_RETURN(contentSize, 0.0);
            auto isSquare = ((contentSize->Get().Width() / starNum) == contentSize->Get().Height());
            radius = (isSquare ? contentSize->Get().Height() / HALF_DIVIDE
                : ratingTheme->GetFocusBorderRadius().ConvertToPx()) + ratingTheme->GetFocusSpace().ConvertToPx();
        }
    }
    return radius;
}

void RatingPattern::PaintFocusState(double ratingScore)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isfocus_ = true;
    focusRatingScore_ = ratingScore;
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool RatingPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    double ratingScore = focusRatingScore_;
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    double starNum = ratingLayoutProperty->GetStarsValue(themeStarNum_);
    bool reverse = ratingLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    const double stepSize = ratingRenderProperty->GetStepSizeValue(themeStepSize_);
    if (event.code == KeyCode::KEY_DPAD_LEFT) {
        ratingScore = reverse ? fmin(ratingScore + stepSize, starNum) : fmax(ratingScore - stepSize, 0.0);
        PaintFocusState(ratingScore);
        return true;
    }
    if (event.code == KeyCode::KEY_DPAD_RIGHT) {
        ratingScore = reverse ? fmax(ratingScore - stepSize, 0.0) : fmin(ratingScore + stepSize, starNum);
        PaintFocusState(ratingScore);
        return true;
    }
    if (event.code == KeyCode::KEY_MOVE_HOME) {
        ratingScore = 1;
        PaintFocusState(ratingScore);
        return true;
    }
    if (event.code == KeyCode::KEY_MOVE_END) {
        ratingScore = starNum;
        PaintFocusState(ratingScore);
        return true;
    }
    if (event.code == KeyCode::KEY_ENTER || event.code == KeyCode::KEY_SPACE) {
        ratingRenderProperty->UpdateRatingScore(ratingScore);
        FireChangeEvent();
        return true;
    }
    return false;
}

void RatingPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    focusHub->SetFocusType(IsIndicator() ? FocusType::DISABLE : FocusType::NODE);
    focusHub->SetOnKeyEventInternal([wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    });
    focusHub->SetInnerFocusPaintRectCallback([wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    });
    focusHub->SetOnFocusInternal([wp = WeakClaim(this)]() {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnFocusEvent();
    });

    focusHub->SetOnBlurInternal([wp = WeakClaim(this)]() {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnBlurEvent();
    });
}

void RatingPattern::SetModifierFocus(bool isFocus)
{
    isfocus_ = isFocus;
    state_ = isfocus_ ? RatingModifier::RatingAnimationType::FOCUS : RatingModifier::RatingAnimationType::NONE;

    CHECK_NULL_VOID(pipelineContext_);
    auto ratingTheme = pipelineContext_->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    if (ratingTheme->GetFocusAndBlurCancleAnimation()) {
        ratingModifier_->SetFocusOrBlurColor(isfocus_ ? ratingTheme->GetFocusColor() : Color::TRANSPARENT);
    }
    ratingModifier_->SetIsFocus(isFocus);
    ratingModifier_->SetNeedDraw(true);
    MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RatingPattern::OnFocusEvent()
{
    CHECK_NULL_VOID(pipelineContext_);
    if (pipelineContext_->GetIsFocusActive()) {
        SetModifierFocus(true);
    }
    AddIsFocusActiveUpdateEvent();
}

void RatingPattern::OnBlurEvent()
{
    SetModifierFocus(false);
    RemoveIsFocusActiveUpdateEvent();
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    focusRatingScore_ = ratingRenderProperty->GetRatingScoreValue();
    MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RatingPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetModifierFocus(isFocusAcitve);
        };
    }
    CHECK_NULL_VOID(pipelineContext_);
    pipelineContext_->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void RatingPattern::RemoveIsFocusActiveUpdateEvent()
{
    CHECK_NULL_VOID(pipelineContext_);
    pipelineContext_->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void RatingPattern::SetRatingScore(double ratingScore)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    if (!enabled) {
        return;
    }
    UpdateRatingScore(ratingScore);
    OnModifyDone();
}

void RatingPattern::UpdateRatingScore(double ratingScore)
{
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    ratingRenderProperty->UpdateRatingScore(ratingScore);
    focusRatingScore_ = ratingScore;
    FireBuilder();
}

void RatingPattern::InitMouseEvent()
{
    CHECK_NULL_VOID(!(mouseEvent_ && hoverEvent_));
    auto eventHub = GetHost()->GetEventHub<RatingEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    mouseEvent_ = MakeRefPtr<InputEvent>([weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(info);
    });
    hoverEvent_ = MakeRefPtr<InputEvent>([weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleHoverEvent(isHover);
    });
    inputHub->AddOnHoverEvent(hoverEvent_);
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void RatingPattern::HandleHoverEvent(bool isHover)
{
    isHover_ = isHover;
    if (isfocus_) {
        state_ = RatingModifier::RatingAnimationType::FOCUS;
    } else {
        state_ = isHover_ ? RatingModifier::RatingAnimationType::HOVER : RatingModifier::RatingAnimationType::NONE;
    }

    if (!isHover) {
        UpdateRatingScore(lastRatingScore_);
        auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
        CHECK_NULL_VOID(ratingRenderProperty);
        ratingRenderProperty->UpdateTouchStar(lastRatingScore_);
    }
    MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RatingPattern::HandleMouseEvent(MouseInfo& info)
{
    CHECK_NULL_VOID(!IsIndicator() && isHover_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& content = host->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentOffset = content->GetRect().GetOffset();
    auto ratingRenderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_VOID(ratingRenderProperty);
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(ratingLayoutProperty);
    // calculate the number of star the mouse moved on and trigger render update.
    auto touchStar =
        static_cast<int32_t>(floor((info.GetLocalLocation().GetX() - contentOffset.GetX()) / singleStarWidth_));
    touchStar =
        std::clamp(touchStar, DEFAULT_RATING_TOUCH_STAR_NUMBER, ratingLayoutProperty->GetStarsValue(themeStarNum_) - 1);
    ratingRenderProperty->UpdateTouchStar(touchStar);
    RecalculatedRatingScoreBasedOnEventPoint(info.GetLocalLocation().GetX(), false);
}

void RatingPattern::LoadForeground(const RefPtr<RatingLayoutProperty>& layoutProperty,
    const RefPtr<RatingTheme>& ratingTheme, const RefPtr<IconTheme>& iconTheme)
{
    foregroundConfig_.isSvg_ = false;
    /*
     * tips : foregroundUri loaded the default star the first time, the ForegroundImageSourceInfo will not nullopt when
     * rating create again. such as the ratingScore partical update.
     * secondaryUri, backgroundUri is the same.
     */
    auto sourceInfo = ImageSourceInfo::CreateImageSourceInfoWithHost(GetHost());
    if (!layoutProperty->HasForegroundImageSourceInfo()) {
        isForegroundImageInfoFromTheme_ = true;
        sourceInfo.SetResourceId(ratingTheme->GetForegroundResourceId());
        foregroundImageSourceInfo_ = sourceInfo;
    } else {
        sourceInfo = layoutProperty->GetForegroundImageSourceInfo().value();
    }
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (!iconPath.empty()) {
        sourceInfo.SetSrc(iconPath, ratingTheme->GetStarColorActive());
    }
    if (sourceInfo.IsSvg()) {
        foregroundConfig_.isSvg_ = true;
    }
    // Recreate ImageLoadingContext only when image source info has changed.
    if (!foregroundImageLoadingCtx_ || (foregroundImageLoadingCtx_->GetSourceInfo() != sourceInfo)) {
        // Construct the ImageLoadingContext and register the image life cycle callback.
        LoadNotifier loadNotifierForegroundImage(
            CreateDataReadyCallback(0b001), CreateLoadSuccessCallback(0b001), CreateLoadFailCallback(0b001));
        foregroundImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifierForegroundImage));
        foregroundImageLoadingCtx_->LoadImageData();
    }
}

void RatingPattern::LoadSecondary(const RefPtr<RatingLayoutProperty>& layoutProperty,
    const RefPtr<RatingTheme>& ratingTheme, const RefPtr<IconTheme>& iconTheme)
{
    secondaryConfig_.isSvg_ = false;
    auto sourceInfo = ImageSourceInfo::CreateImageSourceInfoWithHost(GetHost());
    if (!layoutProperty->HasSecondaryImageSourceInfo()) {
        isSecondaryImageInfoFromTheme_ = true;
        sourceInfo.SetResourceId(ratingTheme->GetSecondaryResourceId());
        secondaryImageSourceInfo_ = sourceInfo;
    } else {
        sourceInfo = layoutProperty->GetSecondaryImageSourceInfo().value();
    }
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (!iconPath.empty()) {
        sourceInfo.SetSrc(iconPath, ratingTheme->GetStarColorInactive());
    }
    if (sourceInfo.IsSvg()) {
        secondaryConfig_.isSvg_ = true;
    }
    if (!secondaryImageLoadingCtx_ || secondaryImageLoadingCtx_->GetSourceInfo() != sourceInfo) {
        LoadNotifier loadNotifierSecondaryImage(
            CreateDataReadyCallback(0b010), CreateLoadSuccessCallback(0b010), CreateLoadFailCallback(0b010));
        secondaryImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifierSecondaryImage));
        secondaryImageLoadingCtx_->LoadImageData();
    }
}

void RatingPattern::LoadBackground(const RefPtr<RatingLayoutProperty>& layoutProperty,
    const RefPtr<RatingTheme>& ratingTheme, const RefPtr<IconTheme>& iconTheme)
{
    backgroundConfig_.isSvg_ = false;
    auto sourceInfo = ImageSourceInfo::CreateImageSourceInfoWithHost(GetHost());
    if (!layoutProperty->HasBackgroundImageSourceInfo()) {
        isBackgroundImageInfoFromTheme_ = true;
        sourceInfo.SetResourceId(ratingTheme->GetBackgroundResourceId());
        backgroundImageSourceInfo_ = sourceInfo;
    } else {
        sourceInfo = layoutProperty->GetBackgroundImageSourceInfo().value();
    }
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (!iconPath.empty()) {
        sourceInfo.SetSrc(iconPath, ratingTheme->GetStarColorInactive());
    }
    if (sourceInfo.IsSvg()) {
        backgroundConfig_.isSvg_ = true;
    }
    if (!backgroundImageLoadingCtx_ || backgroundImageLoadingCtx_->GetSourceInfo() != sourceInfo) {
        LoadNotifier loadNotifierBackgroundImage(
            CreateDataReadyCallback(0b100), CreateLoadSuccessCallback(0b100), CreateLoadFailCallback(0b100));
        backgroundImageLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifierBackgroundImage));
        backgroundImageLoadingCtx_->LoadImageData();
    }
}

void RatingPattern::LoadFocusBackground(const RefPtr<RatingLayoutProperty>& layoutProperty,
    const RefPtr<RatingTheme>& ratingTheme, const RefPtr<IconTheme>& iconTheme)
{
    backgroundFocusConfig_.isSvg_ = false;
    ImageSourceInfo sourceInfo;
    if (!layoutProperty->HasBackgroundImageSourceInfo()) {
        isBackgroundImageInfoFromTheme_ = true;
        sourceInfo.SetResourceId(ratingTheme->GetBackgroundResourceId());
        focusBackgroundImageSourceInfo_ = sourceInfo;
    } else {
        sourceInfo = layoutProperty->GetBackgroundImageSourceInfo().value();
    }
    auto iconPath = iconTheme->GetIconPath(sourceInfo.GetResourceId());
    if (!iconPath.empty()) {
        sourceInfo.SetSrc(iconPath, ratingTheme->GetUnlitStarFocusColor());
    }
    if (sourceInfo.IsSvg()) {
        backgroundFocusConfig_.isSvg_ = true;
    }
    if (!backgroundImageFocusLoadingCtx_ || backgroundImageFocusLoadingCtx_->GetSourceInfo() != sourceInfo) {
        LoadNotifier loadNotifierBackgroundImage(
            CreateDataReadyCallback(0b1000), CreateLoadSuccessCallback(0b1000), CreateLoadFailCallback(0b1000));
        backgroundImageFocusLoadingCtx_ =
            AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, std::move(loadNotifierBackgroundImage));
        backgroundImageFocusLoadingCtx_->LoadImageData();
    }
}

void RatingPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
        HandleEnabled();
    }
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto layoutProperty = host->GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    // Reset image state code.
    imageReadyStateCode_ = 0;
    imageSuccessStateCode_ = 0;
    // Constrains ratingScore and starNum in case of the illegal input.
    ConstrainsRatingScore(layoutProperty);

    LoadForeground(layoutProperty, ratingTheme, iconTheme);
    LoadSecondary(layoutProperty, ratingTheme, iconTheme);
    LoadBackground(layoutProperty, ratingTheme, iconTheme);
    if (IsNeedFocusStyle()) {
        LoadFocusBackground(layoutProperty, ratingTheme, iconTheme);
    }
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    bool isIndicator = IsIndicator();
    if (!isIndicator) {
        InitTouchEvent(gestureHub);
        InitPanEvent(gestureHub);
        InitClickEvent(gestureHub);
    }
    InitMouseEvent();
    // Init touch, pan, click and key event and register callback.
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
}

void RatingPattern::HandleEnabled()
{
    if (UseContentModifier()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(theme);
    auto alpha = theme->GetDisabledAlpha();
    auto originalOpacity = renderContext->GetOpacityValue(1.0f);
    renderContext->OnOpacityUpdate(enabled ? originalOpacity : alpha * originalOpacity);
}

// XTS inspector code
void RatingPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto ratingLayoutProperty = GetLayoutProperty<RatingLayoutProperty>();
    if (isForegroundImageInfoFromTheme_) {
        json->PutExtAttr("foregroundImageSourceInfo", ImageSourceInfo("").ToString().c_str(), filter);
    } else {
        auto foregroundImageSourceInfo =
            ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(ImageSourceInfo(""));
        json->PutExtAttr("foregroundImageSourceInfo", foregroundImageSourceInfo.ToString().c_str(), filter);
    }
    if (isSecondaryImageInfoFromTheme_) {
        json->PutExtAttr("secondaryImageSourceInfo", ImageSourceInfo("").ToString().c_str(), filter);
    } else {
        auto secondaryImageSourceInfo =
            ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo(""));
        json->PutExtAttr("secondaryImageSourceInfo", secondaryImageSourceInfo.ToString().c_str(), filter);
    }
    if (isBackgroundImageInfoFromTheme_) {
        json->PutExtAttr("backgroundImageSourceInfo", ImageSourceInfo("").ToString().c_str(), filter);
    } else {
        auto backgroundImageSourceInfo =
            ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo(""));
        json->PutExtAttr("backgroundImageSourceInfo", backgroundImageSourceInfo.ToString().c_str(), filter);
    }
}

void RatingPattern::MarkDirtyNode(const PropertyChangeFlag& flag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(flag);
}

void RatingPattern::PrepareAnimation(const RefPtr<CanvasImage>& image)
{
    if (image->IsStatic()) {
        return;
    }
    SetRedrawCallback(image);
    // RegisterVisibleAreaChange
    auto layoutProps = GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    // pause animation if prop is initially set to invisible
    if (layoutProps->GetVisibility().value_or(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
        image->ControlAnimation(false);
    } else {
        image->ControlAnimation(true);
    }
}

void RatingPattern::SetRedrawCallback(const RefPtr<CanvasImage>& image)
{
    CHECK_NULL_VOID(image);
    // set animation flush function for svg / gif
    image->SetRedrawCallback([weak = WeakPtr(GetHost())] {
        auto ratingNode = weak.Upgrade();
        CHECK_NULL_VOID(ratingNode);
        ratingNode->MarkNeedRenderOnly();
    });
}

void RatingPattern::FireBuilder()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!makeFunc_.has_value()) {
        host->RemoveChildAtIndex(0);
        host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto node = BuildContentModifierNode();
    if (contentModifierNode_ == node) {
        return;
    }
    host->RemoveChildAtIndex(0);
    contentModifierNode_ = node;
    CHECK_NULL_VOID(contentModifierNode_);
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> RatingPattern::BuildContentModifierNode()
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto property = GetLayoutProperty<RatingLayoutProperty>();
    CHECK_NULL_RETURN(property, nullptr);
    auto renderProperty = GetPaintProperty<RatingRenderProperty>();
    CHECK_NULL_RETURN(renderProperty, nullptr);
    auto starNum = property->GetStarsValue(themeStarNum_);
    auto isIndicator = IsIndicator();
    auto ratingScore = renderProperty->GetRatingScoreValue(themeRatingScore_);
    auto stepSize = renderProperty->GetStepSizeValue(themeStepSize_);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto enabled = eventHub->IsEnabled();
    RatingConfiguration ratingConfiguration(starNum, isIndicator, ratingScore, stepSize, enabled);
    return (makeFunc_.value())(ratingConfiguration);
}
} // namespace OHOS::Ace::NG
