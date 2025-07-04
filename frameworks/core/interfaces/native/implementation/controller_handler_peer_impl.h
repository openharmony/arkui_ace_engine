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
#include "core/interfaces/native/implementation/webview_controller_peer_impl.h"
#include "core/interfaces/ani/ani_api.h"
#include "core/components_ng/pattern/web/ani/web_model_static.h"

struct ControllerHandlerPeer {
    struct ChildWindowInfo {
        int32_t parentWebId = -1;
        OHOS::Ace::RefPtr<WebviewControllerPeer> controller = nullptr;
        WebviewControllerInfo controllerInfo = {};
    };

    OHOS::Ace::RefPtr<OHOS::Ace::WebWindowNewHandler> handler;
    inline static std::unordered_map<int32_t, ChildWindowInfo> controllerMap {};

    inline static void ReleaseRef(const std::function<void()>& releaseRefFunc)
    {
        if (releaseRefFunc) {
            releaseRefFunc();
        }
    }

    static WebviewControllerInfo PopController(int32_t id, int32_t* parentId = nullptr)
    {
        auto iter = controllerMap.find(id);
        if (iter == controllerMap.end()) {
            return {};
        }
        auto controllerInfo = iter->second.controllerInfo;
        if (parentId) {
            *parentId = iter->second.parentWebId;
        }
        controllerMap.erase(iter);
        return controllerInfo;
    }

    static bool ExistController(int64_t nativeController, int32_t& parentWebId)
    {
        for (auto iter = controllerMap.begin(); iter != controllerMap.end(); iter++) {
            if ((iter->second.controllerInfo.getNativePtrFunc) &&
                (nativeController == iter->second.controllerInfo.getNativePtrFunc())) {
                parentWebId = iter->second.parentWebId;
                return true;
            }
        }
        parentWebId = -1;
        return false;
    }

    void SetWebController(const WebviewControllerInfo& controllerInfo)
    {
        if (!handler) {
            ReleaseRef(controllerInfo.releaseRefFunc);
            return;
        }
        int32_t parentNWebId = handler->GetParentNWebId();
        if (parentNWebId == -1) {
            ReleaseRef(controllerInfo.releaseRefFunc);
            return;
        }
        if ((!controllerInfo.getWebIdFunc) || (!controllerInfo.completeWindowNewFunc) ||
            (!controllerInfo.getNativePtrFunc)) {
            ReleaseRef(controllerInfo.releaseRefFunc);
            OHOS::Ace::NG::WebModelStatic::NotifyPopupWindowResultStatic(parentNWebId, false);
            return;
        }
        int32_t childWebId = controllerInfo.getWebIdFunc();
        if ((childWebId == parentNWebId) || (childWebId != -1)) {
            ReleaseRef(controllerInfo.releaseRefFunc);
            OHOS::Ace::NG::WebModelStatic::NotifyPopupWindowResultStatic(parentNWebId, false);
            return;
        }
        controllerMap.insert(std::pair<int32_t, ChildWindowInfo>(handler->GetId(),
        {
            .parentWebId = parentNWebId,
            .controller = nullptr,
            .controllerInfo = controllerInfo,
        }));
    }
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CONTROLLER_HANDLER_PEER_IMPL_H