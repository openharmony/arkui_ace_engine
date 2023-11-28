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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_RESPONSE_CTRL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_RESPONSE_CTRL_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
// forward declare
class FrameNode;
// define of response controller, affected by monopolize attribute
class ResponseCtrl : public AceType {
    DECLARE_ACE_TYPE(ResponseCtrl, AceType);

public:
    ResponseCtrl() = default;
    bool ShouldResponse(const WeakPtr<NG::FrameNode>& frameNode);
    void TrySetFirstResponse(const WeakPtr<NG::FrameNode>& frameNode);
    void Reset();

private:
    enum class MonopolizeState { INIT, ON, OFF };

    MonopolizeState state_ = MonopolizeState::INIT;
    WeakPtr<NG::FrameNode> firstResponseNode_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_RESPONSE_CTRL_H