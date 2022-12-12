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
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {

constexpr uint32_t MIN_GRID_COUNTS = 2;
constexpr uint32_t MAX_GRID_COUNTS = 6;

} // namespace

namespace OHOS::Ace::NG {

void MenuLayoutAlgorithm::Initialize(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    screenSize_ = SizeF(pipeline->GetRootWidth(), pipeline->GetRootHeight());

    // currently using click point as menu position
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    position_ = props->GetMenuOffset().value_or(OffsetF());
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
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childSize = child->GetGeometryNode()->GetFrameSize();
        LOGD("menu childSize = %{public}f, %{public}f", childSize.Width(), childSize.Height());
        // set minimum size
        childSize.SetWidth(maxChildrenWidth);
        child->GetGeometryNode()->SetFrameSize(childSize);

        menuSize.AddHeight(childSize.Height());
    }
    // set menu size
    menuSize.AddHeight(2.0 * outPadding);
    menuSize.AddWidth(2.0 * outPadding);
    LOGD("finish measure, menu size = %{public}f x %{public}f", menuSize.Width(), menuSize.Height());
    layoutWrapper->GetGeometryNode()->SetFrameSize(menuSize);
}

void MenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    LOGD("MenuLayout: clickPosition = %{public}f, %{public}f", position_.GetX(), position_.GetY());
    CHECK_NULL_VOID(props);

    float x = HorizontalLayout(size, position_.GetX());
    float y = VerticalLayout(size, position_.GetY());

    layoutWrapper->GetGeometryNode()->SetMarginFrameOffset(NG::OffsetF(x, y));

    // translate each option by the height of previous options
    auto outPadding = OUT_PADDING.ConvertToPx();
    OffsetF translate(outPadding, outPadding);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        LOGD("layout child at offset: %{public}f, %{public}f", translate.GetX(), translate.GetY());
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        translate += OffsetF(0, child->GetGeometryNode()->GetFrameSize().Height());
    }
}

// return vertical offset
float MenuLayoutAlgorithm::VerticalLayout(const SizeF& size, float clickPosition)
{
    double screenHeight = screenSize_.Height();
    double bottomSpace = screenHeight - clickPosition;
    double topSpace = clickPosition;
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
    double leftSpace = clickPosition;
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
