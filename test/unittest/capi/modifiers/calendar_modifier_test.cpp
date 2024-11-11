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
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CalendarModifierTest : public ModifierTestBase<
    GENERATED_ArkUICalendarModifier, &GENERATED_ArkUINodeModifiers::getCalendarModifier, GENERATED_ARKUI_CALENDAR> {
};

namespace {
constexpr auto OPTIONS_NAME = "value";
constexpr auto OPTIONS_VALUE = ""; // There is no field in JSON.

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

} // namespace OHOS::Ace::NG
