/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentControllerAccessor {
XComponentControllerPeer* CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void GetXComponentSurfaceIdImpl(XComponentControllerPeer* peer)
{
}
Ark_NativePointer GetXComponentContextImpl(XComponentControllerPeer* peer)
{
    return 0;
}
void SetXComponentSurfaceSizeImpl(XComponentControllerPeer* peer,
                                  const Ark_Literal_Number_surfaceHeight_surfaceWidth* value)
{
}
void SetXComponentSurfaceRectImpl(XComponentControllerPeer* peer,
                                  const Ark_SurfaceRect* rect)
{
}
Ark_NativePointer GetXComponentSurfaceRectImpl(XComponentControllerPeer* peer)
{
    return 0;
}
void SetXComponentSurfaceRotationImpl(XComponentControllerPeer* peer,
                                      const Ark_SurfaceRotationOptions* rotationOptions)
{
}
Ark_NativePointer GetXComponentSurfaceRotationImpl(XComponentControllerPeer* peer)
{
    return 0;
}
void OnSurfaceCreatedImpl(XComponentControllerPeer* peer,
                          const Ark_String* surfaceId)
{
}
void OnSurfaceChangedImpl(XComponentControllerPeer* peer,
                          const Ark_String* surfaceId,
                          const Ark_SurfaceRect* rect)
{
}
void OnSurfaceDestroyedImpl(XComponentControllerPeer* peer,
                            const Ark_String* surfaceId)
{
}
Ark_NativePointer StartImageAnalyzerImpl(XComponentControllerPeer* peer,
                                         const Ark_ImageAnalyzerConfig* config)
{
    return 0;
}
void StopImageAnalyzerImpl(XComponentControllerPeer* peer)
{
}
} // XComponentControllerAccessor
const GENERATED_ArkUIXComponentControllerAccessor* GetXComponentControllerAccessor()
{
    static const GENERATED_ArkUIXComponentControllerAccessor XComponentControllerAccessorImpl {
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
