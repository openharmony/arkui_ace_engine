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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_CUSTOM_CUSTOM_LAYOUT_OPTIONS_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_CUSTOM_CUSTOM_LAYOUT_OPTIONS_H

#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::Ace::NG {
/**
 * @brief Get regular demo options.
 * @param crossCount The cross count of grid.
 * @param itemMainSize The main size of grid item.
 * @return The GridLayoutOptions object.
 */
GridLayoutOptions GetRegularDemoOptions(int32_t crossCount, float itemMainSize);

/**
 * @brief Get irregular demo options.
 * @param childrenCount The children count of grid.
 * @param itemMainSize The main size of grid item.
 * @return The GridLayoutOptions object.
 */
GridLayoutOptions Get3LinesIrregularDemoOptions(int32_t childrenCount, float itemMainSize);

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_CUSTOM_CUSTOM_LAYOUT_OPTIONS_H
