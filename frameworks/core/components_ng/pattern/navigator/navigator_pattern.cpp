/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigator/navigator_pattern.h"

namespace OHOS::Ace::NG {
void NavigatorPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    // only register click event once
    if (clickListener_) {
        return;
    }
    // register click event
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);

    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& /*info*/) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // pass to eventHub to perform navigation
        auto eventHub = pattern->GetOrCreateEventHub<NavigatorEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->NavigatePage();
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

} // namespace OHOS::Ace::NG