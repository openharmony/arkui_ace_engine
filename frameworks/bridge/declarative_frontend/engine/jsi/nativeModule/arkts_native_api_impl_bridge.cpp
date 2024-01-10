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
#include <cstdint>
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_blank_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_button_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkbox_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkboxgroup_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_animator_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_counter_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_divider_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_col_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_row_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_item_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_hyperlink_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_list_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_list_item_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_span_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_loading_progress_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_menu_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_nav_destination_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_nav_router_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_menu_item_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_date_picker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigator_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_panel_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_node_container_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_pattern_lock_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_progress_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_area_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_clock_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_swiper_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_input_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_toggle_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_radio_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rating_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_render_node_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_row_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_row_split_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_search_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_select_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stack_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_slider_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_span_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_textpicker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_timepicker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rich_editor_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_video_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stepper_item_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_marquee_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_tabcontent_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_tabs_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_split_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_line_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_path_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_polygon_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_polyline_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_qrcode_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_side_bar_container_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_calendar_picker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_water_flow_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_alphabet_indexer_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_data_panel_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_gauge_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scroll_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_marquee_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_shape_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_shape_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rect_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_list_item_group_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_timer_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_render_node_bridge.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_plugin_bridge.h"
#endif
#ifdef XCOMPONENT_SUPPORTED
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_xcomponent_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_xcomponent_node_bridge.h"
#endif
#ifdef FORM_SUPPORTED
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_form_component_bridge.h"
#endif
namespace OHOS::Ace::NG {
ArkUINativeModuleValue ArkUINativeModule::GetFrameNodeById(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int nodeId = firstArg->ToNumber(vm)->Value();
    auto nodePtr = GetArkUIInternalNodeAPI()->GetFrameNodeById(nodeId);
    return panda::NativePointerRef::New(vm, nodePtr);
}

ArkUINativeModuleValue ArkUINativeModule::GetUIState(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int64_t state = GetArkUIInternalNodeAPI()->GetUIState(nativeNode);
    return panda::NumberRef::New(vm, state);
}

ArkUINativeModuleValue ArkUINativeModule::SetSupportedUIState(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto state = secondArg->ToNumber(vm)->Value();
    GetArkUIInternalNodeAPI()->SetSupportedUIState(nativeNode, state);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ArkUINativeModule::GetArkUINativeModule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto object = panda::ObjectRef::New(vm);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFrameNodeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetFrameNodeById));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getUIState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetUIState));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSupportedUIState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SetSupportedUIState));

    auto common = panda::ObjectRef::New(vm);
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetHeight));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetHeight));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderRadius));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderRadius));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTransform"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTransform));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTransform"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTransform));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetPosition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetPosition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOutlineColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOutlineColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOutlineColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOutlineColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOutlineRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOutlineRadius));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOutlineRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOutlineRadius));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOutlineStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOutlineStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOutlineStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOutlineStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOutlineWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOutlineWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOutlineWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOutlineWidth));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOutline"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOutline));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOutline"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOutline));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetShadow));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetShadow));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHitTestBehavior"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetHitTestBehavior));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHitTestBehavior"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetHitTestBehavior));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setZIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetZIndex));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetZIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetZIndex));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOpacity));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOpacity));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAlign));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAlign));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackdropBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackdropBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackdropBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackdropBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHueRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetHueRotate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHueRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetHueRotate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInvert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetInvert));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInvert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetInvert));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSepia"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSepia));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSepia"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSepia));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSaturate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSaturate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSaturate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSaturate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColorBlend"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetColorBlend));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColorBlend"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetColorBlend));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGrayscale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetGrayscale));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGrayscale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetGrayscale));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContrast"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetContrast));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContrast"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetContrast));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBrightness));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBrightness));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLinearGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetLinearGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLinearGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetLinearGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSweepGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSweepGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSweepGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSweepGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadialGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRadialGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadialGradient"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRadialGradient));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOverlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOverlay));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOverlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOverlay));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderImage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderImage));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderImage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorderImage));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setForegroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetForegroundBlurStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetForegroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetForegroundBlurStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLinearGradientBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetLinearGradientBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLinearGradientBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetLinearGradientBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundBlurStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundBlurStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorder));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBorder));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImagePosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundImagePosition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundImagePosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundImagePosition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImageSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundImageSize));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundImageSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundImageSize));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundImage));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundImage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundImage));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTranslate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTranslate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTranslate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTranslate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetScale));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetScale));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRotate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRotate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRotate));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGeometryTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetGeometryTransition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGeometryTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetGeometryTransition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetClip));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetClip));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPixelStretchEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetPixelStretchEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPixelStretchEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetPixelStretchEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLightUpEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetLightUpEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLightUpEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetLightUpEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSphericalEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSphericalEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSphericalEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSphericalEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRenderGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRenderGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRenderFit));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRenderFit));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setUseEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetUseEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetUseEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetUseEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetForegroundColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetForegroundColor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMotionPath"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetMotionPath));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMotionPath"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetMotionPath));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGroupDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetGroupDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGroupDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetGroupDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFocusOnTouch"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFocusOnTouch));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFocusOnTouch"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFocusOnTouch));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFocusable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFocusable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFocusable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFocusable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTouchable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTouchable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTouchable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTouchable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisplayPriority"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDisplayPriority));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisplayPriority"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDisplayPriority));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetMask));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetMask));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetOffset));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetOffset));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetPadding));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetPadding));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetMargin));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetMargin));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarkAnchor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetMarkAnchor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMarkAnchor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetMarkAnchor));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVisibility"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetVisibility));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVisibility"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetVisibility));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityText));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityText));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAllowDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAllowDrop));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAllowDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAllowDrop));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityLevel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityLevel));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityLevel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityLevel));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDirection));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDirection));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLayoutWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetLayoutWeight));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLayoutWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetLayoutWeight));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSize));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSize));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignSelf"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAlignSelf));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignSelf"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAlignSelf));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAspectRatio"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAspectRatio));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAspectRatio"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAspectRatio));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFlexGrow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFlexGrow));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFlexGrow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFlexGrow));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFlexShrink"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFlexShrink));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFlexShrink"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFlexShrink));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setConstraintSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetConstraintSize));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetConstraintSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetConstraintSize));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetGridOffset));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetGridOffset));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridSpan"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetGridSpan));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridSpan"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetGridSpan));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setExpandSafeArea"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetExpandSafeArea));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetExpandSafeArea"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetExpandSafeArea));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignRules"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAlignRules));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignRules"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAlignRules));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFlexBasis"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFlexBasis));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFlexBasis"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFlexBasis));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityDescription"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityDescription));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityDescription"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityDescription));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetKey));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetKey));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRestoreId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetRestoreId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRestoreId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetRestoreId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTabIndex));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTabIndex));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObscured"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetObscured));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObscured"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetObscured));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetResponseRegion));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetResponseRegion));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMouseResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetMouseResponseRegion));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMouseResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetMouseResponseRegion));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTransition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTransition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSharedTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSharedTransition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSharedTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetSharedTransition));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnabled"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetEnabled));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnabled"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetEnabled));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDraggable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDraggable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHoverEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetHoverEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHoverEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetHoverEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setClickEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetClickEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetClickEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetClickEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setKeyBoardShortCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetKeyBoardShortCut));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetKeyBoardShortCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetKeyBoardShortCut));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setClipWithEdge"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetClipWithEdge));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetClipWithEdge"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetClipWithEdge));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "common"), common);

    auto counter = panda::ObjectRef::New(vm);
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableInc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetEnableInc));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableInc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetEnableInc));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableDec"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetEnableDec));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableDec"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetEnableDec));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCounterHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterHeight));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCounterHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterHeight));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCounterWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterWidth));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCounterWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterWidth));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCounterBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterBackgroundColor));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCounterBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterBackgroundColor));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCounterSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterSize));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCounterSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterSize));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "counter"), counter);

    auto checkboxgroup = panda::ObjectRef::New(vm);
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupSelectedColor));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupSelectedColor));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupUnSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupUnSelectedColor));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupUnSelectedColor"),
        panda::FunctionRef::New(
            const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupUnSelectedColor));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupSelectAll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupSelectAll));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupSelectAll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupSelectAll));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupWidth));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupWidth));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupHeight));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupHeight));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupMark"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupMark));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupMark"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupMark));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupSize));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupSize));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "checkboxgroup"), checkboxgroup);

    auto panel = panda::ObjectRef::New(vm);
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowCloseIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetShowCloseIcon));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowCloseIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetShowCloseIcon));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDragBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetDragBar));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDragBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetDragBar));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetShow));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetShow));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "panel"), panel);

    auto row = panda::ObjectRef::New(vm);
    row->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowBridge::SetAlignItems));
    row->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowBridge::ResetAlignItems));
    row->Set(vm, panda::StringRef::NewFromUtf8(vm, "setJustifyContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowBridge::SetJustifyContent));
    row->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetJustifyContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowBridge::ResetJustifyContent));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "row"), row);

    auto rowSplit = panda::ObjectRef::New(vm);
    rowSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResizeable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowSplitBridge::SetResizeable));
    rowSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResizeable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowSplitBridge::ResetResizeable));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "rowSplit"), rowSplit);

    auto text = panda::ObjectRef::New(vm);
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontStyle));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontStyle));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextAlign));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetTextAlign));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontWeight));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontWeight));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetLineHeight));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetLineHeight));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextOverflow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextOverflow));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextOverflow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetTextOverflow));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetDecoration));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetDecoration));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextCase"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextCase));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextCase"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetTextCase));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetMaxLines));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetMaxLines));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetMinFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ReSetMinFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetDraggable));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetDraggable));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetMaxFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetMaxFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontFamily));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontFamily));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetCopyOption));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetCopyOption));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextShadow));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetTextShadow));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeightAdaptivePolicy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetHeightAdaptivePolicy));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeightAdaptivePolicy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetHeightAdaptivePolicy));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextIndent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextIndent));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextIndent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetTextIndent));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBaselineOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetBaselineOffset));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBaselineOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetBaselineOffset));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetLetterSpacing));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetLetterSpacing));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFont));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFont));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWordBreak"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetWordBreak));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWordBreak"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetWordBreak));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "text"), text);

    auto search = panda::ObjectRef::New(vm);
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetTextFont));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetTextFont));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPlaceholderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetPlaceholderColor));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPlaceholderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetPlaceholderColor));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectionMenuHidden"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSelectionMenuHidden));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectionMenuHidden"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSelectionMenuHidden));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCaretStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCaretStyle));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCaretStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetCaretStyle));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchTextAlign));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchTextAlign));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCancelButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCancelButton));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCancelButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetCancelButton));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableKeyboardOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetEnableKeyboardOnFocus));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableKeyboardOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetEnableKeyboardOnFocus));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPlaceholderFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetPlaceholderFont));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPlaceholderFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetPlaceholderFont));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSearchIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchIcon));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSearchIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchIcon));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSearchButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchButton));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSearchButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchButton));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetFontColor));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetFontColor));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetCopyOption));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetCopyOption));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "search"), search);

    auto stack = panda::ObjectRef::New(vm);
    stack->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StackBridge::SetAlignContent));
    stack->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StackBridge::ResetAlignContent));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "stack"), stack);

    auto imageSpan = panda::ObjectRef::New(vm);
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVerticalAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::SetVerticalAlign));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVerticalAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::ResetVerticalAlign));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::SetObjectFit));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::ResetObjectFit));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageSpan"), imageSpan);

    auto blank = panda::ObjectRef::New(vm);
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::SetColor));
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::ResetColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "blank"), blank);

    auto span = panda::ObjectRef::New(vm);
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextCase"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetTextCase));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextCase"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetTextCase));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetFontWeight));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetFontWeight));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetLineHeight));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ReSetLineHeight));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetFontStyle));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ReSetFontStyle));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetFontSize));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetFontSize));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetFontFamily));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetFontFamily));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetDecoration));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetDecoration));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetFontColor));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetFontColor));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetLetterSpacing));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetLetterSpacing));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetFont));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetFont));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "span"), span);

    auto gridCol = panda::ObjectRef::New(vm);
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSpan"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetSpan));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSpan"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetSpan));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridColOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetGridColOffset));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridColOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetGridColOffset));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOrder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::SetOrder));
    gridCol->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOrder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridColBridge::ResetOrder));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridCol"), gridCol);

    auto column = panda::ObjectRef::New(vm);
    column->Set(vm, panda::StringRef::NewFromUtf8(vm, "setJustifyContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnBridge::SetJustifyContent));
    column->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetJustifyContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnBridge::ResetJustifyContent));
    column->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnBridge::SetAlignItems));
    column->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnBridge::ResetAlignItems));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "column"), column);

    auto gridRow = panda::ObjectRef::New(vm);
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetAlignItems));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetAlignItems));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridRow"), gridRow);

    auto richEditor = panda::ObjectRef::New(vm);
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCopyOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCopyOptions));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCopyOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetCopyOptions));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "richEditor"), richEditor);

    auto textArea = panda::ObjectRef::New(vm);
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetStyle));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetStyle));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectionMenuHidden"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetSelectionMenuHidden));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectionMenuHidden"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetSelectionMenuHidden));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxLines));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxLines));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCopyOption));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetCopyOption));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPlaceholderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPlaceholderColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPlaceholderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetPlaceholderColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextAreaTextAlign));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextAreaTextAlign));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPlaceholderFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPlaceholderFont));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPlaceholderFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetPlaceholderFont));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBarState));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBarState));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableKeyboardOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnableKeyboardOnFocus));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableKeyboardOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnableKeyboardOnFocus));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontFamily));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontFamily));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowCounter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetShowCounter));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowCounter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetShowCounter));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCaretColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCaretColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCaretColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetCaretColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxLength));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxLength));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontStyle));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontStyle));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontWeight));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontWeight));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontSize));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontSize));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textArea"), textArea);

    auto video = panda::ObjectRef::New(vm);
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoPlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetAutoPlay));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoPlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetAutoPlay));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setControls"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetControls));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetControls"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetControls));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetObjectFit));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetObjectFit));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetLoop));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetLoop));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMuted"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetMuted));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMuted"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetMuted));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "video"), video);

    auto patternLock = panda::ObjectRef::New(vm);
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSideLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetSideLength));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSideLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetSideLength));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoReset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetAutoReset));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoReset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetAutoReset));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPathStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPathStrokeWidth));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPathStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPathStrokeWidth));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRegularColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetRegularColor));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRegularColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetRegularColor));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPathColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPathColor));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPathColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPathColor));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setActiveColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockActiveColor));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetActiveColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockActiveColor));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCircleRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockCircleRadius));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCircleRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockCircleRadius));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockSelectedColor));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockSelectedColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "patternLock"), patternLock);

    auto columnSplit = panda::ObjectRef::New(vm);
    columnSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ColumnSplitBridge::SetDivider));
    columnSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ColumnSplitBridge::ResetDivider));
    columnSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResizeable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ColumnSplitBridge::SetResizeable));
    columnSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResizeable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ColumnSplitBridge::ResetResizeable));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "columnSplit"), columnSplit);

    auto imageAnimator = panda::ObjectRef::New(vm);
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetState));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetState));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDuration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetDuration));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDuration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetDuration));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFixedSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetFixedSize));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFixedSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetFixedSize));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFillMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetFillMode));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFillMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetFillMode));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setReverse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetReverse));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetReverse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetReverse));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImages"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImages));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImages"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImages));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setIterations"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetIteration));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetIterations"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetIteration));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageAnimator"), imageAnimator);

    auto textInput = panda::ObjectRef::New(vm);
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCaretColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCaretColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCaretColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCaretColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetType));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetType));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMaxLines));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMaxLines));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPlaceholderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPlaceholderColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPlaceholderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPlaceholderColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCaretPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCaretPosition));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCaretPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCaretPosition));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCopyOption));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCopyOption));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowPasswordIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowPasswordIcon));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowPasswordIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowPasswordIcon));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPasswordIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPasswordIcon));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPasswordIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPasswordIcon));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextAlign));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextAlign));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetStyle));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetStyle));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectionMenuHidden"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectionMenuHidden));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectionMenuHidden"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectionMenuHidden));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowUnderline"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextInputShowUnderline));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowUnderline"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextInputShowUnderline));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCaretStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCaretStyle));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCaretStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCaretStyle));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableKeyboardOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnableKeyboardOnFocus));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableKeyboardOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnableKeyboardOnFocus));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetBarState));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetBarState));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnterKeyType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextInputEnterKeyType));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnterKeyType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextInputEnterKeyType));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextInputFontWeight));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextInputFontWeight));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontSize));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontSize));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMaxLength));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMaxLength));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectedBackgroundColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectedBackgroundColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowError"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowError));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowError"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowError));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPlaceholderFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPlaceholderFont));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPlaceholderFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPlaceholderFont));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontStyle));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontStyle));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontFamily));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontFamily));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textInput"), textInput);

    auto navDestination = panda::ObjectRef::New(vm);
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetHideTitleBar));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetHideTitleBar));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navDestination"), navDestination);

    RegisterButtonAttributes(object, vm);
    RegisterToggleAttributes(object, vm);
    RegisterDividerAttributes(object, vm);
    RegisterNavigationAttributes(object, vm);
    RegisterImageAttributes(object, vm);
    RegisterNavRouterAttributes(object, vm);
    RegisterNavigatorAttributes(object, vm);
    RegisterNodeContainerAttributes(object, vm);
    RegisterRenderNodeAttributes(object, vm);
    RegisterPanelAttributes(object, vm);
    RegisterLineAttributes(object, vm);
    RegisterPathAttributes(object, vm);
    RegisterPolygonAttributes(object, vm);
    RegisterPolylineAttributes(object, vm);
    RegisterSideBarContainerAttributes(object, vm);
    RegisterCalendarPickerAttributes(object, vm);
    RegisterTabAttributes(object, vm);
    RegisterTabContentAttributes(object, vm);
    RegisterStepperItemAttributes(object, vm);
    RegisterHyperlinkAttributes(object, vm);
    RegisterMenuItemAttributes(object, vm);
    RegisterMenuAttributes(object, vm);
    RegisterMarqueeAttributes(object, vm);
    RegisterDatePickerAttributes(object, vm);
    RegisterAlphabetIndexerAttributes(object, vm);
    RegisterGaugeAttributes(object, vm);
    RegisterSwiperAttributes(object, vm);
    RegisterSelectAttributes(object, vm);
    RegisterRadioAttributes(object, vm);
    RegisterSliderAttributes(object, vm);
    RegisterRatingAttributes(object, vm);
    RegisterTimepickerAttributes(object, vm);
    RegisterTextpickerAttributes(object, vm);
    RegisterWaterFlowAttributes(object, vm);
    RegisterCheckboxAttributes(object, vm);
    RegisterDataPanelAttributes(object, vm);
    RegisterScrollAttributes(object, vm);
    RegisterGridItemAttributes(object, vm);
    RegisterMarqueeAttributes(object, vm);
    RegisterProgressAttributes(object, vm);
    RegisterCommonShapeAttributes(object, vm);
    RegisterShapeAttributes(object, vm);
    RegisterRectAttributes(object, vm);
    RegisterListAttributes(object, vm);
    RegisterGridAttributes(object, vm);
    RegisterLisitItemGroupAttributes(object, vm);
    RegisterQRCodeAttributes(object, vm);
    RegisterLoadingProgressAttributes(object, vm);
    RegisterTextClockAttributes(object, vm);
    RegisterListItemAttributes(object, vm);
    RegisterTextTimerAttributes(object, vm);
    RegisterRenderNodeAttributes(object, vm);
#ifdef PLUGIN_COMPONENT_SUPPORTED
    RegisterPluginAttributes(object, vm);
#endif
#ifdef XCOMPONENT_SUPPORTED
    RegisterXComponentAttributes(object, vm);
    RegisterXComponentNodeAttributes(object, vm);
#endif

#ifdef FORM_SUPPORTED
    RegisterFormAttributes(object, vm);
#endif

    return object;
}

void ArkUINativeModule::RegisterCheckboxAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto checkbox = panda::ObjectRef::New(vm);
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMark"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetMark));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMark"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetMark));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setUnSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetUnSelectedColor));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetUnSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetUnSelectedColor));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetSelect));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetSelect));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetSelectedColor));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetSelectedColor));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxWidth));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxWidth));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxHeight));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxHeight));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxSize));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxSize));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxResponseRegion));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxResponseRegion));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CheckboxBridge::SetCheckboxPadding));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CheckboxBridge::ResetCheckboxPadding));

    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "checkbox"), checkbox);
}

void ArkUINativeModule::RegisterTextpickerAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto textpicker = panda::ObjectRef::New(vm);
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCanLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetCanLoop));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetSelectedIndex));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetSelectedTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetDisappearTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDefaultPickerItemHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetDefaultPickerItemHeight));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::SetBackgroundColor));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCanLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetCanLoop));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetSelectedIndex));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetSelectedTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetDisappearTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDefaultPickerItemHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetDefaultPickerItemHeight));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextpickerBridge::ResetBackgroundColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textpicker"), textpicker);
}

void ArkUINativeModule::RegisterTimepickerAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto timepicker = panda::ObjectRef::New(vm);
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetSelectedTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetDisappearTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetSelectedTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetDisappearTextStyle));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTimepickerBackgroundColor));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTimepickerBackgroundColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "timepicker"), timepicker);
}

void ArkUINativeModule::RegisterRatingAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto rating = panda::ObjectRef::New(vm);
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStars"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetStars));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStars"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetStars));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStepSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetRatingStepSize));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStepSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetRatingStepSize));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStarStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetStarStyle));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStarStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetStarStyle));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "rating"), rating);
}

void ArkUINativeModule::RegisterSliderAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto slider = panda::ObjectRef::New(vm);
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowTips"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetShowTips));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowTips"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetShowTips));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStepSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSliderStepSize));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStepSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSliderStepSize));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockSize));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockSize));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTrackBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetTrackBorderRadius));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTrackBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetTrackBorderRadius));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStepColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetStepColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStepColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetStepColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockBorderColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockBorderColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockBorderWidth));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockBorderWidth));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTrackBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetTrackBackgroundColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTrackBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetTrackBackgroundColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSelectColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSelectColor));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowSteps"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetShowSteps));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowSteps"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetShowSteps));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setThickness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetThickness));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetThickness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetThickness));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlockStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetBlockStyle));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlockStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetBlockStyle));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "slider"), slider);
}

void ArkUINativeModule::RegisterRadioAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto radio = panda::ObjectRef::New(vm);
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioChecked"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioChecked));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioChecked"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioChecked));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioStyle));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioStyle));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioWidth));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioWidth));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioHeight));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioHeight));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioSize));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioSize));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioHoverEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioHoverEffect));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioHoverEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioHoverEffect));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioPadding));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioPadding));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioResponseRegion));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioResponseRegion));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "radio"), radio);
}

void ArkUINativeModule::RegisterSelectAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto select = panda::ObjectRef::New(vm);
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSpace));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetValue));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelected));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedOptionBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionBgColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptionBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionBgColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptionFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedOptionFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setArrowPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetArrowPosition));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuAlign));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptionFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedOptionFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectedOptionFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetArrowPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetArrowPosition));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuAlign));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptionFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedOptionFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionFont));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSpace));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetValue));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelected));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedOptionBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionBgColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptionBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionBgColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptionFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedOptionFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectedOptionFontColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptionWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionWidth));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptionWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionWidth));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptionHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptionHeight));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptionHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetOptionHeight));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetWidth));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetWidth));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetHeight));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetHeight));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSize));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSize));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "select"), select);
}

void ArkUINativeModule::RegisterPanelAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto panel = panda::ObjectRef::New(vm);
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPanelMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelMode));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPanelMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelMode));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPanelFullHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelFullHeight));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPanelFullHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelFullHeight));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPanelHalfHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelHalfHeight));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPanelHalfHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelHalfHeight));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPanelMiniHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelMiniHeight));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPanelMiniHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelMiniHeight));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPanelBackgroundMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelBackgroundMask));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPanelBackgroundMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelBackgroundMask));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPanelType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelType));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPanelType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelType));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPanelCustomHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetPanelCustomHeight));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPanelCustomHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetPanelCustomHeight));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowCloseIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetShowCloseIcon));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowCloseIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetShowCloseIcon));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDragBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetDragBar));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDragBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetDragBar));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::SetShow));
    panel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PanelBridge::ResetShow));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "panel"), panel);
}

void ArkUINativeModule::RegisterButtonAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto button = panda::ObjectRef::New(vm);
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetType));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetType));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStateEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetStateEffect));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStateEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetStateEffect));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontColor));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontColor));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontSize));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontSize));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontWeight));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontWeight));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetFontFamily));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetFontFamily));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLabelStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetLabelStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLabelStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetLabelStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetBackgroundColor));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetBackgroundColor));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetButtonBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonBorderRadius));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setButtonBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonBorderRadius));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "button"), button);
}

void ArkUINativeModule::RegisterToggleAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto toggle = panda::ObjectRef::New(vm);
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetSelectedColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetSelectedColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwitchPointColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetSwitchPointColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwitchPointColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetSwitchPointColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "toggle"), toggle);
}

void ArkUINativeModule::RegisterDividerAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto divider = panda::ObjectRef::New(vm);
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::SetStrokeWidth));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::ResetStrokeWidth));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineCap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::SetLineCap));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineCap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::ResetLineCap));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::SetColor));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::ResetColor));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::SetVertical));
    divider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), DividerBridge::ResetVertical));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "divider"), divider);
}

void ArkUINativeModule::RegisterGridAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto grid = panda::ObjectRef::New(vm);
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetColumnsTemplate));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetColumnsTemplate));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRowsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetRowsTemplate));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRowsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetRowsTemplate));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetColumnsGap));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetColumnsGap));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetRowsGap));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetRowsGap));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetScrollBar));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetScrollBar));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetScrollBarWidth));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetScrollBarWidth));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBarColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetScrollBarColor));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBarColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetScrollBarColor));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCachedCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetCachedCount));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCachedCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetCachedCount));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEditMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetEditMode));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEditMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetEditMode));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMultiSelectable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetMultiSelectable));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMultiSelectable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetMultiSelectable));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetMaxCount));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetMaxCount));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetMinCount));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetMinCount));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCellLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetCellLength));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCellLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetCellLength));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLayoutDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetLayoutDirection));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLayoutDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetLayoutDirection));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSupportAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetSupportAnimation));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSupportAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetSupportAnimation));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetEdgeEffect));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetEdgeEffect));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetNestedScroll));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetNestedScroll));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetEnableScroll));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetEnableScroll));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetFriction));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetFriction));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "grid"), grid);
}

void ArkUINativeModule::RegisterNavigationAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto navigation = panda::ObjectRef::New(vm);
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideToolBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideToolBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideToolBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideToolBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTitleMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetTitleMode));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTitleMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetTitleMode));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideBackButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideBackButton));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideBackButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideBackButton));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSubTitle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetSubtitle));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSubTitle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetSubtitle));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideNavBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideNavBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideNavBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideNavBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetUsrNavigationMode));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetUsrNavigationMode));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNavBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetNavBarPosition));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNavBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetNavBarPosition));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNavBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetNavBarWidth));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNavBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetNavBarWidth));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNavBarWidthRange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetNavBarWidthRange));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNavBarWidthRange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetNavBarWidthRange));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinContentWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetMinContentWidth));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinContentWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetMinContentWidth));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideTitleBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideTitleBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackButtonIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetBackButtonIcon));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackButtonIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetBackButtonIcon));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navigation"), navigation);
}

void ArkUINativeModule::RegisterImageAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto image = panda::ObjectRef::New(vm);
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetCopyOption));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCopyOption"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetCopyOption));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoResize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetAutoResize));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoResize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetAutoResize));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectRepeat"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetObjectRepeat));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectRepeat"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetObjectRepeat));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetRenderMode));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetRenderMode));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSyncLoad"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetSyncLoad));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSyncLoad"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetSyncLoad));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetObjectFit));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetObjectFit));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFitOriginalSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetFitOriginalSize));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFitOriginalSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetFitOriginalSize));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSourceSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetSourceSize));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSourceSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetSourceSize));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMatchTextDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetMatchTextDirection));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMatchTextDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetMatchTextDirection));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFillColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetFillColor));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFillColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetFillColor));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlt"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetAlt));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlt"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetAlt));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageInterpolation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetImageInterpolation));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageInterpolation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetImageInterpolation));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColorFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetColorFilter));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColorFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetColorFilter));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSyncLoad"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetSyncLoad));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSyncLoad"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetSyncLoad));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetObjectFit));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetObjectFit));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFitOriginalSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetFitOriginalSize));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFitOriginalSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetFitOriginalSize));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetDraggable));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetDraggable));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetBorderRadius));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetBorderRadius));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "image"), image);
}

void ArkUINativeModule::RegisterNavRouterAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto navRouter = panda::ObjectRef::New(vm);
    navRouter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavRouterBridge::SetMode));
    navRouter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavRouterBridge::ResetMode));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navRouter"), navRouter);
}

void ArkUINativeModule::RegisterNavigatorAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto navigator = panda::ObjectRef::New(vm);
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTarget"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetTarget));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTarget"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetTarget));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetType));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetType));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setActive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetActive));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetActive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetActive));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setParams"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::SetParams));
    navigator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetParams"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigatorBridge::ResetParams));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navigator"), navigator);
}

void ArkUINativeModule::RegisterNodeContainerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto nodeContainer = panda::ObjectRef::New(vm);
    nodeContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "rebuild"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeContainerBridge::Rebuild));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "nodeContainer"), nodeContainer);
}

void ArkUINativeModule::RegisterRenderNodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto renderNode = panda::ObjectRef::New(vm);
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "appendChild"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::AppendChild));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "insertChildAfter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::InsertChildAfter));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "removeChild"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::RemoveChild));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "clearChildren"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::ClearChildren));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setClipToFrame"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetClipToFrame));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRotation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetRotation));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShadowColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetShadowColor));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShadowOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetShadowOffset));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShadowAlpha"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetShadowAlpha));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShadowElevation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetShadowElevation));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShadowRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetShadowRadius));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "invalidate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::Invalidate));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetScale));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetBackgroundColor));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPivot"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetPivot));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFrame"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetFrame));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetSize));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetOpacity));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTranslate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetTranslate));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "renderNode"), renderNode);
}

void ArkUINativeModule::RegisterLineAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto line = panda::ObjectRef::New(vm);
    line->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStartPoint"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::SetStartPoint));
    line->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStartPoint"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::ResetStartPoint));
    line->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEndPoint"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::SetEndPoint));
    line->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEndPoint"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LineBridge::ResetEndPoint));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "line"), line);
}

void ArkUINativeModule::RegisterPathAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto path = panda::ObjectRef::New(vm);
    path->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPathCommands"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PathBridge::SetPathCommands));
    path->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPathCommands"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PathBridge::ResetPathCommands));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "path"), path);
}

void ArkUINativeModule::RegisterPolygonAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto polygon = panda::ObjectRef::New(vm);
    polygon->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPolygonPoints"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PolygonBridge::SetPolygonPoints));
    polygon->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPolygonPoints"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PolygonBridge::ResetPolygonPoints));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "polygon"), polygon);
}

void ArkUINativeModule::RegisterPolylineAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto polyline = panda::ObjectRef::New(vm);
    polyline->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPoints"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PolylineBridge::SetPoints));
    polyline->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPoints"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PolylineBridge::ResetPoints));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "polyline"), polyline);
}

void ArkUINativeModule::RegisterSideBarContainerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto sideBarContainer = panda::ObjectRef::New(vm);
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSideBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetSideBarWidth));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSideBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetSideBarWidth));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinSideBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetMinSideBarWidth));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinSideBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetMinSideBarWidth));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setControlButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetControlButton));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetControlButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetControlButton));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowControlButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetShowControlButton));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowControlButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetShowControlButton));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoHide"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetAutoHide));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoHide"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetAutoHide));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxSideBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetMaxSideBarWidth));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxSideBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetMaxSideBarWidth));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinContentWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetMinContentWidth));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinContentWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetMinContentWidth));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSideBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetSideBarPosition));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSideBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetSideBarPosition));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowSideBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetShowSideBar));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowSideBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetShowSideBar));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::SetDivider));
    sideBarContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SideBarContainerBridge::ResetDivider));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "sideBarContainer"), sideBarContainer);
}

void ArkUINativeModule::RegisterCalendarPickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto calendarPicker = panda::ObjectRef::New(vm);
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetTextStyle));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetTextStyle));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEdgeAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetEdgeAlign));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEdgeAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetEdgeAlign));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCalendarPickerPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerPadding));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCalendarPickerPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerPadding));
        calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCalendarPickerBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerBorder));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCalendarPickerBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerBorder));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "calendarPicker"), calendarPicker);
}

void ArkUINativeModule::RegisterMenuItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto menuitem = panda::ObjectRef::New(vm);
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuItemSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::SetMenuItemSelected));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuItemSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::ResetMenuItemSelected));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLabelFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::SetLabelFontColor));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLabelFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::ResetLabelFontColor));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::SetContentFontColor));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContentFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::ResetContentFontColor));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLabelFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::SetLabelFont));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLabelFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::ResetLabelFont));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::SetContentFont));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContentFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::ResetContentFont));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "menuitem"), menuitem);
}

void ArkUINativeModule::RegisterMenuAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto menu = panda::ObjectRef::New(vm);
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetMenuFontColor));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetMenuFontColor));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetFont));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetFont));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetRadius));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetRadius));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "menu"), menu);
}

void ArkUINativeModule::RegisterTabAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto tabs = panda::ObjectRef::New(vm);
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabBarMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabBarMode));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabBarMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabBarMode));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollableBarModeOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetScrollableBarModeOptions));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollableBarModeOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetScrollableBarModeOptions));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarGridAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarGridAlign));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarGridAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarGridAlign));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetDivider));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetDivider));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFadingEdge"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetFadingEdge));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFadingEdge"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetFadingEdge));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarBackgroundColor));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarBackgroundColor));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarOverlap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarOverlap));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarOverlap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarOverlap));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setIsVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetIsVertical));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetIsVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetIsVertical));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabBarWidth));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabBarWidth));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabBarPosition));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabBarPosition));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetScrollable));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetScrollable));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabBarHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabBarHeight));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabBarHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabBarHeight));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarAdaptiveHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarAdaptiveHeight));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarAdaptiveHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarAdaptiveHeight));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAnimationDuration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetAnimationDuration));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAnimationDuration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetAnimationDuration));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarPosition));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarPosition));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabClip));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabClip));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "tabs"), tabs);
}

void ArkUINativeModule::RegisterStepperItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto stepperItem = panda::ObjectRef::New(vm);
    stepperItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNextLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::SetNextLabel));
    stepperItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNextLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::ResetNextLabel));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "stepperItem"), stepperItem);
}

void ArkUINativeModule::RegisterTabContentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto tabContent = panda::ObjectRef::New(vm);
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabContentWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentWidth));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabContentHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentHeight));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabContentSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentSize));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabContentWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentWidth));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabContentHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentHeight));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabContentSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentSize));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "tabContent"), tabContent);
}

void ArkUINativeModule::RegisterHyperlinkAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto hyperlink = panda::ObjectRef::New(vm);
    hyperlink->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::SetColor));
    hyperlink->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::ResetColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "hyperlink"), hyperlink);
}

#ifdef FORM_SUPPORTED
void ArkUINativeModule::RegisterFormAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto formComponent = panda::ObjectRef::New(vm);
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVisibility"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::SetVisibility));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVisibility"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::ResetVisibility));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAllowUpdate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::AllowUpdate));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAllowUpdate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::DisallowUpdate));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDimension"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::SetDimension));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDimension"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::ResetDimension));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setModuleName"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::SetModuleName));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetModuleName"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::ResetModuleName));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::SetSize));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FormComponentBridge::ResetSize));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "formComponent"), formComponent);
}
#endif

void ArkUINativeModule::RegisterDatePickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto datePicker = panda::ObjectRef::New(vm);
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetSelectedTextStyle));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetSelectedTextStyle));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetTextStyle));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetTextStyle));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetDisappearTextStyle));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetDisappearTextStyle));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLunar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetLunar));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLunar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetLunar));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetBackgroundColor));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetBackgroundColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "datePicker"), datePicker);
}

void ArkUINativeModule::RegisterWaterFlowAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto waterflow = panda::ObjectRef::New(vm);
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetColumnsTemplate));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetColumnsTemplate));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRowsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetRowsTemplate));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRowsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetRowsTemplate));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableScrollInteraction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetEnableScrollInteraction));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableScrollInteraction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetEnableScrollInteraction));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetColumnsGap));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetColumnsGap));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetRowsGap));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetRowsGap));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setItemConstraintSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetItemConstraintSize));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetItemConstraintSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetItemConstraintSize));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLayoutDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetLayoutDirection));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLayoutDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetLayoutDirection));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetNestedScroll));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetNestedScroll));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetFriction));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetFriction));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "waterFlow"), waterflow);
}

void ArkUINativeModule::RegisterAlphabetIndexerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto alphabetIndexer = panda::ObjectRef::New(vm);
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupItemFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupItemFont));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupItemFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupItemFont));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetSelectedFont));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetSelectedFont));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupFont));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupFont));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetFont));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetFont));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupItemBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupItemBackgroundColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupItemBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupItemBackgroundColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetSelectedColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetSelectedColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupBackground"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupBackground));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupBackground"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupBackground));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetSelectedBackgroundColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetSelectedBackgroundColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupUnselectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupUnselectedColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupUnselectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupUnselectedColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupSelectedColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupSelectedColor));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetAlignStyle));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetAlignStyle));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setUsingPopup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetUsingPopup));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetUsingPopup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetUsingPopup));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetSelected));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetSelected));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setItemSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetItemSize));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetItemSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetItemSize));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupPosition));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupPosition));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "alphabetIndexer"), alphabetIndexer);
}

void ArkUINativeModule::RegisterGaugeAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto gauge = panda::ObjectRef::New(vm);
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugeVaule"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetGaugeVaule));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugeVaule"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetGaugeVaule));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugeStartAngle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetGaugeStartAngle));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugeStartAngle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetGaugeStartAngle));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugeEndAngle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetGaugeEndAngle));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugeEndAngle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetGaugeEndAngle));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugeStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetGaugeStrokeWidth));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugeStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetGaugeStrokeWidth));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugeTrackShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetGaugeTrackShadow));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugeTrackShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetGaugeTrackShadow));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugeIndicator"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetGaugeIndicator));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugeIndicator"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetGaugeIndicator));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugeColors"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetColors));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugeColors"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetColors));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gauge"), gauge);
}
void ArkUINativeModule::RegisterMarqueeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto marquee = panda::ObjectRef::New(vm);
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAllowScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), MarqueeBridge::SetAllowScale));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAllowScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), MarqueeBridge::ResetAllowScale));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), MarqueeBridge::SetFontWeight));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), MarqueeBridge::ResetFontWeight));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), MarqueeBridge::SetFontFamily));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), MarqueeBridge::ResetFontFamily));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetFontSize));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetFontSize));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetFontColor));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetFontColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "marquee"), marquee);
}

void ArkUINativeModule::RegisterDataPanelAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto dataPanel = panda::ObjectRef::New(vm);
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCloseEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetCloseEffect));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCloseEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetCloseEffect));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDataPanelTrackBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetDataPanelTrackBackgroundColor));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDataPanelTrackBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetDataPanelTrackBackgroundColor));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDataPanelStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetDataPanelStrokeWidth));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDataPanelStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetDataPanelStrokeWidth));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDataPanelValueColors"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetValueColors));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDataPanelValueColors"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetValueColors));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDataPanelTrackShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetTrackShadow));
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDataPanelTrackShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::ResetTrackShadow));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "dataPanel"), dataPanel);
}

void ArkUINativeModule::RegisterScrollAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto scroll = panda::ObjectRef::New(vm);
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetNestedScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetNestedScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetEnableScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetEnableScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetFriction));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetFriction));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollSnap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetScrollSnap));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollSnap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetScrollSnap));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetScrollBar));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetScrollBar));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetScrollable));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetScrollable));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBarColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetScrollBarColor));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBarColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetScrollBarColor));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetScrollBarWidth));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetScrollBarWidth));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetEdgeEffect));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetEdgeEffect));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "scroll"), scroll);
}

void ArkUINativeModule::RegisterGridItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto gridItem = panda::ObjectRef::New(vm);
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridItemSelectable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::SetGridItemSelectable));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridItemSelectable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::ResetGridItemSelectable));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridItemSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::SetGridItemSelected));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridItemSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::ResetGridItemSelected));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridItemRowStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::SetGridItemRowStart));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridItemRowStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::ResetGridItemRowStart));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridItemRowEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::SetGridItemRowEnd));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridItemRowEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::ResetGridItemRowEnd));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridItemColumnStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::SetGridItemColumnStart));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridItemColumnStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::ResetGridItemColumnStart));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridItemColumnEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::SetGridItemColumnEnd));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridItemColumnEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::ResetGridItemColumnEnd));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridItem"), gridItem);
}

void ArkUINativeModule::RegisterProgressAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto progress = panda::ObjectRef::New(vm);
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetProgressValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressValue));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "ResetProgressValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressValue));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setProgressColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressColor));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetProgressColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressColor));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "ResetProgressStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressStyle));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "SetProgressStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressStyle));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setProgressBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ProgressBridge::SetProgressBackgroundColor));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetProgressBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ProgressBridge::ResetProgressBackgroundColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "progress"), progress);
}

#ifdef PLUGIN_COMPONENT_SUPPORTED
void ArkUINativeModule::RegisterPluginAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto plugin = panda::ObjectRef::New(vm);
    plugin->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PluginBridge::SetSize));
    plugin->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PluginBridge::ResetSize));
    plugin->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PluginBridge::SetWidth));
    plugin->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PluginBridge::ResetWidth));
    plugin->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PluginBridge::SetHeight));
    plugin->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PluginBridge::ResetHeight));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "plugin"), plugin);
}
#endif

void ArkUINativeModule::RegisterCommonShapeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto commonShape = panda::ObjectRef::New(vm);
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeDashArray"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeDashArray));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeDashArray"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeDashArray));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeMiterLimit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeMiterLimit));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeMiterLimit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeMiterLimit));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFillOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetFillOpacity));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFillOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetFillOpacity));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeOpacity));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeOpacity));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeWidth));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeWidth));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAntiAlias"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetAntiAlias));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAntiAlias"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetAntiAlias));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStroke"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStroke));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStroke"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStroke));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFill"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetFill));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFill"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetFill));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeDashOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeDashOffset));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeDashOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeDashOffset));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeLineCap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeLineCap));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeLineCap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeLineCap));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStrokeLineJoin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetStrokeLineJoin));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStrokeLineJoin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetStrokeLineJoin));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetHeight));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetHeight));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetWidth));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetWidth));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::SetForegroundColor));
    commonShape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonShapeBridge::ResetForegroundColor));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "commonShape"), commonShape);
}

void ArkUINativeModule::RegisterShapeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto shape = panda::ObjectRef::New(vm);
    shape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShapeViewPort"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::SetViewPort));
    shape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShapeViewPort"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::ResetViewPort));
    shape->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShapeMesh"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::SetMesh));
    shape->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShapeMesh"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ShapeBridge::ResetMesh));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "shape"), shape);
}

void ArkUINativeModule::RegisterRectAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto rect = panda::ObjectRef::New(vm);
    rect->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRectRadiusWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::SetRadiusWidth));
    rect->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRectRadiusWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::ResetRadiusWidth));
    rect->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRectRadiusHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::SetRadiusHeight));
    rect->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRectRadiusHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::ResetRadiusHeight));
    rect->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRectRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::SetRadius));
    rect->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRectRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RectBridge::ResetRadius));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "rect"), rect);
}

void ArkUINativeModule::RegisterSwiperAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto swiper = panda::ObjectRef::New(vm);
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperNextMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperNextMargin));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperNextMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperNextMargin));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperPrevMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperPrevMargin));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperPrevMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperPrevMargin));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperDisplayCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisplayCount));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperDisplayCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisplayCount));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperDisplayArrow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisplayArrow));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperDisplayArrow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisplayArrow));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperCurve"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperCurve));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperCurve"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperCurve));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperDisableSwipe"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisableSwipe));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperDisableSwipe"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisableSwipe));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperEffectMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperEffectMode));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperEffectMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperEffectMode));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperCachedCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperCachedCount));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperCachedCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperCachedCount));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperDisplayMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisplayMode));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperDisplayMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisplayMode));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperItemSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperItemSpace));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperItemSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperItemSpace));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperVertical));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperVertical));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperLoop));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperLoop));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperInterval"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperInterval));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperInterval"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperInterval));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperAutoPlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperAutoPlay));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperAutoPlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperAutoPlay));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperIndex));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperIndex));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperIndicator"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperIndicator));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperIndicator"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperIndicator));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperDuration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDuration));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperDuration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDuration));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperEnabled"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperEnabled));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperEnabled"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperEnabled));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "swiper"), swiper);
}

void ArkUINativeModule::RegisterListItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto listItem = panda::ObjectRef::New(vm);
    listItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListItemSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemBridge::SetListItemSelected));
    listItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListItemSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemBridge::ResetListItemSelected));
    listItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemBridge::SetSelectable));
    listItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemBridge::ResetSelectable));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "listItem"), listItem);
}

void ArkUINativeModule::RegisterListAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto list = panda::ObjectRef::New(vm);
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEditMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetEditMode));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEditMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetEditMode));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMultiSelectable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetMultiSelectable));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMultiSelectable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetMultiSelectable));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setChainAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetChainAnimation));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetChainAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetChainAnimation));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCachedCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetCachedCount));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCachedCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetCachedCount));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableScrollInteraction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetEnableScrollInteraction));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableScrollInteraction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetEnableScrollInteraction));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSticky"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetSticky));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSticky"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetSticky));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSticky"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetSticky));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSticky"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetSticky));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListEdgeEffect));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListEdgeEffect));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListDirection));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListDirection));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListFriction));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListFriction));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListNestedScroll));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListNestedScroll));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListScrollBar));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListScrollBar));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignListItem"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetAlignListItem));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignListItem"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetAlignListItem));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollSnapAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetScrollSnapAlign));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollSnapAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetScrollSnapAlign));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetDivider));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetDivider));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setChainAnimationOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetChainAnimationOptions));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetChainAnimationOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetChainAnimationOptions));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListLanes"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListLanes));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListLanes"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListLanes));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "list"), list);
}

void ArkUINativeModule::RegisterLisitItemGroupAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto listItemGroup = panda::ObjectRef::New(vm);
    listItemGroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListeItemGroupBridege::SetDivider));
    listItemGroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListeItemGroupBridege::ResetDivider));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "listItemGroup"), listItemGroup);
}

void ArkUINativeModule::RegisterQRCodeAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto qrcode = panda::ObjectRef::New(vm);
    qrcode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setQRColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), QRCodeBridge::SetQRColor));
    qrcode->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetQRColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), QRCodeBridge::ResetQRColor));
    qrcode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setQRBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), QRCodeBridge::SetQRBackgroundColor));
    qrcode->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetQRBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), QRCodeBridge::ResetQRBackgroundColor));
    qrcode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), QRCodeBridge::SetContentOpacity));
    qrcode->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContentOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), QRCodeBridge::ResetContentOpacity));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "qrcode"), qrcode);
}

void ArkUINativeModule::RegisterLoadingProgressAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto loadingProgress = panda::ObjectRef::New(vm);
    loadingProgress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::SetColor));
    loadingProgress->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::ResetColor));
    loadingProgress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableLoading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::SetEnableLoading));
    loadingProgress->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableLoading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::ResetEnableLoading));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadingProgress"), loadingProgress);
}

void ArkUINativeModule::RegisterTextClockAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto textClock = panda::ObjectRef::New(vm);
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFormat"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFormat));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFormat"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFormat));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontColor));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontColor));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontSize));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontSize));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontStyle));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontStyle));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontWeight));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontWeight));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontFamily));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontFamily));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textClock"), textClock);
}

void ArkUINativeModule::RegisterTextTimerAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto textTimer = panda::ObjectRef::New(vm);
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::SetFontColor));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::ResetFontColor));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::SetFontSize));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::ResetFontSize));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::SetFontWeight));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::ResetFontWeight));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::SetFontStyle));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::ResetFontStyle));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::SetFontFamily));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFamily"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::ResetFontFamily));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFormat"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::SetFormat));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFormat"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::ResetFormat));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textTimer"), textTimer);
}
#ifdef XCOMPONENT_SUPPORTED
void ArkUINativeModule::RegisterXComponentAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto xComponent = panda::ObjectRef::New(vm);
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBackgroundColor));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetBackgroundColor));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetOpacity));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetOpacity));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "xComponent"), xComponent);
}

void ArkUINativeModule::RegisterXComponentNodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto xcomponentNode = panda::ObjectRef::New(vm);
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "create"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::Create));
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFrameNode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::GetFrameNode));
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerOnCreateCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::RegisterOnCreateCallback));
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerOnDestroyCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::RegisterOnDestroyCallback));
    xcomponentNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "changeRenderType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentNodeBridge::ChangeRenderType));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "xcomponentNode"), xcomponentNode);
}
#endif
} // namespace OHOS::Ace::NG
