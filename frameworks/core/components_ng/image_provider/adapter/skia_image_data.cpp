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

#include "core/components_ng/image_provider/adapter/skia_image_data.h"

#include "include/codec/SkCodec.h"
#include "include/core/SkGraphics.h"

#include "base/image/image_source.h"
#include "base/utils/system_properties.h"
#include "core/components_ng/image_provider/adapter/skia_svg_dom.h"
#include "core/components_ng/svg/svg_dom.h"

namespace OHOS::Ace::NG {
constexpr int32_t ASTC_FRAME_COUNT = 1;

SkiaImageData::SkiaImageData(const void* data, size_t length)
{
    // [SkData::MakeWithCopy] will not return nullptr
    skData_ = SkData::MakeWithCopy(data, length);
}

RefPtr<ImageData> ImageData::MakeFromDataWithCopy(const void* data, size_t length)
{
    return MakeRefPtr<SkiaImageData>(data, length);
}

RefPtr<ImageData> ImageData::MakeFromDataWrapper(void* dataWrapper)
{
    auto* skDataPtr = reinterpret_cast<sk_sp<SkData>*>(dataWrapper);
    CHECK_NULL_RETURN(skDataPtr && *skDataPtr, nullptr);
    return MakeRefPtr<SkiaImageData>(*skDataPtr);
}

size_t SkiaImageData::GetSize() const
{
    CHECK_NULL_RETURN(skData_, 0);
    return skData_->size();
}

const void* SkiaImageData::GetData() const
{
    CHECK_NULL_RETURN(skData_, nullptr);
    return skData_->data();
}

sk_sp<SkData> SkiaImageData::GetSkData() const
{
    CHECK_NULL_RETURN(skData_, nullptr);
    return skData_;
}

RefPtr<SvgDomBase> SkiaImageData::MakeSvgDom(const std::optional<Color>& svgFillColor)
{
    const auto svgStream = std::make_unique<SkMemoryStream>(skData_);
    CHECK_NULL_RETURN(svgStream, nullptr);
    if (SystemProperties::GetSvgMode() <= 0) {
        return SkiaSvgDom::CreateSkiaSvgDom(*svgStream, svgFillColor);
    }
    auto svgDom_ = SvgDom::CreateSvgDom(*svgStream, svgFillColor);
    if (!svgDom_) {
        return nullptr;
    }
    svgDom_->SetFuncNormalizeToPx(
        [pipeline = WeakPtr(PipelineContext::GetCurrentContext())](const Dimension& value) -> double {
            auto context = pipeline.Upgrade();
            CHECK_NULL_RETURN(context, 0.0);
            return context->NormalizeToPx(value);
        });
    return svgDom_;
}

std::pair<SizeF, int32_t> SkiaImageData::Parse() const
{
    SizeF imageSize;
    if (ImageSource::IsAstc(GetSkData()->bytes(), GetSkData()->size())) {
        ImageSource::Size astcSize = ImageSource::GetASTCInfo(GetSkData()->bytes(), GetSkData()->size());
        imageSize.SetSizeT(SizeF(astcSize.first, astcSize.second));
        return { imageSize, ASTC_FRAME_COUNT };
    }

    auto codec = SkCodec::MakeFromData(GetSkData());
    CHECK_NULL_RETURN(codec, {});
    switch (codec->getOrigin()) {
        case SkEncodedOrigin::kLeftTop_SkEncodedOrigin:
        case SkEncodedOrigin::kRightTop_SkEncodedOrigin:
        case SkEncodedOrigin::kRightBottom_SkEncodedOrigin:
        case SkEncodedOrigin::kLeftBottom_SkEncodedOrigin:
            imageSize.SetSizeT(SizeF(codec->dimensions().fHeight, codec->dimensions().fWidth));
            break;
        default:
            imageSize.SetSizeT(SizeF(codec->dimensions().fWidth, codec->dimensions().fHeight));
    }
    return { imageSize, codec->getFrameCount() };
}

const void* SkiaImageData::GetDataWrapper() const
{
    return &skData_;
}

std::string SkiaImageData::ToString() const
{
    return "SkiaImageData Size" + std::to_string(skData_->size()) + "(B)";
}
} // namespace OHOS::Ace::NG
