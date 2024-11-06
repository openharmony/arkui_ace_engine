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
#include "core/common/container_consts.h"
#include "core/components/web/web_property.h"
#include "core/interfaces/arkoala/utility/ace_engine_types.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class WebControllerPeerImpl : public Referenced {
public:
    WebControllerPeerImpl();
    ~WebControllerPeerImpl() override;

    const RefPtr<WebController>& GetController() const;
    void SetController(const RefPtr<WebController>& webController);

    void TriggerOnInactive();
    void TriggerOnActive();
    void TriggerZoom(float factor);
    void TriggerClearHistory();
    void TriggerLoadData(
        std::string baseUrl, std::string data, std::string mimeType, std::string encoding, std::string historyUrl);
    void TriggerLoadUrl(std::string url, std::map<std::string, std::string>& httpHeaders);
    void TriggerRefresh();
    void TriggerStop();
    void TriggerRequestFocus();
    bool TriggerAccessBackward();
    bool TriggerAccessForward();
    bool TriggerAccessStep(int32_t step);
    void TriggerBackward();
    void TriggerForward();
    RefPtr<WebCookiePeerImpl> TriggerGetCookieManager();
    void TriggerRegisterJavaScriptProxy(const std::string& objectName, const std::vector<std::string>& methodList);
    void TriggerDeleteJavaScriptRegister(std::string objectName);
    int TriggerGetHitTest();
    void TriggerRunJavaScript(std::string jscode, std::function<void(std::string)>&& callback);

private:
    RefPtr<WebController> webController_;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<WebCookiePeerImpl> webCookie_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_WEB_CONTROLLER_PEER_IMPL_H