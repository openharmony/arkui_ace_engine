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
    auto pixelMapPeer = value.value;
    if (pixelMapPeer) {
        imageOptions.imagePixelMap = pixelMapPeer->pixelMap;
    }
#endif
    auto imageStyle = OptConvert<ImageSpanAttribute>(value.layoutStyle);
    if (imageStyle) {
        imageStyle->verticalAlign = OptConvert<VerticalAlign>(value.verticalAlign);
        imageStyle->objectFit = OptConvert<ImageFit>(value.objectFit);
        imageStyle->size = OptConvert<ImageSpanSize>(value.size);
        imageOptions.imageAttribute = imageStyle;
    }
    return AceType::MakeRefPtr<ImageSpan>(imageOptions);
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
Ark_ImageSpanAlignment GetVerticalAlignImpl(Ark_ImageAttachment peer)
{
    CHECK_NULL_RETURN(peer && peer->imageSpan && peer->imageSpan->GetImageSpanOptions().imageAttribute,
        INVALID_ENUM_VAL<Ark_ImageSpanAlignment>);
    auto aligment = peer->imageSpan->GetImageSpanOptions().imageAttribute->verticalAlign;
    CHECK_NULL_RETURN(aligment, INVALID_ENUM_VAL<Ark_ImageSpanAlignment>);
    return ArkValue<Ark_ImageSpanAlignment>(*aligment);
}
Ark_ImageFit GetObjectFitImpl(Ark_ImageAttachment peer)
{
    CHECK_NULL_RETURN(peer && peer->imageSpan && peer->imageSpan->GetImageSpanOptions().imageAttribute,
        INVALID_ENUM_VAL<Ark_ImageFit>);
    auto objectFit = peer->imageSpan->GetImageSpanOptions().imageAttribute->objectFit;
    CHECK_NULL_RETURN(objectFit, INVALID_ENUM_VAL<Ark_ImageFit>);
    return ArkValue<Ark_ImageFit>(*objectFit);
}
} // ImageAttachmentAccessor
const GENERATED_ArkUIImageAttachmentAccessor* GetImageAttachmentAccessor()
{
    static const GENERATED_ArkUIImageAttachmentAccessor ImageAttachmentAccessorImpl {
        ImageAttachmentAccessor::DestroyPeerImpl,
        ImageAttachmentAccessor::CtorImpl,
        ImageAttachmentAccessor::GetFinalizerImpl,
        ImageAttachmentAccessor::GetValueImpl,
        ImageAttachmentAccessor::GetVerticalAlignImpl,
        ImageAttachmentAccessor::GetObjectFitImpl,
    };
    return &ImageAttachmentAccessorImpl;
}
}
