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

#include "test/unittest/core/event/drag_event_test_ng.h"
#include "test/unittest/core/event/drag_event_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct DragInfo {
    bool isDragForbidden = false;
    bool isDraggable = false;
    bool isCustomerSet = false;
    bool textIsSelected = false;
    DragInfo(bool isDragForbidden, bool isDraggable, bool isCustomerSet, bool textIsSelected)
        : isDragForbidden(isDragForbidden), isDraggable(isDraggable),
          isCustomerSet(isCustomerSet), textIsSelected(textIsSelected) {}
};
struct DragStatusTestCase {
    DragInfo dragInfo;
    InputEventType inputEventType;
    bool expectResult = false;
    DragStatusTestCase(DragInfo dragInfo, InputEventType inputEventType, bool expectResult)
        : dragInfo(dragInfo), inputEventType(inputEventType), expectResult(expectResult) {}
};

const std::vector<DragStatusTestCase> DRAG_STATUS_IMAGE_TEST_CASES = {
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::TOUCH_SCREEN, false),   // case 0
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::TOUCH_PAD, false),      // case 1
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::MOUSE_BUTTON, false),   // case 2
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::AXIS, false),           // case 3
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::KEYBOARD, false),       // case 4
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::TOUCH_SCREEN, false),  // case 5
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::TOUCH_PAD, false),     // case 6
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::MOUSE_BUTTON, false),  // case 7
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::AXIS, false),          // case 8
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::KEYBOARD, false),      // case 9

    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::TOUCH_SCREEN, false),  // case 10
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::TOUCH_PAD, false),     // case 11
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::MOUSE_BUTTON, false),  // case 12
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::AXIS, false),          // case 13
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::KEYBOARD, false),      // case 14
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::TOUCH_SCREEN, false), // case 15
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::TOUCH_PAD, false),    // case 16
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::MOUSE_BUTTON, false), // case 17
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::AXIS, false),         // case 18
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::KEYBOARD, false),     // case 19
    
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::TOUCH_SCREEN, true),   // case 20
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::TOUCH_PAD, true),      // case 21
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::MOUSE_BUTTON, true),   // case 22
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::AXIS, false),          // case 23
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::KEYBOARD, true),       // case 24
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::TOUCH_SCREEN, true),  // case 25
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::TOUCH_PAD, true),     // case 26
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::MOUSE_BUTTON, true),  // case 27
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::AXIS, false),         // case 28
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::KEYBOARD, true),      // case 29

    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::TOUCH_SCREEN, false), // case 30
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::TOUCH_PAD, false),    // case 31
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::MOUSE_BUTTON, false), // case 32
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::AXIS, false),         // case 33
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::KEYBOARD, false),     // case 34
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::TOUCH_SCREEN, true), // case 35
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::TOUCH_PAD, true),    // case 36
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::MOUSE_BUTTON, true), // case 37
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::AXIS, false),        // case 38
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::KEYBOARD, true),     // case 39
};

const std::vector<DragStatusTestCase> DRAG_STATUS_TEXT_TEST_CASES = {
    DragStatusTestCase(DragInfo(true, true, true, true), InputEventType::TOUCH_SCREEN, false),    // case 0
    DragStatusTestCase(DragInfo(true, true, true, true), InputEventType::TOUCH_PAD, false),       // case 1
    DragStatusTestCase(DragInfo(true, true, true, true), InputEventType::MOUSE_BUTTON, false),    // case 2
    DragStatusTestCase(DragInfo(true, true, true, true), InputEventType::AXIS, false),            // case 3
    DragStatusTestCase(DragInfo(true, true, true, true), InputEventType::KEYBOARD, false),        // case 4
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::TOUCH_SCREEN, false),   // case 5
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::TOUCH_PAD, false),      // case 6
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::MOUSE_BUTTON, false),   // case 7
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::AXIS, false),           // case 8
    DragStatusTestCase(DragInfo(true, true, true, false), InputEventType::KEYBOARD, false),       // case 9

    DragStatusTestCase(DragInfo(true, true, false, true), InputEventType::TOUCH_SCREEN, false),   // case 10
    DragStatusTestCase(DragInfo(true, true, false, true), InputEventType::TOUCH_PAD, false),      // case 11
    DragStatusTestCase(DragInfo(true, true, false, true), InputEventType::MOUSE_BUTTON, false),   // case 12
    DragStatusTestCase(DragInfo(true, true, false, true), InputEventType::AXIS, false),           // case 13
    DragStatusTestCase(DragInfo(true, true, false, true), InputEventType::KEYBOARD, false),       // case 14
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::TOUCH_SCREEN, false),  // case 15
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::TOUCH_PAD, false),     // case 16
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::MOUSE_BUTTON, false),  // case 17
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::AXIS, false),          // case 18
    DragStatusTestCase(DragInfo(true, true, false, false), InputEventType::KEYBOARD, false),      // case 19

    DragStatusTestCase(DragInfo(true, false, true, true), InputEventType::TOUCH_SCREEN, false),   // case 20
    DragStatusTestCase(DragInfo(true, false, true, true), InputEventType::TOUCH_PAD, false),      // case 21
    DragStatusTestCase(DragInfo(true, false, true, true), InputEventType::MOUSE_BUTTON, false),   // case 22
    DragStatusTestCase(DragInfo(true, false, true, true), InputEventType::AXIS, false),           // case 23
    DragStatusTestCase(DragInfo(true, false, true, true), InputEventType::KEYBOARD, false),       // case 24
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::TOUCH_SCREEN, false),  // case 25
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::TOUCH_PAD, false),     // case 26
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::MOUSE_BUTTON, false),  // case 27
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::AXIS, false),          // case 28
    DragStatusTestCase(DragInfo(true, false, true, false), InputEventType::KEYBOARD, false),      // case 29

    DragStatusTestCase(DragInfo(true, false, false, true), InputEventType::TOUCH_SCREEN, false),  // case 30
    DragStatusTestCase(DragInfo(true, false, false, true), InputEventType::TOUCH_PAD, false),     // case 31
    DragStatusTestCase(DragInfo(true, false, false, true), InputEventType::MOUSE_BUTTON, false),  // case 32
    DragStatusTestCase(DragInfo(true, false, false, true), InputEventType::AXIS, false),          // case 33
    DragStatusTestCase(DragInfo(true, false, false, true), InputEventType::KEYBOARD, false),      // case 34
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::TOUCH_SCREEN, false), // case 35
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::TOUCH_PAD, false),    // case 36
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::MOUSE_BUTTON, false), // case 37
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::AXIS, false),         // case 38
    DragStatusTestCase(DragInfo(true, false, false, false), InputEventType::KEYBOARD, false),     // case 39

    DragStatusTestCase(DragInfo(false, true, true, true), InputEventType::TOUCH_SCREEN, true),    // case 40
    DragStatusTestCase(DragInfo(false, true, true, true), InputEventType::TOUCH_PAD, true),       // case 41
    DragStatusTestCase(DragInfo(false, true, true, true), InputEventType::MOUSE_BUTTON, true),    // case 42
    DragStatusTestCase(DragInfo(false, true, true, true), InputEventType::AXIS, false),           // case 43
    DragStatusTestCase(DragInfo(false, true, true, true), InputEventType::KEYBOARD, true),        // case 44
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::TOUCH_SCREEN, false),  // case 45
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::TOUCH_PAD, false),     // case 46
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::MOUSE_BUTTON, false),  // case 47
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::AXIS, false),          // case 48
    DragStatusTestCase(DragInfo(false, true, true, false), InputEventType::KEYBOARD, false),      // case 49

    DragStatusTestCase(DragInfo(false, true, false, true), InputEventType::TOUCH_SCREEN, true),   // case 50
    DragStatusTestCase(DragInfo(false, true, false, true), InputEventType::TOUCH_PAD, true),      // case 51
    DragStatusTestCase(DragInfo(false, true, false, true), InputEventType::MOUSE_BUTTON, true),   // case 52
    DragStatusTestCase(DragInfo(false, true, false, true), InputEventType::AXIS, false),          // case 53
    DragStatusTestCase(DragInfo(false, true, false, true), InputEventType::KEYBOARD, true),       // case 54
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::TOUCH_SCREEN, false), // case 55
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::TOUCH_PAD, false),    // case 56
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::MOUSE_BUTTON, false), // case 57
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::AXIS, false),         // case 58
    DragStatusTestCase(DragInfo(false, true, false, false), InputEventType::KEYBOARD, false),     // case 59

    DragStatusTestCase(DragInfo(false, false, true, true), InputEventType::TOUCH_SCREEN, false),  // case 60
    DragStatusTestCase(DragInfo(false, false, true, true), InputEventType::TOUCH_PAD, false),     // case 61
    DragStatusTestCase(DragInfo(false, false, true, true), InputEventType::MOUSE_BUTTON, false),  // case 62
    DragStatusTestCase(DragInfo(false, false, true, true), InputEventType::AXIS, false),          // case 63
    DragStatusTestCase(DragInfo(false, false, true, true), InputEventType::KEYBOARD, false),      // case 64
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::TOUCH_SCREEN, false), // case 65
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::TOUCH_PAD, false),    // case 66
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::MOUSE_BUTTON, false), // case 67
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::AXIS, false),         // case 68
    DragStatusTestCase(DragInfo(false, false, true, false), InputEventType::KEYBOARD, false),     // case 69

    DragStatusTestCase(DragInfo(false, false, false, true), InputEventType::TOUCH_SCREEN, true),   // case 70
    DragStatusTestCase(DragInfo(false, false, false, true), InputEventType::TOUCH_PAD, true),      // case 77
    DragStatusTestCase(DragInfo(false, false, false, true), InputEventType::MOUSE_BUTTON, true),   // case 72
    DragStatusTestCase(DragInfo(false, false, false, true), InputEventType::AXIS, false),          // case 73
    DragStatusTestCase(DragInfo(false, false, false, true), InputEventType::KEYBOARD, true),       // case 74
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::TOUCH_SCREEN, false), // case 75
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::TOUCH_PAD, false),    // case 76
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::MOUSE_BUTTON, false), // case 77
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::AXIS, false),         // case 78
    DragStatusTestCase(DragInfo(false, false, false, false), InputEventType::KEYBOARD, false),     // case 79
};

/**
 * @tc.name: DragEventTestNGIssue001
 * @tc.desc: Test IsCurrentNodeStatusSuitableForDragging function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventTestNGIssue001, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_STATUS_IMAGE_TEST_CASES) {
        /**
         * @tc.steps: step1. create DragEventActuator.
         */
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
        ASSERT_NE(gestureEventHub, nullptr);
        gestureEventHub->SetDragForbiddenForcely(testCase.dragInfo.isDragForbidden);
        auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
            AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
        ASSERT_NE(dragEventActuator, nullptr);
        /**
         * @tc.steps: step2. call IsCurrentNodeStatusSuitableForDragging function.
         * @tc.expected: step2. drag status equals.
         */
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
        ASSERT_NE(frameNode, nullptr);
        frameNode->draggable_ = testCase.dragInfo.isDraggable;
        frameNode->customerSet_ = testCase.dragInfo.isCustomerSet;
        TouchRestrict dragTouchRestrict = { TouchRestrict::NONE };
        dragTouchRestrict.inputEventType = testCase.inputEventType;
        auto status = dragEventActuator->IsCurrentNodeStatusSuitableForDragging(frameNode, dragTouchRestrict);
        EXPECT_TRUE(IsDragEventStateEqual(caseNum, status, testCase.expectResult));
        caseNum++;
    }
}

/**
 * @tc.name: DragEventTestNGIssue002
 * @tc.desc: Test IsCurrentNodeStatusSuitableForDragging function when frameNode is text.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNg, DragEventTestNGIssue002, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : DRAG_STATUS_TEXT_TEST_CASES) {
        /**
         * @tc.steps: step1. create DragEventActuator.
         */
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
        ASSERT_NE(gestureEventHub, nullptr);
        gestureEventHub->SetDragForbiddenForcely(testCase.dragInfo.isDragForbidden);
        gestureEventHub->SetTextDraggable(true);
        auto dragEventActuator = AceType::MakeRefPtr<DragEventActuator>(
            AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), DRAG_DIRECTION, FINGERS_NUMBER, DISTANCE);
        ASSERT_NE(dragEventActuator, nullptr);
        /**
         * @tc.steps: step2. call IsCurrentNodeStatusSuitableForDragging function.
         * @tc.expected: step2. drag status equals.
         */
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        ASSERT_NE(frameNode, nullptr);
        frameNode->draggable_ = testCase.dragInfo.isDraggable;
        frameNode->customerSet_ = testCase.dragInfo.isCustomerSet;
        auto textPattern = frameNode->GetPattern<TextBase>();
        ASSERT_NE(textPattern, nullptr);
        if (testCase.dragInfo.textIsSelected) {
            textPattern->textSelector_.baseOffset = 0;
            textPattern->textSelector_.destinationOffset = 1;
        }
        TouchRestrict dragTouchRestrict = { TouchRestrict::NONE };
        dragTouchRestrict.inputEventType = testCase.inputEventType;
        auto status = dragEventActuator->IsCurrentNodeStatusSuitableForDragging(frameNode, dragTouchRestrict);
        EXPECT_TRUE(IsDragEventStateEqual(caseNum, status, testCase.expectResult));
        caseNum++;
    }
};

} // namespace OHOS::Ace::NG