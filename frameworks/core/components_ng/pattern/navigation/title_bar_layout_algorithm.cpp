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
namespace {
void MeasureBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto backButtonNode = titleBarNode->GetBackButton();
    CHECK_NULL_VOID(backButtonNode);
    auto index = titleBarNode->GetChildIndexById(backButtonNode->GetId());
    auto backButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(backButtonWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (!titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
            constraint.selfIdealSize = OptionalSizeF(static_cast<float>(BACK_BUTTON_WIDTH.ConvertToPx()),
                static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx()));
            backButtonWrapper->Measure(constraint);
            return;
        }
    }
    constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
    backButtonWrapper->Measure(constraint);
}

void MeasureSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize)
{
    auto subtitleNode = titleBarNode->GetSubtitle();
    CHECK_NULL_VOID(subtitleNode);
    auto index = titleBarNode->GetChildIndexById(subtitleNode->GetId());
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(subtitleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();

    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (!titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
            auto size = SizeF(
                titleBarSize.Width() - static_cast<float>(BACK_BUTTON_WIDTH.ConvertToPx()),
                static_cast<float>(SUBTITLE_HEIGHT.ConvertToPx()));
            constraint.maxSize.SetSizeT(size);
            subtitleWrapper->Measure(constraint);
            return;
        }
    }
    auto size = SizeF(titleBarSize.Width(), static_cast<float>(SUBTITLE_HEIGHT.ConvertToPx()));
    constraint.maxSize.SetSizeT(size);
    subtitleWrapper->Measure(constraint);
}

void MeasureTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize)
{
    auto titleNode = titleBarNode->GetTitle();
    CHECK_NULL_VOID(titleNode);
    auto index = titleBarNode->GetChildIndexById(titleNode->GetId());
    auto titleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();

    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (!titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
            auto size = SizeF(
                titleBarSize.Width() - static_cast<float>(BACK_BUTTON_WIDTH.ConvertToPx()),
                static_cast<float>(TITLE_HEIGHT.ConvertToPx()));
            constraint.maxSize.SetSizeT(size);
            titleWrapper->Measure(constraint);
            return;
        }
    }
    auto size = SizeF(titleBarSize.Width(), static_cast<float>(TITLE_HEIGHT.ConvertToPx()));
    constraint.maxSize.SetSizeT(size);
    titleWrapper->Measure(constraint);
}

void MeasureMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty, const SizeF& titleBarSize)
{
    auto menuNode = titleBarNode->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto index = titleBarNode->GetChildIndexById(menuNode->GetId());
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(menuWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();

    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (!titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
            auto size = SizeF(
                titleBarSize.Width() - static_cast<float>(BACK_BUTTON_WIDTH.ConvertToPx()),
                static_cast<float>(SUBTITLE_HEIGHT.ConvertToPx()));
            constraint.maxSize.SetSizeT(size);
            menuWrapper->Measure(constraint);
            return;
        }
    }
    constraint.maxSize.SetSizeT(titleBarSize);
    menuWrapper->Measure(constraint);
}

void LayoutBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode)
{
    auto backButtonNode = titleBarNode->GetBackButton();
    CHECK_NULL_VOID(backButtonNode);
    auto index = titleBarNode->GetChildIndexById(backButtonNode->GetId());
    auto backButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(backButtonWrapper);
    backButtonWrapper->Layout();
}

void LayoutSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto subtitleNode = titleBarNode->GetSubtitle();
    CHECK_NULL_VOID(subtitleNode);
    auto index = titleBarNode->GetChildIndexById(subtitleNode->GetId());
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(subtitleWrapper);
    auto geometryNode = subtitleWrapper->GetGeometryNode();

    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (!titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
            OffsetF subtitleOffset = OffsetF(static_cast<float>(BACK_BUTTON_WIDTH.ConvertToPx()),
                static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx()));
            subtitleWrapper->GetGeometryNode()->SetMarginFrameOffset(subtitleOffset);
            subtitleWrapper->Layout();
            return;
        }
    }
    OffsetF subtitleOffset = OffsetF(geometryNode->GetFrameOffset().GetX(),
        static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx()));
    subtitleWrapper->GetGeometryNode()->SetMarginFrameOffset(subtitleOffset);
    subtitleWrapper->Layout();
}

void LayoutTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto titleNode = titleBarNode->GetTitle();
    CHECK_NULL_VOID(titleNode);
    auto index = titleBarNode->GetChildIndexById(titleNode->GetId());
    auto titleWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleWrapper);
    auto geometryNode = titleWrapper->GetGeometryNode();

    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        if (!titleBarLayoutProperty->GetHideBackButton().value_or(false)) {
            OffsetF offset = OffsetF(static_cast<float>(BACK_BUTTON_WIDTH.ConvertToPx()), 0.0f);
            titleWrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
        }
    }
    titleWrapper->Layout();
}

void LayoutMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode)
{
    auto menuNode = titleBarNode->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto index = titleBarNode->GetChildIndexById(menuNode->GetId());
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(menuWrapper);
    auto menuWidth = menuWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    auto geometryNode = menuWrapper->GetGeometryNode();
    auto maxWidth = geometryNode->GetParentLayoutConstraint()->maxSize.Width();
    auto parentWidth = geometryNode->GetParentLayoutConstraint()->parentIdealSize.Width().value_or(maxWidth);
    OffsetF menuOffset(parentWidth - menuWidth, 0.0f);
    menuWrapper->GetGeometryNode()->SetMarginFrameOffset(menuOffset);
    menuWrapper->Layout();
}
} // namespace

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
    if (layoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        LayoutBackButton(layoutWrapper, titleBarNode);
    }
    LayoutTitle(layoutWrapper, titleBarNode, layoutProperty);
    LayoutSubtitle(layoutWrapper, titleBarNode, layoutProperty);
    LayoutMenu(layoutWrapper, titleBarNode);
}

} // namespace OHOS::Ace::NG