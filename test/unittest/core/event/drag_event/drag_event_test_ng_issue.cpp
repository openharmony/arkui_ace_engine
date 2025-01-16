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

struct MenuStatusTestCase {
    bool isBindCustomMenu = false;
    bool isShow = false;
    MenuPreviewMode previewMode = MenuPreviewMode::NONE;
    bool expectResult = false;
};

struct DragCursorStyleTestCase {
    bool isCapi = false;
    bool isEnabled = true;
    bool isDisallowDropForcedly = false;
    bool isInDraggedFrameNode = false;
    DragRet dragResult = DragRet::DRAG_DEFAULT;
    DragBehavior dragBehavior = DragBehavior::UNKNOWN;
    std::set<std::string> allowDropSet;
    std::map<std::string, int64_t> summaryMap;
    int32_t expectResult;
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

const std::vector<DragCursorStyleTestCase> DRAG_CURSOR_STYLE_TEST_CASES = {
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { false, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 2},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 2},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 2},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 2},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, false, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 2},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 2},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, false, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 2},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 2},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, false, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, true, false, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},

    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DRAG_DEFAULT, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 2},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::ENABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::UNKNOWN, {"A"}, {{"B", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::COPY, {"A"}, {{"B", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"A", 1}}, 3},
    { true, true, true, true, DragRet::DISABLE_DROP, DragBehavior::MOVE, {"A"}, {{"B", 1}}, 3}
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
    for (const auto& testCase : DRAG_CURSOR_STYLE_TEST_CASES) {

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
        frameNode->isDisallowDropForcedly_ = testCase.isDisallowDropForcedly;
        frameNode->allowDrop_ = testCase.allowDropSet;

        /**
         * @tc.steps: step3. create dragEvent.
         */
        RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        event->isCapi_ = testCase.isCapi;
        event->dragBehavior_ = testCase.dragBehavior;
        event->dragRet_ = testCase.dragResult;

        
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
            static_cast<DragCursorStyleCore>(testCase.expectResult), true));
        caseNum++;
    }
};

} // namespace OHOS::Ace::NG