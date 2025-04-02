/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "xcomponent.h"

#include <ace/xcomponent/native_interface_xcomponent.h>
#include "oh_sk_log.h"

#ifdef __cplusplus
extern "C" {
#endif

void xcomponent_initEGLContext(OH_NativeXComponent *component, void *window) {
  uint64_t width;
  uint64_t height;
  int32_t status = OH_NativeXComponent_GetXComponentSize(component, window, &width, &height);

  OH_SK_LOG_INFO_A("xcomponent_initEGLContext: %" PRIu64 "x%" PRIu64, width, height);

  if (status == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
      XComponent::engine.initEGLContext(window, (int)width, (int)height);
  }
}

void xcomponent_resizeSurface(OH_NativeXComponent *component, void *window) {
  uint64_t width;
  uint64_t height;
  int32_t status = OH_NativeXComponent_GetXComponentSize(component, window, &width, &height);

  OH_SK_LOG_INFO_A("xcomponent_resizeSurface: %" PRIu64 "x%" PRIu64, width, height);

  if (status == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
      XComponent::engine.resizeSurface((int)width, (int)height);
  }
}

void onSurfaceCreated(OH_NativeXComponent *component, void *window) {
  OH_SK_LOG_INFO("XComponent: onSurfaceCreated");
  xcomponent_initEGLContext(component, window);
}

void onSurfaceChanged(OH_NativeXComponent *component, void *window) {
  OH_SK_LOG_INFO("XComponent: onSurfaceChanged");
  xcomponent_resizeSurface(component, window);
}

void onSurfaceDestroyed(OH_NativeXComponent *component, void *window) {
  OH_SK_LOG_INFO("XComponent: onSurfaceDestroyed");
  XComponent::engine.resetEGL();
}

void dispatchTouchEvent(OH_NativeXComponent *component, void *window) {
  OH_SK_LOG_INFO("XComponent: dispatchTouchEvent");
  OH_NativeXComponent_TouchEvent event;
  int32_t status = OH_NativeXComponent_GetTouchEvent(component, window, &event);
  if (status == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
      XComponent::engine.onTouchEvent(&event);
  }
}

#ifdef __cplusplus
}
#endif

OH_NativeXComponent_Callback XComponent::nativeXComponentCallback;
OH_NativeXComponent *XComponent::nativeXComponent;
Engine XComponent::engine;

Napi::Object init(Napi::Env env, Napi::Object exports) {
  OH_SK_LOG_INFO("XComponent::init");
  napi_value exportXComponent = nullptr;

  NAPI_CALL(env, napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportXComponent), exports);
  NAPI_CALL(env, napi_unwrap(env, exportXComponent, reinterpret_cast<void**>(&XComponent::nativeXComponent)), exports);

  OH_NativeXComponent_RegisterCallback(XComponent::nativeXComponent, &XComponent::nativeXComponentCallback);

  auto callback = &XComponent::nativeXComponentCallback;
  callback->OnSurfaceCreated = onSurfaceCreated;
  callback->OnSurfaceChanged = onSurfaceChanged;
  callback->OnSurfaceDestroyed = onSurfaceDestroyed;
  callback->DispatchTouchEvent = dispatchTouchEvent;

#ifdef KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED
  XComponent::engine.napiEnv = env;
#endif  // KOALA_USE_ARK_VM_WITH_ETS_DEPRECATED

  return exports;
}

extern "C" __attribute__((constructor)) void initXComponent(void) {
  ProvideModuleRegisterCallback(init);
}
