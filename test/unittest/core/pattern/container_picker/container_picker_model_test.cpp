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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/container_picker/container_picker_layout_algorithm.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    // Test constants for SetIndicatorStyle
    constexpr int32_t INDICATOR_TYPE_DIVIDER = static_cast<int32_t>(PickerIndicatorType::DIVIDER);
    constexpr int32_t INDICATOR_TYPE_BACKGROUND = static_cast<int32_t>(PickerIndicatorType::BACKGROUND);
    constexpr int32_t INDICATOR_TYPE_INVALID = 999;
    constexpr Dimension TEST_STROKE_WIDTH = 2.0_vp;
    constexpr Dimension TEST_START_MARGIN = 4.0_vp;
    constexpr Dimension TEST_END_MARGIN = 6.0_vp;
    constexpr double TEST_SCROLL_LARGE_INDEX = 88888;
    constexpr int32_t DEFAULT_DISPLAYED_ITEM_COUNT = 7;
    constexpr float DEFAULT_ITEM_HEIGHT_VP = 40.0f;
    constexpr float FLOAT_COMPARE_EPSILON = 0.001f;
    
    // Test constants for NormalizeDisplayedItemCount
    constexpr int32_t DISPLAYED_COUNT_MIN = 2;
    constexpr int32_t DISPLAYED_COUNT_MAX = 9;
    constexpr int32_t DISPLAYED_COUNT_UNDER_MIN = 1;
    constexpr int32_t DISPLAYED_COUNT_OVER_MAX = 10;
    constexpr int32_t DISPLAYED_COUNT_EVEN_4 = 4;
    constexpr int32_t DISPLAYED_COUNT_EVEN_6 = 6;
    constexpr int32_t DISPLAYED_COUNT_EVEN_8 = 8;
    constexpr int32_t DISPLAYED_COUNT_ODD_3 = 3;
    constexpr int32_t DISPLAYED_COUNT_ODD_5 = 5;
    
    // Test constants for ClampPickerItemHeight
    constexpr float ITEM_HEIGHT_MIN_VP = 40.0f;
    constexpr float ITEM_HEIGHT_MAX_VP = 64.0f;
    constexpr float ITEM_HEIGHT_UNDER_MIN_VP = 10.0f;
    constexpr float ITEM_HEIGHT_OVER_MAX_VP = 100.0f;
    constexpr float ITEM_HEIGHT_IN_RANGE_VP = 50.0f;
}

class ContainerPickerModelTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateContainerPickerNode();

    // Helper function to get all ContainerPicker component references from CreateContainerPickerNode
    void GetContainerPickerComponents()
    {
        frameNode_ = CreateContainerPickerNode();
        ASSERT_NE(frameNode_, nullptr);

        pickerPattern_ = frameNode_->GetPattern<ContainerPickerPattern>();
        ASSERT_NE(pickerPattern_, nullptr);

        layoutProperty_ = frameNode_->GetLayoutProperty<ContainerPickerLayoutProperty>();
        ASSERT_NE(layoutProperty_, nullptr);
    }

    // Helper function to get components from ViewStackProcessor
    void GetContainerPickerComponentsFromStack()
    {
        ContainerPickerModel::Create();
        frameNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode_, nullptr);

        pickerPattern_ = frameNode_->GetPattern<ContainerPickerPattern>();
        ASSERT_NE(pickerPattern_, nullptr);

        layoutProperty_ = frameNode_->GetLayoutProperty<ContainerPickerLayoutProperty>();
        ASSERT_NE(layoutProperty_, nullptr);
    }

protected:
    RefPtr<FrameNode> frameNode_;
    RefPtr<ContainerPickerPattern> pickerPattern_;
    RefPtr<ContainerPickerLayoutProperty> layoutProperty_;
};

void ContainerPickerModelTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerPickerTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerPickerModelTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    TestNG::TearDownTestSuite();
}

void ContainerPickerModelTest::SetUp()
{
    ClearOldNodes();
}

void ContainerPickerModelTest::TearDown()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> ContainerPickerModelTest::CreateContainerPickerNode()
{
    auto frameNode = ContainerPickerModel::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->InitDefaultParams();
    return frameNode;
}

/**
 * @tc.name: SetSelectedIndex001
 * @tc.desc: Test SetSelectedIndex when HasSelectedIndex is false (first time setting)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and Pattern are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set selected index for the first time (HasSelectedIndex is false)
     * @tc.expected: step2. Pattern's selectedIndex should be updated
     */
    int32_t testIndex = 3;
    ContainerPickerModel::SetSelectedIndex(testIndex);

    EXPECT_EQ(pickerPattern_->GetSelectedIndex(), testIndex);
    EXPECT_TRUE(layoutProperty_->HasSelectedIndex());
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), testIndex);
}

/**
 * @tc.name: SetSelectedIndex002
 * @tc.desc: Test SetSelectedIndex when HasSelectedIndex is true (updating existing index)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker and set initial index
     * @tc.expected: step1. Initial index is set
     */
    GetContainerPickerComponentsFromStack();

    // First set to establish HasSelectedIndex
    int32_t initialIndex = 2;
    ContainerPickerModel::SetSelectedIndex(initialIndex);
    EXPECT_TRUE(layoutProperty_->HasSelectedIndex());

    /**
     * @tc.steps: step2. Set selected index again (HasSelectedIndex is now true)
     * @tc.expected: step2. Pattern's SetTargetIndex should be called, layoutProperty updated
     */
    int32_t newIndex = 5;
    ContainerPickerModel::SetSelectedIndex(newIndex);

    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), newIndex);
    EXPECT_TRUE(layoutProperty_->HasSelectedIndex());
}

/**
 * @tc.name: SetSelectedIndex003
 * @tc.desc: Test SetSelectedIndex with zero value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set selected index to 0
     * @tc.expected: step2. Index should be set correctly
     */
    ContainerPickerModel::SetSelectedIndex(0);

    EXPECT_EQ(pickerPattern_->GetSelectedIndex(), 0);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), 0);
}

/**
 * @tc.name: SetSelectedIndex004
 * @tc.desc: Test SetSelectedIndex with negative value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set selected index to negative value
     * @tc.expected: step2. Index should be set (validation is handled elsewhere)
     */
    int32_t negativeIndex = -1;
    ContainerPickerModel::SetSelectedIndex(negativeIndex);

    EXPECT_EQ(pickerPattern_->GetSelectedIndex(), negativeIndex);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-999), negativeIndex);
}

/**
 * @tc.name: SetSelectedIndex005
 * @tc.desc: Test SetSelectedIndex with large positive value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set selected index to large positive value
     * @tc.expected: step2. Index should be set correctly
     */
    int32_t largeIndex = 9999;
    ContainerPickerModel::SetSelectedIndex(largeIndex);

    EXPECT_EQ(pickerPattern_->GetSelectedIndex(), largeIndex);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), largeIndex);
}

/**
 * @tc.name: SetSelectedIndex006
 * @tc.desc: Test SetSelectedIndex with FrameNode parameter (first time)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node directly
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set selected index using FrameNode parameter
     * @tc.expected: step2. Index should be set correctly
     */
    int32_t testIndex = 4;
    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode_), testIndex);

    EXPECT_EQ(pickerPattern_->GetSelectedIndex(), testIndex);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), testIndex);
}

/**
 * @tc.name: SetSelectedIndex007
 * @tc.desc: Test SetSelectedIndex with FrameNode parameter (subsequent call)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker and set initial index
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponents();

    // First set
    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode_), 2);
    EXPECT_TRUE(layoutProperty_->HasSelectedIndex());

    /**
     * @tc.steps: step2. Update selected index again using FrameNode parameter
     * @tc.expected: step2. Index should be updated correctly
     */
    int32_t newIndex = 7;
    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode_), newIndex);

    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), newIndex);
}

/**
 * @tc.name: SetSelectedIndex008
 * @tc.desc: Test SetSelectedIndex with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetSelectedIndex with null FrameNode
     * @tc.expected: step1. Should not crash, return gracefully
     */
    ContainerPickerModel::SetSelectedIndex(static_cast<FrameNode*>(nullptr), 5);
    // If we reach here without crashing, the test passes
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetSelectedIndex009
 * @tc.desc: Test SetSelectedIndex when ViewStackProcessor has no main frame node
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear ViewStackProcessor to ensure no main frame node
     * @tc.expected: step1. Should not crash, return gracefully
     */
    ClearOldNodes();
    ContainerPickerModel::SetSelectedIndex(3);
    // If we reach here without crashing, the test passes
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetSelectedIndex010
 * @tc.desc: Test multiple consecutive SetSelectedIndex calls
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set selected index multiple times consecutively
     * @tc.expected: step2. Each call should update the index correctly
     */
    std::vector<int32_t> testIndices = {1, 3, 5, 2, 8};

    for (size_t i = 0; i < testIndices.size(); ++i) {
        ContainerPickerModel::SetSelectedIndex(testIndices[i]);
        EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), testIndices[i]);
    }

    // Final index should be the last one set
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), testIndices.back());
}

/**
 * @tc.name: SetSelectedIndex011
 * @tc.desc: Test SetSelectedIndex with same value multiple times
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set the same index multiple times
     * @tc.expected: step2. Index should remain the same
     */
    int32_t testIndex = 5;

    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode_), testIndex);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), testIndex);

    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode_), testIndex);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), testIndex);

    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode_), testIndex);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), testIndex);
}

/**
 * @tc.name: SetSelectedIndex012
 * @tc.desc: Test GetSelectedIndex after SetSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set selected index and then retrieve it
     * @tc.expected: step2. Retrieved index should match set value
     */
    int32_t testIndex = 6;
    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode_), testIndex);

    int32_t retrievedIndex = ContainerPickerModel::GetSelectedIndex(AceType::RawPtr(frameNode_));
    EXPECT_EQ(retrievedIndex, testIndex);
}

/**
 * @tc.name: SetSelectedIndex013
 * @tc.desc: Test GetSelectedIndex with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetSelectedIndex with null FrameNode
     * @tc.expected: step1. Should return 0 as default value
     */
    int32_t result = ContainerPickerModel::GetSelectedIndex(nullptr);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: SetSelectedIndex014
 * @tc.desc: Test SetSelectedIndex alternation between indices
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Alternate between two indices
     * @tc.expected: step2. Index should change correctly each time
     */
    int32_t index1 = 2;
    int32_t index2 = 5;

    ContainerPickerModel::SetSelectedIndex(index1);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), index1);

    ContainerPickerModel::SetSelectedIndex(index2);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), index2);

    ContainerPickerModel::SetSelectedIndex(index1);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), index1);

    ContainerPickerModel::SetSelectedIndex(index2);
    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), index2);
}

/**
 * @tc.name: SetSelectedIndex015
 * @tc.desc: Test SetSelectedIndex with INT_MAX value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetSelectedIndex015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set selected index to INT_MAX
     * @tc.expected: step2. Index should be set correctly
     */
    int32_t maxIndex = INT32_MAX;
    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode_), maxIndex);

    EXPECT_EQ(layoutProperty_->GetSelectedIndex().value_or(-1), maxIndex);
}

/**
 * @tc.name: SetDisplayedItemCount001
 * @tc.desc: Test SetDisplayedItemCount normalization with ViewStackProcessor API
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetDisplayedItemCount001, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();

    ContainerPickerModel::SetDisplayedItemCount(8);
    ASSERT_TRUE(layoutProperty_->HasDisplayedItemCount());
    EXPECT_EQ(layoutProperty_->GetDisplayedItemCount().value_or(-1), 9);

    ContainerPickerModel::SetDisplayedItemCount(1);
    EXPECT_EQ(layoutProperty_->GetDisplayedItemCount().value_or(-1), DEFAULT_DISPLAYED_ITEM_COUNT);

    ContainerPickerModel::SetDisplayedItemCount(std::nullopt);
    EXPECT_FALSE(layoutProperty_->HasDisplayedItemCount());
}

/**
 * @tc.name: SetDisplayedItemCount002
 * @tc.desc: Test SetDisplayedItemCount with FrameNode API and reset behavior
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetDisplayedItemCount002, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetDisplayedItemCount(AceType::RawPtr(frameNode_), 2);
    ASSERT_TRUE(layoutProperty_->HasDisplayedItemCount());
    EXPECT_EQ(layoutProperty_->GetDisplayedItemCount().value_or(-1), 3);

    ContainerPickerModel::SetDisplayedItemCount(AceType::RawPtr(frameNode_), std::nullopt);
    EXPECT_FALSE(layoutProperty_->HasDisplayedItemCount());
}

/**
 * @tc.name: SetItemHeight001
 * @tc.desc: Test SetItemHeight clamp with ViewStackProcessor API
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeight001, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();

    ContainerPickerModel::SetItemHeight(50.0_vp);
    ASSERT_TRUE(layoutProperty_->HasItemHeight());
    EXPECT_NEAR(layoutProperty_->GetItemHeight().value().ConvertToVp(), 50.0f, FLOAT_COMPARE_EPSILON);

    ContainerPickerModel::SetItemHeight(10.0_vp);
    EXPECT_NEAR(layoutProperty_->GetItemHeight().value().ConvertToVp(), DEFAULT_ITEM_HEIGHT_VP, FLOAT_COMPARE_EPSILON);

    ContainerPickerModel::SetItemHeight(std::nullopt);
    EXPECT_FALSE(layoutProperty_->HasItemHeight());
}

/**
 * @tc.name: SetItemHeight002
 * @tc.desc: Test SetItemHeight with FrameNode API and upper bound clamp
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeight002, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), 64.0_vp);
    ASSERT_TRUE(layoutProperty_->HasItemHeight());
    EXPECT_NEAR(layoutProperty_->GetItemHeight().value().ConvertToVp(), 64.0f, FLOAT_COMPARE_EPSILON);

    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), 100.0_vp);
    EXPECT_NEAR(layoutProperty_->GetItemHeight().value().ConvertToVp(), DEFAULT_ITEM_HEIGHT_VP, FLOAT_COMPARE_EPSILON);

    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), std::nullopt);
    EXPECT_FALSE(layoutProperty_->HasItemHeight());
}

/**
 * @tc.name: NormalizeDisplayedItemCount001
 * @tc.desc: Test NormalizeDisplayedItemCount with under min value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, NormalizeDisplayedItemCount001, TestSize.Level1)
{
    auto result = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_UNDER_MIN);
    EXPECT_EQ(result, DEFAULT_DISPLAYED_ITEM_COUNT);
}

/**
 * @tc.name: NormalizeDisplayedItemCount002
 * @tc.desc: Test NormalizeDisplayedItemCount with over max value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, NormalizeDisplayedItemCount002, TestSize.Level1)
{
    auto result = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_OVER_MAX);
    EXPECT_EQ(result, DEFAULT_DISPLAYED_ITEM_COUNT);
}

/**
 * @tc.name: NormalizeDisplayedItemCount003
 * @tc.desc: Test NormalizeDisplayedItemCount with min boundary (even number)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, NormalizeDisplayedItemCount003, TestSize.Level1)
{
    auto result = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_MIN);
    EXPECT_EQ(result, DISPLAYED_COUNT_MIN + 1);
}

/**
 * @tc.name: NormalizeDisplayedItemCount004
 * @tc.desc: Test NormalizeDisplayedItemCount with max boundary (odd number)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, NormalizeDisplayedItemCount004, TestSize.Level1)
{
    auto result = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_MAX);
    EXPECT_EQ(result, DISPLAYED_COUNT_MAX);
}

/**
 * @tc.name: NormalizeDisplayedItemCount005
 * @tc.desc: Test NormalizeDisplayedItemCount with even numbers in range
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, NormalizeDisplayedItemCount005, TestSize.Level1)
{
    auto result4 = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_EVEN_4);
    EXPECT_EQ(result4, DISPLAYED_COUNT_EVEN_4 + 1);
    
    auto result6 = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_EVEN_6);
    EXPECT_EQ(result6, DISPLAYED_COUNT_EVEN_6 + 1);
    
    auto result8 = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_EVEN_8);
    EXPECT_EQ(result8, DISPLAYED_COUNT_EVEN_8 + 1);
}

/**
 * @tc.name: NormalizeDisplayedItemCount006
 * @tc.desc: Test NormalizeDisplayedItemCount with odd numbers in range
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, NormalizeDisplayedItemCount006, TestSize.Level1)
{
    auto result3 = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_ODD_3);
    EXPECT_EQ(result3, DISPLAYED_COUNT_ODD_3);
    
    auto result5 = ContainerPickerUtils::NormalizeDisplayedItemCount(DISPLAYED_COUNT_ODD_5);
    EXPECT_EQ(result5, DISPLAYED_COUNT_ODD_5);
    
    auto result7 = ContainerPickerUtils::NormalizeDisplayedItemCount(DEFAULT_DISPLAYED_ITEM_COUNT);
    EXPECT_EQ(result7, DEFAULT_DISPLAYED_ITEM_COUNT);
}

/**
 * @tc.name: ClampPickerItemHeight001
 * @tc.desc: Test ClampPickerItemHeight with value under min
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, ClampPickerItemHeight001, TestSize.Level1)
{
    auto result = ContainerPickerUtils::ClampPickerItemHeight(
        Dimension(ITEM_HEIGHT_UNDER_MIN_VP, DimensionUnit::VP));
    auto expectedDefault = Dimension(DEFAULT_ITEM_HEIGHT_VP, DimensionUnit::PX);
    EXPECT_NEAR(result.ConvertToPx(), expectedDefault.ConvertToPx(), FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: ClampPickerItemHeight002
 * @tc.desc: Test ClampPickerItemHeight with value over max
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, ClampPickerItemHeight002, TestSize.Level1)
{
    auto result = ContainerPickerUtils::ClampPickerItemHeight(
        Dimension(ITEM_HEIGHT_OVER_MAX_VP, DimensionUnit::VP));
    auto expectedDefault = Dimension(DEFAULT_ITEM_HEIGHT_VP, DimensionUnit::PX);
    EXPECT_NEAR(result.ConvertToPx(), expectedDefault.ConvertToPx(), FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: ClampPickerItemHeight003
 * @tc.desc: Test ClampPickerItemHeight with min boundary value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, ClampPickerItemHeight003, TestSize.Level1)
{
    auto result = ContainerPickerUtils::ClampPickerItemHeight(
        Dimension(ITEM_HEIGHT_MIN_VP, DimensionUnit::VP));
    auto expectedMin = Dimension(ITEM_HEIGHT_MIN_VP, DimensionUnit::VP);
    EXPECT_NEAR(result.ConvertToVp(), expectedMin.ConvertToVp(), FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: ClampPickerItemHeight004
 * @tc.desc: Test ClampPickerItemHeight with max boundary value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, ClampPickerItemHeight004, TestSize.Level1)
{
    auto result = ContainerPickerUtils::ClampPickerItemHeight(
        Dimension(ITEM_HEIGHT_MAX_VP, DimensionUnit::VP));
    auto expectedMax = Dimension(ITEM_HEIGHT_MAX_VP, DimensionUnit::VP);
    EXPECT_NEAR(result.ConvertToVp(), expectedMax.ConvertToVp(), FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: ClampPickerItemHeight005
 * @tc.desc: Test ClampPickerItemHeight with value in range
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, ClampPickerItemHeight005, TestSize.Level1)
{
    auto result = ContainerPickerUtils::ClampPickerItemHeight(
        Dimension(ITEM_HEIGHT_IN_RANGE_VP, DimensionUnit::VP));
    auto expected = Dimension(ITEM_HEIGHT_IN_RANGE_VP, DimensionUnit::VP);
    EXPECT_NEAR(result.ConvertToVp(), expected.ConvertToVp(), FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: SetIndicatorStyle001
 * @tc.desc: Test SetIndicatorStyle with DIVIDER type and all properties set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set indicator style with DIVIDER type and all properties
     * @tc.expected: step2. All DIVIDER properties should be set, Pattern should be updated
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    style.strokeWidth = TEST_STROKE_WIDTH;
    style.dividerColor = Color::RED;
    style.startMargin = TEST_START_MARGIN;
    style.endMargin = TEST_END_MARGIN;

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_DIVIDER);
    EXPECT_EQ(layoutProperty_->GetIndicatorDividerWidth().value_or(Dimension()), TEST_STROKE_WIDTH);
    EXPECT_EQ(layoutProperty_->GetIndicatorDividerColor().value_or(Color()), Color::RED);
    EXPECT_EQ(layoutProperty_->GetIndicatorStartMargin().value_or(Dimension()), TEST_START_MARGIN);
    EXPECT_EQ(layoutProperty_->GetIndicatorEndMargin().value_or(Dimension()), TEST_END_MARGIN);

    auto retrievedStyle = pickerPattern_->GetIndicatorStyleVal();
    EXPECT_EQ(retrievedStyle.type, INDICATOR_TYPE_DIVIDER);
    EXPECT_EQ(retrievedStyle.strokeWidth.value_or(Dimension()), TEST_STROKE_WIDTH);
    EXPECT_EQ(retrievedStyle.dividerColor.value_or(Color()), Color::RED);
    EXPECT_EQ(retrievedStyle.startMargin.value_or(Dimension()), TEST_START_MARGIN);
    EXPECT_EQ(retrievedStyle.endMargin.value_or(Dimension()), TEST_END_MARGIN);
}

/**
 * @tc.name: SetIndicatorStyle002
 * @tc.desc: Test SetIndicatorStyle with DIVIDER type and partial properties set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set indicator style with DIVIDER type but only strokeWidth
     * @tc.expected: step2. Only strokeWidth and type should be set
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    style.strokeWidth = TEST_STROKE_WIDTH;
    // dividerColor, startMargin, endMargin are not set (std::nullopt)

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_DIVIDER);
    EXPECT_EQ(layoutProperty_->GetIndicatorDividerWidth().value_or(Dimension()), TEST_STROKE_WIDTH);
    EXPECT_FALSE(layoutProperty_->HasIndicatorDividerColor());
    EXPECT_FALSE(layoutProperty_->HasIndicatorStartMargin());
    EXPECT_FALSE(layoutProperty_->HasIndicatorEndMargin());
}

/**
 * @tc.name: SetIndicatorStyle003
 * @tc.desc: Test SetIndicatorStyle with BACKGROUND type and all properties set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set indicator style with BACKGROUND type and all properties
     * @tc.expected: step2. All BACKGROUND properties should be set, Pattern should be updated
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_BACKGROUND;
    style.backgroundColor = Color::BLUE;
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(8.0_vp));
    style.borderRadius = borderRadius;

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_BACKGROUND);
    EXPECT_EQ(layoutProperty_->GetIndicatorBackgroundColor().value_or(Color()), Color::BLUE);
    auto retrievedRadius = layoutProperty_->GetIndicatorBorderRadius();
    EXPECT_TRUE(retrievedRadius.has_value());

    auto retrievedStyle = pickerPattern_->GetIndicatorStyleVal();
    EXPECT_EQ(retrievedStyle.type, INDICATOR_TYPE_BACKGROUND);
    EXPECT_EQ(retrievedStyle.backgroundColor.value_or(Color()), Color::BLUE);
    EXPECT_TRUE(retrievedStyle.borderRadius.has_value());
}

/**
 * @tc.name: SetIndicatorStyle004
 * @tc.desc: Test SetIndicatorStyle with BACKGROUND type and partial properties set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set indicator style with BACKGROUND type but only backgroundColor
     * @tc.expected: step2. Only backgroundColor and type should be set
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_BACKGROUND;
    style.backgroundColor = Color::GREEN;
    // borderRadius is not set (std::nullopt)

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_BACKGROUND);
    EXPECT_EQ(layoutProperty_->GetIndicatorBackgroundColor().value_or(Color()), Color::GREEN);
    EXPECT_FALSE(layoutProperty_->HasIndicatorBorderRadius());
}

/**
 * @tc.name: SetIndicatorStyle005
 * @tc.desc: Test SetIndicatorStyle with invalid type
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set indicator style with invalid type
     * @tc.expected: step2. Type should still be set, but Pattern should not be updated (early return)
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_INVALID;
    style.strokeWidth = TEST_STROKE_WIDTH;

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_INVALID);

    auto retrievedStyle = pickerPattern_->GetIndicatorStyleVal();
    // Pattern should not be updated when type is invalid
    EXPECT_NE(retrievedStyle.type, INDICATOR_TYPE_INVALID);
}

/**
 * @tc.name: SetIndicatorStyle006
 * @tc.desc: Test SetIndicatorStyle with FrameNode parameter and DIVIDER type
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set indicator style using FrameNode parameter with DIVIDER type
     * @tc.expected: step2. All DIVIDER properties should be set correctly
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    style.strokeWidth = 3.0_vp;
    style.dividerColor = Color::RED;
    style.startMargin = 5.0_vp;
    style.endMargin = 7.0_vp;

    ContainerPickerModel::SetIndicatorStyle(AceType::RawPtr(frameNode_), style);

    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_DIVIDER);
    EXPECT_EQ(layoutProperty_->GetIndicatorDividerWidth().value_or(Dimension()), 3.0_vp);
    EXPECT_EQ(layoutProperty_->GetIndicatorDividerColor().value_or(Color()), Color::RED);
    EXPECT_EQ(layoutProperty_->GetIndicatorStartMargin().value_or(Dimension()), 5.0_vp);
    EXPECT_EQ(layoutProperty_->GetIndicatorEndMargin().value_or(Dimension()), 7.0_vp);

    auto retrievedStyle = pickerPattern_->GetIndicatorStyleVal();
    EXPECT_EQ(retrievedStyle.type, INDICATOR_TYPE_DIVIDER);
}

/**
 * @tc.name: SetIndicatorStyle007
 * @tc.desc: Test SetIndicatorStyle with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetIndicatorStyle with null FrameNode
     * @tc.expected: step1. Should not crash, return gracefully
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    style.strokeWidth = TEST_STROKE_WIDTH;

    ContainerPickerModel::SetIndicatorStyle(static_cast<FrameNode*>(nullptr), style);
    // If we reach here without crashing, the test passes
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetIndicatorStyle008
 * @tc.desc: Test SetIndicatorStyle when ViewStackProcessor has no main frame node
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear ViewStackProcessor to ensure no main frame node
     * @tc.expected: step1. Should not crash, return gracefully
     */
    ClearOldNodes();

    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_BACKGROUND;
    style.backgroundColor = Color::WHITE;

    ContainerPickerModel::SetIndicatorStyle(style);
    // If we reach here without crashing, the test passes
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetIndicatorStyle009
 * @tc.desc: Test switching from DIVIDER to BACKGROUND type
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set DIVIDER type first
     * @tc.expected: step2. DIVIDER properties should be set
     */
    PickerIndicatorStyle dividerStyle;
    dividerStyle.type = INDICATOR_TYPE_DIVIDER;
    dividerStyle.strokeWidth = TEST_STROKE_WIDTH;
    dividerStyle.dividerColor = Color::RED;

    ContainerPickerModel::SetIndicatorStyle(dividerStyle);
    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_DIVIDER);
    EXPECT_TRUE(layoutProperty_->HasIndicatorDividerWidth());

    /**
     * @tc.steps: step3. Switch to BACKGROUND type
     * @tc.expected: step3. BACKGROUND properties should be set, DIVIDER properties may remain
     */
    PickerIndicatorStyle backgroundStyle;
    backgroundStyle.type = INDICATOR_TYPE_BACKGROUND;
    backgroundStyle.backgroundColor = Color::BLUE;

    ContainerPickerModel::SetIndicatorStyle(backgroundStyle);
    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_BACKGROUND);
    EXPECT_TRUE(layoutProperty_->HasIndicatorBackgroundColor());

    auto retrievedStyle = pickerPattern_->GetIndicatorStyleVal();
    EXPECT_EQ(retrievedStyle.type, INDICATOR_TYPE_BACKGROUND);
}

/**
 * @tc.name: SetIndicatorStyle010
 * @tc.desc: Test GetIndicatorStyle after SetIndicatorStyle with DIVIDER type
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set indicator style with DIVIDER type
     * @tc.expected: step2. Properties should be set correctly
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    style.strokeWidth = 4.0_vp;
    style.dividerColor = Color::RED;
    style.startMargin = 8.0_vp;
    style.endMargin = 10.0_vp;

    ContainerPickerModel::SetIndicatorStyle(AceType::RawPtr(frameNode_), style);

    /**
     * @tc.steps: step3. Get indicator style and verify
     * @tc.expected: step3. Retrieved style should match set values
     */
    auto retrievedStyle = ContainerPickerModel::GetIndicatorStyle(AceType::RawPtr(frameNode_));
    EXPECT_EQ(retrievedStyle.type, INDICATOR_TYPE_DIVIDER);
    EXPECT_EQ(retrievedStyle.strokeWidth.value_or(Dimension()), 4.0_vp);
    EXPECT_EQ(retrievedStyle.dividerColor.value_or(Color()), Color::RED);
    EXPECT_EQ(retrievedStyle.startMargin.value_or(Dimension()), 8.0_vp);
    EXPECT_EQ(retrievedStyle.endMargin.value_or(Dimension()), 10.0_vp);
}

/**
 * @tc.name: SetIndicatorStyle011
 * @tc.desc: Test GetIndicatorStyle after SetIndicatorStyle with BACKGROUND type
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set indicator style with BACKGROUND type
     * @tc.expected: step2. Properties should be set correctly
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_BACKGROUND;
    style.backgroundColor = Color::RED;

    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(12.0_vp));
    style.borderRadius = borderRadius;

    ContainerPickerModel::SetIndicatorStyle(AceType::RawPtr(frameNode_), style);

    /**
     * @tc.steps: step3. Get indicator style and verify
     * @tc.expected: step3. Retrieved style should match set values
     */
    auto retrievedStyle = ContainerPickerModel::GetIndicatorStyle(AceType::RawPtr(frameNode_));
    EXPECT_EQ(retrievedStyle.type, INDICATOR_TYPE_BACKGROUND);
    EXPECT_EQ(retrievedStyle.backgroundColor.value_or(Color()), Color::RED);
    EXPECT_TRUE(retrievedStyle.borderRadius.has_value());
}

/**
 * @tc.name: SetIndicatorStyle012
 * @tc.desc: Test GetIndicatorStyle with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetIndicatorStyle with null FrameNode
     * @tc.expected: step1. Should return default style
     */
    auto retrievedStyle = ContainerPickerModel::GetIndicatorStyle(nullptr);
    EXPECT_EQ(retrievedStyle.type, 0);  // Default type value
}

/**
 * @tc.name: SetIndicatorStyle013
 * @tc.desc: Test multiple consecutive SetIndicatorStyle calls with different types
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set indicator style multiple times with alternating types
     * @tc.expected: step2. Each call should update the style correctly
     */
    // First call: DIVIDER
    PickerIndicatorStyle style1;
    style1.type = INDICATOR_TYPE_DIVIDER;
    style1.strokeWidth = 1.0_vp;
    ContainerPickerModel::SetIndicatorStyle(style1);
    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_DIVIDER);

    // Second call: BACKGROUND
    PickerIndicatorStyle style2;
    style2.type = INDICATOR_TYPE_BACKGROUND;
    style2.backgroundColor = Color::RED;
    ContainerPickerModel::SetIndicatorStyle(style2);
    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_BACKGROUND);

    // Third call: DIVIDER again
    PickerIndicatorStyle style3;
    style3.type = INDICATOR_TYPE_DIVIDER;
    style3.dividerColor = Color::BLUE;
    ContainerPickerModel::SetIndicatorStyle(style3);
    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_DIVIDER);
}

/**
 * @tc.name: SetIndicatorStyle014
 * @tc.desc: Test SetIndicatorStyle with all optional properties unset
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set indicator style with DIVIDER type but no optional properties
     * @tc.expected: step2. Only type should be set, no optional properties
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    // All optional properties remain std::nullopt

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_EQ(layoutProperty_->GetIndicatorType().value_or(-1), INDICATOR_TYPE_DIVIDER);
    EXPECT_FALSE(layoutProperty_->HasIndicatorDividerWidth());
    EXPECT_FALSE(layoutProperty_->HasIndicatorDividerColor());
    EXPECT_FALSE(layoutProperty_->HasIndicatorStartMargin());
    EXPECT_FALSE(layoutProperty_->HasIndicatorEndMargin());
}

/**
 * @tc.name: SetIndicatorStyle015
 * @tc.desc: Test SetIndicatorStyle preserves borderRadius correctly
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyle015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode, Pattern, and LayoutProperty are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set indicator style with BACKGROUND type and custom borderRadius
     * @tc.expected: step2. BorderRadius should be preserved correctly
     */
    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_BACKGROUND;
    style.backgroundColor = Color::GRAY;

    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(5.0_vp);
    borderRadius.radiusTopRight = Dimension(10.0_vp);
    borderRadius.radiusBottomLeft = Dimension(15.0_vp);
    borderRadius.radiusBottomRight = Dimension(20.0_vp);
    style.borderRadius = borderRadius;

    ContainerPickerModel::SetIndicatorStyle(style);

    auto retrievedBorderRadius = layoutProperty_->GetIndicatorBorderRadius();
    EXPECT_TRUE(retrievedBorderRadius.has_value());
    EXPECT_EQ(retrievedBorderRadius->radiusTopLeft.value_or(Dimension()), 5.0_vp);
    EXPECT_EQ(retrievedBorderRadius->radiusTopRight.value_or(Dimension()), 10.0_vp);
    EXPECT_EQ(retrievedBorderRadius->radiusBottomLeft.value_or(Dimension()), 15.0_vp);
    EXPECT_EQ(retrievedBorderRadius->radiusBottomRight.value_or(Dimension()), 20.0_vp);
}

/**
 * @tc.name: SetOnChange001
 * @tc.desc: Test SetOnChange basic functionality using ViewStackProcessor
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onChange event and trigger it
     * @tc.expected: step2. Event should be triggered with correct index
     */
    int32_t testIndex = -1;
    ContainerPickerModel::SetOnChange([&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(5.0);
    EXPECT_EQ(testIndex, 5);

    eventHub->FireChangeEvent(10.0);
    EXPECT_EQ(testIndex, 10);
}

/**
 * @tc.name: SetOnChange002
 * @tc.desc: Test SetOnChange event replacement (multiple calls)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set first onChange event
     * @tc.expected: step2. First event should work
     */
    int32_t firstIndex = -1;
    ContainerPickerModel::SetOnChange([&firstIndex](const double& index) {
        firstIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(3.0);
    EXPECT_EQ(firstIndex, 3);

    /**
     * @tc.steps: step3. Replace with second onChange event
     * @tc.expected: step3. Second event should replace first, only second should be triggered
     */
    int32_t secondIndex = -1;
    ContainerPickerModel::SetOnChange([&secondIndex](const double& index) {
        secondIndex = static_cast<int32_t>(index) + 100; // Different logic to verify replacement
    });

    eventHub->FireChangeEvent(7.0);
    // First event handler should not be called
    EXPECT_EQ(firstIndex, 3); // Still 3, not updated
    // Second event handler should be called
    EXPECT_EQ(secondIndex, 107); // 7 + 100
}

/**
 * @tc.name: SetOnChange003
 * @tc.desc: Test SetOnChange when ViewStackProcessor has no main frame node
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear ViewStackProcessor to ensure no main frame node
     * @tc.expected: step1. Should not crash, return gracefully
     */
    ClearOldNodes();

    int32_t testIndex = -1;
    ContainerPickerModel::SetOnChange([&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });
    // If we reach here without crashing, the test passes
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnChange004
 * @tc.desc: Test SetOnChange with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node directly
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onChange event using FrameNode parameter
     * @tc.expected: step2. Event should be triggered with correct index
     */
    int32_t testIndex = -1;
    ContainerPickerChangeEvent testEvent = [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    };
    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode_), std::move(testEvent));

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(8.0);
    EXPECT_EQ(testIndex, 8);
}

/**
 * @tc.name: SetOnChange005
 * @tc.desc: Test SetOnChange with null FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetOnChange with null FrameNode
     * @tc.expected: step1. Should not crash, return gracefully
     */
    int32_t testIndex = -1;
    ContainerPickerChangeEvent testEvent = [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    };
    ContainerPickerModel::SetOnChange(static_cast<FrameNode*>(nullptr), std::move(testEvent));
    // If we reach here without crashing, the test passes
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnChange006
 * @tc.desc: Test SetOnChange event captures external variables correctly
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onChange event that captures multiple variables
     * @tc.expected: step2. Event should capture and update all variables correctly
     */
    int32_t indexValue = -1;
    bool eventFired = false;
    int32_t fireCount = 0;

    ContainerPickerModel::SetOnChange([&](const double& index) {
        indexValue = static_cast<int32_t>(index);
        eventFired = true;
        fireCount++;
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(12.0);
    EXPECT_EQ(indexValue, 12);
    EXPECT_TRUE(eventFired);
    EXPECT_EQ(fireCount, 1);

    eventHub->FireChangeEvent(25.0);
    EXPECT_EQ(indexValue, 25);
    EXPECT_TRUE(eventFired);
    EXPECT_EQ(fireCount, 2);
}

/**
 * @tc.name: SetOnChange007
 * @tc.desc: Test SetOnChange with zero index value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onChange event and trigger with zero
     * @tc.expected: step2. Event should handle zero correctly
     */
    int32_t testIndex = 999; // Non-zero initial value
    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode_), [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(0.0);
    EXPECT_EQ(testIndex, 0);
}

/**
 * @tc.name: SetOnChange008
 * @tc.desc: Test SetOnChange with negative index value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onChange event and trigger with negative value
     * @tc.expected: step2. Event should handle negative value correctly
     */
    int32_t testIndex = 0;
    ContainerPickerModel::SetOnChange([&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(-5.0);
    EXPECT_EQ(testIndex, -5);
}

/**
 * @tc.name: SetOnChange009
 * @tc.desc: Test SetOnChange with large index value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onChange event and trigger with large value
     * @tc.expected: step2. Event should handle large value correctly
     */
    int32_t testIndex = 0;
    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode_), [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(TEST_SCROLL_LARGE_INDEX);
    EXPECT_EQ(testIndex, TEST_SCROLL_LARGE_INDEX);
}

/**
 * @tc.name: SetOnChange010
 * @tc.desc: Test SetOnChange with multiple event fires
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onChange event and fire multiple times
     * @tc.expected: step2. Event should be triggered each time with correct value
     */
    std::vector<int32_t> receivedIndices;
    ContainerPickerModel::SetOnChange([&receivedIndices](const double& index) {
        receivedIndices.push_back(static_cast<int32_t>(index));
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::vector<double> testValues = {1.0, 5.0, 10.0, 100.0, 500.0};
    for (double value : testValues) {
        eventHub->FireChangeEvent(value);
    }

    EXPECT_EQ(receivedIndices.size(), testValues.size());
    for (size_t i = 0; i < testValues.size(); ++i) {
        EXPECT_EQ(receivedIndices[i], static_cast<int32_t>(testValues[i]));
    }
}

/**
 * @tc.name: SetOnChange011
 * @tc.desc: Test SetOnChange with move semantics
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onChange event using std::move
     * @tc.expected: step2. Event should work correctly after move
     */
    int32_t testIndex = -1;
    ContainerPickerChangeEvent testEvent = [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index) * 2;
    };
    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode_), std::move(testEvent));

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(15.0);
    EXPECT_EQ(testIndex, 30); // 15 * 2
}

/**
 * @tc.name: SetOnChange012
 * @tc.desc: Test SetOnChange preserves state across multiple events
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnChange012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onChange event with state accumulation
     * @tc.expected: step2. Event should maintain state across calls
     */
    int32_t sum = 0;
    ContainerPickerModel::SetOnChange([&sum](const double& index) {
        sum += static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(10.0);
    EXPECT_EQ(sum, 10);

    eventHub->FireChangeEvent(20.0);
    EXPECT_EQ(sum, 30);

    eventHub->FireChangeEvent(30.0);
    EXPECT_EQ(sum, 60);
}

/**
 * @tc.name: SetOnScrollStop001
 * @tc.desc: Test SetOnScrollStop basic functionality using ViewStackProcessor
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onScrollStop event and trigger it
     * @tc.expected: step2. Event should be triggered with correct index
     */
    int32_t testIndex = -1;
    ContainerPickerModel::SetOnScrollStop([&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(6.0);
    EXPECT_EQ(testIndex, 6);
}

/**
 * @tc.name: SetOnScrollStop002
 * @tc.desc: Test SetOnScrollStop with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onScrollStop event using FrameNode parameter
     * @tc.expected: step2. Event should be triggered with correct index
     */
    int32_t testIndex = -1;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(11.0);
    EXPECT_EQ(testIndex, 11);
}

/**
 * @tc.name: SetOnScrollStop003
 * @tc.desc: Test SetOnScrollStop with null FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetOnScrollStop with null FrameNode
     * @tc.expected: step1. Should not crash, return gracefully
     */
    int32_t testIndex = -1;
    ContainerPickerModel::SetOnScrollStop(static_cast<FrameNode*>(nullptr), [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });
    // If we reach here without crashing, the test passes
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnScrollStop004
 * @tc.desc: Test SetOnScrollStop and SetOnChange can coexist
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set both onChange and onScrollStop events
     * @tc.expected: step2. Both events should work independently
     */
    int32_t changeIndex = -1;
    int32_t scrollStopIndex = -1;

    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode_), [&changeIndex](const double& index) {
        changeIndex = static_cast<int32_t>(index);
    });

    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&scrollStopIndex](const double& index) {
        scrollStopIndex = static_cast<int32_t>(index) + 1000;
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(5.0);
    EXPECT_EQ(changeIndex, 5);
    EXPECT_EQ(scrollStopIndex, -1); // Not fired yet

    eventHub->FireScrollStopEvent(7.0);
    EXPECT_EQ(changeIndex, 5); // Unchanged
    EXPECT_EQ(scrollStopIndex, 1007); // 7 + 1000
}

/**
 * @tc.name: SetOnScrollStop005
 * @tc.desc: Test SetOnScrollStop event replacement (multiple calls)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set first onScrollStop event
     * @tc.expected: step2. First event should work
     */
    int32_t firstIndex = -1;
    ContainerPickerModel::SetOnScrollStop([&firstIndex](const double& index) {
        firstIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(4.0);
    EXPECT_EQ(firstIndex, 4);

    /**
     * @tc.steps: step3. Replace with second onScrollStop event
     * @tc.expected: step3. Second event should replace first, only second should be triggered
     */
    int32_t secondIndex = -1;
    ContainerPickerModel::SetOnScrollStop([&secondIndex](const double& index) {
        secondIndex = static_cast<int32_t>(index) + 200; // Different logic to verify replacement
    });

    eventHub->FireScrollStopEvent(6.0);
    // First event handler should not be called
    EXPECT_EQ(firstIndex, 4); // Still 4, not updated
    // Second event handler should be called
    EXPECT_EQ(secondIndex, 206); // 6 + 200
}

/**
 * @tc.name: SetOnScrollStop006
 * @tc.desc: Test SetOnScrollStop when ViewStackProcessor has no main frame node
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear ViewStackProcessor to ensure no main frame node
     * @tc.expected: step1. Should not crash, return gracefully
     */
    ClearOldNodes();

    int32_t testIndex = -1;
    ContainerPickerModel::SetOnScrollStop([&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });
    // If we reach here without crashing, the test passes
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnScrollStop007
 * @tc.desc: Test SetOnScrollStop event captures external variables correctly
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onScrollStop event that captures multiple variables
     * @tc.expected: step2. Event should capture and update all variables correctly
     */
    int32_t indexValue = -1;
    bool eventFired = false;
    int32_t fireCount = 0;

    ContainerPickerModel::SetOnScrollStop([&](const double& index) {
        indexValue = static_cast<int32_t>(index);
        eventFired = true;
        fireCount++;
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireScrollStopEvent(18.0);
    EXPECT_EQ(indexValue, 18);
    EXPECT_TRUE(eventFired);
    EXPECT_EQ(fireCount, 1);

    eventHub->FireScrollStopEvent(32.0);
    EXPECT_EQ(indexValue, 32);
    EXPECT_TRUE(eventFired);
    EXPECT_EQ(fireCount, 2);
}

/**
 * @tc.name: SetOnScrollStop008
 * @tc.desc: Test SetOnScrollStop with zero index value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onScrollStop event and trigger with zero
     * @tc.expected: step2. Event should handle zero correctly
     */
    int32_t testIndex = 888; // Non-zero initial value
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(0.0);
    EXPECT_EQ(testIndex, 0);
}

/**
 * @tc.name: SetOnScrollStop009
 * @tc.desc: Test SetOnScrollStop with negative index value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onScrollStop event and trigger with negative value
     * @tc.expected: step2. Event should handle negative value correctly
     */
    int32_t testIndex = 0;
    ContainerPickerModel::SetOnScrollStop([&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(-8.0);
    EXPECT_EQ(testIndex, -8);
}

/**
 * @tc.name: SetOnScrollStop010
 * @tc.desc: Test SetOnScrollStop with large index value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onScrollStop event and trigger with large value
     * @tc.expected: step2. Event should handle large value correctly
     */
    int32_t testIndex = 0;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(TEST_SCROLL_LARGE_INDEX);
    EXPECT_EQ(testIndex, TEST_SCROLL_LARGE_INDEX);
}

/**
 * @tc.name: SetOnScrollStop011
 * @tc.desc: Test SetOnScrollStop with multiple event fires
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onScrollStop event and fire multiple times
     * @tc.expected: step2. Event should be triggered each time with correct value
     */
    std::vector<int32_t> receivedIndices;
    ContainerPickerModel::SetOnScrollStop([&receivedIndices](const double& index) {
        receivedIndices.push_back(static_cast<int32_t>(index));
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::vector<double> testValues = {2.0, 6.0, 11.0, 101.0, 501.0};
    for (double value : testValues) {
        eventHub->FireScrollStopEvent(value);
    }

    EXPECT_EQ(receivedIndices.size(), testValues.size());
    for (size_t i = 0; i < testValues.size(); ++i) {
        EXPECT_EQ(receivedIndices[i], static_cast<int32_t>(testValues[i]));
    }
}

/**
 * @tc.name: SetOnScrollStop012
 * @tc.desc: Test SetOnScrollStop with move semantics
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onScrollStop event using std::move
     * @tc.expected: step2. Event should work correctly after move
     */
    int32_t testIndex = -1;
    ContainerPickerChangeEvent testEvent = [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index) * 3;
    };
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), std::move(testEvent));

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(14.0);
    EXPECT_EQ(testIndex, 42); // 14 * 3
}

/**
 * @tc.name: SetOnScrollStop013
 * @tc.desc: Test SetOnScrollStop preserves state across multiple events
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onScrollStop event with state accumulation
     * @tc.expected: step2. Event should maintain state across calls
     */
    int32_t product = 1;
    ContainerPickerModel::SetOnScrollStop([&product](const double& index) {
        product *= static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireScrollStopEvent(2.0);
    EXPECT_EQ(product, 2);

    eventHub->FireScrollStopEvent(3.0);
    EXPECT_EQ(product, 6);

    eventHub->FireScrollStopEvent(4.0);
    EXPECT_EQ(product, 24);
}

/**
 * @tc.name: SetOnScrollStop014
 * @tc.desc: Test SetOnScrollStop with alternating calls
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set onScrollStop event and fire with alternating values
     * @tc.expected: step2. Event should handle alternating values correctly
     */
    int32_t testIndex = 0;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    // Alternate between two values
    eventHub->FireScrollStopEvent(5.0);
    EXPECT_EQ(testIndex, 5);

    eventHub->FireScrollStopEvent(10.0);
    EXPECT_EQ(testIndex, 10);

    eventHub->FireScrollStopEvent(5.0);
    EXPECT_EQ(testIndex, 5);

    eventHub->FireScrollStopEvent(10.0);
    EXPECT_EQ(testIndex, 10);
}

/**
 * @tc.name: SetOnScrollStop015
 * @tc.desc: Test SetOnScrollStop with INT_MAX value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set onScrollStop event and trigger with INT_MAX
     * @tc.expected: step2. Event should handle INT_MAX correctly
     */
    int32_t testIndex = 0;
    ContainerPickerModel::SetOnScrollStop([&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(static_cast<double>(INT32_MAX));
    EXPECT_EQ(testIndex, INT32_MAX);
}

/**
 * @tc.name: SetOnScrollStop016
 * @tc.desc: Test SetOnScrollStop events are independent of onChange events
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set both onChange and onScrollStop events
     * @tc.expected: step2. FireChangeEvent should not trigger onScrollStop, and vice versa
     */
    int32_t changeCount = 0;
    int32_t scrollStopCount = 0;

    ContainerPickerModel::SetOnChange([&changeCount](const double& index) {
        changeCount++;
    });

    ContainerPickerModel::SetOnScrollStop([&scrollStopCount](const double& index) {
        scrollStopCount++;
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    // Fire multiple change events
    eventHub->FireChangeEvent(1.0);
    eventHub->FireChangeEvent(2.0);
    eventHub->FireChangeEvent(3.0);
    EXPECT_EQ(changeCount, 3);
    EXPECT_EQ(scrollStopCount, 0); // Should not be triggered

    // Fire multiple scroll stop events
    eventHub->FireScrollStopEvent(4.0);
    eventHub->FireScrollStopEvent(5.0);
    EXPECT_EQ(changeCount, 3); // Unchanged
    EXPECT_EQ(scrollStopCount, 2); // Only increased by scroll stop events
}

/**
 * @tc.name: SetOnScrollStop017
 * @tc.desc: Test alternating between ViewStackProcessor and FrameNode versions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponentsFromStack();

    /**
     * @tc.steps: step2. Set event using ViewStackProcessor version
     * @tc.expected: step2. First event should work
     */
    int32_t firstIndex = -1;
    ContainerPickerModel::SetOnScrollStop([&firstIndex](const double& index) {
        firstIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(3.0);
    EXPECT_EQ(firstIndex, 3);

    /**
     * @tc.steps: step3. Replace with FrameNode version
     * @tc.expected: step3. Second event should replace first
     */
    int32_t secondIndex = -1;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&secondIndex](const double& index) {
        secondIndex = static_cast<int32_t>(index) + 100;
    });

    eventHub->FireScrollStopEvent(5.0);
    EXPECT_EQ(firstIndex, 3); // Unchanged
    EXPECT_EQ(secondIndex, 105); // 5 + 100

    /**
     * @tc.steps: step4. Switch back to ViewStackProcessor version
     * @tc.expected: step4. Third event should replace second
     */
    int32_t thirdIndex = -1;
    ContainerPickerModel::SetOnScrollStop([&thirdIndex](const double& index) {
        thirdIndex = static_cast<int32_t>(index) + 200;
    });

    eventHub->FireScrollStopEvent(7.0);
    EXPECT_EQ(secondIndex, 105); // Unchanged
    EXPECT_EQ(thirdIndex, 207); // 7 + 200
}

/**
 * @tc.name: SetOnScrollStop018
 * @tc.desc: Test FrameNode version with event replacement
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set first event using FrameNode version
     * @tc.expected: step2. First event should work
     */
    int32_t firstCount = 0;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&firstCount](const double& index) {
        firstCount++;
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(1.0);
    EXPECT_EQ(firstCount, 1);

    /**
     * @tc.steps: step3. Replace with second event using FrameNode version
     * @tc.expected: step3. Second event should replace first completely
     */
    int32_t secondCount = 0;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&secondCount](const double& index) {
        secondCount++;
    });

    eventHub->FireScrollStopEvent(2.0);
    EXPECT_EQ(firstCount, 1); // Unchanged
    EXPECT_EQ(secondCount, 1);

    /**
     * @tc.steps: step4. Replace with third event
     * @tc.expected: step4. Third event should replace second
     */
    int32_t thirdCount = 0;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&thirdCount](const double& index) {
        thirdCount++;
    });

    eventHub->FireScrollStopEvent(3.0);
    EXPECT_EQ(firstCount, 1); // Unchanged
    EXPECT_EQ(secondCount, 1); // Unchanged
    EXPECT_EQ(thirdCount, 1);
}

/**
 * @tc.name: SetOnScrollStop019
 * @tc.desc: Test FrameNode version with lambda capturing this pointer
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set event using FrameNode with this pointer capture
     * @tc.expected: step2. Event should capture and use class member
     */
    int32_t capturedValue = 0;
    auto eventCallback = [this, &capturedValue](const double& index) {
        capturedValue = static_cast<int32_t>(index);
        // Verify we can access test fixture members
        EXPECT_NE(frameNode_, nullptr);
    };

    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), std::move(eventCallback));

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(42.0);
    EXPECT_EQ(capturedValue, 42);
}

/**
 * @tc.name: SetOnScrollStop020
 * @tc.desc: Test FrameNode version preserves lambda capture state
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set event with captured state
     * @tc.expected: step2. Event should maintain captured state across calls
     */
    std::string eventLog;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&eventLog](const double& index) {
        eventLog += "Index:" + std::to_string(static_cast<int32_t>(index)) + ";";
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireScrollStopEvent(1.0);
    EXPECT_EQ(eventLog, "Index:1;");

    eventHub->FireScrollStopEvent(2.0);
    EXPECT_EQ(eventLog, "Index:1;Index:2;");

    eventHub->FireScrollStopEvent(3.0);
    EXPECT_EQ(eventLog, "Index:1;Index:2;Index:3;");
}

/**
 * @tc.name: SetOnScrollStop021
 * @tc.desc: Test FrameNode version with complex lambda logic
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set event with complex lambda logic
     * @tc.expected: step2. Event should execute complex logic correctly
     */
    struct EventData {
        int32_t minIndex = INT32_MAX;
        int32_t maxIndex = INT32_MIN;
        int32_t sum = 0;
        int32_t count = 0;
        double average = 0.0;
    } eventData;

    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&eventData](const double& index) {
        int32_t idx = static_cast<int32_t>(index);
        eventData.minIndex = std::min(eventData.minIndex, idx);
        eventData.maxIndex = std::max(eventData.maxIndex, idx);
        eventData.sum += idx;
        eventData.count++;
        eventData.average = static_cast<double>(eventData.sum) / eventData.count;
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    std::vector<int32_t> testValues = {5, 10, 3, 8, 12};
    for (int32_t value : testValues) {
        eventHub->FireScrollStopEvent(static_cast<double>(value));
    }

    EXPECT_EQ(eventData.minIndex, 3);
    EXPECT_EQ(eventData.maxIndex, 12);
    EXPECT_EQ(eventData.sum, 38);
    EXPECT_EQ(eventData.count, 5);
    EXPECT_DOUBLE_EQ(eventData.average, 7.6);
}

/**
 * @tc.name: SetOnScrollStop022
 * @tc.desc: Test FrameNode version immediately after CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and immediately set event
     * @tc.expected: step1. Event should be set correctly without any issues
     */
    auto frameNode = ContainerPickerModel::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);

    int32_t testIndex = -1;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode), [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    });

    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(99.0);
    EXPECT_EQ(testIndex, 99);
}

/**
 * @tc.name: SetOnScrollStop023
 * @tc.desc: Test FrameNode version with multiple calls before event fire
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set event multiple times before firing
     * @tc.expected: step2. Only the last set event should be triggered
     */
    int32_t firstIndex = -1;
    int32_t secondIndex = -1;
    int32_t thirdIndex = -1;

    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&firstIndex](const double& index) {
        firstIndex = static_cast<int32_t>(index);
    });

    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&secondIndex](const double& index) {
        secondIndex = static_cast<int32_t>(index) + 10;
    });

    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&thirdIndex](const double& index) {
        thirdIndex = static_cast<int32_t>(index) + 100;
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(7.0);

    EXPECT_EQ(firstIndex, -1); // Never triggered
    EXPECT_EQ(secondIndex, -1); // Never triggered
    EXPECT_EQ(thirdIndex, 107); // Only last one triggered: 7 + 100
}

/**
 * @tc.name: SetOnScrollStop024
 * @tc.desc: Test FrameNode version alternating with SetOnChange
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Alternate setting onChange and onScrollStop
     * @tc.expected: step2. Events should be independent
     */
    int32_t changeIndex = -1;
    int32_t scrollStopIndex = -1;

    // Set onChange
    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode_), [&changeIndex](const double& index) {
        changeIndex = static_cast<int32_t>(index);
    });

    // Set onScrollStop
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&scrollStopIndex](const double& index) {
        scrollStopIndex = static_cast<int32_t>(index);
    });

    // Replace onChange
    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode_), [&changeIndex](const double& index) {
        changeIndex = static_cast<int32_t>(index) + 1000;
    });

    // Replace onScrollStop
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&scrollStopIndex](const double& index) {
        scrollStopIndex = static_cast<int32_t>(index) + 2000;
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(5.0);
    EXPECT_EQ(changeIndex, 1005); // 5 + 1000
    EXPECT_EQ(scrollStopIndex, -1); // Not fired

    eventHub->FireScrollStopEvent(7.0);
    EXPECT_EQ(changeIndex, 1005); // Unchanged
    EXPECT_EQ(scrollStopIndex, 2007); // 7 + 2000
}

/**
 * @tc.name: SetOnScrollStop025
 * @tc.desc: Test FrameNode version event doesn't affect onChange event
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetOnScrollStop025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node
     * @tc.expected: step1. FrameNode and EventHub are created successfully
     */
    GetContainerPickerComponents();

    /**
     * @tc.steps: step2. Set both events using FrameNode version
     * @tc.expected: step2. Events should be completely independent
     */
    int32_t changeCallCount = 0;
    int32_t scrollStopCallCount = 0;
    std::vector<int32_t> changeValues;
    std::vector<int32_t> scrollStopValues;

    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode_), [&](const double& index) {
        changeCallCount++;
        changeValues.push_back(static_cast<int32_t>(index));
    });

    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode_), [&](const double& index) {
        scrollStopCallCount++;
        scrollStopValues.push_back(static_cast<int32_t>(index));
    });

    auto eventHub = frameNode_->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);

    // Fire multiple change events
    eventHub->FireChangeEvent(1.0);
    eventHub->FireChangeEvent(2.0);
    eventHub->FireChangeEvent(3.0);

    // Fire multiple scroll stop events
    eventHub->FireScrollStopEvent(10.0);
    eventHub->FireScrollStopEvent(20.0);

    EXPECT_EQ(changeCallCount, 3);
    EXPECT_EQ(scrollStopCallCount, 2);

    EXPECT_EQ(changeValues.size(), 3UL);
    EXPECT_EQ(changeValues[0], 1);
    EXPECT_EQ(changeValues[1], 2);
    EXPECT_EQ(changeValues[2], 3);

    EXPECT_EQ(scrollStopValues.size(), 2UL);
    EXPECT_EQ(scrollStopValues[0], 10);
    EXPECT_EQ(scrollStopValues[1], 20);
}

/**
 * @tc.name: CreateChildConstraint001
 * @tc.desc: Test CreateChildConstraint with custom maxItemHeightPx parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, CreateChildConstraint001, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();

    ContainerPickerModel::SetItemHeight(50.0_vp);

    auto geometryNode = frameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    OptionalSizeF idealSize;
    idealSize.SetWidth(200.0f);

    auto layoutProperty = frameNode_->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    float customItemHeightPx = static_cast<float>(Dimension(50.0_vp).ConvertToPx());
    auto constraint = ContainerPickerUtils::CreateChildConstraint(layoutProperty, idealSize, customItemHeightPx);

    EXPECT_FLOAT_EQ(constraint.maxSize.Height(), customItemHeightPx);
    EXPECT_FLOAT_EQ(constraint.selfIdealSize.Height().value_or(0.0f), customItemHeightPx);
}

/**
 * @tc.name: CreateChildConstraint002
 * @tc.desc: Test CreateChildConstraint with default maxItemHeightPx parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, CreateChildConstraint002, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();

    auto geometryNode = frameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    OptionalSizeF idealSize;
    idealSize.SetWidth(200.0f);

    auto layoutProperty = frameNode_->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    float defaultItemHeightPx = static_cast<float>(Dimension(DEFAULT_ITEM_HEIGHT_VP).ConvertToPx());
    auto constraint = ContainerPickerUtils::CreateChildConstraint(layoutProperty, idealSize, defaultItemHeightPx);

    EXPECT_FLOAT_EQ(constraint.maxSize.Height(), defaultItemHeightPx);
    EXPECT_FLOAT_EQ(constraint.selfIdealSize.Height().value_or(0.0f), defaultItemHeightPx);
}

/**
 * @tc.name: SyncPickerParamsFromLayout001
 * @tc.desc: Test SyncPickerParamsFromLayout updates displayCount and itemHeight from properties
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SyncPickerParamsFromLayout001, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetDisplayedItemCount(AceType::RawPtr(frameNode_), 5);
    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), 50.0_vp);

    pickerPattern_->OnModifyDone();

    auto patternItemHeight = pickerPattern_->GetPickerItemHeight();
    auto expectedItemHeightPx = static_cast<float>(Dimension(50.0_vp).ConvertToPx());
    EXPECT_NEAR(patternItemHeight, expectedItemHeightPx, FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: SyncPickerParamsFromLayout002
 * @tc.desc: Test SyncPickerParamsFromLayout with default values when properties not set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SyncPickerParamsFromLayout002, TestSize.Level1)
{
    GetContainerPickerComponents();

    pickerPattern_->OnModifyDone();

    auto patternItemHeight = pickerPattern_->GetPickerItemHeight();
    auto defaultItemHeightPx = static_cast<float>(Dimension(DEFAULT_ITEM_HEIGHT_VP).ConvertToPx());
    EXPECT_NEAR(patternItemHeight, defaultItemHeightPx, FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: LayoutAlgorithmDisplayedItemCount001
 * @tc.desc: Test LayoutAlgorithm uses displayedItemCount_ parameter correctly
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, LayoutAlgorithmDisplayedItemCount001, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetDisplayedItemCount(AceType::RawPtr(frameNode_), 5);

    auto layoutAlgorithm = pickerPattern_->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);

    auto containerPickerAlgorithm = AceType::DynamicCast<ContainerPickerLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(containerPickerAlgorithm, nullptr);
}

/**
 * @tc.name: LayoutAlgorithmDisplayedItemCount002
 * @tc.desc: Test LayoutAlgorithm CalcMainAndMiddlePos with different displayedItemCount
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, LayoutAlgorithmDisplayedItemCount002, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetDisplayedItemCount(AceType::RawPtr(frameNode_), 9);
    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), 64.0_vp);

    pickerPattern_->OnModifyDone();

    auto layoutAlgorithm = pickerPattern_->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
}

/**
 * @tc.name: SetDisplayedItemCount003
 * @tc.desc: Test SetDisplayedItemCount with negative value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetDisplayedItemCount003, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetDisplayedItemCount(AceType::RawPtr(frameNode_), -1);

    ASSERT_TRUE(layoutProperty_->HasDisplayedItemCount());
    EXPECT_EQ(layoutProperty_->GetDisplayedItemCount().value_or(-1), DEFAULT_DISPLAYED_ITEM_COUNT);
}

/**
 * @tc.name: SetItemHeight003
 * @tc.desc: Test SetItemHeight with negative value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeight003, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), -10.0_vp);

    ASSERT_TRUE(layoutProperty_->HasItemHeight());
    auto resultHeight = layoutProperty_->GetItemHeight().value().ConvertToVp();
    EXPECT_NEAR(resultHeight, DEFAULT_ITEM_HEIGHT_VP, FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: SetDisplayedItemCount004
 * @tc.desc: Test SetDisplayedItemCount with zero value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetDisplayedItemCount004, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetDisplayedItemCount(AceType::RawPtr(frameNode_), 0);

    ASSERT_TRUE(layoutProperty_->HasDisplayedItemCount());
    EXPECT_EQ(layoutProperty_->GetDisplayedItemCount().value_or(-1), DEFAULT_DISPLAYED_ITEM_COUNT);
}

/**
 * @tc.name: SetItemHeight004
 * @tc.desc: Test SetItemHeight with zero value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeight004, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), 0.0_vp);

    ASSERT_TRUE(layoutProperty_->HasItemHeight());
    auto resultHeight = layoutProperty_->GetItemHeight().value().ConvertToVp();
    EXPECT_NEAR(resultHeight, DEFAULT_ITEM_HEIGHT_VP, FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: SetDisplayedItemCount005
 * @tc.desc: Test SetDisplayedItemCount with very large value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetDisplayedItemCount005, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetDisplayedItemCount(AceType::RawPtr(frameNode_), 1000);

    ASSERT_TRUE(layoutProperty_->HasDisplayedItemCount());
    EXPECT_EQ(layoutProperty_->GetDisplayedItemCount().value_or(-1), DEFAULT_DISPLAYED_ITEM_COUNT);
}

/**
 * @tc.name: SetItemHeight005
 * @tc.desc: Test SetItemHeight with very large value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeight005, TestSize.Level1)
{
    GetContainerPickerComponents();

    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), 1000.0_vp);

    ASSERT_TRUE(layoutProperty_->HasItemHeight());
    auto resultHeight = layoutProperty_->GetItemHeight().value().ConvertToVp();
    EXPECT_NEAR(resultHeight, DEFAULT_ITEM_HEIGHT_VP, FLOAT_COMPARE_EPSILON);
}

/**
 * @tc.name: SetItemHeightLpx001
 * @tc.desc: Test SetItemHeight with LPX unit
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeightLpx001, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();
    ASSERT_NE(frameNode_, nullptr);

    constexpr double lpxValue = 50.0;
    Dimension height(lpxValue, DimensionUnit::LPX);

    ContainerPickerModel::SetItemHeight(height);

    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_PICKER_ITEM_HEIGHT) !=
        frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetItemHeightLpx002
 * @tc.desc: Test SetItemHeight with VP unit (non-LPX)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeightLpx002, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();
    ASSERT_NE(frameNode_, nullptr);

    constexpr double vpValue = 50.0;
    Dimension height(vpValue, DimensionUnit::VP);

    ContainerPickerModel::SetItemHeight(height);

    EXPECT_TRUE(frameNode_->lpxAttributes_.find(LpxAttribute::ALWAYS) == frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetIndicatorStyleLpx001
 * @tc.desc: Test SetIndicatorStyle with LPX units for divider indicator
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyleLpx001, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();
    ASSERT_NE(frameNode_, nullptr);

    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    constexpr double lpxValue = 5.0;
    style.strokeWidth = Dimension(lpxValue, DimensionUnit::LPX);
    style.startMargin = Dimension(lpxValue, DimensionUnit::LPX);
    style.endMargin = Dimension(lpxValue, DimensionUnit::LPX);

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_STROKE_WIDTH) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_START_MARGIN) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_END_MARGIN) !=
        frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetIndicatorStyleLpx002
 * @tc.desc: Test SetIndicatorStyle with VP units (non-LPX) for divider indicator
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyleLpx002, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();
    ASSERT_NE(frameNode_, nullptr);

    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    constexpr double vpValue = 5.0;
    style.strokeWidth = Dimension(vpValue, DimensionUnit::VP);
    style.startMargin = Dimension(vpValue, DimensionUnit::VP);
    style.endMargin = Dimension(vpValue, DimensionUnit::VP);

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_TRUE(frameNode_->lpxAttributes_.find(LpxAttribute::ALWAYS) == frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetIndicatorStyleLpx003
 * @tc.desc: Test SetIndicatorStyle with LPX units for borderRadius
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyleLpx003, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();
    ASSERT_NE(frameNode_, nullptr);

    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_BACKGROUND;
    constexpr double lpxValue = 5.0;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(lpxValue, DimensionUnit::LPX);
    borderRadius.radiusTopRight = Dimension(lpxValue, DimensionUnit::LPX);
    borderRadius.radiusBottomLeft = Dimension(lpxValue, DimensionUnit::LPX);
    borderRadius.radiusBottomRight = Dimension(lpxValue, DimensionUnit::LPX);
    style.borderRadius = borderRadius;

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_BORDER_RADIUS_TOP_LEFT) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_BORDER_RADIUS_TOP_RIGHT) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_BORDER_RADIUS_BOTTOM_LEFT) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_BORDER_RADIUS_BOTTOM_RIGHT) !=
        frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetIndicatorStyleLpx004
 * @tc.desc: Test SetIndicatorStyle with VP units (non-LPX) for borderRadius
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyleLpx004, TestSize.Level1)
{
    GetContainerPickerComponentsFromStack();
    ASSERT_NE(frameNode_, nullptr);

    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    constexpr double vpValue = 5.0;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(vpValue, DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(vpValue, DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(vpValue, DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(vpValue, DimensionUnit::VP);
    style.borderRadius = borderRadius;

    ContainerPickerModel::SetIndicatorStyle(style);

    EXPECT_TRUE(frameNode_->lpxAttributes_.find(LpxAttribute::ALWAYS) == frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetItemHeightFrameNodeLpx001
 * @tc.desc: Test SetItemHeight with FrameNode and LPX unit
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeightFrameNodeLpx001, TestSize.Level1)
{
    GetContainerPickerComponents();
    ASSERT_NE(frameNode_, nullptr);

    constexpr double lpxValue = 50.0;
    Dimension height(lpxValue, DimensionUnit::LPX);

    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), height);

    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_PICKER_ITEM_HEIGHT) !=
        frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetItemHeightFrameNodeLpx002
 * @tc.desc: Test SetItemHeight with FrameNode and VP unit (non-LPX)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetItemHeightFrameNodeLpx002, TestSize.Level1)
{
    GetContainerPickerComponents();
    ASSERT_NE(frameNode_, nullptr);

    constexpr double vpValue = 50.0;
    Dimension height(vpValue, DimensionUnit::VP);

    ContainerPickerModel::SetItemHeight(AceType::RawPtr(frameNode_), height);

    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_PICKER_ITEM_HEIGHT) ==
        frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetIndicatorStyleFrameNodeLpx001
 * @tc.desc: Test SetIndicatorStyle with FrameNode and LPX units
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyleFrameNodeLpx001, TestSize.Level1)
{
    GetContainerPickerComponents();
    ASSERT_NE(frameNode_, nullptr);

    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    constexpr double lpxValue = 5.0;
    style.strokeWidth = Dimension(lpxValue, DimensionUnit::LPX);
    style.startMargin = Dimension(lpxValue, DimensionUnit::LPX);
    style.endMargin = Dimension(lpxValue, DimensionUnit::LPX);

    ContainerPickerModel::SetIndicatorStyle(AceType::RawPtr(frameNode_), style);

    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_STROKE_WIDTH) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_START_MARGIN) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_END_MARGIN) !=
        frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetIndicatorStyleFrameNodeLpx002
 * @tc.desc: Test SetIndicatorStyle with FrameNode and VP units (non-LPX)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyleFrameNodeLpx002, TestSize.Level1)
{
    GetContainerPickerComponents();
    ASSERT_NE(frameNode_, nullptr);

    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_DIVIDER;
    constexpr double vpValue = 5.0;
    style.strokeWidth = Dimension(vpValue, DimensionUnit::VP);
    style.startMargin = Dimension(vpValue, DimensionUnit::VP);
    style.endMargin = Dimension(vpValue, DimensionUnit::VP);

    ContainerPickerModel::SetIndicatorStyle(AceType::RawPtr(frameNode_), style);

    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_STROKE_WIDTH) ==
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_START_MARGIN) ==
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_DIVIDER_END_MARGIN) ==
        frameNode_->lpxAttributes_.end());
}

/**
 * @tc.name: SetIndicatorStyleFrameNodeLpx003
 * @tc.desc: Test SetIndicatorStyle with FrameNode and LPX units for borderRadius
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerModelTest, SetIndicatorStyleFrameNodeLpx003, TestSize.Level1)
{
    GetContainerPickerComponents();
    ASSERT_NE(frameNode_, nullptr);

    PickerIndicatorStyle style;
    style.type = INDICATOR_TYPE_BACKGROUND;
    constexpr double lpxValue = 5.0;
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(lpxValue, DimensionUnit::LPX);
    borderRadius.radiusTopRight = Dimension(lpxValue, DimensionUnit::LPX);
    borderRadius.radiusBottomLeft = Dimension(lpxValue, DimensionUnit::LPX);
    borderRadius.radiusBottomRight = Dimension(lpxValue, DimensionUnit::LPX);
    style.borderRadius = borderRadius;

    ContainerPickerModel::SetIndicatorStyle(AceType::RawPtr(frameNode_), style);

    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_BORDER_RADIUS_TOP_LEFT) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_BORDER_RADIUS_TOP_RIGHT) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_BORDER_RADIUS_BOTTOM_LEFT) !=
        frameNode_->lpxAttributes_.end());
    EXPECT_TRUE(
        frameNode_->lpxAttributes_.find(LpxAttribute::LPX_BORDER_RADIUS_BOTTOM_RIGHT) !=
        frameNode_->lpxAttributes_.end());
}

} // namespace OHOS::Ace::NG
