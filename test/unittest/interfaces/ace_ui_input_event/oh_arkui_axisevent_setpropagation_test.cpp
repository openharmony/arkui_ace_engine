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

#include "frameworks/base/error/error_code.h" // Include the header with error code definitions

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

/**
 * @tc.name: OH_ArkUI_AxisEvent_SetPropagation001
 * @tc.desc: Test OH_ArkUI_AxisEvent_SetPropagation with null event pointer
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_SetPropagation001, TestSize.Level0)
{
    auto result = OH_ArkUI_AxisEvent_SetPropagation(nullptr, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_SetPropagation002
 * @tc.desc: Test OH_ArkUI_AxisEvent_SetPropagation with unsupported event type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_SetPropagation002, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_TOUCH_EVENT_ID, nullptr };
    auto result = OH_ArkUI_AxisEvent_SetPropagation(&event, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_SetPropagation101
 * @tc.desc: Test OH_ArkUI_AxisEvent_SetPropagation with C_AXIS_EVENT_ID type
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_SetPropagation101, TestSize.Level0)
{
    // Prepare test data
    ArkUIAxisEvent axisEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, &axisEvent };

    // Test enable propagation
    auto result = OH_ArkUI_AxisEvent_SetPropagation(&event, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(axisEvent.propagation);

    // Test disable propagation
    result = OH_ArkUI_AxisEvent_SetPropagation(&event, false);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(axisEvent.propagation);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_SetPropagation102
 * @tc.desc: Test OH_ArkUI_AxisEvent_SetPropagation with null inputEvent
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_SetPropagation102, TestSize.Level0)
{
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, C_AXIS_EVENT_ID, nullptr };
    auto result = OH_ArkUI_AxisEvent_SetPropagation(&event, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_AxisEvent_SetPropagation103
 * @tc.desc: Test OH_ArkUI_AxisEvent_SetPropagation with AXIS_EVENT_ID type (unsupported)
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_AxisEvent_SetPropagation103, TestSize.Level0)
{
    OHOS::Ace::AxisEvent axisEvent;
    ArkUI_UIInputEvent event = { ARKUI_UIINPUTEVENT_TYPE_UNKNOWN, AXIS_EVENT_ID, &axisEvent };
    auto result = OH_ArkUI_AxisEvent_SetPropagation(&event, true);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

} // namespace OHOS::Ace