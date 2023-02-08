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

#include "core/components_ng/pattern/list/list_item_group_pattern.h"

#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_paint_method.h"

namespace OHOS::Ace::NG {

RefPtr<LayoutAlgorithm> ListItemGroupPattern::CreateLayoutAlgorithm()
{
    auto layoutAlgorithm = MakeRefPtr<ListItemGroupLayoutAlgorithm>(headerIndex_, footerIndex_, itemStartIndex_);
    layoutAlgorithm->SetItemsPosition(itemPosition_);
    return layoutAlgorithm;
}

RefPtr<NodePaintMethod> ListItemGroupPattern::CreateNodePaintMethod()
{
    auto layoutProperty = GetLayoutProperty<ListItemGroupLayoutProperty>();
    V2::ItemDivider itemDivider;
    auto divider = layoutProperty->GetDivider().value_or(itemDivider);
    auto drawVertical = (axis_ == Axis::HORIZONTAL);
    return MakeRefPtr<ListItemGroupPaintMethod>(divider, drawVertical, lanes_, spaceWidth_, itemPosition_);
}

bool ListItemGroupPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    itemPosition_ = layoutAlgorithm->GetItemPosition();
    spaceWidth_ = layoutAlgorithm->GetSpaceWidth();
    lanes_ = layoutAlgorithm->GetLanes();
    axis_ = layoutAlgorithm->GetAxis();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto listLayoutProperty = host->GetLayoutProperty<ListItemGroupLayoutProperty>();
    return listLayoutProperty && listLayoutProperty->GetDivider().has_value() && !itemPosition_.empty();
}
} // namespace OHOS::Ace::NG