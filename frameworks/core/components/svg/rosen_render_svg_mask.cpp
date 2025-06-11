/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/core/components/svg/rosen_render_svg_mask.h"

#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#include "frameworks/core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

void RosenRenderSvgMask::Paint(RenderContext& context, const Offset& offset)
{
    return;
}

void RosenRenderSvgMask::PaintMaskLayer(RenderContext& context, const Offset& offset, const Rect& paintRect)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }

    RSRect maskBounds = RSRect(static_cast<RSScalar>(paintRect.Left() + ParseUnitsAttr(x_, paintRect.Width())),
        static_cast<RSScalar>(paintRect.Top() + ParseUnitsAttr(y_, paintRect.Height())),
        static_cast<RSScalar>(ParseUnitsAttr(width_, paintRect.Width()) +
        paintRect.Left() + ParseUnitsAttr(x_, paintRect.Width())),
        static_cast<RSScalar>(ParseUnitsAttr(height_, paintRect.Height()) +
        paintRect.Top() + ParseUnitsAttr(y_, paintRect.Height())));

    // create mask layer
    RSSaveLayerOps slo(&maskBounds, nullptr);
    canvas->SaveLayer(slo);
    {
        // render mask content
        RSAutoCanvasRestore save(*canvas, false);
        RosenSvgPainter::SetMask(canvas);
        PaintDirectly(context, offset);
    }

    // create content layer and render content
    RSBrush maskBrush;
    maskBrush.SetBlendMode(RSBlendMode::SRC_IN);
    RSSaveLayerOps maskSlo(&maskBounds, &maskBrush);
    canvas->SaveLayer(maskSlo);
    canvas->ClipRect(maskBounds, RSClipOp::INTERSECT, true);
}

} // namespace OHOS::Ace
