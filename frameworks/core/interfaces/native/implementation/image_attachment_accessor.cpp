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
#include "core/interfaces/native/implementation/image_attachment_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace GeneratedModifier {
const GENERATED_ArkUIPixelMapAccessor* GetPixelMapAccessor();
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
    imageStyle.verticalAlign = OptConvert<VerticalAlign>(value.verticalAlign);
    imageStyle.objectFit = OptConvert<ImageFit>(value.objectFit);
    imageStyle.size = OptConvert<ImageSpanSize>(value.size);
    imageOptions.imageAttribute = imageStyle;
    return AceType::MakeRefPtr<ImageSpan>(imageOptions);
}

void AssignArkValue(Ark_ImageAttachmentLayoutStyle& dst, const ImageSpanAttribute& src)
{
    Ark_ImageAttachmentLayoutStyle style = {
        .margin = ArkUnion<Opt_Union_LengthMetrics_Margin>(Ark_Empty()),
        .padding = ArkUnion<Opt_Union_LengthMetrics_Padding>(Ark_Empty()),
        .borderRadius = ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses>(Ark_Empty()),
    };
    if (src.marginProp) {
        auto arkMargin = ArkValue<Ark_Padding>(*(src.marginProp));
        style.margin = ArkUnion<Opt_Union_LengthMetrics_Margin, Ark_Padding>(arkMargin);
    }
    if (src.paddingProp) {
        auto arkPadding = ArkValue<Ark_Padding>(*(src.paddingProp));
        style.padding = ArkUnion<Opt_Union_LengthMetrics_Padding, Ark_Padding>(arkPadding);
    }
    if (src.borderRadius) {
        auto arkBorder = ArkValue<Ark_BorderRadiuses>(*src.borderRadius);
        style.borderRadius = ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses, Ark_BorderRadiuses>(arkBorder);
    }
    dst = style;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageAttachmentAccessor {
using namespace Converter;
void DestroyPeerImpl(Ark_ImageAttachment peer)
{
    CHECK_NULL_VOID(peer);
    peer->imageSpan = nullptr;
    delete peer;
}
Ark_ImageAttachment CtorImpl(const Ark_ImageAttachmentInterface* value)
{
    auto peer = new ImageAttachmentPeer();
    CHECK_NULL_RETURN(value, peer);
    auto imageSpan = OptConvert<RefPtr<ImageSpan>>(*value);
    CHECK_NULL_RETURN(imageSpan, peer);
    peer->imageSpan = *imageSpan;
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_PixelMap GetValueImpl(Ark_ImageAttachment peer)
{
#if defined(PIXEL_MAP_SUPPORTED) || defined(PIXEL_MAP_TEST_SUPPORTED)
    auto arkPixelMap = GetPixelMapAccessor()->ctor();
    CHECK_NULL_RETURN(peer && peer->imageSpan, arkPixelMap);
    auto pixelMap = peer->imageSpan->GetImageSpanOptions().imagePixelMap;
    CHECK_NULL_RETURN(pixelMap, arkPixelMap);
    arkPixelMap->pixelMap = *pixelMap;
    return arkPixelMap;
#else
    LOGE("ARKOALA ImageAttachmentAccessor::GetPixelMapImpl PixelMap is not supported on current platform.");
    return nullptr;
#endif
}
Ark_SizeOptions GetSizeImpl(Ark_ImageAttachment peer)
{
    Ark_SizeOptions size = {
        .width = ArkValue<Opt_Length>(),
        .height = ArkValue<Opt_Length>(),
    };
    CHECK_NULL_RETURN(peer, size);
    CHECK_NULL_RETURN(peer->imageSpan, size);
    CHECK_NULL_RETURN(peer->imageSpan->GetImageAttribute(), size);
    CHECK_NULL_RETURN(peer->imageSpan->GetImageAttribute()->size, size);
    if (peer->imageSpan->GetImageAttribute()->size->width) {
        size.width = ArkValue<Opt_Length>(*peer->imageSpan->GetImageAttribute()->size->width);
    }
    if (peer->imageSpan->GetImageAttribute()->size->height) {
        size.height = ArkValue<Opt_Length>(*peer->imageSpan->GetImageAttribute()->size->height);
    }
    return size;
}
Ark_ImageSpanAlignment GetVerticalAlignImpl(Ark_ImageAttachment peer)
{
    CHECK_NULL_RETURN(
        peer && peer->imageSpan && peer->imageSpan->GetImageAttribute(), INVALID_ENUM_VAL<Ark_ImageSpanAlignment>);
    auto aligment = peer->imageSpan->GetImageAttribute()->verticalAlign;
    CHECK_NULL_RETURN(aligment, INVALID_ENUM_VAL<Ark_ImageSpanAlignment>);
    return ArkValue<Ark_ImageSpanAlignment>(*aligment);
}
Ark_ImageFit GetObjectFitImpl(Ark_ImageAttachment peer)
{
    CHECK_NULL_RETURN(peer && peer->imageSpan && peer->imageSpan->GetImageAttribute(), INVALID_ENUM_VAL<Ark_ImageFit>);
    auto objectFit = peer->imageSpan->GetImageAttribute()->objectFit;
    CHECK_NULL_RETURN(objectFit, INVALID_ENUM_VAL<Ark_ImageFit>);
    return ArkValue<Ark_ImageFit>(*objectFit);
}
Ark_ImageAttachmentLayoutStyle GetLayoutStyleImpl(Ark_ImageAttachment peer)
{
    Ark_ImageAttachmentLayoutStyle style = {
        .margin = ArkUnion<Opt_Union_LengthMetrics_Margin>(Ark_Empty()),
        .padding = ArkUnion<Opt_Union_LengthMetrics_Padding>(Ark_Empty()),
        .borderRadius = ArkUnion<Opt_Union_LengthMetrics_BorderRadiuses>(Ark_Empty()),
    };
    CHECK_NULL_RETURN(peer, style);
    CHECK_NULL_RETURN(peer->imageSpan, style);
    CHECK_NULL_RETURN(peer->imageSpan->GetImageAttribute(), style);
    style = ArkValue<Ark_ImageAttachmentLayoutStyle>(*peer->imageSpan->GetImageAttribute());
    return style;
}
} // ImageAttachmentAccessor
const GENERATED_ArkUIImageAttachmentAccessor* GetImageAttachmentAccessor()
{
    static const GENERATED_ArkUIImageAttachmentAccessor ImageAttachmentAccessorImpl {
        ImageAttachmentAccessor::DestroyPeerImpl,
        ImageAttachmentAccessor::CtorImpl,
        ImageAttachmentAccessor::GetFinalizerImpl,
        ImageAttachmentAccessor::GetValueImpl,
        ImageAttachmentAccessor::GetSizeImpl,
        ImageAttachmentAccessor::GetVerticalAlignImpl,
        ImageAttachmentAccessor::GetObjectFitImpl,
        ImageAttachmentAccessor::GetLayoutStyleImpl,
    };
    return &ImageAttachmentAccessorImpl;
}
}
