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

#include "core/components/text/text_theme.h"
#include "core/components_ng/render/adapter/svg_canvas_image.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {
constexpr unsigned int TOP_LEFT = 0;
constexpr unsigned int TOP_RIGHT = 1;
constexpr unsigned int BOTTOM_LEFT = 2;
constexpr unsigned int BOTTOM_RIGHT = 3;
} // namespace

namespace OHOS::Ace::NG {
namespace {
void NormalizeRadius(BorderRadiusArray& radius, const SizeF& size)
{
    auto maxRadius = std::min(size.Width(), size.Height()) / 2;
    // radius shouldn't be larger than half of image size
    for (auto&& corner : radius) {
        if (corner.GetX() > maxRadius) {
            corner.SetX(maxRadius);
        }
        if (corner.GetY() > maxRadius) {
            corner.SetY(maxRadius);
        }
    }
}
} // namespace

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

    NormalizeRadius(radiusXY, paintWrapper->GetContentSize());
    auto&& config = canvasImage_->GetPaintConfig();
    config.borderRadiusXY_ = std::make_shared<BorderRadiusArray>(radiusXY);
}

void ImagePaintMethod::UpdatePaintConfig(const RefPtr<ImageRenderProperty>& renderProps, PaintWrapper* paintWrapper)
{
    auto&& config = canvasImage_->GetPaintConfig();
    config.renderMode_ = renderProps->GetImageRenderMode().value_or(ImageRenderMode::ORIGINAL);
    config.imageInterpolation_ = renderProps->GetImageInterpolation().value_or(ImageInterpolation::NONE);
    config.imageRepeat_ = renderProps->GetImageRepeat().value_or(ImageRepeat::NO_REPEAT);
    auto pipelineCtx = PipelineBase::GetCurrentContext();
    bool isRightToLeft = pipelineCtx && pipelineCtx->IsRightToLeft();
    config.flipHorizontally_ = isRightToLeft && renderProps->GetMatchTextDirection().value_or(false);
    auto colorFilterMatrix = renderProps->GetColorFilter();
    if (colorFilterMatrix.has_value()) {
        config.colorFilter_ = std::make_shared<std::vector<float>>(colorFilterMatrix.value());
    }
    auto renderCtx = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    config.obscuredReasons_ = renderCtx->GetObscured().value_or(std::vector<ObscuredReasons>());

    if (renderProps->GetNeedBorderRadiusValue(false)) {
        UpdateBorderRadius(paintWrapper);
    }
}

CanvasDrawFunction ImagePaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(canvasImage_, nullptr);
    auto contentSize = paintWrapper->GetContentSize();

    // update render props to ImagePaintConfig
    auto props = DynamicCast<ImageRenderProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(props, nullptr);
    UpdatePaintConfig(props, paintWrapper);
    if (InstanceOf<SvgCanvasImage>(canvasImage_)) {
        DynamicCast<SvgCanvasImage>(canvasImage_)->SetFillColor(props->GetSvgFillColor());
    }
    ImagePainter imagePainter(canvasImage_);
    return [imagePainter, contentSize](RSCanvas& canvas) { imagePainter.DrawImage(canvas, {}, contentSize); };
}

CanvasDrawFunction ImagePaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    // draw selected mask effect
    CHECK_NULL_RETURN_NOLOG(selected_, {});

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto theme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, {});
    auto selectedColor = theme->GetSelectedColor();
    return [selectedColor, size = paintWrapper->GetContentSize(), offset = paintWrapper->GetContentOffset()](
               RSCanvas& canvas) {
        canvas.Save();
        RSBrush brush;
        brush.SetAntiAlias(true);
        brush.SetColor(selectedColor.GetValue());
        canvas.AttachBrush(brush);

        canvas.DrawRect(
            RSRect(offset.GetX(), offset.GetY(), offset.GetX() + size.Width(), offset.GetY() + size.Height()));

        canvas.DetachBrush();
        canvas.Restore();
    };
}
} // namespace OHOS::Ace::NG