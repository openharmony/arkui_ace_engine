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

#include "frameworks/core/components/svg/flutter_render_svg_text.h"

#include "frameworks/core/components/common/painter/flutter_svg_painter.h"
#include "frameworks/core/components/svg/flutter_render_svg_text_path.h"
#include "frameworks/core/components/svg/flutter_render_svg_tspan.h"
#include "frameworks/core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderNode> FlutterRenderSvgText::Create()
{
    FlutterSvgPainter::CheckFontType();
    return AceType::MakeRefPtr<FlutterRenderSvgText>();
}

RenderLayer FlutterRenderSvgText::GetRenderLayer()
{
    if (!transformLayer_) {
        transformLayer_ = AceType::MakeRefPtr<Flutter::TransformLayer>(Matrix4::CreateIdentity(), 0.0, 0.0);
    }
    return AceType::RawPtr(transformLayer_);
}

void FlutterRenderSvgText::Paint(RenderContext& context, const Offset& offset)
{
    DrawOffset drawOffset = { offset, offset, false };
    DrawText(context, drawOffset);
}

void FlutterRenderSvgText::DrawText(RenderContext& context, DrawOffset& drawOffset)
{
    // update current offset by attribute
    UpdateDrawOffset(drawOffset);

    if (!textData_.empty()) {
        drawOffset.current = OnDrawText(context, drawOffset);
        drawOffset.isTspan = true;
    }

    const auto& children = GetChildren();
    if (!children.empty()) {
        for (const auto& child : children) {
            auto textSpan = AceType::DynamicCast<FlutterRenderSvgTspan>(child);
            if (textSpan) {
                textSpan->DrawText(context, drawOffset);
                continue;
            }

            auto textPath = AceType::DynamicCast<FlutterRenderSvgTextPath>(child);
            if (textPath) {
                drawOffset.current = textPath->PaintTextPath(context, drawOffset.svg);
                drawOffset.isTspan = true;
            }
        }
    }
}

Offset FlutterRenderSvgText::OnDrawText(RenderContext& context, const DrawOffset& drawOffset)
{
    Offset offset = drawOffset.current;
    const auto renderContext = static_cast<FlutterRenderContext*>(&context);
    flutter::Canvas* canvas = renderContext->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return offset;
    }
    SkCanvas* skCanvas = canvas->canvas();
    if (!skCanvas) {
        LOGE("Paint skCanvas is null");
        return offset;
    }

    std::string text = isDrawSpace_ ? " " + textData_ : textData_;
    SvgTextInfo svgTextInfo = { fillState_, strokeState_, textStyle_, text, opacity_ };
    TextDrawInfo textDrawInfo = { offset, rotate_ };
    offset = FlutterSvgPainter::UpdateText(skCanvas, svgTextInfo, textDrawInfo);
    return offset;
}

void FlutterRenderSvgText::UpdateDrawOffset(DrawOffset& drawOffset)
{
    double width = GetLayoutSize().Width();
    double height = GetLayoutSize().Height();
    double x = ConvertDimensionToPx(x_, width);
    double dx = ConvertDimensionToPx(dx_, width);
    double y = ConvertDimensionToPx(y_, height);
    double dy = ConvertDimensionToPx(dy_, height);
    drawOffset.current = drawOffset.current + Offset(x + dx, y + dy);
    drawOffset.isTspan = false;
}

} // namespace OHOS::Ace
