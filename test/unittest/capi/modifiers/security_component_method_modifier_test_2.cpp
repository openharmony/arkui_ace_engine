/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "security_component_method_modifier_test.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
using namespace TestConst::SecurityComponentMethod;

typedef std::pair<Ark_Length, std::string> MarginPaddingOneTestStep;
static const std::vector<MarginPaddingOneTestStep> LENGTH_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(2.45f), "2.45vp" },
    { Converter::ArkValue<Ark_Length>(-2.45f), "-2.45vp" },
    { Converter::ArkValue<Ark_Length>(5.0_px), "5.00px" },
    { Converter::ArkValue<Ark_Length>(-5.0_px), "-5.00px" },
    { Converter::ArkValue<Ark_Length>(22.35_px), "22.35px" },
    { Converter::ArkValue<Ark_Length>(-22.35_px), "-22.35px" },
    { Converter::ArkValue<Ark_Length>(7.0_vp), "7.00vp" },
    { Converter::ArkValue<Ark_Length>(-7.0_vp), "-7.00vp" },
    { Converter::ArkValue<Ark_Length>(1.65_vp), "1.65vp" },
    { Converter::ArkValue<Ark_Length>(-1.65_vp), "-1.65vp" },
    { Converter::ArkValue<Ark_Length>(65.0_fp), "65.00fp" },
    { Converter::ArkValue<Ark_Length>(-65.0_fp), "-65.00fp" },
    { Converter::ArkValue<Ark_Length>(4.3_fp), "4.30fp" },
    { Converter::ArkValue<Ark_Length>(-4.3_fp), "-4.30fp" },
    { Converter::ArkValue<Ark_Length>("12.00%"), "12.00%" },
    { Converter::ArkValue<Ark_Length>(FLOAT_RES_0_ID), "70.50px" },
};

using LengthMetrictsTestStep = std::pair<Ark_LengthMetrics, std::string>;
static const std::vector<LengthMetrictsTestStep> LENGTH_METRICS_ANY_TEST_PLAN = {
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 1.f), "1.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 0.f), "0.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, 2.45f), "2.45vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, -7.f), "-7.00vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_FP, -65.5f), "-65.50fp" },
};

/*
 * @tc.name: setOffsetTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
    auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
    EXPECT_EQ(xResult, ATTRIBUTE_OFFSET_X_DEFAULT_VALUE);
    auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
    EXPECT_EQ(yResult, ATTRIBUTE_OFFSET_Y_DEFAULT_VALUE);
}

/*
 * @tc.name: setOffsetTestValidPositionXValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidPositionXValues, TestSize.Level1)
{
    Ark_Position position;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        position.x = Converter::ArkValue<Opt_Length>(arkLength);
        position.y = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
        EXPECT_EQ(xResult, expected);
        auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
        EXPECT_EQ(yResult, "0.00px");
    }
}

/*
 * @tc.name: setOffsetTestValidPositionYValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidPositionYValues, TestSize.Level1)
{
    Ark_Position position;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        position.x = Converter::ArkValue<Opt_Length>(Ark_Empty());
        position.y = Converter::ArkValue<Opt_Length>(arkLength);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Position>(position);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto xResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_X_NAME);
        EXPECT_EQ(xResult, "0.00px");
        auto yResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_Y_NAME);
        EXPECT_EQ(yResult, expected);
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesLeftValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidEdgesLeftValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(arkLength);
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, expected);
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesTopValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidEdgesTopValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(arkLength);
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, expected);
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesRightValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidEdgesRightValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(arkLength);
        edges.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, expected);
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, "");
    }
}

/*
 * @tc.name: setOffsetTestValidEdgesBottomValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidEdgesBottomValues, TestSize.Level1)
{
    Ark_Edges edges;
    std::string strResult;
    for (const auto &[arkLength, expected]: LENGTH_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edges.bottom = Converter::ArkValue<Opt_Length>(arkLength);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges);
        modifier_->setOffset(node_, &value);
        strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        auto leftResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_LEFT_NAME);
        EXPECT_EQ(leftResult, "");
        auto topResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_TOP_NAME);
        EXPECT_EQ(topResult, "");
        auto rightResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_RIGHT_NAME);
        EXPECT_EQ(rightResult, "");
        auto bottomResult = GetAttrValue<std::string>(strResult, ATTRIBUTE_OFFSET_BOTTOM_NAME);
        EXPECT_EQ(bottomResult, expected);
    }
}

/*
 * @tc.name: setOffsetTestValidLocalizedEdgesStartValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidLocalizedEdgesStartValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.start = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), defaultValue);
    }
}

/*
 * @tc.name: setOffsetTestValidLocalizedEdgesEndValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidLocalizedEdgesEndValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.end = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), defaultValue);
    }
}

/*
 * @tc.name: setOffsetTestValidLocalizedEdgesTopValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidLocalizedEdgesTopValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.top = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), expected);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), defaultValue);
    }
}

/*
 * @tc.name: setOffsetTestValidLocalizedEdgesBottomValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setOffsetTestValidLocalizedEdgesBottomValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.bottom = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Ark_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
        modifier_->setOffset(node_, &value);
        auto strResult = GetStringAttribute(node_, ATTRIBUTE_OFFSET_NAME);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_LEFT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_TOP_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_RIGHT_NAME), defaultValue);
        EXPECT_EQ(GetAttrValue<std::string>(strResult, ATTRIBUTE_BOTTOM_NAME), expected);
    }
}

/*
 * @tc.name: alignTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, alignTestValidValues, TestSize.Level1)
{
    std::vector<std::tuple<std::string, Ark_Alignment, Alignment>> testFixtureEnumAlignmentValidValues = {
        { "ARK_ALIGNMENT_TOP_START", ARK_ALIGNMENT_TOP_START, Alignment::TOP_LEFT },
        { "ARK_ALIGNMENT_TOP", ARK_ALIGNMENT_TOP, Alignment::TOP_CENTER },
        { "ARK_ALIGNMENT_TOP_END", ARK_ALIGNMENT_TOP_END, Alignment::TOP_RIGHT },
        { "ARK_ALIGNMENT_START", ARK_ALIGNMENT_START, Alignment::CENTER_LEFT },
        { "ARK_ALIGNMENT_CENTER", ARK_ALIGNMENT_CENTER, Alignment::CENTER },
        { "ARK_ALIGNMENT_END", ARK_ALIGNMENT_END, Alignment::CENTER_RIGHT },
        { "ARK_ALIGNMENT_BOTTOM_START", ARK_ALIGNMENT_BOTTOM_START, Alignment::BOTTOM_LEFT },
        { "ARK_ALIGNMENT_BOTTOM", ARK_ALIGNMENT_BOTTOM, Alignment::BOTTOM_CENTER },
        { "ARK_ALIGNMENT_BOTTOM_END", ARK_ALIGNMENT_BOTTOM_END, Alignment::BOTTOM_RIGHT },
    };

    auto checkValue = [this](const std::string& input, const Ark_Alignment& value,
        const Alignment& expected)
    {
        modifier_->setAlign(node_, value);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        ASSERT_TRUE(layoutProperty->HasAlignment()) <<
            "Input value is: " << input << ", method: setAlign";
        EXPECT_EQ(layoutProperty->GetAlignmentValue(), expected) <<
            "Input value is: " << input << ", method: setAlign";
    };

    for (const auto &[input, value, expected]: testFixtureEnumAlignmentValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: alignTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, alignTestInvalidValues, TestSize.Level1)
{
    const auto initialValue = ARK_ALIGNMENT_TOP_START;

    auto checkValue = [this](const std::string& input, const Ark_Alignment& value)
    {
        modifier_->setAlign(node_, initialValue);
        modifier_->setAlign(node_, value);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        ASSERT_FALSE(layoutProperty->HasAlignment()) <<
            "Input value is: " << input << ", method: setAlign";
    };

    for (const auto &[input, value]: Fixtures::testFixtureEnumAlignmentInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setMaxFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxFontScaleTestValidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMaxFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_Resource& value) {
        Ark_Union_Number_Resource inputValueMaxFontScale = initValueMaxFontScale;

        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto maxFontScale = layoutProperty->GetMaxFontScale();
        ASSERT_TRUE(maxFontScale) << "Passed value is: " << input;
        auto resultStr = std::to_string(maxFontScale.value());
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMaxFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureMaxFontScaleResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setMaxFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxFontScaleTestInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMaxFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const Ark_Union_Number_Resource& value) {
        Ark_Union_Number_Resource inputValueMaxFontScale = initValueMaxFontScale;

        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        inputValueMaxFontScale = value;
        modifier_->setMaxFontScale(node_, &inputValueMaxFontScale);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasMaxFontScale()) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMinFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMinFontScaleTestValidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMinFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_Resource& value) {
        Ark_Union_Number_Resource inputValueMinFontScale = initValueMinFontScale;

        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto minFontScale = layoutProperty->GetMinFontScale();
        ASSERT_TRUE(minFontScale) << "Passed value is: " << input;
        auto resultStr = std::to_string(minFontScale.value());
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureMinFontScaleNumValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureMinFontScaleResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setMinFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMinFontScaleTestInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale = ArkUnion<Ark_Union_Number_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureMinFontScaleNumValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const Ark_Union_Number_Resource& value) {
        Ark_Union_Number_Resource inputValueMinFontScale = initValueMinFontScale;

        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        inputValueMinFontScale = value;
        modifier_->setMinFontScale(node_, &inputValueMinFontScale);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasMinFontScale()) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMaxLinesTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxLinesTestValidValues, TestSize.Level1)
{
    Ark_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueMaxLines](
                          const std::string& input, const std::string& expectedStr, const Ark_Number& value) {
        Ark_Number inputValueMaxLines = initValueMaxLines;

        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto maxLines = layoutProperty->GetMaxLines();
        ASSERT_TRUE(maxLines) << "Passed value is: " << input;
        auto resultStr = std::to_string(maxLines.value());
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberNonNegIntFloorValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setMaxLinesTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxLinesTestInvalidValues, TestSize.Level1)
{
    Ark_Number initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(Fixtures::testFixtureNumberNonNegIntFloorValidValues[0]);

    auto checkValue = [this, &initValueMaxLines](const std::string& input, const Ark_Number& value) {
        Ark_Number inputValueMaxLines = initValueMaxLines;

        modifier_->setMaxLines(node_, &inputValueMaxLines);
        inputValueMaxLines = value;
        modifier_->setMaxLines(node_, &inputValueMaxLines);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        ASSERT_FALSE(layoutProperty->HasMaxLines()) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value] : Fixtures::testFixtureNumberNonNegIntFloorInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setMinFontSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMinFontSizeTestValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMinFontSize = initValueMinFontSize;

        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto minFontSize = layoutProperty->GetAdaptMinFontSize();
        ASSERT_TRUE(minFontSize) << "Passed value is: " << input;
        auto resultStr = minFontSize.value().ToString();
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMinFontSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMinFontSizeTestInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMinFontSize = initValueMinFontSize;

        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        inputValueMinFontSize = value;
        modifier_->setMinFontSize(node_, &inputValueMinFontSize);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasAdaptMinFontSize()) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMaxFontSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxFontSizeTestValidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto maxFontSize = layoutProperty->GetAdaptMaxFontSize();
        ASSERT_TRUE(maxFontSize) << "Passed value is: " << input;
        auto resultStr = maxFontSize.value().ToString();
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMaxFontSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxFontSizeTestInvalidValues, TestSize.Level1)
{
    Ark_Union_Number_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(
        std::get<1>(Fixtures::testFixtureDimensionsNumNonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](
                          const std::string& input, const Ark_Union_Number_String_Resource& value) {
        Ark_Union_Number_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        inputValueMaxFontSize = value;
        modifier_->setMaxFontSize(node_, &inputValueMaxFontSize);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasAdaptMaxFontSize()) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value] : Fixtures::testFixtureDimensionsNumNonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_Number_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_Number_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setHeightAdaptivePolicyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setHeightAdaptivePolicyTestValidValues, TestSize.Level1)
{
    Ark_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]);

    auto checkValue = [this, &initValueHeightAdaptivePolicy](const std::string& input, const std::string& expectedStr,
                          const Ark_TextHeightAdaptivePolicy& value) {
        Ark_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto heightAdaptivePolicy = layoutProperty->GetHeightAdaptivePolicy();
        ASSERT_TRUE(heightAdaptivePolicy) << "Passed value is: " << input;
        auto resultStr = V2::ConvertWrapTextHeightAdaptivePolicyToString(heightAdaptivePolicy.value());
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues) {
        checkValue(input, expected, value);
    }
}

/*
 * @tc.name: setHeightAdaptivePolicyTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setHeightAdaptivePolicyTestInvalidValues, TestSize.Level1)
{
    Ark_TextHeightAdaptivePolicy initValueHeightAdaptivePolicy;

    // Initial setup
    initValueHeightAdaptivePolicy = std::get<1>(Fixtures::testFixtureEnumTextHeightAdaptivePolicyValidValues[0]);

    auto checkValue = [this, &initValueHeightAdaptivePolicy](
                          const std::string& input, const Ark_TextHeightAdaptivePolicy& value) {
        Ark_TextHeightAdaptivePolicy inputValueHeightAdaptivePolicy = initValueHeightAdaptivePolicy;

        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        inputValueHeightAdaptivePolicy = value;
        modifier_->setHeightAdaptivePolicy(node_, inputValueHeightAdaptivePolicy);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasHeightAdaptivePolicy()) <<
            "Input value is: " << input << ", method: setHeightAdaptivePolicy, attribute: heightAdaptivePolicy";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumTextHeightAdaptivePolicyInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: ChainModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, ChainModeTest, TestSize.Level1)
{
    Ark_Axis direction = Ark_Axis::ARK_AXIS_HORIZONTAL;
    Ark_ChainStyle style = Ark_ChainStyle::ARK_CHAIN_STYLE_SPREAD_INSIDE;
    modifier_->setChainMode(node_, direction, style);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(layoutProperty->GetFlexItemProperty(), nullptr);

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());

    auto storedChainMode = layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD_INSIDE, storedChainMode.style.value());

    modifier_->setChainMode(node_, direction, Ark_ChainStyle::ARK_CHAIN_STYLE_SPREAD);

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());

    storedChainMode = layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD, storedChainMode.style.value());

    direction = Ark_Axis::ARK_AXIS_VERTICAL;
    style = Ark_ChainStyle::ARK_CHAIN_STYLE_PACKED;
    modifier_->setChainMode(node_, direction, style);

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    EXPECT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());

    storedChainMode = layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::VERTICAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::PACKED, storedChainMode.style.value());

    storedChainMode = layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD, storedChainMode.style.value());
}

/*
 * @tc.name: ChainModeImpl_SetBadDirectionValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, ChainModeImpl_SetBadDirectionValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_EQ(layoutProperty->GetFlexItemProperty(), nullptr);

    Ark_Axis direction = static_cast<Ark_Axis>(INT_MAX);
    Ark_ChainStyle style = Ark_ChainStyle::ARK_CHAIN_STYLE_SPREAD_INSIDE;
    modifier_->setChainMode(node_, direction, style);
    // empty direction optional creates both ChainStyle components but sets the style part of the VerticalChainStyle
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().direction.has_value());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD_INSIDE,
        layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().style.value());

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.has_value());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().style.has_value());
}

/*
 * @tc.name: ChainModeImpl_SetBadStyleValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, ChainModeImpl_SetBadStyleValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_EQ(layoutProperty->GetFlexItemProperty(), nullptr);

    Ark_Axis direction = Ark_Axis::ARK_AXIS_HORIZONTAL;
    Ark_ChainStyle style = static_cast<Ark_ChainStyle>(INT_MIN);
    modifier_->setChainMode(node_, direction, style);

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL,
        layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.value());

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().style.has_value());
}

/*
 * @tc.name: ChainModeImpl_SetBadBothValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, ChainModeImpl_SetBadBothValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_EQ(layoutProperty->GetFlexItemProperty(), nullptr);

    Ark_Axis direction = static_cast<Ark_Axis>(INT_MAX);
    Ark_ChainStyle style = static_cast<Ark_ChainStyle>(INT_MIN);
    modifier_->setChainMode(node_, direction, style);

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().direction.has_value());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().style.has_value());

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.has_value());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().style.has_value());
}

/*
 * @tc.name: setBorderRadius1TestBorderRadiusBorderRadiusesTopLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadius1TestBorderRadiusBorderRadiusesTopLeftValidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).topLeft = value;
        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_TRUE(borderRadius->radiusTopLeft) << "Passed value is: " << input;
        EXPECT_EQ(borderRadius->radiusTopLeft->ToString(), expectedStr) <<
            "Input value is: " << input
            << ", method: setBorderRadius1, attribute: borderRadius.BorderRadiuses.topLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setBorderRadius1TestBorderRadiusBorderRadiusesTopLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadius1TestBorderRadiusBorderRadiusesTopLeftInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](const std::string& input, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).topLeft = value;
        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_FALSE(borderRadius->radiusTopLeft) <<
            "Input value is: " << input
            << ", method: setBorderRadius1, attribute: borderRadius.BorderRadiuses.topLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBorderRadius1TestBorderRadiusBorderRadiusesTopRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadius1TestBorderRadiusBorderRadiusesTopRightValidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).topRight = value;
        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_TRUE(borderRadius->radiusTopRight) << "Passed value is: " << input;
        EXPECT_EQ(borderRadius->radiusTopRight->ToString(), expectedStr) <<
            "Input value is: " << input
            << ", method: setBorderRadius1, attribute: borderRadius.BorderRadiuses.topRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setBorderRadius1TestBorderRadiusBorderRadiusesTopRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadius1TestBorderRadiusBorderRadiusesTopRightInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](const std::string& input, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).topRight = value;
        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_FALSE(borderRadius->radiusTopRight) <<
            "Input value is: " << input
            << ", method: setBorderRadius1, attribute: borderRadius.BorderRadiuses.topRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBorderRadius1TestBorderRadiusBorderRadiusesBottomLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadius1TestBorderRadiusBorderRadiusesBottomLeftValidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).bottomLeft = value;
        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_TRUE(borderRadius->radiusBottomLeft) << "Passed value is: " << input;
        EXPECT_EQ(borderRadius->radiusBottomLeft->ToString(), expectedStr) <<
            "Input value is: " << input
            << ", method: setBorderRadius1, attribute: borderRadius.BorderRadiuses.bottomLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setBorderRadius1TestBorderRadiusBorderRadiusesBottomLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadius1TestBorderRadiusBorderRadiusesBottomLeftInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](const std::string& input, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).bottomLeft = value;
        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_FALSE(borderRadius->radiusBottomLeft) <<
            "Input value is: " << input
            << ", method: setBorderRadius1, attribute: borderRadius.BorderRadiuses.bottomLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}

/*
 * @tc.name: setBorderRadius1TestBorderRadiusBorderRadiusesBottomRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadius1TestBorderRadiusBorderRadiusesBottomRightValidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).bottomRight = value;
        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_TRUE(borderRadius->radiusBottomRight);
        EXPECT_EQ(borderRadius->radiusBottomRight->ToString(), expectedStr) <<
            "Input value is: " << input
            << ", method: setBorderRadius1, attribute: borderRadius.BorderRadiuses.bottomRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkValue<Opt_Length>(value));
    }
}

/*
 * @tc.name: setBorderRadius1TestBorderRadiusBorderRadiusesBottomRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadius1TestBorderRadiusBorderRadiusesBottomRightInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkValue<Opt_Length>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](const std::string& input, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).bottomRight = value;
        modifier_->setBorderRadius1(node_, &inputValueBorderRadius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_FALSE(borderRadius->radiusBottomRight) <<
            "Input value is: " << input
            << ", method: setBorderRadius1, attribute: borderRadius.BorderRadiuses.bottomRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkValue<Opt_Length>(value));
    }
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Length>());
}
} // namespace OHOS::Ace::NG
