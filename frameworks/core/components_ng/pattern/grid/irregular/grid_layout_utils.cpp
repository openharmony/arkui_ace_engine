/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"

#include "core/components_ng/pattern/grid/grid_layout_property.h"
namespace OHOS::Ace::NG {
GridItemSize GridLayoutUtils::GetItemSize(const GridLayoutInfo* info, const LayoutWrapper* wrapper, int32_t idx)
{
    GridItemSize size { 1, 1 };
    auto props = AceType::DynamicCast<GridLayoutProperty>(wrapper->GetLayoutProperty());
    const auto& opts = *props->GetLayoutOptions();
    if (opts.irregularIndexes.find(idx) != opts.irregularIndexes.end()) {
        if (!opts.getSizeByIndex) {
            // default irregular size = [1, full cross length]
            return { 1, info->crossCount_ };
        }

        size = opts.getSizeByIndex(idx);

        // assume [row] represents mainLength and [column] represents crossLength in this class, so flip sides if
        // horizontal
        if (info->axis_ == Axis::HORIZONTAL) {
            std::swap(size.rows, size.columns);
        }
    }

    // handle illegal size
    if (size.columns > info->crossCount_) {
        size.columns = info->crossCount_;
    }
    return size;
}
} // namespace OHOS::Ace::NG
