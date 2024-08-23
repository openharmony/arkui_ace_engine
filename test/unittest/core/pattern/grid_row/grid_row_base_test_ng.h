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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_ROW_BASE_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_ROW_BASE_TEST_NG_H
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/grid_col/grid_col_layout_algorithm.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_pattern.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_property.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"
#include "core/components_ng/pattern/grid_row/grid_row_event_hub.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_algorithm.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_pattern.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_property.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
class GridRowBaseTestNG : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateGridRow(const std::function<void(GridRowModelNG)>& callback);
    RefPtr<FrameNode> CreateGridCol(const std::function<void(GridColModelNG)>& callback);
};
}

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_GRID_ROW_BASE_TEST_NG_H