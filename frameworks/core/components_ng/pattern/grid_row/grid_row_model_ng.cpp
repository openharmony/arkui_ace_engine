/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "grid_row_model_ng.h"
#include "core/common/container.h"

#include "grid_row_layout_pattern.h"

namespace OHOS::Ace::NG {
void GridRowModelNG::Create()
{
    RefPtr<V2::GridContainerSize> col;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
        col = Referenced::MakeRefPtr<V2::GridContainerSize>(NG::DEFAULT_COLUMN_NUMBER);
    } else {
        col = Referenced::MakeRefPtr<V2::GridContainerSize>();
    }
    auto gutter = Referenced::MakeRefPtr<V2::Gutter>();
    auto breakpoints = Referenced::MakeRefPtr<V2::BreakPoints>();
    auto direction = V2::GridRowDirection::Row;
    Create(col, gutter, breakpoints, direction);
}

void GridRowModelNG::Create(const RefPtr<V2::GridContainerSize>& col, const RefPtr<V2::Gutter>& gutter,
    const RefPtr<V2::BreakPoints>& breakpoints, V2::GridRowDirection direction)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_UINODE_TRACE(nodeId);
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::GRID_ROW_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::GRID_ROW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridRowLayoutPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, *col);
    auto gridRowpattern = frameNode->GetPattern<GridRowLayoutPattern>();
    CHECK_NULL_VOID(gridRowpattern);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto&& updateFunc = [gutter, weak = AceType::WeakClaim(
        AceType::RawPtr(frameNode))](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        RefPtr<V2::Gutter> &value = const_cast<RefPtr<V2::Gutter> &>(gutter);
        value->ReloadResources(value);
        CheckNodeGutterLPX(frameNode, value);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, *value, frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    gridRowpattern->AddResObj("gridrow.gutter", resObj, std::move(updateFunc));
    CheckGutterLPX(gutter);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, *gutter);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, *breakpoints);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, direction);
}

void GridRowModelNG::CheckGutterLPX(const RefPtr<V2::Gutter>& gutter)
{
    CHECK_NULL_VOID(gutter);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->xXs, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XS);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->xSm, LpxAttribute::LPX_GRID_ROW_GUTTER_X_SM);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->xMd, LpxAttribute::LPX_GRID_ROW_GUTTER_X_MD);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->xLg, LpxAttribute::LPX_GRID_ROW_GUTTER_X_LG);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->xXl, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XL);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->xXXl, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XXL);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->ySm, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_SM);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->yMd, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_MD);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->yLg, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_LG);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->yXl, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_XL);
    ACE_CHECK_LPX_ATTRIBUTE(gutter->yXXl, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_XXL);
}

void GridRowModelNG::CheckNodeGutterLPX(FrameNode* frameNode, const RefPtr<V2::Gutter>& gutter)
{
    CHECK_NULL_VOID(gutter);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xXs, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XS, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xSm, LpxAttribute::LPX_GRID_ROW_GUTTER_X_SM, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xMd, LpxAttribute::LPX_GRID_ROW_GUTTER_X_MD, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xLg, LpxAttribute::LPX_GRID_ROW_GUTTER_X_LG, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xXl, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XL, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xXXl, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XXL, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->ySm, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_SM, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->yMd, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_MD, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->yLg, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_LG, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->yXl, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_XL, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->yXXl, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_XXL, frameNode);
}

void GridRowModelNG::CheckNodeGutterLPX(RefPtr<OHOS::Ace::NG::FrameNode> frameNode, const RefPtr<V2::Gutter>& gutter)
{
    CHECK_NULL_VOID(gutter);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xXs, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XS, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xSm, LpxAttribute::LPX_GRID_ROW_GUTTER_X_SM, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xMd, LpxAttribute::LPX_GRID_ROW_GUTTER_X_MD, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xLg, LpxAttribute::LPX_GRID_ROW_GUTTER_X_LG, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xXl, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XL, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->xXXl, LpxAttribute::LPX_GRID_ROW_GUTTER_X_XXL, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->ySm, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_SM, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->yMd, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_MD, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->yLg, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_LG, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->yXl, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_XL, frameNode);
    ACE_CHECK_NODE_LPX_ATTRIBUTE(gutter->yXXl, LpxAttribute::LPX_GRID_ROW_GUTTER_Y_XXL, frameNode);
}

RefPtr<FrameNode> GridRowModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::GRID_ROW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridRowLayoutPattern>(); });
    return frameNode;
}

void GridRowModelNG::SetOnBreakPointChange(std::function<void(const std::string)>&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridRowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBreakpointChange(std::move(onChange));
}

void GridRowModelNG::SetAlignItems(FlexAlign alignItem)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutPriority = frameNode->GetLayoutProperty<GridRowLayoutProperty>();
    CHECK_NULL_VOID(layoutPriority);
    layoutPriority->UpdateAlignItems(alignItem);
    ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, alignItem);
}

void GridRowModelNG::SetAlignItems(FrameNode* frameNode, FlexAlign alignItem)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutPriority = frameNode->GetLayoutProperty<GridRowLayoutProperty>();
    CHECK_NULL_VOID(layoutPriority);
    layoutPriority->UpdateAlignItems(alignItem);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, AlignItems, alignItem, frameNode);
}

void GridRowModelNG::SetGutter(FrameNode* frameNode, const RefPtr<V2::Gutter>& gutter)
{
    CheckNodeGutterLPX(frameNode, gutter);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, *gutter, frameNode);
}

void GridRowModelNG::SetColumns(FrameNode* frameNode, const RefPtr<V2::GridContainerSize>& col)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, *col, frameNode);
}

void GridRowModelNG::SetBreakpoints(FrameNode* frameNode, const RefPtr<V2::BreakPoints>& breakpoints)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, *breakpoints, frameNode);
}

void GridRowModelNG::SetDirection(FrameNode* frameNode, V2::GridRowDirection direction)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, direction, frameNode);
}

void GridRowModelNG::SetOnBreakPointChange(FrameNode* frameNode,
    std::function<void(const std::string)>&& onBreakPointChange)
{
    auto eventHub = frameNode->GetEventHub<GridRowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnBreakpointChange(std::move(onBreakPointChange));
}
} // namespace OHOS::Ace::NG
