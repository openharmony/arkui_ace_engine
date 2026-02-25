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

#include "frameworks/core/components_ng/pattern/stack/stack_pattern.h"

#include "core/components_ng/event/overflow_scroll_event_hub.h"
#include "core/components_ng/layout/vertical_overflow_handler.h"

namespace OHOS::Ace::NG {
RefPtr<EventHub> StackPattern::CreateEventHub()
{
    return MakeRefPtr<OverflowScrollEventHub>();
}

RefPtr<VerticalOverflowHandler> StackPattern::GetOrCreateVerticalOverflowHandler(const WeakPtr<FrameNode>& host)
{
    if (!vOverflowHandler_) {
        vOverflowHandler_ = MakeRefPtr<VerticalOverflowHandler>(host);
    }
    return vOverflowHandler_;
}

void StackPattern::DumpInfo()
{
    if (vOverflowHandler_) {
        DumpLog::GetInstance().AddDesc(std::string("OverflowInfo: ").append(vOverflowHandler_->ToString().c_str()));
    }
}
} // namespace OHOS::Ace::NG