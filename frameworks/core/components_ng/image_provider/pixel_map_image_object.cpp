/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/image_provider/pixel_map_image_object.h"

#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

void PixelMapImageObject::MakeCanvasImage(
    const RefPtr<ImageLoadingContext>& ctx, const SizeF& /*resizeTarget*/, bool /*forceResize*/, bool /*syncLoad*/)
{
    if (!pixmap_) {
        ctx->FailCallback("pixmap is null when PixelMapImageObject try MakeCanvasImage");
        return;
    }
    ctx->SuccessCallback(CanvasImage::Create(pixmap_));
}

RefPtr<PixelMapImageObject> PixelMapImageObject::Create(const ImageSourceInfo& src, const RefPtr<ImageData>& data)
{
    auto pixmapData = DynamicCast<PixmapData>(data);
    CHECK_NULL_RETURN(pixmapData, nullptr);
    auto&& pixelMap = pixmapData->GetPixmap();
    if (!pixelMap) {
        LOGW("ImageData has no pixel map data when try CreateImageEncodedInfoForDecodedPixelMap, src: %{public}s",
            src.ToString().c_str());
        return nullptr;
    }
    return AceType::MakeRefPtr<NG::PixelMapImageObject>(
        pixelMap, src, SizeF(pixelMap->GetWidth(), pixelMap->GetHeight()));
}

} // namespace OHOS::Ace::NG
