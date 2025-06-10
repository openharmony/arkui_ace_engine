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

#include <string>
#include "base/pixel_map.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class PixelMapPreview : public PixelMap {
public:
    int32_t GetWidth() const override;
    int32_t GetHeight() const override;
    const uint8_t* GetPixels() const override;
    int32_t GetRowStride() const override;
    int32_t GetRowBytes() const override;
    int32_t GetByteCount() const override;
    void* GetRawPixelMapPtr() const override;
    std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr() override;
    bool IsHdr() const override;
    void SetMemoryName(std::string pixelMapName) const override;
};

std::shared_ptr<PixelMap> Create(const std::shared_ptr<Media::PixelMap>& pixmap)
{
    return nullptr;
}

std::shared_ptr<PixelMap> PixelMap::Create(const std::shared_ptr<Media::PixelMap>& pixmap)
{
    return nullptr;
}

int32_t PixelMapPreview::GetWidth() const
{
    return -1;
}

bool PixelMapPreview::IsHdr() const
{
    return false;
}

int32_t PixelMapPreview::GetHeight() const
{
    return -1;
}

const uint8_t* PixelMapPreview::GetPixels() const
{
    return nullptr;
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

void* PixelMapPreview::GetRawPixelMapPtr() const
{
    return nullptr;
}

std::shared_ptr<Media::PixelMap> PixelMapPreview::GetPixelMapSharedPtr()
{
    return nullptr;
}

void PixelMapPreview::SetMemoryName(std::string pixelMapName) const {}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
