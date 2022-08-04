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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_TEST_UNITTEST_LIST_LAYOUT_PROPERTY_TEST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_TEST_UNITTEST_LIST_LAYOUT_PROPERTY_TEST_H

#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_layout_property.h"

namespace OHOS::Ace::NG {

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
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_TEST_UNITTEST_LIST_LAYOUT_PROPERTY_TEST_H
