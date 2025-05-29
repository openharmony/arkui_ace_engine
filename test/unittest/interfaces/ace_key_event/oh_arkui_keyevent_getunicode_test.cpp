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

HWTEST_F(KeyEventTest, KeyEvent_GetUnicode001, TestSize.Level0)
{
    auto result = OH_ArkUI_KeyEvent_GetUnicode(nullptr);
    EXPECT_EQ(result, 0u);
}

HWTEST_F(KeyEventTest, KeyEvent_GetUnicode002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = {
        .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
        .eventTypeId = C_KEY_EVENT_ID,
        .inputEvent = nullptr,
        .isCloned = false,
        .apiVersion = 0,
    };
    auto result = OH_ArkUI_KeyEvent_GetUnicode(&event);
    EXPECT_EQ(result, 0u);
}

HWTEST_F(KeyEventTest, KeyEvent_GetUnicode003, TestSize.Level0)
{
    std::vector<uint32_t> unicodeValues = { 65, 97, 8364, 0x1F600 }; // A, a, €, 😀
    int count = 0;
    for (auto unicode : unicodeValues) {
        ArkUIKeyEvent keyEvent { .unicode = static_cast<int32_t>(unicode) };
        ArkUI_UIInputEvent event = {
            .inputType = ARKUI_UIINPUTEVENT_TYPE_KEY,
            .eventTypeId = C_KEY_EVENT_ID,
            .inputEvent = &keyEvent,
            .isCloned = false,
            .apiVersion = 0,
        };
        auto result = OH_ArkUI_KeyEvent_GetUnicode(&event);
        EXPECT_EQ(result, unicode) << "index = " << count << " : expected unicode = " << unicode;
        count++;
    }
}

} // namespace OHOS::Ace