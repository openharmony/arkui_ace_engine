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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_ROSEN_TESTING_BITMAP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_ROSEN_TESTING_BITMAP_H

#include <cstddef>
#include <cstdint>

#include "testing_rect.h"

namespace OHOS::Ace::Testing {
class TestingImageInfo;
typedef uint32_t ColorQuad;

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

struct BitmapFormat {
    ColorType colorType;
    AlphaType alphaType;
};

class TestingBitmap {
public:
    TestingBitmap() = default;
    ~TestingBitmap() = default;

    virtual void* GetPixels()
    {
        return nullptr;
    }

    void SetPixels(void* pixel) {}

    void ClearWithColor(const ColorQuad& color) const {}
    size_t ComputeByteSize() const
    {
        return 0;
    }

    bool ExtractSubset(TestingBitmap& dst, const TestingRect& subset) const
    {
        return false;
    }

    bool ReadPixels(
        const TestingImageInfo& dstInfo, void* dstPixels, size_t dstRowBytes, int32_t srcX, int32_t srcY) const
    {
        return false;
    }

    void Free() {}

    bool Build(const int width, const int height, const BitmapFormat& format)
    {
        return false;
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_BITMAP_H
