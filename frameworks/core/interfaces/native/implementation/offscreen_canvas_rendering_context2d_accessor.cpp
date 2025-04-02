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
#include "offscreen_canvas_rendering_context2d_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor();

namespace OffscreenCanvasRenderingContext2DAccessor {
void DestroyPeerImpl(Ark_OffscreenCanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<OffscreenCanvasRenderingContext2DPeerImpl*>(peer);
    if (peerImpl) {
        peerImpl->RemoveOptions();
        peerImpl->DecRefCount();
    }
}
Ark_OffscreenCanvasRenderingContext2D CtorImpl(const Ark_Number* width,
                                               const Ark_Number* height,
                                               const Opt_RenderingContextSettings* settings)
{
    auto peerImpl = Referenced::MakeRefPtr<OffscreenCanvasRenderingContext2DPeerImpl>();
    peerImpl->IncRefCount();
    auto fWidth = static_cast<double>(Converter::Convert<float>(*width));
    auto fHeight = static_cast<double>(Converter::Convert<float>(*height));
    auto optSettings = Converter::OptConvert<Ark_RenderingContextSettings>(*settings);
    peerImpl->SetOptions(fWidth, fHeight, optSettings);
    return reinterpret_cast<OffscreenCanvasRenderingContext2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String ToDataURLImpl(Ark_OffscreenCanvasRenderingContext2D peer,
                         const Opt_String* type,
                         const Opt_Float32* quality)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<OffscreenCanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(type, {});
    CHECK_NULL_RETURN(quality, {});
    auto optType = Converter::OptConvert<std::string>(*type);
    auto optQuality = Converter::OptConvert<float>(*quality);
    auto result = peerImpl->ToDataURL(optType, optQuality);
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_ImageBitmap TransferToImageBitmapImpl(Ark_OffscreenCanvasRenderingContext2D peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<OffscreenCanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    Ark_String emptyString;
    auto bitmap = GetImageBitmapAccessor()->ctor(&emptyString);
    return peerImpl->TransferToImageBitmap(bitmap);
}
} // OffscreenCanvasRenderingContext2DAccessor
const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor* GetOffscreenCanvasRenderingContext2DAccessor()
{
    static const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor OffscreenCanvasRenderingContext2DAccessorImpl {
        OffscreenCanvasRenderingContext2DAccessor::DestroyPeerImpl,
        OffscreenCanvasRenderingContext2DAccessor::CtorImpl,
        OffscreenCanvasRenderingContext2DAccessor::GetFinalizerImpl,
        OffscreenCanvasRenderingContext2DAccessor::ToDataURLImpl,
        OffscreenCanvasRenderingContext2DAccessor::TransferToImageBitmapImpl,
    };
    return &OffscreenCanvasRenderingContext2DAccessorImpl;
}

struct OffscreenCanvasRenderingContext2DPeer {
    virtual ~OffscreenCanvasRenderingContext2DPeer() = default;
};
}
