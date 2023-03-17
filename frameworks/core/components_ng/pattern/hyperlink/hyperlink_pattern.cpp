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

#include "core/components_ng/pattern/hyperlink/hyperlink_pattern.h"

namespace OHOS::Ace::NG {
void HyperlinkPattern::OnAttachToFrameNode() {}

void HyperlinkPattern::OnModifyDone()
{
    TextPattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);

    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitClickEvent(gestureHub);
}

void HyperlinkPattern::LinkToAddress()
{
#if defined(PREVIEW)
    LOGW("Unable to jump in preview.");
    return;
#else
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->HyperlinkStartAbility(address_);
#endif
}

void HyperlinkPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto hyperlinkPattern = weak.Upgrade();
        CHECK_NULL_VOID(hyperlinkPattern);
        hyperlinkPattern->LinkToAddress();
    };
    gestureHub->SetUserOnClick(std::move(clickCallback));
}

void HyperlinkPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("address", address_.c_str());
}
} // namespace OHOS::Ace::NG
