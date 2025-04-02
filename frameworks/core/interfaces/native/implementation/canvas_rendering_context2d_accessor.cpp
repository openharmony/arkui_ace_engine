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
#include <utility>

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "canvas_rendering_context2d_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasRenderingContext2DAccessor {
const Ark_Number ARK_ERROR_VALUE = OHOS::Ace::NG::Converter::ArkValue<Ark_Number>(-1);

void DestroyPeerImpl(Ark_CanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl *>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_CanvasRenderingContext2D CtorImpl(const Opt_RenderingContextSettings* settings)
{
    CHECK_NULL_RETURN(settings, {});
    auto peerImpl = Referenced::MakeRefPtr<CanvasRenderingContext2DPeerImpl>();
    peerImpl->IncRefCount();
    auto optSettings = Converter::OptConvert<Ark_RenderingContextSettings>(*settings);
    peerImpl->SetOptions(optSettings);
    return reinterpret_cast<CanvasRenderingContext2DPeer*>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String ToDataURLImpl(Ark_CanvasRenderingContext2D peer,
                         const Opt_String* type,
                         const Opt_Float32* quality)
{
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(type, {});
    CHECK_NULL_RETURN(quality, {});
    auto optType = Converter::OptConvert<std::string>(*type);
    auto optQuality = Converter::OptConvert<float>(*quality);
    auto result = peerImpl->ToDataURL(optType, optQuality);
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_CanvasRenderingContext2D peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->StartImageAnalyzer(config, outputArgumentForReturningPromise);
}
void StopImageAnalyzerImpl(Ark_CanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->StopImageAnalyzer();
}
void OnOnAttachImpl(Ark_VMContext vmContext,
                    Ark_CanvasRenderingContext2D peer,
                    const Callback_Void* callback_)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(callback_);
    auto arkCallback = CallbackHelper(*callback_);
    peerImpl->On(std::move(arkCallback), CanvasRenderingContext2DPeerImpl::CanvasCallbackType::ON_ATTACH);
}
void OffOnAttachImpl(Ark_VMContext vmContext,
                     Ark_CanvasRenderingContext2D peer,
                     const Opt_Callback_Void* callback_)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto optCallback = Converter::OptConvert<Callback_Void>(*callback_);
    auto arkCallback = optCallback ? CallbackHelper(*optCallback) : CallbackHelper<Callback_Void>();
    peerImpl->Off(std::move(arkCallback), CanvasRenderingContext2DPeerImpl::CanvasCallbackType::ON_ATTACH);
}
void OnOnDetachImpl(Ark_VMContext vmContext,
                    Ark_CanvasRenderingContext2D peer,
                    const Callback_Void* callback_)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(callback_);
    auto arkCallback = CallbackHelper(*callback_);
    peerImpl->On(std::move(arkCallback), CanvasRenderingContext2DPeerImpl::CanvasCallbackType::ON_DETACH);
}
void OffOnDetachImpl(Ark_VMContext vmContext,
                     Ark_CanvasRenderingContext2D peer,
                     const Opt_Callback_Void* callback_)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto optCallback = Converter::OptConvert<Callback_Void>(*callback_);
    auto arkCallback = optCallback ? CallbackHelper(*optCallback) : CallbackHelper<Callback_Void>();
    peerImpl->Off(std::move(arkCallback), CanvasRenderingContext2DPeerImpl::CanvasCallbackType::ON_DETACH);
}
Ark_Number GetHeightImpl(Ark_CanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, ARK_ERROR_VALUE);
    return Converter::ArkValue<Ark_Number>(peerImpl->GetHeight());
}
Ark_Number GetWidthImpl(Ark_CanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, ARK_ERROR_VALUE);
    return Converter::ArkValue<Ark_Number>(peerImpl->GetWidth());
}
Ark_FrameNode GetCanvasImpl(Ark_CanvasRenderingContext2D peer)
{
    LOGE("ARKOALA CanvasRenderingContext2DAccessor::GetCanvasImpl type Ark_UIContext"
        " is not fully implemented on the current platform.");
    return {};
}
} // CanvasRenderingContext2DAccessor
const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor()
{
    static const GENERATED_ArkUICanvasRenderingContext2DAccessor CanvasRenderingContext2DAccessorImpl {
        CanvasRenderingContext2DAccessor::DestroyPeerImpl,
        CanvasRenderingContext2DAccessor::CtorImpl,
        CanvasRenderingContext2DAccessor::GetFinalizerImpl,
        CanvasRenderingContext2DAccessor::ToDataURLImpl,
        CanvasRenderingContext2DAccessor::StartImageAnalyzerImpl,
        CanvasRenderingContext2DAccessor::StopImageAnalyzerImpl,
        CanvasRenderingContext2DAccessor::OnOnAttachImpl,
        CanvasRenderingContext2DAccessor::OffOnAttachImpl,
        CanvasRenderingContext2DAccessor::OnOnDetachImpl,
        CanvasRenderingContext2DAccessor::OffOnDetachImpl,
        CanvasRenderingContext2DAccessor::GetHeightImpl,
        CanvasRenderingContext2DAccessor::GetWidthImpl,
        CanvasRenderingContext2DAccessor::GetCanvasImpl,
    };
    return &CanvasRenderingContext2DAccessorImpl;
}

struct CanvasRenderingContext2DPeer {
    virtual ~CanvasRenderingContext2DPeer() = default;
};
}
