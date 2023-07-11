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

#include "core/components_ng/pattern/ui_extension/ui_extension_proxy.h"

#include "session/host/include/extension_session.h"

#include "adapter/ohos/osal/want_wrap_ohos.h"

namespace OHOS::Ace::NG {
UIExtensionProxy::UIExtensionProxy(const sptr<Rosen::Session>& session): session_(session) {}

void UIExtensionProxy::SendData(const RefPtr<WantParamsWrap>& wantParams)
{
    if (session_) {
        sptr<Rosen::ExtensionSession> extensionSession(static_cast<Rosen::ExtensionSession*>(session_.GetRefPtr()));
        auto params = DynamicCast<WantParamsWrapOhos>(wantParams)->GetWantParams();
        extensionSession->TransferComponentData(params);
    }
}
} // namespace OHOS::Ace::NG
