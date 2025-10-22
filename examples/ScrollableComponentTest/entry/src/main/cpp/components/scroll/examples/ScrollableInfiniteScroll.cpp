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
 
#include <cmath>
#include <cstdint>

#include "common/ArkUINode.h"
#include "common/ArkUIUtils.h"
#include "components/scroll/Scroll.h"

#include <hilog/log.h>
#ifndef LOG_TAG
#define LOG_TAG "ScrollableInfiniteScroll"
#endif

// ===== 业务常量 =====
namespace {
constexpr float K_WIDTH_PERCENT_FULL = 1.0f;
constexpr float K_HEIGHT_PERCENT_FULL = 1.0f;
constexpr uint32_t K_PAGE_BG = 0xFFFFFF00U; // Yellow

constexpr uint32_t K_COLOR_BROWN = 0xFFA52A2AU;
constexpr uint32_t K_COLOR_BLUE = 0xFF0000FFU;
constexpr uint32_t K_COLOR_GREEN = 0xFF008000U;

constexpr float K_TEXT_SIZE = 100.0f;

// 其他行为参数
constexpr float K_FRICTION = 0.9f;
constexpr float K_FLING_LIMIT = 12000.0f;

constexpr unsigned int K_LOG_DOMAIN = 0xFF00;

// 事件数据数组索引常量
constexpr int32_t K_PRIMARY_DELTA_DATA_INDEX = 0;
constexpr int32_t K_SECONDARY_DELTA_DATA_INDEX = 1;
constexpr int32_t K_AREA_HEIGHT_FALLBACK_DATA_INDEX = 6;
constexpr int32_t K_AREA_HEIGHT_PRIMARY_DATA_INDEX = 7;
} // namespace

// ===== 全局状态 =====
static ArkUI_NativeNodeAPI_1 *gApi{nullptr};
static std::shared_ptr<Scroll> gScroll;
static ArkUI_NodeHandle gRoot{nullptr};
static ArkUI_NodeHandle gPageTop{nullptr};
static ArkUI_NodeHandle gPageMid{nullptr};
static ArkUI_NodeHandle gPageBot{nullptr};

static float g_selfH{0.0f};
static float g_yOffset{0.0f};

// ===== 工具：页面创建与布局 =====
/**
 * 创建页面节点
 * @param bg 背景色
 * @param label 标签文本
 * @return 页面节点句柄
 */
static ArkUI_NodeHandle CreatePage(uint32_t bg, const char *label)
{
    if (gApi == nullptr) {
        return nullptr;
    }

    ArkUI_NodeHandle page = gApi->createNode(ARKUI_NODE_STACK);
    SetAttributeFloat32(gApi, page, NODE_WIDTH_PERCENT, K_WIDTH_PERCENT_FULL);
    SetAttributeFloat32(gApi, page, NODE_HEIGHT_PERCENT, K_HEIGHT_PERCENT_FULL);
    SetAttributeUInt32(gApi, page, NODE_BACKGROUND_COLOR, bg);

    ArkUI_NodeHandle text = gApi->createNode(ARKUI_NODE_TEXT);
    SetTextContent(gApi, text, label);
    SetAttributeFloat32(gApi, text, NODE_FONT_SIZE, K_TEXT_SIZE);

    gApi->addChild(page, text);
    return page;
}

/**
 * 根据索引获取偏移量
 * @param index 索引值
 * @return 偏移量
 */
static inline float GetOffsetByIndex(int index)
{
    float off = g_yOffset - static_cast<float>(index) * g_selfH;
    if (off > 1.5f * g_selfH) {
        off -= 3.0f * g_selfH;
    } else if (off < -1.5f * g_selfH) {
        off += 3.0f * g_selfH;
    }
    return off;
}

static void ApplyTranslate(ArkUI_NodeHandle n, float ty)
{
    ArkUI_NumberValue vx{.f32 = 0.0f};
    ArkUI_NumberValue vy{.f32 = ty};
    ArkUI_NumberValue vz{.f32 = 0.0f};

    ArkUI_NumberValue v[] = {vx, vy, vz};
    ArkUI_AttributeItem it{v, 3};

    gApi->setAttribute(n, NODE_TRANSLATE, &it);
}

static void SyncAllTranslate()
{
    if (gApi == nullptr) {
        return;
    }
    ApplyTranslate(gPageTop, -GetOffsetByIndex(-1));
    ApplyTranslate(gPageMid, -GetOffsetByIndex(0));
    ApplyTranslate(gPageBot, -GetOffsetByIndex(1));
}

// ===== 事件读取辅助 =====
static inline float ReadDeltaPrimary(ArkUI_NodeComponentEvent *ce)
{
    return ce->data[K_PRIMARY_DELTA_DATA_INDEX].f32;
}
static inline float ReadDeltaSecondary(ArkUI_NodeComponentEvent *ce)
{
    return ce->data[K_SECONDARY_DELTA_DATA_INDEX].f32;
}

// ===== 事件处理 =====
static void OnAreaChange(ArkUI_NodeComponentEvent *ce)
{
    if (ce == nullptr) {
        return;
    }

    float h = ce->data[K_AREA_HEIGHT_PRIMARY_DATA_INDEX].f32;
    if (h <= 0.0f) {
        h = ce->data[K_AREA_HEIGHT_FALLBACK_DATA_INDEX].f32;
    }

    if (h > 0.0f && std::fabs(h - g_selfH) > 0.5f) {
        g_selfH = h;
        SyncAllTranslate();
    }
}

static void ApplyScrollDelta(float delta)
{
    if (std::fabs(delta) <= 1e-5f) {
        return;
    }

    g_yOffset += delta;

    const float period = 3.0f * g_selfH;
    if (g_selfH > 0.0f && period > 0.0f) {
        while (g_yOffset < 0.0f) {
            g_yOffset += period;
        }
        while (g_yOffset >= period) {
            g_yOffset -= period;
        }
    }

    SyncAllTranslate();
}

static void OnScrollFrameBegin(ArkUI_NodeComponentEvent *ce)
{
    if (ce == nullptr) {
        return;
    }

    float delta = ReadDeltaPrimary(ce);
    if (std::fabs(delta) < 1e-5f) {
        delta = ReadDeltaSecondary(ce);
    }

    ApplyScrollDelta(delta);

    ce->data[K_PRIMARY_DELTA_DATA_INDEX].f32 = 0.0f;
    ce->data[K_SECONDARY_DELTA_DATA_INDEX].f32 = 0.0f;
}

static void OnScroll(ArkUI_NodeComponentEvent *ce)
{
    if (ce == nullptr) {
        return;
    }
    float delta = ReadDeltaPrimary(ce);
    if (std::fabs(delta) < 1e-5f) {
        delta = ReadDeltaSecondary(ce);
    }
    ApplyScrollDelta(delta);
}

static void OnSimpleLog(const char *tag)
{
    OH_LOG_Print(LOG_APP, LOG_DEBUG, K_LOG_DOMAIN, LOG_TAG, "%{public}s", tag);
}

static bool HandleCoreScrollEvents(int32_t type, ArkUI_NodeComponentEvent *ce)
{
    switch (type) {
        case NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN:
            OnScrollFrameBegin(ce);
            return true;
        case NODE_SCROLL_EVENT_ON_WILL_SCROLL:
            OnSimpleLog("OnWillScroll");
            return true;
        case NODE_SCROLL_EVENT_ON_SCROLL:
            OnScroll(ce);
            return true;
        case NODE_SCROLL_EVENT_ON_DID_SCROLL:
            OnSimpleLog("OnDidScroll");
            return true;
        case NODE_SCROLL_EVENT_ON_SCROLL_START:
            OnSimpleLog("OnScrollStart");
            return true;
        case NODE_SCROLL_EVENT_ON_SCROLL_STOP:
            OnSimpleLog("OnScrollStop");
            return true;
        default:
            return false;
    }
}

static bool HandleBoundaryEvents(int32_t type, ArkUI_NodeComponentEvent * /*ce*/)
{
    switch (type) {
        case NODE_SCROLL_EVENT_ON_REACH_START:
            OnSimpleLog("OnReachStart");
            return true;
        case NODE_SCROLL_EVENT_ON_REACH_END:
            OnSimpleLog("OnReachEnd");
            return true;
        case NODE_SCROLL_EVENT_ON_WILL_STOP_DRAGGING:
            OnSimpleLog("OnWillStopDragging");
            return true;
        case NODE_SCROLL_EVENT_ON_SCROLL_EDGE:
            OnSimpleLog("OnScrollEdge");
            return true;
        default:
            return false;
    }
}

static bool HandleZoomEvents(int32_t type, ArkUI_NodeComponentEvent * /*ce*/)
{
    switch (type) {
        case NODE_SCROLL_EVENT_ON_ZOOM_START:
            OnSimpleLog("OnZoomStart");
            return true;
        case NODE_SCROLL_EVENT_ON_ZOOM_STOP:
            OnSimpleLog("OnZoomStop");
            return true;
        case NODE_SCROLL_EVENT_ON_DID_ZOOM:
            OnSimpleLog("OnDidZoom");
            return true;
        default:
            return false;
    }
}

static void HandleNodeEvent(ArkUI_NodeEvent *ev)
{
    if (ev == nullptr) {
        return;
    }

    int32_t type = OH_ArkUI_NodeEvent_GetEventType(ev);
    ArkUI_NodeComponentEvent *ce = OH_ArkUI_NodeEvent_GetNodeComponentEvent(ev);

    if (type == NODE_EVENT_ON_AREA_CHANGE) {
        OnAreaChange(ce);
        return;
    }

    if (HandleCoreScrollEvents(type, ce)) {
        return;
    }
    if (HandleBoundaryEvents(type, ce)) {
        return;
    }
    if (HandleZoomEvents(type, ce)) {
        return;
    }
}

// ===== 组装构建 =====
static void SetupScroll()
{
    gScroll = std::make_shared<Scroll>();

    gScroll->SetWidthPercent(K_WIDTH_PERCENT_FULL);
    gScroll->SetHeightPercent(K_HEIGHT_PERCENT_FULL);
    gScroll->SetBackgroundColor(K_PAGE_BG);

    gScroll->SetDirection(ARKUI_SCROLL_DIRECTION_VERTICAL);
    gScroll->SetScrollBarDisplayMode(ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF);
    gScroll->SetScrollBarWidth(2.0f);
    gScroll->SetScrollBarColor(0x66000000U);
    gScroll->SetScrollBarMargin(0.0f, 0.0f, 0.0f, 0.0f);

    gScroll->SetEnableScrollInteraction(true);
    gScroll->SetFriction(K_FRICTION);
    gScroll->SetClipContent(true);
    gScroll->SetPageEnabled(false);
    gScroll->SetBackToTopEnabled(false);
    gScroll->SetFadingEdge(0.0f);
    gScroll->SetFlingSpeedLimit(K_FLING_LIMIT);
    gScroll->SetEdgeEffect(ARKUI_EDGE_EFFECT_SPRING, true,
                           static_cast<ArkUI_EffectEdge>(ARKUI_EFFECT_EDGE_START | ARKUI_EFFECT_EDGE_END));
}

static void SetupRootAndPages()
{
    gRoot = gApi->createNode(ARKUI_NODE_STACK);
    SetAttributeFloat32(gApi, gRoot, NODE_WIDTH_PERCENT, K_WIDTH_PERCENT_FULL);
    SetAttributeFloat32(gApi, gRoot, NODE_HEIGHT_PERCENT, K_HEIGHT_PERCENT_FULL);

    gPageTop = CreatePage(K_COLOR_BROWN, "3");
    gPageMid = CreatePage(K_COLOR_BLUE, "1");
    gPageBot = CreatePage(K_COLOR_GREEN, "2");

    gApi->addChild(gRoot, gPageTop);
    gApi->addChild(gRoot, gPageMid);
    gApi->addChild(gRoot, gPageBot);

    gScroll->AddChild(gRoot);
}

static void RegisterEvents()
{
    gApi->addNodeEventReceiver(gScroll->GetScroll(), &HandleNodeEvent);
    gApi->addNodeEventReceiver(gRoot, &HandleNodeEvent);
    gApi->registerNodeEvent(gRoot, NODE_EVENT_ON_AREA_CHANGE, 0, nullptr);
}

/**
 * 构建滚动视图
 * @return 滚动节点句柄
 */
static ArkUI_NodeHandle Build()
{
    gApi = NodeApiInstance::GetInstance()->GetNativeNodeAPI();
    if (gApi == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "GetNativeNodeAPI failed");
        return nullptr;
    }

    SetupScroll();
    SetupRootAndPages();
    RegisterEvents();
    SyncAllTranslate();

    return gScroll->GetScroll();
}

ArkUI_NodeHandle Scroll::CreateScrollableInfiniteScroll()
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

    ArkUI_NodeHandle scroll = Build();
    if (scroll != nullptr) {
        SetAttributeFloat32(api, scroll, NODE_LAYOUT_WEIGHT, 1.0f);
        api->addChild(page, scroll);
    }

    return page;
}
