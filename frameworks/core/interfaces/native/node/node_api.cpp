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

#include <deque>

#include "base/error/error_code.h"
#include "base/log/log_wrapper.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "core/interfaces/native/node/canvas_rendering_context_2d_modifier.h"
#include "core/interfaces/native/node/custom_dialog_model.h"
#include "core/interfaces/native/node/node_animate.h"
#include "core/interfaces/native/node/node_canvas_modifier.h"
#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/interfaces/native/node/node_checkbox_modifier.h"
#include "core/interfaces/native/node/node_common_modifier.h"
#include "core/interfaces/native/node/node_date_picker_modifier.h"
#include "core/interfaces/native/node/node_image_modifier.h"
#include "core/interfaces/native/node/node_list_modifier.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"
#include "core/interfaces/native/node/node_scroll_modifier.h"
#include "core/interfaces/native/node/node_slider_modifier.h"
#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "core/interfaces/native/node/node_text_area_modifier.h"
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "core/interfaces/native/node/node_timepicker_modifier.h"
#include "core/interfaces/native/node/node_toggle_modifier.h"
#include "core/interfaces/native/node/util_modifier.h"
#include "core/interfaces/native/node/view_model.h"
#include "core/interfaces/native/node/water_flow_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

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
    static const ArkUIStateModifier modifier = { GetUIState, SetSupportedUIState };
    return &modifier;
}
} // namespace NodeModifier

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

static EventReceiver globalEventReceiver = nullptr;

void SendArkUIAsyncEvent(ArkUINodeEvent* event)
{
    if (globalEventReceiver) {
        globalEventReceiver(event);
    } else {
        g_eventQueue.push_back(*event);
    }
}
} // namespace NodeEvent

namespace CustomNodeEvent {
std::deque<ArkUICustomNodeEvent> g_eventQueue;
int CheckEvent(ArkUICustomNodeEvent* event)
{
    if (!g_eventQueue.empty()) {
        *event = g_eventQueue.front();
        g_eventQueue.pop_front();
        return 1;
    }
    return 0;
}

void (*g_fliter)(ArkUICustomNodeEvent* event) = nullptr;
void SendArkUIAsyncEvent(ArkUICustomNodeEvent* event)
{
    if (g_fliter) {
        g_fliter(event);
    } else {
        g_eventQueue.push_back(*event);
    }
}
} // namespace CustomNodeEvent

namespace {

void SetCustomCallback(ArkUIVMContext context, ArkUINodeHandle node, ArkUI_Int32 callback)
{
    ViewModel::SetCustomCallback(context, node, callback);
}

ArkUINodeHandle CreateNode(ArkUINodeType type, int peerId, ArkUI_Int32 flags)
{
    auto* node = reinterpret_cast<ArkUINodeHandle>(ViewModel::CreateNode(type, peerId));
    return node;
}

ArkUINodeHandle GetNodeByViewStack()
{
    auto node = ViewStackProcessor::GetInstance()->Finish();
    node->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(node));
}

void DisposeNode(ArkUINodeHandle node)
{
    ViewModel::DisposeNode(node);
}

ArkUI_CharPtr GetName(ArkUINodeHandle node)
{
    return ViewModel::GetName(node);
}

static void DumpTree(ArkUINodeHandle node, int indent)
{
    TAG_LOGI(AceLogTag::ACE_NATIVE_NODE, "dumpTree %{public}p", node);
}

void DumpTreeNode(ArkUINodeHandle node)
{
    DumpTree(node, 0);
}

ArkUI_Int32 AddChild(ArkUINodeHandle parent, ArkUINodeHandle child)
{
    auto* nodeAdapter = NodeAdapter::GetNodeAdapterAPI()->getNodeAdapter(parent);
    if (nodeAdapter) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_EXIST;
    }
    ViewModel::AddChild(parent, child);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 InsertChildAt(ArkUINodeHandle parent, ArkUINodeHandle child, int32_t position)
{
    auto* nodeAdapter = NodeAdapter::GetNodeAdapterAPI()->getNodeAdapter(parent);
    if (nodeAdapter) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_EXIST;
    }
    ViewModel::InsertChildAt(parent, child, position);
    return ERROR_CODE_NO_ERROR;
}

void RemoveChild(ArkUINodeHandle parent, ArkUINodeHandle child)
{
    ViewModel::RemoveChild(parent, child);
}

ArkUI_Int32 InsertChildAfter(ArkUINodeHandle parent, ArkUINodeHandle child, ArkUINodeHandle sibling)
{
    auto* nodeAdapter = NodeAdapter::GetNodeAdapterAPI()->getNodeAdapter(parent);
    if (nodeAdapter) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_EXIST;
    }
    ViewModel::InsertChildAfter(parent, child, sibling);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Bool IsBuilderNode(ArkUINodeHandle node)
{
    return ViewModel::IsBuilderNode(node);
}

ArkUI_Int32 InsertChildBefore(ArkUINodeHandle parent, ArkUINodeHandle child, ArkUINodeHandle sibling)
{
    auto* nodeAdapter = NodeAdapter::GetNodeAdapterAPI()->getNodeAdapter(parent);
    if (nodeAdapter) {
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_EXIST;
    }
    ViewModel::InsertChildBefore(parent, child, sibling);
    return ERROR_CODE_NO_ERROR;
}

void SetAttribute(ArkUINodeHandle node, ArkUI_CharPtr attribute, ArkUI_CharPtr value)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "%{public}p SetAttribute %{public}s, %{public}s", node, attribute, value);
}

ArkUI_CharPtr GetAttribute(ArkUINodeHandle node, ArkUI_CharPtr attribute)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "%{public}p GetAttribute %{public}s", node, attribute);
    return "";
}

void ResetAttribute(ArkUINodeHandle nodePtr, ArkUI_CharPtr attribute)
{
    TAG_LOGI(AceLogTag::ACE_NATIVE_NODE, "Reset attribute %{public}s", attribute);
}

typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);

/**
 * IMPORTANT!!!
 * the order of declaring the handler must be same as the in the ArkUIEventSubKind enum
 */
/* clang-format off */
const ComponentAsyncEventHandler commonNodeAsyncEventHandlers[] = {
    NodeModifier::SetOnAppear,
    NodeModifier::SetOnDisappear,
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
    NodeModifier::SetOnTouchIntercept,
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
    NodeModifier::SetOnTextInputSelectionChange,
};

const ComponentAsyncEventHandler textAreaNodeAsyncEventHandlers[] = {
    nullptr,
    nullptr,
    NodeModifier::SetOnTextAreaChange,
    NodeModifier::SetOnTextAreaPaste,
    NodeModifier::SetOnTextAreaSelectionChange,
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
    NodeModifier::SetImageOnSvgPlayFinish,
};

const ComponentAsyncEventHandler DATE_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetDatePickerOnDateChange,
};

const ComponentAsyncEventHandler TIME_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetTimePickerOnChange,
};

const ComponentAsyncEventHandler TEXT_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetTextPickerOnChange,
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

const ComponentAsyncEventHandler SWIPER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetSwiperChange,
    NodeModifier::SetSwiperAnimationStart,
    NodeModifier::SetSwiperAnimationEnd,
    NodeModifier::SetSwiperGestureSwipe,
};

const ComponentAsyncEventHandler CANVAS_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetCanvasOnReady,
};

const ComponentAsyncEventHandler listNodeAsyncEventHandlers[] = {
    NodeModifier::SetOnListScroll,
    nullptr,
    NodeModifier::SetOnListScrollStart,
    NodeModifier::SetOnListScrollStop,
    NodeModifier::SetOnListScrollFrameBegin,
};

const ComponentAsyncEventHandler WATER_FLOW_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnWillScroll,
    NodeModifier::SetOnReachEnd,
};

/* clang-format on */
void NotifyComponentAsyncEvent(ArkUINodeHandle node, ArkUIEventSubKind kind, ArkUI_Int64 extraParam)
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
            // text input event type.
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
        case ARKUI_TEXT_PICKER: {
            if (subKind >= sizeof(TEXT_PICKER_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TEXT_PICKER_NODE_ASYNC_EVENT_HANDLERS[subKind];
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
        case ARKUI_SWIPER: {
            // swiper event type.
            if (subKind >= sizeof(SWIPER_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SWIPER_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_CANVAS: {
            if (subKind >= sizeof(CANVAS_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CANVAS_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_LIST: {
            // list event type.
            if (subKind >= sizeof(listNodeAsyncEventHandlers) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = listNodeAsyncEventHandlers[subKind];
            break;
        }
        case ARKUI_WATER_FLOW: {
            // swiper event type.
            if (subKind >= sizeof(WATER_FLOW_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = WATER_FLOW_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        default: {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        }
    }
    if (eventHandle) {
        // TODO: fix handlers.
        eventHandle(node, reinterpret_cast<void*>(static_cast<intptr_t>(extraParam)));
    } else {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d EMPTY IMPLEMENT", kind);
    }
}

void NotifyResetComponentAsyncEvent(ArkUINodeHandle node, ArkUIEventSubKind subKind)
{
    // TODO
}

void RegisterNodeAsyncEventReceiver(EventReceiver eventReceiver)
{
    NodeEvent::globalEventReceiver = eventReceiver;
}

void UnregisterNodeAsyncEventReceiver()
{
    NodeEvent::globalEventReceiver = nullptr;
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

void SetAttachNodePtr(ArkUINodeHandle node, void* value)
{
    return ViewModel::SetAttachNodePtr(node, value);
}

void* GetAttachNodePtr(ArkUINodeHandle node)
{
    return ViewModel::GetAttachNodePtr(node);
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

void RegisterCustomNodeAsyncEvent(ArkUINodeHandle node, int32_t eventType, void* extraParam)
{
    auto companion = ViewModel::GetCompanion(node);
    if (!companion) {
        ViewModel::RegisterCompanion(node, -1, eventType);
        auto companion = ViewModel::GetCompanion(node);
        CHECK_NULL_VOID(companion);
        companion->SetExtraParam(eventType, extraParam);
    } else {
        auto originEventType = companion->GetFlags();
        companion->SetFlags(originEventType | eventType);
        companion->SetExtraParam(eventType, extraParam);
    }
}

ArkUI_Int32 UnregisterCustomNodeEvent(ArkUINodeHandle node, ArkUI_Int32 eventType)
{
    auto companion = ViewModel::GetCompanion(node);
    CHECK_NULL_RETURN(companion, -1);
    auto originEventType = companion->GetFlags();
    //check is Contains
    if ((originEventType & eventType) != eventType) {
        return -1;
    }
    companion->SetFlags(originEventType ^ eventType);
    companion->EraseExtraParam(eventType);
    return 0;
}

void RegisterCustomNodeEventReceiver(void (*eventReceiver)(ArkUICustomNodeEvent* event))
{
    CustomNodeEvent::g_fliter = eventReceiver;
}

void SetMeasureWidth(ArkUINodeHandle node, ArkUI_Int32 value)
{
    // directly set frameNode measure width.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (!frameNode) {
        return;
    }
    frameNode->GetGeometryNode()->SetFrameWidth(value);
}

ArkUI_Int32 GetMeasureWidth(ArkUINodeHandle node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (!frameNode) {
        return 0;
    }
    return frameNode->GetGeometryNode()->GetFrameSize().Width();
}

void SetMeasureHeight(ArkUINodeHandle node, ArkUI_Int32 value)
{
    // directly set frameNode measure height.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (!frameNode) {
        return;
    }
    frameNode->GetGeometryNode()->SetFrameHeight(value);
}

ArkUI_Int32 GetMeasureHeight(ArkUINodeHandle node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (!frameNode) {
        return 0;
    }
    return frameNode->GetGeometryNode()->GetFrameSize().Height();
}

void SetX(ArkUINodeHandle node, ArkUI_Int32 value)
{
    // directly set frameNode measure postionX.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (!frameNode) {
        return;
    }
    frameNode->GetGeometryNode()->SetMarginFrameOffsetX(value);
}

void SetY(ArkUINodeHandle node, ArkUI_Int32 value)
{
    // directly set frameNode measure postionY.
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (!frameNode) {
        return;
    }
    frameNode->GetGeometryNode()->SetMarginFrameOffsetY(value);
}

ArkUI_Int32 GetX(ArkUINodeHandle node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (!frameNode) {
        return 0;
    }
    return frameNode->GetGeometryNode()->GetMarginFrameOffset().GetX();
}

ArkUI_Int32 GetY(ArkUINodeHandle node)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    if (!frameNode) {
        return 0;
    }
    return frameNode->GetGeometryNode()->GetMarginFrameOffset().GetY();
}

void SetCustomMethodFlag(ArkUINodeHandle node, ArkUI_Int32 flag)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->SetFlags(flag);
}

ArkUI_Int32 GetCustomMethodFlag(ArkUINodeHandle node)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_RETURN(companion, 0);
    return companion->GetFlags();
}

void SetAlignment(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_VOID(companion);
    companion->SetAlignmentValue(value);
}

ArkUI_Int32 GetAlignment(ArkUINodeHandle node)
{
    auto* companion = ViewModel::GetCompanion(node);
    CHECK_NULL_RETURN(companion, 0);
    return companion->GetAlignmentValue();
}

void GetLayoutConstraint(ArkUINodeHandle node, ArkUI_Int32* value)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    auto layoutConstraint = frameNode->GetLayoutProperty()->GetContentLayoutConstraint();
    if (layoutConstraint.has_value()) {
        //min
        value[0] = static_cast<ArkUI_Int32>(layoutConstraint.value().minSize.Width());
        //min
        value[1] = static_cast<ArkUI_Int32>(layoutConstraint.value().minSize.Height());
        //.max
        value[2] = static_cast<ArkUI_Int32>(layoutConstraint.value().maxSize.Width());
        //.max
        value[3] = static_cast<ArkUI_Int32>(layoutConstraint.value().maxSize.Height());
        //percentReference
        value[4] = static_cast<ArkUI_Int32>(layoutConstraint.value().percentReference.Width());
        //percentReference
        value[5] = static_cast<ArkUI_Int32>(layoutConstraint.value().percentReference.Height());
    }
}

const ArkUIBasicAPI* GetBasicAPI()
{
    /* clang-format off */
    static const ArkUIBasicAPI basicImpl = {
        CreateNode,
        GetNodeByViewStack,
        DisposeNode,
        GetName,
        DumpTreeNode,

        AddChild,
        RemoveChild,
        InsertChildAfter,
        InsertChildBefore,
        InsertChildAt,
        GetAttribute,
        SetAttribute,
        ResetAttribute,

        NotifyComponentAsyncEvent,
        NotifyResetComponentAsyncEvent,
        RegisterNodeAsyncEventReceiver,
        UnregisterNodeAsyncEventReceiver,

        nullptr,

        ApplyModifierFinish,
        MarkDirty,
        IsBuilderNode,
    };
    /* clang-format on */

    return &basicImpl;
}

ArkUIDialogHandle CreateDialog()
{
    return CustomDialog::CreateDialog();
}

void DisposeDialog(ArkUIDialogHandle handle)
{
    CustomDialog::DisposeDialog(handle);
}

ArkUI_Int32 SetDialogContent(ArkUIDialogHandle handle, ArkUINodeHandle contentNode)
{
    return CustomDialog::SetDialogContent(handle, contentNode);
}

ArkUI_Int32 RemoveDialogContent(ArkUIDialogHandle handle)
{
    return CustomDialog::RemoveDialogContent(handle);
}

ArkUI_Int32 SetDialogContentAlignment(
    ArkUIDialogHandle handle, ArkUI_Int32 alignment, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY)
{
    return CustomDialog::SetDialogContentAlignment(handle, alignment, offsetX, offsetY);
}

ArkUI_Int32 ResetDialogContentAlignment(ArkUIDialogHandle handle)
{
    return CustomDialog::ResetDialogContentAlignment(handle);
}

ArkUI_Int32 SetDialogModalMode(ArkUIDialogHandle handle, ArkUI_Bool isModal)
{
    return CustomDialog::SetDialogModalMode(handle, isModal);
}

ArkUI_Int32 SetDialogAutoCancel(ArkUIDialogHandle handle, ArkUI_Bool autoCancel)
{
    return CustomDialog::SetDialogAutoCancel(handle, autoCancel);
}

ArkUI_Int32 SetDialogMask(ArkUIDialogHandle handle, ArkUI_Uint32 maskColor, ArkUIRect* rect)
{
    return CustomDialog::SetDialogMask(handle, maskColor, rect);
}

ArkUI_Int32 SetDialogBackgroundColor(ArkUIDialogHandle handle, uint32_t backgroundColor)
{
    return CustomDialog::SetDialogBackgroundColor(handle, backgroundColor);
}

ArkUI_Int32 SetDialogCornerRadius(
    ArkUIDialogHandle handle, float topLeft, float topRight, float bottomLeft, float bottomRight)
{
    return CustomDialog::SetDialogCornerRadius(handle, topLeft, topRight, bottomLeft, bottomRight);
}

ArkUI_Int32 SetDialogGridColumnCount(ArkUIDialogHandle handle, int32_t gridCount)
{
    return CustomDialog::SetDialogGridColumnCount(handle, gridCount);
}

ArkUI_Int32 EnableDialogCustomStyle(ArkUIDialogHandle handle, ArkUI_Bool enableCustomStyle)
{
    return CustomDialog::EnableDialogCustomStyle(handle, enableCustomStyle);
}

ArkUI_Int32 EnableDialogCustomAnimation(ArkUIDialogHandle handle, ArkUI_Bool enableCustomAnimation)
{
    return CustomDialog::EnableDialogCustomAnimation(handle, enableCustomAnimation);
}

ArkUI_Int32 ShowDialog(ArkUIDialogHandle handle, ArkUI_Bool showInSubWindow)
{
    return CustomDialog::ShowDialog(handle, showInSubWindow);
}

ArkUI_Int32 CloseDialog(ArkUIDialogHandle handle)
{
    return CustomDialog::CloseDialog(handle);
}

// Register closing event
ArkUI_Int32 RegisterOnWillDialogDismiss(ArkUIDialogHandle handle, bool (*eventHandler)(ArkUI_Int32))
{
    return CustomDialog::RegisterOnWillDialogDismiss(handle, eventHandler);
}

const ArkUIDialogAPI* GetDialogAPI()
{
    static const ArkUIDialogAPI dialogImpl = {
        CreateDialog,
        DisposeDialog,
        SetDialogContent,
        RemoveDialogContent,
        SetDialogContentAlignment,
        ResetDialogContentAlignment,
        SetDialogModalMode,
        SetDialogAutoCancel,
        SetDialogMask,
        SetDialogBackgroundColor,
        SetDialogCornerRadius,
        SetDialogGridColumnCount,
        EnableDialogCustomStyle,
        EnableDialogCustomAnimation,
        ShowDialog,
        CloseDialog,
        RegisterOnWillDialogDismiss,
    };
    return &dialogImpl;
}

void ShowCrash(ArkUI_CharPtr message)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Arkoala crash: %{public}s", message);
}

/* clang-format off */
ArkUIExtendedNodeAPI impl_extended = {
    ARKUI_EXTENDED_API_VERSION,

    NodeModifier::GetUtilsModifier, // getUtilsModifier
    NodeModifier::GetCanvasRenderingContext2DModifier,

    SetCallbackMethod,
    SetCustomMethodFlag,
    GetCustomMethodFlag,
    RegisterCustomNodeAsyncEvent,
    UnregisterCustomNodeEvent,
    RegisterCustomNodeEventReceiver,
    SetCustomCallback, // setCustomCallback
    MeasureLayoutAndDraw,
    MeasureNode,
    LayoutNode,
    DrawNode,
    SetAttachNodePtr,
    GetAttachNodePtr,
    SetMeasureWidth, // setMeasureWidth
    GetMeasureWidth, // getMeasureWidth
    SetMeasureHeight, // setMeasureHeight
    GetMeasureHeight, // getMeasureHeight
    SetX, // setX
    SetY, // setY
    GetX, // getX
    GetY, // getY
    GetLayoutConstraint,
    SetAlignment,
    GetAlignment,
    nullptr, // indexerChecker
    nullptr, // setRangeUpdater
    nullptr, // setLazyItemIndexer
    SetVsyncCallback,
    UnblockVsyncWait,
    NodeEvent::CheckEvent,
    NodeEvent::SendArkUIAsyncEvent, // sendEvent
    nullptr, // callContinuation
    nullptr, // setChildTotalCount
    ShowCrash,
};
/* clang-format on */

void CanvasDrawRect(ArkUICanvasHandle canvas, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right,
    ArkUI_Float32 bottom, ArkUIPaintHandle paint)
{
    TAG_LOGI(AceLogTag::ACE_NATIVE_NODE,
        "DrawRect canvas=%{public}p [%{public}f, %{public}f, %{public}f, %{public}f]\n", canvas, left, top, right,
        bottom);
}

const ArkUIGraphicsCanvas* GetCanvasAPI()
{
    static const ArkUIGraphicsCanvas modifier = { nullptr, nullptr, nullptr, nullptr, nullptr, CanvasDrawRect,
        nullptr };
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
    static const ArkUIGraphicsPaint modifier = { PaintMake, PaintFinalize, nullptr, nullptr, nullptr, nullptr };
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
    static const ArkUIGraphicsAPI api = { ARKUI_NODE_GRAPHICS_API_VERSION, SetCallbackMethod, GetCanvasAPI, GetPaintAPI,
        GetFontAPI };
    return &api;
}

void AnimateTo(ArkUIContext* context, ArkUIAnimateOption option, void* event, void* user)
{
    ViewAnimate::AnimateTo(context, option, reinterpret_cast<void (*)(void*)>(event), user);
}

const ArkUIAnimation* GetAnimationAPI()
{
    static const ArkUIAnimation modifier = {
        nullptr,
        nullptr,
        nullptr,
        AnimateTo,
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

const ArkUIExtendedNodeAPI* GetExtendedAPI()
{
    return &impl_extended;
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
    GetDialogAPI,
    GetExtendedAPI,         // Extended
    NodeAdapter::GetNodeAdapterAPI,         // adapter.
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

void SendArkUIAsyncCustomEvent(ArkUICustomNodeEvent* event)
{
    OHOS::Ace::NG::CustomNodeEvent::SendArkUIAsyncEvent(event);
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
                        "Requested basic version %{public}d is not supported, we're version %{public}d\n", version,
                        ARKUI_BASIC_API_VERSION);

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
                        "Requested full version %{public}d is not supported, we're version %{public}d\n", version,
                        ARKUI_FULL_API_VERSION);

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
                        "Requested graphics version %{public}d is not supported, we're version %{public}d\n", version,
                        ARKUI_NODE_GRAPHICS_API_VERSION);

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
                        "Requested extended version %{public}d is not supported, we're version %{public}d\n", version,
                        ARKUI_EXTENDED_API_VERSION);

                    return nullptr;
                }
            }
        }
        default: {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "API kind %{public}d is not supported\n",
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
