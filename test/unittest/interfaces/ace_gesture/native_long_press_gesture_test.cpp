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

#include <unordered_map>
#include <vector>
 
#include "gtest/gtest.h"
#include "interfaces/native/native_gesture.h"
#include "interfaces/native/native_interface.h"
#include "interfaces/native/native_node.h"
#include "interfaces/native/native_type.h"
#include "interfaces/native/node/gesture_impl.h"

#define private public
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class NativeLongPressGestureTest : public testing::Test {
public:
    static ArkUI_NativeGestureAPI_1* NATIVE_GESTURE_API;
    static void SetUpTestCase()
    {
        NATIVE_GESTURE_API = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(
            OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1"));
        ASSERT_NE(NATIVE_GESTURE_API, nullptr);
    };
    static void TearDownTestCase()
    {
        NATIVE_GESTURE_API = nullptr;
    };
};
ArkUI_NativeGestureAPI_1* NativeLongPressGestureTest::NATIVE_GESTURE_API = nullptr;

/**
 * @tc.name: NativeLongPressGestureTest001
 * @tc.desc: Test Native Api create LongPress handle fingerNum parameter, fingerNum must in range in [0, 10], when out
 * of this range the default value is 1.
 * @tc.type: FUNC
 */
HWTEST_F(NativeLongPressGestureTest, NativeLongPressGestureTest001, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> fingerCountTestCases = {
        { -1, -1 }, //in native api -1 will retain the original value
        { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 },
        { 6, 6 }, { 7, 7 }, { 8, 8 }, { 9, 9 }, { 10, 10 },
        {11, 11}  //in native api 11 will retain the original value
    };

    constexpr static int32_t DEFAULT_LONG_PRESS_DURATION = 1000;

    for (auto iter = fingerCountTestCases.begin(); iter != fingerCountTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* longPressGestureRecognizer = NATIVE_GESTURE_API->createLongPressGesture(
            inputValue, false, DEFAULT_LONG_PRESS_DURATION);
        ASSERT_NE(longPressGestureRecognizer, nullptr);
        ASSERT_EQ(longPressGestureRecognizer->type, ArkUI_GestureRecognizerType::LONG_PRESS_GESTURE);

        Ace::NG::LongPressGesture* longPressGesture =
            reinterpret_cast<Ace::NG::LongPressGesture*>(longPressGestureRecognizer->gesture);
        EXPECT_EQ(longPressGesture->GetFingers(), expectValue);

        NATIVE_GESTURE_API->dispose(longPressGestureRecognizer);
    }
}

/**
 * @tc.name: NativeLongPressGestureTest002
 * @tc.desc: Test Native Api create LongPress handle duration parameter, duration must be positive, invalid values will
 * default to 500ms.
 * @tc.type: FUNC
 */
HWTEST_F(NativeLongPressGestureTest, NativeLongPressGestureTest002, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> durationTestCases = {
        { -100, -100 }, //in native api -100 will retain the original value
        { 0, 0 }, // in native api 0 will retain the original value
        { 500, 500 }, { 1000, 1000 }, { 2000, 2000 }};

    constexpr static int32_t DEFAULT_FINGER_NUM = 1;

    for (auto iter = durationTestCases.begin(); iter != durationTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* longPressGestureRecognizer =
            NATIVE_GESTURE_API->createLongPressGesture(DEFAULT_FINGER_NUM, false, inputValue);
        ASSERT_NE(longPressGestureRecognizer, nullptr);
        ASSERT_EQ(longPressGestureRecognizer->type, ArkUI_GestureRecognizerType::LONG_PRESS_GESTURE);

        Ace::NG::LongPressGesture* longPressGesture =
            reinterpret_cast<Ace::NG::LongPressGesture*>(longPressGestureRecognizer->gesture);
        EXPECT_DOUBLE_EQ(longPressGesture->duration_, expectValue);

        NATIVE_GESTURE_API->dispose(longPressGestureRecognizer);
    }
}

} // namespace OHOS::Ace
