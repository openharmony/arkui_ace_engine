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

#include "core/components_ng/pattern/menu/sub_menu_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"

namespace OHOS::Ace::NG {

void SubMenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto menuNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto parentMenuItem = menuPattern->GetParentMenuItem();
    CHECK_NULL_VOID(parentMenuItem);
    auto menuItemSize = parentMenuItem->GetGeometryNode()->GetFrameSize();

    float x = HorizontalLayoutSubMenu(size, position_.GetX(), menuItemSize);
    float y = VerticalLayoutSubMenu(size, position_.GetY(), menuItemSize);
    auto mainMenuPattern = menuPattern->GetMainMenuPattern();
    if (mainMenuPattern && !mainMenuPattern->IsContextMenu()) {
        x -= pageOffset_.GetX();
        y -= pageOffset_.GetY();
    }

    const auto& geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetMarginFrameOffset(NG::OffsetF(x, y));

    if (parentMenuItem) {
        auto parentPattern = parentMenuItem->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(parentPattern);
        auto topLeftPoint = OffsetF(x, y);
        auto bottomRightPoint = OffsetF(x + size.Width(), y + size.Height());
        parentPattern->AddHoverRegions(topLeftPoint, bottomRightPoint);
    }

    auto child = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(child);
    child->Layout();
}

// return submenu vertical offset
float SubMenuLayoutAlgorithm::VerticalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize)
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
float SubMenuLayoutAlgorithm::HorizontalLayoutSubMenu(const SizeF& size, float position, const SizeF& menuItemSize)
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
} // namespace OHOS::Ace::NG
