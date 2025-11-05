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
#include "core/components_ng/pattern/container_picker/container_picker_paint_method.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"
#include "core/components_ng/pattern/container_picker/container_picker_utils.h"
#include "core/components_ng/pattern/image/image_pattern.h"
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
    RefPtr<FrameNode> CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern);
    void CreateItemPosition() const;
};

void ContainerPickerPatternTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerPickerTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerPickerPatternTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    TestNG::TearDownTestSuite();
}

void ContainerPickerPatternTest::CreateItemPosition() const
{
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    float itemHeight = 100.0f;
    int32_t total = 5;
    for (int32_t i = 0; i < total; ++i) {
        pattern->itemPosition_[i] = { itemHeight * i, itemHeight * (i + 1), nullptr };
    }
}

void ContainerPickerPatternTest::SetUp() {}

void ContainerPickerPatternTest::TearDown() {}

RefPtr<FrameNode> ContainerPickerPatternTest::CreateContainerPickerNode()
{
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->InitDefaultParams();
    pattern->isLoop_ = true;
    return frameNode;
}

RefPtr<FrameNode> ContainerPickerPatternTest::CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern)
{
    auto frameNode = FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
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
HWTEST_F(ContainerPickerPatternTest, ContainerPickerUtilsCalcCurrentMiddleItemTest001, TestSize.Level0)
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
    pattern->selectedIndex_ = 1;
    pattern->SetSelectedIndex(3);
    EXPECT_EQ(pattern->selectedIndex_, 3);

    /**
     * @tc.steps: step3. test SetSelectedIndex with invalid index.
     * @tc.expected: step3. the selected index is set to 0.
     */
    pattern->SetSelectedIndex(-1);
    EXPECT_EQ(pattern->selectedIndex_, -1);

    pattern->SetSelectedIndex(10);
    EXPECT_EQ(pattern->selectedIndex_, 10);
}

/**
 * @tc.name: ContainerPickerPatternTest_SetTargetIndex001
 * @tc.desc: Test SetTargetIndex function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_SetTargetIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set totalItemCount and test SetTargetIndex with valid index.
     * @tc.expected: step2. the target index is set correctly.
     */
    pattern->totalItemCount_ = 5;
    pattern->selectedIndex_ = 1;
    pattern->SetTargetIndex(3);
    EXPECT_EQ(pattern->targetIndex_, 3);

    /**
     * @tc.steps: step3. test SetTargetIndex with invalid index.
     * @tc.expected: step3. the target index is set to 0.
     */
    pattern->SetTargetIndex(-1);
    EXPECT_EQ(pattern->targetIndex_, 0);

    pattern->SetTargetIndex(10);
    EXPECT_EQ(pattern->targetIndex_, 0);
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

/**
 * @tc.name: ContainerPickerPatternTest_CreateChildrenClickEvent_VerifyEventRegistration001
 * @tc.desc: Verify that CreateChildrenClickEvent correctly registers click events for supported node types.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CreateChildrenClickEvent_VerifyEventRegistration001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and mock gesture event hub.
     */
    auto containerPickerNode = CreateContainerPickerNode();
    auto pattern = containerPickerNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create child nodes with different tags and set up mock event hubs.
     */
    auto rowNode = CreateChildNode(V2::ROW_ETS_TAG, AceType::MakeRefPtr<Pattern>());
    auto imageNode = CreateChildNode(V2::IMAGE_ETS_TAG, AceType::MakeRefPtr<ImagePattern>());
    auto textNode = CreateChildNode(V2::TEXT_ETS_TAG, AceType::MakeRefPtr<TextPattern>());
    auto symbolNode = CreateChildNode(V2::SYMBOL_ETS_TAG, AceType::MakeRefPtr<Pattern>());

    containerPickerNode->AddChild(rowNode);
    containerPickerNode->AddChild(imageNode);
    containerPickerNode->AddChild(textNode);
    containerPickerNode->AddChild(symbolNode);

    RefPtr<UINode> pickerUiNode = AceType::DynamicCast<UINode>(containerPickerNode);
    ASSERT_NE(pickerUiNode, nullptr);
    EXPECT_FALSE(pickerUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);

    pattern->CreateChildrenClickEvent();
    EXPECT_TRUE(pickerUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);
}

/**
 * @tc.name: ContainerPickerPatternTest_InitMouseAndPressEvent_VerifyEventCreation001
 * @tc.desc: Verify that InitMouseAndPressEvent correctly creates mouse and press events.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_InitMouseAndPressEvent_VerifyEventCreation001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and pattern.
     */
    auto containerPickerNode = CreateContainerPickerNode();
    auto pattern = containerPickerNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Verify initial state of isItemClickEventCreated_.
     */
    EXPECT_FALSE(pattern->isItemClickEventCreated_);

    /**
     * @tc.steps: step3. Call InitMouseAndPressEvent and verify event creation flag is set.
     */
    pattern->InitMouseAndPressEvent();
    EXPECT_TRUE(pattern->isItemClickEventCreated_);
}

/**
 * @tc.name: ContainerPickerPatternTest_CustomizeSafeAreaPadding001
 * @tc.desc: Test CustomizeSafeAreaPadding function with different safe area configurations
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CustomizeSafeAreaPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set safe area padding with values and test CustomizeSafeAreaPadding.
     * @tc.expected: step2. top and bottom padding are reset to nullopt.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set initial padding values
    PaddingPropertyF padding { 10, 10, 10, 10 };
    PaddingPropertyF padding1 = pattern->CustomizeSafeAreaPadding(padding, false);

    // Verify results
    EXPECT_EQ(padding1.top, std::nullopt);
    EXPECT_EQ(padding1.bottom, std::nullopt);
    EXPECT_EQ(padding1.left, 10);
    EXPECT_EQ(padding1.right, 10);

    PaddingPropertyF padding2 = pattern->CustomizeSafeAreaPadding(padding, true);

    // Verify results
    EXPECT_EQ(padding2.top, 10);
    EXPECT_EQ(padding2.bottom, 10);
    EXPECT_EQ(padding2.left, std::nullopt);
    EXPECT_EQ(padding2.right, std::nullopt);
}

/**
 * @tc.name: ContainerPickerPatternTest_SwipeTo001
 * @tc.desc: Test SwipeTo function with valid target index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_SwipeTo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test SwipeTo with valid target index.
     * @tc.expected: step2. function sets targetIndex_ and marks as dirty.
     */
    pattern->selectedIndex_ = 1;
    pattern->isAnimationRunning_ = false;

    // Call function under test
    pattern->SwipeTo(3);

    // Verify results
    EXPECT_EQ(pattern->targetIndex_, 3);
    // We can't directly verify PickerMarkDirty is called, but we check targetIndex_ is set
}

/**
 * @tc.name: ContainerPickerPatternTest_SwipeTo002
 * @tc.desc: Test SwipeTo function with edge cases
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_SwipeTo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test SwipeTo with edge cases.
     * @tc.expected: step2. function handles edge cases correctly.
     */
    // Test with same index as current selection
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = 0; // Different initial targetIndex_
    pattern->isAnimationRunning_ = false;

    pattern->SwipeTo(2);
    EXPECT_EQ(pattern->targetIndex_, 0); // Should not change targetIndex_

    // Test with animation already running
    pattern->selectedIndex_ = 1;
    pattern->targetIndex_ = 0; // Different from selectedIndex_
    pattern->isAnimationRunning_ = true;

    pattern->SwipeTo(3);
    EXPECT_EQ(pattern->targetIndex_, 0); // Should not change targetIndex_ when animation is running
}

/**
 * @tc.name: ContainerPickerPatternTest_OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function under normal conditions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto textNode1 = CreateChildNode(V2::TEXT_ETS_TAG, AceType::MakeRefPtr<TextPattern>());
    frameNode->AddChild(textNode1);
    auto textNode2 = CreateChildNode(V2::TEXT_ETS_TAG, AceType::MakeRefPtr<TextPattern>());
    frameNode->AddChild(textNode2);
    auto textNode3 = CreateChildNode(V2::TEXT_ETS_TAG, AceType::MakeRefPtr<TextPattern>());
    frameNode->AddChild(textNode3);

    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto algorithm = AceType::MakeRefPtr<ContainerPickerLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);

    auto firstChild = AccessibilityManager::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    firstGeometryNode->Reset();
    auto firstLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(firstChild, firstGeometryNode, firstChild->GetLayoutProperty());
    dirty->AppendChild(firstLayoutWrapper);

    /**
     * @tc.steps: step2. setup test data and call OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. function processes correctly and returns false.
     */
    pattern->currentDelta_ = 10.0f;
    pattern->isNeedPlayInertialAnimation_ = false;

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;

    bool result = pattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern->currentDelta_, 0.0f);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function with skip flags
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. setup test data with skip flags and call OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. function returns false when all skip flags are true and no animation.
     */
    pattern->isNeedPlayInertialAnimation_ = false;

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test OnDirtyLayoutWrapperSwap function when isModified_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. setup test data with skip flags and call OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. function returns true when isModified_ is true.
     */
    pattern->isNeedPlayInertialAnimation_ = true;
    pattern->isModified_ = true;

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;

    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(result);
    EXPECT_FALSE(pattern->isModified_);
}

/**
 * @tc.name: ContainerPickerPatternTest_HandleDragStart001
 * @tc.desc: Test HandleDragStart function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_HandleDragStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. create gesture event and call HandleDragStart.
     * @tc.expected: step2. drag state variables are initialized correctly.
     */
    GestureEvent info;
    info.SetLocalLocation(Offset(100.0, 200.0));

    pattern->HandleDragStart(info);
    EXPECT_TRUE(pattern->isDragging_);
    EXPECT_EQ(pattern->mainDeltaSum_, 0.0f);
    EXPECT_EQ(pattern->yLast_, 200.0f);
}

/**
 * @tc.name: ContainerPickerPatternTest_GetCurrentTime001
 * @tc.desc: Test GetCurrentTime function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_GetCurrentTime001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call GetCurrentTime and verify it returns a valid time.
     * @tc.expected: step2. current time is positive and reasonable.
     */
    double currentTime = pattern->GetCurrentTime();
    EXPECT_GT(currentTime, 0.0);

    // Verify time advances
    double timeLater = pattern->GetCurrentTime();
    EXPECT_GE(timeLater, currentTime);
}

/**
 * @tc.name: ContainerPickerPatternTest_Play001
 * @tc.desc: Test Play function with valid velocity
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_Play001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup test data and call Play with valid velocity.
     * @tc.expected: step2. function returns true and sets isNeedPlayInertialAnimation_.
     */
    pattern->dragStartTime_ = pattern->GetCurrentTime() - 2.0; // More than MIN_TIME
    pattern->dragEndTime_ = pattern->GetCurrentTime();

    bool result = pattern->Play(1000.0); // Velocity above threshold

    EXPECT_TRUE(result);
    EXPECT_TRUE(pattern->isNeedPlayInertialAnimation_);
}

/**
 * @tc.name: ContainerPickerPatternTest_Play002
 * @tc.desc: Test Play function with invalid conditions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_Play002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test Play with various invalid conditions.
     * @tc.expected: step2. function returns false for invalid conditions.
     */
    // Test with time difference less than MIN_TIME
    pattern->dragStartTime_ = pattern->GetCurrentTime() - 0.5; // Less than MIN_TIME
    pattern->dragEndTime_ = pattern->GetCurrentTime();

    bool result1 = pattern->Play(1000.0);
    EXPECT_FALSE(result1);

    // Test with velocity below threshold
    pattern->dragStartTime_ = pattern->GetCurrentTime() - 2.0; // More than MIN_TIME
    pattern->dragEndTime_ = pattern->GetCurrentTime();

    bool result2 = pattern->Play(100.0); // Velocity below threshold
    EXPECT_FALSE(result2);
}

/**
 * @tc.name: ContainerPickerPatternTest_HandleDragEnd001
 * @tc.desc: Test HandleDragEnd function with valid velocity
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_HandleDragEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup test data and call HandleDragEnd.
     * @tc.expected: step2. drag state is updated and animation may be triggered.
     */
    pattern->isDragging_ = true;
    pattern->isLoop_ = false;
    pattern->animationCreated_ = true;

    pattern->HandleDragEnd(500.0, 0.0f);

    EXPECT_FALSE(pattern->isDragging_);
}

/**
 * @tc.name: ContainerPickerPatternTest_HandleDragUpdate001
 * @tc.desc: Test HandleDragUpdate function with valid gesture event
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_HandleDragUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup test data and call HandleDragUpdate.
     * @tc.expected: step2. drag state is updated correctly.
     */
    pattern->yLast_ = 100.0f;
    pattern->mainDeltaSum_ = 0.0f;
    pattern->currentDelta_ = 0.0f;
    pattern->contentMainSize_ = 200.0f;
    pattern->itemPosition_[0] = { 0.0f, 100.0f, nullptr };

    GestureEvent info;
    info.SetLocalLocation(Offset(50.0, 150.0));
    info.SetMainDelta(50.0f);
    info.SetMainVelocity(200.0f);

    pattern->HandleDragUpdate(info);

    EXPECT_EQ(pattern->mainDeltaSum_, 50.0f);
    EXPECT_EQ(pattern->currentDelta_, -50.0f);
    EXPECT_EQ(pattern->yLast_, 150.0f);
}

/**
 * @tc.name: ContainerPickerPatternTest_CreateScrollProperty001
 * @tc.desc: Test CreateScrollProperty function for initial animation setup
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CreateScrollProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. ensure animationCreated_ is false and call CreateScrollProperty.
     * @tc.expected: step2. animation is created and animationCreated_ is set to true.
     */
    pattern->animationCreated_ = false;

    pattern->CreateScrollProperty();

    EXPECT_TRUE(pattern->animationCreated_);
    EXPECT_NE(pattern->scrollProperty_, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_StopAnimation001
 * @tc.desc: Test StopAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_StopAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup snapOffsetProperty_ and call StopAnimation.
     * @tc.expected: step2. toss status is stopped and animation is reset.
     */
    pattern->isAnimationRunning_ = true;
    pattern->lastAnimationScroll_ = 100.0f;
    pattern->CreateScrollProperty();
    pattern->CreateSpringAnimation(0.0f);

    pattern->StopAnimation();

    EXPECT_FALSE(pattern->isAnimationRunning_);
}

/**
 * @tc.name: ContainerPickerPatternTest_PickerMarkDirty001
 * @tc.desc: Test PickerMarkDirty function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_PickerMarkDirty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test PickerMarkDirty with different crossMatchChild_ values.
     * @tc.expected: step2. node is marked dirty with appropriate flags.
     */
    // We can't directly verify the specific dirty flags, but we check the function completes
    pattern->crossMatchChild_ = false;
    pattern->PickerMarkDirty();

    pattern->crossMatchChild_ = true;
    pattern->PickerMarkDirty();
}

/**
 * @tc.name: ContainerPickerPatternTest_PostIdleTask_EmptyOffScreenItems001
 * @tc.desc: Test PostIdleTask function with empty offScreenItemsIndex_
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_PostIdleTask_EmptyOffScreenItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Ensure offScreenItemsIndex_ is empty and call PostIdleTask.
     * @tc.expected: step2. Function should return immediately without adding any task.
     */
    pattern->offScreenItemsIndex_.clear();
    auto pipe = MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(pipe);

    pattern->PostIdleTask(frameNode);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_AccumulatingTerminateHelper001
 * @tc.desc: Test AccumulatingTerminateHelper function with normal case
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_AccumulatingTerminateHelper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up parameters and call AccumulatingTerminateHelper.
     * @tc.expected: step2. Function returns true and updates totalExpand correctly.
     */
    frameNode->isScrollableAxis_ = false;
    ExpandEdges padding { 10, 20, 30, 40 };
    RectF rect {};

    // Call function under test
    bool result = pattern->AccumulatingTerminateHelper(rect, padding);

    // Verify results
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ContainerPickerPatternTest_AccumulatingTerminateHelper_ScrollableAxisInsensitive002
 * @tc.desc: Test AccumulatingTerminateHelper function when host is scrollable axis insensitive
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest,
    ContainerPickerPatternTest_AccumulatingTerminateHelper_ScrollableAxisInsensitive002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Mock IsScrollableAxisInsensitive to return true and call AccumulatingTerminateHelper.
     * @tc.expected: step2. Function returns false.
     */
    frameNode->isScrollableAxis_ = true;
    ExpandEdges padding { 10, 20, 30, 40 };
    RectF rect {};

    // Call function under test
    bool result = pattern->AccumulatingTerminateHelper(rect, padding);

    // Verify results
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ContainerPickerPatternCreateNodePaintMethodTest001
 * @tc.desc: Test that ContainerPickerPattern::CreateNodePaintMethod returns non-null object
 * @tc.type: FUNC
 */
TEST_F(ContainerPickerPatternTest, ContainerPickerPatternCreateNodePaintMethodTest001)
{
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    // Act
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();

    // Assert
    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternCreateNodePaintMethodTest002
 * @tc.desc: Test that ContainerPickerPattern::CreateNodePaintMethod returns object of correct type
 * @tc.type: FUNC
 */
TEST_F(ContainerPickerPatternTest, ContainerPickerPatternCreateNodePaintMethodTest002)
{
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    // Act
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    RefPtr<ContainerPickerPaintMethod> containerPickerPaintMethod =
        AceType::DynamicCast<ContainerPickerPaintMethod>(paintMethod);

    // Assert
    EXPECT_NE(containerPickerPaintMethod, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternCreateNodePaintMethodTest003
 * @tc.desc: Test that ContainerPickerPattern::CreateNodePaintMethod returns different instances on multiple calls
 * @tc.type: FUNC
 */
TEST_F(ContainerPickerPatternTest, ContainerPickerPatternCreateNodePaintMethodTest003)
{
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    // Act
    RefPtr<NodePaintMethod> paintMethod1 = pattern->CreateNodePaintMethod();
    RefPtr<NodePaintMethod> paintMethod2 = pattern->CreateNodePaintMethod();

    // Assert
    EXPECT_NE(paintMethod1, paintMethod2);
}

/**
 * @tc.name: ContainerPickerPatternTest_IsEnableHaptic_HostIsNull001
 * @tc.desc: Test IsEnableHaptic function when host is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_IsEnableHaptic_HostIsNull001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pattern without setting host
     */
    auto pattern = AceType::MakeRefPtr<ContainerPickerPattern>();

    /**
     * @tc.steps: step2. call IsEnableHaptic and verify result
     * @tc.expected: step2. function returns true when host is null
     */
    bool result = pattern->IsEnableHaptic();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ContainerPickerPatternTest_IsEnableHaptic_EnableTrue001
 * @tc.desc: Test IsEnableHaptic function when haptic feedback is enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_IsEnableHaptic_EnableTrue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pattern with haptic feedback enabled
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto props = pattern->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(props, nullptr);
    props->UpdateEnableHapticFeedback(true);

    /**
     * @tc.steps: step2. call IsEnableHaptic and verify result
     * @tc.expected: step2. function returns true when haptic feedback is enabled
     */
    bool result = pattern->IsEnableHaptic();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ContainerPickerPatternTest_IsEnableHaptic_EnableFalse001
 * @tc.desc: Test IsEnableHaptic function when haptic feedback is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_IsEnableHaptic_EnableFalse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pattern with haptic feedback disabled
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto props = pattern->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(props, nullptr);
    props->UpdateEnableHapticFeedback(false);

    /**
     * @tc.steps: step2. call IsEnableHaptic and verify result
     * @tc.expected: step2. function returns false when haptic feedback is disabled
     */
    bool result = pattern->IsEnableHaptic();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ContainerPickerPatternTest_InitOrRefreshHapticController_Init001
 * @tc.desc: Test InitOrRefreshHapticController function to initialize haptic controller
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_InitOrRefreshHapticController_Init001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pattern with haptic enabled but no controller
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto props = pattern->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(props, nullptr);
    props->UpdateEnableHapticFeedback(true);
    pattern->hapticController_ = nullptr;

    /**
     * @tc.steps: step2. call InitOrRefreshHapticController and verify isEnableHaptic_ is updated
     * @tc.expected: step2. isEnableHaptic_ is set to true and hapticController_ is not nullptr.
     */
    pattern->InitOrRefreshHapticController();
    EXPECT_TRUE(pattern->isEnableHaptic_);
    EXPECT_NE(pattern->hapticController_, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_InitOrRefreshHapticController_Stop001
 * @tc.desc: Test InitOrRefreshHapticController function to stop haptic controller
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_InitOrRefreshHapticController_Stop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pattern with haptic disabled but has controller
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto props = pattern->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(props, nullptr);
    props->UpdateEnableHapticFeedback(false);

    /**
     * @tc.steps: step2. call InitOrRefreshHapticController and verify result
     * @tc.expected: step2. isEnableHaptic_ is set to false and hapticController_ is nullptr
     */
    pattern->InitOrRefreshHapticController();
    EXPECT_FALSE(pattern->isEnableHaptic_);
    EXPECT_EQ(pattern->hapticController_, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_HandleTargetIndex001
 * @tc.desc: Test HandleTargetIndex function with valid target index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_HandleTargetIndex001, TestSize.Level1)
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
    pattern->pickerItemHeight_ = 100.0f;
    CreateItemPosition();
    pattern->currentOffset_ = 150.0f;
    pattern->targetIndex_ = 3;
    pattern->HandleTargetIndex();
    EXPECT_FALSE(pattern->targetIndex_.has_value());
    EXPECT_FALSE(pattern->isDragging_);
}

/**
 * @tc.name: ContainerPickerPatternTest_ShortestDistanceBetweenCurrentAndTarget001
 * @tc.desc: Test ShortestDistanceBetweenCurrentAndTarget function with different indices
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerPatternTest, ContainerPickerPatternTest_ShortestDistanceBetweenCurrentAndTarget001, TestSize.Level1)
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
    pattern->pickerItemHeight_ = 100.0f;
    pattern->height_ = 500.0f;
    CreateItemPosition();
    pattern->selectedIndex_ = 3;
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(4), 100.0f);
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(0), -300.0f);

    // Test with loop mode
    pattern->isLoop_ = true;
    EXPECT_EQ(pattern->ShortestDistanceBetweenCurrentAndTarget(0), 200.f);
}

/**
 * @tc.name: ContainerPickerPatternTest_UpdateCurrentOffset001
 * @tc.desc: Test UpdateCurrentOffset function with different delta values
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_UpdateCurrentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    CreateItemPosition();

    /**
     * @tc.steps: step2. test UpdateCurrentOffset with different delta values.
     * @tc.expected: step2. current offset is updated correctly.
     */
    pattern->currentOffset_ = 100.0f;
    pattern->UpdateCurrentOffset(50.0f);
    EXPECT_EQ(pattern->mainDeltaSum_, 50.0f);

    pattern->UpdateCurrentOffset(-70.0f);
    EXPECT_EQ(pattern->mainDeltaSum_, -20.0f);
}

/**
 * @tc.name: ContainerPickerPatternTest_IsOutOfBoundary001
 * @tc.desc: Test IsOutOfBoundary function with different positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_IsOutOfBoundary001, TestSize.Level1)
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
    pattern->height_ = 500.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    CreateItemPosition();

    // Test within boundary
    EXPECT_FALSE(pattern->IsOutOfBoundary(0.0f));

    // Test out of start boundary
    EXPECT_TRUE(pattern->IsOutOfBoundary(251.0f));

    // Test out of end boundary
    EXPECT_TRUE(pattern->IsOutOfBoundary(-251.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_IsOutOfStart001
 * @tc.desc: Test IsOutOfStart function with different positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_IsOutOfStart001, TestSize.Level1)
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
    pattern->height_ = 500.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    CreateItemPosition();

    // Test within boundary
    EXPECT_FALSE(pattern->IsOutOfStart(0.0f));

    // Test out of start boundary
    EXPECT_TRUE(pattern->IsOutOfStart(251.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_IsOutOfEnd001
 * @tc.desc: Test IsOutOfEnd function with different positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_IsOutOfEnd001, TestSize.Level1)
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
    pattern->height_ = 500.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    CreateItemPosition();

    // Test within boundary
    EXPECT_FALSE(pattern->IsOutOfEnd(0.0f));

    // Test out of end boundary
    EXPECT_TRUE(pattern->IsOutOfEnd(-251.0f));
}

/**
 * @tc.name: ContainerPickerPatternTest_SpringOverScroll001
 * @tc.desc: Test SpringOverScroll function with different delta values
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_SpringOverScroll001, TestSize.Level1)
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
    pattern->height_ = 500.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    CreateItemPosition();

    float delta1 = -301.0f; // Over scroll
    pattern->SpringOverScroll(delta1);
    EXPECT_TRUE(pattern->SpringOverScroll(delta1));

    float delta2 = 0.0f; // Not over scroll
    pattern->SpringOverScroll(delta2);
    EXPECT_FALSE(pattern->SpringOverScroll(delta2));
}

/**
 * @tc.name: ContainerPickerPatternTest_CheckDragOutOfBoundary001
 * @tc.desc: Test CheckDragOutOfBoundary not out of boundary
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CheckDragOutOfBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test CheckDragOutOfBoundary.
     * @tc.expected: step2. Not out of boundary.
     */
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    CreateItemPosition();

    // Test drag within boundary
    EXPECT_FALSE(pattern->CheckDragOutOfBoundary());
}

/**
 * @tc.name: ContainerPickerPatternTest_PlaySpringAnimation001
 * @tc.desc: Test PlaySpringAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_PlaySpringAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    CreateItemPosition();

    /**
     * @tc.steps: step2. setup spring animation properties and call PlaySpringAnimation.
     * @tc.expected: step2. spring animation is played.
     */
    pattern->CreateScrollProperty();
    pattern->CreateSpringAnimation(0.0f);
    pattern->isAnimationRunning_ = false;
    pattern->yLast_ = 100.0f;
    pattern->height_ = 500.0f;

    pattern->PlaySpringAnimation();
    EXPECT_TRUE(NearZero(pattern->yLast_));
}

/**
 * @tc.name: ContainerPickerPatternTest_PlayTargetAnimation001
 * @tc.desc: Test PlayTargetAnimation function with valid target index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_PlayTargetAnimation001, TestSize.Level1)
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
    CreateItemPosition();
    pattern->selectedIndex_ = 1;
    pattern->targetIndex_ = 3;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->currentOffset_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->yLast_ = 100.0f;

    pattern->PlayTargetAnimation();
    EXPECT_TRUE(NearZero(pattern->yLast_));
}

/**
 * @tc.name: ContainerPickerPatternTest_CalcEndOffset001
 * @tc.desc: Test CalcEndOffset function with different parameters
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CalcEndOffset001, TestSize.Level1)
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
    pattern->pickerItemHeight_ = 100.0f;
    CreateItemPosition();

    float endOffset1 = 100.0f;
    pattern->CalcEndOffset(endOffset1, 3);
    EXPECT_EQ(endOffset1, 50);

    float endOffset2 = 150.0f;
    pattern->CalcEndOffset(endOffset2, 2);
    EXPECT_EQ(endOffset2, 50);
}

/**
 * @tc.name: ContainerPickerPatternTest_CreateSpringAnimation001
 * @tc.desc: Test CreateSpringAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CreateSpringAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. call CreateSpringAnimation and verify springAnimation_ is created.
     * @tc.expected: step2. springAnimation_ is not null after creation.
     */
    pattern->CreateSpringAnimation(0.0f);
    EXPECT_NE(pattern->scrollAnimation_, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_CalculateMiddleLineOffset001
 * @tc.steps: step1. create picker and get pattern.
 * @tc.desc: Test CalculateMiddleLineOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CalculateMiddleLineOffset001, TestSize.Level1)
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
    pattern->height_ = 500.0f;
    pattern->pickerItemHeight_ = 100.0f;
    CreateItemPosition();

    float offset1 = pattern->CalculateMiddleLineOffset();
    EXPECT_EQ(offset1, 0);
}

/**
 * @tc.name: ContainerPickerPatternTest_SetDefaultTextStyle001
 * @tc.desc: Test SetDefaultTextStyle function with defaultColor parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_SetDefaultTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and text node, setup testing environment.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto textNode = CreateChildNode(V2::TEXT_ETS_TAG, textPattern);
    ASSERT_NE(textNode, nullptr);

    // Add text node as child
    frameNode->AddChild(textNode);

    /**
     * @tc.steps: step2. call SetDefaultTextStyle with defaultColor and verify text color is set correctly.
     * @tc.expected: step2. text color is updated to defaultColor and isUseDefaultFontColor_ is set to true.
     */
    Color defaultColor = Color::RED;
    pattern->SetDefaultTextStyle(textNode, defaultColor);

    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->GetTextColor().has_value());
    EXPECT_TRUE(textLayoutProperty->GetTextColor().value() == defaultColor);
    EXPECT_TRUE(pattern->isUseDefaultFontColor_);
    EXPECT_TRUE(pattern->isModified_);
}

/**
 * @tc.name: ContainerPickerPatternTest_UpdateDefaultTextStyle001
 * @tc.desc: Test UpdateDefaultTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_UpdateDefaultTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and text node, setup testing environment.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto textNode = CreateChildNode(V2::TEXT_ETS_TAG, textPattern);
    ASSERT_NE(textNode, nullptr);

    // Add text node as child
    frameNode->AddChild(textNode);

    /**
     * @tc.steps: step2. set isUseDefaultFontColor_ to true and call UpdateDefaultTextStyle.
     * @tc.expected: step2. text color is updated to new defaultColor.
     */
    pattern->isUseDefaultFontColor_ = true;
    Color newDefaultColor = Color::BLUE;
    pattern->UpdateDefaultTextStyle(textNode, newDefaultColor);

    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->GetTextColor().has_value());
    EXPECT_TRUE(textLayoutProperty->GetTextColor().value() == newDefaultColor);

    /**
     * @tc.steps: step3. set isUseDefaultFontColor_ to false and call UpdateDefaultTextStyle.
     * @tc.expected: step3. text color is not updated when isUseDefaultFontColor_ is false.
     */
    pattern->isUseDefaultFontColor_ = false;
    Color anotherColor = Color::GREEN;
    pattern->UpdateDefaultTextStyle(textNode, anotherColor);

    // Color should remain BLUE
    EXPECT_TRUE(textLayoutProperty->GetTextColor().value() == newDefaultColor);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate function when the value of isUseDefaultFontColor_ is different.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto textNode = CreateChildNode(V2::TEXT_ETS_TAG, textPattern);
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    Color textColor = Color::RED;
    textLayoutProperty->UpdateTextColor(textColor);

    // Add text node as child
    frameNode->AddChild(textNode);
    pattern->itemPosition_[0] = { 0.0f, 100.0f, nullptr };

    /**
     * @tc.steps: step2. set isUseDefaultFontColor_ to false and call OnColorConfigurationUpdate.
     * @tc.expected: step2. The value of textColor will not change.
     */
    pattern->isUseDefaultFontColor_ = false;
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(textLayoutProperty->GetTextColor().has_value());
    EXPECT_TRUE(textLayoutProperty->GetTextColor().value() == textColor);

    /**
     * @tc.steps: step3. set isUseDefaultFontColor_ to true and call OnColorConfigurationUpdate.
     * @tc.expected: step3. The value of textColor will be change.
     */
    pattern->isUseDefaultFontColor_ = true;
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(textLayoutProperty->GetTextColor().has_value());
    EXPECT_FALSE(textLayoutProperty->GetTextColor().value() == textColor);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_ClickBreak001
 * @tc.desc: Test OnAroundButtonClick function when clickBreak_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_ClickBreak001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set clickBreak_ to true and call OnAroundButtonClick.
     * @tc.expected: step2. function returns immediately without any action.
     */
    pattern->clickBreak_ = true;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->OnAroundButtonClick(100.0f);
    // Verify no action was taken
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_ClickOutOfVisibleArea001
 * @tc.desc: Test OnAroundButtonClick function when click is out of visible area
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_ClickOutOfVisibleArea001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click out of visible area.
     * @tc.expected: step2. function returns immediately without any action.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;

    // Click position is outside the visible area (more than height_/2 away from middle)
    float clickPosition = 500.0f; // Middle is at 200.0f, this is 300.0f away
    pattern->OnAroundButtonClick(clickPosition);
    // Verify no action was taken
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_ClickMiddleItem001
 * @tc.desc: Test OnAroundButtonClick function when click is on middle item
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_ClickMiddleItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click on middle item.
     * @tc.expected: step2. function returns immediately without any action.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;

    // Click position is on middle item (within pickerItemHeight_/2 of middle)
    float clickPosition = 220.0f; // Middle is at 200.0f, this is 20.0f away (less than 50.0f)
    pattern->OnAroundButtonClick(clickPosition);
    // Verify no action was taken
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_Level1Delta001
 * @tc.desc: Test OnAroundButtonClick function with level 1 delta (click in level 1 area)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_Level1Delta001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click in level 1 area.
     * @tc.expected: step2. function sets target index with delta 1.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;

    // Click position is in level 1 area (between 50.0f and 100.0f away from middle)
    float clickPosition = 270.0f; // Middle is at 200.0f, this is 70.0f away
    pattern->OnAroundButtonClick(clickPosition);

    // Verify target index is set correctly (selectedIndex_ + 1)
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 3);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_Level1DeltaNegative001
 * @tc.desc: Test OnAroundButtonClick function with negative level 1 delta (click above middle)
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_Level1DeltaNegative001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click above middle in level 1 area.
     * @tc.expected: step2. function sets target index with delta -1.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;

    float clickPosition = 130.0f; // Middle is at 200.0f, this is -70.0f away
    pattern->OnAroundButtonClick(clickPosition);
    // Verify target index is set correctly (selectedIndex_ - 1)
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 1);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_Level2Delta001
 * @tc.desc: Test OnAroundButtonClick function with level 2 delta (click in level 2 area)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_Level2Delta001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click in level 2 area.
     * @tc.expected: step2. function sets target index with delta 2.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;
    pattern->secondAdjacentItemHeight_ = 50.0f;

    float clickPosition = 320.0f; // Middle is at 200.0f, this is 120.0f away
    pattern->OnAroundButtonClick(clickPosition);
    // Verify target index is set correctly (selectedIndex_ + 2)
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 4);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_Level2DeltaNegative001
 * @tc.desc: Test OnAroundButtonClick function with negative level 2 delta (click above middle in level 2 area)
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_Level2DeltaNegative001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click above middle in level 2 area.
     * @tc.expected: step2. function sets target index with delta -2.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;
    pattern->secondAdjacentItemHeight_ = 50.0f;

    float clickPosition = 80.0f; // Middle is at 200.0f, this is -120.0f away
    pattern->OnAroundButtonClick(clickPosition);
    // Verify target index is set correctly (selectedIndex_ - 2)
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 0);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_Level3Delta001
 * @tc.desc: Test OnAroundButtonClick function with level 3 delta (click in level 3 area)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_Level3Delta001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click in level 3 area.
     * @tc.expected: step2. function sets target index with delta 3.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;
    pattern->secondAdjacentItemHeight_ = 50.0f;
    pattern->thirdAdjacentItemHeight_ = 50.0f;

    float clickPosition = 370.0f; // Middle is at 200.0f, this is 170.0f away
    pattern->OnAroundButtonClick(clickPosition);
    // Verify target index is set correctly (selectedIndex_ + 3)
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 5);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_Level3DeltaNegative001
 * @tc.desc: Test OnAroundButtonClick function with negative level 3 delta (click above middle in level 3 area)
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_Level3DeltaNegative001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click above middle in level 3 area.
     * @tc.expected: step2. function sets target index with delta -3.
     */
    pattern->clickBreak_ = false;
    pattern->totalItemCount_ = 5;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;
    pattern->secondAdjacentItemHeight_ = 50.0f;
    pattern->thirdAdjacentItemHeight_ = 50.0f;

    float clickPosition = 30.0f; // Middle is at 200.0f, this is -170.0f away
    pattern->OnAroundButtonClick(clickPosition);
    // Verify target index is set correctly (selectedIndex_ - 3)
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 4);
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_ClickBeyondAllLevels001
 * @tc.desc: Test OnAroundButtonClick function when click is beyond all levels but still within visible area
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_ClickBeyondAllLevels001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click beyond all levels but within visible
     * area.
     * @tc.expected: step2. function returns immediately without any action.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 500.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;
    pattern->secondAdjacentItemHeight_ = 50.0f;
    pattern->thirdAdjacentItemHeight_ = 50.0f;

    float clickPosition = 40.0f; // Middle is at 250.0f, this is -210.0f away (beyond 3 levels but within 250.0f)
    pattern->OnAroundButtonClick(clickPosition);
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_ClickBeyondAllLevels002
 * @tc.desc: Test OnAroundButtonClick function when click is beyond all levels and isLoop is false
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_ClickBeyondAllLevels002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data and call OnAroundButtonClick with click beyond all levels and isLoop is false
     * area.
     * @tc.expected: step2. function returns immediately without any action.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 0.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;
    pattern->secondAdjacentItemHeight_ = 50.0f;
    pattern->thirdAdjacentItemHeight_ = 50.0f;

    float clickPosition = 10.0f; // Middle is at 200.0f, this is -190.0f away (beyond 3 levels but within 200.0f)
    pattern->OnAroundButtonClick(clickPosition);
    // Verify no action was taken
    EXPECT_FALSE(pattern->targetIndex_.has_value());

    clickPosition = 390.0f; // Middle is at 200.0f, this is 190.0f away (beyond 3 levels but within 200.0f)
    pattern->OnAroundButtonClick(clickPosition);
    // Verify no action was taken
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: ContainerPickerPatternTest_OnAroundButtonClick_WithTopPadding001
 * @tc.desc: Test OnAroundButtonClick function with topPadding set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_OnAroundButtonClick_WithTopPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data with topPadding and call OnAroundButtonClick.
     * @tc.expected: step2. function calculates middle position correctly with topPadding.
     */
    pattern->clickBreak_ = false;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_ = std::nullopt;
    pattern->height_ = 400.0f;
    pattern->topPadding_ = 50.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->firstAdjacentItemHeight_ = 50.0f;

    // Click position is in level 1 area considering topPadding
    // Middle is at height_/2 + topPadding = 200.0f + 50.0f = 250.0f
    float clickPosition = 320.0f; // This is 70.0f away from middle (within level 1)
    pattern->OnAroundButtonClick(clickPosition);

    // Verify target index is set correctly (selectedIndex_ + 1)
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 3);
}

/**
 * @tc.name: ContainerPickerPatternHandleDirectionKeyTest001
 * @tc.desc: Test HandleDirectionKey method with Arrow Up key
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternHandleDirectionKeyTest001, TestSize.Level1)
{
    // Create picker and get pattern.
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = 5;

    // Test Arrow Up key
    EXPECT_TRUE(pattern->HandleDirectionKey(KeyCode::KEY_DPAD_UP));
}

/**
 * @tc.name: ContainerPickerPatternHandleDirectionKeyTest002
 * @tc.desc: Test HandleDirectionKey method with Arrow Down key
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternHandleDirectionKeyTest002, TestSize.Level1)
{
    // Create picker and get pattern.
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = 5;

    // Test Arrow Down key
    EXPECT_TRUE(pattern->HandleDirectionKey(KeyCode::KEY_DPAD_DOWN));
}

/**
 * @tc.name: ContainerPickerPatternHandleDirectionKeyTest003
 * @tc.desc: Test HandleDirectionKey method with invalid key
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternHandleDirectionKeyTest003, TestSize.Level1)
{
    // Create picker and get pattern.
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = 5;

    // Test invalid key
    EXPECT_FALSE(pattern->HandleDirectionKey(KeyCode::KEY_0));
}

/**
 * @tc.name: ContainerPickerPatternOnKeyEventTest001
 * @tc.desc: Test OnKeyEvent method with KEY_DPAD_UP key
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternOnKeyEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = 5;

    /**
     * @tc.steps: step2. Create a key event for KEY_DPAD_UP
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.action = KeyAction::DOWN;

    /**
     * @tc.steps: step3. Call OnKeyEvent
     * @tc.expected: step3. OnKeyEvent should return true
     */
    bool result = pattern->OnKeyEvent(keyEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ContainerPickerPatternOnKeyEventTest002
 * @tc.desc: Test OnKeyEvent method with KEY_DPAD_DOWN key
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternOnKeyEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = 5;

    /**
     * @tc.steps: step2. Create a key event for KEY_DPAD_DOWN
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    keyEvent.action = KeyAction::DOWN;

    /**
     * @tc.steps: step3. Call OnKeyEvent
     * @tc.expected: step3. OnKeyEvent should return true
     */
    bool result = pattern->OnKeyEvent(keyEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ContainerPickerPatternOnKeyEventTest003
 * @tc.desc: Test OnKeyEvent method with invalid key
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternOnKeyEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a key event for invalid key
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_0;
    keyEvent.action = KeyAction::DOWN;

    /**
     * @tc.steps: step3. Call OnKeyEvent
     * @tc.expected: step3. OnKeyEvent should return false
     */
    bool result = pattern->OnKeyEvent(keyEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ContainerPickerPatternOnKeyEventTest004
 * @tc.desc: Test OnKeyEvent method with UP action
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternOnKeyEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create a key event with UP action
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.action = KeyAction::UP;

    /**
     * @tc.steps: step3. Call OnKeyEvent
     * @tc.expected: step3. OnKeyEvent should return false
     */
    bool result = pattern->OnKeyEvent(keyEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ContainerPickerPatternTest_GetDragDeltaLessThanJumpInterval001
 * @tc.desc: Test GetDragDeltaLessThanJumpInterval function with isOverScroll logic
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_GetDragDeltaLessThanJumpInterval001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set up test data
     */
    pattern->height_ = 500.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    CreateItemPosition();

    /**
     * @tc.steps: step3. test with useRebound=true but not out of boundary
     * @tc.expected: step3. isOverScroll should be false
     */
    double offsetY = 0.0f;
    float originalDragDelta = 10.0f;
    bool useRebound = true;
    float shiftDistance = 100.0f;
    pattern->yOffset_ = 0.0f;
    double result = pattern->GetDragDeltaLessThanJumpInterval(offsetY, originalDragDelta, useRebound, shiftDistance);
    EXPECT_EQ(result, 10.0f); // originalDragDelta + yOffset_

    /**
     * @tc.steps: step4. test with useRebound=true and out of boundary
     * @tc.expected: step4. isOverScroll should be true
     */
    offsetY = 300.0f; // Out of boundary
    result = pattern->GetDragDeltaLessThanJumpInterval(offsetY, originalDragDelta, useRebound, shiftDistance);
    EXPECT_EQ(result, 10.0f); // originalDragDelta + yOffset_
}

} // namespace OHOS::Ace::NG
