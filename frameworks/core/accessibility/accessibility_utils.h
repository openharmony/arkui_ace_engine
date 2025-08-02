/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_UTILS_H

#include <cstddef>
#include <cstdint>

#include "base/geometry/rect.h"

namespace OHOS::Ace {

// define accessibility node tags
extern const char ACCESSIBILITY_TAG_DIV[];
extern const char ACCESSIBILITY_TAG_CALENDAR[];
extern const char ACCESSIBILITY_TAG_TEXT[];
extern const char ACCESSIBILITY_TAG_PICKER[];
extern const char ACCESSIBILITY_TAG_OPTION[];
extern const char ACCESSIBILITY_TAG_POPUP[];
extern const char ACCESSIBILITY_TAG_PROGRESS[];
extern const char ACCESSIBILITY_TAG_SELECT[];
extern const char ACCESSIBILITY_TAG_MENU[];
extern const char ACCESSIBILITY_TAG_SLIDER[];
extern const char ACCESSIBILITY_TAG_SPAN[];
extern const char ACCESSIBILITY_TAG_STACK[];
extern const char ACCESSIBILITY_TAG_SWIPER[];
extern const char ACCESSIBILITY_TAG_SWITCH[];
extern const char ACCESSIBILITY_TAG_TABS[];
extern const char ACCESSIBILITY_TAG_TAB_BAR[];
extern const char ACCESSIBILITY_TAG_TAB_CONTENT[];
extern const char ACCESSIBILITY_TAG_REFRESH[];
extern const char ACCESSIBILITY_TAG_IMAGE[];
extern const char ACCESSIBILITY_TAG_LIST[];
extern const char ACCESSIBILITY_TAG_LIST_ITEM[];
extern const char ACCESSIBILITY_TAG_LIST_ITEM_GROUP[];
extern const char ACCESSIBILITY_TAG_VIDEO[];
extern const char ACCESSIBILITY_TAG_RATING[];
extern const char ACCESSIBILITY_TAG_MARQUEE[];
extern const char ACCESSIBILITY_TAG_NAVIGATION_BAR[];
extern const char ACCESSIBILITY_TAG_NAVIGATION_MENU[];
extern const char ACCESSIBILITY_TAG_TEXTAREA[];
extern const char ACCESSIBILITY_TAG_INPUT[];
extern const char ACCESSIBILITY_TAG_LABEL[];
extern const char ACCESSIBILITY_TAG_DIVIDER[];
extern const char ACCESSIBILITY_TAG_CANVAS[];
extern const char ACCESSIBILITY_TAG_BUTTON[];
extern const char ACCESSIBILITY_TAG_CHART[];
extern const char ACCESSIBILITY_TAG_CLOCK[];
extern const char ACCESSIBILITY_TAG_DIALOG[];
extern const char ACCESSIBILITY_TAG_SEARCH[];

extern const int32_t FOCUS_DIRECTION_UP;
extern const int32_t FOCUS_DIRECTION_DOWN;
extern const int32_t FOCUS_DIRECTION_LEFT;
extern const int32_t FOCUS_DIRECTION_RIGHT;
extern const int32_t FOCUS_DIRECTION_FORWARD;
extern const int32_t FOCUS_DIRECTION_BACKWARD;

enum class AccessibilityEventType : size_t {
    CLICK = 0x00000001,
    LONG_PRESS = 0x00000002,
    SELECTED = 0x00000004,
    BLUR = 0x00000007,
    FOCUS = 0x00000008,
    TEXT_CHANGE = 0x00000010,
    EJECT_DISMISS = 0x00000020,
    MOUSE = 149,
    KEYBOARD_BACK = 150,
    KEYBOARD_UP = 151,
    KEYBOARD_DOWN = 152,
    KEYBOARD_LEFT = 153,
    KEYBOARD_RIGHT = 154,
    KEYBOARD_CENTER = 155,
    HANDLE_A = 156,
    HANDLE_SELECT = 157,
    KEYBOARD_TAB = 158,
    KEYBOARD_SPACE = 159,
    KEYBOARD_ENTER = 160,
    KEYBOARD_ESCAPE = 161,
    KEYBOARD_NUMBER_ENTER = 162,
    TV_CONTROL_MEDIA_PLAY = 163,
    PAGE_CHANGE = 200,
    HOVER_ENTER_EVENT = 0x0000080,
    HOVER_EXIT_EVENT = 0x0000100,
    TOUCH_START = 0x00000200,
    TOUCH_MOVE = 0x00000201,
    TOUCH_CANCEL = 0x00000202,
    TOUCH_END = 0x00000400,
    CHANGE = 0x00000800,
    COMPONENT_CHANGE = 0x00000801,
    SCROLL_END = 0x00001000,
    TEXT_SELECTION_UPDATE = 0x000002000,
    ACCESSIBILITY_FOCUSED = 0x00008000,
    ACCESSIBILITY_FOCUS_CLEARED = 0x00010000,
    TEXT_MOVE_UNIT = 0x00020000,
    REQUEST_FOCUS = 0x00800000,
    SCROLL_START = 0x01000000,
    PAGE_CLOSE = 0x08000000,
    ANNOUNCE_FOR_ACCESSIBILITY = 0x10000000,
    PAGE_OPEN = 0x20000000,
    ELEMENT_INFO_CHANGE = 0x40000000,
    ANNOUNCE_FOR_ACCESSIBILITY_NOT_INTERRUPT = 0x40000001,
    SCROLLING_EVENT = 0x40000003,
    UNKNOWN,
};

enum WindowUpdateType : int32_t {
    WINDOW_UPDATE_INVALID = 0,
    WINDOW_UPDATE_ACCESSIBILITY_FOCUSED = 0x00000001,
    WINDOW_UPDATE_FOCUSED = 0x00000002,
    WINDOW_UPDATE_ACTIVE = 0x00000004,
    WINDOW_UPDATE_ADDED = 0x00000008,
    WINDOW_UPDATE_REMOVED = 0x00000010,
    WINDOW_UPDATE_BOUNDS = 0x00000020,
    WINDOW_UPDATE_TITLE = 0x00000040,
    WINDOW_UPDATE_LAYER = 0x00000080,
    WINDOW_UPDATE_PARENT = 0x00000100,
    WINDOW_UPDATE_CHILDREN = 0x00000200,
    WINDOW_UPDATE_PIP = 0x00000400,
};

enum WindowsContentChangeTypes : int32_t {
    CONTENT_CHANGE_TYPE_INVALID = 0,
    CONTENT_CHANGE_TYPE_SUBTREE = 0x00000001,
    CONTENT_CHANGE_TYPE_TEXT = 0x00000002,
    CONTENT_CHANGE_TYPE_CONTENT_DESCRIPTION = 0x00000004,
};

struct OperableInfo {
    bool checkable = false;
    bool clickable = false;
    bool scrollable = false;
    bool longClickable = false;
    bool focusable = false;
};

enum class AceAction : uint32_t {
    ACTION_NONE = 0,
    GLOBAL_ACTION_BACK,
    CUSTOM_ACTION,
    ACTION_CLICK = 10,
    ACTION_LONG_CLICK,
    ACTION_SCROLL_FORWARD,
    ACTION_SCROLL_BACKWARD,
    ACTION_FOCUS,
    ACTION_CLEAR_FOCUS,
    ACTION_ACCESSIBILITY_FOCUS,
    ACTION_CLEAR_ACCESSIBILITY_FOCUS,
    ACTION_NEXT_AT_MOVEMENT_GRANULARITY,
    ACTION_PREVIOUS_AT_MOVEMENT_GRANULARITY,
    ACTION_SET_TEXT,
    ACTION_COPY,
    ACTION_PASTE,
    ACTION_CUT,
    ACTION_SELECT,
    ACTION_SET_SELECTION,
    ACTION_CLEAR_SELECTION,
    ACTION_SET_CURSOR_POSITION,
    ACTION_EXEC_SUB_COMPONENT,
    ACTION_NEXT_HTML_ITEM,
    ACTION_PREVIOUS_HTML_ITEM,
};

struct AccessibilityValue {
    double min = 0.0;
    double max = 0.0;
    double current = 0.0;
};

enum class AceTextCategory {
    INPUT_TYPE_DEFAULT = 0,
    INPUT_TYPE_TEXT,
    INPUT_TYPE_EMAIL,
    INPUT_TYPE_DATE,
    INPUT_TYPE_TIME,
    INPUT_TYPE_NUMBER,
    INPUT_TYPE_PASSWORD,
    INPUT_TYPE_PHONENUMBER,
    INPUT_TYPE_USER_NAME,
    INPUT_TYPE_NEW_PASSWORD,
};

struct AceCollectionInfo {
    int32_t rows = 0;
    int32_t columns = 0;
    int32_t selectMode = 0;
};

struct AceCollectionItemInfo {
    bool heading = false;
    int32_t row = 0;
    int32_t column = 0;
    int32_t rowSpan = 0;
    int32_t columnSpan = 0;
};

enum class AccessibilityScrollType : int32_t {
    SCROLL_DEFAULT = -1, // no parameter trans, do not add enum before
    SCROLL_HALF = 0,
    SCROLL_FULL = 1,
    SCROLL_MAX_TYPE = SCROLL_FULL, // for check parameter, do not add enum after
};

struct SubComponentInfo {
    int32_t spanId = 0;
    std::string spanText = "";
    std::string accessibilityText = "";
    std::string accessibilityDescription = "";
    std::string accessibilityLevel = "";
};

enum class NotifyChildActionType : uint32_t {
    ACTION_CLICK = 1,
};

enum class AccessibilityActionResult : int32_t {
    ACTION_OK = 0,
    ACTION_ERROR = -1,
    ///< need to  bubble up the action
    ACTION_RISE = 2,
};

enum class AccessibilityInterfaceAction : uint32_t {
    UNDEFINED_ACTION = 0,
    ACCESSIBILITY_CLICK = 1,
};

enum class AccessibilityActionInterceptResult : uint32_t {
    ACTION_INTERCEPT = 0,
    ACTION_CONTINUE = 1,
    ///< need to  bubble up the action
    ACTION_RISE = 2,
};
bool CheckBetterRect(const Rect& nodeRect, int direction, const Rect& itemRect, const Rect& tempBest);

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_UTILS_H
