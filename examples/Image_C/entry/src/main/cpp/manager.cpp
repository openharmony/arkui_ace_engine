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
#include <native_drawing/drawing_brush.h>
#include <native_drawing/drawing_font.h>
#include <native_drawing/drawing_rect.h>
#include <native_drawing/drawing_round_rect.h>
#include <native_drawing/drawing_text_blob.h>
#include <string>
#include <cstdio>

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_interface.h>
#include <hilog/log.h>

#include "manager.h"
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_path.h>
#include <native_drawing/drawing_pen.h>
#include <native_drawing/drawing_color.h>


namespace NativeXComponentSample {
Manager Manager::manager_;

Manager::~Manager()
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "~Manager");
    for (auto iter = nativeXComponentMap_.begin(); iter != nativeXComponentMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            iter->second = nullptr;
        }
    }
    nativeXComponentMap_.clear();

    for (auto iter = containerMap_.begin(); iter != containerMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    containerMap_.clear();
}

bool CheckEnv(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
        return false;
    }

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return false;
    }
    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return false;
    }

    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return false;
    }
    return true;
}

napi_value Manager::CreateNativeNode(napi_env env, napi_callback_info info)
{
    if (!CheckEnv(env, info)) {
        return nullptr;
    }
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }

    auto manager = Manager::GetInstance();
    if (manager == nullptr) {
        return nullptr;
    }

    OH_NativeXComponent *component = manager->GetNativeXComponent(idStr);
    if (component == nullptr) {
        return nullptr;
    }

    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    if (nodeAPI == nullptr) {
        return nullptr;
    }
    if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        auto Column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
        ArkUI_NumberValue ColumnWidthValue[] = {400};
        ArkUI_AttributeItem ColumnWidthItem = {ColumnWidthValue, 1};
        nodeAPI->setAttribute(Column, NODE_WIDTH, &ColumnWidthItem);
        ArkUI_NumberValue ColumnHeightValue[] = {600};
        ArkUI_AttributeItem ColumnHeightItem = {ColumnHeightValue, 1};
        nodeAPI->setAttribute(Column, NODE_HEIGHT, &ColumnHeightItem);
        ArkUI_NumberValue ColumnPaddingValue[] = {5};
        ArkUI_AttributeItem ColumnPaddingItem = {ColumnPaddingValue, 1};
        nodeAPI->setAttribute(Column, NODE_PADDING, &ColumnPaddingItem);
        auto textInput = nodeAPI->createNode(ARKUI_NODE_TEXT_INPUT);
        nodeAPI->registerNodeEvent(textInput, NODE_TEXT_INPUT_ON_CHANGE_WITH_PREVIEW_TEXT, 0, nullptr);
        nodeAPI->addChild(Column, textInput);
        OH_NativeXComponent_AttachNativeRootNode(component, Column);
    }
    return nullptr;
}


napi_value Manager::UpdateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong type of arguments");
        return nullptr;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }

    auto manager = Manager::GetInstance();
    if (manager == nullptr) {
        return nullptr;
    }

    OH_NativeXComponent *component = manager->GetNativeXComponent(idStr);
    if (component == nullptr) {
        return nullptr;
    }

    if ((env == nullptr) || (info == nullptr || component == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext env or info is null");
        return nullptr;
    }

    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    if (nodeAPI != nullptr) {
        if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "UpdateNativeNode");
        }
    }
    return nullptr;
}

napi_value Manager::GetContext(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext env or info is null");
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext napi_get_cb_info failed");
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

void Manager::Export(napi_env env, napi_value exports)
{
    if ((env == nullptr) || (exports == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: env or exports is null");
        return;
    }

    napi_value exportInstance = nullptr;
    if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: napi_get_named_property fail");
        return;
    }

    OH_NativeXComponent *nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void **>(&nativeXComponent)) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: napi_unwrap fail");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager",
                     "Export: OH_NativeXComponent_GetXComponentId fail");
        return;
    }

    std::string id(idStr);
    auto manager = Manager::GetInstance();
    if ((manager != nullptr) && (nativeXComponent != nullptr)) {
        manager->SetNativeXComponent(id, nativeXComponent);
        auto container = manager->GetContainer(id);
        if (container != nullptr) {
            container->RegisterCallback(nativeXComponent);
        }
    }
}

void Manager::SetNativeXComponent(std::string &id, OH_NativeXComponent *nativeXComponent)
{
    if (nativeXComponent == nullptr) {
        return;
    }

    if (nativeXComponentMap_.find(id) == nativeXComponentMap_.end()) {
        nativeXComponentMap_[id] = nativeXComponent;
        return;
    }

    if (nativeXComponentMap_[id] != nativeXComponent) {
        OH_NativeXComponent *tmp = nativeXComponentMap_[id];
        delete tmp;
        tmp = nullptr;
        nativeXComponentMap_[id] = nativeXComponent;
    }
}

OH_NativeXComponent *Manager::GetNativeXComponent(const std::string &id) { return nativeXComponentMap_[id]; }

Container *Manager::GetContainer(std::string &id)
{
    if (containerMap_.find(id) == containerMap_.end()) {
        Container *instance = Container::GetInstance(id);
        containerMap_[id] = instance;
        return instance;
    }

    return containerMap_[id];
}
} // namespace NativeXComponentSample
