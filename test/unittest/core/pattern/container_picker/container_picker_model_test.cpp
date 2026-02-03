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

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

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

} // namespace OHOS::Ace::NG
