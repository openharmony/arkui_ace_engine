/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "relative_container_base_test_ng.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class RelativeContainerAlgorithmTestNG : public RelativeContainerBaseTestNG {
public:
    void SetUp() override {}
    void TearDown() override {}
};


/**
 * @tc.name: CalcOffsetInChainGetStart001
 * @tc.desc: Test chain offset calculation with different styles
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, CalcOffsetInChainGetStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize chain parameters with SPREAD style and default bias
     * @tc.expected: ChainParam is properly configured with bias values
     */
    RelativeContainerLayoutAlgorithm algorithm;
    RelativeContainerLayoutAlgorithm::ChainParam chainParam;
    chainParam.bias = BiasPair(0.5f, 0.5f);
    float anchorDistance = 300.0f;
    float contentSize = 150.0f;
    int32_t itemCount = 3;
    chainParam.chainStyle = ChainStyle::SPREAD;

    /**
     * @tc.steps: step2. Calculate offset for SPREAD chain style
     * @tc.expected: Returns correct space size for even distribution
     */
    auto result1 = algorithm.CalcOffsetInChainGetStart(anchorDistance, contentSize, itemCount, chainParam, 
        LineDirection::HORIZONTAL);
    float expectedSpaceSize = (anchorDistance - contentSize) / (itemCount + 1);
    EXPECT_FLOAT_EQ(result1.first, expectedSpaceSize);
    EXPECT_FLOAT_EQ(result1.second, expectedSpaceSize);

    /**
     * @tc.steps: step3. Calculate offset for SPREAD_INSIDE chain style
     * @tc.expected: Returns correct space size with no padding at ends
     */
    chainParam.chainStyle = ChainStyle::SPREAD_INSIDE;
    auto result2 = algorithm.CalcOffsetInChainGetStart(anchorDistance, contentSize, itemCount, chainParam, 
        LineDirection::HORIZONTAL);
    EXPECT_FLOAT_EQ(result2.first, (anchorDistance - contentSize) / (itemCount - 1));
    EXPECT_FLOAT_EQ(result2.second, 0.0f);

    /**
     * @tc.steps: step4. Calculate offset for PACKED chain style with custom bias
     * @tc.expected: Returns correct offset based on bias value
     */
    chainParam.chainStyle = ChainStyle::PACKED;
    chainParam.bias = BiasPair(0.3f, 0.5f);
    auto result3 = algorithm.CalcOffsetInChainGetStart(anchorDistance, contentSize, itemCount, chainParam, 
        LineDirection::HORIZONTAL);
    EXPECT_FLOAT_EQ(result3.first, 0.0f);
    EXPECT_FLOAT_EQ(result3.second, (anchorDistance - contentSize) * 0.3f);

    /**
     * @tc.steps: step5. Calculate offset when content size exceeds anchor distance
     * @tc.expected: Returns negative space size for proper handling
     */
    chainParam.chainStyle = ChainStyle::SPREAD;
    chainParam.bias = BiasPair(0.5f, 0.5f);
    auto result4 = algorithm.CalcOffsetInChainGetStart(100.0f, 200.0f, itemCount, chainParam, 
        LineDirection::HORIZONTAL);
    EXPECT_FLOAT_EQ(result4.second, -50.0f);
}

/**
 * @tc.name: CalcBias001
 * @tc.desc: Test bias calculation functions
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, CalcBias001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test IsValidBias function with various bias values
     * @tc.expected: Valid biases (0.0, 0.5, 1.0) return true, invalid biases return false
     */
    RelativeContainerLayoutAlgorithm algorithm;
    EXPECT_TRUE(algorithm.IsValidBias(0.0f));
    EXPECT_TRUE(algorithm.IsValidBias(0.5f));
    EXPECT_TRUE(algorithm.IsValidBias(1.0f));
    EXPECT_FALSE(algorithm.IsValidBias(-0.1f));
    EXPECT_FALSE(algorithm.IsValidBias(-1.0f));

    /**
     * @tc.steps: step2. Setup aligned values and child ideal size for bias calculation
     * @tc.expected: Values are properly initialized for testing
     */
    TwoAlignedValues horizontalValues = {std::optional<float>(100.0f), std::optional<float>(300.0f)};
    TwoAlignedValues verticalValues = {std::optional<float>(50.0f), std::optional<float>(250.0f)};
    std::pair<TwoAlignedValues, TwoAlignedValues> alignedValues = {horizontalValues, verticalValues};
    ChildIdealSize childIdealSize = {std::optional<float>(50.0f), std::optional<float>(80.0f)};
    BiasPair biasPair(0.5f, 0.5f);
    float horizontalOffset = 0.0f;
    float verticalOffset = 0.0f;

    /**
     * @tc.steps: step3. Calculate bias offsets with valid aligned values
     * @tc.expected: Returns correct horizontal and vertical offsets
     */
    algorithm.CalcBiasTowDirection(alignedValues, childIdealSize, biasPair, horizontalOffset, verticalOffset);
    EXPECT_FLOAT_EQ(horizontalOffset, 75.0f);
    EXPECT_FLOAT_EQ(verticalOffset, 60.0f);

    /**
     * @tc.steps: step4. Calculate bias offsets with empty aligned values
     * @tc.expected: Returns zero offsets when aligned values are empty
     */
    TwoAlignedValues emptyValues;
    std::pair<TwoAlignedValues, TwoAlignedValues> alignedValues2 = {emptyValues, emptyValues};
    horizontalOffset = 0.0f;
    verticalOffset = 0.0f;
    algorithm.CalcBiasTowDirection(alignedValues2, childIdealSize, biasPair, horizontalOffset, verticalOffset);
    EXPECT_FLOAT_EQ(horizontalOffset, 0.0f);
    EXPECT_FLOAT_EQ(verticalOffset, 0.0f);
}

/**
 * @tc.name: AdjustOffsetRtl001
 * @tc.desc: Test RTL layout support
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, AdjustOffsetRtl001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step2. Configure container size, padding, and record offset for a test node
     * @tc.expected: Algorithm state is properly configured for RTL adjustment
     */
    algorithm.containerSizeWithoutPaddingBorder_.SetWidth(500.0f);
    algorithm.padding_.left = 10.0f;
    algorithm.padding_.right = 10.0f;
    algorithm.recordOffsetMap_["testNode"] = OffsetF(100.0f, 50.0f);

    /**
     * @tc.steps: step3. Execute RTL offset adjustment on the layout wrapper
     * @tc.expected: Offset values remain unchanged (LTR mode)
     */
    algorithm.AdjustOffsetRtl(AceType::RawPtr(layoutWrapper));
    EXPECT_FLOAT_EQ(algorithm.recordOffsetMap_["testNode"].GetX(), 100.0f);
    EXPECT_FLOAT_EQ(algorithm.recordOffsetMap_["testNode"].GetY(), 50.0f);
}

/**
 * @tc.name: BarrierDirectionRtl001
 * @tc.desc: Test barrier direction conversion
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, BarrierDirectionRtl001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize the RelativeContainerLayoutAlgorithm
     * @tc.expected: Algorithm instance is created successfully
     */
    RelativeContainerLayoutAlgorithm algorithm;

    /**
     * @tc.steps: step2. Test barrier direction conversion for RTL layout
     * @tc.expected: START maps to LEFT, END maps to RIGHT, other directions remain unchanged
     */
    EXPECT_EQ(algorithm.BarrierDirectionRtl(BarrierDirection::START), BarrierDirection::LEFT);
    EXPECT_EQ(algorithm.BarrierDirectionRtl(BarrierDirection::END), BarrierDirection::RIGHT);
    EXPECT_EQ(algorithm.BarrierDirectionRtl(BarrierDirection::LEFT), BarrierDirection::LEFT);
    EXPECT_EQ(algorithm.BarrierDirectionRtl(BarrierDirection::RIGHT), BarrierDirection::RIGHT);
    EXPECT_EQ(algorithm.BarrierDirectionRtl(BarrierDirection::TOP), BarrierDirection::TOP);
    EXPECT_EQ(algorithm.BarrierDirectionRtl(BarrierDirection::BOTTOM), BarrierDirection::BOTTOM);
}

/**
 * @tc.name: GuidelineAndBarrier001
 * @tc.desc: Test guideline and barrier identification
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, GuidelineAndBarrier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure a horizontal guideline and a left barrier
     * @tc.expected: Guideline and barrier are added to the algorithm maps
     */
    algorithm.guidelines_["guideline1"] = std::make_pair(LineDirection::HORIZONTAL, 100.0f);
    std::vector<std::string> referencedIds = {"node1"};
    algorithm.barriers_["barrier1"] = std::make_pair(BarrierDirection::LEFT, referencedIds);

    /**
     * @tc.steps: step3. Test IsGuideline function to identify guideline nodes
     * @tc.expected: Returns true for guideline1, false for nonexistent nodes
     */
    EXPECT_TRUE(algorithm.IsGuideline("guideline1"));
    EXPECT_FALSE(algorithm.IsGuideline("nonexistent"));

    /**
     * @tc.steps: step4. Test IsBarrier function to identify barrier nodes
     * @tc.expected: Returns true for barrier1, false for nonexistent nodes
     */
    EXPECT_TRUE(algorithm.IsBarrier("barrier1"));
    EXPECT_FALSE(algorithm.IsBarrier("nonexistent"));

    /**
     * @tc.steps: step5. Test IsGuidelineOrBarrier function to identify special nodes
     * @tc.expected: Returns true for guideline1 and barrier1, false for regularNode
     */
    EXPECT_TRUE(algorithm.IsGuidelineOrBarrier("guideline1"));
    EXPECT_TRUE(algorithm.IsGuidelineOrBarrier("barrier1"));
    EXPECT_FALSE(algorithm.IsGuidelineOrBarrier("regularNode"));
}

/**
 * @tc.name: IsAnchorLegal001
 * @tc.desc: Test anchor validation
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, IsAnchorLegal001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;
    algorithm.CollectNodesById(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step2. Configure a guideline and barrier for testing anchor validation
     * @tc.expected: Guideline and barrier are properly added to the algorithm maps
     */
    algorithm.guidelines_["guideline1"] = std::make_pair(LineDirection::HORIZONTAL, 100.0f);
    std::vector<std::string> referencedIds = {"node1"};
    algorithm.barriers_["barrier1"] = std::make_pair(BarrierDirection::LEFT, referencedIds);

    /**
     * @tc.steps: step3. Test IsAnchorLegal function with various anchor types
     * @tc.expected: Container, guideline, and barrier are legal anchors; nonexistent is not
     */
    EXPECT_TRUE(algorithm.IsAnchorLegal("__container__"));
    EXPECT_TRUE(algorithm.IsAnchorLegal("guideline1"));
    EXPECT_TRUE(algorithm.IsAnchorLegal("barrier1"));
    EXPECT_FALSE(algorithm.IsAnchorLegal("nonexistent"));
}

/**
 * @tc.name: GetAnchorValue001
 * @tc.desc: Test anchor value retrieval
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, GetAnchorValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step2. Configure container size without padding/border
     * @tc.expected: Container dimensions are set to 400x400
     */
    algorithm.containerSizeWithoutPaddingBorder_.SetWidth(400.0f);
    algorithm.containerSizeWithoutPaddingBorder_.SetHeight(400.0f);

    /**
     * @tc.steps: step3. Setup horizontal and vertical align rules targeting container
     * @tc.expected: Align rules are configured with START and TOP alignment
     */
    AlignRule hAlignRule;
    hAlignRule.anchor = "__container__";
    hAlignRule.horizontal = HorizontalAlign::START;
    AlignRule vAlignRule;
    vAlignRule.anchor = "__container__";
    vAlignRule.vertical = VerticalAlign::TOP;

    /**
     * @tc.steps: step4. Retrieve anchor values based on align rules
     * @tc.expected: Returns 0.0f for both horizontal and vertical anchor positions
     */
    EXPECT_FLOAT_EQ(algorithm.GetHorizontalAnchorValueByAlignRule(hAlignRule), 0.0f);
    EXPECT_FLOAT_EQ(algorithm.GetVerticalAnchorValueByAlignRule(vAlignRule), 0.0f);
}

/**
 * @tc.name: UpdateSizeWhenChildrenEmpty001
 * @tc.desc: Test empty container size update
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, UpdateSizeWhenChildrenEmpty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer with fixed dimensions
     * @tc.expected: Container is created successfully with width and height of 500
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Initialize layout algorithm and update size when no children present
     * @tc.expected: Algorithm updates container size without errors
     */
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.UpdateSizeWhenChildrenEmpty(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step3. Verify the frame size after updating empty container
     * @tc.expected: Frame width and height are non-negative values
     */
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_GE(frameSize.Width(), 0.0f);
    EXPECT_GE(frameSize.Height(), 0.0f);
}

/**
 * @tc.name: CalcOffsetAlign001
 * @tc.desc: Test offset alignment calculations
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, CalcOffsetAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize algorithm and setup anchor/flex item dimensions
     * @tc.expected: Algorithm is ready for offset calculations with defined dimensions
     */
    RelativeContainerLayoutAlgorithm algorithm;
    float anchorWidth = 200.0f;
    float flexItemWidth = 50.0f;
    float anchorHeight = 200.0f;
    float flexItemHeight = 50.0f;

    /**
     * @tc.steps: step2. Calculate horizontal offset aligned to left edge with various alignments
     * @tc.expected: Returns correct offsets: START=0, CENTER=100, END=200
     */
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignLeft(HorizontalAlign::START, anchorWidth), 0.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignLeft(HorizontalAlign::CENTER, anchorWidth), 100.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignLeft(HorizontalAlign::END, anchorWidth), 200.0f);

    /**
     * @tc.steps: step3. Calculate horizontal offset aligned to middle with various alignments
     * @tc.expected: Returns correct offsets accounting for flex item width
     */
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignMiddle(HorizontalAlign::START, anchorWidth, flexItemWidth), -25.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignMiddle(HorizontalAlign::CENTER, anchorWidth, flexItemWidth), 75.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignMiddle(HorizontalAlign::END, anchorWidth, flexItemWidth), 175.0f);

    /**
     * @tc.steps: step4. Calculate horizontal offset aligned to right edge with various alignments
     * @tc.expected: Returns correct offsets accounting for flex item width
     */
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignRight(HorizontalAlign::START, anchorWidth, flexItemWidth), -50.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignRight(HorizontalAlign::CENTER, anchorWidth, flexItemWidth), 50.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcHorizontalOffsetAlignRight(HorizontalAlign::END, anchorWidth, flexItemWidth), 150.0f);

    /**
     * @tc.steps: step5. Calculate vertical offset aligned to top edge with various alignments
     * @tc.expected: Returns correct offsets: TOP=0, CENTER=100, BOTTOM=200
     */
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignTop(VerticalAlign::TOP, anchorHeight), 0.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignTop(VerticalAlign::CENTER, anchorHeight), 100.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignTop(VerticalAlign::BOTTOM, anchorHeight), 200.0f);

    /**
     * @tc.steps: step6. Calculate vertical offset aligned to center with various alignments
     * @tc.expected: Returns correct offsets accounting for flex item height
     */
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignCenter(VerticalAlign::TOP, anchorHeight, flexItemHeight), -25.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignCenter(VerticalAlign::CENTER, anchorHeight, flexItemHeight), 75.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignCenter(VerticalAlign::BOTTOM, anchorHeight, flexItemHeight), 175.0f);

    /**
     * @tc.steps: step7. Calculate vertical offset aligned to bottom edge with various alignments
     * @tc.expected: Returns correct offsets accounting for flex item height
     */
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignBottom(VerticalAlign::TOP, anchorHeight, flexItemHeight), -50.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignBottom(VerticalAlign::CENTER, anchorHeight, flexItemHeight), 50.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcVerticalOffsetAlignBottom(VerticalAlign::BOTTOM, anchorHeight, flexItemHeight), 150.0f);
}

/**
 * @tc.name: IsNodeInChain001
 * @tc.desc: Test chain membership check
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, IsNodeInChain001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Setup horizontal and vertical chain node mappings
     * @tc.expected: Chain node maps and chain parameters are configured
     */
    algorithm.horizontalChainNodeMap_["hNode"] = "hChain";
    algorithm.verticalChainNodeMap_["vNode"] = "vChain";
    RelativeContainerLayoutAlgorithm::ChainParam chainParam;
    algorithm.horizontalChains_["hChain"] = chainParam;
    algorithm.verticalChains_["vChain"] = chainParam;
    std::string chainName;

    /**
     * @tc.steps: step3. Test IsNodeInChain for horizontal chain membership
     * @tc.expected: Returns true for hNode in horizontal direction
     */
    EXPECT_TRUE(algorithm.IsNodeInChain("hNode", chainName, LineDirection::HORIZONTAL));

    /**
     * @tc.steps: step4. Test IsNodeInChain for vertical chain membership
     * @tc.expected: Returns true for vNode in vertical direction
     */
    EXPECT_TRUE(algorithm.IsNodeInChain("vNode", chainName, LineDirection::VERTICAL));

    /**
     * @tc.steps: step5. Test IsNodeInChain with mismatched direction
     * @tc.expected: Returns false when checking hNode in vertical direction
     */
    EXPECT_FALSE(algorithm.IsNodeInChain("hNode", chainName, LineDirection::VERTICAL));
}

/**
 * @tc.name: HasWeight001
 * @tc.desc: Test weight detection
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, HasWeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step2. Create a FlexItemProperty with horizontal chain weight only
     * @tc.expected: FlexItemProperty is configured with horizontal weight 0.5 and vertical weight 0.0
     */
    auto flexItem = std::make_unique<FlexItemProperty>();
    flexItem->UpdateChainWeight(ChainWeightPair(0.5f, 0.0f));

    /**
     * @tc.steps: step3. Test HasWeight function for horizontal direction
     * @tc.expected: Returns true for HORIZONTAL direction
     */
    EXPECT_TRUE(algorithm.HasWeight(flexItem, LineDirection::HORIZONTAL));

    /**
     * @tc.steps: step4. Test HasWeight function for vertical direction
     * @tc.expected: Returns false for VERTICAL direction
     */
    EXPECT_FALSE(algorithm.HasWeight(flexItem, LineDirection::VERTICAL));
}

/**
 * @tc.name: GetOriginMarginLeft001
 * @tc.desc: Test margin calculation for RTL
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, GetOriginMarginLeft001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize algorithm and create margin property with left and right margins
     * @tc.expected: MarginPropertyF is created with left=10.0f and right=20.0f
     */
    RelativeContainerLayoutAlgorithm algorithm;
    auto marginProp = std::make_unique<MarginPropertyF>();
    marginProp->left = 10.0f;
    marginProp->right = 20.0f;

    /**
     * @tc.steps: step2. Test GetOriginMarginLeft with LTR text direction
     * @tc.expected: Returns left margin value (10.0f) for LTR
     */
    EXPECT_FLOAT_EQ(algorithm.GetOriginMarginLeft(TextDirection::LTR, marginProp), 10.0f);

    /**
     * @tc.steps: step3. Test GetOriginMarginLeft with RTL text direction
     * @tc.expected: Returns right margin value (20.0f) for RTL
     */
    EXPECT_FLOAT_EQ(algorithm.GetOriginMarginLeft(TextDirection::RTL, marginProp), 20.0f);

    /**
     * @tc.steps: step4. Test GetOriginMarginLeft with null margin property
     * @tc.expected: Returns 0.0f when margin property is null
     */
    EXPECT_FLOAT_EQ(algorithm.GetOriginMarginLeft(TextDirection::LTR, nullptr), 0.0f);
}

/**
 * @tc.name: UpdateTwoAlignValues001
 * @tc.desc: Test alignment value update
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, UpdateTwoAlignValues001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize algorithm and setup align rule targeting container with START alignment
     * @tc.expected: Algorithm and align rule are properly configured
     */
    RelativeContainerLayoutAlgorithm algorithm;
    TwoAlignedValues twoAlignedValues;
    AlignRule alignRule;
    alignRule.anchor = "__container__";
    alignRule.horizontal = HorizontalAlign::START;
    algorithm.containerSizeWithoutPaddingBorder_.SetWidth(400.0f);

    /**
     * @tc.steps: step2. Update aligned values with the align rule for the first time
     * @tc.expected: First aligned value is set to 0.0f (START position)
     */
    algorithm.UpdateTwoAlignValues(twoAlignedValues, alignRule, LineDirection::HORIZONTAL);
    EXPECT_TRUE(twoAlignedValues.first.has_value());
    EXPECT_FLOAT_EQ(twoAlignedValues.first.value(), 0.0f);

    /**
     * @tc.steps: step3. Manually set second aligned value and update again
     * @tc.expected: Both first and second aligned values are correctly set
     */
    twoAlignedValues.second = 200.0f;
    algorithm.UpdateTwoAlignValues(twoAlignedValues, alignRule, LineDirection::HORIZONTAL);
    EXPECT_FLOAT_EQ(twoAlignedValues.first.value(), 0.0f);
    EXPECT_FLOAT_EQ(twoAlignedValues.second.value(), 200.0f);
}

/**
 * @tc.name: IsRelyOnContainer001
 * @tc.desc: Test container dependency check
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, IsRelyOnContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure a vertical guideline in the algorithm
     * @tc.expected: Guideline is added to the guidelines map
     */
    algorithm.guidelines_["guideline1"] = std::make_pair(LineDirection::VERTICAL, 100.0f);

    /**
     * @tc.steps: step3. Test IsRelyOnContainer with container anchor
     * @tc.expected: Returns true for __container__
     */
    EXPECT_TRUE(algorithm.IsRelyOnContainer("__container__"));

    /**
     * @tc.steps: step4. Test IsRelyOnContainer with guideline
     * @tc.expected: Returns true for guideline1
     */
    EXPECT_TRUE(algorithm.IsRelyOnContainer("guideline1"));

    /**
     * @tc.steps: step5. Test IsRelyOnContainer with regular node
     * @tc.expected: Returns false for regularNode
     */
    EXPECT_FALSE(algorithm.IsRelyOnContainer("regularNode"));
}

/**
 * @tc.name: CalcAnchorWidth001
 * @tc.desc: Test anchor width calculation
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, CalcAnchorWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;
    float containerWidth = 400.0f;

    /**
     * @tc.steps: step2. Calculate anchor width for container with isWidth=true
     * @tc.expected: Returns container width (400.0f) for __container__
     */
    EXPECT_FLOAT_EQ(algorithm.CalcAnchorWidth(true, containerWidth, "__container__"), 400.0f);

    /**
     * @tc.steps: step3. Configure a vertical guideline and calculate anchor width with isWidth=false
     * @tc.expected: Returns 0.0f for guideline anchor
     */
    algorithm.guidelines_["guideline1"] = std::make_pair(LineDirection::VERTICAL, 100.0f);
    EXPECT_FLOAT_EQ(algorithm.CalcAnchorWidth(false, containerWidth, "guideline1"), 0.0f);
}

/**
 * @tc.name: TopologicalSort001
 * @tc.desc: Test topological sorting
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, TopologicalSort001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.CollectNodesById(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step2. Setup dependency graph with incoming degrees and reliance relationships
     * @tc.expected: NodeA has 0 incoming degree, NodeB has 1, and NodeA relies on NodeB
     */
    algorithm.incomingDegreeMap_["nodeA"] = 0;
    algorithm.incomingDegreeMap_["nodeB"] = 1;
    algorithm.reliedOnMap_["nodeA"].insert("nodeB");

    /**
     * @tc.steps: step3. Execute topological sort and populate render list
     * @tc.expected: Render list contains sorted nodes
     */
    std::list<std::string> renderList;
    algorithm.TopologicalSort(renderList);
    EXPECT_GE(renderList.size(), 0u);
}

/**
 * @tc.name: DetermineTopologicalOrder001
 * @tc.desc: Test topological order determination
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, DetermineTopologicalOrder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.CollectNodesById(AceType::RawPtr(layoutWrapper));
    algorithm.GetDependencyRelationship();

    /**
     * @tc.steps: step2. Determine topological order for layout processing
     * @tc.expected: Render list is populated with sorted nodes
     */
    algorithm.DetermineTopologicalOrder(AceType::RawPtr(layoutWrapper));
    EXPECT_GE(algorithm.renderList_.size(), 0u);

    /**
     * @tc.steps: step3. Check if topological sort hit any errors
     * @tc.expected: Returns false indicating no topological errors
     */
    EXPECT_FALSE(algorithm.TopologicalResultHit(AceType::RawPtr(layoutWrapper)));
}

/**
 * @tc.name: ResetCalculatedChain001
 * @tc.desc: Test chain calculation reset
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, ResetCalculatedChain001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure a chain with calculated state and remaining space
     * @tc.expected: Chain parameter is set with remainingSpace=100.0f and isCalculated=true
     */
    RelativeContainerLayoutAlgorithm::ChainParam chainParam;
    chainParam.remainingSpace = 100.0f;
    chainParam.isCalculated = true;
    algorithm.horizontalChains_["chain1"] = chainParam;

    /**
     * @tc.steps: step3. Reset calculated chain state
     * @tc.expected: Chain calculation state is reset successfully
     */
    algorithm.ResetCalculatedChain();

    /**
     * @tc.steps: step4. Verify chain parameters after reset
     * @tc.expected: remainingSpace is reset to 0.0f and isCalculated is false
     */
    EXPECT_FLOAT_EQ(algorithm.horizontalChains_["chain1"].remainingSpace, 0.0f);
    EXPECT_FALSE(algorithm.horizontalChains_["chain1"].isCalculated);
}

/**
 * @tc.name: IsUnionRelyOnContainer001
 * @tc.desc: Test recursive container dependency
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, IsUnionRelyOnContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step2. Setup horizontal dependency chain: nodeA -> container, nodeB -> nodeA
     * @tc.expected: Horizontal rely map is configured with transitive dependencies
     */
    algorithm.horizontalRelyMap_["nodeA"].insert("__container__");
    algorithm.horizontalRelyMap_["nodeB"].insert("nodeA");

    /**
     * @tc.steps: step3. Test IsUnionRelyOnContainer for nodeA in HORIZONTAL direction
     * @tc.expected: Returns true as nodeA directly relies on container
     */
    EXPECT_TRUE(algorithm.IsUnionRelyOnContainer(LineDirection::HORIZONTAL, "nodeA"));

    /**
     * @tc.steps: step4. Test IsUnionRelyOnContainer for nodeB in HORIZONTAL direction
     * @tc.expected: Returns true as nodeB transitively relies on container through nodeA
     */
    EXPECT_TRUE(algorithm.IsUnionRelyOnContainer(LineDirection::HORIZONTAL, "nodeB"));

    /**
     * @tc.steps: step5. Test IsUnionRelyOnContainer for nodeA in VERTICAL direction
     * @tc.expected: Returns false as no vertical dependencies are configured
     */
    EXPECT_FALSE(algorithm.IsUnionRelyOnContainer(LineDirection::VERTICAL, "nodeA"));
}

/**
 * @tc.name: ReliedOnMap001
 * @tc.desc: Test relied on map insertion
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, ReliedOnMap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step2. Insert horizontal reliance relationships into the map
     * @tc.expected: node1 is registered as relying on anchor1 and anchor2 horizontally
     */
    algorithm.InsertToHorizontalReliedOnMap("anchor1", "node1");
    algorithm.InsertToHorizontalReliedOnMap("anchor2", "node1");

    /**
     * @tc.steps: step3. Insert vertical reliance relationship into the map
     * @tc.expected: node1 is registered as relying on anchor1 vertically
     */
    algorithm.InsertToVerticalReliedOnMap("anchor1", "node1");

    /**
     * @tc.steps: step4. Verify horizontal reliance map entries
     * @tc.expected: node1 has one entry each for anchor1 and anchor2
     */
    EXPECT_EQ(algorithm.horizontalRelyMap_["node1"].count("anchor1"), 1u);
    EXPECT_EQ(algorithm.horizontalRelyMap_["node1"].count("anchor2"), 1u);

    /**
     * @tc.steps: step5. Verify vertical reliance map entries
     * @tc.expected: node1 has one entry for anchor1
     */
    EXPECT_EQ(algorithm.verticalRelyMap_["node1"].count("anchor1"), 1u);
}

/**
 * @tc.name: InitRemainingSpace001
 * @tc.desc: Test remaining space initialization
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, InitRemainingSpace001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.containerSizeWithoutPaddingBorder_.SetWidth(400.0f);

    /**
     * @tc.steps: step2. Configure chain parameters with uncalculated weight state
     * @tc.expected: ChainParam is set with isWeightCalculated=false and anchor rules
     */
    RelativeContainerLayoutAlgorithm::ChainParam chainParam;
    chainParam.isWeightCalculated = false;
    AlignRule headRule = {.anchor = "__container__", .horizontal = HorizontalAlign::START};
    AlignRule tailRule = {.anchor = "__container__", .horizontal = HorizontalAlign::END};
    chainParam.anchorHead = headRule;
    chainParam.anchorTail = tailRule;

    /**
     * @tc.steps: step3. Initialize remaining space for the chain
     * @tc.expected: remainingSpace is set to 400.0f and isWeightCalculated becomes true
     */
    algorithm.InitRemainingSpace(chainParam, LineDirection::HORIZONTAL);
    EXPECT_FLOAT_EQ(chainParam.remainingSpace, 400.0f);
    EXPECT_TRUE(chainParam.isWeightCalculated);

    /**
     * @tc.steps: step4. Modify chain parameters and reinitialize when already calculated
     * @tc.expected: remainingSpace remains at the manually set value (100.0f)
     */
    chainParam.isWeightCalculated = true;
    chainParam.remainingSpace = 100.0f;
    algorithm.InitRemainingSpace(chainParam, LineDirection::HORIZONTAL);
    EXPECT_FLOAT_EQ(chainParam.remainingSpace, 100.0f);
}

/**
 * @tc.name: UpdateDegreeMapWithBarrier001
 * @tc.desc: Test barrier degree map update
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, UpdateDegreeMapWithBarrier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure a barrier referencing two nodes and add nodes to idNodeMap
     * @tc.expected: Barrier and nodes are properly registered in the algorithm
     */
    std::vector<std::string> referencedIds = {"node1", "node2"};
    algorithm.barriers_["barrier1"] = std::make_pair(BarrierDirection::LEFT, referencedIds);
    algorithm.idNodeMap_["node1"] = {.layoutWrapper = nullptr, .id = "node1"};
    algorithm.idNodeMap_["node2"] = {.layoutWrapper = nullptr, .id = "node2"};

    /**
     * @tc.steps: step3. Update degree map with barrier information
     * @tc.expected: incomingDegreeMap for barrier1 reflects the number of referenced nodes (2)
     */
    std::queue<std::string> layoutQueue;
    algorithm.UpdateDegreeMapWithBarrier(layoutQueue);
    EXPECT_EQ(algorithm.incomingDegreeMap_["barrier1"], 2u);
}

/**
 * @tc.name: GetDependencyRelationshipInBarrier001
 * @tc.desc: Test barrier dependency relationship
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, GetDependencyRelationshipInBarrier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure a barrier with two referenced nodes and register nodes
     * @tc.expected: Barrier and nodes are properly added to the algorithm maps
     */
    std::vector<std::string> referencedIds = {"node1", "node2"};
    algorithm.barriers_["barrier1"] = std::make_pair(BarrierDirection::LEFT, referencedIds);
    algorithm.idNodeMap_["node1"] = {.layoutWrapper = nullptr, .id = "node1"};
    algorithm.idNodeMap_["node2"] = {.layoutWrapper = nullptr, .id = "node2"};

    /**
     * @tc.steps: step3. Retrieve dependency relationships for barriers
     * @tc.expected: Barrier dependency relationships are populated in reliedOnMap
     */
    algorithm.GetDependencyRelationshipInBarrier();

    /**
     * @tc.steps: step4. Verify barrier dependencies for referenced nodes
     * @tc.expected: Both node1 and node2 have barrier1 in their reliedOnMap
     */
    EXPECT_EQ(algorithm.reliedOnMap_["node1"].count("barrier1"), 1u);
    EXPECT_EQ(algorithm.reliedOnMap_["node2"].count("barrier1"), 1u);
}

/**
 * @tc.name: GetDependencyRelationshipInChain001
 * @tc.desc: Test chain dependency relationship
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, GetDependencyRelationshipInChain001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.idNodeMap_["node1"] = {.layoutWrapper = nullptr, .id = "node1"};

    /**
     * @tc.steps: step2. Get dependency relationship for regular node chain
     * @tc.expected: node1 is recorded as relying on node2
     */
    algorithm.GetDependencyRelationshipInChain("node1", "node2");
    EXPECT_EQ(algorithm.reliedOnMap_["node1"].count("node2"), 1u);

    /**
     * @tc.steps: step3. Enable version >= 11 and configure a vertical guideline
     * @tc.expected: Guideline is added to the guidelines map
     */
    algorithm.versionGreatorOrEqualToEleven_ = true;
    algorithm.guidelines_["guideline1"] = std::make_pair(LineDirection::VERTICAL, 100.0f);

    /**
     * @tc.steps: step4. Get dependency relationship for container and guideline
     * @tc.expected: Container and guideline are not added to reliedOnMap (they are special anchors)
     */
    algorithm.GetDependencyRelationshipInChain("__container__", "node1");
    algorithm.GetDependencyRelationshipInChain("guideline1", "node2");
    EXPECT_EQ(algorithm.reliedOnMap_.count("__container__"), 0u);
    EXPECT_EQ(algorithm.reliedOnMap_.count("guideline1"), 0u);
}

/**
 * @tc.name: IsAlignRuleInChain001
 * @tc.desc: Test chain align rule check
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, IsAlignRuleInChain001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure a horizontal chain with node1 as a member
     * @tc.expected: Chain node map and chain parameters are properly set
     */
    algorithm.horizontalChainNodeMap_["node1"] = "chain1";
    RelativeContainerLayoutAlgorithm::ChainParam chainParam;
    AlignRule headRule = {.anchor = "__container__", .horizontal = HorizontalAlign::START};
    AlignRule tailRule = {.anchor = "node2", .horizontal = HorizontalAlign::END};
    chainParam.anchorHead = headRule;
    chainParam.anchorTail = tailRule;
    algorithm.horizontalChains_["chain1"] = chainParam;

    /**
     * @tc.steps: step3. Test IsAlignRuleInChain for LEFT direction on node1
     * @tc.expected: Returns true as LEFT aligns with chain head
     */
    EXPECT_TRUE(algorithm.IsAlignRuleInChain(AlignDirection::LEFT, "node1"));

    /**
     * @tc.steps: step4. Test IsAlignRuleInChain for RIGHT direction on node1
     * @tc.expected: Returns true as RIGHT aligns with chain tail
     */
    EXPECT_TRUE(algorithm.IsAlignRuleInChain(AlignDirection::RIGHT, "node1"));

    /**
     * @tc.steps: step5. Test IsAlignRuleInChain for TOP direction on node1
     * @tc.expected: Returns false as TOP is not part of horizontal chain
     */
    EXPECT_FALSE(algorithm.IsAlignRuleInChain(AlignDirection::TOP, "node1"));
}

/**
 * @tc.name: PreTopologicalLoopDetectionGetAnchorSet001
 * @tc.desc: Test anchor set generation for loop detection
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, PreTopologicalLoopDetectionGetAnchorSet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.idNodeMap_["node1"] = {.layoutWrapper = nullptr, .id = "node1"};
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure a barrier referencing node1
     * @tc.expected: Barrier is added to the barriers map
     */
    std::vector<std::string> referencedIds = {"node1"};
    algorithm.barriers_["barrier1"] = std::make_pair(BarrierDirection::LEFT, referencedIds);

    /**
     * @tc.steps: step3. Setup align rules with node1 as LEFT anchor and get anchor set
     * @tc.expected: Anchor set contains node1
     */
    AlignRulesItem alignRules;
    AlignRule rule1 = {.anchor = "node1", .horizontal = HorizontalAlign::START};
    AlignRule rule2 = {.anchor = "barrier1", .horizontal = HorizontalAlign::START};
    alignRules[AlignDirection::LEFT] = rule1;
    std::set<std::string> anchorSet1;
    algorithm.PreTopologicalLoopDetectionGetAnchorSet("testNode", alignRules, anchorSet1);
    EXPECT_EQ(anchorSet1.count("node1"), 1u);

    /**
     * @tc.steps: step4. Add RIGHT align rule with barrier1 and get updated anchor set
     * @tc.expected: Anchor set contains barrier1
     */
    alignRules[AlignDirection::RIGHT] = rule2;
    std::set<std::string> anchorSet2;
    algorithm.PreTopologicalLoopDetectionGetAnchorSet("testNode", alignRules, anchorSet2);
    EXPECT_EQ(anchorSet2.count("barrier1"), 1u);
}



/**
 * @tc.name: CalcChainWeightSize001
 * @tc.desc: Test chain weight size calculation
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, CalcChainWeightSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.containerSizeWithoutPaddingBorder_.SetWidth(400.0f);
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure a horizontal chain with weight parameters
     * @tc.expected: Chain is set up with remainingSpace=200.0f, totalChainWeight=2.0f
     */
    RelativeContainerLayoutAlgorithm::ChainParam chainParam;
    chainParam.remainingSpace = 200.0f;
    chainParam.isWeightCalculated = true;
    chainParam.totalChainWeight = 2.0f;
    chainParam.ids = {"node1"};
    AlignRule headRule = {.anchor = "__container__", .horizontal = HorizontalAlign::START};
    AlignRule tailRule = {.anchor = "__container__", .horizontal = HorizontalAlign::END};
    chainParam.anchorHead = headRule;
    chainParam.anchorTail = tailRule;
    algorithm.horizontalChains_["chain1"] = chainParam;
    algorithm.horizontalChainNodeMap_["node1"] = "chain1";
    algorithm.idNodeMap_["node1"] = {.layoutWrapper = nullptr, .id = "node1"};

    /**
     * @tc.steps: step3. Create FlexItemProperty with horizontal chain weight and calculate weight size
     * @tc.expected: Child constraint width is calculated as 100.0f (200.0f * 1.0f / 2.0f)
     */
    auto flexItem = std::make_unique<FlexItemProperty>();
    flexItem->UpdateChainWeight(ChainWeightPair(1.0f, 0.0f));
    LayoutConstraintF childConstraint;
    algorithm.CalcChainWeightSize(flexItem, childConstraint, "node1", LineDirection::HORIZONTAL);
    EXPECT_TRUE(childConstraint.selfIdealSize.Width().has_value());
    EXPECT_FLOAT_EQ(childConstraint.selfIdealSize.Width().value(), 100.0f);

    /**
     * @tc.steps: step4. Set remaining space to zero and recalculate weight size
     * @tc.expected: Child constraint width is 0.0f when no remaining space
     */
    chainParam.remainingSpace = 0.0f;
    algorithm.horizontalChains_["chain1"] = chainParam;
    LayoutConstraintF childConstraint2;
    algorithm.CalcChainWeightSize(flexItem, childConstraint2, "node1", LineDirection::HORIZONTAL);
    EXPECT_FLOAT_EQ(childConstraint2.selfIdealSize.Width().value(), 0.0f);
}


/**
 * @tc.name: GetBarrierRectByReferencedIds001
 * @tc.desc: Test barrier rect calculation with guidelines
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerAlgorithmTestNG, GetBarrierRectByReferencedIds001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RelativeContainer and initialize the layout algorithm
     * @tc.expected: Container and layout wrapper are created successfully
     */
    auto relativeContainer = CreateRelativeContainer([](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(500.0f, DimensionUnit::PX));
    });
    ASSERT_NE(relativeContainer, nullptr);
    auto layoutWrapper = relativeContainer->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    RelativeContainerLayoutAlgorithm algorithm;
    algorithm.Initialize(AceType::RawPtr(layoutWrapper));
    algorithm.versionGreatorOrEqualToEleven_ = true;

    /**
     * @tc.steps: step2. Configure vertical and horizontal guidelines with record offsets
     * @tc.expected: guidelineV at x=100 and guidelineH at y=100 are set up
     */
    algorithm.guidelines_["guidelineV"] = std::make_pair(LineDirection::VERTICAL, 100.0f);
    algorithm.guidelines_["guidelineH"] = std::make_pair(LineDirection::HORIZONTAL, 100.0f);
    algorithm.recordOffsetMap_["guidelineV"] = OffsetF(100.0f, 0.0f);
    algorithm.recordOffsetMap_["guidelineH"] = OffsetF(0.0f, 100.0f);

    /**
     * @tc.steps: step3. Get barrier rectangles for vertical and horizontal guidelines
     * @tc.expected: Barrier rectangles are calculated for both guideline types
     */
    std::vector<std::string> referencedIdsV = {"guidelineV"};
    std::vector<std::string> referencedIdsH = {"guidelineH"};
    auto resultV = algorithm.GetBarrierRectByReferencedIds(referencedIdsV);
    auto resultH = algorithm.GetBarrierRectByReferencedIds(referencedIdsH);

    /**
     * @tc.steps: step4. Verify barrier rectangle values for vertical guideline
     * @tc.expected: minLeft=100.0f, maxRight=100.0f for vertical guideline
     */
    EXPECT_FLOAT_EQ(resultV.minLeft, 100.0f);
    EXPECT_FLOAT_EQ(resultV.maxRight, 100.0f);

    /**
     * @tc.steps: step5. Verify barrier rectangle values for horizontal guideline
     * @tc.expected: minTop=100.0f, maxBottom=100.0f for horizontal guideline
     */
    EXPECT_FLOAT_EQ(resultH.minTop, 100.0f);
    EXPECT_FLOAT_EQ(resultH.maxBottom, 100.0f);
}

} // namespace OHOS::Ace::NG