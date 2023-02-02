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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_INTERFACE_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_INTERFACE_H

#include <ipc_types.h>
#include <iremote_broker.h>

#include "pointer_event.h"

namespace OHOS {
namespace Ace {
/**
 * @class IFormRendererDispatcher
 * IFormRendererDispatcher interface is used to form render dispatcher.
 */
class IFormRendererDispatcher : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.FormRendererDispatcher")

    IFormRendererDispatcher() = default;
    ~IFormRendererDispatcher() override = default;
    /**
     * @brief Dispatcher pointer event.
     * @param pointerEvent The pointer event info.
     */
    virtual void DispatchPointerEvent(
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent) = 0;

    enum Message : uint32_t {
        DISPATCH_POINTER_EVENT = 1,
    };
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_INTERFACE_H
