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

#include "core/components_ng/image_provider/drawing_image_data.h"

#include "include/codec/SkCodec.h"
#ifdef USE_NEW_SKIA
#include "include/core/SkStream.h"
#endif

#include "base/image/image_source.h"
#include "core/components_ng/svg/svg_dom.h"

namespace OHOS::Ace::NG {
namespace {
struct RSDataWrapper {
    std::shared_ptr<RSData> data;
};

inline void RSDataWrapperReleaseProc(const void*, void* context)
{
    RSDataWrapper* wrapper = reinterpret_cast<RSDataWrapper*>(context);
    delete wrapper;
}
} // namespace

constexpr int32_t ASTC_FRAME_COUNT = 1;
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
    CHECK_NULL_RETURN(rsDataPtr, nullptr);
    CHECK_NULL_RETURN(*rsDataPtr, nullptr);
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

RefPtr<SvgDomBase> DrawingImageData::MakeSvgDom(const ImageSourceInfo& src)
{
    CHECK_NULL_RETURN(rsData_, nullptr);
    RSDataWrapper* wrapper = new RSDataWrapper { rsData_ };
    auto skData = SkData::MakeWithProc(rsData_->GetData(), rsData_->GetSize(), RSDataWrapperReleaseProc, wrapper);
    if (!skData) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "skData is null, %{public}d-%{public}d-%{public}lld.",
            static_cast<int32_t>(rsData_->GetSize()), nodeId_, static_cast<long long>(accessibilityId_));
        return nullptr;
    }
    const auto svgStream = std::make_unique<SkMemoryStream>(skData);
    if (!svgStream) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "svgStream is null, %{public}d-%{public}d-%{public}lld.",
            static_cast<int32_t>(rsData_->GetSize()), nodeId_, static_cast<long long>(accessibilityId_));
        return nullptr;
    }
    auto svgDom_ = SvgDom::CreateSvgDom(*svgStream, src);
    if (!svgDom_) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "svgDom is null, %{public}d-%{public}d-%{public}lld.",
            static_cast<int32_t>(rsData_->GetSize()), nodeId_, static_cast<long long>(accessibilityId_));
        return nullptr;
    }
    svgDom_->SetFuncNormalizeToPx(
        [pipeline = WeakPtr(PipelineContext::GetCurrentContext())](const Dimension& value) -> double {
            auto context = pipeline.Upgrade();
            if (!context) {
                TAG_LOGW(AceLogTag::ACE_IMAGE, "SVG value missing, null pipeline.");
                return 0.0;
            }
            return context->NormalizeToPx(value);
        });
    return svgDom_;
}

ImageRotateOrientation GetImageRotateOrientation(SkEncodedOrigin origin)
{
    switch (origin) {
        case SkEncodedOrigin::kTopRight_SkEncodedOrigin:
            return ImageRotateOrientation::UP_MIRRORED;
        case SkEncodedOrigin::kBottomRight_SkEncodedOrigin:
            // Rotated 180
            return ImageRotateOrientation::DOWN;
        case SkEncodedOrigin::kBottomLeft_SkEncodedOrigin:
            return ImageRotateOrientation::DOWN_MIRRORED;
        case SkEncodedOrigin::kLeftTop_SkEncodedOrigin:
            // Reflected across x-axis, Rotated 90 CCW
            return ImageRotateOrientation::LEFT_MIRRORED;
        case SkEncodedOrigin::kRightTop_SkEncodedOrigin:
            // Rotated 90 CW
            return ImageRotateOrientation::RIGHT;
        case SkEncodedOrigin::kRightBottom_SkEncodedOrigin:
            // Reflected across x-axis, Rotated 90 CW
            return ImageRotateOrientation::RIGHT_MIRRORED;
        case SkEncodedOrigin::kLeftBottom_SkEncodedOrigin:
            // Rotated 90 CCW
            return ImageRotateOrientation::LEFT;
        case SkEncodedOrigin::kTopLeft_SkEncodedOrigin:
            return ImageRotateOrientation::UP;
        default:
            return ImageRotateOrientation::UP;
    }
}

ImageCodec DrawingImageData::Parse() const
{
    auto rsData = GetRSData();
    CHECK_NULL_RETURN(rsData, {});
    SizeF imageSize;
    if (ImageSource::IsAstc(static_cast<const uint8_t*>(rsData->GetData()), rsData->GetSize())) {
        ImageSource::Size astcSize =
            ImageSource::GetASTCInfo(static_cast<const uint8_t*>(rsData->GetData()), rsData->GetSize());
        imageSize.SetSizeT(SizeF(astcSize.first, astcSize.second));
        return { imageSize, ASTC_FRAME_COUNT, ImageRotateOrientation::UP };
    }

    RSDataWrapper* wrapper = new RSDataWrapper { rsData };
    auto skData = SkData::MakeWithProc(rsData->GetData(), rsData->GetSize(), RSDataWrapperReleaseProc, wrapper);
    if (!skData) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "skData in Parse is null, rsDataSize = %{public}d, nodeID = %{public}d-%{public}lld.",
            static_cast<int32_t>(rsData->GetSize()), nodeId_, static_cast<long long>(accessibilityId_));
        return {};
    }
    auto codec = SkCodec::MakeFromData(skData);
    if (!codec) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "codec in Parse is null, rsDataSize = %{public}d, nodeID = %{public}d-%{public}lld.",
            static_cast<int32_t>(rsData->GetSize()), nodeId_, static_cast<long long>(accessibilityId_));
        return {};
    }
    auto orientation = GetImageRotateOrientation(codec->getOrigin());
    imageSize.SetSizeT(SizeF(codec->dimensions().fWidth, codec->dimensions().fHeight));
    return { imageSize, codec->getFrameCount(), orientation };
}

std::string DrawingImageData::ToString() const
{
    return "DrawingImageData Size" + std::to_string(rsData_->GetSize()) + "(B)";
}
} // namespace OHOS::Ace::NG
