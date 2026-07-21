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

#include "plugin_manager.h"
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <cstdint>
#include <cstdio>
#include <hilog/log.h>
#include <string>
#include "arkui/native_node.h"
#include "arkui/native_node_napi.h"
#include "arkui/native_interface.h"
#include "../common/common.h"

#define COLUMN_MARGIN 10
#define XC_WIDTH 300
#define XC_HEIGHT 300
#define ARG_CNT 2

namespace NativeXComponentSample {
std::unordered_map<std::string, ArkUI_NodeHandle> PluginManager::nodeHandleMap_;
std::unordered_map<void *, OH_ArkUI_SurfaceCallback *> PluginManager::callbackMap_;
std::unordered_map<void *, OH_ArkUI_SurfaceHolder *> PluginManager::surfaceHolderMap_;
ArkUI_AccessibilityProvider *PluginManager::provider_ = nullptr;
ArkUI_NativeNodeAPI_1 *nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
    OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

PluginManager PluginManager::pluginManager_;
OH_NativeXComponent_Callback PluginManager::callback_;
ArkUI_NodeHandle xc;
int32_t PluginManager::hasDraw_ = 0;
int32_t PluginManager::hasChangeColor_ = 0;

PluginManager::~PluginManager()
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "~PluginManager");
    nativeXComponentMap_.clear();
    if (eglcore_ != nullptr) {
        delete eglcore_;
        eglcore_ = nullptr;
    }

    for (auto iter = pluginManagerMap_.begin(); iter != pluginManagerMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    pluginManagerMap_.clear();
}

// [Start surface_holder_declarative_get_native_window]
void OnSurfaceCreatedNative(OH_ArkUI_SurfaceHolder *holder)
{
    auto window = OH_ArkUI_XComponent_GetNativeWindow(holder); // 获取native window
    // [StartExclude surface_holder_declarative_get_native_window]
    auto render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    render->SetUpEGLContext(window); // 初始化egl环境
    // [EndExclude surface_holder_declarative_get_native_window]
}
// [End surface_holder_declarative_get_native_window]

void OnSurfaceChangedNative(OH_ArkUI_SurfaceHolder *holder, uint64_t width, uint64_t height)
{
    EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    render->SetEGLWindowSize(width, height); // 设置绘制区域大小
    render->Background();
}

void OnSurfaceDestroyedNative(OH_ArkUI_SurfaceHolder *holder)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, 0xff00, "onBind", "on destroyed");
    EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    render->DestroySurface(); // 销毁eglSurface相关资源
}

void OnSurfaceShowNative(OH_ArkUI_SurfaceHolder *holder)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "on surface show");
}

void OnSurfaceHideNative(OH_ArkUI_SurfaceHolder *holder)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "on surface hide");
}

void OnFrameCallbackNative(ArkUI_NodeHandle node, uint64_t timestamp, uint64_t targetTimestamp)
{
    if (!PluginManager::surfaceHolderMap_.count(node)) {
        return;
    }
    static uint64_t count = 0;
    count++;
    if (count % FRAME_COUNT == 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "OnFrameCallback count = %{public}ld", count);
    }
}

void onEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event); // 获取组件事件类型
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "on event");
    if (eventType == NODE_TOUCH_EVENT) {
        ArkUI_NodeHandle handle = OH_ArkUI_NodeEvent_GetNodeHandle(event); // 获取触发该事件的组件对象
        auto holder = PluginManager::surfaceHolderMap_[handle];
        EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
        render->DrawStar(false); // 绘制五角星
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "on touch");
    }
}

static std::string value2String(napi_env env, napi_value value)
{
    size_t stringSize = 0;
    napi_get_value_string_utf8(env, value, nullptr, 0, &stringSize);
    std::string valueString;
    valueString.resize(stringSize);
    napi_get_value_string_utf8(env, value, &valueString[0], stringSize + 1, &stringSize);
    return valueString;
}
napi_value PluginManager::GetXComponentStatus(napi_env env, napi_callback_info info)
{
    int hasDraw = -1;
    int hasChangeColor = -1;
    napi_value hasDrawValue;
    napi_value hasChangeColorValue;
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (argc == 1) {
        std::string tag = value2String(env, args[0]);
        auto xcNode = PluginManager::nodeHandleMap_[tag];
        auto surfaceHolder = OH_ArkUI_SurfaceHolder_Create(xcNode);
        EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(surfaceHolder));
        hasDraw = render->hasDraw_;
        hasChangeColor = render->hasChangeColor_;
    } else {
        hasDraw = hasDraw_;
        hasChangeColor = hasChangeColor_;
    }

    napi_status ret = napi_create_int32(env, hasDraw, &(hasDrawValue));
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus", "napi_create_int32 hasDraw error");
        return nullptr;
    }
    ret = napi_create_int32(env, hasChangeColor, &(hasChangeColorValue));
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus",
                     "napi_create_int32 hasChangeColor error");
        return nullptr;
    }

    napi_value obj;
    ret = napi_create_object(env, &obj);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus", "napi_create_object error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasDraw", hasDrawValue);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus",
                     "napi_set_named_property hasDraw error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasChangeColor", hasChangeColorValue);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus",
                     "napi_set_named_property hasChangeColor error");
        return nullptr;
    }
    return obj;
}

napi_value PluginManager::NapiDrawPattern(napi_env env, napi_callback_info info)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginManager", "NapiDrawPattern");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "NapiDrawPattern: env or info is null");
        return nullptr;
    }
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "NapiDrawPattern: napi_get_cb_info fail");
        return nullptr;
    }

    if (argCnt == 1) {
        std::string tag = value2String(env, args[0]);
        auto xcNode = PluginManager::nodeHandleMap_[tag];
        auto surfaceHolder = OH_ArkUI_SurfaceHolder_Create(xcNode);
        EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(surfaceHolder));
        if (render) {
            render->DrawStar(true);
        }
        return nullptr;
    }

    auto *pluginManger = PluginManager::GetInstance();
    pluginManger->eglcore_->Draw(hasDraw_);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginManager", "render->eglCore_->Draw() executed");

    return nullptr;
}

// [Start native_xcomponent_get_native_window]
void OnSurfaceCreatedCB(OH_NativeXComponent *component, void *window)
{
    // [StartExclude native_xcomponent_get_native_window]
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native", "OnSurfaceCreatedCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }

    std::string id(idStr);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native", "OnSurfaceCreatedCB id=%{public}s",
                 id.c_str());
    auto *pluginManger = PluginManager::GetInstance();
    pluginManger->OnSurfaceCreated(component, window);
    // [EndExclude native_xcomponent_get_native_window]
}
void OnSurfaceChangedCB(OH_NativeXComponent *component, void *window)
{
    // [StartExclude native_xcomponent_get_native_window]
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native", "OnSurfaceChangedCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    std::string id(idStr);
    auto *pluginManger = PluginManager::GetInstance();
    pluginManger->OnSurfaceChanged(component, window);
    // [EndExclude native_xcomponent_get_native_window]
}
void OnSurfaceDestroyedCB(OH_NativeXComponent *component, void *window)
{
    // [StartExclude native_xcomponent_get_native_window]
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceDestroyedCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    std::string id(idStr);
    auto *pluginManger = PluginManager::GetInstance();
    pluginManger->OnSurfaceDestroyed(component, window);
    // [EndExclude native_xcomponent_get_native_window]
}
void DispatchTouchEventCB(OH_NativeXComponent *component, void *window)
{
    // [StartExclude native_xcomponent_get_native_window]
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback", "DispatchTouchEventCB");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    std::string id(idStr);
    auto *pluginManger = PluginManager::GetInstance();
    pluginManger->DispatchTouchEvent(component, window);
    // [EndExclude native_xcomponent_get_native_window]
}
// [End native_xcomponent_get_native_window]
PluginManager::PluginManager()
{
    eglcore_ = new EGLCore();
    callback_.OnSurfaceCreated = OnSurfaceCreatedCB;
    callback_.OnSurfaceChanged = OnSurfaceChangedCB;
    callback_.OnSurfaceDestroyed = OnSurfaceDestroyedCB;
    callback_.DispatchTouchEvent = DispatchTouchEventCB;
}

ArkUI_NodeHandle CreateNodeHandle(const std::string &tag)
{
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    ArkUI_NumberValue value[] = {480};
    ArkUI_NumberValue value1[] = {{.u32 = 15}, {.f32 = 15}};
    ArkUI_AttributeItem item = {value, 1, "changeSize"};
    ArkUI_AttributeItem item1 = {value1, 2};
    nodeAPI->setAttribute(column, NODE_WIDTH, &item);
    value[0].f32 = COLUMN_MARGIN;
    nodeAPI->setAttribute(column, NODE_MARGIN, &item);
    xc = nodeAPI->createNode(ARKUI_NODE_XCOMPONENT);
    value[0].u32 = ARKUI_XCOMPONENT_TYPE_SURFACE;
    nodeAPI->setAttribute(xc, NODE_XCOMPONENT_TYPE, &item);
    nodeAPI->setAttribute(xc, NODE_XCOMPONENT_ID, &item);
    nodeAPI->setAttribute(xc, NODE_XCOMPONENT_SURFACE_SIZE, &item1);
    ArkUI_NumberValue focusable[] = {1};
    focusable[0].i32 = 1;
    ArkUI_AttributeItem focusableItem = {focusable, 1};
    nodeAPI->setAttribute(xc, NODE_FOCUSABLE, &focusableItem);
    ArkUI_NumberValue valueSize[] = {480};
    ArkUI_AttributeItem itemSize = {valueSize, 1};
    valueSize[0].f32 = XC_WIDTH;
    nodeAPI->setAttribute(xc, NODE_WIDTH, &itemSize);
    valueSize[0].f32 = XC_HEIGHT;
    nodeAPI->setAttribute(xc, NODE_HEIGHT, &itemSize);
    ArkUI_AttributeItem item2 = {value, 1, "ndkxcomponent"};
    nodeAPI->setAttribute(xc, NODE_ID, &item2);

    auto *nativeXComponent = OH_NativeXComponent_GetNativeXComponent(xc);
    if (!nativeXComponent) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "GetNativeXComponent error");
        return column;
    }
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "GetNativeXComponent success");
    OH_NativeXComponent_RegisterCallback(nativeXComponent, &PluginManager::callback_);
    auto typeRet = nodeAPI->getAttribute(xc, NODE_XCOMPONENT_TYPE);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "xcomponent type: %{public}d",
                 typeRet->value[0].i32);
    auto idRet = nodeAPI->getAttribute(xc, NODE_XCOMPONENT_ID);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "xcomponent id: %{public}s", idRet->string);
    nodeAPI->addChild(column, xc);
    return column;
}

// [Start surface_holder_ndk_create_xc_node]
ArkUI_NodeHandle CreateNodeHandleUsingSurfaceHolder(const std::string &tag)
{
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    // [StartExclude surface_holder_ndk_create_xc_node]
    ArkUI_NumberValue value[] = {480};
    ArkUI_NumberValue value1[] = {{.u32 = 15}, {.f32 = 15}};
    ArkUI_AttributeItem item = {value, 1, "changeSize"};
    ArkUI_AttributeItem item1 = {value1, 2};
    nodeAPI->setAttribute(column, NODE_WIDTH, &item);
    value[0].f32 = COLUMN_MARGIN;
    nodeAPI->setAttribute(column, NODE_MARGIN, &item);
    // [EndExclude surface_holder_ndk_create_xc_node]
    xc = nodeAPI->createNode(ARKUI_NODE_XCOMPONENT); // 创建XComponent节点
    // [StartExclude surface_holder_ndk_create_xc_node]
    value[0].u32 = ARKUI_XCOMPONENT_TYPE_SURFACE;
    nodeAPI->setAttribute(xc, NODE_XCOMPONENT_TYPE, &item);
    nodeAPI->setAttribute(xc, NODE_XCOMPONENT_ID, &item);
    nodeAPI->setAttribute(xc, NODE_XCOMPONENT_SURFACE_SIZE, &item1);
    ArkUI_NumberValue focusable[] = {1};
    focusable[0].i32 = 1;
    ArkUI_AttributeItem focusableItem = {focusable, 1};
    nodeAPI->setAttribute(xc, NODE_FOCUSABLE, &focusableItem);
    ArkUI_NumberValue valueSize[] = {480};
    ArkUI_AttributeItem itemSize = {valueSize, 1};
    valueSize[0].f32 = XC_WIDTH;
    nodeAPI->setAttribute(xc, NODE_WIDTH, &itemSize);
    valueSize[0].f32 = XC_HEIGHT;
    nodeAPI->setAttribute(xc, NODE_HEIGHT, &itemSize);
    ArkUI_AttributeItem item2 = {value, 1, "ndkxcomponent"};
    nodeAPI->setAttribute(xc, NODE_ID, &item2);
    // [EndExclude surface_holder_ndk_create_xc_node]
    OH_ArkUI_SurfaceHolder *holder = OH_ArkUI_SurfaceHolder_Create(xc); // 获取SurfaceHolder
    PluginManager::surfaceHolderMap_[xc] = holder;
    PluginManager::nodeHandleMap_[tag] = xc;
    auto callback = OH_ArkUI_SurfaceCallback_Create(); // 创建SurfaceCallback
    PluginManager::callbackMap_[holder] = callback;
    auto render = new EGLRender();
    OH_ArkUI_SurfaceHolder_SetUserData(holder, render);                                // 将render保存在holder中
    OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(callback, OnSurfaceCreatedNative); // 注册OnSurfaceCreated回调
    OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(callback, OnSurfaceChangedNative); // 注册OnSurfaceChanged回调
    OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(callback, OnSurfaceDestroyedNative); // 注册OnSurfaceDestroyed回调
    OH_ArkUI_SurfaceHolder_AddSurfaceCallback(holder, callback); // 添加SurfaceCallback回调
    if (!nodeAPI->addNodeEventReceiver(xc, onEvent)) {           // 添加事件监听，返回成功码 0
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "addNodeEventReceiver error");
    }
    if (!nodeAPI->registerNodeEvent(xc, NODE_TOUCH_EVENT, 0, nullptr)) { // 用C接口注册touch事件，返回成功码 0
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "registerTouchEvent error");
    }
    nodeAPI->addChild(column, xc); // 将XComponent挂载到Column下
    return column;
}
// [End surface_holder_ndk_create_xc_node]

// [Start surface_holder_ndk_createNode]
napi_value PluginManager::createNativeNode(napi_env env, napi_callback_info info)
{
    // [StartExclude surface_holder_ndk_createNode]
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "CreateNativeNode env or info is null");
        return nullptr;
    }
    size_t argCnt = 2;
    napi_value args[2] = {nullptr, nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "CreateNativeNode napi_get_cb_info failed");
    }
    if (argCnt != ARG_CNT) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }
    // [EndExclude surface_holder_ndk_createNode]
    ArkUI_NodeContentHandle nodeContentHandle_ = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle_);
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    std::string tag = value2String(env, args[1]);
    // [StartExclude surface_holder_ndk_createNode]
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "tag=%{public}s", tag.c_str());
    int32_t ret = OH_ArkUI_NodeContent_SetUserData(nodeContentHandle_, new std::string(tag));
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "setUserData failed error=%{public}d", ret);
    }
    // [EndExclude surface_holder_ndk_createNode]
    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "CreateNativeNode tag=%{public}s",
                     tag.c_str());
        auto nodeContentEvent = [](ArkUI_NodeContentEvent *event) {
            ArkUI_NodeContentHandle handle = OH_ArkUI_NodeContentEvent_GetNodeContentHandle(event);
            std::string *userData = reinterpret_cast<std::string *>(OH_ArkUI_NodeContent_GetUserData(handle));
            if (!userData) {
                return;
            }
            if (OH_ArkUI_NodeContentEvent_GetEventType(event) != NODE_CONTENT_EVENT_ON_ATTACH_TO_WINDOW) {
                return;
            }
            ArkUI_NodeHandle testNode;
            if (userData->find("SurfaceHolder") == std::string::npos) {
                // [StartExclude surface_holder_ndk_createNode]
                testNode = CreateNodeHandle(*userData);
                // [EndExclude surface_holder_ndk_createNode]
            } else {
                // 创建XComponent组件并使用SurfaceHolder管理Surface生命周期
                testNode = CreateNodeHandleUsingSurfaceHolder(*userData);
            }
            delete userData;
            userData = nullptr;
            OH_ArkUI_NodeContent_AddNode(handle, testNode);
        };
        OH_ArkUI_NodeContent_RegisterCallback(nodeContentHandle_, nodeContentEvent);
    }
    return nullptr;
}
// [End surface_holder_ndk_createNode]

void PluginManager::OnSurfaceCreated(OH_NativeXComponent *component, void *window)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native", "PluginManager::OnSurfaceCreated");
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    ret = OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        eglcore_->EglContextInit(window, width_, height_);
        eglcore_->Background();
    }
}

void PluginManager::OnSurfaceDestroyed(OH_NativeXComponent *component, void *window)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native", "PluginManager::OnSurfaceDestroyed");
}

void PluginManager::DispatchTouchEvent(OH_NativeXComponent *component, void *window)
{
    int32_t ret = OH_NativeXComponent_GetTouchEvent(component, window, &touchEvent_);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        float tiltX = 2.2;
        float tiltY = 2.2;
        OH_NativeXComponent_TouchPointToolType toolType =
            OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS;
        OH_NativeXComponent_GetTouchPointToolType(component, 0, &toolType);
        OH_NativeXComponent_GetTouchPointTiltX(component, 0, &tiltX);
        OH_NativeXComponent_GetTouchPointTiltY(component, 0, &tiltY);
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native",
                     "Touch Info : x=%{public}f, y=%{public}f screenx=%{public}f, screeny=%{public}f,"
                     "type=%{public}d, force=%{public}f, tiltX=%{public}f, tiltY=%{public}f, toolType=%{public}d",
                     touchEvent_.x, touchEvent_.y, touchEvent_.screenX, touchEvent_.screenY, touchEvent_.type,
                     touchEvent_.force, tiltX, tiltY, toolType);
        if (touchEvent_.type == OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UP) {
            eglcore_->ChangeColor(hasChangeColor_);
        }
    } else {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native", "touch fail");
    }

    int32_t size = 0;
    OH_NativeXComponent_HistoricalPoint *points = nullptr;

    if (OH_NativeXComponent_GetHistoricalPoints(component, window, &size, &points) ==
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "XComponent_Native", "HistoricalPoints size=%{public}d",
                     size);
        for (auto i = 0; i < size; i++) {
            auto point = points[i];
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "XComponent_Native",
                         "HistoricalPoint %{public}d Info : id=%{public}d, x=%{public}f, y=%{public}f, "
                         "type=%{public}d, timeStamp=%{public}lld, sourceTool=%{public}d",
                         i, point.id, point.x, point.y, point.type, point.timeStamp, point.sourceTool);
        }
    }
}
void PluginManager::OnSurfaceChanged(OH_NativeXComponent *component, void *window)
{
    int32_t ret = OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native",
                 "OnSurfaceChanged ret=%{public}d width=%{public}lu, height=%{public}lu", ret, width_, height_);
}

napi_value PluginManager::GetContext(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "GetContext env or info is null");
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "GetContext napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return nullptr;
    }

    int64_t value;
    if (napi_get_value_int64(env, args[0], &value) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }

    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }

    return exports;
}

// [Start native_xcomponent_declarative_get_native_xcomponent]
void PluginManager::Export(napi_env env, napi_value exports)
{
    if ((env == nullptr) || (exports == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "Export: env or exports is null");
        return;
    }

    napi_value exportInstance = nullptr;
    // 利用OH_NATIVE_XCOMPONENT_OBJ字段获取NativeXComponent实例
    if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "Export: napi_get_named_property fail");
        return;
    }

    OH_NativeXComponent *nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void **>(&nativeXComponent)) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "Export: napi_unwrap fail");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    // 从NativeXComponent实例中获取id属性用来和ArkTS侧的XComponent组件一一对应
    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "Export: OH_NativeXComponent_GetXComponentId fail");
        return;
    }

    std::string id(idStr);
    auto context = PluginManager::GetInstance();
    if ((context != nullptr) && (nativeXComponent != nullptr)) {
        context->SetNativeXComponent(id, nativeXComponent);
        auto render = context->GetRender(id);
        if (render != nullptr) {
            // 注册Surface生命周期
            render->RegisterCallback(nativeXComponent);
            render->Export(env, exports);
        }
    }
}
// [End native_xcomponent_declarative_get_native_xcomponent]

void PluginManager::SetNativeXComponent(std::string &id, OH_NativeXComponent *nativeXComponent)
{
    if (nativeXComponent == nullptr) {
        return;
    }
    nativeXComponentMap_[id] = nativeXComponent;
}

PluginRender *PluginManager::GetRender(std::string &id)
{
    if (pluginRenderMap_.find(id) == pluginRenderMap_.end()) {
        PluginRender *instance = PluginRender::GetInstance(id);
        pluginRenderMap_[id] = instance;
        return instance;
    }

    return pluginRenderMap_[id];
}

// [Start surface_holder_declarative_c_bind]
// [Start surface_holder_declarative_surface_callback]
napi_value PluginManager::BindNode(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string nodeId = value2String(env, args[0]);
    ArkUI_NodeHandle handle;
    OH_ArkUI_GetNodeHandleFromNapiValue(env, args[1], &handle);             // 获取nodeHandle
    OH_ArkUI_SurfaceHolder *holder = OH_ArkUI_SurfaceHolder_Create(handle); // 获取SurfaceHolder
    nodeHandleMap_[nodeId] = handle;
    surfaceHolderMap_[handle] = holder;
    auto callback = OH_ArkUI_SurfaceCallback_Create(); // 创建SurfaceCallback
    callbackMap_[holder] = callback;
    auto render = new EGLRender();
    OH_ArkUI_SurfaceHolder_SetUserData(holder, render);                                // 将render保存在holder中
    OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(callback, OnSurfaceCreatedNative); // 注册OnSurfaceCreated回调
    OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(callback, OnSurfaceChangedNative); // 注册OnSurfaceChanged回调
    OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(callback, OnSurfaceDestroyedNative); // 注册OnSurfaceDestroyed回调
    OH_ArkUI_SurfaceHolder_AddSurfaceCallback(holder, callback);                // 注册SurfaceCallback回调
    // [StartExclude surface_holder_declarative_c_bind]
    // [StartExclude surface_holder_declarative_surface_callback]
    OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(callback, OnSurfaceShowNative);           // 注册OnSurfaceShow回调
    OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(callback, OnSurfaceHideNative);           // 注册OnSurfaceHide回调
    OH_ArkUI_XComponent_RegisterOnFrameCallback(handle, OnFrameCallbackNative); // 注册OnFrameCallback回调
    // [Start surface_holder_declarative_register_event]
    if (!nodeAPI->addNodeEventReceiver(handle, onEvent)) { // 添加事件监听，返回成功码 0
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "addNodeEventReceiver error");
    }
    if (!nodeAPI->registerNodeEvent(handle, NODE_TOUCH_EVENT, 0, nullptr)) { // 用C接口注册touch事件，返回成功码 0
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "onBind", "registerTouchEvent error");
    }
    // [End surface_holder_declarative_register_event]
    provider_ = OH_ArkUI_AccessibilityProvider_Create(handle); // 创建一个ArkUI_AccessibilityProvider类型的对象
    /**
     * 获取ArkUI_AccessibilityProvider后，如果注册无障碍回调函数请参考：
     * https://gitee.com/openharmony/docs/blob/master/zh-cn/application-dev/ui/ndk-accessibility-xcomponent.md
     * **/
    // [EndExclude surface_holder_declarative_c_bind]
    // [EndExclude surface_holder_declarative_surface_callback]
    return nullptr;
}
// [End surface_holder_declarative_c_bind]
// [End surface_holder_declarative_surface_callback]

// [Start surface_holder_declarative_c_unbind]
napi_value PluginManager::UnbindNode(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string nodeId = value2String(env, args[0]);
    ArkUI_NodeHandle node;
    if (nodeHandleMap_.find(nodeId) == nodeHandleMap_.end()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SetNeedSoftKeyboard", "nodeId not exit error");
        return nullptr;
    }
    node = nodeHandleMap_[nodeId];
    // [StartExclude surface_holder_declarative_c_bind]
    OH_ArkUI_XComponent_UnregisterOnFrameCallback(node); // 解注册帧回调
    OH_ArkUI_AccessibilityProvider_Dispose(provider_);   // 销毁ArkUI_AccessibilityProvider
    // [EndExclude surface_holder_declarative_c_bind]
    auto holder = surfaceHolderMap_[node];
    if (PluginManager::callbackMap_.count(holder)) {
        auto callback = PluginManager::callbackMap_[holder];
        OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(holder, callback); // 移除SurfaceCallback
        OH_ArkUI_SurfaceCallback_Dispose(callback);                     // 销毁surfaceCallback
        PluginManager::callbackMap_.erase(holder);
    }
    auto render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    delete render;                          // 销毁EGLRender对象
    OH_ArkUI_SurfaceHolder_Dispose(holder); // 销毁surfaceHolder
    nodeAPI->disposeNode(node);             // 销毁nodeHandle
    nodeHandleMap_.erase(nodeId);
    return nullptr;
}
// [End surface_holder_declarative_c_unbind]

napi_value PluginManager::SetFrameRate(napi_env env, napi_callback_info info)
{
    size_t argc = 4;
    napi_value args[4] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string nodeId = value2String(env, args[0]);
    auto node = nodeHandleMap_[nodeId];

    int32_t min = 0;
    napi_get_value_int32(env, args[FIRST_ARG], &min);

    int32_t max = 0;
    napi_get_value_int32(env, args[SECOND_ARG], &max);

    int32_t expected = 0;
    napi_get_value_int32(env, args[THIRD_ARG], &expected);
    OH_NativeXComponent_ExpectedRateRange range = {.min = min, .max = max, .expected = expected};
    OH_ArkUI_XComponent_SetExpectedFrameRateRange(node, range); // 设置期望帧率
    return nullptr;
}

napi_value PluginManager::SetNeedSoftKeyboard(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string nodeId = value2String(env, args[0]);
    ArkUI_NodeHandle node;
    if (nodeHandleMap_.find(nodeId) == nodeHandleMap_.end()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SetNeedSoftKeyboard", "nodeId not exit error");
        return nullptr;
    }
    node = nodeHandleMap_[nodeId];

    bool needSoftKeyboard = false;
    napi_get_value_bool(env, args[1], &needSoftKeyboard);
    OH_ArkUI_XComponent_SetNeedSoftKeyboard(node, needSoftKeyboard); // 设置是否需要软键盘
    return nullptr;
}

napi_value PluginManager::Initialize(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string nodeId = value2String(env, args[0]);
    ArkUI_NodeHandle node;
    if (nodeHandleMap_.find(nodeId) == nodeHandleMap_.end()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SetNeedSoftKeyboard", "nodeId not exit error");
        return nullptr;
    }
    node = nodeHandleMap_[nodeId];
    OH_ArkUI_XComponent_Initialize(node);
    auto holder = surfaceHolderMap_[node];
    EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    render->DrawStar(true); // 绘制五角星
    return nullptr;
}

napi_value PluginManager::Finalize(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string nodeId = value2String(env, args[0]);
    ArkUI_NodeHandle node;
    if (nodeHandleMap_.find(nodeId) == nodeHandleMap_.end()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SetNeedSoftKeyboard", "nodeId not exit error");
        return nullptr;
    }
    node = nodeHandleMap_[nodeId];
    auto holder = surfaceHolderMap_[node];
    EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    render->Clear();
    OH_ArkUI_XComponent_Finalize(node);
    return nullptr;
}

napi_value PluginManager::DrawStar(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    std::string nodeId = value2String(env, args[0]);
    ArkUI_NodeHandle node;
    if (nodeHandleMap_.find(nodeId) == nodeHandleMap_.end()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SetNeedSoftKeyboard", "nodeId not exit error");
        return nullptr;
    }
    node = nodeHandleMap_[nodeId];
    auto holder = surfaceHolderMap_[node];
    EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    OH_LOG_Print(LOG_APP, LOG_ERROR, 0xff00, "onBind", "YGB DrawStar w:[%{public}d],h[%{public}d]", render->width_,
                 render->height_);
    render->DrawStar(true); // 绘制五角星
    return nullptr;
}

napi_value PluginManager::DrawPatternForSurfaceHolder(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeHandle handle;
    OH_ArkUI_GetNodeHandleFromNapiValue(env, args[0], &handle);             // 获取nodeHandle
    OH_ArkUI_SurfaceHolder *holder = OH_ArkUI_SurfaceHolder_Create(handle); // 获取SurfaceHolder
    EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    render->DrawStar(true);
    return nullptr;
}

napi_value PluginManager::GetStatusForSurfaceHolder(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    ArkUI_NodeHandle handle;
    OH_ArkUI_GetNodeHandleFromNapiValue(env, args[0], &handle);             // 获取nodeHandle
    OH_ArkUI_SurfaceHolder *holder = OH_ArkUI_SurfaceHolder_Create(handle); // 获取SurfaceHolder
    EGLRender *render = reinterpret_cast<EGLRender *>(OH_ArkUI_SurfaceHolder_GetUserData(holder));
    auto hasDraw = render->hasDraw_;
    auto hasChangeColor = render->hasChangeColor_;

    napi_value hasDrawValue;
    napi_value hasChangeColorValue;
    napi_create_int32(env, hasDraw, &(hasDrawValue));
    napi_create_int32(env, hasChangeColor, &(hasChangeColorValue));
    napi_value obj;
    auto ret = napi_create_object(env, &obj);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus", "napi_create_object error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasDraw", hasDrawValue);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus",
                     "napi_set_named_property hasDraw error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasChangeColor", hasChangeColorValue);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus",
                     "napi_set_named_property hasChangeColor error");
        return nullptr;
    }
    return obj;
}

} // namespace NativeXComponentSample
