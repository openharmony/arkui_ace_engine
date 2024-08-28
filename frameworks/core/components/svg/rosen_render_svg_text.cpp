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

#include "frameworks/core/components/svg/rosen_render_svg_text.h"

#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#include "frameworks/core/components/svg/rosen_render_svg_text_path.h"
#include "frameworks/core/components/transform/rosen_render_transform.h"

namespace OHOS::Ace {

RosenRenderSvgText::RosenRenderSvgText()
{
    RosenSvgPainter::CheckFontType();
}

void RosenRenderSvgText::Paint(RenderContext& context, const Offset& offset)
{
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (rsNode && NeedTransform()) {
        auto [transform, pivotX, pivotY] = GetRawTransformInfo();
        rsNode->SetPivot(pivotX, pivotY);
        RosenRenderTransform::SyncTransformToRsNode(rsNode, transform);
    }

    DrawOffset drawOffset = { offset, offset, false };
    DrawText(context, drawOffset);
}

void RosenRenderSvgText::PaintDirectly(RenderContext& context, const Offset& offset)
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
#else
    RSAutoCanvasRestore save(*canvas, true);
    if (NeedTransform()) {
        canvas->ConcatMatrix(RosenSvgPainter::ToDrawingMatrix(GetTransformMatrix4Raw()));
    }
#endif

    DrawOffset drawOffset = { offset, offset, false };
    DrawText(context, drawOffset);
}

Rect RosenRenderSvgText::GetPaintBounds(const Offset& offset)
{
    DrawOffset drawOffset = { Offset(), offset, false };
    Rect bounds;
    MeasureTextBounds(drawOffset, bounds);
    return bounds;
}

void RosenRenderSvgText::MeasureTextBounds(DrawOffset& drawOffset, Rect& bounds)
{
    UpdateDrawOffset(drawOffset);
    if (!textData_.empty()) {
        drawOffset.current = OnMeasureTextBounds(drawOffset, bounds);
        drawOffset.isTspan = true;
    }

    const auto& children = GetChildren();
    if (!children.empty()) {
        for (const auto& child : children) {
            auto textSpan = AceType::DynamicCast<RosenRenderSvgTspan>(child);
            if (textSpan) {
                textSpan->MeasureTextBounds(drawOffset, bounds);
                continue;
            }

            auto textPath = AceType::DynamicCast<RosenRenderSvgTextPath>(child);
            if (textPath) {
                drawOffset.current = textPath->MeasureTextPathBounds(drawOffset.svg, bounds);
                drawOffset.isTspan = true;
            }
        }
    }
}

void RosenRenderSvgText::DrawText(RenderContext& context, DrawOffset& drawOffset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }

#ifndef USE_ROSEN_DRAWING
    SkAutoCanvasRestore save(canvas, true);
#else
    RSAutoCanvasRestore save(*canvas, true);
#endif
    PaintMaskLayer(context, drawOffset.svg, drawOffset.current);

    // update current offset by attribute
    UpdateDrawOffset(drawOffset);

    if (!textData_.empty()) {
        drawOffset.current = OnDrawText(context, drawOffset);
        drawOffset.isTspan = true;
    }

    const auto& children = GetChildren();
    if (!children.empty()) {
        for (const auto& child : children) {
            auto textSpan = AceType::DynamicCast<RosenRenderSvgTspan>(child);
            if (textSpan) {
                textSpan->DrawText(context, drawOffset);
                continue;
            }

            auto textPath = AceType::DynamicCast<RosenRenderSvgTextPath>(child);
            if (textPath) {
                drawOffset.current = textPath->PaintTextPath(context, drawOffset.svg);
                drawOffset.isTspan = true;
            }
        }
    }
}

Offset RosenRenderSvgText::OnDrawText(RenderContext& context, const DrawOffset& drawOffset)
{
    Offset offset = drawOffset.current;
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return offset;
    }

    std::string text = isDrawSpace_ ? " " + textData_ : textData_;
    SvgTextInfo svgTextInfo = { fillState_, strokeState_, textStyle_, text, opacity_ };
    TextDrawInfo textDrawInfo = { offset, rotate_ };
    offset = RosenSvgPainter::UpdateText(canvas, svgTextInfo, textDrawInfo);
    return offset;
}

Offset RosenRenderSvgText::OnMeasureTextBounds(const DrawOffset& drawOffset, Rect& bounds)
{
    Offset offset = drawOffset.current;
    std::string text = isDrawSpace_ ? " " + textData_ : textData_;
    SvgTextInfo svgTextInfo = { fillState_, strokeState_, textStyle_, text, opacity_ };
    TextDrawInfo textDrawInfo = { offset, rotate_ };
    offset = RosenSvgPainter::MeasureTextBounds(svgTextInfo, textDrawInfo, bounds);
    return offset;
}

void RosenRenderSvgText::UpdateDrawOffset(DrawOffset& drawOffset)
{
    double x = ConvertDimensionToPx(x_, LengthType::HORIZONTAL);
    double dx = ConvertDimensionToPx(dx_, LengthType::HORIZONTAL);
    double y = ConvertDimensionToPx(y_, LengthType::VERTICAL);
    double dy = ConvertDimensionToPx(dy_, LengthType::VERTICAL);
    drawOffset.current = drawOffset.current + Offset(x + dx, y + dy);
    drawOffset.isTspan = false;
}

} // namespace OHOS::Ace
