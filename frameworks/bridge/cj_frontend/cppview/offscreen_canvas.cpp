/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/cppview/offscreen_canvas.h"

#include "bridge/cj_frontend/cppview/offscreen_rendering_context.h"
#include "core/components/common/properties/paint_state.h"

namespace OHOS::Ace::Framework {
NativeOffscreenCanvas::NativeOffscreenCanvas(double height, double width, int32_t unit) : FFIData()
{
    SetUnit(static_cast<CanvasUnit>(unit));
    double density = GetDensity();
    SetHeight(height * density);
    SetWidth(width * density);
    offscreenCanvasPattern_ = AceType::MakeRefPtr<NG::OffscreenCanvasPattern>(
        static_cast<int32_t>(this->width_), static_cast<int32_t>(this->height_));
}

NativeOffscreenCanvas::~NativeOffscreenCanvas()
{
    LOGI("Native Offscreen Canvas Destroyed: %{public}" PRId64, GetID());
}

void NativeOffscreenCanvas::NativeSetHeihgt(double height)
{
    double density = GetDensity();
    height *= density;
    if (height_ != height) {
        height_ = height;
        offscreenCanvasPattern_->UpdateSize(width_, height_);
        if (offscreenCanvasContext_ != nullptr) {
            offscreenCanvasContext_->SetHeight(height_);
        }
    }
}

void NativeOffscreenCanvas::NativeSetWidth(double width)
{
    double density = GetDensity();
    width *= density;
    if (width_ != width) {
        width_ = width;
        offscreenCanvasPattern_->UpdateSize(width_, width_);
        if (offscreenCanvasContext_ != nullptr) {
            offscreenCanvasContext_->SetWidth(width_);
        }
    }
}

double NativeOffscreenCanvas::NativeGetHeihgt()
{
    double fHeight = GetHeight();
    double density = Positive(GetDensity()) ? GetDensity() : 1;
    fHeight /= density;
    return fHeight;
}

double NativeOffscreenCanvas::NativeGetWidth()
{
    double fWidth = GetWidth();
    double density = Positive(GetDensity()) ? GetDensity() : 1;
    fWidth /= density;
    return fWidth;
}

int64_t NativeOffscreenCanvas::GetContext(int32_t contextType, bool option, double width, double height)
{
    double density = GetDensity();
    isGetContext_ = true;
    width_ = width * density;
    height_ = height * density;
    if (!Container::IsCurrentUseNewPipeline()) {
        return 0;
    }
    contextType_ = static_cast<ContextType>(contextType);
    if (contextType_ == ContextType::CONTEXT_2D) {
        offscreenCanvasContext_ = FFIData::Create<CJOffscreenRenderingContext>();
        offscreenCanvasContext_->SetInstanceId(Container::CurrentId());
        offscreenCanvasContext_->SetOffscreenPattern(offscreenCanvasPattern_);
        offscreenCanvasContext_->AddOffscreenCanvasPattern(offscreenCanvasPattern_);
        offscreenCanvasContext_->SetWidth(width_);
        offscreenCanvasContext_->SetHeight(height_);
        offscreenCanvasContext_->SetUnit(GetUnit());
    }
    offscreenCanvasContext_->SetDensity();
    return offscreenCanvasContext_->GetID();
}

int64_t NativeOffscreenCanvas::TransferToImageBitmap()
{
    if (offscreenCanvasPattern_ == nullptr || offscreenCanvasContext_ == nullptr) {
        return 0;
    }
    auto pixelMap = offscreenCanvasPattern_->TransferToImageBitmap();
    auto renderImage = FFIData::Create<CJRenderImage>();
    renderImage->InitCJRenderImage(pixelMap);

#ifndef PIXEL_MAP_SUPPORTED
    auto imageData = offscreenCanvasPattern_->GetImageData(0, 0, width_, height_);
    if (imageData == nullptr) {
        return nullptr;
    }
    renderImage->SetImageData(std::make_shared<Ace::ImageData>(*imageData));
#endif
    renderImage->SetUnit(GetUnit());
    renderImage->SetWidth(GetWidth());
    renderImage->SetHeight(GetHeight());
    return renderImage->GetID();
}

} // namespace OHOS::Ace::Framework