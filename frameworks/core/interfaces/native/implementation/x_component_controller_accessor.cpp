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
    peer->DecRefCount();
}
Ark_XComponentController CtorImpl()
{
    auto peer = Referenced::MakeRefPtr<XComponentControllerPeer>();
    peer->IncRefCount();
#ifdef XCOMPONENT_SUPPORTED
    peer->controller = std::make_shared<OHOS::Ace::NG::XComponentControllerNG>();
#endif //XCOMPONENT_SUPPORTED
    return Referenced::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetXComponentSurfaceIdImpl(Ark_XComponentController peer)
{
    Ark_String arkSurfaceId = {};
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer && peer->controller, {});
    auto surfaceId = peer->controller->GetSurfaceId();
    arkSurfaceId = Converter::ArkValue<Ark_String>(surfaceId, Converter::FC);
#endif //XCOMPONENT_SUPPORTED
    return arkSurfaceId;
}
Ark_CustomObject GetXComponentContextImpl(Ark_XComponentController peer)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer && peer->controller, {});
    LOGE("XComponentControllerAccessor::GetXComponentContextImpl - return context object need to be supported");
#endif //XCOMPONENT_SUPPORTED
    return {};
}
void SetXComponentSurfaceSizeImpl(Ark_XComponentController peer,
                                  const Ark_Literal_Number_surfaceHeight_surfaceWidth* value)
{
#ifdef XCOMPONENT_SUPPORTED
    //This API is deprecated since API version 12. Should be used SetXComponentSurfaceRectImpl instead.
    CHECK_NULL_VOID(peer && peer->controller);
    CHECK_NULL_VOID(value);
    uint32_t surfaceWidth = static_cast<uint32_t>(Converter::Convert<int32_t>(value->surfaceWidth));
    uint32_t surfaceHeight = static_cast<uint32_t>(Converter::Convert<int32_t>(value->surfaceHeight));
    peer->controller->ConfigSurface(surfaceWidth, surfaceHeight);
#endif //XCOMPONENT_SUPPORTED
}
void SetXComponentSurfaceRectImpl(Ark_XComponentController peer,
                                  const Ark_SurfaceRect* rect)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer && peer->controller);
    CHECK_NULL_VOID(rect);
    auto offsetX = Converter::OptConvert<float>(rect->offsetX);
    auto offsetY = Converter::OptConvert<float>(rect->offsetY);
    auto surfaceWidth = Converter::Convert<float>(rect->surfaceWidth);
    auto surfaceHeight = Converter::Convert<float>(rect->surfaceHeight);
    peer->controller->SetIdealSurfaceWidth(surfaceWidth);
    peer->controller->SetIdealSurfaceHeight(surfaceHeight);
    if (offsetX) {
        peer->controller->SetIdealSurfaceOffsetX(offsetX.value());
    } else {
        peer->controller->ClearIdealSurfaceOffset(true);
    }
    if (offsetY) {
        peer->controller->SetIdealSurfaceOffsetY(offsetY.value());
    } else {
        peer->controller->ClearIdealSurfaceOffset(true);
    }
    peer->controller->UpdateSurfaceBounds();
#endif //XCOMPONENT_SUPPORTED
}
Ark_SurfaceRect GetXComponentSurfaceRectImpl(Ark_XComponentController peer)
{
    Ark_SurfaceRect rect;
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer && peer->controller, {});
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    peer->controller->GetSurfaceOffset(offsetX, offsetY);
    peer->controller->GetSurfaceSize(width, height);
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
    CHECK_NULL_VOID(peer && peer->controller);
    CHECK_NULL_VOID(rotationOptions);
    auto lock = Converter::OptConvert<bool>(rotationOptions->lock);
    peer->controller->SetSurfaceRotation(lock.value_or(false));
#endif //XCOMPONENT_SUPPORTED
}
Ark_SurfaceRotationOptions GetXComponentSurfaceRotationImpl(Ark_XComponentController peer)
{
    Ark_SurfaceRotationOptions rotationOptions;
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer && peer->controller, {});
    bool lock = peer->controller->GetSurfaceRotation();
    rotationOptions.lock = Converter::ArkValue<Opt_Boolean>(lock);
#endif //XCOMPONENT_SUPPORTED
    return rotationOptions;
}
void OnSurfaceCreatedImpl(Ark_XComponentController peer,
                          const Ark_String* surfaceId)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer && peer->controller);
    auto pattern = peer->controller->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto frameNode = pattern->GetHost();
    LOGE("XComponentControllerAccessor::OnSurfaceCreatedImpl - callback need to be supported");
#endif //XCOMPONENT_SUPPORTED
}
void OnSurfaceChangedImpl(Ark_XComponentController peer,
                          const Ark_String* surfaceId,
                          const Ark_SurfaceRect* rect)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer && peer->controller);
    auto pattern = peer->controller->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto frameNode = pattern->GetHost();
    LOGE("XComponentControllerAccessor::OnSurfaceChangedImpl - callback need to be supported");
#endif //XCOMPONENT_SUPPORTED
}
void OnSurfaceDestroyedImpl(Ark_XComponentController peer,
                            const Ark_String* surfaceId)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer && peer->controller);
    auto pattern = peer->controller->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto frameNode = pattern->GetHost();
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
    peer->TriggerStartImageAnalyzer(config, outputArgumentForReturningPromise);
#endif //XCOMPONENT_SUPPORTED
}
void StopImageAnalyzerImpl(Ark_XComponentController peer)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer && peer->controller);
    peer->controller->StopImageAnalyzer();
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
    };
    return &XComponentControllerAccessorImpl;
}

struct XComponentControllerPeer {
    virtual ~XComponentControllerPeer() = default;
};
}
