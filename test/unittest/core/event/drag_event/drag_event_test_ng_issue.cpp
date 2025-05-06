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

#include "test/unittest/core/event/drag_event/drag_event_common_test_ng.h"

#include "test/unittest/core/event/drag_event/drag_event_test_ng_issue_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct DragStatusTestCase {
    DragInfo dragInfo;
    InputEventType inputEventType;
    bool expectResult = false;
    DragStatusTestCase(DragInfo dragInfo, InputEventType inputEventType, bool expectResult)
        : dragInfo(dragInfo), inputEventType(inputEventType), expectResult(expectResult) {}
};

struct MenuStatusTestCase {
    bool isBindCustomMenu = false;
    bool isShow = false;
    MenuPreviewMode previewMode = MenuPreviewMode::NONE;
    bool expectResult = false;
};

struct UpdateDragCursorStyleTestCase {
    DragRet dragResult = DragRet::DRAG_DEFAULT;
    DragBehavior dragBehavior = DragBehavior::UNKNOWN;
    DragCursorStyleCore expectResult;
};

struct UpdateDragAllowDropTestCase {
    bool isCapi = false;
    std::set<std::string> allowDropSet;
    std::map<std::string, int64_t> summaryMap;
    DragBehavior dragBehavior = DragBehavior::UNKNOWN;
    bool isEnabled = true;
    bool isInDraggedFrameNode = false;
    DragCursorStyleCore expectResult = DragCursorStyleCore::MOVE;
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

const std::vector<MenuStatusTestCase> MENU_STATUS_TEST_CASES = {
    { false, false, MenuPreviewMode::NONE, true},
    { false, false, MenuPreviewMode::IMAGE, true},
    { false, false, MenuPreviewMode::CUSTOM, true},
    { false, true, MenuPreviewMode::NONE, true},
    { false, true, MenuPreviewMode::IMAGE, true},
    { false, true, MenuPreviewMode::CUSTOM, true},
    { true, false, MenuPreviewMode::NONE, false},
    { true, false, MenuPreviewMode::IMAGE, false},
    { true, false, MenuPreviewMode::CUSTOM, false},
    { true, true, MenuPreviewMode::NONE, true},
    { true, true, MenuPreviewMode::IMAGE, true},
    { true, true, MenuPreviewMode::CUSTOM, true}
};

const std::vector<UpdateDragCursorStyleTestCase> UPDATE_DRAG_CURSOR_TEST_CASES = {
    { DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, DragCursorStyleCore::COPY },
    { DragRet::ENABLE_DROP, DragBehavior::COPY, DragCursorStyleCore::COPY },
    { DragRet::ENABLE_DROP, DragBehavior::MOVE, DragCursorStyleCore::MOVE },
    { DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, DragCursorStyleCore::MOVE },
    { DragRet::DISABLE_DROP, DragBehavior::COPY, DragCursorStyleCore::MOVE },
    { DragRet::DISABLE_DROP, DragBehavior::MOVE, DragCursorStyleCore::MOVE }
};

const std::vector<UpdateDragAllowDropTestCase> UPDATE_DRAG_ALLOW_DROP_TEST_CASES = {
    { false, {}, {}, DragBehavior::UNKNOWN, true, true, DragCursorStyleCore::MOVE },
    { false, {}, {{"A", 1}}, DragBehavior::UNKNOWN, true, true, DragCursorStyleCore::MOVE },
    { false, {"A"}, {}, DragBehavior::UNKNOWN, true, true, DragCursorStyleCore::MOVE },

    { true, {}, {}, DragBehavior::UNKNOWN, true, true, DragCursorStyleCore::MOVE },
    { true, {}, {}, DragBehavior::UNKNOWN, true, false, DragCursorStyleCore::COPY },
    { true, {}, {}, DragBehavior::UNKNOWN, false, true, DragCursorStyleCore::MOVE },
    { true, {}, {}, DragBehavior::UNKNOWN, false, false, DragCursorStyleCore::MOVE },

    { true, {}, {}, DragBehavior::MOVE, false, false, DragCursorStyleCore::MOVE },
    { true, {}, {}, DragBehavior::COPY, false, false, DragCursorStyleCore::COPY }
};

class DragEventTestNgIssue : public DragEventCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void DragEventTestNgIssue::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DragEventTestNgIssue::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DragEventTestNGIssue001
 * @tc.desc: Test IsCurrentNodeStatusSuitableForDragging function when frameNode is image.
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue001, TestSize.Level1)
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
        eventHub->gestureEventHub_ = gestureEventHub;
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
        frameNode->eventHub_ = eventHub;
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
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue002, TestSize.Level1)
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
        eventHub->gestureEventHub_ = gestureEventHub;
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
        frameNode->eventHub_ = eventHub;
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

/**
 * @tc.name: DragEventTestNGIssue003
 * @tc.desc: Test SetDragPreviewOptions function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 1.0f);
    /**
     * @tc.steps: step2. call SetDragPreviewOptions function.
     * @tc.expected: step2. drag status equals.
     */
    DragPreviewOption dragPreviewOption;
    dragPreviewOption.options.opacity = 0.5f;
    frameNode->SetDragPreviewOptions(dragPreviewOption, false);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 1.0f);

    frameNode->SetDragPreviewOptions(dragPreviewOption);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.5f);

    dragPreviewOption.options.opacity = 0.3f;
    frameNode->SetDragPreviewOptions(dragPreviewOption, true);
    EXPECT_EQ(frameNode->GetDragPreviewOption().options.opacity, 0.3f);
};

/**
 * @tc.name: DragEventTestNGIssue004
 * @tc.desc: Test SetBindMenuStatus function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue004, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : MENU_STATUS_TEST_CASES) {
        /**
         * @tc.steps: step1. create GestureEventHub.
         */
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
        ASSERT_NE(gestureEventHub, nullptr);
        /**
         * @tc.steps: step2. call SetBindMenuStatus function.
         * @tc.expected: step2. drag status equals.
         */
        gestureEventHub->SetBindMenuStatus(testCase.isBindCustomMenu, testCase.isShow, testCase.previewMode);
        EXPECT_TRUE(IsDragEventStateEqual(caseNum, gestureEventHub->bindMenuStatus_.IsNotNeedShowPreview(),
            testCase.expectResult));
        caseNum++;
    }
};

/**
 * @tc.name: DragEventTestNGIssue005
 * @tc.desc: Test UpdateDragCursorStyle function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue005, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : UPDATE_DRAG_CURSOR_TEST_CASES) {
        /**
         * @tc.steps: step1. create frameNode.
         */
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        ASSERT_NE(frameNode, nullptr);

        /**
         * @tc.steps: step2. create dragEvent.
         */
        RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        ASSERT_NE(event, nullptr);
        event->dragBehavior_ = testCase.dragBehavior;
        event->dragRet_ = testCase.dragResult;

        
        /**
         * @tc.steps: step3. call UpdateDragCursorStyle function.
         * @tc.expected: step4. drag status equals.
         */
        auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
        ASSERT_NE(dragDropManager, nullptr);
        dragDropManager->UpdateDragCursorStyle(frameNode, event, -1);
        EXPECT_TRUE(IsDragEventStateEqual(caseNum, dragDropManager->dragCursorStyleCore_ ==
            testCase.expectResult, true));
        caseNum++;
    }
};

/**
 * @tc.name: DragEventTestNGIssue006
 * @tc.desc: Test UpdateDragAllowDrop function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue006, TestSize.Level1)
{
    int32_t caseNum = 0;
    for (const auto& testCase : UPDATE_DRAG_ALLOW_DROP_TEST_CASES) {

        /**
         * @tc.steps: step1. create eventhub.
        */
        auto eventHub = AceType::MakeRefPtr<EventHub>();
        ASSERT_NE(eventHub, nullptr);
        auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
        ASSERT_NE(gestureEventHub, nullptr);
        eventHub->enabled_ = testCase.isEnabled;
        /**
         * @tc.steps: step2. create frameNode.
         */
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        ASSERT_NE(frameNode, nullptr);
        frameNode->eventHub_ = eventHub;
        frameNode->allowDrop_ = testCase.allowDropSet;

        /**
         * @tc.steps: step3. create dragEvent.
         */
        RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        ASSERT_NE(event, nullptr);
        event->isCapi_ = testCase.isCapi;
        event->dragBehavior_ = testCase.dragBehavior;

        
        /**
         * @tc.steps: step4. call UpdateDragCursorStyle function.
         * @tc.expected: step4. drag status equals.
         */
        auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
        ASSERT_NE(dragDropManager, nullptr);
        dragDropManager->summaryMap_ = testCase.summaryMap;
        if (testCase.isInDraggedFrameNode) {
            dragDropManager->draggedFrameNode_ = frameNode;
        }
        dragDropManager->UpdateDragCursorStyle(frameNode, event, -1);
        EXPECT_TRUE(IsDragEventStateEqual(caseNum, dragDropManager->dragCursorStyleCore_ ==
            testCase.expectResult, true));
        caseNum++;
    }
};

/**
 * @tc.name: DragEventTestNGIssue007
 * @tc.desc: Test HideSubwindowDragNode function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlayManager and dragDropManager.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    dragDropManager->subwindowOverlayManager_ = overlayManager;

    /**
     * @tc.steps: step2. create frameNode.
     */
    auto rootNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(rootNode, nullptr);
    {
        auto gatherNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        ASSERT_NE(gatherNode, nullptr);
        auto pixmapColumnNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        ASSERT_NE(pixmapColumnNode, nullptr);
        auto dragPixmapColumnNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        ASSERT_NE(dragPixmapColumnNode, nullptr);

        overlayManager->gatherNodeWeak_ = gatherNode;
        overlayManager->pixmapColumnNodeWeak_ = pixmapColumnNode;
        overlayManager->dragPixmapColumnNodeWeak_ = dragPixmapColumnNode;
        gatherNode->MountToParent(rootNode);
        pixmapColumnNode->MountToParent(rootNode);
        dragPixmapColumnNode->MountToParent(rootNode);
    }
    overlayManager->hasDragPixelMap_ = true;
    overlayManager->hasPixelMap_ = true;
    overlayManager->hasGatherNode_ = true;

    /**
     * @tc.steps: step3. call HideSubwindowDragNode.
     */
    dragDropManager->HideSubwindowDragNode();

    EXPECT_EQ(overlayManager->gatherNodeWeak_.Upgrade(), nullptr);
    EXPECT_EQ(overlayManager->pixmapColumnNodeWeak_.Upgrade(), nullptr);
    EXPECT_EQ(overlayManager->dragPixmapColumnNodeWeak_.Upgrade(), nullptr);
    EXPECT_EQ(overlayManager->hasDragPixelMap_, false);
    EXPECT_EQ(overlayManager->hasPixelMap_, false);
    EXPECT_EQ(overlayManager->hasGatherNode_, false);
}

/**
 * @tc.name: DragEventTestNGIssue008
 * @tc.desc: Test OnDragPullCancel function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get dragDropManager.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. create frameNode.
     */
    auto preTargetFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(preTargetFrameNode, nullptr);
    dragDropManager->preTargetFrameNode_ = preTargetFrameNode;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    preTargetFrameNode->eventHub_ = eventHub;

    /**
     * @tc.steps: step3. trigger OnDragPullCancel.
     */
    auto pointerEvent = DragPointerEvent();
    dragDropManager->OnDragPullCancel(pointerEvent);
    EXPECT_EQ(dragDropManager->preTargetFrameNode_, nullptr);
}

/**
 * @tc.name: DragEventTestNGIssue009
 * @tc.desc: Test OnDragPullCancel function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue009, TestSize.Level1)
{
    /**
    * @tc.steps: step1. get dragDropManager.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
    * @tc.steps: step2. create frameNode.
    */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode, nullptr);

    /**
    * @tc.steps: step3. set drag status.
    */
    const int32_t pullId = 10000;
    dragDropManager->currentPullId_ = pullId;
    dragDropManager->previewRect_ = Rect(1, 1, 1, 1);
    dragDropManager->extraInfo_ = "test";
    dragDropManager->velocityTracker_.lastPosition_ = Offset(1.0f, 1.0f);
    dragDropManager->dragDropState_ = DragDropMgrState::DRAGGING;
    dragDropManager->draggedFrameNode_ = frameNode;
    dragDropManager->menuWrapperNode_ = frameNode;
    dragDropManager->preMovePoint_ = Point(1, 1);
    dragDropManager->hasNotifiedTransformation_ = true;
    dragDropManager->badgeNumber_ = 1;
    dragDropManager->isDragWithContextMenu_ = true;
    dragDropManager->isDragNodeNeedClean_ = true;
    dragDropManager->isAnyDraggableHit_ = true;
    dragDropManager->isPullThrow_ = true;

    /**
    * @tc.steps: step4. trigger OnDragPullCancel.
    */
    auto pointerEvent = DragPointerEvent();
    dragDropManager->OnDragPullCancel(pointerEvent);
    EXPECT_EQ(dragDropManager->currentPullId_, -1);
    EXPECT_EQ(dragDropManager->previewRect_, Rect(-1, -1, -1, -1));
    EXPECT_EQ(dragDropManager->extraInfo_, "");
    EXPECT_EQ(dragDropManager->velocityTracker_.lastPosition_, Offset(0.0f, 0.0f));
    EXPECT_EQ(dragDropManager->dragDropState_, DragDropMgrState::IDLE);
    EXPECT_EQ(dragDropManager->draggedFrameNode_, nullptr);
    EXPECT_EQ(dragDropManager->GetMenuWrapperNode(), nullptr);
    EXPECT_EQ(dragDropManager->preMovePoint_, Point(0, 0));
    EXPECT_EQ(dragDropManager->hasNotifiedTransformation_, false);
    EXPECT_EQ(dragDropManager->badgeNumber_, -1);
    EXPECT_EQ(dragDropManager->isDragWithContextMenu_, false);
    EXPECT_EQ(dragDropManager->isDragNodeNeedClean_, false);
    EXPECT_EQ(dragDropManager->isAnyDraggableHit_, false);
    EXPECT_EQ(dragDropManager->isPullThrow_, false);
}

/**
 * @tc.name: DragEventTestNGIssue010
 * @tc.desc: Test OnDragPullCancel function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue010, TestSize.Level1)
{
    /**
    * @tc.steps: step1. get dragDropManager.
    */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
    * @tc.steps: step2. create frameNode.
    */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(frameNode, nullptr);

    /**
    * @tc.steps: step3. set drag status.
    */
    const Point dragMoveLastPoint = Point(1, 1, 1, 1);
    dragDropManager->fingerPointInfo_[0] = dragMoveLastPoint;
    DragDropGlobalController::GetInstance().UpdateDragDropInitiatingStatus(frameNode,
        DragDropInitiatingStatus::MOVING);

    bool isInMoving = DragDropGlobalController::GetInstance().IsInMoving();
    EXPECT_EQ(isInMoving, true);

    /**
    * @tc.steps: step4. trigger OnDragPullCancel.
    */
    auto pointerEvent = DragPointerEvent();
    dragDropManager->OnDragPullCancel(pointerEvent);
    int32_t fingerPointInfoSize = dragDropManager->fingerPointInfo_.size();
    EXPECT_EQ(fingerPointInfoSize, 0);
    isInMoving = DragDropGlobalController::GetInstance().IsInMoving();
    EXPECT_EQ(isInMoving, false);
}

/**
 * @tc.name: DragEventTestNGIssue011
 * @tc.desc: Test CheckIsUIExtensionBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get dragDropManager.
     */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    container->pipelineContext_ = pipeline;
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. test is not UIExtension inner.
     */
    container->isUIExtensionWindow_ = false;
    float x = 0.0f;
    float y = 0.0f;
    float width = pipeline->rootWidth_;
    float height = pipeline->rootHeight_;
    bool isUIExtensionBoundary = false;

    x = width / 2.0f;
    y = height / 2.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = 0.0f;
    y = 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = 1.0f;
    y = 0.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = width - 1.0f;
    y = 0.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = 0.0f;
    y = height - 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = width - 1.0f;
    y = height - 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);
}

/**
 * @tc.name: DragEventTestNGIssue012
 * @tc.desc: Test CheckIsUIExtensionBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue012, TestSize.Level1)
{
    /**
    * @tc.steps: step1. get dragDropManager.
    */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    container->pipelineContext_ = pipeline;
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
    * @tc.steps: step2. test is not UIExtension outer.
    */
    container->isUIExtensionWindow_ = false;
    float x = 0.0f;
    float y = 0.0f;
    float width = pipeline->rootWidth_;
    float height = pipeline->rootHeight_;
    bool isUIExtensionBoundary = false;

    x = 0.0f;
    y = -1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = -1.0f;
    y = 0.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = width + 1.0f;
    y = 0.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = 0.0f;
    y = height + 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = width + 1.0f;
    y = height + 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);
}

/**
 * @tc.name: DragEventTestNGIssue013
 * @tc.desc: Test CheckIsUIExtensionBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue013, TestSize.Level1)
{
    /**
    * @tc.steps: step1. get dragDropManager.
    */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    container->pipelineContext_ = pipeline;
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
    * @tc.steps: step2. test is UIExtension inner.
    */
    container->isUIExtensionWindow_ = true;
    float x = 0.0f;
    float y = 0.0f;
    float width = pipeline->rootWidth_;
    float height = pipeline->rootHeight_;
    bool isUIExtensionBoundary = false;

    x = width / 2.0f;
    y = height / 2.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, false);

    x = 0.0f;
    y = 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);

    x = 1.0f;
    y = 0.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);

    x = width - 1.0f;
    y = 0.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);

    x = 0.0f;
    y = height - 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);

    x = width - 1.0f;
    y = height - 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);
}

/**
 * @tc.name: DragEventTestNGIssue014
 * @tc.desc: Test CheckIsUIExtensionBoundary function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue014, TestSize.Level1)
{
    /**
    * @tc.steps: step1. get dragDropManager.
    */
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    container->pipelineContext_ = pipeline;
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
    * @tc.steps: step2. test is UIExtension outer.
    */
    container->isUIExtensionWindow_ = true;
    float x = 0.0f;
    float y = 0.0f;
    float width = pipeline->rootWidth_;
    float height = pipeline->rootHeight_;
    bool isUIExtensionBoundary = false;

    x = 0.0f;
    y = -1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);

    x = -1.0f;
    y = 0.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);

    x = width + 1.0f;
    y = 0.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);

    x = 0.0f;
    y = height + 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);

    x = width + 1.0f;
    y = height + 1.0f;
    isUIExtensionBoundary = dragDropManager->CheckIsUIExtensionBoundary(x, y, 0);
    EXPECT_EQ(isUIExtensionBoundary, true);
}

/**
 * @tc.name: DragEventTestNGIssue015
 * @tc.desc: Test CheckIsNewDrag function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue015, TestSize.Level1)
{
    /**
    * @tc.steps: step1. get dragDropManager.
    */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);
    const int32_t pullId = 10000;
    dragDropManager->currentPullId_ = pullId;

    /**
    * @tc.steps: step2. create dragPointEvent.
    */
    auto pointerEvent = DragPointerEvent();

    /**
    * @tc.steps: step3. call CheckIsNewDrag.
    */
    pointerEvent.pullId = -1;
    bool result = false;
    result = dragDropManager->CheckIsNewDrag(pointerEvent);
    EXPECT_EQ(result, false);

    pointerEvent.pullId = pullId;
    result = dragDropManager->CheckIsNewDrag(pointerEvent);
    EXPECT_EQ(result, false);

    const int32_t newPullId = 10001;
    pointerEvent.pullId = newPullId;
    result = dragDropManager->CheckIsNewDrag(pointerEvent);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DragEventTestNGIssue016
 * @tc.desc: Test InitDragAnimationPointerEvent function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue016, TestSize.Level1)
{
    /**
    * @tc.steps: step1. get dragDropManager.
    */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto dragDropManager = pipeline->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
    * @tc.steps: step2. create GestureEvent.
    */
    auto gestureEvent = GestureEvent();
    const Offset globalLocation = Offset(0, 0);
    const Offset screenLocation = Offset(10, 10);
    gestureEvent.globalLocation_ = globalLocation;
    gestureEvent.screenLocation_ = screenLocation;
    gestureEvent.pointerId_ = 0;

    /**
    * @tc.steps: step3. set fingerPointInfo.
    */
    const Point dragMoveLastPoint = Point(1, 1, 11, 11);
    dragDropManager->fingerPointInfo_[0] = dragMoveLastPoint;


    /**
    * @tc.steps: step4. call InitDragAnimationPointerEvent.
    */
    dragDropManager->InitDragAnimationPointerEvent(gestureEvent, false);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.windowX, 0);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.windowY, 0);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.displayX, 10);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.displayY, 10);

    dragDropManager->InitDragAnimationPointerEvent(gestureEvent, true);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.windowX, 1);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.windowY, 1);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.displayX, 11);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.displayY, 11);

    gestureEvent.pointerId_ = 1;
    dragDropManager->InitDragAnimationPointerEvent(gestureEvent, true);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.windowX, 0);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.windowY, 0);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.displayX, 0);
    EXPECT_EQ(dragDropManager->dragAnimationPointerEvent_.displayY, 0);
}

/**
 * @tc.name: DragEventTestNGIssue017
 * @tc.desc: Test RequestDragEndCallback function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set DragDropGlobalController init status.
     */
    const int32_t requestId = 10000;
    DragDropGlobalController::GetInstance().requestId_ = -1;
    DragDropGlobalController::GetInstance().dragResult_ = DragRet::DRAG_FAIL;
    DragDropGlobalController::GetInstance().isOnOnDropPhase_ = true;
    auto finalDragResult = DragRet::DRAG_FAIL;
    auto callback = [&finalDragResult](const DragRet& dragResult) {
        finalDragResult = dragResult;
    };

    /**
     * @tc.steps: step2. call RequestDragEndCallback.
     */
    bool result = DragDropGlobalController::GetInstance().RequestDragEndCallback(-1, DragRet::DRAG_SUCCESS, callback);
    EXPECT_EQ(result, false);
    EXPECT_EQ(DragDropGlobalController::GetInstance().requestId_, -1);
    EXPECT_EQ(DragDropGlobalController::GetInstance().dragResult_, DragRet::DRAG_FAIL);

    result = DragDropGlobalController::GetInstance().RequestDragEndCallback(requestId,
        DragRet::DRAG_SUCCESS, nullptr);
    EXPECT_EQ(result, false);
    EXPECT_EQ(DragDropGlobalController::GetInstance().requestId_, -1);
    EXPECT_EQ(DragDropGlobalController::GetInstance().dragResult_, DragRet::DRAG_FAIL);

    result = DragDropGlobalController::GetInstance().RequestDragEndCallback(-1, DragRet::DRAG_SUCCESS, nullptr);
    EXPECT_EQ(result, false);
    EXPECT_EQ(DragDropGlobalController::GetInstance().requestId_, -1);
    EXPECT_EQ(DragDropGlobalController::GetInstance().dragResult_, DragRet::DRAG_FAIL);

    DragDropGlobalController::GetInstance().isOnOnDropPhase_ = false;
    result = DragDropGlobalController::GetInstance().RequestDragEndCallback(requestId,
        DragRet::DRAG_SUCCESS, callback);
    EXPECT_EQ(result, false);
    EXPECT_EQ(DragDropGlobalController::GetInstance().requestId_, -1);
    EXPECT_EQ(DragDropGlobalController::GetInstance().dragResult_, DragRet::DRAG_FAIL);

    DragDropGlobalController::GetInstance().isOnOnDropPhase_ = true;
    result = DragDropGlobalController::GetInstance().RequestDragEndCallback(requestId,
        DragRet::DRAG_SUCCESS, callback);
    EXPECT_EQ(result, true);
    EXPECT_EQ(DragDropGlobalController::GetInstance().requestId_, requestId);
    EXPECT_EQ(DragDropGlobalController::GetInstance().dragResult_, DragRet::DRAG_SUCCESS);
}

/**
 * @tc.name: DragEventTestNGIssue018
 * @tc.desc: Test NotifyDragEndPendingDone function
 * @tc.type: FUNC
 */
HWTEST_F(DragEventTestNgIssue, DragEventTestNGIssue018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set DragDropGlobalController init status.
     */
    const int32_t requestId = 10000;
    DragDropGlobalController::GetInstance().requestId_ = -1;
    DragDropGlobalController::GetInstance().dragResult_ = DragRet::DRAG_FAIL;
    DragDropGlobalController::GetInstance().isOnOnDropPhase_ = true;
    auto finalDragResult = DragRet::DRAG_FAIL;
    auto callback = [&finalDragResult](const DragRet& dragResult) {
        finalDragResult = dragResult;
    };

    /**
     * @tc.steps: step2. call RequestDragEndCallback.
     */
    auto result = DragDropGlobalController::GetInstance().RequestDragEndCallback(requestId,
        DragRet::DRAG_SUCCESS, callback);
    EXPECT_EQ(result, true);

    /**
     * @tc.steps: step3. call NotifyDragEndPendingDone.
     */
    DragDropGlobalController::GetInstance().dragResult_ = DragRet::DRAG_CANCEL;
    DragDropGlobalController::GetInstance().NotifyDragEndPendingDone(requestId);
    EXPECT_EQ(finalDragResult, DragRet::DRAG_CANCEL);
    EXPECT_EQ(DragDropGlobalController::GetInstance().stopDragCallback_, nullptr);
    EXPECT_EQ(DragDropGlobalController::GetInstance().dragResult_, DragRet::DRAG_FAIL);
}
} // namespace OHOS::Ace::NG