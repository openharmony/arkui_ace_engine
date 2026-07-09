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
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <unordered_map>
#include <native_window/external_window.h>
#include "../render/plugin_render.h"

namespace NativeXComponentSample {
// [Start xcomponent_define_class]
// PluginManager类定义
class PluginManager {
public:
    ~PluginManager();
    static PluginRender* GetPluginRender(int64_t& id);
    static napi_value ChangeColor(napi_env env, napi_callback_info info);
    static napi_value DrawPattern(napi_env env, napi_callback_info info);
    static napi_value SetSurfaceId(napi_env env, napi_callback_info info);
    static napi_value ChangeSurface(napi_env env, napi_callback_info info);
    static napi_value DestroySurface(napi_env env, napi_callback_info info);
    static napi_value GetXComponentStatus(napi_env env, napi_callback_info info);
    // ANI-friendly core methods taking int64_t surfaceId directly
    static void SetSurfaceIdCore(int64_t surfaceId);
    static void DestroySurfaceCore(int64_t surfaceId);
    static void ChangeSurfaceCore(int64_t surfaceId);
    static void ChangeColorCore(int64_t surfaceId);
    static void DrawPatternCore(int64_t surfaceId);
public:
    static std::unordered_map<int64_t, PluginRender*> pluginRenderMap_;
    static std::unordered_map<int64_t, OHNativeWindow*> windowMap_;
};
// [End xcomponent_define_class]
} // namespace NativeXComponentSample
#endif // NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
