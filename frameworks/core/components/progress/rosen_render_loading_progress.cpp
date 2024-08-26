/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/progress/rosen_render_loading_progress.h"

namespace OHOS::Ace {
namespace {

constexpr double BG_START = 90.0;
constexpr double BG_END = 270.0;
constexpr float CAMERA_ROTATE_X = -23.3f;
constexpr float CAMERA_ROTATE_Y = -90.0f;
constexpr uint8_t RING_ALPHA = 200;
constexpr uint8_t RING_BG_BLUR_ALPHA = 150;

} // namespace

void RosenRenderLoadingProgress::Paint(RenderContext& context, const Offset& offset)
{
    if (cometParams_.empty()) {
        LOGE("no comet need to paint.");
        return;
    }

    const auto renderContext = static_cast<RosenRenderContext*>(&context);
    auto canvas = renderContext->GetCanvas();
    if (canvas == nullptr) {
        LOGE("canvas is nullptr");
        return;
    }

    // Paint the Ring first when ring in front.
    if (cometParams_[0].angular > BG_START && cometParams_[0].angular < BG_END) {
        PaintComet(canvas, offset + center_ + ringOffset_);
        PaintRing(canvas, offset + center_ + ringOffset_);
    } else {
        PaintRing(canvas, offset + center_ + ringOffset_);
        PaintComet(canvas, offset + center_ + ringOffset_);
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderLoadingProgress::PaintRing(SkCanvas* canvas, const Offset& offset)
{
    SkPaint ringPaint;
    uint8_t ringAlpha = RING_ALPHA;
    // Need to Paint Ring Blur effect when Dark Mode.
    if (progressColor_ == PROGRESS_COLOR_DARK) {
        ringPaint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle, ringBlurRadius_ * scale_));
        SkPaint ringBgPaint;
        ringBgPaint.setStyle(SkPaint::Style::kStroke_Style);
        ringBgPaint.setStrokeWidth(ringBgWidth_ * scale_);
        ringBgPaint.setColor(progressColor_.GetValue());
        ringBgPaint.setAlpha(RING_BG_BLUR_ALPHA * dragAlpha_ * exitAlpha_);
        ringBgPaint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle, ringBgBlurRadius_ * scale_));
        canvas->drawCircle(offset.GetX(), offset.GetY(), ringRadius_ * scale_ * dragScale_ * exitScale_, ringBgPaint);
        ringAlpha = UINT8_MAX;
    }
    ringAlpha = ringAlpha * progressColor_.GetAlpha() / UINT8_MAX;
    ringPaint.setAntiAlias(true);
    ringPaint.setStyle(SkPaint::Style::kStroke_Style);
    ringPaint.setStrokeWidth(ringWidth_ * scale_);
    ringPaint.setColor(progressColor_.GetValue());
    ringPaint.setAlpha(ringAlpha * dragAlpha_ * exitAlpha_);
    canvas->drawCircle(offset.GetX(), offset.GetY(), ringRadius_ * scale_ * dragScale_ * exitScale_, ringPaint);
}
#else
void RosenRenderLoadingProgress::PaintRing(RSCanvas* canvas, const Offset& offset)
{
    RSPen ringPen;
    uint8_t ringAlpha = RING_ALPHA;
    // Need to Paint Ring Blur effect when Dark Mode.
    if (progressColor_ == PROGRESS_COLOR_DARK) {
        RSFilter filter;
        filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, ringBlurRadius_ * scale_));
        ringPen.SetFilter(filter);
        RSPen ringBgPen;
        ringBgPen.SetWidth(ringBgWidth_ * scale_);
        ringBgPen.SetColor(progressColor_.GetValue());
        ringBgPen.SetAlpha(RING_BG_BLUR_ALPHA * dragAlpha_ * exitAlpha_);
        RSFilter bgFilter;
        bgFilter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, ringBgBlurRadius_ * scale_));
        ringBgPen.SetFilter(bgFilter);
        canvas->AttachPen(ringBgPen);
        canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), ringRadius_ * scale_ * dragScale_ * exitScale_);
        canvas->DetachPen();
        ringAlpha = UINT8_MAX;
    }
    ringAlpha = ringAlpha * progressColor_.GetAlpha() / UINT8_MAX;
    ringPen.SetAntiAlias(true);
    ringPen.SetWidth(ringWidth_ * scale_);
    ringPen.SetColor(progressColor_.GetValue());
    ringPen.SetAlpha(ringAlpha * dragAlpha_ * exitAlpha_);
    canvas->AttachPen(ringPen);
    canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), ringRadius_ * scale_ * dragScale_ * exitScale_);
    canvas->DetachPen();
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderLoadingProgress::PaintComet(SkCanvas* canvas, const Offset& offset)
#else
void RosenRenderLoadingProgress::PaintComet(RSCanvas* canvas, const Offset& offset)
#endif
{
    // Init the Camera Degree and Location when first paint.
    if (!camera_) {
#ifndef USE_ROSEN_DRAWING
        camera_ = new Sk3DView();
        camera_->rotateY(CAMERA_ROTATE_Y);
        camera_->rotateX(CAMERA_ROTATE_X);
        camera_->save();
        camera_->setCameraLocation(camera_->getCameraLocationX(), 1.0f, camera_->getCameraLocationZ());
#else
        camera_ = new RSCamera3D();
        camera_->RotateYDegrees(CAMERA_ROTATE_Y);
        camera_->RotateXDegrees(CAMERA_ROTATE_X);
        camera_->Save();
        camera_->SetCameraPos(camera_->GetCameraPosX(), 1.0f, camera_->GetCameraPosZ());
#endif
    }

    // Scale changed will effect the locationOffsetY_.
    if (!NearEqual(usedScale_, scale_)) {
        usedScale_ = scale_;
        cometCenter_.SetX(orbitRadius_);
        Offset locationOffset;
        RotateCalculate(cometCenter_ * usedScale_, locationOffset, 0.0f);
        locationOffsetY_ = locationOffset.GetY();
    }

    // Paint Comet Head and Tail.
    Offset rotatePos;
#ifndef USE_ROSEN_DRAWING
    SkPaint tailPaint;
    tailPaint.setAntiAlias(true);
    tailPaint.setStyle(SkPaint::Style::kFill_Style);
    tailPaint.setColor(progressColor_.GetValue());
#else
    RSBrush tailBrush;
    tailBrush.SetAntiAlias(true);
    tailBrush.SetColor(progressColor_.GetValue());
#endif
    double colorAlpha = 1.0 * progressColor_.GetAlpha() / UINT8_MAX;
    for (CometParam para : cometParams_) {
        if (para.alpha == 0) {
            return;
        }
#ifndef USE_ROSEN_DRAWING
        tailPaint.setAlpha(para.alpha * exitAlpha_ * colorAlpha);
        RotateCalculate(cometCenter_ * scale_, rotatePos, para.angular);
        canvas->drawCircle(offset.GetX() + rotatePos.GetX(), offset.GetY() + rotatePos.GetY() - locationOffsetY_,
            cometRadius_ * para.scale * scale_ * exitScale_, tailPaint);
#else
        tailBrush.SetAlpha(para.alpha * exitAlpha_ * colorAlpha);
        RotateCalculate(cometCenter_ * scale_, rotatePos, para.angular);
        canvas->AttachBrush(tailBrush);
        canvas->DrawCircle(
            RSPoint(offset.GetX() + rotatePos.GetX(), offset.GetY() + rotatePos.GetY() - locationOffsetY_),
            cometRadius_ * para.scale * scale_ * exitScale_);
        canvas->DetachBrush();
#endif
    }
}

// Convert 2D position to 3D position according to the angle of rotation.
void RosenRenderLoadingProgress::RotateCalculate(const Offset& src, Offset& dst, float degrees)
{
#ifndef USE_ROSEN_DRAWING
    camera_->rotateY(degrees);
    SkPoint point;
    point.set(src.GetX(), src.GetY());
    SkMatrix matrix;
    camera_->getMatrix(&matrix);
    matrix.mapPoints(&point, &point, 1);
    dst.SetX(point.fX);
    dst.SetY(point.fY);
    camera_->restore();
    camera_->save();
#else
    camera_->RotateYDegrees(degrees);
    std::vector<RSPoint> point(1);
    point[0] = RSPoint(src.GetX(), src.GetY());
    RSMatrix matrix;
    camera_->ApplyToMatrix(matrix);
    matrix.MapPoints(point, point, 1);
    dst.SetX(point[0].GetX());
    dst.SetY(point[0].GetY());
    camera_->Restore();
    camera_->Save();
#endif
}

} // namespace OHOS::Ace
