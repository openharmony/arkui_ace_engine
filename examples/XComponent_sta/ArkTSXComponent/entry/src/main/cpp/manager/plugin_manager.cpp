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

#include "plugin_manager.h"
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <cstdint>
#include <hilog/log.h>
#include <native_drawing/drawing_text_typography.h>
#include <string>
#include "../common/common.h"
#include <native_window/external_window.h>

namespace NativeXComponentSample {
// [Start xcomponent_manager_cpp]
namespace {
    // 解析从ArkTS侧传入的surfaceId，此处surfaceId是一个64位int值
    int64_t ParseId(napi_env env, napi_callback_info info)
    {
        if ((env == nullptr) || (info == nullptr)) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ParseId", "env or info is null");
            return -1;
        }
        size_t argc = 1;
        napi_value args[1] = {nullptr};
        if (napi_ok != napi_get_cb_info(env, info, &argc, args, nullptr, nullptr)) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ParseId", "GetContext napi_get_cb_info failed");
            return -1;
        }
        int64_t value = 0;
        bool lossless = true;
        if (napi_ok != napi_get_value_bigint_int64(env, args[0], &value, &lossless)) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ParseId", "Get value failed");
            return -1;
        }
        return value;
    }
}
// [StartExclude xcomponent_manager_cpp]
std::unordered_map<int64_t, PluginRender*> PluginManager::pluginRenderMap_;
std::unordered_map<int64_t, OHNativeWindow*> PluginManager::windowMap_;

PluginManager::~PluginManager()
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "~PluginManager");
    for (auto iter = pluginRenderMap_.begin(); iter != pluginRenderMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    pluginRenderMap_.clear();
    for (auto iter = windowMap_.begin(); iter != windowMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    windowMap_.clear();
}
// [EndExclude xcomponent_manager_cpp]

PluginRender* PluginManager::GetPluginRender(int64_t& id)
{
    if (pluginRenderMap_.find(id) != pluginRenderMap_.end()) {
        return pluginRenderMap_[id];
    }
    return nullptr;
}

// 设置SurfaceId，基于SurfaceId完成对NativeWindow的初始化
void PluginManager::SetSurfaceIdCore(int64_t surfaceId)
{
    OHNativeWindow *nativeWindow = nullptr;
    PluginRender *pluginRender = nullptr;
    if (windowMap_.find(surfaceId) == windowMap_.end()) {
        OH_NativeWindow_CreateNativeWindowFromSurfaceId(surfaceId, &nativeWindow);
        windowMap_[surfaceId] = nativeWindow;
    } else {
        return;
    }
    if (pluginRenderMap_.find(surfaceId) == pluginRenderMap_.end()) {
        pluginRender = new PluginRender(surfaceId);
        pluginRenderMap_[surfaceId] = pluginRender;
    }
    pluginRender->InitNativeWindow(nativeWindow);
}

// 根据surfaceId查询NativeWindow尺寸并完成首次背景绘制
void PluginManager::ChangeSurfaceCore(int64_t surfaceId)
{
    auto pluginRender = GetPluginRender(surfaceId);
    if (pluginRender == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "ChangeSurface: Get pluginRender failed");
        return;
    }
    auto windowIter = windowMap_.find(surfaceId);
    if (windowIter == windowMap_.end() || windowIter->second == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "ChangeSurface: window not found");
        return;
    }
    // GET_BUFFER_GEOMETRY returns height first, then width.
    int32_t height = 0;
    int32_t width = 0;
    OH_NativeWindow_NativeWindowHandleOpt(windowIter->second, GET_BUFFER_GEOMETRY, &height, &width);
    pluginRender->UpdateNativeWindowSize(width, height);
}

napi_value PluginManager::SetSurfaceId(napi_env env, napi_callback_info info)
{
    int64_t surfaceId = ParseId(env, info);
    SetSurfaceIdCore(surfaceId);
    return nullptr;
}

// 销毁Surface
void PluginManager::DestroySurfaceCore(int64_t surfaceId)
{
    auto pluginRenderMapIter = pluginRenderMap_.find(surfaceId);
    if (pluginRenderMapIter != pluginRenderMap_.end()) {
        delete pluginRenderMapIter->second;
        pluginRenderMap_.erase(pluginRenderMapIter);
    }
    auto windowMapIter = windowMap_.find(surfaceId);
    if (windowMapIter != windowMap_.end()) {
        OH_NativeWindow_DestroyNativeWindow(windowMapIter->second);
        windowMap_.erase(windowMapIter);
    }
}

napi_value PluginManager::DestroySurface(napi_env env, napi_callback_info info)
{
    int64_t surfaceId = ParseId(env, info);
    DestroySurfaceCore(surfaceId);
    return nullptr;
}

// 根据传入的surfaceId、width、height实现Surface大小的变动
napi_value PluginManager::ChangeSurface(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "ChangeSurface: OnLoad env or info is null");
        return nullptr;
    }
    int64_t surfaceId = 0;
    size_t argc = 3;
    napi_value args[3] = {nullptr};

    if (napi_ok != napi_get_cb_info(env, info, &argc, args, nullptr, nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "ChangeSurface: GetContext napi_get_cb_info failed");
    }
    bool lossless = true;
    int index = 0;
    if (napi_ok != napi_get_value_bigint_int64(env, args[index++], &surfaceId, &lossless)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "ChangeSurface: Get value failed");
    }
    double width;
    if (napi_ok != napi_get_value_double(env, args[index++], &width)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "ChangeSurface: Get width failed");
    }
    double height;
    if (napi_ok != napi_get_value_double(env, args[index++], &height)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "ChangeSurface: Get height failed");
    }
    auto pluginRender = GetPluginRender(surfaceId);
    if (pluginRender == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "ChangeSurface: Get pluginRender failed");
        return nullptr;
    }
    pluginRender->UpdateNativeWindowSize(width, height);
    return nullptr;
}

// 实现改变绘制图形颜色的功能
void PluginManager::ChangeColorCore(int64_t surfaceId)
{
    auto pluginRender = GetPluginRender(surfaceId);
    if (pluginRender == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "ChangeColor: Get pluginRender failed");
        return;
    }
    pluginRender->ChangeColor(); // 参考Native XComponent场景ChangeColor实现
}

napi_value PluginManager::ChangeColor(napi_env env, napi_callback_info info)
{
    int64_t surfaceId = ParseId(env, info);
    ChangeColorCore(surfaceId);
    return nullptr;
}

// 实现EGL绘画逻辑
void PluginManager::DrawPatternCore(int64_t surfaceId)
{
    auto pluginRender = GetPluginRender(surfaceId);
    if (pluginRender == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "DrawPattern: Get pluginRender failed");
        return;
    }
    pluginRender->DrawPattern();
}

napi_value PluginManager::DrawPattern(napi_env env, napi_callback_info info)
{
    int64_t surfaceId = ParseId(env, info);
    DrawPatternCore(surfaceId);
    return nullptr;
}

// 获得xcomponent状态，并返回至ArkTS侧
napi_value PluginManager::GetXComponentStatus(napi_env env, napi_callback_info info)
{
    int64_t surfaceId = ParseId(env, info);
    auto pluginRender = GetPluginRender(surfaceId);
    if (pluginRender == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "GetXComponentStatus: Get pluginRender failed");
        return nullptr;
    }
    napi_value hasDraw;
    napi_value hasChangeColor;
    napi_status ret = napi_create_int32(env, pluginRender->HasDraw(), &(hasDraw));
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "GetXComponentStatus: napi_create_int32 hasDraw_ error");
        return nullptr;
    }
    ret = napi_create_int32(env, pluginRender->HasChangedColor(), &(hasChangeColor));
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "GetXComponentStatus: napi_create_int32 hasChangeColor_ error");
        return nullptr;
    }
    napi_value obj;
    ret = napi_create_object(env, &obj);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN,
                     "PluginManager", "GetXComponentStatus: napi_create_object error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasDraw", hasDraw);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "GetXComponentStatus: napi_set_named_property hasDraw error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasChangeColor", hasChangeColor);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "GetXComponentStatus: napi_set_named_property hasChangeColor error");
        return nullptr;
    }
    return obj;
}
// [End xcomponent_manager_cpp]
} // namespace NativeXComponentSample
