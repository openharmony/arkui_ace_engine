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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_MATRIX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_MATRIX_H

#include <stdint.h>
#include <vector>

#include "testing_point.h"

namespace OHOS::Ace::Testing {
class TestingMatrix {
public:
    enum Index {
        SCALE_X,
        SKEW_X,
        TRANS_X,
        SKEW_Y,
        SCALE_Y,
        TRANS_Y,
        PERSP_0,
        PERSP_1,
        PERSP_2,
    };

    TestingMatrix() = default;
    ~TestingMatrix() = default;
    void PreRotate(float degree, float px, float py) {}
    void PreConcat(const TestingMatrix& other) {}
    void PreTranslate(float dx, float dy) {}
    void SetScale(float sx, float sy) {}
    void Rotate(float degree, float px, float py) {}
    void Translate(float dx, float dy) {}
    void Scale(float sx, float sy, float px, float py) {}

    TestingMatrix operator*(const TestingMatrix& other)
    {
        return other;
    }

    bool operator==(const TestingMatrix& /* other */)
    {
        return false;
    }

    void SetMatrix(
        float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float p0, float p1, float p2)
    {}

    void Set(Index index, float value) {}

    void MapPoints(std::vector<TestingPoint>& dst, const std::vector<TestingPoint>& src, uint32_t count) const {}

    float Get(int /* index */) const
    {
        return 1.0f;
    }

    void Reset() {}
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_MATRIX_H
