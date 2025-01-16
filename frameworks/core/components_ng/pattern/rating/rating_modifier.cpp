/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rating/rating_modifier.h"

#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/image_painter.h"
#include "core/components/theme/icon_theme.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t RATING_DISTANCE_TWO = 2;
}
RatingModifier::RatingModifier()
    : needDraw_(AceType::MakeRefPtr<PropertyBool>(false)), starNum_(AceType::MakeRefPtr<PropertyInt>(0)),
      touchStar_(AceType::MakeRefPtr<PropertyInt>(0)), drawScore_(AceType::MakeRefPtr<PropertyFloat>(.0f)),
      stepSize_(AceType::MakeRefPtr<PropertyFloat>(.0f)),
      useContentModifier_(AceType::MakeRefPtr<PropertyBool>(false)),
      contentOffset_(AceType::MakeRefPtr<PropertyOffsetF>(OffsetF())),
      contentSize_(AceType::MakeRefPtr<PropertySizeF>(SizeF())),
      boardColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT))),
      reverse_(AceType::MakeRefPtr<PropertyBool>(false))
{
    AttachProperty(needDraw_);
    AttachProperty(starNum_);
    AttachProperty(touchStar_);
    AttachProperty(drawScore_);
    AttachProperty(stepSize_);
    AttachProperty(useContentModifier_);
    AttachProperty(contentOffset_);
    AttachProperty(contentSize_);
    AttachProperty(boardColor_);
    AttachProperty(reverse_);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    ratingTheme_ = pipeline->GetTheme<RatingTheme>();
}

void RatingModifier::onDraw(DrawingContext& context)
{
    if (useContentModifier_->Get()) {
        return;
    }
    CHECK_NULL_VOID(foregroundImageCanvas_);
    CHECK_NULL_VOID(secondaryImageCanvas_);
    CHECK_NULL_VOID(backgroundImageCanvas_);
    // step1: check if touch down any stars.
    PaintBoard(context);
    if (reverse_ && reverse_->Get()) {
        PaintReverseStar(context);
    } else {
        PaintStar(context);
    }
    SetNeedDraw(false);
}

int32_t RatingModifier::GetTouchStar()
{
    CHECK_NULL_RETURN(starNum_, 0);
    auto starNum = starNum_->Get();
    CHECK_NULL_RETURN(touchStar_, 0);
    auto touchStar = touchStar_->Get();
    CHECK_NULL_RETURN(drawScore_, 0);
    auto drawScore = drawScore_->Get();
    auto drawNum = fmax((NearEqual(drawScore, std::round(drawScore)) ? drawScore : ceil(drawScore)) - 1, 0.0);
    if (touchStar != drawNum) {
        touchStar = drawNum;
    }
    if (reverse_ && reverse_->Get()) {
        touchStar = starNum - drawNum - 1;
    }
    return touchStar;
}

double RatingModifier::GetDistanceFromTheme()
{
    CHECK_NULL_RETURN(ratingTheme_, 0.0f);
    CHECK_NULL_RETURN(isImageInfoFromTheme_, 0.0f);
    auto isNeedSubDistance = ratingTheme_->GetFocusAndBlurCancleAnimation();
    auto distance = indicator_ ? 0.0 : (
        ratingTheme_->GetIconBoardDistance() - (isNeedSubDistance ? distance_ : 0.0_vp)).ConvertToPx();
    return distance;
}
void RatingModifier::PaintBoard(DrawingContext& context)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    // animate color
    LinearColor bgColor = boardColor_->Get();
    auto& canvas = context.canvas;
    auto starNum = starNum_->Get();
    CHECK_EQUAL_VOID(starNum, 0);
    auto singleStarImagePaintConfig = foregroundImageCanvas_->GetPaintConfig();
    const float singleStarWidth = contentSize_->Get().Width() / static_cast<float>(starNum);
    const float singleStarHeight = contentSize_->Get().Height();
    float pressBorderRadius = 0.0f;
    if (!ratingTheme->GetIsCircleRadius()) {
        pressBorderRadius = ratingTheme->GetFocusBorderRadius().ConvertToPx();
    } else {
        auto isSquare = singleStarWidth == singleStarHeight;
        pressBorderRadius = isSquare ? singleStarHeight / NUMBER_TWO
            : ratingTheme->GetFocusBorderRadius().ConvertToPx();
    }
    auto offset = contentOffset_->Get();
    auto touchStar = GetTouchStar();
    if (touchStar >= 0 && touchStar < starNum) {
        bool isCircleBoard = static_cast<bool>(ratingTheme->GetFocusAndBlurCancleAnimation());
        RSBrush rsBrush(ToRSColor(bgColor));
        rsBrush.SetAntiAlias(true);
        if (!isCircleBoard || (isCircleBoard && singleStarWidth != singleStarHeight)) {
            const RSRect rsRect(offset.GetX() + singleStarWidth * static_cast<float>(touchStar),
                offset.GetY(), offset.GetX() + singleStarWidth * static_cast<float>(
                (touchStar + 1)), offset.GetY() + singleStarHeight);
            const RSRoundRect rsRoundRect(rsRect, static_cast<float>(pressBorderRadius),
                static_cast<float>(pressBorderRadius));
            canvas.Save();
            canvas.ClipRoundRect(rsRoundRect, RSClipOp::INTERSECT);
            canvas.DrawBackground(rsBrush);
            canvas.Restore();
        } else {
            RSPoint centerPt;
            centerPt.SetX(
                offset.GetX() + singleStarWidth / NUMBER_TWO + singleStarWidth * static_cast<float>(touchStar));
            centerPt.SetY(offset.GetY() + singleStarHeight / NUMBER_TWO);
            canvas.AttachBrush(rsBrush);
            canvas.DrawCircle(centerPt, pressBorderRadius);
            canvas.DetachBrush();
        }
    }
}

void RatingModifier::PaintStar(DrawingContext& context)
{
    const ImagePainter foregroundImagePainter(foregroundImageCanvas_);
    const ImagePainter secondaryImagePainter(secondaryImageCanvas_);
    const ImagePainter backgroundPainter(backgroundImageCanvas_);
    const ImagePainter backgroundFocusPainter(backgroundImageFocusCanvas_);

    auto& canvas = context.canvas;
    auto offset = contentOffset_->Get();
    auto starNum = starNum_->Get();
    CHECK_EQUAL_VOID(starNum, 0);
    auto drawScore = drawScore_->Get();
    auto config = foregroundImageCanvas_->GetPaintConfig();
    const float singleStarWidth = contentSize_->Get().Width() / static_cast<float>(starNum);
    const float singleStarHeight = contentSize_->Get().Height();
    // step2: calculate 3 images repeat times.
    const int32_t foregroundImageRepeatNum = ceil(drawScore);
    const float secondaryImageRepeatNum = foregroundImageRepeatNum - drawScore;
    const int32_t backgroundImageRepeatNum = starNum - foregroundImageRepeatNum;
    // step3: draw the foreground images.
    canvas.Save();
    auto offsetTemp = offset;
    auto distance = GetDistanceFromTheme();
    offsetTemp.SetX((static_cast<float>(offsetTemp.GetX() + distance)));
    offsetTemp.SetY((static_cast<float>(offsetTemp.GetY() + distance)));
    auto size = distance * RATING_DISTANCE_TWO;
    auto contentSize = SizeF(singleStarWidth - size, singleStarHeight - size);

    // step2.1: calculate the clip area in order to display the secondary image.
    auto clipRect1 = RSRect(offset.GetX(), offsetTemp.GetY(),
        static_cast<float>(offset.GetX() + singleStarWidth * drawScore), offset.GetY() + singleStarHeight);
    canvas.ClipRect(clipRect1, RSClipOp::INTERSECT);
    for (int32_t i = 0; i < foregroundImageRepeatNum; i++) {
        foregroundImagePainter.DrawImage(canvas, offsetTemp, contentSize);
        offsetTemp.SetX(static_cast<float>(offsetTemp.GetX() + singleStarWidth));
    }
    canvas.Restore();

    // step3: if drawScore is a decimal, it needs to draw the secondary image.
    if (secondaryImageRepeatNum != 0) {
        canvas.Save();
        auto clipRect2 = RSRect(static_cast<float>(offset.GetX() + singleStarWidth * drawScore), offsetTemp.GetY(),
            static_cast<float>(offset.GetX() + singleStarWidth * static_cast<float>(foregroundImageRepeatNum)),
            offset.GetY() + singleStarHeight);
        // step3.1: calculate the clip area which already occupied by the foreground image.
        canvas.ClipRect(clipRect2, RSClipOp::INTERSECT);
        offsetTemp.SetX(static_cast<float>(offsetTemp.GetX() - singleStarWidth));
        isFocus_ ? backgroundFocusPainter.DrawImage(canvas, offsetTemp, contentSize) :
            secondaryImagePainter.DrawImage(canvas, offsetTemp, contentSize);
        offsetTemp.SetX(offsetTemp.GetX() + singleStarWidth);
        canvas.Restore();
    }

    // step4: draw background image.
    for (int32_t i = 0; i < backgroundImageRepeatNum; i++) {
        if (i == 0 && foregroundImageRepeatNum == 0 && isFocus_) {
            backgroundFocusPainter.DrawImage(canvas, offsetTemp, contentSize);
            offsetTemp.SetX(static_cast<float>(offsetTemp.GetX() + singleStarWidth));
            continue;
        }
        backgroundPainter.DrawImage(canvas, offsetTemp, contentSize);
        if (i < backgroundImageRepeatNum - 1) {
            offsetTemp.SetX(offsetTemp.GetX() + singleStarWidth);
        }
    }
}

void RatingModifier::PaintReverseStar(DrawingContext& context)
{
    const ImagePainter foregroundImagePainter(foregroundImageCanvas_);
    const ImagePainter secondaryImagePainter(secondaryImageCanvas_);
    const ImagePainter backgroundPainter(backgroundImageCanvas_);
    const ImagePainter backgroundFocusPainter(backgroundImageFocusCanvas_);

    auto& canvas = context.canvas;
    auto offset = contentOffset_->Get();
    auto starNum = starNum_->Get();
    CHECK_EQUAL_VOID(starNum, 0);
    auto drawScore = drawScore_->Get();
    auto config = foregroundImageCanvas_->GetPaintConfig();
    const float singleStarWidth = contentSize_->Get().Width() / static_cast<float>(starNum);
    const float singleStarHeight = contentSize_->Get().Height();
    const int32_t foregroundImageRepeatNum = ceil(drawScore);
    const float secondaryImageRepeatNum = foregroundImageRepeatNum - drawScore;
    const int32_t backgroundImageRepeatNum = starNum - foregroundImageRepeatNum;
    canvas.Save();
    auto offsetTemp = offset;
    auto distance = GetDistanceFromTheme();
    offsetTemp.SetX((static_cast<float>(offsetTemp.GetX() + distance)));
    offsetTemp.SetY((static_cast<float>(offsetTemp.GetY() + distance)));
    auto size = distance * RATING_DISTANCE_TWO;
    auto contentSize = SizeF(singleStarWidth - size, singleStarHeight - size);
    for (int32_t i = 0; i < backgroundImageRepeatNum; i++) {
        if (i == backgroundImageRepeatNum - 1 && foregroundImageRepeatNum == 0 && isFocus_) {
            backgroundFocusPainter.DrawImage(canvas, offsetTemp, contentSize);
            offsetTemp.SetX(static_cast<float>(offsetTemp.GetX() + singleStarWidth));
            continue;
        }
        backgroundPainter.DrawImage(canvas, offsetTemp, contentSize);
        offsetTemp.SetX(offsetTemp.GetX() + singleStarWidth);
    }
    if (secondaryImageRepeatNum != 0) {
        canvas.Save();
        auto clipRect2 =
            RSRect(static_cast<float>(offset.GetX() + singleStarWidth * backgroundImageRepeatNum), offsetTemp.GetY(),
                static_cast<float>(offset.GetX() + singleStarWidth * (static_cast<float>(starNum) - drawScore)),
                offset.GetY() + singleStarHeight);
        canvas.ClipRect(clipRect2, RSClipOp::INTERSECT);
        isFocus_ ? backgroundFocusPainter.DrawImage(canvas, offsetTemp, contentSize) :
            secondaryImagePainter.DrawImage(canvas, offsetTemp, contentSize);
        canvas.Restore();
    }
    auto clipRect1 =
        RSRect(static_cast<float>(offset.GetX() + singleStarWidth * (static_cast<float>(starNum) - drawScore)),
            offsetTemp.GetY(), offset.GetX() + singleStarWidth * starNum, offset.GetY() + singleStarHeight);
    canvas.ClipRect(clipRect1, RSClipOp::INTERSECT);
    for (int32_t i = 0; i < foregroundImageRepeatNum; i++) {
        foregroundImagePainter.DrawImage(canvas, offsetTemp, contentSize);
        offsetTemp.SetX(static_cast<float>(offsetTemp.GetX() + singleStarWidth));
    }
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
