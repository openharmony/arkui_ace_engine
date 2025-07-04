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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentControllerAccessor {
void DestroyPeerImpl(Ark_XComponentController peer)
{
}
Ark_XComponentController CtorImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<XComponentControllerPeerImpl>();
    peerImpl->IncRefCount();
#ifdef XCOMPONENT_SUPPORTED
    peerImpl->controller = std::make_shared<XComponentControllerNG>();
#endif //XCOMPONENT_SUPPORTED
    return reinterpret_cast<Ark_XComponentController>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetXComponentSurfaceIdImpl(Ark_XComponentController peer)
{
    return {};
}
Ark_Object GetXComponentContextImpl(Ark_XComponentController peer)
{
    return {};
}
void SetXComponentSurfaceRectImpl(Ark_XComponentController peer,
                                  const Ark_SurfaceRect* rect)
{
}
Ark_SurfaceRect GetXComponentSurfaceRectImpl(Ark_XComponentController peer)
{
    return {};
}
void SetXComponentSurfaceRotationImpl(Ark_XComponentController peer,
                                      const Ark_SurfaceRotationOptions* rotationOptions)
{
}
Ark_SurfaceRotationOptions GetXComponentSurfaceRotationImpl(Ark_XComponentController peer)
{
    return {};
}
void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_XComponentController peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    peer->TriggerStartImageAnalyzer(vmContext, asyncWorker, config, outputArgumentForReturningPromise);
#endif //XCOMPONENT_SUPPORTED
}
void StopImageAnalyzerImpl(Ark_XComponentController peer)
{
}
Callback_String_Void GetOnSurfaceCreatedImpl(Ark_XComponentController peer)
{
    return {};
}
void SetOnSurfaceCreatedImpl(Ark_XComponentController peer,
                             const Callback_String_Void* onSurfaceCreated)
{
}
Callback_String_SurfaceRect_Void GetOnSurfaceChangedImpl(Ark_XComponentController peer)
{
    return {};
}
void SetOnSurfaceChangedImpl(Ark_XComponentController peer,
                             const Callback_String_SurfaceRect_Void* onSurfaceChanged)
{
}
Callback_String_Void GetOnSurfaceDestroyedImpl(Ark_XComponentController peer)
{
    return {};
}
void SetOnSurfaceDestroyedImpl(Ark_XComponentController peer,
                               const Callback_String_Void* onSurfaceDestroyed)
{
}
} // XComponentControllerAccessor
const GENERATED_ArkUIXComponentControllerAccessor* GetXComponentControllerAccessor()
{
    static const GENERATED_ArkUIXComponentControllerAccessor XComponentControllerAccessorImpl {
        XComponentControllerAccessor::DestroyPeerImpl,
        XComponentControllerAccessor::ConstructImpl,
        XComponentControllerAccessor::GetFinalizerImpl,
        XComponentControllerAccessor::GetXComponentSurfaceIdImpl,
        XComponentControllerAccessor::GetXComponentContextImpl,
        XComponentControllerAccessor::SetXComponentSurfaceRectImpl,
        XComponentControllerAccessor::GetXComponentSurfaceRectImpl,
        XComponentControllerAccessor::SetXComponentSurfaceRotationImpl,
        XComponentControllerAccessor::GetXComponentSurfaceRotationImpl,
        XComponentControllerAccessor::StartImageAnalyzerImpl,
        XComponentControllerAccessor::StopImageAnalyzerImpl,
        XComponentControllerAccessor::GetOnSurfaceCreatedImpl,
        XComponentControllerAccessor::SetOnSurfaceCreatedImpl,
        XComponentControllerAccessor::GetOnSurfaceChangedImpl,
        XComponentControllerAccessor::SetOnSurfaceChangedImpl,
        XComponentControllerAccessor::GetOnSurfaceDestroyedImpl,
        XComponentControllerAccessor::SetOnSurfaceDestroyedImpl,
    };
    return &XComponentControllerAccessorImpl;
}

}
