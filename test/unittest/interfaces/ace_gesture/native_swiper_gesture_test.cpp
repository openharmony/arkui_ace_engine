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
#include "core/components_ng/gestures/swipe_gesture.h"
#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class NativeSwiperGestureTest : public testing::Test {
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
ArkUI_NativeGestureAPI_1* NativeSwiperGestureTest::NATIVE_GESTURE_API = nullptr;

/**
 * @tc.name: NativeSwiperGestureTest001
 * @tc.desc: Test Native Api create SwiperGesture handle fingerNum parameter,
 * fingerNum must in range in [1, 10], when out of this range the default value is 2.
 * @tc.type: FUNC
 */
HWTEST_F(NativeSwiperGestureTest, NativeSwiperGestureTest001, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> fingerCountTestCases = {
        { -1, -1 }, // in native api -1 will retain the original value
        { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 },
        { 7, 7 }, { 8, 8 }, { 9, 9 }, { 10, 10 } };

    constexpr static ArkUI_GestureDirectionMask DEFAULT_DIRECTION_MASK = GESTURE_DIRECTION_LEFT;
    constexpr static double DEFAULT_SPEED_NUM = 10.0;

    for (auto iter = fingerCountTestCases.begin(); iter != fingerCountTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* swiperGestureRecognizer = nullptr;
        if (NATIVE_GESTURE_API && NATIVE_GESTURE_API->createSwipeGesture) {
            swiperGestureRecognizer = NATIVE_GESTURE_API->createSwipeGesture(inputValue,
                DEFAULT_DIRECTION_MASK, DEFAULT_SPEED_NUM);
        }
        ASSERT_NE(swiperGestureRecognizer, nullptr);
        ASSERT_EQ(swiperGestureRecognizer->type, ArkUI_GestureRecognizerType::SWIPE_GESTURE);

        Ace::NG::SwipeGesture* swipeGesture = reinterpret_cast<Ace::NG::SwipeGesture*>
            (swiperGestureRecognizer->gesture);
        EXPECT_EQ(swipeGesture->GetFingers(), expectValue);

        NATIVE_GESTURE_API->dispose(swiperGestureRecognizer);
    }
}

/**
 * @tc.name: NativeSwiperGestureTest002
 * @tc.desc: Test Native API createSwipeGesture with various ArkUI_GestureDirectionMask values.
 * @tc.type: FUNC
 */
HWTEST_F(NativeSwiperGestureTest, NativeSwiperGestureTest002, TestSize.Level1)
{
    std::unordered_map<ArkUI_GestureDirectionMask, uint32_t> directionTestCases = {
        { GESTURE_DIRECTION_LEFT, 1 }, { GESTURE_DIRECTION_RIGHT, 1 },
        { GESTURE_DIRECTION_UP, 2 }, { GESTURE_DIRECTION_DOWN, 2 }
    };

    constexpr static int DEFAULT_FINGER_COUNT = 1;
    constexpr static double DEFAULT_SPEED_NUM = 10.0;

    for (auto iter = directionTestCases.begin(); iter != directionTestCases.end(); iter++) {
        auto inputDirection = iter->first;
        auto expectedDirection = iter->second;

        ArkUI_GestureRecognizer* swiperGestureRecognizer = nullptr;
        if (NATIVE_GESTURE_API && NATIVE_GESTURE_API->createSwipeGesture) {
            swiperGestureRecognizer = NATIVE_GESTURE_API->createSwipeGesture(DEFAULT_FINGER_COUNT,
                inputDirection, DEFAULT_SPEED_NUM);
        }
        ASSERT_NE(swiperGestureRecognizer, nullptr);
        ASSERT_EQ(swiperGestureRecognizer->type, ArkUI_GestureRecognizerType::SWIPE_GESTURE);

        Ace::NG::SwipeGesture* swipeGesture = reinterpret_cast<Ace::NG::SwipeGesture*>
            (swiperGestureRecognizer->gesture);
        EXPECT_EQ(swipeGesture->direction_.type, expectedDirection);

        NATIVE_GESTURE_API->dispose(swiperGestureRecognizer);
    }
}

/**
 * @tc.name: NativeSwiperGestureTest003
 * @tc.desc: Test Native API createSwipeGesture with various speed values. speed must in range in [1, +∞],
 * when out of this range the default value is 100.
 * @tc.type: FUNC
 */
HWTEST_F(NativeSwiperGestureTest, NativeSwiperGestureTest003, TestSize.Level1)
{
    //In the native api, different inputs will result in an expected 0.
    std::unordered_map<double, double> speedTestCases = { { -10.0f, 0.0f }, { 0.0f, 0.0f },
    { 1.0f, 0.0f }, { 50.0f, 0.0f }, { 100.0f, 0.0f }, { 200.0f, 0.0f } };

    constexpr static int DEFAULT_FINGER_COUNT = 1;
    constexpr static ArkUI_GestureDirectionMask DEFAULT_DIRECTION_MASK = GESTURE_DIRECTION_LEFT;

    for (auto iter = speedTestCases.begin(); iter != speedTestCases.end(); iter++) {
        auto inputSpeed = iter->first;
        auto expectedSpeed = iter->second;

        ArkUI_GestureRecognizer* swiperGestureRecognizer = nullptr;
        if (NATIVE_GESTURE_API && NATIVE_GESTURE_API->createSwipeGesture) {
            swiperGestureRecognizer = NATIVE_GESTURE_API->createSwipeGesture(DEFAULT_FINGER_COUNT,
                DEFAULT_DIRECTION_MASK, inputSpeed);
        }
        ASSERT_NE(swiperGestureRecognizer, nullptr);
        ASSERT_EQ(swiperGestureRecognizer->type, ArkUI_GestureRecognizerType::SWIPE_GESTURE);

        Ace::NG::SwipeGesture* swipeGesture = reinterpret_cast<Ace::NG::SwipeGesture*>
            (swiperGestureRecognizer->gesture);
        EXPECT_EQ(swipeGesture->speed_, Dimension(expectedSpeed, DimensionUnit::VP));

        NATIVE_GESTURE_API->dispose(swiperGestureRecognizer);
    }
}

} // namespace OHOS::Ace