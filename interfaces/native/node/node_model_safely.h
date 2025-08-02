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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_MODEL_SAFELY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_MODEL_SAFELY_H
#include "node_model.h"

namespace OHOS::Ace::NodeModel {
ArkUI_NodeHandle CreateNodeSafely(ArkUI_NodeType type);
void DisposeNodeSafely(ArkUI_NodeHandle nativePtr);
int32_t AddChildSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode);
int32_t RemoveChildSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode);
int32_t InsertChildAfterSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode);
int32_t InsertChildBeforeSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode);
int32_t InsertChildAtSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, int32_t position);
int32_t SetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* value);
const ArkUI_AttributeItem* GetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);
int32_t ResetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);
int32_t RegisterNodeEventSafely(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType,
    int32_t targetId, void* userData);
void UnregisterNodeEventSafely(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType);
void RegisterOnEventSafely(void (*eventReceiver)(ArkUI_NodeEvent* event));
void UnregisterOnEventSafely();
void MarkDirtySafely(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag);
int32_t AddNodeEventReceiverSafely(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));
int32_t RemoveNodeEventReceiverSafely(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));
int32_t SetUserDataSafely(ArkUI_NodeHandle node, void* userData);
void* GetUserDataSafely(ArkUI_NodeHandle node);
int32_t SetLengthMetricUnitSafely(ArkUI_NodeHandle nodePtr, ArkUI_LengthMetricUnit unit);
uint32_t GetTotalChildCountSafely(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetChildAtSafely(ArkUI_NodeHandle node, int32_t position);
ArkUI_NodeHandle GetFirstChildSafely(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetLastChildSafely(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetPreviousSiblingSafely(ArkUI_NodeHandle node);
ArkUI_NodeHandle GetNextSiblingSafely(ArkUI_NodeHandle node);
int32_t RegisterNodeCustomEventSafely(
    ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData);
void UnregisterNodeCustomEventSafely(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType);
void RegisterNodeCustomReceiverSafely(void (*eventReceiver)(ArkUI_NodeCustomEvent* event));
void UnregisterNodeCustomEventReceiverSafely();
int32_t SetMeasuredSizeSafely(ArkUI_NodeHandle node, int32_t width, int32_t height);
int32_t SetLayoutPositionSafely(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY);
ArkUI_IntSize GetMeasuredSizeSafely(ArkUI_NodeHandle node);
ArkUI_IntOffset GetLayoutPositionSafely(ArkUI_NodeHandle node);
int32_t MeasureNodeSafely(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* constraint);
int32_t LayoutNodeSafely(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY);
int32_t AddNodeCustomEventReceiverSafely(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeCustomEvent* event));
int32_t RemoveNodeCustomEventReceiverSafely(ArkUI_NodeHandle nodePtr,
    void (*eventReceiver)(ArkUI_NodeCustomEvent* event));
ArkUI_NodeHandle GetParentSafely(ArkUI_NodeHandle node);
int32_t RemoveAllChildrenSafely(ArkUI_NodeHandle parentNode);
bool IsValidArkUINodeMultiThread(ArkUI_NodeHandle nodePtr);
}; // namespace OHOS::Ace::NodeModel
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_MODEL_SAFELY_H