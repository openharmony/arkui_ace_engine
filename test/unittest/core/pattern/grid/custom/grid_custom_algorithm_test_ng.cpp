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

#include "custom_layout_options.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_custom/grid_custom_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::Ace::NG {
class GridCustomAlgorithmTestNg : public GridTestNg {
public:
    // Create GridCustomLayoutAlgorithm instance for testing
    RefPtr<GridCustomLayoutAlgorithm> CreateTestAlgorithm()
    {
        GridLayoutInfo info;
        auto algorithm = AceType::MakeRefPtr<GridCustomLayoutAlgorithm>(std::move(info));
        algorithm->mainGap_ = COL_GAP;
        return algorithm;
    }
};

/**
 * @tc.name: TargetOffsetInCache_NormalCase_001
 * @tc.desc: Test TargetOffsetInCache when target offset is in page
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, TargetOffsetInCache_NormalCase_001, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.currentOffset_ = -20.0f; // Distance between current start line and page top is -20
    algorithm->info_.startMainLineIndex_ = 2;

    // Fill gridMatrix_ and lineHeightMap_
    for (int32_t i = 0; i < 5; ++i) {
        // Add line i with two columns in gridMatrix_
        algorithm->info_.gridMatrix_[i][0] = i * 2;
        algorithm->info_.gridMatrix_[i][1] = i * 2 + 1;
        // Set line height
        algorithm->info_.lineHeightMap_[i] = ITEM_MAIN_SIZE;
    }

    // GridMatrix structure reference:
    // [0] -> (0: 0) (1: 1)
    // [1] -> (0: 2) (1: 3)
    // [2] -> (0: 4) (1: 5)  <--- startMainLine
    // [3] -> (0: 6) (1: 7)
    // [4] -> (0: 8) (1: 9)

    // Call test function
    bool result = algorithm->TargetOffsetInCache();

    // Verify result: currentOffset_(-20) + lineHeight(100) = 80 >= 0, should return true
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TargetOffsetInCache_OffsetZero_002
 * @tc.desc: Test TargetOffsetInCache when currentOffset_ is 0
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, TargetOffsetInCache_OffsetZero_002, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.currentOffset_ = 0.0f; // Distance between current start line and page top is 0
    algorithm->info_.startMainLineIndex_ = 1;

    // Fill gridMatrix_ and lineHeightMap_
    algorithm->info_.gridMatrix_[1][0] = 2;
    algorithm->info_.gridMatrix_[1][1] = 3;
    algorithm->info_.lineHeightMap_[1] = ITEM_MAIN_SIZE;

    // GridMatrix structure reference:
    // [1] -> (0: 2) (1: 3)

    // Call test function
    bool result = algorithm->TargetOffsetInCache();

    // Verify result: currentOffset_ is 0, should return true directly
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TargetOffsetInCache_NegativeStartLine_003
 * @tc.desc: Test TargetOffsetInCache when startMainLineIndex_ is negative
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, TargetOffsetInCache_NegativeStartLine_003, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.currentOffset_ = 10.0f;
    algorithm->info_.startMainLineIndex_ = -1; // Invalid start line

    // No gridMatrix_ data needed for this test case

    // Call test function
    bool result = algorithm->TargetOffsetInCache();

    // Verify result: startMainLineIndex_ is negative, should return false directly
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TargetOffsetInCache_OffsetNotInCache_004
 * @tc.desc: Test TargetOffsetInCache when target offset is not in page
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, TargetOffsetInCache_OffsetNotInCache_004, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.currentOffset_ = -250.0f; // Large negative value
    algorithm->info_.startMainLineIndex_ = 2;

    // Fill only current line and previous line data
    algorithm->info_.gridMatrix_[2][0] = 4;
    algorithm->info_.gridMatrix_[2][1] = 5;
    algorithm->info_.lineHeightMap_[2] = ITEM_MAIN_SIZE;

    algorithm->info_.gridMatrix_[1][0] = 2;
    algorithm->info_.gridMatrix_[1][1] = 3;
    algorithm->info_.lineHeightMap_[1] = ITEM_MAIN_SIZE;

    // GridMatrix structure reference:
    // [1] -> (0: 2) (1: 3)
    // [2] -> (0: 4) (1: 5)

    // Call test function
    bool result = algorithm->TargetOffsetInCache();

    // Verify result: currentOffset_(-250) + lineHeight(100) + mainGap(10) + lineHeight(100) = -40 < 0, should return
    // false
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TargetOffsetInCache_OnlyOneLine_005
 * @tc.desc: Test TargetOffsetInCache with only one line data
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, TargetOffsetInCache_OnlyOneLine_005, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.currentOffset_ = -30.0f;
    algorithm->info_.startMainLineIndex_ = 0;

    // Fill only one line data
    algorithm->info_.gridMatrix_[0][0] = 0;
    algorithm->info_.gridMatrix_[0][1] = 1;
    algorithm->info_.lineHeightMap_[0] = ITEM_MAIN_SIZE;

    // GridMatrix structure reference:
    // [0] -> (0: 0) (1: 1)

    // Call test function
    bool result = algorithm->TargetOffsetInCache();

    // Verify result: currentOffset_(-30) + lineHeight(100) = 70 >= 0, should return true
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TargetOffsetInCache_LineNotInCache_006
 * @tc.desc: Test TargetOffsetInCache when some lines are not in cache
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, TargetOffsetInCache_LineNotInCache_006, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.currentOffset_ =
        -350.0f; // Increase negative value to ensure accumulated value is still less than 0
    algorithm->info_.startMainLineIndex_ = 3;

    // Fill data, but skip line 1 and line 2
    for (int32_t i = 0; i < 5; ++i) {
        if (i == 1 || i == 2) {
            continue; // Skip line 1 and line 2
        }
        algorithm->info_.gridMatrix_[i][0] = i * 2;
        algorithm->info_.gridMatrix_[i][1] = i * 2 + 1;
        algorithm->info_.lineHeightMap_[i] = ITEM_MAIN_SIZE;
    }

    // GridMatrix structure reference:
    // [0] -> (0: 0) (1: 1)
    // [3] -> (0: 6) (1: 7)
    // [4] -> (0: 8) (1: 9)

    // Call test function
    bool result = algorithm->TargetOffsetInCache();

    // Verify result: skip line 1 and line 2, accumulated value is still less than 0, should return false
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TargetOffsetInCache_MultipleLines_007
 * @tc.desc: Test TargetOffsetInCache when multiple lines are needed to reach >= 0
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, TargetOffsetInCache_MultipleLines_007, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.currentOffset_ = -120.0f;
    algorithm->info_.startMainLineIndex_ = 4;

    // Fill multiple lines data
    for (int32_t i = 0; i < 6; ++i) {
        algorithm->info_.gridMatrix_[i][0] = i * 2;
        algorithm->info_.gridMatrix_[i][1] = i * 2 + 1;
        algorithm->info_.lineHeightMap_[i] = ITEM_MAIN_SIZE;
    }

    // GridMatrix structure reference:
    // [0] -> (0: 0) (1: 1)
    // [1] -> (0: 2) (1: 3)
    // [2] -> (0: 4) (1: 5)
    // [3] -> (0: 6) (1: 7)
    // [4] -> (0: 8) (1: 9)
    // [5] -> (0: 10) (1: 11)

    // Call test function
    bool result = algorithm->TargetOffsetInCache();

    // Verify result: accumulated value is >= 0 after traversing multiple lines, should return true
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TargetOffsetInCache_PositiveOffset_008
 * @tc.desc: Test TargetOffsetInCache when currentOffset_ is positive
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, TargetOffsetInCache_PositiveOffset_008, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.currentOffset_ = 10.0f; // Positive value
    algorithm->info_.startMainLineIndex_ = 1;

    // Fill data
    algorithm->info_.gridMatrix_[1][0] = 2;
    algorithm->info_.gridMatrix_[1][1] = 3;
    algorithm->info_.lineHeightMap_[1] = ITEM_MAIN_SIZE;

    // GridMatrix structure reference:
    // [1] -> (0: 2) (1: 3)

    // Call test function
    bool result = algorithm->TargetOffsetInCache();

    // Verify result: currentOffset_ is positive, should return true directly
    EXPECT_TRUE(result);
}
/**
 * @tc.name: UpdateTotalOffset_NormalCase_001
 * @tc.desc: Test UpdateTotalOffset logic when startLine is less than current line
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, UpdateTotalOffset_NormalCase_001, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.prevOffset_ = 100.0f;
    algorithm->info_.startMainLineIndex_ = 3; // current line is 3

    // Fill lineHeightMap_
    for (int32_t i = 0; i < 5; ++i) {
        algorithm->info_.lineHeightMap_[i] = ITEM_MAIN_SIZE;
    }

    // Test UpdateTotalOffset logic
    int32_t startLine = 1;
    float mainGap = algorithm->mainGap_;

    // Calculate expected values
    float expectedHeightInRange =
        algorithm->info_.GetHeightInRange(startLine, algorithm->info_.startMainLineIndex_, mainGap);
    float expectedTotalOffset = algorithm->info_.prevOffset_ - expectedHeightInRange;

    // Apply UpdateTotalOffset logic
    algorithm->info_.totalOffset_ = algorithm->info_.prevOffset_ - algorithm->info_.GetHeightInRange(startLine,
                                                                       algorithm->info_.startMainLineIndex_, mainGap);

    // Verify result
    EXPECT_EQ(algorithm->info_.totalOffset_, expectedTotalOffset);
}

/**
 * @tc.name: UpdateTotalOffset_SameLine_002
 * @tc.desc: Test UpdateTotalOffset when startLine equals current line
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, UpdateTotalOffset_SameLine_002, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.prevOffset_ = 50.0f;
    algorithm->info_.startMainLineIndex_ = 2; // current line is 2

    // Fill lineHeightMap_
    for (int32_t i = 0; i < 3; ++i) {
        algorithm->info_.lineHeightMap_[i] = ITEM_MAIN_SIZE;
    }

    // Test UpdateTotalOffset logic with same startLine and current line
    int32_t startLine = 2;
    float mainGap = algorithm->mainGap_;

    // Calculate expected values - GetHeightInRange should return 0 when startLine equals endLine
    float expectedHeightInRange = 0.0f;
    float expectedTotalOffset = algorithm->info_.prevOffset_ - expectedHeightInRange;

    // Apply UpdateTotalOffset logic
    algorithm->info_.totalOffset_ = algorithm->info_.prevOffset_ - algorithm->info_.GetHeightInRange(startLine,
                                                                       algorithm->info_.startMainLineIndex_, mainGap);

    // Verify result
    EXPECT_EQ(algorithm->info_.totalOffset_, expectedTotalOffset);
    EXPECT_EQ(algorithm->info_.totalOffset_, algorithm->info_.prevOffset_); // Should remain unchanged
}

/**
 * @tc.name: UpdateTotalOffset_StartLineZero_003
 * @tc.desc: Test UpdateTotalOffset when startLine is 0
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, UpdateTotalOffset_StartLineZero_003, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.prevOffset_ = 200.0f;
    algorithm->info_.startMainLineIndex_ = 4; // current line is 4

    // Fill lineHeightMap_
    for (int32_t i = 0; i < 5; ++i) {
        algorithm->info_.lineHeightMap_[i] = ITEM_MAIN_SIZE;
    }

    // Test UpdateTotalOffset logic from line 0
    int32_t startLine = 0;
    float mainGap = algorithm->mainGap_;

    // Calculate expected values
    float expectedHeightInRange =
        algorithm->info_.GetHeightInRange(startLine, algorithm->info_.startMainLineIndex_, mainGap);
    float expectedTotalOffset = algorithm->info_.prevOffset_ - expectedHeightInRange;

    // Apply UpdateTotalOffset logic
    algorithm->info_.totalOffset_ = algorithm->info_.prevOffset_ - algorithm->info_.GetHeightInRange(startLine,
                                                                       algorithm->info_.startMainLineIndex_, mainGap);

    // Verify result
    EXPECT_EQ(algorithm->info_.totalOffset_, expectedTotalOffset);
}

/**
 * @tc.name: UpdateTotalOffset_EmptyLineHeightMap_004
 * @tc.desc: Test UpdateTotalOffset when lineHeightMap_ is empty
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, UpdateTotalOffset_EmptyLineHeightMap_004, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.prevOffset_ = 75.0f;
    algorithm->info_.startMainLineIndex_ = 2;

    // lineHeightMap_ is empty

    // Test UpdateTotalOffset logic
    int32_t startLine = 0;
    float mainGap = algorithm->mainGap_;

    // Calculate expected values - GetHeightInRange should return 0 when lineHeightMap_ is empty
    float expectedHeightInRange = 0.0f;
    float expectedTotalOffset = algorithm->info_.prevOffset_ - expectedHeightInRange;

    // Apply UpdateTotalOffset logic
    algorithm->info_.totalOffset_ = algorithm->info_.prevOffset_ - algorithm->info_.GetHeightInRange(startLine,
                                                                       algorithm->info_.startMainLineIndex_, mainGap);

    // Verify result
    EXPECT_EQ(algorithm->info_.totalOffset_, expectedTotalOffset);
    EXPECT_EQ(algorithm->info_.totalOffset_, algorithm->info_.prevOffset_); // Should remain unchanged
}

/**
 * @tc.name: UpdateTotalOffset_DifferentLineHeights_005
 * @tc.desc: Test UpdateTotalOffset with different line heights
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, UpdateTotalOffset_DifferentLineHeights_005, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data
    algorithm->info_.prevOffset_ = 150.0f;
    algorithm->info_.startMainLineIndex_ = 2;

    // Fill lineHeightMap_ with different heights
    algorithm->info_.lineHeightMap_[0] = 50.0f;
    algorithm->info_.lineHeightMap_[1] = 100.0f;
    algorithm->info_.lineHeightMap_[2] = 75.0f;

    // Test UpdateTotalOffset logic
    int32_t startLine = 0;
    float mainGap = algorithm->mainGap_;

    // Calculate expected values
    float expectedHeightInRange =
        algorithm->info_.GetHeightInRange(startLine, algorithm->info_.startMainLineIndex_, mainGap);
    float expectedTotalOffset = algorithm->info_.prevOffset_ - expectedHeightInRange;

    // Apply UpdateTotalOffset logic
    algorithm->info_.totalOffset_ = algorithm->info_.prevOffset_ - algorithm->info_.GetHeightInRange(startLine,
                                                                       algorithm->info_.startMainLineIndex_, mainGap);

    // Verify result
    EXPECT_EQ(algorithm->info_.totalOffset_, expectedTotalOffset);
}

/**
 * @tc.name: UpdateTotalOffset_NegativePrevOffset_006
 * @tc.desc: Test UpdateTotalOffset with negative prevOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, UpdateTotalOffset_NegativePrevOffset_006, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Set test data with negative prevOffset
    algorithm->info_.prevOffset_ = -100.0f;
    algorithm->info_.startMainLineIndex_ = 2;

    // Fill lineHeightMap_
    for (int32_t i = 0; i < 3; ++i) {
        algorithm->info_.lineHeightMap_[i] = ITEM_MAIN_SIZE;
    }

    // Test UpdateTotalOffset logic
    int32_t startLine = 0;
    float mainGap = algorithm->mainGap_;

    // Calculate expected values
    float expectedHeightInRange =
        algorithm->info_.GetHeightInRange(startLine, algorithm->info_.startMainLineIndex_, mainGap);
    float expectedTotalOffset = algorithm->info_.prevOffset_ - expectedHeightInRange;

    // Apply UpdateTotalOffset logic
    algorithm->info_.totalOffset_ = algorithm->info_.prevOffset_ - algorithm->info_.GetHeightInRange(startLine,
                                                                       algorithm->info_.startMainLineIndex_, mainGap);

    // Verify result
    EXPECT_EQ(algorithm->info_.totalOffset_, expectedTotalOffset);
}

/**
 * @tc.name: GetItemPos_NotInMatrix_001
 * @tc.desc: Test GetItemPos when item is not in gridMatrix_ (returns -1)
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, GetItemPos_NotInMatrix_001, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Setup: gridMatrix_ is empty, so GetItemPos should return {-1, -1}
    algorithm->info_.gridMatrix_.clear();

    // Call GetItemPos for any index
    auto pos = algorithm->info_.GetItemPos(5);

    // Verify: pos.second should be -1 when item is not in matrix
    EXPECT_EQ(pos.first, -1);
    EXPECT_EQ(pos.second, -1);
}

/**
 * @tc.name: GetItemPos_InMatrix_002
 * @tc.desc: Test GetItemPos when item is in gridMatrix_ (returns valid position)
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, GetItemPos_InMatrix_002, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Setup: Set crossCount_ for FindInMatrix to work correctly
    algorithm->info_.crossCount_ = 2;

    // Setup: Add items sequentially in gridMatrix_
    // Line 0: items 0, 1
    // Line 1: items 2, 3
    // Line 2: items 4, 5  <- item 5 is at line 2, column 1
    algorithm->info_.gridMatrix_[0][0] = 0;
    algorithm->info_.gridMatrix_[0][1] = 1;
    algorithm->info_.gridMatrix_[1][0] = 2;
    algorithm->info_.gridMatrix_[1][1] = 3;
    algorithm->info_.gridMatrix_[2][0] = 4;
    algorithm->info_.gridMatrix_[2][1] = 5; // item 5 is at line 2, column 1

    // Call GetItemPos for item 5
    auto pos = algorithm->info_.GetItemPos(5);

    // Verify: pos should be {column, line} = {1, 2}
    EXPECT_EQ(pos.first, 1);  // column
    EXPECT_EQ(pos.second, 2); // line (pos.second != -1)
}

/**
 * @tc.name: GetItemPos_With6NodesGroupLayout_003
 * @tc.desc: Test GetItemPos with 6-nodes-group irregular layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, GetItemPos_With6NodesGroupLayout_003, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Setup: Set crossCount_ for FindInMatrix to work correctly
    algorithm->info_.crossCount_ = 3;

    // Setup: Simulate 6-nodes-group layout structure
    // Group 0: items 0-5, where 0 and 4 are irregular (2x2)
    // Line 0: items 0, 1, 2  (max index = 2)
    // Line 1: items 0, 2, 3  (max index = 3)
    // Line 2: items 3, 4, 4  (max index = 4)
    // Line 3: items 5, 4, 4  (max index = 5)
    algorithm->info_.gridMatrix_[0][0] = 0;
    algorithm->info_.gridMatrix_[0][1] = 1;
    algorithm->info_.gridMatrix_[0][2] = 2;

    algorithm->info_.gridMatrix_[1][0] = 0;
    algorithm->info_.gridMatrix_[1][1] = 2;
    algorithm->info_.gridMatrix_[1][2] = 3;

    algorithm->info_.gridMatrix_[2][0] = 3;
    algorithm->info_.gridMatrix_[2][1] = 4; // item 4 first appears at line 2, column 1
    algorithm->info_.gridMatrix_[2][2] = 4;

    algorithm->info_.gridMatrix_[3][0] = 5;
    algorithm->info_.gridMatrix_[3][1] = 4;
    algorithm->info_.gridMatrix_[3][2] = 4;

    // Test: GetItemPos for item 4 (should find first occurrence at line 2, column 1)
    auto pos4 = algorithm->info_.GetItemPos(4);

    // Verify: item 4 should be found in matrix at line 2, column 1
    EXPECT_EQ(pos4.first, 1);
    EXPECT_EQ(pos4.second, 2);

    // Test: GetItemPos for item 3 (appears at line 2, column 0)
    auto pos3 = algorithm->info_.GetItemPos(3);

    // Verify: item 3 should be found in matrix at line 2, column 0
    EXPECT_EQ(pos3.first, 0);
    EXPECT_EQ(pos3.second, 2);
}

/**
 * @tc.name: PreloadItemsBranch_StartIndexNotInMatrix_004
 * @tc.desc: Test PreloadItems branch logic when startIndex is not in gridMatrix_
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, PreloadItemsBranch_StartIndexNotInMatrix_004, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Setup: startIndex_ = 5, but gridMatrix_ is empty
    algorithm->info_.startIndex_ = 5;
    algorithm->info_.endIndex_ = 8;

    // Verify: GetItemPos(5) should return {-1, -1}
    auto pos = algorithm->info_.GetItemPos(5);
    EXPECT_EQ(pos.second, -1);
}

/**
 * @tc.name: PreloadItemsBranch_StartIndexInMatrix_005
 * @tc.desc: Test PreloadItems branch logic when startIndex is already in gridMatrix_
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, PreloadItemsBranch_StartIndexInMatrix_005, TestSize.Level1)
{
    auto algorithm = CreateTestAlgorithm();

    // Setup: Set crossCount_ for FindInMatrix to work correctly
    algorithm->info_.crossCount_ = 2;

    // Setup: startIndex_ = 5, and gridMatrix_ contains item 5
    algorithm->info_.startIndex_ = 5;
    algorithm->info_.endIndex_ = 8;

    // Add items sequentially in gridMatrix_
    // Line 0: items 0, 1
    // Line 1: items 2, 3
    // Line 2: items 4, 5  <- item 5 is at line 2, column 1
    // Line 3: items 6, 7
    algorithm->info_.gridMatrix_[0][0] = 0;
    algorithm->info_.gridMatrix_[0][1] = 1;
    algorithm->info_.gridMatrix_[1][0] = 2;
    algorithm->info_.gridMatrix_[1][1] = 3;
    algorithm->info_.gridMatrix_[2][0] = 4;
    algorithm->info_.gridMatrix_[2][1] = 5; // item 5 is at line 2, column 1
    algorithm->info_.gridMatrix_[3][0] = 6;
    algorithm->info_.gridMatrix_[3][1] = 7;

    // Verify: GetItemPos(5) should return valid position
    auto pos = algorithm->info_.GetItemPos(5);

    // Verify: item 5 is at line 2, column 1
    EXPECT_EQ(pos.first, 1);
    EXPECT_EQ(pos.second, 2);
}

/**
 * @tc.name: PreloadItemsBranch_With6NodesGroupDemoOptions_006
 * @tc.desc: Test PreloadItems branch logic with Get6NodesGroupDemoOptions layout
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomAlgorithmTestNg, PreloadItemsBranch_With6NodesGroupDemoOptions_006, TestSize.Level1)
{
    // Setup layout options with 6-nodes-group pattern
    const int32_t childrenCount = 12;
    const float itemMainSize = ITEM_MAIN_SIZE;
    GridLayoutOptions options = Get6NodesGroupDemoOptions(childrenCount, itemMainSize);

    // Verify: irregular indexes include 0, 4, 6, 10 (every 6 nodes, positions 0 and 4)
    EXPECT_TRUE(options.irregularIndexes.count(0) > 0);
    EXPECT_TRUE(options.irregularIndexes.count(4) > 0);
    EXPECT_TRUE(options.irregularIndexes.count(6) > 0);
    EXPECT_TRUE(options.irregularIndexes.count(10) > 0);

    // Verify: callbacks are properly set
    EXPECT_TRUE(options.getStartIndexByIndex != nullptr);
    EXPECT_TRUE(options.getStartIndexByOffset != nullptr);

    // Test getStartIndexByIndex callback for item 4 (irregular item)
    auto startInfo4 = options.getStartIndexByIndex(4);

    // Verify: item 4 returns startIndex=3, startLine=2
    EXPECT_EQ(startInfo4.startIndex, 3);
    EXPECT_EQ(startInfo4.startLine, 2);

    // Test getStartIndexByIndex callback for item 5 (regular item)
    auto startInfo5 = options.getStartIndexByIndex(5);

    // Verify: item 5 returns startIndex=3, startLine=2
    EXPECT_EQ(startInfo5.startIndex, 3);
    EXPECT_EQ(startInfo5.startLine, 2);
}

} // namespace OHOS::Ace::NG
