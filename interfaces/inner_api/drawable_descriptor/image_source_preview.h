/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_IMAGE_SOURCE_PREVIEW_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_IMAGE_SOURCE_PREVIEW_H

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace Media {
enum class PixelFormat : int32_t {
    ALPHA_8 = 6,
    RGBA_F16 = 7,
    NV21 = 8,
    NV12 = 9,
    CMYK = 10,
    UNKNOWN = 0,
    ARGB_8888 = 1,
    RGB_565 = 2,
    RGBA_8888 = 3,
    BGRA_8888 = 4,
    RGB_888 = 5,
};

enum class AlphaType : int32_t {
    IMAGE_ALPHA_TYPE_PREMUL = 2,
    IMAGE_ALPHA_TYPE_UNPREMUL = 3,
    IMAGE_ALPHA_TYPE_UNKNOWN = 0,
    IMAGE_ALPHA_TYPE_OPAQUE = 1,
};

struct Size {
    int32_t width = 0;
    int32_t height = 0;
};

enum class ScaleMode : int32_t {
    FIT_TARGET_SIZE = 0,
    CENTER_CROP = 1,
};
struct InitializationOptions {
    AlphaType alphaType = AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
    ScaleMode scaleMode = ScaleMode::FIT_TARGET_SIZE;
    PixelFormat pixelFormat = PixelFormat::UNKNOWN;
    bool useIfMatch = false;
    bool editable = false;
    Size size;
};

struct SourceOptions {};
struct DecodeOptions {
    PixelFormat desiredPixelFormat;
    Size desiredSize;
};
class PixelMap;

class ImageSource {
public:
    static std::unique_ptr<ImageSource> CreateImageSource(
        const uint8_t* data, uint32_t size, const SourceOptions& opts, uint32_t& errorCode)
    {
        return nullptr;
    }

    static std::unique_ptr<ImageSource> CreateImageSource(
        const std::string& path, const SourceOptions& opts, uint32_t& errorCode)
    {
        return nullptr;
    }

    std::unique_ptr<PixelMap> CreatePixelMap(const DecodeOptions& opts, uint32_t& errorCode)
    {
        return nullptr;
    }
};
class PixelMap {
public:
    PixelFormat GetPixelFormat()
    {
        return PixelFormat::ALPHA_8;
    }

    AlphaType GetAlphaType()
    {
        return AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
    }

    const uint8_t* GetPixels()
    {
        return nullptr;
    }

    int32_t GetWidth()
    {
        return 0;
    }

    int32_t GetHeight()
    {
        return 0;
    }

    void* GetWritablePixels()
    {
        return nullptr;
    }

    int32_t GetByteCount()
    {
        return 0;
    }

    static std::unique_ptr<PixelMap> Create(const InitializationOptions& opts)
    {
        return nullptr;
    }

    static std::unique_ptr<PixelMap> Create(
        const uint32_t* colors, uint32_t colorLength, const InitializationOptions& opts)
    {
        return nullptr;
    }
};
class OptionalPixelMap {};

class PixelMapNapi {
public:
    static napi_value CreatePixelMap(napi_env env, std::shared_ptr<PixelMap> pixelmap)
    {
        return nullptr;
    }

    static std::shared_ptr<PixelMap> GetPixelMap(napi_env env, napi_value pixelmap)
    {
        return nullptr;
    }
    static std::shared_ptr<std::vector<std::shared_ptr<PixelMap>>> GetPixelMaps(napi_env env, napi_value pixelmaps)
    {
        return nullptr;
    }
};
} // namespace Media
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_IMAGE_SOURCE_PREVIEW_H
