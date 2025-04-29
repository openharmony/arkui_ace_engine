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
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class NativePanGestureTest : public testing::Test {
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
ArkUI_NativeGestureAPI_1* NativePanGestureTest::NATIVE_GESTURE_API = nullptr;

/**
 * @tc.name: NativePanGestureTest001
 * @tc.desc: Test Native Api create PanGesture handle fingerNum parameter, fingerNum must in range in [0, 10], when out
 * of this range the default value is 1.
 * @tc.type: FUNC
 */
HWTEST_F(NativePanGestureTest, NativePanGestureTest001, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> fingerCountTestCases = { { -1, 1 }, { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 },
        { 5, 5 }, { 6, 6 }, { 7, 7 }, { 8, 8 }, { 9, 9 }, { 10, 10 }, { 11, 1 }, { 100, 1 } };

    constexpr static ArkUI_GestureDirection DEFAULT_PAN_DIRECTION = ArkUI_GestureDirection::GESTURE_DIRECTION_NONE;
    constexpr static double DEFAULT_PAN_DISTANCE = 10;

    for (auto iter = fingerCountTestCases.begin(); iter != fingerCountTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* panGestureRecognizer =
            NATIVE_GESTURE_API->createPanGesture(inputValue, DEFAULT_PAN_DIRECTION, DEFAULT_PAN_DISTANCE);
        ASSERT_NE(panGestureRecognizer, nullptr);
        ASSERT_EQ(panGestureRecognizer->type, ArkUI_GestureRecognizerType::PAN_GESTURE);

        Ace::NG::PanGesture* panGesture = reinterpret_cast<Ace::NG::PanGesture*>(panGestureRecognizer->gesture);
        EXPECT_EQ(panGesture->GetFingers(), expectValue);

        NATIVE_GESTURE_API->dispose(panGestureRecognizer);
    }
}

/**
 * @tc.name: NativePanGestureTest002
 * @tc.desc: Test Native Api create PanGesture handle direction parameter, direction must in range in [0, 15], when out
 * of this range the default value is 0. in native api [ 5, 6, 7, 8, 9, 10, 11, 13, 14 ] is also invalid value.
 * @tc.type: FUNC
 */
HWTEST_F(NativePanGestureTest, NativePanGestureTest002, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> directionTestCases = {
        { -1, 0 }, // invalid value will regard as default value GESTURE_DIRECTION_NONE(0)
        { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 },
        { 5, 0 },              // in native api 5 is invalid value, different with js api
        { 6, 0 },              // in native api 6 is invalid value, different with js api
        { 7, 0 },              // in native api 7 is invalid value, different with js api
        { 8, 8 }, { 9, 0 },    // in native api 9 is invalid value, different with js api
        { 10, 0 },             // in native api 10 is invalid value, different with js api
        { 11, 0 },             // in native api 11 is invalid value, different with js api
        { 12, 12 }, { 13, 0 }, // in native api 13 is invalid value, different with js api
        { 14, 0 },             // in native api 14 is invalid value, different with js api
        { 15, 15 }, { 16, 0 }, { 30, 0 }, { 100, 0 }
    };

    constexpr static int32_t DEFAULT_FINGER_NUM = 1;
    constexpr static double DEFAULT_PAN_DISTANCE = 10.0;

    for (auto iter = directionTestCases.begin(); iter != directionTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* panGestureRecognizer =
            NATIVE_GESTURE_API->createPanGesture(DEFAULT_FINGER_NUM, inputValue, DEFAULT_PAN_DISTANCE);
        ASSERT_NE(panGestureRecognizer, nullptr);
        ASSERT_EQ(panGestureRecognizer->type, ArkUI_GestureRecognizerType::PAN_GESTURE);

        Ace::NG::PanGesture* panGesture = reinterpret_cast<Ace::NG::PanGesture*>(panGestureRecognizer->gesture);
        EXPECT_EQ(panGesture->direction_.type, expectValue);

        NATIVE_GESTURE_API->dispose(panGestureRecognizer);
    }
}

/**
 * @tc.name: NativePanGestureTest003
 * @tc.desc: Test Native Api create PanGesture handle distance parameter, in native api invaild value will not transform
 * to default value.
 * @tc.type: FUNC
 */
HWTEST_F(NativePanGestureTest, NativePanGestureTest003, TestSize.Level1)
{
    std::vector<std::pair<double, double>> distanceTestCases = { { -100.0, -100.0 }, { -1.0, -1.0 }, { 0.0, 0.0 },
        { 5.0, 5.0 }, { 100.0, 100.0 }, { 10000000.0, 10000000.0 } };

    constexpr static int32_t DEFAULT_FINGER_NUM = 1;
    constexpr static ArkUI_GestureDirection DEFAULT_PAN_DIRECTION = ArkUI_GestureDirection::GESTURE_DIRECTION_NONE;

    for (auto iter = distanceTestCases.begin(); iter != distanceTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* panGestureRecognizer =
            NATIVE_GESTURE_API->createPanGesture(DEFAULT_FINGER_NUM, DEFAULT_PAN_DIRECTION, inputValue);
        ASSERT_NE(panGestureRecognizer, nullptr);
        ASSERT_EQ(panGestureRecognizer->type, ArkUI_GestureRecognizerType::PAN_GESTURE);
        Ace::NG::PanGesture* panGesture = reinterpret_cast<Ace::NG::PanGesture*>(panGestureRecognizer->gesture);
        EXPECT_DOUBLE_EQ(panGesture->distance_, expectValue);

        NATIVE_GESTURE_API->dispose(panGestureRecognizer);
    }
}

} // namespace OHOS::Ace
