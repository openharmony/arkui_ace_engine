/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
#define NATIVE_XCOMPONENT_PLUGIN_MANAGER_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <cstdint>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <napi/native_api.h>
#include <string>
#include <unordered_map>
#include "render/egl_core.h"

namespace NativeXComponentSample {
class PluginManager {
public:
    
    static OH_NativeXComponent_Callback callback_;
    PluginManager();
    ~PluginManager();
    static PluginManager* GetInstance()
    {
        return &PluginManager::pluginManager_;
    }
    
    static napi_value createNativeNode(napi_env env, napi_callback_info info);
    static napi_value GetXComponentStatus(napi_env env, napi_callback_info info);
    static napi_value NapiDrawPattern(napi_env env, napi_callback_info info);
    
    // CApi XComponent
    void OnSurfaceChanged(OH_NativeXComponent* component, void* window);
    void OnSurfaceDestroyed(OH_NativeXComponent* component, void* window);
    void DispatchTouchEvent(OH_NativeXComponent* component, void* window);
    void OnSurfaceCreated(OH_NativeXComponent* component, void* window);

private:
    static PluginManager pluginManager_;
    std::unordered_map<std::string, OH_NativeXComponent*> nativeXComponentMap_;
    std::unordered_map<std::string, PluginManager*> pluginManagerMap_;
    
public:
    EGLCore *eglcore_;
    uint64_t width_;
    uint64_t height_;
    OH_NativeXComponent_TouchEvent touchEvent_;
    static int32_t hasDraw_;
    static int32_t hasChangeColor_;
};
} // namespace NativeXComponentSample
#endif // NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
