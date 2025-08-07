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
#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class NativeTapGestureTest : public testing::Test {
public:
    static ArkUI_NativeGestureAPI_1* NATIVE_GESTURE_API;
    void SetUp() override {};
    void TearDown() override {};

    static void SetUpTestSuite()
    {
        NATIVE_GESTURE_API = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(
            OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1"));
        ASSERT_NE(NATIVE_GESTURE_API, nullptr);
    }

    static void TearDownTestSuite()
    {
        NATIVE_GESTURE_API = nullptr;
    }
};
ArkUI_NativeGestureAPI_1* NativeTapGestureTest::NATIVE_GESTURE_API = nullptr;

/**
 * @tc.name: NativeTapGestureTest001
 * @tc.desc: Test Native Api create TapGesture handle numCount parameter, numCount must in range in [1, +∞], when out
 * of this range the default value is 1.
 * @tc.type: FUNC
 */
HWTEST_F(NativeTapGestureTest, NativeTapGestureTest001, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> numCountTestCases = { { -100, 1 }, { 0, 1 }, { 5, 5 }, { 10, 10 } };
    constexpr int32_t fingerNum = 1;

    for (auto iter = numCountTestCases.begin(); iter != numCountTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* tapGestureRecognizer = NATIVE_GESTURE_API->createTapGesture(inputValue, fingerNum);
        ASSERT_NE(tapGestureRecognizer, nullptr);
        ASSERT_EQ(tapGestureRecognizer->type, ArkUI_GestureRecognizerType::TAP_GESTURE);

        Ace::NG::TapGesture* tapGesture = reinterpret_cast<Ace::NG::TapGesture*>(tapGestureRecognizer->gesture);
        EXPECT_EQ(tapGesture->GetTapCount(), expectValue);

        NATIVE_GESTURE_API->dispose(tapGestureRecognizer);
    }
}

/**
 * @tc.name: NativeTapGestureTest002
 * @tc.desc: Test Native Api create TapGesture handle fingerNum parameter, fingerNum must in range in [1, 10], when out
 * of this range the default value is 1 or 10.
 * @tc.type: FUNC
 */
HWTEST_F(NativeTapGestureTest, NativeTapGestureTest002, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> fingerNumTestCases = { { -100, 1 }, { 0, 1 }, { 5, 5 }, { 10, 10 },
        { 100, 10 } };
    constexpr int32_t numCount = 1;

    for (auto iter = fingerNumTestCases.begin(); iter != fingerNumTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* tapGestureRecognizer = NATIVE_GESTURE_API->createTapGesture(numCount, inputValue);
        ASSERT_NE(tapGestureRecognizer, nullptr);
        ASSERT_EQ(tapGestureRecognizer->type, ArkUI_GestureRecognizerType::TAP_GESTURE);

        Ace::NG::TapGesture* tapGesture = reinterpret_cast<Ace::NG::TapGesture*>(tapGestureRecognizer->gesture);
        EXPECT_EQ(tapGesture->GetFingers(), expectValue);

        NATIVE_GESTURE_API->dispose(tapGestureRecognizer);
    }
}

/**
 * @tc.name: NativeTapGestureTest003
 * @tc.desc: Test Native Api create TapGesture handle numCount parameter, numCount must in range in [1, +∞], when out
 * of this range the default value is 1.
 * @tc.type: FUNC
 */
HWTEST_F(NativeTapGestureTest, NativeTapGestureTest003, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> numCountTestCases = { { -100, 1 }, { 0, 1 }, { 5, 5 }, { 10, 10 } };
    constexpr int32_t fingerNum = 1;
    constexpr double distance = 10.0;

    for (auto iter = numCountTestCases.begin(); iter != numCountTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* tapGestureRecognizer =
            NATIVE_GESTURE_API->createTapGestureWithDistanceThreshold(inputValue, fingerNum, distance);
        ASSERT_NE(tapGestureRecognizer, nullptr);
        ASSERT_EQ(tapGestureRecognizer->type, ArkUI_GestureRecognizerType::TAP_GESTURE);

        Ace::NG::TapGesture* tapGesture = reinterpret_cast<Ace::NG::TapGesture*>(tapGestureRecognizer->gesture);
        EXPECT_EQ(tapGesture->GetTapCount(), expectValue);
        EXPECT_EQ(tapGesture->GetFingers(), fingerNum);
        EXPECT_DOUBLE_EQ(tapGesture->distanceThreshold_.ConvertToPx(), 0.0); // not support

        NATIVE_GESTURE_API->dispose(tapGestureRecognizer);
    }
}

/**
 * @tc.name: NativeTapGestureTest004
 * @tc.desc: Test Native Api create TapGesture handle fingerNum parameter, fingerNum must in range in [1, 10], when out
 * of this range the default value is 1 or 10.
 * @tc.type: FUNC
 */
HWTEST_F(NativeTapGestureTest, NativeTapGestureTest004, TestSize.Level1)
{
    std::unordered_map<int32_t, int32_t> fingerNumTestCases = { { -100, 1 }, { 0, 1 }, { 5, 5 }, { 10, 10 },
        { 100, 10 } };
    constexpr int32_t numCount = 1;
    constexpr double distance = 10.0;

    for (auto iter = fingerNumTestCases.begin(); iter != fingerNumTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* tapGestureRecognizer =
            NATIVE_GESTURE_API->createTapGestureWithDistanceThreshold(numCount, inputValue, distance);
        ASSERT_NE(tapGestureRecognizer, nullptr);
        ASSERT_EQ(tapGestureRecognizer->type, ArkUI_GestureRecognizerType::TAP_GESTURE);

        Ace::NG::TapGesture* tapGesture = reinterpret_cast<Ace::NG::TapGesture*>(tapGestureRecognizer->gesture);
        EXPECT_EQ(tapGesture->GetTapCount(), numCount);
        EXPECT_EQ(tapGesture->GetFingers(), expectValue);
        EXPECT_DOUBLE_EQ(tapGesture->distanceThreshold_.ConvertToPx(), 0.0); // not support

        NATIVE_GESTURE_API->dispose(tapGestureRecognizer);
    }
}

/**
 * @tc.name: NativeTapGestureTest005
 * @tc.desc: Test Native Api create TapGesture handle distance parameter, invaild value will not transform
 * to default value.
 * @tc.type: FUNC
 */
HWTEST_F(NativeTapGestureTest, NativeTapGestureTest005, TestSize.Level1)
{
    std::vector<std::pair<double, double>> distanceTestCases = { { -100.0, 0.0 }, { 0.0, 0.0 }, { 5.0, 0.0 },
        { 10, 0.0 }, { 100.0, 0.0 } };

    constexpr int32_t numCount = 1;
    constexpr int32_t fingerNum = 5;

    for (auto iter = distanceTestCases.begin(); iter != distanceTestCases.end(); iter++) {
        auto inputValue = iter->first;
        auto expectValue = iter->second;

        ArkUI_GestureRecognizer* tapGestureRecognizer =
            NATIVE_GESTURE_API->createTapGestureWithDistanceThreshold(numCount, fingerNum, inputValue);
        ASSERT_NE(tapGestureRecognizer, nullptr);
        ASSERT_EQ(tapGestureRecognizer->type, ArkUI_GestureRecognizerType::TAP_GESTURE);

        Ace::NG::TapGesture* tapGesture = reinterpret_cast<Ace::NG::TapGesture*>(tapGestureRecognizer->gesture);
        EXPECT_EQ(tapGesture->GetTapCount(), numCount);
        EXPECT_EQ(tapGesture->GetFingers(), fingerNum);
        EXPECT_DOUBLE_EQ(tapGesture->distanceThreshold_.ConvertToPx(), expectValue); // not support

        NATIVE_GESTURE_API->dispose(tapGestureRecognizer);
    }
}

} // namespace OHOS::Ace