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

#include "core/components_v2/grid_layout/render_grid_col.h"

#include "core/components_v2/grid_layout/grid_col_component.h"

namespace OHOS::Ace::V2 {

RefPtr<RenderNode> RenderGridCol::Create()
{
    return AceType::MakeRefPtr<RenderGridCol>();
}

void RenderGridCol::Update(const RefPtr<Component>& component)
{
    component_ = component;
}

void RenderGridCol::PerformLayout()
{
    auto layout = GetLayoutParam();
    auto children = GetChildren();
    if (children.size() != 1) {
        LOGI("Grid Col should only contain one component");
    }
    for (const auto& child : children) {
        // single child will run for once
        child->Layout(layout);
        SetLayoutSize(child->GetLayoutSize());
    }
}

int32_t RenderGridCol::GetSpan(GridSizeType sizeType) const
{
    auto gridCol = AceType::DynamicCast<GridColComponent>(component_);
    if (!gridCol) {
        LOGI("child component error return span 1");
        return 1;
    }
    return gridCol->GetSpan(sizeType);
}

int32_t RenderGridCol::GetOffset(GridSizeType sizeType) const
{
    auto gridCol = AceType::DynamicCast<GridColComponent>(component_);
    if (!gridCol) {
        LOGI("child component error return offset 0");
        return 0;
    }
    return gridCol->GetOffset(sizeType);
}

int32_t RenderGridCol::GetOrder(GridSizeType sizeType) const
{
    auto gridCol = AceType::DynamicCast<GridColComponent>(component_);
    if (!gridCol) {
        LOGI("child component error return order 0");
        return 0;
    }
    return gridCol->GetOrder(sizeType);
}

} // namespace OHOS::Ace::V2