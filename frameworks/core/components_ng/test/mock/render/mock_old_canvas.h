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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RENDER_MOCK_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RENDER_MOCK_CANVAS_H

#include "core/components_ng/render/canvas.h"

namespace OHOS::Ace::NG {
enum class ClipQuality {
    NONE = 0,
    HARD_EDGE,
    ANTI_ALIAS,
};

// Canvas is interface for drawing content.
class MockOldCanvas : public Canvas {
    DECLARE_ACE_TYPE(MockOldCanvas, Canvas)
public:
    MockOldCanvas() = default;
    ~MockOldCanvas() = default;
    
    MOCK_METHOD0(Save, void());
    MOCK_METHOD0(Restore, void());
    MOCK_METHOD2(Translate, void(float dx, float dy));
    MOCK_METHOD2(Scale, void(float sx, float sy));
    MOCK_METHOD1(Rotate, void(float rad));
    MOCK_METHOD2(Skew, void(float sx, float sy));
    MOCK_METHOD1(SetMatrix, void(const Matrix3& matrix));
    MOCK_METHOD1(ConcatMatrix, void(const Matrix3& matrix));
    MOCK_METHOD2(ClipRect, void(const RectF& rect, ClipQuality quality));
    MOCK_METHOD2(ClipRRect, void(const RRect& rRect, ClipQuality quality));
    MOCK_METHOD2(ClipWithPath, void(const ClipPath& path, ClipQuality quality));
    MOCK_METHOD1(ClearColor, void(const Color& color));
    MOCK_METHOD1(DrawColor, void(const Color& color));
    MOCK_METHOD3(DrawLine, void(const PointF& start, const PointF& end, const RefPtr<Paint>& paint));
    MOCK_METHOD2(DrawRect, void(const RectF& rect, const RefPtr<Paint>& paint));
    MOCK_METHOD2(DrawRRect, void(const RRect& rect, const RefPtr<Paint>& paint));
    MOCK_METHOD4(DrawCircle, void(float centerX, float centerY, float radius, const RefPtr<Paint>& paint));
    MOCK_METHOD4(DrawImage,
        void(const RefPtr<CanvasImage>& image, const RectF& srcRect, const RectF& dstRect, const RefPtr<Paint>& paint));
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_MOCK_RENDER_MOCK_CANVAS_H
