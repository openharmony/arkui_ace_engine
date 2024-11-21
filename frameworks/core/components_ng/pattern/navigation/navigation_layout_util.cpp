/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/navigation_layout_util.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"

namespace OHOS::Ace::NG {
bool NavigationLayoutUtil::CheckWhetherNeedToHideToolbar(
    const RefPtr<NavDestinationNodeBase>& nodeBase, const SizeF& navigationSize)
{
    // if current menu or toolBar is custom, no need to hide.
    if (nodeBase->GetPrevMenuIsCustomValue(false) || nodeBase->GetPrevToolBarIsCustom().value_or(false)) {
        return false;
    }

    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetToolBarNode());
    CHECK_NULL_RETURN(toolbarNode, false);
    if (!toolbarNode->HasValidContent()) {
        return true;
    }

    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, false);
    auto rotationLimitCount = theme->GetToolbarRotationLimitGridCount();

    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::NAVIGATION_TOOLBAR);
    CHECK_NULL_RETURN(columnInfo, false);
    auto columnInfoParent = columnInfo->GetParent();
    CHECK_NULL_RETURN(columnInfoParent, false);
    columnInfoParent->BuildColumnWidth();

    auto currentColumns = columnInfoParent->GetColumns();
    float gridWidth = static_cast<float>(columnInfo->GetWidth(rotationLimitCount));
    float gutterWidth = columnInfoParent->GetGutterWidth().ConvertToPx();
    float hideLimitWidth = gridWidth + gutterWidth * 2;
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        if (currentColumns >= static_cast<int32_t>(rotationLimitCount) &&
            GreatOrEqual(navigationSize.Width(), gridWidth)) {
            return true;
        }
    } else if (SystemProperties::GetDeviceType() == DeviceType::TABLET) {
        if (currentColumns > static_cast<int32_t>(rotationLimitCount) &&
            GreatNotEqual(navigationSize.Width(), hideLimitWidth)) {
            return true;
        }
    }
    return false;
}

void NavigationLayoutUtil::UpdateTitleBarMenuNode(
    const RefPtr<NavDestinationNodeBase>& nodeBase, const SizeF& navigationSize)
{
    auto pattern = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(pattern);
    if (nodeBase->GetPrevMenuIsCustomValue(false)) {
        return;
    }

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(nodeBase->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto toolBarNode = AceType::DynamicCast<FrameNode>(nodeBase->GetToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(toolBarLayoutProperty);
    auto toolBarDivider = AceType::DynamicCast<FrameNode>(nodeBase->GetToolBarDividerNode());
    RefPtr<LayoutProperty> toolBarDividerProperty = nullptr;
    if (toolBarDivider) {
        toolBarDividerProperty = toolBarDivider->GetLayoutProperty();
    }
    auto isHideToolbar = pattern->GetToolbarHideStatus();
    auto preMenuNode = titleBarNode->GetMenu();
    bool needHide = CheckWhetherNeedToHideToolbar(nodeBase, navigationSize);
    bool isNeedLandscapeMenu = needHide && !isHideToolbar;
    pattern->SetIsNeedHideToolBarForNavWidth(needHide);
    if (isNeedLandscapeMenu) {
        toolBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
        if (toolBarDividerProperty) {
            toolBarDividerProperty->UpdateVisibility(VisibleType::GONE);
        }
    } else if (!isHideToolbar) {
        toolBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        if (toolBarDividerProperty) {
            toolBarDividerProperty->UpdateVisibility(VisibleType::VISIBLE);
        }
    }
    RefPtr<UINode> newMenuNode = isNeedLandscapeMenu ? nodeBase->GetLandscapeMenu() : nodeBase->GetMenu();
    if (preMenuNode == newMenuNode) {
        return;
    }
    auto nodeBasePattern = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(nodeBasePattern);
    // Mark need update safeAreaPadding when need hide safe-area-padding-mode-toolBar by landscape menu
    if (nodeBasePattern->GetToolBarStyle().value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING) {
        nodeBasePattern->UpdateSafeAreaPaddingChanged(true);
    }
    titleBarNode->RemoveChild(preMenuNode);
    titleBarNode->SetMenu(newMenuNode);
    titleBarNode->AddChild(newMenuNode);
}

float NavigationLayoutUtil::MeasureToolBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationNodeBase>& nodeBase,
    const RefPtr<NavDestinationLayoutPropertyBase>& layoutPropertyBase, const SizeF& navigationSize)
{
    auto navDestinationPatternBase = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_RETURN(navDestinationPatternBase, 0.0f);
    auto toolBarNode = nodeBase->GetToolBarNode();
    CHECK_NULL_RETURN(toolBarNode, 0.0f);
    auto index = nodeBase->GetChildIndexById(toolBarNode->GetId());
    auto toolBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(toolBarWrapper, 0.0f);
    auto constraint = layoutPropertyBase->CreateChildConstraint();

    /**
     * In the follow scenarios, we need to set the toolBar size to zero.
     * 1. ToolBar has no child.
     * 2. ToolBar is hidden and no toolBar animation is running.
     * 3. ToolBar should be moved to the menu position in the Title.
     */
    auto translateState = layoutPropertyBase->GetToolBarTranslateStateValue(BarTranslateState::NONE);
    if ((translateState == BarTranslateState::NONE &&
        layoutPropertyBase->GetHideToolBar().value_or(false)) || toolBarNode->GetChildren().empty() ||
        CheckWhetherNeedToHideToolbar(nodeBase, navigationSize)) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        toolBarWrapper->Measure(constraint);
        return 0.0f;
    }

    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto toolbarHeight = theme->GetHeight();
    constraint.selfIdealSize = OptionalSizeF(navigationSize.Width(), static_cast<float>(toolbarHeight.ConvertToPx()));
    toolBarWrapper->Measure(constraint);
    auto toolbarHeightAfterMeasure = toolBarWrapper->GetGeometryNode()->GetFrameSize().Height();
    return static_cast<float>(toolbarHeightAfterMeasure);
}

float NavigationLayoutUtil::MeasureToolBarDivider(
    LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationNodeBase>& nodeBase,
    const RefPtr<NavDestinationLayoutPropertyBase>& layoutPropertyBase,
    const SizeF& navigationSize, float toolBarHeight)
{
    if (nodeBase->GetPrevToolBarIsCustom().value_or(false) || !nodeBase->IsUseToolbarConfiguration()) {
        return 0.0f;
    }

    auto navDestinationPatternBase = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_RETURN(navDestinationPatternBase, 0.0f);
    auto toolBarDividerNode = AceType::DynamicCast<FrameNode>(nodeBase->GetToolBarDividerNode());
    CHECK_NULL_RETURN(toolBarDividerNode, 0.0f);
    auto dividerIndex = nodeBase->GetChildIndexById(toolBarDividerNode->GetId());
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(dividerIndex);
    CHECK_NULL_RETURN(dividerWrapper, 0.0f);
    auto constraint = layoutPropertyBase->CreateChildConstraint();

    /**
     * In the follow scenarios, we need to set the toolBarDivider size to zero.
     * 1. ToolBar has zero size.
     * 2. ToolBar is hidden and no toolBar animation is running.
     */
    auto translateState = layoutPropertyBase->GetToolBarTranslateStateValue(BarTranslateState::NONE);
    if ((translateState == BarTranslateState::NONE &&
        layoutPropertyBase->GetHideToolBar().value_or(false)) || NearEqual(toolBarHeight, 0.0f)) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        dividerWrapper->Measure(constraint);
        return 0.0f;
    }
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, 0.0f);
    constraint.selfIdealSize =
        OptionalSizeF(navigationSize.Width(), static_cast<float>(theme->GetToolBarDividerWidth().ConvertToPx()));
    dividerWrapper->Measure(constraint);
    return static_cast<float>(theme->GetToolBarDividerWidth().ConvertToPx());
}

float NavigationLayoutUtil::LayoutToolBar(LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationNodeBase>& nodeBase,
    const RefPtr<NavDestinationLayoutPropertyBase>& layoutPropertyBase, bool isNeedToCreatePaddingAndBorder)
{
    /**
     * When all the following conditions are met, we consider the boolBar height to be 0:
     * 1. ToolBar should hide.
     * 2. No toolBar animation is running or toolBar was translate out of navigation area.
     */
    auto translateState = layoutPropertyBase->GetToolBarTranslateStateValue(BarTranslateState::NONE);
    if (translateState != BarTranslateState::TRANSLATE_ZERO && layoutPropertyBase->GetHideToolBar().value_or(false)) {
        return 0.0f;
    }
    auto toolBarNode = nodeBase->GetToolBarNode();
    CHECK_NULL_RETURN(toolBarNode, 0.0f);
    auto index = nodeBase->GetChildIndexById(toolBarNode->GetId());
    auto toolBarWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(toolBarWrapper, 0.0f);
    auto geometryNode = toolBarWrapper->GetGeometryNode();
    float toolbarHeight = geometryNode->GetFrameSize().Height();
    if (NearZero(toolbarHeight)) {
        return 0.0f;
    }
    auto toolBarOffsetX = geometryNode->GetFrameOffset().GetX();
    auto toolBarOffsetY = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - toolbarHeight;
    if (isNeedToCreatePaddingAndBorder) {
        const auto& padding = layoutPropertyBase->CreatePaddingAndBorder();
        toolBarOffsetX = padding.left.value_or(0.0f);
        toolBarOffsetY -= padding.bottom.value_or(0.0f);
    }
    auto toolBarOffset = OffsetF(static_cast<float>(toolBarOffsetX), static_cast<float>(toolBarOffsetY));
    geometryNode->SetMarginFrameOffset(toolBarOffset);
    toolBarWrapper->Layout();
    return toolbarHeight;
}

void NavigationLayoutUtil::LayoutToolBarDivider(
    LayoutWrapper* layoutWrapper, const RefPtr<NavDestinationNodeBase>& nodeBase,
    const RefPtr<NavDestinationLayoutPropertyBase>& layoutPropertyBase, float toolbarHeight,
    bool isNeedToCreatePaddingAndBorder)
{
    /**
     * In the follow scenarios, we should not layout the toolBarDivider:
     * 1. ToolBar has zero size.
     * 2. Developer use the deprecated `toolBar` attr.
     * 3. Custom toolbar was used.
     * 4. Hide toolbar, no toolBar animation is running or toolBar was translate out of navigation area.
     */
    auto translateState = layoutPropertyBase->GetToolBarTranslateStateValue(BarTranslateState::NONE);
    if ((translateState != BarTranslateState::TRANSLATE_ZERO && layoutPropertyBase->GetHideToolBar().value_or(false)) ||
        nodeBase->GetPrevToolBarIsCustom().value_or(false) ||
        !nodeBase->IsUseToolbarConfiguration() || NearZero(toolbarHeight)) {
        return;
    }
    auto dividerNode = nodeBase->GetToolBarDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto dividerIndex = nodeBase->GetChildIndexById(dividerNode->GetId());
    auto dividerWrapper = layoutWrapper->GetOrCreateChildByIndex(dividerIndex);
    CHECK_NULL_VOID(dividerWrapper);
    auto dividerGeometryNode = dividerWrapper->GetGeometryNode();

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto dividerOffsetX = dividerGeometryNode->GetFrameOffset().GetX();
    auto dividerOffsetY = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - toolbarHeight -
                          theme->GetToolBarDividerWidth().ConvertToPx();
    if (isNeedToCreatePaddingAndBorder) {
        const auto& padding = layoutPropertyBase->CreatePaddingAndBorder();
        dividerOffsetX = padding.left.value_or(0.0f);
        dividerOffsetY -= padding.bottom.value_or(0.0f);
    }
    auto toolBarDividerOffset = OffsetF(static_cast<float>(dividerOffsetX), static_cast<float>(dividerOffsetY));
    dividerGeometryNode->SetFrameOffset(toolBarDividerOffset);
    dividerWrapper->Layout();
}

void NavigationLayoutUtil::UpdateContentSafeAreaPadding(
    const RefPtr<NavDestinationNodeBase>& nodeBase, float titleBarHeight)
{
    CHECK_NULL_VOID(nodeBase);
    auto patternBase = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(patternBase);
    if (!patternBase->IsSafeAreaPaddingChanged()) {
        return;
    }
    patternBase->UpdateSafeAreaPaddingChanged(false);
    auto contentNode = AceType::DynamicCast<FrameNode>(nodeBase->GetContentNode());
    CHECK_NULL_VOID(contentNode);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);

    Dimension paddingTop = 0.0_vp;
    if (patternBase->GetTitleBarStyle().value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING &&
        !NavigationTitleUtil::IsTitleBarHasOffsetY(AceType::DynamicCast<FrameNode>(nodeBase->GetTitleBarNode()))) {
        paddingTop = Dimension(titleBarHeight);
    }
    Dimension paddingBottom = 0.0_vp;
    auto toolBarNode = AceType::DynamicCast<FrameNode>(nodeBase->GetToolBarNode());
    if (patternBase->GetToolBarStyle().value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING &&
        toolBarNode && toolBarNode->IsVisible()) {
        auto theme = NavigationGetTheme();
        if (theme) {
            paddingBottom = theme->GetHeight();
        }
    }
    PaddingProperty paddingProperty;
    paddingProperty.left = CalcLength(0.0_vp);
    paddingProperty.right = CalcLength(0.0_vp);
    paddingProperty.top = CalcLength(paddingTop);
    paddingProperty.bottom = CalcLength(paddingBottom);

    contentLayoutProperty->UpdateSafeAreaPadding(paddingProperty);
}
} // namespace OHOS::Ace::NG
