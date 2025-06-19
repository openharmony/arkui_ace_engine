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

HWTEST_F(UIInputEventTest, OH_ArkUI_HoverEvent_IsHovered_NullEvent, TestSize.Level0)
{
    auto result = OH_ArkUI_HoverEvent_IsHovered(nullptr);
    EXPECT_FALSE(result) << "Input event is nullptr, expected false, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_HoverEvent_IsHovered_EventTypeNotHover, TestSize.Level0)
{
    ArkUIHoverEvent hoverEvent = {};
    hoverEvent.isHover = 1;
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_CLICK_EVENT_ID,
        &hoverEvent
    };
    auto result = OH_ArkUI_HoverEvent_IsHovered(&inputEvent);
    EXPECT_FALSE(result) << "eventTypeId != C_HOVER_EVENT_ID, expected false, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_HoverEvent_IsHovered_NullInputEvent, TestSize.Level0)
{
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_HOVER_EVENT_ID,
        nullptr
    };
    auto result = OH_ArkUI_HoverEvent_IsHovered(&inputEvent);
    EXPECT_FALSE(result) << "inputEvent is nullptr, expected false, got " << result;
}

HWTEST_F(UIInputEventTest, OH_ArkUI_HoverEvent_IsHovered_IsHoverVariants, TestSize.Level0)
{
    ArkUIHoverEvent hoverEvent = {};
    ArkUI_UIInputEvent inputEvent = {
        ARKUI_UIINPUTEVENT_TYPE_MOUSE,
        C_HOVER_EVENT_ID,
        &hoverEvent
    };

    struct HoverTestCase {
        int32_t isHover;
        bool expected;
        const char* desc;
    };
    std::vector<HoverTestCase> cases = {
        { 0, false, "isHover = 0" },
        { 1, true,  "isHover = 1" },
        { -1, true, "isHover = -1 (nonzero treated as true)" },
        { 999, true, "isHover = 999 (nonzero treated as true)" }
    };
    int count = 0;
    for (const auto& testCase : cases) {
        hoverEvent.isHover = testCase.isHover;
        auto result = OH_ArkUI_HoverEvent_IsHovered(&inputEvent);
        EXPECT_EQ(result, testCase.expected) << "index = " << count
            << " : " << testCase.desc << ", actual = " << result;
        count++;
    }
}

} // namespace OHOS::Ace
