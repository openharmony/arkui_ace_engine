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

#include "core/components_ng/pattern/refresh/refresh_model_ng.h"

#include <string>
 
#include "base/memory/referenced.h"
#include "base/utils/multi_thread.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/ng/offset_t.h"
#include "frameworks/base/i18n/localization.h"
#include "frameworks/base/utils/time_util.h"
#include "frameworks/core/components/refresh/refresh_theme.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/base/view_stack_processor.h"
#include "frameworks/core/components_ng/event/event_hub.h"

namespace OHOS::Ace::NG {
void RefreshModelNG::SetCustomBuilderMultiThread(FrameNode* frameNode, FrameNode* customBuilder)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RefreshPattern>();
    CHECK_NULL_VOID(pattern);
    frameNode->PostAfterAttachMainTreeTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)), customBuilder]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->AddCustomBuilderNode(AceType::Claim<UINode>(customBuilder));
    });
}
} // namespace OHOS::Ace::NG
