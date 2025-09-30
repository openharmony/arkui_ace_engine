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
    RefPtr<FrameNode> frameNode_;
    void CreateContainerPickerNode(int32_t itemCount = 9);
    void AddChildNodes(RefPtr<FrameNode>& parentNode, int32_t count);
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

void ContainerPickerLayoutAlgorithmTest::CreateContainerPickerNode(int32_t itemCount)
{
    ContainerPickerModel picker;
    picker.Create();
    frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode_, nullptr);

    if (itemCount > 0) {
        AddChildNodes(frameNode_, itemCount);
    }
}

void ContainerPickerLayoutAlgorithmTest::AddChildNodes(RefPtr<FrameNode>& parentNode, int32_t count)
{
    for (int i = 0; i < count; i++) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        parentNode->AddChild(textNode);
    }
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureSizeTest001
 * @tc.desc: Test MeasureSize method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureSizeTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest001
 * @tc.desc: Test MeasureHeight method of ContainerPickerLayoutAlgorithm with defined height
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set contentIdealSize with defined height and call MeasureHeight
     * @tc.expected: step2. The height should be set correctly
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_FALSE(NearEqual(algorithm_->height_, -1.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest002
 * @tc.desc: Test MeasureHeight method of ContainerPickerLayoutAlgorithm with undefined height
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and modify layout constraint
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    LayoutConstraintF constraint = layoutConstraintF;
    constraint.selfIdealSize = { 200, -1 };
    layoutProperty->contentConstraint_ = constraint;

    /**
     * @tc.steps: step2. Call MeasureHeight with undefined height
     * @tc.expected: step2. The default height should be used
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_FALSE(NearEqual(algorithm_->height_, -1.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest003
 * @tc.steps: Test MeasureHeight method with height change
 * @tc.expected: itemPosition_ should be cleared when height changes
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set initial height
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    algorithm_->SetHeight(500.0f);
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, nullptr };
    ASSERT_FALSE(algorithm_->itemPosition_.empty());

    /**
     * @tc.steps: step2. Change height and call MeasureHeight
     * @tc.expected: itemPosition_ should be cleared when height changes
     */
    OptionalSizeF contentIdealSize;
    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    LayoutConstraintF constraint = layoutConstraintF;
    constraint.selfIdealSize = { 200, 600 };
    layoutProperty->contentConstraint_ = constraint;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureWidthTest001
 * @tc.desc: Test MeasureWidth method of ContainerPickerLayoutAlgorithm with default width
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureWidthTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureWidthTest002
 * @tc.desc: Test MeasureWidth method of ContainerPickerLayoutAlgorithm with WRAP_CONTENT policy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureWidthTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set WRAP_CONTENT policy
     */
    CreateContainerPickerNode();
    algorithm_->widthLayoutPolicy = LayoutCalPolicy::WRAP_CONTENT;
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Call MeasureWidth with WRAP_CONTENT policy
     * @tc.expected: step2. The width should be calculated correctly
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureWidthTest003
 * @tc.desc: Test MeasureWidth method of ContainerPickerLayoutAlgorithm with FIX_AT_IDEAL_SIZE policy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureWidthTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set FIX_AT_IDEAL_SIZE policy
     */
    CreateContainerPickerNode();
    algorithm_->widthLayoutPolicy = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Call MeasureWidth with FIX_AT_IDEAL_SIZE policy
     * @tc.expected: step2. The width should be set to ideal size
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_CalcMainAndMiddlePosTest001
 * @tc.desc: Test CalcMainAndMiddlePos method of ContainerPickerLayoutAlgorithm with default height
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_CalcMainAndMiddlePosTest001, TestSize.Level0)
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
 * @tc.name: ContainerPickerLayoutAlgorithm_CalcMainAndMiddlePosTest002
 * @tc.desc: Test CalcMainAndMiddlePos method of ContainerPickerLayoutAlgorithm with large height
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_CalcMainAndMiddlePosTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set large height and call CalcMainAndMiddlePos
     * @tc.expected: step1. The positions should be calculated correctly with padding
     */
    algorithm_->SetHeight(1200.0f);
    algorithm_->CalcMainAndMiddlePos();

    EXPECT_TRUE(NearEqual(algorithm_->startMainPos_, 145.0f));
    EXPECT_TRUE(NearEqual(algorithm_->endMainPos_, 1055.0f));
    EXPECT_TRUE(NearEqual(algorithm_->middleItemStartPos_, 535.0f));
    EXPECT_TRUE(NearEqual(algorithm_->middleItemEndPos_, 665.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasurePickerItemsTest001
 * @tc.desc: Test MeasurePickerItems method of ContainerPickerLayoutAlgorithm with items
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasurePickerItemsTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(5);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasurePickerItemsTest002
 * @tc.desc: Test MeasurePickerItems method of ContainerPickerLayoutAlgorithm with existing item positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasurePickerItemsTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(5);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set existing item positions
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;
    algorithm_->selectedIndex_ = 2;

    algorithm_->itemPosition_[1] = { 185.0f, 315.0f, nullptr };

    /**
     * @tc.steps: step3. Call MeasurePickerItems
     * @tc.expected: step3. The items should be measured correctly based on existing positions
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };

    algorithm_->MeasurePickerItems(layoutWrapper, layoutConstraint);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_GetStartEndPositionTest001
 * @tc.desc: Test GetStartPosition and GetEndPosition methods of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_GetStartEndPositionTest001, TestSize.Level0)
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

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_GetStartEndIndexTest001
 * @tc.desc: Test GetStartIndex and GetEndIndex methods of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_GetStartEndIndexTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Add items to itemPosition_
     */
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, nullptr };
    algorithm_->itemPosition_[1] = { 150.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[2] = { 200.0f, 250.0f, nullptr };

    /**
     * @tc.steps: step2. Test GetStartIndex and GetEndIndex
     * @tc.expected: step2. The indexes should be returned correctly
     */
    EXPECT_EQ(algorithm_->GetStartIndex(), 0);
    EXPECT_EQ(algorithm_->GetEndIndex(), 2);

    // Test with empty itemPosition_
    algorithm_->itemPosition_.clear();
    EXPECT_EQ(algorithm_->GetStartIndex(), 0);
    EXPECT_EQ(algorithm_->GetEndIndex(), 0);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureBelowTest001
 * @tc.desc: Test MeasureBelow method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureBelowTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(5);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set up algorithm and call MeasureBelow
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };

    algorithm_->MeasureBelow(layoutWrapper, layoutConstraint, 2, 185.0f);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureBelowTest002
 * @tc.desc: Test MeasureBelow method with overScrollFeature enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureBelowTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(5);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set up algorithm with overScrollFeature and call MeasureBelow
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;
    algorithm_->overScrollFeature_ = true;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };

    algorithm_->MeasureBelow(layoutWrapper, layoutConstraint, 2, 185.0f);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureAboveTest001
 * @tc.desc: Test MeasureAbove method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureAboveTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(5);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set up algorithm and call MeasureAbove
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };

    algorithm_->MeasureAbove(layoutWrapper, layoutConstraint, 2, 315.0f);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureAboveTest002
 * @tc.desc: Test MeasureAbove method with overScrollFeature enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureAboveTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(5);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set up algorithm with overScrollFeature and call MeasureAbove
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;
    algorithm_->overScrollFeature_ = true;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };

    algorithm_->MeasureAbove(layoutWrapper, layoutConstraint, 2, 315.0f);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_NeedMeasureBelowTest001
 * @tc.desc: Test NeedMeasureBelow method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_NeedMeasureBelowTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up algorithm properties
     */
    algorithm_->contentMainSize_ = 500.0f;

    /**
     * @tc.steps: step2. Test different scenarios
     * @tc.expected: step2. The return value should be correct based on conditions
     */
    EXPECT_TRUE(algorithm_->NeedMeasureBelow(0, 100.0f, 500.0f, false));
    EXPECT_FALSE(algorithm_->NeedMeasureBelow(0, 600.0f, 500.0f, false));

    // Test with overScrollFeature
    algorithm_->overScrollFeature_ = true;
    EXPECT_FALSE(algorithm_->NeedMeasureBelow(0, 600.0f, 500.0f, false));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_NeedMeasureAboveTest001
 * @tc.desc: Test NeedMeasureAbove method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_NeedMeasureAboveTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Test different scenarios
     * @tc.expected: step1. The return value should be correct based on conditions
     */
    EXPECT_TRUE(algorithm_->NeedMeasureAbove(0, 100.0f, 50.0f, false));
    EXPECT_FALSE(algorithm_->NeedMeasureAbove(0, 30.0f, 50.0f, false));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_AdjustOffsetOnBelowTest001
 * @tc.desc: Test AdjustOffsetOnBelow method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_AdjustOffsetOnBelowTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up itemPosition_ with last item at the bottom
     */
    algorithm_->itemPosition_[0] = { 100.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[1] = { 200.0f, 300.0f, nullptr };
    algorithm_->itemPosition_[2] = { 300.0f, 400.0f, nullptr };
    algorithm_->totalItemCount_ = 3;
    algorithm_->middleItemEndPos_ = 400.0f;
    algorithm_->currentOffset_ = 100.0f;
    algorithm_->canOverScroll_ = false;

    /**
     * @tc.steps: step2. Call AdjustOffsetOnBelow
     * @tc.expected: step2. The currentOffset_ should be adjusted to 0
     */
    algorithm_->AdjustOffsetOnBelow(400.0f);
    EXPECT_TRUE(NearEqual(algorithm_->currentOffset_, 0.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_AdjustOffsetOnBelowTest002
 * @tc.desc: Test AdjustOffsetOnBelow method with canOverScroll enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_AdjustOffsetOnBelowTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up itemPosition_ and enable canOverScroll
     */
    algorithm_->itemPosition_[0] = { 100.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[1] = { 200.0f, 300.0f, nullptr };
    algorithm_->totalItemCount_ = 2;
    algorithm_->middleItemEndPos_ = 250.0f;
    algorithm_->currentOffset_ = 100.0f;
    algorithm_->canOverScroll_ = true;

    /**
     * @tc.steps: step2. Call AdjustOffsetOnBelow
     * @tc.expected: step2. The currentOffset_ should not be adjusted
     */
    algorithm_->AdjustOffsetOnBelow(300.0f);
    EXPECT_TRUE(NearEqual(algorithm_->currentOffset_, 100.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_AdjustOffsetOnAboveTest001
 * @tc.desc: Test AdjustOffsetOnAbove method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_AdjustOffsetOnAboveTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up itemPosition_ with first item at the top
     */
    algorithm_->itemPosition_[0] = { 100.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[1] = { 200.0f, 300.0f, nullptr };
    algorithm_->middleItemStartPos_ = 100.0f;
    algorithm_->currentOffset_ = -50.0f;
    algorithm_->canOverScroll_ = false;

    /**
     * @tc.steps: step2. Call AdjustOffsetOnAbove
     * @tc.expected: step2. The currentOffset_ should be adjusted to 0
     */
    algorithm_->AdjustOffsetOnAbove(100.0f);
    EXPECT_TRUE(NearEqual(algorithm_->currentOffset_, 0.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_AdjustOffsetOnAboveTest002
 * @tc.desc: Test AdjustOffsetOnAbove method with canOverScroll enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_AdjustOffsetOnAboveTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up itemPosition_ and enable canOverScroll
     */
    algorithm_->itemPosition_[0] = { 100.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[1] = { 200.0f, 300.0f, nullptr };
    algorithm_->middleItemStartPos_ = 150.0f;
    algorithm_->currentOffset_ = -50.0f;
    algorithm_->canOverScroll_ = true;

    /**
     * @tc.steps: step2. Call AdjustOffsetOnAbove
     * @tc.expected: step2. The currentOffset_ should not be adjusted
     */
    algorithm_->AdjustOffsetOnAbove(100.0f);
    EXPECT_TRUE(NearEqual(algorithm_->currentOffset_, -50.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_GetChildMainAxisSizeTest001
 * @tc.desc: Test GetChildMainAxisSize method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_GetChildMainAxisSizeTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a child node with geometry
     */
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto childLayoutWrapper = textNode->CreateLayoutWrapper();
    auto geometryNode = childLayoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100.0f, 50.0f));

    /**
     * @tc.steps: step2. Call GetChildMainAxisSize
     * @tc.expected: step2. The correct main axis size should be returned
     */
    float mainAxisSize = algorithm_->GetChildMainAxisSize(childLayoutWrapper);
    EXPECT_TRUE(NearEqual(mainAxisSize, 50.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_LayoutTest001
 * @tc.desc: Test Layout method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_LayoutTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;
    for (int i = 0; i < 3; i++) {
        auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(i));
        algorithm_->itemPosition_[i] = { 100.0f * i, 100.0f * (i + 1), childNode };
    }

    algorithm_->currentOffset_ = 50.0f;

    /**
     * @tc.steps: step2. Call Layout
     * @tc.expected: step2. The items should be laid out correctly
     */
    algorithm_->Layout(layoutWrapper);

    for (const auto& pos : algorithm_->itemPosition_) {
        EXPECT_TRUE(NearEqual(pos.second.startPos, 100.0f * pos.first - 50.0f));
        EXPECT_TRUE(NearEqual(pos.second.endPos, 100.0f * (pos.first + 1) - 50.0f));
    }
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_LayoutItemTest001
 * @tc.desc: Test LayoutItem method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_LayoutItemTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with a child node
     */
    CreateContainerPickerNode(1);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    std::pair<int32_t, PickerItemInfo> pos = { 0, { 100.0f, 200.0f, childNode } };

    /**
     * @tc.steps: step2. Call LayoutItem
     * @tc.expected: step2. The item should be laid out at the correct position
     */
    algorithm_->LayoutItem(layoutWrapper, OffsetF(0.0f, 0.0f), pos);

    auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childLayoutWrapper, nullptr);
    auto childGeometryNode = childLayoutWrapper->GetGeometryNode();
    ASSERT_NE(childGeometryNode, nullptr);
    EXPECT_TRUE(GreatNotEqual(childGeometryNode->GetMarginFrameOffset().GetY(), 0.0f));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureTest001
 * @tc.desc: Test Measure method of ContainerPickerLayoutAlgorithm with items
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(3);
    algorithm_->SetTotalItemCount(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Call Measure
     * @tc.expected: step2. The container and items should be measured correctly
     */
    algorithm_->Measure(layoutWrapper);

    EXPECT_TRUE(algorithm_->measured_);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureTest002
 * @tc.desc: Test Measure method of ContainerPickerLayoutAlgorithm with loop enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
     */
    CreateContainerPickerNode(3);
    algorithm_->SetTotalItemCount(3);
    algorithm_->SetIsLoop(true);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Call Measure
     * @tc.expected: step2. The container and items should be measured correctly in loop mode
     */
    algorithm_->Measure(layoutWrapper);

    EXPECT_TRUE(algorithm_->measured_);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureTest003
 * @tc.desc: Test Measure method of ContainerPickerLayoutAlgorithm with no items
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker without child nodes
     */
    CreateContainerPickerNode(0);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Call Measure with no items
     * @tc.expected: step2. The container should still be measured correctly
     */
    algorithm_->Measure(layoutWrapper);

    EXPECT_TRUE(algorithm_->measured_);
    EXPECT_TRUE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_SetGetMethodsTest001
 * @tc.desc: Test set and get methods of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_SetGetMethodsTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set various properties
     */
    algorithm_->SetIsLoop(true);
    algorithm_->SetSelectedIndex(2);
    algorithm_->SetContentMainSize(500.0f);
    algorithm_->SetHeight(600.0f);
    algorithm_->SetCurrentDelta(100.0f);

    /**
     * @tc.steps: step2. Verify get methods return correct values
     * @tc.expected: step2. The get methods should return the values set in step1
     */
    EXPECT_TRUE(algorithm_->isLoop_);
    EXPECT_EQ(algorithm_->selectedIndex_, 2);
    EXPECT_TRUE(NearEqual(algorithm_->GetContentMainSize(), 500.0f));
    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), 600.0f));
    EXPECT_TRUE(NearEqual(algorithm_->GetCurrentOffset(), 100.0f));
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

}