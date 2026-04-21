/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 */

#include "GridDragEventMaker.h"

#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "../common/ArkUIColumnNode.h"
#include "ArkUIGridNode.h"
#include "ArkUIGridItemNode.h"
#include "ArkUINodeExpandAdapter.h"
#include "../common/ArkUITextNode.h"
#include "../common/ArkUINode.h"

namespace {
// ===== 布局与样式常量 =====
constexpr char K_COLUMNS_TEMPLATE[] = "1fr 1fr 1fr";
constexpr float K_WIDTH_PERCENT = 0.9f;
constexpr float K_COLUMNS_GAP = 10.0f;
constexpr float K_ROWS_GAP = 10.0f;
constexpr float K_HEIGHT = 300.0f;
constexpr float K_TEXT_SIZE = 16.0f;
constexpr float K_ITEM_HEIGHT = 80.0f;
constexpr float K_ITEM_WIDTH = 80.f;
constexpr float SIZE_450 = 450.0f;
constexpr float SIZE_300 = 300.0f;
constexpr int32_t HALF = 2;
constexpr float SIZE_3 = 3.0f;
constexpr float SIZE_5 = 5.0f;
constexpr float K_NODE_FONT_SIZE = 16.0f;
constexpr char K_COLUMNS_TEMPLATE_OTHER[] = "1fr 1fr 1fr 1fr";
constexpr float K_ITEM_HEIGHT_OTHER = 50.0f;
constexpr float K_ITEM_WIDTH_OTHER = 50.f;
constexpr uint32_t K_ITEM_BG_COLOR = 0xFFF9CF93U;
constexpr uint32_t K_BG_COLOR = 0xFFFAEEE0;
constexpr uint32_t K_TEXT_COLOR = 0xFFCCCCCC;
constexpr uint32_t GRID_ITEM_COUNT = 15;
constexpr uint32_t K_BORDER_COLOR = 0xFFDDDDDD;
const std::string CONTENT = "演示GridItem的拖拽事件";
const std::string CONTENT_OTHER = "演示MultiSelectable及选中事件";
} // namespace

static std::vector<std::string> BuildData()
{
    std::vector<std::string> data;
    for (size_t i = 0; i < GRID_ITEM_COUNT; i++) {
        data.emplace_back(std::to_string(i));
    }
    return data;
}

// ---------- 配置 Grid 外观/交互 ----------
void GridDragEventMaker::ConfigureGrid(std::shared_ptr<ArkUIGridNode>& grid)
{
    grid->SetGridColumnsTemplate(K_COLUMNS_TEMPLATE);
    grid->SetWidthPercent(K_WIDTH_PERCENT);
    grid->SetHeight(K_HEIGHT);
    grid->SetBackgroundColor(K_BG_COLOR);
    grid->SetGridEditMode(true);
    grid->SetGridSupportDragAnimation(true);
    grid->SetGridRowsGap(K_ROWS_GAP);
    grid->SetGridColumnsGap(K_COLUMNS_GAP);
    grid->SetBorderWidth(1);
    grid->RegisterOnItemDragStart([grid](float x, float y, int32_t index) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridDragEventMaker",
            "OnItemDragStart x:%{public}f y:%{public}f, index:%{public}d", x, y, index);
    });
    grid->RegisterOnItemDragMove([grid](float x, float y, int32_t index, int32_t insertIndex) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridDragEventMaker",
            "OnItemDragMove x: %{public}f, y: %{public}f, index:%{public}d, insertIndex:%{public}d", x, y, index,
            insertIndex);
    });
    grid->RegisterOnItemDragLeave([grid](float x, float y, int32_t index) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridDragEventMaker",
            "OnItemDragLeave x: %{public}f, y: %{public}f, index:%{public}d", x, y, index);
    });
    grid->RegisterOnItemDragEnter([grid](float x, float y) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridDragEventMaker",
            "OnItemDragEnter x: %{public}f, y: %{public}f", x, y);
    });
    grid->RegisterOnItemDrop([grid](float x, float y, int32_t index, int32_t insertIndex, int32_t success) {
        if (!success || insertIndex >= BuildData().size()) {
            return;
        }
        auto lazyLoader = grid->GetLazyAdapter();
        if (lazyLoader) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridDragEventMaker",
                "MoveItem index: %{public}d, insertIndex:%{public}d", index, insertIndex);
            lazyLoader->MoveItem(index, insertIndex);
        }
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "GridDragEventMaker",
            "OnItemDragDrop x: %{public}f, y: %{public}f, index:%{public}d, itemIndex:%{public}d, success:%{public}d",
            x, y, index, insertIndex, success);
    });
}

// ---------- 适配器回调（创建/绑定） ----------
std::shared_ptr<ArkUIGridItemNode> GridDragEventMaker::CreateGridItem(const std::string& content)
{
    auto item = std::make_shared<ArkUIGridItemNode>();
    auto text = std::make_shared<ArkUITextNode>();
    text->SetTextAlign(ARKUI_TEXT_ALIGNMENT_CENTER);
    text->SetBackgroundColor(K_ITEM_BG_COLOR);
    text->SetHeight(K_ITEM_HEIGHT);
    text->SetWidth(K_ITEM_WIDTH);
    text->SetFontSize(K_NODE_FONT_SIZE);
    text->SetTextContent(content);
    item->AddChild(text);
    return item;
}

std::shared_ptr<ArkUIGridNode> GridDragEventMaker::BuildGrid()
{
    auto grid = std::make_shared<ArkUIGridNode>();
    ConfigureGrid(grid);
    std::vector<std::shared_ptr<BaseNode>> input1;
    auto adapter = std::make_shared<ItemAdapter<ArkUIGridItemNode>>(input1);
    grid->SetLazyAdapter(adapter);

    auto data = BuildData();
    for (int i = 0; i < data.size(); i++) {
        auto item = CreateGridItem(data[i]);
        adapter->InsertItem(i, item);
    }
    GetKeepAliveContainer<ArkUIGridNode>().emplace_back(grid);
    return grid;
}

std::shared_ptr<ArkUIGridNode> GridDragEventMaker::BuildGrid2()
{
    auto grid = std::make_shared<ArkUIGridNode>();
    grid->SetWidth(SIZE_450);
    grid->SetHeight(SIZE_300);
    grid->SetGridColumnsTemplate(K_COLUMNS_TEMPLATE_OTHER);
    grid->SetGridColumnsGap(K_COLUMNS_GAP);
    grid->SetGridRowsGap(K_ROWS_GAP);
    grid->SetBorderWidth(SIZE_3);
    grid->SetMargin(SIZE_5);
    grid->SetGridMultiSelectable(true);

    for (int i = 0; i < GRID_ITEM_COUNT; i++) {
        auto gridItem = CreateGridItem(std::to_string(i));
        grid->SetSelectedStates(gridItem);

        if (i % HALF == 0) {
            gridItem->SetGridItemSelectable(false);
        } else {
            gridItem->SetGridItemSelectable(true);
        }
        if (i == 1) {
            gridItem->SetGridItemSelectable(true);
            gridItem->SetGridItemSelected(true);
        }

        gridItem->RegisterOnItemSelect([gridItem](bool selected) {
            OH_LOG_Print(
                LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridDragEventMaker", "OnSelect selected:%{public}d", selected);
        });
        grid->AddChild(gridItem);
    }
    
    GetKeepAliveContainer<ArkUIGridNode>().emplace_back(grid);
    return grid;
}
 
ArkUI_NodeHandle GridDragEventMaker::CreateNativeNode()
{
    ArkUI_NativeNodeAPI_1* api = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, api);
    if (api == nullptr) {
        return nullptr;
    }

    // 根容器全屏
    auto page = std::make_shared<ArkUIColumnNode>();
    page->SetWidthPercent(1.0f);
    page->SetHeightPercent(1.0f);

    auto title = std::make_shared<ArkUITextNode>();
    if (title) {
        title->SetMargin(SIZE_5);
        title->SetTextContent(CONTENT);
        title->SetFontSize(K_TEXT_SIZE);
        page->AddChild(title);
    }

    // 构建 Grid
    // 用于测试NODE_GRID_DRAG_ANIMATION和NODE_GRID_EDIT_MODE2个属性，
    // 以及NODE_GRID_ON_ITEM_DRAG_START、NODE_GRID_ON_ITEM_DRAG_MOVE、NODE_GRID_ON_ITEM_DRAG_ENTER、
    // NODE_GRID_ON_ITEM_DRAG_LEAVE、NODE_GRID_ON_ITEM_DROP 几个事件
    std::shared_ptr<ArkUIGridNode> grid = BuildGrid();
    if (grid) {
        page->AddChild(grid);
    }

    auto title2 = std::make_shared<ArkUITextNode>();
    title2->SetTextContent(CONTENT_OTHER);
    if (title2) {
        title2->SetMargin(SIZE_5);
        title2->SetTextContent(CONTENT_OTHER);
        title2->SetFontSize(K_TEXT_SIZE);
        page->AddChild(title2);
    }

    // 用于测试 NODE_GRID_ITEM_SELECTABLE和NODE_GRID_ITEM_SELECTED 2个属性，
    // 以及NODE_GRID_ITEM_ON_SELECT 事件
    std::shared_ptr<ArkUIGridNode> grid2 = BuildGrid2();
    if (grid2) {
        page->AddChild(grid2);
    }

    return page->GetHandle();
}
