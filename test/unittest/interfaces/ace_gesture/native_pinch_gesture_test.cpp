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
#include "core/components_ng/gestures/pinch_gesture.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class NativePinchGestureTest : public testing::Test {
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
ArkUI_NativeGestureAPI_1* NativePinchGestureTest::NATIVE_GESTURE_API = nullptr;

/**
 * @tc.name: NativePinchGestureTest001
 * @tc.desc: Test Native Api create Pinch handle fingerNum parameter, fingerNum must in range in [0, 5], when out
 * of this range the default value is 2.
 * @tc.type: FUNC
 */
HWTEST_F(NativePinchGestureTest, NativePinchGestureTest001, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> fingerCountTestCases = {
        { -1, -1 }, //in native api -1 will retain the original value
        { 1, 1 }, //in native api 1 will retain the original value
        { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 },
        { 6, 6 }, //in native api 6 will retain the original value
        { 7, 7 }, //in native api 7 will retain the original value
        { 8, 8 }, //in native api 8 will retain the original value
        { 9, 9 }, //in native api 9 will retain the original value
        { 10, 10 } //in native api 10 will retain the original value
    };

    constexpr static double DEFAULT_PINCH_DISTANCE = 10;

    for (auto iter = fingerCountTestCases.begin(); iter != fingerCountTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* pinchGestureRecognizer =
            NATIVE_GESTURE_API->createPinchGesture(inputValue, DEFAULT_PINCH_DISTANCE);
        ASSERT_NE(pinchGestureRecognizer, nullptr);
        ASSERT_EQ(pinchGestureRecognizer->type, ArkUI_GestureRecognizerType::PINCH_GESTURE);

        Ace::NG::PinchGesture* pinchGesture = reinterpret_cast<Ace::NG::PinchGesture*>(pinchGestureRecognizer->gesture);
        EXPECT_EQ(pinchGesture->GetFingers(), expectValue);

        NATIVE_GESTURE_API->dispose(pinchGestureRecognizer);
    }
}

/**
 * @tc.name: NativePinchGestureTest002
 * @tc.desc: Test Native Api create Pinch handle distanceNum parameter, If this parameter is set to a value less
    *        than or equal to 0, the default value <b>5</b> is used.
 * @tc.type: FUNC
 */
HWTEST_F(NativePinchGestureTest, NativePinchGestureTest002, TestSize.Level1)
{
    //In the native api, different inputs will result in an expected 0.
    std::unordered_map<double, double> distanceTestCases = { { -10.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f },
        { 5.0f, 0.0f }, { 10.0f, 0.0f }, { 20.0f, 0.0f } };

    constexpr static int32_t DEFAULT_FINGER_COUNT = 2;

    for (auto iter = distanceTestCases.begin(); iter != distanceTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* pinchGestureRecognizer =
            NATIVE_GESTURE_API->createPinchGesture(DEFAULT_FINGER_COUNT, inputValue);
        ASSERT_NE(pinchGestureRecognizer, nullptr);
        ASSERT_EQ(pinchGestureRecognizer->type, ArkUI_GestureRecognizerType::PINCH_GESTURE);

        Ace::NG::PinchGesture* pinchGesture = reinterpret_cast<Ace::NG::PinchGesture*>(pinchGestureRecognizer->gesture);
        EXPECT_DOUBLE_EQ(pinchGesture->distance_, expectValue);

        NATIVE_GESTURE_API->dispose(pinchGestureRecognizer);
    }
}

} // namespace OHOS::Ace
