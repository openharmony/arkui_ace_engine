/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "test_fixtures.h"
#include "type_helpers.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_MARK_TODAY_NAME = "markToday";
const auto ATTRIBUTE_MARK_TODAY_DEFAULT_VALUE = "false";
} // namespace

class CalendarPickerModifierTest
    : public ModifierTestBase<GENERATED_ArkUICalendarPickerModifier,
          &GENERATED_ArkUINodeModifiers::getCalendarPickerModifier, GENERATED_ARKUI_CALENDAR_PICKER> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }
};

/*
 * @tc.name: setMarkTodayTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerModifierTest, setMarkTodayTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MARK_TODAY_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_MARK_TODAY_DEFAULT_VALUE) << "Default value for attribute 'markToday'";
}

/*
 * @tc.name: setMarkTodayTestMarkTodayValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerModifierTest, setMarkTodayTestMarkTodayValidValues, TestSize.Level1)
{
    Ark_Boolean initValueMarkToday;

    // Initial setup
    initValueMarkToday = std::get<1>(Fixtures::testFixtureBooleanValidValues[0]);

    auto checkValue = [this, &initValueMarkToday](
                          const std::string& input, const std::string& expectedStr, const Ark_Boolean& value) {
        Ark_Boolean inputValueMarkToday = initValueMarkToday;

        inputValueMarkToday = value;
        modifier_->setMarkToday(node_, inputValueMarkToday);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_MARK_TODAY_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setMarkToday, attribute: markToday";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureBooleanValidValues) {
        checkValue(input, expected, value);
    }
}
} // namespace OHOS::Ace::NG
