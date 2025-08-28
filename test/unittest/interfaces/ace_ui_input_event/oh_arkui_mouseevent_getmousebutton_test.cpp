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

#include "../ui_input_event_test.h"
#include "interfaces/native/event/ui_input_event_impl.h"
#include "interfaces/native/ui_input_event.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseButton_NullEvent, TestSize.Level0)
{
    int32_t result = OH_ArkUI_MouseEvent_GetMouseButton(nullptr);
    EXPECT_EQ(result, -1);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseButton_EventTypeNotMouse, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.button = 1; // Left button
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_CLICK_EVENT_ID, // Not mouse event
        &mouseEvent };
    int32_t result = OH_ArkUI_MouseEvent_GetMouseButton(&inputEvent);
    EXPECT_EQ(result, -1);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseButton_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, nullptr };
    int32_t result = OH_ArkUI_MouseEvent_GetMouseButton(&inputEvent);
    EXPECT_EQ(result, -1);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseButton_Normal, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.button = 1; // Left button
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent };
    int32_t result = OH_ArkUI_MouseEvent_GetMouseButton(&inputEvent);
    EXPECT_EQ(result, 1);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseButton_ButtonVariants, TestSize.Level0)
{
    struct ButtonTestCase {
        int32_t rawButton; // Raw button value from event
        int32_t expected;  // Expected converted value
        const char* desc;
    };
    std::vector<ButtonTestCase> cases = { { 0, 0, "No button pressed" }, { 1, 1, "Left button pressed" },
        { 2, 2, "Right button pressed" }, { 4, 3, "Middle button pressed" }, { 8, 4, "Back button pressed" },
        { 16, 5, "Forward button pressed" }, { 3, 0, "Invalid combination" }, { 32, 0, "Unsupported button" } };

    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent };
    int count = 0;
    for (const auto& testCase : cases) {
        mouseEvent.button = testCase.rawButton;
        int32_t result = OH_ArkUI_MouseEvent_GetMouseButton(&inputEvent);
        EXPECT_EQ(result, testCase.expected)
            << "Test case " << count << " failed: " << testCase.desc << ", rawButton=" << testCase.rawButton
            << ", expected=" << testCase.expected << ", actual=" << result;
        count++;
    }
}

} // namespace OHOS::Ace