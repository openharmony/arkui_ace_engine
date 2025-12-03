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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/pattern/shape/shape_container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace {
using OneTestColorStep = std::pair<Opt_ResourceColor, std::string>;
using OneUnionNumStrResStep = std::pair<Opt_Union_F64_String_Resource, std::string>;
using OneUnionNumStrStep = std::pair<Opt_Union_F64_String, double>;

// Names
constexpr auto ATTRIBUTE_WIDTH_NAME = "width";
constexpr auto ATTRIBUTE_HEIGHT_NAME = "height";
constexpr auto ATTRIBUTE_X_NAME = "x";
constexpr auto ATTRIBUTE_Y_NAME = "y";
constexpr auto ATTRIBUTE_STROKE_DASH_OFFSET_NAME = "strokeDashOffset";
constexpr auto ATTRIBUTE_STROKE_LINE_JOIN_NAME = "strokeLineJoin";
constexpr auto ATTRIBUTE_STROKE_MITER_LIMIT_NAME = "strokeMiterLimit";
constexpr auto ATTRIBUTE_STROKE_LINE_CAP_NAME = "strokeLineCap";
constexpr auto ATTRIBUTE_STROKE_OPACITY_NAME = "strokeOpacity";
constexpr auto ATTRIBUTE_STROKE_WIDTH_NAME = "strokeWidth";
constexpr auto ATTRIBUTE_FILL_OPACITY_NAME = "fillOpacity";

// Default values
constexpr auto ATTRIBUTE_STROKE_LINE_JOIN_DEFAULT_VALUE = "LineJoinStyle.Miter";
constexpr auto ATTRIBUTE_STROKE_LINE_CAP_DEFAULT_VALUE = "LineCapStyle.Butt";

constexpr int WIDTH = 100;
constexpr int HEIGHT = 200;
constexpr int X = 10;
constexpr int Y = 20;
constexpr auto WIDTH_STR = "100.00vp";
constexpr auto HEIGHT_STR = "200.00vp";
constexpr auto X_STR = "10.00vp";
constexpr auto Y_STR = "20.00vp";

const std::vector<OneTestColorStep> TEST_COLOR_PLAN = {
    { ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
    { ArkUnion<Opt_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
#ifdef WRONG_COLOR
    { ArkUnion<Opt_ResourceColor, Ark_Int32>(0), "#00000000" },
#endif
    { ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { ArkUnion<Opt_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

} // namespace

class ShapeModifierTest : public ModifierTestBase<GENERATED_ArkUIShapeModifier,
                              &GENERATED_ArkUINodeModifiers::getShapeModifier, GENERATED_ARKUI_SHAPE> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            return AceType::MakeRefPtr<CheckboxTheme>();
        });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

Ark_ViewportRect BuildViewPort(double x, double y, double width, double height)
{
    Ark_ViewportRect viewPort;
    viewPort.x = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(x);
    viewPort.y = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(y);
    viewPort.width = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(width);
    viewPort.height = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(height);
    return viewPort;
}

/**
 * @tc.name: setViewPortTest
 * @tc.desc: setViewPort test
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setViewPortTest, TestSize.Level1)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto viewPort = BuildViewPort(X, Y, WIDTH, HEIGHT);
    auto viewPortOpt = Converter::ArkValue<Opt_ViewportRect>(viewPort);
    modifier_->setViewPort(frameNode, &viewPortOpt);

    auto paintProperty = frameNode->GetPaintProperty<ShapeContainerPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    std::string strResult;
    std::string viewPortStr = GetStringAttribute(node_, "viewPort");
    auto jsonVal = JsonUtil::ParseJsonString(viewPortStr);

    strResult = jsonVal->GetString(ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, WIDTH_STR);
    strResult = jsonVal->GetString(ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, HEIGHT_STR);
    strResult = jsonVal->GetString(ATTRIBUTE_X_NAME);
    EXPECT_EQ(strResult, X_STR);
    strResult = jsonVal->GetString(ATTRIBUTE_Y_NAME);
    EXPECT_EQ(strResult, Y_STR);
}

/**
 * @tc.name: setStrokeTest
 * @tc.desc: setStroke test
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeTest, TestSize.Level1)
{
    static const std::string PROP_NAME("stroke");
    ASSERT_NE(modifier_->setStroke, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, Color::BLACK.ToString());

    for (const auto& [arkResColor, expected] : TEST_COLOR_PLAN) {
        modifier_->setStroke(node_, &arkResColor);
        auto checkColor = GetAttrValue<std::string>(node_, PROP_NAME);
        EXPECT_EQ(checkColor, expected);
    }
}

/**
 * @tc.name: setFillTest
 * @tc.desc: setFill test
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setFillTest, TestSize.Level1)
{
    static const std::string PROP_NAME("fill");
    ASSERT_NE(modifier_->setFill, nullptr);

    auto checkInitial = GetAttrValue<std::string>(node_, PROP_NAME);
    EXPECT_EQ(checkInitial, Color::BLACK.ToString());

    for (const auto& [arkResColor, expected] : TEST_COLOR_PLAN) {
        modifier_->setFill(node_, &arkResColor);
        auto checkColor = GetAttrValue<std::string>(node_, PROP_NAME);
        EXPECT_EQ(checkColor, expected);
    }
}

/*
 * @tc.name: setStrokeDashOffset
 * @tc.desc: check setStrokeDashOffset
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, DISABLED_setStrokeDashOffset, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Union_F64_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.), "1.00vp" },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(0.), "0.00px" },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(2.45), "2.45vp" },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(-2.45), "0.00px" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("5px"), "5.00px" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("22.35px"), "22.35px" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("7vp"), "7.00vp" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("1.65vp"), "1.65vp" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("65fp"), "65.00fp" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("4.3fp"), "4.30fp" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("11lpx"), "11.00lpx" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("0.5lpx"), "0.50lpx" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("3"), "3.00fp" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>(""), "0.00px" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("10.65"), "10.65fp" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("23%"), "0.00px" },
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
 * @tc.name: setStrokeLineCapTestValidValues
 * @tc.desc: Check the functionality of setStrokeLineCap
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeLineCapTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    // Initial setup
    auto valueOpt = Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_BUTT);
    // Test
    modifier_->setStrokeLineCap(node_, &valueOpt);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, "LineCapStyle.Butt");

    // Verifying attribute's other values
    valueOpt = Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_ROUND);
    modifier_->setStrokeLineCap(node_, &valueOpt);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, "LineCapStyle.Round");

    valueOpt = Converter::ArkValue<Opt_LineCapStyle>(ARK_LINE_CAP_STYLE_SQUARE);
    modifier_->setStrokeLineCap(node_, &valueOpt);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, "LineCapStyle.Square");
}

/*
 * @tc.name: setStrokeLineCapTestInvalidValues
 * @tc.desc: Check the functionality of setStrokeLineCap
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeLineCapTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_LineCapStyle inputValueStrokeLineCap;

    // Initial setup
    inputValueStrokeLineCap = static_cast<Ark_LineCapStyle>(-1);
    auto valueOpt = Converter::ArkValue<Opt_LineCapStyle>(inputValueStrokeLineCap);
    // Test
    modifier_->setStrokeLineCap(node_, &valueOpt);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_CAP_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_LINE_CAP_DEFAULT_VALUE);
}

/*
 * @tc.name: setStrokeLineJoinTestValidValues
 * @tc.desc: Check the functionality of setStrokeLineJoin
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeLineJoinTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;

    // Initial setup
    auto valueOpt = Converter::ArkValue<Opt_LineJoinStyle>(ARK_LINE_JOIN_STYLE_MITER);
    // Test
    modifier_->setStrokeLineJoin(node_, &valueOpt);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, "LineJoinStyle.Miter");

    // Verifying attribute's other values
    valueOpt = Converter::ArkValue<Opt_LineJoinStyle>(ARK_LINE_JOIN_STYLE_ROUND);
    modifier_->setStrokeLineJoin(node_, &valueOpt);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, "LineJoinStyle.Round");

    valueOpt = Converter::ArkValue<Opt_LineJoinStyle>(ARK_LINE_JOIN_STYLE_BEVEL);
    modifier_->setStrokeLineJoin(node_, &valueOpt);
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, "LineJoinStyle.Bevel");
}

/*
 * @tc.name: setStrokeLineJoinTestInvalidValues
 * @tc.desc: Check the functionality of setStrokeLineJoin
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeLineJoinTestInvalidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    std::string resultStr;
    Ark_LineJoinStyle inputValueStrokeLineJoin;

    // Initial setup
    inputValueStrokeLineJoin = static_cast<Ark_LineJoinStyle>(-1);
    auto valueOpt = Converter::ArkValue<Opt_LineJoinStyle>(inputValueStrokeLineJoin);
    // Test
    modifier_->setStrokeLineJoin(node_, &valueOpt);

    // Initial verification
    jsonValue = GetJsonValue(node_);
    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_STROKE_LINE_JOIN_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_STROKE_LINE_JOIN_DEFAULT_VALUE);
}

/*
 * @tc.name: setStrokeMiterLimitTest
 * @tc.desc: check setStrokeMiterLimit
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeMiterLimitTest, TestSize.Level1)
{
    using OneTestStep = std::pair<Opt_Union_F64_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.), "1.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(0.), "1.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(2.45), "2.450000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("5px"), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("22.35px"), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("7vp"), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("1.65vp"), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("65fp"), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("4.3fp"), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("11lpx"), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("0.5lpx"), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("3"), "3.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("-3"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>(""), "4.000000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("10.65"), "10.650000" },
        { ArkUnion<Opt_Union_F64_String, Ark_String>("23%"), "1.000000" },
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
 * @tc.name: setStrokeOpacityTest
 * @tc.desc: Check the functionality of setStrokeOpacity
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeOpacityTest, TestSize.Level1)
{
    static const std::vector<OneUnionNumStrResStep> UNION_NUM_STR_RES_TEST_PLAN = {
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(123.), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-123.), "0.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("5.6vp"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-5.6vp"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45px"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-45px"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(0.23), "0.230000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-0.23), "0.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("10%"), "0.100000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45dp"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("undefVal"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(""), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("qw111vp"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("qw111"), "1.000000" },
    };

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setStrokeOpacity(node_, &value);
        auto checkVal = GetStringAttribute(node_, ATTRIBUTE_STROKE_OPACITY_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/**
 * @tc.name: setFillOpacityTest
 * @tc.desc: Check the functionality of setFillOpacity
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setFillOpacityTest, TestSize.Level1)
{
    static const std::vector<OneUnionNumStrResStep> UNION_NUM_STR_RES_TEST_PLAN = {
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(123.), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-123), "0.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("5.6vp"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-5.6vp"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45px"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("-45px"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(0.23), "0.230000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(-0.23), "0.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("10%"), "0.100000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("45dp"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("undefVal"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(""), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("qw111vp"), "1.000000" },
        { ArkUnion<Opt_Union_F64_String_Resource, Ark_String>("qw111"), "1.000000" },
    };

    for (const auto &[value, expectVal]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setFillOpacity(node_, &value);
        auto checkVal = GetStringAttribute(node_, ATTRIBUTE_FILL_OPACITY_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

/*
 * @tc.name: setStrokeWidthTestValidValues
 * @tc.desc: Check the functionality of setStrokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    double result;

    static const std::vector<OneUnionNumStrStep> UNION_NUM_STR_RES_TEST_PLAN = {
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(1.0), 1.0f },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(0.0), 0.0f },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(2.45), 2.45f },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(5.0), 5.0f },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(22.35), 22.35f },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(-0.1), 0.0f },
        { ArkUnion<Opt_Union_F64_String, Ark_Float64>(-5.0), 0.0f },
    };

    for (const auto &[value, expected]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setStrokeWidth(node_, &value);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<double>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        EXPECT_FLOAT_EQ(result, expected);
    }
}

/**
 * @tc.name: setAntiAliasTest
 * @tc.desc: Check the functionality of setAntiAlias
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setAntiAliasTest, TestSize.Level1)
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
        auto valueOpt = Converter::ArkValue<Opt_Boolean>(value);
        modifier_->setAntiAlias(node_, &valueOpt);
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
HWTEST_F(ShapeModifierTest, setStrokeDashArrayTest, TestSize.Level1)
{
    static const std::string propName("strokeDashArray");
    ASSERT_NE(modifier_->setStrokeDashArray, nullptr);
    using OneArrayLengthStep = std::tuple<Array_Length, std::vector<std::string>>;
    std::vector<Dimension> vec1 = {3._px, 6._px};
    std::vector<float> vec2 = {5.4f};
    std::vector<Dimension> vec3 = {8.43_vp};
    std::vector<Dimension> vec4 = {0.1_pct, 0.55_pct};
    const std::vector<OneArrayLengthStep> TEST_PLAN = {
        { Converter::ArkValue<Array_Length>(vec1, Converter::FC), {"3.00px", "6.00px"} },
        { Converter::ArkValue<Array_Length>(vec2, Converter::FC), {"5.40vp", "5.40vp"} },
        { Converter::ArkValue<Array_Length>(vec3, Converter::FC), {"8.43vp", "8.43vp"} },
        { Converter::ArkValue<Array_Length>(vec4, Converter::FC), {"10.00%", "55.00%"} },
    };
    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    ASSERT_TRUE(checkVal->IsArray());
    EXPECT_EQ(checkVal->GetArraySize(), 0);

    for (const auto& [value, expectVal] : TEST_PLAN) {
        auto valueOpt = Converter::ArkValue<Opt_Array_Length>(value);
        modifier_->setStrokeDashArray(node_, &valueOpt);
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
 * @tc.name: setStrokeDashArrayInavlidTest
 * @tc.desc: Check the invalid cases for setStrokeDashArray
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeDashArrayInavlidTest, TestSize.Level1)
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

/**
 * @tc.name: setMeshTest
 * @tc.desc: Check the functionality of setMesh
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setMeshTest, TestSize.Level1)
{
    static const std::string propName("mesh");
    static const std::string propNameValue("value");
    static const std::string propNameRow("row");
    static const std::string propNameColumn("column");
    ASSERT_NE(modifier_->setMesh, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    EXPECT_EQ(checkVal->GetString(), "");

    int32_t column = 2;
    int32_t row = 3;
    std::vector<double> mesh = { 1, 2, 4, 6, 4, 2, 1, 3, 5, 1, 3, 5, 6, 3, 2, 2, 4, 5, 5, 3, 2, 2, 2, 4 };

    auto arkMesh = Converter::ArkValue<Opt_Array_Float64>(mesh, Converter::FC);
    auto arkColumn = Converter::ArkValue<Opt_Int32>(column);
    auto arkRow = Converter::ArkValue<Opt_Int32>(row);

    modifier_->setMesh(node_, &arkMesh, &arkColumn, &arkRow);
    fullJson = GetJsonValue(node_);
    checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    auto valueJson = GetAttrValue<std::unique_ptr<JsonValue>>(checkVal, propNameValue);
    auto valueSize = valueJson->GetArraySize();
    ASSERT_EQ(valueSize, mesh.size());
    for (int i = 0; i < valueSize; i++) {
        EXPECT_EQ(valueJson->GetArrayItem(i)->GetString(), std::to_string(mesh[i]));
    }
    auto rowJson = GetAttrValue<std::string>(checkVal, propNameRow);
    EXPECT_EQ(rowJson, "3");
    auto columnJson = GetAttrValue<std::string>(checkVal, propNameColumn);
    EXPECT_EQ(columnJson, "2");
}

/**
 * @tc.name: setMeshInvalidTest
 * @tc.desc: Check the invalid values for setMesh
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, DISABLED_setMeshInvalidTest, TestSize.Level1)
{
    static const std::string propName("mesh");
    static const std::string propNameValue("value");
    static const std::string propNameRow("row");
    static const std::string propNameColum("column");

    int32_t column = 2;
    int32_t row = 3;
    std::vector<double> mesh = { 1, 2, 4, 6, 4, 2, 1, 3, 5, 1, 3, 5, 6, 3, 2, 2, 4, 5, 5, 3, 2, 2, 2, 4 };

    auto arkMesh = Converter::ArkValue<Opt_Array_Float64>(mesh, Converter::FC);
    auto arkColumn = Converter::ArkValue<Opt_Int32>(column);
    auto arkRow = Converter::ArkValue<Opt_Int32>(row);

    modifier_->setMesh(nullptr, &arkMesh, &arkColumn, &arkRow);
    ASSERT_NE(modifier_->setMesh, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    EXPECT_EQ(checkVal->GetString(), "");

    modifier_->setMesh(node_, nullptr, &arkColumn, &arkRow);
    ASSERT_NE(modifier_->setMesh, nullptr);
    fullJson = GetJsonValue(node_);
    checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    EXPECT_EQ(checkVal->GetString(), "");

    modifier_->setMesh(node_, &arkMesh, nullptr, &arkRow);
    ASSERT_NE(modifier_->setMesh, nullptr);
    fullJson = GetJsonValue(node_);
    checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    EXPECT_EQ(checkVal->GetString(), "");

    modifier_->setMesh(node_, &arkMesh, &arkColumn, nullptr);
    ASSERT_NE(modifier_->setMesh, nullptr);
    fullJson = GetJsonValue(node_);
    checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    EXPECT_EQ(checkVal->GetString(), "");

    arkColumn = Converter::ArkValue<Opt_Int32>(1);
    arkRow = Converter::ArkValue<Opt_Int32>(2);

    modifier_->setMesh(node_, &arkMesh, &arkColumn, &arkRow);
    fullJson = GetJsonValue(node_);
    checkVal = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, propName);
    auto valueJson = GetAttrValue<std::unique_ptr<JsonValue>>(checkVal, propNameValue);
    auto valueSize = valueJson->GetArraySize();
    EXPECT_EQ(valueSize, 0);
    auto rowJson = GetAttrValue<std::string>(checkVal, propNameRow);
    EXPECT_EQ(rowJson, "0");
    auto columnJson = GetAttrValue<std::string>(checkVal, propNameColum);
    EXPECT_EQ(columnJson, "0");
}

} // namespace OHOS::Ace::NG
