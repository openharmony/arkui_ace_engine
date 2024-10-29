/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_pattern.h"

namespace OHOS::Ace::NG {
void GridColModelNG::Create()
{
    V2::GridContainerSize span = V2::GridContainerSize(1);
    V2::GridContainerSize offset = V2::GridContainerSize(0);
    V2::GridContainerSize order = V2::GridContainerSize(0);
    Create(span, offset, order);
}

void GridColModelNG::Create(const V2::GridContainerSize &span, const V2::GridContainerSize &offset,
    const V2::GridContainerSize &order)
{
    auto *stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::GRID_COL_ETS_TAG, nodeId);
    auto frameNode = CreateFrameNode(nodeId);
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, span);
    ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Offset, offset);
    ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Order, order);
}

RefPtr<FrameNode> GridColModelNG::CreateFrameNode(int32_t nodeId)
{
    RefPtr<FrameNode> frameNode = FrameNode::GetFrameNode(V2::GRID_COL_ETS_TAG, nodeId);
    if (frameNode) {
        return frameNode;
    }
    auto defaultSpan = V2::GridContainerSize(1);
    auto defaultOther = V2::GridContainerSize(0);
    frameNode = FrameNode::CreateFrameNode(V2::GRID_COL_ETS_TAG, nodeId, AceType::MakeRefPtr<GridColLayoutPattern>());
    auto castGridColLayoutProperty = (frameNode)->GetLayoutPropertyPtr<GridColLayoutProperty>();
    if (castGridColLayoutProperty) {
        castGridColLayoutProperty->UpdateSpan(defaultSpan);
        castGridColLayoutProperty->UpdateOffset(defaultOther);
        castGridColLayoutProperty->UpdateOrder(defaultOther);
    }
    return frameNode;
}

void GridColModelNG::SetSpan(const V2::GridContainerSize &span)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, span);
}

void GridColModelNG::SetOffset(const V2::GridContainerSize &offset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Offset, offset);
}

void GridColModelNG::SetOrder(const V2::GridContainerSize &order)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Order, order);
}

void GridColModelNG::SetSpan(FrameNode *frameNode, const std::optional<V2::GridContainerSize>& span)
{
    int32_t defaultValue {1};
    V2::GridContainerSize gcSizeValue = (span.has_value()) ? span.value() : V2::GridContainerSize(defaultValue);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, gcSizeValue, frameNode);
}

void GridColModelNG::SetOffset(FrameNode *frameNode, const std::optional<V2::GridContainerSize>& offset)
{
    int32_t defaultValue {0};
    V2::GridContainerSize gcSizeValue = (offset.has_value()) ? offset.value() : V2::GridContainerSize(defaultValue);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridColLayoutProperty, Offset, gcSizeValue, frameNode);
}

void GridColModelNG::SetOrder(FrameNode *frameNode, const std::optional<V2::GridContainerSize>& order)
{
    int32_t defaultValue {0};
    V2::GridContainerSize gcSizeValue = (order.has_value()) ? order.value() : V2::GridContainerSize(defaultValue);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridColLayoutProperty, Order, gcSizeValue, frameNode);
}
} // namespace OHOS::Ace::NG
