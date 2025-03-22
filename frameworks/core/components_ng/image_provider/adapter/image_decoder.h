/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_IMAGE_DECODER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_IMAGE_DECODER_H

#include "ui/base/geometry/ng/size_t.h"
#include "base/image/pixel_map.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/render/adapter/rosen/drawing_image.h"

namespace OHOS::Ace::NG {

struct ImageDecoderConfig {
    SizeF desiredSize_;
    bool forceResize_ = false;
    AIImageQuality imageQuality_ = AIImageQuality::NONE;
    bool isHdrDecoderNeed_ = false;
    PixelFormat photoDecodeFormat_ = PixelFormat::UNKNOWN;
};
class ImageDecoder : public virtual AceType {
public:
    // decode image using Skia, return true if process is successful.
    static RefPtr<CanvasImage> MakeDrawingImage(
        const RefPtr<ImageObject>& obj, const ImageDecoderConfig& imageDecoderConfig);

    // decode image using ImageFramework, return true if process is successful.
    static RefPtr<CanvasImage> MakePixmapImage(
        const RefPtr<ImageObject>& obj, const ImageDecoderConfig& imageDecoderConfig);

    static WeakPtr<PixelMap> GetFromPixelMapCache(const ImageSourceInfo& imageSourceInfo, const SizeF& size);
    static void RemoveFromPixelMapCache(const ImageSourceInfo& imageSourceInfo, const SizeF& size);

private:
    static void AddToPixelMapCache(
        const ImageSourceInfo& imageSourceInfo, const SizeF& size, WeakPtr<PixelMap> weakPixelMap);
    static std::shared_ptr<RSImage> ForceResizeImage(const std::shared_ptr<RSImage>& image, const RSImageInfo& info);
    static std::shared_ptr<RSImage> ResizeDrawingImage(
        const RefPtr<ImageObject>& obj, std::shared_ptr<RSData> data, const ImageDecoderConfig& imageDecoderConfig);
    static void SwapDecodeSize(const RefPtr<ImageObject>& obj, int32_t& width, int32_t& height);

    static RefPtr<CanvasImage> QueryCompressedCache(
        const RefPtr<ImageObject>& obj, std::shared_ptr<RSData> data, const ImageDecoderConfig& imageDecoderConfig);
    static void TryCompress(const RefPtr<ImageObject>& obj, const RefPtr<DrawingImage>& image,
        const ImageDecoderConfig& imageDecoderConfig);

    static std::shared_mutex pixelMapMtx_;
    static std::unordered_map<std::string, WeakPtr<PixelMap>> weakPixelMapCache_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_IMAGE_DECODER_H
