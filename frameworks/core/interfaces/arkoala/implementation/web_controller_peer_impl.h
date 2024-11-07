/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_WEB_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_WEB_CONTROLLER_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/common/container_consts.h"
#include "core/components/web/web_property.h"
#include "core/interfaces/arkoala/utility/ace_engine_types.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class WebControllerPeerImpl : public Referenced {
public:
    WebControllerPeerImpl()
    {
        instanceId_ = Container::CurrentId();
    }

    ~WebControllerPeerImpl() override
    {
        if (webCookie_) {
            webCookie_->DecRefCount();
        }
    }

    const RefPtr<WebController>& GetController() const
    {
        return webController_;
    }

    void SetController(const RefPtr<WebController>& webController)
    {
        webController_ = webController;
    }

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    RefPtr<WebCookiePeerImpl> GetCookieManager()
    {
        ContainerScope scope(instanceId_);
        if (webController_) {
            if (!webController_->GetCookieManager()) {
                return nullptr;
            }
            if (webCookie_ == nullptr) {
                webCookie_ = Referenced::MakeRefPtr<WebCookiePeerImpl>();
                webCookie_->IncRefCount();
            }
        }
        return webCookie_;
    }

private:
    RefPtr<WebController> webController_;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<WebCookiePeerImpl> webCookie_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_WEB_CONTROLLER_PEER_IMPL_H