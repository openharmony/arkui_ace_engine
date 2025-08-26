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

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation_NullEvent, TestSize.Level0)
{
    int32_t result = OH_ArkUI_PointerEvent_SetStopPropagation(nullptr, true);
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID)
        << "event is nullptr, expected ERROR_CODE_PARAM_INVALID, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_AXIS_EVENT_ID, &touchEvent };
    int32_t result = OH_ArkUI_PointerEvent_SetStopPropagation(&inputEvent, true);
    EXPECT_EQ(result, ERROR_CODE_PARAM_INVALID)
        << "Unsupported eventTypeId, expected ERROR_CODE_PARAM_INVALID, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation_TouchEvent, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    touchEvent.stopPropagation = false;
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent };
    int32_t result = OH_ArkUI_PointerEvent_SetStopPropagation(&inputEvent, true);
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR) << "C_TOUCH_EVENT_ID, expected ERROR_CODE_NO_ERROR, got " << result;
    EXPECT_TRUE(touchEvent.stopPropagation) << "stopPropagation should be set to true";

    result = OH_ArkUI_PointerEvent_SetStopPropagation(&inputEvent, false);
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR) << "C_TOUCH_EVENT_ID, expected ERROR_CODE_NO_ERROR, got " << result;
    EXPECT_FALSE(touchEvent.stopPropagation) << "stopPropagation should be set to false";
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation_MouseEvent, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.stopPropagation = false;
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent };
    int32_t result = OH_ArkUI_PointerEvent_SetStopPropagation(&inputEvent, true);
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR) << "C_MOUSE_EVENT_ID, expected ERROR_CODE_NO_ERROR, got " << result;
    EXPECT_TRUE(mouseEvent.stopPropagation) << "stopPropagation should be set to true";

    result = OH_ArkUI_PointerEvent_SetStopPropagation(&inputEvent, false);
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR) << "C_MOUSE_EVENT_ID, expected ERROR_CODE_NO_ERROR, got " << result;
    EXPECT_FALSE(mouseEvent.stopPropagation) << "stopPropagation should be set to false";
}

HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_SetStopPropagation_HoverEvent, TestSize.Level0)
{
    ArkUIHoverEvent hoverEvent = {};
    hoverEvent.stopPropagation = false;
    ArkUI_UIInputEvent inputEvent = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_HOVER_EVENT_ID, &hoverEvent };
    int32_t result = OH_ArkUI_PointerEvent_SetStopPropagation(&inputEvent, true);
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR) << "C_HOVER_EVENT_ID, expected ERROR_CODE_NO_ERROR, got " << result;
    EXPECT_TRUE(hoverEvent.stopPropagation) << "stopPropagation should be set to true";

    result = OH_ArkUI_PointerEvent_SetStopPropagation(&inputEvent, false);
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR) << "C_HOVER_EVENT_ID, expected ERROR_CODE_NO_ERROR, got " << result;
    EXPECT_FALSE(hoverEvent.stopPropagation) << "stopPropagation should be set to false";
}

} // namespace OHOS::Ace
