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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_PROXY_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_PROXY_H

#include "form_renderer_dispatcher_interface.h"
#include "iremote_proxy.h"

#include "base/utils/macros.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormRendererDispatcherProxy
 * FormRendererDispatcherProxy is used to access form render dispatcher.
 */
class ACE_EXPORT FormRendererDispatcherProxy : public IRemoteProxy<IFormRendererDispatcher> {
public:
    explicit FormRendererDispatcherProxy(const sptr<IRemoteObject>& impl);
    virtual ~FormRendererDispatcherProxy() = default;

    void DispatchPointerEvent(
        const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, SerializedGesture& serializedGesture) override;

    void SetAllowUpdate(bool allowUpdate) override;

    void DispatchSurfaceChangeEvent(float width, float height) override;

    void SetVisibleChange(bool isVisible) override;
private:
    template<typename T>
    int32_t GetParcelableInfos(MessageParcel &reply, std::vector<T> &parcelableInfos);
    static bool WriteInterfaceToken(MessageParcel &data);

    static inline BrokerDelegator<FormRendererDispatcherProxy> delegator_;
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_PROXY_H
