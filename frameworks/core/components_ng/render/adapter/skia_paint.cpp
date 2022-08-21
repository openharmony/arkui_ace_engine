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

#include "core/components_ng/render/adapter/skia_paint.h"

#include "core/components_ng/render/adapter/skia_color_filter.h"

namespace OHOS::Ace::NG {

#ifndef NG_BUILD
SkFilterQuality ToSkFilterQuality(FilterQuality quality)
{
    // keep FilterQuality define same with SkFilterQuality
    return static_cast<SkFilterQuality>(quality);
}
#endif

SkPaint::Style ToSkStyle(PaintStyle style)
{
    // keep PaintStyle define same with Style in skia
    return static_cast<SkPaint::Style>(style);
}

SkBlendMode ToSkBlendMode(BlendMode blendMode)
{
    // keep BlendMode define same with SkBlendMode in skia
    return static_cast<SkBlendMode>(blendMode);
}

RefPtr<Paint> Paint::Create()
{
    return AceType::MakeRefPtr<SkiaPaint>();
}

void SkiaPaint::Reset()
{
    rawPaint_.reset();
}

void SkiaPaint::EnableAntiAlias()
{
    rawPaint_.setAntiAlias(true);
}

void SkiaPaint::SetFilterQuality(FilterQuality quality)
{
#ifdef NG_BUILD
    options_ = SkSamplingOptions(SkFilterMode::kNearest, SkMipmapMode::kNone);
    switch (quality) {
        case FilterQuality::HIGH:
            options_ = SkSamplingOptions(SkCubicResampler { 1 / 3.0f, 1 / 3.0f });
            break;
        case FilterQuality::MEDIUM:
            options_ = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kLinear);
            break;
        case FilterQuality::LOW:
            options_ = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kNone);
            break;
        case FilterQuality::NONE:
            break;
    }
#else
    rawPaint_.setFilterQuality(ToSkFilterQuality(quality));
#endif
}

void SkiaPaint::SetStyle(PaintStyle style)
{
    rawPaint_.setStyle(ToSkStyle(style));
}

void SkiaPaint::SetColor(const Color& color)
{
    rawPaint_.setColor(color.GetValue());
}

void SkiaPaint::SetStrokeWidth(float width)
{
    rawPaint_.setStrokeWidth(width);
}

void SkiaPaint::SetAlphaf(float alpha)
{
    rawPaint_.setAlphaf(alpha);
}

void SkiaPaint::SetBlendMode(BlendMode blendMode)
{
    rawPaint_.setBlendMode(ToSkBlendMode(blendMode));
}

void SkiaPaint::SetStrokeCap(LineCap lineCap)
{
    switch (lineCap) {
        case LineCap::SQUARE:
            rawPaint_.setStrokeCap(SkPaint::Cap::kSquare_Cap);
            break;
        case LineCap::ROUND:
            rawPaint_.setStrokeCap(SkPaint::Cap::kRound_Cap);
            break;
        default:
            LOGI("LineCap is an illegal value");
            break;
    }
}

void SkiaPaint::SetColorFilter(const RefPtr<ColorFilter>& colorFilter)
{
    auto skiaColorFilter = DynamicCast<SkiaColorFilter>(colorFilter);
    CHECK_NULL_VOID(skiaColorFilter);
    rawPaint_.setColorFilter(skiaColorFilter->GetSkColorFilter());
}

} // namespace OHOS::Ace::NG
