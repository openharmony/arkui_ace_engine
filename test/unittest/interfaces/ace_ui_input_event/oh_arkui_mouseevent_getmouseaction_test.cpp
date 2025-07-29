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

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseAction_NullEvent, TestSize.Level0)
{
    int32_t result = OH_ArkUI_MouseEvent_GetMouseAction(nullptr);
    EXPECT_EQ(result, -1) << "Input event is nullptr, expected -1, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseAction_EventTypeNotMouse, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.action = 1; // Press action
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_CLICK_EVENT_ID, // Not mouse event
        &mouseEvent };
    int32_t result = OH_ArkUI_MouseEvent_GetMouseAction(&inputEvent);
    EXPECT_EQ(result, -1);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseAction_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, nullptr };
    int32_t result = OH_ArkUI_MouseEvent_GetMouseAction(&inputEvent);
    EXPECT_EQ(result, -1);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseAction_Normal, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.action = 1; // Press action
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent };
    int32_t result = OH_ArkUI_MouseEvent_GetMouseAction(&inputEvent);
    EXPECT_EQ(result, 1);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseAction_ActionVariants, TestSize.Level0)
{
    struct ActionTestCase {
        int32_t rawAction; // Raw action value from event
        int32_t expected;  // Expected converted value
        const char* desc;
    };
    std::vector<ActionTestCase> cases = { { 0, 0, "No action" }, { 1, 1, "Press action" }, { 2, 2, "Release action" },
        { 3, 3, "Move action" }, { 4, 0, "Hover enter (unsupported)" }, { 5, 0, "Hover exit (unsupported)" },
        { 6, 0, "Drag action (unsupported)" }, { 7, 0, "Unsupported action type" } };

    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent };
    int count = 0;
    for (const auto& testCase : cases) {
        mouseEvent.action = testCase.rawAction;
        int32_t result = OH_ArkUI_MouseEvent_GetMouseAction(&inputEvent);
        EXPECT_EQ(result, testCase.expected)
            << "Test case " << count << " failed: " << testCase.desc << ", rawAction=" << testCase.rawAction
            << ", expected=" << testCase.expected << ", actual=" << result;
        count++;
    }
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetMouseAction_ConvertedValues, TestSize.Level0)
{
    // Test that the conversion function returns expected values
    EXPECT_EQ(OHOS::Ace::NodeModel::ConvertToCMouseActionType(1), 1) << "Press action conversion failed";
    EXPECT_EQ(OHOS::Ace::NodeModel::ConvertToCMouseActionType(2), 2) << "Release action conversion failed";
    EXPECT_EQ(OHOS::Ace::NodeModel::ConvertToCMouseActionType(3), 3) << "Move action conversion failed";
    EXPECT_EQ(OHOS::Ace::NodeModel::ConvertToCMouseActionType(4), 0) << "Unsupported action should return 0";
}

} // namespace OHOS::Ace