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

#include "test/unittest/core/layout/layout_property_test_ng.h"

#include "core/components_ng/property/position_property.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: UpdateUserDefinedIdealSize001
 * @tc.desc: Test UpdateUserDefinedIdealSize with width and height
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateUserDefinedIdealSize001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Call UpdateUserDefinedIdealSize with valid size.
     */
    layoutProperty->UpdateUserDefinedIdealSize(CALC_SIZE);

    /**
     * @tc.expected: calcLayoutConstraint should be created with selfIdealSize.
     */
    auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(calcLayoutConstraint, nullptr);
    auto& selfIdealSize = calcLayoutConstraint->selfIdealSize.value();
    ASSERT_TRUE(selfIdealSize.Width().has_value());
    ASSERT_TRUE(selfIdealSize.Height().has_value());
    EXPECT_EQ(selfIdealSize.Width().value(), CalcLength(WIDTH));
    EXPECT_EQ(selfIdealSize.Height().value(), CalcLength(HEIGHT));
}

/**
 * @tc.name: UpdateUserDefinedIdealSize002
 * @tc.desc: Test UpdateUserDefinedIdealSize with only width
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateUserDefinedIdealSize002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Call UpdateUserDefinedIdealSize with only width.
     */
    CalcSize calcSizeWidth(CalcLength(WIDTH), std::nullopt);
    layoutProperty->UpdateUserDefinedIdealSize(calcSizeWidth);

    auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(calcLayoutConstraint, nullptr);
    auto& selfIdealSize = calcLayoutConstraint->selfIdealSize.value();
    ASSERT_TRUE(selfIdealSize.Width().has_value());
    EXPECT_EQ(selfIdealSize.Width().value(), CalcLength(WIDTH));
    EXPECT_FALSE(selfIdealSize.Height().has_value());
}

/**
 * @tc.name: UpdateLayoutPolicyProperty001
 * @tc.desc: Test UpdateLayoutPolicyProperty with width
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateLayoutPolicyProperty001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Call UpdateLayoutPolicyProperty for width.
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);

    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    ASSERT_TRUE(layoutPolicy.has_value());
    auto widthPolicy = layoutPolicy.value().GetLayoutPolicy(true);
    ASSERT_TRUE(widthPolicy.has_value());
    EXPECT_EQ(widthPolicy.value(), LayoutCalPolicy::WRAP_CONTENT);
}

/**
 * @tc.name: UpdateLayoutPolicyProperty002
 * @tc.desc: Test UpdateLayoutPolicyProperty with height
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateLayoutPolicyProperty002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Call UpdateLayoutPolicyProperty for height.
     */
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);

    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    ASSERT_TRUE(layoutPolicy.has_value());
    auto heightPolicy = layoutPolicy.value().GetLayoutPolicy(false);
    ASSERT_TRUE(heightPolicy.has_value());
    EXPECT_EQ(heightPolicy.value(), LayoutCalPolicy::MATCH_PARENT);
}

/**
 * @tc.name: HasFixedWidth001
 * @tc.desc: Test HasFixedWidth with fixed width
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, HasFixedWidth001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Set fixed width.
     */
    CalcSize calcSizeFixedWidth(CalcLength(Dimension(100.0, DimensionUnit::PX)), std::nullopt);
    layoutProperty->UpdateUserDefinedIdealSize(calcSizeFixedWidth);

    /**
     * @tc.expected: HasFixedWidth should return true.
     */
    EXPECT_TRUE(layoutProperty->HasFixedWidth());
}

/**
 * @tc.name: HasFixedWidth002
 * @tc.desc: Test HasFixedWidth with percent width
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, HasFixedWidth002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Set percent width.
     */
    CalcSize calcSizePercent(CalcLength(Dimension(50.0, DimensionUnit::PERCENT)), std::nullopt);
    layoutProperty->UpdateUserDefinedIdealSize(calcSizePercent);

    /**
     * @tc.expected: HasFixedWidth with checkPercent=true should return false.
     */
    EXPECT_FALSE(layoutProperty->HasFixedWidth(true));
    EXPECT_TRUE(layoutProperty->HasFixedWidth(false));
}

/**
 * @tc.name: HasFixedHeight001
 * @tc.desc: Test HasFixedHeight with fixed height
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, HasFixedHeight001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Set fixed height.
     */
    CalcSize calcSizeFixedHeight(std::nullopt, CalcLength(Dimension(100.0, DimensionUnit::PX)));
    layoutProperty->UpdateUserDefinedIdealSize(calcSizeFixedHeight);

    /**
     * @tc.expected: HasFixedHeight should return true.
     */
    EXPECT_TRUE(layoutProperty->HasFixedHeight());
}

/**
 * @tc.name: UpdateAlignment001
 * @tc.desc: Test UpdateAlignment
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAlignment001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Update alignment with CENTER.
     */
    layoutProperty->UpdateAlignment(Alignment::CENTER);

    /**
     * @tc.expected: PositionProperty should be created with CENTER alignment.
     */
    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetPositionProperty()->GetAlignment(), Alignment::CENTER);

    /**
     * @tc.steps: step3. Update alignment with TOP_LEFT.
     */
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    EXPECT_EQ(layoutProperty->GetPositionProperty()->GetAlignment(), Alignment::TOP_LEFT);
}

/**
 * @tc.name: UpdateLayoutGravity001
 * @tc.desc: Test UpdateLayoutGravity
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateLayoutGravity001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Update layout gravity.
     */
    layoutProperty->UpdateLayoutGravity(Alignment::BOTTOM_RIGHT);

    /**
     * @tc.expected: PositionProperty should have layoutGravity set.
     */
    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetPositionProperty()->GetLayoutGravity(), Alignment::BOTTOM_RIGHT);
}

/**
 * @tc.name: UpdateLayoutWeight001
 * @tc.desc: Test UpdateLayoutWeight
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateLayoutWeight001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Update layout weight.
     */
    layoutProperty->UpdateLayoutWeight(2.0f);

    /**
     * @tc.expected: MagicItemProperty should have layoutWeight set.
     */
    auto& magicItemProperty = layoutProperty->GetMagicItemProperty();
    EXPECT_EQ(magicItemProperty.GetLayoutWeight(), 2.0f);
}

/**
 * @tc.name: GetNonAutoLayoutDirection001
 * @tc.desc: Test GetNonAutoLayoutDirection with AUTO
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, GetNonAutoLayoutDirection001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Set layout direction to LTR.
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);

    /**
     * @tc.expected: GetNonAutoLayoutDirection should return LTR.
     */
    auto result = layoutProperty->GetNonAutoLayoutDirection();
    EXPECT_EQ(result, TextDirection::LTR);
}

/**
 * @tc.name: GetNonAutoLayoutDirection002
 * @tc.desc: Test GetNonAutoLayoutDirection with RTL
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, GetNonAutoLayoutDirection002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Set layout direction to RTL.
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);

    /**
     * @tc.expected: GetNonAutoLayoutDirection should return RTL.
     */
    auto result = layoutProperty->GetNonAutoLayoutDirection();
    EXPECT_EQ(result, TextDirection::RTL);
}

/**
 * @tc.name: UpdateAlignSelf001
 * @tc.desc: Test UpdateAlignSelf
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateAlignSelf001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Update alignSelf.
     */
    layoutProperty->UpdateAlignSelf(FlexAlign::CENTER);

    /**
     * @tc.expected: FlexItemProperty should be created with alignSelf set.
     */
    ASSERT_NE(layoutProperty->GetFlexItemProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetFlexItemProperty()->GetAlignSelf(), FlexAlign::CENTER);
}

/**
 * @tc.name: UpdateBias001
 * @tc.desc: Test UpdateBias
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateBias001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Update bias.
     */
    BiasPair biasPair(0.3f, 0.7f);
    layoutProperty->UpdateBias(biasPair);

    /**
     * @tc.expected: Bias should be set in FlexItemProperty.
     */
    ASSERT_NE(layoutProperty->GetFlexItemProperty(), nullptr);
    auto bias = layoutProperty->GetFlexItemProperty()->GetBias();
    EXPECT_TRUE(bias.has_value());
    EXPECT_EQ(bias->first, 0.3f);
    EXPECT_EQ(bias->second, 0.7f);
}

/**
 * @tc.name: UpdateUserDefinedIdealSize003
 * @tc.desc: Test UpdateUserDefinedIdealSize with percent size
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateUserDefinedIdealSize003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Call UpdateUserDefinedIdealSize with percent size.
     */
    CalcSize calcSizePercent(
        CalcLength(Dimension(50.0, DimensionUnit::PERCENT)), CalcLength(Dimension(100.0, DimensionUnit::PERCENT)));
    layoutProperty->UpdateUserDefinedIdealSize(calcSizePercent);

    auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(calcLayoutConstraint, nullptr);
    auto& selfIdealSize = calcLayoutConstraint->selfIdealSize.value();
    ASSERT_TRUE(selfIdealSize.Width().has_value());
    ASSERT_TRUE(selfIdealSize.Height().has_value());
    EXPECT_EQ(selfIdealSize.Width().value(), CalcLength(Dimension(50.0, DimensionUnit::PERCENT)));
    EXPECT_EQ(selfIdealSize.Height().value(), CalcLength(Dimension(100.0, DimensionUnit::PERCENT)));
}

/**
 * @tc.name: UpdateLayoutConstraintWithPadding001
 * @tc.desc: Test UpdateLayoutConstraint with padding
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateLayoutConstraintWithPadding001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Update padding with different values for each edge.
     */
    PaddingProperty padding;
    padding.left = CalcLength(10.0, DimensionUnit::PX);
    padding.right = CalcLength(20.0, DimensionUnit::PX);
    padding.top = CalcLength(15.0, DimensionUnit::PX);
    padding.bottom = CalcLength(25.0, DimensionUnit::PX);
    layoutProperty->UpdatePadding(padding);

    /**
     * @tc.expected: Padding should be set correctly.
     */
    auto& resultPadding = layoutProperty->GetPaddingProperty();
    ASSERT_NE(resultPadding, nullptr);
    ASSERT_TRUE(resultPadding->left.has_value());
    ASSERT_TRUE(resultPadding->right.has_value());
    ASSERT_TRUE(resultPadding->top.has_value());
    ASSERT_TRUE(resultPadding->bottom.has_value());
    EXPECT_EQ(resultPadding->left.value(), CalcLength(10.0, DimensionUnit::PX));
    EXPECT_EQ(resultPadding->right.value(), CalcLength(20.0, DimensionUnit::PX));
    EXPECT_EQ(resultPadding->top.value(), CalcLength(15.0, DimensionUnit::PX));
    EXPECT_EQ(resultPadding->bottom.value(), CalcLength(25.0, DimensionUnit::PX));
}

/**
 * @tc.name: UpdateLayoutConstraintWithMargin001
 * @tc.desc: Test UpdateLayoutConstraint with margin
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, UpdateLayoutConstraintWithMargin001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Update margin with same value for all edges.
     */
    MarginProperty margin;
    margin.left = CalcLength(12.0, DimensionUnit::PX);
    margin.right = CalcLength(12.0, DimensionUnit::PX);
    margin.top = CalcLength(12.0, DimensionUnit::PX);
    margin.bottom = CalcLength(12.0, DimensionUnit::PX);
    layoutProperty->UpdateMargin(margin);

    /**
     * @tc.expected: Margin should be set correctly for all edges.
     */
    auto& resultMargin = layoutProperty->GetMarginProperty();
    ASSERT_NE(resultMargin, nullptr);
    ASSERT_TRUE(resultMargin->left.has_value());
    ASSERT_TRUE(resultMargin->right.has_value());
    ASSERT_TRUE(resultMargin->top.has_value());
    ASSERT_TRUE(resultMargin->bottom.has_value());
    EXPECT_EQ(resultMargin->left.value(), CalcLength(12.0, DimensionUnit::PX));
    EXPECT_EQ(resultMargin->right.value(), CalcLength(12.0, DimensionUnit::PX));
    EXPECT_EQ(resultMargin->top.value(), CalcLength(12.0, DimensionUnit::PX));
    EXPECT_EQ(resultMargin->bottom.value(), CalcLength(12.0, DimensionUnit::PX));
}

/**
 * @tc.name: ConstraintSizeCombination001
 * @tc.desc: Test constraint size with min and max combination
 * @tc.type: FUNC
 */
HWTEST_F(LayoutPropertyTestNg, ConstraintSizeCombination001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create a layoutProperty.
     */
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();

    /**
     * @tc.steps: step2. Set min and max constraint size using UpdateCalcMinSize and UpdateCalcMaxSize.
     */
    layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(100.0), CalcLength(200.0)));
    layoutProperty->UpdateCalcMaxSize(CalcSize(CalcLength(500.0), CalcLength(600.0)));

    /**
     * @tc.expected: Min and max constraints should be set correctly.
     */
    auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(calcLayoutConstraint, nullptr);
    const auto& minSize = calcLayoutConstraint->minSize;
    const auto& maxSize = calcLayoutConstraint->maxSize;
    ASSERT_TRUE(minSize.has_value());
    ASSERT_TRUE(maxSize.has_value());
    ASSERT_TRUE(minSize->Width().has_value());
    ASSERT_TRUE(minSize->Height().has_value());
    ASSERT_TRUE(maxSize->Width().has_value());
    ASSERT_TRUE(maxSize->Height().has_value());
    EXPECT_EQ(minSize->Width().value(), CalcLength(100.0));
    EXPECT_EQ(minSize->Height().value(), CalcLength(200.0));
    EXPECT_EQ(maxSize->Width().value(), CalcLength(500.0));
    EXPECT_EQ(maxSize->Height().value(), CalcLength(600.0));
}

} // namespace OHOS::Ace::NG