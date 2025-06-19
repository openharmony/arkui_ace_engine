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

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX_Null, TestSize.Level0)
{
    float result = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f) << "event is nullptr, should return 0.0f";
}

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX_AllCases, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    touchEvent.targetGlobalPositionX = 1.1f;

    OHOS::Ace::TouchEvent baseTouchEvent = {};
    baseTouchEvent.targetGlobalPositionX = 2;

    ArkUIAxisEvent axisEvent = {};
    axisEvent.targetGlobalPositionX = 3.3f;

    OHOS::Ace::AxisEvent baseAxisEvent = {};
    baseAxisEvent.targetGlobalPositionX = 4.4f;

    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.targetGlobalPositionX = 5.5f;

    ArkUIHoverEvent hoverEvent = {};
    hoverEvent.targetGlobalPositionX = 6.6f;

    ArkUIClickEvent clickEvent = {};
    clickEvent.targetGlobalPositionX = 7.7f;

    ArkUIFocusAxisEvent focusAxisEvent = {};
    focusAxisEvent.targetGlobalPositionX = 8.8f;

    std::vector<std::pair<ArkUI_UIInputEvent, float>> testCases = {
        { { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent },      1.1f },
        { { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID, &baseTouchEvent },   2 },
        { { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, &axisEvent },        3.3f },
        { { ARKUI_UIINPUTEVENT_TYPE_AXIS, AXIS_EVENT_ID, &baseAxisEvent },      4.4f },
        { { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent },     5.5f },
        { { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_HOVER_EVENT_ID, &hoverEvent },     6.6f },
        { { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_CLICK_EVENT_ID, &clickEvent },     7.7f },
        { { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_FOCUS_AXIS_EVENT_ID, &focusAxisEvent }, 8.8f },

        { { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr },         0.0f },
        { { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_KEY_EVENT_ID, &touchEvent },        0.0f },
        { { ARKUI_UIINPUTEVENT_TYPE_MOUSE, AXIS_EVENT_ID, &mouseEvent },        0.0f },
    };

    int count = 0;
    for (const auto& test : testCases) {
        float result = OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(&test.first);
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
