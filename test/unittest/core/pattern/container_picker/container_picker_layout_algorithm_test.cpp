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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest001
 * @tc.desc: Test MeasureHeight method with default height
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest002
 * @tc.desc: Test MeasureHeight method with heightMatch policy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set heightMatch policy
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest003
 * @tc.desc: Test MeasureHeight method with negative height
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker and set up layoutWrapper
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
     * @tc.steps: step2. Call MeasureHeight with negative height
     * @tc.expected: step2. The height should be set to default value
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Height().has_value());
    EXPECT_EQ(algorithm_->GetHeight(), 200);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest004
 * @tc.desc: Test MeasureHeight method with height changed
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest004, TestSize.Level0)
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
    layoutProperty->contentConstraint_ = layoutConstraintF;

    // Set initial height
    float initialHeight = 300.0f;
    algorithm_->SetHeight(initialHeight);

    // Add some items to itemPosition_
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, childNode };

    EXPECT_FALSE(algorithm_->itemPosition_.empty());

    /**
     * @tc.steps: step2. Change height and call MeasureHeight
     * @tc.expected: step2. itemPosition_ should be cleared when height changes
     */
    OptionalSizeF contentIdealSize;
    LayoutConstraintF constraintWithDifferentHeight = layoutConstraintF;
    constraintWithDifferentHeight.selfIdealSize = { 200, 500 };
    layoutProperty->contentConstraint_ = constraintWithDifferentHeight;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_FALSE(NearEqual(algorithm_->GetHeight(), initialHeight));
    EXPECT_TRUE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest005
 * @tc.desc: Test MeasureHeight method with height unchanged
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest005, TestSize.Level0)
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
     * @tc.expected: step2. itemPosition_ should not be cleared
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), sameHeight));
    EXPECT_FALSE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest006
 * @tc.desc: Test MeasureHeight method without layoutPolicy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest006, TestSize.Level0)
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest007
 * @tc.desc: Test MeasureHeight method with custom selfIdealSize
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest007, TestSize.Level0)
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest008
 * @tc.desc: Test MeasureHeight method with layoutPolicy MATCH_PARENT
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest008, TestSize.Level0)
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
     * @tc.steps: step2. Set layoutPolicy MATCH_PARENT
     * @tc.expected: step2. The height should be set to parent height
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_EQ(contentIdealSize.Height().value(), 910);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest009
 * @tc.desc: Test MeasureHeight method with layoutPolicy WRAP_CONTENT or FIX_AT_IDEAL_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest009, TestSize.Level0)
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
     * @tc.steps: step2. Set layoutPolicy WRAP_CONTENT
     * @tc.expected: step2. The height should be set to default height
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_EQ(contentIdealSize.Height().value(), 200);

    /**
     * @tc.steps: step3. Set layoutPolicy FIX_AT_IDEAL_SIZE
     * @tc.expected: step3. The height should be set to default height
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    OptionalSizeF contentIdealSize2;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize2);
    EXPECT_EQ(contentIdealSize2.Height().value(), 200);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureHeightTest010
 * @tc.desc: Test MeasureHeight method with layoutPolicy NO_MATCH
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureHeightTest010, TestSize.Level0)
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
     * @tc.steps: step2. Set layoutPolicy NO_MATCH
     * @tc.expected: step2. The height should be set to default height
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureHeight(layoutWrapper, contentIdealSize);
    EXPECT_EQ(contentIdealSize.Height().value(), 200);
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
    EXPECT_EQ(contentIdealSize.Width().value(), 200);
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
     * @tc.expected: step2. The width should be calculated correctly
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 150);
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
     * @tc.expected: step2. The width should be set to ideal size
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 150);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureWidthTest004
 * @tc.desc: Test MeasureWidth method with different content constraints
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureWidthTest004, TestSize.Level0)
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
     * @tc.steps: step2. Test MeasureWidth with undefined cross size
     * @tc.expected: step2. The width should be calculated correctly
     */
    OptionalSizeF contentIdealSize;

    // Set item positions to simulate measured items
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(0));
    algorithm_->itemPosition_[0] = { 100.0f, 150.0f, childNode };

    SetChildNodeFrameSize(layoutWrapper, 0, 150, 40);

    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 150);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureWidthTest005
 * @tc.desc: Test MeasureWidth method when self cross size is greater then parent cross size
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureWidthTest005, TestSize.Level0)
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
     * @tc.expected: step2. The width should be set to default width
     */
    layoutConstraintF.selfIdealSize = { 500, 910 };
    layoutProperty->contentConstraint_ = layoutConstraintF;
    OptionalSizeF contentIdealSize;

    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(contentIdealSize.Width().value(), 500);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureWidthTest006
 * @tc.desc: Test MeasureWidth method with WRAP_CONTENT and parent cross size
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureWidthTest006, TestSize.Level0)
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
     * @tc.steps: step2. Test WRAP_CONTENT with parent cross size constraint
     * @tc.expected: step2. The width should be constrained by parent cross size
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureWidthTest007
 * @tc.desc: Test MeasureWidth method with FIX_AT_IDEAL_SIZE and parent cross size
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureWidthTest007, TestSize.Level0)
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
     * @tc.steps: step2. Test FIX_AT_IDEAL_SIZE with parent cross size constraint
     * @tc.expected: step2. The width should be constrained by parent cross size
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureWidthTest008
 * @tc.desc: Test MeasureWidth method with negative cross size with MATCH_PARENT policy
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureWidthTest008, TestSize.Level0)
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
     * @tc.steps: step2. Set negative cross size
     * @tc.expected: step2. The width should be set to parent width
     */
    OptionalSizeF contentIdealSize;
    algorithm_->MeasureWidth(layoutWrapper, contentIdealSize);
    EXPECT_TRUE(contentIdealSize.Width().has_value());
    EXPECT_EQ(algorithm_->GetContentCrossSize(), 200);
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

    EXPECT_EQ(algorithm_->startMainPos_, 110);
    EXPECT_EQ(algorithm_->endMainPos_, 390);
    EXPECT_EQ(algorithm_->middleItemStartPos_, 230);
    EXPECT_EQ(algorithm_->middleItemEndPos_, 270);
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
     * @tc.expected: step1. The positions should be calculated correctly with large height
     */
    algorithm_->SetHeight(1200.0f);
    algorithm_->CalcMainAndMiddlePos();

    EXPECT_EQ(algorithm_->startMainPos_, 460);
    EXPECT_EQ(algorithm_->endMainPos_, 740);
    EXPECT_EQ(algorithm_->middleItemStartPos_, 580.0f);
    EXPECT_EQ(algorithm_->middleItemEndPos_, 620.0f);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_CalcMainAndMiddlePosTest003
 * @tc.desc: Test CalcMainAndMiddlePos method of ContainerPickerLayoutAlgorithm with positive delta
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_CalcMainAndMiddlePosTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set large height and call CalcMainAndMiddlePos
     * @tc.expected: step1. The positions should be calculated correctly with delta
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->SetCurrentDelta(50.0f);
    algorithm_->CalcMainAndMiddlePos();

    EXPECT_EQ(algorithm_->startMainPos_, 110);
    EXPECT_EQ(algorithm_->endMainPos_, 440);
    EXPECT_EQ(algorithm_->middleItemStartPos_, 230);
    EXPECT_EQ(algorithm_->middleItemEndPos_, 270);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_CalcMainAndMiddlePosTest004
 * @tc.desc: Test CalcMainAndMiddlePos method of ContainerPickerLayoutAlgorithm with negative delta
 * @tc.type: FUNC
 */
HWTEST_F(
    ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_CalcMainAndMiddlePosTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Set large height and call CalcMainAndMiddlePos
     * @tc.expected: step1. The positions should be calculated correctly with delta
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->SetCurrentDelta(-50.0f);
    algorithm_->CalcMainAndMiddlePos();

    EXPECT_EQ(algorithm_->startMainPos_, 60);
    EXPECT_EQ(algorithm_->endMainPos_, 390);
    EXPECT_EQ(algorithm_->middleItemStartPos_, 230);
    EXPECT_EQ(algorithm_->middleItemEndPos_, 270);
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
 * @tc.desc: Test MeasureBelow method with canOverScroll enabled
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
     * @tc.steps: step2. Set up algorithm with canOverScroll and call MeasureBelow
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;
    algorithm_->canOverScroll_ = true;

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
 * @tc.desc: Test MeasureAbove method with canOverScroll enabled
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
     * @tc.steps: step2. Set up algorithm with canOverScroll and call MeasureAbove
     */
    algorithm_->SetHeight(500.0f);
    algorithm_->CalcMainAndMiddlePos();
    algorithm_->totalItemCount_ = 5;
    algorithm_->canOverScroll_ = true;

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

    // Test with canOverScroll
    algorithm_->canOverScroll_ = true;
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
    algorithm_->SetTotalItemCount(7);
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
    algorithm_->SetHeight(280);
    algorithm_->CalcMainAndMiddlePos();

    /**
     * @tc.steps: step2. Test TranslateAndRotate with different offset values
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
 * @tc.name: ContainerPickerLayoutAlgorithmTranslateAndRotateTest002
 * @tc.desc: Test TranslateAndRotate method of ContainerPickerLayoutAlgorithm when height is 0
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithmTranslateAndRotateTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create FrameNode and set up necessary properties
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    // SetPickerHeightBeforeRotate with 0
    algorithm_->SetPickerHeightBeforeRotate(0);

    /**
     * @tc.steps: step2. Test TranslateAndRotate with zero offset
     */
    OffsetF offset1(0.0f, 120.0f);
    float originalY1 = offset1.GetY();
    algorithm_->TranslateAndRotate(frameNode, offset1);
    EXPECT_TRUE(NearEqual(offset1.GetY(), originalY1));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_ResetOffscreenItemPositionTest001
 * @tc.desc: Test ResetOffscreenItemPosition method of ContainerPickerLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_ResetOffscreenItemPositionTest001,
    TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create ContainerPicker with child nodes
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
     * @tc.expected: step2. The offscreen item position should be reset correctly
     */
    algorithm_->ResetOffscreenItemPosition(layoutWrapper, 0);

    // Check if offset is set to -PICKER_ITEM_DEFAULT_HEIGHT
    auto newOffset = childGeometryNode->GetMarginFrameOffset();
    EXPECT_TRUE(NearEqual(newOffset.GetX(), 0.0f));
    EXPECT_TRUE(NearEqual(newOffset.GetY(), -40.0));
    EXPECT_FALSE(NearEqual(newOffset.GetY(), originalOffset.GetY()));
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_ResetOffscreenItemPositionTest002
 * @tc.desc: Test ResetOffscreenItemPosition method with nullptr check
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_ResetOffscreenItemPositionTest002,
    TestSize.Level0)
{
    /**
     * @tc.steps: step1. Test with nullptr parameters (should not crash)
     * @tc.expected: step1. The function should handle nullptr gracefully
     */
    // This test case verifies that the function handles nullptr gracefully without crashing
    algorithm_->ResetOffscreenItemPosition(nullptr, 0);

    // Create layout wrapper but test with invalid index
    CreateContainerPickerNode(1);
    auto refLayoutWrapper = frameNode_->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);

    // Test with invalid index
    algorithm_->ResetOffscreenItemPosition(layoutWrapper, 10);
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_LayoutTest002
 * @tc.desc: Test Layout method without position property alignment
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_LayoutTest002, TestSize.Level1)
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureAspectRatioTest001
 * @tc.desc: Test aspect ratio processing when aspect ratio is valid and height changes
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureAspectRatioTest001, TestSize.Level0)
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
     * @tc.steps: step2. Set aspectRatio/height/width
     */
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateAspectRatio(2);
    algorithm_->height_ = 200;
    algorithm_->contentCrossSize_ = 300;
    algorithm_->totalItemCount_ = 0;

    /**
     * @tc.steps: step3. Call HandleAspectRatio to trigger aspect ratio processing
     * @tc.expected: step3. Height should be updated, reMeasure_ should be true
     */
    OptionalSizeF contentIdealSize;
    algorithm_->HandleAspectRatio(layoutWrapper, contentIdealSize);

    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), 150));
    EXPECT_TRUE(NearEqual(algorithm_->contentCrossSize_, 300));
    EXPECT_TRUE(algorithm_->reMeasure_);
    EXPECT_TRUE(algorithm_->itemPosition_.empty());
}

/**
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureAspectRatioTest002
 * @tc.desc: Test aspect ratio processing when aspect ratio is valid but height doesn't change
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureAspectRatioTest002, TestSize.Level0)
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
     * @tc.steps: step2. Set aspectRatio/height/width
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
 * @tc.name: ContainerPickerLayoutAlgorithm_MeasureAspectRatioTest003
 * @tc.desc: Test aspect ratio processing when aspect ratio is invalid (zero)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerPickerLayoutAlgorithmTest, ContainerPickerLayoutAlgorithm_MeasureAspectRatioTest003, TestSize.Level0)
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
     * @tc.steps: step2. Set aspectRatio/height/width
     */
    layoutProperty->contentConstraint_ = layoutConstraintF;
    layoutProperty->UpdateAspectRatio(0);
    algorithm_->height_ = 200;
    algorithm_->contentCrossSize_ = 300;

    /**
     * @tc.steps: step3. Call HandleAspectRatio to trigger aspect ratio processing
     * @tc.expected: step3. Height should not be updated, reMeasure_ should be false
     */
    OptionalSizeF contentIdealSize;
    algorithm_->HandleAspectRatio(layoutWrapper, contentIdealSize);

    EXPECT_TRUE(NearEqual(algorithm_->GetHeight(), 200));
    EXPECT_TRUE(NearEqual(algorithm_->contentCrossSize_, 300));
    EXPECT_FALSE(algorithm_->reMeasure_);
}

} // namespace OHOS::Ace::NG
