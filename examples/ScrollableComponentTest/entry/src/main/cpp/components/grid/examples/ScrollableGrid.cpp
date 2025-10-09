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

#include <functional>
#include <string>
#include <vector>
#include <cstdio> // snprintf
#include <sstream>
#include <iomanip>

#include <arkui/native_node.h>
#include <arkui/native_type.h>

#include "common/ArkUINode.h"
#include "common/ArkUINodeAdapter.h"
#include "components/grid/Grid.h"

namespace {
// ===== 布局与样式常量 =====
constexpr char K_ROWS_TEMPLATE[] = "auto";
constexpr char K_COLUMNS_TEMPLATE[] = "1fr 1fr";
constexpr float K_COLUMNS_GAP = 10.0f;
constexpr float K_ROWS_GAP = 15.0f;
constexpr uint32_t K_ITEM_BG_COLOR = 0xFFF1F3F5U;

constexpr uint32_t K_GRID_CACHED_COUNT = 32;
constexpr bool K_GRID_SYNC_LOAD = true;
constexpr ArkUI_FocusWrapMode K_FOCUS_WRAP_MODE = ARKUI_FOCUS_WRAP_MODE_DEFAULT;

constexpr int K_ITEM_COUNT = 60;
constexpr float K_ITEM_HEIGHT = 72.0f;
constexpr int K_GRID_INDEX_WIDTH = 2;
} // namespace

// ---------- 生成数据：Grid01 ~ Grid60 ----------
static std::vector<std::string> MakeServicesData(size_t count = K_ITEM_COUNT)
{
    std::vector<std::string> out;
    out.reserve(count);
    for (size_t i = 1; i <= count; ++i) {
        std::ostringstream oss;
        oss << "Grid" << std::setw(K_GRID_INDEX_WIDTH) << std::setfill('0') << i;
        out.emplace_back(oss.str());
    }
    return out;
}

// ---------- 配置 Grid 外观/交互 ----------
static void ConfigureGrid(const std::shared_ptr<Grid> &grid)
{
    grid->SetWidthPercent(1.0f);
    grid->SetDefaultScrollStyle();
    grid->SetColumnsTemplate(K_COLUMNS_TEMPLATE);
    grid->SetCachedCount(K_GRID_CACHED_COUNT);
    grid->SetFocusWrapMode(K_FOCUS_WRAP_MODE);
    grid->SetSyncLoad(K_GRID_SYNC_LOAD);
    grid->SetColumnsGap(K_COLUMNS_GAP);
    grid->SetRowsGap(K_ROWS_GAP);
}

// ---------- 适配器回调（创建/绑定） ----------
static ArkUI_NodeHandle GridCreateItem(ArkUI_NativeNodeAPI_1 *api)
{
    ArkUI_NodeHandle text = api->createNode(ARKUI_NODE_TEXT);
    ArkUI_NodeHandle item = api->createNode(ARKUI_NODE_GRID_ITEM);
    api->addChild(item, text);
    return item;
}

static void GridBindItem(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle item, int32_t index,
                         const std::shared_ptr<std::vector<std::string>> &data)
{
    SetAttributeUInt32(api, item, NODE_BACKGROUND_COLOR, K_ITEM_BG_COLOR);
    SetAttributeFloat32(api, item, NODE_HEIGHT, K_ITEM_HEIGHT);

    ArkUI_NodeHandle text = api->getFirstChild(item);
    if (!text) {
        return;
    }

    const int32_t n = static_cast<int32_t>(data->size());
    const char *s = (index >= 0 && index < n) ? (*data)[static_cast<size_t>(index)].c_str() : "<invalid>";
    SetTextContent(api, text, s);
}

// ---------- 构建 Adapter ----------
static std::shared_ptr<ArkUINodeAdapter> MakeGridAdapter(const std::shared_ptr<std::vector<std::string>> &data)
{
    auto adapter = std::make_shared<ArkUINodeAdapter>();
    adapter->EnsurePlaceholderTypeOr(static_cast<int32_t>(ARKUI_NODE_GRID_ITEM));

    ArkUINodeAdapter::Callbacks cb{};
    cb.getTotalCount = [data]() -> int32_t { return static_cast<int32_t>(data->size()); };
    cb.getStableId = [data](int32_t i) -> uint64_t {
        const int32_t n = static_cast<int32_t>(data->size());
        if (i >= 0 && i < n) {
            return static_cast<uint64_t>(std::hash<std::string>{}((*data)[static_cast<size_t>(i)]));
        }
        return static_cast<uint64_t>(i);
    };
    cb.onCreate = [](ArkUI_NativeNodeAPI_1 *api, int32_t /*index*/) -> ArkUI_NodeHandle { return GridCreateItem(api); };
    cb.onBind = [data](ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle item, int32_t index) {
        GridBindItem(api, item, index, data);
    };

    adapter->SetCallbacks(cb);
    return adapter;
}

// ---------- 整体构建 Grid ----------
static std::shared_ptr<Grid> BuildGrid()
{
    auto grid = std::make_shared<Grid>();
    ConfigureGrid(grid);

    auto data = std::make_shared<std::vector<std::string>>(MakeServicesData(K_ITEM_COUNT));
    auto adapter = MakeGridAdapter(data);
    grid->SetLazyAdapter(adapter);
    adapter->ReloadAllItems();
    GetKeepAliveContainer<Grid>().emplace_back(grid);
    return grid;
}

ArkUI_NodeHandle Grid::CreateScrollableGrid()
{
    ArkUI_NativeNodeAPI_1 *api = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, api);
    if (api == nullptr) {
        return nullptr;
    }

    // 根容器全屏
    ArkUI_NodeHandle page = api->createNode(ARKUI_NODE_COLUMN);
    if (page == nullptr) {
        return nullptr;
    }
    SetAttributeFloat32(api, page, NODE_WIDTH_PERCENT, 1.0f);
    SetAttributeFloat32(api, page, NODE_HEIGHT_PERCENT, 1.0f);

    // 构建 Grid
    std::shared_ptr<Grid> grid = BuildGrid();
    if (grid && grid->GetHandle() != nullptr) {
        SetAttributeFloat32(api, grid->GetHandle(), NODE_LAYOUT_WEIGHT, 1.0f);
        api->addChild(page, grid->GetHandle());
    }

    return page;
}
