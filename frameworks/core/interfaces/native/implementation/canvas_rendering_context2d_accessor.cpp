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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "canvas_rendering_context2d_peer_impl.h"
#include "drawing_rendering_context_peer_impl.h"
#include "rendering_context_settings_peer.h"

#include "arkoala_api_generated.h"

namespace {
const Ark_Number ERROR_VALUE = OHOS::Ace::NG::Converter::ArkValue<Ark_Number>(-1);
constexpr auto IMAGE_TYPE_DEFAULT = "image/png";
constexpr auto IMAGE_QUALITY_MIN = 0.0f;
constexpr auto IMAGE_QUALITY_MAX = 1.0f;
constexpr auto IMAGE_QUALITY_DEFAULT = 0.92f;
constexpr auto EMPTY_STRING = "";
} // namespace

namespace OHOS::Ace::NG {
namespace Validator {
void ValidateNonEmpty(std::optional<std::string>& opt)
{
    if (opt.has_value() && opt.value().empty()) {
        opt.reset();
    }
}
} // namespace Validator
namespace Converter {
template<>
inline void AssignCast(std::optional<bool>& dst, const Ark_RenderingContextSettings& src)
{
    dst = src->antialias;
}
} // namespace OHOS::Ace::NG::Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CanvasRenderingContext2DAccessor {
void DestroyPeerImpl(Ark_CanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl *>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_CanvasRenderingContext2D CtorImpl(const Opt_RenderingContextSettings* settings)
{
    CHECK_NULL_RETURN(settings, nullptr);

    auto peerImpl = Referenced::MakeRefPtr<CanvasRenderingContext2DPeerImpl>();
    peerImpl->IncRefCount();
    auto antialias = Converter::OptConvert<bool>(*settings);
    if (antialias) {
        peerImpl->SetAntiAlias(*antialias);
    }
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
    Validator::ValidateNonEmpty(optType);
    auto optQuality = Converter::OptConvert<float>(*quality);
    Validator::ValidateByRange(optQuality, IMAGE_QUALITY_MIN, IMAGE_QUALITY_MAX);
    auto imageType = optType.value_or(IMAGE_TYPE_DEFAULT);
    auto imageQuality = optQuality.value_or(IMAGE_QUALITY_DEFAULT);
    peerImpl->ToDataURL(imageType, imageQuality);
    return {};
}
void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_CanvasRenderingContext2D peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStartImageAnalyzer(config, outputArgumentForReturningPromise);
}
void StopImageAnalyzerImpl(Ark_CanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->TriggerStopImageAnalyzer();
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
    auto optCallback = callback_ ? Converter::OptConvert<Callback_Void>(*callback_) : std::nullopt;
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
    auto optCallback = callback_ ? Converter::OptConvert<Callback_Void>(*callback_) : std::nullopt;
    auto arkCallback = optCallback ? CallbackHelper(*optCallback) : CallbackHelper<Callback_Void>();
    peerImpl->Off(std::move(arkCallback), CanvasRenderingContext2DPeerImpl::CanvasCallbackType::ON_DETACH);
}
Ark_Number GetHeightImpl(Ark_CanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, ::ERROR_VALUE);
    return Converter::ArkValue<Ark_Number>(peerImpl->TriggerGetHeight());
}
Ark_Number GetWidthImpl(Ark_CanvasRenderingContext2D peer)
{
    auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    return Converter::ArkValue<Ark_Number>(peerImpl->TriggerGetWidth());
}
Ark_FrameNode GetCanvasImpl(Ark_CanvasRenderingContext2D peer)
{
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

}
