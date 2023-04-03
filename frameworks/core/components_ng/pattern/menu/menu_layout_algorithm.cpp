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

#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"

#include <optional>
#include <vector>

#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t MIN_GRID_COUNTS = 2;
constexpr uint32_t GRID_COUNTS_4 = 4;
constexpr uint32_t GRID_COUNTS_6 = 6;
constexpr uint32_t GRID_COUNTS_8 = 8;
constexpr uint32_t GRID_COUNTS_12 = 12;

uint32_t GetMaxGridCounts(const RefPtr<GridColumnInfo>& columnInfo)
{
    CHECK_NULL_RETURN(columnInfo, GRID_COUNTS_8);
    auto currentColumns = columnInfo->GetParent()->GetColumns();
    auto maxGridCounts = GRID_COUNTS_8;
    switch (currentColumns) {
        case GRID_COUNTS_4:
            maxGridCounts = GRID_COUNTS_4;
            break;
        case GRID_COUNTS_8:
            maxGridCounts = GRID_COUNTS_6;
            break;
        case GRID_COUNTS_12:
            maxGridCounts = GRID_COUNTS_8;
            break;
        default:
            break;
    }
    return maxGridCounts;
}
} // namespace

void MenuLayoutAlgorithm::Initialize(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    // currently using click point as menu position
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    auto targetSize = props->GetTargetSizeValue(SizeF());
    position_ = props->GetMenuOffset().value_or(OffsetF());
    LOGD("menu position_ = %{public}s, targetSize = %{public}s", position_.ToString().c_str(),
        targetSize.ToString().c_str());

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    margin_ = static_cast<float>(theme->GetOutPadding().ConvertToPx());
    optionPadding_ = margin_;

    auto constraint = props->GetLayoutConstraint();
    auto wrapperIdealSize =
        CreateIdealSize(constraint.value(), Axis::FREE, props->GetMeasureType(MeasureType::MATCH_PARENT), true);
    wrapperSize_ = wrapperIdealSize;
    topSpace_ = position_.GetY() - targetSize.Height() - margin_ * 2.0f;
    bottomSpace_ = wrapperSize_.Height() - position_.GetY() - margin_ * 2.0f;
    leftSpace_ = position_.GetX();
    rightSpace_ = wrapperSize_.Width() - leftSpace_;

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto page = stageManager->GetLastPage();
    CHECK_NULL_VOID(page);
    pageOffset_ = page->GetOffsetRelativeToWindow();
    topSpace_ -= pageOffset_.GetY();
    leftSpace_ -= pageOffset_.GetX();
}

// Called to perform layout render node and child.
void MenuLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // initialize screen size and menu position
    CHECK_NULL_VOID(layoutWrapper);
    Initialize(layoutWrapper);

    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuLayoutProperty);
    const auto& constraint = menuLayoutProperty->GetLayoutConstraint();
    if (!constraint) {
        LOGE("fail to measure menu due to layoutConstraint is nullptr");
        return;
    }
    auto idealSize = CreateIdealSize(
        constraint.value(), Axis::VERTICAL, menuLayoutProperty->GetMeasureType(MeasureType::MATCH_CONTENT), true);
    const auto& padding = menuLayoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);

    // calculate menu main size
    auto childConstraint = CreateChildConstraint(layoutWrapper);
    float idealHeight = 0.0f;
    float idealWidth = 0.0f;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(childConstraint);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        LOGD("child finish measure, child %{public}s size = %{public}s", child->GetHostTag().c_str(),
            child->GetGeometryNode()->GetMarginFrameSize().ToString().c_str());
        idealHeight += childSize.Height();
        idealWidth = std::max(idealWidth, childSize.Width());
    }
    idealSize.SetHeight(idealHeight);
    idealSize.SetWidth(idealWidth);
    AddPaddingToSize(padding, idealSize);

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    LOGD("finish measure, menu size = %{public}f x %{public}f", idealSize.Width(), idealSize.Height());
    geometryNode->SetFrameSize(idealSize);
}

void MenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);

    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    if (menuPattern->IsSubMenu()) {
        LayoutSubMenu(layoutWrapper);
        return;
    }

    auto size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize();
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    LOGD("MenuLayout: clickPosition = %{public}f, %{public}f", position_.GetX(), position_.GetY());
    CHECK_NULL_VOID(props);

    float x = HorizontalLayout(size, position_.GetX(), menuPattern->IsSelectMenu());
    float y = VerticalLayout(size, position_.GetY());
    if (!menuPattern->IsContextMenu()) {
        x -= pageOffset_.GetX();
        y -= pageOffset_.GetY();
    }

    MarginPropertyF margin;
    if (!menuPattern->IsMultiMenu()) {
        margin.left = margin.top = margin.right = margin.bottom = margin_;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameOffset(NG::OffsetF(x, y));

    // translate each option by the height of previous options
    OffsetF translate;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        LOGD("layout child at offset: %{public}s, tag %{public}s", translate.ToString().c_str(),
            child->GetHostTag().c_str());
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        translate += OffsetF(0, child->GetGeometryNode()->GetFrameSize().Height());
    }

    if (menuPattern->IsContextMenu()) {
        std::vector<Rect> rects;
        auto frameRect = layoutWrapper->GetGeometryNode()->GetFrameRect();
        auto rect = Rect(frameRect.GetX(), frameRect.GetY(), frameRect.Width(), frameRect.Height());
        rects.emplace_back(rect);
        SubwindowManager::GetInstance()->SetHotAreas(rects);
    }
}

void MenuLayoutAlgorithm::UpdateConstraintWidth(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    // set min width
    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    columnInfo->GetParent()->BuildColumnWidth();
    float minWidth = static_cast<float>(columnInfo->GetWidth(MIN_GRID_COUNTS));
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    constraint.minSize.SetWidth(minWidth);

    // set max width
    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuLayoutProperty);
    const auto& padding = menuLayoutProperty->CreatePaddingAndBorder();
    auto maxHorizontalSpace = std::max(leftSpace_, rightSpace_) - 2.0f * padding.Width();
    auto maxGridWidth = static_cast<float>(columnInfo->GetWidth(GetMaxGridCounts(columnInfo)));
    auto maxWidth = std::min(maxHorizontalSpace, maxGridWidth);
    maxWidth = std::min(constraint.maxSize.Width(), maxWidth);
    constraint.maxSize.SetWidth(maxWidth);
    constraint.percentReference.SetWidth(maxWidth);
}

void MenuLayoutAlgorithm::UpdateConstraintHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    auto maxSpaceHeight = std::max(topSpace_, bottomSpace_);
    constraint.maxSize.SetHeight(maxSpaceHeight);
    constraint.percentReference.SetHeight(maxSpaceHeight);
}

LayoutConstraintF MenuLayoutAlgorithm::CreateChildConstraint(LayoutWrapper* layoutWrapper)
{
    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(menuLayoutProperty, LayoutConstraintF());

    auto childConstraint = menuLayoutProperty->CreateChildConstraint();
    UpdateConstraintWidth(layoutWrapper, childConstraint);
    UpdateConstraintHeight(layoutWrapper, childConstraint);
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuLayoutProperty, childConstraint);
    if (!menuPattern->IsMultiMenu()) {
        UpdateConstraintBaseOnOptions(layoutWrapper, childConstraint);
    } else {
        UpdateConstraintBaseOnMenuItems(layoutWrapper, childConstraint);
    }
    return childConstraint;
}

void MenuLayoutAlgorithm::UpdateConstraintBaseOnOptions(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    auto menuPattern = layoutWrapper->GetHostNode()->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    if (options.empty()) {
        LOGD("options is empty, no need to update constraint.");
        return;
    }
    auto maxChildrenWidth = constraint.minSize.Width();
    auto optionConstraint = constraint;
    optionConstraint.maxSize.MinusWidth(optionPadding_ * 2.0f);
    auto optionsLayoutWrapper = GetOptionsLayoutWrappper(layoutWrapper);
    for (const auto& optionWrapper : optionsLayoutWrapper) {
        optionWrapper->Measure(optionConstraint);
        auto childSize = optionWrapper->GetGeometryNode()->GetMarginFrameSize();
        maxChildrenWidth = std::max(maxChildrenWidth, childSize.Width());
    }
    UpdateOptionConstraint(optionsLayoutWrapper, maxChildrenWidth);
    constraint.minSize.SetWidth(maxChildrenWidth + optionPadding_ * 2.0f);
}

std::list<RefPtr<LayoutWrapper>> MenuLayoutAlgorithm::GetOptionsLayoutWrappper(LayoutWrapper* layoutWrapper)
{
    std::list<RefPtr<LayoutWrapper>> optionsWrapper;
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(scrollWrapper, optionsWrapper);
    auto columnWrapper = scrollWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_RETURN(columnWrapper, optionsWrapper);
    optionsWrapper = columnWrapper->GetAllChildrenWithBuild();
    return optionsWrapper;
}

void MenuLayoutAlgorithm::UpdateOptionConstraint(std::list<RefPtr<LayoutWrapper>>& options, float width)
{
    for (const auto& option : options) {
        auto optionLayoutProps = option->GetLayoutProperty();
        CHECK_NULL_VOID(optionLayoutProps);
        optionLayoutProps->UpdateCalcMinSize(CalcSize(CalcLength(width), std::nullopt));
    }
}

void MenuLayoutAlgorithm::UpdateConstraintBaseOnMenuItems(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    // multiMenu children are menuItem or menuItemGroup, constrain width is same as the menu
    auto maxChildrenWidth = GetChildrenMaxWidth(layoutWrapper, constraint);
    constraint.minSize.SetWidth(maxChildrenWidth);
}

void MenuLayoutAlgorithm::LayoutSubMenu(LayoutWrapper* layoutWrapper)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto menuLayoutProperty = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(menuLayoutProperty);
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto parentMenuItem = menuPattern->GetParentMenuItem();
    CHECK_NULL_VOID(parentMenuItem);
    auto menuItemSize = parentMenuItem->GetGeometryNode()->GetFrameSize();

    float x = HorizontalLayoutSubMenu(size, position_.GetX(), menuItemSize) - pageOffset_.GetX();
    float y = VerticalLayoutSubMenu(size, position_.GetY(), menuItemSize) - pageOffset_.GetY();

    const auto& geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetMarginFrameOffset(NG::OffsetF(x, y));

    if (parentMenuItem) {
        auto parentPattern = parentMenuItem->GetPattern<MenuItemPattern>();
        auto topLeftPoint = OffsetF(x, y);
        auto bottomRightPoint = OffsetF(x + size.Width(), y + size.Height());
        parentPattern->AddHoverRegions(topLeftPoint, bottomRightPoint);
    }

    auto child = layoutWrapper->GetOrCreateChildByIndex(0);
    child->Layout();
}

// return vertical offset
float MenuLayoutAlgorithm::VerticalLayout(const SizeF& size, float position)
{
    float wrapperHeight = wrapperSize_.Height();
    // can put menu below click point
    if (bottomSpace_ >= size.Height()) {
        return position + margin_;
    }

    // put menu above click point
    if (topSpace_ >= size.Height()) {
        return topSpace_ - size.Height() + margin_ + pageOffset_.GetY();
    }

    // line up bottom of menu with bottom of the screen
    if (size.Height() < wrapperHeight) {
        return wrapperHeight - size.Height();
    }
    // can't fit in screen, line up with top of the screen
    return 0.0f;
}

// returns horizontal offset
float MenuLayoutAlgorithm::HorizontalLayout(const SizeF& size, float position, bool isSelectMenu)
{
    float wrapperWidth = wrapperSize_.Width();
    // can fit menu on the right side of position
    if (rightSpace_ >= size.Width()) {
        return position + margin_;
    }

    // fit menu on the left side
    if (!isSelectMenu && leftSpace_ >= size.Width()) {
        return position - size.Width();
    }

    // line up right side of menu with right boundary of the screen
    if (size.Width() < wrapperWidth) {
        return wrapperWidth - size.Width();
    }

    // can't fit in screen, line up with left side of the screen
    return 0.0f;
}

// return vertical offset
float MenuLayoutAlgorithm::VerticalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize)
{
    float wrapperHeight = wrapperSize_.Height();
    float bottomSpace = wrapperHeight - position;
    // line up top of subMenu with top of the menuItem
    if (bottomSpace >= size.Height()) {
        return position;
    }
    // line up bottom of menu with bottom of the screen
    if (size.Height() < wrapperHeight) {
        return wrapperHeight - size.Height();
    }
    // can't fit in screen, line up with top of the screen
    return 0.0f;
}

// returns submenu horizontal offset
float MenuLayoutAlgorithm::HorizontalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize)
{
    float wrapperWidth = wrapperSize_.Width();
    float rightSpace = wrapperWidth - position;
    float leftSpace = position - pageOffset_.GetX() - menuItemSize.Width();
    // can fit subMenu on the right side of menuItem
    if (rightSpace >= size.Width()) {
        return position;
    }
    // fit subMenu on the left side of menuItem
    if (leftSpace >= size.Width()) {
        return position - size.Width() - menuItemSize.Width();
    }
    // line up right side of menu with right boundary of the screen
    if (size.Width() < wrapperWidth) {
        return wrapperWidth - size.Width();
    }
    // can't fit in screen, line up with left side of the screen
    return 0.0f;
}

float MenuLayoutAlgorithm::GetChildrenMaxWidth(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint)
{
    float maxWidth = layoutConstraint.minSize.Width();
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
        auto childSize = child->GetGeometryNode()->GetFrameSize();
        maxWidth = std::max(maxWidth, childSize.Width());
    }
    return maxWidth;
}

} // namespace OHOS::Ace::NG
