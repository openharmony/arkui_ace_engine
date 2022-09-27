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
    if (!titleBarNode->HasBackButtonIndex()) {
        return;
    }
    auto backButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(titleBarNode->GetBackButtonIndexValue());
    CHECK_NULL_VOID(backButtonWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    if (!titleBarLayoutProperty->HasTitleMode() ||
        titleBarLayoutProperty->GetTitleModeValue() != NavigationTitleMode::MINI ||
        (titleBarLayoutProperty->HasHideBackButton() && titleBarLayoutProperty->GetHideBackButtonValue())) {
        constraint.selfIdealSize = OptionalSizeF(0.0f, 0.0f);
        backButtonWrapper->Measure(constraint);
        return;
    }
    constraint.selfIdealSize = OptionalSizeF(BACK_BUTTON_WIDTH, TITLEBAR_HEIGHT);
    backButtonWrapper->Measure(constraint);
}

void MeasureSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    if (!titleBarNode->HasSubtitleIndex()) {
        return;
    }
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(titleBarNode->GetSubtitleIndexValue());
    CHECK_NULL_VOID(subtitleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    constraint.maxSize.SetHeight(SUBTITLE_HEIGHT);
    constraint.minSize.SetHeight(SUBTITLE_HEIGHT);
    subtitleWrapper->Measure(constraint);
}

void MeasureTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    if (!titleBarNode->HasTitleIndex()) {
        return;
    }
    auto titleWrapper = layoutWrapper->GetOrCreateChildByIndex(titleBarNode->GetTitleIndexValue());
    CHECK_NULL_VOID(titleWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    constraint.maxSize.SetHeight(TITLE_HEIGHT);
    titleWrapper->Measure(constraint);
}

void MeasureMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    if (!titleBarNode->HasMenuIndex()) {
        return;
    }
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(titleBarNode->GetMenuIndexValue());
    CHECK_NULL_VOID(menuWrapper);
    auto constraint = titleBarLayoutProperty->CreateChildConstraint();
    auto menuMaxWidth = constraint.maxSize.Width();
    if (titleBarLayoutProperty->GetTitleModeValue() == NavigationTitleMode::MINI) {
        menuMaxWidth -= TITLE_WIDTH + BACK_BUTTON_WIDTH;
    }
    SizeF menuSize(menuMaxWidth, BAR_ITEM_HEIGHT);
    constraint.maxSize.SetSizeT(menuSize);
    constraint.parentIdealSize = OptionalSizeF(constraint.maxSize.Width(), constraint.maxSize.Height());
    menuWrapper->Measure(constraint);
}

void LayoutBackButton(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (!titleBarNode->HasBackButtonIndex()) {
        return;
    }
    auto backButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(titleBarNode->GetBackButtonIndexValue());
    CHECK_NULL_VOID(backButtonWrapper);
    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    backButtonWrapper->Layout(parentOffset);
}

void LayoutSubtitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    if (!titleBarNode->HasSubtitleIndex()) {
        return;
    }
    auto subtitleWrapper = layoutWrapper->GetOrCreateChildByIndex(titleBarNode->GetSubtitleIndexValue());
    CHECK_NULL_VOID(subtitleWrapper);
    OffsetF subtitleOffset(0.0f, TITLEBAR_HEIGHT - SUBTITLE_HEIGHT);
    if (titleBarLayoutProperty->GetTitleModeValue() == NavigationTitleMode::MINI) {
        subtitleOffset.SetX(BACK_BUTTON_WIDTH);
    }
    subtitleWrapper->GetGeometryNode()->SetFrameOffset(subtitleOffset);
    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    subtitleWrapper->Layout(parentOffset);
}

void LayoutTitle(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    if (!titleBarNode->HasTitleIndex()) {
        return;
    }
    auto titleWrapper = layoutWrapper->GetOrCreateChildByIndex(titleBarNode->GetTitleIndexValue());
    CHECK_NULL_VOID(titleWrapper);
    OffsetF titleOffset(0.0f, 0.0f);
    if (titleBarLayoutProperty->GetTitleModeValue() == NavigationTitleMode::MINI) {
        titleOffset.SetX(BACK_BUTTON_WIDTH);
    } else {
        titleOffset.SetY(titleOffset.GetY() + BAR_ITEM_HEIGHT);
    }
    titleWrapper->GetGeometryNode()->SetFrameOffset(titleOffset);
    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    titleWrapper->Layout(parentOffset);
}

void LayoutMenu(LayoutWrapper* layoutWrapper, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (!titleBarNode->HasMenuIndex()) {
        return;
    }
    auto menuWrapper = layoutWrapper->GetOrCreateChildByIndex(titleBarNode->GetMenuIndexValue());
    CHECK_NULL_VOID(menuWrapper);
    auto menuWidth = menuWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto geometryNode = menuWrapper->GetGeometryNode();
    auto maxWidth = geometryNode->GetParentLayoutConstraint()->maxSize.Width();
    auto parentWidth = geometryNode->GetParentLayoutConstraint()->parentIdealSize.Width().value_or(maxWidth);
    OffsetF menuOffset(parentWidth - menuWidth, 0.0f);
    menuWrapper->GetGeometryNode()->SetFrameOffset(menuOffset);
    menuWrapper->Layout(layoutWrapper->GetGeometryNode()->GetParentGlobalOffset());
}
} // namespace

void TitleBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(titleBarNode);
    auto layoutProperty = AceType::DynamicCast<TitleBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasHideTitleBar() && layoutProperty->GetHideTitleBarValue()) {
        return;
    }
    MeasureBackButton(layoutWrapper, titleBarNode, layoutProperty);
    MeasureTitle(layoutWrapper, titleBarNode, layoutProperty);
    MeasureSubtitle(layoutWrapper, titleBarNode, layoutProperty);
    MeasureMenu(layoutWrapper, titleBarNode, layoutProperty);
    const auto& constraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto size = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT_MAIN_AXIS, true);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void TitleBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(titleBarNode);
    auto layoutProperty = AceType::DynamicCast<TitleBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    if (layoutProperty->HasHideTitleBar() && layoutProperty->GetHideTitleBarValue()) {
        return;
    }
    if (layoutProperty->GetTitleModeValue() == NavigationTitleMode::MINI) {
        LayoutBackButton(layoutWrapper, titleBarNode);
    }
    LayoutTitle(layoutWrapper, titleBarNode, layoutProperty);
    LayoutSubtitle(layoutWrapper, titleBarNode, layoutProperty);
    LayoutMenu(layoutWrapper, titleBarNode);
}

} // namespace OHOS::Ace::NG