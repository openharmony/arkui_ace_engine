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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/implementation/calendar_controller_peer.h"
#include "core/components_ng/pattern/calendar/calendar_event_hub.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"

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

const Ark_Type_CalendarInterface_value calendarOptions {
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
} // namespace

/*
 * @tc.name: setCalendarOptionsTestValidValues1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarModifierTest, DISABLED_setCalendarOptionsTestValidValues1, TestSize.Level1)
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
    calendarOptions2.controller = Converter::ArkValue<Opt_CalendarController, Ark_CalendarController>({
        .ptr = reinterpret_cast<Ark_NativePointer>(&mockControllerPeer)
    });

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
        Ark_Boolean inputValueNeedSlide = initValueNeedSlide;

        inputValueNeedSlide = value;
        modifier_->setNeedSlide(node_, inputValueNeedSlide);
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
    initValueDirection = std::get<1>(testFixtureIntAxisValidValues[0]);

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

    for (auto& [input, value, expected] : testFixtureIntAxisValidValues) {
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
    initValueDirection = std::get<1>(testFixtureIntAxisValidValues[0]);

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

    for (auto& [input, value] : testFixtureIntAxisInvalidValues) {
        checkValue(input, value);
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
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_NE(swiperNode, nullptr);
    std::vector<RefPtr<CalendarEventHub>> eventHubList;
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
    modifier_->setOnSelectChange(node_, &arkCallback);
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
    modifier_->setOnRequestData(node_, &arkCallback);
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
