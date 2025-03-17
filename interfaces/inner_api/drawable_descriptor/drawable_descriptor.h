/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include <cinttypes>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "rstate.h"

#include "base/marcos.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Bitmap;
class Canvas;
class ImageInfo;
class Brush;
class Image;
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS

namespace OHOS {
namespace Media {
class PixelMap;
class ImageSource;
} // namespace Media
} // namespace OHOS

namespace OHOS {
namespace Global {
namespace Resource {
class ResourceManager;
} // namespace Resource
} // namespace Global
} // namespace OHOS

namespace OHOS {
namespace Ace {
namespace Napi {
using UINT8 = std::unique_ptr<uint8_t[]>;
using SharedPixelMap = std::shared_ptr<Media::PixelMap>;
using OptionalPixelMap = std::optional<std::shared_ptr<Media::PixelMap>>;
using OptionalDecodeSize = std::optional<std::pair<int32_t, int32_t>>;
using RSBitmap = Rosen::Drawing::Bitmap;
using SharedResourceManager = std::shared_ptr<Global::Resource::ResourceManager>;
using SharedBitMap = std::shared_ptr<Rosen::Drawing::Bitmap>;
using DataInfo = std::pair<std::unique_ptr<uint8_t[]>, size_t>;
using RSCanvas = Rosen::Drawing::Canvas;
using RSImageInfo = Rosen::Drawing::ImageInfo;
using RSBrush = Rosen::Drawing::Brush;
using RState = Global::Resource::RState;
using RSImage = Rosen::Drawing::Image;
using UniqueImageSource = std::unique_ptr<Media::ImageSource>;

struct DrawableItem {
    UINT8 data_;
    size_t len_ = 0;
    RState state_;
};

class DRAWABLE_FORCE_EXPORT DrawableDescriptor {
public:
    enum class DrawableType {
        BASE,
        LAYERED,
        ANIMATED,
        PIXELMAP,
    };

    DrawableDescriptor() = default;

    explicit DrawableDescriptor(SharedPixelMap pixelMap) : pixelMap_(std::move(pixelMap)) {}

    DrawableDescriptor(UINT8 mediaData, size_t len) : mediaData_(std::move(mediaData)), len_(len) {}

    virtual ~DrawableDescriptor() = default;

    virtual SharedPixelMap GetPixelMap();

    virtual DrawableType GetDrawableType();

    virtual void SetDecodeSize(int32_t width, int32_t height) {}

    void SetPixelMap(SharedPixelMap pixelMap)
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

    UINT8 mediaData_;
    size_t len_ = 0;
    OptionalPixelMap pixelMap_;
};

class DRAWABLE_FORCE_EXPORT LayeredDrawableDescriptor : public DrawableDescriptor {
public:
    LayeredDrawableDescriptor() = default;

    LayeredDrawableDescriptor(UINT8 jsonBuf, size_t len, const SharedResourceManager& resourceMgr)
        : jsonBuf_(std::move(jsonBuf)), len_(len)
    {
        InitialResource(resourceMgr);
        jsonBuf_.reset();
    }

    LayeredDrawableDescriptor(UINT8 jsonBuf, size_t len, const SharedResourceManager& resourceMgr, std::string path,
        uint32_t iconType, uint32_t density)
        : jsonBuf_(std::move(jsonBuf)), len_(len), maskPath_(std::move(path)), iconType_(iconType), density_(density)
    {
        InitialResource(resourceMgr);
        jsonBuf_.reset();
    }

    LayeredDrawableDescriptor(UINT8 jsonBuf, size_t len, const SharedResourceManager& resourceMgr, std::string path,
        uint32_t iconType, DataInfo& foregroundInfo, DataInfo& backgroundInfo)
        : jsonBuf_(std::move(jsonBuf)), len_(len), maskPath_(std::move(path)), iconType_(iconType)
    {
        InitLayeredParam(foregroundInfo, backgroundInfo);
        InitialResource(resourceMgr);
        jsonBuf_.reset();
    }

    ~LayeredDrawableDescriptor() override = default;

    std::unique_ptr<DrawableDescriptor> GetForeground();

    std::unique_ptr<DrawableDescriptor> GetBackground();

    std::unique_ptr<DrawableDescriptor> GetMask();

    SharedPixelMap GetPixelMap() override;

    DrawableType GetDrawableType() override;

    static std::string GetStaticMaskClipPath();

    void InitLayeredParam(DataInfo& foregroundInfo, DataInfo& backgroundInfo);

    void SetForeground(SharedPixelMap foreground);

    void SetBackground(SharedPixelMap background);

    void SetMask(SharedPixelMap mask);

    bool Customized();

    void InitialMask(const SharedResourceManager& resourceMgr);

    void SetDecodeSize(int32_t width, int32_t height) override;

    bool GetDefaultMask();

    bool GetCompositePixelMapWithBadge(
        const SharedPixelMap layeredPixelMap, const SharedPixelMap badgedPixelMap, SharedPixelMap& compositePixelMap);

private:
    DrawableItem PreGetDrawableItem(const SharedResourceManager& resourceMgr, const char* item);

    void InitialResource(const SharedResourceManager& resourceMgr);

    bool PreGetPixelMapFromJsonBuf(const SharedResourceManager& resourceMgr, bool isBackground);

    bool GetPixelMapFromJsonBuf(bool isBackground);

    bool GetMaskByName(SharedResourceManager& resourceMgr, const std::string& name);

    bool CreatePixelMap();

    bool GetMaskByPath();

    bool GetLayeredIconParm(SharedBitMap& foreground, SharedBitMap& background, SharedBitMap& mask);

    void CompositeIconNotAdaptive(SharedBitMap& foreground, SharedBitMap& background, SharedBitMap& mask);

    bool CompositeIconAdaptive(SharedBitMap& foreground, SharedBitMap& background, SharedBitMap& mask);

    void TransformToPixelMap(const RSBitmap& bitmap, const RSImageInfo& imageInfo);

    UINT8 defaultMaskData_;
    size_t defaultMaskDataLength_ = 0;
    DrawableItem backgroundItem_;
    DrawableItem foregroundItem_;
    UINT8 jsonBuf_;
    size_t len_ = 0;
    std::string maskPath_;
    uint32_t iconType_ = 0;
    uint32_t density_ = 0;
    OptionalPixelMap foreground_;
    OptionalPixelMap background_;
    OptionalPixelMap mask_;
    OptionalPixelMap layeredPixelMap_;
    bool customized_ = false;
    OptionalDecodeSize decodeSize_ = std::nullopt;
};

class DRAWABLE_FORCE_EXPORT AnimatedDrawableDescriptor : public DrawableDescriptor {
public:
    AnimatedDrawableDescriptor(std::vector<SharedPixelMap> pixelMaps, int32_t duration, int32_t iterations)
        : pixelMapList_(std::move(pixelMaps)), duration_(duration), iterations_(iterations) {};

    ~AnimatedDrawableDescriptor() override = default;

    SharedPixelMap GetPixelMap() override;

    DrawableType GetDrawableType() override;

    std::vector<SharedPixelMap> GetPixelMapList();

    int32_t GetDuration();

    int32_t GetIterations();

    void SetDuration(int32_t duration);

    void SetIterations(int32_t iterations);

private:
    std::vector<SharedPixelMap> pixelMapList_;
    int32_t duration_ = -1;
    int32_t iterations_ = 1;
};

class DRAWABLE_FORCE_EXPORT DrawableDescriptorFactory {
public:
    using DrawableType = DrawableDescriptor::DrawableType;

    static std::unique_ptr<DrawableDescriptor> Create(int32_t id, const SharedResourceManager& resourceMgr,
        RState& state, DrawableType& drawableType, uint32_t density);

    static std::unique_ptr<DrawableDescriptor> Create(const char* name, const SharedResourceManager& resourceMgr,
        RState& state, DrawableType& drawableType, uint32_t density);

    static std::unique_ptr<DrawableDescriptor> Create(std::tuple<int32_t, uint32_t, uint32_t>& drawableInfo,
        const SharedResourceManager& resourceMgr, RState& state, DrawableType& drawableType);

    static std::unique_ptr<DrawableDescriptor> Create(std::tuple<const char*, uint32_t, uint32_t>& drawableInfo,
        const SharedResourceManager& resourceMgr, RState& state, DrawableType& drawableType);

    static std::unique_ptr<DrawableDescriptor> Create(DataInfo& foregroundInfo, DataInfo& backgroundInfo,
        std::string& path, DrawableType& drawableType, const SharedResourceManager& resourceMgr);
};
} // namespace Napi
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_DRAWABLE_DESCRIPTOR_H
