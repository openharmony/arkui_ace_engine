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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CANVAS_H

#include "testing_bitmap.h"
#include "testing_brush.h"
#include "testing_color.h"
#include "testing_image.h"
#include "testing_matrix.h"
#include "testing_path.h"
#include "testing_pen.h"
#include "testing_point.h"
#include "testing_point3.h"
#include "testing_rect.h"
#include "testing_round_rect.h"
#include "testing_sampling_options.h"
#include "testing_save_layer_ops.h"
#include "testing_shadowflags.h"

namespace OHOS::Ace::Testing {
enum class ClipOp {
    DIFFERENCE,
    INTERSECT,
    UNION,
    XOR,
    REVERSE_DIFFERENCE,
    REPLACE,
};

enum class SrcRectConstraint {
    STRICT_SRC_RECT_CONSTRAINT,
    FAST_SRC_RECT_CONSTRAINT,
};

class TestingCanvas {
public:
    TestingCanvas() = default;
    explicit TestingCanvas(void* rawCanvas) {}
    virtual ~TestingCanvas() = default;

    virtual void DrawLine(const TestingPoint& startPt, const TestingPoint& endPt) {}
    virtual void DrawPath(const TestingPath& path) {}
    virtual void DrawArc(const TestingRect& oval, float startAngle, float sweepAngle) {}
    virtual void DrawRect(const TestingRect& rect) {}
    virtual void ClipRoundRect(const TestingRoundRect& roundRect, ClipOp op, bool antiAlias = false) {}
    virtual void ClipRoundRect(const TestingRect& rect, std::vector<TestingPoint>& pts, bool antiAlias = false) {}
    virtual void Rotate(float deg, float sx, float sy) {}
    virtual void Rotate(float deg) {}
    virtual void Translate(float tx, float ty) {}
    virtual void DrawBitmap(const TestingBitmap& bitmap, const float px, const float py) {}
    virtual void DrawImage(
        const TestingImage& image, const float px, const float py, const TestingSamplingOptions& sampling)
    {}
    virtual void DrawShadow(const TestingPath& path, const TestingPoint3& planeParams, const TestingPoint3& devLightPos,
        float lightRadius, TestingColor /* ambientColor */, TestingColor /* spotColor */, TestingShadowFlags flag)
    {}
    virtual void DrawShadowStyle(const TestingPath& path, const TestingPoint3& planeParams,
        const TestingPoint3& devLightPos, float lightRadius, TestingColor /* ambientColor */,
        TestingColor /* spotColor */, TestingShadowFlags flag, bool isLimitElevation)
    {}
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

    template<typename T>
    const std::shared_ptr<T> GetImpl() const
    {
        return std::shared_ptr<T>();
    }

    virtual void Save() {}
    virtual void Restore() {}
    virtual void DrawCircle(const TestingPoint& center, float radius) {}
    virtual void DrawRoundRect(const TestingRoundRect& roundRect) {}
    virtual void DrawBackground(const TestingBrush& brush) {}
    virtual void ClipRect(const TestingRect& rect, ClipOp op = ClipOp::INTERSECT, bool doAntiAlias = false) {}
    virtual void Scale(float sx, float sy) {}
    virtual void ClipPath(const TestingPath& path, ClipOp op, bool doAntiAlias = false) {}
    virtual void DrawOval(const TestingRect& oval) {}
    virtual void DrawImageRect(
        const TestingImage& image, const TestingRect& dst, const TestingSamplingOptions& sampling)
    {}
    virtual void DrawImageRect(const TestingImage& image, const TestingRect& src, const TestingRect& dst,
        const TestingSamplingOptions& sampling,
        SrcRectConstraint constraint = SrcRectConstraint::STRICT_SRC_RECT_CONSTRAINT)
    {}
    virtual void SaveLayer(const TestingSaveLayerOps& saveLayerOps) {}
    virtual uint32_t GetSaveCount() const
    {
        return 0;
    }

    virtual void RestoreToCount(uint32_t count) {}
    virtual void ConcatMatrix(const TestingMatrix& matrix) {}
    void SetMatrix(const TestingMatrix& matrix) {}
    void ResetMatrix() {}
    void SetScale(float sx, float sy) {}
    void Bind(const TestingBitmap& bitmap) {}
    void Clear(ColorQuad color) {}
    TestingMatrix GetTotalMatrix() const
    {
        return TestingMatrix();
    }
    bool ReadPixels(const TestingImageInfo& dstInfo, void* dstPixels, size_t dstRowBytes, int srcX, int srcY)
    {
        return true;
    }
    void ResetHybridRenderSize(float width, float height) {}
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CANVAS_H
