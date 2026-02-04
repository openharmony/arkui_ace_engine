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

#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_model_static.h"
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
} // namespace

class ContainerPickerSupplementTest : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> CreateContainerPickerNode();
    RefPtr<FrameNode> CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern);
};

void ContainerPickerSupplementTest::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerPickerTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerPickerSupplementTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    TestNG::TearDownTestSuite();
}

void ContainerPickerSupplementTest::SetUp() {}

void ContainerPickerSupplementTest::TearDown() {}

RefPtr<FrameNode> ContainerPickerSupplementTest::CreateContainerPickerNode()
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

RefPtr<FrameNode> ContainerPickerSupplementTest::CreateChildNode(const std::string& tag, const RefPtr<Pattern>& pattern)
{
    auto frameNode = FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(), pattern);
    EXPECT_NE(frameNode, nullptr);
    return frameNode;
}

/**
 * @tc.name: SetIndicatorStyleTest001
 * @tc.desc: Test SetIndicatorStyle and GetIndicatorStyle methods of ContainerPickerModel
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetIndicatorStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set indicator style (DIVIDER type) and verify it is set correctly.
     * @tc.expected: step2. The indicator style should be retrieved correctly.
     */
    PickerIndicatorStyle style;
    style.type = static_cast<int32_t>(PickerIndicatorType::DIVIDER);  // DIVIDER = 1
    style.strokeWidth = Dimension(10.0);
    style.dividerColor = Color::RED;

    ContainerPickerModel::SetIndicatorStyle(AceType::RawPtr(frameNode), style);
    auto retrievedStyle = ContainerPickerModel::GetIndicatorStyle(AceType::RawPtr(frameNode));

    EXPECT_EQ(retrievedStyle.type, static_cast<int32_t>(PickerIndicatorType::DIVIDER));
    EXPECT_TRUE(retrievedStyle.strokeWidth.has_value());
    EXPECT_EQ(retrievedStyle.strokeWidth.value(), Dimension(10.0));
    EXPECT_TRUE(retrievedStyle.dividerColor.has_value());
    EXPECT_EQ(retrievedStyle.dividerColor.value(), Color::RED);
}

/**
 * @tc.name: SetIndicatorStyleTest002
 * @tc.desc: Test SetIndicatorStyle with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetIndicatorStyleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set indicator style with BACKGROUND type.
     * @tc.expected: step2. The indicator style should be set correctly.
     */
    PickerIndicatorStyle style;
    style.type = static_cast<int32_t>(PickerIndicatorType::BACKGROUND);  // BACKGROUND = 0
    style.backgroundColor = Color::BLUE;
    style.borderRadius = BorderRadiusProperty(Dimension(15.0));

    ContainerPickerModel::SetIndicatorStyle(AceType::RawPtr(frameNode), style);
    auto retrievedStyle = ContainerPickerModel::GetIndicatorStyle(AceType::RawPtr(frameNode));

    EXPECT_EQ(retrievedStyle.type, static_cast<int32_t>(PickerIndicatorType::BACKGROUND));
    EXPECT_TRUE(retrievedStyle.backgroundColor.has_value());
    EXPECT_EQ(retrievedStyle.backgroundColor.value(), Color::BLUE);
    EXPECT_TRUE(retrievedStyle.borderRadius.has_value());
}

/**
 * @tc.name: SetIndicatorStyleValTest001
 * @tc.desc: Test SetIndicatorStyleVal and GetIndicatorStyleVal methods of ContainerPickerPattern
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetIndicatorStyleValTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set indicator style value (DIVIDER type) and verify it is set correctly.
     * @tc.expected: step2. The indicator style value should be retrieved correctly.
     */
    PickerIndicatorStyle style;
    style.type = static_cast<int32_t>(PickerIndicatorType::DIVIDER);  // DIVIDER = 1
    style.strokeWidth = Dimension(12.0);
    style.startMargin = Dimension(5.0);
    style.endMargin = Dimension(10.0);

    pattern->SetIndicatorStyleVal(style);
    auto retrievedStyle = pattern->GetIndicatorStyleVal();

    EXPECT_EQ(retrievedStyle.type, static_cast<int32_t>(PickerIndicatorType::DIVIDER));
    EXPECT_TRUE(retrievedStyle.strokeWidth.has_value());
    EXPECT_EQ(retrievedStyle.strokeWidth.value(), Dimension(12.0));
    EXPECT_TRUE(retrievedStyle.startMargin.has_value());
    EXPECT_EQ(retrievedStyle.startMargin.value(), Dimension(5.0));
    EXPECT_TRUE(retrievedStyle.endMargin.has_value());
    EXPECT_EQ(retrievedStyle.endMargin.value(), Dimension(10.0));
}

/**
 * @tc.name: SetHeightFromAlgoTest001
 * @tc.desc: Test SetHeightFromAlgo and GetHeightFromAlgo methods
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetHeightFromAlgoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set height from algorithm and verify it is retrieved correctly.
     * @tc.expected: step2. The height should be set and retrieved correctly.
     */
    pattern->SetHeightFromAlgo(500.0f);
    EXPECT_EQ(pattern->GetHeightFromAlgo(), 500.0f);

    pattern->SetHeightFromAlgo(600.0f);
    EXPECT_EQ(pattern->GetHeightFromAlgo(), 600.0f);
}

/**
 * @tc.name: GetLayoutConstraintTest001
 * @tc.desc: Test GetLayoutConstraint method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetLayoutConstraintTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set layout constraint and verify it is retrieved correctly.
     * @tc.expected: step2. The layout constraint should be retrieved correctly.
     */
    LayoutConstraintF constraint;
    constraint.maxSize = { 400.0f, 500.0f };
    constraint.minSize = { 100.0f, 200.0f };
    pattern->layoutConstraint_ = constraint;

    auto retrievedConstraint = pattern->GetLayoutConstraint();
    EXPECT_EQ(retrievedConstraint.maxSize.Width(), 400.0f);
    EXPECT_EQ(retrievedConstraint.maxSize.Height(), 500.0f);
    EXPECT_EQ(retrievedConstraint.minSize.Width(), 100.0f);
    EXPECT_EQ(retrievedConstraint.minSize.Height(), 200.0f);
}

/**
 * @tc.name: GetRequestLongPredictTest001
 * @tc.desc: Test GetRequestLongPredict method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetRequestLongPredictTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Verify default value and set new value.
     * @tc.expected: step2. The requestLongPredict_ value should be retrieved correctly.
     */
    EXPECT_TRUE(pattern->GetRequestLongPredict());

    pattern->requestLongPredict_ = false;
    EXPECT_FALSE(pattern->GetRequestLongPredict());
}

/**
 * @tc.name: GetStartIndexTest001
 * @tc.desc: Test GetStartIndex method with items
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetStartIndexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Add items to itemPosition_ and verify GetStartIndex.
     * @tc.expected: step2. GetStartIndex should return the first index.
     */
    pattern->itemPosition_[2] = { 200.0f, 300.0f, nullptr };
    pattern->itemPosition_[5] = { 500.0f, 600.0f, nullptr };
    pattern->itemPosition_[8] = { 800.0f, 900.0f, nullptr };

    EXPECT_EQ(pattern->GetStartIndex(), 2);
}

/**
 * @tc.name: GetEndIndexTest001
 * @tc.desc: Test GetEndIndex method with items
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetEndIndexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Add items to itemPosition_ and verify GetEndIndex.
     * @tc.expected: step2. GetEndIndex should return the last index.
     */
    pattern->itemPosition_[2] = { 200.0f, 300.0f, nullptr };
    pattern->itemPosition_[5] = { 500.0f, 600.0f, nullptr };
    pattern->itemPosition_[8] = { 800.0f, 900.0f, nullptr };

    EXPECT_EQ(pattern->GetEndIndex(), 8);
}

/**
 * @tc.name: GetOffScreenItemsTest001
 * @tc.desc: Test SetOffScreenItems and GetOffScreenItems methods
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetOffScreenItemsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set offscreen items and verify they are retrieved correctly.
     * @tc.expected: step2. The offscreen items should be retrieved correctly.
     */
    std::vector<int32_t> offScreenItems = { 1, 2, 3 };
    pattern->SetOffScreenItems(offScreenItems);

    auto retrievedItems = pattern->GetOffScreenItems();
    EXPECT_EQ(retrievedItems.size(), 3);
    EXPECT_EQ(retrievedItems[0], 1);
    EXPECT_EQ(retrievedItems[1], 2);
    EXPECT_EQ(retrievedItems[2], 3);
}

/**
 * @tc.name: OnModifyDoneTest001
 * @tc.desc: Test OnModifyDone method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, OnModifyDoneTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnModifyDone and verify it executes without crash.
     * @tc.expected: step2. OnModifyDone should execute successfully.
     */
    pattern->OnModifyDone();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnScrollStopStaticTest001
 * @tc.desc: Test SetOnScrollStop static method without FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetOnScrollStopStaticTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set onScrollStop event and verify it works.
     * @tc.expected: step2. The event should be triggered with correct index.
     */
    int32_t testIndex = -1;
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode),
        [&testIndex](const double& index) { testIndex = static_cast<int32_t>(index); });

    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(7.0);
    EXPECT_EQ(testIndex, 7);
}

/**
 * @tc.name: SetOnChangeStaticTest001
 * @tc.desc: Test SetOnChange static method without FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetOnChangeStaticTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set onChange event and verify it works.
     * @tc.expected: step2. The event should be triggered with correct index.
     */
    int32_t testIndex = -1;
    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode),
        [&testIndex](const double& index) { testIndex = static_cast<int32_t>(index); });

    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(9.0);
    EXPECT_EQ(testIndex, 9);
}

/**
 * @tc.name: UpdateDividerWidthWithResObjTest001
 * @tc.desc: Test UpdateDividerWidthWithResObj method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, UpdateDividerWidthWithResObjTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create resource object and call UpdateDividerWidthWithResObj.
     * @tc.expected: step2. The function should execute without crash.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    pattern->UpdateDividerWidthWithResObj(resObj);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateDividerColorWithResObjTest001
 * @tc.desc: Test UpdateDividerColorWithResObj method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, UpdateDividerColorWithResObjTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create resource object and call UpdateDividerColorWithResObj.
     * @tc.expected: step2. The function should execute without crash.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    pattern->UpdateDividerColorWithResObj(resObj);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateStartMarginWithResObjTest001
 * @tc.desc: Test UpdateStartMarginWithResObj method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, UpdateStartMarginWithResObjTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create resource object and call UpdateStartMarginWithResObj.
     * @tc.expected: step2. The function should execute without crash.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    pattern->UpdateStartMarginWithResObj(resObj);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateEndMarginWithResObjTest001
 * @tc.desc: Test UpdateEndMarginWithResObj method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, UpdateEndMarginWithResObjTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create resource object and call UpdateEndMarginWithResObj.
     * @tc.expected: step2. The function should execute without crash.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    pattern->UpdateEndMarginWithResObj(resObj);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateBackgroundColorWithResObjTest001
 * @tc.desc: Test UpdateBackgroundColorWithResObj method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, UpdateBackgroundColorWithResObjTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create resource object and call UpdateBackgroundColorWithResObj.
     * @tc.expected: step2. The function should execute without crash.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    pattern->UpdateBackgroundColorWithResObj(resObj);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateBorderRadiusWithResObjTest001
 * @tc.desc: Test UpdateBorderRadiusWithResObj method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, UpdateBorderRadiusWithResObjTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create resource object and call UpdateBorderRadiusWithResObj.
     * @tc.expected: step2. The function should execute without crash.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    pattern->UpdateBorderRadiusWithResObj(resObj);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ProcessResourceObjTest001
 * @tc.desc: Test ProcessResourceObj static method without FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ProcessResourceObjTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker.
     */
    ContainerPickerModel picker;
    picker.Create();

    /**
     * @tc.steps: step2. Create resource object and call ProcessResourceObj.
     * @tc.expected: step2. The function should execute without crash.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ContainerPickerModel::ProcessResourceObj("test_key", resObj);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ProcessResourceObjWithFrameNodeTest001
 * @tc.desc: Test ProcessResourceObj static method with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ProcessResourceObjWithFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get frameNode.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create resource object and call ProcessResourceObj with FrameNode.
     * @tc.expected: step2. The function should execute without crash.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>();
    ContainerPickerModel::ProcessResourceObj(AceType::RawPtr(frameNode), "test_key", resObj);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetChangeEventTest001
 * @tc.desc: Test SetChangeEvent method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetChangeEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set change event and verify it works.
     * @tc.expected: step2. The event should be triggered with correct index.
     */
    int32_t testIndex = -1;
    ContainerPickerChangeEvent testEvent = [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    };

    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetChangeEvent(std::move(testEvent));
    eventHub->FireChangeEvent(11.0);
    EXPECT_EQ(testIndex, 11);
}

/**
 * @tc.name: GetTotalCountTest001
 * @tc.desc: Test GetTotalCount method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetTotalCountTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set totalItemCount and verify it is retrieved correctly.
     * @tc.expected: step2. The total count should be retrieved correctly.
     */
    pattern->totalItemCount_ = 10;
    EXPECT_EQ(pattern->GetTotalCount(), 10);

    pattern->totalItemCount_ = 20;
    EXPECT_EQ(pattern->GetTotalCount(), 20);
}

/**
 * @tc.name: InitDisabledTest001
 * @tc.desc: Test InitDisabled method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, InitDisabledTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call InitDisabled and verify it executes without crash.
     * @tc.expected: step2. InitDisabled should execute successfully.
     */
    pattern->InitDisabled();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateColumnChildPositionTest001
 * @tc.desc: Test UpdateColumnChildPosition method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, UpdateColumnChildPositionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up position and call UpdateColumnChildPosition.
     * @tc.expected: step2. The function should execute without crash.
     */
    pattern->pickerItemHeight_ = 100.0f;
    pattern->height_ = 500.0f;
    pattern->itemPosition_[0] = { 0.0f, 100.0f, nullptr };
    pattern->itemPosition_[1] = { 100.0f, 200.0f, nullptr };

    pattern->UpdateColumnChildPosition(50.0);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: FireAnimationEndEventTest001
 * @tc.desc: Test FireAnimationEndEvent method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, FireAnimationEndEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call FireAnimationEndEvent and verify it executes without crash.
     * @tc.expected: step2. FireAnimationEndEvent should execute successfully.
     */
    pattern->FireAnimationEndEvent();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InnerHandleScrollTest001
 * @tc.desc: Test InnerHandleScroll method with isDown parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, InnerHandleScrollTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = 5;
    pattern->selectedIndex_ = 2;

    /**
     * @tc.steps: step2. Test InnerHandleScroll with true and false.
     * @tc.expected: step2. InnerHandleScroll should handle both directions.
     */
    // Test with isDown = true
    bool result1 = pattern->InnerHandleScroll(true);
    EXPECT_TRUE(result1);

    // Test with isDown = false
    bool result2 = pattern->InnerHandleScroll(false);
    EXPECT_TRUE(result2);
}

/**
 * @tc.name: PlayHapticTest001
 * @tc.desc: Test PlayHaptic method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, PlayHapticTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call PlayHaptic with different offset values.
     * @tc.expected: step2. PlayHaptic should execute successfully.
     */
    pattern->PlayHaptic(10.0f);
    EXPECT_TRUE(true);

    pattern->PlayHaptic(-10.0f);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetStartIndexEmptyTest001
 * @tc.desc: Test GetStartIndex method with empty itemPosition_
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetStartIndexEmptyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Verify GetStartIndex returns 0 when itemPosition_ is empty.
     * @tc.expected: step2. GetStartIndex should return 0 for empty itemPosition_.
     */
    EXPECT_TRUE(pattern->itemPosition_.empty());
    EXPECT_EQ(pattern->GetStartIndex(), 0);
}

/**
 * @tc.name: GetEndIndexEmptyTest001
 * @tc.desc: Test GetEndIndex method with empty itemPosition_
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetEndIndexEmptyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Verify GetEndIndex returns 0 when itemPosition_ is empty.
     * @tc.expected: step2. GetEndIndex should return 0 for empty itemPosition_.
     */
    EXPECT_TRUE(pattern->itemPosition_.empty());
    EXPECT_EQ(pattern->GetEndIndex(), 0);
}

/**
 * @tc.name: SetSelectedIndexModelTest001
 * @tc.desc: Test SetSelectedIndex static method with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetSelectedIndexModelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set selected index using static method.
     * @tc.expected: step2. Selected index should be set correctly.
     */
    ContainerPickerModel::SetSelectedIndex(AceType::RawPtr(frameNode), 3);
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->selectedIndex_, 3);
}

/**
 * @tc.name: SetCanLoopModelTest001
 * @tc.desc: Test SetCanLoop static method with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetCanLoopModelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set canLoop using static method.
     * @tc.expected: step2. CanLoop should be set correctly.
     */
    ContainerPickerModel::SetCanLoop(AceType::RawPtr(frameNode), false);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetCanLoopValue(), false);
}

/**
 * @tc.name: SetEnableHapticFeedbackModelTest001
 * @tc.desc: Test SetEnableHapticFeedback static method with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetEnableHapticFeedbackModelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set enableHapticFeedback using static method.
     * @tc.expected: step2. EnableHapticFeedback should be set correctly.
     */
    ContainerPickerModel::SetEnableHapticFeedback(AceType::RawPtr(frameNode), false);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetEnableHapticFeedbackValue(), false);
}

/**
 * @tc.name: SetOnChangeWithFrameNodeTest001
 * @tc.desc: Test SetOnChange static method with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetOnChangeWithFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set onChange event using static method.
     * @tc.expected: step2. The event should be set correctly.
     */
    int32_t testIndex = -1;
    ContainerPickerChangeEvent testEvent = [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    };
    ContainerPickerModel::SetOnChange(AceType::RawPtr(frameNode), std::move(testEvent));

    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(13.0);
    EXPECT_EQ(testIndex, 13);
}

/**
 * @tc.name: SetOnScrollStopWithFrameNodeTest001
 * @tc.desc: Test SetOnScrollStop static method with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetOnScrollStopWithFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker node.
     */
    auto frameNode = CreateContainerPickerNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set onScrollStop event using static method.
     * @tc.expected: step2. The event should be set correctly.
     */
    int32_t testIndex = -1;
    ContainerPickerChangeEvent testEvent = [&testIndex](const double& index) {
        testIndex = static_cast<int32_t>(index);
    };
    ContainerPickerModel::SetOnScrollStop(AceType::RawPtr(frameNode), std::move(testEvent));

    auto eventHub = frameNode->GetEventHub<ContainerPickerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireScrollStopEvent(15.0);
    EXPECT_EQ(testIndex, 15);
}

/**
 * @tc.name: OnAttachToFrameNodeTest001
 * @tc.desc: Test OnAttachToFrameNode method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, OnAttachToFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnAttachToFrameNode and verify it executes without crash.
     * @tc.expected: step2. OnAttachToFrameNode should execute successfully.
     */
    pattern->OnAttachToFrameNode();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: OnColorConfigurationUpdateTest001
 * @tc.desc: Test OnColorConfigurationUpdate method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, OnColorConfigurationUpdateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnColorConfigurationUpdate.
     * @tc.expected: step2. OnColorConfigurationUpdate should execute successfully.
     */
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: IsAxisAnimationRunningTest001
 * @tc.desc: Test IsAxisAnimationRunning method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, IsAxisAnimationRunningTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Verify IsAxisAnimationRunning returns false initially.
     * @tc.expected: step2. IsAxisAnimationRunning should return false when no animator exists.
     */
    EXPECT_FALSE(pattern->IsAxisAnimationRunning());
}

/**
 * @tc.name: InitAxisAnimatorTest001
 * @tc.desc: Test InitAxisAnimator method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, InitAxisAnimatorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call InitAxisAnimator.
     * @tc.expected: step2. axisAnimator_ should be created.
     */
    pattern->InitAxisAnimator();
    EXPECT_NE(pattern->axisAnimator_, nullptr);
}

/**
 * @tc.name: StopAxisAnimationTest001
 * @tc.desc: Test StopAxisAnimation method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, StopAxisAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Initialize axis animator and call StopAxisAnimation.
     * @tc.expected: step2. StopAxisAnimation should stop the animation.
     */
    pattern->InitAxisAnimator();
    pattern->StopAxisAnimation();
    EXPECT_FALSE(pattern->IsAxisAnimationRunning());
}

/**
 * @tc.name: ProcessScrollMotionTest001
 * @tc.desc: Test ProcessScrollMotion method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ProcessScrollMotionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call ProcessScrollMotion with position.
     * @tc.expected: step2. ProcessScrollMotion should execute successfully.
     */
    pattern->ProcessScrollMotion(100.0);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ProcessScrollMotionStartTest001
 * @tc.desc: Test ProcessScrollMotionStart method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ProcessScrollMotionStartTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set non-zero scroll values and call ProcessScrollMotionStart.
     * @tc.expected: step2. Scroll parameters should be reset to zero.
     */
    pattern->mainDeltaSum_ = 100.0f;
    pattern->currentDelta_ = 50.0f;
    pattern->springOffset_ = 25.0f;

    pattern->ProcessScrollMotionStart();

    EXPECT_NEAR(pattern->mainDeltaSum_, 0.0f, 0.001f);
    EXPECT_NEAR(pattern->currentDelta_, 0.0f, 0.001f);
    EXPECT_NEAR(pattern->springOffset_, 0.0f, 0.001f);
}

/**
 * @tc.name: ShowNextTest001
 * @tc.desc: Test ShowNext method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ShowNextTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = TEST_ITEM_COUNT;
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowNext.
     * @tc.expected: step2. targetIndex_ should be set to selectedIndex_ + 1.
     */
    pattern->ShowNext();
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 1);
}

/**
 * @tc.name: ShowPreviousTest001
 * @tc.desc: Test ShowPrevious method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ShowPreviousTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = TEST_ITEM_COUNT;
    pattern->SetSelectedIndex(TEST_SELECTED_INDEX);
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call ShowPrevious.
     * @tc.expected: step2. targetIndex_ should be set to selectedIndex_ - 1.
     */
    pattern->ShowPrevious();
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 0);
}

/**
 * @tc.name: GetTextOfCurrentChildTest001
 * @tc.desc: Test GetTextOfCurrentChild method with valid child
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetTextOfCurrentChildTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and text node.
     */
    auto frameNode = CreateContainerPickerNode();
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto textNode = CreateChildNode(V2::TEXT_ETS_TAG, textPattern);
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(u"test");
    frameNode->AddChild(textNode);

    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetSelectedIndex(DEFAULT_SELECTED_INDEX);

    /**
     * @tc.steps: step2. Call GetTextOfCurrentChild.
     * @tc.expected: step2. Should return the text content.
     */
    std::string result = pattern->GetTextOfCurrentChild();
    EXPECT_EQ(result, "test");
}

/**
 * @tc.name: GetTextOfCurrentChildEmptyTest001
 * @tc.desc: Test GetTextOfCurrentChild method with no children
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetTextOfCurrentChildEmptyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker without children.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetSelectedIndex(DEFAULT_SELECTED_INDEX);

    /**
     * @tc.steps: step2. Call GetTextOfCurrentChild with no children.
     * @tc.expected: step2. Should return empty string.
     */
    std::string result = pattern->GetTextOfCurrentChild();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: SetAccessibilityActionTest001
 * @tc.desc: Test SetAccessibilityAction method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetAccessibilityActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call SetAccessibilityAction.
     * @tc.expected: step2. Should execute without crash.
     */
    pattern->SetAccessibilityAction();
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityCustomRole(), "TextPicker");
}

/**
 * @tc.name: IsOutOfBoundaryTest001
 * @tc.desc: Test IsOutOfBoundary method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, IsOutOfBoundaryTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->height_ = 500.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    pattern->itemPosition_[0] = { 0.0f, 100.0f, nullptr };

    /**
     * @tc.steps: step2. Test IsOutOfBoundary with large offset.
     * @tc.expected: step2. Should return true for out of boundary.
     */
    EXPECT_TRUE(pattern->IsOutOfBoundary(300.0f));
}

/**
 * @tc.name: IsOutOfStartTest001
 * @tc.desc: Test IsOutOfStart method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, IsOutOfStartTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->height_ = 500.0f;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    pattern->itemPosition_[0] = { 0.0f, 100.0f, nullptr };

    /**
     * @tc.steps: step2. Test IsOutOfStart with large positive offset.
     * @tc.expected: step2. Should return true for out of start boundary.
     */
    EXPECT_TRUE(pattern->IsOutOfStart(300.0f));
}

/**
 * @tc.name: CheckDragOutOfBoundaryTest001
 * @tc.desc: Test CheckDragOutOfBoundary method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CheckDragOutOfBoundaryTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->pickerItemHeight_ = 100.0f;
    pattern->totalItemCount_ = 5;
    pattern->itemPosition_[0] = { 0.0f, 100.0f, nullptr };

    /**
     * @tc.steps: step2. Test CheckDragOutOfBoundary with default position.
     * @tc.expected: step2. Should return false when not out of boundary.
     */
    EXPECT_FALSE(pattern->CheckDragOutOfBoundary());
}

/**
 * @tc.name: CreateFrameNodeModelTest001
 * @tc.desc: Test CreateFrameNode method of ContainerPickerModel
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CreateFrameNodeModelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call CreateFrameNode with node ID.
     * @tc.expected: step1. Should return valid frameNode.
     */
    auto node = ContainerPickerModel::CreateFrameNode(1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::CONTAINER_PICKER_ETS_TAG);
}

/**
 * @tc.name: IsLoopTest001
 * @tc.desc: Test IsLoop method with different configurations
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, IsLoopTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test IsLoop with different totalItemCount and canLoop settings.
     * @tc.expected: step2. IsLoop should return correct value based on conditions.
     */
    pattern->totalItemCount_ = 10;
    pattern->displayCount_ = 5;
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerPickerLayoutProperty>();
    layoutProperty->UpdateCanLoop(true);

    EXPECT_TRUE(pattern->IsLoop());

    layoutProperty->UpdateCanLoop(false);
    EXPECT_FALSE(pattern->IsLoop());
}

/**
 * @tc.name: SetTargetIndexTest002
 * @tc.desc: Test SetTargetIndex with same index as selected
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SetTargetIndexTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = 5;
    pattern->selectedIndex_ = 2;
    pattern->targetIndex_.reset();

    /**
     * @tc.steps: step2. Call SetTargetIndex with same index.
     * @tc.expected: step2. targetIndex_ should not be set when same as selectedIndex.
     */
    pattern->SetTargetIndex(2);
    EXPECT_FALSE(pattern->targetIndex_.has_value());
}

/**
 * @tc.name: CreateLayoutAlgorithmTest001
 * @tc.desc: Test CreateLayoutAlgorithm method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CreateLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call CreateLayoutAlgorithm.
     * @tc.expected: step2. Should return valid layout algorithm.
     */
    auto algorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(algorithm, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<ContainerPickerLayoutAlgorithm>(algorithm));
}

/**
 * @tc.name: CreateNodePaintMethodTest001
 * @tc.desc: Test CreateNodePaintMethod method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CreateNodePaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call CreateNodePaintMethod.
     * @tc.expected: step2. Should return valid paint method.
     */
    auto paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: CreateEventHubTest001
 * @tc.desc: Test CreateEventHub method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CreateEventHubTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call CreateEventHub.
     * @tc.expected: step2. Should return ContainerPickerEventHub instance.
     */
    auto eventHub = pattern->CreateEventHub();
    EXPECT_NE(eventHub, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<ContainerPickerEventHub>(eventHub));
}

/**
 * @tc.name: CreateAccessibilityPropertyTest001
 * @tc.desc: Test CreateAccessibilityProperty method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CreateAccessibilityPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call CreateAccessibilityProperty.
     * @tc.expected: step2. Should return ContainerPickerAccessibilityProperty instance.
     */
    auto accessibilityProperty = pattern->CreateAccessibilityProperty();
    EXPECT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<ContainerPickerAccessibilityProperty>(accessibilityProperty));
}

/**
 * @tc.name: CreateLayoutPropertyTest001
 * @tc.desc: Test CreateLayoutProperty method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CreateLayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call CreateLayoutProperty.
     * @tc.expected: step2. Should return ContainerPickerLayoutProperty instance.
     */
    auto layoutProperty = pattern->CreateLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<ContainerPickerLayoutProperty>(layoutProperty));
}

/**
 * @tc.name: IsAtomicNodeTest001
 * @tc.desc: Test IsAtomicNode method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, IsAtomicNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call IsAtomicNode.
     * @tc.expected: step2. Should return false.
     */
    EXPECT_FALSE(pattern->IsAtomicNode());
}

/**
 * @tc.name: SwipeToTest001
 * @tc.desc: Test SwipeTo method with valid index
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, SwipeToTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->totalItemCount_ = 5;
    pattern->selectedIndex_ = 1;
    pattern->targetIndex_.reset();
    pattern->isAnimationRunning_ = false;

    /**
     * @tc.steps: step2. Call SwipeTo with different index.
     * @tc.expected: step2. targetIndex_ should be set.
     */
    pattern->SwipeTo(3);
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 3);
}

/**
 * @tc.name: ShortestDistanceBetweenCurrentAndTargetTest001
 * @tc.desc: Test ShortestDistanceBetweenCurrentAndTarget method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ShortestDistanceBetweenCurrentAndTargetTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up parameters and test distance calculation.
     * @tc.expected: step2. Distance should be calculated correctly.
     */
    pattern->totalItemCount_ = 5;
    pattern->isLoop_ = false;
    pattern->pickerItemHeight_ = 100.0f;
    pattern->height_ = 500.0f;
    pattern->itemPosition_[0] = { 0.0f, 100.0f, nullptr };
    pattern->itemPosition_[1] = { 100.0f, 200.0f, nullptr };
    pattern->itemPosition_[2] = { 200.0f, 300.0f, nullptr };
    pattern->selectedIndex_ = 1;

    float distance = pattern->ShortestDistanceBetweenCurrentAndTarget(2);
    EXPECT_NEAR(distance, 100.0f, 0.01f);
}

/**
 * @tc.name: CalcEndOffsetTest001
 * @tc.desc: Test CalcEndOffset method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CalcEndOffsetTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->pickerItemHeight_ = 100.0f;
    pattern->itemPosition_[0] = { 0.0f, 100.0f, nullptr };
    pattern->itemPosition_[1] = { 100.0f, 200.0f, nullptr };

    /**
     * @tc.steps: step2. Call CalcEndOffset.
     * @tc.expected: step2. endOffset should be adjusted.
     */
    float endOffset = 150.0f;
    pattern->CalcEndOffset(endOffset, 1);
    EXPECT_NEAR(endOffset, 50.0f, 0.01f);
}

/**
 * @tc.name: StopAnimationTest001
 * @tc.desc: Test StopAnimation method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, StopAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up animation and call StopAnimation.
     * @tc.expected: step2. Animation should be stopped.
     */
    pattern->CreateScrollProperty();
    pattern->CreateSpringAnimation(0.0f);
    pattern->isAnimationRunning_ = true;

    pattern->StopAnimation();
    EXPECT_FALSE(pattern->isAnimationRunning_);
}

/**
 * @tc.name: PickerMarkDirtyTest001
 * @tc.desc: Test PickerMarkDirty method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, PickerMarkDirtyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call PickerMarkDirty.
     * @tc.expected: step2. Should execute without crash.
     */
    pattern->PickerMarkDirty();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: PostIdleTaskTest001
 * @tc.desc: Test PostIdleTask method
 * @tc:type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, PostIdleTaskTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call PostIdleTask with empty offscreen items.
     * @tc.expected: step2. Should return immediately with empty offscreen items.
     */
    pattern->offScreenItemsIndex_.clear();
    pattern->PostIdleTask(frameNode);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetCurrentTimeTest001
 * @tc.desc: Test GetCurrentTime method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetCurrentTimeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCurrentTime.
     * @tc.expected: step2. Should return valid time.
     */
    double time1 = pattern->GetCurrentTime();
    EXPECT_GT(time1, 0.0);

    double time2 = pattern->GetCurrentTime();
    EXPECT_GE(time2, time1);
}

/**
 * @tc.name: PlayTest001
 * @tc.desc: Test Play method with drag velocity
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, PlayTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up drag parameters and call Play.
     * @tc.expected: step2. Should return true for valid drag.
     */
    pattern->dragStartTime_ = pattern->GetCurrentTime() - 2.0;
    pattern->dragEndTime_ = pattern->GetCurrentTime();
    pattern->dragVelocity_ = 1000.0;

    bool result = pattern->Play(1000.0);
    EXPECT_TRUE(result);
    EXPECT_TRUE(pattern->isNeedPlayInertialAnimation_);
}

/**
 * @tc.name: HandleDragStartTest001
 * @tc.desc: Test HandleDragStart method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, HandleDragStartTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create gesture event and call HandleDragStart.
     * @tc.expected: step2. Drag state should be initialized.
     */
    GestureEvent info;
    info.SetLocalLocation(Offset(100.0, 200.0));

    pattern->HandleDragStart(info);
    EXPECT_TRUE(pattern->isDragging_);
    EXPECT_EQ(pattern->yLast_, 200.0f);
}

/**
 * @tc.name: HandleDragEndTest001
 * @tc.desc: Test HandleDragEnd method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, HandleDragEndTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set up drag state and call HandleDragEnd.
     * @tc.expected: step2. Drag should be stopped.
     */
    pattern->isDragging_ = true;
    pattern->isLoop_ = false;
    pattern->animationCreated_ = true;

    pattern->HandleDragEnd(500.0, 0.0f);
    EXPECT_FALSE(pattern->isDragging_);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapTest001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, OnDirtyLayoutWrapperSwapTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker with children.
     */
    auto frameNode = CreateContainerPickerNode();
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto textNode = CreateChildNode(V2::TEXT_ETS_TAG, textPattern);
    frameNode->AddChild(textNode);

    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create layout wrapper and call OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. Should handle the swap.
     */
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;

    pattern->currentDelta_ = 10.0f;
    pattern->isNeedPlayInertialAnimation_ = false;

    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CustomizeSafeAreaPaddingTest001
 * @tc.desc: Test CustomizeSafeAreaPadding method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, CustomizeSafeAreaPaddingTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create padding and call CustomizeSafeAreaPadding.
     * @tc.expected: step2. Top and bottom should be reset.
     */
    PaddingPropertyF padding { 10, 10, 10, 10 };
    PaddingPropertyF result = pattern->CustomizeSafeAreaPadding(padding, false);

    EXPECT_EQ(result.top, std::nullopt);
    EXPECT_EQ(result.bottom, std::nullopt);
    EXPECT_EQ(result.left, 10);
    EXPECT_EQ(result.right, 10);
}

/**
 * @tc.name: AccumulatingTerminateHelperTest001
 * @tc.desc: Test AccumulatingTerminateHelper method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, AccumulatingTerminateHelperTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call AccumulatingTerminateHelper.
     * @tc.expected: step2. Should return appropriate value.
     */
    frameNode->isScrollableAxis_ = false;
    ExpandEdges padding { 10, 20, 30, 40 };
    RectF rect {};

    bool result = pattern->AccumulatingTerminateHelper(rect, padding);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ChildPreMeasureHelperEnabledTest001
 * @tc.desc: Test ChildPreMeasureHelperEnabled method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ChildPreMeasureHelperEnabledTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call ChildPreMeasureHelperEnabled.
     * @tc.expected: step2. Should return true.
     */
    EXPECT_TRUE(pattern->ChildPreMeasureHelperEnabled());
}

/**
 * @tc.name: PostponedTaskForIgnoreEnabledTest001
 * @tc.desc: Test PostponedTaskForIgnoreEnabled method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, PostponedTaskForIgnoreEnabledTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call PostponedTaskForIgnoreEnabled.
     * @tc.expected: step2. Should return true.
     */
    EXPECT_TRUE(pattern->PostponedTaskForIgnoreEnabled());
}

/**
 * @tc.name: NeedCustomizeSafeAreaPaddingTest001
 * @tc.desc: Test NeedCustomizeSafeAreaPadding method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, NeedCustomizeSafeAreaPaddingTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call NeedCustomizeSafeAreaPadding.
     * @tc.expected: step2. Should return true.
     */
    EXPECT_TRUE(pattern->NeedCustomizeSafeAreaPadding());
}

/**
 * @tc.name: ChildTentativelyLayoutedTest001
 * @tc.desc: Test ChildTentativelyLayouted method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, ChildTentativelyLayoutedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call ChildTentativelyLayouted.
     * @tc.expected: step2. Should return true.
     */
    EXPECT_TRUE(pattern->ChildTentativelyLayouted());
}

/**
 * @tc.name: GetAxisTest001
 * @tc.desc: Test GetAxis method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerSupplementTest, GetAxisTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create picker and get pattern.
     */
    auto frameNode = CreateContainerPickerNode();
    auto pattern = frameNode->GetPattern<ContainerPickerPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetAxis.
     * @tc.expected: step2. Should return VERTICAL.
     */
    EXPECT_EQ(pattern->GetAxis(), Axis::VERTICAL);
}
}
