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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_picker/container_picker_accessibility_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace {
const int32_t TEST_ITEM_COUNT = 5;
const int32_t LOOPABLE_ITEM_COUNT = 8;
const int32_t TEST_CURRENT_INDEX = 2;
const int32_t TEST_BEGIN_INDEX = 0;
const int32_t TEST_END_INDEX = 4;
} // namespace

namespace OHOS::Ace::NG {
class ContainerPickerAccessibilityPropertyTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateItemPosition() const;
    void CreateContainerPickerNode();

    RefPtr<FrameNode> frameNode_ = nullptr;
    RefPtr<ContainerPickerAccessibilityProperty> accessibilityProperty_ = nullptr;
    RefPtr<ContainerPickerPattern> pattern_ = nullptr;
    RefPtr<ContainerPickerLayoutProperty> layoutProperty_ = nullptr;
};

void ContainerPickerAccessibilityPropertyTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void ContainerPickerAccessibilityPropertyTest::CreateContainerPickerNode()
{
    ContainerPickerModel picker;
    picker.Create();
    frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode_, nullptr);
    pattern_ = frameNode_->GetPattern<ContainerPickerPattern>();
    EXPECT_NE(pattern_, nullptr);
    pattern_->InitDefaultParams();
    pattern_->isLoop_ = true;
    accessibilityProperty_ =
        AceType::DynamicCast<ContainerPickerAccessibilityProperty>(pattern_->CreateAccessibilityProperty());
    EXPECT_NE(accessibilityProperty_, nullptr);
    accessibilityProperty_->SetHost(frameNode_);
    layoutProperty_ = AceType::DynamicCast<ContainerPickerLayoutProperty>(pattern_->CreateLayoutProperty());
    EXPECT_NE(layoutProperty_, nullptr);
}

void ContainerPickerAccessibilityPropertyTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerPickerAccessibilityPropertyTest::SetUp() {}

void ContainerPickerAccessibilityPropertyTest::TearDown() {}

void ContainerPickerAccessibilityPropertyTest::CreateItemPosition() const
{
    float itemHeight = 100.0f;
    int32_t total = 5;
    for (int32_t i = 0; i < total; ++i) {
        pattern_->itemPosition_[i] = { itemHeight * i, itemHeight * (i + 1), nullptr };
    }
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetTextTest001
 * @tc.desc: Test GetText method with normal case
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetTextTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and text node.
     */
    CreateContainerPickerNode();
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto textNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), textPattern);
    EXPECT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(u"test");
    // Add text node as child
    frameNode_->AddChild(textNode);

    /**
     * @tc.steps: step2. Test GetText method.
     * @tc.expected: step2. The text is retrieved correctly.
     */
    EXPECT_EQ(accessibilityProperty_->GetText(), "test");
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetTextTest002
 * @tc.desc: Test GetText method with empty text
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetTextTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set empty text.
     */
    CreateContainerPickerNode();
    accessibilityProperty_->SetUserTextValue("");

    /**
     * @tc.steps: step2. Test GetText method.
     * @tc.expected: step2. The empty text is retrieved correctly.
     */
    EXPECT_EQ(accessibilityProperty_->GetText(), "");
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_IsScrollableTest001
 * @tc.desc: Test IsScrollable method when item count > 1
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, IsScrollableTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set item count greater than 1.
     */
    CreateContainerPickerNode();
    pattern_->totalItemCount_ = TEST_ITEM_COUNT;

    /**
     * @tc.steps: step2. Test IsScrollable method.
     * @tc.expected: step2. The result is true when item count > 1.
     */
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_IsScrollableTest002
 * @tc.desc: Test IsScrollable method when item count = 1
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, IsScrollableTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set item count to 1.
     */
    CreateContainerPickerNode();
    pattern_->totalItemCount_ = 1;

    /**
     * @tc.steps: step2. Test IsScrollable method.
     * @tc.expected: step2. The result is false when item count = 1.
     */
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetCollectionItemCountsTest001
 * @tc.desc: Test GetCollectionItemCounts method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetCollectionItemCountsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set item count.
     */
    CreateContainerPickerNode();
    pattern_->totalItemCount_ = TEST_ITEM_COUNT;

    /**
     * @tc.steps: step2. Test GetCollectionItemCounts method.
     * @tc.expected: step2. The item count is retrieved correctly.
     */
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), TEST_ITEM_COUNT);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetCurrentIndexTest001
 * @tc.desc: Test GetCurrentIndex method without totalItemCount_
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetCurrentIndexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and set selected index.
     */
    CreateContainerPickerNode();
    pattern_->SetSelectedIndex(TEST_CURRENT_INDEX);

    /**
     * @tc.steps: step2. Test GetCurrentIndex method without totalItemCount_.
     * @tc.expected: step2. The result is -1 when totalItemCount_ is not set.
     */
    EXPECT_EQ(accessibilityProperty_->GetCurrentIndex(), -1);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetCurrentIndexTest002
 * @tc.desc: Test GetCurrentIndex method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetCurrentIndexTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node, set item count and selected index.
     */
    CreateContainerPickerNode();
    pattern_->totalItemCount_ = TEST_ITEM_COUNT;
    pattern_->SetSelectedIndex(TEST_CURRENT_INDEX);

    /**
     * @tc.steps: step2. Test GetCurrentIndex method.
     * @tc.expected: step2. The current index is retrieved correctly.
     */
    EXPECT_EQ(accessibilityProperty_->GetCurrentIndex(), TEST_CURRENT_INDEX);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetBeginIndexTest001
 * @tc.desc: Test GetBeginIndex method without totalItemCount_
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetBeginIndexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and item positions.
     */
    CreateContainerPickerNode();
    CreateItemPosition();

    /**
     * @tc.steps: step2. Test GetBeginIndex method without totalItemCount_.
     * @tc.expected: step2. The result is -1 when totalItemCount_ is not set.
     */
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), -1);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetBeginIndexTest002
 * @tc.desc: Test GetBeginIndex method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetBeginIndexTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node, set item count and item positions.
     */
    CreateContainerPickerNode();
    pattern_->totalItemCount_ = TEST_ITEM_COUNT;
    CreateItemPosition();

    /**
     * @tc.steps: step2. Test GetBeginIndex method.
     * @tc.expected: step2. The begin index is retrieved correctly.
     */
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), TEST_BEGIN_INDEX);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetEndIndexTest001
 * @tc.desc: Test GetEndIndex method without totalItemCount_
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetEndIndexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and item positions.
     */
    CreateContainerPickerNode();
    CreateItemPosition();

    /**
     * @tc.steps: step2. Test GetEndIndex method without totalItemCount_.
     * @tc.expected: step2. The result is -1 when totalItemCount_ is not set.
     */
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), -1);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_GetEndIndexTest002
 * @tc.desc: Test GetEndIndex method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, GetEndIndexTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node, set item count and item positions.
     */
    CreateContainerPickerNode();
    pattern_->totalItemCount_ = TEST_ITEM_COUNT;
    CreateItemPosition();

    /**
     * @tc.steps: step2. Test GetEndIndex method.
     * @tc.expected: step2. The end index is retrieved correctly.
     */
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), TEST_END_INDEX);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_SetSpecificSupportActionTest001
 * @tc.desc: Test SetSpecificSupportAction method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, SetSpecificSupportActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and reset support action.
     */
    CreateContainerPickerNode();
    accessibilityProperty_->ResetSupportAction();

    pattern_->totalItemCount_ = LOOPABLE_ITEM_COUNT;
    pattern_->isLoop_ = true;

    /**
     * @tc.steps: step2. Test SetSpecificSupportAction.
     */
    accessibilityProperty_->SetSpecificSupportAction();

    /**
     * @tc.steps: step3. Verify that both scroll forward and backward actions are supported.
     * @tc.expected: step3. Both actions are supported when loop is enabled.
     */
    auto supportActions = accessibilityProperty_->GetSupportAction();
    EXPECT_TRUE(supportActions.count(AceAction::ACTION_SCROLL_FORWARD) > 0);
    EXPECT_TRUE(supportActions.count(AceAction::ACTION_SCROLL_BACKWARD) > 0);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_SetSpecificSupportActionTest002
 * @tc.desc: Test SetSpecificSupportAction method with limited movement
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, SetSpecificSupportActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and reset support action.
     */
    CreateContainerPickerNode();
    accessibilityProperty_->ResetSupportAction();

    /**
     * @tc.steps: step2. Set item count to limit movement.
     */
    pattern_->totalItemCount_ = TEST_ITEM_COUNT;

    /**
     * @tc.steps: step3. Test SetSpecificSupportAction.
     */
    accessibilityProperty_->SetSpecificSupportAction();

    /**
     * @tc.steps: step4. Verify that only scroll forward action is supported.
     * @tc.expected: step4. Only scroll forward action is supported when movement is limited.
     */
    auto supportActions = accessibilityProperty_->GetSupportAction();
    EXPECT_TRUE(supportActions.count(AceAction::ACTION_SCROLL_FORWARD) > 0);
    EXPECT_FALSE(supportActions.count(AceAction::ACTION_SCROLL_BACKWARD) > 0);
}

/**
 * @tc.name: ContainerPickerAccessibilityPropertyTest_SetSpecificSupportActionTest003
 * @tc.desc: Test SetSpecificSupportAction method with no movement
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerAccessibilityPropertyTest, SetSpecificSupportActionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create container picker node and reset support action.
     */
    CreateContainerPickerNode();
    accessibilityProperty_->ResetSupportAction();

    /**
     * @tc.steps: step2. Set item count to 1 to disallow movement.
     */
    pattern_->totalItemCount_ = 1;

    /**
     * @tc.steps: step3. Test SetSpecificSupportAction.
     */
    accessibilityProperty_->SetSpecificSupportAction();

    /**
     * @tc.steps: step4. Verify that no scroll actions are supported.
     * @tc.expected: step4. No scroll actions are supported when there's only one item.
     */
    auto supportActions = accessibilityProperty_->GetSupportAction();
    EXPECT_FALSE(supportActions.count(AceAction::ACTION_SCROLL_FORWARD) > 0);
    EXPECT_FALSE(supportActions.count(AceAction::ACTION_SCROLL_BACKWARD) > 0);
}
} // namespace OHOS::Ace::NG
