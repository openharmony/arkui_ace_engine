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

#include "node_model_safely.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"
#include "node_extened.h"
#include "node_model.h"

#ifdef __cplusplus
extern "C" {
#endif
int32_t OH_ArkUI_PostAsyncUITask(ArkUI_ContextHandle context,
    void* asyncUITaskData, void (*asyncUITask)(void* asyncUITaskData), void(*onFinish)(void* asyncUITaskData))
{
    if (!context || !asyncUITask) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* contextPtr = reinterpret_cast<ArkUI_Context*>(context);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    return impl->getMultiThreadManagerAPI()->postAsyncUITask(contextPtr->id, asyncUITaskData, asyncUITask, onFinish);
}

int32_t OH_ArkUI_PostUITask(ArkUI_ContextHandle context, void* taskData, void(*task)(void* taskData))
{
    if (!context || !task) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* contextPtr = reinterpret_cast<ArkUI_Context*>(context);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    return impl->getMultiThreadManagerAPI()->postUITask(contextPtr->id, taskData, task);
}

int32_t OH_ArkUI_PostUITaskAndWait(ArkUI_ContextHandle context, void* taskData, void(*task)(void* taskData))
{
    if (!context || !task) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* contextPtr = reinterpret_cast<ArkUI_Context*>(context);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    return impl->getMultiThreadManagerAPI()->postUITaskAndWait(contextPtr->id, taskData, task);
}
#ifdef __cplusplus
};
#endif

namespace OHOS::Ace::NodeModel {
class FreeNodeScope {
public:
    explicit FreeNodeScope()
    {
        GetFullImpl()->getMultiThreadManagerAPI()->setIsFreeNodeScope(true);
    }

    ~FreeNodeScope()
    {
        GetFullImpl()->getMultiThreadManagerAPI()->setIsFreeNodeScope(false);
    }
};

ArkUI_NodeHandle CreateNodeSafely(ArkUI_NodeType type)
{
    FreeNodeScope freeNodeScope;
    return CreateNodeInner(type, true);
}

void DisposeNodeSafely(ArkUI_NodeHandle nativePtr)
{
    CHECK_NULL_VOID(nativePtr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nativePtr->uiNodeHandle)) {
        return;
    }
    FreeNodeScope freeNodeScope;
    DisposeNode(nativePtr);
}

int32_t AddChildSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(parentNode->uiNodeHandle) ||
        !impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(childNode->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return AddChild(parentNode, childNode);
}

int32_t RemoveChildSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(parentNode->uiNodeHandle) ||
        !impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(childNode->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return RemoveChild(parentNode, childNode);
}

int32_t InsertChildAfterSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(parentNode->uiNodeHandle) ||
        !impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(childNode->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return InsertChildAfter(parentNode, childNode, siblingNode);
}

int32_t InsertChildBeforeSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(parentNode->uiNodeHandle) ||
        !impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(childNode->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return InsertChildBefore(parentNode, childNode, siblingNode);
}

int32_t InsertChildAtSafely(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, int32_t position)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(parentNode->uiNodeHandle) ||
        !impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(childNode->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return InsertChildAt(parentNode, childNode, position);
}

int32_t SetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* value)
{
    CHECK_NULL_RETURN(node, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return SetAttribute(node, attribute, value);
}

int32_t ResetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    CHECK_NULL_RETURN(node, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return ResetAttribute(node, attribute);
}

const ArkUI_AttributeItem* GetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    FreeNodeScope freeNodeScope;
    return GetAttribute(node, attribute);
}

int32_t RegisterNodeEventSafely(ArkUI_NodeHandle nodePtr,
    ArkUI_NodeEventType eventType, int32_t targetId, void* userData)
{
    CHECK_NULL_RETURN(nodePtr, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return RegisterNodeEvent(nodePtr, eventType, targetId, userData);
}

void UnregisterNodeEventSafely(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType)
{
    CHECK_NULL_VOID(nodePtr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return;
    }
    FreeNodeScope freeNodeScope;
    UnregisterNodeEvent(nodePtr, eventType);
}

void RegisterOnEventSafely(void (*eventReceiver)(ArkUI_NodeEvent* event))
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        RegisterOnEvent(eventReceiver);
    }
}

void UnregisterOnEventSafely()
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        UnregisterOnEvent();
    }
}

int32_t SetUserDataSafely(ArkUI_NodeHandle node, void* userData)
{
    CHECK_NULL_RETURN(node, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return SetUserData(node, userData);
    }
    return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
}

void* GetUserDataSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return GetUserData(node);
    }
    return nullptr;
}

int32_t SetLengthMetricUnitSafely(ArkUI_NodeHandle nodePtr, ArkUI_LengthMetricUnit unit)
{
    CHECK_NULL_RETURN(nodePtr, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return SetLengthMetricUnit(nodePtr, unit);
}

void MarkDirtySafely(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag)
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        MarkDirty(nodePtr, dirtyFlag);
    }
}

int32_t AddNodeEventReceiverSafely(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeEvent* event))
{
    CHECK_NULL_RETURN(nodePtr, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return AddNodeEventReceiver(nodePtr, eventReceiver);
}

int32_t RemoveNodeEventReceiverSafely(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeEvent* event))
{
    CHECK_NULL_RETURN(nodePtr, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return RemoveNodeEventReceiver(nodePtr, eventReceiver);
}

int32_t RegisterNodeCustomEventSafely(ArkUI_NodeHandle node,
    ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData)
{
    CHECK_NULL_RETURN(node, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return RegisterNodeCustomEvent(node, eventType, targetId, userData);
}

void UnregisterNodeCustomEventSafely(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType)
{
    CHECK_NULL_VOID(node);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return;
    }
    FreeNodeScope freeNodeScope;
    UnregisterNodeCustomEvent(node, eventType);
}

void RegisterNodeCustomReceiverSafely(void (*eventReceiver)(ArkUI_NodeCustomEvent* event))
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        RegisterNodeCustomReceiver(eventReceiver);
    }
}

void UnregisterNodeCustomEventReceiverSafely()
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        UnregisterNodeCustomEventReceiver();
    }
}

int32_t AddNodeCustomEventReceiverSafely(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeCustomEvent* event))
{
    CHECK_NULL_RETURN(nodePtr, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return AddNodeCustomEventReceiver(nodePtr, eventReceiver);
}

int32_t RemoveNodeCustomEventReceiverSafely(ArkUI_NodeHandle nodePtr,
    void (*eventReceiver)(ArkUI_NodeCustomEvent* event))
{
    CHECK_NULL_RETURN(nodePtr, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return RemoveNodeCustomEventReceiver(nodePtr, eventReceiver);
}

int32_t SetMeasuredSizeSafely(ArkUI_NodeHandle node, int32_t width, int32_t height)
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        return SetMeasuredSize(node, width, height);
    }
    return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
}

int32_t SetLayoutPositionSafely(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY)
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        return SetLayoutPosition(node, positionX, positionY);
    }
    return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
}

ArkUI_IntSize GetMeasuredSizeSafely(ArkUI_NodeHandle node)
{
    ArkUI_IntSize size;
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        return GetMeasuredSize(node);
    }
    return size;
}

ArkUI_IntOffset GetLayoutPositionSafely(ArkUI_NodeHandle node)
{
    ArkUI_IntOffset offset;
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        return GetLayoutPosition(node);
    }
    return offset;
}

int32_t MeasureNodeSafely(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* constraint)
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        return MeasureNode(node, constraint);
    }
    return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
}

int32_t LayoutNodeSafely(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY)
{
    auto* impl = GetFullImpl();
    if (impl->getMultiThreadManagerAPI()->checkOnUIThread()) {
        return LayoutNode(node, positionX, positionY);
    }
    return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
}

uint32_t GetTotalChildCountSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, 0);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return 0;
    }
    FreeNodeScope freeNodeScope;
    return GetTotalChildCount(node);
}

ArkUI_NodeHandle GetChildAtSafely(ArkUI_NodeHandle node, int32_t position)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    FreeNodeScope freeNodeScope;
    return GetChildAt(node, position);
}

ArkUI_NodeHandle GetFirstChildSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    FreeNodeScope freeNodeScope;
    return GetFirstChild(node);
}

ArkUI_NodeHandle GetLastChildSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    FreeNodeScope freeNodeScope;
    return GetLastChild(node);
}

ArkUI_NodeHandle GetPreviousSiblingSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    FreeNodeScope freeNodeScope;
    return GetPreviousSibling(node);
}

ArkUI_NodeHandle GetNextSiblingSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    FreeNodeScope freeNodeScope;
    return GetNextSibling(node);
}

ArkUI_NodeHandle GetParentSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    FreeNodeScope freeNodeScope;
    return GetParent(node);
}

int32_t RemoveAllChildrenSafely(ArkUI_NodeHandle parentNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(parentNode->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    FreeNodeScope freeNodeScope;
    return RemoveAllChildren(parentNode);
}
} // namespace OHOS::Ace::NodeModel