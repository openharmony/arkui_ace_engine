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

#include "frameworks/core/components/svg/rosen_render_svg_ellipse.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPath.h"
#include "include/core/SkPicture.h"
#endif

#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#include "frameworks/core/components/transform/rosen_render_transform.h"

namespace OHOS::Ace {

void RosenRenderSvgEllipse::Paint(RenderContext& context, const Offset& offset)
{
    const auto renderContext = static_cast<RosenRenderContext*>(&context);
    auto rsNode = renderContext->GetRSNode();
    auto canvas = renderContext->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }

    if (rsNode && NeedTransform()) {
        auto [transform, pivotX, pivotY] = GetRawTransformInfo();
        rsNode->SetPivot(pivotX, pivotY);
        RosenRenderTransform::SyncTransformToRsNode(rsNode, transform);
    }

#ifndef USE_ROSEN_DRAWING
    SkAutoCanvasRestore save(canvas, false);
    PaintMaskLayer(context, offset, offset);

    SkPath path;
#else
    RSAutoCanvasRestore save(*canvas, false);
    PaintMaskLayer(context, offset, offset);

    RSPath path;
#endif
    GetPath(path);
    UpdateGradient(fillState_);

    RenderInfo renderInfo = { AceType::Claim(this), offset, opacity_, true };
    RosenSvgPainter::SetFillStyle(canvas, path, fillState_, renderInfo);
    RosenSvgPainter::SetStrokeStyle(canvas, path, strokeState_, renderInfo);
    RenderNode::Paint(context, offset);
}

void RosenRenderSvgEllipse::PaintDirectly(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkAutoCanvasRestore save(canvas, true);
    if (NeedTransform()) {
        canvas->concat(RosenSvgPainter::ToSkMatrix(GetTransformMatrix4Raw()));
    }
    PaintMaskLayer(context, offset, offset);

    SkPath path;
#else
    RSAutoCanvasRestore save(*canvas, true);
    if (NeedTransform()) {
        canvas->ConcatMatrix(RosenSvgPainter::ToDrawingMatrix(GetTransformMatrix4Raw()));
    }
    PaintMaskLayer(context, offset, offset);

    RSPath path;
#endif
    GetPath(path);
    UpdateGradient(fillState_);
    RosenSvgPainter::SetFillStyle(canvas, path, fillState_, opacity_);
    RosenSvgPainter::SetStrokeStyle(canvas, path, strokeState_, opacity_);
}

void RosenRenderSvgEllipse::UpdateMotion(const std::string& path, const std::string& rotate, double percent)
{
    auto rsNode = GetRSNode();
    if (!rsNode) {
        LOGE("transformLayer is null");
        return;
    }
    RosenSvgPainter::UpdateMotionMatrix(rsNode, path, rotate, percent);
}

Rect RosenRenderSvgEllipse::GetPaintBounds(const Offset& offset)
{
#ifndef USE_ROSEN_DRAWING
    SkPath path;
    GetPath(path);
    auto& bounds = path.getBounds();
    return Rect(bounds.left(), bounds.top(), bounds.width(), bounds.height());
#else
    RSPath path;
    GetPath(path);
    auto bounds = path.GetBounds();
    return Rect(bounds.GetLeft(), bounds.GetTop(), bounds.GetWidth(), bounds.GetHeight());
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderSvgEllipse::GetPath(SkPath& path)
#else
void RosenRenderSvgEllipse::GetPath(RSPath& path)
#endif
{
    double rx = 0.0;
    if (GreatOrEqual(rx_.Value(), 0.0)) {
        rx = ConvertDimensionToPx(rx_, LengthType::HORIZONTAL);
    } else {
        if (GreatNotEqual(ry_.Value(), 0.0)) {
            rx = ConvertDimensionToPx(ry_, LengthType::VERTICAL);
        }
    }
    double ry = 0.0;
    if (GreatOrEqual(ry_.Value(), 0.0)) {
        ry = ConvertDimensionToPx(ry_, LengthType::VERTICAL);
    } else {
        if (GreatNotEqual(rx_.Value(), 0.0)) {
            ry = ConvertDimensionToPx(rx_, LengthType::HORIZONTAL);
        }
    }
#ifndef USE_ROSEN_DRAWING
    SkRect rect = SkRect::MakeXYWH(ConvertDimensionToPx(cx_, LengthType::HORIZONTAL) - rx,
        ConvertDimensionToPx(cy_, LengthType::VERTICAL) - ry, rx + rx, ry + ry);
    path.addOval(rect);
#else
    auto rect = RSRect(ConvertDimensionToPx(cx_, LengthType::HORIZONTAL) - rx,
        ConvertDimensionToPx(cy_, LengthType::VERTICAL) - ry,
        rx + ConvertDimensionToPx(cx_, LengthType::HORIZONTAL),
        ry + ConvertDimensionToPx(cy_, LengthType::VERTICAL));
    path.AddOval(rect);
#endif
}

} // namespace OHOS::Ace
