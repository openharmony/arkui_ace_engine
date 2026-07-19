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

#ifndef SCROLLABLE_COMPONENT_COMPONENTS_WATERFLOW_H
#define SCROLLABLE_COMPONENT_COMPONENTS_WATERFLOW_H

#include <functional>
#include <memory>
#include <vector>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <hilog/log.h>

#include "common/ArkUINodeAdapter.h"
#include "WaterFlowSection.h"
#include "common/ArkUINode.h"
#include "common/ArkUIUtils.h"
#include "common/ArkUIScrollEvents.h"

#ifndef LOG_TAG
#define LOG_TAG "WaterFlow"
#endif

// ===== 业务常量 =====
constexpr unsigned int K_LOG_DOMAIN = 0xFF00;
constexpr float K_DEFAULT_SCROLL_BAR_WIDTH = 4.0f;
constexpr uint32_t K_DEFAULT_SCROLL_BAR_COLOR = 0x66000000U;
constexpr float K_DEFAULT_SCROLL_FRICTION = 0.12f;
constexpr float K_DEFAULT_FLING_SPEED_LIMIT = 2800.0f;
// 渐隐边缘尺寸
constexpr int32_t K_DEFAULT_FADING_EDGE = 12;
// 单分组索引
constexpr int32_t K_SINGLE_SECTION_INDEX = 0;

// ---- 新增：单分组配置结构体 ----
struct SingleSectionParams {
    int32_t itemCount = 0;
    int32_t crossCount = 1;
    float colGap = 0.0f;
    float rowGap = 0.0f;
    ArkUI_Margin margin{}; // {top,right,bottom,left}

    // 必填：按 index 计算主轴尺寸的回调
    float (*getMainSizeByIndex)(int32_t) = nullptr;

    // 可选：带 userData 的回调
    void *userData = nullptr;
    float (*getMainSizeByIndexWithUserData)(int32_t, void *) = nullptr;
};

class WaterFlow {
public:
    static ArkUI_NodeHandle CreateWaterFlowInfiniteScrollingEarly();
    static ArkUI_NodeHandle CreateWaterFlowCapiShowcase();

    WaterFlow()
    {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, api_);
        waterFlow_ = api_->createNode(ARKUI_NODE_WATER_FLOW);
        api_->addNodeEventReceiver(waterFlow_, StaticEvent);

        scrollGuard_.Bind(api_, waterFlow_, this, SCROLL_EVT_ALL);

        OH_LOG_Print(LOG_APP, LOG_INFO, K_LOG_DOMAIN, LOG_TAG, "WaterFlowNode created");
    }

    ~WaterFlow()
    {
        for (auto event : waterFlowEvents_) {
            api_->unregisterNodeEvent(waterFlow_, event);
        }
        waterFlowEvents_.clear();
        scrollGuard_.Release();

        adapter_.reset();
        section_.reset();
        waterFlow_ = nullptr;
    }

    // ---- Size ----
    void SetWidth(float width)
    {
        SetAttributeFloat32(api_, waterFlow_, NODE_WIDTH, width);
    }

    void SetHeight(float height)
    {
        SetAttributeFloat32(api_, waterFlow_, NODE_HEIGHT, height);
    }

    // ---- Adapter ----
    void SetLazyAdapter(const std::shared_ptr<ArkUINodeAdapter> &adapter)
    {
        if (adapter == nullptr) {
            return;
        }
        ArkUI_AttributeItem item{nullptr, 0, nullptr, adapter->GetAdapter()};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_NODE_ADAPTER, &item);
        adapter_ = adapter;
    }

    // ---- Section ----
    void SetSection(const std::shared_ptr<WaterFlowSection> &section)
    {
        if (section == nullptr) {
            return;
        }
        auto *opts = section->GetSectionOptions();
        if (opts == nullptr) {
            return;
        }
        ArkUI_NumberValue start[] = {{.i32 = K_SINGLE_SECTION_INDEX}};
        ArkUI_AttributeItem item{start, 1, nullptr, opts};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_SECTION_OPTION, &item);
        section_ = section;
    }

    void ResetSection()
    {
        api_->resetAttribute(waterFlow_, NODE_WATER_FLOW_SECTION_OPTION);
        section_.reset();
    }

    // ---- Layout / template / gap ----
    void SetLayoutDirection(int32_t direction)
    {
        ArkUI_NumberValue v[] = {{.i32 = direction}};
        ArkUI_AttributeItem item{v, 1};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_LAYOUT_DIRECTION, &item);
    }

    void SetColumnTemplate(const char *tpl)
    {
        ArkUI_AttributeItem item{nullptr, 0, tpl, nullptr};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_COLUMN_TEMPLATE, &item);
    }

    void SetRowTemplate(const char *tpl)
    {
        ArkUI_AttributeItem item{nullptr, 0, tpl, nullptr};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_ROW_TEMPLATE, &item);
    }

    void SetGaps(float colGap, float rowGap)
    {
        SetAttributeFloat32(api_, waterFlow_, NODE_WATER_FLOW_COLUMN_GAP, colGap);
        SetAttributeFloat32(api_, waterFlow_, NODE_WATER_FLOW_ROW_GAP, rowGap);
    }

    // ---- Cache / scroll / mode ----
    void SetCachedCount(int32_t count)
    {
        SetAttributeInt32(api_, waterFlow_, NODE_WATER_FLOW_CACHED_COUNT, count);
    }

    void SetCachedCount(int32_t count, bool showCached)
    {
        ArkUI_NumberValue v[] = {{.i32 = count}, {.i32 = showCached ? 1 : 0}};
        ArkUI_AttributeItem item{v, 2};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_CACHED_COUNT, &item);
    }

    void SetFooter(ArkUI_NodeHandle footer)
    {
        ArkUI_AttributeItem item{nullptr, 0, nullptr, footer};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_FOOTER, &item);
    }

    void ResetFooter()
    {
        api_->resetAttribute(waterFlow_, NODE_WATER_FLOW_FOOTER);
    }

    void ScrollToIndex(int32_t index, int32_t align)
    {
        ArkUI_NumberValue v[] = {{.i32 = index}, {.i32 = align}};
        ArkUI_AttributeItem item{v, 2};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_SCROLL_TO_INDEX, &item);
    }

    void ScrollToIndex(int32_t index, bool animation, int32_t align, float extraOffset)
    {
        ArkUI_NumberValue v[] = {
            {.i32 = index}, {.i32 = animation ? 1 : 0}, {.i32 = align}, {.f32 = extraOffset}};
        ArkUI_AttributeItem item{v, 4};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_SCROLL_TO_INDEX, &item);
    }

    void SetItemConstraintSize(float minWidth, float maxWidth, float minHeight, float maxHeight)
    {
        ArkUI_NumberValue v[] = {{.f32 = minWidth}, {.f32 = maxWidth}, {.f32 = minHeight}, {.f32 = maxHeight}};
        ArkUI_AttributeItem item{v, 4};
        api_->setAttribute(waterFlow_, NODE_WATER_FLOW_ITEM_CONSTRAINT_SIZE, &item);
    }

    void SetItemConstraintSize(float mainMin, float mainMax)
    {
        SetItemConstraintSize(0.0f, 10000.0f, mainMin, mainMax);
    }

    void SetColumnTemplateItemFillPolicy(int32_t policy)
    {
        constexpr auto attr = static_cast<ArkUI_NodeAttributeType>(1010013);
        ArkUI_NumberValue v[] = {{.i32 = policy}};
        ArkUI_AttributeItem item{v, 1};
        api_->setAttribute(waterFlow_, attr, &item);
    }

    void SetSupportEmptyBranchInLazyLoading(bool enabled)
    {
        constexpr auto attr = static_cast<ArkUI_NodeAttributeType>(1010014);
        ArkUI_NumberValue v[] = {{.i32 = enabled ? 1 : 0}};
        ArkUI_AttributeItem item{v, 1};
        api_->setAttribute(waterFlow_, attr, &item);
    }

    void SetLayoutMode(ArkUI_WaterFlowLayoutMode mode)
    {
        SetAttributeInt32(api_, waterFlow_, NODE_WATER_FLOW_LAYOUT_MODE, static_cast<int32_t>(mode));
    }

    void SetSyncLoad(bool enabled)
    {
        SetAttributeInt32(api_, waterFlow_, NODE_WATER_FLOW_SYNC_LOAD, enabled ? 1 : 0);
    }

    void SetScrollFriction(float f)
    {
        SetAttributeFloat32(api_, waterFlow_, NODE_SCROLL_FRICTION, f);
    }

    void SetFlingSpeedLimit(float limit)
    {
        SetAttributeFloat32(api_, waterFlow_, NODE_SCROLL_FLING_SPEED_LIMIT, limit);
    }

    void SetFadingEdge(int32_t fadingEdge)
    {
        SetAttributeInt32(api_, waterFlow_, NODE_SCROLL_FADING_EDGE, fadingEdge);
    }

    void SetScrollBar(int32_t displayMode)
    {
        SetAttributeInt32(api_, waterFlow_, NODE_SCROLL_BAR_DISPLAY_MODE, displayMode);
    }

    void SetScrollBarWidth(float width)
    {
        SetAttributeFloat32(api_, waterFlow_, NODE_SCROLL_BAR_WIDTH, width);
    }

    void SetScrollBarColor(uint32_t color)
    {
        SetAttributeUInt32(api_, waterFlow_, NODE_SCROLL_BAR_COLOR, color);
    }

    void SetScrollEnabled(bool enabled)
    {
        SetAttributeInt32(api_, waterFlow_, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, enabled ? 1 : 0);
    }

    void SetNestedScroll(int32_t forward, int32_t backward)
    {
        ArkUI_NumberValue v[] = {{.i32 = forward}, {.i32 = backward}};
        ArkUI_AttributeItem item{v, 2};
        api_->setAttribute(waterFlow_, NODE_SCROLL_NESTED_SCROLL, &item);
    }

    void SetEdgeEffect(int32_t edgeEffect, bool alwaysEnabled, int32_t effectEdge)
    {
        ArkUI_NumberValue v[] = {
            {.i32 = edgeEffect}, {.i32 = alwaysEnabled ? 1 : 0}, {.i32 = effectEdge}};
        ArkUI_AttributeItem item{v, 3};
        api_->setAttribute(waterFlow_, NODE_SCROLL_EDGE_EFFECT, &item);
    }

    void ScrollBy(float hDistance, float vDistance)
    {
        ArkUI_NumberValue v[] = {{.f32 = hDistance}, {.f32 = vDistance}};
        ArkUI_AttributeItem item{v, 2};
        api_->setAttribute(waterFlow_, NODE_SCROLL_BY, &item);
    }

    void ScrollTo(float hOffset, float vOffset)
    {
        ArkUI_NumberValue v[] = {{.f32 = hOffset}, {.f32 = vOffset}};
        ArkUI_AttributeItem item{v, 2};
        api_->setAttribute(waterFlow_, NODE_SCROLL_OFFSET, &item);
    }

    void ScrollPage(bool next, bool animation)
    {
        ArkUI_NumberValue v[] = {{.i32 = next ? 1 : 0}, {.i32 = animation ? 1 : 0}};
        ArkUI_AttributeItem item{v, 2};
        api_->setAttribute(waterFlow_, NODE_SCROLL_PAGE, &item);
    }

    void ScrollEdge(int32_t edge)
    {
        ArkUI_NumberValue v[] = {{.i32 = edge}};
        ArkUI_AttributeItem item{v, 1};
        api_->setAttribute(waterFlow_, NODE_SCROLL_EDGE, &item);
    }

    void RegisterWaterFlowEvents()
    {
        if (waterFlowEventsRegistered_ || api_ == nullptr || waterFlow_ == nullptr) {
            return;
        }
        const ArkUI_NodeEventType events[] = {
            NODE_ON_WILL_SCROLL,
            NODE_WATER_FLOW_ON_DID_SCROLL,
            NODE_WATER_FLOW_ON_SCROLL_INDEX,
        };
        for (auto event : events) {
            api_->registerNodeEvent(waterFlow_, event, 0, this);
            waterFlowEvents_.push_back(event);
        }
        waterFlowEventsRegistered_ = true;
    }

    void SetEventHandler(std::function<void(ArkUI_NodeEvent*)> handler)
    {
        eventHandler_ = std::move(handler);
    }

    // ---- 通用滚动外观/行为预设 ----
    void SetScrollCommon()
    {
        // 滚动条外观
        SetAttributeInt32(api_, waterFlow_, NODE_SCROLL_BAR_DISPLAY_MODE,
                          static_cast<int>(ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO));
        SetAttributeFloat32(api_, waterFlow_, NODE_SCROLL_BAR_WIDTH, K_DEFAULT_SCROLL_BAR_WIDTH);
        SetAttributeUInt32(api_, waterFlow_, NODE_SCROLL_BAR_COLOR, K_DEFAULT_SCROLL_BAR_COLOR);

        // 交互与摩擦
        SetAttributeInt32(api_, waterFlow_, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, 1);
        SetAttributeFloat32(api_, waterFlow_, NODE_SCROLL_FRICTION, K_DEFAULT_SCROLL_FRICTION);
        SetAttributeFloat32(api_, waterFlow_, NODE_SCROLL_FLING_SPEED_LIMIT, K_DEFAULT_FLING_SPEED_LIMIT);

        // 嵌套滚动策略 & 渐隐边缘
        SetNestedScroll(ARKUI_SCROLL_NESTED_MODE_SELF_FIRST, ARKUI_SCROLL_NESTED_MODE_SELF_FIRST);
        SetAttributeInt32(api_, waterFlow_, NODE_SCROLL_FADING_EDGE, K_DEFAULT_FADING_EDGE);
    }

    ArkUI_NodeHandle GetWaterFlow() const
    {
        return waterFlow_;
    }

    std::shared_ptr<WaterFlowSection> GetWaterFlowSection() const
    {
        return section_;
    }

    void SetSingleSection(const SingleSectionParams &p)
    {
        if (!ValidateSingleSectionParams(p)) {
            return;
        }

        EnsureSectionSized(1);

        SectionOption opt = BuildSectionOption(p.itemCount, p.crossCount, p.colGap, p.rowGap, p.margin);
        opt.onGetItemMainSizeByIndex = p.getMainSizeByIndex;
        opt.userData = p.userData;

        ApplySectionOption(opt);
        RegisterUserDataCallbackIfNeeded(p.userData, p.getMainSizeByIndexWithUserData);
        SetSection(section_);
    }

private:
    static void StaticEvent(ArkUI_NodeEvent *ev)
    {
        auto *self = reinterpret_cast<WaterFlow *>(OH_ArkUI_NodeEvent_GetUserData(ev));
        if (self != nullptr) {
            self->OnEvent(ev);
        }
    }

    void OnEvent(ArkUI_NodeEvent *ev)
    {
        if (eventHandler_) {
            eventHandler_(ev);
        }
    }

    static bool ValidateSingleSectionParams(const SingleSectionParams &p)
    {
        if (p.getMainSizeByIndex == nullptr) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "getMainSizeByIndex is null");
            return false;
        }
        if (p.itemCount < 0 || p.crossCount <= 0) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG,
                         "invalid counts: itemCount=%{public}d, crossCount=%{public}d", p.itemCount, p.crossCount);
            return false;
        }
        return true;
    }

    void EnsureSectionSized(int32_t sectionCount)
    {
        if (section_ == nullptr) {
            section_ = std::make_shared<WaterFlowSection>();
        }
        section_->Resize(sectionCount);
    }

    SectionOption BuildSectionOption(int32_t itemCount, int32_t crossCount, float colGap, float rowGap,
                                     ArkUI_Margin margin) const
    {
        SectionOption opt{};
        opt.itemsCount = itemCount;
        opt.crossCount = crossCount;
        opt.columnsGap = colGap;
        opt.rowsGap = rowGap;
        opt.margin = margin;
        return opt;
    }

    void ApplySectionOption(const SectionOption &opt)
    {
        section_->SetSection(section_->GetSectionOptions(), K_SINGLE_SECTION_INDEX, opt);
    }

    void RegisterUserDataCallbackIfNeeded(void *userData, float (*cb)(int32_t, void *))
    {
        if (userData != nullptr && cb != nullptr) {
            OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
                section_->GetSectionOptions(), K_SINGLE_SECTION_INDEX, userData, cb);
        }
    }

private:
    ArkUI_NativeNodeAPI_1 *api_ = nullptr;
    ArkUI_NodeHandle waterFlow_ = nullptr;
    std::shared_ptr<WaterFlowSection> section_ = nullptr;
    std::shared_ptr<ArkUINodeAdapter> adapter_;
    std::function<void(ArkUI_NodeEvent*)> eventHandler_;
    std::vector<ArkUI_NodeEventType> waterFlowEvents_;
    bool waterFlowEventsRegistered_ = false;

    ScrollEventGuard scrollGuard_;
};

#endif // SCROLLABLE_COMPONENT_COMPONENTS_WATERFLOW_H
