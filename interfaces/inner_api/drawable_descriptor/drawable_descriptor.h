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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_DESCRIPTOR_H

#define ACE_FORCE_EXPORT __attribute__((visibility("default")))

#ifndef ACE_EXPORT
#ifndef HIDDEN_SYMBOL
#define ACE_EXPORT ACE_FORCE_EXPORT
#else
#define ACE_EXPORT
#endif
#endif

#include <optional>
#include <string>
#include <tuple>
#include <utility>

#include "image_converter.h"
#ifndef USE_ROSEN_DRAWING
#include "include/core/SkBlendMode.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#else
#include "draw/canvas.h"
#include "image/bitmap.h"
#include "image/image_info.h"
#endif
#include "resource_manager.h"

#include "drawable_descriptor_log.h"

namespace OHOS::Ace::Napi {
using OptionalPixelMap = std::optional<std::shared_ptr<Media::PixelMap>>;
struct DrawableItem {
    using RState = Global::Resource::RState;
    std::unique_ptr<uint8_t[]> data_;
    size_t len_ = 0;
    RState state_ = Global::Resource::ERROR;
};

class ACE_EXPORT DrawableDescriptor {
public:
    enum class DrawableType {
        BASE,
        LAYERED,
        ANIMATED,
        PIXELMAP,
    };
    DrawableDescriptor() = default;
    explicit DrawableDescriptor(std::shared_ptr<Media::PixelMap> pixelMap) : pixelMap_(std::move(pixelMap)) {};
    DrawableDescriptor(std::unique_ptr<uint8_t[]> mediaData, size_t len)
        : mediaData_(std::move(mediaData)), len_(len) {};
    virtual ~DrawableDescriptor() = default;
    virtual std::shared_ptr<Media::PixelMap> GetPixelMap();
    virtual DrawableType GetDrawableType();
    void SetPixelMap(std::shared_ptr<Media::PixelMap> pixelMap)
    {
        pixelMap_ = pixelMap;
    }
    bool HasPixelMap()
    {
        return pixelMap_.has_value();
    }
    void ResetPixelMap()
    {
        pixelMap_.reset();
    }

private:
    bool GetPixelMapFromBuffer();

    std::unique_ptr<uint8_t[]> mediaData_;
    size_t len_ = 0;
    OptionalPixelMap pixelMap_;
};

class ACE_EXPORT LayeredDrawableDescriptor : public DrawableDescriptor {
public:
    LayeredDrawableDescriptor() = default;
    LayeredDrawableDescriptor(std::unique_ptr<uint8_t[]> jsonBuf, size_t len,
        const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr)
        : jsonBuf_(std::move(jsonBuf)), len_(len)
    {
        InitialResource(resourceMgr);
        jsonBuf_.reset();
    };
    LayeredDrawableDescriptor(std::unique_ptr<uint8_t[]> jsonBuf, size_t len,
        const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr, std::string path, uint32_t iconType,
        uint32_t density)
        : jsonBuf_(std::move(jsonBuf)), len_(len), maskPath_(std::move(path)), iconType_(iconType), density_(density)
    {
        InitialResource(resourceMgr);
        jsonBuf_.reset();
    };
    LayeredDrawableDescriptor(std::unique_ptr<uint8_t[]> jsonBuf, size_t len,
        const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr, std::string path, uint32_t iconType,
        std::pair<std::unique_ptr<uint8_t[]>, size_t>& foregroundInfo,
        std::pair<std::unique_ptr<uint8_t[]>, size_t>& backgroundInfo)
        : jsonBuf_(std::move(jsonBuf)), len_(len), maskPath_(std::move(path)), iconType_(iconType)
    {
        InitLayeredParam(foregroundInfo, backgroundInfo);
        InitialResource(resourceMgr);
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

class ACE_EXPORT AnimatedDrawableDescriptor : public DrawableDescriptor {
public:
    AnimatedDrawableDescriptor(std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps, int32_t duration,
        int32_t iterations): pixelMapList_(std::move(pixelMaps)), duration_(duration), iterations_(iterations) {};
    ~AnimatedDrawableDescriptor() override = default;
    std::shared_ptr<Media::PixelMap> GetPixelMap() override;
    DrawableType GetDrawableType() override;
    std::vector<std::shared_ptr<Media::PixelMap>> GetPixelMapList();
    int32_t GetDuration();
    int32_t GetIterations();
    void SetDuration(int32_t duration);
    void SetIterations(int32_t iterations);
private:
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList_;
    int32_t duration_ = -1;
    int32_t iterations_ = 1;
};

class DrawableDescriptorFactory {
public:
    using DrawableType = DrawableDescriptor::DrawableType;
    using ResourceManager = Global::Resource::ResourceManager;
    using RState = Global::Resource::RState;
    static std::unique_ptr<DrawableDescriptor> Create(int32_t id, const std::shared_ptr<ResourceManager>& resourceMgr,
        RState& state, DrawableType& drawableType, uint32_t density)
    {
        std::string type;
        size_t len;
        std::unique_ptr<uint8_t[]> jsonBuf;
        state = resourceMgr->GetDrawableInfoById(id, type, len, jsonBuf, density);
        if (state != Global::Resource::SUCCESS) {
            HILOGE("Failed to get drawable info from resmgr");
            return nullptr;
        }
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "json") {
            HILOGD("Create LayeredDrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::LAYERED;
            state = Global::Resource::SUCCESS;
            return std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr);
        }
        if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
            type == "astc" || type == "sut") {
            HILOGD("Create DrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::BASE;
            state = Global::Resource::SUCCESS;
            return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
        }
        HILOGE("unknow resource type: %{public}s", type.c_str());
        state = Global::Resource::INVALID_FORMAT;
        return nullptr;
    }

    static std::unique_ptr<DrawableDescriptor> Create(const char* name,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType,
        uint32_t density)
    {
        std::string type;
        size_t len;
        std::unique_ptr<uint8_t[]> jsonBuf;
        state = resourceMgr->GetDrawableInfoByName(name, type, len, jsonBuf, density);
        if (state != Global::Resource::SUCCESS) {
            HILOGE("Failed to get drawable info from resmgr");
            return nullptr;
        }
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "json") {
            HILOGD("Create LayeredDrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::LAYERED;
            state = Global::Resource::SUCCESS;
            return std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr);
        }
        if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
            type == "astc" || type == "sut") {
            HILOGD("Create DrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::BASE;
            state = Global::Resource::SUCCESS;
            return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
        }
        HILOGE("unknow resource type: %{public}s", type.c_str());
        state = Global::Resource::INVALID_FORMAT;
        return nullptr;
    }

    static std::unique_ptr<DrawableDescriptor> Create(std::tuple<int32_t, uint32_t, uint32_t>& drawableInfo,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType)
    {
        int32_t resId = std::get<0>(drawableInfo);
        uint32_t iconType = std::get<1>(drawableInfo);
        uint32_t density = std::get<2>(drawableInfo);
        std::unique_ptr<uint8_t[]> jsonBuf;
        std::tuple<std::string, size_t, std::string> info;
        state = resourceMgr->GetDrawableInfoById(resId, info, jsonBuf, iconType, density);
        if (state != Global::Resource::SUCCESS) {
            HILOGW("Failed to get drawable info from resmgr");
            return nullptr;
        }
        std::string type = std::get<0>(info);
        size_t len = std::get<1>(info);
        std::string path = std::get<2>(info);
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "json") {
            HILOGD("Create LayeredDrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::LAYERED;
            auto layeredDrawableDescriptor =
                std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr,
                    path, iconType, density);
            return layeredDrawableDescriptor;
        }
        if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
            type == "astc" || type == "sut") {
            HILOGD("Create DrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::BASE;
            return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
        }
        HILOGE("unknow resource type: %{public}s", type.c_str());
        state = Global::Resource::INVALID_FORMAT;
        return nullptr;
    }

    static std::unique_ptr<DrawableDescriptor> Create(std::tuple<const char*, uint32_t, uint32_t>& drawableInfo,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType)
    {
        const char* name = std::get<0>(drawableInfo);
        uint32_t iconType = std::get<1>(drawableInfo);
        uint32_t density = std::get<2>(drawableInfo);
        std::unique_ptr<uint8_t[]> jsonBuf;
        std::tuple<std::string, size_t, std::string> info;
        state = resourceMgr->GetDrawableInfoByName(name, info, jsonBuf, iconType, density);
        if (state != Global::Resource::SUCCESS) {
            HILOGW("Failed to get drawable info from resmgr");
            return nullptr;
        }
        std::string type = std::get<0>(info);
        size_t len = std::get<1>(info);
        std::string path = std::get<2>(info);
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (type == "json") {
            HILOGD("Create LayeredDrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::LAYERED;
            auto layeredDrawableDescriptor = std::make_unique<LayeredDrawableDescriptor>(
                std::move(jsonBuf), len, resourceMgr, path, iconType, density);
            return layeredDrawableDescriptor;
        }
        if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
            type == "astc" || type == "sut") {
            HILOGD("Create DrawableDescriptor object");
            drawableType = DrawableDescriptor::DrawableType::BASE;
            return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
        }
        HILOGE("unknow resource type: %{public}s", type.c_str());
        state = Global::Resource::INVALID_FORMAT;
        return nullptr;
    }

    static std::unique_ptr<DrawableDescriptor> Create(std::pair<std::unique_ptr<uint8_t[]>, size_t> &foregroundInfo,
        std::pair<std::unique_ptr<uint8_t[]>, size_t> &backgroundInfo, std::string &path, DrawableType& drawableType,
        const std::shared_ptr<ResourceManager>& resourceMgr)
    {
        std::unique_ptr<uint8_t[]> jsonBuf;
        drawableType = DrawableDescriptor::DrawableType::LAYERED;
        auto layeredDrawableDescriptor = std::make_unique<LayeredDrawableDescriptor>(
            std::move(jsonBuf), 0, resourceMgr, path, 1, foregroundInfo, backgroundInfo);
        return layeredDrawableDescriptor;
    }
};
} // namespace OHOS::Ace::Napi
#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_DESCRIPTOR_H
