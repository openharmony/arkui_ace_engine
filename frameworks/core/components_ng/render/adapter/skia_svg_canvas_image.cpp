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

#include "core/components_ng/render/adapter/skia_svg_canvas_image.h"

#include "skia_adapter/skia_canvas.h"

#include "core/components_ng/image_provider/adapter/skia_svg_dom.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

void SkiaSvgCanvasImage::SetSVGDom(const RefPtr<SvgDom>& svgDom)
{
    svgDom_ = svgDom;
}

const RefPtr<SvgDom>& SkiaSvgCanvasImage::GetSVGDom() const
{
    return svgDom_;
}

void SkiaSvgCanvasImage::DrawToRSCanvas(RSCanvas& canvas, const RSRect& srcRect, const RSRect&  /*dstRect*/)
{
    CHECK_NULL_VOID(svgDom_);
    auto skiaSvgDom = DynamicCast<SkiaSvgDom>(svgDom_);
    CHECK_NULL_VOID(skiaSvgDom->GetSkiaSvgDom());
    auto rsCanvas = canvas.GetImpl<Rosen::Drawing::SkiaCanvas>();
    CHECK_NULL_VOID(rsCanvas);
    auto *skCanvas = rsCanvas->ExportSkCanvas();
    //TODO:use graphics_2d to paint SVG
    auto svgContainerSize = SizeF(srcRect.GetWidth(), srcRect.GetHeight());
    if (svgContainerSize.IsNegative()) {
        // when layout size is invalid, try the container size of svg
        if (skiaSvgDom->GetContainerSize().IsNegative()) {
            return;
        }
        svgContainerSize = skiaSvgDom->GetContainerSize();
    }
    //TODO:svg ObjectFit
    double width = svgContainerSize.Width();
    double height = svgContainerSize.Height();
    skiaSvgDom->SetContainerSize(svgContainerSize);
    skCanvas->clipRect({ 0, 0, width, height }, SkClipOp::kIntersect, true);
    skiaSvgDom->Render(skCanvas);
}

} // namespace OHOS::Ace::NG
