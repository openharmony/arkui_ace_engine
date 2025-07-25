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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_PointerEvent_DestroyClonedEvent001
 * @tc.desc: Test with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_DestroyClonedEvent001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_DestroyClonedEvent(nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_DestroyClonedEvent002
 * @tc.desc: Test with non-cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_DestroyClonedEvent002, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, &touchEvent, false };

    auto result = OH_ArkUI_PointerEvent_DestroyClonedEvent(&event);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_DestroyClonedEvent003
 * @tc.desc: Test with null inputEvent in cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_DestroyClonedEvent003, TestSize.Level0)
{
    // Test all unsupported event types
    std::vector<std::pair<ArkUI_UIInputEvent_Type, ArkUIEventTypeId>> unsupportedEventTypes = {
        { ARKUI_UIINPUTEVENT_TYPE_AXIS, AXIS_EVENT_ID },            // AXIS_EVENT_ID = 0
        { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID },        // C_MOUSE_EVENT_ID = 3
        { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID },          // C_AXIS_EVENT_ID = 4
        { ARKUI_UIINPUTEVENT_TYPE_KEY, C_KEY_EVENT_ID },            // C_KEY_EVENT_ID = 5
        { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID }, // C_FOCUS_AXIS_EVENT_ID = 6
        { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID },      // C_CLICK_EVENT_ID = 7
        { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID },      // C_HOVER_EVENT_ID = 8
    };

    for (const auto& [inputType, eventTypeId] : unsupportedEventTypes) {
        ArkUI_UIInputEvent* event = new ArkUI_UIInputEvent { inputType, eventTypeId, nullptr, true };

        auto result = OH_ArkUI_PointerEvent_DestroyClonedEvent(event);
        EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR) << "Failed for event type: " << static_cast<int>(eventTypeId);
        delete event; // Clean up the allocated memory
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_DestroyClonedEvent101
 * @tc.desc: Test successful destruction of valid cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_DestroyClonedEvent101, TestSize.Level0)
{
    // Create a valid cloned event
    ArkUITouchEvent* touchEvent = new ArkUITouchEvent {};
    ArkUI_UIInputEvent* event =
        new ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, touchEvent, true };

    auto result = OH_ArkUI_PointerEvent_DestroyClonedEvent(event);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_DestroyClonedEvent102
 * @tc.desc: Test with unsupported event type (mouse event)
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_DestroyClonedEvent102, TestSize.Level0)
{
    ArkUITouchEvent* touchEvent = new ArkUITouchEvent {};
    ArkUI_UIInputEvent* event =
        new ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, touchEvent, true };

    auto result = OH_ArkUI_PointerEvent_DestroyClonedEvent(event);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    if (result != ARKUI_ERROR_CODE_NO_ERROR) {
        delete touchEvent;
        delete event;
    }
}

} // namespace OHOS::Ace