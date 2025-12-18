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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/calendar_controller_peer.h"
#include "core/components_ng/pattern/calendar/calendar_event_hub.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CalendarModifierTest : public ModifierTestBase<
    GENERATED_ArkUICalendarModifier, &GENERATED_ArkUINodeModifiers::getCalendarModifier, GENERATED_ARKUI_CALENDAR> {
};

namespace {
constexpr auto OPTIONS_NAME = "value";
constexpr auto OPTIONS_VALUE = ""; // There is no field in JSON.
constexpr auto ATTRIBUTE_NEED_SLIDE_NAME = "needSlide";
constexpr auto ATTRIBUTE_NEED_SLIDE_DEFAULT_VALUE = "false";
constexpr auto ATTRIBUTE_DIRECTION_NAME = "direction";
constexpr auto ATTRIBUTE_DIRECTION_DEFAULT_VALUE = "1";

constexpr auto ATTRIBUTE_SHOW_LUNAR_NAME = "showLunar";
constexpr auto ATTRIBUTE_SHOW_HOLIDAY_NAME = "showHoliday";
constexpr auto ATTRIBUTE_START_OF_WEEK_NAME = "startOfWeek";
constexpr auto ATTRIBUTE_OFF_DAYS_NAME = "offDays";

constexpr auto ATTRIBUTE_DAY_COLOR_NAME = "dayColor";
constexpr auto ATTRIBUTE_LUNAR_COLOR_NAME = "lunarColor";
constexpr auto ATTRIBUTE_OFF_MARK_LUNAR_COLOR_NAME = "markLunarColor";
constexpr auto ATTRIBUTE_DAY_FONT_SIZE_NAME = "dayFontSize";
constexpr auto ATTRIBUTE_LUNAR_DAY_FONT_SIZE_NAME = "lunarDayFontSize";
constexpr auto ATTRIBUTE_DAY_HEIGHT_NAME = "dayHeight";
constexpr auto ATTRIBUTE_DAY_WIDTH_NAME = "dayWidth";
constexpr auto ATTRIBUTE_GREGORIAN_CALENDAR_HEIGHT_NAME = "gregorianCalendarHeight";
constexpr auto ATTRIBUTE_DAY_Y_AXIS_OFFSET_NAME = "dayYAxisOffset";
constexpr auto ATTRIBUTE_LUNAR_DAY_Y_AXIS_OFFSET_NAME = "lunarDayYAxisOffset";
constexpr auto ATTRIBUTE_UNDERSCORE_X_AXIS_OFFSET_NAME = "underscoreXAxisOffset";
constexpr auto ATTRIBUTE_UNDERSCORE_Y_AXIS_OFFSET_NAME = "underscoreYAxisOffset";
constexpr auto ATTRIBUTE_SCHEDULE_MARKER_X_AXIS_OFFSET_NAME = "scheduleMarkerXAxisOffset";
constexpr auto ATTRIBUTE_SCHEDULE_MARKER_Y_AXIS_OFFSET_NAME = "scheduleMarkerYAxisOffset";
constexpr auto ATTRIBUTE_COL_SPACE_NAME = "colSpace";
constexpr auto ATTRIBUTE_DAILY_FIVE_ROW_SPACE_NAME = "dailyFiveRowSpace";
constexpr auto ATTRIBUTE_DAILY_SIX_ROW_SPACE_NAME = "dailySixRowSpace";
constexpr auto ATTRIBUTE_LUNAR_HEIGHT_NAME = "lunarHeight";
constexpr auto ATTRIBUTE_UNDERSCORE_WIDTH_NAME = "underscoreWidth";
constexpr auto ATTRIBUTE_UNDERSCORE_LENGTH_NAME = "underscoreLength";
constexpr auto ATTRIBUTE_SCHEDULE_MARKER_RADIUS_NAME = "scheduleMarkerRadius";
constexpr auto ATTRIBUTE_BOUNDARY_ROW_OFFSET_NAME = "boundaryRowOffset";
constexpr auto ATTRIBUTE_BOUNDARY_COL_OFFSET_NAME = "boundaryColOffset";

constexpr auto ATTRIBUTE_NON_CURRENT_MONTH_DAY_COLOR_NAME = "nonCurrentMonthDayColor";
constexpr auto ATTRIBUTE_NON_CURRENT_MONTH_LUNAR_COLOR_NAME = "nonCurrentMonthLunarColor";
constexpr auto ATTRIBUTE_NON_CURRENT_MONTH_WORK_DAY_MARK_COLOR_NAME = "nonCurrentMonthWorkDayMarkColor";
constexpr auto ATTRIBUTE_NON_CURRENT_MONTH_OFF_DAY_MARK_COLOR_NAME = "nonCurrentMonthOffDayMarkColor";

constexpr auto ATTRIBUTE_FOCUSED_DAY_COLOR_NAME = "focusedDayColor";
constexpr auto ATTRIBUTE_FOCUSED_LUNAR_COLOR_NAME = "focusedLunarColor";
constexpr auto ATTRIBUTE_FOCUSED_AREA_BACKGROUND_COLOR_NAME = "focusedAreaBackgroundColor";
constexpr auto ATTRIBUTE_FOCUSED_AREA_RADIUS_COLOR_NAME = "focusedAreaRadius";

constexpr auto ATTRIBUTE_WEEK_COLOR_NAME = "weekColor";
constexpr auto ATTRIBUTE_WEEKEND_DAY_COLOR_NAME = "weekendDayColor";
constexpr auto ATTRIBUTE_WEEKEND_LUNAR_COLOR_NAME = "weekendLunarColor";
constexpr auto ATTRIBUTE_WEEK_FONT_SIZE_NAME = "weekFontSize";
constexpr auto ATTRIBUTE_WEEK_HEIGHT_NAME = "weekHeight";
constexpr auto ATTRIBUTE_WEEK_WIDTH_NAME = "weekWidth";
constexpr auto ATTRIBUTE_WEEK_AND_DAY_ROW_SPACE_NAME = "weekAndDayRowSpace";

constexpr auto ATTRIBUTE_WORK_DAY_MARK_COLOR_NAME = "workDayMarkColor";
constexpr auto ATTRIBUTE_OFF_DAY_MARK_COLOR_NAME = "offDayMarkColor";
constexpr auto ATTRIBUTE_WORK_DAY_MARK_SIZE_NAME = "workDayMarkSize";
constexpr auto ATTRIBUTE_OFF_DAY_MARK_SIZE_NAME = "offDayMarkSize";
constexpr auto ATTRIBUTE_WORK_STATE_WIDTH_NAME = "workStateWidth";
constexpr auto ATTRIBUTE_WORK_STATE_HORIZONTAL_MOVING_DISTANCE_NAME = "workStateHorizontalMovingDistance";
constexpr auto ATTRIBUTE_WORK_STATE_VERTICAL_MOVING_DISTANCE_NAME = "workStateVerticalMovingDistance";

constexpr auto ATTRIBUTE_SHOW_LUNAR_DEFAULT_VALUE = "false";
constexpr auto ATTRIBUTE_SHOW_HOLIDAY_DEFAULT_VALUE = "false";
constexpr auto ATTRIBUTE_START_OF_WEEK_DEFAULT_VALUE = "Week.Mon";
constexpr auto ATTRIBUTE_OF_DAYS_DEFAULT_VALUE = "5,6";
constexpr auto RESULT_COLOR_WHITE = "#FFFFFFFF";
constexpr auto RESULT_COLOR_BLACK = "#FF000000";
constexpr auto RESULT_COLOR_BLUE = "#FF0000FF";
constexpr auto RESULT_COLOR_BROWN = "#FFA52A2A";

class MockCalendarController : public OHOS::Ace::NG::CalendarControllerNg {
public:
    MOCK_METHOD(void, SetCalendarPattern, (const WeakPtr<Pattern>&));
};

const std::vector<Ark_CalendarDay> currentDayArray {
    {
        .index = Converter::ArkValue<Ark_Number>(1),
        .lunarMonth = Converter::ArkValue<Ark_String>("two"),
        .lunarDay = Converter::ArkValue<Ark_String>("3"),
        .dayMark = Converter::ArkValue<Ark_String>("three"),
        .dayMarkValue = Converter::ArkValue<Ark_String>("std"),
        .year = Converter::ArkValue<Ark_Number>(2024),
        .month = Converter::ArkValue<Ark_Number>(2),
        .day = Converter::ArkValue<Ark_Number>(1),
        .isFirstOfLunar = Converter::ArkValue<Ark_Boolean>(false),
        .hasSchedule = Converter::ArkValue<Ark_Boolean>(false),
        .markLunarDay = Converter::ArkValue<Ark_Boolean>(false),
    },
};
Converter::ArkArrayHolder<Array_CalendarDay> currentDays(currentDayArray);

const std::vector<Ark_CalendarDay> preDayArray {
    {
        .index = Converter::ArkValue<Ark_Number>(1),
        .lunarMonth = Converter::ArkValue<Ark_String>("one"),
        .lunarDay = Converter::ArkValue<Ark_String>("6"),
        .dayMark = Converter::ArkValue<Ark_String>("six"),
        .dayMarkValue = Converter::ArkValue<Ark_String>("Children's Day"),
        .year = Converter::ArkValue<Ark_Number>(2024),
        .month = Converter::ArkValue<Ark_Number>(1),
        .day = Converter::ArkValue<Ark_Number>(1),
        .isFirstOfLunar = Converter::ArkValue<Ark_Boolean>(true),
        .hasSchedule = Converter::ArkValue<Ark_Boolean>(false),
        .markLunarDay = Converter::ArkValue<Ark_Boolean>(true),
    },
};
Converter::ArkArrayHolder<Array_CalendarDay> preDays(preDayArray);

const std::vector<Ark_CalendarDay> nextDayArray {
    {
        .index = Converter::ArkValue<Ark_Number>(1),
        .lunarMonth = Converter::ArkValue<Ark_String>("three"),
        .lunarDay = Converter::ArkValue<Ark_String>("2"),
        .dayMark = Converter::ArkValue<Ark_String>("two"),
        .dayMarkValue = Converter::ArkValue<Ark_String>("weekend"),
        .year = Converter::ArkValue<Ark_Number>(2024),
        .month = Converter::ArkValue<Ark_Number>(3),
        .day = Converter::ArkValue<Ark_Number>(1),
        .isFirstOfLunar = Converter::ArkValue<Ark_Boolean>(true),
        .hasSchedule = Converter::ArkValue<Ark_Boolean>(true),
        .markLunarDay = Converter::ArkValue<Ark_Boolean>(true),
    },
};
Converter::ArkArrayHolder<Array_CalendarDay> nextDays(nextDayArray);

const Ark_CalendarRequestedMonths calendarOptions {
    .date {
        .year = Converter::ArkValue<Ark_Number>(2024),
        .month = Converter::ArkValue<Ark_Number>(2),
        .day = Converter::ArkValue<Ark_Number>(1),
    },
    .currentData {
        .year = Converter::ArkValue<Ark_Number>(2024),
        .month = Converter::ArkValue<Ark_Number>(2),
        .data = currentDays.ArkValue(),
    },
    .preData {
        .year = Converter::ArkValue<Ark_Number>(2024),
        .month = Converter::ArkValue<Ark_Number>(1),
        .data = preDays.ArkValue(),
    },
    .nextData {
        .year = Converter::ArkValue<Ark_Number>(2024),
        .month = Converter::ArkValue<Ark_Number>(3),
        .data = nextDays.ArkValue(),
    },
    .controller = Converter::ArkValue<Opt_CalendarController>(Ark_Empty()),
};

const std::vector<std::tuple<std::string, Ark_Boolean, std::string>> testFixtureBooleanValidValues = {
    { "true", Converter::ArkValue<Ark_Boolean>(true), "true" },
    { "false", Converter::ArkValue<Ark_Boolean>(false), "false" },
};

const std::vector<std::tuple<std::string, Ark_Axis, std::string>> testFixtureIntAxisValidValues = {
    { "ARK_AXIS_VERTICAL", Converter::ArkValue<Ark_Axis>(ARK_AXIS_VERTICAL), "0" },
    { "ARK_AXIS_HORIZONTAL", Converter::ArkValue<Ark_Axis>(ARK_AXIS_HORIZONTAL), "1" },
};

const std::vector<std::tuple<std::string, Ark_Axis>> testFixtureIntAxisInvalidValues = {
    { "static_cast<Ark_Axis>(-1)", Converter::ArkValue<Ark_Axis>(static_cast<Ark_Axis>(-1)) },
    { "static_cast<Ark_Axis>(INT_MAX)", Converter::ArkValue<Ark_Axis>(static_cast<Ark_Axis>(INT_MAX)) },
};

const std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureOffDaysValidValues = {
    { "1", Converter::ArkValue<Ark_Number>(1), "0"},
    { "2", Converter::ArkValue<Ark_Number>(2), "1" },
};

const std::vector<std::tuple<std::string, Ark_Number, std::string>> testFixtureStartOfWeekValidValues = {
    { "1", Converter::ArkValue<Ark_Number>(0), "Week.Mon"},
    { "0", Converter::ArkValue<Ark_Number>(1), "Week.Tue" },
};
} // namespace

/*
 * @tc.name: setCalendarOptionsTestValidValues1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setCalendarOptionsTestValidValues1, TestSize.Level1)
{
    modifier_->setCalendarOptions(node_, &calendarOptions);
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);

    EXPECT_EQ(GetAttrValue<std::string>(jsonValue, OPTIONS_NAME), OPTIONS_VALUE);
}

/*
 * @tc.name: setCalendarOptionsControllerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setCalendarOptionsControllerTest, TestSize.Level1)
{
    const auto mockController = Referenced::MakeRefPtr<MockCalendarController>();
    CalendarControllerPeer mockControllerPeer { .controller = mockController };
    auto calendarOptions2 = calendarOptions;
    calendarOptions2.controller =
        Converter::ArkValue<Opt_CalendarController, Ark_CalendarController>(&mockControllerPeer);

    EXPECT_CALL(*mockController, SetCalendarPattern(_)).Times(1);
    modifier_->setCalendarOptions(node_, &calendarOptions2);
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
    initValueNeedSlide = std::get<1>(testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueNeedSlide](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        auto inputValueNeedSlide = Converter::ArkValue<Opt_Boolean>(value);
        modifier_->setNeedSlide(node_, &inputValueNeedSlide);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NEED_SLIDE_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setNeedSlide, attribute: needSlide";
    };

    for (auto& [input, value, expected] : testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: showLunarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, showLunarTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonVal = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonVal, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonVal, ATTRIBUTE_SHOW_LUNAR_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_LUNAR_DEFAULT_VALUE)
            << "Default value for attribute 'showLunar'";
    }
}

/*
 * @tc.name: showLunarTestNeedSlideValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, showLunarTestNeedSlideValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowLunar;

    // Initial setup
    initValueShowLunar = std::get<1>(testFixtureBooleanValidValues[0]);
    auto checkValue = [this, &initValueShowLunar](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        auto inputValueShowLunar = Converter::ArkValue<Opt_Boolean>(value);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_FALSE(frameNode->GetChildren().empty());
        auto swiperNode = frameNode->GetChildren().front();
        ASSERT_NE(swiperNode, nullptr);
        modifier_->setShowLunar(node_, &inputValueShowLunar);
        ASSERT_FALSE(swiperNode->GetChildren().empty());
        for (const auto& calendarNode : swiperNode->GetChildren()) {
            auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
            ASSERT_NE(calendarFrameNode, nullptr);
            auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
            ASSERT_NE(calendarPaintProperty, nullptr);
            const InspectorFilter inspector;
            auto jsonVal = JsonUtil::Create(true);
            calendarPaintProperty->ToJsonValue(jsonVal, inspector);
            auto resultStr = GetAttrValue<std::string>(jsonVal, ATTRIBUTE_SHOW_LUNAR_NAME);
            EXPECT_EQ(resultStr, expectedStr)
                 << "Input value is: " << input << ", method: setShowLunar, attribute: showLunar";
        }
    };
    for (auto& [input, value, expected] : testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: showHolidayTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, showHolidayTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonVal = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonVal, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonVal, ATTRIBUTE_SHOW_HOLIDAY_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_SHOW_HOLIDAY_DEFAULT_VALUE)
            << "Default value for attribute 'showHoliday'";
    }
}

/*
 * @tc.name: showHolidayTestNeedSlideValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, showHolidayTestNeedSlideValidValues, TestSize.Level1)
{
    Ark_Boolean initValueShowHoliday;
    initValueShowHoliday = std::get<1>(testFixtureBooleanValidValues[0]);
    auto checkValue = [this, &initValueShowHoliday](
                          const std::string& input, const Ark_Boolean& value, const std::string& expectedStr) {
        auto inputValueShowHoliday = Converter::ArkValue<Opt_Boolean>(value);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_FALSE(frameNode->GetChildren().empty());
        auto swiperNode = frameNode->GetChildren().front();
        ASSERT_NE(swiperNode, nullptr);
        modifier_->setShowHoliday(node_, &inputValueShowHoliday);
        ASSERT_FALSE(swiperNode->GetChildren().empty());
        for (const auto& calendarNode : swiperNode->GetChildren()) {
            auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
            ASSERT_NE(calendarFrameNode, nullptr);
            auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
            ASSERT_NE(calendarPaintProperty, nullptr);
            const InspectorFilter inspector;
            auto jsonVal = JsonUtil::Create(true);
            calendarPaintProperty->ToJsonValue(jsonVal, inspector);
            auto resultStr = GetAttrValue<std::string>(jsonVal, ATTRIBUTE_SHOW_HOLIDAY_NAME);
            EXPECT_EQ(resultStr, expectedStr)
                 << "Input value is: " << input << ", method: setShowHoliday, attribute: showHoliday";
        }
    };
    for (auto& [input, value, expected] : testFixtureBooleanValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: startOfWeekTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, startOfWeekTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonVal = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonVal, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonVal, ATTRIBUTE_START_OF_WEEK_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_START_OF_WEEK_DEFAULT_VALUE)
            << "Default value for attribute 'startOfWeek'";
    }
}

/*
 * @tc.name: startOfWeekTestNeedSlideValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, startOfWeekTestValidValues, TestSize.Level1)
{
    Ark_Number initValuestartOfWeek;
    initValuestartOfWeek = std::get<1>(testFixtureStartOfWeekValidValues[0]);
    auto checkValue = [this, &initValuestartOfWeek](
                          const std::string& input, const  Ark_Number& value, const std::string& expectedStr) {
        auto inputValueStartOfWeek = Converter::ArkValue<Opt_Number>(value);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_FALSE(frameNode->GetChildren().empty());
        auto swiperNode = frameNode->GetChildren().front();
        ASSERT_NE(swiperNode, nullptr);
        modifier_->setStartOfWeek(node_, &inputValueStartOfWeek);
        ASSERT_FALSE(swiperNode->GetChildren().empty());
        for (const auto& calendarNode : swiperNode->GetChildren()) {
            auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
            ASSERT_NE(calendarFrameNode, nullptr);
            auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
            ASSERT_NE(calendarPaintProperty, nullptr);
            const InspectorFilter inspector;
            auto jsonVal = JsonUtil::Create(true);
            calendarPaintProperty->ToJsonValue(jsonVal, inspector);
            auto resultStr = GetAttrValue<std::string>(jsonVal, ATTRIBUTE_START_OF_WEEK_NAME);
            EXPECT_EQ(resultStr, expectedStr)
                 << "Input value is: " << input << ", method: setStartOfWeek, attribute: startOfWeek";
        }
    };
    for (auto& [input, value, expected] : testFixtureStartOfWeekValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: offDaysTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, offDaysTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonVal = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonVal, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonVal, ATTRIBUTE_OFF_DAYS_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_OF_DAYS_DEFAULT_VALUE)
            << "Default value for attribute 'offDays'";
    }
}

/*
 * @tc.name: offDaysTestNeedSlideValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, offDaysTestValidValues, TestSize.Level1)
{
    Ark_Number initValueOffDays;
    initValueOffDays = std::get<1>(testFixtureOffDaysValidValues[0]);
    auto checkValue = [this, &initValueOffDays](
                          const std::string& input, const  Ark_Number& value, const std::string& expectedStr) {
        auto inputValueOffDays = Converter::ArkValue<Opt_Number>(value);
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_FALSE(frameNode->GetChildren().empty());
        auto swiperNode = frameNode->GetChildren().front();
        ASSERT_NE(swiperNode, nullptr);
        modifier_->setOffDays(node_, &inputValueOffDays);
        ASSERT_FALSE(swiperNode->GetChildren().empty());
        for (const auto& calendarNode : swiperNode->GetChildren()) {
            auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
            ASSERT_NE(calendarFrameNode, nullptr);
            auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
            ASSERT_NE(calendarPaintProperty, nullptr);
            const InspectorFilter inspector;
            auto jsonVal = JsonUtil::Create(true);
            calendarPaintProperty->ToJsonValue(jsonVal, inspector);
            auto resultStr = GetAttrValue<std::string>(jsonVal, ATTRIBUTE_OFF_DAYS_NAME);
            EXPECT_EQ(resultStr, expectedStr)
                 << "Input value is: " << input << ", method: setOffDays, attribute: offDays";
        }
    };
    for (auto& [input, value, expected] : testFixtureOffDaysValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDirectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setDirectionTestDefaultValues, TestSize.Level1)
{
    auto jsonValue = GetPatternJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE) << "Default value for attribute 'direction'";
}

/*
 * @tc.name: setDirectionTestDirectionValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setDirectionTestDirectionValidValues, TestSize.Level1)
{
    Ark_Axis initValueDirection;

    // Initial setup
    initValueDirection = std::get<1>(testFixtureIntAxisValidValues[0]);

    auto checkValue = [this, &initValueDirection](
                          const std::string& input, const Ark_Axis& value, const std::string& expectedStr) {
        auto inputValueDirection = Converter::ArkValue<Opt_Axis>(value);
        modifier_->setDirection(node_, &inputValueDirection);
        auto jsonValue = GetPatternJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        EXPECT_EQ(resultStr, expectedStr)
            << "Input value is: " << input << ", method: setDirection, attribute: direction";
    };

    for (auto& [input, value, expected] : testFixtureIntAxisValidValues) {
        checkValue(input, value, expected);
    }
}

/*
 * @tc.name: setDirectionTestDirectionInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setDirectionTestDirectionInvalidValues, TestSize.Level1)
{
    Ark_Axis initValueDirection;

    // Initial setup
    initValueDirection = std::get<1>(testFixtureIntAxisValidValues[0]);

    auto checkValue = [this, &initValueDirection](const std::string& input, const Ark_Axis& value) {
        auto inputValueDirection = Converter::ArkValue<Opt_Axis>(value);
        modifier_->setDirection(node_, &inputValueDirection);
        auto jsonValue = GetPatternJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DIRECTION_NAME);
        EXPECT_EQ(resultStr, ATTRIBUTE_DIRECTION_DEFAULT_VALUE)
            << "Input value is: " << input << ", method: setDirection, attribute: direction";
    };

    for (auto& [input, value] : testFixtureIntAxisInvalidValues) {
        checkValue(input, value);
    }
}

/*
 * @tc.name: currentDayStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, currentDayStyleTest, TestSize.Level1)
{
    Ark_CurrentDayStyle initValue;
    initValue.dayColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE);
    initValue.lunarColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK);
    initValue.markLunarColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE);
    initValue.dayFontSize = Converter::ArkValue<Opt_Number>(0);
    initValue.lunarDayFontSize = Converter::ArkValue<Opt_Number>(1);
    initValue.dayHeight = Converter::ArkValue<Opt_Number>(2);
    initValue.dayWidth = Converter::ArkValue<Opt_Number>(3);
    initValue.gregorianCalendarHeight = Converter::ArkValue<Opt_Number>(4);
    initValue.dayYAxisOffset = Converter::ArkValue<Opt_Number>(5);
    initValue.lunarDayYAxisOffset = Converter::ArkValue<Opt_Number>(6);
    auto optInitValue = Converter::ArkValue<Opt_CurrentDayStyle>(initValue);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    modifier_->setCurrentDayStyle(node_, &optInitValue);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonValue = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonValue, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_WHITE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLACK);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OFF_MARK_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLUE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DAY_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, "0.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LUNAR_DAY_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, "1.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DAY_HEIGHT_NAME);
        EXPECT_EQ(resultStr, "2.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DAY_WIDTH_NAME);
        EXPECT_EQ(resultStr, "3.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_GREGORIAN_CALENDAR_HEIGHT_NAME);
        EXPECT_EQ(resultStr, "4.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DAY_Y_AXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, "5.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LUNAR_DAY_Y_AXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, "6.00vp");
    }
}

/*
 * @tc.name: currentDayStyleTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, currentDayStyleTest2, TestSize.Level1)
{
    Ark_CurrentDayStyle initValue;
    initValue.underscoreXAxisOffset = Converter::ArkValue<Opt_Number>(7);
    initValue.underscoreYAxisOffset = Converter::ArkValue<Opt_Number>(8);
    initValue.scheduleMarkerXAxisOffset = Converter::ArkValue<Opt_Number>(9);
    initValue.scheduleMarkerYAxisOffset = Converter::ArkValue<Opt_Number>(10);
    initValue.colSpace = Converter::ArkValue<Opt_Number>(11);
    initValue.dailyFiveRowSpace = Converter::ArkValue<Opt_Number>(12);
    auto optInitValue = Converter::ArkValue<Opt_CurrentDayStyle>(initValue);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    modifier_->setCurrentDayStyle(node_, &optInitValue);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonValue = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonValue, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNDERSCORE_X_AXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, "7.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNDERSCORE_Y_AXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, "8.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCHEDULE_MARKER_X_AXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, "9.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCHEDULE_MARKER_Y_AXIS_OFFSET_NAME);
        EXPECT_EQ(resultStr, "10.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_COL_SPACE_NAME);
        EXPECT_EQ(resultStr, "11.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DAILY_FIVE_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, "12.00vp");
    }
}

/*
 * @tc.name: currentDayStyleTest3
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, currentDayStyleTest3, TestSize.Level1)
{
    Ark_CurrentDayStyle initValue;
    initValue.dailySixRowSpace = Converter::ArkValue<Opt_Number>(13);
    initValue.lunarHeight = Converter::ArkValue<Opt_Number>(14);
    initValue.underscoreWidth = Converter::ArkValue<Opt_Number>(15);
    initValue.underscoreLength = Converter::ArkValue<Opt_Number>(16);
    initValue.scheduleMarkerRadius = Converter::ArkValue<Opt_Number>(17);
    initValue.boundaryRowOffset = Converter::ArkValue<Opt_Number>(18);
    initValue.boundaryColOffset = Converter::ArkValue<Opt_Number>(19);
    auto optInitValue = Converter::ArkValue<Opt_CurrentDayStyle>(initValue);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    modifier_->setCurrentDayStyle(node_, &optInitValue);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonValue = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonValue, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_DAILY_SIX_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, "13.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_LUNAR_HEIGHT_NAME);
        EXPECT_EQ(resultStr, "14.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNDERSCORE_WIDTH_NAME);
        EXPECT_EQ(resultStr, "15.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_UNDERSCORE_LENGTH_NAME);
        EXPECT_EQ(resultStr, "16.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_SCHEDULE_MARKER_RADIUS_NAME);
        EXPECT_EQ(resultStr, "17.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BOUNDARY_ROW_OFFSET_NAME);
        EXPECT_EQ(resultStr, "18.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_BOUNDARY_COL_OFFSET_NAME);
        EXPECT_EQ(resultStr, "19.00vp");
    }
}

/*
 * @tc.name: nonCurrentDayStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, nonCurrentDayStyleTest, TestSize.Level1)
{
    Ark_NonCurrentDayStyle initValue;
    initValue.nonCurrentMonthDayColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE);
    initValue.nonCurrentMonthLunarColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK);
    initValue.nonCurrentMonthWorkDayMarkColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE);
    initValue.nonCurrentMonthOffDayMarkColor =
        Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BROWN);
    auto optInitValue = Converter::ArkValue<Opt_NonCurrentDayStyle>(initValue);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    modifier_->setNonCurrentDayStyle(node_, &optInitValue);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonValue = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonValue, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NON_CURRENT_MONTH_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_WHITE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NON_CURRENT_MONTH_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLACK);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NON_CURRENT_MONTH_WORK_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLUE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_NON_CURRENT_MONTH_OFF_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BROWN);
    }
}

/*
 * @tc.name: todayStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, todayStyleTest, TestSize.Level1)
{
    Ark_TodayStyle initValue;
    initValue.focusedDayColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE);
    initValue.focusedLunarColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK);
    initValue.focusedAreaBackgroundColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE);
    initValue.focusedAreaRadius = Converter::ArkValue<Opt_Number>(0);
    auto optInitValue = Converter::ArkValue<Opt_TodayStyle>(initValue);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);

    modifier_->setTodayStyle(node_, &optInitValue);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonValue = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonValue, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUSED_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_WHITE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUSED_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLACK);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUSED_AREA_BACKGROUND_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLUE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_FOCUSED_AREA_RADIUS_COLOR_NAME);
        EXPECT_EQ(resultStr, "0.00vp");
    }
}

/*
 * @tc.name: weekStyleTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, weekStyleTest, TestSize.Level1)
{
    Ark_WeekStyle initValue;
    initValue.weekColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE);
    initValue.weekendDayColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK);
    initValue.weekendLunarColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE);
    initValue.weekFontSize = Converter::ArkValue<Opt_Number>(0);
    initValue.weekHeight = Converter::ArkValue<Opt_Number>(1);
    initValue.weekWidth = Converter::ArkValue<Opt_Number>(2);
    initValue.weekAndDayRowSpace = Converter::ArkValue<Opt_Number>(3);
    auto optInitValue = Converter::ArkValue<Opt_WeekStyle>(initValue);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);

    modifier_->setWeekStyle(node_, &optInitValue);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonValue = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonValue, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEEK_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_WHITE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEEKEND_DAY_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLACK);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEEKEND_LUNAR_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLUE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEEK_FONT_SIZE_NAME);
        EXPECT_EQ(resultStr, "0.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEEK_HEIGHT_NAME);
        EXPECT_EQ(resultStr, "1.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEEK_WIDTH_NAME);
        EXPECT_EQ(resultStr, "2.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WEEK_AND_DAY_ROW_SPACE_NAME);
        EXPECT_EQ(resultStr, "3.00vp");
    }
}

/*
 * @tc.name: workStateStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, workStateStyleTest, TestSize.Level1)
{
    Ark_WorkStateStyle initValue;
    initValue.workDayMarkColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE);
    initValue.offDayMarkColor = Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK);
    initValue.workDayMarkSize = Converter::ArkValue<Opt_Number>(0);
    initValue.offDayMarkSize = Converter::ArkValue<Opt_Number>(1);
    initValue.workStateWidth = Converter::ArkValue<Opt_Number>(2);
    initValue.workStateHorizontalMovingDistance = Converter::ArkValue<Opt_Number>(3);
    initValue.workStateVerticalMovingDistance = Converter::ArkValue<Opt_Number>(4);
    auto optInitValue = Converter::ArkValue<Opt_WorkStateStyle>(initValue);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);

    modifier_->setWorkStateStyle(node_, &optInitValue);
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        ASSERT_NE(calendarFrameNode, nullptr);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        ASSERT_NE(calendarPaintProperty, nullptr);
        const InspectorFilter inspector;
        auto jsonValue = JsonUtil::Create(true);
        calendarPaintProperty->ToJsonValue(jsonValue, inspector);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORK_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_WHITE);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OFF_DAY_MARK_COLOR_NAME);
        EXPECT_EQ(resultStr, RESULT_COLOR_BLACK);
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORK_DAY_MARK_SIZE_NAME);
        EXPECT_EQ(resultStr, "0.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_OFF_DAY_MARK_SIZE_NAME);
        EXPECT_EQ(resultStr, "1.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORK_STATE_WIDTH_NAME);
        EXPECT_EQ(resultStr, "2.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORK_STATE_HORIZONTAL_MOVING_DISTANCE_NAME);
        EXPECT_EQ(resultStr, "3.00vp");
        resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_WORK_STATE_VERTICAL_MOVING_DISTANCE_NAME);
        EXPECT_EQ(resultStr, "4.00vp");
    }
}

/*
 * @tc.name: setOnSelectChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setOnSelectChangeTest, TestSize.Level1)
{
    static constexpr auto contextId = 654321;
    static std::vector<Ark_CalendarSelectedDate> checkInvoke;

    modifier_->setCalendarOptions(node_, &calendarOptions);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_FALSE(frameNode->GetChildren().empty());
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    std::vector<RefPtr<CalendarEventHub>> eventHubList;
    ASSERT_FALSE(swiperNode->GetChildren().empty());
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_CONTINUE(calendarFrameNode);
        auto pattern = calendarFrameNode->GetPattern<CalendarMonthPattern>();
        CHECK_NULL_CONTINUE(pattern);
        auto calendarEventHub = pattern->GetEventHub<CalendarEventHub>();
        CHECK_NULL_CONTINUE(calendarEventHub);
        eventHubList.emplace_back(std::move(calendarEventHub));
    }

    auto callback = [](const Ark_Int32 resourceId, const Ark_CalendarSelectedDate event) {
        EXPECT_EQ(resourceId, contextId);
        checkInvoke.emplace_back(std::move(event));
    };
    auto arkCallback = Converter::ArkValue<Callback_CalendarSelectedDate_Void>(callback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_CalendarSelectedDate_Void>(arkCallback);
    modifier_->setOnSelectChange(node_, &optCallback);
    auto json = JsonUtil::Create(true);
    json->Put("day", 31);
    json->Put("month", 12);
    json->Put("year", 2024);
    for (auto&& eventHub : eventHubList) {
        eventHub->UpdateSelectedChangeEvent(json->ToString());
    }

    EXPECT_EQ(checkInvoke.size(), eventHubList.size());
    EXPECT_GT(checkInvoke.size(), 0);
    for (auto&& event : checkInvoke) {
        EXPECT_EQ(Converter::Convert<int32_t>(event.day), 31);
        EXPECT_EQ(Converter::Convert<int32_t>(event.month), 12);
        EXPECT_EQ(Converter::Convert<int32_t>(event.year), 2024);
    }
    checkInvoke.clear();
}

/*
 * @tc.name: setOnRequestDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, setOnRequestDataTest, TestSize.Level1)
{
    static constexpr auto contextId = 0xABCDEF;
    static std::vector<Ark_CalendarRequestedData> checkInvoke;

    modifier_->setCalendarOptions(node_, &calendarOptions);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<CalendarEventHub>();
    ASSERT_NE(eventHub, nullptr);

    auto callback = [](const Ark_Int32 resourceId, const Ark_CalendarRequestedData event) {
        EXPECT_EQ(resourceId, contextId);
        checkInvoke.emplace_back(std::move(event));
    };
    auto arkCallback = Converter::ArkValue<Callback_CalendarRequestedData_Void>(callback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_CalendarRequestedData_Void>(arkCallback);
    modifier_->setOnRequestData(node_, &optCallback);
    auto json = JsonUtil::Create(true);
    json->Put("currentYear", 2000);
    json->Put("currentMonth", 1);
    json->Put("year", 1999);
    json->Put("month", 12);
    json->Put("MonthState", 2);
    eventHub->UpdateRequestDataEvent(json->ToString());

    ASSERT_EQ(checkInvoke.size(), 1);
    auto&& event = checkInvoke[0];
    EXPECT_EQ(Converter::Convert<int32_t>(event.year), 1999);
    EXPECT_EQ(Converter::Convert<int32_t>(event.month), 12);
    EXPECT_EQ(Converter::Convert<int32_t>(event.currentYear), 2000);
    EXPECT_EQ(Converter::Convert<int32_t>(event.currentMonth), 1);
    EXPECT_EQ(Converter::Convert<int32_t>(event.monthState), 2);
    checkInvoke.clear();
}

} // namespace OHOS::Ace::NG
