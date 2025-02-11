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

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"

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

const decltype(WaterFlowLayoutInfo::items_) ITEM_MAP_3 = { {
    // segment 0
    { 0, { { 0, { 0.0f, 0.0f } } } },                           // Column 0
    { 1, { { 1, { 0.0f, 30.0f } }, { 4, { 35.0f, 20.0f } } } }, // Column 1
    { 2, { { 2, { 0.0f, 40.0f } } } },                          // Column 2
    { 3, { { 3, { 0.0f, 60.0f } } } },                          // Column 3
} };

const std::vector<std::pair<float, int32_t>> END_POS_ARRAY_3 = {
    { 0.0f, 0 },
    { 30.0f, 1 },
    { 40.0f, 2 },
    { 60.0f, 3 },
};

const std::function<float(int32_t)> GET_MAIN_SIZE_FUNC = [](int32_t idx) {
    if (idx & 1) {
        return 200.0f;
    }
    return 100.0f;
};

const std::vector<WaterFlowSections::Section> SECTION_4 = {
    WaterFlowSections::Section { .itemsCount = 20, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 3 },
    WaterFlowSections::Section { .itemsCount = 10, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 5 },
    WaterFlowSections::Section { .itemsCount = 0, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 2 },
    WaterFlowSections::Section { .itemsCount = 30, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC },
};
const std::vector<int32_t> SEGMENT_TAILS_4 = { 19, 29, 29, 59 };

const PaddingProperty MARGIN_1 = {
    .bottom = CalcLength(5.0_vp),
    .top = CalcLength(1.0_vp),
    .right = CalcLength(3.0_vp),
    .left = CalcLength(5.0_vp),
};

const std::vector<WaterFlowSections::Section> SECTION_5 = {
    WaterFlowSections::Section { .itemsCount = 5,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 3,
        .rowsGap = 5.0_px },
    WaterFlowSections::Section { .itemsCount = 5,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 5,
        .margin = MARGIN_1 },
    WaterFlowSections::Section { .itemsCount = 0, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC, .crossCount = 1 },
    WaterFlowSections::Section { .itemsCount = 30,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .rowsGap = 1.0_px,
        .columnsGap = 2.0_vp },
    WaterFlowSections::Section { .itemsCount = 20,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 2,
        .rowsGap = 2.0_px },
};
const std::vector<int32_t> SEGMENT_TAILS_5 = { 4, 9, 9, 39, 59 };

const std::vector<float> CROSS_GAP_5 = { 0.0f, 0.0f, 0.0f, 2.0f, 0.0f };
const std::vector<float> MAIN_GAP_5 = { 5.0f, 0.0f, 0.0f, 1.0f, 2.0f };
// assuming WaterFlow width = 400.0f
const std::vector<std::vector<float>> ITEM_CROSS_SIZE_5 = { { 400.0f / 3, 400.0f / 3, 400.0f / 3 },
    { 78.4f, 78.4f, 78.4f, 78.4f, 78.4f }, { 400.0f }, { 400.0f }, { 200.0f, 200.0f } };

const std::vector<WaterFlowSections::Section> ADD_SECTION_6 = {
    WaterFlowSections::Section { .itemsCount = 10,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 2,
        .rowsGap = 5.0_px },
};

const PaddingProperty MARGIN_2 = {
    .bottom = CalcLength(3.0_vp),
    .top = CalcLength(5.0_vp),
};

const std::function<float(int32_t)> GET_MAIN_SIZE_2 = [](int32_t idx) { return 100.0f; };

const std::vector<WaterFlowSections::Section> SECTION_7 = {
    WaterFlowSections::Section { .itemsCount = 4,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 1,
        .margin = MARGIN_2 },
    WaterFlowSections::Section { .itemsCount = 3,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 2,
        .columnsGap = 5.0_vp },
    WaterFlowSections::Section { .itemsCount = 0,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 5,
        .margin = MARGIN_2 },
    WaterFlowSections::Section { .itemsCount = 30,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .rowsGap = 2.0_px,
        .margin = MARGIN_2 },
};

const std::vector<WaterFlowSections::Section> ADD_SECTION_7 = {
    WaterFlowSections::Section { .itemsCount = 10,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 2,
        .columnsGap = 5.0_vp },
};

const std::function<float(int32_t)> GET_MAIN_SIZE_ILLEGAL = [](int32_t idx) { return -100.0f; };
const std::vector<WaterFlowSections::Section> SECTION_8 = {
    WaterFlowSections::Section { .itemsCount = 10,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_ILLEGAL,
        .crossCount = 1,
        .margin = MARGIN_2 },
};
const std::vector<WaterFlowSections::Section> SECTION_9 = {
    { .itemsCount = 6, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2, .crossCount = 3 },
};

const std::vector<WaterFlowSections::Section> SECTION_10 = {
    { .itemsCount = 3, .crossCount = 3, .margin = MARGIN_2, .rowsGap = Dimension(5.0f) },
    { .itemsCount = 2, .crossCount = 2, .margin = MARGIN_2, .rowsGap = Dimension(5.0f) },
    { .itemsCount = 3, .crossCount = 3 },
    { .itemsCount = 2, .crossCount = 2 },
    { .itemsCount = 3, .crossCount = 3 },
    { .itemsCount = 2, .crossCount = 2 },
    { .itemsCount = 30, .crossCount = 3 },
};

const PaddingProperty MARGIN_3 = {
    .bottom = CalcLength(5.0_vp),
    .top = CalcLength(5.0_vp),
    .left = CalcLength(2.0_vp),
    .right = CalcLength(2.0_vp),
};

const std::vector<WaterFlowSections::Section> SECTION_11 = {
    WaterFlowSections::Section { .itemsCount = 3,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 1,
        .rowsGap = 5.0_vp,
        .margin = MARGIN_3 },
    WaterFlowSections::Section { .itemsCount = 2,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .crossCount = 2,
        .rowsGap = 5.0_vp,
        .columnsGap = 5.0_vp,
        .margin = MARGIN_3 },
    WaterFlowSections::Section { .itemsCount = 0,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 5,
        .margin = MARGIN_3 },
    WaterFlowSections::Section { .itemsCount = 30,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_2,
        .rowsGap = 2.0_px,
        .margin = MARGIN_3 },
};

const std::vector<WaterFlowSections::Section> SECTION_12 = {
    WaterFlowSections::Section { .itemsCount = 3,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 1,
        .rowsGap = 5.0_vp,
        .margin = MARGIN_3 },
    WaterFlowSections::Section { .itemsCount = 2,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 2,
        .rowsGap = 5.0_vp,
        .columnsGap = 5.0_vp,
        .margin = MARGIN_3 },
    WaterFlowSections::Section { .itemsCount = 0,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 5,
        .margin = MARGIN_3 },
    WaterFlowSections::Section { .itemsCount = 5,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 2,
        .rowsGap = 2.0_px,
        .margin = MARGIN_3 },
    WaterFlowSections::Section { .itemsCount = 5,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 4,
        .rowsGap = 2.0_px,
        .margin = MARGIN_3 },
    WaterFlowSections::Section { .itemsCount = 15,
        .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC,
        .crossCount = 3,
        .rowsGap = 2.0_px,
        .margin = MARGIN_3 },
};

const std::vector<WaterFlowSections::Section> SECTION_13 = {
    { .itemsCount = 2, .crossCount = 2},
    { .itemsCount = 2, .crossCount = 2 },
    { .itemsCount = 1, .crossCount = 1 },
};

const std::vector<WaterFlowSections::Section> SECTION_14 = {
    { .itemsCount = 14, .crossCount = 2 },
    { .itemsCount = 20, .crossCount = 1 },
    { .itemsCount = 3, .crossCount = 1 },
};

const std::vector<WaterFlowSections::Section> SECTION_15 = {
    { .itemsCount = 4, .crossCount = 2, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC },
    { .itemsCount = 8, .crossCount = 1, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC },
    { .itemsCount = 4, .crossCount = 2, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC },
    { .itemsCount = 6, .crossCount = 1, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC },
    { .itemsCount = 4, .crossCount = 2, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC },
    { .itemsCount = 6, .crossCount = 1, .onGetItemMainSizeByIndex = GET_MAIN_SIZE_FUNC },
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_WATER_FLOW_ITEM_MAPS_H
