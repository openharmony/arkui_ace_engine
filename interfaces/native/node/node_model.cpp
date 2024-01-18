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

#include "basic_node.h"
#include "event_converter.h"
#include "style_modifier.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/native/node/node_api.h"

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
        typedef ArkUIAnyNodeAPI* (*GetAPI_t)(int);
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
        ARKUI_REFRESH, ARKUI_XCOMPONENT };
    auto* impl = GetFullImpl();
    if (!impl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get node impl");
        return nullptr;
    }
    if (type > sizeof(nodes) / sizeof(ArkUINodeType)) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node type: %{public}d NOT IMPLEMENT", type);
        return nullptr;
    }
    auto* uiNode = impl->getBasicAPI()->createNode(nodes[type - 1], -1, 0);
    if (!uiNode) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "node type: %{public}d can not find in full impl", type);
        return nullptr;
    }
    return new ArkUI_Node({ type, uiNode });
}

void DisposeNode(ArkUI_NodeHandle nativePtr)
{
    CHECK_NULL_VOID(nativePtr);
    auto* impl = GetFullImpl();
    if (!impl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get node impl");
        return;
    }
    if (nativePtr) {
        impl->getBasicAPI()->disposeNode(nativePtr->uiNodeHandle);
        delete nativePtr;
    }
}

void AddChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* impl = GetFullImpl();
    if (!impl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get node impl");
        return;
    }
    impl->getBasicAPI()->addChild(parentNode->uiNodeHandle, childNode->uiNodeHandle);
}

void RemoveChild(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* impl = GetFullImpl();
    if (!impl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get node impl");
        return;
    }
    impl->getBasicAPI()->removeChild(parentNode->uiNodeHandle, childNode->uiNodeHandle);
}

void InsertChildAfter(ArkUI_NodeHandle parentNode, ArkUI_NodeHandle childNode, ArkUI_NodeHandle siblingNode)
{
    CHECK_NULL_VOID(parentNode);
    CHECK_NULL_VOID(childNode);
    auto* impl = GetFullImpl();
    if (!impl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get node impl");
        return;
    }
    impl->getBasicAPI()->insertChildAfter(
        parentNode->uiNodeHandle, childNode->uiNodeHandle, siblingNode ? siblingNode->uiNodeHandle : nullptr);
}

const char* GetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    return GetNodeAttribute(node, attribute);
}

void SetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const char* value)
{
    SetNodeAttribute(node, attribute, value);
}

void ResetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    ResetNodeAttribute(node, attribute);
}

void RegisterNodeEvent(ArkUI_NodeHandle nodePtr, ArkUI_NodeEventType eventType, int32_t eventId)
{
    auto originEventType = ConvertOriginEventType(eventType);
    if (originEventType < 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "event is not supported %{public}d", eventType);
        return;
    }
    auto* impl = GetFullImpl();
    if (!impl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get node impl");
        return;
    }
    impl->getBasicAPI()->registerNodeAsyncEvent(
        nodePtr->uiNodeHandle, static_cast<ArkUIAsyncEventKind>(originEventType), eventId, nodePtr);
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
        auto* impl = GetFullImpl();
        if (!impl) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get event register impl");
            return;
        }
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
    auto* impl = GetFullImpl();
    if (!impl) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to get node impl");
        return;
    }
    impl->getBasicAPI()->applyModifierFinish(nodePtr->uiNodeHandle);
}

void MarkDirty(ArkUI_NodeHandle nodePtr, ArkUI_NodeDirtyFlag dirtyFlag)
{
    // spanNode inherited from UINode
    auto* uiNode = reinterpret_cast<NG::UINode*>(nodePtr->uiNodeHandle);
    CHECK_NULL_VOID(uiNode);
    NG::PropertyChangeFlag flag;
    switch (dirtyFlag) {
        case NODE_NEED_LAYOUT: {
            flag = NG::PROPERTY_UPDATE_LAYOUT;
        }
        case NODE_NEED_RENDER: {
            flag = NG::PROPERTY_UPDATE_RENDER;
        }
        default: {
            flag = NG::PROPERTY_UPDATE_NORMAL;
        }
    }
    uiNode->MarkDirtyNode(flag);
}

} // namespace OHOS::Ace::NodeModel