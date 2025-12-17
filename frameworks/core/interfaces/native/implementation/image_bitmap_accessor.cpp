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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/image_bitmap_peer_impl.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ImageBitmapAccessor {
const auto ARK_ERROR_VALUE = Converter::ArkValue<Ark_Number>(0);
void DestroyPeerImpl(Ark_ImageBitmap peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ImageBitmap ConstructImpl(const Ark_Union_PixelMap_String* src,
                              const Opt_LengthMetricsUnit* unit)
{
    auto peer = PeerUtils::CreatePeer<ImageBitmapPeer>();
    Converter::VisitUnionPtr(src,
        [peer](const Ark_String& src) {
            auto stringSrc = Converter::Convert<std::string>(src);
            peer->SetOptions(stringSrc);
        },
        [peer](const Ark_image_PixelMap& src) {
            peer->SetOptions("", src->pixelMap);
        },
        []() {});
    auto optUnit = Converter::OptConvertPtr<Ace::CanvasUnit>(unit);
    if (optUnit) {
        peer->SetUnit(optUnit.value());
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void CloseImpl(Ark_ImageBitmap peer)
{
    CHECK_NULL_VOID(peer);
    peer->OnClose();
}
Ark_Number GetHeightImpl(Ark_ImageBitmap peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    auto height = peer->OnGetHeight();
    return NG::Converter::ArkValue<Ark_Number>(static_cast<int32_t>(height));
}
void SetHeightImpl(Ark_ImageBitmap peer,
                   const Ark_Number* height)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(height);
    auto value = Converter::Convert<float>(*height);
    peer->SetHeight(value);
}
Ark_Number GetWidthImpl(Ark_ImageBitmap peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    double width = peer->OnGetWidth();
    return NG::Converter::ArkValue<Ark_Number>(static_cast<int32_t>(width));
}
void SetWidthImpl(Ark_ImageBitmap peer,
                  const Ark_Number* width)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(width);
    auto value = Converter::Convert<float>(*width);
    peer->SetWidth(value);
}
} // ImageBitmapAccessor
const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor()
{
    static const GENERATED_ArkUIImageBitmapAccessor ImageBitmapAccessorImpl {
        ImageBitmapAccessor::DestroyPeerImpl,
        ImageBitmapAccessor::ConstructImpl,
        ImageBitmapAccessor::GetFinalizerImpl,
        ImageBitmapAccessor::CloseImpl,
        ImageBitmapAccessor::GetHeightImpl,
        ImageBitmapAccessor::SetHeightImpl,
        ImageBitmapAccessor::GetWidthImpl,
        ImageBitmapAccessor::SetWidthImpl,
    };
    return &ImageBitmapAccessorImpl;
}
}
