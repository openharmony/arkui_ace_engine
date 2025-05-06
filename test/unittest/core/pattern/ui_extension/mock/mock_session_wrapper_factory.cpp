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

#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"

namespace OHOS::Ace::NG {
RefPtr<SessionWrapper> SessionWrapperFactory::CreateSessionWrapper(SessionType sessionType,
    const WeakPtr<UIExtensionPattern>& hostPattern, int32_t instanceId, bool isTransferringCaller)
{
    if (sessionType == SessionType::UI_EXTENSION_ABILITY || sessionType == SessionType::EMBEDDED_UI_EXTENSION) {
        auto ret = RefPtr<SessionWrapper>();
        return ret;
    }
    return nullptr;
}

RefPtr<SessionWrapper> SessionWrapperFactory::CreateSessionWrapper(
    SessionType sessionType, const SessionCreateParam& sessionCreateParam)
{
    if (sessionType == SessionType::SECURITY_UI_EXTENSION_ABILITY) {
        auto ret = AceType::MakeRefPtr<SecuritySessionWrapperImpl>(
            sessionCreateParam.hostPattern, sessionCreateParam.instanceId,
            sessionCreateParam.isTransferringCaller, sessionType);
        return ret;
    }
    return nullptr;
}
} // namespace OHOS::Ace::NG