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

#if defined(IOS_PLATFORM)
#include "application_context.h"
#endif
#include <cstdlib>
#include <cerrno>
#include <limits>

#include "drawable_descriptor.h"
#include "cJSON.h"
#ifndef PREVIEW
#include "image_source.h"
#endif
#include "include/core/SkImage.h"
#include "include/core/SkRect.h"
#ifdef PREVIEW
#ifdef WINDOWS_PLATFORM
#include <direct.h>
#include <windows.h>
#elif defined(MAC_PLATFORM)
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#endif
#endif

namespace OHOS::Ace::Napi {

bool DrawableDescriptor::GetPixelMapFromBuffer()
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(mediaData_.get(), len_, opts, errorCode);
    if (errorCode != 0) {
        HILOGE("CreateImageSource from buffer failed");
        return false;
    }
    mediaData_.reset();
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        pixelMap_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    }
    if (errorCode != 0 || !pixelMap_) {
        HILOGE("Get PixelMap from buffer failed");
        return false;
    }
    return true;
}

std::shared_ptr<Media::PixelMap> DrawableDescriptor::GetPixelMap()
{
    if (pixelMap_.has_value()) {
        return pixelMap_.value();
    }
    if (GetPixelMapFromBuffer()) {
        return pixelMap_.value();
    }
    HILOGE("Failed to GetPixelMap!");
    return nullptr;
}

DrawableDescriptor::DrawableType DrawableDescriptor::GetDrawableType()
{
    return DrawableType::BASE;
}

} // namespace OHOS::Ace::Napi