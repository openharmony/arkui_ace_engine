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

#include "core/components_ng/event/response_ctrl.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
bool ResponseCtrl::ShouldResponse(const WeakPtr<NG::FrameNode>& frameNode)
{
    if (state_ != MonopolizeState::ON) {
        return true;
    }
    return frameNode == firstResponseNode_;
}

void ResponseCtrl::TrySetFirstResponse(const WeakPtr<NG::FrameNode>& frameNode)
{
    if (state_ != MonopolizeState::INIT) {
        return;
    }
    auto node = frameNode.Upgrade();
    if (node) {
        state_ = node->GetMonopolizeEvents() ? MonopolizeState::ON : MonopolizeState::OFF;
        firstResponseNode_ = frameNode;
        if (state_ == MonopolizeState::ON) {
            TAG_LOGI(
                AceLogTag::ACE_GESTURE, "monopolize on by node id:" SEC_PLD(%{public}d) ", tag:%s",
                    SEC_PARAM(node->GetId()), node->GetTag().c_str());
        }
    }
}

void ResponseCtrl::Reset()
{
    if (state_ == MonopolizeState::ON) {
        TAG_LOGI(AceLogTag::ACE_GESTURE, "monopolize reset from on");
    }
    state_ = MonopolizeState::INIT;
    firstResponseNode_.Reset();
}
} // namespace OHOS::Ace::NG
