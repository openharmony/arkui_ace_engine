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
#ifndef CAPI_STUBS_MOCK_IMAGE_SOURCE_H
#define CAPI_STUBS_MOCK_IMAGE_SOURCE_H

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
class PixelMap {
public:
    static std::unique_ptr<PixelMap> Create(const InitializationOptions& opts)
    {
        return std::make_unique<PixelMap>();
    }

    void WritePixels(const uint8_t* data, uint64_t bufferSize)
    {
        // empty impl for mock
    }
};
} // namespace Media
} // namespace OHOS

#endif // CAPI_STUBS_MOCK_IMAGE_SOURCE_H