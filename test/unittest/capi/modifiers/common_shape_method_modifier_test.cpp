/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace  {
// attributes name
const auto ATTRIBUTE_STROKE_LINE_CAP_NAME = "strokeLineCap";
const auto ATTRIBUTE_STROKE_LINE_JOIN_NAME = "strokeLineJoin";
const auto ATTRIBUTE_STROKE_WIDTH_NAME = "strokeWidth";
const auto ATTRIBUTE_STROKE_DASH_OFFSET_NAME = "strokeDashOffset";
const auto ATTRIBUTE_STROKE_MITER_LIMIT_NAME = "strokeMiterLimit";
const auto ATTRIBUTE_STROKE_OPACITY_NAME = "strokeOpacity";
const auto ATTRIBUTE_FILL_OPACITY_NAME = "fillOpacity";

// attributes default
const auto ATTRIBUTE_STROKE_LINE_CAP_DEFAULT_VALUE = "LineCapStyle.Butt";
const auto ATTRIBUTE_STROKE_LINE_JOIN_DEFAULT_VALUE = "LineJoinStyle.Miter";
const auto ATTRIBUTE_STROKE_MITER_LIMIT_DEFAULT_VALUE = "4.000000";
const auto ATTRIBUTE_STROKE_DASH_OFFSET_DEFAULT_VALUE = "0.00px";
const auto ATTRIBUTE_STROKE_OPACITY_DEFAULT_VALUE = "1.000000";
const auto ATTRIBUTE_FILL_OPACITY_DEFAULT_VALUE = "1.000000";
const auto ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE = 0.0f;

// global types
using OneTestColorStep = std::pair<Opt_ResourceColor, std::string>;
using OneUnionNumStrResStep = std::pair<Opt_Union_F64_String_Resource, std::string>;

// global test plans
const auto RES_NAME = NamedResourceId{"aa.bb.cc", ResourceType::COLOR};
const auto RES_ID = IntResourceId{11111, ResourceType::COLOR};
static const std::string EXPECTED_RESOURCE_COLOR =
    Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs
static const std::vector<OneTestColorStep> TEST_COLOR_PLAN = {
    { ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE),
        "#FFFFFFFF" },
    { ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { ArkUnion<Opt_ResourceColor, Ark_Int32>(0.5f), "#00000000" },
    { ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { ArkUnion<Opt_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { CreateResourceUnion<Opt_ResourceColor>(RES_NAME), EXPECTED_RESOURCE_COLOR },
    { CreateResourceUnion<Opt_ResourceColor>(RES_ID), EXPECTED_RESOURCE_COLOR },
};
} // namespace

class CommonShapeMethodModifierTest : public ModifierTestBase<GENERATED_ArkUICommonShapeMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonShapeMethodModifier,
    GENERATED_ARKUI_CIRCLE // test common shape methods on frameNode for Circle component
    > {
    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getCircleModifier()->construct(GetId(), 0);
    }
};

/**
 * @tc.name: setStrokeTest
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStroke
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, DISABLED_setStrokeTest, TestSize.Level1)
{
    static const std::string PROP_NAME("stroke");
    ASSERT_NE(modifier_->setStroke, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, Color::BLACK.ToString());

    for (const auto &[arkResColor, expected]: TEST_COLOR_PLAN) {
        modifier_->setStroke(node_, &arkResColor);
        auto checkColor = GetAttrValue<std::string>(node_, PROP_NAME);
        EXPECT_EQ(checkColor, expected);
    }
}

/**
 * @tc.name: setFillTest
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setFill
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, DISABLED_setFillTest, TestSize.Level1)
{
    static const std::string PROP_NAME("fill");
    ASSERT_NE(modifier_->setFill, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, Color::BLACK.ToString());

    for (const auto &[arkResColor, expected]: TEST_COLOR_PLAN) {
        modifier_->setFill(node_, &arkResColor);
        auto checkColor = GetAttrValue<std::string>(node_, PROP_NAME);
        EXPECT_EQ(checkColor, expected);
    }
}

/*
 * @tc.name: setStrokeLineCapTestDefaultValues
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStrokeLineCap
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeLineCapTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_LINE_CAP_DEFAULT_VALUE);
}

/*
 * @tc.name: setStrokeLineCapTestValidValues
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStrokeLineCap
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeLineCapTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    // Initial setup
    auto inputValueStrokeLineCap = Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_BUTT);

    // Test
    modifier_->setStrokeLineCap(node_, &inputValueStrokeLineCap);


    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, "LineCapStyle.Butt");

    // Verifying attribute's other values
    inputValueStrokeLineCap =  Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_ROUND);
    modifier_->setStrokeLineCap(node_, &inputValueStrokeLineCap);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, "LineCapStyle.Round");

    inputValueStrokeLineCap =  Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_SQUARE);
    modifier_->setStrokeLineCap(node_, &inputValueStrokeLineCap);

    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, "LineCapStyle.Square");
}

/*
 * @tc.name: setStrokeLineCapTestInvalidValues
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStrokeLineCap
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeLineCapTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    // Initial setup
    auto inputValueStrokeLineCap = Converter::ArkValue<Opt_LineCapStyle>(static_cast<Ark_LineCapStyle>(-1));

    // Test
    modifier_->setStrokeLineCap(node_, &inputValueStrokeLineCap);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_LINE_CAP_DEFAULT_VALUE);
}

/*
 * @tc.name: setStrokeLineJoinTestDefaultValues
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStrokeLineJoin
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeLineJoinTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_LINE_JOIN_DEFAULT_VALUE);
}

/*
 * @tc.name: setStrokeLineJoinTestValidValues
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStrokeLineJoin
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeLineJoinTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    // Initial setup
    auto inputValueStrokeLineJoin = Converter::ArkValue<Opt_LineJoinStyle>(ARK_LINE_JOIN_STYLE_MITER);

    // Test
    modifier_->setStrokeLineJoin(node_, &inputValueStrokeLineJoin);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, "LineJoinStyle.Miter");

    // Verifying attribute's other values
    inputValueStrokeLineJoin = Converter::ArkValue<Opt_LineJoinStyle>(ARK_LINE_JOIN_STYLE_ROUND);
    modifier_->setStrokeLineJoin(node_, &inputValueStrokeLineJoin);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, "LineJoinStyle.Round");

    inputValueStrokeLineJoin = Converter::ArkValue<Opt_LineJoinStyle>(ARK_LINE_JOIN_STYLE_BEVEL);
    modifier_->setStrokeLineJoin(node_, &inputValueStrokeLineJoin);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, "LineJoinStyle.Bevel");
}

/*
 * @tc.name: setStrokeLineJoinTestInvalidValues
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStrokeLineJoin
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeLineJoinTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    // Initial setup
    auto inputValueStrokeLineJoin = Converter::ArkValue<Opt_LineJoinStyle>(static_cast<Ark_LineJoinStyle>(-1));

    // Test
    modifier_->setStrokeLineJoin(node_, &inputValueStrokeLineJoin);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_LINE_JOIN_DEFAULT_VALUE);
}

/**
 * @tc.name: setStrokeOpacityTestDefault
 * @tc.desc: Check the functionality of setStrokeOpacity
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeOpacityTestDefault, TestSize.Level1)
{
    ASSERT_NE(modifier_->setStrokeOpacity, nullptr);
    auto checkVal = GetStringAttribute(node_, ATTRIBUTE_STROKE_OPACITY_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_STROKE_OPACITY_DEFAULT_VALUE);
}

/**
 * @tc.name: setStrokeOpacityTest
 * @tc.desc: Check the functionality of setStrokeOpacity
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeOpacityTest, TestSize.Level1)
{
    static const std::vector<OneUnionNumStrResStep> UNION_NUM_STR_RES_TEST_PLAN = {
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(ArkValue<Ark_Float64>(123))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(ArkValue<Ark_Float64>(-123))), "0.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("5.6vp"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("-5.6vp"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("45px"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("-45px"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(ArkValue<Ark_Float64>(0.23f))), "0.230000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(ArkValue<Ark_Float64>(-0.23f))), "0.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("10%"))), "0.100000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("45dp"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("undefVal"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>(""))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111vp"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111"))), "1.000000" },
    };

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setStrokeOpacity(node_, &value);
        auto checkVal = GetStringAttribute(node_, ATTRIBUTE_STROKE_OPACITY_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setFillOpacityTestDefault
 * @tc.desc: Check the functionality of setFillOpacity
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setFillOpacityTestDefault, TestSize.Level1)
{
    ASSERT_NE(modifier_->setStrokeOpacity, nullptr);
    auto checkVal = GetStringAttribute(node_, ATTRIBUTE_FILL_OPACITY_NAME);
    EXPECT_EQ(checkVal, ATTRIBUTE_FILL_OPACITY_DEFAULT_VALUE);
}

/**
 * @tc.name: setFillOpacityTest
 * @tc.desc: Check the functionality of setFillOpacity
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setFillOpacityTest, TestSize.Level1)
{
    static const std::vector<OneUnionNumStrResStep> UNION_NUM_STR_RES_TEST_PLAN = {
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(ArkValue<Ark_Float64>(123))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(ArkValue<Ark_Float64>(-123))), "0.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("5.6vp"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("-5.6vp"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("45px"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("-45px"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(ArkValue<Ark_Float64>(0.23f))), "0.230000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_Float64>(ArkValue<Ark_Float64>(-0.23f))), "0.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("10%"))), "0.100000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("45dp"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("undefVal"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>(""))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111vp"))), "1.000000" },
        { Converter::ArkValue<Opt_Union_F64_String_Resource>(
            ArkUnion<Ark_Union_F64_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111"))), "1.000000" },
    };

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setFillOpacity(node_, &value);
        auto checkVal = GetStringAttribute(node_, ATTRIBUTE_FILL_OPACITY_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: setStrokeWidthTestDefaultValues
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStrokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeWidthTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    double result;

    result = GetAttrValue<double>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
    EXPECT_NEAR(result, ATTRIBUTE_STROKE_WIDTH_DEFAULT_VALUE, FLT_EPSILON);
}

/*
 * @tc.name: setStrokeWidthTestValidValues
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStrokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    double result;

    typedef std::pair<Opt_Length, double> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Opt_Length>(1.0f), 1.0f },
        { ArkValue<Opt_Length>(2.45f), 2.45f },
        { ArkValue<Opt_Length>("5.0px"), 5.0f },
        { ArkValue<Opt_Length>("22.35px"), 22.35f },
        { ArkValue<Opt_Length>("23.00%"), 0.0f },
        { ArkValue<Opt_Length>("7.0vp"), 7.0f },
        { ArkValue<Opt_Length>("1.65vp"), 1.65f },
        { ArkValue<Opt_Length>(-0.1f), 0.0f },
        { ArkValue<Opt_Length>("65.0fp"), 65.0f },
        { ArkValue<Opt_Length>("4.3fp"), 4.30f },
        { ArkValue<Opt_Length>("-5.0px"), 0.0f },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        modifier_->setStrokeWidth(node_, &arkLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<double>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        EXPECT_FLOAT_EQ(result, expected);
    }
}

/*
 * @tc.name: setStrokeDashOffsetTest
 * @tc.desc: check work setStrokeDashOffset
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeDashOffsetTestDefault, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_DASH_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_DASH_OFFSET_DEFAULT_VALUE);
}

/*
 * @tc.name: setStrokeDashOffsetTest
 * @tc.desc: check work setStrokeDashOffset
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeDashOffsetTest, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Union_F64_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(1), "1.00vp" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(0), "0.00px" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(2.45f), "2.45vp" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-2.45f), "0.00px" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("5px"), "5.00px" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("22.35px"), "22.35px" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("7vp"), "7.00vp" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("1.65vp"), "1.65vp" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("65fp"), "65.00fp" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("4.3fp"), "4.30fp" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("11lpx"), "11.00lpx" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("0.5lpx"), "0.50lpx" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("3"), "3.00vp" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(""), "0.00px" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("10.65"), "10.65vp" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("23%"), "0.00px" },
    };

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    for (const auto &[arkValue, expected]: testPlan) {
        modifier_->setStrokeDashOffset(node_, &arkValue);

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_DASH_OFFSET_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/*
 * @tc.name: setStrokeMiterLimitTest
 * @tc.desc: check work setStrokeMiterLimit
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeMiterLimitTestDefaultValue, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_MITER_LIMIT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_MITER_LIMIT_DEFAULT_VALUE);
}

/*
 * @tc.name: setStrokeMiterLimitTest
 * @tc.desc: check work setStrokeMiterLimit
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeMiterLimitTest, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Union_F64_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(1), "1.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(0), "1.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(2.45f), "2.450000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("5px"), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("22.35px"), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("7vp"), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("1.65vp"), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("65fp"), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("4.3fp"), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("11lpx"), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("0.5lpx"), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("3"), "3.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("-3"), "1.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(""), "4.000000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("10.65"), "10.650000" },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("23%"), "1.000000" },
    };

    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    for (const auto &[arkValue, expected]: testPlan) {
        modifier_->setStrokeMiterLimit(node_, &arkValue);

        jsonValue = GetJsonValue(node_);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_MITER_LIMIT_NAME);
        EXPECT_EQ(resultStr, expected);
    }
}

/**
 * @tc.name: setAntiAliasTest
 * @tc.desc: Check the functionality of setAntiAlias
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setAntiAliasTest, TestSize.Level1)
{
    static const std::string PROP_NAME("antiAlias");
    ASSERT_NE(modifier_->setAntiAlias, nullptr);
    using OneBoolStep = std::tuple<Opt_Boolean, std::string>;
    const std::vector<OneBoolStep> BOOL_TEST_PLAN = {
        { Converter::ArkValue<Opt_Boolean>(false), "false" },
        { Converter::ArkValue<Opt_Boolean>(true), "true" },
        { Converter::ArkValue<Opt_Boolean>(0), "false" },
        { Converter::ArkValue<Opt_Boolean>(-25), "true" },
        { Converter::ArkValue<Opt_Boolean>(0), "false" },
        { Converter::ArkValue<Opt_Boolean>(25), "true" },
        { Converter::ArkValue<Opt_Boolean>(false), "false" }
    };
    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<std::string>(fullJson, PROP_NAME);
    EXPECT_EQ(checkVal, "true");

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setAntiAlias(node_, &value);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetAttrValue<std::string>(fullJson, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setStrokeDashArrayTest
 * @tc.desc: Check the functionality of setStrokeDashArray
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, DISABLED_setStrokeDashArrayTest, TestSize.Level1)
{
    static const std::string propName("strokeDashArray");
    ASSERT_NE(modifier_->setStrokeDashArray, nullptr);
    using OneArrayLengthStep = std::tuple<Opt_Array_Length, std::vector<std::string>>;
    std::vector<Dimension> vec1 = {3._px, 6._px};
    std::vector<float> vec2 = {5.4f};
    std::vector<Dimension> vec3 = {8.43_vp};
    std::vector<Dimension> vec4 = {0.1_pct, 0.55_pct};
    const std::vector<OneArrayLengthStep> TEST_PLAN = {
        { Converter::ArkValue<Opt_Array_Length>(vec1, Converter::FC), {"3.00px", "6.00px"} },
        { Converter::ArkValue<Opt_Array_Length>(vec2, Converter::FC), {"5.40vp", "5.40vp"} },
        { Converter::ArkValue<Opt_Array_Length>(vec3, Converter::FC), {"8.43vp", "8.43vp"} },
        { Converter::ArkValue<Opt_Array_Length>(vec4, Converter::FC), {"10.00%", "55.00%"} },
    };
    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    ASSERT_TRUE(checkVal->IsArray());
    EXPECT_EQ(checkVal->GetArraySize(), 0);

    for (const auto& [value, expectVal] : TEST_PLAN) {
        modifier_->setStrokeDashArray(node_, &value);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
        ASSERT_TRUE(checkVal->IsArray());
        ASSERT_EQ(checkVal->GetArraySize(), 2);
        ASSERT_NE(checkVal->GetArrayItem(0), nullptr);
        EXPECT_EQ(checkVal->GetArrayItem(0)->GetString(), expectVal[0]);
        ASSERT_NE(checkVal->GetArrayItem(1), nullptr);
        EXPECT_EQ(checkVal->GetArrayItem(1)->GetString(), expectVal[1]);
    }
}

/**
 * @tc.name: setStrokeDashArrayInvalidTest
 * @tc.desc: Check the invalid cases for setStrokeDashArray
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, DISABLED_setStrokeDashArrayInvalidTest, TestSize.Level1)
{
    static const std::string propName("strokeDashArray");
    ASSERT_NE(modifier_->setStrokeDashArray, nullptr);
    modifier_->setStrokeDashArray(node_, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    ASSERT_TRUE(checkVal->IsArray());
    EXPECT_EQ(checkVal->GetArraySize(), 0);

    modifier_->setStrokeDashArray(nullptr, nullptr);
    fullJson = GetJsonValue(node_);
    checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    ASSERT_TRUE(checkVal->IsArray());
    EXPECT_EQ(checkVal->GetArraySize(), 0);
}
} // namespace OHOS::Ace::NG
