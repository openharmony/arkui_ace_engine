/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "xcomponent_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#ifdef XCOMPONENT_SUPPORTED
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_static.h"
#endif
#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"

namespace OHOS::Ace::NG {

void SetXComponentInitParameters(ArkUINodeHandle node, const ArkUIXComponentParams& params)
{
#ifdef XCOMPONENT_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    if (params.type == static_cast<ArkUI_Int32>(XComponentType::SURFACE) ||
        params.type == static_cast<ArkUI_Int32>(XComponentType::TEXTURE)) {
        XComponentModelStatic::SetXComponentType(frameNode, static_cast<XComponentType>(params.type));
    }
    auto controllerPeerImpl = reinterpret_cast<GeneratedModifier::XComponentControllerPeerImpl*>(params.controller);
    bool shouldUpdateController = false;
    if (controllerPeerImpl) {
        auto controller = controllerPeerImpl->controller;
        shouldUpdateController = XComponentModelStatic::SetXComponentController(frameNode, controller);
    }
    if (params.nativeHandler) {
        XComponentModelStatic::SetXComponentId(frameNode, params.id);
        XComponentModelStatic::SetNativeXComponentHandler(frameNode, params.nativeHandler);
        return XComponentModelStatic::InitParams(frameNode);
    }
    if (shouldUpdateController) {
        auto onSurfaceCreatedEvent = [onSurfaceCreated = params.onSurfaceCreated]
            (const std::string& surfaceId, const std::string xcomponentId) {
            CHECK_NULL_VOID(onSurfaceCreated);
            onSurfaceCreated(surfaceId);
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] ControllerOnCreated surfaceId:%{public}s",
                xcomponentId.c_str(), surfaceId.c_str());
        };
        auto onSurfaceChangedEvent = [onSurfaceChanged = params.onSurfaceChanged]
            (const std::string& surfaceId, const RectF& rect) {
            CHECK_NULL_VOID(onSurfaceChanged);
            onSurfaceChanged(surfaceId, rect.Width(), rect.Height(), rect.Left(), rect.Top());
        };
        auto onSurfaceDestroyedEvent = [onSurfaceDestroyed = params.onSurfaceDestroyed]
            (const std::string& surfaceId, const std::string xcomponentId) {
            CHECK_NULL_VOID(onSurfaceDestroyed);
            onSurfaceDestroyed(surfaceId);
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] ControllerOnDestroyed surfaceId:%{public}s",
                xcomponentId.c_str(), surfaceId.c_str());
        };
        XComponentModelNG::SetControllerOnCreated(frameNode, std::move(onSurfaceCreatedEvent));
        XComponentModelNG::SetControllerOnChanged(frameNode, std::move(onSurfaceChangedEvent));
        XComponentModelNG::SetControllerOnDestroyed(frameNode, std::move(onSurfaceDestroyedEvent));
    }
    XComponentModelStatic::InitParams(frameNode);
#endif
}

void SetScreenId(ArkUINodeHandle node, uint64_t screenId)
{
#ifdef XCOMPONENT_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    XComponentModelStatic::SetScreenId(frameNode, screenId);
#endif
}

void MarkBindNative(ArkUINodeHandle node)
{
#ifdef XCOMPONENT_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    XComponentModelStatic::MarkBindNative(frameNode);
#endif
}

const ArkUIAniXComponentModifier* GetXComponentAniModifier()
{
    static const ArkUIAniXComponentModifier impl = {
        .setXComponentInitParameters = OHOS::Ace::NG::SetXComponentInitParameters,
        .setScreenId = OHOS::Ace::NG::SetScreenId,
        .markBindNative = OHOS::Ace::NG::MarkBindNative,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
