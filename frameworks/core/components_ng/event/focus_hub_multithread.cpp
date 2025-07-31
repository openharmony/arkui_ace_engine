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

#include "core/components_ng/event/focus_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void FocusHub::RemoveSelfMultiThread(BlurReason reason)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->PostAfterAttachMainTreeTask([weak = WeakClaim(this), reason]() {
        auto focusHub = weak.Upgrade();
        CHECK_NULL_VOID(focusHub);
        focusHub->RemoveSelfExecuteFunction(reason);
    });
}

void FocusHub::RemoveSelfExecuteFunction(BlurReason reason)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_FOCUS, "%{public}s/" SEC_PLD(%{public}d) " remove self focus.",
            GetFrameName().c_str(), SEC_PARAM(GetFrameId()));
    }
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto focusView = frameNode->GetPattern<FocusView>();
    auto* pipeline = frameNode->GetContext();
    auto screenNode = pipeline ? pipeline->GetScreenNode() : nullptr;
    auto screenFocusHub = screenNode ? screenNode->GetFocusHub() : nullptr;
    auto parent = GetParentFocusHub();
    if (parent && parent != screenFocusHub && !focusView) {
        parent->RemoveChild(AceType::Claim(this), reason);
    } else if (IsCurrentFocus()) {
        FocusManager::FocusGuard guard(parent, SwitchingStartReason::REMOVE_SELF);
        LostFocus(reason);
    }
    if (!focusScopeId_.empty()) {
        RemoveFocusScopeIdAndPriority();
    }
}
} // namespace OHOS::Ace::NG
