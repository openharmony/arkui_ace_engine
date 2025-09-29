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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CONTROLLER_HANDLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CONTROLLER_HANDLER_PEER_IMPL_H

#include "core/components/web/web_event.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/implementation/webview_controller_peer_impl.h"
#include "core/components_ng/pattern/web/ani/web_model_static.h"

struct ControllerHandlerPeer {
    struct ChildWindowInfo {
        int32_t parentWebId = -1;
        Ark_webview_WebviewController controller = nullptr;
    };

    OHOS::Ace::RefPtr<OHOS::Ace::WebWindowNewHandler> handler;
    inline static std::unordered_map<int32_t, ChildWindowInfo> controllerMap {};

    inline static void ReleaseRef(const Ark_webview_WebviewController controller)
    {
        if (controller->releaseRefFunc) {
            controller->releaseRefFunc();
        }
        delete controller;
    }

    static void DestroyController()
    {
        for (auto iter = controllerMap.begin(); iter != controllerMap.end(); iter++) {
            if (!iter->second.controller) {
                continue;
            }
            ReleaseRef(iter->second.controller);
            iter->second.controller = nullptr;
        }
    }

    static Ark_webview_WebviewController PopController(int32_t id, int32_t* parentId = nullptr)
    {
        auto iter = controllerMap.find(id);
        if (iter == controllerMap.end()) {
            return {};
        }
        if (!iter->second.controller) {
            return {};
        }
        if (parentId) {
            *parentId = iter->second.parentWebId;
        }
        controllerMap.erase(iter);
        return iter->second.controller;
    }

    static bool ExistController(int64_t nativeController, int32_t& parentWebId)
    {
        for (auto iter = controllerMap.begin(); iter != controllerMap.end(); iter++) {
            if (!iter->second.controller) {
                continue;
            }
            auto controller = iter->second.controller;
            if ((controller->getNativePtrFunc) && (nativeController == controller->getNativePtrFunc())) {
                parentWebId = iter->second.parentWebId;
                return true;
            }
        }
        parentWebId = -1;
        return false;
    }

    void SetWebController(const Ark_webview_WebviewController controller)
    {
        if (!controller) {
            return;
        }
        if (!handler) {
            ReleaseRef(controller);
            return;
        }
        int32_t parentNWebId = handler->GetParentNWebId();
        if (parentNWebId == -1) {
            ReleaseRef(controller);
            return;
        }
        if ((!controller->getWebIdFunc) || (!controller->completeWindowNewFunc) ||
            (!controller->getNativePtrFunc)) {
            ReleaseRef(controller);
            OHOS::Ace::NG::WebModelStatic::NotifyPopupWindowResultStatic(parentNWebId, false);
            return;
        }
        int32_t childWebId = controller->getWebIdFunc();
        if ((childWebId == parentNWebId) || (childWebId != -1)) {
            ReleaseRef(controller);
            OHOS::Ace::NG::WebModelStatic::NotifyPopupWindowResultStatic(parentNWebId, false);
            return;
        }
        controllerMap.insert(std::pair<int32_t, ChildWindowInfo>(handler->GetId(),
        {
            .parentWebId = parentNWebId,
            .controller = controller,
        }));
        LOGI("SetWebController set controller success. parentNWebId: %{public}d", parentNWebId);
    }
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CONTROLLER_HANDLER_PEER_IMPL_H
