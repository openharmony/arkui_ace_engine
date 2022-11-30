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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_MATRIX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_MATRIX_H

#include <stdint.h>
#include <vector>

#include "utils/point.h"
#include "utils/scalar.h"

namespace OHOS::Ace::Testing {
using scalar = Rosen::Drawing::scalar;
using Point = Rosen::Drawing::PointF;
class TestingMatrix {
public:
    TestingMatrix() = default;
    ~TestingMatrix() = default;
    void Rotate(scalar degree, scalar px, scalar py) {}
    void Translate(scalar dx, scalar dy) {}
    void Scale(scalar sx, scalar sy, scalar px, scalar py) {}
    TestingMatrix operator*(const TestingMatrix& other)
    {
        return other;
    }
    bool operator==(const TestingMatrix& other)
    {
        return false;
    }
    void SetMatrix(scalar scaleX, scalar skewX, scalar transX, scalar skewY, scalar scaleY, scalar transY,
        scalar persp0, scalar persp1, scalar persp2)
    {}
    void MapPoints(std::vector<Point>& dst, const std::vector<Point>& src, uint32_t count) const {}
    scalar Get(int index) const
    {
        return scalar();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_MATRIX_H
