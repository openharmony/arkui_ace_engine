/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//
// Created on 2025/9/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CAPIDEMO_IMAGESOURCE_H
#define CAPIDEMO_IMAGESOURCE_H

#include <log.h>
#include <memory>
#include <multimedia/image_framework/image/image_common.h>
#include <multimedia/image_framework/image/image_source_native.h>
#include <multimedia/image_framework/image/pixelmap_native.h>
#include <string>

#include "pixel_map.h"

enum class PixelMapFormat { RGBA_8888 = PIXEL_FORMAT_BGRA_8888 };

class DecodingOptions {
public:
    DecodingOptions()
    {
        OH_DecodingOptions* options;
        OH_DecodingOptions_Create(&options);
        options_ = options;
    }
    ~DecodingOptions() = default;

    void SetPixelFormat(PixelMapFormat format)
    {
        OH_DecodingOptions_SetPixelFormat(options_, static_cast<int32_t>(PixelMapFormat::RGBA_8888));
    }

    OH_DecodingOptions* GetNativePointer()
    {
        return options_;
    }

private:
    OH_DecodingOptions* options_;
};

struct PixelMaps {
    OH_PixelmapNative** pixelMaps;
    size_t size;
};

class ImageSource {
public:
    ImageSource() = default;
    ~ImageSource()
    {
        if (source_) {
            OH_ImageSourceNative_Release(source_);
        }
    }

    static std::shared_ptr<ImageSource> Create(const std::string& uri)
    {
        auto imageSource = std::make_shared<ImageSource>();
        auto code =
            OH_ImageSourceNative_CreateFromUri(const_cast<char*>(uri.c_str()), uri.size(), &(imageSource->source_));
        if (code != Image_ErrorCode::IMAGE_SUCCESS) {
            OH_LOG_ERROR(LogType::LOG_APP, "Test image source create failed, error code = %{public}d", code);
            return nullptr;
        }
        return imageSource;
    }

    std::shared_ptr<PixelMap> CreatePixelMap(DecodingOptions options)
    {
        if (!source_) {
            return nullptr;
        }
        OH_PixelmapNative* pixel;
        auto code = OH_ImageSourceNative_CreatePixelmap(source_, options.GetNativePointer(), &pixel);
        if (code != Image_ErrorCode::IMAGE_SUCCESS) {
            OH_LOG_ERROR(LogType::LOG_APP, "Test pixel map create failed, error code = %{public}d", code);
            return nullptr;
        }
        auto pixelMap = std::make_shared<PixelMap>(pixel);
        return pixelMap;
    }

    PixelMaps CreatePixelMapList(DecodingOptions options)
    {
        if (!source_) {
            return { nullptr, 0 };
        }
        auto count = GetFrameCount();
        if (count <= 1) {
            return { nullptr, 0 };
        }
        OH_PixelmapNative** recV = new OH_PixelmapNative*[count];
        auto code = OH_ImageSourceNative_CreatePixelmapList(
            source_, options.GetNativePointer(), recV, static_cast<size_t>(count));
        if (code != Image_ErrorCode::IMAGE_SUCCESS) {
            OH_LOG_ERROR(LogType::LOG_APP, "Test pixel map list create failed, error code = %{public}d", code);
            return { nullptr, 0 };
        }
        PixelMaps maps;
        maps.pixelMaps = recV;
        maps.size = count;
        return maps;
    }

    uint32_t GetFrameCount()
    {
        if (!source_) {
            return 0;
        }
        uint32_t frameCount;
        auto code = OH_ImageSourceNative_GetFrameCount(source_, &frameCount);
        return frameCount;
    }

private:
    OH_ImageSourceNative* source_;
};

#endif // CAPIDEMO_IMAGESOURCE_H
