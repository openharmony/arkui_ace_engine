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

#include <cstdint>

#include "event_converter.h"
#include "native_node.h"
#include "native_type.h"
#include "style_modifier.h"

#include "base/error/error_code.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/arkoala/arkoala_api.h"

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

ArkUIFullNodeAPI* GetAnyFullNodeImpl(int version)
{
    if (!impl) {
        typedef ArkUIAnyAPI* (*GetAPI_t)(int);
        GetAPI_t getAPI = nullptr;
        void* module = FindModule();
        if (module == nullptr) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get module");
            return nullptr;
        }
        // Note, that RTLD_DEFAULT is ((void *) 0).
        getAPI = reinterpret_cast<GetAPI_t>(FindFunction(module, "GetArkUIAnyFullNodeAPI"));
        if (!getAPI) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Cannot find GetArkUIAnyFullNodeAPI()");
            return nullptr;
        }

        impl = reinterpret_cast<ArkUIFullNodeAPI*>((*getAPI)(version));
        if (!impl) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "getAPI() returned null");
            return nullptr;
        }

        if (impl->version != version) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE,
                "API version mismatch: expected %{public}d, but get the version %{public}d", version, impl->version);
            return nullptr;
        }
    }
    return impl;
}
} // namespace

ArkUIFullNodeAPI* GetFullImpl()
{
    return GetAnyFullNodeImpl(ARKUI_NODE_API_VERSION);
}

ArkUI_NodeHandle CreateNode(ArkUI_NodeType type)
{
    static const ArkUINodeType nodes[] = { ARKUI_TEXT, ARKUI_SPAN, ARKUI_IMAGE_SPAN, ARKUI_IMAGE, ARKUI_TOGGLE,
        ARKUI_LOADING_PROGRESS, ARKUI_TEXT_INPUT, ARKUI_STACK, ARKUI_SCROLL, ARKUI_LIST, ARKUI_SWIPER, ARKUI_TEXTAREA,
        ARKUI_BUTTON, ARKUI_PROGRESS, ARKUI_CHECKBOX, ARKUI_COLUMN, ARKUI_ROW, ARKUI_FLEX, ARKUI_LIST_ITEM,
        ARKUI_REFRESH, ARKUI_XCOMPONENT, ARKUI_LIST_ITEM_GROUP };
    // already check in entry point.
    auto* impl = GetFullImpl();
    if (type > sizeof(nodes) / sizeof(ArkUINodeType)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node type: %{public}d NOT IMPLEMENT", type);
        return nullptr;
    }

    ArkUI_Int32 id = -1;
    if (type == ARKUI_NODE_LOADING_PROGRESS) {
        id = ARKUI_AUTO_GENERATE_NODE_ID;
    }
    auto* uiNode = impl->getBasicAPI()->createNode(nodes[type - 1], id, 0);
    if (!uiNode) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node type: %{public}d can not find in full impl", type);
        return nullptr;
    }
    impl->getBasicAPI()->markDirty(uiNode, ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF);
    return new ArkUI_Node({ type, uiNode });
}

void DisposeNode(ArkUI_NodeHandle nativePtr)
{
    CHECK_NULL_VOID(nativePtr);
    // already check in entry point.
    auto* impl = GetFullImpl();
    impl->getBasicAPI()->disposeNode(nativePtr->uiNodeHandle);
    delete nativePtr;
}

void AddChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    // already check in entry point.
    auto* impl = GetFullImpl();
    impl->getBasicAPI()->addChild(parentNode->uiNodeHandle, childNode->uiNodeHandle);
    impl->getBasicAPI()->markDirty(parentNode->uiNodeHandle, ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
}

void RemoveChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    // already check in entry point.
    auto* impl = GetFullImpl();
    impl->getBasicAPI()->removeChild(parentNode->uiNodeHandle, childNode->uiNodeHandle);
    impl->getBasicAPI()->markDirty(parentNode->uiNodeHandle, ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
}

void InsertChildAfter(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    // already check in entry point.
    auto* impl = GetFullImpl();
    impl->getBasicAPI()->insertChildAfter(
        parentNode->uiNodeHandle, childNode->uiNodeHandle, siblingNode ? siblingNode->uiNodeHandle : nullptr);
    impl->getBasicAPI()->markDirty(parentNode->uiNodeHandle, ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
}

void SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const char* value)
{
    SetNodeAttribute(node, attribute, value);
}

int32_t SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* value)
{
    return SetNodeAttribute(node, attribute, value);
}

void ResetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    ResetNodeAttribute(node, attribute);
}

const ArkUI_AttributeItem* GetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    return GetNodeAttribute(node, attribute);
}

int32_t RegisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t eventId)
{
    auto originEventType = ConvertOriginEventType(eventType);
    if (originEventType < 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "event is not supported %{public}d", eventType);
        return ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    // already check in entry point.
    auto* impl = GetFullImpl();
    impl->getBasicAPI()->registerNodeAsyncEvent(
        nodePtr->uiNodeHandle, static_cast<ArkUIAsyncEventKind>(originEventType), eventId, nodePtr);
    return ERROR_CODE_NO_ERROR;
}

void UnregisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType)
{
    // TODO.
}

void (*g_eventReceiver)(ArkUI_NodeEvent* event) = nullptr;
void RegisterOnEvent(void (*eventReceiver)(ArkUI_NodeEvent* event))
{
    g_eventReceiver = eventReceiver;
    if (g_eventReceiver) {
        // already check in entry point.
        auto* impl = GetFullImpl();
        auto innerReceiver = [](ArkUINodeEvent* origin) {
            if (g_eventReceiver) {
                auto event = reinterpret_cast<ArkUI_NodeEvent*>(origin);
                event->node = reinterpret_cast<ArkUI_NodeHandle>(origin->extraParam);
                event->kind = ConvertToNodeEventType(static_cast<ArkUIAsyncEventKind>(origin->kind));
                event->stringEvent.pStr = origin->stringAsyncEvent.pStr;
                g_eventReceiver(event);
            }
        };
        impl->getBasicAPI()->registerNodeAsyncEventReceiver(innerReceiver);
    }
}

void UnregisterOnEvent()
{
    g_eventReceiver = nullptr;
}

int32_t CheckEvent(ArkUI_NodeEvent* event)
{
    // TODO.
    return 0;
}

void ApplyModifierFinish(ArkUI_NodeHandle nodePtr)
{
    // already check in entry point.
    auto* impl = GetFullImpl();
    impl->getBasicAPI()->applyModifierFinish(nodePtr->uiNodeHandle);
}

void MarkDirty(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag)
{
    // spanNode inherited from UINode
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
    auto* impl = GetFullImpl();
    impl->getBasicAPI()->markDirty(nodePtr->uiNodeHandle, flag);
}

} // namespace OHOS::Ace::NodeModel