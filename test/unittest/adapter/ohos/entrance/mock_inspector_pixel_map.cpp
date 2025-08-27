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
#include "adapter/ohos/osal/pixel_map_ohos.h"

namespace OHOS::Ace {
int32_t PixelMapOhos::GetWidth() const
{
    return 0;
}
int32_t PixelMapOhos::GetHeight() const
{
    return 0;
}
bool PixelMapOhos::GetPixelsVec(std::vector<uint8_t>& data) const
{
    return false;
}
const uint8_t* PixelMapOhos::GetPixels() const
{
    return nullptr;
}
PixelFormat PixelMapOhos::GetPixelFormat() const
{
    return PixelFormat::UNKNOWN;
}
AlphaType PixelMapOhos::GetAlphaType() const
{
    return AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
}
int32_t PixelMapOhos::GetRowStride() const
{
    return 0;
}
int32_t PixelMapOhos::GetRowBytes() const
{
    return 0;
}
int32_t PixelMapOhos::GetByteCount() const
{
    return 0;
}
AllocatorType PixelMapOhos::GetAllocatorType() const
{
    return AllocatorType::DEFAULT;
}
bool PixelMapOhos::IsHdr() const
{
    return false;
}
void* PixelMapOhos::GetPixelManager() const
{
    return nullptr;
}
void* PixelMapOhos::GetRawPixelMapPtr() const
{
    return nullptr;
}
std::string PixelMapOhos::GetId()
{
    return "";
}
std::string PixelMapOhos::GetModifyId()
{
    return "";
}
std::shared_ptr<Media::PixelMap> PixelMapOhos::GetPixelMapSharedPtr()
{
    return nullptr;
}
void* PixelMapOhos::GetWritablePixels() const
{
    return nullptr;
}
void PixelMapOhos::Scale(float xAxis, float yAxis)
{
}
void PixelMapOhos::Scale(float xAxis, float yAxis, const AceAntiAliasingOption &option)
{
}
void PixelMapOhos::SavePixelMapToFile(const std::string& dst) const
{
}
RefPtr<PixelMap> PixelMapOhos::GetCropPixelMap(const Rect& srcRect)\
{
    return nullptr;
}
bool PixelMapOhos::EncodeTlv(std::vector<uint8_t>& buff)
{
    return false;
}
uint32_t PixelMapOhos::WritePixels(const WritePixelsOptions& opts)
{
    return 0;
}
uint32_t PixelMapOhos::GetInnerColorGamut() const
{
    return 0;
}
void PixelMapOhos::SetMemoryName(std::string pixelMapName) const
{
}
} // namespace OHOS::Ace
