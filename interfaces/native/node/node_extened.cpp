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

#include <cstdint>
#include <unordered_map>

#include "event_converter.h"
#include "node_model.h"
#include "style_modifier.h"

#include "base/error/error_code.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NodeModel {

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;

struct InnerEventExtraParam {
    int32_t targetId;
    void* userData;
};

struct ExtraData {
    std::unordered_map<int64_t, InnerEventExtraParam*> eventMap;
};

void NodeAddExtraData(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData)
{
    if (!node->extraData) {
        node->extraData = new ExtraData();
    }

    auto* extraData = reinterpret_cast<ExtraData*>(node->extraData);
    auto& eventMap = extraData->eventMap;

    auto it = eventMap.find(eventType);
    if (it != eventMap.end()) {
        it->second->targetId = targetId;
    } else {
        auto eventExtraParam = new InnerEventExtraParam({ targetId, userData });
        eventMap.emplace(eventType, eventExtraParam);
    }
}

int32_t RegisterNodeCustomEvent(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData)
{
    if (eventType <= 0 || node->type != ARKUI_NODE_CUSTOM) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Custom event is not supported %{public}d", eventType);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    auto* impl = GetFullImpl();

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE, targetId, userData);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT, targetId, userData);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_DRAW) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_DRAW, targetId, userData);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW, targetId, userData);
    }

    if (eventType & ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW) {
        NodeAddExtraData(node, ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW, targetId, userData);
    }
    impl->getExtendedAPI()->registerCustomNodeAsyncEvent(
        node->uiNodeHandle, eventType, reinterpret_cast<void*>(node));
    return ERROR_CODE_NO_ERROR;
}

void NodeRemoveExtraData(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType)
{
    auto* extraData = reinterpret_cast<ExtraData*>(node->extraData);
    auto& eventMap = extraData->eventMap;
    auto innerEventExtraParam = eventMap.find(eventType);
    if (innerEventExtraParam == eventMap.end()) {
        return;
    }
    delete innerEventExtraParam->second;
    eventMap.erase(innerEventExtraParam);
    if (eventMap.empty()) {
        delete extraData;
        node->extraData = nullptr;
    }
}

void UnregisterNodeCustomEvent(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType)
{
    if (!node->extraData) {
        return;
    }
    auto* impl = GetFullImpl();
    
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
    if (g_customEventReceiver) {
        // already check in entry point.
        auto* impl = GetFullImpl();
        auto innerReceiver = [](ArkUICustomNodeEvent* origin) {
            if (g_customEventReceiver) {
                auto* nodePtr = reinterpret_cast<ArkUI_NodeHandle>(origin->extraParam);
                if (!nodePtr->extraData) {
                    return;
                }

                auto* extraData = reinterpret_cast<ExtraData*>(nodePtr->extraData);
                ArkUI_NodeCustomEventType eventType = static_cast<ArkUI_NodeCustomEventType>(origin->kind);

                auto innerEventExtraParam = extraData->eventMap.find(eventType);
                if (innerEventExtraParam == extraData->eventMap.end()) {
                    return;
                }
                ArkUI_NodeCustomEvent event;
                if (ConvertCustomEvent(origin, &event)) {
                    event.kind = origin->kind;
                    event.canvas = origin->canvas;
                    event.node = nodePtr;
                    event.targetId = innerEventExtraParam->second->targetId;
                    event.userData = innerEventExtraParam->second->userData;
                    g_customEventReceiver(&event);
                }
            }
        };
        impl->getExtendedAPI()->registerCustomNodeAsyncEventReceiver(innerReceiver);
    }
}

void UnregisterNodeCustomEventReceiver()
{
    g_customEventReceiver = nullptr;
}

int32_t SetMeasuredSize(ArkUI_NodeHandle node, int32_t width, int32_t height)
{
    auto* impl = GetFullImpl();
    impl->getExtendedAPI()->setMeasureWidth(node->uiNodeHandle, width);
    impl->getExtendedAPI()->setMeasureHeight(node->uiNodeHandle, height);
    return ERROR_CODE_NO_ERROR;
}

int32_t SetLayoutPosition(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY)
{
    auto* impl = GetFullImpl();
    impl->getExtendedAPI()->setX(node->uiNodeHandle, positionX);
    impl->getExtendedAPI()->setY(node->uiNodeHandle, positionY);
    return ERROR_CODE_NO_ERROR;
}

int32_t GetLayoutConstraint(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* layoutConstraint)
{
    auto* impl = GetFullImpl();
    ArkUI_Int32 data[NUM_6];
    impl->getExtendedAPI()->getLayoutConstraint(node->uiNodeHandle, data);
    layoutConstraint->minWidth = data[NUM_0];
    layoutConstraint->minHeight = data[NUM_1];
    layoutConstraint->maxWidth = data[NUM_2];
    layoutConstraint->maxHeight = data[NUM_3];
    layoutConstraint->percentReferWidth = data[NUM_4];
    layoutConstraint->percentReferHeight = data[NUM_5];
    return ERROR_CODE_NO_ERROR;
}

ArkUI_IntSize GetMeasuredSize(ArkUI_NodeHandle node)
{
    ArkUI_IntSize size;
    auto* impl = GetFullImpl();
    size.width = impl->getExtendedAPI()->getMeasureWidth(node->uiNodeHandle);
    size.height = impl->getExtendedAPI()->getMeasureHeight(node->uiNodeHandle);
    return size;
}

ArkUI_IntOffset GetLayoutPosition(ArkUI_NodeHandle node)
{
    ArkUI_IntOffset offset;
    auto* impl = GetFullImpl();
    offset.x = impl->getExtendedAPI()->getX(node->uiNodeHandle);
    offset.y = impl->getExtendedAPI()->getY(node->uiNodeHandle);
    return offset;
}

int32_t MeasureNode(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* constraint)
{
    auto* impl = GetFullImpl();
    ArkUI_Float32 data[NUM_6];
    data[NUM_0] = static_cast<ArkUI_Float32>(constraint->minWidth);
    data[NUM_1] = static_cast<ArkUI_Float32>(constraint->minHeight);
    data[NUM_2] = static_cast<ArkUI_Float32>(constraint->maxWidth);
    data[NUM_3] = static_cast<ArkUI_Float32>(constraint->maxHeight);
    data[NUM_4] = static_cast<ArkUI_Float32>(constraint->percentReferWidth);
    data[NUM_5] = static_cast<ArkUI_Float32>(constraint->percentReferHeight);
    impl->getExtendedAPI()->measureNode(nullptr, node->uiNodeHandle, data);
    return ERROR_CODE_NO_ERROR;
}

int32_t LayoutNode(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY)
{
    auto* impl = GetFullImpl();
    float data[NUM_2];
    data[NUM_0] = positionX;
    data[NUM_1] = positionY;
    impl->getExtendedAPI()->layoutNode(nullptr, node->uiNodeHandle, data);
    return ERROR_CODE_NO_ERROR;
}

uint32_t GetTotalChildCount(ArkUI_NodeHandle node)
{
    auto* impl = GetFullImpl();
    return impl->getNodeModifiers()->getFrameNodeModifier()->getChildrenCount(node->uiNodeHandle);
}

ArkUI_NodeHandle GetChildAt(ArkUI_NodeHandle node, int32_t position)
{
    auto* impl = GetFullImpl();
    auto* value = impl->getNodeModifiers()->getFrameNodeModifier()->getChild(node->uiNodeHandle, position);
    void* attachNode = impl->getExtendedAPI()->getAttachNodePtr(value);
    if (attachNode) {
        return reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    return nullptr;
}

ArkUI_NodeHandle GetFirstChild(ArkUI_NodeHandle node)
{
    auto* impl = GetFullImpl();
    auto* value = impl->getNodeModifiers()->getFrameNodeModifier()->getFirst(node->uiNodeHandle);
    void* attachNode = impl->getExtendedAPI()->getAttachNodePtr(value);
    if (attachNode) {
        return reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    return nullptr;
}

ArkUI_NodeHandle GetLastChild(ArkUI_NodeHandle node)
{
    auto* impl = GetFullImpl();
    auto* value = impl->getNodeModifiers()->getFrameNodeModifier()->getLast(node->uiNodeHandle);
    void* attachNode = impl->getExtendedAPI()->getAttachNodePtr(value);
    if (attachNode) {
        return reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    return nullptr;
}

ArkUI_NodeHandle GetPreviousSibling(ArkUI_NodeHandle node)
{
    auto* impl = GetFullImpl();
    auto* value = impl->getNodeModifiers()->getFrameNodeModifier()->getPreviousSibling(node->uiNodeHandle);
    void* attachNode = impl->getExtendedAPI()->getAttachNodePtr(value);
    if (attachNode) {
        return reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    return nullptr;
}

ArkUI_NodeHandle GetNextSibling(ArkUI_NodeHandle node)
{
    auto* impl = GetFullImpl();
    auto* value = impl->getNodeModifiers()->getFrameNodeModifier()->getNextSibling(node->uiNodeHandle);
    void* attachNode = impl->getExtendedAPI()->getAttachNodePtr(value);
    if (attachNode) {
        return reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    return nullptr;
}

} // namespace OHOS::Ace::NodeModel
