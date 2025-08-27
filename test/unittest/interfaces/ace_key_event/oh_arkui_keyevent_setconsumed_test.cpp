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

HWTEST_F(KeyEventTest, OH_ArkUI_KeyEvent_SetConsumed001, TestSize.Level0)
{
    OH_ArkUI_KeyEvent_SetConsumed(nullptr, true);
    OH_ArkUI_KeyEvent_SetConsumed(nullptr, false);

    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = C_KEY_EVENT_ID,
        .inputEvent = nullptr,
    };
    OH_ArkUI_KeyEvent_SetConsumed(&event, true);
    OH_ArkUI_KeyEvent_SetConsumed(&event, false);

    EXPECT_EQ(event.inputEvent, nullptr);
}

HWTEST_F(KeyEventTest, OH_ArkUI_KeyEvent_SetConsumed002, TestSize.Level0)
{
    ArkUIKeyEvent keyEvent = {
        .isConsumed = false
    };
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = C_KEY_EVENT_ID,
        .inputEvent = &keyEvent,
        .isCloned = false,
        .apiVersion = 0,
    };

    OH_ArkUI_KeyEvent_SetConsumed(&event, true);
    EXPECT_TRUE(keyEvent.isConsumed);

    OH_ArkUI_KeyEvent_SetConsumed(&event, false);
    EXPECT_FALSE(keyEvent.isConsumed);
}

HWTEST_F(KeyEventTest, OH_ArkUI_KeyEvent_SetConsumed003, TestSize.Level0)
{
    ArkUIKeyEvent keyEvent = {
        .isConsumed = false
    };
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = AXIS_EVENT_ID,
        .inputEvent = &keyEvent,
        .isCloned = false,
        .apiVersion = 0,
    };
    OH_ArkUI_KeyEvent_SetConsumed(&event, true);
    EXPECT_FALSE(keyEvent.isConsumed);

    OH_ArkUI_KeyEvent_SetConsumed(&event, false);
    EXPECT_FALSE(keyEvent.isConsumed);
}
} // namespace OHOS::Ace
