/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model_static.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_pattern.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_property.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> LazyWaterFlowLayoutModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", "LazyVWaterFlowLayout", nodeId);
    return FrameNode::GetOrCreateFrameNode("LazyVWaterFlowLayout", nodeId, []() {
        return AceType::MakeRefPtr<LazyWaterFlowLayoutPattern>();
    });
}

void LazyWaterFlowLayoutModelStatic::SetRowGap(FrameNode* frameNode, const std::optional<Dimension>& rowGap)
{
    if (rowGap) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, RowGap, rowGap.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            LazyWaterFlowLayoutProperty, RowGap, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void LazyWaterFlowLayoutModelStatic::SetColumnGap(FrameNode* frameNode, const std::optional<Dimension>& columnGap)
{
    if (columnGap) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ColumnGap, columnGap.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            LazyWaterFlowLayoutProperty, ColumnGap, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void LazyWaterFlowLayoutModelStatic::SetOnVisibleIndexesChange(
    FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyWaterFlowLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyVWaterFlowLayoutModelStatic::SetColumnsTemplate(FrameNode* frameNode, const std::string& value)
{
    if (value.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ColumnsTemplate, "1fr", frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            LazyWaterFlowLayoutProperty, ItemFillPolicy, PROPERTY_UPDATE_MEASURE, frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ColumnsTemplate, value, frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        LazyWaterFlowLayoutProperty, ItemFillPolicy, PROPERTY_UPDATE_MEASURE, frameNode);
}

void LazyVWaterFlowLayoutModelStatic::SetItemFillPolicy(FrameNode* frameNode, PresetFillType policy)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ItemFillPolicy, policy, frameNode);
}

void LazyVWaterFlowLayoutModelStatic::ResetItemFillPolicy(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        LazyWaterFlowLayoutProperty, ItemFillPolicy, PROPERTY_UPDATE_MEASURE, frameNode);
}

} // namespace OHOS::Ace::NG
