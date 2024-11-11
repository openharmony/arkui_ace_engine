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
 * @tc.name: setCalendarOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCalendarOptionsTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultValue = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_VALUE_NAME);
    std::unique_ptr<JsonValue> resultDate =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultValue, ATTRIBUTE_VALUE_I_DATE_NAME);
    std::unique_ptr<JsonValue> resultCurrentData =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultValue, ATTRIBUTE_VALUE_I_CURRENT_DATA_NAME);
    std::unique_ptr<JsonValue> resultPreData =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultValue, ATTRIBUTE_VALUE_I_PRE_DATA_NAME);
    std::unique_ptr<JsonValue> resultNextData =
        GetAttrValue<std::unique_ptr<JsonValue>>(resultValue, ATTRIBUTE_VALUE_I_NEXT_DATA_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultDate, ATTRIBUTE_VALUE_I_DATE_I_YEAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_DATE_I_YEAR_DEFAULT_VALUE)
        << "Default value for attribute 'value.date.year'";

    resultStr = GetAttrValue<std::string>(resultDate, ATTRIBUTE_VALUE_I_DATE_I_MONTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_DATE_I_MONTH_DEFAULT_VALUE)
        << "Default value for attribute 'value.date.month'";

    resultStr = GetAttrValue<std::string>(resultDate, ATTRIBUTE_VALUE_I_DATE_I_DAY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_DATE_I_DAY_DEFAULT_VALUE) << "Default value for attribute 'value.date.day'";

    resultStr = GetAttrValue<std::string>(resultCurrentData, ATTRIBUTE_VALUE_I_CURRENT_DATA_I_YEAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_CURRENT_DATA_I_YEAR_DEFAULT_VALUE)
        << "Default value for attribute 'value.currentData.year'";

    resultStr = GetAttrValue<std::string>(resultCurrentData, ATTRIBUTE_VALUE_I_CURRENT_DATA_I_MONTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_CURRENT_DATA_I_MONTH_DEFAULT_VALUE)
        << "Default value for attribute 'value.currentData.month'";

    resultStr = GetAttrValue<std::string>(resultCurrentData, ATTRIBUTE_VALUE_I_CURRENT_DATA_I_DATA_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_CURRENT_DATA_I_DATA_DEFAULT_VALUE)
        << "Default value for attribute 'value.currentData.data'";

    resultStr = GetAttrValue<std::string>(resultPreData, ATTRIBUTE_VALUE_I_PRE_DATA_I_YEAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_PRE_DATA_I_YEAR_DEFAULT_VALUE)
        << "Default value for attribute 'value.preData.year'";

    resultStr = GetAttrValue<std::string>(resultPreData, ATTRIBUTE_VALUE_I_PRE_DATA_I_MONTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_PRE_DATA_I_MONTH_DEFAULT_VALUE)
        << "Default value for attribute 'value.preData.month'";

    resultStr = GetAttrValue<std::string>(resultPreData, ATTRIBUTE_VALUE_I_PRE_DATA_I_DATA_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_PRE_DATA_I_DATA_DEFAULT_VALUE)
        << "Default value for attribute 'value.preData.data'";

    resultStr = GetAttrValue<std::string>(resultNextData, ATTRIBUTE_VALUE_I_NEXT_DATA_I_YEAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_NEXT_DATA_I_YEAR_DEFAULT_VALUE)
        << "Default value for attribute 'value.nextData.year'";

    resultStr = GetAttrValue<std::string>(resultNextData, ATTRIBUTE_VALUE_I_NEXT_DATA_I_MONTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_NEXT_DATA_I_MONTH_DEFAULT_VALUE)
        << "Default value for attribute 'value.nextData.month'";

    resultStr = GetAttrValue<std::string>(resultNextData, ATTRIBUTE_VALUE_I_NEXT_DATA_I_DATA_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_NEXT_DATA_I_DATA_DEFAULT_VALUE)
        << "Default value for attribute 'value.nextData.data'";

    resultStr = GetAttrValue<std::string>(resultValue, ATTRIBUTE_VALUE_I_CONTROLLER_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_VALUE_I_CONTROLLER_DEFAULT_VALUE)
        << "Default value for attribute 'value.controller'";
}

/*
 * @tc.name: setCalendarOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCalendarOptionsTestValidValues, TestSize.Level1)
{
    FAIL() << "Need to properly configure fixtures in configuration file for proper test generation!";
}

/*
 * @tc.name: setShowLunarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setShowLunarTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_LUNAR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_LUNAR_DEFAULT_VALUE) << "Default value for attribute 'showLunar'";
}

/*
 * @tc.name: setShowLunarTestShowLunarValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setShowLunarTestShowLunarValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowLunar;

    // Initial setup
    initValueShowLunar = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueShowLunar](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueShowLunar = initValueShowLunar;

        inputValueShowLunar = value;
        modifier_->setShowLunar(node_, inputValueShowLunar);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_LUNAR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setShowLunar, attribute: showLunar";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setShowHolidayTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setShowHolidayTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_HOLIDAY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_HOLIDAY_DEFAULT_VALUE) << "Default value for attribute 'showHoliday'";
}

/*
 * @tc.name: setShowHolidayTestShowHolidayValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setShowHolidayTestShowHolidayValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowHoliday;

    // Initial setup
    initValueShowHoliday = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueShowHoliday](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueShowHoliday = initValueShowHoliday;

        inputValueShowHoliday = value;
        modifier_->setShowHoliday(node_, inputValueShowHoliday);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SHOW_HOLIDAY_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setShowHoliday, attribute: showHoliday";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setNeedSlideTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setNeedSlideTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NEED_SLIDE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_NEED_SLIDE_DEFAULT_VALUE) << "Default value for attribute 'needSlide'";
}

/*
 * @tc.name: setNeedSlideTestNeedSlideValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setNeedSlideTestNeedSlideValidValues, TestSize.Level1)
{
    Ark_Boolean initValueNeedSlide;

    // Initial setup
    initValueNeedSlide = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueNeedSlide](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        Ark_Boolean inputValueNeedSlide = initValueNeedSlide;

        inputValueNeedSlide = value;
        modifier_->setNeedSlide(node_, inputValueNeedSlide);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NEED_SLIDE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNeedSlide, attribute: needSlide";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setStartOfWeekTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setStartOfWeekTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_START_OF_WEEK_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_START_OF_WEEK_DEFAULT_VALUE) << "Default value for attribute 'startOfWeek'";
}

/*
 * @tc.name: setStartOfWeekTestStartOfWeekValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setStartOfWeekTestStartOfWeekValidValues, TestSize.Level1)
{
    Ark_Number initValueStartOfWeek;

    // Initial setup
    initValueStartOfWeek = std::get<1>(Fixtures::testFixtureWeekDaysValidValues[0]);

    auto checkValue = [this, &initValueStartOfWeek](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueStartOfWeek = initValueStartOfWeek;

        inputValueStartOfWeek = value;
        modifier_->setStartOfWeek(node_, &inputValueStartOfWeek);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_START_OF_WEEK_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setStartOfWeek, attribute: startOfWeek";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureWeekDaysValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setStartOfWeekTestStartOfWeekInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setStartOfWeekTestStartOfWeekInvalidValues, TestSize.Level1)
{
    Ark_Number initValueStartOfWeek;

    // Initial setup
    initValueStartOfWeek = std::get<1>(Fixtures::testFixtureWeekDaysValidValues[0]);

    auto checkValue = [this, &initValueStartOfWeek](const std::string& input, const Ark_Number& value) {
        Ark_Number inputValueStartOfWeek = initValueStartOfWeek;

        modifier_->setStartOfWeek(node_, &inputValueStartOfWeek);
        inputValueStartOfWeek = value;
        modifier_->setStartOfWeek(node_, &inputValueStartOfWeek);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_START_OF_WEEK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_START_OF_WEEK_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setStartOfWeek, attribute: startOfWeek";
    };

    for (auto& [input, value] : Fixtures::testFixtureWeekDaysInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setOffDaysTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setOffDaysTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OFF_DAYS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_OFF_DAYS_DEFAULT_VALUE) << "Default value for attribute 'offDays'";
}

/*
 * @tc.name: setOffDaysTestOffDaysValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setOffDaysTestOffDaysValidValues, TestSize.Level1)
{
    Ark_Number initValueOffDays;

    // Initial setup
    initValueOffDays = std::get<1>(Fixtures::testFixtureOffDayBitsValidValues[0]);

    auto checkValue = [this, &initValueOffDays](
                          const std::string& input, const Ark_Number& value, const std::string& expectedStr) {
        Ark_Number inputValueOffDays = initValueOffDays;

        inputValueOffDays = value;
        modifier_->setOffDays(node_, &inputValueOffDays);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OFF_DAYS_NAME);
        EXPECT_EQ(resultStr, expectedStr) << "Input value is: " << input << ", method: setOffDays, attribute: offDays";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureOffDayBitsValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setOffDaysTestOffDaysInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setOffDaysTestOffDaysInvalidValues, TestSize.Level1)
{
    Ark_Number initValueOffDays;

    // Initial setup
    initValueOffDays = std::get<1>(Fixtures::testFixtureOffDayBitsValidValues[0]);

    auto checkValue = [this, &initValueOffDays](const std::string& input, const Ark_Number& value) {
        Ark_Number inputValueOffDays = initValueOffDays;

        modifier_->setOffDays(node_, &inputValueOffDays);
        inputValueOffDays = value;
        modifier_->setOffDays(node_, &inputValueOffDays);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OFF_DAYS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OFF_DAYS_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setOffDays, attribute: offDays";
    };

    for (auto& [input, value] : Fixtures::testFixtureOffDayBitsInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setDirectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setDirectionTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE) << "Default value for attribute 'direction'";
}

/*
 * @tc.name: setDirectionTestDirectionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setDirectionTestDirectionValidValues, TestSize.Level1)
{
    Ark_Axis initValueDirection;

    // Initial setup
    initValueDirection = std::get<1>(Fixtures::testFixtureIntAxisValidValues[0]);

    auto checkValue = [this, &initValueDirection](
                          const std::string& input, const Ark_Axis& value, const std::string& expectedStr) {
        Ark_Axis inputValueDirection = initValueDirection;

        inputValueDirection = value;
        modifier_->setDirection(node_, inputValueDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDirection, attribute: direction";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureIntAxisValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDirectionTestDirectionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setDirectionTestDirectionInvalidValues, TestSize.Level1)
{
    Ark_Axis initValueDirection;

    // Initial setup
    initValueDirection = std::get<1>(Fixtures::testFixtureIntAxisValidValues[0]);

    auto checkValue = [this, &initValueDirection](const std::string& input, const Ark_Axis& value) {
        Ark_Axis inputValueDirection = initValueDirection;

        modifier_->setDirection(node_, inputValueDirection);
        inputValueDirection = value;
        modifier_->setDirection(node_, inputValueDirection);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setDirection, attribute: direction";
    };

    for (auto& [input, value] : Fixtures::testFixtureIntAxisInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::unique_ptr<JsonValue> resultCurrentDayStyle =
        GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.dayColor'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.lunarColor'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_MARK_LUNAR_COLOR_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_MARK_LUNAR_COLOR_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.markLunarColor'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_FONT_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.dayFontSize'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_FONT_SIZE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_FONT_SIZE_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.lunarDayFontSize'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_HEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.dayHeight'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_WIDTH_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.dayWidth'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_GREGORIAN_CALENDAR_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_GREGORIAN_CALENDAR_HEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.gregorianCalendarHeight'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_YAXIS_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_YAXIS_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.dayYAxisOffset'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_YAXIS_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_YAXIS_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.lunarDayYAxisOffset'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_XAXIS_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_XAXIS_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.underscoreXAxisOffset'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_YAXIS_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_YAXIS_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.underscoreYAxisOffset'";

    resultStr = GetAttrValue<std::string>(
        resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_XAXIS_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_XAXIS_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.scheduleMarkerXAxisOffset'";

    resultStr = GetAttrValue<std::string>(
        resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_YAXIS_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_YAXIS_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.scheduleMarkerYAxisOffset'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_COL_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_COL_SPACE_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.colSpace'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_FIVE_ROW_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_FIVE_ROW_SPACE_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.dailyFiveRowSpace'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_SIX_ROW_SPACE_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAILY_SIX_ROW_SPACE_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.dailySixRowSpace'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_HEIGHT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_HEIGHT_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.lunarHeight'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_WIDTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_WIDTH_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.underscoreWidth'";

    resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_LENGTH_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_LENGTH_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.underscoreLength'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_RADIUS_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_RADIUS_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.scheduleMarkerRadius'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_ROW_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_ROW_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.boundaryRowOffset'";

    resultStr =
        GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_COL_OFFSET_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_BOUNDARY_COL_OFFSET_DEFAULT_VALUE)
        << "Default value for attribute 'currentDayStyle.boundaryColOffset'";
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayColorValidValues, TestSize.Level1)
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
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.dayColor = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayColor";
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
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayColorInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.dayColor = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayColor";
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
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleLunarColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleLunarColorValidValues, TestSize.Level1)
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
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.lunarColor = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.lunarColor";
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
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleLunarColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleLunarColorInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.lunarColor = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.lunarColor";
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
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleMarkLunarColorValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleMarkLunarColorValidValues, TestSize.Level1)
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
                          const std::string& input, const Opt_ResourceColor& value, const std::string& expectedStr) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        inputValueCurrentDayStyle.markLunarColor = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_MARK_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.markLunarColor";
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
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleMarkLunarColorInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleMarkLunarColorInvalidValues, TestSize.Level1)
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

    auto checkValue = [this, &initValueCurrentDayStyle](const std::string& input, const Opt_ResourceColor& value) {
        Ark_CurrentDayStyle inputValueCurrentDayStyle = initValueCurrentDayStyle;

        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        inputValueCurrentDayStyle.markLunarColor = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_MARK_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_MARK_LUNAR_COLOR_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.markLunarColor";
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
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayFontSizeValidValues, TestSize.Level1)
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

        inputValueCurrentDayStyle.dayFontSize = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayFontSizeInvalidValues, TestSize.Level1)
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
        inputValueCurrentDayStyle.dayFontSize = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_FONT_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayFontSize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleLunarDayFontSizeValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleLunarDayFontSizeValidValues, TestSize.Level1)
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

        inputValueCurrentDayStyle.lunarDayFontSize = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.lunarDayFontSize";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleLunarDayFontSizeInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleLunarDayFontSizeInvalidValues, TestSize.Level1)
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
        inputValueCurrentDayStyle.lunarDayFontSize = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_FONT_SIZE_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.lunarDayFontSize";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayHeightValidValues, TestSize.Level1)
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

        inputValueCurrentDayStyle.dayHeight = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayHeightInvalidValues, TestSize.Level1)
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
        inputValueCurrentDayStyle.dayHeight = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_HEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayHeight";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayWidthValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayWidthValidValues, TestSize.Level1)
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

        inputValueCurrentDayStyle.dayWidth = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_WIDTH_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayWidth";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayWidthInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayWidthInvalidValues, TestSize.Level1)
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
        inputValueCurrentDayStyle.dayWidth = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_WIDTH_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_WIDTH_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayWidth";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleGregorianCalendarHeightValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleGregorianCalendarHeightValidValues,
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

        inputValueCurrentDayStyle.gregorianCalendarHeight = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_GREGORIAN_CALENDAR_HEIGHT_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.gregorianCalendarHeight";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleGregorianCalendarHeightInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleGregorianCalendarHeightInvalidValues,
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
        inputValueCurrentDayStyle.gregorianCalendarHeight = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_GREGORIAN_CALENDAR_HEIGHT_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_GREGORIAN_CALENDAR_HEIGHT_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.gregorianCalendarHeight";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayYAxisOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayYAxisOffsetValidValues, TestSize.Level1)
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

        inputValueCurrentDayStyle.dayYAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_YAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayYAxisOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleDayYAxisOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleDayYAxisOffsetInvalidValues, TestSize.Level1)
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
        inputValueCurrentDayStyle.dayYAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_YAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_DAY_YAXIS_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.dayYAxisOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleLunarDayYAxisOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(
    CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleLunarDayYAxisOffsetValidValues, TestSize.Level1)
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

        inputValueCurrentDayStyle.lunarDayYAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_YAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.lunarDayYAxisOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleLunarDayYAxisOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleLunarDayYAxisOffsetInvalidValues,
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
        inputValueCurrentDayStyle.lunarDayYAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr =
            GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_YAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_LUNAR_DAY_YAXIS_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.lunarDayYAxisOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleUnderscoreXAxisOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleUnderscoreXAxisOffsetValidValues,
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

        inputValueCurrentDayStyle.underscoreXAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_XAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.underscoreXAxisOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleUnderscoreXAxisOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleUnderscoreXAxisOffsetInvalidValues,
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
        inputValueCurrentDayStyle.underscoreXAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_XAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_XAXIS_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.underscoreXAxisOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleUnderscoreYAxisOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleUnderscoreYAxisOffsetValidValues,
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

        inputValueCurrentDayStyle.underscoreYAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_YAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.underscoreYAxisOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleUnderscoreYAxisOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleUnderscoreYAxisOffsetInvalidValues,
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
        inputValueCurrentDayStyle.underscoreYAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_YAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_UNDERSCORE_YAXIS_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.underscoreYAxisOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleScheduleMarkerXAxisOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleScheduleMarkerXAxisOffsetValidValues,
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

        inputValueCurrentDayStyle.scheduleMarkerXAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_XAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.scheduleMarkerXAxisOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleScheduleMarkerXAxisOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleScheduleMarkerXAxisOffsetInvalidValues,
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
        inputValueCurrentDayStyle.scheduleMarkerXAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_XAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_XAXIS_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.scheduleMarkerXAxisOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleScheduleMarkerYAxisOffsetValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleScheduleMarkerYAxisOffsetValidValues,
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

        inputValueCurrentDayStyle.scheduleMarkerYAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_YAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.scheduleMarkerYAxisOffset";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleScheduleMarkerYAxisOffsetInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleScheduleMarkerYAxisOffsetInvalidValues,
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
        inputValueCurrentDayStyle.scheduleMarkerYAxisOffset = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(
            resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_YAXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_SCHEDULE_MARKER_YAXIS_OFFSET_DEFAULT_VALUE)
            << "Input value is: " << input
            << ", method: setCurrentDayStyle, attribute: currentDayStyle.scheduleMarkerYAxisOffset";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleColSpaceValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleColSpaceValidValues, TestSize.Level1)
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

        inputValueCurrentDayStyle.colSpace = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_COL_SPACE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.colSpace";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureNumberAnythingValidValues) {
        checkValue(input, ArkValue<Opt_Number>(value), expected);
    }
}

/*
 * @tc.name: setCurrentDayStyleTestCurrentDayStyleColSpaceInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCurrentDayStyleTestCurrentDayStyleColSpaceInvalidValues, TestSize.Level1)
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
        inputValueCurrentDayStyle.colSpace = value;
        modifier_->setCurrentDayStyle(node_, &inputValueCurrentDayStyle);
        auto jsonValue = GetJsonValue(node_);
        auto resultCurrentDayStyle =
            GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CURRENT_DAY_STYLE_NAME);
        auto resultStr = GetAttrValue<std::string>(resultCurrentDayStyle, ATTRIBUTE_CURRENT_DAY_STYLE_I_COL_SPACE_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_CURRENT_DAY_STYLE_I_COL_SPACE_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setCurrentDayStyle, attribute: currentDayStyle.colSpace";
    };

    // Check empty optional
    checkValue("undefined", ArkValue<Opt_Number>());
}

} // namespace OHOS::Ace::NG
