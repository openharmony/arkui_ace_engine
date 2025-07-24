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
 * @tc.name: OH_ArkUI_PointerEvent_PostClonedEvent001
 * @tc.desc: Test with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_PostClonedEvent001, TestSize.Level0)
{
    auto result = OH_ArkUI_PointerEvent_PostClonedEvent(nullptr, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_PostClonedEvent002
 * @tc.desc: Test with null node handle
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_PostClonedEvent002, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, true };

    auto result = OH_ArkUI_PointerEvent_PostClonedEvent(nullptr, &event);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL);
}

/**
 * @tc.name: OH_ArkUI_PointerEvent_PostClonedEvent003
 * @tc.desc: Test with non-cloned event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_PostClonedEvent003, TestSize.Level0)
{
    ArkUITouchEvent touchEvent = {};
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, &touchEvent, false };
    ArkUI_NodeHandle node = reinterpret_cast<ArkUI_NodeHandle>(0x1234);

    auto result = OH_ArkUI_PointerEvent_PostClonedEvent(node, &event);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT);
}

/**`
 * @tc.name: OH_ArkUI_PointerEvent_PostClonedEvent004
 * @tc.desc: Test with null inputEvent in event
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_PointerEvent_PostClonedEvent004, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_TOUCH, C_TOUCH_EVENT_ID, nullptr, true };
    ArkUI_NodeHandle node = reinterpret_cast<ArkUI_NodeHandle>(0x1234);

    auto result = OH_ArkUI_PointerEvent_PostClonedEvent(node, &event);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

} // namespace OHOS::Ace
