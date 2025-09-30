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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_algorithm.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"


#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
LayoutConstraintF layoutConstraintF = { .maxSize = { 200, 910 },
    .parentIdealSize = { 200, 910 },
    .selfIdealSize = { 200, 910 } };

class ContainerPickerLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<Theme> GetThemeByType(ThemeType type);

    RefPtr<IconTheme> iconThem_;
    RefPtr<PickerTheme> pickerTheme_;
    RefPtr<ContainerPickerLayoutAlgorithm> algorithm_;
};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

void ContainerPickerLayoutAlgorithmTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void ContainerPickerLayoutAlgorithmTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ContainerPickerLayoutAlgorithmTest::SetUp()
{
    iconThem_ = AceType::MakeRefPtr<IconTheme>();
    pickerTheme_ = AceType::MakeRefPtr<PickerTheme>();
    algorithm_ = AceType::MakeRefPtr<ContainerPickerLayoutAlgorithm>();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([this](ThemeType type) -> RefPtr<Theme> {
        return GetThemeByType(type);
    });

    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([this](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetThemeByType(type); });
}

void ContainerPickerLayoutAlgorithmTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> ContainerPickerLayoutAlgorithmTest::GetThemeByType(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return iconThem_;
    } else if (type == PickerTheme::TypeId()) {
        return pickerTheme_;
    } else {
        return nullptr;
    }
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithmMeasureSizeTest001
 * @tc.desc: Test MeasureSize method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithmMeasureSizeTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set contentIdealSize and call MeasureSize
     * @tc.expected: step2. The contentIdealSize should be updated correctly
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureSize(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_TRUE(contentIdealSize.Width().has_value());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithmMeasureHeightTest001
 * @tc.desc: Test MeasureHeight method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithmMeasureHeightTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set contentIdealSize and call MeasureHeight
     * @tc.expected: step2. The height should be set correctly
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_FALSE(NearEqual(algorithm_->height_, -1.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithmMeasureWidthTest001
 * @tc.desc: Test MeasureWidth method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithmMeasureWidthTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set contentIdealSize and call MeasureWidth
     * @tc.expected: step2. The width should be set correctly
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithmCalcMainAndMiddlePosTest001
 * @tc.desc: Test CalcMainAndMiddlePos method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithmCalcMainAndMiddlePosTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set height and call CalcMainAndMiddlePos
     * @tc.expected: step1. The main and middle positions should be calculated correctly
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();

    EXPECT_TRUE(NearEqual(algorithm_->startMainPos_, 0.0f));
    EXPECT_TRUE(NearEqual(algorithm_->endMainPos_, 500.0f));
    EXPECT_TRUE(NearEqual(algorithm_->middleItemStartPos_, 185.0f));
    EXPECT_TRUE(NearEqual(algorithm_->middleItemEndPos_, 315.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithmMeasurePickerItemsTest001
 * @tc.desc: Test MeasurePickerItems method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithmMeasurePickerItemsTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and add child nodes
     */
    ContainerPickerModel picker;
    picker.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);

    // Add some child nodes
    for (int i = 0; i < 5; i++) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        frameNode->AddChild(textNode);
    }

    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set algorithm properties and call MeasurePickerItems
     * @tc.expected: step2. The items should be measured correctly
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };

    algorithm_->MeasurePickerItems(layoutWrapper, layoutConstraint);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithmTranslateAndRotateTest001
 * @tc.desc: Test TranslateAndRotate method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithmTranslateAndRotateTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create FrameNode and set up necessary properties
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    // Set up algorithm properties needed for TranslateAndRotate
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->topPadding_ = 20.0f;

    /**
     * @tc.steps: step2. Test TranslateAndRotate with different offset values
     */
    // Test case 1: Zero offset
    OffsetF offset1(0.0f, 0.0f);
    float originalY1 = offset1.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset1);
    EXPECT_TRUE(GreatNotEqual(offset1.GetY(), originalY1));

    // Test case 2: Positive offset
    OffsetF offset2(0.0f, 100.0f);
    float originalY2 = offset2.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset2);
    EXPECT_TRUE(GreatNotEqual(offset2.GetY(), originalY2));

    // Test case 3: Negative offset
    OffsetF offset3(0.0f, -100.0f);
    float originalY3 = offset3.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset3);
    EXPECT_TRUE(GreatNotEqual(offset3.GetY(), originalY3));

    // Test case 4: Large positive offset (should be clamped to VERTICAL_ANGLE)
    OffsetF offset4(0.0f, 1000.0f);
    float originalY4 = offset4.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset4);
    EXPECT_TRUE(NearEqual(offset4.GetY(), originalY4));

    // Test case 5: Large negative offset (should be clamped to -VERTICAL_ANGLE)
    OffsetF offset5(0.0f, -1000.0f);
    float originalY5 = offset5.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset5);
    EXPECT_TRUE(NearEqual(offset5.GetY(), originalY5));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithmGetStartEndPositionTest001
 * @tc.desc: Test GetStartPosition and GetEndPosition methods of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithmGetStartEndPositionTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Add items to itemPosition_
     */
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, nullptr };
    algorithm_->itemPosition_[1] = { 150.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[2] = { 200.0f, 250.0f, nullptr };

    /**
     * @tc.steps: step2. Test GetStartPosition and GetEndPosition
     * @tc.expected: step2. The positions should be returned correctly
     */
    EXPECT_TRUE(NearEqual(algorithm_->GetStartPosition(), 100.0f));
    EXPECT_TRUE(NearEqual(algorithm_->GetEndPosition(), 250.0f));

    // Test with empty itemPosition_
    algorithm_->itemPosition_.clear();
    EXPECT_TRUE(NearEqual(algorithm_->GetStartPosition(), 0.0f));
    EXPECT_TRUE(NearEqual(algorithm_->GetEndPosition(), 0.0f));
}
} // namespace OHOS::Ace::NG
