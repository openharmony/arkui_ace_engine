/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "gesture_impl.cpp"
#include "native_gesture.h"
#include "native_interface.h"
#include "native_node.h"
#include "native_type.h"

#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/core/components_ng/gestures/recognizers/click_recognizer.h"
#include "frameworks/core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "frameworks/core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "frameworks/core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;
class NativeGestureTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: NativeGestureTest001
 * @tc.desc: Test createTapGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeGestureTest001, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1"));
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto group = gestureAPI->createGroupGesture(EXCLUSIVE_GROUP);
    auto tapGesture = gestureAPI->createTapGesture(1, 1);
    auto tapGesture1 = gestureAPI->createTapGesture(0, 11);
    auto longPressGesture = gestureAPI->createLongPressGesture(1, true, 500);
    auto panGesture = gestureAPI->createPanGesture(1, GESTURE_DIRECTION_DOWN, 5);
    auto swipeGesture = gestureAPI->createSwipeGesture(1, 1, 5);
    auto pinchGesture = gestureAPI->createPinchGesture(2, 20);
    auto rotateGesture = gestureAPI->createRotationGesture(2, 90);
    gestureAPI->addChildGesture(group, tapGesture);
    gestureAPI->addChildGesture(group, tapGesture1);
    gestureAPI->addChildGesture(group, longPressGesture);
    auto onActionCallBack = [](ArkUI_GestureEvent *event, void *extraParam) {};
    gestureAPI->setGestureEventTarget(
        longPressGesture, GESTURE_EVENT_ACTION_ACCEPT,
        gestureNode, onActionCallBack);
    auto onInterruptCallback = [](ArkUI_GestureInterruptInfo* info) -> ArkUI_GestureInterruptResult {
        return GESTURE_INTERRUPT_RESULT_REJECT;
    };
    gestureAPI->setGestureInterrupterToNode(gestureNode, onInterruptCallback);
    auto ret = gestureAPI->addGestureToNode(gestureNode, group, PRIORITY, NORMAL_GESTURE_MASK);
    EXPECT_EQ(ret, 0);
    gestureAPI->removeGestureFromNode(gestureNode, group);
    gestureAPI->removeChildGesture(group, tapGesture);
    gestureAPI->removeChildGesture(group, tapGesture1);
    gestureAPI->removeChildGesture(group, longPressGesture);
    gestureAPI->dispose(tapGesture);
    gestureAPI->dispose(longPressGesture);
    gestureAPI->dispose(panGesture);
    gestureAPI->dispose(swipeGesture);
    gestureAPI->dispose(pinchGesture);
    gestureAPI->dispose(rotateGesture);
}

/**
 * @tc.name: NativeGestureTest002
 * @tc.desc: Test createTapGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeGestureTest002, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1"));
    auto pinchGesture = gestureAPI->createPinchGesture(2, 0.0f);
    EXPECT_NE(pinchGesture, nullptr);
    auto swipeGesture = gestureAPI->createSwipeGesture(1, 1, 0.0f);
    EXPECT_NE(swipeGesture, nullptr);
    auto panGesture = gestureAPI->createPanGesture(0, GESTURE_DIRECTION_DOWN, 5);
    EXPECT_NE(panGesture, nullptr);
    gestureAPI->dispose(pinchGesture);
    gestureAPI->dispose(swipeGesture);
    gestureAPI->dispose(panGesture);
    EXPECT_NE(gestureAPI, nullptr);
}

/**
 * @tc.name: NativeGestureTest003
 * @tc.desc: Test the API2 setGestureInterrupterToNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeGestureTest003, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto group = gestureAPI->gestureApi1->createGroupGesture(EXCLUSIVE_GROUP);
    auto tapGesture = gestureAPI->gestureApi1->createTapGesture(1, 1);
    auto tapGesture1 = gestureAPI->gestureApi1->createTapGesture(0, 11);
    auto longPressGesture = gestureAPI->gestureApi1->createLongPressGesture(1, true, 500);
    auto panGesture = gestureAPI->gestureApi1->createPanGesture(1, GESTURE_DIRECTION_DOWN, 5);
    auto swipeGesture = gestureAPI->gestureApi1->createSwipeGesture(1, 1, 5);
    auto pinchGesture = gestureAPI->gestureApi1->createPinchGesture(2, 20);
    auto rotateGesture = gestureAPI->gestureApi1->createRotationGesture(2, 90);
    gestureAPI->gestureApi1->addChildGesture(group, tapGesture);
    gestureAPI->gestureApi1->addChildGesture(group, tapGesture1);
    gestureAPI->gestureApi1->addChildGesture(group, longPressGesture);
    auto onActionCallBack = [](ArkUI_GestureEvent *event, void *extraParam) {};
    gestureAPI->gestureApi1->setGestureEventTarget(
        longPressGesture, GESTURE_EVENT_ACTION_ACCEPT,
        gestureNode, onActionCallBack);
    auto onInterruptCallback = [](ArkUI_GestureInterruptInfo* info) -> ArkUI_GestureInterruptResult {
        return GESTURE_INTERRUPT_RESULT_REJECT;
    };
    int userData = 1;
    gestureAPI->setGestureInterrupterToNode(gestureNode, &userData, onInterruptCallback);
    auto ret = gestureAPI->gestureApi1->addGestureToNode(gestureNode, group, PRIORITY, NORMAL_GESTURE_MASK);
    EXPECT_EQ(ret, 0);
    gestureAPI->gestureApi1->removeGestureFromNode(gestureNode, group);
    gestureAPI->gestureApi1->removeChildGesture(group, tapGesture);
    gestureAPI->gestureApi1->removeChildGesture(group, tapGesture1);
    gestureAPI->gestureApi1->removeChildGesture(group, longPressGesture);
    gestureAPI->gestureApi1->dispose(tapGesture);
    gestureAPI->gestureApi1->dispose(longPressGesture);
    gestureAPI->gestureApi1->dispose(panGesture);
    gestureAPI->gestureApi1->dispose(swipeGesture);
    gestureAPI->gestureApi1->dispose(pinchGesture);
    gestureAPI->gestureApi1->dispose(rotateGesture);
}

/**
 * @tc.name: NativeGestureTest004
 * @tc.desc: Test the OH_ArkUI_GestureInterrupter_GetUserData function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeGestureTest004, TestSize.Level1)
{
    auto info = new ArkUI_GestureInterruptInfo();
    void* userDataVoidPtr = OH_ArkUI_GestureInterrupter_GetUserData(info);
    int* userDataPtr = reinterpret_cast<int*>(userDataVoidPtr);
    EXPECT_EQ(userDataPtr, nullptr);
    delete info;
}

/**
 * @tc.name: NativeGestureIssueTest001
 * @tc.desc: Test the OH_ArkUI_GestureInterruptInfo_GetGestureEvent functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeGestureIssueTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create ArkUI_GestureInterruptInfo, related function is called.
     */
    ArkUI_GestureInterruptInfo interruptInfo;
    ArkUI_GestureEvent gestureEvent;
    ArkUIGestureInterruptInfo interruptData;
    auto* nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto* gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    interruptData.userData = reinterpret_cast<void*>(gestureNode);
    interruptData.gestureEvent = &gestureEvent;
    interruptInfo.interruptData = interruptData;

    auto* event = OH_ArkUI_GestureInterruptInfo_GetGestureEvent(&interruptInfo);
    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_NE(event, nullptr);
}

/**
 * @tc.name: NativeNodeGestureRecognizer001
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_DirectMask function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer001, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    ArkUI_GestureDirectionMask directMask = 1;
    auto ret = OH_ArkUI_GetGestureParam_DirectMask(recognizer, &directMask);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer002
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_DirectMask function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer002, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    ArkUI_GestureDirectionMask* directMask = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_DirectMask(&recognizer, directMask);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer003
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_DirectMask function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer003, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 5, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    ArkUI_GestureDirectionMask directMaskNew = 1;
    ArkUI_GestureDirectionMask* directMask = &directMaskNew;
    OHOS::Ace::SwipeDirection direction = { OHOS::Ace::SwipeDirection::HORIZONTAL };
    OHOS::Ace::NG::NGGestureRecognizer* gestureRecognizer = new OHOS::Ace::NG::SwipeRecognizer(1, direction, 100);
    recognizer->recognizer = gestureRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_DirectMask(recognizer, directMask);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    OHOS::Ace::PanDirection direction_another = { OHOS::Ace::PanDirection::LEFT };
    OHOS::Ace::NG::NGGestureRecognizer* gestureRecognizer_another =
        new OHOS::Ace::NG::PanRecognizer(1, direction_another, 5);
    recognizer->recognizer = gestureRecognizer_another;
    recognizer->type = 2;
    ret = OH_ArkUI_GetGestureParam_DirectMask(recognizer, directMask);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 3;
    ret = OH_ArkUI_GetGestureParam_DirectMask(recognizer, directMask);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer004
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_FingerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer004, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    int finger = 2;
    auto ret = OH_ArkUI_GetGestureParam_FingerCount(recognizer, &finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer005
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_FingerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer005, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    int* finger = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_FingerCount(&recognizer, finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer006
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_FingerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer006, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 0, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    int fingerNew = 2;
    int* finger = &fingerNew;
    double distanceThreshold = std::numeric_limits<double>::infinity();
    OHOS::Ace::NG::NGGestureRecognizer* tapRecognizer = new OHOS::Ace::NG::ClickRecognizer(1, 1, distanceThreshold);
    recognizer->recognizer = tapRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_FingerCount(recognizer, finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 1;
    OHOS::Ace::NG::NGGestureRecognizer* longPressRecognizer =
        new OHOS::Ace::NG::LongPressRecognizer(500, 1, true, false, false);
    recognizer->recognizer = longPressRecognizer;
    ret = OH_ArkUI_GetGestureParam_FingerCount(recognizer, finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 3;
    OHOS::Ace::NG::NGGestureRecognizer* pinchRecognizer = new OHOS::Ace::NG::PinchRecognizer(1, 5);
    recognizer->recognizer = pinchRecognizer;
    ret = OH_ArkUI_GetGestureParam_FingerCount(recognizer, finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 4;
    OHOS::Ace::NG::NGGestureRecognizer* rotationRecognizer = new OHOS::Ace::NG::RotationRecognizer(1, 1);
    recognizer->recognizer = rotationRecognizer;
    ret = OH_ArkUI_GetGestureParam_FingerCount(recognizer, finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 5;
    OHOS::Ace::SwipeDirection direction = { OHOS::Ace::SwipeDirection::HORIZONTAL };
    OHOS::Ace::NG::NGGestureRecognizer* gestureRecognizer = new OHOS::Ace::NG::SwipeRecognizer(1, direction, 100);
    recognizer->recognizer = gestureRecognizer;
    ret = OH_ArkUI_GetGestureParam_FingerCount(recognizer, finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 2;
    OHOS::Ace::PanDirection direction_another = { OHOS::Ace::PanDirection::LEFT };
    OHOS::Ace::NG::NGGestureRecognizer* gestureRecognizer_another =
        new OHOS::Ace::NG::PanRecognizer(1, direction_another, 5);
    recognizer->recognizer = gestureRecognizer_another;
    ret = OH_ArkUI_GetGestureParam_FingerCount(recognizer, finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = -1;
    ret = OH_ArkUI_GetGestureParam_FingerCount(recognizer, finger);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer007
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_limitFingerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer007, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    bool isLimited = false;
    auto ret = OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, &isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer008
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_limitFingerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer008, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    bool* isLimited = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_limitFingerCount(&recognizer, isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer009
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_limitFingerCount function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer009, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 0, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    bool isLimitedNew = false;
    bool* isLimited = &isLimitedNew;
    double distanceThreshold = std::numeric_limits<double>::infinity();
    OHOS::Ace::NG::NGGestureRecognizer* tapRecognizer = new OHOS::Ace::NG::ClickRecognizer(1, 1, distanceThreshold);
    recognizer->recognizer = tapRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 1;
    OHOS::Ace::NG::NGGestureRecognizer* longPressRecognizer =
        new OHOS::Ace::NG::LongPressRecognizer(500, 1, true, false, false);
    recognizer->recognizer = longPressRecognizer;
    ret = OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 3;
    OHOS::Ace::NG::NGGestureRecognizer* pinchRecognizer = new OHOS::Ace::NG::PinchRecognizer(1, 5);
    recognizer->recognizer = pinchRecognizer;
    ret = OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 4;
    OHOS::Ace::NG::NGGestureRecognizer* rotationRecognizer = new OHOS::Ace::NG::RotationRecognizer(1, 1);
    recognizer->recognizer = rotationRecognizer;
    ret = OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 5;
    OHOS::Ace::SwipeDirection direction = { OHOS::Ace::SwipeDirection::HORIZONTAL };
    OHOS::Ace::NG::NGGestureRecognizer* gestureRecognizer = new OHOS::Ace::NG::SwipeRecognizer(1, direction, 100);
    recognizer->recognizer = gestureRecognizer;
    ret = OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 2;
    OHOS::Ace::PanDirection direction_another = { OHOS::Ace::PanDirection::LEFT };
    OHOS::Ace::NG::NGGestureRecognizer* gestureRecognizer_another =
        new OHOS::Ace::NG::PanRecognizer(1, direction_another, 5);
    recognizer->recognizer = gestureRecognizer_another;
    ret = OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = -1;
    ret = OH_ArkUI_GetGestureParam_limitFingerCount(recognizer, isLimited);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer010
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_repeat function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer010, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    bool isRepeat = true;
    auto ret = OH_ArkUI_GetGestureParam_repeat(recognizer, &isRepeat);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer011
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_repeat function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer011, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    bool* isRepeat = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_repeat(&recognizer, isRepeat);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer012
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_repeat function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer012, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 1, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    bool isRepeatNew = true;
    bool* isRepeat = &isRepeatNew;
    OHOS::Ace::NG::NGGestureRecognizer* longPressRecognizer =
        new OHOS::Ace::NG::LongPressRecognizer(500, 1, true, false, false);
    recognizer->recognizer = longPressRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_repeat(recognizer, isRepeat);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 2;
    ret = OH_ArkUI_GetGestureParam_repeat(recognizer, isRepeat);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED);
}

/**
 * @tc.name: NativeNodeGestureRecognizer013
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_distance function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer013, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    double distance = 5;
    auto ret = OH_ArkUI_GetGestureParam_distance(recognizer, &distance);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer014
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_distance function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer014, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    double* distance = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_distance(&recognizer, distance);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer015
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_distance function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer015, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 3, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    double distanceNew = 5;
    double* distance = &distanceNew;
    OHOS::Ace::NG::NGGestureRecognizer* pinchRecognizer = new OHOS::Ace::NG::PinchRecognizer(1, 5);
    recognizer->recognizer = pinchRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_distance(recognizer, distance);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 2;
    OHOS::Ace::PanDirection direction_another = { OHOS::Ace::PanDirection::LEFT };
    OHOS::Ace::NG::NGGestureRecognizer* gestureRecognizer_another =
        new OHOS::Ace::NG::PanRecognizer(1, direction_another, 5);
    recognizer->recognizer = gestureRecognizer_another;
    ret = OH_ArkUI_GetGestureParam_distance(recognizer, distance);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 5;
    ret = OH_ArkUI_GetGestureParam_distance(recognizer, distance);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED);
}

/**
 * @tc.name: NativeNodeGestureRecognizer016
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_speed function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer016, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    double speed = 100;
    auto ret = OH_ArkUI_GetGestureParam_speed(recognizer, &speed);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer017
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_speed function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer017, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    double* speed = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_speed(&recognizer, speed);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer018
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_speed function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer018, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 5, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    double speedNew = 100;
    double* speed = &speedNew;
    recognizer->type = 5;
    OHOS::Ace::SwipeDirection direction = { OHOS::Ace::SwipeDirection::HORIZONTAL };
    OHOS::Ace::NG::NGGestureRecognizer* gestureRecognizer = new OHOS::Ace::NG::SwipeRecognizer(1, direction, 100);
    recognizer->recognizer = gestureRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_speed(recognizer, speed);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 2;
    ret = OH_ArkUI_GetGestureParam_speed(recognizer, speed);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED);
}

/**
 * @tc.name: NativeNodeGestureRecognizer019
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_duration function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer019, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    int duration = 500;
    auto ret = OH_ArkUI_GetGestureParam_duration(recognizer, &duration);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer020
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_duration function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer020, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    int* duration = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_duration(&recognizer, duration);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer021
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_duration function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer021, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 1, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    int durationNew = 500;
    int* duration = &durationNew;
    OHOS::Ace::NG::NGGestureRecognizer* longPressRecognizer =
        new OHOS::Ace::NG::LongPressRecognizer(500, 1, true, false, false);
    recognizer->recognizer = longPressRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_duration(recognizer, duration);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 4;
    ret = OH_ArkUI_GetGestureParam_duration(recognizer, duration);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED);
}

/**
 * @tc.name: NativeNodeGestureRecognizer022
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_angle function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer022, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    double angle = 1;
    auto ret = OH_ArkUI_GetGestureParam_angle(recognizer, &angle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer023
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_angle function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer023, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    double* angle = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_angle(&recognizer, angle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer024
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_angle function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer024, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 4, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    double angleNew = 1;
    double* angle = &angleNew;
    OHOS::Ace::NG::NGGestureRecognizer* rotationRecognizer = new OHOS::Ace::NG::RotationRecognizer(1, 1);
    recognizer->recognizer = rotationRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_angle(recognizer, angle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = 2;
    ret = OH_ArkUI_GetGestureParam_angle(recognizer, angle);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED);
}

/**
 * @tc.name: NativeNodeGestureRecognizer025
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_distanceThreshold function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer025, TestSize.Level1)
{
    ArkUI_GestureRecognizer* recognizer = nullptr;
    double distanceThreshold = std::numeric_limits<double>::infinity();
    auto ret = OH_ArkUI_GetGestureParam_distanceThreshold(recognizer, &distanceThreshold);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer026
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_distanceThreshold function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer026, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    double* distanceThreshold = nullptr;
    auto ret = OH_ArkUI_GetGestureParam_distanceThreshold(&recognizer, distanceThreshold);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeGestureRecognizer027
 * @tc.desc: Test the OH_ArkUI_GetGestureParam_distanceThreshold function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, NativeNodeGestureRecognizer027, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizerNew = { 0, nullptr, nullptr, nullptr };
    ArkUI_GestureRecognizer* recognizer = &recognizerNew;
    double distanceThresholdNew = std::numeric_limits<double>::infinity();
    double* distanceThreshold = &distanceThresholdNew;
    double distanceThresholdAnother = std::numeric_limits<double>::infinity();
    OHOS::Ace::NG::NGGestureRecognizer* tapRecognizer =
        new OHOS::Ace::NG::ClickRecognizer(1, 1, distanceThresholdAnother);
    recognizer->recognizer = tapRecognizer;
    auto ret = OH_ArkUI_GetGestureParam_distanceThreshold(recognizer, distanceThreshold);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    recognizer->type = -1;
    ret = OH_ArkUI_GetGestureParam_distanceThreshold(recognizer, distanceThreshold);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED);
}

/**
 * @tc.name: GestureImplTest001
 * @tc.desc: Test the OH_ArkUI_GestureEvent_GetActionType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest001, TestSize.Level1)
{
    ArkUI_GestureEvent event;
    event.eventData.subKind = ON_ACTION;
    EXPECT_EQ(OH_ArkUI_GestureEvent_GetActionType(&event), GESTURE_EVENT_ACTION_ACCEPT);

    event.eventData.subKind = ON_ACTION_START;
    EXPECT_EQ(OH_ArkUI_GestureEvent_GetActionType(&event), GESTURE_EVENT_ACTION_ACCEPT);

    event.eventData.subKind = ON_ACTION_UPDATE;
    EXPECT_EQ(OH_ArkUI_GestureEvent_GetActionType(&event), GESTURE_EVENT_ACTION_UPDATE);

    event.eventData.subKind = ON_ACTION_END;
    EXPECT_EQ(OH_ArkUI_GestureEvent_GetActionType(&event), GESTURE_EVENT_ACTION_END);

    event.eventData.subKind = ON_ACTION_CANCEL;
    EXPECT_EQ(OH_ArkUI_GestureEvent_GetActionType(&event), GESTURE_EVENT_ACTION_CANCEL);

    event.eventData.subKind = -1;
    EXPECT_EQ(OH_ArkUI_GestureEvent_GetActionType(&event), GESTURE_EVENT_ACTION_ACCEPT);
}

/**
* @tc.name: GestureImplTest002
* @tc.desc: Test the OH_ArkUI_GestureEvent_GetRawInputEvent function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest002, TestSize.Level1)
{
    auto* ret1 = OH_ArkUI_GestureEvent_GetRawInputEvent(nullptr);
    EXPECT_EQ(ret1, nullptr);

    ArkUI_GestureEvent event;
    ArkUI_UIInputEvent inputEvent;
    event.eventData.repeat = 10;
    event.eventData.velocity = 10.0f;
    event.eventData.velocityX = 11.0f;
    event.eventData.velocityY = 12.0f;
    event.eventData.x = 13.0f;
    event.eventData.y = 14.0f;
    event.eventData.angle = 15.0f;
    event.eventData.speed = 16.0f;
    event.eventData.scale = 17.0f;
    event.eventData.pinchCenterX = 18.0f;
    event.eventData.pinchCenterY = 19.0f;
    event.eventData.rawPointerEvent = &inputEvent;
    auto* ret2 = OH_ArkUI_GestureEvent_GetRawInputEvent(&event);
    auto repeat = OH_ArkUI_LongPress_GetRepeatCount(&event);
    auto velocity = OH_ArkUI_PanGesture_GetVelocity(&event);
    auto velocityX = OH_ArkUI_PanGesture_GetVelocityX(&event);
    auto velocityY = OH_ArkUI_PanGesture_GetVelocityY(&event);
    auto x = OH_ArkUI_PanGesture_GetOffsetX(&event);
    auto y = OH_ArkUI_PanGesture_GetOffsetY(&event);
    auto swipeAngle = OH_ArkUI_SwipeGesture_GetAngle(&event);
    auto speed = OH_ArkUI_SwipeGesture_GetVelocity(&event);
    auto rotationAngle = OH_ArkUI_RotationGesture_GetAngle(&event);
    auto scale = OH_ArkUI_PinchGesture_GetScale(&event);
    auto pinchCenterX = OH_ArkUI_PinchGesture_GetCenterX(&event);
    auto pinchCenterY = OH_ArkUI_PinchGesture_GetCenterY(&event);
    EXPECT_NE(ret2, nullptr);
    EXPECT_EQ(repeat, 10);
    EXPECT_EQ(velocity, 10.0f);
    EXPECT_EQ(velocityX, 11.0f);
    EXPECT_EQ(velocityY, 12.0f);
    EXPECT_EQ(x, 13.0f);
    EXPECT_EQ(y, 14.0f);
    EXPECT_EQ(swipeAngle, 15.0f);
    EXPECT_EQ(speed, 16.0f);
    EXPECT_EQ(rotationAngle, 15.0f);
    EXPECT_EQ(scale, 17.0f);
    EXPECT_EQ(pinchCenterX, 18.0f);
    EXPECT_EQ(pinchCenterY, 19.0f);
}

/**
* @tc.name: GestureImplTest003
* @tc.desc: Test the OH_ArkUI_GestureEvent_GetNode function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest003, TestSize.Level1)
{
    auto* ret1 = OH_ArkUI_GestureEvent_GetNode(nullptr);
    EXPECT_EQ(ret1, nullptr);

    ArkUI_GestureEvent event;
    ArkUI_NodeHandle node;
    event.eventData.repeat = 10;
    event.attachNode = &node;
    auto* ret2 = OH_ArkUI_GestureEvent_GetNode(&event);
    EXPECT_NE(ret2, nullptr);
}

/**
* @tc.name: GestureImplTest004
* @tc.desc: Test the OH_ArkUI_GestureInterruptInfo_GetSystemFlag function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest004, TestSize.Level1)
{
    ArkUI_GestureInterruptInfo interruptInfo;
    interruptInfo.interruptData.isSystemGesture = true;
    auto result = OH_ArkUI_GestureInterruptInfo_GetSystemFlag(&interruptInfo);
    EXPECT_TRUE(result);

    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    interruptInfo.interruptData.userData = recognizer;
    auto* re1 = OH_ArkUI_GestureInterruptInfo_GetRecognizer(&interruptInfo);
    EXPECT_NE(re1, nullptr);
}

/**
* @tc.name: GestureImplTest005
* @tc.desc: Test the OH_ArkUI_GestureInterruptInfo_GetGestureEvent function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest005, TestSize.Level1)
{
    auto* ret1 = OH_ArkUI_GestureInterruptInfo_GetGestureEvent(nullptr);
    EXPECT_EQ(ret1, nullptr);

    ArkUI_GestureInterruptInfo interruptInfo;
    interruptInfo.interruptData.gestureEvent = nullptr;
    auto* re2 = OH_ArkUI_GestureInterruptInfo_GetGestureEvent(&interruptInfo);
    EXPECT_EQ(re2, nullptr);

    ArkUI_GestureEvent event;
    event.eventData.repeat = 10;
    interruptInfo.interruptData.gestureEvent = &event;
    interruptInfo.interruptData.inputEvent = nullptr;
    ArkUI_GestureEvent* gestureEvent = reinterpret_cast<ArkUI_GestureEvent*>(interruptInfo.interruptData.gestureEvent);
    EXPECT_EQ(gestureEvent->eventData.rawPointerEvent, nullptr);

    interruptInfo.interruptData.userData = nullptr;
    auto* re3 = OH_ArkUI_GestureInterruptInfo_GetGestureEvent(&interruptInfo);
    EXPECT_EQ(re3, nullptr);

    auto* nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto* gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    interruptInfo.interruptData.userData = reinterpret_cast<void*>(gestureNode);
    auto* re4 = OH_ArkUI_GestureInterruptInfo_GetGestureEvent(&interruptInfo);
    EXPECT_NE(re4, nullptr);
}

/**
* @tc.name: GestureImplTest006
* @tc.desc: Test the OH_ArkUI_GestureInterruptInfo_GetSystemRecognizerType function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest006, TestSize.Level1)
{
    ArkUI_GestureInterruptInfo interruptInfo;
    interruptInfo.interruptData.isSystemGesture = true;
    interruptInfo.interruptData.systemRecognizerType = 10;
    auto result = OH_ArkUI_GestureInterruptInfo_GetSystemRecognizerType(&interruptInfo);
    EXPECT_EQ(result, 10);

    interruptInfo.interruptData.isSystemGesture = false;
    result = OH_ArkUI_GestureInterruptInfo_GetSystemRecognizerType(&interruptInfo);
    EXPECT_EQ(result, -1);
}

/**
* @tc.name: GestureImplTest007
* @tc.desc: Test the OH_ArkUI_GestureInterruptInfo_GetTouchRecognizers function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest007, TestSize.Level1)
{
    ArkUI_GestureInterruptInfo interruptInfo;
    ArkUI_TouchRecognizerHandleArray recognizers;
    interruptInfo.interruptData.touchRecognizerCnt = 10;

    int32_t size;
    auto ret1 = OH_ArkUI_GestureInterruptInfo_GetTouchRecognizers(nullptr, &recognizers, &size);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GestureInterruptInfo_GetTouchRecognizers(&interruptInfo, nullptr, &size);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret3 = OH_ArkUI_GestureInterruptInfo_GetTouchRecognizers(&interruptInfo, &recognizers, nullptr);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret4 = OH_ArkUI_GestureInterruptInfo_GetTouchRecognizers(&interruptInfo, &recognizers, &size);
    EXPECT_EQ(ret4, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(size, 10);
}

/**
* @tc.name: GestureImplTest008
* @tc.desc: Test the OH_ArkUI_TouchRecognizer_GetNodeHandle function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest008, TestSize.Level1)
{
    auto ret1 = OH_ArkUI_TouchRecognizer_GetNodeHandle(nullptr);
    EXPECT_EQ(ret1, nullptr);
}

/**
* @tc.name: GestureImplTest009
* @tc.desc: Test the OH_ArkUI_TouchRecognizer_CancelTouch function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest009, TestSize.Level1)
{
    ArkUI_GestureInterruptInfo interruptInfo;
    interruptInfo.interruptData.touchRecognizerCnt = 10;
    auto ret1 = OH_ArkUI_TouchRecognizer_CancelTouch(nullptr, &interruptInfo);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
* @tc.name: GestureImplTest0010
* @tc.desc: Test the OH_ArkUI_GetResponseRecognizersFromInterruptInfo function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0010, TestSize.Level1)
{
    ArkUI_GestureRecognizerHandleArray recognizers;
    ArkUI_GestureInterruptInfo interruptInfo;
    interruptInfo.interruptData.count = 10;
    int32_t count = 10;
    auto ret1 = OH_ArkUI_GetResponseRecognizersFromInterruptInfo(&interruptInfo, nullptr, &count);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GetResponseRecognizersFromInterruptInfo(&interruptInfo, &recognizers, nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret3 = OH_ArkUI_GetResponseRecognizersFromInterruptInfo(&interruptInfo, &recognizers, &count);
    EXPECT_EQ(ret3, 0);
    EXPECT_EQ(count, 10);
}

/**
* @tc.name: GestureImplTest0011
* @tc.desc: Test the OH_ArkUI_SetGestureRecognizerEnabled function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0011, TestSize.Level1)
{
    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    auto ret1 = OH_ArkUI_SetGestureRecognizerEnabled(nullptr, true);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_SetGestureRecognizerEnabled(recognizer, true);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);

    auto ret3 = OH_ArkUI_GetGestureRecognizerEnabled(nullptr);
    EXPECT_EQ(ret3, false);
    auto ret4 = OH_ArkUI_GetGestureRecognizerEnabled(recognizer);
    EXPECT_EQ(ret4, false);

    auto ret5 = OH_ArkUI_SetGestureRecognizerLimitFingerCount(recognizer, true);
    EXPECT_EQ(ret5, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
* @tc.name: GestureImplTest0012
* @tc.desc: Test the OH_ArkUI_GetGestureRecognizerState function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0012, TestSize.Level1)
{
    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    ArkUI_GestureRecognizerState state;
    auto ret1 = OH_ArkUI_GetGestureRecognizerState(nullptr, &state);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GetGestureRecognizerState(recognizer, &state);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
* @tc.name: GestureImplTest0013
* @tc.desc: Test the OH_ArkUI_GetGestureEventTargetInfo function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0013, TestSize.Level1)
{
    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    ArkUI_GestureEventTargetInfo* info = nullptr;
    auto ret1 = OH_ArkUI_GetGestureEventTargetInfo(nullptr, &info);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GetGestureEventTargetInfo(recognizer, &info);
    EXPECT_EQ(ret2, 0);
    EXPECT_NE(info, nullptr);
}

/**
* @tc.name: GestureImplTest0014
* @tc.desc: Test the OH_ArkUI_GestureEventTargetInfo_IsScrollBegin function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0014, TestSize.Level1)
{
    ArkUI_GestureEventTargetInfo info;
    bool ret = false;
    auto ret1 = OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(nullptr, &ret);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(&info, &ret);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
* @tc.name: GestureImplTest0015
* @tc.desc: Test the OH_ArkUI_GestureEventTargetInfo_IsScrollEnd function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0015, TestSize.Level1)
{
    ArkUI_GestureEventTargetInfo info;
    bool ret = false;
    auto ret1 = OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(nullptr, &ret);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(&info, &ret);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
* @tc.name: GestureImplTest0016
* @tc.desc: Test the OH_ArkUI_GetPanGestureDirectionMask function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0016, TestSize.Level1)
{
    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    ArkUI_GestureDirectionMask mask;
    auto ret1 = OH_ArkUI_GetPanGestureDirectionMask(nullptr, &mask);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GetPanGestureDirectionMask(recognizer, &mask);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
* @tc.name: GestureImplTest0017
* @tc.desc: Test the OH_ArkUI_IsBuiltInGesture function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0017, TestSize.Level1)
{
    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    auto ret1 = OH_ArkUI_IsBuiltInGesture(nullptr);
    EXPECT_EQ(ret1, false);
    auto ret2 = OH_ArkUI_IsBuiltInGesture(recognizer);
    EXPECT_EQ(ret2, false);
}

/**
* @tc.name: GestureImplTest0018
* @tc.desc: Test the OH_ArkUI_GetGestureTag function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0018, TestSize.Level1)
{
    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    char buffer[100];
    int32_t bufferSize = 100;
    int32_t result = 0;
    auto ret1 = OH_ArkUI_GetGestureTag(nullptr, buffer, bufferSize, &result);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GetGestureTag(recognizer, buffer, bufferSize, &result);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
* @tc.name: GestureImplTest0019
* @tc.desc: Test the OH_ArkUI_GetGestureBindNodeId function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0019, TestSize.Level1)
{
    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    char nodeId[128];
    std::fill_n(nodeId, sizeof(nodeId), 0);
    auto ret1 = OH_ArkUI_GetGestureBindNodeId(nullptr, nodeId, sizeof(nodeId), nullptr);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_GetGestureBindNodeId(recognizer, nodeId, sizeof(nodeId), nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
* @tc.name: GestureImplTest0020
* @tc.desc: Test the OH_ArkUI_IsGestureRecognizerValid function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0020, TestSize.Level1)
{
    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    auto ret1 = OH_ArkUI_IsGestureRecognizerValid(nullptr);
    EXPECT_EQ(ret1, false);
    auto ret2 = OH_ArkUI_IsGestureRecognizerValid(recognizer);
    EXPECT_EQ(ret2, false);
}

/**
* @tc.name: GestureImplTest0021
* @tc.desc: Test the OH_ArkUI_ParallelInnerGestureEvent_GetUserData function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0021, TestSize.Level1)
{
    auto *event = new ArkUI_ParallelInnerGestureEvent();
    auto ret1 = OH_ArkUI_ParallelInnerGestureEvent_GetUserData(event);
    EXPECT_EQ(ret1, nullptr);
}

/**
* @tc.name: GestureImplTest0022
* @tc.desc: Test the OH_ArkUI_ParallelInnerGestureEvent_GetCurrentRecognizer function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0022, TestSize.Level1)
{
    auto *event = new ArkUI_ParallelInnerGestureEvent();
    auto ret1 = OH_ArkUI_ParallelInnerGestureEvent_GetCurrentRecognizer(event);
    EXPECT_EQ(ret1, nullptr);
}

/**
* @tc.name: GestureImplTest0023
* @tc.desc: Test the OH_ArkUI_ParallelInnerGestureEvent_GetConflictRecognizers function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0023, TestSize.Level1)
{
    ArkUI_ParallelInnerGestureEvent *event = new ArkUI_ParallelInnerGestureEvent();
    ArkUI_GestureRecognizerHandleArray array;
    int32_t size = 0;
    event->count = 10;
    auto ret1 = OH_ArkUI_ParallelInnerGestureEvent_GetConflictRecognizers(event, nullptr, &size);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_ParallelInnerGestureEvent_GetConflictRecognizers(event, &array, nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret3 = OH_ArkUI_ParallelInnerGestureEvent_GetConflictRecognizers(event, &array, &size);
    EXPECT_EQ(ret3, 0);
    EXPECT_EQ(size, 10);
}

/**
* @tc.name: GestureImplTest0024
* @tc.desc: Test the OH_ArkUI_SetArkUIGestureRecognizerDisposeNotify function.
* @tc.type: FUNC
*/
HWTEST_F(NativeGestureTest, GestureImplTest0024, TestSize.Level1)
{
    ArkUI_GestureRecognizer recognizer;
    ArkUI_GestureRecognizerDisposeNotifyCallback callback = nullptr;
    auto ret1 = OH_ArkUI_SetArkUIGestureRecognizerDisposeNotify(nullptr, callback, nullptr);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto ret2 = OH_ArkUI_SetArkUIGestureRecognizerDisposeNotify(&recognizer, callback, nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: GestureImplTest0025
 * @tc.desc: Test the CreateTapGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0025, TestSize.Level1)
{
    int32_t count = 1;
    int32_t fingers = 11;
    auto ret = OHOS::Ace::GestureModel::CreateTapGesture(count, fingers);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: GestureImplTest0026
 * @tc.desc: Test the CreateTapGestureWithDistanceThreshold function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0026, TestSize.Level1)
{
    int32_t count = 1;
    int32_t fingers = 11;
    double distanceThreshold = 10.0;
    auto ret = OHOS::Ace::GestureModel::CreateTapGestureWithDistanceThreshold(count, fingers, distanceThreshold);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: GestureImplTest0027
 * @tc.desc: Test the CreateLongPressGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0027, TestSize.Level1)
{
    int32_t fingers = 11;
    bool repeatResult = true;
    int32_t duration = 100;
    auto ret = OHOS::Ace::GestureModel::CreateLongPressGesture(fingers, repeatResult, duration);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: GestureImplTest0028
 * @tc.desc: Test the CreateLongPressGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0028, TestSize.Level1)
{
    int32_t fingers = 11;
    bool repeatResult = true;
    int32_t duration = 100;
    auto ret = OHOS::Ace::GestureModel::CreateLongPressGesture(fingers, repeatResult, duration);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: GestureImplTest0029
 * @tc.desc: Test the CreatePinchGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0029, TestSize.Level1)
{
    int32_t fingers = 11;
    double distance1 = 10.0;
    auto ret1 = OHOS::Ace::GestureModel::CreatePinchGesture(fingers, distance1);
    EXPECT_NE(ret1, nullptr);
    double distance2 = 0.0;
    auto ret2 = OHOS::Ace::GestureModel::CreatePinchGesture(fingers, distance2);
    EXPECT_NE(ret2, nullptr);
}

/**
 * @tc.name: GestureImplTest0030
 * @tc.desc: Test the CreateRotationGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0030, TestSize.Level1)
{
    int32_t fingers = 11;
    double angle = 10.0;
    auto ret = OHOS::Ace::GestureModel::CreateRotationGesture(fingers, angle);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: GestureImplTest0031
 * @tc.desc: Test the CreateSwipeGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0031, TestSize.Level1)
{
    int32_t fingers = 11;
    ArkUI_GestureDirectionMask directions = 1;
    double speed1 = 10.0;
    auto ret1 = OHOS::Ace::GestureModel::CreateSwipeGesture(fingers, directions, speed1);
    EXPECT_NE(ret1, nullptr);
    double speed2 = 0.0;
    auto ret2 = OHOS::Ace::GestureModel::CreateSwipeGesture(fingers, directions, speed2);
    EXPECT_NE(ret2, nullptr);
}

/**
 * @tc.name: GestureImplTest0032
 * @tc.desc: Test the CreatePanGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0032, TestSize.Level1)
{
    int32_t fingers = 2;
    ArkUI_GestureDirectionMask directions = 1;
    double distanceNum = 10.0;
    auto ret1 = OHOS::Ace::GestureModel::CreatePanGesture(fingers, directions, distanceNum);
    EXPECT_NE(ret1, nullptr);
    fingers = 20;
    auto ret2 = OHOS::Ace::GestureModel::CreatePanGesture(fingers, directions, distanceNum);
    EXPECT_NE(ret2, nullptr);
}

/**
 * @tc.name: GestureImplTest0033
 * @tc.desc: Test the DisposeGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0033, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto longPressGesture = gestureAPI->gestureApi1->createLongPressGesture(1, true, 500);
    OHOS::Ace::GestureModel::DisposeGesture(longPressGesture);
    EXPECT_EQ(longPressGesture->extraData, nullptr);
}

/**
 * @tc.name: GestureImplTest0034
 * @tc.desc: Test the SetGestureEventTarget function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0034, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto longPressGesture = gestureAPI->gestureApi1->createLongPressGesture(1, true, 500);
    auto onActionCallBack = [](ArkUI_GestureEvent *event, void *extraParam) {};
    auto ret = OHOS::Ace::GestureModel::SetGestureEventTarget(
        longPressGesture, GESTURE_EVENT_ACTION_ACCEPT, gestureNode, onActionCallBack);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GestureImplTest0035
 * @tc.desc: Test the AddGestureToNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0035, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto longPressGesture = gestureAPI->gestureApi1->createLongPressGesture(1, true, 500);
    auto ret = OHOS::Ace::GestureModel::AddGestureToNode(gestureNode, longPressGesture, PRIORITY, NORMAL_GESTURE_MASK);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GestureImplTest0036
 * @tc.desc: Test the RemoveGestureFromNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0036, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto longPressGesture = gestureAPI->gestureApi1->createLongPressGesture(1, true, 500);
    auto ret = OHOS::Ace::GestureModel::RemoveGestureFromNode(gestureNode, longPressGesture);
    EXPECT_EQ(longPressGesture->targetInfo.uiNode, nullptr);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GestureImplTest0037
 * @tc.desc: Test the CreateGroupGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0037, TestSize.Level1)
{
    auto ret = OHOS::Ace::GestureModel::CreateGroupGesture(EXCLUSIVE_GROUP);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: GestureImplTest0038
 * @tc.desc: Test the AddChildGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0038, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto group = gestureAPI->gestureApi1->createGroupGesture(EXCLUSIVE_GROUP);
    auto tapGesture = gestureAPI->gestureApi1->createTapGesture(1, 1);
    auto ret = OHOS::Ace::GestureModel::AddChildGesture(group, tapGesture);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GestureImplTest0039
 * @tc.desc: Test the GetGestureType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0039, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto longPressGesture = gestureAPI->gestureApi1->createLongPressGesture(1, true, 500);
    longPressGesture->type = 2;
    auto ret = OHOS::Ace::GestureModel::GetGestureType(longPressGesture);
    EXPECT_EQ(ret, 2);
}

/**
 * @tc.name: GestureImplTest0040
 * @tc.desc: Test the RemoveChildGesture function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0040, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto group = gestureAPI->gestureApi1->createGroupGesture(EXCLUSIVE_GROUP);
    auto tapGesture = gestureAPI->gestureApi1->createTapGesture(1, 1);
    auto ret = OHOS::Ace::GestureModel::RemoveChildGesture(group, tapGesture);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GestureImplTest0041
 * @tc.desc: Test the HandleGestureEvent function.
 * @tc.type: FUNC
 */
void MockTargetReceiver(ArkUI_GestureEvent* event, void* extraParam)
{
    EXPECT_NE(event->eventData.rawPointerEvent, nullptr);
}
void MockTargetReceiver2(ArkUI_GestureEvent* event, void* extraParam)
{
    EXPECT_NE(event->eventData.rawPointerEvent, nullptr);
    EXPECT_EQ(event->attachNode, nullptr);
}
HWTEST_F(NativeGestureTest, GestureImplTest0041, TestSize.Level1)
{
    ArkUINodeEvent* event1 = nullptr;
    OHOS::Ace::GestureModel::HandleGestureEvent(event1);
    EXPECT_EQ(event1, nullptr);

    ArkUINodeEvent event2;
    event2.extraParam = 0;
    OHOS::Ace::GestureModel::HandleGestureEvent(&event2);
    EXPECT_EQ(event2.extraParam, 0);

    ArkUINodeEvent event3 = {0};
    OHOS::Ace::GestureModel::GestureInnerData extraData;
    extraData.gesture = nullptr;
    extraData.targetReceiver = MockTargetReceiver;
    extraData.extraParam = nullptr;
    event3.kind = ArkUIEventCategory::GESTURE_ASYNC_EVENT;
    event3.extraParam = reinterpret_cast<ArkUI_Int64>(&extraData);
    event3.gestureAsyncEvent.inputEventType = static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_MOUSE);
    event3.gestureAsyncEvent.rawPointerEvent = nullptr;
    OHOS::Ace::GestureModel::HandleGestureEvent(&event3);
    event3.gestureAsyncEvent.rawPointerEvent = nullptr;
    event3.kind = ArkUIEventCategory::INVALID;
    event3.gestureAsyncEvent.inputEventType = static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_AXIS);
    OHOS::Ace::GestureModel::HandleGestureEvent(&event3);
    event3.gestureAsyncEvent.rawPointerEvent = nullptr;
    event3.gestureAsyncEvent.inputEventType = static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_TOUCH);
    OHOS::Ace::GestureModel::HandleGestureEvent(&event3);
    event3.gestureAsyncEvent.inputEventType = static_cast<int32_t>(ARKUI_UIINPUTEVENT_TYPE_KEY);
    OHOS::Ace::GestureModel::HandleGestureEvent(&event3);

    ArkUI_GestureRecognizer *recognizer = new ArkUI_GestureRecognizer();
    recognizer->attachNode = nullptr;
    extraData.gesture = reinterpret_cast<ArkUI_GestureRecognizer*>(recognizer);
    extraData.targetReceiver = MockTargetReceiver2;
    event3.extraParam = reinterpret_cast<ArkUI_Int64>(&extraData);
    OHOS::Ace::GestureModel::HandleGestureEvent(&event3);
    ArkUI_GestureEvent* gestureEvent = reinterpret_cast<ArkUI_GestureEvent *>(&event3.gestureAsyncEvent);
    ASSERT_EQ(gestureEvent->eventData.rawPointerEvent, nullptr);
}

/**
 * @tc.name: GestureImplTest0042
 * @tc.desc: Test the SetGestureInterrupterToNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0042, TestSize.Level1)
{
    auto interrupter = [](ArkUI_GestureInterruptInfo* info) -> ArkUI_GestureInterruptResult {
        return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
    };
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto ret = OHOS::Ace::GestureModel::SetGestureInterrupterToNode(gestureNode, interrupter);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GestureImplTest0043
 * @tc.desc: Test the SetGestureInterrupterToNodeWithUserData function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0043, TestSize.Level1)
{
    auto interrupter = [](ArkUI_GestureInterruptInfo* info) -> ArkUI_GestureInterruptResult {
        return ArkUI_GestureInterruptResult::GESTURE_INTERRUPT_RESULT_CONTINUE;
    };
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    void* userData = reinterpret_cast<void*>(new int);
    auto ret = OHOS::Ace::GestureModel::SetGestureInterrupterToNodeWithUserData(gestureNode, userData, interrupter);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GestureImplTest0044
 * @tc.desc: Test the SetInnerGestureParallelTo function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0044, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    void* userData = reinterpret_cast<void*>(new int);
    auto ret = OHOS::Ace::GestureModel::SetInnerGestureParallelTo(gestureNode, userData, nullptr);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: GestureImplTest0045
 * @tc.desc: Test the AddGestureToNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeGestureTest, GestureImplTest0045, TestSize.Level1)
{
    auto gestureAPI = reinterpret_cast<ArkUI_NativeGestureAPI_2*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_2"));
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto gestureNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto tapGesture = gestureAPI->gestureApi1->createTapGesture(1, 1);
    auto ret = OHOS::Ace::GestureModel::AddGestureToNode(gestureNode, tapGesture, PRIORITY, NORMAL_GESTURE_MASK);
    EXPECT_EQ(ret, 0);
}