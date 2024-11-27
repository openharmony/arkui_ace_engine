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
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentControllerAccessor {

static void DestroyPeer(XComponentControllerPeer *peer)
{
    CHECK_NULL_VOID(peer);
    delete peer;
}
XComponentControllerPeer* CtorImpl()
{
    auto peer = new XComponentControllerPeer();
    peer->controller = std::make_shared<OHOS::Ace::NG::XComponentControllerNG>();
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(DestroyPeer);
}
void GetXComponentSurfaceIdImpl(XComponentControllerPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->controller);
    auto surfaceId = peer->controller->GetSurfaceId();
    LOGE("XComponentControllerAccessor::GetXComponentSurfaceIdImpl - return surfaceId need to be supported");
}
Ark_NativePointer GetXComponentContextImpl(XComponentControllerPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->controller, 0);
    LOGE("XComponentControllerAccessor::GetXComponentContextImpl - return context object need to be supported");
    return 0;
}
void SetXComponentSurfaceSizeImpl(XComponentControllerPeer* peer,
                                  const Ark_Literal_Number_surfaceHeight_surfaceWidth* value)
{
    //This API is deprecated since API version 12. Should be used SetXComponentSurfaceRectImpl instead.
    CHECK_NULL_VOID(peer && peer->controller);
    CHECK_NULL_VOID(value);
    uint32_t surfaceWidth = static_cast<uint32_t>(Converter::Convert<int32_t>(value->surfaceWidth));
    uint32_t surfaceHeight = static_cast<uint32_t>(Converter::Convert<int32_t>(value->surfaceHeight));
    peer->controller->ConfigSurface(surfaceWidth, surfaceHeight);
}
void SetXComponentSurfaceRectImpl(XComponentControllerPeer* peer,
                                  const Ark_SurfaceRect* rect)
{
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
}
Ark_NativePointer GetXComponentSurfaceRectImpl(XComponentControllerPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->controller, 0);
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    peer->controller->GetSurfaceOffset(offsetX, offsetY);
    peer->controller->GetSurfaceSize(width, height);
    LOGE("XComponentControllerAccessor::GetXComponentSurfaceRectImpl - return value need to be supported");
    return 0;
}
void SetXComponentSurfaceRotationImpl(XComponentControllerPeer* peer,
                                      const Ark_SurfaceRotationOptions* rotationOptions)
{
    CHECK_NULL_VOID(peer && peer->controller);
    CHECK_NULL_VOID(rotationOptions);
    auto lock = Converter::OptConvert<bool>(rotationOptions->lock);
    peer->controller->SetSurfaceRotation(lock.value_or(false));
}
Ark_NativePointer GetXComponentSurfaceRotationImpl(XComponentControllerPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->controller, 0);
    bool lock = peer->controller->GetSurfaceRotation();
    LOGE("XComponentControllerAccessor::GetXComponentSurfaceRotationImpl - return value need to be supported");
    return 0;
}
void OnSurfaceCreatedImpl(XComponentControllerPeer* peer,
                          const Ark_String* surfaceId)
{
    CHECK_NULL_VOID(peer && peer->controller);
    auto pattern = peer->controller->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto frameNode = pattern->GetHost();
    LOGE("XComponentControllerAccessor::OnSurfaceCreatedImpl - callback need to be supported");
}
void OnSurfaceChangedImpl(XComponentControllerPeer* peer,
                          const Ark_String* surfaceId,
                          const Ark_SurfaceRect* rect)
{
    CHECK_NULL_VOID(peer && peer->controller);
    auto pattern = peer->controller->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto frameNode = pattern->GetHost();
    LOGE("XComponentControllerAccessor::OnSurfaceChangedImpl - callback need to be supported");
}
void OnSurfaceDestroyedImpl(XComponentControllerPeer* peer,
                            const Ark_String* surfaceId)
{
    CHECK_NULL_VOID(peer && peer->controller);
    auto pattern = peer->controller->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto frameNode = pattern->GetHost();
    LOGE("XComponentControllerAccessor::OnSurfaceDestroyedImpl - callback need to be supported");
}
Ark_NativePointer StartImageAnalyzerImpl(XComponentControllerPeer* peer,
                                         const Ark_ImageAnalyzerConfig* config)
{
    CHECK_NULL_RETURN(peer && peer->controller, 0);
    LOGE("XComponentControllerAccessor::StartImageAnalyzerImpl - return promise need to be supported");
    return 0;
}
void StopImageAnalyzerImpl(XComponentControllerPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->controller);
    peer->controller->StopImageAnalyzer();
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
