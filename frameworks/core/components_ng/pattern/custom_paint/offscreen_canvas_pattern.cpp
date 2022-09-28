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

#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"

#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"

namespace OHOS::Ace::NG {
OffscreenCanvasPattern::OffscreenCanvasPattern(int32_t width, int32_t height)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    offscreenPaintMethod_ = MakeRefPtr<OffscreenCanvasPaintMethod>(context, width, height);
}

void OffscreenCanvasPattern::FillRect(const Rect& rect)
{
    offscreenPaintMethod_->FillRect(nullptr, rect);
}

void OffscreenCanvasPattern::StrokeRect(const Rect& rect)
{
    offscreenPaintMethod_->StrokeRect(nullptr, rect);
}

std::unique_ptr<Ace::ImageData> OffscreenCanvasPattern::GetImageData(
    double left, double top, double width, double height)
{
    return offscreenPaintMethod_->GetImageData(left, top, width, height);
}

void OffscreenCanvasPattern::UpdateFillColor(const Color& color)
{
    offscreenPaintMethod_->SetFillColor(color);
}

int32_t OffscreenCanvasPattern::GetWidth()
{
    return offscreenPaintMethod_->GetWidth();
}

int32_t OffscreenCanvasPattern::GetHeight()
{
    return offscreenPaintMethod_->GetHeight();
}
} // namespace OHOS::Ace::NG
