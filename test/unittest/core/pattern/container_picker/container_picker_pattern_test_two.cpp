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
 * @tc.name: ContainerPickerPatternTestTwo_SetCanLoopTest001
 * @tc.desc: Test ContainerPickerModel SetCanLoop
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, SetCanLoopTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set canLoop and get value from ContainerPickerLayoutProperty.
     * @tc.expected: step2. The value is the same with setting.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    picker.SetCanLoop(false);
    EXPECT_EQ(layoutProperty->GetCanLoopValue(), false);
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_SetEnableHapticFeedbackTest001
 * @tc.desc: Test ContainerPickerModel SetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, SetEnableHapticFeedbackTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set enableHapticFeedback and get value from ContainerPickerLayoutProperty.
     * @tc.expected: step2. The value is the same with setting.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    picker.SetEnableHapticFeedback(false);
    EXPECT_EQ(layoutProperty->GetEnableHapticFeedbackValue(), false);
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_CreateAnimationTest001
 * @tc.desc: Test ContainerPicker CreateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ContainerPickerCreateAnimation001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     * @tc.expected: step1. When creating the node, animationCreated_ will be set to true.
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
 * @tc.name: ContainerPickerPatternTestTwo_GetTextOfCurrentChildTest001
 * @tc.desc: Test GetTextOfCurrentChild function in normal case
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, GetTextOfCurrentChildTest001, TestSize.Level1)
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
     * @tc.steps: step2. Call GetTextOfCurrentChild.
     * @tc.expected: step2. The text of current child is retrieved correctly.
     */
    std::string result = pattern->GetTextOfCurrentChild();

    // Verify the result is not empty
    EXPECT_EQ(result, "test");
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_GetTextOfCurrentChildTest002
 * @tc.desc: Test GetTextOfCurrentChild function with invalid index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, GetTextOfCurrentChildTest002, TestSize.Level1)
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
     * @tc.expected: step2. The function handles invalid index correctly.
     */
    std::string result = pattern->GetTextOfCurrentChild();

    // Verify the result handling for invalid index
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_SetAccessibilityActionTest001
 * @tc.desc: Test SetAccessibilityAction function
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, SetAccessibilityActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and call SetAccessibilityAction.
     * @tc.expected: step1. The function executes without crashing.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetAccessibilityAction();

    // Verify accessibility actions are set properly (we can't directly verify, but the test ensures no crash)
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_ShowNextTest001
 * @tc.desc: Test ShowNext function in normal case
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ShowNextTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set up pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = TEST_ITEM_COUNT;
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowNext.
     * @tc.expected: step2. The targetIndex_ is updated correctly.
     */
    pattern->ShowNext();

    // Verify targetIndex_ is updated
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 1);
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_ShowNextTest002
 * @tc.desc: Test ShowNext function with last item (non-loop case)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ShowNextTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set up pattern with non-loop mode.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isLoop_ = false;
    pattern->totalItemCount_ = TEST_ITEM_COUNT;
    pattern->SetSelectedIndex(TEST_ITEM_COUNT - 1);
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowNext on last item.
     * @tc.expected: step2. The targetIndex_ remains the same in non-loop case.
     */
    pattern->ShowNext();

    // Verify targetIndex_ remains the same (non-loop case)
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_ShowPreviousTest001
 * @tc.desc: Test ShowPrevious function in normal case
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ShowPreviousTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set up pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = TEST_ITEM_COUNT;
    pattern->SetSelectedIndex(TEST_SELECTED_INDEX);
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowPrevious.
     * @tc.expected: step2. The targetIndex_ is updated correctly.
     */
    pattern->ShowPrevious();

    // Verify targetIndex_ is updated
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 0);
}

/**
 * @tc.name: ContainerPickerPatternTestTwo_ShowPreviousTest002
 * @tc.desc: Test ShowPrevious function with first item (non-loop case)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerPatternTestTwo, ShowPreviousTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set up pattern with non-loop mode.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isLoop_ = false;
    pattern->SetSelectedIndex(DEFAULT_SELECTED_INDEX);
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowPrevious on first item.
     * @tc.expected: step2. The targetIndex_ remains the same in non-loop case.
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
    RectF oldRect = {10.0f, 10.0f, 10.0f, 10.0f};
    RectF rect = {20.0f, 20.0f, 20.0f, 20.0f};
    OffsetF oldOrigin = {50.0f, 50.0f};
    OffsetF origin = {30.0f, 30.0f};
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

} // namespace OHOS::Ace::NG
