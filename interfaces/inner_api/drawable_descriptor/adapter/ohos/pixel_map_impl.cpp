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

#include <memory>

#include "image_source.h"

#include "base/marcos.h"
#include "base/pixel_map.h"

namespace OHOS {
namespace Ace {
namespace Drawable {

class PixelMapImpl final : public PixelMap {
public:
    explicit PixelMapImpl(const std::shared_ptr<Media::PixelMap>& pixmap) : pixmap_(std::move(pixmap)) {}
    ~PixelMapImpl() = default;

    int32_t GetWidth() const override;
    int32_t GetHeight() const override;
    const uint8_t* GetPixels() const override;
    int32_t GetRowStride() const override;
    int32_t GetRowBytes() const override;
    int32_t GetByteCount() const override;
    void* GetRawPixelMapPtr() const override;
    std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr() override;
    bool IsHdr() const override;

private:
    std::shared_ptr<Media::PixelMap> pixmap_;
};

std::shared_ptr<PixelMap> PixelMap::Create(std::unique_ptr<Media::PixelMap>&& pixmap)
{
    return std::make_shared<PixelMapImpl>(std::move(pixmap));
}

std::shared_ptr<PixelMap>  PixelMap::Create(const std::shared_ptr<Media::PixelMap>& pixmap)
{
    return std::make_shared<PixelMapImpl>(pixmap);
}

int32_t PixelMapImpl::GetWidth() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetWidth();
}

int32_t PixelMapImpl::GetHeight() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetHeight();
}

const uint8_t* PixelMapImpl::GetPixels() const
{
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return pixmap_->GetPixels();
}

int32_t PixelMapImpl::GetRowStride() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetRowStride();
}

int32_t PixelMapImpl::GetRowBytes() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetRowBytes();
}

int32_t PixelMapImpl::GetByteCount() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetByteCount();
}

bool PixelMapImpl::IsHdr() const
{
    CHECK_NULL_RETURN(pixmap_, false);
    return pixmap_->IsHdr();
}

void* PixelMapImpl::GetRawPixelMapPtr() const
{
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return pixmap_.get();
}

std::shared_ptr<Media::PixelMap> PixelMapImpl::GetPixelMapSharedPtr()
{
    return pixmap_;
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
