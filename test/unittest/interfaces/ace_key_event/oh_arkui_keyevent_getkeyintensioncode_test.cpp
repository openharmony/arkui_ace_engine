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

#include "key_event_test.h"

#include "frameworks/core/common/ace_application_info.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {

HWTEST_F(KeyEventTest, KeyEvent_GetKeyIntentionCode001, TestSize.Level0)
{
    auto result = OH_ArkUI_KeyEvent_GetKeyIntensionCode(nullptr);
    EXPECT_EQ(result, static_cast<ArkUI_KeyIntension>(-1));
}

HWTEST_F(KeyEventTest, KeyEvent_GetKeyIntentionCode002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = C_KEY_EVENT_ID,
        .inputEvent = nullptr,
        .isCloned = false,
        .apiVersion = 0,
    };
    auto result = OH_ArkUI_KeyEvent_GetKeyIntensionCode(&event);
    EXPECT_EQ(result, static_cast<ArkUI_KeyIntension>(-1));
}

HWTEST_F(KeyEventTest, KeyEvent_GetKeyIntentionCode003, TestSize.Level0)
{
    std::vector<ArkUI_KeyIntension> intensions = {
        ARKUI_KEY_INTENSION_UP,
        ARKUI_KEY_INTENSION_LEFT,
        ARKUI_KEY_INTENTION_MEDIA_PLAY_PAUSE,
        ARKUI_KEY_INTENTION_VOLUME_DOWN,
        ARKUI_KEY_INTENTION_CAMERA
    };

    int count = 0;
    for (auto intention : intensions) {
        ArkUIKeyEvent keyEvent { .intentionCode = static_cast<int32_t>(intention) };
        ArkUI_UIInputEvent event = {
            .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
            .eventTypeId = C_KEY_EVENT_ID,
            .inputEvent = &keyEvent,
            .isCloned = false,
            .apiVersion = 0,
        };
        auto result = OH_ArkUI_KeyEvent_GetKeyIntensionCode(&event);
        EXPECT_EQ(result, intention) << "index = " << count << " : expected intention = " << intention;
        count++;
    }
}

HWTEST_F(KeyEventTest, KeyEvent_GetKeyIntentionCode004, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = AXIS_EVENT_ID,
        .inputEvent = nullptr,
        .isCloned = false,
        .apiVersion = 0,
    };
    auto result = OH_ArkUI_KeyEvent_GetKeyIntensionCode(&event);
    EXPECT_EQ(result, static_cast<ArkUI_KeyIntension>(-1));
}
} // namespace OHOS::Ace
