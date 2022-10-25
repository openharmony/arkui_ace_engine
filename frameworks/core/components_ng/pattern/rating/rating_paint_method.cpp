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
#include "core/components_ng/pattern/rating/rating_paint_method.h"

#include "draw/canvas.h"

#include "base/geometry/ng/offset_t.h"
#include "core/components/rating/rating_theme.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr Dimension PRESS_BORDER_RADIUS = 4.0_vp;
constexpr uint32_t PRESS_COLOR = 0x19000000;

CanvasDrawFunction RatingPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(foregroundImageCanvas_, nullptr);
    CHECK_NULL_RETURN(secondaryImageCanvas_, nullptr);
    CHECK_NULL_RETURN(backgroundImageCanvas_, nullptr);
    auto offset = paintWrapper->GetContentOffset();

    ImagePainter foregroundImagePainter(foregroundImageCanvas_);
    ImagePainter secondaryImagePainter(secondaryImageCanvas_);
    ImagePainter backgroundPainter(backgroundImageCanvas_);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto ratingTheme = pipelineContext->GetTheme<RatingTheme>();
    CHECK_NULL_RETURN(ratingTheme, nullptr);

    auto ratingRenderProperty = DynamicCast<RatingRenderProperty>(paintWrapper->GetPaintProperty());
    double drawScore = ratingRenderProperty->GetRatingScoreValue();
    double stepSize = ratingRenderProperty->GetStepSize().value_or(ratingTheme->GetStepSize());
    int32_t touchStar = ratingRenderProperty->GetTouchStar().value_or(0);
    return [foregroundImagePainter, secondaryImagePainter, backgroundPainter, drawScore, stepSize, touchStar,
               starNum = starNum_, offset, ImagePaintConfig = singleStarImagePaintConfig_](RSCanvas& canvas) {
        // step1: check if touch down any stars.
        float singleStarWidth = ImagePaintConfig.dstRect_.Width();
        float singleStarHeight = ImagePaintConfig.dstRect_.Height();
        if (touchStar > 0 && touchStar <= starNum) {
            RSBrush rsBrush(PRESS_COLOR);
            rsBrush.SetAntiAlias(true);
            RSRect rsRect(offset.GetX() + singleStarWidth * static_cast<float>(touchStar), offset.GetY(),
                offset.GetX() + singleStarWidth * static_cast<float>((touchStar + 1)),
                offset.GetY() + singleStarHeight);
            RSRoundRect rsRoundRect(rsRect, static_cast<float>(PRESS_BORDER_RADIUS.ConvertToPx()),
                static_cast<float>(PRESS_BORDER_RADIUS.ConvertToPx()));
            canvas.Save();
            canvas.ClipRoundRect(rsRoundRect, OHOS::Rosen::Drawing::ClipOp::INTERSECT);
            canvas.DrawBackground(rsBrush);
            canvas.Restore();
        }

        // step2: calculate 3 images repeat times.
        int32_t foregroundImageRepeatNum = ceil(drawScore);
        double secondaryImageRepeatNum = foregroundImageRepeatNum - drawScore;
        int32_t backgroundImageRepeatNum = starNum - foregroundImageRepeatNum;
        // step3: draw the foreground images.
        canvas.Save();
        auto offsetTemp = offset;
        auto contentSize = SizeF(singleStarWidth, singleStarHeight);
        // step2.1: calculate the clip area in order to display the secondary image.
        auto clipRect1 = OHOS::Rosen::Drawing::RectF(offset.GetX(), offsetTemp.GetY(),
            static_cast<float>(offset.GetX() + singleStarWidth * drawScore), offset.GetY() + singleStarHeight);
        canvas.ClipRect(clipRect1, OHOS::Rosen::Drawing::ClipOp::INTERSECT);
        for (int32_t i = 0; i < foregroundImageRepeatNum; i++) {
            foregroundImagePainter.DrawImage(canvas, offsetTemp, ImagePaintConfig);
            offsetTemp.SetX(static_cast<float>(offsetTemp.GetX() + singleStarWidth));
        }
        canvas.Restore();

        // step3: if drawScore is a decimal, it needs to draw the secondary image.
        if (secondaryImageRepeatNum != 0) {
            canvas.Save();
            auto clipRect2 = OHOS::Rosen::Drawing::RectF(
                static_cast<float>(offset.GetX() + singleStarWidth * drawScore), offsetTemp.GetY(),
                static_cast<float>(offset.GetX() + singleStarWidth * static_cast<float>(foregroundImageRepeatNum)),
                offset.GetY() + singleStarHeight);
            // step3.1: calculate the clip area which already occupied by the foreground image.
            canvas.ClipRect(clipRect2, OHOS::Rosen::Drawing::ClipOp::INTERSECT);
            offsetTemp.SetX(static_cast<float>(offsetTemp.GetX() - singleStarWidth));
            secondaryImagePainter.DrawImage(canvas, offsetTemp, ImagePaintConfig);
            offsetTemp.SetX(offsetTemp.GetX() + ImagePaintConfig.dstRect_.Width());
            canvas.Restore();
        }

        // step4: draw background image.
        for (int32_t i = 0; i < backgroundImageRepeatNum; i++) {
            backgroundPainter.DrawImage(canvas, offsetTemp, ImagePaintConfig);
            if (i < backgroundImageRepeatNum - 1) {
                offsetTemp.SetX(offsetTemp.GetX() + ImagePaintConfig.dstRect_.Width());
            }
        }
    };
}

} // namespace OHOS::Ace::NG