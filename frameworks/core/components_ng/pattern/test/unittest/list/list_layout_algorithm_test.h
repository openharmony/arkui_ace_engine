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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_TEST_UNITTEST_LIST_LAYOUT_ALGORITHM_TEST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_TEST_UNITTEST_LIST_LAYOUT_ALGORITHM_TEST_H

#define private public
#define protected public
#include "core/components_ng/pattern/list/list_layout_property.h"

namespace OHOS::Ace {

const int32_t START_INDEX = 0;
const int32_t END_INDEX = 10;

const float GEOMETRYNODE_FRAMESIZE = 200.0;

const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_1 = Dimension(0);
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_2 = Dimension(10);
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_3 = Dimension(100);
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_4 = Dimension(1000);
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PX_5 = Dimension(10000);
const std::vector<Dimension> LIST_LAYOUT_ALGORITHM_SPACE_PXS = {LIST_LAYOUT_ALGORITHM_SPACE_PX_1,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_PX_2,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_PX_3,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_PX_4,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_PX_5};
const size_t TEST_SPACE_PX_COUNT = LIST_LAYOUT_ALGORITHM_SPACE_PXS.size();

const Dimension LIST_LAYOUT_ALGORITHM_SPACE_VP_1 = 0.0_vp;
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_VP_2 = 10.0_vp;
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_VP_3 = 20.0_vp;
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_VP_4 = 30.0_vp;
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_VP_5 = 40.0_vp;
const std::vector<Dimension> LIST_LAYOUT_ALGORITHM_SPACE_VPS = {LIST_LAYOUT_ALGORITHM_SPACE_VP_1,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_VP_2,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_VP_3,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_VP_4,
                                                                LIST_LAYOUT_ALGORITHM_SPACE_VP_5};
const size_t TEST_SPACE_VP_COUNT = LIST_LAYOUT_ALGORITHM_SPACE_VPS.size();

const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_1 = Dimension(0.0, DimensionUnit::PERCENT);
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_2 = Dimension(0.1, DimensionUnit::PERCENT);
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_3 = Dimension(0.2, DimensionUnit::PERCENT);
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_4 = Dimension(0.3, DimensionUnit::PERCENT);
const Dimension LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_5 = Dimension(0.4, DimensionUnit::PERCENT);
const std::vector<Dimension> LIST_LAYOUT_ALGORITHM_SPACE_PERCENTS = {LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_1,
                                                                     LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_2,
                                                                     LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_3,
                                                                     LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_4,
                                                                     LIST_LAYOUT_ALGORITHM_SPACE_PERCENT_5};
const size_t TEST_SPACE_PERCENT_COUNT = LIST_LAYOUT_ALGORITHM_SPACE_PERCENTS.size();

const float MAIN_SIZE_1 = 100;
const float MAIN_SIZE_2 = 200;
const float MAIN_SIZE_3 = 300;
const float MAIN_SIZE_4 = 400;
const float MAIN_SIZE_5 = 500;
const std::vector<float> MAIN_SIZES = { MAIN_SIZE_1, MAIN_SIZE_2, MAIN_SIZE_3, MAIN_SIZE_4, MAIN_SIZE_5 };
const size_t TEST_MAIN_SIZE_COUNT = MAIN_SIZES.size();
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_TEST_UNITTEST_LIST_LAYOUT_ALGORITHM_TEST_H
