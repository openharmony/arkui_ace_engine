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

#include <algorithm>
#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ContainerPickerPatternTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateContainerPickerNode();
};

void ContainerPickerPatternTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PickerTheme>()));
}

void ContainerPickerPatternTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerPickerPatternTest::SetUp() {}

void ContainerPickerPatternTest::TearDown() {}

RefPtr<FrameNode> ContainerPickerPatternTest::CreateContainerPickerNode()
{
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

/**
 * @tc.name: ContainerPickerUtilsTest_GetLoopIndex001
 * @tc.desc: Test GetLoopIndex function with positive index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerUtilsTest_GetLoopIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set totalItemCount and test GetLoopIndex with positive index.
     * @tc.expected: step1. the loop index is correct.
     */
    EXPECT_EQ(ContainerPickerUtils::GetLoopIndex(0, 5), 0);
    EXPECT_EQ(ContainerPickerUtils::GetLoopIndex(3, 5), 3);
    EXPECT_EQ(ContainerPickerUtils::GetLoopIndex(5, 5), 0);
    EXPECT_EQ(ContainerPickerUtils::GetLoopIndex(7, 5), 2);
}

/**
 * @tc.name: ContainerPickerUtilsTest_GetLoopIndex002
 * @tc.desc: Test GetLoopIndex function with negative index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerUtilsTest_GetLoopIndex002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set totalItemCount and test GetLoopIndex with negative index.
     * @tc.expected: step1. the loop index is correct.
     */
    EXPECT_EQ(ContainerPickerUtils::GetLoopIndex(-1, 5), 4);
    EXPECT_EQ(ContainerPickerUtils::GetLoopIndex(-3, 5), 2);
    EXPECT_EQ(ContainerPickerUtils::GetLoopIndex(-5, 5), 0);
    EXPECT_EQ(ContainerPickerUtils::GetLoopIndex(-7, 5), 3);
}

/**
 * @tc.name: ContainerPickerUtilsCalcCurrentMiddleItemTest001
 * @tc.desc: Test CalcCurrentMiddleItem method of ContainerPickerUtils
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerPatternTest, ContainerPickerUtilsCalcCurrentMiddleItemTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Add items to itemPosition_
     */
    ContainerPickerUtils::PositionMap itemPosition_;
    itemPosition_[0] = { 100.0f, 150.0f, nullptr };
    itemPosition_[1] = { 150.0f, 200.0f, nullptr };
    itemPosition_[2] = { 200.0f, 250.0f, nullptr };
    itemPosition_[3] = { 250.0f, 300.0f, nullptr };

    /**
     * @tc.steps: step2. Call CalcCurrentMiddleItem
     * @tc.expected: step2. The middle item should be found correctly
     */
    auto result = ContainerPickerUtils::CalcCurrentMiddleItem(itemPosition_, 450.0f, 4, false);
    EXPECT_EQ(result.first, 2);
    EXPECT_TRUE(NearEqual(result.second.startPos, 200.0f));
    EXPECT_TRUE(NearEqual(result.second.endPos, 250.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_SetSelectedIndex001
 * @tc.desc: Test SetSelectedIndex function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_SetSelectedIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set totalItemCount and test SetSelectedIndex with valid index.
     * @tc.expected: step2. the selected index is set correctly.
     */
    pattern->totalItemCount_ = 5;
    pattern->SetSelectedIndex(3);
    EXPECT_EQ(pattern->selectedIndex_, 3);

    /**
     * @tc.steps: step3. test SetSelectedIndex with invalid index.
     * @tc.expected: step3. the selected index is set to 0.
     */
    pattern->SetSelectedIndex(-1);
    EXPECT_EQ(pattern->selectedIndex_, 0);

    pattern->SetSelectedIndex(10);
    EXPECT_EQ(pattern->selectedIndex_, 0);
}

/**
 * @tc.name: ContainerPickerPatternTest_FireChangeEvent001
 * @tc.desc: Test FireChangeEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_FireChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set change event and test FireChangeEvent.
     * @tc.expected: step2. the change event is triggered with correct index.
     */
    int32_t testIndex = -1;
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnChange([&testIndex](const double& index) { testIndex = static_cast<int32_t>(index); });

    pattern->FireChangeEvent();
    EXPECT_EQ(testIndex, 0);

    pattern->selectedIndex_ = 3;
    pattern->FireChangeEvent();
    EXPECT_EQ(testIndex, 3);
}

/**
 * @tc.name: ContainerPickerPatternTest_FireScrollStopEvent001
 * @tc.desc: Test FireScrollStopEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_FireScrollStopEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set scroll stop event and test FireScrollStopEvent.
     * @tc.expected: step2. the scroll stop event is triggered with correct index.
     */
    int32_t testIndex = -1;
    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnScrollStop([&testIndex](const double& index) { testIndex = static_cast<int32_t>(index); });

    pattern->FireScrollStopEvent();
    EXPECT_EQ(testIndex, 0);

    pattern->selectedIndex_ = 3;
    pattern->FireScrollStopEvent();
    EXPECT_EQ(testIndex, 3);
}

/**
 * @tc.name: ContainerPickerPatternTest_IsLoop001
 * @tc.desc: Test IsLoop function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_IsLoop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set canLoop property to true and test IsLoop.
     * @tc.expected: step2. IsLoop returns true.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCanLoop(true);

    // Set totalItemCount larger than displayCount_
    pattern->totalItemCount_ = 10;
    pattern->displayCount_ = 5;
    EXPECT_TRUE(pattern->IsLoop());

    /**
     * @tc.steps: step3. set canLoop property to false and test IsLoop.
     * @tc.expected: step3. IsLoop returns false.
     */
    layoutProperty->UpdateCanLoop(false);
    EXPECT_FALSE(pattern->IsLoop());
}

/**
 * @tc.name: ContainerPickerPatternTest_CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CreateLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test CreateLayoutAlgorithm.
     * @tc.expected: step2. returns a valid ContainerPickerLayoutAlgorithm.
     */
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<ContainerPickerLayoutAlgorithm>(layoutAlgorithm));
}

/**
 * @tc.name: ContainerPickerPatternTest_CreateNodePaintMethod001
 * @tc.desc: Test CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test CreateNodePaintMethod.
     * @tc.expected: step2. returns a valid ContainerPickerPaintMethod.
     */
    auto paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_SetContentMainSize001
 * @tc.desc: Test SetContentMainSize function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_SetContentMainSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test SetContentMainSize.
     * @tc.expected: step2. contentMainSize is set correctly.
     */
    pattern->SetContentMainSize(100.0f);
    EXPECT_EQ(pattern->contentMainSize_, 100.0f);

    pattern->SetContentMainSize(200.0f);
    EXPECT_EQ(pattern->contentMainSize_, 200.0f);
}

} // namespace OHOS::Ace::NG
