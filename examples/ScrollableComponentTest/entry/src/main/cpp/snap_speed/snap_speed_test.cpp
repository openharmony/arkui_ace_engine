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

/*
 * Description: List组件限位滚动支持设置动画速度档位
 * Writer: renxiaowen
 */

#include "snap_speed/snap_speed_test.h"

#include <arkui/native_interface.h>
#include <memory>

#include "common.h"
#include "components/button/Button.h"
#include "components/column/Column.h"
#include "components/list/List1.h"
#include "components/row/Row.h"
#include "components/text/Text.h"
#include "manager/plugin_manager.h"

namespace ArkUICApiDemo {

constexpr int32_t LIST_ITEM_COUNT = 60;
constexpr int32_t LIST_ITEM_GROUP_COUNT = 6;

int32_t ConvertSnapSpeed(const std::string& label)
{
    if (label == "-1") {
        return -1;
    } else if (label == "NORMAL") {
        return ArkUI_ScrollSnapAnimationSpeed::ARKUI_SCROLL_SNAP_ANIMATION_NORMAL;
    } else if (label == "SLOW") {
        return ArkUI_ScrollSnapAnimationSpeed::ARKUI_SCROLL_SNAP_ANIMATION_SLOW;
    } else if (label == "2") {
        return PARAM_2;
    } else {
        return PARAM_3;
    }
}

std::shared_ptr<ButtonComponent> CreateButton(
    const std::string& label, const std::shared_ptr<ListComponent>& list, const std::shared_ptr<TextComponent>& text)
{
    auto button = std::make_shared<ButtonComponent>();
    button->SetLabel(label);
    button->RegisterOnClick([list, label, text]() {
        if (label == "reset") {
            list->resetAttribute(NODE_LIST_SCROLL_SNAP_ANIMATION_SPEED);
        } else {
            int32_t speed = ConvertSnapSpeed(label);
            list->SetScrollSnapAnimationSpeed(speed);
        }
        text->SetTextContent(std::to_string(list->getAttribute(NODE_LIST_SCROLL_SNAP_ANIMATION_SPEED)->value[0].i32));
    });
    return button;
}

template<int32_t size = LIST_ITEM_COUNT, int32_t direction = ArkUI_Axis::ARKUI_AXIS_VERTICAL>
static std::shared_ptr<ListComponent> CreateList()
{
    auto list = std::make_shared<ListComponent>();
    list->SetListDirection(direction);
    list->SetBorderWidth(PARAM_1);
    list->SetBorderColor(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
    list->SetWidth(SIZE_100);
    list->SetHeight(SIZE_300);
    int32_t alignCenter = ArkUI_ScrollSnapAlign::ARKUI_SCROLL_SNAP_ALIGN_CENTER;
    list->SetScrollSnapAlign(alignCenter);
    std::vector<std::shared_ptr<Component>> input;
    for (int i = 0; i < size; i++) {
        auto column = std::make_shared<ColumnComponent>();
        column->SetWidth(SIZE_100);
        column->SetHeight(SIZE_50);
        // 调试时应开启这段代码显示编号
        auto text = std::make_shared<TextComponent>();
        text->SetAlign(ARKUI_ALIGNMENT_CENTER);
        text->SetTextContent("Text" + std::to_string(i));
        column->AddChild(text);
        column->SetBackgroundColor(COLOR_LIGHT_BLUE);
        column->SetBorderWidth(PARAM_2);
        column->SetBorderColor(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
        input.push_back(column);
    }
    auto adapter = make_shared<ItemAdapter<ListItemComponent>>(input);
    list->SetLazyAdapter(adapter);
    auto childrenMainSize = new ListChildrenMainSizeOption();
    childrenMainSize->Resize(size);
    childrenMainSize->SetDefaultMainSize(SIZE_50);
    return list;
}

template<int32_t size = LIST_ITEM_COUNT, int32_t direction = ArkUI_Axis::ARKUI_AXIS_VERTICAL>
static std::shared_ptr<ListComponent> CreateListNoLazyForeachs()
{
    auto list = std::make_shared<ListComponent>();
    list->SetListDirection(direction);
    list->SetBorderWidth(PARAM_1);
    list->SetBorderColor(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
    list->SetWidth(SIZE_100);
    list->SetHeight(SIZE_300);
    int32_t align = ArkUI_ScrollSnapAlign::ARKUI_SCROLL_SNAP_ALIGN_CENTER;
    list->SetScrollSnapAlign(align);
    for (int i = 0; i < size; i++) {
        auto column = std::make_shared<ColumnComponent>();
        column->SetWidth(SIZE_100);
        column->SetHeight(SIZE_50);
        // 调试时应开启这段代码显示编号
        auto text = std::make_shared<TextComponent>();
        text->SetAlign(ARKUI_ALIGNMENT_CENTER);
        text->SetTextContent("Text" + std::to_string(i));
        column->AddChild(text);
        column->SetBackgroundColor(COLOR_LIGHT_BLUE);
        column->SetBorderWidth(PARAM_2);
        column->SetBorderColor(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
        list->AddChild(column);
    }
    auto childrenMainSize = new ListChildrenMainSizeOption();
    childrenMainSize->Resize(size);
    childrenMainSize->SetDefaultMainSize(SIZE_50);
    return list;
}

napi_value SnapSpeedTest::CreateNativeNode(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    size_t length = PARAM_64;
    size_t strLength = 0;
    char xComponentID[PARAM_64] = { 0 };
    napi_get_value_string_utf8(env, args[0], xComponentID, length, &strLength);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SnapSpeedTest", "%{public}s", xComponentID);

    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SnapSpeedTest", "GetContext env or info is null");
        return nullptr;
    }
    auto row = std::make_shared<RowComponent>();
    auto list = CreateList<LIST_ITEM_COUNT>();
    auto btnCol = std::make_shared<ColumnComponent>();
    auto btnCol1 = std::make_shared<ColumnComponent>();
    auto text = std::make_shared<TextComponent>();
    btnCol->AddChild(text);
    btnCol->AddChild(CreateButton("NORMAL", list, text));
    btnCol->AddChild(CreateButton("SLOW", list, text));
    btnCol->AddChild(CreateButton("-1", list, text));
    btnCol->AddChild(CreateButton("2", list, text));
    btnCol->AddChild(CreateButton("reset", list, text));
    row->AddChild(list);
    row->AddChild(btnCol);
    auto rootColumn = new ColumnComponent();
    rootColumn->AddChild(row);

    std::string id(xComponentID);
    if (OH_NativeXComponent_AttachNativeRootNode(
        PluginManager::GetInstance()->GetNativeXComponent(id),
        rootColumn->GetComponent == INVALID_PARAM)) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SnapSpeedTest", "OH_NativeXComponent_AttachNativeRootNode failed");
    }
    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }
    return exports;
}

napi_value SnapSpeedTest::CreateNativeNodeNoLazyForeach(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    size_t length = PARAM_64;
    size_t strLength = 0;
    char xComponentID[PARAM_64] = { 0 };
    napi_get_value_string_utf8(env, args[0], xComponentID, length, &strLength);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SnapSpeedTest", "%{public}s", xComponentID);

    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SnapSpeedTest", "GetContext env or info is null");
        return nullptr;
    }
    auto row = std::make_shared<RowComponent>();
    auto list = CreateListNoLazyForeachs<LIST_ITEM_COUNT>();
    auto btnCol = std::make_shared<ColumnComponent>();
    auto btnCol1 = std::make_shared<ColumnComponent>();
    auto text = std::make_shared<TextComponent>();
    btnCol->AddChild(text);
    btnCol->AddChild(CreateButton("NORMAL", list, text));
    btnCol->AddChild(CreateButton("SLOW", list, text));
    btnCol->AddChild(CreateButton("-1", list, text));
    btnCol->AddChild(CreateButton("2", list, text));
    btnCol->AddChild(CreateButton("reset", list, text));
    row->AddChild(list);
    row->AddChild(btnCol);
    auto rootColumn = new ColumnComponent();
    rootColumn->AddChild(row);

    std::string id(xComponentID);
    if (OH_NativeXComponent_AttachNativeRootNode(
        PluginManager::GetInstance()->GetNativeXComponent(id),
        rootColumn->GetComponent == INVALID_PARAM)) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SnapSpeedTest", "OH_NativeXComponent_AttachNativeRootNode failed");
    }
    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }
    return exports;
}
} // namespace ArkUICApiDemo