/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "event/ui_input_event_impl.h"
#include "node/node_model.h"

#include "core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
const int32_t TEST_ID = 1;
const float TEST_FLOAT = 1.0f;
const int64_t TEST_TIME = 1000;
const double TEST_DOUBLE = 1.5;
} // namespace

HWTEST_F(UIInputEventTest, SetPressureByIndex_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressureByIndex(nullptr, TEST_FLOAT, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressureByIndex_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetPressureByIndex(&event, TEST_FLOAT, 0), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetPressureByIndex_NegativeValue, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressureByIndex(&event, -1.0f, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressureByIndex_NegativeIndex, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressureByIndex(&event, TEST_FLOAT, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressureByIndex_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressureByIndex(&event, TEST_FLOAT, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressureByIndex_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressureByIndex(&event, TEST_FLOAT, 0), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetEventTime_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetEventTime(nullptr, TEST_TIME), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetEventTime_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetEventTime(&event, TEST_TIME), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetEventTime_NegativeTime, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetEventTime(&event, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetEventTime_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetEventTime(&event, TEST_TIME), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetEventTime_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetEventTime(&event, TEST_TIME), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetDeviceId_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetDeviceId(nullptr, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetDeviceId_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetDeviceId(&event, TEST_ID), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetDeviceId_NegativeId, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetDeviceId(&event, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetDeviceId_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetDeviceId(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetDeviceId_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetDeviceId(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTargetDisplayId_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTargetDisplayId(nullptr, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTargetDisplayId_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTargetDisplayId(&event, TEST_ID), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetTargetDisplayId_NegativeId, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTargetDisplayId(&event, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTargetDisplayId_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTargetDisplayId(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTargetDisplayId_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTargetDisplayId(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedFingerId_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedFingerId(nullptr, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedFingerId_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedFingerId(&event, TEST_ID), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetChangedFingerId_NegativeId, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedFingerId(&event, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedFingerId_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedFingerId(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedFingerId_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedFingerId(&event, TEST_ID), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetFingerIdByIndex_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetFingerIdByIndex(nullptr, TEST_ID, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetFingerIdByIndex_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetFingerIdByIndex(&event, TEST_ID, 0), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetFingerIdByIndex_NegativeId, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetFingerIdByIndex(&event, -1, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetFingerIdByIndex_NegativeIndex, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetFingerIdByIndex(&event, TEST_ID, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetFingerIdByIndex_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetFingerIdByIndex(&event, TEST_ID, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetFingerIdByIndex_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetFingerIdByIndex(&event, TEST_ID, 0), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetChangedWindowPosition_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetChangedWindowPosition(nullptr, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedWindowPosition_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedWindowPosition(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetChangedWindowPosition_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetChangedWindowPosition(&event, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedWindowPosition_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedWindowPosition(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetWindowPositionByIndex_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetWindowPositionByIndex(nullptr, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetWindowPositionByIndex_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetWindowPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetWindowPositionByIndex_NegativeIndex, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetWindowPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, -1),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetWindowPositionByIndex_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetWindowPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetWindowPositionByIndex_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetWindowPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetChangedScreenPosition_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetChangedScreenPosition(nullptr, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedScreenPosition_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedScreenPosition(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetChangedScreenPosition_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetChangedScreenPosition(&event, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedScreenPosition_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedScreenPosition(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetScreenPositionByIndex_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScreenPositionByIndex(nullptr, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetScreenPositionByIndex_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScreenPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetScreenPositionByIndex_NegativeIndex, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScreenPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, -1),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetScreenPositionByIndex_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScreenPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetScreenPositionByIndex_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScreenPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetChangedGlobalDisplayPosition_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedGlobalDisplayPosition(nullptr, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedGlobalDisplayPosition_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedGlobalDisplayPosition(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetChangedGlobalDisplayPosition_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedGlobalDisplayPosition(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedGlobalDisplayPosition_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedGlobalDisplayPosition(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetGlobalDisplayPositionByIndex_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetGlobalDisplayPositionByIndex(nullptr, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetGlobalDisplayPositionByIndex_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetGlobalDisplayPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetGlobalDisplayPositionByIndex_NegativeIndex, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetGlobalDisplayPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, -1),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetGlobalDisplayPositionByIndex_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetGlobalDisplayPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetGlobalDisplayPositionByIndex_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetGlobalDisplayPositionByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetHandleId_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHandleId(nullptr, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetHandleId_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHandleId(&event, TEST_ID), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetHandleId_NegativeId, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHandleId(&event, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetHandleId_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHandleId(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetHandleId_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHandleId(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTiltAngle_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTiltAngle(nullptr, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTiltAngle_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetTiltAngle(&event, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetTiltAngle_InvalidAngle, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTiltAngle(&event, -91.0f, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTiltAngle_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTiltAngle(&event, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTiltAngle_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetTiltAngle(&event, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetRollAngle_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRollAngle(nullptr, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetRollAngle_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRollAngle(&event, TEST_FLOAT), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetRollAngle_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRollAngle(&event, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetRollAngle_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRollAngle(&event, TEST_FLOAT), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetPressedKeys_NullEvent, TestSize.Level0)
{
    int32_t keys[] = { 1 };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedKeys(nullptr, keys, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedKeys_NotCloned, TestSize.Level0)
{
    int32_t keys[] = { 1 };
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedKeys(&event, keys, 1), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetPressedKeys_NullKeys, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedKeys(&event, nullptr, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedKeys_InvalidLength, TestSize.Level0)
{
    int32_t keys[] = { 1 };
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedKeys(&event, keys, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedKeys_NullInputEvent, TestSize.Level0)
{
    int32_t keys[] = { 1 };
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedKeys(&event, keys, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedKeys_UnsupportedType, TestSize.Level0)
{
    int32_t keys[] = { 1 };
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedKeys(&event, keys, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedTouchArea_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetChangedTouchArea(nullptr, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedTouchArea_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedTouchArea(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetChangedTouchArea_NegativeSize, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedTouchArea(&event, -1.0f, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedTouchArea_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedTouchArea(&event, TEST_FLOAT, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedTouchArea_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedTouchArea(&event, TEST_FLOAT, TEST_FLOAT),
        ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetTouchAreaByIndex_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetTouchAreaByIndex(nullptr, TEST_FLOAT, TEST_FLOAT, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTouchAreaByIndex_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTouchAreaByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetTouchAreaByIndex_NegativeSize, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTouchAreaByIndex(&event, -1.0f, TEST_FLOAT, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTouchAreaByIndex_NegativeIndex, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetTouchAreaByIndex(&event, TEST_FLOAT, TEST_FLOAT, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTouchAreaByIndex_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetTouchAreaByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetTouchAreaByIndex_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetTouchAreaByIndex(&event, TEST_FLOAT, TEST_FLOAT, 0),
        ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetChangedInteractionHand_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedInteractionHand(nullptr, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedInteractionHand_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetChangedInteractionHand(&event, TEST_ID), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetChangedInteractionHand_InvalidHand, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedInteractionHand(&event, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedInteractionHand_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetChangedInteractionHand(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetChangedInteractionHand_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetChangedInteractionHand(&event, TEST_ID), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetInteractionHandByIndex_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetInteractionHandByIndex(nullptr, TEST_ID, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetInteractionHandByIndex_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetInteractionHandByIndex(&event, TEST_ID, 0), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetInteractionHandByIndex_InvalidHand, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetInteractionHandByIndex(&event, -1, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetInteractionHandByIndex_NegativeIndex, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetInteractionHandByIndex(&event, TEST_ID, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetInteractionHandByIndex_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetInteractionHandByIndex(&event, TEST_ID, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetInteractionHandByIndex_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetInteractionHandByIndex(&event, TEST_ID, 0), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetPressedTimeByIndex_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedTimeByIndex(nullptr, TEST_TIME, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedTimeByIndex_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetPressedTimeByIndex(&event, TEST_TIME, 0), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetPressedTimeByIndex_NegativeTime, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedTimeByIndex(&event, -1, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedTimeByIndex_NegativeIndex, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedTimeByIndex(&event, TEST_TIME, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedTimeByIndex_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedTimeByIndex(&event, TEST_TIME, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedTimeByIndex_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetPressedTimeByIndex(&event, TEST_TIME, 0), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetPinchAxisScaleValue_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPinchAxisScaleValue(nullptr, TEST_DOUBLE), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPinchAxisScaleValue_NotCloned, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, &axisEvent, false };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetPinchAxisScaleValue(&event, TEST_DOUBLE), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetPinchAxisScaleValue_NegativeValue, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, &axisEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPinchAxisScaleValue(&event, -1.0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPinchAxisScaleValue_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPinchAxisScaleValue(&event, TEST_DOUBLE), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPinchAxisScaleValue_UnsupportedType, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &axisEvent, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetPinchAxisScaleValue(&event, TEST_DOUBLE), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetHorizontalAxisScaleValue_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHorizontalAxisScaleValue(nullptr, TEST_DOUBLE), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetHorizontalAxisScaleValue_NotCloned, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, &axisEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHorizontalAxisScaleValue(&event, TEST_DOUBLE),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetHorizontalAxisScaleValue_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHorizontalAxisScaleValue(&event, TEST_DOUBLE), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetHorizontalAxisScaleValue_UnsupportedType, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &axisEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetHorizontalAxisScaleValue(&event, TEST_DOUBLE),
        ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetVerticalAxisScaleValue_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetVerticalAxisScaleValue(nullptr, TEST_DOUBLE), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetVerticalAxisScaleValue_NotCloned, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, &axisEvent, false };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetVerticalAxisScaleValue(&event, TEST_DOUBLE), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetVerticalAxisScaleValue_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetVerticalAxisScaleValue(&event, TEST_DOUBLE), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetVerticalAxisScaleValue_UnsupportedType, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &axisEvent, true };
    EXPECT_EQ(
        OH_ArkUI_ClonedEvent_SetVerticalAxisScaleValue(&event, TEST_DOUBLE), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetScrollStep_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScrollStep(nullptr, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetScrollStep_NotCloned, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, &axisEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScrollStep(&event, TEST_ID), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetScrollStep_InvalidStep, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, &axisEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScrollStep(&event, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetScrollStep_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScrollStep(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetScrollStep_UnsupportedType, TestSize.Level0)
{
    ArkUIAxisEvent axisEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &axisEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetScrollStep(&event, TEST_ID), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetMouseButton_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetMouseButton(nullptr, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetMouseButton_NotCloned, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetMouseButton(&event, TEST_ID), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetMouseButton_InvalidButton, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetMouseButton(&event, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetMouseButton_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetMouseButton(&event, TEST_ID), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetMouseButton_UnsupportedType, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &mouseEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetMouseButton(&event, TEST_ID), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetRawDeltaX_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRawDeltaX(nullptr, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetRawDeltaX_NotCloned, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRawDeltaX(&event, TEST_FLOAT), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetRawDeltaX_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRawDeltaX(&event, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetRawDeltaX_UnsupportedType, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &mouseEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRawDeltaX(&event, TEST_FLOAT), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetRawDeltaY_NullEvent, TestSize.Level0)
{
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRawDeltaY(nullptr, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetRawDeltaY_NotCloned, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRawDeltaY(&event, TEST_FLOAT), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetRawDeltaY_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRawDeltaY(&event, TEST_FLOAT), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetRawDeltaY_UnsupportedType, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &mouseEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetRawDeltaY(&event, TEST_FLOAT), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, SetPressedButtons_NullEvent, TestSize.Level0)
{
    int32_t buttons[] = { 1 };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedButtons(nullptr, buttons, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedButtons_NotCloned, TestSize.Level0)
{
    int32_t buttons[] = { 1 };
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent, false };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedButtons(&event, buttons, 1), ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, SetPressedButtons_NullButtons, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedButtons(&event, nullptr, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedButtons_InvalidLength, TestSize.Level0)
{
    int32_t buttons[] = { 1 };
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, &mouseEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedButtons(&event, buttons, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedButtons_NullInputEvent, TestSize.Level0)
{
    int32_t buttons[] = { 1 };
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, nullptr, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedButtons(&event, buttons, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, SetPressedButtons_UnsupportedType, TestSize.Level0)
{
    int32_t buttons[] = { 1 };
    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &mouseEvent, true };
    EXPECT_EQ(OH_ArkUI_ClonedEvent_SetPressedButtons(&event, buttons, 1), ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORT);
}

HWTEST_F(UIInputEventTest, PostClonedEventWithStrategy_NullEvent, TestSize.Level0)
{
    ArkUI_NodeHandle node = reinterpret_cast<ArkUI_NodeHandle>(0x1234);
    EXPECT_EQ(OH_ArkUI_PointerEvent_PostClonedEventWithStrategy(
                  node, nullptr, ArkUI_CompetitionStrategy::ARKUI_COMPETITION_STRATEGY_COMPETITION),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, PostClonedEventWithStrategy_NullNode, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };
    EXPECT_EQ(OH_ArkUI_PointerEvent_PostClonedEventWithStrategy(
                  nullptr, &event, ArkUI_CompetitionStrategy::ARKUI_COMPETITION_STRATEGY_COMPETITION),
        ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL);
}

HWTEST_F(UIInputEventTest, PostClonedEventWithStrategy_NotCloned, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    ArkUI_NodeHandle node = reinterpret_cast<ArkUI_NodeHandle>(0x1234);
    EXPECT_EQ(OH_ArkUI_PointerEvent_PostClonedEventWithStrategy(
                  node, &event, ArkUI_CompetitionStrategy::ARKUI_COMPETITION_STRATEGY_COMPETITION),
        ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

HWTEST_F(UIInputEventTest, PostClonedEventWithStrategy_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    ArkUI_NodeHandle node = reinterpret_cast<ArkUI_NodeHandle>(0x1234);
    EXPECT_EQ(OH_ArkUI_PointerEvent_PostClonedEventWithStrategy(
                  node, &event, ArkUI_CompetitionStrategy::ARKUI_COMPETITION_STRATEGY_COMPETITION),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UIInputEventTest, PostClonedEventWithStrategy_UnsupportedType, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_DIGITAL_CROWN_ID, &touchEvent, true };
    ArkUI_NodeHandle node = reinterpret_cast<ArkUI_NodeHandle>(0x1234);
    EXPECT_EQ(OH_ArkUI_PointerEvent_PostClonedEventWithStrategy(
                  node, &event, ArkUI_CompetitionStrategy::ARKUI_COMPETITION_STRATEGY_COMPETITION),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

} // namespace OHOS::Ace
