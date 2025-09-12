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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_MOCK_IMAGE_ACE_IMAGE_SOURCE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_MOCK_IMAGE_ACE_IMAGE_SOURCE_H

#include "gmock/gmock.h"
#include "base/image/image_source.h"
#include "base/image/pixel_map.h"

namespace OHOS::Ace {
class MockImageSource : public ImageSource {
    DECLARE_ACE_TYPE(MockImageSource, ImageSource);

public:
    MOCK_METHOD1(GetProperty, std::string(const std::string& key));
    MOCK_METHOD3(CreatePixelMap,
        RefPtr<PixelMap>(const ImageSource::Size& size, uint32_t& errorCode, const PixelMapConfig& pixelMapConfig));
    MOCK_METHOD4(CreatePixelMap, RefPtr<PixelMap>(uint32_t index, const ImageSource::Size& size, uint32_t& errorCode,
                                     const PixelMapConfig& pixelMapConfig));
    MOCK_METHOD1(CreatePixelMap, RefPtr<PixelMap>(const DecodeOptions& options));
    MOCK_METHOD0(CreatePixelMap, RefPtr<PixelMap>());
    MOCK_METHOD0(GetImageSize, ImageSource::Size());
    MOCK_METHOD0(GetFrameCount, uint32_t());
    MOCK_METHOD0(GetEncodedFormat, std::string());
    MOCK_METHOD0(GetLoopCount, int32_t());
    MOCK_METHOD0(GetDelayTime, std::vector<int32_t>());

    static RefPtr<MockImageSource> mockImageSource_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_MOCK_BASE_IMAGE_ACE_IMAGE_SOURCE_H
