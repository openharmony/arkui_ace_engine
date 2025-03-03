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

#include <securec.h>
#include <vector>

#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/interfaces/native/node/alphabet_indexer_modifier.h"
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "core/interfaces/native/node/canvas_rendering_context_2d_modifier.h"
#include "core/interfaces/native/node/custom_dialog_model.h"
#include "core/interfaces/native/node/drag_adapter_impl.h"
#include "core/interfaces/native/node/grid_modifier.h"
#include "core/interfaces/native/node/image_animator_modifier.h"
#include "core/interfaces/native/node/node_adapter_impl.h"
#include "core/interfaces/native/node/node_animate.h"
#include "core/interfaces/native/node/node_canvas_modifier.h"
#include "core/interfaces/native/node/node_checkbox_modifier.h"
#include "core/interfaces/native/node/node_common_modifier.h"
#include "core/interfaces/native/node/node_custom_node_ext_modifier.h"
#include "core/interfaces/native/node/node_drag_modifier.h"
#include "core/interfaces/native/node/node_date_picker_modifier.h"
#include "core/interfaces/native/node/node_image_modifier.h"
#include "core/interfaces/native/node/node_image_span_modifier.h"
#include "core/interfaces/native/node/node_list_item_modifier.h"
#include "core/interfaces/native/node/node_list_modifier.h"
#include "core/interfaces/native/node/node_refresh_modifier.h"
#include "core/interfaces/native/node/node_scroll_modifier.h"
#include "core/interfaces/native/node/node_slider_modifier.h"
#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "core/interfaces/native/node/node_span_modifier.h"
#include "core/interfaces/native/node/node_text_area_modifier.h"
#include "core/interfaces/native/node/node_text_input_modifier.h"
#include "core/interfaces/native/node/node_text_modifier.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "core/interfaces/native/node/node_timepicker_modifier.h"
#include "core/interfaces/native/node/node_toggle_modifier.h"
#include "core/interfaces/native/node/radio_modifier.h"
#include "core/interfaces/native/node/search_modifier.h"
#include "core/interfaces/native/node/select_modifier.h"
#include "core/interfaces/native/node/util_modifier.h"
#include "core/interfaces/native/node/view_model.h"
#include "core/interfaces/native/node/water_flow_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/text/html_utils.h"
#include "interfaces/native/native_type.h"
#include "core/interfaces/native/node/checkboxgroup_modifier.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INVLID_VALUE = -1;

int32_t WriteStringToBuffer(const std::string& src, char* buffer, int32_t bufferSize, int32_t* writeLen)
{
    CHECK_NULL_RETURN(buffer, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(writeLen, ERROR_CODE_PARAM_INVALID);
    if (src.empty()) {
        return ERROR_CODE_NO_ERROR;
    }
    int32_t srcLength = static_cast<int32_t>(src.length());
    if (bufferSize - 1 < srcLength) {
        *writeLen = srcLength == INT32_MAX ? INT32_MAX : srcLength + 1;
        return ERROR_CODE_NATIVE_IMPL_BUFFER_SIZE_ERROR;
    }
    src.copy(buffer, srcLength);
    buffer[srcLength] = '\0';
    *writeLen = srcLength;
    return ERROR_CODE_NO_ERROR;
}

std::shared_ptr<NavDestinationInfo> GetNavDestinationInfoByNode(ArkUINodeHandle node)
{
    FrameNode* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    return NG::UIObserverHandler::GetInstance().GetNavigationState(Ace::AceType::Claim<FrameNode>(currentNode));
}

std::shared_ptr<RouterPageInfoNG> GetRouterPageInfoByNode(ArkUINodeHandle node)
{
    FrameNode* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    return NG::UIObserverHandler::GetInstance().GetRouterPageState(Ace::AceType::Claim<FrameNode>(currentNode));
}

RefPtr<NavigationStack> GetNavigationStackByNode(ArkUINodeHandle node)
{
    FrameNode* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto pipeline = currentNode->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto navigationMgr = pipeline->GetNavigationManager();
    CHECK_NULL_RETURN(navigationMgr, nullptr);
    auto result = navigationMgr->GetNavigationInfo(Ace::AceType::Claim<FrameNode>(currentNode));
    CHECK_NULL_RETURN(result, nullptr);
    return result->pathStack.Upgrade();
}
} // namespace

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

void AddSupportedUIState(ArkUINodeHandle node, ArkUI_Int64 state, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    std::function<void(uint64_t)>* func = reinterpret_cast<std::function<void(uint64_t)>*>(callback);
    eventHub->AddSupportedUIStateWithCallback(static_cast<uint64_t>(state), *func, false);
    func = nullptr;
}

void RemoveSupportedUIState(ArkUINodeHandle node, ArkUI_Int64 state)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->RemoveSupportedUIState(static_cast<uint64_t>(state), false);
}

namespace NodeModifier {
const ArkUIStateModifier* GetUIStateModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIStateModifier modifier = {
        .getUIState = GetUIState,
        .setSupportedUIState = SetSupportedUIState,
        .addSupportedUIState = AddSupportedUIState,
        .removeSupportedUIState = RemoveSupportedUIState
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIStateModifier* GetCJUIStateModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIStateModifier modifier = {
        .getUIState = GetUIState,
        .setSupportedUIState = SetSupportedUIState,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier

namespace NodeEvent {

static EventReceiver globalEventReceiver = nullptr;

void SendArkUISyncEvent(ArkUINodeEvent* event)
{
    if (globalEventReceiver) {
        globalEventReceiver(event);
    }
}
} // namespace NodeEvent

namespace CustomNodeEvent {

void (*g_fliter)(ArkUICustomNodeEvent* event) = nullptr;
void SendArkUISyncEvent(ArkUICustomNodeEvent* event)
{
    if (g_fliter) {
        g_fliter(event);
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
    ArkUINodeHandle node = nullptr;
    if (flags == ARKUI_NODE_FLAG_C) {
        ContainerScope Scope(Container::CurrentIdSafelyWithCheck());
        node = reinterpret_cast<ArkUINodeHandle>(ViewModel::CreateNode(type, peerId));
        auto* uiNode = reinterpret_cast<UINode*>(node);
        if (uiNode) {
            uiNode->setIsCNode(true);
        }
    } else {
        node = reinterpret_cast<ArkUINodeHandle>(ViewModel::CreateNode(type, peerId));
    }
    return node;
}

ArkUINodeHandle CreateNodeWithParams(ArkUINodeType type, int peerId, ArkUI_Int32 flags, const ArkUI_Params& params)
{
    auto* node = reinterpret_cast<ArkUINodeHandle>(ViewModel::CreateNodeWithParams(type, peerId, params));
    return node;
}

ArkUINodeHandle GetNodeByViewStack()
{
    auto node = ViewStackProcessor::GetInstance()->Finish();
    node->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(node));
}

ArkUINodeHandle GetTopNodeByViewStack()
{
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(node, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(node);
}

ArkUINodeHandle CreateCustomNode(ArkUI_CharPtr tag)
{
    return reinterpret_cast<ArkUINodeHandle>(ViewModel::CreateCustomNode(tag));
}

ArkUINodeHandle GetOrCreateCustomNode(ArkUI_CharPtr tag)
{
    return reinterpret_cast<ArkUINodeHandle>(ViewModel::GetOrCreateCustomNode(tag));
}

ArkUI_Bool IsRightToLeft()
{
    return AceApplicationInfo::GetInstance().IsRightToLeft();
}

void CreateNewScope()
{
    ViewStackModel::GetInstance()->NewScope();
}

ArkUIRSNodeHandle GetRSNodeByNode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto rsNode = frameNode->GetExtraCustomProperty("RS_NODE");
    CHECK_NULL_RETURN(rsNode, nullptr);
    return reinterpret_cast<ArkUIRSNodeHandle>(rsNode);
}

void RegisterOEMVisualEffect(ArkUIOEMVisualEffectFuncHandle func)
{
    OEMVisualEffectFunc oemFunc = reinterpret_cast<OEMVisualEffectFunc>(func);
    ViewAbstract::RegisterOEMVisualEffect(oemFunc);
}

void SetOnNodeDestroyCallback(ArkUINodeHandle node, void (*onDestroy)(ArkUINodeHandle node))
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    auto onDestroyCallback = [node, onDestroy](int32_t nodeId) {
        onDestroy(node);
    };
    uiNode->SetOnNodeDestroyCallback(std::move(onDestroyCallback));
}

void DisposeNode(ArkUINodeHandle node)
{
    ViewModel::DisposeNode(node);
}

ArkUI_CharPtr GetName(ArkUINodeHandle node)
{
    return ViewModel::GetName(node);
}

static void DumpTree(ArkUINodeHandle node, int indent) {}

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

ArkUI_Float64 ConvertLengthMetricsUnit(ArkUI_Float64 value, ArkUI_Int32 originUnit, ArkUI_Int32 targetUnit)
{
    Dimension lengthMetric(value, static_cast<DimensionUnit>(originUnit));
    return lengthMetric.GetNativeValue(static_cast<DimensionUnit>(targetUnit));
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

void SetAttribute(ArkUINodeHandle node, ArkUI_CharPtr attribute, ArkUI_CharPtr value) {}

ArkUI_CharPtr GetAttribute(ArkUINodeHandle node, ArkUI_CharPtr attribute)
{
    return "";
}

void ResetAttribute(ArkUINodeHandle nodePtr, ArkUI_CharPtr attribute)
{
    TAG_LOGI(AceLogTag::ACE_NATIVE_NODE, "Reset attribute %{public}s", attribute);
}

typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);

typedef void (*ResetComponentAsyncEventHandler)(ArkUINodeHandle node);

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
    NodeModifier::SetOnHover,
    NodeModifier::SetOnBlur,
    NodeModifier::SetOnKeyEvent,
    NodeModifier::SetOnMouse,
    NodeModifier::SetOnAreaChange,
    nullptr,
    nullptr,
    NodeModifier::SetOnFocus,
    NodeModifier::SetOnTouchIntercept,
    NodeModifier::SetOnAttach,
    NodeModifier::SetOnDetach,
    NodeModifier::SetOnAccessibilityActions,
    NodeModifier::SetOnDragStart,
    NodeModifier::SetOnDragEnter,
    NodeModifier::SetOnDragDrop,
    NodeModifier::SetOnDragMove,
    NodeModifier::SetOnDragLeave,
    NodeModifier::SetOnDragEnd,
    NodeModifier::SetOnPreDrag,
    NodeModifier::SetOnKeyPreIme,
    NodeModifier::SetOnFocusAxisEvent,
    NodeModifier::SetOnKeyEventDispatch,
    nullptr,
    NodeModifier::SetOnAxisEvent,
    NodeModifier::SetOnClick,
    NodeModifier::SetOnHover,
    NodeModifier::SetOnHoverMove,
};

const ComponentAsyncEventHandler scrollNodeAsyncEventHandlers[] = {
    NodeModifier::SetOnScroll,
    NodeModifier::SetOnScrollFrameBegin,
    NodeModifier::SetScrollOnWillScroll,
    NodeModifier::SetScrollOnDidScroll,
    NodeModifier::SetOnScrollStart,
    NodeModifier::SetOnScrollStop,
    NodeModifier::SetOnScrollEdge,
    NodeModifier::SetOnScrollReachStart,
    NodeModifier::SetOnScrollReachEnd,
};

const ComponentAsyncEventHandler TEXT_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnDetectResultUpdate,
};

const ComponentAsyncEventHandler textInputNodeAsyncEventHandlers[] = {
    NodeModifier::SetOnTextInputEditChange,
    NodeModifier::SetTextInputOnSubmit,
    NodeModifier::SetOnTextInputChange,
    NodeModifier::SetOnTextInputCut,
    NodeModifier::SetOnTextInputPaste,
    NodeModifier::SetOnTextInputSelectionChange,
    NodeModifier::SetOnTextInputContentSizeChange,
    NodeModifier::SetOnTextInputInputFilterError,
    NodeModifier::SetTextInputOnTextContentScroll,
    NodeModifier::SetTextInputOnWillInsert,
    NodeModifier::SetTextInputOnDidInsert,
    NodeModifier::SetTextInputOnWillDelete,
    NodeModifier::SetTextInputOnDidDelete,
    NodeModifier::SetOnTextInputChangeWithPreviewText,
};

const ComponentAsyncEventHandler textAreaNodeAsyncEventHandlers[] = {
    NodeModifier::SetOnTextAreaEditChange,
    nullptr,
    NodeModifier::SetOnTextAreaChange,
    NodeModifier::SetOnTextAreaPaste,
    NodeModifier::SetOnTextAreaSelectionChange,
    NodeModifier::SetTextAreaOnSubmit,
    NodeModifier::SetOnTextAreaContentSizeChange,
    NodeModifier::SetOnTextAreaInputFilterError,
    NodeModifier::SetTextAreaOnTextContentScroll,
    NodeModifier::SetTextAreaOnWillInsertValue,
    NodeModifier::SetTextAreaOnDidInsertValue,
    NodeModifier::SetTextAreaOnWillDeleteValue,
    NodeModifier::SetTextAreaOnDidDeleteValue,
    NodeModifier::SetOnTextAreaChangeWithPreviewText,
};

const ComponentAsyncEventHandler refreshNodeAsyncEventHandlers[] = {
    NodeModifier::SetRefreshOnStateChange,
    NodeModifier::SetOnRefreshing,
    NodeModifier::SetRefreshOnOffsetChange,
    NodeModifier::SetRefreshChangeEvent,
};

const ComponentAsyncEventHandler TOGGLE_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnToggleChange,
};

const ComponentAsyncEventHandler imageNodeAsyncEventHandlers[] = {
    NodeModifier::SetImageOnComplete,
    NodeModifier::SetImageOnError,
    NodeModifier::SetImageOnSvgPlayFinish,
    NodeModifier::SetImageOnDownloadProgress,
};

const ComponentAsyncEventHandler IMAGE_SPAN_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetImageSpanOnCompleteEvent,
    NodeModifier::SetImageSpanOnErrorEvent,
};

const ComponentAsyncEventHandler DATE_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetDatePickerOnDateChange,
};

const ComponentAsyncEventHandler TIME_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetTimePickerOnChange,
};

const ComponentAsyncEventHandler TEXT_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetTextPickerOnChange,
    NodeModifier::SetTextPickerOnScrollStop,
};

#ifndef ARKUI_WEARABLE
const ComponentAsyncEventHandler CALENDAR_PICKER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetCalendarPickerOnChange,
};
#endif

const ComponentAsyncEventHandler CHECKBOX_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetCheckboxChange,
};

const ComponentAsyncEventHandler CHECKBOX_GROUP_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetCheckboxGroupChange,
};

const ComponentAsyncEventHandler SLIDER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetSliderChange,
};

const ComponentAsyncEventHandler SWIPER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetSwiperChange,
    NodeModifier::SetSwiperAnimationStart,
    NodeModifier::SetSwiperAnimationEnd,
    NodeModifier::SetSwiperGestureSwipe,
    NodeModifier::SetSwiperOnContentDidScroll,
    NodeModifier::SetSwiperSelected,
    NodeModifier::SetSwiperUnselected,
    NodeModifier::SetSwiperContentWillScroll,
};

const ComponentAsyncEventHandler CANVAS_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetCanvasOnReady,
};

const ComponentAsyncEventHandler listNodeAsyncEventHandlers[] = {
    NodeModifier::SetOnListScroll,
    NodeModifier::SetOnListScrollIndex,
    NodeModifier::SetOnListScrollStart,
    NodeModifier::SetOnListScrollStop,
    NodeModifier::SetOnListScrollFrameBegin,
    NodeModifier::SetOnListWillScroll,
    NodeModifier::SetOnListDidScroll,
    NodeModifier::SetOnListReachStart,
    NodeModifier::SetOnListReachEnd,
    NodeModifier::SetOnListScrollVisibleContentChange,
};

const ComponentAsyncEventHandler LIST_ITEM_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetListItemOnSelect,
};

#ifndef ARKUI_WEARABLE
const ComponentAsyncEventHandler WATER_FLOW_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnWillScroll,
    NodeModifier::SetOnWaterFlowReachEnd,
    NodeModifier::SetOnDidScroll,
    NodeModifier::SetOnWaterFlowScrollStart,
    NodeModifier::SetOnWaterFlowScrollStop,
    NodeModifier::SetOnWaterFlowScrollFrameBegin,
    NodeModifier::SetOnWaterFlowScrollIndex,
    NodeModifier::SetOnWaterFlowReachStart,
};
#endif

const ComponentAsyncEventHandler GRID_NODE_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
    nullptr,
    nullptr,
    NodeModifier::SetOnGridScrollIndex,
};

const ComponentAsyncEventHandler ALPHABET_INDEXER_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnIndexerSelected,
    NodeModifier::SetOnIndexerRequestPopupData,
    NodeModifier::SetOnIndexerPopupSelected,
    NodeModifier::SetIndexerChangeEvent,
    NodeModifier::SetIndexerCreatChangeEvent,
};

const ComponentAsyncEventHandler SEARCH_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnSearchSubmit,
    NodeModifier::SetOnSearchChange,
    NodeModifier::SetOnSearchCopy,
    NodeModifier::SetOnSearchCut,
    NodeModifier::SetOnSearchPaste,
};

const ComponentAsyncEventHandler RADIO_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnRadioChange,
};

#ifndef ARKUI_WEARABLE
const ComponentAsyncEventHandler SELECT_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetOnSelectSelect,
};
#endif

const ComponentAsyncEventHandler IMAGE_ANIMATOR_NODE_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::SetImageAnimatorOnStart,
    NodeModifier::SetImageAnimatorOnPause,
    NodeModifier::SetImageAnimatorOnRepeat,
    NodeModifier::SetImageAnimatorOnCancel,
    NodeModifier::SetImageAnimatorOnFinish,
};

const ResetComponentAsyncEventHandler COMMON_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetOnAppear,
    NodeModifier::ResetOnDisappear,
    NodeModifier::ResetOnTouch,
    NodeModifier::ResetOnClick,
    NodeModifier::ResetOnHover,
    NodeModifier::ResetOnBlur,
    NodeModifier::ResetOnKeyEvent,
    NodeModifier::ResetOnMouse,
    NodeModifier::ResetOnAreaChange,
    NodeModifier::ResetOnVisibleAreaChange,
    nullptr,
    NodeModifier::ResetOnFocus,
    NodeModifier::ResetOnTouchIntercept,
    NodeModifier::ResetOnAttach,
    NodeModifier::ResetOnDetach,
    nullptr,
    NodeModifier::ResetOnDragStart,
    NodeModifier::ResetOnDragEnter,
    NodeModifier::ResetOnDragDrop,
    NodeModifier::ResetOnDragMove,
    NodeModifier::ResetOnDragLeave,
    NodeModifier::ResetOnDragEnd,
    NodeModifier::ResetOnPreDrag,
    NodeModifier::ResetOnKeyPreIme,
    NodeModifier::ResetOnFocusAxisEvent,
    nullptr,
    nullptr,
    NodeModifier::ResetOnAxisEvent,
    nullptr,
    nullptr,
    NodeModifier::ResetOnHoverMove,
};

const ResetComponentAsyncEventHandler SCROLL_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetOnScroll,
    NodeModifier::ResetOnScrollFrameBegin,
    NodeModifier::ResetScrollOnWillScroll,
    NodeModifier::ResetScrollOnDidScroll,
    NodeModifier::ResetOnScrollStart,
    NodeModifier::ResetOnScrollStop,
    NodeModifier::ResetOnScrollEdge,
    NodeModifier::ResetOnScrollReachStart,
    NodeModifier::ResetOnScrollReachEnd,
};

const ResetComponentAsyncEventHandler TEXT_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetOnDetectResultUpdate,
};

const ResetComponentAsyncEventHandler TEXT_INPUT_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetOnTextInputEditChange,
    NodeModifier::ResetTextInputOnSubmit,
    NodeModifier::ResetOnTextInputChange,
    NodeModifier::ResetOnTextInputCut,
    NodeModifier::ResetOnTextInputPaste,
    NodeModifier::ResetOnTextInputSelectionChange,
    NodeModifier::ResetOnTextInputContentSizeChange,
    NodeModifier::ResetOnTextInputInputFilterError,
    NodeModifier::ResetTextInputOnTextContentScroll,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    NodeModifier::ResetOnTextInputChangeWithPreviewText,
};

const ResetComponentAsyncEventHandler TEXT_AREA_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetOnTextAreaEditChange,
    nullptr,
    NodeModifier::ResetOnTextAreaChange,
    NodeModifier::ResetOnTextAreaPaste,
    NodeModifier::ResetOnTextAreaSelectionChange,
    NodeModifier::ResetTextAreaOnSubmit,
    NodeModifier::ResetOnTextAreaContentSizeChange,
    NodeModifier::ResetOnTextAreaInputFilterError,
    NodeModifier::ResetTextAreaOnTextContentScroll,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    NodeModifier::ResetOnTextAreaChangeWithPreviewText,
};

const ResetComponentAsyncEventHandler REFRESH_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetRefreshOnStateChange,
    NodeModifier::ResetOnRefreshing,
    NodeModifier::ResetRefreshOnOffsetChange,
    NodeModifier::ResetRefreshChangeEvent,
};

const ResetComponentAsyncEventHandler TOGGLE_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetOnToggleChange,
};

const ResetComponentAsyncEventHandler IMAGE_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetImageOnComplete,
    NodeModifier::ResetImageOnError,
    NodeModifier::ResetImageOnSvgPlayFinish,
    NodeModifier::ResetImageOnDownloadProgress,
};

const ResetComponentAsyncEventHandler DATE_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler TIME_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler TEXT_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler CALENDAR_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler CHECKBOX_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler CHECKBOX_GROUP_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetCheckboxGroupChange,
};

const ResetComponentAsyncEventHandler SLIDER_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler SWIPER_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

const ResetComponentAsyncEventHandler CANVAS_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler LIST_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetOnListScroll,
    NodeModifier::ResetOnListScrollIndex,
    NodeModifier::ResetOnListScrollStart,
    NodeModifier::ResetOnListScrollStop,
    NodeModifier::ResetOnListScrollFrameBegin,
    NodeModifier::ResetOnListWillScroll,
    NodeModifier::ResetOnListDidScroll,
    NodeModifier::ResetOnListReachStart,
    NodeModifier::ResetOnListReachEnd,
    NodeModifier::ResetOnScrollVisibleContentChange,
};

const ResetComponentAsyncEventHandler LIST_ITEM_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetListItemOnSelect,
};

#ifndef ARKUI_WEARABLE
const ResetComponentAsyncEventHandler WATERFLOW_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetOnWillScroll,
    NodeModifier::ResetOnWaterFlowReachEnd,
    NodeModifier::ResetOnDidScroll,
    NodeModifier::ResetOnWaterFlowScrollStart,
    NodeModifier::ResetOnWaterFlowScrollStop,
    NodeModifier::ResetOnWaterFlowScrollFrameBegin,
    NodeModifier::ResetOnWaterFlowScrollIndex,
    NodeModifier::ResetOnWaterFlowReachStart,
};
#endif

const ResetComponentAsyncEventHandler GRID_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
    nullptr,
    nullptr,
    NodeModifier::ResetOnGridScrollIndex,
};

const ResetComponentAsyncEventHandler ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

const ResetComponentAsyncEventHandler SEARCH_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

const ResetComponentAsyncEventHandler RADIO_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler SELECT_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    nullptr,
};

const ResetComponentAsyncEventHandler IMAGE_ANIMATOR_NODE_RESET_ASYNC_EVENT_HANDLERS[] = {
    NodeModifier::ResetImageAnimatorOnStart,
    NodeModifier::ResetImageAnimatorOnPause,
    NodeModifier::ResetImageAnimatorOnRepeat,
    NodeModifier::ResetImageAnimatorOnCancel,
    NodeModifier::ResetImageAnimatorOnFinish,
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
        case ARKUI_IMAGE_SPAN: {
            if (subKind >= sizeof(IMAGE_SPAN_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = IMAGE_SPAN_NODE_ASYNC_EVENT_HANDLERS[subKind];
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
        case ARKUI_TEXT: {
            // text event type.
            if (subKind >= sizeof(TEXT_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TEXT_NODE_ASYNC_EVENT_HANDLERS[subKind];
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
#ifndef ARKUI_WEARABLE
            if (subKind >= sizeof(CALENDAR_PICKER_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CALENDAR_PICKER_NODE_ASYNC_EVENT_HANDLERS[subKind];
#endif
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
        case ARKUI_LIST_ITEM: {
            // list item event type.
            if (subKind >= sizeof(LIST_ITEM_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = LIST_ITEM_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
#ifndef ARKUI_WEARABLE
        case ARKUI_WATER_FLOW: {
            // swiper event type.
            if (subKind >= sizeof(WATER_FLOW_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = WATER_FLOW_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
#endif
        case ARKUI_GRID: {
            // grid event type.
            if (subKind >= sizeof(GRID_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = GRID_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_ALPHABET_INDEXER: {
            // alphabet indexer event type.
            if (subKind >= sizeof(ALPHABET_INDEXER_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = ALPHABET_INDEXER_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_SEARCH: {
            // search event type.
            if (subKind >= sizeof(SEARCH_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SEARCH_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_RADIO: {
            // search event type.
            if (subKind >= sizeof(RADIO_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = RADIO_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
#ifndef ARKUI_WEARABLE
        case ARKUI_SELECT: {
            // select event type.
            if (subKind >= sizeof(SELECT_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SELECT_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
#endif
        case ARKUI_IMAGE_ANIMATOR: {
            // imageAnimator event type.
            if (subKind >= sizeof(IMAGE_ANIMATOR_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = IMAGE_ANIMATOR_NODE_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_CHECK_BOX_GROUP: {
            if (subKind >= sizeof(CHECKBOX_GROUP_NODE_ASYNC_EVENT_HANDLERS) / sizeof(ComponentAsyncEventHandler)) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CHECKBOX_GROUP_NODE_ASYNC_EVENT_HANDLERS[subKind];
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

void NotifyResetComponentAsyncEvent(ArkUINodeHandle node, ArkUIEventSubKind kind)
{
    unsigned int subClassType = kind / ARKUI_MAX_EVENT_NUM;
    unsigned int subKind = kind % ARKUI_MAX_EVENT_NUM;
    ResetComponentAsyncEventHandler eventHandle = nullptr;
    switch (subClassType) {
        case 0: {
            // common event type.
            if (subKind >= sizeof(COMMON_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = COMMON_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_IMAGE: {
            if (subKind >= sizeof(IMAGE_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = IMAGE_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_SCROLL: {
            // scroll event type.
            if (subKind >= sizeof(SCROLL_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SCROLL_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_TEXT: {
            // text event type.
            if (subKind >= sizeof(TEXT_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TEXT_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_TEXT_INPUT: {
            // text input event type.
            if (subKind >=
                sizeof(TEXT_INPUT_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TEXT_INPUT_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_TEXTAREA: {
            // textarea event type.
            if (subKind >=
                sizeof(TEXT_AREA_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TEXT_AREA_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_REFRESH: {
            // refresh event type.
            if (subKind >= sizeof(REFRESH_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = REFRESH_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_TOGGLE: {
            // toggle event type.
            if (subKind >= sizeof(TOGGLE_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TOGGLE_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_DATE_PICKER: {
            // datepicker event type.
            if (subKind >=
                sizeof(DATE_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = DATE_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_TIME_PICKER: {
            // timepicker event type.
            if (subKind >=
                sizeof(TIME_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TIME_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_TEXT_PICKER: {
            if (subKind >=
                sizeof(TEXT_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = TEXT_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_CALENDAR_PICKER: {
            // calendar picker event type.
            if (subKind >= sizeof(CALENDAR_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(
                ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CALENDAR_PICKER_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_CHECKBOX: {
            // timepicker event type.
            if (subKind >= sizeof(CHECKBOX_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CHECKBOX_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_SLIDER: {
            // timepicker event type.
            if (subKind >= sizeof(SLIDER_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SLIDER_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_SWIPER: {
            // swiper event type.
            if (subKind >= sizeof(SWIPER_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SWIPER_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_CANVAS: {
            if (subKind >= sizeof(CANVAS_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CANVAS_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_LIST: {
            // list event type.
            if (subKind >= sizeof(LIST_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = LIST_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_LIST_ITEM: {
            // list item event type.
            if (subKind >=
                sizeof(LIST_ITEM_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = LIST_ITEM_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
#ifndef ARKUI_WEARABLE
        case ARKUI_WATER_FLOW: {
            // swiper event type.
            if (subKind >=
                sizeof(WATERFLOW_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = WATERFLOW_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
#endif
        case ARKUI_GRID: {
            // grid event type.
            if (subKind >= sizeof(GRID_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = GRID_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_ALPHABET_INDEXER: {
            // alphabet indexer event type.
            if (subKind >= sizeof(ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(
                ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = ALPHABET_INDEXER_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_SEARCH: {
            // search event type.
            if (subKind >= sizeof(SEARCH_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SEARCH_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_RADIO: {
            // search event type.
            if (subKind >= sizeof(RADIO_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = RADIO_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_SELECT: {
            // select event type.
            if (subKind >= sizeof(SELECT_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = SELECT_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_IMAGE_ANIMATOR: {
            // imageAnimator event type.
            if (subKind >=
                sizeof(IMAGE_ANIMATOR_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = IMAGE_ANIMATOR_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        case ARKUI_CHECK_BOX_GROUP: {
            if (subKind >=
                sizeof(CHECKBOX_GROUP_NODE_RESET_ASYNC_EVENT_HANDLERS) / sizeof(ResetComponentAsyncEventHandler)) {
                TAG_LOGE(
                    AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
                return;
            }
            eventHandle = CHECKBOX_GROUP_NODE_RESET_ASYNC_EVENT_HANDLERS[subKind];
            break;
        }
        default: {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d NOT IMPLEMENT", kind);
        }
    }
    if (eventHandle) {
        eventHandle(node);
    } else {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "NotifyResetComponentAsyncEvent kind:%{public}d EMPTY IMPLEMENT", kind);
    }
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

ArkUIPipelineContext GetPipelineContext(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    return reinterpret_cast<ArkUIPipelineContext>(frameNode->GetContext());
}

void SetVsyncCallback(ArkUIVMContext vmContext, ArkUIPipelineContext pipelineContext, ArkUI_Int32 callbackId)
{
    static int vsyncCount = 1;
    auto vsync = [vmContext, callbackId]() {
        ArkUIEventCallbackArg args[] = { {.i32 =vsyncCount++ } };
        ArkUIAPICallbackMethod* cbs = GetArkUIAPICallbackMethod();
        CHECK_NULL_VOID(vmContext);
        CHECK_NULL_VOID(cbs);
        cbs->CallInt(vmContext, callbackId, 1, &args[0]);
    };

    reinterpret_cast<PipelineContext*>(pipelineContext)->SetVsyncListener(vsync);
}

void UnblockVsyncWait(ArkUIVMContext vmContext, ArkUIPipelineContext pipelineContext)
{
    reinterpret_cast<PipelineContext*>(pipelineContext)->RequestFrame();
}

ArkUI_Int32 MeasureNode(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Float32* data)
{
    return ViewModel::MeasureNode(vmContext, node, data);
}

ArkUI_Int32 LayoutNode(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Float32 (*data)[2])
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
    float width = root->GetGeometryNode()->GetFrameSize().Width();
    float height = root->GetGeometryNode()->GetFrameSize().Height();
    // measure
    ArkUI_Float32 measureData[] = { width, height, width, height, width, height };
    MeasureNode(vmContext, rootPtr, &measureData[0]);
    // layout
    ArkUI_Float32 layoutData[] = { 0, 0 };
    LayoutNode(vmContext, rootPtr, &layoutData);
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
        companion->SetFlags(static_cast<uint32_t>(originEventType) | static_cast<uint32_t>(eventType));
        companion->SetExtraParam(eventType, extraParam);
    }
}

void RegisterCustomSpanAsyncEvent(ArkUINodeHandle node, int32_t eventType, void* extraParam)
{
    switch (eventType) {
        case ArkUIAPINodeFlags::CUSTOM_MEASURE:
            NodeModifier::SetCustomSpanOnMeasure(node, extraParam);
            break;
        case ArkUIAPINodeFlags::CUSTOM_DRAW:
            NodeModifier::SetCustomSpanOnDraw(node, extraParam);
            break;
        default:
            break;
    }
}

ArkUI_Int32 UnregisterCustomNodeEvent(ArkUINodeHandle node, ArkUI_Int32 eventType)
{
    auto companion = ViewModel::GetCompanion(node);
    CHECK_NULL_RETURN(companion, -1);
    auto originEventType = static_cast<uint32_t>(companion->GetFlags());
    //check is Contains
    if ((originEventType & static_cast<uint32_t>(eventType)) != static_cast<uint32_t>(eventType)) {
        return -1;
    }
    companion->SetFlags(static_cast<uint32_t>(originEventType) ^ static_cast<uint32_t>(eventType));
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



ArkUI_Int32 GetNavigationId(
    ArkUINodeHandle node, char* buffer, ArkUI_Int32 bufferSize, ArkUI_Int32* writeLen)
{
    auto navDesInfo = GetNavDestinationInfoByNode(node);
    CHECK_NULL_RETURN(navDesInfo, ERROR_CODE_NATIVE_IMPL_GET_INFO_FAILED);
    std::string navigationId = navDesInfo->navigationId;
    return WriteStringToBuffer(navigationId, buffer, bufferSize, writeLen);
}

ArkUI_Int32 GetNavDestinationName(
    ArkUINodeHandle node, char* buffer, ArkUI_Int32 bufferSize, ArkUI_Int32* writeLen)
{
    auto navDesInfo = GetNavDestinationInfoByNode(node);
    CHECK_NULL_RETURN(navDesInfo, ERROR_CODE_NATIVE_IMPL_GET_INFO_FAILED);
    std::string name = navDesInfo->name;
    return WriteStringToBuffer(name, buffer, bufferSize, writeLen);
}

ArkUI_Int32 GetStackLength(ArkUINodeHandle node)
{
    auto navigationStack = GetNavigationStackByNode(node);
    CHECK_NULL_RETURN(navigationStack, INVLID_VALUE);
    return navigationStack->Size();
}

ArkUI_Int32 GetNavDesNameByIndex(
    ArkUINodeHandle node, ArkUI_Int32 index, char* buffer, ArkUI_Int32 bufferSize, ArkUI_Int32* writeLen)
{
    auto navigationStack = GetNavigationStackByNode(node);
    CHECK_NULL_RETURN(navigationStack, ERROR_CODE_NATIVE_IMPL_GET_INFO_FAILED);
    if (index < 0 || index >= navigationStack->Size()) {
        return ERROR_CODE_NATIVE_IMPL_NODE_INDEX_INVALID;
    }

    std::string name = navigationStack->GetNavDesNameByIndex(index);
    return WriteStringToBuffer(name, buffer, bufferSize, writeLen);
}

ArkUI_Int32 GetNavDestinationId(
    ArkUINodeHandle node, char* buffer, ArkUI_Int32 bufferSize, ArkUI_Int32* writeLen)
{
    auto navDesInfo = GetNavDestinationInfoByNode(node);
    CHECK_NULL_RETURN(navDesInfo, ERROR_CODE_NATIVE_IMPL_GET_INFO_FAILED);
    std::string navDestinationId = navDesInfo->navDestinationId;
    return WriteStringToBuffer(navDestinationId, buffer, bufferSize, writeLen);
}

ArkUI_Int32 GetNavDestinationState(ArkUINodeHandle node)
{
    auto navDesInfo = GetNavDestinationInfoByNode(node);
    CHECK_NULL_RETURN(navDesInfo, INVLID_VALUE);
    return static_cast<int32_t>(navDesInfo->state);
}

ArkUI_Int32 GetNavDestinationIndex(ArkUINodeHandle node)
{
    auto navDesInfo = GetNavDestinationInfoByNode(node);
    CHECK_NULL_RETURN(navDesInfo, INVLID_VALUE);
    return navDesInfo->index;
}

void* GetNavDestinationParam(ArkUINodeHandle node)
{
    auto navDesInfo = GetNavDestinationInfoByNode(node);
    CHECK_NULL_RETURN(navDesInfo, nullptr);
    return reinterpret_cast<void*>(navDesInfo->param);
}

ArkUI_Int32 GetRouterPageIndex(ArkUINodeHandle node)
{
    auto routerInfo = GetRouterPageInfoByNode(node);
    CHECK_NULL_RETURN(routerInfo, INVLID_VALUE);
    return routerInfo->index;
}

ArkUI_Int32 GetRouterPageName(
    ArkUINodeHandle node, char* buffer, ArkUI_Int32 bufferSize, ArkUI_Int32* writeLen)
{
    auto routerInfo = GetRouterPageInfoByNode(node);
    CHECK_NULL_RETURN(routerInfo, ERROR_CODE_NATIVE_IMPL_GET_INFO_FAILED);
    std::string name = routerInfo->name;
    return WriteStringToBuffer(name, buffer, bufferSize, writeLen);
}

ArkUI_Int32 GetRouterPagePath(
    ArkUINodeHandle node, char* buffer, ArkUI_Int32 bufferSize, ArkUI_Int32* writeLen)
{
    auto routerInfo = GetRouterPageInfoByNode(node);
    CHECK_NULL_RETURN(routerInfo, ERROR_CODE_NATIVE_IMPL_GET_INFO_FAILED);
    std::string path = routerInfo->path;
    return WriteStringToBuffer(path, buffer, bufferSize, writeLen);
}

ArkUI_Int32 GetRouterPageState(ArkUINodeHandle node)
{
    auto routerInfo = GetRouterPageInfoByNode(node);
    CHECK_NULL_RETURN(routerInfo, INVLID_VALUE);
    return static_cast<int32_t>(routerInfo->state);
}

ArkUI_Int32 GetRouterPageId(
    ArkUINodeHandle node, char* buffer, ArkUI_Int32 bufferSize, ArkUI_Int32* writeLen)
{
    auto routerInfo = GetRouterPageInfoByNode(node);
    CHECK_NULL_RETURN(routerInfo, ERROR_CODE_NATIVE_IMPL_GET_INFO_FAILED);
    std::string pageId = routerInfo->pageId;
    return WriteStringToBuffer(pageId, buffer, bufferSize, writeLen);
}

int32_t GetContextByNode(ArkUINodeHandle node)
{
    int32_t instanceId = -1;
    FrameNode* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, instanceId);
    auto pipeline = currentNode->GetContext();
    CHECK_NULL_RETURN(pipeline, instanceId);
    instanceId = pipeline->GetInstanceId();
    return instanceId;
}

ArkUI_Int32 PostFrameCallback(ArkUI_Int32 instanceId, void* userData,
    void (*callback)(uint64_t nanoTimestamp, uint32_t frameCount, void* userData))
{
    auto pipeline = PipelineContext::GetContextByContainerId(instanceId);
    if (pipeline == nullptr) {
        LOGW("Cannot find pipeline context by contextHandle ID");
        return ARKUI_ERROR_CODE_UI_CONTEXT_INVALID;
    }
    if (!pipeline->CheckThreadSafe()) {
        return ERROR_CODE_NATIVE_IMPL_NOT_MAIN_THREAD;
    }
    auto onframeCallbackFuncFromCAPI = [userData, callback](uint64_t nanoTimestamp, uint32_t frameCount) -> void {
        callback(nanoTimestamp, frameCount, userData);
    };

    pipeline->AddCAPIFrameCallback(std::move(onframeCallbackFuncFromCAPI));
    return ERROR_CODE_NO_ERROR;
}

const ArkUIBasicAPI* GetBasicAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIBasicAPI basicImpl = {
        .createNode = CreateNode,
        .createNodeWithParams = CreateNodeWithParams,
        .getNodeByViewStack = GetNodeByViewStack,
        .disposeNode = DisposeNode,
        .getName = GetName,
        .dump = DumpTreeNode,
        .addChild = AddChild,
        .removeChild = RemoveChild,
        .insertChildAfter = InsertChildAfter,
        .insertChildBefore = InsertChildBefore,
        .insertChildAt = InsertChildAt,
        .getAttribute = GetAttribute,
        .setAttribute = SetAttribute,
        .resetAttribute = ResetAttribute,
        .registerNodeAsyncEvent = NotifyComponentAsyncEvent,
        .unRegisterNodeAsyncEvent = NotifyResetComponentAsyncEvent,
        .registerNodeAsyncEventReceiver = RegisterNodeAsyncEventReceiver,
        .unRegisterNodeAsyncEventReceiver = UnregisterNodeAsyncEventReceiver,
        .checkAsyncEvent = nullptr,
        .applyModifierFinish = ApplyModifierFinish,
        .markDirty = MarkDirty,
        .isBuilderNode = IsBuilderNode,
        .convertLengthMetricsUnit = ConvertLengthMetricsUnit,
        .getContextByNode = GetContextByNode,
        .postFrameCallback = PostFrameCallback,
    };
    CHECK_INITIALIZED_FIELDS_END(basicImpl, 0, 0, 0); // don't move this line
    return &basicImpl;
}

const CJUIBasicAPI* GetCJUIBasicAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIBasicAPI basicImpl = {
        .createNode = CreateNode,
        .disposeNode = DisposeNode,
        .getName = GetName,
        .dump = DumpTreeNode,
        .addChild = AddChild,
        .removeChild = RemoveChild,
        .insertChildAfter = InsertChildAfter,
        .insertChildBefore = InsertChildBefore,
        .insertChildAt = InsertChildAt,
        .getAttribute = GetAttribute,
        .setAttribute = SetAttribute,
        .resetAttribute = ResetAttribute,
        .registerNodeAsyncEvent = NotifyComponentAsyncEvent,
        .unRegisterNodeAsyncEvent = NotifyResetComponentAsyncEvent,
        .registerNodeAsyncEventReceiver = RegisterNodeAsyncEventReceiver,
        .unRegisterNodeAsyncEventReceiver = UnregisterNodeAsyncEventReceiver,
        .checkAsyncEvent = nullptr,
        .applyModifierFinish = ApplyModifierFinish,
        .markDirty = MarkDirty,
        .isBuilderNode = IsBuilderNode,
        .convertLengthMetricsUnit = ConvertLengthMetricsUnit,
        .getContextByNode = GetContextByNode,
    };
    CHECK_INITIALIZED_FIELDS_END(basicImpl, 0, 0, 0); // don't move this line
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

// Register closing event
ArkUI_Int32 RegisterOnWillDismissWithUserData(
    ArkUIDialogHandle handler, void* userData, void (*callback)(ArkUI_DialogDismissEvent* event))
{
    return CustomDialog::RegisterOnWillDialogDismissWithUserData(handler, userData, callback);
}

ArkUI_Int32 SetKeyboardAvoidDistance(ArkUIDialogHandle handle, float distance, ArkUI_Int32 unit)
{
    return CustomDialog::SetKeyboardAvoidDistance(handle, distance, unit);
}

ArkUI_Int32 SetDialogLevelMode(ArkUIDialogHandle handle, ArkUI_Int32 mode)
{
    return CustomDialog::SetLevelMode(handle, mode);
}

ArkUI_Int32 SetDialogLevelUniqueId(ArkUIDialogHandle handle, ArkUI_Int32 uniqueId)
{
    return CustomDialog::SetLevelUniqueId(handle, uniqueId);
}

ArkUI_Int32 SetDialogImmersiveMode(ArkUIDialogHandle handle, ArkUI_Int32 mode)
{
    return CustomDialog::SetImmersiveMode(handle, mode);
}

ArkUI_Int32 SetLevelOrder(ArkUIDialogHandle handle, ArkUI_Float64 levelOrder)
{
    return CustomDialog::SetLevelOrder(handle, levelOrder);
}

ArkUI_Int32 SetFocusable(ArkUIDialogHandle handle, ArkUI_Bool focusable)
{
    return CustomDialog::SetFocusable(handle, focusable);
}

ArkUI_Int32 RegisterOnWillAppear(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData))
{
    return CustomDialog::RegisterOnWillAppearDialog(handle, userData, callback);
}

ArkUI_Int32 RegisterOnDidAppear(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData))
{
    return CustomDialog::RegisterOnDidAppearDialog(handle, userData, callback);
}

ArkUI_Int32 RegisterOnWillDisappear(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData))
{
    return CustomDialog::RegisterOnWillDisappearDialog(handle, userData, callback);
}

ArkUI_Int32 RegisterOnDidDisappear(ArkUIDialogHandle handle, void* userData, void (*callback)(void* userData))
{
    return CustomDialog::RegisterOnDidDisappearDialog(handle, userData, callback);
}

ArkUI_Int32 OpenCustomDialog(ArkUIDialogHandle handle, void (*callback)(ArkUI_Int32 dialogId))
{
    return CustomDialog::OpenCustomDialog(handle, callback);
}

ArkUI_Int32 CloseCustomDialog(ArkUI_Int32 dialogId)
{
    return CustomDialog::CloseCustomDialog(dialogId);
}

const ArkUIDialogAPI* GetDialogAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDialogAPI dialogImpl = {
        .create = CreateDialog,
        .dispose = DisposeDialog,
        .setContent = SetDialogContent,
        .removeContent = RemoveDialogContent,
        .setContentAlignment = SetDialogContentAlignment,
        .resetContentAlignment = ResetDialogContentAlignment,
        .setModalMode = SetDialogModalMode,
        .setAutoCancel = SetDialogAutoCancel,
        .setMask = SetDialogMask,
        .setBackgroundColor = SetDialogBackgroundColor,
        .setCornerRadius = SetDialogCornerRadius,
        .setGridColumnCount = SetDialogGridColumnCount,
        .enableCustomStyle = EnableDialogCustomStyle,
        .enableCustomAnimation = EnableDialogCustomAnimation,
        .show = ShowDialog,
        .close = CloseDialog,
        .registerOnWillDismiss = RegisterOnWillDialogDismiss,
        .registerOnWillDismissWithUserData = RegisterOnWillDismissWithUserData,
        .setKeyboardAvoidDistance = SetKeyboardAvoidDistance,
        .setLevelMode = SetDialogLevelMode,
        .setLevelUniqueId = SetDialogLevelUniqueId,
        .setImmersiveMode = SetDialogImmersiveMode,
        .setLevelOrder = SetLevelOrder,
        .setFocusable = SetFocusable,
        .registerOnWillAppear = RegisterOnWillAppear,
        .registerOnDidAppear = RegisterOnDidAppear,
        .registerOnWillDisappear = RegisterOnWillDisappear,
        .registerOnDidDisappear = RegisterOnDidDisappear,
        .openCustomDialog = OpenCustomDialog,
        .closeCustomDialog = CloseCustomDialog,
    };
    CHECK_INITIALIZED_FIELDS_END(dialogImpl, 0, 0, 0); // don't move this line
    return &dialogImpl;
}

void ShowCrash(ArkUI_CharPtr message)
{
    TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "Arkoala crash: %{public}s", message);
}

/* clang-format off */
ArkUIExtendedNodeAPI impl_extended = {
    .version = ARKUI_EXTENDED_API_VERSION,
    .getUtilsModifier = NodeModifier::GetUtilsModifier, // getUtilsModifier
    .getCanvasRenderingContext2DModifier = NodeModifier::GetCanvasRenderingContext2DModifier,
    .setCallbackMethod = SetCallbackMethod,
    .setCustomMethodFlag = SetCustomMethodFlag,
    .getCustomMethodFlag = GetCustomMethodFlag,
    .registerCustomNodeAsyncEvent = RegisterCustomNodeAsyncEvent,
    .registerCustomSpanAsyncEvent = RegisterCustomSpanAsyncEvent,
    .unregisterCustomNodeAsyncEvent = UnregisterCustomNodeEvent,
    .registerCustomNodeAsyncEventReceiver = RegisterCustomNodeEventReceiver,
    .setCustomCallback = SetCustomCallback, // setCustomCallback
    .measureLayoutAndDraw = MeasureLayoutAndDraw,
    .measureNode = MeasureNode,
    .layoutNode = LayoutNode,
    .drawNode = DrawNode,
    .setAttachNodePtr = SetAttachNodePtr,
    .getAttachNodePtr = GetAttachNodePtr,
    .setMeasureWidth = SetMeasureWidth, // setMeasureWidth
    .getMeasureWidth = GetMeasureWidth, // getMeasureWidth
    .setMeasureHeight = SetMeasureHeight, // setMeasureHeight
    .getMeasureHeight = GetMeasureHeight, // getMeasureHeight
    .setX = SetX, // setX
    .setY = SetY, // setY
    .getX = GetX, // getX
    .getY = GetY, // getY
    .getLayoutConstraint = GetLayoutConstraint,
    .setAlignment = SetAlignment,
    .getAlignment = GetAlignment,
    .indexerChecker = nullptr, // indexerChecker
    .setRangeUpdater = nullptr, // setRangeUpdater
    .setLazyItemIndexer = nullptr, // setLazyItemIndexer
    .getPipelineContext = GetPipelineContext,
    .setVsyncCallback = SetVsyncCallback,
    .unblockVsyncWait = UnblockVsyncWait,
    .sendEvent = NodeEvent::SendArkUISyncEvent, // sendEvent
    .callContinuation = nullptr, // callContinuation
    .setChildTotalCount = nullptr, // setChildTotalCount
    .showCrash = ShowCrash,
    .getTopNodeFromViewStack = GetTopNodeByViewStack,
    .createCustomNode = CreateCustomNode,
    .getOrCreateCustomNode = GetOrCreateCustomNode,
    .getRSNodeByNode = GetRSNodeByNode,
    .isRightToLeft = IsRightToLeft,
    .createNewScope = CreateNewScope,
    .registerOEMVisualEffect = RegisterOEMVisualEffect,
    .setOnNodeDestroyCallback = SetOnNodeDestroyCallback,
};
/* clang-format on */

void CanvasDrawRect(ArkUICanvasHandle canvas, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right,
    ArkUI_Float32 bottom, ArkUIPaintHandle paint) {}

const ArkUIGraphicsCanvas* GetCanvasAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGraphicsCanvas modifier = {
        .finalize = nullptr,
        .drawPoint = nullptr,
        .drawPoints = nullptr,
        .drawLine = nullptr,
        .drawArc = nullptr,
        .drawRect = CanvasDrawRect,
        .drawOval = nullptr,
        .drawCircle = nullptr,
        .drawRRect = nullptr,
        .drawDRRect = nullptr,
        .drawString = nullptr,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
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
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGraphicsPaint modifier = {
        .make = PaintMake,
        .finalize = PaintFinalize,
        .setColor = nullptr,
        .getColor = nullptr,
        .setAlpha = nullptr,
        .getAlpha = nullptr
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIGraphicsFont* GetFontAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGraphicsFont modifier = {
        .makeDefault = nullptr,
        .finalize = nullptr,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIGraphicsAPI* GetGraphicsAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGraphicsAPI api = {
        .version = ARKUI_NODE_GRAPHICS_API_VERSION,
        .setCallbackMethod = SetCallbackMethod,
        .getCanvasAPI = GetCanvasAPI,
        .getPaintAPI = GetPaintAPI,
        .getFontAPI = GetFontAPI
    };
    CHECK_INITIALIZED_FIELDS_END(api, 0, 0, 0); // don't move this line
    return &api;
}

void AnimateTo(ArkUIContext* context, ArkUIAnimateOption option, void* event, void* user)
{
    ViewAnimate::AnimateTo(context, option, reinterpret_cast<void (*)(void*)>(event), user);
}

void KeyframeAnimateTo(ArkUIContext* context, ArkUIKeyframeAnimateOption* animateOption)
{
    ViewAnimate::KeyframeAnimateTo(context, animateOption);
}

ArkUIAnimatorHandle CreateAnimator(ArkUIContext* context, ArkUIAnimatorOption* animateOption)
{
    return ViewAnimate::CreateAnimator(context, animateOption);
}

void DisposeAnimator(ArkUIAnimatorHandle animator)
{
    ViewAnimate::DisposeAnimator(animator);
}

ArkUI_Int32 AnimatorReset(ArkUIAnimatorHandle animator, ArkUIAnimatorOption* option)
{
    return ViewAnimate::AnimatorReset(animator, option);
}

ArkUI_Int32 AnimatorPlay(ArkUIAnimatorHandle animator)
{
    return ViewAnimate::AnimatorPlay(animator);
}

ArkUI_Int32 AnimatorFinish(ArkUIAnimatorHandle animator)
{
    return ViewAnimate::AnimatorFinish(animator);
}

ArkUI_Int32 AnimatorPause(ArkUIAnimatorHandle animator)
{
    return ViewAnimate::AnimatorPause(animator);
}

ArkUI_Int32 AnimatorCancel(ArkUIAnimatorHandle animator)
{
    return ViewAnimate::AnimatorCancel(animator);
}

ArkUI_Int32 AnimatorReverse(ArkUIAnimatorHandle animator)
{
    return ViewAnimate::AnimatorReverse(animator);
}

ArkUICurveHandle CreateCurve(ArkUI_Int32 curve)
{
    return ViewAnimate::CreateCurve(curve);
}

ArkUICurveHandle CreateStepsCurve(ArkUI_Int32 count, ArkUI_Bool end)
{
    return ViewAnimate::CreateStepsCurve(count, end);
}

ArkUICurveHandle CreateCubicBezierCurve(ArkUI_Float32 x1, ArkUI_Float32 y1, ArkUI_Float32 x2, ArkUI_Float32 y2)
{
    return ViewAnimate::CreateCubicBezierCurve(x1, y1, x2, y2);
}

ArkUICurveHandle CreateSpringCurve(
    ArkUI_Float32 velocity, ArkUI_Float32 mass, ArkUI_Float32 stiffness, ArkUI_Float32 damping)
{
    return ViewAnimate::CreateSpringCurve(velocity, mass, stiffness, damping);
}

ArkUICurveHandle CreateSpringMotion(
    ArkUI_Float32 response, ArkUI_Float32 dampingFraction, ArkUI_Float32 overlapDuration)
{
    return ViewAnimate::CreateSpringMotion(response, dampingFraction, overlapDuration);
}

ArkUICurveHandle CreateResponsiveSpringMotion(
    ArkUI_Float32 response, ArkUI_Float32 dampingFraction, ArkUI_Float32 overlapDuration)
{
    return ViewAnimate::CreateResponsiveSpringMotion(response, dampingFraction, overlapDuration);
}

ArkUICurveHandle CreateInterpolatingSpring(
    ArkUI_Float32 velocity, ArkUI_Float32 mass, ArkUI_Float32 stiffness, ArkUI_Float32 damping)
{
    return ViewAnimate::CreateInterpolatingSpring(velocity, mass, stiffness, damping);
}

ArkUICurveHandle CreateCustomCurve(ArkUI_Float32 (*interpolate)(ArkUI_Float32 fraction, void* userData), void* userData)
{
    return ViewAnimate::CreateCustomCurve(interpolate, userData);
}

void DisposeCurve(ArkUICurveHandle curve)
{
    return ViewAnimate::DisposeCurve(curve);
}

const ArkUIAnimation* GetAnimationAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIAnimation modifier = {
        .startAnimation = nullptr,
        .openImplicitAnimation = nullptr,
        .closeImplicitAnimation = nullptr,
        .animateTo = AnimateTo,
        .keyframeAnimateTo = KeyframeAnimateTo,
        .createAnimator = CreateAnimator,
        .disposeAnimator = DisposeAnimator,
        .animatorReset = AnimatorReset,
        .animatorPlay = AnimatorPlay,
        .animatorFinish = AnimatorFinish,
        .animatorPause = AnimatorPause,
        .animatorCancel = AnimatorCancel,
        .animatorReverse = AnimatorReverse,
        .initCurve = CreateCurve,
        .stepsCurve = CreateStepsCurve,
        .cubicBezierCurve = CreateCubicBezierCurve,
        .springCurve = CreateSpringCurve,
        .springMotion = CreateSpringMotion,
        .responsiveSpringMotion = CreateResponsiveSpringMotion,
        .interpolatingSpring = CreateInterpolatingSpring,
        .customCurve = CreateCustomCurve,
        .disposeCurve = DisposeCurve,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUINavigation* GetNavigationAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUINavigation modifier = {
        .popPageToIndex = nullptr,
        .setNavDestinationBackPressed = nullptr,
        .getNavigationId = GetNavigationId,
        .getNavDestinationName = GetNavDestinationName,
        .getStackLength = GetStackLength,
        .getNavDesNameByIndex = GetNavDesNameByIndex,
        .getNavDestinationId = GetNavDestinationId,
        .getNavDestinationState = GetNavDestinationState,
        .getNavDestinationIndex = GetNavDestinationIndex,
        .getNavDestinationParam = GetNavDestinationParam,
        .getRouterPageIndex = GetRouterPageIndex,
        .getRouterPageName = GetRouterPageName,
        .getRouterPagePath = GetRouterPagePath,
        .getRouterPageState = GetRouterPageState,
        .getRouterPageId = GetRouterPageId,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIExtendedNodeAPI* GetExtendedAPI()
{
    return &impl_extended;
}

ArkUI_StyledString_Descriptor* CreateArkUIStyledStringDescriptor()
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ArkUI_StyledString_Descriptor create");
    return new ArkUI_StyledString_Descriptor;
}

void DestroyArkUIStyledStringDescriptor(ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ArkUI_StyledString_Descriptor destroy");
    CHECK_NULL_VOID(descriptor);
    if (descriptor->html) {
        delete descriptor->html;
        descriptor->html = nullptr;
    }
    if (descriptor->spanString) {
        auto* spanString = reinterpret_cast<SpanString*>(descriptor->spanString);
        delete spanString;
        descriptor->spanString = nullptr;
    }
    delete descriptor;
    descriptor = nullptr;
}

ArkUI_Int32 UnmarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "UnmarshallStyledStringDescriptor");
    CHECK_NULL_RETURN(buffer && descriptor && bufferSize > 0, ARKUI_ERROR_CODE_PARAM_INVALID);
    std::vector<uint8_t> vec(buffer, buffer + bufferSize);
    SpanString* spanString = new SpanString(u"");
    std::function<RefPtr<ExtSpan>(const std::vector<uint8_t>&, int32_t, int32_t)> unmarshallCallback;
    spanString->DecodeTlvExt(vec, spanString, std::move(unmarshallCallback));
    descriptor->spanString = reinterpret_cast<void*>(spanString);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 MarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor, size_t* resultSize)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "MarshallStyledStringDescriptor");
    CHECK_NULL_RETURN(buffer && resultSize && descriptor, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(descriptor->spanString, ARKUI_ERROR_CODE_INVALID_STYLED_STRING);
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    std::vector<uint8_t> tlvData;
    spanStringRawPtr->EncodeTlv(tlvData);
    *resultSize = tlvData.size();
    if (bufferSize < *resultSize) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    auto data = tlvData.data();
    std::copy(data, data + *resultSize, buffer);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

const char* ConvertToHtml(ArkUI_StyledString_Descriptor* descriptor)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE, "ConvertToHtml");
    CHECK_NULL_RETURN(descriptor && descriptor->spanString, "");
    auto spanStringRawPtr = reinterpret_cast<SpanString*>(descriptor->spanString);
    auto htmlStr = HtmlUtils::ToHtml(spanStringRawPtr);
    char* html = new char[htmlStr.length() + 1];
    CHECK_NULL_RETURN(html, "");
    std::copy(htmlStr.begin(), htmlStr.end(), html);
    html[htmlStr.length()] = '\0';
    descriptor->html = html;
    return descriptor->html;
}

const ArkUIStyledStringAPI* GetStyledStringAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIStyledStringAPI impl {
        .createArkUIStyledStringDescriptor = CreateArkUIStyledStringDescriptor,
        .destroyArkUIStyledStringDescriptor = DestroyArkUIStyledStringDescriptor,
        .unmarshallStyledStringDescriptor = UnmarshallStyledStringDescriptor,
        .marshallStyledStringDescriptor = MarshallStyledStringDescriptor,
        .convertToHtml = ConvertToHtml
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}

ArkUISnapshotOptions* CreateSnapshotOptions()
{
    ArkUISnapshotOptions* snapshotOptions = new ArkUISnapshotOptions();
    snapshotOptions->scale = 1.0f;
    return snapshotOptions;
}

void DestroySnapshotOptions(ArkUISnapshotOptions* snapshotOptions)
{
    if (snapshotOptions != nullptr) {
        delete snapshotOptions;
        snapshotOptions = nullptr;
    }
}

ArkUI_Int32 SnapshotOptionsSetScale(ArkUISnapshotOptions* snapshotOptions, ArkUI_Float32 scale)
{
    if (snapshotOptions == nullptr || !OHOS::Ace::GreatNotEqual(scale, 0.0)) {
        return ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    snapshotOptions->scale = scale;
    return ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetNodeSnapshot(ArkUINodeHandle node, ArkUISnapshotOptions* snapshotOptions, void* mediaPixel)
{
    auto frameNode =
        OHOS::Ace::AceType::Claim<OHOS::Ace::NG::FrameNode>(reinterpret_cast<OHOS::Ace::NG::FrameNode*>(node));
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    NG::SnapshotOptions options;
    options.scale = snapshotOptions != nullptr ? snapshotOptions->scale : 1.0f;
    options.waitUntilRenderFinished = true;
    auto result = delegate->GetSyncSnapshot(frameNode, options);
    *reinterpret_cast<std::shared_ptr<Media::PixelMap>*>(mediaPixel) = result.second;
    return result.first;
}

const ArkUISnapshotAPI* GetComponentSnapshotAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISnapshotAPI impl {
        .createSnapshotOptions = CreateSnapshotOptions,
        .destroySnapshotOptions = DestroySnapshotOptions,
        .snapshotOptionsSetScale = SnapshotOptionsSetScale,
        .getSyncSnapshot = GetNodeSnapshot
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}

/* clang-format off */
ArkUIFullNodeAPI impl_full = {
    .version = ARKUI_NODE_API_VERSION,
    .setCallbackMethod = SetCallbackMethod,      // CallbackMethod
    .getBasicAPI = GetBasicAPI,            // BasicAPI
    .getNodeModifiers = GetArkUINodeModifiers,  // NodeModifiers
    .getAnimation = GetAnimationAPI,        // Animation
    .getNavigation = GetNavigationAPI,       // Navigation
    .getGraphicsAPI = GetGraphicsAPI,         // Graphics
    .getDialogAPI = GetDialogAPI,
    .getExtendedAPI = GetExtendedAPI,         // Extended
    .getNodeAdapterAPI = NodeAdapter::GetNodeAdapterAPI,         // adapter.
    .getDragAdapterAPI = DragAdapter::GetDragAdapterAPI,        // drag adapter.
    .getStyledStringAPI = GetStyledStringAPI,     // StyledStringAPI
    .getSnapshotAPI = GetComponentSnapshotAPI,     // SyncSnapshot
};
/* clang-format on */

const CJUIAnimation* GetCJUIAnimationAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIAnimation modifier = {
        .startAnimation = nullptr,
        .openImplicitAnimation = nullptr,
        .closeImplicitAnimation = nullptr,
        .animateTo = AnimateTo,
        .keyframeAnimateTo = KeyframeAnimateTo,
        .createAnimator = CreateAnimator,
        .disposeAnimator = DisposeAnimator,
        .animatorReset = AnimatorReset,
        .animatorPlay = AnimatorPlay,
        .animatorFinish = AnimatorFinish,
        .animatorPause = AnimatorPause,
        .animatorCancel = AnimatorCancel,
        .animatorReverse = AnimatorReverse,
        .initCurve = CreateCurve,
        .stepsCurve = CreateStepsCurve,
        .cubicBezierCurve = CreateCubicBezierCurve,
        .springCurve = CreateSpringCurve,
        .springMotion = CreateSpringMotion,
        .responsiveSpringMotion = CreateResponsiveSpringMotion,
        .interpolatingSpring = CreateInterpolatingSpring,
        .customCurve = CreateCustomCurve,
        .disposeCurve = DisposeCurve,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUINavigation* GetCJUINavigationAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUINavigation modifier = {
        .popPageToIndex = nullptr,
        .setNavDestinationBackPressed = nullptr,
        .getNavigationId = GetNavigationId,
        .getNavDestinationName = GetNavDestinationName,
        .getStackLength = GetStackLength,
        .getNavDesNameByIndex = GetNavDesNameByIndex,
        .getNavDestinationId = GetNavDestinationId,
        .getNavDestinationState = GetNavDestinationState,
        .getNavDestinationIndex =GetNavDestinationIndex,
        .getNavDestinationParam = GetNavDestinationParam,
        .getRouterPageIndex = GetRouterPageIndex,
        .getRouterPageName = GetRouterPageName,
        .getRouterPagePath = GetRouterPagePath,
        .getRouterPageState = GetRouterPageState,
        .getRouterPageId = GetRouterPageId,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIGraphicsAPI* GetCJUIGraphicsAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIGraphicsAPI api = {
        .version = ARKUI_NODE_GRAPHICS_API_VERSION,
        .setCallbackMethod = SetCallbackMethod,
        .getCanvasAPI = GetCanvasAPI,
        .getPaintAPI = GetPaintAPI,
        .getFontAPI = GetFontAPI
    };
    CHECK_INITIALIZED_FIELDS_END(api, 0, 0, 0); // don't move this line
    return &api;
}

const CJUIDialogAPI* GetCJUIDialogAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIDialogAPI dialogImpl = {
        .create = CreateDialog,
        .dispose = DisposeDialog,
        .setContent = SetDialogContent,
        .removeContent = RemoveDialogContent,
        .setContentAlignment = SetDialogContentAlignment,
        .resetContentAlignment = ResetDialogContentAlignment,
        .setModalMode = SetDialogModalMode,
        .setAutoCancel = SetDialogAutoCancel,
        .setMask = SetDialogMask,
        .setBackgroundColor = SetDialogBackgroundColor,
        .setCornerRadius = SetDialogCornerRadius,
        .setGridColumnCount = SetDialogGridColumnCount,
        .enableCustomStyle = EnableDialogCustomStyle,
        .enableCustomAnimation = EnableDialogCustomAnimation,
        .show = ShowDialog,
        .close = CloseDialog,
        .registerOnWillDismiss = RegisterOnWillDialogDismiss,
    };
    CHECK_INITIALIZED_FIELDS_END(dialogImpl, 0, 0, 0); // don't move this line
    return &dialogImpl;
}

const CJUIExtendedNodeAPI* GetCJUIExtendedAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static CJUIExtendedNodeAPI impl_extended = {
        .version = ARKUI_EXTENDED_API_VERSION,
        .getUtilsModifier = NodeModifier::GetUtilsModifier,
        .getCanvasRenderingContext2DModifier = NodeModifier::GetCanvasRenderingContext2DModifier,
        .setCallbackMethod = SetCallbackMethod,
        .setCustomMethodFlag = SetCustomMethodFlag,
        .getCustomMethodFlag = GetCustomMethodFlag,
        .registerCustomNodeAsyncEvent = RegisterCustomNodeAsyncEvent,
        .unregisterCustomNodeAsyncEvent = UnregisterCustomNodeEvent,
        .registerCustomNodeAsyncEventReceiver = RegisterCustomNodeEventReceiver,
        .setCustomCallback = SetCustomCallback, // setCustomCallback
        .measureLayoutAndDraw = MeasureLayoutAndDraw,
        .measureNode = MeasureNode,
        .layoutNode = LayoutNode,
        .drawNode = DrawNode,
        .setAttachNodePtr = SetAttachNodePtr,
        .getAttachNodePtr = GetAttachNodePtr,
        .setMeasureWidth = SetMeasureWidth, // setMeasureWidth
        .getMeasureWidth = GetMeasureWidth, // getMeasureWidth
        .setMeasureHeight = SetMeasureHeight, // setMeasureHeight
        .getMeasureHeight = GetMeasureHeight, // getMeasureHeight
        .setX = SetX, // setX
        .setY = SetY, // setY
        .getX = GetX, // getX
        .getY = GetY, // getY
        .getLayoutConstraint = GetLayoutConstraint,
        .setAlignment = SetAlignment,
        .getAlignment = GetAlignment,
        .indexerChecker = nullptr, // indexerChecker
        .setRangeUpdater = nullptr, // setRangeUpdater
        .setLazyItemIndexer = nullptr, // setLazyItemIndexer
        .getPipelineContext = GetPipelineContext,
        .setVsyncCallback = SetVsyncCallback,
        .unblockVsyncWait = UnblockVsyncWait,
        .sendEvent = NodeEvent::SendArkUISyncEvent,
        .callContinuation = nullptr, // callContinuation
        .setChildTotalCount = nullptr, // setChildTotalCount
        .showCrash = ShowCrash,
    };
    CHECK_INITIALIZED_FIELDS_END(impl_extended, 0, 0, 0); // don't move this line
    return &impl_extended;
}

CJUIFullNodeAPI fullCJUIApi {
    .setCallbackMethod = SetCallbackMethod,
    .getBasicAPI = GetCJUIBasicAPI,            // BasicAPI
    .getNodeModifiers = GetCJUINodeModifiers,       // NodeModifiers
    .getAnimation = GetCJUIAnimationAPI,        // Animation
    .getNavigation = GetCJUINavigationAPI,       // Navigation
    .getGraphicsAPI = GetCJUIGraphicsAPI,         // Graphics
    .getDialogAPI = GetCJUIDialogAPI,
    .getExtendedAPI = GetCJUIExtendedAPI,         // Extended
    .getNodeAdapterAPI = NodeAdapter::GetCJUINodeAdapterAPI,         // adapter.
};
} // namespace

} // namespace OHOS::Ace::NG

extern "C" {

ACE_FORCE_EXPORT CJUIFullNodeAPI* GetCJUIFullNodeAPI()
{
    return &OHOS::Ace::NG::fullCJUIApi;
}

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

void SendArkUISyncEvent(ArkUINodeEvent* event)
{
    OHOS::Ace::NG::NodeEvent::SendArkUISyncEvent(event);
}

void SendArkUIAsyncCustomEvent(ArkUICustomNodeEvent* event)
{
    OHOS::Ace::NG::CustomNodeEvent::SendArkUISyncEvent(event);
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
    if (snprintf_s(entryPointString, sizeof entryPointString, sizeof entryPointString - 1,
        "__LIBACE_ENTRY_POINT=%llx", static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(&GetArkUIAPI))) < 0) {
        return;
    }
    putenv(entryPointString);
#else
    char entryPointString[64];
    if (snprintf_s(entryPointString, sizeof entryPointString, sizeof entryPointString - 1,
        "%llx", static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(&GetArkUIAPI))) < 0) {
        return;
    }
    setenv("__LIBACE_ENTRY_POINT", entryPointString, 1);
#endif
}
}
