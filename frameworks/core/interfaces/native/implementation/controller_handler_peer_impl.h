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

struct ControllerHandlerPeer {
    struct ChildWindowInfo {
        int32_t parentWebId = -1;
        OHOS::Ace::RefPtr<WebviewControllerPeer> controller;
    };

    OHOS::Ace::RefPtr<OHOS::Ace::WebWindowNewHandler> handler;
    inline static std::unordered_map<int32_t, ChildWindowInfo> controllerMap {};
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CONTROLLER_HANDLER_PEER_IMPL_H