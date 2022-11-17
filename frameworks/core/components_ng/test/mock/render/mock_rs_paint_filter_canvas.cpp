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

#include "pipeline/rs_paint_filter_canvas.h"

namespace OHOS {
namespace Rosen {
RSPaintFilterCanvas::RSPaintFilterCanvas(SkCanvas* canvas, float alpha)
    : SkPaintFilterCanvas(canvas), alphaStack_({ std::clamp(alpha, 0.f, 1.f) })
{}

RSPaintFilterCanvas::RSPaintFilterCanvas(SkSurface* skSurface, float alpha)
    : SkPaintFilterCanvas(nullptr), skSurface_(skSurface), alphaStack_({ std::clamp(alpha, 0.f, 1.f) })
{}

SkSurface* RSPaintFilterCanvas::GetSurface() const
{
    return skSurface_;
}

bool RSPaintFilterCanvas::onFilter(SkPaint& paint) const
{
    return true;
}

void RSPaintFilterCanvas::onDrawPicture(const SkPicture* picture, const SkMatrix* matrix, const SkPaint* paint) {}

void RSPaintFilterCanvas::MultiplyAlpha(float alpha) {}

int RSPaintFilterCanvas::SaveAlpha()
{
    return 0;
}

float RSPaintFilterCanvas::GetAlpha() const
{
    // return top of stack
    return 0.0f;
}

void RSPaintFilterCanvas::RestoreAlpha() {}

void RSPaintFilterCanvas::RestoreAlphaToCount(int count) {}

std::pair<int, int> RSPaintFilterCanvas::SaveCanvasAndAlpha()
{
    return { 0, 0 };
}

void RSPaintFilterCanvas::RestoreCanvasAndAlpha(std::pair<int, int>& count) {}
} // namespace Rosen
} // namespace OHOS
