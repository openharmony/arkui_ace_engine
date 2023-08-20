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

#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"

#include "include/codec/SkCodec.h"
#include "include/core/SkGraphics.h"

#include "drawing/engine_adapter/skia_adapter/skia_data.h"

#include "base/utils/system_properties.h"
#include "core/components_ng/image_provider/adapter/skia_svg_dom.h"
#include "core/components_ng/svg/svg_dom.h"

namespace OHOS::Ace::NG {
DrawingImageData::DrawingImageData(const void* data, size_t length)
{
    rsData_ = std::make_shared<RSData>();
    rsData_->BuildWithCopy(data, length);
}

RefPtr<ImageData> ImageData::MakeFromDataWithCopy(const void* data, size_t length)
{
    return MakeRefPtr<DrawingImageData>(data, length);
}

RefPtr<ImageData> ImageData::MakeFromDataWrapper(void* dataWrapper)
{
    std::shared_ptr<RSData>* rsDataPtr = reinterpret_cast<std::shared_ptr<RSData>*>(dataWrapper);
    CHECK_NULL_RETURN_NOLOG(rsDataPtr, nullptr);
    CHECK_NULL_RETURN_NOLOG(*rsDataPtr, nullptr);
    return MakeRefPtr<DrawingImageData>(*rsDataPtr);
}

size_t DrawingImageData::GetSize() const
{
    CHECK_NULL_RETURN(rsData_, 0);
    return rsData_->GetSize();
}

const void* DrawingImageData::GetData() const
{
    CHECK_NULL_RETURN(rsData_, nullptr);
    return rsData_->GetData();
}

std::shared_ptr<RSData> DrawingImageData::GetRSData() const
{
    CHECK_NULL_RETURN(rsData_, nullptr);
    return rsData_;
}

RefPtr<SvgDomBase> DrawingImageData::MakeSvgDom(const std::optional<Color>& svgFillColor)
{
    CHECK_NULL_RETURN(rsData_, nullptr);
    auto skData = rsData_->GetImpl<Rosen::Drawing::SkiaData>()->GetSkData();
    const auto svgStream = std::make_unique<SkMemoryStream>(skData);
    CHECK_NULL_RETURN(svgStream, nullptr);
    if (SystemProperties::GetSvgMode() <= 0) {
        return SkiaSvgDom::CreateSkiaSvgDom(*svgStream, svgFillColor);
    }
#ifdef NG_BUILD
    LOGE("NG SvgDom not support!");
    return nullptr;
#else
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
#endif
}

std::pair<SizeF, int32_t> DrawingImageData::Parse() const
{
    CHECK_NULL_RETURN(GetRSData(), {});
    auto skData = GetRSData()->GetImpl<Rosen::Drawing::SkiaData>()->GetSkData();
    auto codec = SkCodec::MakeFromData(skData);
    CHECK_NULL_RETURN_NOLOG(codec, {});
    SizeF imageSize;
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
} // namespace OHOS::Ace::NG
