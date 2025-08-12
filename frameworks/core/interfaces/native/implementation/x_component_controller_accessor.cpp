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
#ifdef XCOMPONENT_SUPPORTED
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#endif //XCOMPONENT_SUPPORTED
#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentControllerAccessor {
void DestroyPeerImpl(Ark_XComponentController peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    peerImpl->DecRefCount();
}
Ark_XComponentController CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<XComponentControllerPeerImpl>();
    peerImpl->IncRefCount();
#ifdef XCOMPONENT_SUPPORTED
    peerImpl->controller = std::make_shared<OHOS::Ace::NG::XComponentControllerNG>();
#endif //XCOMPONENT_SUPPORTED
    return reinterpret_cast<Ark_XComponentController>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetXComponentSurfaceIdImpl(Ark_XComponentController peer)
{
    Ark_String arkSurfaceId = {};
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl->controller, {});
    auto surfaceId = peerImpl->controller->GetSurfaceId();
    arkSurfaceId = Converter::ArkValue<Ark_String>(surfaceId, Converter::FC);
#endif //XCOMPONENT_SUPPORTED
    return arkSurfaceId;
}
Ark_Object GetXComponentContextImpl(Ark_XComponentController peer)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl->controller, {});
    LOGE("XComponentControllerAccessor::GetXComponentContextImpl - return context object need to be supported");
#endif //XCOMPONENT_SUPPORTED
    return {};
}
void SetXComponentSurfaceSizeImpl(Ark_XComponentController peer,
                                  const Ark_Literal_Number_surfaceHeight_surfaceWidth* value)
{
#ifdef XCOMPONENT_SUPPORTED
    //This API is deprecated since API version 12. Should be used SetXComponentSurfaceRectImpl instead.
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl->controller);
    CHECK_NULL_VOID(value);
    uint32_t surfaceWidth = static_cast<uint32_t>(Converter::Convert<int32_t>(value->surfaceWidth));
    uint32_t surfaceHeight = static_cast<uint32_t>(Converter::Convert<int32_t>(value->surfaceHeight));
    peerImpl->controller->ConfigSurface(surfaceWidth, surfaceHeight);
#endif //XCOMPONENT_SUPPORTED
}
void SetXComponentSurfaceRectImpl(Ark_XComponentController peer,
                                  const Ark_SurfaceRect* rect)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl->controller);
    CHECK_NULL_VOID(rect);
    auto offsetX = Converter::OptConvert<float>(rect->offsetX);
    auto offsetY = Converter::OptConvert<float>(rect->offsetY);
    auto surfaceWidth = Converter::Convert<float>(rect->surfaceWidth);
    auto surfaceHeight = Converter::Convert<float>(rect->surfaceHeight);
    peerImpl->controller->SetIdealSurfaceWidth(surfaceWidth);
    peerImpl->controller->SetIdealSurfaceHeight(surfaceHeight);
    if (offsetX) {
        peerImpl->controller->SetIdealSurfaceOffsetX(offsetX.value());
    } else {
        peerImpl->controller->ClearIdealSurfaceOffset(true);
    }
    if (offsetY) {
        peerImpl->controller->SetIdealSurfaceOffsetY(offsetY.value());
    } else {
        peerImpl->controller->ClearIdealSurfaceOffset(true);
    }
    peerImpl->controller->UpdateSurfaceBounds();
#endif //XCOMPONENT_SUPPORTED
}
Ark_SurfaceRect GetXComponentSurfaceRectImpl(Ark_XComponentController peer)
{
    Ark_SurfaceRect rect;
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl->controller, {});
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    peerImpl->controller->GetSurfaceOffset(offsetX, offsetY);
    peerImpl->controller->GetSurfaceSize(width, height);
    rect.offsetX = Converter::ArkValue<Opt_Number>(offsetX);
    rect.offsetY = Converter::ArkValue<Opt_Number>(offsetY);
    rect.surfaceWidth = Converter::ArkValue<Ark_Number>(width);
    rect.surfaceHeight = Converter::ArkValue<Ark_Number>(height);
#endif //XCOMPONENT_SUPPORTED
    return rect;
}
void SetXComponentSurfaceRotationImpl(Ark_XComponentController peer,
                                      const Ark_SurfaceRotationOptions* rotationOptions)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl->controller);
    CHECK_NULL_VOID(rotationOptions);
    auto lock = Converter::OptConvert<bool>(rotationOptions->lock);
    peerImpl->controller->SetSurfaceRotation(lock.value_or(false));
#endif //XCOMPONENT_SUPPORTED
}
Ark_SurfaceRotationOptions GetXComponentSurfaceRotationImpl(Ark_XComponentController peer)
{
    Ark_SurfaceRotationOptions rotationOptions;
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl->controller, {});
    bool lock = peerImpl->controller->GetSurfaceRotation();
    rotationOptions.lock = Converter::ArkValue<Opt_Boolean>(lock);
#endif //XCOMPONENT_SUPPORTED
    return rotationOptions;
}
void OnSurfaceCreatedImpl(Ark_XComponentController peer,
                          const Ark_String* surfaceId)
{
#ifdef XCOMPONENT_SUPPORTED
    LOGE("XComponentControllerAccessor::OnSurfaceCreatedImpl - callback need to be supported");
#endif //XCOMPONENT_SUPPORTED
}
void OnSurfaceChangedImpl(Ark_XComponentController peer,
                          const Ark_String* surfaceId,
                          const Ark_SurfaceRect* rect)
{
#ifdef XCOMPONENT_SUPPORTED
    LOGE("XComponentControllerAccessor::OnSurfaceChangedImpl - callback need to be supported");
#endif //XCOMPONENT_SUPPORTED
}
void OnSurfaceDestroyedImpl(Ark_XComponentController peer,
                            const Ark_String* surfaceId)
{
#ifdef XCOMPONENT_SUPPORTED
    LOGE("XComponentControllerAccessor::OnSurfaceDestroyedImpl - callback need to be supported");
#endif //XCOMPONENT_SUPPORTED
}
void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_XComponentController peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    peerImpl->TriggerStartImageAnalyzer(config, outputArgumentForReturningPromise);
#endif //XCOMPONENT_SUPPORTED
}
void StopImageAnalyzerImpl(Ark_XComponentController peer)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl->controller);
    peerImpl->controller->StopImageAnalyzer();
#endif //XCOMPONENT_SUPPORTED
}
void SetOnSurfaceCreatedCallbackImpl(Ark_XComponentController peer,
    const Callback_String_Void* onSurfaceCreatedCallback)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl->controller);
    CHECK_NULL_VOID(onSurfaceCreatedCallback);
    peerImpl->SetOnSurfaceCreatedEvent(*onSurfaceCreatedCallback);
#endif //XCOMPONENT_SUPPORTED
}
void SetOnSurfaceChangedCallbackImpl(Ark_XComponentController peer,
    const Callback_String_SurfaceRect_Void* onSurfaceChangedCallback)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl->controller);
    CHECK_NULL_VOID(onSurfaceChangedCallback);
    peerImpl->SetOnSurfaceChangedEvent(*onSurfaceChangedCallback);
#endif //XCOMPONENT_SUPPORTED
}
void SetOnSurfaceDestroyedCallbackImpl(Ark_XComponentController peer,
    const Callback_String_Void* onSurfaceDestroyedCallback)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl->controller);
    CHECK_NULL_VOID(onSurfaceDestroyedCallback);
    peerImpl->SetOnSurfaceDestroyedEvent(*onSurfaceDestroyedCallback);
#endif //XCOMPONENT_SUPPORTED
}
} // XComponentControllerAccessor
const GENERATED_ArkUIXComponentControllerAccessor* GetXComponentControllerAccessor()
{
    static const GENERATED_ArkUIXComponentControllerAccessor XComponentControllerAccessorImpl {
        XComponentControllerAccessor::DestroyPeerImpl,
        XComponentControllerAccessor::CtorImpl,
        XComponentControllerAccessor::GetFinalizerImpl,
        XComponentControllerAccessor::GetXComponentSurfaceIdImpl,
        XComponentControllerAccessor::GetXComponentContextImpl,
        XComponentControllerAccessor::SetXComponentSurfaceSizeImpl,
        XComponentControllerAccessor::SetXComponentSurfaceRectImpl,
        XComponentControllerAccessor::GetXComponentSurfaceRectImpl,
        XComponentControllerAccessor::SetXComponentSurfaceRotationImpl,
        XComponentControllerAccessor::GetXComponentSurfaceRotationImpl,
        XComponentControllerAccessor::OnSurfaceCreatedImpl,
        XComponentControllerAccessor::OnSurfaceChangedImpl,
        XComponentControllerAccessor::OnSurfaceDestroyedImpl,
        XComponentControllerAccessor::StartImageAnalyzerImpl,
        XComponentControllerAccessor::StopImageAnalyzerImpl,
        XComponentControllerAccessor::SetOnSurfaceCreatedCallbackImpl,
        XComponentControllerAccessor::SetOnSurfaceChangedCallbackImpl,
        XComponentControllerAccessor::SetOnSurfaceDestroyedCallbackImpl,
    };
    return &XComponentControllerAccessorImpl;
}

struct XComponentControllerPeer {
    virtual ~XComponentControllerPeer() = default;
};
}
