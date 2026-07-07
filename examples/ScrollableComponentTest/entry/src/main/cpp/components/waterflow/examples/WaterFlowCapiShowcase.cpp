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

#include "components/waterflow/WaterFlow.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <arkui/native_type.h>

namespace {
constexpr float FULL = 1.0f;
constexpr float PAGE_WIDTH = 400.0f;
constexpr float WATERFLOW_HEIGHT = 500.0f;
constexpr int32_t INITIAL_COUNT = 96;
constexpr int32_t APPEND_COUNT = 24;
constexpr int32_t SINGLE_SECTION_COUNT = 1;
constexpr int32_t MIXED_SECTION_COUNT = 3;
constexpr int32_t FIRST_SECTION_INDEX = 0;
constexpr int32_t SECOND_SECTION_INDEX = 1;
constexpr int32_t THIRD_SECTION_INDEX = 2;
constexpr int32_t SECTION_A_COUNT = 24;
constexpr int32_t SECTION_B_COUNT = 36;
constexpr int32_t SINGLE_SECTION_CROSS_COUNT = 2;
constexpr int32_t FIRST_SECTION_CROSS_COUNT = 2;
constexpr int32_t SECOND_SECTION_CROSS_COUNT = 3;
constexpr int32_t THIRD_SECTION_CROSS_COUNT = 4;
constexpr int32_t INITIAL_TARGET_INDEX = 18;
constexpr int32_t TARGET_INDEX_STEP = 17;
constexpr int32_t STABLE_ID_OFFSET = 1000;
constexpr int32_t DEFAULT_CACHED_COUNT = 30;
constexpr int32_t COMPACT_CACHED_COUNT = 12;
constexpr int32_t DEFAULT_FADING_EDGE = 12;
constexpr int32_t RESET_ITEM_FILL_POLICY = -1;
constexpr int32_t DEFAULT_FILL_POLICY_INDEX = 1;
constexpr int32_t DEFAULT_EDGE_EFFECT_INDEX = 0;
constexpr int32_t DEFAULT_ITEM_FILL_POLICY = static_cast<int32_t>(ARKUI_ITEMFILLPOLICY_DEFAULT);
constexpr float CARD_RADIUS = 8.0f;
constexpr float DEFAULT_ITEM_HEIGHT = 120.0f;
constexpr float BUTTON_WIDTH = 112.0f;
constexpr float BUTTON_HEIGHT = 38.0f;
constexpr float BUTTON_GAP = 4.0f;
constexpr float DEFAULT_GAP = 10.0f;
constexpr float SMALL_GAP = 6.0f;
constexpr float MEDIUM_GAP = 8.0f;
constexpr float DEFAULT_MARGIN = 12.0f;
constexpr float SECTION_SECOND_BIAS = -10.0f;
constexpr float SECTION_SECOND_SCALE = 0.88f;
constexpr float SECTION_FIRST_BOTTOM_MARGIN = 6.0f;
constexpr float SECTION_THIRD_BOTTOM_MARGIN = 16.0f;
constexpr float DEFAULT_ITEM_MIN_SIZE = 84.0f;
constexpr float DEFAULT_ITEM_MAX_WIDTH = 260.0f;
constexpr float DEFAULT_ITEM_MAX_HEIGHT = 230.0f;
constexpr float DEFAULT_SCROLL_BAR_WIDTH = 5.0f;
constexpr float DEFAULT_SCROLL_FRICTION = 0.12f;
constexpr float DEFAULT_FLING_SPEED_LIMIT = 2800.0f;
constexpr float INDEX_EXTRA_OFFSET = -8.0f;
constexpr float SCROLL_BY_DISTANCE = 160.0f;
constexpr float SCROLL_TO_OFFSET = 240.0f;
constexpr float FOOTER_HEIGHT = 48.0f;
constexpr float HEADLINE_FONT_SIZE = 20.0f;
constexpr float SUBTITLE_FONT_SIZE = 12.0f;
constexpr float STATUS_FONT_SIZE = 11.0f;
constexpr float ITEM_FONT_SIZE = 15.0f;
constexpr float BUTTON_FONT_SIZE = 12.0f;
constexpr float FOOTER_FONT_SIZE = 13.0f;
constexpr const char *DEFAULT_COLUMN_TEMPLATE = "repeat(auto-fill, 118)";
constexpr const char *DEFAULT_ROW_TEMPLATE = "1fr";
constexpr size_t BUTTONS_PER_ROW = 3;
constexpr size_t ATTRIBUTE_VALUE_BUFFER_SIZE = 8;
constexpr uint32_t PAGE_BG = 0xFFF4F7FA;
constexpr uint32_t PANEL_BG = 0xFFFFFFFF;
constexpr uint32_t TEXT_PRIMARY = 0xFF1B2430;
constexpr uint32_t TEXT_SECONDARY = 0xFF667085;
constexpr uint32_t BRAND = 0xFF2457C5;
constexpr uint32_t BRAND_DARK = 0xFF173B8F;
constexpr uint32_t FOOTER_BG = 0xFFEAF0F8;
constexpr auto ATTR_WATER_FLOW_ITEM_FILL_POLICY = static_cast<ArkUI_NodeAttributeType>(1010013);
constexpr auto ATTR_WATER_FLOW_SUPPORT_EMPTY_BRANCH = static_cast<ArkUI_NodeAttributeType>(1010014);

struct EdgeValues {
    float top = 0.0f;
    float right = 0.0f;
    float bottom = 0.0f;
    float left = 0.0f;
};

struct TextStyle {
    float fontSize = STATUS_FONT_SIZE;
    uint32_t color = TEXT_PRIMARY;
    int32_t align = ARKUI_TEXT_ALIGNMENT_START;
};

constexpr TextStyle HEADLINE_TEXT_STYLE { HEADLINE_FONT_SIZE, TEXT_PRIMARY, ARKUI_TEXT_ALIGNMENT_START };
constexpr TextStyle SUBTITLE_TEXT_STYLE { SUBTITLE_FONT_SIZE, TEXT_SECONDARY, ARKUI_TEXT_ALIGNMENT_START };
constexpr TextStyle STATUS_TEXT_STYLE { STATUS_FONT_SIZE, TEXT_SECONDARY, ARKUI_TEXT_ALIGNMENT_START };
constexpr TextStyle ITEM_TEXT_STYLE { ITEM_FONT_SIZE, TEXT_PRIMARY, ARKUI_TEXT_ALIGNMENT_CENTER };
constexpr TextStyle FOOTER_TEXT_STYLE { FOOTER_FONT_SIZE, TEXT_SECONDARY, ARKUI_TEXT_ALIGNMENT_CENTER };

struct SectionSpec {
    int32_t itemCount = 0;
    int32_t crossCount = 0;
    float columnGap = DEFAULT_GAP;
    float rowGap = DEFAULT_GAP;
    EdgeValues margin;
};

struct DemoItem {
    float height = DEFAULT_ITEM_HEIGHT;
    uint32_t color = PANEL_BG;
};

struct SectionSizeConfig {
    float bias = 0.0f;
    float scale = 1.0f;
};

struct ActionContext {
    std::function<void()> action;
};

struct DemoState {
    ArkUI_NativeNodeAPI_1 *api = nullptr;
    std::shared_ptr<WaterFlow> waterFlow;
    std::shared_ptr<ArkUINodeAdapter> adapter;
    std::shared_ptr<WaterFlowSection> sections;
    std::vector<DemoItem> items;
    std::vector<std::unique_ptr<ActionContext>> actions;
    std::array<SectionSizeConfig, MIXED_SECTION_COUNT> sectionSizeConfig {};
    ArkUI_NodeHandle statusText = nullptr;
    ArkUI_NodeHandle headlineText = nullptr;
    bool slidingMode = true;
    bool showCached = true;
    bool supportEmptyBranch = true;
    bool syncLoad = true;
    bool sectionsEnabled = true;
    bool mixedSections = true;
    bool footerEnabled = false;
    int32_t fillPolicyIndex = DEFAULT_FILL_POLICY_INDEX;
    int32_t edgeEffectIndex = DEFAULT_EDGE_EFFECT_INDEX;
    int32_t targetIndex = INITIAL_TARGET_INDEX;
    int32_t firstIndex = 0;
    int32_t lastIndex = 0;
    std::string lastEvent = "ready";
};

std::shared_ptr<DemoState> g_demo;

uint32_t PaletteColor(int32_t index)
{
    static constexpr uint32_t colors[] = {
        0xFFFFE4D6, 0xFFD7F7E6, 0xFFDCEBFF, 0xFFFFF0B8, 0xFFEBDFFF, 0xFFD8F3FF,
    };
    return colors[static_cast<size_t>(index) % (sizeof(colors) / sizeof(colors[0]))];
}

float CardHeightForIndex(int32_t index)
{
    static constexpr float heights[] = {116.0f, 152.0f, 96.0f, 188.0f, 132.0f, 168.0f};
    return heights[static_cast<size_t>(index) % (sizeof(heights) / sizeof(heights[0]))];
}

void SetFloatArray(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr,
    std::initializer_list<float> values)
{
    std::array<ArkUI_NumberValue, ATTRIBUTE_VALUE_BUFFER_SIZE> buffer {};
    int32_t count = 0;
    for (auto value : values) {
        if (static_cast<size_t>(count) >= buffer.size()) {
            break;
        }
        buffer[static_cast<size_t>(count++)].f32 = value;
    }
    ArkUI_AttributeItem item { buffer.data(), count };
    api->setAttribute(node, attr, &item);
}

void SetRadius(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, float radius)
{
    SetFloatArray(api, node, NODE_BORDER_RADIUS, { radius, radius, radius, radius });
}

void SetMargin(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, const EdgeValues &margin)
{
    SetFloatArray(api, node, NODE_MARGIN, { margin.top, margin.right, margin.bottom, margin.left });
}

void SetPaddingAll(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, float value)
{
    SetFloatArray(api, node, NODE_PADDING, { value, value, value, value });
}

ArkUI_NodeHandle CreateText(ArkUI_NativeNodeAPI_1 *api, const std::string &text, const TextStyle &style)
{
    ArkUI_NodeHandle textNode = api->createNode(ARKUI_NODE_TEXT);
    SetTextContent(api, textNode, text.c_str());
    SetAttributeFloat32(api, textNode, NODE_FONT_SIZE, style.fontSize);
    SetAttributeUInt32(api, textNode, NODE_FONT_COLOR, style.color);
    SetAttributeInt32(api, textNode, NODE_TEXT_ALIGN, style.align);
    return textNode;
}

std::string FormatStatus()
{
    if (!g_demo || !g_demo->api || !g_demo->waterFlow) {
        return "WaterFlow CAPI showcase initializing";
    }

    auto *api = g_demo->api;
    auto flow = g_demo->waterFlow->GetWaterFlow();
    int32_t layoutMode = 0;
    int32_t syncLoad = 0;
    int32_t cachedCount = 0;
    int32_t showCached = 0;
    int32_t fillPolicy = 0;
    int32_t emptyBranch = 0;
    if (auto attr = api->getAttribute(flow, NODE_WATER_FLOW_LAYOUT_MODE); attr && attr->value) {
        layoutMode = attr->value[0].i32;
    }
    if (auto attr = api->getAttribute(flow, NODE_WATER_FLOW_SYNC_LOAD); attr && attr->value) {
        syncLoad = attr->value[0].i32;
    }
    if (auto attr = api->getAttribute(flow, NODE_WATER_FLOW_CACHED_COUNT); attr && attr->value) {
        cachedCount = attr->value[0].i32;
        if (attr->size > 1) {
            showCached = attr->value[1].i32;
        }
    }
    if (auto attr = api->getAttribute(flow, ATTR_WATER_FLOW_ITEM_FILL_POLICY); attr && attr->value) {
        fillPolicy = attr->value[0].i32;
    }
    if (auto attr = api->getAttribute(flow, ATTR_WATER_FLOW_SUPPORT_EMPTY_BRANCH); attr && attr->value) {
        emptyBranch = attr->value[0].i32;
    }

    int32_t sectionCount = 0;
    int32_t firstSectionItems = 0;
    if (g_demo->sections) {
        sectionCount = g_demo->sections->Size();
        firstSectionItems =
            g_demo->sections->GetSection(g_demo->sections->GetSectionOptions(), FIRST_SECTION_INDEX).itemsCount;
    }

    std::ostringstream status;
    status << "items " << g_demo->items.size()
           << " | visible " << g_demo->firstIndex << "-" << g_demo->lastIndex
           << " | sections " << sectionCount << "/" << firstSectionItems
           << " | footer " << (g_demo->footerEnabled ? 1 : 0)
           << " | mode " << layoutMode
           << " | sync " << syncLoad
           << " | cache " << cachedCount << ":" << showCached
           << " | fill " << fillPolicy
           << " | empty " << emptyBranch
           << " | " << g_demo->lastEvent;
    return status.str();
}

void RefreshStatus()
{
    if (!g_demo || !g_demo->statusText) {
        return;
    }
    SetTextContent(g_demo->api, g_demo->statusText, FormatStatus().c_str());
}

float MainSizeByIndex(int32_t itemIndex)
{
    if (!g_demo || g_demo->items.empty()) {
        return DEFAULT_ITEM_HEIGHT;
    }
    const int32_t maxIndex = static_cast<int32_t>(g_demo->items.size() - 1);
    const auto safeIndex = static_cast<size_t>(std::clamp(itemIndex, 0, maxIndex));
    return g_demo->items[safeIndex].height;
}

float MainSizeByIndexWithUserData(int32_t itemIndex, void *userData)
{
    auto *config = reinterpret_cast<SectionSizeConfig *>(userData);
    float base = MainSizeByIndex(itemIndex);
    if (config == nullptr) {
        return base;
    }
    return std::max(DEFAULT_ITEM_MIN_SIZE, base * config->scale + config->bias);
}

ArkUI_NodeHandle CreateFooter(ArkUI_NativeNodeAPI_1 *api);

void InitItems(int32_t count)
{
    if (!g_demo) {
        return;
    }
    g_demo->items.clear();
    g_demo->items.reserve(static_cast<size_t>(count));
    for (int32_t i = 0; i < count; ++i) {
        DemoItem item;
        item.height = CardHeightForIndex(i);
        item.color = PaletteColor(i);
        g_demo->items.emplace_back(std::move(item));
    }
}

ArkUI_Margin MakeMargin(const EdgeValues &values)
{
    return { values.top, values.right, values.bottom, values.left };
}

SectionOption CreateSectionOption(const SectionSpec &spec)
{
    SectionOption option {};
    option.itemsCount = spec.itemCount;
    option.crossCount = spec.crossCount;
    option.columnsGap = spec.columnGap;
    option.rowsGap = spec.rowGap;
    option.margin = MakeMargin(spec.margin);
    option.onGetItemMainSizeByIndex = MainSizeByIndex;
    return option;
}

void ApplyFooterOnly()
{
    g_demo->waterFlow->ResetSection();
    g_demo->sections.reset();
    g_demo->waterFlow->ResetFooter();
    g_demo->waterFlow->SetFooter(CreateFooter(g_demo->api));
    g_demo->footerEnabled = true;
}

void PrepareSections()
{
    g_demo->waterFlow->ResetFooter();
    g_demo->waterFlow->ResetSection();
    g_demo->footerEnabled = false;
    g_demo->sections = std::make_shared<WaterFlowSection>();
}

void ApplySingleSection(int32_t total)
{
    g_demo->sections->Resize(SINGLE_SECTION_COUNT);
    const SectionSpec spec {
        total,
        SINGLE_SECTION_CROSS_COUNT,
        DEFAULT_GAP,
        DEFAULT_GAP,
        { DEFAULT_MARGIN, DEFAULT_MARGIN, DEFAULT_MARGIN, DEFAULT_MARGIN },
    };
    auto section = CreateSectionOption(spec);
    g_demo->sections->SetSection(g_demo->sections->GetSectionOptions(), FIRST_SECTION_INDEX, section);
    g_demo->waterFlow->SetSection(g_demo->sections);
}

void RegisterSecondSectionSizeCallback()
{
    g_demo->sectionSizeConfig[SECOND_SECTION_INDEX] = { SECTION_SECOND_BIAS, SECTION_SECOND_SCALE };
    OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
        g_demo->sections->GetSectionOptions(),
        SECOND_SECTION_INDEX,
        &g_demo->sectionSizeConfig[SECOND_SECTION_INDEX],
        MainSizeByIndexWithUserData);
}

void ApplyMixedSections(int32_t total)
{
    const int32_t firstCount = std::min(SECTION_A_COUNT, total);
    const int32_t secondCount = std::min(SECTION_B_COUNT, std::max(0, total - firstCount));
    const int32_t thirdCount = std::max(0, total - firstCount - secondCount);
    g_demo->sections->Resize(MIXED_SECTION_COUNT);

    const SectionSpec firstSpec {
        firstCount,
        FIRST_SECTION_CROSS_COUNT,
        DEFAULT_GAP,
        DEFAULT_GAP,
        { DEFAULT_MARGIN, DEFAULT_MARGIN, SECTION_FIRST_BOTTOM_MARGIN, DEFAULT_MARGIN },
    };
    const SectionSpec secondSpec {
        secondCount,
        SECOND_SECTION_CROSS_COUNT,
        MEDIUM_GAP,
        MEDIUM_GAP,
        { DEFAULT_GAP, DEFAULT_GAP, DEFAULT_GAP, DEFAULT_GAP },
    };
    const SectionSpec thirdSpec {
        thirdCount,
        THIRD_SECTION_CROSS_COUNT,
        SMALL_GAP,
        SMALL_GAP,
        { MEDIUM_GAP, MEDIUM_GAP, SECTION_THIRD_BOTTOM_MARGIN, MEDIUM_GAP },
    };

    auto first = CreateSectionOption(firstSpec);
    auto second = CreateSectionOption(secondSpec);
    auto third = CreateSectionOption(thirdSpec);
    auto options = g_demo->sections->GetSectionOptions();
    g_demo->sections->SetSection(options, FIRST_SECTION_INDEX, first);
    g_demo->sections->SetSection(options, SECOND_SECTION_INDEX, second);
    RegisterSecondSectionSizeCallback();
    g_demo->sections->SetSection(options, THIRD_SECTION_INDEX, third);

    g_demo->waterFlow->SetSection(g_demo->sections);
}

void ApplySections()
{
    if (!g_demo || !g_demo->waterFlow) {
        return;
    }
    if (!g_demo->sectionsEnabled) {
        ApplyFooterOnly();
        return;
    }

    PrepareSections();
    const int32_t total = static_cast<int32_t>(g_demo->items.size());
    if (g_demo->mixedSections) {
        ApplyMixedSections(total);
        return;
    }
    ApplySingleSection(total);
}

ArkUI_NodeHandle AdapterOnCreate(ArkUI_NativeNodeAPI_1 *api, int32_t)
{
    ArkUI_NodeHandle flowItem = api->createNode(ARKUI_NODE_FLOW_ITEM);
    ArkUI_NodeHandle text = CreateText(api, "", ITEM_TEXT_STYLE);
    SetAttributeFloat32(api, text, NODE_WIDTH_PERCENT, FULL);
    api->addChild(flowItem, text);
    return flowItem;
}

void AdapterOnBind(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle flowItem, int32_t index)
{
    if (!g_demo || index < 0 || index >= static_cast<int32_t>(g_demo->items.size())) {
        return;
    }
    const DemoItem &item = g_demo->items[static_cast<size_t>(index)];
    SetAttributeFloat32(api, flowItem, NODE_WIDTH_PERCENT, FULL);
    SetAttributeFloat32(api, flowItem, NODE_HEIGHT, item.height);
    SetBackgroundColor(api, flowItem, item.color);
    SetRadius(api, flowItem, CARD_RADIUS);

    ArkUI_NodeHandle text = api->getFirstChild(flowItem);
    if (!text) {
        return;
    }
    const std::string label = "item " + std::to_string(index);
    SetTextContent(api, text, label.c_str());
}

uint64_t AdapterGetStableId(int32_t index)
{
    return static_cast<uint64_t>(index + STABLE_ID_OFFSET);
}

int32_t AdapterGetTotalCount()
{
    return g_demo ? static_cast<int32_t>(g_demo->items.size()) : 0;
}

void AppendItems(int32_t count)
{
    if (!g_demo || !g_demo->adapter || count <= 0) {
        return;
    }
    const int32_t start = static_cast<int32_t>(g_demo->items.size());
    for (int32_t i = 0; i < count; ++i) {
        const int32_t index = start + i;
        DemoItem item;
        item.height = CardHeightForIndex(index);
        item.color = PaletteColor(index);
        g_demo->items.emplace_back(std::move(item));
    }
    g_demo->adapter->InsertRange(start, count);
    ApplySections();
    g_demo->lastEvent = "adapter insert " + std::to_string(count);
    RefreshStatus();
}

ArkUINodeAdapter::Callbacks MakeAdapterCallbacks()
{
    ArkUINodeAdapter::Callbacks callbacks {};
    callbacks.getTotalCount = AdapterGetTotalCount;
    callbacks.getStableId = AdapterGetStableId;
    callbacks.onCreate = AdapterOnCreate;
    callbacks.onBind = AdapterOnBind;
    callbacks.onRecycle = nullptr;
    return callbacks;
}

void HandleWaterFlowEvent(ArkUI_NodeEvent *event)
{
    if (!g_demo || event == nullptr) {
        return;
    }
    auto type = OH_ArkUI_NodeEvent_GetEventType(event);
    auto *componentEvent = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
    switch (type) {
        case NODE_WATER_FLOW_ON_SCROLL_INDEX:
            if (componentEvent != nullptr) {
                g_demo->firstIndex = componentEvent->data[0].i32;
                g_demo->lastIndex = componentEvent->data[1].i32;
            }
            g_demo->lastEvent = "onScrollIndex";
            break;
        case NODE_ON_WILL_SCROLL:
            g_demo->lastEvent = "onWillScroll";
            break;
        case NODE_WATER_FLOW_ON_DID_SCROLL:
            g_demo->lastEvent = "onDidScroll";
            break;
        case NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN:
            g_demo->lastEvent = "onScrollFrameBegin";
            break;
        case NODE_SCROLL_EVENT_ON_SCROLL_START:
            g_demo->lastEvent = "onScrollStart";
            break;
        case NODE_SCROLL_EVENT_ON_SCROLL_STOP:
            g_demo->lastEvent = "onScrollStop";
            break;
        case NODE_SCROLL_EVENT_ON_REACH_START:
            g_demo->lastEvent = "onReachStart";
            break;
        case NODE_SCROLL_EVENT_ON_REACH_END:
            g_demo->lastEvent = "onReachEnd";
            break;
        default:
            g_demo->lastEvent = "scroll event";
            break;
    }
    RefreshStatus();
}

void HandleButtonEvent(ArkUI_NodeEvent *event)
{
    if (event == nullptr || OH_ArkUI_NodeEvent_GetEventType(event) != NODE_ON_CLICK) {
        return;
    }
    auto *context = reinterpret_cast<ActionContext *>(OH_ArkUI_NodeEvent_GetUserData(event));
    if (context != nullptr && context->action) {
        context->action();
    }
}

ArkUI_NodeHandle CreateCommandButton(ArkUI_NativeNodeAPI_1 *api, const std::string &label, std::function<void()> action)
{
    ArkUI_NodeHandle button = api->createNode(ARKUI_NODE_BUTTON);
    ArkUI_AttributeItem labelItem { nullptr, 0, label.c_str(), nullptr };
    api->setAttribute(button, NODE_BUTTON_LABEL, &labelItem);
    SetAttributeFloat32(api, button, NODE_WIDTH, BUTTON_WIDTH);
    SetAttributeFloat32(api, button, NODE_HEIGHT, BUTTON_HEIGHT);
    SetAttributeFloat32(api, button, NODE_FONT_SIZE, BUTTON_FONT_SIZE);
    SetAttributeUInt32(api, button, NODE_FONT_COLOR, PANEL_BG);
    SetBackgroundColor(api, button, BRAND);
    SetRadius(api, button, CARD_RADIUS);
    SetMargin(api, button, { BUTTON_GAP, BUTTON_GAP, BUTTON_GAP, BUTTON_GAP });

    auto context = std::make_unique<ActionContext>();
    context->action = std::move(action);
    ActionContext *rawContext = context.get();
    g_demo->actions.emplace_back(std::move(context));
    api->addNodeEventReceiver(button, HandleButtonEvent);
    api->registerNodeEvent(button, NODE_ON_CLICK, 0, rawContext);
    return button;
}

ArkUI_NodeHandle CreateButtonRow(ArkUI_NativeNodeAPI_1 *api, const std::vector<ArkUI_NodeHandle> &buttons)
{
    ArkUI_NodeHandle row = api->createNode(ARKUI_NODE_ROW);
    SetAttributeFloat32(api, row, NODE_WIDTH_PERCENT, FULL);
    for (auto button : buttons) {
        api->addChild(row, button);
    }
    return row;
}

void ToggleMode()
{
    g_demo->slidingMode = !g_demo->slidingMode;
    g_demo->waterFlow->SetLayoutMode(g_demo->slidingMode ? ARKUI_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW
                                                          : ARKUI_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN);
    ApplySections();
    g_demo->lastEvent = g_demo->slidingMode ? "layoutMode sliding" : "layoutMode topDown";
    RefreshStatus();
}

void CycleFillPolicy()
{
    static constexpr int32_t policies[] = {
        RESET_ITEM_FILL_POLICY,
        ARKUI_ITEMFILLPOLICY_DEFAULT,
        ARKUI_ITEMFILLPOLICY_SM1MD2LG3,
        ARKUI_ITEMFILLPOLICY_SM2MD3LG5,
    };
    constexpr int32_t policyCount = static_cast<int32_t>(sizeof(policies) / sizeof(policies[0]));
    g_demo->fillPolicyIndex = (g_demo->fillPolicyIndex + 1) % policyCount;
    g_demo->waterFlow->SetColumnTemplateItemFillPolicy(policies[g_demo->fillPolicyIndex]);
    g_demo->lastEvent = "itemFillPolicy " + std::to_string(policies[g_demo->fillPolicyIndex]);
    RefreshStatus();
}

void ToggleCached()
{
    g_demo->showCached = !g_demo->showCached;
    const int32_t cachedCount = g_demo->showCached ? DEFAULT_CACHED_COUNT : COMPACT_CACHED_COUNT;
    g_demo->waterFlow->SetCachedCount(cachedCount, g_demo->showCached);
    g_demo->lastEvent = g_demo->showCached ? "show cached on" : "show cached off";
    RefreshStatus();
}

void ToggleEmptyBranch()
{
    g_demo->supportEmptyBranch = !g_demo->supportEmptyBranch;
    g_demo->waterFlow->SetSupportEmptyBranchInLazyLoading(g_demo->supportEmptyBranch);
    g_demo->lastEvent = g_demo->supportEmptyBranch ? "empty branch on" : "empty branch off";
    RefreshStatus();
}

void ToggleSections()
{
    if (g_demo->sectionsEnabled && g_demo->mixedSections) {
        g_demo->mixedSections = false;
    } else if (g_demo->sectionsEnabled) {
        g_demo->sectionsEnabled = false;
    } else {
        g_demo->sectionsEnabled = true;
        g_demo->mixedSections = true;
    }
    ApplySections();
    if (!g_demo->sectionsEnabled) {
        g_demo->lastEvent = "sections off + footer";
    } else {
        g_demo->lastEvent = g_demo->mixedSections ? "mixed sections" : "single section";
    }
    RefreshStatus();
}

void ToggleSyncLoad()
{
    g_demo->syncLoad = !g_demo->syncLoad;
    g_demo->waterFlow->SetSyncLoad(g_demo->syncLoad);
    g_demo->lastEvent = g_demo->syncLoad ? "syncLoad on" : "syncLoad off";
    RefreshStatus();
}

void CycleEdgeEffect()
{
    static constexpr int32_t effects[] = { ARKUI_EDGE_EFFECT_SPRING, ARKUI_EDGE_EFFECT_FADE, ARKUI_EDGE_EFFECT_NONE };
    constexpr int32_t effectCount = static_cast<int32_t>(sizeof(effects) / sizeof(effects[0]));
    g_demo->edgeEffectIndex = (g_demo->edgeEffectIndex + 1) % effectCount;
    g_demo->waterFlow->SetEdgeEffect(effects[g_demo->edgeEffectIndex], true, ARKUI_EDGE_DIRECTION_ALL);
    g_demo->lastEvent = "edgeEffect " + std::to_string(effects[g_demo->edgeEffectIndex]);
    RefreshStatus();
}

void ResetAttributes()
{
    g_demo->slidingMode = true;
    g_demo->showCached = true;
    g_demo->supportEmptyBranch = true;
    g_demo->syncLoad = true;
    g_demo->sectionsEnabled = true;
    g_demo->mixedSections = true;
    g_demo->footerEnabled = false;
    g_demo->fillPolicyIndex = DEFAULT_FILL_POLICY_INDEX;
    g_demo->edgeEffectIndex = DEFAULT_EDGE_EFFECT_INDEX;
    g_demo->waterFlow->SetLayoutDirection(ARKUI_FLEX_DIRECTION_COLUMN);
    g_demo->waterFlow->SetColumnTemplate(DEFAULT_COLUMN_TEMPLATE);
    g_demo->waterFlow->SetRowTemplate(DEFAULT_ROW_TEMPLATE);
    g_demo->waterFlow->SetGaps(DEFAULT_GAP, DEFAULT_GAP);
    g_demo->waterFlow->SetCachedCount(DEFAULT_CACHED_COUNT, true);
    g_demo->waterFlow->SetItemConstraintSize(
        DEFAULT_ITEM_MIN_SIZE, DEFAULT_ITEM_MAX_WIDTH, DEFAULT_ITEM_MIN_SIZE, DEFAULT_ITEM_MAX_HEIGHT);
    g_demo->waterFlow->SetLayoutMode(ARKUI_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW);
    g_demo->waterFlow->SetSyncLoad(true);
    g_demo->waterFlow->SetScrollBar(ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO);
    g_demo->waterFlow->SetScrollBarWidth(DEFAULT_SCROLL_BAR_WIDTH);
    g_demo->waterFlow->SetScrollBarColor(BRAND_DARK);
    g_demo->waterFlow->SetScrollEnabled(true);
    g_demo->waterFlow->SetScrollFriction(DEFAULT_SCROLL_FRICTION);
    g_demo->waterFlow->SetFlingSpeedLimit(DEFAULT_FLING_SPEED_LIMIT);
    g_demo->waterFlow->SetFadingEdge(DEFAULT_FADING_EDGE);
    g_demo->waterFlow->SetNestedScroll(ARKUI_SCROLL_NESTED_MODE_SELF_FIRST, ARKUI_SCROLL_NESTED_MODE_SELF_FIRST);
    g_demo->waterFlow->SetEdgeEffect(ARKUI_EDGE_EFFECT_SPRING, true, ARKUI_EDGE_DIRECTION_ALL);
    g_demo->waterFlow->SetColumnTemplateItemFillPolicy(DEFAULT_ITEM_FILL_POLICY);
    g_demo->waterFlow->SetSupportEmptyBranchInLazyLoading(true);
    ApplySections();
    g_demo->lastEvent = "reset attributes";
    RefreshStatus();
}

void ScrollToNextTargetIndex()
{
    if (g_demo->items.empty()) {
        return;
    }
    g_demo->waterFlow->ScrollToIndex(
        g_demo->targetIndex, true, ARKUI_SCROLL_ALIGNMENT_CENTER, INDEX_EXTRA_OFFSET);
    g_demo->targetIndex = (g_demo->targetIndex + TARGET_INDEX_STEP) % static_cast<int32_t>(g_demo->items.size());
}

std::vector<ArkUI_NodeHandle> CreateToolbarButtons(ArkUI_NativeNodeAPI_1 *api)
{
    return {
        CreateCommandButton(api, "Top", [] { g_demo->waterFlow->ScrollEdge(ARKUI_SCROLL_EDGE_TOP); }),
        CreateCommandButton(api, "Index", ScrollToNextTargetIndex),
        CreateCommandButton(api, "By 160", [] { g_demo->waterFlow->ScrollBy(0.0f, SCROLL_BY_DISTANCE); }),
        CreateCommandButton(api, "Bottom", [] { g_demo->waterFlow->ScrollEdge(ARKUI_SCROLL_EDGE_BOTTOM); }),
        CreateCommandButton(api, "Mode", ToggleMode),
        CreateCommandButton(api, "Fill", CycleFillPolicy),
        CreateCommandButton(api, "Cache", ToggleCached),
        CreateCommandButton(api, "Empty", ToggleEmptyBranch),
        CreateCommandButton(api, "Page", [] { g_demo->waterFlow->ScrollPage(true, true); }),
        CreateCommandButton(api, "Add", [] { AppendItems(APPEND_COUNT); }),
        CreateCommandButton(api, "Section", ToggleSections),
        CreateCommandButton(api, "Sync", ToggleSyncLoad),
        CreateCommandButton(api, "Edge", CycleEdgeEffect),
        CreateCommandButton(api, "Offset", [] { g_demo->waterFlow->ScrollTo(0.0f, SCROLL_TO_OFFSET); }),
        CreateCommandButton(api, "Reset", ResetAttributes),
    };
}

void AddButtonRows(
    ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle panel, const std::vector<ArkUI_NodeHandle> &buttons)
{
    for (size_t start = 0; start < buttons.size(); start += BUTTONS_PER_ROW) {
        const size_t end = std::min(start + BUTTONS_PER_ROW, buttons.size());
        std::vector<ArkUI_NodeHandle> row(buttons.begin() + static_cast<std::ptrdiff_t>(start),
            buttons.begin() + static_cast<std::ptrdiff_t>(end));
        api->addChild(panel, CreateButtonRow(api, row));
    }
}

ArkUI_NodeHandle CreateToolbar(ArkUI_NativeNodeAPI_1 *api)
{
    ArkUI_NodeHandle panel = api->createNode(ARKUI_NODE_COLUMN);
    SetAttributeFloat32(api, panel, NODE_WIDTH_PERCENT, FULL);
    SetPaddingAll(api, panel, SMALL_GAP);
    SetBackgroundColor(api, panel, PANEL_BG);
    SetRadius(api, panel, CARD_RADIUS);
    SetMargin(api, panel, { CARD_RADIUS, 0.0f, CARD_RADIUS, 0.0f });

    const auto buttons = CreateToolbarButtons(api);
    AddButtonRows(api, panel, buttons);
    return panel;
}

ArkUI_NodeHandle CreateFooter(ArkUI_NativeNodeAPI_1 *api)
{
    ArkUI_NodeHandle footer = api->createNode(ARKUI_NODE_FLOW_ITEM);
    ArkUI_NodeHandle text = CreateText(
        api,
        "End of WaterFlow CAPI demo",
        FOOTER_TEXT_STYLE);
    SetAttributeFloat32(api, footer, NODE_WIDTH_PERCENT, FULL);
    SetAttributeFloat32(api, footer, NODE_HEIGHT, FOOTER_HEIGHT);
    SetBackgroundColor(api, footer, FOOTER_BG);
    SetRadius(api, footer, CARD_RADIUS);
    api->addChild(footer, text);
    return footer;
}

void SetupWaterFlow()
{
    g_demo->waterFlow = std::make_shared<WaterFlow>();
    g_demo->waterFlow->SetEventHandler(HandleWaterFlowEvent);
    g_demo->waterFlow->RegisterWaterFlowEvents();
    ResetAttributes();

    g_demo->adapter = std::make_shared<ArkUINodeAdapter>();
    g_demo->adapter->SetCallbacks(MakeAdapterCallbacks());
    g_demo->waterFlow->SetLazyAdapter(g_demo->adapter);
    g_demo->adapter->ReloadAllItems();
}

ArkUI_NodeHandle BuildPage()
{
    auto *api = g_demo->api;
    ArkUI_NodeHandle page = api->createNode(ARKUI_NODE_COLUMN);
    SetAttributeFloat32(api, page, NODE_WIDTH_PERCENT, FULL);
    SetAttributeFloat32(api, page, NODE_HEIGHT_PERCENT, FULL);
    SetBackgroundColor(api, page, PAGE_BG);
    SetPaddingAll(api, page, DEFAULT_GAP);

    g_demo->headlineText = CreateText(api, "WaterFlow NDK CAPI Showcase", HEADLINE_TEXT_STYLE);
    ArkUI_NodeHandle subTitle = CreateText(
        api,
        "All WaterFlow node attributes, sections, adapter, events and scroll controls.",
        SUBTITLE_TEXT_STYLE);
    g_demo->statusText = CreateText(api, "status", STATUS_TEXT_STYLE);
    SetBackgroundColor(api, g_demo->statusText, PANEL_BG);
    SetPaddingAll(api, g_demo->statusText, CARD_RADIUS);
    SetRadius(api, g_demo->statusText, CARD_RADIUS);

    ArkUI_NodeHandle waterFlow = g_demo->waterFlow->GetWaterFlow();
    SetAttributeFloat32(api, waterFlow, NODE_WIDTH_PERCENT, FULL);
    SetAttributeFloat32(api, waterFlow, NODE_HEIGHT, WATERFLOW_HEIGHT);
    SetBackgroundColor(api, waterFlow, PANEL_BG);
    SetRadius(api, waterFlow, CARD_RADIUS);
    SetMargin(api, waterFlow, { CARD_RADIUS, 0.0f, CARD_RADIUS, 0.0f });

    api->addChild(page, g_demo->headlineText);
    api->addChild(page, subTitle);
    api->addChild(page, g_demo->statusText);
    api->addChild(page, CreateToolbar(api));
    api->addChild(page, waterFlow);
    RefreshStatus();
    return page;
}
} // namespace

ArkUI_NodeHandle WaterFlow::CreateWaterFlowCapiShowcase()
{
    ArkUI_NativeNodeAPI_1 *api = nullptr;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, api);
    if (api == nullptr) {
        return nullptr;
    }
    g_demo = std::make_shared<DemoState>();
    g_demo->api = api;
    InitItems(INITIAL_COUNT);
    SetupWaterFlow();
    return BuildPage();
}
