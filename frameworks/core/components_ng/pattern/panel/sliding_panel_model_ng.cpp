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

#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {

namespace {
const Dimension PANEL_RADIUS = 32.0_vp;
constexpr Dimension BLANK_MIN_HEIGHT = 8.0_vp;
constexpr double HALF_VALUS = 2.0;
} // namespace

void SlidingPanelModelNG::Create(bool isShow)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::PANEL_ETS_TAG, nodeId);
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
    auto slidingPanelPattern = panelNode->GetPattern<SlidingPanelPattern>();
    CHECK_NULL_VOID(slidingPanelPattern);
    auto layoutProperty = slidingPanelPattern->GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelType,
        layoutProperty->GetPanelTypeValue(PanelType::FOLDABLE_BAR));    // default value
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HasDragBar,
        layoutProperty->GetHasDragBarValue(true));                      // default value
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelMode,
        layoutProperty->GetPanelModeValue(PanelMode::HALF));            // default value
    ACE_UPDATE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, IsShow, isShow);

    auto renderContext = columnNode->GetRenderContext();
    if (renderContext) {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    auto eventHub = frameNode->GetOrCreateEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSizeChange(std::move(changeEvent));
}

void SlidingPanelModelNG::SetOnHeightChange(HeightChangeEvent&& onHeightChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<SlidingPanelEventHub>();
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
    auto eventHub = frameNode->GetOrCreateEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetModeChangeEvent(std::move(modeChangeEvent));
}

RefPtr<FrameNode> SlidingPanelModelNG::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::PANEL_ETS_TAG, nodeId);
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
    CHECK_NULL_RETURN(contentLayoutProperty, panelNode);
    contentLayoutProperty->UpdateLayoutWeight(1.0f);
    contentNode->MountToParent(columnNode);

    auto renderContext = columnNode->GetRenderContext();
    if (renderContext) {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(pipeline, panelNode);
        auto dragBarTheme = pipeline->GetTheme<DragBarTheme>();
        CHECK_NULL_RETURN(dragBarTheme, panelNode);
        renderContext->UpdateBackgroundColor(dragBarTheme->GetPanelBgColor());
        BorderRadiusProperty radius;
        radius.radiusTopLeft = PANEL_RADIUS;
        radius.radiusTopRight = PANEL_RADIUS;
        renderContext->UpdateBorderRadius(radius);
        renderContext->UpdateClipEdge(true);
    }

    return panelNode;
}

void SlidingPanelModelNG::SetPanelMode(FrameNode* frameNode, const std::optional<PanelMode>& mode)
{
    if (mode.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelMode, mode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelMode, frameNode);
    }
}

void SlidingPanelModelNG::SetPanelFullHeight(FrameNode* frameNode, const std::optional<Dimension>& fullHeight)
{
    if (fullHeight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, FullHeight, fullHeight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, FullHeight, frameNode);
    }
}

void SlidingPanelModelNG::SetPanelHalfHeight(FrameNode* frameNode, const std::optional<Dimension>& halfHeight)
{
    if (halfHeight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HalfHeight, halfHeight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HalfHeight, frameNode);
    }
}

void SlidingPanelModelNG::SetPanelMiniHeight(FrameNode* frameNode, const std::optional<Dimension>& miniHeight)
{
    if (miniHeight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, MiniHeight, miniHeight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, MiniHeight, frameNode);
    }
}

void SlidingPanelModelNG::SetPanelBackgroundMask(FrameNode* frameNode, const std::optional<Color>& backgroundMask)
{
    if (backgroundMask.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, BackgroundMask, backgroundMask.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, BackgroundMask, frameNode);
    }
}

void SlidingPanelModelNG::SetPanelType(FrameNode* frameNode, const std::optional<PanelType>& type)
{
    if (type.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelType, type.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, PanelType, frameNode);
    }
}

void SlidingPanelModelNG::SetPanelCustomHeight(FrameNode* frameNode, const std::optional<CalcDimension>& customHeight)
{
    if (customHeight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, CustomHeight, customHeight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, CustomHeight, frameNode);
    }
}

void SlidingPanelModelNG::SetShowCloseIcon(FrameNode* frameNode, bool showCloseIcon)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, ShowCloseIcon, showCloseIcon, frameNode);
}

void SlidingPanelModelNG::SetHasDragBar(FrameNode* frameNode, bool hasDragBar)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HasDragBar, hasDragBar, frameNode);
}

void SlidingPanelModelNG::SetIsShow(FrameNode* frameNode, bool isShow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, IsShow, isShow, frameNode);
}

void SlidingPanelModelNG::ResetPanelHalfHeight(FrameNode* frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    if (GreatNotEqual(frameSize.Height(), 0.0)) {
        auto halfHeight = Dimension((frameSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx()) / HALF_VALUS);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, HalfHeight, halfHeight, frameNode);
    }
}

void SlidingPanelModelNG::ResetPanelFullHeight(FrameNode* frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty<SlidingPanelLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    if (GreatNotEqual(frameSize.Height(), 0.0)) {
        auto fullHeight = Dimension(frameSize.Height() - BLANK_MIN_HEIGHT.ConvertToPx());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(SlidingPanelLayoutProperty, FullHeight, fullHeight, frameNode);
    }
}

void SlidingPanelModelNG::SetOnSizeChange(FrameNode* frameNode, ChangeEvent&& changeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSizeChange(std::move(changeEvent));
};

void SlidingPanelModelNG::SetOnHeightChange(FrameNode* frameNode, HeightChangeEvent&& onHeightChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnHeightChange(std::move(onHeightChange));
}

void SlidingPanelModelNG::SetModeChangeEvent(FrameNode* frameNode, ChangeEvent&& modeChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SlidingPanelEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetModeChangeEvent(std::move(modeChangeEvent));
}
} // namespace OHOS::Ace::NG
