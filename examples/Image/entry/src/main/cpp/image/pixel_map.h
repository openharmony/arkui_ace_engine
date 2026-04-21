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

#ifndef CAPI_PIXEL_MAP_H
#define CAPI_PIXEL_MAP_H

#include <cassert>
#include <atomic>

#include "utils/log.h"
#include <cstdint>
#include <multimedia/image_framework/image/pixelmap_native.h>

namespace Self::UI {
class PixelMap {
public:
    PixelMap(OH_PixelmapNative *pixelMap) : pixelMap_(pixelMap) {}
    ~PixelMap()
    {
        if (pixelMap_) {
        OH_PixelmapNative_Release(pixelMap_);
        }
        if (info_) {
            OH_PixelmapImageInfo_Release(info_);
        }
    }

    const int32_t GetWidth() 
    {
        if (!GetOrCreateImageInfo()) {
            return -1;
        }
        auto code = OH_PixelmapNative_GetImageInfo(pixelMap_, info_);
        if (code != Image_ErrorCode::IMAGE_SUCCESS) {
            OH_LOG_ERROR(LogType::LOG_APP, "get image info failed");
            return -1;
        }
        uint32_t width;
        code = OH_PixelmapImageInfo_GetWidth(info_, &width);
        if (code != Image_ErrorCode::IMAGE_SUCCESS) {
            OH_LOG_ERROR(LogType::LOG_APP, "get width from image info failed");
            return -1;
        }
        return static_cast<int32_t>(width);
    }

    const int32_t GetHeight() 
    {
        if (!GetOrCreateImageInfo()) {
            return -1;
        }
        auto code = OH_PixelmapNative_GetImageInfo(pixelMap_, info_);
        if (code != Image_ErrorCode::IMAGE_SUCCESS) {
            OH_LOG_ERROR(LogType::LOG_APP, "get image info failed");
            return -1;
        }
        uint32_t height;
        code = OH_PixelmapImageInfo_GetHeight(info_, &height);
        if (code != Image_ErrorCode::IMAGE_SUCCESS) {
            OH_LOG_ERROR(LogType::LOG_APP, "get height from image info failed");
            return -1;
        }
        return static_cast<int32_t>(height);
    }

    OH_PixelmapNative *GetNativePointer() { return pixelMap_; }

private:
    bool GetOrCreateImageInfo() 
    {
        if (!isCreate_) {
            auto code = OH_PixelmapImageInfo_Create(&info_);
            if (code != Image_ErrorCode::IMAGE_SUCCESS) {
                OH_LOG_ERROR(LogType::LOG_APP, "create image info failed");
                return false;
            }
            isCreate_ = false;
        }
        return true;
    }

    std::atomic<bool> isCreate_ = false;
    OH_Pixelmap_ImageInfo *info_;
    OH_PixelmapNative *pixelMap_;
};
} // namespace Self::UI


#endif // CAPI_PIXEL_MAP_H
