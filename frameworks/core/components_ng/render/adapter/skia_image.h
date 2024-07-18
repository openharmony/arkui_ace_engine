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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_IMAGE_H

#include <stdint.h>

#include "include/core/SkImage.h"

#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class SkiaImage : public virtual CanvasImage {
    DECLARE_ACE_TYPE(SkiaImage, CanvasImage)
public:
    explicit SkiaImage(const sk_sp<SkImage>& image) : image_(image) {}
    SkiaImage() = default;
    ~SkiaImage() override = default;

    virtual sk_sp<SkImage> GetImage() const
    {
        return image_;
    }

    virtual sk_sp<SkData> GetCompressData() const
    {
        return compressData_;
    }

    bool HasData() const override
    {
        return GetCompressData() || GetImage();
    }

    void SetCompressData(sk_sp<SkData> data, int32_t w, int32_t h)
    {
        compressData_ = data;
        compressWidth_ = w;
        compressHeight_ = h;
        uniqueId_ = image_->uniqueID();
    }

    void SetRawCompressData(void* dataPtr, int32_t w, int32_t h) override
    {
        auto* skData = reinterpret_cast<sk_sp<SkData>*>(dataPtr);
        SetCompressData(*skData, w, h);
    }

    virtual int32_t GetCompressWidth() const
    {
        return compressWidth_;
    }

    virtual int32_t GetCompressHeight() const
    {
        return compressHeight_;
    }

    virtual uint32_t GetUniqueID() const
    {
        return uniqueId_;
    }

    virtual void SetUniqueID(uint32_t id)
    {
        uniqueId_ = id;
    }

    RefPtr<CanvasImage> Clone() override;

    void Cache(const std::string& key) override;

    RefPtr<PixelMap> GetPixelMap() const override;

    void ReplaceSkImage(sk_sp<SkImage> newImage);
    int32_t GetWidth() const override;
    int32_t GetHeight() const override;

    void DrawToRSCanvas(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) override;

    static RefPtr<CanvasImage> QueryFromCache(const std::string& key);

    static sk_sp<SkImage> MakeSkImageFromPixmap(const RefPtr<PixelMap>& pixmap);
    static sk_sp<SkColorSpace> ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap);
    static SkAlphaType AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap);
    static SkColorType PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap);

private:
    void DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) override {}
    void ClipRRect(RSCanvas& canvas, const RSRect& dstRect, const BorderRadiusArray& radiusXY);
    bool DrawWithRecordingCanvas(RSCanvas& canvas, const BorderRadiusArray& radiusXY);

    uint32_t uniqueId_ = 0;
    sk_sp<SkImage> image_;
    sk_sp<SkData> compressData_;
    int32_t compressWidth_ = 0;
    int32_t compressHeight_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_IMAGE_H
