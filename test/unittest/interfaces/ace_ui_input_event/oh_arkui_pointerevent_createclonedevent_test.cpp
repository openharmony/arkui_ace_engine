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
#include "event/ui_input_event_impl.h"

#include "core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_PointerEvent_CreateClonedEvent001
 * @tc.desc: Test with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_CreateClonedEvent001, TestSize.Level0)
{
    ArkUI_UIInputEvent* clonedEvent = nullptr;
    auto result = OH_ArkUI_PointerEvent_CreateClonedEvent(nullptr, &clonedEvent);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(clonedEvent, nullptr);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_CreateClonedEvent002
 * @tc.desc: Test with null clonedEvent pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_CreateClonedEvent002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr, false };
    auto result = OH_ArkUI_PointerEvent_CreateClonedEvent(&event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_CreateClonedEvent003
 * @tc.desc: Test with null inputEvent in source event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_CreateClonedEvent003, TestSize.Level0)
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
        ArkUITouchEvent inputEvent;
        ArkUI_UIInputEvent event = { inputType, eventTypeId, &inputEvent, false };
        ArkUI_UIInputEvent* clonedEvent = nullptr;

        auto result = OH_ArkUI_PointerEvent_CreateClonedEvent(&event, &clonedEvent);
        EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
        ASSERT_EQ(clonedEvent, nullptr) << "Failed for event type: " << static_cast<int>(eventTypeId);
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_CreateClonedEvent004
 * @tc.desc: Test with unsupported event types
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_CreateClonedEvent004, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, nullptr, false };
    ArkUI_UIInputEvent* clonedEvent = nullptr;
    auto result = OH_ArkUI_PointerEvent_CreateClonedEvent(&event, &clonedEvent);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    ASSERT_EQ(clonedEvent, nullptr);

    ArkUI_UIInputEvent event2 = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr, false };
    ArkUI_UIInputEvent* clonedEvent2 = nullptr;
    auto result2 = OH_ArkUI_PointerEvent_CreateClonedEvent(&event2, &clonedEvent2);
    EXPECT_EQ(result2, ARKUI_ERROR_CODE_PARAM_INVALID);
    ASSERT_EQ(clonedEvent2, nullptr);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_CreateClonedEvent101
 * @tc.desc: Test successful creation of cloned touch event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_CreateClonedEvent101, TestSize.Level0)
{
    // Test all unsupported event types
    std::vector<std::pair<ArkUI_UIInputEvent_Type, ArkUIEventTypeId>> unsupportedEventTypes = {
        { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID },   // TOUCH_EVENT_ID = 1
        { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID }, // C_TOUCH_EVENT_ID = 2
    };

    for (const auto& [inputType, eventTypeId] : unsupportedEventTypes) {
        ArkUI_UIInputEvent event = { inputType, eventTypeId, nullptr, false };
        ArkUI_UIInputEvent* clonedEvent = nullptr;
        auto result = OH_ArkUI_PointerEvent_CreateClonedEvent(&event, &clonedEvent);
        EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
        ASSERT_EQ(clonedEvent, nullptr) << "Failed for event type: " << static_cast<int>(eventTypeId);
    }
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_CreateClonedEvent102
 * @tc.desc: Test with different touch event types
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_CreateClonedEvent102, TestSize.Level0)
{
    // Test all unsupported event types
    std::vector<std::pair<ArkUI_UIInputEvent_Type, ArkUIEventTypeId>> unsupportedEventTypes = {
        { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID },   // TOUCH_EVENT_ID = 1
        { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID }, // C_TOUCH_EVENT_ID = 2
    };

    for (const auto& [inputType, eventTypeId] : unsupportedEventTypes) {
        ArkUITouchEvent inputEvent;
        ArkUI_UIInputEvent event = { inputType, eventTypeId, &inputEvent, false };
        ArkUI_UIInputEvent* clonedEvent = nullptr;
        auto result = OH_ArkUI_PointerEvent_CreateClonedEvent(&event, &clonedEvent);
        EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
        ASSERT_NE(clonedEvent, nullptr) << "Failed for event type: " << static_cast<int>(eventTypeId);
        OH_ArkUI_PointerEvent_DestroyClonedEvent(clonedEvent);
    }
}

} // namespace OHOS::Ace