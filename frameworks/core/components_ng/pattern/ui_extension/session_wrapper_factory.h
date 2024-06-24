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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_FACTORY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_FACTORY_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_pattern.h"

namespace OHOS::Ace::NG {
struct SessionCreateParam {
    WeakPtr<SecurityUIExtensionPattern> hostPattern = nullptr;
    int32_t instanceId = 0;
    bool isTransferringCaller = false;
};

class SessionWrapperFactory {
public:
    static RefPtr<SessionWrapper> CreateSessionWrapper(SessionType sessionType,
        const WeakPtr<UIExtensionPattern>& hostPattern, int32_t instanceId, bool isTransferringCaller);
    static RefPtr<SessionWrapper> CreateSessionWrapper(
        SessionType sessionType, const SessionCreateParam& sessionCreateParam);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_SESSION_WRAPPER_FACTORY_H
