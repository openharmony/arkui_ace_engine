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
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_paint_method.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ContainerPickerPatternTestTwo : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateContainerPickerNode();
    RefPtr<FrameNode> CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern);
};

void ContainerPickerPatternTestTwo::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PickerTheme>()));
}

void ContainerPickerPatternTestTwo::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerPickerPatternTestTwo::SetUp() {}

void ContainerPickerPatternTestTwo::TearDown() {}

RefPtr<FrameNode> ContainerPickerPatternTestTwo::CreateContainerPickerNode()
{
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

RefPtr<FrameNode> ContainerPickerPatternTestTwo::CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern)
{
    auto frameNode = FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

/**
 * @tc.name: ContainerPickerPatternTest_HandleTargetIndex001
 * @tc.desc: Test HandleTargetIndex function with valid target index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_HandleTargetIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup test data and call HandleTargetIndex with valid index.
     * @tc.expected: step2. function handles target index correctly.
     */
    pattern->selectedIndex_ = 1;
    pattern->totalItemCount_ = 5;
    pattern->itemHeight_ = 100.0f;
    pattern->middleItemOffset_ = 250.0f;
    pattern->currentOffset_ = 150.0f;

    pattern->HandleTargetIndex(3);
    EXPECT_EQ(pattern->targetIndex_, 3);
    EXPECT_FALSE(pattern->isDragging_);
}

/**
 * @tc.name: ContainerPickerPatternTest_ShortestDistanceBetweenCurrentAndTarget001
 * @tc.desc: Test ShortestDistanceBetweenCurrentAndTarget function with different indices
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_ShortestDistanceBetweenCurrentAndTarget001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test ShortestDistanceBetweenCurrentAndTarget with different current and target indices.
     * @tc.expected: step2. function calculates shortest distance correctly.
     */
    // Test with non-loop mode
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(1, 3), 2);
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(3, 1), -2);

    // Test with loop mode
    pattern->isLoop_ = true;
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(1, 3), 2);
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(3, 1), -2);
    // Test shorter path in loop mode
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(0, 4), -1);
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(4, 0), 1);
}

/**
 * @tc.name: ContainerPickerPatternTest_StopSpringAnimation001
 * @tc.desc: Test StopSpringAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_StopSpringAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup spring animation and call StopSpringAnimation.
     * @tc.expected: step2. spring animation is stopped correctly.
     */
    pattern->springAnimation_ = AceType::MakeRefPtr<SpringAnimation>();
    pattern->isSpringAnimationRunning_ = true;

    pattern->StopSpringAnimation();
    EXPECT_FALSE(pattern->isSpringAnimationRunning_);
}

/**
 * @tc.name: ContainerPickerPatternTest_StopTargetAnimation001
 * @tc.desc: Test StopTargetAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_StopTargetAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup target animation and call StopTargetAnimation.
     * @tc.expected: step2. target animation is stopped correctly.
     */
    pattern->targetAnimation_ = AceType::MakeRefPtr<Animator>();
    pattern->isTargetAnimationRunning_ = true;

    pattern->StopTargetAnimation();
    EXPECT_FALSE(pattern->isTargetAnimationRunning_);
}

/**
 * @tc.name: ContainerPickerPatternTest_UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset function with different delta values
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_UpdateCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test UpdateCurrentOffset with different delta values.
     * @tc.expected: step2. current offset is updated correctly.
     */
    pattern->currentOffset_ = 100.0f;
    pattern->UpdateCurrentOffset(50.0f);
    EXPECT_EQ(pattern->currentOffset_, 150.0f);

    pattern->UpdateCurrentOffset(-70.0f);
    EXPECT_EQ(pattern->currentOffset_, 80.0f);
}

/**
 * @tc.name: ContainerPickerPatternTest_IsOutOfBoundary001
 * @tc.desc: Test IsOutOfBoundary function with different positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_IsOutOfBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test IsOutOfBoundary with different positions.
     * @tc.expected: step2. function correctly identifies boundary conditions.
     */
    pattern->itemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->displayCount_ = 3;
    pattern->middleItemOffset_ = 200.0f;
    pattern->selectedIndex_ = 2;

    // Test within boundary
    EXPECT_FALSE(pattern->IsOutOfBoundary(200.0f, 0.0f));

    // Test out of start boundary
    EXPECT_TRUE(pattern->IsOutOfBoundary(200.0f, -150.0f));

    // Test out of end boundary
    EXPECT_TRUE(pattern->IsOutOfBoundary(200.0f, 150.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_IsOutOfStart001
 * @tc.desc: Test IsOutOfStart function with different positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_IsOutOfStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test IsOutOfStart with different positions.
     * @tc.expected: step2. function correctly identifies start boundary conditions.
     */
    pattern->itemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->displayCount_ = 3;
    pattern->middleItemOffset_ = 200.0f;
    pattern->selectedIndex_ = 2;

    // Test within boundary
    EXPECT_FALSE(pattern->IsOutOfStart(200.0f, 0.0f));

    // Test out of start boundary
    EXPECT_TRUE(pattern->IsOutOfStart(200.0f, -150.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_IsOutOfEnd001
 * @tc.desc: Test IsOutOfEnd function with different positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_IsOutOfEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test IsOutOfEnd with different positions.
     * @tc.expected: step2. function correctly identifies end boundary conditions.
     */
    pattern->itemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->displayCount_ = 3;
    pattern->middleItemOffset_ = 200.0f;
    pattern->selectedIndex_ = 2;

    // Test within boundary
    EXPECT_FALSE(pattern->IsOutOfEnd(200.0f, 0.0f));

    // Test out of end boundary
    EXPECT_TRUE(pattern->IsOutOfEnd(200.0f, 150.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_SpringOverScroll001
 * @tc.desc: Test SpringOverScroll function with different delta values
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_SpringOverScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test SpringOverScroll with different delta values.
     * @tc.expected: step2. function processes overscroll with spring effect correctly.
     */
    pattern->springFactor_ = 0.5f;
    pattern->middleItemOffset_ = 200.0f;
    pattern->itemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->displayCount_ = 3;

    float delta1 = -200.0f; // Over scroll to start
    pattern->SpringOverScroll(delta1, 0, 0);
    EXPECT_LT(delta1, 0); // Should be adjusted but still negative

    float delta2 = 200.0f; // Over scroll to end
    pattern->SpringOverScroll(delta2, 4, 0);
    EXPECT_GT(delta2, 0); // Should be adjusted but still positive
}

/**
 * @tc.name: ContainerPickerPatternTest_CheckDragOutOfBoundary001
 * @tc.desc: Test CheckDragOutOfBoundary function with different drag positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_CheckDragOutOfBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test CheckDragOutOfBoundary with different drag positions.
     * @tc.expected: step2. function correctly checks for drag out of boundary conditions.
     */
    pattern->itemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->displayCount_ = 3;
    pattern->middleItemOffset_ = 200.0f;

    // Test drag within boundary
    EXPECT_FALSE(pattern->CheckDragOutOfBoundary(0, 200.0f, 0.0f));
    EXPECT_FALSE(pattern->CheckDragOutOfBoundary(4, 200.0f, 0.0f));

    // Test drag out of start boundary
    EXPECT_TRUE(pattern->CheckDragOutOfBoundary(0, 200.0f, -50.0f));

    // Test drag out of end boundary
    EXPECT_TRUE(pattern->CheckDragOutOfBoundary(4, 200.0f, 50.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_CreateSpringProperty001
 * @tc.desc: Test CreateSpringProperty function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_CreateSpringProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call CreateSpringProperty and verify springProperty_ is created.
     * @tc.expected: step2. springProperty_ is not null after creation.
     */
    pattern->springProperty_ = nullptr;
    pattern->CreateSpringProperty();
    EXPECT_NE(pattern->springProperty_, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_PlaySpringAnimation001
 * @tc.desc: Test PlaySpringAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_PlaySpringAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup spring animation properties and call PlaySpringAnimation.
     * @tc.expected: step2. spring animation is played.
     */
    pattern->CreateSpringProperty();
    pattern->springAnimation_ = AceType::MakeRefPtr<SpringAnimation>();
    pattern->isSpringAnimationRunning_ = false;

    // We can't directly verify the animation is played, but we check the function completes
    pattern->PlaySpringAnimation();
}

/**
 * @tc.name: ContainerPickerPatternTest_PlayTargetAnimation001
 * @tc.desc: Test PlayTargetAnimation function with valid target index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_PlayTargetAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup animation properties and call PlayTargetAnimation.
     * @tc.expected: step2. target animation is played.
     */
    pattern->selectedIndex_ = 1;
    pattern->targetIndex_ = 3;
    pattern->itemHeight_ = 100.0f;
    pattern->currentOffset_ = 100.0f;
    pattern->middleItemOffset_ = 200.0f;
    pattern->totalItemCount_ = 5;

    // We can't directly verify the animation is played, but we check the function completes
    pattern->PlayTargetAnimation();
}

/**
 * @tc.name: ContainerPickerPatternTest_CalcEndOffset001
 * @tc.desc: Test CalcEndOffset function with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_CalcEndOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test CalcEndOffset with different parameters.
     * @tc.expected: step2. end offset is calculated correctly.
     */
    pattern->itemHeight_ = 100.0f;
    pattern->middleItemOffset_ = 200.0f;

    float endOffset1 = pattern->CalcEndOffset(100.0f, 3);
    EXPECT_TRUE(NearEqual(endOffset1, 400.0f));

    float endOffset2 = pattern->CalcEndOffset(150.0f, 2);
    EXPECT_TRUE(NearEqual(endOffset2, 350.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_CreateTargetAnimation001
 * @tc.desc: Test CreateTargetAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_CreateTargetAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call CreateTargetAnimation and verify targetAnimation_ is created.
     * @tc.expected: step2. targetAnimation_ is not null after creation.
     */
    pattern->targetAnimation_ = nullptr;
    pattern->CreateTargetAnimation();
    EXPECT_NE(pattern->targetAnimation_, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_CreateSpringtAnimation001
 * @tc.desc: Test CreateSpringtAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_CreateSpringtAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call CreateSpringtAnimation and verify springAnimation_ is created.
     * @tc.expected: step2. springAnimation_ is not null after creation.
     */
    pattern->springAnimation_ = nullptr;
    pattern->springProperty_ = nullptr;
    pattern->CreateSpringProperty();
    pattern->CreateSpringtAnimation();
    EXPECT_NE(pattern->springAnimation_, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_CalculateMiddleLineOffset001
 * @tc.steps: step1. create picker and get pattern.
 * @tc.desc: Test CalculateMiddleLineOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerPatternTest_CalculateMiddleLineOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test CalculateMiddleLineOffset with different parameters.
     * @tc.expected: step2. middle line offset is calculated correctly.
     */
    pattern->itemHeight_ = 100.0f;
    pattern->displayCount_ = 3;

    float offset1 = pattern->CalculateMiddleLineOffset(0, 0.0f);
    EXPECT_TRUE(NearEqual(offset1, 150.0f));

    float offset2 = pattern->CalculateMiddleLineOffset(2, 50.0f);
    EXPECT_TRUE(NearEqual(offset2, 350.0f));
}

} // namespace OHOS::Ace::NG