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

#include "core/components_ng/pattern/image/image_paint_method.h"

namespace {
constexpr unsigned int TOP_LEFT = 0;
constexpr unsigned int TOP_RIGHT = 1;
constexpr unsigned int BOTTOM_LEFT = 2;
constexpr unsigned int BOTTOM_RIGHT = 3;
} // namespace

namespace OHOS::Ace::NG {
void ImagePaintMethod::UpdateBorderRadius(PaintWrapper* paintWrapper)
{
    auto renderCtx = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    auto borderRadius = renderCtx->GetBorderRadius();

    BorderRadiusArray radiusXY = {
        PointF(borderRadius->radiusTopLeft->ConvertToPx(), borderRadius->radiusTopLeft->ConvertToPx()),
        PointF(borderRadius->radiusTopRight->ConvertToPx(), borderRadius->radiusTopRight->ConvertToPx()),
        PointF(borderRadius->radiusBottomLeft->ConvertToPx(), borderRadius->radiusBottomLeft->ConvertToPx()),
        PointF(borderRadius->radiusBottomRight->ConvertToPx(), borderRadius->radiusBottomRight->ConvertToPx())
    };

    // adjust image radius to match border (concentric round rects)
    auto width = renderCtx->GetBorderWidth();
    if (width) {
        if (width->leftDimen) {
            auto diff = width->leftDimen->ConvertToPx();
            radiusXY[TOP_LEFT].SetX(radiusXY[TOP_LEFT].GetX() - diff);
            radiusXY[BOTTOM_LEFT].SetX(radiusXY[BOTTOM_LEFT].GetX() - diff);
        }
        if (width->rightDimen) {
            auto diff = width->rightDimen->ConvertToPx();
            radiusXY[TOP_RIGHT].SetX(radiusXY[TOP_RIGHT].GetX() - diff);
            radiusXY[BOTTOM_RIGHT].SetX(radiusXY[BOTTOM_RIGHT].GetX() - diff);
        }
        if (width->topDimen) {
            auto diff = width->topDimen->ConvertToPx();
            radiusXY[TOP_LEFT].SetY(radiusXY[TOP_LEFT].GetY() - diff);
            radiusXY[TOP_RIGHT].SetY(radiusXY[TOP_RIGHT].GetY() - diff);
        }
        if (width->bottomDimen) {
            auto diff = width->bottomDimen->ConvertToPx();
            radiusXY[BOTTOM_LEFT].SetY(radiusXY[BOTTOM_LEFT].GetY() - diff);
            radiusXY[BOTTOM_RIGHT].SetY(radiusXY[BOTTOM_RIGHT].GetY() - diff);
        }
    }
    auto&& config = canvasImage_->GetPaintConfig();
    config.borderRadiusXY_ = std::make_shared<BorderRadiusArray>(std::move(radiusXY));
}

void ImagePaintMethod::UpdatePaintConfig(const RefPtr<ImageRenderProperty>& renderProps, PaintWrapper* paintWrapper)
{
    auto&& config = canvasImage_->GetPaintConfig();
    config.renderMode_ = renderProps->GetImageRenderMode().value_or(ImageRenderMode::ORIGINAL);
    config.imageInterpolation_ = renderProps->GetImageInterpolation().value_or(ImageInterpolation::NONE);
    config.imageRepeat_ = renderProps->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
    auto pipelineCtx = PipelineBase::GetCurrentContext();
    bool isRightToLeft = pipelineCtx && pipelineCtx->IsRightToLeft();
    config.needFlipCanvasHorizontally_ = isRightToLeft && renderProps->GetMatchTextDirection().value_or(false);
    auto colorFilterMatrix = renderProps->GetColorFilter();
    if (colorFilterMatrix.has_value()) {
        config.colorFilter_ = std::make_shared<std::vector<float>>(colorFilterMatrix.value());
    }
    if (renderProps->GetNeedBorderRadiusValue(false)) {
        UpdateBorderRadius(paintWrapper);
    }
    // scale for recordingCanvas: take padding into account
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto contentSize = paintWrapper->GetContentSize();
    config.scaleX_ = contentSize.Width() / frameSize.Width();
    config.scaleY_ = contentSize.Height() / frameSize.Height();
}

CanvasDrawFunction ImagePaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(canvasImage_, nullptr);
    auto offset = paintWrapper->GetContentOffset();
    auto contentSize = paintWrapper->GetContentSize();

    // update render props to ImagePaintConfig
    auto props = DynamicCast<ImageRenderProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(props, nullptr);
    UpdatePaintConfig(props, paintWrapper);
    ImagePainter imagePainter(canvasImage_);
    return
        [imagePainter, offset, contentSize](RSCanvas& canvas) { imagePainter.DrawImage(canvas, offset, contentSize); };
}
} // namespace OHOS::Ace::NG