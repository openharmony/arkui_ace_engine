/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_UI_EXTENSION_SECURITY_UI_EXTENSION_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_UI_EXTENSION_SECURITY_UI_EXTENSION_STATIC_H

#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "base/want/want_wrap.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"

namespace OHOS::Ace::NG {
class SecurityUIExtensionProxy;

class ACE_FORCE_EXPORT SecurityUIExtensionStatic : public AceType {
    DECLARE_ACE_TYPE(SecurityUIExtensionStatic, AceType);
public:
    static RefPtr<FrameNode> CreateSecurityUIExtensionComponent(int32_t nodeId, NG::SessionType sessionType);
    static void UpdateSecurityUecConfig(
        FrameNode* frameNode, bool isTransferringCaller, bool densityDpi, bool isWindowModeFollowHost,
        const std::map<PlaceholderType, RefPtr<NG::FrameNode>>& placeholderMap);
    static void UpdateSecurityWant(FrameNode* frameNode, const AAFwk::Want& want);
    static void SetSecurityOnError(FrameNode* frameNode,
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError);
    static void SetSecurityOnReceive(FrameNode* frameNode,
        std::function<void(const AAFwk::WantParams&)>&& onReceive);
    static void SetSecurityOnRelease(FrameNode* frameNode, std::function<void(int32_t)>&& onRelease);
    static void SetSecurityOnRemoteReady(FrameNode* frameNode,
        std::function<void(const RefPtr<SecurityUIExtensionProxy>&)>&& onRemoteReady);
    static void SetSecurityOnResult(FrameNode* frameNode, std::function<void(int32_t, const AAFwk::Want&)>&& onResult);
    static void SetSecurityOnTerminated(FrameNode* frameNode,
        std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated);
    static void SetSecurityOnDrawReady(FrameNode* frameNode, std::function<void()>&& onDrawReady);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_UI_EXTENSION_SECURITY_UI_EXTENSION_STATIC_H