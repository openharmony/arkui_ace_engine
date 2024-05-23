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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_H

#include <cstdint>
#include <memory>

#include "testing_bitmap.h"
#include "testing_data.h"

namespace OHOS::Ace::Testing {
class TestingImage {
public:
    TestingImage() = default;
    ~TestingImage() = default;

    virtual int GetWidth()
    {
        const int imageWidth = 100;
        return imageWidth;
    }

    virtual int GetHeight()
    {
        const int imageHeight = 100;
        return imageHeight;
    }

    virtual uint32_t GetUniqueID() const
    {
        const uint32_t id = 0;
        return id;
    }

    virtual bool BuildFromBitmap(const TestingBitmap& bitmap) const
    {
        return true;
    }

    bool MakeFromEncoded(const std::shared_ptr<TestingData>& data)
    {
        return true;
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_H
