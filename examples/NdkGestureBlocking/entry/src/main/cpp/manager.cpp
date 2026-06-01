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

#include "napi/native_api.h"
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_animate.h>
#include <arkui/native_gesture.h>
#include <arkui/native_interface.h>
#include <arkui/native_key_event.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <cstdint>
#include <cstdio>
#include <hilog/log.h>
#include <iostream>
#include <string>

#include "manager.h"


namespace NativeXComponentSample {
Manager Manager::manager_;
ArkUI_NodeHandle refresh;

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

static ArkUI_AnimatorHandle animatorHandle = nullptr;
static ArkUI_AnimatorOption *animatorOption = nullptr;
static ArkUI_NativeAnimateAPI_1 *animateApi = nullptr;
static ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
static ArkUI_NodeHandle showContent = nullptr;
static ArkUI_NodeHandle textInput = nullptr;
static ArkUI_NativeGestureAPI_1 *gestureApi = nullptr;

struct AA {
    int32_t a;
};

static const int NUM_3 = 3;

const char *ConvertTypeToName(ArkUI_GestureRecognizerType type)
{
    const char *name = "";
    switch (type) {
        case TAP_GESTURE: {
            name = "TapGesture is preventBegin";
            break;
        }
        case LONG_PRESS_GESTURE: {
            name = "LongPressGesture is preventBegin";
            break;
        }
        case PAN_GESTURE: {
            name = "PanGesture is preventBegin";
            break;
        }
        default: {
            name = "default";
        }
    }
    return name;
}

void SetTextAttribute(ArkUI_NodeHandle& node, const char* str)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue marginValue[] = {5};
    ArkUI_AttributeItem marginItem = {marginValue, 1};
    ArkUI_AttributeItem text_valueItem = {.string = str};
    nodeAPI->setAttribute(node, NODE_TEXT_CONTENT, &text_valueItem);
    nodeAPI->setAttribute(node, NODE_MARGIN, &marginItem);
}

void SetColumnAttribute(ArkUI_NodeHandle& node, float width, float height, unsigned int color)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = { width };
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    ArkUI_NumberValue heightValue[] = { height };
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    ArkUI_NumberValue colorValue[] = {{.u32 = color}};
    ArkUI_AttributeItem colorItem = {colorValue, 1};
    nodeAPI->setAttribute(node, NODE_WIDTH, &widthItem);
    nodeAPI->setAttribute(node, NODE_HEIGHT, &heightItem);
    nodeAPI->setAttribute(node, NODE_BACKGROUND_COLOR, &colorItem);
}

void Manager::CreateNode(ArkUI_NodeHandle& button, ArkUI_NodeHandle& buttonText, ArkUI_NodeHandle& textShow,
    ArkUI_NodeHandle& textShow2)
{
    ArkUI_NumberValue marginValue[] = {5};
    ArkUI_AttributeItem marginItem = {marginValue, 1};
    ArkUI_AttributeItem textShow_valueItem = {.string = ConvertTypeToName(manager_.list_[manager_.index_])};
    nodeAPI->setAttribute(textShow, NODE_TEXT_CONTENT, &textShow_valueItem);
    nodeAPI->setAttribute(textShow, NODE_MARGIN, &marginItem);
    manager_.textShow_ = textShow;
    
    ArkUI_NumberValue button_widthValue[] = {200};
    ArkUI_AttributeItem button_widthItem = {button_widthValue, 1};
    ArkUI_NumberValue button_heightValue1[] = {50};
    ArkUI_AttributeItem button_heightItem = {button_heightValue1, 1};
    nodeAPI->setAttribute(button, NODE_WIDTH, &button_widthItem);
    nodeAPI->setAttribute(button, NODE_HEIGHT, &button_heightItem);
    nodeAPI->setAttribute(button, NODE_MARGIN, &marginItem);
    
    ArkUI_AttributeItem buttonText_valueItem = {.string = "Click to change Type"};
    nodeAPI->setAttribute(buttonText, NODE_TEXT_CONTENT, &buttonText_valueItem);
    nodeAPI->addChild(button, buttonText);
    
    ArkUI_AttributeItem textShow2_valueItem = {.string = ""};
    nodeAPI->setAttribute(textShow2, NODE_TEXT_CONTENT, &textShow2_valueItem);
    nodeAPI->setAttribute(textShow2, NODE_MARGIN, &marginItem);
    manager_.textShow2_ = textShow2;

    nodeAPI->registerNodeEvent(button, NODE_ON_CLICK, 0, nullptr);
    nodeAPI->addNodeEventReceiver(button, [](ArkUI_NodeEvent *event) {
        manager_.index_++;
        manager_.index_ %= NUM_3;
        ArkUI_AttributeItem textShow_valueItem = {.string = ConvertTypeToName(manager_.list_[manager_.index_])};
        nodeAPI->setAttribute(manager_.textShow_, NODE_TEXT_CONTENT, &textShow_valueItem);
    });
}

void Manager::SetTapGesture(ArkUI_GestureRecognizer *tapGesture, ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    gestureApi->setGestureEventTarget(
        tapGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "tapGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "touchTestDone", "column1 tapGesture is called");
        });
    gestureApi->addGestureToNode(column, tapGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

void Manager::SetPanGesture(ArkUI_GestureRecognizer *panGesture, ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    gestureApi->setGestureEventTarget(
        panGesture, GESTURE_EVENT_ACTION_ACCEPT, column, [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "panGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "touchTestDone", "column2 panGesture is called");
        });
    gestureApi->addGestureToNode(column, panGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

void Manager::SetLongPressGesture(ArkUI_GestureRecognizer *longPressGesture, ArkUI_NodeHandle &column)
{
    if (!gestureApi) {
        return;
    }
    gestureApi->setGestureEventTarget(
        longPressGesture, GESTURE_EVENT_ACTION_ACCEPT, column,
        [](ArkUI_GestureEvent *event, void *extraParams) {
            ArkUI_AttributeItem valueItem = {.string = "longPressGesture is called"};
            nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "touchTestDone",
                         "column longPressGesture is called");
        });
    gestureApi->addGestureToNode(column, longPressGesture, ArkUI_GesturePriority::NORMAL,
                                 ArkUI_GestureMask::NORMAL_GESTURE_MASK);
}

void Manager::SetGestureBlocking(ArkUI_NodeHandle &stack, ArkUI_NodeHandle &column1, OH_NativeXComponent* component)
{
    auto onTouchTestDoneCallback = [](ArkUI_GestureEvent *event, ArkUI_GestureRecognizerHandleArray recognizers,
                                      int32_t count, void *userData) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "touchTestDone", "touchTestDone count is %{public}d",
                     count);
        for (int i = 0; i < count; i++) {
            auto type = gestureApi->getGestureType(recognizers[i]);
            if (type == manager_.list_[manager_.index_]) {
                OH_ArkUI_PreventGestureRecognizerBegin(recognizers[i]);
            }
        }
    };
    OH_ArkUI_SetTouchTestDoneCallback(column1, nullptr, onTouchTestDoneCallback);
    nodeAPI->registerNodeEvent(stack, NODE_ON_CLICK, 0, nullptr);
    nodeAPI->addNodeEventReceiver(stack, [](ArkUI_NodeEvent *event) {
        ArkUI_AttributeItem valueItem = {.string = "stack click is called"};
        nodeAPI->setAttribute(manager_.textShow2_, NODE_TEXT_CONTENT, &valueItem);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "touchTestDone", "stack click tap is called");
    });
    OH_NativeXComponent_AttachNativeRootNode(component, stack);
}

void BindingGesture(napi_env env, napi_value arg, OH_NativeXComponent* component)
{
    // 此场景为多层嵌套组件场景，stack绑定了onClick，column1 2 3分别绑定了tap手势
    static ArkUI_ContextHandle context = nullptr;

    auto text1 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text1, "TapGesture");

    auto text2 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text2, "PanGesture");

    auto text3 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    SetTextAttribute(text3, "LongPressGesture");
    
    float stackWidth = 400;
    float stackHeight = 800;
    unsigned int stackColor = 0xFEF5F5F5;
    auto stack = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetColumnAttribute(stack, stackWidth, stackHeight, stackColor);

    // column
    float column1Width = 250;
    float column1Height = 500;
    unsigned int column1Color = 0xFF2FF3FF;
    auto column1 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetColumnAttribute(column1, column1Width, column1Height, column1Color);
    nodeAPI->addChild(stack, column1);
    
    float column2Width = 200;
    float column2Height = 400;
    unsigned int column2Color = 0xFF20F30F;
    auto column2 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetColumnAttribute(column2, column2Width, column2Height, column2Color);
    nodeAPI->addChild(column1, column2);
    nodeAPI->addChild(column1, text1);
    
    float column3Width = 150;
    float column3Height = 300;
    unsigned int column3Color = 0xF2F2F3F0;
    auto column3 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetColumnAttribute(column3, column3Width, column3Height, column3Color);
    nodeAPI->addChild(column2, column3);
    nodeAPI->addChild(column2, text2);
    nodeAPI->addChild(column3, text3);

    auto button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    auto buttonText = nodeAPI->createNode(ARKUI_NODE_TEXT);
    auto textShow = nodeAPI->createNode(ARKUI_NODE_TEXT);
    auto textShow2 = nodeAPI->createNode(ARKUI_NODE_TEXT);
    Manager::CreateNode(button, buttonText, textShow, textShow2);

    nodeAPI->addChild(stack, textShow);
    nodeAPI->addChild(stack, button);
    nodeAPI->addChild(stack, textShow2);

    auto tapGesture = gestureApi->createTapGesture(1, 1);
    auto panGesture = gestureApi->createPanGesture(1, GESTURE_DIRECTION_ALL, 1);
    auto longPressGesture = gestureApi->createLongPressGesture(1, false, 500);
    Manager::SetTapGesture(tapGesture, column1);
    Manager::SetPanGesture(panGesture, column2);
    Manager::SetLongPressGesture(longPressGesture, column3);
    
    Manager::SetGestureBlocking(stack, column1, component);
}

napi_value Manager::CreateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode napi_get_cb_info failed");
    }

    if (argCnt < 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
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
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_ANIMATE, ArkUI_NativeAnimateAPI_1, animateApi);
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_GESTURE, ArkUI_NativeGestureAPI_1, gestureApi);

    if (nodeAPI != nullptr) {
        if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
            BindingGesture(env, args[1], component);
        }
    }
    return nullptr;
}

napi_value Manager::UpdateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode env or info is null");
        return nullptr;
    }

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "UpdateNativeNode  1111");

    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode napi_get_cb_info failed");
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
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "CreateNativeNode %{public}s", idStr);

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