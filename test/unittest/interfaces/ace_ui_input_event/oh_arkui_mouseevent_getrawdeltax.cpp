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

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX_NullEvent, TestSize.Level0)
{
    float result = OH_ArkUI_MouseEvent_GetRawDeltaX(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f) << "Input event is nullptr, expected 0.0f, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX_EventTypeNotMouse, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.rawDeltaX = 1.23f;
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_CLICK_EVENT_ID,
        &mouseEvent
    };
    float result = OH_ArkUI_MouseEvent_GetRawDeltaX(&inputEvent);
    EXPECT_FLOAT_EQ(result, 0.0f) << "eventTypeId != C_MOUSE_EVENT_ID, expected 0.0f, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_MOUSE_EVENT_ID,
        nullptr
    };
    float result = OH_ArkUI_MouseEvent_GetRawDeltaX(&inputEvent);
    EXPECT_FLOAT_EQ(result, 0.0f) << "inputEvent is nullptr, expected 0.0f, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX_Normal, TestSize.Level0)
{
    ArkUIMouseEvent mouseEvent = {};
    mouseEvent.rawDeltaX = 5.67f;
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_MOUSE_EVENT_ID,
        &mouseEvent
    };
    float result = OH_ArkUI_MouseEvent_GetRawDeltaX(&inputEvent);
    EXPECT_FLOAT_EQ(result, mouseEvent.rawDeltaX)
        << "C_MOUSE_EVENT_ID, expect rawDeltaX=" << mouseEvent.rawDeltaX << ", actual=" << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_MouseEvent_GetRawDeltaX_Variants, TestSize.Level0)
{
    struct DeltaXTestCase {
        float value;
        const char* desc;
    };
    std::vector<DeltaXTestCase> cases = {
        { 0.0f, "rawDeltaX = 0.0f" },
        { -10.0f, "rawDeltaX = -10.0f" },
        { 10000.123f, "rawDeltaX = 10000.123f" }
    };

    ArkUIMouseEvent mouseEvent = {};
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_MOUSE_EVENT_ID,
        &mouseEvent
    };
    int count = 0;
    for (const auto& testCase : cases) {
        mouseEvent.rawDeltaX = testCase.value;
        float result = OH_ArkUI_MouseEvent_GetRawDeltaX(&inputEvent);
        EXPECT_FLOAT_EQ(result, testCase.value)
            << "index = " << count << " : " << testCase.desc << ", actual = " << result;
        count++;
    }
}

} // namespace OHOS::Ace
