/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "base/utils/measure_util.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components/custom_paint/rosen_render_custom_paint.h"
#endif

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t MENU_OFFSET_RATIO = 9;
// maximum radio of the subtitle height to the titlebar height
constexpr double SUBTITLE_MAX_HEIGHT_RADIO = 0.35;
constexpr float OVERDRAG_DIVIDE_NUM = 6.0f;

bool NeedAvoidMenuBar(PipelineContext* pipeline)
{
    return pipeline && pipeline->GetInstallationFree();
}

bool NeedAvoidContainerModal(
    PipelineContext* pipeline, const RefPtr<TitleBarNode>& titleBarNode)
{
    CHECK_NULL_RETURN(pipeline, false);
    auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_RETURN(avoidInfoMgr, false);
    return avoidInfoMgr->NeedAvoidContainerModal() && titleBarNode && titleBarNode->NeedAvoidContainerModal();
}
} // namespace

void TitleBarLayoutAlgorithm::BackButtonLayout(LayoutWrapper* layoutWrapper)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();
    CHECK_NULL_VOID(backButtonLayoutProperty);
    PaddingProperty padding;
    padding.SetEdges(CalcLength(MENU_BUTTON_PADDING));
    backButtonLayoutProperty->UpdatePadding(padding);
}

void TitleBarLayoutAlgorithm::UpdateIconSize(const RefPtr<FrameNode>& backButtonNode)
{
    auto backButtonImageNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    CHECK_NULL_VOID(backButtonImageNode);
    auto backButtonImageLayoutProperty = backButtonImageNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(backButtonImageLayoutProperty);
    backButtonImageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(backIconWidth_), CalcLength(backIconHeight_)));
}

void TitleBarLayoutAlgorithm::MeasureBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto index = titleBarNode->GetChildIndexById(backButtonNode->GetId());
    auto backButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(backButtonWrapper);
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();

    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        if (!showBackButton_) {
            backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
            return;
        }
        backButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        PaddingProperty padding;
        padding.SetEdges(CalcLength(BUTTON_PADDING));
        backButtonLayoutProperty->UpdatePadding(padding);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            constraint.selfIdealSize = OptionalSizeF(static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()),
                static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()));
            backButtonWrapper->Measure(constraint);
            return;
        }
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            UpdateIconSize(backButtonNode);
            constraint.selfIdealSize = OptionalSizeF(static_cast<float>(backButtonWidth_.ConvertToPx()),
                static_cast<float>(backButtonWidth_.ConvertToPx()));
            backButtonWrapper->Measure(constraint);
            return;
        }
        constraint.selfIdealSize = OptionalSizeF(static_cast<float>(BACK_BUTTON_SIZE.ConvertToPx()),
            static_cast<float>(BACK_BUTTON_SIZE.ConvertToPx()));
        backButtonWrapper->Measure(constraint);
        return;
    }

    backButtonLayoutProperty->UpdateVisibility(VisibleType::GONE);
    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        return;
    }

    backButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        UpdateIconSize(backButtonNode);
        constraint.selfIdealSize = OptionalSizeF(static_cast<float>(backButtonWidth_.ConvertToPx()),
            static_cast<float>(backButtonWidth_.ConvertToPx()));
        backButtonWrapper->Measure(constraint);
        return;
    }

    constraint.selfIdealSize = OptionalSizeF(
        static_cast<float>(BACK_BUTTON_SIZE.ConvertToPx()), static_cast<float>(BACK_BUTTON_SIZE.ConvertToPx()));
    backButtonWrapper->Measure(constraint);
}

float TitleBarLayoutAlgorithm::GetTitleWidth(const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize)
{
    double paddingLeft = maxPaddingStart_.ConvertToPx();
    double paddingLeftForBackButton = paddingLeft;
    double paddingRight = maxPaddingEnd_.ConvertToPx();
    double paddingRightForMenu = paddingRight;
    double horizontalMargin = NAV_HORIZONTAL_MARGIN_L.ConvertToPx();
    auto backButtonWidth = BACK_BUTTON_ICON_SIZE.ConvertToPx();
    auto customBackButtonRightPadding = BUTTON_PADDING.ConvertToPx();
    auto defaultPaddingStart = defaultPaddingStart_.ConvertToPx();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        paddingLeft = paddingLeft_;
        paddingLeftForBackButton = paddingLeftForBackButton_;
        paddingRight = paddingRight_;
        paddingRightForMenu = paddingRightForMenu_;
        horizontalMargin = menuCompPadding_.ConvertToPx();
        backButtonWidth = backButtonWidth_.ConvertToPx();
        customBackButtonRightPadding = 0.0f;
        defaultPaddingStart = paddingRight;
    }
    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        // nav destination custom title
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(titleBarNode->GetParent());
        CHECK_NULL_RETURN(navDestination, 0.0f);
        auto isCustom = navDestination->GetPrevTitleIsCustomValue(false);
        float occupiedWidth = 0.0f;
        // left padding
        if (showBackButton_) {
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                occupiedWidth += backButtonWidth_.ConvertToPx();
            } else {
                occupiedWidth += (BACK_BUTTON_ICON_SIZE + BUTTON_PADDING).ConvertToPx();
            }
            occupiedWidth += paddingLeftForBackButton;
            occupiedWidth += isCustom ? 0.0f : horizontalMargin;
        } else {
            occupiedWidth += isCustom ? 0.0f : paddingLeft;
        }
        // compute right padding
        if (NearZero(menuOccupiedWidth_)) {
            occupiedWidth += isCustom ? 0.0f : paddingRight;
        } else {
            occupiedWidth += menuOccupiedWidth_;
            if (!navDestination->GetPrevMenuIsCustomValue(false)) {
                occupiedWidth += paddingRightForMenu;
                occupiedWidth += isCustom ? 0.0f : horizontalMargin;
            }
        }
        return titleBarSize.Width() < occupiedWidth ? 0.0f : titleBarSize.Width() - occupiedWidth;
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarNode->GetParent());
    CHECK_NULL_RETURN(navBarNode, 0.0f);
    float occupiedWidth = 0.0f;
    auto isCustom = navBarNode->GetPrevTitleIsCustomValue(false);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        // mini mode
        if (titleBarLayoutProperty->GetHideBackButtonValue(false)) {
            occupiedWidth += isCustom ? 0.0f : paddingLeft;
        } else {
            occupiedWidth += paddingLeft + backButtonWidth;
            // custom right padding is the back button hot zone
            occupiedWidth += isCustom ? customBackButtonRightPadding : horizontalMargin;
        }
        // compute right padding
        if (NearZero(menuOccupiedWidth_)) {
            occupiedWidth += isCustom ? 0.0f : paddingRight;
        } else {
            occupiedWidth += menuOccupiedWidth_;
            if (!navBarNode->GetPrevMenuIsCustomValue(false)) {
                occupiedWidth += defaultPaddingStart;
                occupiedWidth += isCustom ? 0.0f : horizontalMargin;
            }
        }
        return titleBarSize.Width() < occupiedWidth ? 0.0f : titleBarSize.Width() - occupiedWidth;
    }
    // left padding of full and free mode
    occupiedWidth = isCustom ? 0.0f : paddingLeft;
    // right padding of full mode
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FULL
        || isCustom) {
        occupiedWidth += isCustom ? 0.0f : paddingRight;
        return titleBarSize.Width() < occupiedWidth ? 0.0f : titleBarSize.Width() - occupiedWidth;
    }
    // right padding of free mode
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    if (titleBarPattern && titleBarPattern->IsFreeTitleUpdated() &&
        titleBarPattern->GetTempTitleOffsetY() < menuOccupiedHeight_) {
        if (NearZero(menuOccupiedWidth_)) {
            occupiedWidth += isCustom ? 0.0f : paddingRight;
        } else {
            occupiedWidth += menuOccupiedWidth_;
            if (!navBarNode->GetPrevMenuIsCustomValue(false)) {
                occupiedWidth += paddingLeft;
                occupiedWidth += isCustom ? 0.0f : horizontalMargin;
            }
        }
    } else {
        occupiedWidth += isCustom ? 0.0f : paddingRight;
    }
    return titleBarSize.Width() < occupiedWidth ? 0.0f : titleBarSize.Width() - occupiedWidth;
}

float TitleBarLayoutAlgorithm::WidthAfterAvoidMenuBarAndContainerModal(
    const RefPtr<TitleBarNode>& titleBarNode, float width)
{
    float afterAvoidWidth = width;
    CHECK_NULL_RETURN(titleBarNode, afterAvoidWidth);
    auto titleBarGeo = titleBarNode->GetGeometryNode();
    CHECK_NULL_RETURN(titleBarGeo, afterAvoidWidth);
    auto pipeline = titleBarNode->GetContext();
    CHECK_NULL_RETURN(pipeline, afterAvoidWidth);
    auto titleBarOffset = titleBarNode->GetParentGlobalOffsetDuringLayout();
    RectF avoidArea;
    if (NeedAvoidMenuBar(pipeline)) {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, afterAvoidWidth);
        auto appBar = container->GetAppBar();
        CHECK_NULL_RETURN(appBar, afterAvoidWidth);
        auto appBarRect = appBar->GetAppBarRect();
        CHECK_NULL_RETURN(appBarRect, afterAvoidWidth);
        avoidArea = appBarRect.value();
    }
    if (NeedAvoidContainerModal(pipeline, titleBarNode)) {
        RectF containerModal;
        RectF buttonsRect;
        auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
        CHECK_NULL_RETURN(avoidInfoMgr, afterAvoidWidth);
        if (avoidInfoMgr->GetContainerModalButtonsRect(containerModal, buttonsRect)) {
            if (NearZero(avoidArea.Width())) {
                avoidArea = buttonsRect;
            } else {
                avoidArea.CombineRectT(buttonsRect);
            }
        }
        titleBarOffset += titleBarGeo->GetFrameOffset();
    }
    if (NearZero(avoidArea.Width())) {
        return afterAvoidWidth;
    }

    auto avoidAreaOffset = avoidArea.GetOffset();
    auto avoidAreaSize = avoidArea.GetSize();
    auto avoidWidth = titleBarOffset.GetX() + titleBarGeo->GetFrameSize().Width() - avoidAreaOffset.GetX();
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        avoidWidth = avoidAreaOffset.GetX() + avoidAreaSize.Width() - titleBarOffset.GetX();
    }
    auto avoidAreaBottom = avoidAreaOffset.GetY() + avoidAreaSize.Height();
    if (LessOrEqual(titleBarOffset.GetY(), avoidAreaBottom) && GreatOrEqual(avoidWidth, 0.0f)) {
        afterAvoidWidth = afterAvoidWidth - avoidWidth;
    }

    return LessOrEqual(afterAvoidWidth, 0.0f) ? 0.0f : afterAvoidWidth;
}

void TitleBarLayoutAlgorithm::MeasureSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize, float maxWidth)
{
    auto subtitleNode = titleBarNode->GetSubtitle();
    CHECK_NULL_VOID(subtitleNode);
    auto index = titleBarNode->GetChildIndexById(subtitleNode->GetId());
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(subtitleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        // limit the maxHeight of the subtitle to adapt to the scenarios where the text is too high
        constraint.maxSize.SetHeight(SUBTITLE_MAX_HEIGHT_RADIO * titleBarSize.Height());
    } else {
        constraint.maxSize.SetHeight(titleBarSize.Height());
    }
    constraint.maxSize.SetWidth(maxWidth);
    subtitleWrapper->Measure(constraint);
}

void TitleBarLayoutAlgorithm::MeasureTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize, float maxWidth)
{
    auto titleNode = titleBarNode->GetTitle();
    CHECK_NULL_VOID(titleNode);
    auto index = titleBarNode->GetChildIndexById(titleNode->GetId());
    auto titleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    constraint.maxSize.SetHeight(titleBarSize.Height());

    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(titleBarNode->GetParent());
        CHECK_NULL_VOID(navDestination);
        auto isCustomTitle = navDestination->GetPrevTitleIsCustomValue(false);
        if (isCustomTitle) {
            constraint.parentIdealSize.SetWidth(maxWidth);
            constraint.maxSize.SetWidth(maxWidth);
            // custom title must be single line title

            constraint.parentIdealSize.SetHeight(titleBarSize.Height());
            constraint.maxSize.SetHeight(titleBarSize.Height());
            titleWrapper->Measure(constraint);
            return;
        }
        constraint.maxSize.SetWidth(maxWidth);
        if (!titleBarNode->GetSubtitle()) {
            constraint.maxSize.SetHeight(titleBarSize.Height());
            titleWrapper->Measure(constraint);
            return;
        }
        auto subtitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
        auto subtitleHeight = subtitle->GetGeometryNode()->GetFrameSize().Height();
        constraint.maxSize.SetHeight(titleBarSize.Height() - subtitleHeight);
        titleWrapper->Measure(constraint);
        return;
    }
    // NavigationCustomTitle: Custom title + height
    if (titleBarLayoutProperty->HasTitleHeight()) {
        constraint.parentIdealSize.SetWidth(maxWidth);
        constraint.maxSize.SetWidth(maxWidth);
        constraint.parentIdealSize.SetHeight(titleBarSize.Height());
        constraint.maxSize.SetHeight(titleBarSize.Height());
        titleWrapper->Measure(constraint);
        return;
    }
    // subTitle
    auto titleMode = titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    auto subTitle = titleBarNode->GetSubtitle();
    float titleSpaceVertical = 0.0f;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        titleSpaceVertical = static_cast<float>(titleSpaceVertical_.ConvertToPx());
    }
    if (subTitle) {
        // common title
        auto index = titleBarNode->GetChildIndexById(subTitle->GetId());
        auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(subtitleWrapper);
        auto subtitleHeight = subtitleWrapper->GetGeometryNode()->GetFrameSize().Height();
        // mini mode double title height is 56vp, free/full mode is 82vp
        auto maxTitleHeight = titleMode == NavigationTitleMode::MINI ? SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx() :
            DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx();
        constraint.maxSize.SetWidth(maxWidth);
        constraint.maxSize.SetHeight(maxTitleHeight - subtitleHeight - titleSpaceVertical);
        titleWrapper->Measure(constraint);
        return;
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarNode->GetParent());
    CHECK_NULL_VOID(navBarNode);
    auto isCustomTitle = navBarNode->GetPrevTitleIsCustomValue(false);
    // single line title and mini mode
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (isCustomTitle) {
            constraint.parentIdealSize.SetWidth(maxWidth);
            constraint.maxSize.SetWidth(maxWidth);
            constraint.parentIdealSize.SetHeight(titleBarSize.Height());
            constraint.maxSize.SetHeight(titleBarSize.Height());
        } else {
            constraint.maxSize.SetWidth(maxWidth);
            constraint.maxSize.SetHeight(titleBarSize.Height());
        }
        titleWrapper->Measure(constraint);
        return;
    }
    // custom builder
    if (isCustomTitle) {
        constraint.parentIdealSize.SetWidth(maxWidth);
        constraint.maxSize.SetWidth(maxWidth);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            constraint.parentIdealSize.SetHeight(titleBarSize.Height());
        } else {
            auto isCustomMenu = navBarNode->GetPrevMenuIsCustomValue(false);
            // if has menu and menu is not custom, max height is single line height
            auto maxHeight = NearZero(menuOccupiedWidth_) ? titleBarSize.Height()
                             : isCustomMenu       ? titleBarSize.Height() - menuOccupiedHeight_
                                                  : SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx();
            constraint.parentIdealSize.SetHeight(maxHeight);
            constraint.maxSize.SetHeight(maxHeight);
        }
        titleWrapper->Measure(constraint);
        return;
    }
    // resourceStr title
    constraint.maxSize.SetWidth(maxWidth);
    constraint.maxSize.SetHeight(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleWrapper->Measure(constraint);
}

void TitleBarLayoutAlgorithm::MeasureMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto menuNode = titleBarNode->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto index = titleBarNode->GetChildIndexById(menuNode->GetId());
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(menuWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();

    auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(titleBarNode->GetParent());
    CHECK_NULL_VOID(nodeBase);
    bool isCustomMenu = nodeBase->GetPrevMenuIsCustomValue(false);
    auto patternBase = nodeBase->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(patternBase);
    int32_t maxMenu = patternBase->GetMaxMenuNum();

    if (isCustomMenu) {
        // custom title can't be higher than 56vp
        constraint.parentIdealSize.SetHeight(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
        if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI &&
            !titleBarLayoutProperty->HasTitleHeight()) {
            auto maxWidth = static_cast<float>(MENU_ITEM_SIZE.ConvertToPx()) * maxMenu +
                            defaultPaddingStart_.ConvertToPx();
            constraint.parentIdealSize.SetWidth(maxWidth);
        }
        menuWrapper->Measure(constraint);
        menuOccupiedWidth_ = menuWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
        menuOccupiedHeight_ = menuWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
        return;
    }
    auto menuItemNum = static_cast<int32_t>(menuNode->GetChildren().size());
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        if (menuItemNum >= maxMenu) {
            menuOccupiedWidth_ = static_cast<float>(iconBackgroundWidth_.ConvertToPx()) * maxMenu +
                static_cast<float>(menuCompPadding_.ConvertToPx()) * (maxMenu - 1);
        } else {
            // the number of the padding between menuItem.
            int32_t paddingAmount = std::max(menuItemNum - 1, 0);
            menuOccupiedWidth_ = static_cast<float>(iconBackgroundWidth_.ConvertToPx()) * menuItemNum +
                static_cast<float>(menuCompPadding_.ConvertToPx()) * paddingAmount;
        }
    } else {
        if (menuItemNum >= maxMenu) {
            menuOccupiedWidth_ = static_cast<float>(MENU_ITEM_SIZE.ConvertToPx()) * maxMenu;
        } else {
            menuOccupiedWidth_ = static_cast<float>(MENU_ITEM_SIZE.ConvertToPx()) * menuItemNum;
        }
    }
    constraint.selfIdealSize = OptionalSizeF(menuOccupiedWidth_, menuOccupiedHeight_);
    menuWrapper->Measure(constraint);
}

void TitleBarLayoutAlgorithm::ShowBackButtonLayout(LayoutWrapper* layoutWrapper,
    RefPtr<GeometryNode>& geometryNode, const RefPtr<LayoutWrapper>& backButtonWrapper, float titleBarHeight)
{
    Dimension backButtonHeight = BACK_BUTTON_SIZE;
    float paddingLeft = (maxPaddingStart_ - BUTTON_PADDING).ConvertToPx();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        backButtonHeight = backButtonHeight_;
        paddingLeft = paddingLeftForBackButton_;
        BackButtonLayout(layoutWrapper);
    }
    auto offsetY = (titleBarHeight - backButtonHeight.ConvertToPx()) / 2.0f;
    auto offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, paddingLeft);
    OffsetF backButtonOffset = OffsetF(offsetX, offsetY);
    geometryNode->SetMarginFrameOffset(backButtonOffset);
    backButtonWrapper->Layout();
}

void TitleBarLayoutAlgorithm::LayoutBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarGeometryNode = titleBarNode->GetGeometryNode();
    CHECK_NULL_VOID(titleBarGeometryNode);
    auto titleBarHeight = titleBarGeometryNode->GetFrameSize().Height();
    auto backButtonNode = titleBarNode->GetBackButton();
    CHECK_NULL_VOID(backButtonNode);
    auto index = titleBarNode->GetChildIndexById(backButtonNode->GetId());
    auto backButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(backButtonWrapper);
    auto geometryNode = backButtonWrapper->GetGeometryNode();

    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        OffsetF backButtonOffset = OffsetF(0.0f, 0.0f);
        if (!showBackButton_) {
            SizeF size = SizeF(0.0f, 0.0f);
            geometryNode->SetFrameSize(size);
            backButtonWrapper->Layout();
            return;
        }
        bool useContainerModalTitleHeight = titleBarNode->UseContainerModalTitleHeight();
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            auto fullHeight = useContainerModalTitleHeight ? titleBarHeight : menuOccupiedHeight_;
            auto offsetY = (fullHeight - BACK_BUTTON_ICON_SIZE.ConvertToPx()) / 2.0f;
            auto offsetXResult = ChangeOffsetByDirection(layoutWrapper, geometryNode,
                static_cast<float>(maxPaddingStart_.ConvertToPx()));
            backButtonOffset = OffsetF(offsetXResult, offsetY);
            geometryNode->SetMarginFrameOffset(backButtonOffset);
            backButtonWrapper->Layout();
            return;
        }

        float height = useContainerModalTitleHeight ?
            titleBarHeight : titleBarLayoutProperty->GetTitleHeightValue(SINGLE_LINE_TITLEBAR_HEIGHT).ConvertToPx();
        ShowBackButtonLayout(layoutWrapper, geometryNode, backButtonWrapper, height);
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        OffsetF backButtonOffset = OffsetF(0.0f, 0.0f);
        geometryNode->SetMarginFrameOffset(backButtonOffset);
        backButtonWrapper->Layout();
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        OffsetF backButtonOffset = OffsetF(0.0f, 0.0f);
        geometryNode->SetMarginFrameOffset(backButtonOffset);
        backButtonWrapper->Layout();
        return;
    }

    ShowBackButtonLayout(layoutWrapper, geometryNode, backButtonWrapper,
        titleBarLayoutProperty->GetTitleHeightValue(SINGLE_LINE_TITLEBAR_HEIGHT).ConvertToPx());
}

float TitleBarLayoutAlgorithm::GetFullModeTitleOffsetY(float titleHeight, float subtitleHeight,
    RefPtr<GeometryNode> titleBarGeometryNode)
{
    auto titleBarHeight = titleBarGeometryNode->GetFrameSize().Height();
    // fixed white space menuHeight
    OffsetF titleOffset = OffsetF(0.0f, 0.0f);
    float offsetY = 0.0f;
    auto titleSpace = titleBarHeight - menuOccupiedHeight_ - static_cast<float>(paddingTopTwolines_.ConvertToPx());
    auto titleRealHeight = titleHeight + subtitleHeight + navTitleSpaceVertical_;
    float dividerOffset = 2.0f;
    if (NearZero(subtitleHeight) && titleHeight < titleBarHeight - menuOccupiedHeight_) {
        offsetY = (titleBarHeight - menuOccupiedHeight_ - titleRealHeight) / dividerOffset;
        return offsetY;
    }
    if (titleRealHeight <= titleSpace) {
        offsetY = (titleSpace - titleRealHeight +
            static_cast<float>(paddingTopTwolines_.ConvertToPx())) / dividerOffset;
    } else {
        offsetY = titleSpace - titleRealHeight;
    }

    return offsetY;
}

void TitleBarLayoutAlgorithm::LayoutTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, float subtitleHeight)
{
    auto titleNode = titleBarNode->GetTitle();
    CHECK_NULL_VOID(titleNode);
    auto index = titleBarNode->GetChildIndexById(titleNode->GetId());
    auto titleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleWrapper);
    auto geometryNode = titleWrapper->GetGeometryNode();
    auto titleBarGeometryNode = titleBarNode->GetGeometryNode();
    CHECK_NULL_VOID(titleBarGeometryNode);
    auto titleBarHeight = titleBarGeometryNode->GetFrameSize().Height();
    CHECK_NULL_VOID(geometryNode);

    auto titleHeight = geometryNode->GetFrameSize().Height();
    float offsetY = 0.0f;
    float dividerOffset = 2.0f;
    bool isNavDestination = titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION;
    bool useContainerModalTitleHeight = titleBarNode->UseContainerModalTitleHeight();
    if (!NearZero(subtitleHeight)) {
        auto fullHeight = doubleLineTitleBarHeight_;
        if (isNavDestination && useContainerModalTitleHeight) {
            fullHeight = titleBarHeight;
        }
        offsetY = (fullHeight - titleHeight - subtitleHeight - navTitleSpaceVertical_) / dividerOffset;
    } else {
        navTitleSpaceVertical_ = 0.0f;
        auto fullHeight = singleLineTitleHeight_;
        if (isNavDestination && useContainerModalTitleHeight) {
            fullHeight = titleBarHeight;
        }
        offsetY = (fullHeight - titleHeight) / dividerOffset;
    }
    // navDestination title bar
    if (isNavDestination) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(titleBarNode->GetParent());
        CHECK_NULL_VOID(navDestination);
        auto isCustom = navDestination->GetPrevTitleIsCustomValue(false);
        OffsetF titleOffset = OffsetF(0.0f, 0.0f);
        // add sdk 9 compatible
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (showBackButton_) {
                auto offsetXResult = ChangeOffsetByDirection(layoutWrapper, geometryNode,
                    static_cast<float>(
                        (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + NAV_HORIZONTAL_MARGIN_M).ConvertToPx()));
                titleOffset = OffsetF(offsetXResult, offsetY);
                geometryNode->SetMarginFrameOffset(titleOffset);
                titleWrapper->Layout();
                return;
            }
            auto offsetXResult = ChangeOffsetByDirection(layoutWrapper, geometryNode,
                static_cast<float>(maxPaddingStart_.ConvertToPx()));
            titleOffset = OffsetF(offsetXResult, offsetY);
            geometryNode->SetMarginFrameOffset(titleOffset);
            titleWrapper->Layout();
            return;
        }
        if (showBackButton_) {
            float offsetX = 0.0f;
            if (isCustom) {
                offsetX = paddingLeft_ + navBackIconWidth_ + navButtonPadding_;
            } else {
                offsetX = paddingLeftForBackButton_ + navBackIconWidth_ + navHorizontalMargin_;
            }
            offsetY = isCustom ? 0.0f : offsetY;
            auto offsetXResult = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
            titleOffset = OffsetF(offsetXResult, offsetY);
            geometryNode->SetMarginFrameOffset(titleOffset);
            titleWrapper->Layout();
            return;
        }
        auto offsetX = isCustom ? 0.0f : paddingLeft_;
        offsetY = isCustom ? 0.0f : offsetY;
        auto offsetXResult = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
        titleOffset = OffsetF(offsetXResult, offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        titleWrapper->Layout();
        return;
    }

    // navBar title bar
    auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarNode->GetParent());
    CHECK_NULL_VOID(navBarNode);
    auto isCustom = navBarNode->GetPrevTitleIsCustomValue(false);
    // full mode
    if (!isCustom) {
        if (!NearZero(subtitleHeight)) {
            offsetY = (doubleLineTitleBarHeight_ - titleHeight -
                subtitleHeight - navTitleSpaceVertical_) / dividerOffset;
        } else {
            navTitleSpaceVertical_ = 0.0f;
            offsetY = (singleLineTitleHeight_ - titleHeight) / dividerOffset;
        }
    }
    // only control layout when titleMode is free
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
                auto offsetX = maxPaddingStart_.ConvertToPx();
                offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
                geometryNode->SetMarginFrameOffset(OffsetF { offsetX, offsetY });
                titleWrapper->Layout();
                return;
            }
            auto offsetX =  (defaultPaddingStart_ + BACK_BUTTON_ICON_SIZE + NAV_HORIZONTAL_MARGIN_L).ConvertToPx();
            offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
            geometryNode->SetMarginFrameOffset(OffsetF {offsetX, offsetY});
            titleWrapper->Layout();
            return;
        }
        // NavigationCustomTitle and Custom builder layout margin is (0, 0);
        offsetY = isCustom ? 0 : offsetY;
        if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
            auto offsetX = isCustom ? 0.0f : paddingLeft_;
            offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
            OffsetF titleOffset = OffsetF(offsetX, offsetY);
            geometryNode->SetMarginFrameOffset(titleOffset);
            titleWrapper->Layout();
            return;
        }

        auto offsetX = isCustom ? (paddingLeft_ + navBackIconWidth_ + navButtonPadding_) :
                (paddingLeft_ + navBackIconWidth_ + navHorizontalMargin_);
        offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
        OffsetF offset = OffsetF(offsetX, offsetY);
        geometryNode->SetMarginFrameOffset(offset);
        titleWrapper->Layout();
        return;
    }

    float offsetX = paddingLeft_;
    offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        offsetY = GetFullModeTitleOffsetY(titleHeight, subtitleHeight, titleBarGeometryNode);
    }
    // full mode
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            offsetX = maxPaddingStart_.ConvertToPx();
            offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
            geometryNode->SetMarginFrameOffset(OffsetF { offsetX, menuOccupiedHeight_ + offsetY });
            titleWrapper->Layout();
            return;
        }
        // full mode
        if (isCustom) {
            // custom title margin is (0.0f, menuOccupiedHeight_)
            float customOffsetX = 0.0f;
            customOffsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, customOffsetX);
            geometryNode->SetMarginFrameOffset(OffsetF { customOffsetX, menuOccupiedHeight_});
            titleWrapper->Layout();
            return;
        }
        // fixed white space menuHeight
        OffsetF titleOffset = OffsetF(0.0f, 0.0f);
        titleOffset = OffsetF(offsetX, menuOccupiedHeight_ + offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        titleWrapper->Layout();
        return;
    }

    // free mode
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    if (isCustom) {
        isInitialTitle_ = false;
        // customBuilder and NavigationCustomTitle offset is (0.0f, menuOccupiedHeight_)
        auto customOffsetX = 0.0f;
        customOffsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, customOffsetX);
        geometryNode->SetMarginFrameOffset(OffsetF { customOffsetX, menuOccupiedHeight_});
        titleWrapper->Layout();
        return;
    }
    auto title = AceType::DynamicCast<FrameNode>(titleNode);
    CHECK_NULL_VOID(title);
    if (isInitialTitle_) {
        auto textLayoutProperty = title->GetLayoutProperty<TextLayoutProperty>();
        if (!textLayoutProperty) {
            // current title mode is Navigation common title
            OffsetF titleOffset = OffsetF(offsetX, menuOccupiedHeight_+ offsetY);
            geometryNode->SetMarginFrameOffset(titleOffset);
            titleWrapper->Layout();
            return;
        }
        MeasureContext context;
        if (textLayoutProperty->HasContent()) {
            context.textContent = UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue());
        }
        context.fontSize = titleFontSize_;
#ifdef ENABLE_ROSEN_BACKEND
        minTitleHeight_ = static_cast<float>(RosenRenderCustomPaint::MeasureTextSizeInner(context).Height());
#else
        minTitleHeight_ = 0.0;
#endif
        initialTitleOffsetY_ = menuOccupiedHeight_ + offsetY;
        isInitialTitle_ = false;
        auto titleOffset = OffsetF(offsetX, initialTitleOffsetY_);
        titlePattern->SetCurrentTitleOffsetY(initialTitleOffsetY_);
        geometryNode->SetMarginFrameOffset(titleOffset);
        titleWrapper->Layout();
        return;
    }

    if (NearZero(titlePattern->GetTempTitleOffsetY())) {
        initialTitleOffsetY_ = menuOccupiedHeight_ + offsetY;
        titlePattern->SetCurrentTitleOffsetY(initialTitleOffsetY_);
        auto titleOffset = OffsetF(offsetX, initialTitleOffsetY_);
        geometryNode->SetMarginFrameOffset(titleOffset);
        titleWrapper->Layout();
        return;
    }
    auto overDragOffset = titlePattern->GetOverDragOffset();
    auto titleOffset = OffsetF(offsetX, titlePattern->GetTempTitleOffsetY() + overDragOffset / OVERDRAG_DIVIDE_NUM);
    titlePattern->SetCurrentTitleOffsetY(titleOffset.GetY());
    geometryNode->SetMarginFrameOffset(titleOffset);
    titleWrapper->Layout();
}

void TitleBarLayoutAlgorithm::LayoutSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, float titleHeight)
{
    auto subtitleNode = titleBarNode->GetSubtitle();
    CHECK_NULL_VOID(subtitleNode);
    auto index = titleBarNode->GetChildIndexById(subtitleNode->GetId());
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(subtitleWrapper);
    auto geometryNode = subtitleWrapper->GetGeometryNode();
    auto titleBarGeometryNode = titleBarNode->GetGeometryNode();
    CHECK_NULL_VOID(titleBarGeometryNode);
    auto titleBarHeight = titleBarGeometryNode->GetFrameSize().Height();
    CHECK_NULL_VOID(geometryNode);

    auto subtitleHeight = geometryNode->GetFrameSize().Height();
    float offsetY = 0.0f;
    float dividerOffset = 2.0f;
    bool isNavDestination = titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION;
    bool useContainerModalTitleHeight = titleBarNode->UseContainerModalTitleHeight();
    if (!NearZero(titleHeight)) {
        auto fullHeight = doubleLineTitleBarHeight_;
        if (isNavDestination && useContainerModalTitleHeight) {
            fullHeight = titleBarHeight;
        }
        offsetY = (fullHeight - titleHeight -
                  subtitleHeight - navTitleSpaceVertical_) / dividerOffset + titleHeight + navTitleSpaceVertical_;
    } else {
        navTitleSpaceVertical_ = 0.0f;
        auto fullHeight = singleLineTitleHeight_;
        if (isNavDestination && useContainerModalTitleHeight) {
            fullHeight = titleBarHeight;
        }
        offsetY = (fullHeight - subtitleHeight) / dividerOffset;
    }
    // navDestination title bar
    if (isNavDestination) {
        OffsetF subTitleOffset = OffsetF(0.0f, 0.0f);
        // subtitle doesn't support custom title
        if (showBackButton_) {
            float offsetX = 0.0f;
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
                offsetX = (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + NAV_HORIZONTAL_MARGIN_M).ConvertToPx();
            } else {
                offsetX = paddingLeftForBackButton_ + navBackIconWidth_ + navHorizontalMargin_;
            }
            offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
            subTitleOffset = OffsetF(offsetX, offsetY);
            geometryNode->SetMarginFrameOffset(subTitleOffset);
            subtitleWrapper->Layout();
            return;
        }

        auto offsetXResult = ChangeOffsetByDirection(layoutWrapper, geometryNode, paddingLeft_);
        subTitleOffset = OffsetF(offsetXResult, offsetY);
        geometryNode->SetMarginFrameOffset(subTitleOffset);
        subtitleWrapper->Layout();
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        float offsetX = paddingLeft_;
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            auto titleOffsetY = GetFullModeTitleOffsetY(titleHeight, subtitleHeight, titleBarGeometryNode);
            offsetY = titleOffsetY + titleHeight + navTitleSpaceVertical_;
        }
        offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
        initialSubtitleOffsetY_ = menuOccupiedHeight_ + offsetY;
        if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) {
            if (isInitialSubtitle_) {
                isInitialSubtitle_ = false;
                OffsetF titleOffset = OffsetF(offsetX, initialSubtitleOffsetY_);
                geometryNode->SetMarginFrameOffset(titleOffset);
                subtitleWrapper->Layout();
                return;
            }

            auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
            CHECK_NULL_VOID(titlePattern);
            if (NearZero(titlePattern->GetTempTitleOffsetY())) {
                OffsetF titleOffset = OffsetF(offsetX, initialSubtitleOffsetY_);
                geometryNode->SetMarginFrameOffset(titleOffset);
                subtitleWrapper->Layout();
                return;
            }
            auto overDragOffset = titlePattern->GetOverDragOffset();
            OffsetF titleOffset = OffsetF(
                offsetX, titlePattern->GetTempSubTitleOffsetY() + overDragOffset / OVERDRAG_DIVIDE_NUM);
            geometryNode->SetMarginFrameOffset(titleOffset);
            subtitleWrapper->Layout();
            return;
        }
        // full mode
        OffsetF titleOffset = OffsetF(offsetX, initialSubtitleOffsetY_);
        geometryNode->SetMarginFrameOffset(titleOffset);
        subtitleWrapper->Layout();
        return;
    }
    // mini mode + hideBackButton true
    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        auto offsetX = paddingLeft_;
        offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
        OffsetF titleOffset = OffsetF(offsetX, offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        subtitleWrapper->Layout();
        return;
    }
    float occupiedWidth = 0.0f;
    // mini mode + back button
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        occupiedWidth = static_cast<float>((maxPaddingStart_ + BACK_BUTTON_ICON_SIZE +
            NAV_HORIZONTAL_MARGIN_M).ConvertToPx());
    } else {
        occupiedWidth = paddingLeft_ + navBackIconWidth_ + navHorizontalMargin_;
    }
    auto miniOffsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, occupiedWidth);
    OffsetF offset = OffsetF(miniOffsetX, offsetY);
    geometryNode->SetMarginFrameOffset(offset);
    subtitleWrapper->Layout();
}

void TitleBarLayoutAlgorithm::LayoutMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, float subtitleHeight)
{
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarGeometryNode = titleBarNode->GetGeometryNode();
    CHECK_NULL_VOID(titleBarGeometryNode);
    auto titleBarHeight = titleBarGeometryNode->GetFrameSize().Height();
    bool useContainerModalTitleHeight = titleBarNode->UseContainerModalTitleHeight();
    auto menuNode = titleBarNode->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto index = titleBarNode->GetChildIndexById(menuNode->GetId());
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(menuWrapper);
    auto geometryNode = menuWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto menuWidth = geometryNode->GetMarginFrameSize().Width();
    auto maxWidth = geometryNode->GetParentLayoutConstraint()->maxSize.Width();
    maxWidth = WidthAfterAvoidMenuBarAndContainerModal(titleBarNode, maxWidth);
    auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(titleBarNode->GetParent());
    CHECK_NULL_VOID(nodeBase);
    bool isCustomMenu = nodeBase->GetPrevMenuIsCustomValue(false);
    auto currentOffsetX = maxWidth - menuWidth - defaultPaddingStart_.ConvertToPx();
    auto isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) {
        auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
        auto overDragOffset = titlePattern->GetOverDragOffset();
        float menuOffsetY = 0.0f;
        if (!isCustomMenu) {
            float totalHeight = useContainerModalTitleHeight ?
                titleBarHeight : SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx();
            menuOffsetY = (totalHeight - menuOccupiedHeight_) / 2.0f;
        }
        // custom menu width has no right padding
        float offsetX = 0.0f;
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            offsetX = isCustomMenu ? maxWidth - menuWidth
                                   : (maxWidth - menuWidth - paddingRightForMenu_);
        } else {
            offsetX = isCustomMenu ? maxWidth - menuWidth
                                   : (maxWidth - menuWidth - static_cast<float>(maxPaddingEnd_.ConvertToPx()) +
                                         BUTTON_PADDING.ConvertToPx());
        }
        currentOffsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, currentOffsetX);
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            geometryNode->SetMarginFrameOffset(OffsetF { currentOffsetX,
                menuOffsetY + overDragOffset / MENU_OFFSET_RATIO });
            menuWrapper->Layout();
            return;
        }
        offsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, offsetX);
        // Fixed the issue of repeatedly adding margin in SetMarginFrameOffset for RTL
        if (isRightToLeft && geometryNode->GetMargin()) {
            offsetX = offsetX - geometryNode->GetMargin()->left.value_or(.0f) -
                      geometryNode->GetMargin()->right.value_or(.0f);
        }
        OffsetF menuOffset(offsetX, menuOffsetY + overDragOffset / MENU_OFFSET_RATIO);
        geometryNode->SetMarginFrameOffset(menuOffset);
        menuWrapper->Layout();
        return;
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        float totalHeight = titleBarHeight;
        if (!useContainerModalTitleHeight) {
            auto totalHeightDimension = NearZero(subtitleHeight) ?
                SINGLE_LINE_TITLEBAR_HEIGHT : DOUBLE_LINE_TITLEBAR_HEIGHT;
            totalHeight = totalHeightDimension.ConvertToPx();
        }
        geometryNode->SetMarginFrameOffset(OffsetF { currentOffsetX, (totalHeight - menuOccupiedHeight_) / 2.0f });
        menuWrapper->Layout();
        return;
    }
    // custom menu doesn't have top padding. if menu isn't custom, menu items has top padding
    auto menuOffsetY =  0.0f;
    if (!isCustomMenu) {
        float totalHeight = useContainerModalTitleHeight ?
            titleBarHeight : SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx();
        menuOffsetY = (totalHeight - menuOccupiedHeight_) / 2.0f;
    }
    auto menuOffsetX = maxWidth - menuWidth;
    // custom menu doesn't have right padding. if menu isn't custom, menu items has right padding
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        menuOffsetX =
            isCustomMenu ? menuOffsetX : (menuOffsetX - paddingRight_);
    } else {
        menuOffsetX =
            isCustomMenu ? menuOffsetX : (menuOffsetX - maxPaddingEnd_.ConvertToPx() + BUTTON_PADDING.ConvertToPx());
    }
    menuOffsetX = ChangeOffsetByDirection(layoutWrapper, geometryNode, menuOffsetX);
    // Fixed the issue of repeatedly adding margin in SetMarginFrameOffset for RTL
    if (isRightToLeft && geometryNode->GetMargin()) {
        menuOffsetX = menuOffsetX - geometryNode->GetMargin()->left.value_or(.0f) -
                      geometryNode->GetMargin()->right.value_or(.0f);
    }
    OffsetF menuOffset(menuOffsetX, menuOffsetY);
    geometryNode->SetMarginFrameOffset(menuOffset);
    menuWrapper->Layout();
}

// set variables from theme
void TitleBarLayoutAlgorithm::InitializeTheme(const RefPtr<TitleBarNode>& titleBarNode, const SizeF& titleBarSize)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    maxPaddingStart_ = theme->GetMaxPaddingStart();
    maxPaddingEnd_ = theme->GetMaxPaddingEnd();
    menuOccupiedHeight_ = theme->GetHeight().ConvertToPx();
    defaultPaddingStart_ = theme->GetDefaultPaddingStart();
    iconSize_ = theme->GetMenuIconSize();
    titleFontSize_ = theme->GetTitleFontSize();
    menuCompPadding_ = theme->GetCompPadding();
    iconBackgroundWidth_ = theme->GetIconBackgroundWidth();
    backButtonWidth_ = theme->GetBackButtonWidth();
    backButtonHeight_ = theme->GetBackButtonHeight();
    paddingTopTwolines_ = theme->GetPaddingTopTwolines();
    titleSpaceVertical_ = theme->GetTitleSpaceVertical();
    backIconWidth_ = theme->GetIconWidth();
    backIconHeight_ = theme->GetIconHeight();
    singleLineTitleHeight_ = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    doubleLineTitleBarHeight_ = static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    navTitleSpaceVertical_ = 0.0f;
    paddingLeft_ = maxPaddingStart_.ConvertToPx();
    navBackIconWidth_ = BACK_BUTTON_ICON_SIZE.ConvertToPx();
    navButtonPadding_ = BUTTON_PADDING.ConvertToPx();
    navHorizontalMargin_ = NAV_HORIZONTAL_MARGIN_L.ConvertToPx();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        doubleLineTitleBarHeight_ = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
        navTitleSpaceVertical_ = static_cast<float>(titleSpaceVertical_.ConvertToPx());
        CHECK_NULL_VOID(titleBarNode);
        auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titlePattern);
        auto options = titlePattern->GetTitleBarOptions();
        auto paddingStart = options.brOptions.paddingStart;
        if (paddingStart.has_value()) {
            paddingLeft_ = NavigationTitleUtil::ParseCalcDimensionToPx(paddingStart, titleBarSize.Width());
            paddingLeftForBackButton_ = paddingLeft_;
        } else {
            paddingLeft_ = theme->GetMarginLeft().ConvertToPx();
            paddingLeftForBackButton_ = theme->GetMarginLeftForBackButton().ConvertToPx();
        }
        auto paddingEnd = options.brOptions.paddingEnd;
        if (paddingEnd.has_value()) {
            paddingRight_ = NavigationTitleUtil::ParseCalcDimensionToPx(paddingEnd, titleBarSize.Width());
            paddingRightForMenu_ = paddingRight_;
        } else {
            paddingRight_ = theme->GetMarginRight().ConvertToPx();
            paddingRightForMenu_ = theme->GetMarginRightForMenu().ConvertToPx();
        }
        navBackIconWidth_ = backIconWidth_.ConvertToPx();
        navButtonPadding_ = (MENU_BUTTON_PADDING + MENU_BUTTON_PADDING).ConvertToPx();
        navHorizontalMargin_ = navButtonPadding_ + menuCompPadding_.ConvertToPx();
    }
}

void TitleBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(titleBarNode);
    auto layoutProperty = AceType::DynamicCast<TitleBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    InitializeTheme(titleBarNode, size);
    do {
        if (layoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) !=
            TitleBarParentType::NAV_DESTINATION) {
            break;
        }
        auto navDestinationNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetParent());
        CHECK_NULL_BREAK(navDestinationNode);
        auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(navDestinationNode->GetPattern());
        CHECK_NULL_BREAK(navDestinationPattern);
        showBackButton_ = navDestinationPattern->GetBackButtonState();
    } while (false);
    MeasureBackButton(layoutWrapper, titleBarNode, layoutProperty);
    MeasureMenu(layoutWrapper, titleBarNode, layoutProperty);
    auto titleMaxWidth = GetTitleWidth(titleBarNode, layoutProperty, size);
    titleMaxWidth = WidthAfterAvoidMenuBarAndContainerModal(titleBarNode, titleMaxWidth);
    MeasureSubtitle(layoutWrapper, titleBarNode, layoutProperty, size, titleMaxWidth);
    MeasureTitle(layoutWrapper, titleBarNode, layoutProperty, size, titleMaxWidth);
    titlePattern->SetCurrentTitleBarHeight(size.Height());
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void TitleBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(titleBarNode);
    auto pipeline = titleBarNode->GetContext();
    if (NeedAvoidMenuBar(pipeline) ||
        NeedAvoidContainerModal(pipeline, titleBarNode)) {
        // TitleBar need run measure again during Layout
        // when avoiding menuBar in atomic service, or avoiding containerModal.
        Measure(layoutWrapper);
    }
    auto layoutProperty = AceType::DynamicCast<TitleBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    LayoutBackButton(layoutWrapper, titleBarNode, layoutProperty);

    float subtitleHeight = 0.0f;
    auto subtitleNode = titleBarNode->GetSubtitle();
    if (subtitleNode) {
        auto index = titleBarNode->GetChildIndexById(subtitleNode->GetId());
        auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(subtitleWrapper);
        auto geometryNode = subtitleWrapper->GetGeometryNode();
        subtitleHeight = geometryNode->GetFrameSize().Height();
    }
    LayoutTitle(layoutWrapper, titleBarNode, layoutProperty, subtitleHeight);

    float titleHeight = 0.0f;
    auto titleNode = titleBarNode->GetTitle();
    if (titleNode) {
        auto index = titleBarNode->GetChildIndexById(titleNode->GetId());
        auto titleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(titleWrapper);
        auto geometryNode = titleWrapper->GetGeometryNode();
        titleHeight = geometryNode->GetFrameSize().Height();
    }
    LayoutSubtitle(layoutWrapper, titleBarNode, layoutProperty, titleHeight);

    LayoutMenu(layoutWrapper, titleBarNode, layoutProperty, subtitleHeight);
}

float TitleBarLayoutAlgorithm::ChangeOffsetByDirection(LayoutWrapper* layoutWrapper,
    const RefPtr<NG::GeometryNode>& childGeometryNode, float offsetX) const
{
    CHECK_NULL_RETURN(layoutWrapper, offsetX);
    CHECK_NULL_RETURN(childGeometryNode, offsetX);
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        auto geometryNode = layoutWrapper->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, offsetX);
        auto parentWidth = geometryNode->GetFrameSize().Width();
        offsetX = parentWidth - offsetX - childGeometryNode->GetFrameSize().Width();
    }
    return offsetX;
}
} // namespace OHOS::Ace::NG
