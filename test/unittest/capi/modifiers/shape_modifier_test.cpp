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
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace {
using OneTestColorStep = std::pair<Ark_ResourceColor, std::string>;
using OneUnionNumStrResStep = std::pair<Ark_Union_Number_String_Resource, std::string>;
using OneUnionNumStrStep = std::pair<Ark_Union_Number_String, double>;

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
    { ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
    { ArkUnion<Ark_ResourceColor, Ark_Number>(0x123456), "#FF123456" },
    { ArkUnion<Ark_ResourceColor, Ark_Number>(0.5f), "#00000000" },
    { ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
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

Ark_Literal_Union_Number_String_height_width_x_y BuildViewPort(int x, int y, int width, int height)
{
    Ark_Literal_Union_Number_String_height_width_x_y viewPort;
    viewPort.x = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(x);
    viewPort.y = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(y);
    viewPort.width = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(width);
    viewPort.height = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(height);
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
    modifier_->setViewPort(frameNode, &viewPort);

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
HWTEST_F(ShapeModifierTest, setStrokeDashOffset, TestSize.Level1)
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
 * @tc.name: setStrokeLineCapTestValidValues
 * @tc.desc: Check the functionality of setStrokeLineCap
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeLineCapTestValidValues, TestSize.Level1)
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

    // Test
    modifier_->setStrokeLineCap(node_, inputValueStrokeLineCap);

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

    // Test
    modifier_->setStrokeLineJoin(node_, inputValueStrokeLineJoin);

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
 * @tc.name: setStrokeOpacityTest
 * @tc.desc: Check the functionality of setStrokeOpacity
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeOpacityTest, TestSize.Level1)
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
 * @tc.name: setFillOpacityTest
 * @tc.desc: Check the functionality of setFillOpacity
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setFillOpacityTest, TestSize.Level1)
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
 * @tc.name: setStrokeWidthTestValidValues
 * @tc.desc: Check the functionality of setStrokeWidth
 * @tc.type: FUNC
 */
HWTEST_F(ShapeModifierTest, setStrokeWidthTestValidValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue;
    double result;

    static const std::vector<OneUnionNumStrStep> UNION_NUM_STR_RES_TEST_PLAN = {
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(1.0f)), 1.0f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(2.45f)), 2.45f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(5.0_px)), 5.0f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(22.35_px)), 22.35f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(0.23_pct)), 0.0f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(7.0_vp)), 7.0f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(1.65_vp)), 1.65f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(-0.1f)), 0.0f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(65.0_fp)), 65.0f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(4.3_fp)), 4.30f },
        { ArkUnion<Ark_Union_Number_String, Ark_Number>(ArkValue<Ark_Number>(-5.0_px)), 0.0f },
    };

    for (const auto &[value, expected]: UNION_NUM_STR_RES_TEST_PLAN) {
        modifier_->setStrokeWidth(node_, &value);
        jsonValue = GetJsonValue(node_);
        result = GetAttrValue<double>(jsonValue, ATTRIBUTE_STROKE_WIDTH_NAME);
        EXPECT_NEAR(result, expected, FLT_EPSILON);
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
        modifier_->setAntiAlias(node_, value);
        auto fullJson = GetJsonValue(node_);
        checkVal = GetAttrValue<std::string>(fullJson, PROP_NAME);
        EXPECT_EQ(checkVal, expectVal);
    }
}

} // namespace OHOS::Ace::NG
