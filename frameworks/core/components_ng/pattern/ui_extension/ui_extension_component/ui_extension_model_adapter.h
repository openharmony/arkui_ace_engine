/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_NG_H

#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "base/want/want_wrap.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"

namespace OHOS::Ace::NG {
class UIExtensionProxy;

class ACE_FORCE_EXPORT UIExtensionAdapter : public AceType {
    DECLARE_ACE_TYPE(UIExtensionAdapter, AceType);
public:
    static RefPtr<FrameNode> CreateFrameNode(
        int32_t nodeId, NG::SessionType sessionType = NG::SessionType::UI_EXTENSION_ABILITY);
    static void UpdateUecConfig(FrameNode* frameNode, bool isTransferringCaller, bool densityDpi);
    static void UpdateWant(FrameNode* frameNode, const AAFwk::Want& want);
    static void SetOnError(FrameNode* frameNode,
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError);
    static void SetOnReceive(FrameNode* frameNode,
        std::function<void(const AAFwk::WantParams&)>&& onReceive);
    static void SetOnRelease(FrameNode* frameNode, std::function<void(int32_t)>&& onRelease);
    static void SetOnRemoteReady(FrameNode* frameNode,
        std::function<void(const RefPtr<UIExtensionProxy>&)>&& onRemoteReady);
    static void SetOnResult(FrameNode* frameNode, std::function<void(int32_t, const AAFwk::Want&)>&& onResult);
    static void SetOnTerminated(FrameNode* frameNode,
        std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UI_EXTENSION_MODEL_NG_H
 