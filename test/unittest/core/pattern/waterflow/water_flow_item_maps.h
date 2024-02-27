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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_ITEM_MAPS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_ITEM_MAPS_H

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

const decltype(WaterFlowLayoutInfo::itemInfos_) ITEM_INFO_1 = {
    { 0, 0.0f, 50.0f },
    { 1, 0.0f, 30.0f },
    { 2, 0.0f, 40.0f },
    { 3, 0.0f, 60.0f },
    { 1, 35.0f, 20.0f },
    { 0, 65.0f, 50.0f },
    { 1, 65.0f, 30.0f },
    { 2, 65.0f, 40.0f },
    { 1, 96.0f, 2.0f },
    { 1, 99.0f, 20.0f },
};

const std::vector<std::pair<float, int32_t>> END_POS_ARRAY_1 = {
    { 50.0f, 0 },
    { 60.0f, 3 },
    { 115.0f, 5 },
    { 119.0f, 9 },
};

const std::vector<int32_t> SEGMENT_TAILS_1 = { 4, 4, 9 };

const decltype(WaterFlowLayoutInfo::items_) ITEM_MAP_2 = {
    {
        { 0, { { 0, { 0, 100 } }, { 4, { 101, 100 } }, { 8, { 202, 100 } } } },
        { 1, { { 1, { 0, 200 } }, { 6, { 201, 100 } }, { 9, { 302, 200 } } } },
        { 2, { { 2, { 0, 100 } }, { 5, { 101, 200 } } } }, // Column 2
        { 3, { { 3, { 0, 200 } }, { 7, { 201, 200 } } } }  // Column 3
    },
    { { 0, { { 10, { 502, 50 } } } } } // footer
};

const decltype(WaterFlowLayoutInfo::itemInfos_) ITEM_INFO_2 = {
    { 0, 0.0f, 100.0f },
    { 1, 0.0f, 200.0f },
    { 2, 0.0f, 100.0f },
    { 3, 0.0f, 200.0f },
    { 0, 101.0f, 100.0f },
    { 2, 101.0f, 200.0f },
    { 1, 201.0f, 100.0f },
    { 3, 201.0f, 200.0f },
    { 0, 202.0f, 100.0f },
    { 1, 302.0f, 200.0f },
    { 0, 502.0F, 50.0f },
};

const std::vector<std::pair<float, int32_t>> END_POS_ARRAY_2 = {
    { 100.0f, 0 },
    { 200.0f, 1 },
    { 201.0f, 4 },
    { 301.0f, 5 },
    { 401.0f, 7 },
    { 502.0f, 9 },
    { 552.0f, 10 },
};

const std::vector<int32_t> SEGMENT_TAILS_2 = { 9, 10 };
const std::vector<float> SEGMENT_START_POS_2 = { 0.0f, 502.0f };

const std::vector<int32_t> SEGMENT_TAILS_3 = { 99, 100 };

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_ITEM_MAPS_H
