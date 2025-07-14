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
#include "securec.h"
#include "frameworks/core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {

HWTEST_F(KeyEventTest, KeyEvent_GetKeyText001, TestSize.Level0)
{
    auto result = OH_ArkUI_KeyEvent_GetKeyText(nullptr);
    EXPECT_EQ(result, nullptr);
}

HWTEST_F(KeyEventTest, KeyEvent_GetKeyText002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = C_KEY_EVENT_ID,
        .inputEvent = nullptr,
        .isCloned = false,
        .apiVersion = 0,
    };
    auto result = OH_ArkUI_KeyEvent_GetKeyText(&event);
    EXPECT_EQ(result, nullptr);
}

HWTEST_F(KeyEventTest, KeyEvent_GetKeyText003, TestSize.Level0)
{
    const char* testText = "A";
    ArkUIKeyEvent keyEvent { .type = ARKUI_KEY_EVENT_DOWN, .keyCode = 65 };
    std::size_t maxLen  = sizeof(keyEvent.keyText);
    std::size_t copyLen = std::min(strlen(testText), maxLen - 1);
    errno_t ret = strncpy_s(keyEvent.keyText, maxLen, testText, copyLen);
    ASSERT_EQ(ret, 0);
    keyEvent.keyText[copyLen] = '\0';

    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = C_KEY_EVENT_ID,
        .inputEvent = &keyEvent,
        .isCloned = false,
        .apiVersion = 0,
    };
    auto result = OH_ArkUI_KeyEvent_GetKeyText(&event);
    EXPECT_STREQ(result, testText);
}

} // namespace OHOS::Ace
