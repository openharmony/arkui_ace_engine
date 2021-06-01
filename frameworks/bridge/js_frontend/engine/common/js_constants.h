/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "base/utils/macros.h"

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_CONSTANTS_H

namespace OHOS::Ace::Framework {

ACE_EXPORT extern const int32_t JS_CALL_FAIL;
ACE_EXPORT extern const int32_t JS_CALL_SUCCESS;
ACE_EXPORT extern const int32_t MAX_STACK_SIZE;

// for pcPreview
ACE_EXPORT extern const char PC_PREVIEW[];

// for common
ACE_EXPORT extern const char COMMON_SUCCESS[];
ACE_EXPORT extern const char COMMON_FAIL[];
ACE_EXPORT extern const char COMMON_COMPLETE[];
ACE_EXPORT extern const char COMMON_CANCEL[];

// for page route
ACE_EXPORT extern const char ROUTE_PAGE_PUSH[];
ACE_EXPORT extern const char ROUTE_PAGE_REPLACE[];
ACE_EXPORT extern const char ROUTE_PAGE_BACK[];
ACE_EXPORT extern const char ROUTE_PAGE_CLEAR[];
ACE_EXPORT extern const char ROUTE_PAGE_GET_LENGTH[];
ACE_EXPORT extern const char ROUTE_PAGE_GET_STATE[];
ACE_EXPORT extern const char ROUTE_KEY_URI[];
ACE_EXPORT extern const char ROUTE_KEY_PATH[];
ACE_EXPORT extern const char ROUTE_KEY_PARAMS[];

// for prompt
ACE_EXPORT extern const char PROMPT_SHOW_TOAST[];
ACE_EXPORT extern const char PROMPT_KEY_MESSAGE[];
ACE_EXPORT extern const char PROMPT_KEY_DURATION[];
ACE_EXPORT extern const char PROMPT_KEY_BOTTOM[];
ACE_EXPORT extern const char PROMPT_SHOW_DIALOG[];
ACE_EXPORT extern const char PROMPT_KEY_TITLE[];
ACE_EXPORT extern const char PROMPT_KEY_BUTTONS[];
ACE_EXPORT extern const char PROMPT_DIALOG_AUTO_CANCEL[];

// for callback
ACE_EXPORT extern const char APP_DESTROY_FINISH[];
ACE_EXPORT extern const char CALLBACK_NATIVE[];
ACE_EXPORT extern const char KEY_STEPPER_PENDING_INDEX[];

// for configuration
ACE_EXPORT extern const char CONFIGURATION_GET_LOCALE[];
ACE_EXPORT extern const char CONFIGURATION_SET_LOCALE[];
ACE_EXPORT extern const char LOCALE_LANGUAGE[];
ACE_EXPORT extern const char LOCALE_COUNTRY_OR_REGION[];
ACE_EXPORT extern const char LOCALE_UNICODE_SETTING[];
ACE_EXPORT extern const char LOCALE_TEXT_DIR[];
ACE_EXPORT extern const char LOCALE_TEXT_DIR_LTR[];
ACE_EXPORT extern const char LOCALE_TEXT_DIR_RTL[];

// for mediaquery
ACE_EXPORT extern const char ADD_LISTENER[];
ACE_EXPORT extern const char GET_DEVICE_TYPE[];

// for timer
ACE_EXPORT extern const char SET_TIMEOUT[];
ACE_EXPORT extern const char CLEAR_TIMEOUT[];
ACE_EXPORT extern const char CLEAR_INTERVAL[];
ACE_EXPORT extern const char SET_INTERVAL[];

// for app
ACE_EXPORT extern const char APP_GET_INFO[];
ACE_EXPORT extern const char APP_TERMINATE[];
ACE_EXPORT extern const char APP_GET_PACKAGE_INFO[];
ACE_EXPORT extern const char APP_PACKAGE_NAME[];
ACE_EXPORT extern const char APP_REQUEST_FULL_WINDOW[];
ACE_EXPORT extern const char APP_SCREEN_ON_VISIBLE[];
ACE_EXPORT extern const char APP_SET_SWIPE_TO_DISMISS[];
ACE_EXPORT extern const char APP_REQUEST_FULL_WINDOW_DUATION[];
ACE_EXPORT extern const char APP_SCREEN_ON_VISIBLE_FLAG[];

// for animation
ACE_EXPORT extern const char ANIMATION_REQUEST_ANIMATION_FRAME[];
ACE_EXPORT extern const char ANIMATION_CANCEL_ANIMATION_FRAME[];

// for grid
ACE_EXPORT extern const char GRID_GET_SYSTEM_LAYOUT_INFO[];

// for plugin
ACE_EXPORT extern const int32_t PLUGIN_REQUEST_SUCCESS;
ACE_EXPORT extern const int32_t PLUGIN_REQUEST_FAIL;
ACE_EXPORT extern const int32_t PLUGIN_CALLBACK_DESTROY;
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_JS_CONSTANTS_H
