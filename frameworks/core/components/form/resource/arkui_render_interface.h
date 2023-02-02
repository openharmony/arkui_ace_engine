/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_ARK_UI_RENDER_INTERFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_ARK_UI_RENDER_INTERFACE_H

#include <vector>

#include "iremote_broker.h"

namespace OHOS {
namespace MMI {
class PointerEvent;
} // namespace MMI
namespace Ace {
/**
 * @class IArkUIRender
 * IArkUIRender interface is used to access form render service.
 */
class IArkUIRender : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.appexecfwk.ArkUIRender");
    /**
     * @brief Dispatch pointer event. This is sync API.
     * @param pointerEvent The pointer event info.
     */
    virtual void DispatchFormEvent(
        int64_t formId, const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) = 0;

    enum class Message {
        // ipc id 1-1000 for kit
        // ipc id 1001-2000 for DMS
        // ipc id 2001-3000 for tools
        // ipc id for form mgr (3001)
        // ipc id for form provider (3051)
        // ipc id for form form render (3101)
        // ipc id for form arkui render (3151)
        // ipc id for form supply (3201)
        // ipc id for form host (3681)
        FORM_RENDER_DISPATCH_FORM_EVENT = 3151,
    };
};
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_ARK_UI_RENDER_INTERFACE_H
