/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

// [Start injectTouchEvent]
#include "napi/native_api.h"
#include "window_manager/oh_window.h"
#include "multimodalinput/oh_input_manager.h"

namespace {
enum InjectEventArgIndex {
    ARG_WINDOW_ID = 0,
    ARG_DISPLAY_ID,
    ARG_WINDOW_X,
    ARG_WINDOW_Y,
    ARG_ACTION,
    ARG_FINGER_ID,
    ARG_DISPLAY_X,
    ARG_DISPLAY_Y,
    ARG_ACTION_TIME,
    ARG_TE_WINDOW_ID
};
}

static napi_value injectEvent(napi_env env, napi_callback_info info)
{
  size_t argc = 10;
  napi_value args[10] = {nullptr};
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  int32_t windowId;
  napi_get_value_int32(env, args[ARG_WINDOW_ID], &windowId);

  int32_t displayId;
  napi_get_value_int32(env, args[ARG_DISPLAY_ID], &displayId);

  int32_t windowX;
  napi_get_value_int32(env, args[ARG_WINDOW_X], &windowX);

  int32_t windowY;
  napi_get_value_int32(env, args[ARG_WINDOW_Y], &windowY);

  int32_t action;
  napi_get_value_int32(env, args[ARG_ACTION], &action);

  int32_t fingerId;
  napi_get_value_int32(env, args[ARG_FINGER_ID], &fingerId);

  int32_t displayX;
  napi_get_value_int32(env, args[ARG_DISPLAY_X], &displayX);

  int32_t displayY;
  napi_get_value_int32(env, args[ARG_DISPLAY_Y], &displayY);

  int32_t actionTime;
  napi_get_value_int32(env, args[ARG_ACTION_TIME], &actionTime);

  int32_t TE_WindowId;
  napi_get_value_int32(env, args[ARG_TE_WINDOW_ID], &TE_WindowId);
  
  // 构造多模事件touchEvent
  Input_TouchEvent* touchEvent = OH_Input_CreateTouchEvent();
  OH_Input_SetTouchEventAction(touchEvent, action);
  OH_Input_SetTouchEventFingerId(touchEvent, fingerId);
  OH_Input_SetTouchEventDisplayX(touchEvent, displayX);
  OH_Input_SetTouchEventDisplayY(touchEvent, displayY);
  OH_Input_SetTouchEventActionTime(touchEvent, actionTime);
  OH_Input_SetTouchEventWindowId(touchEvent, TE_WindowId);
  OH_Input_SetTouchEventDisplayId(touchEvent, displayId);

  // 向windowId对应的窗口注入多模触摸事件
  auto res = OH_WindowManager_InjectTouchEvent(windowId, touchEvent, windowX, windowY);

  // 使用完touchEvent后销毁对象
  OH_Input_DestroyTouchEvent(&touchEvent);

  napi_value errCode;
  napi_create_int32(env, res, &errCode);
  return errCode;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
  napi_property_descriptor desc[] = {
      {"injectEvent", nullptr, injectEvent, nullptr, nullptr, nullptr, napi_default, nullptr}};
  napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
  return exports;
}
EXTERN_C_END
// [End injectTouchEvent]

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void) { napi_module_register(&demoModule); }