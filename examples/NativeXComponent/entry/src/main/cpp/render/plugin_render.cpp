/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <hilog/log.h>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <string>

#include "../common/common.h"
#include "../manager/plugin_manager.h"
#include "plugin_render.h"

namespace NativeXComponentSample {
namespace {
// [Start native_xcomponent_declarative_get_native_window]
void OnSurfaceCreatedCB(OH_NativeXComponent* component, void* window)
{
    // Surface创建回调函数，用于初始化EGL环境并绘制背景
    // [StartExclude native_xcomponent_declarative_get_native_window]
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceCreatedCB");
    if ((component == nullptr) || (window == nullptr)) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceCreatedCB: component or window is null");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceCreatedCB: Unable to get XComponent id");
        return;
    }

    std::string id(idStr);
    auto render = PluginRender::GetInstance(id);
    uint64_t width;
    uint64_t height;
    int32_t xSize = OH_NativeXComponent_GetXComponentSize(component, window, &width, &height);
    if ((xSize == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) && (render != nullptr)) {
        if (render->eglCore_->EglContextInit(window, width, height)) {
            render->eglCore_->Background();
        }
    }
    // [EndExclude native_xcomponent_declarative_get_native_window]
}

void OnSurfaceChangedCB(OH_NativeXComponent* component, void* window)
{
    // Surface变化回调函数，用于处理Surface尺寸、位置等属性变化
    // [StartExclude native_xcomponent_declarative_get_native_window]
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceChangedCB");
    if ((component == nullptr) || (window == nullptr)) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceChangedCB: component or window is null");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceChangedCB: Unable to get XComponent id");
        return;
    }

    std::string id(idStr);
    auto render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->OnSurfaceChanged(component, window);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "surface changed");
    }
    // [EndExclude native_xcomponent_declarative_get_native_window]
}

void OnSurfaceDestroyedCB(OH_NativeXComponent* component, void* window)
{
    // Surface销毁回调函数，用于释放EGL资源和清理渲染实例
    // [StartExclude native_xcomponent_declarative_get_native_window]
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceDestroyedCB");
    if ((component == nullptr) || (window == nullptr)) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceDestroyedCB: component or window is null");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceDestroyedCB: Unable to get XComponent id");
        return;
    }

    std::string id(idStr);
    PluginRender::Release(id);
    // [EndExclude native_xcomponent_declarative_get_native_window]
}

void DispatchTouchEventCB(OH_NativeXComponent* component, void* window)
{
    // 触摸事件分发回调函数，用于处理屏幕触摸事件
    // [StartExclude native_xcomponent_declarative_get_native_window]
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "DispatchTouchEventCB");
    if ((component == nullptr) || (window == nullptr)) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "DispatchTouchEventCB: component or window is null");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "DispatchTouchEventCB: Unable to get XComponent id");
        return;
    }

    std::string id(idStr);
    PluginRender* render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->OnTouchEvent(component, window);
    }
    // [EndExclude native_xcomponent_declarative_get_native_window]
}
// [End native_xcomponent_declarative_get_native_window]

void DispatchMouseEventCB(OH_NativeXComponent* component, void* window)
{
    // 鼠标事件分发回调函数，用于处理鼠标点击、移动等事件
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "DispatchMouseEventCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }

    std::string id(idStr);
    auto render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->OnMouseEvent(component, window);
    }
}

void DispatchHoverEventCB(OH_NativeXComponent* component, bool isHover)
{
    // 悬停事件分发回调函数，用于处理鼠标悬停状态变化
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "DispatchHoverEventCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }

    std::string id(idStr);
    auto render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->OnHoverEvent(component, isHover);
    }
}

void OnFocusEventCB(OH_NativeXComponent* component, void* window)
{
    // 获得焦点事件回调函数，用于处理组件获得焦点的状态
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnFocusEventCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }

    std::string id(idStr);
    auto render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->OnFocusEvent(component, window);
    }
}

void OnBlurEventCB(OH_NativeXComponent* component, void* window)
{
    // 失去焦点事件回调函数，用于处理组件失去焦点的状态
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnBlurEventCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }

    std::string id(idStr);
    auto render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->OnBlurEvent(component, window);
    }
}

void OnKeyEventCB(OH_NativeXComponent* component, void* window)
{
    // 按键事件回调函数，用于处理键盘按键事件
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnKeyEventCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    std::string id(idStr);
    auto render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->OnKeyEvent(component, window);
    }
}
} // namespace

std::unordered_map<std::string, PluginRender*> PluginRender::instance_;
int32_t PluginRender::hasDraw_ = 0;
int32_t PluginRender::hasChangeColor_ = 0;

PluginRender::PluginRender(std::string& id)
{
    // 构造函数，初始化PluginRender实例，创建EGLCore对象
    this->id_ = id;
    this->eglCore_ = new EGLCore();
}

PluginRender* PluginRender::GetInstance(std::string& id)
{
    // 获取指定ID的PluginRender单例实例，如果不存在则创建新实例
    if (instance_.find(id) == instance_.end()) {
        PluginRender* instance = new PluginRender(id);
        instance_[id] = instance;
        return instance;
    } else {
        return instance_[id];
    }
}

void PluginRender::Export(napi_env env, napi_value exports)
{
    // 导出NAPI接口，注册JavaScript可调用的Native方法
    if ((env == nullptr) || (exports == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "Export: env or exports is null");
        return;
    }

    napi_property_descriptor desc[] = {
        {"drawPatternX", nullptr, PluginRender::NapiDrawPattern, nullptr, nullptr,
         nullptr, napi_default, nullptr},
        {"getStatusX", nullptr, PluginRender::TestGetXComponentStatus, nullptr, nullptr,
         nullptr, napi_default, nullptr}};
    if (napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "Export: napi_define_properties failed");
    }
}

// NAPI registration method type napi_callback. If no value is returned, nullptr is returned.
napi_value PluginRender::NapiDrawPattern(napi_env env, napi_callback_info info)
{
    // NAPI绘图方法，从JavaScript层调用来触发Native绘制操作
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender", "NapiDrawPattern");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "NapiDrawPattern: env or info is null");
        return nullptr;
    }

    napi_value thisArg;
    if (napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "NapiDrawPattern: napi_get_cb_info fail");
        return nullptr;
    }

    napi_value exportInstance;
    if (napi_get_named_property(env, thisArg, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "NapiDrawPattern: napi_get_named_property fail");
        return nullptr;
    }

    OH_NativeXComponent* nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void**>(&nativeXComponent)) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "NapiDrawPattern: napi_unwrap fail");
        return nullptr;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "NapiDrawPattern: Unable to get XComponent id");
        return nullptr;
    }

    std::string id(idStr);
    PluginRender* render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->eglCore_->Draw(hasDraw_);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender", "render->eglCore_->Draw() executed");
    }
    return nullptr;
}

void PluginRender::Release(std::string& id)
{
    // 释放指定ID的PluginRender实例资源，包括EGL资源和实例本身
    PluginRender* render = PluginRender::GetInstance(id);
    if (render != nullptr) {
        render->eglCore_->Release();
        delete render->eglCore_;
        render->eglCore_ = nullptr;
        instance_.erase(instance_.find(id));
    }
}

void PluginRender::OnSurfaceChanged(OH_NativeXComponent* component, void* window)
{
    // 处理Surface变化事件，更新组件尺寸和偏移量信息
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceChanged: Unable to get XComponent id");
        return;
    }

    std::string id(idStr);
    PluginRender* render = PluginRender::GetInstance(id);
    double offsetX;
    double offsetY;
    OH_NativeXComponent_GetXComponentOffset(component, window, &offsetX, &offsetY);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "OH_NativeXComponent_GetXComponentOffset",
        "offsetX = %{public}lf, offsetY = %{public}lf", offsetX, offsetY);
    uint64_t width;
    uint64_t height;
    OH_NativeXComponent_GetXComponentSize(component, window, &width, &height);
    if (render != nullptr) {
        render->eglCore_->UpdateSize(width, height);
    }
}

void PluginRender::OnTouchEvent(OH_NativeXComponent* component, void* window)
{
    // 处理触摸事件，包括点击、触摸工具类型、倾斜角度等信息
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "DispatchTouchEventCB: Unable to get XComponent id");
        return;
    }
    OH_NativeXComponent_TouchEvent touchEvent;
    OH_NativeXComponent_GetTouchEvent(component, window, &touchEvent);
    std::string id(idStr);
    PluginRender* render = PluginRender::GetInstance(id);
    if (render != nullptr && touchEvent.type == OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UP) {
        render->eglCore_->ChangeColor(hasChangeColor_);
    }
    float tiltX = 0.0f;
    float tiltY = 0.0f;
    OH_NativeXComponent_TouchPointToolType toolType =
        OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
    OH_NativeXComponent_GetTouchPointToolType(component, 0, &toolType);
    OH_NativeXComponent_GetTouchPointTiltX(component, 0, &tiltX);
    OH_NativeXComponent_GetTouchPointTiltY(component, 0, &tiltY);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "OnTouchEvent",
        "touch info: toolType = %{public}d, tiltX = %{public}lf, tiltY = %{public}lf", toolType, tiltX, tiltY);
}

// [Start native_xcomponent_declarative_surface_callback]
void PluginRender::RegisterCallback(OH_NativeXComponent* nativeXComponent)
{
    // 注册XComponent的各种回调函数，包括Surface回调和各类事件回调
    renderCallback_.OnSurfaceCreated = OnSurfaceCreatedCB;
    renderCallback_.OnSurfaceChanged = OnSurfaceChangedCB;
    renderCallback_.OnSurfaceDestroyed = OnSurfaceDestroyedCB;
    // [StartExclude native_xcomponent_declarative_surface_callback]
    // [Start native_xcomponent_declarative_register_event]
    renderCallback_.DispatchTouchEvent = DispatchTouchEventCB; // 注册触摸事件
    // [EndExclude native_xcomponent_declarative_surface_callback]
    OH_NativeXComponent_RegisterCallback(nativeXComponent, &renderCallback_);
    // [StartExclude native_xcomponent_declarative_surface_callback]
    mouseCallback_.DispatchMouseEvent = DispatchMouseEventCB;
    mouseCallback_.DispatchHoverEvent = DispatchHoverEventCB;
    OH_NativeXComponent_RegisterMouseEventCallback(nativeXComponent, &mouseCallback_); // 注册鼠标事件

    OH_NativeXComponent_RegisterFocusEventCallback(nativeXComponent, OnFocusEventCB); // 注册获焦事件
    OH_NativeXComponent_RegisterKeyEventCallback(nativeXComponent, OnKeyEventCB);  // 注册按键事件
    OH_NativeXComponent_RegisterBlurEventCallback(nativeXComponent, OnBlurEventCB); // 注册失焦事件
    // [EndExclude native_xcomponent_declarative_surface_callback]
    // [End native_xcomponent_declarative_register_event]
}
// [End native_xcomponent_declarative_surface_callback]

void PluginRender::OnMouseEvent(OH_NativeXComponent* component, void* window)
{
    // 处理鼠标事件，记录鼠标坐标、动作类型和按键信息
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender", "OnMouseEvent");
    OH_NativeXComponent_MouseEvent mouseEvent;
    int32_t ret = OH_NativeXComponent_GetMouseEvent(component, window, &mouseEvent);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender",
            "MouseEvent Info: x = %{public}f, y = %{public}f, action = %{public}d, button = %{public}d", mouseEvent.x,
            mouseEvent.y, mouseEvent.action, mouseEvent.button);
    } else {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "GetMouseEvent error");
    }
}

void PluginRender::OnHoverEvent(OH_NativeXComponent* component, bool isHover)
{
    // 处理鼠标悬停事件，记录悬停状态
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender", "OnHoverEvent isHover_ = %{public}d", isHover);
}

void PluginRender::OnFocusEvent(OH_NativeXComponent* component, void* window)
{
    // 处理获得焦点事件
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender", "OnFocusEvent");
}

void PluginRender::OnBlurEvent(OH_NativeXComponent* component, void* window)
{
    // 处理失去焦点事件
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender", "OnBlurEvent");
}

void PluginRender::OnKeyEvent(OH_NativeXComponent* component, void* window)
{
    // 处理按键事件，记录按键动作、键码、设备ID和时间戳等信息
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender", "OnKeyEvent");

    OH_NativeXComponent_KeyEvent* keyEvent = nullptr;
    if (OH_NativeXComponent_GetKeyEvent(component, &keyEvent) >= 0) {
        OH_NativeXComponent_KeyAction action;
        OH_NativeXComponent_GetKeyEventAction(keyEvent, &action);
        OH_NativeXComponent_KeyCode code;
        OH_NativeXComponent_GetKeyEventCode(keyEvent, &code);
        OH_NativeXComponent_EventSourceType sourceType;
        OH_NativeXComponent_GetKeyEventSourceType(keyEvent, &sourceType);
        int64_t deviceId;
        OH_NativeXComponent_GetKeyEventDeviceId(keyEvent, &deviceId);
        int64_t timeStamp;
        OH_NativeXComponent_GetKeyEventTimestamp(keyEvent, &timeStamp);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginRender",
            "KeyEvent Info: action=%{public}d, code=%{public}d, sourceType=%{public}d, deviceId=%{public}ld, "
            "timeStamp=%{public}ld",
            action, code, sourceType, deviceId, timeStamp);
    } else {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginRender", "GetKeyEvent error");
    }
}

napi_value PluginRender::TestGetXComponentStatus(napi_env env, napi_callback_info info)
{
    // 获取XComponent状态信息，返回包含绘图状态和颜色变化状态的对象
    napi_value hasDraw;
    napi_value hasChangeColor;

    napi_status ret = napi_create_int32(env, hasDraw_, &(hasDraw));
    if (ret != napi_ok) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "TestGetXComponentStatus", "napi_create_int32 hasDraw_ error");
        return nullptr;
    }
    ret = napi_create_int32(env, hasChangeColor_, &(hasChangeColor));
    if (ret != napi_ok) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "TestGetXComponentStatus", "napi_create_int32 hasChangeColor_ error");
        return nullptr;
    }

    napi_value obj;
    ret = napi_create_object(env, &obj);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "TestGetXComponentStatus", "napi_create_object error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasDraw", hasDraw);
    if (ret != napi_ok) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "TestGetXComponentStatus", "napi_set_named_property hasDraw error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasChangeColor", hasChangeColor);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "TestGetXComponentStatus",
            "napi_set_named_property hasChangeColor error");
        return nullptr;
    }
    return obj;
}
} // namespace NativeXComponentSample
