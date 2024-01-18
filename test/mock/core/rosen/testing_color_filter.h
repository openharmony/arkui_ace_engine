/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_FILTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_FILTER_H

#include <memory>

#include "testing_color_matrix.h"

namespace OHOS::Ace::Testing {
class TestingColorFilter {
public:
    TestingColorFilter() = default;
    virtual ~TestingColorFilter() = default;

    static std::shared_ptr<TestingColorFilter> CreateMatrixColorFilter(TestingColorMatrix& /* cm */)
    {
        return std::make_shared<TestingColorFilter>();
    }

    static std::shared_ptr<TestingColorFilter> CreateSrgbGammaToLinear()
    {
        return std::make_shared<TestingColorFilter>();
    }

    static std::shared_ptr<TestingColorFilter> CreateLinearToSrgbGamma()
    {
        return std::make_shared<TestingColorFilter>();
    }

    static std::shared_ptr<TestingColorFilter> CreateLumaColorFilter()
    {
        return std::make_shared<TestingColorFilter>();
    }

    static std::shared_ptr<TestingColorFilter> CreateComposeColorFilter(TestingColorFilter& f1, TestingColorFilter& f2)
    {
        return std::make_shared<TestingColorFilter>();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_FILTER_H
