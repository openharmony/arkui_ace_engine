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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "arkoala_api_generated.h"
#include "image_bitmap_peer_impl.h"
#include "offscreen_canvas_peer.h"
#include "offscreen_canvas_rendering_context2d_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace OffscreenCanvasAccessor {
const double ERROR_VALUE = -1;
const auto ARK_ERROR_VALUE = Converter::ArkValue<Ark_Float64>(ERROR_VALUE);

void DestroyPeerImpl(Ark_OffscreenCanvas peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_OffscreenCanvas ConstructImpl(Ark_Float64 width,
                                  Ark_Float64 height,
                                  const Opt_LengthMetricsUnit* unit)
{
    auto cw = static_cast<double>(Converter::Convert<float>(width));
    auto ch = static_cast<double>(Converter::Convert<float>(height));
    auto optUnit = Converter::OptConvertPtr<Ace::CanvasUnit>(unit);
    auto peer = PeerUtils::CreatePeer<OffscreenCanvasPeer>();
    peer->SetOptions(cw, ch);
    if (unit->tag != INTEROP_TAG_UNDEFINED) {
        peer->SetUnit(optUnit.value());
    }
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_ImageBitmap TransferToImageBitmapImpl(Ark_OffscreenCanvas peer)
{
    auto invalid = Converter::ArkValue<Opt_ImageBitmap>();
    CHECK_NULL_RETURN(peer, invalid);
    auto bitmap = peer->TransferToImageBitmap();
    CHECK_NULL_RETURN(bitmap, invalid);
    return Converter::ArkValue<Opt_ImageBitmap>(bitmap);
}
Ark_OffscreenCanvasRenderingContext2D GetContext2dImpl(Ark_OffscreenCanvas peer,
                                                       const Opt_RenderingContextSettings* options)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(options, {});
    auto offscreenContext = PeerUtils::CreatePeer<OffscreenCanvasRenderingContext2DPeer>();
    auto offscreenSettings = Converter::GetOptPtr(options).value_or(nullptr);
    return peer->GetContext2D(offscreenContext, offscreenSettings);
}
Ark_Float64 GetHeightImpl(Ark_OffscreenCanvas peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    double height = peer->OnGetHeight(ERROR_VALUE);
    return Converter::ArkValue<Ark_Float64>(static_cast<float>(height));
}
void SetHeightImpl(Ark_OffscreenCanvas peer,
                   Ark_Float64 height)
{
    CHECK_NULL_VOID(peer);
    auto ch = static_cast<double>(Converter::Convert<float>(height));
    peer->OnSetHeight(ch);
}
Ark_Float64 GetWidthImpl(Ark_OffscreenCanvas peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    double width = peer->OnGetWidth(ERROR_VALUE);
    return Converter::ArkValue<Ark_Float64>(static_cast<float>(width));
}
void SetWidthImpl(Ark_OffscreenCanvas peer,
                  Ark_Float64 width)
{
    CHECK_NULL_VOID(peer);
    auto cw = static_cast<double>(Converter::Convert<float>(width));
    peer->OnSetWidth(cw);
}
} // OffscreenCanvasAccessor
const GENERATED_ArkUIOffscreenCanvasAccessor* GetOffscreenCanvasAccessor()
{
    static const GENERATED_ArkUIOffscreenCanvasAccessor OffscreenCanvasAccessorImpl {
        OffscreenCanvasAccessor::DestroyPeerImpl,
        OffscreenCanvasAccessor::ConstructImpl,
        OffscreenCanvasAccessor::GetFinalizerImpl,
        OffscreenCanvasAccessor::TransferToImageBitmapImpl,
        OffscreenCanvasAccessor::GetContext2dImpl,
        OffscreenCanvasAccessor::GetHeightImpl,
        OffscreenCanvasAccessor::SetHeightImpl,
        OffscreenCanvasAccessor::GetWidthImpl,
        OffscreenCanvasAccessor::SetWidthImpl,
    };
    return &OffscreenCanvasAccessorImpl;
}

}
