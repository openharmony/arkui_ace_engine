/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// #include "core/interfaces/native/node/node_modifiers.h"

#include "core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ARKUI_NODE_API_VERSION 66

enum ArkUINodeType {
    ARKUI_TEXT = 1,
    ARKUI_SPAN = 2,
    ARKUI_IMAGE_SPAN = 3,
    ARKUI_IMAGE = 4,
    ARKUI_TOGGLE = 5,
    ARKUI_LOADINGPROGRESS = 6,
    ARKUI_TEXTINPUT = 7,
    ARKUI_STACK = 8,
    ARKUI_SCROLL = 9,
    ARKUI_LIST = 10,
    ARKUI_SWIPER = 11,
    ARKUI_TEXTAREA = 12,
    ARKUI_BUTTON = 13,
    ARKUI_PROGRESS = 14,
    ARKUI_CHECKBOX = 15,
    ARKUI_COLUMN = 16,
    ARKUI_ROW = 17,
    ARKUI_FLEX = 18,
    ARKUI_LIST_ITEM = 19,
    ARKUI_REFRESH = 20,
    ARKUI_XCOMPONENT = 21,
};

#define ARKUI_MAX_EVENT_NUM 1000

enum ArkUIAsyncEventKind {
    // common events
    ON_APPEAR = 0,
    ON_DISAPPEAR = 1,
    ON_TOUCH = 2,
    ON_CLICK = 3,
    ON_HOVER = 4,
    ON_BLUR = 5,
    ON_KEYEVENT = 6,
    ON_MOUSE = 7,
    ON_AREA_CHANGE = 8,
    ON_VISIBLEAREA_CHANGE = 9,
    ON_GESTURE = 10,
    ON_FOCUS = 11,
    
    // components events
    ON_LIST_SCROLL = ARKUI_MAX_EVENT_NUM * ARKUI_LIST,
    ON_LIST_SCROLL_INDEX,
    ON_LIST_SCROLL_START,
    ON_LIST_SCROLL_STOP,

    ON_TOGGLE_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TOGGLE,

    ON_TEXTINPUT_EDIT_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TEXTINPUT,
    ON_TEXTINPUT_SUBMIT,
    ON_TEXTINPUT_CHANGE,

    ON_TEXTAREA_EDIT_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TEXTAREA,
    ON_TEXTAREA_SUBMIT,
    ON_TEXTAREA_CHANGE,

    ON_SWIPER_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_SWIPER,
    ON_SWIPER_ANIMATION_START,
    ON_SWIPER_ANIMATION_END,
    ON_SWIPER_GESTURE_SWIPE,

    ON_IMAGE_COMPLETE = ARKUI_MAX_EVENT_NUM * ARKUI_IMAGE,
    ON_IMAGE_ERROR,

    ON_SCROLL = ARKUI_MAX_EVENT_NUM * ARKUI_SCROLL,
    ON_SCROLL_FRAME_BEGIN,
    ON_SCROLL_START,
    ON_SCROLL_STOP,
    ON_SCROLL_EDGE,

    ON_REFRESH_STATE_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_REFRESH,
    ON_REFRESH_REFRESHING,
};

// Current implementation assumes that each argument is 4 bytes,
// fix decodeEvent() in TS if it will change.

#define ARKUI_ASYNC_EVENT_ARGS_COUNT 12

struct ArkUINodeAsyncEvent {
    ArkUIEventCallbackArg data[ARKUI_ASYNC_EVENT_ARGS_COUNT];
};

struct ArkUIStringAsyncEvent {
    ArkUI_CharPtr pStr;
};

struct ArkUINodeEvent {
    ArkUI_Int32 kind;    // Actually ArkUINodeAPIEventKind, but use int for fixed
                         // binary layout.
    ArkUI_Int32 eventId; // use to identify the event.
    void* extraParam;
    union {
        ArkUINodeAsyncEvent componentAsyncEvent;
        ArkUIGestureAsyncEvent gestureAsyncEvent;
        ArkUIStringAsyncEvent stringAsyncEvent;
    };
};

enum ArkUINodeDirtyFlag {
    NEED_MEASURE = 0,
    NEED_LAYOUT,
    NEED_RENDER,
};


#ifdef __cplusplus
};
#endif