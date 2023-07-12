/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/navigation/bar_item_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t GRID_COUNTS_4 = 4;
constexpr uint32_t GRID_COUNTS_6 = 6;
constexpr uint32_t GRID_COUNTS_8 = 8;
constexpr uint32_t TOOLBAR_ITEMS_NUM_4 = 4;

float GetToolbarContainerMaxWidth(const float& toolbarWidth, size_t toolbarItemNum)
{
    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::NAVIGATION_TOOLBAR);
    columnInfo->GetParent()->BuildColumnWidth();

    auto currentColumns = columnInfo->GetParent()->GetColumns();
    if (currentColumns == GRID_COUNTS_4) {
        if (toolbarItemNum >= TOOLBAR_ITEMS_NUM_4) {
            return toolbarWidth;
        } else {
            return static_cast<float>(columnInfo->GetWidth(GRID_COUNTS_4));
        }
    } else if (currentColumns == GRID_COUNTS_8) {
        if (toolbarItemNum >= GRID_COUNTS_4) {
            return static_cast<float>(columnInfo->GetWidth(GRID_COUNTS_8));
        } else {
            return static_cast<float>(columnInfo->GetWidth(GRID_COUNTS_6));
        }
    }
    return 0.0f;
}

float CalcToolbarItemWidth(const float& toolbarWidth, size_t toolbarItemNum)
{
    if (toolbarItemNum == 0) {
        return 0.0f;
    }
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto toolbarItemInterval = theme->GetToolbarItemSafeInterval().ConvertToPx();

    float totalItemsInterval = (toolbarItemNum - 1) * (toolbarItemInterval);
    float containerWidth = GetToolbarContainerMaxWidth(toolbarWidth, toolbarItemNum);
    return (containerWidth - totalItemsInterval) / toolbarItemNum;
}

float CalcBarItemMaxWidth(const float& toolbarWidth, size_t toolbarItemNum)
{
    if (toolbarItemNum == 0) {
        return 0.0f;
    }
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto toolbarItemInterval = theme->GetToolbarItemSafeInterval().ConvertToPx();
    auto toolbarItemPadding = theme->GetToolbarItemHorizontalPadding().ConvertToPx();

    return (toolbarWidth - (toolbarItemNum - 1) * toolbarItemInterval - toolbarItemNum * toolbarItemPadding) /
           toolbarItemNum;
}

float CalcToolbarItemMaxWidthIfNeedToExpand(const float& toolbarWidth, size_t toolbarItemNum)
{
    if (toolbarItemNum == 0) {
        return 0.0f;
    }
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto toolbarItemInterval = theme->GetToolbarItemSafeInterval().ConvertToPx();

    return (toolbarWidth - (toolbarItemNum - 1) * toolbarItemInterval) / toolbarItemNum;
}

void SetBarItemMaxWidth(const RefPtr<LayoutWrapper>& toolbarItemWrapper, const float& barItemWidth)
{
    auto barItemWrapper = toolbarItemWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(barItemWrapper);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(barItemWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto barItemLayoutAlgorithm =
        AceType::DynamicCast<BarItemLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(barItemLayoutAlgorithm);
    barItemLayoutAlgorithm->SetBarItemMaxWidth(barItemWidth);
}

float UpdateToolBarItemsContainer(LayoutWrapper* layoutWrapper, size_t toolbarItemNum, const float& toolbarWidth)
{
    auto containerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(containerWrapper, 0.0f);
    float toolbarItemWidth = CalcToolbarItemWidth(toolbarWidth, toolbarItemNum);
    float barItemMaxWidth = CalcBarItemMaxWidth(toolbarWidth, toolbarItemNum);

    for (const auto& toolbarItemWrapper : containerWrapper->GetAllChildrenWithBuild()) {
        auto layoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(toolbarItemWrapper->GetLayoutProperty());
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(toolbarItemWidth), std::nullopt));
        SetBarItemMaxWidth(toolbarItemWrapper, barItemMaxWidth);
    }

    return toolbarItemWidth;
}

bool CheckWhetherBarItemSizeCrossBorder(LayoutWrapper* layoutWrapper, NG::SizeF& toolbarItemSize)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, false);
    float toolbarItemHorizontalPadding = theme->GetToolbarItemHorizontalPadding().ConvertToPx();
    float toolbarItemVerticalPadding = theme->GetToolbarItemVerticalPadding().ConvertToPx();

    auto containerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(containerWrapper, false);
    bool needToUpdateWidth = false;
    bool needToUpdateHeight = false;

    for (const auto& toolbarItemWrapper : containerWrapper->GetAllChildrenWithBuild()) {
        auto layoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(toolbarItemWrapper->GetLayoutProperty());
        auto barItemWrapper = toolbarItemWrapper->GetOrCreateChildByIndex(0);
        CHECK_NULL_RETURN(barItemWrapper, false);

        auto barItemWidth = barItemWrapper->GetGeometryNode()->GetFrameSize().Width();
        if (GreatOrEqual(barItemWidth, (toolbarItemSize.Width() - toolbarItemHorizontalPadding))) {
            toolbarItemSize.SetWidth(barItemWidth + toolbarItemHorizontalPadding);
            needToUpdateWidth = true;
        }

        auto barItemHeight = barItemWrapper->GetGeometryNode()->GetFrameSize().Height();
        float toolbarItemHeight = barItemHeight + toolbarItemVerticalPadding;
        if (GreatOrEqual(toolbarItemHeight, toolbarItemSize.Height())) {
            toolbarItemSize.SetHeight(toolbarItemHeight);
            needToUpdateHeight = true;
        }
    }

    return needToUpdateWidth || needToUpdateHeight;
}

void UpdateToolbarItemSize(LayoutWrapper* layoutWrapper, NG::SizeF& toolbarItemSize)
{
    auto containerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(containerWrapper);
    for (const auto& toolbarItemWrapper : containerWrapper->GetAllChildrenWithBuild()) {
        auto layoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(toolbarItemWrapper->GetLayoutProperty());
        layoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(toolbarItemSize.Width()), CalcLength(toolbarItemSize.Height())));
    }
}
} // namespace

void ToolbarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto toolbarNode = AceType::DynamicCast<ToolbarNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(toolbarNode);
    auto containerNode = toolbarNode->GetToolbarContainerNode();
    auto toolbarItemNum = containerNode->GetChildren().size();
    if (!containerNode || toolbarItemNum == 0) {
        LinearLayoutAlgorithm::Measure(layoutWrapper);
        return;
    }

    auto toolbarLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(toolbarLayoutProperty);
    auto constraint = toolbarLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto toolbarWidth = constraint->selfIdealSize.Width().value();
    auto toolbarHeight = constraint->selfIdealSize.Height().value();
    auto toolbarItemWidth = UpdateToolBarItemsContainer(layoutWrapper, toolbarItemNum, toolbarWidth);
    LinearLayoutAlgorithm::Measure(layoutWrapper);

    SizeF toolbarItemSize { toolbarItemWidth, toolbarHeight };
    auto toolbarItemMaxWidth = CalcToolbarItemMaxWidthIfNeedToExpand(toolbarWidth, toolbarItemNum);

    if (CheckWhetherBarItemSizeCrossBorder(layoutWrapper, toolbarItemSize)) {
        if (LessOrEqual(toolbarItemSize.Width(), toolbarItemMaxWidth)) {
            UpdateToolbarItemSize(layoutWrapper, toolbarItemSize);
        } else {
            toolbarItemSize.SetWidth(toolbarItemMaxWidth);
            UpdateToolbarItemSize(layoutWrapper, toolbarItemSize);
        }
        constraint->selfIdealSize.SetHeight(toolbarItemSize.Height());
        toolbarLayoutProperty->UpdateLayoutConstraint(constraint.value());
        LinearLayoutAlgorithm::Measure(layoutWrapper);
    }
}
} // namespace OHOS::Ace::NG