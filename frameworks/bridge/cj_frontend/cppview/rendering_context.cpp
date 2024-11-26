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

#include "bridge/cj_frontend/cppview/rendering_context.h"

using namespace OHOS;

namespace OHOS::Ace::Framework {

std::string CJRenderingContext::ToDataUrl(const std::string type, const double quality)
{
    std::string result = renderingContext2DModel_->ToDataURL(type, quality);
    return result;
}

double CJRenderingContext::GetWidth()
{
    double width = 0.0;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    canvasRenderingContext2DModel->GetWidth(width);
    double density = !NearZero(GetDensity()) ? GetDensity() : 1.0;
    width /= density;
    return width;
}

double CJRenderingContext::GetHeight()
{
    double height = 0.0;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    canvasRenderingContext2DModel->GetHeight(height);
    double density = !NearZero(GetDensity()) ? GetDensity() : 1.0;
    height /= density;
    return height;
}

void CJRenderingContext::TransferFromImageBitmap(std::unique_ptr<RenderImage> cjImage)
{
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
#ifdef PIXEL_MAP_SUPPORTED
    auto instance = FFIData::GetData<OHOS::Media::PixelMapImpl>(cjImage->pixMapID);
    if (instance == nullptr) {
        LOGE("canvas TransferFromImageBitmap error, Cannot get PixelMapProxy by id: %{public}" PRId64,
            cjImage->pixMapID);
        return;
    }
    auto pixMap = instance->GetRealPixelMap();
    if (pixMap == nullptr) {
        LOGE("canvas TransferFromImageBitmap error, Cannot get pixMap in PixelMapProxy");
        return;
    }
    auto pixMapOhos = PixelMap::CreatePixelMap(&pixMap);
    if (pixMapOhos == nullptr) {
        LOGE("canvas TransferFromImageBitmap error, Cannot create PixelMapOhos by pixMap");
        return;
    }
    canvasRenderingContext2DModel->TransferFromImageBitmap(pixMapOhos);
#else
    auto imageData = cjImage->imageData;
    CHECK_NULL_VOID(imageData);
    canvasRenderingContext2DModel->TransferFromImageBitmap(imageData);
#endif
}
}