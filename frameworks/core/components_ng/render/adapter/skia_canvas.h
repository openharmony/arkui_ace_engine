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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_CANVAS_H

#include "core/components_ng/render/canvas.h"

class SkCanvas;

namespace OHOS::Ace::NG {

// Canvas is interface for drawing content.
class SkiaCanvas : public Canvas {
    DECLARE_ACE_TYPE(NG::SkiaCanvas, NG::Canvas)

public:
    explicit SkiaCanvas(SkCanvas* canvas) : rawCanvas_(canvas) {}
    ~SkiaCanvas() override = default;

    // save and restore interfaces
    void Save() override;
    void Restore() override;

    // transform interfaces
    void Translate(float dx, float dy) override;
    void Scale(float sx, float sy) override;
    void Rotate(float rad) override;
    void Skew(float sx, float sy) override;
    void SetMatrix(const Matrix3& matrix) override;
    void ConcatMatrix(const Matrix3& matrix) override;

    // clip interfaces
    void ClipRect(const RectF& rect, ClipQuality quality) override;
    void ClipRRect(const RRect& rRect, ClipQuality quality) override;
    void ClipWithPath(const ClipPath& path, ClipQuality quality) override;

    // drawing interfaces
    void ClearColor(const Color& color) override;
    void DrawColor(const Color& color) override;
    void DrawLine(const PointF& start, const PointF& end, const RefPtr<Paint>& paint) override;
    void DrawRect(const RectF& rect, const RefPtr<Paint>& paint) override;
    void DrawRRect(const RRect& rect, const RefPtr<Paint>& paint) override;
    void DrawCircle(float centerX, float centerY, float radius, const RefPtr<Paint>& paint) override;

    void DrawImage(const RefPtr<CanvasImage>& image, const RectF& srcRect, const RectF& dstRect,
        const RefPtr<Paint>& paint) override;

    SkCanvas* RawCanvas()
    {
        return rawCanvas_;
    }

private:
    SkCanvas* rawCanvas_ = nullptr;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SKIA_CANVAS_H
