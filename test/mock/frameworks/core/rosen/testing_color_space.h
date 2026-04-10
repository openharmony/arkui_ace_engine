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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_SPACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_SPACE_H

#include <memory>

namespace OHOS::Ace::Testing {
enum class TestingCMSTransferFuncType {
    SRGB,
    DOT2,
    LINEAR,
    REC2020,
};

enum class TestingCMSMatrixType {
    SRGB,
    ADOBE_RGB,
    DCIP3,
    REC2020,
    XYZ,
};

enum class TestingClamp {
    NO_CLAMP,
    YES_CLAMP,
};

class TestingColorSpace {
public:
    TestingColorSpace() = default;
    virtual ~TestingColorSpace() = default;

    static std::shared_ptr<TestingColorSpace> CreateSRGB()
    {
        return std::make_shared<TestingColorSpace>();
    }

    static std::shared_ptr<TestingColorSpace> CreateRGB(
        const TestingCMSTransferFuncType& func, const TestingCMSMatrixType& matrix)
    {
        return std::make_shared<TestingColorSpace>();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_SPACE_H