/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_SURFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_SURFACE_H

#include <memory>
#include "testing_image.h"
#include "testing_canvas.h"

namespace OHOS::Ace::Testing {
class TestingSurface {
public:
    TestingSurface() = default;
    ~TestingSurface() = default;

    static std::shared_ptr<TestingSurface> MakeRasterN32Premul(int32_t width, int32_t height)
    {
        return std::make_shared<TestingSurface>();
    }

    std::shared_ptr<TestingImage> GetImageSnapshot() const
    {
        return std::make_shared<TestingImage>();
    }

    std::shared_ptr<TestingCanvas> GetCanvas()
    {
        return std::make_shared<TestingCanvas>();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_SURFACE_H
