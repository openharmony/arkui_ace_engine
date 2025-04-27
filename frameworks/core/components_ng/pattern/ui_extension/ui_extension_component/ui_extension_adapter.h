/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UEC_UI_EXTENSION_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UEC_UI_EXTENSION_ADAPTER_H

#include <memory>
#include <string>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"

namespace OHOS::Ace {
struct ModalUIExtensionCallbacks;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT UIExtensionAdapter {
public:
    // for Embedded Component
    static RefPtr<FrameNode> CreateEmbeddedComponent(int32_t nodeId, const RefPtr<OHOS::Ace::WantWrap>& wantWrap);
    static void SetEmbeddedComponentWant(FrameNode* frameNode, const AAFwk::Want& want);
    static void SetEmbeddedComponentOnError(FrameNode* frameNode,
        std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError);
    static void SetEmbeddedComponentOnTerminated(
        FrameNode* frameNode, std::function<void(int32_t, const RefPtr<WantWrap>&)>&& onTerminated);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_UEC_UI_EXTENSION_ADAPTER_H