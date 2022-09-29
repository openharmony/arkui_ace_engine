/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_item_view.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_item_layout_property.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void GridItemView::Create(std::function<void(int32_t)>&& deepRenderFunc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto deepRender = [nodeId, deepRenderFunc = std::move(deepRenderFunc)]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(deepRenderFunc, nullptr);
        deepRenderFunc(nodeId);
        return ViewStackProcessor::GetInstance()->Finish();
    };
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, nodeId, [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender))]() {
            return AceType::MakeRefPtr<GridItemPattern>(shallowBuilder);
        });
    stack->Push(frameNode);
}

void GridItemView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::GRID_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridItemPattern>(nullptr); });
    stack->Push(frameNode);
}

void GridItemView::SetRowStart(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridItemLayoutProperty, RowStart, value);
}

void GridItemView::SetRowEnd(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridItemLayoutProperty, RowEnd, value);
}

void GridItemView::SetColumnStart(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridItemLayoutProperty, ColumnStart, value);
}

void GridItemView::SetColumnEnd(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridItemLayoutProperty, ColumnEnd, value);
}

void GridItemView::SetForceRebuild(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetForceRebuild(value);
}

void GridItemView::SetSelectable(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectable(value);
}

void GridItemView::SetOnSelect(SelectFunc&& onSelect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(onSelect));
}

} // namespace OHOS::Ace::NG
