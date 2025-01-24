/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_LAYERED_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_LAYERED_DRAWABLE_DESCRIPTOR_H

#include "drawable_descriptor_base.h"

namespace OHOS::Ace::Napi {
using OptionalPixelMap = std::optional<std::shared_ptr<Media::PixelMap>>;
struct LayeredDrawableParams {
    std::unique_ptr<uint8_t[]> jsonBuf;
    size_t len = 0;
    std::shared_ptr<Global::Resource::ResourceManager> resourceMgr;
    std::string path;
    uint32_t iconType = 0;
    uint32_t density = 0;
    std::pair<std::unique_ptr<uint8_t[]>, size_t> foregroundInfo;
    std::pair<std::unique_ptr<uint8_t[]>, size_t> backgroundInfo;
};
class ACE_EXPORT LayeredDrawableDescriptor : public DrawableDescriptor {
public:
    LayeredDrawableDescriptor() = default;

    explicit LayeredDrawableDescriptor(LayeredDrawableParams&& params)
        : jsonBuf_(std::move(params.jsonBuf)), len_(params.len), maskPath_(std::move(params.path)),
          iconType_(params.iconType), density_(params.density)
    {
        if (params.foregroundInfo.first && params.backgroundInfo.first) {
            InitLayeredParam(params.foregroundInfo, params.backgroundInfo);
        }
        InitialResource(params.resourceMgr);
        jsonBuf_.reset();
    };

    ~LayeredDrawableDescriptor() override = default;
    std::unique_ptr<DrawableDescriptor> GetForeground();
    std::unique_ptr<DrawableDescriptor> GetBackground();
    std::unique_ptr<DrawableDescriptor> GetMask();
    std::shared_ptr<Media::PixelMap> GetPixelMap() override;
    DrawableType GetDrawableType() override;
    static std::string GetStaticMaskClipPath();
    void InitLayeredParam(std::pair<std::unique_ptr<uint8_t[]>, size_t> &foregroundInfo,
        std::pair<std::unique_ptr<uint8_t[]>, size_t> &backgroundInfo);
    void SetForeground(std::shared_ptr<Media::PixelMap> foreground)
    {
        foreground_ = foreground;
        customized_ = true;
    }

    void SetBackground(std::shared_ptr<Media::PixelMap> background)
    {
        background_ = background;
        customized_ = true;
    }

    void SetMask(std::shared_ptr<Media::PixelMap> mask)
    {
        mask_ = mask;
        customized_ = true;
    }

    bool Customized()
    {
        return customized_;
    }

    void InitialMask(const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr);
    bool GetDefaultMask();

    bool GetCompositePixelMapWithBadge(
        const std::shared_ptr<Media::PixelMap> layeredPixelMap,
        const std::shared_ptr<Media::PixelMap> badgedPixelMap,
        std::shared_ptr<Media::PixelMap> &compositePixelMap);

private:
    friend class ImageConverter;
    void InitialResource(const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr);
    bool PreGetPixelMapFromJsonBuf(
        const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr, bool isBackground);
    DrawableItem PreGetDrawableItem(
        const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr, const char* item);
    std::unique_ptr<Media::ImageSource> CreateImageSource(DrawableItem& drawableItem, uint32_t& errorCode);
    bool GetPixelMapFromJsonBuf(bool isBackground);
    bool GetMaskByName(std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr, const std::string& name);
    bool CreatePixelMap();
    bool GetMaskByPath();
#ifndef USE_ROSEN_DRAWING
    void DrawOntoCanvas(
        const std::shared_ptr<SkBitmap>& bitMap, float width, float height, SkCanvas& canvas, const SkPaint& paint);
#else
    bool GetLayeredIconParm(std::shared_ptr<Rosen::Drawing::Bitmap>& foreground,
        std::shared_ptr<Rosen::Drawing::Bitmap>& background, std::shared_ptr<Rosen::Drawing::Bitmap>& mask);
    Rosen::Drawing::ImageInfo ImageInfo();
    void CompositeIconNotAdaptive(std::shared_ptr<Rosen::Drawing::Bitmap>& foreground,
        std::shared_ptr<Rosen::Drawing::Bitmap>& background, std::shared_ptr<Rosen::Drawing::Bitmap>& mask);
    bool CompositeIconAdaptive(std::shared_ptr<Rosen::Drawing::Bitmap>& foreground,
        std::shared_ptr<Rosen::Drawing::Bitmap>& background, std::shared_ptr<Rosen::Drawing::Bitmap>& mask);
    Rosen::Drawing::ImageInfo CreateRSImageInfo(OptionalPixelMap pixelmap, int32_t width, int32_t height);
    void TransformToPixelMap(const Rosen::Drawing::Bitmap& bitmap, const Rosen::Drawing::ImageInfo& imageInfo);
    void DrawOntoCanvas(const std::shared_ptr<Rosen::Drawing::Bitmap>& bitMap, float width, float height,
        Rosen::Drawing::Canvas& canvas);
    void BlendForeground(Rosen::Drawing::Canvas& bitmapCanvas, Rosen::Drawing::Brush& brush,
        Rosen::Drawing::Image& image, const std::shared_ptr<Rosen::Drawing::Bitmap>& background,
        const std::shared_ptr<Rosen::Drawing::Bitmap>& foreground);
#endif

    std::unique_ptr<uint8_t[]> defaultMaskData_;
    size_t defaultMaskDataLength_ = 0;
    DrawableItem backgroundItem_;
    DrawableItem foregroundItem_;
    std::unique_ptr<uint8_t[]> jsonBuf_;
    size_t len_ = 0;
    std::string maskPath_;
    uint32_t iconType_ = 0;
    uint32_t density_ = 0;
    OptionalPixelMap foreground_;
    OptionalPixelMap background_;
    OptionalPixelMap mask_;
    OptionalPixelMap layeredPixelMap_;
    bool customized_ = false;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_LAYERED_DRAWABLE_DESCRIPTOR_H