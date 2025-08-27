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

#include "core/components_ng/pattern/swiper/swiper_paint_method.h"

#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction SwiperPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto swiper = weak.Upgrade();
        if (swiper) {
            swiper->PaintFade(canvas, paintWrapper);
        }
    };

    return paintFunc;
}

void SwiperPaintMethod::PaintFade(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    if (!needPaintFade_) {
        return;
    }
    if (NearZero(mainDelta_)) {
        return;
    }

    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<SwiperPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // TODO use theme.
    constexpr float FADE_MAX_DISTANCE = 2000.0f;
    constexpr float FADE_MAX_TRANSLATE = 40.0f;
    constexpr float FADE_MAX_RADIUS = 2.0f;
    constexpr float FADE_ALPHA = 0.45f;
    constexpr float FADE_SCALE_RATE = 0.2f;

    bool isVertical = (axis_ == Axis::VERTICAL);
    auto frameSize = renderContext->GetPaintRectWithoutTransform();
    float width = frameSize.Width();
    float height = frameSize.Height();
    float centerX = 0.0;
    float centerY = 0.0;
    float fadeTranslate = mainDelta_ * FADE_SCALE_RATE;
    float radius = 0.0;
    if (GreatNotEqual(mainDelta_, 0.0)) {
        fadeTranslate = fadeTranslate > FADE_MAX_TRANSLATE ? FADE_MAX_TRANSLATE : fadeTranslate;
        if (isVertical) {
            centerY = -FADE_MAX_DISTANCE + mainDelta_ / FADE_SCALE_RATE;
            if (centerY > (-width * FADE_MAX_RADIUS)) {
                centerY = -width * FADE_MAX_RADIUS;
            }
            centerX = width / 2;
        } else {
            centerX = -FADE_MAX_DISTANCE + mainDelta_ / FADE_SCALE_RATE;
            if (centerX > (-FADE_MAX_RADIUS * height)) {
                centerX = (-FADE_MAX_RADIUS * height);
            }
            centerY = height / 2;
        }
        radius = sqrt(pow(centerX, 2) + pow(centerY, 2));
    } else {
        fadeTranslate = fadeTranslate > -FADE_MAX_TRANSLATE ? fadeTranslate : -FADE_MAX_TRANSLATE;
        if (isVertical) {
            centerY = height + FADE_MAX_DISTANCE + mainDelta_ / FADE_SCALE_RATE;
            if (centerY < (height + width * FADE_MAX_RADIUS)) {
                centerY = height + width * FADE_MAX_RADIUS;
            }
            centerX = width / 2;
            radius = sqrt(pow(centerY - height, 2) + pow(centerX, 2));
        } else {
            centerX = width + FADE_MAX_DISTANCE + mainDelta_ / FADE_SCALE_RATE;
            if (centerX < (width + FADE_MAX_RADIUS * height)) {
                centerX = width + FADE_MAX_RADIUS * height;
            }
            centerY = height / 2;
            radius = sqrt(pow(centerX - width, 2) + pow(centerY, 2));
        }
    }

    auto clipRect = RSRect(0, 0, width, height);
    canvas.ClipRect(clipRect, RSClipOp::INTERSECT);

    RSBrush brush;
    brush.SetColor(ToRSColor(paintProperty->GetFadeColor().value_or(Color::GRAY)));
    brush.SetAlphaF(FADE_ALPHA);
    brush.SetBlendMode(RSBlendMode::SRC_OVER);
    canvas.AttachBrush(brush);
    if (isVertical) {
        canvas.DrawCircle({ centerX, centerY + fadeTranslate }, radius);
    } else {
        canvas.DrawCircle({ centerX + fadeTranslate, centerY }, radius);
    }
    canvas.DetachBrush();
}

CanvasDrawFunction SwiperPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->ClipPadding(paintWrapper, canvas);
    };
    return paintFunc;
}

void SwiperPaintMethod::ClipPadding(PaintWrapper* paintWrapper, RSCanvas& canvas) const
{
    if (!needClipPadding_ || !paintWrapper) {
        return;
    }
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetPaddingSize();
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    auto renderContext = paintWrapper->GetRenderContext();
    if (!renderContext || renderContext->GetClipEdge().value_or(true)) {
        auto clipRect = RSRect(paddingOffset.GetX(), paddingOffset.GetY(), frameSize.Width() + paddingOffset.GetX(),
                    paddingOffset.GetY() + frameSize.Height());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    }
}

} // namespace OHOS::Ace::NG
