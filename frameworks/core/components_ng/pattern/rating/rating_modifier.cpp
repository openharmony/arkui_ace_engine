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

namespace OHOS::Ace::NG {
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

void RatingModifier::PaintBoard(DrawingContext& context)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    // animate color
    LinearColor bgColor = boardColor_->Get();
    auto pressBorderRadius = ratingTheme->GetFocusBorderRadius();
    auto& canvas = context.canvas;
    auto starNum = starNum_->Get();
    CHECK_EQUAL_VOID(starNum, 0);
    auto singleStarImagePaintConfig = foregroundImageCanvas_->GetPaintConfig();
    const float singleStarWidth = contentSize_->Get().Width() / static_cast<float>(starNum);
    const float singleStarHeight = contentSize_->Get().Height();
    auto offset = contentOffset_->Get();
    auto touchStar = touchStar_->Get();
    if (touchStar >= 0 && touchStar < starNum) {
        RSBrush rsBrush(ToRSColor(bgColor));
        rsBrush.SetAntiAlias(true);
        const RSRect rsRect(offset.GetX() + singleStarWidth * static_cast<float>(touchStar), offset.GetY(),
            offset.GetX() + singleStarWidth * static_cast<float>((touchStar + 1)), offset.GetY() + singleStarHeight);
        const RSRoundRect rsRoundRect(rsRect, static_cast<float>(pressBorderRadius.ConvertToPx()),
            static_cast<float>(pressBorderRadius.ConvertToPx()));
        canvas.Save();
        canvas.ClipRoundRect(rsRoundRect, RSClipOp::INTERSECT);
        canvas.DrawBackground(rsBrush);
        canvas.Restore();
    }
}

void RatingModifier::PaintStar(DrawingContext& context)
{
    const ImagePainter foregroundImagePainter(foregroundImageCanvas_);
    const ImagePainter secondaryImagePainter(secondaryImageCanvas_);
    const ImagePainter backgroundPainter(backgroundImageCanvas_);

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
    auto contentSize = SizeF(singleStarWidth, singleStarHeight);
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
        secondaryImagePainter.DrawImage(canvas, offsetTemp, contentSize);
        offsetTemp.SetX(offsetTemp.GetX() + singleStarWidth);
        canvas.Restore();
    }

    // step4: draw background image.
    for (int32_t i = 0; i < backgroundImageRepeatNum; i++) {
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
    auto contentSize = SizeF(singleStarWidth, singleStarHeight);
    for (int32_t i = 0; i < backgroundImageRepeatNum; i++) {
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
