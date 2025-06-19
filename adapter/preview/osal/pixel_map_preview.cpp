/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/image/pixel_map.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
RefPtr<PixelMap> PixelMap::CreatePixelMap(void* rawPtr)
{
    return nullptr;
}

RefPtr<PixelMap> PixelMap::GetFromDrawable(void* ptr)
{
    return nullptr;
}

bool PixelMap::GetPxielMapListFromAnimatedDrawable(void* ptr, std::vector<RefPtr<PixelMap>>& pixelMaps,
    int32_t& duration, int32_t& iterations)
{
    return false;
}

RefPtr<PixelMap> PixelMap::CreatePixelMapFromDataAbility(void* uniquePtr)
{
    return nullptr;
}

RefPtr<PixelMap> PixelMap::ConvertSkImageToPixmap(
    const uint32_t* colors, uint32_t colorLength, int32_t width, int32_t height)
{
    return nullptr;
}

RefPtr<PixelMap> PixelMap::DecodeTlv(std::vector<uint8_t>& buff)
{
    return nullptr;
}

int32_t PixelMapPreview::GetWidth() const
{
    return -1;
}

int32_t PixelMapPreview::GetHeight() const
{
    return -1;
}

const uint8_t* PixelMapPreview::GetPixels() const
{
    return nullptr;
}

bool PixelMapPreview::GetPixelsVec(std::vector<uint8_t>& data) const
{
    return false;
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

std::string PixelMapPreview::GetId()
{
    return "";
}

std::string PixelMapPreview::GetModifyId()
{
    return "";
}

bool PixelMapPreview::EncodeTlv(std::vector<uint8_t>& buff)
{
    return false;
}

void PixelMapPreview::Scale(float xAxis, float yAxis) {}

void PixelMapPreview::Scale(float xAxis, float yAxis, const AceAntiAliasingOption &option) {}

uint32_t PixelMapPreview::WritePixels(const WritePixelsOptions& opts)
{
    return 0;
}

void PixelMapPreview::SetMemoryName(std::string pixelMapName) const {}
} // namespace OHOS::Ace
