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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_ARK_UI_RENDER_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_ARK_UI_RENDER_PROXY_H

#include "arkui_render_interface.h"
#include "iremote_proxy.h"

namespace OHOS {
namespace Ace {
/**
 * @class ArkUIRenderProxy
 * ArkUIRenderProxy is used to access form render service.
 */
class ArkUIRenderProxy : public IRemoteProxy<IArkUIRender> {
public:
    explicit ArkUIRenderProxy(const sptr<IRemoteObject> &impl) : IRemoteProxy<IArkUIRender>(impl)
    {}

    virtual ~ArkUIRenderProxy() = default;

    /**
     * @brief Dispatch pointer event. This is sync API.
     * @param formId The formId.
     * @param pointerEvent The pointer event info.
     */
    void DispatchFormEvent(
        int64_t formId, const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent);

private:
    template<typename T>
    int32_t GetParcelableInfos(MessageParcel &reply, std::vector<T> &parcelableInfos);
    static bool WriteInterfaceToken(MessageParcel &data);

    static inline BrokerDelegator<ArkUIRenderProxy> delegator_;
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_FORM_RESOURCE_ARK_UI_RENDER_PROXY_H
