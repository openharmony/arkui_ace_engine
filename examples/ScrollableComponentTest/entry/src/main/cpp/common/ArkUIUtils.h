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

#ifndef SCROLLABLE_COMPONENT_COMMON_ARKUIUTILS_H
#define SCROLLABLE_COMPONENT_COMMON_ARKUIUTILS_H

#include <cstdint>
#include <functional>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <arkui/native_node_napi.h>
#include <napi/native_api.h>

#include <hilog/log.h>

#ifndef LOG_TAG
#define LOG_TAG "ArkUIUtils"
#endif

// ==============================
// 判空 / 校验
// ==============================
template <typename T> inline bool IsNotNull(const T *ptr)
{
    return ptr != nullptr;
}

template <typename T> inline bool IsNotNull(const std::shared_ptr<T> &ptr)
{
    return ptr != nullptr;
}

template <typename T> inline bool IsNotNull(T *ptr)
{
    return ptr != nullptr;
}

inline bool IsValidIndex(int32_t index, int32_t count)
{
    return (index >= 0) && (index < count);
}

inline bool IsValidRange(int32_t start, int32_t end, int32_t count);

bool ValidateApiAndNode(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, const char *functionName = nullptr);

template <typename T, std::size_t N> constexpr int ArrSize(const T (&arr)[N]) noexcept
{
    return static_cast<int>(N);
}

// ==============================
// 尺寸 / 背景
// ==============================

struct Padding {
    float top{0.f};
    float right{0.f};
    float bottom{0.f};
    float left{0.f};

    static Padding All(float v)
    {
        return Padding{v, v, v, v};
    }
    static Padding Symmetric(float vertical, float horizontal)
    {
        return Padding{vertical, horizontal, vertical, horizontal};
    }
    static Padding Only(float t, float r, float b, float l)
    {
        return Padding{t, r, b, l};
    }
};

void SetSize(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, float width, float height);

void SetSizePercent(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, float widthPercent, float heightPercent);

void SetFullSize(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node);

void SetBackgroundColor(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, uint32_t color);

void SetTransparentBackground(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node);

void SetPadding(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, const Padding &padding);

// ==============================
// 通用属性设置
// ==============================
void SetAttributeFloat32(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr, float value);

void SetAttributeUInt32(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr,
                        uint32_t value);

void SetAttributeInt32(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr, int32_t value);

void SetAttributeString(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attr,
                        const char *value);

// ==============================
// 文本节点工具
// ==============================
ArkUI_NodeHandle CreateTextNode(ArkUI_NativeNodeAPI_1 *api, const char *text);

void SetTextStyle(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle textNode, float fontSize, uint32_t fontColor,
                  int32_t textAlign);

void SetTextContent(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle textNode, const char *text);

// ==============================
// 滚动相关
// ==============================
void SetScrollBarStyle(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, bool visible, float width, uint32_t color);

void SetDefaultScrollStyle(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node);

// ==============================
// 异步任务
// ==============================
void PostDelayedTask(int32_t delayMs, std::function<void()> task);

// ==============================
// N-API 工具
// ==============================
std::string GetStringFromNapi(napi_env env, napi_value value);

bool IsNapiArray(napi_env env, napi_value value);

ArkUI_NodeContentHandle GetNodeContentFromNapi(napi_env env, napi_callback_info info);

void AddNodeToContent(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node);

// ==============================
// 节点事件注册器
// ==============================
class NodeEventRegistrar {
public:
    NodeEventRegistrar(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node);
    ~NodeEventRegistrar();

    void RegisterEvent(ArkUI_NodeEventType eventType, void *userData);
    void RegisterMultipleEvents(std::initializer_list<ArkUI_NodeEventType> eventTypes, void *userData);

private:
    ArkUI_NativeNodeAPI_1 *nodeApi_ = nullptr;
    ArkUI_NodeHandle nodeHandle_ = nullptr;
    std::vector<ArkUI_NodeEventType> registeredEventTypes_;
};

// ==============================
// Adapter 事件接收器
// ==============================
class AdapterEventRegistrar {
public:
    AdapterEventRegistrar(ArkUI_NodeAdapterHandle adapter, void *userData, void (*callback)(ArkUI_NodeAdapterEvent *));
    ~AdapterEventRegistrar();

private:
    ArkUI_NodeAdapterHandle adapterHandle_ = nullptr;
};

#endif // SCROLLABLE_COMPONENT_COMMON_ARKUIUTILS_H
