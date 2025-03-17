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
#include "offscreen_canvas_peer.h"
#include "offscreen_canvas_rendering_context2d_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor();
const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor* GetOffscreenCanvasRenderingContext2DAccessor();

namespace OffscreenCanvasAccessor {
const double ERROR_VALUE = -1;
const auto ARK_ERROR_VALUE = Converter::ArkValue<Ark_Number>(ERROR_VALUE);

void DestroyPeerImpl(Ark_OffscreenCanvas peer)
{
    if (peer) {
        peer->RemoveOptions();
        delete peer;
    }
}
Ark_OffscreenCanvas CtorImpl(const Ark_Number* width,
                             const Ark_Number* height)
{
    CHECK_NULL_RETURN(width, {});
    CHECK_NULL_RETURN(height, {});
    auto cw = static_cast<double>(Converter::Convert<float>(*width));
    auto ch = static_cast<double>(Converter::Convert<float>(*height));
    auto peer = new OffscreenCanvasPeer();
    peer->SetOptions(cw, ch);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_ImageBitmap TransferToImageBitmapImpl(Ark_OffscreenCanvas peer)
{
    CHECK_NULL_RETURN(peer, {});
    Ark_String emptyString;
    auto bitmap = GetImageBitmapAccessor()->ctor(&emptyString);
    return peer->TransferToImageBitmap(bitmap);
}
Ark_OffscreenCanvasRenderingContext2D GetContext2dImpl(Ark_OffscreenCanvas peer,
                                                       const Opt_RenderingContextSettings* options)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(options, {});
    auto width = Converter::ArkValue<Ark_Number>(static_cast<float>(peer->GetWidth()));
    auto height = Converter::ArkValue<Ark_Number>(static_cast<float>(peer->GetHeight()));
    auto offscreenContext = GetOffscreenCanvasRenderingContext2DAccessor()->ctor(&width, &height, options);
    auto offscreenSettings = Converter::OptConvert<RenderingContextSettingsPeer*>(*options).value_or(nullptr);
    return peer->GetContext2D(offscreenContext, offscreenSettings);
}
Ark_Number GetHeightImpl(Ark_OffscreenCanvas peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    double height = peer->OnGetHeight(ERROR_VALUE);
    return Converter::ArkValue<Ark_Number>(static_cast<float>(height));
}
void SetHeightImpl(Ark_OffscreenCanvas peer,
                   const Ark_Number* height)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(height);
    auto ch = static_cast<double>(Converter::Convert<float>(*height));
    peer->OnSetHeight(ch);
}
Ark_Number GetWidthImpl(Ark_OffscreenCanvas peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    double width = peer->OnGetWidth(ERROR_VALUE);
    return Converter::ArkValue<Ark_Number>(static_cast<float>(width));
}
void SetWidthImpl(Ark_OffscreenCanvas peer,
                  const Ark_Number* width)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(width);
    auto cw = static_cast<double>(Converter::Convert<float>(*width));
    peer->OnSetWidth(cw);
}
} // OffscreenCanvasAccessor
const GENERATED_ArkUIOffscreenCanvasAccessor* GetOffscreenCanvasAccessor()
{
    static const GENERATED_ArkUIOffscreenCanvasAccessor OffscreenCanvasAccessorImpl {
        OffscreenCanvasAccessor::DestroyPeerImpl,
        OffscreenCanvasAccessor::CtorImpl,
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
