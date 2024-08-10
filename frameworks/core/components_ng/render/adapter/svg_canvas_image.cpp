/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
const RefPtr<SvgDomBase>& SvgCanvasImage::GetSVGDom() const
{
    return svgDom_;
}

void SvgCanvasImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& /* dstRect */, const BorderRadiusArray& radiusXY)
{
    CHECK_NULL_VOID(svgDom_);
    svgDom_->SetRadius(radiusXY);
    svgDom_->DrawImage(canvas, GetPaintConfig().imageFit_, Size(srcRect.GetWidth(), srcRect.GetHeight()));
}

void SvgCanvasImage::DrawRect(RSCanvas& canvas, const RSRect& /* srcRect */, const RSRect& dstRect)
{
    OffsetF offset(dstRect.GetLeft(), dstRect.GetTop());
    SizeF contentSize(dstRect.GetWidth(), dstRect.GetHeight());
    auto clipRect = RSRect(0, 0, dstRect.GetWidth(), dstRect.GetHeight());
    canvas.Save();
    canvas.Translate(dstRect.GetLeft(), dstRect.GetTop());
    canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    DrawToRSCanvas(canvas, dstRect, dstRect, BorderRadiusArray());
    canvas.Restore();
}

bool SvgCanvasImage::IsStatic()
{
    CHECK_NULL_RETURN(svgDom_, true);
    return svgDom_->IsStatic();
}

void SvgCanvasImage::SetRedrawCallback(std::function<void()>&& callback)
{
    svgDom_->SetAnimationCallback(std::move(callback), WeakClaim(this));
}

void SvgCanvasImage::SetOnFinishCallback(std::function<void()>&& callback)
{
    svgDom_->SetAnimationOnFinishCallback(callback);
}

void SvgCanvasImage::ControlAnimation(bool play)
{
    svgDom_->ControlAnimation(play);
}
} // namespace OHOS::Ace::NG
