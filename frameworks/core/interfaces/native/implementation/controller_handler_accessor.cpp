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
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/web_model_ng.h"
#endif // WEB_SUPPORTED
#include "core/interfaces/native/implementation/controller_handler_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ControllerHandlerAccessor {
void DestroyPeerImpl(Ark_ControllerHandler peer)
{
    delete peer;
}
Ark_ControllerHandler CtorImpl()
{
    return new ControllerHandlerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetWebControllerImpl(Ark_ControllerHandler peer,
                          Ark_WebviewController controller)
{
#ifdef WEB_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->handler);

    int32_t parentNWebId = peer->handler->GetParentNWebId();
    if (parentNWebId == -1) {
        return;
    }

    if (controller == nullptr) {
        // WebModelNG::NotifyPopupWindowResultStatic(parentNWebId, false);
        return;
    }

    int32_t childWebId = controller->nwebId;
    if (childWebId == parentNWebId || childWebId != -1) {
        // WebModelNG::NotifyPopupWindowResultStatic(parentNWebId, false);
        return;
    }
    ControllerHandlerPeer::ChildWindowInfo info { parentNWebId, Referenced::Claim(controller) };
    ControllerHandlerPeer::controllerMap.insert(std::pair<int32_t, ControllerHandlerPeer::ChildWindowInfo>(
        peer->handler->GetId(), info));
#endif // WEB_SUPPORTED
}
} // ControllerHandlerAccessor
const GENERATED_ArkUIControllerHandlerAccessor* GetControllerHandlerAccessor()
{
    static const GENERATED_ArkUIControllerHandlerAccessor ControllerHandlerAccessorImpl {
        ControllerHandlerAccessor::DestroyPeerImpl,
        ControllerHandlerAccessor::CtorImpl,
        ControllerHandlerAccessor::GetFinalizerImpl,
        ControllerHandlerAccessor::SetWebControllerImpl,
    };
    return &ControllerHandlerAccessorImpl;
}

struct ControllerHandlerPeer {
    virtual ~ControllerHandlerPeer() = default;
};
}
