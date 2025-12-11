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
namespace {
const std::string TEST_VALUE = "test_value";
const int32_t DEFAULT_SELECTED_INDEX = 0;
const int32_t TEST_SELECTED_INDEX = 1;
const int32_t TEST_ITEM_COUNT = 5;
const int32_t INVALID_INDEX = -1;
} // namespace

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
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerPickerTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerPickerPatternTestTwo::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
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
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->InitDefaultParams();
    pattern->isLoop_ = true;
    return frameNode;
}

RefPtr<FrameNode> ContainerPickerPatternTestTwo::CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern)
{
    auto frameNode = FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

/**
 * @tc.name: SetCanLoopTest
 * @tc.desc: Test ContainerPickerModel's SetCanLoop method to verify canLoop value is correctly set and retrieved
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, SetCanLoopTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set canLoop to false and get value from ContainerPickerLayoutProperty.
     * @tc.expected: step2. The retrieved value should match the set value (false).
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    picker.SetCanLoop(false);
    EXPECT_EQ(layoutProperty->GetCanLoopValue(), false);
}

/**
 * @tc.name: SetEnableHapticFeedbackTest
 * @tc.desc: Test ContainerPickerModel's SetEnableHapticFeedback method to verify haptic feedback setting
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, SetEnableHapticFeedbackTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set enableHapticFeedback to false and get value from ContainerPickerLayoutProperty.
     * @tc.expected: step2. The retrieved value should match the set value (false).
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    picker.SetEnableHapticFeedback(false);
    EXPECT_EQ(layoutProperty->GetEnableHapticFeedbackValue(), false);
}

/**
 * @tc.name: CreateAnimationTest
 * @tc.desc: Test ContainerPicker animation creation during node initialization
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, CreateAnimationTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     * @tc.expected: step1. The animationCreated_ flag should be set to true during node creation.
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->animationCreated_, true);
}

/**
 * @tc.name: GetTextOfCurrentChildNormalTest
 * @tc.desc: Test GetTextOfCurrentChild function in normal case with valid selected index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, GetTextOfCurrentChildNormalTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and text node, set selected index.
     */
    auto frameNode = CreateContainerPickerNode();
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto textNode = CreateChildNode(V2::TEXT_ETS_TAG, textPattern);
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(u"test");
    // Add text node as child
    frameNode->AddChild(textNode);

    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetSelectedIndex(DEFAULT_SELECTED_INDEX);

    /**
     * @tc.steps: step2. Call GetTextOfCurrentChild to retrieve text content.
     * @tc.expected: step2. The text of current child should be retrieved correctly as "test".
     */
    std::string result = pattern->GetTextOfCurrentChild();

    // Verify the result is not empty
    EXPECT_EQ(result, "test");
}

/**
 * @tc.name: GetTextOfCurrentChildInvalidIndexTest
 * @tc.desc: Test GetTextOfCurrentChild function with invalid selected index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, GetTextOfCurrentChildInvalidIndexTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set invalid selected index.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetSelectedIndex(INVALID_INDEX);

    /**
     * @tc.steps: step2. Call GetTextOfCurrentChild with invalid index.
     * @tc.expected: step2. The function should handle invalid index correctly and return an empty string.
     */
    std::string result = pattern->GetTextOfCurrentChild();

    // Verify the result handling for invalid index
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: SetAccessibilityActionTest
 * @tc.desc: Test SetAccessibilityAction function to ensure proper setup
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, SetAccessibilityActionTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and call SetAccessibilityAction.
     * @tc.expected: step1. The function should execute without crashing.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetAccessibilityAction();

    // Verify property is set properly
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), "TextPicker");
}

/**
 * @tc.name: ShowNextNormalTest
 * @tc.desc: Test ShowNext function in normal case with valid item navigation
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ShowNextNormalTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set up pattern with valid item count.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = TEST_ITEM_COUNT;
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowNext to navigate to next item.
     * @tc.expected: step2. The targetIndex_ should be updated correctly to 1.
     */
    pattern->ShowNext();

    // Verify targetIndex_ is updated
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 1);
}

/**
 * @tc.name: ShowNextLastItemTest
 * @tc.desc: Test ShowNext function with last item in non-loop mode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ShowNextLastItemTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set up pattern with non-loop mode at last item.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isLoop_ = false;
    pattern->totalItemCount_ = TEST_ITEM_COUNT;
    pattern->SetSelectedIndex(TEST_ITEM_COUNT - 1);
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowNext on last item in non-loop mode.
     * @tc.expected: step2. The targetIndex_ should remain unset (no value) in non-loop case.
     */
    pattern->ShowNext();

    // Verify targetIndex_ remains the same (non-loop case)
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: ShowPreviousNormalTest
 * @tc.desc: Test ShowPrevious function in normal case with valid item navigation
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ShowPreviousNormalTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set up pattern with valid selected index.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = TEST_ITEM_COUNT;
    pattern->SetSelectedIndex(TEST_SELECTED_INDEX);
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowPrevious to navigate to previous item.
     * @tc.expected: step2. The targetIndex_ should be updated correctly to 0.
     */
    pattern->ShowPrevious();

    // Verify targetIndex_ is updated
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 0);
}

/**
 * @tc.name: ShowPreviousFirstItemTest
 * @tc.desc: Test ShowPrevious function with first item in non-loop mode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ShowPreviousFirstItemTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set up pattern with non-loop mode at first item.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isLoop_ = false;
    pattern->SetSelectedIndex(DEFAULT_SELECTED_INDEX);
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowPrevious on first item in non-loop mode.
     * @tc.expected: step2. The targetIndex_ should remain unset (no value) in non-loop case.
     */
    pattern->ShowPrevious();

    // Verify targetIndex_ remains the same (non-loop case)
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_InitAreaChangeEvent001
 * @tc.desc: Test InitAreaChangeEvent function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, InitAreaChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->CleanDirty();

    /**
     * @tc.steps: step2. Call InitAreaChangeEvent
     */
    pattern->InitAreaChangeEvent();

    /**
     * @tc.steps: step3. Trigger the area change event by calling the callback manually
     * @tc.expected: step3. MarkDirtyNode should be called with correct parameters
     */
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    RectF oldRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    RectF rect = { 20.0f, 20.0f, 20.0f, 20.0f };
    OffsetF oldOrigin = { 50.0f, 50.0f };
    OffsetF origin = { 30.0f, 30.0f };
    eventHub->FireInnerOnAreaChanged(oldRect, oldOrigin, rect, origin);
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag(), PROPERTY_UPDATE_MEASURE_SELF | PROPERTY_UPDATE_RENDER);
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_InitAreaChangeEvent002
 * @tc.desc: Test that InitAreaChangeEvent is called during OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, InitAreaChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnAttachToFrameNode
     * @tc.expected: step2. InitAreaChangeEvent should be called
     */
    pattern->OnAttachToFrameNode();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->onAreaChangedInnerCallbacks_.count(frameNode->nodeId_));
}

/**
 * @tc.name: InitAxisAnimatorTest
 * @tc.desc: Test InitAxisAnimator function to verify axis animator is initialized correctly
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, InitAxisAnimatorTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call InitAxisAnimator to initialize axis animator.
     * @tc.expected: step2. The axisAnimator_ should be created and initialized.
     */
    pattern->InitAxisAnimator();
    EXPECT_NE(pattern->axisAnimator_, nullptr);
}

/**
 * @tc.name: InitAxisAnimatorNullHostTest
 * @tc.desc: Test InitAxisAnimator function when host is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, InitAxisAnimatorNullHostTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker pattern without host.
     */
    auto pattern = AceType::MakeRefPtr<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call InitAxisAnimator with null host.
     * @tc.expected: step2. The function should handle null host gracefully without crashing.
     */
    pattern->InitAxisAnimator();
    EXPECT_EQ(pattern->axisAnimator_, nullptr);
}

/**
 * @tc.name: InitAxisAnimatorAlreadyInitializedTest
 * @tc.desc: Test InitAxisAnimator function when axis animator is already initialized
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, InitAxisAnimatorAlreadyInitializedTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and initialize axis animator.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitAxisAnimator();
    ASSERT_NE(pattern->axisAnimator_, nullptr);

    /**
     * @tc.steps: step2. Call InitAxisAnimator again when already initialized.
     * @tc.expected: step2. The function should not reinitialize the existing animator.
     */
    auto originalAnimator = pattern->axisAnimator_;
    pattern->InitAxisAnimator();
    EXPECT_EQ(pattern->axisAnimator_, originalAnimator);
}

/**
 * @tc.name: StopAxisAnimationTest
 * @tc.desc: Test StopAxisAnimation function when axis animator exists
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, StopAxisAnimationTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and initialize axis animator.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitAxisAnimator();
    ASSERT_NE(pattern->axisAnimator_, nullptr);

    /**
     * @tc.steps: step2. Call StopAxisAnimation to stop the animation.
     * @tc.expected: step2. The StopAxisAnimation method should be called without errors.
     */
    pattern->StopAxisAnimation();
    EXPECT_FALSE(pattern->IsAxisAnimationRunning());
}

/**
 * @tc.name: StopAxisAnimationNullTest
 * @tc.desc: Test StopAxisAnimation function when axis animator is null
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, StopAxisAnimationNullTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node with null axis animator.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_EQ(pattern->axisAnimator_, nullptr);

    /**
     * @tc.steps: step2. Call StopAxisAnimation with null animator.
     * @tc.expected: step2. The function should handle null animator gracefully without crashing.
     */
    pattern->StopAxisAnimation();
    EXPECT_FALSE(pattern->IsAxisAnimationRunning());
}

/**
 * @tc.name: ProcessScrollMotionStartTest
 * @tc.desc: Test ProcessScrollMotionStart function to verify scroll motion starts correctly
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ProcessScrollMotionStartTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set non-zero values for scroll parameters.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->mainDeltaSum_ = 100.0f;
    pattern->currentDelta_ = 50.0f;
    pattern->springOffset_ = 25.0f;

    /**
     * @tc.steps: step2. Call ProcessScrollMotionStart to reset scroll parameters.
     * @tc.expected: step2. All scroll parameters should be reset to zero.
     */
    pattern->ProcessScrollMotionStart();

    // Verify all scroll parameters are reset
    EXPECT_NEAR(pattern->mainDeltaSum_, 0.0f, 0.001f);
    EXPECT_NEAR(pattern->currentDelta_, 0.0f, 0.001f);
    EXPECT_NEAR(pattern->springOffset_, 0.0f, 0.001f);
}

/**
 * @tc.name: ProcessScrollMotionTest
 * @tc.desc: Test ProcessScrollMotion function with normal position update
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ProcessScrollMotionTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set initial position.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->currentPos_ = 100.0f;
    pattern->dragVelocity_ = 10.0f;

    /**
     * @tc.steps: step2. Call ProcessScrollMotion with new position.
     * @tc.expected: step2. The drag velocity should be reset and current position should be updated.
     */
    double newPosition = 150.0f;
    pattern->ProcessScrollMotion(newPosition);

    // Verify drag velocity is reset and position is updated
    EXPECT_NEAR(pattern->dragVelocity_, 0.0f, 0.001f);
    EXPECT_NEAR(pattern->currentPos_, newPosition, 0.001f);
}

/**
 * @tc.name: ProcessScrollMotionZeroDeltaTest
 * @tc.steps: step1. Create container picker node and set initial position to same as target position.
 */
HWTEST_F(ContainerPickerPatternTestTwo, ProcessScrollMotionZeroDeltaTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set initial position.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->currentPos_ = 200.0f;

    /**
     * @tc.steps: step2. Call ProcessScrollMotion with the same position.
     * @tc.expected: step2. The function should handle zero delta gracefully.
     */
    pattern->ProcessScrollMotion(200.0f);
    EXPECT_NEAR(pattern->currentPos_, 200.0f, 0.001f);
}

/**
 * @tc.name: CreateFrameNodeTest
 * @tc.steps: step1. Create container picker node and set selected index.
 */
HWTEST_F(ContainerPickerPatternTestTwo, CreateFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     */
    ContainerPickerModel picker;
    auto node = picker.CreateFrameNode(1);
    EXPECT_NE(node, nullptr);
    picker.SetSelectedIndex(AceType::RawPtr(node), 1);
    EXPECT_EQ(picker.GetSelectedIndex(AceType::RawPtr(node)), 1);
}

/**
 * @tc.name: GetEnableHapticFeedbackTest
 * @tc.steps: step1. Create container picker node and get enable haptic feedback.
 */
HWTEST_F(ContainerPickerPatternTestTwo, GetEnableHapticFeedbackTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     */
    ContainerPickerModel picker;
    auto node = picker.CreateFrameNode(1);
    EXPECT_NE(node, nullptr);
    picker.SetEnableHapticFeedback(AceType::RawPtr(node), 1);
    EXPECT_EQ(picker.GetEnableHapticFeedback(AceType::RawPtr(node)), 1);
}

/**
 * @tc.name: GetCanLoopTest
 * @tc.steps: step1. Create container picker node and get canLoop.
 */
HWTEST_F(ContainerPickerPatternTestTwo, GetCanLoopTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     */
    ContainerPickerModel picker;
    auto node = picker.CreateFrameNode(1);
    EXPECT_NE(node, nullptr);
    picker.SetCanLoop(AceType::RawPtr(node), 1);
    EXPECT_EQ(picker.GetCanLoop(AceType::RawPtr(node)), 1);
}

} // namespace OHOS::Ace::NG
