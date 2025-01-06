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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_BASE_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_BASE_DRAWABLE_DESCRIPTOR_H
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
#include "drawable_descriptor_utils.h"
#include "image_loader/image_define.h"

namespace OHOS::Ace::Napi {
using OptionalPixelMap = std::optional<std::shared_ptr<Media::PixelMap>>;
struct DrawableItem {
    using RState = Global::Resource::RState;
    std::unique_ptr<uint8_t[]> data_;
    size_t len_ = 0;
    RState state_ = Global::Resource::ERROR;
};

struct DrawableInfo {
    size_t originalWidth = -1;
    size_t originalHeight = -1;
};

constexpr int32_t ERROR_CODE_NO_ERROR = 0;
// data loading failed when fetching
constexpr int32_t ERROR_CODE_FETCH_LOADING_ERROR = 100001;
// data decoding failed when fetching
constexpr int32_t ERROR_CODE_FETCH_DECODE_ERROR = 100002;
// data is not ready when starting/stoping animation
constexpr int32_t ERROR_CODE_ANIMATED_DATA_NOT_READY_ERROR = 100001;

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
    // add
    virtual void DecodeImage() {}
    virtual int32_t FetchSync(DrawableInfo& info)
    {
        return ERROR_CODE_NO_ERROR;
    }

protected:
    bool GetPixelMapFromBuffer();
    std::unique_ptr<uint8_t[]> mediaData_;
    size_t len_ = 0;
    OptionalPixelMap pixelMap_;
};

} // namespace OHOS::Ace::Napi
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_BASE_DRAWABLE_DESCRIPTOR_H