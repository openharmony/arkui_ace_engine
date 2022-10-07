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

#include "core/components_ng/render/adapter/svg_canvas_image.h"

#include "utils/rect.h"

namespace OHOS::Ace::NG {

void SvgCanvasImage::SetSVGDom(const RefPtr<SvgDomBase>& svgDom)
{
    svgDom_ = svgDom;
}

const RefPtr<SvgDomBase>& SvgCanvasImage::GetSVGDom() const
{
    return svgDom_;
}

void SvgCanvasImage::SetSvgImageFit(const ImageFit& imageFit)
{
    imageFit_ = imageFit;
}

void SvgCanvasImage::SetSvgFillColor(const std::optional<Color>& color)
{
    color_ = color;
}

void SvgCanvasImage::DrawToRSCanvas(RSCanvas& canvas, const RSRect& srcRect, const RSRect&  /*dstRect*/)
{
    CHECK_NULL_VOID(svgDom_);
    svgDom_->DrawImage(canvas, imageFit_, Size(srcRect.GetWidth(), srcRect.GetHeight()), color_);
}

} // namespace OHOS::Ace::NG
