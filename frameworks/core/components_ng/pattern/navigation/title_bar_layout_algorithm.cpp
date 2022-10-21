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
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
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
        constraint.selfIdealSize = OptionalSizeF(static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()),
            static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()));
        backButtonWrapper->Measure(constraint);
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        backButtonWrapper->Measure(constraint);
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        backButtonWrapper->Measure(constraint);
        return;
    }

    constraint.selfIdealSize = OptionalSizeF(static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()),
        static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()));
    backButtonWrapper->Measure(constraint);
}

void TitleBarLayoutAlgorithm::MeasureSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize)
{
    auto subtitleNode = titleBarNode->GetSubtitle();
    CHECK_NULL_VOID(subtitleNode);
    auto index = titleBarNode->GetChildIndexById(subtitleNode->GetId());
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(subtitleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();

    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        if (titleBarNode->GetBackButton()) {
            auto occupiedWidth = maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + HORIZONTAL_MARGIN_M + maxPaddingEnd_;
            constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
            subtitleWrapper->Measure(constraint);
            return;
        }

        auto occupiedWidth = maxPaddingStart_ + maxPaddingEnd_;
        constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
        subtitleWrapper->Measure(constraint);
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        auto occupiedWidth = maxPaddingStart_ + maxPaddingEnd_;
        constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
        subtitleWrapper->Measure(constraint);
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        auto occupiedWidth = maxPaddingStart_ + maxPaddingEnd_;
        constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
        subtitleWrapper->Measure(constraint);
        return;
    }

    auto occupiedWidth = maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + HORIZONTAL_MARGIN_M + maxPaddingEnd_;
    constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
    subtitleWrapper->Measure(constraint);
}

void TitleBarLayoutAlgorithm::MeasureTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize)
{
    auto titleNode = titleBarNode->GetTitle();
    CHECK_NULL_VOID(titleNode);
    auto index = titleBarNode->GetChildIndexById(titleNode->GetId());
    auto titleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();

    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        if (titleBarNode->GetBackButton()) {
            auto occupiedWidth = maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + HORIZONTAL_MARGIN_M + maxPaddingEnd_;
            constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
            titleWrapper->Measure(constraint);
            return;
        }

        auto occupiedWidth = maxPaddingStart_ + maxPaddingEnd_;
        constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
        titleWrapper->Measure(constraint);
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        auto occupiedWidth = maxPaddingStart_ + maxPaddingEnd_;
        constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
        titleWrapper->Measure(constraint);
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        auto occupiedWidth = maxPaddingStart_ + maxPaddingEnd_;
        constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
        titleWrapper->Measure(constraint);
        return;
    }

    auto occupiedWidth = maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + HORIZONTAL_MARGIN_M + maxPaddingEnd_;
    constraint.maxSize.SetWidth(titleBarSize.Width() - static_cast<float>(occupiedWidth.ConvertToPx()));
    titleWrapper->Measure(constraint);
}

void TitleBarLayoutAlgorithm::MeasureMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize)
{
    auto menuNode = titleBarNode->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto index = titleBarNode->GetChildIndexById(menuNode->GetId());
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(menuWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        auto size = SizeF(titleBarSize.Width(), static_cast<float>(menuHeight_.ConvertToPx()));
        constraint.maxSize.SetSizeT(size);
        menuWrapper->Measure(constraint);
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        auto size = SizeF(titleBarSize.Width(), static_cast<float>(menuHeight_.ConvertToPx()));
        constraint.maxSize.SetSizeT(size);
        menuWrapper->Measure(constraint);
        return;
    }

    auto size = SizeF(titleBarSize.Width() - static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()),
        static_cast<float>(menuHeight_.ConvertToPx()));
    constraint.maxSize.SetSizeT(size);
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

        auto offsetY = (menuHeight_ - BACK_BUTTON_ICON_SIZE) / 2;
        OffsetF backButtonOffset =
            OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), static_cast<float>(offsetY.ConvertToPx()));
        geometryNode->SetMarginFrameOffset(backButtonOffset);
        backButtonWrapper->Layout();
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        return;
    }
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
    if (subtitleHeight != 0.0f) {
        offsetY = (static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - titleHeight - subtitleHeight) / 2;
    } else {
        offsetY = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - titleHeight) / 2;
    }

    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        if (titleBarNode->GetBackButton()) {
            OffsetF offset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()) +
                                         static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()) +
                                         static_cast<float>(HORIZONTAL_MARGIN_M.ConvertToPx()),
                offsetY);
            geometryNode->SetMarginFrameOffset(offset);
            titleWrapper->Layout();
            return;
        }

        OffsetF offset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), offsetY);
        geometryNode->SetMarginFrameOffset(offset);
        titleWrapper->Layout();
        return;
    }

    // navBar title bar
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::MINI) {
        OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()),
            static_cast<float>(menuHeight_.ConvertToPx()) + offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        titleWrapper->Layout();
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        titleWrapper->Layout();
        return;
    }

    auto occupiedWidth = maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + HORIZONTAL_MARGIN_M;
    OffsetF offset = OffsetF(static_cast<float>(occupiedWidth.ConvertToPx()), offsetY);
    geometryNode->SetMarginFrameOffset(offset);
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

    auto subtitleHeight = geometryNode->GetFrameSize().Height();
    float offsetY = 0.0f;
    if (titleHeight != 0.0f) {
        offsetY = (static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - titleHeight - subtitleHeight) / 2 +
                  titleHeight;
    } else {
        offsetY = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - subtitleHeight) / 2;
    }

    // navDestination title bar
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) ==
        TitleBarParentType::NAV_DESTINATION) {
        if (titleBarNode->GetBackButton()) {
            OffsetF offset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()) +
                                         static_cast<float>(BACK_BUTTON_ICON_SIZE.ConvertToPx()) +
                                         static_cast<float>(HORIZONTAL_MARGIN_M.ConvertToPx()),
                offsetY);
            geometryNode->SetMarginFrameOffset(offset);
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
        OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()),
            static_cast<float>(menuHeight_.ConvertToPx()) + offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        subtitleWrapper->Layout();
        return;
    }

    if (titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
        OffsetF titleOffset = OffsetF(static_cast<float>(maxPaddingStart_.ConvertToPx()), offsetY);
        geometryNode->SetMarginFrameOffset(titleOffset);
        subtitleWrapper->Layout();
        return;
    }

    auto occupiedWidth = maxPaddingStart_ + BACK_BUTTON_ICON_SIZE + HORIZONTAL_MARGIN_M;
    OffsetF offset = OffsetF(static_cast<float>(occupiedWidth.ConvertToPx()), offsetY);
    geometryNode->SetMarginFrameOffset(offset);
    subtitleWrapper->Layout();
}

void TitleBarLayoutAlgorithm::LayoutMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode)
{
    auto menuNode = titleBarNode->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto index = titleBarNode->GetChildIndexById(menuNode->GetId());
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(menuWrapper);
    auto geometryNode = menuWrapper->GetGeometryNode();
    auto menuWidth = geometryNode->GetMarginFrameSize().Width();
    auto maxWidth = geometryNode->GetParentLayoutConstraint()->maxSize.Width();
    auto parentWidth = geometryNode->GetParentLayoutConstraint()->parentIdealSize.Width().value_or(maxWidth);
    OffsetF menuOffset(parentWidth - menuWidth - static_cast<float>(maxPaddingEnd_.ConvertToPx()), 0.0f);
    menuWrapper->GetGeometryNode()->SetMarginFrameOffset(menuOffset);
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
    
    InitializeTheme();

    MinusPaddingToSize(padding, size);
    MeasureBackButton(layoutWrapper, titleBarNode, layoutProperty);
    MeasureMenu(layoutWrapper, titleBarNode, layoutProperty, size);
    MeasureTitle(layoutWrapper, titleBarNode, layoutProperty, size);
    MeasureSubtitle(layoutWrapper, titleBarNode, layoutProperty, size);
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

    LayoutMenu(layoutWrapper, titleBarNode);
}

} // namespace OHOS::Ace::NG