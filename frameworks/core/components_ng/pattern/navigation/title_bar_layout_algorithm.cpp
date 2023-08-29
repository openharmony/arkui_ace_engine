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

#include "core/components_ng/pattern/navigation/title_bar_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/measure_util.h"
#include "base/utils/utils.h"
#include "core/components/custom_paint/rosen_render_custom_paint.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t MAX_MENU_ITEMS_NUM = 3;
constexpr int32_t MENU_OFFSET_RATIO = 9;
}

void TitleBarLayoutAlgorithm::MeasureBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto backButtonNode = titleBarNode->GetBackButton();
    CHECK_NULL_VOID(backButtonNode);
    auto index = titleBarNode->GetChildIndexById(backButtonNode->GetId());
    auto backButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(backButtonWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();

    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        constraint.parentIdealSize = OptionalSizeF(static_cast<float>(BACK_BUTTON_SIZE.ConvertToPx()),
            static_cast<float>(BACK_BUTTON_SIZE.ConvertToPx()));
        backButtonWrapper->Measure(constraint);
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        constraint.parentIdealSize = OptionalSizeF(0.0f, 0.0f);
        backButtonWrapper->Measure(constraint);
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        constraint.parentIdealSize = OptionalSizeF(0.0f, 0.0f);
        backButtonWrapper->Measure(constraint);
        return;
    }

    constraint.parentIdealSize = OptionalSizeF(
        static_cast<float>(BACK_BUTTON_SIZE.ConvertToPx()), static_cast<float>(BACK_BUTTON_SIZE.ConvertToPx()));
    backButtonWrapper->Measure(constraint);
}

float TitleBarLayoutAlgorithm::GetTitleWidth(const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize)
{
    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {

        // nav destination custom title
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(titleBarNode->GetParent());
        CHECK_NULL_RETURN(navDestination, 0.0f);
        auto isCustom = navDestination->GetPrevTitleIsCustomValue(false);
        float occupiedWidth = 0.0f;
        // left padding
        if (GetNavigationBackButtonState(titleBarNode)) {
            occupiedWidth += isCustom ? (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + BUTTON_PADDING).ConvertToPx() :
                (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + NAV_HORIZONTAL_MARGIN_L).ConvertToPx();
        } else {
            occupiedWidth += isCustom ? 0.0f : maxPaddingStart_.ConvertToPx();
        }
        // right padding
        occupiedWidth += isCustom ? 0.0f : maxPaddingEnd_.ConvertToPx();
        return titleBarSize.Width() - occupiedWidth;
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarNode->GetParent());
    CHECK_NULL_RETURN(navBarNode, 0.0f);
    float occupiedWidth = 0.0f;
    auto isCustom = navBarNode->GetPrevTitleIsCustomValue(false);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        occupiedWidth = isCustom ? 0.0f : (maxPaddingStart_ + maxPaddingEnd_).ConvertToPx();
        return titleBarSize.Width() - occupiedWidth;
    }
    // mini mode
    if (titleBarLayoutProperty->GetHideBackButtonValue(false)) {
        occupiedWidth += isCustom ? 0 : maxPaddingStart_.ConvertToPx();
    } else {
        occupiedWidth += (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE).ConvertToPx();
        // custom right padding is the back button hot zone
        occupiedWidth += isCustom ? BUTTON_PADDING.ConvertToPx() : (NAV_HORIZONTAL_MARGIN_L).ConvertToPx();
    }
    // compute right padding
    if (NearZero(menuWidth_)) {
        occupiedWidth += isCustom ? 0.0f : maxPaddingEnd_.ConvertToPx();
    } else {
        occupiedWidth += menuWidth_;
        // title is custom, the title right margin is not needed
        occupiedWidth += isCustom ? 0.0f : (NAV_HORIZONTAL_MARGIN_L).ConvertToPx();
        auto isCustomMenu = navBarNode->GetPrevMenuIsCustomValue(false);
        occupiedWidth += isCustomMenu ? 0.0f : (defaultPaddingStart_).ConvertToPx();
    }
    return titleBarSize.Width() - occupiedWidth;
}

void TitleBarLayoutAlgorithm::MeasureSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize, float maxWidth)
{
    auto subtitleNode = titleBarNode->GetSubtitle();
    CHECK_NULL_VOID_NOLOG(subtitleNode);
    auto index = titleBarNode->GetChildIndexById(subtitleNode->GetId());
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(subtitleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    constraint.maxSize.SetHeight(titleBarSize.Height());
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
            auto navDestinationProperty = navDestination->GetLayoutProperty<NavDestinationLayoutProperty>();
            auto titleHeight = navDestinationProperty->GetTitleBarHeightValue(SINGLE_LINE_TITLEBAR_HEIGHT);
            constraint.parentIdealSize.SetHeight(titleHeight.ConvertToPx());
            constraint.maxSize.SetHeight(titleHeight.ConvertToPx());
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
        constraint.parentIdealSize.SetHeight(titleBarLayoutProperty->GetTitleHeightValue().ConvertToPx());
        constraint.maxSize.SetHeight(titleBarLayoutProperty->GetTitleHeightValue().ConvertToPx());
        titleWrapper->Measure(constraint);
        return;
    }
    // subTitle
    auto titleMode = titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    auto subTitle = titleBarNode->GetSubtitle();
    if (subTitle) {
        // common title
        auto index = titleBarNode->GetChildIndexById(subTitle->GetId());
        auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(subtitleWrapper);
        auto geometryNode = subtitleWrapper->GetGeometryNode();
        // mini mode double title height is 56vp, free/full mode is 82vp
        auto maxTitleHeight = titleMode == NavigationTitleMode::MINI ? SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx() :
            DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx();
        constraint.maxSize.SetWidth(maxWidth);
        constraint.maxSize.SetHeight(maxTitleHeight - geometryNode->GetFrameSize().Height());
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
        // if has menu, max height is single line height
        auto maxHeight = NearZero(menuWidth_) ? titleBarSize.Height() : SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx();
        constraint.parentIdealSize.SetHeight(maxHeight);
        constraint.maxSize.SetHeight(maxHeight);
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
    CHECK_NULL_VOID_NOLOG(menuNode);
    auto index = titleBarNode->GetChildIndexById(menuNode->GetId());
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(menuWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarNode->GetParent());
    CHECK_NULL_VOID(navBarNode);
    auto isCustomMenu = navBarNode->GetPrevMenuIsCustomValue(false);
    if (isCustomMenu) {
        // custom title can't be higher than 56vp
        constraint.parentIdealSize.SetHeight(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
        if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI &&
            !titleBarLayoutProperty->HasTitleHeight()) {
                auto maxWidth = static_cast<float>(MENU_ITEM_SIZE.ConvertToPx()) * MAX_MENU_ITEMS_NUM +
                    defaultPaddingStart_.ConvertToPx();
                constraint.parentIdealSize.SetWidth(maxWidth);
            }
        menuWrapper->Measure(constraint);
        menuWidth_ = menuWrapper->GetGeometryNode()->GetFrameSize().Width();
        return;
    }
    auto menuItemNum = static_cast<int32_t>(menuNode->GetChildren().size());
    if (menuItemNum >= MAX_MENU_ITEMS_NUM) {
        menuWidth_ = static_cast<float>(MENU_ITEM_SIZE.ConvertToPx()) * MAX_MENU_ITEMS_NUM;
    } else {
        menuWidth_ = static_cast<float>(MENU_ITEM_SIZE.ConvertToPx()) * menuItemNum;
    }
    constraint.selfIdealSize = OptionalSizeF(menuWidth_, static_cast<float>(menuHeight_.ConvertToPx()));
    menuWrapper->Measure(constraint);
}

void TitleBarLayoutAlgorithm::LayoutBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto backButtonNode = titleBarNode->GetBackButton();
    CHECK_NULL_VOID(backButtonNode);
    auto index = titleBarNode->GetChildIndexById(backButtonNode->GetId());
    auto backButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(backButtonWrapper);
    auto geometryNode = backButtonWrapper->GetGeometryNode();

    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        if (!titleBarNode->GetBackButton()) {
            return;
        }
        auto titleHeight = titleBarLayoutProperty->GetTitleHeightValue(SINGLE_LINE_TITLEBAR_HEIGHT);
        auto offsetY = (titleHeight - BACK_BUTTON_SIZE) / 2;

        OffsetF backButtonOffset = OffsetF(static_cast<float>((maxPaddingStart_ - BUTTON_PADDING).ConvertToPx()),
            static_cast<float>(offsetY.ConvertToPx()));
        geometryNode->SetMarginFrameOffset(backButtonOffset);
        backButtonWrapper->Layout();
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
    auto titleHeight = titleBarLayoutProperty->GetTitleHeightValue(SINGLE_LINE_TITLEBAR_HEIGHT);
    auto offsetY = (titleHeight - BACK_BUTTON_SIZE) / 2;
    auto offsetX = (maxPaddingStart_ - (BACK_BUTTON_SIZE - BACK_BUTTON_ICON_SIZE) / 2).ConvertToPx();
    OffsetF backButtonOffset = OffsetF(offsetX, static_cast<float>(offsetY.ConvertToPx()));
    geometryNode->SetMarginFrameOffset(backButtonOffset);
    backButtonWrapper->Layout();
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

    auto titleHeight = geometryNode->GetFrameSize().Height();
    float offsetY = 0.0f;
    if (!NearZero(subtitleHeight)) {
        offsetY = (static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - titleHeight - subtitleHeight) / 2;
    } else {
        offsetY = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - titleHeight) / 2;
    }
    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(titleBarNode->GetParent());
        CHECK_NULL_VOID(navDestination);
        auto isCustom = navDestination->GetPrevTitleIsCustomValue(false);
        if (GetNavigationBackButtonState(titleBarNode)) {
            auto offsetX = isCustom ? (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + BUTTON_PADDING).ConvertToPx() :
                (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + NAV_HORIZONTAL_MARGIN_L).ConvertToPx();
            offsetY = isCustom ? 0.0f : offsetY;
            geometryNode->SetMarginFrameOffset(OffsetF { offsetX, offsetY });
            titleWrapper->Layout();
            return;
        }
        auto offsetX = isCustom ? 0.0f : maxPaddingStart_.ConvertToPx();
        offsetY = isCustom ? 0.0f : offsetY;
        OffsetF offset = OffsetF(offsetX, offsetY);
        geometryNode->SetMarginFrameOffset(offset);
        titleWrapper->Layout();
        return;
    }

    // navBar title bar
    auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarNode->GetParent());
    CHECK_NULL_VOID(navBarNode);
    auto isCustom = navBarNode->GetPrevTitleIsCustomValue(false);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        // NavigationCustomTitle and Custom builder layout margin is (0, 0);
        offsetY = isCustom ? 0 : offsetY;
        if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
            auto offsetX = isCustom ? 0.0f : (maxPaddingStart_).ConvertToPx();
            OffsetF titleOffset = OffsetF(offsetX, offsetY);
            geometryNode->SetMarginFrameOffset(titleOffset);
            titleWrapper->Layout();
            return;
        }

        auto offsetX = isCustom ? (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + BUTTON_PADDING).ConvertToPx() :
            (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + NAV_HORIZONTAL_MARGIN_L).ConvertToPx();
        OffsetF offset = OffsetF(offsetX, offsetY);
        geometryNode->SetMarginFrameOffset(offset);
        titleWrapper->Layout();
        return;
    }
    // full mode
    if (!isCustom) {
        auto dividerOffset = 2;
        if (!NearZero(subtitleHeight)) {
            offsetY = (static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - titleHeight -
                subtitleHeight) / dividerOffset;
        } else {
            offsetY = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - titleHeight) / dividerOffset;
        }
    }

    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        // full mode
        if (isCustom) {
            // custom title margin is (0.0f, menuHeight_)
            auto customOffsetY = NearZero(menuWidth_) ? 0.0f : menuHeight_.ConvertToPx();
            geometryNode->SetMarginFrameOffset(OffsetF { 0.0f, customOffsetY});
            titleWrapper->Layout();
        } else {
            // fixed white space menuHeight
            OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()),
                static_cast<float>(menuHeight_.ConvertToPx()) + offsetY);
            geometryNode->SetMarginFrameOffset(titleOffset);
            titleWrapper->Layout();
        }
        return;
    }
    if (isInitialTitle_) {
        // free mode
        if (isCustom) {
            // customBuilder and NavigationCustomTitle offset is (0.0f, menuHeight_)
            auto customOffsetY = NearZero(menuWidth_) ? 0.0f : menuHeight_.ConvertToPx();
            geometryNode->SetMarginFrameOffset(OffsetF { 0.0f, customOffsetY});
            titleWrapper->Layout();
            return;
        }
        auto title = AceType::DynamicCast<FrameNode>(titleNode);
        CHECK_NULL_VOID(title);

        auto textLayoutProperty = title->GetLayoutProperty<TextLayoutProperty>();
        if (!textLayoutProperty) {
            // current title mode is Navigation common title
            OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()),
                static_cast<float>(menuHeight_.ConvertToPx())+ offsetY);
            geometryNode->SetMarginFrameOffset(titleOffset);
            titleWrapper->Layout();
            return;
        }
        MeasureContext context;
        context.textContent = textLayoutProperty->GetContentValue();
        context.fontSize = titleFontSize_;
#ifdef ENABLE_ROSEN_BACKEND
        minTitleHeight_ = static_cast<float>(RosenRenderCustomPaint::MeasureTextSizeInner(context).Height());
#else
        minTitleHeight_ = 0.0;
#endif
        initialTitleOffsetY_ = static_cast<float>(menuHeight_.ConvertToPx()) + offsetY;
        isInitialTitle_ = false;
        auto titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), initialTitleOffsetY_);
        geometryNode->SetMarginFrameOffset(titleOffset);
        titleWrapper->Layout();
        return;
    }

    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titlePattern);
    if (NearZero(titlePattern->GetTempTitleOffsetY())) {
        initialTitleOffsetY_ = static_cast<float>(menuHeight_.ConvertToPx()) + offsetY;
        auto titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), initialTitleOffsetY_);
        geometryNode->SetMarginFrameOffset(titleOffset);
        titleWrapper->Layout();
        return;
    }
    auto overDragOffset = titlePattern->GetOverDragOffset();
    auto titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()),
        titlePattern->GetTempTitleOffsetY() + overDragOffset / 6.0f);
    geometryNode->SetMarginFrameOffset(titleOffset);
    titleWrapper->Layout();
}

void TitleBarLayoutAlgorithm::LayoutSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, float titleHeight)
{
    auto subtitleNode = titleBarNode->GetSubtitle();
    CHECK_NULL_VOID_NOLOG(subtitleNode);
    auto index = titleBarNode->GetChildIndexById(subtitleNode->GetId());
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(subtitleWrapper);
    auto geometryNode = subtitleWrapper->GetGeometryNode();

    auto subtitleHeight = geometryNode->GetFrameSize().Height();
    float offsetY = 0.0f;
    if (!NearZero(titleHeight)) {
        offsetY = (static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - titleHeight - subtitleHeight) / 2 +
                  titleHeight;
    } else {
        offsetY = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - subtitleHeight) / 2;
    }
    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        // subtitle doesn't support custom title
        if (GetNavigationBackButtonState(titleBarNode)) {
            geometryNode->SetMarginFrameOffset(OffsetF { (maxPaddingStart_ + BACK_BUTTON_ICON_SIZE
                + NAV_HORIZONTAL_MARGIN_L).ConvertToPx(), offsetY });
            subtitleWrapper->Layout();
            return;
        }

        OffsetF offset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), offsetY);
        geometryNode->SetMarginFrameOffset(offset);
        subtitleWrapper->Layout();
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) {
            if (isInitialSubtitle_) {
                initialSubtitleOffsetY_ = static_cast<float>(menuHeight_.ConvertToPx()) + offsetY;
                isInitialSubtitle_ = false;
                OffsetF titleOffset =
                    OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), initialSubtitleOffsetY_);
                geometryNode->SetMarginFrameOffset(titleOffset);
                subtitleWrapper->Layout();
                return;
            }

            auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
            CHECK_NULL_VOID(titlePattern);
            if (NearZero(titlePattern->GetTempTitleOffsetY())) {
                OffsetF titleOffset =
                    OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), initialSubtitleOffsetY_);
                geometryNode->SetMarginFrameOffset(titleOffset);
                subtitleWrapper->Layout();
                return;
            }
            auto overDragOffset = titlePattern->GetOverDragOffset();
            OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()),
                titlePattern->GetTempSubTitleOffsetY() + overDragOffset / 6.0f);
            geometryNode->SetMarginFrameOffset(titleOffset);
            subtitleWrapper->Layout();
            return;
        }
        // full mode
        OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()),
            static_cast<float>(menuHeight_.ConvertToPx()) + offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        subtitleWrapper->Layout();
        return;
    }
    // mini mode + hideBackButton true
    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        subtitleWrapper->Layout();
        return;
    }
    // mini mode + back button
    auto occupiedWidth = maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + NAV_HORIZONTAL_MARGIN_L;
    OffsetF offset = OffsetF(static_cast<float>(occupiedWidth.ConvertToPx()), offsetY);
    geometryNode->SetMarginFrameOffset(offset);
    subtitleWrapper->Layout();
}

void TitleBarLayoutAlgorithm::LayoutMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, float subtitleHeight)
{
    auto menuNode = titleBarNode->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto index = titleBarNode->GetChildIndexById(menuNode->GetId());
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(menuWrapper);
    auto geometryNode = menuWrapper->GetGeometryNode();
    auto menuWidth = geometryNode->GetMarginFrameSize().Width();
    auto maxWidth = geometryNode->GetParentLayoutConstraint()->maxSize.Width();
    auto navBarNode = AceType::DynamicCast<NavBarNode>(titleBarNode->GetParent());
    auto isCustomMenu = navBarNode->GetPrevMenuIsCustomValue(false);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) {
        auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
        auto overDragOffset = titlePattern->GetOverDragOffset();
        auto menuOffsetY = (SINGLE_LINE_TITLEBAR_HEIGHT - menuHeight_) / 2;
        // custom menu width has no right padding
        auto offsetX = isCustomMenu ? maxWidth - menuWidth
                                    : (maxWidth - menuWidth - static_cast<float>(maxPaddingEnd_.ConvertToPx()) +
                                          BUTTON_PADDING.ConvertToPx());
        OffsetF menuOffset(offsetX, static_cast<float>(menuOffsetY.ConvertToPx()) + overDragOffset / MENU_OFFSET_RATIO);
        geometryNode->SetMarginFrameOffset(menuOffset);
        menuWrapper->Layout();
        return;
    }

    auto menuOffsetY =  (SINGLE_LINE_TITLEBAR_HEIGHT - menuHeight_) / 2;
    auto menuOffsetX = maxWidth - menuWidth;
    // custom menu doesn't have right padding. if menu isn't custom, menu items has right padding
    menuOffsetX =
        isCustomMenu ? menuOffsetX : (menuOffsetX - maxPaddingEnd_.ConvertToPx() + BUTTON_PADDING.ConvertToPx());
    OffsetF menuOffset(menuOffsetX, static_cast<float>(menuOffsetY.ConvertToPx()));
    geometryNode->SetMarginFrameOffset(menuOffset);
    menuWrapper->Layout();
}

// set variables from theme
void TitleBarLayoutAlgorithm::InitializeTheme()
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    maxPaddingStart_ = theme->GetMaxPaddingStart();
    maxPaddingEnd_ = theme->GetMaxPaddingEnd();
    menuHeight_ = theme->GetHeight();
    defaultPaddingStart_ = theme->GetDefaultPaddingStart();
    iconSize_ = theme->GetMenuIconSize();
    titleFontSize_ = theme->GetTitleFontSize();
}

void TitleBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(titleBarNode);
    auto layoutProperty = AceType::DynamicCast<TitleBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    InitializeTheme();

    MeasureBackButton(layoutWrapper, titleBarNode, layoutProperty);
    MeasureMenu(layoutWrapper, titleBarNode, layoutProperty);
    auto titleMaxWidth = GetTitleWidth(titleBarNode, layoutProperty, size);
    MeasureSubtitle(layoutWrapper, titleBarNode, layoutProperty, size, titleMaxWidth);
    MeasureTitle(layoutWrapper, titleBarNode, layoutProperty, size, titleMaxWidth);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void TitleBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(titleBarNode);
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

bool TitleBarLayoutAlgorithm::GetNavigationBackButtonState(const RefPtr<TitleBarNode>& titleBarNode)
{
    auto backButton = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_RETURN_NOLOG(backButton, false);
    auto layoutProperty = backButton->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE;
}
} // namespace OHOS::Ace::NG
