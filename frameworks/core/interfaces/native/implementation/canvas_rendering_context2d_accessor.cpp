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
#include "frame_node_peer_impl.h"
#include "ui_context_accessor_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasRenderingContext2DAccessor {
const Ark_Number ARK_ERROR_VALUE = OHOS::Ace::NG::Converter::ArkValue<Ark_Number>(-1);

void DestroyPeerImpl(Ark_CanvasRenderingContext2D peer)
{
    if (peer) {
        peer->DecRefCount();
    }
}
Ark_CanvasRenderingContext2D ConstructImpl(const Opt_RenderingContextSettings* settings,
                                           const Opt_LengthMetricsUnit* unit)
{
    CHECK_NULL_RETURN(settings, {});
    auto peer = Referenced::MakeRefPtr<CanvasRenderingContext2DPeer>();
    peer->IncRefCount();
    auto optSettings = Converter::GetOptPtr(settings);
    auto optUnit = Converter::OptConvertPtr<Ace::CanvasUnit>(unit);
    if (optUnit) {
        peer->SetUnit(optUnit.value());
    }
    peer->SetOptions(optSettings);
    return Referenced::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String ToDataURLImpl(Ark_CanvasRenderingContext2D peer,
                         const Opt_String* type,
                         const Opt_Number* quality)
{
    CHECK_NULL_RETURN(peer, {});
    auto optType = Converter::OptConvertPtr<std::string>(type);
    auto optQuality = Converter::OptConvertPtr<float>(quality);
    auto result = peer->ToDataURL(optType, optQuality);
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_CanvasRenderingContext2D peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(peer);
    peer->StartImageAnalyzer(vmContext, asyncWorker, config, outputArgumentForReturningPromise);
}
void StopImageAnalyzerImpl(Ark_CanvasRenderingContext2D peer)
{
    CHECK_NULL_VOID(peer);
    peer->StopImageAnalyzer();
}
void OnAttachImpl(Ark_CanvasRenderingContext2D peer,
                  const VoidCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback_);
    auto arkCallback = CallbackHelper(*callback_);
    peer->On(std::move(arkCallback), CanvasRenderingContext2DPeer::CanvasCallbackType::ON_ATTACH);
}
void OffAttachImpl(Ark_CanvasRenderingContext2D peer,
                   const Opt_VoidCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto optCallback = Converter::GetOptPtr(callback_);
    auto arkCallback = optCallback ? CallbackHelper(*optCallback) : CallbackHelper<VoidCallback>();
    peer->Off(std::move(arkCallback), CanvasRenderingContext2DPeerImpl::CanvasCallbackType::ON_ATTACH);
}
void OnDetachImpl(Ark_CanvasRenderingContext2D peer,
                  const VoidCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback_);
    auto arkCallback = CallbackHelper(*callback_);
    peer->On(std::move(arkCallback), CanvasRenderingContext2DPeer::CanvasCallbackType::ON_DETACH);
}
void OffDetachImpl(Ark_CanvasRenderingContext2D peer,
                   const Opt_VoidCallback* callback_)
{
    CHECK_NULL_VOID(peer);
    auto optCallback = Converter::GetOptPtr(callback_);
    auto arkCallback = optCallback ? CallbackHelper(*optCallback) : CallbackHelper<VoidCallback>();
    peer->Off(std::move(arkCallback), CanvasRenderingContext2DPeer::CanvasCallbackType::ON_DETACH);
}
Ark_Number GetHeightImpl(Ark_CanvasRenderingContext2D peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    return Converter::ArkValue<Ark_Number>(peer->GetHeight());
}
void SetHeightImpl(Ark_CanvasRenderingContext2D peer,
                   const Ark_Number* height)
{
}
Ark_Number GetWidthImpl(Ark_CanvasRenderingContext2D peer)
{
    CHECK_NULL_RETURN(peer, ARK_ERROR_VALUE);
    return Converter::ArkValue<Ark_Number>(peer->GetWidth());
}
void SetWidthImpl(Ark_CanvasRenderingContext2D peer,
                  const Ark_Number* width)
{
}
Ark_FrameNode GetCanvasImpl(Ark_CanvasRenderingContext2D peer)
{
    return FrameNodePeer::Create(static_cast<Ark_UIContext>(nullptr));
}
void SetCanvasImpl(Ark_CanvasRenderingContext2D peer,
                   Ark_FrameNode canvas)
{
}
} // CanvasRenderingContext2DAccessor
const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor()
{
    static const GENERATED_ArkUICanvasRenderingContext2DAccessor CanvasRenderingContext2DAccessorImpl {
        CanvasRenderingContext2DAccessor::DestroyPeerImpl,
        CanvasRenderingContext2DAccessor::ConstructImpl,
        CanvasRenderingContext2DAccessor::GetFinalizerImpl,
        CanvasRenderingContext2DAccessor::ToDataURLImpl,
        CanvasRenderingContext2DAccessor::StartImageAnalyzerImpl,
        CanvasRenderingContext2DAccessor::StopImageAnalyzerImpl,
        CanvasRenderingContext2DAccessor::OnAttachImpl,
        CanvasRenderingContext2DAccessor::OffAttachImpl,
        CanvasRenderingContext2DAccessor::OnDetachImpl,
        CanvasRenderingContext2DAccessor::OffDetachImpl,
        CanvasRenderingContext2DAccessor::GetHeightImpl,
        CanvasRenderingContext2DAccessor::SetHeightImpl,
        CanvasRenderingContext2DAccessor::GetWidthImpl,
        CanvasRenderingContext2DAccessor::SetWidthImpl,
        CanvasRenderingContext2DAccessor::GetCanvasImpl,
        CanvasRenderingContext2DAccessor::SetCanvasImpl,
    };
    return &CanvasRenderingContext2DAccessorImpl;
}

}
