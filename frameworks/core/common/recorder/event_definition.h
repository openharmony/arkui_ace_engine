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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_DEFINITION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_DEFINITION_H

#include <cstdint>

namespace OHOS::Ace::Recorder {
enum class EventCategory: int32_t {
    CATEGORY_PAGE = 0,
    CATEGORY_COMPONENT,
    CATEGORY_EXPOSURE,
    CATEGORY_PAGE_PARAM,
    CATEGORY_SCROLL,
    CATEGORY_ANIMATION,
    CATEGORY_RECT,
    CATEGORY_WEB,
    CATEGORY_TEXT_INPUT,
    CATEGORY_POINT,
    CATEGORY_PARENT_TEXT,
    CATEGORY_END,
};

enum EventType : int32_t {
    INVALID = 0,
    PAGE_SHOW,
    PAGE_HIDE,
    CLICK,
    LONG_PRESS,
    CHANGE,
    EXPOSURE,
    NAVIGATOR,
    REFRESH,
    STEPPER_FINISH,
    STEPPER_SKIP,
    STEPPER_NEXT,
    STEPPER_PREVIOUS,
    SEARCH_SUBMIT,
    WEB_PAGE_BEGIN,
    WEB_PAGE_END,
    VIDEO_START,
    VIDEO_PAUSE,
    VIDEO_FINISH,
    VIDEO_ERROR,
    VIDEO_PREPARED,
    VIDEO_SEEKED,
    VIDEO_SCREEN_CHANGE,
    VIDEO_STOP,
    DIALOG_SHOW,
    DIALOG_CANCEL,
    DIALOG_ACTION,
    DIALOG_SELECT,
    DIALOG_ACCEPT,
    SCROLL_START,
    SCROLL_STOP,
    ANIMATION_FINISHED,
    TEXT_INPUT,
    WEB_ACTION,
    BACK_PRESSED,
    LOAD_STARTED,
    LOAD_FINISHED,
};

constexpr char KEY_COUNT[] = "count";
constexpr char KEY_NODE_RECT[] = "rect";
constexpr char KEY_MOUDLE_NAME[] = "module";
constexpr char KEY_ABILITY_NAME[] = "ability";
constexpr char KEY_ACE_ID[] = "aceId";
constexpr char KEY_POINT[] = "point";
constexpr char KEY_CURRENT_OFFSET[] = "currentOffset";
constexpr char KEY_DISTANCE[] = "distance";
constexpr char KEY_NAME[] = "name";
constexpr char KEY_EXTRA_TEXT[] = "extraText";
constexpr char KEY_WEB_CATEGORY[] = "webCategory";
constexpr char WEB_OBJ_NAME[] = "arkMessager";
constexpr char WEB_METHOD_NAME[] = "postMessage";
constexpr int32_t WEB_PARAM_SIZE = 3;
constexpr int32_t WEB_PARAM_INDEX_CATEGORY = 0;
constexpr int32_t WEB_PARAM_INDEX_CONTENT = 1;
constexpr int32_t WEB_PARAM_INDEX_IDENTIFIER = 2;
} // namespace OHOS::Ace::Recorder
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_DEFINITION_H
