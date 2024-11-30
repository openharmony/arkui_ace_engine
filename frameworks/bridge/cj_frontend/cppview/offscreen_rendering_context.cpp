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

#include <utility>
#include "ffi_remote_data.h"

#include "base/utils/utils.h"
#include "bridge/cj_frontend/cppview/offscreen_rendering_context.h"
#include "bridge/cj_frontend/cppview/render_image.h"
#include "bridge/declarative_frontend/jsview/models/canvas/offscreen_canvas_rendering_context_2d_model_impl.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.h"

using namespace OHOS;

namespace OHOS::Ace::Framework {
std::mutex CJOffscreenRenderingContext::mutex_;
std::unordered_map<uint32_t, RefPtr<AceType>> CJOffscreenRenderingContext::offscreenPatternMap_;
uint32_t CJOffscreenRenderingContext::offscreenPatternCount_ = 0;

CJOffscreenRenderingContext::CJOffscreenRenderingContext(double width, double height, bool antialias, int32_t unit)
    : NativeCanvasRenderer(antialias), width_(width), height_(height)
{
    if ((static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
        this->SetUnit(CanvasUnit::PX);
    }
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::OffscreenCanvasRenderingContext2DModelNG>();
    this->SetAntiAlias();
}

CJOffscreenRenderingContext::CJOffscreenRenderingContext()
{
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::OffscreenCanvasRenderingContext2DModelNG>();
}

CJOffscreenRenderingContext::~CJOffscreenRenderingContext()
{
    LOGI("Native OffscreeCanvasRenderer Destroyed: %{public}" PRId64, GetID());
}

int64_t CJOffscreenRenderingContext::CJTransferToImageBitmap()
{
    auto offscreenCanvasPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(GetOffscreenPattern(id_));
    auto pixelMap = offscreenCanvasPattern->TransferToImageBitmap();
    auto ret = FFIData::Create<OHOS::Media::PixelMapImpl>(pixelMap->GetPixelMapSharedPtr());
    auto cjImage = FFI::FFIData::Create<CJRenderImage>();
    cjImage->SetUnit(GetUnit());
    cjImage->SetWidth(GetWidth());
    cjImage->SetHeight(GetHeight());
    cjImage->SetPixelMapId(ret->GetID());
#ifndef PIXEL_MAP_SUPPORTED
    auto imageData = offscreenCanvasPattern->GetImageData(0, 0, width_, height_);
    cjImage->SetImageData(std::move(imageData));
#endif
    return cjImage->GetID();
}
} // namespace OHOS::Ace::Framework