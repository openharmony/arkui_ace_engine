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
