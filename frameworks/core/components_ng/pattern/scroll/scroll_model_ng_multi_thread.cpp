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


#include "core/components_ng/pattern/scroll/scroll_model_ng.h"

#include "base/memory/referenced.h"
#include "base/utils/multi_thread.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> ScrollModelNG::CreateFrameNodeMultiThread(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, nodeId, AceType::MakeRefPtr<ScrollPattern>());
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    pattern->SetAlwaysEnabled(true);
    auto positionController = AceType::MakeRefPtr<NG::ScrollableController>();
    pattern->SetPositionController(positionController);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern))] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->TriggerModifyDone();
    });
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
    positionController->SetScrollPattern(pattern);
    return frameNode;
}
} // namespace OHOS::Ace::NG
