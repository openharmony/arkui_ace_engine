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
 * Description: Grid组件高频接口CAPI补齐
 * Writer: renxiaowen
 */

#include "grid_test.h"

#include <cstdint>
#include <napi/native_api.h>
#include <string>
#include <sys/types.h>
#include <vector>

#include "common.h"
#include "components/button/Button.h"
#include "components/grid/Grid1.h"
#include "components/row/Row.h"
#include "components/scroll/Scroll1.h"
#include "components/text/Text.h"
#include "manager/plugin_manager.h"

/*
 * 测试总结：测试grid组件的属性设置和获取，包括：edgeEffect、scrollSize、scrollMode、scrollColor、rowGap、enableScroll、
 * alignItems、flingSpeedLimit、friction、clip、fadingEdge、nestedMode、itemStyle、backToTop。
 * 预期结果：设置和获取的属性值正确，并且能够正常显示。
 */

namespace ArkUICApiDemo {
constexpr int32_t GRID_ITEM_COUNT = 100;
constexpr int32_t GRID_ITEM_COUNT_80 = 80;
// 设置边缘回弹效果
std::vector<int32_t> effectPool = { ARKUI_EDGE_EFFECT_SPRING, ARKUI_EDGE_EFFECT_FADE, ARKUI_EDGE_EFFECT_NONE };
std::vector<float> scrollSizePool = { 0.0f, 20.0f, -10.0f, 30.0f };
// scrollbar显示效果库
std::vector<int32_t> scrollModePool = { ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO, ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF,
    ARKUI_SCROLL_BAR_DISPLAY_MODE_ON, -1 };
// scrollColor颜色库
std::vector<uint32_t> scrollColorPool = { COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW, 1 };
// rowGap库
std::vector<float> rowGapPool = { 0.0f, 20.0f, -10.0f, 30.0f };
// enableScroll设置库
std::vector<int32_t> enableScrollPool = { 0, 1, 0, -1, -2 };
// alignItem属性设置库
std::vector<int32_t> alignItemsPool = { GRID_ITEM_ALIGNMENT_DEFAULT, GRID_ITEM_ALIGNMENT_STRETCH, napi_undefined,
    napi_null, 2, -1 };
// flingSpeedLimit属性设置库
std::vector<float> flingSpeedLimitPool = { 10000.0f, 9000.0f, 20.0f, -1.0f, 300.0f, 0.0f, 1.0f, -2.0f };
// friction属性设置库
std::vector<float> frictionPool = { 0.6f, 0.1f, 0.8f, -1.0f };
// clip属性设置库
std::vector<int32_t> clipModePool = { ARKUI_CONTENT_CLIP_MODE_CONTENT_ONLY, ARKUI_CONTENT_CLIP_MODE_BOUNDARY,
    ARKUI_CONTENT_CLIP_MODE_SAFE_AREA, -1 };
// fadingEdge设置库
std::vector<float> fadingEdgePool = { 10.0f, 30.0f, 40.0f, 400.0f, -1.0f };
// nestedMode设置
std::vector<int32_t> nestedModePool = { ARKUI_SCROLL_NESTED_MODE_SELF_ONLY, ARKUI_SCROLL_NESTED_MODE_SELF_FIRST,
    ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST, ARKUI_SCROLL_NESTED_MODE_PARALLEL, -1, 4 };
// itemStyle设置
std::vector<int32_t> itemStylePool = { GRID_ITEM_STYLE_NONE, GRID_ITEM_STYLE_PLAIN, -1, 3 };
// backToTop设置
std::vector<int32_t> backToTopPool = { true, false, -1, 3 };
int32_t GridTest::edgeEffectIndex_ = 0;
int32_t GridTest::modeIndex_ = 0;
int32_t GridTest::widthIndex_ = 0;
int32_t GridTest::colorIndex_ = 0;
int32_t GridTest::rowGapIndex_ = 0;
int32_t GridTest::enableScrollIndex_ = 0;
int32_t GridTest::alignItemsIndex_ = 0;
int32_t GridTest::flingSpeedLimitIndex_ = 0;
int32_t GridTest::frictionIndex_ = 0;
int32_t GridTest::clipModeIndex_ = 0;
int32_t GridTest::fadingEdgeIndex_ = 0;
int32_t GridTest::nestedModeIndex_ = 0;
int32_t GridTest::itemStyleIndex_ = 0;
int32_t GridTest::backToTopIndex_ = 0;

std::shared_ptr<GridComponent> GridTest::CreatGrid(int32_t type)
{
    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);

    auto grid = std::make_shared<GridComponent>();
    grid->SetWidth(SIZE_450);
    grid->SetHeight(SIZE_300);
    // 设置columnsTemplate:NODE_GRID_COLUMN_TEMPLATE;
    grid->SetGridColumnsTemplate("1fr 1fr 1fr 1fr");
    // 设置columnsGap:NODE_GRID_COLUMN_GAP
    grid->SetGridColumnsGap(SIZE_10);
    // 设置rowGap:NODE_GRID_ROW_GAP
    grid->SetGridRowsGap(SIZE_5);
    grid->SetBorderWidth(SIZE_5);
    grid->SetMargin(SIZE_5);

    if (type == 1) {
        ArkUI_NumberValue value[] = { { .i32 = 1 } };
        ArkUI_AttributeItem item = { value, 1 };
        nodeAPI->setAttribute(grid->GetComponent(), NODE_GRID_FOCUS_WRAP_MODE, &item);
    }

    std::string message = "这是一段文字";
    std::string showMessage;
    for (int i = 0; i < GRID_ITEM_COUNT; i++) {
        auto gridItem = new Component(ARKUI_NODE_GRID_ITEM);
        auto text = new TextComponent();
        gridItem->SetBackgroundColor(COLOR_YELLOW);
        gridItem->SetBorderWidth(PARAM_3);
        gridItem->SetBorderColor(COLOR_GRAY, COLOR_GRAY, COLOR_GRAY, COLOR_GRAY);
        showMessage += message;
        text->SetTextContent(showMessage);

        ArkUI_NumberValue focusable_value[] = { { .i32 = 1 } };
        ArkUI_AttributeItem focusable_item = { focusable_value, sizeof(focusable_value) / sizeof(ArkUI_NumberValue) };
        nodeAPI->setAttribute(text->GetComponent(), NODE_FOCUSABLE, &focusable_item);

        nodeAPI->addChild(gridItem->GetComponent(), text->GetComponent());
        nodeAPI->addChild(grid->GetComponent(), gridItem->GetComponent());
    }
    return grid;
}

// 用来测试clipMode
std::shared_ptr<GridComponent> GridTest::CreatGrid1(int32_t type)
{
    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);

    auto grid = std::make_shared<GridComponent>();
    grid->SetWidth(SIZE_300);
    grid->SetHeight(SIZE_300);
    grid->SetMargin(PARAM_20, PARAM_0, PARAM_0, PARAM_0);
    grid->SetPadding(PARAM_10, PARAM_10, PARAM_10, PARAM_10);
    grid->SetBackgroundColor(COLOR_BLUE);
    std::string message = "A";
    for (int i = 0; i < PARAM_13; i++) {
        auto gridItem = new Component(ARKUI_NODE_GRID_ITEM);
        auto text = new TextComponent();
        gridItem->SetBackgroundColor(COLOR_YELLOW);
        gridItem->SetBorderWidth(PARAM_3);
        gridItem->SetBorderColor(COLOR_GRAY, COLOR_GRAY, COLOR_GRAY, COLOR_GRAY);
        text->SetTextContent(message);
        text->SetWidth(SIZE_300);
        text->SetHeight(SIZE_80);
        text->SetTextAlign(ARKUI_TEXT_ALIGNMENT_CENTER);
        text->SetBackgroundColor(COLOR_GRAY);

        nodeAPI->addChild(gridItem->GetComponent(), text->GetComponent());
        nodeAPI->addChild(grid->GetComponent(), gridItem->GetComponent());
    }
    return grid;
}

// 测试 OH_ArkUI_GridLayoutOptions_SetIrregularIndexes 及
// OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback
std::shared_ptr<GridComponent> GridTest::CreatGrid2(int32_t type)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridTest", "CreatGrid2");
    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto grid = std::make_shared<GridComponent>();
    grid->SetWidth(SIZE_450);
    grid->SetHeight(SIZE_300);
    // 设置columnsTemplate:NODE_GRID_COLUMN_TEMPLATE;
    grid->SetGridColumnsTemplate("1fr 1fr 1fr 1fr 1fr");
    // 设置columnsGap:NODE_GRID_COLUMN_GAP
    grid->SetGridColumnsGap(SIZE_10);
    grid->SetGridRowsGap(PARAM_10);
    grid->SetBorderWidth(SIZE_5);
    grid->SetMargin(SIZE_5);
    if (type == 1) {
        ArkUI_NumberValue value[] = { { .i32 = 1 } };
        ArkUI_AttributeItem item = { value, 1 };
        nodeAPI->setAttribute(grid->GetComponent(), NODE_GRID_FOCUS_WRAP_MODE, &item);
    }
    for (int i = 0; i < GRID_ITEM_COUNT; i++) {
        auto gridItem = new Component(ARKUI_NODE_GRID_ITEM);
        auto text = new TextComponent();
        gridItem->SetBackgroundColor(COLOR_YELLOW);
        gridItem->SetBorderWidth(PARAM_3);
        gridItem->SetBorderColor(COLOR_GRAY, COLOR_GRAY, COLOR_GRAY, COLOR_GRAY);
        gridItem->SetWidth(SIZE_50);
        gridItem->SetHeight(SIZE_50);
        text->SetTextContent("A");

        nodeAPI->addChild(gridItem->GetComponent(), text->GetComponent());
        nodeAPI->addChild(grid->GetComponent(), gridItem->GetComponent());
    }
    auto option = OH_ArkUI_GridLayoutOptions_Create();
    uint32_t irregularIndexes[] = { 0, 7 };
    auto ret = OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option, irregularIndexes, 2);
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridTest", "CreatGrid2 ret:%{public}d", ret);
    std::string* str = new std::string("CreatGrid2");
    void* userData = static_cast<void*>(str);
    OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
        option, userData, [](int32_t itemIndex, void* userData) -> ArkUI_GridItemSize {
            if (userData) {
                std::string* str = static_cast<std::string*>(userData);
                OH_LOG_Print(
                    LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridTest", "CreatGrid2 userData:%{public}s", str->c_str());
            }
            if (itemIndex == 0) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridTest", "*** CreatGrid2 itemIndex == 0");
                return { 1, 2 };
            }
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridTest", "*** CreatGrid2 itemIndex != 0");
            return { 1, 4 };
        });
    grid->SetGridLayoutOptions(option);
    return grid;
}

// 测试 OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback
std::shared_ptr<GridComponent> GridTest::CreatGrid3(int32_t type)
{
    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);

    auto grid = std::make_shared<GridComponent>();
    grid->SetWidth(SIZE_300);
    grid->SetHeight(SIZE_300);
    grid->SetGridColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    grid->SetGridRowsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    grid->SetGridColumnsGap(SIZE_10);
    grid->SetGridRowsGap(SIZE_10);
    grid->SetBorderWidth(SIZE_5);
    grid->SetMargin(SIZE_5);
    if (type == 1) {
        ArkUI_NumberValue value[] = { { .i32 = 1 } };
        ArkUI_AttributeItem item = { value, 1 };
        nodeAPI->setAttribute(grid->GetComponent(), NODE_GRID_FOCUS_WRAP_MODE, &item);
    }

    for (int i = 0; i < PARAM_6; i++) {
        auto gridItem = new Component(ARKUI_NODE_GRID_ITEM);
        auto text = new TextComponent();
        gridItem->SetBackgroundColor(COLOR_YELLOW);
        gridItem->SetBorderWidth(PARAM_3);
        gridItem->SetBorderColor(COLOR_GRAY, COLOR_GRAY, COLOR_GRAY, COLOR_GRAY);
        gridItem->SetWidth(SIZE_50);
        gridItem->SetHeight(SIZE_50);
        gridItem->SetFontSize(SIZE_10);
        ArkUI_NumberValue value_number[] = { { .i32 = GRID_ITEM_STYLE_PLAIN } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        gridItem->setAttribute(NODE_GRID_ITEM_STYLE, &attribute_item);

        auto itemStyle = gridItem->getAttribute(NODE_GRID_ITEM_STYLE)->value->i32;
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "itemStyle:%{public}d", itemStyle);

        text->SetTextContent("A");

        nodeAPI->addChild(gridItem->GetComponent(), text->GetComponent());
        nodeAPI->addChild(grid->GetComponent(), gridItem->GetComponent());
    }

    auto option = OH_ArkUI_GridLayoutOptions_Create();
    std::string* str = new std::string("CreatGrid3");
    void* userDataWorld = static_cast<void*>(str);
    OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
        option, userDataWorld, [](int32_t itemIndex, void* userData) -> ArkUI_GridItemRect {
            if (userData) {
                std::string* str = static_cast<std::string*>(userData);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "CreatGrid3 grid userData:%{public}s",
                    str->c_str());
            }
            if (itemIndex == PARAM_0) {
                return ArkUI_GridItemRect { 0, 0, 1, 1 };
            } else if (itemIndex == PARAM_1) {
                return ArkUI_GridItemRect { 0, 1, 2, 2 };
            } else if (itemIndex == PARAM_2) {
                return ArkUI_GridItemRect { 0, 3, 3, 3 };
            } else if (itemIndex == PARAM_3) {
                return ArkUI_GridItemRect { 3, 0, 3, 3 };
            } else if (itemIndex == PARAM_4) {
                return ArkUI_GridItemRect { 4, 3, 2, 2 };
            } else {
                return ArkUI_GridItemRect { 5, 5, 1, 1 };
            }
        });
    grid->SetGridLayoutOptions(option);
    OH_ArkUI_GridLayoutOptions_Dispose(option);
    return grid;
}

// 测试未设置 OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback时
// OH_ArkUI_GridLayoutOptions_GetIrregularIndexes返回值
std::shared_ptr<GridComponent> GridTest::CreatGrid4(int32_t type)
{
    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);

    auto grid = std::make_shared<GridComponent>();
    grid->SetWidth(SIZE_300);
    grid->SetHeight(SIZE_300);
    grid->SetGridColumnsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    grid->SetGridRowsTemplate("1fr 1fr 1fr 1fr 1fr 1fr");
    grid->SetGridColumnsGap(SIZE_10);
    grid->SetGridRowsGap(SIZE_10);
    grid->SetBorderWidth(SIZE_5);
    grid->SetMargin(SIZE_5);
    if (type == 1) {
        ArkUI_NumberValue value[] = { { .i32 = 1 } };
        ArkUI_AttributeItem item = { value, 1 };
        nodeAPI->setAttribute(grid->GetComponent(), NODE_GRID_FOCUS_WRAP_MODE, &item);
    }

    for (int i = 0; i < PARAM_6; i++) {
        auto gridItem = new Component(ARKUI_NODE_GRID_ITEM);
        auto text = new TextComponent();
        gridItem->SetBackgroundColor(COLOR_YELLOW);

        gridItem->SetBorderColor(COLOR_GRAY, COLOR_GRAY, COLOR_GRAY, COLOR_GRAY);
        gridItem->SetWidth(SIZE_50);
        gridItem->SetHeight(SIZE_50);
        gridItem->SetFontSize(SIZE_10);
        ArkUI_NumberValue value_number[] = { { .i32 = GRID_ITEM_STYLE_PLAIN } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        gridItem->setAttribute(NODE_GRID_ITEM_STYLE, &attribute_item);

        auto itemStyle = gridItem->getAttribute(NODE_GRID_ITEM_STYLE)->value->i32;
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "CreatGrid4 itemStyle:%{public}d", itemStyle);

        text->SetTextContent("A");

        nodeAPI->addChild(gridItem->GetComponent(), text->GetComponent());
        nodeAPI->addChild(grid->GetComponent(), gridItem->GetComponent());
    }

    auto option = OH_ArkUI_GridLayoutOptions_Create();
    uint32_t irregularIndexes[2] = {};
    int32_t size = 4;
    auto ret = OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(option, irregularIndexes, &size);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest",
        "CreatGrid4 Option ret: %{public}d, size:%{public}d, index[0]:%{public}d, index[1]:%{public}d", ret, size,
        irregularIndexes[0], irregularIndexes[1]);
    grid->SetGridLayoutOptions(option);
    OH_ArkUI_GridLayoutOptions_Dispose(option);
    return grid;
}

// napi_value GridTest::CreateNativeNode(napi_env env, napi_callback_info info)
void GridTest::InitializeGrid(napi_env env, napi_callback_info info)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridTest", "CreateNativeNode");

    size_t argc = 1;
    napi_value args[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    size_t length = 64;
    size_t strLength = 0;
    char xComponentID[64] = { 0 };
    napi_get_value_string_utf8(env, args[0], xComponentID, length, &strLength);

    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridTest", "GetContext env or info is null");
        return nullptr;
    }

    ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
}

static std::shared_ptr<GridComponent> CreateBaseGrid()
{
    // 创建grid
    auto grid = CreatGrid(0);
    // 测试 onReachStart
    grid->SetOnGridReachStart([grid]() {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "OnGridReachStart");
        grid->SetBackgroundColor(COLOR_RED);
    });
    // 测试 SetOnReachEnd
    grid->SetOnGridReachEnd([grid]() {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "OnReachEnd");
        grid->SetBackgroundColor(COLOR_YELLOW);
    });
    // 测试 SetOnGridScrollStop
    grid->SetOnGridScrollStop([grid]() {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "OnScrollStop");
        grid->SetBackgroundColor(COLOR_GREEN);
    });
    // 测试 SetOnGridScrollStart
    grid->SetOnGridScrollStart([grid]() {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "OnScrollStart");
        grid->SetBackgroundColor(COLOR_GRAY);
    });
    // 测试 SetOnGridWillScroll
    grid->SetOnGridWillScroll([grid](float offset, int32_t state, int32_t source) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest",
            "OnWillScroll offset: %{public}f, state: %{public}d, source: %{public}d", offset, state, source);
        grid->SetBackgroundColor(COLOR_PINK);
    });
    // 测试 SetOnGridDidScroll
    grid->SetOnGridDidScroll([grid](float offset, int32_t state) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest",
            "OnGridDidScroll offset: %{public}f, state: %{public}d", offset, state);
        grid->SetBackgroundColor(COLOR_PURPLE);
    });
    // 测试 SetOnGridWillStopDragging
    grid->SetOnGridWillStopDragging([grid](float velocity) {
        OH_LOG_Print(
            LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "OnGridWillStopDragging velocity: %{public}f", velocity);
        grid->SetBackgroundColor(COLOR_WHITE);
    });
    // 测试 SetOnGridScrollIndex
    grid->SetOnGridScrollIndex([grid](int32_t first, int32_t last) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest",
            "OnGridScrollIndex first: %{public}d, last: %{public}d", first, last);
        grid->SetBackgroundColor(COLOR_BLACK);
    });
    return grid;
}

static std::shared_ptr<ColumnComponent> CreateModeControls(std::shared_ptr<GridComponent> grid)
{
    // mode属性
    auto modeColumn = std::make_shared<ColumnComponent>();
    auto scrollModeText = std::make_shared<TextComponent>();
    scrollModeText->SetTextContent("scrollMode:");

    auto getScrollModeText = std::make_shared<TextComponent>();
    getScrollModeText->SetTextContent("getScrollMode:");

    auto scrollModeButton = std::make_shared<ButtonComponent>();
    scrollModeButton->SetWidth(SIZE_120);
    scrollModeButton->SetHeight(SIZE_50);
    scrollModeButton->SetId("scrollMode");
    scrollModeButton->SetLable("scrollMode");
    scrollModeButton->RegisterOnClick([grid, scrollModeText, getScrollModeText]() {
        modeIndex_ = (modeIndex_ + 1) % scrollModePool.size();
        auto scrollMode = scrollModePool[modeIndex_];
        scrollModeText->SetTextContent("scrollMode:" + std::to_string(scrollMode) + ", ");
        ArkUI_NumberValue scroll_mode[] = { { .i32 = scrollMode } };
        ArkUI_AttributeItem scroll_mode_item = { scroll_mode, sizeof(scroll_mode) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_SCROLL_BAR_DISPLAY_MODE, &scroll_mode_item);

        auto getScrollMode = grid->getAttribute(NODE_SCROLL_BAR_DISPLAY_MODE);
        getScrollModeText->SetTextContent("getScrollMode:" + std::to_string(getScrollMode->value->i32));
    });

    auto resetScrollModeButton = std::make_shared<ButtonComponent>();
    resetScrollModeButton->SetWidth(SIZE_120);
    resetScrollModeButton->SetHeight(SIZE_50);
    resetScrollModeButton->SetId("resetScrollMode");
    resetScrollModeButton->SetLable("resetScrollMode");
    resetScrollModeButton->RegisterOnClick([grid, getScrollModeText]() {
        grid->resetAttribute(NODE_SCROLL_BAR_DISPLAY_MODE);

        auto getScrollMode = grid->getAttribute(NODE_SCROLL_BAR_DISPLAY_MODE);
        getScrollModeText->SetTextContent("getScrollMode:" + std::to_string(getScrollMode->value->i32));
    });

    modeColumn->AddChild(scrollModeText);
    modeColumn->AddChild(getScrollModeText);
    modeColumn->AddChild(scrollModeButton);
    modeColumn->AddChild(resetScrollModeButton);
    return modeColumn;
}

static std::shared_ptr<ColumnComponent> CreateWidthControls(std::shared_ptr<GridComponent> grid)
{
    // width属性
    auto widthColumn = std::make_shared<ColumnComponent>();
    auto scrollWidthText = std::make_shared<TextComponent>();
    scrollWidthText->SetTextContent("scrollWidth:, ");
    auto getScrollWidthText = std::make_shared<TextComponent>();
    getScrollWidthText->SetTextContent("GetScrollWidth:");

    auto scrollWidthButton = std::make_shared<ButtonComponent>();
    scrollWidthButton->SetWidth(SIZE_120);
    scrollWidthButton->SetHeight(SIZE_50);
    scrollWidthButton->SetId("scrollWidth");
    scrollWidthButton->SetLable("scrollWidth");
    scrollWidthButton->RegisterOnClick([grid, scrollWidthText, getScrollWidthText]() {
        widthIndex_ = (widthIndex_ + 1) % scrollModePool.size();
        auto scrollWidth = scrollSizePool[widthIndex_];
        scrollWidthText->SetTextContent("scrollWidth:" + std::to_string(scrollWidth) + " ,");
        ArkUI_NumberValue scroll_width[] = { { .f32 = scrollWidth } };
        ArkUI_AttributeItem scroll_width_item = { scroll_width, sizeof(scroll_width) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_SCROLL_BAR_WIDTH, &scroll_width_item);

        auto getScrollWidth = grid->getAttribute(NODE_SCROLL_BAR_WIDTH);
        getScrollWidthText->SetTextContent("getScrollWidth:" + std::to_string(getScrollWidth->value->f32));
    });

    auto resetScrollWidthButton = std::make_shared<ButtonComponent>();
    resetScrollWidthButton->SetWidth(SIZE_120);
    resetScrollWidthButton->SetHeight(SIZE_50);
    resetScrollWidthButton->SetId("resetScrollWidth");
    resetScrollWidthButton->SetLable("resetScrollWidth");
    resetScrollWidthButton->RegisterOnClick([grid, getScrollWidthText]() {
        grid->resetAttribute(NODE_SCROLL_BAR_WIDTH);

        auto getScrollWidth = grid->getAttribute(NODE_SCROLL_BAR_WIDTH);
        getScrollWidthText->SetTextContent("getScrollWidth:" + std::to_string(getScrollWidth->value->f32));
    });

    widthColumn->AddChild(scrollWidthText);
    widthColumn->AddChild(getScrollWidthText);
    widthColumn->AddChild(scrollWidthButton);
    widthColumn->AddChild(resetScrollWidthButton);
    return widthColumn;
}

static std::shared_ptr<ColumnComponent> CreateColorControls(std::shared_ptr<GridComponent> grid)
{
    // color属性
    auto colorColumn = std::make_shared<ColumnComponent>();
    auto scrollColorText = std::make_shared<TextComponent>();
    scrollColorText->SetTextContent("scrollColor:");
    auto getScrollColorText = std::make_shared<TextComponent>();
    getScrollColorText->SetTextContent("GetScrollColor:");

    auto scrollColorButton = std::make_shared<ButtonComponent>();
    const int SIZE_120 = 120;
    scrollColorButton->SetWidth(SIZE_120);
    resetFrictionButton->SetHeight(SIZE_50);
    scrollColorButton->SetId("scrollColor");
    scrollColorButton->SetLable("scrollColor");
    scrollColorButton->RegisterOnClick([grid, scrollColorText, getScrollColorText]() {
        colorIndex_ = (colorIndex_ + 1) % scrollColorPool.size();
        auto scrollColor = scrollColorPool[colorIndex_];
        scrollColorText->SetTextContent("scrollColor:" + std::to_string(scrollColor));
        ArkUI_NumberValue scroll_color[] = { { .u32 = scrollColor } };
        ArkUI_AttributeItem scroll_color_item = { scroll_color, sizeof(scroll_color) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_SCROLL_BAR_COLOR, &scroll_color_item);

        auto getScrollColor = grid->getAttribute(NODE_SCROLL_BAR_COLOR);
        getScrollColorText->SetTextContent("getScrollWidth:" + std::to_string(getScrollColor->value->u32));
    });

    auto resetScrollColorButton = std::make_shared<ButtonComponent>();
    resetScrollColorButton->SetWidth(SIZE_120);
    resetScrollColorButton->SetHeight(SIZE_50);
    resetScrollColorButton->SetId("resetScrollColor");
    resetScrollColorButton->SetLable("resetScrollColor");
    resetScrollColorButton->RegisterOnClick([grid, getScrollColorText]() {
        grid->resetAttribute(NODE_SCROLL_BAR_COLOR);

        auto getScrollColor = grid->getAttribute(NODE_SCROLL_BAR_COLOR);
        getScrollColorText->SetTextContent("getScrollWidth:" + std::to_string(getScrollColor->value->u32));
    });
    colorColumn->AddChild(scrollColorText);
    colorColumn->AddChild(getScrollColorText);
    colorColumn->AddChild(scrollColorButton);
    colorColumn->AddChild(resetScrollColorButton);
    return colorColumn;
}

static std::shared_ptr<ColumnComponent> CreateEnableScrollControls(std::shared_ptr<GridComponent> grid)
{
    // enableScroll属性
    auto enableScrollColumn = std::make_shared<ColumnComponent>();
    auto enableScrollText = std::make_shared<TextComponent>();
    enableScrollText->SetTextContent("enableScroll:, ");
    auto getEnableScrollText = std::make_shared<TextComponent>();
    getEnableScrollText->SetTextContent("GetEnableScroll:");

    auto enableScrollButton = std::make_shared<ButtonComponent>();
    enableScrollButton->SetWidth(SIZE_120);
    enableScrollButton->SetHeight(SIZE_50);
    enableScrollButton->SetId("enableScroll");
    enableScrollButton->SetLable("enableScroll");
    enableScrollButton->RegisterOnClick([grid, enableScrollText, getEnableScrollText]() {
        enableScrollIndex_ = (enableScrollIndex_ + 1) % enableScrollPool.size();
        auto value = enableScrollPool[enableScrollIndex_];
        enableScrollText->SetTextContent("enableScroll:" + std::to_string(value));
        ArkUI_NumberValue value_number[] = { { .i32 = value } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &attribute_item);

        auto getValue = grid->getAttribute(NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
        getEnableScrollText->SetTextContent("getEnableScroll:" + std::to_string(getValue->value->i32));
    });

    auto resetEnableScrollButton = std::make_shared<ButtonComponent>();
    resetEnableScrollButton->SetWidth(SIZE_120);
    resetEnableScrollButton->SetHeight(SIZE_50);
    resetEnableScrollButton->SetId("resetEnableScroll");
    resetEnableScrollButton->SetLable("resetEnableScroll");
    resetEnableScrollButton->RegisterOnClick([grid, getEnableScrollText]() {
        grid->resetAttribute(NODE_SCROLL_ENABLE_SCROLL_INTERACTION);

        auto getValue = grid->getAttribute(NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
        getEnableScrollText->SetTextContent("getEnableScroll:" + std::to_string(getValue->value->i32));
    });
    enableScrollColumn->AddChild(enableScrollText);
    enableScrollColumn->AddChild(getEnableScrollText);
    enableScrollColumn->AddChild(enableScrollButton);
    enableScrollColumn->AddChild(resetEnableScrollButton);
    return enableScrollColumn;
}

static std::shared_ptr<ColumnComponent> CreateRowsGapControls(std::shared_ptr<GridComponent> grid)
{
    // rowsGap属性
    auto rowsGapColumn = std::make_shared<ColumnComponent>();
    auto rowsGapText = std::make_shared<TextComponent>();
    rowsGapText->SetTextContent("rowsGap:, ");
    auto getRowsGapText = std::make_shared<TextComponent>();
    getRowsGapText->SetTextContent("GetRowsGap:");

    auto rowsGapButton = std::make_shared<ButtonComponent>();
    rowsGapButton->SetWidth(SIZE_120);
    rowsGapButton->SetHeight(SIZE_50);
    rowsGapButton->SetId("rowGap");
    rowsGapButton->SetLable("rowGap");
    rowsGapButton->RegisterOnClick([grid, rowsGapText, getRowsGapText]() {
        rowGapIndex_ = (rowGapIndex_ + 1) % rowGapPool.size();
        auto rowGap = scrollSizePool[rowGapIndex_];
        rowsGapText->SetTextContent("rowsGap:" + std::to_string(rowGap) + " ,");
        ArkUI_NumberValue rows_gap[] = { { .f32 = rowGap } };
        ArkUI_AttributeItem rows_gap_item = { rows_gap, sizeof(rows_gap) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_GRID_ROW_GAP, &rows_gap_item);

        auto getRowGap = grid->getAttribute(NODE_GRID_ROW_GAP);
        getRowsGapText->SetTextContent("getRowsGap:" + std::to_string(getRowGap->value->f32));
    });

    auto resetRowsGapButton = std::make_shared<ButtonComponent>();
    resetRowsGapButton->SetWidth(SIZE_120);
    resetRowsGapButton->SetHeight(SIZE_50);
    resetRowsGapButton->SetId("resetRowsGap");
    resetRowsGapButton->SetLable("resetRowsGap");
    resetRowsGapButton->RegisterOnClick([grid, getRowsGapText]() {
        grid->resetAttribute(NODE_GRID_ROW_GAP);

        auto getRowGap = grid->getAttribute(NODE_GRID_ROW_GAP);
        getRowsGapText->SetTextContent("getRowsGap:" + std::to_string(getRowGap->value->f32));
    });

    rowsGapColumn->AddChild(rowsGapText);
    rowsGapColumn->AddChild(getRowsGapText);
    rowsGapColumn->AddChild(rowsGapButton);
    rowsGapColumn->AddChild(resetRowsGapButton);
    return rowsGapColumn;
}

static std::shared_ptr<ColumnComponent> CreateAlignItemsControls(std::shared_ptr<GridComponent> grid)
{
    // alignItems属性
    auto alignItemsColumn = std::make_shared<ColumnComponent>();
    auto alignItemsText = std::make_shared<TextComponent>();
    alignItemsText->SetTextContent("alignItems:, ");
    auto getAlignItemsText = std::make_shared<TextComponent>();
    getAlignItemsText->SetTextContent("GetAlignItems:");

    auto alignItemsButton = std::make_shared<ButtonComponent>();
    alignItemsButton->SetWidth(SIZE_120);
    alignItemsButton->SetHeight(SIZE_50);
    alignItemsButton->SetId("alignItems");
    alignItemsButton->SetLable("alignItems");
    alignItemsButton->RegisterOnClick([grid, alignItemsText, getAlignItemsText]() {
        alignItemsIndex_ = (alignItemsIndex_ + 1) % alignItemsPool.size();
        auto value = alignItemsPool[alignItemsIndex_];
        alignItemsText->SetTextContent("alignItems:" + std::to_string(value) + " ,");
        ArkUI_NumberValue value_number[] = { { .i32 = value } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_GRID_ALIGN_ITEMS, &attribute_item);

        auto getValue = grid->getAttribute(NODE_GRID_ALIGN_ITEMS);
        getAlignItemsText->SetTextContent("getEnableScroll:" + std::to_string(getValue->value->i32));
    });

    auto resetAlignItemsButton = std::make_shared<ButtonComponent>();
    resetAlignItemsButton->SetWidth(SIZE_120);
    resetAlignItemsButton->SetHeight(SIZE_50);
    resetAlignItemsButton->SetId("resetAlignItems");
    resetAlignItemsButton->SetLable("resetAlignItems");
    resetAlignItemsButton->RegisterOnClick([grid, getAlignItemsText]() {
        grid->resetAttribute(NODE_GRID_ALIGN_ITEMS);

        auto getValue = grid->getAttribute(NODE_GRID_ALIGN_ITEMS);
        getAlignItemsText->SetTextContent("getEnableScroll:" + std::to_string(getValue->value->i32));
    });

    alignItemsColumn->AddChild(alignItemsText);
    alignItemsColumn->AddChild(getAlignItemsText);
    alignItemsColumn->AddChild(alignItemsButton);
    alignItemsColumn->AddChild(resetAlignItemsButton);
    return alignItemsColumn;
}

static std::shared_ptr<ColumnComponent> CreateFlingSpeedLimitControls(std::shared_ptr<GridComponent> grid)
{
    // flingSpeedLimit属性
    auto flingSpeedLimitColumn = std::make_shared<ColumnComponent>();
    auto flingSpeedLimitText = std::make_shared<TextComponent>();
    flingSpeedLimitText->SetTextContent("flingSpeedLimit:, ");
    auto getFlingSpeedLimitText = std::make_shared<TextComponent>();
    getFlingSpeedLimitText->SetTextContent("GetFlingSpeedLimit:");

    auto flingSpeedLimitButton = std::make_shared<ButtonComponent>();
    flingSpeedLimitButton->SetWidth(SIZE_120);
    alignItemsButton->SetHeight(SIZE_50);
    flingSpeedLimitButton->SetId("flingSpeedLimit");
    flingSpeedLimitButton->SetLable("flingSpeedLimit");
    flingSpeedLimitButton->RegisterOnClick([grid, flingSpeedLimitText, getFlingSpeedLimitText]() {
        flingSpeedLimitIndex_ = (flingSpeedLimitIndex_ + 1) % flingSpeedLimitPool.size();
        auto value = flingSpeedLimitPool[flingSpeedLimitIndex_];
        flingSpeedLimitText->SetTextContent("flingSpeedLimit:" + std::to_string(value) + " ,");
        ArkUI_NumberValue value_number[] = { { .f32 = value } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_SCROLL_FLING_SPEED_LIMIT, &attribute_item);

        auto getValue = grid->getAttribute(NODE_SCROLL_FLING_SPEED_LIMIT);
        getFlingSpeedLimitText->SetTextContent("getFlingSpeedLimit:" + std::to_string(getValue->value->f32));
    });

    auto resetFlingSpeedLimitButton = std::make_shared<ButtonComponent>();
    resetFlingSpeedLimitButton->SetWidth(SIZE_120);
    resetFlingSpeedLimitButton->SetHeight(SIZE_50);
    resetFlingSpeedLimitButton->SetId("resetFlingSpeedLimit");
    resetFlingSpeedLimitButton->SetLable("resetFlingSpeedLimit");
    resetFlingSpeedLimitButton->RegisterOnClick([grid, getFlingSpeedLimitText]() {
        grid->resetAttribute(NODE_SCROLL_FLING_SPEED_LIMIT);

        auto getValue = grid->getAttribute(NODE_SCROLL_FLING_SPEED_LIMIT);
        getFlingSpeedLimitText->SetTextContent("getFlingSpeedLimit:" + std::to_string(getValue->value->f32));
    });
    flingSpeedLimitColumn->AddChild(flingSpeedLimitText);
    flingSpeedLimitColumn->AddChild(getFlingSpeedLimitText);
    flingSpeedLimitColumn->AddChild(flingSpeedLimitButton);
    flingSpeedLimitColumn->AddChild(resetFlingSpeedLimitButton);
    return flingSpeedLimitColumn;
}

static std::shared_ptr<ColumnComponent> CreateFrictionControls(std::shared_ptr<GridComponent> grid)
{
    // friction属性
    auto frictionColumn = std::make_shared<ColumnComponent>();
    auto frictionText = std::make_shared<TextComponent>();
    frictionText->SetTextContent("friction:, ");
    auto getFrictionText = std::make_shared<TextComponent>();
    getFrictionText->SetTextContent("GetFriction:");

    auto frictionButton = std::make_shared<ButtonComponent>();
    frictionButton->SetWidth(SIZE_120);
    frictionButton->SetHeight(SIZE_50);
    frictionButton->SetId("friction");
    frictionButton->SetLable("friction");
    frictionButton->RegisterOnClick([grid, frictionText, getFrictionText]() {
        frictionIndex_ = (frictionIndex_ + 1) % frictionPool.size();
        auto value = frictionPool[frictionIndex_];
        frictionText->SetTextContent("friction:" + std::to_string(value) + " ,");
        ArkUI_NumberValue value_number[] = { { .f32 = value } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_SCROLL_FRICTION, &attribute_item);

        auto getValue = grid->getAttribute(NODE_SCROLL_FRICTION);
        getFrictionText->SetTextContent("friction:" + std::to_string(getValue->value->f32));
    });

    auto resetFrictionButton = std::make_shared<ButtonComponent>();
    resetFrictionButton->SetWidth(SIZE_120);
    resetFrictionButton->SetHeight(SIZE_50);
    resetFrictionButton->SetId("resetFriction");
    resetFrictionButton->SetLable("resetFriction");
    resetFrictionButton->RegisterOnClick([grid, getFrictionText]() {
        grid->resetAttribute(NODE_SCROLL_FRICTION);

        auto getValue = grid->getAttribute(NODE_SCROLL_FRICTION);
        getFrictionText->SetTextContent("friction:" + std::to_string(getValue->value->f32));
    });
    frictionColumn->AddChild(frictionText);
    frictionColumn->AddChild(getFrictionText);
    frictionColumn->AddChild(frictionButton);
    frictionColumn->AddChild(resetFrictionButton);
}

static std::shared_ptr<ColumnComponent> CreateNestedScrollControls(std::shared_ptr<GridComponent> grid)
{
    auto nestedScrollColumn = std::make_shared<ColumnComponent>();
    auto nestedScrollText = std::make_shared<TextComponent>();
    nestedScrollText->SetTextContent("nestedScroll:, ");
    auto getNestedScrollText = std::make_shared<TextComponent>();
    getNestedScrollText->SetTextContent("getNestedScroll:");
    auto nestedScrollButton = std::make_shared<ButtonComponent>();
    nestedScrollButton->SetWidth(SIZE_120);
    nestedScrollButton->SetHeight(SIZE_50);
    nestedScrollButton->SetId("nestedScroll");
    nestedScrollButton->SetLable("nestedScroll");
    nestedScrollButton->RegisterOnClick([grid, nestedScrollText, getNestedScrollText]() {
        nestedModeIndex_ = (nestedModeIndex_ + 1) % nestedModePool.size();
        auto forwardValue = nestedModePool[nestedModeIndex_];
        auto backValue = nestedModePool[nestedModeIndex_];
        nestedScrollText->SetTextContent("nestedScroll" + std::to_string(forwardValue) + std::to_string(backValue));
        ArkUI_NumberValue value_number[] = { { .i32 = forwardValue }, { .i32 = backValue } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_SCROLL_NESTED_SCROLL, &attribute_item);
        auto getValue = grid->getAttribute(NODE_SCROLL_NESTED_SCROLL);
        if (getValue != nullptr) {
            auto size = getValue->size;
            auto forward = getValue->value[0].i32;
            auto back = getValue->value[1].i32;
            getNestedScrollText->SetTextContent("getNestedScroll" + std::to_string(forward) + std::to_string(back));
        } else {
            getNestedScrollText->SetTextContent("空");
        }
    });
    auto resetNestedScrollButton = std::make_shared<ButtonComponent>();
    resetNestedScrollButton->SetWidth(SIZE_120);
    resetNestedScrollButton->SetHeight(SIZE_50);
    resetNestedScrollButton->SetId("resetNestedScroll");
    resetNestedScrollButton->SetLable("resetNestedScroll");
    resetNestedScrollButton->RegisterOnClick([grid, getNestedScrollText]() {
        grid->resetAttribute(NODE_SCROLL_NESTED_SCROLL);
        auto getValue = grid->getAttribute(NODE_SCROLL_NESTED_SCROLL);
        if (getValue != nullptr) {
            auto size = getValue->size;
            auto forward = getValue->value[0].i32;
            auto back = getValue->value[1].i32;
            getNestedScrollText->SetTextContent("getNestedScroll" + std::to_string(forward) + std::to_string(back));
        } else {
            getNestedScrollText->SetTextContent("空");
        }
    });
    nestedScrollColumn->AddChild(nestedScrollText);
    nestedScrollColumn->AddChild(getNestedScrollText);
    nestedScrollColumn->AddChild(nestedScrollButton);
    nestedScrollColumn->AddChild(resetNestedScrollButton);
    return nestedScrollColumn;
}

static std::shared_ptr<ColumnComponent> CreateFadingEdgeControls(std::shared_ptr<GridComponent> grid)
{
    // fadingEdge
    auto fadingEdgeColumn = std::make_shared<ColumnComponent>();
    auto fadingEdgeText = std::make_shared<TextComponent>();
    fadingEdgeText->SetTextContent("fadingEdge:, ");
    auto getFadingEdgeText = std::make_shared<TextComponent>();
    getFadingEdgeText->SetTextContent("getFadingEdge:");
    auto fadingEdgeButton = std::make_shared<ButtonComponent>();
    fadingEdgeButton->SetWidth(SIZE_120);
    fadingEdgeButton->SetHeight(SIZE_50);
    fadingEdgeButton->SetId("fadingEdge");
    fadingEdgeButton->SetLable("fadingEdge");
    fadingEdgeButton->RegisterOnClick([grid, fadingEdgeText, getFadingEdgeText]() {
        fadingEdgeIndex_ = (fadingEdgeIndex_ + 1) % fadingEdgePool.size();
        auto value = fadingEdgePool[fadingEdgeIndex_];
        fadingEdgeText->SetTextContent("fadingEdge:" + std::to_string(value) + ",");
        ArkUI_NumberValue value_number[] = { { .i32 = 1 }, { .f32 = value } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        grid->setAttribute(NODE_SCROLL_FADING_EDGE, &attribute_item);
        auto getValue = grid->getAttribute(NODE_SCROLL_FADING_EDGE);
        if (getValue != nullptr) {
            auto effect = getValue->value[0].i32;
            auto value = getValue->value[1].f32;
            getFadingEdgeText->SetTextContent("effect:" + std::to_string(effect) + ",value:" + std::to_string(value));
        } else {
            getFadingEdgeText->SetTextContent("空");
        }
    });
    auto resetEdgeButton = std::make_shared<ButtonComponent>();
    resetEdgeButton->SetWidth(SIZE_120);
    resetEdgeButton->SetHeight(SIZE_50);
    resetEdgeButton->SetId("resetFadingEdge");
    resetEdgeButton->SetLable("resetFadingEdge");
    resetEdgeButton->RegisterOnClick([grid, fadingEdgeText, getFadingEdgeText]() {
        grid->resetAttribute(NODE_SCROLL_FADING_EDGE);
        auto getValue = grid->getAttribute(NODE_SCROLL_FADING_EDGE);
        if (getValue != nullptr) {
            auto effect = getValue->value[0].i32;
            auto value = getValue->value[1].f32;
            getFadingEdgeText->SetTextContent("effect:" + std::to_string(effect) + ",value:" + std::to_string(value));
        } else {
            getFadingEdgeText->SetTextContent("空");
        }
    });
    fadingEdgeColumn->AddChild(fadingEdgeText);
    fadingEdgeColumn->AddChild(getFadingEdgeText);
    fadingEdgeColumn->AddChild(fadingEdgeButton);
    fadingEdgeColumn->AddChild(resetEdgeButton);
    return fadingEdgeColumn;
}

static std::shared_ptr<GridComponent> CreateBaseGrid2()
{
    // 创建grid2
    auto grid2 = CreatGrid2(0);
    // 测试 SetOnGridScrollFrameBegin
    grid2->SetOnGridScrollFrameBegin([grid](float offset, int32_t state) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest",
            "OnScrollFrameBegin offset: %{public}f, state: %{public}d", offset, state);
        grid->SetBackgroundColor(COLOR_BLUE);
        return PARAM_10;
    });
    grid->SetMargin(PARAM_0, SIZE_50, PARAM_0, SIZE_50);
    auto option2 = grid2->GetGridLayoutOptions();
    uint32_t irregularIndexes2[] = { 3, 6 };
    auto ret = OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option2, irregularIndexes2, 2);
    std::string* str = new std::string("grid2 IrregularSizeWorld-2");
    void* userDataWorld = static_cast<void*>(str);
    OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
        option2, userDataWorld, [](int32_t itemIndex, void* userData) -> ArkUI_GridItemSize {
            if (userData) {
                std::string* str = static_cast<std::string*>(userData);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest",
                    "CreateNativeNode grid2 userData-1:%{public}s", str->c_str());
            }
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "CreateNativeNode grid2 itemIndex:%{public}d",
                itemIndex);
            if (itemIndex == 0) {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "CreateNativeNode grid2 itemIndex == 0");
                return { 2, 3 };
            }
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest", "CreateNativeNode grid2 itemIndex != 0");
            return { 2, 4 };
        });
    grid2->SetGridLayoutOptions(option2);
    grid2->SetOnScrollBarUpdate();
    column->AddChild(grid2);

    uint32_t irregularIndexes[2] = {};
    int32_t size = 4;
    ret = OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(option2, irregularIndexes, &size);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridTest",
        "CreateNativeNode Option ret: %{public}d, size:%{public}d, index[0]:%{public}d, index[1]:%{public}d", ret, size,
        irregularIndexes[0], irregularIndexes[1]);
    OH_ArkUI_GridLayoutOptions_Dispose(option2);
    return grid2;
}

static std::shared_ptr<ColumnComponent> CreateClipModeControls(std::shared_ptr<GridComponent> grid)
{
    // clipMode
    auto clipModeColumn = std::make_shared<ColumnComponent>();
    auto clipModeText = std::make_shared<TextComponent>();
    clipModeText->SetTextContent("clipMode:, ");
    auto getClipModeText = std::make_shared<TextComponent>();
    getClipModeText->SetTextContent("GetClipMode:");

    auto clipModeButton = std::make_shared<ButtonComponent>();
    clipModeButton->SetWidth(SIZE_120);
    clipModeButton->SetHeight(SIZE_50);
    clipModeButton->SetId("clipMode");
    clipModeButton->SetLable("clipMode");
    clipModeButton->RegisterOnClick([grid1, clipModeText, getClipModeText]() {
        clipModeIndex_ = (clipModeIndex_ + 1) % clipModePool.size();
        auto value = clipModePool[clipModeIndex_];
        clipModeText->SetTextContent("clipMode:" + std::to_string(value) + " ,");
        ArkUI_NumberValue value_number[] = { { .i32 = value } };
        ArkUI_AttributeItem attribute_item = { value_number, sizeof(value_number) / sizeof(ArkUI_NumberValue) };
        grid1->setAttribute(NODE_SCROLL_CLIP_CONTENT, &attribute_item);

        auto getValue = grid1->getAttribute(NODE_SCROLL_CLIP_CONTENT);
        getClipModeText->SetTextContent("clipMode:" + std::to_string(getValue->value->i32));
    });

    auto resetClipModeButton = std::make_shared<ButtonComponent>();
    resetClipModeButton->SetWidth(SIZE_120);
    resetClipModeButton->SetHeight(SIZE_50);
    resetClipModeButton->SetId("resetClipMode");
    resetClipModeButton->SetLable("resetClipMode");
    resetClipModeButton->RegisterOnClick([grid1, clipModeText, getClipModeText]() {
        grid1->resetAttribute(NODE_SCROLL_CLIP_CONTENT);

        auto getValue = grid1->getAttribute(NODE_SCROLL_CLIP_CONTENT);
        getClipModeText->SetTextContent("clipMode:" + std::to_string(getValue->value->i32));
    });
    clipModeColumn->AddChild(clipModeText);
    clipModeColumn->AddChild(getClipModeText);
    clipModeColumn->AddChild(clipModeButton);
    clipModeColumn->AddChild(resetClipModeButton);
    return clipModeColumn;
}

static std::shared_ptr<ColumnComponent> CreateColumn(std::shared_ptr<GridComponent> grid)
{
    // firstRow
    auto firstRow = std::make_shared<RowComponent>();
    auto modeControls = CreateModeControls(grid);
    auto widthControls = CreateWidthControls(grid);
    firstRow->AddChild(modeColumn);
    firstRow->AddChild(widthColumn);

    auto colorControls = CreateColorControls(grid);
    auto firstRow1 = std::make_shared<RowComponent>();
    firstRow1->AddChild(colorColumn);

    // secondRow
    auto secondRow = std::make_shared<RowComponent>();
    auto rowsGapColumn = CreateRowsGapControls(grid);
    auto enableScrollColumn = CreateEnableScrollControls(grid);
    auto alignItemsColumn = CreateAlignItemsControls(grid);
    secondRow->AddChild(rowsGapColumn);
    secondRow->AddChild(enableScrollColumn);
    secondRow->AddChild(alignItemsColumn);

    // third
    auto thirdRow = std::make_shared<RowComponent>();
    auto flingSpeedLimitColumn = CreateFlingSpeedLimitControls(grid);
    auto frictionColumn = CreateFrictionControls(grid);
    thirdRow->AddChild(flingSpeedLimitColumn);
    thirdRow->AddChild(frictionColumn);

    // forth
    auto forthRow = std::make_shared<RowComponent>();
    auto nestedScrollColumn = CreateNestedScrollControls(grid);
    auto fadingEdgeColumn = CreateFadingEdgeControls(grid);
    forthRow->AddChild(nestedScrollColumn);
    forthRow->AddChild(fadingEdgeColumn);

    auto column = std::make_shared<ColumnComponent>();
    auto grid4 = CreatGrid(0);
    column->AddChild(grid4);
    column->AddChild(firstRow);
    column->AddChild(firstRow1);
    column->AddChild(secondRow);
    column->AddChild(thirdRow);
    column->AddChild(forthRow);
    auto grid1 = CreatGrid1(0);
    column->AddChild(grid1);
    auto clipModeColumn = CreateClipModeControls(grid);
    column->AddChild(clipModeColumn);
    return column;
}

static std::shared_ptr<ScrollComponent> AssembleFinalLayout()
{
    auto scroll = new ScrollComponent();
    scroll->SetMargin(PARAM_0, PARAM_0, SIZE_50, PARAM_0);
    scroll->SetHeight(SIZE_2000);
    scroll->SetScrollScrollBar(ArkUI_ScrollBarDisplayMode::ARKUI_SCROLL_BAR_DISPLAY_MODE_ON);
    scroll->SetId("scroll");
    scroll->AddChild(column);
    return scroll;
}

napi_value GridTest::CreateNativeNode(napi_env env, napi_callback_info info)
{
    auto scroll = AssembleFinalLayout();
    std::string id(xComponentID);
    if (OH_NativeXComponent_AttachNativeRootNode(
        PluginManager::GetInstance()->GetNativeXComponent(id),
        scroll->GetComponent()) == INVALID_PARAM) {
    OH_LOG_Print(
        LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridTest", "OH_NativeXComponent_AttachNativeRootNode failed");
    }

    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }

    return exports;
}
} // namespace ArkUICApiDemo