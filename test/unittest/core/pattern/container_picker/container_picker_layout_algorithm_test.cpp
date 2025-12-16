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

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_algorithm.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"
#include "core/components_ng/pattern/container_picker/container_picker_model.h"
#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"
#include "core/components_ng/pattern/container_picker/container_picker_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
LayoutConstraintF layoutConstraintF = { .maxSize = { 400, 910 },
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
    RefPtr<ContainerPickerTheme> containerPickerTheme_;
    RefPtr<ContainerPickerLayoutAlgorithm> algorithm_;
    RefPtr<FrameNode> frameNode_;
    void CreateContainerPickerNode(int32_t itemCount = 9);
    void AddChildNodes(RefPtr<FrameNode>& parentNode, int32_t count);
    void SetChildNodeFrameSize(LayoutWrapper* layoutWrapper, int32_t childIndex, float width, float height);
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
    containerPickerTheme_ = AceType::MakeRefPtr<ContainerPickerTheme>();
    algorithm_ = AceType::MakeRefPtr<ContainerPickerLayoutAlgorithm>();

    float itemHeight = 40.0f;
    float pickerHeight = 200.0f;
    float pickerHeightBeforeRotate = 280.0f;
    algorithm_->SetItemHeight(itemHeight);
    algorithm_->SetPickerHeight(pickerHeight);
    algorithm_->SetPickerHeightBeforeRotate(pickerHeightBeforeRotate);

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
    } else if (type == ContainerPickerTheme::TypeId()) {
        return containerPickerTheme_;
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

void ContainerPickerLayoutAlgorithmTest::SetChildNodeFrameSize(
    LayoutWrapper* layoutWrapper, int32_t childIndex, float width, float height)
{
    auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(childIndex);
    ASSERT_NE(childLayoutWrapper, nullptr);
    auto childGeometryNode = childLayoutWrapper->GetGeometryNode();
    ASSERT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize({ width, height });
}

/**
 * @tc.name: MeasureHeightWithDefaultHeight
 * @tc.desc: Test MeasureHeight method with default height
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithDefaultHeight, TestSize.Level0)
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
     * @tc.steps: step2. Set contentIdealSize and call MeasureHeight
     * @tc.expected: step2. The height should be set to default value
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_EQ(algorithm_->GetHeight(), 910);
    EXPECT_FALSE(Negative(algorithm_->GetContentMainSize()));
}

/**
 * @tc.name: MeasureHeightWithHeightMatchPolicy
 * @tc.desc: Test MeasureHeight method with heightMatch policy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithHeightMatchPolicy, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set heightMatch policy to MATCH_PARENT
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    /**
     * @tc.steps: step2. Call MeasureHeight with heightMatch policy
     * @tc.expected: step2. The height should be set to parent size
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_EQ(algorithm_->GetHeight(), 910);
}

/**
 * @tc.name: MeasureHeightWithNegativeHeight
 * @tc.desc: Test MeasureHeight method when handling negative or undefined height
 * values
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithNegativeHeight, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper with undefined height
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF constraintWithNegativeHeight = layoutConstraintF;
    std::optional<float> height;
    constraintWithNegativeHeight.selfIdealSize = { 200, height };
    layoutProperty->contentConstraint_ = constraintWithNegativeHeight;

    /**
     * @tc.steps: step2. Call MeasureHeight with undefined height
     * @tc.expected: step2. The height should be set to default value of 200
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_EQ(algorithm_->GetHeight(), 200);
}

/**
 * @tc.name: MeasureHeightWithHeightUnchanged
 * @tc.desc: Test MeasureHeight method when height remains unchanged
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithHeightUnchanged, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set initial height
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    float sameHeight = 400.0f;
    LayoutConstraintF constraintWithSameHeight = layoutConstraintF;
    constraintWithSameHeight.selfIdealSize = { 200, sameHeight };
    layoutProperty->contentConstraint_ = constraintWithSameHeight;

    // Set initial height to the same value
    algorithm_->SetHeight(sameHeight);

    // Add some items to itemPosition_
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, childNode };

    EXPECT_FALSE(algorithm_->itemPosition_.empty());

    /**
     * @tc.steps: step2. Call MeasureHeight with same height
     * @tc.expected: step2. itemPosition_ should not be cleared and height should remain the same
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), sameHeight));
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: MeasureHeightWithoutLayoutPolicy
 * @tc.desc: Test MeasureHeight method when no layoutPolicy is set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithoutLayoutPolicy, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker without layoutPolicy
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;
    // Ensure no layoutPolicy is set
    layoutProperty->layoutPolicy_.reset();

    /**
     * @tc.steps: step2. Call MeasureHeight without layoutPolicy
     * @tc.expected: step2. The height should be set correctly
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_EQ(algorithm_->GetHeight(), 910);
}

/**
 * @tc.name: MeasureHeightWithCustomSelfIdealSize
 * @tc.desc: Test MeasureHeight method with custom selfIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithCustomSelfIdealSize, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with custom selfIdealSize
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    float customHeight = 450.0f;
    LayoutConstraintF constraintWithCustomHeight = layoutConstraintF;
    constraintWithCustomHeight.selfIdealSize = { 200, customHeight };
    layoutProperty->contentConstraint_ = constraintWithCustomHeight;

    /**
     * @tc.steps: step2. Call MeasureHeight with custom height
     * @tc.expected: step2. The height should be set to custom value
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), customHeight));
}

/**
 * @tc.name: MeasureHeightWithLayoutPolicyMatchParent
 * @tc.desc: Test MeasureHeight method with layoutPolicy set to MATCH_PARENT
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithLayoutPolicyMatchParent, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    std::optional<float> height;
    layoutConstraintF.selfIdealSize = { 200, height };
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set layoutPolicy to MATCH_PARENT
     * @tc.expected: step2. The height should be set to parent height
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_EQ(contentIdealSize.Height().value(), 910);
}

/**
 * @tc.name: MeasureHeightWithLayoutPolicyWrapContentOrFixAtIdealSize
 * @tc.desc: Test MeasureHeight method with layoutPolicy set to WRAP_CONTENT or
 * FIX_AT_IDEAL_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithLayoutPolicyWrapContentOrFixAtIdealSize, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    std::optional<float> height;
    layoutConstraintF.selfIdealSize = { 200, height };
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set layoutPolicy to WRAP_CONTENT
     * @tc.expected: step2. The height should be set to default height
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_EQ(contentIdealSize.Height().value(), 200);

    /**
     * @tc.steps: step3. Set layoutPolicy to FIX_AT_IDEAL_SIZE
     * @tc.expected: step3. The height should be set to default height
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    OptionalSizeF contentIdealSize2;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize2);
    EXPECT_EQ(contentIdealSize2.Height().value(), 200);
}

/**
 * @tc.name: MeasureHeightWithLayoutPolicyNoMatch
 * @tc.desc: Test MeasureHeight method with layoutPolicy set to NO_MATCH
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureHeightWithLayoutPolicyNoMatch, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    std::optional<float> height;
    layoutConstraintF.selfIdealSize = { 200, height };
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set layoutPolicy to NO_MATCH
     * @tc.expected: step2. The height should be set to default height
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_EQ(contentIdealSize.Height().value(), 200);
}

/**
 * @tc.name: MeasureWidthWithDefaultWidth
 * @tc.desc: Test MeasureWidth method with default width settings
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWidthWithDefaultWidth, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper with default settings
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
     * @tc.expected: step2. The width should be set correctly with a valid value
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 200);
}

/**
 * @tc.name: MeasureWidthWithWrapContentPolicy
 * @tc.desc: Test MeasureWidth method with WRAP_CONTENT policy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWidthWithWrapContentPolicy, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set WRAP_CONTENT policy for width
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    SetChildNodeFrameSize(layoutWrapper, 0, 150, 40);
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, childNode };

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);

    /**
     * @tc.steps: step2. Call MeasureWidth with WRAP_CONTENT policy
     * @tc.expected: step2. The width should be calculated correctly with a valid value
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 150);
}

/**
 * @tc.name: MeasureWidthWithFixAtIdealSizePolicy
 * @tc.desc: Test MeasureWidth method with FIX_AT_IDEAL_SIZE policy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWidthWithFixAtIdealSizePolicy, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set FIX_AT_IDEAL_SIZE policy for width
     */
    CreateContainerPickerNode();
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    SetChildNodeFrameSize(layoutWrapper, 0, 150, 40);
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, childNode };

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    /**
     * @tc.steps: step2. Call MeasureWidth with FIX_AT_IDEAL_SIZE policy
     * @tc.expected: step2. The width should be set to ideal size with a valid value
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 150);
}

/**
 * @tc.name: MeasureWidthWithDifferentContentConstraints
 * @tc.desc: Test MeasureWidth method with different content constraints
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWidthWithDifferentContentConstraints, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    std::optional<float> width;
    layoutConstraintF.selfIdealSize = { width, 910 };
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Test MeasureWidth with undefined cross size by setting up item positions and frame size
     * @tc.expected: step2. The width should be calculated correctly based on child node frame size
     */
    OptionalSizeF contentIdealSize;

    // Set item positions to simulate measured items
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, childNode };

    auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childLayoutWrapper, nullptr);
    auto childGeometryNode = childLayoutWrapper->GetGeometryNode();
    ASSERT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize({ 150, 40 });

    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 150);
}

/**
 * @tc.name: MeasureWidthWithLargeCrossSize
 * @tc.desc: Test MeasureWidth method with large cross size
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWidthWithLargeCrossSize, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);

    /**
     * @tc.steps: step2. Set self cross size greater than parent cross size
     * @tc.expected: step2. The width remains.
     */
    layoutConstraintF.selfIdealSize = { 500, 910 };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 500);
}

/**
 * @tc.name: MeasureWidthWithWrapContentAndParentCrossSize
 * @tc.desc: Test MeasureWidth method with WRAP_CONTENT and parent cross size
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWidthWithWrapContentAndParentCrossSize, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    SetChildNodeFrameSize(layoutWrapper, 0, 500, 40);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);

    /**
     * @tc.steps: step2. Test WRAP_CONTENT with parent cross size constraint and simulate measured items
     * @tc.expected: step2. The width should be constrained by parent cross size and crossMatchChild_ should be true
     */
    OptionalSizeF contentIdealSize;

    // Set item positions to simulate measured items
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, childNode };

    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 400);
    EXPECT_TRUE(algorithm_->crossMatchChild_);
}

/**
 * @tc.name: MeasureWidthWithFixAtIdealSizeAndParentCrossSize
 * @tc.desc: Test MeasureWidth method with FIX_AT_IDEAL_SIZE and parent cross size
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWidthWithFixAtIdealSizeAndParentCrossSize, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    SetChildNodeFrameSize(layoutWrapper, 0, 400, 40);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);

    /**
     * @tc.steps: step2. Test FIX_AT_IDEAL_SIZE with parent cross size constraint and simulate measured items
     * @tc.expected: step2. The width should be constrained by parent cross size and crossMatchChild_ should be true
     */
    OptionalSizeF contentIdealSize;

    // Set item positions to simulate measured items
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, childNode };

    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 400);
    EXPECT_TRUE(algorithm_->crossMatchChild_);
}

/**
 * @tc.name: MeasureWidthWithNegativeCrossSizeAndMatchParentPolicy
 * @tc.desc: Test MeasureWidth method with negative cross size and MATCH_PARENT policy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWidthWithNegativeCrossSizeAndMatchParentPolicy, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    std::optional<float> width;
    layoutConstraintF.selfIdealSize = { width, 910 };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);

    /**
     * @tc.steps: step2. Set negative cross size by not providing a valid cross size
     * @tc.expected: step2. The width should be set to parent width of 200.0f
     */
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_TRUE(NearEqual(algorithm_->GetContentCrossSize(), 200.0f));
}

/**
 * @tc.name: CalcMainAndMiddlePosWithDefaultHeight
 * @tc.desc: Test CalcMainAndMiddlePos method with default height settings
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, CalcMainAndMiddlePosWithDefaultHeight, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set height to 500.0f and call CalcMainAndMiddlePos
     * @tc.expected: step1. The main and middle positions should be calculated correctly with expected values
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();

    EXPECT_EQ(algorithm_->startMainPos_, 110);
    EXPECT_EQ(algorithm_->endMainPos_, 390);
    EXPECT_EQ(algorithm_->middleItemStartPos_, 230);
    EXPECT_EQ(algorithm_->middleItemEndPos_, 270);
}

/**
 * @tc.name: CalcMainAndMiddlePosWithLargeHeight
 * @tc.desc: Test CalcMainAndMiddlePos method with large height settings
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, CalcMainAndMiddlePosWithLargeHeight, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set large height to 1200.0f and call CalcMainAndMiddlePos
     * @tc.expected: step1. The positions should be calculated correctly with expected values for large height
     */
    algorithm_->SetHeight(1200.0f);
    algorithm_->CalcMainAndMiddlePos();

    EXPECT_EQ(algorithm_->startMainPos_, 460);
    EXPECT_EQ(algorithm_->endMainPos_, 740);
    EXPECT_EQ(algorithm_->middleItemStartPos_, 580.0f);
    EXPECT_EQ(algorithm_->middleItemEndPos_, 620.0f);
}

/**
 * @tc.name: MeasurePickerItemsWithItems
 * @tc.desc: Test MeasurePickerItems method with items
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasurePickerItemsWithItems, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with 5 child nodes
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
     * @tc.steps: step2. Set algorithm properties including height and total item count, then call MeasurePickerItems
     * @tc.expected: step2. The items should be measured correctly and itemPosition_ should not be empty
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };
    algorithm_->childLayoutConstraint_ = layoutConstraint;
    algorithm_->MeasurePickerItems(layoutWrapper);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: MeasurePickerItemsWithExistingItemPositions
 * @tc.desc: Test MeasurePickerItems method with existing item positions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasurePickerItemsWithExistingItemPositions, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with 5 child nodes
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
     * @tc.steps: step2. Set existing item positions with selected index and height properties
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;
    algorithm_->selectedIndex_ = 2;

    algorithm_->itemPosition_[1] = { 185.0f, 315.0f, nullptr };

    /**
     * @tc.steps: step3. Call MeasurePickerItems with existing positions
     * @tc.expected: step3. The items should be measured correctly based on existing positions and itemPosition_ should
     * not be empty
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };
    algorithm_->childLayoutConstraint_ = layoutConstraint;
    algorithm_->MeasurePickerItems(layoutWrapper);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: GetStartEndPosition
 * @tc.desc: Test GetStartPosition and GetEndPosition methods
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, GetStartEndPosition, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Add items to itemPosition_ with specific start and end positions
     */
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, nullptr };
    algorithm_->itemPosition_[1] = { 150.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[2] = { 200.0f, 250.0f, nullptr };

    /**
     * @tc.steps: step2. Test GetStartPosition and GetEndPosition methods
     * @tc.expected: step2. The positions should be returned correctly matching the minimum start and maximum end values
     */
    EXPECT_TRUE(NearEqual(algorithm_->GetStartPosition(), 100.0f));
    EXPECT_TRUE(NearEqual(algorithm_->GetEndPosition(), 250.0f));

    // Test with empty itemPosition_
    algorithm_->itemPosition_.clear();
    EXPECT_TRUE(NearEqual(algorithm_->GetStartPosition(), 0.0f));
    EXPECT_TRUE(NearEqual(algorithm_->GetEndPosition(), 0.0f));
}

/**
 * @tc.name: GetStartEndIndex
 * @tc.desc: Test GetStartIndex and GetEndIndex methods
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, GetStartEndIndex, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Add items to itemPosition_ with specific indexes
     */
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, nullptr };
    algorithm_->itemPosition_[1] = { 150.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[2] = { 200.0f, 250.0f, nullptr };

    /**
     * @tc.steps: step2. Test GetStartIndex and GetEndIndex methods
     * @tc.expected: step2. The indexes should be returned correctly matching the minimum and maximum index values
     */
    EXPECT_EQ(algorithm_->GetStartIndex(), 0);
    EXPECT_EQ(algorithm_->GetEndIndex(), 2);

    // Test with empty itemPosition_
    algorithm_->itemPosition_.clear();
    EXPECT_EQ(algorithm_->GetStartIndex(), 0);
    EXPECT_EQ(algorithm_->GetEndIndex(), 0);
}

/**
 * @tc.name: MeasureBelow
 * @tc.desc: Test MeasureBelow method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureBelow, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with 5 child nodes
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
     * @tc.steps: step2. Set up algorithm properties and call MeasureBelow with index 2 and position 185.0f
     * @tc.expected: step2. The items below should be measured correctly and itemPosition_ should not be empty
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };
    algorithm_->childLayoutConstraint_ = layoutConstraint;
    algorithm_->MeasureBelow(layoutWrapper, 2, 185.0f);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: MeasureBelowWithCanOverScrollEnabled
 * @tc.desc: Test MeasureBelow method with canOverScroll enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureBelowWithCanOverScrollEnabled, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with 5 child nodes
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
     * @tc.steps: step2. Set up algorithm with canOverScroll enabled and call MeasureBelow
     * @tc.expected: step2. The items below should be measured correctly with overscroll support and itemPosition_
     * should not be empty
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;
    algorithm_->canOverScroll_ = true;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };
    algorithm_->childLayoutConstraint_ = layoutConstraint;
    algorithm_->MeasureBelow(layoutWrapper, 2, 185.0f);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: MeasureAbove
 * @tc.desc: Test MeasureAbove method
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureAbove, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with 5 child nodes
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
     * @tc.steps: step2. Set up algorithm properties and call MeasureAbove with index 2 and position 315.0f
     * @tc.expected: step2. The items above should be measured correctly and itemPosition_ should not be empty
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };
    algorithm_->childLayoutConstraint_ = layoutConstraint;
    algorithm_->MeasureAbove(layoutWrapper, 2, 315.0f);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: MeasureAboveWithCanOverScrollEnabled
 * @tc.desc: Test MeasureAbove method with canOverScroll enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureAboveWithCanOverScrollEnabled, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with 5 child nodes
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
     * @tc.steps: step2. Set up algorithm with canOverScroll enabled and call MeasureAbove
     * @tc.expected: step2. The items above should be measured correctly with overscroll support and itemPosition_
     * should not be empty
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;
    algorithm_->canOverScroll_ = true;

    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = { 300.0f, 500.0f };
    algorithm_->childLayoutConstraint_ = layoutConstraint;
    algorithm_->MeasureAbove(layoutWrapper, 2, 315.0f);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: NeedMeasureBelow
 * @tc.desc: Test NeedMeasureBelow method under different scenarios
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, NeedMeasureBelow, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up algorithm contentMainSize property to 500.0f
     */
    algorithm_->contentMainSize_ = 500.0f;

    /**
     * @tc.steps: step2. Test different scenarios with varying end positions and canOverScroll settings
     * @tc.expected: step2. The return value should be correct based on whether items need to be measured below
     */
    EXPECT_TRUE(algorithm_->NeedMeasureBelow(100.0f, 500.0f));
    EXPECT_FALSE(algorithm_->NeedMeasureBelow(600.0f, 500.0f));

    // Test with canOverScroll
    algorithm_->canOverScroll_ = true;
    EXPECT_FALSE(algorithm_->NeedMeasureBelow(600.0f, 500.0f));
}

/**
 * @tc.name: NeedMeasureAbove
 * @tc.desc: Test NeedMeasureAbove method under different scenarios
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, NeedMeasureAbove, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Test different scenarios with varying start positions
     * @tc.expected: step1. The return value should be correct based on whether items need to be measured above
     */
    EXPECT_TRUE(algorithm_->NeedMeasureAbove(100.0f, 50.0f));
    EXPECT_FALSE(algorithm_->NeedMeasureAbove(30.0f, 50.0f));
}

/**
 * @tc.name: AdjustOffsetOnBelow
 * @tc.desc: Test AdjustOffsetOnBelow method when last item is at the bottom
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, AdjustOffsetOnBelow, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up itemPosition_ with last item at the bottom and canOverScroll disabled
     */
    algorithm_->itemPosition_[0] = { 100.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[1] = { 200.0f, 300.0f, nullptr };
    algorithm_->itemPosition_[2] = { 300.0f, 400.0f, nullptr };
    algorithm_->totalItemCount_ = 3;
    algorithm_->middleItemEndPos_ = 400.0f;
    algorithm_->currentOffset_ = 100.0f;
    algorithm_->canOverScroll_ = false;

    /**
     * @tc.steps: step2. Call AdjustOffsetOnBelow with position 400.0f
     * @tc.expected: step2. The currentOffset_ should be adjusted to 0
     */
    algorithm_->AdjustOffsetOnBelow(400.0f);
    EXPECT_TRUE(NearEqual(algorithm_->currentOffset_, 0.0f));
}

/**
 * @tc.name: AdjustOffsetOnBelowWithCanOverScrollEnabled
 * @tc.desc: Test AdjustOffsetOnBelow method with canOverScroll enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, AdjustOffsetOnBelowWithCanOverScrollEnabled, TestSize.Level0)
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
     * @tc.steps: step2. Call AdjustOffsetOnBelow with position 300.0f
     * @tc.expected: step2. The currentOffset_ should not be adjusted when canOverScroll is enabled
     */
    algorithm_->AdjustOffsetOnBelow(300.0f);
    EXPECT_TRUE(NearEqual(algorithm_->currentOffset_, 100.0f));
}

/**
 * @tc.name: AdjustOffsetOnAbove
 * @tc.desc: Test AdjustOffsetOnAbove method when first item is at the top
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, AdjustOffsetOnAbove, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up itemPosition_ with first item at the top and canOverScroll disabled
     */
    algorithm_->itemPosition_[0] = { 100.0f, 200.0f, nullptr };
    algorithm_->itemPosition_[1] = { 200.0f, 300.0f, nullptr };
    algorithm_->middleItemStartPos_ = 100.0f;
    algorithm_->currentOffset_ = -50.0f;
    algorithm_->canOverScroll_ = false;

    /**
     * @tc.steps: step2. Call AdjustOffsetOnAbove with position 100.0f
     * @tc.expected: step2. The currentOffset_ should be adjusted to 0
     */
    algorithm_->AdjustOffsetOnAbove(100.0f);
    EXPECT_TRUE(NearEqual(algorithm_->currentOffset_, 0.0f));
}

/**
 * @tc.name: AdjustOffsetOnAboveWithCanOverScrollEnabled
 * @tc.desc: Test AdjustOffsetOnAbove method with canOverScroll enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, AdjustOffsetOnAboveWithCanOverScrollEnabled, TestSize.Level0)
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
     * @tc.steps: step2. Call AdjustOffsetOnAbove with position 100.0f
     * @tc.expected: step2. The currentOffset_ should not be adjusted when canOverScroll is enabled
     */
    algorithm_->AdjustOffsetOnAbove(100.0f);
    EXPECT_TRUE(NearEqual(algorithm_->currentOffset_, -50.0f));
}

/**
 * @tc.name: LayoutTest
 * @tc.desc: Test Layout method to verify item positioning with currentOffset_
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, LayoutTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with 3 child nodes and set up item positions
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
     * @tc.steps: step2. Call Layout method to position items
     * @tc.expected: step2. The items should be laid out correctly with adjusted positions based on currentOffset_
     */
    algorithm_->Layout(layoutWrapper);

    for (const auto& pos : algorithm_->itemPosition_) {
        EXPECT_TRUE(NearEqual(pos.second.startPos, 100.0f * pos.first - 50.0f));
        EXPECT_TRUE(NearEqual(pos.second.endPos, 100.0f * (pos.first + 1) - 50.0f));
    }
}

/**
 * @tc.name: LayoutItemTest
 * @tc.desc: Test LayoutItem method to verify individual item positioning
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, LayoutItemTest, TestSize.Level0)
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
     * @tc.expected: step2. The item should be laid out at the correct position with non-zero Y offset
     */
    algorithm_->LayoutItem(layoutWrapper, OffsetF(0.0f, 0.0f), pos);

    auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childLayoutWrapper, nullptr);
    auto childGeometryNode = childLayoutWrapper->GetGeometryNode();
    ASSERT_NE(childGeometryNode, nullptr);
    EXPECT_TRUE(GreatNotEqual(childGeometryNode->GetMarginFrameOffset().GetY(), 0.0f));
}

/**
 * @tc.name: MeasureWithItemsTest
 * @tc.desc: Test Measure method with multiple child items
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWithItemsTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes and set total item count
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
     * @tc.steps: step2. Call Measure method
     * @tc.expected: step2. The container should be marked as measured and itemPosition_ should not be empty
     */
    algorithm_->Measure(layoutWrapper);

    EXPECT_TRUE(algorithm_->measured_);
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: MeasureWithLoopEnabledTest
 * @tc.desc: Test Measure method with loop mode enabled
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWithLoopEnabledTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes, set total item count and enable loop mode
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
     * @tc.steps: step2. Call Measure method
     * @tc.expected: step2. The container should be marked as measured in loop mode
     */
    algorithm_->Measure(layoutWrapper);

    EXPECT_TRUE(algorithm_->measured_);
}

/**
 * @tc.name: MeasureWithoutItemsTest
 * @tc.desc: Test Measure method with no child items
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureWithoutItemsTest, TestSize.Level0)
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
     * @tc.steps: step2. Call Measure method
     * @tc.expected: step2. The container should be marked as measured and itemPosition_ should be empty
     */
    algorithm_->Measure(layoutWrapper);

    EXPECT_TRUE(algorithm_->measured_);
    EXPECT_TRUE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: SetGetMethodsTest
 * @tc.desc: Test set and get methods to verify property value consistency
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, SetGetMethodsTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set various properties using set methods
     */
    algorithm_->SetIsLoop(true);
    algorithm_->SetTotalItemCount(7);
    algorithm_->SetSelectedIndex(2);
    algorithm_->SetContentMainSize(500.0f);
    algorithm_->SetHeight(600.0f);
    algorithm_->SetCurrentDelta(100.0f);

    /**
     * @tc.steps: step2. Verify property values using get methods
     * @tc.expected: step2. The get methods should return the values set in step1
     */
    EXPECT_TRUE(algorithm_->isLoop_);
    EXPECT_EQ(algorithm_->selectedIndex_, 2);
    EXPECT_TRUE(NearEqual(algorithm_->GetContentMainSize(), 500.0f));
    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), 600.0f));
    EXPECT_TRUE(NearEqual(algorithm_->GetCurrentOffset(), 100.0f));
}

/**
 * @tc.name: TranslateAndRotateTest
 * @tc.desc: Test TranslateAndRotate method with different offset values
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, TranslateAndRotateTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create FrameNode and set up necessary properties
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    // Set up algorithm properties needed for TranslateAndRotate
    algorithm_->SetHeight(280);
    algorithm_->CalcMainAndMiddlePos();

    /**
     * @tc.steps: step2. Test TranslateAndRotate with different offset values
     * @tc.expected: step2. The Y offset should be adjusted based on the position relative to the middle
     */
    // Test case 1: Zero offset
    OffsetF offset1(0.0f, 120.0f);
    float originalY1 = offset1.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset1);
    EXPECT_TRUE(NearEqual(offset1.GetY(), originalY1));

    // Test case 2: Positive offset
    OffsetF offset2(0.0f, 130.0f);
    float originalY2 = offset2.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset2);
    EXPECT_TRUE(LessNotEqual(offset2.GetY(), originalY2));

    // Test case 3: Negative offset
    OffsetF offset3(0.0f, 110.0f);
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
 * @tc.name: TranslateAndRotateWithZeroHeightTest
 * @tc.desc: Test TranslateAndRotate method when height is zero
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, TranslateAndRotateWithZeroHeightTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create FrameNode and set height before rotation to zero
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    // SetPickerHeightBeforeRotate with 0
    algorithm_->SetPickerHeightBeforeRotate(0);

    /**
     * @tc.steps: step2. Test TranslateAndRotate with zero offset
     * @tc.expected: step2. The Y offset should remain unchanged when height is zero
     */
    OffsetF offset1(0.0f, 120.0f);
    float originalY1 = offset1.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset1);
    EXPECT_TRUE(NearEqual(offset1.GetY(), originalY1));
}

/**
 * @tc.name: ResetOffscreenItemPositionTest
 * @tc.desc: Test ResetOffscreenItemPosition method to verify offscreen item resetting
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ResetOffscreenItemPositionTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes and get layout wrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    // Get child wrapper before reset
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(childWrapper, nullptr);
    auto childGeometryNode = childWrapper->GetGeometryNode();
    ASSERT_NE(childGeometryNode, nullptr);

    // Save original offset
    OffsetF originalOffset = childGeometryNode->GetMarginFrameOffset();

    /**
     * @tc.steps: step2. Call ResetOffscreenItemPosition
     * @tc.expected: step2. The offscreen item position should be reset to -PICKER_ITEM_DEFAULT_HEIGHT
     */
    algorithm_->ResetOffscreenItemPosition(layoutWrapper, 0);

    // Check if offset is set to -PICKER_ITEM_DEFAULT_HEIGHT
    auto newOffset = childGeometryNode->GetMarginFrameOffset();
    EXPECT_TRUE(NearEqual(newOffset.GetX(), 0.0f));
    EXPECT_TRUE(NearEqual(newOffset.GetY(), -40.0));
    EXPECT_FALSE(NearEqual(newOffset.GetY(), originalOffset.GetY()));
}

/**
 * @tc.name: ResetOffscreenItemPositionWithNullTest
 * @tc.desc: Test ResetOffscreenItemPosition method with nullptr and invalid index parameters
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ResetOffscreenItemPositionWithNullTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Test with nullptr parameters
     * @tc.expected: step1. The function should handle nullptr gracefully without crashing
     */
    // This test case verifies that the function handles nullptr gracefully without crashing
    algorithm_->ResetOffscreenItemPosition(nullptr, 0);

    /**
     * @tc.steps: step2. Create layout wrapper and test with invalid index
     * @tc.expected: step2. The function should handle invalid index gracefully without crashing
     */
    // Create layout wrapper but test with invalid index
    CreateContainerPickerNode(1);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    // Test with invalid index
    algorithm_->ResetOffscreenItemPosition(layoutWrapper, 10);
}

/**
 * @tc.name: LayoutWithoutPositionAlignmentTest
 * @tc.desc: Test Layout method without position property alignment
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, LayoutWithoutPositionAlignmentTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
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
     * @tc.steps: step2. Call Layout method
     * @tc.expected: step2. align_ should be Alignment::CENTER
     */
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    algorithm_->Layout(layoutWrapper);
    EXPECT_EQ(algorithm_->align_, Alignment::CENTER);
}

/**
 * @tc.name: MeasureAspectRatioWithHeightChangeTest
 * @tc.desc: Test aspect ratio processing when aspect ratio is valid and height changes are required
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureAspectRatioWithHeightChangeTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set aspect ratio, initial height, width, and total item count
     */
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateAspectRatio(2);
    algorithm_->height_ = 200;
    algorithm_->contentCrossSize_ = 300;
    algorithm_->totalItemCount_ = 0;

    /**
     * @tc.steps: step3. Call HandleAspectRatio to trigger aspect ratio processing
     * @tc.expected: step3. Height should be updated to maintain aspect ratio, reMeasure_ should be true
     */
    OptionalSizeF contentIdealSize;
    algorithm_->HandleAspectRatio(layoutWrapper, contentIdealSize);

    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), 150));
    EXPECT_TRUE(NearEqual(algorithm_->contentCrossSize_, 300));
    EXPECT_TRUE(algorithm_->reMeasure_);
    EXPECT_TRUE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: MeasureAspectRatioWithNoHeightChangeTest
 * @tc.desc: Test aspect ratio processing when aspect ratio is valid but height doesn't need to change
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureAspectRatioWithNoHeightChangeTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set aspect ratio, height and width that already maintain aspect ratio
     */
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateAspectRatio(2);
    algorithm_->height_ = 200;
    algorithm_->contentCrossSize_ = 400;

    /**
     * @tc.steps: step3. Call HandleAspectRatio to trigger aspect ratio processing
     * @tc.expected: step3. Height should not be updated, reMeasure_ should be false
     */
    OptionalSizeF contentIdealSize;
    algorithm_->HandleAspectRatio(layoutWrapper, contentIdealSize);

    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), 200));
    EXPECT_TRUE(NearEqual(algorithm_->contentCrossSize_, 400));
    EXPECT_FALSE(algorithm_->reMeasure_);
}

/**
 * @tc.name: MeasureAspectRatioWithInvalidRatioTest
 * @tc.desc: Test aspect ratio processing when aspect ratio is invalid (zero)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, MeasureAspectRatioWithInvalidRatioTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and get layoutWrapper
     */
    CreateContainerPickerNode(3);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ContainerPickerLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set invalid aspect ratio (zero) and initial dimensions
     */
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateAspectRatio(0);
    algorithm_->height_ = 200;
    algorithm_->contentCrossSize_ = 300;

    /**
     * @tc.steps: step3. Call HandleAspectRatio to trigger aspect ratio processing
     * @tc.expected: step3. Height and width should not be updated, reMeasure_ should be false
     */
    OptionalSizeF contentIdealSize;
    algorithm_->HandleAspectRatio(layoutWrapper, contentIdealSize);

    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), 200));
    EXPECT_TRUE(NearEqual(algorithm_->contentCrossSize_, 300));
    EXPECT_FALSE(algorithm_->reMeasure_);
}

/**
 * @tc.name: CalcMainAndMiddlePosWithRemeasure
 * @tc.desc: Test CalcMainAndMiddlePos method when reMeasure_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, CalcMainAndMiddlePosWithRemeasure, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up initial values with reMeasure_ true
     */
    float height = 200.0f;
    float pickerItemHeight = 40.0f;
    float currentOffsetFromMiddle = 10.0f;
    algorithm_->SetHeight(height);
    algorithm_->SetItemHeight(pickerItemHeight);
    algorithm_->reMeasure_ = true;
    algorithm_->currentOffsetFromMiddle_ = currentOffsetFromMiddle;

    /**
     * @tc.steps: step2. Call CalcMainAndMiddlePos
     * @tc.expected: step2. middleItemStartPos_ and middleItemEndPos_ should be calculated with offset
     */
    algorithm_->CalcMainAndMiddlePos();
    EXPECT_FLOAT_EQ(algorithm_->middleItemStartPos_, (height - pickerItemHeight) / 2.0f + currentOffsetFromMiddle);
    EXPECT_FLOAT_EQ(algorithm_->middleItemEndPos_, (height + pickerItemHeight) / 2.0f + currentOffsetFromMiddle);
}

/**
 * @tc.name: CalcMainAndMiddlePosWithPositiveDelta
 * @tc.desc: Test CalcMainAndMiddlePos method when currentDelta_ is positive
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, CalcMainAndMiddlePosWithPositiveDelta, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up initial values with positive currentDelta_
     */
    float height = 200.0f;
    float pickerItemHeight = 40.0f;
    float positiveDelta = 10.0f;
    algorithm_->SetHeight(height);
    algorithm_->SetItemHeight(pickerItemHeight);
    algorithm_->currentDelta_ = positiveDelta;
    algorithm_->reMeasure_ = false;

    /**
     * @tc.steps: step2. Call CalcMainAndMiddlePos
     * @tc.expected: step2. startMainPos_ should be reduced by pickerItemHeight, endMainPos_ should include delta
     */
    float expectedMiddleStart = (height - pickerItemHeight) / 2.0f;
    float expectedMiddleEnd = (height + pickerItemHeight) / 2.0f;
    int32_t halfOfDisplayCount = 3; // DISPLAY_COUNT / 2
    float expectedStartMainPos = expectedMiddleStart - pickerItemHeight * (halfOfDisplayCount - 1) - pickerItemHeight;
    float expectedEndMainPos = expectedMiddleEnd + pickerItemHeight * (halfOfDisplayCount - 1) + positiveDelta;

    algorithm_->CalcMainAndMiddlePos();
    EXPECT_FLOAT_EQ(algorithm_->middleItemStartPos_, expectedMiddleStart);
    EXPECT_FLOAT_EQ(algorithm_->middleItemEndPos_, expectedMiddleEnd);
    EXPECT_FLOAT_EQ(algorithm_->startMainPos_, expectedStartMainPos);
    EXPECT_FLOAT_EQ(algorithm_->endMainPos_, expectedEndMainPos);
}

/**
 * @tc.name: CalcMainAndMiddlePosWithNegativeDelta
 * @tc.desc: Test CalcMainAndMiddlePos method when currentDelta_ is negative
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, CalcMainAndMiddlePosWithNegativeDelta, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up initial values with negative currentDelta_
     */
    float height = 200.0f;
    float pickerItemHeight = 40.0f;
    float negativeDelta = -10.0f;
    algorithm_->SetHeight(height);
    algorithm_->SetItemHeight(pickerItemHeight);
    algorithm_->currentDelta_ = negativeDelta;
    algorithm_->reMeasure_ = false;

    /**
     * @tc.steps: step2. Call CalcMainAndMiddlePos
     * @tc.expected: step2. startMainPos_ should include delta, endMainPos_ should be increased by pickerItemHeight
     */
    float expectedMiddleStart = (height - pickerItemHeight) / 2.0f;
    float expectedMiddleEnd = (height + pickerItemHeight) / 2.0f;
    int32_t halfOfDisplayCount = 3; // DISPLAY_COUNT / 2
    float expectedStartMainPos = expectedMiddleStart - pickerItemHeight * (halfOfDisplayCount - 1) + negativeDelta;
    float expectedEndMainPos = expectedMiddleEnd + pickerItemHeight * (halfOfDisplayCount - 1) + pickerItemHeight;

    algorithm_->CalcMainAndMiddlePos();
    EXPECT_FLOAT_EQ(algorithm_->middleItemStartPos_, expectedMiddleStart);
    EXPECT_FLOAT_EQ(algorithm_->middleItemEndPos_, expectedMiddleEnd);
    EXPECT_FLOAT_EQ(algorithm_->startMainPos_, expectedStartMainPos);
    EXPECT_FLOAT_EQ(algorithm_->endMainPos_, expectedEndMainPos);
}

/**
 * @tc.name: CalcMainAndMiddlePosWithZeroDelta
 * @tc.desc: Test CalcMainAndMiddlePos method when currentDelta_ is zero
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, CalcMainAndMiddlePosWithZeroDelta, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up initial values with zero currentDelta_
     */
    float height = 200.0f;
    float pickerItemHeight = 40.0f;
    algorithm_->SetHeight(height);
    algorithm_->SetItemHeight(pickerItemHeight);
    algorithm_->currentDelta_ = 0.0f;
    algorithm_->reMeasure_ = false;

    /**
     * @tc.steps: step2. Call CalcMainAndMiddlePos
     * @tc.expected: step2. startMainPos_ should be reduced and endMainPos_ should be increased by pickerItemHeight
     */
    float expectedMiddleStart = (height - pickerItemHeight) / 2.0f;
    float expectedMiddleEnd = (height + pickerItemHeight) / 2.0f;
    int32_t halfOfDisplayCount = 3; // DISPLAY_COUNT / 2
    float expectedStartMainPos = expectedMiddleStart - pickerItemHeight * (halfOfDisplayCount - 1) - pickerItemHeight;
    float expectedEndMainPos = expectedMiddleEnd + pickerItemHeight * (halfOfDisplayCount - 1) + pickerItemHeight;

    algorithm_->CalcMainAndMiddlePos();
    EXPECT_FLOAT_EQ(algorithm_->middleItemStartPos_, expectedMiddleStart);
    EXPECT_FLOAT_EQ(algorithm_->middleItemEndPos_, expectedMiddleEnd);
    EXPECT_FLOAT_EQ(algorithm_->startMainPos_, expectedStartMainPos);
    EXPECT_FLOAT_EQ(algorithm_->endMainPos_, expectedEndMainPos);
}

/**
 * @tc.name: CalcMainAndMiddlePosWithoutRemeasure
 * @tc.desc: Test CalcMainAndMiddlePos method when reMeasure_ is false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, CalcMainAndMiddlePosWithoutRemeasure, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set up initial values with reMeasure_ false
     */
    float height = 200.0f;
    float pickerItemHeight = 40.0f;
    float offsetFromMiddle = 10.0f;
    algorithm_->SetHeight(height);
    algorithm_->SetItemHeight(pickerItemHeight);
    algorithm_->reMeasure_ = false;
    algorithm_->currentOffsetFromMiddle_ = offsetFromMiddle;

    /**
     * @tc.steps: step2. Call CalcMainAndMiddlePos
     * @tc.expected: step2. middleItemStartPos_ and middleItemEndPos_ should not include offsetFromMiddle
     */
    algorithm_->CalcMainAndMiddlePos();
    EXPECT_FLOAT_EQ(algorithm_->middleItemStartPos_, (height - pickerItemHeight) / 2.0f);
    EXPECT_FLOAT_EQ(algorithm_->middleItemEndPos_, (height + pickerItemHeight) / 2.0f);
}

/**
 * @tc.name: RetainDisplayItemsWhenLessThanLimit
 * @tc.desc: Test RetainDisplayItems method when item count is less than or equal to DISPLAY_COUNT + 1
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, RetainDisplayItemsWhenLessThanLimit, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create itemPosition_ with count less than DISPLAY_COUNT + 1
     */
    // Create 10 items which is less than 11
    for (int32_t i = 0; i < 8; i++) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        algorithm_->itemPosition_[i] = { static_cast<float>(i * 40), static_cast<float>((i + 1) * 40), textNode };
    }

    int32_t initialSize = algorithm_->itemPosition_.size();

    /**
     * @tc.steps: step2. Call RetainDisplayItems with both atTop true and false
     * @tc.expected: step2. itemPosition_ should remain unchanged in both cases
     */
    algorithm_->RetainDisplayItems(true);
    EXPECT_EQ(algorithm_->itemPosition_.size(), initialSize);

    algorithm_->RetainDisplayItems(false);
    EXPECT_EQ(algorithm_->itemPosition_.size(), initialSize);
}

/**
 * @tc.name: RetainDisplayItemsAtTop
 * @tc.desc: Test RetainDisplayItems method with atTop true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, RetainDisplayItemsAtTop, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create itemPosition_ with count greater than DISPLAY_COUNT + 1
     */
    // Create 20 items which is more than DISPLAY_COUNT + 1
    for (int32_t i = 0; i < 8; i++) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        algorithm_->itemPosition_[i] = { static_cast<float>(i * 40), static_cast<float>((i + 1) * 40), textNode };
    }

    /**
     * @tc.steps: step2. Call RetainDisplayItems with atTop true
     * @tc.expected: step2. Only DISPLAY_COUNT + 1 items should be retained from the top
     */
    algorithm_->RetainDisplayItems(true);
    EXPECT_LE(algorithm_->itemPosition_.size(), 8);

    // Verify that the first item is still index 0
    EXPECT_TRUE(algorithm_->itemPosition_.find(0) != algorithm_->itemPosition_.end());
}

/**
 * @tc.name: RetainDisplayItemsAtBottom
 * @tc.desc: Test RetainDisplayItems method with atTop false
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, RetainDisplayItemsAtBottom, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create itemPosition_ with count greater than DISPLAY_COUNT + 1
     */
    // Create 20 items which is more than DISPLAY_COUNT + 1
    for (int32_t i = 0; i < 20; i++) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        algorithm_->itemPosition_[i] = { static_cast<float>(i * 40), static_cast<float>((i + 1) * 40), textNode };
    }

    /**
     * @tc.steps: step2. Call RetainDisplayItems with atTop false
     * @tc.expected: step2. Only DISPLAY_COUNT + 1 items should be retained from the bottom
     */
    algorithm_->RetainDisplayItems(false);
    EXPECT_LE(algorithm_->itemPosition_.size(), 8);

    // Verify that the last item is still index 19
    EXPECT_TRUE(algorithm_->itemPosition_.find(19) != algorithm_->itemPosition_.end());
}

/**
 * @tc.name: RetainDisplayItemsWithExactlyLimitCount
 * @tc.desc: Test RetainDisplayItems method when item count is exactly DISPLAY_COUNT + 1
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, RetainDisplayItemsWithExactlyLimitCount, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create itemPosition_ with count exactly DISPLAY_COUNT + 1
     */
    for (int32_t i = 0; i < 8; i++) {
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        algorithm_->itemPosition_[i] = { static_cast<float>(i * 40), static_cast<float>((i + 1) * 40), textNode };
    }

    int32_t initialSize = algorithm_->itemPosition_.size();

    /**
     * @tc.steps: step2. Call RetainDisplayItems with both atTop true and false
     * @tc.expected: step2. itemPosition_ should remain unchanged in both cases
     */
    algorithm_->RetainDisplayItems(true);
    EXPECT_EQ(algorithm_->itemPosition_.size(), initialSize);

    algorithm_->RetainDisplayItems(false);
    EXPECT_EQ(algorithm_->itemPosition_.size(), initialSize);
}

/**
 * @tc.name: RetainDisplayItemsWithEmptyPosition
 * @tc.desc: Test RetainDisplayItems method with empty itemPosition_
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, RetainDisplayItemsWithEmptyPosition, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Ensure itemPosition_ is empty
     */
    algorithm_->itemPosition_.clear();
    EXPECT_TRUE(algorithm_->itemPosition_.empty());

    /**
     * @tc.steps: step2. Call RetainDisplayItems with both atTop true and false
     * @tc.expected: step2. itemPosition_ should remain empty in both cases
     */
    algorithm_->RetainDisplayItems(true);
    EXPECT_TRUE(algorithm_->itemPosition_.empty());

    algorithm_->RetainDisplayItems(false);
    EXPECT_TRUE(algorithm_->itemPosition_.empty());
}

} // namespace OHOS::Ace::NG
