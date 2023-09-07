/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/panel/drag_bar_pattern.h"
#include "core/components_ng/pattern/panel/sliding_panel_node.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
const Dimension PANEL_RADIUS = 32.0_vp;
} // namespace

void SlidingPanelModelNG::Create(bool isShow)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto panelNode = GetOrCreateSlidingPanelNode(
        V2::PANEL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SlidingPanelPattern>(); });

    // Create Column node to mount to Panel.
    auto columnId = panelNode->GetColumnId();
    auto columnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    columnNode->MountToParent(panelNode);
    auto contentId = panelNode->GetContentId();
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, contentId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto contentLayoutProperty = contentNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(contentLayoutProperty);
    contentLayoutProperty->UpdateLayoutWeight(1.0f);
    contentNode->MountToParent(columnNode);

    ViewStackProcessor::GetInstance()->Push(panelNode);
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelType, PanelType::FOLDABLE_BAR); // default value
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HasDragBar, true);                   // default value
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelMode, PanelMode::HALF);         // default value
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, IsShow, isShow);

    auto renderContext = columnNode->GetRenderContext();
    if (renderContext) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto dragBarTheme = pipeline->GetTheme<DragBarTheme>();
        CHECK_NULL_VOID(dragBarTheme);
        renderContext->UpdateBackgroundColor(dragBarTheme->GetPanelBgColor());
        BorderRadiusProperty radius;
        radius.radiusTopLeft = PANEL_RADIUS;
        radius.radiusTopRight = PANEL_RADIUS;
        renderContext->UpdateBorderRadius(radius);
        renderContext->UpdateClipEdge(true);
    }
}

RefPtr<SlidingPanelNode> SlidingPanelModelNG::GetOrCreateSlidingPanelNode(
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

RefPtr<LinearLayoutProperty> SlidingPanelModelNG::GetLinearLayoutProperty()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back());
    CHECK_NULL_RETURN(columnNode, nullptr);
    auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(columnLayoutProperty, nullptr);
    return columnLayoutProperty;
}

void SlidingPanelModelNG::SetPanelType(PanelType type)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelType, type);
}

void SlidingPanelModelNG::SetPanelMode(PanelMode mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelMode, mode);
}

void SlidingPanelModelNG::SetHasDragBar(bool hasDragBar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HasDragBar, hasDragBar);
}

void SlidingPanelModelNG::SetCustomHeight(const CalcDimension& customHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, CustomHeight, customHeight);
}

void SlidingPanelModelNG::SetMiniHeight(const Dimension& miniHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, MiniHeight, miniHeight);
}

void SlidingPanelModelNG::SetHalfHeight(const Dimension& halfHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HalfHeight, halfHeight);
}

void SlidingPanelModelNG::SetFullHeight(const Dimension& fullHeight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, FullHeight, fullHeight);
}

void SlidingPanelModelNG::SetIsShow(bool isShow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, IsShow, isShow);
}

void SlidingPanelModelNG::SetShowCloseIcon(bool showCloseIcon)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, ShowCloseIcon, showCloseIcon);
}

void SlidingPanelModelNG::SetBackgroundMask(const Color& backgroundMask)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, BackgroundMask, backgroundMask);
}

// Set the color of the panel content area
void SlidingPanelModelNG::SetBackgroundColor(const Color& backgroundColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    CHECK_NULL_VOID(columnNode);
    auto renderContext = columnNode->GetRenderContext();
    if (renderContext) {
        ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, BackgroundColor, backgroundColor);
        renderContext->UpdateBackgroundColor(backgroundColor);
    }
}

void SlidingPanelModelNG::SetOnSizeChange(ChangeEvent&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSizeChange(std::move(changeEvent));
}

void SlidingPanelModelNG::SetOnHeightChange(HeightChangeEvent&& onHeightChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnHeightChange(std::move(onHeightChange));
}

void SlidingPanelModelNG::Pop()
{
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}

void SlidingPanelModelNG::SetBorderColor(const Color& borderColor)
{
    NG::ViewAbstract::SetBorderColor(borderColor);
}
void SlidingPanelModelNG::SetBorderWidth(const Dimension& borderWidth)
{
    NG::ViewAbstract::SetBorderWidth(borderWidth);
}
void SlidingPanelModelNG::SetBorderStyle(const BorderStyle& borderStyle)
{
    NG::ViewAbstract::SetBorderStyle(borderStyle);
}

void SlidingPanelModelNG::SetBorder(const BorderStyle& borderStyle, const Dimension& borderWidth) {}

void SlidingPanelModelNG::SetModeChangeEvent(ChangeEvent&& modeChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetModeChangeEvent(std::move(modeChangeEvent));
}
} // namespace OHOS::Ace::NG
