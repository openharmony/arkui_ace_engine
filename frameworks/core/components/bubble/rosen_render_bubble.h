/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "core/components/bubble/render_bubble.h"
#include "core/pipeline/base/rosen_render_context.h"

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUBBLE_ROSEN_RENDER_BUBBLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUBBLE_ROSEN_RENDER_BUBBLE_H

namespace OHOS::Ace {

class RosenRenderBubble : public RenderBubble {
    DECLARE_ACE_TYPE(RosenRenderBubble, RenderBubble);

public:
    RosenRenderBubble() = default;
    ~RosenRenderBubble() override = default;

    void Paint(RenderContext& context, const Offset& offset) override;

private:
    bool hasEventFired_ = false;
#ifndef USE_ROSEN_DRAWING
    SkPath path_;
    SkRRect rrect_;

    SkRRect MakeRRect();
#else
    RSRecordingPath path_;
    RSRoundRect rrect_;

    RSRoundRect MakeRRect();
#endif
    void PaintMask(RenderContext& context);
    void PaintBubble(RenderContext& context);
#ifndef USE_ROSEN_DRAWING
    void PaintTopBubble(SkCanvas* skCanvas, const SkPaint& paint);
    void PaintBottomBubble(SkCanvas* skCanvas, const SkPaint& paint);
    void PaintTopBubbleInJs(SkCanvas* skCanvas, const SkPaint& paint);
    void PaintBottomBubbleInJs(SkCanvas* skCanvas, const SkPaint& paint);
    void PaintNonCustomPopup(SkCanvas* skCanvas, const SkPaint& paint);
    void PaintBubbleWithArrow(SkCanvas* skCanvas, const SkPaint& paint);
    void PaintDefaultBubble(SkCanvas* skCanvas, const SkPaint& paint);
    void PaintBorder(RenderContext& context);
    SkCanvas* GetSkCanvas(RenderContext& context);
#else
    void PaintTopBubble(RSCanvas* canvas, const RSPen& pen);
    void PaintBottomBubble(RSCanvas* canvas, const RSPen& pen);
    void PaintTopBubbleInJs(RSCanvas* canvas, const RSPen& pen);
    void PaintBottomBubbleInJs(RSCanvas* canvas, const RSPen& pen);
    void PaintNonCustomPopup(RSCanvas* canvas, const RSPen& pen);
    void PaintBubbleWithArrow(RSCanvas* canvas, const RSPen& pen);
    void PaintDefaultBubble(RSCanvas* canvas, const RSPen& pen);
    void PaintBorder(RenderContext& context);
    RSCanvas* GetDrawingCanvas(RenderContext& context);
#endif
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BUBBLE_ROSEN_RENDER_BUBBLE_H
