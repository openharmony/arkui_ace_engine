/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class NavigationLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<NavigationGroupNode> CreateNavigationNode();
    RefPtr<FrameNode> CreateChildNode(const std::string& tag);
};

void NavigationLayoutAlgorithmTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationLayoutAlgorithmTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationLayoutAlgorithmTest::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(12);
}

void NavigationLayoutAlgorithmTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<NavigationGroupNode> NavigationLayoutAlgorithmTest::CreateNavigationNode()
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    if (!navigationPattern) {
        return nullptr;
    }
    navigationPattern->SetNavigationStack(AceType::MakeRefPtr<MockNavigationStack>());
    navigationNode->contentNode_ = CreateChildNode("content");
    return navigationNode;
}

RefPtr<FrameNode> NavigationLayoutAlgorithmTest::CreateChildNode(const std::string& tag)
{
    auto childNode = FrameNode::CreateFrameNode(
        tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    return childNode;
}

/**
 * @tc.name: IsAutoHeightWithNullLayoutProperty
 * @tc.desc: Test IsAutoHeight method with null layout property
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, IsAutoHeightWithNullLayoutProperty, TestSize.Level1)
{
    RefPtr<LayoutProperty> layoutProperty = nullptr;
    auto result = NavigationLayoutAlgorithm::IsAutoHeight(layoutProperty);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsAutoHeightWithNullCalcLayoutConstraint
 * @tc.desc: Test IsAutoHeight method with null calc layout constraint
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, IsAutoHeightWithNullCalcLayoutConstraint, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    auto result = NavigationLayoutAlgorithm::IsAutoHeight(layoutProperty);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsAutoHeightWithNullSelfIdealSize
 * @tc.desc: Test IsAutoHeight method with null self ideal size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, IsAutoHeightWithNullSelfIdealSize, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto result = NavigationLayoutAlgorithm::IsAutoHeight(layoutProperty);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsAutoHeightWithNullHeightValue
 * @tc.desc: Test IsAutoHeight method with null height value
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, IsAutoHeightWithNullHeightValue, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(100.0f), std::nullopt);
    auto result = NavigationLayoutAlgorithm::IsAutoHeight(layoutProperty);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsAutoHeightWithFixedHeight
 * @tc.desc: Test IsAutoHeight method with fixed height value
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, IsAutoHeightWithFixedHeight, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(100.0f), CalcLength(200.0f));
    auto result = NavigationLayoutAlgorithm::IsAutoHeight(layoutProperty);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsAutoHeightWithAutoHeight
 * @tc.desc: Test IsAutoHeight method with auto height value
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, IsAutoHeightWithAutoHeight, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(100.0f), CalcLength("auto"));
    auto result = NavigationLayoutAlgorithm::IsAutoHeight(layoutProperty);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckSizeInSplitWithVeryLargeFrame001
 * @tc.desc: Test CheckSizeInSplit with very large frame width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithVeryLargeFrame001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    float testWidth = 300.0f;
    algorithm->SetRealNavBarWidth(testWidth);
    EXPECT_EQ(algorithm->GetRealNavBarWidth(), testWidth);
}

/**
 * @tc.name: SetIfNeedInit
 * @tc.desc: Test SetIfNeedInit method
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SetIfNeedInit, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->SetIfNeedInit(true);
    EXPECT_TRUE(algorithm->ifNeedInit_);
    algorithm->SetIfNeedInit(false);
    EXPECT_FALSE(algorithm->ifNeedInit_);
}

/**
 * @tc.name: RangeCalculationWithValidParams
 * @tc.desc: Test RangeCalculation with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, RangeCalculationWithValidParams, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    algorithm->RangeCalculation(hostNode, layoutProperty);
    EXPECT_GT(algorithm->minNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->maxNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->minContentWidthValue_.value_, 0.0f);
}

/**
 * @tc.name: GetRangeWithValidParams
 * @tc.desc: Test GetRange with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, GetRangeWithValidParams, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    if (pattern) {
        pattern->SetMinNavBarWidthValue(Dimension(200.0_vp));
        pattern->SetMaxNavBarWidthValue(Dimension(400.0_vp));
        pattern->SetMinContentWidthValue(Dimension(300.0_vp));
        pattern->SetUserSetNavBarRangeFlag(true);
        pattern->SetUserSetMinContentFlag(true);
        pattern->SetUserSetNavBarWidthFlag(true);
    }
    algorithm->GetRange(hostNode);
    EXPECT_TRUE(algorithm->userSetNavBarRangeFlag_);
    EXPECT_TRUE(algorithm->userSetMinContentFlag_);
    EXPECT_TRUE(algorithm->userSetNavBarWidthFlag_);
}

/**
 * @tc.name: CalculateNavigationWidthWithNullContext
 * @tc.desc: Test CalculateNavigationWidth with null context
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CalculateNavigationWidthWithNullContext, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    if (pipeline) {
        pipeline->SetMinPlatformVersion(9);
    }
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto width = algorithm->CalculateNavigationWidth(hostNode);
    EXPECT_GT(width, 0.0f);
}

/**
 * @tc.name: CalculateNavigationWidthWithValidParams
 * @tc.desc: Test CalculateNavigationWidth with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CalculateNavigationWidthWithValidParams, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(1000.0f, 1000.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        algorithm->minNavBarWidthValue_ = Dimension(200.0_vp);
        algorithm->minContentWidthValue_ = Dimension(300.0_vp);
    }
    auto width = algorithm->CalculateNavigationWidth(hostNode);
    EXPECT_GT(width, 0.0f);
}

/**
 * @tc.name: SizeCalculationForForceSplitWithValidParams
 * @tc.desc: Test SizeCalculationForForceSplit with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationForForceSplitWithValidParams, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF frameSize(1000.0f, 1000.0f);
    algorithm->SizeCalculationForForceSplit(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_GT(algorithm->realDividerWidth_, 0.0f);
}

/**
 * @tc.name: SizeCalculationWithValidParamsSplitMode
 * @tc.desc: Test SizeCalculation with SPLIT mode and valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationWithValidParamsSplitMode, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    hostNode->contentNode_ = CreateChildNode("content");
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(1000.0f, 1000.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
        algorithm->minNavBarWidthValue_ = Dimension(200.0_vp);
        algorithm->maxNavBarWidthValue_ = Dimension(400.0_vp);
        algorithm->minContentWidthValue_ = Dimension(300.0_vp);
    }
    SizeF frameSize(1000.0f, 1000.0f);
    algorithm->SizeCalculation(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: SizeCalculationWithValidParamsStackMode
 * @tc.desc: Test SizeCalculation with STACK mode and valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationWithValidParamsStackMode, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    hostNode->contentNode_ = CreateChildNode("content");
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(1000.0f, 1000.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    }
    SizeF frameSize(1000.0f, 1000.0f);
    algorithm->SizeCalculation(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_EQ(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithUserSetMinContentFlag
 * @tc.desc: Test CheckSizeInSplit with userSetMinContentFlag true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithUserSetMinContentFlag, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 300.0f;
    float frameWidth = 1000.0f;
    float userSetNavBarWidth = 300.0f;
    float minNavBarWidth = 200.0f;
    float minContentWidth = 300.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithUserSetNavBarWidthFlag
 * @tc.desc: Test CheckSizeInSplit with userSetNavBarNavBarWidthFlag true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithUserSetNavBarWidthFlag, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->userSetMinContentFlag_ = false;
    algorithm->userSetNavBarWidthFlag_ = true;
    algorithm->realNavBarWidth_ = 300.0f;
    float frameWidth = 1000.0f;
    float userSetNavBarWidth = 300.0f;
    float minNavBarWidth = 200.0f;
    float minContentWidth = 300.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithDefaultFlags
 * @tc.desc: Test CheckSizeInSplit with default flags
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithDefaultFlags, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->userSetMinContentFlag_ = false;
    algorithm->userSetNavBarWidthFlag_ = false;
    algorithm->realNavBarWidth_ = 300.0f;
    float frameWidth = 1000.0f;
    float userSetNavBarWidth = 300.0f;
    float minNavBarWidth = 200.0f;
    float minContentWidth = 300.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithMinContentExceedsFrameWidth
 * @tc.desc: Test CheckSizeInSplit when minContentWidth exceeds frameWidth
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithMinContentExceedsFrameWidth, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 300.0f;
    float frameWidth = 500.0f;
    float userSetNavBarWidth = 300.0f;
    float minNavBarWidth = 200.0f;
    float minContentWidth = 600.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_EQ(algorithm->realContentWidth_, frameWidth);
}

/**
 * @tc.name: SizeCalculationStackWithValidatedParams
 * @tc.desc: Test SizeCalculationStack with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationStackWithValidatedParams, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SizeF frameSize(1000.0f, 1000.0f);
    algorithm->SizeCalculationStack(hostNode, layoutProperty, frameSize);
    EXPECT_EQ(algorithm->realDividerWidth_, 0.0f);
    EXPECT_EQ(algorithm->realContentWidth_, frameSize.Width());
}

/**
 * @tc.name: SizeCalculationWithSmallFrameSize
 * @tc.desc: Test SizeCalculation with small frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationWithSmallFrameSize, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.selfIdealSize = OptionalSizeF(400.0f, 400.0f);
        constraint.maxSize = SizeF(400.0f, 400.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
        algorithm->minNavBarWidthValue_ = Dimension(100.0_vp);
        algorithm->maxNavBarWidthValue_ = Dimension(200.0_vp);
        algorithm->minContentWidthValue_ = Dimension(150.0_vp);
    }
    SizeF frameSize(400.0f, 400.0f);
    algorithm->SizeCalculation(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_LT(algorithm->realNavBarWidth_, frameSize.Width());
}

/**
 * @tc.name: CheckSizeInSplitWithLargeFrameWidth
 * @tc.desc: Test CheckSizeInSplit with large frame width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithLargeFrameWidth, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 500.0f;
    float frameWidth = 2000.0f;
    float userSetNavBarWidth = 500.0f;
    float minNavBarWidth = 300.0f;
    float minContentWidth = 400.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_LT(algorithm->realContentWidth_, frameWidth);
}

/**
 * @tc.name: CheckSizeInSplitWithSmallFrameWidth
 * @tc.desc: Test CheckSizeInSplit with small frame width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithSmallFrameWidth, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 150.0f;
    float frameWidth = 400.0f;
    float userSetNavBarWidth = 150.0f;
    float minNavBarWidth = 100.0f;
    float minContentWidth = 150.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_LT(algorithm->realContentWidth_, frameWidth);
}

/**
 * @tc.name: CheckSizeInSplitWithExactFrameWidth
 * @tc.desc: Test CheckSizeInSplit when frame width equals total width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithExactFrameWidth, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 300.0f;
    float frameWidth = 600.0f;
    float userSetNavBarWidth = 300.0f;
    float minNavBarWidth = 200.0f;
    float minContentWidth = 300.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_EQ(algorithm->realNavBarWidth_ + algorithm->realContentWidth_ + 1.0f, frameWidth);
}

/**
 * @tc.name: RangeCalculationWithDifferentFrameSizes
 * @tc.desc: Test RangeCalculation with different frame sizes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, RangeCalculationWithDifferentFrameSizes, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();

    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(800.0f, 600.0f);
    constraint.maxSize = SizeF(800.0f, 600.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    algorithm->RangeCalculation(hostNode, layoutProperty);

    EXPECT_GT(algorithm->minNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->maxNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->minContentWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->maxNavBarWidthValue_.value_, algorithm->minNavBarWidthValue_.value_);
}

/**
 * @tc.name: CalculateNavigationWidthWithSmallConstraints
 * @tc.desc: Test CalculateNavigationWidth with small constraints
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CalculateNavigationWidthWithSmallConstraints, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(400.0f, 400.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        algorithm->minNavBarWidthValue_ = Dimension(100.0_vp);
        algorithm->minContentWidthValue_ = Dimension(150.0_vp);
    }
    auto width = algorithm->CalculateNavigationWidth(hostNode);
    EXPECT_GT(width, 0.0f);
    EXPECT_LT(width, 400.0f);
}

/**
 * @tc.name: CalculateNavigationWidthWithLargeConstraints
 * @tc.desc: Test CalculateNavigationWidth with large constraints
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CalculateNavigationWidthWithLargeConstraints, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(1920.0f, 1080.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        algorithm->minNavBarWidthValue_ = Dimension(200.0_vp);
        algorithm->minContentWidthValue_ = Dimension(300.0_vp);
    }
    auto width = algorithm->CalculateNavigationWidth(hostNode);
    EXPECT_GT(width, 0.0f);
    EXPECT_GT(width, 200.0f);
}

/**
 * @tc.name: SizeCalculationForForceSplitWithDifferentSizes
 * @tc.desc: Test SizeCalculationForForceSplit with different frame sizes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationForForceSplitWithDifferentSizes, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF frameSize(800.0f, 600.0f);
    algorithm->SizeCalculationForForceSplit(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_GT(algorithm->realDividerWidth_, 0.0f);
}

/**
 * @tc.name: SizeCalculationStackWithLargeFrameSize
 * @tc.desc: Test SizeCalculationStack with large frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationStackWithLargeFrameSize, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SizeF frameSize(1920.0f, 1080.0f);
    algorithm->SizeCalculationStack(hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: SizeCalculationStackWithSmallFrameSize
 * @tc.desc: Test SizeCalculationStack with small frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationStackWithSmallFrameSize, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SizeF frameSize(320.0f, 480.0f);
    algorithm->SizeCalculationStack(hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: SetRealNavBarWidthWithDifferentValues
 * @tc.desc: Test SetRealNavBarWidth with different width values
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SetRealNavBarWidthWithDifferentValues, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();

    float testWidth1 = 100.0f;
    algorithm->SetRealNavBarWidth(testWidth1);
    EXPECT_EQ(algorithm->GetRealNavBarWidth(), testWidth1);

    float testWidth2 = 500.0f;
    algorithm->SetRealNavBarWidth(testWidth2);
    EXPECT_EQ(algorithm->GetRealNavBarWidth(), testWidth2);

    float testWidth3 = 0.0f;
    algorithm->SetRealNavBarWidth(testWidth3);
    EXPECT_EQ(algorithm->GetRealNavBarWidth(), testWidth3);
}

/**
 * @tc.name: SetIfNeedInitWithMultipleCalls
 * @tc.desc: Test SetIfNeedInit with multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SetIfNeedInitWithMultipleCalls, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();

    algorithm->SetIfNeedInit(true);
    EXPECT_TRUE(algorithm->ifNeedInit_);

    algorithm->SetIfNeedInit(false);
    EXPECT_FALSE(algorithm->ifNeedInit_);

    algorithm->SetIfNeedInit(true);
    EXPECT_TRUE(algorithm->ifNeedInit_);

    algorithm->SetIfNeedInit(false);
    EXPECT_FALSE(algorithm->ifNeedInit_);
}

/**
 * @tc.name: GetRangeWithDefaultValues
 * @tc.desc: Test GetRange with default values
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, GetRangeWithDefaultValues, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    if (pattern) {
        pattern->SetMinNavBarWidthValue(Dimension(150.0_vp));
        pattern->SetMaxNavBarWidthValue(Dimension(300.0_vp));
        pattern->SetMinContentWidthValue(Dimension(200.0_vp));
        pattern->SetUserSetNavBarRangeFlag(false);
        pattern->SetUserSetMinContentFlag(false);
        pattern->SetUserSetNavBarWidthFlag(false);
    }
    algorithm->GetRange(hostNode);
    EXPECT_FALSE(algorithm->userSetNavBarRangeFlag_);
    EXPECT_FALSE(algorithm->userSetMinContentFlag_);
    EXPECT_FALSE(algorithm->userSetNavBarWidthFlag_);
}

/**
 * @tc.name: CheckSizeInSplitWithVariousWidthCombinations
 * @tc.desc: Test CheckSizeInSplit with various width combinations
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithVariousWidthCombinations, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;

    float frameWidth = 1000.0f;
    float userSetNavBarWidth = 400.0f;
    float minNavBarWidth = 200.0f;
    float minContentWidth = 400.0f;

    algorithm->realNavBarWidth_ = userSetNavBarWidth;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);

    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_EQ(algorithm->realNavBarWidth_ + algorithm->realContentWidth_ + 1.0f, frameWidth);
}

/**
 * @tc.name: SizeCalculationWithAutoModeAndValidParams
 * @tc.desc: Test SizeCalculation with AUTO mode and valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationWithAutoModeAndValidParams, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(1000.0f, 1000.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
        algorithm->minNavBarWidthValue_ = Dimension(200.0_vp);
        algorithm->maxNavBarWidthValue_ = Dimension(400.0_vp);
        algorithm->minContentWidthValue_ = Dimension(300.0_vp);
    }
    SizeF frameSize(1000.0f, 1000.0f);
    algorithm->SizeCalculation(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: SizeCalculationStackWithWideFrame
 * @tc.desc: Test SizeCalculationStack with wide frame
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationStackWithWideFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SizeF frameSize(2560.0f, 1440.0f);
    algorithm->SizeCalculationStack(hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: RangeCalculationWithSquareFrame
 * @tc.desc: Test RangeCalculation with square frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, RangeCalculationWithSquareFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1024.0f, 1024.0f);
    constraint.maxSize = SizeF(1024.0f, 1024.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    algorithm->RangeCalculation(hostNode, layoutProperty);
    EXPECT_GT(algorithm->minNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->maxNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->minContentWidthValue_.value_, 0.0f);
}

/**
 * @tc.name: CalculateNavigationWidthWithPortraitFrame
 * @tc.desc: Test CalculateNavigationWidth with portrait frame
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CalculateNavigationWidthWithPortraitFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(360.0f, 760.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        algorithm->minNavBarWidthValue_ = Dimension(120.0_vp);
        algorithm->minContentWidthValue_ = Dimension(180.0_vp);
    }
    auto width = algorithm->CalculateNavigationWidth(hostNode);
    EXPECT_GT(width, 0.0f);
    EXPECT_LT(width, 360.0f);
}

/**
 * @tc.name: CalculateNavigationWidthWithLandscapeFrame
 * @tc.desc: Test CalculateNavigationWidth with landscape frame
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CalculateNavigationWidthWithLandscapeFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(1280.0f, 720.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        algorithm->minNavBarWidthValue_ = Dimension(200.0_vp);
        algorithm->minContentWidthValue_ = Dimension(300.0_vp);
    }
    auto width = algorithm->CalculateNavigationWidth(hostNode);
    EXPECT_GT(width, 0.0f);
    EXPECT_LT(width, 1280.0f);
}

/**
 * @tc.name: SizeCalculationForForceSplitWithSquareFrame
 * @tc.desc: Test SizeCalculationForForceSplit with square frame
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationForForceSplitWithSquareFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF frameSize(1024.0f, 1024.0f);
    algorithm->SizeCalculationForForceSplit(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_GT(algorithm->realDividerWidth_, 0.0f);
}

/**
 * @tc.name: RangeCalculationWithVerySmallFrame
 * @tc.desc: Test RangeCalculation with very small frame
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, RangeCalculationWithVerySmallFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(320.0f, 480.0f);
    constraint.maxSize = SizeF(320.0f, 480.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    algorithm->RangeCalculation(hostNode, layoutProperty);
    EXPECT_GT(algorithm->minNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->maxNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->minContentWidthValue_.value_, 0.0f);
}
/**
 * @tc.name: CheckSizeInSplitWithZeroMinWidths001
 * @tc.desc: Test CheckSizeInSplit with zero minimum widths
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithZeroMinWidths001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 400.0f;
    float frameWidth = 1200.0f;
    float userSetNavBarWidth = 400.0f;
    float minNavBarWidth = 0.0f;
    float minContentWidth = 0.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithVeryLargeFrame003
 * @tc.desc: Test CheckSizeInSplit with very large frame width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithVeryLargeFrame003, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 600.0f;
    float frameWidth = 3840.0f;
    float userSetNavBarWidth = 600.0f;
    float minNavBarWidth = 400.0f;
    float minContentWidth = 500.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_LT(algorithm->realNavBarWidth_ + algorithm->realContentWidth_, frameWidth);
}

/**
 * @tc.name: SizeCalculationWithVeryLargeFrame
 * @tc.desc: Test SizeCalculation with very large frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationWithVeryLargeFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.selfIdealSize = OptionalSizeF(3840.0f, 2160.0f);
        constraint.maxSize = SizeF(3840.0f, 2160.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
        algorithm->minNavBarWidthValue_ = Dimension(800.0_vp);
        algorithm->maxNavBarWidthValue_ = Dimension(1200.0_vp);
        algorithm->minContentWidthValue_ = Dimension(1000.0_vp);
    }
    SizeF frameSize(3840.0f, 2160.0f);
    algorithm->SizeCalculation(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: SizeCalculationStackWithVeryLargeFrame
 * @tc.desc: Test SizeCalculationStack with very large frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationStackWithVeryLargeFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SizeF frameSize(3840.0f, 2160.0f);
    algorithm->SizeCalculationStack(hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: SizeCalculationStackWithVerySmallFrame
 * @tc.desc: Test SizeCalculationStack with very small frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationStackWithVerySmallFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    SizeF frameSize(320.0f, 480.0f);
    algorithm->SizeCalculationStack(hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: RangeCalculationWithVeryLargeFrame
 * @tc.desc: Test RangeCalculation with very large frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, RangeCalculationWithVeryLargeFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(3840.0f, 2160.0f);
    constraint.maxSize = SizeF(3840.0f, 2160.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    algorithm->RangeCalculation(hostNode, layoutProperty);
    EXPECT_GT(algorithm->minNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->maxNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->minContentWidthValue_.value_, 0.0f);
}

/**
 * @tc.name: RangeCalculationWithVerySmallFrameAgain
 * @tc.desc: Test RangeCalculation with very small frame size again
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, RangeCalculationWithVerySmallFrameAgain, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(320.0f, 480.0f);
    constraint.maxSize = SizeF(320.0f, 480.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    algorithm->RangeCalculation(hostNode, layoutProperty);
    EXPECT_GT(algorithm->minNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->maxNavBarWidthValue_.value_, 0.0f);
    EXPECT_GT(algorithm->minContentWidthValue_.value_, 0.0f);
}

/**
 * @tc.name: CalculateNavigationWidthWithVeryLargeFrame
 * @tc.desc: Test CalculateNavigationWidth with very large frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CalculateNavigationWidthWithVeryLargeFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(3840.0f, 2160.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        algorithm->minNavBarWidthValue_ = Dimension(800.0_vp);
        algorithm->minContentWidthValue_ = Dimension(1000.0_vp);
    }
    auto width = algorithm->CalculateNavigationWidth(hostNode);
    EXPECT_GT(width, 0.0f);
}

/**
 * @tc.name: CalculateNavigationWidthWithVerySmallFrame
 * @tc.desc: Test CalculateNavigationWidth with very small frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CalculateNavigationWidthWithVerySmallFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.maxSize = SizeF(320.0f, 480.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        algorithm->minNavBarWidthValue_ = Dimension(100.0_vp);
        algorithm->minContentWidthValue_ = Dimension(120.0_vp);
    }
    auto width = algorithm->CalculateNavigationWidth(hostNode);
    EXPECT_GT(width, 0.0f);
}

/**
 * @tc.name: SizeCalculationForForceSplitWithVerySmallFrame
 * @tc.desc: Test SizeCalculationForForceSplit with very small frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationForForceSplitWithVerySmallFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF frameSize(320.0f, 480.0f);
    algorithm->SizeCalculationForForceSplit(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_GT(algorithm->realDividerWidth_, 0.0f);
}

/**
 * @tc.name: SizeCalculationWithAutoModeAndLargeFrame
 * @tc.desc: Test SizeCalculation with AUTO mode and large frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SizeCalculationWithAutoModeAndLargeFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    if (layoutProperty) {
        LayoutConstraintF constraint;
        constraint.selfIdealSize = OptionalSizeF(3840.0f, 2160.0f);
        constraint.maxSize = SizeF(3840.0f, 2160.0f);
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
        algorithm->minNavBarWidthValue_ = Dimension(800.0_vp);
        algorithm->minContentWidthValue_ = Dimension(1000.0_vp);
    }
    SizeF frameSize(3840.0f, 2160.0f);
    algorithm->SizeCalculation(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, frameSize);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithVeryLargeFrame002
 * @tc.desc: Test CheckSizeInSplit with very large frame width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithVeryLargeFrame002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 800.0f;
    float frameWidth = 3840.0f;
    float userSetNavBarWidth = 800.0f;
    float minNavBarWidth = 600.0f;
    float minContentWidth = 700.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithVerySmallFrame
 * @tc.desc: Test CheckSizeInSplit with very small frame width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithVerySmallFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 80.0f;
    float frameWidth = 320.0f;
    float userSetNavBarWidth = 80.0f;
    float minNavBarWidth = 60.0f;
    float minContentWidth = 70.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: GetRangeWithVerySmallFrame001
 * @tc.desc: Test GetRange with very small frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, GetRangeWithVerySmallFrame001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    if (pattern) {
        pattern->SetMinNavBarWidthValue(Dimension(80.0_vp));
        pattern->SetMaxNavBarWidthValue(Dimension(120.0_vp));
        pattern->SetMinContentWidthValue(Dimension(100.0_vp));
        pattern->SetUserSetNavBarRangeFlag(true);
        pattern->SetUserSetMinContentFlag(true);
        pattern->SetUserSetNavBarWidthFlag(true);
    }
    algorithm->GetRange(hostNode);
    EXPECT_TRUE(algorithm->userSetNavBarRangeFlag_);
    EXPECT_TRUE(algorithm->userSetMinContentFlag_);
    EXPECT_TRUE(algorithm->userSetNavBarWidthFlag_);
}

/**
 * @tc.name: GetRangeWithVeryLargeFrame
 * @tc.desc: Test GetRange with very large frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, GetRangeWithVeryLargeFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    if (pattern) {
        pattern->SetMinNavBarWidthValue(Dimension(800.0_vp));
        pattern->SetMaxNavBarWidthValue(Dimension(1600.0_vp));
        pattern->SetMinContentWidthValue(Dimension(1200.0_vp));
        pattern->SetUserSetNavBarRangeFlag(true);
        pattern->SetUserSetMinContentFlag(true);
        pattern->SetUserSetNavBarWidthFlag(true);
    }
    algorithm->GetRange(hostNode);
    EXPECT_TRUE(algorithm->userSetNavBarRangeFlag_);
    EXPECT_TRUE(algorithm->userSetMinContentFlag_);
    EXPECT_TRUE(algorithm->userSetNavBarWidthFlag_);
}

/**
 * @tc.name: GetRangeWithVerySmallFrame002
 * @tc.desc: Test GetRange with very small frame size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, GetRangeWithVerySmallFrame002, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    if (pattern) {
        pattern->SetMinNavBarWidthValue(Dimension(80.0_vp));
        pattern->SetMaxNavBarWidthValue(Dimension(120.0_vp));
        pattern->SetMinContentWidthValue(Dimension(100.0_vp));
        pattern->SetUserSetNavBarRangeFlag(true);
        pattern->SetUserSetMinContentFlag(true);
        pattern->SetUserSetNavBarWidthFlag(true);
    }
    algorithm->GetRange(hostNode);
    EXPECT_TRUE(algorithm->userSetNavBarRangeFlag_);
    EXPECT_TRUE(algorithm->userSetMinContentFlag_);
    EXPECT_TRUE(algorithm->userSetNavBarWidthFlag_);
}

/**
 * @tc.name: CheckSizeInSplitWithExtremeValues001
 * @tc.desc: Test CheckSizeInSplit with extreme values
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithExtremeValues001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 1000.0f;
    float frameWidth = 2000.0f;
    float userSetNavBarWidth = 1000.0f;
    float minNavBarWidth = 800.0f;
    float minContentWidth = 1200.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
    EXPECT_GT(algorithm->realNavBarWidth_, 0.0f);
    EXPECT_EQ(algorithm->realNavBarWidth_ + algorithm->realContentWidth_ + 1.0f, frameWidth);
}

/**
 * @tc.name: CheckSizeInSplitWithZeroMinWidths
 * @tc.desc: Test CheckSizeInSplit with zero minimum widths
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithZeroMinWidths, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 400.0f;
    float frameWidth = 800.0f;
    float userSetNavBarWidth = 400.0f;
    float minNavBarWidth = 0.0f;
    float minContentWidth = 0.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithVeryLargeFrame
 * @tc.desc: Test CheckSizeInSplit with very large frame width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithVeryLargeFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 1200.0f;
    float frameWidth = 2400.0f;
    float userSetNavBarWidth = 1200.0f;
    float minNavBarWidth = 800.0f;
    float minContentWidth = 1000.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithNarrowFrame
 * @tc.desc: Test CheckSizeInSplit with narrow frame width
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithNarrowFrame, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 150.0f;
    float frameWidth = 360.0f;
    float userSetNavBarWidth = 150.0f;
    float minNavBarWidth = 120.0f;
    float minContentWidth = 130.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: CheckSizeInSplitWithExtremeValues
 * @tc.desc: Test CheckSizeInSplit with extreme values
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, CheckSizeInSplitWithExtremeValues, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->realNavBarWidth_ = 100.0f;
    float frameWidth = 200.0f;
    float userSetNavBarWidth = 100.0f;
    float minNavBarWidth = 800.0f;
    float minContentWidth = 120.0f;
    algorithm->CheckSizeInSplit(frameWidth, userSetNavBarWidth, minNavBarWidth, minContentWidth);
    EXPECT_GT(algorithm->realContentWidth_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNodeNullHost001
 * @tc.desc: Test MeasurePrimaryContentNode with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasurePrimaryContentNodeNullHost001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF primaryNodeSize(1000.0f, 1000.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), nullptr, layoutProperty, primaryNodeSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNodeNullPrimary001
 * @tc.desc: Test MeasurePrimaryContentNode with null primaryContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasurePrimaryContentNodeNullPrimary001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF primaryNodeSize(1000.0f, 1000.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNodeNotVisible001
 * @tc.desc: Test MeasurePrimaryContentNode with invisible primaryContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasurePrimaryContentNodeNotVisible001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto primaryContentNode = CreateChildNode("primaryContent");
    primaryContentNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF primaryNodeSize(1000.0f, 1000.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNodeNullWrapper001
 * @tc.desc: Test MeasurePrimaryContentNode with null nodeWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasurePrimaryContentNodeNullWrapper001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto primaryContentNode = CreateChildNode("primaryContent");
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF primaryNodeSize(1000.0f, 1000.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_EQ(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNodeAutoHeight001
 * @tc.desc: Test MeasurePrimaryContentNode with auto height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasurePrimaryContentNodeAutoHeight001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto primaryContentNode = CreateChildNode("primaryContent");
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(1000.0f), CalcLength("auto"));
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF primaryNodeSize(500.0f, 800.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_GT(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasurePrimaryContentNodeNotAutoHeight001
 * @tc.desc: Test MeasurePrimaryContentNode with fixed height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasurePrimaryContentNodeNotAutoHeight001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto primaryContentNode = CreateChildNode("primaryContent");
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF primaryNodeSize(500.0f, 800.0f);
    algorithm->MeasurePrimaryContentNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, primaryNodeSize);
    EXPECT_GT(algorithm->realNavBarHeight_, 0.0f);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNodeNullPh001
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode with null phNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitPlaceHolderNodeNullPh001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNodeNullProperty001
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode with null phProperty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitPlaceHolderNodeNullProperty001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto phNode = FrameNode::CreateFrameNode(
        "forceSplitPH", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    phNode->layoutProperty_ = nullptr;
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNodeNotVisible001
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode with invisible node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitPlaceHolderNodeNotVisible001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto phNode = CreateChildNode("forceSplitPH");
    phNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->AddChild(phNode);
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = phNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(phNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNodeVisibleNotAutoHeight001
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode visible with fixed height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitPlaceHolderNodeVisibleNotAutoHeight001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto phNode = CreateChildNode("forceSplitPH");
    hostNode->AddChild(phNode);
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = phNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(phNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNodeVisibleAutoHeight001
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode visible with auto height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitPlaceHolderNodeVisibleAutoHeight001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto phNode = CreateChildNode("forceSplitPH");
    hostNode->AddChild(phNode);
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(1000.0f), CalcLength("auto"));
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = phNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(phNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureForceSplitPlaceHolderNodeNullWrapper001
 * @tc.desc: Test MeasureForceSplitPlaceHolderNode with null phWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitPlaceHolderNodeNullWrapper001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto phNode = CreateChildNode("forceSplitPH");
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureForceSplitPlaceHolderNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: LayoutForceSplitPlaceHolderNodeNullPh001
 * @tc.desc: Test LayoutForceSplitPlaceHolderNode with null phNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitPlaceHolderNodeNullPh001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutForceSplitPlaceHolderNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
}

/**
 * @tc.name: LayoutForceSplitPlaceHolderNodeNullWrapper001
 * @tc.desc: Test LayoutForceSplitPlaceHolderNode with null phWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitPlaceHolderNodeNullWrapper001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto phNode = CreateChildNode("forceSplitPH");
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutForceSplitPlaceHolderNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
}

/**
 * @tc.name: LayoutForceSplitPlaceHolderNodeNormal001
 * @tc.desc: Test LayoutForceSplitPlaceHolderNode normal path
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitPlaceHolderNodeNormal001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto phNode = CreateChildNode("forceSplitPH");
    hostNode->AddChild(phNode);
    hostNode->SetForceSplitPlaceHolderNode(phNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = phNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(phNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->LayoutForceSplitPlaceHolderNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    auto offset = childGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 301.0f);
}

/**
 * @tc.name: MeasureRelatedPageNodeNullNode001
 * @tc.desc: Test MeasureRelatedPageNode with null node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureRelatedPageNodeNullNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureRelatedPageNodeNotVisible001
 * @tc.desc: Test MeasureRelatedPageNode with invisible node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureRelatedPageNodeNotVisible001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto relatedNode = CreateChildNode("relatedPage");
    relatedNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureRelatedPageNodeNullWrapper001
 * @tc.desc: Test MeasureRelatedPageNode with null wrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureRelatedPageNodeNullWrapper001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto relatedNode = CreateChildNode("relatedPage");
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureRelatedPageNodeNotAutoHeight001
 * @tc.desc: Test MeasureRelatedPageNode with fixed height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureRelatedPageNodeNotAutoHeight001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto relatedNode = CreateChildNode("relatedPage");
    hostNode->AddChild(relatedNode);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = relatedNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(relatedNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: MeasureRelatedPageNodeAutoHeight001
 * @tc.desc: Test MeasureRelatedPageNode with auto height
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureRelatedPageNodeAutoHeight001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto relatedNode = CreateChildNode("relatedPage");
    hostNode->AddChild(relatedNode);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(1000.0f), CalcLength("auto"));
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = relatedNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(relatedNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    SizeF phSize(500.0f, 800.0f);
    algorithm->MeasureRelatedPageNode(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, phSize);
}

/**
 * @tc.name: LayoutRelatedPageNodeNullNode001
 * @tc.desc: Test LayoutRelatedPageNode with null node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutRelatedPageNodeNullNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutRelatedPageNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
}

/**
 * @tc.name: LayoutRelatedPageNodeNotVisible001
 * @tc.desc: Test LayoutRelatedPageNode with invisible node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutRelatedPageNodeNotVisible001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto relatedNode = CreateChildNode("relatedPage");
    relatedNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutRelatedPageNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
}

/**
 * @tc.name: LayoutRelatedPageNodeNullWrapper001
 * @tc.desc: Test LayoutRelatedPageNode with null wrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutRelatedPageNodeNullWrapper001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto relatedNode = CreateChildNode("relatedPage");
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutRelatedPageNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
}

/**
 * @tc.name: LayoutRelatedPageNodeNormal001
 * @tc.desc: Test LayoutRelatedPageNode normal path
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutRelatedPageNodeNormal001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto relatedNode = CreateChildNode("relatedPage");
    hostNode->AddChild(relatedNode);
    hostNode->SetRelatedPageDestNode(relatedNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = relatedNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(relatedNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->LayoutRelatedPageNode(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 300.0f, 1.0f);
    auto offset = childGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 301.0f);
}

/**
 * @tc.name: MeasureForceSplitMaskNodesNullLayoutWrapper001
 * @tc.desc: Test MeasureForceSplitMaskNodes with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitMaskNodesNullLayoutWrapper001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    algorithm->MeasureForceSplitMaskNodes(nullptr, hostNode, layoutProperty);
}

/**
 * @tc.name: MeasureForceSplitMaskNodesNullHostNode001
 * @tc.desc: Test MeasureForceSplitMaskNodes with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitMaskNodesNullHostNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->MeasureForceSplitMaskNodes(layoutWrapper.GetRawPtr(), nullptr, layoutProperty);
}

/**
 * @tc.name: MeasureForceSplitMaskNodesNullProperty001
 * @tc.desc: Test MeasureForceSplitMaskNodes with null navigationLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitMaskNodesNullProperty001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->MeasureForceSplitMaskNodes(layoutWrapper.GetRawPtr(), hostNode, nullptr);
}

/**
 * @tc.name: MeasureForceSplitMaskNodesNoMask001
 * @tc.desc: Test MeasureForceSplitMaskNodes with no mask nodes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitMaskNodesNoMask001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->primaryNodeSize_ = SizeF(400.0f, 800.0f);
    algorithm->contentSize_ = SizeF(500.0f, 800.0f);
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->MeasureForceSplitMaskNodes(layoutWrapper.GetRawPtr(), hostNode, layoutProperty);
}

/**
 * @tc.name: MeasureForceSplitMaskNodesWithMask001
 * @tc.desc: Test MeasureForceSplitMaskNodes with mask nodes set
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitMaskNodesWithMask001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->primaryNodeSize_ = SizeF(400.0f, 800.0f);
    algorithm->contentSize_ = SizeF(500.0f, 800.0f);
    auto hostNode = CreateNavigationNode();
    auto leftMask = CreateChildNode("leftMask");
    auto rightMask = CreateChildNode("rightMask");
    hostNode->AddChild(leftMask);
    hostNode->AddChild(rightMask);
    hostNode->leftMaskNode_ = leftMask;
    hostNode->rightMaskNode_ = rightMask;
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto leftGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto leftProp = leftMask->GetLayoutProperty();
    auto leftWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(leftMask, leftGeoNode, leftProp);
    layoutWrapper->AppendChild(leftWrapper);
    auto rightGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto rightProp = rightMask->GetLayoutProperty();
    auto rightWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(rightMask, rightGeoNode, rightProp);
    layoutWrapper->AppendChild(rightWrapper);
    algorithm->MeasureForceSplitMaskNodes(layoutWrapper.GetRawPtr(), hostNode, layoutProperty);
}

/**
 * @tc.name: MeasureForceSplitMaskNodesLeftNull001
 * @tc.desc: Test MeasureForceSplitMaskNodes with null left mask but valid right mask
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureForceSplitMaskNodesLeftNull001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->primaryNodeSize_ = SizeF(400.0f, 800.0f);
    algorithm->contentSize_ = SizeF(500.0f, 800.0f);
    auto hostNode = CreateNavigationNode();
    auto rightMask = CreateChildNode("rightMask");
    hostNode->AddChild(rightMask);
    hostNode->rightMaskNode_ = rightMask;
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto rightGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto rightProp = rightMask->GetLayoutProperty();
    auto rightWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(rightMask, rightGeoNode, rightProp);
    layoutWrapper->AppendChild(rightWrapper);
    algorithm->MeasureForceSplitMaskNodes(layoutWrapper.GetRawPtr(), hostNode, layoutProperty);
}

/**
 * @tc.name: LayoutForceSplitMaskNodesNullLayoutWrapper001
 * @tc.desc: Test LayoutForceSplitMaskNodes with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitMaskNodesNullLayoutWrapper001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    algorithm->LayoutForceSplitMaskNodes(nullptr, hostNode, layoutProperty, 400.0f, 1.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodesNullHostNode001
 * @tc.desc: Test LayoutForceSplitMaskNodes with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitMaskNodesNullHostNode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutForceSplitMaskNodes(layoutWrapper.GetRawPtr(), nullptr, layoutProperty, 400.0f, 1.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodesNullProperty001
 * @tc.desc: Test LayoutForceSplitMaskNodes with null navigationLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitMaskNodesNullProperty001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->LayoutForceSplitMaskNodes(layoutWrapper.GetRawPtr(), hostNode, nullptr, 400.0f, 1.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodesNullGeo001
 * @tc.desc: Test LayoutForceSplitMaskNodes with null navigationGeometryNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitMaskNodesNullGeo001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, nullptr, layoutProperty);
    algorithm->LayoutForceSplitMaskNodes(layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 400.0f, 1.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodesLeftNotVisible001
 * @tc.desc: Test LayoutForceSplitMaskNodes with left mask not visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitMaskNodesLeftNotVisible001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto leftMask = CreateChildNode("leftMask");
    leftMask->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->AddChild(leftMask);
    hostNode->leftMaskNode_ = leftMask;
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto leftGeoNode = AceType::MakeRefPtr<GeometryNode>();
    leftGeoNode->SetFrameSize(SizeF(400.0f, 800.0f));
    auto leftProp = leftMask->GetLayoutProperty();
    auto leftWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(leftMask, leftGeoNode, leftProp);
    layoutWrapper->AppendChild(leftWrapper);
    algorithm->LayoutForceSplitMaskNodes(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 400.0f, 1.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodesRightNotVisible001
 * @tc.desc: Test LayoutForceSplitMaskNodes with right mask not visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitMaskNodesRightNotVisible001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto leftMask = CreateChildNode("leftMask");
    auto rightMask = CreateChildNode("rightMask");
    rightMask->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->AddChild(leftMask);
    hostNode->AddChild(rightMask);
    hostNode->leftMaskNode_ = leftMask;
    hostNode->rightMaskNode_ = rightMask;
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto leftGeoNode = AceType::MakeRefPtr<GeometryNode>();
    leftGeoNode->SetFrameSize(SizeF(400.0f, 800.0f));
    auto leftProp = leftMask->GetLayoutProperty();
    auto leftWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(leftMask, leftGeoNode, leftProp);
    layoutWrapper->AppendChild(leftWrapper);
    auto rightGeoNode = AceType::MakeRefPtr<GeometryNode>();
    rightGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto rightProp = rightMask->GetLayoutProperty();
    auto rightWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(rightMask, rightGeoNode, rightProp);
    layoutWrapper->AppendChild(rightWrapper);
    algorithm->LayoutForceSplitMaskNodes(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 400.0f, 1.0f);
}

/**
 * @tc.name: LayoutForceSplitMaskNodesBothVisible001
 * @tc.desc: Test LayoutForceSplitMaskNodes with both masks visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutForceSplitMaskNodesBothVisible001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto leftMask = CreateChildNode("leftMask");
    auto rightMask = CreateChildNode("rightMask");
    hostNode->AddChild(leftMask);
    hostNode->AddChild(rightMask);
    hostNode->leftMaskNode_ = leftMask;
    hostNode->rightMaskNode_ = rightMask;
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto leftGeoNode = AceType::MakeRefPtr<GeometryNode>();
    leftGeoNode->SetFrameSize(SizeF(400.0f, 800.0f));
    auto leftProp = leftMask->GetLayoutProperty();
    auto leftWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(leftMask, leftGeoNode, leftProp);
    layoutWrapper->AppendChild(leftWrapper);
    auto rightGeoNode = AceType::MakeRefPtr<GeometryNode>();
    rightGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto rightProp = rightMask->GetLayoutProperty();
    auto rightWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(rightMask, rightGeoNode, rightProp);
    layoutWrapper->AppendChild(rightWrapper);
    algorithm->LayoutForceSplitMaskNodes(
        layoutWrapper.GetRawPtr(), hostNode, layoutProperty, 400.0f, 1.0f);
    auto rightOffset = rightGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(rightOffset.GetX(), 401.0f);
}

/**
 * @tc.name: SetNavigationWidthEmptyStack001
 * @tc.desc: Test SetNavigationWidth with empty navigation stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SetNavigationWidthEmptyStack001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 300.0f);
}

/**
 * @tc.name: SetNavigationWidthStackMode001
 * @tc.desc: Test SetNavigationWidth with STACK mode and non-empty stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SetNavigationWidthStackMode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    algorithm->realContentWidth_ = 600.0f;
    auto hostNode = CreateNavigationNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.emplace_back(std::make_pair("page1", nullptr));
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 600.0f);
}

/**
 * @tc.name: SetNavigationWidthSplitMode001
 * @tc.desc: Test SetNavigationWidth with SPLIT mode and non-empty stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SetNavigationWidthSplitMode001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    algorithm->realContentWidth_ = 600.0f;
    algorithm->realDividerWidth_ = 1.0f;
    auto hostNode = CreateNavigationNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.emplace_back(std::make_pair("page1", nullptr));
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 901.0f);
}

/**
 * @tc.name: SetNavigationWidthNullHost001
 * @tc.desc: Test SetNavigationWidth with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SetNavigationWidthNullHost001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    auto plainNode = FrameNode::CreateFrameNode(
        "plain", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto layoutProperty = plainNode->GetLayoutProperty();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(plainNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 1000.0f);
}

/**
 * @tc.name: SetNavigationWidthNullStack001
 * @tc.desc: Test SetNavigationWidth with null navigationStack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, SetNavigationWidthNullStack001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->realNavBarWidth_ = 300.0f;
    auto hostNode = CreateNavigationNode();
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto savedStack = pattern->GetNavigationStack();
    pattern->SetNavigationStack(nullptr);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    SizeF size(1000.0f, 1000.0f);
    algorithm->SetNavigationWidth(layoutWrapper.GetRawPtr(), size);
    EXPECT_FLOAT_EQ(size.Width(), 1000.0f);
    pattern->SetNavigationStack(savedStack);
}

/**
 * @tc.name: MeasureSplitPlaceholderNullPlaceholder001
 * @tc.desc: Test MeasureSplitPlaceholder with null placeholderContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureSplitPlaceholderNullPlaceholder001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Measure(layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: MeasureSplitPlaceholderWithPlaceholder001
 * @tc.desc: Test MeasureSplitPlaceholder with valid placeholder node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureSplitPlaceholderWithPlaceholder001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto placeholderNode = CreateChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Measure(layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: MeasureSplitPlaceholderHideNavBar001
 * @tc.desc: Test MeasureSplitPlaceholder with hideNavBar true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureSplitPlaceholderHideNavBar001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto placeholderNode = CreateChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    layoutProperty->UpdateHideNavBar(true);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Measure(layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: MeasureSplitPlaceholderAutoHeight001
 * @tc.desc: Test MeasureSplitPlaceholder with auto height and empty stack in SPLIT mode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, MeasureSplitPlaceholderAutoHeight001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto placeholderNode = CreateChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(1000.0f, 1000.0f);
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    layoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutProperty->calcLayoutConstraint_->selfIdealSize = CalcSize(CalcLength(1000.0f), CalcLength("auto"));
    layoutProperty->UpdateContentConstraint();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Measure(layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: LayoutPrimaryContentNodeNullHost001
 * @tc.desc: Test LayoutPrimaryContentNode with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutPrimaryContentNodeNullHost001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto primaryContentNode = CreateChildNode("primaryContent");
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    algorithm->Layout(layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: LayoutPrimaryContentNodeNullPrimary001
 * @tc.desc: Test LayoutPrimaryContentNode with null primaryContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutPrimaryContentNodeNullPrimary001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    algorithm->Layout(layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: LayoutPrimaryContentNodeNotVisible001
 * @tc.desc: Test LayoutPrimaryContentNode with invisible primaryContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutPrimaryContentNodeNotVisible001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto primaryContentNode = CreateChildNode("primaryContent");
    primaryContentNode->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    algorithm->Layout(layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: LayoutPrimaryContentNodeNormal001
 * @tc.desc: Test LayoutPrimaryContentNode normal path with visible node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutPrimaryContentNodeNormal001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto primaryContentNode = CreateChildNode("primaryContent");
    hostNode->AddChild(primaryContentNode);
    hostNode->SetPrimaryContentNode(primaryContentNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = primaryContentNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(primaryContentNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    algorithm->Layout(layoutWrapper.GetRawPtr());
    auto offset = childGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 0.0f);
}

/**
 * @tc.name: LayoutSplitPlaceholderContentNullHost001
 * @tc.desc: Test LayoutSplitPlaceholderContent with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutSplitPlaceholderContentNullHost001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto placeholderNode = CreateChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Layout(layoutWrapper.GetRawPtr());
}

/**
 * @tc.name: LayoutSplitPlaceholderContentWithPlaceholder001
 * @tc.desc: Test LayoutSplitPlaceholderContent with valid placeholder in SPLIT mode and empty stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutSplitPlaceholderContentWithPlaceholder001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto navBarNode = CreateChildNode("navBar");
    hostNode->AddChild(navBarNode);
    hostNode->navBarNode_ = navBarNode;
    auto dividerNode = CreateChildNode("divider");
    hostNode->AddChild(dividerNode);
    hostNode->dividerNode_ = dividerNode;
    auto placeholderNode = CreateChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto navBarGeoNode = AceType::MakeRefPtr<GeometryNode>();
    navBarGeoNode->SetFrameSize(SizeF(500.0f, 1000.0f));
    auto navBarProp = navBarNode->GetLayoutProperty();
    auto navBarWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(navBarNode, navBarGeoNode, navBarProp);
    layoutWrapper->AppendChild(navBarWrapper);
    auto dividerGeoNode = AceType::MakeRefPtr<GeometryNode>();
    dividerGeoNode->SetFrameSize(SizeF(1.0f, 1000.0f));
    auto dividerProp = dividerNode->GetLayoutProperty();
    auto dividerWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, dividerGeoNode, dividerProp);
    layoutWrapper->AppendChild(dividerWrapper);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    algorithm->Layout(layoutWrapper.GetRawPtr());
    auto offset = childGeoNode->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 501.0f);
}

/**
 * @tc.name: LayoutSplitPlaceholderContentNonEmptyStack001
 * @tc.desc: Test LayoutSplitPlaceholderContent with non-empty stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLayoutAlgorithmTest, LayoutSplitPlaceholderContentNonEmptyStack001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto hostNode = CreateNavigationNode();
    auto placeholderNode = CreateChildNode("splitPlaceholder");
    hostNode->AddChild(placeholderNode);
    hostNode->SetPlaceholderContentNode(placeholderNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(1000.0f, 1000.0f));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(hostNode, geometryNode, layoutProperty);
    auto childGeoNode = AceType::MakeRefPtr<GeometryNode>();
    childGeoNode->SetFrameSize(SizeF(500.0f, 800.0f));
    auto childProp = placeholderNode->GetLayoutProperty();
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(placeholderNode, childGeoNode, childProp);
    layoutWrapper->AppendChild(childWrapper);
    algorithm->realNavBarWidth_ = 500.0f;
    algorithm->realDividerWidth_ = 1.0f;
    algorithm->primaryNodeSize_ = SizeF(500.0f, 1000.0f);
    algorithm->contentSize_ = SizeF(499.0f, 1000.0f);
    algorithm->navBarSize_ = SizeF(500.0f, 1000.0f);
    algorithm->dividerSize_ = SizeF(1.0f, 1000.0f);
    auto pattern = hostNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.emplace_back(std::make_pair("page1", nullptr));
    algorithm->Layout(layoutWrapper.GetRawPtr());
}
} // namespace OHOS::Ace::NG
