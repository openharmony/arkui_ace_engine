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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_CANVAS_H

#include "testing_pen.h"
#include "utils/point.h"

namespace OHOS::Ace::Testing {
using Point = Rosen::Drawing::Point;
class TestingCanvas {
public:
    TestingCanvas() = default;
    explicit TestingCanvas(void* rawCanvas) {}
    virtual ~TestingCanvas() = default;

    virtual void DrawLine(const Point& startPt, const Point& endPt) = 0;
    virtual TestingCanvas& AttachPen(const TestingPen& pen) = 0;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_CANVAS_H
