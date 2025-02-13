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

#include "pixel_map_preview.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
std::shared_ptr<PixelMap> Create(std::shared_ptr<Media::PixelMap>&& pixmap)
{
    return nullptr;
}

int32_t PixelMapPreview::GetWidth() const
{
    return 0;
}

int32_t PixelMapPreview::GetHeight() const
{
    return 0;
}

const uint8_t* PixelMapPreview::GetPixels() const
{
    return nullptr;
}

PixelFormat PixelMapPreview::GetPixelFormat() const
{
    return PixelFormat::UNKNOWN;
}

AlphaType PixelMapPreview::GetAlphaType() const
{
    return AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
}

int32_t PixelMapPreview::GetRowStride() const
{
    return 0;
}

int32_t PixelMapPreview::GetRowBytes() const
{
    return 0;
}

int32_t PixelMapPreview::GetByteCount() const
{
    return 0;
}

void* PixelMapPreview::GetPixelManager() const
{
    return nullptr;
}

void* PixelMapPreview::GetRawPixelMapPtr() const
{
    return nullptr;
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
