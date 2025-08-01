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

HWTEST_F(KeyEventTest, KeyEvent_GetKeyCode001, TestSize.Level0)
{
    auto result = OH_ArkUI_KeyEvent_GetKeyCode(nullptr);
    EXPECT_EQ(result, -1);
}

HWTEST_F(KeyEventTest, KeyEvent_GetKeyCode002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = C_KEY_EVENT_ID,
        .inputEvent = nullptr,
        .isCloned = false,
        .apiVersion = 0,
    };
    auto result = OH_ArkUI_KeyEvent_GetKeyCode(&event);
    EXPECT_EQ(result, -1);
}

HWTEST_F(KeyEventTest, KeyEvent_GetKeyCode003, TestSize.Level0)
{
    std::vector<int32_t> testKeyCodes = { 0, 1, 13, 255 };
    int count = 0;
    for (int32_t code : testKeyCodes) {
        ArkUIKeyEvent keyEvent { .type = ARKUI_KEY_EVENT_DOWN, .keyCode = code };
        ArkUI_UIInputEvent event = {
            .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
            .eventTypeId = C_KEY_EVENT_ID,
            .inputEvent = &keyEvent,
            .isCloned = false,
            .apiVersion = 0,
        };
        auto result = OH_ArkUI_KeyEvent_GetKeyCode(&event);
        EXPECT_EQ(result, code) << "index = " << count << " : expected keyCode = " << code;
        count++;
    }
}

HWTEST_F(KeyEventTest, KeyEvent_GetKeyCode004, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = AXIS_EVENT_ID,
        .inputEvent = nullptr,
        .isCloned = false,
        .apiVersion = 0,
    };
    auto result = OH_ArkUI_KeyEvent_GetKeyCode(&event);
    EXPECT_EQ(result, -1);
}
} // namespace OHOS::Ace
