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

#include "manager.h"

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <cstdint>
#include <hilog/log.h>
#include <string>

#include "container.h"
#include "focus_manager.h"
#include "napi/native_api.h"

namespace NativeXComponentSample {
Manager Manager::manager_;

Manager::~Manager()
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "~Manager");
    for (auto& [key, component] : nativeXComponentMap_) {
        component = nullptr;
    }
    nativeXComponentMap_.clear();
}

static ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
static ArkUI_Context* context_ = nullptr;

// 颜色常量
const uint32_t RED_COLOR = 0xFFFF0000;
const uint32_t BLACK_COLOR = 0xFF000000;
const uint32_t DEFAULT_COLOR = 0xFF165DFF;

// 数字常量
const int32_t NUMBER_ZERO = 0;
const int32_t NUMBER_ONE = 1;
const int32_t NUMBER_TWO = 2;
const int32_t NUMBER_THREE = 3;
const int32_t NUMBER_FOUR = 4;
const int32_t NUMBER_FIVE = 5;
const int32_t NUMBER_NINE = 9;

// 按键事件回调数据结构
struct KeyEventCallbackData {
    ArkUI_NodeHandle buttonNode;   // Button节点引用
    ArkUI_NodeEventType eventType; // 事件类型
};

KeyEventCallbackData* CreateCallbackData(
    ArkUI_NodeHandle buttonNode, ArkUI_NodeEventType eventType)
{
    KeyEventCallbackData* callbackData = new KeyEventCallbackData();
    callbackData->buttonNode = buttonNode;
    callbackData->eventType = eventType;
    return callbackData;
}

// 获焦回调函数
void EventReceiver(ArkUI_NodeEvent* event)
{
    if (!event || !nodeAPI) {
        return;
    }
    // 从事件中提取关键信息（根据ArkUI_NodeEvent结构体定义）
    ArkUI_NodeHandle node = OH_ArkUI_NodeEvent_GetNodeHandle(event);        // 事件所属节点
    ArkUI_NodeEventType eventType = OH_ArkUI_NodeEvent_GetEventType(event); // 事件类型
    // 处理焦点相关事件
    if (eventType == NODE_ON_FOCUS) {
        // 获焦：设置红色背景
        ArkUI_NumberValue colorValue[] = { { .u32 = RED_COLOR } };
        ArkUI_AttributeItem colorItem = { colorValue, 1 };
        nodeAPI->setAttribute(node, NODE_BACKGROUND_COLOR, &colorItem);
    } else if (eventType == NODE_ON_BLUR) {
        // 失焦：设置黑色背景
        ArkUI_NumberValue colorValue[] = { { .u32 = BLACK_COLOR } };
        ArkUI_AttributeItem colorItem = { colorValue, 1 };
        nodeAPI->setAttribute(node, NODE_BACKGROUND_COLOR, &colorItem);
    } else if (eventType == NODE_ON_CLICK) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "EventReceiver",
            "Button9 clicked, creating real menu for AutoTransfer test");
        bool autoTransfer = true;
        auto focusManager = FocusManager::GetInstance();
        focusManager->SetAutoTransfer(context_, autoTransfer);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "EventReceiver", "AutoTransfer set to true");
    } else if (eventType == NODE_ON_KEY_EVENT) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "EventReceiver",
            "List handle the KeyEvent");
    }
}

void SetListAttribute(ArkUI_NodeHandle& list)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue listWidthValue[] = { 1 };
    ArkUI_AttributeItem listWidthItem = { listWidthValue, 1 };
    nodeAPI->setAttribute(list, NODE_WIDTH_PERCENT, &listWidthItem);
    ArkUI_NumberValue listHeightValue[] = { 200 };
    ArkUI_AttributeItem listHeightItem = { listHeightValue, 1 };
    nodeAPI->setAttribute(list, NODE_HEIGHT, &listHeightItem);
    ArkUI_NumberValue borderColorValue[] = { { .u32 = 0xCCCCCCCC } };
    ArkUI_AttributeItem borderColorItem = { borderColorValue, 1 };
    nodeAPI->setAttribute(list, NODE_BORDER_COLOR, &borderColorItem);
    ArkUI_NumberValue borderWidthValue[] = { 5 };
    ArkUI_AttributeItem borderWidthItem = { borderWidthValue, 1 };
    nodeAPI->setAttribute(list, NODE_BORDER_WIDTH, &borderWidthItem);
    ArkUI_NumberValue initialIndexValue[] = { { .i32 = 5 } };
    ArkUI_AttributeItem initialIndexItem = { initialIndexValue, 1 };
    nodeAPI->setAttribute(list, NODE_LIST_INITIAL_INDEX, &initialIndexItem);
    ArkUI_NumberValue edgeEffectValue[] = { { .i32 = ARKUI_EDGE_EFFECT_NONE } };
    ArkUI_AttributeItem edgeEffectItem = { edgeEffectValue, 1 };
    nodeAPI->setAttribute(list, NODE_SCROLL_EDGE_EFFECT, &edgeEffectItem);
    ArkUI_AttributeItem nodeIdItem = { .string = "inner" };
    nodeAPI->setAttribute(list, NODE_ID, &nodeIdItem);
    KeyEventCallbackData* callbackData = CreateCallbackData(list, NODE_ON_KEY_EVENT);
    nodeAPI->registerNodeEvent(list, NODE_ON_KEY_EVENT, NUMBER_FIVE, callbackData);
    nodeAPI->registerNodeEventReceiver(EventReceiver);
}

void SetScrollAttribute(ArkUI_NodeHandle& scroll)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue scrollWidthValue[] = { 1 };
    ArkUI_AttributeItem scrollWidthItem = { scrollWidthValue, 1 };
    nodeAPI->setAttribute(scroll, NODE_WIDTH_PERCENT, &scrollWidthItem);
    ArkUI_NumberValue scrollHeightValue[] = { 400 };
    ArkUI_AttributeItem scrollHeightItem = { scrollHeightValue, 1 };
    nodeAPI->setAttribute(scroll, NODE_HEIGHT, &scrollHeightItem);
    ArkUI_NumberValue scrollColorValue[] = { { .u32 = 0xFF2F2F4F } };
    ArkUI_AttributeItem backColorItem = { scrollColorValue, 1 };
    nodeAPI->setAttribute(scroll, NODE_BACKGROUND_COLOR, &backColorItem);
    ArkUI_AttributeItem scrollNodeIdItem = { .string = "outer" };
    nodeAPI->setAttribute(scroll, NODE_ID, &scrollNodeIdItem);
}

// 创建默认按钮
ArkUI_NodeHandle CreateDefaultButton(
    const ArkUI_AttributeItem& marginItem, const ArkUI_AttributeItem& widthItem, const ArkUI_AttributeItem& heightItem)
{
    ArkUI_NodeHandle defaultListItem = nodeAPI->createNode(ARKUI_NODE_LIST_ITEM);
    nodeAPI->setAttribute(defaultListItem, NODE_MARGIN, &marginItem);

    ArkUI_NodeHandle defaultButton = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    nodeAPI->setAttribute(defaultButton, NODE_WIDTH_PERCENT, &widthItem);
    nodeAPI->setAttribute(defaultButton, NODE_HEIGHT, &heightItem);

    // 设置默认按钮背景色
    ArkUI_NumberValue defaultBackColorValue[] = { { .u32 = 0xFFE6F3FF } };
    ArkUI_AttributeItem defaultBackColorItem = { defaultBackColorValue, 1 };
    nodeAPI->setAttribute(defaultButton, NODE_BACKGROUND_COLOR, &defaultBackColorItem);

    // 设置默认按钮文本和ID
    ArkUI_AttributeItem defaultContentItem = { .string = "ButtonDefault" };
    nodeAPI->setAttribute(defaultButton, NODE_BUTTON_LABEL, &defaultContentItem);
    nodeAPI->setAttribute(defaultButton, NODE_ID, &defaultContentItem);

    // 设置为默认焦点
    ArkUI_NumberValue defaultFocusValue[] = { { .i32 = 1 } };
    ArkUI_AttributeItem defaultFocusItem = { defaultFocusValue, 1 };
    nodeAPI->setAttribute(defaultButton, NODE_DEFAULT_FOCUS, &defaultFocusItem);

    // 注册焦点事件
    nodeAPI->registerNodeEvent(defaultButton, NODE_ON_FOCUS, 0, defaultButton);
    nodeAPI->registerNodeEvent(defaultButton, NODE_ON_BLUR, 0, defaultButton);
    nodeAPI->registerNodeEventReceiver(EventReceiver);

    nodeAPI->addChild(defaultListItem, defaultButton);
    return defaultListItem;
}

// 创建普通按钮
ArkUI_NodeHandle CreateNormalButton(int index, const ArkUI_AttributeItem& marginItem,
    const ArkUI_AttributeItem& widthItem, const ArkUI_AttributeItem& heightItem)
{
    ArkUI_NodeHandle listItem = nodeAPI->createNode(ARKUI_NODE_LIST_ITEM);
    nodeAPI->setAttribute(listItem, NODE_MARGIN, &marginItem);

    ArkUI_NodeHandle button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    nodeAPI->setAttribute(button, NODE_WIDTH_PERCENT, &widthItem);
    nodeAPI->setAttribute(button, NODE_HEIGHT, &heightItem);

    // 设置按钮默认背景色
    ArkUI_NumberValue backColorValue[] = { { .u32 = DEFAULT_COLOR } };
    ArkUI_AttributeItem backColorItem = { backColorValue, 1 };
    nodeAPI->setAttribute(button, NODE_BACKGROUND_COLOR, &backColorItem);

    // 设置按钮文本和ID
    std::string content = "Button" + std::to_string(index);
    ArkUI_AttributeItem contentItem = { .string = content.c_str() };
    nodeAPI->setAttribute(button, NODE_BUTTON_LABEL, &contentItem);
    nodeAPI->setAttribute(button, NODE_ID, &contentItem);

    // Button9需要注册点击事件
    if (index == NUMBER_NINE) {
        nodeAPI->registerNodeEvent(button, NODE_ON_CLICK, 0, button);
    }

    // 注册焦点事件
    nodeAPI->registerNodeEvent(button, NODE_ON_FOCUS, 0, button);
    nodeAPI->registerNodeEvent(button, NODE_ON_BLUR, 0, button);
    nodeAPI->registerNodeEventReceiver(EventReceiver);

    nodeAPI->addChild(listItem, button);
    return listItem;
}

// 创建特殊按钮（Button4包装在Column中）
ArkUI_NodeHandle CreateSpecialButton(int index, const ArkUI_AttributeItem& marginItem,
    const ArkUI_AttributeItem& widthItem, const ArkUI_AttributeItem& heightItem)
{
    ArkUI_NodeHandle listItem = nodeAPI->createNode(ARKUI_NODE_LIST_ITEM);
    nodeAPI->setAttribute(listItem, NODE_MARGIN, &marginItem);

    ArkUI_NodeHandle button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    nodeAPI->setAttribute(button, NODE_WIDTH_PERCENT, &widthItem);
    nodeAPI->setAttribute(button, NODE_HEIGHT, &heightItem);

    // 设置按钮默认背景色
    ArkUI_NumberValue backColorValue[] = { { .u32 = DEFAULT_COLOR } };
    ArkUI_AttributeItem backColorItem = { backColorValue, 1 };
    nodeAPI->setAttribute(button, NODE_BACKGROUND_COLOR, &backColorItem);

    // 设置按钮文本和ID
    std::string content = "Button" + std::to_string(index);
    ArkUI_AttributeItem contentItem = { .string = content.c_str() };
    nodeAPI->setAttribute(button, NODE_BUTTON_LABEL, &contentItem);
    nodeAPI->setAttribute(button, NODE_ID, &contentItem);

    // 注册焦点事件
    nodeAPI->registerNodeEvent(button, NODE_ON_FOCUS, 0, button);
    nodeAPI->registerNodeEvent(button, NODE_ON_BLUR, 0, button);
    nodeAPI->registerNodeEventReceiver(EventReceiver);

    // 创建Column4包装
    ArkUI_NodeHandle column4 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    nodeAPI->setAttribute(column4, NODE_WIDTH_PERCENT, &widthItem);
    nodeAPI->setAttribute(column4, NODE_HEIGHT, &heightItem);
    ArkUI_AttributeItem columnContentItem = { .string = "Column4" };
    nodeAPI->setAttribute(column4, NODE_ID, &columnContentItem);

    nodeAPI->addChild(column4, button);
    nodeAPI->addChild(listItem, column4);
    return listItem;
}

void AddListChild(ArkUI_NodeHandle& list)
{
    if (!nodeAPI) {
        return;
    }

    // 创建公共属性
    ArkUI_NumberValue marginValues[] = { { 10 }, { 5 }, { 10 }, { 5 } };
    ArkUI_AttributeItem marginItem = { marginValues, 4 };
    ArkUI_NumberValue widthValue[] = { 1 };
    ArkUI_AttributeItem widthItem = { widthValue, 1 };
    ArkUI_NumberValue heightValue[] = { 40 };
    ArkUI_AttributeItem heightItem = { heightValue, 1 };

    // 创建默认按钮
    ArkUI_NodeHandle defaultListItem = CreateDefaultButton(marginItem, widthItem, heightItem);
    nodeAPI->addChild(list, defaultListItem);

    // 创建Button0-Button9
    for (int i = NUMBER_ZERO; i < NUMBER_NINE; i++) {
        ArkUI_NodeHandle listItem;

        if (i == NUMBER_FOUR) {
            listItem = CreateSpecialButton(i, marginItem, widthItem, heightItem);
        } else {
            listItem = CreateNormalButton(i, marginItem, widthItem, heightItem);
        }

        nodeAPI->addChild(list, listItem);
    }
}

void AddScrollChild(ArkUI_NodeHandle& scroll, ArkUI_NodeHandle& list)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue itemWidthValue[] = { 400 };
    ArkUI_AttributeItem itemWidthItem = { itemWidthValue, 1 };
    ArkUI_NumberValue itemHeightValue[] = { 40 };
    ArkUI_AttributeItem itemHeightItem = { itemHeightValue, 1 };
    ArkUI_NumberValue itemBackColorvalue[] = { { .u32 = 0xFF00FFFF } };
    ArkUI_AttributeItem itemBackColoritem = { itemBackColorvalue, 1 };
    ArkUI_NodeHandle text = nodeAPI->createNode(ARKUI_NODE_TEXT);
    nodeAPI->setAttribute(text, NODE_WIDTH, &itemWidthItem);
    nodeAPI->setAttribute(text, NODE_HEIGHT, &itemHeightItem);
    nodeAPI->setAttribute(text, NODE_BACKGROUND_COLOR, &itemBackColoritem);
    ArkUI_AttributeItem contentItem = { .string = "TestFocus" };
    nodeAPI->setAttribute(text, NODE_TEXT_CONTENT, &contentItem);
    nodeAPI->setAttribute(text, NODE_ID, &contentItem);
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    nodeAPI->addChild(column, text);
    nodeAPI->addChild(column, list);

    nodeAPI->addChild(scroll, column);
}

void CreateFocusTree(napi_env env, napi_value arg, OH_NativeXComponent* component)
{
    // 创建父子滚动容器
    ArkUI_NodeHandle scroll = nodeAPI->createNode(ARKUI_NODE_SCROLL);
    ArkUI_NodeHandle list = nodeAPI->createNode(ARKUI_NODE_LIST);
    // 设置属性
    SetListAttribute(list);
    SetScrollAttribute(scroll);
    AddListChild(list);
    AddScrollChild(scroll, list);
    OH_NativeXComponent_AttachNativeRootNode(component, scroll);
    auto manager = NativeXComponentSample::Manager::GetInstance();
    if (!manager) {
        return;
    }
    context_ = OH_ArkUI_GetContextByNode(scroll);
}

napi_value Manager::CreateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode napi_get_cb_info failed");
    }

    if (argCnt < 1) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong type of arguments");
        return nullptr;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_int64 failed");
        return nullptr;
    }

    auto manager = Manager::GetInstance();
    if (manager == nullptr) {
        return nullptr;
    }

    OH_NativeXComponent* component = manager->GetNativeXComponent(idStr);
    if (component == nullptr) {
        return nullptr;
    }
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);

    if (nodeAPI != nullptr) {
        if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
            CreateFocusTree(env, args[1], component);
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
    napi_value args[1] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "Wrong type of arguments");
        return nullptr;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "napi_get_value_int64 failed");
        return nullptr;
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "CreateNativeNode %{public}s", idStr);

    auto manager = Manager::GetInstance();
    if (manager == nullptr) {
        return nullptr;
    }

    OH_NativeXComponent* component = manager->GetNativeXComponent(idStr);
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
    napi_value args[1] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetContext napi_get_cb_info failed");
    }

    if (argCnt != 1) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_number) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong type of arguments");
        return nullptr;
    }

    int64_t value;
    if (napi_get_value_int64(env, args[0], &value) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_int64 failed");
        return nullptr;
    }

    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_create_object failed");
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

    OH_NativeXComponent* nativeXComponent = nullptr;
    if (napi_unwrap(env, exportInstance, reinterpret_cast<void**>(&nativeXComponent)) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: napi_unwrap fail");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = { '\0' };
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Export: OH_NativeXComponent_GetXComponentId fail");
        return;
    }

    std::string id(idStr);
    auto manager = Manager::GetInstance();
    if ((manager != nullptr) && (nativeXComponent != nullptr)) {
        manager->SetNativeXComponent(id, nativeXComponent);
    }
}

void Manager::SetNativeXComponent(std::string& id, OH_NativeXComponent* nativeXComponent)
{
    if (nativeXComponent == nullptr) {
        return;
    }

    if (nativeXComponentMap_.find(id) == nativeXComponentMap_.end()) {
        nativeXComponentMap_[id] = nativeXComponent;
        return;
    }

    if (nativeXComponentMap_[id] != nativeXComponent) {
        OH_NativeXComponent* tmp = nativeXComponentMap_[id];
        tmp = nullptr;
        nativeXComponentMap_[id] = nativeXComponent;
    }
}

OH_NativeXComponent* Manager::GetNativeXComponent(const std::string& id)
{
    return nativeXComponentMap_[id];
}

// 焦点相关接口实现
napi_value Manager::RequestFocus(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "RequestFocus env or info is null");
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "RequestFocus napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != 1) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong type of arguments");
        return nullptr;
    }

    char nodeId[256] = { 0 };
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], nodeId, sizeof(nodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_string_utf8 failed");
        return nullptr;
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "接收的nodeId: %s, 长度: %zu", nodeId, length);

    auto focusManager = FocusManager::GetInstance();
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "qqh -> start request");
    int result = focusManager->RequestFocus(nodeId);

    napi_value returnValue;
    napi_create_int32(env, result, &returnValue);
    return returnValue;
}

napi_value Manager::RequestFocusAsync(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "RequestFocus env or info is null");
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "RequestFocus napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != 1) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_typeof failed");
        return nullptr;
    }

    if (valuetype != napi_string) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong type of arguments");
        return nullptr;
    }

    char nodeId[256] = { 0 };
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], nodeId, sizeof(nodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_string_utf8 failed");
        return nullptr;
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "接收的nodeId: %s, 长度: %zu", nodeId, length);

    auto focusManager = FocusManager::GetInstance();
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "qqh -> start request");
    int result = focusManager->RequestFocusAsync(nodeId);

    napi_value returnValue;
    napi_create_int32(env, result, &returnValue);
    return returnValue;
}

napi_value Manager::ClearFocus(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "ClearFocus env or info is null");
        return nullptr;
    }

    auto focusManager = FocusManager::GetInstance();
    focusManager->ClearFocus(context_);

    return nullptr;
}

napi_value Manager::ActivateFocus(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "ActivateFocus env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "ActivateFocus napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != NUMBER_TWO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    bool isActive = false;
    bool isAutoInactive = true;

    napi_get_value_bool(env, args[0], &isActive);
    napi_get_value_bool(env, args[1], &isAutoInactive);

    auto focusManager = FocusManager::GetInstance();
    focusManager->ActivateFocus(context_, isActive, isAutoInactive);

    return nullptr;
}

napi_value Manager::SetAutoTransfer(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetAutoTransfer env or info is null");
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetAutoTransfer napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != 1) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    bool autoTransfer = true;
    napi_get_value_bool(env, args[0], &autoTransfer);

    auto focusManager = FocusManager::GetInstance();
    focusManager->SetAutoTransfer(context_, autoTransfer);

    return nullptr;
}

napi_value Manager::SetKeyProcessingMode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetKeyProcessingMode env or info is null");
        return nullptr;
    }

    size_t argCnt = 1;
    napi_value args[1] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetKeyProcessingMode napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != 1) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    int32_t mode = 0;
    napi_get_value_int32(env, args[0], &mode);

    auto focusManager = FocusManager::GetInstance();
    focusManager->SetKeyProcessingMode(context_, static_cast<FocusKeyProcessingMode>(mode));

    return nullptr;
}

napi_value Manager::SetNodeFocusable(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeFocusable env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeFocusable napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != NUMBER_TWO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    char nodeId[256] = { 0 };
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], nodeId, sizeof(nodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_string_utf8 failed");
        return nullptr;
    }

    bool focusable = false;
    napi_get_value_bool(env, args[1], &focusable);

    auto focusManager = FocusManager::GetInstance();
    int result = focusManager->SetNodeFocusable(nodeId, focusable);

    napi_value returnValue;
    napi_create_int32(env, result, &returnValue);
    return returnValue;
}

napi_value Manager::SetNodeFocusOnTouch(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeFocusOnTouch env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeFocusOnTouch napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != NUMBER_TWO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    char nodeId[256] = { 0 };
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], nodeId, sizeof(nodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_string_utf8 failed");
        return nullptr;
    }

    bool focusable = false;
    napi_get_value_bool(env, args[1], &focusable);

    auto focusManager = FocusManager::GetInstance();
    int result = focusManager->SetFocusOnTouch(nodeId, focusable);

    napi_value returnValue;
    napi_create_int32(env, result, &returnValue);
    return returnValue;
}

napi_value Manager::GetCurrentFocusNodeId(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "GetCurrentFocusNodeId env or info is null");
        return nullptr;
    }

    auto focusManager = FocusManager::GetInstance();
    std::string currentNodeId = focusManager->GetCurrentFocusNodeId();

    napi_value returnValue;
    napi_create_string_utf8(env, currentNodeId.c_str(), currentNodeId.length(), &returnValue);
    return returnValue;
}

napi_value Manager::SetNodeDefaultFocus(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeDefaultFocus env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeDefaultFocus napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != NUMBER_TWO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    char nodeId[256] = { 0 };
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], nodeId, sizeof(nodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_string_utf8 failed");
        return nullptr;
    }

    bool isDefault = false;
    napi_get_value_bool(env, args[1], &isDefault);

    auto focusManager = FocusManager::GetInstance();
    int result = focusManager->SetNodeDefaultFocus(nodeId, isDefault);

    napi_value returnValue;
    napi_create_int32(env, result, &returnValue);
    return returnValue;
}

napi_value Manager::SetNodeFocusBox(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeFocusBox env or info is null");
        return nullptr;
    }

    size_t argCnt = 4;
    napi_value args[4] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeFocusBox napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != NUMBER_FOUR) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    char nodeId[256] = { 0 };
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], nodeId, sizeof(nodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_string_utf8 failed");
        return nullptr;
    }

    double distance = 0.0;
    double width = 0.0;
    uint32_t color = 0;

    napi_get_value_double(env, args[NUMBER_ONE], &distance);
    napi_get_value_double(env, args[NUMBER_TWO], &width);
    napi_get_value_uint32(env, args[NUMBER_THREE], &color);

    auto focusManager = FocusManager::GetInstance();
    int result = focusManager->SetNodeFocusBox(nodeId, static_cast<float>(distance), static_cast<float>(width), color);

    napi_value returnValue;
    napi_create_int32(env, result, &returnValue);
    return returnValue;
}

napi_value Manager::SetNodeNextFocus(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeNextFocus env or info is null");
        return nullptr;
    }

    size_t argCnt = 3;
    napi_value args[3] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeNextFocus napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != NUMBER_THREE) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    char nodeId[256] = { 0 };
    char nextNodeId[256] = { 0 };
    size_t length;

    if (napi_get_value_string_utf8(env, args[0], nodeId, sizeof(nodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_string_utf8 failed for nodeId");
        return nullptr;
    }

    if (napi_get_value_string_utf8(env, args[1], nextNodeId, sizeof(nextNodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager",
            "napi_get_value_string_utf8 failed for nextNodeId");
        return nullptr;
    }

    int32_t direction = 0;
    napi_get_value_int32(env, args[NUMBER_TWO], &direction);

    auto focusManager = FocusManager::GetInstance();
    int result = focusManager->SetNodeNextFocus(nodeId, nextNodeId, direction);

    napi_value returnValue;
    napi_create_int32(env, result, &returnValue);
    return returnValue;
}

napi_value Manager::SetNodeTabStop(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeTabStop env or info is null");
        return nullptr;
    }

    size_t argCnt = 2;
    napi_value args[2] = { nullptr };
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "SetNodeTabStop napi_get_cb_info failed");
        return nullptr;
    }

    if (argCnt != NUMBER_TWO) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "Wrong number of arguments");
        return nullptr;
    }

    char nodeId[256] = { 0 };
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], nodeId, sizeof(nodeId) - 1, &length) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "napi_get_value_string_utf8 failed");
        return nullptr;
    }

    bool tabStop = false;
    napi_get_value_bool(env, args[1], &tabStop);

    auto focusManager = FocusManager::GetInstance();
    int result = focusManager->SetNodeTabStop(nodeId, tabStop);

    napi_value returnValue;
    napi_create_int32(env, result, &returnValue);
    return returnValue;
}

} // namespace NativeXComponentSample
