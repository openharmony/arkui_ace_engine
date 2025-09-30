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
#include <atomic>
#include <chrono>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <napi/native_api.h>

#include <hilog/log.h>
#ifndef LOG_TAG
#define LOG_TAG "Refresh"
#endif

#include "common/ArkUINode.h"
#include "common/ArkUINodeAdapter.h"
#include "components/refresh/Refresh.h"
#include "components/list/List.h"
#include "components/list/ListItemSwipe.h"
#include "components/list/ListItemGroup.h"

// ================= 业务常量 =================
namespace {

constexpr uint32_t K_COLOR_PAGE_BG = 0xFFF1F3F5U;
constexpr uint32_t K_ITEM_BG_COLOR = 0xFFFFFFFFU;
constexpr const char *K_LOADING_TEXT = "加载中…";
constexpr float K_ITEM_FONT_SIZE = 16.0f;

constexpr int K_INIT_COUNT = 10;
constexpr int K_LOAD_BATCH = 10;
constexpr int K_MAX_ITEMS = 100;
constexpr int K_REFRESH_PREPEND_COUNT = 5;
constexpr int K_MIN_REFRESH_MS = 350;

constexpr float K_WIDTH_PERCENT_FULL = 1.0f;
constexpr float K_HEIGHT_PERCENT_FULL = 1.0f;
constexpr float K_LIST_SPACE = 12.0f;

constexpr float K_REFRESH_OFFSET_VP = 64.0f;
constexpr float K_MAX_PULL_VP = 128.0f;
constexpr float K_PULL_DOWN_RATIO = 0.6f;

constexpr bool K_LIST_CLIP_CONTENT = true;
constexpr bool K_LIST_EDGE_SPRING = true;
constexpr bool K_LIST_SCROLLBAR_VISIBLE = false;

constexpr int K_MIN_INDEX = 0;
constexpr int K_LAST_INDEX_OFFSET = 1;

// 样式
constexpr float K_ROW_HEIGHT = 80.0f;
constexpr float K_FOOTER_HEIGHT = 64.0f;

constexpr int64_t K_FOOTER_STABLE_ID = -16;

} // namespace

namespace {
constexpr int RET_OK = 0;

inline bool Ok(int rc, const char *what)
{
    if (rc != RET_OK) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, LOG_TAG, "%{public}s failed rc=%{public}d", what, rc);
        return false;
    }
    return true;
}
} // namespace

// ================= 状态 =================
namespace {

struct RefreshListState {
    std::shared_ptr<ArkUINodeAdapter> adapter;
    std::vector<std::string> data;
    bool showLoadingFooter = false;

    int total = K_INIT_COUNT; // 逻辑总数（与 data.size() 同步增长）
    int lastTriggeredTot = -1;
    bool loading = false;

    bool NoMore() const
    {
        return total >= K_MAX_ITEMS;
    }

    int ItemsCount() const
    {
        return static_cast<int>(data.size());
    }
    int RenderCount() const
    {
        return ItemsCount() + (showLoadingFooter ? 1 : 0);
    }
};

} // namespace

// ================= 业务工具 =================
namespace {

/**
 * 添加加载状态尾部
 * @param st 刷新列表状态
 */
inline void AddLoadingFooter(const std::shared_ptr<RefreshListState> &st)
{
    const int footerIndex = st->ItemsCount();
    st->adapter->InsertRange(footerIndex, 1);
    st->showLoadingFooter = true;
}

/**
 * 移除加载状态尾部
 * @param st 刷新列表状态
 */
inline void RemoveLoadingFooter(const std::shared_ptr<RefreshListState> &st)
{
    const int footerIndex = st->ItemsCount();
    st->adapter->RemoveRange(footerIndex, 1);
    st->showLoadingFooter = false;
}

/**
 * 切换加载状态尾部显示
 * @param st 刷新列表状态
 * @param on 是否显示
 */
static void ToggleLoadingFooter(const std::shared_ptr<RefreshListState> &st, bool on)
{
    if (!st || !st->adapter) {
        return;
    }

    if (on && !st->showLoadingFooter) {
        AddLoadingFooter(st);
    } else if (!on && st->showLoadingFooter) {
        RemoveLoadingFooter(st);
    }
}

/**
 * 末尾追加批量数据
 * @param st 刷新列表状态
 * @param add 添加数量
 */
static void AppendTailBatch(const std::shared_ptr<RefreshListState> &st, int add)
{
    if (!st || !st->adapter) {
        return;
    }

    const int base = st->total;
    const int addClamped = std::min(add, K_MAX_ITEMS - base);
    if (addClamped <= 0) {
        return;
    }

    // 先去掉 footer，再插入数据，再恢复 footer（避免 index 混淆）
    const bool hadFooter = st->showLoadingFooter;
    ToggleLoadingFooter(st, false);

    st->data.reserve(st->data.size() + static_cast<size_t>(addClamped));
    for (int i = 0; i < addClamped; ++i) {
        st->data.emplace_back(std::to_string(base + i));
    }
    st->adapter->InsertRange(base, addClamped);

    st->total += addClamped;
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "AppendTailBatch add=%{public}d total=%{public}d", addClamped,
                 st->total);

    if (hadFooter) {
        ToggleLoadingFooter(st, true);
    }
}

} // namespace

// ================= 适配器回调（通用 ArkUINodeAdapter） =================
namespace {

/**
 * 创建列表项
 * @param api 原生节点API接口
 * @return 列表项节点句柄
 */
static ArkUI_NodeHandle CreateListItem(ArkUI_NativeNodeAPI_1 *api)
{
    ArkUI_NodeHandle text = api->createNode(ARKUI_NODE_TEXT);
    if (text == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, LOG_TAG, "create TEXT node null");
        return nullptr;
    }
    ArkUI_NodeHandle item = api->createNode(ARKUI_NODE_LIST_ITEM);
    if (item == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, LOG_TAG, "create LIST_ITEM node null");
        return nullptr;
    }

    if (int rc = api->addChild(item, text); !Ok(rc, "addChild(item,text)")) {
        return nullptr;
    }

    SetAttributeFloat32(api, item, NODE_WIDTH_PERCENT, 1.0f);
    SetAttributeUInt32(api, item, NODE_BACKGROUND_COLOR, K_ITEM_BG_COLOR);

    // 让文本也占满宽度
    SetAttributeFloat32(api, text, NODE_WIDTH_PERCENT, 1.0f);
    return item;
}

/**
 * 绑定为普通列表项
 * @param api 原生节点API接口
 * @param item 列表项节点句柄
 * @param txt 文本内容
 */
static void BindAsNormal(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle item, const char *txt)
{
    ArkUI_NodeHandle text = api->getFirstChild(item);
    if (!text) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, LOG_TAG, "BindAsNormal getFirstChild null");
        return;
    }

    // 背景放在 item 上
    SetAttributeUInt32(api, item, NODE_BACKGROUND_COLOR, K_ITEM_BG_COLOR);

    // 文本占满宽度
    SetAttributeFloat32(api, text, NODE_WIDTH_PERCENT, 1.0f);

    SetTextContent(api, text, txt);
    SetAttributeFloat32(api, text, NODE_FONT_SIZE, K_ITEM_FONT_SIZE);
    SetAttributeFloat32(api, text, NODE_HEIGHT, K_ROW_HEIGHT);
    SetAttributeFloat32(api, text, NODE_TEXT_LINE_HEIGHT, K_ROW_HEIGHT);
    SetAttributeInt32(api, text, NODE_TEXT_ALIGN, ARKUI_TEXT_ALIGNMENT_CENTER);
}

/**
 * 绑定为加载尾部项
 * @param api 原生节点API接口
 * @param item 列表项节点句柄
 */
static void BindAsFooter(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle item)
{
    ArkUI_NodeHandle text = api->getFirstChild(item);
    if (!text) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, LOG_TAG, "BindAsFooter getFirstChild null");
        return;
    }

    SetAttributeUInt32(api, item, NODE_BACKGROUND_COLOR, K_ITEM_BG_COLOR);
    SetAttributeFloat32(api, text, NODE_WIDTH_PERCENT, 1.0f);

    SetTextContent(api, text, K_LOADING_TEXT);
    SetAttributeFloat32(api, text, NODE_FONT_SIZE, K_ITEM_FONT_SIZE);
    SetAttributeFloat32(api, text, NODE_HEIGHT, K_FOOTER_HEIGHT);
    SetAttributeFloat32(api, text, NODE_TEXT_LINE_HEIGHT, K_FOOTER_HEIGHT);
    SetAttributeInt32(api, text, NODE_TEXT_ALIGN, ARKUI_TEXT_ALIGNMENT_CENTER);
}

/**
 * 创建节点适配器回调
 * @param st 刷新列表状态
 * @return 节点适配器回调结构
 */
static NodeAdapterCallbacks MakeCallbacks(const std::shared_ptr<RefreshListState> &st)
{
    NodeAdapterCallbacks cb{};

    cb.getTotalCount = [st]() -> int32_t { return st ? st->RenderCount() : 0; };

    cb.getStableId = [st](int32_t i) -> uint64_t {
        if (!st) {
            return static_cast<uint64_t>(i);
        }
        const int items = st->ItemsCount();
        if (st->showLoadingFooter && i == items) {
            return static_cast<uint64_t>(K_FOOTER_STABLE_ID);
        }
        if (i >= 0 && i < items) {
            return static_cast<uint64_t>(std::hash<std::string>{}(st->data[static_cast<size_t>(i)]));
        }
        return static_cast<uint64_t>(i);
    };

    cb.onCreate = [](ArkUI_NativeNodeAPI_1 *api, int32_t /*index*/) -> ArkUI_NodeHandle { return CreateListItem(api); };

    cb.onBind = [st](ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle item, int32_t index) {
        if (!st) {
            return;
        }

        const int items = st->ItemsCount();
        if (st->showLoadingFooter && index == items) {
            BindAsFooter(api, item);
            return;
        }
        if (index >= 0 && index < items) {
            BindAsNormal(api, item, st->data[static_cast<size_t>(index)].c_str());
            return;
        }
        BindAsNormal(api, item, "<invalid>");
    };

    return cb;
}

/**
 * 创建 ArkUINodeAdapter
 */
static std::shared_ptr<ArkUINodeAdapter> MakeListAdapter(const std::shared_ptr<RefreshListState> &st)
{
    std::shared_ptr<ArkUINodeAdapter> adapter =
        std::make_shared<ArkUINodeAdapter>(static_cast<int32_t>(ARKUI_NODE_LIST_ITEM));
    adapter->SetCallbacks(MakeCallbacks(st));
    return adapter;
}

} // namespace

// ================= 视图拼装 =================
namespace {

/**
 * 创建根节点
 * @return 根节点智能指针
 */
static std::shared_ptr<BaseNode> MakeRoot()
{
    ArkUI_NativeNodeAPI_1 *api = NodeApiInstance::GetInstance()->GetNativeNodeAPI();
    ArkUI_NodeHandle h = api->createNode(ARKUI_NODE_COLUMN);

    std::shared_ptr<BaseNode> root = std::make_shared<BaseNode>(h);
    root->SetWidthPercent(K_WIDTH_PERCENT_FULL);
    root->SetHeightPercent(K_HEIGHT_PERCENT_FULL);
    SetAttributeUInt32(api, root->GetHandle(), NODE_BACKGROUND_COLOR, K_COLOR_PAGE_BG);
    return root;
}

static void ConfigureList(const std::shared_ptr<List> &list)
{
    list->SetWidthPercent(K_WIDTH_PERCENT_FULL);
    list->SetHeightPercent(K_HEIGHT_PERCENT_FULL);
    list->SetTransparentBackground();
    list->SetClipContent(K_LIST_CLIP_CONTENT);
    list->SetEdgeEffectSpring(K_LIST_EDGE_SPRING);
    list->SetScrollBarState(K_LIST_SCROLLBAR_VISIBLE);
    list->SetSpace(K_LIST_SPACE);
    list->SetNestedScrollMode(List::kNestedScrollParentFirst);
}

/**
 * 创建列表节点
 * @param group 列表项组节点
 * @return 列表节点智能指针
 */
inline std::shared_ptr<List> MakeList(const std::shared_ptr<ListItemGroupNode> &group)
{
    std::shared_ptr<List> list = std::make_shared<List>();
    ConfigureList(list);
    list->AddChild(std::static_pointer_cast<BaseNode>(group));
    return list;
}

/**
 * 创建刷新节点
 * @param list 列表节点
 * @return 刷新节点智能指针
 */
static std::shared_ptr<Refresh> MakeRefresh(const std::shared_ptr<List> &list)
{
    std::shared_ptr<Refresh> refresh = std::make_shared<Refresh>();
    refresh->AttachChild(list);
    refresh->SetTransparentBackground();
    refresh->SetPullToRefresh(true);
    refresh->SetRefreshOffset(K_REFRESH_OFFSET_VP);
    refresh->SetPullDownRatio(K_PULL_DOWN_RATIO);
    refresh->SetMaxPullDownDistance(K_MAX_PULL_VP);
    return refresh;
}

// 触底加载
static void WireReachEnd(const std::shared_ptr<RefreshListState> &st, const std::shared_ptr<List> &list)
{
    list->RegisterOnReachEnd([st, list]() {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "OnReachEnd triggered");

        if (!st || st->loading || st->lastTriggeredTot == st->total) {
            return;
        }
        st->lastTriggeredTot = st->total;

        if (st->NoMore()) {
            const int count = st->RenderCount();
            const int idx = std::max(K_MIN_INDEX, count - K_LAST_INDEX_OFFSET);
            list->ScrollToIndex(idx);
            return;
        }

        st->loading = true;
        ToggleLoadingFooter(st, true);
        AppendTailBatch(st, K_LOAD_BATCH);
        ToggleLoadingFooter(st, false);
        st->loading = false;
    });
}

static void OnVisibleChangeCore(const std::shared_ptr<RefreshListState> &st, const std::shared_ptr<List> &list,
                                int32_t endIdxInGroup)
{
    if (!st) {
        return;
    }

    const int items = st->ItemsCount();
    if (items <= 0) {
        return;
    }

    if (endIdxInGroup < items - K_LAST_INDEX_OFFSET) {
        return;
    }

    if (st->loading || st->lastTriggeredTot == st->total) {
        return;
    }

    st->lastTriggeredTot = st->total;

    if (st->NoMore()) {
        const int count = st->RenderCount();
        const int idx = std::max(K_MIN_INDEX, count - K_LAST_INDEX_OFFSET);
        list->ScrollToIndex(idx);
        return;
    }

    st->loading = true;
    ToggleLoadingFooter(st, true);
    AppendTailBatch(st, K_LOAD_BATCH);
    ToggleLoadingFooter(st, false);
    st->loading = false;
}

inline void WireVisibleChange(const std::shared_ptr<RefreshListState> &st, const std::shared_ptr<List> &list)
{
    using V = List::VisibleContentChange;
    list->RegisterOnVisibleContentChange([st, list](const V &ev) {
        const int32_t endIdx = ev.EndOnItem() ? ev.endItemIndex : -1;
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "OnVisibleContentChange endIdxInGroup=%{public}d",
                     endIdx);
        OnVisibleChangeCore(st, list, endIdx);
    });
}

static void PrependNewData(const std::shared_ptr<RefreshListState> &st)
{
    std::vector<std::string> news;
    news.reserve(K_REFRESH_PREPEND_COUNT);
    for (int i = 0; i < K_REFRESH_PREPEND_COUNT; ++i) {
        news.emplace_back(std::string("New Item ") + std::to_string(i));
    }

    const bool hadFooter = st->showLoadingFooter;
    ToggleLoadingFooter(st, false);

    st->data.insert(st->data.begin(), news.begin(), news.end());
    st->adapter->InsertRange(0, K_REFRESH_PREPEND_COUNT);

    st->total = std::min(st->total + K_REFRESH_PREPEND_COUNT, K_MAX_ITEMS);
    st->lastTriggeredTot = -1;

    if (hadFooter) {
        ToggleLoadingFooter(st, true);
    }

    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "OnRefresh prepend=%{public}d total=%{public}d",
                 K_REFRESH_PREPEND_COUNT, st->total);
}

/**
 * 刷新行为
 */
static void WireRefreshBehavior(const std::shared_ptr<RefreshListState> &st, const std::shared_ptr<Refresh> &refresh)
{
    static std::atomic_bool sRefreshing{false};

    refresh->RegisterOnRefresh([st, refresh]() {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "OnRefresh triggered");

        if (sRefreshing.exchange(true)) {
            OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "OnRefresh ignored: busy");
            return;
        }

        using Clock = std::chrono::steady_clock;
        const auto t0 = Clock::now();

        if (st && !st->NoMore()) {
            PrependNewData(st);
        }

        const int elapsedMs =
            static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t0).count());
        const int delay = std::max(0, K_MIN_REFRESH_MS - elapsedMs);

        PostDelayedTask(delay, [refresh]() {
            refresh->SetRefreshing(false);
            OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "OnRefresh complete");
        });

        sRefreshing = false;
    });
}

inline void WireRefreshLogs(const std::shared_ptr<Refresh> &refresh)
{
    refresh->RegisterOnOffsetChange([](float offsetVp) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "OnOffsetChange offsetVp=%{public}f", offsetVp);
    });
    refresh->RegisterOnStateChange([](int32_t state) {
        OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "OnStateChange state=%{public}d", state);
    });
}

/**
 * Build
 */
static std::shared_ptr<BaseNode> Build()
{
    // 根节点
    std::shared_ptr<BaseNode> root = MakeRoot();

    // 分组 + 列表
    std::shared_ptr<ListItemGroupNode> group = std::make_shared<ListItemGroupNode>();
    std::shared_ptr<List> list = MakeList(group);

    // 刷新容器
    std::shared_ptr<Refresh> refresh = MakeRefresh(list);

    // 状态
    std::shared_ptr<RefreshListState> st = std::make_shared<RefreshListState>();
    st->data.reserve(K_MAX_ITEMS);
    for (int i = 0; i < K_INIT_COUNT; ++i) {
        st->data.emplace_back(std::to_string(i));
    }
    st->total = K_INIT_COUNT;

    // 适配器
    st->adapter = MakeListAdapter(st);
    group->SetLazyAdapter(st->adapter);

    // 行为绑定
    WireReachEnd(st, list);
    WireVisibleChange(st, list);
    WireRefreshBehavior(st, refresh);
    WireRefreshLogs(refresh);

    // 组装
    root->AddChild(refresh);

    // keep alive
    GetKeepAliveContainer<BaseNode>().emplace_back(root);
    GetKeepAliveContainer<Refresh>().emplace_back(refresh);
    GetKeepAliveContainer<List>().emplace_back(list);
    GetKeepAliveContainer<ListItemGroupNode>().emplace_back(group);
    static std::vector<std::shared_ptr<RefreshListState>> g_states;
    g_states.emplace_back(st);

    return root;
}
} // namespace

ArkUI_NodeHandle Refresh::CreateRefreshList()
{
    ArkUI_NativeNodeAPI_1 *api = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, api);
    if (api == nullptr) {
        return nullptr;
    }

    ArkUI_NodeHandle page = api->createNode(ARKUI_NODE_COLUMN);
    if (page == nullptr) {
        return nullptr;
    }
    SetAttributeFloat32(api, page, NODE_WIDTH_PERCENT, 1.0f);
    SetAttributeFloat32(api, page, NODE_HEIGHT_PERCENT, 1.0f);

    std::shared_ptr<BaseNode> root = Build();
    if (root && root->GetHandle() != nullptr) {
        SetAttributeFloat32(api, root->GetHandle(), NODE_LAYOUT_WEIGHT, 1.0f);
        api->addChild(page, root->GetHandle());
    }

    return page;
}