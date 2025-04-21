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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_DRAWING_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_DRAWING_IMAGE_H

#include <stdint.h>

#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace::NG {
class DrawingImage : public virtual CanvasImage {
    DECLARE_ACE_TYPE(DrawingImage, CanvasImage)
public:
    explicit DrawingImage(const std::shared_ptr<RSImage>& image) : image_(image) {}
    DrawingImage() = default;
    ~DrawingImage() override = default;

    virtual std::shared_ptr<RSImage> GetImage() const
    {
        return image_;
    }

    virtual std::shared_ptr<RSData> GetCompressData() const
    {
        return compressData_;
    }

    bool HasData() const override
    {
        return GetCompressData() || GetImage();
    }

    void SetCompressData(std::shared_ptr<RSData> data, int32_t w, int32_t h)
    {
        compressData_ = data;
        compressWidth_ = w;
        compressHeight_ = h;
        uniqueId_ = image_->GetUniqueID();
    }

    void SetRawCompressData(void* dataPtr, int32_t w, int32_t h) override
    {
        auto* rsData = reinterpret_cast<std::shared_ptr<RSData>*>(dataPtr);
        SetCompressData(*rsData, w, h);
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

    void ReplaceRSImage(std::shared_ptr<RSImage> image);
    int32_t GetWidth() const override;
    int32_t GetHeight() const override;

    void DrawToRSCanvas(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) override;
    bool DrawImageNine(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY);
    bool DrawImageLattice(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY);
    void DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) override;
    static RefPtr<CanvasImage> QueryFromCache(const std::string& key);

    static std::shared_ptr<RSImage> MakeRSImageFromPixmap(const RefPtr<PixelMap>& pixmap);
    static std::shared_ptr<RSColorSpace> ColorSpaceToRSColorSpace(const RefPtr<PixelMap>& pixmap);
    static RSAlphaType AlphaTypeToRSAlphaType(const RefPtr<PixelMap>& pixmap);
    static RSColorType PixelFormatToRSColorType(const RefPtr<PixelMap>& pixmap);

private:
    void ClipRRect(RSCanvas& canvas, const RSRect& dstRect, const BorderRadiusArray& radiusXY);
    bool DrawWithRecordingCanvas(RSCanvas& canvas, const BorderRadiusArray& radiusXY);

    uint32_t uniqueId_ = 0;
    std::shared_ptr<RSImage> image_;
    std::shared_ptr<RSData> compressData_;
    int32_t compressWidth_ = 0;
    int32_t compressHeight_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_DRAWING_IMAGE_H
