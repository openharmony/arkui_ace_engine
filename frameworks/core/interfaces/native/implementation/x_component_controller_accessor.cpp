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
#endif // XCOMPONENT_SUPPORTED
#include "arkoala_api_generated.h"

#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace XComponentControllerNativeAccessor {
void DestroyPeerImpl(Ark_XComponentControllerNative peer)
{
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    peerImpl->DecRefCount();
}
Ark_XComponentControllerNative ConstructImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<XComponentControllerNativePeerImpl>();
    peerImpl->IncRefCount();
#ifdef XCOMPONENT_SUPPORTED
    peerImpl->controller = std::make_shared<XComponentControllerNG>();
#endif //XCOMPONENT_SUPPORTED
    return reinterpret_cast<Ark_XComponentControllerNative>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetXComponentSurfaceIdImpl(Ark_XComponentControllerNative peer)
{
    Ark_String arkSurfaceId = {};
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(peerImpl->controller, {});
    auto surfaceId = peerImpl->controller->GetSurfaceId();
    arkSurfaceId = Converter::ArkValue<Ark_String>(surfaceId, Converter::FC);
#endif //XCOMPONENT_SUPPORTED
    return arkSurfaceId;
}
void SetXComponentSurfaceRectImpl(Ark_XComponentControllerNative peer,
                                  const Ark_SurfaceRect* rect)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(peerImpl->controller);
    CHECK_NULL_VOID(rect);
    auto offsetX = Converter::OptConvert<float>(rect->offsetX);
    auto offsetY = Converter::OptConvert<float>(rect->offsetY);
    auto surfaceWidth = Converter::Convert<float>(rect->surfaceWidth);
    auto surfaceHeight = Converter::Convert<float>(rect->surfaceHeight);
    if (surfaceWidth <= 0 || surfaceHeight <= 0) {
        return;
    }
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
        peerImpl->controller->ClearIdealSurfaceOffset(false);
    }
    peerImpl->controller->UpdateSurfaceBounds();
#endif //XCOMPONENT_SUPPORTED
}
Ark_SurfaceRect GetXComponentSurfaceRectImpl(Ark_XComponentControllerNative peer)
{
    Ark_SurfaceRect rect;
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(peerImpl->controller, {});
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    peerImpl->controller->GetSurfaceOffset(offsetX, offsetY);
    peerImpl->controller->GetSurfaceSize(width, height);
    rect.offsetX = Converter::ArkValue<Opt_Float64>(offsetX);
    rect.offsetY = Converter::ArkValue<Opt_Float64>(offsetY);
    rect.surfaceWidth = Converter::ArkValue<Ark_Float64>(width);
    rect.surfaceHeight = Converter::ArkValue<Ark_Float64>(height);
#endif //XCOMPONENT_SUPPORTED
    return rect;
}
void SetXComponentSurfaceRotationImpl(Ark_XComponentControllerNative peer,
                                      const Ark_SurfaceRotationOptions* rotationOptions)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(peerImpl->controller);
    CHECK_NULL_VOID(rotationOptions);
    auto lock = Converter::OptConvert<bool>(rotationOptions->lock);
    peerImpl->controller->SetSurfaceRotation(lock.value_or(false));
#endif //XCOMPONENT_SUPPORTED
}
Ark_SurfaceRotationOptions GetXComponentSurfaceRotationImpl(Ark_XComponentControllerNative peer)
{
    Ark_SurfaceRotationOptions rotationOptions;
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer, {});
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, {});
    CHECK_NULL_RETURN(peerImpl->controller, {});
    bool lock = peerImpl->controller->GetSurfaceRotation();
    rotationOptions.lock = Converter::ArkValue<Opt_Boolean>(lock);
#endif //XCOMPONENT_SUPPORTED
    return rotationOptions;
}
void StopImageAnalyzerImpl(Ark_XComponentControllerNative peer)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(peerImpl->controller);
    peerImpl->controller->StopImageAnalyzer();
#endif //XCOMPONENT_SUPPORTED
}
Opt_drawing_Canvas LockCanvasImpl(Ark_XComponentControllerNative peer)
{
    auto invalid = Converter::ArkValue<Opt_drawing_Canvas>();
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_RETURN(peer, invalid);
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, invalid);
    auto canvas = peerImpl->GetCanvas();
    CHECK_NULL_RETURN(canvas, invalid);
    return Converter::ArkValue<Opt_drawing_Canvas>(canvas);
#else
    return invalid;
#endif // XCOMPONENT_SUPPORTED
}

void UnlockCanvasAndPostImpl(Ark_XComponentControllerNative peer, Ark_drawing_Canvas canvas)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(canvas);
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(peerImpl->controller);
    peerImpl->controller->UnlockCanvasAndPost(reinterpret_cast<RSCanvas*>(canvas));
#endif // XCOMPONENT_SUPPORTED
}

void SetXComponentSurfaceConfigImpl(Ark_XComponentControllerNative peer, const Ark_SurfaceConfig* config)
{
#ifdef XCOMPONENT_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(config);
    auto peerImpl = reinterpret_cast<XComponentControllerNativePeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    CHECK_NULL_VOID(peerImpl->controller);
    auto isOpaque = Converter::OptConvert<bool>(config->isOpaque);
    peerImpl->controller->SetSurfaceConfig(isOpaque.value_or(false));
#endif // XCOMPONENT_SUPPORTED
}
} // XComponentControllerAccessor
const GENERATED_ArkUIXComponentControllerNativeAccessor* GetXComponentControllerNativeAccessor()
{
    static const GENERATED_ArkUIXComponentControllerNativeAccessor XComponentControllerAccessorImpl {
        XComponentControllerNativeAccessor::DestroyPeerImpl,
        XComponentControllerNativeAccessor::ConstructImpl,
        XComponentControllerNativeAccessor::GetFinalizerImpl,
        XComponentControllerNativeAccessor::GetXComponentSurfaceIdImpl,
        XComponentControllerNativeAccessor::SetXComponentSurfaceRectImpl,
        XComponentControllerNativeAccessor::GetXComponentSurfaceRectImpl,
        XComponentControllerNativeAccessor::SetXComponentSurfaceRotationImpl,
        XComponentControllerNativeAccessor::GetXComponentSurfaceRotationImpl,
        XComponentControllerNativeAccessor::StopImageAnalyzerImpl,
        XComponentControllerNativeAccessor::LockCanvasImpl,
        XComponentControllerNativeAccessor::UnlockCanvasAndPostImpl,
        XComponentControllerNativeAccessor::SetXComponentSurfaceConfigImpl,
    };
    return &XComponentControllerAccessorImpl;
}

struct XComponentControllerPeer {
    virtual ~XComponentControllerPeer() = default;
};
}
