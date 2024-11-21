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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_UTILS_H

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_layout_info.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::Ace::NG {
class GridPattern;

class GridLayoutUtils {
public:
    /**
     * @brief Gets the size of an item at the specified index.
     *
     * @param info The GridLayoutInfo object.
     * @param wrapper The LayoutWrapper of Grid.
     * @param idx The index of the item.
     * @return The size of the item.
     * IMPORTANT: Output assumes [row] represents mainSize and [column] represents crossSize.
     */
    static GridItemSize GetItemSize(const GridLayoutInfo* info, const LayoutWrapper* wrapper, int32_t idx);

    /**
     * @brief Add a task to preload GridItems when Pipeline is idle.
     *
     * @param pattern of this Grid component.
     * @param items list of GridItems to preload.
     * @param buildCb callback to build a GridItem.
     */
    static void PreloadGridItems(
        const RefPtr<GridPattern>& pattern, std::list<GridPreloadItem>&& items, const BuildGridItemCallback& buildCb);

private:
    // helper to add the GridItem build task to Pipeline
    static void PreloadGridItemsHelper(const RefPtr<GridPattern>& pattern, const BuildGridItemCallback& buildCb);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_LAYOUT_UTILS_H
