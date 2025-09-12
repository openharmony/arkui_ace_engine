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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_INFO_H

#include <memory>

#include "testing_color_space.h"

namespace OHOS::Ace::Testing {
enum ColorType {
    COLORTYPE_UNKNOWN = 0,
    COLORTYPE_ALPHA_8,
    COLORTYPE_RGB_565,
    COLORTYPE_ARGB_4444,
    COLORTYPE_RGBA_8888,
    COLORTYPE_BGRA_8888,
};

enum AlphaType {
    ALPHATYPE_UNKNOWN = 0,
    ALPHATYPE_OPAQUE,
    ALPHATYPE_PREMUL,
    ALPHATYPE_UNPREMUL,
};

class TestingImageInfo {
public:
    TestingImageInfo() = default;
    TestingImageInfo(int width, int height, ColorType colorType, AlphaType alphaType,
        std::shared_ptr<TestingColorSpace> colorSpace = nullptr)
    {}
    ~TestingImageInfo() = default;
    int32_t GetBytesPerPixel() const
    {
        return 0;
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_INFO_H
