/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <array>

#include "ani.h"
#include "animation/animation_ani_impl.h"
#include "canvas/canvas_module.h"
#include "common/common_module.h"
#include "componentSnapshot/componentSnapshot_module.h"
#include "content_slot/content_slot_module.h"
#include "custom_node/custom_node_module.h"
#include "lazy_for_each_module.h"
#include "drag_and_drop/native_drag_drop_global.h"
#include "dragController/drag_controller_module.h"
#include "styled_string/styled_string_module.h"
#include "image_span/image_span_module.h"
#include "image/image_module.h"
#include "list/list_children_main_size_module.h"
#include "load.h"
#include "log/log.h"
#include "utils/convert_utils.h"
#include "water_flow/waterFlowSection_module.h"
#include "interop/interop_module.h"
#include "web/web_module_methods.h"
#include "video/video_module_methods.h"
#include "rich_editor/rich_editor_module.h"
#include "stateMgmt/stateMgmt_module.h"
#include "shape/shape_module_methods.h"
#include "xcomponent/xcomponent_module_methods.h"
#include "condition_scope/condition_scope.h"
#include "utils/ani_trace.h"

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_class cls;
    auto ani_status = env->FindClass("Larkui/ani/arkts/ArkUIAniModule/ArkUIAniModule;", &cls);
    if (ani_status != ANI_OK) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {
            "_Image_ResizableOptions",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ImageResizableOptions)
        },
        ani_native_function {
            "_Image_Consturct_PixelMap",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ImageConstructPixelMap)
        },
        ani_native_function {
            "_Image_Consturct_DrawableDescriptor",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ImageConstructDrawableDescriptor)
        },
        ani_native_function {
            "_Image_DrawingColorFilter",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ImageDrawingColorFilter)
        },
        ani_native_function {
            "_Web_SetWebOptions",
            "JL@ohos/web/webview/webview/WebviewController;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWebOptions)
        },
        ani_native_function {
            "_Web_SetWebController_ControllerHandler",
            "JL@ohos/web/webview/webview/WebviewController;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWebControllerControllerHandler)
        },
        ani_native_function {
            "_TransferScreenCaptureHandlerToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferScreenCaptureHandlerToStatic)
        },
        ani_native_function {
            "_TransferJsGeolocationToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferJsGeolocationToStatic)
        },
        ani_native_function {
            "_TransferJsResultToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferJsResultToStatic)
        },
        ani_native_function {
            "_TransferEventResultToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferEventResultToStatic)
        },
        ani_native_function {
            "_TransferFileSelectorResultToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferFileSelectorResultToStatic)
        },
        ani_native_function {
            "_TransferFileSelectorParamToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferFileSelectorParamToStatic)
        },
        ani_native_function {
            "_TransferWebContextMenuResultToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebContextMenuResultToStatic)
        },
        ani_native_function {
            "_TransferWebContextMenuParamToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebContextMenuParamToStatic)
        },
        ani_native_function {
            "_TransferHttpAuthHandlerToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferHttpAuthHandlerToStatic)
        },
        ani_native_function {
            "_TransferWebResourceReponseToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebResourceReponseToStatic)
        },
        ani_native_function {
            "_TransferWebResourceRequestToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebResourceRequestToStatic)
        },
        ani_native_function {
            "_TransferConsoleMessageToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferConsoleMessageToStatic)
        },
        ani_native_function {
            "_TransferDataResubmissionHandlerToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferDataResubmissionHandlerToStatic)
        },
        ani_native_function {
            "_TransferClientAuthenticationHandlerToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferClientAuthenticationHandlerToStatic)
        },
        ani_native_function {
            "_TransferSslErrorHandlerToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferSslErrorHandlerToStatic)
        },
        ani_native_function {
            "_TransferScreenCaptureHandlerToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferScreenCaptureHandlerToDynamic)
        },
        ani_native_function {
            "_TransferJsGeolocationToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferJsGeolocationToDynamic)
        },
        ani_native_function {
            "_TransferJsResultToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferJsResultToDynamic)
        },
        ani_native_function {
            "_TransferEventResultToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferEventResultToDynamic)
        },
        ani_native_function {
            "_TransferFileSelectorResultToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferFileSelectorResultToDynamic)
        },
        ani_native_function {
            "_TransferFileSelectorParamToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferFileSelectorParamToDynamic)
        },
        ani_native_function {
            "_TransferWebContextMenuResultToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebContextMenuResultToDynamic)
        },
        ani_native_function {
            "_TransferWebContextMenuParamToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebContextMenuParamToDynamic)
        },
        ani_native_function {
            "_TransferHttpAuthHandlerToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferHttpAuthHandlerToDynamic)
        },
        ani_native_function {
            "_TransferWebResourceReponseToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebResourceReponseToDynamic)
        },
        ani_native_function {
            "_TransferWebResourceRequestToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebResourceRequestToDynamic)
        },
        ani_native_function {
            "_TransferConsoleMessageToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferConsoleMessageToDynamic)
        },
        ani_native_function {
            "_TransferDataResubmissionHandlerToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferDataResubmissionHandlerToDynamic)
        },
        ani_native_function {
            "_TransferClientAuthenticationHandlerToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferClientAuthenticationHandlerToDynamic)
        },
        ani_native_function {
            "_TransferSslErrorHandlerToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferSslErrorHandlerToDynamic)
        },
        ani_native_function {
            "_TransferPermissionRequestToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferPermissionRequestToStatic)
        },
        ani_native_function {
            "_TransferControllerHandlerToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferControllerHandlerToStatic)
        },
        ani_native_function {
            "_TransferWebKeyboardControllerToStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebKeyboardControllerToStatic)
        },
        ani_native_function {
            "_TransferPermissionRequestToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferPermissionRequestToDynamic)
        },
        ani_native_function {
            "_TransferControllerHandlerToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferControllerHandlerToDynamic)
        },
        ani_native_function {
            "_TransferWebKeyboardControllerToDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferWebKeyboardControllerToDynamic)
        },
        ani_native_function {
            "_ConvertUtils_ConvertFromPixelMapAni",
            "L@ohos/multimedia/image/image/PixelMap;:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConvertFromPixelMapAni)
        },
        ani_native_function {
            "_CustomNode_QueryNavigationInfo",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryNavigationInfo)
        },
        ani_native_function {
            "_CustomNode_QueryNavDestinationInfo",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryNavDestinationInfo)
        },
        ani_native_function {
            "_CustomNode_QueryNavDestinationInfo0",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryNavDestinationInfo0)
        },
        ani_native_function {
            "_CustomNode_QueryRouterPageInfo",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryRouterPageInfo)
        },
        ani_native_function {
            "_ConvertUtils_ConvertToPixelMapAni",
            "J:L@ohos/multimedia/image/image/PixelMap;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConvertToPixelMapAni)
        },
        ani_native_function {
            "_Common_GetHostContext",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetHostContext)
        },
        ani_native_function {
            "_Common_Sync_InstanceId",
            "I:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SyncInstanceId)
        },
        ani_native_function {
            "_Common_Restore_InstanceId",
            ":V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RestoreInstanceId)
        },
        ani_native_function {
            "_Common_Get_Current_InstanceId",
            ":I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetCurrentInstanceId)
        },
        ani_native_function {
            "_Common_GetFocused_InstanceId",
            ":I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetFocusedInstanceId)
        },
        ani_native_function {
            "_CustomNode_Construct",
            "ILarkui/ArkCustomComponent/ArkCustomComponent;:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructCustomNode)
        },
        ani_native_function {
            "_CustomNode_RequestFrame",
            ":V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RequestFrame)
        },
        ani_native_function {
            "_LazyForEachNode_Construct",
            "I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructLazyForEachNode)
        },
        ani_native_function {
            "_BuilderProxyNode_Construct",
            "I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::BuilderProxyNodeConstruct)
        },
        ani_native_function {
            "_ContentSlot_construct",
            "I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ContentSlotConstruct)
        },
        ani_native_function {
            "_ContentSlotInterface_setContentSlotOptions",
            "JJ:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetContentSlotOptions)
        },
        ani_native_function {
            "_SetDrawCallback",
            "JLstd/core/Function1;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawCallback)
        },
        ani_native_function {
            "_SetDrawModifier",
            "JILarkui/component/common/DrawModifier;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawModifier)
        },
        ani_native_function {
            "_Invalidate",
            "J:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Invalidate)
        },
        ani_native_function {
            "_SetOverlay_ComponentContent",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetOverlayComponentContent)
        },
        ani_native_function {
            "_SetWaterFlowOptions",
            "JLarkui/component/waterFlow/WaterFlowOptions;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowOptions)
        },
        ani_native_function {
            "_SetListChildrenMainSize",
            "JLarkui/component/common/ChildrenMainSize;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetListChildrenMainSize)
        },
        ani_native_function {
            "_DragEvent_Set_Data",
            "JL@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetData)
        },
        ani_native_function {
            "_DragEvent_Get_Data",
            "J:L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventGetData)
        },
        ani_native_function {
            "_DragEvent_Get_Summary",
            "J:L@ohos/data/unifiedDataChannel/unifiedDataChannel/Summary;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventGetSummary)
        },
        ani_native_function {
            "_DragEvent_Start_Data_Loading",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEveStartDataLoading)
        },
        ani_native_function {
            "_DragEvent_Set_PixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetPixelMap)
        },
        ani_native_function {
            "_DragEvent_Set_ExtraInfo",
            "JLstd/core/String;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetExtraInfo)
        },
        ani_native_function {
            "_DragEvent_Set_CustomNode",
            "JJ:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetCustomNode)
        },
        ani_native_function {
            "_Drag_Set_AllowDrop_Null",
            "J:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragSetAllowDropNull)
        },
        ani_native_function {
            "_Drag_Set_AllowDrop",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragSetAllowDrop)
        },
        ani_native_function {
            "_Drag_Set_DragPreview",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragSetDragPreview)
        },
        ani_native_function {
            "_ComponentSnapshot_createFromBuilderWithCallback",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateFromBuilderWithCallback)
        },
        ani_native_function {
            "_ComponentSnapshot_createFromBuilderWithPromise",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateFromBuilderWithPromise)
        },
        ani_native_function {
            "_Common_GetSharedLocalStorage",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetSharedLocalStorage)
        },
        ani_native_function {
            "_ComponentSnapshot_createFromComponentWithPromise",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateFromComponentWithPromise)
        },
        ani_native_function {
            "_Animation_SetOrCreateAnimatableProperty",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetOrCreateAnimatableProperty)
        },
        ani_native_function {
            "_Animation_CreatePageTransitionEnter",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreatePageTransitionEnter)
        },
        ani_native_function {
            "_Animation_PageTransitionSetOnEnter",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PageTransitionSetOnEnter)
        },
        ani_native_function {
            "_Animation_CreatePageTransitionExit",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreatePageTransitionExit)
        },
        ani_native_function {
            "_Animation_PageTransitionSetOnExit",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PageTransitionSetOnExit)
        },
        ani_native_function {
            "_Animation_PageTransitionSetSlide",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PageTransitionSetSlide)
        },
        ani_native_function {
            "_Animation_PageTransitionSetTranslate",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PageTransitionSetTranslate)
        },
        ani_native_function {
            "_Animation_PageTransitionSetScale",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PageTransitionSetScale)
        },
        ani_native_function {
            "_Animation_PageTransitionSetOpacity",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PageTransitionSetOpacity)
        },
        ani_native_function {
            "_CreateViewStackProcessor",
            ":J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateViewStackProcessor)
        },
        ani_native_function {
            "_PopViewStackProcessor",
            ":J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PopViewStackProcessor)
        },
        ani_native_function {
            "_DeleteViewStackProcessor",
            "J:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DeleteViewStackProcessor)
        },
        ani_native_function {
            "_BackgroundImage_PixelMap",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetBackgroundImagePixelMap)
        },
        ani_native_function {
            "_DragController_executeDragWithCallback",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIExecuteDragWithCallback)
        },
        ani_native_function {
            "_DragController_executeDragWithPromise",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIExecuteDragWithPromise)
        },
        ani_native_function {
            "_DragController_createDragAction",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANICreateDragAction)
        },
        ani_native_function {
            "_DragController_startDrag",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIDragActionStartDrag)
        },
        ani_native_function {
            "_DragController_on",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIDragActionOn)
        },
        ani_native_function {
            "_DragController_off",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIDragActionOff)
        },
        ani_native_function {
            "_DragController_getDragPreview",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIGetDragPreview)
        },
        ani_native_function {
            "_DragController_setForegroundColor",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIDragPreviewSetForegroundColor)
        },
        ani_native_function {
            "_DragController_animate",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIDragPreviewAnimate)
        },
        ani_native_function {
            "_DragController_cleanDragAction",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANICleanDragAction)
        },
        ani_native_function {
            "_DragController_cleanDragPreview",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANICleanDragPreview)
        },
        ani_native_function {
            "_DragController_setDragEventStrictReportingEnabled",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIDragActionSetDragEventStrictReportingEnabled)
        },
        ani_native_function {
            "_DragController_cancelDataLoading",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIDragActionCancelDataLoading)
        },
        ani_native_function {
            "_DragController_notifyDragStartReques",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ANIDragActionNotifyDragStartReques)
        },
        ani_native_function {
            "_StyledString_SetPixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::StyledStringModule::SetPixelMap)
        },
        ani_native_function {
            "_StyledString_GetPixelMap",
            "J:L@ohos/multimedia/image/image/PixelMap;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::StyledStringModule::GetPixelMap)
        },
        ani_native_function {
            "_ImageSpan_Set_PixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetImageSpanPixelMap)
        },
        ani_native_function {
            "_ImageSpan_SetAlt_PixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetImageSpanAltPixelMap)
        },
        ani_native_function {
            "_ImageSpan_Set_DrawingColorFilter",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetImageSpanDrawingColorFilter)
        },
        ani_native_function {
            "_SetCustomCallback",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetCustomCallback)
        },
        ani_native_function {
            "_RequireArkoalaNodeId",
            "I:I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RequireArkoalaNodeId)
        },
        ani_native_function {
            "_Video_Transfer_PixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetVideoPixelMap)
        },
        ani_native_function {
            "_Shape_Transfer_PixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetShapePixelMap)
        },
        ani_native_function {
            "_RichEditor_Transfer_PixelMap",
            "L@ohos/multimedia/image/image/PixelMap;:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RichEditorTransferPixelMap)
        },
        ani_native_function {
            "_PersistentStorage_Get",
            "Lstd/core/String;:Lstd/core/String;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Get)
        },
        ani_native_function {
            "_PersistentStorage_Set",
            "Lstd/core/String;Lstd/core/String;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Set)
        },
        ani_native_function {
            "_PersistentStorage_Has",
            "Lstd/core/String;:Z",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Has)
        },
        ani_native_function {
            "_PersistentStorage_Clear",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Clear)
        },
        ani_native_function {
            "_PersistentStorage_Delete",
            "Lstd/core/String;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Delete)
        },
        ani_native_function {
            "_Env_GetColorMode",
            ":I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetColorMode)
        },
        ani_native_function {
            "_Env_GetFontScale",
            ":F",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetFontScale)
        },
        ani_native_function {
            "_Env_GetFontWeightScale",
            ":F",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetFontWeightScale)
        },
        ani_native_function {
            "_Env_GetAccessibilityEnabled",
            ":Z",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetAccessibilityEnabled)
        },
        ani_native_function {
            "_Env_GetLayoutDirection",
            ":Lstd/core/String;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetLayoutDirection)
        },
        ani_native_function {
            "_Env_GetLanguageCode",
            ":Lstd/core/String;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetLanguageCode)
        },
        ani_native_function {
            "_XComponent_SetXComponentOptions",
            "JLarkui/component/xcomponent/XComponentOptionsInternal;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetXComponentOptions)
        },
        ani_native_function {
            "_XComponent_SetXComponentParameters",
            "JLarkui/component/xcomponent/XComponentParametersInternal;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetXComponentParameters)
        },
        ani_native_function {
            "_XComponent_SetNativeXComponentParameters",
            "JI:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetNativeXComponentParameters)
        },
        ani_native_function {
            "_RemoveComponent_FromFrameNode",
            "JJ:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RemoveComponentFromFrameNode)
        },
        ani_native_function {
            "_AddComponent_ToFrameNode",
            "JJ:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::AddComponentToFrameNode)
        },
        ani_native_function {
            "_CheckIsUIThread",
            "I:I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CheckIsUIThread)
        },
        ani_native_function {
            "_IsDebugMode",
            "I:I",
            reinterpret_cast<void*>(OHOS::Ace::Ani::IsDebugMode)
        },
        ani_native_function {
            "_OnMeasure_InnerMeasure",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::OnMeasureInnerMeasure)
        },
        ani_native_function {
            "_OnLayout_InnerLayout",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::OnLayoutInnerLayout)
        },
        ani_native_function {
            "_SetParallelScoped",
            "Z:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetParallelScoped)
        },
        ani_native_function {
            "_Common_SetCustomPropertyCallBack",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetCustomPropertyCallBack)
        },
        ani_native_function {
            "_Common_getCustomProperty",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetCustomProperty)
        },
        ani_native_function {
            "_ConditionScopeNode_Construct",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructConditionScope)
        },
        ani_native_function {
            "_Common_vp2px",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Vp2px)
        },
        ani_native_function {
            "_Common_px2vp",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Px2vp)
        },
        ani_native_function {
            "_Common_fp2px",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Fp2px)
        },
        ani_native_function {
            "_Common_px2fp",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Px2fp)
        },
        ani_native_function {
            "_Common_lpx2px",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Lpx2px)
        },
        ani_native_function {
            "_Common_px2lpx",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Px2lpx)
        },
        ani_native_function {
            "_TransferKeyEventPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferKeyEventPointer)
        },
        ani_native_function {
            "_CreateKeyEventAccessorWithPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateKeyEventAccessorWithPointer)
        },
        ani_native_function {
            "_CreateEventTargetInfoAccessor",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateEventTargetInfoAccessor)
        },
        ani_native_function {
            "_EventTargetInfoAccessorWithId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::EventTargetInfoAccessorWithId)
        },
        ani_native_function {
            "_CreateScrollableTargetInfoAccessor",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateScrollableTargetInfoAccessor)
        },
        ani_native_function {
            "_ScrollableTargetInfoAccessorWithId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ScrollableTargetInfoAccessorWithId)
        },
        ani_native_function {
            "_ScrollableTargetInfoAccessorWithPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ScrollableTargetInfoAccessorWithPointer)
        },
        ani_native_function {
            "_TransferScrollableTargetInfoPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::TransferScrollableTargetInfoPointer)
        },
        ani_native_function {
            "_createDragEventAccessorWithPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateDragEventAccessorWithPointer)
        },
        ani_native_function {
            "_getDragEventPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetDragEventPointer)
        },
        ani_native_function {
            "_createTouchEventAccessorWithPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateTouchEventAccessorWithPointer)
        },
        ani_native_function {
            "_createMouseEventAccessorWithPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateMouseEventAccessorWithPointer)
        },
        ani_native_function {
            "_createAxisEventAccessorWithPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateAxisEventAccessorWithPointer)
        },
        ani_native_function {
            "_createClickEventAccessorWithPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateClickEventAccessorWithPointer)
        },
        ani_native_function {
            "_createHoverEventAccessorWithPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateHoverEventAccessorWithPointer)
        },
        ani_native_function {
            "_getTouchEventPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetTouchEventPointer)
        },
        ani_native_function {
            "_getMouseEventPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetMouseEventPointer)
        },
        ani_native_function {
            "_getAxisEventPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetAxisEventPointer)
        },
        ani_native_function {
            "_getClickEventPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetClickEventPointer)
        },
        ani_native_function {
            "_getHoverEventPointer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetHoverEventPointer)
        },
       ani_native_function {
            "_CanvasRenderer_SetPixelMap",
            "JL@ohos/multimedia/image/image/PixelMap;:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::SetPixelMap)
        },
        ani_native_function {
            "_CanvasRenderer_GetPixelMap",
            "JDDDD:L@ohos/multimedia/image/image/PixelMap;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetPixelMap)
        },
        ani_native_function {
            "_CanvasRenderer_DrawPixelMap0",
            "JL@ohos/multimedia/image/image/PixelMap;DD:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::DrawPixelMap0)
        },
        ani_native_function {
            "_CanvasRenderer_DrawPixelMap1",
            "JL@ohos/multimedia/image/image/PixelMap;DDDD:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::DrawPixelMap1)
        },
        ani_native_function {
            "_CanvasRenderer_DrawPixelMap2",
            "JL@ohos/multimedia/image/image/PixelMap;DDDDDDDD:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::DrawPixelMap2)
        },
        ani_native_function {
            "_ImageBitmap_Construct0",
            "Lstd/core/String;I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::ImageBitmapConstruct0)
        },
        ani_native_function {
            "_ImageBitmap_Construct1",
            "L@ohos/multimedia/image/image/PixelMap;I:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::ImageBitmapConstruct1)
        },
        ani_native_function {
            "_CanvasRenderer_GetCanvasDensity",
            "J:D",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetCanvasDensity)
        },
        ani_native_function {
            "_GetSystemDensity",
            ":D",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetSystemDensity)
        },
        ani_native_function {
            "_CanvasRenderer_GetImageData",
            "JDDDD:Lescompat/Uint8ClampedArray;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetImageData)
        },
        ani_native_function {
            "_CanvasRenderer_PutImageData0",
            "JLescompat/Uint8ClampedArray;DDII:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::PutImageData0)
        },
        ani_native_function {
            "_CanvasRenderer_PutImageData1",
            "JLescompat/Uint8ClampedArray;DDIIDDDD:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::PutImageData1)
        },
        ani_native_function {
            "_DrawingRenderingContext_GetCanvas",
            "J:L@ohos/graphics/drawing/drawing/Canvas;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetDrawingCanvas)
        },
        ani_native_function {
            "_FrameNode_MarkDirtyNode",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::FrameNodeMarkDirtyNode)
        },
        ani_native_function {
            "_TraceBegin",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::AniTrace::TraceBegin)
        },
        ani_native_function {
            "_TraceEnd",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::AniTrace::TraceEnd)
        },
        ani_native_function {
            "_AsyncTraceBegin",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::AniTrace::AsyncTraceBegin)
        },
        ani_native_function {
            "_AsyncTraceEnd",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::AniTrace::AsyncTraceEnd)
        },
        ani_native_function {            
            "_GetColorValue",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetColorValue)
        },
        ani_native_function {
            "_SendThemeToNative",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SendThemeToNative)
        },
        ani_native_function {
            "_SetDefaultTheme",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDefaultTheme)
        },
        ani_native_function {
            "_UpdateColorMode",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::UpdateColorMode)
        },
        ani_native_function {
            "_RestoreColorMode",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::RestoreColorMode)
        },
    };

    auto bindRst = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (bindRst != ANI_OK) {
        HILOGE("Bind native methonds failed, bindRst:%{public}d", bindRst);
        return bindRst;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
