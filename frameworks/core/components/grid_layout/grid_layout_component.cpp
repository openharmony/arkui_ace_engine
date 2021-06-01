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

#include "core/components/grid_layout/grid_layout_component.h"

#include "core/components/grid_layout/grid_layout_element.h"
#include "core/components/grid_layout/render_grid_layout.h"

namespace OHOS::Ace {

RefPtr<Element> GridLayoutComponent::CreateElement()
{
    return AceType::MakeRefPtr<GridLayoutElement>();
}

RefPtr<RenderNode> GridLayoutComponent::CreateRenderNode()
{
    return RenderGridLayout::Create();
}

void GridLayoutComponent::SetDirection(FlexDirection direction)
{
    if (direction < FlexDirection::ROW || direction > FlexDirection::COLUMN_REVERSE) {
        LOGW("Invalid direction %{public}d", direction);
        return;
    }
    direction_ = direction;
}

void GridLayoutComponent::SetFlexAlign(FlexAlign flexAlign)
{
    if (flexAlign < FlexAlign::FLEX_START || flexAlign > FlexAlign::STRETCH) {
        LOGW("Invalid flexAlign %{public}d", flexAlign);
        return;
    }
    flexAlign_ = flexAlign;
}

void GridLayoutComponent::SetColumnCount(int32_t count)
{
    if (count <= 0) {
        LOGW("Invalid ColumnCount %{public}d", count);
        return;
    }
    columnCount_ = count;
}

void GridLayoutComponent::SetRowCount(int32_t count)
{
    if (count <= 0) {
        LOGW("Invalid RowCount %{public}d", count);
        return;
    }
    rowCount_ = count;
}

void GridLayoutComponent::SetWidth(double width)
{
    if (width <= 0.0) {
        LOGW("Invalid Width %{public}lf", width);
        return;
    }
    width_ = width;
}

void GridLayoutComponent::SetHeight(double height)
{
    if (height <= 0.0) {
        LOGW("Invalid Height %{public}lf", height);
        return;
    }
    height_ = height;
}

void GridLayoutComponent::SetColumnsArgs(const std::string& columnsArgs)
{
    columnsArgs_ = columnsArgs;
}

void GridLayoutComponent::SetRowsArgs(const std::string& rowsArgs)
{
    rowsArgs_ = rowsArgs;
}

void GridLayoutComponent::SetColumnGap(double columnGap)
{
    if (columnGap < 0.0) {
        LOGW("Invalid ColumnGap %{public}lf", columnGap);
        return;
    }
    columnGap_ = columnGap;
}

void GridLayoutComponent::SetRowGap(double rowGap)
{
    if (rowGap < 0.0) {
        LOGW("Invalid RowGap %{public}lf", rowGap);
        return;
    }
    rowGap_ = rowGap;
}

void GridLayoutComponent::SetRightToLeft(bool rightToLeft)
{
    LOGD("SetRightToLeft to %{public}d.", rightToLeft);
    rightToLeft_ = rightToLeft;
}

} // namespace OHOS::Ace
