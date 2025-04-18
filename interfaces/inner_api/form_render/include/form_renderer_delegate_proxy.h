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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_PROXY_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_PROXY_H

#include "form_renderer_delegate_interface.h"
#include "iremote_proxy.h"

#include "base/utils/macros.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormRendererDelegateProxy
 * FormRendererDelegateProxy is used to access form renderer delegate.
 */
class ACE_EXPORT FormRendererDelegateProxy : public IRemoteProxy<IFormRendererDelegate> {
public:
    explicit FormRendererDelegateProxy(const sptr<IRemoteObject>& impl);
    ~FormRendererDelegateProxy() override = default;

    int32_t OnSurfaceCreate(const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
        const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want) override;

    int32_t OnSurfaceReuse(
        uint64_t surfaceId, const OHOS::AppExecFwk::FormJsInfo& formJsInfo, const AAFwk::Want& want) override;

    int32_t OnSurfaceDetach(uint64_t surfaceId) override;

    int32_t OnSurfaceRelease(uint64_t surfaceId) override;

    int32_t OnActionEvent(const std::string& action) override;

    int32_t OnError(const std::string& code, const std::string& msg) override;

    int32_t OnSurfaceChange(float width, float height, float borderWidth = 0.0) override;

    int32_t OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos) override;

    int32_t OnGetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo) override;

    int32_t OnCheckManagerDelegate(bool &checkFlag) override;

    int32_t OnUpdateFormDone(const int64_t formId) override;
private:
    static bool WriteInterfaceToken(MessageParcel& data);
    int32_t SendRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option);

    static inline BrokerDelegator<FormRendererDelegateProxy> delegator_;
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DELEGATE_PROXY_H
