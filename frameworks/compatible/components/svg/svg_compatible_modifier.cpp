/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "compatible/components/svg/svg_compatible_modifier.h"

#include "compatible/components/svg/parse/svg_dom.h"
#include "compatible/components/svg/rosen_render_svg_pattern.h"

namespace OHOS::Ace::SvgCompatibleModifier {
namespace {

void SetSvgRenderTreeAndUpdateLayout(OHOS::Ace::PipelineContext* context, OHOS::Ace::SvgRenderTree* svgRenderTree,
    OHOS::Ace::ImageFit imageFit, OHOS::Ace::SvgRadius* svgRadius, bool directPaint)
{
    SvgDom svgDom(AceType::WeakClaim(context));
    svgDom.SetSvgRenderTree(*svgRenderTree);
    svgDom.UpdateLayout(imageFit, *svgRadius, directPaint);
}

OHOS::Ace::RefPtr<OHOS::Ace::SvgDom> CreateSvgDom(
    SkStream* svgStream, OHOS::Ace::PipelineContext* context, const OHOS::Ace::Color* svgThemeColor)
{
    std::optional<Color> themeColor = std::nullopt;
    if (svgThemeColor != nullptr) {
        themeColor = *svgThemeColor;
    }
    return SvgDom::CreateSvgDom(*svgStream, AceType::WeakClaim(context), themeColor);
}

OHOS::Ace::SvgRenderTree* CreateRenderTree(OHOS::Ace::RefPtr<OHOS::Ace::SvgDom> svg, OHOS::Ace::ImageFit imageFit,
    OHOS::Ace::SvgRadius* svgRadius, bool useBox)
{
    auto svgRenderTree = svg->CreateRenderTree(imageFit, *svgRadius, useBox);
    return new SvgRenderTree(std::move(svgRenderTree));
}

void PaintDirectly(OHOS::Ace::RefPtr<OHOS::Ace::SvgDom> svg, OHOS::Ace::RenderContext* context,
    const OHOS::Ace::Offset* offset, OHOS::Ace::ImageFit imageFit, OHOS::Ace::Size* layout)
{
    svg->PaintDirectly(*context, *offset, imageFit, *layout);
}

OHOS::Ace::RefPtr<OHOS::Ace::RosenRenderSvgPattern> GetPatternFromRoot(
    OHOS::Ace::RefPtr<OHOS::Ace::RenderSvgBase> node, const char* id)
{
    return AceType::DynamicCast<RosenRenderSvgPattern>(node->GetPatternFromRoot(id));
}

bool OnAsPaint(OHOS::Ace::RefPtr<OHOS::Ace::RosenRenderSvgPattern> pattern, const OHOS::Ace::Offset* offset,
    const OHOS::Ace::Rect* paintRect, OHOS::Ace::RSPen* rsPen, OHOS::Ace::RSBrush* rsBrush)
{
    return pattern->OnAsPaint(*offset, *paintRect, rsPen, rsBrush);
}

} // namespace
const ArkUISvgCompatibleModifier* GetSvgCompatibleModifier()
{
    static const ArkUISvgCompatibleModifier instance = {
        .setSvgRenderTreeAndUpdateLayout = SetSvgRenderTreeAndUpdateLayout,
        .createSvgDom = CreateSvgDom,
        .createRenderTree = CreateRenderTree,
        .paintDirectly = PaintDirectly,
        .getPatternFromRoot = GetPatternFromRoot,
        .onAsPaint = OnAsPaint,
    };
    return &instance;
}
} // namespace OHOS::Ace::SvgCompatibleModifier