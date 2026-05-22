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

// [Start keyEventFilter]
#include "napi/native_api.h"
#include "window_manager/oh_window_comm.h"
#include "window_manager/oh_window_event_filter.h"
#include "multimodalinput/oh_input_manager.h"
#include "multimodalinput/oh_key_code.h"

// 设置过滤函数
static bool filterFunc(Input_KeyEvent *event)
{
  auto keyCode = OH_Input_GetKeyEventKeyCode(event);
  auto action = OH_Input_GetKeyEventAction(event);
  // 过滤escape和数字键的按下
  return (keyCode >= Input_KeyCode::KEYCODE_0 && keyCode <= Input_KeyCode::KEYCODE_9
     && action == Input_KeyEventAction::KEY_ACTION_DOWN) || (keyCode == Input_KeyCode::KEYCODE_ESCAPE);
}

static napi_value registerFilter(napi_env env, napi_callback_info info)
{
  size_t argc = 1;
  napi_value args[1] = {nullptr};
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  
  int32_t windowId;
  napi_get_value_int32(env, args[0], &windowId);
  
  // 向windowId对应的窗口注册filterFunc的过滤函数
  auto res = OH_NativeWindowManager_RegisterKeyEventFilter(windowId, filterFunc);
  
  napi_value errCode;
  napi_create_int32(env, res, &errCode);
  return errCode;
}

static napi_value clearFilter(napi_env env, napi_callback_info info)
{
  size_t argc = 1;
  napi_value args[1] = {nullptr};
  napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

  int32_t windowId;
  napi_get_value_int32(env, args[0], &windowId);

  auto res = OH_NativeWindowManager_UnregisterKeyEventFilter(windowId);
  napi_value errCode;
  napi_create_int32(env, res, &errCode);
  return errCode;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
  napi_property_descriptor desc[] = {
      {"registerFilter", nullptr, registerFilter, nullptr, nullptr, nullptr, napi_default, nullptr},
      {"clearFilter", nullptr, clearFilter, nullptr, nullptr, nullptr, napi_default, nullptr}};
  napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
  return exports;
}
EXTERN_C_END
// [End keyEventFilter]

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