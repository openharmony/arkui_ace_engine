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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_MATRIX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_MATRIX_H

#include <memory>

namespace OHOS::Ace::Testing {
class TestingColorMatrix {
public:
    typedef float scalar;
    TestingColorMatrix() = default;
    virtual ~TestingColorMatrix() = default;

    constexpr static int MATRIX_SIZE = 20;

    virtual void SetArray(const float src[MATRIX_SIZE]) {}
    virtual void SetScale(scalar sr, scalar sg, scalar sb, scalar sa) {}
    virtual void PreConcat(const TestingColorMatrix& m) {}
    virtual void PostConcat(const TestingColorMatrix& m) {}
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_COLOR_MATRIX_H
