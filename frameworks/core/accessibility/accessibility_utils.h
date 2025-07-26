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

enum class AccessibilityRoleType {
    ACTION_SHEET = 0,
    ALERT_DIALOG = 1,
    INDEXER_COMPONENT = 2,
    BADGE_COMPONENT = 3,
    BLANK = 4,
    BUTTON = 5,
    BACK_BUTTON = 6,
    SHEET_DRAG_BAR = 7,
    CALENDAR_PICKER = 8,
    CALENDAR = 9,
    CANVAS = 10,
    CANVAS_GRADIENT = 11,
    CANVAS_PATTERN = 12,
    CHECKBOX = 13,
    CHECKBOX_GROUP = 14,
    CIRCLE = 15,
    COLUMN_SPLIT = 16,
    COLUMN = 17,
    CANVAS_RENDERING_CONTEXT_2D = 18,
    CHART = 19,
    COUNTER = 20,
    CONTAINER_MODAL = 21,
    DATA_PANEL = 22,
    DATE_PICKER = 23,
    DIALOG = 24,
    DIVIDER = 25,
    DRAG_BAR = 26,
    EFFECT_COMPONENT = 27,
    ELLIPSE = 28,
    FLEX = 29,
    FLOW_ITEM = 30,
    FORM_COMPONENT = 31,
    FORM_LINK = 32,
    GAUGE = 33,
    GRID = 34,
    GRID_COL = 35,
    GRID_CONTAINER = 36,
    GRID_ITEM = 37,
    GRID_ROW = 38,
    HYPERLINK = 39,
    IMAGE = 40,
    IMAGE_ANIMATOR = 41,
    ROLE_IMAGE_BITMAP = 42,
    IMAGE_DATA = 43,
    IMAGE_SPAN = 44,
    LABEL = 45,
    LINE = 46,
    LIST = 47,
    LIST_ITEM = 48,
    LIST_ITEM_GROUP = 49,
    LOADING_PROGRESS = 50,
    MARQUEE = 51,
    MATRIX2D = 52,
    MENU = 53,
    MENU_ITEM = 54,
    MENU_ITEM_GROUP = 55,
    NAV_DESTINATION = 56,
    NAV_ROUTER = 57,
    NAVIGATION = 58,
    NAVIGATION_BAR = 59,
    NAVIGATION_MENU = 60,
    NAVIGATOR = 61,
    OFFSCREEN_CANVAS = 62,
    OFFSCREEN_CANVAS_RENDERING_CONTEXT2D = 63,
    OPTION = 64,
    PANEL = 65,
    PAPER_PAGE = 66,
    PATH = 67,
    PATH2D = 68,
    PATTERN_LOCK = 69,
    PICKER = 70,
    PICKER_VIEW = 71,
    PLUGIN_COMPONENT = 72,
    POLYGON = 73,
    POLYLINE = 74,
    POPUP = 75,
    PROGRESS = 76,
    QRCODE = 77,
    RADIO = 78,
    RATING = 79,
    RECT = 80,
    REFRESH = 81,
    RELATIVE_CONTAINER = 82,
    REMOTE_WINDOW = 83,
    RICH_EDITOR = 84,
    RICH_TEXT = 85,
    ROLE_PAGER = 86,
    ROW = 87,
    ROW_SPLIT = 88,
    SCROLL = 89,
    SCROLL_BAR = 90,
    SEARCH = 91,
    SEARCH_FIELD = 92,
    SELECT = 93,
    SHAPE = 94,
    SIDEBAR_CONTAINER = 95,
    SLIDER = 96,
    SPAN = 97,
    STACK = 98,
    STEPPER = 99,
    STEPPER_ITEM = 100,
    SWIPER = 101,
    SWIPER_INDICATOR = 102,
    SWITCH = 103,
    SYMBOL_GLYPH = 104,
    TAB_CONTENT = 105,
    TAB_BAR = 106,
    TABS = 107,
    TEXT = 108,
    TEXT_CLOCK = 109,
    TEXT_ENTRY = 110,
    TEXT_INPUT = 111,
    TEXT_PICKER = 112,
    TEXT_TIMER = 113,
    TEXT_AREA = 114,
    TEXT_FIELD = 115,
    TIME_PICKER = 116,
    TITLE_BAR = 117,
    TOGGLER = 118,
    UI_EXTENSION_COMPONENT = 119,
    VIDEO = 120,
    WATER_FLOW = 121,
    WEB = 122,
    XCOMPONENT = 123,
    ROLE_NONE = 124,
};

enum class AccessibilitySamePageMode {
    SEMI_SILENT = 0,
    FULL_SILENT = 1,
};

enum class FocusDrawLevel {
    SELF = 0,
    TOP = 1,
};

class AccessibilityUtils {
public:
    static std::string GetRoleByType(AccessibilityRoleType roleType);
    static std::string GetPageModeType(int32_t pageModeType);
    static int32_t GetFocusDrawLevel(int32_t inputValue);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_UTILS_H
