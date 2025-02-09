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