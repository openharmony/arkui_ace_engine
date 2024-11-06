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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_ROUND_RECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_ROUND_RECT_H

#include <vector>

#include "testing_point.h"
#include "testing_rect.h"

namespace OHOS::Ace::Testing {
class TestingRoundRect {
public:
    enum CornerPos {
        TOP_LEFT_POS,
        TOP_RIGHT_POS,
        BOTTOM_RIGHT_POS,
        BOTTOM_LEFT_POS,
        CORNER_NUMBER,
    };

    TestingRoundRect()
        : radiusXY_(CORNER_NUMBER, TestingPoint(0, 0)) {};
    virtual ~TestingRoundRect() = default;

    TestingRoundRect(const TestingRoundRect& testingRoundRect) : TestingRoundRect()
    {
        rect_ = testingRoundRect.rect_;
    }

    TestingRoundRect(const TestingRect& rect, float xRad, float yRad) : TestingRoundRect()
    {
        rect_ = rect;
        for (size_t i = 0; i < radiusXY_.size(); ++i) {
            radiusXY_[i].SetX(xRad);
            radiusXY_[i].SetY(yRad);
        }
    }

    TestingRoundRect(const TestingRect& rect, std::vector<TestingPoint>& radiusXY) : TestingRoundRect()
    {
        rect_ = rect;
        for (size_t i = 0; i < radiusXY_.size(); ++i) {
            radiusXY_[i] = radiusXY[i];
        }
    }

    virtual void SetCornerRadius(CornerPos pos, float radiusX, float radiusY)
    {
        radiusXY_[pos].SetX(radiusX);
        radiusXY_[pos].SetY(radiusY);
    }

    virtual TestingPoint GetCornerRadius(CornerPos pos) const
    {
        return radiusXY_[pos];
    }

    virtual void SetRect(const TestingRect& rect)
    {
        rect_ = rect;
    }

    virtual TestingRect GetRect() const
    {
        return rect_;
    }

    virtual void Offset(float dx, float dy)
    {
        rect_.Offset(dx, dy);
    }

private:
    TestingRect rect_;
    std::vector<TestingPoint> radiusXY_;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_ROUND_RECT_H
