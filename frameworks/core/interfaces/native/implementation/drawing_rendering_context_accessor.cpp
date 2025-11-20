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
#include "core/interfaces/native/utility/peer_utils.h"
#include "drawing_rendering_context_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DrawingRenderingContextAccessor {
void DestroyPeerImpl(Ark_DrawingRenderingContext peer)
{
    auto peerImpl = reinterpret_cast<DrawingRenderingContextPeerImpl*>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_DrawingRenderingContext ConstructImpl(const Opt_LengthMetricsUnit* unit)
{
    auto peerImpl = Referenced::MakeRefPtr<DrawingRenderingContextPeerImpl>();
    peerImpl->IncRefCount();
    auto optUnit = Converter::OptConvertPtr<Ace::CanvasUnit>(unit);
    peerImpl->SetOptions(optUnit);
    return reinterpret_cast<DrawingRenderingContextPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void InvalidateImpl(Ark_DrawingRenderingContext peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<DrawingRenderingContextPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->SetInvalidate();
}
Ark_Size GetSizeImpl(Ark_DrawingRenderingContext peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<DrawingRenderingContextPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    return Converter::ArkValue<Ark_Size>(peerImpl->GetSize());
}
Opt_drawing_Canvas GetCanvasImpl(Ark_DrawingRenderingContext peer)
{
    auto invalid = Converter::ArkValue<Opt_drawing_Canvas>();
    CHECK_NULL_RETURN(peer, invalid);
    auto peerImpl = reinterpret_cast<DrawingRenderingContextPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, invalid);
    auto canvas = peerImpl->GetCanvas();
    return Converter::ArkValue<Opt_drawing_Canvas>(canvas);
}
} // DrawingRenderingContextAccessor
const GENERATED_ArkUIDrawingRenderingContextAccessor* GetDrawingRenderingContextAccessor()
{
    static const GENERATED_ArkUIDrawingRenderingContextAccessor DrawingRenderingContextAccessorImpl {
        DrawingRenderingContextAccessor::DestroyPeerImpl,
        DrawingRenderingContextAccessor::ConstructImpl,
        DrawingRenderingContextAccessor::GetFinalizerImpl,
        DrawingRenderingContextAccessor::InvalidateImpl,
        DrawingRenderingContextAccessor::GetSizeImpl,
        DrawingRenderingContextAccessor::GetCanvasImpl,
    };
    return &DrawingRenderingContextAccessorImpl;
}

}
