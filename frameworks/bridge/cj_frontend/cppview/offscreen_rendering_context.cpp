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

#include "bridge/cj_frontend/cppview/offscreen_rendering_context.h"

#include <inttypes.h>
#include <mutex>
#include <utility>

#include "ffi_remote_data.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/cj_frontend/cppview/render_image.h"
#include "core/interfaces/native/implementation/canvas_runtime_bridge.h"

using namespace OHOS;

namespace OHOS::Ace::Framework {
std::mutex CJOffscreenRenderingContext::mutex_;
std::unordered_map<uint32_t, RefPtr<AceType>> CJOffscreenRenderingContext::offscreenPatternMap_;
uint32_t CJOffscreenRenderingContext::offscreenPatternCount_ = 0;

namespace {

RefPtr<RenderingContext2DModel> CreateOffscreenCanvasRenderingContextModel()
{
    auto* bridge = NG::GetCanvasRuntimeBridgeFromModule();
    CHECK_NULL_RETURN(bridge, nullptr);
    CHECK_NULL_RETURN(bridge->createOffscreenCanvasRenderingContext2DModel, nullptr);
    return bridge->createOffscreenCanvasRenderingContext2DModel();
}

RefPtr<PixelMap> TransferToImageBitmap(const RefPtr<AceType>& offscreenPattern)
{
    auto* bridge = NG::GetCanvasRuntimeBridgeFromModule();
    CHECK_NULL_RETURN(bridge, nullptr);
    CHECK_NULL_RETURN(bridge->transferOffscreenToImageBitmap, nullptr);
    return bridge->transferOffscreenToImageBitmap(offscreenPattern);
}

#ifndef PIXEL_MAP_SUPPORTED
std::unique_ptr<ImageData> GetImageData(
    const RefPtr<AceType>& offscreenPattern, double left, double top, double width, double height)
{
    auto* bridge = NG::GetCanvasRuntimeBridgeFromModule();
    CHECK_NULL_RETURN(bridge, nullptr);
    CHECK_NULL_RETURN(bridge->getOffscreenImageData, nullptr);
    return bridge->getOffscreenImageData(offscreenPattern, left, top, width, height);
}
#endif

} // namespace

CJOffscreenRenderingContext::CJOffscreenRenderingContext(double width, double height, bool antialias, int32_t unit)
    : NativeCanvasRenderer(antialias)
{
    renderingContext2DModel_ = CreateOffscreenCanvasRenderingContextModel();
    CHECK_NULL_VOID(renderingContext2DModel_);
    id_ = offscreenPatternCount_;

    double density = this->GetDensity();
    this->SetHeight(height * density);
    this->SetWidth(width * density);
    auto renderingContext =
        AceType::DynamicCast<OffscreenCanvasRenderingContext2DModel>(this->renderingContext2DModel_);
    CHECK_NULL_VOID(renderingContext);
    auto offscreenPattern = renderingContext->CreateOffscreenPattern(round(width * density), round(height * density));
    this->SetOffscreenPattern(offscreenPattern);
    std::lock_guard<std::mutex> lock(mutex_);
    offscreenPatternMap_[offscreenPatternCount_++] = offscreenPattern;

    if ((static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
        this->SetUnit(CanvasUnit::PX);
    }
    this->SetAntiAlias();
    this->SetDensity();
}

CJOffscreenRenderingContext::CJOffscreenRenderingContext()
{
    id_ = offscreenPatternCount_;
    renderingContext2DModel_ = CreateOffscreenCanvasRenderingContextModel();
}

CJOffscreenRenderingContext::~CJOffscreenRenderingContext()
{
    LOGI("Native OffscreeCanvasRenderer Destroyed: %{public}" PRId64, GetID());
}

int64_t CJOffscreenRenderingContext::CJTransferToImageBitmap()
{
    auto offscreenCanvasPattern = GetOffscreenPattern(id_);
    CHECK_NULL_RETURN(offscreenCanvasPattern, 0);
    auto pixelMap = TransferToImageBitmap(offscreenCanvasPattern);
    CHECK_NULL_RETURN(pixelMap, 0);
    auto ret = FFIData::Create<OHOS::Media::PixelMapImpl>(pixelMap->GetPixelMapSharedPtr());
    auto cjImage = FFI::FFIData::Create<CJRenderImage>();
    cjImage->InitCJRenderImage(pixelMap);
    cjImage->SetUnit(GetUnit());
    cjImage->SetWidth(GetWidth());
    cjImage->SetHeight(GetHeight());
    cjImage->SetPixelMapId(ret->GetID());
#ifndef PIXEL_MAP_SUPPORTED
    auto imageData = GetImageData(offscreenCanvasPattern, 0, 0, width_, height_);
    cjImage->SetImageData(std::move(imageData));
#endif
    return cjImage->GetID();
}
} // namespace OHOS::Ace::Framework
