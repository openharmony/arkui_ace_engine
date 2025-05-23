/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SUEC_SECURITY_UI_EXTENSION_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SUEC_SECURITY_UI_EXTENSION_PROXY_H

#include "base/memory/ace_type.h"
#include "base/want/want_wrap.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"

namespace OHOS::Ace::NG {
class SecurityUIExtensionPattern;
class SecurityUIExtensionProxy : public AceType {
    DECLARE_ACE_TYPE(SecurityUIExtensionProxy, AceType);

public:
    SecurityUIExtensionProxy(const RefPtr<SessionWrapper>& sessionWrapper,
        const RefPtr<SecurityUIExtensionPattern>& pattern);
    void SendData(const RefPtr<WantParamsWrap>& params);
    int32_t SendDataSync(
        const RefPtr<WantParamsWrap>& wantParams, AAFwk::WantParams& reWantParams);
    RefPtr<SecurityUIExtensionPattern> GetPattern() const;

private:
    RefPtr<SessionWrapper> sessionWrapper_;
    WeakPtr<SecurityUIExtensionPattern> pattern_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SUEC_SECURITY_UI_EXTENSION_PROXY_H
