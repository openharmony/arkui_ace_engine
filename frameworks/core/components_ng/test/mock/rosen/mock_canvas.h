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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_CANVAS_H

#include "gmock/gmock-function-mocker.h"
#include "gmock/gmock.h"
#include "testing_canvas.h"
#include "testing_path.h"
#include "testing_point.h"
#include "testing_rect.h"

namespace OHOS::Ace::Testing {
class MockCanvas : public TestingCanvas {
public:
    MockCanvas() = default;
    explicit MockCanvas(void* rawCanvas) {}
    ~MockCanvas() = default;

    MOCK_METHOD2(DrawLine, void(const TestingPoint& startPt, const TestingPoint& endPt));
    MOCK_METHOD1(DrawPath, void(const TestingPath& path));
    MOCK_METHOD3(DrawArc, void(const TestingRect& oval, float startAngle, float sweepAngle));
    MOCK_METHOD1(DrawRect, void(const TestingRect& rect));
    MOCK_METHOD3(Rotate, void(float deg, float sx, float sy));
    MOCK_METHOD2(Translate, void(float sx, float sy));
    MOCK_METHOD2(ClipRoundRect, void(const TestingRoundRect& roundRect, ClipOp op));
    MOCK_METHOD1(AttachPen, TestingCanvas&(const TestingPen& pen));
    MOCK_METHOD1(AttachBrush, TestingCanvas&(const TestingBrush& brush));
    MOCK_METHOD0(DetachPen, TestingCanvas&());
    MOCK_METHOD0(DetachBrush, TestingCanvas&());
    MOCK_METHOD0(Save, void());
    MOCK_METHOD0(Restore, void());
    MOCK_METHOD2(DrawCircle, void(const TestingPoint& centerPt, float radius));
    MOCK_METHOD1(DrawRoundRect, void(const TestingRoundRect& roundRect));
    MOCK_METHOD3(DrawBitmap, void(const TestingBitmap& bitmap, const float px, const float py));
    MOCK_METHOD1(DrawBackground, void(const TestingBrush& brush));
    MOCK_METHOD2(ClipRect, void(const TestingRect& rect, ClipOp op));
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_CANVAS_H
