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
PluginManager PluginManager::pluginManager_;
OH_NativeXComponent_Callback PluginManager::callback_;
static ArkUI_NativeNodeAPI_1* nodeAPI;
ArkUI_NodeHandle xc;
int32_t PluginManager::hasDraw_ = 0;
int32_t PluginManager::hasChangeColor_ = 0;

static std::string value2String(napi_env env, napi_value value)
{
    size_t stringSize = 0;
    napi_get_value_string_utf8(env, value, nullptr, 0, &stringSize);
    std::string valueString;
    valueString.resize(stringSize);
    napi_get_value_string_utf8(env, value, &valueString[0], stringSize+1, &stringSize);
    return valueString;
}
napi_value PluginManager::GetXComponentStatus(napi_env env, napi_callback_info info)
{
    napi_value hasDraw;
    napi_value hasChangeColor;

    napi_status ret = napi_create_int32(env, hasDraw_, &(hasDraw));
    if (ret != napi_ok) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus", "napi_create_int32 hasDraw_ error");
        return nullptr;
    }
    ret = napi_create_int32(env, hasChangeColor_, &(hasChangeColor));
    if (ret != napi_ok) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus", "napi_create_int32 hasChangeColor_ error");
        return nullptr;
    }

    napi_value obj;
    ret = napi_create_object(env, &obj);
    if (ret != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus", "napi_create_object error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasDraw", hasDraw);
    if (ret != napi_ok) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GetXComponentStatus", "napi_set_named_property hasDraw error");
        return nullptr;
    }
    ret = napi_set_named_property(env, obj, "hasChangeColor", hasChangeColor);
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
    napi_value thisArg;
    if (napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "NapiDrawPattern: napi_get_cb_info fail");
        return nullptr;
    }

    auto *pluginManger = PluginManager::GetInstance();
    pluginManger->eglcore_->Draw(hasDraw_);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "PluginManager", "render->eglCore_->Draw() executed");
    
    return nullptr;
}

void OnSurfaceCreatedCB(OH_NativeXComponent* component, void* window)
{
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
}
void OnSurfaceChangedCB(OH_NativeXComponent* component, void* window)
{
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
}
void OnSurfaceDestroyedCB(OH_NativeXComponent* component, void* window)
{
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
}
void DispatchTouchEventCB(OH_NativeXComponent* component, void* window)
{
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
}
PluginManager::PluginManager()
{
    eglcore_ = new EGLCore();
    callback_.OnSurfaceCreated = OnSurfaceCreatedCB;
    callback_.OnSurfaceChanged = OnSurfaceChangedCB;
    callback_.OnSurfaceDestroyed = OnSurfaceDestroyedCB;
    callback_.DispatchTouchEvent = DispatchTouchEventCB;
}

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
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "xcomponent id: %{public}s",
                 idRet->string);
    nodeAPI->addChild(column, xc);
    return column;
}

napi_value PluginManager::createNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "CreateNativeNode env or info is null");
        return nullptr;
    }
    size_t argCnt = 2;
    napi_value args[2] = { nullptr, nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "CreateNativeNode napi_get_cb_info failed");
    }
    if (argCnt != ARG_CNT) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }
    ArkUI_NodeContentHandle nodeContentHandle_ = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle_);
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1")
    );
    std::string tag = value2String(env, args[1]);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "tag=%{public}s", tag.c_str());
    int32_t ret = OH_ArkUI_NodeContent_SetUserData(nodeContentHandle_, new std::string(tag));
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "setUserData failed error=%{public}d", ret);
    }
    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager",
                     "CreateNativeNode tag=%{public}s", tag.c_str());
        auto nodeContentEvent = [](ArkUI_NodeContentEvent *event) {
            ArkUI_NodeContentHandle handle = OH_ArkUI_NodeContentEvent_GetNodeContentHandle(event);
            std::string *userDate = reinterpret_cast<std::string*>(OH_ArkUI_NodeContent_GetUserData(handle));
            if (OH_ArkUI_NodeContentEvent_GetEventType(event) == NODE_CONTENT_EVENT_ON_ATTACH_TO_WINDOW) {
                ArkUI_NodeHandle testNode;
                if (userDate) {
                    testNode = CreateNodeHandle(*userDate);
                    delete userDate;
                    userDate = nullptr;
                } else {
                    testNode = CreateNodeHandle("noUserData");
                }
                OH_ArkUI_NodeContent_AddNode(handle, testNode);
            }
        };
        OH_ArkUI_NodeContent_RegisterCallback(nodeContentHandle_, nodeContentEvent);
    }
    return nullptr;
}

void PluginManager::OnSurfaceCreated(OH_NativeXComponent* component, void* window)
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

void PluginManager::OnSurfaceDestroyed(OH_NativeXComponent* component, void* window)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native", "PluginManager::OnSurfaceDestroyed");
}

void PluginManager::DispatchTouchEvent(OH_NativeXComponent* component, void* window)
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
                     touchEvent_.x, touchEvent_.y, touchEvent_.screenX,
                     touchEvent_.screenY, touchEvent_.type, touchEvent_.force, tiltX, tiltY, toolType);
        if (touchEvent_.type == OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UP)
            eglcore_->ChangeColor(hasChangeColor_);
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
void PluginManager::OnSurfaceChanged(OH_NativeXComponent* component, void* window)
{
    int32_t ret = OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "XComponent_Native",
                 "OnSurfaceChanged ret=%{public}d width=%{public}lu, height=%{public}lu", ret, width_, height_);
}

} // namespace NativeXComponentSample
