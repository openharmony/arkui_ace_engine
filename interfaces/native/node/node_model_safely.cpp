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
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    return impl->getMultiThreadManagerAPI()->postAsyncUITask(contextPtr->id, asyncUITaskData, asyncUITask, onFinish);
}

int32_t OH_ArkUI_PostUITask(ArkUI_ContextHandle context, void* taskData, void(*task)(void* taskData))
{
    if (!context || !task) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* contextPtr = reinterpret_cast<ArkUI_Context*>(context);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    return impl->getMultiThreadManagerAPI()->postUITask(contextPtr->id, taskData, task);
}

int32_t OH_ArkUI_PostUITaskAndWait(ArkUI_ContextHandle context, void* taskData, void(*task)(void* taskData))
{
    if (!context || !task) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto* contextPtr = reinterpret_cast<ArkUI_Context*>(context);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    return impl->getMultiThreadManagerAPI()->postUITaskAndWait(contextPtr->id, taskData, task);
}
#ifdef __cplusplus
};
#endif

namespace OHOS::Ace::NodeModel {
class ThreadSafeNodeScope {
public:
    ThreadSafeNodeScope()
    {
        GetFullImpl()->getMultiThreadManagerAPI()->setIsThreadSafeNodeScope(true);
    }

    ~ThreadSafeNodeScope()
    {
        GetFullImpl()->getMultiThreadManagerAPI()->setIsThreadSafeNodeScope(false);
    }
};

std::mutex g_nodeSetMutex_;
std::set<ArkUI_NodeHandle> g_nodeSetSafely;

ArkUI_NodeHandle CreateNodeSafely(ArkUI_NodeType type)
{
    static const ArkUINodeType nodes[] = { ARKUI_CUSTOM, ARKUI_TEXT, ARKUI_SPAN, ARKUI_IMAGE_SPAN, ARKUI_IMAGE,
        ARKUI_TOGGLE, ARKUI_LOADING_PROGRESS, ARKUI_TEXT_INPUT, ARKUI_TEXTAREA, ARKUI_BUTTON, ARKUI_PROGRESS,
        ARKUI_CHECKBOX, ARKUI_XCOMPONENT, ARKUI_DATE_PICKER, ARKUI_TIME_PICKER, ARKUI_TEXT_PICKER,
        ARKUI_CALENDAR_PICKER, ARKUI_SLIDER, ARKUI_RADIO, ARKUI_IMAGE_ANIMATOR, ARKUI_XCOMPONENT_TEXTURE,
        ARKUI_CHECK_BOX_GROUP, ARKUI_STACK, ARKUI_SWIPER, ARKUI_SCROLL, ARKUI_LIST, ARKUI_LIST_ITEM,
        ARKUI_LIST_ITEM_GROUP, ARKUI_COLUMN, ARKUI_ROW, ARKUI_FLEX, ARKUI_REFRESH, ARKUI_WATER_FLOW, ARKUI_FLOW_ITEM,
        ARKUI_RELATIVE_CONTAINER, ARKUI_GRID, ARKUI_GRID_ITEM, ARKUI_CUSTOM_SPAN };
    // already check in entry point.
    uint32_t nodeType = type < MAX_NODE_SCOPE_NUM ? type : (type - MAX_NODE_SCOPE_NUM + BASIC_COMPONENT_NUM);
    const auto* impl = GetFullImpl();
    if (nodeType >= sizeof(nodes) / sizeof(ArkUINodeType)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node type: %{public}d NOT IMPLEMENT", type);
        return nullptr;
    }

    ArkUI_Int32 id = ARKUI_AUTO_GENERATE_NODE_ID;
    ThreadSafeNodeScope threadSafeNodeScope;
    auto* uiNode = impl->getBasicAPI()->createNode(nodes[nodeType], id, ARKUI_NODE_FLAG_C);
    if (!uiNode) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node type: %{public}d can not find in full impl", type);
        return nullptr;
    }
    impl->getBasicAPI()->markDirty(uiNode, ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF);
    ArkUI_Node* arkUINode = new ArkUI_Node({ type, uiNode, true, true });
    impl->getExtendedAPI()->setAttachNodePtr(uiNode, reinterpret_cast<void*>(arkUINode));
    std::lock_guard<std::mutex> lock(g_nodeSetMutex_);
    g_nodeSetSafely.emplace(arkUINode);
    return arkUINode;
}

void DisposeNodeSafely(ArkUI_NodeHandle nativePtr)
{
    CHECK_NULL_VOID(nativePtr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nativePtr->uiNodeHandle)) {
        return;
    }
    if (!(nativePtr->threadSafeNode)) {
        DisposeNode(nativePtr);
        return;
    }
    if (!CheckIsCNode(nativePtr)) {
        return;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    impl->getBasicAPI()->disposeNode(nativePtr->uiNodeHandle);
    DisposeNativeSource(nativePtr);
    std::lock_guard<std::mutex> lock(g_nodeSetMutex_);
    g_nodeSetSafely.erase(nativePtr);
    delete nativePtr;
    nativePtr = nullptr;
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
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
    return InsertChildAt(parentNode, childNode, position);
}

int32_t SetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* value)
{
    CHECK_NULL_RETURN(node, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return SetAttribute(node, attribute, value);
}

int32_t ResetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    CHECK_NULL_RETURN(node, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return ResetAttribute(node, attribute);
}

const ArkUI_AttributeItem* GetAttributeSafely(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
    return RegisterNodeEvent(nodePtr, eventType, targetId, userData);
}

void UnregisterNodeEventSafely(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType)
{
    CHECK_NULL_VOID(nodePtr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
    return AddNodeEventReceiver(nodePtr, eventReceiver);
}

int32_t RemoveNodeEventReceiverSafely(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeEvent* event))
{
    CHECK_NULL_RETURN(nodePtr, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(nodePtr->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
    return RegisterNodeCustomEvent(node, eventType, targetId, userData);
}

void UnregisterNodeCustomEventSafely(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType)
{
    CHECK_NULL_VOID(node);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
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
    ThreadSafeNodeScope threadSafeNodeScope;
    return GetTotalChildCount(node);
}

ArkUI_NodeHandle GetChildAtSafely(ArkUI_NodeHandle node, int32_t position)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return GetChildAt(node, position);
}

ArkUI_NodeHandle GetFirstChildSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return GetFirstChild(node);
}

ArkUI_NodeHandle GetLastChildSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return GetLastChild(node);
}

ArkUI_NodeHandle GetPreviousSiblingSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return GetPreviousSibling(node);
}

ArkUI_NodeHandle GetNextSiblingSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return GetNextSibling(node);
}

ArkUI_NodeHandle GetParentSafely(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(node->uiNodeHandle)) {
        return nullptr;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return GetParent(node);
}

int32_t RemoveAllChildrenSafely(ArkUI_NodeHandle parentNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    auto* impl = GetFullImpl();
    if (!impl->getMultiThreadManagerAPI()->checkNodeOnValidThread(parentNode->uiNodeHandle)) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ON_INVALID_THREAD;
    }
    ThreadSafeNodeScope threadSafeNodeScope;
    return RemoveAllChildren(parentNode);
}

bool IsValidArkUINodeMultiThread(ArkUI_NodeHandle nodePtr)
{
    std::lock_guard<std::mutex> lock(g_nodeSetMutex_);
    return g_nodeSetSafely.count(nodePtr) > 0;
}
} // namespace OHOS::Ace::NodeModel