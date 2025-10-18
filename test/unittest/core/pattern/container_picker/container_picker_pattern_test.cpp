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
    EXPECT_EQ(pattern->targetIndex_, 3);

    /**
     * @tc.steps: step3. test SetSelectedIndex with invalid index.
     * @tc.expected: step3. the selected index is set to 0.
     */
    pattern->SetSelectedIndex(-1);
    EXPECT_EQ(pattern->targetIndex_, 0);

    pattern->SetSelectedIndex(10);
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

    RefPtr<UINode> rowUiNode = AceType::DynamicCast<UINode>(rowNode);
    EXPECT_FALSE(rowUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);

    RefPtr<UINode> imageUiNode = AceType::DynamicCast<UINode>(imageNode);
    EXPECT_FALSE(imageUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);

    RefPtr<UINode> textUiNode = AceType::DynamicCast<UINode>(textNode);
    EXPECT_FALSE(textUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);

    RefPtr<UINode> symbolUiNode = AceType::DynamicCast<UINode>(symbolNode);
    EXPECT_FALSE(symbolUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);

    RefPtr<UINode> uiNode = AceType::DynamicCast<UINode>(containerPickerNode);
    pattern->CreateChildrenClickEvent(uiNode);
    EXPECT_TRUE(rowUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);
    EXPECT_TRUE(imageUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);
    EXPECT_TRUE(textUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);
    EXPECT_TRUE(symbolUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);
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
 * @tc.name: ContainerPickerPatternTest_CreateChildrenClickEvent_RecursiveProcessing001
 * @tc.desc: Verify that CreateChildrenClickEvent recursively processes nested container nodes.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CreateChildrenClickEvent_RecursiveProcessing001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and pattern.
     */
    auto containerPickerNode = CreateContainerPickerNode();
    auto pattern = containerPickerNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create nested container nodes with FOR_EACH and ITEM tags.
     */
    auto forEachNode = CreateChildNode(V2::JS_FOR_EACH_ETS_TAG, AceType::MakeRefPtr<Pattern>());
    auto itemNode = CreateChildNode(V2::JS_SYNTAX_ITEM_ETS_TAG, AceType::MakeRefPtr<Pattern>());
    auto textNode = CreateChildNode(V2::TEXT_ETS_TAG, AceType::MakeRefPtr<TextPattern>());

    containerPickerNode->AddChild(forEachNode);
    forEachNode->AddChild(itemNode);
    itemNode->AddChild(textNode);

    /**
     * @tc.steps: step3. Call CreateChildrenClickEvent and verify recursive processing.
     */
    RefPtr<UINode> uiNode = AceType::DynamicCast<UINode>(containerPickerNode);
    // This should trigger recursive processing of the nested nodes
    pattern->CreateChildrenClickEvent(uiNode);
    RefPtr<UINode> forEachUiNode = AceType::DynamicCast<UINode>(forEachNode);
    RefPtr<UINode> itemUiNode = AceType::DynamicCast<UINode>(itemNode);
    RefPtr<UINode> textUiNode = AceType::DynamicCast<UINode>(textNode);
    EXPECT_FALSE(forEachUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);
    EXPECT_FALSE(itemUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);
    EXPECT_TRUE(textUiNode->GetInteractionEventBindingInfo().builtInEventRegistered);
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
    pattern->isTargetAnimationRunning_ = false;

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
    pattern->isTargetAnimationRunning_ = false;

    pattern->SwipeTo(2);
    EXPECT_EQ(pattern->targetIndex_, 0); // Should not change targetIndex_

    // Test with animation already running
    pattern->selectedIndex_ = 1;
    pattern->targetIndex_ = 0; // Different from selectedIndex_
    pattern->isTargetAnimationRunning_ = true;

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
    pattern->dragOffset_ = 20.0f;
    pattern->isNeedStartInertialAnimation_ = false;

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;

    bool result = pattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern->currentDelta_, 0.0f);
    EXPECT_EQ(pattern->dragOffset_, 30.0f);
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
    pattern->isNeedStartInertialAnimation_ = false;

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;

    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
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
    info.SetGlobalPoint(Point(100.0f, 200.0f));

    pattern->HandleDragStart(info);
    EXPECT_TRUE(pattern->isDragging_);
    EXPECT_EQ(pattern->mainDeltaSum_, 0.0f);
    EXPECT_EQ(pattern->currentIndexOffset_, 0.0f);
    EXPECT_EQ(pattern->dragOffset_, 0.0f);
    EXPECT_EQ(pattern->yLast_, 200.0f);
}

/**
 * @tc.name: ContainerPickerPatternTest_ProcessDelta001
 * @tc.desc: Test ProcessDelta function with different delta values
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_ProcessDelta001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test ProcessDelta with different delta values.
     * @tc.expected: step2. delta is processed correctly based on constraints.
     */
    float delta1 = 200.0f;
    pattern->ProcessDelta(delta1, 100.0f, 0.0f);
    EXPECT_EQ(delta1, 100.0f); // Should be clamped to mainSize

    float delta2 = -150.0f;
    pattern->ProcessDelta(delta2, 100.0f, 0.0f);
    EXPECT_EQ(delta2, -100.0f); // Should be clamped to -mainSize

    float delta3 = 70.0f;
    pattern->ProcessDelta(delta3, 100.0f, 80.0f);
    EXPECT_EQ(delta3, 20.0f); // Should be adjusted to not exceed mainSize when summed with deltaSum
}

/**
 * @tc.name: ContainerPickerPatternTest_CalculateResetOffset001
 * @tc.desc: Test CalculateResetOffset function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CalculateResetOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. test CalculateResetOffset with different totalOffset values.
     * @tc.expected: step2. reset offset is calculated correctly.
     */
    // Test with offset less than half item height (should snap back)
    pattern->animationOffset_ = 50.0f;
    pattern->dragOffsetForAnimation_ = 0.0f;
    float resetOffset1 = pattern->CalculateResetOffset(50.0f);
    EXPECT_TRUE(NearEqual(resetOffset1, -50.0f));

    // Test with offset more than half item height (should snap forward)
    pattern->animationOffset_ = -90.0f;
    pattern->dragOffsetForAnimation_ = 0.0f;
    float resetOffset2 = pattern->CalculateResetOffset(-90.0f);
    EXPECT_TRUE(NearEqual(resetOffset2, -40.0f));
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
     * @tc.expected: step2. function returns true and sets isNeedStartInertialAnimation_.
     */
    pattern->dragStartTime_ = pattern->GetCurrentTime() - 2.0; // More than MIN_TIME
    pattern->dragEndTime_ = pattern->GetCurrentTime();

    bool result = pattern->Play(1000.0); // Velocity above threshold

    EXPECT_TRUE(result);
    EXPECT_TRUE(pattern->isNeedStartInertialAnimation_);
    EXPECT_EQ(pattern->dragVelocity_, 1000.0);
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

    GestureEvent info;
    info.SetGlobalPoint(Point(50.0f, 150.0f));
    info.SetMainDelta(50.0f);
    info.SetMainVelocity(200.0f);

    pattern->HandleDragUpdate(info);

    EXPECT_EQ(pattern->mainDeltaSum_, 50.0f);
    EXPECT_EQ(pattern->currentDelta_, -50.0f);
    EXPECT_EQ(pattern->yLast_, 150.0f);
}

/**
 * @tc.name: ContainerPickerPatternTest_CreateAnimation001
 * @tc.desc: Test CreateAnimation function for initial animation setup
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_CreateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. ensure animationCreated_ is false and call CreateAnimation.
     * @tc.expected: step2. animation is created and animationCreated_ is set to true.
     */
    pattern->animationCreated_ = false;

    pattern->CreateAnimation();

    EXPECT_TRUE(pattern->animationCreated_);
    EXPECT_NE(pattern->scrollProperty_, nullptr);
    EXPECT_NE(pattern->aroundClickProperty_, nullptr);
}

/**
 * @tc.name: ContainerPickerPatternTest_StopInertialRollingAnimation001
 * @tc.desc: Test StopInertialRollingAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_StopInertialRollingAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup snapOffsetProperty_ and call StopInertialRollingAnimation.
     * @tc.expected: step2. toss status is stopped and animation is reset.
     */
    pattern->isInertialRolling = true;
    pattern->lastAnimationScroll_ = 100.0f;
    pattern->CreateSnapProperty();

    pattern->StopInertialRollingAnimation();

    EXPECT_FALSE(pattern->isInertialRolling);
}

/**
 * @tc.name: ContainerPickerPatternTest_PlayResetAnimation001
 * @tc.desc: Test PlayResetAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTest, ContainerPickerPatternTest_PlayResetAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. setup animation properties and call PlayResetAnimation.
     * @tc.expected: step2. reset animation is played.
     */
    pattern->animationOffset_ = 50.0f;
    pattern->dragOffsetForAnimation_ = 0.0f;
    pattern->CreateAnimation();

    // We can't directly verify the animation is played, but we check the function completes
    pattern->PlayResetAnimation();
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
    ExpandEdges padding {10, 20, 30, 40};
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
    ExpandEdges padding {10, 20, 30, 40};
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

} // namespace OHOS::Ace::NG
