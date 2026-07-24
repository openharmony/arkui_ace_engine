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

#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> LazyGridLayoutModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::LAZY_V_GRID_LAYOUT_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::LAZY_V_GRID_LAYOUT_ETS_TAG, nodeId, []() {
            return AceType::MakeRefPtr<LazyGridLayoutPattern>();
        });
    return frameNode;
}

void LazyGridLayoutModelStatic::SetRowGap(FrameNode* frameNode, const std::optional<Dimension>& rowGap)
{
    if (rowGap) {
        ACE_CHECK_NODE_LPX_ATTRIBUTE(rowGap.value(), LpxAttribute::LPX_ROWS_GAP, frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, RowGap, rowGap.value(), frameNode);
    } else {
        CHECK_NULL_VOID(frameNode);
        frameNode->UnRegisterLpxAttribute(LpxAttribute::LPX_ROWS_GAP);
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(LazyGridLayoutProperty, RowGap, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void LazyGridLayoutModelStatic::SetColumnGap(FrameNode* frameNode, const std::optional<Dimension>& columnGap)
{
    if (columnGap) {
        ACE_CHECK_NODE_LPX_ATTRIBUTE(columnGap.value(), LpxAttribute::LPX_COLUMNS_GAP, frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnGap, columnGap.value(), frameNode);
    } else {
        CHECK_NULL_VOID(frameNode);
        frameNode->UnRegisterLpxAttribute(LpxAttribute::LPX_COLUMNS_GAP);
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(LazyGridLayoutProperty, ColumnGap, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void LazyGridLayoutModelStatic::SetOnVisibleIndexesChange(
    FrameNode* frameNode, VisibleIndexesChangeEvent&& onVisibleIndexesChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnVisibleIndexesChange(std::move(onVisibleIndexesChange));
}

void LazyVGridLayoutModelStatic::SetColumnsTemplate(FrameNode* frameNode, const std::string& value)
{
    if (value.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LazyGridLayoutProperty, ColumnsTemplate, value, frameNode);
}

void LazyGridLayoutModelStatic::SetSticky(FrameNode* frameNode, const std::optional<int32_t>& stickyStyle)
{
    if (stickyStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            LazyGridLayoutProperty, StickyStyle, static_cast<StickyStyle>(stickyStyle.value()), frameNode);
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty<LazyGridLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(
            LazyGridLayoutProperty, StickyStyle, PROPERTY_UPDATE_MEASURE, frameNode);
    }
}

void LazyGridLayoutModelStatic::SetHeader(FrameNode* frameNode, const RefPtr<UINode>& headerNode)
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

void LazyGridLayoutModelStatic::SetFooter(FrameNode* frameNode, const RefPtr<UINode>& footerNode)
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

void LazyGridLayoutModelStatic::RemoveHeader(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveHeader();
}

void LazyGridLayoutModelStatic::RemoveFooter(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveFooter();
}
} // namespace OHOS::Ace::NG
