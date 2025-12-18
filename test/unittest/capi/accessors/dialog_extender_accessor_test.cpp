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
#include "accessor_test_base.h"
#include "gmock/gmock.h"
#include "node_api.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/unittest/capi/stubs/mock_date_picker_dialog.h"

#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace {
typedef std::pair<Ark_Date, PickerDate> PickerDateTestPlanStep;
const std::vector<PickerDateTestPlanStep> DATE_TEST_PLAN = {
    { Converter::ArkValue<Ark_Date>("2025-06-22T08:01:33"), PickerDate(2025, 06, 22) },
    { Converter::ArkValue<Ark_Date>("2023-01-29T08:01:33"), PickerDate(2025, 01, 29) },
    { Converter::ArkValue<Ark_Date>("2027-12-31T08:01:33"), PickerDate(2027, 12, 31) }
};
} // namespace

using namespace testing;
using namespace testing::ext;

class DialogExtenderAccessorTest : public StaticAccessorTest<GENERATED_ArkUIDialogExtenderAccessor,
    &GENERATED_ArkUIAccessors::getDialogExtenderAccessor> {
};

/**
 * @tc.name: showTextPickerDialogTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DialogExtenderAccessorTest, showTextPickerDialogTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showTextPickerDialog, nullptr);
}

/**
 * @tc.name: showTimePickerDialogTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DialogExtenderAccessorTest, showTimePickerDialogTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showTimePickerDialog, nullptr);
}

/**
 * @tc.name: showDatePickerDialogTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DialogExtenderAccessorTest, DISABLED_showDatePickerDialogTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showDatePickerDialog, nullptr);
    PickerDialogInfo dialogInfo;

    for (const auto& [date, expected] : DATE_TEST_PLAN) {
        Ark_DatePickerDialogOptions options {
            .selected = Converter::ArkUnion<Opt_Union_Date_Bindable_Date, Ark_Date>(date)
        };
        accessor_->showDatePickerDialog(&options);
        dialogInfo = MockDatePickerDialog::GetDialogInfo();
        auto selectedDate = dialogInfo.parseSelectedDate;
        EXPECT_EQ(selectedDate.GetYear(), expected.GetYear());
        EXPECT_EQ(selectedDate.GetMonth(), expected.GetMonth());
        EXPECT_EQ(selectedDate.GetDay(), expected.GetDay());
    }
}
} // namespace OHOS::Ace::NG