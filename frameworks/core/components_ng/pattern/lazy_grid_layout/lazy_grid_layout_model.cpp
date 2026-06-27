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

#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_model.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"

namespace OHOS::Ace::NG {
void LazyGridLayoutModel::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", LAZY_V_GRID_LAYOUT_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(LAZY_V_GRID_LAYOUT_ETS_TAG, nodeId, []() {
            return AceType::MakeRefPtr<LazyGridLayoutPattern>();
        });
    stack->Push(frameNode);
}

void LazyGridLayoutModel::SetRowGap(const Dimension& rowGap)
{
    ACE_CHECK_LPX_ATTRIBUTE(rowGap, LpxAttribute::LPX_ROWS_GAP);
    ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, RowGap, rowGap);
}

void LazyGridLayoutModel::SetColumnGap(const Dimension& columnGap)
{
    ACE_CHECK_LPX_ATTRIBUTE(columnGap, LpxAttribute::LPX_COLUMNS_GAP);
    ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnGap, columnGap);
}

void LazyGridLayoutModel::SetOnVisibleIndexesChange(VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyVGridLayoutModel::SetColumnsTemplate(const std::string& value)
{
    if (value.empty()) {
        ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, "1fr");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, value);
}

void LazyGridLayoutModel::SetRowGap(FrameNode* frameNode, const Dimension& rowGap)
{
    ACE_CHECK_NODE_LPX_ATTRIBUTE(rowGap, LpxAttribute::LPX_ROWS_GAP, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, RowGap, rowGap, frameNode);
}

void LazyGridLayoutModel::SetColumnGap(FrameNode* frameNode, const Dimension& columnGap)
{
    ACE_CHECK_NODE_LPX_ATTRIBUTE(columnGap, LpxAttribute::LPX_COLUMNS_GAP, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnGap, columnGap, frameNode);
}

void LazyGridLayoutModel::SetOnVisibleIndexesChange(
    FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyVGridLayoutModel::SetColumnsTemplate(FrameNode* frameNode, const std::string& value)
{
    if (value.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, value, frameNode);
}

void LazyGridLayoutModel::SetSticky(StickyStyle stickyStyle)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LazyGridLayoutProperty, StickyStyle, stickyStyle);
}

void LazyGridLayoutModel::SetSticky(FrameNode* frameNode, StickyStyle stickyStyle)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, StickyStyle, stickyStyle, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<LazyGridLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
}

void LazyGridLayoutModel::SetHeader(std::function<void()>&& header)
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
            TAG_LOGW(AceLogTag::ACE_LAZY_GRID, "LazyGridLayout header builder produced no node");
        }
    }
    SetHeader(frameNode, headerNode);
}

void LazyGridLayoutModel::SetFooter(std::function<void()>&& footer)
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
            TAG_LOGW(AceLogTag::ACE_LAZY_GRID, "LazyGridLayout footer builder produced no node");
        }
    }
    SetFooter(frameNode, footerNode);
}

void LazyGridLayoutModel::SetHeader(FrameNode* frameNode, const RefPtr<UINode>& headerNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    if (!headerNode) {
        pattern->RemoveHeader();
        return;
    }
    pattern->AddHeader(headerNode);
}

void LazyGridLayoutModel::SetFooter(FrameNode* frameNode, const RefPtr<UINode>& footerNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    if (!footerNode) {
        pattern->RemoveFooter();
        return;
    }
    pattern->AddFooter(footerNode);
}

void LazyGridLayoutModel::RemoveHeader()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    RemoveHeader(frameNode);
}

void LazyGridLayoutModel::RemoveFooter()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    RemoveFooter(frameNode);
}

void LazyGridLayoutModel::RemoveHeader(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveHeader();
}

void LazyGridLayoutModel::RemoveFooter(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveFooter();
}
} // namespace OHOS::Ace::NG
