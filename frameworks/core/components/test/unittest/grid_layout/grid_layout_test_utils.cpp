/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/test/unittest/grid_layout/grid_layout_test_utils.h"

#include "core/components/box/box_component.h"
#include "core/components/grid_layout/grid_layout_component.h"

namespace OHOS::Ace {

void GridLayoutTestUtils::PrintNodeInfo(const RefPtr<RenderNode>& node)
{
    if (!node) {
        printf("ERROR: node is nullptr.");
        return;
    }
    printf("Node Position(%lf %lf) Size(%lf %lf)\n", node->GetPosition().GetX(), node->GetPosition().GetY(),
        node->GetLayoutSize().Width(), node->GetLayoutSize().Height());
}

RefPtr<Component> GridLayoutTestUtils::CreateComponent(FlexDirection direction, std::string rows, std::string cols)
{
    std::list<RefPtr<Component>> children;
    RefPtr<GridLayoutComponent> component = AceType::MakeRefPtr<GridLayoutComponent>(children);
    component->SetWidth(1080.0);
    component->SetHeight(1080.0);
    component->SetDirection(direction);
    component->SetRowsArgs(rows);
    component->SetColumnsArgs(cols);
    return component;
}

RefPtr<RenderNode> GridLayoutTestUtils::CreateRenderItem(int32_t row, int32_t col, int32_t rowSpan, int32_t colSpan)
{
    RefPtr<BoxComponent> boxComponent = AceType::MakeRefPtr<BoxComponent>();
    RefPtr<RenderBox> renderBox = AceType::MakeRefPtr<MockRenderBox>();
    boxComponent->SetWidth(540.0);
    boxComponent->SetHeight(540.0);
    renderBox->Update(boxComponent);
    RefPtr<RenderGridLayoutItem> item = AceType::MakeRefPtr<MockRenderGridLayoutItem>();
    item->SetRowIndex(row);
    item->SetColumnIndex(col);
    item->SetRowSpan(rowSpan);
    item->SetColumnSpan(colSpan);
    item->AddChild(renderBox);
    return item;
}

} // namespace OHOS::Ace
