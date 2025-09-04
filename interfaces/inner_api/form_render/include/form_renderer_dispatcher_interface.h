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

#include "base/utils/macros.h"
#include "interfaces/inner_api/ace/serialized_gesture.h"
#include "form_surface_info.h"

namespace OHOS::Rosen {
class RSTransaction;
}
namespace OHOS {
namespace Ace {
/**
 * @class IFormRendererDispatcher
 * IFormRendererDispatcher interface is used to form render dispatcher.
 */
class ACE_EXPORT IFormRendererDispatcher : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.ace.FormRendererDispatcher")

    IFormRendererDispatcher() = default;
    ~IFormRendererDispatcher() override = default;
    /**
     * @brief Dispatcher pointer event.
     * @param pointerEvent The pointer event info.
     */
    virtual void DispatchPointerEvent(
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent,
        SerializedGesture& serializedGesture) = 0;
    /**
     * @brief Set AllowUpdate.
     * @param allowUpdate The allowUpdate.
     */
    virtual void SetAllowUpdate(bool allowUpdate) = 0;
    virtual void SetMultiInstanceEnabled(bool isMultiInstanceEnabled) = 0;

    virtual void DispatchSurfaceChangeEvent(const OHOS::AppExecFwk::FormSurfaceInfo& formSurfaceInfo,
        uint32_t reason = 0, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction = nullptr) = 0;
    virtual void SetObscured(bool isObscured) = 0;

    virtual void OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId, int64_t accessibilityId) = 0;
    virtual void OnAccessibilityChildTreeDeregister() = 0;
    virtual void OnAccessibilityDumpChildInfo(
        const std::vector<std::string>& params, std::vector<std::string>& info) = 0;
    virtual void OnAccessibilityTransferHoverEvent(float pointX, float pointY, int32_t sourceType,
        int32_t eventType, int64_t timeMs) = 0;
    virtual void OnNotifyDumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info) = 0;

    enum Message : uint32_t {
        DISPATCH_POINTER_EVENT = 1,
        SET_ALLOW_UPDATE,
        DISPATCH_SURFACE_CHANGE_EVENT,
        SET_OBSCURED,
        ACCESSIBILITY_CHILD_TREE_REGISTER,
        ACCESSIBILITY_CHILD_TREE_DEREGISTER,
        ACCESSIBILITY_DUMP_CHILD_INFO,
        ACCESSIBILITY_TRANSFER_HOVER_EVENT,
        NOTIFY_DUMP_INFO,
        SET_MULTI_INSTANCE_ENABLED
    };
};
}  // namespace Ace
}  // namespace OHOS
#endif  // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_INTERFACE_H
