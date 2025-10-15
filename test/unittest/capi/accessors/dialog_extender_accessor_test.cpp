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
#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/unittest/capi/stubs/mock_text_picker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

namespace OHOS::Ace::NG {

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
HWTEST_F(DialogExtenderAccessorTest, showDatePickerDialogTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->showDatePickerDialog, nullptr);
}
}