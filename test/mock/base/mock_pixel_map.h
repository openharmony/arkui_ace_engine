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
#ifndef FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_PIXEL_MAP_H
#define FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_PIXEL_MAP_H
#include "gmock/gmock.h"

#include "base/image/pixel_map.h"

namespace OHOS::Ace {
class MockPixelMap : public PixelMap {
public:
    MOCK_METHOD(int32_t, GetWidth, (), (const override));
    MOCK_METHOD(int32_t, GetHeight, (), (const override));
    MOCK_METHOD(bool, GetPixelsVec, (std::vector<uint8_t> & data), (const override));
    MOCK_METHOD(const uint8_t*, GetPixels, (), (const override));
    MOCK_METHOD(PixelFormat, GetPixelFormat, (), (const override));
    MOCK_METHOD(AlphaType, GetAlphaType, (), (const override));
    MOCK_METHOD(int32_t, GetRowStride, (), (const override));
    MOCK_METHOD(int32_t, GetRowBytes, (), (const override));
    MOCK_METHOD(int32_t, GetByteCount, (), (const override));
    MOCK_METHOD(void*, GetPixelManager, (), (const override));
    MOCK_METHOD(void*, GetRawPixelMapPtr, (), (const override));
    MOCK_CONST_METHOD0(GetWritablePixels, void*());
    MOCK_METHOD(void, Scale, (float xAxis, float yAxis), (override));
    MOCK_METHOD(void, Scale, (float xAxis, float yAxis, const AceAntiAliasingOption &option), (override));
    MOCK_METHOD(std::string, GetId, (), (override));
    MOCK_METHOD(std::string, GetModifyId, (), (override));
    MOCK_METHOD0(GetPixelMapSharedPtr, std::shared_ptr<Media::PixelMap>());
    MOCK_METHOD(void, SavePixelMapToFile, (const std::string& dst), (const override));
    MOCK_METHOD(RefPtr<PixelMap>, GetCropPixelMap, (const Rect& srcRect), (override));
    MOCK_METHOD(bool, EncodeTlv, (std::vector<uint8_t>& buff), (override));
    MOCK_METHOD(AllocatorType, GetAllocatorType, (), (const override));
    MOCK_METHOD(bool, IsHdr, (), (const override));
    MOCK_METHOD(uint32_t, WritePixels, (const WritePixelsOptions& opts), (override));
    MOCK_METHOD(uint32_t, GetInnerColorGamut, (), (const override));
    MOCK_METHOD(void, SetMemoryName, (std::string pixelMapName), (const override));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_PIXEL_MAP_H
