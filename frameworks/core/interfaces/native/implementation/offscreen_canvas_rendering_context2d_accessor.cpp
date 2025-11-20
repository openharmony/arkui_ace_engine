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

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "arkoala_api_generated.h"
#include "image_bitmap_peer_impl.h"
#include "offscreen_canvas_rendering_context2d_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace OffscreenCanvasRenderingContext2DAccessor {
void DestroyPeerImpl(Ark_OffscreenCanvasRenderingContext2D peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_OffscreenCanvasRenderingContext2D ConstructImpl(Ark_Float64 width,
                                                    Ark_Float64 height,
                                                    const Opt_RenderingContextSettings* settings,
                                                    const Opt_LengthMetricsUnit* unit)
{
    auto offscreenContext = PeerUtils::CreatePeer<OffscreenCanvasRenderingContext2DPeer>();
    auto fWidth = static_cast<double>(Converter::Convert<float>(width));
    auto fHeight = static_cast<double>(Converter::Convert<float>(height));
    auto optSettings = Converter::GetOptPtr(settings);
    auto optUnit = Converter::OptConvertPtr<Ace::CanvasUnit>(unit);
    if (optUnit) {
        offscreenContext->SetUnit(optUnit.value());
    }
    offscreenContext->SetOptions(fWidth, fHeight, optSettings);
    return offscreenContext;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String ToDataURLImpl(Ark_OffscreenCanvasRenderingContext2D peer,
                         const Opt_String* type,
                         const Opt_Float64* quality)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<OffscreenCanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    auto optType = Converter::OptConvertPtr<std::string>(type);
    auto optQuality = Converter::OptConvertPtr<float>(quality);
    auto result = peerImpl->ToDataURL(optType, optQuality);
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Opt_ImageBitmap TransferToImageBitmapImpl(Ark_OffscreenCanvasRenderingContext2D peer)
{
    auto invalid = Converter::ArkValue<Opt_ImageBitmap>();
    CHECK_NULL_RETURN(peer, invalid);
    auto bitmap = peer->TransferToImageBitmap();
    CHECK_NULL_RETURN(bitmap, invalid);
    return Converter::ArkValue<Opt_ImageBitmap>(bitmap);
}
} // OffscreenCanvasRenderingContext2DAccessor
const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor* GetOffscreenCanvasRenderingContext2DAccessor()
{
    static const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor OffscreenCanvasRenderingContext2DAccessorImpl {
        OffscreenCanvasRenderingContext2DAccessor::DestroyPeerImpl,
        OffscreenCanvasRenderingContext2DAccessor::ConstructImpl,
        OffscreenCanvasRenderingContext2DAccessor::GetFinalizerImpl,
        OffscreenCanvasRenderingContext2DAccessor::ToDataURLImpl,
        OffscreenCanvasRenderingContext2DAccessor::TransferToImageBitmapImpl,
    };
    return &OffscreenCanvasRenderingContext2DAccessorImpl;
}

}
