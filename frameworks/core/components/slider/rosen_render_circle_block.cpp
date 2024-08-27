/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/slider/rosen_render_circle_block.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkMaskFilter.h"
#include "include/core/SkPath.h"
#include "include/core/SkRRect.h"
#endif

#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

constexpr double BORDER_WEIGHT = 0.33;
constexpr double HALF = 0.5;
constexpr double RADIUS_PADDING = 4.0;
constexpr Dimension HOVER_RADIUS = 12.0_vp;
constexpr Dimension PRESS_RADIUS = 12.0_vp;
constexpr Dimension FOCUS_BORDER_PADDING = 2.0_vp;
constexpr uint32_t FOCUS_BORDER_COLOR = 0xFF0A59F7;
constexpr uint32_t HOVER_BORDER_COLOR = 0x0C000000;
constexpr uint32_t PRESS_BORDER_COLOR = 0x19000000;
} // namespace

void RosenRenderCircleBlock::Update(const RefPtr<Component>& component)
{
    RenderBlock::Update(component);
}

void RosenRenderCircleBlock::SyncGeometryProperties()
{
    RenderBlock::SyncGeometryProperties();
    auto rsNode = GetRSNode();
    if (!rsNode) {
        return;
    }

    double radius = NormalizeToPx(blockSize_) * HALF * radiusScale_;
    double diameter = radius * 2.0;
    auto frame = rsNode->GetStagingProperties().GetFrame();
#ifndef USE_ROSEN_DRAWING
    SkRect rect = SkRect::MakeXYWH(frame.x_ - radius, frame.y_ - radius, diameter, diameter);

    float elevationOfDefaultShadowXS = 4.0f;
    float transRatio = elevationOfDefaultShadowXS / (LIGHT_HEIGHT - elevationOfDefaultShadowXS);
    float spotRatio = LIGHT_HEIGHT / (LIGHT_HEIGHT - elevationOfDefaultShadowXS);

    SkRect spotRect = SkRect::MakeLTRB(rect.left() * spotRatio, rect.top() * spotRatio,
        rect.right() * spotRatio, rect.bottom() * spotRatio);
    spotRect.offset(-transRatio * LIGHT_POSITION_X, -transRatio * LIGHT_POSITION_Y);
    spotRect.outset(transRatio * LIGHT_RADIUS, transRatio * LIGHT_RADIUS);

    SkRect shadowRect = rect;
    float ambientBlur = 2.0f;
    shadowRect.outset(ambientBlur, ambientBlur);
    shadowRect.join(spotRect);
    shadowRect.outset(1, 1);

    float offsetX = 0.0f;
    float offsetY = 0.0f;
    if (isHover_) {
        double hoverRadius = NormalizeToPx(HOVER_RADIUS);
        offsetX = hoverRadius > shadowRect.width() * HALF ? hoverRadius : shadowRect.width() * HALF;
        offsetY = hoverRadius > shadowRect.height() * HALF ? hoverRadius : shadowRect.height() * HALF;
    } else if (isPress_) {
        double pressRadius = NormalizeToPx(PRESS_RADIUS);
        offsetX = pressRadius > shadowRect.width() * HALF ? pressRadius : shadowRect.width() * HALF;
        offsetY = pressRadius > shadowRect.height() * HALF ? pressRadius : shadowRect.height() * HALF;
    } else {
        offsetX = shadowRect.width() * HALF;
        offsetY = shadowRect.height() * HALF;
    }
#else
    RSRect rect =
        RSRect(frame.x_ - radius, frame.y_ - radius,
            diameter + frame.x_ - radius, diameter + frame.y_ - radius);

    float elevationOfDefaultShadowXS = 4.0f;
    float transRatio = elevationOfDefaultShadowXS / (LIGHT_HEIGHT - elevationOfDefaultShadowXS);
    float spotRatio = LIGHT_HEIGHT / (LIGHT_HEIGHT - elevationOfDefaultShadowXS);

    auto spotRect = RSRect(rect.GetLeft() * spotRatio, rect.GetTop() * spotRatio,
        rect.GetRight() * spotRatio, rect.GetBottom() * spotRatio);
    spotRect.Offset(-transRatio * LIGHT_POSITION_X, -transRatio * LIGHT_POSITION_Y);
    spotRect.SetLeft(spotRect.GetLeft() - transRatio * LIGHT_RADIUS);
    spotRect.SetTop(spotRect.GetTop() - transRatio * LIGHT_RADIUS);
    spotRect.SetRight(spotRect.GetRight() + transRatio * LIGHT_RADIUS);
    spotRect.SetBottom(spotRect.GetBottom() + transRatio * LIGHT_RADIUS);

    RSRect shadowRect(rect);
    float ambientBlur = 2.0f;
    shadowRect.SetLeft(shadowRect.GetLeft() - ambientBlur);
    shadowRect.SetTop(shadowRect.GetTop() - ambientBlur);
    shadowRect.SetRight(shadowRect.GetRight() + ambientBlur);
    shadowRect.SetBottom(shadowRect.GetBottom() + ambientBlur);
    shadowRect.Join(spotRect);
    shadowRect.SetLeft(shadowRect.GetLeft() - 1);
    shadowRect.SetTop(shadowRect.GetTop() - 1);
    shadowRect.SetRight(shadowRect.GetRight() + 1);
    shadowRect.SetBottom(shadowRect.GetBottom() + 1);

    float offsetX = 0.0f;
    float offsetY = 0.0f;
    if (isHover_) {
        double hoverRadius = NormalizeToPx(HOVER_RADIUS);
        offsetX = hoverRadius > shadowRect.GetWidth() * HALF ? hoverRadius : shadowRect.GetWidth() * HALF;
        offsetY = hoverRadius > shadowRect.GetHeight() * HALF ? hoverRadius : shadowRect.GetHeight() * HALF;
    } else if (isPress_) {
        double pressRadius = NormalizeToPx(PRESS_RADIUS);
        offsetX = pressRadius > shadowRect.GetWidth() * HALF ? pressRadius : shadowRect.GetWidth() * HALF;
        offsetY = pressRadius > shadowRect.GetHeight() * HALF ? pressRadius : shadowRect.GetHeight() * HALF;
    } else {
        offsetX = shadowRect.GetWidth() * HALF;
        offsetY = shadowRect.GetHeight() * HALF;
    }
#endif
    rsNode->SetFrame(frame.x_ - offsetX, frame.y_ - offsetY, frame.z_ + offsetX, frame.w_ + offsetY);
}

void RosenRenderCircleBlock::Paint(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("canvas fetch failed");
        return;
    }

#ifndef USE_ROSEN_DRAWING
    if (isHover_) {
        SkPaint hoverPaint;
        hoverPaint.setColor(HOVER_BORDER_COLOR);
        double hoverRadius = NormalizeToPx(HOVER_RADIUS);
        canvas->drawCircle(offset.GetX(), offset.GetY(), hoverRadius, hoverPaint);
    }

    if (isPress_) {
        SkPaint pressPaint;
        pressPaint.setColor(PRESS_BORDER_COLOR);
        double pressRadius = NormalizeToPx(PRESS_RADIUS);
        canvas->drawCircle(offset.GetX(), offset.GetY(), pressRadius, pressPaint);
    }
#else
    if (isHover_) {
        RSBrush brush;
        brush.SetColor(HOVER_BORDER_COLOR);
        double hoverRadius = NormalizeToPx(HOVER_RADIUS);
        canvas->AttachBrush(brush);
        canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), hoverRadius);
        canvas->DetachBrush();
    }

    if (isPress_) {
        RSBrush brush;
        brush.SetColor(PRESS_BORDER_COLOR);
        double pressRadius = NormalizeToPx(PRESS_RADIUS);
        canvas->AttachBrush(brush);
        canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), pressRadius);
        canvas->DetachBrush();
    }
#endif

    double radius = NormalizeToPx(blockSize_) * HALF * radiusScale_;

    PaintShadow(context, offset, radius);

#ifndef USE_ROSEN_DRAWING
    if (GetFocus() && GetMode() == SliderMode::OUTSET) {
        SkPaint focusPaint;
        focusPaint.setColor(FOCUS_BORDER_COLOR);
        focusPaint.setStyle(SkPaint::Style::kStroke_Style);
        focusPaint.setStrokeWidth(NormalizeToPx(FOCUS_BORDER_PADDING));
        focusPaint.setAntiAlias(true);
        canvas->drawCircle(offset.GetX(), offset.GetY(), radius + RADIUS_PADDING, focusPaint);
        SkPaint blockPaint;
        blockPaint.setColor(SkColorSetARGB(GetBlockColor().GetAlpha(), GetBlockColor().GetRed(),
            GetBlockColor().GetGreen(), GetBlockColor().GetBlue()));
        blockPaint.setAntiAlias(true);
        canvas->drawCircle(offset.GetX(), offset.GetY(), radius, blockPaint);
    } else {
        SkPaint blockPaint;
        blockPaint.setColor(SkColorSetARGB(GetBlockColor().GetAlpha(), GetBlockColor().GetRed(),
            GetBlockColor().GetGreen(), GetBlockColor().GetBlue()));
        blockPaint.setAntiAlias(true);
        canvas->drawCircle(offset.GetX(), offset.GetY(), radius, blockPaint);
    }

    // Draw block border
    SkPaint borderPaint;
    // use this color to reduce the loss at corner.
    static const uint8_t alpha = 13;
    borderPaint.setColor(SkColorSetARGB(alpha, 0, 0, 0));
    borderPaint.setStyle(SkPaint::Style::kStroke_Style);
    borderPaint.setAntiAlias(true);
    borderPaint.setStrokeWidth(BORDER_WEIGHT);
    canvas->drawCircle(offset.GetX(), offset.GetY(), radius, borderPaint);
#else
    if (GetFocus() && GetMode() == SliderMode::OUTSET) {
        RSPen focusPen;
        focusPen.SetColor(FOCUS_BORDER_COLOR);
        focusPen.SetWidth(NormalizeToPx(FOCUS_BORDER_PADDING));
        focusPen.SetAntiAlias(true);
        canvas->AttachPen(focusPen);
        canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), radius + RADIUS_PADDING);
        canvas->DetachPen();
        RSBrush brush;
        brush.SetColor(RSColor::ColorQuadSetARGB(GetBlockColor().GetAlpha(),
            GetBlockColor().GetRed(), GetBlockColor().GetGreen(), GetBlockColor().GetBlue()));
        brush.SetAntiAlias(true);
        canvas->AttachBrush(brush);
        canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), radius);
        canvas->DetachBrush();
    } else {
        RSBrush brush;
        brush.SetColor(RSColor::ColorQuadSetARGB(GetBlockColor().GetAlpha(),
            GetBlockColor().GetRed(), GetBlockColor().GetGreen(), GetBlockColor().GetBlue()));
        brush.SetAntiAlias(true);
        canvas->AttachBrush(brush);
        canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), radius);
        canvas->DetachBrush();
    }

    // Draw block border
    RSPen blockPen;
    // use this color to reduce the loss at corner.
    static const uint8_t alpha = 13;
    blockPen.SetColor(RSColor::ColorQuadSetARGB(alpha, 0, 0, 0));
    blockPen.SetAntiAlias(true);
    blockPen.SetWidth(BORDER_WEIGHT);
    canvas->AttachPen(blockPen);
    canvas->DrawCircle(RSPoint(offset.GetX(), offset.GetY()), radius);
    canvas->DetachPen();
#endif
}

void RosenRenderCircleBlock::PaintShadow(RenderContext& context, const Offset& offset, double radius)
{
    double diameter = radius * 2.0;
#ifndef USE_ROSEN_DRAWING
    SkRect rect = SkRect::MakeXYWH(offset.GetX() - radius, offset.GetY() - radius, diameter, diameter);
    RosenDecorationPainter::PaintShadow(SkPath().addRRect(SkRRect::MakeRectXY(rect, radius, radius)),
        ShadowConfig::DefaultShadowXS, static_cast<RosenRenderContext*>(&context)->GetCanvas());
#else
    RSRect rect =
        RSRect(offset.GetX() - radius, offset.GetY() - radius,
            diameter + offset.GetX() - radius, diameter + offset.GetY() - radius);
    RSRecordingPath path;
    path.AddRoundRect(rect, radius, radius);
    RosenDecorationPainter::PaintShadow(
        path, ShadowConfig::DefaultShadowXS, static_cast<RosenRenderContext*>(&context)->GetCanvas());
#endif
}

} // namespace OHOS::Ace
