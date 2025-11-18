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
// Created on 2025/8/18.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CAPIDEMO_PIXEL_MAP_H
#define CAPIDEMO_PIXEL_MAP_H

#include <memory>
#include <multimedia/image_framework/image/pixelmap_native.h>

class PixelMap {
public:
    PixelMap(OH_PixelmapNative* pixelMap)
    {
        pixelMap_ = pixelMap;
    }
    ~PixelMap()
    {
        if (pixelMap_) {
            OH_PixelmapNative_Destroy(&pixelMap_);
        }
    }

    OH_PixelmapNative* GetNativePixelMap()
    {
        return pixelMap_;
    }

private:
    OH_PixelmapNative* pixelMap_;
};

#endif // CAPIDEMO_PIXEL_MAP_H
