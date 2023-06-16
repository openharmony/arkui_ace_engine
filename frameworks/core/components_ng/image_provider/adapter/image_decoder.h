/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "include/core/SkImage.h"

#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/render/adapter/skia_image.h"

namespace OHOS::Ace::NG {
class ImageDecoder : public virtual AceType {
public:
    ImageDecoder(const RefPtr<ImageObject>& obj, const SizeF& size, bool forceResize);
    // decode image using Skia, return true if process is successful.
    RefPtr<CanvasImage> MakeSkiaImage();

    // decode image using ImageFramework, return true if process is successful.
    RefPtr<CanvasImage> MakePixmapImage();

private:
    static sk_sp<SkImage> ForceResizeImage(const sk_sp<SkImage>& image, const SkImageInfo& info);
    sk_sp<SkImage> ResizeSkImage();

    RefPtr<CanvasImage> QueryCompressedCache();
    void TryCompress(const RefPtr<SkiaImage>& image);

    const RefPtr<ImageObject> obj_;
    sk_sp<SkData> data_;
    const SizeF desiredSize_;
    const bool forceResize_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_ADAPTER_IMAGE_DECODER_H
