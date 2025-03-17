/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"

namespace OHOS::Ace::NG {
class GridPatternTestNg : public GridTestNg {};

/**
 * @tc.name: IsPredictInRange001
 * @tc.desc: Test index is in range
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, IsPredictInRange001, TestSize.Level1)
{
    GridPattern gridPattern;
    gridPattern.info_.startIndex_ = 3;
    gridPattern.info_.endIndex_ = 7;

    EXPECT_TRUE(gridPattern.IsPredictInRange(3));  // Lower bound
    EXPECT_TRUE(gridPattern.IsPredictInRange(5));  // Mid value
    EXPECT_TRUE(gridPattern.IsPredictInRange(7));  // Upper bound
    EXPECT_FALSE(gridPattern.IsPredictInRange(2)); // Below lower bound
    EXPECT_FALSE(gridPattern.IsPredictInRange(8)); // Above upper bound
}

/**
 * @tc.name: IsPredictInRange002
 * @tc.desc: Test Single-element range (start == end)
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, IsPredictInRange002, TestSize.Level1)
{
    GridPattern gridPattern;
    gridPattern.info_.startIndex_ = 5;
    gridPattern.info_.endIndex_ = 5;

    EXPECT_TRUE(gridPattern.IsPredictInRange(5));  // Only valid value
    EXPECT_FALSE(gridPattern.IsPredictInRange(4)); // Below
    EXPECT_FALSE(gridPattern.IsPredictInRange(6)); // Above
}

/**
 * @tc.name: IsPredictInRange003
 * @tc.desc: Test Invalid range (start > end, should always return false)
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, IsPredictInRange003, TestSize.Level1)
{
    GridPattern gridPattern;
    gridPattern.info_.startIndex_ = 7;
    gridPattern.info_.endIndex_ = 3;

    EXPECT_FALSE(gridPattern.IsPredictInRange(3)); // Original upper bound
    EXPECT_FALSE(gridPattern.IsPredictInRange(5)); // Original mid value
    EXPECT_FALSE(gridPattern.IsPredictInRange(7)); // Original lower bound
    EXPECT_FALSE(gridPattern.IsPredictInRange(2)); // Below original range
    EXPECT_FALSE(gridPattern.IsPredictInRange(8)); // Above original range
}

/**
 * @tc.name: IsPredictInRange004
 * @tc.desc: Test Negative range
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, IsPredictInRange004, TestSize.Level1)
{
    GridPattern gridPattern;
    gridPattern.info_.startIndex_ = -5;
    gridPattern.info_.endIndex_ = -1;

    EXPECT_TRUE(gridPattern.IsPredictInRange(-5));  // Lower bound
    EXPECT_TRUE(gridPattern.IsPredictInRange(-3));  // Mid value
    EXPECT_TRUE(gridPattern.IsPredictInRange(-1));  // Upper bound
    EXPECT_FALSE(gridPattern.IsPredictInRange(-6)); // Below lower bound
    EXPECT_FALSE(gridPattern.IsPredictInRange(0));  // Above upper bound
}

/**
 * @tc.name: IsPredictInRange005
 * @tc.desc: Test Range crossing zero
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, IsPredictInRange005, TestSize.Level1)
{
    GridPattern gridPattern;
    gridPattern.info_.startIndex_ = -2;
    gridPattern.info_.endIndex_ = 2;

    EXPECT_TRUE(gridPattern.IsPredictInRange(-2));  // Lower bound
    EXPECT_TRUE(gridPattern.IsPredictInRange(0));   // Mid value (zero)
    EXPECT_TRUE(gridPattern.IsPredictInRange(2));   // Upper bound
    EXPECT_FALSE(gridPattern.IsPredictInRange(-3)); // Below lower bound
    EXPECT_FALSE(gridPattern.IsPredictInRange(3));  // Above upper bound
}

/**
 * @tc.name: IsPredictInRange006
 * @tc.desc: Test Edge case testing (int32_t min/max values)
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, IsPredictInRange006, TestSize.Level1)
{
    GridPattern gridPattern;
    gridPattern.info_.startIndex_ = INT32_MIN;
    gridPattern.info_.endIndex_ = INT32_MAX;

    EXPECT_TRUE(gridPattern.IsPredictInRange(INT32_MIN)); // Lower bound
    EXPECT_TRUE(gridPattern.IsPredictInRange(0));         // Mid value
    EXPECT_TRUE(gridPattern.IsPredictInRange(INT32_MAX)); // Upper bound
    // Note: Cannot generate values smaller than INT32_MIN or larger than INT32_MAX
}

} // namespace OHOS::Ace::NG
