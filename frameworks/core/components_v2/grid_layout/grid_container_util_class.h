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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_CONTAINER_UTIL_CLASS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_CONTAINER_UTIL_CLASS_H

#include <utility>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace::V2 {

struct GridContainerSize : public AceType {
    int32_t xs = 0;
    int32_t sm = 0;
    int32_t md = 0;
    int32_t lg = 0;
    int32_t xl = 0;
    int32_t xxl = 0;
};

enum class BreakPointsReference {
    WindowSize,
    ComponentSize,
};

enum class GridRowDirection {
    Row,
    RowReverse,
};

enum class GridSizeType {
    XS = 0,
    SM = 1,
    MD = 2,
    LG = 3,
    XL = 4,
    XXL = 5,
};

struct GridSizeInfo : public AceType {
    std::vector<Dimension> sizeInfo {
        Dimension(320, DimensionUnit::VP),
        Dimension(520, DimensionUnit::VP),
        Dimension(840, DimensionUnit::VP),
    };

    void Reset()
    {
        sizeInfo.clear();
    }
};

class Getter : public AceType {
    DECLARE_ACE_TYPE(Getter, AceType);

public:
    Dimension xXs;
    Dimension yXs;
    Dimension xSm;
    Dimension ySm;
    Dimension xMd;
    Dimension yMd;
    Dimension xLg;
    Dimension yLg;
    Dimension xXl;
    Dimension yXl;
    Dimension xXXl;
    Dimension yXXl;
};

class BreakPoints : public AceType {
    DECLARE_ACE_TYPE(BreakPoints, AceType);

public:
    BreakPointsReference reference = BreakPointsReference::WindowSize;
    std::vector<std::string> breakpoints;
};

} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_GRID_CONTAINER_UTIL_CLASS_H