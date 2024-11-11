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
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDailyFiveRowSpaceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDailyFiveRowSpaceValidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.dailyFiveRowSpace = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_FIVE_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.dailyFiveRowSpace";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDailyFiveRowSpaceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDailyFiveRowSpaceInvalidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_Number& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.dailyFiveRowSpace = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_FIVE_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_FIVE_ROW_SPACE_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.dailyFiveRowSpace";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDailySixRowSpaceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDailySixRowSpaceValidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.dailySixRowSpace = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_SIX_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.dailySixRowSpace";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDailySixRowSpaceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDailySixRowSpaceInvalidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_Number& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.dailySixRowSpace = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_SIX_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_SIX_ROW_SPACE_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.dailySixRowSpace";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleLunarHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleLunarHeightValidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.lunarHeight = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.lunarHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleLunarHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleLunarHeightInvalidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_Number& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.lunarHeight = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_HEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.lunarHeight";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleUnderscoreWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleUnderscoreWidthValidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.underscoreWidth = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input
                                          << ", method: setCurrentDayStyle, attribute: currentDayStyle.underscoreWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleUnderscoreWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleUnderscoreWidthInvalidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_Number& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.underscoreWidth = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.underscoreWidth";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleUnderscoreLengthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleUnderscoreLengthValidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.underscoreLength = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_LENGTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.underscoreLength";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleUnderscoreLengthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleUnderscoreLengthInvalidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_Number& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.underscoreLength = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_LENGTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_LENGTH_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.underscoreLength";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleScheduleMarkerRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleScheduleMarkerRadiusValidValues,
    TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.scheduleMarkerRadius = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.scheduleMarkerRadius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleScheduleMarkerRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleScheduleMarkerRadiusInvalidValues,
    TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_Number& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.scheduleMarkerRadius = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_RADIUS_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.scheduleMarkerRadius";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleBoundaryRowOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleBoundaryRowOffsetValidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.boundaryRowOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_ROW_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.boundaryRowOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleBoundaryRowOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleBoundaryRowOffsetInvalidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_Number& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.boundaryRowOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_ROW_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_ROW_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.boundaryRowOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleBoundaryColOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleBoundaryColOffsetValidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.boundaryColOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_COL_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.boundaryColOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleBoundaryColOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleBoundaryColOffsetInvalidValues, TestSize.Level1)
{
    Ark_CurrentDayStyle initValueCurrentDayStyle;

    // Initial setup
    initValueCurrentDayStyle.dayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.lunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.markLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueCurrentDayStyle.dayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.gregorianCalendarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarDayYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerXAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerYAxisOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.colSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailyFiveRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.dailySixRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.lunarHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreWidth =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.underscoreLength =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.scheduleMarkerRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryRowOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueCurrentDayStyle.boundaryColOffset =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_Number& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.boundaryColOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_COL_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_COL_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.boundaryColOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setNonCurrentDayStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setNonCurrentDayStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultNonCurrentDayStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(
        resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_DAY_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_DAY_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'nonCurrentDayStyle.nonCurrentMonthDayColor'";

    resultStr = GetAttrValue<std::string>(
        resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_LUNAR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_LUNAR_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'nonCurrentDayStyle.nonCurrentMonthLunarColor'";

    resultStr = GetAttrValue<std::string>(
        resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_WORK_DAY_MARK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_WORK_DAY_MARK_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'nonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor'";

    resultStr = GetAttrValue<std::string>(
        resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_OFF_DAY_MARK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_OFF_DAY_MARK_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'nonCurrentDayStyle.nonCurrentMonthOffDayMarkColor'";
}

/*
 * @tc.name: setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthDayColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthDayColorValidValues,
    TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValueNonCurrentDayStyle;

    // Initial setup
    initValueNonCurrentDayStyle.nonCurrentMonthDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueNonCurrentDayStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_NonCurrentDayStyle inputValueNonCurrentDayStyle = initValueNonCurrentDayStyle;

        inputValueNonCurrentDayStyle.nonCurrentMonthDayColor = value;
        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultNonCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setNonCurrentDayStyle, attribute: nonCurrentDayStyle.nonCurrentMonthDayColor";
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
 * @tc.name: setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthDayColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthDayColorInvalidValues,
    TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValueNonCurrentDayStyle;

    // Initial setup
    initValueNonCurrentDayStyle.nonCurrentMonthDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueNonCurrentDayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_NonCurrentDayStyle inputValueNonCurrentDayStyle = initValueNonCurrentDayStyle;

        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        inputValueNonCurrentDayStyle.nonCurrentMonthDayColor = value;
        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultNonCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_DAY_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setNonCurrentDayStyle, attribute: nonCurrentDayStyle.nonCurrentMonthDayColor";
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
 * @tc.name: setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthLunarColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthLunarColorValidValues,
    TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValueNonCurrentDayStyle;

    // Initial setup
    initValueNonCurrentDayStyle.nonCurrentMonthDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueNonCurrentDayStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_NonCurrentDayStyle inputValueNonCurrentDayStyle = initValueNonCurrentDayStyle;

        inputValueNonCurrentDayStyle.nonCurrentMonthLunarColor = value;
        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultNonCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setNonCurrentDayStyle, attribute: nonCurrentDayStyle.nonCurrentMonthLunarColor";
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
 * @tc.name: setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthLunarColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest,
    DISABLED_setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthLunarColorInvalidValues, TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValueNonCurrentDayStyle;

    // Initial setup
    initValueNonCurrentDayStyle.nonCurrentMonthDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueNonCurrentDayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_NonCurrentDayStyle inputValueNonCurrentDayStyle = initValueNonCurrentDayStyle;

        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        inputValueNonCurrentDayStyle.nonCurrentMonthLunarColor = value;
        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultNonCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_LUNAR_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setNonCurrentDayStyle, attribute: nonCurrentDayStyle.nonCurrentMonthLunarColor";
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
 * @tc.name: setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthWorkDayMarkColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest,
    DISABLED_setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthWorkDayMarkColorValidValues, TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValueNonCurrentDayStyle;

    // Initial setup
    initValueNonCurrentDayStyle.nonCurrentMonthDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueNonCurrentDayStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_NonCurrentDayStyle inputValueNonCurrentDayStyle = initValueNonCurrentDayStyle;

        inputValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor = value;
        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultNonCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_WORK_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setNonCurrentDayStyle, attribute: nonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor";
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
 * @tc.name: setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthWorkDayMarkColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest,
    DISABLED_setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthWorkDayMarkColorInvalidValues, TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValueNonCurrentDayStyle;

    // Initial setup
    initValueNonCurrentDayStyle.nonCurrentMonthDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueNonCurrentDayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_NonCurrentDayStyle inputValueNonCurrentDayStyle = initValueNonCurrentDayStyle;

        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        inputValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor = value;
        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultNonCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_WORK_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_WORK_DAY_MARK_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setNonCurrentDayStyle, attribute: nonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor";
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
 * @tc.name: setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthOffDayMarkColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest,
    DISABLED_setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthOffDayMarkColorValidValues, TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValueNonCurrentDayStyle;

    // Initial setup
    initValueNonCurrentDayStyle.nonCurrentMonthDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueNonCurrentDayStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_NonCurrentDayStyle inputValueNonCurrentDayStyle = initValueNonCurrentDayStyle;

        inputValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor = value;
        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultNonCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_OFF_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setNonCurrentDayStyle, attribute: nonCurrentDayStyle.nonCurrentMonthOffDayMarkColor";
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
 * @tc.name: setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthOffDayMarkColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest,
    DISABLED_setNonCurrentDayStyleTestNonCurrentDayStyleNonCurrentMonthOffDayMarkColorInvalidValues, TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValueNonCurrentDayStyle;

    // Initial setup
    initValueNonCurrentDayStyle.nonCurrentMonthDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));

    auto checkValue = [this, &initValueNonCurrentDayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_NonCurrentDayStyle inputValueNonCurrentDayStyle = initValueNonCurrentDayStyle;

        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        inputValueNonCurrentDayStyle.nonCurrentMonthOffDayMarkColor = value;
        modifier_->setNonCurrentDayStyle(node_, &inputValueNonCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultNonCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_NON_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultNonCurrentDayStyle, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_OFF_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_NON_CURRENT_DAY_STYLE_I_NON_CURRENT_MONTH_OFF_DAY_MARK_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setNonCurrentDayStyle, attribute: nonCurrentDayStyle.nonCurrentMonthOffDayMarkColor";
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
 * @tc.name: setTodayStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setTodayStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultTodayStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_DAY_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_DAY_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'todayStyle.focusedDayColor'";

    resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_LUNAR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_LUNAR_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'todayStyle.focusedLunarColor'";

    resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_BACKGROUND_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_BACKGROUND_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'todayStyle.focusedAreaBackgroundColor'";

    resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_RADIUS_DEFAULT_VALUE)
        << "Default value for attribute 'todayStyle.focusedAreaRadius'";
}

/*
 * @tc.name: setTodayStyleTestTodayStyleFocusedDayColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setTodayStyleTestTodayStyleFocusedDayColorValidValues, TestSize.Level1)
{
    Ark_TodayStyle initValueTodayStyle;

    // Initial setup
    initValueTodayStyle.focusedDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueTodayStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_TodayStyle inputValueTodayStyle = initValueTodayStyle;

        inputValueTodayStyle.focusedDayColor = value;
        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTodayStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTodayStyle, attribute: todayStyle.focusedDayColor";
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
 * @tc.name: setTodayStyleTestTodayStyleFocusedDayColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setTodayStyleTestTodayStyleFocusedDayColorInvalidValues, TestSize.Level1)
{
    Ark_TodayStyle initValueTodayStyle;

    // Initial setup
    initValueTodayStyle.focusedDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueTodayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_TodayStyle inputValueTodayStyle = initValueTodayStyle;

        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        inputValueTodayStyle.focusedDayColor = value;
        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTodayStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_DAY_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTodayStyle, attribute: todayStyle.focusedDayColor";
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
 * @tc.name: setTodayStyleTestTodayStyleFocusedLunarColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setTodayStyleTestTodayStyleFocusedLunarColorValidValues, TestSize.Level1)
{
    Ark_TodayStyle initValueTodayStyle;

    // Initial setup
    initValueTodayStyle.focusedDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueTodayStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_TodayStyle inputValueTodayStyle = initValueTodayStyle;

        inputValueTodayStyle.focusedLunarColor = value;
        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTodayStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTodayStyle, attribute: todayStyle.focusedLunarColor";
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
 * @tc.name: setTodayStyleTestTodayStyleFocusedLunarColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setTodayStyleTestTodayStyleFocusedLunarColorInvalidValues, TestSize.Level1)
{
    Ark_TodayStyle initValueTodayStyle;

    // Initial setup
    initValueTodayStyle.focusedDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueTodayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_TodayStyle inputValueTodayStyle = initValueTodayStyle;

        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        inputValueTodayStyle.focusedLunarColor = value;
        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTodayStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_LUNAR_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTodayStyle, attribute: todayStyle.focusedLunarColor";
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
 * @tc.name: setTodayStyleTestTodayStyleFocusedAreaBackgroundColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setTodayStyleTestTodayStyleFocusedAreaBackgroundColorValidValues, TestSize.Level1)
{
    Ark_TodayStyle initValueTodayStyle;

    // Initial setup
    initValueTodayStyle.focusedDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueTodayStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_TodayStyle inputValueTodayStyle = initValueTodayStyle;

        inputValueTodayStyle.focusedAreaBackgroundColor = value;
        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTodayStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setTodayStyle, attribute: todayStyle.focusedAreaBackgroundColor";
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
 * @tc.name: setTodayStyleTestTodayStyleFocusedAreaBackgroundColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setTodayStyleTestTodayStyleFocusedAreaBackgroundColorInvalidValues, TestSize.Level1)
{
    Ark_TodayStyle initValueTodayStyle;

    // Initial setup
    initValueTodayStyle.focusedDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueTodayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_TodayStyle inputValueTodayStyle = initValueTodayStyle;

        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        inputValueTodayStyle.focusedAreaBackgroundColor = value;
        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTodayStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_BACKGROUND_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setTodayStyle, attribute: todayStyle.focusedAreaBackgroundColor";
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
 * @tc.name: setTodayStyleTestTodayStyleFocusedAreaRadiusValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setTodayStyleTestTodayStyleFocusedAreaRadiusValidValues, TestSize.Level1)
{
    Ark_TodayStyle initValueTodayStyle;

    // Initial setup
    initValueTodayStyle.focusedDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueTodayStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_TodayStyle inputValueTodayStyle = initValueTodayStyle;

        inputValueTodayStyle.focusedAreaRadius = value;
        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTodayStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_RADIUS_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setTodayStyle, attribute: todayStyle.focusedAreaRadius";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setTodayStyleTestTodayStyleFocusedAreaRadiusInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setTodayStyleTestTodayStyleFocusedAreaRadiusInvalidValues, TestSize.Level1)
{
    Ark_TodayStyle initValueTodayStyle;

    // Initial setup
    initValueTodayStyle.focusedDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaBackgroundColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueTodayStyle.focusedAreaRadius =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueTodayStyle](const std::string& input, const Opt_Number& value) {
        Ark_TodayStyle inputValueTodayStyle = initValueTodayStyle;

        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        inputValueTodayStyle.focusedAreaRadius = value;
        modifier_->setTodayStyle(node_, &inputValueTodayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultTodayStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_TODAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultTodayStyle, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_RADIUS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_TODAY_STYLE_I_FOCUSED_AREA_RADIUS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setTodayStyle, attribute: todayStyle.focusedAreaRadius";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWeekStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultWeekStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'weekStyle.weekColor'";

    resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_DAY_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_DAY_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'weekStyle.weekendDayColor'";

    resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_LUNAR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_LUNAR_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'weekStyle.weekendLunarColor'";

    resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_FONT_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'weekStyle.weekFontSize'";

    resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_HEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'weekStyle.weekHeight'";

    resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_WIDTH_DEFAULT_VALUE)
        << "Default value for attribute 'weekStyle.weekWidth'";

    resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_AND_DAY_ROW_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_AND_DAY_ROW_SPACE_DEFAULT_VALUE)
        << "Default value for attribute 'weekStyle.weekAndDayRowSpace'";
}

/*
 * @tc.name: setWeekStyleTestWeekStyleWeekColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekColorValidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        inputValueWeekStyle.weekColor = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekColor";
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
 * @tc.name: setWeekStyleTestWeekStyleWeekColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekColorInvalidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        inputValueWeekStyle.weekColor = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekColor";
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
 * @tc.name: setWeekStyleTestWeekStyleWeekendDayColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekendDayColorValidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        inputValueWeekStyle.weekendDayColor = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekendDayColor";
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
 * @tc.name: setWeekStyleTestWeekStyleWeekendDayColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekendDayColorInvalidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        inputValueWeekStyle.weekendDayColor = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_DAY_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekendDayColor";
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
 * @tc.name: setWeekStyleTestWeekStyleWeekendLunarColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekendLunarColorValidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        inputValueWeekStyle.weekendLunarColor = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekendLunarColor";
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
 * @tc.name: setWeekStyleTestWeekStyleWeekendLunarColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekendLunarColorInvalidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        inputValueWeekStyle.weekendLunarColor = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEKEND_LUNAR_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekendLunarColor";
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
 * @tc.name: setWeekStyleTestWeekStyleWeekFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekFontSizeValidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        inputValueWeekStyle.weekFontSize = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWeekStyleTestWeekStyleWeekFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekFontSizeInvalidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](const std::string& input, const Opt_Number& value) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        inputValueWeekStyle.weekFontSize = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_FONT_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekFontSize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWeekStyleTestWeekStyleWeekHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekHeightValidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        inputValueWeekStyle.weekHeight = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWeekStyleTestWeekStyleWeekHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekHeightInvalidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](const std::string& input, const Opt_Number& value) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        inputValueWeekStyle.weekHeight = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_HEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekHeight";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWeekStyleTestWeekStyleWeekWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekWidthValidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        inputValueWeekStyle.weekWidth = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWeekStyleTestWeekStyleWeekWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekWidthInvalidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](const std::string& input, const Opt_Number& value) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        inputValueWeekStyle.weekWidth = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekWidth";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setWeekStyleTestWeekStyleWeekAndDayRowSpaceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekAndDayRowSpaceValidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](
                          const std::string& input, const Opt_Number& value, const std::string& expectedStr) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        inputValueWeekStyle.weekAndDayRowSpace = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_AND_DAY_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekAndDayRowSpace";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setWeekStyleTestWeekStyleWeekAndDayRowSpaceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setWeekStyleTestWeekStyleWeekAndDayRowSpaceInvalidValues, TestSize.Level1)
{
    Ark_WeekStyle initValueWeekStyle;

    // Initial setup
    initValueWeekStyle.weekColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendDayColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekendLunarColor =
        ArkUnion<Opt_ResourceColor, Ark_Color>(std::get<1>(Fixtures::testFixtureColorsEnumValidValues[0]));
    initValueWeekStyle.weekFontSize =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekHeight =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekWidth = ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));
    initValueWeekStyle.weekAndDayRowSpace =
        ArkValue<Opt_Number>(std::get<1>(Fixtures::testFixtureNumberAnythingValidValues[0]));

    auto checkValue = [this, &initValueWeekStyle](const std::string& input, const Opt_Number& value) {
        Ark_WeekStyle inputValueWeekStyle = initValueWeekStyle;

        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        inputValueWeekStyle.weekAndDayRowSpace = value;
        modifier_->setWeekStyle(node_, &inputValueWeekStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultWeekStyle = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_WEEK_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultWeekStyle, ATTRIBUTE_WEEK_STYLE_I_WEEK_AND_DAY_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_WEEK_STYLE_I_WEEK_AND_DAY_ROW_SPACE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setWeekStyle, attribute: weekStyle.weekAndDayRowSpace";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

} // namespace OHOS::Ace::NG
