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

#include "calendar_modifier_test.h"

namespace OHOS::Ace::NG {
using namespace TestConst::Calendar;
/*
 * @tc.name: setWorkStateStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultWorkStateStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'workStateStyle.workDayMarkColor'";

    resultStr = GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'workStateStyle.offDayMarkColor'";

    resultStr = GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'workStateStyle.workDayMarkSize'";

    resultStr = GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'workStateStyle.offDayMarkSize'";

    resultStr = GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_WIDTH_DEFAULT_VALUE)
        << "Default value for attribute 'workStateStyle.workStateWidth'";

    resultStr = GetAttrValue<std::string>(
        resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_HORIZONTAL_MOVING_DISTANCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_HORIZONTAL_MOVING_DISTANCE_DEFAULT_VALUE)
        << "Default value for attribute 'workStateStyle.workStateHorizontalMovingDistance'";

    resultStr = GetAttrValue<std::string>(
        resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_VERTICAL_MOVING_DISTANCE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_VERTICAL_MOVING_DISTANCE_DEFAULT_VALUE)
        << "Default value for attribute 'workStateStyle.workStateVerticalMovingDistance'";
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkDayMarkColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkDayMarkColorValidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        inputValueWorkStateStyle.workDayMarkColor = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.workDayMarkColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkDayMarkColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkDayMarkColorInvalidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        inputValueWorkStateStyle.workDayMarkColor = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.workDayMarkColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleOffDayMarkColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleOffDayMarkColorValidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        inputValueWorkStateStyle.offDayMarkColor = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.offDayMarkColor";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureColorsEnumValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsNumValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Number>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsResValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Resource>(value), expected);
    }
    for (auto& [input, value, expected] : Fixtures::testFixtureColorsStrValidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value), expected);
    }
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleOffDayMarkColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleOffDayMarkColorInvalidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        inputValueWorkStateStyle.offDayMarkColor = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.offDayMarkColor";
    };

    for (auto& [input, value] : Fixtures::testFixtureColorsStrInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_String>(value));
    }
    for (auto& [input, value] : Fixtures::testFixtureColorsEnumInvalidValues) {
        checkValue(input, ArkUnion<Opt_ResourceColor, Ark_Color>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr));
    // Check empty optional
    checkValue("undefined", ArkValue<Opt_ResourceColor>());
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkDayMarkSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkDayMarkSizeValidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        inputValueWorkStateStyle.workDayMarkSize = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.workDayMarkSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkDayMarkSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkDayMarkSizeInvalidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](const std::string& input, const Opt_Number& value) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        inputValueWorkStateStyle.workDayMarkSize = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_DAY_MARK_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.workDayMarkSize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleOffDayMarkSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleOffDayMarkSizeValidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        inputValueWorkStateStyle.offDayMarkSize = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.offDayMarkSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleOffDayMarkSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleOffDayMarkSizeInvalidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](const std::string& input, const Opt_Number& value) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        inputValueWorkStateStyle.offDayMarkSize = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_OFF_DAY_MARK_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.offDayMarkSize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkStateWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkStateWidthValidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        inputValueWorkStateStyle.workStateWidth = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.workStateWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkStateWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkStateWidthInvalidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](const std::string& input, const Opt_Number& value) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        inputValueWorkStateStyle.workStateWidth = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWorkStateStyle, attribute: workStateStyle.workStateWidth";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkStateHorizontalMovingDistanceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkStateHorizontalMovingDistanceValidValues,
    TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        inputValueWorkStateStyle.workStateHorizontalMovingDistance = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_HORIZONTAL_MOVING_DISTANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setWorkStateStyle, attribute: workStateStyle.workStateHorizontalMovingDistance";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkStateHorizontalMovingDistanceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest,
    DISABLED_setWorkStateStyleTestWorkStateStyleWorkStateHorizontalMovingDistanceInvalidValues, TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](const std::string& input, const Opt_Number& value) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        inputValueWorkStateStyle.workStateHorizontalMovingDistance = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_HORIZONTAL_MOVING_DISTANCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_HORIZONTAL_MOVING_DISTANCE_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setWorkStateStyle, attribute: workStateStyle.workStateHorizontalMovingDistance";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkStateVerticalMovingDistanceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkStateVerticalMovingDistanceValidValues,
    TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        inputValueWorkStateStyle.workStateVerticalMovingDistance = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_VERTICAL_MOVING_DISTANCE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setWorkStateStyle, attribute: workStateStyle.workStateVerticalMovingDistance";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWorkStateStyleTestWorkStateStyleWorkStateVerticalMovingDistanceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWorkStateStyleTestWorkStateStyleWorkStateVerticalMovingDistanceInvalidValues,
    TestSize.Level1)
{
    Ark_WorkStateStyle initValueWorkStateStyle;

    // Initial setup
    initValueWorkStateStyle.workDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.offDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWorkStateStyle.workDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.offDayMarkSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateHorizontalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWorkStateStyle.workStateVerticalMovingDistance =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWorkStateStyle](const std::string& input, const Opt_Number& value) {
        Ark_WorkStateStyle inputValueWorkStateStyle = initValueWorkStateStyle;

        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        inputValueWorkStateStyle.workStateVerticalMovingDistance = value;
        modifier_->setWorkStateStyle(node_, &inputValueWorkStateStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWorkStateStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WORK_STATE_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultWorkStateStyle, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_VERTICAL_MOVING_DISTANCE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WORK_STATE_STYLE_I_WORK_STATE_VERTICAL_MOVING_DISTANCE_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setWorkStateStyle, attribute: workStateStyle.workStateVerticalMovingDistance";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}
} // namespace OHOS::Ace::NG
