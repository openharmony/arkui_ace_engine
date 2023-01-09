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

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {

constexpr uint32_t MIN_GRID_COUNTS = 2;
constexpr uint32_t MAX_GRID_COUNTS = 6;

} // namespace

namespace OHOS::Ace::NG {

void MenuLayoutAlgorithm::Initialize(LayoutWrapper* layoutWrapper)
{
    // currently using click point as menu position
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    position_ = props->GetMenuOffset().value_or(OffsetF());

    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    screenSize_ = SizeF(pipeline->GetRootWidth(), pipeline->GetRootHeight());

    auto stageManager = pipeline->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    auto page = stageManager->GetLastPage();
    CHECK_NULL_VOID(page);
    pageOffset_ = page->GetOffsetRelativeToWindow();
}

// Called to perform layout render node and child.
void MenuLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // initialize screen size and menu position
    CHECK_NULL_VOID(layoutWrapper);
    Initialize(layoutWrapper);

    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    const auto& padding = props->CreatePaddingAndBorder();
    LOGD("menu padding width = %{public}f", padding.Width());
    double outPadding = OUT_PADDING.ConvertToPx();

    // calculate menu main size
    auto childConstraint = props->CreateChildConstraint();
    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
    columnInfo->GetParent()->BuildColumnWidth();
    float minWidth = columnInfo->GetWidth(MIN_GRID_COUNTS);
    childConstraint.minSize.SetWidth(minWidth);

    // set max width
    LOGD("Measure Menu Position = %{public}f %{public}f", position_.GetX(), position_.GetY());
    auto leftSpace = position_.GetX();
    auto rightSpace = screenSize_.Width() - leftSpace;
    float maxWidth = std::min(std::max(leftSpace, rightSpace) - 2.0 * padding.Width() - 2.0 * outPadding,
        columnInfo->GetWidth(MAX_GRID_COUNTS));
    childConstraint.maxSize.SetWidth(maxWidth);
    childConstraint.percentReference.SetWidth(maxWidth);

    // measure children (options/customNode)
    float maxChildrenWidth = GetChildrenMaxWidth(layoutWrapper->GetAllChildrenWithBuild(), childConstraint);
    SizeF menuSize;
    menuSize.SetWidth(maxChildrenWidth);
    childConstraint.selfIdealSize.SetWidth(maxChildrenWidth);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(childConstraint);
        auto childSize = child->GetGeometryNode()->GetFrameSize();
        LOGD("menu childSize = %{public}f, %{public}f", childSize.Width(), childSize.Height());
        // set minimum size
        childSize.SetWidth(maxChildrenWidth);
        child->GetGeometryNode()->SetFrameSize(childSize);

        menuSize.AddHeight(childSize.Height());
    }
    // set menu size
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    if (!menuPattern->IsMultiMenu()) {
        menuSize.AddHeight(2.0 * outPadding);
        menuSize.AddWidth(2.0 * outPadding);
    }

    LOGD("finish measure, menu size = %{public}f x %{public}f", menuSize.Width(), menuSize.Height());
    layoutWrapper->GetGeometryNode()->SetFrameSize(menuSize);
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

    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    LOGD("MenuLayout: clickPosition = %{public}f, %{public}f", position_.GetX(), position_.GetY());
    CHECK_NULL_VOID(props);

    float x = HorizontalLayout(size, position_.GetX());
    float y = VerticalLayout(size, position_.GetY());
    if (!menuPattern->IsContextMenu()) {
        x -= pageOffset_.GetX();
        y -= pageOffset_.GetY();
    }
    auto outPadding = OUT_PADDING.ConvertToPx();
    MarginPropertyF margin;
    if (!menuPattern->IsMultiMenu()) {
        margin.left = margin.top = margin.right = margin.bottom = outPadding;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->UpdateMargin(margin);
    geometryNode->SetMarginFrameOffset(NG::OffsetF(x, y));

    // translate each option by the height of previous options
    OffsetF translate;
    auto menuParent = menuNode->GetParent();
    CHECK_NULL_VOID(menuParent);
    if (!menuPattern->IsMultiMenu() || menuParent->GetTag() == V2::MENU_ETS_TAG) {
        translate = OffsetF(outPadding, outPadding);
    }
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        LOGD("layout child at offset: %{public}f, %{public}f", translate.GetX(), translate.GetY());
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        translate += OffsetF(0, child->GetGeometryNode()->GetFrameSize().Height());
    }
}

void MenuLayoutAlgorithm::LayoutSubMenu(LayoutWrapper* layoutWrapper)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
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

    auto outPadding = OUT_PADDING.ConvertToPx();
    OffsetF translate(outPadding, outPadding);
    auto child = layoutWrapper->GetOrCreateChildByIndex(0);
    child->GetGeometryNode()->SetMarginFrameOffset(translate);
    child->Layout();
}

// return vertical offset
float MenuLayoutAlgorithm::VerticalLayout(const SizeF& size, float clickPosition)
{
    double screenHeight = screenSize_.Height();
    double bottomSpace = screenHeight - clickPosition;
    double topSpace = clickPosition - pageOffset_.GetY();
    // can put menu below click point
    if (bottomSpace >= size.Height()) {
        return clickPosition;
    }

    // put menu above click point
    if (topSpace >= size.Height()) {
        return clickPosition - size.Height();
    }

    // line up bottom of menu with bottom of the screen
    if (size.Height() < screenHeight) {
        return screenHeight - size.Height();
    }
    // can't fit in screen, line up with top of the screen
    return 0.0;
}

// returns horizontal offset
float MenuLayoutAlgorithm::HorizontalLayout(const SizeF& size, float clickPosition)
{
    double screenWidth = screenSize_.Width();
    double rightSpace = screenWidth - clickPosition;
    double leftSpace = clickPosition - pageOffset_.GetX();
    // can fit menu on the right side of clickPosition
    if (rightSpace >= size.Width()) {
        return clickPosition;
    }

    // fit menu on the left side
    if (leftSpace >= size.Width()) {
        return clickPosition - size.Width();
    }

    // line up right side of menu with right boundary of the screen
    if (size.Width() < screenWidth) {
        return screenWidth - size.Width();
    }

    // can't fit in screen, line up with left side of the screen
    return 0.0;
}

// return vertical offset
float MenuLayoutAlgorithm::VerticalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize)
{
    float screenHeight = screenSize_.Height();
    float bottomSpace = screenHeight - position;
    // line up top of subMenu with top of the menuItem
    if (bottomSpace >= size.Height()) {
        return position;
    }
    // line up bottom of menu with bottom of the screen
    if (size.Height() < screenHeight) {
        return screenHeight - size.Height();
    }
    // can't fit in screen, line up with top of the screen
    return 0.0;
}

// returns submenu horizontal offset
float MenuLayoutAlgorithm::HorizontalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize)
{
    float screenWidth = screenSize_.Width();
    float rightSpace = screenWidth - position;
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
    if (size.Width() < screenWidth) {
        return screenWidth - size.Width();
    }
    // can't fit in screen, line up with left side of the screen
    return 0.0;
}

float MenuLayoutAlgorithm::GetChildrenMaxWidth(
    const std::list<RefPtr<LayoutWrapper>>& children, const LayoutConstraintF& layoutConstraint)
{
    float width = layoutConstraint.minSize.Width();

    for (const auto& child : children) {
        child->Measure(layoutConstraint);
        auto childSize = child->GetGeometryNode()->GetFrameSize();
        width = std::max(width, childSize.Width());
    }
    return width;
}

} // namespace OHOS::Ace::NG
