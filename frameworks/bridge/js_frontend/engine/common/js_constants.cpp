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

#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"

namespace OHOS::Ace::Framework {

const int32_t JS_CALL_FAIL = -1;
const int32_t JS_CALL_SUCCESS = 0;
// To solve the problem of stack overflow when qjs runs JS_Eval() after the context is generated.
const int32_t MAX_STACK_SIZE = -1;

// for pc preview
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
const char PC_PREVIEW[] = "enable";
#else
const char PC_PREVIEW[] = "disable";
#endif

// for common
const char COMMON_SUCCESS[] = "success";
const char COMMON_FAIL[] = "fail";
const char COMMON_COMPLETE[] = "complete";
const char COMMON_CANCEL[] = "cancel";

// for page route
const char ROUTE_PAGE_PUSH[] = "push";
const char ROUTE_PAGE_REPLACE[] = "replace";
const char ROUTE_PAGE_BACK[] = "back";
const char ROUTE_PAGE_CLEAR[] = "clear";
const char ROUTE_PAGE_GET_LENGTH[] = "getLength";
const char ROUTE_PAGE_GET_STATE[] = "getState";
const char ROUTE_KEY_URI[] = "uri";
const char ROUTE_KEY_PATH[] = "path";
const char ROUTE_KEY_PARAMS[] = "params";

// for prompt
const char PROMPT_SHOW_TOAST[] = "showToast";
const char PROMPT_KEY_MESSAGE[] = "message";
const char PROMPT_KEY_DURATION[] = "duration";
const char PROMPT_KEY_BOTTOM[] = "bottom";
const char PROMPT_SHOW_DIALOG[] = "showDialog";
const char PROMPT_KEY_TITLE[] = "title";
const char PROMPT_KEY_BUTTONS[] = "buttons";
const char PROMPT_DIALOG_AUTO_CANCEL[] = "autocancel";

// for callback
const char APP_DESTROY_FINISH[] = "appDestroyFinish";
const char CALLBACK_NATIVE[] = "callbackNative";
const char KEY_STEPPER_PENDING_INDEX[] = "pendingIndex";

// for configuration
const char CONFIGURATION_GET_LOCALE[] = "getLocale";
const char CONFIGURATION_SET_LOCALE[] = "setLocale";
const char LOCALE_LANGUAGE[] = "language";
const char LOCALE_COUNTRY_OR_REGION[] = "countryOrRegion";
const char LOCALE_UNICODE_SETTING[] = "unicodeSetting";
const char LOCALE_TEXT_DIR[] = "dir";
const char LOCALE_TEXT_DIR_LTR[] = "ltr";
const char LOCALE_TEXT_DIR_RTL[] = "rtl";

// for mediaquery
const char ADD_LISTENER[] = "addListener";
const char GET_DEVICE_TYPE[] = "getDeviceType";

// for timer
const char SET_TIMEOUT[] = "setTimeout";
const char CLEAR_TIMEOUT[] = "clearTimeout";
const char CLEAR_INTERVAL[] = "clearInterval";
const char SET_INTERVAL[] = "setInterval";

// for app
const char APP_GET_INFO[] = "getInfo";
const char APP_TERMINATE[] = "terminate";
const char APP_GET_PACKAGE_INFO[] = "getPackageInfo";
const char APP_PACKAGE_NAME[] = "packageName";
const char APP_REQUEST_FULL_WINDOW[] = "requestFullWindow";
const char APP_SCREEN_ON_VISIBLE[] = "screenOnVisible";
const char APP_SET_SWIPE_TO_DISMISS[] = "setSwipeToDismiss";
const char APP_REQUEST_FULL_WINDOW_DUATION[] = "duration";
const char APP_SCREEN_ON_VISIBLE_FLAG[] = "visible";

// for animation
const char ANIMATION_REQUEST_ANIMATION_FRAME[] = "requestAnimationFrame";
const char ANIMATION_CANCEL_ANIMATION_FRAME[] = "cancelAnimationFrame";

// for grid
const char GRID_GET_SYSTEM_LAYOUT_INFO[] = "getSystemLayoutInfo";
// for plugin
const int32_t PLUGIN_REQUEST_SUCCESS = 0;
const int32_t PLUGIN_REQUEST_FAIL = 200;
const int32_t PLUGIN_CALLBACK_DESTROY = 3;
} // namespace OHOS::Ace::Framework
