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
#include "common_node/common_node_module.h"
#include "component3d/component3d_module_methods.h"
#include "componentSnapshot/componentSnapshot_module.h"
#include "content_slot/content_slot_module.h"
#include "keyboard_avoid_mode/keyboard_avoid_mode_module.h"
#include "custom_node/custom_node_module.h"
#include "syntax/lazy_for_each_module.h"
#include "syntax/syntax_module.h"
#include "syntax/for_each_module.h"
#include "syntax/parallelize_ui_module.h"
#include "drag_and_drop/native_drag_drop_global.h"
#include "dragController/drag_controller_module.h"
#include "styled_string/styled_string_module.h"
#include "image_span/image_span_module.h"
#include "image/image_module.h"
#include "list/list_children_main_size_module.h"
#include "load.h"
#include "log/log.h"
#include "utils/convert_utils.h"
#include "water_flow/water_flow_module.h"
#include "interop/interop_module.h"
#include "web/web_module_methods.h"
#include "video/video_module_methods.h"
#include "rich_editor/rich_editor_module.h"
#include "text_based_modifier/text_based_modifier_module.h"
#include "stateMgmt/stateMgmt_module.h"
#include "shape/shape_module_methods.h"
#include "xbar/xbar_module_methods.h"
#include "xcomponent/xcomponent_module_methods.h"
#include "condition_scope/condition_scope.h"
#include "utils/ani_trace.h"
#include "UINode/uinode_module_methods.h"
#include "node_adapter/node_adapter_module.h"
#include "visual_effect/visual_effect_module.h"
#include "security_component/paste_button_module.h"
#include "security_component/save_button_module.h"

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_class cls;
    auto ani_status = env->FindClass("arkui.ani.arkts.ArkUIAniModule.ArkUIAniModule", &cls);
    if (ani_status != ANI_OK) {
        return ANI_ERROR;
    }

    std::array staticMethods = {
        ani_native_function {
            "_Extractors_ToDrawableDescriptorPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToDrawableDescriptorPtr)
        },
        ani_native_function {
            "_Extractors_ToDrawingColorFilterPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToDrawingColorFilterPtr)
        },
        ani_native_function {
            "_Extractors_ToDrawingLatticePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToDrawingLatticePtr)
        },
        ani_native_function {
            "_Extractors_FromImagePixelMapPtr",
            "J:L@ohos/multimedia/image/image/PixelMap;",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromImagePixelMapPtr)
        },
        ani_native_function {
            "_Extractors_ToImagePixelMapPtr",
            "L@ohos/multimedia/image/image/PixelMap;:J",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToImagePixelMapPtr)
        },
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
            "_Image_ColorFilter_TransferStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Image_ColorFilter_TransferStatic)
        },
        ani_native_function {
            "_Image_ColorFilter_TransferDynamic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Image_ColorFilter_TransferDynamic)
        },
        ani_native_function {
            "_Extractors_ToWebviewWebviewControllerPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToWebviewWebviewControllerPtr)
        },
        ani_native_function {
            "_Extractors_FromWebviewWebviewControllerPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromWebviewWebviewControllerPtr)
        },
        ani_native_function {
            "_Web_SetJavaScriptProxyController",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetJavaScriptProxyController)
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
            "C{@ohos.multimedia.image.image.PixelMap}:l",
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
            "_CustomNode_QueryNavDestinationInfo1",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryNavDestinationInfo1)
        },
        ani_native_function {
            "_CustomNode_OnReuse",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::OnReuse)
        },
        ani_native_function {
            "_CustomNode_OnRecycle",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::OnRecycle)
        },
        ani_native_function {
            "_CustomNode_QueryRouterPageInfo",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryRouterPageInfo)
        },
        ani_native_function {
            "_CustomNode_QueryRouterPageInfo1",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::QueryRouterPageInfo1)
        },
        ani_native_function {
            "_ConvertUtils_ConvertToPixelMapAni",
            "l:C{@ohos.multimedia.image.image.PixelMap}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConvertToPixelMapAni)
        },
        ani_native_function {
            "_Common_GetHostContext",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetHostContext)
        },
        ani_native_function {
            "_Common_SetFrameRateRange",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetFrameRateRange)
        },
        ani_native_function {
            "_Common_Sync_InstanceId",
            "i:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SyncInstanceId)
        },
        ani_native_function {
            "_Common_Restore_InstanceId",
            ":",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RestoreInstanceId)
        },
        ani_native_function {
            "_Common_Get_Current_InstanceId",
            ":i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetCurrentInstanceId)
        },
        ani_native_function {
            "_Common_GetFocused_InstanceId",
            ":i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetFocusedInstanceId)
        },
        ani_native_function {
            "_Common_SetImageCacheCount",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetImageCacheCount)
        },
        ani_native_function {
            "_Common_SetImageRawDataCacheSize",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetImageRawDataCacheSize)
        },
        ani_native_function {
            "_GetNodePtrWithPeerPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetNodePtrWithPeerPtr)
        },
        ani_native_function {
            "_GetNodeIdWithNodePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetNodeIdWithNodePtr)
        },
        ani_native_function {
            "_GetNodeIdWithPeerPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetNodeIdWithPeerPtr)
        },
        ani_native_function {
            "_CreateRenderNodePeerWithNodePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateRenderNodePeerWithNodePtr)
        },
        ani_native_function {
            "_ToColorLong",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ToColorLong)
        },
        ani_native_function {
            "_ToColorInt",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ToColorInt)
        },
        ani_native_function {
            "_CustomNode_Construct",
            "iC{arkui.ArkCustomComponent.ArkCustomComponent}:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructCustomNode)
        },
        ani_native_function {
            "_CustomNode_RequestFrame",
            ":",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RequestFrame)
        },
        ani_native_function {
            "_LazyForEachNode_Construct",
            "iz:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructLazyForEachNode)
        },
        ani_native_function {
            "_BuilderProxyNode_Construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::BuilderProxyNodeConstruct)
        },
        ani_native_function {
            "_ContentSlot_construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ContentSlotConstruct)
        },
        ani_native_function {
            "_ContentSlotInterface_setContentSlotOptions",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetContentSlotOptions)
        },
        ani_native_function {
            "_SetDrawCallback",
            "lC{std.core.Function1}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawCallback)
        },
        ani_native_function {
            "_SetFrameNodeDrawCallback",
            "lC{std.core.Function1}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetFrameNodeDrawCallback)
        },
        ani_native_function {
            "_SetDrawModifier",
            "liC{arkui.component.common.DrawModifier}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetDrawModifier)
        },
        ani_native_function {
            "_Invalidate",
            "l:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Invalidate)
        },
        ani_native_function {
            "_SetOverlay_ComponentContent",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetOverlayComponentContent)
        },
        ani_native_function {
            "_SetWaterFlowSection",
            "lC{arkui.component.waterFlow.WaterFlowSections}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowSection)
        },
        ani_native_function {
            "_UpdateWaterFlowSection",
            "lC{arkui.component.waterFlow.SectionChangeInfo}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::UpdateWaterFlowSection)
        },
        ani_native_function {
            "_SetWaterFlowFooterContent",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowFooterContent)
        },
        ani_native_function {
            "_SetWaterFlowFooter",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowFooter)
        },
        ani_native_function {
            "_ResetWaterFlowFooter",
            "l:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ResetWaterFlowFooter)
        },
        ani_native_function {
            "_SetWaterFlowScroller",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowScroller)
        },
        ani_native_function {
            "_SetWaterFlowLayoutMode",
            "li:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetWaterFlowLayoutMode)
        },
        ani_native_function {
            "_SetListChildrenMainSize",
            "lC{arkui.component.common.ChildrenMainSize}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetListChildrenMainSize)
        },
        ani_native_function {
            "_GetKeyboardAvoidMode",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetKeyboardAvoidMode)
        },
        ani_native_function {
            "_SetKeyboardAvoidMode",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetKeyboardAvoidMode)
        },
        ani_native_function {
            "_DragEvent_Set_Data",
            "lC{@ohos.data.unifiedDataChannel.unifiedDataChannel.UnifiedData}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetData)
        },
        ani_native_function {
            "_DragEvent_Get_Data",
            "l:C{@ohos.data.unifiedDataChannel.unifiedDataChannel.UnifiedData}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventGetData)
        },
        ani_native_function {
            "_DragEvent_Get_Summary",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventGetSummary)
        },
        ani_native_function {
            "_DragEvent_Start_Data_Loading",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEveStartDataLoading)
        },
        ani_native_function {
            "_DragEvent_Set_PixelMap",
            "lC{@ohos.multimedia.image.image.PixelMap}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetPixelMap)
        },
        ani_native_function {
            "_DragEvent_Set_ExtraInfo",
            "lC{std.core.String}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetExtraInfo)
        },
        ani_native_function {
            "_DragEvent_Set_CustomNode",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragEventSetCustomNode)
        },
        ani_native_function {
            "_Drag_Set_AllowDrop_Null",
            "l:",
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
            "_Drag_Set_DragPreviewOptions",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DragSetDragPreviewOptions)
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
            "_UiMaterial_ConstructMaterial",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::UiMaterialConstructMaterial)
        },
        ani_native_function {
            "_UiMaterial_DestroyMaterial",
            "l:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::UiMaterialDestroyMaterial)
        },
        ani_native_function {
            "_CreateViewStackProcessor",
            ":l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateViewStackProcessor)
        },
        ani_native_function {
            "_PopViewStackProcessor",
            ":l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PopViewStackProcessor)
        },
        ani_native_function {
            "_DeleteViewStackProcessor",
            "l:",
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
            "lC{@ohos.multimedia.image.image.PixelMap}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::StyledStringModule::SetPixelMap)
        },
        ani_native_function {
            "_StyledString_GetPixelMap",
            "l:C{@ohos.multimedia.image.image.PixelMap}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::StyledStringModule::GetPixelMap)
        },
        ani_native_function {
            "_Extractors_FromSymbolGlyphModifierPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromSymbolGlyphModifierPtr)
        },
        ani_native_function {
            "_Extractors_ToSymbolGlyphModifierPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToSymbolGlyphModifierPtr)
        },
        ani_native_function {
            "_Extractors_FromTextModifierPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromTextModifierPtr)
        },
        ani_native_function {
            "_Extractors_ToTextModifierPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToTextModifierPtr)
        },
        ani_native_function {
            "_ImageSpan_Set_PixelMap",
            "lC{@ohos.multimedia.image.image.PixelMap}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetImageSpanPixelMap)
        },
        ani_native_function {
            "_ImageSpan_SetAlt_PixelMap",
            "lC{@ohos.multimedia.image.image.PixelMap}:",
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
            "i:i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RequireArkoalaNodeId)
        },
        ani_native_function {
            "_Video_SetVoidCallback",
            "lC{std.core.Function0}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetVideoOnErrorVoidCallback)
        },
        ani_native_function {
            "_Video_SetErrorCallback",
            "lC{std.core.Function1}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetVideoOnErrorErrorCallback)
        },
        ani_native_function {
            "_Shape_Transfer_PixelMap",
            "lC{@ohos.multimedia.image.image.PixelMap}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetShapePixelMap)
        },
        ani_native_function {
            "_RichEditor_Transfer_PixelMap",
            "C{@ohos.multimedia.image.image.PixelMap}:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RichEditorTransferPixelMap)
        },
        ani_native_function {
            "_PersistentStorage_Get",
            "C{std.core.String}i:C{std.core.String}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Get)
        },
        ani_native_function {
            "_PersistentStorage_Set",
            "C{std.core.String}C{std.core.String}i:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Set)
        },
        ani_native_function {
            "_PersistentStorage_Has",
            "C{std.core.String}i:z",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Has)
        },
        ani_native_function {
            "_PersistentStorage_Clear",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Clear)
        },
        ani_native_function {
            "_PersistentStorage_Delete",
            "C{std.core.String}i:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::PersistentStorage_Delete)
        },
        ani_native_function {
            "_Env_GetColorMode",
            ":i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetColorMode)
        },
        ani_native_function {
            "_Env_GetFontScale",
            ":f",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetFontScale)
        },
        ani_native_function {
            "_Env_GetFontWeightScale",
            ":f",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetFontWeightScale)
        },
        ani_native_function {
            "_Env_GetAccessibilityEnabled",
            ":z",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetAccessibilityEnabled)
        },
        ani_native_function {
            "_Env_GetLayoutDirection",
            ":C{std.core.String}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetLayoutDirection)
        },
        ani_native_function {
            "_Env_GetLanguageCode",
            ":C{std.core.String}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::Env_GetLanguageCode)
        },
        ani_native_function {
            "_XComponent_SetXComponentControllerCallback",
            "lC{arkui.component.xcomponent.XComponentOptionsInternal}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetXComponentControllerCallback)
        },
        ani_native_function {
            "_RemoveComponent_FromFrameNode",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::RemoveComponentFromFrameNode)
        },
        ani_native_function {
            "_AddComponent_ToFrameNode",
            "ll:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::AddComponentToFrameNode)
        },

        ani_native_function {
            "_CreateWindowFreeContainer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateWindowFreeContainer)
        },

        ani_native_function {
            "_DestroyWindowFreeContainer",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::DestroyWindowFreeContainer)
        },

        ani_native_function {
            "_CheckIsUIThread",
            "i:i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CheckIsUIThread)
        },
        ani_native_function {
            "_IsDebugMode",
            "i:i",
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
            "z:",
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
            "_ConditionScope_Mark_Dirty",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConditionScopeMarkDirty)
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
            "_Common_getWindowName",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::getWindowName)
        },
        ani_native_function {
            "_Common_getWindowId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::getWindowId)
        },
        ani_native_function {
            "_Common_getWindowWidthBreakpoint",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::getWindowWidthBreakpoint)
        },
        ani_native_function {
            "_Common_getWindowHeightBreakpoint",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::getWindowHeightBreakpoint)
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
            "_Extractors_toUnifiedDataChannelUnifiedDataPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorFromUnifiedDataToPtr)
        },
        ani_native_function {
            "_Extractors_fromUnifiedDataChannelUnifiedDataPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorFromPtrToUnifiedData)
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
            "lC{@ohos.multimedia.image.image.PixelMap}:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::SetPixelMap)
        },
        ani_native_function {
            "_CanvasRenderer_DrawPixelMap0",
            "lC{@ohos.multimedia.image.image.PixelMap}dd:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::DrawPixelMap0)
        },
        ani_native_function {
            "_CanvasRenderer_DrawPixelMap1",
            "lC{@ohos.multimedia.image.image.PixelMap}dddd:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::DrawPixelMap1)
        },
        ani_native_function {
            "_CanvasRenderer_DrawPixelMap2",
            "lC{@ohos.multimedia.image.image.PixelMap}dddddddd:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::DrawPixelMap2)
        },
        ani_native_function {
            "_ImageBitmap_Construct0",
            "C{std.core.String}i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::ImageBitmapConstruct0)
        },
        ani_native_function {
            "_ImageBitmap_Construct1",
            "C{@ohos.multimedia.image.image.PixelMap}i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::ImageBitmapConstruct1)
        },
        ani_native_function {
            "_CanvasRenderer_GetCanvasDensity",
            "l:d",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetCanvasDensity)
        },
        ani_native_function {
            "_GetSystemDensity",
            ":d",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetSystemDensity)
        },
        ani_native_function {
            "_CanvasRenderer_GetImageData",
            "ldddd:C{escompat.Uint8ClampedArray}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetImageData)
        },
        ani_native_function {
            "_CanvasRenderer_PutImageData0",
            "lC{escompat.Uint8ClampedArray}ddii:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::PutImageData0)
        },
        ani_native_function {
            "_CanvasRenderer_PutImageData1",
            "lC{escompat.Uint8ClampedArray}ddiidddd:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::PutImageData1)
        },
        ani_native_function {
            "_DrawingRenderingContext_GetCanvas",
            "l:C{@ohos.graphics.drawing.drawing.Canvas}",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetDrawingCanvas)
        },
        ani_native_function {
            "_CanvasRenderingContext_GetCanvasId",
            "l:i",
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::GetCanvasId)
        },
        ani_native_function {
            "_CanvasRenderingContext_setAttachCallbackId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::SetAttachCallbackId)
        },
        ani_native_function {
            "_CanvasRenderingContext_setDetachCallbackId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CanvasModule::SetDetachCallbackId)
        },
        ani_native_function {
            "_FrameNode_MarkDirtyNode",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::FrameNodeMarkDirtyNode)
        },
        ani_native_function {
            "_GetAttributeSetTraceEnabled",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::AniTrace::GetAttributeSetTraceEnabled)
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
            "_GetStringColorValue",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetStringColorValue)
        },
        ani_native_function {
            "_GetNumberColorValue",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetNumberColorValue)
        },
        ani_native_function {
            "_SendThemeToNative",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SendThemeToNative)
        },
        ani_native_function {
            "_RemoveThemeInNative",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::RemoveThemeInNative)
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
        ani_native_function {
            "_SetThemeScopeId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetThemeScopeId)
        },
        ani_native_function {
            "_CreateAndBindTheme",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateAndBindTheme)
        },
        ani_native_function {
            "_ApplyParentThemeScopeId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ApplyParentThemeScopeId)
        },
        ani_native_function {
            "_UINode_OnUpdateDone",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::OnUpdateDone)
        },
        ani_native_function {
            "_UINode_SetStatic",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetUINodeIsStatic)
        },
        ani_native_function {
            "_NodeAdapter_Construct",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterConstruct)
        },
        ani_native_function {
            "_NodeAdapter_DetachNodeAdapter",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterDetachNodeAdapter)
        },
        ani_native_function {
            "_NodeAdapter_AttachNodeAdapter",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterAttachNodeAdapter)
        },
        ani_native_function {
            "_NodeAdapter_Dispose",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterDispose)
        },
        ani_native_function {
            "_NodeAdapter_SetTotalNodeCount",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterSetTotalNodeCount)
        },
        ani_native_function {
            "_NodeAdapter_NotifyItemReloaded",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterNotifyItemReloaded)
        },
        ani_native_function {
            "_NodeAdapter_NotifyItemChanged",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterNotifyItemChanged)
        },
        ani_native_function {
            "_NodeAdapter_NotifyItemRemoved",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterNotifyItemRemoved)
        },
        ani_native_function {
            "_NodeAdapter_NotifyItemInserted",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterNotifyItemInserted)
        },
        ani_native_function {
            "_NodeAdapter_NotifyItemMoved",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterNotifyItemMoved)
        },
        ani_native_function { "_NodeAdapter_GetAllItems",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::NodeAdapterGetAllItems)
        },
        ani_native_function {
            "_SyntaxItem_Construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructSyntaxItem)
        },
        ani_native_function {
            "_ForEachNode_Construct",
            "iz:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ConstructForEachNode)
        },
        ani_native_function {
            "_ForEach_FinishRender",
            "J:V",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ForEachFinishRender)
        },
        ani_native_function {
            "_Component3D_SetScene",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Component3DSetScene)
        },
        ani_native_function {
            "_Component3D_SetWidget",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Component3DSetWidget)
        },
        ani_native_function {
            "_Extractors_ToScenePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToScenePtr)
        },
        ani_native_function {
            "_XBar_Set_ComponentCreateFunc",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::XBarSetComponentCreateFunc)
        },
        ani_native_function {
            "_XBar_Set_JsFunc",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::XBarSetJsFunc)
        },
        ani_native_function {
            "_XBar_Call_Native",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::XBarCallNative)
        },
        ani_native_function {
            "_Extractors_ToRectShapePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToRectShapePtr)
        },
        ani_native_function {
            "_Extractors_FromRectShapePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromRectShapePtr)
        },
        ani_native_function {
            "_Extractors_ToCircleShapePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToCircleShapePtr)
        },
        ani_native_function {
            "_Extractors_FromCircleShapePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromCircleShapePtr)
        },
        ani_native_function {
            "_Extractors_ToEllipseShapePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToEllipseShapePtr)
        },
        ani_native_function {
            "_Extractors_FromEllipseShapePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromEllipseShapePtr)
        },
        ani_native_function {
            "_Extractors_ToPathShapePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToPathShapePtr)
        },
        ani_native_function {
            "_Extractors_FromPathShapePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromPathShapePtr)
        },
        ani_native_function {
            "_Extractors_ToICurvePtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToICurvePtr)
        },
        ani_native_function {
            "_Extractors_ToMatrix4TransitPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToMatrix4TransitPtr)
        },
        ani_native_function {
            "_Extractors_ToUiEffectFilterPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToUiEffectFilterPtr)
        },
        ani_native_function {
            "_Extractors_ToUiEffectVisualEffectPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToUiEffectVisualEffectPtr)
        },
        ani_native_function {
            "_Extractors_ToUiMaterialMaterialPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToUiMaterialMaterialPtr)
        },
        ani_native_function {
            "_Extractors_ToDrawContextPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToDrawContextPtr)
        },
        ani_native_function {
            "_Extractors_FromDrawContextPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromDrawContextPtr)
        },
        ani_native_function {
            "_Extractors_ToDrawingCanvasPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsToDrawingCanvasPtr)
        },
        ani_native_function {
            "_Extractors_FromDrawingCanvasPtr",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ExtractorsFromDrawingCanvasPtr)
        },
        ani_native_function {
            "_Common_construct",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::Commonconstruct)
        },
        ani_native_function {
            "_CommonInterface_setCommonOptions",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetCommonOptions)
        },
        ani_native_function {
            "_ParallelizeUIAdapterNode_Construct",
            "i:l",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ParallelizeUIAdapterNodeConstruct)
        },
        ani_native_function {
            "_ParallelizeUIAdapterNode_Reset",
            "l:",
            reinterpret_cast<void*>(OHOS::Ace::Ani::ParallelizeUIReset)
        },
        ani_native_function {
            "_ParallelizeUIAdapterNode_RegisterCallback",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ParallelizeUIRegisterCallback)
        },
        ani_native_function {
            "_ApplyThemeScopeId",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::ApplyThemeScopeId)
        },
        ani_native_function {
            "_SaveButton_SetOnClickCallback",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SaveButton_SetOnClickCallback)
        },
        ani_native_function {
            "_PasteButton_SetOnClickCallback",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::PasteButton_SetOnClickCallback)
        },
        ani_native_function {
            "_BaseEvent_getModifierKeyState",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetBaseEventModifierKeyState)
        },
        ani_native_function {
            "_DragEvent_getModifierKeyState",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetDragEventModifierKeyState)
        },
        ani_native_function {
            "_KeyEvent_getModifierKeyState",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::GetKeyEventModifierKeyState)
        },
        ani_native_function {
            "_ClickEvent_preventDefault",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetClickEventPreventDefault)
        },
        ani_native_function {
            "_TouchEvent_preventDefault",
            nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::SetTouchEventPreventDefault)
        }
    };

    auto bindRst = env->Class_BindStaticNativeMethods(cls, staticMethods.data(), staticMethods.size());
    if (bindRst != ANI_OK) {
        HILOGE("Bind static native methods failed, bindRst:%{public}d", bindRst);
        return bindRst;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
