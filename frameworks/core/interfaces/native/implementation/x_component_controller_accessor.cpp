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
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetXComponentSurfaceIdImpl(Ark_XComponentController peer)
{
    return {};
}
Ark_CustomObject GetXComponentContextImpl(Ark_XComponentController peer)
{
    return {};
}
void SetXComponentSurfaceSizeImpl(Ark_XComponentController peer,
                                  const Ark_Literal_Number_surfaceHeight_surfaceWidth* value)
{
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
void OnSurfaceCreatedImpl(Ark_XComponentController peer,
                          const Ark_String* surfaceId)
{
}
void OnSurfaceChangedImpl(Ark_XComponentController peer,
                          const Ark_String* surfaceId,
                          const Ark_SurfaceRect* rect)
{
}
void OnSurfaceDestroyedImpl(Ark_XComponentController peer,
                            const Ark_String* surfaceId)
{
}
void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_XComponentController peer,
                            const Ark_ImageAnalyzerConfig* config,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void StopImageAnalyzerImpl(Ark_XComponentController peer)
{
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

}
