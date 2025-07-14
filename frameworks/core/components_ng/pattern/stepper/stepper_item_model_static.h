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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_ITEM_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_ITEM_MODEL_STATIC_H

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT StepperItemModelStatic {
public:
    enum class ItemState {
        NORMAL,
        DISABLED,
        WAITING,
        SKIP
    };

    static const std::map<ItemState, std::string> ITEM_STATE;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetNextLabel(FrameNode* frameNode, const std::string& rightLabel);
    static void ResetNextLabel(FrameNode* frameNode);
    static void SetPrevLabel(FrameNode* frameNode, const std::string& leftLabel);
    static void ResetPrevLabel(FrameNode* frameNode);
    static void SetStatus(FrameNode* frameNode, const std::optional<std::string>& labelStatus);
    static void ResetStatus(FrameNode* frameNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_ITEM_MODEL_STATIC_H