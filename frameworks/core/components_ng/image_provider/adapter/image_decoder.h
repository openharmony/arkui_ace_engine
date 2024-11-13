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

#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/render/adapter/rosen/drawing_image.h"

namespace OHOS::Ace::NG {
class ImageDecoder : public virtual AceType {
public:
    ImageDecoder(const RefPtr<ImageObject>& obj, const SizeF& size, bool forceResize);
    // decode image using Skia, return true if process is successful.
    RefPtr<CanvasImage> MakeDrawingImage();

    // decode image using ImageFramework, return true if process is successful.
    RefPtr<CanvasImage> MakePixmapImage(
        AIImageQuality imageQuality = AIImageQuality::NONE, bool isHdrDecoderNeed = false);

private:
    static std::shared_ptr<RSImage> ForceResizeImage(const std::shared_ptr<RSImage>& image, const RSImageInfo& info);
    static std::string GetResolutionQuality(AIImageQuality imageQuality);
    std::shared_ptr<RSImage> ResizeDrawingImage();
    void SwapDecodeSize(int32_t &width, int32_t &height);

    RefPtr<CanvasImage> QueryCompressedCache();
    void TryCompress(const RefPtr<DrawingImage>& image);

    const RefPtr<ImageObject> obj_;
    std::shared_ptr<RSData> data_;
    const SizeF desiredSize_;
    const bool forceResize_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_IMAGE_DECODER_H
