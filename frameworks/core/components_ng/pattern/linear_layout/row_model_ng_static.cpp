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

#include "core/components_ng/pattern/linear_layout/row_model_ng_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {

void RowModelNGStatic::SetIsReverse(FrameNode* frameNode, const std::optional<bool> isReverse)
{
    CHECK_NULL_VOID(frameNode);
    if (isReverse.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, IsReverse, isReverse.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, IsReverse, frameNode);
    }
}

void RowModelNGStatic::SetJustifyContent(FrameNode* frameNode, const std::optional<FlexAlign>& flexAlign)
{
    CHECK_NULL_VOID(frameNode);
    if (flexAlign.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, MainAxisAlign, flexAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, MainAxisAlign, frameNode);
    }
}

void RowModelNGStatic::SetAlignItems(FrameNode* frameNode, const std::optional<FlexAlign>& flexAlign)
{
    CHECK_NULL_VOID(frameNode);
    if (flexAlign.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, CrossAxisAlign, flexAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, CrossAxisAlign, frameNode);
    }
}
}