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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_CANVAS_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_CANVAS_IMAGE_H

#ifdef NG_BUILD
#include "flutter/flow/skia_gpu_object.h"
#include "third_party/skia/include/core/SkImage.h"
#else
#include "flutter/lib/ui/painting/image.h"
#endif

#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class SkiaCanvasImage : public CanvasImage {
    DECLARE_ACE_TYPE(SkiaCanvasImage, CanvasImage)
public:
#ifndef NG_BUILD
    explicit SkiaCanvasImage(const fml::RefPtr<flutter::CanvasImage>& image) : image_(image) {}
#else
    SkiaCanvasImage() = default;
#endif

    ~SkiaCanvasImage() override = default;

    virtual sk_sp<SkImage> GetCanvasImage() const
    {
#ifndef NG_BUILD
        if (image_) {
            return image_->image();
        }
#endif
        return nullptr;
    }
    void ReplaceSkImage(flutter::SkiaGPUObject<SkImage> newSkGpuObjSkImage);
    int32_t GetWidth() const override;
    int32_t GetHeight() const override;

    void DrawToRSCanvas(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) override;

    static SkImageInfo MakeSkImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap);
    static sk_sp<SkColorSpace> ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap);
    static SkAlphaType AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap);
    static SkColorType PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap);

private:
    // TODO: should not deps on flutter.
#ifndef NG_BUILD
    fml::RefPtr<flutter::CanvasImage> image_;
#endif
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_CANVAS_IMAGE_H
