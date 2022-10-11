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

#include "core/components_ng/pattern/panel/sliding_panel_view.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/panel/drag_bar_pattern.h"
#include "core/components_ng/pattern/panel/sliding_panel_node.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void SlidingPanelView::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto panelNode = GetOrCreateSlidingPanelNode(
        V2::PANEL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SlidingPanelPattern>(); });

    // Create Column node to mount to Panel.
    auto columnId_ = panelNode->GetColumnId();
    auto columnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId_, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    ACE_UPDATE_LAYOUT_PROPERTY(LinearLayoutProperty, CrossAxisAlign, FlexAlign::CENTER);
    ACE_UPDATE_LAYOUT_PROPERTY(LinearLayoutProperty, MainAxisAlign, FlexAlign::STRETCH);
    auto columnPattern = columnNode->GetPattern<LinearLayoutPattern>();
    CHECK_NULL_VOID(columnPattern);
    columnNode->MountToParent(panelNode);

    ViewStackProcessor::GetInstance()->Push(panelNode);
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelType, PanelType::FOLDABLE_BAR); // default value
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HasDragBar, true);                   // default value
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelMode, PanelMode::HALF);         // default value
}

RefPtr<SlidingPanelNode> SlidingPanelView::GetOrCreateSlidingPanelNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto panelNode = ElementRegister::GetInstance()->GetSpecificItemById<SlidingPanelNode>(nodeId);
    if (panelNode) {
        if (panelNode->GetTag() == tag) {
            return panelNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = panelNode->GetParent();
        if (parent) {
            parent->RemoveChild(panelNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    panelNode = AceType::MakeRefPtr<SlidingPanelNode>(tag, nodeId, pattern, false);
    panelNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(panelNode);
    return panelNode;
}

RefPtr<LinearLayoutProperty> SlidingPanelView::GetLinearLayoutProperty()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back());
    CHECK_NULL_RETURN(columnNode, nullptr);
    auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(columnLayoutProperty, nullptr);
    return columnLayoutProperty;
}

void SlidingPanelView::SetPanelType(PanelType type)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelType, type);
}

void SlidingPanelView::SetPanelMode(PanelMode mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelMode, mode);
}

void SlidingPanelView::SetHasDragBar(bool hasDragBar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HasDragBar, hasDragBar);
}

void SlidingPanelView::SetMiniHeight(const Dimension& miniHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, MiniHeight, miniHeight);
}

void SlidingPanelView::SetHalfHeight(const Dimension& halfHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HalfHeight, halfHeight);
}

void SlidingPanelView::SetFullHeight(const Dimension& fullHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, FullHeight, fullHeight);
}

// Set the color of the panel content area
void SlidingPanelView::SetBackgroundColor(Color backgroundColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto renderContext = columnNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateBackgroundColor(backgroundColor);
    }
}

void SlidingPanelView::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SlidingPanelView::SetOnHeightChange(HeightChangeEvent&& onHeightChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnHeightChange(std::move(onHeightChange));
}

void SlidingPanelView::Pop()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto hasDragBar = layoutProperty->GetHasDragBar().value_or(true);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto dragBarNode = columnNode->GetChildren().front();
    CHECK_NULL_VOID(dragBarNode);
    auto isFirstChildDragBar = dragBarNode->GetTag() == V2::DRAG_BAR_ETS_TAG;
    if (hasDragBar) {
        if (!isFirstChildDragBar) {
            auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DragBarPattern>(); });
            dragBarNode->MountToParent(columnNode, 0);
        }
        return;
    }

    if (isFirstChildDragBar) {
        columnNode->RemoveChildAtIndex(0);
    }
}

} // namespace OHOS::Ace::NG
