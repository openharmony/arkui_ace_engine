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

#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace  {
Ark_Resource ArkRes(Ark_String *name, int id = -1,
    NodeModifier::ResourceType type = NodeModifier::ResourceType::COLOR,
    const char *module = "", const char *bundle = "")
{
    return {
        .id = ArkValue<Ark_Number>(id),
        .type = ArkValue<Ark_Number>(static_cast<Ark_Int32>(type)),
        .moduleName = ArkValue<Ark_String>(module),
        .bundleName = ArkValue<Ark_String>(bundle),
        .params = { .tag = ARK_TAG_OBJECT, .value = {.array = name, .length = name ? 1 : 0} }
    };
}

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
using OneTestColorStep = std::pair<Ark_ResourceColor, std::string>;
using OneUnionNumStrResStep = std::pair<Ark_Union_Number_String_Resource, std::string>;

// global test plans
static Ark_String RESOURCE_NAME = ArkValue<Ark_String>("aa.bb.cc");
static const std::string EXPECTED_RESOURCE_COLOR =
    Color::RED.ToString(); // Color::RED is result of ThemeConstants::GetColorXxxx stubs
static const std::vector<OneTestColorStep> TEST_COLOR_PLAN = {
    { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
    { ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), "#00000000" },
    { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
    { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(&RESOURCE_NAME)), EXPECTED_RESOURCE_COLOR },
    { ArkUnion<Ark_ResourceColor, Ark_Resource>(ArkRes(nullptr, 1234)), EXPECTED_RESOURCE_COLOR },
};
} // namespace

class CommonShapeMethodModifierTest : public ModifierTestBase<GENERATED_ArkUICommonShapeMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonShapeMethodModifier,
    GENERATED_ARKUI_CIRCLE // test common shape methods on frameNode for Circle component
    > {
};

/**
 * @tc.name: setStrokeTest
 * @tc.desc: Check the functionality of CommonShapeMethodModifierTest.setStroke
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierTest, setStrokeTest, TestSize.Level1)
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
HWTEST_F(CommonShapeMethodModifierTest, setFillTest, TestSize.Level1)
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
    Ark_LineCapStyle inputValueStrokeLineCap;

    // Initial setup
    inputValueStrokeLineCap = ARK_LINE_CAP_STYLE_BUTT;

    // Test
    modifier_->setStrokeLineCap(node_, inputValueStrokeLineCap);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, "LineCapStyle.Butt");

    // Verifying attribute's other values
    inputValueStrokeLineCap = ARK_LINE_CAP_STYLE_ROUND;
    modifier_->setStrokeLineCap(node_, inputValueStrokeLineCap);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, "LineCapStyle.Round");

    inputValueStrokeLineCap = ARK_LINE_CAP_STYLE_SQUARE;
    modifier_->setStrokeLineCap(node_, inputValueStrokeLineCap);
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
    Ark_LineCapStyle inputValueStrokeLineCap;

    // Initial setup
    inputValueStrokeLineCap = static_cast<Ark_LineCapStyle>(-1);

    // Test
    modifier_->setStrokeLineCap(node_, inputValueStrokeLineCap);

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
    Ark_LineJoinStyle inputValueStrokeLineJoin;

    // Initial setup
    inputValueStrokeLineJoin = ARK_LINE_JOIN_STYLE_MITER;

    // Test
    modifier_->setStrokeLineJoin(node_, inputValueStrokeLineJoin);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, "LineJoinStyle.Miter");

    // Verifying attribute's other values
    inputValueStrokeLineJoin = ARK_LINE_JOIN_STYLE_ROUND;
    modifier_->setStrokeLineJoin(node_, inputValueStrokeLineJoin);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, "LineJoinStyle.Round");

    inputValueStrokeLineJoin = ARK_LINE_JOIN_STYLE_BEVEL;
    modifier_->setStrokeLineJoin(node_, inputValueStrokeLineJoin);
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
    Ark_LineJoinStyle inputValueStrokeLineJoin;

    // Initial setup
    inputValueStrokeLineJoin = static_cast<Ark_LineJoinStyle>(-1);

    // Test
    modifier_->setStrokeLineJoin(node_, inputValueStrokeLineJoin);

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
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(123)), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(-123)), "0.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("5.6vp")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-5.6vp")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45px")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-45px")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(0.23f)), "0.230000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(-0.23f)), "0.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("10%")), "0.100000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45dp")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("undefVal")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111vp")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111")), "1.000000" },
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
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(123)), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(-123)), "0.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("5.6vp")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-5.6vp")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45px")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("-45px")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(0.23f)), "0.230000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_Number>(ArkValue<Ark_Number>(-0.23f)), "0.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("10%")), "0.100000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("45dp")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("undefVal")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111vp")), "1.000000" },
        { ArkUnion<Ark_Union_Number_String_Resource, Ark_String>(ArkValue<Ark_String>("qw111")), "1.000000" },
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

    typedef std::pair<Ark_Length, double> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { ArkValue<Ark_Length>(1.0f), 1.0f },
        { ArkValue<Ark_Length>(2.45f), 2.45f },
        { ArkValue<Ark_Length>(5.0_px), 5.0f },
        { ArkValue<Ark_Length>(22.35_px), 22.35f },
        { ArkValue<Ark_Length>("23.00%"), 0.0f },
        { ArkValue<Ark_Length>(7.0_vp), 7.0f },
        { ArkValue<Ark_Length>(1.65_vp), 1.65f },
        { ArkValue<Ark_Length>(-0.1f), 0.0f },
        { ArkValue<Ark_Length>(65.0_fp), 65.0f },
        { ArkValue<Ark_Length>(4.3_fp), 4.30f },
        { ArkValue<Ark_Length>(-5.0_px), 0.0f },
    };

    for (const auto &[arkLength, expected]: testPlan) {
        modifier_->setStrokeWidth(node_, &arkLength);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<double>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        EXPECT_NEAR(result, expected, FLT_EPSILON);
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
    using OneTestStep = std::pair<Ark_Union_Number_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(1), "1.00vp" },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(0), "0.00px" },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(2.45f), "2.45vp" },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(-2.45f), "0.00px" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("5px"), "5.00px" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("22.35px"), "22.35px" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("7vp"), "7.00vp" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("1.65vp"), "1.65vp" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("65fp"), "65.00fp" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("4.3fp"), "4.30fp" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("11lpx"), "11.00lpx" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("0.5lpx"), "0.50lpx" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("3"), "3.00fp" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>(""), "0.00px" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("10.65"), "10.65fp" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("23%"), "0.00px" },
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
    using OneTestStep = std::pair<Ark_Union_Number_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(1), "1.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(0), "1.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(2.45f), "2.450000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("5px"), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("22.35px"), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("7vp"), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("1.65vp"), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("65fp"), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("4.3fp"), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("11lpx"), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("0.5lpx"), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("3"), "3.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("-3"), "1.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>(""), "4.000000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("10.65"), "10.650000" },
        { ArkUnion<Ark_Union_Number_String, Ark_String>("23%"), "1.000000" },
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
    using OneBoolStep = std::tuple<Ark_Boolean, std::string>;
    const std::vector<OneBoolStep> BOOL_TEST_PLAN = {
        { false, "false" },
        { true, "true" },
        { 0, "false" },
        { -25, "true" },
        { 0, "false" },
        { 25, "true" },
        { false, "false" }
    };
    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<std::string>(fullJson, PROP_NAME);
    EXPECT_EQ(checkVal, "true");

    for (const auto& [value, expectVal] : BOOL_TEST_PLAN) {
        modifier_->setAntiAlias(node_, value);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetAttrValue<std::string>(fullJson, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}
} // namespace OHOS::Ace::NG
