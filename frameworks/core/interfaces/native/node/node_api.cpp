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

#include "core/interfaces/native/node/node_api.h"

#include <array>
#include <deque>

#include "base/log/log_wrapper.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_scroll_modifier.h"
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/node/node_text_area_modifier.h"
#include "core/interfaces/native/node/node_toggle_modifier.h"
#include "core/interfaces/native/node/view_model.h"
#include "core/interfaces/native/node/node_common_modifier.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace::NG {

namespace NodeEvent {
std::deque<ArkUINodeEvent> g_eventQueue;
int CheckEvent(ArkUINodeEvent* event)
{
    if (!g_eventQueue.empty()) {
        *event = g_eventQueue.front();
        g_eventQueue.pop_front();
        return 1;
    }
    return 0;
}

void (*g_fliter)(ArkUINodeEvent* event) = nullptr;
void SendArkUIAsyncEvent(ArkUINodeEvent* event)
{
    if (g_fliter) {
        g_fliter(event);
    } else {
        g_eventQueue.push_back(*event);
    }
}
} // namespace NodeEvent

namespace {

ArkUINodeHandle CreateNode(ArkUINodeType type, int peerId, ArkUI_Int32 /*flags*/)
{
    return reinterpret_cast<ArkUINodeHandle>(ViewModel::CreateNode(type, peerId));
}

void DisposeNode(ArkUINodeHandle node)
{
    ViewModel::DisposeNode(node);
}

void AddChild(ArkUINodeHandle parent, ArkUINodeHandle child)
{
    ViewModel::AddChild(parent, child);
}

void RemoveChild(ArkUINodeHandle parent, ArkUINodeHandle child)
{
    ViewModel::RemoveChild(parent, child);
}

void InsertChildAfter(ArkUINodeHandle parent, ArkUINodeHandle child, ArkUINodeHandle sibling)
{
    ViewModel::InsertChildAfter(parent, child, sibling);
}

typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, ArkUI_Int32 eventId, void* extraParam);

/**
 * IMPORTANT!!!
 * the order of declaring the handler must be same as the ArkUIAsyncEventKind did
 */
/* clang-format off */
const ComponentAsyncEventHandler commonNodeAsyncEventHandlers[] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    NodeModifier::SetOnBlur,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    NodeModifier::SetOnFocus,
};

const ComponentAsyncEventHandler scrollNodeAsyncEventHandlers[] = {
    NodeModifier::SetOnScroll,
    NodeModifier::SetOnScrollFrameBegin,
    NodeModifier::SetOnScrollStart,
    NodeModifier::SetOnScrollStop,
    NodeModifier::SetOnScrollEdge,
};

const ComponentAsyncEventHandler textInputNodeAsyncEventHandlers[] = {
    nullptr,
    NodeModifier::SetTextInputOnSubmit,
    NodeModifier::SetOnTextInputChange,
};

const ComponentAsyncEventHandler textAreaNodeAsyncEventHandlers[] = {
    nullptr,
    nullptr,
    NodeModifier::SetOnTextAreaChange,
};

const ComponentAsyncEventHandler refreshNodeAsyncEventHandlers[] = {
    NodeModifier::SetRefreshOnStateChange,
    NodeModifier::SetOnRefreshing,
};

const ComponentAsyncEventHandler TOGGLE_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnToggleChange,
};

/* clang-format on */
void NotifyComponentAsyncEvent(ArkUINodeHandle node, ArkUIAsyncEventKind kind, ArkUI_Int32 eventId, void* extraParam)
{
    unsigned int subClassType = kind / ARKUI_MAX_EVENT_NUM;
    unsigned int subKind = kind % ARKUI_MAX_EVENT_NUM;
    ComponentAsyncEventHandler eventHandle = nullptr;
    switch (subClassType) {
        case 0: {
            // common event type.
            if (subKind >= sizeof(commonNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = commonNodeAsyncEventHandlers[subKind];
            break;
        }
        case ARKUI_SCROLL: {
            // scroll event type.
            if (subKind >= sizeof(scrollNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = scrollNodeAsyncEventHandlers[subKind];
            break;
        }
        case ARKUI_TEXT_INPUT: {
            // textinput event type.
            if (subKind >= sizeof(textInputNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = textInputNodeAsyncEventHandlers[subKind];
            break;
        }
        case ARKUI_TEXTAREA: {
            // textarea event type.
            if (subKind >= sizeof(textAreaNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = textAreaNodeAsyncEventHandlers[subKind];
            break;
        }
        case ARKUI_REFRESH: {
            // refresh event type.
            if (subKind >= sizeof(refreshNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = refreshNodeAsyncEventHandlers[subKind];
            break;
        }
        case ARKUI_TOGGLE: {
            // toggle event type.
            if (subKind >= sizeof(TOGGLE_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TOGGLE_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        default: {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        }
    }
    if (eventHandle) {
        eventHandle(node, eventId, extraParam);
    } else {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d EMPTY IMPLEMENT", kind);
    }
}

void NotifyResetComponentAsyncEvent(ArkUINodeHandle node, ArkUIAsyncEventKind subKind)
{
    // TODO
}

void RegisterNodeAsyncEventReceiver(void (*eventReceiver)(ArkUINodeEvent* event))
{
    NodeEvent::g_fliter = eventReceiver;
}

void ApplyModifierFinish(ArkUINodeHandle nodePtr)
{
    auto* uiNode = reinterpret_cast<UINode*>(nodePtr);
    auto* frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    if (frameNode) {
        frameNode->MarkModifyDone();
    }
}

void MarkDirty(ArkUINodeHandle nodePtr, ArkUI_Uint32 flag)
{
    auto* uiNode = reinterpret_cast<UINode*>(nodePtr);
    if (uiNode) {
        uiNode->MarkDirtyNode(flag);
    }
}

static ArkUIAPICallbackMethod* callbacks = nullptr;

static void SetCallbackMethod(ArkUIAPICallbackMethod* method)
{
    callbacks = method;
}

const ArkUIBasicAPI* GetBasicAPI()
{
    /* clang-format off */
    static const ArkUIBasicAPI basicImpl = {
        CreateNode,
        DisposeNode,
        nullptr,
        nullptr,

        AddChild,
        RemoveChild,
        InsertChildAfter,
        nullptr,
        nullptr,
        nullptr,

        NotifyComponentAsyncEvent,
        NotifyResetComponentAsyncEvent,
        RegisterNodeAsyncEventReceiver,
        nullptr,

        nullptr,

        ApplyModifierFinish,
        MarkDirty,
    };
    /* clang-format on */

    return &basicImpl;
}

/* clang-format off */
ArkUIExtendedNodeAPI impl_extended = {
    ARKUI_EXTENDED_API_VERSION,

    nullptr,
    nullptr,

    SetCallbackMethod,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};
/* clang-format on */

void CanvasDrawRect(ArkUICanvasHandle canvas,
    ArkUI_Float64 left, ArkUI_Float64 top, ArkUI_Float64 right, ArkUI_Float64 bottom, ArkUIPaintHandle paint) {
        TAG_LOGI(AceLogTag::ACE_NATIVE_NODE,
            "DrawRect canvas=%{public}p [%{public}f, %{public}f, %{public}f, %{public}f]\n",
            canvas, left, top, right, bottom);
    }

const ArkUIGraphicsCanvas* GetCanvasAPI()
{
    static const ArkUIGraphicsCanvas modifier = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        CanvasDrawRect,
        nullptr
    };
    return &modifier;
}

struct DummyPaint {
    ArkUI_Int32 color;
};

ArkUIPaintHandle PaintMake()
{
    return reinterpret_cast<ArkUIPaintHandle>(new DummyPaint());
}

void PaintFinalize(ArkUIPaintHandle paintPtr)
{
    auto* paint = reinterpret_cast<DummyPaint*>(paintPtr);
    delete paint;
}

const ArkUIGraphicsPaint* GetPaintAPI()
{
    static const ArkUIGraphicsPaint modifier = {
        PaintMake,
        PaintFinalize,
        nullptr,
        nullptr,
        nullptr,
        nullptr
    };
    return &modifier;
}

const ArkUIGraphicsFont* GetFontAPI()
{
    static const ArkUIGraphicsFont modifier = {
        nullptr,
    };
    return &modifier;
}

const ArkUIGraphicsAPI* GetGraphicsAPI()
{
    static const ArkUIGraphicsAPI api = {
        ARKUI_NODE_GRAPHICS_API_VERSION,
        SetCallbackMethod,
        GetCanvasAPI,
        GetPaintAPI,
        GetFontAPI
    };
    return &api;
}

const ArkUIAnimation* GetAnimationAPI()
{
    static const ArkUIAnimation modifier = {
        nullptr,
        nullptr,
        nullptr,
    };
    return &modifier;
}

const ArkUINavigation* GetNavigationAPI()
{
    static const ArkUINavigation modifier = {
        nullptr,
        nullptr,
    };
    return &modifier;
}


/* clang-format off */
ArkUIFullNodeAPI impl_full = {
    ARKUI_NODE_API_VERSION,
    SetCallbackMethod,      // CallbackMethod
    GetBasicAPI,            // BasicAPI
    GetArkUINodeModifiers,  // NodeModifiers
    GetAnimationAPI,        // Animation
    GetNavigationAPI,       // Navigation
    GetGraphicsAPI,         // Graphics
};
/* clang-format on */
} // namespace

} // namespace OHOS::Ace::NG


extern "C" {

ACE_FORCE_EXPORT ArkUIAnyAPI* GetArkUIAnyFullNodeAPI(int version)
{
    switch (version) {
        case ARKUI_NODE_API_VERSION:
            return reinterpret_cast<ArkUIAnyAPI*>(&OHOS::Ace::NG::impl_full);
        default: {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                "Requested version %{public}d is not supported, we're version %{public}d", version,
                ARKUI_NODE_API_VERSION);
            return nullptr;
        }
    }
}

const ArkUIFullNodeAPI* GetArkUIFullNodeAPI()
{
    return &OHOS::Ace::NG::impl_full;
}

void SendArkUIAsyncEvent(ArkUINodeEvent* event)
{
    OHOS::Ace::NG::NodeEvent::SendArkUIAsyncEvent(event);
}

ACE_FORCE_EXPORT const ArkUIAnyAPI* GetArkUIAPI(ArkUIAPIVariantKind kind, ArkUI_Int32 version)
{
    switch (kind) {
        case ArkUIAPIVariantKind::BASIC: {
            switch (version) {
                case ARKUI_BASIC_API_VERSION:
                    return reinterpret_cast<const ArkUIAnyAPI*>(OHOS::Ace::NG::GetBasicAPI());
                default: {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                        "Requested basic version %{public}d is not supported, we're version %{public}d\n",
                        version, ARKUI_BASIC_API_VERSION);

                    return nullptr;
                }
            }
        }
        case ArkUIAPIVariantKind::FULL: {
            switch (version) {
                case ARKUI_FULL_API_VERSION:
                    return reinterpret_cast<const ArkUIAnyAPI*>(&OHOS::Ace::NG::impl_full);
                default: {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                        "Requested full version %{public}d is not supported, we're version %{public}d\n",
                        version, ARKUI_FULL_API_VERSION);

                    return nullptr;
                }
            }
        }
        case ArkUIAPIVariantKind::GRAPHICS: {
            switch (version) {
                case ARKUI_NODE_GRAPHICS_API_VERSION:
                    return reinterpret_cast<const ArkUIAnyAPI*>(OHOS::Ace::NG::GetGraphicsAPI());
                default: {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                        "Requested graphics version %{public}d is not supported, we're version %{public}d\n",
                        version, ARKUI_NODE_GRAPHICS_API_VERSION);

                    return nullptr;
                }
            }
        }
        case ArkUIAPIVariantKind::EXTENDED: {
            switch (version) {
                case ARKUI_EXTENDED_API_VERSION:
                    return reinterpret_cast<const ArkUIAnyAPI*>(&OHOS::Ace::NG::impl_extended);
                default: {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                        "Requested extended version %{public}d is not supported, we're version %{public}d\n",
                        version, ARKUI_EXTENDED_API_VERSION);

                    return nullptr;
                }
            }
        }
        default: {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                "API kind %{public}d is not supported\n",
                static_cast<int>(kind));

            return nullptr;
        }
    }
}

__attribute__((constructor)) static void provideEntryPoint(void)
{
#ifdef WINDOWS_PLATFORM
    // mingw has no setenv :(.
    static char entryPointString[64];
    (void)snprintf(entryPointString, sizeof entryPointString, "__LIBACE_ENTRY_POINT=%llx",
        static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(&GetArkUIAPI)));
    putenv(entryPointString);
#else
    char entryPointString[64];
    (void)snprintf(entryPointString, sizeof entryPointString, "%llx",
        static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(&GetArkUIAPI)));
    setenv("__LIBACE_ENTRY_POINT", entryPointString, 1);
#endif
}
}