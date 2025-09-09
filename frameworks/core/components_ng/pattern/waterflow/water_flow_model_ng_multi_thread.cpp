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

#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"

#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/multi_thread.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void WaterFlowModelNG::SetScrollToIndexMultiThread(
    FrameNode* frameNode, int32_t index, int32_t animation, int32_t alignment)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    frameNode->PostAfterAttachMainTreeTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), index, animation, alignment]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ScrollToIndex(index, animation, static_cast<ScrollAlign>(alignment));
        });
}
} // namespace OHOS::Ace::NG
