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

#include "core/components_ng/pattern/grid/grid_model_ng.h"

#include <regex>

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void GridModelNG::Create(
    const RefPtr<V2::GridPositionController>& /*positionController*/, const RefPtr<ScrollBarProxy>& /*scrollBarProxy*/)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::GRID_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridPattern>(); });
    stack->Push(frameNode);
}

void GridModelNG::Pop()
{
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}

void GridModelNG::SetColumnsTemplate(const std::string& value)
{
    if (!CheckTemplate(value)) {
        LOGE("Columns Template [%{public}s] is not valid.", value.c_str());
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, "");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, value);
}

void GridModelNG::SetRowsTemplate(const std::string& value)
{
    if (!CheckTemplate(value)) {
        LOGE("Rows Template [%{public}s] is not valid.", value.c_str());
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, "");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, value);
}

void GridModelNG::SetColumnsGap(const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsGap, value);
    }
}

void GridModelNG::SetRowsGap(const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsGap, value);
    }
}

void GridModelNG::SetGridHeight(const Dimension& value)
{
    ViewAbstract::SetHeight(NG::CalcLength(value));
}

void GridModelNG::SetScrollBarMode(DisplayMode value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollBarMode, value);
}

void GridModelNG::SetScrollBarColor(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollBarColor, Color::FromString(value));
}

void GridModelNG::SetScrollBarWidth(const std::string& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollBarWidth, StringUtils::StringToDimensionWithUnit(value));
}

void GridModelNG::SetCachedCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, CachedCount, value);
}

void GridModelNG::SetEditable(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, Editable, value);
}

void GridModelNG::SetIsRTL(bool rightToLeft) {}

void GridModelNG::SetLayoutDirection(FlexDirection value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, LayoutDirection, value);
}

void GridModelNG::SetMaxCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, MaxCount, value);
}

void GridModelNG::SetMinCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, MinCount, value);
}

void GridModelNG::SetCellLength(int32_t value)
{
    if (value > 0) {
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, CellLength, value);
    }
}

void GridModelNG::SetMultiSelectable(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMultiSelectable(value);
}

void GridModelNG::SetSupportAnimation(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportAnimation(value);
}

void GridModelNG::SetSupportDragAnimation(bool value) {}

void GridModelNG::SetEdgeEffect(EdgeEffect edgeEffect) {}

void GridModelNG::SetOnScrollToIndex(ScrollToIndexFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollToIndex(std::move(value));
}

void GridModelNG::SetOnItemDragStart(std::function<void(const ItemDragInfo&, int32_t)>&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragStart = [func = std::move(value)](const ItemDragInfo& dragInfo, int32_t index) -> RefPtr<UINode> {
        ScopedViewStackProcessor builderViewStackProcessor;
        {
            func(dragInfo, index);
        }
        return ViewStackProcessor::GetInstance()->Finish();
    };
    eventHub->SetOnItemDragStart(std::move(onDragStart));

    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    eventHub->InitItemDragEvent(gestureEventHub);

    AddDragFrameNodeToManager();
}

void GridModelNG::SetOnItemDragEnter(ItemDragEnterFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(value));

    AddDragFrameNodeToManager();
}

void GridModelNG::SetOnItemDragMove(ItemDragMoveFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(value));

    AddDragFrameNodeToManager();
}

void GridModelNG::SetOnItemDragLeave(ItemDragLeaveFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(value));

    AddDragFrameNodeToManager();
}

void GridModelNG::SetOnItemDrop(ItemDropFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(value));

    AddDragFrameNodeToManager();
}

void GridModelNG::AddDragFrameNodeToManager() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    dragDropManager->AddGridDragFrameNode(AceType::WeakClaim(AceType::RawPtr(frameNode)));
}

bool GridModelNG::CheckTemplate(const std::string& value)
{
    std::vector<std::string> strs;
    StringUtils::StringSplitter(value, ' ', strs);
    std::regex reg("\\d+fr");
    return std::all_of(strs.begin(), strs.end(), [reg](const std::string& str) { return std::regex_match(str, reg); });
}

} // namespace OHOS::Ace::NG
