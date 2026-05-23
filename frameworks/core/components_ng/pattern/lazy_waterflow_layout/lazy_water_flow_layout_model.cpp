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

#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_model.h"

#include <utility>

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_pattern.h"
#include "core/components_ng/pattern/lazy_waterflow_layout/lazy_water_flow_layout_property.h"

namespace OHOS::Ace::NG {

void* GetLazyVWaterFlowLayoutModel()
{
    static LazyVWaterFlowLayoutModel model;
    return &model;
}

void LazyWaterFlowLayoutModel::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", "LazyVWaterFlowLayout", nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode("LazyVWaterFlowLayout", nodeId, []() {
        return AceType::MakeRefPtr<LazyWaterFlowLayoutPattern>();
    });
    stack->Push(frameNode);
}

void LazyWaterFlowLayoutModel::SetRowGap(const Dimension& rowGap)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, RowGap, rowGap);
}

void LazyWaterFlowLayoutModel::SetColumnGap(const Dimension& columnGap)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ColumnGap, columnGap);
}

void LazyWaterFlowLayoutModel::SetRowGap(FrameNode* frameNode, const Dimension& rowGap)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, RowGap, rowGap, frameNode);
}

void LazyWaterFlowLayoutModel::SetColumnGap(FrameNode* frameNode, const Dimension& columnGap)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ColumnGap, columnGap, frameNode);
}

void LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyWaterFlowLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyWaterFlowLayoutModel::SetOnVisibleIndexesChange(
    FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyWaterFlowLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyWaterFlowLayoutModel::SetSticky(StickyStyle stickyStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, StickyStyle, stickyStyle);
}

void LazyWaterFlowLayoutModel::SetSticky(FrameNode* frameNode, StickyStyle stickyStyle)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, StickyStyle, stickyStyle, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<LazyWaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
}

void LazyWaterFlowLayoutModel::SetHeader(std::function<void()>&& header)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    RefPtr<UINode> headerNode;
    if (header) {
        auto isBuilderNode = stack->IsBuilderNode();
        auto isExportTexture = stack->IsExportTexture();
        ScopedViewStackProcessor builderViewStackProcessor;
        stack = ViewStackProcessor::GetInstance();
        CHECK_NULL_VOID(stack);
        stack->SetIsBuilderNode(isBuilderNode);
        stack->SetIsExportTexture(isExportTexture);
        header();
        headerNode = stack->Finish();
        if (!headerNode) {
            TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout header builder produced no node");
        }
    }
    SetHeader(frameNode, headerNode);
}

void LazyWaterFlowLayoutModel::SetFooter(std::function<void()>&& footer)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    RefPtr<UINode> footerNode;
    if (footer) {
        auto isBuilderNode = stack->IsBuilderNode();
        auto isExportTexture = stack->IsExportTexture();
        ScopedViewStackProcessor builderViewStackProcessor;
        stack = ViewStackProcessor::GetInstance();
        CHECK_NULL_VOID(stack);
        stack->SetIsBuilderNode(isBuilderNode);
        stack->SetIsExportTexture(isExportTexture);
        footer();
        footerNode = stack->Finish();
        if (!footerNode) {
            TAG_LOGW(AceLogTag::ACE_LAZY_WATER_FLOW, "LazyWaterFlowLayout footer builder produced no node");
        }
    }
    SetFooter(frameNode, footerNode);
}

void LazyWaterFlowLayoutModel::SetHeader(FrameNode* frameNode, const RefPtr<UINode>& headerNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyWaterFlowLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    if (!headerNode) {
        pattern->RemoveHeader();
        return;
    }
    pattern->AddHeader(headerNode);
}

void LazyWaterFlowLayoutModel::SetFooter(FrameNode* frameNode, const RefPtr<UINode>& footerNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyWaterFlowLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    if (!footerNode) {
        pattern->RemoveFooter();
        return;
    }
    pattern->AddFooter(footerNode);
}

void LazyWaterFlowLayoutModel::RemoveHeader()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    RemoveHeader(frameNode);
}

void LazyWaterFlowLayoutModel::RemoveFooter()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    RemoveFooter(frameNode);
}

void LazyWaterFlowLayoutModel::RemoveHeader(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyWaterFlowLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveHeader();
}

void LazyWaterFlowLayoutModel::RemoveFooter(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyWaterFlowLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveFooter();
}

void LazyVWaterFlowLayoutModel::SetColumnsTemplate(const std::string& value)
{
    if (value.empty()) {
        ACE_UPDATE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ColumnsTemplate, "1fr");
        ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(LazyWaterFlowLayoutProperty, ItemFillPolicy, PROPERTY_UPDATE_MEASURE);
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ColumnsTemplate, value);
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(LazyWaterFlowLayoutProperty, ItemFillPolicy, PROPERTY_UPDATE_MEASURE);
}

void LazyVWaterFlowLayoutModel::SetColumnsTemplate(FrameNode* frameNode, const std::string& value)
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

void LazyVWaterFlowLayoutModel::SetItemFillPolicy(PresetFillType policy)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ItemFillPolicy, policy);
}

void LazyVWaterFlowLayoutModel::SetItemFillPolicy(FrameNode* frameNode, PresetFillType policy)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyWaterFlowLayoutProperty, ItemFillPolicy, policy, frameNode);
}

void LazyVWaterFlowLayoutModel::ResetItemFillPolicy()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(LazyWaterFlowLayoutProperty, ItemFillPolicy, PROPERTY_UPDATE_MEASURE);
}

void LazyVWaterFlowLayoutModel::ResetItemFillPolicy(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
        LazyWaterFlowLayoutProperty, ItemFillPolicy, PROPERTY_UPDATE_MEASURE, frameNode);
}

} // namespace OHOS::Ace::NG
