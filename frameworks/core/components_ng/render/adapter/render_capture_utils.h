/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_CAPTURE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_CAPTURE_UTILS_H

#ifdef RENDER_EXTRACT_SUPPORTED

#include <cstdint>
#include <memory>

#include "pixel_map.h"

namespace OHOS::Ace::NG {

inline std::shared_ptr<Media::PixelMap> CreateCapturePixelMap(int32_t width, int32_t height)
{
    Media::InitializationOptions opts;
    opts.size.width = width;
    opts.size.height = height;
    opts.pixelFormat = Media::PixelFormat::RGBA_8888;
    opts.editable = true;
    return Media::PixelMap::Create(opts);
}

template<typename CaptureFunc>
inline std::shared_ptr<Media::PixelMap> CapturePixelMap(
    int32_t width, int32_t height, const char* captureName, CaptureFunc&& captureFunc)
{
    if (width <= 0 || height <= 0) {
        LOGE("%{public}s invalid surface size", captureName);
        return nullptr;
    }
    auto pixelMap = CreateCapturePixelMap(width, height);
    CHECK_NULL_RETURN(pixelMap, nullptr);
    auto* rawBuffer = const_cast<uint8_t*>(pixelMap->GetPixels());
    CHECK_NULL_RETURN(rawBuffer, nullptr);
    return captureFunc(reinterpret_cast<uintptr_t>(rawBuffer), width, height) ? pixelMap : nullptr;
}

} // namespace OHOS::Ace::NG

#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_CAPTURE_UTILS_H