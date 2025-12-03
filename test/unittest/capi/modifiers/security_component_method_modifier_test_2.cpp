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

ConvContext ctx;

static const std::vector<std::pair<Ark_Dimension, std::string>> DIMENSION_TEST_PLAN = {
    { Converter::ArkUnion<Ark_Dimension, Ark_Number>(2.45f, &ctx), "2.45vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_Number>(-2.45f, &ctx), "-2.45vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("5.0px", &ctx), "5.00px" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-5.0px", &ctx), "-5.00px" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("22.35px", &ctx), "22.35px" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-22.35px", &ctx), "-22.35px" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("7.0vp", &ctx), "7.00vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-7.0vp", &ctx), "-7.00vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("1.65vp", &ctx), "1.65vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-1.65vp", &ctx), "-1.65vp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("65.0fp", &ctx), "65.00fp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-65.0fp", &ctx), "-65.00fp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("4.3fp", &ctx), "4.30fp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("-4.3fp", &ctx), "-4.30fp" },
    { Converter::ArkUnion<Ark_Dimension, Ark_String>("12.00%", &ctx), "12.00%" },
    { Converter::ArkUnion<Ark_Dimension, Ark_Resource>(FLOAT_RES_0, &ctx), "70.50px" },
};

static const std::vector<std::pair<Ark_Length, std::string>> LENGTH_TEST_PLAN = {
    { Converter::ArkUnion<Ark_Length, Ark_Float64>(2.45f, &ctx), "2.45vp" },
    { Converter::ArkUnion<Ark_Length, Ark_Float64>(-2.45f, &ctx), "-2.45vp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("5.0px", &ctx), "5.00px" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("-5.0px", &ctx), "-5.00px" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("22.35px", &ctx), "22.35px" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("-22.35px", &ctx), "-22.35px" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("7.0vp", &ctx), "7.00vp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("-7.0vp", &ctx), "-7.00vp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("1.65vp", &ctx), "1.65vp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("-1.65vp", &ctx), "-1.65vp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("65.0fp", &ctx), "65.00fp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("-65.0fp", &ctx), "-65.00fp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("4.3fp", &ctx), "4.30fp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("-4.3fp", &ctx), "-4.30fp" },
    { Converter::ArkUnion<Ark_Length, Ark_String>("12.00%", &ctx), "12.00%" },
    { Converter::ArkUnion<Ark_Length, Ark_Resource>(FLOAT_RES_0, &ctx), "70.50px" },
};

using LengthMetrictsTestStep = std::pair<Ark_LengthMetrics, std::string>;
static const std::vector<LengthMetrictsTestStep> LENGTH_METRICS_ANY_TEST_PLAN = {
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 1.f), "1.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_PX, 0.f), "0.00px" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, 2.45f), "2.45vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_VP, -7.f), "-7.00vp" },
    { Converter::ArkCreate<Ark_LengthMetrics>(ARK_LENGTH_UNIT_FP, -65.5f), "-65.50fp" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureMaxFontScaleFloat64ValidValues = {
    { "1", Converter::ArkValue<Ark_Float64>(1), "1.000000" },
    { "2.5", Converter::ArkValue<Ark_Float64>(2.5), "2.500000" },
    { "100", Converter::ArkValue<Ark_Float64>(100), "100.000000" },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureMinFontScaleFloat64ValidValues = {
    { "0.1", Converter::ArkValue<Ark_Float64>(0.1), "0.100000" },
    { "0.89", Converter::ArkValue<Ark_Float64>(0.89), "0.890000" },
    { "1", Converter::ArkValue<Ark_Float64>(1), "1.000000" },
};

std::vector<std::tuple<std::string, Ark_Int32, std::string>> testFixtureMaxLinesValidValues = {
    { "100", Converter::ArkValue<Ark_Int32>(100), "100" },
    { "0", Converter::ArkValue<Ark_Int32>(0), "0" },
    { "1", Converter::ArkValue<Ark_Int32>(1), "1" },
};

std::vector<std::tuple<std::string, Ark_Int32>> testFixtureMaxLinesInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Int32>(-1) },
    { "-100", Converter::ArkValue<Ark_Int32>(-100) },
};

std::vector<std::tuple<std::string, Ark_Float64, std::string>> testFixtureFloat64NonNegValidValues = {
    { "123", Converter::ArkValue<Ark_Float64>(123), "123.00vp" },
    { "0", Converter::ArkValue<Ark_Float64>(0), "0.00vp" },
    { "1.23", Converter::ArkValue<Ark_Float64>(1.23), "1.23vp" },
};

std::vector<std::tuple<std::string, Ark_Float64>> testFixtureFloat64NonNegInvalidValues = {
    { "-1", Converter::ArkValue<Ark_Float64>(-1) },
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
        position.x = Converter::ArkValue<Opt_Length>(arkLength, &ctx);
        position.y = Converter::ArkUnion<Opt_Length, Ark_Empty>(nullptr);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Position>(position, &ctx);
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
        position.x = Converter::ArkUnion<Opt_Length, Ark_Empty>(nullptr);
        position.y = Converter::ArkValue<Opt_Length>(arkLength, &ctx);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Position>(position, &ctx);
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
    for (const auto &[arkValue, expected]: DIMENSION_TEST_PLAN) {
        edges.left = Converter::ArkValue<Opt_Dimension>(arkValue, &ctx);
        edges.top = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.right = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.bottom = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges, &ctx);
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
    for (const auto &[arkValue, expected]: DIMENSION_TEST_PLAN) {
        edges.left = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.top = Converter::ArkValue<Opt_Dimension>(arkValue, &ctx);
        edges.right = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.bottom = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges, &ctx);
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
    for (const auto &[arkValue, expected]: DIMENSION_TEST_PLAN) {
        edges.left = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.top = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.right = Converter::ArkValue<Opt_Dimension>(arkValue, &ctx);
        edges.bottom = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges, &ctx);
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
    for (const auto &[arkValue, expected]: DIMENSION_TEST_PLAN) {
        edges.left = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.top = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.right = Converter::ArkUnion<Opt_Dimension, Ark_Empty>(nullptr);
        edges.bottom = Converter::ArkValue<Opt_Dimension>(arkValue, &ctx);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_Edges>(edges, &ctx);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setOffsetTestValidLocalizedEdgesStartValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.start = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setOffsetTestValidLocalizedEdgesEndValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.end = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setOffsetTestValidLocalizedEdgesTopValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.top = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
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
HWTEST_F(SecurityComponentMethodModifierTest, DISABLED_setOffsetTestValidLocalizedEdgesBottomValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOffset, nullptr);

    const std::string defaultValue{};

    auto lenMetUndef = Converter::ArkValue<Opt_LengthMetrics>();
    Ark_LocalizedEdges inputValue { lenMetUndef, lenMetUndef, lenMetUndef, lenMetUndef };
    for (const auto &[lenMetrics, expected]: LENGTH_METRICS_ANY_TEST_PLAN) {
        inputValue.bottom = Converter::ArkValue<Opt_LengthMetrics>(lenMetrics);
        auto value = Converter::ArkUnion<Opt_Union_Position_Edges_LocalizedEdges, Ark_LocalizedEdges>(inputValue);
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
        auto convValue = Converter::ArkValue<Opt_Alignment>(value);
        modifier_->setAlign(node_, &convValue);
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
    const auto initialValue = Converter::ArkValue<Opt_Alignment>(ARK_ALIGNMENT_TOP_START);

    std::vector<std::tuple<std::string, Opt_Alignment>> testFixtureEnumAlignmentInvalidValues = {
        {"invalid", Converter::ArkValue<Opt_Alignment>(INVALID_ENUM_VAL<Ark_Alignment>)},
        {"undefined", Converter::ArkValue<Opt_Alignment>()},
    };

    auto checkValue = [initialValue, this](const std::string& input, const Opt_Alignment& value)
    {
        modifier_->setAlign(node_, &initialValue);
        modifier_->setAlign(node_, &value);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        ASSERT_FALSE(layoutProperty->HasAlignment()) <<
            "Input value is: " << input << ", method: setAlign";
    };

    for (const auto &[input, value]: testFixtureEnumAlignmentInvalidValues) {
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
    Ark_Union_F64_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale = ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(
        std::get<1>(testFixtureMaxFontScaleFloat64ValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_F64_Resource& value) {
        Ark_Union_F64_Resource inputValueMaxFontScale = initValueMaxFontScale;

        inputValueMaxFontScale = value;
        auto convValue = ArkValue<Opt_Union_F64_Resource>(inputValueMaxFontScale);
        modifier_->setMaxFontScale(node_, &convValue);
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

    for (auto& [input, value, expected] : testFixtureMaxFontScaleFloat64ValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureMaxFontScaleResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setMaxFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxFontScaleTestInvalidValues, TestSize.Level1)
{
    Ark_Union_F64_Resource initValueMaxFontScale;

    // Initial setup
    initValueMaxFontScale = ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(
        std::get<1>(testFixtureMaxFontScaleFloat64ValidValues[0]));

    auto checkValue = [this, &initValueMaxFontScale](const std::string& input, const Ark_Union_F64_Resource& value) {
        Ark_Union_F64_Resource inputValueMaxFontScale = initValueMaxFontScale;
        auto convValue = ArkValue<Opt_Union_F64_Resource>(inputValueMaxFontScale);
        modifier_->setMaxFontScale(node_, &convValue);
        inputValueMaxFontScale = value;
        convValue = ArkValue<Opt_Union_F64_Resource>(inputValueMaxFontScale);
        modifier_->setMaxFontScale(node_, &convValue);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasMaxFontScale()) <<
            "Input value is: " << input << ", method: setMaxFontScale, attribute: maxFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_F64_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMinFontScaleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMinFontScaleTestValidValues, TestSize.Level1)
{
    Ark_Union_F64_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale = ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(
        std::get<1>(testFixtureMinFontScaleFloat64ValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_F64_Resource& value) {
        Ark_Union_F64_Resource inputValueMinFontScale = initValueMinFontScale;

        inputValueMinFontScale = value;
        auto convValue = ArkValue<Opt_Union_F64_Resource>(inputValueMinFontScale);
        modifier_->setMinFontScale(node_, &convValue);
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

    for (auto& [input, value, expected] : testFixtureMinFontScaleFloat64ValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureMinFontScaleResValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_Resource, Ark_Resource>(value));
    }
}

/*
 * @tc.name: setMinFontScaleTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMinFontScaleTestInvalidValues, TestSize.Level1)
{
    Ark_Union_F64_Resource initValueMinFontScale;

    // Initial setup
    initValueMinFontScale = ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(
        std::get<1>(testFixtureMinFontScaleFloat64ValidValues[0]));

    auto checkValue = [this, &initValueMinFontScale](const std::string& input, const Ark_Union_F64_Resource& value) {
        Ark_Union_F64_Resource inputValueMinFontScale = initValueMinFontScale;
        auto convValue = ArkValue<Opt_Union_F64_Resource>(inputValueMinFontScale);
        modifier_->setMinFontScale(node_, &convValue);
        inputValueMinFontScale = value;
        convValue = ArkValue<Opt_Union_F64_Resource>(inputValueMinFontScale);
        modifier_->setMinFontScale(node_, &convValue);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasMinFontScale()) <<
            "Input value is: " << input << ", method: setMinFontScale, attribute: minFontScale";
    };

    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_F64_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMaxLinesTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxLinesTestValidValues, TestSize.Level1)
{
    Ark_Int32 initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(testFixtureMaxLinesValidValues[0]);

    auto checkValue = [this, &initValueMaxLines](
                          const std::string& input, const std::string& expectedStr, const Ark_Int32& value) {
        Ark_Int32 inputValueMaxLines = initValueMaxLines;

        inputValueMaxLines = value;
        auto convValue = ArkUnion<Opt_Union_I32_Resource, Ark_Int32>(inputValueMaxLines);
        modifier_->setMaxLines(node_, &convValue);
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

    for (auto& [input, value, expected] : testFixtureMaxLinesValidValues) {
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
    Ark_Int32 initValueMaxLines;

    // Initial setup
    initValueMaxLines = std::get<1>(testFixtureMaxLinesValidValues[0]);

    auto checkValue = [this, &initValueMaxLines](const std::string& input, const Ark_Int32& value) {
        Ark_Int32 inputValueMaxLines = initValueMaxLines;
        auto convValue = ArkUnion<Opt_Union_I32_Resource, Ark_Int32>(inputValueMaxLines);
        modifier_->setMaxLines(node_, &convValue);
        inputValueMaxLines = value;
        convValue = ArkUnion<Opt_Union_I32_Resource, Ark_Int32>(inputValueMaxLines);
        modifier_->setMaxLines(node_, &convValue);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        ASSERT_FALSE(layoutProperty->HasMaxLines()) <<
            "Input value is: " << input << ", method: setMaxLines, attribute: maxLines";
    };

    for (auto& [input, value] : testFixtureMaxLinesInvalidValues) {
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
    Ark_Union_F64_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(
        std::get<1>(testFixtureFloat64NonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_F64_String_Resource& value) {
        Ark_Union_F64_String_Resource inputValueMinFontSize = initValueMinFontSize;

        inputValueMinFontSize = value;
        auto convValue = ArkValue<Opt_Union_F64_String_Resource>(inputValueMinFontSize);
        modifier_->setMinFontSize(node_, &convValue);
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

    for (auto& [input, value, expected] : testFixtureFloat64NonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMinFontSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMinFontSizeTestInvalidValues, TestSize.Level1)
{
    Ark_Union_F64_String_Resource initValueMinFontSize;

    // Initial setup
    initValueMinFontSize = ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(
        std::get<1>(testFixtureFloat64NonNegValidValues[0]));

    auto checkValue = [this, &initValueMinFontSize](
                          const std::string& input, const Ark_Union_F64_String_Resource& value) {
        Ark_Union_F64_String_Resource inputValueMinFontSize = initValueMinFontSize;
        auto convValue = ArkValue<Opt_Union_F64_String_Resource>(inputValueMinFontSize);
        modifier_->setMinFontSize(node_, &convValue);
        inputValueMinFontSize = value;
        convValue = ArkValue<Opt_Union_F64_String_Resource>(inputValueMinFontSize);
        modifier_->setMinFontSize(node_, &convValue);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasAdaptMinFontSize()) <<
            "Input value is: " << input << ", method: setMinFontSize, attribute: minFontSize";
    };

    for (auto& [input, value] : testFixtureFloat64NonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_F64_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_F64_String_Resource, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setMaxFontSizeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxFontSizeTestValidValues, TestSize.Level1)
{
    Ark_Union_F64_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(
        std::get<1>(testFixtureFloat64NonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_F64_String_Resource& value) {
        Ark_Union_F64_String_Resource inputValueMaxFontSize = initValueMaxFontSize;

        inputValueMaxFontSize = value;
        auto convValue = ArkValue<Opt_Union_F64_String_Resource>(inputValueMaxFontSize);
        modifier_->setMaxFontSize(node_, &convValue);
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

    for (auto& [input, value, expected] : testFixtureFloat64NonNegValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsResNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_String_Resource, Ark_Resource>(value));
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(value));
    }
}

/*
 * @tc.name: setMaxFontSizeTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setMaxFontSizeTestInvalidValues, TestSize.Level1)
{
    Ark_Union_F64_String_Resource initValueMaxFontSize;

    // Initial setup
    initValueMaxFontSize = ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(
        std::get<1>(testFixtureFloat64NonNegValidValues[0]));

    auto checkValue = [this, &initValueMaxFontSize](
                          const std::string& input, const Ark_Union_F64_String_Resource& value) {
        Ark_Union_F64_String_Resource inputValueMaxFontSize = initValueMaxFontSize;
        auto convValue = ArkValue<Opt_Union_F64_String_Resource>(inputValueMaxFontSize);
        modifier_->setMaxFontSize(node_, &convValue);
        inputValueMaxFontSize = value;
        convValue = ArkValue<Opt_Union_F64_String_Resource>(inputValueMaxFontSize);
        modifier_->setMaxFontSize(node_, &convValue);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        EXPECT_FALSE(layoutProperty->HasAdaptMaxFontSize()) <<
            "Input value is: " << input << ", method: setMaxFontSize, attribute: maxFontSize";
    };

    for (auto& [input, value] : testFixtureFloat64NonNegInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsStrNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureDimensionsResNonNegNonPctInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_F64_String_Resource, Ark_Resource>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_F64_String_Resource, Ark_Empty>(nullptr));
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
        auto convValue = ArkValue<Opt_TextHeightAdaptivePolicy>(inputValueHeightAdaptivePolicy);
        modifier_->setHeightAdaptivePolicy(node_, &convValue);
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
        auto convValue = ArkValue<Opt_TextHeightAdaptivePolicy>(inputValueHeightAdaptivePolicy);
        modifier_->setHeightAdaptivePolicy(node_, &convValue);
        inputValueHeightAdaptivePolicy = value;
        convValue = ArkValue<Opt_TextHeightAdaptivePolicy>(inputValueHeightAdaptivePolicy);
        modifier_->setHeightAdaptivePolicy(node_, &convValue);
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
    auto convDirection = ArkValue<Opt_Axis>(direction);
    auto convStyle = ArkValue<Opt_ChainStyle>(style);
    modifier_->setChainMode(node_, &convDirection, &convStyle);

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

    convDirection = ArkValue<Opt_Axis>(direction);
    convStyle = ArkValue<Opt_ChainStyle>(Ark_ChainStyle::ARK_CHAIN_STYLE_SPREAD);
    modifier_->setChainMode(node_, &convDirection, &convStyle);

    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());

    storedChainMode = layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue();
    ASSERT_TRUE(storedChainMode.direction.has_value());
    EXPECT_EQ(LineDirection::HORIZONTAL, storedChainMode.direction.value());
    ASSERT_TRUE(storedChainMode.style.has_value());
    EXPECT_EQ(ChainStyle::SPREAD, storedChainMode.style.value());

    direction = Ark_Axis::ARK_AXIS_VERTICAL;
    style = Ark_ChainStyle::ARK_CHAIN_STYLE_PACKED;
    convDirection = ArkValue<Opt_Axis>(direction);
    convStyle = ArkValue<Opt_ChainStyle>(style);
    modifier_->setChainMode(node_, &convDirection, &convStyle);

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

    Opt_Axis direction = ArkValue<Opt_Axis>(static_cast<Ark_Axis>(INT_MAX));
    Opt_ChainStyle style = ArkValue<Opt_ChainStyle>(Ark_ChainStyle::ARK_CHAIN_STYLE_SPREAD_INSIDE);
    modifier_->setChainMode(node_, &direction, &style);
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

    Opt_Axis direction = ArkValue<Opt_Axis>(Ark_Axis::ARK_AXIS_HORIZONTAL);
    Opt_ChainStyle style = ArkValue<Opt_ChainStyle>(static_cast<Ark_ChainStyle>(INT_MIN));
    modifier_->setChainMode(node_, &direction, &style);

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

    Opt_Axis direction = ArkValue<Opt_Axis>(static_cast<Ark_Axis>(INT_MAX));
    Opt_ChainStyle style = ArkValue<Opt_ChainStyle>(static_cast<Ark_ChainStyle>(INT_MIN));
    modifier_->setChainMode(node_, &direction, &style);

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasVerticalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().direction.has_value());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetVerticalChainStyleValue().style.has_value());

    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->HasHorizontalChainStyle());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().direction.has_value());
    EXPECT_FALSE(layoutProperty->GetFlexItemProperty()->GetHorizontalChainStyleValue().style.has_value());
}

/*
 * @tc.name: setBorderRadiusTestBorderRadiusBorderRadiusesTopLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestBorderRadiusBorderRadiusesTopLeftValidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);

    auto checkValue = [this, &initValueBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).topLeft = value;
        auto radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius, &ctx);
        modifier_->setBorderRadius(node_, &radius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_TRUE(borderRadius->radiusTopLeft) << "Passed value is: " << input;
        EXPECT_EQ(borderRadius->radiusTopLeft->ToString(), expectedStr) <<
            "Input value is: " << input
            << ", method: setBorderRadius, attribute: borderRadius.BorderRadiuses.topLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value, &ctx));
    }
}

/*
 * @tc.name: setBorderRadiusTestBorderRadiusBorderRadiusesTopLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestBorderRadiusBorderRadiusesTopLeftInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]));

    auto checkValue = [this, &initValueBorderRadius](const std::string& input, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;
        auto radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius);
        modifier_->setBorderRadius(node_, &radius);
        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).topLeft = value;
        radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius, &ctx);
        modifier_->setBorderRadius(node_, &radius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_FALSE(borderRadius->radiusTopLeft) <<
            "Input value is: " << input
            << ", method: setBorderRadius, attribute: borderRadius.BorderRadiuses.topLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value, &ctx));
    }
    // Check empty optional
    checkValue("undefined", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setBorderRadiusTestBorderRadiusBorderRadiusesTopRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestBorderRadiusBorderRadiusesTopRightValidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);

    auto checkValue = [this, &initValueBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).topRight = value;
        auto radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius, &ctx);
        modifier_->setBorderRadius(node_, &radius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_TRUE(borderRadius->radiusTopRight) << "Passed value is: " << input;
        EXPECT_EQ(borderRadius->radiusTopRight->ToString(), expectedStr) <<
            "Input value is: " << input
            << ", method: setBorderRadius, attribute: borderRadius.BorderRadiuses.topRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value, &ctx));
    }
}

/*
 * @tc.name: setBorderRadiusTestBorderRadiusBorderRadiusesTopRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestBorderRadiusBorderRadiusesTopRightInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);

    auto checkValue = [this, &initValueBorderRadius](const std::string& input, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;
        auto radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius);
        modifier_->setBorderRadius(node_, &radius);
        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).topRight = value;
        radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius, &ctx);
        modifier_->setBorderRadius(node_, &radius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_FALSE(borderRadius->radiusTopRight) <<
            "Input value is: " << input
            << ", method: setBorderRadius, attribute: borderRadius.BorderRadiuses.topRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value, &ctx));
    }
    // Check empty optional
    checkValue("undefined", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setBorderRadiusTestBorderRadiusBorderRadiusesBottomLeftValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestBorderRadiusBorderRadiusesBottomLeftValidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);

    auto checkValue = [this, &initValueBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).bottomLeft = value;
        auto radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius, &ctx);
        modifier_->setBorderRadius(node_, &radius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_TRUE(borderRadius->radiusBottomLeft) << "Passed value is: " << input;
        EXPECT_EQ(borderRadius->radiusBottomLeft->ToString(), expectedStr) <<
            "Input value is: " << input
            << ", method: setBorderRadius, attribute: borderRadius.BorderRadiuses.bottomLeft";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value, &ctx));
    }
}

/*
 * @tc.name: setBorderRadiusTestBorderRadiusBorderRadiusesBottomLeftInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestBorderRadiusBorderRadiusesBottomLeftInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);

    auto checkValue = [this, &initValueBorderRadius](const std::string& input, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;
        auto radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius, &ctx);
        modifier_->setBorderRadius(node_, &radius);
        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).bottomLeft = value;
        radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius);
        modifier_->setBorderRadius(node_, &radius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_FALSE(borderRadius->radiusBottomLeft) <<
            "Input value is: " << input
            << ", method: setBorderRadius, attribute: borderRadius.BorderRadiuses.bottomLeft";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value, &ctx));
    }
    // Check empty optional
    checkValue("undefined", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setBorderRadiusTestBorderRadiusBorderRadiusesBottomRightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestBorderRadiusBorderRadiusesBottomRightValidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);

    auto checkValue = [this, &initValueBorderRadius](
                          const std::string& input, const std::string& expectedStr, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;

        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).bottomRight = value;
        auto radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius, &ctx);
        modifier_->setBorderRadius(node_, &radius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_TRUE(borderRadius->radiusBottomRight);
        EXPECT_EQ(borderRadius->radiusBottomRight->ToString(), expectedStr) <<
            "Input value is: " << input
            << ", method: setBorderRadius, attribute: borderRadius.BorderRadiuses.bottomRight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureLengthNonNegValidValues) {
        checkValue(input, expected, ArkUnion<Opt_Length, Ark_String>(value, &ctx));
    }
}

/*
 * @tc.name: setBorderRadiusTestBorderRadiusBorderRadiusesBottomRightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SecurityComponentMethodModifierTest, setBorderRadiusTestBorderRadiusBorderRadiusesBottomRightInvalidValues,
    TestSize.Level1)
{
    Ark_Union_Dimension_BorderRadiuses initValueBorderRadius;

    // Initial setup
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).topRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomLeft =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);
    WriteToUnion<Ark_BorderRadiuses>(initValueBorderRadius).bottomRight =
        ArkUnion<Opt_Length, Ark_String>(std::get<1>(Fixtures::testFixtureLengthNonNegValidValues[0]), &ctx);

    auto checkValue = [this, &initValueBorderRadius](const std::string& input, const Opt_Length& value) {
        Ark_Union_Dimension_BorderRadiuses inputValueBorderRadius = initValueBorderRadius;
        auto radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius, &ctx);
        modifier_->setBorderRadius(node_, &radius);
        WriteToUnion<Ark_BorderRadiuses>(inputValueBorderRadius).bottomRight = value;
        radius = ArkValue<Opt_Union_Dimension_BorderRadiuses>(inputValueBorderRadius);
        modifier_->setBorderRadius(node_, &radius);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto layoutProperty = frameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
        ASSERT_TRUE(layoutProperty);
        auto borderRadius = layoutProperty->GetBackgroundBorderRadius();
        ASSERT_TRUE(borderRadius) << "Passed value is: " << input;
        ASSERT_FALSE(borderRadius->radiusBottomRight) <<
            "Input value is: " << input
            << ", method: setBorderRadius, attribute: borderRadius.BorderRadiuses.bottomRight";
    };

    for (auto& [input, value] : Fixtures::testFixtureLengthNonNegInvalidValues) {
        checkValue(input, ArkUnion<Opt_Length, Ark_String>(value, &ctx));
    }
    // Check empty optional
    checkValue("undefined", ArkUnion<Opt_Length, Ark_Empty>(nullptr));
}
} // namespace OHOS::Ace::NG
