/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "key_event_test.h"

#include "frameworks/core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {

HWTEST_F(KeyEventTest, KeyEvent_IsNumLockOn001, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_KeyEvent_IsNumLockOn(nullptr, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(KeyEventTest, KeyEvent_IsNumLockOn002, TestSize.Level0)
{
    bool state = false;
    ArkUI_UIInputEvent event = { .inputEvent = nullptr };
    EXPECT_EQ(OH_ArkUI_KeyEvent_IsNumLockOn(&event, &state), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(KeyEventTest, KeyEvent_IsNumLockOn003, TestSize.Level0)
{
    std::vector<bool> testValues = { true, false };
    int count = 0;
    for (bool val : testValues) {
        ArkUIKeyEvent keyEvent { .isNumLockOn = val };
        ArkUI_UIInputEvent event = {
            .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
            .eventTypeId = C_KEY_EVENT_ID,
            .inputEvent = &keyEvent,
            .isCloned = false,
            .apiVersion = 0,
        };
        bool resultState = !val;
        auto result = OH_ArkUI_KeyEvent_IsNumLockOn(&event, &resultState);
        EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
        EXPECT_EQ(resultState, val) << "index = " << count;
        count++;
    }
}

HWTEST_F(KeyEventTest, KeyEvent_IsNumLockOn004, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = AXIS_EVENT_ID,
        .inputEvent = nullptr,
        .isCloned = false,
        .apiVersion = 0,
    };
    bool state = false;
    EXPECT_EQ(OH_ArkUI_KeyEvent_IsNumLockOn(&event, &state), ARKUI_ERROR_CODE_PARAM_INVALID);
}
} // namespace OHOS::Ace
