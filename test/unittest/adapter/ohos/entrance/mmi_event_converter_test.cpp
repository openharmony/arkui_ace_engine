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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "base/utils/system_properties.h"
#include "pointer_event.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Platform {
class MMIEventConvertorTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: MMIConvertorTest_001
 * @tc.desc: Test MMIEventConvertorTest
 * @tc.type: FUNC
 */
HWTEST_F(MMIEventConvertorTest, MMIConvertorTest_001, TestSize.Level1)
{
    auto pointerEvent = MMI::PointerEvent::Create();
    MMI::PointerEvent::PointerItem pointerItem;
    pointerItem.SetWindowXPos(0.0001);
    pointerItem.SetWindowYPos(100.2);
    pointerItem.SetWindowX(0);
    pointerItem.SetWindowY(100);
    pointerItem.SetPointerId(0);
    pointerEvent->SetPointerId(0);
    pointerEvent->SetSourceType(MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN);
    pointerEvent->UpdatePointerItem(0, pointerItem);
    auto res = ConvertTouchEvent(pointerEvent);
    ASSERT_EQ(res.x, pointerItem.GetWindowX());
    pointerEvent->SetSourceType(MMI::PointerEvent::SOURCE_TYPE_JOYSTICK);
    res = ConvertTouchEvent(pointerEvent);
    pointerEvent->SetSourceType(MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN);
    res = ConvertTouchEvent(pointerEvent);
    pointerItem.SetExtension(OHOS::MMI::PointerEvent::PointerItemExtension::PREDICT_WINDOW_X, 100.123);
    pointerEvent->UpdatePointerItem(0, pointerItem);
    res = ConvertTouchEvent(pointerEvent);
    pointerItem.SetExtension(OHOS::MMI::PointerEvent::PointerItemExtension::PREDICT_WINDOW_Y, 200.456);
    pointerEvent->UpdatePointerItem(0, pointerItem);
    res = ConvertTouchEvent(pointerEvent);
}
} // namespace OHOS::Ace::NG
