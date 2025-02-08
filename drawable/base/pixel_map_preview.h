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

#ifndef FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_BASE_PIXEL_MAP_PREVIEW_H
#define FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_BASE_PIXEL_MAP_PREVIEW_H

#include "pixel_map.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class PixelMapPreview : public PixelMap {
public:
    explicit PixelMapPreview(std::shared_ptr<Media::PixelMap> pixmap) : pixmap_(std::move(pixmap)) {}

    int32_t GetWidth() const override;
    int32_t GetHeight() const override;
    const uint8_t* GetPixels() const override;
    PixelFormat GetPixelFormat() const override;
    AlphaType GetAlphaType() const override;
    int32_t GetRowStride() const override;
    int32_t GetRowBytes() const override;
    int32_t GetByteCount() const override;
    void* GetPixelManager() const override;
    void* GetRawPixelMapPtr() const override;
    std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr() override;
    bool IsHdr() const override;

private:
    std::shared_ptr<Media::PixelMap> pixmap_;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_BASE_PIXEL_MAP_PREVIEW_H
