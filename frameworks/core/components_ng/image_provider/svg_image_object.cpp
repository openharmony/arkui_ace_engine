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

#include "core/components_ng/image_provider/svg_image_object.h"

#include "core/components_ng/render/canvas_image.h"

#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#else
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#endif
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/render/adapter/svg_canvas_image.h"

namespace OHOS::Ace::NG {
RefPtr<SvgImageObject> SvgImageObject::Create(const ImageSourceInfo& src, const RefPtr<ImageData>& data)
{
    auto obj = AceType::MakeRefPtr<SvgImageObject>(src, SizeF(), data);
    if (!obj->MakeSvgDom(data, src)) {
        return nullptr;
    }
    return obj;
}

RefPtr<SvgDomBase> SvgImageObject::GetSVGDom() const
{
    return svgDomBase_;
}

void SvgImageObject::MakeCanvasImage(
    const RefPtr<ImageLoadingContext>& ctx, const SizeF& resizeTarget, bool /*forceResize*/, bool /*syncLoad*/)
{
    auto src = GetSourceInfo();
    auto key = ImageUtils::GenerateImageKey(src, resizeTarget);

    if (!svgImageData_) {
        ctx->FailCallback("svgImageData is null when SvgImageObject try MakeSvgDom");
        return;
    }
    auto svgDomBase = MakeSvgDom(svgImageData_, src);
    if (!svgDomBase) {
        ctx->FailCallback("MakeSvgDom failed");
        return;
    }
    auto canvasImage = MakeRefPtr<SvgCanvasImage>(svgDomBase);
    ctx->SuccessCallback(canvasImage);
}

RefPtr<SvgDomBase> SvgImageObject::MakeSvgDom(const RefPtr<ImageData>& data, const ImageSourceInfo& src)
{
    RefPtr<SvgDomBase> svgDomBase;
#ifndef USE_ROSEN_DRAWING
    auto skiaImageData = DynamicCast<SkiaImageData>(data);
    CHECK_NULL_RETURN(skiaImageData, nullptr);
    svgDomBase = skiaImageData->MakeSvgDom(src.GetFillColor());
#else
    auto rosenImageData = DynamicCast<DrawingImageData>(data);
    CHECK_NULL_RETURN(rosenImageData, nullptr);
    // update SVGSkiaDom
    svgDomBase = rosenImageData->MakeSvgDom(src);
#endif
    CHECK_NULL_RETURN(svgDomBase, nullptr);
    imageSize_ = svgDomBase->GetContainerSize();

    if (imageSize_.IsNonPositive()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE,
            "[Engine Log] [Image] %{public}s doesn't have an intrinsic size. The developer must set a size for it.",
            GetSourceInfo().ToString().c_str());
    }
    return svgDomBase;
}

const RefPtr<ImageData>& SvgImageObject::GetSvgImageData() const
{
    return svgImageData_;
}
} // namespace OHOS::Ace::NG
