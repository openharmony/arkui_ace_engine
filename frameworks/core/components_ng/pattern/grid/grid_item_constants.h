/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_CONSTANTS_H

#include <cstdint>

namespace OHOS::Ace::NG {
enum class GridItemStyle {
    NONE = 0,
    PLAIN,
};

struct GridItemIndexInfo {
    int32_t mainIndex = -1;
    int32_t crossIndex = -1;
    int32_t mainSpan = -1;
    int32_t crossSpan = -1;
    int32_t mainStart = -1;
    int32_t mainEnd = -1;
    int32_t crossStart = -1;
    int32_t crossEnd = -1;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_CONSTANTS_H
