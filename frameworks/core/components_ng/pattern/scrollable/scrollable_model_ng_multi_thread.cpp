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

#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

#include "base/memory/referenced.h"
#include "base/utils/multi_thread.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
void ScrollableModelNG::SetBackToTopMultiThread(FrameNode* frameNode, bool backToTop)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)), backToTop]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetBackToTop(backToTop);
    });

    pattern->UseDefaultBackToTop(false);
}
} // namespace OHOS::Ace::NG
