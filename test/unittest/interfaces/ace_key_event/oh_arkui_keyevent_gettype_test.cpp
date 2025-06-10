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

HWTEST_F(KeyEventTest, KeyEvent_GetType001, TestSize.Level0)
{
    auto result = OH_ArkUI_KeyEvent_GetType(nullptr);
    EXPECT_EQ(result, ArkUI_KeyEventType::ARKUI_KEY_EVENT_UNKNOWN);
}

HWTEST_F(KeyEventTest, KeyEvent_GetType002, TestSize.Level0)
{
    // Prepare test cases for event pointer null and wrong input type scenarios
    std::vector<std::pair<ArkUI_UIInputEvent, ArkUI_KeyEventType>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_KEY_EVENT_ID, nullptr }, ARKUI_KEY_EVENT_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID, nullptr }, ARKUI_KEY_EVENT_UNKNOWN },
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto inputEvent = testCase.first;
        auto expect = testCase.second;
        auto result = OH_ArkUI_KeyEvent_GetType(&inputEvent);
        EXPECT_EQ(result, expect) << "index = " << count << " : inputType = " << inputEvent.inputType
                                  << " , eventTypeId = " << inputEvent.eventTypeId;
        count++;
    }
}

HWTEST_F(KeyEventTest, KeyEvent_GetType003, TestSize.Level0)
{
    std::vector<ArkUI_KeyEventType> keyTypes = {
        ARKUI_KEY_EVENT_DOWN,
        ARKUI_KEY_EVENT_UP,
        ARKUI_KEY_EVENT_LONG_PRESS,
        ARKUI_KEY_EVENT_CLICK,
    };

    int count = 0;
    for (auto type : keyTypes) {
        ArkUIKeyEvent keyEvent { .type = static_cast<int32_t>(type) };
        ArkUI_UIInputEvent event = {
            .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
            .eventTypeId = C_KEY_EVENT_ID,
            .inputEvent = &keyEvent,
            .isCloned = false,
            .apiVersion = 0,
        };
        auto result = OH_ArkUI_KeyEvent_GetType(&event);
        EXPECT_EQ(result, type) << "index = " << count << " : expected = " << type;
        count++;
    }
}

} // namespace OHOS::Ace
