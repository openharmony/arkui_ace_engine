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
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "core/interfaces/native/node/node_common_modifier.h"
#include "core/interfaces/native/node/node_image_modifier.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"
#include "core/interfaces/native/node/node_date_picker_modifier.h"
#include "core/interfaces/native/node/node_scroll_modifier.h"
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/node/node_text_area_modifier.h"
#include "core/interfaces/native/node/node_timepicker_modifier.h"
#include "core/interfaces/native/node/node_toggle_modifier.h"
#include "core/interfaces/native/node/node_checkbox_modifier.h"
#include "core/interfaces/native/node/node_slider_modifier.h"
#include "core/interfaces/native/node/view_model.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace::NG {

ArkUINodeHandle GetFrameNodeById(ArkUI_Int32 nodeId)
{
    auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

ArkUI_Int64 GetUIState(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, 0);
    return eventHub->GetCurrentUIState();
}

void SetSupportedUIState(ArkUINodeHandle node, ArkUI_Int64 state)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->AddSupportedState(static_cast<uint64_t>(state));
}

namespace NodeModifier {
const ArkUIStateModifier* GetUIStateModifier()
{
    static const ArkUIStateModifier modifier = { GetFrameNodeById, GetUIState, SetSupportedUIState };
    return &modifier;
}
}

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

void SetCustomCallback(ArkUINodeHandle node, ArkUI_Int32 callback)
{
    ViewModel::SetCustomCallback(node, callback);
}

ArkUINodeHandle CreateNode(ArkUINodeType type, int peerId, ArkUI_Int32 flags)
{
    auto* node = reinterpret_cast<ArkUINodeHandle>(ViewModel::CreateNode(type, peerId));
    ViewModel::RegisterCompanion(node, peerId, flags);
    return node;
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
    NodeModifier::SetOnAppear,
    nullptr,
    NodeModifier::SetOnTouch,
    NodeModifier::SetOnClick,
    nullptr,
    NodeModifier::SetOnBlur,
    nullptr,
    nullptr,
    NodeModifier::SetOnAreaChange,
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
    NodeModifier::SetOnTextInputCut,
    NodeModifier::SetOnTextInputPaste,
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

const ComponentAsyncEventHandler imageNodeAsyncEventHandlers[] = {
    NodeModifier::SetImageOnComplete,
    NodeModifier::SetImageOnError,
};

const ComponentAsyncEventHandler DATE_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetDatePickerOnDateChange,
};

const ComponentAsyncEventHandler TIME_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetTimePickerOnChange,
};

const ComponentAsyncEventHandler CALENDAR_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetCalendarPickerOnChange,
};

const ComponentAsyncEventHandler CHECKBOX_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetCheckboxChange,
};

const ComponentAsyncEventHandler SLIDER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetSliderChange,
};

/* clang-format on */
void NotifyComponentAsyncEvent(ArkUINodeHandle node, ArkUIAsyncEventKind kind, ArkUI_Int64 extraParam)
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
        case ARKUI_IMAGE: {
            if (subKind >= sizeof(imageNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = imageNodeAsyncEventHandlers[subKind];
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
        case ARKUI_DATE_PICKER: {
            // datepicker event type.
            if (subKind >= sizeof(DATE_PICKER_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = DATE_PICKER_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_TIME_PICKER: {
            // timepicker event type.
            if (subKind >= sizeof(TIME_PICKER_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TIME_PICKER_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_CALENDAR_PICKER: {
            // calendar picker event type.
            if (subKind >= sizeof(CALENDAR_PICKER_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CALENDAR_PICKER_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_CHECKBOX: {
            // timepicker event type.
            if (subKind >= sizeof(CHECKBOX_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CHECKBOX_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_SLIDER: {
            // timepicker event type.
            if (subKind >= sizeof(SLIDER_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SLIDER_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        default: {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        }
    }
    if (eventHandle) {
        // TODO: fix handlers.
        eventHandle(node, 0, reinterpret_cast<void*>(static_cast<intptr_t>(extraParam)));
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

static void SetCallbackMethod(ArkUIAPICallbackMethod* method)
{
    ViewModel::SetCallbackMethod(method);
}

ArkUIAPICallbackMethod* GetArkUIAPICallbackMethod()
{
    return ViewModel::GetCallbackMethod();
}

int SetVsyncCallback(ArkUIVMContext vmContext, ArkUI_Int32 device, ArkUI_Int32 callbackId)
{
    static int vsyncCount = 1;
    auto vsync = [vmContext, callbackId]() {
        ArkUIEventCallbackArg args[] = { { vsyncCount++ } };
        ArkUIAPICallbackMethod* cbs = GetArkUIAPICallbackMethod();
        CHECK_NULL_VOID(vmContext);
        CHECK_NULL_VOID(cbs);
        cbs->CallInt(vmContext, callbackId, 1, &args[0]);
    };
    PipelineContext::GetCurrentContext()->SetVsyncListener(vsync);
    return 0;
}

void UnblockVsyncWait(ArkUIVMContext vmContext, ArkUI_Int32 device)
{
    PipelineContext::GetCurrentContext()->RequestFrame();
}

ArkUI_Int32 MeasureNode(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Float32* data)
{
    return ViewModel::MeasureNode(vmContext, node, data);
}

ArkUI_Int32 LayoutNode(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Float32* data)
{
    return ViewModel::LayoutNode(vmContext, node, data);
}

ArkUI_Int32 DrawNode(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Float32* data)
{
    return ViewModel::DrawNode(vmContext, node, data);
}

ArkUI_Int32 MeasureLayoutAndDraw(ArkUIVMContext vmContext, ArkUINodeHandle rootPtr)
{
    auto* root = reinterpret_cast<FrameNode*>(rootPtr);
    float scale = static_cast<float>(OHOS::Ace::SystemProperties::GetResolution());
    float width = root->GetGeometryNode()->GetFrameSize().Width() / scale;
    float height = root->GetGeometryNode()->GetFrameSize().Height() / scale;
    // measure
    ArkUI_Float32 measureData[] = { width, height, width, height };
    MeasureNode(vmContext, rootPtr, &measureData[0]);
    // layout
    ArkUI_Float32 layoutData[] = { 0, 0, width, height };
    LayoutNode(vmContext, rootPtr, &layoutData[0]);
    // draw
    ArkUI_Float32 drawData[] = { 0, 0, 0, 0 };
    DrawNode(vmContext, rootPtr, &drawData[0]);

    return 0;
}

void SetMeasureWidth(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->setMeasureWidthValue(value);
}

ArkUI_Float32 GetMeasureWidth(ArkUINodeHandle node)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_RETURN(companion, 0);
    return companion->getMeasureWidthValue();
}

void SetMeasureHeight(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->setMeasureHeightValue(value);
}

ArkUI_Float32 GetMeasureHeight(ArkUINodeHandle node)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_RETURN(companion, 0);
    return companion->getMeasureHeightValue();
}

void SetX(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->setXValue(value);
}

void SetY(ArkUINodeHandle node, ArkUI_Float32 value)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->setYValue(value);
}

void SetAlignment(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->alignment = value;
}

ArkUI_Int32 GetAlignment(ArkUINodeHandle node)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_RETURN(companion, 0);
    return companion->alignment;
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

void ShowCrash(ArkUI_CharPtr message)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Arkoala crash: %{public}s", message);
}
/* clang-format off */
ArkUIExtendedNodeAPI impl_extended = {
    ARKUI_EXTENDED_API_VERSION,

    nullptr, // getUtilsModifier
    nullptr, // getCanvasRenderingContext2DModifier

    SetCallbackMethod,
    SetCustomCallback, // setCustomCallback
    MeasureLayoutAndDraw,
    MeasureNode,
    LayoutNode,
    DrawNode,
    SetMeasureWidth, // setMeasureWidth
    GetMeasureWidth, // getMeasureWidth
    SetMeasureHeight, // setMeasureHeight
    GetMeasureHeight, // getMeasureHeight
    SetX, // setX
    SetY, // setY
    SetAlignment,
    GetAlignment,
    nullptr, // indexerChecker
    nullptr, // setRangeUpdater
    nullptr, // setLazyItemIndexer
    OHOS::Ace::NG::SetVsyncCallback,
    OHOS::Ace::NG::UnblockVsyncWait,
    OHOS::Ace::NG::NodeEvent::CheckEvent,
    nullptr, // sendEvent
    nullptr, // callContinuation
    nullptr, // setChildTotalCount
    ShowCrash,
};
/* clang-format on */

void CanvasDrawRect(ArkUICanvasHandle canvas, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right,
    ArkUI_Float32 bottom, ArkUIPaintHandle paint)
{
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