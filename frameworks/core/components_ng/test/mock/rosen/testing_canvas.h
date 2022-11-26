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

#include "draw/clip.h"
#include "testing_brush.h"
#include "testing_path.h"
#include "testing_pen.h"
#include "utils/point.h"
#include "utils/round_rect.h"

namespace OHOS::Ace::Testing {
using Point = Rosen::Drawing::Point;
using RoundRect = Rosen::Drawing::RoundRect;
using ClipOp = Rosen::Drawing::ClipOp;

class TestingCanvas {
public:
    TestingCanvas() = default;
    explicit TestingCanvas(void* rawCanvas) {}
    virtual ~TestingCanvas() = default;

    virtual void DrawLine(const Point& startPt, const Point& endPt) {}

    virtual void DrawPath(const TestingPath& path) {}
    virtual void DrawArc(const Rect& oval, scalar startAngle, scalar sweepAngle) {}
    virtual void DrawRect(const Rect& rect) {}

    virtual void ClipRoundRect(const RoundRect& roundRect, ClipOp op) {}

    virtual void Rotate(scalar deg, scalar sx, scalar sy) {}
    virtual void Translate(scalar dx, scalar dy) {}

    virtual TestingCanvas& AttachPen(const TestingPen& pen)
    {
        return *this;
    }

    virtual TestingCanvas& AttachBrush(const TestingBrush& brush)
    {
        return *this;
    }

    virtual TestingCanvas& DetachPen()
    {
        return *this;
    }

    virtual TestingCanvas& DetachBrush()
    {
        return *this;
    }

    virtual void Save() {}
    virtual void Restore() {}
    virtual void DrawCircle(const Point& centerPt, scalar radius) {}
    virtual void DrawRoundRect(const RoundRect& roundRect) {}
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_TESTING_CANVAS_H
