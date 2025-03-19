/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "jsnapi_expo.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_badge_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_blank_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_button_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkbox_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_checkboxgroup_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#ifdef MODEL_COMPONENT_SUPPORTED
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_component3d_bridge.h"
#endif
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_animator_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_counter_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_divider_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_flex_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_col_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_row_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_item_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_hyperlink_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_indicator_component_bridge.h"
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_node_adapter_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_panel_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_node_container_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_pattern_lock_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_progress_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_resource_bridge.h"
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_folder_stack_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_slider_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_span_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_symbol_glyph_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_symbol_span_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_textpicker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_theme_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_timepicker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rich_editor_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_video_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_stepper_item_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_marquee_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_tabcontent_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_tabs_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_column_split_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_line_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_particle_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_path_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_polygon_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_polyline_bridge.h"
#ifdef QRCODEGEN_SUPPORT
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_qrcode_bridge.h"
#endif
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_side_bar_container_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_calendar_picker_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_water_flow_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_alphabet_indexer_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_data_panel_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_gauge_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scroll_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scrollable_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_marquee_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_shape_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_shape_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rect_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_list_item_group_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_timer_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_refresh_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_relative_container_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_container_span_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_linear_indicator.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_lazy_grid_layout_bridge.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scrollbar_bridge.h"
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
#ifdef WEB_SUPPORTED
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_web_bridge.h"
#endif

namespace OHOS::Ace::NG {
namespace {
void RegisterRenderNodeBorderAndMaskAttributes(Local<panda::ObjectRef> renderNode, EcmaVM* vm)
{
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetBorderStyle));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetBorderWidth));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetBorderColor));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetBorderRadius));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRectMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetRectMask));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCircleMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetCircleMask));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRoundRectMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetRoundRectMask));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOvalMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetOvalMask));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPath"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetCommandPathMask));
}
void RegisterRenderNodeShapeClipAttributes(Local<panda::ObjectRef> renderNode, EcmaVM* vm)
{
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRectClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetRectClip));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCircleClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetCircleClip));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRoundRectClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetRoundRectClip));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOvalClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetOvalClip));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPathClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetCommandPathClip));
}
} // namespace

ArkUINativeModuleValue ArkUINativeModule::PreviewMockComponent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ArkUINativeModule::GetFrameNodeById(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int nodeId = firstArg->ToNumber(vm)->Value();
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getFrameNodeById(nodeId);
    return panda::NativePointerRef::New(vm, nodePtr);
}

ArkUINativeModuleValue ArkUINativeModule::GetFrameNodeByUniqueId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int nodeId = firstArg->ToNumber(vm)->Value();
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getFrameNodeByUniqueId(nodeId);
    if (nodePtr) {
        return panda::NativePointerRef::New(vm, nodePtr);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ArkUINativeModule::GetPageInfoByUniqueId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::ObjectRef::New(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int nodeId = firstArg->ToNumber(vm)->Value();
    auto nodePtr = AceType::DynamicCast<NG::UINode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId));
    auto pageInfo = panda::ObjectRef::New(vm);
    CHECK_NULL_RETURN(nodePtr, pageInfo);

    auto routerPageResult = OHOS::Ace::NG::UIObserverHandler::GetInstance().GetRouterPageState(nodePtr);
    if (routerPageResult) {
        auto jsContext = Framework::JsConverter::ConvertNapiValueToJsVal(routerPageResult->context);
        Local<JSValueRef> routerPageValues[] = { jsContext->GetLocalHandle(),
            panda::NumberRef::New(vm, routerPageResult->index),
            panda::StringRef::NewFromUtf8(vm, routerPageResult->name.c_str()),
            panda::StringRef::NewFromUtf8(vm, routerPageResult->path.c_str()),
            panda::NumberRef::New(vm, static_cast<int32_t>(routerPageResult->state)),
            panda::StringRef::NewFromUtf8(vm, routerPageResult->pageId.c_str()) };
        const char* routerPageKeys[] = { "context", "index", "name", "path", "state", "pageId" };
        auto routerPageObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(routerPageKeys), routerPageKeys,
            routerPageValues);
        pageInfo->Set(vm, panda::StringRef::NewFromUtf8(vm, "routerPageInfo"), routerPageObj);
    }

    auto navDestinationResult = OHOS::Ace::NG::UIObserverHandler::GetInstance().GetNavigationState(nodePtr);
    if (navDestinationResult) {
        Local<JSValueRef> navDestinationValues[] = {
            panda::StringRef::NewFromUtf8(vm, navDestinationResult->navigationId.c_str()),
            panda::StringRef::NewFromUtf8(vm, navDestinationResult->name.c_str()),
            panda::NumberRef::New(vm, static_cast<int32_t>(navDestinationResult->state)),
            panda::NumberRef::New(vm, navDestinationResult->index),
            Framework::JsConverter::ConvertNapiValueToJsVal(navDestinationResult->param)->GetLocalHandle(),
            panda::StringRef::NewFromUtf8(vm, navDestinationResult->navDestinationId.c_str()),
            panda::NumberRef::New(vm, static_cast<int32_t>(navDestinationResult->mode)),
            panda::NumberRef::New(vm, navDestinationResult->uniqueId) };
        const char* navDestinationKeys[] = { "navigationId", "name", "state", "index", "param", "navDestinationId",
            "mode", "uniqueId" };
        auto navDestinationObj = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(navDestinationKeys),
            navDestinationKeys, navDestinationValues);
        pageInfo->Set(vm, panda::StringRef::NewFromUtf8(vm, "navDestinationInfo"), navDestinationObj);
    }

    return pageInfo;
}

ArkUINativeModuleValue ArkUINativeModule::GetNavigationInfoByUniqueId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::ObjectRef::New(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    int nodeId = firstArg->ToNumber(vm)->Value();
    auto nodePtr = AceType::DynamicCast<NG::UINode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId));
    auto defaultResult = panda::JSValueRef::Undefined(vm);
    CHECK_NULL_RETURN(nodePtr, defaultResult);

    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, defaultResult);
    auto navigationMgr = pipeline->GetNavigationManager();
    CHECK_NULL_RETURN(navigationMgr, defaultResult);
    auto result = navigationMgr->GetNavigationInfo(nodePtr);
    CHECK_NULL_RETURN(result, defaultResult);
    auto jsStack = AceType::DynamicCast<Framework::JSNavigationStack>(result->pathStack.Upgrade());
    CHECK_NULL_RETURN(jsStack, defaultResult);
    Framework::JSRef<Framework::JSObject> navPathStackObj = jsStack->GetDataSourceObj();
    CHECK_NULL_RETURN(!navPathStackObj->IsEmpty(), defaultResult);
    auto obj = panda::ObjectRef::New(vm);
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "navigationId"),
        panda::StringRef::NewFromUtf8(vm, result->navigationId.c_str()));
    obj->Set(vm, panda::StringRef::NewFromUtf8(vm, "pathStack"), navPathStackObj->GetLocalHandle());

    return obj;
}

ArkUINativeModuleValue ArkUINativeModule::GetUIState(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int64_t state = GetArkUINodeModifiers()->getUIStateModifier()->getUIState(nativeNode);
    return panda::NumberRef::New(vm, state);
}

ArkUINativeModuleValue ArkUINativeModule::SetSupportedUIState(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto state = secondArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getUIStateModifier()->setSupportedUIState(nativeNode, state);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ArkUINativeModule::GetFrameNodeByKey(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto key = firstArg->ToString(vm)->ToString(vm);
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getFrameNodeByKey(key.c_str());
    if (!nodePtr) {
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::NativePointerRef::New(vm, nodePtr);
}

ArkUINativeModuleValue ArkUINativeModule::GetAttachedFrameNodeById(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto key = firstArg->ToString(vm)->ToString(vm);
    auto nodePtr = GetArkUINodeModifiers()->getFrameNodeModifier()->getAttachedFrameNodeById(key.c_str());
    if (!nodePtr) {
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::NativePointerRef::New(vm, nodePtr);
}

ArkUINativeModuleValue ArkUINativeModule::RequireDynamicSyncScene(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);

    auto sceneId = firstArg->ToString(vm)->ToString(vm);
    auto sceneNode = NG::Inspector::GetFrameNodeByKey(sceneId);

    if (!sceneNode) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto sceneTag = sceneNode->GetTag();
    auto nativeRef = NativeUtilsBridge::CreateWeakRef(vm, sceneNode);
    const char* keys[] = { "nativeRef", "tag" };
    Local<JSValueRef> values[] = { nativeRef, panda::StringRef::NewFromUtf8(vm, sceneTag.c_str()) };
    return panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
}

ArkUINativeModuleValue ArkUINativeModule::SetFrameRateRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    auto swiperNode = firstArg;
    auto obj = secondArg->ToObject(vm);
    auto minValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "min"))->Int32Value(vm);
    auto maxValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "max"))->Int32Value(vm);
    auto expectValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "expected"))->Int32Value(vm);

    auto frameRateRange = AceType::MakeRefPtr<FrameRateRange>(minValue, maxValue, expectValue);
    auto value = thirdArg->Int32Value(vm);
    auto type = static_cast<SwiperDynamicSyncSceneType>(value);
    if (type != SwiperDynamicSyncSceneType::ANIMATE) {
        type = SwiperDynamicSyncSceneType::GESTURE;
    }
    auto nativePointer = swiperNode->ToNativePointer(vm);
    if (nativePointer.IsEmpty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nativePointer->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* swiperFrameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(swiperFrameNode, panda::JSValueRef::Undefined(vm));
    auto swiperPattern = swiperFrameNode->GetPattern();
    CHECK_NULL_RETURN(swiperPattern, panda::JSValueRef::Undefined(vm));
    swiperPattern->SetFrameRateRange(frameRateRange, type);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ArkUINativeModule::SetMarqueeFrameRateRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2); // 2: parameter index
    auto marqueeNode = firstArg;
    auto obj = secondArg->ToObject(vm);
    auto minValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "min"))->Int32Value(vm);
    auto maxValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "max"))->Int32Value(vm);
    auto expectValue = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "expected"))->Int32Value(vm);

    auto frameRateRange = AceType::MakeRefPtr<FrameRateRange>(minValue, maxValue, expectValue);
    auto value = thirdArg->Int32Value(vm);
    auto type = static_cast<MarqueeDynamicSyncSceneType>(value);
    auto nativePointer = marqueeNode->ToNativePointer(vm);
    if (nativePointer.IsEmpty()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(nativePointer->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));
    auto* marqueeFrameNode = reinterpret_cast<NG::FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(marqueeFrameNode, panda::JSValueRef::Undefined(vm));
    MarqueeModelNG::SetMarqueeFrameRateRange(marqueeFrameNode, frameRateRange, type);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ArkUINativeModule::GetArkUINativeModule(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto object = panda::ObjectRef::New(vm);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFrameNodeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetFrameNodeById));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFrameNodeByUniqueId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetFrameNodeByUniqueId));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPageInfoByUniqueId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetPageInfoByUniqueId));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getNavigationInfoByUniqueId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetNavigationInfoByUniqueId));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getUIState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetUIState));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSupportedUIState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SetSupportedUIState));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFrameNodeByKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetFrameNodeByKey));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "getAttachedFrameNodeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GetAttachedFrameNodeById));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "requireDynamicSyncScene"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RequireDynamicSyncScene));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFrameRateRange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SetFrameRateRange));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarqueeFrameRateRange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SetMarqueeFrameRateRange));

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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPointLightStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetPointLightStyle));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPointLightStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetPointLightStyle));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundImageResizable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundImageResizable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundImageResizable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundImageResizable));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBindTips"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBindTips));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBindTips"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBindTips));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBindMenu"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBindMenu));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetClip));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetClip));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setClipShape"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetClipShape));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetClipShape"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetClipShape));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMotionBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetMotionBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMotionBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetMotionBlur));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetTabStop));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetTabStop));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaskShape"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetMaskShape));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaskShape"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetMaskShape));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSafeAreaPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::SetSafeAreaPadding));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSafeAreaPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CommonBridge::ResetSafeAreaPadding));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityRoleType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityRoleType));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityRoleType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityRoleType));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityFocusCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityFocusCallback));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityFocusCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityFocusCallback));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setForegroundEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetForegroundEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetForegroundEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetForegroundEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundBrightness));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundBrightness));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundBrightnessInternal"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBackgroundBrightnessInternal));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundBrightnessInternal"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBackgroundBrightnessInternal));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setForegroundBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetForegroundBrightness));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetForegroundBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetForegroundBrightness));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDragPreviewOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDragPreviewOptions));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDragPreviewOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDragPreviewOptions));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDragPreview"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDragPreview));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDragPreview"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDragPreview));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setUseShadowBatching"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetUseShadowBatching));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetUseShadowBatching"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetUseShadowBatching));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlendMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBlendMode));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlendMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetBlendMode));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMonopolizeEvents"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetMonopolizeEvents));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMonopolizeEvents"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetMonopolizeEvents));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetDraggable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetDraggable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityNextFocusId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityNextFocusId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityNextFocusId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityNextFocusId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityDefaultFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityDefaultFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityUseSamePage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityUseSamePage));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityUseSamePage"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityUseSamePage));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityScrollTriggerable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityScrollTriggerable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityScrollTriggerable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityScrollTriggerable));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityFocusDrawLevel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAccessibilityFocusDrawLevel));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityFocusDrawLevel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAccessibilityFocusDrawLevel));
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
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnClick"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnClick));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnClick"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnClick));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDragStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnDragStart));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDragStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnDragStart));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDragEnter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnDragEnter));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDragEnter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnDragEnter));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDragMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnDragMove));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDragMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnDragMove));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDragLeave"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnDragLeave));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDragLeave"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnDragLeave));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnDrop));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnDrop));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDragEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnDragEnd));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDragEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnDragEnd));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnTouch"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnTouch));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnTouch"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnTouch));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnAppear"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnAppear));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnAppear"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnAppear));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDisappear"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnDisappear));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDisappear"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnDisappear));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnAttach"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnAttach));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnAttach"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnAttach));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDetach"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnDetach));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDetach"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnDetach));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnKeyEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnKeyEvent));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnKeyEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnKeyEvent));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnKeyPreIme"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnKeyPreIme));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnKeyPreIme"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnKeyPreIme));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnFocusAxisEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnFocusAxisEvent));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnFocusAxisEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnFocusAxisEvent));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnFocus));
        common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnBlur));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnHover"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnHover));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnHover"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnHover));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnHoverMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnHoverMove));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnHoverMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnHoverMove));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnMouse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnMouse));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnMouse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnMouse));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnAxisEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnAxisEvent));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnAxisEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnAxisEvent));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSizeChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnSizeChange));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSizeChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnSizeChange));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnAreaChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnAreaChange));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnAreaChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnAreaChange));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnGestureJudgeBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnGestureJudgeBegin));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnGestureJudgeBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnGestureJudgeBegin));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnGestureRecognizerJudgeBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetOnGestureRecognizerJudgeBegin));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnGestureRecognizerJudgeBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetOnGestureRecognizerJudgeBegin));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShouldBuiltInRecognizerParallelWith"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetShouldBuiltInRecognizerParallelWith));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShouldBuiltInRecognizerParallelWith"),
        panda::FunctionRef::New(
            const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetShouldBuiltInRecognizerParallelWith));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addTapGesture"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddTapGesture));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addLongPressGesture"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddLongPressGesture));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addPanGesture"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddPanGesture));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addSwipeGesture"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddSwipeGesture));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addPinchGesture"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddPinchGesture));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addRotationGesture"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddRotationGesture));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addGestureGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddGestureGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addTapGestureToGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddTapGestureToGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addLongPressGestureToGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddLongPressGestureToGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addPanGestureToGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddPanGestureToGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addSwipeGestureToGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddSwipeGestureToGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addPinchGestureToGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddPinchGestureToGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addRotationGestureToGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddRotationGestureToGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "addGestureGroupToGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AddGestureGroupToGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "attachGestureGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::AttachGestureGroup));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "removeGestureByTag"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::RemoveGestureByTag));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "clearGestures"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ClearGestures));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "getWindowName"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::GetWindowName));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "getWindowWidthBreakpoint"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::GetWindowWidthBreakpoint));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "getWindowHeightBreakpoint"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::GetWindowHeightBreakpoint));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "freezeUINodeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::FreezeUINodeById));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "freezeUINodeByUniqueId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::FreezeUINodeByUniqueId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSystemBarEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetSystemBarEffect));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "postFrameCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::PostFrameCallback));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFocusScopeId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFocusScopeId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFocusScopeId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFocusScopeId));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFocusScopePriority"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFocusScopePriority));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFocusScopePriority"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFocusScopePriority));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setChainMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetChainMode));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetChainMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetChainMode));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPixelRound"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetPixelRound));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPixelRound"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetPixelRound));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "greatOrEqualAPITargetVersion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::GreatOrEqualAPITargetVersion));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "lessThanAPITargetVersion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::LessThanAPITargetVersion));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "getApiTargetVersion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::GetApiTargetVersion));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderWithDashParams"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetBorderWithDashParams));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFocusBox"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetFocusBox));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFocusBox"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetFocusBox));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNextFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetNextFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNextFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetNextFocus));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAdvancedBlendMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::SetAdvancedBlendMode));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAdvancedBlendMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::ResetAdvancedBlendMode));
    common->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerFrameNodeDestructorCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CommonBridge::RegisterFrameNodeDestructorCallback));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "common"), common);

    auto nativeUtils = panda::ObjectRef::New(vm);
    nativeUtils->Set(vm, panda::StringRef::NewFromUtf8(vm, "createNativeWeakRef"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::CreateNativeWeakRef));
    nativeUtils->Set(vm, panda::StringRef::NewFromUtf8(vm, "createNativeStrongRef"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::CreateNativeStrongRef));
    nativeUtils->Set(vm, panda::StringRef::NewFromUtf8(vm, "parseResourceColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::ParseResourceColor));
    nativeUtils->Set(vm, panda::StringRef::NewFromUtf8(vm, "blendColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::BlendColor));
    nativeUtils->Set(vm, panda::StringRef::NewFromUtf8(vm, "resoureToLengthMetrics"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NativeUtilsBridge::ResoureToLengthMetrics));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "nativeUtils"), nativeUtils);

    auto nodeAdapter = panda::ObjectRef::New(vm);
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "createAdapter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::CreateNodeAdapter));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCallbacks"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::SetCallbacks));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTotalNodeCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::SetTotalNodeCount));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "getTotalNodeCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::GetTotalNodeCount));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "notifyItemReloaded"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::NotifyItemReloaded));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "notifyItemChanged"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::NotifyItemChanged));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "notifyItemRemoved"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::NotifyItemRemoved));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "notifyItemInserted"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::NotifyItemInserted));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "notifyItemMoved"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::NotifyItemMoved));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "getAllItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::GetAllItems));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "attachNodeAdapter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::AttachNodeAdapter));
    nodeAdapter->Set(vm, panda::StringRef::NewFromUtf8(vm, "detachNodeAdapter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeAdapterBridge::DetachNodeAdapter));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "nodeAdapter"), nodeAdapter);

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
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCounterOnInc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterOnInc));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCounterOnInc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterOnInc));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCounterOnDec"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::SetCounterOnDec));
    counter->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCounterOnDec"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CounterBridge::ResetCounterOnDec));
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
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupStyle));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupStyle));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupOptions));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxGroupOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::SetCheckboxGroupOnChange));
    checkboxgroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxGroupOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxGroupBridge::ResetCheckboxGroupOnChange));
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
    row->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowBridge::SetSpace));
    row->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowBridge::ResetSpace));
    row->Set(vm, panda::StringRef::NewFromUtf8(vm, "setReverse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowBridge::SetReverse));
    row->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetReverse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowBridge::ResetReverse));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "row"), row);

#ifndef ARKUI_WEARABLE
    auto rowSplit = panda::ObjectRef::New(vm);
    rowSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResizeable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowSplitBridge::SetResizable));
    rowSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResizeable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RowSplitBridge::ResetResizable));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "rowSplit"), rowSplit);
#endif

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
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPrivacySensitive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetPrivacySensitive));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPrivacySensitive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetPrivacySensitive));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetMaxFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetMaxFontSize));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetMinFontScale));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetMinFontScale));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetMaxFontScale));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetMaxFontScale));
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
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetContent));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextController"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextController));
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
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetLineSpacing));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetLineSpacing));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFont));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFont));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWordBreak"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetWordBreak));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWordBreak"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetWordBreak));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineBreakStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetLineBreakStrategy));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineBreakStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetLineBreakStrategy));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEllipsisMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetEllipsisMode));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEllipsisMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetEllipsisMode));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableDataDetector"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetEnableDataDetector));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableDataDetector"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetEnableDataDetector));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetFontFeature));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetFontFeature));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetForegroundColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetForegroundColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetSelection));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetSelection));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextSelectableMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetTextSelectableMode));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextSelectableMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetTextSelectableMode));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCaretColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetCaretColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCaretColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetCaretColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetSelectedBackgroundColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetSelectedBackgroundColor));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDataDetectorConfig"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetDataDetectorConfig));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDataDetectorConfig"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetDataDetectorConfig));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetOnCopy));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetOnCopy));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnTextSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetOnTextSelectionChange));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnTextSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetOnTextSelectionChange));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectionMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetSelectionMenuOptions));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectionMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetSelectionMenuOptions));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHalfLeading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetHalfLeading));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHalfLeading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetHalfLeading));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnClick"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetOnClick));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnClick"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetOnClick));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetResponseRegion));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetResponseRegion));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetEnableHapticFeedback));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetEnableHapticFeedback));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarqueeOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetMarqueeOptions));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMarqueeOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetMarqueeOptions));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnMarqueeStateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::SetOnMarqueeStateChange));
    text->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnMarqueeStateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextBridge::ResetOnMarqueeStateChange));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "text"), text);

    auto search = panda::ObjectRef::New(vm);
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSearchInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchInitialize));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSearchInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchInitialize));
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
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSearchEnterKeyType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchEnterKeyType));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSearchEnterKeyType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchEnterKeyType));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSearchHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchHeight));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSearchHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchHeight));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSearchInspectorId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchInspectorId));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSearchInspectorId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchInspectorId));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetDecoration));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetDecoration));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetLetterSpacing));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetLetterSpacing));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetLineHeight));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetLineHeight));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHalfLeading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetHalfLeading));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHalfLeading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetHalfLeading));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetFontFeature));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetFontFeature));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSearchMinFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchMinFontSize));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSearchMinFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchMinFontSize));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSearchMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchMaxFontSize));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSearchMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchMaxFontSize));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetMinFontScale));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetMinFontScale));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetMaxFontScale));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetMaxFontScale));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSelectedBackgroundColor));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSelectedBackgroundColor));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextIndent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetTextIndent));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextIndent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetTextIndent));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInputFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetInputFilter));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInputFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetInputFilter));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetMaxLength));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetMaxLength));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetType));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetType));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnEditChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnEditChange));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnEditChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnEditChange));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSubmit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnSubmit));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSubmit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnSubmit));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnCopy));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnCopy));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnCut));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnCut));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnPaste"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnPaste));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnPaste"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnPaste));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnChange));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnChange));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnTextSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnTextSelectionChange));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnTextSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnTextSelectionChange));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnContentScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnContentScroll));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnContentScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnContentScroll));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowCounter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetShowCounter));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowCounter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetShowCounter));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnWillChange));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnWillChange));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnWillInsert));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnWillInsert));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnDidInsert));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnDidInsert));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnWillDelete));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnWillDelete));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetOnDidDelete));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetOnDidDelete));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnablePreviewText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetEnablePreviewText));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnablePreviewText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetEnablePreviewText));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectionMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSelectionMenuOptions));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectionMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSelectionMenuOptions));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetEnableHapticFeedback));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetEnableHapticFeedback));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoCapitalizationMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetSearchAutoCapitalizationMode));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoCapitalizationMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetSearchAutoCapitalizationMode));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStopBackPress"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetStopBackPress));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStopBackPress"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetStopBackPress));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "setKeyboardAppearance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::SetKeyboardAppearance));
    search->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetKeyboardAppearance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SearchBridge::ResetKeyboardAppearance));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "search"), search);

    auto stack = panda::ObjectRef::New(vm);
    stack->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StackBridge::SetAlignContent));
    stack->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StackBridge::ResetAlignContent));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "stack"), stack);

#ifndef ARKUI_WEARABLE
    auto folderStack = panda::ObjectRef::New(vm);
    folderStack->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::SetEnableAnimation));
    folderStack->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::ResetEnableAnimation));
    folderStack->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoHalfFold"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::SetAutoHalfFold));
    folderStack->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoHalfFold"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FolderStackBridge::ResetAutoHalfFold));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "folderStack"), folderStack);
#endif

    auto imageSpan = panda::ObjectRef::New(vm);
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVerticalAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::SetVerticalAlign));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVerticalAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::ResetVerticalAlign));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::SetObjectFit));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::ResetObjectFit));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextBackgroundStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::SetTextBackgroundStyle));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextBackgroundStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::ResetTextBackgroundStyle));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBaselineOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::SetBaselineOffset));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBaselineOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::ResetBaselineOffset));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlt"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::SetAlt));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlt"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::ResetAlt));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::SetOnComplete));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::ResetOnComplete));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnError"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::SetOnError));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnError"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageSpanBridge::ResetOnError));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColorFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::SetColorFilter));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColorFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::ResetColorFilter));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::SetBorderRadius));
    imageSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageSpanBridge::ResetBorderRadius));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageSpan"), imageSpan);

    auto blank = panda::ObjectRef::New(vm);
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::SetColor));
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::ResetColor));
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlankHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::SetBlankHeight));
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlankHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::ResetBlankHeight));
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBlankMin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::SetBlankMin));
    blank->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBlankMin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BlankBridge::ResetBlankMin));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "blank"), blank);

    auto span = panda::ObjectRef::New(vm);
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSpanSrc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SpanBridge::SetSpanSrc));
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
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetLineHeight));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetFontStyle));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetFontStyle));
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
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBaselineOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetBaselineOffset));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBaselineOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetBaselineOffset));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetFont));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFont"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetFont));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextBackgroundStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetTextBackgroundStyle));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextBackgroundStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetTextBackgroundStyle));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetTextShadow));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetTextShadow));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetAccessibilityText));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetAccessibilityText));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityDescription"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetAccessibilityDescription));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityDescription"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetAccessibilityDescription));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAccessibilityLevel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::SetAccessibilityLevel));
    span->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAccessibilityLevel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), SpanBridge::ResetAccessibilityLevel));
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
    column->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnBridge::SetSpace));
    column->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnBridge::ResetSpace));
    column->Set(vm, panda::StringRef::NewFromUtf8(vm, "setReverse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnBridge::SetReverse));
    column->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetReverse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ColumnBridge::ResetReverse));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "column"), column);

    auto gridRow = panda::ObjectRef::New(vm);
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetAlignItems));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetAlignItems));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetDirection));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetDirection));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBreakpoints"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetBreakpoints));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBreakpoints"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetBreakpoints));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumns"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetColumns));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumns"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetColumns));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGutter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetGutter));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGutter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetGutter));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnBreakpointChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::SetOnBreakpointChange));
    gridRow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnBreakpointChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridRowBridge::ResetOnBreakpointChange));

    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridRow"), gridRow);

    auto richEditor = panda::ObjectRef::New(vm);
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnterKeyType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnterKeyType));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnterKeyType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnterKeyType));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetSelectedBackgroundColor));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetSelectedBackgroundColor));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCaretColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCaretColor));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCaretColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetCaretColor));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnSelectionChange));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnSelectionChange));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableDataDetector"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnableDataDetector));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableDataDetector"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnableDataDetector));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDataDetectorConfig"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetDataDetectorConfig));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDataDetectorConfig"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetDataDetectorConfig));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnIMEInputComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnIMEInputComplete));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnIMEInputComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnIMEInputComplete));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnWillChange));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnWillChange));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnDidChange));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnDidChange));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPlaceholder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetPlaceholder));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPlaceholder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetPlaceholder));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAboutToDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetAboutToDelete));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAboutToDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetAboutToDelete));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSubmit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnSubmit));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSubmit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnSubmit));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAboutToIMEInput"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetAboutToIMEInput));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAboutToIMEInput"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetAboutToIMEInput));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCopyOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetCopyOptions));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCopyOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetCopyOptions));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnSelect));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnSelect));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReady"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnReady));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReady"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnReady));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDeleteComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnDeleteComplete));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDeleteComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnDeleteComplete));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnEditingChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnEditingChange));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnEditingChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnEditingChange));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnPaste"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnPaste));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnPaste"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnPaste));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnCut));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnCut));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetOnCopy));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetOnCopy));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableKeyboardOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnableKeyboardOnFocus));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableKeyboardOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnableKeyboardOnFocus));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnablePreviewText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEnablePreviewText));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnablePreviewText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEnablePreviewText));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEditMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetEditMenuOptions));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEditMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetEditMenuOptions));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetBarState));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarState"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetBarState));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetMaxLength));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLength"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetMaxLength));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetMaxLines));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxLines"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetMaxLines));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStopBackPress"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetStopBackPress));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStopBackPress"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetStopBackPress));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "setKeyboardAppearance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::SetKeyboardAppearance));
    richEditor->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetKeyboardAppearance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RichEditorBridge::ResetKeyboardAppearance));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "richEditor"), richEditor);

    auto linearIndicator = panda::ObjectRef::New(vm);
    linearIndicator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setIndicatorStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LinearIndicatorBridge::SetIndicatorStyle));
    linearIndicator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetIndicatorStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LinearIndicatorBridge::ResetIndicatorStyle));
    linearIndicator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setIndicatorLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LinearIndicatorBridge::SetIndicatorLoop));
    linearIndicator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetIndicatorLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LinearIndicatorBridge::ResetIndicatorLoop));
    linearIndicator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LinearIndicatorBridge::SetOnChange));
    linearIndicator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LinearIndicatorBridge::ResetOnChange));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "linearIndicator"), linearIndicator);

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
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetDecoration));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetDecoration));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetLetterSpacing));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetLetterSpacing));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetLineSpacing));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetLineSpacing));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetLineHeight));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetLineHeight));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHalfLeading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHalfLeading));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHalfLeading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetHalfLeading));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetFontFeature));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetFontFeature));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWordBreak"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetWordBreak));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWordBreak"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetWordBreak));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineBreakStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetLineBreakStrategy));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineBreakStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetLineBreakStrategy));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMinFontSize));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMinFontSize));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxFontSize));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxFontSize));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMinFontScale));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMinFontScale));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMaxFontScale));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMaxFontScale));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeightAdaptivePolicy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetHeightAdaptivePolicy));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeightAdaptivePolicy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetHeightAdaptivePolicy));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetSelectedBackgroundColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetSelectedBackgroundColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCaretStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetCaretStyle));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCaretStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetCaretStyle));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextOverflow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextOverflow));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextOverflow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextOverflow));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextIndent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextIndent));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextIndent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextIndent));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetType));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetType));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetPadding));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetPadding));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnChange));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnChange));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnterKeyType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnterKeyType));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnterKeyType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnterKeyType));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoCapitalizationMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextAreAutoCapitalizationMode));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoCapitalizationMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetTextAreAutoCapitalizationMode));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInputFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetInputFilter));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInputFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetInputFilter));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnTextSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnTextSelectionChange));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnTextSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnTextSelectionChange));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnContentScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnContentScroll));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnContentScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnContentScroll));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnEditChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnEditChange));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnEditChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnEditChange));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnCopy));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnCopy));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnCut));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnCut));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnPaste"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnPaste));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnPaste"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnPaste));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSubmit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnSubmit));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSubmit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnSubmit));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetContentType));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContentType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetContentType));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableAutoFill"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnableAutoFill));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableAutoFill"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnableAutoFill));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorder));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorder));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderWidth));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderWidth));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderStyle));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderStyle));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderRadius));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderRadius));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBackgroundColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBackgroundColor));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetMargin));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetMargin));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillChange));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillChange));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillInsert));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillInsert));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnDidInsert));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnDidInsert));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillDelete));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillDelete));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnDidDelete));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnDidDelete));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnablePreviewText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnablePreviewText));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnablePreviewText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnablePreviewText));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectionMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetSelectionMenuOptions));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectionMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetSelectionMenuOptions));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextAreaInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetTextAreaInitialize));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetWidth));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetWidth));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEnableHapticFeedback));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEnableHapticFeedback));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEllipsisMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetEllipsisMode));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEllipsisMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetEllipsisMode));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStopBackPress"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetStopBackPress));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStopBackPress"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetStopBackPress));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "setKeyboardAppearance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetKeyboardAppearance));
    textArea->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetKeyboardAppearance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetKeyboardAppearance));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textArea"), textArea);

    auto video = panda::ObjectRef::New(vm);
#ifdef PREVIEW
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoPlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoPlay"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setControls"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetControls"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetObjectFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMuted"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMuted"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShortcutKeyEnabled"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShortcutKeyEnabled"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
#else
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
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShortcutKeyEnabled"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetShortcutKeyEnabled));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShortcutKeyEnabled"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetShortcutKeyEnabled));
#endif
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetOpacity));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetOpacity));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVideoSurfaceBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetVideoSurfaceBackgroundColor));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVideoSurfaceBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetVideoSurfaceBackgroundColor));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::SetTransition));
    video->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), VideoBridge::ResetTransition));
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
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setActivateCircleStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockActivateCircleStyle));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetActivateCircleStyle"),
        panda::FunctionRef::New(
            const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockActivateCircleStyle));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSkipUnselectedPoint"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockSkipUnselectedPoint));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSkipUnselectedPoint"),
        panda::FunctionRef::New(
            const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockSkipUnselectedPoint));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPatternLockOnPatternComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockOnPatternComplete));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPatternLockOnPatternComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockOnPatternComplete));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPatternLockOnDotConnect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::SetPatternLockOnDotConnect));
    patternLock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPatternLockOnDotConnect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), PatternLockBridge::ResetPatternLockOnDotConnect));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "patternLock"), patternLock);

#ifndef ARKUI_WEARABLE
    auto columnSplit = panda::ObjectRef::New(vm);
    columnSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ColumnSplitBridge::SetDivider));
    columnSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ColumnSplitBridge::ResetDivider));
    columnSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResizeable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ColumnSplitBridge::SetResizable));
    columnSplit->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResizeable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ColumnSplitBridge::ResetResizable));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "columnSplit"), columnSplit);
#endif

    RegisterImageAnimatorAttributes(object, vm);

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
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowPassword"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowPassword));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowPassword"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowPassword));
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
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPasswordRules"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPasswordRules));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPasswordRules"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPasswordRules));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableAutoFill"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnableAutoFill));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableAutoFill"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnableAutoFill));
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
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoCapitalizationMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextInputAutoCapitalizationMode));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoCapitalizationMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextInputAutoCapitalizationMode));
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
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetDecoration));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDecoration"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetDecoration));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetLetterSpacing));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLetterSpacing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetLetterSpacing));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetLineHeight));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetLineHeight));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHalfLeading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetHalfLeading));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHalfLeading"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetHalfLeading));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setUnderlineColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetUnderlineColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetUnderlineColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetUnderlineColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetFontFeature));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetFontFeature));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWordBreak"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetWordBreak));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWordBreak"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetWordBreak));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLineBreakStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetLineBreakStrategy));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLineBreakStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetLineBreakStrategy));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCancelButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetCancelButton));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCancelButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetCancelButton));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectAll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectAll));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectAll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectAll));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowCounter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowCounter));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowCounter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowCounter));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShowCounter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetShowCounter));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShowCounter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetShowCounter));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnEditChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnEditChange));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnEditChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnEditChange));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInputFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetInputFilter));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInputFilter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetInputFilter));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSubmit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnSubmit));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSubmit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnSubmit));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnChange));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnChange));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnTextSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnTextSelectionChange));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnTextSelectionChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnTextSelectionChange));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnContentScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnContentScroll));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnContentScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnContentScroll));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnCopy));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCopy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnCopy));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnCut));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnCut"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnCut));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnPaste"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetOnPaste));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnPaste"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetOnPaste));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMinFontSize));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMinFontSize));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMaxFontSize));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMaxFontSize));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMinFontScale));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMinFontScale));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMaxFontScale));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMaxFontScale));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeightAdaptivePolicy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetHeightAdaptivePolicy));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeightAdaptivePolicy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetHeightAdaptivePolicy));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextOverflow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextOverflow));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextOverflow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextOverflow));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextIndent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetTextIndent));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextIndent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetTextIndent));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPadding));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPadding));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetContentType));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContentType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetContentType));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorder));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorder));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderWidth));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderWidth));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderStyle));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderStyle));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetBorderRadius));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetBorderRadius));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetBackgroundColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetBackgroundColor));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetMargin));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetMargin));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetText));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetText));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetController"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetController));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setController"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetController));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPlaceholder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetPlaceholder));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPlaceholder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetPlaceholder));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillChange));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillChange));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillInsert));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillInsert));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnDidInsert));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidInsert"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnDidInsert));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnWillDelete));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnWillDelete));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::SetOnDidDelete));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidDelete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextAreaBridge::ResetOnDidDelete));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnablePreviewText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnablePreviewText));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnablePreviewText"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnablePreviewText));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectionMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetSelectionMenuOptions));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectionMenuOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetSelectionMenuOptions));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetWidth));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetWidth));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEnableHapticFeedback));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEnableHapticFeedback));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEllipsisMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetEllipsisMode));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEllipsisMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetEllipsisMode));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStopBackPress"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetStopBackPress));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStopBackPress"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetStopBackPress));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "setKeyboardAppearance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::SetKeyboardAppearance));
    textInput->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetKeyboardAppearance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextInputBridge::ResetKeyboardAppearance));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textInput"), textInput);

    auto navDestination = panda::ObjectRef::New(vm);
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetHideTitleBar));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetHideTitleBar));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideToolBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetHideToolBar));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideToolBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetHideToolBar));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideBackButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetHideBackButton));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideBackButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetHideBackButton));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackButtonIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetBackButtonIcon));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackButtonIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetBackButtonIcon));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetNavDestinationMode));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetNavDestinationMode));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setIgnoreLayoutSafeArea"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetIgnoreLayoutSafeArea));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetIgnoreLayoutSafeArea"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetIgnoreLayoutSafeArea));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTitle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetTitle));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTitle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetTitle));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetMenus));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetMenus));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRecoverable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetRecoverable));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRecoverable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetRecoverable));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSystemTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
        NavDestinationBridge::SetNavDestinationSystemTransition));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSystemTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm),
        NavDestinationBridge::ResetNavDestinationSystemTransition));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPreferredOrientation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetPreferredOrientation));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPreferredOrientation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetPreferredOrientation));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableStatusBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetEnableStatusBar));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableStatusBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetEnableStatusBar));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableNavigationIndicator"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::SetEnableNavigationIndicator));
    navDestination->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableNavigationIndicator"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavDestinationBridge::ResetEnableNavigationIndicator));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navDestination"), navDestination);

    auto particle = panda::ObjectRef::New(vm);
    particle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisturbanceField"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ParticleBridge::SetDisturbanceField));
    particle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisturbanceField"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ParticleBridge::ResetDisturbanceField));
    particle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEmitter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ParticleBridge::SetEmitter));
    particle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEmitter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ParticleBridge::ResetEmitter));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "particle"), particle);

    auto symbolGlyph = panda::ObjectRef::New(vm);
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetFontColor));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetFontColor));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetFontSize));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetFontSize));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetFontWeight));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetFontWeight));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderingStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetRenderingStrategy));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderingStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetRenderingStrategy));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEffectStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetEffectStrategy));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEffectStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetEffectStrategy));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSymbolEffectOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetSymbolEffect));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSymbolEffectOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetSymbolEffect));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSymbolGlyphInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetSymbolGlyphInitialize));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSymbolGlyphInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetSymbolGlyphInitialize));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetMinFontScale));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetMinFontScale));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::SetMaxFontScale));
    symbolGlyph->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolGlyphBridge::ResetMaxFontScale));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolGlyph"), symbolGlyph);

    auto symbolSpan = panda::ObjectRef::New(vm);
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetFontColor));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetFontColor));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetFontSize));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetFontSize));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetFontWeight));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontWeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetFontWeight));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEffectStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetEffectStrategy));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEffectStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetEffectStrategy));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderingStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetRenderingStrategy));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderingStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetRenderingStrategy));
    symbolSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetId));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolSpan"), symbolSpan);

#ifdef MODEL_COMPONENT_SUPPORTED
    auto component3D = panda::ObjectRef::New(vm);
    component3D->Set(vm, panda::StringRef::NewFromUtf8(vm, "setShaderInputBuffer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Component3DBridge::SetShaderInputBuffer));
    component3D->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetShaderInputBuffer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Component3DBridge::ResetShaderInputBuffer));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "component3D"), component3D);
#endif

    auto containerSpan = panda::ObjectRef::New(vm);
    containerSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextBackgroundStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ContainerSpanBridge::SetTextBackgroundStyle));
    containerSpan->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextBackgroundStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ContainerSpanBridge::ResetTextBackgroundStyle));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "containerSpan"), containerSpan);

    auto relativeContainer = panda::ObjectRef::New(vm);
    relativeContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGuideLine"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), RelativeContainerBridge::SetGuideLine));
    relativeContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGuideLine"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), RelativeContainerBridge::ResetGuideLine));
    relativeContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarrier"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), RelativeContainerBridge::SetBarrier));
    relativeContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarrier"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), RelativeContainerBridge::ResetBarrier));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "relativeContainer"), relativeContainer);

    RegisterButtonAttributes(object, vm);
    RegisterToggleAttributes(object, vm);
    RegisterDividerAttributes(object, vm);
    RegisterNavigationAttributes(object, vm);
    RegisterImageAttributes(object, vm);
    RegisterNavRouterAttributes(object, vm);
    RegisterNavigatorAttributes(object, vm);
    RegisterNodeContainerAttributes(object, vm);
    RegisterRenderNodeAttributes(object, vm);
    RegisterFrameNodeAttributes(object, vm);
    RegisterPanelAttributes(object, vm);
    RegisterLineAttributes(object, vm);
    RegisterPathAttributes(object, vm);
    RegisterPolygonAttributes(object, vm);
    RegisterPolylineAttributes(object, vm);
    RegisterSideBarContainerAttributes(object, vm);
    RegisterCalendarPickerAttributes(object, vm);
    RegisterTabAttributes(object, vm);
    RegisterTabContentAttributes(object, vm);
#ifndef ARKUI_WEARABLE
    RegisterStepperItemAttributes(object, vm);
#endif
    RegisterHyperlinkAttributes(object, vm);
    RegisterMenuItemAttributes(object, vm);
    RegisterMenuAttributes(object, vm);
    RegisterMarqueeAttributes(object, vm);
    RegisterDatePickerAttributes(object, vm);
    RegisterAlphabetIndexerAttributes(object, vm);
    RegisterGaugeAttributes(object, vm);
    RegisterSwiperAttributes(object, vm);
#ifndef ARKUI_WEARABLE
    RegisterSelectAttributes(object, vm);
#endif
    RegisterRadioAttributes(object, vm);
    RegisterSliderAttributes(object, vm);
    RegisterRatingAttributes(object, vm);
    RegisterTimepickerAttributes(object, vm);
    RegisterTextpickerAttributes(object, vm);
    RegisterThemeAttributes(object, vm);
#ifndef ARKUI_WEARABLE
    RegisterWaterFlowAttributes(object, vm);
#endif
    RegisterCheckboxAttributes(object, vm);
    RegisterDataPanelAttributes(object, vm);
    RegisterScrollAttributes(object, vm);
    RegisterScrollableAttributes(object, vm);
    RegisterGridItemAttributes(object, vm);
    RegisterMarqueeAttributes(object, vm);
    RegisterProgressAttributes(object, vm);
    RegisterCommonShapeAttributes(object, vm);
    RegisterShapeAttributes(object, vm);
    RegisterRectAttributes(object, vm);
    RegisterListAttributes(object, vm);
    RegisterGridAttributes(object, vm);
    RegisterListItemGroupAttributes(object, vm);
#ifdef QRCODEGEN_SUPPORT
    RegisterQRCodeAttributes(object, vm);
#endif
    RegisterLoadingProgressAttributes(object, vm);
    RegisterTextClockAttributes(object, vm);
    RegisterListItemAttributes(object, vm);
    RegisterTextTimerAttributes(object, vm);
    RegisterRefreshAttributes(object, vm);
#ifdef PLUGIN_COMPONENT_SUPPORTED
    RegisterPluginAttributes(object, vm);
#endif
#ifdef XCOMPONENT_SUPPORTED
    RegisterXComponentAttributes(object, vm);
    RegisterXComponentNodeAttributes(object, vm);
#endif

#if defined(FORM_SUPPORTED) || defined(PREVIEW)
    RegisterFormAttributes(object, vm);
#endif
    RegisterResourceAttributes(object, vm);
    RegisterFlexAttributes(object, vm);
    RegisterBadgeAttributes(object, vm);
    RegisterScrollBarAttributes(object, vm);
    RegisterIndicatorComponentAttributes(object, vm);
#ifdef WEB_SUPPORTED
    RegisterWebAttributes(object, vm);
#endif
    RegisterLazyVGridLayoutAttributes(object, vm);
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
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxShape"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxShape));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxShape"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxShape));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetCheckboxResponseRegion));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::ResetCheckboxResponseRegion));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CheckboxBridge::SetCheckboxPadding));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CheckboxBridge::SetContentModifierBuilder));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CheckboxBridge::ResetCheckboxPadding));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CheckboxBridge::SetCheckboxOptions));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCheckboxOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CheckboxBridge::ResetCheckboxOnChange));
    checkbox->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCheckboxOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), CheckboxBridge::SetCheckboxOnChange));

    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "checkbox"), checkbox);
}

void ArkUINativeModule::RegisterTextpickerAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto textpicker = panda::ObjectRef::New(vm);
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCanLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetCanLoop));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetSelectedIndex));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetSelectedTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDisappearTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDefaultPickerItemHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDefaultPickerItemHeight));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetBackgroundColor));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCanLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetCanLoop));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetSelectedIndex));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetSelectedTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisappearTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDisappearTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDefaultPickerItemHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDefaultPickerItemHeight));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetBackgroundColor));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDivider));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDivider));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGradientHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetGradientHeight));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGradientHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetGradientHeight));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDisableTextStyleAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDisableTextStyleAnimation));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDisableTextStyleAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDisableTextStyleAnimation));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDefaultTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDefaultTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDefaultTextStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDefaultTextStyle));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextpickerEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetTextPickerEnableHapticFeedback));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextpickerEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetTextPickerEnableHapticFeedback));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetOnChange));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetOnChange));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetOnScrollStop));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetOnScrollStop));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textpicker"), textpicker);
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDigitalCrownSensitivity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::SetDigitalCrownSensitivity));
    textpicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDigitalCrownSensitivity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextPickerBridge::ResetDigitalCrownSensitivity));
}

void ArkUINativeModule::RegisterThemeAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto theme = panda::ObjectRef::New(vm);
    theme->Set(vm, panda::StringRef::NewFromUtf8(vm, "createAndBindTheme"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ThemeBridge::Create));
    theme->Set(vm, panda::StringRef::NewFromUtf8(vm, "pop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ThemeBridge::Pop));
    theme->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDefaultTheme"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ThemeBridge::SetDefaultTheme));
    theme->Set(vm, panda::StringRef::NewFromUtf8(vm, "removeFromCache"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ThemeBridge::RemoveFromCache));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "theme"), theme);
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
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTimepickerUseMilitaryTime"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTimepickerUseMilitaryTime));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTimepickerUseMilitaryTime"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTimepickerUseMilitaryTime));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTimepickerLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTimepickerLoop));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTimepickerLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTimepickerLoop));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTimepickerDateTimeOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTimepickerDateTimeOptions));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTimepickerDateTimeOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTimepickerDateTimeOptions));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTimepickerEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTimepickerEnableHapticFeedback));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTimepickerEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTimepickerEnableHapticFeedback));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTimepickerEnableCascade"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTimepickerEnableCascade));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTimepickerEnableCascade"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTimepickerEnableCascade));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTimepickerOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetTimepickerOnChange));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTimepickerOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetTimepickerOnChange));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "timepicker"), timepicker);
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDigitalCrownSensitivity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::SetDigitalCrownSensitivity));
    timepicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDigitalCrownSensitivity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TimepickerBridge::ResetDigitalCrownSensitivity));
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
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetContentModifierBuilder));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRatingOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetRatingOptions));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetOnChange));
    rating->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetOnChange));
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
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setValidSlideRange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetValidSlideRange));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetValidSlideRange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetValidSlideRange));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSelectedBorderRadius));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetSelectedBorderRadius));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInteractionMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetInteractionMode));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInteractionMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetInteractionMode));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinResponsiveDistance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetMinResponsiveDistance));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinResponsiveDistance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetMinResponsiveDistance));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetContentModifierBuilder));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSliderOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetSliderOptions));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetEnableHapticFeedback));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetEnableHapticFeedback));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::SetOnChange));
    slider->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SliderBridge::ResetOnChange));
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
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetContentModifierBuilder));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioOptions));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRadioOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::SetRadioOnChange));
    radio->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRadioOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RadioBridge::ResetRadioOnChange));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "radio"), radio);
}

#ifndef ARKUI_WEARABLE
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
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAvoidance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetAvoidance));
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
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAvoidance"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetAvoidance));
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
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setControlSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetControlSize));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetControlSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetControlSize));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetContentModifierBuilder));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuBackgroundColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuBackgroundColor));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuBackgroundBlurStyle));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuBackgroundBlurStyle));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetDivider));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetDivider));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDividerStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetDividerStyle));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDividerStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetDividerStyle));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetOptions));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetSelectDirection));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetSelectDirection));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuOutline"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::SetMenuOutline));
    select->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuOutline"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SelectBridge::ResetMenuOutline));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "select"), select);
}
#endif

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
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCreateWithLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetCreateWithLabel));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetLabel));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetLabel));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::SetOptions));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ButtonBridge::ResetOptions));
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
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setButtonBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonBorderRadius));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetButtonBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonBorderRadius));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setButtonBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonBorder));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetButtonBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonBorder));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setButtonSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonSize));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetButtonSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonSize));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setButtonRole"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonRole));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetButtonRole"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonRole));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setButtonStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetButtonStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonStyle));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setButtonControlSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetButtonControlSize));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetContentModifierBuilder));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetButtonControlSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetButtonControlSize));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetMinFontScale));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMinFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetMinFontScale));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::SetMaxFontScale));
    button->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMaxFontScale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ButtonBridge::ResetMaxFontScale));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "button"), button);
}

void ArkUINativeModule::RegisterToggleAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto toggle = panda::ObjectRef::New(vm);
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetSelectedColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectedColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetSelectedColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetOnChange));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetOnChange));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwitchPointColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetSwitchPointColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwitchPointColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetSwitchPointColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetHeight));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetHeight));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetResponseRegion));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetResponseRegion));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetPadding));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetPadding));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetBackgroundColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetBackgroundColor));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHoverEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetHoverEffect));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHoverEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetHoverEffect));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwitchStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetSwitchStyle));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwitchStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::ResetSwitchStyle));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetContentModifierBuilder));
    toggle->Set(vm, panda::StringRef::NewFromUtf8(vm, "setToggleOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ToggleBridge::SetToggleOptions));
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
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetAlignItems));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignItems"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetAlignItems));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridScroller"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetGridScroller));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridLayoutOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetGridLayoutOptions));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollFrameBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnScrollFrameBegin));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollFrameBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnScrollFrameBegin));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnWillScroll));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnWillScroll));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnDidScroll));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnDidScroll));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReachStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnReachStart));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReachStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnReachStart));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReachEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnReachEnd));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReachEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnReachEnd));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnScrollStart));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnScrollStart));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnScrollStop));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnScrollStop));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetOnGridScrollIndex));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetOnGridScrollIndex));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollBarUpdate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetOnGridScrollBarUpdate));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollBarUpdate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetOnGridScrollBarUpdate));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDragStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetOnGridItemDragStart));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDragStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetOnGridItemDragStart));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDragEnter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetOnGridItemDragEnter));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDragEnter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetOnGridItemDragEnter));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDragMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetOnGridItemDragMove));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDragMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetOnGridItemDragMove));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDragLeave"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetOnGridItemDragLeave));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDragLeave"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetOnGridItemDragLeave));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::SetOnGridItemDrop));
    grid->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridBridge::ResetOnGridItemDrop));
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
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableModeChangeAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetEnableModeChangeAnimation));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableModeChangeAnimation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetEnableModeChangeAnimation));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetHideTitleBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHideTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetHideTitleBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackButtonIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetBackButtonIcon));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackButtonIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetBackButtonIcon));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setIgnoreLayoutSafeArea"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetIgnoreLayoutSafeArea));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetIgnoreLayoutSafeArea"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetIgnoreLayoutSafeArea));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTitle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetTitle));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTitle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetTitle));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetMenus));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetMenus));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRecoverable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetRecoverable));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRecoverable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetRecoverable));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableDragBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetEnableDragBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableDragBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetEnableDragBar));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableToolBarAdaptation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::SetEnableToolBarAdaptation));
    navigation->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableToolBarAdaptation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NavigationBridge::ResetEnableToolBarAdaptation));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "navigation"), navigation);
}

void ArkUINativeModule::RegisterImageAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto image = panda::ObjectRef::New(vm);
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageShowSrc"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetImageShowSrc));
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
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageMatrix"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetImageMatrix));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageMatrix"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetImageMatrix));
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
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetImageBorder));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageBorder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetImageBorder));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetImageOpacity));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetImageOpacity));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetImageTransition));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetImageTransition));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEdgeAntialiasing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetEdgeAntialiasing));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEdgeAntialiasing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetEdgeAntialiasing));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResizableLattice"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetResizableLattice));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResizable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetResizable));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResizable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetResizable));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDynamicRangeMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetDynamicRangeMode));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDynamicRangeMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetDynamicRangeMode));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOrientation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetOrientation));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOrientation"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetOrientation));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnhancedImageQuality"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetEnhancedImageQuality));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnhancedImageQuality"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetEnhancedImageQuality));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPrivacySensitive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::SetPrivacySensitive));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPrivacySensitive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::ResetPrivacySensitive));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "enableAnalyzer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::EnableAnalyzer));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "analyzerConfig"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageBridge::AnalyzerConfig));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageBridge::SetOnComplete));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnComplete"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageBridge::ResetOnComplete));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnError"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageBridge::SetOnError));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnError"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageBridge::ResetOnError));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnFinish"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageBridge::SetOnFinish));
    image->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnFinish"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ImageBridge::ResetOnFinish));
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
    nodeContainer->Set(vm, panda::StringRef::NewFromUtf8(vm, "clean"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NodeContainerBridge::Clean));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "nodeContainer"), nodeContainer);
}

void ArkUINativeModule::RegisterRenderNodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto renderNode = panda::ObjectRef::New(vm);
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "createRenderNode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::CreateRenderNode));
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
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetLabel));
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
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetPosition));
    renderNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarkNodeGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RenderNodeBridge::SetMarkNodeGroup));
    RegisterRenderNodeBorderAndMaskAttributes(renderNode, vm);
    RegisterRenderNodeShapeClipAttributes(renderNode, vm);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "renderNode"), renderNode);
}

void ArkUINativeModule::RegisterFrameNodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto frameNode = panda::ObjectRef::New(vm);
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "isModifiable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::IsModifiable));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "createFrameNode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::CreateFrameNode));
        frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "createTypedFrameNode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::CreateTypedFrameNode));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "invalidate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::Invalidate));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "appendChild"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::AppendChild));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "insertChildAfter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::InsertChildAfter));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "removeChild"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::RemoveChild));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "clearChildren"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::ClearChildren));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getChildrenCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetChildrenCount));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getChild"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetChild));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFirstChildIndexWithoutExpand"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetFirstChildIndexWithoutExpand));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getLastChildIndexWithoutExpand"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetLastChildIndexWithoutExpand));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFirst"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetFirst));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getNextSibling"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetNextSibling));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPreviousSibling"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetPreviousSibling));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getParent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetParent));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "moveTo"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::MoveTo));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getIdByNodePtr"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetIdByNodePtr));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPositionToParent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetPositionToParent));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPositionToScreen"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetPositionToScreen));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPositionToWindow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetPositionToWindow));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPositionToParentWithTransform"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetPositionToParentWithTransform));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPositionToScreenWithTransform"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetPositionToScreenWithTransform));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPositionToWindowWithTransform"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetPositionToWindowWithTransform));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getMeasuredSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetMeasuredSize));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getLayoutPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetLayoutPosition));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getConfigBorderWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetConfigBorderWidth));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getConfigPadding"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetConfigPadding));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getConfigMargin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetConfigMargin));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getConfigSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetConfigSize));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getId"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetId));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getNodeType"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetNodeType));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetOpacity));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "isVisible"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::IsVisible));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "isClipToFrame"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::IsClipToFrame));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "isAttached"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::IsAttached));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorInfo"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetInspectorInfo));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMeasuredSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetMeasuredSize));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLayoutPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetLayoutPosition));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "measureNode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::MeasureNode));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "layoutNode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::LayoutNode));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNeedsLayout"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetNeedsLayout));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnClick"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnClick));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnTouch"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnTouch));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnAppear"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnAppear));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDisappear"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnDisappear));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnAttach"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnAttach));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDetach"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnDetach));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnKeyEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnKeyEvent));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnFocus));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnBlur"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnBlur));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnHover"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnHover));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnHoverMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnHoverMove));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnMouse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnMouse));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSizeChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnSizeChange));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnVisibleAreaApproximateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetOnVisibleAreaApproximateChange));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "propertyUpdate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::PropertyUpdate));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerFrameCallback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::RegisterFrameCallback));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "markDirty"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::MarkDirty));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCrossLanguageOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetCrossLanguageOptions));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getCrossLanguageOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetCrossLanguageOptions));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "checkIfCanCrossLanguageAttributeSetting"),
        panda::FunctionRef::New(
            const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::CheckIfCanCrossLanguageAttributeSetting));

    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "createNodeContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::CreateNodeContent));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "addFrameNodeToNodeContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::AddFrameNodeToNodeContent));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "removeFrameNodeFromNodeContent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::RemoveFrameNodeFromNodeContent));

    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFirstUINode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetFirstUINode));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "getCustomPropertyCapiByKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::GetCustomPropertyCapiByKey));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCustomPropertyModiferByKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::SetCustomPropertyModiferByKey));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "triggerOnReuse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::TriggerOnReuse));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "triggerOnRecycle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::TriggerOnRecycle));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "addSupportedStates"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::AddSupportedStates));
    frameNode->Set(vm, panda::StringRef::NewFromUtf8(vm, "removeSupportedStates"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FrameNodeBridge::RemoveSupportedStates));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "frameNode"), frameNode);
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
#ifndef ARKUI_WEARABLE
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
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCalendarPickerHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerHeight));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCalendarPickerHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerHeight));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCalendarPickerBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerBorderColor));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCalendarPickerBorderColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerBorderColor));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCalendarPickerBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerBorderRadius));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCalendarPickerBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerBorderRadius));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCalendarPickerMarkToday"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerMarkToday));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCalendarPickerMarkToday"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerMarkToday));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCalendarPickerOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::SetCalendarPickerOnChange));
    calendarPicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCalendarPickerOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), CalendarPickerBridge::ResetCalendarPickerOnChange));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "calendarPicker"), calendarPicker);
#endif
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
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSelectIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::SetSelectIcon));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSelectIcon"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::ResetSelectIcon));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::SetOnChange));
    menuitem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuItemBridge::ResetOnChange));
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
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetWidth));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetWidth));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuItemDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetMenuItemDivider));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuItemDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetMenuItemDivider));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMenuItemGroupDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetMenuItemGroupDivider));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMenuItemGroupDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetMenuItemGroupDivider));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSubMenuExpandingMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetSubMenuExpandingMode));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSubMenuExpandingMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetSubMenuExpandingMode));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::SetFontSize));
    menu->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MenuBridge::ResetFontSize));
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
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabOnUnselected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabOnUnselected));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabOnUnselected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabOnUnselected));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarBackgroundColor));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarBackgroundColor));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarBackgroundBlurStyle));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarBackgroundBlurStyle));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBarBackgroundEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarBackgroundEffect));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBarBackgroundEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarBackgroundEffect));
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
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOptionsIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOptionsIndex));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOptionsIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOptionsIndex));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOptionsController"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOptionsController));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOptionsController"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOptionsController));
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
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabEdgeEffect));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabEdgeEffect));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabPageFlipMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabPageFlipMode));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabPageFlipMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabPageFlipMode));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetWidthAuto));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetWidthAuto));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetHeightAuto));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabHeight"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetHeightAuto));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAnimateMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetAnimateMode));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAnimateMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetAnimateMode));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOnSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnSelected));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOnSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnSelected));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCachedMaxCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetCachedMaxCount));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCachedMaxCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetCachedMaxCount));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnChange));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnChange));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOnTabBarClick"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnTabBarClick));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOnTabBarClick"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnTabBarClick));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOnAnimationStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnAnimationStart));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOnAnimationStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnAnimationStart));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOnAnimationEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnAnimationEnd));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOnAnimationEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnAnimationEnd));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOnGestureSwipe"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnGestureSwipe));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOnGestureSwipe"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnGestureSwipe));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsOnContentWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnContentWillChange));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsOnContentWillChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnContentWillChange));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabsCustomContentTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsCustomContentTransition));
    tabs->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabsCustomContentTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsCustomContentTransition));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "tabs"), tabs);
}

#ifndef ARKUI_WEARABLE
void ArkUINativeModule::RegisterStepperItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto stepperItem = panda::ObjectRef::New(vm);
    stepperItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNextLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::SetNextLabel));
    stepperItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNextLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::ResetNextLabel));
    stepperItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPrevLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::SetPrevLabel));
    stepperItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPrevLabel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::ResetPrevLabel));
    stepperItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStatus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::SetStatus));
    stepperItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStatus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), StepperItemBridge::ResetStatus));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "stepperItem"), stepperItem);
}
#endif

void ArkUINativeModule::RegisterTabContentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto tabContent = panda::ObjectRef::New(vm);
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabBar));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabBar));
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
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabContentOnWillShow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentOnWillShow));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabContentOnWillShow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentOnWillShow));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTabContentOnWillHide"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::SetTabContentOnWillHide));
    tabContent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTabContentOnWillHide"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabContentBridge::ResetTabContentOnWillHide));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "tabContent"), tabContent);
}

void ArkUINativeModule::RegisterRefreshAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto refresh = panda::ObjectRef::New(vm);
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRefreshOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::SetRefreshOffset));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRefreshOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::ResetRefreshOffset));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPullToRefresh"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::SetPullToRefresh));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPullToRefresh"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::ResetPullToRefresh));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPullDownRatio"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::SetPullDownRatio));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPullDownRatio"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::ResetPullDownRatio));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnOffsetChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::SetOnOffsetChange));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnOffsetChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::ResetOnOffsetChange));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnStateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::SetOnStateChange));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnStateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::ResetOnStateChange));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnRefreshing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::SetOnRefreshing));
    refresh->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnRefreshing"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RefreshBridege::ResetOnRefreshing));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "refresh"), refresh);
}

void ArkUINativeModule::RegisterHyperlinkAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto hyperlink = panda::ObjectRef::New(vm);
    hyperlink->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::SetColor));
    hyperlink->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::ResetColor));
    hyperlink->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::SetDraggable));
    hyperlink->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDraggable"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::ResetDraggable));
    hyperlink->Set(vm, panda::StringRef::NewFromUtf8(vm, "setResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::SetResponseRegion));
    hyperlink->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetResponseRegion"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::ResetResponseRegion));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "hyperlink"), hyperlink);
}

#if defined(FORM_SUPPORTED) || defined(PREVIEW)
void ArkUINativeModule::RegisterFormAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto formComponent = panda::ObjectRef::New(vm);
#ifdef PREVIEW
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVisibility"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVisibility"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAllowUpdate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAllowUpdate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDimension"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDimension"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setModuleName"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetModuleName"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
    formComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ArkUINativeModule::PreviewMockComponent));
#else
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
#endif
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
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetEnableHapticFeedback));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetEnableHapticFeedback));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDatePickerOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetDatePickerOnChange));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDatePickerOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetDatePickerOnChange));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDatePickerOnDateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetDatePickerOnDateChange));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDatePickerOnDateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetDatePickerOnDateChange));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "datePicker"), datePicker);
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDigitalCrownSensitivity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::SetDigitalCrownSensitivity));
    datePicker->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDigitalCrownSensitivity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DatePickerBridge::ResetDigitalCrownSensitivity));
}

#ifndef ARKUI_WEARABLE
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
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetScrollBar));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetScrollBar));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetScrollBarWidth));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetScrollBarWidth));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBarColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetScrollBarColor));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBarColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetScrollBarColor));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCachedCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetCachedCount));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCachedCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetCachedCount));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setWaterFlowInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetWaterFlowInitialize));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetWaterFlowInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetWaterFlowInitialize));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollFrameBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnScrollFrameBegin));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollFrameBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnScrollFrameBegin));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnWillScroll));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnWillScroll));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnDidScroll));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnDidScroll));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReachStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnReachStart));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReachStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnReachStart));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReachEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnReachEnd));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReachEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnReachEnd));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnScrollStart));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnScrollStart));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnScrollStop));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnScrollStop));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::SetOnWaterFlowScrollIndex));
    waterflow->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WaterFlowBridge::ResetOnWaterFlowScrollIndex));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "waterFlow"), waterflow);
}
#endif

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
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupItemBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupItemBorderRadius));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupItemBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupItemBorderRadius));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setItemBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetItemBorderRadius));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetItemBorderRadius"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetItemBorderRadius));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupBackgroundBlurStyle));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupBackgroundBlurStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupBackgroundBlurStyle));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setPopupTitleBackground"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupTitleBackground));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetPopupTitleBackground"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupTitleBackground));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAdaptiveWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetAdaptiveWidth));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAdaptiveWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetAdaptiveWidth));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoCollapse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetAutoCollapse));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAutoCollapse"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetAutoCollapse));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetEnableHapticFeedback));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableHapticFeedback"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetEnableHapticFeedback));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetOnSelected));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetOnSelected));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetOnSelect));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetOnSelect));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnRequestPopupData"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetOnRequestPopupData));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnRequestPopupData"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetOnRequestPopupData));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnPopupSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetOnPopupSelect));
    alphabetIndexer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnPopupSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetOnPopupSelect));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "alphabetIndexer"), alphabetIndexer);
}

void ArkUINativeModule::RegisterGaugeAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto gauge = panda::ObjectRef::New(vm);
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugeVaule"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetGaugeValue));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugeVaule"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetGaugeValue));
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
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetContentModifierBuilder));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGaugePrivacySensitive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::SetGaugePrivacySensitive));
    gauge->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGaugePrivacySensitive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GaugeBridge::ResetGaugePrivacySensitive));
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
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarqueeUpdateStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetMarqueeUpdateStrategy));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMarqueeUpdateStrategy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetMarqueeUpdateStrategy));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarqueeOnStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetMarqueeOnStart));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMarqueeOnStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetMarqueeOnStart));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarqueeOnBounce"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetMarqueeOnBounce));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMarqueeOnBounce"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetMarqueeOnBounce));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMarqueeOnFinish"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetMarqueeOnFinish));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMarqueeOnFinish"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::ResetMarqueeOnFinish));
    marquee->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), MarqueeBridge::SetInitialize));
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
    dataPanel->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), DataPanelBridge::SetContentModifierBuilder));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "dataPanel"), dataPanel);
}

void ArkUINativeModule::RegisterScrollableAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto scrollable = panda::ObjectRef::New(vm);
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetContentClip));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContentClip"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetContentClip));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetEdgeEffect));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEdgeEffect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetEdgeEffect));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFadingEdge"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetFadingEdge));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFadingEdge"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetFadingEdge));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReachStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnReachStart));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReachStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnReachStart));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReachEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetOnReachEnd));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReachEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetOnReachEnd));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFlingSpeedLimit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollableBridge::SetFlingSpeedLimit));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFlingSpeedLimit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollableBridge::ResetFlingSpeedLimit));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackToTop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::SetBackToTop));
    scrollable->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackToTop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollableBridge::ResetBackToTop));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "scrollable"), scrollable);
}

void ArkUINativeModule::RegisterScrollAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto scroll = panda::ObjectRef::New(vm);
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetScrollInitialize));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetScrollInitialize));
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
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnablePaging"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetEnablePaging));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnablePaging"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetEnablePaging));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInitialOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::SetInitialOffset));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInitialOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), ScrollBridge::ResetInitialOffset));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollOnScrollStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::SetScrollOnScrollStart));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollOnScrollStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::ResetScrollOnScrollStart));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollOnScrollEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::SetScrollOnScrollEnd));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollOnScrollEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::ResetScrollOnScrollEnd));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::SetScrollOnScrollStop));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::ResetScrollOnScrollStop));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollOnScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::SetScrollOnScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollOnScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::ResetScrollOnScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollOnScrollEdge"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::SetScrollOnScrollEdge));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollOnScrollEdge"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::ResetScrollOnScrollEdge));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollOnDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::SetScrollOnDidScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollOnDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::ResetScrollOnDidScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollOnWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::SetScrollOnWillScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollOnWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::ResetScrollOnWillScroll));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollOnScrollFrameBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::SetScrollOnScrollFrameBegin));
    scroll->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollOnScrollFrameBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBridge::ResetScrollOnScrollFrameBegin));
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
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridItemOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::SetGridItemOptions));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGridItemOnSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::SetGridItemOnSelected));
    gridItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGridItemOnSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), GridItemBridge::ResetGridItemOnSelected));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "gridItem"), gridItem);
}

void ArkUINativeModule::RegisterProgressAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto progress = panda::ObjectRef::New(vm);
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setProgressInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressInitialize));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetProgressInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressInitialize));
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
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetContentModifierBuilder));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setProgressPrivacySensitive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::SetProgressPrivacySensitive));
    progress->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetProgressPrivacySensitive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ProgressBridge::ResetProgressPrivacySensitive));
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
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperInitialize));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperInitialize));
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
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperSwipeByGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperSwipeByGroup));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperSwipeByGroup"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperSwipeByGroup));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperDisplayArrow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperDisplayArrow));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperDisplayArrow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperDisplayArrow));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperCurve"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperCurve));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperCurve"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperCurve));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnChange));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnChange));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperOnSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnSelected));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperOnSelected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnSelected));
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
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperIsShown"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperIsShown));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperIsShown"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperIsShown));
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
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetNestedScroll));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetNestedScroll));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperOnAnimationStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnAnimationStart));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperOnAnimationStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnAnimationStart));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperOnAnimationEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnAnimationEnd));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperOnAnimationEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnAnimationEnd));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperOnGestureSwipe"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnGestureSwipe));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperOnGestureSwipe"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnGestureSwipe));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperOnUnselected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnUnselected));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperOnUnselected"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnUnselected));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setIndicatorInteractive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetIndicatorInteractive));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetIndicatorInteractive"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetIndicatorInteractive));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperCustomContentTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperCustomContentTransition));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperCustomContentTransition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperCustomContentTransition));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperOnContentDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetOnContentDidScroll));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperOnContentDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetOnContentDidScroll));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperPageFlipMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperPageFlipMode));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperPageFlipMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperPageFlipMode));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwiperOnContentWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::SetSwiperOnContentWillScroll));
    swiper->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwiperOnContentWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SwiperBridge::ResetSwiperOnContentWillScroll));
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
    listItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSwipeAction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemBridge::SetSwipeAction));
    listItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSwipeAction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemBridge::ResetSwipeAction));
    listItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemBridge::SetOnSelect));
    listItem->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnSelect"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemBridge::ResetOnSelect));
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
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListDirection));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListDirection"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListDirection));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListFriction));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListFriction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListFriction));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListMaintainVisibleContentPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListMaintainVisibleContentPosition));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListMaintainVisibleContentPosition"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListMaintainVisibleContentPosition));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListStackFromEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListStackFromEnd));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListStackFromEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListStackFromEnd));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListNestedScroll));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListNestedScroll));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListScrollBar));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListScrollBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListScrollBar));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListScrollBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListScrollBarWidth));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListScrollBarWidth"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListScrollBarWidth));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListScrollBarColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListScrollBarColor));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListScrollBarColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListScrollBarColor));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAlignListItem"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetAlignListItem));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAlignListItem"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetAlignListItem));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollSnapAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetScrollSnapAlign));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollSnapAlign"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetScrollSnapAlign));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentStartOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetContentStartOffset));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContentStartOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetContentStartOffset));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentEndOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetContentEndOffset));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetContentEndOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetContentEndOffset));
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
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListChildrenMainSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetListChildrenMainSize));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListChildrenMainSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetListChildrenMainSize));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetSpace));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetSpace"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetSpace));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInitialIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetInitialIndex));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInitialIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetInitialIndex));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInitialScroller"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetInitialScroller));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInitialScroller"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetInitialScroller));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnScrollIndex));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnScrollIndex));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollVisibleContentChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnScrollVisibleContentChange));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollVisibleContentChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnScrollVisibleContentChange));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnItemMove));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnItemMove));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDragStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnItemDragStart));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDragStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnItemDragStart));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDragEnter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnItemDragEnter));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDragEnter"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnItemDragEnter));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDragMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnItemDragMove));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDragMove"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnItemDragMove));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDragLeave"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnItemDragLeave));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDragLeave"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnItemDragLeave));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnItemDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnItemDrop));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnItemDrop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnItemDrop));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnListScrollStart));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnListScrollStart));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnListScrollStop));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollStop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnListScrollStop));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnScrollFrameBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnListScrollFrameBegin));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnScrollFrameBegin"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnListScrollFrameBegin));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnListWillScroll));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnWillScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnListWillScroll));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnListDidScroll));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDidScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnListDidScroll));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReachStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnListReachStart));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReachStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnListReachStart));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnReachEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::SetOnListReachEnd));
    list->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnReachEnd"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListBridge::ResetOnListReachEnd));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "list"), list);
}

void ArkUINativeModule::RegisterListItemGroupAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto listItemGroup = panda::ObjectRef::New(vm);
    listItemGroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemGroupBridge::SetDivider));
    listItemGroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDivider"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemGroupBridge::ResetDivider));
    listItemGroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListItemGroupChildrenMainSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemGroupBridge::SetChildrenMainSize));
    listItemGroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListItemGroupChildrenMainSize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemGroupBridge::ResetChildrenMainSize));
    listItemGroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "setListItemGroupInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemGroupBridge::SetListItemGroupInitialize));
    listItemGroup->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetListItemGroupInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ListItemGroupBridge::ResetListItemGroupInitialize));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "listItemGroup"), listItemGroup);
}

#ifdef QRCODEGEN_SUPPORT
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
    qrcode->Set(vm, panda::StringRef::NewFromUtf8(vm, "setQRValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), QRCodeBridge::SetQRValue));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "qrcode"), qrcode);
}
#endif

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
    loadingProgress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::SetForegroundColor));
    loadingProgress->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetForegroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::ResetForegroundColor));
    loadingProgress->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LoadingProgressBridge::SetContentModifierBuilder));
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
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetTextShadow));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetTextShadow));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetFontFeature));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFontFeature"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetFontFeature));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetContentModifierBuilder));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDateTimeOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetDateTimeOptions));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDateTimeOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetDateTimeOptions));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextClockTimeZoneOffset"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetTextClockTimeZoneOffset));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextClockController"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetTextClockController));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextClockOnDateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::SetTextClockOnDateChange));
    textClock->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextClockOnDateChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextClockBridge::ResetTextClockOnDateChange));
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
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::SetTextShadow));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextShadow"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::ResetTextShadow));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setContentModifierBuilder"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetContentModifierBuilder));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextTimerOptions"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TextTimerBridge::SetTextTimerOptions));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "setTextTimerOnTimer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::SetTextTimerOnTimer));
    textTimer->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetTextTimerOnTimer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM *>(vm), TextTimerBridge::ResetTextTimerOnTimer));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "textTimer"), textTimer);
}
#ifdef XCOMPONENT_SUPPORTED
void ArkUINativeModule::RegisterXComponentAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    auto xComponent = panda::ObjectRef::New(vm);
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setXComponentInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetXComponentInitialize));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetXComponentInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetXComponentInitialize));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetBackgroundColor));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetBackgroundColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetBackgroundColor));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetOpacity));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOpacity"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetOpacity));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setGrayscale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetGrayscale));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetGrayscale"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetGrayscale));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnLoad"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetOnLoad));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnLoad"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetOnLoad));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnDestroy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetOnDestroy));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnDestroy"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetOnDestroy));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableAnalyzer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetEnableAnalyzer));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableAnalyzer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetEnableAnalyzer));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableSecure"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetEnableSecure));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableSecure"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetEnableSecure));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setHdrBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetHdrBrightness));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetHdrBrightness"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetHdrBrightness));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setEnableTransparentLayer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetEnableTransparentLayer));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetEnableTransparentLayer"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetEnableTransparentLayer));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRenderFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::SetRenderFit));
    xComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRenderFit"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), XComponentBridge::ResetRenderFit));
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

void ArkUINativeModule::RegisterResourceAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto resource = panda::ObjectRef::New(vm);
    resource->Set(vm, panda::StringRef::NewFromUtf8(vm, "updateColorMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ResourceBridge::UpdateColorMode));
    resource->Set(vm, panda::StringRef::NewFromUtf8(vm, "restore"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ResourceBridge::Restore));
    resource->Set(vm, panda::StringRef::NewFromUtf8(vm, "getColorValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ResourceBridge::GetColorValue));
    resource->Set(vm, panda::StringRef::NewFromUtf8(vm, "getStringValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ResourceBridge::GetStringValue));
    resource->Set(vm, panda::StringRef::NewFromUtf8(vm, "getNumberValue"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ResourceBridge::GetNumberValue));
    resource->Set(vm, panda::StringRef::NewFromUtf8(vm, "clearCache"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ResourceBridge::ClearCache));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "resource"), resource);
}

void ArkUINativeModule::RegisterFlexAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto flex = panda::ObjectRef::New(vm);
    flex->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFlexInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FlexBridge::SetFlexInitialize));
    flex->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFlexInitialize"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), FlexBridge::ResetFlexInitialize));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "flex"), flex);
}

void ArkUINativeModule::RegisterBadgeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto badge = panda::ObjectRef::New(vm);
    badge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBadgeParamWithNumber"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BadgeBridge::SetBadgeParamWithNumber));
    badge->Set(vm, panda::StringRef::NewFromUtf8(vm, "setBadgeParamWithString"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), BadgeBridge::SetBadgeParamWithString));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "badge"), badge);
}

void ArkUINativeModule::RegisterScrollBarAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto ScrollBar = panda::ObjectRef::New(vm);
    ScrollBar->Set(vm, panda::StringRef::NewFromUtf8(vm, "setScrollBarEnableNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBarBridge::SetScrollBarEnableNestedScroll));
    ScrollBar->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetScrollBarEnableNestedScroll"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ScrollBarBridge::ResetScrollBarEnableNestedScroll));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "ScrollBar"), ScrollBar);
}

void ArkUINativeModule::RegisterIndicatorComponentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto indicatorComponent = panda::ObjectRef::New(vm);
    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setInitialIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetInitialIndex));
    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetInitialIndex"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetInitialIndex));

    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetCount));
    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCount"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetCount));

    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetStyle));
    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetStyle"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetStyle));

    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetLoop));
    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetLoop"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetLoop));

    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetVertical));
    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetVertical"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetVertical));

    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "setOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::SetOnChange));
    indicatorComponent->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetOnChange"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), IndicatorComponentBridge::ResetOnChange));

    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "indicatorComponent"), indicatorComponent);
}

#ifdef WEB_SUPPORTED
void ArkUINativeModule::RegisterWebAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto web = panda::ObjectRef::New(vm);
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setJavaScriptAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetJavaScriptAccess));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetJavaScriptAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetJavaScriptAccess));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setFileAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetFileAccessEnabled));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetFileAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetFileAccessEnabled));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDomStorageAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetDomStorageAccessEnabled));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDomStorageAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetDomStorageAccessEnabled));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMixedMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetMixedMode));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMixedMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetMixedMode));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setZoomAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetZoomAccessEnabled));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetZoomAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetZoomAccessEnabled));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCacheMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetCacheMode));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetCacheMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetCacheMode));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setDarkMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetDarkMode));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetDarkMode"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetDarkMode));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setMultiWindowAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetMultiWindowAccessEnabled));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetMultiWindowAccess"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetMultiWindowAccessEnabled));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAllowWindowOpenMethod"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::SetAllowWindowOpenMethod));
    web->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetAllowWindowOpenMethod"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), WebBridge::ResetAllowWindowOpenMethod));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "web"), web);
}
#endif

void ArkUINativeModule::RegisterImageAnimatorAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
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
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAutoMonitorInvisibleArea"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetAutoMonitorInvisibleArea));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageAnimatorOnStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnStart));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageAnimatorOnStart"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnStart));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageAnimatorOnPause"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnPause));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageAnimatorOnPause"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnPause));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageAnimatorOnRepeat"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnRepeat));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageAnimatorOnRepeat"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnRepeat));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageAnimatorOnCancel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnCancel));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageAnimatorOnCancel"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnCancel));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "setImageAnimatorOnFinish"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnFinish));
    imageAnimator->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetImageAnimatorOnFinish"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnFinish));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageAnimator"), imageAnimator);
}

void ArkUINativeModule::RegisterLazyVGridLayoutAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    auto lazyGridLayout = panda::ObjectRef::New(vm);
    lazyGridLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyGridLayoutBridge::SetColumnsGap));
    lazyGridLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyGridLayoutBridge::ResetColumnsGap));
    lazyGridLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyGridLayoutBridge::SetRowsGap));
    lazyGridLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetRowsGap"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyGridLayoutBridge::ResetRowsGap));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "lazyGridLayout"), lazyGridLayout);

    auto lazyVGridLayout = panda::ObjectRef::New(vm);
    lazyVGridLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "setColumnsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyVGridLayoutBridge::SetColumnsTemplate));
    lazyVGridLayout->Set(vm, panda::StringRef::NewFromUtf8(vm, "resetColumnsTemplate"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), LazyVGridLayoutBridge::ResetColumnsTemplate));
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "lazyVGridLayout"), lazyVGridLayout);
}
} // namespace OHOS::Ace::NG
