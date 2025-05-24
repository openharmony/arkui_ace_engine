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

#include "frameworks/core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetType001, TestSize.Level0)
{
    auto result = OH_ArkUI_UIInputEvent_GetType(nullptr);
    EXPECT_EQ(result, ArkUI_UIInputEvent_Type::ARKUI_UIINPUTEVENT_TYPE_UNKNOWN);
}

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetType002, TestSize.Level0)
{
    std::vector<std::pair<ArkUI_UIInputEvent, ArkUI_UIInputEvent_Type>> testCases = {
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_MOUSE_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_HOVER_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },

        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_MOUSE_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_HOVER_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_TOUCH },

        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, TOUCH_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_MOUSE_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_AXIS },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, C_HOVER_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_AXIS },

        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_TOUCH_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_MOUSE_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_MOUSE, C_HOVER_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_MOUSE },

        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, TOUCH_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_TOUCH_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_MOUSE_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_AXIS_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_KEY_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_FOCUS_AXIS_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_CLICK_EVENT_ID, nullptr },
            ARKUI_UIINPUTEVENT_TYPE_UNKNOWN },
        { ArkUI_UIInputEvent { ARKUI_UIINPUTEVENT_TYPE_KEY, C_HOVER_EVENT_ID, nullptr }, ARKUI_UIINPUTEVENT_TYPE_KEY },
    };

    auto count = 0;
    for (auto testCase : testCases) {
        auto input = testCase.first;
        auto expect = testCase.second;
        auto result = OH_ArkUI_UIInputEvent_GetType(&input);
        EXPECT_EQ(result, expect) << "index = " << count << " : inputtype = " << input.inputType
                                  << " , eventTypeId = " << input.eventTypeId;
        count++;
    }
}

HWTEST_F(UIInputEventTest, OH_ArkUI_UIInputEvent_GetType003, TestSize.Level0)
{
    const int32_t apiVersion = static_cast<int32_t>(OHOS::Ace::PlatformVersion::VERSION_TWENTY);

    std::vector<ArkUI_UIInputEvent_Type> types = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, ARKUI_UIINPUTEVENT_TYPE_TOUCH,
        ARKUI_UIINPUTEVENT_TYPE_AXIS, ARKUI_UIINPUTEVENT_TYPE_MOUSE, ARKUI_UIINPUTEVENT_TYPE_KEY };

    std::vector<ArkUIEventTypeId> typeIds = {
        AXIS_EVENT_ID,
        TOUCH_EVENT_ID,
        C_TOUCH_EVENT_ID,
        C_MOUSE_EVENT_ID,
        C_AXIS_EVENT_ID,
        C_KEY_EVENT_ID,
        C_FOCUS_AXIS_EVENT_ID,
        C_CLICK_EVENT_ID,
        C_HOVER_EVENT_ID,
    };

    auto count = 0;
    for (auto type : types) {
        for (auto typeId : typeIds) {
            auto uiInputEvent = ArkUI_UIInputEvent { type, typeId, nullptr, false, apiVersion };
            auto result = OH_ArkUI_UIInputEvent_GetType(&uiInputEvent);
            EXPECT_EQ(result, type) << "index = " << count << " : inputtype = " << type
                                    << " , eventTypeId = " << typeId;
            count++;
        }
    }
}

} // namespace OHOS::Ace