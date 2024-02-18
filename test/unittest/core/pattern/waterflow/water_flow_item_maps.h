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

#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"

namespace OHOS::Ace::NG {
const decltype(WaterFlowLayoutInfo::items_) ITEM_MAP_1 = {
    {
        // segment 0
        { 0, { { 0, { 0.0f, 50.0f } } } },                          // Column 0
        { 1, { { 1, { 0.0f, 30.0f } }, { 4, { 35.0f, 20.0f } } } }, // Column 1
        { 2, { { 2, { 0.0f, 40.0f } } } },                          // Column 2
        { 3, { { 3, { 0.0f, 60.0f } } } },                          // Column 3
    },
    // segment 1
    {},
    // segment 2
    {
        { 0, { { 5, { 65.0f, 50.0f } } } },                                                  // Column 0
        { 1, { { 6, { 65.0f, 30.0f } }, { 8, { 96.0f, 2.0f } }, { 9, { 99.0f, 20.0f } } } }, // Column 1
        { 2, { { 7, { 65.0f, 40.0f } } } },                                                  // Column 2
    }
};

const std::map<int32_t, WaterFlowLayoutInfo::ItemInfo> ITEM_INFO_1 = {
    { 0, { 0.0f, 50.0f } },
    { 1, { 0.0f, 30.0f } },
    { 2, { 0.0f, 40.0f } },
    { 3, { 0.0f, 60.0f } },
    { 4, { 35.0f, 20.0f } },
    { 5, { 65.0f, 50.0f } },
    { 6, { 65.0f, 30.0f } },
    { 7, { 65.0f, 40.0f } },
    { 8, { 96.0f, 2.0f } },
    { 9, { 99.0f, 20.0f } },
};

const std::vector<std::pair<float, int32_t>> END_POS_ARRAY_1 = {
    { 50.0f, 0 },
    { 60.0f, 3 },
    { 115.0f, 5 },
    { 119.0f, 9 },
};

const std::vector<int32_t> SEGMENT_TAILS_1 = { 4, 4, 9 };
} // namespace OHOS::Ace::NG