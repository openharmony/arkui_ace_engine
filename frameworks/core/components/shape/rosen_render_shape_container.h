/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SHAPE_ROSEN_RENDER_SHAPE_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SHAPE_ROSEN_RENDER_SHAPE_CONTAINER_H

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPath.h"
#endif

#include "core/components/custom_paint/offscreen_canvas.h"
#include "core/components/shape/rosen_render_shape.h"
#include "frameworks/core/components/shape/render_shape_container.h"

namespace OHOS::Ace {

class RosenRenderShapeContainer : public RenderShapeContainer {
    DECLARE_ACE_TYPE(RosenRenderShapeContainer, RenderShapeContainer);

public:
    void PerformLayout() override;
    void Paint(RenderContext& context, const Offset& offset) override;
    RefPtr<RosenRenderShape> GetShapeChild(const RefPtr<RenderNode>& node, Offset& offset);

private:
    void BitmapMesh(RenderContext& context, const Offset& offset);
#ifndef USE_ROSEN_DRAWING
    void DrawBitmapMesh(SkBitmap& bitmap, int column, int row,
        const float* vertices, const int* colors, const SkPaint* paint);

    SkPath path_;
    SkBitmap skOffBitmap_;
    std::unique_ptr<SkCanvas> skOffCanvas_;
    SkCanvas* skCanvas_ = nullptr;
#else
    void DrawBitmapMesh(RSBitmap& bitmap, int column, int row,
        const float* vertices, const int* colors, const RSBrush* brush);

    RSRecordingPath path_;
    RSBitmap offBitmap_;
    std::unique_ptr<RSCanvas> offCanvas_;
    RSCanvas* canvas_ = nullptr;
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SHAPE_ROSEN_RENDER_SHAPE_CONTAINER_H
