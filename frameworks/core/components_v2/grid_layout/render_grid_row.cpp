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

#include "core/components_v2/grid_layout/render_grid_row.h"

#include <utility>

#include "core/components_v2/grid_layout/grid_container_utils.h"
#include "core/components_v2/grid_layout/grid_row_component.h"
#include "core/components_v2/grid_layout/render_grid_col.h"

namespace OHOS::Ace::V2 {
namespace {
struct OrderCompartor {
    bool operator()(const RefPtr<RenderNode>& left, const RefPtr<RenderNode>& right) const
    {
        auto leftGrid = AceType::DynamicCast<RenderGridCol>(left);
        auto rightGrid = AceType::DynamicCast<RenderGridCol>(right);
        return (leftGrid->GetOrder() < rightGrid->GetOrder());
    }
};

inline std::list<RefPtr<RenderNode>, OrderCompartor> SortChildrenByOrder(const std::list<RefPtr<RenderNode>>& children)
{
    return std::list<RefPtr<RenderNode>, OrderCompartor>(children.begin(), children.end());
}
} // namespace

RefPtr<RenderNode> RenderGridRow::Create()
{
    return AceType::MakeRefPtr<RenderGridRow>();
}

void RenderGridRow::Update(const RefPtr<Component>& component)
{
    auto gridRowComponent = AceType::DynamicCast<GridRowComponent>(component);
    if (!gridRowComponent) {
        LOGE("update grid row component fail, because type unmatch");
        return;
    }
    gridRowComponent_ = component;
}

void RenderGridRow::PerformLayout()
{
    auto maxSize = GetLayoutParam().GetMaxSize();
    auto component = AceType::DynamicCast<GridRowComponent>(gridRowComponent_);
    if (!component) {
        LOGI("Grid row fail to perform build");
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGI("context upgrade fail perform layout fail");
        return;
    }
    auto sizeType = GridContainerUtils::ProcessGridSizeType(component->GetBreakPoints(), maxSize, context);
    auto getter = GridContainerUtils::ProcessGetter(sizeType, component->GetGetter());
    auto getterInDouble = std::make_pair<double, double>(NormalizeToPx(getter.first), NormalizeToPx(getter.second));
    int32_t columnNum = GridContainerUtils::ProcessColumn(sizeType, component->GetTotalCol());
    double childWidthLimit = GridContainerUtils::ProcessColumnWidth(getterInDouble, columnNum, maxSize);
    LOGI("yyc childWidthLimit %{public}lf", childWidthLimit);
    LayoutEachChild(childWidthLimit, maxSize.Height(), getterInDouble.first);
    int offset = 0;
    std::pair<double, double> pos = {0, 0};
    for (auto child : gridColChildren_) {

    }
}

void RenderGridRow::LayoutEachChild(double childWidthLimit, double childHeightLimit, double getter)
{
    auto children = GetChildren();
    for (auto child : children) {
        auto gridCol = AceType::DynamicCast<RenderGridCol>(child);
        if (!gridCol) {
            LOGI("check the component inside grid_row is grid_col");
            return;
        }
        auto span = gridCol->GetSpan();
        LayoutParam childLayout(Size(childWidthLimit * span + (span - 1) * getter, childHeightLimit),
            Size(childWidthLimit * span + (span - 1) * getter, 0));
        child->Layout(childLayout);
    }
    gridColChildren_ = SortChildrenByOrder(children);
}

} // namespace OHOS::Ace::V2