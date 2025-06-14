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
#include "interfaces/native/ui_input_event.h"
#include "interfaces/native/event/ui_input_event_impl.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY_Null, TestSize.Level0)
{
    float result = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f) << "event is nullptr, should return 0.0f";
}

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY_AllCases, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    touchEvent.targetGlobalPositionY = 10.1f;

    OHOS::Ace::TouchEvent baseTouchEvent = {};
    baseTouchEvent.targetGlobalPositionY = 11;

    ArkUIAxisEvent axisEvent = {};
    axisEvent.targetGlobalPositionY = 12.3f;

    OHOS::Ace::AxisEvent baseAxisEvent = {};
    baseAxisEvent.targetGlobalPositionY = 13.4f;

    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.targetGlobalPositionY = 14.5f;

    ArkUIHoverEvent hoverEvent = {};
    hoverEvent.targetGlobalPositionY = 15.6f;

    ArkUIClickEvent clickEvent = {};
    clickEvent.targetGlobalPositionY = 16.7f;

    ArkUIFocusAxisEvent focusAxisEvent = {};
    focusAxisEvent.targetGlobalPositionY = 17.8f;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent },      10.1f },
        { { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID, &baseTouchEvent },   11 },
        { { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, &axisEvent },        12.3f },
        { { ARKUI_UIINPUTEVENT_TYPE_AXIS, AXIS_EVENT_ID, &baseAxisEvent },      13.4f },
        { { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent },     14.5f },
        { { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_HOVER_EVENT_ID, &hoverEvent },     15.6f },
        { { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_CLICK_EVENT_ID, &clickEvent },     16.7f },
        { { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_FOCUS_AXIS_EVENT_ID, &focusAxisEvent }, 17.8f },

        { { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr },         0.0f },
        { { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_KEY_EVENT_ID, &touchEvent },        0.0f },
        { { ARKUI_UIINPUTEVENT_TYPE_MOUSE, AXIS_EVENT_ID, &mouseEvent },        0.0f },
    };

    int count = 0;
    for (const auto& test : testCases) {
        float result = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(&test.first);
        EXPECT_FLOAT_EQ(result, test.second)
            << "index=" << count
            << " : inputType=" << test.first.inputType
            << " , eventTypeId=" << test.first.eventTypeId
            << " , expect=" << test.second
            << " , got=" << result;
        count++;
    }
}

} // namespace OHOS::Ace
