/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef CAPI_STUBS_ACE_PIXELMAP_STUB_H
#define CAPI_STUBS_ACE_PIXELMAP_STUB_H

#include <string>

#include "base/memory/ace_type.h"
#include "frameworks/base/image/pixel_map.h"

namespace OHOS::Ace {
class PixelMapStub : public PixelMap {
public:
    PixelMapStub() = default;

    int32_t GetWidth() const override
    {
        return stubWidth;
    }

    int32_t GetHeight() const override
    {
        return stubHeight;
    }

    bool GetPixelsVec(std::vector<uint8_t>& data) const override
    {
        // Implement pixel data retrieval here
        data = stubPixelData;
        return true;  // Return true to indicate success
    }

    const uint8_t* GetPixels() const override
    {
        if (!stubPixelData.empty()) {
            return stubPixelData.data();
        }
        return nullptr;
    }

    PixelFormat GetPixelFormat() const override
    {
        return PixelFormat::ARGB_8888;  // Example format
    }

    AlphaType GetAlphaType() const override
    {
        return AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;  // Example alpha type
    }

    int32_t GetRowStride() const override
    {
        return stubWidth * 4;  // Assuming ARGB_8888 where each pixel is 4 bytes
    }

    int32_t GetRowBytes() const override
    {
        return GetRowStride();
    }

    int32_t GetByteCount() const override
    {
        return GetRowStride() * stubHeight;
    }

    AllocatorType GetAllocatorType() const override
    {
        return AllocatorType::DEFAULT;  // Example allocator type
    }

    bool IsHdr() const override
    {
        return false;  // Assuming not HDR for simplicity
    }

    void* GetPixelManager() const override
    {
        return nullptr;  // Return null pointer as placeholder
    }

    void* GetRawPixelMapPtr() const override
    {
        return nullptr;  // Return null pointer as placeholder
    }

    std::string GetId() override
    {
        return stubId;
    }

    std::string GetModifyId() override
    {
        return stubModifyId;
    }

    std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr() override
    {
        return nullptr;  // Return null pointer as placeholder
    }

    void* GetWritablePixels() const override
    {
        if (!stubPixelData.empty()) {
            return const_cast<uint8_t*>(stubPixelData.data());
        }
        return nullptr;
    }

    void Scale(float xAxis, float yAxis) override
    {
        // Implement scaling logic here
        stubWidth *= xAxis;
        stubHeight *= yAxis;
    }

    void Scale(float xAxis, float yAxis, const AceAntiAliasingOption &option) override
    {
        // Implement scaled with anti-aliasing option
        Scale(xAxis, yAxis);  // Reuse the existing scaling function for simplicity
    }

    void SavePixelMapToFile(const std::string& dst) const override
    {
        // Implement file saving logic here
    }

    RefPtr<PixelMap> GetCropPixelMap(const Rect& srcRect) override
    {
        // Implement cropping logic here and return a new PixelMap instance
        return nullptr;  // Return null pointer as placeholder
    }

    bool EncodeTlv(std::vector<uint8_t>& buff) override
    {
        // Implement TLV encoding logic here
        buff = stubEncodedData;
        return true;  // Return true to indicate success
    }

    uint32_t WritePixels(const WritePixelsOptions& opts) override
    {
        return 0;
    }

    uint32_t GetInnerColorGamut() const override
    {
        return 0;
    }

    void SetMemoryName(std::string pixelMapName) const override
    {
    }

    uint32_t GetUniqueId() override
    {
        return 0;
    }

private:
    int32_t stubWidth = 2;
    int32_t stubHeight = 2;
    std::vector<uint8_t> stubPixelData = std::vector<uint8_t>(stubWidth * stubHeight * 4, 0); // ARGB_8888
    std::string stubId = "StubPixelMapId";
    std::string stubModifyId = "StubPixelMapModifyId";
    std::vector<uint8_t> stubEncodedData = {0x1A, 0x2B, 0x3C}; // Example encoded data
};

} // OHOS::Ace

#endif // CAPI_STUBS_ACE_PIXELMAP_STUB_H
