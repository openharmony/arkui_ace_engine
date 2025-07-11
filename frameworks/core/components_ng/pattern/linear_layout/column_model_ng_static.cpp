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

#include "core/components_ng/pattern/linear_layout/column_model_ng_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {

void ColumnModelNGStatic::SetSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    if (space && GreatOrEqual(space->Value(), 0.0)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, space.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, frameNode);
    }
}

void ColumnModelNGStatic::SetJustifyContent(FrameNode* frameNode, const std::optional<FlexAlign>& valueOpt)
{
    if (valueOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, MainAxisAlign, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, MainAxisAlign, frameNode);
    }
}

void ColumnModelNGStatic::SetAlignItems(FrameNode* frameNode, const std::optional<FlexAlign>& valueOpt)
{
    if (valueOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, CrossAxisAlign, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, CrossAxisAlign, frameNode);
    }
}
} // namespace OHOS::AceL::NG
