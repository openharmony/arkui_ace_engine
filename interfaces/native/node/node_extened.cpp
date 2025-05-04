/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "node_extened.h"


#include "node_model.h"

#include "base/error/error_code.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NodeModel {

struct InnerCustomExtraParam  {
    int32_t targetId;
    void* userData;
};

struct ExtraCustomData {
    std::unordered_map<int64_t, InnerCustomExtraParam*> eventMap;
};

void NodeAddExtraData(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData)
{
    if (!node->extraCustomData) {
        node->extraCustomData = new ExtraCustomData();
    }

    auto* extraCustomData = reinterpret_cast<ExtraCustomData*>(node->extraCustomData);
    auto& eventMap = extraCustomData->eventMap;

    auto it = eventMap.find(eventType);
    if (it != eventMap.end()) {
        it->second->targetId = targetId;
    } else {
        auto eventExtraParam = new InnerCustomExtraParam({ targetId, userData });
        eventMap.emplace(eventType, eventExtraParam);
    }
}

int32_t RegisterNodeCustomEvent(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData)
{
    if (!node || !CheckIsCNode(node)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (eventType <= 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Custom event is not supported %{public}d", eventType);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE) {
        if (node->type == ARKUI_NODE_CUSTOM || node->type == ARKUI_NODE_CUSTOM_SPAN) {
            NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE, targetId, userData);
        } else {
            return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
        }
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT) {
        if (node->type == ARKUI_NODE_CUSTOM) {
            NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT, targetId, userData);
        } else {
            return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
        }
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_DRAW) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW, targetId, userData);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_FRONT) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_FRONT, targetId, userData);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_BEHIND) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_BEHIND, targetId, userData);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW, targetId, userData);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW, targetId, userData);
    }
    const auto* impl = GetFullImpl();
    if (node->type == ARKUI_NODE_CUSTOM_SPAN) {
        impl->getExtendedAPI()->registerCustomSpanAsyncEvent(
            node->uiNodeHandle, eventType, reinterpret_cast<void*>(node));
    } else {
        impl->getExtendedAPI()->registerCustomNodeAsyncEvent(
            node->uiNodeHandle, eventType, reinterpret_cast<void*>(node));
    }
    return ERROR_CODE_NO_ERROR;
}

void NodeRemoveExtraData(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType)
{
    auto* extraCustomData = reinterpret_cast<ExtraCustomData*>(node->extraCustomData);
    auto& eventMap = extraCustomData->eventMap;
    auto innerEventExtraParam = eventMap.find(eventType);
    if (innerEventExtraParam == eventMap.end()) {
        return;
    }
    delete innerEventExtraParam->second;
    eventMap.erase(innerEventExtraParam);
    if (eventMap.empty()) {
        delete extraCustomData;
        node->extraCustomData = nullptr;
    }
}

void UnregisterNodeCustomEvent(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType)
{
    if (node == nullptr || !node->extraCustomData || !CheckIsCNode(node)) {
        return;
    }
    const auto* impl = GetFullImpl();
    
    auto resultValue = impl->getExtendedAPI()->unregisterCustomNodeAsyncEvent(node->uiNodeHandle, eventType);
    if (resultValue == -1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Custom event Unregister error %{public}d", eventType);
        return;
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE) {
        NodeRemoveExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT) {
        NodeRemoveExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_DRAW) {
        NodeRemoveExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_FRONT) {
        NodeRemoveExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_FRONT);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_BEHIND) {
        NodeRemoveExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_BEHIND);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW) {
        NodeRemoveExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW) {
        NodeRemoveExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW);
    }
}

void (*g_customEventReceiver)(ArkUI_NodeCustomEvent* event) = nullptr;
void RegisterNodeCustomReceiver(void (*eventReceiver)(ArkUI_NodeCustomEvent* event))
{
    g_customEventReceiver = eventReceiver;
}

void UnregisterNodeCustomEventReceiver()
{
    g_customEventReceiver = nullptr;
}

void HandleInnerCustomEvent(ArkUICustomNodeEvent* origin)
{
    if (!origin) {
        return;
    }
    auto* nodePtr = reinterpret_cast<ArkUI_NodeHandle>(origin->extraParam);
    if (!IsValidArkUINode(nodePtr) || !nodePtr->extraCustomData) {
        return;
    }

    auto* extraCustomData = reinterpret_cast<ExtraCustomData*>(nodePtr->extraCustomData);
    ArkUI_NodeCustomEventType eventType = static_cast<ArkUI_NodeCustomEventType>(origin->kind);

    auto innerEventExtraParam = extraCustomData->eventMap.find(eventType);
    if (innerEventExtraParam == extraCustomData->eventMap.end()) {
        return;
    }
    ArkUI_NodeCustomEvent event;
    event.event = origin;
    event.node = nodePtr;
    event.targetId = innerEventExtraParam->second->targetId;
    event.userData = innerEventExtraParam->second->userData;
    HandleCustomEvent(&event);
}

void HandleCustomEvent(ArkUI_NodeCustomEvent* event)
{
    if (!event) {
        return;
    }
    if (event->node && event->node->customEventListeners) {
        auto eventListenersSet = reinterpret_cast<std::set<void (*)(ArkUI_NodeCustomEvent*)>*>(
            event->node->customEventListeners);
        if (eventListenersSet) {
            for (const auto& eventlistener : *eventListenersSet) {
                (*eventlistener)(event);
            }
        }
    }
    if (g_customEventReceiver) {
        g_customEventReceiver(event);
    }
}

int32_t AddNodeCustomEventReceiver(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeCustomEvent* event))
{
    if (!nodePtr || !eventReceiver || !CheckIsCNode(nodePtr)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!nodePtr->customEventListeners) {
        nodePtr->customEventListeners = new std::set<void (*)(ArkUI_NodeCustomEvent*)>();
    }
    auto eventListenersSet = reinterpret_cast<std::set<void (*)(ArkUI_NodeCustomEvent*)>*>(
        nodePtr->customEventListeners);
    if (!eventListenersSet) {
        return ERROR_CODE_PARAM_INVALID;
    }
    eventListenersSet->emplace(eventReceiver);
    return ERROR_CODE_NO_ERROR;
}

int32_t RemoveNodeCustomEventReceiver(ArkUI_NodeHandle nodePtr,
    void (*eventReceiver)(ArkUI_NodeCustomEvent* event))
{
    if (!nodePtr || !eventReceiver || !nodePtr->customEventListeners || !CheckIsCNode(nodePtr)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto eventListenersSet = reinterpret_cast<std::set<void (*)(ArkUI_NodeCustomEvent*)>*>(
        nodePtr->customEventListeners);
    if (!eventListenersSet) {
        return ERROR_CODE_PARAM_INVALID;
    }
    eventListenersSet->erase(eventReceiver);
    if (eventListenersSet->empty()) {
        delete eventListenersSet;
        nodePtr->customEventListeners = nullptr;
    }
    return ERROR_CODE_NO_ERROR;
}

int32_t SetMeasuredSize(ArkUI_NodeHandle node, int32_t width, int32_t height)
{
    if (node == nullptr || !CheckIsCNode(node)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = GetFullImpl();
    impl->getExtendedAPI()->setMeasureWidth(node->uiNodeHandle, width > 0 ? width : 0);
    impl->getExtendedAPI()->setMeasureHeight(node->uiNodeHandle, height > 0 ? height : 0);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetLayoutPosition(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY)
{
    if (node == nullptr || !CheckIsCNode(node)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = GetFullImpl();
    impl->getExtendedAPI()->setX(node->uiNodeHandle, positionX);
    impl->getExtendedAPI()->setY(node->uiNodeHandle, positionY);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetLayoutConstraint(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* layoutConstraint)
{
    if (node == nullptr || layoutConstraint == nullptr || !CheckIsCNode(node)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = GetFullImpl();
    // data size
    ArkUI_Int32 data[6];
    impl->getExtendedAPI()->getLayoutConstraint(node->uiNodeHandle, data);
    //minWidth
    layoutConstraint->minWidth = data[0];
    //minHeight
    layoutConstraint->minHeight = data[1];
    //maxWidth
    layoutConstraint->maxWidth = data[2];
    //maxHeight
    layoutConstraint->maxHeight = data[3];
    //percentReferWidth
    layoutConstraint->percentReferWidth = data[4];
    //percentReferHeight
    layoutConstraint->percentReferHeight = data[5];
    return ERROR_CODE_NO_ERROR;
}

ArkUI_IntSize GetMeasuredSize(ArkUI_NodeHandle node)
{
    ArkUI_IntSize size;
    if (node == nullptr) {
        return size;
    }
    const auto* impl = GetFullImpl();
    size.width = impl->getExtendedAPI()->getMeasureWidth(node->uiNodeHandle);
    size.height = impl->getExtendedAPI()->getMeasureHeight(node->uiNodeHandle);
    return size;
}

ArkUI_IntOffset GetLayoutPosition(ArkUI_NodeHandle node)
{
    ArkUI_IntOffset offset;
    if (node == nullptr) {
        return offset;
    }
    const auto* impl = GetFullImpl();
    offset.x = impl->getExtendedAPI()->getX(node->uiNodeHandle);
    offset.y = impl->getExtendedAPI()->getY(node->uiNodeHandle);
    return offset;
}

int32_t MeasureNode(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* constraint)
{
    if (node == nullptr || constraint == nullptr || !CheckIsCNode(node)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = GetFullImpl();
    // data size
    ArkUI_Float32 data[6];
    //minWidth
    data[0] = static_cast<ArkUI_Float32>(constraint->minWidth);
    //minHeight
    data[1] = static_cast<ArkUI_Float32>(constraint->minHeight);
    //maxWidth
    data[2] = static_cast<ArkUI_Float32>(constraint->maxWidth);
    //maxHeight
    data[3] = static_cast<ArkUI_Float32>(constraint->maxHeight);
    //percentReferWidth
    data[4] = static_cast<ArkUI_Float32>(constraint->percentReferWidth);
    //percentReferHeight
    data[5] = static_cast<ArkUI_Float32>(constraint->percentReferHeight);
    impl->getExtendedAPI()->measureNode(nullptr, node->uiNodeHandle, data);
    return ERROR_CODE_NO_ERROR;
}

int32_t LayoutNode(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY)
{
    if (node == nullptr || !CheckIsCNode(node)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = GetFullImpl();
    //layout data size
    float data[2];
    //positionX
    data[0] = positionX;
    //positionY
    data[1] = positionY;
    impl->getExtendedAPI()->layoutNode(nullptr, node->uiNodeHandle, &data);
    return ERROR_CODE_NO_ERROR;
}

uint32_t GetTotalChildCount(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return 0;
    }
    const auto* impl = GetFullImpl();
    return impl->getNodeModifiers()->getFrameNodeModifier()->getChildrenCount(node->uiNodeHandle, true);
}

ArkUI_NodeHandle GetChildAt(ArkUI_NodeHandle node, int32_t position)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getChild(node->uiNodeHandle, position, true);
    return GetArkUINode(attachNode);
}

ArkUI_NodeHandle GetFirstChild(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getFirst(node->uiNodeHandle, true);
    return GetArkUINode(attachNode);
}

ArkUI_NodeHandle GetLastChild(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getLast(node->uiNodeHandle, true);
    return GetArkUINode(attachNode);
}

ArkUI_NodeHandle GetPreviousSibling(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getPreviousSibling(node->uiNodeHandle, true);
    return GetArkUINode(attachNode);
}

ArkUI_NodeHandle GetNextSibling(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getNextSibling(node->uiNodeHandle, true);
    return GetArkUINode(attachNode);
}

ArkUI_NodeHandle GetParent(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = GetFullImpl();
    auto* value = impl->getNodeModifiers()->getFrameNodeModifier()->getParent(node->uiNodeHandle);
    void* attachNode = impl->getExtendedAPI()->getAttachNodePtr(value);
    if (attachNode) {
        return reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    return nullptr;
}

int32_t RemoveAllChildren(ArkUI_NodeHandle parentNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    const auto* impl = GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->clearChildren(parentNode->uiNodeHandle);
    return ERROR_CODE_NO_ERROR;
}
} // namespace OHOS::Ace::NodeModel
