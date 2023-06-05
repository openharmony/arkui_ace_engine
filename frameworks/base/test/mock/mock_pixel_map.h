/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_PIXEL_MAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_PIXEL_MAP_H

#include "gmock/gmock.h"

#include "base/image/pixel_map.h"

namespace OHOS::Ace {
class MockPixelMap : public PixelMap {
    DECLARE_ACE_TYPE(MockPixelMap, PixelMap);

public:
    MockPixelMap() = default;
    ~MockPixelMap() override = default;

    int32_t GetWidth() const override;
    int32_t GetHeight() const override;
    MOCK_CONST_METHOD0(GetPixels, const uint8_t*());
    MOCK_CONST_METHOD0(GetPixelFormat, PixelFormat());
    MOCK_CONST_METHOD0(GetAlphaType, AlphaType());
    MOCK_CONST_METHOD0(GetRowBytes, int32_t());
    MOCK_CONST_METHOD0(GetByteCount, int32_t());
    MOCK_CONST_METHOD0(GetPixelManager, void*());
    MOCK_CONST_METHOD0(GetRawPixelMapPtr, void*());
    MOCK_METHOD0(GetId, std::string());
    MOCK_METHOD0(GetModifyId, std::string());
    MOCK_METHOD0(GetPixelMapSharedPtr, std::shared_ptr<Media::PixelMap>());
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_TEST_MOCK_MOCK_PIXEL_MAP_H
