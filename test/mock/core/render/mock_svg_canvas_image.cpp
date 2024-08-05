/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {
const RefPtr<SvgDomBase>& SvgCanvasImage::GetSVGDom() const
{
    return nullptr;
}

void SvgCanvasImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& /* dstRect */, const BorderRadiusArray& /* radiusXY */)
{}

void SvgCanvasImage::DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) {}

void SvgCanvasImage::SetRedrawCallback(std::function<void()>&& callback) {}

void SvgCanvasImage::SetOnFinishCallback(std::function<void ()> &&callback) {}

void SvgCanvasImage::ControlAnimation(bool play) {}

bool SvgCanvasImage::IsStatic()
{
    return false;
}
} // namespace OHOS::Ace::NG
