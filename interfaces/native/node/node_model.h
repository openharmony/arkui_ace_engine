/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#pragma once

#include <cstdint>

#include "native_compatible.h"
#include "native_node.h"
#include "native_type.h"

#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_Node {
    int32_t type;
    ArkUINodeHandle uiNodeHandle = nullptr;
    void* extraData = nullptr;
    void* extraCustomData = nullptr;
    ArkUI_LengthMetricUnit lengthMetricUnit = ARKUI_LENGTH_METRIC_UNIT_DEFAULT;
    void* eventListeners = nullptr;
    void* userData = nullptr;
    void* swiperIndicator = nullptr;
};

struct ArkUI_Context {
    int32_t id;
};

constexpr int BASIC_COMPONENT_NUM = 19;

#ifdef __cplusplus
};
#endif

struct ArkUIFullNodeAPI;

namespace OHOS::Ace::NodeModel {

bool InitialFullImpl();
ArkUIFullNodeAPI* GetFullImpl();
ArkUI_NodeHandle CreateNode(ArkUI_NodeType type);
void DisposeNode(ArkUI_NodeHandle nativePtr);

int32_t AddChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode);
int32_t RemoveChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode);
int32_t InsertChildAfter(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode);
int32_t InsertChildBefore(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode);
int32_t InsertChildAt(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, int32_t position);

// deprecated.
[[deprecated]] void SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const char* value);

int32_t SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* value);
const ArkUI_AttributeItem* GetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);
int32_t ResetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

int32_t RegisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t targetId);
int32_t RegisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t targetId, void* userData);
void UnregisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType);
void RegisterOnEvent(void (*eventReceiver)(ArkUI_NodeEvent* event));
void RegisterOnEvent(void (*eventReceiver)(ArkUI_CompatibleNodeEvent* event));
void UnregisterOnEvent();
int32_t CheckEvent(ArkUI_NodeEvent* event);
void HandleInnerNodeEvent(ArkUINodeEvent* innerEvent);
int32_t GetNativeNodeEventType(ArkUINodeEvent* innerEvent);
void HandleNodeEvent(ArkUI_NodeEvent* event);
void ApplyModifierFinish(ArkUI_NodeHandle nodePtr);
void MarkDirty(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag);

int32_t SetUserData(ArkUI_NodeHandle node, void* userData);
void* GetUserData(ArkUI_NodeHandle node);
int32_t SetLengthMetricUnit(ArkUI_NodeHandle nodePtr, ArkUI_LengthMetricUnit unit);
int32_t AddNodeEventReceiver(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));
int32_t RemoveNodeEventReceiver(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));
}; // namespace OHOS::Ace::NodeModel
