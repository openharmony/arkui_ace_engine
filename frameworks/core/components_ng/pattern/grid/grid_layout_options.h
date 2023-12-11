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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_OPTIONS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_OPTIONS_H

#include <set>

namespace OHOS::Ace {
struct GridItemSize {
    int32_t rows = 1;
    int32_t columns = 1;
    bool operator==(const GridItemSize& itemSize) const
    {
        return (rows == itemSize.rows) && (columns == itemSize.columns);
    }
    int32_t GetCrossSize(Axis axis) const
    {
        return axis == Axis::VERTICAL ? columns : rows;
    }
};

struct GridItemRect {
    int32_t rowStart = -1;
    int32_t rowSpan = 1;
    int32_t columnStart = -1;
    int32_t columnSpan = 1;
    bool operator==(const GridItemRect& itemRect) const
    {
        return (rowStart == itemRect.rowStart) && (rowSpan == itemRect.rowSpan) &&
               (columnStart == itemRect.columnStart) && (columnSpan == itemRect.columnSpan);
    }
    int32_t GetCrossSize(Axis axis) const
    {
        return axis == Axis::VERTICAL ? columnSpan : rowSpan;
    }
    // [rowStart, columnStart, rowSpan, columnSpan]
    enum GridItemRectProperty { ROW_START, COLUMN_START, ROW_SPAN, COLUMN_SPAN };
};

using GetSizeByIndex = std::function<GridItemSize(int32_t)>;
using GetRectByIndex = std::function<GridItemRect(int32_t)>;

struct GridLayoutOptions {
    GridItemSize regularSize;
    std::set<int32_t> irregularIndexes;
    GetSizeByIndex getSizeByIndex; // irregular sizes
    GetRectByIndex getRectByIndex;
    bool operator==(const GridLayoutOptions& options) const
    {
        return (regularSize == options.regularSize) && (irregularIndexes == options.irregularIndexes) &&
               (!getSizeByIndex && !options.getSizeByIndex) && (!getRectByIndex && !options.getRectByIndex);
    }

    bool operator!=(const GridLayoutOptions& options) const
    {
        return !operator==(options);
    }
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_OPTIONS_H
