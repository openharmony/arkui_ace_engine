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
#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_CANVAS_MOCK_CANVAS_PAINT_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_CANVAS_MOCK_CANVAS_PAINT_H

#include "gmock/gmock.h"
#include "test/mock/core/rosen/testing_brush.h"
#include "test/mock/core/rosen/testing_filter.h"
#include "test/mock/core/rosen/testing_matrix.h"
#include "test/mock/core/rosen/testing_path.h"
#include "test/mock/core/rosen/testing_pen.h"
#include "test/mock/core/rosen/testing_typography.h"

namespace OHOS::Ace::Testing {
class MockPen : public TestingPen {
public:
    MockPen() = default;
    ~MockPen() = default;

    MOCK_METHOD1(SetWidth, void(float width));
    MOCK_METHOD1(SetCapStyle, void(CapStyle cap));
    MOCK_METHOD1(SetColor, void(int color));
    MOCK_METHOD1(SetJoinStyle, void(JoinStyle js));
    MOCK_METHOD1(SetMiterLimit, void(float limit));
    MOCK_METHOD1(SetAlphaF, void(float alpha));
};

class MockFilter : public TestingFilter {
public:
    MockFilter() = default;
    ~MockFilter() = default;

    MOCK_METHOD1(SetMaskFilter, void(std::shared_ptr<TestingMaskFilter> /* maskFilter */));
    MOCK_METHOD1(SetImageFilter, void(std::shared_ptr<TestingImageFilter> /* imageFilter */));
    MOCK_METHOD1(SetColorFilter, void(std::shared_ptr<TestingColorFilter> colorFilter));
};

class MockBrush : public TestingBrush {
public:
    MockBrush() = default;
    ~MockBrush() = default;
    MOCK_METHOD1(SetAlphaF, void(float a));
    MOCK_METHOD1(SetColor, void(int color));
};

class MockPath : public TestingPath {
public:
    MockPath() = default;
    ~MockPath() = default;
    MOCK_METHOD1(SetFillStyle, void(TestingPathFillType fillStyle));
    MOCK_METHOD2(AddRect, void(const TestingRect& rect, TestingPathDirection dir));
    MOCK_METHOD4(ArcTo, void(const TestingPoint& pt1, const TestingPoint& pt2, float startAngle, float sweepAngle));
    MOCK_METHOD1(Transform, void(const TestingMatrix& matrix));
    MOCK_METHOD1(AddPath, void(const TestingPath& src));
};

class MockMatrix : public TestingMatrix {
public:
    MockMatrix() = default;
    ~MockMatrix() = default;
    MOCK_METHOD3(Rotate, void(float degree, float px, float py));
};

class MockTypography : public TestingTypography {
public:
    MockTypography() = default;
    ~MockTypography() = default;
    MOCK_METHOD1(Layout, void(double width));
    MOCK_METHOD3(Paint, void(TestingCanvas* canvas, double x, double y));
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_CANVAS_MOCK_CANVAS_PAINT_H
