/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components/image/image_component.h"
#include "core/interfaces/native/implementation/image_attachment_peer.h"
#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/implementation/drawing_color_filter_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace {
const std::vector<float> DEFAULT_COLORFILTER_MATRIX = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
}
namespace GeneratedModifier {
const GENERATED_ArkUIColorFilterAccessor* GetColorFilterAccessor();
} // namespace GeneratedModifier
namespace Converter {

template<>
ImageSpanAttribute Convert(const Ark_ImageAttachmentLayoutStyle& value)
{
    ImageSpanAttribute imageStyle;
    imageStyle.marginProp = OptConvert<MarginProperty>(value.margin);
    imageStyle.paddingProp = OptConvert<MarginProperty>(value.padding);
    imageStyle.borderRadius = OptConvert<BorderRadiusProperty>(value.borderRadius);
    return imageStyle;
}

template<>
RefPtr<ImageSpan> Convert(const Ark_ImageAttachmentInterface& value)
{
    ImageSpanOptions imageOptions;
#if defined(PIXEL_MAP_SUPPORTED) || defined(PIXEL_MAP_TEST_SUPPORTED)
    auto container = Container::CurrentSafely();
    auto context = PipelineBase::GetCurrentContextSafely();
    if (container && context) {
        bool isCard = context->IsFormRender() && !container->IsDynamicRender();
        auto pixelMapPeer = value.value;
        if (pixelMapPeer && !isCard) {
            imageOptions.imagePixelMap = pixelMapPeer->pixelMap;
        }
    }
#endif
    auto imageStyle = OptConvert<ImageSpanAttribute>(value.layoutStyle).value_or(ImageSpanAttribute());
    imageStyle.verticalAlign = OptConvert<VerticalAlign>(value.verticalAlign).value_or(VerticalAlign::BOTTOM);
    imageStyle.objectFit = OptConvert<ImageFit>(value.objectFit).value_or(ImageFit::COVER);
    imageStyle.size = OptConvert<ImageSpanSize>(value.size);
    std::optional<Ark_ColorFilterType> colorFilter = GetOpt(value.colorFilter);
    if (colorFilter) {
        Converter::VisitUnion(
            *colorFilter,
            [&imageStyle](const Ark_ColorFilter& filter) {
                if (filter && filter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
                    imageStyle.colorFilterMatrix = filter->GetColorFilterMatrix();
                }
            },
            [&imageStyle](const Ark_drawing_ColorFilter& colorStrategy) {
                CHECK_NULL_VOID(colorStrategy);
                imageStyle.drawingColorFilter = colorStrategy->drawingColorFilter;
                drawing_ColorFilterPeer::Destroy(colorStrategy);
            },
            []() {
            });
    } else {
        imageStyle.colorFilterMatrix = DEFAULT_COLORFILTER_MATRIX;
        imageStyle.drawingColorFilter = std::nullopt;
    }
    imageOptions.imageAttribute = imageStyle;
    return AceType::MakeRefPtr<ImageSpan>(imageOptions);
}

template<>
RefPtr<ImageSpan> Convert(const Ark_ResourceImageAttachmentOptions& value)
{
    ImageSpanOptions imageOptions;
    auto resourceStrOpt = Converter::OptConvert<Converter::Ark_Resource_Simple>(value.resourceValue);
    if (resourceStrOpt.has_value()) {
        imageOptions.bundleName = resourceStrOpt->bundleName;
        imageOptions.moduleName = resourceStrOpt->moduleName;
        imageOptions.image = resourceStrOpt->content;
    }
    auto imageStyle = OptConvert<ImageSpanAttribute>(value.layoutStyle).value_or(ImageSpanAttribute());
    imageStyle.verticalAlign = OptConvert<VerticalAlign>(value.verticalAlign).value_or(VerticalAlign::BOTTOM);
    imageStyle.objectFit = OptConvert<ImageFit>(value.objectFit).value_or(ImageFit::COVER);
    imageStyle.size = OptConvert<ImageSpanSize>(value.size);
    std::optional<Ark_ColorFilterType> colorFilter = GetOpt(value.colorFilter);
    if (colorFilter) {
        Converter::VisitUnion(
            *colorFilter,
            [&imageStyle](const Ark_ColorFilter& filter) {
                if (filter && filter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
                    imageStyle.colorFilterMatrix = filter->GetColorFilterMatrix();
                }
            },
            [&imageStyle](const Ark_drawing_ColorFilter& colorStrategy) {
                CHECK_NULL_VOID(colorStrategy);
                imageStyle.drawingColorFilter = colorStrategy->drawingColorFilter;
                drawing_ColorFilterPeer::Destroy(colorStrategy);
            },
            []() {
            });
    } else {
        imageStyle.colorFilterMatrix = DEFAULT_COLORFILTER_MATRIX;
        imageStyle.drawingColorFilter = std::nullopt;
    }
    imageOptions.imageAttribute = imageStyle;
    return AceType::MakeRefPtr<ImageSpan>(imageOptions);
}

Opt_Length OptValueFromOptDimension(const std::optional<Dimension>& src)
{
    if (!src.has_value()) {
        Opt_Length dst;
        dst.tag = INTEROP_TAG_UNDEFINED;
        return dst;
    }
    return ArkValue<Opt_Length>(src->ConvertToVp());
}

Ark_BorderRadiuses ArkValueFromOptBorderRadius(const OHOS::Ace::NG::BorderRadiusProperty& src)
{
    Ark_BorderRadiuses arkBorder = {
        .topLeft = OptValueFromOptDimension(src.radiusTopLeft),
        .topRight = OptValueFromOptDimension(src.radiusTopRight),
        .bottomLeft = OptValueFromOptDimension(src.radiusBottomLeft),
        .bottomRight = OptValueFromOptDimension(src.radiusBottomRight),
    };
    return arkBorder;
}

void AssignArkValue(Ark_ImageAttachmentLayoutStyle& dst, const ImageSpanAttribute& src, ConvContext *ctx)
{
    dst.margin = ArkUnion<Opt_Union_LengthMetrics_Margin, Ark_Padding>(src.marginProp, ctx);
    dst.padding = ArkUnion<Opt_Union_LengthMetrics_Padding, Ark_Padding>(src.paddingProp, ctx);
    if (src.borderRadius) {
        dst.borderRadius = ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses, Ark_BorderRadiuses>(
            ArkValueFromOptBorderRadius(src.borderRadius.value()));
    } else {
        dst.borderRadius =  ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses>(Ark_Empty());
    }
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageAttachmentAccessor {
using namespace Converter;
void DestroyPeerImpl(Ark_ImageAttachment peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ImageAttachment ConstructImpl(const Opt_AttachmentType* value)
{
    auto peer = PeerUtils::CreatePeer<ImageAttachmentPeer>();
    CHECK_NULL_RETURN(value, peer);
    auto imageSpan = OptConvert<RefPtr<ImageSpan>>(*value);
    CHECK_NULL_RETURN(imageSpan, peer);
    peer->span = *imageSpan;
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_image_PixelMap GetValueImpl(Ark_ImageAttachment peer)
{
#if defined(PIXEL_MAP_SUPPORTED) || defined(PIXEL_MAP_TEST_SUPPORTED)
    auto arkPixelMap = PeerUtils::CreatePeer<image_PixelMapPeer>();
    CHECK_NULL_RETURN(peer && peer->span, arkPixelMap);
    auto pixelMap = peer->span->GetImageSpanOptions().imagePixelMap;
    CHECK_NULL_RETURN(pixelMap, arkPixelMap);
    arkPixelMap->pixelMap = *pixelMap;
    return arkPixelMap;
#else
    LOGE("ARKOALA ImageAttachmentAccessor::GetPixelMapImpl PixelMap is not supported on current platform.");
    return nullptr;
#endif
}
Opt_String GetResourceValueImpl(Ark_ImageAttachment peer)
{
    auto invalid = Converter::ArkValue<Opt_String>();
    CHECK_NULL_RETURN(peer && peer->span, invalid);
    auto image = peer->span->GetImageSpanOptions().image;
    CHECK_NULL_RETURN(image, invalid);
    return Converter::ArkValue<Opt_String>(image.value());
}
Opt_SizeOptions GetSizeImpl(Ark_ImageAttachment peer)
{
    auto invalid = Converter::ArkValue<Opt_SizeOptions>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    CHECK_NULL_RETURN(peer->span->GetImageAttribute(), invalid);
    CHECK_NULL_RETURN(peer->span->GetImageAttribute()->size, invalid);
    Ark_SizeOptions size;
    size.width = ArkValue<Opt_Length>(peer->span->GetImageAttribute()->size->width, Converter::FC);
    size.height = ArkValue<Opt_Length>(peer->span->GetImageAttribute()->size->height, Converter::FC);
    return Converter::ArkValue<Opt_SizeOptions>(size);
}
Opt_ImageSpanAlignment GetVerticalAlignImpl(Ark_ImageAttachment peer)
{
    auto invalid = Converter::ArkValue<Opt_ImageSpanAlignment>();
    CHECK_NULL_RETURN(
        peer && peer->span && peer->span->GetImageAttribute(), invalid);
    auto alignment = peer->span->GetImageAttribute()->verticalAlign;
    return ArkValue<Opt_ImageSpanAlignment>(alignment);
}
Opt_ImageFit GetObjectFitImpl(Ark_ImageAttachment peer)
{
    auto invalid = Converter::ArkValue<Opt_ImageFit>();
    CHECK_NULL_RETURN(peer && peer->span && peer->span->GetImageAttribute(), invalid);
    auto objectFit = peer->span->GetImageAttribute()->objectFit;
    return ArkValue<Opt_ImageFit>(objectFit);
}
Opt_ImageAttachmentLayoutStyle GetLayoutStyleImpl(Ark_ImageAttachment peer)
{
    auto invalid = Converter::ArkValue<Opt_ImageAttachmentLayoutStyle>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    return ArkValue<Opt_ImageAttachmentLayoutStyle>(peer->span->GetImageAttribute(), Converter::FC);
}
Opt_ColorFilterType GetColorFilterImpl(Ark_ImageAttachment peer)
{
    auto empty = Converter::ArkValue<Opt_ColorFilterType>();
    CHECK_NULL_RETURN(peer, empty);
    CHECK_NULL_RETURN(peer->span, empty);
    CHECK_NULL_RETURN(peer->span->GetImageAttribute(), empty);
    CHECK_NULL_RETURN(peer->span->GetImageAttribute()->colorFilterMatrix ||
        peer->span->GetImageAttribute()->drawingColorFilter, empty);
    if (peer->span->GetImageAttribute()->colorFilterMatrix) {
        auto& colorFilter = peer->span->GetImageAttribute()->colorFilterMatrix.value();
        ArkArrayHolder<Array_Float64> colorFilterHolder(colorFilter);
        auto arrayNumber = ArkValue<Array_Float64>(colorFilterHolder.ArkValue());
        auto colorFilterPeer = GeneratedModifier::GetColorFilterAccessor()->construct(&arrayNumber);
        return ArkUnion<Opt_ColorFilterType, Ark_ColorFilter>(colorFilterPeer);
    } else {
        LOGE("Arkoala: ImageAttachmentAccessor.GetColorFilter: DrawinColorFilter doesn't supported");
    }
    return empty;
}
} // ImageAttachmentAccessor
const GENERATED_ArkUIImageAttachmentAccessor* GetImageAttachmentAccessor()
{
    static const GENERATED_ArkUIImageAttachmentAccessor ImageAttachmentAccessorImpl {
        ImageAttachmentAccessor::DestroyPeerImpl,
        ImageAttachmentAccessor::ConstructImpl,
        ImageAttachmentAccessor::GetFinalizerImpl,
        ImageAttachmentAccessor::GetValueImpl,
        ImageAttachmentAccessor::GetResourceValueImpl,
        ImageAttachmentAccessor::GetSizeImpl,
        ImageAttachmentAccessor::GetVerticalAlignImpl,
        ImageAttachmentAccessor::GetObjectFitImpl,
        ImageAttachmentAccessor::GetLayoutStyleImpl,
        ImageAttachmentAccessor::GetColorFilterImpl,
    };
    return &ImageAttachmentAccessorImpl;
}

}
