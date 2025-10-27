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

 /*
  * Description: List组件支持基于断点配置lanes
  * Writer: renxiaowen
  */

#include "list_test.h"

#include <string>

#include "../manager/plugin_manager.h"
#include "column_component.h"
namespace ArkUICApiDemo {
auto CreateNodeWithSize(ArkUI_NativeNodeAPI_1* nodeAPI, ArkUI_NodeHandle node, float width, float height)
{
    ArkUI_NumberValue height_value[] = { { .f32 = height } };
    ArkUI_AttributeItem height_item = { height_value, sizeof(height_value) / sizeof(ArkUI_NumberValue) };
    ArkUI_NumberValue width_value[] = { { .f32 = width } };
    ArkUI_AttributeItem width_item = { width_value, sizeof(width_value) / sizeof(ArkUI_NumberValue) };
    nodeAPI->setAttribute(node, NODE_HEIGHT, &height_item);
    nodeAPI->setAttribute(node, NODE_WIDTH, &width_item);
    return node;
}

napi_value ListTest::CreateNativeNode(napi_env env, napi_callback_info info)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ListTest", "CreateNativeNode");

    size_t argc = 1;
    napi_value args[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    size_t length = 64;
    size_t strLength = 0;
    char xComponentID[64] = { 0 };
    napi_get_value_string_utf8(env, args[0], xComponentID, length, &strLength);

    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ListTest", "GetContext env or info is null");
        return nullptr;
    }

    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);

    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto list = CreateNodeWithSize(nodeAPI, nodeAPI->createNode(ARKUI_NODE_LIST), 400, 500);
    nodeAPI->addChild(column, list);
    for (auto i = 0; i < PARAM_20; i++) {
        auto listItem = CreateNodeWithSize(nodeAPI, nodeAPI->createNode(ARKUI_NODE_LIST_ITEM), 100, 100);
        auto text = CreateNodeWithSize(nodeAPI, nodeAPI->createNode(ARKUI_NODE_TEXT), 100, 100);
        ArkUI_AttributeItem content_item = {};
        content_item.string = std::to_string(i).c_str();
        nodeAPI->setAttribute(text, NODE_TEXT_CONTENT, &content_item);

        ArkUI_NumberValue text_align_value[] = { { .i32 = ARKUI_TEXT_ALIGNMENT_CENTER } };
        ArkUI_AttributeItem text_align_item = { text_align_value,
            sizeof(text_align_value) / sizeof(ArkUI_NumberValue) };
        nodeAPI->setAttribute(text, NODE_TEXT_ALIGN, &text_align_item);
        ArkUI_NumberValue color_value1[] = { { .u32 = 0xFF00FF00 } };
        ArkUI_AttributeItem color_item1 = { color_value1, sizeof(color_value1) / sizeof(ArkUI_NumberValue) };
        nodeAPI->setAttribute(listItem, NODE_BACKGROUND_COLOR, &color_item1);
        nodeAPI->addChild(listItem, text);
        nodeAPI->addChild(list, listItem);
    }

    ArkUI_NumberValue height_value[] = { { .i32 = 2 }, { .f32 = 50 } };
    ArkUI_AttributeItem height_item = { height_value, sizeof(height_value) / sizeof(ArkUI_NumberValue) };

    auto a = nodeAPI->setAttribute(list, NODE_LIST_LANES_ITEMFILLPOLICY, &height_item);
    auto b = nodeAPI->getAttribute(list, NODE_LIST_LANES_ITEMFILLPOLICY)->value->i32;
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ListTest", "laoxu a:%{public}d", a);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "ListTest", "laoxu b:%{public}d", b);

    auto text1 = CreateNodeWithSize(nodeAPI, nodeAPI->createNode(ARKUI_NODE_TEXT), 50, 50);
    ArkUI_AttributeItem content_item1 = {};
    content_item1.string = std::to_string(b).c_str();
    nodeAPI->setAttribute(text1, NODE_TEXT_CONTENT, &content_item1);
    nodeAPI->addChild(column, text1);

    // 所有组件挂载到XComponent
    std::string id(xComponentID);

    if (OH_NativeXComponent_AttachNativeRootNode(PluginManager::GetInstance()->GetNativeXComponent(id), column) ==
        INVALID_PARAM) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "CalendarPickerMinMaxDateTest",
            "OH_NativeXComponent_AttachNativeRootNode failed");
    }

    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }

    return exports;
}
} // namespace ArkUICApiDemo