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

#include <algorithm>
#include <string>
#include <vector>

#include <arkui/native_type.h>

#include "common/ArkUINodeAdapter.h"
#include "components/waterflow/WaterFlowSection.h"
#include "common/ArkUINode.h"
#include "common/ArkUIUtils.h"
#include "common/ArkUIScrollEvents.h"
#include "components/waterflow/WaterFlow.h"

namespace {
constexpr char K_ITEM_TITLE_PREFIX[] = "FlowItem ";
constexpr float K_FONT_SIZE = 16.0f;

constexpr float K_MAIN_A = 120.0f;
constexpr float K_MAIN_B = 160.0f;
constexpr float K_MAIN_C = 100.0f;

constexpr float K_WATER_FLOW_W = 400.0f;
constexpr float K_WATER_FLOW_H = 600.0f;

constexpr int K_INIT_RESERVE = 200;
constexpr int K_INIT_SEED = 100;

constexpr int32_t K_CROSS_COUNT = 2;
constexpr float K_COLUMN_GAP = 10.0f;
constexpr float K_ROW_GAP = 10.0f;
constexpr int32_t K_MARGIN_TOP = 12, K_MARGIN_RIGHT = 12, K_MARGIN_BOTTOM = 12, K_MARGIN_LEFT = 12;

constexpr float K_WIDTH_PERCENT_FULL = 1.0f;
constexpr bool K_SYNC_LOAD = true;
constexpr int32_t K_CACHED_ITEM_COUNT = 24;
constexpr float K_ITEM_MAIN_MIN = 80.0f;
constexpr float K_ITEM_MAIN_MAX = 220.0f;

constexpr int32_t K_LAYOUT_DIRECTION_RTL = 1;
constexpr int32_t K_LAYOUT_MODE_WATER_FLOW = 1;

constexpr char K_COLUMN_TEMPLATE[] = "1fr 1fr";
constexpr char K_ROW_TEMPLATE[] = "auto";

constexpr int32_t K_SCROLL_TO_INDEX = 5;
constexpr int32_t K_SCROLL_ALIGN_CENTER = static_cast<int32_t>(ARKUI_SCROLL_ALIGNMENT_CENTER);

constexpr int K_AUTO_THRESHOLD = 20;
constexpr int K_AUTO_BATCH = 100;
constexpr int K_AUTO_MAX_ITEMS = 100000;

constexpr float K_MAIN_SEQ[] = {K_MAIN_A, K_MAIN_B, K_MAIN_C};
constexpr size_t K_MAIN_SEQ_COUNT = sizeof(K_MAIN_SEQ) / sizeof(K_MAIN_SEQ[0]);
constexpr uint32_t K_PALETTE[] = {0xFF6A5ACD, 0xFF00FFFF, 0xFF00FF7F, 0xFFDA70D6, 0xFFFFC0CB};
constexpr size_t K_PALETTE_COUNT = sizeof(K_PALETTE) / sizeof(K_PALETTE[0]);
} // namespace

static std::shared_ptr<WaterFlow> gNode;
static std::shared_ptr<ArkUINodeAdapter> gAdapter;
static std::shared_ptr<WaterFlowSection> gSection;
static std::vector<std::string> gItems;

struct AutoAppendConfig {
    bool enabled = true;
    int threshold = K_AUTO_THRESHOLD;
    int batch = K_AUTO_BATCH;
    int maxItems = K_AUTO_MAX_ITEMS;
    bool appending = false;
    int lastSizeTriggered = -1;
};
static AutoAppendConfig g_auto;

/**
 * 根据索引获取主轴尺寸
 * @param idx 索引值
 * @return 主轴尺寸
 */
static inline float MainSizeByIndex(int32_t idx)
{
    if (K_MAIN_SEQ_COUNT == 0U) {
        return K_MAIN_C;
    }

    const size_t i = static_cast<size_t>(idx) % K_MAIN_SEQ_COUNT;
    return K_MAIN_SEQ[i];
}

/**
 * 根据索引获取颜色
 * @param index 索引值
 * @return 颜色值
 */
static inline uint32_t ColorByIndex(int index)
{
    if (K_PALETTE_COUNT == 0U) {
        return 0xFFFFFFFFU;
    }

    const size_t i = static_cast<size_t>(index) % K_PALETTE_COUNT;
    return K_PALETTE[i];
}

static inline void BindText(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle flowItem, int32_t index)
{
    ArkUI_NodeHandle text = api->getFirstChild(flowItem);
    if (!text) {
        return;
    }

    SetTextContent(api, text, gItems[static_cast<size_t>(index)].c_str());
    SetAttributeFloat32(api, text, NODE_FONT_SIZE, K_FONT_SIZE);
}

/**
 * 方法描述
 * @param total 参数描述
 * @return 返回值描述
 */
static inline bool ReachedBoundary(int total)
{
    return (total >= g_auto.maxItems) || (total == g_auto.lastSizeTriggered);
}

static inline bool ShouldAppend(int32_t index, int total)
{
    return g_auto.enabled && !g_auto.appending && !ReachedBoundary(total) && index >= (total - g_auto.threshold);
}

static void AppendBatchInternal(int addCount)
{
    if (!gAdapter || !gSection || !gNode || addCount <= 0) {
        return;
    }

    const int32_t start = static_cast<int32_t>(gItems.size());
    gItems.reserve(gItems.size() + static_cast<size_t>(addCount));

    for (int i = 0; i < addCount; ++i) {
        gItems.emplace_back(std::string(K_ITEM_TITLE_PREFIX) + std::to_string(start + i));
    }

    gAdapter->InsertRange(start, addCount);

    const int32_t newCount = static_cast<int32_t>(gItems.size());
    OH_ArkUI_WaterFlowSectionOption_SetItemCount(gSection->GetSectionOptions(), 0, newCount);

    gNode->SetSection(gSection);
    g_auto.lastSizeTriggered = static_cast<int>(gItems.size());
}

static void MaybeAppendOnTail(int32_t index)
{
    const int total = static_cast<int>(gItems.size());
    if (!ShouldAppend(index, total)) {
        return;
    }

    g_auto.appending = true;
    const int remain = g_auto.maxItems - total;
    const int toAdd = remain > 0 ? std::min(g_auto.batch, remain) : 0;
    AppendBatchInternal(toAdd);
    g_auto.appending = false;
}

static int32_t AdapterGetTotalCount()
{
    return static_cast<int32_t>(gItems.size());
}

static uint64_t AdapterGetStableId(int32_t i)
{
    const std::string &key = gItems[static_cast<size_t>(i)];
    return static_cast<uint64_t>(std::hash<std::string>{}(key));
}

static ArkUI_NodeHandle AdapterOnCreate(ArkUI_NativeNodeAPI_1 *api, int32_t /*index*/)
{
    if (!api) {
        return nullptr;
    }

    ArkUI_NodeHandle text = api->createNode(ARKUI_NODE_TEXT);
    ArkUI_NodeHandle item = api->createNode(ARKUI_NODE_FLOW_ITEM);
    api->addChild(item, text);
    return item;
}

static void AdapterOnBind(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle item, int32_t index)
{
    SetAttributeFloat32(api, item, NODE_HEIGHT, MainSizeByIndex(index));
    SetAttributeFloat32(api, item, NODE_WIDTH_PERCENT, K_WIDTH_PERCENT_FULL);
    SetAttributeUInt32(api, item, NODE_BACKGROUND_COLOR, ColorByIndex(index));
    BindText(api, item, index);
    MaybeAppendOnTail(index);
}

static ArkUINodeAdapter::Callbacks MakeCallbacks()
{
    ArkUINodeAdapter::Callbacks cb{};
    cb.getTotalCount = &AdapterGetTotalCount;
    cb.getStableId = &AdapterGetStableId;
    cb.onCreate = &AdapterOnCreate;
    cb.onBind = &AdapterOnBind;
    cb.onRecycle = nullptr;
    return cb;
}

static ArkUI_NodeHandle CreateFooter()
{
    ArkUI_NativeNodeAPI_1 *api = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, api);
    if (!api) {
        return nullptr;
    }

    ArkUI_NodeHandle text = api->createNode(ARKUI_NODE_TEXT);
    SetTextContent(api, text, "到底啦…");
    SetAttributeFloat32(api, text, NODE_FONT_SIZE, 14.0f);

    ArkUI_NodeHandle footer = api->createNode(ARKUI_NODE_FLOW_ITEM);
    SetAttributeFloat32(api, footer, NODE_WIDTH_PERCENT, 1.0f);
    SetAttributeFloat32(api, footer, NODE_HEIGHT, 48.0f);
    SetAttributeUInt32(api, footer, NODE_BACKGROUND_COLOR, 0x11000000U);
    api->addChild(footer, text);
    return footer;
}

static void SetupSection()
{
    ArkUI_Margin margin{K_MARGIN_TOP, K_MARGIN_RIGHT, K_MARGIN_BOTTOM, K_MARGIN_LEFT};

    SingleSectionParams params{};
    params.itemCount = static_cast<int32_t>(gItems.size());
    params.crossCount = K_CROSS_COUNT;
    params.colGap = K_COLUMN_GAP;
    params.rowGap = K_ROW_GAP;
    params.margin = margin;
    params.getMainSizeByIndex = &MainSizeByIndex;
    params.userData = nullptr;
    params.getMainSizeByIndexWithUserData = nullptr;

    gNode->SetSingleSection(params);
    gSection = gNode->GetWaterFlowSection();
}

static void SetupNodeAndAdapter()
{
    gNode = std::make_shared<WaterFlow>();
    gNode->SetHeight(K_WATER_FLOW_H);
    gNode->SetWidth(K_WATER_FLOW_W);
    gNode->SetScrollCommon();
    gNode->SetLayoutDirection(K_LAYOUT_DIRECTION_RTL);
    gNode->SetColumnTemplate(K_COLUMN_TEMPLATE);
    gNode->SetRowTemplate(K_ROW_TEMPLATE);
    gNode->SetGaps(K_COLUMN_GAP, K_ROW_GAP);
    gNode->SetCachedCount(K_CACHED_ITEM_COUNT);
    gNode->SetItemConstraintSize(K_ITEM_MAIN_MIN, K_ITEM_MAIN_MAX);
    gNode->SetLayoutMode(ARKUI_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW);
    gNode->SetSyncLoad(K_SYNC_LOAD);

    SetupSection();

    if (ArkUI_NodeHandle footer = CreateFooter()) {
        gNode->SetFooter(footer);
    }

    gAdapter = std::make_shared<ArkUINodeAdapter>();
    gAdapter->SetCallbacks(MakeCallbacks());
    gNode->SetLazyAdapter(gAdapter);
    gAdapter->ReloadAllItems();
}

static void InitData()
{
    gItems.clear();
    gItems.reserve(static_cast<size_t>(K_INIT_RESERVE));
    for (int i = 0; i < K_INIT_SEED; ++i) {
        gItems.emplace_back(std::string(K_ITEM_TITLE_PREFIX) + std::to_string(i));
    }
}

static ArkUI_NodeHandle BuildWaterFlow()
{
    InitData();
    SetupNodeAndAdapter();
    return gNode->GetWaterFlow();
}

ArkUI_NodeHandle WaterFlow::CreateWaterFlowInfiniteScrollingEarly()
{
    ArkUI_NativeNodeAPI_1 *api = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, api);
    if (!api) {
        return nullptr;
    }

    ArkUI_NodeHandle page = api->createNode(ARKUI_NODE_COLUMN);
    if (!page) {
        return nullptr;
    }
    SetAttributeFloat32(api, page, NODE_WIDTH_PERCENT, 1.0f);
    SetAttributeFloat32(api, page, NODE_HEIGHT_PERCENT, 1.0f);

    ArkUI_NodeHandle waterflow = BuildWaterFlow();
    if (waterflow) {
        SetAttributeFloat32(api, waterflow, NODE_WIDTH_PERCENT, 1.0f);
        SetAttributeFloat32(api, waterflow, NODE_LAYOUT_WEIGHT, 1.0f);

        api->addChild(page, waterflow);
    }
    return page;
}
