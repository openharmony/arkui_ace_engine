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


#include "core/components_ng/pattern/list/list_model_ng.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_pattern.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

void ListModelNG::SetScrollToIndexMultiThread(
    FrameNode* frameNode, int32_t index, int32_t animation, int32_t alignment, std::optional<float> extraOffset)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(pattern);
    frameNode->PostAfterAttachMainTreeTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), index, animation, alignment, extraOffset]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ScrollToIndex(index, animation, static_cast<ScrollAlign>(alignment), extraOffset);
        });
}

void ListModelNG::ScrollToItemInGroupMultiThread(
    FrameNode* frameNode, int32_t index, int32_t indexInGroup, bool smooth, ScrollAlign align)
{
    CHECK_NULL_VOID(frameNode);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    if (align == ScrollAlign::NONE) {
        align = ScrollAlign::START;
    }
    frameNode->PostAfterAttachMainTreeTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(listPattern)), index, indexInGroup, smooth, align]() {
            auto listPattern = weak.Upgrade();
            CHECK_NULL_VOID(listPattern);
            listPattern->ScrollToItemInGroup(index, indexInGroup, smooth, align);
        });
}
} // namespace OHOS::Ace::NG
