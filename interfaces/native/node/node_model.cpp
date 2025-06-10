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

#include "node_model.h"


#include "event_converter.h"
#include "interfaces/native/event/ui_input_event_impl.h"
#include "node_extened.h"
#include "style_modifier.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NodeModel {
namespace {
#if defined(WINDOWS_PLATFORM)
#include <windows.h>
// Here we need to find module where GetArkUINodeAPI()
// function is implemented.
void* FindModule()
{
    // To find from main exe
    HMODULE result = nullptr;
    const char libname[] = "libace_compatible.dll";
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, libname, &result);
    if (result) {
        return result;
    }
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Cannot find module!");
    return nullptr;
}
void* FindFunction(void* library, const char* name)
{
    return (void*)GetProcAddress(reinterpret_cast<HMODULE>(library), name);
}
#else
#include <dlfcn.h>
void* FindModule()
{
    const char libname[] = "libace_compatible.z.so";
    void* result = dlopen(libname, RTLD_LAZY | RTLD_LOCAL);
    if (result) {
        return result;
    }
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Cannot load libace: %{public}s", dlerror());
    return nullptr;
}

void* FindFunction(void* library, const char* name)
{
    return dlsym(library, name);
}
#endif

ArkUIFullNodeAPI* impl = nullptr;
static bool g_isInitialImpl = InitialFullImpl();

bool InitialFullNodeImpl(int version)
{
    if (!impl) {
        typedef ArkUIAnyAPI* (*GetAPI_t)(int);
        GetAPI_t getAPI = nullptr;
        void* module = FindModule();
        if (module == nullptr) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get module");
            return false;
        }
        // Note, that RTLD_DEFAULT is ((void *) 0).
        getAPI = reinterpret_cast<GetAPI_t>(FindFunction(module, "GetArkUIAnyFullNodeAPI"));
        if (!getAPI) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Cannot find GetArkUIAnyFullNodeAPI()");
            return false;
        }

        impl = reinterpret_cast<ArkUIFullNodeAPI*>((*getAPI)(version));
        if (!impl) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "getAPI() returned null");
            return false;
        }

        if (impl->version != version) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE,
                "API version mismatch: expected %{public}d, but get the version %{public}d", version, impl->version);
            return false;
        }
    }

    impl->getBasicAPI()->registerNodeAsyncEventReceiver(OHOS::Ace::NodeModel::HandleInnerEvent);
    impl->getExtendedAPI()->registerCustomNodeAsyncEventReceiver(OHOS::Ace::NodeModel::HandleInnerCustomEvent);
    return true;
}
} // namespace

ArkUIFullNodeAPI* GetFullImpl()
{
    return impl;
}

bool InitialFullImpl()
{
    return InitialFullNodeImpl(ARKUI_NODE_API_VERSION);
}

struct InnerEventExtraParam {
    int32_t targetId;
    ArkUI_NodeHandle nodePtr;
    void* userData;
};

struct ExtraData {
    std::unordered_map<int64_t, InnerEventExtraParam*> eventMap;
};

std::set<ArkUI_NodeHandle> g_nodeSet;
std::mutex g_nodeSetMutex_;
std::set<ArkUI_NodeHandle> g_nodeSetSafely;

bool IsValidArkUINode(ArkUI_NodeHandle nodePtr)
{
    if (!nodePtr) {
        return false;
    }
    if (nodePtr->freeNode) {
        std::lock_guard<std::mutex> lock(g_nodeSetMutex_);
        return g_nodeSetSafely.count(nodePtr) > 0;
    } else {
        return g_nodeSet.count(nodePtr) > 0;
    }
}

void AddNodeSafely(ArkUI_NodeHandle nodePtr)
{
    if (nodePtr->freeNode) {
        std::lock_guard<std::mutex> lock(g_nodeSetMutex_);
        g_nodeSetSafely.emplace(nodePtr);
    } else {
        g_nodeSet.emplace(nodePtr);
    }
}

void RemoveNodeSafely(ArkUI_NodeHandle nodePtr)
{
    if (nodePtr->freeNode) {
        std::lock_guard<std::mutex> lock(g_nodeSetMutex_);
        g_nodeSetSafely.erase(nodePtr);
    } else {
        g_nodeSet.erase(nodePtr);
    }
}

ArkUI_NodeHandle CreateNodeInner(ArkUI_NodeType type, bool isFreeNode)
{
    static const ArkUINodeType nodes[] = { ARKUI_CUSTOM, ARKUI_TEXT, ARKUI_SPAN, ARKUI_IMAGE_SPAN, ARKUI_IMAGE,
        ARKUI_TOGGLE, ARKUI_LOADING_PROGRESS, ARKUI_TEXT_INPUT, ARKUI_TEXTAREA, ARKUI_BUTTON, ARKUI_PROGRESS,
        ARKUI_CHECKBOX, ARKUI_XCOMPONENT, ARKUI_DATE_PICKER, ARKUI_TIME_PICKER, ARKUI_TEXT_PICKER,
        ARKUI_CALENDAR_PICKER, ARKUI_SLIDER, ARKUI_RADIO, ARKUI_IMAGE_ANIMATOR, ARKUI_XCOMPONENT_TEXTURE,
        ARKUI_CHECK_BOX_GROUP, ARKUI_STACK, ARKUI_SWIPER, ARKUI_SCROLL, ARKUI_LIST, ARKUI_LIST_ITEM,
        ARKUI_LIST_ITEM_GROUP, ARKUI_COLUMN, ARKUI_ROW, ARKUI_FLEX, ARKUI_REFRESH, ARKUI_WATER_FLOW, ARKUI_FLOW_ITEM,
        ARKUI_RELATIVE_CONTAINER, ARKUI_GRID, ARKUI_GRID_ITEM, ARKUI_CUSTOM_SPAN, ARKUI_EMBEDDED_COMPONENT };
    // already check in entry point.
    uint32_t nodeType = type < MAX_NODE_SCOPE_NUM ? type : (type - MAX_NODE_SCOPE_NUM + BASIC_COMPONENT_NUM);
    const auto* impl = GetFullImpl();
    if (nodeType >= sizeof(nodes) / sizeof(ArkUINodeType)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node type: %{public}d NOT IMPLEMENT", type);
        return nullptr;
    }

    ArkUI_Int32 id = ARKUI_AUTO_GENERATE_NODE_ID;
    auto* uiNode = impl->getBasicAPI()->createNode(nodes[nodeType], id, ARKUI_NODE_FLAG_C);
    if (!uiNode) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node type: %{public}d can not find in full impl", type);
        return nullptr;
    }
    impl->getBasicAPI()->markDirty(uiNode, ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF);
    ArkUI_Node* arkUINode = new ArkUI_Node({ type, uiNode, true, isFreeNode });
    impl->getExtendedAPI()->setAttachNodePtr(uiNode, reinterpret_cast<void*>(arkUINode));
    AddNodeSafely(arkUINode);
    return arkUINode;
}

ArkUI_NodeHandle CreateNode(ArkUI_NodeType type)
{
    return CreateNodeInner(type, false);
}

void DisposeNativeSource(ArkUI_NodeHandle nativePtr)
{
    CHECK_NULL_VOID(nativePtr);
    if (!CheckIsCNode(nativePtr)) {
        return;
    }
    if (nativePtr->customEventListeners) {
        auto eventListenersSet = reinterpret_cast<std::set<void (*)(ArkUI_NodeCustomEvent*)>*>(
        nativePtr->customEventListeners);
        if (eventListenersSet) {
            eventListenersSet->clear();
        }
        delete eventListenersSet;
        nativePtr->customEventListeners = nullptr;
    }
    if (nativePtr->eventListeners) {
        auto eventListenersSet = reinterpret_cast<std::set<void (*)(ArkUI_NodeEvent*)>*>(
        nativePtr->eventListeners);
        if (eventListenersSet) {
            eventListenersSet->clear();
        }
        delete eventListenersSet;
        nativePtr->eventListeners = nullptr;
    }
    if (nativePtr->areaChangeRadio) {
        delete[] nativePtr->areaChangeRadio->value;
        delete nativePtr->areaChangeRadio;
        nativePtr->areaChangeRadio = nullptr;
    }
}

void DisposeNode(ArkUI_NodeHandle nativePtr)
{
    CHECK_NULL_VOID(nativePtr);
    if (!CheckIsCNode(nativePtr)) {
        return;
    }
    // already check in entry point.
    const auto* impl = GetFullImpl();
    impl->getBasicAPI()->disposeNode(nativePtr->uiNodeHandle);
    DisposeNativeSource(nativePtr);
    RemoveNodeSafely(nativePtr);
    delete nativePtr;
    nativePtr = nullptr;
}

int32_t AddChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    if (!CheckIsCNode(parentNode) || !CheckIsCNode(childNode)) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    // a
    if (parentNode->type == -1) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    const auto* impl = GetFullImpl();
    // already check in entry point.
    impl->getBasicAPI()->addChild(parentNode->uiNodeHandle, childNode->uiNodeHandle);
    impl->getBasicAPI()->markDirty(parentNode->uiNodeHandle, ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return ERROR_CODE_NO_ERROR;
}

int32_t RemoveChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    if (!CheckIsCNode(parentNode) || !CheckIsCNode(childNode)) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    // already check in entry point.
    if (parentNode->type == -1) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    const auto* impl = GetFullImpl();
    impl->getBasicAPI()->removeChild(parentNode->uiNodeHandle, childNode->uiNodeHandle);
    impl->getBasicAPI()->markDirty(parentNode->uiNodeHandle, ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return ERROR_CODE_NO_ERROR;
}

int32_t InsertChildAfter(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    if (!CheckIsCNode(parentNode) || !CheckIsCNode(childNode)) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    // already check in entry point.
    if (parentNode->type == -1) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    const auto* impl = GetFullImpl();
    impl->getBasicAPI()->insertChildAfter(
        parentNode->uiNodeHandle, childNode->uiNodeHandle, siblingNode ? siblingNode->uiNodeHandle : nullptr);
    impl->getBasicAPI()->markDirty(parentNode->uiNodeHandle, ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return ERROR_CODE_NO_ERROR;
}

int32_t InsertChildBefore(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    if (!CheckIsCNode(parentNode) || !CheckIsCNode(childNode)) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    // already check in entry point.
    if (parentNode->type == -1) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    const auto* impl = GetFullImpl();
    impl->getBasicAPI()->insertChildBefore(
        parentNode->uiNodeHandle, childNode->uiNodeHandle, siblingNode ? siblingNode->uiNodeHandle : nullptr);
    impl->getBasicAPI()->markDirty(parentNode->uiNodeHandle, ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return ERROR_CODE_NO_ERROR;
}

int32_t InsertChildAt(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, int32_t position)
{
    CHECK_NULL_RETURN(parentNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(childNode, ERROR_CODE_PARAM_INVALID);
    if (!CheckIsCNode(parentNode) || !CheckIsCNode(childNode)) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    // already check in entry point.
    if (parentNode->type == -1) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    const auto* impl = GetFullImpl();
    impl->getBasicAPI()->insertChildAt(parentNode->uiNodeHandle, childNode->uiNodeHandle, position);
    impl->getBasicAPI()->markDirty(parentNode->uiNodeHandle, ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return ERROR_CODE_NO_ERROR;
}

void SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const char* value)
{
    SetNodeAttribute(node, attribute, value);
}

int32_t SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* value)
{
    if (node == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == -1 && attribute != NODE_LAYOUT_RECT) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    return SetNodeAttribute(node, attribute, value);
}

int32_t ResetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    if (node == nullptr) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (node->type == -1 && attribute != NODE_LAYOUT_RECT) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    return ResetNodeAttribute(node, attribute);
}

const ArkUI_AttributeItem* GetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    if (node == nullptr) {
        return nullptr;
    }
    return GetNodeAttribute(node, attribute);
}

int32_t RegisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t targetId)
{
    return RegisterNodeEvent(nodePtr, eventType, targetId, nullptr);
}

int32_t RegisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t targetId, void* userData)
{
    if (nodePtr == nullptr || !CheckIsCNode(nodePtr)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto originEventType = ConvertOriginEventType(eventType, nodePtr->type);
    if (originEventType < 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "event is not supported %{public}d", eventType);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    // already check in entry point.
    if (nodePtr->type == -1 && !nodePtr->isBindNative) {
        return ERROR_CODE_NATIVE_IMPL_BUILDER_NODE_ERROR;
    }
    const auto* impl = GetFullImpl();
    auto* extraParam = new InnerEventExtraParam({ targetId, nodePtr, userData });
    if (nodePtr->extraData) {
        auto* extraData = reinterpret_cast<ExtraData*>(nodePtr->extraData);
        auto result = extraData->eventMap.try_emplace(eventType, extraParam);
        if (!result.second) {
            result.first->second->targetId = targetId;
            result.first->second->userData = userData;
            delete extraParam;
        }
    } else {
        nodePtr->extraData = new ExtraData();
        auto* extraData = reinterpret_cast<ExtraData*>(nodePtr->extraData);
        extraData->eventMap[eventType] = extraParam;
    }
    if (eventType == NODE_EVENT_ON_VISIBLE_AREA_CHANGE) {
        ArkUI_AttributeItem* radio = nodePtr->areaChangeRadio;
        radio = radio ? radio : static_cast<ArkUI_AttributeItem*>(userData);
        if (!radio) {
            return ERROR_CODE_PARAM_INVALID;
        }
        ArkUI_Int32 radioLength = radio->size;
        if (radioLength <= 0) {
            return ERROR_CODE_PARAM_INVALID;
        }
        ArkUI_Float32 radioList[radioLength];
        for (int i = 0; i < radioLength; ++i) {
            if (LessNotEqual(radio->value[i].f32, 0.0f) || GreatNotEqual(radio->value[i].f32, 1.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            }
            radioList[i] = radio->value[i].f32;
        }
        impl->getNodeModifiers()->getCommonModifier()->setOnVisibleAreaChange(
            nodePtr->uiNodeHandle, reinterpret_cast<int64_t>(nodePtr), radioList, radioLength);
    } else if (eventType == NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_EVENT) {
        auto options = nodePtr->visibleAreaEventOptions;
        if (!options) {
            return ERROR_CODE_PARAM_INVALID;
        }
        auto visibleAreaEventOptions = reinterpret_cast<ArkUI_VisibleAreaEventOptions*>(options);
        if (!visibleAreaEventOptions) {
            return ERROR_CODE_PARAM_INVALID;
        }
        ArkUI_Int32 radioLength = static_cast<ArkUI_Int32>(visibleAreaEventOptions->ratios.size());
        if (radioLength <= 0) {
            return ERROR_CODE_PARAM_INVALID;
        }
        ArkUI_Float32 radioList[radioLength];
        for (int i = 0; i < radioLength; ++i) {
            if (LessNotEqual(visibleAreaEventOptions->ratios[i], 0.0f) ||
                GreatNotEqual(visibleAreaEventOptions->ratios[i], 1.0f)) {
                return ERROR_CODE_PARAM_INVALID;
            }
            radioList[i] = visibleAreaEventOptions->ratios[i];
        }
        impl->getNodeModifiers()->getCommonModifier()->setOnVisibleAreaApproximateChange(nodePtr->uiNodeHandle,
            reinterpret_cast<int64_t>(nodePtr), radioList, radioLength,
            visibleAreaEventOptions->expectedUpdateInterval);
    } else {
        impl->getBasicAPI()->registerNodeAsyncEvent(
            nodePtr->uiNodeHandle, static_cast<ArkUIEventSubKind>(originEventType), reinterpret_cast<int64_t>(nodePtr));
    }
    return ERROR_CODE_NO_ERROR;
}

void UnregisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType)
{
    if (nodePtr == nullptr || !CheckIsCNode(nodePtr)) {
        return;
    }
    if (!nodePtr->extraData) {
        return;
    }
    if (nodePtr->type == -1 && !nodePtr->isBindNative) {
        return;
    }
    auto* extraData = reinterpret_cast<ExtraData*>(nodePtr->extraData);
    auto& eventMap = extraData->eventMap;
    auto innerEventExtraParam = eventMap.find(eventType);
    if (innerEventExtraParam == eventMap.end()) {
        return;
    }
    delete innerEventExtraParam->second;
    eventMap.erase(innerEventExtraParam);
    if (eventMap.empty()) {
        delete extraData;
        nodePtr->extraData = nullptr;
    }
    auto originEventType = ConvertOriginEventType(eventType, nodePtr->type);
    if (originEventType < 0) {
        return;
    }
    impl->getBasicAPI()->unRegisterNodeAsyncEvent(
        nodePtr->uiNodeHandle, static_cast<ArkUIEventSubKind>(originEventType));
}

bool GreatOrEqualTargetAPIVersion(OHOS::Ace::PlatformVersion platfromVersion)
{
    const auto* impl = GetFullImpl();
    CHECK_NULL_RETURN(impl, false);
    return impl->getBasicAPI()->greatOrEqualTargetAPIVersion(static_cast<int32_t>(platfromVersion));
}

void (*g_compatibleEventReceiver)(ArkUI_CompatibleNodeEvent* event) = nullptr;
void RegisterOnEvent(void (*eventReceiver)(ArkUI_CompatibleNodeEvent* event))
{
    g_compatibleEventReceiver = eventReceiver;
}

void (*g_eventReceiver)(ArkUI_NodeEvent* event) = nullptr;
void RegisterOnEvent(void (*eventReceiver)(ArkUI_NodeEvent* event))
{
    g_eventReceiver = eventReceiver;
}

void UnregisterOnEvent()
{
    g_eventReceiver = nullptr;
}

void HandleTouchEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent)
{
    uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_TOUCH;
    uiEvent.eventTypeId = C_TOUCH_EVENT_ID;
    uiEvent.inputEvent = &(innerEvent->touchEvent);
}

void HandleMouseEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent)
{
    uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_MOUSE;
    uiEvent.eventTypeId = C_MOUSE_EVENT_ID;
    uiEvent.inputEvent = &(innerEvent->mouseEvent);
}

void HandleKeyEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent)
{
    uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_KEY;
    uiEvent.eventTypeId = C_KEY_EVENT_ID;
    uiEvent.inputEvent = &(innerEvent->keyEvent);
}

void HandleFocusAxisEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent)
{
    uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_AXIS;
    uiEvent.eventTypeId = C_FOCUS_AXIS_EVENT_ID;
    uiEvent.inputEvent = &(innerEvent->focusAxisEvent);
}

void HandleAxisEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent)
{
    uiEvent.inputType = ARKUI_UIINPUTEVENT_TYPE_AXIS;
    uiEvent.eventTypeId = C_AXIS_EVENT_ID;
    uiEvent.inputEvent = &(innerEvent->axisEvent);
}

void HandleHoverEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent)
{
    uiEvent.eventTypeId = C_HOVER_EVENT_ID;
    uiEvent.inputEvent = &(innerEvent->hoverEvent);
}

void HandleClickEvent(ArkUI_UIInputEvent& uiEvent, ArkUINodeEvent* innerEvent)
{
    uiEvent.eventTypeId = C_CLICK_EVENT_ID;
    uiEvent.inputEvent = &(innerEvent->clickEvent);
}

void HandleInnerNodeEvent(ArkUINodeEvent* innerEvent)
{
    if (!innerEvent) {
        return;
    }
    auto nativeNodeEventType = GetNativeNodeEventType(innerEvent);
    if (nativeNodeEventType == -1) {
        return;
    }
    auto eventType = static_cast<ArkUI_NodeEventType>(nativeNodeEventType);
    auto* nodePtr = reinterpret_cast<ArkUI_NodeHandle>(innerEvent->extraParam);
    auto extraData = reinterpret_cast<ExtraData*>(nodePtr->extraData);
    if (!extraData) {
        return;
    }
    auto innerEventExtraParam = extraData->eventMap.find(eventType);
    if (innerEventExtraParam == extraData->eventMap.end()) {
        return;
    }
    ArkUI_NodeEvent event;
    event.node = nodePtr;
    event.eventId = innerEventExtraParam->second->targetId;
    event.userData = innerEventExtraParam->second->userData;
    if (!g_eventReceiver && !g_compatibleEventReceiver && (!(event.node) ||
        (event.node && !(event.node->eventListeners)))) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "event receiver is not register");
        return;
    }
    if ((g_eventReceiver || (event.node && event.node->eventListeners))  && ConvertEvent(innerEvent, &event)) {
        event.targetId = innerEvent->nodeId;
        ArkUI_UIInputEvent uiEvent;
        std::map<ArkUI_NodeEventType, std::function<void(ArkUI_UIInputEvent&, ArkUINodeEvent*)>> eventHandlers = {
            {NODE_TOUCH_EVENT, HandleTouchEvent},
            {NODE_ON_TOUCH_INTERCEPT, HandleTouchEvent},
            {NODE_ON_MOUSE, HandleMouseEvent},
            {NODE_ON_KEY_EVENT, HandleKeyEvent},
            {NODE_ON_KEY_PRE_IME, HandleKeyEvent},
            {NODE_ON_FOCUS_AXIS, HandleFocusAxisEvent},
            {NODE_DISPATCH_KEY_EVENT, HandleKeyEvent},
            {NODE_ON_AXIS, HandleAxisEvent},
            {NODE_ON_CLICK_EVENT, HandleClickEvent},
            {NODE_ON_HOVER_EVENT, HandleHoverEvent},
            {NODE_ON_HOVER_MOVE, HandleTouchEvent},
        };

        auto it = eventHandlers.find(eventType);
        if (it != eventHandlers.end()) {
            it->second(uiEvent, innerEvent);
            uiEvent.apiVersion = innerEvent->apiVersion;
            event.origin = &uiEvent;
        } else {
            event.origin = innerEvent;
        }
        HandleNodeEvent(&event);
    }
    if (g_compatibleEventReceiver) {
        ArkUI_CompatibleNodeEvent event;
        event.node = nodePtr;
        event.eventId = innerEventExtraParam->second->targetId;
        if (ConvertEvent(innerEvent, &event)) {
            g_compatibleEventReceiver(&event);
            ConvertEventResult(&event, innerEvent);
        }
    }
}

int32_t GetNativeNodeEventType(ArkUINodeEvent* innerEvent)
{
    int32_t invalidType = -1;
    auto* nodePtr = reinterpret_cast<ArkUI_NodeHandle>(innerEvent->extraParam);
    if (!IsValidArkUINode(nodePtr)) {
        return invalidType;
    }
    if (!nodePtr->extraData) {
        return invalidType;
    }
    auto extraData = reinterpret_cast<ExtraData*>(nodePtr->extraData);
    ArkUIEventSubKind subKind = static_cast<ArkUIEventSubKind>(-1);
    switch (innerEvent->kind) {
        case COMPONENT_ASYNC_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->componentAsyncEvent.subKind);
            break;
        case TEXT_INPUT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->textInputEvent.subKind);
            break;
        case TOUCH_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->touchEvent.subKind);
            break;
        case MOUSE_INPUT_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->mouseEvent.subKind);
            break;
        case MIXED_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->mixedEvent.subKind);
            break;
        case DRAG_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->dragEvent.subKind);
            break;
        case KEY_INPUT_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->keyEvent.subKind);
            break;
        case FOCUS_AXIS_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->focusAxisEvent.subKind);
            break;
        case TEXT_INPUT_CHANGE:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->textChangeEvent.subKind);
            break;
        case AXIS_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->axisEvent.subKind);
            break;
        case CLICK_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->clickEvent.subKind);
            break;
        case HOVER_EVENT:
            subKind = static_cast<ArkUIEventSubKind>(innerEvent->hoverEvent.subKind);
            break;
        default:
            break; /* Empty */
    }
    ArkUI_NodeEventType eventType = static_cast<ArkUI_NodeEventType>(ConvertToNodeEventType(subKind));
    auto innerEventExtraParam = extraData->eventMap.find(eventType);
    if (innerEventExtraParam == extraData->eventMap.end()) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "the event of %{public}d is not register", eventType);
        return invalidType;
    }
    return static_cast<int32_t>(eventType);
}

void HandleNodeEvent(ArkUI_NodeEvent* event)
{
    if (!event) {
        return;
    }
    if (event->node && event->node->eventListeners) {
        auto eventListenersSet = reinterpret_cast<std::set<void (*)(ArkUI_NodeEvent*)>*>(event->node->eventListeners);
        TriggerNodeEvent(event, eventListenersSet);
    }
    if (g_eventReceiver) {
        g_eventReceiver(event);
    }
}

void TriggerNodeEvent(ArkUI_NodeEvent* event, std::set<void (*)(ArkUI_NodeEvent*)>* eventListenersSet)
{
    if (!eventListenersSet) {
        return;
    }
    if (eventListenersSet->size() == 1) {
        auto eventListener = eventListenersSet->begin();
        (*eventListener)(event);
    } else if (eventListenersSet->size() > 1) {
        for (const auto& eventListener : *eventListenersSet) {
            (*eventListener)(event);
            if (!IsValidArkUINode(event->node)) {
                break;
            }
        }
    }
}

int32_t CheckEvent(ArkUI_NodeEvent* event)
{
    return 0;
}

int32_t SetUserData(ArkUI_NodeHandle node, void* userData)
{
    if (!node || !CheckIsCNode(node)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!userData) {
        return ERROR_CODE_PARAM_INVALID;
    }
    node->userData = userData;
    return ERROR_CODE_NO_ERROR;
}

void* GetUserData(ArkUI_NodeHandle node)
{
    return node->userData;
}

int32_t SetLengthMetricUnit(ArkUI_NodeHandle nodePtr, ArkUI_LengthMetricUnit unit)
{
    if (!nodePtr || !CheckIsCNode(nodePtr)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!InRegion(static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_DEFAULT),
        static_cast<int32_t>(ARKUI_LENGTH_METRIC_UNIT_FP), static_cast<int32_t>(unit))) {
        return ERROR_CODE_PARAM_INVALID;
    }
    nodePtr->lengthMetricUnit = unit;
    return ERROR_CODE_NO_ERROR;
}

void ApplyModifierFinish(ArkUI_NodeHandle nodePtr)
{
    // already check in entry point.
    if (!nodePtr) {
        return;
    }
    const auto* impl = GetFullImpl();
    impl->getBasicAPI()->applyModifierFinish(nodePtr->uiNodeHandle);
}

void MarkDirty(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag)
{
    // spanNode inherited from UINode
    if (!nodePtr || !CheckIsCNode(nodePtr)) {
        return;
    }
    ArkUIDirtyFlag flag = ARKUI_DIRTY_FLAG_MEASURE;
    switch (dirtyFlag) {
        case NODE_NEED_MEASURE: {
            flag = ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT;
            break;
        }
        case NODE_NEED_LAYOUT: {
            flag = ARKUI_DIRTY_FLAG_LAYOUT;
            break;
        }
        case NODE_NEED_RENDER: {
            flag = ARKUI_DIRTY_FLAG_RENDER;
            break;
        }
        default: {
            flag = ARKUI_DIRTY_FLAG_MEASURE;
        }
    }
    // already check in entry point.
    const auto* impl = GetFullImpl();
    impl->getBasicAPI()->markDirty(nodePtr->uiNodeHandle, flag);
}

int32_t AddNodeEventReceiver(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeEvent* event))
{
    if (!nodePtr || !eventReceiver || !CheckIsCNode(nodePtr)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    if (!nodePtr->eventListeners) {
        nodePtr->eventListeners = new std::set<void (*)(ArkUI_NodeEvent*)>();
    }
    auto eventListenersSet = reinterpret_cast<std::set<void (*)(ArkUI_NodeEvent*)>*>(nodePtr->eventListeners);
    if (!eventListenersSet) {
        return ERROR_CODE_PARAM_INVALID;
    }
    eventListenersSet->emplace(eventReceiver);
    return ERROR_CODE_NO_ERROR;
}

int32_t RemoveNodeEventReceiver(ArkUI_NodeHandle nodePtr, void (*eventReceiver)(ArkUI_NodeEvent* event))
{
    if (!nodePtr || !eventReceiver || !nodePtr->eventListeners || !CheckIsCNode(nodePtr)) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto eventListenersSet = reinterpret_cast<std::set<void (*)(ArkUI_NodeEvent*)>*>(nodePtr->eventListeners);
    if (!eventListenersSet) {
        return ERROR_CODE_PARAM_INVALID;
    }
    eventListenersSet->erase(eventReceiver);
    if (eventListenersSet->empty()) {
        delete eventListenersSet;
        nodePtr->eventListeners = nullptr;
    }
    return ERROR_CODE_NO_ERROR;
}

void* GetParseJsMedia()
{
    void* module = FindModule();
    if (!module) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get module");
        return nullptr;
    }
    void (*parseJsMedia)(void* value, void* resource) = nullptr;
    parseJsMedia = reinterpret_cast<void (*)(void*, void*)>(
        FindFunction(module, "OHOS_ACE_ParseJsMedia"));
    if (!parseJsMedia) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Cannot find OHOS_ACE_ParseJsMedia");
        return nullptr;
    }
    return reinterpret_cast<void*>(parseJsMedia);
}

bool CheckIsCNode(ArkUI_NodeHandle node)
{
    if (node->cNode || node->buildNode) {
        return true;
    }
    return false;
}

bool CheckIsCNodeOrCrossLanguage(ArkUI_NodeHandle node)
{
    if (node->cNode || node->buildNode) {
        return true;
    }
    const auto* impl = GetFullImpl();
    CHECK_NULL_RETURN(impl, false);
    return impl->getNodeModifiers()->getFrameNodeModifier()->getCrossLanguageOptions(node->uiNodeHandle);
}

ArkUI_NodeHandle GetArkUINode(ArkUINodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    void* attachNode = impl->getExtendedAPI()->getAttachNodePtr(node);
    if (attachNode) {
        return reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    ArkUI_Node* arkUINode = new ArkUI_Node({ -1, node, false });
    arkUINode->type = GetNodeTypeByTag(arkUINode);
    impl->getExtendedAPI()->setAttachNodePtr((arkUINode)->uiNodeHandle, reinterpret_cast<void*>(arkUINode));
    return reinterpret_cast<ArkUI_NodeHandle>(arkUINode);
}

int32_t GetNodeTypeByTag(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return -1;
    }

    static const std::unordered_map<std::string, ArkUI_NodeType> nodeTypeMap = {
        { OHOS::Ace::V2::TEXT_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TEXT },
        { OHOS::Ace::V2::SPAN_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_SPAN },
        { OHOS::Ace::V2::IMAGE_SPAN_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_IMAGE_SPAN },
        { OHOS::Ace::V2::IMAGE_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_IMAGE },
        { OHOS::Ace::V2::TOGGLE_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TOGGLE },
        { OHOS::Ace::V2::LOADING_PROGRESS_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_LOADING_PROGRESS },
        { OHOS::Ace::V2::TEXTINPUT_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TEXT_INPUT },
        { OHOS::Ace::V2::TEXTAREA_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TEXT_AREA },
        { OHOS::Ace::V2::BUTTON_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_BUTTON },
        { OHOS::Ace::V2::PROGRESS_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_PROGRESS },
        { OHOS::Ace::V2::CHECK_BOX_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_CHECKBOX },
        { OHOS::Ace::V2::XCOMPONENT_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_XCOMPONENT },
        { OHOS::Ace::V2::DATE_PICKER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_DATE_PICKER },
        { OHOS::Ace::V2::TIME_PICKER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TIME_PICKER },
        { OHOS::Ace::V2::TEXT_PICKER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TEXT_PICKER },
        { OHOS::Ace::V2::CALENDAR_PICKER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_CALENDAR_PICKER },
        { OHOS::Ace::V2::SLIDER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_SLIDER },
        { OHOS::Ace::V2::RADIO_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_RADIO },
        { OHOS::Ace::V2::IMAGE_ANIMATOR_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_IMAGE_ANIMATOR },
        { OHOS::Ace::V2::STACK_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_STACK },
        { OHOS::Ace::V2::SWIPER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_SWIPER },
        { OHOS::Ace::V2::SCROLL_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_SCROLL },
        { OHOS::Ace::V2::LIST_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_LIST },
        { OHOS::Ace::V2::LIST_ITEM_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_LIST_ITEM },
        { OHOS::Ace::V2::LIST_ITEM_GROUP_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_LIST_ITEM_GROUP },
        { OHOS::Ace::V2::COLUMN_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_COLUMN },
        { OHOS::Ace::V2::ROW_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_ROW },
        { OHOS::Ace::V2::FLEX_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_FLEX },
        { OHOS::Ace::V2::REFRESH_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_REFRESH },
        { OHOS::Ace::V2::WATERFLOW_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_WATER_FLOW },
        { OHOS::Ace::V2::FLOW_ITEM_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_FLOW_ITEM },
        { OHOS::Ace::V2::RELATIVE_CONTAINER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_RELATIVE_CONTAINER },
        { OHOS::Ace::V2::GRID_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_GRID },
        { OHOS::Ace::V2::GRID_ITEM_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_GRID_ITEM },
        { OHOS::Ace::V2::CUSTOM_SPAN_NODE_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_CUSTOM_SPAN },
        { OHOS::Ace::V2::EMBEDDED_COMPONENT_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_EMBEDDED_COMPONENT },
    };

    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto value = impl->getNodeModifiers()->getFrameNodeModifier()->getNodeType(node->uiNodeHandle);
    auto iter = nodeTypeMap.find(value);
    if (iter != nodeTypeMap.end()) {
        return iter->second;
    }
    return -1;
}

void RegisterBindNativeNode(ArkUI_NodeHandle node)
{
    CHECK_NULL_VOID(node);
    g_nodeSet.emplace(node);
}
} // namespace OHOS::Ace::NodeModel

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_NodeContent_AddNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    return impl->getNodeModifiers()->getNodeContentModifier()->addChild(
        reinterpret_cast<ArkUINodeContentHandle>(content), node->uiNodeHandle);
}

int32_t OH_ArkUI_NodeContent_InsertNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node, int32_t position)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    return impl->getNodeModifiers()->getNodeContentModifier()->insertChild(
        reinterpret_cast<ArkUINodeContentHandle>(content), node->uiNodeHandle, position);
}

int32_t OH_ArkUI_NodeContent_RemoveNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    return impl->getNodeModifiers()->getNodeContentModifier()->removeChild(
        reinterpret_cast<ArkUINodeContentHandle>(content), node->uiNodeHandle);
}

int32_t OH_ArkUI_NodeContent_RegisterCallback(ArkUI_NodeContentHandle content, ArkUI_NodeContentCallback callback)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    auto innerCallback = reinterpret_cast<void (*)(ArkUINodeContentEvent* event)>(callback);
    return impl->getNodeModifiers()->getNodeContentModifier()->registerEvent(
        reinterpret_cast<ArkUINodeContentHandle>(content), nullptr, innerCallback);
}

ArkUI_NodeContentEventType OH_ArkUI_NodeContentEvent_GetEventType(ArkUI_NodeContentEvent* event)
{
    CHECK_NULL_RETURN(event, static_cast<ArkUI_NodeContentEventType>(-1));
    auto* innerEvent = reinterpret_cast<ArkUINodeContentEvent*>(event);
    return static_cast<ArkUI_NodeContentEventType>(innerEvent->type);
}

ArkUI_NodeContentHandle OH_ArkUI_NodeContentEvent_GetNodeContentHandle(ArkUI_NodeContentEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    auto* innerEvent = reinterpret_cast<ArkUINodeContentEvent*>(event);
    return reinterpret_cast<ArkUI_NodeContentHandle>(innerEvent->nodeContent);
}

int32_t OH_ArkUI_NodeContent_SetUserData(ArkUI_NodeContentHandle content, void* userData)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return impl->getNodeModifiers()->getNodeContentModifier()->setUserData(
        reinterpret_cast<ArkUINodeContentHandle>(content), userData);
}

void* OH_ArkUI_NodeContent_GetUserData(ArkUI_NodeContentHandle content)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    return impl->getNodeModifiers()->getNodeContentModifier()->getUserData(
        reinterpret_cast<ArkUINodeContentHandle>(content));
}

#ifdef __cplusplus
};
#endif
