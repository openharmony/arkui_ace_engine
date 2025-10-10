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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_MODEL_STATIC_H

#include <optional>
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/xcomponent/inner_xcomponent_controller.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT XComponentModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, bool isTypedNode);
    static bool SetXComponentController(
        FrameNode* frameNode, const std::shared_ptr<InnerXComponentController>& controller);
    static void SetNativeXComponentHandler(FrameNode* frameNode, const std::function<void(void*)>& handler);
    static void InitParams(FrameNode* frameNode);
    static void SetXComponentId(FrameNode* frameNode, const std::string& id);
    static void SetXComponentType(FrameNode* frameNode, XComponentType type);
    static void MarkBindNative(FrameNode* frameNode);
    static void SetScreenId(FrameNode* frameNode, uint64_t screenId);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_MODEL_STATIC_H
