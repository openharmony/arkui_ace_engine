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

#ifndef OHOS_ACE_FORM_SURFACE_PROXY_H
#define OHOS_ACE_FORM_SURFACE_PROXY_H

#include "hilog_wrapper.h"
#include "iremote_proxy.h"
#include "form_surface_interface.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormSurfaceServiceProxy
 * FormSurfaceServiceProxy.
 */
class FormSurfaceServiceProxy : public IRemoteProxy<IFormSurfaceService> {
public:
    explicit FormSurfaceServiceProxy(const sptr<IRemoteObject>& impl) : IRemoteProxy<IFormSurfaceService>(impl) {}
    ~FormSurfaceServiceProxy() override = default;

    int32_t ProcessAddSurface(const AAFwk::Want& want, const OHOS::AppExecFwk::FormJsInfo& formJsInfo,
        const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode) override;

private:
    static bool WriteInterfaceToken(MessageParcel& data);

    static inline BrokerDelegator<FormSurfaceServiceProxy> delegator_;
};
}  // namespace Ace
}  // namespace OHOS
#endif  // OHOS_ACE_FORM_SURFACE_PROXY_H
