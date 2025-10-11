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

#include "ArkUIUtils.h"

#include <array>
#include <chrono>
#include <thread>

// ------------------------------
// 常量
// ------------------------------
namespace {
constexpr int K_EDGES = 4;
constexpr int K_EDGE_TOP = 0;
constexpr int K_EDGE_RIGHT = 1;
constexpr int K_EDGE_BOTTOM = 2;
constexpr int K_EDGE_LEFT = 3;

constexpr int K_ENABLED = 1;

constexpr float K_PERCENT_FULL = 1.0f;

constexpr uint32_t K_COLOR_TRANSPARENT = 0x00000000U;
constexpr float K_DEFAULT_SCROLL_BAR_WIDTH = 4.0f;
constexpr uint32_t K_DEFAULT_SCROLL_BAR_COLOR = 0x66000000U;
constexpr float K_DEFAULT_SCROLL_FRICTION = 0.015f;
constexpr int32_t K_DEFAULT_FADING_EDGE = 12;

// 属性数组的最大容量（替代魔法值 8）
constexpr int K_MAX_ATTR_VALUES = 8;

constexpr unsigned int K_LOG_DOMAIN = 0xFF00;

struct NodeAttrTarget {
    ArkUI_NativeNodeAPI_1 *api;
    ArkUI_NodeHandle node;
    ArkUI_NodeAttributeType attr;
    const char *debugName;
};
} // namespace

// ------------------------------
// 判空 / 校验
// ------------------------------
bool IsValidRange(int32_t start, int32_t end, int32_t count)
{
    if (!IsValidIndex(start, count)) {
        return false;
    }
    if (end < start) {
        return false;
    }
    if (end > count) {
        return false;
    }
    return true;
}

bool ValidateApiAndNode(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, const char *functionName)
{
    if (!IsNotNull(api)) {
        if (functionName != nullptr) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "%{public}s: api is null", functionName);
        }
        return false;
    }
    if (!IsNotNull(node)) {
        if (functionName != nullptr) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "%{public}s: node is null", functionName);
        }
        return false;
    }
    return true;
}

// ------------------------------
// 通用属性设置
// ------------------------------
void SetAttributeFloat32(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr, float value)
{
    if (!ValidateApiAndNode(api, node, "SetAttributeFloat32")) {
        return;
    }
    ArkUI_NumberValue numberValue{};
    numberValue.f32 = value;

    ArkUI_AttributeItem item{&numberValue, 1};
    api->setAttribute(node, attr, &item);
}

void SetAttributeUInt32(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr, uint32_t value)
{
    if (!ValidateApiAndNode(api, node, "SetAttributeUInt32")) {
        return;
    }
    ArkUI_NumberValue numberValue{};
    numberValue.u32 = value;

    ArkUI_AttributeItem item{&numberValue, 1};
    api->setAttribute(node, attr, &item);
}

void SetAttributeInt32(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr, int32_t value)
{
    if (!ValidateApiAndNode(api, node, "SetAttributeInt32")) {
        return;
    }
    ArkUI_NumberValue numberValue{};
    numberValue.i32 = value;

    ArkUI_AttributeItem item{&numberValue, 1};
    api->setAttribute(node, attr, &item);
}

void SetAttributeString(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr,
                        const char *value)
{
    if (!ValidateApiAndNode(api, node, "SetAttributeString")) {
        return;
    }
    if (!IsNotNull(value)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "SetAttributeString: value is null");
        return;
    }

    ArkUI_AttributeItem item{nullptr, 0, value};
    api->setAttribute(node, attr, &item);
}

// 设置 float 数组属性
static void ApplyFloatArrayAttribute(const NodeAttrTarget &target, const float *values, int count)
{
    if (!ValidateApiAndNode(target.api, target.node, target.debugName)) {
        return;
    }
    if (values == nullptr || count <= 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "%{public}s: invalid values",
                     target.debugName ? target.debugName : "ApplyFloatArrayAttribute");
        return;
    }

    std::array<ArkUI_NumberValue, K_MAX_ATTR_VALUES> buf{};
    int capped = count;
    if (capped > static_cast<int>(buf.size())) {
        OH_LOG_Print(LOG_APP, LOG_WARN, K_LOG_DOMAIN, LOG_TAG, "%{public}s: count too large=%{public}d",
                     target.debugName ? target.debugName : "ApplyFloatArrayAttribute", count);
        capped = static_cast<int>(buf.size());
    }
    for (int i = 0; i < capped; ++i) {
        buf[static_cast<size_t>(i)].f32 = values[i];
    }

    ArkUI_AttributeItem item{buf.data(), static_cast<int32_t>(capped)};
    target.api->setAttribute(target.node, target.attr, &item);
}

// ------------------------------
// 尺寸 / 背景
// ------------------------------
void SetSize(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, float width, float height)
{
    SetAttributeFloat32(api, node, NODE_WIDTH, width);
    SetAttributeFloat32(api, node, NODE_HEIGHT, height);
}

void SetSizePercent(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, float widthPercent, float heightPercent)
{
    SetAttributeFloat32(api, node, NODE_WIDTH_PERCENT, widthPercent);
    SetAttributeFloat32(api, node, NODE_HEIGHT_PERCENT, heightPercent);
}

void SetFullSize(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node)
{
    SetSizePercent(api, node, K_PERCENT_FULL, K_PERCENT_FULL);
}

void SetBackgroundColor(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, uint32_t color)
{
    SetAttributeUInt32(api, node, NODE_BACKGROUND_COLOR, color);
}

void SetTransparentBackground(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node)
{
    SetBackgroundColor(api, node, K_COLOR_TRANSPARENT);
}

void SetPadding(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, const Padding &padding)
{
    const float vals[K_EDGES] = {padding.top, padding.right, padding.bottom, padding.left};
    ApplyFloatArrayAttribute(NodeAttrTarget{api, node, NODE_PADDING, "SetPadding"}, vals, K_EDGES);
}

// ------------------------------
// 文本
// ------------------------------
ArkUI_NodeHandle CreateTextNode(ArkUI_NativeNodeAPI_1 *api, const char *text)
{
    if (!IsNotNull(api) || !IsNotNull(text)) {
        return nullptr;
    }

    ArkUI_NodeHandle textNode = api->createNode(ARKUI_NODE_TEXT);
    if (!IsNotNull(textNode)) {
        return nullptr;
    }

    SetAttributeString(api, textNode, NODE_TEXT_CONTENT, text);
    return textNode;
}

void SetTextStyle(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle textNode, float fontSize, uint32_t fontColor,
                  int32_t textAlign)
{
    if (!ValidateApiAndNode(api, textNode, "SetTextStyle")) {
        return;
    }
    SetAttributeFloat32(api, textNode, NODE_FONT_SIZE, fontSize);
    SetAttributeUInt32(api, textNode, NODE_FONT_COLOR, fontColor);
    SetAttributeInt32(api, textNode, NODE_TEXT_ALIGN, textAlign);
}

void SetTextContent(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle textNode, const char *text)
{
    SetAttributeString(api, textNode, NODE_TEXT_CONTENT, text);
}

// ------------------------------
// 滚动
// ------------------------------
void SetScrollBarStyle(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, bool visible, float width, uint32_t color)
{
    if (!ValidateApiAndNode(api, node, "SetScrollBarStyle")) {
        return;
    }

    int32_t displayMode = visible ? ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO : ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF;
    SetAttributeInt32(api, node, NODE_SCROLL_BAR_DISPLAY_MODE, displayMode);
    if (visible) {
        SetAttributeFloat32(api, node, NODE_SCROLL_BAR_WIDTH, width);
        SetAttributeUInt32(api, node, NODE_SCROLL_BAR_COLOR, color);
    }
}

void SetDefaultScrollStyle(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node)
{
    if (!ValidateApiAndNode(api, node, "SetDefaultScrollStyle")) {
        return;
    }
    SetScrollBarStyle(api, node, true, K_DEFAULT_SCROLL_BAR_WIDTH, K_DEFAULT_SCROLL_BAR_COLOR);
    SetAttributeInt32(api, node, NODE_SCROLL_EDGE_EFFECT, ARKUI_EDGE_EFFECT_SPRING);
    SetAttributeInt32(api, node, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, K_ENABLED);
    SetAttributeFloat32(api, node, NODE_SCROLL_FRICTION, K_DEFAULT_SCROLL_FRICTION);
    SetAttributeInt32(api, node, NODE_SCROLL_NESTED_SCROLL, ARKUI_SCROLL_NESTED_MODE_SELF_FIRST);
    SetAttributeInt32(api, node, NODE_SCROLL_FADING_EDGE, K_DEFAULT_FADING_EDGE);
}

// ------------------------------
// 异步任务
// ------------------------------
void PostDelayedTask(int32_t delayMs, std::function<void()> task)
{
    if (!task) {
        return;
    }

    int32_t safeDelayMs = delayMs;
    if (safeDelayMs < 0) {
        safeDelayMs = 0;
    }

    std::thread worker([safeDelayMs, fn = std::move(task)]() mutable {
        if (safeDelayMs > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(safeDelayMs));
        }
        fn();
    });
    worker.detach();
}

// ------------------------------
// N-API 工具
// ------------------------------
std::string GetStringFromNapi(napi_env env, napi_value value)
{
    if (!IsNotNull(env) || !IsNotNull(value)) {
        return std::string();
    }

    size_t length = 0;
    napi_status s0 = napi_get_value_string_utf8(env, value, nullptr, 0, &length);
    if (s0 != napi_ok) {
        return std::string();
    }

    std::string result(length, '\0');
    size_t written = 0;
    napi_status s1 = napi_get_value_string_utf8(env, value, result.data(), length + 1, &written);
    if (s1 != napi_ok) {
        return std::string();
    }

    return result;
}

bool IsNapiArray(napi_env env, napi_value value)
{
    if (!IsNotNull(env) || !IsNotNull(value)) {
        return false;
    }

    bool isArray = false;
    napi_status status = napi_is_array(env, value, &isArray);
    if (status != napi_ok) {
        return false;
    }

    return isArray;
}

ArkUI_NodeContentHandle GetNodeContentFromNapi(napi_env env, napi_callback_info info)
{
    if (!IsNotNull(env) || !IsNotNull(info)) {
        return nullptr;
    }

    size_t argc = 1;
    napi_value arg0 = nullptr;
    napi_status st = napi_get_cb_info(env, info, &argc, &arg0, nullptr, nullptr);
    if (st != napi_ok || argc < 1) {
        return nullptr;
    }

    ArkUI_NodeContentHandle content = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, arg0, &content);
    return content;
}

void AddNodeToContent(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node)
{
    if (!IsNotNull(content) || !IsNotNull(node)) {
        return;
    }
    OH_ArkUI_NodeContent_AddNode(content, node);
}

// ------------------------------
// NodeEventRegistrar
// ------------------------------
NodeEventRegistrar::NodeEventRegistrar(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node)
    : nodeApi_(api), nodeHandle_(node)
{
    if (!ValidateApiAndNode(api, node, "NodeEventRegistrar::Constructor")) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "NodeEventRegistrar: invalid api or node");
    }
}

NodeEventRegistrar::~NodeEventRegistrar()
{
    if (!IsNotNull(nodeApi_) || !IsNotNull(nodeHandle_)) {
        return;
    }
    for (ArkUI_NodeEventType eventType : registeredEventTypes_) {
        nodeApi_->unregisterNodeEvent(nodeHandle_, eventType);
    }
    registeredEventTypes_.clear();
}

void NodeEventRegistrar::RegisterEvent(ArkUI_NodeEventType eventType, void *userData)
{
    if (!ValidateApiAndNode(nodeApi_, nodeHandle_, "NodeEventRegistrar::RegisterEvent")) {
        return;
    }
    nodeApi_->registerNodeEvent(nodeHandle_, eventType, 0, userData);
    registeredEventTypes_.push_back(eventType);
}

void NodeEventRegistrar::RegisterMultipleEvents(std::initializer_list<ArkUI_NodeEventType> eventTypes, void *userData)
{
    for (ArkUI_NodeEventType eventType : eventTypes) {
        RegisterEvent(eventType, userData);
    }
}

// ------------------------------
// AdapterEventRegistrar
// ------------------------------
AdapterEventRegistrar::AdapterEventRegistrar(ArkUI_NodeAdapterHandle adapter, void *userData,
                                             void (*callback)(ArkUI_NodeAdapterEvent *))
    : adapterHandle_(adapter)
{
    if (!IsNotNull(adapterHandle_)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "AdapterEventRegistrar: adapter is null");
        return;
    }
    if (!IsNotNull(callback)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG, "AdapterEventRegistrar: callback is null");
        return;
    }

    int32_t result = OH_ArkUI_NodeAdapter_RegisterEventReceiver(adapterHandle_, userData, callback);
    if (result != 0) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, K_LOG_DOMAIN, LOG_TAG,
                     "AdapterEventRegistrar: failed to register event receiver, result=%{public}d", result);
    }
}

AdapterEventRegistrar::~AdapterEventRegistrar()
{
    if (IsNotNull(adapterHandle_)) {
        OH_ArkUI_NodeAdapter_UnregisterEventReceiver(adapterHandle_);
    }
}
