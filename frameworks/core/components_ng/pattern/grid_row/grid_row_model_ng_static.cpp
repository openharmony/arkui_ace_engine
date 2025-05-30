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

#include "grid_row_model_ng_static.h"

#include "grid_row_layout_pattern.h"

namespace OHOS::Ace::NG {

void GridRowModelNGStatic::SetAlignItems(FrameNode* frameNode, const std::optional<FlexAlign>& alignItem)
{
    CHECK_NULL_VOID(frameNode);
    if (alignItem.has_value()) {
        auto layoutProperty = frameNode->GetLayoutProperty<GridRowLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignItems(alignItem.value());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, alignItem.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, frameNode);
    }
}

void GridRowModelNGStatic::SetDirection(FrameNode* frameNode, const std::optional<V2::GridRowDirection>& direction)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction,
        direction.has_value()? direction.value(): V2::GridRowDirection::Row, frameNode);
}
}