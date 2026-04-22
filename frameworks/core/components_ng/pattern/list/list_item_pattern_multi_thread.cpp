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

#include "core/components_ng/pattern/list/list_item_pattern.h"

namespace OHOS::Ace::NG {

void ListItemPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (listItemStyle_ == V2::ListItemStyle::CARD) {
        ApplyListItemDefaultAttributes(host);
    }
}
bool ListItemPattern::CloseSwipeActionMultiThread(OnFinishFunc&& onFinishCallback)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    bool shouldSkipClose =
        !host || !host->IsOnMainTree() || !host->IsActive() || GetSwipeActionState() == SwipeActionState::COLLAPSED;
    host->PostAfterAttachMainTreeTask([onFinishCallback, weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->onFinishEvent_ = onFinishCallback;
        pattern->ResetSwipeStatus(true);
    });
    return shouldSkipClose;
}

void ListItemPattern::SetListItemStyleMultiThread(V2::ListItemStyle style)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (listItemStyle_ == V2::ListItemStyle::NONE && style == V2::ListItemStyle::CARD) {
        host->PostAfterAttachMainTreeTask([style, weak = WeakClaim(this), weakNode = WeakClaim(RawPtr(host))]() {
            auto node = weakNode.Upgrade();
            CHECK_NULL_VOID(node);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->listItemStyle_ = style;
            pattern->ApplyListItemDefaultAttributes(node);
            pattern->InitListItemCardStyleForList();
        });
    }
}

} // namespace OHOS::Ace::NG
