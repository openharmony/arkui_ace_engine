/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/lazy_container_item_helper.h"

#include "core/components_ng/event/focus_hub.h"

namespace OHOS::Ace::NG {

bool LazyContainerItemHelper::FindHeadOrTailChild(
    const RefPtr<FocusHub>& childFocus, FocusStep step, WeakPtr<FocusHub>& target)
{
    CHECK_NULL_RETURN(childFocus, false);
    // Support moving focus to the first item of the List when pressing HOME
    // and to the last item of the List when pressing END.
    auto isHome = step == FocusStep::LEFT_END || step == FocusStep::UP_END;
    auto isEnd = step == FocusStep::RIGHT_END || step == FocusStep::DOWN_END;
    bool isFindTailOrHead = false;
    if (isHome) {
        isFindTailOrHead = childFocus->AnyChildFocusHub([&target](const RefPtr<FocusHub>& node) {
            auto headNode = node->GetHeadOrTailChild(true);
            if (headNode) {
                target = headNode;
                return true;
            }
            return false;
        });
    } else if (isEnd) {
        isFindTailOrHead = childFocus->AnyChildFocusHub(
            [&target](const RefPtr<FocusHub>& node) {
                auto tailNode = node->GetHeadOrTailChild(false);
                if (tailNode) {
                    target = tailNode;
                    return true;
                }
                return false;
            },
            true);
    }
    return isFindTailOrHead;
}
} // namespace OHOS::Ace::NG
