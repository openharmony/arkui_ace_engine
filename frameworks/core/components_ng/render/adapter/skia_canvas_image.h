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

    virtual sk_sp<SkData> GetCompressData() const
    {
#ifndef NG_BUILD
        if (image_) {
            return image_->compressData();
        }
#endif
        return nullptr;
    }

    void SetCompressData(sk_sp<SkData> data, int32_t w, int32_t h)
    {
#ifndef NG_BUILD
        if (image_) {
            image_->setCompress(data, w, h);
            auto skimage = image_->image();
            uniqueId_ = skimage ? skimage->uniqueID() : 0;
        }
#endif
    }

    virtual int32_t GetCompressWidth() const
    {
#ifndef NG_BUILD
        if (image_) {
            return image_->compressWidth();
        }
#endif
        return 0;
    }

    virtual int32_t GetCompressHeight() const
    {
#ifndef NG_BUILD
        if (image_) {
            return image_->compressHeight();
        }
#endif
        return 0;
    }

    virtual uint32_t GetUniqueID() const
    {
#ifndef NG_BUILD
        if (image_ && image_->image()) {
            return image_->image()->uniqueID();
        }
        return uniqueId_;
#endif
        return 0;
    }

    virtual void SetUniqueID(uint32_t id)
    {
#ifndef NG_BUILD
        uniqueId_ = id;
#endif
    }

#ifndef NG_BUILD
    virtual fml::RefPtr<flutter::CanvasImage> GetFlutterCanvasImage() const
    {
        if (image_) {
            return image_;
        }
        return nullptr;
    }
#endif

    RefPtr<CanvasImage> Clone() override;

    RefPtr<PixelMap> GetPixelMap() override;

    void ReplaceSkImage(flutter::SkiaGPUObject<SkImage> newSkGpuObjSkImage);
    int32_t GetWidth() const override;
    int32_t GetHeight() const override;

    void AddFilter(SkPaint& paint);
    void DrawToRSCanvas(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) override;

    static SkImageInfo MakeSkImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap);
    static sk_sp<SkColorSpace> ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap);
    static SkAlphaType AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap);
    static SkColorType PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap);

private:
    void ClipRRect(RSCanvas& canvas, const RSRect& dstRect, const BorderRadiusArray& radiusXY);
    bool DrawWithRecordingCanvas(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY);
    // TODO: should not deps on flutter.
#ifndef NG_BUILD
    uint32_t uniqueId_;
    fml::RefPtr<flutter::CanvasImage> image_;
#endif
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_CANVAS_IMAGE_H
