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

#include "core/components_ng/pattern/grid_col/grid_col_model_ng_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_pattern.h"

namespace OHOS::Ace::NG {

void GridColModelNGStatic::SetSpan(FrameNode *frameNode, const std::optional<V2::GridContainerSize>& span)
{
    int32_t defaultValue {1};
    V2::GridContainerSize gcSizeValue = (span.has_value()) ? span.value() : V2::GridContainerSize(defaultValue);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, gcSizeValue, frameNode);
}

void GridColModelNGStatic::SetOffset(FrameNode *frameNode, const std::optional<V2::GridContainerSize>& offset)
{
    int32_t defaultValue {0};
    V2::GridContainerSize gcSizeValue = (offset.has_value()) ? offset.value() : V2::GridContainerSize(defaultValue);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridColLayoutProperty, Offset, gcSizeValue, frameNode);
}

void GridColModelNGStatic::SetOrder(FrameNode *frameNode, const std::optional<V2::GridContainerSize>& order)
{
    int32_t defaultValue {0};
    V2::GridContainerSize gcSizeValue = (order.has_value()) ? order.value() : V2::GridContainerSize(defaultValue);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridColLayoutProperty, Order, gcSizeValue, frameNode);
}
}