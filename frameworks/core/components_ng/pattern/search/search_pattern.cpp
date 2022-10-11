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

#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"

namespace OHOS::Ace::NG {

void SearchPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // Image click event
    auto imageFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(1));
    CHECK_NULL_VOID(imageFrameNode);
    if (imageClickListener_) {
        return;
    }
    auto imageGesture = imageFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(imageGesture);
    auto imageClickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto searchPattern = weak.Upgrade();
        CHECK_NULL_VOID(searchPattern);
        searchPattern->OnClickButtonAndImage();
    };

    imageClickListener_ = MakeRefPtr<ClickEvent>(std::move(imageClickCallback));
    imageGesture->AddClickEvent(imageClickListener_);

    // Button click event
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(2));
    CHECK_NULL_VOID(buttonFrameNode);
    if (buttonClickListener_) {
        return;
    }
    auto buttonGesture = buttonFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(buttonGesture);
    auto buttonClickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto searchPattern = weak.Upgrade();
        CHECK_NULL_VOID(searchPattern);
        searchPattern->OnClickButtonAndImage();
    };
    buttonClickListener_ = MakeRefPtr<ClickEvent>(std::move(buttonClickCallback));
    buttonGesture->AddClickEvent(buttonClickListener_);
}

void SearchPattern::OnClickButtonAndImage()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchEventHub = host->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(searchEventHub);
    // TODO: get value from TextField
    searchEventHub->UpdateChangeAndSubmitEvent("TODO: get value from TextField");
}

} // namespace OHOS::Ace::NG
