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
 * Description: List支持展开指定ListItem的swipeAction
 * Writer: renxiaowen
 */

#include "swipe_action_test.h"

#include <arkui/native_interface.h>
#include <memory>

#include "components/button/Button.h"
#include "components/column/Column.h"
#include "components/list/List1.h"
#include "components/row/Row.h"
#include "components/text/Text.h"
#include "manager/plugin_manager.h"

/*
 * 测试总结：调用OH_ArkUI_List_CloseAllSwipeActions关闭所有列表项的滑动操作，调用OH_ArkUI_ListItemSwipeAction_Expand
 * 展开列表项，调用OH_ArkUI_ListItemSwipeAction_Collapse关闭列表项
 * 预期结果：列表项展开，列表项关闭
 */

namespace ArkUICApiDemo {

constexpr int32_t LIST_ITEM_COUNT = 10;
constexpr int32_t LIST_ITEM_GROUP_COUNT = 6;

int32_t SwipeActionTest::direction = 0;
int32_t SwipeActionTest::listIndex = 0;
int32_t SwipeActionTest::listGroupIndex = -1;

static void SetAction(std::shared_ptr<ListItemComponent> listItem,
    ArkUI_ListItemSwipeEdgeEffect setEdgeEffect =
        ArkUI_ListItemSwipeEdgeEffect::ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING)
{
    auto option = new ListItemSwipeActionOption();
    auto col1 = std::make_shared<ColumnComponent>();
    col1->SetWidth(SIZE_50);
    col1->SetHeight(SIZE_50);
    col1->SetBackgroundColor(COLOR_GREEN);
    auto col2 = std::make_shared<ColumnComponent>();
    col2->SetWidth(SIZE_50);
    col2->SetHeight(SIZE_50);
    col2->SetBackgroundColor(COLOR_YELLOW);

    auto item1 = OH_ArkUI_ListItemSwipeActionItem_Create();
    auto item2 = OH_ArkUI_ListItemSwipeActionItem_Create();

    OH_ArkUI_ListItemSwipeActionItem_SetContent(item1, col1->GetComponent());
    OH_ArkUI_ListItemSwipeActionItem_SetContent(item2, col2->GetComponent());
    option->SetStart(item1);
    option->SetEnd(item2);
    option->SetEdgeEffect(setEdgeEffect);
    listItem->SetListItemSwiperAction(option);
}

static std::shared_ptr<RowComponent> CreateButton(std::vector<std::shared_ptr<ListComponent>> list)
{
    auto row = std::make_shared<RowComponent>();
    for (int i = 0; i < list.size(); i++) {
        auto eachList = list[i];
        auto button1 = std::make_shared<ButtonComponent>();
        button1->SetWidth(SIZE_50);
        button1->SetHeight(SIZE_50);
        button1->SetId("callbackButton" + std::to_string(i + 1));
        button1->SetBackgroundColor(COLOR_TRANSPARENT);
        button1->RegisterOnClick([eachList]() {
            void* userData = reinterpret_cast<void*>(eachList.get());
            // 测试：点击按钮，调用OH_ArkUI_List_CloseAllSwipeActions关闭所有列表项的滑动操作
            OH_ArkUI_List_CloseAllSwipeActions(eachList->GetComponent(), userData, [](void* userData) {
                auto list = reinterpret_cast<ListComponent*>(userData);
                list->SetBackgroundColor(COLOR_RED);
            });
        });
        auto button2 = std::make_shared<ButtonComponent>();
        button2->SetWidth(SIZE_50);
        button2->SetHeight(SIZE_50);
        button2->SetId("nullCallbackButton" + std::to_string(i + 1));
        button2->SetBackgroundColor(COLOR_TRANSPARENT);
        button2->RegisterOnClick(
            [eachList]() { OH_ArkUI_List_CloseAllSwipeActions(eachList->GetComponent(), nullptr, nullptr); });
        row->AddChild(button1);
        row->AddChild(button2);
    }
    return row;
}

static std::shared_ptr<TextComponent> CreateText(std::string str)
{
    auto text = std::make_shared<TextComponent>();
    text->SetTextContent(str);
    return text;
}

static std::shared_ptr<ListComponent> CreateListWithAction(int32_t listItemCount, int32_t listItemGroupCount,
    int32_t listItemCountInGroup, int32_t vertical, std::string firstItemId)
{
    auto list = std::make_shared<ListComponent>();
    constexpr int32_t width = 150;
    list->SetMargin(PARAM_10);
    list->SetWidth(width);
    list->SetHeight(SIZE_400);
    list->SetListDirection(vertical);
    list->SetListDivider(COLOR_BLACK, PARAM_2, PARAM_0, PARAM_0);
    for (int i = 0; i < listItemCount; i++) {
        auto listItem = std::make_shared<ListItemComponent>();
        if (i == 0) {
            listItem->SetId(firstItemId);
        }
        listItem->SetWidth(width);
        listItem->SetHeight(SIZE_100);
        listItem->SetBackgroundColor(COLOR_BLUE);
        SetAction(listItem);
        listItem->AddChild(CreateText("listItem " + std::to_string(i)));
        list->AddChild(listItem);
    }
    for (int i = 0; i < listItemGroupCount; i++) {
        auto listItemGroup = std::make_shared<ListItemGroupComponent>();
        for (int j = 0; j < listItemCountInGroup; j++) {
            auto listItem = std::make_shared<ListItemComponent>();
            listItem->SetWidth(width);
            listItem->SetHeight(SIZE_100);
            listItem->SetBackgroundColor(COLOR_RED);
            SetAction(listItem);
            listItem->AddChild(CreateText("listItemGroup" + std::to_string(i) + "组" + std::to_string(j)));
            listItemGroup->AddChild(listItem);
        }
        list->AddChild(listItemGroup);
    }
    return list;
}

ArkUI_NodeHandle findListItem(std::shared_ptr<ListComponent> list)
{
    ArkUI_NativeNodeAPI_1* nativeNodeApi = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nativeNodeApi);
    bool hasGroup = SwipeActionTest::listGroupIndex >= 0;
    int32_t targetIndex = SwipeActionTest::listIndex + (hasGroup ? LIST_ITEM_COUNT : 0);
    auto node = nativeNodeApi->getChildAt(list->GetComponent(), targetIndex);
    if (hasGroup) {
        node = nativeNodeApi->getChildAt(node, SwipeActionTest::listGroupIndex);
    }
    return node;
}

void Expand(ArkUI_NodeHandle node, int32_t direction)
{
    // 测试：调用OH_ArkUI_ListItemSwipeAction_Expand展开列表项
    int32_t ret = OH_ArkUI_ListItemSwipeAction_Expand(node, static_cast<ArkUI_ListItemSwipeActionDirection>(direction));
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Expand", "CXN expand ret = %{public}d, direction = %{public}d",
        ret, direction);
}

void Collapse(ArkUI_NodeHandle node)
{
    // 测试：调用OH_ArkUI_ListItemSwipeAction_Collapse收起列表项
    int32_t ret = OH_ArkUI_ListItemSwipeAction_Collapse(node);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Expand", "CXN Collapse ret = %{public}d", ret);
}

static std::shared_ptr<ColumnComponent> CreateSwipeActionController(std::shared_ptr<ListComponent> list)
{
    auto column = std::make_shared<ColumnComponent>();
    auto directionBtn = std::make_shared<ButtonComponent>();
    auto listIndexBtn = std::make_shared<ButtonComponent>();
    auto listGroupIndexBtn = std::make_shared<ButtonComponent>();
    auto resetGroupIndexBtn = std::make_shared<ButtonComponent>();
    auto expandListBtn = std::make_shared<ButtonComponent>();
    auto expandGroupBtn = std::make_shared<ButtonComponent>();
    auto collapseListBtn = std::make_shared<ButtonComponent>();
    auto collapseGroupBtn = std::make_shared<ButtonComponent>();
    directionBtn->SetLabel("direction " + std::to_string(SwipeActionTest::direction));
    listIndexBtn->SetLabel("listIndex " + std::to_string(SwipeActionTest::listIndex));
    resetGroupIndexBtn->SetLabel("resetGroupIndex");
    listGroupIndexBtn->SetLabel("listGroupIndex " + std::to_string(SwipeActionTest::listGroupIndex));
    expandListBtn->SetLabel("expandList");
    expandGroupBtn->SetLabel("expandGroup");
    collapseListBtn->SetLabel("collapseList");
    collapseGroupBtn->SetLabel("collapseGroup");
    column->AddChild(directionBtn);
    column->AddChild(listIndexBtn);
    column->AddChild(resetGroupIndexBtn);
    column->AddChild(listGroupIndexBtn);
    column->AddChild(expandListBtn);
    column->AddChild(collapseListBtn);
    directionBtn->RegisterOnClick([directionBtn]() {
        SwipeActionTest::direction = (SwipeActionTest::direction + 1) % PARAM_4; // Cycle through 0-3
        directionBtn->SetLabel("direction " + std::to_string(SwipeActionTest::direction));
    });
    listIndexBtn->RegisterOnClick([listIndexBtn]() {
        SwipeActionTest::listIndex = (SwipeActionTest::listIndex + 1) % LIST_ITEM_COUNT;
        listIndexBtn->SetLabel("listIndex " + std::to_string(SwipeActionTest::listIndex));
    });
    resetGroupIndexBtn->RegisterOnClick([listGroupIndexBtn]() {
        SwipeActionTest::listGroupIndex = -1;
        listGroupIndexBtn->SetLabel("listGroupIndex " + std::to_string(SwipeActionTest::listGroupIndex));
    });
    listGroupIndexBtn->RegisterOnClick([listGroupIndexBtn]() {
        SwipeActionTest::listGroupIndex++;
        if (SwipeActionTest::listGroupIndex >= LIST_ITEM_GROUP_COUNT) {
            SwipeActionTest::listGroupIndex = -1;
        }
        listGroupIndexBtn->SetLabel("listGroupIndex " + std::to_string(SwipeActionTest::listGroupIndex));
    });
    expandListBtn->RegisterOnClick([list]() { Expand(findListItem(list), SwipeActionTest::direction); });
    collapseListBtn->RegisterOnClick([list]() { Collapse(findListItem(list)); });
    return column;
}

napi_value SwipeActionTest::CreateNativeNode(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    size_t length = PARAM_64;
    size_t strLength = 0;
    char xComponentID[PARAM_64] = { 0 };
    napi_get_value_string_utf8(env, args[0], xComponentID, length, &strLength);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SwipeActionTest", "%{public}s", xComponentID);

    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SwipeActionTest", "GetContext env or info is null");
        return nullptr;
    }
    auto rootRow = new RowComponent();
    auto list =
        CreateListWithAction(LIST_ITEM_COUNT, LIST_ITEM_GROUP_COUNT, 6, ArkUI_Axis::ARKUI_AXIS_VERTICAL, "list1");
    rootRow->AddChild(list);
    rootRow->AddChild(CreateSwipeActionController(list));
    std::string id(xComponentID);
    if (OH_NativeXComponent_AttachNativeRootNode(
        PluginManager::GetInstance()->GetNativeXComponent(id),
        rootRow->GetComponent()) == INVALID_PARAM) {
    OH_LOG_Print(
        LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "SwipeActionTest", "OH_NativeXComponent_AttachNativeRootNode failed");
    }
    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }
    return exports;
}
} // namespace ArkUICApiDemo