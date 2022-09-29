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

#include "core/components_ng/image_provider/svg_image_object.h"

#include "core/components_ng/image_provider/adapter/skia_image_data.h"

namespace OHOS::Ace::NG {

const RefPtr<SvgDom>& SvgImageObject::GetSVGDom() const
{
    return svgDom_;
}

void SvgImageObject::MakeCanvasImage(
    const LoadCallbacks& loadCallbacks, const SizeF&  /*resizeTarget*/, bool  /*forceResize*/)
{
    ImageProvider::MakeCanvasImageForSVG(WeakClaim(this), loadCallbacks);
}

bool SvgImageObject::MakeSvgDom(const std::optional<Color>& svgFillColor)
{
    auto skiaImageData = DynamicCast<SkiaImageData>(data_);
    CHECK_NULL_RETURN(skiaImageData, false);
    // update SVGSkiaDom
    svgDom_ = skiaImageData->MakeSvgDom(svgFillColor);
    CHECK_NULL_RETURN(svgDom_, false);
    // get ImageSize
    SetImageSize(svgDom_->GetContainerSize());
    return true;
}

} // namespace OHOS::Ace::NG
